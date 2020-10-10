/**************************************************************************
*
*  Copyright (c) 2003  Microsoft Corporation
*
*  Title: wiadriver.h
*
*  Description: This contains the WIA driver class definition and needed
*               defines.
*
***************************************************************************/

#pragma once

#define MY_WIA_ERROR_HANDLING_PROP         WIA_PRIVATE_ITEMPROP
#define MY_WIA_ERROR_HANDLING_PROP_STR     L"My error handling property"

#define ERROR_HANDLING_NONE                0x00000000
#define ERROR_HANDLING_WARMING_UP          0x00000001
#define ERROR_HANDLING_COVER_OPEN          0x00000002
#define ERROR_HANDLING_PRIVATE_ERROR       0x00000004
#define ERROR_HANDLING_UNHANDLED_STATUS    0x00000008
#define ERROR_HANDLING_UNHANDLED_ERROR     0x00000010

#define REG_ENTRY_DEVICEDATA            TEXT("DeviceData")
#define REG_ENTRY_STORAGEPATH           TEXT("StoragePath")

#define WIA_DRIVER_ROOT_NAME            L"Root"    // THIS SHOULD NOT BE LOCALIZED
#define WIA_DRIVER_FLATBED_NAME         L"Flatbed" // THIS SHOULD NOT BE LOCALIZED
#define WIA_DRIVER_FEEDER_NAME          L"Feeder"  // THIS SHOULD NOT BE LOCALIZED
#define WIA_DRIVER_FILM_NAME            L"Film"    // THIS SHOULD NOT BE LOCALIZED
#define WIA_DRIVER_STORAGE_NAME         L"Storage" // THIS SHOULD NOT BE LOCALIZED

#define DEFAULT_LOCK_TIMEOUT            1000
#define DEFAULT_NUM_DRIVER_EVENTS       2
#define DEFAULT_NUM_DRIVER_COMMANDS     0
#define DEFAULT_NUM_DRIVER_FORMATS      2

typedef struct _WIA_DRIVER_ITEM_CONTEXT
{
    GUID    guidItemCategory;
    LONG    lNumItemsStored;
    BSTR    bstrStorageDataPath;
}WIA_DRIVER_ITEM_CONTEXT,*PWIA_DRIVER_ITEM_CONTEXT;

class INonDelegatingUnknown {
public:
    virtual STDMETHODIMP NonDelegatingQueryInterface(REFIID riid,LPVOID *ppvObj) = 0;
    virtual STDMETHODIMP_(ULONG) NonDelegatingAddRef() = 0;
    virtual STDMETHODIMP_(ULONG) NonDelegatingRelease() = 0;
};

class CWIADriver : public INonDelegatingUnknown, // NonDelegatingUnknown
                   public IStiUSD,               // STI USD interface
                   public IWiaMiniDrv            // WIA Minidriver interface
{
public:

    ///////////////////////////////////////////////////////////////////////////
    // Construction/Destruction Section
    ///////////////////////////////////////////////////////////////////////////

    CWIADriver(LPUNKNOWN punkOuter);
    ~CWIADriver();

private:

    ///////////////////////////////////////////////////////////////////////////
    // WIA driver internals
    ///////////////////////////////////////////////////////////////////////////

    LONG                    m_cRef;                     // Device object reference count.
    LPUNKNOWN               m_punkOuter;                // Pointer to outer unknown.
    IStiDevice             *m_pIStiDevice;              // STI device interface for locking
    IWiaDrvItem            *m_pIDrvItemRoot;            // WIA root item
    LONG                    m_lClientsConnected;        // number of applications connected
    CWIACapabilityManager   m_CapabilityManager;        // WIA driver capabilities
    WIA_FORMAT_INFO        *m_pFormats;                 // WIA format information
    ULONG                   m_ulNumFormats;             // number of data formats
    BSTR                    m_bstrDeviceID;             // WIA device ID;
    ULONG_PTR               m_ulImageLibraryToken;      // GDI plus token
    WiaDevice               m_WiaDevice;                // Simulated device object
    WCHAR                   m_wszStoragePath[MAX_PATH]; // WIA storage path
    BSTR                    m_bstrRootFullItemName;     // WIA root item (full item name)

public:

    ///////////////////////////////////////////////////////////////////////////
    // Standard COM Section
    ///////////////////////////////////////////////////////////////////////////

    STDMETHODIMP QueryInterface( REFIID riid, LPVOID * ppvObj);

    STDMETHODIMP_(ULONG) AddRef();

    STDMETHODIMP_(ULONG) Release();

    ///////////////////////////////////////////////////////////////////////////
    // IStiUSD Interface Section (for all WIA drivers)
    ///////////////////////////////////////////////////////////////////////////

    STDMETHOD(Initialize)(THIS_
                          PSTIDEVICECONTROL pHelDcb,
                          DWORD             dwStiVersion,
                          HKEY              hParametersKey);

    STDMETHOD(GetCapabilities)(THIS_ PSTI_USD_CAPS pDevCaps);

    STDMETHOD(GetStatus)(THIS_ PSTI_DEVICE_STATUS pDevStatus);

    STDMETHOD(DeviceReset)(THIS);

    STDMETHOD(Diagnostic)(THIS_ LPDIAG pBuffer);

    STDMETHOD(Escape)(THIS_
                      STI_RAW_CONTROL_CODE EscapeFunction,
                      LPVOID               lpInData,
                      DWORD                cbInDataSize,
                      LPVOID               pOutData,
                      DWORD                dwOutDataSize,
                      LPDWORD              pdwActualData);

    STDMETHOD(GetLastError)(THIS_ LPDWORD pdwLastDeviceError);

    STDMETHOD(LockDevice)();

    STDMETHOD(UnLockDevice)();

    STDMETHOD(RawReadData)(THIS_
                           LPVOID       lpBuffer,
                           LPDWORD      lpdwNumberOfBytes,
                           LPOVERLAPPED lpOverlapped);

    STDMETHOD(RawWriteData)(THIS_
                            LPVOID       lpBuffer,
                            DWORD        dwNumberOfBytes,
                            LPOVERLAPPED lpOverlapped);

    STDMETHOD(RawReadCommand)(THIS_
                              LPVOID       lpBuffer,
                              LPDWORD      lpdwNumberOfBytes,
                              LPOVERLAPPED lpOverlapped);

    STDMETHOD(RawWriteCommand)(THIS_
                               LPVOID       lpBuffer,
                               DWORD        dwNumberOfBytes,
                               LPOVERLAPPED lpOverlapped);

    STDMETHOD(SetNotificationHandle)(THIS_ HANDLE hEvent);

    STDMETHOD(GetNotificationData)(THIS_ LPSTINOTIFY lpNotify);

    STDMETHOD(GetLastErrorInfo)(THIS_ STI_ERROR_INFO *pLastErrorInfo);

    /////////////////////////////////////////////////////////////////////////
    // IWiaMiniDrv Interface Section (for all WIA drivers)                 //
    /////////////////////////////////////////////////////////////////////////

    STDMETHOD(drvInitializeWia)(THIS_
                                BYTE        *pWiasContext,
                                LONG        lFlags,
                                BSTR        bstrDeviceID,
                                BSTR        bstrRootFullItemName,
                                IUnknown    *pStiDevice,
                                IUnknown    *pIUnknownOuter,
                                IWiaDrvItem **ppIDrvItemRoot,
                                IUnknown    **ppIUnknownInner,
                                LONG        *plDevErrVal);

    STDMETHOD(drvAcquireItemData)(THIS_
                                  BYTE                      *pWiasContext,
                                  LONG                      lFlags,
                                  PMINIDRV_TRANSFER_CONTEXT pmdtc,
                                  LONG                      *plDevErrVal);

    STDMETHOD(drvInitItemProperties)(THIS_
                                     BYTE *pWiasContext,
                                     LONG lFlags,
                                     LONG *plDevErrVal);

    STDMETHOD(drvValidateItemProperties)(THIS_
                                         BYTE           *pWiasContext,
                                         LONG           lFlags,
                                         ULONG          nPropSpec,
                                         const PROPSPEC *pPropSpec,
                                         LONG           *plDevErrVal);

    STDMETHOD(drvWriteItemProperties)(THIS_
                                      BYTE                      *pWiasContext,
                                      LONG                      lFlags,
                                      PMINIDRV_TRANSFER_CONTEXT pmdtc,
                                      LONG                      *plDevErrVal);

    STDMETHOD(drvReadItemProperties)(THIS_
                                     BYTE           *pWiasContext,
                                     LONG           lFlags,
                                     ULONG          nPropSpec,
                                     const PROPSPEC *pPropSpec,
                                     LONG           *plDevErrVal);

    STDMETHOD(drvLockWiaDevice)(THIS_
                                BYTE *pWiasContext,
                                LONG lFlags,
                                LONG *plDevErrVal);

    STDMETHOD(drvUnLockWiaDevice)(THIS_
                                  BYTE *pWiasContext,
                                  LONG lFlags,
                                  LONG *plDevErrVal);

    STDMETHOD(drvAnalyzeItem)(THIS_
                              BYTE *pWiasContext,
                              LONG lFlags,
                              LONG *plDevErrVal);

    STDMETHOD(drvGetDeviceErrorStr)(THIS_
                                    LONG     lFlags,
                                    LONG     lDevErrVal,
                                    LPOLESTR *ppszDevErrStr,
                                    LONG     *plDevErr);

    STDMETHOD(drvDeviceCommand)(THIS_
                                BYTE        *pWiasContext,
                                LONG        lFlags,
                                const GUID  *plCommand,
                                IWiaDrvItem **ppWiaDrvItem,
                                LONG        *plDevErrVal);

    STDMETHOD(drvGetCapabilities)(THIS_
                                  BYTE            *pWiasContext,
                                  LONG            ulFlags,
                                  LONG            *pcelt,
                                  WIA_DEV_CAP_DRV **ppCapabilities,
                                  LONG            *plDevErrVal);

    STDMETHOD(drvDeleteItem)(THIS_
                             BYTE *pWiasContext,
                             LONG lFlags,
                             LONG *plDevErrVal);

    STDMETHOD(drvFreeDrvItemContext)(THIS_
                                     LONG lFlags,
                                     BYTE *pSpecContext,
                                     LONG *plDevErrVal);

    STDMETHOD(drvGetWiaFormatInfo)(THIS_
                                   BYTE            *pWiasContext,
                                   LONG            lFlags,
                                   LONG            *pcelt,
                                   WIA_FORMAT_INFO **ppwfi,
                                   LONG            *plDevErrVal);

    STDMETHOD(drvNotifyPnpEvent)(THIS_
                                 const GUID *pEventGUID,
                                 BSTR       bstrDeviceID,
                                 ULONG      ulReserved);

    STDMETHOD(drvUnInitializeWia)(THIS_ BYTE *pWiasContext);

public:

    /////////////////////////////////////////////////////////////////////////
    // INonDelegating Interface Section (for all WIA drivers)              //
    /////////////////////////////////////////////////////////////////////////

    STDMETHODIMP NonDelegatingQueryInterface(REFIID  riid,LPVOID  *ppvObj);
    STDMETHODIMP_(ULONG) NonDelegatingAddRef();
    STDMETHODIMP_(ULONG) NonDelegatingRelease();

private:

    /////////////////////////////////////////////////////////////////////////
    // Minidriver private methods specific Section                         //
    /////////////////////////////////////////////////////////////////////////

    UINT GetBitmapResourceIDFromCategory(const GUID &guidItemCategory);

    HRESULT DownloadToStream(LONG                           lflags,
                             BYTE                           *pWiasContext,
                             const GUID                     &guidItemCategory,
                             IWiaMiniDrvTransferCallback    *pTransferCallback,
                             LONG                           *plDevErrVal);

    HRESULT UploadFromStream(LONG                           lflags,
                             BYTE                           *pWiasContext,
                             const GUID                     &guidItemCategory,
                             IWiaMiniDrvTransferCallback    *pTransferCallback,
                             LONG                           *plDevErrVal);

    HRESULT LegacyDownload(LONG                      lFlags,
                           BYTE                      *pWiasContext,
                           const GUID                &guidItemCategory,
                           PMINIDRV_TRANSFER_CONTEXT pmdtc,
                           LONG                      *plDevErrVal);

    HRESULT BuildDriverItemTree();

    HRESULT DestroyDriverItemTree();

    HRESULT DoSynchronizeCommand(BYTE *pWiasContext);

};
