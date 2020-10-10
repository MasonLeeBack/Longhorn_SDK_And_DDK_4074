/*++

Copyright (c) 2003  Microsoft Corporation

Module Name:

    offload.c

Abstract:

    Implements Offload handlers.

Environment:

    Kernel mode

Revision History:

--*/

#include <precomp.h>

#pragma hdrstop

//
//  Define the module number for debugging code.
//
#define MODULE_NUMBER   MODULE_OFFLOAD

#define MAX_BLOCK_DEPTH 8
#define MuxOffloadTag 'lOMI'


PNDIS_TCP_OFFLOAD_EVENT_HANDLERS TcpOffloadEventHandlers;


//
// Type definition of the callback function.
//
typedef
NDIS_STATUS
(*POFFLOAD_PROCESS_BLOCK)(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

//
// Every NBL that is passed down to the offload target and which can be
// asynchronously completed, needs to have its SourceHandle saved upon call
// down and restored upon return. This structure is used for that purpose.
// N.B. The same holds for regular packet sends as well.
//
typedef struct _IM_NBL_ENTRY {
    NDIS_HANDLE PreviousSourceHandle;
    PVELAN pVElan;
} IM_NBL_ENTRY, *PIM_NBL_ENTRY;

//
// Enumerates the states an offload entry can be in.
//
typedef enum {
    ImOffloadOperationalState,
    ImOffloadResourceScarceState,
    ImOffloadStateCount
} IM_OFFLOAD_STATE;

//
// This is the state required to do the translation of the Handle/Context; 
// allocated for every offload state that passes through us.
//
// N.B. OffloadHandle MUST be the first parameter in this structure.
//
typedef struct _IM_OFFLOAD_ENTRY {
    NDIS_OFFLOAD_HANDLE OffloadHandle;
    PNDIS_OFFLOAD_HANDLE NdisOffloadHandle;
    LONG State;
} IM_OFFLOAD_ENTRY, *PIM_OFFLOAD_ENTRY;


//
// This tracks the SourceHandle in the root Offload Block that was passed down.
// When the same block is returned back by the offload target, the SourceHandle
// needs to be restored.
//
typedef struct _IM_CALL_ENTRY {
    union {
        LIST_ENTRY Link;
        PVOID PreviousImReserved[2];
    };

    PVOID PreviousSourceHandle;
    PVELAN pVElan;
    LONG State;
} IM_CALL_ENTRY, *PIM_CALL_ENTRY;


//
// We need to guarantee that state manipulation routines on offload state
// blocks always succeed. However, we do need to allocate IM_CALL_ENTRY to 
// make a call down. If such an allocation fails, we queue up the offload block
// and enter the ResourceScarce mode. While we are in this mode, any new initiate
// offload request is failed. When a previous outstanding offload request 
// completes, its IM_CALL_ENTRY is freed back to the look aside list, and the 
// next request is picked up for further processing. When this lookaside list
// becomes empty we exit the ResourceScarce mode.
//

typedef
VOID
(*PRS_RESUME_OFFLOAD_FUNCTION)(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

typedef struct _RS_MINIPORT_RESERVED {
    PRS_RESUME_OFFLOAD_FUNCTION Function;
    PVELAN pVELan;
} RS_MINIPORT_RESERVED, *PRS_MINIPORT_RESERVED;

#define RS_CALL_ENTRY_RESERVE_LIMIT 10

VOID RSCallback(PNDIS_WORK_ITEM WorkItem, PVOID Context);

NDIS_SPIN_LOCK RSSpinLock;
LIST_ENTRY RSBlockListHead;
LIST_ENTRY RSCallEntryList;
LONG RSBlockCount;
NDIS_WORK_ITEM RSWorkItem;
BOOLEAN RSWorkItemScheduled, RSCallEntryAvailable;



//
// Forward declarations.
//
NDIS_STATUS 
ReplaceSourceHandleInOffloadBlock(
    IN PVELAN pVElan,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock,
    IN PIM_CALL_ENTRY CallEntry
    );


//
// Resource-Scarce condition helper functions.
//

BOOLEAN
InResourceScarceState(
    IN PIM_OFFLOAD_ENTRY ImOffloadEntry
    )
{
    //
    // TODO: Replace this with the NDIS export routine.
    //
    if (InterlockedCompareExchange(&ImOffloadEntry->State,
            ImOffloadOperationalState, ImOffloadOperationalState) != 
            ImOffloadOperationalState) {
        return TRUE;
    } else {
        return FALSE;
    }        
}

VOID
SetResourceScarceState(
    IN PIM_OFFLOAD_ENTRY ImOffloadEntry
    )
{
    InterlockedCompareExchange(&ImOffloadEntry->State, 
        ImOffloadOperationalState, ImOffloadResourceScarceState);
}

BOOLEAN
RSProcessQueuedRequests()
{
    PIM_CALL_ENTRY CallEntry;
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST PopBlock;
    PRS_MINIPORT_RESERVED MiniportReserved;

    NdisAcquireSpinLock(&RSSpinLock);

    if (IsListEmpty(&RSBlockListHead) || IsListEmpty(&RSCallEntryList)) {
        NdisReleaseSpinLock(&RSSpinLock);
        return FALSE;
    }

    CallEntry = CONTAINING_RECORD(RemoveHeadList(&RSCallEntryList),
                    IM_CALL_ENTRY, Link);

    PopBlock = CONTAINING_RECORD(RemoveHeadList(&RSBlockListHead), 
                    NDIS_MINIPORT_OFFLOAD_BLOCK_LIST, Scratch);

    --RSBlockCount;
    NdisReleaseSpinLock(&RSSpinLock);

    MiniportReserved = (PRS_MINIPORT_RESERVED)PopBlock->MiniportReserved;
    ReplaceSourceHandleInOffloadBlock(MiniportReserved->pVELan, PopBlock, CallEntry);

    (MiniportReserved->Function)(MiniportReserved->pVELan->pAdapt->BindingHandle, 
                                 (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)PopBlock);

    return TRUE;
}

VOID 
RSCallback(PNDIS_WORK_ITEM WorkItem, PVOID Context)
{
    BOOLEAN ContinueProcessing;

    NdisAcquireSpinLock(&RSSpinLock);

Retry:
    RSCallEntryAvailable = FALSE;
    NdisReleaseSpinLock(&RSSpinLock);

    do {
        ContinueProcessing = RSProcessQueuedRequests();
    } while (ContinueProcessing);

    NdisAcquireSpinLock(&RSSpinLock);

    if (RSBlockCount != 0 && RSCallEntryAvailable) {
        goto Retry;
    }
    
    RSWorkItemScheduled = FALSE;
    NdisReleaseSpinLock(&RSSpinLock);
}


VOID
RSEnqueueOffloadBlock(
    IN PVELAN pVELan,
    IN PRS_RESUME_OFFLOAD_FUNCTION Function,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    )
{
    PRS_MINIPORT_RESERVED MiniportReserved;

    NdisAcquireSpinLock(&RSSpinLock);

    MiniportReserved = (PRS_MINIPORT_RESERVED)&OffloadBlockList->MiniportReserved;
    MiniportReserved->pVELan = pVELan;
    MiniportReserved->Function = Function;

    InitializeListHead((PLIST_ENTRY)&OffloadBlockList->Scratch);
    InsertTailList(&RSBlockListHead, (PLIST_ENTRY)&OffloadBlockList->Scratch);

    ++RSBlockCount;
    NdisReleaseSpinLock(&RSSpinLock);

    RSProcessQueuedRequests();
}


//
// Functions to replace and restore the SourceHandle in the root Offload block.
//
NDIS_STATUS
ReplaceSourceHandleInOffloadBlock(
    IN PVELAN pVElan,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock,
    IN PIM_CALL_ENTRY CallEntry
    )
{
    if (CallEntry == NULL) {
        NdisAllocateMemoryWithTag(&CallEntry, sizeof(*CallEntry), MuxOffloadTag);
        if (CallEntry == NULL) {
            return NDIS_STATUS_FAILURE;
        }
        CallEntry->State = ImOffloadOperationalState;
    } else {
        ASSERT(CallEntry->State == ImOffloadResourceScarceState);
    }

    CallEntry->PreviousSourceHandle = OffloadBlock->SourceHandle;
    CallEntry->PreviousImReserved[0] = OffloadBlock->ImReserved[0];
    CallEntry->PreviousImReserved[1] = OffloadBlock->ImReserved[1];
    CallEntry->pVElan = pVElan;
    OffloadBlock->ImReserved[0] = CallEntry;

    return NDIS_STATUS_SUCCESS;
}


PVELAN
RestoreSourceHandleInOffloadBlock(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PIM_CALL_ENTRY ImCallEntry = OffloadBlock->ImReserved[0];
    PVELAN pVElan;
    

    OffloadBlock->SourceHandle = ImCallEntry->PreviousSourceHandle;
    OffloadBlock->ImReserved[0] = ImCallEntry->PreviousImReserved[0];
    OffloadBlock->ImReserved[1] = ImCallEntry->PreviousImReserved[1];
    pVElan = ImCallEntry->pVElan;

    if (ImCallEntry->State == ImOffloadOperationalState) {
        NdisFreeMemory(ImCallEntry, sizeof(*ImCallEntry), 0);
    } else {
        ASSERT(ImCallEntry->State == ImOffloadResourceScarceState);
        NdisAcquireSpinLock(&RSSpinLock);

        InsertHeadList(&RSCallEntryList, &ImCallEntry->Link);
        RSCallEntryAvailable = TRUE;

        if (RSBlockCount != 0 &&  RSWorkItemScheduled == FALSE) {
            NdisScheduleWorkItem(&RSWorkItem);
            RSWorkItemScheduled = TRUE;
        }
        NdisReleaseSpinLock(&RSSpinLock);
    }
    
    return pVElan;
}


//
// Functions to replace and restore the SourceHandle in a NBL chain.
//
PVELAN
RestoreSourceHandleInNblChain(
    IN PNET_BUFFER_LIST NetBufferList,
    IN OUT PNET_BUFFER_LIST *NextNetBufferListHead
    )
{
    PNET_BUFFER_LIST PrevNbl, Nbl = NetBufferList;
    NDIS_STATUS Status;
    PVELAN pVElan = NULL;
    PIM_NBL_ENTRY ImNblEntry;

    while (Nbl != NULL && Nbl != *NextNetBufferListHead) {
        ImNblEntry = (PIM_NBL_ENTRY)NET_BUFFER_LIST_CONTEXT_DATA_START(Nbl);

        ASSERT(ImNblEntry->PreviousSourceHandle != NULL);
        ASSERT(ImNblEntry->pVElan != NULL);

        //
        // We scan the Nbls that are from the same protocol in each pass.
        //
        if (pVElan == NULL) {
            pVElan = ImNblEntry->pVElan;
        } else if (pVElan != ImNblEntry->pVElan) {
            ASSERT(PrevNbl != NULL);
            PrevNbl->Next = NULL;
            *NextNetBufferListHead = Nbl;
            return pVElan;
        }

        Nbl->SourceHandle = ImNblEntry->PreviousSourceHandle;

        NdisFreeNetBufferListContext(Nbl, sizeof(*ImNblEntry));

        PrevNbl = Nbl;
        Nbl = Nbl->Next;
    };

    if (Nbl == NULL) {
        *NextNetBufferListHead = NULL;
    }

    return pVElan;
}

NDIS_STATUS
ReplaceSourceHandleInNblChain(
    IN PVELAN pVElan,
    IN PNET_BUFFER_LIST NetBufferList
    )
{
    PNET_BUFFER_LIST Nbl = NetBufferList;
    NDIS_STATUS Status;
    PIM_NBL_ENTRY ImNblEntry;

    while (Nbl != NULL) {

        Status = NdisAllocateNetBufferListContext(Nbl,
                                                  sizeof(*ImNblEntry),
                                                  sizeof(*ImNblEntry),
                                                  MuxOffloadTag);

        if (Status != NDIS_STATUS_SUCCESS) {
            PNET_BUFFER_LIST NextNetBufferListHead = Nbl;
            //
            // Revert back all the changes we have made..
            //
            RestoreSourceHandleInNblChain(NetBufferList, &NextNetBufferListHead);
            return NDIS_STATUS_FAILURE;
        }
    
        ImNblEntry = (PIM_NBL_ENTRY)NET_BUFFER_LIST_CONTEXT_DATA_START(Nbl);
        ImNblEntry->PreviousSourceHandle = Nbl->SourceHandle;
        ImNblEntry->pVElan = pVElan;

        Nbl = Nbl->Next;
    }

    return NDIS_STATUS_SUCCESS;
}

VOID
SetStatusInNblChain(
    IN PNET_BUFFER_LIST NetBufferList,
    IN NDIS_STATUS Status
    )
{
    while (NetBufferList != NULL) {
        NetBufferList->Status = Status;
        NetBufferList = NetBufferList->Next;
    }
}


//
// Offload block traversal utility routines.
//
VOID
RestoreOffloadBlocks(
    PLIST_ENTRY ListHead
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;
    PNDIS_OFFLOAD_HANDLE OffloadHandle;

    while (!IsListEmpty(ListHead)) {
        PLIST_ENTRY Entry = RemoveHeadList(ListHead);

        ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)
            CONTAINING_RECORD(Entry, 
                              NDIS_MINIPORT_OFFLOAD_BLOCK_LIST, 
                              MiniportReserved);

        OffloadHandle = ProtocolOffloadBlock->OffloadHandle;
        ImEntry = CONTAINING_RECORD(ProtocolOffloadBlock->OffloadHandle, 
                                    IM_OFFLOAD_ENTRY,
                                    OffloadHandle);

        ProtocolOffloadBlock->OffloadHandle = ImEntry->NdisOffloadHandle;
        ProtocolOffloadBlock->OffloadHandle->MiniportOffloadContext = NULL;

        if (ProtocolOffloadBlock->NetBufferListChain != NULL) {
            PNET_BUFFER_LIST NextNetBufferListHead = NULL;
            RestoreSourceHandleInNblChain(
                ProtocolOffloadBlock->NetBufferListChain, 
                &NextNetBufferListHead);
        }

        NdisFreeMemory(ImEntry, sizeof(*ImEntry), MuxOffloadTag);
    }
}

VOID
PushNextOffloadBlock(
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock,
    PULONG StackTop,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST *StackBase
    )
{
    if (OffloadBlock->NextBlock != NULL) {
        StackBase[*StackTop] = OffloadBlock->NextBlock;
        *StackTop = *StackTop + 1;

        if (*StackTop >= 8) {
            ASSERT(0);
        }
    }
}

PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST
PopOffloadBlock(
    PULONG StackTop,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST *StackBase
    )
{
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock = NULL;

    if (*StackTop != 0) {
        *StackTop = *StackTop - 1;
        OffloadBlock = StackBase[*StackTop];
    }

    return OffloadBlock;
}


NDIS_STATUS
AdjustOffloadContext(
    PVELAN pVElan,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList,
    POFFLOAD_PROCESS_BLOCK ProcessFunction
    )
{
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST NextBlock[MAX_BLOCK_DEPTH];
    ULONG StackTop = 0;
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST Block = OffloadBlockList;
    NDIS_STATUS Status;
    LIST_ENTRY ModifiedBlockListHead;

    InitializeListHead(&ModifiedBlockListHead);

    while (Block != NULL) {
        while (Block != NULL) {
            PushNextOffloadBlock(Block, &StackTop, NextBlock);
            Status = ProcessFunction(pVElan, Block);

            if (Status == NDIS_STATUS_OFFLOAD_STATE_ALLOCATED) {
                InsertHeadList(&ModifiedBlockListHead, 
                               (PLIST_ENTRY)&Block->MiniportReserved[0]);
            } else if (Status == NDIS_STATUS_SUCCESS) {
                //
                // Continue processing...
                //
            } else {
                //
                // Restore the list back and return failures.
                // N.B. This can happen only during InitiateOffload()
                //
                RestoreOffloadBlocks(&ModifiedBlockListHead);
                return NDIS_STATUS_FAILURE;
            }   
            
            Block = Block->DependentBlockList;
        }
        Block = PopOffloadBlock(&StackTop, NextBlock);
    }

    return NDIS_STATUS_SUCCESS;
}

//
// Offload block processing routines.
//
NDIS_STATUS
ProcessOffloadBlockSetFailureStatus(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;

    ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;
    ProtocolOffloadBlock->Status = NDIS_STATUS_FAILURE;
    return NDIS_STATUS_SUCCESS;
}



NDIS_STATUS
ProcessOffloadBlockInitiateOffload(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;
    NDIS_STATUS Status = NDIS_STATUS_SUCCESS;

    if (OffloadBlock->NetBufferListChain != NULL) {
        Status = ReplaceSourceHandleInNblChain(pVElan, 
                        OffloadBlock->NetBufferListChain);

        if (Status != NDIS_STATUS_SUCCESS) {
            return Status;
        }
    }

    if (OffloadBlock->MiniportOffloadContext != NULL) {
        //
        // This could be a new block or a pointer to an already allocated
        // block.
        //
        if (*OffloadBlock->MiniportOffloadContext == NULL) {
            IM_OFFLOAD_STATE SetState;

            NdisAllocateMemoryWithTag(&ImEntry, sizeof(IM_OFFLOAD_ENTRY), 
                                      MuxOffloadTag);

            if (ImEntry == NULL) {
                if (OffloadBlock->NetBufferListChain != NULL) {
                    PNET_BUFFER_LIST NextNetBufferListHead = NULL;
                    RestoreSourceHandleInNblChain(OffloadBlock->NetBufferListChain, 
                        &NextNetBufferListHead);
                }
                return NDIS_STATUS_FAILURE;
            }

            NdisZeroMemory(ImEntry, sizeof(*ImEntry));
            ImEntry->NdisOffloadHandle = OffloadBlock->NdisOffloadHandle;
            ASSERT(ImEntry->State == ImOffloadOperationalState);
            Status = NDIS_STATUS_OFFLOAD_STATE_ALLOCATED;
        } else {
            ImEntry = (PIM_OFFLOAD_ENTRY)(*OffloadBlock->MiniportOffloadContext);
        }

        ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;
        ProtocolOffloadBlock->OffloadHandle = &ImEntry->OffloadHandle;
    }

    return Status;
}

NDIS_STATUS
ProcessOffloadBlockInitiateOffloadComplete(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;

    ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;

    if (ProtocolOffloadBlock->OffloadHandle != NULL) {
        ImEntry = CONTAINING_RECORD(ProtocolOffloadBlock->OffloadHandle, 
                                    IM_OFFLOAD_ENTRY,
                                    OffloadHandle);
        //
        // Fix up the offload handle appropriately..
        //
        ProtocolOffloadBlock->OffloadHandle = ImEntry->NdisOffloadHandle;

        if (NT_SUCCESS(ProtocolOffloadBlock->Status)) {
            ProtocolOffloadBlock->OffloadHandle->MiniportOffloadContext = ImEntry;
            //
            // $TODO: Uncomment this once the miniport is fixed.
            // ASSERT(ProtocolOffloadBlock->NetBufferListChain == NULL);
            //
        } else if (ImEntry->OffloadHandle.MiniportOffloadContext != NULL) {
            //
            // This block was already offloaded. So, no need to do anything 
            // here.
            //
            ASSERT(ProtocolOffloadBlock->OffloadHandle->MiniportOffloadContext == ImEntry);
            ASSERT(ProtocolOffloadBlock->NetBufferListChain == NULL);
        } else {
            //
            // There was some failure, free up resources..
            //
            ASSERT(ProtocolOffloadBlock->OffloadHandle->MiniportOffloadContext == NULL);
            NdisFreeMemory(ImEntry, sizeof(*ImEntry), MuxOffloadTag);
            if (ProtocolOffloadBlock->NetBufferListChain != NULL) {
                PNET_BUFFER_LIST NextNetBufferListHead = NULL;
                RestoreSourceHandleInNblChain(ProtocolOffloadBlock->NetBufferListChain, 
                                              &NextNetBufferListHead);
                ASSERT(NextNetBufferListHead == NULL);
            }
        }
    }

    return NDIS_STATUS_SUCCESS;
}


NDIS_STATUS
ProcessOffloadBlockExistingBlocks(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;

    ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;

    if (OffloadBlock->MiniportOffloadContext != NULL) {
        //
        // This could be a new block or a pointer to an already allocated
        // block.
        //
        ASSERT(*OffloadBlock->MiniportOffloadContext != NULL);

        ImEntry = (PIM_OFFLOAD_ENTRY)(*OffloadBlock->MiniportOffloadContext);

        ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;
        ProtocolOffloadBlock->OffloadHandle = &ImEntry->OffloadHandle;
    }

    ASSERT(ProtocolOffloadBlock->NetBufferListChain == NULL);
    return NDIS_STATUS_SUCCESS;
}


NDIS_STATUS
ProcessOffloadBlockExistingBlocksComplete(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;

    ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;

    if (ProtocolOffloadBlock->OffloadHandle != NULL) {

        ImEntry = CONTAINING_RECORD(ProtocolOffloadBlock->OffloadHandle, 
                                    IM_OFFLOAD_ENTRY,
                                    OffloadHandle);

        //
        // Fix up the offload handle appropriately..
        //
        ProtocolOffloadBlock->OffloadHandle = ImEntry->NdisOffloadHandle;
    }

    ASSERT(ProtocolOffloadBlock->NetBufferListChain == NULL);
    return NDIS_STATUS_SUCCESS;
}



NDIS_STATUS
ProcessOffloadBlockTerminateOffloadComplete(
    PVELAN pVElan,
    PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlock
    )
{
    PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST ProtocolOffloadBlock;
    PIM_OFFLOAD_ENTRY ImEntry;

    ProtocolOffloadBlock = (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlock;

    if (ProtocolOffloadBlock->OffloadHandle != NULL) {
        ImEntry = CONTAINING_RECORD(ProtocolOffloadBlock->OffloadHandle, 
                                    IM_OFFLOAD_ENTRY,
                                    OffloadHandle);
        //
        // Fix up the offload handle appropriately..
        //
        ProtocolOffloadBlock->OffloadHandle = ImEntry->NdisOffloadHandle;
        ProtocolOffloadBlock->OffloadHandle->MiniportOffloadContext = NULL;

        ASSERT(NT_SUCCESS(ProtocolOffloadBlock->Status));
        NdisFreeMemory(ImEntry, sizeof(*ImEntry), MuxOffloadTag);
    }

    if (ProtocolOffloadBlock->NetBufferListChain != NULL) {
        PNET_BUFFER_LIST NextNetBufferListHead = NULL;
        RestoreSourceHandleInNblChain(ProtocolOffloadBlock->NetBufferListChain, 
                                      &NextNetBufferListHead);
        ASSERT(NextNetBufferListHead == NULL);        
    }
    return NDIS_STATUS_SUCCESS;
}

//
// Requests used by protocol modules.
//
VOID
MPInitiateOffload(
    IN PVOID MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    )
{
    PVELAN pVElan = (PVELAN) MiniportAdapterContext;
    PADAPT pAdapt = pVElan->pAdapt;
    NDIS_STATUS Status;

    Status = ReplaceSourceHandleInOffloadBlock(pVElan, OffloadBlockList, NULL);

    if (Status != NDIS_STATUS_SUCCESS) {
        AdjustOffloadContext(pVElan, OffloadBlockList, 
                             ProcessOffloadBlockSetFailureStatus);
        NdisMInitiateOffloadComplete(pVElan->MiniportAdapterHandle, 
            (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
        return;
    }

    Status = AdjustOffloadContext(pVElan, OffloadBlockList, 
                                  ProcessOffloadBlockInitiateOffload);

    if (Status != NDIS_STATUS_SUCCESS) {
        AdjustOffloadContext(pVElan, OffloadBlockList, 
                             ProcessOffloadBlockSetFailureStatus);
        RestoreSourceHandleInOffloadBlock((PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlockList);
        NdisMInitiateOffloadComplete(pVElan->MiniportAdapterHandle, 
            (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
        return;
    }

    NdisInitiateOffload(pAdapt->BindingHandle, 
                        (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}


VOID
MPTerminateOffload(
    IN PVOID MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    )
{
    PVELAN pVElan = (PVELAN) MiniportAdapterContext;
    PADAPT pAdapt = pVElan->pAdapt;
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(pVElan, OffloadBlockList, 
                                  ProcessOffloadBlockExistingBlocks);
    ASSERT(Status == NDIS_STATUS_SUCCESS);

    Status = ReplaceSourceHandleInOffloadBlock(pVElan, OffloadBlockList, NULL);
    if (Status != NDIS_STATUS_SUCCESS) {
        RSEnqueueOffloadBlock(pVElan, NdisTerminateOffload, OffloadBlockList);
        return;
    }

    NdisTerminateOffload(pAdapt->BindingHandle, 
                         (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
MPUpdateOffload(
    IN PVOID MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    )
{
    PVELAN pVElan = (PVELAN) MiniportAdapterContext;
    PADAPT pAdapt = pVElan->pAdapt;
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(pVElan, OffloadBlockList, 
                                  ProcessOffloadBlockExistingBlocks);
    ASSERT(Status == NDIS_STATUS_SUCCESS);

    Status = ReplaceSourceHandleInOffloadBlock(pVElan, OffloadBlockList, NULL);
    if (Status != NDIS_STATUS_SUCCESS) {
        RSEnqueueOffloadBlock(pVElan, NdisUpdateOffload, OffloadBlockList);
        return;
    }

    NdisUpdateOffload(pAdapt->BindingHandle, 
                      (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
MPInvalidateOffload(
    IN PVOID MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    )
{
    PVELAN pVElan = (PVELAN) MiniportAdapterContext;
    PADAPT pAdapt = pVElan->pAdapt;
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(pVElan, OffloadBlockList, 
                                  ProcessOffloadBlockExistingBlocks);
    ASSERT(Status == NDIS_STATUS_SUCCESS);

    Status = ReplaceSourceHandleInOffloadBlock(pVElan, OffloadBlockList, NULL);
    if (Status != NDIS_STATUS_SUCCESS) {
        RSEnqueueOffloadBlock(pVElan, NdisInvalidateOffload, OffloadBlockList);
        return;
    }

    NdisInvalidateOffload(pAdapt->BindingHandle, 
                         (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
MPQueryOffload(
    IN PVOID MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    )
{
    PVELAN pVElan = (PVELAN) MiniportAdapterContext;
    PADAPT pAdapt = pVElan->pAdapt;
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(pVElan, OffloadBlockList, 
                                  ProcessOffloadBlockExistingBlocks);
    ASSERT(Status == NDIS_STATUS_SUCCESS);

    Status = ReplaceSourceHandleInOffloadBlock(pVElan, OffloadBlockList, NULL);

    if (Status != NDIS_STATUS_SUCCESS) {
        RSEnqueueOffloadBlock(pVElan, NdisQueryOffload, OffloadBlockList);
        return;
    }

    NdisQueryOffload(pAdapt->BindingHandle, 
                     (PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

//
// Requests used by miniport modules.
//
VOID
PtInitiateOffloadComplete(
    IN PVOID MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    )
{
    PADAPT pAdapt = (PADAPT)MiniportAdapterContext;
    PVELAN pVElan = RestoreSourceHandleInOffloadBlock(OffloadBlockList);
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(NULL, 
                (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList,
                ProcessOffloadBlockInitiateOffloadComplete);

    NdisMInitiateOffloadComplete(pVElan->MiniportAdapterHandle, 
                                 (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
PtTerminateOffloadComplete(
    IN PVOID MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    )
{
    PADAPT pAdapt = (PADAPT)MiniportAdapterContext;
    PVELAN pVElan = RestoreSourceHandleInOffloadBlock(OffloadBlockList);
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(NULL, 
                (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList,
                ProcessOffloadBlockTerminateOffloadComplete);
    
    NdisMTerminateOffloadComplete(pVElan->MiniportAdapterHandle, 
                                  (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
PtUpdateOffloadComplete(
    IN PVOID MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    )
{
    PADAPT pAdapt = (PADAPT)MiniportAdapterContext;
    PVELAN pVElan = RestoreSourceHandleInOffloadBlock(OffloadBlockList);
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(NULL, 
                (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList,
                ProcessOffloadBlockExistingBlocksComplete);
    
    NdisMUpdateOffloadComplete(pVElan->MiniportAdapterHandle, 
                                  (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
PtInvalidateOffloadComplete(
    IN PVOID MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    )
{
    PADAPT pAdapt = (PADAPT)MiniportAdapterContext;
    PVELAN pVElan = RestoreSourceHandleInOffloadBlock(OffloadBlockList);
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(NULL, 
                (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList,
                ProcessOffloadBlockExistingBlocksComplete);
    
    NdisMInvalidateOffloadComplete(pVElan->MiniportAdapterHandle, 
                                  (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}

VOID
PtQueryOffloadComplete(
    IN PVOID MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    )
{
    PADAPT pAdapt = (PADAPT)MiniportAdapterContext;
    PVELAN pVElan = RestoreSourceHandleInOffloadBlock(OffloadBlockList);
    NDIS_STATUS Status;

    Status = AdjustOffloadContext(NULL, 
                (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList,
                ProcessOffloadBlockExistingBlocksComplete);
    
    NdisMQueryOffloadComplete(pVElan->MiniportAdapterHandle, 
                              (PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST)OffloadBlockList);
}


//
// IO functions.
//

NDIS_STATUS
MPTcpOffloadSendHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    )
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PADAPT                      pAdapt = pVElan->pAdapt;
    PIM_OFFLOAD_ENTRY           ImOffloadEntry = (PIM_OFFLOAD_ENTRY)ProviderContext;
    NDIS_STATUS                 Status;

    if (InResourceScarceState(ImOffloadEntry)) {
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_UPLOAD_REQUESTED);

        TcpOffloadEventHandlers->NdisTcpOffloadSendComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;        
    }

    Status = ReplaceSourceHandleInNblChain(pVElan, NetBufferList);

    if (Status != NDIS_STATUS_SUCCESS) {
        SetResourceScarceState(ImOffloadEntry);
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_REQUEST_UPLOAD);
        TcpOffloadEventHandlers->NdisTcpOffloadSendComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    return NdisOffloadTcpSend(&ImOffloadEntry->OffloadHandle, NetBufferList);
}

NDIS_STATUS
MPTcpOffloadReceiveHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    )
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PADAPT                      pAdapt = pVElan->pAdapt;
    PIM_OFFLOAD_ENTRY           ImOffloadEntry = (PIM_OFFLOAD_ENTRY)ProviderContext;
    NDIS_STATUS                 Status;

    if (InResourceScarceState(ImOffloadEntry)) {
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_UPLOAD_REQUESTED);

        TcpOffloadEventHandlers->NdisTcpOffloadReceiveComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    Status = ReplaceSourceHandleInNblChain(pVElan, NetBufferList);

    if (Status != NDIS_STATUS_SUCCESS) {
        SetResourceScarceState(ImOffloadEntry);
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_REQUEST_UPLOAD);
        TcpOffloadEventHandlers->NdisTcpOffloadReceiveComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    return NdisOffloadTcpReceive(&ImOffloadEntry->OffloadHandle, NetBufferList);
}

NDIS_STATUS
MPTcpOffloadDisconnectHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN ULONG                                 Flags
    )
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PADAPT                      pAdapt = pVElan->pAdapt;
    PIM_OFFLOAD_ENTRY           ImOffloadEntry = (PIM_OFFLOAD_ENTRY)ProviderContext;
    NDIS_STATUS                 Status;

    if (InResourceScarceState(ImOffloadEntry)) {
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_UPLOAD_REQUESTED);

        TcpOffloadEventHandlers->NdisTcpOffloadDisconnectComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    Status = ReplaceSourceHandleInNblChain(pVElan, NetBufferList);

    if (Status != NDIS_STATUS_SUCCESS) {
        SetResourceScarceState(ImOffloadEntry);
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_REQUEST_UPLOAD);

        TcpOffloadEventHandlers->NdisTcpOffloadDisconnectComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    return NdisOffloadTcpDisconnect(&ImOffloadEntry->OffloadHandle, 
                                    NetBufferList,
                                    Flags);
}

NDIS_STATUS
MPTcpOffloadReceiveReturntHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    )
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PADAPT                      pAdapt = pVElan->pAdapt;

    NdisOffloadTcpReceiveReturn(pAdapt->BindingHandle, NetBufferList);

    return STATUS_SUCCESS;
}

NDIS_STATUS
MPTcpOffloadForwardtHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    )
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PADAPT                      pAdapt = pVElan->pAdapt;
    PIM_OFFLOAD_ENTRY           ImOffloadEntry = (PIM_OFFLOAD_ENTRY)ProviderContext;
    NDIS_STATUS                 Status;

    if (InResourceScarceState(ImOffloadEntry)) {
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_UPLOAD_REQUESTED);

        TcpOffloadEventHandlers->NdisTcpOffloadForwardComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    Status = ReplaceSourceHandleInNblChain(pVElan, NetBufferList);

    if (Status != NDIS_STATUS_SUCCESS) {
        SetResourceScarceState(ImOffloadEntry);
        SetStatusInNblChain(NetBufferList, NDIS_STATUS_REQUEST_UPLOAD);

        TcpOffloadEventHandlers->NdisTcpOffloadForwardComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);
        return NDIS_STATUS_PENDING;
    }

    return NdisOffloadTcpForward(&ImOffloadEntry->OffloadHandle, 
                                    NetBufferList);
}

VOID
PtTcpOffloadSendCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    )
{
    PVELAN                      pVElan;
    PNET_BUFFER_LIST            NextListHead = NULL;

    do {
        pVElan = RestoreSourceHandleInNblChain(NetBufferList, &NextListHead);

        TcpOffloadEventHandlers->NdisTcpOffloadSendComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);

        NetBufferList = NextListHead;
    } while (NextListHead != NULL);
}

VOID
PtTcpOffloadReceiveCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    )
{
    PVELAN                      pVElan;
    PNET_BUFFER_LIST            NextListHead = NULL;

    do {
        pVElan = RestoreSourceHandleInNblChain(NetBufferList, &NextListHead);

        TcpOffloadEventHandlers->NdisTcpOffloadReceiveComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);

        NetBufferList = NextListHead;
    } while (NextListHead != NULL);
}

VOID
PtTcpOffloadDisconnectCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    )
{
    PVELAN                      pVElan;
    PNET_BUFFER_LIST            NextListHead = NULL;

    do {
        pVElan = RestoreSourceHandleInNblChain(NetBufferList, &NextListHead);

        TcpOffloadEventHandlers->NdisTcpOffloadDisconnectComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);

        NetBufferList = NextListHead;
    } while (NextListHead != NULL);
}

VOID
PtTcpOffloadForwardCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    )
{
    PVELAN                      pVElan;
    PNET_BUFFER_LIST            NextListHead = NULL;

    do {
        pVElan = RestoreSourceHandleInNblChain(NetBufferList, &NextListHead);

        TcpOffloadEventHandlers->NdisTcpOffloadForwardComplete(
            pVElan->MiniportAdapterHandle, NetBufferList);

        NetBufferList = NextListHead;
    } while (NextListHead != NULL);
}

VOID
PtTcpOffloadEventIndicate(
    IN NDIS_HANDLE                           NdisOffloadHandle,
    IN ULONG                                 EventType,
    IN ULONG                                 EventSpecificInformation
    )
{
    PNDIS_OFFLOAD_HANDLE Handle;
    PIM_OFFLOAD_ENTRY ImOffloadEntry = (PIM_OFFLOAD_ENTRY)NdisOffloadHandle;

    TcpOffloadEventHandlers->NdisTcpOffloadEventHandler(
        ImOffloadEntry->NdisOffloadHandle,
        EventType,
        EventSpecificInformation);
}


NDIS_STATUS
PtTcpOffloadReceiveIndicate(
    IN NDIS_HANDLE                           NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN NDIS_STATUS                           Status
    )
{
    PNDIS_OFFLOAD_HANDLE Handle;
    PIM_OFFLOAD_ENTRY ImOffloadEntry = (PIM_OFFLOAD_ENTRY)NdisOffloadHandle;

    return TcpOffloadEventHandlers->NdisTcpOffloadReceiveHandler(
                ImOffloadEntry->NdisOffloadHandle,
                NetBufferList, 
                Status);
}


//
// Miniport and protocol offload registration.
//

NDIS_PROVIDER_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS TcpOffloadProviderHandlers = {
    {
        NDIS_OBJECT_TYPE_PROVIDER_CHIMNEY_OFFLOAD_CHARACTERISTICS,
        0,
        sizeof(NDIS_PROVIDER_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS)
    },
    0,
    NdisTcpChimneyOffload,
    MPTcpOffloadSendHandler,
    MPTcpOffloadReceiveHandler,
    MPTcpOffloadDisconnectHandler,
    MPTcpOffloadForwardtHandler,
    MPTcpOffloadReceiveReturntHandler
};

NDIS_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS GenericOffloadProviderHandlers = {
    {
        NDIS_OBJECT_TYPE_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS,
        0,
        sizeof(NDIS_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS)
    },
    0,
    MPInitiateOffload,
    MPTerminateOffload,
    MPUpdateOffload,
    MPInvalidateOffload,
    MPQueryOffload
};

NDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS TcpOffloadClientHandlers = {
    {
        NDIS_OBJECT_TYPE_CLIENT_CHIMNEY_OFFLOAD_CHARACTERISTICS,
        NDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS_REVISION_1,
        sizeof(NDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS)
    },
    0,
    NdisTcpChimneyOffload,
    PtTcpOffloadSendCompleteHandler,
    PtTcpOffloadReceiveCompleteHandler,
    PtTcpOffloadDisconnectCompleteHandler,
    PtTcpOffloadForwardCompleteHandler,
    PtTcpOffloadEventIndicate,
    PtTcpOffloadReceiveIndicate
};

NDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS GenericOffloadClientHandlers = {
    {
        NDIS_OBJECT_TYPE_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS,
        NDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS_REVISION_1,
        sizeof(NDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS)
    },
    0,
    PtInitiateOffloadComplete,
    PtTerminateOffloadComplete,
    PtUpdateOffloadComplete,
    PtInvalidateOffloadComplete,
    PtQueryOffloadComplete,
    NULL
};

NDIS_STATUS
MPSetGenericOffloadClientHandlers(
    IN NDIS_HANDLE NdisDriverHandle
    )
{
    NDIS_STATUS Status;

    Status = NdisSetOptionalHandlers(
        NdisDriverHandle,
        (PNDIS_DRIVER_OPTIONAL_HANDLERS) &GenericOffloadProviderHandlers);

    return Status;
}


NDIS_STATUS
MPSetTcpOffloadClientHandlers(
    IN NDIS_HANDLE NdisDriverHandle
    )
{
    NDIS_STATUS Status;

    Status = NdisSetOptionalHandlers(
        NdisDriverHandle,
        (PNDIS_DRIVER_OPTIONAL_HANDLERS) &TcpOffloadProviderHandlers);

    return Status;  
}

NDIS_STATUS
PtSetGenericOffloadClientHandlers(
    IN NDIS_HANDLE NdisDriverHandle
    )
{
    NDIS_STATUS Status;

    Status = NdisSetOptionalHandlers(
        NdisDriverHandle,
        (PNDIS_DRIVER_OPTIONAL_HANDLERS) &GenericOffloadClientHandlers);

    return Status;
}


NDIS_STATUS
PtSetTcpOffloadClientHandlers(
    IN NDIS_HANDLE NdisBindingHandle
    )
{
    NDIS_STATUS Status;

    Status = NdisSetOptionalHandlers(
        NdisBindingHandle,
        (PNDIS_DRIVER_OPTIONAL_HANDLERS) &TcpOffloadClientHandlers);

    return Status;  
}


//
// Initialization function.
//
VOID
OffloadCleanup()
{
    while (!IsListEmpty(&RSCallEntryList)) {
        PIM_CALL_ENTRY ImCallEntry;
        PLIST_ENTRY ListEntry;

        ListEntry = RemoveHeadList(&RSCallEntryList);
        ImCallEntry = CONTAINING_RECORD(ListEntry, IM_CALL_ENTRY, Link);
        NdisFreeMemory(ImCallEntry, sizeof(*ImCallEntry), 0);
    }

    NdisFreeSpinLock(&RSSpinLock);
}


NDIS_STATUS
OffloadInitialize()
{
    LONG i;
    PIM_CALL_ENTRY ImCallEntry;

    //
    // Initialize the Resouce-scarce handlers.
    //
    NdisInitializeListHead(&RSBlockListHead);
    NdisInitializeListHead(&RSCallEntryList);

    NdisAllocateSpinLock(&RSSpinLock);
    RSBlockCount = 0;
    NdisInitializeWorkItem(&RSWorkItem, RSCallback, NULL);
    RSWorkItemScheduled = RSCallEntryAvailable = FALSE;

    for (i = 0; i < RS_CALL_ENTRY_RESERVE_LIMIT; i++) {
        NdisAllocateMemoryWithTag(&ImCallEntry, sizeof(*ImCallEntry), 
                                  MuxOffloadTag);
        if (ImCallEntry == NULL) {
            OffloadCleanup();
            return NDIS_STATUS_RESOURCES;
        }
        InitializeListHead(&ImCallEntry->Link);
        ImCallEntry->State = ImOffloadResourceScarceState;
        InsertHeadList(&RSBlockListHead, &ImCallEntry->Link);
    }
    return NDIS_STATUS_SUCCESS;
}




