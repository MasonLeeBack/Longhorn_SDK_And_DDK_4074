/*****************************************************************************
 *
 *  imagefilter.h
 *
 *  Copyright (c) 2003 Microsoft Corporation.  All Rights Reserved.
 *
 *  DESCRIPTION:
 *
 *  Contains class declarations  for CMyFilterStream and CImageFilter
 *  
 *******************************************************************************/

#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))
#define HEADER_SIZE 54

#ifndef PI
#define PI 3.1415926538
#endif

// {AA9198F3-3B91-47d3-A371-EBE7D243F606}
static const GUID CLSID_WiaImageFilter = 
{ 0xaa9198f3, 0x3b91, 0x47d3, { 0xa3, 0x71, 0xeb, 0xe7, 0xd2, 0x43, 0xf6, 0x6 } };

static LONG g_cLocks = 0;

void LockModule(void)   { InterlockedIncrement(&g_cLocks); }
void UnlockModule(void) { InterlockedDecrement(&g_cLocks); }

/*****************************************************************************
 *
 * CMyFilterStream is our implemetation of the filtering stream.
 * The only IStream method that it implements is Write().
 *
 * The stream keeps a reference to the applications stream into which it writes
 * the filtered data (the header is not modified however).
 *  
 *******************************************************************************/

class CMyFilterStream : public IStream
{
public:


    CMyFilterStream(
        VOID);

    ~CMyFilterStream(
        VOID);

    STDMETHODIMP
    Initialize(
        IStream      *pAppStream,
        LONG         lBrightness,
        LONG         lContrast,
        LONG         lRotation,
        LONG         lDeskewX,
        LONG         lDeskewY,
        LONG         lXExtent,
        LONG         lYExtent,
        LONG         lBitDepth
        );

    STDMETHODIMP
    Flush(void);

    STDMETHODIMP
    QueryInterface(const IID& iid_requested, void** ppInterfaceOut);

    STDMETHODIMP_(ULONG)
    AddRef(void);

    STDMETHODIMP_(ULONG)
    Release(void);

    STDMETHODIMP
    Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
    
    STDMETHODIMP
    SetSize(ULARGE_INTEGER libNewSize);
    
    STDMETHODIMP
    LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
    
    STDMETHODIMP
    CopyTo(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
     
    STDMETHODIMP
    Commit(DWORD grfCommitFlags);
    
    STDMETHODIMP
    Revert(void);
    
    STDMETHODIMP
    UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
    
    STDMETHODIMP
    Stat(STATSTG *pstatstg, DWORD grfStatFlag);
    
    STDMETHODIMP
    Clone(IStream **ppstm);
    
    STDMETHODIMP
    Read(void *pv, ULONG cb, ULONG *pcbRead);
    
    STDMETHODIMP
    Write(const void *pv, ULONG cb, ULONG *pcbWritten);

    ULONG64         m_cBytesWritten;

private:
    
    IStream         *m_pAppStream;
    IStream         *m_pCachingStream;

    LONG            m_lBrightness;
    LONG            m_lContrast;
    LONG            m_lRotation;
    LONG            m_lDeskewX;
    LONG            m_lDeskewY;

    LONG            m_nRefCount;
};


/*****************************************************************************
 *
 * CImageFilter is the main image processing filter class. It implements IWiaImageFilter
 * as well as the callback interface IWiaTransferCallback.
 *
 * Internally it creates the filtering stream CMyFilterStream in its GetNextStream
 * implementation. Its implementation of TransferCallback simply delegates to the
 * applications callback, since it does not alter the size or the flow of the data
 * that the driver writes to it.
 *  
 *******************************************************************************/
class CImageFilter : public IWiaImageFilter, public IWiaTransferCallback
{
public:

    CImageFilter(
        VOID);

    ~CImageFilter(
        VOID);

    STDMETHODIMP
    QueryInterface(const IID& iid_requested, void** ppInterfaceOut);

    STDMETHODIMP_(ULONG)
    AddRef(void);

    STDMETHODIMP_(ULONG)
    Release(void);

    STDMETHODIMP
    InitializeFilter(
        IN  IWiaItem2               *pWiaItem,
        IN  IWiaTransferCallback    *pWiaTransferCallback);

    STDMETHODIMP
    FilterPreviewImage(
        IN     IWiaItem2               *pWiaChildItem,
        IN     RECT                    InputImageExtents,
        IN     IStream                 *pInputStream);

    STDMETHODIMP
    TransferCallback(
        IN  LONG                lFlags,
        IN  WiaTransferParams   *pWiaTransferParams);
        
    STDMETHODIMP
    GetNextStream(
        IN  LONG                lFlags,
        IN  BSTR                bstrItemName,
        IN  BSTR                bstrFullItemName,
        OUT IStream             **ppDestination);

   LONG    lPercentComplete;
   ULONG64 m_ulBytesWrittenToCurrentStream;
    
private:

    CMyFilterStream         *m_pCurrentStream;

    IWiaItem2               *m_pWiaItem;
    IWiaTransferCallback    *m_pAppWiaTransferCallback;

    LONG                    m_nRefCount;
};


