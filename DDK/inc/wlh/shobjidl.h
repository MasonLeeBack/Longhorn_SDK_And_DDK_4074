

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for shobjidl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __shobjidl_h__
#define __shobjidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPersistFolder_FWD_DEFINED__
#define __IPersistFolder_FWD_DEFINED__
typedef interface IPersistFolder IPersistFolder;
#endif 	/* __IPersistFolder_FWD_DEFINED__ */


#ifndef __IRunnableTask_FWD_DEFINED__
#define __IRunnableTask_FWD_DEFINED__
typedef interface IRunnableTask IRunnableTask;
#endif 	/* __IRunnableTask_FWD_DEFINED__ */


#ifndef __IPersistFolder2_FWD_DEFINED__
#define __IPersistFolder2_FWD_DEFINED__
typedef interface IPersistFolder2 IPersistFolder2;
#endif 	/* __IPersistFolder2_FWD_DEFINED__ */


#ifndef __IPersistFolder3_FWD_DEFINED__
#define __IPersistFolder3_FWD_DEFINED__
typedef interface IPersistFolder3 IPersistFolder3;
#endif 	/* __IPersistFolder3_FWD_DEFINED__ */


#ifndef __IPersistIDList_FWD_DEFINED__
#define __IPersistIDList_FWD_DEFINED__
typedef interface IPersistIDList IPersistIDList;
#endif 	/* __IPersistIDList_FWD_DEFINED__ */


#ifndef __IEnumIDList_FWD_DEFINED__
#define __IEnumIDList_FWD_DEFINED__
typedef interface IEnumIDList IEnumIDList;
#endif 	/* __IEnumIDList_FWD_DEFINED__ */


#ifndef __IEnumFullIDList_FWD_DEFINED__
#define __IEnumFullIDList_FWD_DEFINED__
typedef interface IEnumFullIDList IEnumFullIDList;
#endif 	/* __IEnumFullIDList_FWD_DEFINED__ */


#ifndef __IShellFolder_FWD_DEFINED__
#define __IShellFolder_FWD_DEFINED__
typedef interface IShellFolder IShellFolder;
#endif 	/* __IShellFolder_FWD_DEFINED__ */


#ifndef __IEnumExtraSearch_FWD_DEFINED__
#define __IEnumExtraSearch_FWD_DEFINED__
typedef interface IEnumExtraSearch IEnumExtraSearch;
#endif 	/* __IEnumExtraSearch_FWD_DEFINED__ */


#ifndef __IShellFolder2_FWD_DEFINED__
#define __IShellFolder2_FWD_DEFINED__
typedef interface IShellFolder2 IShellFolder2;
#endif 	/* __IShellFolder2_FWD_DEFINED__ */


#ifndef __IShellView_FWD_DEFINED__
#define __IShellView_FWD_DEFINED__
typedef interface IShellView IShellView;
#endif 	/* __IShellView_FWD_DEFINED__ */


#ifndef __IShellView2_FWD_DEFINED__
#define __IShellView2_FWD_DEFINED__
typedef interface IShellView2 IShellView2;
#endif 	/* __IShellView2_FWD_DEFINED__ */


#ifndef __IShellView3_FWD_DEFINED__
#define __IShellView3_FWD_DEFINED__
typedef interface IShellView3 IShellView3;
#endif 	/* __IShellView3_FWD_DEFINED__ */


#ifndef __IShellViewWithFrame_FWD_DEFINED__
#define __IShellViewWithFrame_FWD_DEFINED__
typedef interface IShellViewWithFrame IShellViewWithFrame;
#endif 	/* __IShellViewWithFrame_FWD_DEFINED__ */


#ifndef __IFolderView_FWD_DEFINED__
#define __IFolderView_FWD_DEFINED__
typedef interface IFolderView IFolderView;
#endif 	/* __IFolderView_FWD_DEFINED__ */


#ifndef __IFolderView2_FWD_DEFINED__
#define __IFolderView2_FWD_DEFINED__
typedef interface IFolderView2 IFolderView2;
#endif 	/* __IFolderView2_FWD_DEFINED__ */


#ifndef __ICommDlgBrowser_FWD_DEFINED__
#define __ICommDlgBrowser_FWD_DEFINED__
typedef interface ICommDlgBrowser ICommDlgBrowser;
#endif 	/* __ICommDlgBrowser_FWD_DEFINED__ */


#ifndef __ICommDlgBrowser2_FWD_DEFINED__
#define __ICommDlgBrowser2_FWD_DEFINED__
typedef interface ICommDlgBrowser2 ICommDlgBrowser2;
#endif 	/* __ICommDlgBrowser2_FWD_DEFINED__ */


#ifndef __ICommDlgBrowser3_FWD_DEFINED__
#define __ICommDlgBrowser3_FWD_DEFINED__
typedef interface ICommDlgBrowser3 ICommDlgBrowser3;
#endif 	/* __ICommDlgBrowser3_FWD_DEFINED__ */


#ifndef __IColumnManager_FWD_DEFINED__
#define __IColumnManager_FWD_DEFINED__
typedef interface IColumnManager IColumnManager;
#endif 	/* __IColumnManager_FWD_DEFINED__ */


#ifndef __IOrderView_FWD_DEFINED__
#define __IOrderView_FWD_DEFINED__
typedef interface IOrderView IOrderView;
#endif 	/* __IOrderView_FWD_DEFINED__ */


#ifndef __IFolderFilterSite_FWD_DEFINED__
#define __IFolderFilterSite_FWD_DEFINED__
typedef interface IFolderFilterSite IFolderFilterSite;
#endif 	/* __IFolderFilterSite_FWD_DEFINED__ */


#ifndef __IFolderFilter_FWD_DEFINED__
#define __IFolderFilter_FWD_DEFINED__
typedef interface IFolderFilter IFolderFilter;
#endif 	/* __IFolderFilter_FWD_DEFINED__ */


#ifndef __IInputObjectSite_FWD_DEFINED__
#define __IInputObjectSite_FWD_DEFINED__
typedef interface IInputObjectSite IInputObjectSite;
#endif 	/* __IInputObjectSite_FWD_DEFINED__ */


#ifndef __IInputObject_FWD_DEFINED__
#define __IInputObject_FWD_DEFINED__
typedef interface IInputObject IInputObject;
#endif 	/* __IInputObject_FWD_DEFINED__ */


#ifndef __IShellIcon_FWD_DEFINED__
#define __IShellIcon_FWD_DEFINED__
typedef interface IShellIcon IShellIcon;
#endif 	/* __IShellIcon_FWD_DEFINED__ */


#ifndef __IShellBrowser_FWD_DEFINED__
#define __IShellBrowser_FWD_DEFINED__
typedef interface IShellBrowser IShellBrowser;
#endif 	/* __IShellBrowser_FWD_DEFINED__ */


#ifndef __IProfferService_FWD_DEFINED__
#define __IProfferService_FWD_DEFINED__
typedef interface IProfferService IProfferService;
#endif 	/* __IProfferService_FWD_DEFINED__ */


#ifndef __IShellItem_FWD_DEFINED__
#define __IShellItem_FWD_DEFINED__
typedef interface IShellItem IShellItem;
#endif 	/* __IShellItem_FWD_DEFINED__ */


#ifndef __IShellItem2_FWD_DEFINED__
#define __IShellItem2_FWD_DEFINED__
typedef interface IShellItem2 IShellItem2;
#endif 	/* __IShellItem2_FWD_DEFINED__ */


#ifndef __IEnumShellItems_FWD_DEFINED__
#define __IEnumShellItems_FWD_DEFINED__
typedef interface IEnumShellItems IEnumShellItems;
#endif 	/* __IEnumShellItems_FWD_DEFINED__ */


#ifndef __IQueryContinue_FWD_DEFINED__
#define __IQueryContinue_FWD_DEFINED__
typedef interface IQueryContinue IQueryContinue;
#endif 	/* __IQueryContinue_FWD_DEFINED__ */


#ifndef __ITransferAdviseSink_FWD_DEFINED__
#define __ITransferAdviseSink_FWD_DEFINED__
typedef interface ITransferAdviseSink ITransferAdviseSink;
#endif 	/* __ITransferAdviseSink_FWD_DEFINED__ */


#ifndef __IPropertyArray_FWD_DEFINED__
#define __IPropertyArray_FWD_DEFINED__
typedef interface IPropertyArray IPropertyArray;
#endif 	/* __IPropertyArray_FWD_DEFINED__ */


#ifndef __IFileOperationProgressSink_FWD_DEFINED__
#define __IFileOperationProgressSink_FWD_DEFINED__
typedef interface IFileOperationProgressSink IFileOperationProgressSink;
#endif 	/* __IFileOperationProgressSink_FWD_DEFINED__ */


#ifndef __IFileOperation_FWD_DEFINED__
#define __IFileOperation_FWD_DEFINED__
typedef interface IFileOperation IFileOperation;
#endif 	/* __IFileOperation_FWD_DEFINED__ */


#ifndef __IShellItemArray_FWD_DEFINED__
#define __IShellItemArray_FWD_DEFINED__
typedef interface IShellItemArray IShellItemArray;
#endif 	/* __IShellItemArray_FWD_DEFINED__ */


#ifndef __IEditVariantInPlace_FWD_DEFINED__
#define __IEditVariantInPlace_FWD_DEFINED__
typedef interface IEditVariantInPlace IEditVariantInPlace;
#endif 	/* __IEditVariantInPlace_FWD_DEFINED__ */


#ifndef __IDrawPropVariant_FWD_DEFINED__
#define __IDrawPropVariant_FWD_DEFINED__
typedef interface IDrawPropVariant IDrawPropVariant;
#endif 	/* __IDrawPropVariant_FWD_DEFINED__ */


#ifndef __IPropertyUI_FWD_DEFINED__
#define __IPropertyUI_FWD_DEFINED__
typedef interface IPropertyUI IPropertyUI;
#endif 	/* __IPropertyUI_FWD_DEFINED__ */


#ifndef __IPropVariantArray_FWD_DEFINED__
#define __IPropVariantArray_FWD_DEFINED__
typedef interface IPropVariantArray IPropVariantArray;
#endif 	/* __IPropVariantArray_FWD_DEFINED__ */


#ifndef __IPropertyDescription_FWD_DEFINED__
#define __IPropertyDescription_FWD_DEFINED__
typedef interface IPropertyDescription IPropertyDescription;
#endif 	/* __IPropertyDescription_FWD_DEFINED__ */


#ifndef __IAggregatePropertyStore_FWD_DEFINED__
#define __IAggregatePropertyStore_FWD_DEFINED__
typedef interface IAggregatePropertyStore IAggregatePropertyStore;
#endif 	/* __IAggregatePropertyStore_FWD_DEFINED__ */


#ifndef __IPropertyDescriptionList_FWD_DEFINED__
#define __IPropertyDescriptionList_FWD_DEFINED__
typedef interface IPropertyDescriptionList IPropertyDescriptionList;
#endif 	/* __IPropertyDescriptionList_FWD_DEFINED__ */


#ifndef __ICategoryProvider_FWD_DEFINED__
#define __ICategoryProvider_FWD_DEFINED__
typedef interface ICategoryProvider ICategoryProvider;
#endif 	/* __ICategoryProvider_FWD_DEFINED__ */


#ifndef __IDropTargetHelper_FWD_DEFINED__
#define __IDropTargetHelper_FWD_DEFINED__
typedef interface IDropTargetHelper IDropTargetHelper;
#endif 	/* __IDropTargetHelper_FWD_DEFINED__ */


#ifndef __IDragSourceHelper_FWD_DEFINED__
#define __IDragSourceHelper_FWD_DEFINED__
typedef interface IDragSourceHelper IDragSourceHelper;
#endif 	/* __IDragSourceHelper_FWD_DEFINED__ */


#ifndef __ICategorizer_FWD_DEFINED__
#define __ICategorizer_FWD_DEFINED__
typedef interface ICategorizer ICategorizer;
#endif 	/* __ICategorizer_FWD_DEFINED__ */


#ifndef __IDropTargetFactory_FWD_DEFINED__
#define __IDropTargetFactory_FWD_DEFINED__
typedef interface IDropTargetFactory IDropTargetFactory;
#endif 	/* __IDropTargetFactory_FWD_DEFINED__ */


#ifndef __IShellLinkA_FWD_DEFINED__
#define __IShellLinkA_FWD_DEFINED__
typedef interface IShellLinkA IShellLinkA;
#endif 	/* __IShellLinkA_FWD_DEFINED__ */


#ifndef __IShellLinkW_FWD_DEFINED__
#define __IShellLinkW_FWD_DEFINED__
typedef interface IShellLinkW IShellLinkW;
#endif 	/* __IShellLinkW_FWD_DEFINED__ */


#ifndef __IResolveShellLink_FWD_DEFINED__
#define __IResolveShellLink_FWD_DEFINED__
typedef interface IResolveShellLink IResolveShellLink;
#endif 	/* __IResolveShellLink_FWD_DEFINED__ */


#ifndef __IResolveShellLink2_FWD_DEFINED__
#define __IResolveShellLink2_FWD_DEFINED__
typedef interface IResolveShellLink2 IResolveShellLink2;
#endif 	/* __IResolveShellLink2_FWD_DEFINED__ */


#ifndef __IActionProgressDialog_FWD_DEFINED__
#define __IActionProgressDialog_FWD_DEFINED__
typedef interface IActionProgressDialog IActionProgressDialog;
#endif 	/* __IActionProgressDialog_FWD_DEFINED__ */


#ifndef __IProgressImage_FWD_DEFINED__
#define __IProgressImage_FWD_DEFINED__
typedef interface IProgressImage IProgressImage;
#endif 	/* __IProgressImage_FWD_DEFINED__ */


#ifndef __IHWNotificationHandler_FWD_DEFINED__
#define __IHWNotificationHandler_FWD_DEFINED__
typedef interface IHWNotificationHandler IHWNotificationHandler;
#endif 	/* __IHWNotificationHandler_FWD_DEFINED__ */


#ifndef __IHWEventHandler_FWD_DEFINED__
#define __IHWEventHandler_FWD_DEFINED__
typedef interface IHWEventHandler IHWEventHandler;
#endif 	/* __IHWEventHandler_FWD_DEFINED__ */


#ifndef __IQueryCancelAutoPlay_FWD_DEFINED__
#define __IQueryCancelAutoPlay_FWD_DEFINED__
typedef interface IQueryCancelAutoPlay IQueryCancelAutoPlay;
#endif 	/* __IQueryCancelAutoPlay_FWD_DEFINED__ */


#ifndef __IDynamicHWHandler_FWD_DEFINED__
#define __IDynamicHWHandler_FWD_DEFINED__
typedef interface IDynamicHWHandler IDynamicHWHandler;
#endif 	/* __IDynamicHWHandler_FWD_DEFINED__ */


#ifndef __IActionProgress_FWD_DEFINED__
#define __IActionProgress_FWD_DEFINED__
typedef interface IActionProgress IActionProgress;
#endif 	/* __IActionProgress_FWD_DEFINED__ */


#ifndef __IShellExtInit_FWD_DEFINED__
#define __IShellExtInit_FWD_DEFINED__
typedef interface IShellExtInit IShellExtInit;
#endif 	/* __IShellExtInit_FWD_DEFINED__ */


#ifndef __IShellPropSheetExt_FWD_DEFINED__
#define __IShellPropSheetExt_FWD_DEFINED__
typedef interface IShellPropSheetExt IShellPropSheetExt;
#endif 	/* __IShellPropSheetExt_FWD_DEFINED__ */


#ifndef __IShellPropSheetExt2_FWD_DEFINED__
#define __IShellPropSheetExt2_FWD_DEFINED__
typedef interface IShellPropSheetExt2 IShellPropSheetExt2;
#endif 	/* __IShellPropSheetExt2_FWD_DEFINED__ */


#ifndef __IRemoteComputer_FWD_DEFINED__
#define __IRemoteComputer_FWD_DEFINED__
typedef interface IRemoteComputer IRemoteComputer;
#endif 	/* __IRemoteComputer_FWD_DEFINED__ */


#ifndef __IUserNotification_FWD_DEFINED__
#define __IUserNotification_FWD_DEFINED__
typedef interface IUserNotification IUserNotification;
#endif 	/* __IUserNotification_FWD_DEFINED__ */


#ifndef __IItemNameLimits_FWD_DEFINED__
#define __IItemNameLimits_FWD_DEFINED__
typedef interface IItemNameLimits IItemNameLimits;
#endif 	/* __IItemNameLimits_FWD_DEFINED__ */


#ifndef __IExtractImage_FWD_DEFINED__
#define __IExtractImage_FWD_DEFINED__
typedef interface IExtractImage IExtractImage;
#endif 	/* __IExtractImage_FWD_DEFINED__ */


#ifndef __IExtractImage2_FWD_DEFINED__
#define __IExtractImage2_FWD_DEFINED__
typedef interface IExtractImage2 IExtractImage2;
#endif 	/* __IExtractImage2_FWD_DEFINED__ */


#ifndef __IDockingWindow_FWD_DEFINED__
#define __IDockingWindow_FWD_DEFINED__
typedef interface IDockingWindow IDockingWindow;
#endif 	/* __IDockingWindow_FWD_DEFINED__ */


#ifndef __IDeskBand_FWD_DEFINED__
#define __IDeskBand_FWD_DEFINED__
typedef interface IDeskBand IDeskBand;
#endif 	/* __IDeskBand_FWD_DEFINED__ */


#ifndef __ITaskbarList_FWD_DEFINED__
#define __ITaskbarList_FWD_DEFINED__
typedef interface ITaskbarList ITaskbarList;
#endif 	/* __ITaskbarList_FWD_DEFINED__ */


#ifndef __ITaskbarList2_FWD_DEFINED__
#define __ITaskbarList2_FWD_DEFINED__
typedef interface ITaskbarList2 ITaskbarList2;
#endif 	/* __ITaskbarList2_FWD_DEFINED__ */


#ifndef __ICDBurn_FWD_DEFINED__
#define __ICDBurn_FWD_DEFINED__
typedef interface ICDBurn ICDBurn;
#endif 	/* __ICDBurn_FWD_DEFINED__ */


#ifndef __IWizardSite_FWD_DEFINED__
#define __IWizardSite_FWD_DEFINED__
typedef interface IWizardSite IWizardSite;
#endif 	/* __IWizardSite_FWD_DEFINED__ */


#ifndef __IWizardExtension_FWD_DEFINED__
#define __IWizardExtension_FWD_DEFINED__
typedef interface IWizardExtension IWizardExtension;
#endif 	/* __IWizardExtension_FWD_DEFINED__ */


#ifndef __IWebWizardExtension_FWD_DEFINED__
#define __IWebWizardExtension_FWD_DEFINED__
typedef interface IWebWizardExtension IWebWizardExtension;
#endif 	/* __IWebWizardExtension_FWD_DEFINED__ */


#ifndef __IPublishingWizard_FWD_DEFINED__
#define __IPublishingWizard_FWD_DEFINED__
typedef interface IPublishingWizard IPublishingWizard;
#endif 	/* __IPublishingWizard_FWD_DEFINED__ */


#ifndef __IPublishingWizard2_FWD_DEFINED__
#define __IPublishingWizard2_FWD_DEFINED__
typedef interface IPublishingWizard2 IPublishingWizard2;
#endif 	/* __IPublishingWizard2_FWD_DEFINED__ */


#ifndef __IFolderViewHost_FWD_DEFINED__
#define __IFolderViewHost_FWD_DEFINED__
typedef interface IFolderViewHost IFolderViewHost;
#endif 	/* __IFolderViewHost_FWD_DEFINED__ */


#ifndef __IDevicePickerFolderViewHost_FWD_DEFINED__
#define __IDevicePickerFolderViewHost_FWD_DEFINED__
typedef interface IDevicePickerFolderViewHost IDevicePickerFolderViewHost;
#endif 	/* __IDevicePickerFolderViewHost_FWD_DEFINED__ */


#ifndef __IEnumObjects_FWD_DEFINED__
#define __IEnumObjects_FWD_DEFINED__
typedef interface IEnumObjects IEnumObjects;
#endif 	/* __IEnumObjects_FWD_DEFINED__ */


#ifndef __IObjectProvider_FWD_DEFINED__
#define __IObjectProvider_FWD_DEFINED__
typedef interface IObjectProvider IObjectProvider;
#endif 	/* __IObjectProvider_FWD_DEFINED__ */


#ifndef __INamespaceWalkCB_FWD_DEFINED__
#define __INamespaceWalkCB_FWD_DEFINED__
typedef interface INamespaceWalkCB INamespaceWalkCB;
#endif 	/* __INamespaceWalkCB_FWD_DEFINED__ */


#ifndef __INamespaceWalkCB2_FWD_DEFINED__
#define __INamespaceWalkCB2_FWD_DEFINED__
typedef interface INamespaceWalkCB2 INamespaceWalkCB2;
#endif 	/* __INamespaceWalkCB2_FWD_DEFINED__ */


#ifndef __INamespaceWalk_FWD_DEFINED__
#define __INamespaceWalk_FWD_DEFINED__
typedef interface INamespaceWalk INamespaceWalk;
#endif 	/* __INamespaceWalk_FWD_DEFINED__ */


#ifndef __IAutoCompleteDropDown_FWD_DEFINED__
#define __IAutoCompleteDropDown_FWD_DEFINED__
typedef interface IAutoCompleteDropDown IAutoCompleteDropDown;
#endif 	/* __IAutoCompleteDropDown_FWD_DEFINED__ */


#ifndef __IModalWindow_FWD_DEFINED__
#define __IModalWindow_FWD_DEFINED__
typedef interface IModalWindow IModalWindow;
#endif 	/* __IModalWindow_FWD_DEFINED__ */


#ifndef __IPassportWizard_FWD_DEFINED__
#define __IPassportWizard_FWD_DEFINED__
typedef interface IPassportWizard IPassportWizard;
#endif 	/* __IPassportWizard_FWD_DEFINED__ */


#ifndef __ICDBurnExt_FWD_DEFINED__
#define __ICDBurnExt_FWD_DEFINED__
typedef interface ICDBurnExt ICDBurnExt;
#endif 	/* __ICDBurnExt_FWD_DEFINED__ */


#ifndef __IDVGetEnum_FWD_DEFINED__
#define __IDVGetEnum_FWD_DEFINED__
typedef interface IDVGetEnum IDVGetEnum;
#endif 	/* __IDVGetEnum_FWD_DEFINED__ */


#ifndef __IInsertItem_FWD_DEFINED__
#define __IInsertItem_FWD_DEFINED__
typedef interface IInsertItem IInsertItem;
#endif 	/* __IInsertItem_FWD_DEFINED__ */


#ifndef __IDeskBar_FWD_DEFINED__
#define __IDeskBar_FWD_DEFINED__
typedef interface IDeskBar IDeskBar;
#endif 	/* __IDeskBar_FWD_DEFINED__ */


#ifndef __IMenuBand_FWD_DEFINED__
#define __IMenuBand_FWD_DEFINED__
typedef interface IMenuBand IMenuBand;
#endif 	/* __IMenuBand_FWD_DEFINED__ */


#ifndef __IFolderBandPriv_FWD_DEFINED__
#define __IFolderBandPriv_FWD_DEFINED__
typedef interface IFolderBandPriv IFolderBandPriv;
#endif 	/* __IFolderBandPriv_FWD_DEFINED__ */


#ifndef __IBandSite_FWD_DEFINED__
#define __IBandSite_FWD_DEFINED__
typedef interface IBandSite IBandSite;
#endif 	/* __IBandSite_FWD_DEFINED__ */


#ifndef __IRegTreeItem_FWD_DEFINED__
#define __IRegTreeItem_FWD_DEFINED__
typedef interface IRegTreeItem IRegTreeItem;
#endif 	/* __IRegTreeItem_FWD_DEFINED__ */


#ifndef __IMenuPopup_FWD_DEFINED__
#define __IMenuPopup_FWD_DEFINED__
typedef interface IMenuPopup IMenuPopup;
#endif 	/* __IMenuPopup_FWD_DEFINED__ */


#ifndef __IImageRecompress_FWD_DEFINED__
#define __IImageRecompress_FWD_DEFINED__
typedef interface IImageRecompress IImageRecompress;
#endif 	/* __IImageRecompress_FWD_DEFINED__ */


#ifndef __IDefViewSafety_FWD_DEFINED__
#define __IDefViewSafety_FWD_DEFINED__
typedef interface IDefViewSafety IDefViewSafety;
#endif 	/* __IDefViewSafety_FWD_DEFINED__ */


#ifndef __IContextMenuSite_FWD_DEFINED__
#define __IContextMenuSite_FWD_DEFINED__
typedef interface IContextMenuSite IContextMenuSite;
#endif 	/* __IContextMenuSite_FWD_DEFINED__ */


#ifndef __IEnumKeywords_FWD_DEFINED__
#define __IEnumKeywords_FWD_DEFINED__
typedef interface IEnumKeywords IEnumKeywords;
#endif 	/* __IEnumKeywords_FWD_DEFINED__ */


#ifndef __IKeywordList_FWD_DEFINED__
#define __IKeywordList_FWD_DEFINED__
typedef interface IKeywordList IKeywordList;
#endif 	/* __IKeywordList_FWD_DEFINED__ */


#ifndef __IModalKeywordEditor_FWD_DEFINED__
#define __IModalKeywordEditor_FWD_DEFINED__
typedef interface IModalKeywordEditor IModalKeywordEditor;
#endif 	/* __IModalKeywordEditor_FWD_DEFINED__ */


#ifndef __IDataConsumerNotify_FWD_DEFINED__
#define __IDataConsumerNotify_FWD_DEFINED__
typedef interface IDataConsumerNotify IDataConsumerNotify;
#endif 	/* __IDataConsumerNotify_FWD_DEFINED__ */


#ifndef __IDataSourceScheduler_FWD_DEFINED__
#define __IDataSourceScheduler_FWD_DEFINED__
typedef interface IDataSourceScheduler IDataSourceScheduler;
#endif 	/* __IDataSourceScheduler_FWD_DEFINED__ */


#ifndef __IModuleDataSource_FWD_DEFINED__
#define __IModuleDataSource_FWD_DEFINED__
typedef interface IModuleDataSource IModuleDataSource;
#endif 	/* __IModuleDataSource_FWD_DEFINED__ */


#ifndef __IOpenFile_FWD_DEFINED__
#define __IOpenFile_FWD_DEFINED__
typedef interface IOpenFile IOpenFile;
#endif 	/* __IOpenFile_FWD_DEFINED__ */


#ifndef __IFileDialogEvents_FWD_DEFINED__
#define __IFileDialogEvents_FWD_DEFINED__
typedef interface IFileDialogEvents IFileDialogEvents;
#endif 	/* __IFileDialogEvents_FWD_DEFINED__ */


#ifndef __IFileDialog_FWD_DEFINED__
#define __IFileDialog_FWD_DEFINED__
typedef interface IFileDialog IFileDialog;
#endif 	/* __IFileDialog_FWD_DEFINED__ */


#ifndef __IFileSaveDialog_FWD_DEFINED__
#define __IFileSaveDialog_FWD_DEFINED__
typedef interface IFileSaveDialog IFileSaveDialog;
#endif 	/* __IFileSaveDialog_FWD_DEFINED__ */


#ifndef __IFileOpenDialog_FWD_DEFINED__
#define __IFileOpenDialog_FWD_DEFINED__
typedef interface IFileOpenDialog IFileOpenDialog;
#endif 	/* __IFileOpenDialog_FWD_DEFINED__ */


#ifndef __IFileDialogInk_FWD_DEFINED__
#define __IFileDialogInk_FWD_DEFINED__
typedef interface IFileDialogInk IFileDialogInk;
#endif 	/* __IFileDialogInk_FWD_DEFINED__ */


#ifndef __IFileDialogCustomize_FWD_DEFINED__
#define __IFileDialogCustomize_FWD_DEFINED__
typedef interface IFileDialogCustomize IFileDialogCustomize;
#endif 	/* __IFileDialogCustomize_FWD_DEFINED__ */


#ifndef __IFileDialogControlEvents_FWD_DEFINED__
#define __IFileDialogControlEvents_FWD_DEFINED__
typedef interface IFileDialogControlEvents IFileDialogControlEvents;
#endif 	/* __IFileDialogControlEvents_FWD_DEFINED__ */


#ifndef __IDelegateFolder_FWD_DEFINED__
#define __IDelegateFolder_FWD_DEFINED__
typedef interface IDelegateFolder IDelegateFolder;
#endif 	/* __IDelegateFolder_FWD_DEFINED__ */


#ifndef __IBrowserFrameOptions_FWD_DEFINED__
#define __IBrowserFrameOptions_FWD_DEFINED__
typedef interface IBrowserFrameOptions IBrowserFrameOptions;
#endif 	/* __IBrowserFrameOptions_FWD_DEFINED__ */


#ifndef __IShellMenuCallback_FWD_DEFINED__
#define __IShellMenuCallback_FWD_DEFINED__
typedef interface IShellMenuCallback IShellMenuCallback;
#endif 	/* __IShellMenuCallback_FWD_DEFINED__ */


#ifndef __IShellMenu_FWD_DEFINED__
#define __IShellMenu_FWD_DEFINED__
typedef interface IShellMenu IShellMenu;
#endif 	/* __IShellMenu_FWD_DEFINED__ */


#ifndef __IPersistSerializedPropStorage_FWD_DEFINED__
#define __IPersistSerializedPropStorage_FWD_DEFINED__
typedef interface IPersistSerializedPropStorage IPersistSerializedPropStorage;
#endif 	/* __IPersistSerializedPropStorage_FWD_DEFINED__ */


#ifndef __IPlaylistEditor_FWD_DEFINED__
#define __IPlaylistEditor_FWD_DEFINED__
typedef interface IPlaylistEditor IPlaylistEditor;
#endif 	/* __IPlaylistEditor_FWD_DEFINED__ */


#ifndef __IFolderInformation_FWD_DEFINED__
#define __IFolderInformation_FWD_DEFINED__
typedef interface IFolderInformation IFolderInformation;
#endif 	/* __IFolderInformation_FWD_DEFINED__ */


#ifndef __IShareManager_FWD_DEFINED__
#define __IShareManager_FWD_DEFINED__
typedef interface IShareManager IShareManager;
#endif 	/* __IShareManager_FWD_DEFINED__ */


#ifndef __IEnumShareInformation_FWD_DEFINED__
#define __IEnumShareInformation_FWD_DEFINED__
typedef interface IEnumShareInformation IEnumShareInformation;
#endif 	/* __IEnumShareInformation_FWD_DEFINED__ */


#ifndef __IShareProgress_FWD_DEFINED__
#define __IShareProgress_FWD_DEFINED__
typedef interface IShareProgress IShareProgress;
#endif 	/* __IShareProgress_FWD_DEFINED__ */


#ifndef __IPreviousVersionsInfo_FWD_DEFINED__
#define __IPreviousVersionsInfo_FWD_DEFINED__
typedef interface IPreviousVersionsInfo IPreviousVersionsInfo;
#endif 	/* __IPreviousVersionsInfo_FWD_DEFINED__ */


#ifndef __IComposeWindow_FWD_DEFINED__
#define __IComposeWindow_FWD_DEFINED__
typedef interface IComposeWindow IComposeWindow;
#endif 	/* __IComposeWindow_FWD_DEFINED__ */


#ifndef __IBasketControl_FWD_DEFINED__
#define __IBasketControl_FWD_DEFINED__
typedef interface IBasketControl IBasketControl;
#endif 	/* __IBasketControl_FWD_DEFINED__ */


#ifndef __IListMakerControl_FWD_DEFINED__
#define __IListMakerControl_FWD_DEFINED__
typedef interface IListMakerControl IListMakerControl;
#endif 	/* __IListMakerControl_FWD_DEFINED__ */


#ifndef __IListMakerControlSite_FWD_DEFINED__
#define __IListMakerControlSite_FWD_DEFINED__
typedef interface IListMakerControlSite IListMakerControlSite;
#endif 	/* __IListMakerControlSite_FWD_DEFINED__ */


#ifndef __ISyncReconciliationAction_FWD_DEFINED__
#define __ISyncReconciliationAction_FWD_DEFINED__
typedef interface ISyncReconciliationAction ISyncReconciliationAction;
#endif 	/* __ISyncReconciliationAction_FWD_DEFINED__ */


#ifndef __ISyncReconciliationList_FWD_DEFINED__
#define __ISyncReconciliationList_FWD_DEFINED__
typedef interface ISyncReconciliationList ISyncReconciliationList;
#endif 	/* __ISyncReconciliationList_FWD_DEFINED__ */


#ifndef __ISyncRelationship_FWD_DEFINED__
#define __ISyncRelationship_FWD_DEFINED__
typedef interface ISyncRelationship ISyncRelationship;
#endif 	/* __ISyncRelationship_FWD_DEFINED__ */


#ifndef __IEnumSyncRelationship_FWD_DEFINED__
#define __IEnumSyncRelationship_FWD_DEFINED__
typedef interface IEnumSyncRelationship IEnumSyncRelationship;
#endif 	/* __IEnumSyncRelationship_FWD_DEFINED__ */


#ifndef __ISyncDatabaseGenerateActionsCB_FWD_DEFINED__
#define __ISyncDatabaseGenerateActionsCB_FWD_DEFINED__
typedef interface ISyncDatabaseGenerateActionsCB ISyncDatabaseGenerateActionsCB;
#endif 	/* __ISyncDatabaseGenerateActionsCB_FWD_DEFINED__ */


#ifndef __ISyncDatabase_FWD_DEFINED__
#define __ISyncDatabase_FWD_DEFINED__
typedef interface ISyncDatabase ISyncDatabase;
#endif 	/* __ISyncDatabase_FWD_DEFINED__ */


#ifndef __IRelatedItem_FWD_DEFINED__
#define __IRelatedItem_FWD_DEFINED__
typedef interface IRelatedItem IRelatedItem;
#endif 	/* __IRelatedItem_FWD_DEFINED__ */


#ifndef __IIdentityName_FWD_DEFINED__
#define __IIdentityName_FWD_DEFINED__
typedef interface IIdentityName IIdentityName;
#endif 	/* __IIdentityName_FWD_DEFINED__ */


#ifndef __ICurrentItem_FWD_DEFINED__
#define __ICurrentItem_FWD_DEFINED__
typedef interface ICurrentItem ICurrentItem;
#endif 	/* __ICurrentItem_FWD_DEFINED__ */


#ifndef __IStorageItem_FWD_DEFINED__
#define __IStorageItem_FWD_DEFINED__
typedef interface IStorageItem IStorageItem;
#endif 	/* __IStorageItem_FWD_DEFINED__ */


#ifndef __IInitializeWithStream_FWD_DEFINED__
#define __IInitializeWithStream_FWD_DEFINED__
typedef interface IInitializeWithStream IInitializeWithStream;
#endif 	/* __IInitializeWithStream_FWD_DEFINED__ */


#ifndef __ISafeCommit_FWD_DEFINED__
#define __ISafeCommit_FWD_DEFINED__
typedef interface ISafeCommit ISafeCommit;
#endif 	/* __ISafeCommit_FWD_DEFINED__ */


#ifndef __IBandHost_FWD_DEFINED__
#define __IBandHost_FWD_DEFINED__
typedef interface IBandHost IBandHost;
#endif 	/* __IBandHost_FWD_DEFINED__ */


#ifndef __INewWindowManager_FWD_DEFINED__
#define __INewWindowManager_FWD_DEFINED__
typedef interface INewWindowManager INewWindowManager;
#endif 	/* __INewWindowManager_FWD_DEFINED__ */


#ifndef __INavBar_FWD_DEFINED__
#define __INavBar_FWD_DEFINED__
typedef interface INavBar INavBar;
#endif 	/* __INavBar_FWD_DEFINED__ */


#ifndef __QueryCancelAutoPlay_FWD_DEFINED__
#define __QueryCancelAutoPlay_FWD_DEFINED__

#ifdef __cplusplus
typedef class QueryCancelAutoPlay QueryCancelAutoPlay;
#else
typedef struct QueryCancelAutoPlay QueryCancelAutoPlay;
#endif /* __cplusplus */

#endif 	/* __QueryCancelAutoPlay_FWD_DEFINED__ */


#ifndef __ImageProperties_FWD_DEFINED__
#define __ImageProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageProperties ImageProperties;
#else
typedef struct ImageProperties ImageProperties;
#endif /* __cplusplus */

#endif 	/* __ImageProperties_FWD_DEFINED__ */


#ifndef __PropertiesUI_FWD_DEFINED__
#define __PropertiesUI_FWD_DEFINED__

#ifdef __cplusplus
typedef class PropertiesUI PropertiesUI;
#else
typedef struct PropertiesUI PropertiesUI;
#endif /* __cplusplus */

#endif 	/* __PropertiesUI_FWD_DEFINED__ */


#ifndef __UserNotification_FWD_DEFINED__
#define __UserNotification_FWD_DEFINED__

#ifdef __cplusplus
typedef class UserNotification UserNotification;
#else
typedef struct UserNotification UserNotification;
#endif /* __cplusplus */

#endif 	/* __UserNotification_FWD_DEFINED__ */


#ifndef __CDBurn_FWD_DEFINED__
#define __CDBurn_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDBurn CDBurn;
#else
typedef struct CDBurn CDBurn;
#endif /* __cplusplus */

#endif 	/* __CDBurn_FWD_DEFINED__ */


#ifndef __TaskbarList_FWD_DEFINED__
#define __TaskbarList_FWD_DEFINED__

#ifdef __cplusplus
typedef class TaskbarList TaskbarList;
#else
typedef struct TaskbarList TaskbarList;
#endif /* __cplusplus */

#endif 	/* __TaskbarList_FWD_DEFINED__ */


#ifndef __WebWizardHost_FWD_DEFINED__
#define __WebWizardHost_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebWizardHost WebWizardHost;
#else
typedef struct WebWizardHost WebWizardHost;
#endif /* __cplusplus */

#endif 	/* __WebWizardHost_FWD_DEFINED__ */


#ifndef __PublishDropTarget_FWD_DEFINED__
#define __PublishDropTarget_FWD_DEFINED__

#ifdef __cplusplus
typedef class PublishDropTarget PublishDropTarget;
#else
typedef struct PublishDropTarget PublishDropTarget;
#endif /* __cplusplus */

#endif 	/* __PublishDropTarget_FWD_DEFINED__ */


#ifndef __PublishingWizard_FWD_DEFINED__
#define __PublishingWizard_FWD_DEFINED__

#ifdef __cplusplus
typedef class PublishingWizard PublishingWizard;
#else
typedef struct PublishingWizard PublishingWizard;
#endif /* __cplusplus */

#endif 	/* __PublishingWizard_FWD_DEFINED__ */


#ifndef __InternetPrintOrdering_FWD_DEFINED__
#define __InternetPrintOrdering_FWD_DEFINED__

#ifdef __cplusplus
typedef class InternetPrintOrdering InternetPrintOrdering;
#else
typedef struct InternetPrintOrdering InternetPrintOrdering;
#endif /* __cplusplus */

#endif 	/* __InternetPrintOrdering_FWD_DEFINED__ */


#ifndef __FolderViewHost_FWD_DEFINED__
#define __FolderViewHost_FWD_DEFINED__

#ifdef __cplusplus
typedef class FolderViewHost FolderViewHost;
#else
typedef struct FolderViewHost FolderViewHost;
#endif /* __cplusplus */

#endif 	/* __FolderViewHost_FWD_DEFINED__ */


#ifndef __ImageRecompress_FWD_DEFINED__
#define __ImageRecompress_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageRecompress ImageRecompress;
#else
typedef struct ImageRecompress ImageRecompress;
#endif /* __cplusplus */

#endif 	/* __ImageRecompress_FWD_DEFINED__ */


#ifndef __TrayBandSiteService_FWD_DEFINED__
#define __TrayBandSiteService_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrayBandSiteService TrayBandSiteService;
#else
typedef struct TrayBandSiteService TrayBandSiteService;
#endif /* __cplusplus */

#endif 	/* __TrayBandSiteService_FWD_DEFINED__ */


#ifndef __PassportWizard_FWD_DEFINED__
#define __PassportWizard_FWD_DEFINED__

#ifdef __cplusplus
typedef class PassportWizard PassportWizard;
#else
typedef struct PassportWizard PassportWizard;
#endif /* __cplusplus */

#endif 	/* __PassportWizard_FWD_DEFINED__ */


#ifndef __DocPropShellExtension_FWD_DEFINED__
#define __DocPropShellExtension_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropShellExtension DocPropShellExtension;
#else
typedef struct DocPropShellExtension DocPropShellExtension;
#endif /* __cplusplus */

#endif 	/* __DocPropShellExtension_FWD_DEFINED__ */


#ifndef __DocPropEditBoxControl_FWD_DEFINED__
#define __DocPropEditBoxControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropEditBoxControl DocPropEditBoxControl;
#else
typedef struct DocPropEditBoxControl DocPropEditBoxControl;
#endif /* __cplusplus */

#endif 	/* __DocPropEditBoxControl_FWD_DEFINED__ */


#ifndef __DocPropMLEditBoxControl_FWD_DEFINED__
#define __DocPropMLEditBoxControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropMLEditBoxControl DocPropMLEditBoxControl;
#else
typedef struct DocPropMLEditBoxControl DocPropMLEditBoxControl;
#endif /* __cplusplus */

#endif 	/* __DocPropMLEditBoxControl_FWD_DEFINED__ */


#ifndef __DocPropDropListComboControl_FWD_DEFINED__
#define __DocPropDropListComboControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropDropListComboControl DocPropDropListComboControl;
#else
typedef struct DocPropDropListComboControl DocPropDropListComboControl;
#endif /* __cplusplus */

#endif 	/* __DocPropDropListComboControl_FWD_DEFINED__ */


#ifndef __DocPropCalendarControl_FWD_DEFINED__
#define __DocPropCalendarControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropCalendarControl DocPropCalendarControl;
#else
typedef struct DocPropCalendarControl DocPropCalendarControl;
#endif /* __cplusplus */

#endif 	/* __DocPropCalendarControl_FWD_DEFINED__ */


#ifndef __DocPropDrawRatingControl_FWD_DEFINED__
#define __DocPropDrawRatingControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropDrawRatingControl DocPropDrawRatingControl;
#else
typedef struct DocPropDrawRatingControl DocPropDrawRatingControl;
#endif /* __cplusplus */

#endif 	/* __DocPropDrawRatingControl_FWD_DEFINED__ */


#ifndef __DocPropEditRatingControl_FWD_DEFINED__
#define __DocPropEditRatingControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropEditRatingControl DocPropEditRatingControl;
#else
typedef struct DocPropEditRatingControl DocPropEditRatingControl;
#endif /* __cplusplus */

#endif 	/* __DocPropEditRatingControl_FWD_DEFINED__ */


#ifndef __DocPropDrawPercentFullControl_FWD_DEFINED__
#define __DocPropDrawPercentFullControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropDrawPercentFullControl DocPropDrawPercentFullControl;
#else
typedef struct DocPropDrawPercentFullControl DocPropDrawPercentFullControl;
#endif /* __cplusplus */

#endif 	/* __DocPropDrawPercentFullControl_FWD_DEFINED__ */


#ifndef __DocPropMultiValuePropertyControl_FWD_DEFINED__
#define __DocPropMultiValuePropertyControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocPropMultiValuePropertyControl DocPropMultiValuePropertyControl;
#else
typedef struct DocPropMultiValuePropertyControl DocPropMultiValuePropertyControl;
#endif /* __cplusplus */

#endif 	/* __DocPropMultiValuePropertyControl_FWD_DEFINED__ */


#ifndef __StickyNoteDisplayControl_FWD_DEFINED__
#define __StickyNoteDisplayControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class StickyNoteDisplayControl StickyNoteDisplayControl;
#else
typedef struct StickyNoteDisplayControl StickyNoteDisplayControl;
#endif /* __cplusplus */

#endif 	/* __StickyNoteDisplayControl_FWD_DEFINED__ */


#ifndef __ShellItem_FWD_DEFINED__
#define __ShellItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellItem ShellItem;
#else
typedef struct ShellItem ShellItem;
#endif /* __cplusplus */

#endif 	/* __ShellItem_FWD_DEFINED__ */


#ifndef __NamespaceWalker_FWD_DEFINED__
#define __NamespaceWalker_FWD_DEFINED__

#ifdef __cplusplus
typedef class NamespaceWalker NamespaceWalker;
#else
typedef struct NamespaceWalker NamespaceWalker;
#endif /* __cplusplus */

#endif 	/* __NamespaceWalker_FWD_DEFINED__ */


#ifndef __KeywordList_FWD_DEFINED__
#define __KeywordList_FWD_DEFINED__

#ifdef __cplusplus
typedef class KeywordList KeywordList;
#else
typedef struct KeywordList KeywordList;
#endif /* __cplusplus */

#endif 	/* __KeywordList_FWD_DEFINED__ */


#ifndef __ModalKeywordEditor_FWD_DEFINED__
#define __ModalKeywordEditor_FWD_DEFINED__

#ifdef __cplusplus
typedef class ModalKeywordEditor ModalKeywordEditor;
#else
typedef struct ModalKeywordEditor ModalKeywordEditor;
#endif /* __cplusplus */

#endif 	/* __ModalKeywordEditor_FWD_DEFINED__ */


#ifndef __FileOperation_FWD_DEFINED__
#define __FileOperation_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileOperation FileOperation;
#else
typedef struct FileOperation FileOperation;
#endif /* __cplusplus */

#endif 	/* __FileOperation_FWD_DEFINED__ */


#ifndef __FileOpenDialog_FWD_DEFINED__
#define __FileOpenDialog_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileOpenDialog FileOpenDialog;
#else
typedef struct FileOpenDialog FileOpenDialog;
#endif /* __cplusplus */

#endif 	/* __FileOpenDialog_FWD_DEFINED__ */


#ifndef __FileSaveDialog_FWD_DEFINED__
#define __FileSaveDialog_FWD_DEFINED__

#ifdef __cplusplus
typedef class FileSaveDialog FileSaveDialog;
#else
typedef struct FileSaveDialog FileSaveDialog;
#endif /* __cplusplus */

#endif 	/* __FileSaveDialog_FWD_DEFINED__ */


#ifndef __PropertyStore_FWD_DEFINED__
#define __PropertyStore_FWD_DEFINED__

#ifdef __cplusplus
typedef class PropertyStore PropertyStore;
#else
typedef struct PropertyStore PropertyStore;
#endif /* __cplusplus */

#endif 	/* __PropertyStore_FWD_DEFINED__ */


#ifndef __PlaylistEditor_FWD_DEFINED__
#define __PlaylistEditor_FWD_DEFINED__

#ifdef __cplusplus
typedef class PlaylistEditor PlaylistEditor;
#else
typedef struct PlaylistEditor PlaylistEditor;
#endif /* __cplusplus */

#endif 	/* __PlaylistEditor_FWD_DEFINED__ */


#ifndef __FolderInformation_FWD_DEFINED__
#define __FolderInformation_FWD_DEFINED__

#ifdef __cplusplus
typedef class FolderInformation FolderInformation;
#else
typedef struct FolderInformation FolderInformation;
#endif /* __cplusplus */

#endif 	/* __FolderInformation_FWD_DEFINED__ */


#ifndef __FSCopyHandler_FWD_DEFINED__
#define __FSCopyHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class FSCopyHandler FSCopyHandler;
#else
typedef struct FSCopyHandler FSCopyHandler;
#endif /* __cplusplus */

#endif 	/* __FSCopyHandler_FWD_DEFINED__ */


#ifndef __ShareManager_FWD_DEFINED__
#define __ShareManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShareManager ShareManager;
#else
typedef struct ShareManager ShareManager;
#endif /* __cplusplus */

#endif 	/* __ShareManager_FWD_DEFINED__ */


#ifndef __PreviousVersions_FWD_DEFINED__
#define __PreviousVersions_FWD_DEFINED__

#ifdef __cplusplus
typedef class PreviousVersions PreviousVersions;
#else
typedef struct PreviousVersions PreviousVersions;
#endif /* __cplusplus */

#endif 	/* __PreviousVersions_FWD_DEFINED__ */


#ifndef __LaunchComposeWindow_FWD_DEFINED__
#define __LaunchComposeWindow_FWD_DEFINED__

#ifdef __cplusplus
typedef class LaunchComposeWindow LaunchComposeWindow;
#else
typedef struct LaunchComposeWindow LaunchComposeWindow;
#endif /* __cplusplus */

#endif 	/* __LaunchComposeWindow_FWD_DEFINED__ */


#ifndef __BasketControl_FWD_DEFINED__
#define __BasketControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class BasketControl BasketControl;
#else
typedef struct BasketControl BasketControl;
#endif /* __cplusplus */

#endif 	/* __BasketControl_FWD_DEFINED__ */


#ifndef __ListMakerControl_FWD_DEFINED__
#define __ListMakerControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ListMakerControl ListMakerControl;
#else
typedef struct ListMakerControl ListMakerControl;
#endif /* __cplusplus */

#endif 	/* __ListMakerControl_FWD_DEFINED__ */


#ifndef __SyncDatabase_FWD_DEFINED__
#define __SyncDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class SyncDatabase SyncDatabase;
#else
typedef struct SyncDatabase SyncDatabase;
#endif /* __cplusplus */

#endif 	/* __SyncDatabase_FWD_DEFINED__ */


#ifndef __DevicePickerDialog_FWD_DEFINED__
#define __DevicePickerDialog_FWD_DEFINED__

#ifdef __cplusplus
typedef class DevicePickerDialog DevicePickerDialog;
#else
typedef struct DevicePickerDialog DevicePickerDialog;
#endif /* __cplusplus */

#endif 	/* __DevicePickerDialog_FWD_DEFINED__ */


#ifndef __DevicePickerFolderViewHost_FWD_DEFINED__
#define __DevicePickerFolderViewHost_FWD_DEFINED__

#ifdef __cplusplus
typedef class DevicePickerFolderViewHost DevicePickerFolderViewHost;
#else
typedef struct DevicePickerFolderViewHost DevicePickerFolderViewHost;
#endif /* __cplusplus */

#endif 	/* __DevicePickerFolderViewHost_FWD_DEFINED__ */


#ifndef __NetworkConnections_FWD_DEFINED__
#define __NetworkConnections_FWD_DEFINED__

#ifdef __cplusplus
typedef class NetworkConnections NetworkConnections;
#else
typedef struct NetworkConnections NetworkConnections;
#endif /* __cplusplus */

#endif 	/* __NetworkConnections_FWD_DEFINED__ */


#ifndef __ScheduledTasks_FWD_DEFINED__
#define __ScheduledTasks_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScheduledTasks ScheduledTasks;
#else
typedef struct ScheduledTasks ScheduledTasks;
#endif /* __cplusplus */

#endif 	/* __ScheduledTasks_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "oaidl.h"
#include "shtypes.h"
#include "servprov.h"
#include "comcat.h"
#include "propidl.h"
#include "prsht.h"
#include "msxml.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_shobjidl_0000 */
/* [local] */ 

#ifndef _WINRESRC_
#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#else
#if (_WIN32_IE < 0x0400) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0500)
#error _WIN32_IE setting conflicts with _WIN32_WINNT setting
#endif
#endif
#endif
#ifndef SHSTDAPI
#if defined(_SHELL32_)
#define SHSTDAPI          STDAPI
#define SHSTDAPI_(type)   STDAPI_(type)
#else
#define SHSTDAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define SHSTDAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#endif
#endif // SHSTDAPI


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0000_v0_0_s_ifspec;

#ifndef __IPersistFolder_INTERFACE_DEFINED__
#define __IPersistFolder_INTERFACE_DEFINED__

/* interface IPersistFolder */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPersistFolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214EA-0000-0000-C000-000000000046")
    IPersistFolder : public IPersist
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ PCIDLIST_ABSOLUTE pidl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistFolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistFolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistFolder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistFolder * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPersistFolder * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidl);
        
        END_INTERFACE
    } IPersistFolderVtbl;

    interface IPersistFolder
    {
        CONST_VTBL struct IPersistFolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistFolder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPersistFolder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPersistFolder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPersistFolder_GetClassID(This,pClassID)	\
    ( (This)->lpVtbl -> GetClassID(This,pClassID) ) 


#define IPersistFolder_Initialize(This,pidl)	\
    ( (This)->lpVtbl -> Initialize(This,pidl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistFolder_Initialize_Proxy( 
    IPersistFolder * This,
    /* [in] */ PCIDLIST_ABSOLUTE pidl);


void __RPC_STUB IPersistFolder_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistFolder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0200 */
/* [local] */ 

typedef IPersistFolder *LPPERSISTFOLDER;

#if (_WIN32_IE >= 0x0400)
#define IRTIR_TASK_NOT_RUNNING   0
#define IRTIR_TASK_RUNNING       1
#define IRTIR_TASK_SUSPENDED     2
#define IRTIR_TASK_PENDING       3
#define IRTIR_TASK_FINISHED      4


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0200_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0200_v0_0_s_ifspec;

#ifndef __IRunnableTask_INTERFACE_DEFINED__
#define __IRunnableTask_INTERFACE_DEFINED__

/* interface IRunnableTask */
/* [local][object][uuid] */ 


EXTERN_C const IID IID_IRunnableTask;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85788d00-6807-11d0-b810-00c04fd706ec")
    IRunnableTask : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Kill( 
            BOOL bWait) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Suspend( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual ULONG STDMETHODCALLTYPE IsRunning( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRunnableTaskVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRunnableTask * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRunnableTask * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRunnableTask * This);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            IRunnableTask * This);
        
        HRESULT ( STDMETHODCALLTYPE *Kill )( 
            IRunnableTask * This,
            BOOL bWait);
        
        HRESULT ( STDMETHODCALLTYPE *Suspend )( 
            IRunnableTask * This);
        
        HRESULT ( STDMETHODCALLTYPE *Resume )( 
            IRunnableTask * This);
        
        ULONG ( STDMETHODCALLTYPE *IsRunning )( 
            IRunnableTask * This);
        
        END_INTERFACE
    } IRunnableTaskVtbl;

    interface IRunnableTask
    {
        CONST_VTBL struct IRunnableTaskVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRunnableTask_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRunnableTask_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRunnableTask_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRunnableTask_Run(This)	\
    ( (This)->lpVtbl -> Run(This) ) 

#define IRunnableTask_Kill(This,bWait)	\
    ( (This)->lpVtbl -> Kill(This,bWait) ) 

#define IRunnableTask_Suspend(This)	\
    ( (This)->lpVtbl -> Suspend(This) ) 

#define IRunnableTask_Resume(This)	\
    ( (This)->lpVtbl -> Resume(This) ) 

#define IRunnableTask_IsRunning(This)	\
    ( (This)->lpVtbl -> IsRunning(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRunnableTask_Run_Proxy( 
    IRunnableTask * This);


void __RPC_STUB IRunnableTask_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunnableTask_Kill_Proxy( 
    IRunnableTask * This,
    BOOL bWait);


void __RPC_STUB IRunnableTask_Kill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunnableTask_Suspend_Proxy( 
    IRunnableTask * This);


void __RPC_STUB IRunnableTask_Suspend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunnableTask_Resume_Proxy( 
    IRunnableTask * This);


void __RPC_STUB IRunnableTask_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


ULONG STDMETHODCALLTYPE IRunnableTask_IsRunning_Proxy( 
    IRunnableTask * This);


void __RPC_STUB IRunnableTask_IsRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRunnableTask_INTERFACE_DEFINED__ */


#ifndef __IPersistFolder2_INTERFACE_DEFINED__
#define __IPersistFolder2_INTERFACE_DEFINED__

/* interface IPersistFolder2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPersistFolder2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1AC3D9F0-175C-11d1-95BE-00609797EA4F")
    IPersistFolder2 : public IPersistFolder
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCurFolder( 
            /* [out] */ PIDLIST_ABSOLUTE *ppidl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistFolder2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistFolder2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistFolder2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistFolder2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistFolder2 * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPersistFolder2 * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurFolder )( 
            IPersistFolder2 * This,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl);
        
        END_INTERFACE
    } IPersistFolder2Vtbl;

    interface IPersistFolder2
    {
        CONST_VTBL struct IPersistFolder2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistFolder2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPersistFolder2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPersistFolder2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPersistFolder2_GetClassID(This,pClassID)	\
    ( (This)->lpVtbl -> GetClassID(This,pClassID) ) 


#define IPersistFolder2_Initialize(This,pidl)	\
    ( (This)->lpVtbl -> Initialize(This,pidl) ) 


#define IPersistFolder2_GetCurFolder(This,ppidl)	\
    ( (This)->lpVtbl -> GetCurFolder(This,ppidl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistFolder2_GetCurFolder_Proxy( 
    IPersistFolder2 * This,
    /* [out] */ PIDLIST_ABSOLUTE *ppidl);


void __RPC_STUB IPersistFolder2_GetCurFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistFolder2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0202 */
/* [local] */ 

typedef IPersistFolder2 *LPPERSISTFOLDER2;

#endif
#if (_WIN32_IE >= 0x0500)
#define CSIDL_FLAG_PFTI_TRACKTARGET CSIDL_FLAG_DONT_VERIFY
#include <pshpack8.h>
typedef struct _PERSIST_FOLDER_TARGET_INFO
    {
    PIDLIST_ABSOLUTE pidlTargetFolder;
    WCHAR szTargetParsingName[ 260 ];
    WCHAR szNetworkProvider[ 260 ];
    DWORD dwAttributes;
    int csidl;
    } 	PERSIST_FOLDER_TARGET_INFO;

#include <poppack.h>


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0202_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0202_v0_0_s_ifspec;

#ifndef __IPersistFolder3_INTERFACE_DEFINED__
#define __IPersistFolder3_INTERFACE_DEFINED__

/* interface IPersistFolder3 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPersistFolder3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CEF04FDF-FE72-11d2-87A5-00C04F6837CF")
    IPersistFolder3 : public IPersistFolder2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitializeEx( 
            /* [in] */ IBindCtx *pbc,
            /* [in] */ PCIDLIST_ABSOLUTE pidlRoot,
            /* [in] */ const PERSIST_FOLDER_TARGET_INFO *ppfti) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFolderTargetInfo( 
            /* [out] */ PERSIST_FOLDER_TARGET_INFO *ppfti) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistFolder3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistFolder3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistFolder3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistFolder3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistFolder3 * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPersistFolder3 * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurFolder )( 
            IPersistFolder3 * This,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeEx )( 
            IPersistFolder3 * This,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ PCIDLIST_ABSOLUTE pidlRoot,
            /* [in] */ const PERSIST_FOLDER_TARGET_INFO *ppfti);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolderTargetInfo )( 
            IPersistFolder3 * This,
            /* [out] */ PERSIST_FOLDER_TARGET_INFO *ppfti);
        
        END_INTERFACE
    } IPersistFolder3Vtbl;

    interface IPersistFolder3
    {
        CONST_VTBL struct IPersistFolder3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistFolder3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPersistFolder3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPersistFolder3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPersistFolder3_GetClassID(This,pClassID)	\
    ( (This)->lpVtbl -> GetClassID(This,pClassID) ) 


#define IPersistFolder3_Initialize(This,pidl)	\
    ( (This)->lpVtbl -> Initialize(This,pidl) ) 


#define IPersistFolder3_GetCurFolder(This,ppidl)	\
    ( (This)->lpVtbl -> GetCurFolder(This,ppidl) ) 


#define IPersistFolder3_InitializeEx(This,pbc,pidlRoot,ppfti)	\
    ( (This)->lpVtbl -> InitializeEx(This,pbc,pidlRoot,ppfti) ) 

#define IPersistFolder3_GetFolderTargetInfo(This,ppfti)	\
    ( (This)->lpVtbl -> GetFolderTargetInfo(This,ppfti) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistFolder3_InitializeEx_Proxy( 
    IPersistFolder3 * This,
    /* [in] */ IBindCtx *pbc,
    /* [in] */ PCIDLIST_ABSOLUTE pidlRoot,
    /* [in] */ const PERSIST_FOLDER_TARGET_INFO *ppfti);


void __RPC_STUB IPersistFolder3_InitializeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistFolder3_GetFolderTargetInfo_Proxy( 
    IPersistFolder3 * This,
    /* [out] */ PERSIST_FOLDER_TARGET_INFO *ppfti);


void __RPC_STUB IPersistFolder3_GetFolderTargetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistFolder3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0203 */
/* [local] */ 

#endif


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0203_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0203_v0_0_s_ifspec;

#ifndef __IPersistIDList_INTERFACE_DEFINED__
#define __IPersistIDList_INTERFACE_DEFINED__

/* interface IPersistIDList */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IPersistIDList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1079acfc-29bd-11d3-8e0d-00c04f6837d5")
    IPersistIDList : public IPersist
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetIDList( 
            /* [in] */ PCIDLIST_ABSOLUTE pidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIDList( 
            /* [out] */ PIDLIST_ABSOLUTE *ppidl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistIDListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistIDList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistIDList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistIDList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetClassID )( 
            IPersistIDList * This,
            /* [out] */ CLSID *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE *SetIDList )( 
            IPersistIDList * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDList )( 
            IPersistIDList * This,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl);
        
        END_INTERFACE
    } IPersistIDListVtbl;

    interface IPersistIDList
    {
        CONST_VTBL struct IPersistIDListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistIDList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPersistIDList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPersistIDList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPersistIDList_GetClassID(This,pClassID)	\
    ( (This)->lpVtbl -> GetClassID(This,pClassID) ) 


#define IPersistIDList_SetIDList(This,pidl)	\
    ( (This)->lpVtbl -> SetIDList(This,pidl) ) 

#define IPersistIDList_GetIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetIDList(This,ppidl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistIDList_SetIDList_Proxy( 
    IPersistIDList * This,
    /* [in] */ PCIDLIST_ABSOLUTE pidl);


void __RPC_STUB IPersistIDList_SetIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistIDList_GetIDList_Proxy( 
    IPersistIDList * This,
    /* [out] */ PIDLIST_ABSOLUTE *ppidl);


void __RPC_STUB IPersistIDList_GetIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistIDList_INTERFACE_DEFINED__ */


#ifndef __IEnumIDList_INTERFACE_DEFINED__
#define __IEnumIDList_INTERFACE_DEFINED__

/* interface IEnumIDList */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IEnumIDList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214F2-0000-0000-C000-000000000046")
    IEnumIDList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ PITEMID_CHILD *rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumIDList **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumIDListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumIDList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumIDList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumIDList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumIDList * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ PITEMID_CHILD *rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumIDList * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumIDList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumIDList * This,
            /* [out] */ IEnumIDList **ppenum);
        
        END_INTERFACE
    } IEnumIDListVtbl;

    interface IEnumIDList
    {
        CONST_VTBL struct IEnumIDListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumIDList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumIDList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumIDList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumIDList_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumIDList_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumIDList_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumIDList_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumIDList_Next_Proxy( 
    IEnumIDList * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ PITEMID_CHILD *rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumIDList_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumIDList_Skip_Proxy( 
    IEnumIDList * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumIDList_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumIDList_Reset_Proxy( 
    IEnumIDList * This);


void __RPC_STUB IEnumIDList_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumIDList_Clone_Proxy( 
    IEnumIDList * This,
    /* [out] */ IEnumIDList **ppenum);


void __RPC_STUB IEnumIDList_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumIDList_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0205 */
/* [local] */ 

typedef IEnumIDList *LPENUMIDLIST;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0205_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0205_v0_0_s_ifspec;

#ifndef __IEnumFullIDList_INTERFACE_DEFINED__
#define __IEnumFullIDList_INTERFACE_DEFINED__

/* interface IEnumFullIDList */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IEnumFullIDList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d0191542-7954-4908-bc06-b2360bbe45ba")
    IEnumFullIDList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ PIDLIST_ABSOLUTE *rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumFullIDList **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumFullIDListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumFullIDList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumFullIDList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumFullIDList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumFullIDList * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ PIDLIST_ABSOLUTE *rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumFullIDList * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumFullIDList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumFullIDList * This,
            /* [out] */ IEnumFullIDList **ppenum);
        
        END_INTERFACE
    } IEnumFullIDListVtbl;

    interface IEnumFullIDList
    {
        CONST_VTBL struct IEnumFullIDListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumFullIDList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumFullIDList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumFullIDList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumFullIDList_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumFullIDList_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumFullIDList_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumFullIDList_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumFullIDList_Next_Proxy( 
    IEnumFullIDList * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ PIDLIST_ABSOLUTE *rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumFullIDList_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFullIDList_Skip_Proxy( 
    IEnumFullIDList * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumFullIDList_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFullIDList_Reset_Proxy( 
    IEnumFullIDList * This);


void __RPC_STUB IEnumFullIDList_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFullIDList_Clone_Proxy( 
    IEnumFullIDList * This,
    /* [out] */ IEnumFullIDList **ppenum);


void __RPC_STUB IEnumFullIDList_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumFullIDList_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0206 */
/* [local] */ 

typedef 
enum tagSHGDN
    {	SHGDN_NORMAL	= 0,
	SHGDN_INFOLDER	= 0x1,
	SHGDN_FOREDITING	= 0x1000,
	SHGDN_FORADDRESSBAR	= 0x4000,
	SHGDN_FORPARSING	= 0x8000
    } 	SHGNO;

typedef DWORD SHGDNF;

typedef 
enum tagSHCONTF
    {	SHCONTF_FOLDERS	= 0x20,
	SHCONTF_NONFOLDERS	= 0x40,
	SHCONTF_INCLUDEHIDDEN	= 0x80,
	SHCONTF_INIT_ON_FIRST_NEXT	= 0x100,
	SHCONTF_NETPRINTERSRCH	= 0x200,
	SHCONTF_SHAREABLE	= 0x400,
	SHCONTF_STORAGE	= 0x800,
	SHCONTF_WALKTREE	= 0x1000,
	SHCONTF_FASTITEMS	= 0x2000,
	SHCONTF_FLATLIST	= 0x4000
    } 	SHCONT;

typedef DWORD SHCONTF;

#define SHCIDS_ALLFIELDS        0x80000000L
#define SHCIDS_CANONICALONLY    0x10000000L
#define SHCIDS_BITMASK          0xFFFF0000L
#define SHCIDS_COLUMNMASK       0x0000FFFFL
#define SFGAO_CANCOPY           DROPEFFECT_COPY // Objects can be copied    (0x1)
#define SFGAO_CANMOVE           DROPEFFECT_MOVE // Objects can be moved     (0x2)
#define SFGAO_CANLINK           DROPEFFECT_LINK // Objects can be linked    (0x4)
#define SFGAO_STORAGE           0x00000008L     // supports BindToObject(IID_IStorage)
#define SFGAO_CANRENAME         0x00000010L     // Objects can be renamed
#define SFGAO_CANDELETE         0x00000020L     // Objects can be deleted
#define SFGAO_HASPROPSHEET      0x00000040L     // Objects have property sheets
#define SFGAO_DROPTARGET        0x00000100L     // Objects are drop target
#define SFGAO_CAPABILITYMASK    0x00000177L
#define SFGAO_ENCRYPTED         0x00002000L     // object is encrypted (use alt color)
#define SFGAO_ISSLOW            0x00004000L     // 'slow' object
#define SFGAO_GHOSTED           0x00008000L     // ghosted icon
#define SFGAO_LINK              0x00010000L     // Shortcut (link)
#define SFGAO_SHARE             0x00020000L     // shared
#define SFGAO_READONLY          0x00040000L     // read-only
#define SFGAO_HIDDEN            0x00080000L     // hidden object
#define SFGAO_DISPLAYATTRMASK   0x000FC000L
#define SFGAO_FILESYSANCESTOR   0x10000000L     // may contain children with SFGAO_FILESYSTEM
#define SFGAO_FOLDER            0x20000000L     // support BindToObject(IID_IShellFolder)
#define SFGAO_FILESYSTEM        0x40000000L     // is a win32 file system object (file/folder/root)
#define SFGAO_HASSUBFOLDER      0x80000000L     // may contain children with SFGAO_FOLDER
#define SFGAO_CONTENTSMASK      0x80000000L
#define SFGAO_VALIDATE          0x01000000L     // invalidate cached information
#define SFGAO_REMOVABLE         0x02000000L     // is this removeable media?
#define SFGAO_COMPRESSED        0x04000000L     // Object is compressed (use alt color)
#define SFGAO_BROWSABLE         0x08000000L     // supports IShellFolder, but only implements CreateViewObject() (non-folder view)
#define SFGAO_NONENUMERATED     0x00100000L     // is a non-enumerated object
#define SFGAO_NEWCONTENT        0x00200000L     // should show bold in explorer tree
#define SFGAO_CANMONIKER        0x00400000L     // defunct
#define SFGAO_HASSTORAGE        0x00400000L     // defunct
#define SFGAO_STREAM            0x00400000L     // supports BindToObject(IID_IStream)
#define SFGAO_STORAGEANCESTOR   0x00800000L     // may contain children with SFGAO_STORAGE or SFGAO_STREAM
#define SFGAO_STORAGECAPMASK    0x70C50008L     // for determining storage capabilities, ie for open/save semantics
typedef ULONG SFGAOF;

#define STR_BIND_INCLUDE_ALL_DETAILS   L"Include All Details"
#define STR_BIND_ALLOW_NTFS_PROPSTORE   L"Allow NTFS PropertyStore"
#define STR_BIND_CACHED_READ_ONLY      L"Get Cached ReadOnly Interface"
#define STR_BIND_DELAY_PROPSTORE_CREATION L"Delay property store creation"
#define STR_BIND_INCLUDE_OFFLINE_DETAILS   L"Include Offline Details"
#define STR_SKIP_BINDING_CLSID      L"Skip Binding CLSID"
#define STR_PARSE_PREFER_FOLDER_BROWSING     L"Parse Prefer Folder Browsing"
#define STR_DONT_PARSE_RELATIVE              L"Don't Parse Relative"
#define STR_PARSE_TRANSLATE_ALIASES          L"Parse Translate Aliases"
#define STR_PARSE_SKIP_NET_CACHE             L"Skip Net Resource Cache"
#define STR_TRACK_CLSID                      L"Track the CLSID"
#define STR_SHAREPOINT_SUPPORT               L"Parse SharePoints in Shell"
#define STR_INTERNAL_NAVIGATE                L"Internal Navigation"
#define STR_ENUM_BY_IDLIST                  L"Enumerate with respect to the IDList"



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0206_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0206_v0_0_s_ifspec;

#ifndef __IShellFolder_INTERFACE_DEFINED__
#define __IShellFolder_INTERFACE_DEFINED__

/* interface IShellFolder */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellFolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214E6-0000-0000-C000-000000000046")
    IShellFolder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ParseDisplayName( 
            /* [in] */ HWND hwnd,
            /* [in] */ LPBC pbc,
            /* [string][in] */ LPOLESTR pszDisplayName,
            /* [out] */ ULONG *pchEaten,
            /* [out] */ PIDLIST_RELATIVE *ppidl,
            /* [unique][out][in] */ ULONG *pdwAttributes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumObjects( 
            /* [in] */ HWND hwnd,
            /* [in] */ SHCONTF grfFlags,
            /* [out] */ IEnumIDList **ppenumIDList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BindToObject( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ LPBC pbc,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BindToStorage( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ LPBC pbc,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompareIDs( 
            /* [in] */ LPARAM lParam,
            /* [in] */ PCUIDLIST_RELATIVE pidl1,
            /* [in] */ PCUIDLIST_RELATIVE pidl2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateViewObject( 
            /* [in] */ HWND hwndOwner,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAttributesOf( 
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [out][in] */ SFGAOF *rgfInOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUIObjectOf( 
            /* [in] */ HWND hwndOwner,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ REFIID riid,
            /* [unique][out][in] */ UINT *rgfReserved,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayNameOf( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ STRRET *pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNameOf( 
            /* [in] */ HWND hwnd,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [string][in] */ LPCOLESTR pszName,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ PITEMID_CHILD *ppidlOut) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellFolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellFolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellFolder * This);
        
        HRESULT ( STDMETHODCALLTYPE *ParseDisplayName )( 
            IShellFolder * This,
            /* [in] */ HWND hwnd,
            /* [in] */ LPBC pbc,
            /* [string][in] */ LPOLESTR pszDisplayName,
            /* [out] */ ULONG *pchEaten,
            /* [out] */ PIDLIST_RELATIVE *ppidl,
            /* [unique][out][in] */ ULONG *pdwAttributes);
        
        HRESULT ( STDMETHODCALLTYPE *EnumObjects )( 
            IShellFolder * This,
            /* [in] */ HWND hwnd,
            /* [in] */ SHCONTF grfFlags,
            /* [out] */ IEnumIDList **ppenumIDList);
        
        HRESULT ( STDMETHODCALLTYPE *BindToObject )( 
            IShellFolder * This,
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ LPBC pbc,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *BindToStorage )( 
            IShellFolder * This,
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ LPBC pbc,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *CompareIDs )( 
            IShellFolder * This,
            /* [in] */ LPARAM lParam,
            /* [in] */ PCUIDLIST_RELATIVE pidl1,
            /* [in] */ PCUIDLIST_RELATIVE pidl2);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewObject )( 
            IShellFolder * This,
            /* [in] */ HWND hwndOwner,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetAttributesOf )( 
            IShellFolder * This,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [out][in] */ SFGAOF *rgfInOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetUIObjectOf )( 
            IShellFolder * This,
            /* [in] */ HWND hwndOwner,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ REFIID riid,
            /* [unique][out][in] */ UINT *rgfReserved,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayNameOf )( 
            IShellFolder * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ STRRET *pName);
        
        HRESULT ( STDMETHODCALLTYPE *SetNameOf )( 
            IShellFolder * This,
            /* [in] */ HWND hwnd,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [string][in] */ LPCOLESTR pszName,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ PITEMID_CHILD *ppidlOut);
        
        END_INTERFACE
    } IShellFolderVtbl;

    interface IShellFolder
    {
        CONST_VTBL struct IShellFolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellFolder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellFolder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellFolder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellFolder_ParseDisplayName(This,hwnd,pbc,pszDisplayName,pchEaten,ppidl,pdwAttributes)	\
    ( (This)->lpVtbl -> ParseDisplayName(This,hwnd,pbc,pszDisplayName,pchEaten,ppidl,pdwAttributes) ) 

#define IShellFolder_EnumObjects(This,hwnd,grfFlags,ppenumIDList)	\
    ( (This)->lpVtbl -> EnumObjects(This,hwnd,grfFlags,ppenumIDList) ) 

#define IShellFolder_BindToObject(This,pidl,pbc,riid,ppv)	\
    ( (This)->lpVtbl -> BindToObject(This,pidl,pbc,riid,ppv) ) 

#define IShellFolder_BindToStorage(This,pidl,pbc,riid,ppv)	\
    ( (This)->lpVtbl -> BindToStorage(This,pidl,pbc,riid,ppv) ) 

#define IShellFolder_CompareIDs(This,lParam,pidl1,pidl2)	\
    ( (This)->lpVtbl -> CompareIDs(This,lParam,pidl1,pidl2) ) 

#define IShellFolder_CreateViewObject(This,hwndOwner,riid,ppv)	\
    ( (This)->lpVtbl -> CreateViewObject(This,hwndOwner,riid,ppv) ) 

#define IShellFolder_GetAttributesOf(This,cidl,apidl,rgfInOut)	\
    ( (This)->lpVtbl -> GetAttributesOf(This,cidl,apidl,rgfInOut) ) 

#define IShellFolder_GetUIObjectOf(This,hwndOwner,cidl,apidl,riid,rgfReserved,ppv)	\
    ( (This)->lpVtbl -> GetUIObjectOf(This,hwndOwner,cidl,apidl,riid,rgfReserved,ppv) ) 

#define IShellFolder_GetDisplayNameOf(This,pidl,uFlags,pName)	\
    ( (This)->lpVtbl -> GetDisplayNameOf(This,pidl,uFlags,pName) ) 

#define IShellFolder_SetNameOf(This,hwnd,pidl,pszName,uFlags,ppidlOut)	\
    ( (This)->lpVtbl -> SetNameOf(This,hwnd,pidl,pszName,uFlags,ppidlOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellFolder_ParseDisplayName_Proxy( 
    IShellFolder * This,
    /* [in] */ HWND hwnd,
    /* [in] */ LPBC pbc,
    /* [string][in] */ LPOLESTR pszDisplayName,
    /* [out] */ ULONG *pchEaten,
    /* [out] */ PIDLIST_RELATIVE *ppidl,
    /* [unique][out][in] */ ULONG *pdwAttributes);


void __RPC_STUB IShellFolder_ParseDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_EnumObjects_Proxy( 
    IShellFolder * This,
    /* [in] */ HWND hwnd,
    /* [in] */ SHCONTF grfFlags,
    /* [out] */ IEnumIDList **ppenumIDList);


void __RPC_STUB IShellFolder_EnumObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_BindToObject_Proxy( 
    IShellFolder * This,
    /* [in] */ PCUIDLIST_RELATIVE pidl,
    /* [in] */ LPBC pbc,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellFolder_BindToObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_BindToStorage_Proxy( 
    IShellFolder * This,
    /* [in] */ PCUIDLIST_RELATIVE pidl,
    /* [in] */ LPBC pbc,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellFolder_BindToStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_CompareIDs_Proxy( 
    IShellFolder * This,
    /* [in] */ LPARAM lParam,
    /* [in] */ PCUIDLIST_RELATIVE pidl1,
    /* [in] */ PCUIDLIST_RELATIVE pidl2);


void __RPC_STUB IShellFolder_CompareIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_CreateViewObject_Proxy( 
    IShellFolder * This,
    /* [in] */ HWND hwndOwner,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellFolder_CreateViewObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_GetAttributesOf_Proxy( 
    IShellFolder * This,
    /* [in] */ UINT cidl,
    /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
    /* [out][in] */ SFGAOF *rgfInOut);


void __RPC_STUB IShellFolder_GetAttributesOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_GetUIObjectOf_Proxy( 
    IShellFolder * This,
    /* [in] */ HWND hwndOwner,
    /* [in] */ UINT cidl,
    /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
    /* [in] */ REFIID riid,
    /* [unique][out][in] */ UINT *rgfReserved,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellFolder_GetUIObjectOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_GetDisplayNameOf_Proxy( 
    IShellFolder * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ SHGDNF uFlags,
    /* [out] */ STRRET *pName);


void __RPC_STUB IShellFolder_GetDisplayNameOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder_SetNameOf_Proxy( 
    IShellFolder * This,
    /* [in] */ HWND hwnd,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [string][in] */ LPCOLESTR pszName,
    /* [in] */ SHGDNF uFlags,
    /* [out] */ PITEMID_CHILD *ppidlOut);


void __RPC_STUB IShellFolder_SetNameOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellFolder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0207 */
/* [local] */ 

typedef IShellFolder *LPSHELLFOLDER;

#if (_WIN32_IE >= 0x0500)
typedef struct tagEXTRASEARCH
    {
    GUID guidSearch;
    WCHAR wszFriendlyName[ 80 ];
    WCHAR wszUrl[ 2084 ];
    } 	EXTRASEARCH;

typedef struct tagEXTRASEARCH *LPEXTRASEARCH;

typedef struct IEnumExtraSearch *LPENUMEXTRASEARCH;




extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0207_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0207_v0_0_s_ifspec;

#ifndef __IEnumExtraSearch_INTERFACE_DEFINED__
#define __IEnumExtraSearch_INTERFACE_DEFINED__

/* interface IEnumExtraSearch */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IEnumExtraSearch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E700BE1-9DB6-11d1-A1CE-00C04FD75D13")
    IEnumExtraSearch : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ EXTRASEARCH *rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumExtraSearch **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumExtraSearchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumExtraSearch * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumExtraSearch * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumExtraSearch * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumExtraSearch * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ EXTRASEARCH *rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumExtraSearch * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumExtraSearch * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumExtraSearch * This,
            /* [out] */ IEnumExtraSearch **ppenum);
        
        END_INTERFACE
    } IEnumExtraSearchVtbl;

    interface IEnumExtraSearch
    {
        CONST_VTBL struct IEnumExtraSearchVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumExtraSearch_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumExtraSearch_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumExtraSearch_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumExtraSearch_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumExtraSearch_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumExtraSearch_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumExtraSearch_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumExtraSearch_Next_Proxy( 
    IEnumExtraSearch * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ EXTRASEARCH *rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumExtraSearch_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumExtraSearch_Skip_Proxy( 
    IEnumExtraSearch * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumExtraSearch_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumExtraSearch_Reset_Proxy( 
    IEnumExtraSearch * This);


void __RPC_STUB IEnumExtraSearch_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumExtraSearch_Clone_Proxy( 
    IEnumExtraSearch * This,
    /* [out] */ IEnumExtraSearch **ppenum);


void __RPC_STUB IEnumExtraSearch_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumExtraSearch_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0208 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagSHCOLSTATE
    {	SHCOLSTATE_TYPE_STR	= 0x1,
	SHCOLSTATE_TYPE_INT	= 0x2,
	SHCOLSTATE_TYPE_DATE	= 0x3,
	SHCOLSTATE_TYPEMASK	= 0xf,
	SHCOLSTATE_ONBYDEFAULT	= 0x10,
	SHCOLSTATE_SLOW	= 0x20,
	SHCOLSTATE_EXTENDED	= 0x40,
	SHCOLSTATE_SECONDARYUI	= 0x80,
	SHCOLSTATE_HIDDEN	= 0x100,
	SHCOLSTATE_PREFER_VARCMP	= 0x200,
	SHCOLSTATE_VIEWONLY	= 0x800,
	SHCOLSTATE_FIXED_WIDTH	= 0x1000,
	SHCOLSTATE_NODPISCALE	= 0x2000,
	SHCOLSTATE_FIXED_RATIO	= 0x4000,
	SHCOLSTATE_DISPLAYMASK	= 0xf000
    } 	SHCOLSTATE;

typedef DWORD SHCOLSTATEF;

typedef PROPERTYKEY SHCOLUMNID;

typedef const SHCOLUMNID *LPCSHCOLUMNID;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0208_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0208_v0_0_s_ifspec;

#ifndef __IShellFolder2_INTERFACE_DEFINED__
#define __IShellFolder2_INTERFACE_DEFINED__

/* interface IShellFolder2 */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellFolder2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93F2F68C-1D1B-11d3-A30E-00C04F79ABD1")
    IShellFolder2 : public IShellFolder
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDefaultSearchGUID( 
            /* [out] */ GUID *pguid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumSearches( 
            /* [out] */ IEnumExtraSearch **ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultColumn( 
            /* [in] */ DWORD dwRes,
            /* [out] */ ULONG *pSort,
            /* [out] */ ULONG *pDisplay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultColumnState( 
            /* [in] */ UINT iColumn,
            /* [out] */ SHCOLSTATEF *pcsFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDetailsEx( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ const SHCOLUMNID *pscid,
            /* [out] */ VARIANT *pv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDetailsOf( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ UINT iColumn,
            /* [out] */ SHELLDETAILS *psd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapColumnToSCID( 
            /* [in] */ UINT iColumn,
            /* [in] */ SHCOLUMNID *pscid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellFolder2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellFolder2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellFolder2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellFolder2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ParseDisplayName )( 
            IShellFolder2 * This,
            /* [in] */ HWND hwnd,
            /* [in] */ LPBC pbc,
            /* [string][in] */ LPOLESTR pszDisplayName,
            /* [out] */ ULONG *pchEaten,
            /* [out] */ PIDLIST_RELATIVE *ppidl,
            /* [unique][out][in] */ ULONG *pdwAttributes);
        
        HRESULT ( STDMETHODCALLTYPE *EnumObjects )( 
            IShellFolder2 * This,
            /* [in] */ HWND hwnd,
            /* [in] */ SHCONTF grfFlags,
            /* [out] */ IEnumIDList **ppenumIDList);
        
        HRESULT ( STDMETHODCALLTYPE *BindToObject )( 
            IShellFolder2 * This,
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ LPBC pbc,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *BindToStorage )( 
            IShellFolder2 * This,
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ LPBC pbc,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *CompareIDs )( 
            IShellFolder2 * This,
            /* [in] */ LPARAM lParam,
            /* [in] */ PCUIDLIST_RELATIVE pidl1,
            /* [in] */ PCUIDLIST_RELATIVE pidl2);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewObject )( 
            IShellFolder2 * This,
            /* [in] */ HWND hwndOwner,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetAttributesOf )( 
            IShellFolder2 * This,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [out][in] */ SFGAOF *rgfInOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetUIObjectOf )( 
            IShellFolder2 * This,
            /* [in] */ HWND hwndOwner,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ REFIID riid,
            /* [unique][out][in] */ UINT *rgfReserved,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayNameOf )( 
            IShellFolder2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ STRRET *pName);
        
        HRESULT ( STDMETHODCALLTYPE *SetNameOf )( 
            IShellFolder2 * This,
            /* [in] */ HWND hwnd,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [string][in] */ LPCOLESTR pszName,
            /* [in] */ SHGDNF uFlags,
            /* [out] */ PITEMID_CHILD *ppidlOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultSearchGUID )( 
            IShellFolder2 * This,
            /* [out] */ GUID *pguid);
        
        HRESULT ( STDMETHODCALLTYPE *EnumSearches )( 
            IShellFolder2 * This,
            /* [out] */ IEnumExtraSearch **ppenum);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultColumn )( 
            IShellFolder2 * This,
            /* [in] */ DWORD dwRes,
            /* [out] */ ULONG *pSort,
            /* [out] */ ULONG *pDisplay);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultColumnState )( 
            IShellFolder2 * This,
            /* [in] */ UINT iColumn,
            /* [out] */ SHCOLSTATEF *pcsFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetDetailsEx )( 
            IShellFolder2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ const SHCOLUMNID *pscid,
            /* [out] */ VARIANT *pv);
        
        HRESULT ( STDMETHODCALLTYPE *GetDetailsOf )( 
            IShellFolder2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ UINT iColumn,
            /* [out] */ SHELLDETAILS *psd);
        
        HRESULT ( STDMETHODCALLTYPE *MapColumnToSCID )( 
            IShellFolder2 * This,
            /* [in] */ UINT iColumn,
            /* [in] */ SHCOLUMNID *pscid);
        
        END_INTERFACE
    } IShellFolder2Vtbl;

    interface IShellFolder2
    {
        CONST_VTBL struct IShellFolder2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellFolder2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellFolder2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellFolder2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellFolder2_ParseDisplayName(This,hwnd,pbc,pszDisplayName,pchEaten,ppidl,pdwAttributes)	\
    ( (This)->lpVtbl -> ParseDisplayName(This,hwnd,pbc,pszDisplayName,pchEaten,ppidl,pdwAttributes) ) 

#define IShellFolder2_EnumObjects(This,hwnd,grfFlags,ppenumIDList)	\
    ( (This)->lpVtbl -> EnumObjects(This,hwnd,grfFlags,ppenumIDList) ) 

#define IShellFolder2_BindToObject(This,pidl,pbc,riid,ppv)	\
    ( (This)->lpVtbl -> BindToObject(This,pidl,pbc,riid,ppv) ) 

#define IShellFolder2_BindToStorage(This,pidl,pbc,riid,ppv)	\
    ( (This)->lpVtbl -> BindToStorage(This,pidl,pbc,riid,ppv) ) 

#define IShellFolder2_CompareIDs(This,lParam,pidl1,pidl2)	\
    ( (This)->lpVtbl -> CompareIDs(This,lParam,pidl1,pidl2) ) 

#define IShellFolder2_CreateViewObject(This,hwndOwner,riid,ppv)	\
    ( (This)->lpVtbl -> CreateViewObject(This,hwndOwner,riid,ppv) ) 

#define IShellFolder2_GetAttributesOf(This,cidl,apidl,rgfInOut)	\
    ( (This)->lpVtbl -> GetAttributesOf(This,cidl,apidl,rgfInOut) ) 

#define IShellFolder2_GetUIObjectOf(This,hwndOwner,cidl,apidl,riid,rgfReserved,ppv)	\
    ( (This)->lpVtbl -> GetUIObjectOf(This,hwndOwner,cidl,apidl,riid,rgfReserved,ppv) ) 

#define IShellFolder2_GetDisplayNameOf(This,pidl,uFlags,pName)	\
    ( (This)->lpVtbl -> GetDisplayNameOf(This,pidl,uFlags,pName) ) 

#define IShellFolder2_SetNameOf(This,hwnd,pidl,pszName,uFlags,ppidlOut)	\
    ( (This)->lpVtbl -> SetNameOf(This,hwnd,pidl,pszName,uFlags,ppidlOut) ) 


#define IShellFolder2_GetDefaultSearchGUID(This,pguid)	\
    ( (This)->lpVtbl -> GetDefaultSearchGUID(This,pguid) ) 

#define IShellFolder2_EnumSearches(This,ppenum)	\
    ( (This)->lpVtbl -> EnumSearches(This,ppenum) ) 

#define IShellFolder2_GetDefaultColumn(This,dwRes,pSort,pDisplay)	\
    ( (This)->lpVtbl -> GetDefaultColumn(This,dwRes,pSort,pDisplay) ) 

#define IShellFolder2_GetDefaultColumnState(This,iColumn,pcsFlags)	\
    ( (This)->lpVtbl -> GetDefaultColumnState(This,iColumn,pcsFlags) ) 

#define IShellFolder2_GetDetailsEx(This,pidl,pscid,pv)	\
    ( (This)->lpVtbl -> GetDetailsEx(This,pidl,pscid,pv) ) 

#define IShellFolder2_GetDetailsOf(This,pidl,iColumn,psd)	\
    ( (This)->lpVtbl -> GetDetailsOf(This,pidl,iColumn,psd) ) 

#define IShellFolder2_MapColumnToSCID(This,iColumn,pscid)	\
    ( (This)->lpVtbl -> MapColumnToSCID(This,iColumn,pscid) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellFolder2_GetDefaultSearchGUID_Proxy( 
    IShellFolder2 * This,
    /* [out] */ GUID *pguid);


void __RPC_STUB IShellFolder2_GetDefaultSearchGUID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder2_EnumSearches_Proxy( 
    IShellFolder2 * This,
    /* [out] */ IEnumExtraSearch **ppenum);


void __RPC_STUB IShellFolder2_EnumSearches_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder2_GetDefaultColumn_Proxy( 
    IShellFolder2 * This,
    /* [in] */ DWORD dwRes,
    /* [out] */ ULONG *pSort,
    /* [out] */ ULONG *pDisplay);


void __RPC_STUB IShellFolder2_GetDefaultColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder2_GetDefaultColumnState_Proxy( 
    IShellFolder2 * This,
    /* [in] */ UINT iColumn,
    /* [out] */ SHCOLSTATEF *pcsFlags);


void __RPC_STUB IShellFolder2_GetDefaultColumnState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder2_GetDetailsEx_Proxy( 
    IShellFolder2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ const SHCOLUMNID *pscid,
    /* [out] */ VARIANT *pv);


void __RPC_STUB IShellFolder2_GetDetailsEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder2_GetDetailsOf_Proxy( 
    IShellFolder2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ UINT iColumn,
    /* [out] */ SHELLDETAILS *psd);


void __RPC_STUB IShellFolder2_GetDetailsOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellFolder2_MapColumnToSCID_Proxy( 
    IShellFolder2 * This,
    /* [in] */ UINT iColumn,
    /* [in] */ SHCOLUMNID *pscid);


void __RPC_STUB IShellFolder2_MapColumnToSCID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellFolder2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0209 */
/* [local] */ 

#endif // _WIN32_IE >= 0x0500)
typedef char *LPVIEWSETTINGS;

typedef /* [v1_enum] */ 
enum tagFOLDERFLAGS
    {	FWF_AUTOARRANGE	= 0x1,
	FWF_ABBREVIATEDNAMES	= 0x2,
	FWF_SNAPTOGRID	= 0x4,
	FWF_MIL	= 0x8,
	FWF_BESTFITWINDOW	= 0x10,
	FWF_DESKTOP	= 0x20,
	FWF_SINGLESEL	= 0x40,
	FWF_NOSUBFOLDERS	= 0x80,
	FWF_TRANSPARENT	= 0x100,
	FWF_NOCLIENTEDGE	= 0x200,
	FWF_NOSCROLL	= 0x400,
	FWF_ALIGNLEFT	= 0x800,
	FWF_NOICONS	= 0x1000,
	FWF_SHOWSELALWAYS	= 0x2000,
	FWF_NOVISIBLE	= 0x4000,
	FWF_SINGLECLICKACTIVATE	= 0x8000,
	FWF_NOWEBVIEW	= 0x10000,
	FWF_HIDEFILENAMES	= 0x20000,
	FWF_CHECKSELECT	= 0x40000,
	FWF_NOENUMREFRESH	= 0x80000,
	FWF_NOGROUPING	= 0x100000,
	FWF_FULLROWSELECT	= 0x200000,
	FWF_PREVIEWPANE	= 0x400000,
	FWF_NOFILTERS	= 0x800000,
	FWF_NOPERSISTORDER	= 0x1000000,
	FWF_NOCOLUMNHEADER	= 0x2000000,
	FWF_SHOWNUMORDER	= 0x4000000,
	FWF_EXTENDEDTILES	= 0x8000000,
	FWF_3D	= 0x10000000,
	FWF_PREVIEWMINIMODE	= 0x20000000,
	FWF_AUTOCHECKSELECT	= 0x40000000,
	FWF_NOAUTOSIZECOLUMNS	= 0x80000000
    } 	FOLDERFLAGS;

typedef /* [v1_enum] */ 
enum tagFOLDERVIEWMODE
    {	FVM_FIRST	= 1,
	FVM_ICON	= 1,
	FVM_SMALLICON	= 2,
	FVM_LIST	= 3,
	FVM_DETAILS	= 4,
	FVM_THUMBNAIL	= 5,
	FVM_TILE	= 6,
	FVM_THUMBSTRIP	= 7,
	FVM_CAROUSEL	= 8,
	FVM_PANORAMA	= 9,
	FVM_LAST	= 9
    } 	FOLDERVIEWMODE;

typedef /* [v1_enum] */ 
enum tagFOLDERLOGICALVIEWMODE
    {	FLVM_FIRST	= 1,
	FLVM_DETAILS	= 1,
	FLVM_TILES	= 2,
	FLVM_ICONS	= 3,
	FLVM_LAST	= 3
    } 	FOLDERLOGICALVIEWMODE;

typedef /* [v1_enum] */ 
enum tagSUPPORTEDVIEWFLAGS
    {	SVF_CAROUSEL	= 0x1,
	SVF_PANORAMA	= 0x2
    } 	SUPPORTEDVIEWFLAGS;

typedef struct tagFOLDERSETTINGS
    {
    UINT ViewMode;
    UINT fFlags;
    } 	FOLDERSETTINGS;

typedef FOLDERSETTINGS *LPFOLDERSETTINGS;

typedef const FOLDERSETTINGS *LPCFOLDERSETTINGS;

typedef FOLDERSETTINGS *PFOLDERSETTINGS;

#define SVSI_DESELECT       0x00000000
#define SVSI_SELECT         0x00000001
#define SVSI_EDIT           0x00000003  // includes select
#define SVSI_DESELECTOTHERS 0x00000004
#define SVSI_ENSUREVISIBLE  0x00000008
#define SVSI_FOCUSED        0x00000010
#define SVSI_TRANSLATEPT    0x00000020
#define SVSI_SELECTIONMARK  0x00000040
#define SVSI_POSITIONITEM   0x00000080
#define SVSI_CHECK          0x00000100
#define SVSI_NOSTATECHANGE  0x80000000
typedef UINT SVSIF;

/* [v1_enum] */ 
enum tagSVGIO
    {	SVGIO_BACKGROUND	= 0,
	SVGIO_SELECTION	= 0x1,
	SVGIO_ALLVIEW	= 0x2,
	SVGIO_CHECKED	= 0x3,
	SVGIO_TYPE_MASK	= 0xf,
	SVGIO_FLAG_VIEWORDER	= 0x80000000
    } ;
typedef int SVGIO;

typedef /* [v1_enum] */ 
enum tagSVUIA_STATUS
    {	SVUIA_DEACTIVATE	= 0,
	SVUIA_ACTIVATE_NOFOCUS	= 1,
	SVUIA_ACTIVATE_FOCUS	= 2,
	SVUIA_INPLACEACTIVATE	= 3
    } 	SVUIA_STATUS;

#ifdef _FIX_ENABLEMODELESS_CONFLICT
#define    EnableModeless EnableModelessSV
#endif
#ifdef _NEVER_
typedef LPARAM LPFNSVADDPROPSHEETPAGE;

#else //!_NEVER_
#include <prsht.h>
typedef LPFNADDPROPSHEETPAGE LPFNSVADDPROPSHEETPAGE;
#endif //_NEVER_



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0209_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0209_v0_0_s_ifspec;

#ifndef __IShellView_INTERFACE_DEFINED__
#define __IShellView_INTERFACE_DEFINED__

/* interface IShellView */
/* [unique][object][uuid] */ 

typedef IShellView *LPSHELLVIEW;


EXTERN_C const IID IID_IShellView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214E3-0000-0000-C000-000000000046")
    IShellView : public IOleWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ MSG *pmsg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UIActivate( 
            /* [in] */ UINT uState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateViewWindow( 
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [in] */ RECT *prcView,
            /* [out] */ HWND *phWnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DestroyViewWindow( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentInfo( 
            /* [out] */ LPFOLDERSETTINGS pfs) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE AddPropertySheetPages( 
            /* [in] */ DWORD dwReserved,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
            /* [in] */ LPARAM lparam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveViewState( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectItem( 
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ SVSIF uFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemObject( 
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellView * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IShellView * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IShellView * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAccelerator )( 
            IShellView * This,
            /* [in] */ MSG *pmsg);
        
        HRESULT ( STDMETHODCALLTYPE *EnableModeless )( 
            IShellView * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *UIActivate )( 
            IShellView * This,
            /* [in] */ UINT uState);
        
        HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IShellView * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewWindow )( 
            IShellView * This,
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [in] */ RECT *prcView,
            /* [out] */ HWND *phWnd);
        
        HRESULT ( STDMETHODCALLTYPE *DestroyViewWindow )( 
            IShellView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentInfo )( 
            IShellView * This,
            /* [out] */ LPFOLDERSETTINGS pfs);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *AddPropertySheetPages )( 
            IShellView * This,
            /* [in] */ DWORD dwReserved,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
            /* [in] */ LPARAM lparam);
        
        HRESULT ( STDMETHODCALLTYPE *SaveViewState )( 
            IShellView * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectItem )( 
            IShellView * This,
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ SVSIF uFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemObject )( 
            IShellView * This,
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IShellViewVtbl;

    interface IShellView
    {
        CONST_VTBL struct IShellViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellView_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellView_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellView_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellView_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IShellView_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IShellView_TranslateAccelerator(This,pmsg)	\
    ( (This)->lpVtbl -> TranslateAccelerator(This,pmsg) ) 

#define IShellView_EnableModeless(This,fEnable)	\
    ( (This)->lpVtbl -> EnableModeless(This,fEnable) ) 

#define IShellView_UIActivate(This,uState)	\
    ( (This)->lpVtbl -> UIActivate(This,uState) ) 

#define IShellView_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IShellView_CreateViewWindow(This,psvPrevious,pfs,psb,prcView,phWnd)	\
    ( (This)->lpVtbl -> CreateViewWindow(This,psvPrevious,pfs,psb,prcView,phWnd) ) 

#define IShellView_DestroyViewWindow(This)	\
    ( (This)->lpVtbl -> DestroyViewWindow(This) ) 

#define IShellView_GetCurrentInfo(This,pfs)	\
    ( (This)->lpVtbl -> GetCurrentInfo(This,pfs) ) 

#define IShellView_AddPropertySheetPages(This,dwReserved,pfn,lparam)	\
    ( (This)->lpVtbl -> AddPropertySheetPages(This,dwReserved,pfn,lparam) ) 

#define IShellView_SaveViewState(This)	\
    ( (This)->lpVtbl -> SaveViewState(This) ) 

#define IShellView_SelectItem(This,pidlItem,uFlags)	\
    ( (This)->lpVtbl -> SelectItem(This,pidlItem,uFlags) ) 

#define IShellView_GetItemObject(This,uItem,riid,ppv)	\
    ( (This)->lpVtbl -> GetItemObject(This,uItem,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellView_TranslateAccelerator_Proxy( 
    IShellView * This,
    /* [in] */ MSG *pmsg);


void __RPC_STUB IShellView_TranslateAccelerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_EnableModeless_Proxy( 
    IShellView * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IShellView_EnableModeless_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_UIActivate_Proxy( 
    IShellView * This,
    /* [in] */ UINT uState);


void __RPC_STUB IShellView_UIActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_Refresh_Proxy( 
    IShellView * This);


void __RPC_STUB IShellView_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_CreateViewWindow_Proxy( 
    IShellView * This,
    /* [in] */ IShellView *psvPrevious,
    /* [in] */ LPCFOLDERSETTINGS pfs,
    /* [in] */ IShellBrowser *psb,
    /* [in] */ RECT *prcView,
    /* [out] */ HWND *phWnd);


void __RPC_STUB IShellView_CreateViewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_DestroyViewWindow_Proxy( 
    IShellView * This);


void __RPC_STUB IShellView_DestroyViewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_GetCurrentInfo_Proxy( 
    IShellView * This,
    /* [out] */ LPFOLDERSETTINGS pfs);


void __RPC_STUB IShellView_GetCurrentInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IShellView_AddPropertySheetPages_Proxy( 
    IShellView * This,
    /* [in] */ DWORD dwReserved,
    /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
    /* [in] */ LPARAM lparam);


void __RPC_STUB IShellView_AddPropertySheetPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_SaveViewState_Proxy( 
    IShellView * This);


void __RPC_STUB IShellView_SaveViewState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_SelectItem_Proxy( 
    IShellView * This,
    /* [in] */ PCUITEMID_CHILD pidlItem,
    /* [in] */ SVSIF uFlags);


void __RPC_STUB IShellView_SelectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView_GetItemObject_Proxy( 
    IShellView * This,
    /* [in] */ UINT uItem,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellView_GetItemObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellView_INTERFACE_DEFINED__ */


#ifndef __IShellView2_INTERFACE_DEFINED__
#define __IShellView2_INTERFACE_DEFINED__

/* interface IShellView2 */
/* [unique][object][uuid] */ 

typedef GUID SHELLVIEWID;

#define SV2GV_CURRENTVIEW ((UINT)-1)
#define SV2GV_DEFAULTVIEW ((UINT)-2)
#include <pshpack8.h>
typedef struct _SV2CVW2_PARAMS
    {
    DWORD cbSize;
    IShellView *psvPrev;
    LPCFOLDERSETTINGS pfs;
    IShellBrowser *psbOwner;
    RECT *prcView;
    const SHELLVIEWID *pvid;
    HWND hwndView;
    } 	SV2CVW2_PARAMS;

typedef struct _SV2CVW2_PARAMS *LPSV2CVW2_PARAMS;

#include <poppack.h>

EXTERN_C const IID IID_IShellView2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88E39E80-3578-11CF-AE69-08002B2E1262")
    IShellView2 : public IShellView
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [out][in] */ SHELLVIEWID *pvid,
            /* [in] */ ULONG uView) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateViewWindow2( 
            /* [in] */ LPSV2CVW2_PARAMS lpParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleRename( 
            /* [in] */ PCUITEMID_CHILD pidlNew) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectAndPositionItem( 
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ UINT uFlags,
            /* [unique][in] */ POINT *ppt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellView2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellView2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellView2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellView2 * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IShellView2 * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IShellView2 * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAccelerator )( 
            IShellView2 * This,
            /* [in] */ MSG *pmsg);
        
        HRESULT ( STDMETHODCALLTYPE *EnableModeless )( 
            IShellView2 * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *UIActivate )( 
            IShellView2 * This,
            /* [in] */ UINT uState);
        
        HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IShellView2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewWindow )( 
            IShellView2 * This,
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [in] */ RECT *prcView,
            /* [out] */ HWND *phWnd);
        
        HRESULT ( STDMETHODCALLTYPE *DestroyViewWindow )( 
            IShellView2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentInfo )( 
            IShellView2 * This,
            /* [out] */ LPFOLDERSETTINGS pfs);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *AddPropertySheetPages )( 
            IShellView2 * This,
            /* [in] */ DWORD dwReserved,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
            /* [in] */ LPARAM lparam);
        
        HRESULT ( STDMETHODCALLTYPE *SaveViewState )( 
            IShellView2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectItem )( 
            IShellView2 * This,
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ SVSIF uFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemObject )( 
            IShellView2 * This,
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            IShellView2 * This,
            /* [out][in] */ SHELLVIEWID *pvid,
            /* [in] */ ULONG uView);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewWindow2 )( 
            IShellView2 * This,
            /* [in] */ LPSV2CVW2_PARAMS lpParams);
        
        HRESULT ( STDMETHODCALLTYPE *HandleRename )( 
            IShellView2 * This,
            /* [in] */ PCUITEMID_CHILD pidlNew);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAndPositionItem )( 
            IShellView2 * This,
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ UINT uFlags,
            /* [unique][in] */ POINT *ppt);
        
        END_INTERFACE
    } IShellView2Vtbl;

    interface IShellView2
    {
        CONST_VTBL struct IShellView2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellView2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellView2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellView2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellView2_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IShellView2_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IShellView2_TranslateAccelerator(This,pmsg)	\
    ( (This)->lpVtbl -> TranslateAccelerator(This,pmsg) ) 

#define IShellView2_EnableModeless(This,fEnable)	\
    ( (This)->lpVtbl -> EnableModeless(This,fEnable) ) 

#define IShellView2_UIActivate(This,uState)	\
    ( (This)->lpVtbl -> UIActivate(This,uState) ) 

#define IShellView2_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IShellView2_CreateViewWindow(This,psvPrevious,pfs,psb,prcView,phWnd)	\
    ( (This)->lpVtbl -> CreateViewWindow(This,psvPrevious,pfs,psb,prcView,phWnd) ) 

#define IShellView2_DestroyViewWindow(This)	\
    ( (This)->lpVtbl -> DestroyViewWindow(This) ) 

#define IShellView2_GetCurrentInfo(This,pfs)	\
    ( (This)->lpVtbl -> GetCurrentInfo(This,pfs) ) 

#define IShellView2_AddPropertySheetPages(This,dwReserved,pfn,lparam)	\
    ( (This)->lpVtbl -> AddPropertySheetPages(This,dwReserved,pfn,lparam) ) 

#define IShellView2_SaveViewState(This)	\
    ( (This)->lpVtbl -> SaveViewState(This) ) 

#define IShellView2_SelectItem(This,pidlItem,uFlags)	\
    ( (This)->lpVtbl -> SelectItem(This,pidlItem,uFlags) ) 

#define IShellView2_GetItemObject(This,uItem,riid,ppv)	\
    ( (This)->lpVtbl -> GetItemObject(This,uItem,riid,ppv) ) 


#define IShellView2_GetView(This,pvid,uView)	\
    ( (This)->lpVtbl -> GetView(This,pvid,uView) ) 

#define IShellView2_CreateViewWindow2(This,lpParams)	\
    ( (This)->lpVtbl -> CreateViewWindow2(This,lpParams) ) 

#define IShellView2_HandleRename(This,pidlNew)	\
    ( (This)->lpVtbl -> HandleRename(This,pidlNew) ) 

#define IShellView2_SelectAndPositionItem(This,pidlItem,uFlags,ppt)	\
    ( (This)->lpVtbl -> SelectAndPositionItem(This,pidlItem,uFlags,ppt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellView2_GetView_Proxy( 
    IShellView2 * This,
    /* [out][in] */ SHELLVIEWID *pvid,
    /* [in] */ ULONG uView);


void __RPC_STUB IShellView2_GetView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView2_CreateViewWindow2_Proxy( 
    IShellView2 * This,
    /* [in] */ LPSV2CVW2_PARAMS lpParams);


void __RPC_STUB IShellView2_CreateViewWindow2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView2_HandleRename_Proxy( 
    IShellView2 * This,
    /* [in] */ PCUITEMID_CHILD pidlNew);


void __RPC_STUB IShellView2_HandleRename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellView2_SelectAndPositionItem_Proxy( 
    IShellView2 * This,
    /* [in] */ PCUITEMID_CHILD pidlItem,
    /* [in] */ UINT uFlags,
    /* [unique][in] */ POINT *ppt);


void __RPC_STUB IShellView2_SelectAndPositionItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellView2_INTERFACE_DEFINED__ */


#ifndef __IShellView3_INTERFACE_DEFINED__
#define __IShellView3_INTERFACE_DEFINED__

/* interface IShellView3 */
/* [unique][object][uuid] */ 

/* [v1_enum] */ 
enum tagSV3CVW3
    {	SV3CVW3_NONINTERACTIVE	= 0x1
    } ;
typedef DWORD SV3CVW3_FLAGS;


EXTERN_C const IID IID_IShellView3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D926E764-B7F6-4992-BEAE-4B587CF46223")
    IShellView3 : public IShellView2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateViewWindow3( 
            /* [in] */ IShellView *psvPrev,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psbOwner,
            /* [in] */ RECT *prcView,
            /* [in] */ const SHELLVIEWID *pvid,
            /* [in] */ SV3CVW3_FLAGS dwFlags,
            /* [out] */ HWND *phwndView) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellView3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellView3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellView3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellView3 * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IShellView3 * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IShellView3 * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAccelerator )( 
            IShellView3 * This,
            /* [in] */ MSG *pmsg);
        
        HRESULT ( STDMETHODCALLTYPE *EnableModeless )( 
            IShellView3 * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *UIActivate )( 
            IShellView3 * This,
            /* [in] */ UINT uState);
        
        HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IShellView3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewWindow )( 
            IShellView3 * This,
            /* [in] */ IShellView *psvPrevious,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psb,
            /* [in] */ RECT *prcView,
            /* [out] */ HWND *phWnd);
        
        HRESULT ( STDMETHODCALLTYPE *DestroyViewWindow )( 
            IShellView3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentInfo )( 
            IShellView3 * This,
            /* [out] */ LPFOLDERSETTINGS pfs);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *AddPropertySheetPages )( 
            IShellView3 * This,
            /* [in] */ DWORD dwReserved,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfn,
            /* [in] */ LPARAM lparam);
        
        HRESULT ( STDMETHODCALLTYPE *SaveViewState )( 
            IShellView3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectItem )( 
            IShellView3 * This,
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ SVSIF uFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemObject )( 
            IShellView3 * This,
            /* [in] */ UINT uItem,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            IShellView3 * This,
            /* [out][in] */ SHELLVIEWID *pvid,
            /* [in] */ ULONG uView);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewWindow2 )( 
            IShellView3 * This,
            /* [in] */ LPSV2CVW2_PARAMS lpParams);
        
        HRESULT ( STDMETHODCALLTYPE *HandleRename )( 
            IShellView3 * This,
            /* [in] */ PCUITEMID_CHILD pidlNew);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAndPositionItem )( 
            IShellView3 * This,
            /* [in] */ PCUITEMID_CHILD pidlItem,
            /* [in] */ UINT uFlags,
            /* [unique][in] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *CreateViewWindow3 )( 
            IShellView3 * This,
            /* [in] */ IShellView *psvPrev,
            /* [in] */ LPCFOLDERSETTINGS pfs,
            /* [in] */ IShellBrowser *psbOwner,
            /* [in] */ RECT *prcView,
            /* [in] */ const SHELLVIEWID *pvid,
            /* [in] */ SV3CVW3_FLAGS dwFlags,
            /* [out] */ HWND *phwndView);
        
        END_INTERFACE
    } IShellView3Vtbl;

    interface IShellView3
    {
        CONST_VTBL struct IShellView3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellView3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellView3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellView3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellView3_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IShellView3_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IShellView3_TranslateAccelerator(This,pmsg)	\
    ( (This)->lpVtbl -> TranslateAccelerator(This,pmsg) ) 

#define IShellView3_EnableModeless(This,fEnable)	\
    ( (This)->lpVtbl -> EnableModeless(This,fEnable) ) 

#define IShellView3_UIActivate(This,uState)	\
    ( (This)->lpVtbl -> UIActivate(This,uState) ) 

#define IShellView3_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#define IShellView3_CreateViewWindow(This,psvPrevious,pfs,psb,prcView,phWnd)	\
    ( (This)->lpVtbl -> CreateViewWindow(This,psvPrevious,pfs,psb,prcView,phWnd) ) 

#define IShellView3_DestroyViewWindow(This)	\
    ( (This)->lpVtbl -> DestroyViewWindow(This) ) 

#define IShellView3_GetCurrentInfo(This,pfs)	\
    ( (This)->lpVtbl -> GetCurrentInfo(This,pfs) ) 

#define IShellView3_AddPropertySheetPages(This,dwReserved,pfn,lparam)	\
    ( (This)->lpVtbl -> AddPropertySheetPages(This,dwReserved,pfn,lparam) ) 

#define IShellView3_SaveViewState(This)	\
    ( (This)->lpVtbl -> SaveViewState(This) ) 

#define IShellView3_SelectItem(This,pidlItem,uFlags)	\
    ( (This)->lpVtbl -> SelectItem(This,pidlItem,uFlags) ) 

#define IShellView3_GetItemObject(This,uItem,riid,ppv)	\
    ( (This)->lpVtbl -> GetItemObject(This,uItem,riid,ppv) ) 


#define IShellView3_GetView(This,pvid,uView)	\
    ( (This)->lpVtbl -> GetView(This,pvid,uView) ) 

#define IShellView3_CreateViewWindow2(This,lpParams)	\
    ( (This)->lpVtbl -> CreateViewWindow2(This,lpParams) ) 

#define IShellView3_HandleRename(This,pidlNew)	\
    ( (This)->lpVtbl -> HandleRename(This,pidlNew) ) 

#define IShellView3_SelectAndPositionItem(This,pidlItem,uFlags,ppt)	\
    ( (This)->lpVtbl -> SelectAndPositionItem(This,pidlItem,uFlags,ppt) ) 


#define IShellView3_CreateViewWindow3(This,psvPrev,pfs,psbOwner,prcView,pvid,dwFlags,phwndView)	\
    ( (This)->lpVtbl -> CreateViewWindow3(This,psvPrev,pfs,psbOwner,prcView,pvid,dwFlags,phwndView) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellView3_CreateViewWindow3_Proxy( 
    IShellView3 * This,
    /* [in] */ IShellView *psvPrev,
    /* [in] */ LPCFOLDERSETTINGS pfs,
    /* [in] */ IShellBrowser *psbOwner,
    /* [in] */ RECT *prcView,
    /* [in] */ const SHELLVIEWID *pvid,
    /* [in] */ SV3CVW3_FLAGS dwFlags,
    /* [out] */ HWND *phwndView);


void __RPC_STUB IShellView3_CreateViewWindow3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellView3_INTERFACE_DEFINED__ */


#ifndef __IShellViewWithFrame_INTERFACE_DEFINED__
#define __IShellViewWithFrame_INTERFACE_DEFINED__

/* interface IShellViewWithFrame */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellViewWithFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7b3a0889-72c2-4b28-a41d-e3c8e1266f84")
    IShellViewWithFrame : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShouldUseFrame( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetModuleCount( 
            /* [out] */ UINT *pcModules) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetModuleAt( 
            /* [in] */ UINT nIndex,
            /* [out] */ BSTR *pbstrAssembly,
            /* [out] */ BSTR *pbstrClass) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellViewWithFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellViewWithFrame * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellViewWithFrame * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellViewWithFrame * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShouldUseFrame )( 
            IShellViewWithFrame * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetModuleCount )( 
            IShellViewWithFrame * This,
            /* [out] */ UINT *pcModules);
        
        HRESULT ( STDMETHODCALLTYPE *GetModuleAt )( 
            IShellViewWithFrame * This,
            /* [in] */ UINT nIndex,
            /* [out] */ BSTR *pbstrAssembly,
            /* [out] */ BSTR *pbstrClass);
        
        END_INTERFACE
    } IShellViewWithFrameVtbl;

    interface IShellViewWithFrame
    {
        CONST_VTBL struct IShellViewWithFrameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellViewWithFrame_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellViewWithFrame_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellViewWithFrame_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellViewWithFrame_ShouldUseFrame(This)	\
    ( (This)->lpVtbl -> ShouldUseFrame(This) ) 

#define IShellViewWithFrame_GetModuleCount(This,pcModules)	\
    ( (This)->lpVtbl -> GetModuleCount(This,pcModules) ) 

#define IShellViewWithFrame_GetModuleAt(This,nIndex,pbstrAssembly,pbstrClass)	\
    ( (This)->lpVtbl -> GetModuleAt(This,nIndex,pbstrAssembly,pbstrClass) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellViewWithFrame_ShouldUseFrame_Proxy( 
    IShellViewWithFrame * This);


void __RPC_STUB IShellViewWithFrame_ShouldUseFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellViewWithFrame_GetModuleCount_Proxy( 
    IShellViewWithFrame * This,
    /* [out] */ UINT *pcModules);


void __RPC_STUB IShellViewWithFrame_GetModuleCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellViewWithFrame_GetModuleAt_Proxy( 
    IShellViewWithFrame * This,
    /* [in] */ UINT nIndex,
    /* [out] */ BSTR *pbstrAssembly,
    /* [out] */ BSTR *pbstrClass);


void __RPC_STUB IShellViewWithFrame_GetModuleAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellViewWithFrame_INTERFACE_DEFINED__ */


#ifndef __IFolderView_INTERFACE_DEFINED__
#define __IFolderView_INTERFACE_DEFINED__

/* interface IFolderView */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFolderView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("cde725b0-ccc9-4519-917e-325d72fab4ce")
    IFolderView : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCurrentViewMode( 
            /* [out][in] */ UINT *pViewMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCurrentViewMode( 
            /* [in] */ UINT ViewMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFolder( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ int iItemIndex,
            /* [out] */ PITEMID_CHILD *ppidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ItemCount( 
            /* [in] */ UINT uFlags,
            /* [out] */ int *pcItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Items( 
            /* [in] */ UINT uFlags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectionMarkedItem( 
            /* [out] */ int *piItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFocusedItem( 
            /* [out] */ int *piItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemPosition( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [out] */ POINT *ppt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSpacing( 
            /* [full][out][in] */ POINT *ppt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultSpacing( 
            /* [out] */ POINT *ppt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAutoArrange( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectItem( 
            /* [in] */ int iItem,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectAndPositionItems( 
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [size_is][full][in] */ POINT *apt,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentViewMode )( 
            IFolderView * This,
            /* [out][in] */ UINT *pViewMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetCurrentViewMode )( 
            IFolderView * This,
            /* [in] */ UINT ViewMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolder )( 
            IFolderView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *Item )( 
            IFolderView * This,
            /* [in] */ int iItemIndex,
            /* [out] */ PITEMID_CHILD *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *ItemCount )( 
            IFolderView * This,
            /* [in] */ UINT uFlags,
            /* [out] */ int *pcItems);
        
        HRESULT ( STDMETHODCALLTYPE *Items )( 
            IFolderView * This,
            /* [in] */ UINT uFlags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectionMarkedItem )( 
            IFolderView * This,
            /* [out] */ int *piItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetFocusedItem )( 
            IFolderView * This,
            /* [out] */ int *piItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemPosition )( 
            IFolderView * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [out] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *GetSpacing )( 
            IFolderView * This,
            /* [full][out][in] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultSpacing )( 
            IFolderView * This,
            /* [out] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *GetAutoArrange )( 
            IFolderView * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectItem )( 
            IFolderView * This,
            /* [in] */ int iItem,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAndPositionItems )( 
            IFolderView * This,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [size_is][full][in] */ POINT *apt,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IFolderViewVtbl;

    interface IFolderView
    {
        CONST_VTBL struct IFolderViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderView_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderView_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderView_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderView_GetCurrentViewMode(This,pViewMode)	\
    ( (This)->lpVtbl -> GetCurrentViewMode(This,pViewMode) ) 

#define IFolderView_SetCurrentViewMode(This,ViewMode)	\
    ( (This)->lpVtbl -> SetCurrentViewMode(This,ViewMode) ) 

#define IFolderView_GetFolder(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetFolder(This,riid,ppv) ) 

#define IFolderView_Item(This,iItemIndex,ppidl)	\
    ( (This)->lpVtbl -> Item(This,iItemIndex,ppidl) ) 

#define IFolderView_ItemCount(This,uFlags,pcItems)	\
    ( (This)->lpVtbl -> ItemCount(This,uFlags,pcItems) ) 

#define IFolderView_Items(This,uFlags,riid,ppv)	\
    ( (This)->lpVtbl -> Items(This,uFlags,riid,ppv) ) 

#define IFolderView_GetSelectionMarkedItem(This,piItem)	\
    ( (This)->lpVtbl -> GetSelectionMarkedItem(This,piItem) ) 

#define IFolderView_GetFocusedItem(This,piItem)	\
    ( (This)->lpVtbl -> GetFocusedItem(This,piItem) ) 

#define IFolderView_GetItemPosition(This,pidl,ppt)	\
    ( (This)->lpVtbl -> GetItemPosition(This,pidl,ppt) ) 

#define IFolderView_GetSpacing(This,ppt)	\
    ( (This)->lpVtbl -> GetSpacing(This,ppt) ) 

#define IFolderView_GetDefaultSpacing(This,ppt)	\
    ( (This)->lpVtbl -> GetDefaultSpacing(This,ppt) ) 

#define IFolderView_GetAutoArrange(This)	\
    ( (This)->lpVtbl -> GetAutoArrange(This) ) 

#define IFolderView_SelectItem(This,iItem,dwFlags)	\
    ( (This)->lpVtbl -> SelectItem(This,iItem,dwFlags) ) 

#define IFolderView_SelectAndPositionItems(This,cidl,apidl,apt,dwFlags)	\
    ( (This)->lpVtbl -> SelectAndPositionItems(This,cidl,apidl,apt,dwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFolderView_GetCurrentViewMode_Proxy( 
    IFolderView * This,
    /* [out][in] */ UINT *pViewMode);


void __RPC_STUB IFolderView_GetCurrentViewMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_SetCurrentViewMode_Proxy( 
    IFolderView * This,
    /* [in] */ UINT ViewMode);


void __RPC_STUB IFolderView_SetCurrentViewMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetFolder_Proxy( 
    IFolderView * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IFolderView_GetFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_Item_Proxy( 
    IFolderView * This,
    /* [in] */ int iItemIndex,
    /* [out] */ PITEMID_CHILD *ppidl);


void __RPC_STUB IFolderView_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_ItemCount_Proxy( 
    IFolderView * This,
    /* [in] */ UINT uFlags,
    /* [out] */ int *pcItems);


void __RPC_STUB IFolderView_ItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_Items_Proxy( 
    IFolderView * This,
    /* [in] */ UINT uFlags,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IFolderView_Items_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetSelectionMarkedItem_Proxy( 
    IFolderView * This,
    /* [out] */ int *piItem);


void __RPC_STUB IFolderView_GetSelectionMarkedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetFocusedItem_Proxy( 
    IFolderView * This,
    /* [out] */ int *piItem);


void __RPC_STUB IFolderView_GetFocusedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetItemPosition_Proxy( 
    IFolderView * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [out] */ POINT *ppt);


void __RPC_STUB IFolderView_GetItemPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetSpacing_Proxy( 
    IFolderView * This,
    /* [full][out][in] */ POINT *ppt);


void __RPC_STUB IFolderView_GetSpacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetDefaultSpacing_Proxy( 
    IFolderView * This,
    /* [out] */ POINT *ppt);


void __RPC_STUB IFolderView_GetDefaultSpacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_GetAutoArrange_Proxy( 
    IFolderView * This);


void __RPC_STUB IFolderView_GetAutoArrange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_SelectItem_Proxy( 
    IFolderView * This,
    /* [in] */ int iItem,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IFolderView_SelectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView_SelectAndPositionItems_Proxy( 
    IFolderView * This,
    /* [in] */ UINT cidl,
    /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
    /* [size_is][full][in] */ POINT *apt,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IFolderView_SelectAndPositionItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderView_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0214 */
/* [local] */ 

#define SID_SFolderView IID_IFolderView    // folder view, usually IFolderView
#if (_WIN32_IE >= 0x0500)
typedef /* [v1_enum] */ 
enum tagSORTDIRECTION
    {	SORT_DESCENDING	= -1,
	SORT_ASCENDING	= 1
    } 	SORTDIRECTION;

typedef struct tagSORTCOLUMN
    {
    PROPERTYKEY propkey;
    SORTDIRECTION Direction;
    } 	SORTCOLUMN;

typedef /* [v1_enum] */ 
enum tagFOLDERVIEWWATERMARKFLAGS
    {	FVWF_DEFAULT	= 0,
	FVWF_ALPHABLEND	= 0x1
    } 	FOLDERVIEWWATERMARKFLAGS;

#define FVST_EMPTYTEXT ((UINT)0)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0214_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0214_v0_0_s_ifspec;

#ifndef __IFolderView2_INTERFACE_DEFINED__
#define __IFolderView2_INTERFACE_DEFINED__

/* interface IFolderView2 */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFolderView2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A606F49-DBA2-4989-B6E4-48F36C3E211A")
    IFolderView2 : public IFolderView
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGroupBy( 
            /* [in] */ REFPROPERTYKEY propkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGroupBy( 
            /* [out] */ PROPERTYKEY *pkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewProperty( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ REFPROPERTYKEY propkey,
            /* [out] */ PROPVARIANT *ppropvar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetViewProperty( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ REFPROPERTYKEY propkey,
            /* [in] */ const PROPVARIANT *ppropvar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTileViewProperties( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ LPCWSTR pszPropList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetExtendedTileViewProperties( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ LPCWSTR pszPropList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetText( 
            /* [in] */ UINT ifvri,
            /* [in] */ LPCOLESTR pwszText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIconSize( 
            /* [out] */ int *piImageSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIconSize( 
            /* [in] */ int iImageSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentFolderFlags( 
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCurrentFolderFlags( 
            /* [in] */ DWORD dwMask,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSortColumnCount( 
            /* [out] */ int *pcColumns) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSortColumns( 
            /* [size_is][out] */ SORTCOLUMN *rgSortColumns,
            /* [in] */ int cColumns) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSortColumns( 
            /* [size_is][in] */ const SORTCOLUMN *rgSortColumns,
            /* [in] */ int cColumns) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVisibleItem( 
            /* [in] */ int iStart,
            /* [out] */ int *piItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectedItem( 
            /* [in] */ int iStart,
            /* [out] */ int *piItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRedraw( 
            /* [in] */ BOOL bRedrawOn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetWatermark( 
            /* [in] */ HBITMAP hbmp,
            /* [in] */ FOLDERVIEWWATERMARKFLAGS fvwf) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTextColor( 
            /* [in] */ COLORREF crBackground,
            /* [in] */ COLORREF crForeground) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSelectionState( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [out] */ DWORD *pdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderView2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderView2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderView2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderView2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentViewMode )( 
            IFolderView2 * This,
            /* [out][in] */ UINT *pViewMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetCurrentViewMode )( 
            IFolderView2 * This,
            /* [in] */ UINT ViewMode);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolder )( 
            IFolderView2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *Item )( 
            IFolderView2 * This,
            /* [in] */ int iItemIndex,
            /* [out] */ PITEMID_CHILD *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *ItemCount )( 
            IFolderView2 * This,
            /* [in] */ UINT uFlags,
            /* [out] */ int *pcItems);
        
        HRESULT ( STDMETHODCALLTYPE *Items )( 
            IFolderView2 * This,
            /* [in] */ UINT uFlags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectionMarkedItem )( 
            IFolderView2 * This,
            /* [out] */ int *piItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetFocusedItem )( 
            IFolderView2 * This,
            /* [out] */ int *piItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemPosition )( 
            IFolderView2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [out] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *GetSpacing )( 
            IFolderView2 * This,
            /* [full][out][in] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultSpacing )( 
            IFolderView2 * This,
            /* [out] */ POINT *ppt);
        
        HRESULT ( STDMETHODCALLTYPE *GetAutoArrange )( 
            IFolderView2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SelectItem )( 
            IFolderView2 * This,
            /* [in] */ int iItem,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SelectAndPositionItems )( 
            IFolderView2 * This,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [size_is][full][in] */ POINT *apt,
            /* [in] */ DWORD dwFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetGroupBy )( 
            IFolderView2 * This,
            /* [in] */ REFPROPERTYKEY propkey);
        
        HRESULT ( STDMETHODCALLTYPE *GetGroupBy )( 
            IFolderView2 * This,
            /* [out] */ PROPERTYKEY *pkey);
        
        HRESULT ( STDMETHODCALLTYPE *GetViewProperty )( 
            IFolderView2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ REFPROPERTYKEY propkey,
            /* [out] */ PROPVARIANT *ppropvar);
        
        HRESULT ( STDMETHODCALLTYPE *SetViewProperty )( 
            IFolderView2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ REFPROPERTYKEY propkey,
            /* [in] */ const PROPVARIANT *ppropvar);
        
        HRESULT ( STDMETHODCALLTYPE *SetTileViewProperties )( 
            IFolderView2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ LPCWSTR pszPropList);
        
        HRESULT ( STDMETHODCALLTYPE *SetExtendedTileViewProperties )( 
            IFolderView2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ LPCWSTR pszPropList);
        
        HRESULT ( STDMETHODCALLTYPE *SetText )( 
            IFolderView2 * This,
            /* [in] */ UINT ifvri,
            /* [in] */ LPCOLESTR pwszText);
        
        HRESULT ( STDMETHODCALLTYPE *GetIconSize )( 
            IFolderView2 * This,
            /* [out] */ int *piImageSize);
        
        HRESULT ( STDMETHODCALLTYPE *SetIconSize )( 
            IFolderView2 * This,
            /* [in] */ int iImageSize);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentFolderFlags )( 
            IFolderView2 * This,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetCurrentFolderFlags )( 
            IFolderView2 * This,
            /* [in] */ DWORD dwMask,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetSortColumnCount )( 
            IFolderView2 * This,
            /* [out] */ int *pcColumns);
        
        HRESULT ( STDMETHODCALLTYPE *GetSortColumns )( 
            IFolderView2 * This,
            /* [size_is][out] */ SORTCOLUMN *rgSortColumns,
            /* [in] */ int cColumns);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSortColumns )( 
            IFolderView2 * This,
            /* [size_is][in] */ const SORTCOLUMN *rgSortColumns,
            /* [in] */ int cColumns);
        
        HRESULT ( STDMETHODCALLTYPE *GetVisibleItem )( 
            IFolderView2 * This,
            /* [in] */ int iStart,
            /* [out] */ int *piItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectedItem )( 
            IFolderView2 * This,
            /* [in] */ int iStart,
            /* [out] */ int *piItem);
        
        HRESULT ( STDMETHODCALLTYPE *SetRedraw )( 
            IFolderView2 * This,
            /* [in] */ BOOL bRedrawOn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetWatermark )( 
            IFolderView2 * This,
            /* [in] */ HBITMAP hbmp,
            /* [in] */ FOLDERVIEWWATERMARKFLAGS fvwf);
        
        HRESULT ( STDMETHODCALLTYPE *SetTextColor )( 
            IFolderView2 * This,
            /* [in] */ COLORREF crBackground,
            /* [in] */ COLORREF crForeground);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSelectionState )( 
            IFolderView2 * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [out] */ DWORD *pdwFlags);
        
        END_INTERFACE
    } IFolderView2Vtbl;

    interface IFolderView2
    {
        CONST_VTBL struct IFolderView2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderView2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderView2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderView2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderView2_GetCurrentViewMode(This,pViewMode)	\
    ( (This)->lpVtbl -> GetCurrentViewMode(This,pViewMode) ) 

#define IFolderView2_SetCurrentViewMode(This,ViewMode)	\
    ( (This)->lpVtbl -> SetCurrentViewMode(This,ViewMode) ) 

#define IFolderView2_GetFolder(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetFolder(This,riid,ppv) ) 

#define IFolderView2_Item(This,iItemIndex,ppidl)	\
    ( (This)->lpVtbl -> Item(This,iItemIndex,ppidl) ) 

#define IFolderView2_ItemCount(This,uFlags,pcItems)	\
    ( (This)->lpVtbl -> ItemCount(This,uFlags,pcItems) ) 

#define IFolderView2_Items(This,uFlags,riid,ppv)	\
    ( (This)->lpVtbl -> Items(This,uFlags,riid,ppv) ) 

#define IFolderView2_GetSelectionMarkedItem(This,piItem)	\
    ( (This)->lpVtbl -> GetSelectionMarkedItem(This,piItem) ) 

#define IFolderView2_GetFocusedItem(This,piItem)	\
    ( (This)->lpVtbl -> GetFocusedItem(This,piItem) ) 

#define IFolderView2_GetItemPosition(This,pidl,ppt)	\
    ( (This)->lpVtbl -> GetItemPosition(This,pidl,ppt) ) 

#define IFolderView2_GetSpacing(This,ppt)	\
    ( (This)->lpVtbl -> GetSpacing(This,ppt) ) 

#define IFolderView2_GetDefaultSpacing(This,ppt)	\
    ( (This)->lpVtbl -> GetDefaultSpacing(This,ppt) ) 

#define IFolderView2_GetAutoArrange(This)	\
    ( (This)->lpVtbl -> GetAutoArrange(This) ) 

#define IFolderView2_SelectItem(This,iItem,dwFlags)	\
    ( (This)->lpVtbl -> SelectItem(This,iItem,dwFlags) ) 

#define IFolderView2_SelectAndPositionItems(This,cidl,apidl,apt,dwFlags)	\
    ( (This)->lpVtbl -> SelectAndPositionItems(This,cidl,apidl,apt,dwFlags) ) 


#define IFolderView2_SetGroupBy(This,propkey)	\
    ( (This)->lpVtbl -> SetGroupBy(This,propkey) ) 

#define IFolderView2_GetGroupBy(This,pkey)	\
    ( (This)->lpVtbl -> GetGroupBy(This,pkey) ) 

#define IFolderView2_GetViewProperty(This,pidl,propkey,ppropvar)	\
    ( (This)->lpVtbl -> GetViewProperty(This,pidl,propkey,ppropvar) ) 

#define IFolderView2_SetViewProperty(This,pidl,propkey,ppropvar)	\
    ( (This)->lpVtbl -> SetViewProperty(This,pidl,propkey,ppropvar) ) 

#define IFolderView2_SetTileViewProperties(This,pidl,pszPropList)	\
    ( (This)->lpVtbl -> SetTileViewProperties(This,pidl,pszPropList) ) 

#define IFolderView2_SetExtendedTileViewProperties(This,pidl,pszPropList)	\
    ( (This)->lpVtbl -> SetExtendedTileViewProperties(This,pidl,pszPropList) ) 

#define IFolderView2_SetText(This,ifvri,pwszText)	\
    ( (This)->lpVtbl -> SetText(This,ifvri,pwszText) ) 

#define IFolderView2_GetIconSize(This,piImageSize)	\
    ( (This)->lpVtbl -> GetIconSize(This,piImageSize) ) 

#define IFolderView2_SetIconSize(This,iImageSize)	\
    ( (This)->lpVtbl -> SetIconSize(This,iImageSize) ) 

#define IFolderView2_GetCurrentFolderFlags(This,pdwFlags)	\
    ( (This)->lpVtbl -> GetCurrentFolderFlags(This,pdwFlags) ) 

#define IFolderView2_SetCurrentFolderFlags(This,dwMask,dwFlags)	\
    ( (This)->lpVtbl -> SetCurrentFolderFlags(This,dwMask,dwFlags) ) 

#define IFolderView2_GetSortColumnCount(This,pcColumns)	\
    ( (This)->lpVtbl -> GetSortColumnCount(This,pcColumns) ) 

#define IFolderView2_GetSortColumns(This,rgSortColumns,cColumns)	\
    ( (This)->lpVtbl -> GetSortColumns(This,rgSortColumns,cColumns) ) 

#define IFolderView2_SetSortColumns(This,rgSortColumns,cColumns)	\
    ( (This)->lpVtbl -> SetSortColumns(This,rgSortColumns,cColumns) ) 

#define IFolderView2_GetVisibleItem(This,iStart,piItem)	\
    ( (This)->lpVtbl -> GetVisibleItem(This,iStart,piItem) ) 

#define IFolderView2_GetSelectedItem(This,iStart,piItem)	\
    ( (This)->lpVtbl -> GetSelectedItem(This,iStart,piItem) ) 

#define IFolderView2_SetRedraw(This,bRedrawOn)	\
    ( (This)->lpVtbl -> SetRedraw(This,bRedrawOn) ) 

#define IFolderView2_SetWatermark(This,hbmp,fvwf)	\
    ( (This)->lpVtbl -> SetWatermark(This,hbmp,fvwf) ) 

#define IFolderView2_SetTextColor(This,crBackground,crForeground)	\
    ( (This)->lpVtbl -> SetTextColor(This,crBackground,crForeground) ) 

#define IFolderView2_GetSelectionState(This,pidl,pdwFlags)	\
    ( (This)->lpVtbl -> GetSelectionState(This,pidl,pdwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFolderView2_SetGroupBy_Proxy( 
    IFolderView2 * This,
    /* [in] */ REFPROPERTYKEY propkey);


void __RPC_STUB IFolderView2_SetGroupBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetGroupBy_Proxy( 
    IFolderView2 * This,
    /* [out] */ PROPERTYKEY *pkey);


void __RPC_STUB IFolderView2_GetGroupBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetViewProperty_Proxy( 
    IFolderView2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ REFPROPERTYKEY propkey,
    /* [out] */ PROPVARIANT *ppropvar);


void __RPC_STUB IFolderView2_GetViewProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetViewProperty_Proxy( 
    IFolderView2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ REFPROPERTYKEY propkey,
    /* [in] */ const PROPVARIANT *ppropvar);


void __RPC_STUB IFolderView2_SetViewProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetTileViewProperties_Proxy( 
    IFolderView2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ LPCWSTR pszPropList);


void __RPC_STUB IFolderView2_SetTileViewProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetExtendedTileViewProperties_Proxy( 
    IFolderView2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ LPCWSTR pszPropList);


void __RPC_STUB IFolderView2_SetExtendedTileViewProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetText_Proxy( 
    IFolderView2 * This,
    /* [in] */ UINT ifvri,
    /* [in] */ LPCOLESTR pwszText);


void __RPC_STUB IFolderView2_SetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetIconSize_Proxy( 
    IFolderView2 * This,
    /* [out] */ int *piImageSize);


void __RPC_STUB IFolderView2_GetIconSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetIconSize_Proxy( 
    IFolderView2 * This,
    /* [in] */ int iImageSize);


void __RPC_STUB IFolderView2_SetIconSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetCurrentFolderFlags_Proxy( 
    IFolderView2 * This,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IFolderView2_GetCurrentFolderFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetCurrentFolderFlags_Proxy( 
    IFolderView2 * This,
    /* [in] */ DWORD dwMask,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IFolderView2_SetCurrentFolderFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetSortColumnCount_Proxy( 
    IFolderView2 * This,
    /* [out] */ int *pcColumns);


void __RPC_STUB IFolderView2_GetSortColumnCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetSortColumns_Proxy( 
    IFolderView2 * This,
    /* [size_is][out] */ SORTCOLUMN *rgSortColumns,
    /* [in] */ int cColumns);


void __RPC_STUB IFolderView2_GetSortColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFolderView2_SetSortColumns_Proxy( 
    IFolderView2 * This,
    /* [size_is][in] */ const SORTCOLUMN *rgSortColumns,
    /* [in] */ int cColumns);


void __RPC_STUB IFolderView2_SetSortColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetVisibleItem_Proxy( 
    IFolderView2 * This,
    /* [in] */ int iStart,
    /* [out] */ int *piItem);


void __RPC_STUB IFolderView2_GetVisibleItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_GetSelectedItem_Proxy( 
    IFolderView2 * This,
    /* [in] */ int iStart,
    /* [out] */ int *piItem);


void __RPC_STUB IFolderView2_GetSelectedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetRedraw_Proxy( 
    IFolderView2 * This,
    /* [in] */ BOOL bRedrawOn);


void __RPC_STUB IFolderView2_SetRedraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFolderView2_SetWatermark_Proxy( 
    IFolderView2 * This,
    /* [in] */ HBITMAP hbmp,
    /* [in] */ FOLDERVIEWWATERMARKFLAGS fvwf);


void __RPC_STUB IFolderView2_SetWatermark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderView2_SetTextColor_Proxy( 
    IFolderView2 * This,
    /* [in] */ COLORREF crBackground,
    /* [in] */ COLORREF crForeground);


void __RPC_STUB IFolderView2_SetTextColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFolderView2_GetSelectionState_Proxy( 
    IFolderView2 * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IFolderView2_GetSelectionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderView2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0215 */
/* [local] */ 

#endif // (_WIN32_IE >= 0x0500)
#define CDBOSC_SETFOCUS     0x00000000
#define CDBOSC_KILLFOCUS    0x00000001
#define CDBOSC_SELCHANGE    0x00000002
#define CDBOSC_RENAME       0x00000003
#define CDBOSC_STATECHANGE  0x00000004


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0215_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0215_v0_0_s_ifspec;

#ifndef __ICommDlgBrowser_INTERFACE_DEFINED__
#define __ICommDlgBrowser_INTERFACE_DEFINED__

/* interface ICommDlgBrowser */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_ICommDlgBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214F1-0000-0000-C000-000000000046")
    ICommDlgBrowser : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnDefaultCommand( 
            /* [in] */ IShellView *ppshv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnStateChange( 
            /* [in] */ IShellView *ppshv,
            /* [in] */ ULONG uChange) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IncludeObject( 
            /* [in] */ IShellView *ppshv,
            /* [in] */ PCUITEMID_CHILD pidl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommDlgBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommDlgBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommDlgBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommDlgBrowser * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnDefaultCommand )( 
            ICommDlgBrowser * This,
            /* [in] */ IShellView *ppshv);
        
        HRESULT ( STDMETHODCALLTYPE *OnStateChange )( 
            ICommDlgBrowser * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ ULONG uChange);
        
        HRESULT ( STDMETHODCALLTYPE *IncludeObject )( 
            ICommDlgBrowser * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        END_INTERFACE
    } ICommDlgBrowserVtbl;

    interface ICommDlgBrowser
    {
        CONST_VTBL struct ICommDlgBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommDlgBrowser_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICommDlgBrowser_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICommDlgBrowser_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICommDlgBrowser_OnDefaultCommand(This,ppshv)	\
    ( (This)->lpVtbl -> OnDefaultCommand(This,ppshv) ) 

#define ICommDlgBrowser_OnStateChange(This,ppshv,uChange)	\
    ( (This)->lpVtbl -> OnStateChange(This,ppshv,uChange) ) 

#define ICommDlgBrowser_IncludeObject(This,ppshv,pidl)	\
    ( (This)->lpVtbl -> IncludeObject(This,ppshv,pidl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommDlgBrowser_OnDefaultCommand_Proxy( 
    ICommDlgBrowser * This,
    /* [in] */ IShellView *ppshv);


void __RPC_STUB ICommDlgBrowser_OnDefaultCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommDlgBrowser_OnStateChange_Proxy( 
    ICommDlgBrowser * This,
    /* [in] */ IShellView *ppshv,
    /* [in] */ ULONG uChange);


void __RPC_STUB ICommDlgBrowser_OnStateChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommDlgBrowser_IncludeObject_Proxy( 
    ICommDlgBrowser * This,
    /* [in] */ IShellView *ppshv,
    /* [in] */ PCUITEMID_CHILD pidl);


void __RPC_STUB ICommDlgBrowser_IncludeObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommDlgBrowser_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0216 */
/* [local] */ 

typedef ICommDlgBrowser *LPCOMMDLGBROWSER;

#define CDB2N_CONTEXTMENU_DONE  0x00000001
#define CDB2N_CONTEXTMENU_START 0x00000002
#define CDB2GVF_SHOWALLFILES        0x00000001
#define CDB2GVF_ISFILESAVE          0x00000002 // is file save, else file open
#define CDB2GVF_ALLOWPREVIEWPANE    0x00000004
#define CDB2GVF_NOSELECTVERB        0x00000008


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0216_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0216_v0_0_s_ifspec;

#ifndef __ICommDlgBrowser2_INTERFACE_DEFINED__
#define __ICommDlgBrowser2_INTERFACE_DEFINED__

/* interface ICommDlgBrowser2 */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_ICommDlgBrowser2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10339516-2894-11d2-9039-00C04F8EEB3E")
    ICommDlgBrowser2 : public ICommDlgBrowser
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ IShellView *ppshv,
            /* [in] */ DWORD dwNotifyType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultMenuText( 
            /* [in] */ IShellView *ppshv,
            /* [size_is][out] */ WCHAR *pszText,
            /* [in] */ int cchMax) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewFlags( 
            /* [out] */ DWORD *pdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommDlgBrowser2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommDlgBrowser2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommDlgBrowser2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommDlgBrowser2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnDefaultCommand )( 
            ICommDlgBrowser2 * This,
            /* [in] */ IShellView *ppshv);
        
        HRESULT ( STDMETHODCALLTYPE *OnStateChange )( 
            ICommDlgBrowser2 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ ULONG uChange);
        
        HRESULT ( STDMETHODCALLTYPE *IncludeObject )( 
            ICommDlgBrowser2 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            ICommDlgBrowser2 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ DWORD dwNotifyType);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultMenuText )( 
            ICommDlgBrowser2 * This,
            /* [in] */ IShellView *ppshv,
            /* [size_is][out] */ WCHAR *pszText,
            /* [in] */ int cchMax);
        
        HRESULT ( STDMETHODCALLTYPE *GetViewFlags )( 
            ICommDlgBrowser2 * This,
            /* [out] */ DWORD *pdwFlags);
        
        END_INTERFACE
    } ICommDlgBrowser2Vtbl;

    interface ICommDlgBrowser2
    {
        CONST_VTBL struct ICommDlgBrowser2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommDlgBrowser2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICommDlgBrowser2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICommDlgBrowser2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICommDlgBrowser2_OnDefaultCommand(This,ppshv)	\
    ( (This)->lpVtbl -> OnDefaultCommand(This,ppshv) ) 

#define ICommDlgBrowser2_OnStateChange(This,ppshv,uChange)	\
    ( (This)->lpVtbl -> OnStateChange(This,ppshv,uChange) ) 

#define ICommDlgBrowser2_IncludeObject(This,ppshv,pidl)	\
    ( (This)->lpVtbl -> IncludeObject(This,ppshv,pidl) ) 


#define ICommDlgBrowser2_Notify(This,ppshv,dwNotifyType)	\
    ( (This)->lpVtbl -> Notify(This,ppshv,dwNotifyType) ) 

#define ICommDlgBrowser2_GetDefaultMenuText(This,ppshv,pszText,cchMax)	\
    ( (This)->lpVtbl -> GetDefaultMenuText(This,ppshv,pszText,cchMax) ) 

#define ICommDlgBrowser2_GetViewFlags(This,pdwFlags)	\
    ( (This)->lpVtbl -> GetViewFlags(This,pdwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommDlgBrowser2_Notify_Proxy( 
    ICommDlgBrowser2 * This,
    /* [in] */ IShellView *ppshv,
    /* [in] */ DWORD dwNotifyType);


void __RPC_STUB ICommDlgBrowser2_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommDlgBrowser2_GetDefaultMenuText_Proxy( 
    ICommDlgBrowser2 * This,
    /* [in] */ IShellView *ppshv,
    /* [size_is][out] */ WCHAR *pszText,
    /* [in] */ int cchMax);


void __RPC_STUB ICommDlgBrowser2_GetDefaultMenuText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommDlgBrowser2_GetViewFlags_Proxy( 
    ICommDlgBrowser2 * This,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB ICommDlgBrowser2_GetViewFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommDlgBrowser2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0217 */
/* [local] */ 

typedef ICommDlgBrowser2 *LPCOMMDLGBROWSER2;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0217_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0217_v0_0_s_ifspec;

#ifndef __ICommDlgBrowser3_INTERFACE_DEFINED__
#define __ICommDlgBrowser3_INTERFACE_DEFINED__

/* interface ICommDlgBrowser3 */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_ICommDlgBrowser3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1c20815f-dd28-4278-9492-17af47143429")
    ICommDlgBrowser3 : public ICommDlgBrowser2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnColumnClicked( 
            /* [in] */ IShellView *ppshv,
            /* [in] */ int iColumn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentFilter( 
            /* [size_is][out] */ LPWSTR pszFileSpec,
            /* [in] */ int cchFileSpec) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommDlgBrowser3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommDlgBrowser3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommDlgBrowser3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommDlgBrowser3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnDefaultCommand )( 
            ICommDlgBrowser3 * This,
            /* [in] */ IShellView *ppshv);
        
        HRESULT ( STDMETHODCALLTYPE *OnStateChange )( 
            ICommDlgBrowser3 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ ULONG uChange);
        
        HRESULT ( STDMETHODCALLTYPE *IncludeObject )( 
            ICommDlgBrowser3 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *Notify )( 
            ICommDlgBrowser3 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ DWORD dwNotifyType);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultMenuText )( 
            ICommDlgBrowser3 * This,
            /* [in] */ IShellView *ppshv,
            /* [size_is][out] */ WCHAR *pszText,
            /* [in] */ int cchMax);
        
        HRESULT ( STDMETHODCALLTYPE *GetViewFlags )( 
            ICommDlgBrowser3 * This,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *OnColumnClicked )( 
            ICommDlgBrowser3 * This,
            /* [in] */ IShellView *ppshv,
            /* [in] */ int iColumn);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentFilter )( 
            ICommDlgBrowser3 * This,
            /* [size_is][out] */ LPWSTR pszFileSpec,
            /* [in] */ int cchFileSpec);
        
        END_INTERFACE
    } ICommDlgBrowser3Vtbl;

    interface ICommDlgBrowser3
    {
        CONST_VTBL struct ICommDlgBrowser3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommDlgBrowser3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICommDlgBrowser3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICommDlgBrowser3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICommDlgBrowser3_OnDefaultCommand(This,ppshv)	\
    ( (This)->lpVtbl -> OnDefaultCommand(This,ppshv) ) 

#define ICommDlgBrowser3_OnStateChange(This,ppshv,uChange)	\
    ( (This)->lpVtbl -> OnStateChange(This,ppshv,uChange) ) 

#define ICommDlgBrowser3_IncludeObject(This,ppshv,pidl)	\
    ( (This)->lpVtbl -> IncludeObject(This,ppshv,pidl) ) 


#define ICommDlgBrowser3_Notify(This,ppshv,dwNotifyType)	\
    ( (This)->lpVtbl -> Notify(This,ppshv,dwNotifyType) ) 

#define ICommDlgBrowser3_GetDefaultMenuText(This,ppshv,pszText,cchMax)	\
    ( (This)->lpVtbl -> GetDefaultMenuText(This,ppshv,pszText,cchMax) ) 

#define ICommDlgBrowser3_GetViewFlags(This,pdwFlags)	\
    ( (This)->lpVtbl -> GetViewFlags(This,pdwFlags) ) 


#define ICommDlgBrowser3_OnColumnClicked(This,ppshv,iColumn)	\
    ( (This)->lpVtbl -> OnColumnClicked(This,ppshv,iColumn) ) 

#define ICommDlgBrowser3_GetCurrentFilter(This,pszFileSpec,cchFileSpec)	\
    ( (This)->lpVtbl -> GetCurrentFilter(This,pszFileSpec,cchFileSpec) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICommDlgBrowser3_OnColumnClicked_Proxy( 
    ICommDlgBrowser3 * This,
    /* [in] */ IShellView *ppshv,
    /* [in] */ int iColumn);


void __RPC_STUB ICommDlgBrowser3_OnColumnClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICommDlgBrowser3_GetCurrentFilter_Proxy( 
    ICommDlgBrowser3 * This,
    /* [size_is][out] */ LPWSTR pszFileSpec,
    /* [in] */ int cchFileSpec);


void __RPC_STUB ICommDlgBrowser3_GetCurrentFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommDlgBrowser3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0218 */
/* [local] */ 

#if (_WIN32_IE >= 0x0501)
typedef /* [v1_enum] */ 
enum tagCM_MASK
    {	CM_MASK_WIDTH	= 0x1,
	CM_MASK_DEFAULTWIDTH	= 0x2,
	CM_MASK_NAME	= 0x4,
	CM_MASK_STATE	= 0x8
    } 	CM_MASK;

typedef /* [v1_enum] */ 
enum tagCM_STATE
    {	CM_STATE_NONE	= 0,
	CM_STATE_VISIBLE	= 0x1,
	CM_STATE_ISLINK	= 0x2,
	CM_STATE_DETAILS	= 0x4,
	CM_STATE_FIXEDWIDTH	= 0x8
    } 	CM_STATE;

typedef /* [v1_enum] */ 
enum tagCM_ENUM_FLAGS
    {	CM_ENUM_ALL	= 0x1,
	CM_ENUM_VISIBLE	= 0x2,
	CM_ENUM_DETAILS	= 0x4,
	CM_ENUM_TILE	= 0x8
    } 	CM_ENUM_FLAGS;

typedef /* [v1_enum] */ 
enum tagCM_SET_WIDTH_VALUE
    {	CM_WIDTH_USEDEFAULT	= -1,
	CM_WIDTH_AUTOSIZE	= -2
    } 	CM_SET_WIDTH_VALUE;

typedef struct tagCM_COLUMNINFO
    {
    DWORD cbSize;
    DWORD dwMask;
    DWORD dwState;
    UINT uWidth;
    UINT uDefaultWidth;
    WCHAR wszName[ 80 ];
    } 	CM_COLUMNINFO;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0218_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0218_v0_0_s_ifspec;

#ifndef __IColumnManager_INTERFACE_DEFINED__
#define __IColumnManager_INTERFACE_DEFINED__

/* interface IColumnManager */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IColumnManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5e275cc5-bd21-45d1-a8a9-fc592444266a")
    IColumnManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetColumnInfo( 
            /* [in] */ REFPROPERTYKEY propkey,
            /* [in] */ const CM_COLUMNINFO *pcmci) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColumnInfo( 
            /* [in] */ REFPROPERTYKEY propkey,
            /* [out] */ CM_COLUMNINFO *pcmci) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColumnCount( 
            /* [in] */ CM_ENUM_FLAGS dwFlags,
            /* [out] */ UINT *puCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColumns( 
            /* [in] */ CM_ENUM_FLAGS dwFlags,
            /* [size_is][out] */ PROPERTYKEY *rgkeyOrder,
            /* [in] */ UINT cColumns) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetColumns( 
            /* [size_is][in] */ const PROPERTYKEY *rgkeyOrder,
            /* [in] */ UINT cVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColumnManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IColumnManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IColumnManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IColumnManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetColumnInfo )( 
            IColumnManager * This,
            /* [in] */ REFPROPERTYKEY propkey,
            /* [in] */ const CM_COLUMNINFO *pcmci);
        
        HRESULT ( STDMETHODCALLTYPE *GetColumnInfo )( 
            IColumnManager * This,
            /* [in] */ REFPROPERTYKEY propkey,
            /* [out] */ CM_COLUMNINFO *pcmci);
        
        HRESULT ( STDMETHODCALLTYPE *GetColumnCount )( 
            IColumnManager * This,
            /* [in] */ CM_ENUM_FLAGS dwFlags,
            /* [out] */ UINT *puCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetColumns )( 
            IColumnManager * This,
            /* [in] */ CM_ENUM_FLAGS dwFlags,
            /* [size_is][out] */ PROPERTYKEY *rgkeyOrder,
            /* [in] */ UINT cColumns);
        
        HRESULT ( STDMETHODCALLTYPE *SetColumns )( 
            IColumnManager * This,
            /* [size_is][in] */ const PROPERTYKEY *rgkeyOrder,
            /* [in] */ UINT cVisible);
        
        END_INTERFACE
    } IColumnManagerVtbl;

    interface IColumnManager
    {
        CONST_VTBL struct IColumnManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumnManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IColumnManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IColumnManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IColumnManager_SetColumnInfo(This,propkey,pcmci)	\
    ( (This)->lpVtbl -> SetColumnInfo(This,propkey,pcmci) ) 

#define IColumnManager_GetColumnInfo(This,propkey,pcmci)	\
    ( (This)->lpVtbl -> GetColumnInfo(This,propkey,pcmci) ) 

#define IColumnManager_GetColumnCount(This,dwFlags,puCount)	\
    ( (This)->lpVtbl -> GetColumnCount(This,dwFlags,puCount) ) 

#define IColumnManager_GetColumns(This,dwFlags,rgkeyOrder,cColumns)	\
    ( (This)->lpVtbl -> GetColumns(This,dwFlags,rgkeyOrder,cColumns) ) 

#define IColumnManager_SetColumns(This,rgkeyOrder,cVisible)	\
    ( (This)->lpVtbl -> SetColumns(This,rgkeyOrder,cVisible) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IColumnManager_SetColumnInfo_Proxy( 
    IColumnManager * This,
    /* [in] */ REFPROPERTYKEY propkey,
    /* [in] */ const CM_COLUMNINFO *pcmci);


void __RPC_STUB IColumnManager_SetColumnInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IColumnManager_GetColumnInfo_Proxy( 
    IColumnManager * This,
    /* [in] */ REFPROPERTYKEY propkey,
    /* [out] */ CM_COLUMNINFO *pcmci);


void __RPC_STUB IColumnManager_GetColumnInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IColumnManager_GetColumnCount_Proxy( 
    IColumnManager * This,
    /* [in] */ CM_ENUM_FLAGS dwFlags,
    /* [out] */ UINT *puCount);


void __RPC_STUB IColumnManager_GetColumnCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IColumnManager_GetColumns_Proxy( 
    IColumnManager * This,
    /* [in] */ CM_ENUM_FLAGS dwFlags,
    /* [size_is][out] */ PROPERTYKEY *rgkeyOrder,
    /* [in] */ UINT cColumns);


void __RPC_STUB IColumnManager_GetColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IColumnManager_SetColumns_Proxy( 
    IColumnManager * This,
    /* [size_is][in] */ const PROPERTYKEY *rgkeyOrder,
    /* [in] */ UINT cVisible);


void __RPC_STUB IColumnManager_SetColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColumnManager_INTERFACE_DEFINED__ */


#ifndef __IOrderView_INTERFACE_DEFINED__
#define __IOrderView_INTERFACE_DEFINED__

/* interface IOrderView */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IOrderView;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("470BCB4B-6DA7-437A-8846-ED51BA6059FA")
    IOrderView : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInsertMark( 
            /* [out] */ int *piInsert) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveObjects( 
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ UINT cidl,
            /* [in] */ int iInsert) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveObjectsUpDown( 
            /* [size_is][in] */ UINT *aiItem,
            /* [in] */ UINT ciItem,
            /* [in] */ BOOL fUp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOrderViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOrderView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOrderView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOrderView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetInsertMark )( 
            IOrderView * This,
            /* [out] */ int *piInsert);
        
        HRESULT ( STDMETHODCALLTYPE *MoveObjects )( 
            IOrderView * This,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [in] */ UINT cidl,
            /* [in] */ int iInsert);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveObjectsUpDown )( 
            IOrderView * This,
            /* [size_is][in] */ UINT *aiItem,
            /* [in] */ UINT ciItem,
            /* [in] */ BOOL fUp);
        
        END_INTERFACE
    } IOrderViewVtbl;

    interface IOrderView
    {
        CONST_VTBL struct IOrderViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOrderView_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOrderView_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOrderView_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOrderView_GetInsertMark(This,piInsert)	\
    ( (This)->lpVtbl -> GetInsertMark(This,piInsert) ) 

#define IOrderView_MoveObjects(This,apidl,cidl,iInsert)	\
    ( (This)->lpVtbl -> MoveObjects(This,apidl,cidl,iInsert) ) 

#define IOrderView_MoveObjectsUpDown(This,aiItem,ciItem,fUp)	\
    ( (This)->lpVtbl -> MoveObjectsUpDown(This,aiItem,ciItem,fUp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOrderView_GetInsertMark_Proxy( 
    IOrderView * This,
    /* [out] */ int *piInsert);


void __RPC_STUB IOrderView_GetInsertMark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOrderView_MoveObjects_Proxy( 
    IOrderView * This,
    /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
    /* [in] */ UINT cidl,
    /* [in] */ int iInsert);


void __RPC_STUB IOrderView_MoveObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IOrderView_MoveObjectsUpDown_Proxy( 
    IOrderView * This,
    /* [size_is][in] */ UINT *aiItem,
    /* [in] */ UINT ciItem,
    /* [in] */ BOOL fUp);


void __RPC_STUB IOrderView_MoveObjectsUpDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOrderView_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0220 */
/* [local] */ 

#endif // (_WIN32_IE >= 0x0501)
#ifdef _FIX_ENABLEMODELESS_CONFLICT
#undef    EnableModeless 
#endif


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0220_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0220_v0_0_s_ifspec;

#ifndef __IFolderFilterSite_INTERFACE_DEFINED__
#define __IFolderFilterSite_INTERFACE_DEFINED__

/* interface IFolderFilterSite */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFolderFilterSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0A651F5-B48B-11d2-B5ED-006097C686F6")
    IFolderFilterSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFilter( 
            /* [in] */ IUnknown *punk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderFilterSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderFilterSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderFilterSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderFilterSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFilter )( 
            IFolderFilterSite * This,
            /* [in] */ IUnknown *punk);
        
        END_INTERFACE
    } IFolderFilterSiteVtbl;

    interface IFolderFilterSite
    {
        CONST_VTBL struct IFolderFilterSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderFilterSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderFilterSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderFilterSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderFilterSite_SetFilter(This,punk)	\
    ( (This)->lpVtbl -> SetFilter(This,punk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFolderFilterSite_SetFilter_Proxy( 
    IFolderFilterSite * This,
    /* [in] */ IUnknown *punk);


void __RPC_STUB IFolderFilterSite_SetFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderFilterSite_INTERFACE_DEFINED__ */


#ifndef __IFolderFilter_INTERFACE_DEFINED__
#define __IFolderFilter_INTERFACE_DEFINED__

/* interface IFolderFilter */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFolderFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CC22886-DC8E-11d2-B1D0-00C04F8EEB3E")
    IFolderFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShouldShow( 
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ PCUITEMID_CHILD pidlItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEnumFlags( 
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ HWND *phwnd,
            /* [out] */ DWORD *pgrfFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShouldShow )( 
            IFolderFilter * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ PCUITEMID_CHILD pidlItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetEnumFlags )( 
            IFolderFilter * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ HWND *phwnd,
            /* [out] */ DWORD *pgrfFlags);
        
        END_INTERFACE
    } IFolderFilterVtbl;

    interface IFolderFilter
    {
        CONST_VTBL struct IFolderFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderFilter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderFilter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderFilter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderFilter_ShouldShow(This,psf,pidlFolder,pidlItem)	\
    ( (This)->lpVtbl -> ShouldShow(This,psf,pidlFolder,pidlItem) ) 

#define IFolderFilter_GetEnumFlags(This,psf,pidlFolder,phwnd,pgrfFlags)	\
    ( (This)->lpVtbl -> GetEnumFlags(This,psf,pidlFolder,phwnd,pgrfFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFolderFilter_ShouldShow_Proxy( 
    IFolderFilter * This,
    /* [in] */ IShellFolder *psf,
    /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
    /* [in] */ PCUITEMID_CHILD pidlItem);


void __RPC_STUB IFolderFilter_ShouldShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderFilter_GetEnumFlags_Proxy( 
    IFolderFilter * This,
    /* [in] */ IShellFolder *psf,
    /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
    /* [in] */ HWND *phwnd,
    /* [out] */ DWORD *pgrfFlags);


void __RPC_STUB IFolderFilter_GetEnumFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderFilter_INTERFACE_DEFINED__ */


#ifndef __IInputObjectSite_INTERFACE_DEFINED__
#define __IInputObjectSite_INTERFACE_DEFINED__

/* interface IInputObjectSite */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInputObjectSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1DB8392-7331-11D0-8C99-00A0C92DBFE8")
    IInputObjectSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnFocusChangeIS( 
            /* [in] */ IUnknown *punkObj,
            /* [in] */ BOOL fSetFocus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInputObjectSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInputObjectSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInputObjectSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInputObjectSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnFocusChangeIS )( 
            IInputObjectSite * This,
            /* [in] */ IUnknown *punkObj,
            /* [in] */ BOOL fSetFocus);
        
        END_INTERFACE
    } IInputObjectSiteVtbl;

    interface IInputObjectSite
    {
        CONST_VTBL struct IInputObjectSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInputObjectSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInputObjectSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInputObjectSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInputObjectSite_OnFocusChangeIS(This,punkObj,fSetFocus)	\
    ( (This)->lpVtbl -> OnFocusChangeIS(This,punkObj,fSetFocus) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IInputObjectSite_OnFocusChangeIS_Proxy( 
    IInputObjectSite * This,
    /* [in] */ IUnknown *punkObj,
    /* [in] */ BOOL fSetFocus);


void __RPC_STUB IInputObjectSite_OnFocusChangeIS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInputObjectSite_INTERFACE_DEFINED__ */


#ifndef __IInputObject_INTERFACE_DEFINED__
#define __IInputObject_INTERFACE_DEFINED__

/* interface IInputObject */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IInputObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("68284fAA-6A48-11D0-8c78-00C04fd918b4")
    IInputObject : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UIActivateIO( 
            /* [in] */ BOOL fActivate,
            /* [in] */ LPMSG lpMsg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HasFocusIO( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAcceleratorIO( 
            /* [in] */ LPMSG lpMsg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInputObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInputObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInputObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInputObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *UIActivateIO )( 
            IInputObject * This,
            /* [in] */ BOOL fActivate,
            /* [in] */ LPMSG lpMsg);
        
        HRESULT ( STDMETHODCALLTYPE *HasFocusIO )( 
            IInputObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAcceleratorIO )( 
            IInputObject * This,
            /* [in] */ LPMSG lpMsg);
        
        END_INTERFACE
    } IInputObjectVtbl;

    interface IInputObject
    {
        CONST_VTBL struct IInputObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInputObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInputObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInputObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInputObject_UIActivateIO(This,fActivate,lpMsg)	\
    ( (This)->lpVtbl -> UIActivateIO(This,fActivate,lpMsg) ) 

#define IInputObject_HasFocusIO(This)	\
    ( (This)->lpVtbl -> HasFocusIO(This) ) 

#define IInputObject_TranslateAcceleratorIO(This,lpMsg)	\
    ( (This)->lpVtbl -> TranslateAcceleratorIO(This,lpMsg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IInputObject_UIActivateIO_Proxy( 
    IInputObject * This,
    /* [in] */ BOOL fActivate,
    /* [in] */ LPMSG lpMsg);


void __RPC_STUB IInputObject_UIActivateIO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IInputObject_HasFocusIO_Proxy( 
    IInputObject * This);


void __RPC_STUB IInputObject_HasFocusIO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IInputObject_TranslateAcceleratorIO_Proxy( 
    IInputObject * This,
    /* [in] */ LPMSG lpMsg);


void __RPC_STUB IInputObject_TranslateAcceleratorIO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInputObject_INTERFACE_DEFINED__ */


#ifndef __IShellIcon_INTERFACE_DEFINED__
#define __IShellIcon_INTERFACE_DEFINED__

/* interface IShellIcon */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellIcon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214E5-0000-0000-C000-000000000046")
    IShellIcon : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetIconOf( 
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ UINT flags,
            /* [out] */ int *pIconIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellIconVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellIcon * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellIcon * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellIcon * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIconOf )( 
            IShellIcon * This,
            /* [in] */ PCUITEMID_CHILD pidl,
            /* [in] */ UINT flags,
            /* [out] */ int *pIconIndex);
        
        END_INTERFACE
    } IShellIconVtbl;

    interface IShellIcon
    {
        CONST_VTBL struct IShellIconVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellIcon_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellIcon_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellIcon_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellIcon_GetIconOf(This,pidl,flags,pIconIndex)	\
    ( (This)->lpVtbl -> GetIconOf(This,pidl,flags,pIconIndex) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellIcon_GetIconOf_Proxy( 
    IShellIcon * This,
    /* [in] */ PCUITEMID_CHILD pidl,
    /* [in] */ UINT flags,
    /* [out] */ int *pIconIndex);


void __RPC_STUB IShellIcon_GetIconOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellIcon_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0225 */
/* [local] */ 

typedef IShellIcon *LPSHELLICON;

#define SBSP_DEFBROWSER         0x0000
#define SBSP_SAMEBROWSER        0x0001
#define SBSP_NEWBROWSER         0x0002
#define SBSP_DEFMODE            0x0000
#define SBSP_OPENMODE           0x0010
#define SBSP_EXPLOREMODE        0x0020
#define SBSP_HELPMODE           0x0040 // IEUNIX : Help window uses this.
#define SBSP_NOTRANSFERHIST     0x0080
#define SBSP_ABSOLUTE           0x0000
#define SBSP_RELATIVE           0x1000
#define SBSP_PARENT             0x2000
#define SBSP_NAVIGATEBACK       0x4000
#define SBSP_NAVIGATEFORWARD    0x8000
#define SBSP_ALLOW_AUTONAVIGATE 0x10000
#define SBSP_NOAUTOSELECT       0x04000000
#define SBSP_WRITENOHISTORY     0x08000000
#define SBSP_REDIRECT                     0x40000000
#define SBSP_INITIATEDBYHLINKFRAME        0x80000000
#define FCW_STATUS      0x0001
#define FCW_TOOLBAR     0x0002
#define FCW_TREE        0x0003
#define FCW_INTERNETBAR 0x0006
#define FCW_PROGRESS    0x0008
#define FCT_MERGE       0x0001
#define FCT_CONFIGABLE  0x0002
#define FCT_ADDTOEND    0x0004
#ifdef _NEVER_
typedef LPARAM LPTBBUTTONSB;

#else //!_NEVER_
#include <commctrl.h>
typedef LPTBBUTTON LPTBBUTTONSB;
#endif //_NEVER_


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0225_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0225_v0_0_s_ifspec;

#ifndef __IShellBrowser_INTERFACE_DEFINED__
#define __IShellBrowser_INTERFACE_DEFINED__

/* interface IShellBrowser */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214E2-0000-0000-C000-000000000046")
    IShellBrowser : public IOleWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InsertMenusSB( 
            /* [in] */ HMENU hmenuShared,
            /* [out][in] */ LPOLEMENUGROUPWIDTHS lpMenuWidths) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMenuSB( 
            /* [in] */ HMENU hmenuShared,
            /* [in] */ HOLEMENU holemenuRes,
            /* [in] */ HWND hwndActiveObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveMenusSB( 
            /* [in] */ HMENU hmenuShared) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStatusTextSB( 
            /* [unique][in] */ LPCOLESTR pszStatusText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableModelessSB( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAcceleratorSB( 
            /* [in] */ MSG *pmsg,
            /* [in] */ WORD wID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BrowseObject( 
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ UINT wFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetViewStateStream( 
            /* [in] */ DWORD grfMode,
            /* [out] */ IStream **ppStrm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetControlWindow( 
            /* [in] */ UINT id,
            /* [out] */ HWND *phwnd) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SendControlMsg( 
            /* [in] */ UINT id,
            /* [in] */ UINT uMsg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam,
            /* [in] */ LRESULT *pret) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryActiveShellView( 
            /* [out] */ IShellView **ppshv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnViewWindowActive( 
            /* [in] */ IShellView *pshv) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetToolbarItems( 
            /* [in] */ LPTBBUTTONSB lpButtons,
            /* [in] */ UINT nButtons,
            /* [in] */ UINT uFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellBrowser * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IShellBrowser * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IShellBrowser * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *InsertMenusSB )( 
            IShellBrowser * This,
            /* [in] */ HMENU hmenuShared,
            /* [out][in] */ LPOLEMENUGROUPWIDTHS lpMenuWidths);
        
        HRESULT ( STDMETHODCALLTYPE *SetMenuSB )( 
            IShellBrowser * This,
            /* [in] */ HMENU hmenuShared,
            /* [in] */ HOLEMENU holemenuRes,
            /* [in] */ HWND hwndActiveObject);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveMenusSB )( 
            IShellBrowser * This,
            /* [in] */ HMENU hmenuShared);
        
        HRESULT ( STDMETHODCALLTYPE *SetStatusTextSB )( 
            IShellBrowser * This,
            /* [unique][in] */ LPCOLESTR pszStatusText);
        
        HRESULT ( STDMETHODCALLTYPE *EnableModelessSB )( 
            IShellBrowser * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateAcceleratorSB )( 
            IShellBrowser * This,
            /* [in] */ MSG *pmsg,
            /* [in] */ WORD wID);
        
        HRESULT ( STDMETHODCALLTYPE *BrowseObject )( 
            IShellBrowser * This,
            /* [in] */ PCUIDLIST_RELATIVE pidl,
            /* [in] */ UINT wFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetViewStateStream )( 
            IShellBrowser * This,
            /* [in] */ DWORD grfMode,
            /* [out] */ IStream **ppStrm);
        
        HRESULT ( STDMETHODCALLTYPE *GetControlWindow )( 
            IShellBrowser * This,
            /* [in] */ UINT id,
            /* [out] */ HWND *phwnd);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SendControlMsg )( 
            IShellBrowser * This,
            /* [in] */ UINT id,
            /* [in] */ UINT uMsg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam,
            /* [in] */ LRESULT *pret);
        
        HRESULT ( STDMETHODCALLTYPE *QueryActiveShellView )( 
            IShellBrowser * This,
            /* [out] */ IShellView **ppshv);
        
        HRESULT ( STDMETHODCALLTYPE *OnViewWindowActive )( 
            IShellBrowser * This,
            /* [in] */ IShellView *pshv);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SetToolbarItems )( 
            IShellBrowser * This,
            /* [in] */ LPTBBUTTONSB lpButtons,
            /* [in] */ UINT nButtons,
            /* [in] */ UINT uFlags);
        
        END_INTERFACE
    } IShellBrowserVtbl;

    interface IShellBrowser
    {
        CONST_VTBL struct IShellBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellBrowser_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellBrowser_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellBrowser_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellBrowser_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IShellBrowser_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IShellBrowser_InsertMenusSB(This,hmenuShared,lpMenuWidths)	\
    ( (This)->lpVtbl -> InsertMenusSB(This,hmenuShared,lpMenuWidths) ) 

#define IShellBrowser_SetMenuSB(This,hmenuShared,holemenuRes,hwndActiveObject)	\
    ( (This)->lpVtbl -> SetMenuSB(This,hmenuShared,holemenuRes,hwndActiveObject) ) 

#define IShellBrowser_RemoveMenusSB(This,hmenuShared)	\
    ( (This)->lpVtbl -> RemoveMenusSB(This,hmenuShared) ) 

#define IShellBrowser_SetStatusTextSB(This,pszStatusText)	\
    ( (This)->lpVtbl -> SetStatusTextSB(This,pszStatusText) ) 

#define IShellBrowser_EnableModelessSB(This,fEnable)	\
    ( (This)->lpVtbl -> EnableModelessSB(This,fEnable) ) 

#define IShellBrowser_TranslateAcceleratorSB(This,pmsg,wID)	\
    ( (This)->lpVtbl -> TranslateAcceleratorSB(This,pmsg,wID) ) 

#define IShellBrowser_BrowseObject(This,pidl,wFlags)	\
    ( (This)->lpVtbl -> BrowseObject(This,pidl,wFlags) ) 

#define IShellBrowser_GetViewStateStream(This,grfMode,ppStrm)	\
    ( (This)->lpVtbl -> GetViewStateStream(This,grfMode,ppStrm) ) 

#define IShellBrowser_GetControlWindow(This,id,phwnd)	\
    ( (This)->lpVtbl -> GetControlWindow(This,id,phwnd) ) 

#define IShellBrowser_SendControlMsg(This,id,uMsg,wParam,lParam,pret)	\
    ( (This)->lpVtbl -> SendControlMsg(This,id,uMsg,wParam,lParam,pret) ) 

#define IShellBrowser_QueryActiveShellView(This,ppshv)	\
    ( (This)->lpVtbl -> QueryActiveShellView(This,ppshv) ) 

#define IShellBrowser_OnViewWindowActive(This,pshv)	\
    ( (This)->lpVtbl -> OnViewWindowActive(This,pshv) ) 

#define IShellBrowser_SetToolbarItems(This,lpButtons,nButtons,uFlags)	\
    ( (This)->lpVtbl -> SetToolbarItems(This,lpButtons,nButtons,uFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellBrowser_InsertMenusSB_Proxy( 
    IShellBrowser * This,
    /* [in] */ HMENU hmenuShared,
    /* [out][in] */ LPOLEMENUGROUPWIDTHS lpMenuWidths);


void __RPC_STUB IShellBrowser_InsertMenusSB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_SetMenuSB_Proxy( 
    IShellBrowser * This,
    /* [in] */ HMENU hmenuShared,
    /* [in] */ HOLEMENU holemenuRes,
    /* [in] */ HWND hwndActiveObject);


void __RPC_STUB IShellBrowser_SetMenuSB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_RemoveMenusSB_Proxy( 
    IShellBrowser * This,
    /* [in] */ HMENU hmenuShared);


void __RPC_STUB IShellBrowser_RemoveMenusSB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_SetStatusTextSB_Proxy( 
    IShellBrowser * This,
    /* [unique][in] */ LPCOLESTR pszStatusText);


void __RPC_STUB IShellBrowser_SetStatusTextSB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_EnableModelessSB_Proxy( 
    IShellBrowser * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IShellBrowser_EnableModelessSB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_TranslateAcceleratorSB_Proxy( 
    IShellBrowser * This,
    /* [in] */ MSG *pmsg,
    /* [in] */ WORD wID);


void __RPC_STUB IShellBrowser_TranslateAcceleratorSB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_BrowseObject_Proxy( 
    IShellBrowser * This,
    /* [in] */ PCUIDLIST_RELATIVE pidl,
    /* [in] */ UINT wFlags);


void __RPC_STUB IShellBrowser_BrowseObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_GetViewStateStream_Proxy( 
    IShellBrowser * This,
    /* [in] */ DWORD grfMode,
    /* [out] */ IStream **ppStrm);


void __RPC_STUB IShellBrowser_GetViewStateStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_GetControlWindow_Proxy( 
    IShellBrowser * This,
    /* [in] */ UINT id,
    /* [out] */ HWND *phwnd);


void __RPC_STUB IShellBrowser_GetControlWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IShellBrowser_SendControlMsg_Proxy( 
    IShellBrowser * This,
    /* [in] */ UINT id,
    /* [in] */ UINT uMsg,
    /* [in] */ WPARAM wParam,
    /* [in] */ LPARAM lParam,
    /* [in] */ LRESULT *pret);


void __RPC_STUB IShellBrowser_SendControlMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_QueryActiveShellView_Proxy( 
    IShellBrowser * This,
    /* [out] */ IShellView **ppshv);


void __RPC_STUB IShellBrowser_QueryActiveShellView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellBrowser_OnViewWindowActive_Proxy( 
    IShellBrowser * This,
    /* [in] */ IShellView *pshv);


void __RPC_STUB IShellBrowser_OnViewWindowActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IShellBrowser_SetToolbarItems_Proxy( 
    IShellBrowser * This,
    /* [in] */ LPTBBUTTONSB lpButtons,
    /* [in] */ UINT nButtons,
    /* [in] */ UINT uFlags);


void __RPC_STUB IShellBrowser_SetToolbarItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellBrowser_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0226 */
/* [local] */ 

typedef IShellBrowser *LPSHELLBROWSER;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0226_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0226_v0_0_s_ifspec;

#ifndef __IProfferService_INTERFACE_DEFINED__
#define __IProfferService_INTERFACE_DEFINED__

/* interface IProfferService */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IProfferService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("cb728b20-f786-11ce-92ad-00aa00a74cd0")
    IProfferService : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ProfferService( 
            /* [in] */ REFGUID rguidService,
            /* [in] */ IServiceProvider *psp,
            /* [out] */ DWORD *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RevokeService( 
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProfferServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProfferService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProfferService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProfferService * This);
        
        HRESULT ( STDMETHODCALLTYPE *ProfferService )( 
            IProfferService * This,
            /* [in] */ REFGUID rguidService,
            /* [in] */ IServiceProvider *psp,
            /* [out] */ DWORD *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *RevokeService )( 
            IProfferService * This,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IProfferServiceVtbl;

    interface IProfferService
    {
        CONST_VTBL struct IProfferServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProfferService_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProfferService_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProfferService_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProfferService_ProfferService(This,rguidService,psp,pdwCookie)	\
    ( (This)->lpVtbl -> ProfferService(This,rguidService,psp,pdwCookie) ) 

#define IProfferService_RevokeService(This,dwCookie)	\
    ( (This)->lpVtbl -> RevokeService(This,dwCookie) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IProfferService_ProfferService_Proxy( 
    IProfferService * This,
    /* [in] */ REFGUID rguidService,
    /* [in] */ IServiceProvider *psp,
    /* [out] */ DWORD *pdwCookie);


void __RPC_STUB IProfferService_ProfferService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IProfferService_RevokeService_Proxy( 
    IProfferService * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IProfferService_RevokeService_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProfferService_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0227 */
/* [local] */ 

#define SID_SProfferService IID_IProfferService    // nearest service that you can proffer to
#define STR_DONT_RESOLVE_LINK      L"Don't Resolve Link"
#define STR_PLAYLIST_EDITOR_UI  L"Static List In Dialog"


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0227_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0227_v0_0_s_ifspec;

#ifndef __IShellItem_INTERFACE_DEFINED__
#define __IShellItem_INTERFACE_DEFINED__

/* interface IShellItem */
/* [unique][object][uuid][helpstring] */ 

typedef /* [v1_enum] */ 
enum tagSIGDN
    {	SIGDN_NORMALDISPLAY	= 0,
	SIGDN_PARENTRELATIVEPARSING	= 0x80018001,
	SIGDN_DESKTOPABSOLUTEPARSING	= 0x80028000,
	SIGDN_PARENTRELATIVEEDITING	= 0x80031001,
	SIGDN_DESKTOPABSOLUTEEDITING	= 0x8004c000,
	SIGDN_FILESYSPATH	= 0x80058000,
	SIGDN_URL	= 0x80068000,
	SIGDN_PARENTRELATIVEFORADDRESSBAR	= 0x8007c001,
	SIGDN_PARENTRELATIVE	= 0x80080001
    } 	SIGDN;

/* [v1_enum] */ 
enum tagSHELLITEMCOMPAREHINTF
    {	SICHINT_DISPLAY	= 0,
	SICHINT_ALLFIELDS	= 0x80000000,
	SICHINT_CANONICAL	= 0x10000000
    } ;
typedef DWORD SICHINTF;


EXTERN_C const IID IID_IShellItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43826d1e-e718-42ee-bc55-a1e261c37bfe")
    IShellItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BindToHandler( 
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID rbhid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParent( 
            /* [out] */ IShellItem **ppsi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [in] */ SIGDN sigdnName,
            /* [string][out] */ LPOLESTR *ppszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAttributes( 
            /* [in] */ SFGAOF sfgaoMask,
            /* [out] */ SFGAOF *psfgaoAttribs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compare( 
            /* [in] */ IShellItem *psi,
            /* [in] */ SICHINTF hint,
            /* [out] */ int *piOrder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *BindToHandler )( 
            IShellItem * This,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID rbhid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IShellItem * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayName )( 
            IShellItem * This,
            /* [in] */ SIGDN sigdnName,
            /* [string][out] */ LPOLESTR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAttributes )( 
            IShellItem * This,
            /* [in] */ SFGAOF sfgaoMask,
            /* [out] */ SFGAOF *psfgaoAttribs);
        
        HRESULT ( STDMETHODCALLTYPE *Compare )( 
            IShellItem * This,
            /* [in] */ IShellItem *psi,
            /* [in] */ SICHINTF hint,
            /* [out] */ int *piOrder);
        
        END_INTERFACE
    } IShellItemVtbl;

    interface IShellItem
    {
        CONST_VTBL struct IShellItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellItem_BindToHandler(This,pbc,rbhid,riid,ppvOut)	\
    ( (This)->lpVtbl -> BindToHandler(This,pbc,rbhid,riid,ppvOut) ) 

#define IShellItem_GetParent(This,ppsi)	\
    ( (This)->lpVtbl -> GetParent(This,ppsi) ) 

#define IShellItem_GetDisplayName(This,sigdnName,ppszName)	\
    ( (This)->lpVtbl -> GetDisplayName(This,sigdnName,ppszName) ) 

#define IShellItem_GetAttributes(This,sfgaoMask,psfgaoAttribs)	\
    ( (This)->lpVtbl -> GetAttributes(This,sfgaoMask,psfgaoAttribs) ) 

#define IShellItem_Compare(This,psi,hint,piOrder)	\
    ( (This)->lpVtbl -> Compare(This,psi,hint,piOrder) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellItem_BindToHandler_Proxy( 
    IShellItem * This,
    /* [in] */ IBindCtx *pbc,
    /* [in] */ REFGUID rbhid,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppvOut);


void __RPC_STUB IShellItem_BindToHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItem_GetParent_Proxy( 
    IShellItem * This,
    /* [out] */ IShellItem **ppsi);


void __RPC_STUB IShellItem_GetParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItem_GetDisplayName_Proxy( 
    IShellItem * This,
    /* [in] */ SIGDN sigdnName,
    /* [string][out] */ LPOLESTR *ppszName);


void __RPC_STUB IShellItem_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItem_GetAttributes_Proxy( 
    IShellItem * This,
    /* [in] */ SFGAOF sfgaoMask,
    /* [out] */ SFGAOF *psfgaoAttribs);


void __RPC_STUB IShellItem_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItem_Compare_Proxy( 
    IShellItem * This,
    /* [in] */ IShellItem *psi,
    /* [in] */ SICHINTF hint,
    /* [out] */ int *piOrder);


void __RPC_STUB IShellItem_Compare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellItem_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0228 */
/* [local] */ 

SHSTDAPI SHCreateItemFromFolderID(int csidl, HANDLE hToken, REFIID riid, void **ppv);
SHSTDAPI SHCreateItemFromIDList(PCIDLIST_ABSOLUTE pidl, REFIID riid, void **ppv);
SHSTDAPI SHCreateItemFromParsingName(PCWSTR pszPath, IBindCtx *pbc, REFIID riid, void **ppv);
SHSTDAPI SHCreateItemWithParent(PCIDLIST_ABSOLUTE pidlParent, IShellFolder *psfParent, PCUITEMID_CHILD pidl, REFIID riid, void **ppvItem);
SHSTDAPI SHCreateItemFromRelativeName(IShellItem *psiParent, PCWSTR pszName, IBindCtx* pbc, REFIID riid, void **ppv);
/* [v1_enum] */ 
enum tagGETPROPERTYSTOREFLAGS
    {	GPS_DEFAULT	= 0,
	GPS_READWRITE	= 0x1,
	GPS_INMEMORY	= ( GPS_READWRITE | 0x2 ) ,
	GPS_NOINCLUDEALLDETAILS	= 0x4,
	GPS_NONTFSPROPSTORE	= 0x8,
	GPS_CACHEDREADONLY	= 0x10,
	GPS_INCLUDEOFFLINEDETAILS	= 0x20,
	GPS_DELAYCREATION	= 0x40
    } ;
typedef DWORD GETPROPERTYSTOREFLAGS;

#define GPS_TEMPORARY GPS_INMEMORY


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0228_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0228_v0_0_s_ifspec;

#ifndef __IShellItem2_INTERFACE_DEFINED__
#define __IShellItem2_INTERFACE_DEFINED__

/* interface IShellItem2 */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IShellItem2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("58bbfe39-c0ad-4f95-9e55-e4c2a1ba1cf8")
    IShellItem2 : public IShellItem
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPropertyStore( 
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropertyDescriptionList( 
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellItem2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellItem2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellItem2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellItem2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *BindToHandler )( 
            IShellItem2 * This,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID rbhid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetParent )( 
            IShellItem2 * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayName )( 
            IShellItem2 * This,
            /* [in] */ SIGDN sigdnName,
            /* [string][out] */ LPOLESTR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetAttributes )( 
            IShellItem2 * This,
            /* [in] */ SFGAOF sfgaoMask,
            /* [out] */ SFGAOF *psfgaoAttribs);
        
        HRESULT ( STDMETHODCALLTYPE *Compare )( 
            IShellItem2 * This,
            /* [in] */ IShellItem *psi,
            /* [in] */ SICHINTF hint,
            /* [out] */ int *piOrder);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyStore )( 
            IShellItem2 * This,
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyDescriptionList )( 
            IShellItem2 * This,
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IShellItem2Vtbl;

    interface IShellItem2
    {
        CONST_VTBL struct IShellItem2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellItem2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellItem2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellItem2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellItem2_BindToHandler(This,pbc,rbhid,riid,ppvOut)	\
    ( (This)->lpVtbl -> BindToHandler(This,pbc,rbhid,riid,ppvOut) ) 

#define IShellItem2_GetParent(This,ppsi)	\
    ( (This)->lpVtbl -> GetParent(This,ppsi) ) 

#define IShellItem2_GetDisplayName(This,sigdnName,ppszName)	\
    ( (This)->lpVtbl -> GetDisplayName(This,sigdnName,ppszName) ) 

#define IShellItem2_GetAttributes(This,sfgaoMask,psfgaoAttribs)	\
    ( (This)->lpVtbl -> GetAttributes(This,sfgaoMask,psfgaoAttribs) ) 

#define IShellItem2_Compare(This,psi,hint,piOrder)	\
    ( (This)->lpVtbl -> Compare(This,psi,hint,piOrder) ) 


#define IShellItem2_GetPropertyStore(This,flags,riid,ppv)	\
    ( (This)->lpVtbl -> GetPropertyStore(This,flags,riid,ppv) ) 

#define IShellItem2_GetPropertyDescriptionList(This,keyType,riid,ppv)	\
    ( (This)->lpVtbl -> GetPropertyDescriptionList(This,keyType,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellItem2_GetPropertyStore_Proxy( 
    IShellItem2 * This,
    /* [in] */ GETPROPERTYSTOREFLAGS flags,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellItem2_GetPropertyStore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItem2_GetPropertyDescriptionList_Proxy( 
    IShellItem2 * This,
    /* [in] */ REFPROPERTYKEY keyType,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellItem2_GetPropertyDescriptionList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellItem2_INTERFACE_DEFINED__ */


#ifndef __IEnumShellItems_INTERFACE_DEFINED__
#define __IEnumShellItems_INTERFACE_DEFINED__

/* interface IEnumShellItems */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IEnumShellItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70629033-e363-4a28-a567-0db78006e6d7")
    IEnumShellItems : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IShellItem **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumShellItems **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumShellItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumShellItems * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumShellItems * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumShellItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumShellItems * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IShellItem **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumShellItems * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumShellItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumShellItems * This,
            /* [out] */ IEnumShellItems **ppenum);
        
        END_INTERFACE
    } IEnumShellItemsVtbl;

    interface IEnumShellItems
    {
        CONST_VTBL struct IEnumShellItemsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumShellItems_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumShellItems_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumShellItems_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumShellItems_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumShellItems_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumShellItems_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumShellItems_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumShellItems_Next_Proxy( 
    IEnumShellItems * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IShellItem **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumShellItems_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumShellItems_Skip_Proxy( 
    IEnumShellItems * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumShellItems_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumShellItems_Reset_Proxy( 
    IEnumShellItems * This);


void __RPC_STUB IEnumShellItems_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumShellItems_Clone_Proxy( 
    IEnumShellItems * This,
    /* [out] */ IEnumShellItems **ppenum);


void __RPC_STUB IEnumShellItems_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumShellItems_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0230 */
/* [local] */ 

#define STRESPONSE_CONTINUE               S_OK
#define STRESPONSE_RENAME                 MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 20)
#define STRESPONSE_SKIP                   MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 21)
#define STRESPONSE_CANCEL                 MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 22)
#define STRESPONSE_RETRY                  __HRESULT_FROM_WIN32(ERROR_RETRY)
typedef GUID STGTRANSCONFIRMATION;

typedef GUID *LPSTGTRANSCONFIRMATION;

typedef /* [v1_enum] */ 
enum tagSTGOP
    {	STGOP_MOVE	= 1,
	STGOP_COPY	= 2,
	STGOP_SYNC	= 3,
	STGOP_DIFF	= 4,
	STGOP_REMOVE	= 5,
	STGOP_RENAME	= 6,
	STGOP_STATS	= 7,
	STGOP_APPLYPROPERTIES	= 8,
	STGOP_LINK	= 9
    } 	STGOP;

typedef /* [v1_enum] */ enum tagSTGOP *LPSTGOP;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0230_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0230_v0_0_s_ifspec;

#ifndef __IQueryContinue_INTERFACE_DEFINED__
#define __IQueryContinue_INTERFACE_DEFINED__

/* interface IQueryContinue */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IQueryContinue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7307055c-b24a-486b-9f25-163e597a28a9")
    IQueryContinue : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryContinue( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQueryContinueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQueryContinue * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQueryContinue * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQueryContinue * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryContinue )( 
            IQueryContinue * This);
        
        END_INTERFACE
    } IQueryContinueVtbl;

    interface IQueryContinue
    {
        CONST_VTBL struct IQueryContinueVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQueryContinue_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQueryContinue_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQueryContinue_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQueryContinue_QueryContinue(This)	\
    ( (This)->lpVtbl -> QueryContinue(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IQueryContinue_QueryContinue_Proxy( 
    IQueryContinue * This);


void __RPC_STUB IQueryContinue_QueryContinue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQueryContinue_INTERFACE_DEFINED__ */


#ifndef __ITransferAdviseSink_INTERFACE_DEFINED__
#define __ITransferAdviseSink_INTERFACE_DEFINED__

/* interface ITransferAdviseSink */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_ITransferAdviseSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9e53e36c-b6b6-4a9b-a6a2-1666e42587bc")
    ITransferAdviseSink : public IQueryContinue
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PreOperation( 
            /* [in] */ const STGOP op,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConfirmOperation( 
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest,
            /* [in] */ STGTRANSCONFIRMATION stc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OperationProgress( 
            /* [in] */ const STGOP op,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest,
            /* [in] */ ULONGLONG ulTotal,
            /* [in] */ ULONGLONG ulComplete) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostOperation( 
            /* [in] */ const STGOP op,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest,
            /* [in] */ HRESULT hrResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransferAdviseSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITransferAdviseSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITransferAdviseSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITransferAdviseSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryContinue )( 
            ITransferAdviseSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *PreOperation )( 
            ITransferAdviseSink * This,
            /* [in] */ const STGOP op,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest);
        
        HRESULT ( STDMETHODCALLTYPE *ConfirmOperation )( 
            ITransferAdviseSink * This,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest,
            /* [in] */ STGTRANSCONFIRMATION stc);
        
        HRESULT ( STDMETHODCALLTYPE *OperationProgress )( 
            ITransferAdviseSink * This,
            /* [in] */ const STGOP op,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest,
            /* [in] */ ULONGLONG ulTotal,
            /* [in] */ ULONGLONG ulComplete);
        
        HRESULT ( STDMETHODCALLTYPE *PostOperation )( 
            ITransferAdviseSink * This,
            /* [in] */ const STGOP op,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDest,
            /* [in] */ HRESULT hrResult);
        
        END_INTERFACE
    } ITransferAdviseSinkVtbl;

    interface ITransferAdviseSink
    {
        CONST_VTBL struct ITransferAdviseSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransferAdviseSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITransferAdviseSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITransferAdviseSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITransferAdviseSink_QueryContinue(This)	\
    ( (This)->lpVtbl -> QueryContinue(This) ) 


#define ITransferAdviseSink_PreOperation(This,op,psiItem,psiDest)	\
    ( (This)->lpVtbl -> PreOperation(This,op,psiItem,psiDest) ) 

#define ITransferAdviseSink_ConfirmOperation(This,psiItem,psiDest,stc)	\
    ( (This)->lpVtbl -> ConfirmOperation(This,psiItem,psiDest,stc) ) 

#define ITransferAdviseSink_OperationProgress(This,op,psiItem,psiDest,ulTotal,ulComplete)	\
    ( (This)->lpVtbl -> OperationProgress(This,op,psiItem,psiDest,ulTotal,ulComplete) ) 

#define ITransferAdviseSink_PostOperation(This,op,psiItem,psiDest,hrResult)	\
    ( (This)->lpVtbl -> PostOperation(This,op,psiItem,psiDest,hrResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransferAdviseSink_PreOperation_Proxy( 
    ITransferAdviseSink * This,
    /* [in] */ const STGOP op,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDest);


void __RPC_STUB ITransferAdviseSink_PreOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransferAdviseSink_ConfirmOperation_Proxy( 
    ITransferAdviseSink * This,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDest,
    /* [in] */ STGTRANSCONFIRMATION stc);


void __RPC_STUB ITransferAdviseSink_ConfirmOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransferAdviseSink_OperationProgress_Proxy( 
    ITransferAdviseSink * This,
    /* [in] */ const STGOP op,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDest,
    /* [in] */ ULONGLONG ulTotal,
    /* [in] */ ULONGLONG ulComplete);


void __RPC_STUB ITransferAdviseSink_OperationProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransferAdviseSink_PostOperation_Proxy( 
    ITransferAdviseSink * This,
    /* [in] */ const STGOP op,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDest,
    /* [in] */ HRESULT hrResult);


void __RPC_STUB ITransferAdviseSink_PostOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransferAdviseSink_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0231 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagPKA_FLAGS
    {	PKA_SET	= 0,
	PKA_APPEND	= 0x1,
	PKA_DELETE	= 0x2
    } 	PKA_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0231_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0231_v0_0_s_ifspec;

#ifndef __IPropertyArray_INTERFACE_DEFINED__
#define __IPropertyArray_INTERFACE_DEFINED__

/* interface IPropertyArray */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IPropertyArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("800c31bd-c671-4604-9eb9-e44245ced2b9")
    IPropertyArray : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ int *pcItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ int iIndex,
            /* [out] */ PROPERTYKEY *pkey,
            /* [out] */ PKA_FLAGS *pflags,
            /* [out] */ PROPVARIANT *ppropvar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsKeyInArray( 
            /* [in] */ REFPROPERTYKEY key) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValues( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ UINT *pcValues,
            /* [size_is][size_is][out] */ PROPVARIANT **prgpropvar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertAt( 
            /* [in] */ int iIndex,
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ PKA_FLAGS flags,
            /* [in] */ const PROPVARIANT *ppropvar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetArrays( 
            /* [out] */ UINT *pcItems,
            /* [size_is][size_is][out] */ PROPVARIANT **prgpropvar,
            /* [size_is][size_is][out] */ PROPERTYKEY **prgkeys,
            /* [size_is][size_is][out] */ PKA_FLAGS **prgFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropertyArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropertyArray * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropertyArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropertyArray * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IPropertyArray * This,
            /* [out] */ int *pcItems);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            IPropertyArray * This,
            /* [in] */ int iIndex,
            /* [out] */ PROPERTYKEY *pkey,
            /* [out] */ PKA_FLAGS *pflags,
            /* [out] */ PROPVARIANT *ppropvar);
        
        HRESULT ( STDMETHODCALLTYPE *IsKeyInArray )( 
            IPropertyArray * This,
            /* [in] */ REFPROPERTYKEY key);
        
        HRESULT ( STDMETHODCALLTYPE *GetValues )( 
            IPropertyArray * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ UINT *pcValues,
            /* [size_is][size_is][out] */ PROPVARIANT **prgpropvar);
        
        HRESULT ( STDMETHODCALLTYPE *InsertAt )( 
            IPropertyArray * This,
            /* [in] */ int iIndex,
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ PKA_FLAGS flags,
            /* [in] */ const PROPVARIANT *ppropvar);
        
        HRESULT ( STDMETHODCALLTYPE *GetArrays )( 
            IPropertyArray * This,
            /* [out] */ UINT *pcItems,
            /* [size_is][size_is][out] */ PROPVARIANT **prgpropvar,
            /* [size_is][size_is][out] */ PROPERTYKEY **prgkeys,
            /* [size_is][size_is][out] */ PKA_FLAGS **prgFlags);
        
        END_INTERFACE
    } IPropertyArrayVtbl;

    interface IPropertyArray
    {
        CONST_VTBL struct IPropertyArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropertyArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPropertyArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPropertyArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPropertyArray_GetCount(This,pcItems)	\
    ( (This)->lpVtbl -> GetCount(This,pcItems) ) 

#define IPropertyArray_GetAt(This,iIndex,pkey,pflags,ppropvar)	\
    ( (This)->lpVtbl -> GetAt(This,iIndex,pkey,pflags,ppropvar) ) 

#define IPropertyArray_IsKeyInArray(This,key)	\
    ( (This)->lpVtbl -> IsKeyInArray(This,key) ) 

#define IPropertyArray_GetValues(This,key,pcValues,prgpropvar)	\
    ( (This)->lpVtbl -> GetValues(This,key,pcValues,prgpropvar) ) 

#define IPropertyArray_InsertAt(This,iIndex,key,flags,ppropvar)	\
    ( (This)->lpVtbl -> InsertAt(This,iIndex,key,flags,ppropvar) ) 

#define IPropertyArray_GetArrays(This,pcItems,prgpropvar,prgkeys,prgFlags)	\
    ( (This)->lpVtbl -> GetArrays(This,pcItems,prgpropvar,prgkeys,prgFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPropertyArray_GetCount_Proxy( 
    IPropertyArray * This,
    /* [out] */ int *pcItems);


void __RPC_STUB IPropertyArray_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyArray_GetAt_Proxy( 
    IPropertyArray * This,
    /* [in] */ int iIndex,
    /* [out] */ PROPERTYKEY *pkey,
    /* [out] */ PKA_FLAGS *pflags,
    /* [out] */ PROPVARIANT *ppropvar);


void __RPC_STUB IPropertyArray_GetAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyArray_IsKeyInArray_Proxy( 
    IPropertyArray * This,
    /* [in] */ REFPROPERTYKEY key);


void __RPC_STUB IPropertyArray_IsKeyInArray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyArray_GetValues_Proxy( 
    IPropertyArray * This,
    /* [in] */ REFPROPERTYKEY key,
    /* [out] */ UINT *pcValues,
    /* [size_is][size_is][out] */ PROPVARIANT **prgpropvar);


void __RPC_STUB IPropertyArray_GetValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyArray_InsertAt_Proxy( 
    IPropertyArray * This,
    /* [in] */ int iIndex,
    /* [in] */ REFPROPERTYKEY key,
    /* [in] */ PKA_FLAGS flags,
    /* [in] */ const PROPVARIANT *ppropvar);


void __RPC_STUB IPropertyArray_InsertAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyArray_GetArrays_Proxy( 
    IPropertyArray * This,
    /* [out] */ UINT *pcItems,
    /* [size_is][size_is][out] */ PROPVARIANT **prgpropvar,
    /* [size_is][size_is][out] */ PROPERTYKEY **prgkeys,
    /* [size_is][size_is][out] */ PKA_FLAGS **prgFlags);


void __RPC_STUB IPropertyArray_GetArrays_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropertyArray_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0232 */
/* [local] */ 

#define FOFX_NOSKIPJUNCTIONS         0x00010000  // Don't avoid binding to junctions (like Task folder, Recycle-Bin)
#define FOFX_PREFERHARDLINK          0x00020000  // Create hard link if possible
#define FOFX_COLLECTION              0x00040000  // Operate on items inside collections (playlists)
#define FOFX_MODALPROGRESSUI         0x00100000  // Display modal (rather than modeless) progress UI
#define FOFX_PRESERVEFILEEXTENSIONS  0x00200000  // Rename collisions preserve file extns (use with FOF_RENAMEONCOLLISION)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0232_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0232_v0_0_s_ifspec;

#ifndef __IFileOperationProgressSink_INTERFACE_DEFINED__
#define __IFileOperationProgressSink_INTERFACE_DEFINED__

/* interface IFileOperationProgressSink */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IFileOperationProgressSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5e09c7bf-4498-43c2-babc-f2f448264c1e")
    IFileOperationProgressSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartOperations( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FinishOperations( 
            /* [in] */ HRESULT hrResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreRenameItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostRenameItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrRename,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreMoveItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostMoveItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrMove,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreCopyItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostCopyItem( 
            DWORD dwFlags,
            IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrCopy,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreLinkItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostLinkItem( 
            DWORD dwFlags,
            IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrLink,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreDeleteItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostDeleteItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ HRESULT hrDelete,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateProgress( 
            /* [in] */ UINT iWorkTotal,
            /* [in] */ UINT iWorkSoFar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetTimer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PauseTimer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResumeTimer( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileOperationProgressSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileOperationProgressSink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileOperationProgressSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileOperationProgressSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartOperations )( 
            IFileOperationProgressSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *FinishOperations )( 
            IFileOperationProgressSink * This,
            /* [in] */ HRESULT hrResult);
        
        HRESULT ( STDMETHODCALLTYPE *PreRenameItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostRenameItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrRename,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreMoveItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostMoveItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrMove,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreCopyItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostCopyItem )( 
            IFileOperationProgressSink * This,
            DWORD dwFlags,
            IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrCopy,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreLinkItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostLinkItem )( 
            IFileOperationProgressSink * This,
            DWORD dwFlags,
            IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrLink,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreDeleteItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem);
        
        HRESULT ( STDMETHODCALLTYPE *PostDeleteItem )( 
            IFileOperationProgressSink * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ HRESULT hrDelete,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateProgress )( 
            IFileOperationProgressSink * This,
            /* [in] */ UINT iWorkTotal,
            /* [in] */ UINT iWorkSoFar);
        
        HRESULT ( STDMETHODCALLTYPE *ResetTimer )( 
            IFileOperationProgressSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *PauseTimer )( 
            IFileOperationProgressSink * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResumeTimer )( 
            IFileOperationProgressSink * This);
        
        END_INTERFACE
    } IFileOperationProgressSinkVtbl;

    interface IFileOperationProgressSink
    {
        CONST_VTBL struct IFileOperationProgressSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileOperationProgressSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileOperationProgressSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileOperationProgressSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileOperationProgressSink_StartOperations(This)	\
    ( (This)->lpVtbl -> StartOperations(This) ) 

#define IFileOperationProgressSink_FinishOperations(This,hrResult)	\
    ( (This)->lpVtbl -> FinishOperations(This,hrResult) ) 

#define IFileOperationProgressSink_PreRenameItem(This,dwFlags,psiItem,pszNewName)	\
    ( (This)->lpVtbl -> PreRenameItem(This,dwFlags,psiItem,pszNewName) ) 

#define IFileOperationProgressSink_PostRenameItem(This,dwFlags,psiItem,pszNewName,hrRename,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostRenameItem(This,dwFlags,psiItem,pszNewName,hrRename,psiNewlyCreated) ) 

#define IFileOperationProgressSink_PreMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IFileOperationProgressSink_PostMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrMove,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrMove,psiNewlyCreated) ) 

#define IFileOperationProgressSink_PreCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IFileOperationProgressSink_PostCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrCopy,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrCopy,psiNewlyCreated) ) 

#define IFileOperationProgressSink_PreLinkItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreLinkItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IFileOperationProgressSink_PostLinkItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrLink,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostLinkItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrLink,psiNewlyCreated) ) 

#define IFileOperationProgressSink_PreDeleteItem(This,dwFlags,psiItem)	\
    ( (This)->lpVtbl -> PreDeleteItem(This,dwFlags,psiItem) ) 

#define IFileOperationProgressSink_PostDeleteItem(This,dwFlags,psiItem,hrDelete,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostDeleteItem(This,dwFlags,psiItem,hrDelete,psiNewlyCreated) ) 

#define IFileOperationProgressSink_UpdateProgress(This,iWorkTotal,iWorkSoFar)	\
    ( (This)->lpVtbl -> UpdateProgress(This,iWorkTotal,iWorkSoFar) ) 

#define IFileOperationProgressSink_ResetTimer(This)	\
    ( (This)->lpVtbl -> ResetTimer(This) ) 

#define IFileOperationProgressSink_PauseTimer(This)	\
    ( (This)->lpVtbl -> PauseTimer(This) ) 

#define IFileOperationProgressSink_ResumeTimer(This)	\
    ( (This)->lpVtbl -> ResumeTimer(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_StartOperations_Proxy( 
    IFileOperationProgressSink * This);


void __RPC_STUB IFileOperationProgressSink_StartOperations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_FinishOperations_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ HRESULT hrResult);


void __RPC_STUB IFileOperationProgressSink_FinishOperations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PreRenameItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ LPCWSTR pszNewName);


void __RPC_STUB IFileOperationProgressSink_PreRenameItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PostRenameItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ HRESULT hrRename,
    /* [in] */ IShellItem *psiNewlyCreated);


void __RPC_STUB IFileOperationProgressSink_PostRenameItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PreMoveItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName);


void __RPC_STUB IFileOperationProgressSink_PreMoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PostMoveItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ HRESULT hrMove,
    /* [in] */ IShellItem *psiNewlyCreated);


void __RPC_STUB IFileOperationProgressSink_PostMoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PreCopyItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName);


void __RPC_STUB IFileOperationProgressSink_PreCopyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PostCopyItem_Proxy( 
    IFileOperationProgressSink * This,
    DWORD dwFlags,
    IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ HRESULT hrCopy,
    /* [in] */ IShellItem *psiNewlyCreated);


void __RPC_STUB IFileOperationProgressSink_PostCopyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PreLinkItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName);


void __RPC_STUB IFileOperationProgressSink_PreLinkItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PostLinkItem_Proxy( 
    IFileOperationProgressSink * This,
    DWORD dwFlags,
    IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ HRESULT hrLink,
    /* [in] */ IShellItem *psiNewlyCreated);


void __RPC_STUB IFileOperationProgressSink_PostLinkItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PreDeleteItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem);


void __RPC_STUB IFileOperationProgressSink_PreDeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PostDeleteItem_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ HRESULT hrDelete,
    /* [in] */ IShellItem *psiNewlyCreated);


void __RPC_STUB IFileOperationProgressSink_PostDeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_UpdateProgress_Proxy( 
    IFileOperationProgressSink * This,
    /* [in] */ UINT iWorkTotal,
    /* [in] */ UINT iWorkSoFar);


void __RPC_STUB IFileOperationProgressSink_UpdateProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_ResetTimer_Proxy( 
    IFileOperationProgressSink * This);


void __RPC_STUB IFileOperationProgressSink_ResetTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_PauseTimer_Proxy( 
    IFileOperationProgressSink * This);


void __RPC_STUB IFileOperationProgressSink_PauseTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperationProgressSink_ResumeTimer_Proxy( 
    IFileOperationProgressSink * This);


void __RPC_STUB IFileOperationProgressSink_ResumeTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileOperationProgressSink_INTERFACE_DEFINED__ */


#ifndef __IFileOperation_INTERFACE_DEFINED__
#define __IFileOperation_INTERFACE_DEFINED__

/* interface IFileOperation */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IFileOperation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b94ed75e-7628-403f-acdb-0d1ae521b1c7")
    IFileOperation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IFileOperationProgressSink *pfops,
            /* [out] */ DWORD *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( 
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOperationFlags( 
            /* [in] */ DWORD dwOperationFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProgressMessage( 
            /* [in] */ LPCWSTR pszMessage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ IPropertyArray *pproparray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParentWindow( 
            /* [in] */ HWND hwndParent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ApplyPropertiesToItem( 
            /* [in] */ IShellItem *psiItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ApplyPropertiesToItems( 
            /* [in] */ IUnknown *punkItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenameItem( 
            /* [in] */ IShellItem *psiItem,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ IFileOperationProgressSink *pfopsItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenameItems( 
            /* [in] */ IUnknown *pUnkItems,
            /* [in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveItem( 
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ IFileOperationProgressSink *pfopsItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveItems( 
            /* [in] */ IUnknown *punkItems,
            /* [in] */ IShellItem *psiDestinationFolder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyItem( 
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszCopyName,
            /* [in] */ IFileOperationProgressSink *pfopsItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyItems( 
            /* [in] */ IUnknown *punkItems,
            /* [in] */ IShellItem *psiDestinationFolder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LinkItem( 
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ IFileOperationProgressSink *pfopsItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LinkItems( 
            /* [in] */ IUnknown *punkItems,
            /* [in] */ IShellItem *psiDestinationFolder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IFileOperationProgressSink *pfopsItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteItems( 
            /* [in] */ IUnknown *punkItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PerformOperations( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileOperationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileOperation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileOperation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileOperation * This);
        
        HRESULT ( STDMETHODCALLTYPE *Advise )( 
            IFileOperation * This,
            /* [in] */ IFileOperationProgressSink *pfops,
            /* [out] */ DWORD *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IFileOperation * This,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *SetOperationFlags )( 
            IFileOperation * This,
            /* [in] */ DWORD dwOperationFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetProgressMessage )( 
            IFileOperation * This,
            /* [in] */ LPCWSTR pszMessage);
        
        HRESULT ( STDMETHODCALLTYPE *SetProperties )( 
            IFileOperation * This,
            /* [in] */ IPropertyArray *pproparray);
        
        HRESULT ( STDMETHODCALLTYPE *SetParentWindow )( 
            IFileOperation * This,
            /* [in] */ HWND hwndParent);
        
        HRESULT ( STDMETHODCALLTYPE *ApplyPropertiesToItem )( 
            IFileOperation * This,
            /* [in] */ IShellItem *psiItem);
        
        HRESULT ( STDMETHODCALLTYPE *ApplyPropertiesToItems )( 
            IFileOperation * This,
            /* [in] */ IUnknown *punkItems);
        
        HRESULT ( STDMETHODCALLTYPE *RenameItem )( 
            IFileOperation * This,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ IFileOperationProgressSink *pfopsItem);
        
        HRESULT ( STDMETHODCALLTYPE *RenameItems )( 
            IFileOperation * This,
            /* [in] */ IUnknown *pUnkItems,
            /* [in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *MoveItem )( 
            IFileOperation * This,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ IFileOperationProgressSink *pfopsItem);
        
        HRESULT ( STDMETHODCALLTYPE *MoveItems )( 
            IFileOperation * This,
            /* [in] */ IUnknown *punkItems,
            /* [in] */ IShellItem *psiDestinationFolder);
        
        HRESULT ( STDMETHODCALLTYPE *CopyItem )( 
            IFileOperation * This,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszCopyName,
            /* [in] */ IFileOperationProgressSink *pfopsItem);
        
        HRESULT ( STDMETHODCALLTYPE *CopyItems )( 
            IFileOperation * This,
            /* [in] */ IUnknown *punkItems,
            /* [in] */ IShellItem *psiDestinationFolder);
        
        HRESULT ( STDMETHODCALLTYPE *LinkItem )( 
            IFileOperation * This,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [in] */ LPCWSTR pszNewName,
            /* [in] */ IFileOperationProgressSink *pfopsItem);
        
        HRESULT ( STDMETHODCALLTYPE *LinkItems )( 
            IFileOperation * This,
            /* [in] */ IUnknown *punkItems,
            /* [in] */ IShellItem *psiDestinationFolder);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteItem )( 
            IFileOperation * This,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IFileOperationProgressSink *pfopsItem);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteItems )( 
            IFileOperation * This,
            /* [in] */ IUnknown *punkItems);
        
        HRESULT ( STDMETHODCALLTYPE *PerformOperations )( 
            IFileOperation * This);
        
        END_INTERFACE
    } IFileOperationVtbl;

    interface IFileOperation
    {
        CONST_VTBL struct IFileOperationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileOperation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileOperation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileOperation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileOperation_Advise(This,pfops,pdwCookie)	\
    ( (This)->lpVtbl -> Advise(This,pfops,pdwCookie) ) 

#define IFileOperation_Unadvise(This,dwCookie)	\
    ( (This)->lpVtbl -> Unadvise(This,dwCookie) ) 

#define IFileOperation_SetOperationFlags(This,dwOperationFlags)	\
    ( (This)->lpVtbl -> SetOperationFlags(This,dwOperationFlags) ) 

#define IFileOperation_SetProgressMessage(This,pszMessage)	\
    ( (This)->lpVtbl -> SetProgressMessage(This,pszMessage) ) 

#define IFileOperation_SetProperties(This,pproparray)	\
    ( (This)->lpVtbl -> SetProperties(This,pproparray) ) 

#define IFileOperation_SetParentWindow(This,hwndParent)	\
    ( (This)->lpVtbl -> SetParentWindow(This,hwndParent) ) 

#define IFileOperation_ApplyPropertiesToItem(This,psiItem)	\
    ( (This)->lpVtbl -> ApplyPropertiesToItem(This,psiItem) ) 

#define IFileOperation_ApplyPropertiesToItems(This,punkItems)	\
    ( (This)->lpVtbl -> ApplyPropertiesToItems(This,punkItems) ) 

#define IFileOperation_RenameItem(This,psiItem,pszNewName,pfopsItem)	\
    ( (This)->lpVtbl -> RenameItem(This,psiItem,pszNewName,pfopsItem) ) 

#define IFileOperation_RenameItems(This,pUnkItems,pszNewName)	\
    ( (This)->lpVtbl -> RenameItems(This,pUnkItems,pszNewName) ) 

#define IFileOperation_MoveItem(This,psiItem,psiDestinationFolder,pszNewName,pfopsItem)	\
    ( (This)->lpVtbl -> MoveItem(This,psiItem,psiDestinationFolder,pszNewName,pfopsItem) ) 

#define IFileOperation_MoveItems(This,punkItems,psiDestinationFolder)	\
    ( (This)->lpVtbl -> MoveItems(This,punkItems,psiDestinationFolder) ) 

#define IFileOperation_CopyItem(This,psiItem,psiDestinationFolder,pszCopyName,pfopsItem)	\
    ( (This)->lpVtbl -> CopyItem(This,psiItem,psiDestinationFolder,pszCopyName,pfopsItem) ) 

#define IFileOperation_CopyItems(This,punkItems,psiDestinationFolder)	\
    ( (This)->lpVtbl -> CopyItems(This,punkItems,psiDestinationFolder) ) 

#define IFileOperation_LinkItem(This,psiItem,psiDestinationFolder,pszNewName,pfopsItem)	\
    ( (This)->lpVtbl -> LinkItem(This,psiItem,psiDestinationFolder,pszNewName,pfopsItem) ) 

#define IFileOperation_LinkItems(This,punkItems,psiDestinationFolder)	\
    ( (This)->lpVtbl -> LinkItems(This,punkItems,psiDestinationFolder) ) 

#define IFileOperation_DeleteItem(This,psiItem,pfopsItem)	\
    ( (This)->lpVtbl -> DeleteItem(This,psiItem,pfopsItem) ) 

#define IFileOperation_DeleteItems(This,punkItems)	\
    ( (This)->lpVtbl -> DeleteItems(This,punkItems) ) 

#define IFileOperation_PerformOperations(This)	\
    ( (This)->lpVtbl -> PerformOperations(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileOperation_Advise_Proxy( 
    IFileOperation * This,
    /* [in] */ IFileOperationProgressSink *pfops,
    /* [out] */ DWORD *pdwCookie);


void __RPC_STUB IFileOperation_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_Unadvise_Proxy( 
    IFileOperation * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IFileOperation_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_SetOperationFlags_Proxy( 
    IFileOperation * This,
    /* [in] */ DWORD dwOperationFlags);


void __RPC_STUB IFileOperation_SetOperationFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_SetProgressMessage_Proxy( 
    IFileOperation * This,
    /* [in] */ LPCWSTR pszMessage);


void __RPC_STUB IFileOperation_SetProgressMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_SetProperties_Proxy( 
    IFileOperation * This,
    /* [in] */ IPropertyArray *pproparray);


void __RPC_STUB IFileOperation_SetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_SetParentWindow_Proxy( 
    IFileOperation * This,
    /* [in] */ HWND hwndParent);


void __RPC_STUB IFileOperation_SetParentWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_ApplyPropertiesToItem_Proxy( 
    IFileOperation * This,
    /* [in] */ IShellItem *psiItem);


void __RPC_STUB IFileOperation_ApplyPropertiesToItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_ApplyPropertiesToItems_Proxy( 
    IFileOperation * This,
    /* [in] */ IUnknown *punkItems);


void __RPC_STUB IFileOperation_ApplyPropertiesToItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_RenameItem_Proxy( 
    IFileOperation * This,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ IFileOperationProgressSink *pfopsItem);


void __RPC_STUB IFileOperation_RenameItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_RenameItems_Proxy( 
    IFileOperation * This,
    /* [in] */ IUnknown *pUnkItems,
    /* [in] */ LPCWSTR pszNewName);


void __RPC_STUB IFileOperation_RenameItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_MoveItem_Proxy( 
    IFileOperation * This,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ IFileOperationProgressSink *pfopsItem);


void __RPC_STUB IFileOperation_MoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_MoveItems_Proxy( 
    IFileOperation * This,
    /* [in] */ IUnknown *punkItems,
    /* [in] */ IShellItem *psiDestinationFolder);


void __RPC_STUB IFileOperation_MoveItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_CopyItem_Proxy( 
    IFileOperation * This,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszCopyName,
    /* [in] */ IFileOperationProgressSink *pfopsItem);


void __RPC_STUB IFileOperation_CopyItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_CopyItems_Proxy( 
    IFileOperation * This,
    /* [in] */ IUnknown *punkItems,
    /* [in] */ IShellItem *psiDestinationFolder);


void __RPC_STUB IFileOperation_CopyItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_LinkItem_Proxy( 
    IFileOperation * This,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IShellItem *psiDestinationFolder,
    /* [in] */ LPCWSTR pszNewName,
    /* [in] */ IFileOperationProgressSink *pfopsItem);


void __RPC_STUB IFileOperation_LinkItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_LinkItems_Proxy( 
    IFileOperation * This,
    /* [in] */ IUnknown *punkItems,
    /* [in] */ IShellItem *psiDestinationFolder);


void __RPC_STUB IFileOperation_LinkItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_DeleteItem_Proxy( 
    IFileOperation * This,
    /* [in] */ IShellItem *psiItem,
    /* [in] */ IFileOperationProgressSink *pfopsItem);


void __RPC_STUB IFileOperation_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_DeleteItems_Proxy( 
    IFileOperation * This,
    /* [in] */ IUnknown *punkItems);


void __RPC_STUB IFileOperation_DeleteItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOperation_PerformOperations_Proxy( 
    IFileOperation * This);


void __RPC_STUB IFileOperation_PerformOperations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileOperation_INTERFACE_DEFINED__ */


#ifndef __IShellItemArray_INTERFACE_DEFINED__
#define __IShellItemArray_INTERFACE_DEFINED__

/* interface IShellItemArray */
/* [unique][object][uuid][helpstring] */ 

typedef /* [v1_enum] */ 
enum tagSIATTRIBFLAGS
    {	SIATTRIBFLAGS_AND	= 0x1,
	SIATTRIBFLAGS_OR	= 0x2,
	SIATTRIBFLAGS_APPCOMPAT	= 0x3,
	SIATTRIBFLAGS_MASK	= 0x3
    } 	SIATTRIBFLAGS;


EXTERN_C const IID IID_IShellItemArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12d3ef71-3051-4cc8-a446-9807d6d14433")
    IShellItemArray : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BindToHandler( 
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID rbhid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropertyStore( 
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropertyDescriptionList( 
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAttributes( 
            /* [in] */ SIATTRIBFLAGS dwAttribFlags,
            /* [in] */ SFGAOF sfgaoMask,
            /* [out] */ SFGAOF *psfgaoAttribs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ DWORD *pdwNumItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemAt( 
            /* [in] */ DWORD dwIndex,
            /* [out] */ IShellItem **ppsi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumItems( 
            /* [out] */ IEnumShellItems **ppenumShellItems) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellItemArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellItemArray * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellItemArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellItemArray * This);
        
        HRESULT ( STDMETHODCALLTYPE *BindToHandler )( 
            IShellItemArray * This,
            /* [in] */ IBindCtx *pbc,
            /* [in] */ REFGUID rbhid,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyStore )( 
            IShellItemArray * This,
            /* [in] */ GETPROPERTYSTOREFLAGS flags,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyDescriptionList )( 
            IShellItemArray * This,
            /* [in] */ REFPROPERTYKEY keyType,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetAttributes )( 
            IShellItemArray * This,
            /* [in] */ SIATTRIBFLAGS dwAttribFlags,
            /* [in] */ SFGAOF sfgaoMask,
            /* [out] */ SFGAOF *psfgaoAttribs);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IShellItemArray * This,
            /* [out] */ DWORD *pdwNumItems);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemAt )( 
            IShellItemArray * This,
            /* [in] */ DWORD dwIndex,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *EnumItems )( 
            IShellItemArray * This,
            /* [out] */ IEnumShellItems **ppenumShellItems);
        
        END_INTERFACE
    } IShellItemArrayVtbl;

    interface IShellItemArray
    {
        CONST_VTBL struct IShellItemArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellItemArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellItemArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellItemArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellItemArray_BindToHandler(This,pbc,rbhid,riid,ppvOut)	\
    ( (This)->lpVtbl -> BindToHandler(This,pbc,rbhid,riid,ppvOut) ) 

#define IShellItemArray_GetPropertyStore(This,flags,riid,ppv)	\
    ( (This)->lpVtbl -> GetPropertyStore(This,flags,riid,ppv) ) 

#define IShellItemArray_GetPropertyDescriptionList(This,keyType,riid,ppv)	\
    ( (This)->lpVtbl -> GetPropertyDescriptionList(This,keyType,riid,ppv) ) 

#define IShellItemArray_GetAttributes(This,dwAttribFlags,sfgaoMask,psfgaoAttribs)	\
    ( (This)->lpVtbl -> GetAttributes(This,dwAttribFlags,sfgaoMask,psfgaoAttribs) ) 

#define IShellItemArray_GetCount(This,pdwNumItems)	\
    ( (This)->lpVtbl -> GetCount(This,pdwNumItems) ) 

#define IShellItemArray_GetItemAt(This,dwIndex,ppsi)	\
    ( (This)->lpVtbl -> GetItemAt(This,dwIndex,ppsi) ) 

#define IShellItemArray_EnumItems(This,ppenumShellItems)	\
    ( (This)->lpVtbl -> EnumItems(This,ppenumShellItems) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellItemArray_BindToHandler_Proxy( 
    IShellItemArray * This,
    /* [in] */ IBindCtx *pbc,
    /* [in] */ REFGUID rbhid,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppvOut);


void __RPC_STUB IShellItemArray_BindToHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItemArray_GetPropertyStore_Proxy( 
    IShellItemArray * This,
    /* [in] */ GETPROPERTYSTOREFLAGS flags,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellItemArray_GetPropertyStore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItemArray_GetPropertyDescriptionList_Proxy( 
    IShellItemArray * This,
    /* [in] */ REFPROPERTYKEY keyType,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellItemArray_GetPropertyDescriptionList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItemArray_GetAttributes_Proxy( 
    IShellItemArray * This,
    /* [in] */ SIATTRIBFLAGS dwAttribFlags,
    /* [in] */ SFGAOF sfgaoMask,
    /* [out] */ SFGAOF *psfgaoAttribs);


void __RPC_STUB IShellItemArray_GetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItemArray_GetCount_Proxy( 
    IShellItemArray * This,
    /* [out] */ DWORD *pdwNumItems);


void __RPC_STUB IShellItemArray_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItemArray_GetItemAt_Proxy( 
    IShellItemArray * This,
    /* [in] */ DWORD dwIndex,
    /* [out] */ IShellItem **ppsi);


void __RPC_STUB IShellItemArray_GetItemAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellItemArray_EnumItems_Proxy( 
    IShellItemArray * This,
    /* [out] */ IEnumShellItems **ppenumShellItems);


void __RPC_STUB IShellItemArray_EnumItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellItemArray_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0235 */
/* [local] */ 

SHSTDAPI SHCreateShellItemArray(PCIDLIST_ABSOLUTE pidlParent, IShellFolder *psfParent, UINT cidl, PCUITEMID_CHILD_ARRAY ppidl, IShellItemArray **ppsiItemArray);
SHSTDAPI SHCreateShellItemArrayFromIDLists(UINT cidl, PCIDLIST_ABSOLUTE_ARRAY rgpidl, IShellItemArray **ppsiItemArray);
/* [v1_enum] */ 
enum tagPROPERTYUI_NAME_FLAGS
    {	PUIFNF_DEFAULT	= 0,
	PUIFNF_MNEMONIC	= 0x1
    } ;
typedef DWORD PROPERTYUI_NAME_FLAGS;

/* [v1_enum] */ 
enum tagPROPERTYUI_FLAGS
    {	PUIF_DEFAULT	= 0,
	PUIF_RIGHTALIGN	= 0x1,
	PUIF_NOLABELININFOTIP	= 0x2,
	PUIF_READONLY	= 0x4,
	PUIF_ISGROUP	= 0x8,
	PUIF_REVERSESORT	= 0x10,
	PUIF_CANSTACKBY	= 0x20,
	PUIF_SHOW_BY_DEFAULT	= 0x40,
	PUIF_SHOW_IN_PRIMARY_LIST	= 0x80,
	PUIF_SHOW_IN_SECONDARY_LIST	= 0x100,
	PUIF_HIDEIFNOTPRESENT	= 0x200,
	PUIF_MULTIPLEVALUES	= 0x400,
	PUIF_BEGINCOLUMN	= 0x1000,
	PUIF_ENDCOLUMN	= 0x2000,
	PUIF_HASACTIONHANDLER	= 0x4000,
	PUIF_SLOW	= 0x8000
    } ;
typedef DWORD PROPERTYUI_FLAGS;

/* [v1_enum] */ 
enum tagPROPERTYUI_FORMAT_FLAGS
    {	PUIFFDF_DEFAULT	= 0,
	PUIFFDF_RIGHTTOLEFT	= 0x1,
	PUIFFDF_SHORTFORMAT	= 0x2,
	PUIFFDF_NOTIME	= 0x4,
	PUIFFDF_FRIENDLYDATE	= 0x8,
	PUIFFDF_NOUNITS	= 0x10,
	PUIFFDF_PREFIXNAME	= 0x20,
	PUIFFDF_ALWAYSKB	= 0x40,
	PUIFFDF_FAILIFEMPTYPROP	= 0x80
    } ;
typedef DWORD PROPERTYUI_FORMAT_FLAGS;

/* [v1_enum] */ 
enum tagPROPERTY_COMPARE_VALUES_FLAGS
    {	PCVF_DEFAULT	= 0
    } ;
typedef DWORD PROPERTY_COMPARE_VALUES_FLAGS;

/* [v1_enum] */ 
enum tagPROPERTY_SORT_DESCRIPTION
    {	PSD_GENERIC	= 0,
	PSD_A_Z	= 0x1,
	PSD_LOWEST_HIGHEST	= 0x2,
	PSD_SMALLEST_BIGGEST	= 0x3,
	PSD_OLDEST_NEWEST	= 0x4,
	PSD_CUSTOM	= 0xffffffff
    } ;
typedef DWORD PROPERTY_SORT_DESCRIPTION;

typedef struct tagPROPERTYUI_DEFVAL
    {
    ULONG ulVal;
    LPWSTR pszName;
    } 	PROPERTYUI_DEFVAL;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0235_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0235_v0_0_s_ifspec;

#ifndef __IEditVariantInPlace_INTERFACE_DEFINED__
#define __IEditVariantInPlace_INTERFACE_DEFINED__

/* interface IEditVariantInPlace */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IEditVariantInPlace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4f9a8df8-fca5-4e56-9dcb-c6d1b4bdc81f")
    IEditVariantInPlace : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HWND hwndParent,
            /* [in] */ UINT uCodePage,
            /* [in] */ LPRECT prect,
            /* [in] */ PROPVARIANT *pv,
            /* [in] */ PROPERTYUI_DEFVAL *pDefVals) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Persist( 
            /* [out] */ PROPVARIANT *pv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEditVariantInPlaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEditVariantInPlace * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEditVariantInPlace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEditVariantInPlace * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IEditVariantInPlace * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ UINT uCodePage,
            /* [in] */ LPRECT prect,
            /* [in] */ PROPVARIANT *pv,
            /* [in] */ PROPERTYUI_DEFVAL *pDefVals);
        
        HRESULT ( STDMETHODCALLTYPE *Persist )( 
            IEditVariantInPlace * This,
            /* [out] */ PROPVARIANT *pv);
        
        END_INTERFACE
    } IEditVariantInPlaceVtbl;

    interface IEditVariantInPlace
    {
        CONST_VTBL struct IEditVariantInPlaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEditVariantInPlace_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEditVariantInPlace_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEditVariantInPlace_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEditVariantInPlace_Initialize(This,hwndParent,uCodePage,prect,pv,pDefVals)	\
    ( (This)->lpVtbl -> Initialize(This,hwndParent,uCodePage,prect,pv,pDefVals) ) 

#define IEditVariantInPlace_Persist(This,pv)	\
    ( (This)->lpVtbl -> Persist(This,pv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEditVariantInPlace_Initialize_Proxy( 
    IEditVariantInPlace * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ UINT uCodePage,
    /* [in] */ LPRECT prect,
    /* [in] */ PROPVARIANT *pv,
    /* [in] */ PROPERTYUI_DEFVAL *pDefVals);


void __RPC_STUB IEditVariantInPlace_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEditVariantInPlace_Persist_Proxy( 
    IEditVariantInPlace * This,
    /* [out] */ PROPVARIANT *pv);


void __RPC_STUB IEditVariantInPlace_Persist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEditVariantInPlace_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0236 */
/* [local] */ 

/* [v1_enum] */ 
enum tagDPV_FLAGS
    {	DPV_DEFAULT	= 0,
	DPV_SELECTED	= 0x1,
	DPV_FOCUSED	= 0x2
    } ;
typedef DWORD DPV_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0236_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0236_v0_0_s_ifspec;

#ifndef __IDrawPropVariant_INTERFACE_DEFINED__
#define __IDrawPropVariant_INTERFACE_DEFINED__

/* interface IDrawPropVariant */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_IDrawPropVariant;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9c054922-416f-4053-8f9b-f991dc3d108c")
    IDrawPropVariant : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ const PROPVARIANT *ppv,
            /* [in] */ HDC hdc,
            /* [in] */ RECT *prc,
            /* [in] */ DPV_FLAGS dwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWidth( 
            /* [out] */ UINT *puWidth,
            /* [out] */ DWORD *pdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDrawPropVariantVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDrawPropVariant * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDrawPropVariant * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDrawPropVariant * This);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IDrawPropVariant * This,
            /* [in] */ const PROPVARIANT *ppv,
            /* [in] */ HDC hdc,
            /* [in] */ RECT *prc,
            /* [in] */ DPV_FLAGS dwState);
        
        HRESULT ( STDMETHODCALLTYPE *GetWidth )( 
            IDrawPropVariant * This,
            /* [out] */ UINT *puWidth,
            /* [out] */ DWORD *pdwFlags);
        
        END_INTERFACE
    } IDrawPropVariantVtbl;

    interface IDrawPropVariant
    {
        CONST_VTBL struct IDrawPropVariantVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDrawPropVariant_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDrawPropVariant_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDrawPropVariant_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDrawPropVariant_Draw(This,ppv,hdc,prc,dwState)	\
    ( (This)->lpVtbl -> Draw(This,ppv,hdc,prc,dwState) ) 

#define IDrawPropVariant_GetWidth(This,puWidth,pdwFlags)	\
    ( (This)->lpVtbl -> GetWidth(This,puWidth,pdwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDrawPropVariant_Draw_Proxy( 
    IDrawPropVariant * This,
    /* [in] */ const PROPVARIANT *ppv,
    /* [in] */ HDC hdc,
    /* [in] */ RECT *prc,
    /* [in] */ DPV_FLAGS dwState);


void __RPC_STUB IDrawPropVariant_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDrawPropVariant_GetWidth_Proxy( 
    IDrawPropVariant * This,
    /* [out] */ UINT *puWidth,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IDrawPropVariant_GetWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDrawPropVariant_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0237 */
/* [local] */ 

#if (_WIN32_IE >= 0x0501)
SHSTDAPI SHFormatForDisplay(REFFMTID fmtid, PROPID pid, const PROPVARIANT *pPropVar, PROPERTYUI_FORMAT_FLAGS flags, LPWSTR pwszText, DWORD cchText);
#endif // (_WIN32_IE >= 0x0501)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0237_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0237_v0_0_s_ifspec;

#ifndef __IPropertyUI_INTERFACE_DEFINED__
#define __IPropertyUI_INTERFACE_DEFINED__

/* interface IPropertyUI */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IPropertyUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("757a7d9f-919a-4118-99d7-dbb208c8cc66")
    IPropertyUI : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ParsePropertyName( 
            /* [in] */ LPCWSTR pszName,
            /* [out] */ FMTID *pfmtid,
            /* [out] */ PROPID *ppid,
            /* [out][in] */ ULONG *pchEaten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCannonicalName( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [in] */ PROPERTYUI_NAME_FLAGS flags,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropertyDescription( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultWidth( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [out] */ ULONG *pcxChars) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [out] */ PROPERTYUI_FLAGS *pflags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FormatForDisplay( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [in] */ const PROPVARIANT *pvar,
            /* [in] */ PROPERTYUI_FORMAT_FLAGS flags,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHelpInfo( 
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [size_is][out] */ LPWSTR pwszHelpFile,
            /* [in] */ DWORD cch,
            /* [out] */ UINT *puHelpID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropertyUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropertyUI * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropertyUI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropertyUI * This);
        
        HRESULT ( STDMETHODCALLTYPE *ParsePropertyName )( 
            IPropertyUI * This,
            /* [in] */ LPCWSTR pszName,
            /* [out] */ FMTID *pfmtid,
            /* [out] */ PROPID *ppid,
            /* [out][in] */ ULONG *pchEaten);
        
        HRESULT ( STDMETHODCALLTYPE *GetCannonicalName )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayName )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [in] */ PROPERTYUI_NAME_FLAGS flags,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyDescription )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultWidth )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [out] */ ULONG *pcxChars);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlags )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [out] */ PROPERTYUI_FLAGS *pflags);
        
        HRESULT ( STDMETHODCALLTYPE *FormatForDisplay )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [in] */ const PROPVARIANT *pvar,
            /* [in] */ PROPERTYUI_FORMAT_FLAGS flags,
            /* [size_is][out] */ LPWSTR pwszText,
            /* [in] */ DWORD cchText);
        
        HRESULT ( STDMETHODCALLTYPE *GetHelpInfo )( 
            IPropertyUI * This,
            /* [in] */ REFFMTID fmtid,
            /* [in] */ PROPID pid,
            /* [size_is][out] */ LPWSTR pwszHelpFile,
            /* [in] */ DWORD cch,
            /* [out] */ UINT *puHelpID);
        
        END_INTERFACE
    } IPropertyUIVtbl;

    interface IPropertyUI
    {
        CONST_VTBL struct IPropertyUIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropertyUI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPropertyUI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPropertyUI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPropertyUI_ParsePropertyName(This,pszName,pfmtid,ppid,pchEaten)	\
    ( (This)->lpVtbl -> ParsePropertyName(This,pszName,pfmtid,ppid,pchEaten) ) 

#define IPropertyUI_GetCannonicalName(This,fmtid,pid,pwszText,cchText)	\
    ( (This)->lpVtbl -> GetCannonicalName(This,fmtid,pid,pwszText,cchText) ) 

#define IPropertyUI_GetDisplayName(This,fmtid,pid,flags,pwszText,cchText)	\
    ( (This)->lpVtbl -> GetDisplayName(This,fmtid,pid,flags,pwszText,cchText) ) 

#define IPropertyUI_GetPropertyDescription(This,fmtid,pid,pwszText,cchText)	\
    ( (This)->lpVtbl -> GetPropertyDescription(This,fmtid,pid,pwszText,cchText) ) 

#define IPropertyUI_GetDefaultWidth(This,fmtid,pid,pcxChars)	\
    ( (This)->lpVtbl -> GetDefaultWidth(This,fmtid,pid,pcxChars) ) 

#define IPropertyUI_GetFlags(This,fmtid,pid,pflags)	\
    ( (This)->lpVtbl -> GetFlags(This,fmtid,pid,pflags) ) 

#define IPropertyUI_FormatForDisplay(This,fmtid,pid,pvar,flags,pwszText,cchText)	\
    ( (This)->lpVtbl -> FormatForDisplay(This,fmtid,pid,pvar,flags,pwszText,cchText) ) 

#define IPropertyUI_GetHelpInfo(This,fmtid,pid,pwszHelpFile,cch,puHelpID)	\
    ( (This)->lpVtbl -> GetHelpInfo(This,fmtid,pid,pwszHelpFile,cch,puHelpID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPropertyUI_ParsePropertyName_Proxy( 
    IPropertyUI * This,
    /* [in] */ LPCWSTR pszName,
    /* [out] */ FMTID *pfmtid,
    /* [out] */ PROPID *ppid,
    /* [out][in] */ ULONG *pchEaten);


void __RPC_STUB IPropertyUI_ParsePropertyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_GetCannonicalName_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [size_is][out] */ LPWSTR pwszText,
    /* [in] */ DWORD cchText);


void __RPC_STUB IPropertyUI_GetCannonicalName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_GetDisplayName_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [in] */ PROPERTYUI_NAME_FLAGS flags,
    /* [size_is][out] */ LPWSTR pwszText,
    /* [in] */ DWORD cchText);


void __RPC_STUB IPropertyUI_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_GetPropertyDescription_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [size_is][out] */ LPWSTR pwszText,
    /* [in] */ DWORD cchText);


void __RPC_STUB IPropertyUI_GetPropertyDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_GetDefaultWidth_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [out] */ ULONG *pcxChars);


void __RPC_STUB IPropertyUI_GetDefaultWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_GetFlags_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [out] */ PROPERTYUI_FLAGS *pflags);


void __RPC_STUB IPropertyUI_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_FormatForDisplay_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [in] */ const PROPVARIANT *pvar,
    /* [in] */ PROPERTYUI_FORMAT_FLAGS flags,
    /* [size_is][out] */ LPWSTR pwszText,
    /* [in] */ DWORD cchText);


void __RPC_STUB IPropertyUI_FormatForDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyUI_GetHelpInfo_Proxy( 
    IPropertyUI * This,
    /* [in] */ REFFMTID fmtid,
    /* [in] */ PROPID pid,
    /* [size_is][out] */ LPWSTR pwszHelpFile,
    /* [in] */ DWORD cch,
    /* [out] */ UINT *puHelpID);


void __RPC_STUB IPropertyUI_GetHelpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropertyUI_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0238 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagPROPERTY_GROUPING_TYPE
    {	PGT_DISCRETE	= 0,
	PGT_STATICRANGE	= 0x1,
	PGT_DYNAMICRANGE	= 0x2,
	PGT_DATERANGE	= 0x3
    } 	PROPERTY_GROUPING_TYPE;

typedef /* [v1_enum] */ 
enum tagPROPERTY_SUGGESTED_VALUES_TYPE
    {	PSV_DEFAULT	= 0,
	PSV_MOSTCOMMON	= 0x1
    } 	PROPERTY_SUGGESTED_VALUES_TYPE;

#if (_WIN32_IE >= 0x0501)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0238_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0238_v0_0_s_ifspec;

#ifndef __IPropVariantArray_INTERFACE_DEFINED__
#define __IPropVariantArray_INTERFACE_DEFINED__

/* interface IPropVariantArray */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IPropVariantArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b19eda26-0eba-4654-a3a3-779793fcb1f5")
    IPropVariantArray : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ int *pcItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ int iIndex,
            /* [out] */ PROPVARIANT *ppvar) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropVariantArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropVariantArray * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropVariantArray * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropVariantArray * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IPropVariantArray * This,
            /* [out] */ int *pcItems);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            IPropVariantArray * This,
            /* [in] */ int iIndex,
            /* [out] */ PROPVARIANT *ppvar);
        
        END_INTERFACE
    } IPropVariantArrayVtbl;

    interface IPropVariantArray
    {
        CONST_VTBL struct IPropVariantArrayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropVariantArray_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPropVariantArray_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPropVariantArray_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPropVariantArray_GetCount(This,pcItems)	\
    ( (This)->lpVtbl -> GetCount(This,pcItems) ) 

#define IPropVariantArray_GetAt(This,iIndex,ppvar)	\
    ( (This)->lpVtbl -> GetAt(This,iIndex,ppvar) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPropVariantArray_GetCount_Proxy( 
    IPropVariantArray * This,
    /* [out] */ int *pcItems);


void __RPC_STUB IPropVariantArray_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropVariantArray_GetAt_Proxy( 
    IPropVariantArray * This,
    /* [in] */ int iIndex,
    /* [out] */ PROPVARIANT *ppvar);


void __RPC_STUB IPropVariantArray_GetAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropVariantArray_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0239 */
/* [local] */ 

/* [v1_enum] */ 
enum tagPROPERTY_DISPLAY_NAME_TYPE
    {	PDNT_DEFAULT	= 0,
	PDNT_PLURAL	= 0x1
    } ;
typedef DWORD PROPERTY_DISPLAY_NAME_TYPE;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0239_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0239_v0_0_s_ifspec;

#ifndef __IPropertyDescription_INTERFACE_DEFINED__
#define __IPropertyDescription_INTERFACE_DEFINED__

/* interface IPropertyDescription */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IPropertyDescription;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("126ab71f-33fa-4e74-b1e9-5c2ef0bfcfe0")
    IPropertyDescription : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPropertyKey( 
            /* [out] */ PROPERTYKEY *pkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCanonicalName( 
            /* [out] */ BSTR *pbstrName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [in] */ PROPERTY_DISPLAY_NAME_TYPE type,
            /* [out] */ BSTR *pbstrName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEditInvitation( 
            /* [out] */ BSTR *pbstrInvite) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlags( 
            /* [in] */ PROPERTYUI_FLAGS mask,
            /* [in] */ PROPERTYUI_FLAGS flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ PROPERTYUI_FLAGS *pflags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStackClassType( 
            /* [out] */ BSTR *pbstrClassType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStackViewStatePropertyBag( 
            /* [in] */ DWORD grfMode,
            /* [out] */ IPropertyBag **pppb) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHelpUrl( 
            /* [out] */ BSTR *pbstrUrl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEditingControlCLSID( 
            /* [out] */ CLSID *pclsidControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEditingControlElementName( 
            /* [out] */ BSTR *pbstrAvalonAssembly,
            /* [out] */ BSTR *pbstrAvalonModule) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDrawingControlCLSID( 
            /* [out] */ CLSID *pclsidControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDrawingControlElementName( 
            /* [out] */ BSTR *pbstrAvalonAssembly,
            /* [out] */ BSTR *pbstrAvalonModule) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetActionHandler( 
            /* [in] */ IDataObject *pdo,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSuggestedValues( 
            /* [in] */ PROPERTY_SUGGESTED_VALUES_TYPE suggval,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultCharWidth( 
            /* [out] */ DWORD *pcxChars) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayType( 
            /* [out] */ DWORD *pshcolstatetype) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGroupingType( 
            /* [out] */ PROPERTY_GROUPING_TYPE *pgroupingtype) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropVariantType( 
            /* [out] */ VARTYPE *pvt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ IPropertyStore *pstore,
            /* [out] */ PROPVARIANT *pv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ IPropertyStore *pstore,
            /* [in] */ const PROPVARIANT *pv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FormatForDisplay( 
            /* [in] */ IPropertyStore *pstore,
            /* [in] */ PROPERTYUI_FORMAT_FLAGS flags,
            /* [out] */ BSTR *pbstrDisplay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRelativeDescription( 
            /* [in] */ IPropertyStore *pstore1,
            /* [in] */ IPropertyStore *pstore2,
            /* [in] */ PROPERTY_COMPARE_VALUES_FLAGS flags,
            /* [out] */ BSTR *pbstrDesc1,
            /* [out] */ BSTR *pbstrDesc2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSortDescription( 
            /* [in] */ BOOL fDescending,
            /* [out] */ BSTR *pbstrDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropertyDescriptionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropertyDescription * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropertyDescription * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropertyDescription * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyKey )( 
            IPropertyDescription * This,
            /* [out] */ PROPERTYKEY *pkey);
        
        HRESULT ( STDMETHODCALLTYPE *GetCanonicalName )( 
            IPropertyDescription * This,
            /* [out] */ BSTR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayName )( 
            IPropertyDescription * This,
            /* [in] */ PROPERTY_DISPLAY_NAME_TYPE type,
            /* [out] */ BSTR *pbstrName);
        
        HRESULT ( STDMETHODCALLTYPE *GetEditInvitation )( 
            IPropertyDescription * This,
            /* [out] */ BSTR *pbstrInvite);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlags )( 
            IPropertyDescription * This,
            /* [in] */ PROPERTYUI_FLAGS mask,
            /* [in] */ PROPERTYUI_FLAGS flags);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlags )( 
            IPropertyDescription * This,
            /* [out] */ PROPERTYUI_FLAGS *pflags);
        
        HRESULT ( STDMETHODCALLTYPE *GetStackClassType )( 
            IPropertyDescription * This,
            /* [out] */ BSTR *pbstrClassType);
        
        HRESULT ( STDMETHODCALLTYPE *GetStackViewStatePropertyBag )( 
            IPropertyDescription * This,
            /* [in] */ DWORD grfMode,
            /* [out] */ IPropertyBag **pppb);
        
        HRESULT ( STDMETHODCALLTYPE *GetHelpUrl )( 
            IPropertyDescription * This,
            /* [out] */ BSTR *pbstrUrl);
        
        HRESULT ( STDMETHODCALLTYPE *GetEditingControlCLSID )( 
            IPropertyDescription * This,
            /* [out] */ CLSID *pclsidControl);
        
        HRESULT ( STDMETHODCALLTYPE *GetEditingControlElementName )( 
            IPropertyDescription * This,
            /* [out] */ BSTR *pbstrAvalonAssembly,
            /* [out] */ BSTR *pbstrAvalonModule);
        
        HRESULT ( STDMETHODCALLTYPE *GetDrawingControlCLSID )( 
            IPropertyDescription * This,
            /* [out] */ CLSID *pclsidControl);
        
        HRESULT ( STDMETHODCALLTYPE *GetDrawingControlElementName )( 
            IPropertyDescription * This,
            /* [out] */ BSTR *pbstrAvalonAssembly,
            /* [out] */ BSTR *pbstrAvalonModule);
        
        HRESULT ( STDMETHODCALLTYPE *GetActionHandler )( 
            IPropertyDescription * This,
            /* [in] */ IDataObject *pdo,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetSuggestedValues )( 
            IPropertyDescription * This,
            /* [in] */ PROPERTY_SUGGESTED_VALUES_TYPE suggval,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetDefaultCharWidth )( 
            IPropertyDescription * This,
            /* [out] */ DWORD *pcxChars);
        
        HRESULT ( STDMETHODCALLTYPE *GetDisplayType )( 
            IPropertyDescription * This,
            /* [out] */ DWORD *pshcolstatetype);
        
        HRESULT ( STDMETHODCALLTYPE *GetGroupingType )( 
            IPropertyDescription * This,
            /* [out] */ PROPERTY_GROUPING_TYPE *pgroupingtype);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropVariantType )( 
            IPropertyDescription * This,
            /* [out] */ VARTYPE *pvt);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IPropertyDescription * This,
            /* [in] */ IPropertyStore *pstore,
            /* [out] */ PROPVARIANT *pv);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            IPropertyDescription * This,
            /* [in] */ IPropertyStore *pstore,
            /* [in] */ const PROPVARIANT *pv);
        
        HRESULT ( STDMETHODCALLTYPE *FormatForDisplay )( 
            IPropertyDescription * This,
            /* [in] */ IPropertyStore *pstore,
            /* [in] */ PROPERTYUI_FORMAT_FLAGS flags,
            /* [out] */ BSTR *pbstrDisplay);
        
        HRESULT ( STDMETHODCALLTYPE *GetRelativeDescription )( 
            IPropertyDescription * This,
            /* [in] */ IPropertyStore *pstore1,
            /* [in] */ IPropertyStore *pstore2,
            /* [in] */ PROPERTY_COMPARE_VALUES_FLAGS flags,
            /* [out] */ BSTR *pbstrDesc1,
            /* [out] */ BSTR *pbstrDesc2);
        
        HRESULT ( STDMETHODCALLTYPE *GetSortDescription )( 
            IPropertyDescription * This,
            /* [in] */ BOOL fDescending,
            /* [out] */ BSTR *pbstrDescription);
        
        END_INTERFACE
    } IPropertyDescriptionVtbl;

    interface IPropertyDescription
    {
        CONST_VTBL struct IPropertyDescriptionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropertyDescription_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPropertyDescription_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPropertyDescription_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPropertyDescription_GetPropertyKey(This,pkey)	\
    ( (This)->lpVtbl -> GetPropertyKey(This,pkey) ) 

#define IPropertyDescription_GetCanonicalName(This,pbstrName)	\
    ( (This)->lpVtbl -> GetCanonicalName(This,pbstrName) ) 

#define IPropertyDescription_GetDisplayName(This,type,pbstrName)	\
    ( (This)->lpVtbl -> GetDisplayName(This,type,pbstrName) ) 

#define IPropertyDescription_GetEditInvitation(This,pbstrInvite)	\
    ( (This)->lpVtbl -> GetEditInvitation(This,pbstrInvite) ) 

#define IPropertyDescription_SetFlags(This,mask,flags)	\
    ( (This)->lpVtbl -> SetFlags(This,mask,flags) ) 

#define IPropertyDescription_GetFlags(This,pflags)	\
    ( (This)->lpVtbl -> GetFlags(This,pflags) ) 

#define IPropertyDescription_GetStackClassType(This,pbstrClassType)	\
    ( (This)->lpVtbl -> GetStackClassType(This,pbstrClassType) ) 

#define IPropertyDescription_GetStackViewStatePropertyBag(This,grfMode,pppb)	\
    ( (This)->lpVtbl -> GetStackViewStatePropertyBag(This,grfMode,pppb) ) 

#define IPropertyDescription_GetHelpUrl(This,pbstrUrl)	\
    ( (This)->lpVtbl -> GetHelpUrl(This,pbstrUrl) ) 

#define IPropertyDescription_GetEditingControlCLSID(This,pclsidControl)	\
    ( (This)->lpVtbl -> GetEditingControlCLSID(This,pclsidControl) ) 

#define IPropertyDescription_GetEditingControlElementName(This,pbstrAvalonAssembly,pbstrAvalonModule)	\
    ( (This)->lpVtbl -> GetEditingControlElementName(This,pbstrAvalonAssembly,pbstrAvalonModule) ) 

#define IPropertyDescription_GetDrawingControlCLSID(This,pclsidControl)	\
    ( (This)->lpVtbl -> GetDrawingControlCLSID(This,pclsidControl) ) 

#define IPropertyDescription_GetDrawingControlElementName(This,pbstrAvalonAssembly,pbstrAvalonModule)	\
    ( (This)->lpVtbl -> GetDrawingControlElementName(This,pbstrAvalonAssembly,pbstrAvalonModule) ) 

#define IPropertyDescription_GetActionHandler(This,pdo,riid,ppv)	\
    ( (This)->lpVtbl -> GetActionHandler(This,pdo,riid,ppv) ) 

#define IPropertyDescription_GetSuggestedValues(This,suggval,riid,ppv)	\
    ( (This)->lpVtbl -> GetSuggestedValues(This,suggval,riid,ppv) ) 

#define IPropertyDescription_GetDefaultCharWidth(This,pcxChars)	\
    ( (This)->lpVtbl -> GetDefaultCharWidth(This,pcxChars) ) 

#define IPropertyDescription_GetDisplayType(This,pshcolstatetype)	\
    ( (This)->lpVtbl -> GetDisplayType(This,pshcolstatetype) ) 

#define IPropertyDescription_GetGroupingType(This,pgroupingtype)	\
    ( (This)->lpVtbl -> GetGroupingType(This,pgroupingtype) ) 

#define IPropertyDescription_GetPropVariantType(This,pvt)	\
    ( (This)->lpVtbl -> GetPropVariantType(This,pvt) ) 

#define IPropertyDescription_GetValue(This,pstore,pv)	\
    ( (This)->lpVtbl -> GetValue(This,pstore,pv) ) 

#define IPropertyDescription_SetValue(This,pstore,pv)	\
    ( (This)->lpVtbl -> SetValue(This,pstore,pv) ) 

#define IPropertyDescription_FormatForDisplay(This,pstore,flags,pbstrDisplay)	\
    ( (This)->lpVtbl -> FormatForDisplay(This,pstore,flags,pbstrDisplay) ) 

#define IPropertyDescription_GetRelativeDescription(This,pstore1,pstore2,flags,pbstrDesc1,pbstrDesc2)	\
    ( (This)->lpVtbl -> GetRelativeDescription(This,pstore1,pstore2,flags,pbstrDesc1,pbstrDesc2) ) 

#define IPropertyDescription_GetSortDescription(This,fDescending,pbstrDescription)	\
    ( (This)->lpVtbl -> GetSortDescription(This,fDescending,pbstrDescription) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPropertyDescription_GetPropertyKey_Proxy( 
    IPropertyDescription * This,
    /* [out] */ PROPERTYKEY *pkey);


void __RPC_STUB IPropertyDescription_GetPropertyKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetCanonicalName_Proxy( 
    IPropertyDescription * This,
    /* [out] */ BSTR *pbstrName);


void __RPC_STUB IPropertyDescription_GetCanonicalName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetDisplayName_Proxy( 
    IPropertyDescription * This,
    /* [in] */ PROPERTY_DISPLAY_NAME_TYPE type,
    /* [out] */ BSTR *pbstrName);


void __RPC_STUB IPropertyDescription_GetDisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetEditInvitation_Proxy( 
    IPropertyDescription * This,
    /* [out] */ BSTR *pbstrInvite);


void __RPC_STUB IPropertyDescription_GetEditInvitation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_SetFlags_Proxy( 
    IPropertyDescription * This,
    /* [in] */ PROPERTYUI_FLAGS mask,
    /* [in] */ PROPERTYUI_FLAGS flags);


void __RPC_STUB IPropertyDescription_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetFlags_Proxy( 
    IPropertyDescription * This,
    /* [out] */ PROPERTYUI_FLAGS *pflags);


void __RPC_STUB IPropertyDescription_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetStackClassType_Proxy( 
    IPropertyDescription * This,
    /* [out] */ BSTR *pbstrClassType);


void __RPC_STUB IPropertyDescription_GetStackClassType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetStackViewStatePropertyBag_Proxy( 
    IPropertyDescription * This,
    /* [in] */ DWORD grfMode,
    /* [out] */ IPropertyBag **pppb);


void __RPC_STUB IPropertyDescription_GetStackViewStatePropertyBag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetHelpUrl_Proxy( 
    IPropertyDescription * This,
    /* [out] */ BSTR *pbstrUrl);


void __RPC_STUB IPropertyDescription_GetHelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetEditingControlCLSID_Proxy( 
    IPropertyDescription * This,
    /* [out] */ CLSID *pclsidControl);


void __RPC_STUB IPropertyDescription_GetEditingControlCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetEditingControlElementName_Proxy( 
    IPropertyDescription * This,
    /* [out] */ BSTR *pbstrAvalonAssembly,
    /* [out] */ BSTR *pbstrAvalonModule);


void __RPC_STUB IPropertyDescription_GetEditingControlElementName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetDrawingControlCLSID_Proxy( 
    IPropertyDescription * This,
    /* [out] */ CLSID *pclsidControl);


void __RPC_STUB IPropertyDescription_GetDrawingControlCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetDrawingControlElementName_Proxy( 
    IPropertyDescription * This,
    /* [out] */ BSTR *pbstrAvalonAssembly,
    /* [out] */ BSTR *pbstrAvalonModule);


void __RPC_STUB IPropertyDescription_GetDrawingControlElementName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetActionHandler_Proxy( 
    IPropertyDescription * This,
    /* [in] */ IDataObject *pdo,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IPropertyDescription_GetActionHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetSuggestedValues_Proxy( 
    IPropertyDescription * This,
    /* [in] */ PROPERTY_SUGGESTED_VALUES_TYPE suggval,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IPropertyDescription_GetSuggestedValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetDefaultCharWidth_Proxy( 
    IPropertyDescription * This,
    /* [out] */ DWORD *pcxChars);


void __RPC_STUB IPropertyDescription_GetDefaultCharWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetDisplayType_Proxy( 
    IPropertyDescription * This,
    /* [out] */ DWORD *pshcolstatetype);


void __RPC_STUB IPropertyDescription_GetDisplayType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetGroupingType_Proxy( 
    IPropertyDescription * This,
    /* [out] */ PROPERTY_GROUPING_TYPE *pgroupingtype);


void __RPC_STUB IPropertyDescription_GetGroupingType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetPropVariantType_Proxy( 
    IPropertyDescription * This,
    /* [out] */ VARTYPE *pvt);


void __RPC_STUB IPropertyDescription_GetPropVariantType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetValue_Proxy( 
    IPropertyDescription * This,
    /* [in] */ IPropertyStore *pstore,
    /* [out] */ PROPVARIANT *pv);


void __RPC_STUB IPropertyDescription_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_SetValue_Proxy( 
    IPropertyDescription * This,
    /* [in] */ IPropertyStore *pstore,
    /* [in] */ const PROPVARIANT *pv);


void __RPC_STUB IPropertyDescription_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_FormatForDisplay_Proxy( 
    IPropertyDescription * This,
    /* [in] */ IPropertyStore *pstore,
    /* [in] */ PROPERTYUI_FORMAT_FLAGS flags,
    /* [out] */ BSTR *pbstrDisplay);


void __RPC_STUB IPropertyDescription_FormatForDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetRelativeDescription_Proxy( 
    IPropertyDescription * This,
    /* [in] */ IPropertyStore *pstore1,
    /* [in] */ IPropertyStore *pstore2,
    /* [in] */ PROPERTY_COMPARE_VALUES_FLAGS flags,
    /* [out] */ BSTR *pbstrDesc1,
    /* [out] */ BSTR *pbstrDesc2);


void __RPC_STUB IPropertyDescription_GetRelativeDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescription_GetSortDescription_Proxy( 
    IPropertyDescription * This,
    /* [in] */ BOOL fDescending,
    /* [out] */ BSTR *pbstrDescription);


void __RPC_STUB IPropertyDescription_GetSortDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropertyDescription_INTERFACE_DEFINED__ */


#ifndef __IAggregatePropertyStore_INTERFACE_DEFINED__
#define __IAggregatePropertyStore_INTERFACE_DEFINED__

/* interface IAggregatePropertyStore */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IAggregatePropertyStore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e9c40a8f-f83d-47a0-b718-37ed62fcb26b")
    IAggregatePropertyStore : public IPropertyStore
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAggregateValue( 
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ PROPVARIANT *pv,
            /* [out] */ BOOL *pfMultipleValues) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShellItems( 
            /* [out] */ IShellItemArray **ppsia) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStoreCount( 
            /* [out] */ DWORD *pcStores) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStoreAt( 
            /* [in] */ DWORD i,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAggregatePropertyStoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAggregatePropertyStore * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAggregatePropertyStore * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAggregatePropertyStore * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IAggregatePropertyStore * This,
            /* [out] */ DWORD *cProps);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            IAggregatePropertyStore * This,
            /* [in] */ DWORD iProp,
            /* [out] */ PROPERTYKEY *pkey);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IAggregatePropertyStore * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ PROPVARIANT *pv);
        
        HRESULT ( STDMETHODCALLTYPE *SetValue )( 
            IAggregatePropertyStore * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ const PROPVARIANT *pv);
        
        HRESULT ( STDMETHODCALLTYPE *Flush )( 
            IAggregatePropertyStore * This,
            /* [in] */ IProgressNotify *pn);
        
        HRESULT ( STDMETHODCALLTYPE *GetAggregateValue )( 
            IAggregatePropertyStore * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [out] */ PROPVARIANT *pv,
            /* [out] */ BOOL *pfMultipleValues);
        
        HRESULT ( STDMETHODCALLTYPE *GetShellItems )( 
            IAggregatePropertyStore * This,
            /* [out] */ IShellItemArray **ppsia);
        
        HRESULT ( STDMETHODCALLTYPE *GetStoreCount )( 
            IAggregatePropertyStore * This,
            /* [out] */ DWORD *pcStores);
        
        HRESULT ( STDMETHODCALLTYPE *GetStoreAt )( 
            IAggregatePropertyStore * This,
            /* [in] */ DWORD i,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IAggregatePropertyStoreVtbl;

    interface IAggregatePropertyStore
    {
        CONST_VTBL struct IAggregatePropertyStoreVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAggregatePropertyStore_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAggregatePropertyStore_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAggregatePropertyStore_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAggregatePropertyStore_GetCount(This,cProps)	\
    ( (This)->lpVtbl -> GetCount(This,cProps) ) 

#define IAggregatePropertyStore_GetAt(This,iProp,pkey)	\
    ( (This)->lpVtbl -> GetAt(This,iProp,pkey) ) 

#define IAggregatePropertyStore_GetValue(This,key,pv)	\
    ( (This)->lpVtbl -> GetValue(This,key,pv) ) 

#define IAggregatePropertyStore_SetValue(This,key,pv)	\
    ( (This)->lpVtbl -> SetValue(This,key,pv) ) 

#define IAggregatePropertyStore_Flush(This,pn)	\
    ( (This)->lpVtbl -> Flush(This,pn) ) 


#define IAggregatePropertyStore_GetAggregateValue(This,key,pv,pfMultipleValues)	\
    ( (This)->lpVtbl -> GetAggregateValue(This,key,pv,pfMultipleValues) ) 

#define IAggregatePropertyStore_GetShellItems(This,ppsia)	\
    ( (This)->lpVtbl -> GetShellItems(This,ppsia) ) 

#define IAggregatePropertyStore_GetStoreCount(This,pcStores)	\
    ( (This)->lpVtbl -> GetStoreCount(This,pcStores) ) 

#define IAggregatePropertyStore_GetStoreAt(This,i,riid,ppv)	\
    ( (This)->lpVtbl -> GetStoreAt(This,i,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAggregatePropertyStore_GetAggregateValue_Proxy( 
    IAggregatePropertyStore * This,
    /* [in] */ REFPROPERTYKEY key,
    /* [out] */ PROPVARIANT *pv,
    /* [out] */ BOOL *pfMultipleValues);


void __RPC_STUB IAggregatePropertyStore_GetAggregateValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAggregatePropertyStore_GetShellItems_Proxy( 
    IAggregatePropertyStore * This,
    /* [out] */ IShellItemArray **ppsia);


void __RPC_STUB IAggregatePropertyStore_GetShellItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAggregatePropertyStore_GetStoreCount_Proxy( 
    IAggregatePropertyStore * This,
    /* [out] */ DWORD *pcStores);


void __RPC_STUB IAggregatePropertyStore_GetStoreCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAggregatePropertyStore_GetStoreAt_Proxy( 
    IAggregatePropertyStore * This,
    /* [in] */ DWORD i,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IAggregatePropertyStore_GetStoreAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAggregatePropertyStore_INTERFACE_DEFINED__ */


#ifndef __IPropertyDescriptionList_INTERFACE_DEFINED__
#define __IPropertyDescriptionList_INTERFACE_DEFINED__

/* interface IPropertyDescriptionList */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IPropertyDescriptionList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2c2aecc9-c0ab-497f-a92c-56f2968810a1")
    IPropertyDescriptionList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ DWORD *pcmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAt( 
            /* [in] */ DWORD nmd,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropertyDescriptionListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPropertyDescriptionList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPropertyDescriptionList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPropertyDescriptionList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IPropertyDescriptionList * This,
            /* [out] */ DWORD *pcmd);
        
        HRESULT ( STDMETHODCALLTYPE *GetAt )( 
            IPropertyDescriptionList * This,
            /* [in] */ DWORD nmd,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IPropertyDescriptionListVtbl;

    interface IPropertyDescriptionList
    {
        CONST_VTBL struct IPropertyDescriptionListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropertyDescriptionList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPropertyDescriptionList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPropertyDescriptionList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPropertyDescriptionList_GetCount(This,pcmd)	\
    ( (This)->lpVtbl -> GetCount(This,pcmd) ) 

#define IPropertyDescriptionList_GetAt(This,nmd,riid,ppv)	\
    ( (This)->lpVtbl -> GetAt(This,nmd,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPropertyDescriptionList_GetCount_Proxy( 
    IPropertyDescriptionList * This,
    /* [out] */ DWORD *pcmd);


void __RPC_STUB IPropertyDescriptionList_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyDescriptionList_GetAt_Proxy( 
    IPropertyDescriptionList * This,
    /* [in] */ DWORD nmd,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IPropertyDescriptionList_GetAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropertyDescriptionList_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0242 */
/* [local] */ 

SHSTDAPI SHGetPropertyDescription(REFPROPERTYKEY key, REFIID riid, void **ppv);
SHSTDAPI SHGetPropertyDescriptionByName(LPCWSTR pszCanonicalName, REFIID riid, void **ppv);
SHSTDAPI SHGetPropertyDescriptionListFromString(LPCWSTR pszPropList, REFIID riid, void **ppv);
#endif // (_WIN32_IE >= 0x0501)
#if (_WIN32_IE >= 0x0500)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0242_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0242_v0_0_s_ifspec;

#ifndef __ICategoryProvider_INTERFACE_DEFINED__
#define __ICategoryProvider_INTERFACE_DEFINED__

/* interface ICategoryProvider */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_ICategoryProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9af64809-5864-4c26-a720-c1f78c086ee3")
    ICategoryProvider : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CanCategorizeOnSCID( 
            SHCOLUMNID *pscid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDefaultCategory( 
            GUID *pguid,
            SHCOLUMNID *pscid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCategoryForSCID( 
            SHCOLUMNID *pscid,
            GUID *pguid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumCategories( 
            IEnumGUID **penum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCategoryName( 
            GUID *pguid,
            LPWSTR pszName,
            UINT cch) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateCategory( 
            GUID *pguid,
            REFIID riid,
            /* [iid_is] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICategoryProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICategoryProvider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICategoryProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICategoryProvider * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CanCategorizeOnSCID )( 
            ICategoryProvider * This,
            SHCOLUMNID *pscid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDefaultCategory )( 
            ICategoryProvider * This,
            GUID *pguid,
            SHCOLUMNID *pscid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCategoryForSCID )( 
            ICategoryProvider * This,
            SHCOLUMNID *pscid,
            GUID *pguid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumCategories )( 
            ICategoryProvider * This,
            IEnumGUID **penum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCategoryName )( 
            ICategoryProvider * This,
            GUID *pguid,
            LPWSTR pszName,
            UINT cch);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateCategory )( 
            ICategoryProvider * This,
            GUID *pguid,
            REFIID riid,
            /* [iid_is] */ void **ppv);
        
        END_INTERFACE
    } ICategoryProviderVtbl;

    interface ICategoryProvider
    {
        CONST_VTBL struct ICategoryProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICategoryProvider_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICategoryProvider_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICategoryProvider_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICategoryProvider_CanCategorizeOnSCID(This,pscid)	\
    ( (This)->lpVtbl -> CanCategorizeOnSCID(This,pscid) ) 

#define ICategoryProvider_GetDefaultCategory(This,pguid,pscid)	\
    ( (This)->lpVtbl -> GetDefaultCategory(This,pguid,pscid) ) 

#define ICategoryProvider_GetCategoryForSCID(This,pscid,pguid)	\
    ( (This)->lpVtbl -> GetCategoryForSCID(This,pscid,pguid) ) 

#define ICategoryProvider_EnumCategories(This,penum)	\
    ( (This)->lpVtbl -> EnumCategories(This,penum) ) 

#define ICategoryProvider_GetCategoryName(This,pguid,pszName,cch)	\
    ( (This)->lpVtbl -> GetCategoryName(This,pguid,pszName,cch) ) 

#define ICategoryProvider_CreateCategory(This,pguid,riid,ppv)	\
    ( (This)->lpVtbl -> CreateCategory(This,pguid,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategoryProvider_CanCategorizeOnSCID_Proxy( 
    ICategoryProvider * This,
    SHCOLUMNID *pscid);


void __RPC_STUB ICategoryProvider_CanCategorizeOnSCID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategoryProvider_GetDefaultCategory_Proxy( 
    ICategoryProvider * This,
    GUID *pguid,
    SHCOLUMNID *pscid);


void __RPC_STUB ICategoryProvider_GetDefaultCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategoryProvider_GetCategoryForSCID_Proxy( 
    ICategoryProvider * This,
    SHCOLUMNID *pscid,
    GUID *pguid);


void __RPC_STUB ICategoryProvider_GetCategoryForSCID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategoryProvider_EnumCategories_Proxy( 
    ICategoryProvider * This,
    IEnumGUID **penum);


void __RPC_STUB ICategoryProvider_EnumCategories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategoryProvider_GetCategoryName_Proxy( 
    ICategoryProvider * This,
    GUID *pguid,
    LPWSTR pszName,
    UINT cch);


void __RPC_STUB ICategoryProvider_GetCategoryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategoryProvider_CreateCategory_Proxy( 
    ICategoryProvider * This,
    GUID *pguid,
    REFIID riid,
    /* [iid_is] */ void **ppv);


void __RPC_STUB ICategoryProvider_CreateCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICategoryProvider_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0243 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagCATEGORYINFO_FLAGS
    {	CATINFO_NORMAL	= 0,
	CATINFO_COLLAPSED	= 0x1,
	CATINFO_HIDDEN	= 0x2,
	CATINFO_EXPANDED	= 0x3,
	CATINFO_NOHEADER	= 0x4
    } 	CATEGORYINFO_FLAGS;

typedef /* [v1_enum] */ 
enum tagCATSORT_FLAGS
    {	CATSORT_DEFAULT	= 0,
	CATSORT_NAME	= 0x1
    } 	CATSORT_FLAGS;

typedef struct tagCATEGORY_INFO
    {
    CATEGORYINFO_FLAGS cif;
    WCHAR wszName[ 260 ];
    } 	CATEGORY_INFO;

#include <pshpack8.h>
typedef struct tagSHDRAGIMAGE
    {
    SIZE sizeDragImage;
    POINT ptOffset;
    HBITMAP hbmpDragImage;
    COLORREF crColorKey;
    } 	SHDRAGIMAGE;

typedef struct tagSHDRAGIMAGE *LPSHDRAGIMAGE;

#include <poppack.h> // Return to byte packing
#define DI_GETDRAGIMAGE     TEXT("ShellGetDragImage")


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0243_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0243_v0_0_s_ifspec;

#ifndef __IDropTargetHelper_INTERFACE_DEFINED__
#define __IDropTargetHelper_INTERFACE_DEFINED__

/* interface IDropTargetHelper */
/* [object][unique][local][uuid] */ 


EXTERN_C const IID IID_IDropTargetHelper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4657278B-411B-11D2-839A-00C04FD918D0")
    IDropTargetHelper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DragEnter( 
            /* [in] */ HWND hwndTarget,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ POINT *ppt,
            /* [in] */ DWORD dwEffect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragLeave( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragOver( 
            /* [in] */ POINT *ppt,
            /* [in] */ DWORD dwEffect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Drop( 
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ POINT *ppt,
            DWORD dwEffect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ BOOL fShow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDropTargetHelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDropTargetHelper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDropTargetHelper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDropTargetHelper * This);
        
        HRESULT ( STDMETHODCALLTYPE *DragEnter )( 
            IDropTargetHelper * This,
            /* [in] */ HWND hwndTarget,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ POINT *ppt,
            /* [in] */ DWORD dwEffect);
        
        HRESULT ( STDMETHODCALLTYPE *DragLeave )( 
            IDropTargetHelper * This);
        
        HRESULT ( STDMETHODCALLTYPE *DragOver )( 
            IDropTargetHelper * This,
            /* [in] */ POINT *ppt,
            /* [in] */ DWORD dwEffect);
        
        HRESULT ( STDMETHODCALLTYPE *Drop )( 
            IDropTargetHelper * This,
            /* [in] */ IDataObject *pDataObject,
            /* [in] */ POINT *ppt,
            DWORD dwEffect);
        
        HRESULT ( STDMETHODCALLTYPE *Show )( 
            IDropTargetHelper * This,
            /* [in] */ BOOL fShow);
        
        END_INTERFACE
    } IDropTargetHelperVtbl;

    interface IDropTargetHelper
    {
        CONST_VTBL struct IDropTargetHelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDropTargetHelper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDropTargetHelper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDropTargetHelper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDropTargetHelper_DragEnter(This,hwndTarget,pDataObject,ppt,dwEffect)	\
    ( (This)->lpVtbl -> DragEnter(This,hwndTarget,pDataObject,ppt,dwEffect) ) 

#define IDropTargetHelper_DragLeave(This)	\
    ( (This)->lpVtbl -> DragLeave(This) ) 

#define IDropTargetHelper_DragOver(This,ppt,dwEffect)	\
    ( (This)->lpVtbl -> DragOver(This,ppt,dwEffect) ) 

#define IDropTargetHelper_Drop(This,pDataObject,ppt,dwEffect)	\
    ( (This)->lpVtbl -> Drop(This,pDataObject,ppt,dwEffect) ) 

#define IDropTargetHelper_Show(This,fShow)	\
    ( (This)->lpVtbl -> Show(This,fShow) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDropTargetHelper_DragEnter_Proxy( 
    IDropTargetHelper * This,
    /* [in] */ HWND hwndTarget,
    /* [in] */ IDataObject *pDataObject,
    /* [in] */ POINT *ppt,
    /* [in] */ DWORD dwEffect);


void __RPC_STUB IDropTargetHelper_DragEnter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDropTargetHelper_DragLeave_Proxy( 
    IDropTargetHelper * This);


void __RPC_STUB IDropTargetHelper_DragLeave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDropTargetHelper_DragOver_Proxy( 
    IDropTargetHelper * This,
    /* [in] */ POINT *ppt,
    /* [in] */ DWORD dwEffect);


void __RPC_STUB IDropTargetHelper_DragOver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDropTargetHelper_Drop_Proxy( 
    IDropTargetHelper * This,
    /* [in] */ IDataObject *pDataObject,
    /* [in] */ POINT *ppt,
    DWORD dwEffect);


void __RPC_STUB IDropTargetHelper_Drop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDropTargetHelper_Show_Proxy( 
    IDropTargetHelper * This,
    /* [in] */ BOOL fShow);


void __RPC_STUB IDropTargetHelper_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDropTargetHelper_INTERFACE_DEFINED__ */


#ifndef __IDragSourceHelper_INTERFACE_DEFINED__
#define __IDragSourceHelper_INTERFACE_DEFINED__

/* interface IDragSourceHelper */
/* [object][unique][local][uuid] */ 


EXTERN_C const IID IID_IDragSourceHelper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE5BF786-477A-11D2-839D-00C04FD918D0")
    IDragSourceHelper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitializeFromBitmap( 
            /* [in] */ LPSHDRAGIMAGE pshdi,
            /* [in] */ IDataObject *pDataObject) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeFromWindow( 
            /* [in] */ HWND hwnd,
            /* [in] */ POINT *ppt,
            /* [in] */ IDataObject *pDataObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDragSourceHelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDragSourceHelper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDragSourceHelper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDragSourceHelper * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeFromBitmap )( 
            IDragSourceHelper * This,
            /* [in] */ LPSHDRAGIMAGE pshdi,
            /* [in] */ IDataObject *pDataObject);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeFromWindow )( 
            IDragSourceHelper * This,
            /* [in] */ HWND hwnd,
            /* [in] */ POINT *ppt,
            /* [in] */ IDataObject *pDataObject);
        
        END_INTERFACE
    } IDragSourceHelperVtbl;

    interface IDragSourceHelper
    {
        CONST_VTBL struct IDragSourceHelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDragSourceHelper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDragSourceHelper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDragSourceHelper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDragSourceHelper_InitializeFromBitmap(This,pshdi,pDataObject)	\
    ( (This)->lpVtbl -> InitializeFromBitmap(This,pshdi,pDataObject) ) 

#define IDragSourceHelper_InitializeFromWindow(This,hwnd,ppt,pDataObject)	\
    ( (This)->lpVtbl -> InitializeFromWindow(This,hwnd,ppt,pDataObject) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDragSourceHelper_InitializeFromBitmap_Proxy( 
    IDragSourceHelper * This,
    /* [in] */ LPSHDRAGIMAGE pshdi,
    /* [in] */ IDataObject *pDataObject);


void __RPC_STUB IDragSourceHelper_InitializeFromBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDragSourceHelper_InitializeFromWindow_Proxy( 
    IDragSourceHelper * This,
    /* [in] */ HWND hwnd,
    /* [in] */ POINT *ppt,
    /* [in] */ IDataObject *pDataObject);


void __RPC_STUB IDragSourceHelper_InitializeFromWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDragSourceHelper_INTERFACE_DEFINED__ */


#ifndef __ICategorizer_INTERFACE_DEFINED__
#define __ICategorizer_INTERFACE_DEFINED__

/* interface ICategorizer */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_ICategorizer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a3b14589-9174-49a8-89a3-06a1ae2b9ba7")
    ICategorizer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDescription( 
            LPWSTR pszDesc,
            UINT cch) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCategory( 
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [size_is][out][in] */ DWORD *rgCategoryIds) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCategoryInfo( 
            DWORD dwCategoryId,
            CATEGORY_INFO *pci) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CompareCategory( 
            CATSORT_FLAGS csfFlags,
            DWORD dwCategoryId1,
            DWORD dwCategoryId2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICategorizerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICategorizer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICategorizer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICategorizer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDescription )( 
            ICategorizer * This,
            LPWSTR pszDesc,
            UINT cch);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCategory )( 
            ICategorizer * This,
            /* [in] */ UINT cidl,
            /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
            /* [size_is][out][in] */ DWORD *rgCategoryIds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCategoryInfo )( 
            ICategorizer * This,
            DWORD dwCategoryId,
            CATEGORY_INFO *pci);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CompareCategory )( 
            ICategorizer * This,
            CATSORT_FLAGS csfFlags,
            DWORD dwCategoryId1,
            DWORD dwCategoryId2);
        
        END_INTERFACE
    } ICategorizerVtbl;

    interface ICategorizer
    {
        CONST_VTBL struct ICategorizerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICategorizer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICategorizer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICategorizer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICategorizer_GetDescription(This,pszDesc,cch)	\
    ( (This)->lpVtbl -> GetDescription(This,pszDesc,cch) ) 

#define ICategorizer_GetCategory(This,cidl,apidl,rgCategoryIds)	\
    ( (This)->lpVtbl -> GetCategory(This,cidl,apidl,rgCategoryIds) ) 

#define ICategorizer_GetCategoryInfo(This,dwCategoryId,pci)	\
    ( (This)->lpVtbl -> GetCategoryInfo(This,dwCategoryId,pci) ) 

#define ICategorizer_CompareCategory(This,csfFlags,dwCategoryId1,dwCategoryId2)	\
    ( (This)->lpVtbl -> CompareCategory(This,csfFlags,dwCategoryId1,dwCategoryId2) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategorizer_GetDescription_Proxy( 
    ICategorizer * This,
    LPWSTR pszDesc,
    UINT cch);


void __RPC_STUB ICategorizer_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategorizer_GetCategory_Proxy( 
    ICategorizer * This,
    /* [in] */ UINT cidl,
    /* [size_is][in] */ PCUITEMID_CHILD_ARRAY apidl,
    /* [size_is][out][in] */ DWORD *rgCategoryIds);


void __RPC_STUB ICategorizer_GetCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategorizer_GetCategoryInfo_Proxy( 
    ICategorizer * This,
    DWORD dwCategoryId,
    CATEGORY_INFO *pci);


void __RPC_STUB ICategorizer_GetCategoryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICategorizer_CompareCategory_Proxy( 
    ICategorizer * This,
    CATSORT_FLAGS csfFlags,
    DWORD dwCategoryId1,
    DWORD dwCategoryId2);


void __RPC_STUB ICategorizer_CompareCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICategorizer_INTERFACE_DEFINED__ */


#ifndef __IDropTargetFactory_INTERFACE_DEFINED__
#define __IDropTargetFactory_INTERFACE_DEFINED__

/* interface IDropTargetFactory */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IDropTargetFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("504C9F82-0F68-47f4-8F63-083E58C88412")
    IDropTargetFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateDropTarget( 
            /* [in] */ DWORD dwCategoryID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDropTargetFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDropTargetFactory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDropTargetFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDropTargetFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateDropTarget )( 
            IDropTargetFactory * This,
            /* [in] */ DWORD dwCategoryID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IDropTargetFactoryVtbl;

    interface IDropTargetFactory
    {
        CONST_VTBL struct IDropTargetFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDropTargetFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDropTargetFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDropTargetFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDropTargetFactory_CreateDropTarget(This,dwCategoryID,riid,ppv)	\
    ( (This)->lpVtbl -> CreateDropTarget(This,dwCategoryID,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDropTargetFactory_CreateDropTarget_Proxy( 
    IDropTargetFactory * This,
    /* [in] */ DWORD dwCategoryID,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IDropTargetFactory_CreateDropTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDropTargetFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0247 */
/* [local] */ 

#endif // (_WIN32_IE >= 0x0500)
#ifdef UNICODE
#define IShellLink      IShellLinkW
#else
#define IShellLink      IShellLinkA
#endif
typedef 
enum tagSLR_FLAGS
    {	SLR_NO_UI	= 0x1,
	SLR_ANY_MATCH	= 0x2,
	SLR_UPDATE	= 0x4,
	SLR_NOUPDATE	= 0x8,
	SLR_NOSEARCH	= 0x10,
	SLR_NOTRACK	= 0x20,
	SLR_NOLINKINFO	= 0x40,
	SLR_INVOKE_MSI	= 0x80,
	SLR_NO_UI_WITH_MSG_PUMP	= 0x101
    } 	SLR_FLAGS;

typedef 
enum tagSLGP_FLAGS
    {	SLGP_SHORTPATH	= 0x1,
	SLGP_UNCPRIORITY	= 0x2,
	SLGP_RAWPATH	= 0x4,
	SLGP_RELATIVEPRIORITY	= 0x8
    } 	SLGP_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0247_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0247_v0_0_s_ifspec;

#ifndef __IShellLinkA_INTERFACE_DEFINED__
#define __IShellLinkA_INTERFACE_DEFINED__

/* interface IShellLinkA */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellLinkA;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214EE-0000-0000-C000-000000000046")
    IShellLinkA : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPath( 
            /* [size_is][out] */ LPSTR pszFile,
            /* [in] */ int cch,
            /* [full][out][in] */ WIN32_FIND_DATAA *pfd,
            /* [in] */ DWORD fFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIDList( 
            /* [out] */ PIDLIST_ABSOLUTE *ppidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIDList( 
            /* [in] */ PCIDLIST_ABSOLUTE pidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [size_is][out] */ LPSTR pszName,
            /* [in] */ int cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDescription( 
            /* [in] */ LPCSTR pszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkingDirectory( 
            /* [size_is][out] */ LPSTR pszDir,
            /* [in] */ int cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWorkingDirectory( 
            /* [in] */ LPCSTR pszDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetArguments( 
            /* [size_is][out] */ LPSTR pszArgs,
            /* [in] */ int cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetArguments( 
            /* [in] */ LPCSTR pszArgs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHotkey( 
            /* [out] */ WORD *pwHotkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHotkey( 
            /* [in] */ WORD wHotkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShowCmd( 
            /* [out] */ int *piShowCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetShowCmd( 
            /* [in] */ int iShowCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIconLocation( 
            /* [size_is][out] */ LPSTR pszIconPath,
            /* [in] */ int cch,
            /* [out] */ int *piIcon) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIconLocation( 
            /* [in] */ LPCSTR pszIconPath,
            /* [in] */ int iIcon) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRelativePath( 
            /* [in] */ LPCSTR pszPathRel,
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resolve( 
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPath( 
            /* [in] */ LPCSTR pszFile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellLinkAVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellLinkA * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellLinkA * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellLinkA * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPath )( 
            IShellLinkA * This,
            /* [size_is][out] */ LPSTR pszFile,
            /* [in] */ int cch,
            /* [full][out][in] */ WIN32_FIND_DATAA *pfd,
            /* [in] */ DWORD fFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDList )( 
            IShellLinkA * This,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *SetIDList )( 
            IShellLinkA * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetDescription )( 
            IShellLinkA * This,
            /* [size_is][out] */ LPSTR pszName,
            /* [in] */ int cch);
        
        HRESULT ( STDMETHODCALLTYPE *SetDescription )( 
            IShellLinkA * This,
            /* [in] */ LPCSTR pszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetWorkingDirectory )( 
            IShellLinkA * This,
            /* [size_is][out] */ LPSTR pszDir,
            /* [in] */ int cch);
        
        HRESULT ( STDMETHODCALLTYPE *SetWorkingDirectory )( 
            IShellLinkA * This,
            /* [in] */ LPCSTR pszDir);
        
        HRESULT ( STDMETHODCALLTYPE *GetArguments )( 
            IShellLinkA * This,
            /* [size_is][out] */ LPSTR pszArgs,
            /* [in] */ int cch);
        
        HRESULT ( STDMETHODCALLTYPE *SetArguments )( 
            IShellLinkA * This,
            /* [in] */ LPCSTR pszArgs);
        
        HRESULT ( STDMETHODCALLTYPE *GetHotkey )( 
            IShellLinkA * This,
            /* [out] */ WORD *pwHotkey);
        
        HRESULT ( STDMETHODCALLTYPE *SetHotkey )( 
            IShellLinkA * This,
            /* [in] */ WORD wHotkey);
        
        HRESULT ( STDMETHODCALLTYPE *GetShowCmd )( 
            IShellLinkA * This,
            /* [out] */ int *piShowCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SetShowCmd )( 
            IShellLinkA * This,
            /* [in] */ int iShowCmd);
        
        HRESULT ( STDMETHODCALLTYPE *GetIconLocation )( 
            IShellLinkA * This,
            /* [size_is][out] */ LPSTR pszIconPath,
            /* [in] */ int cch,
            /* [out] */ int *piIcon);
        
        HRESULT ( STDMETHODCALLTYPE *SetIconLocation )( 
            IShellLinkA * This,
            /* [in] */ LPCSTR pszIconPath,
            /* [in] */ int iIcon);
        
        HRESULT ( STDMETHODCALLTYPE *SetRelativePath )( 
            IShellLinkA * This,
            /* [in] */ LPCSTR pszPathRel,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *Resolve )( 
            IShellLinkA * This,
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetPath )( 
            IShellLinkA * This,
            /* [in] */ LPCSTR pszFile);
        
        END_INTERFACE
    } IShellLinkAVtbl;

    interface IShellLinkA
    {
        CONST_VTBL struct IShellLinkAVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellLinkA_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellLinkA_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellLinkA_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellLinkA_GetPath(This,pszFile,cch,pfd,fFlags)	\
    ( (This)->lpVtbl -> GetPath(This,pszFile,cch,pfd,fFlags) ) 

#define IShellLinkA_GetIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetIDList(This,ppidl) ) 

#define IShellLinkA_SetIDList(This,pidl)	\
    ( (This)->lpVtbl -> SetIDList(This,pidl) ) 

#define IShellLinkA_GetDescription(This,pszName,cch)	\
    ( (This)->lpVtbl -> GetDescription(This,pszName,cch) ) 

#define IShellLinkA_SetDescription(This,pszName)	\
    ( (This)->lpVtbl -> SetDescription(This,pszName) ) 

#define IShellLinkA_GetWorkingDirectory(This,pszDir,cch)	\
    ( (This)->lpVtbl -> GetWorkingDirectory(This,pszDir,cch) ) 

#define IShellLinkA_SetWorkingDirectory(This,pszDir)	\
    ( (This)->lpVtbl -> SetWorkingDirectory(This,pszDir) ) 

#define IShellLinkA_GetArguments(This,pszArgs,cch)	\
    ( (This)->lpVtbl -> GetArguments(This,pszArgs,cch) ) 

#define IShellLinkA_SetArguments(This,pszArgs)	\
    ( (This)->lpVtbl -> SetArguments(This,pszArgs) ) 

#define IShellLinkA_GetHotkey(This,pwHotkey)	\
    ( (This)->lpVtbl -> GetHotkey(This,pwHotkey) ) 

#define IShellLinkA_SetHotkey(This,wHotkey)	\
    ( (This)->lpVtbl -> SetHotkey(This,wHotkey) ) 

#define IShellLinkA_GetShowCmd(This,piShowCmd)	\
    ( (This)->lpVtbl -> GetShowCmd(This,piShowCmd) ) 

#define IShellLinkA_SetShowCmd(This,iShowCmd)	\
    ( (This)->lpVtbl -> SetShowCmd(This,iShowCmd) ) 

#define IShellLinkA_GetIconLocation(This,pszIconPath,cch,piIcon)	\
    ( (This)->lpVtbl -> GetIconLocation(This,pszIconPath,cch,piIcon) ) 

#define IShellLinkA_SetIconLocation(This,pszIconPath,iIcon)	\
    ( (This)->lpVtbl -> SetIconLocation(This,pszIconPath,iIcon) ) 

#define IShellLinkA_SetRelativePath(This,pszPathRel,dwReserved)	\
    ( (This)->lpVtbl -> SetRelativePath(This,pszPathRel,dwReserved) ) 

#define IShellLinkA_Resolve(This,hwnd,fFlags)	\
    ( (This)->lpVtbl -> Resolve(This,hwnd,fFlags) ) 

#define IShellLinkA_SetPath(This,pszFile)	\
    ( (This)->lpVtbl -> SetPath(This,pszFile) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellLinkA_GetPath_Proxy( 
    IShellLinkA * This,
    /* [size_is][out] */ LPSTR pszFile,
    /* [in] */ int cch,
    /* [full][out][in] */ WIN32_FIND_DATAA *pfd,
    /* [in] */ DWORD fFlags);


void __RPC_STUB IShellLinkA_GetPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetIDList_Proxy( 
    IShellLinkA * This,
    /* [out] */ PIDLIST_ABSOLUTE *ppidl);


void __RPC_STUB IShellLinkA_GetIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetIDList_Proxy( 
    IShellLinkA * This,
    /* [in] */ PCIDLIST_ABSOLUTE pidl);


void __RPC_STUB IShellLinkA_SetIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetDescription_Proxy( 
    IShellLinkA * This,
    /* [size_is][out] */ LPSTR pszName,
    /* [in] */ int cch);


void __RPC_STUB IShellLinkA_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetDescription_Proxy( 
    IShellLinkA * This,
    /* [in] */ LPCSTR pszName);


void __RPC_STUB IShellLinkA_SetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetWorkingDirectory_Proxy( 
    IShellLinkA * This,
    /* [size_is][out] */ LPSTR pszDir,
    /* [in] */ int cch);


void __RPC_STUB IShellLinkA_GetWorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetWorkingDirectory_Proxy( 
    IShellLinkA * This,
    /* [in] */ LPCSTR pszDir);


void __RPC_STUB IShellLinkA_SetWorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetArguments_Proxy( 
    IShellLinkA * This,
    /* [size_is][out] */ LPSTR pszArgs,
    /* [in] */ int cch);


void __RPC_STUB IShellLinkA_GetArguments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetArguments_Proxy( 
    IShellLinkA * This,
    /* [in] */ LPCSTR pszArgs);


void __RPC_STUB IShellLinkA_SetArguments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetHotkey_Proxy( 
    IShellLinkA * This,
    /* [out] */ WORD *pwHotkey);


void __RPC_STUB IShellLinkA_GetHotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetHotkey_Proxy( 
    IShellLinkA * This,
    /* [in] */ WORD wHotkey);


void __RPC_STUB IShellLinkA_SetHotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetShowCmd_Proxy( 
    IShellLinkA * This,
    /* [out] */ int *piShowCmd);


void __RPC_STUB IShellLinkA_GetShowCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetShowCmd_Proxy( 
    IShellLinkA * This,
    /* [in] */ int iShowCmd);


void __RPC_STUB IShellLinkA_SetShowCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_GetIconLocation_Proxy( 
    IShellLinkA * This,
    /* [size_is][out] */ LPSTR pszIconPath,
    /* [in] */ int cch,
    /* [out] */ int *piIcon);


void __RPC_STUB IShellLinkA_GetIconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetIconLocation_Proxy( 
    IShellLinkA * This,
    /* [in] */ LPCSTR pszIconPath,
    /* [in] */ int iIcon);


void __RPC_STUB IShellLinkA_SetIconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetRelativePath_Proxy( 
    IShellLinkA * This,
    /* [in] */ LPCSTR pszPathRel,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB IShellLinkA_SetRelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_Resolve_Proxy( 
    IShellLinkA * This,
    /* [in] */ HWND hwnd,
    /* [in] */ DWORD fFlags);


void __RPC_STUB IShellLinkA_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkA_SetPath_Proxy( 
    IShellLinkA * This,
    /* [in] */ LPCSTR pszFile);


void __RPC_STUB IShellLinkA_SetPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellLinkA_INTERFACE_DEFINED__ */


#ifndef __IShellLinkW_INTERFACE_DEFINED__
#define __IShellLinkW_INTERFACE_DEFINED__

/* interface IShellLinkW */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IShellLinkW;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214F9-0000-0000-C000-000000000046")
    IShellLinkW : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPath( 
            /* [size_is][out] */ LPWSTR pszFile,
            /* [in] */ int cch,
            /* [full][out][in] */ WIN32_FIND_DATAW *pfd,
            /* [in] */ DWORD fFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIDList( 
            /* [out] */ PIDLIST_ABSOLUTE *ppidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIDList( 
            /* [in] */ PCIDLIST_ABSOLUTE pidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [size_is][out] */ LPWSTR pszName,
            int cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDescription( 
            /* [in] */ LPCWSTR pszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWorkingDirectory( 
            /* [size_is][out] */ LPWSTR pszDir,
            int cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWorkingDirectory( 
            /* [in] */ LPCWSTR pszDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetArguments( 
            /* [size_is][out] */ LPWSTR pszArgs,
            int cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetArguments( 
            /* [in] */ LPCWSTR pszArgs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHotkey( 
            /* [out] */ WORD *pwHotkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHotkey( 
            /* [in] */ WORD wHotkey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShowCmd( 
            /* [out] */ int *piShowCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetShowCmd( 
            /* [in] */ int iShowCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIconLocation( 
            /* [size_is][out] */ LPWSTR pszIconPath,
            /* [in] */ int cch,
            /* [out] */ int *piIcon) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIconLocation( 
            /* [in] */ LPCWSTR pszIconPath,
            /* [in] */ int iIcon) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRelativePath( 
            /* [in] */ LPCWSTR pszPathRel,
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resolve( 
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPath( 
            /* [in] */ LPCWSTR pszFile) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellLinkWVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellLinkW * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellLinkW * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellLinkW * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPath )( 
            IShellLinkW * This,
            /* [size_is][out] */ LPWSTR pszFile,
            /* [in] */ int cch,
            /* [full][out][in] */ WIN32_FIND_DATAW *pfd,
            /* [in] */ DWORD fFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDList )( 
            IShellLinkW * This,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *SetIDList )( 
            IShellLinkW * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetDescription )( 
            IShellLinkW * This,
            /* [size_is][out] */ LPWSTR pszName,
            int cch);
        
        HRESULT ( STDMETHODCALLTYPE *SetDescription )( 
            IShellLinkW * This,
            /* [in] */ LPCWSTR pszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetWorkingDirectory )( 
            IShellLinkW * This,
            /* [size_is][out] */ LPWSTR pszDir,
            int cch);
        
        HRESULT ( STDMETHODCALLTYPE *SetWorkingDirectory )( 
            IShellLinkW * This,
            /* [in] */ LPCWSTR pszDir);
        
        HRESULT ( STDMETHODCALLTYPE *GetArguments )( 
            IShellLinkW * This,
            /* [size_is][out] */ LPWSTR pszArgs,
            int cch);
        
        HRESULT ( STDMETHODCALLTYPE *SetArguments )( 
            IShellLinkW * This,
            /* [in] */ LPCWSTR pszArgs);
        
        HRESULT ( STDMETHODCALLTYPE *GetHotkey )( 
            IShellLinkW * This,
            /* [out] */ WORD *pwHotkey);
        
        HRESULT ( STDMETHODCALLTYPE *SetHotkey )( 
            IShellLinkW * This,
            /* [in] */ WORD wHotkey);
        
        HRESULT ( STDMETHODCALLTYPE *GetShowCmd )( 
            IShellLinkW * This,
            /* [out] */ int *piShowCmd);
        
        HRESULT ( STDMETHODCALLTYPE *SetShowCmd )( 
            IShellLinkW * This,
            /* [in] */ int iShowCmd);
        
        HRESULT ( STDMETHODCALLTYPE *GetIconLocation )( 
            IShellLinkW * This,
            /* [size_is][out] */ LPWSTR pszIconPath,
            /* [in] */ int cch,
            /* [out] */ int *piIcon);
        
        HRESULT ( STDMETHODCALLTYPE *SetIconLocation )( 
            IShellLinkW * This,
            /* [in] */ LPCWSTR pszIconPath,
            /* [in] */ int iIcon);
        
        HRESULT ( STDMETHODCALLTYPE *SetRelativePath )( 
            IShellLinkW * This,
            /* [in] */ LPCWSTR pszPathRel,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *Resolve )( 
            IShellLinkW * This,
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetPath )( 
            IShellLinkW * This,
            /* [in] */ LPCWSTR pszFile);
        
        END_INTERFACE
    } IShellLinkWVtbl;

    interface IShellLinkW
    {
        CONST_VTBL struct IShellLinkWVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellLinkW_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellLinkW_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellLinkW_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellLinkW_GetPath(This,pszFile,cch,pfd,fFlags)	\
    ( (This)->lpVtbl -> GetPath(This,pszFile,cch,pfd,fFlags) ) 

#define IShellLinkW_GetIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetIDList(This,ppidl) ) 

#define IShellLinkW_SetIDList(This,pidl)	\
    ( (This)->lpVtbl -> SetIDList(This,pidl) ) 

#define IShellLinkW_GetDescription(This,pszName,cch)	\
    ( (This)->lpVtbl -> GetDescription(This,pszName,cch) ) 

#define IShellLinkW_SetDescription(This,pszName)	\
    ( (This)->lpVtbl -> SetDescription(This,pszName) ) 

#define IShellLinkW_GetWorkingDirectory(This,pszDir,cch)	\
    ( (This)->lpVtbl -> GetWorkingDirectory(This,pszDir,cch) ) 

#define IShellLinkW_SetWorkingDirectory(This,pszDir)	\
    ( (This)->lpVtbl -> SetWorkingDirectory(This,pszDir) ) 

#define IShellLinkW_GetArguments(This,pszArgs,cch)	\
    ( (This)->lpVtbl -> GetArguments(This,pszArgs,cch) ) 

#define IShellLinkW_SetArguments(This,pszArgs)	\
    ( (This)->lpVtbl -> SetArguments(This,pszArgs) ) 

#define IShellLinkW_GetHotkey(This,pwHotkey)	\
    ( (This)->lpVtbl -> GetHotkey(This,pwHotkey) ) 

#define IShellLinkW_SetHotkey(This,wHotkey)	\
    ( (This)->lpVtbl -> SetHotkey(This,wHotkey) ) 

#define IShellLinkW_GetShowCmd(This,piShowCmd)	\
    ( (This)->lpVtbl -> GetShowCmd(This,piShowCmd) ) 

#define IShellLinkW_SetShowCmd(This,iShowCmd)	\
    ( (This)->lpVtbl -> SetShowCmd(This,iShowCmd) ) 

#define IShellLinkW_GetIconLocation(This,pszIconPath,cch,piIcon)	\
    ( (This)->lpVtbl -> GetIconLocation(This,pszIconPath,cch,piIcon) ) 

#define IShellLinkW_SetIconLocation(This,pszIconPath,iIcon)	\
    ( (This)->lpVtbl -> SetIconLocation(This,pszIconPath,iIcon) ) 

#define IShellLinkW_SetRelativePath(This,pszPathRel,dwReserved)	\
    ( (This)->lpVtbl -> SetRelativePath(This,pszPathRel,dwReserved) ) 

#define IShellLinkW_Resolve(This,hwnd,fFlags)	\
    ( (This)->lpVtbl -> Resolve(This,hwnd,fFlags) ) 

#define IShellLinkW_SetPath(This,pszFile)	\
    ( (This)->lpVtbl -> SetPath(This,pszFile) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellLinkW_GetPath_Proxy( 
    IShellLinkW * This,
    /* [size_is][out] */ LPWSTR pszFile,
    /* [in] */ int cch,
    /* [full][out][in] */ WIN32_FIND_DATAW *pfd,
    /* [in] */ DWORD fFlags);


void __RPC_STUB IShellLinkW_GetPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetIDList_Proxy( 
    IShellLinkW * This,
    /* [out] */ PIDLIST_ABSOLUTE *ppidl);


void __RPC_STUB IShellLinkW_GetIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetIDList_Proxy( 
    IShellLinkW * This,
    /* [in] */ PCIDLIST_ABSOLUTE pidl);


void __RPC_STUB IShellLinkW_SetIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetDescription_Proxy( 
    IShellLinkW * This,
    /* [size_is][out] */ LPWSTR pszName,
    int cch);


void __RPC_STUB IShellLinkW_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetDescription_Proxy( 
    IShellLinkW * This,
    /* [in] */ LPCWSTR pszName);


void __RPC_STUB IShellLinkW_SetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetWorkingDirectory_Proxy( 
    IShellLinkW * This,
    /* [size_is][out] */ LPWSTR pszDir,
    int cch);


void __RPC_STUB IShellLinkW_GetWorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetWorkingDirectory_Proxy( 
    IShellLinkW * This,
    /* [in] */ LPCWSTR pszDir);


void __RPC_STUB IShellLinkW_SetWorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetArguments_Proxy( 
    IShellLinkW * This,
    /* [size_is][out] */ LPWSTR pszArgs,
    int cch);


void __RPC_STUB IShellLinkW_GetArguments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetArguments_Proxy( 
    IShellLinkW * This,
    /* [in] */ LPCWSTR pszArgs);


void __RPC_STUB IShellLinkW_SetArguments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetHotkey_Proxy( 
    IShellLinkW * This,
    /* [out] */ WORD *pwHotkey);


void __RPC_STUB IShellLinkW_GetHotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetHotkey_Proxy( 
    IShellLinkW * This,
    /* [in] */ WORD wHotkey);


void __RPC_STUB IShellLinkW_SetHotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetShowCmd_Proxy( 
    IShellLinkW * This,
    /* [out] */ int *piShowCmd);


void __RPC_STUB IShellLinkW_GetShowCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetShowCmd_Proxy( 
    IShellLinkW * This,
    /* [in] */ int iShowCmd);


void __RPC_STUB IShellLinkW_SetShowCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_GetIconLocation_Proxy( 
    IShellLinkW * This,
    /* [size_is][out] */ LPWSTR pszIconPath,
    /* [in] */ int cch,
    /* [out] */ int *piIcon);


void __RPC_STUB IShellLinkW_GetIconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetIconLocation_Proxy( 
    IShellLinkW * This,
    /* [in] */ LPCWSTR pszIconPath,
    /* [in] */ int iIcon);


void __RPC_STUB IShellLinkW_SetIconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetRelativePath_Proxy( 
    IShellLinkW * This,
    /* [in] */ LPCWSTR pszPathRel,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB IShellLinkW_SetRelativePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_Resolve_Proxy( 
    IShellLinkW * This,
    /* [in] */ HWND hwnd,
    /* [in] */ DWORD fFlags);


void __RPC_STUB IShellLinkW_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellLinkW_SetPath_Proxy( 
    IShellLinkW * This,
    /* [in] */ LPCWSTR pszFile);


void __RPC_STUB IShellLinkW_SetPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellLinkW_INTERFACE_DEFINED__ */


#ifndef __IResolveShellLink_INTERFACE_DEFINED__
#define __IResolveShellLink_INTERFACE_DEFINED__

/* interface IResolveShellLink */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IResolveShellLink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5cd52983-9449-11d2-963a-00c04f79adf0")
    IResolveShellLink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResolveShellLink( 
            /* [in] */ IUnknown *punkLink,
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResolveShellLinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResolveShellLink * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResolveShellLink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResolveShellLink * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResolveShellLink )( 
            IResolveShellLink * This,
            /* [in] */ IUnknown *punkLink,
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags);
        
        END_INTERFACE
    } IResolveShellLinkVtbl;

    interface IResolveShellLink
    {
        CONST_VTBL struct IResolveShellLinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResolveShellLink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IResolveShellLink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IResolveShellLink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IResolveShellLink_ResolveShellLink(This,punkLink,hwnd,fFlags)	\
    ( (This)->lpVtbl -> ResolveShellLink(This,punkLink,hwnd,fFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResolveShellLink_ResolveShellLink_Proxy( 
    IResolveShellLink * This,
    /* [in] */ IUnknown *punkLink,
    /* [in] */ HWND hwnd,
    /* [in] */ DWORD fFlags);


void __RPC_STUB IResolveShellLink_ResolveShellLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResolveShellLink_INTERFACE_DEFINED__ */


#ifndef __IResolveShellLink2_INTERFACE_DEFINED__
#define __IResolveShellLink2_INTERFACE_DEFINED__

/* interface IResolveShellLink2 */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IResolveShellLink2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ed266937-99a3-42b7-b7a9-760ad135e537")
    IResolveShellLink2 : public IResolveShellLink
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateShellLink( 
            /* [in] */ IUnknown *punkLink) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResolveShellLink2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IResolveShellLink2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IResolveShellLink2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IResolveShellLink2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResolveShellLink )( 
            IResolveShellLink2 * This,
            /* [in] */ IUnknown *punkLink,
            /* [in] */ HWND hwnd,
            /* [in] */ DWORD fFlags);
        
        HRESULT ( STDMETHODCALLTYPE *CreateShellLink )( 
            IResolveShellLink2 * This,
            /* [in] */ IUnknown *punkLink);
        
        END_INTERFACE
    } IResolveShellLink2Vtbl;

    interface IResolveShellLink2
    {
        CONST_VTBL struct IResolveShellLink2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResolveShellLink2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IResolveShellLink2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IResolveShellLink2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IResolveShellLink2_ResolveShellLink(This,punkLink,hwnd,fFlags)	\
    ( (This)->lpVtbl -> ResolveShellLink(This,punkLink,hwnd,fFlags) ) 


#define IResolveShellLink2_CreateShellLink(This,punkLink)	\
    ( (This)->lpVtbl -> CreateShellLink(This,punkLink) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResolveShellLink2_CreateShellLink_Proxy( 
    IResolveShellLink2 * This,
    /* [in] */ IUnknown *punkLink);


void __RPC_STUB IResolveShellLink2_CreateShellLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResolveShellLink2_INTERFACE_DEFINED__ */


#ifndef __IActionProgressDialog_INTERFACE_DEFINED__
#define __IActionProgressDialog_INTERFACE_DEFINED__

/* interface IActionProgressDialog */
/* [unique][uuid][object] */ 

/* [v1_enum] */ 
enum tagSPINITF
    {	SPINITF_NORMAL	= 0,
	SPINITF_MODAL	= 0x1,
	SPINITF_NOMINIMIZE	= 0x8
    } ;
typedef DWORD SPINITF;


EXTERN_C const IID IID_IActionProgressDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49ff1172-eadc-446d-9285-156453a6431c")
    IActionProgressDialog : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ SPINITF flags,
            /* [string][in] */ LPCWSTR pszTitle,
            /* [string][in] */ LPCWSTR pszCancel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IActionProgressDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IActionProgressDialog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IActionProgressDialog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IActionProgressDialog * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IActionProgressDialog * This,
            /* [in] */ SPINITF flags,
            /* [string][in] */ LPCWSTR pszTitle,
            /* [string][in] */ LPCWSTR pszCancel);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IActionProgressDialog * This);
        
        END_INTERFACE
    } IActionProgressDialogVtbl;

    interface IActionProgressDialog
    {
        CONST_VTBL struct IActionProgressDialogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IActionProgressDialog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IActionProgressDialog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IActionProgressDialog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IActionProgressDialog_Initialize(This,flags,pszTitle,pszCancel)	\
    ( (This)->lpVtbl -> Initialize(This,flags,pszTitle,pszCancel) ) 

#define IActionProgressDialog_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IActionProgressDialog_Initialize_Proxy( 
    IActionProgressDialog * This,
    /* [in] */ SPINITF flags,
    /* [string][in] */ LPCWSTR pszTitle,
    /* [string][in] */ LPCWSTR pszCancel);


void __RPC_STUB IActionProgressDialog_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActionProgressDialog_Stop_Proxy( 
    IActionProgressDialog * This);


void __RPC_STUB IActionProgressDialog_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IActionProgressDialog_INTERFACE_DEFINED__ */


#ifndef __IProgressImage_INTERFACE_DEFINED__
#define __IProgressImage_INTERFACE_DEFINED__

/* interface IProgressImage */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IProgressImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f34bf05d-bda6-479e-b8b2-c07a8770c676")
    IProgressImage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTitleImage( 
            /* [in] */ IShellItem *psi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IProgressImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProgressImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProgressImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProgressImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTitleImage )( 
            IProgressImage * This,
            /* [in] */ IShellItem *psi);
        
        END_INTERFACE
    } IProgressImageVtbl;

    interface IProgressImage
    {
        CONST_VTBL struct IProgressImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProgressImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProgressImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProgressImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProgressImage_SetTitleImage(This,psi)	\
    ( (This)->lpVtbl -> SetTitleImage(This,psi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IProgressImage_SetTitleImage_Proxy( 
    IProgressImage * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB IProgressImage_SetTitleImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IProgressImage_INTERFACE_DEFINED__ */


#ifndef __IHWNotificationHandler_INTERFACE_DEFINED__
#define __IHWNotificationHandler_INTERFACE_DEFINED__

/* interface IHWNotificationHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IHWNotificationHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FFF994E6-E785-11D6-8F9F-00065BBD32BD")
    IHWNotificationHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [string][in] */ LPCWSTR pszParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleNotification( 
            /* [string][in] */ LPCWSTR pszPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHWNotificationHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHWNotificationHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHWNotificationHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHWNotificationHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IHWNotificationHandler * This,
            /* [string][in] */ LPCWSTR pszParams);
        
        HRESULT ( STDMETHODCALLTYPE *HandleNotification )( 
            IHWNotificationHandler * This,
            /* [string][in] */ LPCWSTR pszPath);
        
        END_INTERFACE
    } IHWNotificationHandlerVtbl;

    interface IHWNotificationHandler
    {
        CONST_VTBL struct IHWNotificationHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHWNotificationHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHWNotificationHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHWNotificationHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHWNotificationHandler_Initialize(This,pszParams)	\
    ( (This)->lpVtbl -> Initialize(This,pszParams) ) 

#define IHWNotificationHandler_HandleNotification(This,pszPath)	\
    ( (This)->lpVtbl -> HandleNotification(This,pszPath) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHWNotificationHandler_Initialize_Proxy( 
    IHWNotificationHandler * This,
    /* [string][in] */ LPCWSTR pszParams);


void __RPC_STUB IHWNotificationHandler_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHWNotificationHandler_HandleNotification_Proxy( 
    IHWNotificationHandler * This,
    /* [string][in] */ LPCWSTR pszPath);


void __RPC_STUB IHWNotificationHandler_HandleNotification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHWNotificationHandler_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0254 */
/* [local] */ 

#define PREFERENCEOPTIONS_NEVER              0x00000001
#define PREFERENCEOPTIONS_PERMEDIAONLY       0x00000002
#define PREFERENCEOPTIONS_PERMEDIABYDEFAULT  0x00000004


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0254_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0254_v0_0_s_ifspec;

#ifndef __IHWEventHandler_INTERFACE_DEFINED__
#define __IHWEventHandler_INTERFACE_DEFINED__

/* interface IHWEventHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IHWEventHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1FB73D0-EC3A-4ba2-B512-8CDB9187B6D1")
    IHWEventHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [string][in] */ LPCWSTR pszParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleEvent( 
            /* [string][in] */ LPCWSTR pszDeviceID,
            /* [string][in] */ LPCWSTR pszAltDeviceID,
            /* [string][in] */ LPCWSTR pszEventType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleEventWithContent( 
            /* [string][in] */ LPCWSTR pszDeviceID,
            /* [string][in] */ LPCWSTR pszAltDeviceID,
            /* [string][in] */ LPCWSTR pszEventType,
            /* [string][in] */ LPCWSTR pszContentTypeHandler,
            /* [in] */ IDataObject *pdataobject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHWEventHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHWEventHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHWEventHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHWEventHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IHWEventHandler * This,
            /* [string][in] */ LPCWSTR pszParams);
        
        HRESULT ( STDMETHODCALLTYPE *HandleEvent )( 
            IHWEventHandler * This,
            /* [string][in] */ LPCWSTR pszDeviceID,
            /* [string][in] */ LPCWSTR pszAltDeviceID,
            /* [string][in] */ LPCWSTR pszEventType);
        
        HRESULT ( STDMETHODCALLTYPE *HandleEventWithContent )( 
            IHWEventHandler * This,
            /* [string][in] */ LPCWSTR pszDeviceID,
            /* [string][in] */ LPCWSTR pszAltDeviceID,
            /* [string][in] */ LPCWSTR pszEventType,
            /* [string][in] */ LPCWSTR pszContentTypeHandler,
            /* [in] */ IDataObject *pdataobject);
        
        END_INTERFACE
    } IHWEventHandlerVtbl;

    interface IHWEventHandler
    {
        CONST_VTBL struct IHWEventHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHWEventHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHWEventHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHWEventHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHWEventHandler_Initialize(This,pszParams)	\
    ( (This)->lpVtbl -> Initialize(This,pszParams) ) 

#define IHWEventHandler_HandleEvent(This,pszDeviceID,pszAltDeviceID,pszEventType)	\
    ( (This)->lpVtbl -> HandleEvent(This,pszDeviceID,pszAltDeviceID,pszEventType) ) 

#define IHWEventHandler_HandleEventWithContent(This,pszDeviceID,pszAltDeviceID,pszEventType,pszContentTypeHandler,pdataobject)	\
    ( (This)->lpVtbl -> HandleEventWithContent(This,pszDeviceID,pszAltDeviceID,pszEventType,pszContentTypeHandler,pdataobject) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHWEventHandler_Initialize_Proxy( 
    IHWEventHandler * This,
    /* [string][in] */ LPCWSTR pszParams);


void __RPC_STUB IHWEventHandler_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHWEventHandler_HandleEvent_Proxy( 
    IHWEventHandler * This,
    /* [string][in] */ LPCWSTR pszDeviceID,
    /* [string][in] */ LPCWSTR pszAltDeviceID,
    /* [string][in] */ LPCWSTR pszEventType);


void __RPC_STUB IHWEventHandler_HandleEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHWEventHandler_HandleEventWithContent_Proxy( 
    IHWEventHandler * This,
    /* [string][in] */ LPCWSTR pszDeviceID,
    /* [string][in] */ LPCWSTR pszAltDeviceID,
    /* [string][in] */ LPCWSTR pszEventType,
    /* [string][in] */ LPCWSTR pszContentTypeHandler,
    /* [in] */ IDataObject *pdataobject);


void __RPC_STUB IHWEventHandler_HandleEventWithContent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHWEventHandler_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0255 */
/* [local] */ 

#define ARCONTENT_AUTORUNINF             0x00000002
#define ARCONTENT_AUDIOCD                0x00000004
#define ARCONTENT_DVDMOVIE               0x00000008
#define ARCONTENT_BLANKCD                0x00000010
#define ARCONTENT_BLANKDVD               0x00000020
#define ARCONTENT_UNKNOWNCONTENT         0x00000040
#define ARCONTENT_AUTOPLAYPIX            0x00000080
#define ARCONTENT_AUTOPLAYMUSIC          0x00000100
#define ARCONTENT_AUTOPLAYVIDEO          0x00000200
#define ARCONTENT_VIDEOCDMOVIE           0x00000400
#define ARCONTENT_SUPERVIDEOCDMOVIE      0x00000800
#define ARCONTENT_PORTABLEUSERPROFILE    0x00001000
#define ARCONTENT_DVDAUDIO               0x00002000


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0255_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0255_v0_0_s_ifspec;

#ifndef __IQueryCancelAutoPlay_INTERFACE_DEFINED__
#define __IQueryCancelAutoPlay_INTERFACE_DEFINED__

/* interface IQueryCancelAutoPlay */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IQueryCancelAutoPlay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DDEFE873-6997-4e68-BE26-39B633ADBE12")
    IQueryCancelAutoPlay : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AllowAutoPlay( 
            /* [string][in] */ LPCWSTR pszPath,
            /* [in] */ DWORD dwContentType,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ DWORD dwSerialNumber) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQueryCancelAutoPlayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IQueryCancelAutoPlay * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IQueryCancelAutoPlay * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IQueryCancelAutoPlay * This);
        
        HRESULT ( STDMETHODCALLTYPE *AllowAutoPlay )( 
            IQueryCancelAutoPlay * This,
            /* [string][in] */ LPCWSTR pszPath,
            /* [in] */ DWORD dwContentType,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ DWORD dwSerialNumber);
        
        END_INTERFACE
    } IQueryCancelAutoPlayVtbl;

    interface IQueryCancelAutoPlay
    {
        CONST_VTBL struct IQueryCancelAutoPlayVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQueryCancelAutoPlay_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IQueryCancelAutoPlay_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IQueryCancelAutoPlay_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IQueryCancelAutoPlay_AllowAutoPlay(This,pszPath,dwContentType,pszLabel,dwSerialNumber)	\
    ( (This)->lpVtbl -> AllowAutoPlay(This,pszPath,dwContentType,pszLabel,dwSerialNumber) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IQueryCancelAutoPlay_AllowAutoPlay_Proxy( 
    IQueryCancelAutoPlay * This,
    /* [string][in] */ LPCWSTR pszPath,
    /* [in] */ DWORD dwContentType,
    /* [string][in] */ LPCWSTR pszLabel,
    /* [in] */ DWORD dwSerialNumber);


void __RPC_STUB IQueryCancelAutoPlay_AllowAutoPlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQueryCancelAutoPlay_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0256 */
/* [local] */ 

#define DYNHWHANDLER_SHOW                0x00000001
#define DYNHWHANDLER_DYNAMICACTIONSTRING 0x00000002


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0256_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0256_v0_0_s_ifspec;

#ifndef __IDynamicHWHandler_INTERFACE_DEFINED__
#define __IDynamicHWHandler_INTERFACE_DEFINED__

/* interface IDynamicHWHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDynamicHWHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FFF994DA-E785-11D6-8F9F-00065BBD32BD")
    IDynamicHWHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDynamicInfo( 
            /* [string][in] */ LPCWSTR pszDeviceID,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetActionString( 
            /* [string][out] */ LPWSTR *ppszAction) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDynamicHWHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDynamicHWHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDynamicHWHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDynamicHWHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDynamicInfo )( 
            IDynamicHWHandler * This,
            /* [string][in] */ LPCWSTR pszDeviceID,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetActionString )( 
            IDynamicHWHandler * This,
            /* [string][out] */ LPWSTR *ppszAction);
        
        END_INTERFACE
    } IDynamicHWHandlerVtbl;

    interface IDynamicHWHandler
    {
        CONST_VTBL struct IDynamicHWHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDynamicHWHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDynamicHWHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDynamicHWHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDynamicHWHandler_GetDynamicInfo(This,pszDeviceID,pdwFlags)	\
    ( (This)->lpVtbl -> GetDynamicInfo(This,pszDeviceID,pdwFlags) ) 

#define IDynamicHWHandler_GetActionString(This,ppszAction)	\
    ( (This)->lpVtbl -> GetActionString(This,ppszAction) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDynamicHWHandler_GetDynamicInfo_Proxy( 
    IDynamicHWHandler * This,
    /* [string][in] */ LPCWSTR pszDeviceID,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IDynamicHWHandler_GetDynamicInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDynamicHWHandler_GetActionString_Proxy( 
    IDynamicHWHandler * This,
    /* [string][out] */ LPWSTR *ppszAction);


void __RPC_STUB IDynamicHWHandler_GetActionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDynamicHWHandler_INTERFACE_DEFINED__ */


#ifndef __IActionProgress_INTERFACE_DEFINED__
#define __IActionProgress_INTERFACE_DEFINED__

/* interface IActionProgress */
/* [unique][uuid][object] */ 

/* [v1_enum] */ 
enum tagSPBEGINF
    {	SPBEGINF_NORMAL	= 0,
	SPBEGINF_AUTOTIME	= 0x2,
	SPBEGINF_NOPROGRESSBAR	= 0x10,
	SPBEGINF_MARQUEEPROGRESS	= 0x20,
	SPBEGINF_NOCANCELBUTTON	= 0x40
    } ;
typedef DWORD SPBEGINF;

typedef /* [v1_enum] */ 
enum _SPACTION
    {	SPACTION_NONE	= 0,
	SPACTION_MOVING	= ( SPACTION_NONE + 1 ) ,
	SPACTION_COPYING	= ( SPACTION_MOVING + 1 ) ,
	SPACTION_RECYCLING	= ( SPACTION_COPYING + 1 ) ,
	SPACTION_APPLYINGATTRIBS	= ( SPACTION_RECYCLING + 1 ) ,
	SPACTION_DOWNLOADING	= ( SPACTION_APPLYINGATTRIBS + 1 ) ,
	SPACTION_SEARCHING_INTERNET	= ( SPACTION_DOWNLOADING + 1 ) ,
	SPACTION_CALCULATING	= ( SPACTION_SEARCHING_INTERNET + 1 ) ,
	SPACTION_UPLOADING	= ( SPACTION_CALCULATING + 1 ) ,
	SPACTION_SEARCHING_FILES	= ( SPACTION_UPLOADING + 1 ) ,
	SPACTION_DELETING	= ( SPACTION_SEARCHING_FILES + 1 ) 
    } 	SPACTION;

typedef /* [v1_enum] */ 
enum _SPTEXT
    {	SPTEXT_ACTIONDESCRIPTION	= 1,
	SPTEXT_ACTIONDETAIL	= ( SPTEXT_ACTIONDESCRIPTION + 1 ) 
    } 	SPTEXT;


EXTERN_C const IID IID_IActionProgress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49ff1173-eadc-446d-9285-156453a6431c")
    IActionProgress : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Begin( 
            /* [in] */ SPACTION action,
            /* [in] */ SPBEGINF flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateProgress( 
            /* [in] */ ULONGLONG ulCompleted,
            /* [in] */ ULONGLONG ulTotal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateText( 
            /* [in] */ SPTEXT sptext,
            /* [string][in] */ LPCWSTR pszText,
            /* [in] */ BOOL fMayCompact) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryCancel( 
            /* [out] */ BOOL *pfCancelled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetCancel( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE End( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IActionProgressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IActionProgress * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IActionProgress * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IActionProgress * This);
        
        HRESULT ( STDMETHODCALLTYPE *Begin )( 
            IActionProgress * This,
            /* [in] */ SPACTION action,
            /* [in] */ SPBEGINF flags);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateProgress )( 
            IActionProgress * This,
            /* [in] */ ULONGLONG ulCompleted,
            /* [in] */ ULONGLONG ulTotal);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateText )( 
            IActionProgress * This,
            /* [in] */ SPTEXT sptext,
            /* [string][in] */ LPCWSTR pszText,
            /* [in] */ BOOL fMayCompact);
        
        HRESULT ( STDMETHODCALLTYPE *QueryCancel )( 
            IActionProgress * This,
            /* [out] */ BOOL *pfCancelled);
        
        HRESULT ( STDMETHODCALLTYPE *ResetCancel )( 
            IActionProgress * This);
        
        HRESULT ( STDMETHODCALLTYPE *End )( 
            IActionProgress * This);
        
        END_INTERFACE
    } IActionProgressVtbl;

    interface IActionProgress
    {
        CONST_VTBL struct IActionProgressVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IActionProgress_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IActionProgress_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IActionProgress_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IActionProgress_Begin(This,action,flags)	\
    ( (This)->lpVtbl -> Begin(This,action,flags) ) 

#define IActionProgress_UpdateProgress(This,ulCompleted,ulTotal)	\
    ( (This)->lpVtbl -> UpdateProgress(This,ulCompleted,ulTotal) ) 

#define IActionProgress_UpdateText(This,sptext,pszText,fMayCompact)	\
    ( (This)->lpVtbl -> UpdateText(This,sptext,pszText,fMayCompact) ) 

#define IActionProgress_QueryCancel(This,pfCancelled)	\
    ( (This)->lpVtbl -> QueryCancel(This,pfCancelled) ) 

#define IActionProgress_ResetCancel(This)	\
    ( (This)->lpVtbl -> ResetCancel(This) ) 

#define IActionProgress_End(This)	\
    ( (This)->lpVtbl -> End(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IActionProgress_Begin_Proxy( 
    IActionProgress * This,
    /* [in] */ SPACTION action,
    /* [in] */ SPBEGINF flags);


void __RPC_STUB IActionProgress_Begin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActionProgress_UpdateProgress_Proxy( 
    IActionProgress * This,
    /* [in] */ ULONGLONG ulCompleted,
    /* [in] */ ULONGLONG ulTotal);


void __RPC_STUB IActionProgress_UpdateProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActionProgress_UpdateText_Proxy( 
    IActionProgress * This,
    /* [in] */ SPTEXT sptext,
    /* [string][in] */ LPCWSTR pszText,
    /* [in] */ BOOL fMayCompact);


void __RPC_STUB IActionProgress_UpdateText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActionProgress_QueryCancel_Proxy( 
    IActionProgress * This,
    /* [out] */ BOOL *pfCancelled);


void __RPC_STUB IActionProgress_QueryCancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActionProgress_ResetCancel_Proxy( 
    IActionProgress * This);


void __RPC_STUB IActionProgress_ResetCancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IActionProgress_End_Proxy( 
    IActionProgress * This);


void __RPC_STUB IActionProgress_End_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IActionProgress_INTERFACE_DEFINED__ */


#ifndef __IShellExtInit_INTERFACE_DEFINED__
#define __IShellExtInit_INTERFACE_DEFINED__

/* interface IShellExtInit */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_IShellExtInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214E8-0000-0000-C000-000000000046")
    IShellExtInit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ IDataObject *pdtobj,
            /* [in] */ HKEY hkeyProgID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellExtInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellExtInit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellExtInit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellExtInit * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IShellExtInit * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ IDataObject *pdtobj,
            /* [in] */ HKEY hkeyProgID);
        
        END_INTERFACE
    } IShellExtInitVtbl;

    interface IShellExtInit
    {
        CONST_VTBL struct IShellExtInitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellExtInit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellExtInit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellExtInit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellExtInit_Initialize(This,pidlFolder,pdtobj,hkeyProgID)	\
    ( (This)->lpVtbl -> Initialize(This,pidlFolder,pdtobj,hkeyProgID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellExtInit_Initialize_Proxy( 
    IShellExtInit * This,
    /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
    /* [in] */ IDataObject *pdtobj,
    /* [in] */ HKEY hkeyProgID);


void __RPC_STUB IShellExtInit_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellExtInit_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0259 */
/* [local] */ 

typedef IShellExtInit *LPSHELLEXTINIT;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0259_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0259_v0_0_s_ifspec;

#ifndef __IShellPropSheetExt_INTERFACE_DEFINED__
#define __IShellPropSheetExt_INTERFACE_DEFINED__

/* interface IShellPropSheetExt */
/* [unique][local][object][uuid] */ 


enum tagSHELLPROPSHEETEXTPAGEID
    {	EXPPS_FILETYPES	= 0x1
    } ;
typedef UINT EXPPS;


EXTERN_C const IID IID_IShellPropSheetExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214E9-0000-0000-C000-000000000046")
    IShellPropSheetExt : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddPages( 
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
            /* [in] */ LPARAM lParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplacePage( 
            /* [in] */ EXPPS uPageID,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
            /* [in] */ LPARAM lParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellPropSheetExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellPropSheetExt * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellPropSheetExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellPropSheetExt * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages )( 
            IShellPropSheetExt * This,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
            /* [in] */ LPARAM lParam);
        
        HRESULT ( STDMETHODCALLTYPE *ReplacePage )( 
            IShellPropSheetExt * This,
            /* [in] */ EXPPS uPageID,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
            /* [in] */ LPARAM lParam);
        
        END_INTERFACE
    } IShellPropSheetExtVtbl;

    interface IShellPropSheetExt
    {
        CONST_VTBL struct IShellPropSheetExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellPropSheetExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellPropSheetExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellPropSheetExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellPropSheetExt_AddPages(This,pfnAddPage,lParam)	\
    ( (This)->lpVtbl -> AddPages(This,pfnAddPage,lParam) ) 

#define IShellPropSheetExt_ReplacePage(This,uPageID,pfnReplaceWith,lParam)	\
    ( (This)->lpVtbl -> ReplacePage(This,uPageID,pfnReplaceWith,lParam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellPropSheetExt_AddPages_Proxy( 
    IShellPropSheetExt * This,
    /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IShellPropSheetExt_AddPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellPropSheetExt_ReplacePage_Proxy( 
    IShellPropSheetExt * This,
    /* [in] */ EXPPS uPageID,
    /* [in] */ LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IShellPropSheetExt_ReplacePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellPropSheetExt_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0260 */
/* [local] */ 

typedef IShellPropSheetExt *LPSHELLPROPSHEETEXT;

typedef /* [helpstring] */ 
enum tagPropPageSettings
    {	PS_DEFAULT	= 0,
	PS_DONT_ADD_IF_MANAGED_PROPPAGE_EXISTS	= 0x1
    } 	PAGESETTINGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0260_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0260_v0_0_s_ifspec;

#ifndef __IShellPropSheetExt2_INTERFACE_DEFINED__
#define __IShellPropSheetExt2_INTERFACE_DEFINED__

/* interface IShellPropSheetExt2 */
/* [unique][local][object][uuid] */ 


EXTERN_C const IID IID_IShellPropSheetExt2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("137a39c6-34bf-4f52-a18d-39e951714c37")
    IShellPropSheetExt2 : public IShellPropSheetExt
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddPages2( 
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
            /* [in] */ LPARAM lParam,
            /* [in] */ PAGESETTINGS pagesettings,
            /* [out] */ BOOL *pfHasManagedPropPage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellPropSheetExt2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellPropSheetExt2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellPropSheetExt2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellPropSheetExt2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages )( 
            IShellPropSheetExt2 * This,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
            /* [in] */ LPARAM lParam);
        
        HRESULT ( STDMETHODCALLTYPE *ReplacePage )( 
            IShellPropSheetExt2 * This,
            /* [in] */ EXPPS uPageID,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
            /* [in] */ LPARAM lParam);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages2 )( 
            IShellPropSheetExt2 * This,
            /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
            /* [in] */ LPARAM lParam,
            /* [in] */ PAGESETTINGS pagesettings,
            /* [out] */ BOOL *pfHasManagedPropPage);
        
        END_INTERFACE
    } IShellPropSheetExt2Vtbl;

    interface IShellPropSheetExt2
    {
        CONST_VTBL struct IShellPropSheetExt2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellPropSheetExt2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellPropSheetExt2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellPropSheetExt2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellPropSheetExt2_AddPages(This,pfnAddPage,lParam)	\
    ( (This)->lpVtbl -> AddPages(This,pfnAddPage,lParam) ) 

#define IShellPropSheetExt2_ReplacePage(This,uPageID,pfnReplaceWith,lParam)	\
    ( (This)->lpVtbl -> ReplacePage(This,uPageID,pfnReplaceWith,lParam) ) 


#define IShellPropSheetExt2_AddPages2(This,pfnAddPage,lParam,pagesettings,pfHasManagedPropPage)	\
    ( (This)->lpVtbl -> AddPages2(This,pfnAddPage,lParam,pagesettings,pfHasManagedPropPage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellPropSheetExt2_AddPages2_Proxy( 
    IShellPropSheetExt2 * This,
    /* [in] */ LPFNSVADDPROPSHEETPAGE pfnAddPage,
    /* [in] */ LPARAM lParam,
    /* [in] */ PAGESETTINGS pagesettings,
    /* [out] */ BOOL *pfHasManagedPropPage);


void __RPC_STUB IShellPropSheetExt2_AddPages2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellPropSheetExt2_INTERFACE_DEFINED__ */


#ifndef __IRemoteComputer_INTERFACE_DEFINED__
#define __IRemoteComputer_INTERFACE_DEFINED__

/* interface IRemoteComputer */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IRemoteComputer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000214FE-0000-0000-C000-000000000046")
    IRemoteComputer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ LPCWSTR pszMachine,
            /* [in] */ BOOL bEnumerating) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRemoteComputerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRemoteComputer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRemoteComputer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRemoteComputer * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IRemoteComputer * This,
            /* [in] */ LPCWSTR pszMachine,
            /* [in] */ BOOL bEnumerating);
        
        END_INTERFACE
    } IRemoteComputerVtbl;

    interface IRemoteComputer
    {
        CONST_VTBL struct IRemoteComputerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRemoteComputer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRemoteComputer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRemoteComputer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRemoteComputer_Initialize(This,pszMachine,bEnumerating)	\
    ( (This)->lpVtbl -> Initialize(This,pszMachine,bEnumerating) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRemoteComputer_Initialize_Proxy( 
    IRemoteComputer * This,
    /* [in] */ LPCWSTR pszMachine,
    /* [in] */ BOOL bEnumerating);


void __RPC_STUB IRemoteComputer_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRemoteComputer_INTERFACE_DEFINED__ */


#ifndef __IUserNotification_INTERFACE_DEFINED__
#define __IUserNotification_INTERFACE_DEFINED__

/* interface IUserNotification */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IUserNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ba9711ba-5893-4787-a7e1-41277151550b")
    IUserNotification : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetBalloonInfo( 
            /* [string][in] */ LPCWSTR pszTitle,
            /* [string][in] */ LPCWSTR pszText,
            /* [in] */ DWORD dwInfoFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBalloonRetry( 
            /* [in] */ DWORD dwShowTime,
            /* [in] */ DWORD dwInterval,
            /* [in] */ UINT cRetryCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIconInfo( 
            /* [in] */ HICON hIcon,
            /* [string][in] */ LPCWSTR pszToolTip) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ IQueryContinue *pqc,
            /* [in] */ DWORD dwContinuePollInterval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlaySound( 
            /* [string][in] */ LPCWSTR pszSoundName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUserNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUserNotification * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUserNotification * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUserNotification * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetBalloonInfo )( 
            IUserNotification * This,
            /* [string][in] */ LPCWSTR pszTitle,
            /* [string][in] */ LPCWSTR pszText,
            /* [in] */ DWORD dwInfoFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetBalloonRetry )( 
            IUserNotification * This,
            /* [in] */ DWORD dwShowTime,
            /* [in] */ DWORD dwInterval,
            /* [in] */ UINT cRetryCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetIconInfo )( 
            IUserNotification * This,
            /* [in] */ HICON hIcon,
            /* [string][in] */ LPCWSTR pszToolTip);
        
        HRESULT ( STDMETHODCALLTYPE *Show )( 
            IUserNotification * This,
            /* [in] */ IQueryContinue *pqc,
            /* [in] */ DWORD dwContinuePollInterval);
        
        HRESULT ( STDMETHODCALLTYPE *PlaySound )( 
            IUserNotification * This,
            /* [string][in] */ LPCWSTR pszSoundName);
        
        END_INTERFACE
    } IUserNotificationVtbl;

    interface IUserNotification
    {
        CONST_VTBL struct IUserNotificationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUserNotification_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUserNotification_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUserNotification_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUserNotification_SetBalloonInfo(This,pszTitle,pszText,dwInfoFlags)	\
    ( (This)->lpVtbl -> SetBalloonInfo(This,pszTitle,pszText,dwInfoFlags) ) 

#define IUserNotification_SetBalloonRetry(This,dwShowTime,dwInterval,cRetryCount)	\
    ( (This)->lpVtbl -> SetBalloonRetry(This,dwShowTime,dwInterval,cRetryCount) ) 

#define IUserNotification_SetIconInfo(This,hIcon,pszToolTip)	\
    ( (This)->lpVtbl -> SetIconInfo(This,hIcon,pszToolTip) ) 

#define IUserNotification_Show(This,pqc,dwContinuePollInterval)	\
    ( (This)->lpVtbl -> Show(This,pqc,dwContinuePollInterval) ) 

#define IUserNotification_PlaySound(This,pszSoundName)	\
    ( (This)->lpVtbl -> PlaySound(This,pszSoundName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IUserNotification_SetBalloonInfo_Proxy( 
    IUserNotification * This,
    /* [string][in] */ LPCWSTR pszTitle,
    /* [string][in] */ LPCWSTR pszText,
    /* [in] */ DWORD dwInfoFlags);


void __RPC_STUB IUserNotification_SetBalloonInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUserNotification_SetBalloonRetry_Proxy( 
    IUserNotification * This,
    /* [in] */ DWORD dwShowTime,
    /* [in] */ DWORD dwInterval,
    /* [in] */ UINT cRetryCount);


void __RPC_STUB IUserNotification_SetBalloonRetry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUserNotification_SetIconInfo_Proxy( 
    IUserNotification * This,
    /* [in] */ HICON hIcon,
    /* [string][in] */ LPCWSTR pszToolTip);


void __RPC_STUB IUserNotification_SetIconInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUserNotification_Show_Proxy( 
    IUserNotification * This,
    /* [in] */ IQueryContinue *pqc,
    /* [in] */ DWORD dwContinuePollInterval);


void __RPC_STUB IUserNotification_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUserNotification_PlaySound_Proxy( 
    IUserNotification * This,
    /* [string][in] */ LPCWSTR pszSoundName);


void __RPC_STUB IUserNotification_PlaySound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUserNotification_INTERFACE_DEFINED__ */


#ifndef __IItemNameLimits_INTERFACE_DEFINED__
#define __IItemNameLimits_INTERFACE_DEFINED__

/* interface IItemNameLimits */
/* [object][uuid] */ 


EXTERN_C const IID IID_IItemNameLimits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1df0d7f1-b267-4d28-8b10-12e23202a5c4")
    IItemNameLimits : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetValidCharacters( 
            /* [out] */ LPWSTR *ppwszValidChars,
            /* [out] */ LPWSTR *ppwszInvalidChars) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxLength( 
            /* [in] */ LPCWSTR pszName,
            /* [out] */ int *piMaxNameLen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IItemNameLimitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IItemNameLimits * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IItemNameLimits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IItemNameLimits * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetValidCharacters )( 
            IItemNameLimits * This,
            /* [out] */ LPWSTR *ppwszValidChars,
            /* [out] */ LPWSTR *ppwszInvalidChars);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxLength )( 
            IItemNameLimits * This,
            /* [in] */ LPCWSTR pszName,
            /* [out] */ int *piMaxNameLen);
        
        END_INTERFACE
    } IItemNameLimitsVtbl;

    interface IItemNameLimits
    {
        CONST_VTBL struct IItemNameLimitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IItemNameLimits_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IItemNameLimits_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IItemNameLimits_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IItemNameLimits_GetValidCharacters(This,ppwszValidChars,ppwszInvalidChars)	\
    ( (This)->lpVtbl -> GetValidCharacters(This,ppwszValidChars,ppwszInvalidChars) ) 

#define IItemNameLimits_GetMaxLength(This,pszName,piMaxNameLen)	\
    ( (This)->lpVtbl -> GetMaxLength(This,pszName,piMaxNameLen) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IItemNameLimits_GetValidCharacters_Proxy( 
    IItemNameLimits * This,
    /* [out] */ LPWSTR *ppwszValidChars,
    /* [out] */ LPWSTR *ppwszInvalidChars);


void __RPC_STUB IItemNameLimits_GetValidCharacters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IItemNameLimits_GetMaxLength_Proxy( 
    IItemNameLimits * This,
    /* [in] */ LPCWSTR pszName,
    /* [out] */ int *piMaxNameLen);


void __RPC_STUB IItemNameLimits_GetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IItemNameLimits_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0265 */
/* [local] */ 

#if (_WIN32_IE >= 0x0400)
#define IEI_PRIORITY_MAX        ITSAT_MAX_PRIORITY
#define IEI_PRIORITY_MIN        ITSAT_MIN_PRIORITY
#define IEIT_PRIORITY_NORMAL     ITSAT_DEFAULT_PRIORITY
#define IEIFLAG_ASYNC       0x0001      // ask the extractor if it supports ASYNC extract (free threaded)
#define IEIFLAG_CACHE       0x0002      // returned from the extractor if it does NOT cache the thumbnail
#define IEIFLAG_ASPECT      0x0004      // passed to the extractor to beg it to render to the aspect ratio of the supplied rect
#define IEIFLAG_OFFLINE     0x0008      // if the extractor shouldn't hit the net to get any content neede for the rendering
#define IEIFLAG_GLEAM       0x0010      // does the image have a gleam ? this will be returned if it does
#define IEIFLAG_SCREEN      0x0020      // render as if for the screen  (this is exlusive with IEIFLAG_ASPECT )
#define IEIFLAG_ORIGSIZE    0x0040      // render to the approx size passed, but crop if neccessary
#define IEIFLAG_NOSTAMP     0x0080      // returned from the extractor if it does NOT want an icon stamp on the thumbnail
#define IEIFLAG_NOBORDER    0x0100      // returned from the extractor if it does NOT want an a border around the thumbnail
#define IEIFLAG_QUALITY     0x0200      // passed to the Extract method to indicate that a slower, higher quality image is desired, re-compute the thumbnail
#define IEIFLAG_REFRESH     0x0400      // returned from the extractor if it would like to have Refresh Thumbnail available
#define IEIFLAG_INFOTIP     0x0800      // render the thumbnail for the infotip of the item


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0265_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0265_v0_0_s_ifspec;

#ifndef __IExtractImage_INTERFACE_DEFINED__
#define __IExtractImage_INTERFACE_DEFINED__

/* interface IExtractImage */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IExtractImage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB2E617C-0920-11d1-9A0B-00C04FC2D6C1")
    IExtractImage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLocation( 
            /* [size_is][out] */ LPWSTR pszPathBuffer,
            /* [in] */ DWORD cch,
            /* [unique][out][in] */ DWORD *pdwPriority,
            /* [in] */ const SIZE *prgSize,
            /* [in] */ DWORD dwRecClrDepth,
            /* [out][in] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Extract( 
            /* [out] */ HBITMAP *phBmpThumbnail) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExtractImageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExtractImage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExtractImage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExtractImage * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocation )( 
            IExtractImage * This,
            /* [size_is][out] */ LPWSTR pszPathBuffer,
            /* [in] */ DWORD cch,
            /* [unique][out][in] */ DWORD *pdwPriority,
            /* [in] */ const SIZE *prgSize,
            /* [in] */ DWORD dwRecClrDepth,
            /* [out][in] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Extract )( 
            IExtractImage * This,
            /* [out] */ HBITMAP *phBmpThumbnail);
        
        END_INTERFACE
    } IExtractImageVtbl;

    interface IExtractImage
    {
        CONST_VTBL struct IExtractImageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExtractImage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IExtractImage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IExtractImage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IExtractImage_GetLocation(This,pszPathBuffer,cch,pdwPriority,prgSize,dwRecClrDepth,pdwFlags)	\
    ( (This)->lpVtbl -> GetLocation(This,pszPathBuffer,cch,pdwPriority,prgSize,dwRecClrDepth,pdwFlags) ) 

#define IExtractImage_Extract(This,phBmpThumbnail)	\
    ( (This)->lpVtbl -> Extract(This,phBmpThumbnail) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExtractImage_GetLocation_Proxy( 
    IExtractImage * This,
    /* [size_is][out] */ LPWSTR pszPathBuffer,
    /* [in] */ DWORD cch,
    /* [unique][out][in] */ DWORD *pdwPriority,
    /* [in] */ const SIZE *prgSize,
    /* [in] */ DWORD dwRecClrDepth,
    /* [out][in] */ DWORD *pdwFlags);


void __RPC_STUB IExtractImage_GetLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IExtractImage_Extract_Proxy( 
    IExtractImage * This,
    /* [out] */ HBITMAP *phBmpThumbnail);


void __RPC_STUB IExtractImage_Extract_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExtractImage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0266 */
/* [local] */ 

typedef IExtractImage *LPEXTRACTIMAGE;

#endif
#if (_WIN32_IE >= 0x0500)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0266_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0266_v0_0_s_ifspec;

#ifndef __IExtractImage2_INTERFACE_DEFINED__
#define __IExtractImage2_INTERFACE_DEFINED__

/* interface IExtractImage2 */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IExtractImage2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("953BB1EE-93B4-11d1-98A3-00C04FB687DA")
    IExtractImage2 : public IExtractImage
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDateStamp( 
            /* [out] */ FILETIME *pDateStamp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExtractImage2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExtractImage2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExtractImage2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExtractImage2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocation )( 
            IExtractImage2 * This,
            /* [size_is][out] */ LPWSTR pszPathBuffer,
            /* [in] */ DWORD cch,
            /* [unique][out][in] */ DWORD *pdwPriority,
            /* [in] */ const SIZE *prgSize,
            /* [in] */ DWORD dwRecClrDepth,
            /* [out][in] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Extract )( 
            IExtractImage2 * This,
            /* [out] */ HBITMAP *phBmpThumbnail);
        
        HRESULT ( STDMETHODCALLTYPE *GetDateStamp )( 
            IExtractImage2 * This,
            /* [out] */ FILETIME *pDateStamp);
        
        END_INTERFACE
    } IExtractImage2Vtbl;

    interface IExtractImage2
    {
        CONST_VTBL struct IExtractImage2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExtractImage2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IExtractImage2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IExtractImage2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IExtractImage2_GetLocation(This,pszPathBuffer,cch,pdwPriority,prgSize,dwRecClrDepth,pdwFlags)	\
    ( (This)->lpVtbl -> GetLocation(This,pszPathBuffer,cch,pdwPriority,prgSize,dwRecClrDepth,pdwFlags) ) 

#define IExtractImage2_Extract(This,phBmpThumbnail)	\
    ( (This)->lpVtbl -> Extract(This,phBmpThumbnail) ) 


#define IExtractImage2_GetDateStamp(This,pDateStamp)	\
    ( (This)->lpVtbl -> GetDateStamp(This,pDateStamp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IExtractImage2_GetDateStamp_Proxy( 
    IExtractImage2 * This,
    /* [out] */ FILETIME *pDateStamp);


void __RPC_STUB IExtractImage2_GetDateStamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExtractImage2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0267 */
/* [local] */ 

typedef IExtractImage2 *LPEXTRACTIMAGE2;

#endif


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0267_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0267_v0_0_s_ifspec;

#ifndef __IDockingWindow_INTERFACE_DEFINED__
#define __IDockingWindow_INTERFACE_DEFINED__

/* interface IDockingWindow */
/* [object][uuid] */ 


EXTERN_C const IID IID_IDockingWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("012dd920-7b26-11d0-8ca9-00a0c92dbfe8")
    IDockingWindow : public IOleWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShowDW( 
            /* [in] */ BOOL fShow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseDW( 
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBorderDW( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IUnknown *punkToolbarSite,
            /* [in] */ BOOL fReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDockingWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDockingWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDockingWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDockingWindow * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IDockingWindow * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IDockingWindow * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *ShowDW )( 
            IDockingWindow * This,
            /* [in] */ BOOL fShow);
        
        HRESULT ( STDMETHODCALLTYPE *CloseDW )( 
            IDockingWindow * This,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeBorderDW )( 
            IDockingWindow * This,
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IUnknown *punkToolbarSite,
            /* [in] */ BOOL fReserved);
        
        END_INTERFACE
    } IDockingWindowVtbl;

    interface IDockingWindow
    {
        CONST_VTBL struct IDockingWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDockingWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDockingWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDockingWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDockingWindow_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IDockingWindow_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IDockingWindow_ShowDW(This,fShow)	\
    ( (This)->lpVtbl -> ShowDW(This,fShow) ) 

#define IDockingWindow_CloseDW(This,dwReserved)	\
    ( (This)->lpVtbl -> CloseDW(This,dwReserved) ) 

#define IDockingWindow_ResizeBorderDW(This,prcBorder,punkToolbarSite,fReserved)	\
    ( (This)->lpVtbl -> ResizeBorderDW(This,prcBorder,punkToolbarSite,fReserved) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDockingWindow_ShowDW_Proxy( 
    IDockingWindow * This,
    /* [in] */ BOOL fShow);


void __RPC_STUB IDockingWindow_ShowDW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDockingWindow_CloseDW_Proxy( 
    IDockingWindow * This,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB IDockingWindow_CloseDW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDockingWindow_ResizeBorderDW_Proxy( 
    IDockingWindow * This,
    /* [in] */ LPCRECT prcBorder,
    /* [in] */ IUnknown *punkToolbarSite,
    /* [in] */ BOOL fReserved);


void __RPC_STUB IDockingWindow_ResizeBorderDW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDockingWindow_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0268 */
/* [local] */ 

#define DBIM_MINSIZE    0x0001
#define DBIM_MAXSIZE    0x0002
#define DBIM_INTEGRAL   0x0004
#define DBIM_ACTUAL     0x0008
#define DBIM_TITLE      0x0010
#define DBIM_MODEFLAGS  0x0020
#define DBIM_BKCOLOR    0x0040
#include <pshpack8.h>
typedef struct tagDESKBANDINFO
    {
    DWORD dwMask;
    POINTL ptMinSize;
    POINTL ptMaxSize;
    POINTL ptIntegral;
    POINTL ptActual;
    WCHAR wszTitle[ 256 ];
    DWORD dwModeFlags;
    COLORREF crBkgnd;
    } 	DESKBANDINFO;

#include <poppack.h>
#define DBIMF_NORMAL            0x0000
#define DBIMF_FIXED             0x0001
#define DBIMF_FIXEDBMP          0x0004   // a fixed background bitmap (if supported)
#define DBIMF_VARIABLEHEIGHT    0x0008
#define DBIMF_UNDELETEABLE      0x0010
#define DBIMF_DEBOSSED          0x0020
#define DBIMF_BKCOLOR           0x0040
#define DBIMF_USECHEVRON        0x0080
#define DBIMF_BREAK             0x0100
#define DBIMF_ADDTOFRONT        0x0200
#define DBIMF_TOPALIGN          0x0400
#define DBIMF_NOGRIPPER         0x0800
#define DBIMF_ALWAYSGRIPPER     0x1000
#define DBIF_VIEWMODE_NORMAL         0x0000
#define DBIF_VIEWMODE_VERTICAL       0x0001
#define DBIF_VIEWMODE_FLOATING       0x0002
#define DBIF_VIEWMODE_TRANSPARENT    0x0004

enum tagDESKBANDCID
    {	DBID_BANDINFOCHANGED	= 0,
	DBID_SHOWONLY	= 1,
	DBID_MAXIMIZEBAND	= 2,
	DBID_PUSHCHEVRON	= 3,
	DBID_DELAYINIT	= 4,
	DBID_FINISHINIT	= 5,
	DBID_SETWINDOWTHEME	= 6,
	DBID_PERMITAUTOHIDE	= 7
    } ;
#define DBPC_SELECTFIRST    (DWORD)-1
#define DBPC_SELECTLAST     (DWORD)-2
#define CGID_DeskBand IID_IDeskBand


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0268_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0268_v0_0_s_ifspec;

#ifndef __IDeskBand_INTERFACE_DEFINED__
#define __IDeskBand_INTERFACE_DEFINED__

/* interface IDeskBand */
/* [object][uuid] */ 


EXTERN_C const IID IID_IDeskBand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB0FE172-1A3A-11D0-89B3-00A0C90A90AC")
    IDeskBand : public IDockingWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetBandInfo( 
            /* [in] */ DWORD dwBandID,
            /* [in] */ DWORD dwViewMode,
            /* [out][in] */ DESKBANDINFO *pdbi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDeskBandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeskBand * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeskBand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeskBand * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IDeskBand * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IDeskBand * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *ShowDW )( 
            IDeskBand * This,
            /* [in] */ BOOL fShow);
        
        HRESULT ( STDMETHODCALLTYPE *CloseDW )( 
            IDeskBand * This,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *ResizeBorderDW )( 
            IDeskBand * This,
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IUnknown *punkToolbarSite,
            /* [in] */ BOOL fReserved);
        
        HRESULT ( STDMETHODCALLTYPE *GetBandInfo )( 
            IDeskBand * This,
            /* [in] */ DWORD dwBandID,
            /* [in] */ DWORD dwViewMode,
            /* [out][in] */ DESKBANDINFO *pdbi);
        
        END_INTERFACE
    } IDeskBandVtbl;

    interface IDeskBand
    {
        CONST_VTBL struct IDeskBandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeskBand_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeskBand_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeskBand_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeskBand_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IDeskBand_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IDeskBand_ShowDW(This,fShow)	\
    ( (This)->lpVtbl -> ShowDW(This,fShow) ) 

#define IDeskBand_CloseDW(This,dwReserved)	\
    ( (This)->lpVtbl -> CloseDW(This,dwReserved) ) 

#define IDeskBand_ResizeBorderDW(This,prcBorder,punkToolbarSite,fReserved)	\
    ( (This)->lpVtbl -> ResizeBorderDW(This,prcBorder,punkToolbarSite,fReserved) ) 


#define IDeskBand_GetBandInfo(This,dwBandID,dwViewMode,pdbi)	\
    ( (This)->lpVtbl -> GetBandInfo(This,dwBandID,dwViewMode,pdbi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDeskBand_GetBandInfo_Proxy( 
    IDeskBand * This,
    /* [in] */ DWORD dwBandID,
    /* [in] */ DWORD dwViewMode,
    /* [out][in] */ DESKBANDINFO *pdbi);


void __RPC_STUB IDeskBand_GetBandInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDeskBand_INTERFACE_DEFINED__ */


#ifndef __ITaskbarList_INTERFACE_DEFINED__
#define __ITaskbarList_INTERFACE_DEFINED__

/* interface ITaskbarList */
/* [object][uuid] */ 


EXTERN_C const IID IID_ITaskbarList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56FDF342-FD6D-11d0-958A-006097C9A090")
    ITaskbarList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HrInit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddTab( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteTab( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ActivateTab( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetActiveAlt( 
            /* [in] */ HWND hwnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITaskbarListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITaskbarList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITaskbarList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITaskbarList * This);
        
        HRESULT ( STDMETHODCALLTYPE *HrInit )( 
            ITaskbarList * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddTab )( 
            ITaskbarList * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteTab )( 
            ITaskbarList * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateTab )( 
            ITaskbarList * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( 
            ITaskbarList * This,
            /* [in] */ HWND hwnd);
        
        END_INTERFACE
    } ITaskbarListVtbl;

    interface ITaskbarList
    {
        CONST_VTBL struct ITaskbarListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITaskbarList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITaskbarList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITaskbarList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITaskbarList_HrInit(This)	\
    ( (This)->lpVtbl -> HrInit(This) ) 

#define ITaskbarList_AddTab(This,hwnd)	\
    ( (This)->lpVtbl -> AddTab(This,hwnd) ) 

#define ITaskbarList_DeleteTab(This,hwnd)	\
    ( (This)->lpVtbl -> DeleteTab(This,hwnd) ) 

#define ITaskbarList_ActivateTab(This,hwnd)	\
    ( (This)->lpVtbl -> ActivateTab(This,hwnd) ) 

#define ITaskbarList_SetActiveAlt(This,hwnd)	\
    ( (This)->lpVtbl -> SetActiveAlt(This,hwnd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITaskbarList_HrInit_Proxy( 
    ITaskbarList * This);


void __RPC_STUB ITaskbarList_HrInit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskbarList_AddTab_Proxy( 
    ITaskbarList * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB ITaskbarList_AddTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskbarList_DeleteTab_Proxy( 
    ITaskbarList * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB ITaskbarList_DeleteTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskbarList_ActivateTab_Proxy( 
    ITaskbarList * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB ITaskbarList_ActivateTab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITaskbarList_SetActiveAlt_Proxy( 
    ITaskbarList * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB ITaskbarList_SetActiveAlt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITaskbarList_INTERFACE_DEFINED__ */


#ifndef __ITaskbarList2_INTERFACE_DEFINED__
#define __ITaskbarList2_INTERFACE_DEFINED__

/* interface ITaskbarList2 */
/* [object][uuid] */ 


EXTERN_C const IID IID_ITaskbarList2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("602D4995-B13A-429b-A66E-1935E44F4317")
    ITaskbarList2 : public ITaskbarList
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MarkFullscreenWindow( 
            /* [in] */ HWND hwnd,
            /* [in] */ BOOL fFullscreen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITaskbarList2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITaskbarList2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITaskbarList2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITaskbarList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *HrInit )( 
            ITaskbarList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddTab )( 
            ITaskbarList2 * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteTab )( 
            ITaskbarList2 * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ActivateTab )( 
            ITaskbarList2 * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *SetActiveAlt )( 
            ITaskbarList2 * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *MarkFullscreenWindow )( 
            ITaskbarList2 * This,
            /* [in] */ HWND hwnd,
            /* [in] */ BOOL fFullscreen);
        
        END_INTERFACE
    } ITaskbarList2Vtbl;

    interface ITaskbarList2
    {
        CONST_VTBL struct ITaskbarList2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITaskbarList2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITaskbarList2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITaskbarList2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITaskbarList2_HrInit(This)	\
    ( (This)->lpVtbl -> HrInit(This) ) 

#define ITaskbarList2_AddTab(This,hwnd)	\
    ( (This)->lpVtbl -> AddTab(This,hwnd) ) 

#define ITaskbarList2_DeleteTab(This,hwnd)	\
    ( (This)->lpVtbl -> DeleteTab(This,hwnd) ) 

#define ITaskbarList2_ActivateTab(This,hwnd)	\
    ( (This)->lpVtbl -> ActivateTab(This,hwnd) ) 

#define ITaskbarList2_SetActiveAlt(This,hwnd)	\
    ( (This)->lpVtbl -> SetActiveAlt(This,hwnd) ) 


#define ITaskbarList2_MarkFullscreenWindow(This,hwnd,fFullscreen)	\
    ( (This)->lpVtbl -> MarkFullscreenWindow(This,hwnd,fFullscreen) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITaskbarList2_MarkFullscreenWindow_Proxy( 
    ITaskbarList2 * This,
    /* [in] */ HWND hwnd,
    /* [in] */ BOOL fFullscreen);


void __RPC_STUB ITaskbarList2_MarkFullscreenWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITaskbarList2_INTERFACE_DEFINED__ */


#ifndef __ICDBurn_INTERFACE_DEFINED__
#define __ICDBurn_INTERFACE_DEFINED__

/* interface ICDBurn */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICDBurn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3d73a659-e5d0-4d42-afc0-5121ba425c8d")
    ICDBurn : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRecorderDriveLetter( 
            /* [size_is][out] */ LPWSTR pszDrive,
            /* [in] */ UINT cch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Burn( 
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HasRecordableDrive( 
            /* [out] */ BOOL *pfHasRecorder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICDBurnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICDBurn * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICDBurn * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICDBurn * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetRecorderDriveLetter )( 
            ICDBurn * This,
            /* [size_is][out] */ LPWSTR pszDrive,
            /* [in] */ UINT cch);
        
        HRESULT ( STDMETHODCALLTYPE *Burn )( 
            ICDBurn * This,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE *HasRecordableDrive )( 
            ICDBurn * This,
            /* [out] */ BOOL *pfHasRecorder);
        
        END_INTERFACE
    } ICDBurnVtbl;

    interface ICDBurn
    {
        CONST_VTBL struct ICDBurnVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICDBurn_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICDBurn_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICDBurn_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICDBurn_GetRecorderDriveLetter(This,pszDrive,cch)	\
    ( (This)->lpVtbl -> GetRecorderDriveLetter(This,pszDrive,cch) ) 

#define ICDBurn_Burn(This,hwnd)	\
    ( (This)->lpVtbl -> Burn(This,hwnd) ) 

#define ICDBurn_HasRecordableDrive(This,pfHasRecorder)	\
    ( (This)->lpVtbl -> HasRecordableDrive(This,pfHasRecorder) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICDBurn_GetRecorderDriveLetter_Proxy( 
    ICDBurn * This,
    /* [size_is][out] */ LPWSTR pszDrive,
    /* [in] */ UINT cch);


void __RPC_STUB ICDBurn_GetRecorderDriveLetter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICDBurn_Burn_Proxy( 
    ICDBurn * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB ICDBurn_Burn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICDBurn_HasRecordableDrive_Proxy( 
    ICDBurn * This,
    /* [out] */ BOOL *pfHasRecorder);


void __RPC_STUB ICDBurn_HasRecordableDrive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICDBurn_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0272 */
/* [local] */ 

#define IDD_WIZEXTN_FIRST    0x5000
#define IDD_WIZEXTN_LAST     0x5100


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0272_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0272_v0_0_s_ifspec;

#ifndef __IWizardSite_INTERFACE_DEFINED__
#define __IWizardSite_INTERFACE_DEFINED__

/* interface IWizardSite */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IWizardSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88960f5b-422f-4e7b-8013-73415381c3c3")
    IWizardSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPreviousPage( 
            /* [out] */ HPROPSHEETPAGE *phpage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNextPage( 
            /* [out] */ HPROPSHEETPAGE *phpage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCancelledPage( 
            /* [out] */ HPROPSHEETPAGE *phpage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizardSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizardSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizardSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizardSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPreviousPage )( 
            IWizardSite * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *GetNextPage )( 
            IWizardSite * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *GetCancelledPage )( 
            IWizardSite * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        END_INTERFACE
    } IWizardSiteVtbl;

    interface IWizardSite
    {
        CONST_VTBL struct IWizardSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizardSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizardSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizardSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizardSite_GetPreviousPage(This,phpage)	\
    ( (This)->lpVtbl -> GetPreviousPage(This,phpage) ) 

#define IWizardSite_GetNextPage(This,phpage)	\
    ( (This)->lpVtbl -> GetNextPage(This,phpage) ) 

#define IWizardSite_GetCancelledPage(This,phpage)	\
    ( (This)->lpVtbl -> GetCancelledPage(This,phpage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWizardSite_GetPreviousPage_Proxy( 
    IWizardSite * This,
    /* [out] */ HPROPSHEETPAGE *phpage);


void __RPC_STUB IWizardSite_GetPreviousPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWizardSite_GetNextPage_Proxy( 
    IWizardSite * This,
    /* [out] */ HPROPSHEETPAGE *phpage);


void __RPC_STUB IWizardSite_GetNextPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWizardSite_GetCancelledPage_Proxy( 
    IWizardSite * This,
    /* [out] */ HPROPSHEETPAGE *phpage);


void __RPC_STUB IWizardSite_GetCancelledPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWizardSite_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0273 */
/* [local] */ 

#define SID_WizardSite IID_IWizardSite


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0273_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0273_v0_0_s_ifspec;

#ifndef __IWizardExtension_INTERFACE_DEFINED__
#define __IWizardExtension_INTERFACE_DEFINED__

/* interface IWizardExtension */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IWizardExtension;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c02ea696-86cc-491e-9b23-74394a0444a8")
    IWizardExtension : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddPages( 
            /* [out][in] */ HPROPSHEETPAGE *aPages,
            /* [in] */ UINT cPages,
            /* [out] */ UINT *pnPagesAdded) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFirstPage( 
            /* [out] */ HPROPSHEETPAGE *phpage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLastPage( 
            /* [out] */ HPROPSHEETPAGE *phpage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWizardExtensionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWizardExtension * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWizardExtension * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWizardExtension * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages )( 
            IWizardExtension * This,
            /* [out][in] */ HPROPSHEETPAGE *aPages,
            /* [in] */ UINT cPages,
            /* [out] */ UINT *pnPagesAdded);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstPage )( 
            IWizardExtension * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPage )( 
            IWizardExtension * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        END_INTERFACE
    } IWizardExtensionVtbl;

    interface IWizardExtension
    {
        CONST_VTBL struct IWizardExtensionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWizardExtension_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWizardExtension_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWizardExtension_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWizardExtension_AddPages(This,aPages,cPages,pnPagesAdded)	\
    ( (This)->lpVtbl -> AddPages(This,aPages,cPages,pnPagesAdded) ) 

#define IWizardExtension_GetFirstPage(This,phpage)	\
    ( (This)->lpVtbl -> GetFirstPage(This,phpage) ) 

#define IWizardExtension_GetLastPage(This,phpage)	\
    ( (This)->lpVtbl -> GetLastPage(This,phpage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWizardExtension_AddPages_Proxy( 
    IWizardExtension * This,
    /* [out][in] */ HPROPSHEETPAGE *aPages,
    /* [in] */ UINT cPages,
    /* [out] */ UINT *pnPagesAdded);


void __RPC_STUB IWizardExtension_AddPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWizardExtension_GetFirstPage_Proxy( 
    IWizardExtension * This,
    /* [out] */ HPROPSHEETPAGE *phpage);


void __RPC_STUB IWizardExtension_GetFirstPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWizardExtension_GetLastPage_Proxy( 
    IWizardExtension * This,
    /* [out] */ HPROPSHEETPAGE *phpage);


void __RPC_STUB IWizardExtension_GetLastPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWizardExtension_INTERFACE_DEFINED__ */


#ifndef __IWebWizardExtension_INTERFACE_DEFINED__
#define __IWebWizardExtension_INTERFACE_DEFINED__

/* interface IWebWizardExtension */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IWebWizardExtension;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0e6b3f66-98d1-48c0-a222-fbde74e2fbc5")
    IWebWizardExtension : public IWizardExtension
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetInitialURL( 
            /* [string][in] */ LPCWSTR pszURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetErrorURL( 
            /* [string][in] */ LPCWSTR pszErrorURL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebWizardExtensionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWebWizardExtension * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWebWizardExtension * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWebWizardExtension * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages )( 
            IWebWizardExtension * This,
            /* [out][in] */ HPROPSHEETPAGE *aPages,
            /* [in] */ UINT cPages,
            /* [out] */ UINT *pnPagesAdded);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstPage )( 
            IWebWizardExtension * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPage )( 
            IWebWizardExtension * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *SetInitialURL )( 
            IWebWizardExtension * This,
            /* [string][in] */ LPCWSTR pszURL);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorURL )( 
            IWebWizardExtension * This,
            /* [string][in] */ LPCWSTR pszErrorURL);
        
        END_INTERFACE
    } IWebWizardExtensionVtbl;

    interface IWebWizardExtension
    {
        CONST_VTBL struct IWebWizardExtensionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebWizardExtension_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWebWizardExtension_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWebWizardExtension_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWebWizardExtension_AddPages(This,aPages,cPages,pnPagesAdded)	\
    ( (This)->lpVtbl -> AddPages(This,aPages,cPages,pnPagesAdded) ) 

#define IWebWizardExtension_GetFirstPage(This,phpage)	\
    ( (This)->lpVtbl -> GetFirstPage(This,phpage) ) 

#define IWebWizardExtension_GetLastPage(This,phpage)	\
    ( (This)->lpVtbl -> GetLastPage(This,phpage) ) 


#define IWebWizardExtension_SetInitialURL(This,pszURL)	\
    ( (This)->lpVtbl -> SetInitialURL(This,pszURL) ) 

#define IWebWizardExtension_SetErrorURL(This,pszErrorURL)	\
    ( (This)->lpVtbl -> SetErrorURL(This,pszErrorURL) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWebWizardExtension_SetInitialURL_Proxy( 
    IWebWizardExtension * This,
    /* [string][in] */ LPCWSTR pszURL);


void __RPC_STUB IWebWizardExtension_SetInitialURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWebWizardExtension_SetErrorURL_Proxy( 
    IWebWizardExtension * This,
    /* [string][in] */ LPCWSTR pszErrorURL);


void __RPC_STUB IWebWizardExtension_SetErrorURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebWizardExtension_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0275 */
/* [local] */ 

#define SID_WebWizardHost IID_IWebWizardExtension
#define SHPWHF_NORECOMPRESS             0x00000001  // don't allow/prompt for recompress of streams
#define SHPWHF_NONETPLACECREATE         0x00000002  // don't create a network place when transfer is complete
#define SHPWHF_NOFILESELECTOR           0x00000004  // don't show the file selector
#define SHPWHF_ANYLOCATION              0x00000100  // allow publishing to any location
#define SHPWHF_VALIDATEVIAWEBFOLDERS    0x00010000  // enable web folders to validate network places (ANP support)


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0275_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0275_v0_0_s_ifspec;

#ifndef __IPublishingWizard_INTERFACE_DEFINED__
#define __IPublishingWizard_INTERFACE_DEFINED__

/* interface IPublishingWizard */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IPublishingWizard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("aa9198bb-ccec-472d-beed-19a4f6733f7a")
    IPublishingWizard : public IWizardExtension
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IDataObject *pdo,
            /* [in] */ DWORD dwOptions,
            /* [string][in] */ LPCWSTR pszServiceScope) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTransferManifest( 
            /* [out] */ HRESULT *phrFromTransfer,
            /* [out] */ IXMLDOMDocument **pdocManifest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPublishingWizardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPublishingWizard * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPublishingWizard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPublishingWizard * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages )( 
            IPublishingWizard * This,
            /* [out][in] */ HPROPSHEETPAGE *aPages,
            /* [in] */ UINT cPages,
            /* [out] */ UINT *pnPagesAdded);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstPage )( 
            IPublishingWizard * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPage )( 
            IPublishingWizard * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPublishingWizard * This,
            /* [in] */ IDataObject *pdo,
            /* [in] */ DWORD dwOptions,
            /* [string][in] */ LPCWSTR pszServiceScope);
        
        HRESULT ( STDMETHODCALLTYPE *GetTransferManifest )( 
            IPublishingWizard * This,
            /* [out] */ HRESULT *phrFromTransfer,
            /* [out] */ IXMLDOMDocument **pdocManifest);
        
        END_INTERFACE
    } IPublishingWizardVtbl;

    interface IPublishingWizard
    {
        CONST_VTBL struct IPublishingWizardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPublishingWizard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPublishingWizard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPublishingWizard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPublishingWizard_AddPages(This,aPages,cPages,pnPagesAdded)	\
    ( (This)->lpVtbl -> AddPages(This,aPages,cPages,pnPagesAdded) ) 

#define IPublishingWizard_GetFirstPage(This,phpage)	\
    ( (This)->lpVtbl -> GetFirstPage(This,phpage) ) 

#define IPublishingWizard_GetLastPage(This,phpage)	\
    ( (This)->lpVtbl -> GetLastPage(This,phpage) ) 


#define IPublishingWizard_Initialize(This,pdo,dwOptions,pszServiceScope)	\
    ( (This)->lpVtbl -> Initialize(This,pdo,dwOptions,pszServiceScope) ) 

#define IPublishingWizard_GetTransferManifest(This,phrFromTransfer,pdocManifest)	\
    ( (This)->lpVtbl -> GetTransferManifest(This,phrFromTransfer,pdocManifest) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPublishingWizard_Initialize_Proxy( 
    IPublishingWizard * This,
    /* [in] */ IDataObject *pdo,
    /* [in] */ DWORD dwOptions,
    /* [string][in] */ LPCWSTR pszServiceScope);


void __RPC_STUB IPublishingWizard_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPublishingWizard_GetTransferManifest_Proxy( 
    IPublishingWizard * This,
    /* [out] */ HRESULT *phrFromTransfer,
    /* [out] */ IXMLDOMDocument **pdocManifest);


void __RPC_STUB IPublishingWizard_GetTransferManifest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPublishingWizard_INTERFACE_DEFINED__ */


#ifndef __IPublishingWizard2_INTERFACE_DEFINED__
#define __IPublishingWizard2_INTERFACE_DEFINED__

/* interface IPublishingWizard2 */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IPublishingWizard2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6d1b6ff1-badd-440f-b85d-c6a491fb405c")
    IPublishingWizard2 : public IPublishingWizard
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetIDArrayToPublish( 
            /* [out] */ UINT *pcItems,
            /* [size_is][size_is][size_is][out] */ PIDLIST_ABSOLUTE **pppidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetServiceScope( 
            /* [size_is][out] */ LPWSTR pszServiceScope,
            /* [in] */ UINT cchServiceScope) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPublishingWizard2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPublishingWizard2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPublishingWizard2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPublishingWizard2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddPages )( 
            IPublishingWizard2 * This,
            /* [out][in] */ HPROPSHEETPAGE *aPages,
            /* [in] */ UINT cPages,
            /* [out] */ UINT *pnPagesAdded);
        
        HRESULT ( STDMETHODCALLTYPE *GetFirstPage )( 
            IPublishingWizard2 * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *GetLastPage )( 
            IPublishingWizard2 * This,
            /* [out] */ HPROPSHEETPAGE *phpage);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPublishingWizard2 * This,
            /* [in] */ IDataObject *pdo,
            /* [in] */ DWORD dwOptions,
            /* [string][in] */ LPCWSTR pszServiceScope);
        
        HRESULT ( STDMETHODCALLTYPE *GetTransferManifest )( 
            IPublishingWizard2 * This,
            /* [out] */ HRESULT *phrFromTransfer,
            /* [out] */ IXMLDOMDocument **pdocManifest);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDArrayToPublish )( 
            IPublishingWizard2 * This,
            /* [out] */ UINT *pcItems,
            /* [size_is][size_is][size_is][out] */ PIDLIST_ABSOLUTE **pppidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetServiceScope )( 
            IPublishingWizard2 * This,
            /* [size_is][out] */ LPWSTR pszServiceScope,
            /* [in] */ UINT cchServiceScope);
        
        END_INTERFACE
    } IPublishingWizard2Vtbl;

    interface IPublishingWizard2
    {
        CONST_VTBL struct IPublishingWizard2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPublishingWizard2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPublishingWizard2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPublishingWizard2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPublishingWizard2_AddPages(This,aPages,cPages,pnPagesAdded)	\
    ( (This)->lpVtbl -> AddPages(This,aPages,cPages,pnPagesAdded) ) 

#define IPublishingWizard2_GetFirstPage(This,phpage)	\
    ( (This)->lpVtbl -> GetFirstPage(This,phpage) ) 

#define IPublishingWizard2_GetLastPage(This,phpage)	\
    ( (This)->lpVtbl -> GetLastPage(This,phpage) ) 


#define IPublishingWizard2_Initialize(This,pdo,dwOptions,pszServiceScope)	\
    ( (This)->lpVtbl -> Initialize(This,pdo,dwOptions,pszServiceScope) ) 

#define IPublishingWizard2_GetTransferManifest(This,phrFromTransfer,pdocManifest)	\
    ( (This)->lpVtbl -> GetTransferManifest(This,phrFromTransfer,pdocManifest) ) 


#define IPublishingWizard2_GetIDArrayToPublish(This,pcItems,pppidl)	\
    ( (This)->lpVtbl -> GetIDArrayToPublish(This,pcItems,pppidl) ) 

#define IPublishingWizard2_GetServiceScope(This,pszServiceScope,cchServiceScope)	\
    ( (This)->lpVtbl -> GetServiceScope(This,pszServiceScope,cchServiceScope) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPublishingWizard2_GetIDArrayToPublish_Proxy( 
    IPublishingWizard2 * This,
    /* [out] */ UINT *pcItems,
    /* [size_is][size_is][size_is][out] */ PIDLIST_ABSOLUTE **pppidl);


void __RPC_STUB IPublishingWizard2_GetIDArrayToPublish_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPublishingWizard2_GetServiceScope_Proxy( 
    IPublishingWizard2 * This,
    /* [size_is][out] */ LPWSTR pszServiceScope,
    /* [in] */ UINT cchServiceScope);


void __RPC_STUB IPublishingWizard2_GetServiceScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPublishingWizard2_INTERFACE_DEFINED__ */


#ifndef __IFolderViewHost_INTERFACE_DEFINED__
#define __IFolderViewHost_INTERFACE_DEFINED__

/* interface IFolderViewHost */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IFolderViewHost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ea58f02-d55a-411d-b09e-9e65ac21605b")
    IFolderViewHost : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HWND hwndParent,
            /* [in] */ IDataObject *pdo,
            /* [in] */ RECT *prc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderViewHostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderViewHost * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderViewHost * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderViewHost * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IFolderViewHost * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ IDataObject *pdo,
            /* [in] */ RECT *prc);
        
        END_INTERFACE
    } IFolderViewHostVtbl;

    interface IFolderViewHost
    {
        CONST_VTBL struct IFolderViewHostVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderViewHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderViewHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderViewHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderViewHost_Initialize(This,hwndParent,pdo,prc)	\
    ( (This)->lpVtbl -> Initialize(This,hwndParent,pdo,prc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFolderViewHost_Initialize_Proxy( 
    IFolderViewHost * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ IDataObject *pdo,
    /* [in] */ RECT *prc);


void __RPC_STUB IFolderViewHost_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderViewHost_INTERFACE_DEFINED__ */


#ifndef __IDevicePickerFolderViewHost_INTERFACE_DEFINED__
#define __IDevicePickerFolderViewHost_INTERFACE_DEFINED__

/* interface IDevicePickerFolderViewHost */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IDevicePickerFolderViewHost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("efe62d8a-c624-49ab-bf35-046be19966de")
    IDevicePickerFolderViewHost : public IFolderFilterSite
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HWND hwnd,
            /* [in] */ RECT *prc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetView( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDevicePickerFolderViewHostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDevicePickerFolderViewHost * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDevicePickerFolderViewHost * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDevicePickerFolderViewHost * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFilter )( 
            IDevicePickerFolderViewHost * This,
            /* [in] */ IUnknown *punk);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IDevicePickerFolderViewHost * This,
            /* [in] */ HWND hwnd,
            /* [in] */ RECT *prc);
        
        HRESULT ( STDMETHODCALLTYPE *GetView )( 
            IDevicePickerFolderViewHost * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IDevicePickerFolderViewHostVtbl;

    interface IDevicePickerFolderViewHost
    {
        CONST_VTBL struct IDevicePickerFolderViewHostVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDevicePickerFolderViewHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDevicePickerFolderViewHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDevicePickerFolderViewHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDevicePickerFolderViewHost_SetFilter(This,punk)	\
    ( (This)->lpVtbl -> SetFilter(This,punk) ) 


#define IDevicePickerFolderViewHost_Initialize(This,hwnd,prc)	\
    ( (This)->lpVtbl -> Initialize(This,hwnd,prc) ) 

#define IDevicePickerFolderViewHost_GetView(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetView(This,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDevicePickerFolderViewHost_Initialize_Proxy( 
    IDevicePickerFolderViewHost * This,
    /* [in] */ HWND hwnd,
    /* [in] */ RECT *prc);


void __RPC_STUB IDevicePickerFolderViewHost_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDevicePickerFolderViewHost_GetView_Proxy( 
    IDevicePickerFolderViewHost * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IDevicePickerFolderViewHost_GetView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDevicePickerFolderViewHost_INTERFACE_DEFINED__ */


#ifndef __IEnumObjects_INTERFACE_DEFINED__
#define __IEnumObjects_INTERFACE_DEFINED__

/* interface IEnumObjects */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IEnumObjects;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2c1c7e2e-2d0e-4059-831e-1e6f82335c2e")
    IEnumObjects : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [in] */ REFIID riid,
            /* [iid_is][length_is][size_is][out] */ void **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumObjects **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumObjectsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumObjects * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumObjects * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumObjects * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumObjects * This,
            /* [in] */ ULONG celt,
            /* [in] */ REFIID riid,
            /* [iid_is][length_is][size_is][out] */ void **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumObjects * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumObjects * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumObjects * This,
            /* [out] */ IEnumObjects **ppenum);
        
        END_INTERFACE
    } IEnumObjectsVtbl;

    interface IEnumObjects
    {
        CONST_VTBL struct IEnumObjectsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumObjects_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumObjects_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumObjects_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumObjects_Next(This,celt,riid,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,riid,rgelt,pceltFetched) ) 

#define IEnumObjects_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumObjects_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumObjects_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumObjects_Next_Proxy( 
    IEnumObjects * This,
    /* [in] */ ULONG celt,
    /* [in] */ REFIID riid,
    /* [iid_is][length_is][size_is][out] */ void **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumObjects_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjects_Skip_Proxy( 
    IEnumObjects * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumObjects_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjects_Reset_Proxy( 
    IEnumObjects * This);


void __RPC_STUB IEnumObjects_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumObjects_Clone_Proxy( 
    IEnumObjects * This,
    /* [out] */ IEnumObjects **ppenum);


void __RPC_STUB IEnumObjects_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumObjects_INTERFACE_DEFINED__ */


#ifndef __IObjectProvider_INTERFACE_DEFINED__
#define __IObjectProvider_INTERFACE_DEFINED__

/* interface IObjectProvider */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IObjectProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a6087428-3be3-4d73-b308-7c04a540bf1a")
    IObjectProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryObject( 
            /* [in] */ REFGUID guidObject,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObjectProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IObjectProvider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IObjectProvider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IObjectProvider * This);
        
        HRESULT ( STDMETHODCALLTYPE *QueryObject )( 
            IObjectProvider * This,
            /* [in] */ REFGUID guidObject,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvOut);
        
        END_INTERFACE
    } IObjectProviderVtbl;

    interface IObjectProvider
    {
        CONST_VTBL struct IObjectProviderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObjectProvider_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IObjectProvider_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IObjectProvider_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IObjectProvider_QueryObject(This,guidObject,riid,ppvOut)	\
    ( (This)->lpVtbl -> QueryObject(This,guidObject,riid,ppvOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IObjectProvider_QueryObject_Proxy( 
    IObjectProvider * This,
    /* [in] */ REFGUID guidObject,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppvOut);


void __RPC_STUB IObjectProvider_QueryObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObjectProvider_INTERFACE_DEFINED__ */


#ifndef __INamespaceWalkCB_INTERFACE_DEFINED__
#define __INamespaceWalkCB_INTERFACE_DEFINED__

/* interface INamespaceWalkCB */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_INamespaceWalkCB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d92995f8-cf5e-4a76-bf59-ead39ea2b97e")
    INamespaceWalkCB : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FoundItem( 
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnterFolder( 
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LeaveFolder( 
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeProgressDialog( 
            /* [string][out] */ LPWSTR *ppszTitle,
            /* [string][out] */ LPWSTR *ppszCancel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INamespaceWalkCBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INamespaceWalkCB * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INamespaceWalkCB * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INamespaceWalkCB * This);
        
        HRESULT ( STDMETHODCALLTYPE *FoundItem )( 
            INamespaceWalkCB * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *EnterFolder )( 
            INamespaceWalkCB * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *LeaveFolder )( 
            INamespaceWalkCB * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeProgressDialog )( 
            INamespaceWalkCB * This,
            /* [string][out] */ LPWSTR *ppszTitle,
            /* [string][out] */ LPWSTR *ppszCancel);
        
        END_INTERFACE
    } INamespaceWalkCBVtbl;

    interface INamespaceWalkCB
    {
        CONST_VTBL struct INamespaceWalkCBVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INamespaceWalkCB_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INamespaceWalkCB_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INamespaceWalkCB_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INamespaceWalkCB_FoundItem(This,psf,pidl)	\
    ( (This)->lpVtbl -> FoundItem(This,psf,pidl) ) 

#define INamespaceWalkCB_EnterFolder(This,psf,pidl)	\
    ( (This)->lpVtbl -> EnterFolder(This,psf,pidl) ) 

#define INamespaceWalkCB_LeaveFolder(This,psf,pidl)	\
    ( (This)->lpVtbl -> LeaveFolder(This,psf,pidl) ) 

#define INamespaceWalkCB_InitializeProgressDialog(This,ppszTitle,ppszCancel)	\
    ( (This)->lpVtbl -> InitializeProgressDialog(This,ppszTitle,ppszCancel) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INamespaceWalkCB_FoundItem_Proxy( 
    INamespaceWalkCB * This,
    /* [in] */ IShellFolder *psf,
    /* [in] */ PCUITEMID_CHILD pidl);


void __RPC_STUB INamespaceWalkCB_FoundItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INamespaceWalkCB_EnterFolder_Proxy( 
    INamespaceWalkCB * This,
    /* [in] */ IShellFolder *psf,
    /* [in] */ PCUITEMID_CHILD pidl);


void __RPC_STUB INamespaceWalkCB_EnterFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INamespaceWalkCB_LeaveFolder_Proxy( 
    INamespaceWalkCB * This,
    /* [in] */ IShellFolder *psf,
    /* [in] */ PCUITEMID_CHILD pidl);


void __RPC_STUB INamespaceWalkCB_LeaveFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INamespaceWalkCB_InitializeProgressDialog_Proxy( 
    INamespaceWalkCB * This,
    /* [string][out] */ LPWSTR *ppszTitle,
    /* [string][out] */ LPWSTR *ppszCancel);


void __RPC_STUB INamespaceWalkCB_InitializeProgressDialog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INamespaceWalkCB_INTERFACE_DEFINED__ */


#ifndef __INamespaceWalkCB2_INTERFACE_DEFINED__
#define __INamespaceWalkCB2_INTERFACE_DEFINED__

/* interface INamespaceWalkCB2 */
/* [object][uuid] */ 


EXTERN_C const IID IID_INamespaceWalkCB2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7ac7492b-c38e-438a-87db-68737844ff70")
    INamespaceWalkCB2 : public INamespaceWalkCB
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE WalkComplete( 
            HRESULT hr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INamespaceWalkCB2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INamespaceWalkCB2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INamespaceWalkCB2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INamespaceWalkCB2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *FoundItem )( 
            INamespaceWalkCB2 * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *EnterFolder )( 
            INamespaceWalkCB2 * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *LeaveFolder )( 
            INamespaceWalkCB2 * This,
            /* [in] */ IShellFolder *psf,
            /* [in] */ PCUITEMID_CHILD pidl);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeProgressDialog )( 
            INamespaceWalkCB2 * This,
            /* [string][out] */ LPWSTR *ppszTitle,
            /* [string][out] */ LPWSTR *ppszCancel);
        
        HRESULT ( STDMETHODCALLTYPE *WalkComplete )( 
            INamespaceWalkCB2 * This,
            HRESULT hr);
        
        END_INTERFACE
    } INamespaceWalkCB2Vtbl;

    interface INamespaceWalkCB2
    {
        CONST_VTBL struct INamespaceWalkCB2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INamespaceWalkCB2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INamespaceWalkCB2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INamespaceWalkCB2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INamespaceWalkCB2_FoundItem(This,psf,pidl)	\
    ( (This)->lpVtbl -> FoundItem(This,psf,pidl) ) 

#define INamespaceWalkCB2_EnterFolder(This,psf,pidl)	\
    ( (This)->lpVtbl -> EnterFolder(This,psf,pidl) ) 

#define INamespaceWalkCB2_LeaveFolder(This,psf,pidl)	\
    ( (This)->lpVtbl -> LeaveFolder(This,psf,pidl) ) 

#define INamespaceWalkCB2_InitializeProgressDialog(This,ppszTitle,ppszCancel)	\
    ( (This)->lpVtbl -> InitializeProgressDialog(This,ppszTitle,ppszCancel) ) 


#define INamespaceWalkCB2_WalkComplete(This,hr)	\
    ( (This)->lpVtbl -> WalkComplete(This,hr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INamespaceWalkCB2_WalkComplete_Proxy( 
    INamespaceWalkCB2 * This,
    HRESULT hr);


void __RPC_STUB INamespaceWalkCB2_WalkComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INamespaceWalkCB2_INTERFACE_DEFINED__ */


#ifndef __INamespaceWalk_INTERFACE_DEFINED__
#define __INamespaceWalk_INTERFACE_DEFINED__

/* interface INamespaceWalk */
/* [object][helpstring][uuid] */ 


enum tagNAMESPACEWALKFLAG
    {	NSWF_NONE_IMPLIES_ALL	= 0x1,
	NSWF_ONE_IMPLIES_ALL	= 0x2,
	NSWF_DONT_TRAVERSE_LINKS	= 0x4,
	NSWF_DONT_ACCUMULATE_RESULT	= 0x8,
	NSWF_TRAVERSE_STREAM_JUNCTIONS	= 0x10,
	NSWF_FILESYSTEM_ONLY	= 0x20,
	NSWF_SHOW_PROGRESS	= 0x40,
	NSWF_FLAG_VIEWORDER	= 0x80,
	NSWF_IGNORE_AUTOPLAY_HIDA	= 0x100,
	NSWF_ASYNC	= 0x200,
	NSWF_DONT_RESOLVE_LINKS	= 0x400,
	NSWF_ACCUMULATE_FOLDERS	= 0x800,
	NSWF_DONT_SORT	= 0x1000,
	NSWF_USE_STORAGE_ENUM	= 0x2000,
	NSWF_USE_WALKTREE_ENUM	= 0x4000
    } ;

EXTERN_C const IID IID_INamespaceWalk;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57ced8a7-3f4a-432c-9350-30f24483f74f")
    INamespaceWalk : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Walk( 
            /* [in] */ IUnknown *punkToWalk,
            /* [in] */ DWORD dwFlags,
            /* [in] */ int cDepth,
            /* [in] */ INamespaceWalkCB *pnswcb) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIDArrayResult( 
            /* [out] */ UINT *pcItems,
            /* [size_is][size_is][size_is][out] */ PIDLIST_ABSOLUTE **prgpidl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INamespaceWalkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INamespaceWalk * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INamespaceWalk * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INamespaceWalk * This);
        
        HRESULT ( STDMETHODCALLTYPE *Walk )( 
            INamespaceWalk * This,
            /* [in] */ IUnknown *punkToWalk,
            /* [in] */ DWORD dwFlags,
            /* [in] */ int cDepth,
            /* [in] */ INamespaceWalkCB *pnswcb);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDArrayResult )( 
            INamespaceWalk * This,
            /* [out] */ UINT *pcItems,
            /* [size_is][size_is][size_is][out] */ PIDLIST_ABSOLUTE **prgpidl);
        
        END_INTERFACE
    } INamespaceWalkVtbl;

    interface INamespaceWalk
    {
        CONST_VTBL struct INamespaceWalkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INamespaceWalk_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INamespaceWalk_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INamespaceWalk_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INamespaceWalk_Walk(This,punkToWalk,dwFlags,cDepth,pnswcb)	\
    ( (This)->lpVtbl -> Walk(This,punkToWalk,dwFlags,cDepth,pnswcb) ) 

#define INamespaceWalk_GetIDArrayResult(This,pcItems,prgpidl)	\
    ( (This)->lpVtbl -> GetIDArrayResult(This,pcItems,prgpidl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INamespaceWalk_Walk_Proxy( 
    INamespaceWalk * This,
    /* [in] */ IUnknown *punkToWalk,
    /* [in] */ DWORD dwFlags,
    /* [in] */ int cDepth,
    /* [in] */ INamespaceWalkCB *pnswcb);


void __RPC_STUB INamespaceWalk_Walk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE INamespaceWalk_GetIDArrayResult_Proxy( 
    INamespaceWalk * This,
    /* [out] */ UINT *pcItems,
    /* [size_is][size_is][size_is][out] */ PIDLIST_ABSOLUTE **prgpidl);


void __RPC_STUB INamespaceWalk_GetIDArrayResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INamespaceWalk_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0284 */
/* [local] */ 

_inline void FreeIDListArray(PIDLIST_RELATIVE *ppidls, UINT cItems)
{                                        
     UINT i;                             
     for (i = 0; i < cItems; i++)        
     {                                   
         CoTaskMemFree(ppidls[i]);       
     }                                   
     CoTaskMemFree(ppidls);              
}                                        
#if defined(STRICT_TYPED_ITEMIDS) && defined(__cplusplus)
_inline void FreeIDListArrayFull(PIDLIST_ABSOLUTE *ppidls, UINT cItems)
{                                        
     for (UINT i = 0; i < cItems; i++)   
     {                                   
         CoTaskMemFree(ppidls[i]);       
     }                                   
     CoTaskMemFree(ppidls);              
}                                        
_inline void FreeIDListArrayChild(PITEMID_CHILD *ppidls, UINT cItems)
{                                        
     for (UINT i = 0; i < cItems; i++)   
     {                                   
         CoTaskMemFree(ppidls[i]);       
     }                                   
     CoTaskMemFree(ppidls);              
}                                        
#else //  defined(STRICT_TYPED_ITEMIDS) && defined(__cplusplus)
#define FreeIDListArrayFull FreeIDListArray
#define FreeIDListArrayChild FreeIDListArray
#endif //  defined(STRICT_TYPED_ITEMIDS) && defined(__cplusplus)
#define ACDD_VISIBLE        0x0001


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0284_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0284_v0_0_s_ifspec;

#ifndef __IAutoCompleteDropDown_INTERFACE_DEFINED__
#define __IAutoCompleteDropDown_INTERFACE_DEFINED__

/* interface IAutoCompleteDropDown */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IAutoCompleteDropDown;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3CD141F4-3C6A-11d2-BCAA-00C04FD929DB")
    IAutoCompleteDropDown : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDropDownStatus( 
            /* [out] */ DWORD *pdwFlags,
            /* [string][out] */ LPWSTR *ppwszString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetEnumerator( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutoCompleteDropDownVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAutoCompleteDropDown * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAutoCompleteDropDown * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAutoCompleteDropDown * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDropDownStatus )( 
            IAutoCompleteDropDown * This,
            /* [out] */ DWORD *pdwFlags,
            /* [string][out] */ LPWSTR *ppwszString);
        
        HRESULT ( STDMETHODCALLTYPE *ResetEnumerator )( 
            IAutoCompleteDropDown * This);
        
        END_INTERFACE
    } IAutoCompleteDropDownVtbl;

    interface IAutoCompleteDropDown
    {
        CONST_VTBL struct IAutoCompleteDropDownVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutoCompleteDropDown_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAutoCompleteDropDown_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAutoCompleteDropDown_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAutoCompleteDropDown_GetDropDownStatus(This,pdwFlags,ppwszString)	\
    ( (This)->lpVtbl -> GetDropDownStatus(This,pdwFlags,ppwszString) ) 

#define IAutoCompleteDropDown_ResetEnumerator(This)	\
    ( (This)->lpVtbl -> ResetEnumerator(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAutoCompleteDropDown_GetDropDownStatus_Proxy( 
    IAutoCompleteDropDown * This,
    /* [out] */ DWORD *pdwFlags,
    /* [string][out] */ LPWSTR *ppwszString);


void __RPC_STUB IAutoCompleteDropDown_GetDropDownStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAutoCompleteDropDown_ResetEnumerator_Proxy( 
    IAutoCompleteDropDown * This);


void __RPC_STUB IAutoCompleteDropDown_ResetEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAutoCompleteDropDown_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0285 */
/* [local] */ 

#define PPW_LAUNCHEDBYUSER       0x00000001      // The wizard was launch explicitly by the user, not on demand by the key manager


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0285_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0285_v0_0_s_ifspec;

#ifndef __IModalWindow_INTERFACE_DEFINED__
#define __IModalWindow_INTERFACE_DEFINED__

/* interface IModalWindow */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IModalWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b4db1657-70d7-485e-8e3e-6fcb5a5c1802")
    IModalWindow : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ HWND hwndParent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModalWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IModalWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IModalWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IModalWindow * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IModalWindow * This,
            /* [in] */ HWND hwndParent);
        
        END_INTERFACE
    } IModalWindowVtbl;

    interface IModalWindow
    {
        CONST_VTBL struct IModalWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModalWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IModalWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IModalWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IModalWindow_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IModalWindow_RemoteShow_Proxy( 
    IModalWindow * This,
    /* [in] */ HWND hwndParent);


void __RPC_STUB IModalWindow_RemoteShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModalWindow_INTERFACE_DEFINED__ */


#ifndef __IPassportWizard_INTERFACE_DEFINED__
#define __IPassportWizard_INTERFACE_DEFINED__

/* interface IPassportWizard */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IPassportWizard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a09db586-9180-41ac-9114-460a7f362b76")
    IPassportWizard : public IModalWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetOptions( 
            /* [in] */ DWORD dwOptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPassportWizardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPassportWizard * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPassportWizard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPassportWizard * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IPassportWizard * This,
            /* [in] */ HWND hwndParent);
        
        HRESULT ( STDMETHODCALLTYPE *SetOptions )( 
            IPassportWizard * This,
            /* [in] */ DWORD dwOptions);
        
        END_INTERFACE
    } IPassportWizardVtbl;

    interface IPassportWizard
    {
        CONST_VTBL struct IPassportWizardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPassportWizard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPassportWizard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPassportWizard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPassportWizard_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 


#define IPassportWizard_SetOptions(This,dwOptions)	\
    ( (This)->lpVtbl -> SetOptions(This,dwOptions) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPassportWizard_SetOptions_Proxy( 
    IPassportWizard * This,
    /* [in] */ DWORD dwOptions);


void __RPC_STUB IPassportWizard_SetOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPassportWizard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0286 */
/* [local] */ 

#define PROPSTR_EXTENSIONCOMPLETIONSTATE L"ExtensionCompletionState"

enum tagCDBURNINGEXTENSIONRET
    {	CDBE_RET_DEFAULT	= 0,
	CDBE_RET_DONTRUNOTHEREXTS	= 0x1,
	CDBE_RET_STOPWIZARD	= 0x2
    } ;
#define SID_CDWizardHost IID_ICDBurnExt

enum tagCDBURNINGEXTENSIONACTION
    {	CDBE_TYPE_MUSIC	= 0x1,
	CDBE_TYPE_DATA	= 0x2,
	CDBE_TYPE_ALL	= 0xffffffff
    } ;
typedef int CDBE_ACTIONS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0286_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0286_v0_0_s_ifspec;

#ifndef __ICDBurnExt_INTERFACE_DEFINED__
#define __ICDBurnExt_INTERFACE_DEFINED__

/* interface ICDBurnExt */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_ICDBurnExt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2271dcca-74fc-4414-8fb7-c56b05ace2d7")
    ICDBurnExt : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSupportedActionTypes( 
            /* [out] */ CDBE_ACTIONS *pdwActions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICDBurnExtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICDBurnExt * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICDBurnExt * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICDBurnExt * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSupportedActionTypes )( 
            ICDBurnExt * This,
            /* [out] */ CDBE_ACTIONS *pdwActions);
        
        END_INTERFACE
    } ICDBurnExtVtbl;

    interface ICDBurnExt
    {
        CONST_VTBL struct ICDBurnExtVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICDBurnExt_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICDBurnExt_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICDBurnExt_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICDBurnExt_GetSupportedActionTypes(This,pdwActions)	\
    ( (This)->lpVtbl -> GetSupportedActionTypes(This,pdwActions) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICDBurnExt_GetSupportedActionTypes_Proxy( 
    ICDBurnExt * This,
    /* [out] */ CDBE_ACTIONS *pdwActions);


void __RPC_STUB ICDBurnExt_GetSupportedActionTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICDBurnExt_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0287 */
/* [local] */ 

typedef void ( *PFDVENUMREADYBALLBACK )( 
    LPVOID pvData);



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0287_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0287_v0_0_s_ifspec;

#ifndef __IDVGetEnum_INTERFACE_DEFINED__
#define __IDVGetEnum_INTERFACE_DEFINED__

/* interface IDVGetEnum */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IDVGetEnum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70F55181-5FEA-4900-B6B8-7343CB0A348C")
    IDVGetEnum : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetEnumReadyCallback( 
            /* [in] */ PFDVENUMREADYBALLBACK pfn,
            /* [in] */ LPVOID pvData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateEnumIDListFromContents( 
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ DWORD dwEnumFlags,
            /* [out] */ IEnumIDList **ppEnumIDList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDVGetEnumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDVGetEnum * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDVGetEnum * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDVGetEnum * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetEnumReadyCallback )( 
            IDVGetEnum * This,
            /* [in] */ PFDVENUMREADYBALLBACK pfn,
            /* [in] */ LPVOID pvData);
        
        HRESULT ( STDMETHODCALLTYPE *CreateEnumIDListFromContents )( 
            IDVGetEnum * This,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            /* [in] */ DWORD dwEnumFlags,
            /* [out] */ IEnumIDList **ppEnumIDList);
        
        END_INTERFACE
    } IDVGetEnumVtbl;

    interface IDVGetEnum
    {
        CONST_VTBL struct IDVGetEnumVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDVGetEnum_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDVGetEnum_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDVGetEnum_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDVGetEnum_SetEnumReadyCallback(This,pfn,pvData)	\
    ( (This)->lpVtbl -> SetEnumReadyCallback(This,pfn,pvData) ) 

#define IDVGetEnum_CreateEnumIDListFromContents(This,pidlFolder,dwEnumFlags,ppEnumIDList)	\
    ( (This)->lpVtbl -> CreateEnumIDListFromContents(This,pidlFolder,dwEnumFlags,ppEnumIDList) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDVGetEnum_SetEnumReadyCallback_Proxy( 
    IDVGetEnum * This,
    /* [in] */ PFDVENUMREADYBALLBACK pfn,
    /* [in] */ LPVOID pvData);


void __RPC_STUB IDVGetEnum_SetEnumReadyCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDVGetEnum_CreateEnumIDListFromContents_Proxy( 
    IDVGetEnum * This,
    /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
    /* [in] */ DWORD dwEnumFlags,
    /* [out] */ IEnumIDList **ppEnumIDList);


void __RPC_STUB IDVGetEnum_CreateEnumIDListFromContents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDVGetEnum_INTERFACE_DEFINED__ */


#ifndef __IInsertItem_INTERFACE_DEFINED__
#define __IInsertItem_INTERFACE_DEFINED__

/* interface IInsertItem */
/* [local][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IInsertItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D2B57227-3D23-4b95-93C0-492BD454C356")
    IInsertItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InsertItem( 
            /* [in] */ PCUIDLIST_RELATIVE pidl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInsertItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInsertItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInsertItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInsertItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *InsertItem )( 
            IInsertItem * This,
            /* [in] */ PCUIDLIST_RELATIVE pidl);
        
        END_INTERFACE
    } IInsertItemVtbl;

    interface IInsertItem
    {
        CONST_VTBL struct IInsertItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInsertItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInsertItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInsertItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInsertItem_InsertItem(This,pidl)	\
    ( (This)->lpVtbl -> InsertItem(This,pidl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IInsertItem_InsertItem_Proxy( 
    IInsertItem * This,
    /* [in] */ PCUIDLIST_RELATIVE pidl);


void __RPC_STUB IInsertItem_InsertItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInsertItem_INTERFACE_DEFINED__ */


#ifndef __IDeskBar_INTERFACE_DEFINED__
#define __IDeskBar_INTERFACE_DEFINED__

/* interface IDeskBar */
/* [local][unique][object][uuid] */ 


EXTERN_C const IID IID_IDeskBar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB0FE173-1A3A-11D0-89B3-00A0C90A90AC")
    IDeskBar : public IOleWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetClient( 
            /* [in] */ IUnknown *punkClient) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetClient( 
            /* [out] */ IUnknown **ppunkClient) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnPosRectChangeDB( 
            /* [in] */ LPRECT prc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDeskBarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDeskBar * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDeskBar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDeskBar * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IDeskBar * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IDeskBar * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetClient )( 
            IDeskBar * This,
            /* [in] */ IUnknown *punkClient);
        
        HRESULT ( STDMETHODCALLTYPE *GetClient )( 
            IDeskBar * This,
            /* [out] */ IUnknown **ppunkClient);
        
        HRESULT ( STDMETHODCALLTYPE *OnPosRectChangeDB )( 
            IDeskBar * This,
            /* [in] */ LPRECT prc);
        
        END_INTERFACE
    } IDeskBarVtbl;

    interface IDeskBar
    {
        CONST_VTBL struct IDeskBarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeskBar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDeskBar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDeskBar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDeskBar_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IDeskBar_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IDeskBar_SetClient(This,punkClient)	\
    ( (This)->lpVtbl -> SetClient(This,punkClient) ) 

#define IDeskBar_GetClient(This,ppunkClient)	\
    ( (This)->lpVtbl -> GetClient(This,ppunkClient) ) 

#define IDeskBar_OnPosRectChangeDB(This,prc)	\
    ( (This)->lpVtbl -> OnPosRectChangeDB(This,prc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDeskBar_SetClient_Proxy( 
    IDeskBar * This,
    /* [in] */ IUnknown *punkClient);


void __RPC_STUB IDeskBar_SetClient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDeskBar_GetClient_Proxy( 
    IDeskBar * This,
    /* [out] */ IUnknown **ppunkClient);


void __RPC_STUB IDeskBar_GetClient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDeskBar_OnPosRectChangeDB_Proxy( 
    IDeskBar * This,
    /* [in] */ LPRECT prc);


void __RPC_STUB IDeskBar_OnPosRectChangeDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDeskBar_INTERFACE_DEFINED__ */


#ifndef __IMenuBand_INTERFACE_DEFINED__
#define __IMenuBand_INTERFACE_DEFINED__

/* interface IMenuBand */
/* [local][unique][object][uuid] */ 


enum tagMENUBANDHANDLERCID
    {	MBHANDCID_PIDLSELECT	= 0
    } ;

EXTERN_C const IID IID_IMenuBand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("568804CD-CBD7-11d0-9816-00C04FD91972")
    IMenuBand : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsMenuMessage( 
            /* [in] */ MSG *pmsg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateMenuMessage( 
            /* [out][in] */ MSG *pmsg,
            /* [out] */ LRESULT *plRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMenuBandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMenuBand * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMenuBand * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMenuBand * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsMenuMessage )( 
            IMenuBand * This,
            /* [in] */ MSG *pmsg);
        
        HRESULT ( STDMETHODCALLTYPE *TranslateMenuMessage )( 
            IMenuBand * This,
            /* [out][in] */ MSG *pmsg,
            /* [out] */ LRESULT *plRet);
        
        END_INTERFACE
    } IMenuBandVtbl;

    interface IMenuBand
    {
        CONST_VTBL struct IMenuBandVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMenuBand_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMenuBand_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMenuBand_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMenuBand_IsMenuMessage(This,pmsg)	\
    ( (This)->lpVtbl -> IsMenuMessage(This,pmsg) ) 

#define IMenuBand_TranslateMenuMessage(This,pmsg,plRet)	\
    ( (This)->lpVtbl -> TranslateMenuMessage(This,pmsg,plRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMenuBand_IsMenuMessage_Proxy( 
    IMenuBand * This,
    /* [in] */ MSG *pmsg);


void __RPC_STUB IMenuBand_IsMenuMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMenuBand_TranslateMenuMessage_Proxy( 
    IMenuBand * This,
    /* [out][in] */ MSG *pmsg,
    /* [out] */ LRESULT *plRet);


void __RPC_STUB IMenuBand_TranslateMenuMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMenuBand_INTERFACE_DEFINED__ */


#ifndef __IFolderBandPriv_INTERFACE_DEFINED__
#define __IFolderBandPriv_INTERFACE_DEFINED__

/* interface IFolderBandPriv */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IFolderBandPriv;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47c01f95-e185-412c-b5c5-4f27df965aea")
    IFolderBandPriv : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetCascade( 
            /* [in] */ BOOL f) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAccelerators( 
            /* [in] */ BOOL f) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNoIcons( 
            /* [in] */ BOOL f) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNoText( 
            /* [in] */ BOOL f) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderBandPrivVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderBandPriv * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderBandPriv * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderBandPriv * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetCascade )( 
            IFolderBandPriv * This,
            /* [in] */ BOOL f);
        
        HRESULT ( STDMETHODCALLTYPE *SetAccelerators )( 
            IFolderBandPriv * This,
            /* [in] */ BOOL f);
        
        HRESULT ( STDMETHODCALLTYPE *SetNoIcons )( 
            IFolderBandPriv * This,
            /* [in] */ BOOL f);
        
        HRESULT ( STDMETHODCALLTYPE *SetNoText )( 
            IFolderBandPriv * This,
            /* [in] */ BOOL f);
        
        END_INTERFACE
    } IFolderBandPrivVtbl;

    interface IFolderBandPriv
    {
        CONST_VTBL struct IFolderBandPrivVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderBandPriv_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderBandPriv_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderBandPriv_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderBandPriv_SetCascade(This,f)	\
    ( (This)->lpVtbl -> SetCascade(This,f) ) 

#define IFolderBandPriv_SetAccelerators(This,f)	\
    ( (This)->lpVtbl -> SetAccelerators(This,f) ) 

#define IFolderBandPriv_SetNoIcons(This,f)	\
    ( (This)->lpVtbl -> SetNoIcons(This,f) ) 

#define IFolderBandPriv_SetNoText(This,f)	\
    ( (This)->lpVtbl -> SetNoText(This,f) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFolderBandPriv_SetCascade_Proxy( 
    IFolderBandPriv * This,
    /* [in] */ BOOL f);


void __RPC_STUB IFolderBandPriv_SetCascade_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderBandPriv_SetAccelerators_Proxy( 
    IFolderBandPriv * This,
    /* [in] */ BOOL f);


void __RPC_STUB IFolderBandPriv_SetAccelerators_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderBandPriv_SetNoIcons_Proxy( 
    IFolderBandPriv * This,
    /* [in] */ BOOL f);


void __RPC_STUB IFolderBandPriv_SetNoIcons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderBandPriv_SetNoText_Proxy( 
    IFolderBandPriv * This,
    /* [in] */ BOOL f);


void __RPC_STUB IFolderBandPriv_SetNoText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderBandPriv_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0293 */
/* [local] */ 

#if _WIN32_IE >= 0x0400
#include <pshpack8.h>
typedef struct tagBANDSITEINFO
    {
    DWORD dwMask;
    DWORD dwState;
    DWORD dwStyle;
    } 	BANDSITEINFO;

#include <poppack.h>

enum tagBANDSITECID
    {	BSID_BANDADDED	= 0,
	BSID_BANDREMOVED	= ( BSID_BANDADDED + 1 ) 
    } ;
#define BSIM_STATE          0x00000001
#define BSIM_STYLE          0x00000002
#define BSSF_VISIBLE        0x00000001
#define BSSF_NOTITLE        0x00000002
#define BSSF_UNDELETEABLE   0x00001000
#define BSIS_AUTOGRIPPER               0x00000000
#define BSIS_NOGRIPPER                 0x00000001
#define BSIS_ALWAYSGRIPPER             0x00000002
#define BSIS_LEFTALIGN                 0x00000004
#define BSIS_SINGLECLICK               0x00000008
#define BSIS_NOCONTEXTMENU             0x00000010
#define BSIS_NODROPTARGET              0x00000020
#define BSIS_NOCAPTION                 0x00000040
#define BSIS_PREFERNOLINEBREAK         0x00000080
#define BSIS_LOCKED                    0x00000100
#define BSIS_MIL                       0x00000200
#define BSIS_PRESERVEORDERDURINGLAYOUT 0x00000400
#define SID_SBandSite IID_IBandSite
#define CGID_BandSite IID_IBandSite


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0293_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0293_v0_0_s_ifspec;

#ifndef __IBandSite_INTERFACE_DEFINED__
#define __IBandSite_INTERFACE_DEFINED__

/* interface IBandSite */
/* [uuid][object] */ 


EXTERN_C const IID IID_IBandSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4CF504B0-DE96-11D0-8B3F-00A0C911E8E5")
    IBandSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddBand( 
            /* [in] */ IUnknown *punk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumBands( 
            /* [in] */ UINT uBand,
            /* [out] */ DWORD *pdwBandID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryBand( 
            /* [in] */ DWORD dwBandID,
            /* [out] */ IDeskBand **ppstb,
            /* [out] */ DWORD *pdwState,
            /* [size_is][out] */ LPWSTR pszName,
            /* [in] */ int cchName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBandState( 
            /* [in] */ DWORD dwBandID,
            /* [in] */ DWORD dwMask,
            /* [in] */ DWORD dwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveBand( 
            /* [in] */ DWORD dwBandID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBandObject( 
            /* [in] */ DWORD dwBandID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBandSiteInfo( 
            /* [in] */ const BANDSITEINFO *pbsinfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBandSiteInfo( 
            /* [out][in] */ BANDSITEINFO *pbsinfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBandSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBandSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBandSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBandSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddBand )( 
            IBandSite * This,
            /* [in] */ IUnknown *punk);
        
        HRESULT ( STDMETHODCALLTYPE *EnumBands )( 
            IBandSite * This,
            /* [in] */ UINT uBand,
            /* [out] */ DWORD *pdwBandID);
        
        HRESULT ( STDMETHODCALLTYPE *QueryBand )( 
            IBandSite * This,
            /* [in] */ DWORD dwBandID,
            /* [out] */ IDeskBand **ppstb,
            /* [out] */ DWORD *pdwState,
            /* [size_is][out] */ LPWSTR pszName,
            /* [in] */ int cchName);
        
        HRESULT ( STDMETHODCALLTYPE *SetBandState )( 
            IBandSite * This,
            /* [in] */ DWORD dwBandID,
            /* [in] */ DWORD dwMask,
            /* [in] */ DWORD dwState);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveBand )( 
            IBandSite * This,
            /* [in] */ DWORD dwBandID);
        
        HRESULT ( STDMETHODCALLTYPE *GetBandObject )( 
            IBandSite * This,
            /* [in] */ DWORD dwBandID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *SetBandSiteInfo )( 
            IBandSite * This,
            /* [in] */ const BANDSITEINFO *pbsinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetBandSiteInfo )( 
            IBandSite * This,
            /* [out][in] */ BANDSITEINFO *pbsinfo);
        
        END_INTERFACE
    } IBandSiteVtbl;

    interface IBandSite
    {
        CONST_VTBL struct IBandSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBandSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBandSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBandSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBandSite_AddBand(This,punk)	\
    ( (This)->lpVtbl -> AddBand(This,punk) ) 

#define IBandSite_EnumBands(This,uBand,pdwBandID)	\
    ( (This)->lpVtbl -> EnumBands(This,uBand,pdwBandID) ) 

#define IBandSite_QueryBand(This,dwBandID,ppstb,pdwState,pszName,cchName)	\
    ( (This)->lpVtbl -> QueryBand(This,dwBandID,ppstb,pdwState,pszName,cchName) ) 

#define IBandSite_SetBandState(This,dwBandID,dwMask,dwState)	\
    ( (This)->lpVtbl -> SetBandState(This,dwBandID,dwMask,dwState) ) 

#define IBandSite_RemoveBand(This,dwBandID)	\
    ( (This)->lpVtbl -> RemoveBand(This,dwBandID) ) 

#define IBandSite_GetBandObject(This,dwBandID,riid,ppv)	\
    ( (This)->lpVtbl -> GetBandObject(This,dwBandID,riid,ppv) ) 

#define IBandSite_SetBandSiteInfo(This,pbsinfo)	\
    ( (This)->lpVtbl -> SetBandSiteInfo(This,pbsinfo) ) 

#define IBandSite_GetBandSiteInfo(This,pbsinfo)	\
    ( (This)->lpVtbl -> GetBandSiteInfo(This,pbsinfo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBandSite_AddBand_Proxy( 
    IBandSite * This,
    /* [in] */ IUnknown *punk);


void __RPC_STUB IBandSite_AddBand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_EnumBands_Proxy( 
    IBandSite * This,
    /* [in] */ UINT uBand,
    /* [out] */ DWORD *pdwBandID);


void __RPC_STUB IBandSite_EnumBands_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_QueryBand_Proxy( 
    IBandSite * This,
    /* [in] */ DWORD dwBandID,
    /* [out] */ IDeskBand **ppstb,
    /* [out] */ DWORD *pdwState,
    /* [size_is][out] */ LPWSTR pszName,
    /* [in] */ int cchName);


void __RPC_STUB IBandSite_QueryBand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_SetBandState_Proxy( 
    IBandSite * This,
    /* [in] */ DWORD dwBandID,
    /* [in] */ DWORD dwMask,
    /* [in] */ DWORD dwState);


void __RPC_STUB IBandSite_SetBandState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_RemoveBand_Proxy( 
    IBandSite * This,
    /* [in] */ DWORD dwBandID);


void __RPC_STUB IBandSite_RemoveBand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_GetBandObject_Proxy( 
    IBandSite * This,
    /* [in] */ DWORD dwBandID,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IBandSite_GetBandObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_SetBandSiteInfo_Proxy( 
    IBandSite * This,
    /* [in] */ const BANDSITEINFO *pbsinfo);


void __RPC_STUB IBandSite_SetBandSiteInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandSite_GetBandSiteInfo_Proxy( 
    IBandSite * This,
    /* [out][in] */ BANDSITEINFO *pbsinfo);


void __RPC_STUB IBandSite_GetBandSiteInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBandSite_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0294 */
/* [local] */ 

#endif // _WIN32_IE >= 0x0400


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0294_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0294_v0_0_s_ifspec;

#ifndef __IRegTreeItem_INTERFACE_DEFINED__
#define __IRegTreeItem_INTERFACE_DEFINED__

/* interface IRegTreeItem */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IRegTreeItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A9521922-0812-4d44-9EC3-7FD38C726F3D")
    IRegTreeItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCheckState( 
            /* [out] */ BOOL *pbCheck) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCheckState( 
            /* [in] */ BOOL bCheck) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRegTreeItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRegTreeItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRegTreeItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRegTreeItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetCheckState )( 
            IRegTreeItem * This,
            /* [out] */ BOOL *pbCheck);
        
        HRESULT ( STDMETHODCALLTYPE *SetCheckState )( 
            IRegTreeItem * This,
            /* [in] */ BOOL bCheck);
        
        END_INTERFACE
    } IRegTreeItemVtbl;

    interface IRegTreeItem
    {
        CONST_VTBL struct IRegTreeItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRegTreeItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRegTreeItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRegTreeItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRegTreeItem_GetCheckState(This,pbCheck)	\
    ( (This)->lpVtbl -> GetCheckState(This,pbCheck) ) 

#define IRegTreeItem_SetCheckState(This,bCheck)	\
    ( (This)->lpVtbl -> SetCheckState(This,bCheck) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRegTreeItem_GetCheckState_Proxy( 
    IRegTreeItem * This,
    /* [out] */ BOOL *pbCheck);


void __RPC_STUB IRegTreeItem_GetCheckState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegTreeItem_SetCheckState_Proxy( 
    IRegTreeItem * This,
    /* [in] */ BOOL bCheck);


void __RPC_STUB IRegTreeItem_SetCheckState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRegTreeItem_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0295 */
/* [local] */ 


enum tagMENUPOPUPSELECT
    {	MPOS_EXECUTE	= 0,
	MPOS_FULLCANCEL	= ( MPOS_EXECUTE + 1 ) ,
	MPOS_CANCELLEVEL	= ( MPOS_FULLCANCEL + 1 ) ,
	MPOS_SELECTLEFT	= ( MPOS_CANCELLEVEL + 1 ) ,
	MPOS_SELECTRIGHT	= ( MPOS_SELECTLEFT + 1 ) ,
	MPOS_CHILDTRACKING	= ( MPOS_SELECTRIGHT + 1 ) 
    } ;

enum tagMENUPOPUPPOPUPFLAGS
    {	MPPF_SETFOCUS	= 0x1,
	MPPF_INITIALSELECT	= 0x2,
	MPPF_NOANIMATE	= 0x4,
	MPPF_KEYBOARD	= 0x10,
	MPPF_REPOSITION	= 0x20,
	MPPF_FORCEZORDER	= 0x40,
	MPPF_FINALSELECT	= 0x80,
	MPPF_TOP	= 0x20000000,
	MPPF_LEFT	= 0x40000000,
	MPPF_RIGHT	= 0x60000000,
	MPPF_BOTTOM	= 0x80000000,
	MPPF_POS_MASK	= 0xe0000000,
	MPPF_ALIGN_LEFT	= 0x2000000,
	MPPF_ALIGN_RIGHT	= 0x4000000
    } ;
typedef int MP_POPUPFLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0295_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0295_v0_0_s_ifspec;

#ifndef __IMenuPopup_INTERFACE_DEFINED__
#define __IMenuPopup_INTERFACE_DEFINED__

/* interface IMenuPopup */
/* [local][unique][object][uuid] */ 


EXTERN_C const IID IID_IMenuPopup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D1E7AFEB-6A2E-11d0-8C78-00C04FD918B4")
    IMenuPopup : public IDeskBar
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Popup( 
            /* [in] */ POINTL *ppt,
            /* [in] */ RECTL *prcExclude,
            MP_POPUPFLAGS dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnSelect( 
            DWORD dwSelectType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSubMenu( 
            /* [in] */ IMenuPopup *pmp,
            BOOL fSet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMenuPopupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMenuPopup * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMenuPopup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMenuPopup * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IMenuPopup * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *ContextSensitiveHelp )( 
            IMenuPopup * This,
            /* [in] */ BOOL fEnterMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetClient )( 
            IMenuPopup * This,
            /* [in] */ IUnknown *punkClient);
        
        HRESULT ( STDMETHODCALLTYPE *GetClient )( 
            IMenuPopup * This,
            /* [out] */ IUnknown **ppunkClient);
        
        HRESULT ( STDMETHODCALLTYPE *OnPosRectChangeDB )( 
            IMenuPopup * This,
            /* [in] */ LPRECT prc);
        
        HRESULT ( STDMETHODCALLTYPE *Popup )( 
            IMenuPopup * This,
            /* [in] */ POINTL *ppt,
            /* [in] */ RECTL *prcExclude,
            MP_POPUPFLAGS dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *OnSelect )( 
            IMenuPopup * This,
            DWORD dwSelectType);
        
        HRESULT ( STDMETHODCALLTYPE *SetSubMenu )( 
            IMenuPopup * This,
            /* [in] */ IMenuPopup *pmp,
            BOOL fSet);
        
        END_INTERFACE
    } IMenuPopupVtbl;

    interface IMenuPopup
    {
        CONST_VTBL struct IMenuPopupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMenuPopup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMenuPopup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMenuPopup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMenuPopup_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IMenuPopup_ContextSensitiveHelp(This,fEnterMode)	\
    ( (This)->lpVtbl -> ContextSensitiveHelp(This,fEnterMode) ) 


#define IMenuPopup_SetClient(This,punkClient)	\
    ( (This)->lpVtbl -> SetClient(This,punkClient) ) 

#define IMenuPopup_GetClient(This,ppunkClient)	\
    ( (This)->lpVtbl -> GetClient(This,ppunkClient) ) 

#define IMenuPopup_OnPosRectChangeDB(This,prc)	\
    ( (This)->lpVtbl -> OnPosRectChangeDB(This,prc) ) 


#define IMenuPopup_Popup(This,ppt,prcExclude,dwFlags)	\
    ( (This)->lpVtbl -> Popup(This,ppt,prcExclude,dwFlags) ) 

#define IMenuPopup_OnSelect(This,dwSelectType)	\
    ( (This)->lpVtbl -> OnSelect(This,dwSelectType) ) 

#define IMenuPopup_SetSubMenu(This,pmp,fSet)	\
    ( (This)->lpVtbl -> SetSubMenu(This,pmp,fSet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMenuPopup_Popup_Proxy( 
    IMenuPopup * This,
    /* [in] */ POINTL *ppt,
    /* [in] */ RECTL *prcExclude,
    MP_POPUPFLAGS dwFlags);


void __RPC_STUB IMenuPopup_Popup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMenuPopup_OnSelect_Proxy( 
    IMenuPopup * This,
    DWORD dwSelectType);


void __RPC_STUB IMenuPopup_OnSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMenuPopup_SetSubMenu_Proxy( 
    IMenuPopup * This,
    /* [in] */ IMenuPopup *pmp,
    BOOL fSet);


void __RPC_STUB IMenuPopup_SetSubMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMenuPopup_INTERFACE_DEFINED__ */


#ifndef __IImageRecompress_INTERFACE_DEFINED__
#define __IImageRecompress_INTERFACE_DEFINED__

/* interface IImageRecompress */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IImageRecompress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("505f1513-6b3e-4892-a272-59f8889a4d3e")
    IImageRecompress : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RecompressImage( 
            IShellItem *psi,
            int cx,
            int cy,
            int iQuality,
            IStorage *pstg,
            IStream **ppstrmOut) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageRecompressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImageRecompress * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImageRecompress * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImageRecompress * This);
        
        HRESULT ( STDMETHODCALLTYPE *RecompressImage )( 
            IImageRecompress * This,
            IShellItem *psi,
            int cx,
            int cy,
            int iQuality,
            IStorage *pstg,
            IStream **ppstrmOut);
        
        END_INTERFACE
    } IImageRecompressVtbl;

    interface IImageRecompress
    {
        CONST_VTBL struct IImageRecompressVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageRecompress_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImageRecompress_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImageRecompress_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImageRecompress_RecompressImage(This,psi,cx,cy,iQuality,pstg,ppstrmOut)	\
    ( (This)->lpVtbl -> RecompressImage(This,psi,cx,cy,iQuality,pstg,ppstrmOut) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageRecompress_RecompressImage_Proxy( 
    IImageRecompress * This,
    IShellItem *psi,
    int cx,
    int cy,
    int iQuality,
    IStorage *pstg,
    IStream **ppstrmOut);


void __RPC_STUB IImageRecompress_RecompressImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageRecompress_INTERFACE_DEFINED__ */


#ifndef __IDefViewSafety_INTERFACE_DEFINED__
#define __IDefViewSafety_INTERFACE_DEFINED__

/* interface IDefViewSafety */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IDefViewSafety;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A93B3FB-4E75-4c74-871A-2CDA667F39A5")
    IDefViewSafety : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsSafePage( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDefViewSafetyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDefViewSafety * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDefViewSafety * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDefViewSafety * This);
        
        HRESULT ( STDMETHODCALLTYPE *IsSafePage )( 
            IDefViewSafety * This);
        
        END_INTERFACE
    } IDefViewSafetyVtbl;

    interface IDefViewSafety
    {
        CONST_VTBL struct IDefViewSafetyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDefViewSafety_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDefViewSafety_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDefViewSafety_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDefViewSafety_IsSafePage(This)	\
    ( (This)->lpVtbl -> IsSafePage(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDefViewSafety_IsSafePage_Proxy( 
    IDefViewSafety * This);


void __RPC_STUB IDefViewSafety_IsSafePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDefViewSafety_INTERFACE_DEFINED__ */


#ifndef __IContextMenuSite_INTERFACE_DEFINED__
#define __IContextMenuSite_INTERFACE_DEFINED__

/* interface IContextMenuSite */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IContextMenuSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0811AEBE-0B87-4C54-9E72-548CF649016B")
    IContextMenuSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DoContextMenuPopup( 
            /* [in] */ IUnknown *punkContextMenu,
            /* [in] */ UINT fFlags,
            /* [in] */ POINT pt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IContextMenuSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IContextMenuSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IContextMenuSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IContextMenuSite * This);
        
        HRESULT ( STDMETHODCALLTYPE *DoContextMenuPopup )( 
            IContextMenuSite * This,
            /* [in] */ IUnknown *punkContextMenu,
            /* [in] */ UINT fFlags,
            /* [in] */ POINT pt);
        
        END_INTERFACE
    } IContextMenuSiteVtbl;

    interface IContextMenuSite
    {
        CONST_VTBL struct IContextMenuSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IContextMenuSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IContextMenuSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IContextMenuSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IContextMenuSite_DoContextMenuPopup(This,punkContextMenu,fFlags,pt)	\
    ( (This)->lpVtbl -> DoContextMenuPopup(This,punkContextMenu,fFlags,pt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IContextMenuSite_DoContextMenuPopup_Proxy( 
    IContextMenuSite * This,
    /* [in] */ IUnknown *punkContextMenu,
    /* [in] */ UINT fFlags,
    /* [in] */ POINT pt);


void __RPC_STUB IContextMenuSite_DoContextMenuPopup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IContextMenuSite_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0299 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagKEYWORD_SELSTATE
    {	KEYWORD_SELSTATE_UNSELECTED	= 0,
	KEYWORD_SELSTATE_SELECTED	= 0x1,
	KEYWORD_SELSTATE_INDETERMINATE	= 0x2
    } 	KEYWORD_SELSTATE;

typedef struct tagKEYWORD
    {
    BSTR bstrKeyword;
    KEYWORD_SELSTATE nSelectionState;
    } 	KEYWORD;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0299_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0299_v0_0_s_ifspec;

#ifndef __IEnumKeywords_INTERFACE_DEFINED__
#define __IEnumKeywords_INTERFACE_DEFINED__

/* interface IEnumKeywords */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IEnumKeywords;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("847B7DC1-E7EB-44d4-A830-30D933ED6312")
    IEnumKeywords : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][out] */ KEYWORD *pKeywords,
            /* [out] */ ULONG *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumKeywords **ppEnumKeywords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumKeywordsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumKeywords * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumKeywords * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumKeywords * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumKeywords * This,
            /* [in] */ ULONG celt,
            /* [size_is][out] */ KEYWORD *pKeywords,
            /* [out] */ ULONG *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumKeywords * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumKeywords * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumKeywords * This,
            /* [retval][out] */ IEnumKeywords **ppEnumKeywords);
        
        END_INTERFACE
    } IEnumKeywordsVtbl;

    interface IEnumKeywords
    {
        CONST_VTBL struct IEnumKeywordsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumKeywords_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumKeywords_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumKeywords_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumKeywords_Next(This,celt,pKeywords,pcFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,pKeywords,pcFetched) ) 

#define IEnumKeywords_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumKeywords_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumKeywords_Clone(This,ppEnumKeywords)	\
    ( (This)->lpVtbl -> Clone(This,ppEnumKeywords) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumKeywords_Next_Proxy( 
    IEnumKeywords * This,
    /* [in] */ ULONG celt,
    /* [size_is][out] */ KEYWORD *pKeywords,
    /* [out] */ ULONG *pcFetched);


void __RPC_STUB IEnumKeywords_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumKeywords_Reset_Proxy( 
    IEnumKeywords * This);


void __RPC_STUB IEnumKeywords_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumKeywords_Skip_Proxy( 
    IEnumKeywords * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumKeywords_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumKeywords_Clone_Proxy( 
    IEnumKeywords * This,
    /* [retval][out] */ IEnumKeywords **ppEnumKeywords);


void __RPC_STUB IEnumKeywords_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumKeywords_INTERFACE_DEFINED__ */


#ifndef __IKeywordList_INTERFACE_DEFINED__
#define __IKeywordList_INTERFACE_DEFINED__

/* interface IKeywordList */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IKeywordList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2619DF03-B566-44b2-B005-72240980902B")
    IKeywordList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDelimiter( 
            /* [in] */ BOOL bCanonical,
            /* [out][in] */ BSTR *pbstrDelimiter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Prepend( 
            /* [in] */ LPCWSTR pwszKeyword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ LPCWSTR pwszKeyword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ LPCWSTR pwszKeyword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSelectionState( 
            /* [in] */ LPCWSTR pwszKeyword,
            /* [in] */ KEYWORD_SELSTATE nSelectionState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectionState( 
            /* [in] */ LPCWSTR pwszKeyword,
            /* [out][in] */ KEYWORD_SELSTATE *pnSelectionState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitFromDefaultKeywords( 
            /* [in] */ GUID *pKeywordSet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitFromString( 
            /* [in] */ LPCWSTR pwszKeywords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Merge( 
            /* [in] */ IKeywordList *pKeywordList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Apply( 
            /* [in] */ IKeywordList *pKeywordList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToString( 
            /* [out][in] */ BSTR *pbstrKeywords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateKeywords( 
            /* [out][in] */ IEnumKeywords **ppEnumKeywords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKeywordListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IKeywordList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IKeywordList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IKeywordList * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetDelimiter )( 
            IKeywordList * This,
            /* [in] */ BOOL bCanonical,
            /* [out][in] */ BSTR *pbstrDelimiter);
        
        HRESULT ( STDMETHODCALLTYPE *Prepend )( 
            IKeywordList * This,
            /* [in] */ LPCWSTR pwszKeyword);
        
        HRESULT ( STDMETHODCALLTYPE *Append )( 
            IKeywordList * This,
            /* [in] */ LPCWSTR pwszKeyword);
        
        HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IKeywordList * This,
            /* [in] */ LPCWSTR pwszKeyword);
        
        HRESULT ( STDMETHODCALLTYPE *SetSelectionState )( 
            IKeywordList * This,
            /* [in] */ LPCWSTR pwszKeyword,
            /* [in] */ KEYWORD_SELSTATE nSelectionState);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectionState )( 
            IKeywordList * This,
            /* [in] */ LPCWSTR pwszKeyword,
            /* [out][in] */ KEYWORD_SELSTATE *pnSelectionState);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IKeywordList * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitFromDefaultKeywords )( 
            IKeywordList * This,
            /* [in] */ GUID *pKeywordSet);
        
        HRESULT ( STDMETHODCALLTYPE *InitFromString )( 
            IKeywordList * This,
            /* [in] */ LPCWSTR pwszKeywords);
        
        HRESULT ( STDMETHODCALLTYPE *Merge )( 
            IKeywordList * This,
            /* [in] */ IKeywordList *pKeywordList);
        
        HRESULT ( STDMETHODCALLTYPE *Apply )( 
            IKeywordList * This,
            /* [in] */ IKeywordList *pKeywordList);
        
        HRESULT ( STDMETHODCALLTYPE *ToString )( 
            IKeywordList * This,
            /* [out][in] */ BSTR *pbstrKeywords);
        
        HRESULT ( STDMETHODCALLTYPE *EnumerateKeywords )( 
            IKeywordList * This,
            /* [out][in] */ IEnumKeywords **ppEnumKeywords);
        
        END_INTERFACE
    } IKeywordListVtbl;

    interface IKeywordList
    {
        CONST_VTBL struct IKeywordListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKeywordList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IKeywordList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IKeywordList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IKeywordList_GetDelimiter(This,bCanonical,pbstrDelimiter)	\
    ( (This)->lpVtbl -> GetDelimiter(This,bCanonical,pbstrDelimiter) ) 

#define IKeywordList_Prepend(This,pwszKeyword)	\
    ( (This)->lpVtbl -> Prepend(This,pwszKeyword) ) 

#define IKeywordList_Append(This,pwszKeyword)	\
    ( (This)->lpVtbl -> Append(This,pwszKeyword) ) 

#define IKeywordList_Remove(This,pwszKeyword)	\
    ( (This)->lpVtbl -> Remove(This,pwszKeyword) ) 

#define IKeywordList_SetSelectionState(This,pwszKeyword,nSelectionState)	\
    ( (This)->lpVtbl -> SetSelectionState(This,pwszKeyword,nSelectionState) ) 

#define IKeywordList_GetSelectionState(This,pwszKeyword,pnSelectionState)	\
    ( (This)->lpVtbl -> GetSelectionState(This,pwszKeyword,pnSelectionState) ) 

#define IKeywordList_RemoveAll(This)	\
    ( (This)->lpVtbl -> RemoveAll(This) ) 

#define IKeywordList_InitFromDefaultKeywords(This,pKeywordSet)	\
    ( (This)->lpVtbl -> InitFromDefaultKeywords(This,pKeywordSet) ) 

#define IKeywordList_InitFromString(This,pwszKeywords)	\
    ( (This)->lpVtbl -> InitFromString(This,pwszKeywords) ) 

#define IKeywordList_Merge(This,pKeywordList)	\
    ( (This)->lpVtbl -> Merge(This,pKeywordList) ) 

#define IKeywordList_Apply(This,pKeywordList)	\
    ( (This)->lpVtbl -> Apply(This,pKeywordList) ) 

#define IKeywordList_ToString(This,pbstrKeywords)	\
    ( (This)->lpVtbl -> ToString(This,pbstrKeywords) ) 

#define IKeywordList_EnumerateKeywords(This,ppEnumKeywords)	\
    ( (This)->lpVtbl -> EnumerateKeywords(This,ppEnumKeywords) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IKeywordList_GetDelimiter_Proxy( 
    IKeywordList * This,
    /* [in] */ BOOL bCanonical,
    /* [out][in] */ BSTR *pbstrDelimiter);


void __RPC_STUB IKeywordList_GetDelimiter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_Prepend_Proxy( 
    IKeywordList * This,
    /* [in] */ LPCWSTR pwszKeyword);


void __RPC_STUB IKeywordList_Prepend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_Append_Proxy( 
    IKeywordList * This,
    /* [in] */ LPCWSTR pwszKeyword);


void __RPC_STUB IKeywordList_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_Remove_Proxy( 
    IKeywordList * This,
    /* [in] */ LPCWSTR pwszKeyword);


void __RPC_STUB IKeywordList_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_SetSelectionState_Proxy( 
    IKeywordList * This,
    /* [in] */ LPCWSTR pwszKeyword,
    /* [in] */ KEYWORD_SELSTATE nSelectionState);


void __RPC_STUB IKeywordList_SetSelectionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_GetSelectionState_Proxy( 
    IKeywordList * This,
    /* [in] */ LPCWSTR pwszKeyword,
    /* [out][in] */ KEYWORD_SELSTATE *pnSelectionState);


void __RPC_STUB IKeywordList_GetSelectionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_RemoveAll_Proxy( 
    IKeywordList * This);


void __RPC_STUB IKeywordList_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_InitFromDefaultKeywords_Proxy( 
    IKeywordList * This,
    /* [in] */ GUID *pKeywordSet);


void __RPC_STUB IKeywordList_InitFromDefaultKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_InitFromString_Proxy( 
    IKeywordList * This,
    /* [in] */ LPCWSTR pwszKeywords);


void __RPC_STUB IKeywordList_InitFromString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_Merge_Proxy( 
    IKeywordList * This,
    /* [in] */ IKeywordList *pKeywordList);


void __RPC_STUB IKeywordList_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_Apply_Proxy( 
    IKeywordList * This,
    /* [in] */ IKeywordList *pKeywordList);


void __RPC_STUB IKeywordList_Apply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_ToString_Proxy( 
    IKeywordList * This,
    /* [out][in] */ BSTR *pbstrKeywords);


void __RPC_STUB IKeywordList_ToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKeywordList_EnumerateKeywords_Proxy( 
    IKeywordList * This,
    /* [out][in] */ IEnumKeywords **ppEnumKeywords);


void __RPC_STUB IKeywordList_EnumerateKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKeywordList_INTERFACE_DEFINED__ */


#ifndef __IModalKeywordEditor_INTERFACE_DEFINED__
#define __IModalKeywordEditor_INTERFACE_DEFINED__

/* interface IModalKeywordEditor */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IModalKeywordEditor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B670AD2-7C3C-4FE8-A0BC-6B2985191C98")
    IModalKeywordEditor : public IModalWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IKeywordList *pKeywordList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetKeywords( 
            /* [out][in] */ IKeywordList **ppKeywordList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModalKeywordEditorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IModalKeywordEditor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IModalKeywordEditor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IModalKeywordEditor * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IModalKeywordEditor * This,
            /* [in] */ HWND hwndParent);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IModalKeywordEditor * This,
            /* [in] */ IKeywordList *pKeywordList);
        
        HRESULT ( STDMETHODCALLTYPE *GetKeywords )( 
            IModalKeywordEditor * This,
            /* [out][in] */ IKeywordList **ppKeywordList);
        
        END_INTERFACE
    } IModalKeywordEditorVtbl;

    interface IModalKeywordEditor
    {
        CONST_VTBL struct IModalKeywordEditorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModalKeywordEditor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IModalKeywordEditor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IModalKeywordEditor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IModalKeywordEditor_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 


#define IModalKeywordEditor_Initialize(This,pKeywordList)	\
    ( (This)->lpVtbl -> Initialize(This,pKeywordList) ) 

#define IModalKeywordEditor_GetKeywords(This,ppKeywordList)	\
    ( (This)->lpVtbl -> GetKeywords(This,ppKeywordList) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IModalKeywordEditor_Initialize_Proxy( 
    IModalKeywordEditor * This,
    /* [in] */ IKeywordList *pKeywordList);


void __RPC_STUB IModalKeywordEditor_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModalKeywordEditor_GetKeywords_Proxy( 
    IModalKeywordEditor * This,
    /* [out][in] */ IKeywordList **ppKeywordList);


void __RPC_STUB IModalKeywordEditor_GetKeywords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModalKeywordEditor_INTERFACE_DEFINED__ */


#ifndef __IDataConsumerNotify_INTERFACE_DEFINED__
#define __IDataConsumerNotify_INTERFACE_DEFINED__

/* interface IDataConsumerNotify */
/* [object][unique][uuid][local] */ 


EXTERN_C const IID IID_IDataConsumerNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98206e73-f2e6-455a-9332-17b41988a355")
    IDataConsumerNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UpdateViewStrings( 
            /* [in] */ DWORD dwFlags,
            /* [size_is][in] */ BSTR *rgBSTR,
            /* [in] */ DWORD cBSTR) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateViewByteArrays( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ BYTE **rgpData,
            /* [in] */ DWORD *rgcbLen,
            /* [in] */ DWORD dwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateViewVariants( 
            /* [in] */ DWORD dwFlags,
            /* [size_is][in] */ VARIANT *pvData,
            /* [in] */ DWORD dwCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDataConsumerNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataConsumerNotify * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataConsumerNotify * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataConsumerNotify * This);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateViewStrings )( 
            IDataConsumerNotify * This,
            /* [in] */ DWORD dwFlags,
            /* [size_is][in] */ BSTR *rgBSTR,
            /* [in] */ DWORD cBSTR);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateViewByteArrays )( 
            IDataConsumerNotify * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BYTE **rgpData,
            /* [in] */ DWORD *rgcbLen,
            /* [in] */ DWORD dwCount);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateViewVariants )( 
            IDataConsumerNotify * This,
            /* [in] */ DWORD dwFlags,
            /* [size_is][in] */ VARIANT *pvData,
            /* [in] */ DWORD dwCount);
        
        END_INTERFACE
    } IDataConsumerNotifyVtbl;

    interface IDataConsumerNotify
    {
        CONST_VTBL struct IDataConsumerNotifyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataConsumerNotify_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataConsumerNotify_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataConsumerNotify_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataConsumerNotify_UpdateViewStrings(This,dwFlags,rgBSTR,cBSTR)	\
    ( (This)->lpVtbl -> UpdateViewStrings(This,dwFlags,rgBSTR,cBSTR) ) 

#define IDataConsumerNotify_UpdateViewByteArrays(This,dwFlags,rgpData,rgcbLen,dwCount)	\
    ( (This)->lpVtbl -> UpdateViewByteArrays(This,dwFlags,rgpData,rgcbLen,dwCount) ) 

#define IDataConsumerNotify_UpdateViewVariants(This,dwFlags,pvData,dwCount)	\
    ( (This)->lpVtbl -> UpdateViewVariants(This,dwFlags,pvData,dwCount) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDataConsumerNotify_UpdateViewStrings_Proxy( 
    IDataConsumerNotify * This,
    /* [in] */ DWORD dwFlags,
    /* [size_is][in] */ BSTR *rgBSTR,
    /* [in] */ DWORD cBSTR);


void __RPC_STUB IDataConsumerNotify_UpdateViewStrings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataConsumerNotify_UpdateViewByteArrays_Proxy( 
    IDataConsumerNotify * This,
    /* [in] */ DWORD dwFlags,
    /* [in] */ BYTE **rgpData,
    /* [in] */ DWORD *rgcbLen,
    /* [in] */ DWORD dwCount);


void __RPC_STUB IDataConsumerNotify_UpdateViewByteArrays_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataConsumerNotify_UpdateViewVariants_Proxy( 
    IDataConsumerNotify * This,
    /* [in] */ DWORD dwFlags,
    /* [size_is][in] */ VARIANT *pvData,
    /* [in] */ DWORD dwCount);


void __RPC_STUB IDataConsumerNotify_UpdateViewVariants_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDataConsumerNotify_INTERFACE_DEFINED__ */


#ifndef __IDataSourceScheduler_INTERFACE_DEFINED__
#define __IDataSourceScheduler_INTERFACE_DEFINED__

/* interface IDataSourceScheduler */
/* [object][unique][uuid][local] */ 


EXTERN_C const IID IID_IDataSourceScheduler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B9ED45E-6D3F-475b-B18E-CD32D5D8BEEF")
    IDataSourceScheduler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetTimer( 
            /* [in] */ DWORD dwDataTimeoutSecs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE KillTimer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddEventHandle( 
            /* [in] */ HANDLE hEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveEventHandle( 
            /* [in] */ HANDLE hEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateMessageWindow( 
            /* [in] */ LPCWSTR pstrWindowClass,
            /* [out] */ HWND *phwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveMessageWindow( 
            /* [in] */ HWND hwnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDataSourceSchedulerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDataSourceScheduler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDataSourceScheduler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDataSourceScheduler * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetTimer )( 
            IDataSourceScheduler * This,
            /* [in] */ DWORD dwDataTimeoutSecs);
        
        HRESULT ( STDMETHODCALLTYPE *KillTimer )( 
            IDataSourceScheduler * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddEventHandle )( 
            IDataSourceScheduler * This,
            /* [in] */ HANDLE hEvent);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveEventHandle )( 
            IDataSourceScheduler * This,
            /* [in] */ HANDLE hEvent);
        
        HRESULT ( STDMETHODCALLTYPE *CreateMessageWindow )( 
            IDataSourceScheduler * This,
            /* [in] */ LPCWSTR pstrWindowClass,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveMessageWindow )( 
            IDataSourceScheduler * This,
            /* [in] */ HWND hwnd);
        
        END_INTERFACE
    } IDataSourceSchedulerVtbl;

    interface IDataSourceScheduler
    {
        CONST_VTBL struct IDataSourceSchedulerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDataSourceScheduler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDataSourceScheduler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDataSourceScheduler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDataSourceScheduler_SetTimer(This,dwDataTimeoutSecs)	\
    ( (This)->lpVtbl -> SetTimer(This,dwDataTimeoutSecs) ) 

#define IDataSourceScheduler_KillTimer(This)	\
    ( (This)->lpVtbl -> KillTimer(This) ) 

#define IDataSourceScheduler_AddEventHandle(This,hEvent)	\
    ( (This)->lpVtbl -> AddEventHandle(This,hEvent) ) 

#define IDataSourceScheduler_RemoveEventHandle(This,hEvent)	\
    ( (This)->lpVtbl -> RemoveEventHandle(This,hEvent) ) 

#define IDataSourceScheduler_CreateMessageWindow(This,pstrWindowClass,phwnd)	\
    ( (This)->lpVtbl -> CreateMessageWindow(This,pstrWindowClass,phwnd) ) 

#define IDataSourceScheduler_RemoveMessageWindow(This,hwnd)	\
    ( (This)->lpVtbl -> RemoveMessageWindow(This,hwnd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDataSourceScheduler_SetTimer_Proxy( 
    IDataSourceScheduler * This,
    /* [in] */ DWORD dwDataTimeoutSecs);


void __RPC_STUB IDataSourceScheduler_SetTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataSourceScheduler_KillTimer_Proxy( 
    IDataSourceScheduler * This);


void __RPC_STUB IDataSourceScheduler_KillTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataSourceScheduler_AddEventHandle_Proxy( 
    IDataSourceScheduler * This,
    /* [in] */ HANDLE hEvent);


void __RPC_STUB IDataSourceScheduler_AddEventHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataSourceScheduler_RemoveEventHandle_Proxy( 
    IDataSourceScheduler * This,
    /* [in] */ HANDLE hEvent);


void __RPC_STUB IDataSourceScheduler_RemoveEventHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataSourceScheduler_CreateMessageWindow_Proxy( 
    IDataSourceScheduler * This,
    /* [in] */ LPCWSTR pstrWindowClass,
    /* [out] */ HWND *phwnd);


void __RPC_STUB IDataSourceScheduler_CreateMessageWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDataSourceScheduler_RemoveMessageWindow_Proxy( 
    IDataSourceScheduler * This,
    /* [in] */ HWND hwnd);


void __RPC_STUB IDataSourceScheduler_RemoveMessageWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDataSourceScheduler_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0304 */
/* [local] */ 

typedef /* [helpstring] */ 
enum tagModuleDataSourceEventType
    {	MDS_TIMER_TICK	= 0,
	MDS_HANDLE_SIGNALED	= ( MDS_TIMER_TICK + 1 ) ,
	MDS_MESSAGE	= ( MDS_HANDLE_SIGNALED + 1 ) ,
	MDS_STATE_CHANGE	= ( MDS_MESSAGE + 1 ) 
    } 	ModuleDataSourceEventType;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0304_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0304_v0_0_s_ifspec;

#ifndef __IModuleDataSource_INTERFACE_DEFINED__
#define __IModuleDataSource_INTERFACE_DEFINED__

/* interface IModuleDataSource */
/* [object][unique][uuid] */ 


EXTERN_C const IID IID_IModuleDataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("898046a4-ce79-4c73-a650-ac266fe55ac4")
    IModuleDataSource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [unique][in] */ LPCWSTR strInitString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [in] */ ModuleDataSourceEventType evt,
            /* [in] */ UINT uMsg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyFromModuleView( 
            /* [size_is][in] */ LPCWSTR *rgStrings,
            /* [in] */ DWORD dwCount,
            /* [out] */ DWORD *pdwStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModuleDataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IModuleDataSource * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IModuleDataSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IModuleDataSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IModuleDataSource * This,
            /* [unique][in] */ LPCWSTR strInitString);
        
        HRESULT ( STDMETHODCALLTYPE *Shutdown )( 
            IModuleDataSource * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFlags )( 
            IModuleDataSource * This,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *OnEvent )( 
            IModuleDataSource * This,
            /* [in] */ ModuleDataSourceEventType evt,
            /* [in] */ UINT uMsg,
            /* [in] */ WPARAM wParam,
            /* [in] */ LPARAM lParam);
        
        HRESULT ( STDMETHODCALLTYPE *NotifyFromModuleView )( 
            IModuleDataSource * This,
            /* [size_is][in] */ LPCWSTR *rgStrings,
            /* [in] */ DWORD dwCount,
            /* [out] */ DWORD *pdwStatus);
        
        END_INTERFACE
    } IModuleDataSourceVtbl;

    interface IModuleDataSource
    {
        CONST_VTBL struct IModuleDataSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModuleDataSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IModuleDataSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IModuleDataSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IModuleDataSource_Initialize(This,strInitString)	\
    ( (This)->lpVtbl -> Initialize(This,strInitString) ) 

#define IModuleDataSource_Shutdown(This)	\
    ( (This)->lpVtbl -> Shutdown(This) ) 

#define IModuleDataSource_GetFlags(This,pdwFlags)	\
    ( (This)->lpVtbl -> GetFlags(This,pdwFlags) ) 

#define IModuleDataSource_OnEvent(This,evt,uMsg,wParam,lParam)	\
    ( (This)->lpVtbl -> OnEvent(This,evt,uMsg,wParam,lParam) ) 

#define IModuleDataSource_NotifyFromModuleView(This,rgStrings,dwCount,pdwStatus)	\
    ( (This)->lpVtbl -> NotifyFromModuleView(This,rgStrings,dwCount,pdwStatus) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IModuleDataSource_Initialize_Proxy( 
    IModuleDataSource * This,
    /* [unique][in] */ LPCWSTR strInitString);


void __RPC_STUB IModuleDataSource_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModuleDataSource_Shutdown_Proxy( 
    IModuleDataSource * This);


void __RPC_STUB IModuleDataSource_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModuleDataSource_GetFlags_Proxy( 
    IModuleDataSource * This,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IModuleDataSource_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModuleDataSource_OnEvent_Proxy( 
    IModuleDataSource * This,
    /* [in] */ ModuleDataSourceEventType evt,
    /* [in] */ UINT uMsg,
    /* [in] */ WPARAM wParam,
    /* [in] */ LPARAM lParam);


void __RPC_STUB IModuleDataSource_OnEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModuleDataSource_NotifyFromModuleView_Proxy( 
    IModuleDataSource * This,
    /* [size_is][in] */ LPCWSTR *rgStrings,
    /* [in] */ DWORD dwCount,
    /* [out] */ DWORD *pdwStatus);


void __RPC_STUB IModuleDataSource_NotifyFromModuleView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModuleDataSource_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0305 */
/* [local] */ 

typedef /* [helpstring] */ 
enum tagFILE_USAGE_TYPE
    {	FUT_PLAYING	= 0,
	FUT_EDITING	= ( FUT_PLAYING + 1 ) ,
	FUT_GENERIC	= ( FUT_EDITING + 1 ) 
    } 	FILE_USAGE_TYPE;

#define OF_CAP_CANSWITCHTO     0x0001
#define OF_CAP_CANCLOSE        0x0002


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0305_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0305_v0_0_s_ifspec;

#ifndef __IOpenFile_INTERFACE_DEFINED__
#define __IOpenFile_INTERFACE_DEFINED__

/* interface IOpenFile */
/* [object][unique][uuid] */ 


EXTERN_C const IID IID_IOpenFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64a1cbf0-3a1a-4461-9158-376969693950")
    IOpenFile : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAppName( 
            /* [string][out] */ LPWSTR *ppszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUsage( 
            /* [out] */ FILE_USAGE_TYPE *pfut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCapabilities( 
            /* [out] */ DWORD *pdwCapFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSwitchToHWND( 
            /* [out] */ HWND *phwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseFile( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOpenFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOpenFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOpenFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOpenFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAppName )( 
            IOpenFile * This,
            /* [string][out] */ LPWSTR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetUsage )( 
            IOpenFile * This,
            /* [out] */ FILE_USAGE_TYPE *pfut);
        
        HRESULT ( STDMETHODCALLTYPE *GetCapabilities )( 
            IOpenFile * This,
            /* [out] */ DWORD *pdwCapFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetSwitchToHWND )( 
            IOpenFile * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *CloseFile )( 
            IOpenFile * This);
        
        END_INTERFACE
    } IOpenFileVtbl;

    interface IOpenFile
    {
        CONST_VTBL struct IOpenFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOpenFile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOpenFile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOpenFile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOpenFile_GetAppName(This,ppszName)	\
    ( (This)->lpVtbl -> GetAppName(This,ppszName) ) 

#define IOpenFile_GetUsage(This,pfut)	\
    ( (This)->lpVtbl -> GetUsage(This,pfut) ) 

#define IOpenFile_GetCapabilities(This,pdwCapFlags)	\
    ( (This)->lpVtbl -> GetCapabilities(This,pdwCapFlags) ) 

#define IOpenFile_GetSwitchToHWND(This,phwnd)	\
    ( (This)->lpVtbl -> GetSwitchToHWND(This,phwnd) ) 

#define IOpenFile_CloseFile(This)	\
    ( (This)->lpVtbl -> CloseFile(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOpenFile_GetAppName_Proxy( 
    IOpenFile * This,
    /* [string][out] */ LPWSTR *ppszName);


void __RPC_STUB IOpenFile_GetAppName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOpenFile_GetUsage_Proxy( 
    IOpenFile * This,
    /* [out] */ FILE_USAGE_TYPE *pfut);


void __RPC_STUB IOpenFile_GetUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOpenFile_GetCapabilities_Proxy( 
    IOpenFile * This,
    /* [out] */ DWORD *pdwCapFlags);


void __RPC_STUB IOpenFile_GetCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOpenFile_GetSwitchToHWND_Proxy( 
    IOpenFile * This,
    /* [out] */ HWND *phwnd);


void __RPC_STUB IOpenFile_GetSwitchToHWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOpenFile_CloseFile_Proxy( 
    IOpenFile * This);


void __RPC_STUB IOpenFile_CloseFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOpenFile_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0306 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0306_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0306_v0_0_s_ifspec;

#ifndef __IFileDialogEvents_INTERFACE_DEFINED__
#define __IFileDialogEvents_INTERFACE_DEFINED__

/* interface IFileDialogEvents */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFileDialogEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("721ed8c3-8c44-42a5-ba6b-c111351a9d06")
    IFileDialogEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnFileOk( 
            /* [in] */ IFileDialog *pfd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnFolderChange( 
            /* [in] */ IFileDialog *pfd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnHelp( 
            /* [in] */ IFileDialog *pfd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnSelectionChange( 
            /* [in] */ IFileDialog *pfd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnShareViolation( 
            /* [in] */ IFileDialog *pfd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnTypeChange( 
            /* [in] */ IFileDialog *pfd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileDialogEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileDialogEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileDialogEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileDialogEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnFileOk )( 
            IFileDialogEvents * This,
            /* [in] */ IFileDialog *pfd);
        
        HRESULT ( STDMETHODCALLTYPE *OnFolderChange )( 
            IFileDialogEvents * This,
            /* [in] */ IFileDialog *pfd);
        
        HRESULT ( STDMETHODCALLTYPE *OnHelp )( 
            IFileDialogEvents * This,
            /* [in] */ IFileDialog *pfd);
        
        HRESULT ( STDMETHODCALLTYPE *OnSelectionChange )( 
            IFileDialogEvents * This,
            /* [in] */ IFileDialog *pfd);
        
        HRESULT ( STDMETHODCALLTYPE *OnShareViolation )( 
            IFileDialogEvents * This,
            /* [in] */ IFileDialog *pfd);
        
        HRESULT ( STDMETHODCALLTYPE *OnTypeChange )( 
            IFileDialogEvents * This,
            /* [in] */ IFileDialog *pfd);
        
        END_INTERFACE
    } IFileDialogEventsVtbl;

    interface IFileDialogEvents
    {
        CONST_VTBL struct IFileDialogEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileDialogEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileDialogEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileDialogEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileDialogEvents_OnFileOk(This,pfd)	\
    ( (This)->lpVtbl -> OnFileOk(This,pfd) ) 

#define IFileDialogEvents_OnFolderChange(This,pfd)	\
    ( (This)->lpVtbl -> OnFolderChange(This,pfd) ) 

#define IFileDialogEvents_OnHelp(This,pfd)	\
    ( (This)->lpVtbl -> OnHelp(This,pfd) ) 

#define IFileDialogEvents_OnSelectionChange(This,pfd)	\
    ( (This)->lpVtbl -> OnSelectionChange(This,pfd) ) 

#define IFileDialogEvents_OnShareViolation(This,pfd)	\
    ( (This)->lpVtbl -> OnShareViolation(This,pfd) ) 

#define IFileDialogEvents_OnTypeChange(This,pfd)	\
    ( (This)->lpVtbl -> OnTypeChange(This,pfd) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileDialogEvents_OnFileOk_Proxy( 
    IFileDialogEvents * This,
    /* [in] */ IFileDialog *pfd);


void __RPC_STUB IFileDialogEvents_OnFileOk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogEvents_OnFolderChange_Proxy( 
    IFileDialogEvents * This,
    /* [in] */ IFileDialog *pfd);


void __RPC_STUB IFileDialogEvents_OnFolderChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogEvents_OnHelp_Proxy( 
    IFileDialogEvents * This,
    /* [in] */ IFileDialog *pfd);


void __RPC_STUB IFileDialogEvents_OnHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogEvents_OnSelectionChange_Proxy( 
    IFileDialogEvents * This,
    /* [in] */ IFileDialog *pfd);


void __RPC_STUB IFileDialogEvents_OnSelectionChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogEvents_OnShareViolation_Proxy( 
    IFileDialogEvents * This,
    /* [in] */ IFileDialog *pfd);


void __RPC_STUB IFileDialogEvents_OnShareViolation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogEvents_OnTypeChange_Proxy( 
    IFileDialogEvents * This,
    /* [in] */ IFileDialog *pfd);


void __RPC_STUB IFileDialogEvents_OnTypeChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileDialogEvents_INTERFACE_DEFINED__ */


#ifndef __IFileDialog_INTERFACE_DEFINED__
#define __IFileDialog_INTERFACE_DEFINED__

/* interface IFileDialog */
/* [unique][object][uuid] */ 


enum tagFILEOPENDIALOGOPTIONS
    {	FOS_OVERWRITEPROMPT	= 0x2,
	FOS_NOCHANGEDIR	= 0x8,
	FOS_SHOWHELP	= 0x10,
	FOS_FORCEFILESYSTEM	= 0x40,
	FOS_NOVALIDATE	= 0x100,
	FOS_ALLOWMULTISELECT	= 0x200,
	FOS_PATHMUSTEXIST	= 0x800,
	FOS_FILEMUSTEXIST	= 0x1000,
	FOS_CREATEPROMPT	= 0x2000,
	FOS_SHAREAWARE	= 0x4000,
	FOS_NOREADONLYRETURN	= 0x8000,
	FOS_NOTESTFILECREATE	= 0x10000,
	FOS_HIDEMRUPLACES	= 0x20000,
	FOS_HIDEPINNEDPLACES	= 0x40000,
	FOS_NODEREFERENCELINKS	= 0x100000,
	FOS_DONTADDTORECENT	= 0x2000000,
	FOS_FORCESHOWHIDDEN	= 0x10000000
    } ;

EXTERN_C const IID IID_IFileDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("61483B79-DE34-48b3-85C2-554DEC52290A")
    IFileDialog : public IModalWindow
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFileTypes( 
            /* [in] */ UINT cFileTypes,
            /* [size_is][in] */ const COMDLG_FILTERSPEC *rgFilterSpec) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFileTypeIndex( 
            /* [in] */ UINT iFileType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFileTypeIndex( 
            /* [out] */ UINT *piFileType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IFileDialogEvents *pfde,
            /* [out] */ DWORD *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( 
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOptions( 
            /* [in] */ DWORD fos) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOptions( 
            /* [out] */ DWORD *pfos) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultFolder( 
            /* [in] */ IShellItem *psi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFolder( 
            /* [in] */ IShellItem *psi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFolder( 
            /* [out] */ IShellItem **ppsi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentSelection( 
            /* [out] */ IShellItem **ppsi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFileName( 
            /* [string][out] */ WCHAR **pszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTitle( 
            /* [string][in] */ LPCWSTR pszTitle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOkButtonLabel( 
            /* [string][in] */ LPCWSTR pszText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFileNameLabel( 
            /* [string][in] */ LPCWSTR pszLabel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetResult( 
            /* [out] */ IShellItem **ppsi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddPlace( 
            /* [in] */ IShellItem *psi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultExtension( 
            /* [in] */ LPCWSTR pszDefaultExtension) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileDialog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileDialog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileDialog * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IFileDialog * This,
            /* [in] */ HWND hwndParent);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileTypes )( 
            IFileDialog * This,
            /* [in] */ UINT cFileTypes,
            /* [size_is][in] */ const COMDLG_FILTERSPEC *rgFilterSpec);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileTypeIndex )( 
            IFileDialog * This,
            /* [in] */ UINT iFileType);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileTypeIndex )( 
            IFileDialog * This,
            /* [out] */ UINT *piFileType);
        
        HRESULT ( STDMETHODCALLTYPE *Advise )( 
            IFileDialog * This,
            /* [in] */ IFileDialogEvents *pfde,
            /* [out] */ DWORD *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IFileDialog * This,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *SetOptions )( 
            IFileDialog * This,
            /* [in] */ DWORD fos);
        
        HRESULT ( STDMETHODCALLTYPE *GetOptions )( 
            IFileDialog * This,
            /* [out] */ DWORD *pfos);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultFolder )( 
            IFileDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *SetFolder )( 
            IFileDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolder )( 
            IFileDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentSelection )( 
            IFileDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileName )( 
            IFileDialog * This,
            /* [string][out] */ WCHAR **pszName);
        
        HRESULT ( STDMETHODCALLTYPE *SetTitle )( 
            IFileDialog * This,
            /* [string][in] */ LPCWSTR pszTitle);
        
        HRESULT ( STDMETHODCALLTYPE *SetOkButtonLabel )( 
            IFileDialog * This,
            /* [string][in] */ LPCWSTR pszText);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileNameLabel )( 
            IFileDialog * This,
            /* [string][in] */ LPCWSTR pszLabel);
        
        HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            IFileDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *AddPlace )( 
            IFileDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultExtension )( 
            IFileDialog * This,
            /* [in] */ LPCWSTR pszDefaultExtension);
        
        END_INTERFACE
    } IFileDialogVtbl;

    interface IFileDialog
    {
        CONST_VTBL struct IFileDialogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileDialog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileDialog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileDialog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileDialog_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 


#define IFileDialog_SetFileTypes(This,cFileTypes,rgFilterSpec)	\
    ( (This)->lpVtbl -> SetFileTypes(This,cFileTypes,rgFilterSpec) ) 

#define IFileDialog_SetFileTypeIndex(This,iFileType)	\
    ( (This)->lpVtbl -> SetFileTypeIndex(This,iFileType) ) 

#define IFileDialog_GetFileTypeIndex(This,piFileType)	\
    ( (This)->lpVtbl -> GetFileTypeIndex(This,piFileType) ) 

#define IFileDialog_Advise(This,pfde,pdwCookie)	\
    ( (This)->lpVtbl -> Advise(This,pfde,pdwCookie) ) 

#define IFileDialog_Unadvise(This,dwCookie)	\
    ( (This)->lpVtbl -> Unadvise(This,dwCookie) ) 

#define IFileDialog_SetOptions(This,fos)	\
    ( (This)->lpVtbl -> SetOptions(This,fos) ) 

#define IFileDialog_GetOptions(This,pfos)	\
    ( (This)->lpVtbl -> GetOptions(This,pfos) ) 

#define IFileDialog_SetDefaultFolder(This,psi)	\
    ( (This)->lpVtbl -> SetDefaultFolder(This,psi) ) 

#define IFileDialog_SetFolder(This,psi)	\
    ( (This)->lpVtbl -> SetFolder(This,psi) ) 

#define IFileDialog_GetFolder(This,ppsi)	\
    ( (This)->lpVtbl -> GetFolder(This,ppsi) ) 

#define IFileDialog_GetCurrentSelection(This,ppsi)	\
    ( (This)->lpVtbl -> GetCurrentSelection(This,ppsi) ) 

#define IFileDialog_GetFileName(This,pszName)	\
    ( (This)->lpVtbl -> GetFileName(This,pszName) ) 

#define IFileDialog_SetTitle(This,pszTitle)	\
    ( (This)->lpVtbl -> SetTitle(This,pszTitle) ) 

#define IFileDialog_SetOkButtonLabel(This,pszText)	\
    ( (This)->lpVtbl -> SetOkButtonLabel(This,pszText) ) 

#define IFileDialog_SetFileNameLabel(This,pszLabel)	\
    ( (This)->lpVtbl -> SetFileNameLabel(This,pszLabel) ) 

#define IFileDialog_GetResult(This,ppsi)	\
    ( (This)->lpVtbl -> GetResult(This,ppsi) ) 

#define IFileDialog_AddPlace(This,psi)	\
    ( (This)->lpVtbl -> AddPlace(This,psi) ) 

#define IFileDialog_SetDefaultExtension(This,pszDefaultExtension)	\
    ( (This)->lpVtbl -> SetDefaultExtension(This,pszDefaultExtension) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileDialog_SetFileTypes_Proxy( 
    IFileDialog * This,
    /* [in] */ UINT cFileTypes,
    /* [size_is][in] */ const COMDLG_FILTERSPEC *rgFilterSpec);


void __RPC_STUB IFileDialog_SetFileTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetFileTypeIndex_Proxy( 
    IFileDialog * This,
    /* [in] */ UINT iFileType);


void __RPC_STUB IFileDialog_SetFileTypeIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_GetFileTypeIndex_Proxy( 
    IFileDialog * This,
    /* [out] */ UINT *piFileType);


void __RPC_STUB IFileDialog_GetFileTypeIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_Advise_Proxy( 
    IFileDialog * This,
    /* [in] */ IFileDialogEvents *pfde,
    /* [out] */ DWORD *pdwCookie);


void __RPC_STUB IFileDialog_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_Unadvise_Proxy( 
    IFileDialog * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IFileDialog_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetOptions_Proxy( 
    IFileDialog * This,
    /* [in] */ DWORD fos);


void __RPC_STUB IFileDialog_SetOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_GetOptions_Proxy( 
    IFileDialog * This,
    /* [out] */ DWORD *pfos);


void __RPC_STUB IFileDialog_GetOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetDefaultFolder_Proxy( 
    IFileDialog * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB IFileDialog_SetDefaultFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetFolder_Proxy( 
    IFileDialog * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB IFileDialog_SetFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_GetFolder_Proxy( 
    IFileDialog * This,
    /* [out] */ IShellItem **ppsi);


void __RPC_STUB IFileDialog_GetFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_GetCurrentSelection_Proxy( 
    IFileDialog * This,
    /* [out] */ IShellItem **ppsi);


void __RPC_STUB IFileDialog_GetCurrentSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_GetFileName_Proxy( 
    IFileDialog * This,
    /* [string][out] */ WCHAR **pszName);


void __RPC_STUB IFileDialog_GetFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetTitle_Proxy( 
    IFileDialog * This,
    /* [string][in] */ LPCWSTR pszTitle);


void __RPC_STUB IFileDialog_SetTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetOkButtonLabel_Proxy( 
    IFileDialog * This,
    /* [string][in] */ LPCWSTR pszText);


void __RPC_STUB IFileDialog_SetOkButtonLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetFileNameLabel_Proxy( 
    IFileDialog * This,
    /* [string][in] */ LPCWSTR pszLabel);


void __RPC_STUB IFileDialog_SetFileNameLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_GetResult_Proxy( 
    IFileDialog * This,
    /* [out] */ IShellItem **ppsi);


void __RPC_STUB IFileDialog_GetResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_AddPlace_Proxy( 
    IFileDialog * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB IFileDialog_AddPlace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialog_SetDefaultExtension_Proxy( 
    IFileDialog * This,
    /* [in] */ LPCWSTR pszDefaultExtension);


void __RPC_STUB IFileDialog_SetDefaultExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileDialog_INTERFACE_DEFINED__ */


#ifndef __IFileSaveDialog_INTERFACE_DEFINED__
#define __IFileSaveDialog_INTERFACE_DEFINED__

/* interface IFileSaveDialog */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFileSaveDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7E4FD53-13C3-4015-923F-2EE66752E918")
    IFileSaveDialog : public IFileDialog
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSaveName( 
            /* [string][in] */ LPCWSTR pszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSaveAsItem( 
            /* [in] */ IShellItem *psi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileSaveDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileSaveDialog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileSaveDialog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileSaveDialog * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IFileSaveDialog * This,
            /* [in] */ HWND hwndParent);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileTypes )( 
            IFileSaveDialog * This,
            /* [in] */ UINT cFileTypes,
            /* [size_is][in] */ const COMDLG_FILTERSPEC *rgFilterSpec);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileTypeIndex )( 
            IFileSaveDialog * This,
            /* [in] */ UINT iFileType);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileTypeIndex )( 
            IFileSaveDialog * This,
            /* [out] */ UINT *piFileType);
        
        HRESULT ( STDMETHODCALLTYPE *Advise )( 
            IFileSaveDialog * This,
            /* [in] */ IFileDialogEvents *pfde,
            /* [out] */ DWORD *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IFileSaveDialog * This,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *SetOptions )( 
            IFileSaveDialog * This,
            /* [in] */ DWORD fos);
        
        HRESULT ( STDMETHODCALLTYPE *GetOptions )( 
            IFileSaveDialog * This,
            /* [out] */ DWORD *pfos);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultFolder )( 
            IFileSaveDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *SetFolder )( 
            IFileSaveDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolder )( 
            IFileSaveDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentSelection )( 
            IFileSaveDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileName )( 
            IFileSaveDialog * This,
            /* [string][out] */ WCHAR **pszName);
        
        HRESULT ( STDMETHODCALLTYPE *SetTitle )( 
            IFileSaveDialog * This,
            /* [string][in] */ LPCWSTR pszTitle);
        
        HRESULT ( STDMETHODCALLTYPE *SetOkButtonLabel )( 
            IFileSaveDialog * This,
            /* [string][in] */ LPCWSTR pszText);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileNameLabel )( 
            IFileSaveDialog * This,
            /* [string][in] */ LPCWSTR pszLabel);
        
        HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            IFileSaveDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *AddPlace )( 
            IFileSaveDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultExtension )( 
            IFileSaveDialog * This,
            /* [in] */ LPCWSTR pszDefaultExtension);
        
        HRESULT ( STDMETHODCALLTYPE *SetSaveName )( 
            IFileSaveDialog * This,
            /* [string][in] */ LPCWSTR pszName);
        
        HRESULT ( STDMETHODCALLTYPE *SetSaveAsItem )( 
            IFileSaveDialog * This,
            /* [in] */ IShellItem *psi);
        
        END_INTERFACE
    } IFileSaveDialogVtbl;

    interface IFileSaveDialog
    {
        CONST_VTBL struct IFileSaveDialogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSaveDialog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileSaveDialog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileSaveDialog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileSaveDialog_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 


#define IFileSaveDialog_SetFileTypes(This,cFileTypes,rgFilterSpec)	\
    ( (This)->lpVtbl -> SetFileTypes(This,cFileTypes,rgFilterSpec) ) 

#define IFileSaveDialog_SetFileTypeIndex(This,iFileType)	\
    ( (This)->lpVtbl -> SetFileTypeIndex(This,iFileType) ) 

#define IFileSaveDialog_GetFileTypeIndex(This,piFileType)	\
    ( (This)->lpVtbl -> GetFileTypeIndex(This,piFileType) ) 

#define IFileSaveDialog_Advise(This,pfde,pdwCookie)	\
    ( (This)->lpVtbl -> Advise(This,pfde,pdwCookie) ) 

#define IFileSaveDialog_Unadvise(This,dwCookie)	\
    ( (This)->lpVtbl -> Unadvise(This,dwCookie) ) 

#define IFileSaveDialog_SetOptions(This,fos)	\
    ( (This)->lpVtbl -> SetOptions(This,fos) ) 

#define IFileSaveDialog_GetOptions(This,pfos)	\
    ( (This)->lpVtbl -> GetOptions(This,pfos) ) 

#define IFileSaveDialog_SetDefaultFolder(This,psi)	\
    ( (This)->lpVtbl -> SetDefaultFolder(This,psi) ) 

#define IFileSaveDialog_SetFolder(This,psi)	\
    ( (This)->lpVtbl -> SetFolder(This,psi) ) 

#define IFileSaveDialog_GetFolder(This,ppsi)	\
    ( (This)->lpVtbl -> GetFolder(This,ppsi) ) 

#define IFileSaveDialog_GetCurrentSelection(This,ppsi)	\
    ( (This)->lpVtbl -> GetCurrentSelection(This,ppsi) ) 

#define IFileSaveDialog_GetFileName(This,pszName)	\
    ( (This)->lpVtbl -> GetFileName(This,pszName) ) 

#define IFileSaveDialog_SetTitle(This,pszTitle)	\
    ( (This)->lpVtbl -> SetTitle(This,pszTitle) ) 

#define IFileSaveDialog_SetOkButtonLabel(This,pszText)	\
    ( (This)->lpVtbl -> SetOkButtonLabel(This,pszText) ) 

#define IFileSaveDialog_SetFileNameLabel(This,pszLabel)	\
    ( (This)->lpVtbl -> SetFileNameLabel(This,pszLabel) ) 

#define IFileSaveDialog_GetResult(This,ppsi)	\
    ( (This)->lpVtbl -> GetResult(This,ppsi) ) 

#define IFileSaveDialog_AddPlace(This,psi)	\
    ( (This)->lpVtbl -> AddPlace(This,psi) ) 

#define IFileSaveDialog_SetDefaultExtension(This,pszDefaultExtension)	\
    ( (This)->lpVtbl -> SetDefaultExtension(This,pszDefaultExtension) ) 


#define IFileSaveDialog_SetSaveName(This,pszName)	\
    ( (This)->lpVtbl -> SetSaveName(This,pszName) ) 

#define IFileSaveDialog_SetSaveAsItem(This,psi)	\
    ( (This)->lpVtbl -> SetSaveAsItem(This,psi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileSaveDialog_SetSaveName_Proxy( 
    IFileSaveDialog * This,
    /* [string][in] */ LPCWSTR pszName);


void __RPC_STUB IFileSaveDialog_SetSaveName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileSaveDialog_SetSaveAsItem_Proxy( 
    IFileSaveDialog * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB IFileSaveDialog_SetSaveAsItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileSaveDialog_INTERFACE_DEFINED__ */


#ifndef __IFileOpenDialog_INTERFACE_DEFINED__
#define __IFileOpenDialog_INTERFACE_DEFINED__

/* interface IFileOpenDialog */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFileOpenDialog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA68A421-6683-4e35-B343-2994FECB5634")
    IFileOpenDialog : public IFileDialog
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetResults( 
            /* [out] */ IShellItemArray **ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectedItems( 
            /* [out] */ IShellItemArray **ppsai) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileOpenDialogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileOpenDialog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileOpenDialog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileOpenDialog * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IFileOpenDialog * This,
            /* [in] */ HWND hwndParent);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileTypes )( 
            IFileOpenDialog * This,
            /* [in] */ UINT cFileTypes,
            /* [size_is][in] */ const COMDLG_FILTERSPEC *rgFilterSpec);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileTypeIndex )( 
            IFileOpenDialog * This,
            /* [in] */ UINT iFileType);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileTypeIndex )( 
            IFileOpenDialog * This,
            /* [out] */ UINT *piFileType);
        
        HRESULT ( STDMETHODCALLTYPE *Advise )( 
            IFileOpenDialog * This,
            /* [in] */ IFileDialogEvents *pfde,
            /* [out] */ DWORD *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *Unadvise )( 
            IFileOpenDialog * This,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE *SetOptions )( 
            IFileOpenDialog * This,
            /* [in] */ DWORD fos);
        
        HRESULT ( STDMETHODCALLTYPE *GetOptions )( 
            IFileOpenDialog * This,
            /* [out] */ DWORD *pfos);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultFolder )( 
            IFileOpenDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *SetFolder )( 
            IFileOpenDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolder )( 
            IFileOpenDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurrentSelection )( 
            IFileOpenDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *GetFileName )( 
            IFileOpenDialog * This,
            /* [string][out] */ WCHAR **pszName);
        
        HRESULT ( STDMETHODCALLTYPE *SetTitle )( 
            IFileOpenDialog * This,
            /* [string][in] */ LPCWSTR pszTitle);
        
        HRESULT ( STDMETHODCALLTYPE *SetOkButtonLabel )( 
            IFileOpenDialog * This,
            /* [string][in] */ LPCWSTR pszText);
        
        HRESULT ( STDMETHODCALLTYPE *SetFileNameLabel )( 
            IFileOpenDialog * This,
            /* [string][in] */ LPCWSTR pszLabel);
        
        HRESULT ( STDMETHODCALLTYPE *GetResult )( 
            IFileOpenDialog * This,
            /* [out] */ IShellItem **ppsi);
        
        HRESULT ( STDMETHODCALLTYPE *AddPlace )( 
            IFileOpenDialog * This,
            /* [in] */ IShellItem *psi);
        
        HRESULT ( STDMETHODCALLTYPE *SetDefaultExtension )( 
            IFileOpenDialog * This,
            /* [in] */ LPCWSTR pszDefaultExtension);
        
        HRESULT ( STDMETHODCALLTYPE *GetResults )( 
            IFileOpenDialog * This,
            /* [out] */ IShellItemArray **ppenum);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectedItems )( 
            IFileOpenDialog * This,
            /* [out] */ IShellItemArray **ppsai);
        
        END_INTERFACE
    } IFileOpenDialogVtbl;

    interface IFileOpenDialog
    {
        CONST_VTBL struct IFileOpenDialogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileOpenDialog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileOpenDialog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileOpenDialog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileOpenDialog_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 


#define IFileOpenDialog_SetFileTypes(This,cFileTypes,rgFilterSpec)	\
    ( (This)->lpVtbl -> SetFileTypes(This,cFileTypes,rgFilterSpec) ) 

#define IFileOpenDialog_SetFileTypeIndex(This,iFileType)	\
    ( (This)->lpVtbl -> SetFileTypeIndex(This,iFileType) ) 

#define IFileOpenDialog_GetFileTypeIndex(This,piFileType)	\
    ( (This)->lpVtbl -> GetFileTypeIndex(This,piFileType) ) 

#define IFileOpenDialog_Advise(This,pfde,pdwCookie)	\
    ( (This)->lpVtbl -> Advise(This,pfde,pdwCookie) ) 

#define IFileOpenDialog_Unadvise(This,dwCookie)	\
    ( (This)->lpVtbl -> Unadvise(This,dwCookie) ) 

#define IFileOpenDialog_SetOptions(This,fos)	\
    ( (This)->lpVtbl -> SetOptions(This,fos) ) 

#define IFileOpenDialog_GetOptions(This,pfos)	\
    ( (This)->lpVtbl -> GetOptions(This,pfos) ) 

#define IFileOpenDialog_SetDefaultFolder(This,psi)	\
    ( (This)->lpVtbl -> SetDefaultFolder(This,psi) ) 

#define IFileOpenDialog_SetFolder(This,psi)	\
    ( (This)->lpVtbl -> SetFolder(This,psi) ) 

#define IFileOpenDialog_GetFolder(This,ppsi)	\
    ( (This)->lpVtbl -> GetFolder(This,ppsi) ) 

#define IFileOpenDialog_GetCurrentSelection(This,ppsi)	\
    ( (This)->lpVtbl -> GetCurrentSelection(This,ppsi) ) 

#define IFileOpenDialog_GetFileName(This,pszName)	\
    ( (This)->lpVtbl -> GetFileName(This,pszName) ) 

#define IFileOpenDialog_SetTitle(This,pszTitle)	\
    ( (This)->lpVtbl -> SetTitle(This,pszTitle) ) 

#define IFileOpenDialog_SetOkButtonLabel(This,pszText)	\
    ( (This)->lpVtbl -> SetOkButtonLabel(This,pszText) ) 

#define IFileOpenDialog_SetFileNameLabel(This,pszLabel)	\
    ( (This)->lpVtbl -> SetFileNameLabel(This,pszLabel) ) 

#define IFileOpenDialog_GetResult(This,ppsi)	\
    ( (This)->lpVtbl -> GetResult(This,ppsi) ) 

#define IFileOpenDialog_AddPlace(This,psi)	\
    ( (This)->lpVtbl -> AddPlace(This,psi) ) 

#define IFileOpenDialog_SetDefaultExtension(This,pszDefaultExtension)	\
    ( (This)->lpVtbl -> SetDefaultExtension(This,pszDefaultExtension) ) 


#define IFileOpenDialog_GetResults(This,ppenum)	\
    ( (This)->lpVtbl -> GetResults(This,ppenum) ) 

#define IFileOpenDialog_GetSelectedItems(This,ppsai)	\
    ( (This)->lpVtbl -> GetSelectedItems(This,ppsai) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileOpenDialog_GetResults_Proxy( 
    IFileOpenDialog * This,
    /* [out] */ IShellItemArray **ppenum);


void __RPC_STUB IFileOpenDialog_GetResults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileOpenDialog_GetSelectedItems_Proxy( 
    IFileOpenDialog * This,
    /* [out] */ IShellItemArray **ppsai);


void __RPC_STUB IFileOpenDialog_GetSelectedItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileOpenDialog_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0310 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagFILESAVEDIALOGINKMODE
    {	FSDIM_DISABLED	= 0,
	FSDIM_ENABLED	= 1,
	FSDIM_FORCE_VISIBLE	= 2
    } 	FILESAVEDIALOGINKMODE;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0310_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0310_v0_0_s_ifspec;

#ifndef __IFileDialogInk_INTERFACE_DEFINED__
#define __IFileDialogInk_INTERFACE_DEFINED__

/* interface IFileDialogInk */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFileDialogInk;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ca70d954-900f-49d0-ba31-6215f7686596")
    IFileDialogInk : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetInkFilenameMode( 
            /* [in] */ FILESAVEDIALOGINKMODE dwMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileDialogInkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileDialogInk * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileDialogInk * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileDialogInk * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetInkFilenameMode )( 
            IFileDialogInk * This,
            /* [in] */ FILESAVEDIALOGINKMODE dwMode);
        
        END_INTERFACE
    } IFileDialogInkVtbl;

    interface IFileDialogInk
    {
        CONST_VTBL struct IFileDialogInkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileDialogInk_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileDialogInk_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileDialogInk_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileDialogInk_SetInkFilenameMode(This,dwMode)	\
    ( (This)->lpVtbl -> SetInkFilenameMode(This,dwMode) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileDialogInk_SetInkFilenameMode_Proxy( 
    IFileDialogInk * This,
    /* [in] */ FILESAVEDIALOGINKMODE dwMode);


void __RPC_STUB IFileDialogInk_SetInkFilenameMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileDialogInk_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0311 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum tagCDCONTROLSTATE
    {	CDCS_ENABLED	= 0x1,
	CDCS_VISIBLE	= 0x2
    } 	CDCONTROLSTATE;

typedef DWORD CDCONTROLSTATEF;

typedef /* [v1_enum] */ 
enum tagCDCONTROLLAYOUT
    {	CDCL_ABOVE	= 0,
	CDCL_BELOW	= 0x1
    } 	CDCONTROLLAYOUT;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0311_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0311_v0_0_s_ifspec;

#ifndef __IFileDialogCustomize_INTERFACE_DEFINED__
#define __IFileDialogCustomize_INTERFACE_DEFINED__

/* interface IFileDialogCustomize */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFileDialogCustomize;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6857070D-3A83-435f-8767-83182569C051")
    IFileDialogCustomize : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnableToolbarMenu( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableOpenDropDown( 
            /* [in] */ DWORD dwIDCtl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddPushButton( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddComboBox( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddRadioButtonGroup( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddCheckButton( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout,
            /* [in] */ BOOL bChecked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddEditBox( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout,
            /* [string][in] */ LPCWSTR pszText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetControlLabel( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetControlState( 
            /* [in] */ DWORD dwIDCtl,
            /* [out] */ CDCONTROLSTATEF *pdwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetControlState( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ CDCONTROLSTATEF dwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEditBoxText( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][out] */ WCHAR **ppszText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEditBoxText( 
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCheckButtonState( 
            /* [in] */ DWORD dwIDCtl,
            /* [out] */ BOOL *pbChecked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCheckButtonState( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ BOOL bChecked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddControlItem( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem,
            /* [in] */ LPCWSTR pszLabel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveControlItem( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAllControlItems( 
            /* [in] */ DWORD dwIDCtl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetControlItemState( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem,
            /* [out] */ CDCONTROLSTATEF *pdwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetControlItemState( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem,
            /* [in] */ CDCONTROLSTATEF dwState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectedControlItem( 
            /* [in] */ DWORD dwIDCtl,
            /* [out] */ DWORD *pdwIDItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSelectedControlItem( 
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileDialogCustomizeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileDialogCustomize * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileDialogCustomize * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileDialogCustomize * This);
        
        HRESULT ( STDMETHODCALLTYPE *EnableToolbarMenu )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel);
        
        HRESULT ( STDMETHODCALLTYPE *EnableOpenDropDown )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl);
        
        HRESULT ( STDMETHODCALLTYPE *AddPushButton )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout);
        
        HRESULT ( STDMETHODCALLTYPE *AddComboBox )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout);
        
        HRESULT ( STDMETHODCALLTYPE *AddRadioButtonGroup )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout);
        
        HRESULT ( STDMETHODCALLTYPE *AddCheckButton )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout,
            /* [in] */ BOOL bChecked);
        
        HRESULT ( STDMETHODCALLTYPE *AddEditBox )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel,
            /* [in] */ CDCONTROLLAYOUT dwLayout,
            /* [string][in] */ LPCWSTR pszText);
        
        HRESULT ( STDMETHODCALLTYPE *SetControlLabel )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszLabel);
        
        HRESULT ( STDMETHODCALLTYPE *GetControlState )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [out] */ CDCONTROLSTATEF *pdwState);
        
        HRESULT ( STDMETHODCALLTYPE *SetControlState )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ CDCONTROLSTATEF dwState);
        
        HRESULT ( STDMETHODCALLTYPE *GetEditBoxText )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][out] */ WCHAR **ppszText);
        
        HRESULT ( STDMETHODCALLTYPE *SetEditBoxText )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [string][in] */ LPCWSTR pszText);
        
        HRESULT ( STDMETHODCALLTYPE *GetCheckButtonState )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [out] */ BOOL *pbChecked);
        
        HRESULT ( STDMETHODCALLTYPE *SetCheckButtonState )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ BOOL bChecked);
        
        HRESULT ( STDMETHODCALLTYPE *AddControlItem )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem,
            /* [in] */ LPCWSTR pszLabel);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveControlItem )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAllControlItems )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl);
        
        HRESULT ( STDMETHODCALLTYPE *GetControlItemState )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem,
            /* [out] */ CDCONTROLSTATEF *pdwState);
        
        HRESULT ( STDMETHODCALLTYPE *SetControlItemState )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem,
            /* [in] */ CDCONTROLSTATEF dwState);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectedControlItem )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [out] */ DWORD *pdwIDItem);
        
        HRESULT ( STDMETHODCALLTYPE *SetSelectedControlItem )( 
            IFileDialogCustomize * This,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem);
        
        END_INTERFACE
    } IFileDialogCustomizeVtbl;

    interface IFileDialogCustomize
    {
        CONST_VTBL struct IFileDialogCustomizeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileDialogCustomize_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileDialogCustomize_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileDialogCustomize_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileDialogCustomize_EnableToolbarMenu(This,dwIDCtl,pszLabel)	\
    ( (This)->lpVtbl -> EnableToolbarMenu(This,dwIDCtl,pszLabel) ) 

#define IFileDialogCustomize_EnableOpenDropDown(This,dwIDCtl)	\
    ( (This)->lpVtbl -> EnableOpenDropDown(This,dwIDCtl) ) 

#define IFileDialogCustomize_AddPushButton(This,dwIDCtl,pszLabel,dwLayout)	\
    ( (This)->lpVtbl -> AddPushButton(This,dwIDCtl,pszLabel,dwLayout) ) 

#define IFileDialogCustomize_AddComboBox(This,dwIDCtl,pszLabel,dwLayout)	\
    ( (This)->lpVtbl -> AddComboBox(This,dwIDCtl,pszLabel,dwLayout) ) 

#define IFileDialogCustomize_AddRadioButtonGroup(This,dwIDCtl,pszLabel,dwLayout)	\
    ( (This)->lpVtbl -> AddRadioButtonGroup(This,dwIDCtl,pszLabel,dwLayout) ) 

#define IFileDialogCustomize_AddCheckButton(This,dwIDCtl,pszLabel,dwLayout,bChecked)	\
    ( (This)->lpVtbl -> AddCheckButton(This,dwIDCtl,pszLabel,dwLayout,bChecked) ) 

#define IFileDialogCustomize_AddEditBox(This,dwIDCtl,pszLabel,dwLayout,pszText)	\
    ( (This)->lpVtbl -> AddEditBox(This,dwIDCtl,pszLabel,dwLayout,pszText) ) 

#define IFileDialogCustomize_SetControlLabel(This,dwIDCtl,pszLabel)	\
    ( (This)->lpVtbl -> SetControlLabel(This,dwIDCtl,pszLabel) ) 

#define IFileDialogCustomize_GetControlState(This,dwIDCtl,pdwState)	\
    ( (This)->lpVtbl -> GetControlState(This,dwIDCtl,pdwState) ) 

#define IFileDialogCustomize_SetControlState(This,dwIDCtl,dwState)	\
    ( (This)->lpVtbl -> SetControlState(This,dwIDCtl,dwState) ) 

#define IFileDialogCustomize_GetEditBoxText(This,dwIDCtl,ppszText)	\
    ( (This)->lpVtbl -> GetEditBoxText(This,dwIDCtl,ppszText) ) 

#define IFileDialogCustomize_SetEditBoxText(This,dwIDCtl,pszText)	\
    ( (This)->lpVtbl -> SetEditBoxText(This,dwIDCtl,pszText) ) 

#define IFileDialogCustomize_GetCheckButtonState(This,dwIDCtl,pbChecked)	\
    ( (This)->lpVtbl -> GetCheckButtonState(This,dwIDCtl,pbChecked) ) 

#define IFileDialogCustomize_SetCheckButtonState(This,dwIDCtl,bChecked)	\
    ( (This)->lpVtbl -> SetCheckButtonState(This,dwIDCtl,bChecked) ) 

#define IFileDialogCustomize_AddControlItem(This,dwIDCtl,dwIDItem,pszLabel)	\
    ( (This)->lpVtbl -> AddControlItem(This,dwIDCtl,dwIDItem,pszLabel) ) 

#define IFileDialogCustomize_RemoveControlItem(This,dwIDCtl,dwIDItem)	\
    ( (This)->lpVtbl -> RemoveControlItem(This,dwIDCtl,dwIDItem) ) 

#define IFileDialogCustomize_RemoveAllControlItems(This,dwIDCtl)	\
    ( (This)->lpVtbl -> RemoveAllControlItems(This,dwIDCtl) ) 

#define IFileDialogCustomize_GetControlItemState(This,dwIDCtl,dwIDItem,pdwState)	\
    ( (This)->lpVtbl -> GetControlItemState(This,dwIDCtl,dwIDItem,pdwState) ) 

#define IFileDialogCustomize_SetControlItemState(This,dwIDCtl,dwIDItem,dwState)	\
    ( (This)->lpVtbl -> SetControlItemState(This,dwIDCtl,dwIDItem,dwState) ) 

#define IFileDialogCustomize_GetSelectedControlItem(This,dwIDCtl,pdwIDItem)	\
    ( (This)->lpVtbl -> GetSelectedControlItem(This,dwIDCtl,pdwIDItem) ) 

#define IFileDialogCustomize_SetSelectedControlItem(This,dwIDCtl,dwIDItem)	\
    ( (This)->lpVtbl -> SetSelectedControlItem(This,dwIDCtl,dwIDItem) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileDialogCustomize_EnableToolbarMenu_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel);


void __RPC_STUB IFileDialogCustomize_EnableToolbarMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_EnableOpenDropDown_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl);


void __RPC_STUB IFileDialogCustomize_EnableOpenDropDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_AddPushButton_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel,
    /* [in] */ CDCONTROLLAYOUT dwLayout);


void __RPC_STUB IFileDialogCustomize_AddPushButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_AddComboBox_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel,
    /* [in] */ CDCONTROLLAYOUT dwLayout);


void __RPC_STUB IFileDialogCustomize_AddComboBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_AddRadioButtonGroup_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel,
    /* [in] */ CDCONTROLLAYOUT dwLayout);


void __RPC_STUB IFileDialogCustomize_AddRadioButtonGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_AddCheckButton_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel,
    /* [in] */ CDCONTROLLAYOUT dwLayout,
    /* [in] */ BOOL bChecked);


void __RPC_STUB IFileDialogCustomize_AddCheckButton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_AddEditBox_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel,
    /* [in] */ CDCONTROLLAYOUT dwLayout,
    /* [string][in] */ LPCWSTR pszText);


void __RPC_STUB IFileDialogCustomize_AddEditBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_SetControlLabel_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszLabel);


void __RPC_STUB IFileDialogCustomize_SetControlLabel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_GetControlState_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [out] */ CDCONTROLSTATEF *pdwState);


void __RPC_STUB IFileDialogCustomize_GetControlState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_SetControlState_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ CDCONTROLSTATEF dwState);


void __RPC_STUB IFileDialogCustomize_SetControlState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_GetEditBoxText_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][out] */ WCHAR **ppszText);


void __RPC_STUB IFileDialogCustomize_GetEditBoxText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_SetEditBoxText_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [string][in] */ LPCWSTR pszText);


void __RPC_STUB IFileDialogCustomize_SetEditBoxText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_GetCheckButtonState_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [out] */ BOOL *pbChecked);


void __RPC_STUB IFileDialogCustomize_GetCheckButtonState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_SetCheckButtonState_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ BOOL bChecked);


void __RPC_STUB IFileDialogCustomize_SetCheckButtonState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_AddControlItem_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ DWORD dwIDItem,
    /* [in] */ LPCWSTR pszLabel);


void __RPC_STUB IFileDialogCustomize_AddControlItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_RemoveControlItem_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ DWORD dwIDItem);


void __RPC_STUB IFileDialogCustomize_RemoveControlItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_RemoveAllControlItems_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl);


void __RPC_STUB IFileDialogCustomize_RemoveAllControlItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_GetControlItemState_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ DWORD dwIDItem,
    /* [out] */ CDCONTROLSTATEF *pdwState);


void __RPC_STUB IFileDialogCustomize_GetControlItemState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_SetControlItemState_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ DWORD dwIDItem,
    /* [in] */ CDCONTROLSTATEF dwState);


void __RPC_STUB IFileDialogCustomize_SetControlItemState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_GetSelectedControlItem_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [out] */ DWORD *pdwIDItem);


void __RPC_STUB IFileDialogCustomize_GetSelectedControlItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogCustomize_SetSelectedControlItem_Proxy( 
    IFileDialogCustomize * This,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ DWORD dwIDItem);


void __RPC_STUB IFileDialogCustomize_SetSelectedControlItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileDialogCustomize_INTERFACE_DEFINED__ */


#ifndef __IFileDialogControlEvents_INTERFACE_DEFINED__
#define __IFileDialogControlEvents_INTERFACE_DEFINED__

/* interface IFileDialogControlEvents */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IFileDialogControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36116642-D713-4b97-9B83-7484A9D00433")
    IFileDialogControlEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnItemSelected( 
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnButtonClicked( 
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnCheckButtonToggled( 
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ BOOL bChecked) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnControlActivating( 
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileDialogControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFileDialogControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFileDialogControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFileDialogControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnItemSelected )( 
            IFileDialogControlEvents * This,
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ DWORD dwIDItem);
        
        HRESULT ( STDMETHODCALLTYPE *OnButtonClicked )( 
            IFileDialogControlEvents * This,
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl);
        
        HRESULT ( STDMETHODCALLTYPE *OnCheckButtonToggled )( 
            IFileDialogControlEvents * This,
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl,
            /* [in] */ BOOL bChecked);
        
        HRESULT ( STDMETHODCALLTYPE *OnControlActivating )( 
            IFileDialogControlEvents * This,
            /* [in] */ IFileDialogCustomize *pfdc,
            /* [in] */ DWORD dwIDCtl);
        
        END_INTERFACE
    } IFileDialogControlEventsVtbl;

    interface IFileDialogControlEvents
    {
        CONST_VTBL struct IFileDialogControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileDialogControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFileDialogControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFileDialogControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFileDialogControlEvents_OnItemSelected(This,pfdc,dwIDCtl,dwIDItem)	\
    ( (This)->lpVtbl -> OnItemSelected(This,pfdc,dwIDCtl,dwIDItem) ) 

#define IFileDialogControlEvents_OnButtonClicked(This,pfdc,dwIDCtl)	\
    ( (This)->lpVtbl -> OnButtonClicked(This,pfdc,dwIDCtl) ) 

#define IFileDialogControlEvents_OnCheckButtonToggled(This,pfdc,dwIDCtl,bChecked)	\
    ( (This)->lpVtbl -> OnCheckButtonToggled(This,pfdc,dwIDCtl,bChecked) ) 

#define IFileDialogControlEvents_OnControlActivating(This,pfdc,dwIDCtl)	\
    ( (This)->lpVtbl -> OnControlActivating(This,pfdc,dwIDCtl) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileDialogControlEvents_OnItemSelected_Proxy( 
    IFileDialogControlEvents * This,
    /* [in] */ IFileDialogCustomize *pfdc,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ DWORD dwIDItem);


void __RPC_STUB IFileDialogControlEvents_OnItemSelected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogControlEvents_OnButtonClicked_Proxy( 
    IFileDialogControlEvents * This,
    /* [in] */ IFileDialogCustomize *pfdc,
    /* [in] */ DWORD dwIDCtl);


void __RPC_STUB IFileDialogControlEvents_OnButtonClicked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogControlEvents_OnCheckButtonToggled_Proxy( 
    IFileDialogControlEvents * This,
    /* [in] */ IFileDialogCustomize *pfdc,
    /* [in] */ DWORD dwIDCtl,
    /* [in] */ BOOL bChecked);


void __RPC_STUB IFileDialogControlEvents_OnCheckButtonToggled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileDialogControlEvents_OnControlActivating_Proxy( 
    IFileDialogControlEvents * This,
    /* [in] */ IFileDialogCustomize *pfdc,
    /* [in] */ DWORD dwIDCtl);


void __RPC_STUB IFileDialogControlEvents_OnControlActivating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileDialogControlEvents_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0313 */
/* [local] */ 

#include <pshpack1.h>
typedef struct tagDELEGATEITEMID
    {
    WORD cbSize;
    WORD wOuter;
    WORD cbInner;
    BYTE rgb[ 1 ];
    } 	DELEGATEITEMID;

#include <poppack.h>
typedef const UNALIGNED DELEGATEITEMID *PCDELEGATEITEMID;
typedef UNALIGNED DELEGATEITEMID *PDELEGATEITEMID;


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0313_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0313_v0_0_s_ifspec;

#ifndef __IDelegateFolder_INTERFACE_DEFINED__
#define __IDelegateFolder_INTERFACE_DEFINED__

/* interface IDelegateFolder */
/* [unique][object][uuid][helpstring] */ 


EXTERN_C const IID IID_IDelegateFolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADD8BA80-002B-11D0-8F0F-00C04FD7D062")
    IDelegateFolder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetItemAlloc( 
            /* [in] */ IMalloc *pmalloc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDelegateFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDelegateFolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDelegateFolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDelegateFolder * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetItemAlloc )( 
            IDelegateFolder * This,
            /* [in] */ IMalloc *pmalloc);
        
        END_INTERFACE
    } IDelegateFolderVtbl;

    interface IDelegateFolder
    {
        CONST_VTBL struct IDelegateFolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDelegateFolder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDelegateFolder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDelegateFolder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDelegateFolder_SetItemAlloc(This,pmalloc)	\
    ( (This)->lpVtbl -> SetItemAlloc(This,pmalloc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDelegateFolder_SetItemAlloc_Proxy( 
    IDelegateFolder * This,
    /* [in] */ IMalloc *pmalloc);


void __RPC_STUB IDelegateFolder_SetItemAlloc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDelegateFolder_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0314 */
/* [local] */ 

// INTERFACE: IBrowserFrameOptions
//
// This interface was implemented so a browser or host can ask a ShellView/ShelNameSpace what
// kind of 'Behavior' is appropriate for that view.
//
//    IBrowserFrameOptions::GetBrowserOptions()
//       dwMask is the logical OR of bits to look for.  pdwOptions is not optional and
//       it's return value will always equal or will be a subset of dwMask.
//       If the function succeeds, the return value must be S_OK and pdwOptions needs to be filled in.
//       If the function fails, pdwOptions needs to be filled in with BFO_NONE.
//


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0314_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0314_v0_0_s_ifspec;

#ifndef __IBrowserFrameOptions_INTERFACE_DEFINED__
#define __IBrowserFrameOptions_INTERFACE_DEFINED__

/* interface IBrowserFrameOptions */
/* [local][object][uuid] */ 

typedef /* [unique] */ IBrowserFrameOptions *LPBROWSERFRAMEOPTIONS;


enum tagBROWSERFRAMEOPTIONS
    {	BFO_NONE	= 0,
	BFO_BROWSER_PERSIST_SETTINGS	= 0x1,
	BFO_RENAME_FOLDER_OPTIONS_TOINTERNET	= 0x2,
	BFO_BOTH_OPTIONS	= 0x4,
	BIF_PREFER_INTERNET_SHORTCUT	= 0x8,
	BFO_BROWSE_NO_IN_NEW_PROCESS	= 0x10,
	BFO_ENABLE_HYPERLINK_TRACKING	= 0x20,
	BFO_USE_IE_OFFLINE_SUPPORT	= 0x40,
	BFO_SUBSTITUE_INTERNET_START_PAGE	= 0x80,
	BFO_USE_IE_LOGOBANDING	= 0x100,
	BFO_ADD_IE_TOCAPTIONBAR	= 0x200,
	BFO_USE_DIALUP_REF	= 0x400,
	BFO_USE_IE_TOOLBAR	= 0x800,
	BFO_NO_PARENT_FOLDER_SUPPORT	= 0x1000,
	BFO_NO_REOPEN_NEXT_RESTART	= 0x2000,
	BFO_GO_HOME_PAGE	= 0x4000,
	BFO_PREFER_IEPROCESS	= 0x8000,
	BFO_SHOW_NAVIGATION_CANCELLED	= 0x10000,
	BFO_QUERY_ALL	= 0xffffffff
    } ;
typedef DWORD BROWSERFRAMEOPTIONS;


EXTERN_C const IID IID_IBrowserFrameOptions;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10DF43C8-1DBE-11d3-8B34-006097DF5BD4")
    IBrowserFrameOptions : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFrameOptions( 
            /* [in] */ BROWSERFRAMEOPTIONS dwMask,
            /* [out] */ BROWSERFRAMEOPTIONS *pdwOptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBrowserFrameOptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBrowserFrameOptions * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBrowserFrameOptions * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBrowserFrameOptions * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameOptions )( 
            IBrowserFrameOptions * This,
            /* [in] */ BROWSERFRAMEOPTIONS dwMask,
            /* [out] */ BROWSERFRAMEOPTIONS *pdwOptions);
        
        END_INTERFACE
    } IBrowserFrameOptionsVtbl;

    interface IBrowserFrameOptions
    {
        CONST_VTBL struct IBrowserFrameOptionsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBrowserFrameOptions_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBrowserFrameOptions_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBrowserFrameOptions_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBrowserFrameOptions_GetFrameOptions(This,dwMask,pdwOptions)	\
    ( (This)->lpVtbl -> GetFrameOptions(This,dwMask,pdwOptions) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBrowserFrameOptions_GetFrameOptions_Proxy( 
    IBrowserFrameOptions * This,
    /* [in] */ BROWSERFRAMEOPTIONS dwMask,
    /* [out] */ BROWSERFRAMEOPTIONS *pdwOptions);


void __RPC_STUB IBrowserFrameOptions_GetFrameOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBrowserFrameOptions_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0315 */
/* [local] */ 

#include <pshpack8.h>
typedef struct tagSMDATA
    {
    DWORD dwMask;
    DWORD dwFlags;
    HMENU hmenu;
    HWND hwnd;
    UINT uId;
    UINT uIdParent;
    UINT uIdAncestor;
    IUnknown *punk;
    PIDLIST_ABSOLUTE pidlFolder;
    PUITEMID_CHILD pidlItem;
    IShellFolder *psf;
    void *pvUserData;
    } 	SMDATA;

typedef struct tagSMDATA *LPSMDATA;

// Mask
#define SMDM_SHELLFOLDER               0x00000001  // This is for an item in the band
#define SMDM_HMENU                     0x00000002  // This is for the Band itself
#define SMDM_TOOLBAR                   0x00000004  // Plain toolbar, not associated with a shell folder or hmenu
// Flags (bitmask)
typedef struct tagSMINFO
    {
    DWORD dwMask;
    DWORD dwType;
    DWORD dwFlags;
    int iIcon;
    } 	SMINFO;

typedef struct tagSMINFO *PSMINFO;

typedef struct tagSHCSCHANGENOTIFYSTRUCT
    {
    LONG lEvent;
    PCIDLIST_ABSOLUTE pidl1;
    PCIDLIST_ABSOLUTE pidl2;
    } 	SMCSHCHANGENOTIFYSTRUCT;

typedef struct tagSHCSCHANGENOTIFYSTRUCT *PSMCSHCHANGENOTIFYSTRUCT;

#include <poppack.h>

enum tagSMINFOMASK
    {	SMIM_TYPE	= 0x1,
	SMIM_FLAGS	= 0x2,
	SMIM_ICON	= 0x4
    } ;

enum tagSMINFOTYPE
    {	SMIT_SEPARATOR	= 0x1,
	SMIT_STRING	= 0x2
    } ;

enum tagSMINFOFLAGS
    {	SMIF_ICON	= 0x1,
	SMIF_ACCELERATOR	= 0x2,
	SMIF_DROPTARGET	= 0x4,
	SMIF_SUBMENU	= 0x8,
	SMIF_CHECKED	= 0x20,
	SMIF_DROPCASCADE	= 0x40,
	SMIF_HIDDEN	= 0x80,
	SMIF_DISABLED	= 0x100,
	SMIF_TRACKPOPUP	= 0x200,
	SMIF_DEMOTED	= 0x400,
	SMIF_ALTSTATE	= 0x800,
	SMIF_DRAGNDROP	= 0x1000,
	SMIF_NEW	= 0x2000
    } ;
#define SMC_INITMENU            0x00000001  // The callback is called to init a menuband
#define SMC_CREATE              0x00000002
#define SMC_EXITMENU            0x00000003  // The callback is called when menu is collapsing
#define SMC_GETINFO             0x00000005  // The callback is called to return DWORD values
#define SMC_GETSFINFO           0x00000006  // The callback is called to return DWORD values
#define SMC_GETOBJECT           0x00000007  // The callback is called to get some object
#define SMC_GETSFOBJECT         0x00000008  // The callback is called to get some object
#define SMC_SFEXEC              0x00000009  // The callback is called to execute an shell folder item
#define SMC_SFSELECTITEM        0x0000000A  // The callback is called when an item is selected
#define SMC_REFRESH             0x00000010  // Menus have completely refreshed. Reset your state.
#define SMC_DEMOTE              0x00000011  // Demote an item
#define SMC_PROMOTE             0x00000012  // Promote an item, wParam = SMINV_* flag
#define SMC_DEFAULTICON         0x00000016  // Returns Default icon location in wParam, index in lParam
#define SMC_NEWITEM             0x00000017  // Notifies item is not in the order stream.
#define SMC_CHEVRONEXPAND       0x00000019  // Notifies of a expansion via the chevron
#define SMC_DISPLAYCHEVRONTIP   0x0000002A  // S_OK display, S_FALSE not.
#define SMC_SETSFOBJECT         0x0000002D  // Called to save the passed object
#define SMC_SHCHANGENOTIFY      0x0000002E  // Called when a Change notify is received. lParam points to SMCSHCHANGENOTIFYSTRUCT
#define SMC_CHEVRONGETTIP       0x0000002F  // Called to get the chevron tip text. wParam = Tip title, Lparam = TipText Both MAX_PATH
#define SMC_SFDDRESTRICTED      0x00000030  // Called requesting if it's ok to drop. wParam = IDropTarget.
#define SMC_GETAUTOEXPANDSTATE  0x00000041  // callback returns the default autoexpand state lParam = LPDWORD to recieve flags
#define SMC_AUTOEXPANDCHANGE    0x00000042  // Notify that the menu is expanding/contracting
#define SMC_GETCONTEXTMENUMODIFIER 0x00000043  // Used to add items to a context menu
                                            // wParam = state flags
// Flags for return value from SMC_GETAUTOEXPANDSTATE and SMC_AUTOEXPANDCHANGE:
#define SMAE_EXPANDED           0x00000001  // The menu is or should start expanded
#define SMAE_CONTRACTED         0x00000002  // The menu is or should start contracted
                                            // SMAE_EXPANDED and SMAE_CONTRACTED are mutually exclusive
#define SMAE_USER               0x00000004  // Indicates that the menu expansion/contraction is a reflection
                                            // of user choice
#define SMAE_VALID              0x00000007


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0315_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0315_v0_0_s_ifspec;

#ifndef __IShellMenuCallback_INTERFACE_DEFINED__
#define __IShellMenuCallback_INTERFACE_DEFINED__

/* interface IShellMenuCallback */
/* [local][unique][object][uuid] */ 


EXTERN_C const IID IID_IShellMenuCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4CA300A1-9B8D-11d1-8B22-00C04FD918D0")
    IShellMenuCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CallbackSM( 
            /* [out][in] */ LPSMDATA psmd,
            UINT uMsg,
            WPARAM wParam,
            LPARAM lParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellMenuCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellMenuCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellMenuCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellMenuCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *CallbackSM )( 
            IShellMenuCallback * This,
            /* [out][in] */ LPSMDATA psmd,
            UINT uMsg,
            WPARAM wParam,
            LPARAM lParam);
        
        END_INTERFACE
    } IShellMenuCallbackVtbl;

    interface IShellMenuCallback
    {
        CONST_VTBL struct IShellMenuCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellMenuCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellMenuCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellMenuCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellMenuCallback_CallbackSM(This,psmd,uMsg,wParam,lParam)	\
    ( (This)->lpVtbl -> CallbackSM(This,psmd,uMsg,wParam,lParam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellMenuCallback_CallbackSM_Proxy( 
    IShellMenuCallback * This,
    /* [out][in] */ LPSMDATA psmd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam);


void __RPC_STUB IShellMenuCallback_CallbackSM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellMenuCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0316 */
/* [local] */ 

#define SMINIT_DEFAULT              0x00000000  // No Options
#define SMINIT_RESTRICT_DRAGDROP    0x00000002  // Don't allow Drag and Drop
#define SMINIT_TOPLEVEL             0x00000004  // This is the top band.
#define SMINIT_CACHED               0x00000010
#define SMINIT_AUTOEXPAND           0x00000100  // automatically expand/contract menu band
#define SMINIT_VERTICAL             0x10000000  // This is a vertical menu
#define SMINIT_HORIZONTAL           0x20000000  // This is a horizontal menu    (does not inherit)
#define ANCESTORDEFAULT      (UINT)-1
#define SMSET_TOP                   0x10000000    // Bias this namespace to the top of the menu
#define SMSET_BOTTOM                0x20000000    // Bias this namespace to the bottom of the menu
#define SMSET_DONTOWN               0x00000001    // The Menuband doesn't own the non-ref counted object
#define SMINV_REFRESH        0x00000001
#define SMINV_ID             0x00000008


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0316_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0316_v0_0_s_ifspec;

#ifndef __IShellMenu_INTERFACE_DEFINED__
#define __IShellMenu_INTERFACE_DEFINED__

/* interface IShellMenu */
/* [local][unique][object][uuid] */ 


EXTERN_C const IID IID_IShellMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE1F7637-E138-11d1-8379-00C04FD918D0")
    IShellMenu : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IShellMenuCallback *psmc,
            UINT uId,
            UINT uIdAncestor,
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMenuInfo( 
            /* [out] */ IShellMenuCallback **ppsmc,
            /* [out] */ UINT *puId,
            /* [out] */ UINT *puIdAncestor,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetShellFolder( 
            IShellFolder *psf,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            HKEY hKey,
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShellFolder( 
            /* [out] */ DWORD *pdwFlags,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMenu( 
            /* [in] */ HMENU hmenu,
            /* [in] */ HWND hwnd,
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMenu( 
            /* [out] */ HMENU *phmenu,
            /* [out] */ HWND *phwnd,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateItem( 
            /* [in] */ LPSMDATA psmd,
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ LPSMDATA psmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMenuToolbar( 
            /* [in] */ IUnknown *punk,
            DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellMenu * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellMenu * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellMenu * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IShellMenu * This,
            /* [in] */ IShellMenuCallback *psmc,
            UINT uId,
            UINT uIdAncestor,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetMenuInfo )( 
            IShellMenu * This,
            /* [out] */ IShellMenuCallback **ppsmc,
            /* [out] */ UINT *puId,
            /* [out] */ UINT *puIdAncestor,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SetShellFolder )( 
            IShellMenu * This,
            IShellFolder *psf,
            /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
            HKEY hKey,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetShellFolder )( 
            IShellMenu * This,
            /* [out] */ DWORD *pdwFlags,
            /* [out] */ PIDLIST_ABSOLUTE *ppidl,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *SetMenu )( 
            IShellMenu * This,
            /* [in] */ HMENU hmenu,
            /* [in] */ HWND hwnd,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetMenu )( 
            IShellMenu * This,
            /* [out] */ HMENU *phmenu,
            /* [out] */ HWND *phwnd,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *InvalidateItem )( 
            IShellMenu * This,
            /* [in] */ LPSMDATA psmd,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IShellMenu * This,
            /* [out] */ LPSMDATA psmd);
        
        HRESULT ( STDMETHODCALLTYPE *SetMenuToolbar )( 
            IShellMenu * This,
            /* [in] */ IUnknown *punk,
            DWORD dwFlags);
        
        END_INTERFACE
    } IShellMenuVtbl;

    interface IShellMenu
    {
        CONST_VTBL struct IShellMenuVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellMenu_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellMenu_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellMenu_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShellMenu_Initialize(This,psmc,uId,uIdAncestor,dwFlags)	\
    ( (This)->lpVtbl -> Initialize(This,psmc,uId,uIdAncestor,dwFlags) ) 

#define IShellMenu_GetMenuInfo(This,ppsmc,puId,puIdAncestor,pdwFlags)	\
    ( (This)->lpVtbl -> GetMenuInfo(This,ppsmc,puId,puIdAncestor,pdwFlags) ) 

#define IShellMenu_SetShellFolder(This,psf,pidlFolder,hKey,dwFlags)	\
    ( (This)->lpVtbl -> SetShellFolder(This,psf,pidlFolder,hKey,dwFlags) ) 

#define IShellMenu_GetShellFolder(This,pdwFlags,ppidl,riid,ppv)	\
    ( (This)->lpVtbl -> GetShellFolder(This,pdwFlags,ppidl,riid,ppv) ) 

#define IShellMenu_SetMenu(This,hmenu,hwnd,dwFlags)	\
    ( (This)->lpVtbl -> SetMenu(This,hmenu,hwnd,dwFlags) ) 

#define IShellMenu_GetMenu(This,phmenu,phwnd,pdwFlags)	\
    ( (This)->lpVtbl -> GetMenu(This,phmenu,phwnd,pdwFlags) ) 

#define IShellMenu_InvalidateItem(This,psmd,dwFlags)	\
    ( (This)->lpVtbl -> InvalidateItem(This,psmd,dwFlags) ) 

#define IShellMenu_GetState(This,psmd)	\
    ( (This)->lpVtbl -> GetState(This,psmd) ) 

#define IShellMenu_SetMenuToolbar(This,punk,dwFlags)	\
    ( (This)->lpVtbl -> SetMenuToolbar(This,punk,dwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShellMenu_Initialize_Proxy( 
    IShellMenu * This,
    /* [in] */ IShellMenuCallback *psmc,
    UINT uId,
    UINT uIdAncestor,
    DWORD dwFlags);


void __RPC_STUB IShellMenu_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_GetMenuInfo_Proxy( 
    IShellMenu * This,
    /* [out] */ IShellMenuCallback **ppsmc,
    /* [out] */ UINT *puId,
    /* [out] */ UINT *puIdAncestor,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IShellMenu_GetMenuInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_SetShellFolder_Proxy( 
    IShellMenu * This,
    IShellFolder *psf,
    /* [in] */ PCIDLIST_ABSOLUTE pidlFolder,
    HKEY hKey,
    DWORD dwFlags);


void __RPC_STUB IShellMenu_SetShellFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_GetShellFolder_Proxy( 
    IShellMenu * This,
    /* [out] */ DWORD *pdwFlags,
    /* [out] */ PIDLIST_ABSOLUTE *ppidl,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IShellMenu_GetShellFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_SetMenu_Proxy( 
    IShellMenu * This,
    /* [in] */ HMENU hmenu,
    /* [in] */ HWND hwnd,
    DWORD dwFlags);


void __RPC_STUB IShellMenu_SetMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_GetMenu_Proxy( 
    IShellMenu * This,
    /* [out] */ HMENU *phmenu,
    /* [out] */ HWND *phwnd,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IShellMenu_GetMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_InvalidateItem_Proxy( 
    IShellMenu * This,
    /* [in] */ LPSMDATA psmd,
    DWORD dwFlags);


void __RPC_STUB IShellMenu_InvalidateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_GetState_Proxy( 
    IShellMenu * This,
    /* [out] */ LPSMDATA psmd);


void __RPC_STUB IShellMenu_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShellMenu_SetMenuToolbar_Proxy( 
    IShellMenu * This,
    /* [in] */ IUnknown *punk,
    DWORD dwFlags);


void __RPC_STUB IShellMenu_SetMenuToolbar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellMenu_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0317 */
/* [local] */ 

typedef struct tagSERIALIZEDPROPVALUE
    {
    UINT cbNext;
    union 
        {
        UINT pid;
        UINT cbName;
        } 	;
    } 	SERIALIZEDPROPVALUE;

typedef struct tagSERIALIZEDPROPSTORAGE
    {
    UINT cbNext;
    GUID fmtid;
    } 	SERIALIZEDPROPSTORAGE;

typedef SERIALIZEDPROPVALUE __unaligned *PUSERIALIZEDPROPVALUE;

typedef const SERIALIZEDPROPVALUE __unaligned *PCUSERIALIZEDPROPVALUE;

typedef SERIALIZEDPROPSTORAGE __unaligned *PUSERIALIZEDPROPSTORAGE;

typedef const SERIALIZEDPROPSTORAGE __unaligned *PCUSERIALIZEDPROPSTORAGE;

/* [v1_enum] */ 
enum tagPERSIST_SPROPSTORE_FLAGS
    {	FPSPS_READONLY	= 0x1
    } ;
typedef DWORD PERSIST_SPROPSTORE_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0317_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0317_v0_0_s_ifspec;

#ifndef __IPersistSerializedPropStorage_INTERFACE_DEFINED__
#define __IPersistSerializedPropStorage_INTERFACE_DEFINED__

/* interface IPersistSerializedPropStorage */
/* [unique][object][helpstring][uuid] */ 


EXTERN_C const IID IID_IPersistSerializedPropStorage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("88c82d8f-5705-4db1-ab41-55cebe9ac320")
    IPersistSerializedPropStorage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFlags( 
            /* [in] */ PERSIST_SPROPSTORE_FLAGS flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPropertyStorage( 
            /* [in] */ PCUSERIALIZEDPROPSTORAGE psps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropertyStorage( 
            /* [out] */ SERIALIZEDPROPSTORAGE **ppsps,
            /* [out] */ UINT *pcb) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistSerializedPropStorageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPersistSerializedPropStorage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPersistSerializedPropStorage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPersistSerializedPropStorage * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetFlags )( 
            IPersistSerializedPropStorage * This,
            /* [in] */ PERSIST_SPROPSTORE_FLAGS flags);
        
        HRESULT ( STDMETHODCALLTYPE *SetPropertyStorage )( 
            IPersistSerializedPropStorage * This,
            /* [in] */ PCUSERIALIZEDPROPSTORAGE psps);
        
        HRESULT ( STDMETHODCALLTYPE *GetPropertyStorage )( 
            IPersistSerializedPropStorage * This,
            /* [out] */ SERIALIZEDPROPSTORAGE **ppsps,
            /* [out] */ UINT *pcb);
        
        END_INTERFACE
    } IPersistSerializedPropStorageVtbl;

    interface IPersistSerializedPropStorage
    {
        CONST_VTBL struct IPersistSerializedPropStorageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistSerializedPropStorage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPersistSerializedPropStorage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPersistSerializedPropStorage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPersistSerializedPropStorage_SetFlags(This,flags)	\
    ( (This)->lpVtbl -> SetFlags(This,flags) ) 

#define IPersistSerializedPropStorage_SetPropertyStorage(This,psps)	\
    ( (This)->lpVtbl -> SetPropertyStorage(This,psps) ) 

#define IPersistSerializedPropStorage_GetPropertyStorage(This,ppsps,pcb)	\
    ( (This)->lpVtbl -> GetPropertyStorage(This,ppsps,pcb) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistSerializedPropStorage_SetFlags_Proxy( 
    IPersistSerializedPropStorage * This,
    /* [in] */ PERSIST_SPROPSTORE_FLAGS flags);


void __RPC_STUB IPersistSerializedPropStorage_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistSerializedPropStorage_SetPropertyStorage_Proxy( 
    IPersistSerializedPropStorage * This,
    /* [in] */ PCUSERIALIZEDPROPSTORAGE psps);


void __RPC_STUB IPersistSerializedPropStorage_SetPropertyStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistSerializedPropStorage_GetPropertyStorage_Proxy( 
    IPersistSerializedPropStorage * This,
    /* [out] */ SERIALIZEDPROPSTORAGE **ppsps,
    /* [out] */ UINT *pcb);


void __RPC_STUB IPersistSerializedPropStorage_GetPropertyStorage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistSerializedPropStorage_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0318 */
/* [local] */ 

/* [v1_enum] */ 
enum tagPLEINFOFLAGS
    {	PLEIF_SHOWPICKER	= 0x1,
	PLEIF_CREATENEW	= 0x2
    } ;
typedef DWORD PLEINFOFLAGS;

/* [v1_enum] */ 
enum tagPLEINFOMODE
    {	PLEIM_PHOTO	= 0,
	PLEIM_MUSIC	= 1
    } ;
typedef DWORD PLEINFOMODE;

typedef struct tagPLEINFO
    {
    PLEINFOFLAGS pleifFlags;
    PLEINFOMODE pleimMode;
    PIDLIST_ABSOLUTE pidlBrowser;
    PIDLIST_ABSOLUTE pidlPlaylist;
    IDataObject *pdo;
    LPWSTR pszTitle;
    } 	PLEINFO;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0318_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0318_v0_0_s_ifspec;

#ifndef __IPlaylistEditor_INTERFACE_DEFINED__
#define __IPlaylistEditor_INTERFACE_DEFINED__

/* interface IPlaylistEditor */
/* [unique][object][helpstring][uuid] */ 


EXTERN_C const IID IID_IPlaylistEditor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACD6797F-40FD-4E6F-BEC0-04503C7D4F72")
    IPlaylistEditor : public IModalWindow
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ PLEINFO *pInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTitle( 
            /* [in] */ int cchTitle,
            /* [size_is][out] */ LPWSTR pszTitle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPlaylistEditorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlaylistEditor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlaylistEditor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlaylistEditor * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Show )( 
            IPlaylistEditor * This,
            /* [in] */ HWND hwndParent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPlaylistEditor * This,
            /* [in] */ PLEINFO *pInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTitle )( 
            IPlaylistEditor * This,
            /* [in] */ int cchTitle,
            /* [size_is][out] */ LPWSTR pszTitle);
        
        END_INTERFACE
    } IPlaylistEditorVtbl;

    interface IPlaylistEditor
    {
        CONST_VTBL struct IPlaylistEditorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlaylistEditor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPlaylistEditor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPlaylistEditor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPlaylistEditor_Show(This,hwndParent)	\
    ( (This)->lpVtbl -> Show(This,hwndParent) ) 


#define IPlaylistEditor_Initialize(This,pInfo)	\
    ( (This)->lpVtbl -> Initialize(This,pInfo) ) 

#define IPlaylistEditor_GetTitle(This,cchTitle,pszTitle)	\
    ( (This)->lpVtbl -> GetTitle(This,cchTitle,pszTitle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlaylistEditor_Initialize_Proxy( 
    IPlaylistEditor * This,
    /* [in] */ PLEINFO *pInfo);


void __RPC_STUB IPlaylistEditor_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlaylistEditor_GetTitle_Proxy( 
    IPlaylistEditor * This,
    /* [in] */ int cchTitle,
    /* [size_is][out] */ LPWSTR pszTitle);


void __RPC_STUB IPlaylistEditor_GetTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPlaylistEditor_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0319 */
/* [local] */ 

/* [v1_enum] */ 
enum tagFOLDERINFO_FLAGS
    {	FINFO_DEFAULT	= 0,
	FINFO_MOVECONTENTS	= 0x1,
	FINFO_UNPIN	= 0x2
    } ;
typedef DWORD FOLDERINFO_FLAGS;

/* [v1_enum] */ 
enum tagFOLDERPERMISSION_FLAGS
    {	FPERM_NONE	= 0,
	FPERM_SETPATH	= 0x1
    } ;
typedef DWORD FOLDERPERMISSION_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0319_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0319_v0_0_s_ifspec;

#ifndef __IFolderInformation_INTERFACE_DEFINED__
#define __IFolderInformation_INTERFACE_DEFINED__

/* interface IFolderInformation */
/* [version][object][helpstring][uuid] */ 


EXTERN_C const IID IID_IFolderInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("355f57b4-8946-4982-bda6-d1928a5b2043")
    IFolderInformation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFolderPath( 
            /* [in] */ UINT csidl,
            /* [string][out] */ LPWSTR *ppszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFolderPath( 
            /* [in] */ UINT csidl,
            /* [in] */ DWORD dwFlags,
            /* [string][in] */ LPCWSTR pszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPermissions( 
            /* [in] */ UINT csidl,
            /* [out] */ DWORD *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsValidFolderPath( 
            /* [in] */ UINT csidl,
            /* [string][in] */ LPCWSTR pszPath) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE UISetFolderPath( 
            /* [in] */ HWND hwnd,
            /* [in] */ UINT csidl,
            /* [in] */ DWORD dwFlags,
            /* [string][in] */ LPCWSTR pszPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFolderInformation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFolderInformation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFolderInformation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFolderPath )( 
            IFolderInformation * This,
            /* [in] */ UINT csidl,
            /* [string][out] */ LPWSTR *ppszPath);
        
        HRESULT ( STDMETHODCALLTYPE *SetFolderPath )( 
            IFolderInformation * This,
            /* [in] */ UINT csidl,
            /* [in] */ DWORD dwFlags,
            /* [string][in] */ LPCWSTR pszPath);
        
        HRESULT ( STDMETHODCALLTYPE *GetPermissions )( 
            IFolderInformation * This,
            /* [in] */ UINT csidl,
            /* [out] */ DWORD *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *IsValidFolderPath )( 
            IFolderInformation * This,
            /* [in] */ UINT csidl,
            /* [string][in] */ LPCWSTR pszPath);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *UISetFolderPath )( 
            IFolderInformation * This,
            /* [in] */ HWND hwnd,
            /* [in] */ UINT csidl,
            /* [in] */ DWORD dwFlags,
            /* [string][in] */ LPCWSTR pszPath);
        
        END_INTERFACE
    } IFolderInformationVtbl;

    interface IFolderInformation
    {
        CONST_VTBL struct IFolderInformationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderInformation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFolderInformation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFolderInformation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFolderInformation_GetFolderPath(This,csidl,ppszPath)	\
    ( (This)->lpVtbl -> GetFolderPath(This,csidl,ppszPath) ) 

#define IFolderInformation_SetFolderPath(This,csidl,dwFlags,pszPath)	\
    ( (This)->lpVtbl -> SetFolderPath(This,csidl,dwFlags,pszPath) ) 

#define IFolderInformation_GetPermissions(This,csidl,pdwFlags)	\
    ( (This)->lpVtbl -> GetPermissions(This,csidl,pdwFlags) ) 

#define IFolderInformation_IsValidFolderPath(This,csidl,pszPath)	\
    ( (This)->lpVtbl -> IsValidFolderPath(This,csidl,pszPath) ) 

#define IFolderInformation_UISetFolderPath(This,hwnd,csidl,dwFlags,pszPath)	\
    ( (This)->lpVtbl -> UISetFolderPath(This,hwnd,csidl,dwFlags,pszPath) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFolderInformation_GetFolderPath_Proxy( 
    IFolderInformation * This,
    /* [in] */ UINT csidl,
    /* [string][out] */ LPWSTR *ppszPath);


void __RPC_STUB IFolderInformation_GetFolderPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderInformation_SetFolderPath_Proxy( 
    IFolderInformation * This,
    /* [in] */ UINT csidl,
    /* [in] */ DWORD dwFlags,
    /* [string][in] */ LPCWSTR pszPath);


void __RPC_STUB IFolderInformation_SetFolderPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderInformation_GetPermissions_Proxy( 
    IFolderInformation * This,
    /* [in] */ UINT csidl,
    /* [out] */ DWORD *pdwFlags);


void __RPC_STUB IFolderInformation_GetPermissions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFolderInformation_IsValidFolderPath_Proxy( 
    IFolderInformation * This,
    /* [in] */ UINT csidl,
    /* [string][in] */ LPCWSTR pszPath);


void __RPC_STUB IFolderInformation_IsValidFolderPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [local] */ HRESULT STDMETHODCALLTYPE IFolderInformation_UISetFolderPath_Proxy( 
    IFolderInformation * This,
    /* [in] */ HWND hwnd,
    /* [in] */ UINT csidl,
    /* [in] */ DWORD dwFlags,
    /* [string][in] */ LPCWSTR pszPath);


void __RPC_STUB IFolderInformation_UISetFolderPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderInformation_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0320 */
/* [local] */ 




typedef 
enum _tagSHAREMANAGER_SHARE_ATTRIBUTES
    {	SM_SHARE_ATTRIBUTE_NORMAL	= 0x1,
	SM_SHARE_ATTRIBUTE_HIDDEN	= 0x2,
	SM_SHARE_ATTRIBUTE_DRIVE	= 0x4,
	SM_SHARE_ATTRIBUTE_ADMIN	= 0x8,
	SM_SHARE_ATTRIBUTE_READONLY	= 0x100,
	SM_SHARE_ATTRIBUTE_READWRITE	= 0x200
    } 	SHAREMANAGER_SHARE_ATTRIBUTES;

typedef DWORD SM_SHARE_ATTRIBUTES;

#ifdef MIDL_PASS
typedef byte *PSECURITY_DESCRIPTOR;

typedef ULONG ACCESS_MASK;

#endif
typedef 
enum _tagSHAREMANAGER_CONTROL_FLAGS
    {	SM_CONTROL_FLAG_CREATENEWSHAREIFONEEXISTS	= 0x1,
	SM_CONTROL_FLAG_UPDATEEXISTINGSHAREPERMS	= 0x2,
	SM_CONTROL_FLAG_UPDATEEXISTINGSHAREPERMSTODEFAULT	= 0x4,
	SM_CONTROL_FLAG_ENABLEFIREWALLSUBNET	= 0x100,
	SM_CONTROL_FLAG_ENABLEFIREWALLGLOBAL	= 0x200,
	SM_CONTROL_FLAG_DONTCHANGEFIREWALLPORTS	= 0x400,
	SM_CONTROL_FLAG_PROTECTEDSCOPE	= 0x1000,
	SM_CONTROL_FLAG_ABORTONFIRSTERROR	= 0x1000000
    } 	SHAREMANAGER_CONTROL_FLAGS;

typedef DWORD SM_CONTROL_FLAGS;

typedef /* [v1_enum] */ 
enum _tagSHAREMANAGER_ENUMSHARES_FLAGS
    {	SM_ENUMSHARES_FLAG_INCLUDEALL	= 0x1,
	SM_ENUMSHARES_FLAG_INCLUDEADMIN	= 0x2,
	SM_ENUMSHARES_FLAG_INCLUDEDRIVES	= 0x4,
	SM_ENUMSHARES_FLAG_INCLUDEOTHERHIDDEN	= 0x8
    } 	SHAREMANAGER_ENUMSHARES_FLAGS;

typedef DWORD SM_ENUMSHARES_FLAGS;


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0320_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0320_v0_0_s_ifspec;

#ifndef __IShareManager_INTERFACE_DEFINED__
#define __IShareManager_INTERFACE_DEFINED__

/* interface IShareManager */
/* [version][uuid][helpstring][object] */ 


EXTERN_C const IID IID_IShareManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a78b7a2b-f90d-4195-b269-2a7c7fbb4dd0")
    IShareManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GenerateUniqueShareName( 
            /* [string][in] */ LPCWSTR pszFolderPath,
            /* [string][out] */ LPWSTR *ppszShareName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Share( 
            /* [string][in] */ LPCWSTR pszShareName,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [in] */ SM_CONTROL_FLAGS grfControlFlags,
            /* [string][in] */ LPCWSTR pszRemark,
            /* [unique][in] */ IShareProgress *pShareProgress,
            /* [unique][in] */ PSECURITY_DESCRIPTOR pSD) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unshare( 
            /* [string][in] */ LPCWSTR pszShareName,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [in] */ SM_CONTROL_FLAGS grfControlFlags,
            /* [in] */ IShareProgress *pShareProgress) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAggregateSecurity( 
            /* [unique][in] */ IDataObject *pDataObject,
            /* [out] */ LPDWORD pcbSDSize,
            /* [size_is][size_is][out] */ PSECURITY_DESCRIPTOR *ppSD) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetShareInfo( 
            /* [string][in] */ LPCWSTR pszShareName,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [out] */ IEnumShareInformation **ppEnumShareInformation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanShare( 
            /* [unique][in] */ IDataObject *pDataObject,
            /* [out] */ BOOL *pbCanShare) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumSharedItems( 
            /* [string][in] */ LPCWSTR pszSidSharedBy,
            /* [string][in] */ LPCWSTR pszSidSharedTo,
            /* [unique][in] */ ACCESS_MASK *pAccessMask,
            /* [in] */ SM_ENUMSHARES_FLAGS grfFlags,
            /* [out] */ IShellItemArray **ppShellItemArray) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetScopingShare( 
            /* [string][in] */ LPCWSTR pszFolderPath,
            /* [string][in] */ LPCWSTR pszUserSid,
            /* [in] */ ACCESS_MASK *pAccessMask,
            /* [in] */ SM_ENUMSHARES_FLAGS grfFlags,
            /* [string][out] */ LPWSTR *ppszUNCSharePath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShareManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShareManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShareManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShareManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GenerateUniqueShareName )( 
            IShareManager * This,
            /* [string][in] */ LPCWSTR pszFolderPath,
            /* [string][out] */ LPWSTR *ppszShareName);
        
        HRESULT ( STDMETHODCALLTYPE *Share )( 
            IShareManager * This,
            /* [string][in] */ LPCWSTR pszShareName,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [in] */ SM_CONTROL_FLAGS grfControlFlags,
            /* [string][in] */ LPCWSTR pszRemark,
            /* [unique][in] */ IShareProgress *pShareProgress,
            /* [unique][in] */ PSECURITY_DESCRIPTOR pSD);
        
        HRESULT ( STDMETHODCALLTYPE *Unshare )( 
            IShareManager * This,
            /* [string][in] */ LPCWSTR pszShareName,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [in] */ SM_CONTROL_FLAGS grfControlFlags,
            /* [in] */ IShareProgress *pShareProgress);
        
        HRESULT ( STDMETHODCALLTYPE *GetAggregateSecurity )( 
            IShareManager * This,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [out] */ LPDWORD pcbSDSize,
            /* [size_is][size_is][out] */ PSECURITY_DESCRIPTOR *ppSD);
        
        HRESULT ( STDMETHODCALLTYPE *GetShareInfo )( 
            IShareManager * This,
            /* [string][in] */ LPCWSTR pszShareName,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [out] */ IEnumShareInformation **ppEnumShareInformation);
        
        HRESULT ( STDMETHODCALLTYPE *CanShare )( 
            IShareManager * This,
            /* [unique][in] */ IDataObject *pDataObject,
            /* [out] */ BOOL *pbCanShare);
        
        HRESULT ( STDMETHODCALLTYPE *EnumSharedItems )( 
            IShareManager * This,
            /* [string][in] */ LPCWSTR pszSidSharedBy,
            /* [string][in] */ LPCWSTR pszSidSharedTo,
            /* [unique][in] */ ACCESS_MASK *pAccessMask,
            /* [in] */ SM_ENUMSHARES_FLAGS grfFlags,
            /* [out] */ IShellItemArray **ppShellItemArray);
        
        HRESULT ( STDMETHODCALLTYPE *GetScopingShare )( 
            IShareManager * This,
            /* [string][in] */ LPCWSTR pszFolderPath,
            /* [string][in] */ LPCWSTR pszUserSid,
            /* [in] */ ACCESS_MASK *pAccessMask,
            /* [in] */ SM_ENUMSHARES_FLAGS grfFlags,
            /* [string][out] */ LPWSTR *ppszUNCSharePath);
        
        END_INTERFACE
    } IShareManagerVtbl;

    interface IShareManager
    {
        CONST_VTBL struct IShareManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShareManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShareManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShareManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShareManager_GenerateUniqueShareName(This,pszFolderPath,ppszShareName)	\
    ( (This)->lpVtbl -> GenerateUniqueShareName(This,pszFolderPath,ppszShareName) ) 

#define IShareManager_Share(This,pszShareName,pDataObject,grfControlFlags,pszRemark,pShareProgress,pSD)	\
    ( (This)->lpVtbl -> Share(This,pszShareName,pDataObject,grfControlFlags,pszRemark,pShareProgress,pSD) ) 

#define IShareManager_Unshare(This,pszShareName,pDataObject,grfControlFlags,pShareProgress)	\
    ( (This)->lpVtbl -> Unshare(This,pszShareName,pDataObject,grfControlFlags,pShareProgress) ) 

#define IShareManager_GetAggregateSecurity(This,pDataObject,pcbSDSize,ppSD)	\
    ( (This)->lpVtbl -> GetAggregateSecurity(This,pDataObject,pcbSDSize,ppSD) ) 

#define IShareManager_GetShareInfo(This,pszShareName,pDataObject,ppEnumShareInformation)	\
    ( (This)->lpVtbl -> GetShareInfo(This,pszShareName,pDataObject,ppEnumShareInformation) ) 

#define IShareManager_CanShare(This,pDataObject,pbCanShare)	\
    ( (This)->lpVtbl -> CanShare(This,pDataObject,pbCanShare) ) 

#define IShareManager_EnumSharedItems(This,pszSidSharedBy,pszSidSharedTo,pAccessMask,grfFlags,ppShellItemArray)	\
    ( (This)->lpVtbl -> EnumSharedItems(This,pszSidSharedBy,pszSidSharedTo,pAccessMask,grfFlags,ppShellItemArray) ) 

#define IShareManager_GetScopingShare(This,pszFolderPath,pszUserSid,pAccessMask,grfFlags,ppszUNCSharePath)	\
    ( (This)->lpVtbl -> GetScopingShare(This,pszFolderPath,pszUserSid,pAccessMask,grfFlags,ppszUNCSharePath) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShareManager_GenerateUniqueShareName_Proxy( 
    IShareManager * This,
    /* [string][in] */ LPCWSTR pszFolderPath,
    /* [string][out] */ LPWSTR *ppszShareName);


void __RPC_STUB IShareManager_GenerateUniqueShareName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_Share_Proxy( 
    IShareManager * This,
    /* [string][in] */ LPCWSTR pszShareName,
    /* [unique][in] */ IDataObject *pDataObject,
    /* [in] */ SM_CONTROL_FLAGS grfControlFlags,
    /* [string][in] */ LPCWSTR pszRemark,
    /* [unique][in] */ IShareProgress *pShareProgress,
    /* [unique][in] */ PSECURITY_DESCRIPTOR pSD);


void __RPC_STUB IShareManager_Share_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_Unshare_Proxy( 
    IShareManager * This,
    /* [string][in] */ LPCWSTR pszShareName,
    /* [unique][in] */ IDataObject *pDataObject,
    /* [in] */ SM_CONTROL_FLAGS grfControlFlags,
    /* [in] */ IShareProgress *pShareProgress);


void __RPC_STUB IShareManager_Unshare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_GetAggregateSecurity_Proxy( 
    IShareManager * This,
    /* [unique][in] */ IDataObject *pDataObject,
    /* [out] */ LPDWORD pcbSDSize,
    /* [size_is][size_is][out] */ PSECURITY_DESCRIPTOR *ppSD);


void __RPC_STUB IShareManager_GetAggregateSecurity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_GetShareInfo_Proxy( 
    IShareManager * This,
    /* [string][in] */ LPCWSTR pszShareName,
    /* [unique][in] */ IDataObject *pDataObject,
    /* [out] */ IEnumShareInformation **ppEnumShareInformation);


void __RPC_STUB IShareManager_GetShareInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_CanShare_Proxy( 
    IShareManager * This,
    /* [unique][in] */ IDataObject *pDataObject,
    /* [out] */ BOOL *pbCanShare);


void __RPC_STUB IShareManager_CanShare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_EnumSharedItems_Proxy( 
    IShareManager * This,
    /* [string][in] */ LPCWSTR pszSidSharedBy,
    /* [string][in] */ LPCWSTR pszSidSharedTo,
    /* [unique][in] */ ACCESS_MASK *pAccessMask,
    /* [in] */ SM_ENUMSHARES_FLAGS grfFlags,
    /* [out] */ IShellItemArray **ppShellItemArray);


void __RPC_STUB IShareManager_EnumSharedItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareManager_GetScopingShare_Proxy( 
    IShareManager * This,
    /* [string][in] */ LPCWSTR pszFolderPath,
    /* [string][in] */ LPCWSTR pszUserSid,
    /* [in] */ ACCESS_MASK *pAccessMask,
    /* [in] */ SM_ENUMSHARES_FLAGS grfFlags,
    /* [string][out] */ LPWSTR *ppszUNCSharePath);


void __RPC_STUB IShareManager_GetScopingShare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShareManager_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0321 */
/* [local] */ 

typedef struct SHAREINFORMATION
    {
    LPWSTR pszUNCSharePath;
    LPWSTR pszItemPath;
    LPWSTR pszRemark;
    SM_SHARE_ATTRIBUTES spAttributes;
    DWORD cbSDSize;
    BYTE pSD[ 1 ];
    } 	SHAREINFORMATION;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0321_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0321_v0_0_s_ifspec;

#ifndef __IEnumShareInformation_INTERFACE_DEFINED__
#define __IEnumShareInformation_INTERFACE_DEFINED__

/* interface IEnumShareInformation */
/* [unique][uuid][helpstring][object] */ 


EXTERN_C const IID IID_IEnumShareInformation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("edd27709-b533-4c9c-8c19-4bfcd62e4c49")
    IEnumShareInformation : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ SHAREINFORMATION **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumShareInformation **ppEnumShareInformation) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumShareInformationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumShareInformation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumShareInformation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumShareInformation * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumShareInformation * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ SHAREINFORMATION **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumShareInformation * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumShareInformation * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumShareInformation * This,
            /* [out] */ IEnumShareInformation **ppEnumShareInformation);
        
        END_INTERFACE
    } IEnumShareInformationVtbl;

    interface IEnumShareInformation
    {
        CONST_VTBL struct IEnumShareInformationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumShareInformation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumShareInformation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumShareInformation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumShareInformation_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumShareInformation_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumShareInformation_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumShareInformation_Clone(This,ppEnumShareInformation)	\
    ( (This)->lpVtbl -> Clone(This,ppEnumShareInformation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumShareInformation_Next_Proxy( 
    IEnumShareInformation * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ SHAREINFORMATION **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumShareInformation_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumShareInformation_Skip_Proxy( 
    IEnumShareInformation * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumShareInformation_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumShareInformation_Reset_Proxy( 
    IEnumShareInformation * This);


void __RPC_STUB IEnumShareInformation_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumShareInformation_Clone_Proxy( 
    IEnumShareInformation * This,
    /* [out] */ IEnumShareInformation **ppEnumShareInformation);


void __RPC_STUB IEnumShareInformation_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumShareInformation_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0322 */
/* [local] */ 

typedef /* [v1_enum] */ 
enum _tagSHAREPROGRESS_OP
    {	SHAREPROGRESS_OP_CONTAINERSETACL	= 1,
	SHAREPROGRESS_OP_OBJECTSETACL	= ( SHAREPROGRESS_OP_CONTAINERSETACL + 1 ) ,
	SHAREPROGRESS_OP_SHARESETACL	= ( SHAREPROGRESS_OP_OBJECTSETACL + 1 ) ,
	SHAREPROGRESS_OP_SHAREDELETE	= ( SHAREPROGRESS_OP_SHARESETACL + 1 ) 
    } 	SHAREPROGRESS_OP;

typedef /* [v1_enum] */ 
enum _tagSHAREPROGRESS_FLAG
    {	SHAREPROGRESS_FLAG_CONTINUE	= 1,
	SHAREPROGRESS_FLAG_CALLBACKONERROR	= ( SHAREPROGRESS_FLAG_CONTINUE + 1 ) ,
	SHAREPROGRESS_FLAG_NOCALLBACK	= ( SHAREPROGRESS_FLAG_CALLBACKONERROR + 1 ) ,
	SHAREPROGRESS_FLAG_CANCEL	= ( SHAREPROGRESS_FLAG_NOCALLBACK + 1 ) 
    } 	SHAREPROGRESS_FLAG;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0322_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0322_v0_0_s_ifspec;

#ifndef __IShareProgress_INTERFACE_DEFINED__
#define __IShareProgress_INTERFACE_DEFINED__

/* interface IShareProgress */
/* [unique][uuid][helpstring][object] */ 


EXTERN_C const IID IID_IShareProgress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b36a41a2-6e5c-47e4-813d-0bfce8bad090")
    IShareProgress : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PreOp( 
            /* [string][in] */ LPCWSTR pszObjectName,
            /* [in] */ SHAREPROGRESS_OP shareProgressOp,
            /* [in] */ DWORD dwStatus,
            /* [out] */ SHAREPROGRESS_FLAG *pProgressFlag) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostOp( 
            /* [string][in] */ LPCWSTR pszObjectName,
            /* [in] */ SHAREPROGRESS_OP shareProgressOp,
            /* [in] */ DWORD dwStatus,
            /* [out] */ SHAREPROGRESS_FLAG *pProgressFlag) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShareProgressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShareProgress * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShareProgress * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShareProgress * This);
        
        HRESULT ( STDMETHODCALLTYPE *PreOp )( 
            IShareProgress * This,
            /* [string][in] */ LPCWSTR pszObjectName,
            /* [in] */ SHAREPROGRESS_OP shareProgressOp,
            /* [in] */ DWORD dwStatus,
            /* [out] */ SHAREPROGRESS_FLAG *pProgressFlag);
        
        HRESULT ( STDMETHODCALLTYPE *PostOp )( 
            IShareProgress * This,
            /* [string][in] */ LPCWSTR pszObjectName,
            /* [in] */ SHAREPROGRESS_OP shareProgressOp,
            /* [in] */ DWORD dwStatus,
            /* [out] */ SHAREPROGRESS_FLAG *pProgressFlag);
        
        END_INTERFACE
    } IShareProgressVtbl;

    interface IShareProgress
    {
        CONST_VTBL struct IShareProgressVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShareProgress_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShareProgress_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShareProgress_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IShareProgress_PreOp(This,pszObjectName,shareProgressOp,dwStatus,pProgressFlag)	\
    ( (This)->lpVtbl -> PreOp(This,pszObjectName,shareProgressOp,dwStatus,pProgressFlag) ) 

#define IShareProgress_PostOp(This,pszObjectName,shareProgressOp,dwStatus,pProgressFlag)	\
    ( (This)->lpVtbl -> PostOp(This,pszObjectName,shareProgressOp,dwStatus,pProgressFlag) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IShareProgress_PreOp_Proxy( 
    IShareProgress * This,
    /* [string][in] */ LPCWSTR pszObjectName,
    /* [in] */ SHAREPROGRESS_OP shareProgressOp,
    /* [in] */ DWORD dwStatus,
    /* [out] */ SHAREPROGRESS_FLAG *pProgressFlag);


void __RPC_STUB IShareProgress_PreOp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IShareProgress_PostOp_Proxy( 
    IShareProgress * This,
    /* [string][in] */ LPCWSTR pszObjectName,
    /* [in] */ SHAREPROGRESS_OP shareProgressOp,
    /* [in] */ DWORD dwStatus,
    /* [out] */ SHAREPROGRESS_FLAG *pProgressFlag);


void __RPC_STUB IShareProgress_PostOp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShareProgress_INTERFACE_DEFINED__ */


#ifndef __IPreviousVersionsInfo_INTERFACE_DEFINED__
#define __IPreviousVersionsInfo_INTERFACE_DEFINED__

/* interface IPreviousVersionsInfo */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IPreviousVersionsInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("76e54780-ad74-48e3-a695-3ba9a0aff10d")
    IPreviousVersionsInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AreSnapshotsAvailable( 
            /* [string][in] */ LPCWSTR pszPath,
            /* [in] */ BOOL fOkToBeSlow,
            /* [retval][out] */ BOOL *pfAvailable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPreviousVersionsInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPreviousVersionsInfo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPreviousVersionsInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPreviousVersionsInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *AreSnapshotsAvailable )( 
            IPreviousVersionsInfo * This,
            /* [string][in] */ LPCWSTR pszPath,
            /* [in] */ BOOL fOkToBeSlow,
            /* [retval][out] */ BOOL *pfAvailable);
        
        END_INTERFACE
    } IPreviousVersionsInfoVtbl;

    interface IPreviousVersionsInfo
    {
        CONST_VTBL struct IPreviousVersionsInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPreviousVersionsInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPreviousVersionsInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPreviousVersionsInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPreviousVersionsInfo_AreSnapshotsAvailable(This,pszPath,fOkToBeSlow,pfAvailable)	\
    ( (This)->lpVtbl -> AreSnapshotsAvailable(This,pszPath,fOkToBeSlow,pfAvailable) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPreviousVersionsInfo_AreSnapshotsAvailable_Proxy( 
    IPreviousVersionsInfo * This,
    /* [string][in] */ LPCWSTR pszPath,
    /* [in] */ BOOL fOkToBeSlow,
    /* [retval][out] */ BOOL *pfAvailable);


void __RPC_STUB IPreviousVersionsInfo_AreSnapshotsAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPreviousVersionsInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0324 */
/* [local] */ 


//===================================================================
//DESCRIPTION: IComposeWindow
//
//   This interface is implemented by clients that have compose windows
//(E-mail applications, Newsgroup clients, Fax software, Calendar Invites, etc.).
//This interface will allow an application to launch a compose window and have
//the compose window appear partially or fully filled out.
//
// Callers wanting to launch the compose window can create CLSID_LaunchComposeWindow
// in order to create this interface.  Callers should create this object with CLSCTX_ANY.
//
// The registry entry HKLM, \Software\Clients\ contains the list of client applications.
// Examples of Client values: Mail, Calendar, Contacts, IM, News, etc.
//
// For E-mail, the API MAPISendMail() will launch a compose window and fill out a few fields.  
// The goal of the IComposeWindow API is to fill out much more of the compose window.  This is accomplished
// by the caller passing a stream containing rich data needed to fill out the compose window.
// The format of the stream that fills out the compose window will be documented here for each client type.
//
// Applications calling LaunchComposeWindow() should expect that the call may not return until
// the user closes the Compose Window.  Some implementations of LaunchComposeWindow will
// move the user interface to a different thread (recommended).  However, some legacy
// implementers of MAPISendMail() will not return until the UI is dismissed.

// CLIENT: Mail
// The content type for a Mail compose window is message/rfc822. 
// The caller creates a MIME or RFC 822 compatible stream containing the message that they
// want to appear in the compose window.  This stream is then passed in the
// pStream parameter.  IMimeMessage can be used to create this stream from strings for the header
// values, text version of the body, and html version of the body.

// The MIME or RFC 822 stream allows a wide range of attributes to be specified, from custom headers
// to digital signatures.  The email client is recommended to carry forward as many attributes
// as is possible and appropriate.  Digital Signatures and Encrypted email messages are examples of
// attributes that will not be respected.

// WARNING: This method will always launch the compose window.  For security reasons, it will not
//          send the message without user interaction.

// The Mail client supports a special flag SMEX_ALLOWFALLBACK.  If this value is specified and the
// current E-mail application does not support this interface, it will fallback to MAPISendMail().
// attributes that will not be respected.

// Applications register their compose window under the following registry entry:
// HKLM/HKCU, Software\Clients\<ClientType>\<ApplicationName>\Compose,  CLSID [REG_SZ] == {<CLSID>}


// Flags for dwFlags
#define SMEX_DEFAULT              0x00000000      // Normal behavior
#define SMEX_ALLOWFALLBACK        0x00000001      // If the current email application doesn't support this API, then fallback to MAPISendMail().
                                                  // This will result in the Email message not containing an HTML body or othe extended properties.
//
// PARAMETERS:
//   pszClientType:      The client to launch. Examples: Mail, Calendar, News, etc.
//   hwndParent:         The HWND to the general location to Compose window should appear.  OPTIONAL
//   pStream:            The stream of the content for the compose window.
//   dwFlags:            Same as flFlags for MAPISendMail().  MAPI_DIALOG is required to be set.
//   return values:
//                       S_OK: The compose window was successfully launched.
//                       E_NOTIMPL: If the currently selected application for this client type doesn't implement
//                           IComposeWindow, this error value will be returned.
//                       HRESULT_FROM_WIN32(ERROR_SERVICE_DOES_NOT_EXIST): This will be returned if the current application doesn't
//                           implement this client type.
//                       HRESULT_FROM_WIN32(ERROR_SERVICE_NOT_IN_EXE): This will be returned if the currently selected Mail program doesn't
//                           implement IComposeWindow or the fallback function MAPISendMail().
//                       HRESULT_FROM_WIN32(ERROR_NO_MATCH): This will be returned if the current application for
//                           this client type supports IComposeWindow, but does not support this ContentType.
//===================================================================


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0324_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0324_v0_0_s_ifspec;

#ifndef __IComposeWindow_INTERFACE_DEFINED__
#define __IComposeWindow_INTERFACE_DEFINED__

/* interface IComposeWindow */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IComposeWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11E5990F-752A-4876-A422-19B477CF7052")
    IComposeWindow : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LaunchComposeWindow( 
            /* [in] */ LPCWSTR pszClientType,
            /* [in] */ HWND hwndParent,
            /* [in] */ IStream *pStream,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComposeWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComposeWindow * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComposeWindow * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComposeWindow * This);
        
        HRESULT ( STDMETHODCALLTYPE *LaunchComposeWindow )( 
            IComposeWindow * This,
            /* [in] */ LPCWSTR pszClientType,
            /* [in] */ HWND hwndParent,
            /* [in] */ IStream *pStream,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IComposeWindowVtbl;

    interface IComposeWindow
    {
        CONST_VTBL struct IComposeWindowVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComposeWindow_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComposeWindow_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComposeWindow_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComposeWindow_LaunchComposeWindow(This,pszClientType,hwndParent,pStream,dwFlags)	\
    ( (This)->lpVtbl -> LaunchComposeWindow(This,pszClientType,hwndParent,pStream,dwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IComposeWindow_LaunchComposeWindow_Proxy( 
    IComposeWindow * This,
    /* [in] */ LPCWSTR pszClientType,
    /* [in] */ HWND hwndParent,
    /* [in] */ IStream *pStream,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IComposeWindow_LaunchComposeWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IComposeWindow_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0325 */
/* [local] */ 

/* [v1_enum] */ 
enum tagBASKETCONTROLFLAGS
    {	BCF_HIDENAVIGATION	= 0x1,
	BCF_HIDEORDER	= 0x2,
	BCF_WIDELAYOUT	= 0x8,
	BCF_WATERMARKTEXT	= 0x20,
	BCF_STATUS_NOTVIEWBASED	= 0x40,
	BCF_NOHEADER	= 0x100
    } ;
typedef struct tagBASKETCONTROLINFO
    {
    DWORD cbSize;
    DWORD bcf;
    PCIDLIST_ABSOLUTE pidl;
    UINT cpkey;
    const PROPERTYKEY *apkey;
    WCHAR szWatermark[ 100 ];
    } 	BASKETCONTROLINFO;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0325_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0325_v0_0_s_ifspec;

#ifndef __IBasketControl_INTERFACE_DEFINED__
#define __IBasketControl_INTERFACE_DEFINED__

/* interface IBasketControl */
/* [unique][object][helpstring][uuid] */ 


EXTERN_C const IID IID_IBasketControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7424EEBF-BC33-4601-B8DC-3C7620C4C1E6")
    IBasketControl : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HWND hwndParent,
            /* [in] */ const BASKETCONTROLINFO *pbci) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DestroyViewWindow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBrowser( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetStatusText( 
            /* [in] */ LPCWSTR pszStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPropertyGauge( 
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ const PROPVARIANT varMaximum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPropertyText( 
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ LPCWSTR pszFormat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateStatusInfo( 
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ const PROPVARIANT varCurrent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBasketControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBasketControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBasketControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBasketControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IBasketControl * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ const BASKETCONTROLINFO *pbci);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DestroyViewWindow )( 
            IBasketControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBrowser )( 
            IBasketControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetStatusText )( 
            IBasketControl * This,
            /* [in] */ LPCWSTR pszStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPropertyGauge )( 
            IBasketControl * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ const PROPVARIANT varMaximum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPropertyText )( 
            IBasketControl * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ LPCWSTR pszFormat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateStatusInfo )( 
            IBasketControl * This,
            /* [in] */ REFPROPERTYKEY key,
            /* [in] */ const PROPVARIANT varCurrent);
        
        END_INTERFACE
    } IBasketControlVtbl;

    interface IBasketControl
    {
        CONST_VTBL struct IBasketControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBasketControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBasketControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBasketControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBasketControl_Initialize(This,hwndParent,pbci)	\
    ( (This)->lpVtbl -> Initialize(This,hwndParent,pbci) ) 

#define IBasketControl_DestroyViewWindow(This)	\
    ( (This)->lpVtbl -> DestroyViewWindow(This) ) 

#define IBasketControl_GetBrowser(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetBrowser(This,riid,ppv) ) 

#define IBasketControl_SetStatusText(This,pszStatus)	\
    ( (This)->lpVtbl -> SetStatusText(This,pszStatus) ) 

#define IBasketControl_SetPropertyGauge(This,key,varMaximum)	\
    ( (This)->lpVtbl -> SetPropertyGauge(This,key,varMaximum) ) 

#define IBasketControl_SetPropertyText(This,key,pszFormat)	\
    ( (This)->lpVtbl -> SetPropertyText(This,key,pszFormat) ) 

#define IBasketControl_UpdateStatusInfo(This,key,varCurrent)	\
    ( (This)->lpVtbl -> UpdateStatusInfo(This,key,varCurrent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_Initialize_Proxy( 
    IBasketControl * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ const BASKETCONTROLINFO *pbci);


void __RPC_STUB IBasketControl_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_DestroyViewWindow_Proxy( 
    IBasketControl * This);


void __RPC_STUB IBasketControl_DestroyViewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_GetBrowser_Proxy( 
    IBasketControl * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IBasketControl_GetBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_SetStatusText_Proxy( 
    IBasketControl * This,
    /* [in] */ LPCWSTR pszStatus);


void __RPC_STUB IBasketControl_SetStatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_SetPropertyGauge_Proxy( 
    IBasketControl * This,
    /* [in] */ REFPROPERTYKEY key,
    /* [in] */ const PROPVARIANT varMaximum);


void __RPC_STUB IBasketControl_SetPropertyGauge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_SetPropertyText_Proxy( 
    IBasketControl * This,
    /* [in] */ REFPROPERTYKEY key,
    /* [in] */ LPCWSTR pszFormat);


void __RPC_STUB IBasketControl_SetPropertyText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBasketControl_UpdateStatusInfo_Proxy( 
    IBasketControl * This,
    /* [in] */ REFPROPERTYKEY key,
    /* [in] */ const PROPVARIANT varCurrent);


void __RPC_STUB IBasketControl_UpdateStatusInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBasketControl_INTERFACE_DEFINED__ */


#ifndef __IListMakerControl_INTERFACE_DEFINED__
#define __IListMakerControl_INTERFACE_DEFINED__

/* interface IListMakerControl */
/* [object][unique][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IListMakerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E1874FD2-7A1D-476b-9CF9-83A7EB121D88")
    IListMakerControl : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HWND hwndParent,
            /* [in] */ PCIDLIST_ABSOLUTE pidlBrowser,
            /* [in] */ const BASKETCONTROLINFO *pbci) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DestroyViewWindow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBasketInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBrowserInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetWidth( 
            /* [in] */ UINT cxBasket) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWidth( 
            /* [out] */ UINT *pcxBasket) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IListMakerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IListMakerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IListMakerControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IListMakerControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IListMakerControl * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ PCIDLIST_ABSOLUTE pidlBrowser,
            /* [in] */ const BASKETCONTROLINFO *pbci);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DestroyViewWindow )( 
            IListMakerControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBasketInterface )( 
            IListMakerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBrowserInterface )( 
            IListMakerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetWidth )( 
            IListMakerControl * This,
            /* [in] */ UINT cxBasket);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWidth )( 
            IListMakerControl * This,
            /* [out] */ UINT *pcxBasket);
        
        END_INTERFACE
    } IListMakerControlVtbl;

    interface IListMakerControl
    {
        CONST_VTBL struct IListMakerControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IListMakerControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IListMakerControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IListMakerControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IListMakerControl_Initialize(This,hwndParent,pidlBrowser,pbci)	\
    ( (This)->lpVtbl -> Initialize(This,hwndParent,pidlBrowser,pbci) ) 

#define IListMakerControl_DestroyViewWindow(This)	\
    ( (This)->lpVtbl -> DestroyViewWindow(This) ) 

#define IListMakerControl_GetBasketInterface(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetBasketInterface(This,riid,ppv) ) 

#define IListMakerControl_GetBrowserInterface(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetBrowserInterface(This,riid,ppv) ) 

#define IListMakerControl_SetWidth(This,cxBasket)	\
    ( (This)->lpVtbl -> SetWidth(This,cxBasket) ) 

#define IListMakerControl_GetWidth(This,pcxBasket)	\
    ( (This)->lpVtbl -> GetWidth(This,pcxBasket) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControl_Initialize_Proxy( 
    IListMakerControl * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ PCIDLIST_ABSOLUTE pidlBrowser,
    /* [in] */ const BASKETCONTROLINFO *pbci);


void __RPC_STUB IListMakerControl_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControl_DestroyViewWindow_Proxy( 
    IListMakerControl * This);


void __RPC_STUB IListMakerControl_DestroyViewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControl_GetBasketInterface_Proxy( 
    IListMakerControl * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IListMakerControl_GetBasketInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControl_GetBrowserInterface_Proxy( 
    IListMakerControl * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IListMakerControl_GetBrowserInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControl_SetWidth_Proxy( 
    IListMakerControl * This,
    /* [in] */ UINT cxBasket);


void __RPC_STUB IListMakerControl_SetWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControl_GetWidth_Proxy( 
    IListMakerControl * This,
    /* [out] */ UINT *pcxBasket);


void __RPC_STUB IListMakerControl_GetWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IListMakerControl_INTERFACE_DEFINED__ */


#ifndef __IListMakerControlSite_INTERFACE_DEFINED__
#define __IListMakerControlSite_INTERFACE_DEFINED__

/* interface IListMakerControlSite */
/* [object][unique][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IListMakerControlSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7F47D96-41AD-43EB-A3CB-FC6AB1C6E64E")
    IListMakerControlSite : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IncludeItem( 
            /* [in] */ IShellItem *psi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IListMakerControlSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IListMakerControlSite * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IListMakerControlSite * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IListMakerControlSite * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IncludeItem )( 
            IListMakerControlSite * This,
            /* [in] */ IShellItem *psi);
        
        END_INTERFACE
    } IListMakerControlSiteVtbl;

    interface IListMakerControlSite
    {
        CONST_VTBL struct IListMakerControlSiteVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IListMakerControlSite_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IListMakerControlSite_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IListMakerControlSite_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IListMakerControlSite_IncludeItem(This,psi)	\
    ( (This)->lpVtbl -> IncludeItem(This,psi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IListMakerControlSite_IncludeItem_Proxy( 
    IListMakerControlSite * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB IListMakerControlSite_IncludeItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IListMakerControlSite_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0328 */
/* [local] */ 

#define SID_SListMakerControlSite IID_IListMakerControlSite
typedef /* [v1_enum] */ 
enum _tagSYNCENGACTION
    {	SYNCENG_COPYATOB	= 0x1,
	SYNCENG_COPYBTOA	= 0x2,
	SYNCENG_DELETEA	= 0x3,
	SYNCENG_DELETEB	= 0x4,
	SYNCENG_MERGE	= 0x5,
	SYNCENG_SKIP	= 0x6
    } 	SYNCENGACTION;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0328_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0328_v0_0_s_ifspec;

#ifndef __ISyncReconciliationAction_INTERFACE_DEFINED__
#define __ISyncReconciliationAction_INTERFACE_DEFINED__

/* interface ISyncReconciliationAction */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISyncReconciliationAction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f7da33a5-fd27-4ff1-b8e9-05c7535be52b")
    ISyncReconciliationAction : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAction( 
            /* [out] */ IShellItem **ppsiA,
            /* [out] */ IShellItem **ppsiB,
            /* [out] */ SYNCENGACTION *paction) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAction( 
            /* [in] */ SYNCENGACTION action) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Execute( 
            /* [optional][in] */ IFileOperationProgressSink *pfnSyncCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncReconciliationActionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncReconciliationAction * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncReconciliationAction * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncReconciliationAction * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetAction )( 
            ISyncReconciliationAction * This,
            /* [out] */ IShellItem **ppsiA,
            /* [out] */ IShellItem **ppsiB,
            /* [out] */ SYNCENGACTION *paction);
        
        HRESULT ( STDMETHODCALLTYPE *SetAction )( 
            ISyncReconciliationAction * This,
            /* [in] */ SYNCENGACTION action);
        
        HRESULT ( STDMETHODCALLTYPE *Execute )( 
            ISyncReconciliationAction * This,
            /* [optional][in] */ IFileOperationProgressSink *pfnSyncCallback);
        
        END_INTERFACE
    } ISyncReconciliationActionVtbl;

    interface ISyncReconciliationAction
    {
        CONST_VTBL struct ISyncReconciliationActionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncReconciliationAction_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncReconciliationAction_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncReconciliationAction_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncReconciliationAction_GetAction(This,ppsiA,ppsiB,paction)	\
    ( (This)->lpVtbl -> GetAction(This,ppsiA,ppsiB,paction) ) 

#define ISyncReconciliationAction_SetAction(This,action)	\
    ( (This)->lpVtbl -> SetAction(This,action) ) 

#define ISyncReconciliationAction_Execute(This,pfnSyncCallback)	\
    ( (This)->lpVtbl -> Execute(This,pfnSyncCallback) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncReconciliationAction_GetAction_Proxy( 
    ISyncReconciliationAction * This,
    /* [out] */ IShellItem **ppsiA,
    /* [out] */ IShellItem **ppsiB,
    /* [out] */ SYNCENGACTION *paction);


void __RPC_STUB ISyncReconciliationAction_GetAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncReconciliationAction_SetAction_Proxy( 
    ISyncReconciliationAction * This,
    /* [in] */ SYNCENGACTION action);


void __RPC_STUB ISyncReconciliationAction_SetAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncReconciliationAction_Execute_Proxy( 
    ISyncReconciliationAction * This,
    /* [optional][in] */ IFileOperationProgressSink *pfnSyncCallback);


void __RPC_STUB ISyncReconciliationAction_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncReconciliationAction_INTERFACE_DEFINED__ */


#ifndef __ISyncReconciliationList_INTERFACE_DEFINED__
#define __ISyncReconciliationList_INTERFACE_DEFINED__

/* interface ISyncReconciliationList */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISyncReconciliationList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b40a9a34-cdef-43a7-9eeb-9a0abad0c48d")
    ISyncReconciliationList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncReconciliationAction **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ISyncReconciliationList **ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExecuteAll( 
            /* [optional][in] */ ITransferAdviseSink *pfnSyncCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncReconciliationListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncReconciliationList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncReconciliationList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncReconciliationList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            ISyncReconciliationList * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncReconciliationAction **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ISyncReconciliationList * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISyncReconciliationList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISyncReconciliationList * This,
            /* [out] */ ISyncReconciliationList **ppenum);
        
        HRESULT ( STDMETHODCALLTYPE *ExecuteAll )( 
            ISyncReconciliationList * This,
            /* [optional][in] */ ITransferAdviseSink *pfnSyncCallback);
        
        END_INTERFACE
    } ISyncReconciliationListVtbl;

    interface ISyncReconciliationList
    {
        CONST_VTBL struct ISyncReconciliationListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncReconciliationList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncReconciliationList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncReconciliationList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncReconciliationList_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ISyncReconciliationList_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define ISyncReconciliationList_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ISyncReconciliationList_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ISyncReconciliationList_ExecuteAll(This,pfnSyncCallback)	\
    ( (This)->lpVtbl -> ExecuteAll(This,pfnSyncCallback) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncReconciliationList_Next_Proxy( 
    ISyncReconciliationList * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ ISyncReconciliationAction **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB ISyncReconciliationList_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncReconciliationList_Skip_Proxy( 
    ISyncReconciliationList * This,
    /* [in] */ ULONG celt);


void __RPC_STUB ISyncReconciliationList_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncReconciliationList_Reset_Proxy( 
    ISyncReconciliationList * This);


void __RPC_STUB ISyncReconciliationList_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncReconciliationList_Clone_Proxy( 
    ISyncReconciliationList * This,
    /* [out] */ ISyncReconciliationList **ppenum);


void __RPC_STUB ISyncReconciliationList_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncReconciliationList_ExecuteAll_Proxy( 
    ISyncReconciliationList * This,
    /* [optional][in] */ ITransferAdviseSink *pfnSyncCallback);


void __RPC_STUB ISyncReconciliationList_ExecuteAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncReconciliationList_INTERFACE_DEFINED__ */


#ifndef __ISyncRelationship_INTERFACE_DEFINED__
#define __ISyncRelationship_INTERFACE_DEFINED__

/* interface ISyncRelationship */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISyncRelationship;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("650be65d-df09-4028-97a0-40b74c150a50")
    ISyncRelationship : public IEnumShellItems
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISyncRelationshipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncRelationship * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncRelationship * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncRelationship * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            ISyncRelationship * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IShellItem **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ISyncRelationship * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISyncRelationship * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISyncRelationship * This,
            /* [out] */ IEnumShellItems **ppenum);
        
        END_INTERFACE
    } ISyncRelationshipVtbl;

    interface ISyncRelationship
    {
        CONST_VTBL struct ISyncRelationshipVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncRelationship_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncRelationship_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncRelationship_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncRelationship_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ISyncRelationship_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define ISyncRelationship_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ISyncRelationship_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISyncRelationship_INTERFACE_DEFINED__ */


#ifndef __IEnumSyncRelationship_INTERFACE_DEFINED__
#define __IEnumSyncRelationship_INTERFACE_DEFINED__

/* interface IEnumSyncRelationship */
/* [uuid][object] */ 


EXTERN_C const IID IID_IEnumSyncRelationship;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a7254510-9427-4d22-9ebe-0e88c2cbc800")
    IEnumSyncRelationship : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncRelationship **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSyncRelationship **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumSyncRelationshipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSyncRelationship * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSyncRelationship * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSyncRelationship * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSyncRelationship * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncRelationship **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSyncRelationship * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSyncRelationship * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSyncRelationship * This,
            /* [out] */ IEnumSyncRelationship **ppenum);
        
        END_INTERFACE
    } IEnumSyncRelationshipVtbl;

    interface IEnumSyncRelationship
    {
        CONST_VTBL struct IEnumSyncRelationshipVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSyncRelationship_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSyncRelationship_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSyncRelationship_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSyncRelationship_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSyncRelationship_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumSyncRelationship_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSyncRelationship_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumSyncRelationship_Next_Proxy( 
    IEnumSyncRelationship * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ ISyncRelationship **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumSyncRelationship_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncRelationship_Skip_Proxy( 
    IEnumSyncRelationship * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumSyncRelationship_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncRelationship_Reset_Proxy( 
    IEnumSyncRelationship * This);


void __RPC_STUB IEnumSyncRelationship_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncRelationship_Clone_Proxy( 
    IEnumSyncRelationship * This,
    /* [out] */ IEnumSyncRelationship **ppenum);


void __RPC_STUB IEnumSyncRelationship_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumSyncRelationship_INTERFACE_DEFINED__ */


#ifndef __ISyncDatabaseGenerateActionsCB_INTERFACE_DEFINED__
#define __ISyncDatabaseGenerateActionsCB_INTERFACE_DEFINED__

/* interface ISyncDatabaseGenerateActionsCB */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISyncDatabaseGenerateActionsCB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5ff4de38-0de2-45f5-b6ee-8223caf82347")
    ISyncDatabaseGenerateActionsCB : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Begin( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE End( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FoundItem( 
            /* [in] */ IShellItem *psi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncDatabaseGenerateActionsCBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncDatabaseGenerateActionsCB * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncDatabaseGenerateActionsCB * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncDatabaseGenerateActionsCB * This);
        
        HRESULT ( STDMETHODCALLTYPE *Begin )( 
            ISyncDatabaseGenerateActionsCB * This);
        
        HRESULT ( STDMETHODCALLTYPE *End )( 
            ISyncDatabaseGenerateActionsCB * This);
        
        HRESULT ( STDMETHODCALLTYPE *FoundItem )( 
            ISyncDatabaseGenerateActionsCB * This,
            /* [in] */ IShellItem *psi);
        
        END_INTERFACE
    } ISyncDatabaseGenerateActionsCBVtbl;

    interface ISyncDatabaseGenerateActionsCB
    {
        CONST_VTBL struct ISyncDatabaseGenerateActionsCBVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncDatabaseGenerateActionsCB_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncDatabaseGenerateActionsCB_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncDatabaseGenerateActionsCB_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncDatabaseGenerateActionsCB_Begin(This)	\
    ( (This)->lpVtbl -> Begin(This) ) 

#define ISyncDatabaseGenerateActionsCB_End(This)	\
    ( (This)->lpVtbl -> End(This) ) 

#define ISyncDatabaseGenerateActionsCB_FoundItem(This,psi)	\
    ( (This)->lpVtbl -> FoundItem(This,psi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncDatabaseGenerateActionsCB_Begin_Proxy( 
    ISyncDatabaseGenerateActionsCB * This);


void __RPC_STUB ISyncDatabaseGenerateActionsCB_Begin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabaseGenerateActionsCB_End_Proxy( 
    ISyncDatabaseGenerateActionsCB * This);


void __RPC_STUB ISyncDatabaseGenerateActionsCB_End_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabaseGenerateActionsCB_FoundItem_Proxy( 
    ISyncDatabaseGenerateActionsCB * This,
    /* [in] */ IShellItem *psi);


void __RPC_STUB ISyncDatabaseGenerateActionsCB_FoundItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncDatabaseGenerateActionsCB_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0333 */
/* [local] */ 

typedef 
enum _tagSYNCENGFLAGS
    {	SYNCENG_NORMAL	= 0,
	SYNCENG_ONEWAYSYNC	= 0x1,
	SYNCENG_ONECOPYPERVOLUME	= 0x2,
	SYNCENG_OFFLINE	= 0x4,
	SYNCENG_ENABLE_REMAP	= 0x8
    } 	SYNCENGFLAGS;

typedef 
enum _tagSYNCENGADDRELATIONSHIPFLAGS
    {	SYNCENG_ADDREL_NORMAL	= 0,
	SYNCENG_ADDREL_RECURSIVE	= 0x1,
	SYNCENG_ADDREL_REMAPDEST	= 0x2
    } 	SYNCENGADDRELATIONSHIPFLAGS;



extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0333_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0333_v0_0_s_ifspec;

#ifndef __ISyncDatabase_INTERFACE_DEFINED__
#define __ISyncDatabase_INTERFACE_DEFINED__

/* interface ISyncDatabase */
/* [uuid][object] */ 


EXTERN_C const IID IID_ISyncDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32a86a13-5a3d-49e6-8fac-46512adc339a")
    ISyncDatabase : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IShellItem *psiDB,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddRelationship( 
            /* [in] */ IShellItem *psi1,
            /* [in] */ IShellItem *psi2,
            /* [in] */ DWORD dwFlags,
            /* [optional][out] */ ISyncRelationship **pprel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteRelationship( 
            /* [in] */ ISyncRelationship *prel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumRelationships( 
            /* [retval][out] */ IEnumSyncRelationship **pprelEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GenerateSyncActions( 
            /* [optional][in] */ ISyncDatabaseGenerateActionsCB *pfnCallback,
            /* [retval][out] */ ISyncReconciliationList **ppreclist) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncDatabase * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncDatabase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ISyncDatabase * This,
            /* [in] */ IShellItem *psiDB,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Commit )( 
            ISyncDatabase * This);
        
        HRESULT ( STDMETHODCALLTYPE *AddRelationship )( 
            ISyncDatabase * This,
            /* [in] */ IShellItem *psi1,
            /* [in] */ IShellItem *psi2,
            /* [in] */ DWORD dwFlags,
            /* [optional][out] */ ISyncRelationship **pprel);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteRelationship )( 
            ISyncDatabase * This,
            /* [in] */ ISyncRelationship *prel);
        
        HRESULT ( STDMETHODCALLTYPE *EnumRelationships )( 
            ISyncDatabase * This,
            /* [retval][out] */ IEnumSyncRelationship **pprelEnum);
        
        HRESULT ( STDMETHODCALLTYPE *GenerateSyncActions )( 
            ISyncDatabase * This,
            /* [optional][in] */ ISyncDatabaseGenerateActionsCB *pfnCallback,
            /* [retval][out] */ ISyncReconciliationList **ppreclist);
        
        END_INTERFACE
    } ISyncDatabaseVtbl;

    interface ISyncDatabase
    {
        CONST_VTBL struct ISyncDatabaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncDatabase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncDatabase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncDatabase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncDatabase_Initialize(This,psiDB,dwFlags)	\
    ( (This)->lpVtbl -> Initialize(This,psiDB,dwFlags) ) 

#define ISyncDatabase_Commit(This)	\
    ( (This)->lpVtbl -> Commit(This) ) 

#define ISyncDatabase_AddRelationship(This,psi1,psi2,dwFlags,pprel)	\
    ( (This)->lpVtbl -> AddRelationship(This,psi1,psi2,dwFlags,pprel) ) 

#define ISyncDatabase_DeleteRelationship(This,prel)	\
    ( (This)->lpVtbl -> DeleteRelationship(This,prel) ) 

#define ISyncDatabase_EnumRelationships(This,pprelEnum)	\
    ( (This)->lpVtbl -> EnumRelationships(This,pprelEnum) ) 

#define ISyncDatabase_GenerateSyncActions(This,pfnCallback,ppreclist)	\
    ( (This)->lpVtbl -> GenerateSyncActions(This,pfnCallback,ppreclist) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncDatabase_Initialize_Proxy( 
    ISyncDatabase * This,
    /* [in] */ IShellItem *psiDB,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB ISyncDatabase_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabase_Commit_Proxy( 
    ISyncDatabase * This);


void __RPC_STUB ISyncDatabase_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabase_AddRelationship_Proxy( 
    ISyncDatabase * This,
    /* [in] */ IShellItem *psi1,
    /* [in] */ IShellItem *psi2,
    /* [in] */ DWORD dwFlags,
    /* [optional][out] */ ISyncRelationship **pprel);


void __RPC_STUB ISyncDatabase_AddRelationship_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabase_DeleteRelationship_Proxy( 
    ISyncDatabase * This,
    /* [in] */ ISyncRelationship *prel);


void __RPC_STUB ISyncDatabase_DeleteRelationship_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabase_EnumRelationships_Proxy( 
    ISyncDatabase * This,
    /* [retval][out] */ IEnumSyncRelationship **pprelEnum);


void __RPC_STUB ISyncDatabase_EnumRelationships_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncDatabase_GenerateSyncActions_Proxy( 
    ISyncDatabase * This,
    /* [optional][in] */ ISyncDatabaseGenerateActionsCB *pfnCallback,
    /* [retval][out] */ ISyncReconciliationList **ppreclist);


void __RPC_STUB ISyncDatabase_GenerateSyncActions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncDatabase_INTERFACE_DEFINED__ */


#ifndef __IRelatedItem_INTERFACE_DEFINED__
#define __IRelatedItem_INTERFACE_DEFINED__

/* interface IRelatedItem */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IRelatedItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a73ce67a-8ab1-44f1-8d43-d2fcbf6b1cd0")
    IRelatedItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetItemIDList( 
            PIDLIST_ABSOLUTE *ppidl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItem( 
            IShellItem **ppsi) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRelatedItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRelatedItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRelatedItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRelatedItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemIDList )( 
            IRelatedItem * This,
            PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetItem )( 
            IRelatedItem * This,
            IShellItem **ppsi);
        
        END_INTERFACE
    } IRelatedItemVtbl;

    interface IRelatedItem
    {
        CONST_VTBL struct IRelatedItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRelatedItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRelatedItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRelatedItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRelatedItem_GetItemIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetItemIDList(This,ppidl) ) 

#define IRelatedItem_GetItem(This,ppsi)	\
    ( (This)->lpVtbl -> GetItem(This,ppsi) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRelatedItem_GetItemIDList_Proxy( 
    IRelatedItem * This,
    PIDLIST_ABSOLUTE *ppidl);


void __RPC_STUB IRelatedItem_GetItemIDList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRelatedItem_GetItem_Proxy( 
    IRelatedItem * This,
    IShellItem **ppsi);


void __RPC_STUB IRelatedItem_GetItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRelatedItem_INTERFACE_DEFINED__ */


#ifndef __IIdentityName_INTERFACE_DEFINED__
#define __IIdentityName_INTERFACE_DEFINED__

/* interface IIdentityName */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IIdentityName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7d903fca-d6f9-4810-8332-946c0177e247")
    IIdentityName : public IRelatedItem
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IIdentityNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIdentityName * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIdentityName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIdentityName * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemIDList )( 
            IIdentityName * This,
            PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetItem )( 
            IIdentityName * This,
            IShellItem **ppsi);
        
        END_INTERFACE
    } IIdentityNameVtbl;

    interface IIdentityName
    {
        CONST_VTBL struct IIdentityNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIdentityName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIdentityName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIdentityName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIdentityName_GetItemIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetItemIDList(This,ppidl) ) 

#define IIdentityName_GetItem(This,ppsi)	\
    ( (This)->lpVtbl -> GetItem(This,ppsi) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIdentityName_INTERFACE_DEFINED__ */


#ifndef __ICurrentItem_INTERFACE_DEFINED__
#define __ICurrentItem_INTERFACE_DEFINED__

/* interface ICurrentItem */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_ICurrentItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("240a7174-d653-4a1d-a6d3-d4943cfbfe3d")
    ICurrentItem : public IRelatedItem
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICurrentItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICurrentItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICurrentItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICurrentItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemIDList )( 
            ICurrentItem * This,
            PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetItem )( 
            ICurrentItem * This,
            IShellItem **ppsi);
        
        END_INTERFACE
    } ICurrentItemVtbl;

    interface ICurrentItem
    {
        CONST_VTBL struct ICurrentItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICurrentItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICurrentItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICurrentItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICurrentItem_GetItemIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetItemIDList(This,ppidl) ) 

#define ICurrentItem_GetItem(This,ppsi)	\
    ( (This)->lpVtbl -> GetItem(This,ppsi) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICurrentItem_INTERFACE_DEFINED__ */


#ifndef __IStorageItem_INTERFACE_DEFINED__
#define __IStorageItem_INTERFACE_DEFINED__

/* interface IStorageItem */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IStorageItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e5e4077b-39cd-497a-b570-17464059f119")
    IStorageItem : public IRelatedItem
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IStorageItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStorageItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStorageItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStorageItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemIDList )( 
            IStorageItem * This,
            PIDLIST_ABSOLUTE *ppidl);
        
        HRESULT ( STDMETHODCALLTYPE *GetItem )( 
            IStorageItem * This,
            IShellItem **ppsi);
        
        END_INTERFACE
    } IStorageItemVtbl;

    interface IStorageItem
    {
        CONST_VTBL struct IStorageItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStorageItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStorageItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStorageItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStorageItem_GetItemIDList(This,ppidl)	\
    ( (This)->lpVtbl -> GetItemIDList(This,ppidl) ) 

#define IStorageItem_GetItem(This,ppsi)	\
    ( (This)->lpVtbl -> GetItem(This,ppsi) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStorageItem_INTERFACE_DEFINED__ */


#ifndef __IInitializeWithStream_INTERFACE_DEFINED__
#define __IInitializeWithStream_INTERFACE_DEFINED__

/* interface IInitializeWithStream */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IInitializeWithStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64aa0878-44d1-47f2-a460-f24d946f1d7e")
    IInitializeWithStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IStream *pstm,
            /* [in] */ DWORD grfMode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInitializeWithStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInitializeWithStream * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInitializeWithStream * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInitializeWithStream * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IInitializeWithStream * This,
            /* [in] */ IStream *pstm,
            /* [in] */ DWORD grfMode);
        
        END_INTERFACE
    } IInitializeWithStreamVtbl;

    interface IInitializeWithStream
    {
        CONST_VTBL struct IInitializeWithStreamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInitializeWithStream_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IInitializeWithStream_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IInitializeWithStream_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IInitializeWithStream_Initialize(This,pstm,grfMode)	\
    ( (This)->lpVtbl -> Initialize(This,pstm,grfMode) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IInitializeWithStream_Initialize_Proxy( 
    IInitializeWithStream * This,
    /* [in] */ IStream *pstm,
    /* [in] */ DWORD grfMode);


void __RPC_STUB IInitializeWithStream_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInitializeWithStream_INTERFACE_DEFINED__ */


#ifndef __ISafeCommit_INTERFACE_DEFINED__
#define __ISafeCommit_INTERFACE_DEFINED__

/* interface ISafeCommit */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_ISafeCommit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A3028C8-B830-4f02-8C97-8390B134E1BD")
    ISafeCommit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetStream( 
            /* [out] */ IStream **ppstm) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( 
            /* [unique][in] */ LPCWSTR pszBackup) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISafeCommitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISafeCommit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISafeCommit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISafeCommit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetStream )( 
            ISafeCommit * This,
            /* [out] */ IStream **ppstm);
        
        HRESULT ( STDMETHODCALLTYPE *Commit )( 
            ISafeCommit * This,
            /* [unique][in] */ LPCWSTR pszBackup);
        
        END_INTERFACE
    } ISafeCommitVtbl;

    interface ISafeCommit
    {
        CONST_VTBL struct ISafeCommitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISafeCommit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISafeCommit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISafeCommit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISafeCommit_GetStream(This,ppstm)	\
    ( (This)->lpVtbl -> GetStream(This,ppstm) ) 

#define ISafeCommit_Commit(This,pszBackup)	\
    ( (This)->lpVtbl -> Commit(This,pszBackup) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISafeCommit_GetStream_Proxy( 
    ISafeCommit * This,
    /* [out] */ IStream **ppstm);


void __RPC_STUB ISafeCommit_GetStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISafeCommit_Commit_Proxy( 
    ISafeCommit * This,
    /* [unique][in] */ LPCWSTR pszBackup);


void __RPC_STUB ISafeCommit_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISafeCommit_INTERFACE_DEFINED__ */


#ifndef __IBandHost_INTERFACE_DEFINED__
#define __IBandHost_INTERFACE_DEFINED__

/* interface IBandHost */
/* [unique][object][uuid] */ 


EXTERN_C const IID IID_IBandHost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B9075C7C-D48E-403f-AB99-D6C77A1084AC")
    IBandHost : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateBand( 
            /* [in] */ REFCLSID rclsidBand,
            /* [in] */ BOOL fAvailable,
            /* [in] */ BOOL fVisible,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBandAvailability( 
            /* [in] */ REFCLSID rclsidBand,
            /* [in] */ BOOL fAvailable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DestroyBand( 
            /* [in] */ REFCLSID rclsidBand) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBandHostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBandHost * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBandHost * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBandHost * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateBand )( 
            IBandHost * This,
            /* [in] */ REFCLSID rclsidBand,
            /* [in] */ BOOL fAvailable,
            /* [in] */ BOOL fVisible,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *SetBandAvailability )( 
            IBandHost * This,
            /* [in] */ REFCLSID rclsidBand,
            /* [in] */ BOOL fAvailable);
        
        HRESULT ( STDMETHODCALLTYPE *DestroyBand )( 
            IBandHost * This,
            /* [in] */ REFCLSID rclsidBand);
        
        END_INTERFACE
    } IBandHostVtbl;

    interface IBandHost
    {
        CONST_VTBL struct IBandHostVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBandHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBandHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBandHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBandHost_CreateBand(This,rclsidBand,fAvailable,fVisible,riid,ppv)	\
    ( (This)->lpVtbl -> CreateBand(This,rclsidBand,fAvailable,fVisible,riid,ppv) ) 

#define IBandHost_SetBandAvailability(This,rclsidBand,fAvailable)	\
    ( (This)->lpVtbl -> SetBandAvailability(This,rclsidBand,fAvailable) ) 

#define IBandHost_DestroyBand(This,rclsidBand)	\
    ( (This)->lpVtbl -> DestroyBand(This,rclsidBand) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBandHost_CreateBand_Proxy( 
    IBandHost * This,
    /* [in] */ REFCLSID rclsidBand,
    /* [in] */ BOOL fAvailable,
    /* [in] */ BOOL fVisible,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IBandHost_CreateBand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandHost_SetBandAvailability_Proxy( 
    IBandHost * This,
    /* [in] */ REFCLSID rclsidBand,
    /* [in] */ BOOL fAvailable);


void __RPC_STUB IBandHost_SetBandAvailability_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBandHost_DestroyBand_Proxy( 
    IBandHost * This,
    /* [in] */ REFCLSID rclsidBand);


void __RPC_STUB IBandHost_DestroyBand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBandHost_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_shobjidl_0341 */
/* [local] */ 

#define SID_SBandHost IID_IBandHost


extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0341_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0341_v0_0_s_ifspec;

#ifndef __INewWindowManager_INTERFACE_DEFINED__
#define __INewWindowManager_INTERFACE_DEFINED__

/* interface INewWindowManager */
/* [unique][object][uuid] */ 


enum tagNWMF
    {	NWMF_UNLOADING	= 0x1,
	NWMF_USERINITED	= 0x2,
	NWMF_FIRST_USERINITED	= 0x4,
	NWMF_OVERRIDEKEY	= 0x8,
	NWMF_SHOWHELP	= 0x10
    } ;

EXTERN_C const IID IID_INewWindowManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCC802F2-6027-4524-8FD1-47522F98D2E7")
    INewWindowManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EvaluateNewWindow( 
            /* [in] */ LPCWSTR pszUrl,
            /* [in] */ LPCWSTR pszName,
            /* [in] */ LPCWSTR pszUrlContext,
            /* [in] */ LPCWSTR pszFeatures,
            /* [in] */ BOOL fReplace,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INewWindowManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INewWindowManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INewWindowManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INewWindowManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *EvaluateNewWindow )( 
            INewWindowManager * This,
            /* [in] */ LPCWSTR pszUrl,
            /* [in] */ LPCWSTR pszName,
            /* [in] */ LPCWSTR pszUrlContext,
            /* [in] */ LPCWSTR pszFeatures,
            /* [in] */ BOOL fReplace,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } INewWindowManagerVtbl;

    interface INewWindowManager
    {
        CONST_VTBL struct INewWindowManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INewWindowManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INewWindowManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INewWindowManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INewWindowManager_EvaluateNewWindow(This,pszUrl,pszName,pszUrlContext,pszFeatures,fReplace,dwFlags)	\
    ( (This)->lpVtbl -> EvaluateNewWindow(This,pszUrl,pszName,pszUrlContext,pszFeatures,fReplace,dwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INewWindowManager_EvaluateNewWindow_Proxy( 
    INewWindowManager * This,
    /* [in] */ LPCWSTR pszUrl,
    /* [in] */ LPCWSTR pszName,
    /* [in] */ LPCWSTR pszUrlContext,
    /* [in] */ LPCWSTR pszFeatures,
    /* [in] */ BOOL fReplace,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB INewWindowManager_EvaluateNewWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INewWindowManager_INTERFACE_DEFINED__ */


#ifndef __INavBar_INTERFACE_DEFINED__
#define __INavBar_INTERFACE_DEFINED__

/* interface INavBar */
/* [unique][object][uuid] */ 

typedef DWORD NAVBARSIZING;

/* [v1_enum] */ 
enum tagNAVBARSIZING
    {	NAVBAR_SMALL	= 0x1,
	NAVBAR_MEDIUM	= 0x2,
	NAVBAR_LARGE	= 0x3,
	NAVBAR_XLARGE	= 0x4,
	NAVBAR_DEFAULT	= 0x5,
	NAVBAR_CUSTOM	= 0x6
    } ;

EXTERN_C const IID IID_INavBar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C339211E-E4B5-4a2c-AD84-4042F8956AE9")
    INavBar : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetNavbarSize( 
            /* [in] */ DWORD dwSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INavBarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INavBar * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INavBar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INavBar * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetNavbarSize )( 
            INavBar * This,
            /* [in] */ DWORD dwSize);
        
        END_INTERFACE
    } INavBarVtbl;

    interface INavBar
    {
        CONST_VTBL struct INavBarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INavBar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INavBar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INavBar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define INavBar_SetNavbarSize(This,dwSize)	\
    ( (This)->lpVtbl -> SetNavbarSize(This,dwSize) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE INavBar_SetNavbarSize_Proxy( 
    INavBar * This,
    /* [in] */ DWORD dwSize);


void __RPC_STUB INavBar_SetNavbarSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INavBar_INTERFACE_DEFINED__ */



#ifndef __ShellObjects_LIBRARY_DEFINED__
#define __ShellObjects_LIBRARY_DEFINED__

/* library ShellObjects */
/* [version][lcid][helpstring][uuid] */ 

#define SID_PublishingWizard CLSID_PublishingWizard

EXTERN_C const IID LIBID_ShellObjects;

EXTERN_C const CLSID CLSID_QueryCancelAutoPlay;

#ifdef __cplusplus

class DECLSPEC_UUID("331F1768-05A9-4ddd-B86E-DAE34DDC998A")
QueryCancelAutoPlay;
#endif

EXTERN_C const CLSID CLSID_ImageProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("7ab770c7-0e23-4d7a-8aa2-19bfad479829")
ImageProperties;
#endif

EXTERN_C const CLSID CLSID_PropertiesUI;

#ifdef __cplusplus

class DECLSPEC_UUID("d912f8cf-0396-4915-884e-fb425d32943b")
PropertiesUI;
#endif

EXTERN_C const CLSID CLSID_UserNotification;

#ifdef __cplusplus

class DECLSPEC_UUID("0010890e-8789-413c-adbc-48f5b511b3af")
UserNotification;
#endif

EXTERN_C const CLSID CLSID_CDBurn;

#ifdef __cplusplus

class DECLSPEC_UUID("fbeb8a05-beee-4442-804e-409d6c4515e9")
CDBurn;
#endif

EXTERN_C const CLSID CLSID_TaskbarList;

#ifdef __cplusplus

class DECLSPEC_UUID("56FDF344-FD6D-11d0-958A-006097C9A090")
TaskbarList;
#endif

EXTERN_C const CLSID CLSID_WebWizardHost;

#ifdef __cplusplus

class DECLSPEC_UUID("c827f149-55c1-4d28-935e-57e47caed973")
WebWizardHost;
#endif

EXTERN_C const CLSID CLSID_PublishDropTarget;

#ifdef __cplusplus

class DECLSPEC_UUID("CC6EEFFB-43F6-46c5-9619-51D571967F7D")
PublishDropTarget;
#endif

EXTERN_C const CLSID CLSID_PublishingWizard;

#ifdef __cplusplus

class DECLSPEC_UUID("6b33163c-76a5-4b6c-bf21-45de9cd503a1")
PublishingWizard;
#endif

EXTERN_C const CLSID CLSID_InternetPrintOrdering;

#ifdef __cplusplus

class DECLSPEC_UUID("add36aa8-751a-4579-a266-d66f5202ccbb")
InternetPrintOrdering;
#endif

EXTERN_C const CLSID CLSID_FolderViewHost;

#ifdef __cplusplus

class DECLSPEC_UUID("20b1cb23-6968-4eb9-b7d4-a66d00d07cee")
FolderViewHost;
#endif

EXTERN_C const CLSID CLSID_ImageRecompress;

#ifdef __cplusplus

class DECLSPEC_UUID("6e33091c-d2f8-4740-b55e-2e11d1477a2c")
ImageRecompress;
#endif

EXTERN_C const CLSID CLSID_TrayBandSiteService;

#ifdef __cplusplus

class DECLSPEC_UUID("F60AD0A0-E5E1-45cb-B51A-E15B9F8B2934")
TrayBandSiteService;
#endif

EXTERN_C const CLSID CLSID_PassportWizard;

#ifdef __cplusplus

class DECLSPEC_UUID("58f1f272-9240-4f51-b6d4-fd63d1618591")
PassportWizard;
#endif

EXTERN_C const CLSID CLSID_DocPropShellExtension;

#ifdef __cplusplus

class DECLSPEC_UUID("883373C3-BF89-11D1-BE35-080036B11A03")
DocPropShellExtension;
#endif

EXTERN_C const CLSID CLSID_DocPropEditBoxControl;

#ifdef __cplusplus

class DECLSPEC_UUID("A9CF0EAE-901A-4739-A481-E35B73E47F6D")
DocPropEditBoxControl;
#endif

EXTERN_C const CLSID CLSID_DocPropMLEditBoxControl;

#ifdef __cplusplus

class DECLSPEC_UUID("8EE97210-FD1F-4b19-91DA-67914005F020")
DocPropMLEditBoxControl;
#endif

EXTERN_C const CLSID CLSID_DocPropDropListComboControl;

#ifdef __cplusplus

class DECLSPEC_UUID("0EEA25CC-4362-4a12-850B-86EE61B0D3EB")
DocPropDropListComboControl;
#endif

EXTERN_C const CLSID CLSID_DocPropCalendarControl;

#ifdef __cplusplus

class DECLSPEC_UUID("6A205B57-2567-4a2c-B881-F787FAB579A3")
DocPropCalendarControl;
#endif

EXTERN_C const CLSID CLSID_DocPropDrawRatingControl;

#ifdef __cplusplus

class DECLSPEC_UUID("4AB4E1C2-A928-4d32-BD4D-B4159D33917E")
DocPropDrawRatingControl;
#endif

EXTERN_C const CLSID CLSID_DocPropEditRatingControl;

#ifdef __cplusplus

class DECLSPEC_UUID("033DB6C8-EEFE-4852-A080-5BCBFA6759DA")
DocPropEditRatingControl;
#endif

EXTERN_C const CLSID CLSID_DocPropDrawPercentFullControl;

#ifdef __cplusplus

class DECLSPEC_UUID("AB517586-73CF-489c-8D8C-5AE0EAD0613A")
DocPropDrawPercentFullControl;
#endif

EXTERN_C const CLSID CLSID_DocPropMultiValuePropertyControl;

#ifdef __cplusplus

class DECLSPEC_UUID("f444b20e-58ec-4b65-88c3-78fa9395b5a2")
DocPropMultiValuePropertyControl;
#endif

EXTERN_C const CLSID CLSID_StickyNoteDisplayControl;

#ifdef __cplusplus

class DECLSPEC_UUID("2BE90585-29CE-41d1-A042-DE8F40B63DA5")
StickyNoteDisplayControl;
#endif

EXTERN_C const CLSID CLSID_ShellItem;

#ifdef __cplusplus

class DECLSPEC_UUID("9ac9fbe1-e0a2-4ad6-b4ee-e212013ea917")
ShellItem;
#endif

EXTERN_C const CLSID CLSID_NamespaceWalker;

#ifdef __cplusplus

class DECLSPEC_UUID("72eb61e0-8672-4303-9175-f2e4c68b2e7c")
NamespaceWalker;
#endif

EXTERN_C const CLSID CLSID_KeywordList;

#ifdef __cplusplus

class DECLSPEC_UUID("EFDCF468-B5DD-4c7e-97F5-0B53DC064BA5")
KeywordList;
#endif

EXTERN_C const CLSID CLSID_ModalKeywordEditor;

#ifdef __cplusplus

class DECLSPEC_UUID("126455EE-AA1B-476c-B74B-5AECB535BBAD")
ModalKeywordEditor;
#endif

EXTERN_C const CLSID CLSID_FileOperation;

#ifdef __cplusplus

class DECLSPEC_UUID("3ad05575-8857-4850-9277-11b85bdb8e09")
FileOperation;
#endif

EXTERN_C const CLSID CLSID_FileOpenDialog;

#ifdef __cplusplus

class DECLSPEC_UUID("DC1C5A9C-E88A-4dde-A5A1-60F82A20AEF7")
FileOpenDialog;
#endif

EXTERN_C const CLSID CLSID_FileSaveDialog;

#ifdef __cplusplus

class DECLSPEC_UUID("C0B4E2F3-BA21-4773-8DBA-335EC946EB8B")
FileSaveDialog;
#endif

EXTERN_C const CLSID CLSID_PropertyStore;

#ifdef __cplusplus

class DECLSPEC_UUID("61559f58-a1b1-4e0c-8887-e3d5d60d4ced")
PropertyStore;
#endif

EXTERN_C const CLSID CLSID_PlaylistEditor;

#ifdef __cplusplus

class DECLSPEC_UUID("8014DF66-DBF0-4f32-9C15-63AA96DBF668")
PlaylistEditor;
#endif

EXTERN_C const CLSID CLSID_FolderInformation;

#ifdef __cplusplus

class DECLSPEC_UUID("6ad381f2-d036-4a49-8f29-7e9b6812b3e4")
FolderInformation;
#endif

EXTERN_C const CLSID CLSID_FSCopyHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("D197380A-0A79-4dc8-A033-ED882C2FA14B")
FSCopyHandler;
#endif

EXTERN_C const CLSID CLSID_ShareManager;

#ifdef __cplusplus

class DECLSPEC_UUID("edb5f444-cb8d-445a-a523-ec5ab6ea33c7")
ShareManager;
#endif

EXTERN_C const CLSID CLSID_PreviousVersions;

#ifdef __cplusplus

class DECLSPEC_UUID("596AB062-B4D2-4215-9F74-E9109B0A8153")
PreviousVersions;
#endif

EXTERN_C const CLSID CLSID_LaunchComposeWindow;

#ifdef __cplusplus

class DECLSPEC_UUID("C1669D05-2CB2-4e32-8E46-5E1BEAD0FDF1")
LaunchComposeWindow;
#endif

EXTERN_C const CLSID CLSID_BasketControl;

#ifdef __cplusplus

class DECLSPEC_UUID("CF698731-C297-45CB-BE29-CA256AA8EFC3")
BasketControl;
#endif

EXTERN_C const CLSID CLSID_ListMakerControl;

#ifdef __cplusplus

class DECLSPEC_UUID("9E0D5252-7BC9-407A-B69E-446CF891ABD4")
ListMakerControl;
#endif

EXTERN_C const CLSID CLSID_SyncDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("9d161572-d3c1-4022-a2ee-e4480f0c3aca")
SyncDatabase;
#endif

EXTERN_C const CLSID CLSID_DevicePickerDialog;

#ifdef __cplusplus

class DECLSPEC_UUID("9ba04337-a946-4113-9b9b-ea17717da288")
DevicePickerDialog;
#endif

EXTERN_C const CLSID CLSID_DevicePickerFolderViewHost;

#ifdef __cplusplus

class DECLSPEC_UUID("89acdf59-3d16-4f13-a576-9254971b1ce4")
DevicePickerFolderViewHost;
#endif

EXTERN_C const CLSID CLSID_NetworkConnections;

#ifdef __cplusplus

class DECLSPEC_UUID("7007ACC7-3202-11D1-AAD2-00805FC1270E")
NetworkConnections;
#endif

EXTERN_C const CLSID CLSID_ScheduledTasks;

#ifdef __cplusplus

class DECLSPEC_UUID("D6277990-4C6A-11CF-8D87-00AA0060F5BF")
ScheduledTasks;
#endif
#endif /* __ShellObjects_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_shobjidl_0343 */
/* [local] */ 

SHSTDAPI SHGetTemporaryPropertyForItem(IShellItem *psi, REFPROPERTYKEY pk, PROPVARIANT * pvInk);
SHSTDAPI SHSetTemporaryPropertyForItem(IShellItem *psi, REFPROPERTYKEY pk, const PROPVARIANT * pvInk);

extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0343_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_shobjidl_0343_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HBITMAP_UserSize(     unsigned long *, unsigned long            , HBITMAP * ); 
unsigned char * __RPC_USER  HBITMAP_UserMarshal(  unsigned long *, unsigned char *, HBITMAP * ); 
unsigned char * __RPC_USER  HBITMAP_UserUnmarshal(unsigned long *, unsigned char *, HBITMAP * ); 
void                      __RPC_USER  HBITMAP_UserFree(     unsigned long *, HBITMAP * ); 

unsigned long             __RPC_USER  HGLOBAL_UserSize(     unsigned long *, unsigned long            , HGLOBAL * ); 
unsigned char * __RPC_USER  HGLOBAL_UserMarshal(  unsigned long *, unsigned char *, HGLOBAL * ); 
unsigned char * __RPC_USER  HGLOBAL_UserUnmarshal(unsigned long *, unsigned char *, HGLOBAL * ); 
void                      __RPC_USER  HGLOBAL_UserFree(     unsigned long *, HGLOBAL * ); 

unsigned long             __RPC_USER  HICON_UserSize(     unsigned long *, unsigned long            , HICON * ); 
unsigned char * __RPC_USER  HICON_UserMarshal(  unsigned long *, unsigned char *, HICON * ); 
unsigned char * __RPC_USER  HICON_UserUnmarshal(unsigned long *, unsigned char *, HICON * ); 
void                      __RPC_USER  HICON_UserFree(     unsigned long *, HICON * ); 

unsigned long             __RPC_USER  HMENU_UserSize(     unsigned long *, unsigned long            , HMENU * ); 
unsigned char * __RPC_USER  HMENU_UserMarshal(  unsigned long *, unsigned char *, HMENU * ); 
unsigned char * __RPC_USER  HMENU_UserUnmarshal(unsigned long *, unsigned char *, HMENU * ); 
void                      __RPC_USER  HMENU_UserFree(     unsigned long *, HMENU * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  PCIDLIST_ABSOLUTE_UserSize(     unsigned long *, unsigned long            , PCIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PCIDLIST_ABSOLUTE_UserMarshal(  unsigned long *, unsigned char *, PCIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PCIDLIST_ABSOLUTE_UserUnmarshal(unsigned long *, unsigned char *, PCIDLIST_ABSOLUTE * ); 
void                      __RPC_USER  PCIDLIST_ABSOLUTE_UserFree(     unsigned long *, PCIDLIST_ABSOLUTE * ); 

unsigned long             __RPC_USER  PCUIDLIST_RELATIVE_UserSize(     unsigned long *, unsigned long            , PCUIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PCUIDLIST_RELATIVE_UserMarshal(  unsigned long *, unsigned char *, PCUIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PCUIDLIST_RELATIVE_UserUnmarshal(unsigned long *, unsigned char *, PCUIDLIST_RELATIVE * ); 
void                      __RPC_USER  PCUIDLIST_RELATIVE_UserFree(     unsigned long *, PCUIDLIST_RELATIVE * ); 

unsigned long             __RPC_USER  PCUITEMID_CHILD_UserSize(     unsigned long *, unsigned long            , PCUITEMID_CHILD * ); 
unsigned char * __RPC_USER  PCUITEMID_CHILD_UserMarshal(  unsigned long *, unsigned char *, PCUITEMID_CHILD * ); 
unsigned char * __RPC_USER  PCUITEMID_CHILD_UserUnmarshal(unsigned long *, unsigned char *, PCUITEMID_CHILD * ); 
void                      __RPC_USER  PCUITEMID_CHILD_UserFree(     unsigned long *, PCUITEMID_CHILD * ); 

unsigned long             __RPC_USER  PIDLIST_ABSOLUTE_UserSize(     unsigned long *, unsigned long            , PIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PIDLIST_ABSOLUTE_UserMarshal(  unsigned long *, unsigned char *, PIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PIDLIST_ABSOLUTE_UserUnmarshal(unsigned long *, unsigned char *, PIDLIST_ABSOLUTE * ); 
void                      __RPC_USER  PIDLIST_ABSOLUTE_UserFree(     unsigned long *, PIDLIST_ABSOLUTE * ); 

unsigned long             __RPC_USER  PIDLIST_RELATIVE_UserSize(     unsigned long *, unsigned long            , PIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PIDLIST_RELATIVE_UserMarshal(  unsigned long *, unsigned char *, PIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PIDLIST_RELATIVE_UserUnmarshal(unsigned long *, unsigned char *, PIDLIST_RELATIVE * ); 
void                      __RPC_USER  PIDLIST_RELATIVE_UserFree(     unsigned long *, PIDLIST_RELATIVE * ); 

unsigned long             __RPC_USER  PITEMID_CHILD_UserSize(     unsigned long *, unsigned long            , PITEMID_CHILD * ); 
unsigned char * __RPC_USER  PITEMID_CHILD_UserMarshal(  unsigned long *, unsigned char *, PITEMID_CHILD * ); 
unsigned char * __RPC_USER  PITEMID_CHILD_UserUnmarshal(unsigned long *, unsigned char *, PITEMID_CHILD * ); 
void                      __RPC_USER  PITEMID_CHILD_UserFree(     unsigned long *, PITEMID_CHILD * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HBITMAP_UserSize64(     unsigned long *, unsigned long            , HBITMAP * ); 
unsigned char * __RPC_USER  HBITMAP_UserMarshal64(  unsigned long *, unsigned char *, HBITMAP * ); 
unsigned char * __RPC_USER  HBITMAP_UserUnmarshal64(unsigned long *, unsigned char *, HBITMAP * ); 
void                      __RPC_USER  HBITMAP_UserFree64(     unsigned long *, HBITMAP * ); 

unsigned long             __RPC_USER  HGLOBAL_UserSize64(     unsigned long *, unsigned long            , HGLOBAL * ); 
unsigned char * __RPC_USER  HGLOBAL_UserMarshal64(  unsigned long *, unsigned char *, HGLOBAL * ); 
unsigned char * __RPC_USER  HGLOBAL_UserUnmarshal64(unsigned long *, unsigned char *, HGLOBAL * ); 
void                      __RPC_USER  HGLOBAL_UserFree64(     unsigned long *, HGLOBAL * ); 

unsigned long             __RPC_USER  HICON_UserSize64(     unsigned long *, unsigned long            , HICON * ); 
unsigned char * __RPC_USER  HICON_UserMarshal64(  unsigned long *, unsigned char *, HICON * ); 
unsigned char * __RPC_USER  HICON_UserUnmarshal64(unsigned long *, unsigned char *, HICON * ); 
void                      __RPC_USER  HICON_UserFree64(     unsigned long *, HICON * ); 

unsigned long             __RPC_USER  HMENU_UserSize64(     unsigned long *, unsigned long            , HMENU * ); 
unsigned char * __RPC_USER  HMENU_UserMarshal64(  unsigned long *, unsigned char *, HMENU * ); 
unsigned char * __RPC_USER  HMENU_UserUnmarshal64(unsigned long *, unsigned char *, HMENU * ); 
void                      __RPC_USER  HMENU_UserFree64(     unsigned long *, HMENU * ); 

unsigned long             __RPC_USER  HWND_UserSize64(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal64(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal64(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree64(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize64(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal64(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal64(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree64(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  PCIDLIST_ABSOLUTE_UserSize64(     unsigned long *, unsigned long            , PCIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PCIDLIST_ABSOLUTE_UserMarshal64(  unsigned long *, unsigned char *, PCIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PCIDLIST_ABSOLUTE_UserUnmarshal64(unsigned long *, unsigned char *, PCIDLIST_ABSOLUTE * ); 
void                      __RPC_USER  PCIDLIST_ABSOLUTE_UserFree64(     unsigned long *, PCIDLIST_ABSOLUTE * ); 

unsigned long             __RPC_USER  PCUIDLIST_RELATIVE_UserSize64(     unsigned long *, unsigned long            , PCUIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PCUIDLIST_RELATIVE_UserMarshal64(  unsigned long *, unsigned char *, PCUIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PCUIDLIST_RELATIVE_UserUnmarshal64(unsigned long *, unsigned char *, PCUIDLIST_RELATIVE * ); 
void                      __RPC_USER  PCUIDLIST_RELATIVE_UserFree64(     unsigned long *, PCUIDLIST_RELATIVE * ); 

unsigned long             __RPC_USER  PCUITEMID_CHILD_UserSize64(     unsigned long *, unsigned long            , PCUITEMID_CHILD * ); 
unsigned char * __RPC_USER  PCUITEMID_CHILD_UserMarshal64(  unsigned long *, unsigned char *, PCUITEMID_CHILD * ); 
unsigned char * __RPC_USER  PCUITEMID_CHILD_UserUnmarshal64(unsigned long *, unsigned char *, PCUITEMID_CHILD * ); 
void                      __RPC_USER  PCUITEMID_CHILD_UserFree64(     unsigned long *, PCUITEMID_CHILD * ); 

unsigned long             __RPC_USER  PIDLIST_ABSOLUTE_UserSize64(     unsigned long *, unsigned long            , PIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PIDLIST_ABSOLUTE_UserMarshal64(  unsigned long *, unsigned char *, PIDLIST_ABSOLUTE * ); 
unsigned char * __RPC_USER  PIDLIST_ABSOLUTE_UserUnmarshal64(unsigned long *, unsigned char *, PIDLIST_ABSOLUTE * ); 
void                      __RPC_USER  PIDLIST_ABSOLUTE_UserFree64(     unsigned long *, PIDLIST_ABSOLUTE * ); 

unsigned long             __RPC_USER  PIDLIST_RELATIVE_UserSize64(     unsigned long *, unsigned long            , PIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PIDLIST_RELATIVE_UserMarshal64(  unsigned long *, unsigned char *, PIDLIST_RELATIVE * ); 
unsigned char * __RPC_USER  PIDLIST_RELATIVE_UserUnmarshal64(unsigned long *, unsigned char *, PIDLIST_RELATIVE * ); 
void                      __RPC_USER  PIDLIST_RELATIVE_UserFree64(     unsigned long *, PIDLIST_RELATIVE * ); 

unsigned long             __RPC_USER  PITEMID_CHILD_UserSize64(     unsigned long *, unsigned long            , PITEMID_CHILD * ); 
unsigned char * __RPC_USER  PITEMID_CHILD_UserMarshal64(  unsigned long *, unsigned char *, PITEMID_CHILD * ); 
unsigned char * __RPC_USER  PITEMID_CHILD_UserUnmarshal64(unsigned long *, unsigned char *, PITEMID_CHILD * ); 
void                      __RPC_USER  PITEMID_CHILD_UserFree64(     unsigned long *, PITEMID_CHILD * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* [local] */ HRESULT STDMETHODCALLTYPE IModalWindow_Show_Proxy( 
    IModalWindow * This,
    /* [in] */ HWND hwndParent);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IModalWindow_Show_Stub( 
    IModalWindow * This,
    /* [in] */ HWND hwndParent);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif




