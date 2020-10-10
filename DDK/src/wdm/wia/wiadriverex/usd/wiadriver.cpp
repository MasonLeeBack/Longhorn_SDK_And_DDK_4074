/**************************************************************************
*
*  Copyright (c) 2003  Microsoft Corporation
*
*  Title: wiadriver.cpp
*
*  Description: This file contains the implementation of IStiUSD and IWiaMiniDrv
*               in the class CWIADriver.
*               The file also contains all COM DLL entry point functions and an
*               implementation of IClassFactory, CWIADriverClassFactory. 
*
***************************************************************************/

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <initguid.h>
#include "stdafx.h"
#include <strsafe.h>

HINSTANCE g_hInst = NULL;

///////////////////////////////////////////////////////////////////////////////
// WIA driver GUID
///////////////////////////////////////////////////////////////////////////////

// {EEA1E6F7-A59C-487a-BFFA-BD8AA99FE501}
DEFINE_GUID(CLSID_WIADriver, 0xeea1e6f7, 0xa59c, 0x487a, 0xbf, 0xfa, 0xbd, 0x8a, 0xa9, 0x9f, 0xe5, 0x3);

#define HANDLED_PRIVATE_STATUS_ERROR_1      MAKE_HRESULT(SEVERITY_ERROR,   FACILITY_ITF, 1001)
#define UNHANDLED_PRIVATE_STATUS_ERROR_1    MAKE_HRESULT(SEVERITY_ERROR,   FACILITY_ITF, 1002)
#define UNHANDLED_PRIVATE_STATUS_MESSAGE_1  MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 1001)


///////////////////////////////////////////////////////////////////////////
// Construction/Destruction Section
///////////////////////////////////////////////////////////////////////////

CWIADriver::CWIADriver(LPUNKNOWN punkOuter)
{
    if(punkOuter)
    {
        m_punkOuter = punkOuter;
    }

    m_cRef                  = 1;
    m_punkOuter             = NULL;
    m_pIDrvItemRoot         = NULL;
    m_lClientsConnected     = 0;
    m_pFormats              = NULL;
    m_ulNumFormats          = 0;
    m_bstrDeviceID          = NULL;
    m_bstrRootFullItemName  = NULL;
    m_ulImageLibraryToken   = 0;
    m_pIStiDevice           = NULL;
    memset(m_wszStoragePath,0,sizeof(m_wszStoragePath));

    //
    // Intialize GDI+ image library for image manipulation
    //

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    if(GdiplusStartup(&m_ulImageLibraryToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
    {
        WIAS_ERROR((g_hInst, "GDI+ image library could not be initialized"));
    }
}

CWIADriver::~CWIADriver()
{
    HRESULT hr = S_OK;

    if(m_bstrDeviceID)
    {
        SysFreeString(m_bstrDeviceID);
        m_bstrDeviceID = NULL;
    }

    if(m_bstrRootFullItemName)
    {
        SysFreeString(m_bstrRootFullItemName);
        m_bstrRootFullItemName = NULL;
    }

    //
    // Free cached driver capability array
    //

    m_CapabilityManager.Destroy();

    //
    // Free cached driver format array
    //

    if(m_pFormats)
    {
        WIAS_TRACE((g_hInst,"Deleting WIA format array memory"));
        delete [] m_pFormats;
        m_pFormats = NULL;
        m_ulNumFormats = 0;
    }

    //
    // Unlink and release the cached IWiaDrvItem root item interface.
    //

    DestroyDriverItemTree();

    //
    // Unintialize/shutdown GDI+ image library
    //

    if(m_ulImageLibraryToken)
    {
        Gdiplus::GdiplusShutdown(m_ulImageLibraryToken);
        m_ulImageLibraryToken = 0;
    }
}

///////////////////////////////////////////////////////////////////////////
// Standard COM Section
///////////////////////////////////////////////////////////////////////////

HRESULT CWIADriver::QueryInterface( REFIID riid, LPVOID * ppvObj)
{
    if(!m_punkOuter)
    {
        return E_NOINTERFACE;
    }
    return m_punkOuter->QueryInterface(riid,ppvObj);
}
ULONG CWIADriver::AddRef()
{
    if(!m_punkOuter)
    {
        return 0;
    }
    return m_punkOuter->AddRef();
}
ULONG CWIADriver::Release()
{
    if(!m_punkOuter)
    {
        return 0;
    }
    return m_punkOuter->Release();
}

///////////////////////////////////////////////////////////////////////////
// IStiUSD Interface Section (for all WIA drivers)
///////////////////////////////////////////////////////////////////////////

HRESULT CWIADriver::Initialize(PSTIDEVICECONTROL pHelDcb,
                               DWORD             dwStiVersion,
                               HKEY              hParametersKey)
{
    HRESULT hr = E_INVALIDARG;
    if((pHelDcb)&&(hParametersKey))
    {
        //
        // Open DeviceData section in the registry
        //

        HKEY hDeviceDataKey = NULL;
        if(RegOpenKeyEx(hParametersKey,REG_ENTRY_DEVICEDATA,0,KEY_QUERY_VALUE|KEY_READ,&hDeviceDataKey) == ERROR_SUCCESS)
        {
            DWORD dwSize = sizeof(m_wszStoragePath);
            DWORD dwType = REG_SZ;
            if(RegQueryValueEx(hDeviceDataKey,REG_ENTRY_STORAGEPATH,NULL,&dwType,(BYTE*)m_wszStoragePath,&dwSize) == ERROR_SUCCESS)
            {
                WIAS_TRACE((g_hInst,"WIA storage path = %ws",m_wszStoragePath));
                hr = S_OK;
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to read (%ws) entry under %ws section of device registry",REG_ENTRY_STORAGEPATH,REG_ENTRY_DEVICEDATA));
            }

            hr = S_OK;

            //
            // close open DeviceData registry key
            //

            RegCloseKey(hDeviceDataKey);
            hDeviceDataKey = NULL;
        }

        hr = m_CapabilityManager.Initialize(g_hInst);
        if(FAILED(hr))
        {
            WIAS_ERROR((g_hInst, "Failed to initialize the WIA driver capability manager object, hr = 0x%lx",hr));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::GetCapabilities(PSTI_USD_CAPS pDevCaps)
{
    HRESULT hr = E_INVALIDARG;
    if(pDevCaps)
    {
        memset(pDevCaps, 0, sizeof(STI_USD_CAPS));
        pDevCaps->dwVersion     = STI_VERSION_3;
        pDevCaps->dwGenericCaps = STI_GENCAP_WIA                    |
                                  STI_USD_GENCAP_NATIVE_PUSHSUPPORT |
                                  STI_GENCAP_NOTIFICATIONS          |
                                  STI_GENCAP_POLLING_NEEDED;

        WIAS_TRACE((g_hInst,"========================================================"));
        WIAS_TRACE((g_hInst,"STI Capabilities information reported to the WIA Service"));
        WIAS_TRACE((g_hInst,"Version:     0x%lx",pDevCaps->dwVersion));
        WIAS_TRACE((g_hInst,"GenericCaps: 0x%lx", pDevCaps->dwGenericCaps));
        WIAS_TRACE((g_hInst,"========================================================"));

        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::GetStatus( PSTI_DEVICE_STATUS pDevStatus)
{
    HRESULT hr = E_INVALIDARG;
    if(pDevStatus)
    {
        //
        // assume successful status checks
        //

        hr = S_OK;

        if(pDevStatus->StatusMask & STI_DEVSTATUS_ONLINE_STATE)
        {
            //
            // check if the device is ON-LINE
            //

            WIAS_TRACE((g_hInst,"Checking device online status..."));
            pDevStatus->dwOnlineState = 0L;

            if(SUCCEEDED(hr))
            {
                pDevStatus->dwOnlineState |= STI_ONLINESTATE_OPERATIONAL;
                WIAS_TRACE((g_hInst,"The device is online"));
            }
            else
            {
                WIAS_TRACE((g_hInst,"The device is offline"));
            }
        }

        if(pDevStatus->StatusMask & STI_DEVSTATUS_EVENTS_STATE)
        {
            //
            // check for polled events
            //

            pDevStatus->dwEventHandlingState &= ~STI_EVENTHANDLING_PENDING;

            hr = S_FALSE; // no are events detected

            if(hr == S_OK)
            {
                pDevStatus->dwEventHandlingState |= STI_EVENTHANDLING_PENDING;
                WIAS_TRACE((g_hInst,"The device reported a polled event"));
            }
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::DeviceReset()
{
    return S_OK;
}
HRESULT CWIADriver::Diagnostic(LPDIAG pBuffer)
{
    HRESULT hr = E_INVALIDARG;
    if(pBuffer)
    {
        memset(pBuffer,0,sizeof(DIAG));
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::Escape(STI_RAW_CONTROL_CODE EscapeFunction,
                           LPVOID               lpInData,
                           DWORD                cbInDataSize,
                           LPVOID               pOutData,
                           DWORD                dwOutDataSize,
                           LPDWORD              pdwActualData)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::GetLastError(LPDWORD pdwLastDeviceError)
{
    HRESULT hr = E_INVALIDARG;
    if(pdwLastDeviceError)
    {
        *pdwLastDeviceError = 0;
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::LockDevice()
{
    return S_OK;
}
HRESULT CWIADriver::UnLockDevice()
{
    return S_OK;
}
HRESULT CWIADriver::RawReadData(LPVOID       lpBuffer,
                                LPDWORD      lpdwNumberOfBytes,
                                LPOVERLAPPED lpOverlapped)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::RawWriteData(LPVOID       lpBuffer,
                                 DWORD        dwNumberOfBytes,
                                 LPOVERLAPPED lpOverlapped)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::RawReadCommand(LPVOID       lpBuffer,
                                   LPDWORD      lpdwNumberOfBytes,
                                   LPOVERLAPPED lpOverlapped)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::RawWriteCommand(LPVOID       lpBuffer,
                                    DWORD        dwNumberOfBytes,
                                    LPOVERLAPPED lpOverlapped)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}

HRESULT CWIADriver::SetNotificationHandle(HANDLE hEvent)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::GetNotificationData(LPSTINOTIFY lpNotify)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::GetLastErrorInfo(STI_ERROR_INFO *pLastErrorInfo)
{
    HRESULT hr = E_INVALIDARG;
    if(pLastErrorInfo)
    {
        memset(pLastErrorInfo,0,sizeof(STI_ERROR_INFO));
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

/////////////////////////////////////////////////////////////////////////
// IWiaMiniDrv Interface Section (for all WIA drivers)                 //
/////////////////////////////////////////////////////////////////////////

HRESULT CWIADriver::drvInitializeWia(BYTE        *pWiasContext,
                                     LONG        lFlags,
                                     BSTR        bstrDeviceID,
                                     BSTR        bstrRootFullItemName,
                                     IUnknown    *pStiDevice,
                                     IUnknown    *pIUnknownOuter,
                                     IWiaDrvItem **ppIDrvItemRoot,
                                     IUnknown    **ppIUnknownInner,
                                     LONG        *plDevErrVal)
{
    HRESULT hr = S_OK;
    if((pWiasContext)&&(plDevErrVal))
    {
        *plDevErrVal = 0;
        *ppIDrvItemRoot = NULL;

        if(!m_bstrDeviceID)
        {
            m_bstrDeviceID = SysAllocString(bstrDeviceID);
            if(!m_bstrDeviceID)
            {
                hr = E_OUTOFMEMORY;
                WIAS_ERROR((g_hInst, "Failed to allocate BSTR DeviceID string, hr = 0x%lx",hr));
            }
        }

        if(!m_pIStiDevice)
        {
            m_pIStiDevice = reinterpret_cast<IStiDevice*>(pStiDevice);
        }

        if(!m_bstrRootFullItemName)
        {
            m_bstrRootFullItemName = SysAllocString(bstrRootFullItemName);
            if(!m_bstrRootFullItemName)
            {
                hr = E_OUTOFMEMORY;
                WIAS_ERROR((g_hInst, "Failed to allocate BSTR Root full item name string, hr = 0x%lx",hr));
            }
        }

        if(SUCCEEDED(hr))
        {
            if(!m_pIDrvItemRoot)
            {
                hr = BuildDriverItemTree();
            }
            else
            {

                //
                // A WIA item tree already exists.  The root item of this item tree
                // should be returned to the WIA service.
                //

                hr = S_OK;
            }
        }

        //
        // Only increment the client connection count, when the driver
        // has successfully created all the necessary WIA items for
        // a client to use.
        //

        if(SUCCEEDED(hr))
        {
            *ppIDrvItemRoot = m_pIDrvItemRoot;
            InterlockedIncrement(&m_lClientsConnected);
            WIAS_TRACE((g_hInst,"%d client(s) are currently connected to this driver.",m_lClientsConnected));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

UINT CWIADriver::GetBitmapResourceIDFromCategory(const GUID &guidItemCategory)
{
    UINT uiBitmapResourceID = 0;

    if (guidItemCategory == WIA_CATEGORY_FLATBED)
    {
        uiBitmapResourceID = IDB_FLATBED;
    }
    else if (guidItemCategory == WIA_CATEGORY_FEEDER)
    {
        uiBitmapResourceID = IDB_FEEDER;
    }
    else if (guidItemCategory == WIA_CATEGORY_FILM)
    {
        uiBitmapResourceID = IDB_FILM;
    }
    else
    {
        uiBitmapResourceID = IDB_FLATBED;
    }

    return uiBitmapResourceID;
}

HRESULT CWIADriver::DownloadToStream(LONG                           lFlags,
                                     BYTE                           *pWiasContext,
                                     const GUID                     &guidItemCategory,
                                     IWiaMiniDrvTransferCallback    *pTransferCallback,
                                     LONG                           *plDevErrVal)
{
    HRESULT hr                  = S_OK;
    BSTR    bstrItemName        = NULL;
    BSTR    bstrFullItemName    = NULL;
    UINT    uiBitmapResourceID  = GetBitmapResourceIDFromCategory(guidItemCategory);

    //  Get the item name
    hr = wiasReadPropStr(pWiasContext, WIA_IPA_ITEM_NAME, &bstrItemName, NULL, TRUE);
    if (SUCCEEDED(hr))
    {
        //  Get the full item name
        hr = wiasReadPropStr(pWiasContext, WIA_IPA_FULL_ITEM_NAME, &bstrFullItemName, NULL, TRUE);
        if (SUCCEEDED(hr))
        {
            //  Get the destination stream
            IStream *pDestination = NULL;
            hr = pTransferCallback->GetNextStream(0, bstrItemName, bstrFullItemName, &pDestination);
            if (hr == S_OK)
            {
                WiaTransferParams *pParams = (WiaTransferParams*)CoTaskMemAlloc(sizeof(WiaTransferParams));
                if (pParams)
                {
                    memset(pParams, 0, sizeof(WiaTransferParams));
                    BYTE    *pBuffer        = NULL;
                    ULONG   ulBufferSize    = 0;
                    hr = AllocateTransferBuffer(pWiasContext, &pBuffer, &ulBufferSize);
                    if (SUCCEEDED(hr))
                    {
                        if((S_OK == hr) && (guidItemCategory != WIA_CATEGORY_FINISHED_FILE))
                        {
                            LONG    lErrorHandling = ERROR_HANDLING_NONE;

                            hr = wiasReadPropLong(pWiasContext, MY_WIA_ERROR_HANDLING_PROP, &lErrorHandling, NULL, TRUE);

                            BOOL    bSendWarmingUpMsg       = lErrorHandling & ERROR_HANDLING_WARMING_UP;
                            BOOL    bSendCoverOpenMsg       = lErrorHandling & ERROR_HANDLING_COVER_OPEN;
                            BOOL    bSendPrivateErrorMsg    = lErrorHandling & ERROR_HANDLING_PRIVATE_ERROR;
                            BOOL    bSendUnhandledStatusMsg = lErrorHandling & ERROR_HANDLING_UNHANDLED_STATUS;
                            BOOL    bSendUnhandledErrorMsg  = lErrorHandling & ERROR_HANDLING_UNHANDLED_ERROR;

                            //  We need to initialize our device object for each item we transfer.
                            //  Each item may have it's own selection area, data type and so on.
                            hr = m_WiaDevice.InitializeForDownload(pWiasContext,
                                                                   g_hInst,
                                                                   uiBitmapResourceID);

                            if ((S_OK == hr) && bSendWarmingUpMsg)
                            {
                                //
                                // Send non-modal warming up message. To be catched by default UI
                                // unless application handles it (WiaPreview does not handle this
                                // message).
                                //
                                // Sending "update messages" makes it possible for a user to cancel transfer
                                // and also for an error handler to provide progress dialog.
                                //                            
                                for (int i = 0; i < 10 ; i++)
                                {
                                    pParams->lMessage                       = WIA_TRANSFER_MSG_DEVICE_STATUS;
                                    pParams->hrErrorStatus                  = WIA_STATUS_WARMING_UP;
                                    pParams->lPercentComplete               = i * 10;
                                    pParams->ulBytesWrittenToCurrentStream  = 0;

                                    hr = pTransferCallback->SendMessage(0, pParams);

                                    if (S_OK != hr)
                                    {
                                        break;
                                    }

                                    Sleep(500);
                                }
                            }

                            if (S_OK == hr)
                            {
                                BOOL    bProblemFixed = FALSE;

                                //  Data transfer loop
                                //  Read from device
                                ULONG   ulBytesRead         = 0;
                                LONG    lPercentComplete    = 0;

                                if (bSendUnhandledStatusMsg)
                                {
                                    //
                                    // Send "special" unhandled status message
                                    //
                                    pParams->lMessage                       = WIA_TRANSFER_MSG_DEVICE_STATUS;
                                    pParams->hrErrorStatus                  = UNHANDLED_PRIVATE_STATUS_MESSAGE_1;
                                    pParams->lPercentComplete               = 0;
                                    pParams->ulBytesWrittenToCurrentStream  = 0;
    
                                    hr = pTransferCallback->SendMessage(0, pParams);
                                }

                                if ((S_OK == hr) && bSendUnhandledErrorMsg)
                                {

                                    //
                                    // Since none handles this device error it will cause our transfer to be
                                    // be aborted.
                                    //
                                    pParams->lMessage                       = WIA_TRANSFER_MSG_DEVICE_STATUS;
                                    pParams->hrErrorStatus                  = UNHANDLED_PRIVATE_STATUS_ERROR_1;
                                    pParams->lPercentComplete               = 0;
                                    pParams->ulBytesWrittenToCurrentStream  = 0;
    
                                    hr = pTransferCallback->SendMessage(0, pParams);
                                }

                                if ((S_OK == hr) && bSendCoverOpenMsg)
                                {
                                    pParams->lMessage                       = WIA_TRANSFER_MSG_DEVICE_STATUS;
                                    pParams->hrErrorStatus                  = WIA_ERROR_COVER_OPEN;
                                    pParams->lPercentComplete               = 0;
                                    pParams->ulBytesWrittenToCurrentStream  = 0;
    
                                    hr = pTransferCallback->SendMessage(0, pParams);
                                }

                                while((S_OK == hr) && ((hr = m_WiaDevice.GetNextBand(pBuffer, ulBufferSize, &ulBytesRead, &lPercentComplete)) == S_OK))
                                {
                                    //      Check whether the transfer has been cancelled
                                    if (pTransferCallback->ContinueWithTransfer() != S_OK)
                                    {
                                        WIAS_TRACE((g_hInst, "Download was cancelled"));
                                        hr = S_FALSE;
                                        break;
                                    }
                                    //      Write to stream
                                    ULONG   ulBytesWritten = 0;
                                    hr = pDestination->Write(pBuffer, ulBytesRead, &ulBytesWritten);
                                    
                                    if (S_OK == hr)
                                    {
                                        //      Make progress callback
                                        pParams->lMessage                       = WIA_TRANSFER_MSG_STATUS;
                                        pParams->lPercentComplete               = lPercentComplete;
                                        pParams->ulBytesWrittenToCurrentStream  += ulBytesWritten;

                                        hr = pTransferCallback->SendMessage(0, pParams);
                                        if (FAILED(hr))
                                        {
                                            WIAS_ERROR((g_hInst, "Failed to send progress notification during download, hr = 0x%lx",hr));
                                            break;
                                        }
                                        else if (S_FALSE == hr)
                                        {
                                            //
                                            // Transfer cancelled
                                            //
                                            break;
                                        }

                                        if ((lPercentComplete > 50) && !bProblemFixed)
                                        {

                                            if (bSendPrivateErrorMsg)
                                            {
                                                //
                                                // Send "special" driver status message that only our error handling extension knows about
                                                //
                                                pParams->lMessage                       = WIA_TRANSFER_MSG_DEVICE_STATUS;
                                                pParams->hrErrorStatus                  = HANDLED_PRIVATE_STATUS_ERROR_1;
                                                
                                                hr = pTransferCallback->SendMessage(0, pParams);
                                            }

                                            if (S_OK == hr)
                                            {
                                                bProblemFixed = TRUE;
                                            }
                                        }
                                    }
                                }

                                if (WIA_STATUS_END_OF_MEDIA == hr)
                                {
                                    hr = S_OK;
                                }

                                m_WiaDevice.UninitializeForDownload();
                            }
                            else
                            {
                                WIAS_ERROR((g_hInst, "Failed to initialize device for download, hr = 0x%lx",hr));
                            }
                        }
                        else
                        {
                            WIA_DRIVER_ITEM_CONTEXT *pWiaDriverItemContext = NULL;
                            hr = wiasGetDriverItemPrivateContext(pWiasContext,(BYTE**)&pWiaDriverItemContext);
                            if(SUCCEEDED(hr) && (pWiaDriverItemContext))
                            {
                                // Transfer data item contents (storage item data)
                                //  Data transfer loop
                                //      Read from device
                                IStream *pStorageDataStream = NULL;
                                hr = SHCreateStreamOnFile(pWiaDriverItemContext->bstrStorageDataPath,STGM_READ,&pStorageDataStream);
                                if(SUCCEEDED(hr))
                                {
                                    ULONG   ulBytesRead      = 0;
                                    LONG    lPercentComplete = -1;
                                    while((SUCCEEDED(pStorageDataStream->Read(pBuffer, ulBufferSize, &ulBytesRead)) && ulBytesRead))
                                    {
                                        //      Check whether the transfer has been cancelled
                                        if (pTransferCallback->ContinueWithTransfer() != S_OK)
                                        {
                                            WIAS_TRACE((g_hInst, "Download was cancelled"));
                                            hr = S_FALSE;
                                            break;
                                        }
                                        //      Write to stream
                                        ULONG   ulBytesWritten = 0;
                                        hr = pDestination->Write(pBuffer, ulBytesRead, &ulBytesWritten);
                                        if (SUCCEEDED(hr))
                                        {
                                            //      Make progress callback
                                            pParams->lMessage                       = WIA_TRANSFER_MSG_STATUS;
                                            pParams->lPercentComplete               = lPercentComplete;
                                            pParams->ulBytesWrittenToCurrentStream  += ulBytesWritten;

                                            hr = pTransferCallback->SendMessage(0, pParams);
                                            if (FAILED(hr))
                                            {
                                                WIAS_ERROR((g_hInst, "Failed to send progress notification during download, hr = 0x%lx",hr));
                                                break;
                                            }
                                        }
                                    }
                                    pStorageDataStream->Release();
                                    pStorageDataStream = NULL;
                                }
                                else
                                {
                                    WIAS_ERROR((g_hInst, "Failed to create a source stream on storage item data content file (%ws), hr = 0x%lx",pWiaDriverItemContext->bstrStorageDataPath,hr));
                                }
                            }
                            else
                            {
                                WIAS_ERROR((g_hInst, "Failed to get WIA driver item private context, hr = 0x%lx",hr));
                            }
                        }
                        FreeTransferBuffer(pBuffer);
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to allocate memory for transfer buffer, hr = 0x%lx",hr));
                    }
                    CoTaskMemFree(pParams);
                    pParams = NULL;
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                    WIAS_ERROR((g_hInst, "Failed to allocate memory for WiaTransferParams structure, hr = 0x%lx",hr));
                }
                pDestination->Release();
                pDestination = NULL;
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to get the destination stream for download, hr = 0x%lx",hr));
            }

            SysFreeString(bstrFullItemName);
            bstrFullItemName = NULL;
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to read the WIA_IPA_FULL_ITEM_NAME property, hr = 0x%lx",hr));
        }
        SysFreeString(bstrItemName);
        bstrItemName = NULL;
    }
    else
    {
        WIAS_ERROR((g_hInst, "Failed to read the WIA_IPA_ITEM_NAME property, hr = 0x%lx",hr));
    }

    return hr;
}

HRESULT CWIADriver::UploadFromStream(LONG                           lFlags,
                                     BYTE                           *pWiasContext,
                                     const GUID                     &guidItemCategory,
                                     IWiaMiniDrvTransferCallback    *pTransferCallback,
                                     LONG                           *plDevErrVal)
{
    HRESULT hr           = S_OK;

    IStream *pSourceStream = NULL;
    hr = pTransferCallback->GetNextStream(lFlags,NULL,NULL,&pSourceStream);
    if(SUCCEEDED(hr))
    {
        BSTR bstrItemName = NULL;
        hr = wiasReadPropStr(pWiasContext,WIA_IPA_ITEM_NAME,&bstrItemName,NULL,TRUE);
        if(SUCCEEDED(hr))
        {
            STATSTG statstg = {0};

            hr = pSourceStream->Stat(&statstg, STATFLAG_NONAME);
            if(SUCCEEDED(hr))
            {
                WiaTransferParams *pParams = (WiaTransferParams*)CoTaskMemAlloc(sizeof(WiaTransferParams));
                if (pParams)
                {
                    memset(pParams, 0, sizeof(WiaTransferParams));

                    hr = m_WiaDevice.Upload(bstrItemName, statstg.cbSize.LowPart, pSourceStream,pTransferCallback, pParams,m_wszStoragePath);
                    if(SUCCEEDED(hr))
                    {
                        // Succeeded with upload.  We expect the App to do a synchronize to get the new items,
                        // so there's nothing further we need to do.

                        //
                        // TBD: Ideal case would be to create a WIA driver item, and link it to the existing
                        //      application item.  This will also be the place that a item created/added event
                        //      would be sent to the other clients, allowing them to reenumerate and pick up the
                        //      freshly uploaded item.
                        //
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to upload data to the device, hr = 0x%lx",hr));
                    }

                    CoTaskMemFree(pParams);
                    pParams = NULL;
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                    WIAS_ERROR((g_hInst, "Failed to allocate memory for WiaTransferParams structure, hr = 0x%lx",hr));
                }
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to call IStream::Stat on application provided stream, hr = 0x%lx",hr));
            }
            SysFreeString(bstrItemName);
            bstrItemName = NULL;
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to read WIA_IPA_ITEM_NAME property, hr = 0x%lx",hr));
        }

        pSourceStream->Release();
        pSourceStream = NULL;
    }
    return hr;
}

HRESULT CWIADriver::drvAcquireItemData(BYTE                      *pWiasContext,
                                       LONG                      lFlags,
                                       PMINIDRV_TRANSFER_CONTEXT pmdtc,
                                       LONG                      *plDevErrVal)
{
    HRESULT hr                  = E_INVALIDARG;
    GUID    guidItemCategory    = GUID_NULL;
    if((pWiasContext)&&(pmdtc)&&(plDevErrVal))
    {
        //
        // Read the WIA item category, to decide which data transfer handler should
        // be used.
        //
        hr = wiasReadPropGuid(pWiasContext,WIA_IPA_ITEM_CATEGORY,&guidItemCategory,NULL,TRUE);
        if (SUCCEEDED(hr))
        {
            //
            //  Check what kind of data transfer is requested.  This driver
            //  supports 2 transfer modes:
            //  1.  Stream-based download
            //  2.  Stream-based upload
            //

            if (lFlags & WIA_MINIDRV_TRANSFER_DOWNLOAD)
            {
                // This is stream-based download
                IWiaMiniDrvTransferCallback *pTransferCallback = NULL;
                hr = GetTransferCallback(pmdtc, &pTransferCallback);
                if (SUCCEEDED(hr))
                {
                    hr = DownloadToStream(lFlags, pWiasContext, guidItemCategory, pTransferCallback, plDevErrVal);
                    pTransferCallback->Release();
                    pTransferCallback = NULL;
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Could not get our IWiaMiniDrvTransferCallback for download"));
                }
            }
            else if (lFlags & WIA_MINIDRV_TRANSFER_UPLOAD)
            {
                //
                // We only want to do "Upload" if category of the item is WIA_CATEGORY_FINISHED_FILE and
                // it is not the root storage item.
                //
                LONG    lItemType = 0;

                hr = wiasGetItemType(pWiasContext,&lItemType);
                if (SUCCEEDED(hr))
                {
                    if ((guidItemCategory == WIA_CATEGORY_FINISHED_FILE) && !(lItemType & WiaItemTypeStorage))
                    {
                        // This is stream-based upload
                        IWiaMiniDrvTransferCallback *pTransferCallback = NULL;
                        hr = GetTransferCallback(pmdtc, &pTransferCallback);
                        if (SUCCEEDED(hr))
                        {
                            hr = UploadFromStream(lFlags, pWiasContext, guidItemCategory, pTransferCallback, plDevErrVal);
                            pTransferCallback->Release();
                            pTransferCallback = NULL;
                        }
                        else
                        {
                            WIAS_ERROR((g_hInst, "Could not get our IWiaMiniDrvTransferCallback for upload"));
                        }
                    }
                    else
                    {
                        hr = E_INVALIDARG;
                        WIAS_ERROR((g_hInst, "Cannot do Upload to selected item, hr = 0x%lx",hr));
                    }
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Failed to get the WIA item type, hr = 0x%lx",hr));
                }
            }
            else
            {
                // This should not happen!
                hr = E_INVALIDARG;
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to read the WIA_IPA_ITEM_CATEGORY property, hr = 0x%lx",hr));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::drvInitItemProperties(BYTE *pWiasContext,
                                          LONG lFlags,
                                          LONG *plDevErrVal)
{
    HRESULT hr          = E_INVALIDARG;
    LONG    lItemFlags  = 0;
    if((pWiasContext)&&(plDevErrVal))
    {
        //
        // Initialize individual storage item properties using the CWIAStorage object
        //
        hr = wiasReadPropLong(pWiasContext,WIA_IPA_ITEM_FLAGS,&lItemFlags,NULL,TRUE);
        if(SUCCEEDED(hr))
        {
            if((lItemFlags & WiaItemTypeRoot))
            {
                //
                // Add any root item properties needed.  This is where the
                // backward compatibility properties should be written.
                // (example: WIA_DPS_PREVIEW, etc.)
                //

                hr = InitializeRootItemProperties(pWiasContext);
                if(SUCCEEDED(hr))
                {
                    //
                    // Add the legacy supported root item properties, using
                    // the same property initialization function.
                    //
                    hr = InitializeWIAItemProperties(pWiasContext,g_hInst,IDB_FLATBED,TRUE);
                    if(SUCCEEDED(hr))
                    {
                        hr = InitializeWIAItemProperties(pWiasContext,g_hInst,IDB_FEEDER,TRUE);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to initialize WIA root item properties for the feeder item, hr = 0x%lx",hr));
                        }
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to initialize WIA root item properties for the flatbed item, hr = 0x%lx",hr));
                    }
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Failed to initialize generic WIA root item properties, hr = 0x%lx",hr));
                }
            }
            else
            {
                //
                // Add any non-root item properties needed.
                //
                GUID guidItemCategory = GUID_NULL;

                //
                // Use the WIA category setting to determine what type of property
                // set should be created for this WIA item.
                //
                if((lItemFlags & WiaItemTypeGenerated) == FALSE)
                {
                    //
                    // Item is not a generated item, assume that this was created by this WIA driver
                    // and the WIA_ITEM_CATEGORY setting can be read from the WIA_DRIVER_ITEM_CONTEXT
                    // structure stored with the WIA driver item.
                    //

                    WIA_DRIVER_ITEM_CONTEXT *pWiaDriverItemContext = NULL;
                    hr = wiasGetDriverItemPrivateContext(pWiasContext,(BYTE**)&pWiaDriverItemContext);
                    if(SUCCEEDED(hr) && (pWiaDriverItemContext))
                    {
                        guidItemCategory = pWiaDriverItemContext->guidItemCategory;
                    }
                    else
                    {
                        //
                        // This WIA item has no item context and will receive default item
                        // property initialization.  This allows applications to create child items
                        // for storing private data.
                        // NOTE: Data transfers on these types of items will probably not succeed since
                        //       the driver does not have a category to help classify the behavior of the
                        //       item.
                        //
                        hr = S_OK;
                    }
                }
                else
                {
                    //
                    // Read the parents WIA_ITEM_CATEGORY property setting to determine this new
                    // child item's category setting.
                    //

                    BYTE *pWiasParentContext = NULL;
                    hr = wiasGetAppItemParent(pWiasContext,&pWiasParentContext);
                    if(SUCCEEDED(hr))
                    {
                        hr = wiasReadPropGuid(pWiasParentContext,WIA_IPA_ITEM_CATEGORY,&guidItemCategory,NULL,TRUE);
                        if(FAILED(hr))
                        {
                            WIAS_TRACE((g_hInst,"The item does not have a category property setting. Assuming that it is unknown."));
                            //
                            // This WIA item has no item category property setting and will receive default item
                            // property initialization.  This allows applications to create child items
                            // for storing private data.
                            // NOTE: Data transfers on these types of items will probably not succeed since
                            //       the driver does not have a category to help classify the behavior of the
                            //       item.
                            //
                            hr = S_OK;
                        }
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to obtain the WIA application item's parent, hr = 0x%lx",hr));
                    }
                }

                if(SUCCEEDED(hr))
                {
                    //
                    // Initialize the WIA item property set according to the category specified
                    //

                    if(guidItemCategory == WIA_CATEGORY_FLATBED)
                    {
                        hr = InitializeWIAItemProperties(pWiasContext,g_hInst,IDB_FLATBED,FALSE);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to initialize the flatbed item's property set. hr = 0x%lx",hr));
                        }
                    }
                    else if(guidItemCategory == WIA_CATEGORY_FEEDER)
                    {
                        hr = InitializeWIAItemProperties(pWiasContext,g_hInst,IDB_FEEDER,FALSE);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to initialize the feeder item's property set. hr = 0x%lx",hr));
                        }
                    }
                    else if(guidItemCategory == WIA_CATEGORY_FILM)
                    {
                        hr = InitializeWIAItemProperties(pWiasContext,g_hInst,IDB_FILM,FALSE);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to initialize the film item's property set. hr = 0x%lx",hr));
                        }
                    }
                    else if(guidItemCategory == WIA_CATEGORY_FINISHED_FILE)
                    {
                        hr = InitializeWIAStorageItemProperties(pWiasContext,FALSE);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to initialize the storage item's property set. hr = 0x%lx",hr));
                        }
                    }
                    else
                    {
                        hr = S_OK;
                    }
                }
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to read WIA_IPA_ITEM_FLAGS property, hr = 0x%lx",hr));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::drvValidateItemProperties(BYTE           *pWiasContext,
                                              LONG           lFlags,
                                              ULONG          nPropSpec,
                                              const PROPSPEC *pPropSpec,
                                              LONG           *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(pPropSpec)&&(plDevErrVal)&&(nPropSpec))
    {
        LONG lItemType = 0;
        hr = wiasGetItemType(pWiasContext,&lItemType);
        if(SUCCEEDED(hr))
        {
            if((lItemType & WiaItemTypeRoot) == TRUE)
            {
                //
                // Validate root item property settings, if needed.
                //

                hr = S_OK;
            }
            else
            {
                //
                // Validate child item property settings, if needed.
                //
                LONG                    lScanningSurfaceWidth   = 0;
                LONG                    lScanningSurfaceHeight  = 0;
                GUID                    guidItemCategory        = GUID_NULL;
                WIA_PROPERTY_CONTEXT    PropertyContext         = {0};

                //
                // Use the WIA item category to help classify and gather WIA item information
                // needed to validate the property set.
                //
                hr = wiasReadPropGuid(pWiasContext,WIA_IPA_ITEM_CATEGORY,&guidItemCategory,NULL,TRUE);
                if(SUCCEEDED(hr))
                {
                    BOOL bValidCategory = FALSE;
                    //
                    // Validate the selection area against the entire scanning surface of the device.
                    // The scanning surface may be different sizes depending on the type of WIA item.
                    // (ie. Flatbed glass platen sizes may be different to film scanning surfaces, and
                    // feeder sizes.)
                    //
                    if((guidItemCategory == WIA_CATEGORY_FLATBED)||(guidItemCategory == WIA_CATEGORY_FILM))
                    {
                        bValidCategory = TRUE;

                        //
                        // Flatbed items and Film items use the same WIA properties to describe their scanning
                        // surface.
                        //
                        hr = wiasReadPropLong(pWiasContext,WIA_DPS_HORIZONTAL_BED_SIZE,&lScanningSurfaceWidth,NULL,TRUE);
                        if(SUCCEEDED(hr))
                        {
                            hr = wiasReadPropLong(pWiasContext,WIA_DPS_VERTICAL_BED_SIZE,&lScanningSurfaceHeight,NULL,TRUE);
                            if(FAILED(hr))
                            {
                                WIAS_ERROR((g_hInst, "Failed to read WIA_DPS_VERTICAL_BED_SIZE property, hr = 0x%lx",hr));
                            }
                        }
                        else
                        {
                            WIAS_ERROR((g_hInst, "Failed to read WIA_DPS_HORIZONTAL_BED_SIZE property, hr = 0x%lx",hr));
                        }
                    }
                    else if(guidItemCategory == WIA_CATEGORY_FEEDER)
                    {
                        bValidCategory = TRUE;

                        //
                        // Feeder items use a different set of properties to describe the scanning surface.
                        //
                        hr = wiasReadPropLong(pWiasContext,WIA_DPS_HORIZONTAL_SHEET_FEED_SIZE,&lScanningSurfaceWidth,NULL,TRUE);
                        if(SUCCEEDED(hr))
                        {
                            hr = wiasReadPropLong(pWiasContext,WIA_DPS_VERTICAL_SHEET_FEED_SIZE,&lScanningSurfaceHeight,NULL,TRUE);
                            if(FAILED(hr))
                            {
                                WIAS_ERROR((g_hInst, "Failed to read WIA_DPS_VERTICAL_SHEET_FEED_SIZE property, hr = 0x%lx",hr));
                            }
                        }
                        else
                        {
                            WIAS_ERROR((g_hInst, "Failed to read WIA_DPS_HORIZONTAL_SHEET_FEED_SIZE property, hr = 0x%lx",hr));
                        }
                    }
                    else if(guidItemCategory == WIA_CATEGORY_FINISHED_FILE)
                    {
                        bValidCategory = TRUE;
                        hr = S_OK;
                    }
                    else
                    {
                        hr = S_OK;
                        WIAS_TRACE((g_hInst,"Unknown WIA category read from WIA item, hr = 0x%lx",hr));
                    }

                    if((SUCCEEDED(hr))&&(bValidCategory))
                    {
                        hr = wiasCreatePropContext(nPropSpec,(PROPSPEC*)pPropSpec,0,NULL,&PropertyContext);
                        if(SUCCEEDED(hr))
                        {
                            //
                            // Only perform extent validation for items that contain
                            // extent properties.
                            //

                            if(guidItemCategory != WIA_CATEGORY_FINISHED_FILE)
                            {
                                if(SUCCEEDED(hr))
                                {
                                    hr = wiasUpdateValidFormat(pWiasContext,&PropertyContext,(IWiaMiniDrv*)this);
                                    if(FAILED(hr))
                                    {
                                        WIAS_ERROR((g_hInst, "Failed to validate supported formats, hr = %lx",hr));
                                    }
                                }


                                if(SUCCEEDED(hr))
                                {
                                    hr = wiasUpdateScanRect(pWiasContext,&PropertyContext,lScanningSurfaceWidth, lScanningSurfaceHeight);
                                    if(FAILED(hr))
                                    {
                                        WIAS_ERROR((g_hInst, "Failed to validate extent settings. (current selection area), hr = %lx",hr));
                                    }
                                }
                            }

                            HRESULT FreePropContextHR = wiasFreePropContext(&PropertyContext);
                            if(FAILED(FreePropContextHR))
                            {
                                WIAS_ERROR((g_hInst, "wiasFreePropContext failed, hr = 0x%lx",FreePropContextHR));
                            }
                        }
                        else
                        {
                            WIAS_ERROR((g_hInst, "Failed to create WIA property context for validation, hr = 0x%lx",hr));
                        }
                    }
                }
            }

            //
            // Only call wiasValidateItemProperties if the validation above
            // succeeded.
            //
            if(SUCCEEDED(hr))
            {
                hr = wiasValidateItemProperties(pWiasContext,nPropSpec,pPropSpec);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to validate remaining properties using wiasValidateItemProperties, hr = 0x%lx",hr));
                }
            }
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::drvWriteItemProperties(BYTE                      *pWiasContext,
                                           LONG                      lFlags,
                                           PMINIDRV_TRANSFER_CONTEXT pmdtc,
                                           LONG                      *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(pmdtc)&&(plDevErrVal))
    {
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::drvReadItemProperties(BYTE           *pWiasContext,
                                          LONG           lFlags,
                                          ULONG          nPropSpec,
                                          const PROPSPEC *pPropSpec,
                                          LONG           *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(pPropSpec)&&(plDevErrVal))
    {
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::drvLockWiaDevice(BYTE *pWiasContext,
                                     LONG lFlags,
                                     LONG *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(plDevErrVal))
    {
        if(m_pIStiDevice)
        {
            hr = m_pIStiDevice->LockDevice(DEFAULT_LOCK_TIMEOUT);
        }
        else
        {
            hr = S_OK;
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::drvUnLockWiaDevice(BYTE *pWiasContext,
                                       LONG lFlags,
                                       LONG *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(plDevErrVal))
    {
        if(m_pIStiDevice)
        {
            hr = m_pIStiDevice->UnLockDevice();
        }
        else
        {
            hr = S_OK;
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::drvAnalyzeItem(BYTE *pWiasContext,
                                   LONG lFlags,
                                   LONG *plDevErrVal)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::drvGetDeviceErrorStr(LONG     lFlags,
                                         LONG     lDevErrVal,
                                         LPOLESTR *ppszDevErrStr,
                                         LONG     *plDevErr)
{
    WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    return E_NOTIMPL;
}
HRESULT CWIADriver::DestroyDriverItemTree()
{
    HRESULT hr = S_OK;

    if(m_pIDrvItemRoot)
    {
        WIAS_TRACE((g_hInst,"Unlinking WIA item tree"));
        hr = m_pIDrvItemRoot->UnlinkItemTree(WiaItemTypeDisconnected);
        if(FAILED(hr))
        {
            WIAS_ERROR((g_hInst, "Failed to unlink WIA item tree before being released, hr = 0x%lx",hr));
        }

        WIAS_TRACE((g_hInst,"Releasing IDrvItemRoot interface"));
        m_pIDrvItemRoot->Release();
        m_pIDrvItemRoot = NULL;
    }

    return hr;
}

HRESULT CWIADriver::BuildDriverItemTree()
{
    HRESULT hr = S_OK;
    if(!m_pIDrvItemRoot)
    {
        LONG lItemFlags = WiaItemTypeFolder | WiaItemTypeDevice | WiaItemTypeRoot;
        BSTR bstrRootItemName = SysAllocString(WIA_DRIVER_ROOT_NAME);
        if(bstrRootItemName)
        {
            //
            // Create a default WIA root item
            //
            hr = wiasCreateDrvItem(lItemFlags,
                                   bstrRootItemName,
                                   m_bstrRootFullItemName,
                                   (IWiaMiniDrv*)this,
                                   0,
                                   NULL,
                                   &m_pIDrvItemRoot);
            //
            // Create child items that represent the data or programmable data sources.
            //
            if(SUCCEEDED(hr))
            {
                hr = CreateWIAFlatbedItem(WIA_DRIVER_FLATBED_NAME,(IWiaMiniDrv*)this,m_pIDrvItemRoot);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to create WIA flatbed item, hr = 0x%lx",hr));
                }
            }

            if(SUCCEEDED(hr))
            {
                hr = CreateWIAFeederItem(WIA_DRIVER_FEEDER_NAME,(IWiaMiniDrv*)this,m_pIDrvItemRoot);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to create WIA feeder item, hr = 0x%lx",hr));
                }
            }

            if(SUCCEEDED(hr))
            {
                hr = CreateWIAFilmItem(WIA_DRIVER_FILM_NAME,(IWiaMiniDrv*)this,m_pIDrvItemRoot);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to create WIA film item, hr = 0x%lx",hr));
                }
            }

            if(SUCCEEDED(hr))
            {
                hr = CreateWIAStorageItem(WIA_DRIVER_STORAGE_NAME,(IWiaMiniDrv*)this,m_pIDrvItemRoot,m_wszStoragePath);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to create WIA storage item, hr = 0x%lx",hr));
                }
            }

            SysFreeString(bstrRootItemName);
            bstrRootItemName = NULL;
        }
        else
        {
            hr = E_OUTOFMEMORY;
            WIAS_ERROR((g_hInst, "Failed to allocate memory for the root item name, hr = 0x%lx",hr));
        }
    }

    return hr;
}


HRESULT CWIADriver::DoSynchronizeCommand(
    BYTE *pWiasContext)
{
    HRESULT hr = S_OK;

    hr = DestroyDriverItemTree();
    if (SUCCEEDED(hr))
    {
        hr = BuildDriverItemTree();

        //
        //  Queue tree updated event, regardless ofwhether it
        //  succeeded, since we can't guarantee that the tree
        //  was left in the same condition.
        //
        QueueWIAEvent(pWiasContext, WIA_EVENT_TREE_UPDATED);
    }
    else
    {
        WIAS_ERROR((g_hInst, " failed, hr = 0x%lx", hr));
    }

    return hr;
}

HRESULT CWIADriver::drvDeviceCommand(BYTE        *pWiasContext,
                                     LONG        lFlags,
                                     const GUID  *pguidCommand,
                                     IWiaDrvItem **ppWiaDrvItem,
                                     LONG        *plDevErrVal)
{
    HRESULT hr = E_NOTIMPL;

    if (pguidCommand)
    {
        if (*pguidCommand == WIA_CMD_SYNCHRONIZE)
        {
            hr = DoSynchronizeCommand(pWiasContext);
        }
    }
    else
    {
        hr = E_NOTIMPL;
        WIAS_ERROR((g_hInst, "This method is not implemented or supported for this driver"));
    }

    return hr;
}

HRESULT CWIADriver::drvGetCapabilities(BYTE            *pWiasContext,
                                       LONG            ulFlags,
                                       LONG            *pcelt,
                                       WIA_DEV_CAP_DRV **ppCapabilities,
                                       LONG            *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pcelt)&&(ppCapabilities)&&(plDevErrVal))
    {
        hr = S_OK;
        if(m_CapabilityManager.GetNumCapabilities() == 0)
        {
            hr = m_CapabilityManager.AddCapability(WIA_EVENT_DEVICE_CONNECTED,
                                                   IDS_EVENT_DEVICE_CONNECTED_NAME,
                                                   IDS_EVENT_DEVICE_CONNECTED_DESCRIPTION,
                                                   WIA_NOTIFICATION_EVENT,
                                                   WIA_ICON_DEVICE_CONNECTED);
            if(SUCCEEDED(hr))
            {
                hr = m_CapabilityManager.AddCapability(WIA_EVENT_TREE_UPDATED,
                                                       IDS_EVENT_TREE_UPDATED_NAME,
                                                       IDS_EVENT_TREE_UPDATED_DESCRIPTION,
                                                       WIA_NOTIFICATION_EVENT,
                                                       WIA_ICON_TREE_UPDATED);
                if(SUCCEEDED(hr))
                {
                    hr = m_CapabilityManager.AddCapability(WIA_EVENT_DEVICE_DISCONNECTED,
                                                           IDS_EVENT_DEVICE_DISCONNECTED_NAME,
                                                           IDS_EVENT_DEVICE_DISCONNECTED_DESCRIPTION,
                                                           WIA_NOTIFICATION_EVENT,
                                                           WIA_ICON_DEVICE_DISCONNECTED);
                    if(SUCCEEDED(hr))
                    {
                        hr = m_CapabilityManager.AddCapability(WIA_CMD_SYNCHRONIZE,
                                                               IDS_CMD_SYNCHRONIZE_NAME,
                                                               IDS_CMD_SYNCHRONIZE_DESCRIPTION,
                                                               0,
                                                               WIA_ICON_SYNCHRONIZE);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to add WIA_CMD_SYNCHRONIZE to capability manager, hr = 0x%lx",hr));
                        }
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to add WIA_EVENT_DEVICE_DISCONNECTED to capability manager, hr = 0x%lx",hr));
                    }
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Failed to add WIA_EVENT_TREE_UPDATED to capability manager, hr = 0x%lx",hr));
                }
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to add WIA_EVENT_DEVICE_CONNECTED to capability manager, hr = 0x%lx",hr));
            }
        }

        if(SUCCEEDED(hr))
        {
            if(((ulFlags & WIA_DEVICE_COMMANDS) == WIA_DEVICE_COMMANDS)&&(ulFlags & WIA_DEVICE_EVENTS) == WIA_DEVICE_EVENTS)
            {
                *ppCapabilities = m_CapabilityManager.GetCapabilities();
                *pcelt          = m_CapabilityManager.GetNumCapabilities();
                WIAS_TRACE((g_hInst,"Application is asking for Commands and Events, and we have %d total capabilities",*pcelt));
            }
            else if((ulFlags & WIA_DEVICE_COMMANDS) == WIA_DEVICE_COMMANDS)
            {
                *ppCapabilities = m_CapabilityManager.GetCommands();
                *pcelt          = m_CapabilityManager.GetNumCommands();
                WIAS_TRACE((g_hInst,"Application is asking for Commands, and we have %d",*pcelt));
            }
            else if((ulFlags & WIA_DEVICE_EVENTS) == WIA_DEVICE_EVENTS)
            {
                *ppCapabilities = m_CapabilityManager.GetEvents();
                *pcelt          = m_CapabilityManager.GetNumEvents();
                WIAS_TRACE((g_hInst,"Application is asking for Events, and we have %d",*pcelt));
            }

            WIAS_TRACE((g_hInst,0,"========================================================"));
            WIAS_TRACE((g_hInst,0,"WIA driver capability information"));
            WIAS_TRACE((g_hInst,0,"========================================================"));

            WIA_DEV_CAP_DRV *pCapabilities      = m_CapabilityManager.GetCapabilities();
            LONG            lNumCapabilities    = m_CapabilityManager.GetNumCapabilities();

            for(LONG i = 0; i < lNumCapabilities; i++)
            {
                if(pCapabilities[i].ulFlags & WIA_NOTIFICATION_EVENT)
                {
                    WIAS_TRACE((g_hInst,"Event Name:        %ws",pCapabilities[i].wszName));
                    WIAS_TRACE((g_hInst,"Event Description: %ws",pCapabilities[i].wszDescription));
                }
                else
                {
                    WIAS_TRACE((g_hInst,"Command Name:        %ws",pCapabilities[i].wszName));
                    WIAS_TRACE((g_hInst,"Command Description: %ws",pCapabilities[i].wszDescription));
                }
            }
            WIAS_TRACE((g_hInst,"========================================================"));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::drvDeleteItem(BYTE *pWiasContext,
                                  LONG lFlags,
                                  LONG *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(plDevErrVal))
    {
        GUID guidWiaItemCategory = GUID_NULL;
        hr = wiasReadPropGuid(pWiasContext,WIA_IPA_ITEM_CATEGORY,&guidWiaItemCategory,NULL,TRUE);
        if(SUCCEEDED(hr))
        {
            if(guidWiaItemCategory == WIA_CATEGORY_FINISHED_FILE)
            {
                WIA_DRIVER_ITEM_CONTEXT *pWiaDriverItemContext = NULL;
                hr = wiasGetDriverItemPrivateContext(pWiasContext,(BYTE**)&pWiaDriverItemContext);
                if(SUCCEEDED(hr))
                {
                    if(!DeleteFile(pWiaDriverItemContext->bstrStorageDataPath))
                    {
                        hr = E_FAIL;
                        WIAS_ERROR((g_hInst, "Failed to delete %ws from storage, GetLastError = %d, hr = 0x%lx",::GetLastError(),hr));
                    }
                }
                else
                {
                    //
                    // If the WIA item does not have a driver item context, then
                    // assume that there is no associated storage data with it.
                    //

                    hr = S_OK;
                }
            }
            else
            {
                //
                // If the WIA item is not of finished file category, then
                // assume that there is no associated storage data with it.
                //

                hr = S_OK;
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to read the WIA_IPA_ITEM_CATEGORY property, hr = 0x%lx",hr));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }

    //
    // Only queue the deleted event, if the deletion was a success
    //

    if(SUCCEEDED(hr))
    {
        QueueWIAEvent(pWiasContext,WIA_EVENT_ITEM_DELETED);
    }

    return hr;
}
HRESULT CWIADriver::drvFreeDrvItemContext(LONG lFlags,
                                          BYTE *pSpecContext,
                                          LONG *plDevErrVal)
{

    WIA_DRIVER_ITEM_CONTEXT *pWiaDriverItemContext = (WIA_DRIVER_ITEM_CONTEXT*)pSpecContext;
    if(pWiaDriverItemContext)
    {
        // Free allocated BSTR if it exists.
        if(pWiaDriverItemContext->bstrStorageDataPath)
        {
            SysFreeString(pWiaDriverItemContext->bstrStorageDataPath);
            pWiaDriverItemContext->bstrStorageDataPath = NULL;
        }
    }

    return S_OK;
}
HRESULT CWIADriver::drvGetWiaFormatInfo(BYTE            *pWiasContext,
                                        LONG            lFlags,
                                        LONG            *pcelt,
                                        WIA_FORMAT_INFO **ppwfi,
                                        LONG            *plDevErrVal)
{
    HRESULT hr = E_INVALIDARG;
    if((plDevErrVal)&&(pcelt)&&(ppwfi))
    {
        if(m_pFormats)
        {
            delete [] m_pFormats;
            m_pFormats = NULL;
        }

        if(!m_pFormats)
        {
            m_ulNumFormats = DEFAULT_NUM_DRIVER_FORMATS;

            CBasicDynamicArray<GUID> FileFormats;

            //
            // add the default formats to the corresponding arrays
            //

            if(pWiasContext)
            {
                //
                // Create a format list that is specific to the WIA item.
                //

                LONG lItemType = 0;
                hr = wiasGetItemType(pWiasContext,&lItemType);
                if(SUCCEEDED(hr))
                {
                    if((lItemType & WiaItemTypeImage))
                    {
                        FileFormats.Append(WiaImgFmt_BMP);
                    }
                    else
                    {
                        FileFormats.Append(WiaImgFmt_UNDEFINED);
                    }
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Failed to get WIA item type, hr = 0x%lx",hr));
                }
            }
            else
            {
                //
                // Create a default format list
                //

                // FIX: for this device, we are assuming that the majority of data
                //      transferred will be image data, so when a query for formats fails,
                //      it is safe to default to bmp and memory bmp as the formats.
                FileFormats.Append(WiaImgFmt_BMP);
                hr = S_OK;
            }

            m_ulNumFormats  = FileFormats.Size();
            m_pFormats      = new WIA_FORMAT_INFO[m_ulNumFormats];
            if(m_pFormats)
            {
                //
                // add file (TYMED_FILE) formats to format array
                //

                for(INT iIndex = 0; iIndex < FileFormats.Size(); iIndex++)
                {
                    m_pFormats[iIndex].guidFormatID = FileFormats[iIndex];
                    m_pFormats[iIndex].lTymed       = TYMED_FILE;
                }

                hr = S_OK;
            }
            else
            {
                hr              = E_OUTOFMEMORY;
                m_ulNumFormats  = NULL;
                *ppwfi          = NULL;
                WIAS_ERROR((g_hInst, "Failed to allocate memory for WIA_FORMAT_INFO structure array, hr = 0x%lx",hr));
            }
        }

        if(m_pFormats)
        {
            *pcelt  = m_ulNumFormats;
            *ppwfi  = &m_pFormats[0];
            hr      = S_OK;
        }
        else
        {
            *pcelt = 0;
            *ppwfi = NULL;
        }

        *plDevErrVal = 0;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}
HRESULT CWIADriver::drvNotifyPnpEvent(const GUID *pEventGUID,
                                      BSTR       bstrDeviceID,
                                      ULONG      ulReserved)
{
    HRESULT hr = E_INVALIDARG;
    if(pEventGUID)
    {
        // TBD: Add any special event handling here.
        //      Power management, canceling pending I/O etc.
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

HRESULT CWIADriver::drvUnInitializeWia(BYTE *pWiasContext)
{
    HRESULT hr = E_INVALIDARG;
    if(pWiasContext)
    {
        if(InterlockedDecrement(&m_lClientsConnected) < 0)
        {
            WIAS_TRACE((g_hInst, "The client connection counter decremented below zero. Assuming no clients are currently connected and automatically setting to 0"));
            m_lClientsConnected = 0;
        }

        WIAS_TRACE((g_hInst,"%d client(s) are currently connected to this driver.",m_lClientsConnected));

        if(m_lClientsConnected == 0)
        {

            //
            // When the last client disconnects, destroy the WIA item tree.
            // This should reduce the idle memory foot print of this driver
            //

            DestroyDriverItemTree();
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

/////////////////////////////////////////////////////////////////////////
// INonDelegating Interface Section (for all WIA drivers)              //
/////////////////////////////////////////////////////////////////////////

HRESULT CWIADriver::NonDelegatingQueryInterface(REFIID  riid,LPVOID  *ppvObj)
{
    if(!ppvObj)
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
        return E_INVALIDARG;
    }

    *ppvObj = NULL;

    if(IsEqualIID( riid, IID_IUnknown ))
    {
        *ppvObj = static_cast<INonDelegatingUnknown*>(this);
    }
    else if(IsEqualIID( riid, IID_IStiUSD ))
    {
        *ppvObj = static_cast<IStiUSD*>(this);
    }
    else if(IsEqualIID( riid, IID_IWiaMiniDrv ))
    {
        *ppvObj = static_cast<IWiaMiniDrv*>(this);
    }
    else
    {
        return E_NOINTERFACE;
    }

    reinterpret_cast<IUnknown*>(*ppvObj)->AddRef();
    return S_OK;
}

ULONG CWIADriver::NonDelegatingAddRef()
{
    return InterlockedIncrement(&m_cRef);
}

ULONG CWIADriver::NonDelegatingRelease()
{
    ULONG ulRef = InterlockedDecrement(&m_cRef);
    if(ulRef == 0)
    {
        delete this;
        return 0;
    }
    return ulRef;
}

/////////////////////////////////////////////////////////////////////////
// IClassFactory Interface Section (for all COM objects)               //
/////////////////////////////////////////////////////////////////////////

class CWIADriverClassFactory : public IClassFactory
{
public:
    CWIADriverClassFactory() : m_cRef(1) {}
    ~CWIADriverClassFactory(){}
    HRESULT __stdcall QueryInterface(REFIID riid, LPVOID *ppv)
    {
        if(!ppv)
        {
            WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
            return E_INVALIDARG;
        }

        *ppv = NULL;
        HRESULT hr = E_NOINTERFACE;
        if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
        {
            *ppv = static_cast<IClassFactory*>(this);
            reinterpret_cast<IUnknown*>(*ppv)->AddRef();
            hr = S_OK;
        }
        return hr;
    }
    ULONG __stdcall AddRef()
    {
        return InterlockedIncrement(&m_cRef);
    }
    ULONG __stdcall Release()
    {
        ULONG ulRef = InterlockedDecrement(&m_cRef);
        if(ulRef == 0)
        {
            delete this;
            return 0;
        }
        return ulRef;
    }
    HRESULT __stdcall CreateInstance(IUnknown __RPC_FAR *pUnkOuter,REFIID riid,void __RPC_FAR *__RPC_FAR *ppvObject)
    {
        if((pUnkOuter)&&(!IsEqualIID(riid,IID_IUnknown)))
        {
            return CLASS_E_NOAGGREGATION;
        }

        HRESULT hr = E_NOINTERFACE;
        CWIADriver *pDev = new CWIADriver(pUnkOuter);
        if(pDev)
        {
            hr = pDev->NonDelegatingQueryInterface(riid,ppvObject);
            pDev->NonDelegatingRelease();
        }
        else
        {
            hr = E_OUTOFMEMORY;
            WIAS_ERROR((g_hInst, "Failed to allocate WIA driver class object, hr = 0x%lx",hr));
        }

        return hr;
    }
    HRESULT __stdcall LockServer(BOOL fLock)
    {
        return S_OK;
    }
private:
    LONG m_cRef;
};

/////////////////////////////////////////////////////////////////////////
// DLL Entry Point Section (for all COM objects, in a DLL)             //
/////////////////////////////////////////////////////////////////////////

extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HINSTANCE hinst,DWORD dwReason,LPVOID lpReserved)
{
    g_hInst = hinst;
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinst);
        break;
    }
    return TRUE;
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
    return S_OK;
}
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,LPVOID *ppv)
{
    if(!ppv)
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
        return E_INVALIDARG;
    }
    HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;
    if(IsEqualCLSID(rclsid, CLSID_WIADriver))
    {
        CWIADriverClassFactory *pcf = new CWIADriverClassFactory;
        if(pcf)
        {
            hr = pcf->QueryInterface(riid,ppv);
            pcf->Release();
        }
        else
        {
            hr = E_OUTOFMEMORY;
            WIAS_ERROR((g_hInst, "Failed to allocate WIA driver class factory object, hr = 0x%lx",hr));
        }
    }
    return hr;
}

extern "C" HRESULT __stdcall DllRegisterServer()
{
    return S_OK;
}

extern "C" HRESULT __stdcall DllUnregisterServer()
{
    return S_OK;
}
