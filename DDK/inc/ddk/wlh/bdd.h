///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 2004
//
// File: bdd.h
//
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Contents:
//
//  Public BDD header.
//
// History:
//
//  11-01-2003      patmasse    creation
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#define BDD_INVOKED
#include <bio.h>

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// Types //////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef PVOID BDD_DATA_HANDLE, *PBDD_DATA_HANDLE;

//////////////////////////////////////////////////////////////////////////////////////////////////
// Definitions ///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

#define BDD_DI_HARDWAREVERSION          (0x00000001)
#define BDD_DI_DRIVERVERSION            (0x00000002)
#define BDD_DI_SERIAL                   (0x00000004)

//////////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _BDD_BDDFUNCTIONS BDD_BDDFUNCTIONS, *PBDD_BDDFUNCTIONS;
typedef struct _BDD_DEVICEINFO BDD_DEVICEINFO, *PBDD_DEVICEINFO;
typedef struct _BDD_ITEM BDD_ITEM, *PBDD_ITEM;
typedef struct _BDD_SOURCELIST BDD_SOURCELIST, *PBDD_SOURCELIST;

typedef struct _BDD_PARAMS_REGISTERNOTIFY BDD_PARAMS_REGISTERNOTIFY, *PBDD_PARAMS_REGISTERNOTIFY;
typedef struct _BDD_PARAMS_DOCHANNEL BDD_PARAMS_DOCHANNEL, *PBDD_PARAMS_DOCHANNEL;
typedef struct _BDD_PARAMS_GETCONTROL BDD_PARAMS_GETCONTROL, *PBDD_PARAMS_GETCONTROL;
typedef struct _BDD_PARAMS_SETCONTROL BDD_PARAMS_SETCONTROL, *PBDD_PARAMS_SETCONTROL;
typedef struct _BDD_PARAMS_CREATEHANDLE_FROMDATA BDD_PARAMS_CREATEHANDLE_FROMDATA, *PBDD_PARAMS_CREATEHANDLE_FROMDATA;
typedef struct _BDD_PARAMS_CLOSEHANDLE BDD_PARAMS_CLOSEHANDLE, *PBDD_PARAMS_CLOSEHANDLE;
typedef struct _BDD_PARAMS_GETDATA_FROMHANDLE BDD_PARAMS_GETDATA_FROMHANDLE, *PBDD_PARAMS_GETDATA_FROMHANDLE;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Structures /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// BDD_BDDFUNCTIONS
//
//  Used to pass the addresses of the BDD functions to the BCF.
//
struct _BDD_BDDFUNCTIONS
{
    ULONG Size;

    WDFSTATUS (*pfnOpenDevice)(
        IN WDFDEVICE hDevice);

    WDFSTATUS (*pfnCloseDevice)(
        IN WDFDEVICE hDevice);

    WDFSTATUS (*pfnDoChannel)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_DOCHANNEL pParams);

    WDFSTATUS (*pfnGetControl)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_GETCONTROL pParams);

    WDFSTATUS (*pfnSetControl)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_SETCONTROL pParams);

    WDFSTATUS (*pfnRegisterNotify)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_REGISTERNOTIFY pParams);

    WDFSTATUS (*pfnCreateHandleFromData)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_CREATEHANDLE_FROMDATA pParams);

    WDFSTATUS (*pfnCloseHandle)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_CLOSEHANDLE pParams);

    WDFSTATUS (*pfnGetDataFromHandle)(
        IN WDFDEVICE hDevice,
        IN PBDD_PARAMS_GETDATA_FROMHANDLE pParams);
};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// BDD_DEVICEINFO
//
//  This structure holds information about a device.
//
struct _BDD_DEVICEINFO
{
    ULONG Size;

    ULONG Mask;     // BDD_DI_HARDWAREVERSION
                    // BDD_DI_DRIVERVERSION
                    // BDD_DI_SERIAL
    struct
    {
        ULONG Major;
        ULONG Minor;
        ULONG Build;
    }
    HardwareVersion;

    struct
    {
        ULONG Major;
        ULONG Minor;
        ULONG Build;
    }
    DriverVersion;

    WCHAR wszSerial[256];
};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// BDD_ITEM
//
//  This structure is used to represent either the product of
//  or a source to a bddDoChannel call.
//
struct _BDD_ITEM
{
    ULONG Type;

    union _BDD_ITEM_DATA
    {
        BDD_DATA_HANDLE Handle;

        struct _BDD_ITEM_DATA_BLOCK
        {
            ULONG cBuffer;
            PUCHAR pBuffer;
        }
        Block;
    }
    Data;
};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// BDD_SOURCELIST
//
//  This structure is used to pass a list of source items
//  when calling bddDoChannel.
//
struct _BDD_SOURCELIST
{
    ULONG NumSources;
    PBDD_ITEM *rgpSources;
};
//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
// BDD Function Parameter Structures //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

struct _BDD_PARAMS_REGISTERNOTIFY
{
    IN ULONG Size;
    IN ULONG fRegister;
    IN ULONG ComponentId;
    IN ULONG ChannelId;
    IN ULONG ControlId;
};

struct _BDD_PARAMS_DOCHANNEL
{
    IN ULONG Size;
    IN ULONG ComponentId;
    IN ULONG ChannelId;
    IN PKEVENT CancelEvent;
    IN BDD_SOURCELIST *rgSourceLists;
    IN OUT BDD_DATA_HANDLE hStateData;
    OUT PBDD_ITEM *rgpProducts;
    OUT ULONG BIOReturnCode;
};

struct _BDD_PARAMS_GETCONTROL
{
    IN ULONG Size;
    IN ULONG ComponentId;
    IN ULONG ChannelId;
    IN ULONG ControlId;
    OUT INT32 Value;
};

struct _BDD_PARAMS_SETCONTROL
{
    IN ULONG Size;
    IN ULONG ComponentId;
    IN ULONG ChannelId;
    IN ULONG ControlId;
    IN INT32 Value;
};

struct _BDD_PARAMS_CREATEHANDLE_FROMDATA
{
    IN ULONG Size;
    IN GUID guidFormatId;
    IN ULONG cBuffer;
    IN PUCHAR pBuffer;
    OUT BDD_DATA_HANDLE hData;
};

struct _BDD_PARAMS_CLOSEHANDLE
{
    IN ULONG Size;
    IN BDD_DATA_HANDLE hData;
};

struct _BDD_PARAMS_GETDATA_FROMHANDLE
{
    IN ULONG Size;
    IN BDD_DATA_HANDLE hData;
    IN OUT ULONG cBuffer;
    IN OUT PUCHAR pBuffer;
    OUT ULONG BIOReturnCode;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// BCF Function Declarations //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// bcfDeviceInit()
//
// Called in response to the BDD receiving its EvtDeviceAdd call.  This lets the BCF know
// that a new BDD-managed device has been loaded and allows the BCF to initialize its state so
// that it can receive IOCTLs for the newly loaded device.
//
// The BcfInitialize call will initialize its portion of the device context, and create the WDF
// default Queue. This ensures that the BCF will receive the callbacks when IOCTLs arrive. The
// BCF will then decode the IOCTLs and forward them to the appropriate BDD functions. A BDD must
// call BcfInitialize during its EvtDeviceStart WDF callback function, after initializing
// communications with the device and retrieving the data required for filling in pBddInfo.
//
// Parmeters:
// IN hDevice           - This must be the WDFDEVICE object handle that was passed into the BDD's
//                        EvtDeviceStart call.
// IN pBDDFunctions     - Pointer to a BDD_BDDFUNCTIONS structure that is filled in with the
//                        entry points that the BDD exports to support the BDD API set.  The
//                        pointers themselves are copied by the BCF, as opposed to saving the
//                        pBDDFunctions pointer, so the memory pointed to by pBDDFunctions
//                        need not remain accessible after the BcfDeviceAdd call.
//
// Returns:
// A WDFSTATUS code
//
WDFSTATUS bcfDeviceInit(
    IN PWDFDEVICE_INIT pDeviceInit,
    IN WDFDEVICE hDevice,
    IN PBDD_BDDFUNCTIONS pBddFunctions);
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// bcfDeviceStart()
//
// Called in response to the BDD receiving its EvtDeviceStart call.
//
// Parmeters:
// IN hDevice           - This must be the WDFDEVICE object handle that was passed into the BDD's
//                        EvtDeviceStart call.
// IN pBDDInfo          - Pointer to a  BDD_DEVICEINFO structure that is filled in with the version
//                        and other information about the BDD and its Device. The data in the
//                        structure is copied by the BCF, as opposed to saving the pointer, so
//                        so the memory pointed to by pBDDFunctions need not remain accessible
//                        after the BcfInitialize call.
//
// Returns:
// A WDFSTATUS code
//
WDFSTATUS bcfDeviceStart(
    IN WDFDEVICE hDevice,
    IN PBDD_DEVICEINFO pDeviceInfo);
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// bcfDeviceStart()
//
// Called in response to the BDD receiving its EvtDeviceStop call.
//
// Parmeters:
// IN hDevice           - This must be the WDFDEVICE object handle that was passed into the BDD's
//                        EvtDeviceStart call.
VOID bcfDeviceStop(
    IN WDFDEVICE hDevice);
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// bcfControlChange()
//
// This function allows BDDs to asynchronously report changes to the values of its controls.
//
// BcfControlChange is generally called by the BDD in response to one of its controls changing a
// value.  Specifically, it is most often used in the case of a sensor control that has changed
// from 0 to 1 indicating that a source is present and a sample can be taken.
//
// Parameters:
// IN hDevice       - This must be the WDFDEVICE object handle of the device containing the
//                    specified control.
// IN ComponentId   - Specifies either the Component ID of the component in which the control or
//                    the control's parent channel resides, or '0' to indicate that dwControlId
//                    refers to a device control.
// IN ChannelId     - If dwComponentId is not '0', dwChannelId specifies either the Channel ID of
//                    the channel in which the control resides, or '0' to indicate that dwControlId
//                    refers to a component control. Ignored if dwComponentId is '0'.
// IN ControlId     - ControlId of the changed control.
// IN Value         - Specifies the new value for the control .
// IN Flags         - Unused.  Must be 0.
// IN pReserved     - Unused.  Must be NULL.
//
// Rerturns:
// A WDFSTATUS code
//
WDFSTATUS bcfControlChange(
    IN WDFDEVICE hDevice,
    IN ULONG ComponentId,
    IN ULONG ChannelId,
    IN ULONG ControlId,
    IN INT32 Value,
    IN ULONG Flags,
    IN PVOID pReserved);
//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
// Support for WDF Strong Context Typing //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(_X86_)
#define BCF_DEVICE_EXTENSION_SIZE (0x00000568)
#elif (defined(_IA64_) || defined(_AMD64_))
#define BCF_DEVICE_EXTENSION_SIZE (0x00001390)
#endif

#define BDD_DECLARE_CONTEXT_EXTENSION_TYPE(_extension_type_)                                \
                                                                                            \
typedef _extension_type_ BDD_DEVICE_EXTENSION, *PBDD_DEVICE_EXTENSION;                      \
                                                                                            \
typedef struct _BCF_DEVICE_CONTEXT                                                          \
{                                                                                           \
    BYTE pbReserved[BCF_DEVICE_EXTENSION_SIZE];                                             \
    BDD_DEVICE_EXTENSION Extension;                                                         \
}                                                                                           \
BCF_DEVICE_CONTEXT, *PBCF_DEVICE_CONTEXT;                                                   \
                                                                                            \
WDF_DECLARE_CONTEXT_TYPE(BCF_DEVICE_CONTEXT);                                               \
                                                                                            \
PBDD_DEVICE_EXTENSION FORCEINLINE bcfGetDeviceExtension(                                    \
    IN WDFOBJECT Handle)                                                                    \
{                                                                                           \
    return (PBDD_DEVICE_EXTENSION) &(((PBCF_DEVICE_CONTEXT)WdfObjectGetTypedContextWorker(  \
        Handle, WDF_GET_CONTEXT_TYPE_INFO(BCF_DEVICE_CONTEXT)))->Extension);                \
}                                                                                           \
                                                                                            \
VOID FORCEINLINE BDD_DEVICE_OBJECT_ATTRIBUTES_INIT(                                         \
    IN PWDF_OBJECT_ATTRIBUTES pAttributes)                                                  \
{                                                                                           \
    WDF_OBJECT_ATTRIBUTES_INIT(pAttributes);                                                \
    WDF_OBJECT_ATTRIBUTES_SET_CONTEXT_TYPE(pAttributes, BCF_DEVICE_CONTEXT);                \
}                                                                                           \

///////////////////////////////////////////////////////////////////////////////////////////////////
// End Content ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif


