/*++

Copyright (c) 2000  Microsoft Corporation

Module Name:

    recv.c

Abstract:

    NDIS protocol entry points and utility routines to handle receiving
    data.

Environment:

    Kernel mode only.

Revision History:

    arvindm     4/6/2000    Created

--*/

#include "precomp.h"

#define __FILENUMBER 'VCER'



NTSTATUS
NdisprotRead(
    IN PDEVICE_OBJECT       pDeviceObject,
    IN PIRP                 pIrp
    )
/*++

Routine Description:

    Dispatch routine to handle IRP_MJ_READ. 

Arguments:

    pDeviceObject - pointer to our device object
    pIrp - Pointer to request packet

Return Value:

    NT status code.

--*/
{
    PIO_STACK_LOCATION      pIrpSp;
    NTSTATUS                NtStatus;
    PNDISPROT_OPEN_CONTEXT   pOpenContext;

    UNREFERENCED_PARAMETER(pDeviceObject);

    pIrpSp = IoGetCurrentIrpStackLocation(pIrp);
    pOpenContext = pIrpSp->FileObject->FsContext;

    do
    {
        //
        // Validate!
        //
        if (pOpenContext == NULL)
        {
            DEBUGP(DL_FATAL, ("Read: NULL FsContext on FileObject %p\n",
                        pIrpSp->FileObject));
            NtStatus = STATUS_INVALID_HANDLE;
            break;
        }
            
        NPROT_STRUCT_ASSERT(pOpenContext, oc);

        if (pIrp->MdlAddress == NULL)
        {
            DEBUGP(DL_FATAL, ("Read: NULL MDL address on IRP %p\n", pIrp));
            NtStatus = STATUS_INVALID_PARAMETER;
            break;
        }

        //
        // Try to get a virtual address for the MDL.
        //
        if (MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority) == NULL)
        {
            DEBUGP(DL_FATAL, ("Read: MmGetSystemAddr failed for IRP %p, MDL %p\n",
                    pIrp, pIrp->MdlAddress));
            NtStatus = STATUS_INSUFFICIENT_RESOURCES;
            break;
        }
        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);

        if (!NPROT_TEST_FLAGS(pOpenContext->Flags, NPROTO_BIND_FLAGS, NPROTO_BIND_ACTIVE))
        {
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);
            NtStatus = STATUS_INVALID_HANDLE;
            break;
        }

        //
        //  Add this IRP to the list of pended Read IRPs
        //
        NPROT_INSERT_TAIL_LIST(&pOpenContext->PendedReads, &pIrp->Tail.Overlay.ListEntry);
        NPROT_REF_OPEN(pOpenContext);  // pended read IRP
        pOpenContext->PendedReadCount++;

        //
        //  Set up the IRP for possible cancellation.
        //
        pIrp->Tail.Overlay.DriverContext[0] = (PVOID)pOpenContext;
        IoMarkIrpPending(pIrp);
        IoSetCancelRoutine(pIrp, NdisprotCancelRead);

        NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

        NtStatus = STATUS_PENDING;

        //
        //  Run the service routine for reads.
        //
        ndisprotServiceReads(pOpenContext);

    }
    while (FALSE);

    if (NtStatus != STATUS_PENDING)
    {
        NPROT_ASSERT(NtStatus != STATUS_SUCCESS);
        pIrp->IoStatus.Information = 0;
        pIrp->IoStatus.Status = NtStatus;
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);
    }

    return (NtStatus);
}


VOID
NdisprotCancelRead(
    IN PDEVICE_OBJECT               pDeviceObject,
    IN PIRP                         pIrp
    )
/*++

Routine Description:

    Cancel a pending read IRP. We unlink the IRP from the open context
    queue and complete it.

Arguments:

    pDeviceObject - pointer to our device object
    pIrp - IRP to be cancelled

Return Value:

    None

--*/
{
    PNDISPROT_OPEN_CONTEXT       pOpenContext;
    PLIST_ENTRY                 pIrpEntry;
    BOOLEAN                     Found;

    UNREFERENCED_PARAMETER(pDeviceObject);

    IoReleaseCancelSpinLock(pIrp->CancelIrql);

    Found = FALSE;

    pOpenContext = (PNDISPROT_OPEN_CONTEXT) pIrp->Tail.Overlay.DriverContext[0];
    NPROT_STRUCT_ASSERT(pOpenContext, oc);

    NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);

    //
    //  Locate the IRP in the pended read queue and remove it if found.
    //
    for (pIrpEntry = pOpenContext->PendedReads.Flink;
         pIrpEntry != &pOpenContext->PendedReads;
         pIrpEntry = pIrpEntry->Flink)
    {
        if (pIrp == CONTAINING_RECORD(pIrpEntry, IRP, Tail.Overlay.ListEntry))
        {
            NPROT_REMOVE_ENTRY_LIST(&pIrp->Tail.Overlay.ListEntry);
            pOpenContext->PendedReadCount--;
            Found = TRUE;
            break;
        }
    }

    NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

    if (Found)
    {
        DEBUGP(DL_INFO, ("CancelRead: Open %p, IRP %p\n", pOpenContext, pIrp));
        pIrp->IoStatus.Status = STATUS_CANCELLED;
        pIrp->IoStatus.Information = 0;
        IoCompleteRequest(pIrp, IO_NO_INCREMENT);

        NPROT_DEREF_OPEN(pOpenContext); // Cancel removed pended Read
    }
}
        


VOID
ndisprotServiceReads(
    IN PNDISPROT_OPEN_CONTEXT        pOpenContext
    )
/*++

Routine Description:

    Utility routine to copy received data into user buffers and
    complete READ IRPs.

Arguments:

    pOpenContext - pointer to open context

Return Value:

    None

--*/
{
    PIRP                pIrp;
    PLIST_ENTRY         pIrpEntry;
    PNET_BUFFER_LIST    pRcvNetBufList;
    PLIST_ENTRY         pRcvNetBufListEntry;
    PUCHAR              pSrc, pDst;
    ULONG               BytesRemaining; // at pDst
    PNDIS_BUFFER        pNdisBuffer;
    ULONG               BytesAvailable;
    BOOLEAN             FoundPendingIrp;

    DEBUGP(DL_VERY_LOUD, ("ServiceReads: open %p/%x\n",
            pOpenContext, pOpenContext->Flags));

    NPROT_REF_OPEN(pOpenContext);  // temp ref - service reads

    NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);

    while (!NPROT_IS_LIST_EMPTY(&pOpenContext->PendedReads) &&
           !NPROT_IS_LIST_EMPTY(&pOpenContext->RecvNetBufListQueue))
    {
        FoundPendingIrp = FALSE;
        
        //
        //  Get the first pended Read IRP
        //
        pIrpEntry = pOpenContext->PendedReads.Flink;
        while (pIrpEntry != &pOpenContext->PendedReads)
        {
            pIrp = CONTAINING_RECORD(pIrpEntry, IRP, Tail.Overlay.ListEntry);

            //
            //  Check to see if it is being cancelled.
            //
            if (IoSetCancelRoutine(pIrp, NULL))
            {
                //
                //  It isn't being cancelled, and can't be cancelled henceforth.
                //
                NPROT_REMOVE_ENTRY_LIST(pIrpEntry);
                FoundPendingIrp = TRUE;
                break;
                
                //
                //  NOTE: we decrement PendedReadCount way below in the
                //  while loop, to avoid letting through a thread trying
                //  to unbind.
                //
            }
            else
            {
                //
                //  The IRP is being cancelled; let the cancel routine handle it.
                //
                DEBUGP(DL_INFO, ("ServiceReads: open %p, skipping cancelled IRP %p\n",
                        pOpenContext, pIrp));

                pIrpEntry = pIrpEntry->Flink;
            }
        }

        if (FoundPendingIrp == FALSE)
        {
            break;
        }
        //
        //  Get the first queued receive packet
        //
        pRcvNetBufListEntry = pOpenContext->RecvNetBufListQueue.Flink;
        NPROT_REMOVE_ENTRY_LIST(pRcvNetBufListEntry);

        pOpenContext->RecvNetBufListCount --;

        NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

        NPROT_DEREF_OPEN(pOpenContext);  // Service: dequeue rcv packet

        pRcvNetBufList = NPROT_RCV_NBL_FROM_LIST_ENTRY(pRcvNetBufListEntry);
        NPROT_RCV_NBL_FROM_LIST_ENTRY(pRcvNetBufListEntry) = NULL;

        //
        //  Copy as much data as possible from the receive packet to
        //  the IRP MDL.
        //
        pDst = MmGetSystemAddressForMdlSafe(pIrp->MdlAddress, NormalPagePriority);
        NPROT_ASSERT(pDst != NULL);  // since it was already mapped
        BytesRemaining = MmGetMdlByteCount(pIrp->MdlAddress);

        pNdisBuffer = pRcvNetBufList->FirstNetBuffer->MdlChain;

        //
        // Copy the data in the received packet into the buffer provided by the client.
        // If the length of the receive packet is greater than length of the given buffer, 
        // we just copy as many bytes as we can. Once the buffer is full, we just discard 
        // the rest of the data, and complete the IRP sucessfully even we only did a partial copy.
        // 

        while (BytesRemaining && (pNdisBuffer != NULL))
        {
            NdisQueryBufferSafe(pNdisBuffer, &pSrc, &BytesAvailable, NormalPagePriority);

            if (pSrc == NULL) 
            {
                DEBUGP(DL_FATAL,
                    ("ServiceReads: Open %p, QueryBuffer failed for buffer %p\n",
                            pOpenContext, pNdisBuffer));
                break;
            }

            if (BytesAvailable)
            {
                ULONG       BytesToCopy = MIN(BytesAvailable, BytesRemaining);

                NPROT_COPY_MEM(pDst, pSrc, BytesToCopy);
                BytesRemaining -= BytesToCopy;
                pDst += BytesToCopy;
            }

            NdisGetNextBuffer(pNdisBuffer, &pNdisBuffer);
        }

        //
        //  Complete the IRP.
        //
        pIrp->IoStatus.Status = STATUS_SUCCESS;
        pIrp->IoStatus.Information = MmGetMdlByteCount(pIrp->MdlAddress) - BytesRemaining;

        DEBUGP(DL_INFO, ("ServiceReads: Open %p, IRP %p completed with %d bytes\n",
            pOpenContext, pIrp, pIrp->IoStatus.Information));

        IoCompleteRequest(pIrp, IO_NO_INCREMENT);

        ndisprotFreeReceiveNetBufferList(pOpenContext, pRcvNetBufList,FALSE);
          

        NPROT_DEREF_OPEN(pOpenContext);    // took out pended Read

        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);
        pOpenContext->PendedReadCount--;

    }

    NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

    NPROT_DEREF_OPEN(pOpenContext);    // temp ref - service reads
}


VOID
NdisprotReceiveNetBufferLists(
    IN NDIS_HANDLE                  ProtocolBindingContext,
    IN PNET_BUFFER_LIST             pNetBufferLists,
    IN NDIS_STATUS                  Status,
    IN BOOLEAN                      DispatchLevel 
    )
/*++

Routine Description:

    Protocol entry point called by NDIS if the driver below
    uses NDIS 6 net buffer list indications.

    If the miniport allows us to hold on to this net buffer list, we
    use it as is, otherwise we make a copy.

Arguments:

    ProtocolBindingContext - pointer to open context
    pNetBufferLists - a list of the Net Buffer lists being indicated up.
    Status - Whether it is NDIS_STATUS_SUCCESS or NDIS_STATUS_RESOURCES.
    DispatchLevel - If the caller is at DISPATCH level

Return Value:

    NDIS_STATUS_SUCCESS - Protocol is dome with all the net buffer lists
    NDIS_STATUS_PENDING - Protocol will return the owership of the list of
                          of net buffer lists by calling NdisPReturnNetBufferList later.
    

--*/
{
    PNDISPROT_OPEN_CONTEXT   pOpenContext;
    PNDIS_BUFFER            pNdisBuffer;
    UINT                    BufferLength;
    PNDISPROT_ETH_HEADER     pEthHeader;
    PNET_BUFFER_LIST        pCopyNetBufList;
    PUCHAR                  pCopyBuf;
    UINT                    TotalLength;
    SIZE_T                  BytesCopied;
    INT                     RefCount = 0;
    PNET_BUFFER_LIST        pNetBufList;
    PNET_BUFFER_LIST        pNextNetBufList;
    PNET_BUFFER_LIST        pReturnNetBufList = NULL;
    PNET_BUFFER_LIST        pLastReturnNetBufList = NULL;
    NTSTATUS                NtStatus;
    BOOLEAN                 bAcceptedReceive;
    
    
    pOpenContext = (PNDISPROT_OPEN_CONTEXT)ProtocolBindingContext;
    NPROT_STRUCT_ASSERT(pOpenContext, oc);
    if ((pOpenContext->State == NdisprotPausing) 
        || (pOpenContext->State == NdisprotPaused))
    {
        NdisReturnNetBufferLists(pOpenContext->BindingHandle, pNetBufferLists, DispatchLevel);
        return;
    }
    
    pNetBufList = pNetBufferLists;

    while (pNetBufList != NULL)
    {
        pNextNetBufList = NET_BUFFER_LIST_NEXT_NBL (pNetBufList);

        NBL_CLEAR_PROT_RSVD_FLAG(pNetBufList, NBL_PROT_RSVD_FLAGS);
        bAcceptedReceive = FALSE;
        
        //
        // Get first MDL and data length in the list
        //
        pNdisBuffer = pNetBufList->FirstNetBuffer->MdlChain;
        TotalLength = pNetBufList->FirstNetBuffer->DataLength;

        NdisQueryBufferSafe(
            pNdisBuffer,
            &pEthHeader,
            &BufferLength,
            NormalPagePriority);

        if (pEthHeader == NULL)
        {
            //
            //  The system is low on resources. Set up to handle failure
            //  below.
            //
            BufferLength = 0;
        }

        do
        {
            if (BufferLength < sizeof(NDISPROT_ETH_HEADER))
            {
                DEBUGP(DL_WARN,
                    ("ReceiveNetBufferList: Open %p, runt nbl %p, first buffer length %d\n",
                        pOpenContext, pNetBufList, BufferLength));
               
                break;
            }

            //
            //  Check the EtherType. If the Ether type indicates presence of
            //  a tag, then the "real" Ether type is 4 bytes further down.
            //
            if (pEthHeader->EthType == NPROT_8021P_TAG_TYPE)
            {
                USHORT UNALIGNED *pEthType;

                pEthType = (USHORT UNALIGNED *)((PUCHAR)&pEthHeader->EthType + 4);
    
                if (*pEthType != Globals.EthType)
                {
                    break;
                }
            }
            else if (pEthHeader->EthType != Globals.EthType)
            {
                break;
            }

            bAcceptedReceive = TRUE;
            DEBUGP(DL_LOUD, ("ReceiveNetBufferList: Open %p, interesting nbl %p\n",
                        pOpenContext, pNetBufList));

            //
            //  If the miniport is out of resources, we can't queue
            //  this list of net buffer list - make a copy if this is so.
            //
            if (Status == NDIS_STATUS_RESOURCES) 
            {
                pCopyNetBufList = ndisprotAllocateReceiveNetBufferList(
                                pOpenContext,
                                TotalLength,
                                &pCopyBuf,
                                DispatchLevel
                                );
            
                if (pCopyNetBufList == NULL)
                {
                    DEBUGP(DL_FATAL, ("ReceiveNetBufferList: Open %p, failed to"
                        " alloc copy, %d bytes\n", pOpenContext, TotalLength));
                    break;
                }
                NBL_SET_PROT_RSVD_FLAG(pCopyNetBufList, NPROT_ALLOCATED_NBL);
                //
                // Copy the data to the new allocated NetBufferList
                // 
                NtStatus = ndisprotCopyMdlToMdl(
                        pNetBufList->FirstNetBuffer->MdlChain,
                        pNetBufList->FirstNetBuffer->DataOffset,
                        pCopyNetBufList->FirstNetBuffer->MdlChain,
                        0,
                        TotalLength,
                        &BytesCopied);

                if (NtStatus != STATUS_SUCCESS)
                {
                    DEBUGP(DL_FATAL, ("ReceiveNetBufferList: Open %p, failed to"
                        " copy the data, %d bytes\n", pOpenContext, TotalLength));
                    //
                    // Free the NetBufferList and memory allocate before
                    //
                    ndisprotFreeReceiveNetBufferList(pOpenContext,
                                                    pCopyNetBufList,
                                                    DispatchLevel);
                    break;   
                }

                NPROT_ASSERT(BytesCopied == TotalLength);
                pNetBufList = pCopyNetBufList;

            }
            //
            //  Queue this up and service any pending Read IRPs.
            //
            ndisprotQueueReceiveNetBufferList(pOpenContext, pNetBufList, DispatchLevel);

        }
        while (FALSE);

        //
        // Ndisprot is not interested this NetBufferList, and the NetBufferList is indicated
        // as NDIS_STATUS_SUCCESS, Ndisprot should return the NetBufferList immediately
        //
        if ((bAcceptedReceive == FALSE) && (Status == NDIS_STATUS_SUCCESS))
        {
            if (pReturnNetBufList == NULL)
            {
                pReturnNetBufList = pNetBufList;
            }
            else
            { 
                NET_BUFFER_LIST_NEXT_NBL(pLastReturnNetBufList) = pNetBufList;
            }
            pLastReturnNetBufList = pNetBufList;
            NET_BUFFER_LIST_NEXT_NBL(pNetBufList) = NULL;

        }
                
        pNetBufList = pNextNetBufList;
    } // end of the for loop

    //
    if (pReturnNetBufList != NULL)
    {
        NdisReturnNetBufferLists(pOpenContext->BindingHandle, pReturnNetBufList, DispatchLevel);
    }

}


VOID
ndisprotQueueReceiveNetBufferList(
    IN PNDISPROT_OPEN_CONTEXT        pOpenContext,
    IN PNET_BUFFER_LIST             pRcvNetBufList,
    IN BOOLEAN                      DispatchLevel
    )
/*++

Routine Description:

    Queue up a received net buffer list on the open context structure.
    If the queue size goes beyond a water mark, discard a Net Buffer list
    at the head of the queue.

    Finally, run the queue service routine.

Arguments:
    
    pOpenContext - pointer to open context
    pRcvPacket - the received packet

Return Value:

    None

--*/
{
    PLIST_ENTRY        pEnt;
    PLIST_ENTRY        pDiscardEnt;
    PNET_BUFFER_LIST   pDiscardNetBufList;
    NDIS_STATUS        Status;

    do
    {

        NPROT_REF_OPEN(pOpenContext);    // queued rcv net buffer list

        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, DispatchLevel);

        if ((pOpenContext->State == NdisprotPaused)
            || (pOpenContext->State == NdisprotPausing))
        {
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, DispatchLevel);

            ndisprotFreeReceiveNetBufferList(pOpenContext, pRcvNetBufList, DispatchLevel);
            break;
        }

        //
        //  Check if the binding is in the proper state to receive
        //  this net buffer list.
        //
        if (NPROT_TEST_FLAGS(pOpenContext->Flags, NPROTO_BIND_FLAGS, NPROTO_BIND_ACTIVE) &&
            (pOpenContext->PowerState == NetDeviceStateD0))
        {
            
            //
            // Queue the net buffer list
            // 
            pEnt = NPROT_RCV_NBL_TO_LIST_ENTRY(pRcvNetBufList);
            NPROT_INSERT_TAIL_LIST(&pOpenContext->RecvNetBufListQueue, pEnt);
            NPROT_RCV_NBL_FROM_LIST_ENTRY(pEnt) = pRcvNetBufList;
            pOpenContext->RecvNetBufListCount++;

            DEBUGP(DL_VERY_LOUD, ("QueueReceiveNetBufferList: open %p,"
                    " queued nbl %p, queue size %d\n",
                    pOpenContext, pRcvNetBufList, pOpenContext->RecvNetBufListCount));
            
        }
        else
        {
            //
            //  Received this net buffer list when the binding is going away.
            //  Drop this.
            //
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, DispatchLevel);

            ndisprotFreeReceiveNetBufferList(pOpenContext, pRcvNetBufList, DispatchLevel);

            NPROT_DEREF_OPEN(pOpenContext);  // dropped rcv packet - bad state
            break;
        }


        //
        //  Trim the queue if it has grown too big.
        //
        if (pOpenContext->RecvNetBufListCount > MAX_RECV_QUEUE_SIZE)
        {
            //
            //  Remove the head of the queue.
            //
            pDiscardEnt = pOpenContext->RecvNetBufListQueue.Flink;
            NPROT_REMOVE_ENTRY_LIST(pDiscardEnt);

            pOpenContext->RecvNetBufListCount --;

            NPROT_RELEASE_LOCK(&pOpenContext->Lock, DispatchLevel);

            pDiscardNetBufList = NPROT_RCV_NBL_FROM_LIST_ENTRY(pDiscardEnt);

            NPROT_RCV_NBL_FROM_LIST_ENTRY(pDiscardEnt) = NULL;

            ndisprotFreeReceiveNetBufferList(pOpenContext, pDiscardNetBufList, DispatchLevel);

            NPROT_DEREF_OPEN(pOpenContext);  // dropped rcv packet - queue too long

            DEBUGP(DL_INFO, ("QueueReceiveNetBufferList: open %p queue"
                    " too long, discarded  %p\n",
                    pOpenContext, pDiscardNetBufList));
        }
        else
        {
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, DispatchLevel);
        }

        //
        //  Run the receive queue service routine now.
        //
        ndisprotServiceReads(pOpenContext);
    }
    while (FALSE);
}


PNET_BUFFER_LIST
ndisprotAllocateReceiveNetBufferList(
    IN PNDISPROT_OPEN_CONTEXT        pOpenContext,
    IN UINT                         DataLength,
    OUT PUCHAR *                    ppDataBuffer,
    IN  BOOLEAN                     DispatchLevel
    )
/*++

Routine Description:

    Allocate resources to copy and queue a received net buffer list

Arguments:

    pOpenContext - pointer to open context for received packet
    DataLength - total length in bytes of the net buffer list's first net buffer
    ppDataBuffer - place to return pointer to allocated buffer

Return Value:

    Pointer to NDIS packet if successful, else NULL.

--*/
{
    PNET_BUFFER_LIST            pNetBufList;
    PNDIS_BUFFER                pNdisBuffer;
    PUCHAR                      pDataBuffer;
    NDIS_STATUS                 Status;

    pNetBufList = NULL;
    pNdisBuffer = NULL;
    pDataBuffer = NULL;

    do
    {
        NPROT_ALLOC_MEM(pDataBuffer, DataLength);

        if (pDataBuffer == NULL)
        {
            DEBUGP(DL_FATAL, ("AllocRcvNbl: open %p, failed to alloc"
                " data buffer %d bytes\n", pOpenContext, DataLength));
            break;
        }

        //
        //  Make this an NDIS buffer.
        //
        NdisAllocateBuffer(
            &Status,
            &pNdisBuffer,
            pOpenContext->RecvBufferPool,
            pDataBuffer,
            DataLength);
        
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DEBUGP(DL_FATAL, ("AllocateRcvNbl: open %p, failed to alloc"
                " NDIS buffer, %d bytes\n", pOpenContext, DataLength));
            break;
        }

        pNetBufList = NdisAllocateNetBufferAndNetBufferList(
                        pOpenContext->RecvNetBufferListPool,
                        0,                              // ContextSize
                        0,                              // ContextBackfill
                        pNdisBuffer,                    // MdlChain
                        0,                              // DataOffset
                        DataLength,                     // DataLength
                        DispatchLevel);

        if (pNetBufList == NULL)
        {
            DEBUGP(DL_FATAL, ("AllocateRcvNbl: open %p, failed to alloc"
                " Net Buffer List, %d bytes\n", pOpenContext, DataLength));
            break;
        }


        *ppDataBuffer = pDataBuffer;

    }
    while (FALSE);

    if (pNetBufList == NULL)
    {
        //
        //  Clean up
        //
        if (pNdisBuffer != NULL)
        {
            NdisFreeBuffer(pNdisBuffer);
        }

        if (pDataBuffer != NULL)
        {
            NPROT_FREE_MEM(pDataBuffer);
        }
    }

    return (pNetBufList);
}



VOID
ndisprotFreeReceiveNetBufferList(
    IN PNDISPROT_OPEN_CONTEXT        pOpenContext,
    IN PNET_BUFFER_LIST             pNetBufferList,
    IN BOOLEAN                      DispatchLevel
    )
/*++

Routine Description:

    Free up all resources associated with a received net buffer list. If this
    is a local copy, free the net buffer list to our receive pool, else return
    this to the miniport.

Arguments:
    
    pOpenContext - pointer to open context
    pNetBufferList - pointer to net buffer list to be freed.
    bFromQueue - The NetBufferList is from a queue or not

Return Value:

    None

--*/
{
    PNDIS_BUFFER        pNdisBuffer;
    UINT                TotalLength;
    UINT                BufferLength;
    PUCHAR              pCopyData;

        
    do
    {
        if (NBL_TEST_PROT_RSVD_FLAG(pNetBufferList, NPROT_ALLOCATED_NBL))
        {
            //
            //  This is a local copy.
            //
            
            pNdisBuffer = pNetBufferList->FirstNetBuffer->MdlChain;
            TotalLength = pNetBufferList->FirstNetBuffer->DataLength;

            NdisQueryBufferSafe(
                pNdisBuffer,
                (PVOID *)&pCopyData,
                &BufferLength,
                NormalPagePriority);
            NPROT_ASSERT(BufferLength == TotalLength);

            NPROT_ASSERT(pNdisBuffer != NULL);

            NPROT_ASSERT(pCopyData != NULL); // we would have allocated non-paged pool


            NdisFreeNetBufferList(pNetBufferList, DispatchLevel);

            NdisFreeBuffer(pNdisBuffer);

            NPROT_FREE_MEM(pCopyData);
            break;
        }
        //
        // The NetBufferList should be returned

        NET_BUFFER_LIST_NEXT_NBL(pNetBufferList) = NULL;

        NdisReturnNetBufferLists(pOpenContext->BindingHandle,
                                  pNetBufferList, 
                                  DispatchLevel);
    }
    while (FALSE);

}
        

VOID
ndisprotCancelPendingReads(
    IN PNDISPROT_OPEN_CONTEXT        pOpenContext
    )
/*++

Routine Description:

    Cancel any pending read IRPs queued on the given open.

Arguments:

    pOpenContext - pointer to open context

Return Value:

    None

--*/
{
    PIRP                pIrp;
    PLIST_ENTRY         pIrpEntry;

    NPROT_REF_OPEN(pOpenContext);  // temp ref - cancel reads

    NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);

    while (!NPROT_IS_LIST_EMPTY(&pOpenContext->PendedReads))
    {
        //
        //  Get the first pended Read IRP
        //
        pIrpEntry = pOpenContext->PendedReads.Flink;
        pIrp = CONTAINING_RECORD(pIrpEntry, IRP, Tail.Overlay.ListEntry);

        //
        //  Check to see if it is being cancelled.
        //
        if (IoSetCancelRoutine(pIrp, NULL))
        {
            //
            //  It isn't being cancelled, and can't be cancelled henceforth.
            //
            NPROT_REMOVE_ENTRY_LIST(pIrpEntry);

            NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

            //
            //  Complete the IRP.
            //
            pIrp->IoStatus.Status = STATUS_CANCELLED;
            pIrp->IoStatus.Information = 0;

            DEBUGP(DL_INFO, ("CancelPendingReads: Open %p, IRP %p cancelled\n",
                pOpenContext, pIrp));

            IoCompleteRequest(pIrp, IO_NO_INCREMENT);

            NPROT_DEREF_OPEN(pOpenContext);    // took out pended Read for cancelling

            NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);
            pOpenContext->PendedReadCount--;
        }
        else
        {
            //
            //  It is being cancelled, let the cancel routine handle it.
            //
            NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

            //
            //  Give the cancel routine some breathing space, otherwise
            //  we might end up examining the same (cancelled) IRP over
            //  and over again.
            //
            NPROT_SLEEP(1);

            NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);
        }
    }

    NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

    NPROT_DEREF_OPEN(pOpenContext);    // temp ref - cancel reads
}


VOID
ndisprotFlushReceiveQueue(
    IN PNDISPROT_OPEN_CONTEXT            pOpenContext
    )
/*++

Routine Description:

    Free any receive packets queued up on the specified open

Arguments:

    pOpenContext - pointer to open context

Return Value:

    None

--*/
{
    PLIST_ENTRY         pRcvNetBufListEntry;
    PNET_BUFFER_LIST    pRcvNetBufList;

    NPROT_REF_OPEN(pOpenContext);  // temp ref - flushRcvQueue

    NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);
    
    while (!NPROT_IS_LIST_EMPTY(&pOpenContext->RecvNetBufListQueue))
    {
        //
        //  Get the first queued receive packet
        //
        pRcvNetBufListEntry = pOpenContext->RecvNetBufListQueue.Flink;
        NPROT_REMOVE_ENTRY_LIST(pRcvNetBufListEntry);

        pOpenContext->RecvNetBufListCount--;

        NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

        pRcvNetBufList = NPROT_RCV_NBL_FROM_LIST_ENTRY(pRcvNetBufListEntry);
        NPROT_RCV_NBL_FROM_LIST_ENTRY(pRcvNetBufListEntry) = NULL; 

        DEBUGP(DL_LOUD, ("FlushReceiveQueue: open %p, nbl %p\n",
            pOpenContext, pRcvNetBufList));

        ndisprotFreeReceiveNetBufferList(pOpenContext, pRcvNetBufList, FALSE);

        NPROT_DEREF_OPEN(pOpenContext);    // took out pended Read

        NPROT_ACQUIRE_LOCK(&pOpenContext->Lock, FALSE);
    }

    NPROT_RELEASE_LOCK(&pOpenContext->Lock, FALSE);

    NPROT_DEREF_OPEN(pOpenContext);    // temp ref - flushRcvQueue
}



NTSTATUS
ndisprotCopyMdlToMdl(
    IN PMDL     SourceMdl,
    IN SIZE_T   SourceOffset,
    IN PMDL     TargetMdl,
    IN SIZE_T   TargetOffset,
    IN SIZE_T   BytesToCopy,
    OUT SIZE_T* BytesCopied
    )

/*++

Routine Description:

    This routine copies the contents of one MDL chain into another MDL chain.
    A maximum of BytesToCopy bytes will be copied.
    The actual number of bytes copied is returned in BytesCopied.

Arguments:

    SourceMdl - Supplies the source of the data to be copied.

    SourceOffset - Supplies the offset into the source from which to begin.

    TargetMdl - Supplies the target to which data should be copied.

    TargetOffset - Supplies the offset into the target at which to begin.

    BytesToCopy - Supplies the number of bytes to copy.

    BytesCopied - Returns the actual number of bytes copied.

Return Value:

    STATUS_SUCCESS - BytesCopied indicates the number of bytes successfully
        transferred.

    STATUS_INSUFFICIENT_RESOURCES - if one of the MDLs could not be mapped.

Caller IRQL: Must be running at IRQL <= DISPATCH_LEVEL.

--*/

{
    SIZE_T SourceByteCount, TargetByteCount, BytesRemaining, CopySize;
    PUCHAR SourceVa, TargetVa;

    //
    // Skip any offsets specified by the caller. Note that this also serves
    // to skip any zero-length MDLs at the front of the chains,
    // simplifying the logic below.
    //

    while (SourceMdl && SourceOffset >= MmGetMdlByteCount(SourceMdl))
    {
        SourceOffset -= MmGetMdlByteCount(SourceMdl);
        SourceMdl = SourceMdl->Next;
    }

    while (TargetMdl && TargetOffset >= MmGetMdlByteCount(TargetMdl))
    {
        TargetOffset -= MmGetMdlByteCount(TargetMdl);
        TargetMdl = TargetMdl->Next;
    }

    //
    // Determine whether any data transfer will actually occur and,
    // if so, enter the main transfer stage.
    //
    if (BytesToCopy && SourceMdl && TargetMdl) 
    {
        BytesRemaining = BytesToCopy;

        //
        // Compute the length for the first source MDL,
        // and obtain a virtual address for it.
        //

        SourceByteCount = MmGetMdlByteCount(SourceMdl) - SourceOffset;
        if (SourceByteCount > BytesRemaining) 
        {
            SourceByteCount = BytesRemaining;
        }

        SourceVa = MmGetSystemAddressForMdlSafe(SourceMdl, LowPagePriority);
        if (SourceVa == NULL) 
        {
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        SourceVa += SourceOffset;

        //
        // Compute the length for the first target MDL,
        // and obtain a virtual address for it.
        //

        TargetByteCount = MmGetMdlByteCount(TargetMdl) - TargetOffset;

        TargetVa = MmGetSystemAddressForMdlSafe(TargetMdl, LowPagePriority);
        if (TargetVa == NULL)
        {
            return STATUS_INSUFFICIENT_RESOURCES;
        }
        TargetVa += TargetOffset;

        //
        // Transfer data between the MDL chains until the data are exhausted
        // or the end of one of the MDL chains is encountered.
        //

        for (;;) 
        {

            //
            // Copy the current installment and return if done.
            // Otherwise, update the count of bytes remaining.
            //
            CopySize = min(TargetByteCount, SourceByteCount);
            RtlCopyMemory(TargetVa, SourceVa, CopySize);

            if (BytesRemaining == CopySize) 
            {
                *BytesCopied = BytesToCopy;
                return STATUS_SUCCESS;
            } 
            
            BytesRemaining -= CopySize;
            
            //
            // Advance to the next MDL in the target chain if necessary,
            // otherwise update our pointer into the current entry.
            //

            if (TargetByteCount == CopySize) 
            {

                do
                {
                    TargetMdl = TargetMdl->Next;
                    if (TargetMdl == NULL) 
                    {
                        *BytesCopied = BytesToCopy - BytesRemaining;
                        return STATUS_SUCCESS;
                    }
                    TargetByteCount = MmGetMdlByteCount(TargetMdl);
                } while(TargetByteCount == 0);

                TargetVa = MmGetSystemAddressForMdlSafe(TargetMdl,
                                                        LowPagePriority);
                if (TargetVa == NULL) 
                {
                    return STATUS_INSUFFICIENT_RESOURCES;
                }
            } 
            else 
            {
                TargetVa += CopySize;
                TargetByteCount -= CopySize;
            }

            //
            // Advance to the next MDL in the source chain if necessary,
            // otherwise update our pointer into the current entry.
            //
            if (SourceByteCount == CopySize) 
            {

                do 
                {
                    SourceMdl = SourceMdl->Next;
                    if (SourceMdl == NULL) 
                    {
                        *BytesCopied = BytesToCopy - BytesRemaining;
                        return STATUS_SUCCESS;
                    }
                    SourceByteCount = MmGetMdlByteCount(SourceMdl);
                } while(SourceByteCount == 0);

                if (SourceByteCount > BytesRemaining)
                {
                    SourceByteCount = BytesRemaining;
                }
                SourceVa = MmGetSystemAddressForMdlSafe(SourceMdl,
                                                        LowPagePriority);
                if (SourceVa == NULL) 
                {
                    return STATUS_INSUFFICIENT_RESOURCES;
                }
            } 
            else 
            {
                SourceVa += CopySize;
                SourceByteCount -= CopySize;
            }
        }
    }

    *BytesCopied = 0;
    return STATUS_SUCCESS;
}

