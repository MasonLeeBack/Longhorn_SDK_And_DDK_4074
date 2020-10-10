/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    hubbusif.h

Abstract:

    Services exported by the Port driver for use by the hub driver.
    All of these services are callable only at PASSIVE_LEVEL.

Environment:

    Kernel mode

Revision History:

    6-20-99 : created

--*/

#ifndef   __HUBBUSIF_H__
#define   __HUBBUSIF_H__

typedef PVOID PUSB_DEVICE_HANDLE;

typedef struct _ROOTHUB_PDO_EXTENSION {

    ULONG Signature;

} ROOTHUB_PDO_EXTENSION, *PROOTHUB_PDO_EXTENSION;

// legacy flags
#define USBD_DEVHACK_SLOW_ENUMERATION   0x00000001
#define USBD_DEVHACK_DISABLE_SN         0x00000002
#define USBD_DEVHACK_SET_DIAG_ID        0x00000004



#ifndef USB_BUSIFFN
#define USB_BUSIFFN __stdcall
#endif

/****************************************************************************
    Bus interfce for USB Hub
*****************************************************************************/

/*
NTSTATUS
USBPORT_CreateUsbDevice(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE *DeviceHandle,
    IN PUSB_DEVICE_HANDLE HubDeviceHandle,
    IN USHORT PortStatus,
    IN USHORT PortNumber
    );

NTSTATUS
USBPORT_CreateUsbDeviceEx(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE *DeviceHandle,
    IN PUSB_DEVICE_HANDLE HubDeviceHandle,
    IN USHORT PortStatus,
    IN USHORT PortNumber,
    IN OUT PUSB_CD_ERROR_INFORMATION CdErrorInformation
    );

Routine Description:

Service exported for use by the hub driver

Called for each new device on the USB bus, this function sets up
the internal data structures a port driver needs to keep track of the device.

Ex adds one additional parameter for returning error information

IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle - A pointer to return the handle of the new device to the hub.
The value returned here is passed in the DeviceHandle field of all URBs
passed to the USB port driver and references this device.

HubDeviceHandle - device handle for the hub creating the device.  This is
used to keep track which TT is associated with the device if the device is
connected to a USB 2.0 hub.

PortStatus - port status bits (see chap 11 of USB core specification). These
are the bits read from the port status register after the first USB reset has
completed.

PortNumber - port number this device is attached to - necessary for USB 2.0
compatibility.



CdErrorInformation - if Create Device fails additional information about the
error is returned in this structure



*/

#define CD_ERR_V1       0x00000001

typedef enum _USBPORT_CREATEDEV_ERROR {
    CreateDevErrNotSet = 0,
    CreateDevBadHubDevHandle,
    CreateDevFailedAllocDevHandle,
    CreateDevFailedOpenEndpoint,
    CreateDevFailedAllocDsBuff,
    CreateDevFailedGetDs
} USBPORT_CREATEDEV_ERROR;

typedef struct _USB_CD_ERROR_INFORMATION {

    ULONG Version;
    USBPORT_CREATEDEV_ERROR PathError;
    ULONG Arg1;
    ULONG Arg2;
    NTSTATUS NtStatus;
    UCHAR XtraInfo[64];

} USB_CD_ERROR_INFORMATION, *PUSB_CD_ERROR_INFORMATION;


typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_CREATE_USB_DEVICE) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE *,
        IN PUSB_DEVICE_HANDLE,
        IN USHORT,
        IN USHORT
    );

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_CREATE_USB_DEVICE_EX) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE *,
        IN PUSB_DEVICE_HANDLE,
        IN USHORT,
        IN USHORT,
        IN OUT PUSB_CD_ERROR_INFORMATION
    );

/*
NTSTATUS
USBPORT_InitializeUsbDevice(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE DeviceHandle
    );

Routine Description:

Service exported for use by the hub driver

This function finalizes the initialization of the DeviceHandle returned from
CreateUsbDevice and assigns the device a USB address.

IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle -The handle of the new device on the hub returned from
CreateUsbDevice.  The value returned here is passed in the DeviceHandle field
of all URBs passed to the USB port driver and references this device.

*****
NTSTATUS
USBPORT_InitializeUsbDeviceEx(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE DeviceHandle
    IN PUSB_ID_ERROR_INFORMATION IdErrInfo
    );

Parameters and behavior are the same as IntilaizeUsbDevice with one
additional parameter that returns extended error information. This
information can be used to diagnose the precise cause of the enumeration
failure.
typedef struct _USB_ID_ERROR_INFORMATION {

IN     ULONG Version;
OUT    USBPORT_INITDEV_ERROR PathError;
OUT    NTSTATUS NtStatus
OUT    UCHAR XtraInfo[64];

} USB_ID_ERROR_INFORMATION;

Version
The callers expected version of this structure for backward compatibility.
This parameter is filled in by the caller.

PathError
A unique identifier indicated the code path where the error occurred.

NtStatus
NTSTATUS code of the Failure.

XtraInfo
Up to 64 bytes of additional data, this data is specific to the PathError it
may contain such things as the descriptor data returned by the device etc.

*/

#define ID_ERR_V1       0x00000001

typedef enum _USBPORT_INITDEV_ERROR {
    InitDevErrNotSet = 0,
    InitDevFailedSetAddress,
    InitDevFailedPokeEndpoint,
    InitDevBadDeviceDescriptor,
} USBPORT_INITDEV_ERROR;

typedef struct _USB_ID_ERROR_INFORMATION {

    ULONG Version;
    USBPORT_INITDEV_ERROR PathError;
    ULONG Arg1;
    ULONG Arg2;
    NTSTATUS NtStatus;
    UCHAR XtraInfo[64];

} USB_ID_ERROR_INFORMATION, *PUSB_ID_ERROR_INFORMATION;


typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_INITIALIZE_USB_DEVICE) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE
    );

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_INITIALIZE_USB_DEVICE_EX) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE,
        IN OUT PUSB_ID_ERROR_INFORMATION
    );


/*
NTSTATUS
USBPORT_RemoveUsbDevice(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE DeviceHandle,
    IN ULONG Flags
    );
Routine Description:

Service exported for use by the hub driver to remove an instance of a USB
device from the bus.  This function deletes a device handle created with
CreateUsbDevice.

Called by the hub driver to delete

IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle - Handle for the device you want delete.  This is the handle
returned by CreateUsbDevice or returned in IOCTL api
IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE.

Flags - flags for customizing the delete operation

USBD_KEEP_DEVICE_DATA - this flag effectively causes this API to be a nop so
it is not used.
USBD_MARK_DEVICE_BUSY - just marks the device handle as busy - the device
handle itself remains valid and no resources are freed.  This flag can be
used to temporarily disable the device handle.
*/

/*
flags passed to remove device
*/

#define USBD_KEEP_DEVICE_DATA   0x00000001
#define USBD_MARK_DEVICE_BUSY   0x00000002


typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_REMOVE_USB_DEVICE) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE,
        IN ULONG
    );


/*
NTSTATUS
USBPORT_GetUsbDescriptors(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE DeviceHandle,
    IN OUT PUCHAR DeviceDescriptorBuffer,
    IN OUT PULONG DeviceDescriptorBufferLength,
    IN OUT PUCHAR ConfigDescriptorBuffer,
    IN OUT PULONG ConfigDescriptorBufferLength,
    );
Routine Description:

Service exported for use by the hub driver

Called by the hub driver to retrieve the device and configuration descriptors
for a device.  This service may return cached copies of these descriptors
decreasing the amount of traffic to the device.

IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle - Handle for the device you want information about. This is the
handle returned by CreateUsbDevice or returned in IOCTL api
IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE.

DeviceDescriptorBuffer - caller allocated buffer to return the device
descriptor in.
DeviceDescriptorBufferLength - pointer, input is the size of the
DeviceDescriptorBuffer in bytes. Output is the number of bytes copied to the
buffer.

ConfigDescriptorBuffer - caller allocated buffer to return the configuration
descriptor in.
ConfigDescriptorBufferLength - pointer, input is the size of the
ConfigDescriptorBuffer in bytes. Output is the number of bytes copied to the
buffer.

*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_USB_DESCRIPTORS) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE,
        IN OUT PUCHAR,
        IN OUT PULONG,
        IN OUT PUCHAR,
        IN OUT PULONG
    );

/*
NTSTATUS
USBPORT_RestoreDevice(
    IN PVOID BusContext,
    IN OUT PUSB_DEVICE_HANDLE OldDeviceHandle,
    IN OUT PUSB_DEVICE_HANDLE NewDeviceHandle
    );

Routine Description:

    Service exported for use by the hub driver

    This service will re-create the device on the bus
    using the information supplied in the OldDeviceHandle

    IRQL = PASSIVE_LEVEL

Arguments:

    BusHandle -

    OldDeviceHandle -

    NewDeviceHandle -

*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_RESTORE_DEVICE) (
        IN PVOID,
        IN OUT PUSB_DEVICE_HANDLE,
        IN OUT PUSB_DEVICE_HANDLE
    );

/*
NTSTATUS
USBPORT_GetUsbPortHackFlags(
    IN PVOID BusContext,
    OUT PULONG HackFlags
    );

Routine Description:

Service exported for use by the hub driver. This API queries the usbport 'hack
' flags from the port driver.  These flags allow the port driver to control
some of the behaviors of the hub.

IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

HackFlags - Pointer to 32 bit hack flags mask.  There are currently no flags
defined for this API.
*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_POTRTHACK_FLAGS) (
        IN PVOID,
        IN OUT PULONG
        );

/*
NTSTATUS
USBPORT_GetDeviceInformation(
    IN PVOID BusContext,
    IN PUSB_DEVICE_HANDLE DeviceHandle,
    IN OUT PVOID DeviceInformationBuffer,
    IN ULONG DeviceInformationBufferLength,
    IN OUT PULONG LengthOfDataReturned,
    );

Routine Description:

Service exported for use by the hub driver.  This api returns various
information about a USB devices attached to the system.

IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle - Handle for the device you want information about. This is the
handle returned by CreateUsbDevice or returned in IOCTL api
IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE.

DeviceInformationBuffer - buffer for returning device information.  The type
of data returned is defined by the value passed in the InformationLevel field
of the buffer passed in.
Levels Supported:
_ USB_DEVICE_INFORMATION_0, level = 0

DeviceInformationBufferLength - length of DeviceInformationBuffer in bytes

LengthOfDataReturned - length of data copied into DeviceInformationBuffer.
*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_DEVICE_INFORMATION) (
        IN PVOID,
        IN PUSB_DEVICE_HANDLE,
        IN OUT PVOID,
        IN ULONG,
        IN OUT PULONG
        );


/*
NTSTATUS
USBPORT_GetControllerInformation(
    IN PVOID BusContext,
    IN OUT PVOID ControllerInformationBuffer,
    IN ULONG ControllerInformationBufferLength,
    IN OUT PULONG LengthOfDataReturned
    );

Routine Description:

    Service exported for use by the hub driver.  This api returns
    various information about the USB devices attached to the system

    IRQL = PASSIVE_LEVEL

Arguments:

    BusHandle - Handle to the bus we need to create the device on
                this is returned to the hub driver when it requests
                the interface.

    ControllerInformationBuffer - buffer for returned data

    ControllerInformationBufferLength -  length of client buffer

    LengthOfDataReturned -  length of buffer used


*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_CONTROLLER_INFORMATION) (
        IN PVOID,
        IN OUT PVOID,
        IN ULONG,
        IN OUT PULONG
        );


/*
NTSTATUS
USBPORT_ControllerSelectiveSuspend(
    IN PVOID BusContext,
    IN BOOLEAN Enable
    );

Routine Description:

    Service exported for use by the hub driver.  This api enables or
    disables a selective suspend for the controller

    IRQL = PASSIVE_LEVEL

Arguments:

    BusHandle - Handle to the bus we need to create the device on
                this is returned to the hub driver when it requests
                the interface.

    Enable  - TRUE enables selective suspend, false disables it.

*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_CONTROLLER_SELECTIVE_SUSPEND) (
        IN PVOID,
        IN BOOLEAN
        );


/*
NTSTATUS
USBPORT_GetExtendedHubInformation(
    IN PVOID BusContext,
    IN PDEVICE_OBJECT HubPhysicalDeviceObject,
    IN OUT PVOID HubInformationBuffer,
    IN ULONG HubInformationBufferLength,
    IN OUT PULONG LengthOfDataReturned
    );

Routine Description:

In order to simplify the implementation of usbport.sys this API is no longer
supported or used in version 6 and beyond.  The usbhub.sys driver accesses
this information internally.


*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_EXTENDED_HUB_INFO) (
        IN PVOID,
        IN PDEVICE_OBJECT,
        IN OUT PVOID,
        IN ULONG,
        IN OUT PULONG
        );

/*

NTSTATUS
USBPORT_GetRootHubSymName(
    IN PVOID BusContext,
    IN OUT PVOID HubInformationBuffer,
    IN ULONG HubInformationBufferLength,
    OUT PULONG HubNameActualLength
    );

Routine Description:
This API is obsolete in Longhorn, it returns the same information as
IOCTL_INTERNAL_GET_HUB_NAME but this API only works for the root.  Drivers
should use IOCTL_INTERNAL_GET_HUB_NAME instead.

*/


typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_ROOTHUB_SYM_NAME) (
        IN PVOID,
        IN OUT PVOID,
        IN ULONG,
        IN OUT PULONG
        );
/*
PVOID
USBPORT_GetDeviceBusContext(
    IN PVOID BusContext,
    IN PVOID DeviceHandle
    );

Routine Description:

Service exported for use by the hub driver.  This api returns various
information about a USB devices attached to the system.
This API returns the device relative buscontext for the USBD bus interface.
This is the opaque value associated with the USBD bus interface for a
particular device handle.  This function does the exact same thing as calling
QueryBusInterface for the USBD bus interface and passing the devices handle
in InterfaceSpecific data.

    IRQL = PASSIVE_LEVEL

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle - Handle for the device you want information about. This is the
handle returned by CreateUsbDevice or returned in IOCTL api
IOCTL_INTERNAL_USB_GET_DEVICE_HANDLE.

*/

typedef PVOID
    (USB_BUSIFFN *PUSB_BUSIFFN_GET_DEVICE_BUSCONTEXT) (
        IN PVOID,
        IN PVOID
        );

/*
NTSTATUS
USBPORT_Initialize20Hub(
    IN PVOID BusContext,
    IN PUSB_DEVICE_HANDLE HubDeviceHandle,
    IN ULONG TtCount
    );

Routine Description:

Service exported for use by the hub driver

Initialize internal USBPORT structures for a USB 2.0 hub, called during the
hub start process.  This routine sets up the budgeter code for the TTs.

IRQL = ANY

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

HubDeviceHandle - device handle for this hub.

TtCount - Transaction translator count, this is either 1 or equal to the
number of downstream ports depending on what the hub reported in its
configuration descriptor.
*/

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_INITIALIZE_20HUB) (
        IN PVOID,
        IN PUSB_DEVICE_HANDLE,
        IN ULONG
        );

/*
BOOLEAN
USBPORT_HubIsRoot(
    PVOID BusContext,
    PVOID PhysicalDeviceObject
    );

Routine Description:

Service exported for use by the hub driver

This routine returns true if the PhysicalDeviceObject passed in is for the
root hub on the controller.

IRQL = ANY


*/

typedef BOOLEAN
    (USB_BUSIFFN *PUSB_BUSIFFN_IS_ROOT) (
        IN PVOID,
        IN PVOID
    );

/*
VOID
USBPORT_ReleaseBusSemaphore(
    PVOID BusContext
    );

VOID
USBPORT_AcquireBusSemaphore(
    PVOID BusContext
    );

Routine Description:

Service exported for use by the hub driver

Acquires or releases the global bus semaphore.  This semaphore is used by the
hub to serialize parts of enumeration.  The semaphore is held by the hub as
long as a device is at address zero (0).

IRQL = PASSIVE
*/
typedef VOID
    (USB_BUSIFFN *PUSB_BUSIFFN_ACQUIRE_SEMAPHORE) (
        IN PVOID
    );

typedef VOID
    (USB_BUSIFFN *PUSB_BUSIFFN_RELEASE_SEMAPHORE) (
        IN PVOID
    );


/*
NTSTATUS
USBPORT_RootHubInitNotification(
    IN PVOID BusContext,
    IN PVOID CallbackContext,
    IN PRH_INIT_CALLBACK CallbackFunction
    );

Routine Description:

Service exported for use by the hub driver

A notification request issued by usbhub.sys when it is loaded for the root
hub to synchronize enumeration with one or more USB 2.0 companion controllers
.  The port driver calls the notification function when it is ok to enumerate
devices.  The purpose of this function is to delay enumeration on USB
companion controllers until the associated USB 2.0 controller starts.  This
minimizes the number of times the device will move from one bus to the other
during boot.

IRQL = ANY

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

CallBackContext - A hub driver specific context value to be passed to the
notification callback function.

CallbackFunction - Function to call when it is OK to enumerate devices.  The
callback is called at raised IRQL (DPC_LEVEL).

typedef VOID
    (__stdcall *PRH_INIT_CALLBACK) (
        IN PVOID
        );
*/

typedef VOID
    (__stdcall *PRH_INIT_CALLBACK) (
        IN PVOID
        );

typedef NTSTATUS
    (USB_BUSIFFN *PUSB_BUSIFFN_ROOTHUB_INIT_NOTIFY) (
        IN PVOID,
        IN PVOID,
        IN PRH_INIT_CALLBACK
        );

/*
VOID
USBPORT_FlushTransfers(
    PVOID BusContext,
    PVOID DeviceHandle
    );
Routine Description:

Service exported for use by the hub driver

This routine flushes any outstanding transfers associated with a bus and
device handle.  The service is used in conjunction with IRP_MN_REMOVE_DEVICE
for a device PDO to ensure that all outstanding transfers have been completed
when a device is removed.

IRQL = ANY

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

DeviceHandle - Opaque structure returned from CreateUsbDevice.


*/

typedef VOID
    (USB_BUSIFFN *PUSB_BUSIFFN_FLUSH_TRANSFERS) (
        IN PVOID,
        IN PVOID
    );

/*
ULONG
USBPORT_CalculatePipeBandwidth(
    PVOID BusContext,
    PVOID DeviceHandle,
    PUSBD_PIPE_INFORMATION PipeInformation,
    USB_DEVICE_SPEED Speed
    );

Routine Description:

Service exported for use by the hub driver

This routine is used to calculate bandwidth consumed by a pipe with the give
characteristics set in the PipeInformation structure.  The bandwidth value
returned is in bits/second.


IRQL = ANY

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

PipeInformation - pointer to USBD_PIPE_INFORMATION structure filled in with
the attributes of a pipe.

Speed - speed of the device high, full or low



*/
typedef ULONG
    (USB_BUSIFFN *PUSB_BUSIFFN_CALC_PIPE_BANDWIDTH) (
        IN PVOID,
        IN PUSBD_PIPE_INFORMATION,
        IN USB_DEVICE_SPEED
    );

/*
NTSTATUS
USBPORT_SetBusSystemWakeMode(
    PVOID BusContext,
    ULONG ArmMode
    );

Routine Description:

Service exported for use by the hub driver

This routine will enable resume signaling on the USB to wake the system.  The
hub driver calls this function if 1 or more USB devices are 'enabled' to wake
the system.

IRQL = ANY

Arguments:

BusContext - Handle to the bus we need to create the device on. This is the
value returned in the call to QUERY_INTERFACE and is opaque to the caller.

ArmForWake - 1 if we want to arm, 0 to disarm


return value

none

*/

typedef VOID
    (USB_BUSIFFN *PUSB_BUSIFFN_SET_BUS_WAKE_MODE) (
        IN PVOID,
        IN ULONG
    );


/*
VOID
USBPORTBUSIF_SetDeviceHandleData(
    PVOID BusContext,
    PVOID DeviceHandle,
    PDEVICE_OBJECT UsbDevicePdo
    )

Routine Description:

    Assocaites a particular PDO with a device handle for use
    in post mortem debugging situaltions

    This routine must be called at passive level.

Arguments:

Return Value:

    none
*/


typedef VOID
    (USB_BUSIFFN *PUSB_BUSIFFN_SET_DEVHANDLE_DATA) (
        IN PVOID,
        IN PVOID,
        IN PDEVICE_OBJECT
    );


#define USB_BUSIF_HUB_VERSION_0         0x0000
#define USB_BUSIF_HUB_VERSION_1         0x0001
#define USB_BUSIF_HUB_VERSION_2         0x0002
#define USB_BUSIF_HUB_VERSION_3         0x0003
#define USB_BUSIF_HUB_VERSION_4         0x0004
#define USB_BUSIF_HUB_VERSION_5         0x0005
#define USB_BUSIF_HUB_VERSION_6         0x0006

/* {B2BB8C0A-5AB4-11d3-A8CD-00C04F68747A}*/
DEFINE_GUID(USB_BUS_INTERFACE_HUB_GUID,
0xb2bb8c0a, 0x5ab4, 0x11d3, 0xa8, 0xcd, 0x0, 0xc0, 0x4f, 0x68, 0x74, 0x7a);

typedef struct _USB_BUS_INTERFACE_HUB_V0 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

} USB_BUS_INTERFACE_HUB_V0, *PUSB_BUS_INTERFACE_HUB_V0;


typedef struct _USB_BUS_INTERFACE_HUB_V1 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

    //
    // fuctions for the hub driver
    //
    PUSB_BUSIFFN_CREATE_USB_DEVICE CreateUsbDevice;
    PUSB_BUSIFFN_INITIALIZE_USB_DEVICE InitializeUsbDevice;
    PUSB_BUSIFFN_GET_USB_DESCRIPTORS GetUsbDescriptors;
    PUSB_BUSIFFN_REMOVE_USB_DEVICE RemoveUsbDevice;
    PUSB_BUSIFFN_RESTORE_DEVICE RestoreUsbDevice;

    PUSB_BUSIFFN_GET_POTRTHACK_FLAGS GetPortHackFlags;
    PUSB_BUSIFFN_GET_DEVICE_INFORMATION QueryDeviceInformation;


} USB_BUS_INTERFACE_HUB_V1, *PUSB_BUS_INTERFACE_HUB_V1;

/*
*/

typedef struct _USB_BUS_INTERFACE_HUB_V2 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

    //
    // fuctions for the hub driver
    //
    PUSB_BUSIFFN_CREATE_USB_DEVICE CreateUsbDevice;
    PUSB_BUSIFFN_INITIALIZE_USB_DEVICE InitializeUsbDevice;
    PUSB_BUSIFFN_GET_USB_DESCRIPTORS GetUsbDescriptors;
    PUSB_BUSIFFN_REMOVE_USB_DEVICE RemoveUsbDevice;
    PUSB_BUSIFFN_RESTORE_DEVICE RestoreUsbDevice;

    PUSB_BUSIFFN_GET_POTRTHACK_FLAGS GetPortHackFlags;
    PUSB_BUSIFFN_GET_DEVICE_INFORMATION QueryDeviceInformation;

    //
    // new functions for version 2
    //
    PUSB_BUSIFFN_GET_CONTROLLER_INFORMATION GetControllerInformation;
    PUSB_BUSIFFN_CONTROLLER_SELECTIVE_SUSPEND ControllerSelectiveSuspend;
    PUSB_BUSIFFN_GET_EXTENDED_HUB_INFO GetExtendedHubInformation;
    PUSB_BUSIFFN_GET_ROOTHUB_SYM_NAME GetRootHubSymbolicName;
    PUSB_BUSIFFN_GET_DEVICE_BUSCONTEXT GetDeviceBusContext;
    PUSB_BUSIFFN_INITIALIZE_20HUB Initialize20Hub;

} USB_BUS_INTERFACE_HUB_V2, *PUSB_BUS_INTERFACE_HUB_V2;


typedef struct _USB_BUS_INTERFACE_HUB_V3 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

    //
    // fuctions for the hub driver
    //
    PUSB_BUSIFFN_CREATE_USB_DEVICE CreateUsbDevice;
    PUSB_BUSIFFN_INITIALIZE_USB_DEVICE InitializeUsbDevice;
    PUSB_BUSIFFN_GET_USB_DESCRIPTORS GetUsbDescriptors;
    PUSB_BUSIFFN_REMOVE_USB_DEVICE RemoveUsbDevice;
    PUSB_BUSIFFN_RESTORE_DEVICE RestoreUsbDevice;

    PUSB_BUSIFFN_GET_POTRTHACK_FLAGS GetPortHackFlags;
    PUSB_BUSIFFN_GET_DEVICE_INFORMATION QueryDeviceInformation;

    //
    // new functions for version 2
    //
    PUSB_BUSIFFN_GET_CONTROLLER_INFORMATION GetControllerInformation;
    PUSB_BUSIFFN_CONTROLLER_SELECTIVE_SUSPEND ControllerSelectiveSuspend;
    PUSB_BUSIFFN_GET_EXTENDED_HUB_INFO GetExtendedHubInformation;
    PUSB_BUSIFFN_GET_ROOTHUB_SYM_NAME GetRootHubSymbolicName;
    PUSB_BUSIFFN_GET_DEVICE_BUSCONTEXT GetDeviceBusContext;
    PUSB_BUSIFFN_INITIALIZE_20HUB Initialize20Hub;

    //
    // new for version 3
    //

    PUSB_BUSIFFN_ROOTHUB_INIT_NOTIFY RootHubInitNotification;

} USB_BUS_INTERFACE_HUB_V3, *PUSB_BUS_INTERFACE_HUB_V3;


typedef struct _USB_BUS_INTERFACE_HUB_V4 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

    //
    // fuctions for the hub driver
    //
    PUSB_BUSIFFN_CREATE_USB_DEVICE CreateUsbDevice;
    PUSB_BUSIFFN_INITIALIZE_USB_DEVICE InitializeUsbDevice;
    PUSB_BUSIFFN_GET_USB_DESCRIPTORS GetUsbDescriptors;
    PUSB_BUSIFFN_REMOVE_USB_DEVICE RemoveUsbDevice;
    PUSB_BUSIFFN_RESTORE_DEVICE RestoreUsbDevice;

    PUSB_BUSIFFN_GET_POTRTHACK_FLAGS GetPortHackFlags;
    PUSB_BUSIFFN_GET_DEVICE_INFORMATION QueryDeviceInformation;

    //
    // new functions for version 2
    //
    PUSB_BUSIFFN_GET_CONTROLLER_INFORMATION GetControllerInformation;
    PUSB_BUSIFFN_CONTROLLER_SELECTIVE_SUSPEND ControllerSelectiveSuspend;
    PUSB_BUSIFFN_GET_EXTENDED_HUB_INFO GetExtendedHubInformation;
    PUSB_BUSIFFN_GET_ROOTHUB_SYM_NAME GetRootHubSymbolicName;
    PUSB_BUSIFFN_GET_DEVICE_BUSCONTEXT GetDeviceBusContext;
    PUSB_BUSIFFN_INITIALIZE_20HUB Initialize20Hub;

    //
    // new for version 3
    //

    PUSB_BUSIFFN_ROOTHUB_INIT_NOTIFY RootHubInitNotification;

    //
    // new for version 4
    //

    PUSB_BUSIFFN_FLUSH_TRANSFERS FlushTransfers;

} USB_BUS_INTERFACE_HUB_V4, *PUSB_BUS_INTERFACE_HUB_V4;


typedef struct _USB_BUS_INTERFACE_HUB_V5 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

    //
    // fuctions for the hub driver
    //
    PUSB_BUSIFFN_CREATE_USB_DEVICE CreateUsbDevice;
    PUSB_BUSIFFN_INITIALIZE_USB_DEVICE InitializeUsbDevice;
    PUSB_BUSIFFN_GET_USB_DESCRIPTORS GetUsbDescriptors;
    PUSB_BUSIFFN_REMOVE_USB_DEVICE RemoveUsbDevice;
    PUSB_BUSIFFN_RESTORE_DEVICE RestoreUsbDevice;

    PUSB_BUSIFFN_GET_POTRTHACK_FLAGS GetPortHackFlags;
    PUSB_BUSIFFN_GET_DEVICE_INFORMATION QueryDeviceInformation;

    //
    // new functions for version 2
    //
    PUSB_BUSIFFN_GET_CONTROLLER_INFORMATION GetControllerInformation;
    PUSB_BUSIFFN_CONTROLLER_SELECTIVE_SUSPEND ControllerSelectiveSuspend;
    PUSB_BUSIFFN_GET_EXTENDED_HUB_INFO GetExtendedHubInformation;
    PUSB_BUSIFFN_GET_ROOTHUB_SYM_NAME GetRootHubSymbolicName;
    PUSB_BUSIFFN_GET_DEVICE_BUSCONTEXT GetDeviceBusContext;
    PUSB_BUSIFFN_INITIALIZE_20HUB Initialize20Hub;

    //
    // new for version 3
    //

    PUSB_BUSIFFN_ROOTHUB_INIT_NOTIFY RootHubInitNotification;

    //
    // new for version 4
    //

    PUSB_BUSIFFN_FLUSH_TRANSFERS FlushTransfers;

    // new for version 5

    PUSB_BUSIFFN_SET_DEVHANDLE_DATA SetDeviceHandleData;

} USB_BUS_INTERFACE_HUB_V5, *PUSB_BUS_INTERFACE_HUB_V5;


typedef struct _USB_BUS_INTERFACE_HUB_V6 {

    USHORT Size;
    USHORT Version;
    // returns
    PVOID BusContext;
    PINTERFACE_REFERENCE InterfaceReference;
    PINTERFACE_DEREFERENCE InterfaceDereference;

    // interface specific entries go here

    //
    // fuctions for the hub driver
    //
    PUSB_BUSIFFN_CREATE_USB_DEVICE_EX CreateUsbDevice;
    PUSB_BUSIFFN_INITIALIZE_USB_DEVICE_EX InitializeUsbDevice;
    PUSB_BUSIFFN_GET_USB_DESCRIPTORS GetUsbDescriptors;
    PUSB_BUSIFFN_REMOVE_USB_DEVICE RemoveUsbDevice;
    PUSB_BUSIFFN_RESTORE_DEVICE RestoreUsbDevice;

    PUSB_BUSIFFN_GET_POTRTHACK_FLAGS GetPortHackFlags;
    PUSB_BUSIFFN_GET_DEVICE_INFORMATION QueryDeviceInformation;

    //
    // new functions for version 2
    //
    PUSB_BUSIFFN_GET_CONTROLLER_INFORMATION GetControllerInformation;
    PUSB_BUSIFFN_CONTROLLER_SELECTIVE_SUSPEND ControllerSelectiveSuspend;
    PUSB_BUSIFFN_GET_EXTENDED_HUB_INFO GetExtendedHubInformation;
    PUSB_BUSIFFN_GET_ROOTHUB_SYM_NAME GetRootHubSymbolicName;
    PUSB_BUSIFFN_GET_DEVICE_BUSCONTEXT GetDeviceBusContext;
    PUSB_BUSIFFN_INITIALIZE_20HUB Initialize20Hub;

    //
    // new for version 3
    //

    PUSB_BUSIFFN_ROOTHUB_INIT_NOTIFY RootHubInitNotification;

    //
    // new for version 4
    //

    PUSB_BUSIFFN_FLUSH_TRANSFERS FlushTransfers;

    // new for version 5

    PUSB_BUSIFFN_SET_DEVHANDLE_DATA SetDeviceHandleData;

    // new for version 6 - Longhorn

    PUSB_BUSIFFN_IS_ROOT HubIsRoot;
    PUSB_BUSIFFN_ACQUIRE_SEMAPHORE AcquireBusSemaphore;
    PUSB_BUSIFFN_RELEASE_SEMAPHORE ReleaseBusSemaphore;
    PUSB_BUSIFFN_CALC_PIPE_BANDWIDTH CaculatePipeBandwidth;
    PUSB_BUSIFFN_SET_BUS_WAKE_MODE SetBusSystemWakeMode;


} USB_BUS_INTERFACE_HUB_V6, *PUSB_BUS_INTERFACE_HUB_V6;





/*
    The following structures are used by the GetDeviceInformation
    APIs
*/

#include <pshpack1.h>

typedef struct _USB_PIPE_INFORMATION_0 {

    /* pad descriptors to maintain DWORD alignment */
    USB_ENDPOINT_DESCRIPTOR EndpointDescriptor;
    UCHAR ED_Pad[1];

    ULONG ScheduleOffset;
} USB_PIPE_INFORMATION_0, *PUSB_PIPE_INFORMATION_0;

typedef struct _USB_LEVEL_INFORMATION {

    /* inputs: information level requested */
    ULONG InformationLevel;

    /* outputs: */
    ULONG ActualLength;

} USB_LEVEL_INFORMATION, *PUSB_LEVEL_INFORMATION;

typedef struct _USB_DEVICE_INFORMATION_0 {

    /* inputs: information level requested */
    ULONG InformationLevel;

    /* outputs: */
    ULONG ActualLength;

    /* begin level_0 information */
    ULONG PortNumber;

    /* pad descriptors to maintain DWORD alignment */
    USB_DEVICE_DESCRIPTOR DeviceDescriptor;
    UCHAR DD_pad[2];

    UCHAR CurrentConfigurationValue;
    UCHAR ReservedMBZ;
    USHORT DeviceAddress;

    ULONG HubAddress;

    USB_DEVICE_SPEED DeviceSpeed;
    USB_DEVICE_TYPE DeviceType;

    ULONG NumberOfOpenPipes;

    USB_PIPE_INFORMATION_0 PipeList[1];

} USB_DEVICE_INFORMATION_0, *PUSB_DEVICE_INFORMATION_0;



typedef struct _USB_CONTROLLER_INFORMATION_0 {

    /* inputs: information level requested */
    ULONG InformationLevel;

    /* outputs: */
    ULONG ActualLength;

    /* begin level_0 information */
    BOOLEAN SelectiveSuspendEnabled;
    BOOLEAN IsHighSpeedController;

} USB_CONTROLLER_INFORMATION_0, *PUSB_CONTROLLER_INFORMATION_0;


/*
    Structures that define extended hub port charateristics
*/

typedef struct _USB_EXTPORT_INFORMATION_0 {
    /*
       physical port ie number passed in control
       commands 1, 2, 3..255
    */
    ULONG                 PhysicalPortNumber;
    /*
       label on port may not natch the physical
       number
     */
    ULONG                 PortLabelNumber;

    USHORT                VidOverride;
    USHORT                PidOverride;
    /*
       extended port attributes as defined in
       usb.h
    */
    ULONG                 PortAttributes;
} USB_EXTPORT_INFORMATION_0, *PUSB_EXTPORT_INFORMATION;


typedef struct _USB_EXTHUB_INFORMATION_0 {

    /* inputs: information level requested */
    ULONG InformationLevel;

    /* begin level_0 information */
    ULONG NumberOfPorts;

    /* hubs don't have > 255 ports */
    USB_EXTPORT_INFORMATION_0 Port[255];

} USB_EXTHUB_INFORMATION_0, *PUSB_EXTHUB_INFORMATION_0;


#include <poppack.h>


#endif  /* __HUBBUSIF_H */



