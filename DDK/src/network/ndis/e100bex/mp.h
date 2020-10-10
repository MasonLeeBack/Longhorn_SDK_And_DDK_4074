/*++

Copyright (c) 1999  Microsoft Corporation

Module Name:
    mp.h

Abstract:
    Miniport generic portion header file
    Change send and receive APIs to use Net Buffer and Net Buffer List

Revision History:
    Who         When        What
    --------    --------    ----------------------------------------------
    DChen       03-04-99    created

Notes:

--*/

#ifndef _MP_H
#define _MP_H

#ifdef NDIS60_MINIPORT
#define MP_NDIS_MAJOR_VERSION       6
#define MP_NDIS_MINOR_VERSION       0
#endif

#ifdef NDIS50_MINIPORT
#define MP_NDIS_MAJOR_VERSION       5
#define MP_NDIS_MINOR_VERSION       0
#endif

#ifdef NDIS51_MINIPORT
#define MP_NDIS_MAJOR_VERSION       5
#define MP_NDIS_MINOR_VERSION       1
#endif

#define ALIGN_16                   16

#ifndef MIN
#define MIN(a, b)   ((a) > (b) ? b: a)
#endif

//
// The driver should put the data(after Ethernet header) at 8-bytes boundary
//
#define ETH_DATA_ALIGN                      8   // the data(after Ethernet header) should be 8-byte aligned
// 
// Shift HW_RFD 0xA bytes to make Tcp data 8-byte aligned
// Since the ethernet header is 14 bytes long. If a packet is at 0xA bytes 
// offset, its data(ethernet user data) will be at 8 byte boundary
// 
#define HWRFD_SHIFT_OFFSET                0xA   // Shift HW_RFD 0xA bytes to make Tcp data 8-byte aligned

//
// The driver has to allocate more data then HW_RFD needs to allow shifting data
// 
#define MORE_DATA_FOR_ALIGN         (ETH_DATA_ALIGN + HWRFD_SHIFT_OFFSET)
//
// Get a 8-bytes aligned memory address from a given the memory address.
// If the given address is not 8-bytes aligned, return  the closest bigger memory address
// which is 8-bytes aligned. 
// 
#define DATA_ALIGN(_Va)             ((PVOID)(((ULONG_PTR)(_Va) + (ETH_DATA_ALIGN - 1)) & ~(ETH_DATA_ALIGN - 1)))
//
// Get the number of bytes the final address shift from the original address
// 
#define BYTES_SHIFT(_NewVa, _OrigVa) ((PUCHAR)(_NewVa) - (PUCHAR)(_OrigVa))
//
// Define 4 macros to get some fields in NetBufferList for miniport's own use
//
#define MP_GET_NET_BUFFER_LIST_LINK(_NetBufferList)       (&(NET_BUFFER_LIST_NEXT_NBL(_NetBufferList)))
#define MP_GET_NET_BUFFER_LIST_NEXT_SEND(_NetBufferList)  ((_NetBufferList)->MiniportReserved[0])
#define MP_GET_NET_BUFFER_LIST_REF_COUNT(_NetBufferList)  ((ULONG)(ULONG_PTR)((_NetBufferList)->MiniportReserved[1]))

#define MP_GET_NET_BUFFER_PREV(_NetBuffer)      ((_NetBuffer)->MiniportReserved[0])
#define MP_GET_NET_BUFFER_LIST_FROM_QUEUE_LINK(_pEntry)  \
    (CONTAINING_RECORD((_pEntry), NET_BUFFER_LIST, Next))

    //
    // We may need to initialize other field later
    //
#define MP_GET_NET_BUFFER_LIST_RFD(_NetBufferList)      ((PMP_RFD)((_NetBufferList)->MiniportReserved[0])) 
#define INIT_RECV_NET_BUFFER_LIST(_NetBufferList, _NdisBuffer)              \
    {                                                                       \
        ASSERT(_NetBufferList->FirstNetBuffer);                             \
        _NetBufferList->MdlChain = _NdisBuffer                              \
    }                                                                       

//
// Take advantage of dispatch level
//
#define MP_ACQUIRE_SPIN_LOCK(_Lock, DispatchLevel)                          \
    {                                                                       \
        if (DispatchLevel)                                                  \
        {                                                                   \
            NdisDprAcquireSpinLock(_Lock);                                  \
        }                                                                   \
        else                                                                \
        {                                                                   \
            NdisAcquireSpinLock(_Lock);                                     \
        }                                                                   \
    }
            
#define MP_RELEASE_SPIN_LOCK(_Lock, DispatchLevel)                          \
    {                                                                       \
        if (DispatchLevel)                                                  \
        {                                                                   \
            NdisDprReleaseSpinLock(_Lock);                                  \
        }                                                                   \
        else                                                                \
        {                                                                   \
            NdisReleaseSpinLock(_Lock);                                     \
        }                                                                   \
    }
    
//
// Take advantage of MiniportReserved in NDIS_REQUEST
//
#define NDIS_REQUEST_NEXT_REQUEST(_NdisRequest)     ((PNDIS_OID_REQUEST) &((_NdisRequest)->MiniportReserved[0]))
#define MP_INIT_NDIS_STATUS_INDICATION(_pStatusIndication, _M, _St, _Buf, _BufSize)        \
    {                                                                                      \
        NdisZeroMemory(_pStatusIndication, sizeof(NDIS_STATUS_INDICATION));                \
        (_pStatusIndication)->Header.Type = NDIS_OBJECT_TYPE_STATUS_INDICATION;            \
        (_pStatusIndication)->Header.Revision = NDIS_STATUS_INDICATION_REVISION_1;         \
        (_pStatusIndication)->Header.Size = sizeof(NDIS_STATUS_INDICATION);                \
        (_pStatusIndication)->SourceHandle = _M;                                           \
        (_pStatusIndication)->StatusCode = _St;                                            \
        (_pStatusIndication)->StatusBuffer = _Buf;                                         \
        (_pStatusIndication)->StatusBufferSize = _BufSize;                                 \
    }


//--------------------------------------
// Queue structure and macros
//--------------------------------------
typedef struct _QUEUE_ENTRY
{
    struct _QUEUE_ENTRY *Next;
} QUEUE_ENTRY, *PQUEUE_ENTRY;

typedef struct _QUEUE_HEADER
{
    PQUEUE_ENTRY Head;
    PQUEUE_ENTRY Tail;
} QUEUE_HEADER, *PQUEUE_HEADER;

#define ETH_IS_LOCALLY_ADMINISTERED(Address) \
    (BOOLEAN)(((PUCHAR)(Address))[0] & ((UCHAR)0x02))

#define InitializeQueueHeader(QueueHeader)                 \
    {                                                      \
        (QueueHeader)->Head = (QueueHeader)->Tail = NULL;  \
    }

#define IsQueueEmpty(QueueHeader) ((QueueHeader)->Head == NULL)
#define GetHeadQueue(QueueHeader) ((QueueHeader)->Head)  //Get the head of the queue

#define RemoveHeadQueue(QueueHeader)                  \
    (QueueHeader)->Head;                              \
    {                                                 \
        PQUEUE_ENTRY pNext;                           \
        ASSERT((QueueHeader)->Head);                  \
        pNext = (QueueHeader)->Head->Next;            \
        (QueueHeader)->Head = pNext;                  \
        if (pNext == NULL)                            \
            (QueueHeader)->Tail = NULL;               \
    }

#define InsertHeadQueue(QueueHeader, QueueEntry)                \
    {                                                           \
        ((PQUEUE_ENTRY)QueueEntry)->Next = (QueueHeader)->Head; \
        (QueueHeader)->Head = (PQUEUE_ENTRY)(QueueEntry);       \
        if ((QueueHeader)->Tail == NULL)                        \
            (QueueHeader)->Tail = (PQUEUE_ENTRY)(QueueEntry);   \
    }

#define InsertTailQueue(QueueHeader, QueueEntry)                     \
    {                                                                \
        ((PQUEUE_ENTRY)QueueEntry)->Next = NULL;                     \
        if ((QueueHeader)->Tail)                                     \
            (QueueHeader)->Tail->Next = (PQUEUE_ENTRY)(QueueEntry);  \
        else                                                         \
            (QueueHeader)->Head = (PQUEUE_ENTRY)(QueueEntry);        \
        (QueueHeader)->Tail = (PQUEUE_ENTRY)(QueueEntry);            \
    }

//--------------------------------------
// Common fragment list structure
// Identical to the scatter gather frag list structure
// This is created to simplify the NIC-specific portion code
//--------------------------------------
#define MP_FRAG_ELEMENT SCATTER_GATHER_ELEMENT 
#define PMP_FRAG_ELEMENT PSCATTER_GATHER_ELEMENT 

typedef struct _MP_FRAG_LIST {
    ULONG NumberOfElements;
    ULONG_PTR Reserved;
    MP_FRAG_ELEMENT Elements[NIC_MAX_PHYS_BUF_COUNT];
} MP_FRAG_LIST, *PMP_FRAG_LIST;
                     

//--------------------------------------
// Some utility macros        
//--------------------------------------
#ifndef min
#define min(_a, _b)     (((_a) < (_b)) ? (_a) : (_b))
#endif

#ifndef max
#define max(_a, _b)     (((_a) > (_b)) ? (_a) : (_b))
#endif

#define MP_ALIGNMEM(_p, _align) (((_align) == 0) ? (_p) : (PUCHAR)(((ULONG_PTR)(_p) + ((_align)-1)) & (~((ULONG_PTR)(_align)-1))))
#define MP_ALIGNMEM_PHYS(_p, _align) (((_align) == 0) ?  (_p) : (((ULONG)(_p) + ((_align)-1)) & (~((ULONG)(_align)-1))))
#define MP_ALIGNMEM_PA(_p, _align) (((_align) == 0) ?  (_p).QuadPart : (((_p).QuadPart + ((_align)-1)) & (~((ULONGLONG)(_align)-1))))

#define GetListHeadEntry(ListHead)  ((ListHead)->Flink)
#define GetListTailEntry(ListHead)  ((ListHead)->Blink)
#define GetListFLink(ListEntry)     ((ListEntry)->Flink)

#define IsSListEmpty(ListHead)  (((PSINGLE_LIST_ENTRY)ListHead)->Next == NULL)

#define MP_EXIT goto exit

//--------------------------------------
// Memory manipulation macros        
//--------------------------------------

/*++
VOID
MP_MEMSET(
    IN  PVOID       Pointer,
    IN  ULONG       Length,
    IN  UCHAR       Value
    )
--*/
#define MP_MEMSET(Pointer, Length, Value)   NdisFillMemory(Pointer, Length, Value)

/*++
VOID
MP_MEMCOPY(
    IN  POPAQUE     Destn,
    IN  POPAQUE     Source,
    IN  ULONG       Length
    )
--*/
#define MP_MEMCOPY(Destn, Source, Length) NdisMoveMemory((Destn), (Source), (Length))


/*++
ULONG
MP_MEMCOPY(
    IN  PVOID       Destn,
    IN  PVOID       Source,
    IN  ULONG       Length
    )
--*/
#define MPMemCmp(Destn, Source, Length)   \
    RtlCompareMemory((PUCHAR)(Destn), (PUCHAR)(Source), (ULONG)(Length))

#if DBG

/*++
PVOID
MP_ALLOCMEMTAG(
    IN  ULONG   Size
    )
--*/

#define MP_ALLOCMEMTAG(_NdisHandle, size) \
    MPAuditAllocMemTag(size, _FILENUMBER, __LINE__, _NdisHandle);

/*++
VOID
MP_FREEMEM(
    IN  PVOID   Pointer
    )
--*/
#define MP_FREEMEM(ptr) MPAuditFreeMem(ptr)

#else // DBG

#define MP_ALLOCMEMTAG(_NdisHandle, size) \
    NdisAllocateMemoryWithTagPriority(_NdisHandle, size, NIC_TAG, LowPoolPriority)

#define MP_FREEMEM(ptr) NdisFreeMemory(ptr, 0, 0)

#endif 

#define MP_FREE_NDIS_STRING(str)                        \
    MP_FREEMEM((str)->Buffer);                          \
    (str)->Length = 0;                                  \
    (str)->MaximumLength = 0;                           \
    (str)->Buffer = NULL;

//--------------------------------------
// Macros for flag and ref count operations       
//--------------------------------------
#define MP_SET_FLAG(_M, _F)         ((_M)->Flags |= (_F))   
#define MP_CLEAR_FLAG(_M, _F)       ((_M)->Flags &= ~(_F))
#define MP_CLEAR_FLAGS(_M)          ((_M)->Flags = 0)
#define MP_TEST_FLAG(_M, _F)        (((_M)->Flags & (_F)) != 0)
#define MP_TEST_FLAGS(_M, _F)       (((_M)->Flags & (_F)) == (_F))

#define MP_INC_REF(_A)              NdisInterlockedIncrement(&(_A)->RefCount)
#define MP_DEC_REF(_A)              NdisInterlockedDecrement(&(_A)->RefCount)
#define MP_GET_REF(_A)              ((_A)->RefCount)

#define MP_INC_RCV_REF(_A)          ((_A)->RcvRefCount++)
#define MP_DEC_RCV_REF(_A)          ((_A)->RcvRefCount--)
#define MP_GET_RCV_REF(_A)          ((_A)->RcvRefCount)
   
typedef struct _MP_ADAPTER MP_ADAPTER, *PMP_ADAPTER;

//--------------------------------------
// Coalesce Tx buffer for local data copying                     
//--------------------------------------
typedef struct _MP_TXBUF
{
    SINGLE_LIST_ENTRY       SList;
    PNDIS_BUFFER            NdisBuffer;

    ULONG                   AllocSize;
    PVOID                   AllocVa;
    NDIS_PHYSICAL_ADDRESS   AllocPa; 

    PUCHAR                  pBuffer;
    NDIS_PHYSICAL_ADDRESS   BufferPa;
    ULONG                   BufferSize;

} MP_TXBUF, *PMP_TXBUF;

//--------------------------------------
// TCB (Transmit Control Block)
//--------------------------------------
typedef struct _MP_TCB
{
    struct _MP_TCB    *Next;
    struct _MP_TCB    *Prev;
    ULONG             Flags;
    ULONG             Count;
    PNET_BUFFER       NetBuffer;        // Use Net Buffer for transmitting
    PNET_BUFFER_LIST  NetBufferList;

    PMP_TXBUF         MpTxBuf;
    PHW_TCB           HwTcb;            // ptr to HW TCB VA
    ULONG             HwTcbPhys;        // ptr to HW TCB PA
    PHW_TCB           PrevHwTcb;        // ptr to previous HW TCB VA

    PTBD_STRUC        HwTbd;            // ptr to first TBD 
    ULONG             HwTbdPhys;        // ptr to first TBD PA

    PMP_ADAPTER       Adapter;
    PVOID             ScatterGatherListBuffer;  
    PVOID             pSGList;          // SG list passsed to MpProcessSGList which may be different from
                                        // ScatterGatherListBuffer
    
} MP_TCB, *PMP_TCB;

//--------------------------------------
// RFD (Receive Frame Descriptor)
//--------------------------------------
typedef struct _MP_RFD
{
    LIST_ENTRY              List;
    PNET_BUFFER_LIST        NetBufferList;
    PNDIS_BUFFER            NdisBuffer;         // Pointer to Buffer

    PHW_RFD                 HwRfd;              // ptr to hardware RFD
    PHW_RFD                 OriginalHwRfd;       // ptr to memory allocated by NDIS
    NDIS_PHYSICAL_ADDRESS   HwRfdPa;            // physical address of RFD   
    NDIS_PHYSICAL_ADDRESS   OriginalHwRfdPa;     // Original physical address allocated by NDIS
    ULONG                   HwRfdPhys;          // lower part of HwRfdPa 
    
    ULONG                   Flags;
    UINT                    PacketSize;         // total size of receive frame
} MP_RFD, *PMP_RFD;

//--------------------------------------
// Structure for pended OIS query request
//--------------------------------------
typedef struct _MP_QUERY_REQUEST
{
    IN NDIS_OID Oid;
    IN PVOID InformationBuffer;
    IN ULONG InformationBufferLength;
    OUT PULONG BytesWritten;
    OUT PULONG BytesNeeded;
} MP_QUERY_REQUEST, *PMP_QUERY_REQUEST;

//--------------------------------------
// Structure for pended OIS set request
//--------------------------------------
typedef struct _MP_SET_REQUEST
{
    IN NDIS_OID Oid;
    IN PVOID InformationBuffer;
    IN ULONG InformationBufferLength;
    OUT PULONG BytesRead;
    OUT PULONG BytesNeeded;
} MP_SET_REQUEST, *PMP_SET_REQUEST;

//--------------------------------------
// Structure for Power Management Info
//--------------------------------------
typedef struct _MP_POWER_MGMT
{


    // List of Wake Up Patterns
    LIST_ENTRY              PatternList;

    // Number of outstanding Rcv Packet.
    UINT                    OutstandingRecv;
    // Current Power state of the adapter
    UINT                    PowerState;

    // Is PME_En on this adapter
    BOOLEAN                 PME_En;

    // Wake-up capabailities of the adapter
    BOOLEAN                 bWakeFromD0;
    BOOLEAN                 bWakeFromD1;
    BOOLEAN                 bWakeFromD2;
    BOOLEAN                 bWakeFromD3Hot;
    BOOLEAN                 bWakeFromD3Aux;
    // Pad
    BOOLEAN                 Pad[2];

} MP_POWER_MGMT, *PMP_POWER_MGMT;

typedef struct _MP_WAKE_PATTERN 
{
    // Link to the next Pattern
    LIST_ENTRY      linkListEntry;

    // E100 specific signature of the pattern
    ULONG           Signature;

    // Size of this allocation
    ULONG           AllocationSize;

    // Pattern - This contains the NDIS_PM_PACKET_PATTERN
    UCHAR           Pattern[1];
    
} MP_WAKE_PATTERN , *PMP_WAKE_PATTERN ;

//--------------------------------------
// Macros specific to miniport adapter structure 
//--------------------------------------
#define MP_TCB_RESOURCES_AVAIABLE(_M) ((_M)->nBusySend < (_M)->NumTcb)

#define MP_SHOULD_FAIL_SEND(_M)   ((_M)->Flags & fMP_ADAPTER_FAIL_SEND_MASK) 
#define MP_IS_NOT_READY(_M)       ((_M)->Flags & fMP_ADAPTER_NOT_READY_MASK)
#define MP_IS_READY(_M)           !((_M)->Flags & fMP_ADAPTER_NOT_READY_MASK)

#define MP_SET_PACKET_RFD(_p, _rfd)  *((PMP_RFD *)&(_p)->MiniportReserved[0]) = _rfd
#define MP_GET_PACKET_RFD(_p)        *((PMP_RFD *)&(_p)->MiniportReserved[0])
#define MP_GET_PACKET_MR(_p)         (&(_p)->MiniportReserved[0]) 

#define MP_SET_HARDWARE_ERROR(adapter)    MP_SET_FLAG(adapter, fMP_ADAPTER_HARDWARE_ERROR) 
#define MP_SET_NON_RECOVER_ERROR(adapter) MP_SET_FLAG(adapter, fMP_ADAPTER_NON_RECOVER_ERROR)

#define MP_OFFSET(field)   ((UINT)FIELD_OFFSET(MP_ADAPTER,field))
#define MP_SIZE(field)     sizeof(((PMP_ADAPTER)0)->field)

typedef enum _NIC_STATE
{
    NicPaused,
    NicPausing,
    NicRunning
} NIC_STATE, *PNIC_STATE;


//--------------------------------------
// The miniport adapter structure
//--------------------------------------
typedef struct _MP_ADAPTER
{
    LIST_ENTRY              List;
    
    // Handle given by NDIS when the Adapter registered itself.
    NDIS_HANDLE             AdapterHandle;

    //flags 
    ULONG                   Flags;

    // configuration 
    UCHAR                   PermanentAddress[ETH_LENGTH_OF_ADDRESS];
    UCHAR                   CurrentAddress[ETH_LENGTH_OF_ADDRESS];
    BOOLEAN                 bOverrideAddress;

    NDIS_EVENT              ExitEvent;

    // SEND                       
    PMP_TCB                 CurrSendHead;
    PMP_TCB                 CurrSendTail;
    LONG                    nBusySend;
    LONG                    nWaitSend;
    LONG                    nCancelSend;
    QUEUE_HEADER            SendWaitQueue;
    QUEUE_HEADER            SendCancelQueue;
    SINGLE_LIST_ENTRY       SendBufList;

    LONG                    NumTcb;             // Total number of TCBs
    LONG                    RegNumTcb;          // 'NumTcb'
    LONG                    NumTbd;
   
    NDIS_HANDLE             SendBufferPool;

    PUCHAR                  MpTcbMem;
    ULONG                   MpTcbMemSize;

    PUCHAR                  MpTxBufMem;
    ULONG                   MpTxBufMemSize;
    
    PUCHAR                  MpTxBufAllocVa;
    ULONG                   MpTxBufAllocSize;
    NDIS_PHYSICAL_ADDRESS   MpTxBufAllocPa;
    
    PUCHAR                  HwSendMemAllocVa;
    ULONG                   HwSendMemAllocSize;
    NDIS_PHYSICAL_ADDRESS   HwSendMemAllocPa;

    // command unit status flags
    BOOLEAN                 TransmitIdle;
    BOOLEAN                 ResumeWait;

    // RECV
    LIST_ENTRY              RecvList;
    LIST_ENTRY              RecvPendList;
    LONG                    nReadyRecv;
    LONG                    RefCount;

    LONG                    NumRfd;
    LONG                    CurrNumRfd;
    LONG                    MaxNumRfd;
    ULONG                   HwRfdSize;
    PUCHAR                  HwRfds;
    NDIS_PHYSICAL_ADDRESS   HwRfdsPa;
    ULONG                   NumHwRfds;
    
    BOOLEAN                 bAllocNewRfd;
    LONG                    RfdShrinkCount;

    NDIS_HANDLE             RecvNetBufferListPool;
    NDIS_HANDLE             RecvBufferPool;

    // spin locks
    NDIS_SPIN_LOCK          Lock;

    // lookaside lists                               
    NPAGED_LOOKASIDE_LIST   RecvLookaside;

    // Packet Filter and look ahead size.
    ULONG                   PacketFilter;
    ULONG                   OldPacketFilter;
    ULONG                   ulLookAhead;
    USHORT                  usLinkSpeed;
    USHORT                  usDuplexMode;

    // multicast list
    UINT                    MCAddressCount;
    UINT                    OldMCAddressCount;
    UCHAR                   MCList[NIC_MAX_MCAST_LIST][ETH_LENGTH_OF_ADDRESS];
    UCHAR                   OldMCList[NIC_MAX_MCAST_LIST][ETH_LENGTH_OF_ADDRESS];

    // Packet counts
    ULONG64                 GoodTransmits;
    ULONG64                 GoodReceives;
    ULONG                   NumTxSinceLastAdjust;

    // Count of transmit errors
    ULONG                   TxAbortExcessCollisions;
    ULONG                   TxLateCollisions;
    ULONG                   TxDmaUnderrun;
    ULONG                   TxLostCRS;
    ULONG                   TxOKButDeferred;
    ULONG                   OneRetry;
    ULONG                   MoreThanOneRetry;
    ULONG                   TotalRetries;

    // Count of receive errors
    ULONG                   RcvCrcErrors;
    ULONG                   RcvAlignmentErrors;
    ULONG                   RcvResourceErrors;
    ULONG                   RcvDmaOverrunErrors;
    ULONG                   RcvCdtFrames;
    ULONG                   RcvRuntErrors;

    ULONG                   IoBaseAddress;    
    ULONG                   IoRange;           
    ULONG                   InterruptLevel;
    ULONG                   InterruptVector;
    NDIS_PHYSICAL_ADDRESS   MemPhysAddress;

    PVOID                   PortOffset;
    PHW_CSR                 CSRAddress;
    NDIS_HANDLE             NdisInterruptHandle;
    PIO_INTERRUPT_MESSAGE_INFO MessageInfoTable;  // if the driver supports MSI
    NDIS_INTERRUPT_TYPE        InterruptType;     // if the driver supports MSI

    // Revision ID
    UCHAR                   RevsionID;

    USHORT                  SubVendorID;
    USHORT                  SubSystemID;

    ULONG                   CacheFillSize;
    ULONG                   Debug;

    PUCHAR                  HwMiscMemAllocVa;
    ULONG                   HwMiscMemAllocSize;
    NDIS_PHYSICAL_ADDRESS   HwMiscMemAllocPa;

    PSELF_TEST_STRUC        SelfTest;           // 82558 SelfTest
    ULONG                   SelfTestPhys;

    PNON_TRANSMIT_CB        NonTxCmdBlock;      // 82558 (non transmit) Command Block
    ULONG                   NonTxCmdBlockPhys;

    PDUMP_AREA_STRUC        DumpSpace;          // 82558 dump buffer area
    ULONG                   DumpSpacePhys;

    PERR_COUNT_STRUC        StatsCounters;
    ULONG                   StatsCounterPhys;

    UINT                    PhyAddress;         // Address of the phy component 
    UCHAR                   Connector;          // 0=Auto, 1=TPE, 2=MII

    USHORT                  AiTxFifo;           // TX FIFO Threshold
    USHORT                  AiRxFifo;           // RX FIFO Threshold
    UCHAR                   AiTxDmaCount;       // Tx dma count
    UCHAR                   AiRxDmaCount;       // Rx dma count
    UCHAR                   AiUnderrunRetry;    // The underrun retry mechanism
    UCHAR                   AiForceDpx;         // duplex setting
    USHORT                  AiTempSpeed;        // 'Speed', user over-ride of line speed
    USHORT                  AiThreshold;        // 'Threshold', Transmit Threshold
    BOOLEAN                 MWIEnable;          // Memory Write Invalidate bit in the PCI command word
    UCHAR                   Congest;            // Enables congestion control
    UCHAR                   SpeedDuplex;        // New reg value for speed/duplex

    //
    // new fields for NDIS 6.0 version to report unknown 
    // states and speed
    //
    NDIS_MEDIA_CONNECT_STATE  MediaState;
    NDIS_MEDIA_DUPLEX_STATE   MediaDuplexState;
    ULONG64                   LinkSpeed;
    
    NDIS_DEVICE_POWER_STATE CurrentPowerState;
    NDIS_DEVICE_POWER_STATE NextPowerState;

    UCHAR                   OldParameterField;

    // WMI support
    ULONG                   CustomDriverSet;
    ULONG                   HwErrCount;

    BOOLEAN                 bResetPending;
    NDIS_MINIPORT_TIMER     LinkDetectionTimer;
    QUEUE_HEADER            PendingRequestQueue;
    PNDIS_OID_REQUEST       PendingRequest;
    BOOLEAN                 bRequestPending;
    
    BOOLEAN                 bLinkDetectionWait;
    BOOLEAN                 bLookForLink;
    UCHAR                   CurrentScanPhyIndex;
    UCHAR                   LinkDetectionWaitCount;
    UCHAR                   FoundPhyAt;
    USHORT                  EepromAddressSize;

    MP_POWER_MGMT           PoMgmt;
    NDIS_SPIN_LOCK          SendLock;
    NDIS_SPIN_LOCK          RcvLock;
    ULONG                   RcvRefCount;  // number of packets that have not been returned back
    NDIS_EVENT              AllPacketsReturnedEvent;
    ULONG                   WakeUpEnable;
    PNET_BUFFER_LIST        SendingNetBufferList;

    PUCHAR                  pSGListMem;
    NDIS_HANDLE             NdisMiniportDmaHandle;
    ULONG                   ScatterGatherListSize;
    NIC_STATE               AdapterState;

} MP_ADAPTER, *PMP_ADAPTER;

//--------------------------------------
// Stall execution and wait with timeout
//--------------------------------------
/*++
    _condition  - condition to wait for 
    _timeout_ms - timeout value in milliseconds
    _result     - TRUE if condition becomes true before it times out
--*/
#define MP_STALL_AND_WAIT(_condition, _timeout_ms, _result)     \
{                                                               \
    int counter;                                                \
    _result = FALSE;                                            \
    for(counter = _timeout_ms * 50; counter != 0; counter--)    \
    {                                                           \
        if(_condition)                                          \
        {                                                       \
            _result = TRUE;                                     \
            break;                                              \
        }                                                       \
        NdisStallExecution(20);                                 \
    }                                                           \
}

__inline VOID MP_STALL_EXECUTION(
   IN UINT MsecDelay)
{
    // Delay in 100 usec increments
    MsecDelay *= 10;
    while (MsecDelay)
    {
        NdisStallExecution(100);
        MsecDelay--;
    }
}

#define MP_GET_ADAPTER_HANDLE(_A) (_A)->AdapterHandle

__inline NDIS_STATUS MP_GET_STATUS_FROM_FLAGS(PMP_ADAPTER Adapter)
{
    NDIS_STATUS Status = NDIS_STATUS_FAILURE;

    if(MP_TEST_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS))
    {
        Status = NDIS_STATUS_RESET_IN_PROGRESS;      
    }
    else if(MP_TEST_FLAG(Adapter, fMP_ADAPTER_HARDWARE_ERROR))
    {
        Status = NDIS_STATUS_DEVICE_FAILED;
    }
    else if(MP_TEST_FLAG(Adapter, fMP_ADAPTER_NO_CABLE))
    {
        Status = NDIS_STATUS_NO_CABLE;
    }

    return Status;
}   

//--------------------------------------
// Miniport routines in MP_MAIN.C
//--------------------------------------

NDIS_STATUS
DriverEntry(
    IN  PDRIVER_OBJECT      DriverObject,
    IN  PUNICODE_STRING     RegistryPath
    );

VOID 
MPAllocateComplete(
    NDIS_HANDLE     MiniportAdapterContext,
    IN PVOID        VirtualAddress,
    IN PNDIS_PHYSICAL_ADDRESS PhysicalAddress,
    IN ULONG        Length,
    IN PVOID        Context
    );

BOOLEAN 
MPCheckForHang(
    IN NDIS_HANDLE MiniportAdapterContext
    );

VOID
MPHalt(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HALT_ACTION        HaltAction
    );


NDIS_STATUS
MpSetOptions(
    IN NDIS_HANDLE  NdisMiniportDriverHandle,
    IN NDIS_HANDLE  MiniportDriverContext
    );

NDIS_STATUS 
MPInitialize(
    IN  NDIS_HANDLE                        MiniportAdapterHandle,
    IN  NDIS_HANDLE                        MiniportDriverContext,
    IN  PNDIS_MINIPORT_INIT_PARAMETERS     MiniportInitParameters
    );

NDIS_STATUS 
MPPause(
    IN  NDIS_HANDLE                         MiniportAdapterContext,    
    IN  PNDIS_MINIPORT_PAUSE_PARAMETERS     MiniportPauseParameters
    );

NDIS_STATUS 
MPRestart(
    IN  NDIS_HANDLE                         MiniportAdapterContext,    
    IN  PNDIS_MINIPORT_RESTART_PARAMETERS   MiniportRestartParameters
    );

NDIS_STATUS
MPRequest(
    IN  NDIS_HANDLE         MiniportInterruptContext,
    IN  PNDIS_OID_REQUEST   NdisRequest
    );

VOID
MPHandleInterrupt(
    IN  NDIS_HANDLE     MiniportInterruptContext
    );

VOID
MPDisableInterrupt(
    IN  NDIS_HANDLE     MiniportInterruptContext);

VOID
MPEnableInterrupt(
    IN  NDIS_HANDLE     MiniportInterruptContext
    );

BOOLEAN 
MPIsr(
    IN  NDIS_HANDLE     MiniportInterruptContext,
    OUT PBOOLEAN        QueueMiniportInterruptDpcHandler,
    IN  PULONG          TargetProcessors
    );

NDIS_STATUS
MpQueryInformation(
    IN NDIS_HANDLE         MiniportAdapterContext,
    IN PNDIS_OID_REQUEST   NdisRequest
    );

NDIS_STATUS 
MPReset(
    IN  NDIS_HANDLE     MiniportAdapterContext,
    OUT PBOOLEAN        AddressingReset
    );

VOID 
MPReturnNetBufferLists(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

NDIS_STATUS 
MpSetInformation(
    IN NDIS_HANDLE         MiniportAdapterContext,
    IN PNDIS_OID_REQUEST   NdisRequest
    );

VOID 
MPShutdown(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_SHUTDOWN_ACTION    ShutdownAction
    );

VOID
MPSendNetBufferLists(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PNET_BUFFER_LIST    NetBufferList,
    IN  ULONG               SendFlags,
    IN  BOOLEAN             DispatchLevel
    );

VOID
MPReturnNetBufferLists(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PNET_BUFFER_LIST    NetBufferLists,
    IN  BOOLEAN             DispatchLevel
    );

VOID
MPCancelSendNetBufferLists(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PVOID               CancelId
    );

VOID
MPPnPEventNotify(
    IN  NDIS_HANDLE                 MiniportAdapterContext,
    IN  NDIS_DEVICE_PNP_EVENT       PnPEvent,
    IN  PVOID                       InformationBuffer,
    IN  ULONG                       InformationBufferLength
    );

NDIS_STATUS
MPSetPowerD0Private(
    IN MP_ADAPTER* pAdapter
    );

VOID
MPSetPowerLowPrivate(
    PMP_ADAPTER Adapter
    );

VOID 
MpExtractPMInfoFromPciSpace(
    PMP_ADAPTER pAdapter,
    PUCHAR pPciConfig
    );

VOID
HwSetWakeUpConfigure(
    IN PMP_ADAPTER pAdapter, 
    PUCHAR pPoMgmtConfigType, 
    UINT WakeUpParameter
    );

BOOLEAN  
MPIsPoMgmtSupported(
   IN PMP_ADAPTER pAdapter
   );

VOID 
NICIssueSelectiveReset(
    PMP_ADAPTER Adapter
    );

NDIS_STATUS
MPCalculateE100PatternForFilter(
    IN PUCHAR               pFrame,
    IN ULONG                FrameLength,
    IN PUCHAR               pMask,
    IN ULONG                MaskLength,
    OUT PULONG              pSignature
    );

VOID
MPRemoveAllWakeUpPatterns(
    IN PMP_ADAPTER          pAdapter
    );

NDIS_STATUS
MpHandleWMI(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PNDIS_REQUEST       WmiRequest
    );


NDIS_STATUS
MpWmiQueryRequest(
    IN  PMP_ADAPTER         Adapter,
    IN  PNDIS_REQUEST       Request
    );

NDIS_STATUS
MpWmiSetRequest(
    IN  PMP_ADAPTER         Adapter,
    IN  PNDIS_REQUEST       Request
    );

NDIS_STATUS
MpMethodRequest(
    IN  PMP_ADAPTER         Adapter,
    IN  PNDIS_OID_REQUEST   Request
    );
VOID
MpSetPowerLowComplete(
    IN PMP_ADAPTER          Adapter
    );

VOID
MpProcessSGList(
    IN  PDEVICE_OBJECT          pDO,
    IN  PVOID                   pIrp,
    IN  PSCATTER_GATHER_LIST    pSGList,
    IN  PVOID                   Context
    );

VOID MPUnload(IN PDRIVER_OBJECT DriverObject);

VOID
MPCancelRequest(
    IN  NDIS_HANDLE            MiniportAdapterContext,
    IN  PNDIS_OID_REQUEST      Request
    );

#endif  // _MP_H


