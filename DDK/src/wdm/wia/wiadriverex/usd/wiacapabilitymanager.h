/*****************************************************************************
 *
 *  wiacapabilitymanager.h
 *
 *  Copyright (c) 2003 Microsoft Corporation.  All Rights Reserved.
 *
 *  DESCRIPTION:
 *
 *  Contains class declaration for CWIACapabilityManager
 *  
 *******************************************************************************/

#pragma once

#define MAX_CAPABILITY_STRING_SIZE_BYTES (sizeof(WCHAR) * MAX_PATH)

class CWIACapabilityManager {
public:
    CWIACapabilityManager();
    ~CWIACapabilityManager();
public:
    HRESULT Initialize(HINSTANCE hInstance);
    void Destroy();
    HRESULT AddCapability(const GUID    guidCapability,
                          UINT          uiNameResourceID,
                          UINT          uiDescriptionResourceID,
                          ULONG         ulFlags,
                          LPWSTR        wszIcon);
    HRESULT DeleteCapability(const GUID guidCapability,ULONG ulFlags);
    HRESULT AllocateCapability(WIA_DEV_CAP_DRV **ppWIADeviceCapability);
    void FreeCapability(WIA_DEV_CAP_DRV *pWIADeviceCapability, BOOL bFreeCapabilityContentOnly = FALSE);
    LONG GetNumCapabilities();
    LONG GetNumCommands();
    LONG GetNumEvents();

    WIA_DEV_CAP_DRV* GetCapabilities();
    WIA_DEV_CAP_DRV* GetCommands();
    WIA_DEV_CAP_DRV* GetEvents();
private:
    HINSTANCE                            m_hInstance;
    CBasicDynamicArray<WIA_DEV_CAP_DRV> m_CapabilityArray;
};
