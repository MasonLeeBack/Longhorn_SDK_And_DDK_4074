//////////////////////////////////////////////////////////////////////////////
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 2002
//
// File:    bsp.h
//
//////////////////////////////////////////////////////////////////////////////
//
// Contents:
//
//  Public BSP header.
//
// History:
//
//  07-17-2002      patmasse    creation
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <bio.h>

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
// Definitions ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// For dwMask member of BSP_DEVICEINFO structure
#define BSP_DI_HARDWAREVERSION          (0x00000001)
#define BSP_DI_DRIVERVERSION            (0x00000002)
#define BSP_DI_SERIAL                   (0x00000004)
#define BSP_DI_LOCATION                 (0x00000008)

//////////////////////////////////////////////////////////////////////////////
// Types /////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef PVOID BRM_CONTEXT_HANDLE, *PBRM_CONTEXT_HANDLE;
typedef PVOID BSP_DATA_HANDLE, *PBSP_DATA_HANDLE;

//////////////////////////////////////////////////////////////////////////////
// Forward Declarations //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef struct _BSP_BRMFUNCTIONS BSP_BRMFUNCTIONS, *PBSP_BRMFUNCTIONS;
typedef struct _BSP_DEVICEINFO BSP_DEVICEINFO, *PBSP_DEVICEINFO;
typedef struct _BSP_ITEM BSP_ITEM, *PBSP_ITEM;
typedef struct _BSP_SOURCELIST BSP_SOURCELIST, *PBSP_SOURCELIST;

//////////////////////////////////////////////////////////////////////////////
// Structures ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// BSP_BRMFUNCTIONS
//
//  Used to pass the addresses of the BRMI functions to the BSP via the
//  pFunctions parameter of the bspStartup() function.
//
struct _BSP_BRMFUNCTIONS
{
    BOOL (*pfnAddDevice)(
        IN BRM_CONTEXT_HANDLE hContext,
        IN PGUID pguidDeviceId,
        IN DWORD dwDeviceInstance,
        IN PBSP_DEVICEINFO pDeviceInfo);

    BOOL (*pfnRemoveDevice)(
        IN BRM_CONTEXT_HANDLE hContext,
        IN PGUID pguidDeviceId,
        IN DWORD dwDeviceInstance);

    BOOL (*pfnControlChange)(
        IN BRM_CONTEXT_HANDLE hContext,
        IN PVOID pvDeviceContext,
        IN DWORD dwComponentId,
        IN DWORD dwChannelId,
        IN DWORD dwControlId,
        IN INT32 iValue,
        IN DWORD dwFlags,
        IN PVOID pReserved);

    PVOID (*pfnAlloc)(
        IN BRM_CONTEXT_HANDLE hContext,
        IN DWORD dwBytes,
        IN DWORD dwFlags);

    VOID (*pfnFree)(
        IN PVOID pvBlock);
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// BSP_DEVICEINFO
//
//  This structure holds information about a device.
//
struct _BSP_DEVICEINFO
{
    DWORD cbStruct;

    DWORD dwMask;   // BSP_DI_HARDWAREVERSION
                    // BSP_DI_DRIVERVERSION
                    // BSP_DI_SERIAL
                    // BSP_DI_LOCATION
    struct
    {
        DWORD dwMajor;
        DWORD dwMinor;
        DWORD dwBuild;
    }
    HardwareVersion;

    struct
    {
        DWORD dwMajor;
        DWORD dwMinor;
        DWORD dwBuild;
    }
    DriverVersion;

    WCHAR wszLocation[256];
    WCHAR wszSerial[256];
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// BSP_ITEM
//
//  This structure is used to represent either the product of,
//  or an input to, a bspDoChannel call.
//
struct _BSP_ITEM
{
    DWORD dwType;

    union _BSP_ITEM_DATA
    {
        BSP_DATA_HANDLE Handle;

        struct _BSP_ITEM_DATA_BLOCK
        {
            DWORD cbBuffer;
            PBYTE pbBuffer;
        }
        Block;
    }
    Data;
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// BSP_SOURCELIST
//
//  This structure is used to pass a list of source items
//  when calling bspDoChannel.
//
struct _BSP_SOURCELIST
{
    DWORD dwNumSources;
    PBSP_ITEM *rgpSources;
};
//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
// Prototypes for BSP-implemented functions //////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// bspStartup
//
DWORD WINAPI bspStartup(
    IN BRM_CONTEXT_HANDLE hContext,
    IN PBSP_BRMFUNCTIONS pFunctions,
    IN DWORD dwProcessContext);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspShutdown
//
DWORD WINAPI bspShutdown();
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspOpenDevice
//
DWORD WINAPI bspOpenDevice(
    IN PGUID pguidDeviceId,
    IN DWORD dwDeviceInstance,
    OUT PVOID *ppvDeviceContext);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspCloseDevice
//
DWORD WINAPI bspCloseDevice(
    IN PVOID pvDeviceContext);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspRegisterNotify
//
DWORD WINAPI bspRegisterNotify(
    IN PVOID pvDeviceContext,
    IN BOOL fRegister,
    IN DWORD dwComponentId,
    IN DWORD dwChannelId,
    IN DWORD dwControlId);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspDoChannel
//
DWORD WINAPI bspDoChannel(
    IN PVOID pvDeviceContext,
    IN DWORD dwComponentId,
    IN DWORD dwChannelId,
    IN HANDLE hCancel,
    IN OUT BSP_DATA_HANDLE *phStateData,
    IN PBSP_SOURCELIST rgSourceLists,
    IN OUT PBSP_ITEM *rgpProducts);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspGetControl
//
DWORD WINAPI bspGetControl(
    IN PVOID pvDeviceContext,
    IN DWORD dwComponentId,
    IN DWORD dwChannelId,
    IN DWORD dwControlId,
    OUT INT32 *piValue);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspSetControl
//
DWORD WINAPI bspSetControl(
    IN PVOID pvDeviceContext,
    IN DWORD dwComponentId,
    IN DWORD dwChannelId,
    IN DWORD dwControlId,
    IN INT32 iValue);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspCreateHandleFromData
//
DWORD WINAPI bspCreateHandleFromData(
    IN PVOID pvDeviceContext,
    IN PGUID pguidFormatId,
    IN DWORD cbBuffer,
    IN PBYTE pbBuffer,
    OUT BSP_DATA_HANDLE *phData);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspGetDataFromHandle
//
DWORD WINAPI bspGetDataFromHandle(
    IN PVOID pvDeviceContext,
    IN BSP_DATA_HANDLE hData,
    OUT DWORD *pcbBuffer,
    OUT PBYTE *ppbBuffer);
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// bspCloseHandle
//
DWORD WINAPI bspCloseHandle(
    IN PVOID pvDeviceContext,
    IN BSP_DATA_HANDLE hData);
//----------------------------------------------------------------------------

#ifdef __cplusplus
} // Matches extern "C" above
#endif

//////////////////////////////////////////////////////////////////////////////
// End Content ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

