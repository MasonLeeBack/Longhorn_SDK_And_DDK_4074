/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

        USBDRIVR.H

Abstract:

   This file defines kernel mode ioctls available to USB
   drivers.

   The IOCTLS are sent to the PDO enumerated for USB devices by
   the USB 'enumerator' -- the usb hub driver.

Environment:

    Kernel mode

Revision History:

--*/

#ifndef   __USBDRIVR_H__
#define   __USBDRIVR_H__


#include "usbiodef.h"
#include "usb.h"
#include "usbdlib.h"
#include "usbbusif.h"


/*
Routine Description:
Define the standard USB 'URB' IOCTL

IOCTL_INTERNAL_USB_SUBMIT_URB

This IOCTL is used by client drivers to submit URB (USB Request Blocks)

Parameters.Others.Argument1 = pointer to URB

*/

#define IOCTL_INTERNAL_USB_SUBMIT_URB  CTL_CODE(FILE_DEVICE_USB,  \
                                                USB_SUBMIT_URB,  \
                                                METHOD_NEITHER,  \
                                                FILE_ANY_ACCESS)

/* IOCTL_INTERNAL_USB_RESET_PORT

    This IOCTL is used by kernel mode drivers to reset their
    upstream port.

    After a successful reset the device is re-configured to the
    same configuration it was in before the reset.  All pipe
    handles, configuration handles and interface handles remain
    valid.

*/

#define IOCTL_INTERNAL_USB_RESET_PORT  CTL_CODE(FILE_DEVICE_USB,  \
                                                USB_RESET_PORT, \
                                                METHOD_NEITHER,  \
                                                FILE_ANY_ACCESS)

/* IOCTL_INTERNAL_USB_CYCLE_PORT

    This IOCTL will simulate a plug/unplug on the drivers upstream
    port.  The device will be removed and re-added by PnP.
*/

#define IOCTL_INTERNAL_USB_CYCLE_PORT  CTL_CODE(FILE_DEVICE_USB,  \
                                                USB_CYCLE_PORT, \
                                                METHOD_NEITHER,  \
                                                FILE_ANY_ACCESS)


/* IOCTL_INTERNAL_USB_GET_PORT_STATUS

Routine Description:
This function returns the current 'live' status of the port.  It can be used
by client drivers to determine the current state of their device because
certain hardware errors on the bus can result in a device port being disabled
.  The hub driver must communicate with the hub to get this information, if
it cannot for some reason a failure status is returned.

This API will fail if called at raised IRQL.

IRQL: Passive

Parameters:
ioStackLocation->Parameters.Others.Argument1
A pointer to a ULONG that is filled in with the port status bits defined below:

*/

#define  USBD_PORT_ENABLED      0x00000001
#define  USBD_PORT_CONNECTED    0x00000002


#define IOCTL_INTERNAL_USB_GET_PORT_STATUS  CTL_CODE(FILE_DEVICE_USB,  \
                                                USB_GET_PORT_STATUS, \
                                                METHOD_NEITHER,  \
                                                FILE_ANY_ACCESS)

/* IOCTL_INTERNAL_USB_SUBMIT_IDLE_NOTIFICATION

This ioctl registers a device to receive notification when a specific
timeout has expired and it should now be suspended in order to conserve
power. If all devices on a hub are suspended, then the actual hub
can be suspended.

Routine Description:
This function is part of the hub drivers selective suspend feature (see
section 2 usbhub.doc).   This API is serviced only by hubs it is not supported
by a USB Port driver.  The client USB drivers use this API to register an idle
callback request with the parent hub.  The details on how this API is handled
can be found in section 2.

Parameters:
ioStackLocation->Parameters.Others.Argument1
>>IdeCallbackInfo
A pointer to a structure containing the callback routine and a context value.

typedef
VOID
(*USB_IDLE_CALLBACK)(
    PVOID Context
    );

typedef struct _USB_IDLE_CALLBACK_INFO {
    USB_IDLE_CALLBACK IdleCallback;
    PVOID IdleContext;
} USB_IDLE_CALLBACK_INFO, *PUSB_IDLE_CALLBACK_INFO;

*/


#define IOCTL_INTERNAL_USB_SUBMIT_IDLE_NOTIFICATION  CTL_CODE(FILE_DEVICE_USB,\
                                                USB_IDLE_NOTIFICATION,  \
                                                METHOD_NEITHER,  \
                                                FILE_ANY_ACCESS)


/* IOCTL_INTERNAL_USB_RECORD_FAILURE

    This IOCTL records a start failure reason with the device PDO.

    Parameters.Others.Argument1 =
        pointer to start failure data struct _USB_START_FAILDATA
        see USBIODEF.H

*/


#define IOCTL_INTERNAL_USB_RECORD_FAILURE  CTL_CODE(FILE_DEVICE_USB,  \
                                                USB_RECORD_FAILURE, \
                                                METHOD_NEITHER,  \
                                                FILE_ANY_ACCESS)

#endif // __USBDRIVR_H__

