/**************************************************************************
*
*  Copyright (c) 2003  Microsoft Corporation
*
*  Title: wiahelpers.h
*
*  Description: This contains the WIA driver class helper functions.
*
***************************************************************************/
#pragma once

#define NO_FIXED_FRAME 0xFFFFFFFF

typedef struct _FILM_FRAME {
    LONG    XPOS;
    LONG    YPOS;
    LONG    XEXTENT;
    LONG    YEXTENT;
} FILM_FRAME;

HRESULT MakeFullItemName(
    IWiaDrvItem *pParent,
    BSTR        bstrItemName,
    BSTR        *pbstrFullItemName);

HRESULT CreateWIAChildItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent,
    LONG        lItemFlags,
    GUID        guidItemCategory,
    IWiaDrvItem **ppChild       = NULL,
    const WCHAR *wszStoragePath = NULL);

HRESULT CreateWIAFlatbedItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent);

HRESULT CreateWIAFeederItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent);

HRESULT CreateWIAFilmItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent);

HRESULT CreateWIAStorageItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent,
    const WCHAR *wszStoragePath);

HRESULT InitializeRootItemProperties(
    BYTE        *pWiasContext);

HRESULT InitializeWIAItemProperties(
    BYTE        *pWiasContext,
    HINSTANCE   hInstance,
    UINT        uiResourceID,
    BOOL        bRootItem);

HRESULT InitializeWIAStorageItemProperties(
    BYTE        *pWiasContext,
    BOOL        bRootItem);

HRESULT wiasGetDriverItemPrivateContext(
    BYTE *pWiasContext,
    BYTE **ppWiaDriverItemContext);

HRESULT wiasGetAppItemParent(
    BYTE *pWiasContext,
    BYTE **ppWiasContext);

LONG ConvertTo1000thsOfAnInch(
    LONG lPixelSize,
    LONG lResolution);

HRESULT GetBitmapHeaderFromBitmapData(
    Gdiplus::BitmapData *pGDIPlusBitmapData,
    BITMAPINFOHEADER    *pBitmapInfoHeader);

HRESULT GetSelectionAreaRect(
    BYTE            *pWiasContext,
    Gdiplus::Rect   *pRect);

HRESULT LockSelectionAreaOnBitmap(
    BYTE                    *pWiasContext,
    Gdiplus::Bitmap         *pBitmap,
    Gdiplus::BitmapData     *pBitmapData,
    BITMAPINFOHEADER        *pbmih,
    BYTE                    **ppBitmapBits);

void UnlockSelectionAreaOnBitmap(
    Gdiplus::Bitmap         *pBitmap,
    Gdiplus::BitmapData     *pBitmapData);

HRESULT GetTransferCallback(
    PMINIDRV_TRANSFER_CONTEXT       pmdtc,
    IWiaMiniDrvTransferCallback     **ppIWiaMiniDrvTransferCallback);

HRESULT AllocateTransferBuffer(
    BYTE                    *pWiasContext,
    BYTE                    **ppBuffer,
    ULONG                    *pulBufferSize);

void FreeTransferBuffer(
    BYTE                    *pBuffer);

HRESULT GetFileExtensionFromPath(
    BSTR    bstrFullPath,
    BSTR    *pbstrExtension);

bool IsProgrammableItem(
    BYTE    *pWiasContext);

void QueueWIAEvent(
    BYTE        *pWiasContext,
    const GUID  &guidWIAEvent);
