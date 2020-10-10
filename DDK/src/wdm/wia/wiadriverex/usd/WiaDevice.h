/*****************************************************************************
 *
 *  WiaDevice.h
 *
 *  Copyright (c) 2003 Microsoft Corporation.  All Rights Reserved.
 *
 *  DESCRIPTION:
 *
 *  This class simulates a "real" device from which we can acquire image data and upload
 *  image data. It uses GDI+ internally to create the image. 
 *  
 *******************************************************************************/

#pragma once

using namespace Gdiplus;

extern HINSTANCE g_hInst;

class WiaDevice
{
public:
    WiaDevice() :
        m_dwTotalBytes(0),
        m_dwTotalBytesRead(0),
        m_dwLinesRead(0),
        m_pBitmap(NULL),
        m_pBitmapData(NULL),
        m_pBitmapBits(NULL),
        m_ulHeaderSize(NULL)
    {
        memset(&m_bmfh, 0, sizeof(m_bmfh));
        memset(&m_bmih, 0, sizeof(m_bmih));
    };

    virtual ~WiaDevice()
    {
        UninitializeForDownload();
    };

    HRESULT InitializeForDownload(
        BYTE        *pWiasContext,
        HINSTANCE   hInstance,
        UINT        uiBitmapResourceID)
    {
        HRESULT hr = E_INVALIDARG;
        if((pWiasContext)&&(hInstance))
        {
            m_pBitmap = new Bitmap(hInstance,MAKEINTRESOURCE(uiBitmapResourceID));
            if(m_pBitmap)
            {
                m_pBitmapData = new BitmapData;
                if(m_pBitmapData)
                {
                    hr = LockSelectionAreaOnBitmap(pWiasContext, m_pBitmap, m_pBitmapData, &m_bmih, &m_pBitmapBits);
                    if(SUCCEEDED(hr))
                    {
                        this->m_ulHeaderSize    = sizeof(m_bmfh) + sizeof(m_bmih);
                        this->m_bmfh.bfType     = ((WORD) ('M' << 8) | 'B');
                        this->m_bmfh.bfOffBits  = this->m_ulHeaderSize;
                        this->m_bmfh.bfSize     = this->m_bmfh.bfOffBits + this->m_bmih.biSizeImage;

                        this->m_dwTotalBytes        = this->m_bmfh.bfSize;
                        this->m_dwTotalBytesRead    = 0;
                        this->m_dwLinesRead         = 0;
                    }
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                    WIAS_ERROR((g_hInst, "Failed to allocate memory for GDI+ bitmap data object, hr = 0x%lx",hr));
                }
            }
            else
            {
                hr = E_OUTOFMEMORY;
                WIAS_ERROR((g_hInst, "Failed to allocate memory for GDI+ bitmap object, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
        }
        return hr;
    }

    void UninitializeForDownload()
    {
        if (m_pBitmap && m_pBitmapData)
        {
            UnlockSelectionAreaOnBitmap(m_pBitmap, m_pBitmapData);
        }
        m_pBitmapBits = NULL;
        SAFE_DELETE(m_pBitmapData);
        SAFE_DELETE(m_pBitmap);
    }

    HRESULT GetNextBand(BYTE    *pBuffer,
                        ULONG   ulBufferSize,
                        ULONG   *pulBytesRead,
                        LONG    *plPercentComplete)
    {
        HRESULT hr = S_OK;

        if (pBuffer && pulBytesRead && plPercentComplete && (ulBufferSize > this->m_ulHeaderSize))
        {
            //
            // iScanline contains the number of bytes to copy from each scanline
            //
            INT iScanline = ((m_pBitmapData->Width * 3) + 3) & ~3;

            *pulBytesRead       = 0;
            *plPercentComplete  = 0;

            if (this->m_dwTotalBytesRead < this->m_dwTotalBytes)
            {
                //  Check whether we should send the bitmap header or the data.
                //  The header is always sent first.
                if (this->m_dwTotalBytesRead == 0)
                {
                    // Read the header.
                    memcpy(pBuffer,&this->m_bmfh, sizeof(this->m_bmfh));
                    memcpy(pBuffer + sizeof(this->m_bmfh),&this->m_bmih, sizeof(this->m_bmih));
                    *pulBytesRead               = this->m_ulHeaderSize;
                    hr                          = S_OK;
                }
                else
                {
                    // Read a data band
                    //  First calculate number of bytes in whole scan lines.
                    DWORD dwNumLineBytesInBuffer    = (ulBufferSize - (ulBufferSize % iScanline));
                    DWORD dwNumBytesLeftToRead      = (this->m_dwTotalBytes - this->m_dwTotalBytesRead);
                    //  Set how many bytes we are going to read.  This is either the maxiumun
                    //  nunmber of scan lines that will fit into the buffer, or it's the number
                    //  of bytes left in the last chunk.
                    if(dwNumBytesLeftToRead < dwNumLineBytesInBuffer)
                    {
                        dwNumLineBytesInBuffer = dwNumBytesLeftToRead;
                    }
                    //  Position buffer pointer to correct data location for this band.  We are copying 
                    //  in reverse scanline order so that the bitmap becomes topdown (it is currently
                    //  upside-down in the source buffer).
                    BYTE *pBits = m_pBitmapBits + (m_pBitmapData->Height * m_pBitmapData->Stride);
                    pBits -= (m_pBitmapData->Stride * (1 + m_dwLinesRead));

                    DWORD dwDestOffset  = 0;
                    for (BYTE *pCurLine = pBits; dwDestOffset < dwNumLineBytesInBuffer; pCurLine -= m_pBitmapData->Stride, m_dwLinesRead++)
                    {
                        memcpy(pBuffer + dwDestOffset, pCurLine, iScanline);
                        dwDestOffset   += iScanline;
                    }
                    *pulBytesRead = dwNumLineBytesInBuffer;
                    hr = S_OK;
                }
                this->m_dwTotalBytesRead    += *pulBytesRead;
                *plPercentComplete          = (LONG)((((float)this->m_dwTotalBytesRead/(float)this->m_dwTotalBytes)) * 100.0f);
            }
            else
            {
                // We have no more data
                hr = WIA_STATUS_END_OF_MEDIA;
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Invalid parameters"));
            hr = E_INVALIDARG;
        }
        return hr;
    }

    HRESULT Upload(BSTR                         bstrItemName,
                   ULONG                        ulTotalBytes,
                   IStream                      *pSourceStream,
                   IWiaMiniDrvTransferCallback  *pTransferCallback,
                   WiaTransferParams            *pParams,
                   const CBasicStringWide      &cswStoragePath)
    {
        // TBD: don't write to C:\TEMP\DATATRANSFERTEST, use actual storage item.
        HRESULT hr = S_OK;
        IStream             *pDestination   = NULL;
        CBasicStringWide   cswFileName     = cswStoragePath;
        cswFileName += L"\\";
        cswFileName += bstrItemName;

        // create stream on a file in the temporary directory (filename is bstrItemName)
        hr  = SHCreateStreamOnFile(cswFileName.String(),STGM_WRITE|STGM_CREATE,&pDestination);
        if(SUCCEEDED(hr))
        {
            // loop while reading data is availble from source stream
            BYTE *pBuffer = (BYTE*)CoTaskMemAlloc(DEFAULT_BUFFER_SIZE);
            if(pBuffer)
            {
                ULONG ulNumBytesRead        = 0;
                ULONG ulNumBytesWritten     = 0;
                ULONG ulTotalBytesWritten   = 0;
                while(SUCCEEDED(pSourceStream->Read(pBuffer,DEFAULT_BUFFER_SIZE,&ulNumBytesRead)) && ulNumBytesRead)
                {
                    //      write the chunk
                    hr = pDestination->Write(pBuffer,ulNumBytesRead,&ulNumBytesWritten);
                    if(FAILED(hr))
                    {
                        WIAS_ERROR((g_hInst, "Failed to write upload data to destination stream, hr = 0x%lx",hr));
                        break;
                    }

                    ulTotalBytesWritten += ulNumBytesWritten;

                    LONG lPercentComplete = -1;
                    if(ulTotalBytes > 0)
                    {
                        lPercentComplete = (LONG)((((float)ulTotalBytesWritten/(float)ulTotalBytes)) * 100.0f);
                    }
                    // make callback

                    pParams->lMessage                       = WIA_TRANSFER_MSG_STATUS;
                    pParams->lPercentComplete               = lPercentComplete;
                    pParams->ulBytesWrittenToCurrentStream  = ulTotalBytesWritten;

                    hr = pTransferCallback->SendMessage(0,pParams);
                    if(SUCCEEDED(hr))
                    {
                        if(hr == S_FALSE)
                        {
                            WIAS_TRACE((g_hInst,"Application cancelled upload"));
                            break;
                        }
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to send status message to application. Upload aborted, hr = 0x%lx",hr));
                    }
                }

                if(ulTotalBytesWritten == 0)
                {
                    hr = E_FAIL;
                    WIAS_ERROR((g_hInst, "No data was written during upload, hr = 0x%lx",hr));
                }

                CoTaskMemFree(pBuffer);
                pBuffer = NULL;
            }
            else
            {
                hr = E_OUTOFMEMORY;
                WIAS_ERROR((g_hInst, "Failed to allocate buffer for upload, hr = 0x%lx",hr));
            }

            // TBD: decide on exact behavior for notifying clients.

            pDestination->Release();
            pDestination = NULL;
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to create destination stream on file %ws, hr = 0x%lx",cswFileName.String(),hr));
        }
        return hr;
    }

private:
    ULONG               m_ulHeaderSize;
    BITMAPFILEHEADER    m_bmfh;
    BITMAPINFOHEADER    m_bmih;
    DWORD               m_dwTotalBytes;
    DWORD               m_dwTotalBytesRead;
    DWORD               m_dwLinesRead;
    Bitmap              *m_pBitmap;
    BitmapData          *m_pBitmapData;
    BYTE                *m_pBitmapBits;
};

