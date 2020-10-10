

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for wcmhandler.idl:
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

#ifndef __wcmhandler_h__
#define __wcmhandler_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWcmData_FWD_DEFINED__
#define __IWcmData_FWD_DEFINED__
typedef interface IWcmData IWcmData;
#endif 	/* __IWcmData_FWD_DEFINED__ */


#ifndef __IWcmEnumerator_FWD_DEFINED__
#define __IWcmEnumerator_FWD_DEFINED__
typedef interface IWcmEnumerator IWcmEnumerator;
#endif 	/* __IWcmEnumerator_FWD_DEFINED__ */


#ifndef __IWcmHandler_FWD_DEFINED__
#define __IWcmHandler_FWD_DEFINED__
typedef interface IWcmHandler IWcmHandler;
#endif 	/* __IWcmHandler_FWD_DEFINED__ */


#ifndef __IWcmHelper_FWD_DEFINED__
#define __IWcmHelper_FWD_DEFINED__
typedef interface IWcmHelper IWcmHelper;
#endif 	/* __IWcmHelper_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wcmhandler_0000 */
/* [local] */ 

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_wcmhandler_0000_0001
    {	SharedContext	= 0,
	UserContext	= 1,
	UnknownContext	= 2
    } 	WcmNamespaceContext;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_wcmhandler_0000_0002
    {	wsmdtByte	= 1,
	wsmdtSByte	= 2,
	wsmdtUInt16	= 3,
	wsmdtInt16	= 4,
	wsmdtUInt32	= 5,
	wsmdtInt32	= 6,
	wsmdtUInt64	= 7,
	wsmdtInt64	= 8,
	wsmdtDouble	= 9,
	wsmdtSingle	= 10,
	wsmdtBoolean	= 11,
	wsmdtString	= 12,
	wsmdtDateTime	= 13,
	wsmdtDecimal	= 14,
	wsmdtUri	= 15,
	wsmdtComplex	= 16,
	wsmdtAnyType	= 17,
	wsmdtUntyped	= 18
    } 	wsmdtEnum;

typedef /* [public] */ 
enum __MIDL___MIDL_itf_wcmhandler_0000_0003
    {	wcmdtByte	= 1,
	wcmdtSByte	= 2,
	wcmdtUInt16	= 3,
	wcmdtInt16	= 4,
	wcmdtUInt32	= 5,
	wcmdtInt32	= 6,
	wcmdtUInt64	= 7,
	wcmdtInt64	= 8,
	wcmdtDouble	= 9,
	wcmdtSingle	= 10,
	wcmdtBoolean	= 11,
	wcmdtString	= 12,
	wcmdtDateTime	= 13,
	wcmdtDecimal	= 14,
	wcmdtUri	= 15,
	wcmdtComplex	= 16,
	wcmdtAnyType	= 17,
	wcmdtUntyped	= 18
    } 	wcmdtEnum;





typedef /* [public] */ 
enum __MIDL___MIDL_itf_wcmhandler_0000_0004
    {	wsmshManaged	= 0,
	wsmshRegistry	= 1,
	wsmshIniFile	= 2,
	wsmshBlob	= 3,
	wsmshCustom	= 4
    } 	wsmshEnum;

typedef UINT wsmTimestamp;

#define wsmtsBase     0
#define wsmtsNull     0xFFFFFFFF
#define wsmtsLocal    0xFFFFFFFE
typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_wcmhandler_0000_0005
    {	EnumAll	= 0,
	EnumComplexMember	= 1,
	EnumScalarMember	= 2
    } 	WcmEnumOptions;

#define wcmhcReadOnly     0x0001
#define wcmhcTimestamps   0x0010
#define wcmhcReconciles   0x0020
#define wcmhcTransacted   0x0040
#define wcmhcIsolation    0x0080
#define wcmhcDeleteLog    0x0100
#define wcmhcFiltering    0x0200
#define wcmhoReadOnly      0x00000010
#define wcmhoLocalOnly     0x00000020
#define wcmhoFullIsolated  0x00000100
#define wcmhoEnumGroups    0x00010000
#define wcmhoSharedContext 0x01000000
#define wcmhoUserContext   0x10000000
#define wcmhoSetupMode   0x00100000
#define wsmdoArray               0x00008000
#define wsmdoList                0x00004000
#define wsmdoXsdSimple           0x00002000
#define wsmdoXmlAttribute        0x00001000
#define wsmdoDeleted             0x00010000
#define wsmdoNullValue           0x00020000
#define wsmdoRefactoredSetting   0x00040000
#define wsmcoCommit      0x0000
#define wsmcoRollback    0x0001
#define wsmcoReload      0x0002
#define wsmcoAllowed     (wsmcoCommit + wsmcoRollback + wsmcoReload)
#define S_NULLVALUE          _HRESULT_TYPEDEF_(0x00220002L)
#define S_DELETED            _HRESULT_TYPEDEF_(0x00220003L)
typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_wcmhandler_0000_0006
    {	wsmiiPriorityList	= 0x20,
	wsmiiLatestTxId	= 0x21,
	wsmiiTimestamp	= 0x22,
	wsmiiLegacyLocation	= 0x23,
	wsmiiHandlerCapability	= 0x24,
	wsmiiCommittable	= 0x25,
	wsmiiSettingExist	= 0x26,
	wsmiiLastLegacySyncValue	= 0x100
    } 	wsmiiEnum;



extern RPC_IF_HANDLE __MIDL_itf_wcmhandler_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wcmhandler_0000_v0_0_s_ifspec;

#ifndef __IWcmData_INTERFACE_DEFINED__
#define __IWcmData_INTERFACE_DEFINED__

/* interface IWcmData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWcmData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("733E4E52-3BA4-11D7-BF56-000874CD1BAE")
    IWcmData : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetData( 
            /* [size_is][in] */ const BYTE *pb,
            /* [in] */ UINT cb) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [out] */ UINT *cb,
            /* [size_is][size_is][out] */ BYTE **pb) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDataAndType( 
            /* [size_is][in] */ const BYTE *pb,
            /* [in] */ UINT cb,
            /* [in] */ UINT iType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetUnicodeString( 
            /* [string][in] */ const WCHAR *szData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            /* [out] */ UINT *piType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimestamp( 
            /* [out] */ wsmTimestamp *pwsmts) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimestamp( 
            /* [in] */ wsmTimestamp wsmts) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContext( 
            /* [out] */ WcmNamespaceContext *context) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetContext( 
            /* [in] */ WcmNamespaceContext context) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsNullObject( 
            /* [out] */ boolean *pfResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ UINT *pcbData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSize( 
            /* [in] */ UINT cbData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCoTaskMemAlloc( 
            /* [in] */ boolean fUseCoTaskMemAlloc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWcmDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWcmData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWcmData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWcmData * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetData )( 
            IWcmData * This,
            /* [size_is][in] */ const BYTE *pb,
            /* [in] */ UINT cb);
        
        HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IWcmData * This,
            /* [out] */ UINT *cb,
            /* [size_is][size_is][out] */ BYTE **pb);
        
        HRESULT ( STDMETHODCALLTYPE *SetDataAndType )( 
            IWcmData * This,
            /* [size_is][in] */ const BYTE *pb,
            /* [in] */ UINT cb,
            /* [in] */ UINT iType);
        
        HRESULT ( STDMETHODCALLTYPE *SetUnicodeString )( 
            IWcmData * This,
            /* [string][in] */ const WCHAR *szData);
        
        HRESULT ( STDMETHODCALLTYPE *GetType )( 
            IWcmData * This,
            /* [out] */ UINT *piType);
        
        HRESULT ( STDMETHODCALLTYPE *GetTimestamp )( 
            IWcmData * This,
            /* [out] */ wsmTimestamp *pwsmts);
        
        HRESULT ( STDMETHODCALLTYPE *SetTimestamp )( 
            IWcmData * This,
            /* [in] */ wsmTimestamp wsmts);
        
        HRESULT ( STDMETHODCALLTYPE *GetContext )( 
            IWcmData * This,
            /* [out] */ WcmNamespaceContext *context);
        
        HRESULT ( STDMETHODCALLTYPE *SetContext )( 
            IWcmData * This,
            /* [in] */ WcmNamespaceContext context);
        
        HRESULT ( STDMETHODCALLTYPE *IsNullObject )( 
            IWcmData * This,
            /* [out] */ boolean *pfResult);
        
        HRESULT ( STDMETHODCALLTYPE *GetSize )( 
            IWcmData * This,
            /* [out] */ UINT *pcbData);
        
        HRESULT ( STDMETHODCALLTYPE *SetSize )( 
            IWcmData * This,
            /* [in] */ UINT cbData);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWcmData * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetCoTaskMemAlloc )( 
            IWcmData * This,
            /* [in] */ boolean fUseCoTaskMemAlloc);
        
        END_INTERFACE
    } IWcmDataVtbl;

    interface IWcmData
    {
        CONST_VTBL struct IWcmDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWcmData_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWcmData_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWcmData_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWcmData_SetData(This,pb,cb)	\
    ( (This)->lpVtbl -> SetData(This,pb,cb) ) 

#define IWcmData_GetData(This,cb,pb)	\
    ( (This)->lpVtbl -> GetData(This,cb,pb) ) 

#define IWcmData_SetDataAndType(This,pb,cb,iType)	\
    ( (This)->lpVtbl -> SetDataAndType(This,pb,cb,iType) ) 

#define IWcmData_SetUnicodeString(This,szData)	\
    ( (This)->lpVtbl -> SetUnicodeString(This,szData) ) 

#define IWcmData_GetType(This,piType)	\
    ( (This)->lpVtbl -> GetType(This,piType) ) 

#define IWcmData_GetTimestamp(This,pwsmts)	\
    ( (This)->lpVtbl -> GetTimestamp(This,pwsmts) ) 

#define IWcmData_SetTimestamp(This,wsmts)	\
    ( (This)->lpVtbl -> SetTimestamp(This,wsmts) ) 

#define IWcmData_GetContext(This,context)	\
    ( (This)->lpVtbl -> GetContext(This,context) ) 

#define IWcmData_SetContext(This,context)	\
    ( (This)->lpVtbl -> SetContext(This,context) ) 

#define IWcmData_IsNullObject(This,pfResult)	\
    ( (This)->lpVtbl -> IsNullObject(This,pfResult) ) 

#define IWcmData_GetSize(This,pcbData)	\
    ( (This)->lpVtbl -> GetSize(This,pcbData) ) 

#define IWcmData_SetSize(This,cbData)	\
    ( (This)->lpVtbl -> SetSize(This,cbData) ) 

#define IWcmData_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IWcmData_SetCoTaskMemAlloc(This,fUseCoTaskMemAlloc)	\
    ( (This)->lpVtbl -> SetCoTaskMemAlloc(This,fUseCoTaskMemAlloc) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWcmData_SetData_Proxy( 
    IWcmData * This,
    /* [size_is][in] */ const BYTE *pb,
    /* [in] */ UINT cb);


void __RPC_STUB IWcmData_SetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_GetData_Proxy( 
    IWcmData * This,
    /* [out] */ UINT *cb,
    /* [size_is][size_is][out] */ BYTE **pb);


void __RPC_STUB IWcmData_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_SetDataAndType_Proxy( 
    IWcmData * This,
    /* [size_is][in] */ const BYTE *pb,
    /* [in] */ UINT cb,
    /* [in] */ UINT iType);


void __RPC_STUB IWcmData_SetDataAndType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_SetUnicodeString_Proxy( 
    IWcmData * This,
    /* [string][in] */ const WCHAR *szData);


void __RPC_STUB IWcmData_SetUnicodeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_GetType_Proxy( 
    IWcmData * This,
    /* [out] */ UINT *piType);


void __RPC_STUB IWcmData_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_GetTimestamp_Proxy( 
    IWcmData * This,
    /* [out] */ wsmTimestamp *pwsmts);


void __RPC_STUB IWcmData_GetTimestamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_SetTimestamp_Proxy( 
    IWcmData * This,
    /* [in] */ wsmTimestamp wsmts);


void __RPC_STUB IWcmData_SetTimestamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_GetContext_Proxy( 
    IWcmData * This,
    /* [out] */ WcmNamespaceContext *context);


void __RPC_STUB IWcmData_GetContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_SetContext_Proxy( 
    IWcmData * This,
    /* [in] */ WcmNamespaceContext context);


void __RPC_STUB IWcmData_SetContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_IsNullObject_Proxy( 
    IWcmData * This,
    /* [out] */ boolean *pfResult);


void __RPC_STUB IWcmData_IsNullObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_GetSize_Proxy( 
    IWcmData * This,
    /* [out] */ UINT *pcbData);


void __RPC_STUB IWcmData_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_SetSize_Proxy( 
    IWcmData * This,
    /* [in] */ UINT cbData);


void __RPC_STUB IWcmData_SetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_Reset_Proxy( 
    IWcmData * This);


void __RPC_STUB IWcmData_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmData_SetCoTaskMemAlloc_Proxy( 
    IWcmData * This,
    /* [in] */ boolean fUseCoTaskMemAlloc);


void __RPC_STUB IWcmData_SetCoTaskMemAlloc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWcmData_INTERFACE_DEFINED__ */


#ifndef __IWcmEnumerator_INTERFACE_DEFINED__
#define __IWcmEnumerator_INTERFACE_DEFINED__

/* interface IWcmEnumerator */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWcmEnumerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("733E4E53-3BA4-11D7-BF56-000874CD1BAE")
    IWcmEnumerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Current( 
            /* [in] */ IWcmData *pDataObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveNext( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWcmEnumeratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWcmEnumerator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWcmEnumerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWcmEnumerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *Current )( 
            IWcmEnumerator * This,
            /* [in] */ IWcmData *pDataObj);
        
        HRESULT ( STDMETHODCALLTYPE *MoveNext )( 
            IWcmEnumerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWcmEnumerator * This);
        
        END_INTERFACE
    } IWcmEnumeratorVtbl;

    interface IWcmEnumerator
    {
        CONST_VTBL struct IWcmEnumeratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWcmEnumerator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWcmEnumerator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWcmEnumerator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWcmEnumerator_Current(This,pDataObj)	\
    ( (This)->lpVtbl -> Current(This,pDataObj) ) 

#define IWcmEnumerator_MoveNext(This)	\
    ( (This)->lpVtbl -> MoveNext(This) ) 

#define IWcmEnumerator_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWcmEnumerator_Current_Proxy( 
    IWcmEnumerator * This,
    /* [in] */ IWcmData *pDataObj);


void __RPC_STUB IWcmEnumerator_Current_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmEnumerator_MoveNext_Proxy( 
    IWcmEnumerator * This);


void __RPC_STUB IWcmEnumerator_MoveNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmEnumerator_Reset_Proxy( 
    IWcmEnumerator * This);


void __RPC_STUB IWcmEnumerator_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWcmEnumerator_INTERFACE_DEFINED__ */


#ifndef __IWcmHandler_INTERFACE_DEFINED__
#define __IWcmHandler_INTERFACE_DEFINED__

/* interface IWcmHandler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWcmHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("733E4E50-3BA4-11D7-BF56-000874CD1BAE")
    IWcmHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [unique][string][in] */ const WCHAR *szLocation,
            /* [unique][in] */ IWcmHandler *pHandler,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [unique][in] */ IWcmHelper *pWsmHelper) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj,
            /* [unique][string][in] */ const WCHAR *szLegacyType,
            /* [unique][string][in] */ const WCHAR *szLegacyFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutValue( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj,
            /* [unique][string][in] */ const WCHAR *szLegacyType,
            /* [unique][string][in] */ const WCHAR *szLegacyFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteValue( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ wsmTimestamp timestamp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ wsmiiEnum wsmiiAttribute,
            /* [in] */ IWcmData *pDataObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSecurity( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSecurity( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEnumerator( 
            /* [in] */ WcmEnumOptions iOptions,
            /* [unique][string][in] */ const WCHAR *szFilter,
            /* [out] */ IWcmEnumerator **ppEnumerator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( 
            /* [in] */ UINT wsmcoOptions,
            /* [unique][in] */ IWcmData *pCommitInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateChild( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [out] */ IWcmHandler **ppChild) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetChild( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [out] */ IWcmHandler **ppChild) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteChild( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ wsmTimestamp timestamp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InsertChild( 
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [string][in] */ const WCHAR *szTarget,
            /* [in] */ BOOL fLocation,
            /* [out] */ IWcmHandler **ppChild) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveChild( 
            /* [string][in] */ const WCHAR *szItem,
            /* [string][in] */ const WCHAR *szTarget,
            /* [in] */ BOOL fLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CompareChildOrder( 
            /* [string][in] */ const WCHAR *szNode1,
            /* [string][in] */ const WCHAR *szNode2,
            /* [out] */ LONG *plOrder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWcmHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWcmHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWcmHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWcmHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IWcmHandler * This,
            /* [unique][string][in] */ const WCHAR *szLocation,
            /* [unique][in] */ IWcmHandler *pHandler,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [unique][in] */ IWcmHelper *pWsmHelper);
        
        HRESULT ( STDMETHODCALLTYPE *GetValue )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj,
            /* [unique][string][in] */ const WCHAR *szLegacyType,
            /* [unique][string][in] */ const WCHAR *szLegacyFormat);
        
        HRESULT ( STDMETHODCALLTYPE *PutValue )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj,
            /* [unique][string][in] */ const WCHAR *szLegacyType,
            /* [unique][string][in] */ const WCHAR *szLegacyFormat);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteValue )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ wsmTimestamp timestamp);
        
        HRESULT ( STDMETHODCALLTYPE *GetInfo )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ wsmiiEnum wsmiiAttribute,
            /* [in] */ IWcmData *pDataObj);
        
        HRESULT ( STDMETHODCALLTYPE *GetSecurity )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj);
        
        HRESULT ( STDMETHODCALLTYPE *SetSecurity )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ IWcmData *pDataObj);
        
        HRESULT ( STDMETHODCALLTYPE *GetEnumerator )( 
            IWcmHandler * This,
            /* [in] */ WcmEnumOptions iOptions,
            /* [unique][string][in] */ const WCHAR *szFilter,
            /* [out] */ IWcmEnumerator **ppEnumerator);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IWcmHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *Commit )( 
            IWcmHandler * This,
            /* [in] */ UINT wsmcoOptions,
            /* [unique][in] */ IWcmData *pCommitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *CreateChild )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [out] */ IWcmHandler **ppChild);
        
        HRESULT ( STDMETHODCALLTYPE *GetChild )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [out] */ IWcmHandler **ppChild);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteChild )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ wsmTimestamp timestamp);
        
        HRESULT ( STDMETHODCALLTYPE *InsertChild )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ UINT iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [in] */ UINT wsmhoOptions,
            /* [string][in] */ const WCHAR *szTarget,
            /* [in] */ BOOL fLocation,
            /* [out] */ IWcmHandler **ppChild);
        
        HRESULT ( STDMETHODCALLTYPE *MoveChild )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szItem,
            /* [string][in] */ const WCHAR *szTarget,
            /* [in] */ BOOL fLocation);
        
        HRESULT ( STDMETHODCALLTYPE *CompareChildOrder )( 
            IWcmHandler * This,
            /* [string][in] */ const WCHAR *szNode1,
            /* [string][in] */ const WCHAR *szNode2,
            /* [out] */ LONG *plOrder);
        
        END_INTERFACE
    } IWcmHandlerVtbl;

    interface IWcmHandler
    {
        CONST_VTBL struct IWcmHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWcmHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWcmHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWcmHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWcmHandler_Initialize(This,szLocation,pHandler,szItem,iType,szComplexType,wsmhoOptions,pWsmHelper)	\
    ( (This)->lpVtbl -> Initialize(This,szLocation,pHandler,szItem,iType,szComplexType,wsmhoOptions,pWsmHelper) ) 

#define IWcmHandler_GetValue(This,szItem,pDataObj,szLegacyType,szLegacyFormat)	\
    ( (This)->lpVtbl -> GetValue(This,szItem,pDataObj,szLegacyType,szLegacyFormat) ) 

#define IWcmHandler_PutValue(This,szItem,pDataObj,szLegacyType,szLegacyFormat)	\
    ( (This)->lpVtbl -> PutValue(This,szItem,pDataObj,szLegacyType,szLegacyFormat) ) 

#define IWcmHandler_DeleteValue(This,szItem,timestamp)	\
    ( (This)->lpVtbl -> DeleteValue(This,szItem,timestamp) ) 

#define IWcmHandler_GetInfo(This,szItem,wsmiiAttribute,pDataObj)	\
    ( (This)->lpVtbl -> GetInfo(This,szItem,wsmiiAttribute,pDataObj) ) 

#define IWcmHandler_GetSecurity(This,szItem,pDataObj)	\
    ( (This)->lpVtbl -> GetSecurity(This,szItem,pDataObj) ) 

#define IWcmHandler_SetSecurity(This,szItem,pDataObj)	\
    ( (This)->lpVtbl -> SetSecurity(This,szItem,pDataObj) ) 

#define IWcmHandler_GetEnumerator(This,iOptions,szFilter,ppEnumerator)	\
    ( (This)->lpVtbl -> GetEnumerator(This,iOptions,szFilter,ppEnumerator) ) 

#define IWcmHandler_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IWcmHandler_Commit(This,wsmcoOptions,pCommitInfo)	\
    ( (This)->lpVtbl -> Commit(This,wsmcoOptions,pCommitInfo) ) 

#define IWcmHandler_CreateChild(This,szItem,iType,szComplexType,wsmhoOptions,ppChild)	\
    ( (This)->lpVtbl -> CreateChild(This,szItem,iType,szComplexType,wsmhoOptions,ppChild) ) 

#define IWcmHandler_GetChild(This,szItem,iType,szComplexType,wsmhoOptions,ppChild)	\
    ( (This)->lpVtbl -> GetChild(This,szItem,iType,szComplexType,wsmhoOptions,ppChild) ) 

#define IWcmHandler_DeleteChild(This,szItem,iType,szComplexType,timestamp)	\
    ( (This)->lpVtbl -> DeleteChild(This,szItem,iType,szComplexType,timestamp) ) 

#define IWcmHandler_InsertChild(This,szItem,iType,szComplexType,wsmhoOptions,szTarget,fLocation,ppChild)	\
    ( (This)->lpVtbl -> InsertChild(This,szItem,iType,szComplexType,wsmhoOptions,szTarget,fLocation,ppChild) ) 

#define IWcmHandler_MoveChild(This,szItem,szTarget,fLocation)	\
    ( (This)->lpVtbl -> MoveChild(This,szItem,szTarget,fLocation) ) 

#define IWcmHandler_CompareChildOrder(This,szNode1,szNode2,plOrder)	\
    ( (This)->lpVtbl -> CompareChildOrder(This,szNode1,szNode2,plOrder) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWcmHandler_Initialize_Proxy( 
    IWcmHandler * This,
    /* [unique][string][in] */ const WCHAR *szLocation,
    /* [unique][in] */ IWcmHandler *pHandler,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ UINT iType,
    /* [unique][string][in] */ const WCHAR *szComplexType,
    /* [in] */ UINT wsmhoOptions,
    /* [unique][in] */ IWcmHelper *pWsmHelper);


void __RPC_STUB IWcmHandler_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_GetValue_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ IWcmData *pDataObj,
    /* [unique][string][in] */ const WCHAR *szLegacyType,
    /* [unique][string][in] */ const WCHAR *szLegacyFormat);


void __RPC_STUB IWcmHandler_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_PutValue_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ IWcmData *pDataObj,
    /* [unique][string][in] */ const WCHAR *szLegacyType,
    /* [unique][string][in] */ const WCHAR *szLegacyFormat);


void __RPC_STUB IWcmHandler_PutValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_DeleteValue_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ wsmTimestamp timestamp);


void __RPC_STUB IWcmHandler_DeleteValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_GetInfo_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ wsmiiEnum wsmiiAttribute,
    /* [in] */ IWcmData *pDataObj);


void __RPC_STUB IWcmHandler_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_GetSecurity_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ IWcmData *pDataObj);


void __RPC_STUB IWcmHandler_GetSecurity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_SetSecurity_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ IWcmData *pDataObj);


void __RPC_STUB IWcmHandler_SetSecurity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_GetEnumerator_Proxy( 
    IWcmHandler * This,
    /* [in] */ WcmEnumOptions iOptions,
    /* [unique][string][in] */ const WCHAR *szFilter,
    /* [out] */ IWcmEnumerator **ppEnumerator);


void __RPC_STUB IWcmHandler_GetEnumerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_Reset_Proxy( 
    IWcmHandler * This);


void __RPC_STUB IWcmHandler_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_Commit_Proxy( 
    IWcmHandler * This,
    /* [in] */ UINT wsmcoOptions,
    /* [unique][in] */ IWcmData *pCommitInfo);


void __RPC_STUB IWcmHandler_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_CreateChild_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ UINT iType,
    /* [unique][string][in] */ const WCHAR *szComplexType,
    /* [in] */ UINT wsmhoOptions,
    /* [out] */ IWcmHandler **ppChild);


void __RPC_STUB IWcmHandler_CreateChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_GetChild_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ UINT iType,
    /* [unique][string][in] */ const WCHAR *szComplexType,
    /* [in] */ UINT wsmhoOptions,
    /* [out] */ IWcmHandler **ppChild);


void __RPC_STUB IWcmHandler_GetChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_DeleteChild_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ UINT iType,
    /* [unique][string][in] */ const WCHAR *szComplexType,
    /* [in] */ wsmTimestamp timestamp);


void __RPC_STUB IWcmHandler_DeleteChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_InsertChild_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ UINT iType,
    /* [unique][string][in] */ const WCHAR *szComplexType,
    /* [in] */ UINT wsmhoOptions,
    /* [string][in] */ const WCHAR *szTarget,
    /* [in] */ BOOL fLocation,
    /* [out] */ IWcmHandler **ppChild);


void __RPC_STUB IWcmHandler_InsertChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_MoveChild_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szItem,
    /* [string][in] */ const WCHAR *szTarget,
    /* [in] */ BOOL fLocation);


void __RPC_STUB IWcmHandler_MoveChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHandler_CompareChildOrder_Proxy( 
    IWcmHandler * This,
    /* [string][in] */ const WCHAR *szNode1,
    /* [string][in] */ const WCHAR *szNode2,
    /* [out] */ LONG *plOrder);


void __RPC_STUB IWcmHandler_CompareChildOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWcmHandler_INTERFACE_DEFINED__ */


#ifndef __IWcmHelper_INTERFACE_DEFINED__
#define __IWcmHelper_INTERFACE_DEFINED__

/* interface IWcmHelper */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWcmHelper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("733E4E51-3BA4-11D7-BF56-000874CD1BAE")
    IWcmHelper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StringToValue( 
            /* [string][in] */ const WCHAR *szFromString,
            /* [in] */ ULONG iToType,
            /* [in] */ ULONG iOptions,
            /* [out] */ ULONG *piValueSize,
            /* [size_is][size_is][out] */ BYTE **ppbValueData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ExtractKeys( 
            /* [string][in] */ const WCHAR *szXpathExpression,
            /* [out] */ USHORT *piKeyCount,
            /* [size_is][size_is][out] */ USHORT **ppiKeyInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EscapeString( 
            /* [string][in] */ const WCHAR *szFromString,
            /* [out] */ BSTR *pbstrToString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnescapeString( 
            /* [string][in] */ const WCHAR *szFromString,
            /* [out] */ BSTR *pbstrToString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateRootHandler( 
            /* [string][in] */ const WCHAR *szHandler,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ ULONG iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [out] */ IWcmHandler **ppHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateWsmData( 
            /* [out] */ IWcmData **ppWsmData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EncodePath( 
            /* [string][in] */ const WCHAR *szPath,
            /* [out] */ BSTR *pbstrEncodedPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DecodePath( 
            /* [string][in] */ const WCHAR *szPath,
            /* [out] */ BSTR *pbstrDecodedPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetXmlNamespace( 
            /* [string][in] */ const WCHAR *szNamespacePrefix,
            /* [out] */ BSTR *pbstrNamespaceUri) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetXmlNamepsacePrefix( 
            /* [string][in] */ const WCHAR *szNamespaceUri,
            /* [out] */ BSTR *pbstrNamespacePrefix) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWcmHelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWcmHelper * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWcmHelper * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWcmHelper * This);
        
        HRESULT ( STDMETHODCALLTYPE *StringToValue )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szFromString,
            /* [in] */ ULONG iToType,
            /* [in] */ ULONG iOptions,
            /* [out] */ ULONG *piValueSize,
            /* [size_is][size_is][out] */ BYTE **ppbValueData);
        
        HRESULT ( STDMETHODCALLTYPE *ExtractKeys )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szXpathExpression,
            /* [out] */ USHORT *piKeyCount,
            /* [size_is][size_is][out] */ USHORT **ppiKeyInfo);
        
        HRESULT ( STDMETHODCALLTYPE *EscapeString )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szFromString,
            /* [out] */ BSTR *pbstrToString);
        
        HRESULT ( STDMETHODCALLTYPE *UnescapeString )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szFromString,
            /* [out] */ BSTR *pbstrToString);
        
        HRESULT ( STDMETHODCALLTYPE *CreateRootHandler )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szHandler,
            /* [string][in] */ const WCHAR *szItem,
            /* [in] */ ULONG iType,
            /* [unique][string][in] */ const WCHAR *szComplexType,
            /* [out] */ IWcmHandler **ppHandler);
        
        HRESULT ( STDMETHODCALLTYPE *CreateWsmData )( 
            IWcmHelper * This,
            /* [out] */ IWcmData **ppWsmData);
        
        HRESULT ( STDMETHODCALLTYPE *EncodePath )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szPath,
            /* [out] */ BSTR *pbstrEncodedPath);
        
        HRESULT ( STDMETHODCALLTYPE *DecodePath )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szPath,
            /* [out] */ BSTR *pbstrDecodedPath);
        
        HRESULT ( STDMETHODCALLTYPE *GetXmlNamespace )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szNamespacePrefix,
            /* [out] */ BSTR *pbstrNamespaceUri);
        
        HRESULT ( STDMETHODCALLTYPE *GetXmlNamepsacePrefix )( 
            IWcmHelper * This,
            /* [string][in] */ const WCHAR *szNamespaceUri,
            /* [out] */ BSTR *pbstrNamespacePrefix);
        
        END_INTERFACE
    } IWcmHelperVtbl;

    interface IWcmHelper
    {
        CONST_VTBL struct IWcmHelperVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWcmHelper_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWcmHelper_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWcmHelper_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWcmHelper_StringToValue(This,szFromString,iToType,iOptions,piValueSize,ppbValueData)	\
    ( (This)->lpVtbl -> StringToValue(This,szFromString,iToType,iOptions,piValueSize,ppbValueData) ) 

#define IWcmHelper_ExtractKeys(This,szXpathExpression,piKeyCount,ppiKeyInfo)	\
    ( (This)->lpVtbl -> ExtractKeys(This,szXpathExpression,piKeyCount,ppiKeyInfo) ) 

#define IWcmHelper_EscapeString(This,szFromString,pbstrToString)	\
    ( (This)->lpVtbl -> EscapeString(This,szFromString,pbstrToString) ) 

#define IWcmHelper_UnescapeString(This,szFromString,pbstrToString)	\
    ( (This)->lpVtbl -> UnescapeString(This,szFromString,pbstrToString) ) 

#define IWcmHelper_CreateRootHandler(This,szHandler,szItem,iType,szComplexType,ppHandler)	\
    ( (This)->lpVtbl -> CreateRootHandler(This,szHandler,szItem,iType,szComplexType,ppHandler) ) 

#define IWcmHelper_CreateWsmData(This,ppWsmData)	\
    ( (This)->lpVtbl -> CreateWsmData(This,ppWsmData) ) 

#define IWcmHelper_EncodePath(This,szPath,pbstrEncodedPath)	\
    ( (This)->lpVtbl -> EncodePath(This,szPath,pbstrEncodedPath) ) 

#define IWcmHelper_DecodePath(This,szPath,pbstrDecodedPath)	\
    ( (This)->lpVtbl -> DecodePath(This,szPath,pbstrDecodedPath) ) 

#define IWcmHelper_GetXmlNamespace(This,szNamespacePrefix,pbstrNamespaceUri)	\
    ( (This)->lpVtbl -> GetXmlNamespace(This,szNamespacePrefix,pbstrNamespaceUri) ) 

#define IWcmHelper_GetXmlNamepsacePrefix(This,szNamespaceUri,pbstrNamespacePrefix)	\
    ( (This)->lpVtbl -> GetXmlNamepsacePrefix(This,szNamespaceUri,pbstrNamespacePrefix) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWcmHelper_StringToValue_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szFromString,
    /* [in] */ ULONG iToType,
    /* [in] */ ULONG iOptions,
    /* [out] */ ULONG *piValueSize,
    /* [size_is][size_is][out] */ BYTE **ppbValueData);


void __RPC_STUB IWcmHelper_StringToValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_ExtractKeys_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szXpathExpression,
    /* [out] */ USHORT *piKeyCount,
    /* [size_is][size_is][out] */ USHORT **ppiKeyInfo);


void __RPC_STUB IWcmHelper_ExtractKeys_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_EscapeString_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szFromString,
    /* [out] */ BSTR *pbstrToString);


void __RPC_STUB IWcmHelper_EscapeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_UnescapeString_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szFromString,
    /* [out] */ BSTR *pbstrToString);


void __RPC_STUB IWcmHelper_UnescapeString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_CreateRootHandler_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szHandler,
    /* [string][in] */ const WCHAR *szItem,
    /* [in] */ ULONG iType,
    /* [unique][string][in] */ const WCHAR *szComplexType,
    /* [out] */ IWcmHandler **ppHandler);


void __RPC_STUB IWcmHelper_CreateRootHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_CreateWsmData_Proxy( 
    IWcmHelper * This,
    /* [out] */ IWcmData **ppWsmData);


void __RPC_STUB IWcmHelper_CreateWsmData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_EncodePath_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szPath,
    /* [out] */ BSTR *pbstrEncodedPath);


void __RPC_STUB IWcmHelper_EncodePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_DecodePath_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szPath,
    /* [out] */ BSTR *pbstrDecodedPath);


void __RPC_STUB IWcmHelper_DecodePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_GetXmlNamespace_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szNamespacePrefix,
    /* [out] */ BSTR *pbstrNamespaceUri);


void __RPC_STUB IWcmHelper_GetXmlNamespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWcmHelper_GetXmlNamepsacePrefix_Proxy( 
    IWcmHelper * This,
    /* [string][in] */ const WCHAR *szNamespaceUri,
    /* [out] */ BSTR *pbstrNamespacePrefix);


void __RPC_STUB IWcmHelper_GetXmlNamepsacePrefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWcmHelper_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


