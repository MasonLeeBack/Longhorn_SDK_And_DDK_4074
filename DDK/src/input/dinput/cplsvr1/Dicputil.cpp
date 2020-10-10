//===========================================================================
// DICPUTIL.CPP
//
// DirectInput CPL helper functions.
//
// Functions:
//  DIUtilCreateDevice2FromJoyConfig()
//  DIUtilGetJoystickTypeName()
//  DIUtilGetJoystickDisplayName()
//  DIUtilGetJoystickConfigCLSID()
//  DIUtilGetJoystickCallout()
//  DIUtilPollJoystick()
//
//===========================================================================

//===========================================================================
// (C) Copyright 1998 Microsoft Corp.  All rights reserved.
//
// You have a royalty-free right to use, modify, reproduce and
// distribute the Sample Files (and/or any modified version) in
// any way you find useful, provided that you agree that
// Microsoft has no warranty obligations or liability for any
// Sample Application Files which are modified.
//===========================================================================

#include "cplsvr1.h"
#include "dicputil.h"

//===========================================================================
// DIUtilCreateDevice2FromJoyConfig
//
// Helper function to create a DirectInputDevice2 object from a 
//  DirectInputJoyConfig object.
//
// Parameters:
//  short                   nJoystickId     - joystick id for creation
//  HWND                    hWnd            - window handle
//  LPDIRECTINPUT           pdi             - ptr to base DInput object
//  LPDIRECTINPUTJOYCONFIG  pdiJoyCfg       - ptr to joyconfig object
//  LPDIRECTINPUTDEVICE     *ppdiDevice2    - ptr to device object ptr
//
// Returns: HRESULT
//
//===========================================================================
HRESULT DIUtilCreateDevice2FromJoyConfig(short nJoystickId, HWND hWnd,
                                         LPDIRECTINPUT pdi,
                                         LPDIRECTINPUTJOYCONFIG pdiJoyCfg,
                                         LPDIRECTINPUTDEVICE2 *ppdiDevice2)
{
    HRESULT                 hRes        = E_NOTIMPL;
    LPDIRECTINPUTDEVICE     pdiDevTemp  = NULL;
    DIJOYCONFIG             dijc;

    // no need to re-validate parameters.

    // get the instance GUID for device configured as nJoystickId
    // 
    // GetConfig will provide this information
    dijc.dwSize = sizeof(DIJOYCONFIG);
    hRes = pdiJoyCfg->GetConfig(nJoystickId, &dijc, DIJC_GUIDINSTANCE);
    if (FAILED(hRes))
    {
        OutputDebugString(TEXT("DIUtilCreateDeviceFromJoyConfig() - GetConfig() failed\n"));
        return hRes;
    }

    // create temporary device object
    //
    // use the instance GUID returned by GetConfig()
    hRes = pdi->CreateDevice(dijc.guidInstance, &pdiDevTemp, NULL);
    if (FAILED(hRes))
    {
        OutputDebugString(TEXT("DIUtilCreateDeviceFromJoyConfig() - CreateDevice() failed\n"));
        return hRes;
    }

    // query for a device2 object
    hRes = pdiDevTemp->QueryInterface(IID_IDirectInputDevice2, (LPVOID*)ppdiDevice2);

    // release the temporary object
    pdiDevTemp->Release();

    if (FAILED(hRes))
    {
        OutputDebugString(TEXT("DIUtilCreateDeviceFromJoyConfig() - QueryInterface(IDirectInputDevice2) failed\n"));
        return hRes;
    }

    // set the desired data format
    //
    // we want to be a joystick
    hRes = (*ppdiDevice2)->SetDataFormat(&c_dfDIJoystick);
    if (FAILED(hRes))
    {
        OutputDebugString(TEXT("DIUtilCreateDeviceFromJoyConfig() - SetDataFormat(Joystick) failed\n"));
        return hRes;
    }

    // set the cooperative level for the device
    //
    // want to set EXCLUSIVE | BACKGROUND
    hRes = (*ppdiDevice2)->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND);
    if (FAILED(hRes))
    {
        OutputDebugString(TEXT("DIUtilCreateDeviceFromJoyConfig() - SetCooperativeLevel() failed\n"));
        return hRes;
    }

    // all is well
    return hRes;

} //*** end DIUtilCreateDevice2FromJoyConfig()


//===========================================================================
// DIUtilGetJoystickTypeName
//
// Retrieves the joystick type name for the specified object.
//
// Parameters:
//  short                   nJoystickId - joystick id
//  LPDIRECTINPUTJOYCONFIG  pdiJoyCfg   - ptr to joyconfig object
//  LPTSTR                  tszTypeName - ptr to string buffer
//  int                     nBugSize    - size of string buffer
//
// Returns: HRESULT
//
//===========================================================================
HRESULT DIUtilGetJoystickTypeName(short nJoystickId, LPDIRECTINPUTJOYCONFIG pdiJoyCfg, LPTSTR tszTypeName, int nBufSize)
{
    DIJOYCONFIG  dijc;

    // no need to re-validate parameters.

    // get the type name
    ZeroMemory(&dijc, sizeof(dijc));
    dijc.dwSize = sizeof(dijc);

    HRESULT hRes = pdiJoyCfg->GetConfig(nJoystickId, &dijc, DIJC_REGHWCONFIGTYPE);

    if (SUCCEEDED(hRes))
    {
#ifndef UNICODE
        // we've compiled for ANSI
        //
        // we need to convert the type name string
        WideCharToMultiByte(CP_ACP, 0, dijc.wszType, -1, tszTypeName, MAX_JOYSTRING, NULL, NULL);
#else
        // we've compiled for UNICODE
        //
        // no conversion needed
        lstrcpy(tszTypeName, dijc.wszType);
#endif
    } else
    {
        LoadString(ghInst, IDS_ERROR, tszTypeName, nBufSize);
        OutputDebugString (tszTypeName);
    }

    // we're done
    return hRes;

} //*** end DIUtilGetJoystickTypeName()


//===========================================================================
// DIUtilGetJoystickDisplayName
//
// Retrieves the joystick display name for the specified object.
//
// Parameters:
//  short                   nJoystickId - joystick id
//  LPDIRECTINPUTJOYCONFIG  pdiJoyCfg   - ptr to joyconfig object
//  LPTSTR                  tszDispName - ptr to string buffer
//  int                     nBugSize    - size of string buffer
//
// Returns: HRESULT
//
//===========================================================================
HRESULT DIUtilGetJoystickDisplayName(short nJoystickId, LPDIRECTINPUTJOYCONFIG pdiJoyCfg, LPTSTR tszDispName, int nBufSize)
{
    DIJOYCONFIG dijc;
    HRESULT     hres;

    // no need to re-validate parameters.

    // get the display name
    ZeroMemory(&dijc, sizeof(DIJOYCONFIG));
    dijc.dwSize = sizeof(dijc);

    hres = pdiJoyCfg->GetConfig(nJoystickId, &dijc, DIJC_REGHWCONFIGTYPE);
    if ( SUCCEEDED(hres) )
    {
        DIJOYTYPEINFO  dijti;

        // get the display name
        ZeroMemory(&dijti, sizeof(dijti));
        dijti.dwSize = sizeof(dijti);

        hres = pdiJoyCfg->GetTypeInfo(dijc.wszType, &dijti, DITC_DISPLAYNAME);
        if (SUCCEEDED(hres))
        {
#ifndef UNICODE
            // we've compiled for ANSI
            //
            // we need to convert the type name string
            WideCharToMultiByte(CP_ACP, 0, dijti.wszDisplayName, -1, tszDispName, MAX_JOYSTRING, NULL, NULL);
#else
            // we've compiled for UNICODE
            //
            // no conversion needed
            lstrcpy(tszDispName, dijc.wszType);
#endif
        } else
        {
            LoadString(ghInst, IDS_ERROR, tszDispName, nBufSize);
            OutputDebugString (tszDispName);
        }
    } else
    {
        LoadString(ghInst, IDS_ERROR, tszDispName, nBufSize);
        OutputDebugString (tszDispName);
    }

    // we're done
    return hres;

} //*** end DIUtilGetJoystickDisplayName()


//===========================================================================
// DIUtilGetJoystickConfigCLSID
//
// Retrieves the joystick ConfigCLSID for the specified object.
//
// Parameters:
//  short                   nJoystickId - joystick id
//  LPDIRECTINPUTJOYCONFIG  pdiJoyCfg   - ptr to joyconfig object
//  CLSID                   *pclsid     - ptr to store CLSID    
//
// Returns: HRESULT
//
//===========================================================================
HRESULT DIUtilGetJoystickConfigCLSID(short nJoystickId, 
                                     LPDIRECTINPUTJOYCONFIG pdiJoyCfg,
                                     CLSID* pclsid)
{
    DIJOYCONFIG dijc;

    // no need to re-validate parameters.

    // get the type name
    ZeroMemory(&dijc, sizeof(dijc));
    dijc.dwSize = sizeof(dijc);

    HRESULT hRes = pdiJoyCfg->GetConfig(nJoystickId, &dijc, DIJC_REGHWCONFIGTYPE);

    if (SUCCEEDED(hRes))
    {
        DIJOYTYPEINFO  dijti;

        // get the clsid
        ZeroMemory(&dijti, sizeof(&dijti));
        dijti.dwSize = sizeof(dijti);

        hRes = pdiJoyCfg->GetTypeInfo(dijc.wszType, &dijti, DITC_CLSIDCONFIG);
        if (SUCCEEDED(hRes))
        {
            // return the CLSID
            *pclsid = dijti.clsidConfig;
        } else
        {
            // return a NULL GUID
            *pclsid = (CLSID)NULL_GUID;
        }

    }

    // we're done
    return hRes;

} //*** end DIUtilGetJoystickConfigCLSID()



//===========================================================================
// DIUtilGetJoystickCallout
//
// Retrieves the joystick callout for the specified object.
//
// Parameters:
//  short                   nJoystickId - joystick id
//  LPDIRECTINPUTJOYCONFIG  pdiJoyCfg   - ptr to joyconfig object
//  LPTSTR                  tszCallout  - ptr to string buffer
//  int                     nBugSize    - size of string buffer
//
// Returns: HRESULT
//
//===========================================================================
HRESULT DIUtilGetJoystickCallout(short nJoystickId, 
                                 LPDIRECTINPUTJOYCONFIG pdiJoyCfg,
                                 LPTSTR tszCallout, int nBufSize)
{
    HRESULT                 hRes        = E_NOTIMPL;
    DIJOYCONFIG             dijc;

    // no need to re-validate parameters.

    // get the callout
    ZeroMemory(&dijc, sizeof(DIJOYCONFIG));
    dijc.dwSize = sizeof(DIJOYCONFIG);
    hRes = pdiJoyCfg->GetConfig(nJoystickId, &dijc, DIJC_CALLOUT);
    if (FAILED(hRes))
    {
        LoadString(ghInst, IDS_ERROR, tszCallout, nBufSize);
        return hRes;
    }

#ifndef UNICODE
    // we've compiled for ANSI
    //
    // we need to convert the type name string
    WideCharToMultiByte(CP_ACP, 0, dijc.wszCallout, -1, tszCallout,
                        MAX_JOYSTRING, NULL, NULL);
#else
    // we've compiled for UNICODE
    //
    // no conversion needed
    lstrcpy(tszCallout, dijc.wszType);
#endif

    // if there is no callout name, then display a default string
    if (0 == lstrcmp(tszCallout, TEXT("")))
    {
        LoadString(ghInst, IDS_DEFAULT, tszCallout, nBufSize);
    }


    // we're done
    return hRes;

} //*** end DIUtilGetJoystickCallout()


//===========================================================================
// DIUtilPollJoystick
//
// Polls the joystick device and returns the device state.
//
// Parameters:
//  LPDIRECTINPUTDEVICE2    pdiDevice2  - ptr to device object
//  DIJOYSTATE              *pdijs      - ptr to store joystick state
//
// Returns: HRESULT
//
//===========================================================================
HRESULT DIUtilPollJoystick(LPDIRECTINPUTDEVICE2 pdiDevice2, DIJOYSTATE *pdijs)
{
    HRESULT hRes    = E_NOTIMPL;

    // clear the pdijs memory
    //
    // this way, if we fail, we return no data
    ZeroMemory(pdijs, sizeof(DIJOYSTATE));

    // poll the joystick
    //
    // don't worry if it fails, not all devices require polling
    hRes = pdiDevice2->Poll();

    // query the device state
    hRes = pdiDevice2->GetDeviceState(sizeof(DIJOYSTATE), pdijs);
    if (FAILED(hRes))
    {
        OutputDebugString(TEXT("DIUtilPollJoystick() - GetDeviceState() failed\n"));
        return hRes;
    }

    // done
    return hRes;

} //*** end DIUtilPollJoystick()

























