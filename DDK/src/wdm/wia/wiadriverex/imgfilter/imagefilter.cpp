/*****************************************************************************
 *
 *  imagefilter.cpp
 *
 *  Copyright (c) 2003 Microsoft Corporation.  All Rights Reserved.
 *
 *  DESCRIPTION:
 *
 *  Contains implementation of Image Processing Filer with "filtering stream".
 *  The implementation uses GDI+ for cutting out images, for deskewing as well
 *  as for implementing brightness and contrast. 
 *  
 *******************************************************************************/
#include "stdafx.h"
#include <gdiplus.h>
#include <math.h>

#include "imagefilter.h"
#include "wiaitem.h"
#include "gphelper.h"

using namespace Gdiplus;

/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | DoFiltering | Reads unfiltered data from input stream, cuts, deskews, rotates and filters the image data
 *                                     and then writes fitlered data to output stream.
 *
 *  @parm   LONG | lBrightness |
 *          The brightness set into the region we are filtering. Should be between -1000 and 1000
 * 
 *  @parm   LONG | lContrast |
 *          The contrast set into the region we are filtering. Should be between -1000 and 1000
 * 
 *  @parm   LONG | regionRotate |
 *          How much we should rotate the reion (note rotate happens after deskew!)
 * 
 *  @parm   LONG | regionDeskewX |
 *          WIA_IPS_DESKEW_X for region to deskew (note 0 means no deskew)
 * 
 *  @parm   LONG | regionDeskewY |
 *          WIA_IPS_DESKEW_Y for region to deskew (note 0 means no deskew)
 * 
 *  @parm   IStream* | pInputStream |
 *          Unfiltered image data, either directly from driver of from WIA Preview Component
 *
 *  
 *  @parm   IStream* | pOutputStream |
 *          Application stream where we write image data
 *
 *  @parm   LONG | inputXPOS |
 *          X-position of upper left corner of region to "cut-out" from image in pInputStream.
 *          Note that this parameter is relative to image in pInputStream which is not necessarily
 *          its X-position on the flatbed.
 *  
 *  @parm   LONG | inputYPOS |
 *          Y-position of upper left corner of region to "cut-out" from image in pInputStream.
 *          Note that this parameter is relative to image in pInputStream which is not necessarily
 *          its Y-position on the flatbed.
 * 
 *  @parm   LONG | boundingRegionWidth |
 *          Width of bounding area to "cut-out" from pInputStream. A value of 0 means that we should not perform
 *          any cutting, but instead filter the whole image.
 *          boundingRegionWidth will be set to 0 when we receive the image data from the driver since the driver
 *          will only send us the bounding rectangle of the selected region and not the entire flatbed.
 *          Note: if there is not deskewing being performed this is the "actual" width of the region.
 * 
 *  @parm   LONG | boundingRegionHeight |
 *          Height of bounding area to "cut-out" from pInputStream. A value of 0 means that we should not perform
 *          any cutting, but instead filter the whole image.
 *          boundingRegionHeight will be set to 0 when we receive the image data from the driver since the driver
 *          will only send us the bounding rectangle of the selected region and not the entire flatbed. 
 *          Note: if there is not deskewing being performed this is the "actual" height of the region.
 *
 *  @comm
 *  Note, our simple implementation of DoFiltering always write all the data
 *  in one chunk to the application. An actual image processing filter should
 *  be able to work on bands of data in the case where there is no rotation
 *  or deskewing being performed.
 *  This implementation also does not send callbacks (TransferCallback) messages
 *  to the application indicating progress. A "real" implementation should do that!
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXX   | 
 *              The function failed 
 * 
 *****************************************************************************/

static HRESULT DoFiltering(
    LONG        lBrightness,
    LONG        lContrast,
    LONG        regionRotate,
    LONG        regionDeskewX,
    LONG        regionDeskewY,
    IStream     *pInputStream,
    IStream     *pOutputStream,
    LONG        inputXPOS = 0,
    LONG        inputYPOS = 0,
    LONG        boundingRegionWidth = 0,
    LONG        boundingRegionHeight = 0
    )
{
    HRESULT                 hr                  = S_OK;

    Bitmap                  *pOriginalBitmap    = NULL;
    Bitmap                  *pTargetBitmap      = NULL;
    CLSID                   formatEncoder       = {0};
    GdiplusStartupInput     gdiplusStartupInput;
    ULONG_PTR               ulImageLibraryToken = 0;

    if (SUCCEEDED(hr))
    {
        hr = GDISTATUS_TO_HRESULT(GdiplusStartup(&ulImageLibraryToken, &gdiplusStartupInput, NULL));
    }

    //
    // Create a Bitmap object on the unfiltered input stream
    //
    if (SUCCEEDED(hr))
    {
        pOriginalBitmap = new Bitmap(pInputStream, TRUE);

        if (pOriginalBitmap)
        {
            hr = GDISTATUS_TO_HRESULT(pOriginalBitmap->GetLastStatus());
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }

        if (SUCCEEDED(hr))
        {
            hr = GDISTATUS_TO_HRESULT(GetEncoderGUIDFromImage(pOriginalBitmap, &formatEncoder));
        }
    }

    //
    // If boundingRegionWidth or boundingRegionHeight is 0, this means that we should not perform any
    // "cutting" but instead just filter the whole input image.
    //
    if (SUCCEEDED(hr))
    {
        if ((0 == boundingRegionWidth) || (0 == boundingRegionHeight))
        {
            inputXPOS = 0;
            inputXPOS = 0;
            boundingRegionWidth  = pOriginalBitmap->GetWidth();
            boundingRegionHeight = pOriginalBitmap->GetHeight();
        }
    }

    //
    // Perform filtering. This is done in 3 steps:
    // 1. Create a new bitmap with the dimensions of the final, filtered image.
    // 2. "Cut-out" and deskew final image from full image. This is done by a translate
    //    followed by a rotate transformtation.
    // 3. Apply color matrix to to perform brightness and contrast modifications.
    //
    if (SUCCEEDED(hr))
    {
        PixelFormat     originalPixelFormat = pOriginalBitmap->GetPixelFormat();

        double dblDeskewAngle        = 0.0;
        LONG   lXdelta               = 0;
        LONG   lYdelta               = 0;
        LONG   lActualRegionWidth    = 0;
        LONG   lActualRegionHeight   = 0;

        //
        // No deskew, just cut out a rectangular area!
        //
        if ((regionDeskewX) == 0 || (regionDeskewY == 0))
        {
            lActualRegionWidth  = boundingRegionWidth;
            lActualRegionHeight = boundingRegionHeight;
            dblDeskewAngle = 0.0;
        }
        else
        {
            if (regionDeskewX > regionDeskewY)
            {
                lYdelta = regionDeskewY;

                dblDeskewAngle = atan2((double)regionDeskewY, (double)regionDeskewX);

                lActualRegionWidth  = (LONG) sqrt((double) (regionDeskewX * regionDeskewX + regionDeskewY * regionDeskewY));
                lActualRegionHeight = (LONG) (((double) (boundingRegionHeight - regionDeskewY)) / cos(dblDeskewAngle));
            }
            else         
            {
                lXdelta = regionDeskewX;

                dblDeskewAngle = atan2((double)regionDeskewX, (double)regionDeskewY);

                lActualRegionWidth  = (LONG) (((double) (boundingRegionWidth - regionDeskewX)) / cos(dblDeskewAngle)); 
                lActualRegionHeight = (LONG) sqrt((double) (regionDeskewX * regionDeskewX + regionDeskewY * regionDeskewY));

                dblDeskewAngle = -dblDeskewAngle;
            }
        }

        pTargetBitmap = new Bitmap(lActualRegionWidth, lActualRegionHeight, originalPixelFormat);

        if (pTargetBitmap)
        {
            hr = GDISTATUS_TO_HRESULT(pTargetBitmap->GetLastStatus());
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }

        

        if (SUCCEEDED(hr))
        {
            Graphics        graphics(pTargetBitmap);
            ImageAttributes imageAttributes;

            hr = GDISTATUS_TO_HRESULT(graphics.GetLastStatus());

            if (SUCCEEDED(hr))
            {
                graphics.TranslateTransform((REAL)-(inputXPOS + lXdelta), (REAL)-(inputYPOS + lYdelta));
                hr = GDISTATUS_TO_HRESULT(graphics.GetLastStatus());
            }


            if (dblDeskewAngle != 0.0)
            {
                if (SUCCEEDED(hr))
                {
                    graphics.RotateTransform((REAL)(dblDeskewAngle * 180.0 / PI), MatrixOrderAppend);
                    hr = GDISTATUS_TO_HRESULT(graphics.GetLastStatus());
                }
            }

            if (SUCCEEDED(hr))
            {
                //
                // Calculate the values needed for the matrix
                //
                REAL scale = 0.0;
                REAL trans = 0.0;

                //
                // Normalize brightness and contrast to 0 to 1000.
                // This assumes valid settings are - 1000 to 1000.
                //
                CalculateBrightnessAndContrastParams( (lBrightness + 1000) /2, (lContrast + 1000) / 2, &scale, &trans );
    
                //
                // Prepare the matrix for brightness and contrast transforms
                //
                ColorMatrix brightnessAndContrast = {scale, 0,     0,     0,     0,
                                                     0,     scale, 0,     0,     0,
                                                     0,     0,     scale, 0,     0,
                                                     0,     0,     0,     1,     0,
                                                     trans, trans, trans, 0,     1};
    
                hr = imageAttributes.SetColorMatrix(&brightnessAndContrast);
            }
            
            if (SUCCEEDED(hr))
            {
                UINT    uWidth  = pOriginalBitmap->GetWidth();
                UINT    uHeight = pOriginalBitmap->GetHeight();

                Rect rect( 0, 0, uWidth, uHeight );

                hr = GDISTATUS_TO_HRESULT(graphics.DrawImage(pOriginalBitmap,rect,0,0,uWidth, uHeight,UnitPixel,&imageAttributes));
            }
        }
        
        
    }

    //
    // The last step for us to perform is rotating the region
    //
    if (SUCCEEDED(hr) && (regionRotate != PORTRAIT))
    {
        RotateFlipType  rotateFlipType;

        switch (regionRotate)
        {
            case LANSCAPE:
                rotateFlipType = Rotate270FlipNone;
                break;
            case ROT180:
                rotateFlipType = Rotate180FlipNone;
                break;
            case ROT270:                            
                rotateFlipType = Rotate90FlipNone;
                break;
            default:
                //
                // We should never get here!
                //
                rotateFlipType = RotateNoneFlipNone;
        }

        hr = GDISTATUS_TO_HRESULT(pTargetBitmap->RotateFlip(rotateFlipType));
    }

    //
    // The GDI+ Bitmap::Save method does not work very well for images that
    // an application displays band by band since it results in a large number
    // of small Write calls. Instead we do a LockBits to read the bits from
    // the bitmap and then write them to the application's stream.
    //
    if (SUCCEEDED(hr))
    {
        hr = WriteBitmapToStream(pTargetBitmap, pOutputStream);
    }
    
    if (pOriginalBitmap)
    {
        delete pOriginalBitmap;
    }

    if (pTargetBitmap)
    {
        delete pTargetBitmap;
    }

    if(ulImageLibraryToken)
    {
        GdiplusShutdown(ulImageLibraryToken);
        ulImageLibraryToken = 0;
    }

    return hr;
}

/*****************************************************************************
 *
 * CMyFilterStream is our implemetation of the filtering stream.
 * The only IStream method that it implements is Write().
 *
 * The stream keeps a reference to the applications stream into which it writes
 * the filtered data (the header is not modified however).
 *  
 *******************************************************************************/

///
///  Constructor - note sets reference count to 1
///
CMyFilterStream::CMyFilterStream(
    VOID) : m_pAppStream(NULL) , m_pCachingStream(NULL), m_nRefCount(1), m_cBytesWritten(0),
            m_lBrightness(0), m_lContrast(0), m_lRotation(0), m_lDeskewX(0), m_lDeskewY(0)
{
}

///
///  Destructor:
///
CMyFilterStream::~CMyFilterStream(
    VOID)
{
    if (m_pAppStream)
    {
        m_pAppStream->Release();
        m_pAppStream = NULL;
    }

    if (m_pCachingStream)
    {
        m_pCachingStream->Release();
        m_pCachingStream = NULL;
    }
}

///
/// Initilize stores a reference to the application's stream. It also creates
/// its own stream with CreateStreamOnHGlobal into which it stores all the
/// unfiltered image data before it performs its filtering (in Flush).
///
HRESULT
CMyFilterStream::Initialize(
    IStream      *pAppStream,
    LONG         lBrightness,
    LONG         lContrast,
    LONG         lRotation,
    LONG         lDeskewX,
    LONG         lDeskewY,
    LONG         lXExtent,
    LONG         lYExtent,
    LONG         lBitDepth)
{
    HRESULT     hr = S_OK;

    hr = pAppStream ? S_OK : E_INVALIDARG;

    if (SUCCEEDED(hr))
    {
        m_pAppStream = pAppStream;
        m_pAppStream->AddRef();
    }

    if (SUCCEEDED(hr))
    {
        hr = CreateStreamOnHGlobal(0, TRUE, &m_pCachingStream);

        //
        // For large images it is important that we make a good estimate of the image size,
        // otherwise memory re-allocations may become very expensive.
        //
        if (SUCCEEDED(hr))
        {
            ULARGE_INTEGER ullSize = {0};
            LARGE_INTEGER  ullPos  = {0};

            ullSize.QuadPart = GetUpperLimitSize(lXExtent, lYExtent, lBitDepth);

            hr = m_pCachingStream->SetSize(ullSize);

            if (SUCCEEDED(hr))
            {
                hr = m_pCachingStream->Seek(ullPos, STREAM_SEEK_SET, NULL);
            }
        }
    }

    if (SUCCEEDED(hr))
    {
        m_lBrightness = lBrightness;
        m_lContrast   = lContrast;
        m_lRotation   = lRotation;
        m_lDeskewX    = lDeskewX;
        m_lDeskewY    = lDeskewY;
    }

    return hr;
}

/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | CMyFilterStream::Flush | Reads unfiltered data, performs filtering and writes
 *                                                data to application stream
 *  
 *  @comm
 *
 * Flush is called when the image processing filter receives a WIA_TRANSFER_MSG_END_OF_STREAM message.
 * Flush calls DoFiltering where the actual filtering is done.
 *
 * Note that this simple implementation performs all its filtering only after it has received all
 * unfiltered image data and stored it in m_pCachingStream. A "real" implementation should be able
 * to work on bands of data (at least if no deskew and rotation has to be performed).
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXX   | 
 *              The function failed 
 * 
 *****************************************************************************/
HRESULT
CMyFilterStream::Flush(
    VOID)
{
    HRESULT hr;

    hr = DoFiltering(
        m_lBrightness,
        m_lContrast,
        m_lRotation,
        m_lDeskewX,
        m_lDeskewY,
        m_pCachingStream,
        m_pAppStream);

    if (m_pAppStream)
    {
        m_pAppStream->Release();
        m_pAppStream = NULL;
    }

    if (m_pCachingStream)
    {
        m_pCachingStream->Release();
        m_pCachingStream = NULL;
    }

    return hr;
}

///
///  Query Interface
///
STDMETHODIMP
CMyFilterStream::QueryInterface(const IID& iid_requested, void** ppInterfaceOut)
{
    HRESULT hr = S_OK;

    hr = ppInterfaceOut ? S_OK : E_POINTER;

    if (SUCCEEDED(hr))
    {
        *ppInterfaceOut = NULL;
    }

    //
    //  We support IID_IUnknown and IID_IStream
    //
    if (SUCCEEDED(hr))
    {
        if (IID_IUnknown == iid_requested) 
        {
            *ppInterfaceOut = static_cast<IUnknown*>(this);
        }
        else if (IID_IStream == iid_requested) 
        {
            *ppInterfaceOut = static_cast<IStream*>(this);
        }
        else
        {
            hr = E_NOINTERFACE;
        }
    }

    if (SUCCEEDED(hr))
    {
        reinterpret_cast<IUnknown*>(*ppInterfaceOut)->AddRef();
    }

    return hr;
}

///
///  AddRef
///
STDMETHODIMP_(ULONG)
CMyFilterStream::AddRef(void)
{
    if (m_nRefCount == 0)
    {
        LockModule();
    }

    return InterlockedIncrement(&m_nRefCount);
}

///
///  Release
///
STDMETHODIMP_(ULONG)
CMyFilterStream::Release(void)
{
    ULONG nRetval = InterlockedDecrement(&m_nRefCount);

    if (0 == nRetval) 
    {
        delete this;
        UnlockModule();
    }

    return nRetval;
}

STDMETHODIMP
CMyFilterStream::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
{
    return m_pCachingStream->Seek(dlibMove,dwOrigin,plibNewPosition);
}

STDMETHODIMP
CMyFilterStream::SetSize(ULARGE_INTEGER libNewSize)
{
    return m_pCachingStream->SetSize(libNewSize);
}

STDMETHODIMP
CMyFilterStream::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    return m_pCachingStream->LockRegion(libOffset,cb,dwLockType);
}

STDMETHODIMP
CMyFilterStream::CopyTo(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
{
    return m_pCachingStream->CopyTo(pstm,cb,pcbRead,pcbWritten);
}
 
STDMETHODIMP
CMyFilterStream::Commit(DWORD grfCommitFlags)
{
    return m_pCachingStream->Commit(grfCommitFlags);
}

STDMETHODIMP
CMyFilterStream::Revert(void)
{
    return m_pCachingStream->Revert();
}

STDMETHODIMP
CMyFilterStream::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    return m_pCachingStream->UnlockRegion(libOffset,cb,dwLockType);
}

STDMETHODIMP
CMyFilterStream::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
    return m_pCachingStream->Stat(pstatstg, grfStatFlag);
}

STDMETHODIMP
CMyFilterStream::Clone(IStream **ppstm)
{
    return m_pCachingStream->Clone(ppstm);
}

STDMETHODIMP
CMyFilterStream::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
    return m_pCachingStream->Read(pv,cb,pcbRead);
}

/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | CMyFilterStream::Write | Filtering streams implementation of Write
 *  
 *  @parm   const void * | pv |
 *          Pointer to the memory buffer.
 * 
 *  @parm   ULONG | cb | 
 *          Specifies the number of bytes of data to write from the stream object.
 * 
 *  @parm   ULONG | pcbWritten | 
 *          Pointer to a ULONG variable that receives the actual number of bytes written from the stream object.
 *
 *  @comm
 *  Write simply writes unfiltered data from the driver into its internal caching stream.
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXX   | 
 *              The function failed 
 * 
 *****************************************************************************/
STDMETHODIMP
CMyFilterStream::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
    return m_pCachingStream->Write(pv, cb, pcbWritten);
}

///
///  Constructor
///
CImageFilter::CImageFilter(
    VOID) : m_pWiaItem(NULL), m_pAppWiaTransferCallback(NULL), m_nRefCount(0), m_pCurrentStream(NULL)
{
    //
    // Nothing
    //
}

///
///  Destructor
///
CImageFilter::~CImageFilter(
    VOID)
{
    if (m_pWiaItem)
    {
        m_pWiaItem->Release();
        m_pWiaItem = NULL;
    }

    if (m_pAppWiaTransferCallback)
    {
        m_pAppWiaTransferCallback->Release();
        m_pAppWiaTransferCallback = NULL;
    }
}

///
///  QueryInterface
///
STDMETHODIMP
CImageFilter::QueryInterface(const IID& iid_requested, void** ppInterfaceOut)
{
    HRESULT hr = S_OK;

    hr = ppInterfaceOut ? S_OK : E_POINTER;

    if (SUCCEEDED(hr))
    {
        *ppInterfaceOut = NULL;
    }

    //
    //  We support IID_IUnknown, IID_IWiaImageFilter and IID_IWiaTransferCallback
    //
    if (SUCCEEDED(hr))
    {
        if (IID_IUnknown == iid_requested) 
        {
            *ppInterfaceOut = static_cast<IWiaImageFilter*>(this);
        }
        else if (IID_IWiaImageFilter == iid_requested) 
        {
            *ppInterfaceOut = static_cast<IWiaImageFilter*>(this);
        }
        else if (IID_IWiaTransferCallback == iid_requested) 
        {
            *ppInterfaceOut = static_cast<IWiaTransferCallback*>(this);
        }
        else
        {
            hr = E_NOINTERFACE;
        }
    }

    if (SUCCEEDED(hr))
    {
        reinterpret_cast<IUnknown*>(*ppInterfaceOut)->AddRef();
    }

    return hr;
}

///
///  AddRef
///
STDMETHODIMP_(ULONG)
CImageFilter::AddRef(void)
{
    if (m_nRefCount == 0)
    {
        LockModule();
    }

    return InterlockedIncrement(&m_nRefCount);
}

///
///  Release
///
STDMETHODIMP_(ULONG)
CImageFilter::Release(void)
{
    ULONG nRetval = InterlockedDecrement(&m_nRefCount);

    if (0 == nRetval) 
    {
        delete this;
        UnlockModule();
    }

    return nRetval;
}

/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | CImageFilter::InitializeFilter | Initializes image processing filter
 *  
 *  @parm   IWiaItem2 | pWiaItem |
 *          The WIA item we are doing the download for. This will actually be the parent item
 *          for some of the item we acquire the image for. See implementation of GetNextStream
 *          for more details. 
 * 
 *  @parm   IWiaTransferCallback | pWiaTransferCallback | 
 *          Application's callback function
 * 
 *  @comm
 *  Initializes image processing filter. Stores references to applications callback interface
 *  and IWiaItem2
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXX   | 
 *              The function failed 
 * 
 *****************************************************************************/
STDMETHODIMP
CImageFilter::InitializeFilter(
        IN  IWiaItem2               *pWiaItem,
        IN  IWiaTransferCallback    *pWiaTransferCallback)
{
    HRESULT     hr = S_OK;

    hr = (pWiaItem && pWiaTransferCallback) ? S_OK : E_INVALIDARG;

    //
    // InitializeFilter should only be called once ... but we still Release
    // any resources we might reference
    //
    if (SUCCEEDED(hr))
    {
        if (m_pWiaItem)
        {
            m_pWiaItem->Release();
            m_pWiaItem = NULL;
        }
    
        if (m_pAppWiaTransferCallback)
        {
            m_pAppWiaTransferCallback->Release();
            m_pAppWiaTransferCallback = NULL;
        }
    }

    if (SUCCEEDED(hr))
    {
        m_pWiaItem = pWiaItem;
        m_pWiaItem->AddRef();

        m_pAppWiaTransferCallback = pWiaTransferCallback;
        m_pAppWiaTransferCallback->AddRef();
    }

    return hr;
}

/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | CImageFilter::FilterPreviewImage | FilterPreviewImage implementation
 * 
  
 *  @parm   IWiaItem2 | pWiaChildItem |
 *          pWiaChildItem2 is the item which the image process is to process.
 *          This item must be a child item of the item, m_pWiaItem, that was passed into InitializeFilter.
 * 
 *  @parm   RECT | InputImageExtents | 
 *          The coordinates (on the flatbed scanner) of the image that the preview component caches internally,
 *          which is also the image that is passed into the pInputStream parameter.
 *          We need this parameter since it is possible that the cached image (pInputStream) was not captured
 *          with XPOS=YPOS=0.
 * 
 *  @parm   IStream | pInputStream | 
 *          Unfiltered image that is stored by WIA Preview Component.
 *
 *  @comm
 *  FilterPreviewImage is called by the preview component, when an application calls UpdatePreview.
 *  We simply read all the properties from pWiaChildItem that are required for us to do the filtering
 *  and then retrieve the application stream. The actual filtering is then performed in DoFiltering.
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXX   | 
 *              The function failed 
 * 
 *****************************************************************************/
STDMETHODIMP
CImageFilter::FilterPreviewImage(
    IN     IWiaItem2               *pWiaChildItem,
    IN     RECT                    InputImageExtents,
    IN     IStream                 *pInputStream)
{
    IStream     *pAppStream = NULL;
    BSTR        bstrItemName        = NULL;
    BSTR        bstrFullItemName    = NULL;
    GUID        guidItemCategory    = {0};
    LONG        xpos = 0, ypos = 0, width = 0, height = 0;
    LONG        lBrightness = 0;
    LONG        lContrast = 0;
    LONG        lDeskewX = 0;
    LONG        lDeskewY = 0;
    LONG        lRotation = PORTRAIT;
    
    HRESULT     hr;

    hr = m_pAppWiaTransferCallback ? S_OK : E_UNEXPECTED;

    //
    // Read all properties we need
    //
    if (SUCCEEDED(hr))
    {
        CWiaItem    *pWiaItemWrapper = new CWiaItem();

        hr = pWiaItemWrapper ? S_OK : E_OUTOFMEMORY;

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->SetIWiaItem(pWiaChildItem);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyGUID(WIA_IPA_ITEM_CATEGORY, &guidItemCategory);

            if (SUCCEEDED(hr) && (guidItemCategory == WIA_CATEGORY_FINISHED_FILE))
            {
                //
                // We should never get here for storage items!
                //
                hr = E_INVALIDARG;
            }
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_XPOS, &xpos);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_YPOS, &ypos);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_XEXTENT, &width);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_YEXTENT, &height);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyBSTR(WIA_IPA_ITEM_NAME, &bstrItemName);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyBSTR(WIA_IPA_FULL_ITEM_NAME, &bstrFullItemName);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_BRIGHTNESS, &lBrightness);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_CONTRAST, &lContrast);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_ROTATION, &lRotation);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_DESKEW_X, &lDeskewX);
        }

        if (SUCCEEDED(hr))
        {
            hr = pWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_DESKEW_Y, &lDeskewY);
        }

        if (pWiaItemWrapper)
        {
            delete pWiaItemWrapper;
        }
    }

    //
    // If the upper left corner of the passed image does not correspond to (0,0)
    // on the flatbed we have to adjust xpos and ypos accordingly in order for us
    // to "cut out" the correct region represented by pWiaChildItem
    //
    if (SUCCEEDED(hr))
    {
        xpos = xpos - InputImageExtents.left;
        ypos = ypos - InputImageExtents.top;
    }

    //
    // Now get the application stream and write to it
    //
    if (SUCCEEDED(hr))
    {
        hr = m_pAppWiaTransferCallback->GetNextStream(0, bstrItemName, bstrFullItemName, &pAppStream);  
    }

    //
    // Do "actual" filtering
    //
    if (SUCCEEDED(hr))
    {
        hr = DoFiltering(lBrightness,
                         lContrast,
                         lRotation,
                         lDeskewX,
                         lDeskewY,
                         pInputStream,
                         pAppStream,
                         xpos,
                         ypos,
                         width,
                         height
                         );

    }

    if (pAppStream)
    {
        pAppStream->Release();
    }
    
    return hr;
}

/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | CImageFilter::TransferCallback | TransferCallback implementation
 * 
  
 *  @parm   LONG | lFlags |
 *          Flags
 * 
 *  @parm   WiaTransferParams | pWiaTransferParams | 
 *          Contains transfer status
 * 
 *  @comm
 *  TransferCallback delegates to the application's callback. It changes the
 *  number of bytes written since we always cache all the data before writing to
 *  the application's stream. We do however not change the percentage since this
 *  represents percentage of total transfer time (a "real" implementation probably
 *  would take the filtering into account here).
 *  We do not write the data to the application's stream until when we receive
 *  a WIA_TRANSFER_MSG_END_OF_STREAM message. 
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXX   | 
 *              The function failed 
 * 
 *****************************************************************************/
STDMETHODIMP
CImageFilter::TransferCallback(
    IN  LONG                lFlags,
    IN  WiaTransferParams   *pWiaTransferParams)
{
    HRESULT     hr;

    hr = m_pAppWiaTransferCallback ? S_OK : E_UNEXPECTED;

    if (SUCCEEDED(hr))
    {
        //
        // Note the percent reflects the amount of scanning the driver reports
        // whereas the "BytesWritten" member is the actual number of bytes
        // that we have sent to the application stream.
        //
        if (m_pCurrentStream && (pWiaTransferParams->lMessage == WIA_TRANSFER_MSG_END_OF_STREAM))
        {
            hr = m_pCurrentStream->Flush();
        }
        else if (m_pCurrentStream && (pWiaTransferParams->lMessage == WIA_TRANSFER_MSG_STATUS))
        {
            pWiaTransferParams->ulBytesWrittenToCurrentStream = m_pCurrentStream->m_cBytesWritten;
        }

        hr = m_pAppWiaTransferCallback->TransferCallback(lFlags,pWiaTransferParams);

        if (m_pCurrentStream && (pWiaTransferParams->lMessage == WIA_TRANSFER_MSG_END_OF_STREAM))
        {
            m_pCurrentStream->Release();
            m_pCurrentStream = NULL;
        }
    }

    return hr;
}
    
/*****************************************************************************
 *  
 *  @doc INTERNAL
 *  
 *  @func STDMETHODIMP | CImageFilter::GetNextStream | Implementation of GetNextStream
 *  
 *  @parm   LONG | lFlags |
 *          Flags
 * 
 *  @parm   BSTR | bstrItemName | 
 *          Name of item
 *  
 *  @parm   BSTR | bstrFullItemName | 
 *          Full name of item
 *
 *  @parm   IStream | ppDestination | 
 *          Upon successful return this will contain the filtering stream
 *
 *  @comm
 *  GetNextStream creates a filtering stream. Since the item represented by
 *  bstrFullItemName may be a child item of the item passed into InitializeFilter
 *  we have to call FindItemByName to retrieve the actual item.
 *
 *  @rvalue S_OK    | 
 *              The function succeeded.
 *  @rvalue E_XXXXXX    | 
 *              Failure
 * 
 *****************************************************************************/
STDMETHODIMP
CImageFilter::GetNextStream(
    IN  LONG                lFlags,
    IN  BSTR                bstrItemName,
    IN  BSTR                bstrFullItemName,
    OUT IStream             **ppDestination)
{
    HRESULT     hr;
    IStream     *pAppStream      = NULL;
    IWiaItem2   *pCurrentWiaItem = NULL;
    BOOL        bStorageItem     = FALSE;
    LONG        lBrightness      = 0;
    LONG        lContrast        = 0;
    LONG        lDeskewX         = 0;
    LONG        lDeskewY         = 0;
    LONG        lRotation        = PORTRAIT;
    LONG        lXExtent         = 0;
    LONG        lYExtent         = 0;
    LONG        lBitDepth        = 0;

    hr = m_pAppWiaTransferCallback ? S_OK : E_UNEXPECTED;

    if (m_pCurrentStream)
    {
        m_pCurrentStream->Release();
        m_pCurrentStream = NULL;
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pAppWiaTransferCallback->GetNextStream(lFlags, bstrItemName, bstrFullItemName, &pAppStream);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pWiaItem->FindItemByName(0, bstrFullItemName, &pCurrentWiaItem);
    }

    //
    // Here we read all properties from pCurrentWiaItem that we need in order to
    // do the the filtering - in this specific case only brightness.
    //
    if (SUCCEEDED(hr))
    {
        CWiaItem    *pIWiaItemWrapper = NULL;

        pIWiaItemWrapper = new CWiaItem();

        hr = pIWiaItemWrapper ? S_OK : E_OUTOFMEMORY;

        if (SUCCEEDED(hr))
        {
            hr = pIWiaItemWrapper->SetIWiaItem(pCurrentWiaItem);
        }

        if (SUCCEEDED(hr))
        {
            GUID        guidItemCategory = {0};
            
            hr = pIWiaItemWrapper->ReadRequiredPropertyGUID(WIA_IPA_ITEM_CATEGORY,&guidItemCategory);

            bStorageItem = (guidItemCategory == WIA_CATEGORY_FINISHED_FILE);
        }

        if (!bStorageItem)
        {
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_BRIGHTNESS,&lBrightness);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_CONTRAST,&lContrast);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_ROTATION, &lRotation);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_DESKEW_X, &lDeskewX);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_DESKEW_Y, &lDeskewY);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_XEXTENT, &lXExtent);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPS_YEXTENT, &lYExtent);
            }
    
            if (SUCCEEDED(hr))
            {
                hr = pIWiaItemWrapper->ReadRequiredPropertyLong(WIA_IPA_DEPTH, &lBitDepth);
            }
        }

        if (pIWiaItemWrapper)
        {
            delete pIWiaItemWrapper;
        }
    }

    if (SUCCEEDED(hr))
    {
        if (!bStorageItem)
        {
            //
            // We could easily improve the performace by creating a separate filtering stream
            // which simply delegates all calls directly to the application's stream in case
            // Rotation, DeskewX, DeskewY, Brightness and Contrast are all set to 0.
            //
            m_pCurrentStream = new CMyFilterStream();
    
            if (m_pCurrentStream)      
            {
                hr = m_pCurrentStream->Initialize(pAppStream,
                                                  lBrightness,
                                                  lContrast,
                                                  lRotation,
                                                  lDeskewX,
                                                  lDeskewY,
                                                  lXExtent,
                                                  lYExtent,
                                                  lBitDepth);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }
        else
        {
            (*ppDestination) = pAppStream;
            (*ppDestination)->AddRef();
        }
    }

    if (SUCCEEDED(hr) && m_pCurrentStream)
    {
        hr = m_pCurrentStream->QueryInterface(IID_IStream, (void**)ppDestination);
    }

    if (pAppStream)
    {
        pAppStream->Release();
    }

    if (pCurrentWiaItem)
    {
        pCurrentWiaItem->Release();
    }
    
    return hr;
}

/*****************************************************************************
 *
 *  Class Object
 *
 *******************************************************************************/
class CFilterClass : public IClassFactory
{
public:

    STDMETHODIMP
    QueryInterface(const IID& iid_requested, void** ppInterfaceOut)
    {
        HRESULT hr = S_OK;

        hr = ppInterfaceOut ? S_OK : E_POINTER;

        if (SUCCEEDED(hr))
        {
            *ppInterfaceOut = NULL;
        }
    
        //
        //  We support IID_IUnknown and IID_IClassFactory
        //
        if (SUCCEEDED(hr))
        {
            if (IID_IUnknown == iid_requested) 
            {
                *ppInterfaceOut = static_cast<IUnknown*>(this);
            }
            else if (IID_IClassFactory == iid_requested) 
            {
                *ppInterfaceOut = static_cast<IClassFactory*>(this);
            }
            else
            {
                hr = E_NOINTERFACE;
            }
        }

        if (SUCCEEDED(hr))
        {
            reinterpret_cast<IUnknown*>(*ppInterfaceOut)->AddRef();
        }
            
        return hr;
    }

    STDMETHODIMP_(ULONG)
    AddRef(void)
    {
        LockModule();
        return 2;
    }
    
    STDMETHODIMP_(ULONG)
    Release(void)
    {
        UnlockModule();
        return 1;
    }

    STDMETHODIMP
    CreateInstance(IUnknown *pUnkOuter,
                   REFIID   riid,
                   void     **ppv)
    {
        CImageFilter   *pImageFilter = NULL;
        HRESULT     hr;

        hr = ppv ? S_OK : E_POINTER;

        if (SUCCEEDED(hr))
        {
            *ppv = 0;
        }

        if (SUCCEEDED(hr))
        {
            if (pUnkOuter)
            {
                hr = CLASS_E_NOAGGREGATION;
            }
        }

        if (SUCCEEDED(hr))
        {
            pImageFilter = new CImageFilter();

            hr = pImageFilter ? S_OK : E_OUTOFMEMORY;
        }

        if (SUCCEEDED(hr))
        {
            pImageFilter->AddRef();
            hr = pImageFilter->QueryInterface(riid, ppv);
            pImageFilter->Release();
        }

        return hr;
    }

    STDMETHODIMP
    LockServer(BOOL bLock)
    {
        if (bLock)
        {
            LockModule();
        }
        else
        {
            UnlockModule();
        }

        return S_OK;
    }
};

STDAPI DllCanUnloadNow(void)
{
    return (g_cLocks == 0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID   rclsid,
                         REFIID     riid,
                         void       **ppv)
{
    static  CFilterClass s_FilterClass;
    
    if (rclsid == CLSID_WiaImageFilter)
    {
        return s_FilterClass.QueryInterface(riid, ppv);
    }

    *ppv = 0;

    return CLASS_E_CLASSNOTAVAILABLE;
}

//
// Registered in driver INF file - what about un-regestering?
//
STDAPI DllUnregisterServer()
{
    return S_OK;
}

STDAPI DllRegisterServer()
{
    return S_OK;
}
