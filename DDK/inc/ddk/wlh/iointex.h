/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    iointex.h

Abstract:

    This header exposes the new IO APIs to connect and disconnect interrupts 

Author:

    Adrian J. Oney  - April 21, 2002

Revision History:

    01/28/2003 - splante - Changed for use in IoInt.lib

--*/

#ifndef _IOINTEX_H_
#define _IOINTEX_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Supply overrideable library implementation of IoConnectInterruptEx.
// This function is similar to IoConnectInterrupt except that it uses a 
// different calling convention. IoConnectInterrupt will be removed in the
// future and should no longer be called.
//
// See DDK documentation for more details.
//
#undef IoConnectInterruptEx
#define IoConnectInterruptEx WdmlibIoConnectInterruptEx

NTSTATUS
WdmlibIoConnectInterruptEx(
    IN  OUT PIO_CONNECT_INTERRUPT_PARAMETERS    Parameters
    );

//
// Supply overrideable library implementation of IoDisconnectInterruptEx.
// This fucntion is similar to IoDisconnectInterrupt except that it uses a 
// different calling convention. IoDisconnectInterrupt will be removed in the
// future and should no longer be called.
//
// See DDK documentation for more details.
//
#undef IoDisconnectInterruptEx
#define IoDisconnectInterruptEx WdmlibIoDisconnectInterruptEx

NTSTATUS
WdmlibIoDisconnectInterruptEx(
    IN  OUT PIO_DISCONNECT_INTERRUPT_PARAMETERS Parameters
    );


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _WDMSEC_H_


