/*++

Copyright (c) 1999  Microsoft Corporation

Module Name:
    mp_nic.c

Abstract:
    This module contains miniport send/receive routines

Revision History:
    Who         When        What
    --------    --------    ----------------------------------------------
    DChen       11-01-99    created

Notes:

--*/

#include "precomp.h"

#if DBG
#define _FILENUMBER     'CINM'
#endif

__inline PNET_BUFFER_LIST 
MP_FREE_SEND_NET_BUFFER(
    IN  PMP_ADAPTER Adapter,
    IN  PMP_TCB     pMpTcb
    )
/*++
Routine Description:

    Recycle a MP_TCB and complete the packet if necessary
    Assumption: Send spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter
    pMpTcb      Pointer to MP_TCB        

Return Value:

    Return NULL if no NET_BUFFER_LIST is completed.
    Otherwise, return a pointer to a NET_BUFFER_LIST which has been completed.

--*/
{
    
    PNET_BUFFER         NetBuffer;
    PNDIS_BUFFER        CurrBuffer;
    PNET_BUFFER_LIST    NetBufferList;
    BOOLEAN             fWaitForMapping = FALSE;

    ASSERT(MP_TEST_FLAG(pMpTcb, fMP_TCB_IN_USE));

    fWaitForMapping = MP_TEST_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING);
    
    NetBuffer = pMpTcb->NetBuffer;
    NetBufferList = pMpTcb->NetBufferList;
    pMpTcb->NetBuffer = NULL;
    pMpTcb->Count = 0;

    if (NetBuffer && !fWaitForMapping)
    {
        //
        // Call ndis to free resouces allocated for a SG list
        //
        NdisDprReleaseSpinLock(&Adapter->SendLock);

        NdisMFreeNetBufferSGList(
                            Adapter->NdisMiniportDmaHandle,
                            pMpTcb->pSGList,
                            NetBuffer);
        NdisDprAcquireSpinLock(&Adapter->SendLock);
    }

    
    MP_CLEAR_FLAGS(pMpTcb);
    
    Adapter->CurrSendHead = Adapter->CurrSendHead->Next;
    Adapter->nBusySend--;
    ASSERT(Adapter->nBusySend >= 0);
    
    //
    // SendLock is hold
    //
    if (NetBufferList)
    {
        MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList)--;
        if (MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList) == 0)
        {
            DBGPRINT(MP_TRACE, ("Completing NetBufferList= "PTR_FORMAT"\n", NetBufferList));

            NET_BUFFER_LIST_NEXT_NBL(NetBufferList) = NULL;
            return NetBufferList;
        }
    }

    return NULL;
    
}

NDIS_STATUS
MiniportSendNetBufferList(
    IN  PMP_ADAPTER         Adapter,
    IN  PNET_BUFFER_LIST    NetBufferList,
    IN  BOOLEAN             bFromQueue
    )
/*++
Routine Description:

    Do the work to send a packet
    Assumption: Send spinlock has been acquired 

Arguments:

    Adapter             Pointer to our adapter
    NetBufferList       Pointer to the NetBufferList is going to send.
    bFromQueue          TRUE if it's taken from the send wait queue

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_PENDING         Put into the send wait queue
    NDIS_STATUS_HARD_ERRORS

    NOTE: SendLock is held, called at DISPATCH level
--*/
{
    NDIS_STATUS     Status = NDIS_STATUS_PENDING;
    NDIS_STATUS     SendStatus;
    PMP_TCB         pMpTcb = NULL;
    PMP_TXBUF       pMpTxBuf = NULL;
    ULONG           BytesCopied;
    PNET_BUFFER     NetBufferToSend;
    BOOLEAN         bSendNetBuffer = FALSE;
   
    DBGPRINT(MP_TRACE, ("--> MiniportSendNetBufferList, NetBufferList="PTR_FORMAT"\n", 
                            NetBufferList));
    
    SendStatus = NDIS_STATUS_SUCCESS;

    if (bFromQueue)
    {
        NetBufferToSend = MP_GET_NET_BUFFER_LIST_NEXT_SEND(NetBufferList);
        MP_GET_NET_BUFFER_LIST_NEXT_SEND(NetBufferList) = NULL;
    }
    else
    {
        NetBufferToSend = NET_BUFFER_LIST_FIRST_NB(NetBufferList);
    }
    for (;  NetBufferToSend != NULL;
            NetBufferToSend = NET_BUFFER_NEXT_NB(NetBufferToSend))
    {
        bSendNetBuffer = FALSE;

        //
        // If we run out of TCB
        // 
        if (!MP_TCB_RESOURCES_AVAIABLE(Adapter))
        {
            ASSERT(NetBufferToSend != NULL);
            //
            // Put NetBufferList into wait queue
            //
            MP_GET_NET_BUFFER_LIST_NEXT_SEND(NetBufferList) = NetBufferToSend;
            if (!bFromQueue)
            {
                InsertHeadQueue(&Adapter->SendWaitQueue,
                                MP_GET_NET_BUFFER_LIST_LINK(NetBufferList));
                Adapter->nWaitSend++;
                
            }
            //
            // The NetBufferList is already in the queue, we don't do anything
            //
            Adapter->SendingNetBufferList = NULL;
            Status = NDIS_STATUS_RESOURCES;
            break;
        }
        //
        // Get TCB
        //
        pMpTcb = Adapter->CurrSendTail;
        ASSERT(!MP_TEST_FLAG(pMpTcb, fMP_TCB_IN_USE));
        
        
        pMpTcb->Adapter = Adapter;
        pMpTcb->NetBuffer = NetBufferToSend;
        pMpTcb->NetBufferList = NetBufferList;
       
        {
            ASSERT(MP_TEST_FLAG(Adapter, fMP_ADAPTER_SCATTER_GATHER));
            //
            // NOTE: net Buffer has to use new DMA APIs
            // 
            //
            // The function is called at DISPATCH level
            //
            MP_SET_FLAG(pMpTcb, fMP_TCB_IN_USE);
            MP_SET_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING);
            
            
            MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);

            SendStatus = NdisMAllocateNetBufferSGList(
                            Adapter->NdisMiniportDmaHandle,
                            NetBufferToSend,
                            pMpTcb,
                            pMpTcb->ScatterGatherListBuffer,
                            Adapter->ScatterGatherListSize);

            MP_ACQUIRE_SPIN_LOCK(&Adapter->SendLock, TRUE);            
            
            if (NDIS_STATUS_SUCCESS != SendStatus)
            {
                DBGPRINT(MP_WARN, ("NetBuffer can't be mapped, NetBuffer= "PTR_FORMAT"\n", NetBufferToSend));

                MP_CLEAR_FLAGS(pMpTcb);
                pMpTcb->NetBuffer = NULL;
                pMpTcb->NetBufferList = NULL;
                // 
                // We should fail the entire NET_BUFFER_LIST because the system 
                // cannot map the NET_BUFFER
                //
                NET_BUFFER_LIST_COMPLETION_STATUS(NetBufferList) = NDIS_STATUS_RESOURCES;
                
                for (; NetBufferToSend != NULL;
                       NetBufferToSend = NET_BUFFER_NEXT_NB(NetBufferToSend))
                {
                    MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList)--;
                }
                       
                break;
 
            }
        }

        Adapter->nBusySend++;
        ASSERT(Adapter->nBusySend <= Adapter->NumTcb);
        Adapter->CurrSendTail = Adapter->CurrSendTail->Next;

    }
    //
    // All the NetBuffers in the NetBufferList has been processed,
    // If the NetBufferList is in queue now, dequeue it.
    //
    if (NetBufferToSend == NULL)
    {
        if (bFromQueue)
        {
            RemoveHeadQueue(&Adapter->SendWaitQueue);
            Adapter->nWaitSend--;
        }
        Adapter->SendingNetBufferList = NULL;
    }

    //
    // As far as the miniport knows, the NetBufferList has been sent out.
    // Complete the NetBufferList now
    //
    if (MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList) == 0)
    {
        
        MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);

        NET_BUFFER_LIST_NEXT_NBL(NetBufferList) = NULL;
        
        NdisMSendNetBufferListsComplete(
            MP_GET_ADAPTER_HANDLE(Adapter),
            NetBufferList,
            TRUE);   
        MP_ACQUIRE_SPIN_LOCK(&Adapter->SendLock, TRUE);
    } 
            
    DBGPRINT(MP_TRACE, ("<-- MiniportSendNetBufferList\n"));
    return Status;

}  
/*++
Routine Description:
    
   Copy data in a packet to the specified location 
    
Arguments:
    
    BytesToCopy          The number of bytes need to copy
    CurreentBuffer       The buffer to start to copy
    StartVa              The start address to copy the data to
    Offset               The start offset in the buffer to copy the data

Return Value:
 
    The number of bytes actually copied
  

--*/  

ULONG 
MpCopyNetBuffer(
    IN  PNET_BUFFER     NetBuffer, 
    IN  PMP_TXBUF       pMpTxBuf
    )
{
    ULONG          CurrLength;
    PUCHAR         pSrc;
    PUCHAR         pDest;
    ULONG          BytesCopied = 0;
    ULONG          Offset;
    PNDIS_BUFFER   CurrentBuffer;
    ULONG          DataLength;
    
    DBGPRINT(MP_TRACE, ("--> MpCopyNetBuffer\n"));
    
    pDest = pMpTxBuf->pBuffer;
    CurrentBuffer = NetBuffer->MdlChain;
    Offset = NetBuffer->DataOffset;
    DataLength = NetBuffer->DataLength;
    
    while (CurrentBuffer && DataLength > 0)
    {
        NdisQueryBufferSafe(CurrentBuffer, &pSrc, &CurrLength, NormalPagePriority);
        if (pSrc == NULL)
        {
            BytesCopied = 0;
            break;
        }
        // 
        //  Current buffer length is greater than the offset to the buffer
        //  
        if (CurrLength > Offset)
        { 
            pSrc += Offset;
            CurrLength -= Offset;

            if (CurrLength > DataLength)
            {
                CurrLength = DataLength;
            }
            DataLength -= CurrLength;
            NdisMoveMemory(pDest, pSrc, CurrLength);
            BytesCopied += CurrLength;

            pDest += CurrLength;
            Offset = 0;
        }
        else
        {
            Offset -= CurrLength;
        }
        NdisGetNextBuffer( CurrentBuffer, &CurrentBuffer);
    
    }
    if ((BytesCopied != 0) && (BytesCopied < NIC_MIN_PACKET_SIZE))
    {
        NdisZeroMemory(pDest, NIC_MIN_PACKET_SIZE - BytesCopied);
    }
    NdisAdjustBufferLength(pMpTxBuf->NdisBuffer, BytesCopied);
    NdisFlushBuffer(pMpTxBuf->NdisBuffer, TRUE);
    
    ASSERT(BytesCopied <= pMpTxBuf->BufferSize);
    DBGPRINT(MP_TRACE, ("<-- MpCopyNetBuffer\n"));
    return BytesCopied;
}


NDIS_STATUS 
NICSendNetBuffer(
    IN  PMP_ADAPTER     Adapter,
    IN  PMP_TCB         pMpTcb,
    IN  PMP_FRAG_LIST   pFragList
    )
/*++
Routine Description:

    NIC specific send handler
    Assumption: Send spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter
    pMpTcb      Pointer to MP_TCB
    pFragList   The pointer to the frag list to be filled

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRORS
NOTE: called with send lock held.    

--*/
{
    NDIS_STATUS  Status;
    ULONG        index;
    UCHAR        TbdCount = 0;
    PNET_BUFFER  NetBuffer;
    ULONG        DataOffset;

    PHW_TCB      pHwTcb = pMpTcb->HwTcb;
    PTBD_STRUC   pHwTbd = pMpTcb->HwTbd;

    DBGPRINT(MP_TRACE, ("--> NICSendNetBuffer\n"));
    NetBuffer = pMpTcb->NetBuffer;

    //
    // This one is using the local buffer
    //
    if (MP_TEST_FLAG(pMpTcb, fMP_TCB_USE_LOCAL_BUF))
    {
        for (index = 0; index < pFragList->NumberOfElements; index++)
        {
            if (pFragList->Elements[index].Length)
            {
                pHwTbd->TbdBufferAddress = NdisGetPhysicalAddressLow(pFragList->Elements[index].Address);        
                pHwTbd->TbdCount = pFragList->Elements[index].Length;
                pHwTbd++;                    
                TbdCount++;
            }
        }

    }
    else
    {
        //
        // NDIS starts creating SG list from CurrentMdl, the driver don't need to worry
        // about more data will be mapped because NDIS will only map the data to length of
        // (NetBuffer->DataLength + NetBuffer->CurrentMdlOffset).The driver only need to skip 
        // the offset.
        //
        DataOffset = (ULONG)(NetBuffer->CurrentMdlOffset); 
                
        for (index = 0; index < pFragList->NumberOfElements; index++)
        {
            
            if (pFragList->Elements[index].Length <= DataOffset)
            {
                //
                // skip SG elements that are not used to get to the beginning of the data
                //
                DataOffset -= pFragList->Elements[index].Length;
            }
            else
            {
                pHwTbd->TbdBufferAddress = NdisGetPhysicalAddressLow(pFragList->Elements[index].Address) + DataOffset;        
                pHwTbd->TbdCount = pFragList->Elements[index].Length - DataOffset;
                pHwTbd++;                    
                TbdCount++;
                index++;
                break;
            }
        }

        for (; index < pFragList->NumberOfElements; index++)
        {
            if (pFragList->Elements[index].Length)
            {
                pHwTbd->TbdBufferAddress = NdisGetPhysicalAddressLow(pFragList->Elements[index].Address);        
                pHwTbd->TbdCount = pFragList->Elements[index].Length;
                pHwTbd++;                    
                TbdCount++;
                if (TbdCount > 8)
                {
                    ASSERT(FALSE);
                }
            }
        }                
        
    }

    pHwTcb->TxCbHeader.CbStatus = 0;
    pHwTcb->TxCbHeader.CbCommand = CB_S_BIT | CB_TRANSMIT | CB_TX_SF_BIT;

    pHwTcb->TxCbTbdPointer = pMpTcb->HwTbdPhys;
    pHwTcb->TxCbTbdNumber = TbdCount;
    pHwTcb->TxCbCount = 0;
    pHwTcb->TxCbThreshold = (UCHAR) Adapter->AiThreshold;

    Status = NICStartSend(Adapter, pMpTcb);

    DBGPRINT(MP_TRACE, ("<-- NICSendNetBuffer\n"));

    return Status;
}

NDIS_STATUS 
NICStartSend(
    IN  PMP_ADAPTER  Adapter,
    IN  PMP_TCB      pMpTcb
    )
/*++

Routine Description:

    Issue a send command to the NIC
    Assumption: Send spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter
    pMpTcb      Pointer to MP_TCB

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRORS

--*/
{
    NDIS_STATUS     Status;
    PMP_TCB         pPrevTcb = NULL;
    PMP_TCB         pNextTcb = NULL;
    PMP_TCB         pCurrTcb = NULL;

    DBGPRINT(MP_TRACE, ("--> NICStartSend\n"));

    //
    // If the transmit unit is idle (very first transmit) then we must
    // setup the general pointer and issue a full CU-start
    //
    do
    {
        if (Adapter->TransmitIdle)
        {
        
            DBGPRINT(MP_INFO,  ("CU is idle -- First TCB added to Active List\n"));

            //
            // Wait for the SCB to clear before we set the general pointer
            //
            if (!WaitScb(Adapter))
            {
                Status = NDIS_STATUS_HARD_ERRORS;
                break;
            }

            //
            // Don't try to start the transmitter if the command unit is not
            // idle ((not idle) == (Cu-Suspended or Cu-Active)).
            //
            if ((Adapter->CSRAddress->ScbStatus & SCB_CUS_MASK) != SCB_CUS_IDLE)
            {
                DBGPRINT(MP_ERROR, ("Adapter = "PTR_FORMAT", CU Not IDLE\n", Adapter));
                MP_SET_HARDWARE_ERROR(Adapter);
                NdisStallExecution(25);
            }
            pPrevTcb = pMpTcb->Prev;

            //
            // If any TCB in front of this one waiting for mapping, set the waiting
            // for mapping flag, and don't issue the send command.
            //
            if ((pMpTcb != Adapter->CurrSendHead)
                && (MP_TEST_FLAG(pPrevTcb, fMP_TCB_FLAGS_MAPPING)))
            {
                
                ASSERT(!MP_TEST_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING));
                MP_SET_FLAG(pMpTcb, fMP_TCB_PREV_WAIT_FOR_MAPPING);
                break;
            }
            
            //
            // If current one is waiting for mapping to be completed(use SG APIs), the previous
            // TCB should have finished the mapping, and walk through the TCB chain to find if 
            // there is any TCB behind the current one is waiting for this TCB to finish the
            // mapping. Then issue the send command.
            //
            if (MP_TEST_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING))
            {
                if (pMpTcb != Adapter->CurrSendHead)
                {
                    ASSERT(!MP_TEST_FLAG(pPrevTcb, fMP_TCB_FLAGS_MAPPING));
                }
                MP_CLEAR_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING);

                pNextTcb = pMpTcb->Next;
                while (MP_TEST_FLAG(pNextTcb, fMP_TCB_PREV_WAIT_FOR_MAPPING))
                {
                    ASSERT(!MP_TEST_FLAG(pNextTcb, fMP_TCB_WAIT_FOR_MAPPING));
                    MP_CLEAR_FLAG(pNextTcb, fMP_TCB_PREV_WAIT_FOR_MAPPING);
                
                    pNextTcb->PrevHwTcb->TxCbHeader.CbCommand &= ~CB_S_BIT;
                  
                    pNextTcb = pNextTcb->Next;
                }
            }
            //
            // If the current one is to send the small data frame, and no TCB in front of it
            // is waiting for to be mapped.
            // 
            Adapter->CSRAddress->ScbGeneralPointer = pMpTcb->HwTcbPhys;

            // ASSERT((pMpTcb->PrevHwTcb->TxCbHeader.CbCommand & CB_S_BIT) == 0)
            Status = D100IssueScbCommand(Adapter, SCB_CUC_START, FALSE);

            Adapter->TransmitIdle = FALSE;
            Adapter->ResumeWait = TRUE;
            break;
        }
        
        //
        // If the command unit has already been started, then append this
        // TCB onto the end of the transmit chain, and issue a CU-Resume.
        //
        DBGPRINT(MP_LOUD, ("adding TCB to Active chain\n"));
        
        pPrevTcb = pMpTcb->Prev;

        //
        // If any TCB in front of this one waiting for mapping, set the waiting
        // for mapping flag, and don't issue the send command.
        //
        if ((pMpTcb != Adapter->CurrSendHead)
                && (MP_TEST_FLAG(pPrevTcb, fMP_TCB_FLAGS_MAPPING)))
        {
            ASSERT(!MP_TEST_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING));
            MP_SET_FLAG(pMpTcb, fMP_TCB_PREV_WAIT_FOR_MAPPING); 
            break;
        }
        
        //
        // If current one is waiting for mapping to be completed, the previous
        // TCB should have finished the mapping
        //
        if (MP_TEST_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING))
        {
            if (pMpTcb != Adapter->CurrSendHead)
            {
                ASSERT(!MP_TEST_FLAG(pPrevTcb, fMP_TCB_FLAGS_MAPPING));
            }
            
            MP_CLEAR_FLAG(pMpTcb, fMP_TCB_WAIT_FOR_MAPPING);

            pNextTcb = pMpTcb->Next;
            while (MP_TEST_FLAG(pNextTcb, fMP_TCB_PREV_WAIT_FOR_MAPPING))
            {
                ASSERT(!MP_TEST_FLAG(pNextTcb, fMP_TCB_WAIT_FOR_MAPPING));
                MP_CLEAR_FLAG(pNextTcb, fMP_TCB_PREV_WAIT_FOR_MAPPING);
                
                pNextTcb->PrevHwTcb->TxCbHeader.CbCommand &= ~CB_S_BIT;
                
                pNextTcb = pNextTcb->Next;
            }
        }
        //
        // Issue the send command.
        //
        pMpTcb->PrevHwTcb->TxCbHeader.CbCommand &= ~CB_S_BIT;

        //
        // Issue a CU-Resume command to the device.  We only need to do a
        // WaitScb if the last command was NOT a RESUME.
        //
       //  ASSERT((pMpTcb->PrevHwTcb->TxCbHeader.CbCommand & CB_S_BIT) == 0)
        Status = D100IssueScbCommand(Adapter, SCB_CUC_RESUME, Adapter->ResumeWait);
    }
    while (FALSE);
                      
    DBGPRINT(MP_TRACE, ("<-- NICStartSend\n"));

    return Status;
}

NDIS_STATUS
MpHandleSendInterrupt(
    IN  PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    Interrupt handler for sending processing
    Re-claim the send resources, complete sends and get more to send from the send wait queue
    Assumption: Send spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRORS
    NDIS_STATUS_PENDING

--*/
{
    NDIS_STATUS         Status = NDIS_STATUS_SUCCESS;
    PMP_TCB             pMpTcb;
    PNET_BUFFER_LIST    NetBufferList;
    PNET_BUFFER_LIST    LastNetBufferList = NULL;
    PNET_BUFFER_LIST    CompleteNetBufferLists = NULL;

#if DBG
    LONG            i;
#endif

    DBGPRINT(MP_TRACE, ("---> MpHandleSendInterrupt\n"));

    //
    // Any packets being sent? Any packet waiting in the send queue?
    //
    if (Adapter->nBusySend == 0 &&
        IsQueueEmpty(&Adapter->SendWaitQueue))
    {
        ASSERT(Adapter->CurrSendHead == Adapter->CurrSendTail);
        DBGPRINT(MP_TRACE, ("<--- MpHandleSendInterrupt\n"));
        return Status;
    }

    //
    // Check the first TCB on the send list
    //
    while (Adapter->nBusySend > 0)
    {

#if DBG
        pMpTcb = Adapter->CurrSendHead;
        for (i = 0; i < Adapter->nBusySend; i++)
        {
            pMpTcb = pMpTcb->Next;   
        }

        if (pMpTcb != Adapter->CurrSendTail)
        {
            DBGPRINT(MP_ERROR, ("nBusySend= %d\n", Adapter->nBusySend));
            DBGPRINT(MP_ERROR, ("CurrSendhead= "PTR_FORMAT"\n", Adapter->CurrSendHead));
            DBGPRINT(MP_ERROR, ("CurrSendTail= "PTR_FORMAT"\n", Adapter->CurrSendTail));
            ASSERT(FALSE);
        }
#endif      

        pMpTcb = Adapter->CurrSendHead;

        //
        // Is this TCB completed?
        //
        if (pMpTcb->HwTcb->TxCbHeader.CbStatus & CB_STATUS_COMPLETE)
        {
            //
            // Check if this is a multicast hw workaround packet
            //
            if ((pMpTcb->HwTcb->TxCbHeader.CbCommand & CB_CMD_MASK) != CB_MULTICAST)
            {
                //
                // To change this to complete a list of NET_BUFFER_LIST
                //
                NetBufferList = MP_FREE_SEND_NET_BUFFER(Adapter, pMpTcb);
                //
                // One NetBufferList got complete
                //
                if (NetBufferList != NULL)
                {
                    if (CompleteNetBufferLists == NULL)
                    {
                        CompleteNetBufferLists = NetBufferList;
                    }
                    else
                    {
                        NET_BUFFER_LIST_NEXT_NBL(LastNetBufferList) = NetBufferList;
                    }
                    NET_BUFFER_LIST_NEXT_NBL(NetBufferList) = NULL;                    
                    LastNetBufferList = NetBufferList;
                }
                
            }
            else
            {
                //
                // Should we do something?
                //
            }
        }
        else
        {
            break;
        }
    }
    //
    // Complete the NET_BUFFER_LISTs 
    //
    if (CompleteNetBufferLists != NULL)
    {
        NDIS_HANDLE MiniportHandle = MP_GET_ADAPTER_HANDLE(Adapter);           
        NdisDprReleaseSpinLock(&Adapter->SendLock);
        
        NdisMSendNetBufferListsComplete(
                MiniportHandle ,
                CompleteNetBufferLists,
                TRUE);
        NdisDprAcquireSpinLock(&Adapter->SendLock);
        
    }

    //
    // If we queued any transmits because we didn't have any TCBs earlier,
    // dequeue and send those packets now, as long as we have free TCBs.
    //
    if (MP_IS_READY(Adapter))
    {
        while (!IsQueueEmpty(&Adapter->SendWaitQueue) &&
            (MP_TCB_RESOURCES_AVAIABLE(Adapter) &&
            Adapter->SendingNetBufferList == NULL))
            
        {
            PNDIS_PACKET Packet;
            PQUEUE_ENTRY pEntry; 
            
            //
            // We cannot remove it now, we just need to get the head
            //
            pEntry = GetHeadQueue(&Adapter->SendWaitQueue);
            ASSERT(pEntry);
            NetBufferList = MP_GET_NET_BUFFER_LIST_FROM_QUEUE_LINK (pEntry);

            DBGPRINT(MP_INFO, ("MpHandleSendInterrupt - send a queued NetBufferList\n"));
            
            ASSERT(Adapter->SendingNetBufferList == NULL);
            Adapter->SendingNetBufferList = NetBufferList;
            Status = MiniportSendNetBufferList(Adapter, NetBufferList, TRUE);
            //
            // If we failed to send
            // 
            if (Status != NDIS_STATUS_SUCCESS && Status != NDIS_STATUS_PENDING)
            {
                break;
            }
        }
    }

    DBGPRINT(MP_TRACE, ("<--- MpHandleSendInterrupt\n"));
    return Status;
}

BOOLEAN AllocateIoWorkItem = TRUE;
VOID
MPQueuedWorkItem(
    IN PVOID                        WorkItemContext
    );

VOID 
MpHandleRecvInterrupt(
    IN  PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    Interrupt handler for receive processing
    Put the received packets into an array and call NdisMIndicateReceivePacket
    If we run low on RFDs, allocate another one
    Assumption: Rcv spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    None
    
--*/
{
    PMP_RFD             pMpRfd;
    PHW_RFD             pHwRfd;

    PNET_BUFFER_LIST    FreeNetBufferList;
    UINT                NetBufferListCount;
    UINT                NetBufferListFreeCount;
    UINT                Index;
    UINT                LoopIndex = 0;
    UINT                LoopCount = NIC_MAX_RFDS / NIC_DEF_RFDS + 1;    // avoid staying here too long

    BOOLEAN             bContinue = TRUE;
    BOOLEAN             bAllocNewRfd = FALSE;
    USHORT              PacketStatus;
    NDIS_STATUS         Status = NDIS_STATUS_SUCCESS;
    PNET_BUFFER_LIST    NetBufferList = NULL; 
    PNET_BUFFER_LIST    PrevNetBufferList = NULL;
    PNET_BUFFER_LIST    PrevFreeNetBufferList = NULL;
    ULONG               PendingRecv;
    PNET_BUFFER         NetBuffer;
    LONG                Count;

    DBGPRINT(MP_TRACE, ("---> MpHandleRecvInterrupt\n"));
    //
    // If NDIS is pausing the miniport or miniport is paused
    // IGNORE the recvs
    // 
    if ((Adapter->AdapterState == NicPausing) ||
        (Adapter->AdapterState == NicPaused))
    {
        return;
    }

    //
    // add an extra receive ref just in case we indicte up with status resources
    //
    MP_INC_RCV_REF(Adapter);
    
    ASSERT(Adapter->nReadyRecv >= NIC_MIN_RFDS);
    
    while (LoopIndex++ < LoopCount && bContinue)
    {
        NetBufferListCount = 0;
        NetBufferListFreeCount = 0;

        NetBufferList = NULL;
        FreeNetBufferList = NULL;
        
        //
        // Process up to the array size RFD's
        //
        while (NetBufferListCount < NIC_DEF_RFDS)
        {
            if (IsListEmpty(&Adapter->RecvList))
            {
                ASSERT(Adapter->nReadyRecv == 0);
                bContinue = FALSE;  
                break;
            }

            //
            // Get the next MP_RFD to process
            //
            pMpRfd = (PMP_RFD)GetListHeadEntry(&Adapter->RecvList);

            //
            // Get the associated HW_RFD
            //
            pHwRfd = pMpRfd->HwRfd;
            
            //
            // Is this packet completed?
            //
            PacketStatus = NIC_RFD_GET_STATUS(pHwRfd);
            if (!NIC_RFD_STATUS_COMPLETED(PacketStatus))
            {
                bContinue = FALSE;
                break;
            }
            //
            // HW specific - check if actual count field has been updated
            //
            if (!NIC_RFD_VALID_ACTUALCOUNT(pHwRfd))
            {
                bContinue = FALSE;
                break;
            }
            //
            // Remove the RFD from the head of the List
            //
            RemoveEntryList((PLIST_ENTRY)pMpRfd);
            Adapter->nReadyRecv--;
            ASSERT(Adapter->nReadyRecv >= 0);
            
            ASSERT(MP_TEST_FLAG(pMpRfd, fMP_RFD_RECV_READY));
            MP_CLEAR_FLAG(pMpRfd, fMP_RFD_RECV_READY);

            //
            // A good frame? drop it if not.
            //
            if (!NIC_RFD_STATUS_SUCCESS(PacketStatus))
            {
                DBGPRINT(MP_WARN, ("Receive failure = %x\n", PacketStatus));
                NICReturnRFD(Adapter, pMpRfd);
                continue;
            }

            //
            // Do not receive any packets until a filter has been set
            //
            if (!Adapter->PacketFilter)
            {
                NICReturnRFD(Adapter, pMpRfd);
                continue;
            }

            //
            // Do not receive any packets until we are at D0
            //
            if (Adapter->CurrentPowerState != NdisDeviceStateD0)
            {
                NICReturnRFD(Adapter, pMpRfd);
                continue;
            }

            //
            // Get the packet size
            //
            pMpRfd->PacketSize = NIC_RFD_GET_PACKET_SIZE(pHwRfd);
            
            NetBuffer = NET_BUFFER_LIST_FIRST_NB(pMpRfd->NetBufferList);
            //
            // During the call NdisAllocateNetBufferAndNetBufferList to allocate the NET_BUFFER_LIST, NDIS already
            // initializes DataOffset, CurrentMdl and CurrentMdlOffset, here the driver needs to update DataLength
            // in the NET_BUFFER to reflect the received frame size.
            // 
            NET_BUFFER_DATA_LENGTH(NetBuffer) = pMpRfd->PacketSize;
            NdisAdjustBufferLength(pMpRfd->NdisBuffer, pMpRfd->PacketSize);
            NdisFlushBuffer(pMpRfd->NdisBuffer, FALSE);


            //
            // set the status on the packet, either resources or success
            //
            if (Adapter->nReadyRecv >= MIN_NUM_RFD)
            {
                //
                // NDIS_STATUS_SUCCESS
                // 
                Status = NDIS_STATUS_SUCCESS;
                
                MP_SET_FLAG(pMpRfd, fMP_RFD_RECV_PEND);
                
                InsertTailList(&Adapter->RecvPendList, (PLIST_ENTRY)pMpRfd);
                MP_INC_RCV_REF(Adapter);
                if (NetBufferList == NULL)
                {
                    NetBufferList = pMpRfd->NetBufferList;
                }
                else
                {
                    NET_BUFFER_LIST_NEXT_NBL(PrevNetBufferList) = pMpRfd->NetBufferList;
                }
                NET_BUFFER_LIST_NEXT_NBL(pMpRfd->NetBufferList) = NULL;
                pMpRfd->NetBufferList->Flags =  (pMpRfd->NetBufferList->Flags & 0x0fffffff);
                PrevNetBufferList = pMpRfd->NetBufferList;
            }
            else
            {
                //
                // NDIS_STATUS_RESOURCES
                //
                Status = NDIS_STATUS_RESOURCES;
                
                MP_SET_FLAG(pMpRfd, fMP_RFD_RESOURCES);

                if (FreeNetBufferList == NULL)
                {
                    FreeNetBufferList = pMpRfd->NetBufferList;
                }
                else
                {
                    NET_BUFFER_LIST_NEXT_NBL(PrevFreeNetBufferList) = pMpRfd->NetBufferList;
                }
                NET_BUFFER_LIST_NEXT_NBL(pMpRfd->NetBufferList) = NULL;                
                PrevFreeNetBufferList = pMpRfd->NetBufferList;
                pMpRfd->NetBufferList->Flags =  (pMpRfd->NetBufferList->Flags & 0x0fffffff);
                NetBufferListFreeCount++;
                //
                // Reset the RFD shrink count - don't attempt to shrink RFD
                //
                Adapter->RfdShrinkCount = 0;
                
                //
                // Remember to allocate a new RFD later
                //
                bAllocNewRfd = TRUE;
            }
            NetBufferListCount++;

        }

        //
        // if we didn't process any receives, just return from here
        //
        if (NetBufferListCount == 0) 
        {
            break;
        }
        //
        // Update the number of outstanding Recvs
        //
        Adapter->PoMgmt.OutstandingRecv += NetBufferListCount;

        NdisDprReleaseSpinLock(&Adapter->RcvLock);
        NdisDprAcquireSpinLock(&Adapter->Lock);
        //
        // if we have a Recv interrupt and have reported a media disconnect status
        // time to indicate the new status
        //
        if (MediaConnectStateConnected != Adapter->MediaState)
        {
            DBGPRINT(MP_WARN, ("Media state changed to Connected\n"));

            MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_NO_CABLE);

            Adapter->MediaState = MediaConnectStateConnected;

            MPIndicateLinkState(Adapter);
        }

        NdisDprReleaseSpinLock(&Adapter->Lock);

        
        if (NetBufferList != NULL)
        {

            NdisMIndicateReceiveNetBufferLists(
                    MP_GET_ADAPTER_HANDLE(Adapter),
                    NetBufferList,          
                    NDIS_STATUS_SUCCESS,
                    TRUE);                   // run at DISPATCH level
            
        }
        
        if (FreeNetBufferList != NULL)
        {
            NdisMIndicateReceiveNetBufferLists(
                    MP_GET_ADAPTER_HANDLE(Adapter),
                    FreeNetBufferList,          
                    NDIS_STATUS_RESOURCES,
                    TRUE);                   // run at DISPATCH level
        }
        
        NdisDprAcquireSpinLock(&Adapter->RcvLock);

        //
        // NDIS won't take ownership for the packets with NDIS_STATUS_RESOURCES.
        // For other packets, NDIS always takes the ownership and gives them back 
        // by calling MPReturnPackets
        //
           
        for (; FreeNetBufferList != NULL; FreeNetBufferList = NET_BUFFER_LIST_NEXT_NBL(FreeNetBufferList))
        {

            //
            // Get the MP_RFD saved in this packet, in NICAllocRfd
            //
            pMpRfd = MP_GET_NET_BUFFER_LIST_RFD(FreeNetBufferList);
            
            ASSERT(MP_TEST_FLAG(pMpRfd, fMP_RFD_RESOURCES));
            MP_CLEAR_FLAG(pMpRfd, fMP_RFD_RESOURCES);

            //
            // Decrement the number of outstanding Recvs
            //
            Adapter->PoMgmt.OutstandingRecv--;
            NICReturnRFD(Adapter, pMpRfd);
        }

        //
        // If we have set power pending, then complete it
        //
        if (((Adapter->PendingRequest)
                && ((Adapter->PendingRequest->RequestType == NdisRequestSetInformation)
                && (Adapter->PendingRequest->DATA.SET_INFORMATION.Oid == OID_PNP_SET_POWER)))
                && (Adapter->PoMgmt.OutstandingRecv == 0))
        {
            MpSetPowerLowComplete(Adapter);
        }
        
    }

    if (AllocateIoWorkItem)
    {
        NDIS_HANDLE NdisIoWorkItemHandle = NULL;
        //
        // demonstrate allocating an NDIS IO workitem
        //

        NdisIoWorkItemHandle = NdisAllocateIoWorkItem(Adapter->AdapterHandle);
        ASSERT(NdisIoWorkItemHandle != NULL);
            
        if (NdisIoWorkItemHandle)
        {
            NdisQueueIoWorkItem(NdisIoWorkItemHandle,
                                MPQueuedWorkItem,
                                NdisIoWorkItemHandle);
            
        }
        AllocateIoWorkItem = FALSE;
    }
    
    //
    // If we ran low on RFD's, we need to allocate a new RFD
    //
    if (bAllocNewRfd)
    {
        //
        // Allocate one more RFD only if no pending new RFD allocation AND
        // it doesn't exceed the max RFD limit
        //
        if (!Adapter->bAllocNewRfd && Adapter->CurrNumRfd < Adapter->MaxNumRfd)
        {
            PMP_RFD TempMpRfd;
            NDIS_STATUS TempStatus;

            TempMpRfd = NdisAllocateFromNPagedLookasideList(&Adapter->RecvLookaside);
            if (TempMpRfd)
            {
                MP_INC_REF(Adapter);
                Adapter->bAllocNewRfd = TRUE;

                MP_SET_FLAG(TempMpRfd, fMP_RFD_ALLOC_PEND); 

                //
                // Allocate the shared memory for this RFD.
                //
                TempStatus = NdisMAllocateSharedMemoryAsyncEx(
                                 Adapter->NdisMiniportDmaHandle,
                                 Adapter->HwRfdSize,
                                 FALSE,
                                 TempMpRfd);

                //
                // The return value is not NDIS_STATUS_PENDING, and Allocation failed
                //
                if (TempStatus != NDIS_STATUS_PENDING)
                {
                    MP_CLEAR_FLAGS(TempMpRfd);
                    NdisFreeToNPagedLookasideList(&Adapter->RecvLookaside, TempMpRfd);

                    Adapter->bAllocNewRfd = FALSE;
                    MP_DEC_REF(Adapter);
                }
            }
        }
    }

    //
    // get rid of the extra receive ref count we added at the beginning of this
    // function and check to see if we need to complete the pause.
    // Note that we don't have to worry about a blocked Halt here because
    // we are handling an interrupt DPC which means interrupt deregistertion is not
    // completed yet so even if our halt handler is running, NDIS will block the
    // interrupt deregisteration till we return back from this DPC.
    //
    
    MP_DEC_RCV_REF(Adapter);
        
    Count =  MP_GET_RCV_REF(Adapter);
    if ((Count == 0) && (Adapter->AdapterState == NicPausing))
    {
        //
        // If all the NetBufferLists are returned and miniport is pausing,
        // complete the pause
        // 
        
        Adapter->AdapterState = NicPaused;
        NdisDprReleaseSpinLock(&Adapter->RcvLock);
        NdisMPauseComplete(Adapter->AdapterHandle);
        NdisDprAcquireSpinLock(&Adapter->RcvLock);
    }
        
    ASSERT(Adapter->nReadyRecv >= NIC_MIN_RFDS);

    DBGPRINT(MP_TRACE, ("<--- MpHandleRecvInterrupt\n"));
}

VOID
MPQueuedWorkItem(
    IN PVOID                        WorkItemContext
    )
{
    DBGPRINT(MP_INFO,("MPQueuedWorkItem, WorkItemContext = %p\n", WorkItemContext));
    NdisFreeIoWorkItem((NDIS_HANDLE)WorkItemContext);
    
}

VOID 
NICReturnRFD(
    IN  PMP_ADAPTER  Adapter,
    IN  PMP_RFD		pMpRfd
    )
/*++
Routine Description:

    Recycle a RFD and put it back onto the receive list 
    Assumption: Rcv spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter
    pMpRfd      Pointer to the RFD 

Return Value:

    None
    
    NOTE: During return, we should check if we need to allocate new net buffer list
          for the RFD.
--*/
{
    PMP_RFD   pLastMpRfd;
    PHW_RFD   pHwRfd = pMpRfd->HwRfd;

    MP_SET_FLAG(pMpRfd, fMP_RFD_RECV_READY);
    
    //
    // HW_SPECIFIC_START
    //
    pHwRfd->RfdCbHeader.CbStatus = 0;
    pHwRfd->RfdActualCount = 0;
    pHwRfd->RfdCbHeader.CbCommand = (RFD_EL_BIT);
    pHwRfd->RfdCbHeader.CbLinkPointer = DRIVER_NULL;

    //
    // We don't use any of the OOB data besides status
    // Otherwise, we need to clean up OOB data
    // NdisZeroMemory(NDIS_OOB_DATA_FROM_PACKET(pMpRfd->NdisPacket),14);
    //
    // Append this RFD to the RFD chain
    if (!IsListEmpty(&Adapter->RecvList))
    {
        pLastMpRfd = (PMP_RFD)GetListTailEntry(&Adapter->RecvList);

        // Link it onto the end of the chain dynamically
        pHwRfd = pLastMpRfd->HwRfd;
        pHwRfd->RfdCbHeader.CbLinkPointer = pMpRfd->HwRfdPhys;
        pHwRfd->RfdCbHeader.CbCommand = 0;
    }

    //
    // HW_SPECIFIC_END
    //

    //
    // The processing on this RFD is done, so put it back on the tail of
    // our list
    //
    InsertTailList(&Adapter->RecvList, (PLIST_ENTRY)pMpRfd);
    Adapter->nReadyRecv++;
    ASSERT(Adapter->nReadyRecv <= Adapter->CurrNumRfd);
}

NDIS_STATUS 
NICStartRecv(
    IN  PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    Start the receive unit if it's not in a ready state                    
    Assumption: Rcv spinlock has been acquired 

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRROS
    
--*/
{
    PMP_RFD         pMpRfd;
    NDIS_STATUS     Status;

    DBGPRINT(MP_TRACE, ("---> NICStartRecv\n"));

    //
    // If the receiver is ready, then don't try to restart.
    //
    if (NIC_IS_RECV_READY(Adapter))
    {
        DBGPRINT(MP_LOUD, ("Receive unit already active\n"));
        return NDIS_STATUS_SUCCESS;
    }

    DBGPRINT(MP_LOUD, ("Re-start receive unit...\n"));
    ASSERT(!IsListEmpty(&Adapter->RecvList));
    
    //
    // Get the MP_RFD head
    //
    pMpRfd = (PMP_RFD)GetListHeadEntry(&Adapter->RecvList);

    //
    // If more packets are received, clean up RFD chain again
    //
    if (NIC_RFD_GET_STATUS(pMpRfd->HwRfd))
    {
        MpHandleRecvInterrupt(Adapter);
        ASSERT(!IsListEmpty(&Adapter->RecvList));

        //
        // Get the new MP_RFD head
        //
        pMpRfd = (PMP_RFD)GetListHeadEntry(&Adapter->RecvList);
    }

    //
    // Wait for the SCB to clear before we set the general pointer
    //
    if (!WaitScb(Adapter))
    {
        Status = NDIS_STATUS_HARD_ERRORS;
        MP_EXIT;
    }

    if (Adapter->CurrentPowerState > NdisDeviceStateD0)
    {
        Status = NDIS_STATUS_HARD_ERRORS;
        MP_EXIT;
    }
    //
    // Set the SCB General Pointer to point the current Rfd
    //
    Adapter->CSRAddress->ScbGeneralPointer = pMpRfd->HwRfdPhys;

    //
    // Issue the SCB RU start command
    //
    Status = D100IssueScbCommand(Adapter, SCB_RUC_START, FALSE);
    if (Status == NDIS_STATUS_SUCCESS)
    {
        // wait for the command to be accepted
        if (!WaitScb(Adapter))
        {
            Status = NDIS_STATUS_HARD_ERRORS;
        }
    }        
    
    exit:

    DBGPRINT_S(Status, ("<--- NICStartRecv, Status=%x\n", Status));
    return Status;
}

VOID 
MpFreeQueuedSendNetBufferLists(
    IN  PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    Free and complete the pended sends on SendWaitQueue
    Assumption: spinlock has been acquired 
    
Arguments:

    Adapter     Pointer to our adapter

Return Value:

     None
NOTE: Run at DPC     

--*/
{
    PQUEUE_ENTRY        pEntry;
    PNET_BUFFER_LIST    NetBufferList;
    PNET_BUFFER_LIST    NetBufferListToComplete = NULL;
    PNET_BUFFER_LIST    LastNetBufferList = NULL;
    NDIS_STATUS         Status = MP_GET_STATUS_FROM_FLAGS(Adapter);
    PNET_BUFFER         NetBuffer;

    DBGPRINT(MP_TRACE, ("--> MpFreeQueuedSendNetBufferLists\n"));

    while (!IsQueueEmpty(&Adapter->SendWaitQueue))
    {
        pEntry = RemoveHeadQueue(&Adapter->SendWaitQueue); 
        ASSERT(pEntry);
        
        Adapter->nWaitSend--;

        NetBufferList = MP_GET_NET_BUFFER_LIST_FROM_QUEUE_LINK(pEntry);

        NET_BUFFER_LIST_COMPLETION_STATUS(NetBufferList) = Status;
        //
        // The sendLock is held
        // 
        NetBuffer = MP_GET_NET_BUFFER_LIST_NEXT_SEND(NetBufferList);
        
        for (; NetBuffer != NULL; NetBuffer = NET_BUFFER_NEXT_NB(NetBuffer))
        {
            MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList)--;
        }
        //
        // If Ref count goes to 0, then complete it.
        // Otherwise, Send interrupt DPC would complete it later
        // 
        if (MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList) == 0)
        {
            if (NetBufferListToComplete == NULL)
            {
                NetBufferListToComplete = NetBufferList;
            }
            else
            {
                NET_BUFFER_LIST_NEXT_NBL(LastNetBufferList) = NetBufferList;
            }
            NET_BUFFER_LIST_NEXT_NBL(NetBufferList) = NULL;
            LastNetBufferList = NetBufferList;

        }
    }

    if (NetBufferListToComplete != NULL)
    {
        MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);
        NdisMSendNetBufferListsComplete(
               MP_GET_ADAPTER_HANDLE(Adapter),
               NetBufferListToComplete,
               TRUE);   

        MP_ACQUIRE_SPIN_LOCK(&Adapter->SendLock, TRUE);
    }
    
    DBGPRINT(MP_TRACE, ("<-- MpFreeQueuedSendNetBufferLists\n"));

}

void 
MpFreeBusySendNetBufferLists(
    IN  PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    Free and complete the stopped active sends
    Assumption: Send spinlock has been acquired 
    
Arguments:

    Adapter     Pointer to our adapter

Return Value:

     None

--*/
{
    PMP_TCB  pMpTcb;
    PNET_BUFFER_LIST   NetBufferList;
    PNET_BUFFER_LIST   CompleteNetBufferLists = NULL;
    PNET_BUFFER_LIST   LastNetBufferList = NULL;

    DBGPRINT(MP_TRACE, ("--> MpFreeBusySendNetBufferLists\n"));

    //
    // Any NET_BUFFER being sent? Check the first TCB on the send list
    //
    while (Adapter->nBusySend > 0)
    {
        pMpTcb = Adapter->CurrSendHead;

        //
        // Is this TCB completed?
        //
        if ((pMpTcb->HwTcb->TxCbHeader.CbCommand & CB_CMD_MASK) != CB_MULTICAST)
        {
            //
            // To change this to complete a list of NET_BUFFER_LISTs
            //
            NetBufferList = MP_FREE_SEND_NET_BUFFER(Adapter, pMpTcb);
            //
            // If one NET_BUFFER_LIST got complete
            //
            if (NetBufferList != NULL)
            {
                NET_BUFFER_LIST_COMPLETION_STATUS(NetBufferList) = NDIS_STATUS_REQUEST_ABORTED;
                if (CompleteNetBufferLists == NULL)
                {
                    CompleteNetBufferLists = NetBufferList;
                }
                else
                {
                    NET_BUFFER_LIST_NEXT_NBL(LastNetBufferList) = NetBufferList;
                }
                NET_BUFFER_LIST_NEXT_NBL(NetBufferList) = NULL;
                LastNetBufferList = NetBufferList;
            }
            
        }
        else
        {
            break;
        }
        
    }

    //
    // Complete the NET_BUFFER_LISTs
    //
    if (CompleteNetBufferLists != NULL)
    {
        NdisReleaseSpinLock(&Adapter->SendLock);
        NdisMSendNetBufferListsComplete(
           MP_GET_ADAPTER_HANDLE(Adapter),
           CompleteNetBufferLists,
           FALSE);       
        NdisAcquireSpinLock(&Adapter->SendLock);
    }

    DBGPRINT(MP_TRACE, ("<-- MpFreeBusySendNetBufferLists\n"));
}

VOID 
NICResetRecv(
    IN  PMP_ADAPTER   Adapter
    )
/*++
Routine Description:

    Reset the receive list                    
    Assumption: Rcv spinlock has been acquired 
    
Arguments:

    Adapter     Pointer to our adapter

Return Value:

     None

--*/
{
    PMP_RFD   pMpRfd;      
    PHW_RFD   pHwRfd;    
    LONG      RfdCount;

    DBGPRINT(MP_TRACE, ("--> NICResetRecv\n"));

    ASSERT(!IsListEmpty(&Adapter->RecvList));
    
    //
    // Get the MP_RFD head
    //
    pMpRfd = (PMP_RFD)GetListHeadEntry(&Adapter->RecvList);
    for (RfdCount = 0; RfdCount < Adapter->nReadyRecv; RfdCount++)
    {
        pHwRfd = pMpRfd->HwRfd;
        pHwRfd->RfdCbHeader.CbStatus = 0;

        pMpRfd = (PMP_RFD)GetListFLink(&pMpRfd->List);
    }

    DBGPRINT(MP_TRACE, ("<-- NICResetRecv\n"));
}

VOID 
MpLinkDetectionDpc(
    IN  PVOID	    SystemSpecific1,
    IN  PVOID	    FunctionContext,
    IN  PVOID	    SystemSpecific2, 
    IN  PVOID	    SystemSpecific3
    )
/*++

Routine Description:
    
    Timer function for postponed link negotiation
    
Arguments:

    SystemSpecific1     Not used
    FunctionContext     Pointer to our adapter
    SystemSpecific2     Not used
    SystemSpecific3     Not used

Return Value:

    None
    
--*/
{
    PMP_ADAPTER         Adapter = (PMP_ADAPTER)FunctionContext;
    NDIS_STATUS         Status = NDIS_STATUS_SUCCESS;
    NDIS_STATUS         IndicateStatus;
    PQUEUE_ENTRY        pEntry = NULL;
    PNDIS_OID_REQUEST   PendingRequest;
    NDIS_REQUEST_TYPE   RequestType;
    NDIS_OID            Oid;
    ULONG               PacketFilter;
    ULONG               LinkSpeed;
    ULONG               MediaState;
    

    UNREFERENCED_PARAMETER(SystemSpecific1);
    UNREFERENCED_PARAMETER(SystemSpecific2);
    UNREFERENCED_PARAMETER(SystemSpecific3);

    //
    // Handle the link negotiation.
    //
    if (Adapter->bLinkDetectionWait)
    {
        Status = ScanAndSetupPhy(Adapter);
    }
    else
    {
        Status = PhyDetect(Adapter);
    }
    
    if (Status == NDIS_STATUS_PENDING)
    {
        // Wait for 100 ms   
        Adapter->bLinkDetectionWait = TRUE;
        NdisMSetTimer(&Adapter->LinkDetectionTimer, NIC_LINK_DETECTION_DELAY);
        return;
    }

    //
    // NDIS 6.0 miniports are required to report their link speed, link state and
    // duplex state as soon as they figure it out. NDIS does not make any assumption
    // that they are connected, etc.
    //

    MediaState = NICGetMediaState(Adapter);
    NdisDprAcquireSpinLock(&Adapter->Lock);
    
    Adapter->MediaState = MediaState;
    DBGPRINT(MP_WARN, ("Media state changed to %s\n",
              ((MediaState == NdisMediaStateConnected)? 
              "Connected": "Disconnected")));

    MPIndicateLinkState(Adapter);

    //
    // Reset some variables for link detection
    //
    Adapter->bLinkDetectionWait = FALSE;
    
    DBGPRINT(MP_WARN, ("MpLinkDetectionDpc - negotiation done\n"));

    MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION);
    //
    // Any pending request?                                                        
    //
    if (Adapter->PendingRequest)
    {
        PendingRequest = Adapter->PendingRequest;
        Adapter->PendingRequest = NULL;

        RequestType = PendingRequest->RequestType;

        NdisDprReleaseSpinLock(&Adapter->Lock);

        switch(RequestType)
        {
            case NdisRequestQueryInformation:
            case NdisRequestQueryStatistics:
                Oid = PendingRequest->DATA.QUERY_INFORMATION.Oid;
                Status = NDIS_STATUS_SUCCESS;          
                switch (Oid)
                {
                    case OID_GEN_LINK_SPEED:
                        LinkSpeed = Adapter->usLinkSpeed * 10000;
                        NdisMoveMemory(PendingRequest->DATA.QUERY_INFORMATION.InformationBuffer,
                                        &LinkSpeed,
                                        sizeof(ULONG));

                        PendingRequest->DATA.QUERY_INFORMATION.BytesWritten = sizeof(ULONG);

                        break;

                    case OID_GEN_MEDIA_CONNECT_STATUS:
                    default:
                        ASSERT(PendingRequest->DATA.QUERY_INFORMATION.Oid == OID_GEN_MEDIA_CONNECT_STATUS);
                        NdisMoveMemory(PendingRequest->DATA.QUERY_INFORMATION.InformationBuffer,
                                        &MediaState,
                                        sizeof(ULONG));
                        NdisDprAcquireSpinLock(&Adapter->Lock);
                        if (Adapter->MediaState != MediaState)
                        {
                            Adapter->MediaState = MediaState;
                            DBGPRINT(MP_WARN, ("Media state changed to %s\n",
                                      ((MediaState == NdisMediaStateConnected)? 
                                      "Connected": "Disconnected")));
      
                        }
                        NdisDprReleaseSpinLock(&Adapter->Lock);
                        
                    PendingRequest->DATA.QUERY_INFORMATION.BytesWritten = sizeof(NDIS_MEDIA_STATE);
                    break;
                    
                }
                PendingRequest->DATA.QUERY_INFORMATION.BytesNeeded = 0;
                break;

            case NdisRequestSetInformation:
                //
                // It has to be set packet filter
                // 
                Oid = PendingRequest->DATA.QUERY_INFORMATION.Oid;
                if (Oid == OID_GEN_CURRENT_PACKET_FILTER)
                {
                    NdisMoveMemory(&PacketFilter,
                                     PendingRequest->DATA.SET_INFORMATION.InformationBuffer,
                                     sizeof(ULONG));

                    NdisDprAcquireSpinLock(&Adapter->Lock);
 
                    Status = NICSetPacketFilter(
                                 Adapter,
                                 PacketFilter);

                    NdisDprReleaseSpinLock(&Adapter->Lock);

                    if (Status == NDIS_STATUS_SUCCESS)
                    {
                        PendingRequest->DATA.SET_INFORMATION.BytesRead = sizeof(ULONG);
                        Adapter->PacketFilter = PacketFilter;
                
                    }
                    PendingRequest->DATA.QUERY_INFORMATION.BytesNeeded = 0;
                }
                break;
            
            case NdisRequestMethod:
                Status = MpMethodRequest (Adapter, PendingRequest);
                break;

            default:
                ASSERT(FALSE);
                break;
        } //end of outside switch
        if (Status != NDIS_STATUS_PENDING)
        {
            NdisMRequestComplete(Adapter->AdapterHandle, PendingRequest,Status);
        }

        NdisDprAcquireSpinLock(&Adapter->Lock);
    }

    //
    // Adapter->Lock is held
    //
    // Any pending reset?
    //
    if (Adapter->bResetPending)
    {
        //
        // The link detection may have held some requests and caused reset. 
        // Don't need to complete the reset, since the status is not SUCCESS.
        //
        Adapter->bResetPending = FALSE;
        MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS);

        NdisDprReleaseSpinLock(&Adapter->Lock);

        NdisMResetComplete(
            Adapter->AdapterHandle,     
            NDIS_STATUS_ADAPTER_NOT_READY,
            FALSE);
    }
    else
    {
        NdisDprReleaseSpinLock(&Adapter->Lock);
    }

    NdisDprAcquireSpinLock(&Adapter->RcvLock);

    //
    // Start the NIC receive unit                                                     
    //
    Status = NICStartRecv(Adapter);
    if (Status != NDIS_STATUS_SUCCESS)
    {
        MP_SET_HARDWARE_ERROR(Adapter);
    }
    
    NdisDprReleaseSpinLock(&Adapter->RcvLock);
    NdisDprAcquireSpinLock(&Adapter->SendLock);

    //
    // Send NET_BUFFER_LISTs which have been queued while link detection was going on. 
    //
    if (MP_IS_READY(Adapter))
    {
        while (!IsQueueEmpty(&Adapter->SendWaitQueue) &&
            (MP_TCB_RESOURCES_AVAIABLE(Adapter) &&
            Adapter->SendingNetBufferList == NULL))
        {
            PNET_BUFFER_LIST    NetBufferList;
                       
            pEntry = GetHeadQueue(&Adapter->SendWaitQueue); 
            ASSERT(pEntry);
            
            NetBufferList = MP_GET_NET_BUFFER_LIST_FROM_QUEUE_LINK(pEntry);

            DBGPRINT(MP_INFO, ("MpLinkDetectionDpc - send a queued NetBufferList\n"));

            Adapter->SendingNetBufferList = NetBufferList;
            
            Status = MiniportSendNetBufferList(Adapter, NetBufferList, TRUE);

            if (Status != NDIS_STATUS_SUCCESS && Status != NDIS_STATUS_PENDING)
            {
                break;
            }
        }   
    }

    MP_DEC_REF(Adapter);

    if (MP_GET_REF(Adapter) == 0)
    {
        NdisSetEvent(&Adapter->ExitEvent);
    }

    NdisDprReleaseSpinLock(&Adapter->SendLock);

}

VOID
MpProcessSGList(
    IN  PDEVICE_OBJECT          pDO,
    IN  PVOID                   pIrp,
    IN  PSCATTER_GATHER_LIST    pSGList,
    IN  PVOID                   Context
    )
/*++
Routine Description:

    Process  SG list for an NDIS packet or a NetBuffer by submitting the physical addresses
    in SG list to NIC's DMA engine and issuing command n hardware.
    
Arguments:

    pDO:  Ignore this parameter
    
    pIrp: Ignore this parameter
    
    pSGList: A pointer to Scatter Gather list built for the NDIS packet or NetBuffer passed
             to NdisMAllocNetBufferList. This is not necessarily
             the same ScatterGatherListBuffer passed to NdisMAllocNetBufferSGList
             
    Context: The context passed to NdisMAllocNetBufferList. Here is 
             a pointer to MP_TCB
             
Return Value:

     None

    NOTE: called at DISPATCH level
--*/
{
    PMP_TCB             pMpTcb = (PMP_TCB)Context;
    PMP_ADAPTER         Adapter = pMpTcb->Adapter;
    PMP_FRAG_LIST       pFragList = (PMP_FRAG_LIST)pSGList;
    NDIS_STATUS         Status;
    MP_FRAG_LIST        FragList;
    BOOLEAN             fSendComplete = FALSE;
    ULONG               BytesCopied;
    PNET_BUFFER_LIST    NetBufferList;
    
    DBGPRINT(MP_TRACE, ("--> MpProcessSGList\n"));

    MP_ACQUIRE_SPIN_LOCK(&Adapter->SendLock, TRUE);

    //
    // Save SG list that we got from NDIS. This is not necessarily the
    // same SG list buffer we passed to NdisMAllocNetBufferSGList
    //
    pMpTcb->pSGList = pSGList;

    
    if (!MP_TEST_FLAG(pMpTcb, fMP_TCB_IN_USE))
    {
        //
        // Before this callback function is called, reset happened and aborted
        // all the sends.
        // Call ndis to free resouces allocated for a SG list
        //
        MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);

        NdisMFreeNetBufferSGList(
                            Adapter->NdisMiniportDmaHandle,
                            pMpTcb->pSGList,
                            pMpTcb->NetBuffer);
        
    }
    else
    {
        if (pSGList->NumberOfElements > NIC_MAX_PHYS_BUF_COUNT)
        {
            //
            // the driver needs to do the local copy
            // 
            
            BytesCopied = MpCopyNetBuffer(pMpTcb->NetBuffer, pMpTcb->MpTxBuf);
                        
            //
            // MpCopyNetBuffer may return 0 if system resources are low or exhausted
            //
            if (BytesCopied == 0)
            {
                           
                DBGPRINT(MP_ERROR, ("Copy NetBuffer NDIS_STATUS_RESOURCES, NetBuffer= "PTR_FORMAT"\n", pMpTcb->NetBuffer));
                NetBufferList = pMpTcb->NetBufferList;
                NET_BUFFER_LIST_COMPLETION_STATUS(NetBufferList) = NDIS_STATUS_RESOURCES;
                
                MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList)--;
                
                if (MP_GET_NET_BUFFER_LIST_REF_COUNT(NetBufferList) == 0)
                {
                    fSendComplete = TRUE;
                }
               
                MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);
                NdisMFreeNetBufferSGList(
                    Adapter->NdisMiniportDmaHandle,
                    pMpTcb->pSGList,
                    pMpTcb->NetBuffer);

                if (fSendComplete)
                {

                    NET_BUFFER_LIST_NEXT_NBL(NetBufferList) = NULL;
        
                    NdisMSendNetBufferListsComplete(
                        MP_GET_ADAPTER_HANDLE(Adapter),
                        NetBufferList,
                        TRUE);   
                }
             
             }
             else
             {
                MP_SET_FLAG(pMpTcb, fMP_TCB_USE_LOCAL_BUF);
     
                //
                // Set up the frag list, only one fragment after it's coalesced
                //
                pFragList = &FragList;
                pFragList->NumberOfElements = 1;
                pFragList->Elements[0].Address = pMpTcb->MpTxBuf->BufferPa;
                pFragList->Elements[0].Length = (BytesCopied >= NIC_MIN_PACKET_SIZE) ?
                                                BytesCopied : NIC_MIN_PACKET_SIZE;
                
                Status = NICSendNetBuffer(Adapter, pMpTcb, pFragList);
                MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);
             }
        }
        else
        {
            Status = NICSendNetBuffer(Adapter, pMpTcb, pFragList);
            MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, TRUE);
        }
    }

    DBGPRINT(MP_TRACE, ("<-- MpProcessSGList\n"));
}

VOID
MPIndicateLinkState(
    IN  PMP_ADAPTER     Adapter
    )    
/*++
Routine Description:
    This routine sends a NDIS_STATUS_LINK_STATE status up to NDIS
    
Arguments:
    
    Adapter         Pointer to our adapter
    LockAcquired    Flag to indicate whether the miniport Lock has already been acquired or not
             
Return Value:

     None

    NOTE: called at DISPATCH level
--*/

{
    
    NDIS_LINK_STATE                LinkState;
    NDIS_STATUS_INDICATION         StatusIndication;
    
    LinkState.Header.Revision = NDIS_LINK_STATE_REVISION_1;
    LinkState.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
    LinkState.Header.Size = sizeof(NDIS_LINK_STATE);
    
    DBGPRINT(MP_WARN, ("Media state changed to %s\n",
              ((Adapter->MediaState == MediaConnectStateConnected)? 
              "Connected": "Disconnected")));


    if (Adapter->MediaState == MediaConnectStateConnected)
    {
        MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_NO_CABLE);
        
        if (Adapter->usDuplexMode == 1)
        {
            Adapter->MediaDuplexState = MediaDuplexStateHalf;
        }
        else if (Adapter->usDuplexMode == 2)
        {
            Adapter->MediaDuplexState = MediaDuplexStateFull;
        }
        else
        {
            Adapter->MediaDuplexState = MediaDuplexStateUnknown;
        }
        //
        // NDIS 6.0 miniports report xmit and recv link speeds in bps
        //
        Adapter->LinkSpeed = Adapter->usLinkSpeed * 1000000;
    }
    else
    {
        MP_SET_FLAG(Adapter, fMP_ADAPTER_NO_CABLE);
        Adapter->MediaState = MediaConnectStateDisconnected;
        Adapter->MediaDuplexState = MediaDuplexStateUnknown;
        Adapter->LinkSpeed = NDIS_LINK_SPEED_UNKNOWN;
    }

    LinkState.MediaConnectState = Adapter->MediaState;
    LinkState.MediaDuplexState = Adapter->MediaDuplexState;
    LinkState.XmitLinkSpeed = LinkState.RcvLinkSpeed = Adapter->LinkSpeed;
   
    NdisDprReleaseSpinLock(&Adapter->Lock);
    MP_INIT_NDIS_STATUS_INDICATION(&StatusIndication,
                                   Adapter->AdapterHandle,
                                   NDIS_STATUS_LINK_STATE,
                                   (PVOID)&LinkState,
                                   sizeof(LinkState));
                                   
    NdisMIndicateStatusEx(Adapter->AdapterHandle, &StatusIndication);
    NdisDprAcquireSpinLock(&Adapter->Lock);
    
    return;
}
