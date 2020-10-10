/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

        USBIOCTL.H

Abstract:

   This file defines both kernel and user mode IOCTL
   codes supported by the USB core stack.

   These APIs are the APIS supported by th USB hub driver and the USB bus
   driver AKA USBPORT.

   Typically only user mode applications (usbui) or the hub driver include this
   file, USB drivers should use usbdrivr.h usb bus drivers should include
   usbkern.h

Environment:

    Kernel & user mode

Revision History:

    09-29-95 : created
    01-06-97 : added user mode hub ioctls
    10-31-99 : cleanup and document, jdunn
    1-25-03  : more cleanup and documentation

--*/

#ifndef   __USBIOCTL_H__
#define   __USBIOCTL_H__

#include "usb100.h"

#ifndef FAR
#define FAR
#endif

#include "usbiodef.h"


/*
    IOCTL definitions
*/

/*
   USB kernel Mode IOCTLS
*/

/* see usbdrivr.h */
#define IOCTL_INTERNAL_USB_SUBMIT_URB  \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_SUBMIT_URB,  \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)

/* see usbdrivr.h */
#define IOCTL_INTERNAL_USB_RESET_PORT  \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_RESET_PORT, \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)

/* see usbkern.h */
#define IOCTL_INTERNAL_USB_GET_ROOTHUB_PDO  \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_GET_ROOTHUB_PDO, \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)



#define  USBD_PORT_ENABLED      0x00000001
#define  USBD_PORT_CONNECTED    0x00000002

/* see usbdrivr.h */
#define IOCTL_INTERNAL_USB_GET_PORT_STATUS  \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_GET_PORT_STATUS, \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)

/*
    IOCTL_INTERNAL_USB_ENABLE_PORT is obsolete, drivers should use
    IOCTL_INTERNAL_USB_RESET_PORT
*/

#define IOCTL_INTERNAL_USB_ENABLE_PORT      \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_ENABLE_PORT, \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)

/* see usbdrivr.h */
#define IOCTL_INTERNAL_USB_SUBMIT_IDLE_NOTIFICATION   \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_IDLE_NOTIFICATION,  \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)


/* see usbkern.h */
#define IOCTL_INTERNAL_USB_GET_HUB_COUNT    \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_GET_HUB_COUNT, \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)

/* see usbdrivr.h */
#define IOCTL_INTERNAL_USB_CYCLE_PORT  \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_CYCLE_PORT, \
                                            METHOD_NEITHER,  \
                                            FILE_ANY_ACCESS)

/* see usbkern.h */
#define IOCTL_INTERNAL_USB_GET_HUB_NAME  \
                                            CTL_CODE(FILE_DEVICE_USB,  \
                                            USB_GET_HUB_NAME,  \
                                            METHOD_BUFFERED,  \
                                            FILE_ANY_ACCESS)

/*
    IOCTL_INTERNAL_USB_GET_BUS_INFO is obsolete -- it has been replaced by the
    USB_BUSIFFN_QUERY_BUS_INFORMATION service available thru the usb stack bus
    interface. Drivers should use the bus interface function instead
*/
#define IOCTL_INTERNAL_USB_GET_BUS_INFO         CTL_CODE(FILE_DEVICE_USB,  \
                                                    USB_GET_BUS_INFO,  \
                                                    METHOD_BUFFERED,  \
                                                    FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_CONTROLLER_NAME  CTL_CODE(FILE_DEVICE_USB,  \
                                                    USB_GET_CONTROLLER_NAME,  \
                                                    METHOD_BUFFERED,  \
                                                    FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_BUSGUID_INFO     CTL_CODE(FILE_DEVICE_USB,  \
                                                    USB_GET_BUSGUID_INFO,  \
                                                    METHOD_BUFFERED,  \
                                                    FILE_ANY_ACCESS)

#define IOCTL_INTERNAL_USB_GET_PARENT_HUB_INFO  CTL_CODE(FILE_DEVICE_USB,  \
                                                    USB_GET_PARENT_HUB_INFO,  \
                                                    METHOD_BUFFERED,  \
                                                    FILE_ANY_ACCESS)

/* see usbkern.h */
#define IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE     CTL_CODE(FILE_DEVICE_USB,  \
                                                    USB_GET_DEVICE_HANDLE, \
                                                    METHOD_NEITHER,  \
                                                    FILE_ANY_ACCESS)
/* see usbdrivr.h */
#define IOCTL_INTERNAL_USB_RECORD_FAILURE        CTL_CODE(FILE_DEVICE_USB,  \
                                                    USB_RECORD_FAILURE, \
                                                    METHOD_NEITHER,  \
                                                    FILE_ANY_ACCESS)


/*
   USB user mode IOCTLS
*/

/**************************************************************************
The following IOCTLS are always sent to the HCD symbolic name
***************************************************************************/

/* IOCTL_USB_HCD_GET_STATS_1 (OPTIONAL)

    The following IOCTL is used to return internal statictics
    for HCDs

*/

#define IOCTL_USB_HCD_GET_STATS_1           CTL_CODE(FILE_DEVICE_USB,  \
                                                HCD_GET_STATS_1,  \
                                                METHOD_BUFFERED,  \
                                                FILE_ANY_ACCESS)

/* IOCTL_USB_HCD_GET_STATS_2 (OPTIONAL)

    The following IOCTL is used to return internal statictics
    for HCDs

*/

#define IOCTL_USB_HCD_GET_STATS_2           CTL_CODE(FILE_DEVICE_USB,  \
                                                HCD_GET_STATS_2,  \
                                                METHOD_BUFFERED,  \
                                                FILE_ANY_ACCESS)

#define IOCTL_USB_HCD_DISABLE_PORT          CTL_CODE(FILE_DEVICE_USB, \
                                                HCD_DISABLE_PORT, \
                                                METHOD_BUFFERED, \
                                                FILE_ANY_ACCESS)

#define IOCTL_USB_HCD_ENABLE_PORT           CTL_CODE(FILE_DEVICE_USB, \
                                                HCD_ENABLE_PORT, \
                                                METHOD_BUFFERED, \
                                                FILE_ANY_ACCESS)


/*
   These ioctls are used for USB diagnostic and test applications
*/

#define IOCTL_USB_DIAGNOSTIC_MODE_ON   CTL_CODE(FILE_DEVICE_USB,  \
                                                HCD_DIAGNOSTIC_MODE_ON,  \
                                                METHOD_BUFFERED,  \
                                                FILE_ANY_ACCESS)

#define IOCTL_USB_DIAGNOSTIC_MODE_OFF  CTL_CODE(FILE_DEVICE_USB,  \
                                                HCD_DIAGNOSTIC_MODE_OFF,  \
                                                METHOD_BUFFERED,  \
                                                FILE_ANY_ACCESS)

#define IOCTL_USB_GET_ROOT_HUB_NAME    CTL_CODE(FILE_DEVICE_USB,  \
                                                HCD_GET_ROOT_HUB_NAME,  \
                                                METHOD_BUFFERED,  \
                                                FILE_ANY_ACCESS)

#define IOCTL_GET_HCD_DRIVERKEY_NAME   CTL_CODE(FILE_DEVICE_USB,  \
                                                HCD_GET_DRIVERKEY_NAME,  \
                                                METHOD_BUFFERED,  \
                                                FILE_ANY_ACCESS)


/**************************************************************************
The following IOCTLS are always sent to symbolic names
created by usbhub
***************************************************************************/

/*
    Utility IOCTLS supported by the hub device
*/

/*
   These ioctls are supported by the hub driver for
   use by user mode USB utilities.
*/

/*
IOCTL_USB_GET_NODE_INFORMATION

Routine Description:
Returns information about the USB hub in the user buffer passed in.  If the
IOCTL is sent to the hub NodeType is set to UsbHub and USB_HUB_INFORMATION is
returned this includes the hub descriptor and a flag indicating if the hub is
bus vs self powered .
This API returns FAILURE (STATUS_UNSUCCESSFUL) if the hub is not started or
otherwise not functional.

Parameters:
Input:
Irp->AssociatedIrp.SystemBuffer - pointer to USB_NODE_INFORMATION structure

Ouput:
USB_NODE_INFORMATION filled in as appropriate
*/
#define IOCTL_USB_GET_NODE_INFORMATION   \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_NODE_INFORMATION,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)


/*
IOCTL_USB_GET_NODE_CONNECTION_INFORMATION

Exactly the same as _EX but the speed field is a Boolean
LowSpeed
-TRUE if the device is low speed.
*/
#define IOCTL_USB_GET_NODE_CONNECTION_INFORMATION  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_NODE_CONNECTION_INFORMATION,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)
/*
IOCTL_USB_GET_NODE_CONNECTION_ATTRIBUTES

Routine Description:
Returns the Microsoft extended port attributes for a specific port. The
caller inputs the port number as the 'ConnectionIndex'.  Microsoft extended
port attributes are defined in the Extended Port Attribute specification.
This API also returns the current connection status of the port.

This API returns FAILURE (STATUS_UNSUCCESSFUL) if the hub is not started or
otherwise not functional.

Parameters:
Input:
Irp->AssociatedIrp.SystemBuffer - pointer to
Struct  _USB_NODE_CONNECTION_INFORMATION {
    ULONG ConnectionIndex;
}
ConnectionIndex
-is the one based port number.

Ouput: (if a device is attached)
ConnectionStatus
-The current USB connection status. Indicates things like enumeration failure
or overcurrent.
PortAttributes
-Extended port attributes defined in usb.h.
*/

#define IOCTL_USB_GET_NODE_CONNECTION_ATTRIBUTES  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_NODE_CONNECTION_ATTRIBUTES,\
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION   \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_CONNECTION_NAME    \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_NODE_CONNECTION_NAME,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_DIAG_IGNORE_HUBS_ON   CTL_CODE(FILE_DEVICE_USB,  \
                                USB_DIAG_IGNORE_HUBS_ON,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_DIAG_IGNORE_HUBS_OFF  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_DIAG_IGNORE_HUBS_OFF,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_GET_HUB_CAPABILITIES  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_HUB_CAPABILITIES,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)

#define IOCTL_USB_HUB_CYCLE_PORT  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_HUB_CYCLE_PORT,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)
/*
IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX

Routine Description:
Returns information about a specific USB hub port (AKA connection).  If there
is a device connected to the port information about the device is also
returned. The caller inputs the port number as the 'ConnectionIndex'.

This API returns FAILURE (STATUS_UNSUCCESSFUL) if the hub is not started or
otherwise not functional.

Parameters:
Input:
Irp->AssociatedIrp.SystemBuffer - pointer to
Struct  _USB_NODE_CONNECTION_INFORMATION {
    ULONG ConnectionIndex;
    USB_DEVICE_DESCRIPTOR DeviceDescriptor;
    UCHAR CurrentConfigurationValue;
    BOOLEAN LowSpeed;
    BOOLEAN DeviceIsHub;
    USHORT DeviceAddress;
    ULONG NumberOfOpenPipes;
    USB_CONNECTION_STATUS ConnectionStatus;
    USB_PIPE_INFO PipeList[0];
}
ConnectionIndex
-is the one based port number.

Ouput: (if a device is attached)
DeviceDescriptor
-USB device descriptor.
CurrentConfigurationValue
-Currently selected configuration value.
Speed
-indicates the 'current' operating speed, note that high speed devices can
operate at full speed when necessary.
DeviceIsHub
- TRUE if the attached device is a hub
DeviceAddress
- USB assigned device address.
NumberOfOpenPipes
- Number of open USB pipes in the current configuration
ConnectionStatus
- The current USB connection status.
USB_PIPE_INFO PipeList[0];
- list of open pipes including schedule offset and endpoint descriptor.  This
information can be used to calculate bandwidthusage.
*/

#define IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX  \
                                CTL_CODE(FILE_DEVICE_USB,  \
                                USB_GET_NODE_CONNECTION_INFORMATION_EX,  \
                                METHOD_BUFFERED,  \
                                FILE_ANY_ACCESS)



/*
   structures for user mode ioctls
*/

#include <pshpack1.h>

typedef enum _USB_HUB_NODE {
    UsbHub,
    UsbMIParent
} USB_HUB_NODE;

typedef struct _USB_HUB_INFORMATION {
    /*
       copy of data from hub descriptor
    */
    USB_HUB_DESCRIPTOR HubDescriptor;

    BOOLEAN HubIsBusPowered;

} USB_HUB_INFORMATION, *PUSB_HUB_INFORMATION;

typedef struct _USB_MI_PARENT_INFORMATION {
    ULONG NumberOfInterfaces;
} USB_MI_PARENT_INFORMATION, *PUSB_MI_PARENT_INFORMATION;

typedef struct _USB_NODE_INFORMATION {
    USB_HUB_NODE NodeType;        /* hub, mi parent */
    union {
        USB_HUB_INFORMATION HubInformation;
        USB_MI_PARENT_INFORMATION MiParentInformation;
    } u;
} USB_NODE_INFORMATION, *PUSB_NODE_INFORMATION;

typedef struct _USB_PIPE_INFO {
    USB_ENDPOINT_DESCRIPTOR EndpointDescriptor;
    ULONG ScheduleOffset;
} USB_PIPE_INFO, *PUSB_PIPE_INFO;


typedef struct _USB_HUB_CAPABILITIES {
    /*
        Unlike the USB_HUB_INFORMATION structure used by
        IOCTL_USB_GET_NODE_INFORMATION, this structure can be extended in the
        future to accomodate more data.  The IOCTL will return only as much
        data as indicated by the size of the request buffer, to maintain
        backward compatibility with older callers that don't know about the
        new data.
    */

    ULONG HubIs2xCapable:1;

} USB_HUB_CAPABILITIES, *PUSB_HUB_CAPABILITIES;


typedef union _USB_HUB_CAP_FLAGS {
    ULONG ul;
    struct {
        ULONG HubIsHighSpeedCapable:1;
        ULONG HubIsMultiTt:1;
        ULONG ReservedMBZ:30;
    };

} USB_HUB_CAP_FLAGS, *PUSB_HUB_CAP_FLAGS;

C_ASSERT(sizeof(USB_HUB_CAP_FLAGS) == sizeof(ULONG));

typedef struct _USB_HUB_CAPABILITIES_EX {

    USB_HUB_CAP_FLAGS CapabilityFlags;

} USB_HUB_CAPABILITIES_EX, *PUSB_HUB_CAPABILITIES_EX;


typedef enum _USB_CONNECTION_STATUS {
    NoDeviceConnected,
    DeviceConnected,

    /* failure codes, these map to fail reasons */
    DeviceFailedEnumeration,
    DeviceGeneralFailure,
    DeviceCausedOvercurrent,
    DeviceNotEnoughPower,
    DeviceNotEnoughBandwidth,
    DeviceHubNestedTooDeeply,
    DeviceInLegacyHub,
    DeviceEnumerating,
    DeviceReset
} USB_CONNECTION_STATUS, *PUSB_CONNECTION_STATUS;


/** IOCTL_USB_GET_NODE_CONNECTION_INFORMATION **/
typedef struct _USB_NODE_CONNECTION_INFORMATION {
    ULONG ConnectionIndex;  /* INPUT */
    /* usb device descriptor returned by this device
       during enumeration */
    USB_DEVICE_DESCRIPTOR DeviceDescriptor; /* OUTPUT */
    UCHAR CurrentConfigurationValue;/* OUTPUT */
    BOOLEAN LowSpeed;/* OUTPUT */
    BOOLEAN DeviceIsHub;/* OUTPUT */
    USHORT DeviceAddress;/* OUTPUT */
    ULONG NumberOfOpenPipes;/* OUTPUT */
    USB_CONNECTION_STATUS ConnectionStatus;/* OUTPUT */
    USB_PIPE_INFO PipeList[0];/* OUTPUT */
} USB_NODE_CONNECTION_INFORMATION, *PUSB_NODE_CONNECTION_INFORMATION;

/** IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX **/
typedef struct _USB_NODE_CONNECTION_INFORMATION_EX {
    ULONG ConnectionIndex;  /* INPUT */
    /* usb device descriptor returned by this device
       during enumeration */
    USB_DEVICE_DESCRIPTOR DeviceDescriptor;/* OUTPUT */
    UCHAR CurrentConfigurationValue;/* OUTPUT */
    /* values for the speed field are defined in USB200.h */
    UCHAR Speed;/* OUTPUT */
    BOOLEAN DeviceIsHub;/* OUTPUT */
    USHORT DeviceAddress;/* OUTPUT */
    ULONG NumberOfOpenPipes;/* OUTPUT */
    USB_CONNECTION_STATUS ConnectionStatus;/* OUTPUT */
    USB_PIPE_INFO PipeList[0];/* OUTPUT */
} USB_NODE_CONNECTION_INFORMATION_EX, *PUSB_NODE_CONNECTION_INFORMATION_EX;

C_ASSERT(sizeof(USB_NODE_CONNECTION_INFORMATION_EX) == \
    sizeof(USB_NODE_CONNECTION_INFORMATION));

/** IOCTL_USB_GET_NODE_CONNECTION_ATTRIBUTES **/
typedef struct _USB_NODE_CONNECTION_ATTRIBUTES {
    /* one based port number */
    ULONG ConnectionIndex;  /* INPUT */
    /* current USB connect status for the port*/
    USB_CONNECTION_STATUS ConnectionStatus; /* OUTPUT */
    /* extended port attributes defined in usb.h*/
    ULONG PortAttributes; /* OUTPUT */
} USB_NODE_CONNECTION_ATTRIBUTES, *PUSB_NODE_CONNECTION_ATTRIBUTES;

/** IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME **/
typedef struct _USB_NODE_CONNECTION_DRIVERKEY_NAME {
    ULONG ConnectionIndex;  /* INPUT */
    ULONG ActualLength;     /* OUTPUT */
    /* unicode name for the devnode */
    WCHAR DriverKeyName[1]; /* OUTPUT */
} USB_NODE_CONNECTION_DRIVERKEY_NAME, *PUSB_NODE_CONNECTION_DRIVERKEY_NAME;

/** IOCTL_USB_GET_NODE_CONNECTION_NAME **/
typedef struct _USB_NODE_CONNECTION_NAME {
    ULONG ConnectionIndex;  /* INPUT */
    ULONG ActualLength;     /* OUTPUT */
    /* unicode symbolic name for this node if it is a hub or parent driver
       null if this node is a device. */
    WCHAR NodeName[1];      /* OUTPUT */
} USB_NODE_CONNECTION_NAME, *PUSB_NODE_CONNECTION_NAME;

typedef struct _USB_HUB_NAME {
    ULONG ActualLength;     /* OUTPUT */
    /* NULL terminated unicode symbolic name for the root hub */
    WCHAR HubName[1];       /* OUTPUT */
} USB_HUB_NAME, *PUSB_HUB_NAME;

typedef struct _USB_ROOT_HUB_NAME {
    ULONG ActualLength;     /* OUTPUT */
    /* NULL terminated unicode symbolic name for the root hub */
    WCHAR RootHubName[1];   /* OUTPUT */
} USB_ROOT_HUB_NAME, *PUSB_ROOT_HUB_NAME;

typedef struct _USB_HCD_DRIVERKEY_NAME {
    ULONG ActualLength;     /* OUTPUT */
    /* NULL terminated unicode driverkeyname for hcd */
    WCHAR DriverKeyName[1]; /* OUTPUT */
} USB_HCD_DRIVERKEY_NAME, *PUSB_HCD_DRIVERKEY_NAME;

typedef struct _USB_DESCRIPTOR_REQUEST {
    ULONG ConnectionIndex;
    struct {
        UCHAR bmRequest;
        UCHAR bRequest;
        USHORT wValue;
        USHORT wIndex;
        USHORT wLength;
    } SetupPacket;
    UCHAR Data[0];
} USB_DESCRIPTOR_REQUEST, *PUSB_DESCRIPTOR_REQUEST;


/*
   Structure for returning HCD debug and statistic information to
   a user mode application.
*/

typedef struct _HCD_STAT_COUNTERS {
    ULONG BytesTransferred;

    USHORT IsoMissedCount;
    USHORT DataOverrunErrorCount;

    USHORT CrcErrorCount;
    USHORT ScheduleOverrunCount;

    USHORT TimeoutErrorCount;
    USHORT InternalHcErrorCount;

    USHORT BufferOverrunErrorCount;
    USHORT SWErrorCount;

    USHORT StallPidCount;
    USHORT PortDisableCount;

} HCD_STAT_COUNTERS, *PHCD_STAT_COUNTERS;


typedef struct _HCD_ISO_STAT_COUNTERS {

    USHORT  LateUrbs;
    USHORT  DoubleBufferedPackets;

    USHORT  TransfersCF_5ms;
    USHORT  TransfersCF_2ms;

    USHORT  TransfersCF_1ms;
    USHORT  MaxInterruptLatency;

    USHORT  BadStartFrame;
    USHORT  StaleUrbs;

    /* total count of packets programmed but not accessed by
       the controller either due to software scheduling
       problems or HW problems */
    USHORT  IsoPacketNotAccesed;
    USHORT  IsoPacketHWError;

    USHORT  SmallestUrbPacketCount;
    USHORT  LargestUrbPacketCount;

    USHORT IsoCRC_Error;
    USHORT IsoOVERRUN_Error;
    USHORT IsoINTERNAL_Error;
    USHORT IsoUNKNOWN_Error;

    ULONG  IsoBytesTransferred;

    /* count of packets missed due to software scheduling
       problems */
    USHORT LateMissedCount;
    /* incremented when a packet is scheduled but not
       accessed by the controller */
    USHORT HWIsoMissedCount;

    ULONG  Reserved7[8];

} HCD_ISO_STAT_COUNTERS, *PHCD_ISO_STAT_COUNTERS;



typedef struct _HCD_STAT_INFORMATION_1 {
    ULONG Reserved1;
    ULONG Reserved2;
    ULONG ResetCounters;
    LARGE_INTEGER TimeRead;
    /*
       stat registers
    */
    HCD_STAT_COUNTERS Counters;

} HCD_STAT_INFORMATION_1, *PHCD_STAT_INFORMATION_1;

typedef struct _HCD_STAT_INFORMATION_2 {
    ULONG Reserved1;
    ULONG Reserved2;
    ULONG ResetCounters;
    LARGE_INTEGER TimeRead;

    LONG LockedMemoryUsed;
    /*
       stat registers
    */
    HCD_STAT_COUNTERS Counters;
    HCD_ISO_STAT_COUNTERS IsoCounters;

} HCD_STAT_INFORMATION_2, *PHCD_STAT_INFORMATION_2;


/*
   WMI related structures
*/

/* these index in to our array of guids */
#define WMI_USB_DRIVER_INFORMATION      0
#define WMI_USB_DRIVER_NOTIFICATION     1
#define WMI_USB_POWER_DEVICE_ENABLE     2

typedef enum _USB_NOTIFICATION_TYPE {

    /*  the following return a
        USB_CONNECTION_NOTIFICATION structure: */
    EnumerationFailure = 0,
    InsufficentBandwidth,
    InsufficentPower,
    OverCurrent,
    ResetOvercurrent,

    /* the following return a
       USB_BUS_NOTIFICATION structure:*/
    AcquireBusInfo,

    /* the following return a
      USB_ACQUIRE_INFO structure: */
    AcquireHubName,
    AcquireControllerName,

    /* the following return a
       USB_HUB_NOTIFICATION structure: */
    HubOvercurrent,
    HubPowerChange,

    HubNestedTooDeeply,
    ModernDeviceInLegacyHub

} USB_NOTIFICATION_TYPE;

typedef struct _USB_NOTIFICATION {
    /* indicates type of notification */
    USB_NOTIFICATION_TYPE NotificationType;

} USB_NOTIFICATION, *PUSB_NOTIFICATION;

/* this structure is used for connection notification
   codes */

typedef struct _USB_CONNECTION_NOTIFICATION {
    /* indicates type of notification */
    USB_NOTIFICATION_TYPE NotificationType;

    /* valid for all connection notifictaion codes,
       0 indicates global condition for hub or parent
       this value will be a port number for devices
       attached to a hub, otherwise a one based
       index if the device is a child of a composite
       parent */
    ULONG ConnectionNumber;

    /* valid for InsufficentBandwidth,
       the amount of bandwidth the device
       tried to allocate and was denied. */
    ULONG RequestedBandwidth;

    /* valid for EnumerationFailure,
       gives some indication why the device failed
       to enumerate */
    ULONG EnumerationFailReason;

    /* valid for InsufficentPower,
       the amount of power requested to configure
       this device. */
    ULONG PowerRequested;

    /* length of the UNICODE symbolic name (in bytes) for the HUB
       that this device is attached to.
       not including NULL */
    ULONG HubNameLength;

} USB_CONNECTION_NOTIFICATION, *PUSB_CONNECTION_NOTIFICATION;

/*
   This structure is used for the bus notification code 'AcquireBusInfo'
*/

typedef struct _USB_BUS_NOTIFICATION {
    /* indicates type of notification */
    USB_NOTIFICATION_TYPE NotificationType;     /* indicates type of */
                                                /* notification */
    ULONG TotalBandwidth;
    ULONG ConsumedBandwidth;

    /* length of the UNICODE symbolic name (in bytes) for the controller
       that this device is attached to.
       not including NULL */
    ULONG ControllerNameLength;

} USB_BUS_NOTIFICATION, *PUSB_BUS_NOTIFICATION;

/*
   used to acquire user mode filenames to open respective objects
*/

typedef struct _USB_ACQUIRE_INFO {
    /* indicates type of notification */
    USB_NOTIFICATION_TYPE NotificationType;
    /* TotalSize of this struct */
    ULONG TotalSize;

    WCHAR Buffer[1];
} USB_ACQUIRE_INFO, *PUSB_ACQUIRE_INFO;

#ifdef USB20_API
/*
    New structures not comaptible with usbdi.h -- use usb.h instead
*/
typedef struct _USB_START_FAILDATA {
    ULONG LengthInBytes;
    NTSTATUS NtStatus;
    USBD_STATUS UsbdStatus;
    ULONG ConnectStatus;
    UCHAR DriverData[4];
} USB_START_FAILDATA, *PUSB_START_FAILDATA;
#endif


#include <poppack.h>


#endif /* __USBIOCTL_H__ */

