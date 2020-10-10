/*++

Copyright (c) 2003  Microsoft Corporation

Module Name:

    offload.h

Abstract:

    Defines Offload handlers.

Environment:

    Kernel mode

Revision History:

--*/


//
// To complile this sample with in the offload passthru mode, add these flags
// to the sources file {OFFLOAD_SUPPORT=1}
//

//
// Initialization/Cleanup functions.
//
NDIS_STATUS
OffloadInitialize();

VOID
OffloadCleanup();

//
// Global varialbes and functions.
//

extern PNDIS_TCP_OFFLOAD_EVENT_HANDLERS TcpOffloadEventHandlers;

NDIS_STATUS
MPSetGenericOffloadClientHandlers(
    IN NDIS_HANDLE NdisDriverHandle
    );

NDIS_STATUS
MPSetTcpOffloadClientHandlers(
    IN NDIS_HANDLE NdisBindingHandle
    );

NDIS_STATUS
PtSetGenericOffloadClientHandlers(
    IN NDIS_HANDLE NdisDriverHandle
    );

NDIS_STATUS
PtSetTcpOffloadClientHandlers(
    IN NDIS_HANDLE NdisBindingHandle
    );

//
// Requests used by protocol modules.
//
VOID
MPInitiateOffload(
    IN PVOID                                 MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

VOID
MPTerminateOffload(
    IN PVOID                                 MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

VOID
MPUpdateOffload(
    IN PVOID                                 MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

VOID
MPInvalidateOffload(
    IN PVOID                                 MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

VOID
MPQueryOffload(
    IN PVOID                                 MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

//
// Requests used by miniport modules.
//
VOID
PtInitiateOffloadComplete(
    IN PVOID                                 MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

VOID
PtTerminateOffloadComplete(
    IN PVOID                                 MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

VOID
PtUpdateOffloadComplete(
    IN PVOID                                 MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

VOID
PtInvalidateOffloadComplete(
    IN PVOID                                 MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

VOID
PtQueryOffloadComplete(
    IN PVOID                                 MiniportAdapterContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

//
// IO plane handlers.
//

NDIS_STATUS
MPTcpOffloadSendHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

VOID
PtTcpOffloadSendCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    );

NDIS_STATUS
MPTcpOffloadReceiveHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

VOID
PtTcpOffloadReceiveCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    );

NDIS_STATUS
MPTcpOffloadDisconnectHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN ULONG                                 Flags
    );

VOID
PtTcpOffloadDisconnectCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    );

NDIS_STATUS
MPTcpOffloadForwardtHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 ProviderContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

VOID
PtTcpOffloadForwardCompleteHandler(
    IN NDIS_HANDLE ProtocolBindingContext,
    IN PNET_BUFFER_LIST NetBufferList
    );

NDIS_STATUS
MPTcpOffloadReceiveReturntHandler(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

VOID
PtTcpOffloadEventIndicate(
    IN NDIS_HANDLE                           NdisOffloadHandle,
    IN ULONG                                 EventType,
    IN ULONG                                 EventSpecificInformation
    );

NDIS_STATUS
PtTcpOffloadReceiveIndicate(
    IN NDIS_HANDLE                           NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN NDIS_STATUS                           Status
    );


