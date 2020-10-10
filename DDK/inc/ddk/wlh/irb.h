/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    irb.h

Abstract:

    Defines the interface between the Ataport and the ATA miniport drivers.

Authors:

Revision History:

--*/

#ifndef _NTIRB_
#define _NTIRB_

//
// pre-defined channel numbers for P-ATA
//
#define PRIMARY_CHANNEL_NUMBER      0
#define SECONDARY_CHANNEL_NUMBER    1

//
// max number of devices per channel for P-ATA
//
#define MAX_IDE_DEVICE  2

#define MAX_IDE_LUN     8

#define IDE_UNTAGGED  0xFF
#define IDE_UNINITIALIZED_VALUE (-1)

#define IDE_REG_SZ          (1)
#define IDE_REG_BINARY      (3)
#define IDE_REG_DWORD       (4)

typedef PHYSICAL_ADDRESS IDE_PHYSICAL_ADDRESS, *PIDE_PHYSICAL_ADDRESS;

//
// Notification Event Types
//
typedef enum _IDE_NOTIFICATION_TYPE {
    IdeDeviceArrival,
    IdeDeviceRemoval,
    IdePowerStateChange
} IDE_NOTIFICATION_TYPE, *PIDE_NOTIFICATION_TYPE;

//
// Callback types supported by the port driver
//
typedef enum _IDE_CALLBACK_TYPE {
    IdeTimerRoutine,
    IdeWorkerRoutine,
    IdeSynchronizedRoutine,
    IdeControllerSyncRoutine,
    IdeMaxCallbackType
} IDE_CALLBACK_TYPE, *PIDE_CALLBACK_TYPE;

//
// Device type
//
typedef enum  {
    DeviceUnknown = 0,
    DeviceIsAta,
    DeviceIsAtapi,
    DeviceNotExist
} IDE_DEVICE_TYPE;

//
// addressing mode
//
typedef enum {
    UnknownMode = 0,
    ChsMode,
    LbaMode,
    Lba48BitMode
}ATA_ADDRESS_TRANSLATION;

//
// control action for ChannelControl
//
typedef enum {
    IdeStart = 0,
    IdeStop,
    IdePowerUp,
    IdePowerDown
} IDE_CONTROL_ACTION;

//
// device power states
//
typedef enum {
    IdePowerUnSpecified = 0,
    IdePowerD0, 
    IdePowerD3
} IDE_POWER_STATE;

//
// power transition information
// defines a transition from 
// currentPowerState -> DesiredPowerState
//
typedef struct _IDE_POWER_INFO {
    IDE_POWER_STATE CurrentPowerState;
    IDE_POWER_STATE DesiredPowerState;
} IDE_POWER_INFO, *PIDE_POWER_INFO;

//
// task file register contents
//
typedef struct _IDEREGISTERS {

    //
    // ATA features/error register
    //
    UCHAR bFeaturesReg;

    //
    // sector count
    //
    UCHAR bSectorCountReg;

    //
    // block number (7:0)
    //
    UCHAR bSectorNumberReg;

    //
    // cylinder number (7:0) or LBA (15:8) 
    //
    UCHAR bCylLowReg;

    //
    // cylinder number (15:8) or LBA (23:16) 
    //
    UCHAR bCylHighReg;

    //
    // device/Head and LBA (27:24)
    //
    UCHAR bDriveHeadReg;

    //
    // command/status register
    //
    UCHAR bCommandReg;

    //
    // Reserved for future use. Shall be 0
    //
    UCHAR bReserved;

} IDEREGISTERS, *PIDEREGISTERS;

//
// task file (to hold 48 bit)
//
typedef struct _IDE_TASK_FILE {
    IDEREGISTERS Current;
    IDEREGISTERS Previous;
} IDE_TASK_FILE, *PIDE_TASK_FILE;

typedef UCHAR IRB_STATUS;

//
// irb
//
typedef struct _IDE_REQUEST_BLOCK {

    //
    // IRB_FUNCTION_XXX
    //
    USHORT Function;

    //
    // IRB_STATUS_XXX
    //
    UCHAR IrbStatus;

    //
    // contents of the status and error registers
    // at the completion of the command
    //
    UCHAR AtaStatus;
    UCHAR AtaError;

    //
    // channel, target and lun ids uniquely identify the target device
    //
    UCHAR Channel;
    UCHAR TargetId;
    UCHAR Lun;

    //
    // sense info buffer length
    //
    UCHAR SenseInfoBufferLength;    

    //
    // holds the queue tag
    //
    UCHAR QueueTag;

    //
    // Irb Flags
    //
    USHORT IrbFlags;                 

    //
    // timeout
    //
    ULONG TimeOutValue;             

    //
    // data transfer length
    //
    ULONG DataTransferLength;       

    //
    // irb extension
    //
    PVOID IrbExtension;

    //
    // data buffer
    //
    PVOID DataBuffer;               

    //
    // sense buffer
    //
    PVOID SenseInfoBuffer;          

    //
    // Used for queueing irbs
    //
    PVOID NextIrb;

    //
    // For future use (shall be set to NULL)
    //
    PVOID Reserved;

    //
    // task file for ATA devices    or 
    // CDB for ATAPI devices        or
    // power transition information or
    // an array of chars
    // (determined by IrbFunction)
    //
    union {

        //
        // ATA Task file register contents
        //
        IDE_TASK_FILE IdeTaskFile;

        //
        // CDB for ATAPI devices
        //
        UCHAR Cdb[16];

        //
        // power transitition information
        //
        IDE_POWER_INFO PowerChange;

        //
        // array of 16 uchars
        //
        UCHAR AsUChar[16];
    };

} IDE_REQUEST_BLOCK, *PIDE_REQUEST_BLOCK;

//
// irb status
//
#define IRB_STATUS_PENDING              0x0
#define IRB_STATUS_SUCCESS              0x1
#define IRB_STATUS_DATALENGTH_MISMATCH  0x2
#define IRB_STATUS_DEVICE_ERROR         0x3
#define IRB_STATUS_INVALID_REQUEST      0x4
#define IRB_STATUS_BUS_RESET            0x5
#define IRB_STATUS_SELECTION_TIMEOUT    0x6
#define IRB_STATUS_BUSY                 0x7

//
// bit mask to indicate valid sense info
//
#define IRB_STATUS_AUTOSENSE_VALID      0x20

//
// 0x40 and above are reserved for the port driver
//
#define IRB_STATUS_INTERNAL_ERROR       0x40

//
// irb function
//
#define IRB_FUNCTION_ATA_COMMAND        0x80
#define IRB_FUNCTION_ATA_IDENTIFY       0x81
#define IRB_FUNCTION_ATA_READ           0x82
#define IRB_FUNCTION_ATA_WRITE          0x83
#define IRB_FUNCTION_ATA_FLUSH          0x84
#define IRB_FUNCTION_ATA_SMART          0x85

#define IRB_FUNCTION_ATAPI_COMMAND      0x100
#define IRB_FUNCTION_REQUEST_SENSE      0x101 

#define IRB_FUNCTION_MINIPORT_COMMAND   0x200
#define IRB_FUNCTION_ADAPTER_FLUSH      0x201
#define IRB_FUNCTION_SHUTDOWN           0x202
#define IRB_FUNCTION_POWER_CHANGE       0x203
#define IRB_FUNCTION_LUN_RESET          0x204

//
// irb flags
//
#define IRB_FLAGS_DRDY_REQUIRED         0x1
#define IRB_FLAGS_USE_DMA               0x2
#define IRB_FLAGS_MAP_BUFFERS           0x4
#define IRB_FLAGS_48BIT                 0x8
#define IRB_FLAGS_DATA_IN               0x40
#define IRB_FLAGS_DATA_OUT              0x80

//
// helper macros
//
#define IsAtapiCommand(irb)     (irb->Function & IRB_FUNCTION_ATAPI_COMMAND)
#define IsAtaCommand(irb)       (irb->Function & IRB_FUNCTION_ATA_COMMAND)
#define IsMiniportCommand(irb)  (irb->Function & IRB_FUNCTION_MINIPORT_COMMAND)
#define IsRequestSenseIrb(irb)  (irb->Function == IRB_FUNCTION_REQUEST_SENSE)

#define NeedRequestSense(irb) \
    (IsAtapiCommand(irb) && \
     !IsRequestSenseIrb(irb) && \
     (irb->IrbStatus == IRB_STATUS_DEVICE_ERROR) && \
     (irb->SenseInfoBuffer != NULL) && \
     (irb->SenseInfoBufferLength > 0))

#define IRB_USES_DMA(irb)       (irb->IrbFlags & IRB_FLAGS_USE_DMA)

#define MARK_IRB_FOR_DMA(irb)   (irb->IrbFlags |= IRB_FLAGS_USE_DMA)
#define MARK_IRB_FOR_PIO(irb)   (irb->IrbFlags &= ~IRB_FLAGS_USE_DMA)

#define IRB_FOR_DATA_TRANSFER(irb) \
    (irb->IrbFlags & (IRB_FLAGS_DATA_IN | IRB_FLAGS_DATA_OUT))
    
#define GET_IRB_CURRENT_REG(irb)        (&((irb->IdeTaskFile).Current))
#define GET_IRB_PREVIOUS_REG(irb)       (&((irb->IdeTaskFile).Previous))

#define GET_CURRENT_REG(taskFile)       (&(taskFile)->Current)
#define GET_PREVIOUS_REG(taskFile)      (&(taskFile)->Previous)

#define GetIrbErrorReg(irb) (irb->AtaError)
#define GetIrbStatusReg(irb) (irb->AtaStatus)
#define SetIrbCommandReg(irb, cmd) (irb->IdeTaskFile.Current.bCommandReg=cmd)

//
// TargetId >= 1 implies slave device
//
#define SetIrbDeviceReg(irb, val) \
    (irb->IdeTaskFile.Current.bDriveHeadReg = ((irb->TargetId == 0x0) ? (0xA0 | val) : (0xB0 | val)))

//
// algorithm used by the port driver to set the irbFunction
// for an ATA command
//
#define IdeMapAtaCommandToIrbFunction(AtaCommand, irbFunc) \
{ \
    switch (AtaCommand) { \
    case IDE_COMMAND_IDENTIFY: \
    case IDE_COMMAND_ATAPI_IDENTIFY: \
        irbFunc = IRB_FUNCTION_ATA_IDENTIFY; \
        break; \
    case IDE_COMMAND_READ: \
    case IDE_COMMAND_READ_MULTIPLE: \
    case IDE_COMMAND_READ_DMA: \
    case IDE_COMMAND_READ_EXT: \
    case IDE_COMMAND_READ_DMA_EXT: \
    case IDE_COMMAND_READ_MULTIPLE_EXT: \
        irbFunc = IRB_FUNCTION_ATA_READ; \
        break; \
    case IDE_COMMAND_WRITE: \
    case IDE_COMMAND_WRITE_MULTIPLE: \
    case IDE_COMMAND_WRITE_DMA: \
    case IDE_COMMAND_WRITE_EXT: \
    case IDE_COMMAND_WRITE_DMA_EXT: \
    case IDE_COMMAND_WRITE_MULTIPLE_EXT: \
        irbFunc = IRB_FUNCTION_ATA_WRITE; \
        break; \
    case IDE_COMMAND_CHECK_POWER: \
    case IDE_COMMAND_FLUSH_CACHE: \
    case IDE_COMMAND_FLUSH_CACHE_EXT: \
        irbFunc = IRB_FUNCTION_ATA_FLUSH;\
        break; \
    case IDE_COMMAND_SMART: \
        irbFunc = IRB_FUNCTION_ATA_SMART; \
        break;\
    default:\
        irbFunc = IRB_FUNCTION_ATA_COMMAND;\
        break;\
    } \
}

//
// scatter-gather list
//
typedef struct _IDE_SCATTER_GATHER_ELEMENT {
    IDE_PHYSICAL_ADDRESS Address;
    ULONG Length;
    ULONG_PTR Reserved;
} IDE_SCATTER_GATHER_ELEMENT, *PIDE_SCATTER_GATHER_ELEMENT;

typedef struct _IDE_SCATTER_GATHER_LIST {
    ULONG NumberOfElements;
    ULONG_PTR Reserved;
    IDE_SCATTER_GATHER_ELEMENT Elements[];
} IDE_SCATTER_GATHER_LIST, *PIDE_SCATTER_GATHER_LIST;

//
// task file register addresses
//
typedef struct _IDE_REGISTERS_1 {
    PUCHAR RegistersBaseAddress;

    PUSHORT Data;

    union {
        PUCHAR Error;
        PUCHAR Features;
    };

    union {
        PUCHAR BlockCount;
        PUCHAR InterruptReason;
    };

    PUCHAR BlockNumber;

    union {
        PUCHAR CylinderLow;
        PUCHAR ByteCountLow;
    };

    union {
        PUCHAR CylinderHigh;
        PUCHAR ByteCountHigh;
    };

    PUCHAR DriveSelect;
    PUCHAR Command;
} IDE_REGISTERS_1, *PIDE_REGISTERS_1;

//
// device control register addresses
//
typedef struct _IDE_REGISTERS_2 {
    PUCHAR RegistersBaseAddress;

    PUCHAR DeviceControl;
    PUCHAR DriveAddress;
} IDE_REGISTERS_2, *PIDE_REGISTERS_2;

//
// access range that indicates the resources
//
typedef struct _IDE_ACCESS_RANGE {
    IDE_PHYSICAL_ADDRESS RangeStart;
    ULONG            RangeLength;
    BOOLEAN          InMemory;
} IDE_ACCESS_RANGE, *PIDE_ACCESS_RANGE;

//
// the miniport's error log entry
//
typedef struct _IDE_ERROR_LOG_ENTRY {
    UCHAR IrbStatus;
    UCHAR Channel;
    UCHAR TargetId;
    UCHAR Lun;
    UCHAR UniqueId;
    UCHAR DumpDataSize;
    UCHAR DumpData[1];
} IDE_ERROR_LOG_ENTRY, *PIDE_ERROR_LOG_ENTRY;

//
// device characterstics flags
//

//
// Indicates that the drive has the 'removable' bit set in
// identify data (offset 128)
//
#define DFLAGS_REMOVABLE_MEDIA       (1 << 0)    
                                              
//
// Indicates whether device interrupts as DRQ is set after   
// receiving Atapi Packet Command
//
#define DFLAGS_INT_DRQ               (1 << 1)    
                                                 
//
// Device supports media status notification
//
#define DFLAGS_MSN_SUPPORT           (1 << 2)    


typedef struct _IDE_DEVICE_PARAMETERS {

    //
    // size of this structure
    //
    USHORT Version;

    //
    // device type (ata, atapi etc)
    //
    IDE_DEVICE_TYPE IdeDeviceType;

    //
    // target id
    //
    UCHAR TargetId;

    //
    // Number of Luns
    //
    UCHAR MaximumLun;

    //
    // number of requests the miniport can handle 
    // at a time for this device
    //
    UCHAR NumberOfOverlappedRequests;

    //
    // max number of blocks that can be transferred
    // using read/write multiple command
    //
    UCHAR MaxBlockXfer;

    //
    // device characteristics (removable etc)
    //
    USHORT DeviceCharacteristics;

    //
    // Geometry
    //
    ATA_ADDRESS_TRANSLATION AddressTranslation;

    union {
        LARGE_INTEGER MaxLba;
        struct {
            USHORT NumCylinders;
            USHORT NumHeads;
            USHORT NumSectorsPerTrack;
            USHORT Reserved;
        } Chs;
    };

    //
    // number of bytes per sector
    //
    ULONG BytesPerSector;

    //
    // The transfer modes supported by this device
    //
    ULONG TransferModeSupported;

    //
    // The selected transfer mode for this device
    //
    ULONG TransferModeSelected;

} IDE_DEVICE_PARAMETERS, *PIDE_DEVICE_PARAMETERS;

typedef
BOOLEAN
(*IDE_HW_INITIALIZE) (
    IN PVOID ChannelExtension,
    IN OUT PIDE_DEVICE_PARAMETERS DeviceParameters,
    IN PIDENTIFY_DEVICE_DATA IdentifyData
    );

typedef
BOOLEAN
(*IDE_HW_STARTIO) (
    IN PVOID ChannelExtension,
    IN PIDE_REQUEST_BLOCK Irb
    );

typedef
BOOLEAN
(*IDE_HW_BUILDIO) (
    IN PVOID ChannelExtension,
    IN PIDE_REQUEST_BLOCK Irb
    );

typedef
BOOLEAN
(*IDE_HW_INTERRUPT) (
    IN PVOID ChannelExtension
    );

typedef
VOID
(*IDE_HW_DPC) (
    IN PVOID ChannelExtension
    );

typedef
BOOLEAN
(*IDE_HW_RESET) (
    IN PVOID ChannelExtension
    );

typedef
BOOLEAN
(*IDE_HW_CONTROL) (
    IN PVOID ChannelExtension,
    IN IDE_CONTROL_ACTION ControlAction,
    IN PVOID Parameters
    );

//
// miniport hardware resources
//
typedef struct _IDE_MINIPORT_RESOURCES{

    //
    // Number of access ranges
    //
    ULONG NumberOfAccessRanges;

    //
    // array of access range elements.
    //
    PIDE_ACCESS_RANGE IdeAccessRange;

} IDE_MINIPORT_RESOURCES, *PIDE_MINIPORT_RESOURCES;

typedef struct _IDE_CHANNEL_CONFIGURATION {

    //
    // Input parameters
    //

    //
    // version
    //
    USHORT Version;

    //
    // The channel number
    //
    UCHAR ChannelNumber;

    //
    // Output parameters
    //

    //
    // Number of overlapped requests the channel can handle
    //
    UCHAR NumberOfOverlappedRequests;

    //
    // The maximum targetId. 
    // Typically (MaxNumDevices - 1)
    //
    UCHAR MaxTargetId;

    //
    // Always TRUE
    //
    BOOLEAN SyncWithIsr;

    //
    // Always TRUE
    //
    BOOLEAN SupportsWmi;

    //
    // reserved for future use
    //
    PVOID Reserved1;

    //
    // mini driver entry points
    //
    IDE_HW_INITIALIZE    IdeHwInitialize;
    IDE_HW_BUILDIO       IdeHwBuildIo;
    IDE_HW_STARTIO       IdeHwStartIo;
    IDE_HW_INTERRUPT     IdeHwInterrupt;
    IDE_HW_RESET         IdeHwReset;
    IDE_HW_CONTROL       IdeHwControl;

} IDE_CHANNEL_CONFIGURATION, *PIDE_CHANNEL_CONFIGURATION;

typedef BOOLEAN
    (* IDE_CHANNEL_INIT) (
        PVOID ChannelExtension,
        OUT PIDE_CHANNEL_CONFIGURATION ChannelInfo,
        PVOID InitContext
        );

typedef struct _IDE_TRANSFER_MODE_PARAMETERS {

    //
    // Input Parameters
    //          
          
    //
    // IDE Channel Number. 
    //                                       
    UCHAR ChannelNumber;

    //
    // Indicate whether devices are present
    //                                  
    IDE_DEVICE_TYPE DeviceType[MAX_IDE_DEVICE];
    
    //
    // Indicate whether devices support IO Ready Line
    //                                                
    BOOLEAN IoReadySupported[MAX_IDE_DEVICE];

    //
    // Indicate the data transfer modes devices support
    //               
    ULONG DeviceTransferModeSupported[MAX_IDE_DEVICE];

    //
    // Indicate devices' current data transfer modes
    //
    ULONG DeviceTransferModeCurrent[MAX_IDE_DEVICE];

    //
    // Output Parameters
    //          
                      
    //
    // Indicate devices' data transfer modes chosen by
    // the miniport 
    //
    ULONG DeviceTransferModeSelected[MAX_IDE_DEVICE];

} IDE_TRANSFER_MODE_PARAMETERS, *PIDE_TRANSFER_MODE_PARAMETERS;

typedef BOOLEAN
    (*IDE_TRANSFER_MODE_SELECT) (
        IN PVOID ControllerExtension,
        IN OUT PIDE_TRANSFER_MODE_PARAMETERS TransferModeSelect
        );

//
// possible channel state
//         
typedef enum {
    ChannelStateDisabled = 0,
    ChannelStateEnabled,
    ChannelStateUnKnown
} ATA_CHANNEL_STATE;

typedef ATA_CHANNEL_STATE
    (*IDE_CHANNEL_ENABLED) (
        IN PVOID ControllerExtension,
        IN ULONG Channel
        );

typedef struct _IDE_CONTROLLER_CONFIGURATION {

    //
    // size of this structure
    //
    USHORT Version;

    //
    // number of IDE channels
    //
    UCHAR NumberOfChannels;

    //
    // number of elements in the scatter gather list
    //
    UCHAR NumberOfPhysicalBreaks;

    //
    // maximum transfer bytes supported by the controller
    //
    ULONG MaximumTransferLength;

    //
    // TRUE if the controller is in native mode
    //
    BOOLEAN NativeModeEnabled;

    //
    // TRUE if the controller supports 64 bit DMA
    //
    BOOLEAN Dma64BitAddress;

    //
    // TRUE if the controller is a bus master
    //
    BOOLEAN BusMaster;

    //
    // Reserved for future use
    //
    BOOLEAN Reserved;


} IDE_CONTROLLER_CONFIGURATION, *PIDE_CONTROLLER_CONFIGURATION;

typedef
BOOLEAN
(*IDE_ADAPTER_CONTROL) (
    IN PVOID ControllerExtension,
    IN IDE_CONTROL_ACTION ControlAction,
    IN PVOID Parameters
    );

typedef struct _IDE_CONTROLLER_INTERFACE {

    //
    //  Size of this structure
    //
    USHORT Version;

    //
    //  Reserved for future use
    //
    USHORT Reserved;
    
    // Size of the controller device extension
    //
    ULONG ControllerExtensionSize;

    //
    // Size of the channel extension
    //
    ULONG ChannelExtensionSize;

    //
    // Alignment requirement
    //
    ULONG AlignmentMask;

    //
    // mini driver entry point
    //

    //
    // init routine for each channel
    //
    IDE_CHANNEL_INIT AtaChannelInitRoutine;

    //
    // channelEnabled routine
    //
    IDE_CHANNEL_ENABLED AtaControllerChannelEnabled;

    //
    // Transfer mode select routine
    //
    IDE_TRANSFER_MODE_SELECT AtaControllerTransferModeSelect;

    //
    // Adapter control routine
    //
    IDE_ADAPTER_CONTROL AtaAdapterControl;
    
} IDE_CONTROLLER_INTERFACE, *PIDE_CONTROLLER_INTERFACE;

//
// Transfer mode support bit masks
//
#define PIO_MODE0           (1 << 0)
#define PIO_MODE1           (1 << 1)
#define PIO_MODE2           (1 << 2)
#define PIO_MODE3           (1 << 3)
#define PIO_MODE4           (1 << 4)

#define SWDMA_MODE0         (1 << 5)
#define SWDMA_MODE1         (1 << 6)
#define SWDMA_MODE2         (1 << 7)

#define MWDMA_MODE0         (1 << 8)
#define MWDMA_MODE1         (1 << 9)
#define MWDMA_MODE2         (1 << 10)

#define UDMA_MODE0          (1 << 11)
#define UDMA_MODE1          (1 << 12)
#define UDMA_MODE2          (1 << 13)
#define UDMA_MODE3          (1 << 14)
#define UDMA_MODE4          (1 << 15)
#define UDMA_MODE5          (1 << 16)

#define PIO_SUPPORT         (PIO_MODE0      | PIO_MODE1     | PIO_MODE2    | PIO_MODE3     | PIO_MODE4)
#define SWDMA_SUPPORT       (SWDMA_MODE0    | SWDMA_MODE1   | SWDMA_MODE2)
#define MWDMA_SUPPORT       (MWDMA_MODE0    | MWDMA_MODE1   | MWDMA_MODE2)
#define UDMA_SUPPORT        (UNINITIALIZED_TRANSFER_MODE & (~(PIO_SUPPORT | SWDMA_SUPPORT | MWDMA_SUPPORT)))

#define DMA_SUPPORT         (SWDMA_SUPPORT  | MWDMA_SUPPORT | UDMA_SUPPORT)
#define ALL_MODE_SUPPORT    (PIO_SUPPORT | DMA_SUPPORT)

#define PIO0                        0
#define PIO1                        1
#define PIO2                        2
#define PIO3                        3
#define PIO4                        4
#define SWDMA0                      5
#define SWDMA1                      6
#define SWDMA2                      7
#define MWDMA0                      8
#define MWDMA1                      9
#define MWDMA2                      10
#define UDMA0                       11

#ifdef MAX_XFER_MODE
#undef MAX_XFER_MODE
#endif

#define MAX_XFER_MODE               18
#define UNINITIALIZED_CYCLE_TIME    0xffffffff
#define UNINITIALIZED_TRANSFER_MODE 0x7fffffff
#define IS_DEFAULT(mode)    (!(mode & 0x80000000))

#ifdef GenTransferModeMask
#undef GenTransferModeMask
#endif

#define GenTransferModeMask(i, mode) {\
    ULONG temp=0xffffffff; \
    mode = (temp >> (31-(i)));\
}

#define GetHighestBitSet(mode, i) {\
    ULONG temp = (mode); \
    i=0; \
    while (temp) { \
        temp >>= 1; \
        i++; \
    } \
    i--; \
}

ULONG
AtaPortInitializeEx(
    IN PVOID                     DriverObject,
    IN PVOID                     RegistryPath,
    IN PIDE_CONTROLLER_INTERFACE ControllerInterface
    );

//
// To query PCI IDE config space data
//                                    
ULONG
AtaPortGetBusData(
    IN PVOID ControllerExtension,
    IN PVOID Buffer,
    IN ULONG ConfigDataOffset,
    IN ULONG BufferLength
    );

//
// To save PCI IDE config space data
//                                    
ULONG
AtaPortSetBusData(
    IN PVOID ControllerExtension,
    IN PVOID Buffer,
    IN ULONG ConfigDataOffset,
    IN ULONG BufferLength
    );

PIDE_MINIPORT_RESOURCES
AtaPortGetControllerResources (
    IN PVOID ControllerExtension
    );
    
PIDE_SCATTER_GATHER_LIST
AtaPortGetScatterGatherList (
    IN PVOID ChannelExtension,
    IN PIDE_REQUEST_BLOCK   Irb
    );

IDE_PHYSICAL_ADDRESS
AtaPortGetPhysicalAddress (
    IN PVOID                ChannelExtension,
    IN PIDE_REQUEST_BLOCK   Irb,
    IN PVOID                VirtualAddress,
    OUT ULONG *             Length
    );

PVOID
AtaPortGetDeviceBase (
    IN PVOID ChannelExtension,
    IN IDE_PHYSICAL_ADDRESS IoAddress,
    IN ULONG NumberOfBytes
    );

VOID
AtaPortCompleteRequest(
    PVOID ChannelExtension,
    PIDE_REQUEST_BLOCK Irb
    );

VOID
AtaPortCompleteAllActiveRequests(
    IN PVOID ChannelExtension,
    IN UCHAR Target,
    IN UCHAR Lun,
    IN UCHAR IrbStatus
    );

VOID
AtaPortNotification(
    IN IDE_NOTIFICATION_TYPE NotificationType,
    IN PVOID ChannelExtension,
    ...
    );

VOID
AtaPortMoveMemory(
    IN PVOID WriteBuffer,
    IN PVOID ReadBuffer,
    IN ULONG Length
    );

IDE_PHYSICAL_ADDRESS
AtaPortConvertUlongToPhysicalAddress(
    IN ULONG_PTR UlongAddress
    );

ULONG
AtaPortConvertPhysicalAddressToUlong(
    IN IDE_PHYSICAL_ADDRESS Address
    );

VOID
AtaPortStallExecution(
    IN ULONG Delay
    );

PVOID
AtaPortGetUnCachedExtension (
    IN PVOID ChannelExtension,
    IN ULONG UncachedExtensionSize,
    IN ULONG IrbExtensionSize
    );

VOID
AtaPortDebugPrint(
    ULONG DebugPrintLevel,
    PCCHAR DebugMessage,
    ...
    );

VOID
AtaPortLogError(
    IN PVOID ChannelExtension,
    IN PIDE_ERROR_LOG_ENTRY ErrorLogEntry
    );

PIDE_REQUEST_BLOCK
AtaPortBuildRequestSenseIrb(
    IN PVOID ChannelExtension,
    IN PIDE_REQUEST_BLOCK Irb
    );

VOID
AtaPortReleaseRequestSenseIrb(
    IN PVOID ChannelExtension,
    IN PIDE_REQUEST_BLOCK Irb
    );

VOID
AtaPortDeviceStateChange (
    IN PVOID ChannelExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun,
    IN ULONG BusyTimeout
    );

BOOLEAN
AtaPortRequestCallback (
    IN IDE_CALLBACK_TYPE CallbackType,
    IN PVOID ChannelExtension,
    IN IDE_HW_DPC CallBackRoutine,
    IN ULONG TimerValue
    );

PVOID
AtaPortRegistryAllocateBuffer (
    IN PVOID ChannelExtension,
    IN ULONG BufferSize
    );

VOID
AtaPortRegistryFreeBuffer (
    IN PVOID ChannelExtension,
    IN PVOID Buffer
    );

BOOLEAN
AtaPortInitializeQueueTag (
    IN PVOID DeviceExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun,
    IN UCHAR MaxQueueTag
    );

UCHAR
AtaPortAllocateQueueTag (
    IN PVOID DeviceExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun
    );

VOID
AtaPortReleaseQueueTag (
    IN PVOID DeviceExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun,
    IN UCHAR QueueTag
    );

BOOLEAN
AtaPortRegistryRead (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN BOOLEAN ChannelSubKey,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    );

BOOLEAN
AtaPortRegistryWrite (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN BOOLEAN ChannelSubKey,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    );

BOOLEAN
AtaPortRegistryWriteDeferred (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN BOOLEAN ChannelSubKey,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    );

VOID
__inline
AtaPortDeviceBusy (
    IN PVOID ChannelExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun,
    IN ULONG BusyTimeout
    )
{
    AtaPortDeviceStateChange(ChannelExtension,
                             TargetId,
                             Lun,
                             BusyTimeout
                             );
}

VOID
__inline
AtaPortDeviceReady (
    IN PVOID ChannelExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun
    )
{
    AtaPortDeviceStateChange(ChannelExtension,
                             TargetId,
                             Lun,
                             0
                             );
}

BOOLEAN
__inline
AtaPortRegistryControllerKeyRead (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    )
{
    return AtaPortRegistryRead (ChannelExtension,
                                ControllerNumber,
                                FALSE,
                                ValueName,
                                ValueType,
                                Buffer,
                                BufferLength
                                );
}

BOOLEAN
__inline
AtaPortRegistryControllerKeyWrite (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    )
{
    return AtaPortRegistryWrite (ChannelExtension,
                                 ControllerNumber,
                                 FALSE,
                                 ValueName,
                                 ValueType,
                                 Buffer,
                                 BufferLength
                                 );
}

BOOLEAN
__inline
AtaPortRegistryControllerKeyWriteDeferred (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    )
{
    return AtaPortRegistryWriteDeferred (ChannelExtension,
                                         ControllerNumber,
                                         FALSE,
                                         ValueName,
                                         ValueType,
                                         Buffer,
                                         BufferLength
                                         );
}

BOOLEAN
__inline
AtaPortRegistryChannelSubkeyRead (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    )
{
    return AtaPortRegistryRead (ChannelExtension,
                                ControllerNumber,
                                TRUE,
                                ValueName,
                                ValueType,
                                Buffer,
                                BufferLength
                                );
}

BOOLEAN
__inline
AtaPortRegistryChannelSubkeyWrite (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    )
{
    return AtaPortRegistryWrite (ChannelExtension,
                                 ControllerNumber,
                                 TRUE,
                                 ValueName,
                                 ValueType,
                                 Buffer,
                                 BufferLength
                                 );
}

BOOLEAN
__inline
AtaPortRegistryChannelSubkeyWriteDeferred (
    IN PVOID ChannelExtension,
    IN UCHAR ControllerNumber,
    IN PUCHAR ValueName,
    IN UCHAR ValueType,
    IN OUT PUCHAR Buffer,
    IN OUT PULONG BufferLength
    )
{
    return AtaPortRegistryWriteDeferred (ChannelExtension,
                                         ControllerNumber,
                                         TRUE,
                                         ValueName,
                                         ValueType,
                                         Buffer,
                                         BufferLength
                                         );

}

BOOLEAN
__inline
AtaPortRequestWorkerRoutine (
    IN PVOID ChannelExtension,
    IN IDE_HW_DPC CallBackRoutine
    )
{
    return AtaPortRequestCallback (IdeWorkerRoutine, 
                                   ChannelExtension, 
                                   CallBackRoutine, 
                                   0 
                                   );
}

BOOLEAN
__inline
AtaPortRequestSynchronizedRoutine (
    IN PVOID ChannelExtension,
    IN IDE_HW_DPC CallBackRoutine
    )
{
    return AtaPortRequestCallback (IdeSynchronizedRoutine, 
                                   ChannelExtension, 
                                   CallBackRoutine, 
                                   0 
                                   );
}

BOOLEAN
__inline
AtaPortControllerSyncRoutine (
    IN PVOID ChannelExtension,
    IN IDE_HW_DPC CallBackRoutine
    )
{
    return AtaPortRequestCallback (IdeControllerSyncRoutine, 
                                   ChannelExtension, 
                                   CallBackRoutine, 
                                   0 
                                   );
}

BOOLEAN
__inline
AtaPortRequestTimer (
    IN PVOID ChannelExtension,
    IN IDE_HW_DPC CallBackRoutine,
    IN ULONG TimerValue
    )
{
    return AtaPortRequestCallback(IdeTimerRoutine, 
                                  ChannelExtension, 
                                  CallBackRoutine, 
                                  TimerValue 
                                  );
}

VOID
__inline
AtaPortBusChangeDetected (
    IN PVOID ChannelExtension
    )
{
    AtaPortNotification(IdeDeviceArrival,
                        ChannelExtension,
                        IDE_UNTAGGED,
                        0
                        );
}


VOID
__inline
AtaPortDeviceArrived (
    IN PVOID ChannelExtension,
    IN UCHAR TargetId
    )
{
    AtaPortNotification(IdeDeviceArrival,
                        ChannelExtension,
                        TargetId,
                        0
                        );
}

VOID
__inline
AtaPortDeviceRemoved (
    IN PVOID ChannelExtension,
    IN UCHAR TargetId
    )
{
    AtaPortNotification(IdeDeviceRemoval,
                        ChannelExtension,
                        TargetId,
                        0
                        );
}

VOID
__inline
AtaPortRequestPowerStateChange (
    IN PVOID ChannelExtension,
    IN UCHAR TargetId,
    IN UCHAR Lun,
    IN IDE_POWER_STATE DesiredPowerState
    )
{
    AtaPortNotification(IdePowerStateChange,
                        ChannelExtension,
                        TargetId,
                        Lun,
                        DesiredPowerState
                        );
}

VOID
AtaPortQuerySystemTime (
    OUT PLARGE_INTEGER CurrentTime
    );
    
VOID
AtaPortDebugBreak (
    IN PVOID ChannelExtension
    );
    
//
// The below I/O access routines should be forwarded to the HAL or NTOSKRNL on
// Intel platforms.
//
UCHAR
AtaPortReadPortUchar(
    IN PUCHAR Port
    );

USHORT
AtaPortReadPortUshort(
    IN PUSHORT Port
    );

ULONG
AtaPortReadPortUlong(
    IN PULONG Port
    );

VOID
AtaPortReadPortBufferUchar(
    IN PUCHAR Port,
    IN PUCHAR Buffer,
    IN ULONG  Count
    );

VOID
AtaPortReadPortBufferUshort(
    IN PUSHORT Port,
    IN PUSHORT Buffer,
    IN ULONG Count
    );

VOID
AtaPortReadPortBufferUlong(
    IN PULONG Port,
    IN PULONG Buffer,
    IN ULONG Count
    );

UCHAR
AtaPortReadRegisterUchar(
    IN PUCHAR Register
    );

USHORT
AtaPortReadRegisterUshort(
    IN PUSHORT Register
    );

ULONG
AtaPortReadRegisterUlong(
    IN PULONG Register
    );

VOID
AtaPortReadRegisterBufferUchar(
    IN PUCHAR Register,
    IN PUCHAR Buffer,
    IN ULONG  Count
    );

VOID
AtaPortReadRegisterBufferUshort(
    IN PUSHORT Register,
    IN PUSHORT Buffer,
    IN ULONG Count
    );

VOID
AtaPortReadRegisterBufferUlong(
    IN PULONG Register,
    IN PULONG Buffer,
    IN ULONG Count
    );

VOID
AtaPortWritePortUchar(
    IN PUCHAR Port,
    IN UCHAR Value
    );

VOID
AtaPortWritePortUshort(
    IN PUSHORT Port,
    IN USHORT Value
    );

VOID
AtaPortWritePortUlong(
    IN PULONG Port,
    IN ULONG Value
    );

VOID
AtaPortWritePortBufferUchar(
    IN PUCHAR Port,
    IN PUCHAR Buffer,
    IN ULONG  Count
    );

VOID
AtaPortWritePortBufferUshort(
    IN PUSHORT Port,
    IN PUSHORT Buffer,
    IN ULONG Count
    );

VOID
AtaPortWritePortBufferUlong(
    IN PULONG Port,
    IN PULONG Buffer,
    IN ULONG Count
    );


VOID
AtaPortWriteRegisterUchar(
    IN PUCHAR Register,
    IN UCHAR Value
    );

VOID
AtaPortWriteRegisterUshort(
    IN PUSHORT Register,
    IN USHORT Value
    );

VOID
AtaPortWriteRegisterBufferUchar(
    IN PUCHAR Register,
    IN PUCHAR Buffer,
    IN ULONG  Count
    );

VOID
AtaPortWriteRegisterBufferUshort(
    IN PUSHORT Register,
    IN PUSHORT Buffer,
    IN ULONG Count
    );

VOID
AtaPortWriteRegisterBufferUlong(
    IN PULONG Register,
    IN PULONG Buffer,
    IN ULONG Count
    );

VOID
AtaPortWriteRegisterUlong(
    IN PULONG Register,
    IN ULONG Value
    );

#endif
