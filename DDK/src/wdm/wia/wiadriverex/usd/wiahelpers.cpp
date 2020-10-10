/**************************************************************************
*
*  Copyright (c) 2003  Microsoft Corporation
*
*  Title: wiahelpers.cpp
*
*  Description: This file contains a number of helper functions
*               for child item creation etc. 
*
***************************************************************************/
#include "stdafx.h"
#include <strsafe.h>

static FILM_FRAME g_FilmFrames[] = { { 36, 27,  222, 167 },
                                     { 36, 221, 222, 167 },
                                     { 37, 418, 222, 167 },
                                     { 37, 614, 221, 172 } };


/**
 * This function creates a full WIA item name
 * from a given WIA item name.
 *
 * The new full item name is created by concatinating
 * the WIA item name with the parent's full item name.
 *
 * (e.g. 0000\Root + MyItem = 0000\Root\MyItem)
 *
 * @param pParent IWiaDrvItem interface of the parent WIA driver item
 * @param bstrItemName
 *                Name of the WIA item
 * @param pbstrFullItemName
 *                Returned full item name.  This parameter
 *                cannot be NULL.
 * @return S_OK - if successful
 *         E_XXXXXXXX - failure result
 */
HRESULT MakeFullItemName(
    IWiaDrvItem *pParent,
    BSTR        bstrItemName,
    BSTR        *pbstrFullItemName)
{
    HRESULT hr = S_OK;
    if((pParent)&&(bstrItemName)&&(pbstrFullItemName))
    {
        BSTR bstrParentFullItemName = NULL;
        hr = pParent->GetFullItemName(&bstrParentFullItemName);
        if(SUCCEEDED(hr))
        {
            CBasicStringWide cswFullItemName;
            cswFullItemName.Format(TEXT("%ws\\%ws"),bstrParentFullItemName,bstrItemName);
            *pbstrFullItemName = SysAllocString(cswFullItemName.String());
            if(*pbstrFullItemName)
            {
                hr = S_OK;
            }
            else
            {
                hr = E_OUTOFMEMORY;
                WIAS_ERROR((g_hInst, "Failed to allocate memory for BSTR full item name, hr = 0x%lx",hr));
            }
            SysFreeString(bstrParentFullItemName);
            bstrParentFullItemName = NULL;
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get full item name from parent IWiaDrvItem, hr = 0x%lx",hr));
        }
    }
    else
    {
        hr = E_INVALIDARG;
        WIAS_ERROR((g_hInst, "Invalid parameters were passed, hr = 0x%lx",hr));
    }
    return hr;
}

/**
 * This function creates a WIA child item
 *
 * @param wszItemName
 *                   Item name
 * @param pIWiaMiniDrv
 *                   WIA minidriver interface
 * @param pParent Parent's WIA driver item interface
 * @param lItemFlags Item flags
 * @param guidItemCategory
 *                   Item category
 * @param ppChild Pointer to the newly created child item
 * @param wszStoragePath
 *                   Storage data path
 * @return
 */
HRESULT CreateWIAChildItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent,
    LONG        lItemFlags,
    GUID        guidItemCategory,
    IWiaDrvItem **ppChild,
    const WCHAR *wszStoragePath)
{
    HRESULT hr = E_INVALIDARG;
    if((wszItemName)&&(pIWiaMiniDrv)&&(pParent))
    {
        BSTR        bstrItemName        = SysAllocString(wszItemName);
        BSTR        bstrFullItemName    = NULL;
        IWiaDrvItem *pIWiaDrvItem       = NULL;

        hr = MakeFullItemName(pParent,bstrItemName,&bstrFullItemName);
        if(SUCCEEDED(hr))
        {
            WIA_DRIVER_ITEM_CONTEXT *pWiaDriverItemContext = NULL;
            hr = wiasCreateDrvItem(lItemFlags,
                                   bstrItemName,
                                   bstrFullItemName,
                                   pIWiaMiniDrv,
                                   sizeof(WIA_DRIVER_ITEM_CONTEXT),
                                   (BYTE **)&pWiaDriverItemContext,
                                   &pIWiaDrvItem);
            if(SUCCEEDED(hr))
            {
                pWiaDriverItemContext->guidItemCategory = guidItemCategory;
                if(wszStoragePath)
                {
                    pWiaDriverItemContext->bstrStorageDataPath = SysAllocString(wszStoragePath);
                    if(!pWiaDriverItemContext->bstrStorageDataPath)
                    {
                        hr = E_OUTOFMEMORY;
                        WIAS_ERROR((g_hInst, "Failed to allocate memory for BSTR storage item path, hr = 0x%lx",hr));
                    }
                }

                if(SUCCEEDED(hr))
                {
                    hr = pIWiaDrvItem->AddItemToFolder(pParent);
                    if(FAILED(hr))
                    {
                        WIAS_ERROR((g_hInst, "Failed to add the new WIA item (%ws) to the specified parent item, hr = 0x%lx",bstrFullItemName,hr));
                        pIWiaDrvItem->Release();
                        pIWiaDrvItem = NULL;
                    }

                    //
                    // If a child iterface pointer parameter was specified, then the caller
                    // expects to have the newly created child interface pointer returned to
                    // them. (do not release the newly created item, in this case)
                    //

                    if(ppChild)
                    {
                        *ppChild        = pIWiaDrvItem;
                        pIWiaDrvItem    = NULL;
                    }
                    else if (pIWiaDrvItem)
                    {
                        //
                        // The newly created child has been added to the tree, and is no longer
                        // needed.  Release it.
                        //

                        pIWiaDrvItem->Release();
                        pIWiaDrvItem = NULL;
                    }
                }
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to create the new WIA driver item, hr = 0x%lx",hr));
            }

            SysFreeString(bstrItemName);
            bstrItemName = NULL;
            SysFreeString(bstrFullItemName);
            bstrFullItemName = NULL;
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to create the new WIA item's full item name, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function creates a WIA flatbed item.  WIA
 * flatbed items will automatically have the
 * WIA category setting of WIA_CATEGORY_FLATBED.
 *
 * @param wszItemName
 *                   Item name
 * @param pIWiaMiniDrv
 *                   WIA minidriver interface
 * @param pParent Parent's WIA driver item interface
 * @return
 */
HRESULT CreateWIAFlatbedItem(
                            LPOLESTR    wszItemName,
                            IWiaMiniDrv *pIWiaMiniDrv,
                            IWiaDrvItem *pParent)
{
    LONG lItemFlags  = WiaItemTypeImage | WiaItemTypeTransfer | WiaItemTypeFile | WiaItemTypeProgrammableDataSource;
    return CreateWIAChildItem(wszItemName,pIWiaMiniDrv,pParent,lItemFlags, WIA_CATEGORY_FLATBED,NULL);
}

/**
 * This function creates a WIA feeder item.  WIA
 * feeder items will automatically have the
 * WIA category setting of WIA_CATEGORY_FEEDER.
 *
 * @param wszItemName
 *                   Item name
 * @param pIWiaMiniDrv
 *                   WIA minidriver interface
 * @param pParent Parent's WIA driver item interface
 * @return
 */
HRESULT CreateWIAFeederItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent)
{
    LONG lItemFlags  = WiaItemTypeImage | WiaItemTypeTransfer | WiaItemTypeFile | WiaItemTypeProgrammableDataSource;
    return CreateWIAChildItem(wszItemName,pIWiaMiniDrv,pParent,lItemFlags, WIA_CATEGORY_FEEDER,NULL);
}

/**
 * This function creates a WIA film item.  WIA
 * film items will automatically have the
 * WIA category setting of WIA_CATEGORY_FILM.
 *
 * @param wszItemName
 *                   Item name
 * @param pIWiaMiniDrv
 *                   WIA minidriver interface
 * @param pParent Parent's WIA driver item interface
 * @return
 */
HRESULT CreateWIAFilmItem(
    LPOLESTR    wszItemName,
    IWiaMiniDrv *pIWiaMiniDrv,
    IWiaDrvItem *pParent)
{
    LONG        lItemFlags  = WiaItemTypeImage | WiaItemTypeTransfer | WiaItemTypeFolder | WiaItemTypeProgrammableDataSource;
    IWiaDrvItem *pChild     = NULL;
    HRESULT hr = S_OK;
    hr = CreateWIAChildItem(wszItemName,pIWiaMiniDrv,pParent,lItemFlags, WIA_CATEGORY_FILM,&pChild);
    if(SUCCEEDED(hr))
    {
        if(pChild)
        {
            lItemFlags = WiaItemTypeImage | WiaItemTypeTransfer | WiaItemTypeFile | WiaItemTypeProgrammableDataSource;
            hr = CreateWIAChildItem(L"Frame1",pIWiaMiniDrv,pChild,lItemFlags, WIA_CATEGORY_FILM,NULL);
            if(SUCCEEDED(hr))
            {
                hr = CreateWIAChildItem(L"Frame2",pIWiaMiniDrv,pChild,lItemFlags, WIA_CATEGORY_FILM,NULL);
            }
            if(SUCCEEDED(hr))
            {
                hr = CreateWIAChildItem(L"Frame3",pIWiaMiniDrv,pChild,lItemFlags, WIA_CATEGORY_FILM,NULL);
            }
            if(SUCCEEDED(hr))
            {
                hr = CreateWIAChildItem(L"Frame4",pIWiaMiniDrv,pChild,lItemFlags, WIA_CATEGORY_FILM,NULL);
            }

            pChild->Release();
            pChild = NULL;
        }
    }
    return hr;
}

/**
 * This function creates a WIA storage item.  WIA
 * storage items will automatically have the
 * WIA category setting of WIA_CATEGORY_FINISHED_FILE.
 *
 * @param wszItemName
 *                   Item name
 * @param pIWiaMiniDrv
 *                   WIA minidriver interface
 * @param pParent Parent's WIA driver item interface
 * @return
 */
HRESULT CreateWIAStorageItem(
                            LPOLESTR    wszItemName,
                            IWiaMiniDrv *pIWiaMiniDrv,
                            IWiaDrvItem *pParent,
                            const WCHAR * wszStoragePath)
{
    LONG lItemFlags  = WiaItemTypeFolder | WiaItemTypeStorage;

    IWiaDrvItem *pChild = NULL;
    HRESULT     hr      = S_OK;
    hr = CreateWIAChildItem(wszItemName,pIWiaMiniDrv,pParent,lItemFlags, WIA_CATEGORY_FINISHED_FILE,&pChild);
    if(SUCCEEDED(hr))
    {
        if(pChild)
        {
            lItemFlags = WiaItemTypeTransfer | WiaItemTypeFile;

            //TBD: This function only searches the first level for
            //     content.  It ignores any directories found.

            CBasicStringWide cswSearchPath = wszStoragePath;
            cswSearchPath += L"\\*.*";

            WIN32_FIND_DATA FindData = {0};
            HANDLE hFindFile = FindFirstFile(cswSearchPath.String(),&FindData);
            if(hFindFile)
            {
                do
                {
                    if(!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    {
                        CBasicStringWide cswFileDataPath   = wszStoragePath;
                        cswFileDataPath                     += L"\\";
                        cswFileDataPath                     += FindData.cFileName;
                        hr = CreateWIAChildItem(FindData.cFileName,
                                                pIWiaMiniDrv,
                                                pChild,
                                                lItemFlags,
                                                WIA_CATEGORY_FINISHED_FILE,
                                                NULL,
                                                cswFileDataPath.String());
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to create WIA child storage item, hr = 0x%lx",hr));
                            break;
                        }
                    }

                } while(FindNextFile(hFindFile,&FindData));

                FindClose(hFindFile);
            }

            pChild->Release();
            pChild = NULL;
        }
    }

    return hr;
}

/**
 * This function initializes any root item properties
 * needed for this WIA driver.
 *
 * @param pWiasContext
 *               Pointer to the WIA item context
 * @return
 */
HRESULT InitializeRootItemProperties(
    BYTE        *pWiasContext)
{
    HRESULT hr = E_INVALIDARG;
    if(pWiasContext)
    {
        CWIAPropertyManager PropertyManager;
        GUID guidItemCategory = GUID_NULL;
        hr = PropertyManager.AddProperty(WIA_IPA_ITEM_CATEGORY,WIA_IPA_ITEM_CATEGORY_STR,RN,guidItemCategory);
        if(SUCCEEDED(hr))
        {
            hr = PropertyManager.SetItemProperties(pWiasContext);
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "CWIAPropertyManager::SetItemProperties failed to set WIA flatbed item properties, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to add WIA_IPA_ITEM_CATEGORY property to the property manager, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function initializes child item properties
 * needed for this WIA driver.  The uiResourceID parameter
 * determines what image properties will be used.
 *
 * @param pWiasContext
 *                  Pointer to the WIA item context
 * @param hInstance HINSTANCE of the resource location containing uiResourceIDs
 * @param uiResourceID
 *                  Resource ID of a bitmap resource loaded as source data
 *                  and a source of WIA item properties.
 * @param bRootItem TRUE - Legacy WIA properties that belong on the root item
 *                  of the device will be added.
 *                  FALSE - Child item WIA properties will be added to the item.
 * @return
 */
HRESULT InitializeWIAItemProperties(
    BYTE        *pWiasContext,
    HINSTANCE   hInstance,
    UINT        uiResourceID,
    BOOL        bRootItem)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(hInstance))
    {
        CWIAPropertyManager PropertyManager;
        Bitmap GDIPlusBitmap(hInstance,MAKEINTRESOURCE(uiResourceID));

        LONG lXPosition         = 0;
        LONG lYPosition         = 0;
        LONG lXExtent           = (LONG)GDIPlusBitmap.GetWidth();
        LONG lYExtent           = (LONG)GDIPlusBitmap.GetHeight();
        LONG lXResolution       = 75;  // Our sample images are 75 dpi
        LONG lYResolution       = 75;  // Our sample images are 75 dpi
        LONG lHorizontalSize    = ConvertTo1000thsOfAnInch(lXExtent,lXResolution);
        LONG lVerticalSize      = ConvertTo1000thsOfAnInch(lYExtent,lYResolution);
        LONG lItemType          = 0;

        //
        // Set coordinates for fixed frames
        //
        if (IDB_FILM == uiResourceID)
        {
            ULONG   ulFrame      = NO_FIXED_FRAME;
            BSTR    bstrItemName = NULL;
            //  Get the item name
            hr = wiasReadPropStr(pWiasContext, WIA_IPA_ITEM_NAME, &bstrItemName, NULL, TRUE);

            if (S_OK == hr)
            {
                if (!lstrcmp(bstrItemName, L"Frame1"))
                {
                    ulFrame = 0;
                }
                else if (!lstrcmp(bstrItemName, L"Frame2"))
                {
                    ulFrame = 1;
                }
                else if (!lstrcmp(bstrItemName, L"Frame3"))
                {
                    ulFrame = 2;
                }
                else if (!lstrcmp(bstrItemName, L"Frame4"))
                {
                    ulFrame = 3;
                }

                if (ulFrame != NO_FIXED_FRAME)
                {
                    lXPosition = g_FilmFrames[ulFrame].XPOS;
                    lYPosition = g_FilmFrames[ulFrame].YPOS;
                    lXExtent   = g_FilmFrames[ulFrame].XEXTENT;
                    lYExtent   = g_FilmFrames[ulFrame].YEXTENT;
                }

                SysFreeString(bstrItemName);
                bstrItemName = NULL;
            }
        }

        hr = wiasGetItemType(pWiasContext,&lItemType);
        if(SUCCEEDED(hr))
        {
            if(lItemType & WiaItemTypeGenerated)
            {
                WIAS_TRACE((g_hInst,"WIA item was created by application."));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get the WIA item type, hr = 0x%lx",hr));
        }

        //
        // Add all common item properties first
        //

        if((lXExtent)&&(lYExtent)&&(lXResolution)&&(lYResolution)&&(lHorizontalSize)&&(lVerticalSize))
        {
            LONG lAccessRights = WIA_ITEM_READ;
            hr = PropertyManager.AddProperty(WIA_IPA_ACCESS_RIGHTS ,WIA_IPA_ACCESS_RIGHTS_STR ,RN,(LONG) 0);

            if(SUCCEEDED(hr))
            {
                LONG lOpticalXResolution = lXResolution;
                hr = PropertyManager.AddProperty(WIA_DPS_OPTICAL_XRES ,WIA_DPS_OPTICAL_XRES_STR ,RN,lOpticalXResolution);
            }

            if(SUCCEEDED(hr))
            {
                LONG lOpticalYResolution = lYResolution;
                hr = PropertyManager.AddProperty(WIA_DPS_OPTICAL_YRES ,WIA_DPS_OPTICAL_YRES_STR ,RN,lOpticalYResolution);
            }

            if(SUCCEEDED(hr))
            {
                CBasicDynamicArray<LONG> lPreviewArray;
                lPreviewArray.Append(WIA_FINAL_SCAN);
                lPreviewArray.Append(WIA_PREVIEW_SCAN);
                hr = PropertyManager.AddProperty(WIA_DPS_PREVIEW ,WIA_DPS_PREVIEW_STR ,RWLC,lPreviewArray[0],lPreviewArray[0],&lPreviewArray);
            }

            if(SUCCEEDED(hr))
            {
                LONG lShowPreviewControl = WIA_SHOW_PREVIEW_CONTROL;
                hr = PropertyManager.AddProperty(WIA_DPS_SHOW_PREVIEW_CONTROL ,WIA_DPS_SHOW_PREVIEW_CONTROL_STR ,RN,lShowPreviewControl);
            }

            if((uiResourceID == IDB_FLATBED)||(uiResourceID == IDB_FILM))
            {
                if(SUCCEEDED(hr))
                {
                    hr = PropertyManager.AddProperty(WIA_DPS_HORIZONTAL_BED_SIZE ,WIA_DPS_HORIZONTAL_BED_SIZE_STR ,RN,lHorizontalSize);
                }

                if(SUCCEEDED(hr))
                {
                    hr = PropertyManager.AddProperty(WIA_DPS_VERTICAL_BED_SIZE ,WIA_DPS_VERTICAL_BED_SIZE_STR ,RN,lVerticalSize);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lHorizontalBedRegistration = LEFT_JUSTIFIED;
                    hr = PropertyManager.AddProperty(WIA_DPS_HORIZONTAL_BED_REGISTRATION ,WIA_DPS_HORIZONTAL_BED_REGISTRATION_STR ,RN,lHorizontalBedRegistration);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lVerticalBedRegistration = TOP_JUSTIFIED;
                    hr = PropertyManager.AddProperty(WIA_DPS_VERTICAL_BED_REGISTRATION ,WIA_DPS_VERTICAL_BED_REGISTRATION_STR ,RN,lVerticalBedRegistration);
                }
            }
            else if(uiResourceID == IDB_FEEDER)
            {
                if(SUCCEEDED(hr))
                {
                    hr = PropertyManager.AddProperty(WIA_DPS_HORIZONTAL_SHEET_FEED_SIZE ,WIA_DPS_HORIZONTAL_SHEET_FEED_SIZE_STR ,RN,lHorizontalSize);
                }

                if(SUCCEEDED(hr))
                {
                    hr = PropertyManager.AddProperty(WIA_DPS_VERTICAL_SHEET_FEED_SIZE ,WIA_DPS_VERTICAL_SHEET_FEED_SIZE_STR ,RN,lVerticalSize);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lSheetFeederRegistration = LEFT_JUSTIFIED;
                    hr = PropertyManager.AddProperty(WIA_DPS_SHEET_FEEDER_REGISTRATION ,WIA_DPS_SHEET_FEEDER_REGISTRATION_STR ,RN,lSheetFeederRegistration);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lDocumentHandlingSelect            = FEEDER;
                    LONG lDocumentHandlingSelectValidValues = FEEDER|DUPLEX;
                    hr = PropertyManager.AddProperty(WIA_DPS_DOCUMENT_HANDLING_SELECT ,WIA_DPS_DOCUMENT_HANDLING_SELECT_STR ,RWF,lDocumentHandlingSelect,lDocumentHandlingSelectValidValues);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lMaxPages            = 100;
                    LONG lDefaultPagesSetting = 1;
                    LONG lPages               = 1;
                    hr = PropertyManager.AddProperty(WIA_DPS_PAGES ,WIA_DPS_PAGES_STR ,RWR,lDefaultPagesSetting,lDefaultPagesSetting,0,lMaxPages,lPages);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lDocumentHandlingCapabilities = FEED|DUP;
                    hr = PropertyManager.AddProperty(WIA_DPS_DOCUMENT_HANDLING_CAPABILITIES ,WIA_DPS_DOCUMENT_HANDLING_CAPABILITIES_STR ,RN,lDocumentHandlingCapabilities);
                }

                if(SUCCEEDED(hr))
                {
                    LONG lDocumentHandlingStatus            = FEED_READY;
                    hr = PropertyManager.AddProperty(WIA_DPS_DOCUMENT_HANDLING_STATUS ,WIA_DPS_DOCUMENT_HANDLING_STATUS_STR ,RN,lDocumentHandlingStatus);
                }
            }
            if(SUCCEEDED(hr))
            {
                LONG lCurrentIntent             = WIA_INTENT_NONE;
                LONG lCurrentIntentValidValues  = WIA_INTENT_IMAGE_TYPE_COLOR | WIA_INTENT_MINIMIZE_SIZE | WIA_INTENT_MAXIMIZE_QUALITY;
                hr = PropertyManager.AddProperty(WIA_IPS_CUR_INTENT ,WIA_IPS_CUR_INTENT_STR ,RWF,lCurrentIntent,lCurrentIntentValidValues);
            }

            if(bRootItem)
            {
                BYTE *pWiasRootContext = NULL;
                hr = wiasGetRootItem(pWiasContext,&pWiasRootContext);
                if(SUCCEEDED(hr))
                {
                    if(uiResourceID == IDB_FEEDER)
                    {
                        //
                        // Add FLATBED to the WIA_DPS_DOCUMENT_HANDLING_SELECT property, so
                        // legacy applications will be able to determine that this driver supports
                        // both flatbed and feeder scanning.  Default to FLATBED.
                        //

                        LONG lDocumentHandlingSelect            = FLATBED; // default to flatbed for this scanner
                        LONG lDocumentHandlingSelectValidValues = FLATBED|FEEDER|DUPLEX;
                        hr = PropertyManager.AddProperty(WIA_DPS_DOCUMENT_HANDLING_SELECT ,WIA_DPS_DOCUMENT_HANDLING_SELECT_STR ,RWF,lDocumentHandlingSelect,lDocumentHandlingSelectValidValues);
                        if(FAILED(hr))
                        {
                            WIAS_ERROR((g_hInst, "Failed to add WIA_DPS_DOCUMENT_HANDLING_SELECT property to the property manager, hr = 0x%lx",hr));
                        }
                    }

                    hr = PropertyManager.SetItemProperties(pWiasRootContext);
                    if(FAILED(hr))
                    {
                        WIAS_ERROR((g_hInst, "Failed to set the WIA item properties on the root item, hr = 0x%lx",hr));
                    }
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Failed to get the root item, hr = 0x%lx",hr));
                }
                return hr; // early return!!
            }

            if(SUCCEEDED(hr))
            {
                GUID guidItemCategory = WIA_CATEGORY_FLATBED;
                switch(uiResourceID)
                {
                case IDB_FLATBED:
                    guidItemCategory = WIA_CATEGORY_FLATBED;
                    break;
                case IDB_FEEDER:
                    guidItemCategory = WIA_CATEGORY_FEEDER;
                    break;
                case IDB_FILM:
                    guidItemCategory = WIA_CATEGORY_FILM;
                    break;
                default:
                    guidItemCategory = GUID_NULL;
                    break;
                }

                hr = PropertyManager.AddProperty(WIA_IPA_ITEM_CATEGORY,WIA_IPA_ITEM_CATEGORY_STR,RN,guidItemCategory);
            }

            if(SUCCEEDED(hr))
            {
                CBasicDynamicArray<LONG> lXResolutionArray;
                lXResolutionArray.Append(lXResolution);
                hr = PropertyManager.AddProperty(WIA_IPS_XRES ,WIA_IPS_XRES_STR ,RWLC,lXResolutionArray[0],lXResolutionArray[0],&lXResolutionArray);
            }

            if(SUCCEEDED(hr))
            {
                CBasicDynamicArray<LONG> lYResolutionArray;
                lYResolutionArray.Append(lYResolution);
                hr = PropertyManager.AddProperty(WIA_IPS_YRES ,WIA_IPS_YRES_STR ,RWLC,lYResolutionArray[0],lYResolutionArray[0],&lYResolutionArray);
            }

            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.AddProperty(WIA_IPS_XPOS ,WIA_IPS_XPOS_STR ,RWRC,lXPosition,lXPosition,lXPosition,lXPosition + (lXExtent - 1),1);
            }

            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.AddProperty(WIA_IPS_YPOS ,WIA_IPS_YPOS_STR ,RWRC,lYPosition,lYPosition,lYPosition,lYPosition + (lYExtent - 1),1);
            }

            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.AddProperty(WIA_IPS_XEXTENT ,WIA_IPS_XEXTENT_STR , RWRC,lXExtent,lXExtent,1,lXExtent,1);
            }

            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.AddProperty(WIA_IPS_YEXTENT ,WIA_IPS_YEXTENT_STR ,RWRC,lYExtent,lYExtent,1,lYExtent,1);
            }

            if(SUCCEEDED(hr))
            {
                CBasicDynamicArray<LONG> lRotationArray;
                lRotationArray.Append(PORTRAIT);
                lRotationArray.Append(LANSCAPE);
                lRotationArray.Append(ROT180);
                lRotationArray.Append(ROT270);

                hr = PropertyManager.AddProperty(WIA_IPS_ROTATION ,WIA_IPS_ROTATION_STR ,RWLC,lRotationArray[0],lRotationArray[0],&lRotationArray);
            }

            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.AddProperty(WIA_IPS_DESKEW_X ,WIA_IPS_DESKEW_X_STR ,RWRC,0,0,0,lXExtent,1);
            }
           
            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.AddProperty(WIA_IPS_DESKEW_Y ,WIA_IPS_DESKEW_Y_STR ,RWRC,0,0,0,lYExtent,1);
            }            

            if(SUCCEEDED(hr))
            {
                LONG lBrightness = 0;
                hr = PropertyManager.AddProperty(WIA_IPS_BRIGHTNESS,WIA_IPS_BRIGHTNESS_STR,RWRC,lBrightness,lBrightness,-1000,1000,1);
            }

            if(SUCCEEDED(hr))
            {
                LONG lContrast = 0;
                hr = PropertyManager.AddProperty(WIA_IPS_CONTRAST ,WIA_IPS_CONTRAST_STR ,RWRC,lContrast,lContrast,-1000,1000,1);
            }

            if(SUCCEEDED(hr) && ((IDB_FILM == uiResourceID) || (IDB_FLATBED == uiResourceID)))
            {
                LONG lSegmentation = (IDB_FLATBED == uiResourceID) ? WIA_USE_SEGMENTATION_FILTER : WIA_DONT_USE_SEGMENTATION_FILTER;
                hr = PropertyManager.AddProperty(WIA_IPS_SEGMENTATION ,WIA_IPS_SEGMENTATION_STR ,RN, lSegmentation);
            }

            if(SUCCEEDED(hr))
            {
                LONG lErrorHandler             = ERROR_HANDLING_NONE;
                LONG lErrorHandlerValidValues  = ERROR_HANDLING_WARMING_UP | ERROR_HANDLING_COVER_OPEN | ERROR_HANDLING_PRIVATE_ERROR | ERROR_HANDLING_UNHANDLED_STATUS | ERROR_HANDLING_UNHANDLED_ERROR;

                hr = PropertyManager.AddProperty(MY_WIA_ERROR_HANDLING_PROP ,MY_WIA_ERROR_HANDLING_PROP_STR ,RWF,lErrorHandler,lErrorHandlerValidValues);
            }

            if(SUCCEEDED(hr))
            {
                LONG lItemSize = 0;
                hr = PropertyManager.AddProperty(WIA_IPA_ITEM_SIZE ,WIA_IPA_ITEM_SIZE_STR ,RN,lItemSize);
            }

            if(SUCCEEDED(hr))
            {
                // TBD: This property is assuming that the source image is color.  Should be changed to be
                //      more dynamic.
                CBasicDynamicArray<LONG> lDataTypeArray;
                lDataTypeArray.Append(WIA_DATA_COLOR);
                hr = PropertyManager.AddProperty(WIA_IPA_DATATYPE ,WIA_IPA_DATATYPE_STR ,RWL,lDataTypeArray[0],lDataTypeArray[0],&lDataTypeArray);
            }

            if(SUCCEEDED(hr))
            {
                // TBD: This property is assuming that the source image is 24-bit color.  Should be changed to be
                //      more dynamic.
                CBasicDynamicArray<LONG> lBitDepthArray;
                lBitDepthArray.Append(24);
                hr = PropertyManager.AddProperty(WIA_IPA_DEPTH ,WIA_IPA_DEPTH_STR ,RWLC,lBitDepthArray[0],lBitDepthArray[0],&lBitDepthArray);
            }

            if(SUCCEEDED(hr))
            {
                GUID guidPreferredFormat = WiaImgFmt_BMP;
                hr = PropertyManager.AddProperty(WIA_IPA_PREFERRED_FORMAT ,WIA_IPA_PREFERRED_FORMAT_STR ,RN,guidPreferredFormat);
            }

            if(SUCCEEDED(hr))
            {
                CBasicDynamicArray<GUID> guidFormatArray;
                guidFormatArray.Append(WiaImgFmt_BMP);
                hr = PropertyManager.AddProperty(WIA_IPA_FORMAT ,WIA_IPA_FORMAT_STR ,RWL,guidFormatArray[0],guidFormatArray[0],&guidFormatArray);
            }

            if(SUCCEEDED(hr))
            {
                LONG lCompression = WIA_COMPRESSION_NONE;
                hr = PropertyManager.AddProperty(WIA_IPA_COMPRESSION ,WIA_IPA_COMPRESSION_STR ,RN,lCompression);
            }

            if(SUCCEEDED(hr))
            {
                CBasicDynamicArray<LONG> lTymedArray;
                //
                // TBD: We should not have to add TYMED_CALLBACK here in the future - should be
                // done by compat layer.
                //
                lTymedArray.Append(TYMED_FILE);
                lTymedArray.Append(TYMED_CALLBACK);
                hr = PropertyManager.AddProperty(WIA_IPA_TYMED ,WIA_IPA_TYMED_STR ,RWL,lTymedArray[0],lTymedArray[0],&lTymedArray);
            }

            if(SUCCEEDED(hr))
            {
                // TBD: This property is assuming that the source image is 24-bit color and has 3 channels.  Should be changed to be
                //      more dynamic.
                LONG lChannelsPerPixel = 3;
                hr = PropertyManager.AddProperty(WIA_IPA_CHANNELS_PER_PIXEL ,WIA_IPA_CHANNELS_PER_PIXEL_STR ,RN,lChannelsPerPixel);
            }

            if(SUCCEEDED(hr))
            {
                // TBD: This property is assuming that the source image is 24-bit color and has 8 bits per channel.  Should be changed to be
                //      more dynamic.
                LONG lBitsPerChannel = 8;
                hr = PropertyManager.AddProperty(WIA_IPA_BITS_PER_CHANNEL ,WIA_IPA_BITS_PER_CHANNEL_STR ,RN,lBitsPerChannel);
            }

            if(SUCCEEDED(hr))
            {
                LONG lPlanar = WIA_PACKED_PIXEL;
                hr = PropertyManager.AddProperty(WIA_IPA_PLANAR ,WIA_IPA_PLANAR_STR ,RN,lPlanar);
            }

            if(SUCCEEDED(hr))
            {
                LONG lPixelsPerLine = lXExtent;
                hr = PropertyManager.AddProperty(WIA_IPA_PIXELS_PER_LINE ,WIA_IPA_PIXELS_PER_LINE_STR ,RN,lPixelsPerLine);
            }

            if(SUCCEEDED(hr))
            {
                LONG lNumberOfLines = lYExtent;
                hr = PropertyManager.AddProperty(WIA_IPA_NUMBER_OF_LINES ,WIA_IPA_NUMBER_OF_LINES_STR ,RN,lNumberOfLines);
            }

            if(SUCCEEDED(hr))
            {
                // TBD: A small buffer size was used here to allow slower transfers with more progress.  Real
                //      drivers should use a higher value to increase performance.
                LONG lBufferSize = DEFAULT_BUFFER_SIZE;
                hr = PropertyManager.AddProperty(WIA_IPA_BUFFER_SIZE ,WIA_IPA_BUFFER_SIZE_STR ,RN,lBufferSize);
            }

            if(SUCCEEDED(hr))
            {
                BSTR bstrFileExtension = SysAllocString(L"BMP");
                if(bstrFileExtension)
                {
                    hr = PropertyManager.AddProperty(WIA_IPA_FILENAME_EXTENSION ,WIA_IPA_FILENAME_EXTENSION_STR ,RN,bstrFileExtension);

                    SysFreeString(bstrFileExtension);
                    bstrFileExtension = NULL;
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                    WIAS_ERROR((g_hInst, "Could not allocate the file name extension property value, hr = 0x%lx.",hr));
                }
            }

            if(SUCCEEDED(hr))
            {
                GUID guidStreamCompatID = GUID_NULL;
                hr = PropertyManager.AddProperty(WIA_IPA_PROP_STREAM_COMPAT_ID,WIA_IPA_PROP_STREAM_COMPAT_ID_STR,RN,guidStreamCompatID);
            }

            if(SUCCEEDED(hr))
            {
                hr = PropertyManager.SetItemProperties(pWiasContext);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "CWIAPropertyManager::SetItemProperties failed to set WIA flatbed item properties, hr = 0x%lx",hr));
                }
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to obtain valid information from flatbed bitmap file resource to build a WIA property set"));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function initializes child item properties
 * needed for this WIA driver's storage item.  The
 * WIA_DRIVER_ITEM_CONTEXT structure stored as the
 * the WIA driver item context will be used to
 * properly set the WIA_IPA_FILENAME_EXTENSION property
 * value.
 *
 * @param pWiasContext
 *                  Pointer to the WIA item context
 * @param bRootItem TRUE - Legacy WIA properties that belong on the root item
 *                  of the device will be added.
 *                  FALSE - Child item WIA properties will be added to the item.
 * @return
 */
HRESULT InitializeWIAStorageItemProperties(
    BYTE        *pWiasContext,
    BOOL        bRootItem)
{
    HRESULT hr = E_INVALIDARG;
    if(pWiasContext)
    {
        CWIAPropertyManager PropertyManager;
        LONG                lItemType = 0;
        hr = wiasGetItemType(pWiasContext,&lItemType);
        if(SUCCEEDED(hr))
        {
            GUID guidItemCategory = WIA_CATEGORY_FINISHED_FILE;
            hr = PropertyManager.AddProperty(WIA_IPA_ITEM_CATEGORY,WIA_IPA_ITEM_CATEGORY_STR,RN,guidItemCategory);
            if(SUCCEEDED(hr))
            {
                if(!(lItemType & WiaItemTypeGenerated))
                {
                    WIA_DRIVER_ITEM_CONTEXT *pWiaDriverItemContext = NULL;
                    hr = wiasGetDriverItemPrivateContext(pWiasContext,(BYTE**)&pWiaDriverItemContext);
                    if(SUCCEEDED(hr))
                    {
                        if(lItemType & WiaItemTypeStorage)
                        {
                            //
                            // This is the parent storage item, update the number of items stored and
                            // proper access rights
                            //

                            LONG lAccessRights = WIA_ITEM_READ;
                            hr = PropertyManager.AddProperty(WIA_IPA_ACCESS_RIGHTS ,WIA_IPA_ACCESS_RIGHTS_STR ,RN,(LONG) 0);
                            if(SUCCEEDED(hr))
                            {
                                hr = PropertyManager.AddProperty(WIA_IPA_ITEMS_STORED,
                                                             WIA_IPA_ITEMS_STORED_STR,
                                                             RN,
                                                             pWiaDriverItemContext->lNumItemsStored);
                                if(FAILED(hr))
                                {
                                    WIAS_ERROR((g_hInst, "Failed to add WIA_IPA_ITEMS_STORED property to the property manager, hr = 0x%lx",hr));
                                }
                            }
                            else
                            {
                                WIAS_ERROR((g_hInst, "Failed to add WIA_IPA_ACCESS_RIGHTS property to the property manager, hr = 0x%lx",hr));
                            }
                        }
                        else
                        {
                            //
                            // This must be a child item of some kind
                            //

                            if(SUCCEEDED(hr))
                            {
                                LONG lItemSize = 0;
                                hr = PropertyManager.AddProperty(WIA_IPA_ITEM_SIZE ,WIA_IPA_ITEM_SIZE_STR ,RN,lItemSize);
                            }

                            if(SUCCEEDED(hr))
                            {
                                GUID guidPreferredFormat = WiaImgFmt_UNDEFINED;
                                hr = PropertyManager.AddProperty(WIA_IPA_PREFERRED_FORMAT ,WIA_IPA_PREFERRED_FORMAT_STR ,RN,guidPreferredFormat);
                            }

                            if(SUCCEEDED(hr))
                            {
                                CBasicDynamicArray<GUID> guidFormatArray;
                                guidFormatArray.Append(WiaImgFmt_UNDEFINED);
                                hr = PropertyManager.AddProperty(WIA_IPA_FORMAT ,WIA_IPA_FORMAT_STR ,RWL,guidFormatArray[0],guidFormatArray[0],&guidFormatArray);
                            }

                            if(SUCCEEDED(hr))
                            {
                                CBasicDynamicArray<LONG> lTymedArray;

                                //
                                // TBD: We should not have to add TYMED_CALLBACK here in the future - should be
                                // done by compat layer.
                                //
                                lTymedArray.Append(TYMED_FILE);
                                lTymedArray.Append(TYMED_CALLBACK);
                                hr = PropertyManager.AddProperty(WIA_IPA_TYMED ,WIA_IPA_TYMED_STR ,RWL,lTymedArray[0],lTymedArray[0],&lTymedArray);
                            }

                            if(SUCCEEDED(hr))
                            {
                                // TBD: A small buffer size was used here to allow slower transfers with more progress.  Real
                                //      drivers should use a higher value to increase performance.
                                LONG lBufferSize = DEFAULT_BUFFER_SIZE;
                                hr = PropertyManager.AddProperty(WIA_IPA_BUFFER_SIZE ,WIA_IPA_BUFFER_SIZE_STR ,RN,lBufferSize);
                            }

                            if(SUCCEEDED(hr))
                            {
                                BSTR bstrFileExtension = NULL;
                                if(pWiaDriverItemContext->bstrStorageDataPath)
                                {
                                    hr = GetFileExtensionFromPath(pWiaDriverItemContext->bstrStorageDataPath, &bstrFileExtension);
                                }
                                else
                                {
                                    bstrFileExtension = SysAllocString(L"UNDEFINED");
                                    hr = S_OK;
                                }
                                if(SUCCEEDED(hr))
                                {
                                    if(bstrFileExtension)
                                    {
                                        hr = PropertyManager.AddProperty(WIA_IPA_FILENAME_EXTENSION ,WIA_IPA_FILENAME_EXTENSION_STR ,RN,bstrFileExtension);
                                        SysFreeString(bstrFileExtension);
                                        bstrFileExtension = NULL;
                                    }
                                    else
                                    {
                                        hr = E_OUTOFMEMORY;
                                        WIAS_ERROR((g_hInst, "Could not allocate the file name extension property value, hr = 0x%lx.",hr));
                                    }
                                }
                                else
                                {
                                    WIAS_ERROR((g_hInst, "Failed to extract file extension from path (%ws), hr = 0x%lx",pWiaDriverItemContext->bstrStorageDataPath,hr));
                                }
                            }
                        }
                    }
                    else
                    {
                        WIAS_ERROR((g_hInst, "Failed to obtain the WIA_DRIVER_ITEM_CONTEXT structure from the WIA driver item, hr = 0x%lx",hr));
                    }
                }
                else
                {
                    WIAS_TRACE((g_hInst,"WIA item was created by application, driver is only adding the WIA item category property"));
                }
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to add WIA_IPA_ITEM_CATEGORY property to the property manager, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get the WIA item type, hr = 0x%lx",hr));
        }

        if(SUCCEEDED(hr))
        {
            hr = PropertyManager.SetItemProperties(pWiasContext);
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "CWIAPropertyManager::SetItemProperties failed to set WIA storage item properties, hr = 0x%lx",hr));
            }
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function returns the WIA driver item context
 * data stored with the driver item.  NOT ALL DRIVER ITEMS
 * HAVE CONTEXTS STORED WITH THEM.  The context is initialized
 * and stored at WIA item creation.  See CreateWIAChildItem
 * function.
 *
 * @param pWiasContext
 *               Pointer to the WIA item context
 * @param ppWiaDriverItemContext
 *               Pointer to the WIA driver item context data
 * @return
 */
HRESULT wiasGetDriverItemPrivateContext(
    BYTE *pWiasContext,
    BYTE **ppWiaDriverItemContext)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext)&&(ppWiaDriverItemContext))
    {
        IWiaDrvItem *pIWiaDrvItem   = NULL;
        hr = wiasGetDrvItem(pWiasContext, &pIWiaDrvItem);
        if(SUCCEEDED(hr))
        {
            hr = pIWiaDrvItem->GetDeviceSpecContext(ppWiaDriverItemContext);
            //
            // The caller will handle the failure case.  A failure, may mean that the
            // the WIA item does not have a private device specific context
            // stored.  This is OK, because is is not required.
            //
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get the WIA driver item from the application item, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function returns the application item's
 * parent WIA item context.  The returned context
 * can be used to access the parent's WIA property
 * set.
 *
 * @param pWiasContext
 *               Pointer to the WIA item context
 * @param ppWiasContext
 *               Pointer to the parent WIA item context
 * @return
 */
HRESULT wiasGetAppItemParent(
    BYTE *pWiasContext,
    BYTE **ppWiasContext)
{
    HRESULT hr = E_INVALIDARG;
    if((pWiasContext) && (ppWiasContext))
    {
        // FIX! This helper function is actually getting the backing driver
        //      item and returning it as the parent.  This will make the
        //      driver always associate the newly created child item with its
        //      proper backing driver item.  This function should be fixed to
        //      return the parent application item.
        //

        IWiaDrvItem *pIWiaDrvItemParent = NULL;
        hr = wiasGetDrvItem(pWiasContext,&pIWiaDrvItemParent);
        if(SUCCEEDED(hr))
        {
            BSTR bstrFullItemName = NULL;
            hr = pIWiaDrvItemParent->GetFullItemName(&bstrFullItemName);
            if(SUCCEEDED(hr))
            {
                hr = wiasGetContextFromName(pWiasContext,0,bstrFullItemName,ppWiasContext);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to get the parent's application item from the item name (%ws), hr = 0x%lx",bstrFullItemName,hr));
                }
                SysFreeString(bstrFullItemName);
                bstrFullItemName = NULL;
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to get full item name from parent IWiaDrvItem, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get the WIA driver item from the application item, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function converts a unit (in pixels) to
 * another unit (1/1000ths of an inch).
 *
 * @param lPixelLength
 *               Unit length in pixels
 * @param lResolution
 *               Resolution of Pixel unit length (in Dots Per Inch "DPI")
 * @return
 */
LONG ConvertTo1000thsOfAnInch(
    LONG lPixelLength,
    LONG lResolution)
{
    LONG lConvertedValue = 0;
    if((lPixelLength)&&(lResolution))
    {
        lConvertedValue = (LONG)((((lPixelLength * 1000) + lResolution - 1) / lResolution));
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return lConvertedValue;
}

/**
 * This function populates a BITMAPINFOHEADER structure
 * using data contained in a Gdiplus::BitmapData object.
 * This function only works with 24-bit data.
 *
 * @param pGDIPlusBitmapData
 *               Pointer to a GDI+ BitmapData object
 * @param pBitmapInfoHeader
 *               Pointer to a BITMAPINFOHEADER structure
 * @return
 */
HRESULT GetBitmapHeaderFromBitmapData(
    Gdiplus::BitmapData     *pGDIPlusBitmapData,
    BITMAPINFOHEADER        *pBitmapInfoHeader)
{
    HRESULT hr = E_INVALIDARG;
    if((pGDIPlusBitmapData) && (pBitmapInfoHeader) && (pGDIPlusBitmapData->PixelFormat == PixelFormat24bppRGB))
    {
        memset(pBitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
        pBitmapInfoHeader->biSize       = sizeof(BITMAPINFOHEADER);
        pBitmapInfoHeader->biPlanes     = 1;
        pBitmapInfoHeader->biWidth      = pGDIPlusBitmapData->Width;
        pBitmapInfoHeader->biHeight     = pGDIPlusBitmapData->Height;

        // We cannot use the stride to calculate the size, because if there is no
        // format conversion, we might get the original bits...
        // We need to calculate the size based on the width
        pBitmapInfoHeader->biSizeImage  = ((((pGDIPlusBitmapData->Width * 3) + 3) & ~3) * pGDIPlusBitmapData->Height);
        
        pBitmapInfoHeader->biBitCount   = 24;
        hr = S_OK;
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function returns a Gdiplus::Rect structure
 * initialized with the current WIA extent setting
 * values.  This function assumes that the WIA item
 * passed in supports WIA_IPS_XPOS, WIA_IPS_YPOS,
 * WIA_IPS_XEXTENT and WIA_IPS_YEXTENT properties.
 *
 * @param pWiasContext
 *               Pointer to the WIA item context
 * @param pRect  Pointer to a Gdiplus::Rect object
 * @return
 */
HRESULT GetSelectionAreaRect(
    BYTE*           pWiasContext,
    Gdiplus::Rect   *pRect)
{
    HRESULT hr = E_INVALIDARG;
    LONG    lXPos       = 0;
    LONG    lYPos       = 0;
    LONG    lXExtent    = 0;
    LONG    lYExtent    = 0;

    if((pWiasContext)&&(pRect))
    {
        hr = wiasReadPropLong(pWiasContext,WIA_IPS_XPOS,&lXPos,NULL,TRUE);
        if(SUCCEEDED(hr))
        {
            hr = wiasReadPropLong(pWiasContext,WIA_IPS_YPOS,&lYPos,NULL,TRUE);
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "Failed to read the WIA_IPS_YPOS property, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to read the WIA_IPS_XPOS property, hr = 0x%lx",hr));
        }
        if(SUCCEEDED(hr))
        {
            hr = wiasReadPropLong(pWiasContext,WIA_IPS_YEXTENT,&lYExtent,NULL,TRUE);
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "Failed to read the WIA_IPS_YEXTENT property, hr = 0x%lx",hr));
            }
        }
        if(SUCCEEDED(hr))
        {
            hr = wiasReadPropLong(pWiasContext,WIA_IPS_XEXTENT,&lXExtent,NULL,TRUE);
            if(FAILED(hr))
            {
                WIAS_ERROR((g_hInst, "Failed to read the WIA_IPS_XEXTENT property, hr = 0x%lx",hr));
            }
        }
        if(SUCCEEDED(hr))
        {
            Gdiplus::Rect rFrame((INT)lXPos,(INT)lYPos,(INT)lXExtent,(INT)lYExtent);
            *pRect = rFrame;
            hr = S_OK;
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function locks down a portion of a bitmap using
 * the current WIA extent setting values.  This function assumes that the WIA item
 * passed in supports WIA_IPS_XPOS, WIA_IPS_YPOS,
 * WIA_IPS_XEXTENT and WIA_IPS_YEXTENT properties.
 *
 * @param pWiasContext
 *                Pointer to the WIA item context
 * @param pBitmap Pointer to a Gdiplus::Bitmap object containing the
 *                bitmap data.
 * @param pBitmapData
 *                Pointer to a Gdiplus::BitmapData object
 * @param pbmih  Pointer to a BITMAPINFOHEADER structure that will
 *               receive the information about the locked area of the
 *               bitmap.
 * @param ppBitmapBits
 *                Pointer to the first scan line of data of the locked
 *                portion of the bitmap
 * @return
 */
HRESULT LockSelectionAreaOnBitmap(
    BYTE                    *pWiasContext,
    Gdiplus::Bitmap         *pBitmap,
    Gdiplus::BitmapData     *pBitmapData,
    BITMAPINFOHEADER        *pbmih,
    BYTE                    **ppBitmapBits)
{
    HRESULT hr = E_INVALIDARG;

    if((pBitmapData)&&(pbmih)&&(ppBitmapBits))
    {
        Gdiplus::Rect rFrame(0,0,0,0);
        hr = GetSelectionAreaRect(pWiasContext,&rFrame);
        
        if(SUCCEEDED(hr))
        {
            if(pBitmap->LockBits(&rFrame,
                                 ImageLockModeRead,
                                 PixelFormat24bppRGB,
                                 pBitmapData) == Ok)
            {
                hr = GetBitmapHeaderFromBitmapData(pBitmapData,pbmih);
                if(SUCCEEDED(hr))
                {
                    *ppBitmapBits = (BYTE*)pBitmapData->Scan0;
                }
                else
                {
                    WIAS_ERROR((g_hInst, "Failed to get the BITMAPINFOHEADER information from the GDI+ bitmap data object, hr = 0x%lx",hr));
                }
            }
            else
            {
                hr = E_FAIL;
                WIAS_ERROR((g_hInst, "Failed to LockBits on GDI+ bitmap object, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get selection area rect from WIA extent settings properties, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return  hr;
}

/**
 * This function unlocks a portion of a bitmap previously locked
 * by LockSelectionAreaOnBitmap function.
 *
 * @param pBitmap Pointer to a Gdiplus::Bitmap object containing the
 *                bitmap data.
 * @param pBitmapData
 *                Pointer to a Gdiplus::BitmapData object
 */
void UnlockSelectionAreaOnBitmap(
    Gdiplus::Bitmap         *pBitmap,
    Gdiplus::BitmapData     *pBitmapData)
{
    if((pBitmap)&&(pBitmapData))
    {
        if(pBitmap->UnlockBits(pBitmapData) != Ok)
        {
            WIAS_ERROR((g_hInst, "Failed to UnlockBits on GDI+ bitmap object"));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
}

/**
 * This helper function attempts to grab a IWiaMiniDrvTransferCallback interface
 * from a PMINIDRV_TRANSFER_CONTEXT structure.
 *
 * If successful, caller must Release.
 *
 * @param pmdtc  The PMINIDRV_TRANSFER_CONTEXT handed in during drvAcquireItemData.
 * @param ppIWiaMiniDrvTransferCallback
 *               Address of a interface pointer which receives the callback.
 * @return HRESULT return value.
 */
HRESULT GetTransferCallback(
    PMINIDRV_TRANSFER_CONTEXT       pmdtc,
    IWiaMiniDrvTransferCallback     **ppIWiaMiniDrvTransferCallback)
{
    HRESULT hr = E_INVALIDARG;
    if (pmdtc && ppIWiaMiniDrvTransferCallback)
    {
        if (pmdtc->pIWiaMiniDrvCallBack)
        {
            hr = pmdtc->pIWiaMiniDrvCallBack->QueryInterface(IID_IWiaMiniDrvTransferCallback,
                                                             (void**) ppIWiaMiniDrvTransferCallback);
        }
        else
        {
            hr = E_UNEXPECTED;
            WIAS_ERROR((g_hInst, "A NULL pIWiaMiniDrvCallBack was passed in the MINIDRV_TRANSFER_CONTEXT structure, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function allocates a buffer to be used during
 * data transfers.  FreeTransferBuffer should be called
 * to free the memory allocated by this function.
 *
 * @param pWiasContext
 *                 Pointer to the WIA item context
 * @param ppBuffer Pointer to the allocated buffer.  The caller should call
 *                 FreeTransferBuffer() when finished with this buffer.
 * @param pulBufferSize
 *                 Size of the buffer allocated.
 * @return
 */
HRESULT AllocateTransferBuffer(
    BYTE                    *pWiasContext,
    BYTE                    **ppBuffer,
    ULONG                   *pulBufferSize)
{
    HRESULT hr = S_OK;

    if (pWiasContext && ppBuffer && pulBufferSize)
    {
        //
        // Set the buffer size to DEFAULT_BUFFER_SIZE
        //
        *pulBufferSize  = DEFAULT_BUFFER_SIZE;

        // Allocate the memory
        *ppBuffer = (BYTE*) CoTaskMemAlloc(*pulBufferSize);
        if (*ppBuffer)
        {
            hr = S_OK;
        }
        else
        {
            hr = E_OUTOFMEMORY;
            WIAS_ERROR((g_hInst, "Failed to allocate memory for transfer buffer, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
        hr = E_INVALIDARG;
    }
    return hr;
}

/**
 * This function frees any memory allocated using AllocateTransferBuffer()
 * function.
 *
 * @param pBuffer Pointer to a buffer allocated with the AllocateTransferBuffer()
 *                function.
 */
void FreeTransferBuffer(
    BYTE                    *pBuffer)
{
    // Free the memory
    if (pBuffer)
    {
        CoTaskMemFree(pBuffer);
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed. (Attempted to free NULL transfer buffer)"));
    }
}

/**
 * This function attempts to extract the file
 * extension from a file path.  It is assumed that
 * the passed in path contains an extension of some
 * type. (e.g. x:\xxxxx\xxx\xxxxxx.xxx)
 *
 * @param bstrFullPath
 *               Full path containing extension
 * @param pbstrExtension
 *               Extracted extension
 * @return
 */
HRESULT GetFileExtensionFromPath(
    BSTR    bstrFullPath,
    BSTR    *pbstrExtension)
{
    HRESULT hr = E_INVALIDARG;
    if((bstrFullPath)&&(pbstrExtension))
    {
        CBasicStringWide cswPath = bstrFullPath;
        CBasicStringWide cswExtension;
        if(cswPath.Length())
        {
            INT iEndIndex   = cswPath.Length();
            INT iStartIndex = cswPath.ReverseFind(TEXT("."));
            if(iStartIndex > 0)
            {
                cswExtension = cswPath.SubStr((iStartIndex + 1),iEndIndex);
                cswExtension = cswExtension.ToUpper();
            }
        }
        *pbstrExtension = SysAllocString(cswExtension.String());
        if(*pbstrExtension)
        {
            hr = S_OK;
        }
        else
        {
            hr = E_OUTOFMEMORY;
            WIAS_ERROR((g_hInst, "Failed to allocate memory for BSTR file extension string, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Invalid parameters were passed"));
    }
    return hr;
}

/**
 * This function returns TRUE is the WIA item passed
 * in contains the WIA item flag setting of
 * WiaItemTypeProgrammableDataSource.
 *
 * @param pWiasContext
 *                 Pointer to the WIA item context
 * @return
 */
bool IsProgrammableItem(
    BYTE    *pWiasContext)
{
    LONG    lItemType   = 0;
    HRESULT hr          = S_OK;
    hr = wiasGetItemType(pWiasContext,&lItemType);
    return ((lItemType & WiaItemTypeProgrammableDataSource) == WiaItemTypeProgrammableDataSource);
}

/**
 * This function queues a WIA event using the passed in
 * WIA item context.
 *
 * @param pWiasContext
 *               Pointer to the WIA item context
 * @param guidWIAEvent
 *               WIA event to queue
 */
void QueueWIAEvent(
    BYTE        *pWiasContext,
    const GUID  &guidWIAEvent)
{
    HRESULT hr                  = S_OK;
    BSTR    bstrDeviceID        = NULL;
    BSTR    bstrFullItemName    = NULL;
    BYTE    *pRootItemContext   = NULL;

    hr = wiasReadPropStr(pWiasContext, WIA_IPA_FULL_ITEM_NAME, &bstrFullItemName, NULL,TRUE);
    if(SUCCEEDED(hr))
    {
        hr = wiasGetRootItem(pWiasContext,&pRootItemContext);
        if(SUCCEEDED(hr))
        {
            hr = wiasReadPropStr(pRootItemContext, WIA_DIP_DEV_ID,&bstrDeviceID, NULL,TRUE);
            if(SUCCEEDED(hr))
            {
                hr = wiasQueueEvent(bstrDeviceID,&guidWIAEvent,bstrFullItemName);
                if(FAILED(hr))
                {
                    WIAS_ERROR((g_hInst, "Failed to queue WIA event, hr = 0x%lx",hr));
                }
            }
            else
            {
                WIAS_ERROR((g_hInst, "Failed to read the WIA_DIP_DEV_ID property, hr = 0x%lx",hr));
            }
        }
        else
        {
            WIAS_ERROR((g_hInst, "Failed to get the Root item from child item, using wiasGetRootItem, hr = 0x%lx",hr));
        }
    }
    else
    {
        WIAS_ERROR((g_hInst, "Failed to read WIA_IPA_FULL_ITEM_NAME property, hr = %lx",hr));
    }

    if(bstrFullItemName)
    {
        SysFreeString(bstrFullItemName);
        bstrFullItemName = NULL;
    }

    if(bstrDeviceID)
    {
        SysFreeString(bstrDeviceID);
        bstrDeviceID = NULL;
    }
}
