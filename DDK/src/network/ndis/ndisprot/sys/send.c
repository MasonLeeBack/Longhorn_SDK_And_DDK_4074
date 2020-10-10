/*++

Copyright (c) 2000  Microsoft Corporation

Module Name:

    send.c

Abstract:

    NDIS protocol entry points and utility routines to handle sending
    data.

Environment:

    Kernel mode only.

Revision History:

    arvindm     4/10/2000    Created

--*/

#include "precomp.h"

#define __FILENUMBER 'DNES'




NTSTATUS
NdisprotWrite(
    IN PDEVICE_OBJECT       pDeviceObject,
    IN PIRP                 pIrp
    )
/*++

Routine Description:

    Dispatch routine to handle IRP_MJ_WRITE. 

Arguments:

    pDeviceObject - pointer to our device object
    pIrp - Pointer to request packet

Return Value:

    NT status code.

--*/
{
    PIO_STACK_LOCATION      pIrpSp;
    ULONG                   DataLength;
    NTSTATUS                NtStatus;
    NDIS_STATUS             Status;
    PNDISPROT_OPEN_CONTEXT   pOpenContext;
    PNET_BUFFER_LIST        pNetBufferList;
    PNDIS_BUFFER            pNdisBuffer;
    NDISPROT_ETH_HEADER UNALIGNED *pEthHeader;
    PVOID                   CancelId;

    UNREFERENCED_PARAMETER(pDeviceObject);

    pIrpSp = IoGetCurrentIrpStackLocation(pIrp);
    pOpenContext = pIrpSp->FileObject->FsContext;


    do
    {
        if (pOpenContext == NULL)
        {
            DEBUGP(DL_WARN, ("Write: FileObject %p not yet associated with a device\n",
                pIrpSp->FileObject));
            NtStatus = STATUS_INVALID_HANDLE;
            break;
        }
               
        NPROT_STRUCT_ASSERT(pOpenContext, oc);

        if (pIrp->MdlAddress == NULL)
        {
            DEBUGP(DL_FATAL, ("Write: NULL MDL address on IRP %p\n", pIrp));
            NtStatus = STATUS_INVALID_PARAMETER;
            break;
        }

        //
        // Try to get a virtual address for the MDL.
        //
        pEthHeader = MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority);

        if (pEthHeader == NULL)
        {
            DEBUGP(DL_FATAL, ("Write: MmGetSystemAddr failed for"
                    " IRP %p, MDL %p\n",
                    pIrp, pIrp->MdlAddress));
            NtStatus = STATUS_INSUFFICIENT_RESOURCES;
            break;
        }

        //
        // Sanity-check the length.
        //
        DataLength = MmGetMdlByteCount(pIrp->MdlAddress);
        if (DataLength < sizeof(NDISPROT_ETH_HEADER))
        {
            DEBUGP(DL_WARN, ("Write: too small to be a valid packet (%d bytes)\n",
                DataLength));
            NtStatus = STATUS_BUFFER_TOO_SMALL;
            break;
        }

        if (DataLength > (pOpenContext->MaxFrameSize + sizeof(NDISPROT_ETH_HEADER)))
        {
            DEBUGP(DL_WARN, ("Write: Open %p: data length (%d)"
                    " larger than max frame size (%d)\n",
                    pOpenContext, DataLength, pOpenContext->MaxFrameSize));

            NtStatus = STATUS_INVALID_BUFFER_SIZE;
            break;
        }

        if (pEthHeader->EthType != Globals.EthType)
        {
            DEBUGP(DL_WARN, ("Write: Failing send with EthType %x\n",
                pEthHeader->EthType));
            NtStatus = STATUS_INVALID_PARAMETER;
            break;
        }
       
        if (!NPROT_MEM_CMP(pEthHeader->SrcAddr, pOpenContext->CurrentAddress, NPROT_MAC_ADDR_LEN))
        {
            DEBUGP(DL_WARN, ("Write: Failing with invalid Source address"));
            NtStatus = STATUS_INVALID_PARAMETER;
            break;
        }
        

        if (!NPROT_MEM_CMP(pEthHeader->SrcAddr, pOpenContext->CurrentAddress, NPROT_MAC_ADDR_LEN))
        {
            DEBUGP(DL_WARN, ("Write: Failing with invalid Source address"));
            NtStatus = STATUS_INVALID_PARAMETER;
            break;
        }

        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);

        if (!NPROT_TEST_FLAGS(pOpenContext->Flags, NPROTO_BIND_FLAGS, NPROTO_BIND_ACTIVE))
        {
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

            DEBUGP(DL_FATAL, ("Write: Open %p is not bound"
            " or in low power state\n", pOpenContext));

            NtStatus = STATUS_INVALID_HANDLE;
            break;
        }

        if ((pOpenContext->State == NdisprotPaused)
            || (pOpenContext->State == NdisprotPausing))
        {
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);
            
            DEBUGP(DL_INFO, ("Device is paused.\n"));
            NtStatus = STATUS_UNSUCCESSFUL;
            break;
        }


        pNdisBuffer = pIrp->MdlAddress;
        NPROT_ASSERT(pOpenContext->SendNetBufferListPool != NULL);
        pNetBufferList = NdisAllocateNetBufferAndNetBufferList(
                                pOpenContext->SendNetBufferListPool,
                                sizeof(NPROT_SEND_NETBUFLIST_RSVD), //Request control offset delta
                                0,           // back fill size
                                pNdisBuffer,
                                0,          // Data offset
                                DataLength,
                                FALSE);
        
        if (pNetBufferList == NULL)
        {
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);
            
            DEBUGP(DL_FATAL, ("Write: open %p, failed to alloc send net buffer list\n",
                    pOpenContext));
            NtStatus = STATUS_INSUFFICIENT_RESOURCES;
            break;
        }
        pOpenContext->PendedSendCount++;

        NPROT_REF_OPEN(pOpenContext);  // pended send

        IoMarkIrpPending(pIrp);

        //
        //  Initialize the NetBufferList ref count. This NetBufferList will be freed
        //  when this count goes to zero.
        //
        NPROT_SEND_NBL_RSVD(pNetBufferList)->RefCount = 1;

        //
        //  We set up a cancel ID on each send NetBufferList (which maps to a Write IRP), 
        //  and save the NetBufferList pointer in the IRP. If the IRP gets cancelled, we use
        //  NdisCancelSendNetBufferLists() to cancel the NetBufferList.
        //
       
        CancelId = NPROT_GET_NEXT_CANCEL_ID();
        NDIS_SET_NET_BUFFER_LIST_CANCEL_ID(pNetBufferList, CancelId);
        pIrp->Tail.Overlay.DriverContext[0] = (PVOID)pOpenContext;
        pIrp->Tail.Overlay.DriverContext[1] = (PVOID)pNetBufferList;

        NPROT_INSERT_TAIL_LIST(&pOpenContext->PendedWrites, &pIrp->Tail.Overlay.ListEntry);

        IoSetCancelRoutine(pIrp, NdisprotCancelWrite);


        NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

        //
        //  Set a back pointer from the packet to the IRP.
        //
        NPROT_IRP_FROM_SEND_NBL(pNetBufferList) = pIrp;

        NtStatus = STATUS_PENDING;


#if SEND_DBG
        {
            PUCHAR      pData;

            pData = MmGetSystemAddressForMdlSafe(pNdisBuffer, NormalPagePriority);
            NPROT_ASSERT(pEthHeader == pData);

            DEBUGP(DL_VERY_LOUD, 
                ("Write: MDL %p, MdlFlags %x, SystemAddr %p, %d bytes\n",
                    pIrp->MdlAddress, pIrp->MdlAddress->MdlFlags, pData, DataLength));

            DEBUGPDUMP(DL_VERY_LOUD, pData, MIN(DataLength, 48));
        }
#endif // SEND_DBG

        pNetBufferList->SourceHandle = pOpenContext->BindingHandle;
        ASSERT (pNdisBuffer->Next == NULL);

        NdisSendNetBufferLists(        
                        pOpenContext->BindingHandle,
                        pNetBufferList,
                        0,    //SendFlag
                        FALSE);

    }
    while (FALSE);

    if (NtStatus != STATUS_PENDING)
    {
        pIrp->IoStatus.Status = NtStatus;
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);
    }

    return (NtStatus);
}



VOID
NdisprotCancelWrite(
    IN PDEVICE_OBJECT               pDeviceObject,
    IN PIRP                         pIrp
    )
/*++

Routine Description:

    Cancel a pending write IRP. This routine attempt to cancel the NDIS send.

Arguments:

    pDeviceObject - pointer to our device object
    pIrp - IRP to be cancelled

Return Value:

    None

--*/
{
    PNDISPROT_OPEN_CONTEXT       pOpenContext;
    PLIST_ENTRY                 pIrpEntry;
    PNET_BUFFER_LIST            pNetBufList;

    UNREFERENCED_PARAMETER(pDeviceObject);
        
    IoReleaseCancelSpinLock(pIrp->CancelIrql);

    //
    //  The NDIS packet representing this Write IRP.
    //
    pNetBufList = NULL;
    
    pOpenContext = (PNDISPROT_OPEN_CONTEXT) pIrp->Tail.Overlay.DriverContext[0];
    NPROT_STRUCT_ASSERT(pOpenContext, oc);

    //
    //  Try to locate the IRP in the pended write queue. The send completion
    //  routine may be running and might have removed it from there.
    //
    NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);

    for (pIrpEntry = pOpenContext->PendedWrites.Flink;
         pIrpEntry != &pOpenContext->PendedWrites;
         pIrpEntry = pIrpEntry->Flink)
    {
        if (pIrp == CONTAINING_RECORD(pIrpEntry, IRP, Tail.Overlay.ListEntry))
        {
            pNetBufList = (PNET_BUFFER_LIST)pIrp->Tail.Overlay.DriverContext[1];
            
            //
            //  Place a reference on this packet so that it won't get
            //  freed/reused until we are done with it.
            //
            NPROT_REF_SEND_NBL(pNetBufList);            
            break;
        }
    }

    NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

    if (pNetBufList != NULL)    
    {
        //
        //  Either the send completion routine hasn't run, or we got a peak
        //  at the IRP/netbufferlist before it had a chance to take it out of the
        //  pending IRP queue.
        //
        //  We do not complete the IRP here - note that we didn't dequeue it
        //  above. This is because we always want the send complete routine to
        //  complete the IRP. And this in turn is because the NetBufferlist that was
        //  prepared from the IRP has a buffer chain pointing to data associated
        //  with this IRP. Therefore we cannot complete the IRP before the driver
        //  below us is done with the data it pointed to.
        //

        //
        //  Request NDIS to cancel this send. The result of this call is that
        //  our SendComplete handler will be called (if not already called).
        //
        DEBUGP(DL_INFO, ("CancelWrite: cancelling nbl %p on Open %p\n",
            pNetBufList, pOpenContext));
        
        NdisCancelSendNetBufferLists(
                pOpenContext->BindingHandle,
                NDIS_GET_NET_BUFFER_LIST_CANCEL_ID(pNetBufList));
        //
        //  It is now safe to remove the reference we had placed on the packet.
        //
        NPROT_DEREF_SEND_NBL(pNetBufList, FALSE);
    }
    //
    //  else the send completion routine has already picked up this IRP.
    //
}


VOID
NdisprotSendComplete(
    IN NDIS_HANDLE                  ProtocolBindingContext,
    IN PNET_BUFFER_LIST             pNetBufferList,
    IN BOOLEAN                      DispatchLevel
    )
/*++

Routine Description:

    NDIS entry point called to signify completion of a packet send.
    We pick up and complete the Write IRP corresponding to this packet.

Arguments:

    ProtocolBindingContext - pointer to open context
    pNetBufferList - NetBufferList that completed send
    DispatchLevel - A Boolean specifying if the caller is at DISPATCH level

Return Value:

    None

--*/
{
    PIRP                        pIrp;
    PIO_STACK_LOCATION          pIrpSp;
    PNDISPROT_OPEN_CONTEXT      pOpenContext;
    PNET_BUFFER_LIST            CurrNetBufferList = NULL;
    PNET_BUFFER_LIST            NextNetBufferList;
    NDIS_STATUS                 CompletionStatus;

    pOpenContext = (PNDISPROT_OPEN_CONTEXT)ProtocolBindingContext;
    NPROT_STRUCT_ASSERT(pOpenContext, oc);

    for (CurrNetBufferList = pNetBufferList;
            CurrNetBufferList != NULL;
            CurrNetBufferList = NextNetBufferList)
    {
        NextNetBufferList = NET_BUFFER_LIST_NEXT_NBL(CurrNetBufferList);
        
        pIrp = NPROT_IRP_FROM_SEND_NBL(CurrNetBufferList);

        IoSetCancelRoutine(pIrp, NULL);

        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, DispatchLevel);

        NPROT_REMOVE_ENTRY_LIST(&pIrp->Tail.Overlay.ListEntry);

        NPROT_RELEASE_LOCK(&pOpenContext->Lock, DispatchLevel);
        
        CompletionStatus = NET_BUFFER_LIST_COMPLETION_STATUS(CurrNetBufferList);
        
        
        //
        //  We are done with the NDIS_PACKET:
        //
        NPROT_DEREF_SEND_NBL(CurrNetBufferList, DispatchLevel);

        //
        //  Complete the Write IRP with the right status.
        //
        pIrpSp = IoGetCurrentIrpStackLocation(pIrp);
        if (CompletionStatus == NDIS_STATUS_SUCCESS)
        {
            pIrp->IoStatus.Information = pIrpSp->Parameters.Write.Length;
            pIrp->IoStatus.Status = STATUS_SUCCESS;
        }
        else
        {
            pIrp->IoStatus.Information = 0;
            pIrp->IoStatus.Status = STATUS_UNSUCCESSFUL;
        }

        DEBUGP(DL_INFO, ("SendComplete: NetBufferList %p/IRP %p/Length %d "
                        "completed with status %x\n",
                        CurrNetBufferList, pIrp, pIrp->IoStatus.Information, pIrp->IoStatus.Status));

        IoCompleteRequest(pIrp, IO_NO_INCREMENT);

        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, DispatchLevel);
        pOpenContext->PendedSendCount--;
        NPROT_RELEASE_LOCK(&pOpenContext->Lock, DispatchLevel);

        NPROT_DEREF_OPEN(pOpenContext); // send complete - dequeued send IRP
    }
    
}


