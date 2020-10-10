/*++

Copyright (c) 2004 Microsoft Corporation

Module Name:

    dispmprt.h

Abstract:

    This header contain the new Display Loader APIs.

Author:

    Youssef Barakat (youssefb) 21-Jan-2004

Notes:

Revision History:

--*/

#ifndef _DISPMPRT_
#define _DISPMPRT_

//
// Old includes which are only kept for now for compatibility
//

#ifndef _NTOSP_

//
// Structures used by the kernel drivers to describe which ports must be
// hooked out directly from the V86 emulator to the driver.
//

typedef enum _EMULATOR_PORT_ACCESS_TYPE {
    Uchar,
    Ushort,
    Ulong
} EMULATOR_PORT_ACCESS_TYPE, *PEMULATOR_PORT_ACCESS_TYPE;
    
typedef struct _EMULATOR_ACCESS_ENTRY {
    ULONG BasePort;
    ULONG NumConsecutivePorts;
    EMULATOR_PORT_ACCESS_TYPE AccessType;
    UCHAR AccessMode;
    UCHAR StringSupport;
    PVOID Routine;
} EMULATOR_ACCESS_ENTRY, *PEMULATOR_ACCESS_ENTRY;

#endif

//
// Graphics support routines.
//

typedef
VOID
(*PBANKED_SECTION_ROUTINE) (
    IN ULONG ReadBank,
    IN ULONG WriteBank,
    IN PVOID Context
    );

#include <ntddvdeo.h>
#include <video.h>


//
// New defintions which could change
//

VOID
DlDebugPrint(
    VIDEO_DEBUG_LEVEL DebugPrintLevel,
    PCHAR DebugMessage,
    ...
    );

VIDEOPORT_API
VP_STATUS
DlSetTrappedEmulatorPorts(
    PVOID HwDeviceExtension,
    ULONG NumAccessRanges,
    PVIDEO_ACCESS_RANGE AccessRange
    );

VIDEOPORT_API
VP_STATUS
DlSetRegistryParameters(
    PVOID HwDeviceExtension,
    PWSTR ValueName,
    PVOID ValueData,
    ULONG ValueLength
    );

VIDEOPORT_API
VP_STATUS
DlInt10(
    PVOID HwDeviceExtension,
    PVIDEO_X86_BIOS_ARGUMENTS BiosArguments
    );

VIDEOPORT_API
PVOID
DlAllocatePool(
    IN PVOID HwDeviceExtension,
    IN VP_POOL_TYPE PoolType,
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag
    );

VIDEOPORT_API
PVOID
DlGetDeviceBase(
    PVOID HwDeviceExtension,
    PHYSICAL_ADDRESS IoAddress,
    ULONG NumberOfUchars,
    UCHAR InIoSpace
    );

VIDEOPORT_API
VOID
DlFreePool(
    IN PVOID HwDeviceExtension,
    IN PVOID Ptr
    );

VIDEOPORT_API
VOID
DlFreeDeviceBase(
    PVOID HwDeviceExtension,
    PVOID MappedAddress
    );

VIDEOPORT_API
BOOLEAN
DlDDCMonitorHelper(
    IN PVOID HwDeviceExtension,
    IN PVOID DDCControl,
    IN OUT PUCHAR EdidBuffer,
    IN ULONG EdidBufferSize
    );

VIDEOPORT_API
PVOID
DlGetCommonBuffer(
    IN  PVOID              HwDeviceExtension,
    IN  ULONG              DesiredLength,
    IN  ULONG              Alignment,
    OUT PPHYSICAL_ADDRESS  LogicalAddress,
    OUT PULONG             pActualLength,
    IN  BOOLEAN            CacheEnabled
    );

VIDEOPORT_API
VOID
DlFreeCommonBuffer(
    IN  PVOID            HwDeviceExtension,
    IN  ULONG            Length,
    IN  PVOID            VirtualAddress,
    IN  PHYSICAL_ADDRESS LogicalAddress,
    IN  BOOLEAN          CacheEnabled
    );

VIDEOPORT_API
BOOLEAN
DlUnlockPages(
    PVOID   hwDeviceExtension,
    PDMA    pDma
    );


VIDEOPORT_API
PVP_DMA_ADAPTER
DlGetDmaAdapter(
    IN PVOID                   HwDeviceExtension,
    IN PVP_DEVICE_DESCRIPTION  VpDeviceDescription
    );

VIDEOPORT_API
VOID
DlPutDmaAdapter(
    IN PVOID           HwDeviceExtension,
    IN PVP_DMA_ADAPTER VpDmaAdapter
    );

VIDEOPORT_API
PVOID
DlAllocateCommonBuffer(
    IN  PVOID             HwDeviceExtension,
    IN  PVP_DMA_ADAPTER   VpDmaAdapter,
    IN  ULONG             DesiredLength,
    OUT PPHYSICAL_ADDRESS LogicalAddress,
    IN  BOOLEAN           CacheEnabled,
    OUT PVOID             Reserved
    );

VIDEOPORT_API
VOID
DlReleaseCommonBuffer(
    IN  PVOID             HwDeviceExtension,
    IN  PVP_DMA_ADAPTER   VpDmaAdapter,
    IN  ULONG             Length,
    IN  PHYSICAL_ADDRESS  LogicalAddress,
    IN  PVOID             VirtualAddress,
    IN  BOOLEAN           CacheEnabled
    );

VIDEOPORT_API
PVOID
DlLockBuffer(
    IN PVOID              HwDeviceExtension,
    IN PVOID              BaseAddress,
    IN ULONG              Length,
    IN VP_LOCK_OPERATION  Operation
    );

VIDEOPORT_API
PVOID
DlAllocateCommonBuffer(
    IN  PVOID             HwDeviceExtension,
    IN  PVP_DMA_ADAPTER   VpDmaAdapter,
    IN  ULONG             DesiredLength,
    OUT PPHYSICAL_ADDRESS LogicalAddress,
    IN  BOOLEAN           CacheEnabled,
    OUT PVOID             Reserved
    );

VIDEOPORT_API
VOID
DlReleaseCommonBuffer(
    IN  PVOID             HwDeviceExtension,
    IN  PVP_DMA_ADAPTER   VpDmaAdapter,
    IN  ULONG             Length,
    IN  PHYSICAL_ADDRESS  LogicalAddress,
    IN  PVOID             VirtualAddress,
    IN  BOOLEAN           CacheEnabled
    );

VIDEOPORT_API
VOID
DlUnlockBuffer(
    IN PVOID   HwDeviceExtension,
    IN PVOID   Mdl
    );

BOOLEAN
VIDEOPORT_API
DlSynchronizeExecution(
    PVOID HwDeviceExtension,
    VIDEO_SYNCHRONIZE_PRIORITY Priority,
    PMINIPORT_SYNCHRONIZE_ROUTINE SynchronizeRoutine,
    PVOID Context
    );

VIDEOPORT_API
VP_STATUS
DlGetRegistryParameters(
    PVOID HwDeviceExtension,
    PWSTR ParameterName,
    UCHAR IsParameterFileName,
    PMINIPORT_GET_REGISTRY_ROUTINE GetRegistryRoutine,
    PVOID Context
    );

VIDEOPORT_API
VP_STATUS
DlGetDeviceData(
    PVOID HwDeviceExtension,
    VIDEO_DEVICE_DATA_TYPE DeviceDataType,
    PMINIPORT_QUERY_DEVICE_ROUTINE CallbackRoutine,
    PVOID Context
    );

VIDEOPORT_API
VP_STATUS
DlMapMemory(
    PVOID HwDeviceExtension,
    PHYSICAL_ADDRESS PhysicalAddress,
    PULONG Length,
    PULONG InIoSpace,
    PVOID *VirtualAddress
    );

VIDEOPORT_API
VP_STATUS
DlMapBankedMemory(
    PVOID HwDeviceExtension,
    PHYSICAL_ADDRESS PhysicalAddress,
    PULONG Length,
    PULONG InIoSpace,
    PVOID *VirtualAddress,
    ULONG BankLength,
    UCHAR ReadWriteBank,
    PBANKED_SECTION_ROUTINE BankRoutine,
    PVOID Context
    );

VIDEOPORT_API
VP_STATUS
DlAllocateBuffer(
    IN PVOID HwDeviceExtension,
    IN ULONG Size,
    OUT PVOID *Buffer
    );

VIDEOPORT_API
VOID
DlReleaseBuffer(
  IN PVOID HwDeviceExtension,
  IN PVOID Buffer
  );

VIDEOPORT_API
BOOLEAN
DlScanRom(
    PVOID HwDeviceExtension,
    PUCHAR RomBase,
    ULONG RomLength,
    PUCHAR String
    );

VIDEOPORT_API
VP_STATUS
DlUnmapMemory(
    PVOID HwDeviceExtension,
    PVOID VirtualAddress,
    HANDLE ProcessHandle
    );

VIDEOPORT_API
VP_STATUS
DlCreateSecondaryDisplay(
    IN PVOID HwDeviceExtension,
    IN OUT PVOID *SecondaryDeviceExtension,
    IN ULONG ulFlag
    );

VIDEOPORT_API
VP_STATUS
DlQueryServices(
    IN PVOID HwDeviceExtension,
    IN VIDEO_PORT_SERVICES ServicesType,
    IN OUT PINTERFACE Interface
    );

VIDEOPORT_API
BOOLEAN
DlIsNoVesa( 
    VOID 
    );

VIDEOPORT_API
ULONG
DlGetBusData(
    PVOID HwDeviceExtension,
    BUS_DATA_TYPE BusDataType,
    ULONG SlotNumber,
    PVOID Buffer,
    ULONG Offset,
    ULONG Length
    );

VIDEOPORT_API
VP_STATUS
DlGetVgaStatus(
    PVOID HwDeviceExtension,
    OUT PULONG VgaStatus
    );

VIDEOPORT_API
VP_STATUS
DlVerifyAccessRanges(
    PVOID HwDeviceExtension,
    ULONG NumAccessRanges,
    PVIDEO_ACCESS_RANGE AccessRanges
    );

VIDEOPORT_API
BOOLEAN
DlCheckForDeviceExistence(
    IN PVOID HwDeviceExtension,
    IN USHORT VendorId,
    IN USHORT DeviceId,
    IN UCHAR RevisionId,
    IN USHORT SubVendorId,
    IN USHORT SubSystemId,
    IN ULONG Flags
    );

BOOLEAN
DlGetAgpServices(
    IN PVOID HwDeviceExtension,
    IN PVIDEO_PORT_AGP_SERVICES AgpServices
    );

VIDEOPORT_API
BOOLEAN
DlLockPages(
    IN      PVOID                   HwDeviceExtension,
    IN OUT  PVIDEO_REQUEST_PACKET   pVrp,
    IN      PEVENT                  pUEvent,
    IN      PEVENT                  pDisplayEvent,
    IN      DMA_FLAGS               DmaFlags
    );

VIDEOPORT_API
BOOLEAN
DlSignalDmaComplete(
    IN  PVOID HwDeviceExtension,
    IN  PDMA  pDmaHandle
    );


VIDEOPORT_API
PVOID
DlAllocateContiguousMemory(
    IN  PVOID            HwDeviceExtension,
    IN  ULONG            NumberOfBytes,
    IN  PHYSICAL_ADDRESS HighestAcceptableAddress
    );

VIDEOPORT_API
PVOID
DlGetRomImage(
    IN PVOID HwDeviceExtension,
    IN PVOID Unused1,
    IN ULONG Unused2,
    IN ULONG Length
    );

VIDEOPORT_API
PVOID
DlGetAssociatedDeviceExtension(
    IN PVOID DeviceObject
    );

VIDEOPORT_API
ULONG
DlGetAssociatedDeviceID(
    IN PVOID DeviceObject
    );

VIDEOPORT_API
VOID
DlAcquireDeviceLock(
    IN PVOID HwDeviceExtension
    );

VIDEOPORT_API
VOID
DlReleaseDeviceLock(
    IN PVOID HwDeviceExtension
    );

VIDEOPORT_API
LONG
FASTCALL
DlInterlockedIncrement(
    IN PLONG Addend
    );

VIDEOPORT_API
LONG
FASTCALL
DlInterlockedDecrement(
    IN PLONG Addend
    );

VIDEOPORT_API
LONG
FASTCALL
DlInterlockedExchange(
    IN OUT PLONG Target,
    IN LONG Value
    );

VIDEOPORT_API
BOOLEAN
DlQueueDpc(
    IN PVOID HwDeviceExtension,
    IN PVOID CallbackRoutine,
    IN PVOID Context
    );

VIDEOPORT_API
VP_STATUS
DlEnumerateChildren(
    IN PVOID HwDeviceExtension,
    IN PVOID Reserved
    );

VIDEOPORT_API
VP_STATUS
DlStartDma(
    IN PVOID HwDeviceExtension,
    IN PVP_DMA_ADAPTER VpDmaAdapter,
    IN PVOID Mdl,
    IN ULONG Offset,
    IN OUT PULONG pLength,
    IN PEXECUTE_DMA ExecuteDmaRoutine,
    IN PVOID Context,
    IN BOOLEAN WriteToDevice
    );

VIDEOPORT_API
VP_STATUS
DlCompleteDma(
    IN PVOID HwDeviceExtension,
    IN PVP_DMA_ADAPTER VpDmaAdapter,
    IN PVP_SCATTER_GATHER_LIST VpScatterGather,
    IN BOOLEAN WriteToDevice
    );

VIDEOPORT_API
VP_STATUS
DlCreateEvent(
    IN PVOID HwDeviceExtension,
    IN ULONG EventFlag,
    IN PVOID Unused,
    OUT PEVENT *ppEvent
    );

VIDEOPORT_API
VP_STATUS
DlDeleteEvent(
    IN PVOID HwDeviceExtension,
    IN PEVENT pEvent
    );
    
VIDEOPORT_API
LONG
DlSetEvent(
    IN PVOID HwDeviceExtension,
    IN PEVENT pEvent
    );
    
VIDEOPORT_API
VOID
DlClearEvent(
    IN PVOID HwDeviceExtension,
    IN PEVENT pEvent
    );

VIDEOPORT_API
LONG
DlReadStateEvent(
    IN PVOID HwDeviceExtension,
    IN PEVENT pEvent
    );

VIDEOPORT_API
VP_STATUS
DlWaitForSingleObject(
    IN PVOID HwDeviceExtension,
    IN PVOID Object,
    IN PLARGE_INTEGER Timeout
    );

VIDEOPORT_API
VP_STATUS
DlCreateSpinLock(
    IN PVOID HwDeviceExtension,
    OUT PSPIN_LOCK *SpinLock
    );

VIDEOPORT_API
VP_STATUS
DlDeleteSpinLock(
    IN PVOID HwDeviceExtension,
    IN PSPIN_LOCK SpinLock
    );

VIDEOPORT_API
VOID
DlAcquireSpinLock(
    IN PVOID HwDeviceExtension,
    IN PSPIN_LOCK SpinLock,
    OUT PUCHAR OldIrql
    );

VIDEOPORT_API
VOID
DlAcquireSpinLockAtDpcLevel(
    IN PVOID HwDeviceExtension,
    IN PSPIN_LOCK SpinLock
    );

VIDEOPORT_API
VOID
DlReleaseSpinLock(
    IN PVOID HwDeviceExtension,
    IN PSPIN_LOCK SpinLock,
    IN UCHAR NewIrql
    );

VIDEOPORT_API
VOID
DlReleaseSpinLockFromDpcLevel(
    IN PVOID HwDeviceExtension,
    IN PSPIN_LOCK SpinLock
    );

VIDEOPORT_API
VP_STATUS
DlFlushRegistry(
    PVOID HwDeviceExtension
    );

VIDEOPORT_API
LONGLONG
DlQueryPerformanceCounter(
    IN PVOID HwDeviceExtension,
    OUT PLONGLONG PerformanceFrequency OPTIONAL
    );

VIDEOPORT_API
VP_STATUS
DlGetVersion(
    IN PVOID HwDeviceExtension,
    IN OUT PVPOSVERSIONINFO pVpOsVersionInfo
    );

VIDEOPORT_API
VP_STATUS
DlRegisterBugcheckCallback(
    IN PVOID HwDeviceExtension,
    IN ULONG BugcheckCode,
    IN PVIDEO_BUGCHECK_CALLBACK Callback,
    IN ULONG BugcheckDataSize
    );

VIDEOPORT_API
VOID
DlQuerySystemTime(
    OUT PLARGE_INTEGER CurrentTime
    );

VIDEOPORT_API
VP_STATUS
DlGetAccessRanges(
    PVOID HwDeviceExtension,
    ULONG NumRequestedResources,
    PIO_RESOURCE_DESCRIPTOR RequestedResources OPTIONAL,
    ULONG NumAccessRanges,
    PVIDEO_ACCESS_RANGE AccessRanges,
    PVOID VendorId,
    PVOID DeviceId,
    PULONG Slot
    );
    
#endif

