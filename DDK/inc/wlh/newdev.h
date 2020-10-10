/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    newdev.h

Abstract:

    Public header file for Windows NT Driver Installation DLL.

--*/

#ifndef _INC_NEWDEV
#define _INC_NEWDEV

#include <pshpack1.h>   // Assume byte packing throughout
#include <setupapi.h>   // for HDEVINFO, PSP_DEVINFO_DATA, and PSP_DRVINFO_DATA

#ifdef __cplusplus
extern "C" {
#endif


//
// Flags for UpdateDriverForPlugAndPlayDevices
//
#define INSTALLFLAG_FORCE           0x00000001      // Force the installation of the specified driver
#define INSTALLFLAG_READONLY        0x00000002      // Do a read-only install (no file copy)
#define INSTALLFLAG_NONINTERACTIVE  0x00000004      // No UI shown at all. API will fail if any UI must be shown.
#define INSTALLFLAG_BITS            0x00000007

BOOL
WINAPI
UpdateDriverForPlugAndPlayDevicesA(
    IN     HWND hwndParent,
    IN     LPCSTR HardwareId,
    IN     LPCSTR FullInfPath,
    IN     DWORD InstallFlags,
    IN OUT PBOOL bRebootRequired OPTIONAL
    );

BOOL
WINAPI
UpdateDriverForPlugAndPlayDevicesW(
    IN     HWND hwndParent,
    IN     LPCWSTR HardwareId,
    IN     LPCWSTR FullInfPath,
    IN     DWORD InstallFlags,
    IN OUT PBOOL bRebootRequired OPTIONAL
    );

#ifdef UNICODE
#define UpdateDriverForPlugAndPlayDevices UpdateDriverForPlugAndPlayDevicesW
#else
#define UpdateDriverForPlugAndPlayDevices UpdateDriverForPlugAndPlayDevicesA
#endif

#if (WINVER >= 0x600)
//
// Flags for DiInstallDevice
//
#define DIIDFLAG_SHOWSEARCHUI           0x00000001      // Show search UI if no drivers can be found.
#define DIIDFLAG_NOFINISHINSTALLUI      0x00000002      // Do NOT show the finish install UI.
#define DIIDFLAG_INSTALLNULLDRIVER      0x00000004      // Install the NULL driver on this device.
#define DIIDFLAG_BITS                   0x00000007

BOOL
DiInstallDevice(
    IN     HWND hwndParent,
    IN     HDEVINFO DeviceInfoSet,
    IN     PSP_DEVINFO_DATA DeviceInfoData,
    IN     PSP_DRVINFO_DATA DriverInfoData,    OPTIONAL
    IN     DWORD Flags,
    IN OUT PBOOL NeedReboot    OPTIONAL
    );
#endif // (WINVER >= 0x600)

#if (WINVER >= 0x600)
BOOL
DiShowUpdateDevice(
    IN     HWND hwndParent,
    IN     HDEVINFO DeviceInfoSet,
    IN     PSP_DEVINFO_DATA DeviceInfoData,
    IN     DWORD Flags,
    IN OUT PBOOL NeedReboot     OPTIONAL
    );
#endif // (WINVER >= 0x600)


#ifdef __cplusplus
}
#endif

#include <poppack.h>

#endif // _INC_NEWDEV


