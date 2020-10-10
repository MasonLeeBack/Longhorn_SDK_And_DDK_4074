

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for wia.idl, wia.acf:
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

#ifndef __wia_h__
#define __wia_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWiaDevMgr_FWD_DEFINED__
#define __IWiaDevMgr_FWD_DEFINED__
typedef interface IWiaDevMgr IWiaDevMgr;
#endif 	/* __IWiaDevMgr_FWD_DEFINED__ */


#ifndef __IEnumWIA_DEV_INFO_FWD_DEFINED__
#define __IEnumWIA_DEV_INFO_FWD_DEFINED__
typedef interface IEnumWIA_DEV_INFO IEnumWIA_DEV_INFO;
#endif 	/* __IEnumWIA_DEV_INFO_FWD_DEFINED__ */


#ifndef __IWiaEventCallback_FWD_DEFINED__
#define __IWiaEventCallback_FWD_DEFINED__
typedef interface IWiaEventCallback IWiaEventCallback;
#endif 	/* __IWiaEventCallback_FWD_DEFINED__ */


#ifndef __IWiaDataCallback_FWD_DEFINED__
#define __IWiaDataCallback_FWD_DEFINED__
typedef interface IWiaDataCallback IWiaDataCallback;
#endif 	/* __IWiaDataCallback_FWD_DEFINED__ */


#ifndef __IWiaDataTransfer_FWD_DEFINED__
#define __IWiaDataTransfer_FWD_DEFINED__
typedef interface IWiaDataTransfer IWiaDataTransfer;
#endif 	/* __IWiaDataTransfer_FWD_DEFINED__ */


#ifndef __IWiaItem_FWD_DEFINED__
#define __IWiaItem_FWD_DEFINED__
typedef interface IWiaItem IWiaItem;
#endif 	/* __IWiaItem_FWD_DEFINED__ */


#ifndef __IWiaPropertyStorage_FWD_DEFINED__
#define __IWiaPropertyStorage_FWD_DEFINED__
typedef interface IWiaPropertyStorage IWiaPropertyStorage;
#endif 	/* __IWiaPropertyStorage_FWD_DEFINED__ */


#ifndef __IEnumWiaItem_FWD_DEFINED__
#define __IEnumWiaItem_FWD_DEFINED__
typedef interface IEnumWiaItem IEnumWiaItem;
#endif 	/* __IEnumWiaItem_FWD_DEFINED__ */


#ifndef __IEnumWIA_DEV_CAPS_FWD_DEFINED__
#define __IEnumWIA_DEV_CAPS_FWD_DEFINED__
typedef interface IEnumWIA_DEV_CAPS IEnumWIA_DEV_CAPS;
#endif 	/* __IEnumWIA_DEV_CAPS_FWD_DEFINED__ */


#ifndef __IEnumWIA_FORMAT_INFO_FWD_DEFINED__
#define __IEnumWIA_FORMAT_INFO_FWD_DEFINED__
typedef interface IEnumWIA_FORMAT_INFO IEnumWIA_FORMAT_INFO;
#endif 	/* __IEnumWIA_FORMAT_INFO_FWD_DEFINED__ */


#ifndef __IWiaLog_FWD_DEFINED__
#define __IWiaLog_FWD_DEFINED__
typedef interface IWiaLog IWiaLog;
#endif 	/* __IWiaLog_FWD_DEFINED__ */


#ifndef __IWiaLogEx_FWD_DEFINED__
#define __IWiaLogEx_FWD_DEFINED__
typedef interface IWiaLogEx IWiaLogEx;
#endif 	/* __IWiaLogEx_FWD_DEFINED__ */


#ifndef __IWiaNotifyDevMgr_FWD_DEFINED__
#define __IWiaNotifyDevMgr_FWD_DEFINED__
typedef interface IWiaNotifyDevMgr IWiaNotifyDevMgr;
#endif 	/* __IWiaNotifyDevMgr_FWD_DEFINED__ */


#ifndef __IWiaItemExtras_FWD_DEFINED__
#define __IWiaItemExtras_FWD_DEFINED__
typedef interface IWiaItemExtras IWiaItemExtras;
#endif 	/* __IWiaItemExtras_FWD_DEFINED__ */


#ifndef __IWiaAppErrorHandler_FWD_DEFINED__
#define __IWiaAppErrorHandler_FWD_DEFINED__
typedef interface IWiaAppErrorHandler IWiaAppErrorHandler;
#endif 	/* __IWiaAppErrorHandler_FWD_DEFINED__ */


#ifndef __IWiaErrorHandler_FWD_DEFINED__
#define __IWiaErrorHandler_FWD_DEFINED__
typedef interface IWiaErrorHandler IWiaErrorHandler;
#endif 	/* __IWiaErrorHandler_FWD_DEFINED__ */


#ifndef __IWiaTransfer_FWD_DEFINED__
#define __IWiaTransfer_FWD_DEFINED__
typedef interface IWiaTransfer IWiaTransfer;
#endif 	/* __IWiaTransfer_FWD_DEFINED__ */


#ifndef __IWiaTransferCallback_FWD_DEFINED__
#define __IWiaTransferCallback_FWD_DEFINED__
typedef interface IWiaTransferCallback IWiaTransferCallback;
#endif 	/* __IWiaTransferCallback_FWD_DEFINED__ */


#ifndef __IWiaSegmentationFilter_FWD_DEFINED__
#define __IWiaSegmentationFilter_FWD_DEFINED__
typedef interface IWiaSegmentationFilter IWiaSegmentationFilter;
#endif 	/* __IWiaSegmentationFilter_FWD_DEFINED__ */


#ifndef __IWiaImageFilter_FWD_DEFINED__
#define __IWiaImageFilter_FWD_DEFINED__
typedef interface IWiaImageFilter IWiaImageFilter;
#endif 	/* __IWiaImageFilter_FWD_DEFINED__ */


#ifndef __IWiaPreview_FWD_DEFINED__
#define __IWiaPreview_FWD_DEFINED__
typedef interface IWiaPreview IWiaPreview;
#endif 	/* __IWiaPreview_FWD_DEFINED__ */


#ifndef __IEnumWiaItem2_FWD_DEFINED__
#define __IEnumWiaItem2_FWD_DEFINED__
typedef interface IEnumWiaItem2 IEnumWiaItem2;
#endif 	/* __IEnumWiaItem2_FWD_DEFINED__ */


#ifndef __IWiaItem2_FWD_DEFINED__
#define __IWiaItem2_FWD_DEFINED__
typedef interface IWiaItem2 IWiaItem2;
#endif 	/* __IWiaItem2_FWD_DEFINED__ */


#ifndef __IWiaDevMgr2_FWD_DEFINED__
#define __IWiaDevMgr2_FWD_DEFINED__
typedef interface IWiaDevMgr2 IWiaDevMgr2;
#endif 	/* __IWiaDevMgr2_FWD_DEFINED__ */


#ifndef __WiaDevMgr_FWD_DEFINED__
#define __WiaDevMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class WiaDevMgr WiaDevMgr;
#else
typedef struct WiaDevMgr WiaDevMgr;
#endif /* __cplusplus */

#endif 	/* __WiaDevMgr_FWD_DEFINED__ */


#ifndef __WiaDevMgr2_FWD_DEFINED__
#define __WiaDevMgr2_FWD_DEFINED__

#ifdef __cplusplus
typedef class WiaDevMgr2 WiaDevMgr2;
#else
typedef struct WiaDevMgr2 WiaDevMgr2;
#endif /* __cplusplus */

#endif 	/* __WiaDevMgr2_FWD_DEFINED__ */


#ifndef __WiaLog_FWD_DEFINED__
#define __WiaLog_FWD_DEFINED__

#ifdef __cplusplus
typedef class WiaLog WiaLog;
#else
typedef struct WiaLog WiaLog;
#endif /* __cplusplus */

#endif 	/* __WiaLog_FWD_DEFINED__ */


#ifndef __WiaPreview_FWD_DEFINED__
#define __WiaPreview_FWD_DEFINED__

#ifdef __cplusplus
typedef class WiaPreview WiaPreview;
#else
typedef struct WiaPreview WiaPreview;
#endif /* __cplusplus */

#endif 	/* __WiaPreview_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"
#include "propidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wia_0000 */
/* [local] */ 


















typedef struct _WIA_DITHER_PATTERN_DATA
    {
    LONG lSize;
    BSTR bstrPatternName;
    LONG lPatternWidth;
    LONG lPatternLength;
    LONG cbPattern;
    BYTE *pbPattern;
    } 	WIA_DITHER_PATTERN_DATA;

typedef struct _WIA_DITHER_PATTERN_DATA *PWIA_DITHER_PATTERN_DATA;

typedef struct _WIA_PROPID_TO_NAME
    {
    PROPID propid;
    LPOLESTR pszName;
    } 	WIA_PROPID_TO_NAME;

typedef struct _WIA_PROPID_TO_NAME *PWIA_PROPID_TO_NAME;

typedef struct _WIA_FORMAT_INFO
    {
    GUID guidFormatID;
    LONG lTymed;
    } 	WIA_FORMAT_INFO;

typedef struct _WIA_FORMAT_INFO *PWIA_FORMAT_INFO;

#include "wiadef.h"


extern RPC_IF_HANDLE __MIDL_itf_wia_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wia_0000_v0_0_s_ifspec;

#ifndef __IWiaDevMgr_INTERFACE_DEFINED__
#define __IWiaDevMgr_INTERFACE_DEFINED__

/* interface IWiaDevMgr */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaDevMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5eb2502a-8cf1-11d1-bf92-0060081ed811")
    IWiaDevMgr : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumDeviceInfo( 
            /* [in] */ LONG lFlag,
            /* [retval][out] */ IEnumWIA_DEV_INFO **ppIEnum) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateDevice( 
            /* [in] */ BSTR bstrDeviceID,
            /* [out] */ IWiaItem **ppWiaItemRoot) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SelectDeviceDlg( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [out][in] */ BSTR *pbstrDeviceID,
            /* [retval][out] */ IWiaItem **ppItemRoot) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SelectDeviceDlgID( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [retval][out] */ BSTR *pbstrDeviceID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetImageDlg( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lIntent,
            /* [in] */ IWiaItem *pItemRoot,
            /* [in] */ BSTR bstrFilename,
            /* [out][in] */ GUID *pguidFormat) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE RegisterEventCallbackProgram( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [in] */ BSTR bstrCommandline,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIcon) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE RegisterEventCallbackInterface( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
            /* [out] */ IUnknown **pEventObject) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE RegisterEventCallbackCLSID( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [unique][in] */ const GUID *pClsID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIcon) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddDeviceDlg( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaDevMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaDevMgr * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaDevMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaDevMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceInfo )( 
            IWiaDevMgr * This,
            /* [in] */ LONG lFlag,
            /* [retval][out] */ IEnumWIA_DEV_INFO **ppIEnum);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *CreateDevice )( 
            IWiaDevMgr * This,
            /* [in] */ BSTR bstrDeviceID,
            /* [out] */ IWiaItem **ppWiaItemRoot);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SelectDeviceDlg )( 
            IWiaDevMgr * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [out][in] */ BSTR *pbstrDeviceID,
            /* [retval][out] */ IWiaItem **ppItemRoot);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SelectDeviceDlgID )( 
            IWiaDevMgr * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [retval][out] */ BSTR *pbstrDeviceID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *GetImageDlg )( 
            IWiaDevMgr * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lIntent,
            /* [in] */ IWiaItem *pItemRoot,
            /* [in] */ BSTR bstrFilename,
            /* [out][in] */ GUID *pguidFormat);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *RegisterEventCallbackProgram )( 
            IWiaDevMgr * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [in] */ BSTR bstrCommandline,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIcon);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *RegisterEventCallbackInterface )( 
            IWiaDevMgr * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
            /* [out] */ IUnknown **pEventObject);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *RegisterEventCallbackCLSID )( 
            IWiaDevMgr * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [unique][in] */ const GUID *pClsID,
            /* [in] */ BSTR bstrName,
            /* [in] */ BSTR bstrDescription,
            /* [in] */ BSTR bstrIcon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddDeviceDlg )( 
            IWiaDevMgr * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lFlags);
        
        END_INTERFACE
    } IWiaDevMgrVtbl;

    interface IWiaDevMgr
    {
        CONST_VTBL struct IWiaDevMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaDevMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaDevMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaDevMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaDevMgr_EnumDeviceInfo(This,lFlag,ppIEnum)	\
    ( (This)->lpVtbl -> EnumDeviceInfo(This,lFlag,ppIEnum) ) 

#define IWiaDevMgr_CreateDevice(This,bstrDeviceID,ppWiaItemRoot)	\
    ( (This)->lpVtbl -> CreateDevice(This,bstrDeviceID,ppWiaItemRoot) ) 

#define IWiaDevMgr_SelectDeviceDlg(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID,ppItemRoot)	\
    ( (This)->lpVtbl -> SelectDeviceDlg(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID,ppItemRoot) ) 

#define IWiaDevMgr_SelectDeviceDlgID(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID)	\
    ( (This)->lpVtbl -> SelectDeviceDlgID(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID) ) 

#define IWiaDevMgr_GetImageDlg(This,hwndParent,lDeviceType,lFlags,lIntent,pItemRoot,bstrFilename,pguidFormat)	\
    ( (This)->lpVtbl -> GetImageDlg(This,hwndParent,lDeviceType,lFlags,lIntent,pItemRoot,bstrFilename,pguidFormat) ) 

#define IWiaDevMgr_RegisterEventCallbackProgram(This,lFlags,bstrDeviceID,pEventGUID,bstrCommandline,bstrName,bstrDescription,bstrIcon)	\
    ( (This)->lpVtbl -> RegisterEventCallbackProgram(This,lFlags,bstrDeviceID,pEventGUID,bstrCommandline,bstrName,bstrDescription,bstrIcon) ) 

#define IWiaDevMgr_RegisterEventCallbackInterface(This,lFlags,bstrDeviceID,pEventGUID,pIWiaEventCallback,pEventObject)	\
    ( (This)->lpVtbl -> RegisterEventCallbackInterface(This,lFlags,bstrDeviceID,pEventGUID,pIWiaEventCallback,pEventObject) ) 

#define IWiaDevMgr_RegisterEventCallbackCLSID(This,lFlags,bstrDeviceID,pEventGUID,pClsID,bstrName,bstrDescription,bstrIcon)	\
    ( (This)->lpVtbl -> RegisterEventCallbackCLSID(This,lFlags,bstrDeviceID,pEventGUID,pClsID,bstrName,bstrDescription,bstrIcon) ) 

#define IWiaDevMgr_AddDeviceDlg(This,hwndParent,lFlags)	\
    ( (This)->lpVtbl -> AddDeviceDlg(This,hwndParent,lFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_EnumDeviceInfo_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlag,
    /* [retval][out] */ IEnumWIA_DEV_INFO **ppIEnum);


void __RPC_STUB IWiaDevMgr_EnumDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalCreateDevice_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ BSTR bstrDeviceID,
    /* [out] */ IWiaItem **ppWiaItemRoot);


void __RPC_STUB IWiaDevMgr_LocalCreateDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalSelectDeviceDlg_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [out][in] */ BSTR *pbstrDeviceID,
    /* [retval][out] */ IWiaItem **ppItemRoot);


void __RPC_STUB IWiaDevMgr_LocalSelectDeviceDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalSelectDeviceDlgID_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ BSTR *pbstrDeviceID);


void __RPC_STUB IWiaDevMgr_LocalSelectDeviceDlgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalGetImageDlg_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [in] */ IWiaItem *pItemRoot,
    /* [in] */ BSTR bstrFilename,
    /* [out][in] */ GUID *pguidFormat);


void __RPC_STUB IWiaDevMgr_LocalGetImageDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalRegisterEventCallbackProgram_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [in] */ BSTR bstrCommandline,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIcon);


void __RPC_STUB IWiaDevMgr_LocalRegisterEventCallbackProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalRegisterEventCallbackInterface_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
    /* [out] */ IUnknown **pEventObject);


void __RPC_STUB IWiaDevMgr_LocalRegisterEventCallbackInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_LocalRegisterEventCallbackCLSID_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ const GUID *pClsID,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIcon);


void __RPC_STUB IWiaDevMgr_LocalRegisterEventCallbackCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_AddDeviceDlg_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags);


void __RPC_STUB IWiaDevMgr_AddDeviceDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaDevMgr_INTERFACE_DEFINED__ */


#ifndef __IEnumWIA_DEV_INFO_INTERFACE_DEFINED__
#define __IEnumWIA_DEV_INFO_INTERFACE_DEFINED__

/* interface IEnumWIA_DEV_INFO */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumWIA_DEV_INFO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5e38b83c-8cf1-11d1-bf92-0060081ed811")
    IEnumWIA_DEV_INFO : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IWiaPropertyStorage **rgelt,
            /* [unique][out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWIA_DEV_INFO **ppIEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *celt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumWIA_DEV_INFOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWIA_DEV_INFO * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWIA_DEV_INFO * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWIA_DEV_INFO * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWIA_DEV_INFO * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IWiaPropertyStorage **rgelt,
            /* [unique][out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWIA_DEV_INFO * This,
            /* [in] */ ULONG celt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWIA_DEV_INFO * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWIA_DEV_INFO * This,
            /* [out] */ IEnumWIA_DEV_INFO **ppIEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumWIA_DEV_INFO * This,
            /* [out] */ ULONG *celt);
        
        END_INTERFACE
    } IEnumWIA_DEV_INFOVtbl;

    interface IEnumWIA_DEV_INFO
    {
        CONST_VTBL struct IEnumWIA_DEV_INFOVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWIA_DEV_INFO_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumWIA_DEV_INFO_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumWIA_DEV_INFO_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumWIA_DEV_INFO_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumWIA_DEV_INFO_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumWIA_DEV_INFO_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumWIA_DEV_INFO_Clone(This,ppIEnum)	\
    ( (This)->lpVtbl -> Clone(This,ppIEnum) ) 

#define IEnumWIA_DEV_INFO_GetCount(This,celt)	\
    ( (This)->lpVtbl -> GetCount(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_RemoteNext_Proxy( 
    IEnumWIA_DEV_INFO * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IWiaPropertyStorage **rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);


void __RPC_STUB IEnumWIA_DEV_INFO_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_Skip_Proxy( 
    IEnumWIA_DEV_INFO * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumWIA_DEV_INFO_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_Reset_Proxy( 
    IEnumWIA_DEV_INFO * This);


void __RPC_STUB IEnumWIA_DEV_INFO_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_Clone_Proxy( 
    IEnumWIA_DEV_INFO * This,
    /* [out] */ IEnumWIA_DEV_INFO **ppIEnum);


void __RPC_STUB IEnumWIA_DEV_INFO_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_GetCount_Proxy( 
    IEnumWIA_DEV_INFO * This,
    /* [out] */ ULONG *celt);


void __RPC_STUB IEnumWIA_DEV_INFO_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumWIA_DEV_INFO_INTERFACE_DEFINED__ */


#ifndef __IWiaEventCallback_INTERFACE_DEFINED__
#define __IWiaEventCallback_INTERFACE_DEFINED__

/* interface IWiaEventCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaEventCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ae6287b0-0084-11d2-973b-00a0c9068f2e")
    IWiaEventCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ImageEventCallback( 
            /* [in] */ const GUID *pEventGUID,
            /* [in] */ BSTR bstrEventDescription,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ BSTR bstrDeviceDescription,
            /* [in] */ DWORD dwDeviceType,
            /* [in] */ BSTR bstrFullItemName,
            /* [out][in] */ ULONG *pulEventType,
            /* [in] */ ULONG ulReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaEventCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaEventCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaEventCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaEventCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *ImageEventCallback )( 
            IWiaEventCallback * This,
            /* [in] */ const GUID *pEventGUID,
            /* [in] */ BSTR bstrEventDescription,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ BSTR bstrDeviceDescription,
            /* [in] */ DWORD dwDeviceType,
            /* [in] */ BSTR bstrFullItemName,
            /* [out][in] */ ULONG *pulEventType,
            /* [in] */ ULONG ulReserved);
        
        END_INTERFACE
    } IWiaEventCallbackVtbl;

    interface IWiaEventCallback
    {
        CONST_VTBL struct IWiaEventCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaEventCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaEventCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaEventCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaEventCallback_ImageEventCallback(This,pEventGUID,bstrEventDescription,bstrDeviceID,bstrDeviceDescription,dwDeviceType,bstrFullItemName,pulEventType,ulReserved)	\
    ( (This)->lpVtbl -> ImageEventCallback(This,pEventGUID,bstrEventDescription,bstrDeviceID,bstrDeviceDescription,dwDeviceType,bstrFullItemName,pulEventType,ulReserved) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWiaEventCallback_ImageEventCallback_Proxy( 
    IWiaEventCallback * This,
    /* [in] */ const GUID *pEventGUID,
    /* [in] */ BSTR bstrEventDescription,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ BSTR bstrDeviceDescription,
    /* [in] */ DWORD dwDeviceType,
    /* [in] */ BSTR bstrFullItemName,
    /* [out][in] */ ULONG *pulEventType,
    /* [in] */ ULONG ulReserved);


void __RPC_STUB IWiaEventCallback_ImageEventCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaEventCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_wia_0128 */
/* [local] */ 

typedef struct _WIA_DATA_CALLBACK_HEADER
    {
    LONG lSize;
    GUID guidFormatID;
    LONG lBufferSize;
    LONG lPageCount;
    } 	WIA_DATA_CALLBACK_HEADER;

typedef struct _WIA_DATA_CALLBACK_HEADER *PWIA_DATA_CALLBACK_HEADER;



extern RPC_IF_HANDLE __MIDL_itf_wia_0128_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wia_0128_v0_0_s_ifspec;

#ifndef __IWiaDataCallback_INTERFACE_DEFINED__
#define __IWiaDataCallback_INTERFACE_DEFINED__

/* interface IWiaDataCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaDataCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a558a866-a5b0-11d2-a08f-00c04f72dc3c")
    IWiaDataCallback : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE BandedDataCallback( 
            /* [in] */ LONG lMessage,
            /* [in] */ LONG lStatus,
            /* [in] */ LONG lPercentComplete,
            /* [in] */ LONG lOffset,
            /* [in] */ LONG lLength,
            /* [in] */ LONG lReserved,
            /* [in] */ LONG lResLength,
            /* [size_is][in] */ BYTE *pbBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaDataCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaDataCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaDataCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaDataCallback * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *BandedDataCallback )( 
            IWiaDataCallback * This,
            /* [in] */ LONG lMessage,
            /* [in] */ LONG lStatus,
            /* [in] */ LONG lPercentComplete,
            /* [in] */ LONG lOffset,
            /* [in] */ LONG lLength,
            /* [in] */ LONG lReserved,
            /* [in] */ LONG lResLength,
            /* [size_is][in] */ BYTE *pbBuffer);
        
        END_INTERFACE
    } IWiaDataCallbackVtbl;

    interface IWiaDataCallback
    {
        CONST_VTBL struct IWiaDataCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaDataCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaDataCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaDataCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaDataCallback_BandedDataCallback(This,lMessage,lStatus,lPercentComplete,lOffset,lLength,lReserved,lResLength,pbBuffer)	\
    ( (This)->lpVtbl -> BandedDataCallback(This,lMessage,lStatus,lPercentComplete,lOffset,lLength,lReserved,lResLength,pbBuffer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDataCallback_RemoteBandedDataCallback_Proxy( 
    IWiaDataCallback * This,
    /* [in] */ LONG lMessage,
    /* [in] */ LONG lStatus,
    /* [in] */ LONG lPercentComplete,
    /* [in] */ LONG lOffset,
    /* [in] */ LONG lLength,
    /* [in] */ LONG lReserved,
    /* [in] */ LONG lResLength,
    /* [unique][size_is][in] */ BYTE *pbBuffer);


void __RPC_STUB IWiaDataCallback_RemoteBandedDataCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaDataCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_wia_0129 */
/* [local] */ 

typedef struct _WIA_DATA_TRANSFER_INFO
    {
    ULONG ulSize;
    ULONG ulSection;
    ULONG ulBufferSize;
    BOOL bDoubleBuffer;
    ULONG ulReserved1;
    ULONG ulReserved2;
    ULONG ulReserved3;
    } 	WIA_DATA_TRANSFER_INFO;

typedef struct _WIA_DATA_TRANSFER_INFO *PWIA_DATA_TRANSFER_INFO;

typedef struct _WIA_EXTENDED_TRANSFER_INFO
    {
    ULONG ulSize;
    ULONG ulMinBufferSize;
    ULONG ulOptimalBufferSize;
    ULONG ulMaxBufferSize;
    ULONG ulNumBuffers;
    } 	WIA_EXTENDED_TRANSFER_INFO;

typedef struct _WIA_EXTENDED_TRANSFER_INFO *PWIA_EXTENDED_TRANSFER_INFO;



extern RPC_IF_HANDLE __MIDL_itf_wia_0129_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wia_0129_v0_0_s_ifspec;

#ifndef __IWiaDataTransfer_INTERFACE_DEFINED__
#define __IWiaDataTransfer_INTERFACE_DEFINED__

/* interface IWiaDataTransfer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaDataTransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a6cef998-a5b0-11d2-a08f-00c04f72dc3c")
    IWiaDataTransfer : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE idtGetData( 
            /* [out][in] */ LPSTGMEDIUM pMedium,
            /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE idtGetBandedData( 
            /* [unique][in] */ PWIA_DATA_TRANSFER_INFO pWiaDataTransInfo,
            /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE idtQueryGetData( 
            /* [unique][in] */ WIA_FORMAT_INFO *pfe) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE idtEnumWIA_FORMAT_INFO( 
            /* [out] */ IEnumWIA_FORMAT_INFO **ppEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE idtGetExtendedTransferInfo( 
            /* [out] */ PWIA_EXTENDED_TRANSFER_INFO pExtendedTransferInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaDataTransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaDataTransfer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaDataTransfer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaDataTransfer * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *idtGetData )( 
            IWiaDataTransfer * This,
            /* [out][in] */ LPSTGMEDIUM pMedium,
            /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *idtGetBandedData )( 
            IWiaDataTransfer * This,
            /* [unique][in] */ PWIA_DATA_TRANSFER_INFO pWiaDataTransInfo,
            /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *idtQueryGetData )( 
            IWiaDataTransfer * This,
            /* [unique][in] */ WIA_FORMAT_INFO *pfe);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *idtEnumWIA_FORMAT_INFO )( 
            IWiaDataTransfer * This,
            /* [out] */ IEnumWIA_FORMAT_INFO **ppEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *idtGetExtendedTransferInfo )( 
            IWiaDataTransfer * This,
            /* [out] */ PWIA_EXTENDED_TRANSFER_INFO pExtendedTransferInfo);
        
        END_INTERFACE
    } IWiaDataTransferVtbl;

    interface IWiaDataTransfer
    {
        CONST_VTBL struct IWiaDataTransferVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaDataTransfer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaDataTransfer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaDataTransfer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaDataTransfer_idtGetData(This,pMedium,pIWiaDataCallback)	\
    ( (This)->lpVtbl -> idtGetData(This,pMedium,pIWiaDataCallback) ) 

#define IWiaDataTransfer_idtGetBandedData(This,pWiaDataTransInfo,pIWiaDataCallback)	\
    ( (This)->lpVtbl -> idtGetBandedData(This,pWiaDataTransInfo,pIWiaDataCallback) ) 

#define IWiaDataTransfer_idtQueryGetData(This,pfe)	\
    ( (This)->lpVtbl -> idtQueryGetData(This,pfe) ) 

#define IWiaDataTransfer_idtEnumWIA_FORMAT_INFO(This,ppEnum)	\
    ( (This)->lpVtbl -> idtEnumWIA_FORMAT_INFO(This,ppEnum) ) 

#define IWiaDataTransfer_idtGetExtendedTransferInfo(This,pExtendedTransferInfo)	\
    ( (This)->lpVtbl -> idtGetExtendedTransferInfo(This,pExtendedTransferInfo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetDataEx_Proxy( 
    IWiaDataTransfer * This,
    /* [out][in] */ LPSTGMEDIUM pMedium,
    /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);


void __RPC_STUB IWiaDataTransfer_idtGetDataEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetBandedDataEx_Proxy( 
    IWiaDataTransfer * This,
    /* [unique][in] */ PWIA_DATA_TRANSFER_INFO pWiaDataTransInfo,
    /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);


void __RPC_STUB IWiaDataTransfer_idtGetBandedDataEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtQueryGetData_Proxy( 
    IWiaDataTransfer * This,
    /* [unique][in] */ WIA_FORMAT_INFO *pfe);


void __RPC_STUB IWiaDataTransfer_idtQueryGetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtEnumWIA_FORMAT_INFO_Proxy( 
    IWiaDataTransfer * This,
    /* [out] */ IEnumWIA_FORMAT_INFO **ppEnum);


void __RPC_STUB IWiaDataTransfer_idtEnumWIA_FORMAT_INFO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetExtendedTransferInfo_Proxy( 
    IWiaDataTransfer * This,
    /* [out] */ PWIA_EXTENDED_TRANSFER_INFO pExtendedTransferInfo);


void __RPC_STUB IWiaDataTransfer_idtGetExtendedTransferInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaDataTransfer_INTERFACE_DEFINED__ */


#ifndef __IWiaItem_INTERFACE_DEFINED__
#define __IWiaItem_INTERFACE_DEFINED__

/* interface IWiaItem */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4db1ad10-3391-11d2-9a33-00c04fa36145")
    IWiaItem : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemType( 
            /* [out] */ LONG *pItemType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AnalyzeItem( 
            /* [in] */ LONG lFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumChildItems( 
            /* [out] */ IEnumWiaItem **ppIEnumWiaItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ LONG lFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateChildItem( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrItemName,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IWiaItem **ppIWiaItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumRegisterEventInfo( 
            /* [in] */ LONG lFlags,
            /* [in] */ const GUID *pEventGUID,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindItemByName( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IWiaItem **ppIWiaItem) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE DeviceDlg( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lIntent,
            /* [out] */ LONG *plItemCount,
            /* [out] */ IWiaItem ***ppIWiaItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceCommand( 
            /* [in] */ LONG lFlags,
            /* [in] */ const GUID *pCmdGUID,
            /* [out][in] */ IWiaItem **pIWiaItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRootItem( 
            /* [out] */ IWiaItem **ppIWiaItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumDeviceCapabilities( 
            /* [in] */ LONG lFlags,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnumWIA_DEV_CAPS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DumpItemData( 
            /* [out] */ BSTR *bstrData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DumpDrvItemData( 
            /* [out] */ BSTR *bstrData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DumpTreeItemData( 
            /* [out] */ BSTR *bstrData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Diagnostic( 
            /* [in] */ ULONG ulSize,
            /* [size_is][in] */ BYTE *pBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemType )( 
            IWiaItem * This,
            /* [out] */ LONG *pItemType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AnalyzeItem )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumChildItems )( 
            IWiaItem * This,
            /* [out] */ IEnumWiaItem **ppIEnumWiaItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteItem )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateChildItem )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrItemName,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IWiaItem **ppIWiaItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumRegisterEventInfo )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags,
            /* [in] */ const GUID *pEventGUID,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindItemByName )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IWiaItem **ppIWiaItem);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *DeviceDlg )( 
            IWiaItem * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lIntent,
            /* [out] */ LONG *plItemCount,
            /* [out] */ IWiaItem ***ppIWiaItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceCommand )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags,
            /* [in] */ const GUID *pCmdGUID,
            /* [out][in] */ IWiaItem **pIWiaItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRootItem )( 
            IWiaItem * This,
            /* [out] */ IWiaItem **ppIWiaItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceCapabilities )( 
            IWiaItem * This,
            /* [in] */ LONG lFlags,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnumWIA_DEV_CAPS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DumpItemData )( 
            IWiaItem * This,
            /* [out] */ BSTR *bstrData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DumpDrvItemData )( 
            IWiaItem * This,
            /* [out] */ BSTR *bstrData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DumpTreeItemData )( 
            IWiaItem * This,
            /* [out] */ BSTR *bstrData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Diagnostic )( 
            IWiaItem * This,
            /* [in] */ ULONG ulSize,
            /* [size_is][in] */ BYTE *pBuffer);
        
        END_INTERFACE
    } IWiaItemVtbl;

    interface IWiaItem
    {
        CONST_VTBL struct IWiaItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaItem_GetItemType(This,pItemType)	\
    ( (This)->lpVtbl -> GetItemType(This,pItemType) ) 

#define IWiaItem_AnalyzeItem(This,lFlags)	\
    ( (This)->lpVtbl -> AnalyzeItem(This,lFlags) ) 

#define IWiaItem_EnumChildItems(This,ppIEnumWiaItem)	\
    ( (This)->lpVtbl -> EnumChildItems(This,ppIEnumWiaItem) ) 

#define IWiaItem_DeleteItem(This,lFlags)	\
    ( (This)->lpVtbl -> DeleteItem(This,lFlags) ) 

#define IWiaItem_CreateChildItem(This,lFlags,bstrItemName,bstrFullItemName,ppIWiaItem)	\
    ( (This)->lpVtbl -> CreateChildItem(This,lFlags,bstrItemName,bstrFullItemName,ppIWiaItem) ) 

#define IWiaItem_EnumRegisterEventInfo(This,lFlags,pEventGUID,ppIEnum)	\
    ( (This)->lpVtbl -> EnumRegisterEventInfo(This,lFlags,pEventGUID,ppIEnum) ) 

#define IWiaItem_FindItemByName(This,lFlags,bstrFullItemName,ppIWiaItem)	\
    ( (This)->lpVtbl -> FindItemByName(This,lFlags,bstrFullItemName,ppIWiaItem) ) 

#define IWiaItem_DeviceDlg(This,hwndParent,lFlags,lIntent,plItemCount,ppIWiaItem)	\
    ( (This)->lpVtbl -> DeviceDlg(This,hwndParent,lFlags,lIntent,plItemCount,ppIWiaItem) ) 

#define IWiaItem_DeviceCommand(This,lFlags,pCmdGUID,pIWiaItem)	\
    ( (This)->lpVtbl -> DeviceCommand(This,lFlags,pCmdGUID,pIWiaItem) ) 

#define IWiaItem_GetRootItem(This,ppIWiaItem)	\
    ( (This)->lpVtbl -> GetRootItem(This,ppIWiaItem) ) 

#define IWiaItem_EnumDeviceCapabilities(This,lFlags,ppIEnumWIA_DEV_CAPS)	\
    ( (This)->lpVtbl -> EnumDeviceCapabilities(This,lFlags,ppIEnumWIA_DEV_CAPS) ) 

#define IWiaItem_DumpItemData(This,bstrData)	\
    ( (This)->lpVtbl -> DumpItemData(This,bstrData) ) 

#define IWiaItem_DumpDrvItemData(This,bstrData)	\
    ( (This)->lpVtbl -> DumpDrvItemData(This,bstrData) ) 

#define IWiaItem_DumpTreeItemData(This,bstrData)	\
    ( (This)->lpVtbl -> DumpTreeItemData(This,bstrData) ) 

#define IWiaItem_Diagnostic(This,ulSize,pBuffer)	\
    ( (This)->lpVtbl -> Diagnostic(This,ulSize,pBuffer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_GetItemType_Proxy( 
    IWiaItem * This,
    /* [out] */ LONG *pItemType);


void __RPC_STUB IWiaItem_GetItemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_AnalyzeItem_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags);


void __RPC_STUB IWiaItem_AnalyzeItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_EnumChildItems_Proxy( 
    IWiaItem * This,
    /* [out] */ IEnumWiaItem **ppIEnumWiaItem);


void __RPC_STUB IWiaItem_EnumChildItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_DeleteItem_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags);


void __RPC_STUB IWiaItem_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_CreateChildItem_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrItemName,
    /* [in] */ BSTR bstrFullItemName,
    /* [out] */ IWiaItem **ppIWiaItem);


void __RPC_STUB IWiaItem_CreateChildItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_EnumRegisterEventInfo_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags,
    /* [in] */ const GUID *pEventGUID,
    /* [out] */ IEnumWIA_DEV_CAPS **ppIEnum);


void __RPC_STUB IWiaItem_EnumRegisterEventInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_FindItemByName_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrFullItemName,
    /* [out] */ IWiaItem **ppIWiaItem);


void __RPC_STUB IWiaItem_FindItemByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem_LocalDeviceDlg_Proxy( 
    IWiaItem * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [out] */ LONG *plItemCount,
    /* [out] */ IWiaItem ***pIWiaItem);


void __RPC_STUB IWiaItem_LocalDeviceDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_DeviceCommand_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags,
    /* [in] */ const GUID *pCmdGUID,
    /* [out][in] */ IWiaItem **pIWiaItem);


void __RPC_STUB IWiaItem_DeviceCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_GetRootItem_Proxy( 
    IWiaItem * This,
    /* [out] */ IWiaItem **ppIWiaItem);


void __RPC_STUB IWiaItem_GetRootItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_EnumDeviceCapabilities_Proxy( 
    IWiaItem * This,
    /* [in] */ LONG lFlags,
    /* [out] */ IEnumWIA_DEV_CAPS **ppIEnumWIA_DEV_CAPS);


void __RPC_STUB IWiaItem_EnumDeviceCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_DumpItemData_Proxy( 
    IWiaItem * This,
    /* [out] */ BSTR *bstrData);


void __RPC_STUB IWiaItem_DumpItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_DumpDrvItemData_Proxy( 
    IWiaItem * This,
    /* [out] */ BSTR *bstrData);


void __RPC_STUB IWiaItem_DumpDrvItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_DumpTreeItemData_Proxy( 
    IWiaItem * This,
    /* [out] */ BSTR *bstrData);


void __RPC_STUB IWiaItem_DumpTreeItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem_Diagnostic_Proxy( 
    IWiaItem * This,
    /* [in] */ ULONG ulSize,
    /* [size_is][in] */ BYTE *pBuffer);


void __RPC_STUB IWiaItem_Diagnostic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaItem_INTERFACE_DEFINED__ */


#ifndef __IWiaPropertyStorage_INTERFACE_DEFINED__
#define __IWiaPropertyStorage_INTERFACE_DEFINED__

/* interface IWiaPropertyStorage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaPropertyStorage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98B5E8A0-29CC-491a-AAC0-E6DB4FDCCEB6")
    IWiaPropertyStorage : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReadMultiple( 
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ const PROPSPEC rgpspec[  ],
            /* [size_is][out] */ PROPVARIANT rgpropvar[  ]) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE WriteMultiple( 
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ const PROPSPEC rgpspec[  ],
            /* [size_is][in] */ const PROPVARIANT rgpropvar[  ],
            /* [in] */ PROPID propidNameFirst) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteMultiple( 
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ const PROPSPEC rgpspec[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadPropertyNames( 
            /* [in] */ ULONG cpropid,
            /* [size_is][in] */ const PROPID rgpropid[  ],
            /* [size_is][out] */ LPOLESTR rglpwstrName[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WritePropertyNames( 
            /* [in] */ ULONG cpropid,
            /* [size_is][in] */ const PROPID rgpropid[  ],
            /* [size_is][in] */ const LPOLESTR rglpwstrName[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeletePropertyNames( 
            /* [in] */ ULONG cpropid,
            /* [size_is][in] */ const PROPID rgpropid[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( 
            /* [in] */ DWORD grfCommitFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Revert( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Enum( 
            /* [out] */ IEnumSTATPROPSTG **ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimes( 
            /* [in] */ const FILETIME *pctime,
            /* [in] */ const FILETIME *patime,
            /* [in] */ const FILETIME *pmtime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetClass( 
            /* [in] */ REFCLSID clsid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stat( 
            /* [out] */ STATPROPSETSTG *pstatpsstg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPropertyAttributes( 
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ PROPSPEC rgpspec[  ],
            /* [size_is][out] */ ULONG rgflags[  ],
            /* [size_is][out] */ PROPVARIANT rgpropvar[  ]) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *pulNumProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPropertyStream( 
            /* [out] */ GUID *pCompatibilityId,
            /* [out] */ IStream **ppIStream) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SetPropertyStream( 
            /* [in] */ GUID *pCompatibilityId,
            /* [unique][in] */ IStream *pIStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaPropertyStorageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaPropertyStorage * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaPropertyStorage * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaPropertyStorage * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReadMultiple )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ const PROPSPEC rgpspec[  ],
            /* [size_is][out] */ PROPVARIANT rgpropvar[  ]);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *WriteMultiple )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ const PROPSPEC rgpspec[  ],
            /* [size_is][in] */ const PROPVARIANT rgpropvar[  ],
            /* [in] */ PROPID propidNameFirst);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteMultiple )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ const PROPSPEC rgpspec[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *ReadPropertyNames )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpropid,
            /* [size_is][in] */ const PROPID rgpropid[  ],
            /* [size_is][out] */ LPOLESTR rglpwstrName[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *WritePropertyNames )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpropid,
            /* [size_is][in] */ const PROPID rgpropid[  ],
            /* [size_is][in] */ const LPOLESTR rglpwstrName[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *DeletePropertyNames )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpropid,
            /* [size_is][in] */ const PROPID rgpropid[  ]);
        
        HRESULT ( STDMETHODCALLTYPE *Commit )( 
            IWiaPropertyStorage * This,
            /* [in] */ DWORD grfCommitFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Revert )( 
            IWiaPropertyStorage * This);
        
        HRESULT ( STDMETHODCALLTYPE *Enum )( 
            IWiaPropertyStorage * This,
            /* [out] */ IEnumSTATPROPSTG **ppenum);
        
        HRESULT ( STDMETHODCALLTYPE *SetTimes )( 
            IWiaPropertyStorage * This,
            /* [in] */ const FILETIME *pctime,
            /* [in] */ const FILETIME *patime,
            /* [in] */ const FILETIME *pmtime);
        
        HRESULT ( STDMETHODCALLTYPE *SetClass )( 
            IWiaPropertyStorage * This,
            /* [in] */ REFCLSID clsid);
        
        HRESULT ( STDMETHODCALLTYPE *Stat )( 
            IWiaPropertyStorage * This,
            /* [out] */ STATPROPSETSTG *pstatpsstg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyAttributes )( 
            IWiaPropertyStorage * This,
            /* [in] */ ULONG cpspec,
            /* [size_is][in] */ PROPSPEC rgpspec[  ],
            /* [size_is][out] */ ULONG rgflags[  ],
            /* [size_is][out] */ PROPVARIANT rgpropvar[  ]);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IWiaPropertyStorage * This,
            /* [out] */ ULONG *pulNumProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyStream )( 
            IWiaPropertyStorage * This,
            /* [out] */ GUID *pCompatibilityId,
            /* [out] */ IStream **ppIStream);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SetPropertyStream )( 
            IWiaPropertyStorage * This,
            /* [in] */ GUID *pCompatibilityId,
            /* [unique][in] */ IStream *pIStream);
        
        END_INTERFACE
    } IWiaPropertyStorageVtbl;

    interface IWiaPropertyStorage
    {
        CONST_VTBL struct IWiaPropertyStorageVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaPropertyStorage_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaPropertyStorage_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaPropertyStorage_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaPropertyStorage_ReadMultiple(This,cpspec,rgpspec,rgpropvar)	\
    ( (This)->lpVtbl -> ReadMultiple(This,cpspec,rgpspec,rgpropvar) ) 

#define IWiaPropertyStorage_WriteMultiple(This,cpspec,rgpspec,rgpropvar,propidNameFirst)	\
    ( (This)->lpVtbl -> WriteMultiple(This,cpspec,rgpspec,rgpropvar,propidNameFirst) ) 

#define IWiaPropertyStorage_DeleteMultiple(This,cpspec,rgpspec)	\
    ( (This)->lpVtbl -> DeleteMultiple(This,cpspec,rgpspec) ) 

#define IWiaPropertyStorage_ReadPropertyNames(This,cpropid,rgpropid,rglpwstrName)	\
    ( (This)->lpVtbl -> ReadPropertyNames(This,cpropid,rgpropid,rglpwstrName) ) 

#define IWiaPropertyStorage_WritePropertyNames(This,cpropid,rgpropid,rglpwstrName)	\
    ( (This)->lpVtbl -> WritePropertyNames(This,cpropid,rgpropid,rglpwstrName) ) 

#define IWiaPropertyStorage_DeletePropertyNames(This,cpropid,rgpropid)	\
    ( (This)->lpVtbl -> DeletePropertyNames(This,cpropid,rgpropid) ) 

#define IWiaPropertyStorage_Commit(This,grfCommitFlags)	\
    ( (This)->lpVtbl -> Commit(This,grfCommitFlags) ) 

#define IWiaPropertyStorage_Revert(This)	\
    ( (This)->lpVtbl -> Revert(This) ) 

#define IWiaPropertyStorage_Enum(This,ppenum)	\
    ( (This)->lpVtbl -> Enum(This,ppenum) ) 

#define IWiaPropertyStorage_SetTimes(This,pctime,patime,pmtime)	\
    ( (This)->lpVtbl -> SetTimes(This,pctime,patime,pmtime) ) 

#define IWiaPropertyStorage_SetClass(This,clsid)	\
    ( (This)->lpVtbl -> SetClass(This,clsid) ) 

#define IWiaPropertyStorage_Stat(This,pstatpsstg)	\
    ( (This)->lpVtbl -> Stat(This,pstatpsstg) ) 

#define IWiaPropertyStorage_GetPropertyAttributes(This,cpspec,rgpspec,rgflags,rgpropvar)	\
    ( (This)->lpVtbl -> GetPropertyAttributes(This,cpspec,rgpspec,rgflags,rgpropvar) ) 

#define IWiaPropertyStorage_GetCount(This,pulNumProps)	\
    ( (This)->lpVtbl -> GetCount(This,pulNumProps) ) 

#define IWiaPropertyStorage_GetPropertyStream(This,pCompatibilityId,ppIStream)	\
    ( (This)->lpVtbl -> GetPropertyStream(This,pCompatibilityId,ppIStream) ) 

#define IWiaPropertyStorage_SetPropertyStream(This,pCompatibilityId,pIStream)	\
    ( (This)->lpVtbl -> SetPropertyStream(This,pCompatibilityId,pIStream) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_ReadMultiple_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpspec,
    /* [size_is][in] */ const PROPSPEC rgpspec[  ],
    /* [size_is][out] */ PROPVARIANT rgpropvar[  ]);


void __RPC_STUB IWiaPropertyStorage_ReadMultiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_RemoteWriteMultiple_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpspec,
    /* [size_is][in] */ const PROPSPEC *rgpspec,
    /* [size_is][in] */ const PROPVARIANT *rgpropvar,
    /* [in] */ PROPID propidNameFirst);


void __RPC_STUB IWiaPropertyStorage_RemoteWriteMultiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_DeleteMultiple_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpspec,
    /* [size_is][in] */ const PROPSPEC rgpspec[  ]);


void __RPC_STUB IWiaPropertyStorage_DeleteMultiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_ReadPropertyNames_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpropid,
    /* [size_is][in] */ const PROPID rgpropid[  ],
    /* [size_is][out] */ LPOLESTR rglpwstrName[  ]);


void __RPC_STUB IWiaPropertyStorage_ReadPropertyNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_WritePropertyNames_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpropid,
    /* [size_is][in] */ const PROPID rgpropid[  ],
    /* [size_is][in] */ const LPOLESTR rglpwstrName[  ]);


void __RPC_STUB IWiaPropertyStorage_WritePropertyNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_DeletePropertyNames_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpropid,
    /* [size_is][in] */ const PROPID rgpropid[  ]);


void __RPC_STUB IWiaPropertyStorage_DeletePropertyNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_Commit_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ DWORD grfCommitFlags);


void __RPC_STUB IWiaPropertyStorage_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_Revert_Proxy( 
    IWiaPropertyStorage * This);


void __RPC_STUB IWiaPropertyStorage_Revert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_Enum_Proxy( 
    IWiaPropertyStorage * This,
    /* [out] */ IEnumSTATPROPSTG **ppenum);


void __RPC_STUB IWiaPropertyStorage_Enum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_SetTimes_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ const FILETIME *pctime,
    /* [in] */ const FILETIME *patime,
    /* [in] */ const FILETIME *pmtime);


void __RPC_STUB IWiaPropertyStorage_SetTimes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_SetClass_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ REFCLSID clsid);


void __RPC_STUB IWiaPropertyStorage_SetClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_Stat_Proxy( 
    IWiaPropertyStorage * This,
    /* [out] */ STATPROPSETSTG *pstatpsstg);


void __RPC_STUB IWiaPropertyStorage_Stat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_GetPropertyAttributes_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpspec,
    /* [size_is][in] */ PROPSPEC rgpspec[  ],
    /* [size_is][out] */ ULONG rgflags[  ],
    /* [size_is][out] */ PROPVARIANT rgpropvar[  ]);


void __RPC_STUB IWiaPropertyStorage_GetPropertyAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_GetCount_Proxy( 
    IWiaPropertyStorage * This,
    /* [out] */ ULONG *pulNumProps);


void __RPC_STUB IWiaPropertyStorage_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_GetPropertyStream_Proxy( 
    IWiaPropertyStorage * This,
    /* [out] */ GUID *pCompatibilityId,
    /* [out] */ IStream **ppIStream);


void __RPC_STUB IWiaPropertyStorage_GetPropertyStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_RemoteSetPropertyStream_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ GUID *pCompatibilityId,
    /* [unique][in] */ IStream *pIStream);


void __RPC_STUB IWiaPropertyStorage_RemoteSetPropertyStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaPropertyStorage_INTERFACE_DEFINED__ */


#ifndef __IEnumWiaItem_INTERFACE_DEFINED__
#define __IEnumWiaItem_INTERFACE_DEFINED__

/* interface IEnumWiaItem */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumWiaItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5e8383fc-3391-11d2-9a33-00c04fa36145")
    IEnumWiaItem : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IWiaItem **ppIWiaItem,
            /* [unique][out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWiaItem **ppIEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *celt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumWiaItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWiaItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWiaItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWiaItem * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWiaItem * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ IWiaItem **ppIWiaItem,
            /* [unique][out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWiaItem * This,
            /* [in] */ ULONG celt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWiaItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWiaItem * This,
            /* [out] */ IEnumWiaItem **ppIEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumWiaItem * This,
            /* [out] */ ULONG *celt);
        
        END_INTERFACE
    } IEnumWiaItemVtbl;

    interface IEnumWiaItem
    {
        CONST_VTBL struct IEnumWiaItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWiaItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumWiaItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumWiaItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumWiaItem_Next(This,celt,ppIWiaItem,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,ppIWiaItem,pceltFetched) ) 

#define IEnumWiaItem_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumWiaItem_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumWiaItem_Clone(This,ppIEnum)	\
    ( (This)->lpVtbl -> Clone(This,ppIEnum) ) 

#define IEnumWiaItem_GetCount(This,celt)	\
    ( (This)->lpVtbl -> GetCount(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_RemoteNext_Proxy( 
    IEnumWiaItem * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IWiaItem **ppIWiaItem,
    /* [unique][out][in] */ ULONG *pceltFetched);


void __RPC_STUB IEnumWiaItem_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_Skip_Proxy( 
    IEnumWiaItem * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumWiaItem_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_Reset_Proxy( 
    IEnumWiaItem * This);


void __RPC_STUB IEnumWiaItem_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_Clone_Proxy( 
    IEnumWiaItem * This,
    /* [out] */ IEnumWiaItem **ppIEnum);


void __RPC_STUB IEnumWiaItem_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_GetCount_Proxy( 
    IEnumWiaItem * This,
    /* [out] */ ULONG *celt);


void __RPC_STUB IEnumWiaItem_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumWiaItem_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_wia_0133 */
/* [local] */ 

typedef struct _WIA_DEV_CAP
    {
    GUID guid;
    ULONG ulFlags;
    BSTR bstrName;
    BSTR bstrDescription;
    BSTR bstrIcon;
    BSTR bstrCommandline;
    } 	WIA_DEV_CAP;

typedef struct _WIA_DEV_CAP *PWIA_DEV_CAP;

typedef struct _WIA_DEV_CAP WIA_EVENT_HANDLER;

typedef struct _WIA_DEV_CAP *PWIA_EVENT_HANDLER;



extern RPC_IF_HANDLE __MIDL_itf_wia_0133_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wia_0133_v0_0_s_ifspec;

#ifndef __IEnumWIA_DEV_CAPS_INTERFACE_DEFINED__
#define __IEnumWIA_DEV_CAPS_INTERFACE_DEFINED__

/* interface IEnumWIA_DEV_CAPS */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumWIA_DEV_CAPS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1fcc4287-aca6-11d2-a093-00c04f72dc3c")
    IEnumWIA_DEV_CAPS : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ WIA_DEV_CAP *rgelt,
            /* [unique][out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *pcelt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumWIA_DEV_CAPSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWIA_DEV_CAPS * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWIA_DEV_CAPS * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWIA_DEV_CAPS * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWIA_DEV_CAPS * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ WIA_DEV_CAP *rgelt,
            /* [unique][out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWIA_DEV_CAPS * This,
            /* [in] */ ULONG celt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWIA_DEV_CAPS * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWIA_DEV_CAPS * This,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumWIA_DEV_CAPS * This,
            /* [out] */ ULONG *pcelt);
        
        END_INTERFACE
    } IEnumWIA_DEV_CAPSVtbl;

    interface IEnumWIA_DEV_CAPS
    {
        CONST_VTBL struct IEnumWIA_DEV_CAPSVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWIA_DEV_CAPS_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumWIA_DEV_CAPS_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumWIA_DEV_CAPS_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumWIA_DEV_CAPS_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumWIA_DEV_CAPS_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumWIA_DEV_CAPS_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumWIA_DEV_CAPS_Clone(This,ppIEnum)	\
    ( (This)->lpVtbl -> Clone(This,ppIEnum) ) 

#define IEnumWIA_DEV_CAPS_GetCount(This,pcelt)	\
    ( (This)->lpVtbl -> GetCount(This,pcelt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_RemoteNext_Proxy( 
    IEnumWIA_DEV_CAPS * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ WIA_DEV_CAP *rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);


void __RPC_STUB IEnumWIA_DEV_CAPS_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_Skip_Proxy( 
    IEnumWIA_DEV_CAPS * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumWIA_DEV_CAPS_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_Reset_Proxy( 
    IEnumWIA_DEV_CAPS * This);


void __RPC_STUB IEnumWIA_DEV_CAPS_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_Clone_Proxy( 
    IEnumWIA_DEV_CAPS * This,
    /* [out] */ IEnumWIA_DEV_CAPS **ppIEnum);


void __RPC_STUB IEnumWIA_DEV_CAPS_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_GetCount_Proxy( 
    IEnumWIA_DEV_CAPS * This,
    /* [out] */ ULONG *pcelt);


void __RPC_STUB IEnumWIA_DEV_CAPS_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumWIA_DEV_CAPS_INTERFACE_DEFINED__ */


#ifndef __IEnumWIA_FORMAT_INFO_INTERFACE_DEFINED__
#define __IEnumWIA_FORMAT_INFO_INTERFACE_DEFINED__

/* interface IEnumWIA_FORMAT_INFO */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumWIA_FORMAT_INFO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("81BEFC5B-656D-44f1-B24C-D41D51B4DC81")
    IEnumWIA_FORMAT_INFO : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ WIA_FORMAT_INFO *rgelt,
            /* [unique][out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWIA_FORMAT_INFO **ppIEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *pcelt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumWIA_FORMAT_INFOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWIA_FORMAT_INFO * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWIA_FORMAT_INFO * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWIA_FORMAT_INFO * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWIA_FORMAT_INFO * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ WIA_FORMAT_INFO *rgelt,
            /* [unique][out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWIA_FORMAT_INFO * This,
            /* [in] */ ULONG celt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWIA_FORMAT_INFO * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWIA_FORMAT_INFO * This,
            /* [out] */ IEnumWIA_FORMAT_INFO **ppIEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumWIA_FORMAT_INFO * This,
            /* [out] */ ULONG *pcelt);
        
        END_INTERFACE
    } IEnumWIA_FORMAT_INFOVtbl;

    interface IEnumWIA_FORMAT_INFO
    {
        CONST_VTBL struct IEnumWIA_FORMAT_INFOVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWIA_FORMAT_INFO_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumWIA_FORMAT_INFO_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumWIA_FORMAT_INFO_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumWIA_FORMAT_INFO_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumWIA_FORMAT_INFO_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumWIA_FORMAT_INFO_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumWIA_FORMAT_INFO_Clone(This,ppIEnum)	\
    ( (This)->lpVtbl -> Clone(This,ppIEnum) ) 

#define IEnumWIA_FORMAT_INFO_GetCount(This,pcelt)	\
    ( (This)->lpVtbl -> GetCount(This,pcelt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_RemoteNext_Proxy( 
    IEnumWIA_FORMAT_INFO * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ WIA_FORMAT_INFO *rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);


void __RPC_STUB IEnumWIA_FORMAT_INFO_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_Skip_Proxy( 
    IEnumWIA_FORMAT_INFO * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumWIA_FORMAT_INFO_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_Reset_Proxy( 
    IEnumWIA_FORMAT_INFO * This);


void __RPC_STUB IEnumWIA_FORMAT_INFO_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_Clone_Proxy( 
    IEnumWIA_FORMAT_INFO * This,
    /* [out] */ IEnumWIA_FORMAT_INFO **ppIEnum);


void __RPC_STUB IEnumWIA_FORMAT_INFO_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_GetCount_Proxy( 
    IEnumWIA_FORMAT_INFO * This,
    /* [out] */ ULONG *pcelt);


void __RPC_STUB IEnumWIA_FORMAT_INFO_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumWIA_FORMAT_INFO_INTERFACE_DEFINED__ */


#ifndef __IWiaLog_INTERFACE_DEFINED__
#define __IWiaLog_INTERFACE_DEFINED__

/* interface IWiaLog */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaLog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A00C10B6-82A1-452f-8B6C-86062AAD6890")
    IWiaLog : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitializeLog( 
            /* [in] */ LONG hInstance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE hResult( 
            /* [in] */ HRESULT hResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Log( 
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lResID,
            /* [in] */ LONG lDetail,
            /* [in] */ BSTR bstrText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaLogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaLog * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaLog * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaLog * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitializeLog )( 
            IWiaLog * This,
            /* [in] */ LONG hInstance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hResult )( 
            IWiaLog * This,
            /* [in] */ HRESULT hResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Log )( 
            IWiaLog * This,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lResID,
            /* [in] */ LONG lDetail,
            /* [in] */ BSTR bstrText);
        
        END_INTERFACE
    } IWiaLogVtbl;

    interface IWiaLog
    {
        CONST_VTBL struct IWiaLogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaLog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaLog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaLog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaLog_InitializeLog(This,hInstance)	\
    ( (This)->lpVtbl -> InitializeLog(This,hInstance) ) 

#define IWiaLog_hResult(This,hResult)	\
    ( (This)->lpVtbl -> hResult(This,hResult) ) 

#define IWiaLog_Log(This,lFlags,lResID,lDetail,bstrText)	\
    ( (This)->lpVtbl -> Log(This,lFlags,lResID,lDetail,bstrText) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLog_InitializeLog_Proxy( 
    IWiaLog * This,
    /* [in] */ LONG hInstance);


void __RPC_STUB IWiaLog_InitializeLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLog_hResult_Proxy( 
    IWiaLog * This,
    /* [in] */ HRESULT hResult);


void __RPC_STUB IWiaLog_hResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLog_Log_Proxy( 
    IWiaLog * This,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lResID,
    /* [in] */ LONG lDetail,
    /* [in] */ BSTR bstrText);


void __RPC_STUB IWiaLog_Log_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaLog_INTERFACE_DEFINED__ */


#ifndef __IWiaLogEx_INTERFACE_DEFINED__
#define __IWiaLogEx_INTERFACE_DEFINED__

/* interface IWiaLogEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaLogEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AF1F22AC-7A40-4787-B421-AEb47A1FBD0B")
    IWiaLogEx : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitializeLogEx( 
            /* [in] */ BYTE *hInstance) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE hResult( 
            /* [in] */ HRESULT hResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Log( 
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lResID,
            /* [in] */ LONG lDetail,
            /* [in] */ BSTR bstrText) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE hResultEx( 
            /* [in] */ LONG lMethodId,
            /* [in] */ HRESULT hResult) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LogEx( 
            /* [in] */ LONG lMethodId,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lResID,
            /* [in] */ LONG lDetail,
            /* [in] */ BSTR bstrText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaLogExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaLogEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaLogEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaLogEx * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitializeLogEx )( 
            IWiaLogEx * This,
            /* [in] */ BYTE *hInstance);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hResult )( 
            IWiaLogEx * This,
            /* [in] */ HRESULT hResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Log )( 
            IWiaLogEx * This,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lResID,
            /* [in] */ LONG lDetail,
            /* [in] */ BSTR bstrText);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *hResultEx )( 
            IWiaLogEx * This,
            /* [in] */ LONG lMethodId,
            /* [in] */ HRESULT hResult);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LogEx )( 
            IWiaLogEx * This,
            /* [in] */ LONG lMethodId,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lResID,
            /* [in] */ LONG lDetail,
            /* [in] */ BSTR bstrText);
        
        END_INTERFACE
    } IWiaLogExVtbl;

    interface IWiaLogEx
    {
        CONST_VTBL struct IWiaLogExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaLogEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaLogEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaLogEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaLogEx_InitializeLogEx(This,hInstance)	\
    ( (This)->lpVtbl -> InitializeLogEx(This,hInstance) ) 

#define IWiaLogEx_hResult(This,hResult)	\
    ( (This)->lpVtbl -> hResult(This,hResult) ) 

#define IWiaLogEx_Log(This,lFlags,lResID,lDetail,bstrText)	\
    ( (This)->lpVtbl -> Log(This,lFlags,lResID,lDetail,bstrText) ) 

#define IWiaLogEx_hResultEx(This,lMethodId,hResult)	\
    ( (This)->lpVtbl -> hResultEx(This,lMethodId,hResult) ) 

#define IWiaLogEx_LogEx(This,lMethodId,lFlags,lResID,lDetail,bstrText)	\
    ( (This)->lpVtbl -> LogEx(This,lMethodId,lFlags,lResID,lDetail,bstrText) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLogEx_InitializeLogEx_Proxy( 
    IWiaLogEx * This,
    /* [in] */ BYTE *hInstance);


void __RPC_STUB IWiaLogEx_InitializeLogEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLogEx_hResult_Proxy( 
    IWiaLogEx * This,
    /* [in] */ HRESULT hResult);


void __RPC_STUB IWiaLogEx_hResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLogEx_Log_Proxy( 
    IWiaLogEx * This,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lResID,
    /* [in] */ LONG lDetail,
    /* [in] */ BSTR bstrText);


void __RPC_STUB IWiaLogEx_Log_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLogEx_hResultEx_Proxy( 
    IWiaLogEx * This,
    /* [in] */ LONG lMethodId,
    /* [in] */ HRESULT hResult);


void __RPC_STUB IWiaLogEx_hResultEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaLogEx_LogEx_Proxy( 
    IWiaLogEx * This,
    /* [in] */ LONG lMethodId,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lResID,
    /* [in] */ LONG lDetail,
    /* [in] */ BSTR bstrText);


void __RPC_STUB IWiaLogEx_LogEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaLogEx_INTERFACE_DEFINED__ */


#ifndef __IWiaNotifyDevMgr_INTERFACE_DEFINED__
#define __IWiaNotifyDevMgr_INTERFACE_DEFINED__

/* interface IWiaNotifyDevMgr */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaNotifyDevMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70681EA0-E7BF-4291-9FB1-4E8813A3F78E")
    IWiaNotifyDevMgr : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewDeviceArrival( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaNotifyDevMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaNotifyDevMgr * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaNotifyDevMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaNotifyDevMgr * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewDeviceArrival )( 
            IWiaNotifyDevMgr * This);
        
        END_INTERFACE
    } IWiaNotifyDevMgrVtbl;

    interface IWiaNotifyDevMgr
    {
        CONST_VTBL struct IWiaNotifyDevMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaNotifyDevMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaNotifyDevMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaNotifyDevMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaNotifyDevMgr_NewDeviceArrival(This)	\
    ( (This)->lpVtbl -> NewDeviceArrival(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaNotifyDevMgr_NewDeviceArrival_Proxy( 
    IWiaNotifyDevMgr * This);


void __RPC_STUB IWiaNotifyDevMgr_NewDeviceArrival_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaNotifyDevMgr_INTERFACE_DEFINED__ */


#ifndef __IWiaItemExtras_INTERFACE_DEFINED__
#define __IWiaItemExtras_INTERFACE_DEFINED__

/* interface IWiaItemExtras */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaItemExtras;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6291ef2c-36ef-4532-876a-8e132593778d")
    IWiaItemExtras : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetExtendedErrorInfo( 
            /* [out] */ BSTR *bstrErrorText) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Escape( 
            /* [in] */ DWORD dwEscapeCode,
            /* [size_is][in] */ BYTE *lpInData,
            /* [in] */ DWORD cbInDataSize,
            /* [length_is][size_is][out] */ BYTE *pOutData,
            /* [in] */ DWORD dwOutDataSize,
            /* [out] */ DWORD *pdwActualDataSize) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CancelPendingIO( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaItemExtrasVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaItemExtras * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaItemExtras * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaItemExtras * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExtendedErrorInfo )( 
            IWiaItemExtras * This,
            /* [out] */ BSTR *bstrErrorText);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Escape )( 
            IWiaItemExtras * This,
            /* [in] */ DWORD dwEscapeCode,
            /* [size_is][in] */ BYTE *lpInData,
            /* [in] */ DWORD cbInDataSize,
            /* [length_is][size_is][out] */ BYTE *pOutData,
            /* [in] */ DWORD dwOutDataSize,
            /* [out] */ DWORD *pdwActualDataSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CancelPendingIO )( 
            IWiaItemExtras * This);
        
        END_INTERFACE
    } IWiaItemExtrasVtbl;

    interface IWiaItemExtras
    {
        CONST_VTBL struct IWiaItemExtrasVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaItemExtras_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaItemExtras_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaItemExtras_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaItemExtras_GetExtendedErrorInfo(This,bstrErrorText)	\
    ( (This)->lpVtbl -> GetExtendedErrorInfo(This,bstrErrorText) ) 

#define IWiaItemExtras_Escape(This,dwEscapeCode,lpInData,cbInDataSize,pOutData,dwOutDataSize,pdwActualDataSize)	\
    ( (This)->lpVtbl -> Escape(This,dwEscapeCode,lpInData,cbInDataSize,pOutData,dwOutDataSize,pdwActualDataSize) ) 

#define IWiaItemExtras_CancelPendingIO(This)	\
    ( (This)->lpVtbl -> CancelPendingIO(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItemExtras_GetExtendedErrorInfo_Proxy( 
    IWiaItemExtras * This,
    /* [out] */ BSTR *bstrErrorText);


void __RPC_STUB IWiaItemExtras_GetExtendedErrorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItemExtras_Escape_Proxy( 
    IWiaItemExtras * This,
    /* [in] */ DWORD dwEscapeCode,
    /* [size_is][in] */ BYTE *lpInData,
    /* [in] */ DWORD cbInDataSize,
    /* [length_is][size_is][out] */ BYTE *pOutData,
    /* [in] */ DWORD dwOutDataSize,
    /* [out] */ DWORD *pdwActualDataSize);


void __RPC_STUB IWiaItemExtras_Escape_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItemExtras_CancelPendingIO_Proxy( 
    IWiaItemExtras * This);


void __RPC_STUB IWiaItemExtras_CancelPendingIO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaItemExtras_INTERFACE_DEFINED__ */


#ifndef __IWiaAppErrorHandler_INTERFACE_DEFINED__
#define __IWiaAppErrorHandler_INTERFACE_DEFINED__

/* interface IWiaAppErrorHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaAppErrorHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C16186C-D0A6-400c-80F4-D26986A0E734")
    IWiaAppErrorHandler : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWindow( 
            /* [out] */ HWND *phwnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportStatus( 
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ LONG lPercentComplete) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaAppErrorHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaAppErrorHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaAppErrorHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaAppErrorHandler * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWindow )( 
            IWiaAppErrorHandler * This,
            /* [out] */ HWND *phwnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReportStatus )( 
            IWiaAppErrorHandler * This,
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ LONG lPercentComplete);
        
        END_INTERFACE
    } IWiaAppErrorHandlerVtbl;

    interface IWiaAppErrorHandler
    {
        CONST_VTBL struct IWiaAppErrorHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaAppErrorHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaAppErrorHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaAppErrorHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaAppErrorHandler_GetWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetWindow(This,phwnd) ) 

#define IWiaAppErrorHandler_ReportStatus(This,lFlags,pWiaItem2,hrStatus,lPercentComplete)	\
    ( (This)->lpVtbl -> ReportStatus(This,lFlags,pWiaItem2,hrStatus,lPercentComplete) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaAppErrorHandler_GetWindow_Proxy( 
    IWiaAppErrorHandler * This,
    /* [out] */ HWND *phwnd);


void __RPC_STUB IWiaAppErrorHandler_GetWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaAppErrorHandler_ReportStatus_Proxy( 
    IWiaAppErrorHandler * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IWiaItem2 *pWiaItem2,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ LONG lPercentComplete);


void __RPC_STUB IWiaAppErrorHandler_ReportStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaAppErrorHandler_INTERFACE_DEFINED__ */


#ifndef __IWiaErrorHandler_INTERFACE_DEFINED__
#define __IWiaErrorHandler_INTERFACE_DEFINED__

/* interface IWiaErrorHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaErrorHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0e4a51b1-bc1f-443d-a835-72e890759ef3")
    IWiaErrorHandler : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReportStatus( 
            /* [in] */ LONG lFlags,
            /* [in] */ HWND hwndParent,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ LONG lPercentComplete) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatusDescription( 
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ HRESULT hrStatus,
            /* [out] */ BSTR *pbstrDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaErrorHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaErrorHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaErrorHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaErrorHandler * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReportStatus )( 
            IWiaErrorHandler * This,
            /* [in] */ LONG lFlags,
            /* [in] */ HWND hwndParent,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ HRESULT hrStatus,
            /* [in] */ LONG lPercentComplete);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStatusDescription )( 
            IWiaErrorHandler * This,
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ HRESULT hrStatus,
            /* [out] */ BSTR *pbstrDescription);
        
        END_INTERFACE
    } IWiaErrorHandlerVtbl;

    interface IWiaErrorHandler
    {
        CONST_VTBL struct IWiaErrorHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaErrorHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaErrorHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaErrorHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaErrorHandler_ReportStatus(This,lFlags,hwndParent,pWiaItem2,hrStatus,lPercentComplete)	\
    ( (This)->lpVtbl -> ReportStatus(This,lFlags,hwndParent,pWiaItem2,hrStatus,lPercentComplete) ) 

#define IWiaErrorHandler_GetStatusDescription(This,lFlags,pWiaItem2,hrStatus,pbstrDescription)	\
    ( (This)->lpVtbl -> GetStatusDescription(This,lFlags,pWiaItem2,hrStatus,pbstrDescription) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaErrorHandler_ReportStatus_Proxy( 
    IWiaErrorHandler * This,
    /* [in] */ LONG lFlags,
    /* [in] */ HWND hwndParent,
    /* [in] */ IWiaItem2 *pWiaItem2,
    /* [in] */ HRESULT hrStatus,
    /* [in] */ LONG lPercentComplete);


void __RPC_STUB IWiaErrorHandler_ReportStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaErrorHandler_GetStatusDescription_Proxy( 
    IWiaErrorHandler * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IWiaItem2 *pWiaItem2,
    /* [in] */ HRESULT hrStatus,
    /* [out] */ BSTR *pbstrDescription);


void __RPC_STUB IWiaErrorHandler_GetStatusDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaErrorHandler_INTERFACE_DEFINED__ */


#ifndef __IWiaTransfer_INTERFACE_DEFINED__
#define __IWiaTransfer_INTERFACE_DEFINED__

/* interface IWiaTransfer */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaTransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c39d6942-2f4e-4d04-92fe-4ef4d3a1de5a")
    IWiaTransfer : public IUnknown
    {
    public:
        virtual /* [helpstring][local] */ HRESULT STDMETHODCALLTYPE Download( 
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaTransferCallback *pIWiaTransferCallback) = 0;
        
        virtual /* [helpstring][local] */ HRESULT STDMETHODCALLTYPE Upload( 
            /* [in] */ LONG lFlags,
            /* [in] */ IStream *pSource,
            /* [in] */ IWiaTransferCallback *pIWiaTransferCallback) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLastError( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumWIA_FORMAT_INFO( 
            /* [out] */ IEnumWIA_FORMAT_INFO **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaTransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaTransfer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaTransfer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaTransfer * This);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE *Download )( 
            IWiaTransfer * This,
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);
        
        /* [helpstring][local] */ HRESULT ( STDMETHODCALLTYPE *Upload )( 
            IWiaTransfer * This,
            /* [in] */ LONG lFlags,
            /* [in] */ IStream *pSource,
            /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLastError )( 
            IWiaTransfer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Cancel )( 
            IWiaTransfer * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumWIA_FORMAT_INFO )( 
            IWiaTransfer * This,
            /* [out] */ IEnumWIA_FORMAT_INFO **ppEnum);
        
        END_INTERFACE
    } IWiaTransferVtbl;

    interface IWiaTransfer
    {
        CONST_VTBL struct IWiaTransferVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaTransfer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaTransfer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaTransfer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaTransfer_Download(This,lFlags,pIWiaTransferCallback)	\
    ( (This)->lpVtbl -> Download(This,lFlags,pIWiaTransferCallback) ) 

#define IWiaTransfer_Upload(This,lFlags,pSource,pIWiaTransferCallback)	\
    ( (This)->lpVtbl -> Upload(This,lFlags,pSource,pIWiaTransferCallback) ) 

#define IWiaTransfer_GetLastError(This)	\
    ( (This)->lpVtbl -> GetLastError(This) ) 

#define IWiaTransfer_Cancel(This)	\
    ( (This)->lpVtbl -> Cancel(This) ) 

#define IWiaTransfer_EnumWIA_FORMAT_INFO(This,ppEnum)	\
    ( (This)->lpVtbl -> EnumWIA_FORMAT_INFO(This,ppEnum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [call_as] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_RemoteDownload_Proxy( 
    IWiaTransfer * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);


void __RPC_STUB IWiaTransfer_RemoteDownload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_RemoteUpload_Proxy( 
    IWiaTransfer * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IStream *pSource,
    /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);


void __RPC_STUB IWiaTransfer_RemoteUpload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_GetLastError_Proxy( 
    IWiaTransfer * This);


void __RPC_STUB IWiaTransfer_GetLastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_Cancel_Proxy( 
    IWiaTransfer * This);


void __RPC_STUB IWiaTransfer_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_EnumWIA_FORMAT_INFO_Proxy( 
    IWiaTransfer * This,
    /* [out] */ IEnumWIA_FORMAT_INFO **ppEnum);


void __RPC_STUB IWiaTransfer_EnumWIA_FORMAT_INFO_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaTransfer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_wia_0142 */
/* [local] */ 

typedef struct _WiaTransferParams
    {
    LONG lMessage;
    LONG lPercentComplete;
    ULONG64 ulBytesWrittenToCurrentStream;
    HRESULT hrErrorStatus;
    } 	WiaTransferParams;



extern RPC_IF_HANDLE __MIDL_itf_wia_0142_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wia_0142_v0_0_s_ifspec;

#ifndef __IWiaTransferCallback_INTERFACE_DEFINED__
#define __IWiaTransferCallback_INTERFACE_DEFINED__

/* interface IWiaTransferCallback */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaTransferCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27d4eaaf-28a6-4ca5-9aab-e678168b9527")
    IWiaTransferCallback : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TransferCallback( 
            /* [in] */ LONG lFlags,
            /* [in] */ WiaTransferParams *pWiaTransferParams) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNextStream( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrItemName,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IStream **ppDestination) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaTransferCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaTransferCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaTransferCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaTransferCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TransferCallback )( 
            IWiaTransferCallback * This,
            /* [in] */ LONG lFlags,
            /* [in] */ WiaTransferParams *pWiaTransferParams);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNextStream )( 
            IWiaTransferCallback * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrItemName,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IStream **ppDestination);
        
        END_INTERFACE
    } IWiaTransferCallbackVtbl;

    interface IWiaTransferCallback
    {
        CONST_VTBL struct IWiaTransferCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaTransferCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaTransferCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaTransferCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaTransferCallback_TransferCallback(This,lFlags,pWiaTransferParams)	\
    ( (This)->lpVtbl -> TransferCallback(This,lFlags,pWiaTransferParams) ) 

#define IWiaTransferCallback_GetNextStream(This,lFlags,bstrItemName,bstrFullItemName,ppDestination)	\
    ( (This)->lpVtbl -> GetNextStream(This,lFlags,bstrItemName,bstrFullItemName,ppDestination) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaTransferCallback_TransferCallback_Proxy( 
    IWiaTransferCallback * This,
    /* [in] */ LONG lFlags,
    /* [in] */ WiaTransferParams *pWiaTransferParams);


void __RPC_STUB IWiaTransferCallback_TransferCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaTransferCallback_GetNextStream_Proxy( 
    IWiaTransferCallback * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrItemName,
    /* [in] */ BSTR bstrFullItemName,
    /* [out] */ IStream **ppDestination);


void __RPC_STUB IWiaTransferCallback_GetNextStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaTransferCallback_INTERFACE_DEFINED__ */


#ifndef __IWiaSegmentationFilter_INTERFACE_DEFINED__
#define __IWiaSegmentationFilter_INTERFACE_DEFINED__

/* interface IWiaSegmentationFilter */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaSegmentationFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC46A697-AC04-4447-8F65-FF63D5154B21")
    IWiaSegmentationFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DetectRegions( 
            /* [in] */ LONG lFlags,
            /* [in] */ IStream *pInputStream,
            /* [in] */ IWiaItem2 *pWiaItem2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaSegmentationFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaSegmentationFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaSegmentationFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaSegmentationFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *DetectRegions )( 
            IWiaSegmentationFilter * This,
            /* [in] */ LONG lFlags,
            /* [in] */ IStream *pInputStream,
            /* [in] */ IWiaItem2 *pWiaItem2);
        
        END_INTERFACE
    } IWiaSegmentationFilterVtbl;

    interface IWiaSegmentationFilter
    {
        CONST_VTBL struct IWiaSegmentationFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaSegmentationFilter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaSegmentationFilter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaSegmentationFilter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaSegmentationFilter_DetectRegions(This,lFlags,pInputStream,pWiaItem2)	\
    ( (This)->lpVtbl -> DetectRegions(This,lFlags,pInputStream,pWiaItem2) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWiaSegmentationFilter_DetectRegions_Proxy( 
    IWiaSegmentationFilter * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IStream *pInputStream,
    /* [in] */ IWiaItem2 *pWiaItem2);


void __RPC_STUB IWiaSegmentationFilter_DetectRegions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaSegmentationFilter_INTERFACE_DEFINED__ */


#ifndef __IWiaImageFilter_INTERFACE_DEFINED__
#define __IWiaImageFilter_INTERFACE_DEFINED__

/* interface IWiaImageFilter */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaImageFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A8A79FFA-450B-41f1-8F87-849CCD94EBF6")
    IWiaImageFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitializeFilter( 
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ IWiaTransferCallback *pWiaTransferCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FilterPreviewImage( 
            /* [in] */ IWiaItem2 *pWiaChildItem2,
            /* [in] */ RECT InputImageExtents,
            /* [in] */ IStream *pInputStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaImageFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaImageFilter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaImageFilter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaImageFilter * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeFilter )( 
            IWiaImageFilter * This,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ IWiaTransferCallback *pWiaTransferCallback);
        
        HRESULT ( STDMETHODCALLTYPE *FilterPreviewImage )( 
            IWiaImageFilter * This,
            /* [in] */ IWiaItem2 *pWiaChildItem2,
            /* [in] */ RECT InputImageExtents,
            /* [in] */ IStream *pInputStream);
        
        END_INTERFACE
    } IWiaImageFilterVtbl;

    interface IWiaImageFilter
    {
        CONST_VTBL struct IWiaImageFilterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaImageFilter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaImageFilter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaImageFilter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaImageFilter_InitializeFilter(This,pWiaItem2,pWiaTransferCallback)	\
    ( (This)->lpVtbl -> InitializeFilter(This,pWiaItem2,pWiaTransferCallback) ) 

#define IWiaImageFilter_FilterPreviewImage(This,pWiaChildItem2,InputImageExtents,pInputStream)	\
    ( (This)->lpVtbl -> FilterPreviewImage(This,pWiaChildItem2,InputImageExtents,pInputStream) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWiaImageFilter_InitializeFilter_Proxy( 
    IWiaImageFilter * This,
    /* [in] */ IWiaItem2 *pWiaItem2,
    /* [in] */ IWiaTransferCallback *pWiaTransferCallback);


void __RPC_STUB IWiaImageFilter_InitializeFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaImageFilter_FilterPreviewImage_Proxy( 
    IWiaImageFilter * This,
    /* [in] */ IWiaItem2 *pWiaChildItem2,
    /* [in] */ RECT InputImageExtents,
    /* [in] */ IStream *pInputStream);


void __RPC_STUB IWiaImageFilter_FilterPreviewImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaImageFilter_INTERFACE_DEFINED__ */


#ifndef __IWiaPreview_INTERFACE_DEFINED__
#define __IWiaPreview_INTERFACE_DEFINED__

/* interface IWiaPreview */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaPreview;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("95C2B4FD-33F2-4d86-AD40-9431F0DF08F7")
    IWiaPreview : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetNewPreview( 
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaTransferCallback *pWiaTransferCallback) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdatePreview( 
            /* [in] */ LONG lOptions,
            /* [in] */ IWiaItem2 *pChildWiaItem2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaPreviewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaPreview * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaPreview * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaPreview * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetNewPreview )( 
            IWiaPreview * This,
            /* [in] */ IWiaItem2 *pWiaItem2,
            /* [in] */ LONG lFlags,
            /* [in] */ IWiaTransferCallback *pWiaTransferCallback);
        
        HRESULT ( STDMETHODCALLTYPE *UpdatePreview )( 
            IWiaPreview * This,
            /* [in] */ LONG lOptions,
            /* [in] */ IWiaItem2 *pChildWiaItem2);
        
        HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IWiaPreview * This);
        
        END_INTERFACE
    } IWiaPreviewVtbl;

    interface IWiaPreview
    {
        CONST_VTBL struct IWiaPreviewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaPreview_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaPreview_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaPreview_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaPreview_GetNewPreview(This,pWiaItem2,lFlags,pWiaTransferCallback)	\
    ( (This)->lpVtbl -> GetNewPreview(This,pWiaItem2,lFlags,pWiaTransferCallback) ) 

#define IWiaPreview_UpdatePreview(This,lOptions,pChildWiaItem2)	\
    ( (This)->lpVtbl -> UpdatePreview(This,lOptions,pChildWiaItem2) ) 

#define IWiaPreview_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWiaPreview_GetNewPreview_Proxy( 
    IWiaPreview * This,
    /* [in] */ IWiaItem2 *pWiaItem2,
    /* [in] */ LONG lFlags,
    /* [in] */ IWiaTransferCallback *pWiaTransferCallback);


void __RPC_STUB IWiaPreview_GetNewPreview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPreview_UpdatePreview_Proxy( 
    IWiaPreview * This,
    /* [in] */ LONG lOptions,
    /* [in] */ IWiaItem2 *pChildWiaItem2);


void __RPC_STUB IWiaPreview_UpdatePreview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWiaPreview_Clear_Proxy( 
    IWiaPreview * This);


void __RPC_STUB IWiaPreview_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaPreview_INTERFACE_DEFINED__ */


#ifndef __IEnumWiaItem2_INTERFACE_DEFINED__
#define __IEnumWiaItem2_INTERFACE_DEFINED__

/* interface IEnumWiaItem2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumWiaItem2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59970AF4-CD0D-44d9-AB24-52295630E582")
    IEnumWiaItem2 : public IUnknown
    {
    public:
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cElt,
            /* [length_is][size_is][out] */ IWiaItem2 **ppIWiaItem2,
            /* [unique][out][in] */ ULONG *pcEltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cElt) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumWiaItem2 **ppIEnum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG *cElt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumWiaItem2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumWiaItem2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumWiaItem2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumWiaItem2 * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumWiaItem2 * This,
            /* [in] */ ULONG cElt,
            /* [length_is][size_is][out] */ IWiaItem2 **ppIWiaItem2,
            /* [unique][out][in] */ ULONG *pcEltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumWiaItem2 * This,
            /* [in] */ ULONG cElt);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumWiaItem2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumWiaItem2 * This,
            /* [out] */ IEnumWiaItem2 **ppIEnum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCount )( 
            IEnumWiaItem2 * This,
            /* [out] */ ULONG *cElt);
        
        END_INTERFACE
    } IEnumWiaItem2Vtbl;

    interface IEnumWiaItem2
    {
        CONST_VTBL struct IEnumWiaItem2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumWiaItem2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumWiaItem2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumWiaItem2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumWiaItem2_Next(This,cElt,ppIWiaItem2,pcEltFetched)	\
    ( (This)->lpVtbl -> Next(This,cElt,ppIWiaItem2,pcEltFetched) ) 

#define IEnumWiaItem2_Skip(This,cElt)	\
    ( (This)->lpVtbl -> Skip(This,cElt) ) 

#define IEnumWiaItem2_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumWiaItem2_Clone(This,ppIEnum)	\
    ( (This)->lpVtbl -> Clone(This,ppIEnum) ) 

#define IEnumWiaItem2_GetCount(This,cElt)	\
    ( (This)->lpVtbl -> GetCount(This,cElt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_RemoteNext_Proxy( 
    IEnumWiaItem2 * This,
    /* [in] */ ULONG cElt,
    /* [length_is][size_is][out] */ IWiaItem2 **ppIWiaItem2,
    /* [unique][out][in] */ ULONG *pcEltFetched);


void __RPC_STUB IEnumWiaItem2_RemoteNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_Skip_Proxy( 
    IEnumWiaItem2 * This,
    /* [in] */ ULONG cElt);


void __RPC_STUB IEnumWiaItem2_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_Reset_Proxy( 
    IEnumWiaItem2 * This);


void __RPC_STUB IEnumWiaItem2_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_Clone_Proxy( 
    IEnumWiaItem2 * This,
    /* [out] */ IEnumWiaItem2 **ppIEnum);


void __RPC_STUB IEnumWiaItem2_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_GetCount_Proxy( 
    IEnumWiaItem2 * This,
    /* [out] */ ULONG *cElt);


void __RPC_STUB IEnumWiaItem2_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumWiaItem2_INTERFACE_DEFINED__ */


#ifndef __IWiaItem2_INTERFACE_DEFINED__
#define __IWiaItem2_INTERFACE_DEFINED__

/* interface IWiaItem2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaItem2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6CBA0075-1287-407d-9B77-CF0E030435CC")
    IWiaItem2 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateChildItem( 
            /* [in] */ LONG lItemFlags,
            /* [in] */ LONG lCreationFlags,
            /* [in] */ BSTR bstrItemName,
            /* [out] */ IWiaItem2 **ppIWiaItem2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteItem( 
            /* [in] */ LONG lFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumChildItems( 
            /* [unique][in] */ const GUID *pCategoryGUID,
            /* [out] */ IEnumWiaItem2 **ppIEnumWiaItem2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindItemByName( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IWiaItem2 **ppIWiaItem2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemCategory( 
            /* [out] */ GUID *pItemCategoryGUID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemType( 
            /* [out] */ LONG *pItemType) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE DeviceDlg( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lIntent,
            /* [out] */ LONG *plItemCount,
            /* [out] */ IWiaItem2 ***ppIWiaItem2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceCommand( 
            /* [in] */ LONG lFlags,
            /* [in] */ const GUID *pCmdGUID,
            /* [out][in] */ IWiaItem2 **ppIWiaItem2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumDeviceCapabilities( 
            /* [in] */ LONG lFlags,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnumWIA_DEV_CAPS) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CheckExtension( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrName,
            /* [in] */ REFIID riidExtensionInterface,
            /* [out] */ BOOL *pbExtensionExists) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetExtension( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrName,
            /* [in] */ REFIID riidExtensionInterface,
            /* [iid_is][out] */ void **ppOut) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetParentItem( 
            /* [out] */ IWiaItem2 **ppIWiaItem2) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRootItem( 
            /* [out] */ IWiaItem2 **ppIWiaItem2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaItem2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaItem2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaItem2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaItem2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateChildItem )( 
            IWiaItem2 * This,
            /* [in] */ LONG lItemFlags,
            /* [in] */ LONG lCreationFlags,
            /* [in] */ BSTR bstrItemName,
            /* [out] */ IWiaItem2 **ppIWiaItem2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteItem )( 
            IWiaItem2 * This,
            /* [in] */ LONG lFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumChildItems )( 
            IWiaItem2 * This,
            /* [unique][in] */ const GUID *pCategoryGUID,
            /* [out] */ IEnumWiaItem2 **ppIEnumWiaItem2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FindItemByName )( 
            IWiaItem2 * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrFullItemName,
            /* [out] */ IWiaItem2 **ppIWiaItem2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemCategory )( 
            IWiaItem2 * This,
            /* [out] */ GUID *pItemCategoryGUID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemType )( 
            IWiaItem2 * This,
            /* [out] */ LONG *pItemType);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *DeviceDlg )( 
            IWiaItem2 * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lFlags,
            /* [in] */ LONG lIntent,
            /* [out] */ LONG *plItemCount,
            /* [out] */ IWiaItem2 ***ppIWiaItem2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceCommand )( 
            IWiaItem2 * This,
            /* [in] */ LONG lFlags,
            /* [in] */ const GUID *pCmdGUID,
            /* [out][in] */ IWiaItem2 **ppIWiaItem2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceCapabilities )( 
            IWiaItem2 * This,
            /* [in] */ LONG lFlags,
            /* [out] */ IEnumWIA_DEV_CAPS **ppIEnumWIA_DEV_CAPS);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *CheckExtension )( 
            IWiaItem2 * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrName,
            /* [in] */ REFIID riidExtensionInterface,
            /* [out] */ BOOL *pbExtensionExists);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *GetExtension )( 
            IWiaItem2 * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrName,
            /* [in] */ REFIID riidExtensionInterface,
            /* [iid_is][out] */ void **ppOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetParentItem )( 
            IWiaItem2 * This,
            /* [out] */ IWiaItem2 **ppIWiaItem2);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRootItem )( 
            IWiaItem2 * This,
            /* [out] */ IWiaItem2 **ppIWiaItem2);
        
        END_INTERFACE
    } IWiaItem2Vtbl;

    interface IWiaItem2
    {
        CONST_VTBL struct IWiaItem2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaItem2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaItem2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaItem2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaItem2_CreateChildItem(This,lItemFlags,lCreationFlags,bstrItemName,ppIWiaItem2)	\
    ( (This)->lpVtbl -> CreateChildItem(This,lItemFlags,lCreationFlags,bstrItemName,ppIWiaItem2) ) 

#define IWiaItem2_DeleteItem(This,lFlags)	\
    ( (This)->lpVtbl -> DeleteItem(This,lFlags) ) 

#define IWiaItem2_EnumChildItems(This,pCategoryGUID,ppIEnumWiaItem2)	\
    ( (This)->lpVtbl -> EnumChildItems(This,pCategoryGUID,ppIEnumWiaItem2) ) 

#define IWiaItem2_FindItemByName(This,lFlags,bstrFullItemName,ppIWiaItem2)	\
    ( (This)->lpVtbl -> FindItemByName(This,lFlags,bstrFullItemName,ppIWiaItem2) ) 

#define IWiaItem2_GetItemCategory(This,pItemCategoryGUID)	\
    ( (This)->lpVtbl -> GetItemCategory(This,pItemCategoryGUID) ) 

#define IWiaItem2_GetItemType(This,pItemType)	\
    ( (This)->lpVtbl -> GetItemType(This,pItemType) ) 

#define IWiaItem2_DeviceDlg(This,hwndParent,lFlags,lIntent,plItemCount,ppIWiaItem2)	\
    ( (This)->lpVtbl -> DeviceDlg(This,hwndParent,lFlags,lIntent,plItemCount,ppIWiaItem2) ) 

#define IWiaItem2_DeviceCommand(This,lFlags,pCmdGUID,ppIWiaItem2)	\
    ( (This)->lpVtbl -> DeviceCommand(This,lFlags,pCmdGUID,ppIWiaItem2) ) 

#define IWiaItem2_EnumDeviceCapabilities(This,lFlags,ppIEnumWIA_DEV_CAPS)	\
    ( (This)->lpVtbl -> EnumDeviceCapabilities(This,lFlags,ppIEnumWIA_DEV_CAPS) ) 

#define IWiaItem2_CheckExtension(This,lFlags,bstrName,riidExtensionInterface,pbExtensionExists)	\
    ( (This)->lpVtbl -> CheckExtension(This,lFlags,bstrName,riidExtensionInterface,pbExtensionExists) ) 

#define IWiaItem2_GetExtension(This,lFlags,bstrName,riidExtensionInterface,ppOut)	\
    ( (This)->lpVtbl -> GetExtension(This,lFlags,bstrName,riidExtensionInterface,ppOut) ) 

#define IWiaItem2_GetParentItem(This,ppIWiaItem2)	\
    ( (This)->lpVtbl -> GetParentItem(This,ppIWiaItem2) ) 

#define IWiaItem2_GetRootItem(This,ppIWiaItem2)	\
    ( (This)->lpVtbl -> GetRootItem(This,ppIWiaItem2) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_CreateChildItem_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lItemFlags,
    /* [in] */ LONG lCreationFlags,
    /* [in] */ BSTR bstrItemName,
    /* [out] */ IWiaItem2 **ppIWiaItem2);


void __RPC_STUB IWiaItem2_CreateChildItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_DeleteItem_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags);


void __RPC_STUB IWiaItem2_DeleteItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_EnumChildItems_Proxy( 
    IWiaItem2 * This,
    /* [unique][in] */ const GUID *pCategoryGUID,
    /* [out] */ IEnumWiaItem2 **ppIEnumWiaItem2);


void __RPC_STUB IWiaItem2_EnumChildItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_FindItemByName_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrFullItemName,
    /* [out] */ IWiaItem2 **ppIWiaItem2);


void __RPC_STUB IWiaItem2_FindItemByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_GetItemCategory_Proxy( 
    IWiaItem2 * This,
    /* [out] */ GUID *pItemCategoryGUID);


void __RPC_STUB IWiaItem2_GetItemCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_GetItemType_Proxy( 
    IWiaItem2 * This,
    /* [out] */ LONG *pItemType);


void __RPC_STUB IWiaItem2_GetItemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem2_LocalDeviceDlg_Proxy( 
    IWiaItem2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [out] */ LONG *plItemCount,
    /* [out] */ IWiaItem2 ***ppIWiaItem2);


void __RPC_STUB IWiaItem2_LocalDeviceDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_DeviceCommand_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ const GUID *pCmdGUID,
    /* [out][in] */ IWiaItem2 **ppIWiaItem2);


void __RPC_STUB IWiaItem2_DeviceCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_EnumDeviceCapabilities_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [out] */ IEnumWIA_DEV_CAPS **ppIEnumWIA_DEV_CAPS);


void __RPC_STUB IWiaItem2_EnumDeviceCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem2_RemoteCheckExtension_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrName,
    /* [in] */ REFIID riidExtensionInterface,
    /* [out] */ BOOL *pbExtensionExists);


void __RPC_STUB IWiaItem2_RemoteCheckExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem2_RemoteGetExtension_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrName,
    /* [in] */ REFIID riidExtensionInterface,
    /* [iid_is][out] */ void **ppOut);


void __RPC_STUB IWiaItem2_RemoteGetExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_GetParentItem_Proxy( 
    IWiaItem2 * This,
    /* [out] */ IWiaItem2 **ppIWiaItem2);


void __RPC_STUB IWiaItem2_GetParentItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaItem2_GetRootItem_Proxy( 
    IWiaItem2 * This,
    /* [out] */ IWiaItem2 **ppIWiaItem2);


void __RPC_STUB IWiaItem2_GetRootItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaItem2_INTERFACE_DEFINED__ */


#ifndef __IWiaDevMgr2_INTERFACE_DEFINED__
#define __IWiaDevMgr2_INTERFACE_DEFINED__

/* interface IWiaDevMgr2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWiaDevMgr2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79C07CF1-CBDD-41ee-8EC3-F00080CADA7A")
    IWiaDevMgr2 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumDeviceInfo( 
            /* [in] */ LONG lFlags,
            /* [retval][out] */ IEnumWIA_DEV_INFO **ppIEnum) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateDevice( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [out] */ IWiaItem2 **ppWiaItem2Root) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SelectDeviceDlg( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [out][in] */ BSTR *pbstrDeviceID,
            /* [retval][out] */ IWiaItem2 **ppItemRoot) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE SelectDeviceDlgID( 
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [retval][out] */ BSTR *pbstrDeviceID) = 0;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE RegisterEventCallbackInterface( 
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
            /* [out] */ IUnknown **pEventObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWiaDevMgr2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWiaDevMgr2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWiaDevMgr2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWiaDevMgr2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumDeviceInfo )( 
            IWiaDevMgr2 * This,
            /* [in] */ LONG lFlags,
            /* [retval][out] */ IEnumWIA_DEV_INFO **ppIEnum);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *CreateDevice )( 
            IWiaDevMgr2 * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [out] */ IWiaItem2 **ppWiaItem2Root);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SelectDeviceDlg )( 
            IWiaDevMgr2 * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [out][in] */ BSTR *pbstrDeviceID,
            /* [retval][out] */ IWiaItem2 **ppItemRoot);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *SelectDeviceDlgID )( 
            IWiaDevMgr2 * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ LONG lDeviceType,
            /* [in] */ LONG lFlags,
            /* [retval][out] */ BSTR *pbstrDeviceID);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *RegisterEventCallbackInterface )( 
            IWiaDevMgr2 * This,
            /* [in] */ LONG lFlags,
            /* [in] */ BSTR bstrDeviceID,
            /* [in] */ const GUID *pEventGUID,
            /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
            /* [out] */ IUnknown **pEventObject);
        
        END_INTERFACE
    } IWiaDevMgr2Vtbl;

    interface IWiaDevMgr2
    {
        CONST_VTBL struct IWiaDevMgr2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWiaDevMgr2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWiaDevMgr2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWiaDevMgr2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWiaDevMgr2_EnumDeviceInfo(This,lFlags,ppIEnum)	\
    ( (This)->lpVtbl -> EnumDeviceInfo(This,lFlags,ppIEnum) ) 

#define IWiaDevMgr2_CreateDevice(This,lFlags,bstrDeviceID,ppWiaItem2Root)	\
    ( (This)->lpVtbl -> CreateDevice(This,lFlags,bstrDeviceID,ppWiaItem2Root) ) 

#define IWiaDevMgr2_SelectDeviceDlg(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID,ppItemRoot)	\
    ( (This)->lpVtbl -> SelectDeviceDlg(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID,ppItemRoot) ) 

#define IWiaDevMgr2_SelectDeviceDlgID(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID)	\
    ( (This)->lpVtbl -> SelectDeviceDlgID(This,hwndParent,lDeviceType,lFlags,pbstrDeviceID) ) 

#define IWiaDevMgr2_RegisterEventCallbackInterface(This,lFlags,bstrDeviceID,pEventGUID,pIWiaEventCallback,pEventObject)	\
    ( (This)->lpVtbl -> RegisterEventCallbackInterface(This,lFlags,bstrDeviceID,pEventGUID,pIWiaEventCallback,pEventObject) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_EnumDeviceInfo_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ IEnumWIA_DEV_INFO **ppIEnum);


void __RPC_STUB IWiaDevMgr2_EnumDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_LocalCreateDevice_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [out] */ IWiaItem2 **ppWiaItem2Root);


void __RPC_STUB IWiaDevMgr2_LocalCreateDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_LocalSelectDeviceDlg_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [out][in] */ BSTR *pbstrDeviceID,
    /* [retval][out] */ IWiaItem2 **ppItemRoot);


void __RPC_STUB IWiaDevMgr2_LocalSelectDeviceDlg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_LocalSelectDeviceDlgID_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ BSTR *pbstrDeviceID);


void __RPC_STUB IWiaDevMgr2_LocalSelectDeviceDlgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_LocalRegisterEventCallbackInterface_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
    /* [out] */ IUnknown **pEventObject);


void __RPC_STUB IWiaDevMgr2_LocalRegisterEventCallbackInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWiaDevMgr2_INTERFACE_DEFINED__ */



#ifndef __WiaDevMgr_LIBRARY_DEFINED__
#define __WiaDevMgr_LIBRARY_DEFINED__

/* library WiaDevMgr */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WiaDevMgr;

EXTERN_C const CLSID CLSID_WiaDevMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("a1f4e726-8cf1-11d1-bf92-0060081ed811")
WiaDevMgr;
#endif

EXTERN_C const CLSID CLSID_WiaDevMgr2;

#ifdef __cplusplus

class DECLSPEC_UUID("B6C292BC-7C88-41ee-8B54-8EC92617E599")
WiaDevMgr2;
#endif

EXTERN_C const CLSID CLSID_WiaLog;

#ifdef __cplusplus

class DECLSPEC_UUID("A1E75357-881A-419e-83E2-BB16DB197C68")
WiaLog;
#endif

EXTERN_C const CLSID CLSID_WiaPreview;

#ifdef __cplusplus

class DECLSPEC_UUID("FEC52D45-D657-42c3-B43E-BF64B95E7072")
WiaPreview;
#endif
#endif /* __WiaDevMgr_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  STGMEDIUM_UserSize(     unsigned long *, unsigned long            , STGMEDIUM * ); 
unsigned char * __RPC_USER  STGMEDIUM_UserMarshal(  unsigned long *, unsigned char *, STGMEDIUM * ); 
unsigned char * __RPC_USER  STGMEDIUM_UserUnmarshal(unsigned long *, unsigned char *, STGMEDIUM * ); 
void                      __RPC_USER  STGMEDIUM_UserFree(     unsigned long *, STGMEDIUM * ); 

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_CreateDevice_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ BSTR bstrDeviceID,
    /* [out] */ IWiaItem **ppWiaItemRoot);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_CreateDevice_Stub( 
    IWiaDevMgr * This,
    /* [in] */ BSTR bstrDeviceID,
    /* [out] */ IWiaItem **ppWiaItemRoot);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_SelectDeviceDlg_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [out][in] */ BSTR *pbstrDeviceID,
    /* [retval][out] */ IWiaItem **ppItemRoot);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_SelectDeviceDlg_Stub( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [out][in] */ BSTR *pbstrDeviceID,
    /* [retval][out] */ IWiaItem **ppItemRoot);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_SelectDeviceDlgID_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ BSTR *pbstrDeviceID);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_SelectDeviceDlgID_Stub( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ BSTR *pbstrDeviceID);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_GetImageDlg_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [in] */ IWiaItem *pItemRoot,
    /* [in] */ BSTR bstrFilename,
    /* [out][in] */ GUID *pguidFormat);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_GetImageDlg_Stub( 
    IWiaDevMgr * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [in] */ IWiaItem *pItemRoot,
    /* [in] */ BSTR bstrFilename,
    /* [out][in] */ GUID *pguidFormat);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_RegisterEventCallbackProgram_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [in] */ BSTR bstrCommandline,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIcon);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_RegisterEventCallbackProgram_Stub( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [in] */ BSTR bstrCommandline,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIcon);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_RegisterEventCallbackInterface_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
    /* [out] */ IUnknown **pEventObject);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_RegisterEventCallbackInterface_Stub( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
    /* [out] */ IUnknown **pEventObject);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_RegisterEventCallbackCLSID_Proxy( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ const GUID *pClsID,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIcon);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr_RegisterEventCallbackCLSID_Stub( 
    IWiaDevMgr * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ const GUID *pClsID,
    /* [in] */ BSTR bstrName,
    /* [in] */ BSTR bstrDescription,
    /* [in] */ BSTR bstrIcon);

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_Next_Proxy( 
    IEnumWIA_DEV_INFO * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IWiaPropertyStorage **rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_INFO_Next_Stub( 
    IEnumWIA_DEV_INFO * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IWiaPropertyStorage **rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDataCallback_BandedDataCallback_Proxy( 
    IWiaDataCallback * This,
    /* [in] */ LONG lMessage,
    /* [in] */ LONG lStatus,
    /* [in] */ LONG lPercentComplete,
    /* [in] */ LONG lOffset,
    /* [in] */ LONG lLength,
    /* [in] */ LONG lReserved,
    /* [in] */ LONG lResLength,
    /* [size_is][in] */ BYTE *pbBuffer);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDataCallback_BandedDataCallback_Stub( 
    IWiaDataCallback * This,
    /* [in] */ LONG lMessage,
    /* [in] */ LONG lStatus,
    /* [in] */ LONG lPercentComplete,
    /* [in] */ LONG lOffset,
    /* [in] */ LONG lLength,
    /* [in] */ LONG lReserved,
    /* [in] */ LONG lResLength,
    /* [unique][size_is][in] */ BYTE *pbBuffer);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetData_Proxy( 
    IWiaDataTransfer * This,
    /* [out][in] */ LPSTGMEDIUM pMedium,
    /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetData_Stub( 
    IWiaDataTransfer * This,
    /* [out][in] */ LPSTGMEDIUM pMedium,
    /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetBandedData_Proxy( 
    IWiaDataTransfer * This,
    /* [unique][in] */ PWIA_DATA_TRANSFER_INFO pWiaDataTransInfo,
    /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDataTransfer_idtGetBandedData_Stub( 
    IWiaDataTransfer * This,
    /* [unique][in] */ PWIA_DATA_TRANSFER_INFO pWiaDataTransInfo,
    /* [unique][in] */ IWiaDataCallback *pIWiaDataCallback);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaItem_DeviceDlg_Proxy( 
    IWiaItem * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [out] */ LONG *plItemCount,
    /* [out] */ IWiaItem ***ppIWiaItem);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem_DeviceDlg_Stub( 
    IWiaItem * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [out] */ LONG *plItemCount,
    /* [out] */ IWiaItem ***pIWiaItem);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_WriteMultiple_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpspec,
    /* [size_is][in] */ const PROPSPEC rgpspec[  ],
    /* [size_is][in] */ const PROPVARIANT rgpropvar[  ],
    /* [in] */ PROPID propidNameFirst);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_WriteMultiple_Stub( 
    IWiaPropertyStorage * This,
    /* [in] */ ULONG cpspec,
    /* [size_is][in] */ const PROPSPEC *rgpspec,
    /* [size_is][in] */ const PROPVARIANT *rgpropvar,
    /* [in] */ PROPID propidNameFirst);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_SetPropertyStream_Proxy( 
    IWiaPropertyStorage * This,
    /* [in] */ GUID *pCompatibilityId,
    /* [unique][in] */ IStream *pIStream);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaPropertyStorage_SetPropertyStream_Stub( 
    IWiaPropertyStorage * This,
    /* [in] */ GUID *pCompatibilityId,
    /* [unique][in] */ IStream *pIStream);

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_Next_Proxy( 
    IEnumWiaItem * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IWiaItem **ppIWiaItem,
    /* [unique][out][in] */ ULONG *pceltFetched);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem_Next_Stub( 
    IEnumWiaItem * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ IWiaItem **ppIWiaItem,
    /* [unique][out][in] */ ULONG *pceltFetched);

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_Next_Proxy( 
    IEnumWIA_DEV_CAPS * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ WIA_DEV_CAP *rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWIA_DEV_CAPS_Next_Stub( 
    IEnumWIA_DEV_CAPS * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ WIA_DEV_CAP *rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_Next_Proxy( 
    IEnumWIA_FORMAT_INFO * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ WIA_FORMAT_INFO *rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWIA_FORMAT_INFO_Next_Stub( 
    IEnumWIA_FORMAT_INFO * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ WIA_FORMAT_INFO *rgelt,
    /* [unique][out][in] */ ULONG *pceltFetched);

/* [helpstring][local] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_Download_Proxy( 
    IWiaTransfer * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_Download_Stub( 
    IWiaTransfer * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);

/* [helpstring][local] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_Upload_Proxy( 
    IWiaTransfer * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IStream *pSource,
    /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);


/* [call_as] */ HRESULT STDMETHODCALLTYPE IWiaTransfer_Upload_Stub( 
    IWiaTransfer * This,
    /* [in] */ LONG lFlags,
    /* [in] */ IStream *pSource,
    /* [in] */ IWiaTransferCallback *pIWiaTransferCallback);

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_Next_Proxy( 
    IEnumWiaItem2 * This,
    /* [in] */ ULONG cElt,
    /* [length_is][size_is][out] */ IWiaItem2 **ppIWiaItem2,
    /* [unique][out][in] */ ULONG *pcEltFetched);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IEnumWiaItem2_Next_Stub( 
    IEnumWiaItem2 * This,
    /* [in] */ ULONG cElt,
    /* [length_is][size_is][out] */ IWiaItem2 **ppIWiaItem2,
    /* [unique][out][in] */ ULONG *pcEltFetched);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaItem2_DeviceDlg_Proxy( 
    IWiaItem2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [out] */ LONG *plItemCount,
    /* [out] */ IWiaItem2 ***ppIWiaItem2);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem2_DeviceDlg_Stub( 
    IWiaItem2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lFlags,
    /* [in] */ LONG lIntent,
    /* [out] */ LONG *plItemCount,
    /* [out] */ IWiaItem2 ***ppIWiaItem2);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaItem2_CheckExtension_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrName,
    /* [in] */ REFIID riidExtensionInterface,
    /* [out] */ BOOL *pbExtensionExists);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem2_CheckExtension_Stub( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrName,
    /* [in] */ REFIID riidExtensionInterface,
    /* [out] */ BOOL *pbExtensionExists);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaItem2_GetExtension_Proxy( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrName,
    /* [in] */ REFIID riidExtensionInterface,
    /* [iid_is][out] */ void **ppOut);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaItem2_GetExtension_Stub( 
    IWiaItem2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrName,
    /* [in] */ REFIID riidExtensionInterface,
    /* [iid_is][out] */ void **ppOut);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_CreateDevice_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [out] */ IWiaItem2 **ppWiaItem2Root);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_CreateDevice_Stub( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [out] */ IWiaItem2 **ppWiaItem2Root);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_SelectDeviceDlg_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [out][in] */ BSTR *pbstrDeviceID,
    /* [retval][out] */ IWiaItem2 **ppItemRoot);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_SelectDeviceDlg_Stub( 
    IWiaDevMgr2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [out][in] */ BSTR *pbstrDeviceID,
    /* [retval][out] */ IWiaItem2 **ppItemRoot);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_SelectDeviceDlgID_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ BSTR *pbstrDeviceID);


/* [nocode][helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_SelectDeviceDlgID_Stub( 
    IWiaDevMgr2 * This,
    /* [in] */ HWND hwndParent,
    /* [in] */ LONG lDeviceType,
    /* [in] */ LONG lFlags,
    /* [retval][out] */ BSTR *pbstrDeviceID);

/* [local] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_RegisterEventCallbackInterface_Proxy( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
    /* [out] */ IUnknown **pEventObject);


/* [helpstring][call_as] */ HRESULT STDMETHODCALLTYPE IWiaDevMgr2_RegisterEventCallbackInterface_Stub( 
    IWiaDevMgr2 * This,
    /* [in] */ LONG lFlags,
    /* [in] */ BSTR bstrDeviceID,
    /* [in] */ const GUID *pEventGUID,
    /* [unique][in] */ IWiaEventCallback *pIWiaEventCallback,
    /* [out] */ IUnknown **pEventObject);



/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


