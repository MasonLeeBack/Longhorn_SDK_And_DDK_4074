

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for mobsync.idl:
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

#ifndef __mobsync_h__
#define __mobsync_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISyncMgrSynchronizeCallback_FWD_DEFINED__
#define __ISyncMgrSynchronizeCallback_FWD_DEFINED__
typedef interface ISyncMgrSynchronizeCallback ISyncMgrSynchronizeCallback;
#endif 	/* __ISyncMgrSynchronizeCallback_FWD_DEFINED__ */


#ifndef __ISyncMgrEnumItems_FWD_DEFINED__
#define __ISyncMgrEnumItems_FWD_DEFINED__
typedef interface ISyncMgrEnumItems ISyncMgrEnumItems;
#endif 	/* __ISyncMgrEnumItems_FWD_DEFINED__ */


#ifndef __ISyncMgrSynchronize_FWD_DEFINED__
#define __ISyncMgrSynchronize_FWD_DEFINED__
typedef interface ISyncMgrSynchronize ISyncMgrSynchronize;
#endif 	/* __ISyncMgrSynchronize_FWD_DEFINED__ */


#ifndef __ISyncMgrSynchronizeInvoke_FWD_DEFINED__
#define __ISyncMgrSynchronizeInvoke_FWD_DEFINED__
typedef interface ISyncMgrSynchronizeInvoke ISyncMgrSynchronizeInvoke;
#endif 	/* __ISyncMgrSynchronizeInvoke_FWD_DEFINED__ */


#ifndef __ISyncMgrRegister_FWD_DEFINED__
#define __ISyncMgrRegister_FWD_DEFINED__
typedef interface ISyncMgrRegister ISyncMgrRegister;
#endif 	/* __ISyncMgrRegister_FWD_DEFINED__ */


#ifndef __ISyncMgrConflictItem_FWD_DEFINED__
#define __ISyncMgrConflictItem_FWD_DEFINED__
typedef interface ISyncMgrConflictItem ISyncMgrConflictItem;
#endif 	/* __ISyncMgrConflictItem_FWD_DEFINED__ */


#ifndef __IEnumSyncMgrConflictItem_FWD_DEFINED__
#define __IEnumSyncMgrConflictItem_FWD_DEFINED__
typedef interface IEnumSyncMgrConflictItem IEnumSyncMgrConflictItem;
#endif 	/* __IEnumSyncMgrConflictItem_FWD_DEFINED__ */


#ifndef __ISyncMgrConflictShellItem_FWD_DEFINED__
#define __ISyncMgrConflictShellItem_FWD_DEFINED__
typedef interface ISyncMgrConflictShellItem ISyncMgrConflictShellItem;
#endif 	/* __ISyncMgrConflictShellItem_FWD_DEFINED__ */


#ifndef __ISyncMgrConflictCategory_FWD_DEFINED__
#define __ISyncMgrConflictCategory_FWD_DEFINED__
typedef interface ISyncMgrConflictCategory ISyncMgrConflictCategory;
#endif 	/* __ISyncMgrConflictCategory_FWD_DEFINED__ */


#ifndef __ISyncMgrConflict_FWD_DEFINED__
#define __ISyncMgrConflict_FWD_DEFINED__
typedef interface ISyncMgrConflict ISyncMgrConflict;
#endif 	/* __ISyncMgrConflict_FWD_DEFINED__ */


#ifndef __IEnumSyncMgrConflict_FWD_DEFINED__
#define __IEnumSyncMgrConflict_FWD_DEFINED__
typedef interface IEnumSyncMgrConflict IEnumSyncMgrConflict;
#endif 	/* __IEnumSyncMgrConflict_FWD_DEFINED__ */


#ifndef __ISyncMgrConflictStore_FWD_DEFINED__
#define __ISyncMgrConflictStore_FWD_DEFINED__
typedef interface ISyncMgrConflictStore ISyncMgrConflictStore;
#endif 	/* __ISyncMgrConflictStore_FWD_DEFINED__ */


#ifndef __SyncMgr_FWD_DEFINED__
#define __SyncMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class SyncMgr SyncMgr;
#else
typedef struct SyncMgr SyncMgr;
#endif /* __cplusplus */

#endif 	/* __SyncMgr_FWD_DEFINED__ */


#ifndef __ConflictFolder_FWD_DEFINED__
#define __ConflictFolder_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConflictFolder ConflictFolder;
#else
typedef struct ConflictFolder ConflictFolder;
#endif /* __cplusplus */

#endif 	/* __ConflictFolder_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_mobsync_0000 */
/* [local] */ 

#define SYNCMGRITEMID        GUID
#define REFSYNCMGRITEMID     REFGUID
#define SYNCMGRERRORID       GUID
#define REFSYNCMGRERRORID    REFGUID

#define S_SYNCMGR_MISSINGITEMS       MAKE_SCODE(SEVERITY_SUCCESS,FACILITY_ITF,0x0201)
#define S_SYNCMGR_RETRYSYNC          MAKE_SCODE(SEVERITY_SUCCESS,FACILITY_ITF,0x0202)
#define S_SYNCMGR_CANCELITEM         MAKE_SCODE(SEVERITY_SUCCESS,FACILITY_ITF,0x0203)
#define S_SYNCMGR_CANCELALL          MAKE_SCODE(SEVERITY_SUCCESS,FACILITY_ITF,0x0204)
#define S_SYNCMGR_ITEMDELETED        MAKE_SCODE(SEVERITY_SUCCESS,FACILITY_ITF,0x0210)
#define S_SYNCMGR_ENUMITEMS          MAKE_SCODE(SEVERITY_SUCCESS,FACILITY_ITF,0x0211)


extern RPC_IF_HANDLE __MIDL_itf_mobsync_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mobsync_0000_v0_0_s_ifspec;

#ifndef __ISyncMgrSynchronizeCallback_INTERFACE_DEFINED__
#define __ISyncMgrSynchronizeCallback_INTERFACE_DEFINED__

/* interface ISyncMgrSynchronizeCallback */
/* [uuid][object] */ 

typedef /* [unique] */ ISyncMgrSynchronizeCallback *LPSYNCMGRSYNCHRONIZECALLBACK;

#define   SYNCMGRPROGRESSITEM_STATUSTEXT         0x0001
#define   SYNCMGRPROGRESSITEM_STATUSTYPE         0x0002
#define   SYNCMGRPROGRESSITEM_PROGVALUE          0x0004
#define   SYNCMGRPROGRESSITEM_MAXVALUE           0x0008
typedef /* [v1_enum] */ 
enum _tagSYNCMGRSTATUS
    {	SYNCMGRSTATUS_STOPPED	= 0,
	SYNCMGRSTATUS_SKIPPED	= 0x1,
	SYNCMGRSTATUS_PENDING	= 0x2,
	SYNCMGRSTATUS_UPDATING	= 0x3,
	SYNCMGRSTATUS_SUCCEEDED	= 0x4,
	SYNCMGRSTATUS_FAILED	= 0x5,
	SYNCMGRSTATUS_PAUSED	= 0x6,
	SYNCMGRSTATUS_RESUMING	= 0x7,
	SYNCMGRSTATUS_DELETED	= 0x100
    } 	SYNCMGRSTATUS;

typedef struct _tagSYNCMGRPROGRESSITEM
    {
    DWORD cbSize;
    UINT mask;
    LPCWSTR lpcStatusText;
    DWORD dwStatusType;
    int iProgValue;
    int iMaxValue;
    } 	SYNCMGRPROGRESSITEM;

typedef struct _tagSYNCMGRPROGRESSITEM *LPSYNCMGRPROGRESSITEM;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRLOGLEVEL
    {	SYNCMGRLOGLEVEL_INFORMATION	= 0x1,
	SYNCMGRLOGLEVEL_WARNING	= 0x2,
	SYNCMGRLOGLEVEL_ERROR	= 0x3
    } 	SYNCMGRLOGLEVEL;

#define   SYNCMGRLOGERROR_ERRORFLAGS                     0x0001
#define   SYNCMGRLOGERROR_ERRORID                        0x0002
#define   SYNCMGRLOGERROR_ITEMID                         0x0004
typedef /* [v1_enum] */ 
enum _tagSYNCMGRERRORFLAGS
    {	SYNCMGRERRORFLAG_ENABLEJUMPTEXT	= 0x1
    } 	SYNCMGRERRORFLAGS;

typedef struct _tagSYNCMGRLOGERRORINFO
    {
    DWORD cbSize;
    DWORD mask;
    DWORD dwSyncMgrErrorFlags;
    GUID ErrorID;
    GUID ItemID;
    } 	SYNCMGRLOGERRORINFO;

typedef struct _tagSYNCMGRLOGERRORINFO *LPSYNCMGRLOGERRORINFO;


EXTERN_C const IID IID_ISyncMgrSynchronizeCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6295DF41-35EE-11d1-8707-00C04FD93327")
    ISyncMgrSynchronizeCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShowPropertiesCompleted( 
            /* [in] */ HRESULT hr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrepareForSyncCompleted( 
            /* [in] */ HRESULT hr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SynchronizeCompleted( 
            /* [in] */ HRESULT hr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowErrorCompleted( 
            /* [in] */ HRESULT hr,
            /* [in] */ ULONG cbNumItems,
            /* [size_is][unique][in] */ GUID *pItemIDs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Progress( 
            /* [in] */ REFGUID pItemID,
            /* [unique][in] */ LPSYNCMGRPROGRESSITEM lpSyncProgressItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LogError( 
            /* [in] */ DWORD dwErrorLevel,
            /* [in] */ LPCWSTR lpcErrorText,
            /* [unique][in] */ LPSYNCMGRLOGERRORINFO lpSyncLogError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteLogError( 
            /* [in] */ REFGUID ErrorID,
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EstablishConnection( 
            /* [unique][in] */ LPCWSTR lpwszConnection,
            /* [in] */ DWORD dwReserved) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrSynchronizeCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrSynchronizeCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrSynchronizeCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *ShowPropertiesCompleted )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE *PrepareForSyncCompleted )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE *SynchronizeCompleted )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE *ShowErrorCompleted )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ HRESULT hr,
            /* [in] */ ULONG cbNumItems,
            /* [size_is][unique][in] */ GUID *pItemIDs);
        
        HRESULT ( STDMETHODCALLTYPE *EnableModeless )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE *Progress )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ REFGUID pItemID,
            /* [unique][in] */ LPSYNCMGRPROGRESSITEM lpSyncProgressItem);
        
        HRESULT ( STDMETHODCALLTYPE *LogError )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ DWORD dwErrorLevel,
            /* [in] */ LPCWSTR lpcErrorText,
            /* [unique][in] */ LPSYNCMGRLOGERRORINFO lpSyncLogError);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteLogError )( 
            ISyncMgrSynchronizeCallback * This,
            /* [in] */ REFGUID ErrorID,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *EstablishConnection )( 
            ISyncMgrSynchronizeCallback * This,
            /* [unique][in] */ LPCWSTR lpwszConnection,
            /* [in] */ DWORD dwReserved);
        
        END_INTERFACE
    } ISyncMgrSynchronizeCallbackVtbl;

    interface ISyncMgrSynchronizeCallback
    {
        CONST_VTBL struct ISyncMgrSynchronizeCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrSynchronizeCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrSynchronizeCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrSynchronizeCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrSynchronizeCallback_ShowPropertiesCompleted(This,hr)	\
    ( (This)->lpVtbl -> ShowPropertiesCompleted(This,hr) ) 

#define ISyncMgrSynchronizeCallback_PrepareForSyncCompleted(This,hr)	\
    ( (This)->lpVtbl -> PrepareForSyncCompleted(This,hr) ) 

#define ISyncMgrSynchronizeCallback_SynchronizeCompleted(This,hr)	\
    ( (This)->lpVtbl -> SynchronizeCompleted(This,hr) ) 

#define ISyncMgrSynchronizeCallback_ShowErrorCompleted(This,hr,cbNumItems,pItemIDs)	\
    ( (This)->lpVtbl -> ShowErrorCompleted(This,hr,cbNumItems,pItemIDs) ) 

#define ISyncMgrSynchronizeCallback_EnableModeless(This,fEnable)	\
    ( (This)->lpVtbl -> EnableModeless(This,fEnable) ) 

#define ISyncMgrSynchronizeCallback_Progress(This,pItemID,lpSyncProgressItem)	\
    ( (This)->lpVtbl -> Progress(This,pItemID,lpSyncProgressItem) ) 

#define ISyncMgrSynchronizeCallback_LogError(This,dwErrorLevel,lpcErrorText,lpSyncLogError)	\
    ( (This)->lpVtbl -> LogError(This,dwErrorLevel,lpcErrorText,lpSyncLogError) ) 

#define ISyncMgrSynchronizeCallback_DeleteLogError(This,ErrorID,dwReserved)	\
    ( (This)->lpVtbl -> DeleteLogError(This,ErrorID,dwReserved) ) 

#define ISyncMgrSynchronizeCallback_EstablishConnection(This,lpwszConnection,dwReserved)	\
    ( (This)->lpVtbl -> EstablishConnection(This,lpwszConnection,dwReserved) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_ShowPropertiesCompleted_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ HRESULT hr);


void __RPC_STUB ISyncMgrSynchronizeCallback_ShowPropertiesCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_PrepareForSyncCompleted_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ HRESULT hr);


void __RPC_STUB ISyncMgrSynchronizeCallback_PrepareForSyncCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_SynchronizeCompleted_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ HRESULT hr);


void __RPC_STUB ISyncMgrSynchronizeCallback_SynchronizeCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_ShowErrorCompleted_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ HRESULT hr,
    /* [in] */ ULONG cbNumItems,
    /* [size_is][unique][in] */ GUID *pItemIDs);


void __RPC_STUB ISyncMgrSynchronizeCallback_ShowErrorCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_EnableModeless_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB ISyncMgrSynchronizeCallback_EnableModeless_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_Progress_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ REFGUID pItemID,
    /* [unique][in] */ LPSYNCMGRPROGRESSITEM lpSyncProgressItem);


void __RPC_STUB ISyncMgrSynchronizeCallback_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_LogError_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ DWORD dwErrorLevel,
    /* [in] */ LPCWSTR lpcErrorText,
    /* [unique][in] */ LPSYNCMGRLOGERRORINFO lpSyncLogError);


void __RPC_STUB ISyncMgrSynchronizeCallback_LogError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_DeleteLogError_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [in] */ REFGUID ErrorID,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB ISyncMgrSynchronizeCallback_DeleteLogError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeCallback_EstablishConnection_Proxy( 
    ISyncMgrSynchronizeCallback * This,
    /* [unique][in] */ LPCWSTR lpwszConnection,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB ISyncMgrSynchronizeCallback_EstablishConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrSynchronizeCallback_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrEnumItems_INTERFACE_DEFINED__
#define __ISyncMgrEnumItems_INTERFACE_DEFINED__

/* interface ISyncMgrEnumItems */
/* [unique][uuid][object] */ 

typedef /* [unique] */ ISyncMgrEnumItems *LPSYNCMGRENUMITEMS;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRITEMFLAGS
    {	SYNCMGRITEM_HASPROPERTIES	= 0x1,
	SYNCMGRITEM_TEMPORARY	= 0x2,
	SYNCMGRITEM_ROAMINGUSER	= 0x4,
	SYNCMGRITEM_LASTUPDATETIME	= 0x8,
	SYNCMGRITEM_MAYDELETEITEM	= 0x10,
	SYNCMGRITEM_HIDDEN	= 0x20,
	SYNCMGRITEM_MARQUEEPROGRESS	= 0x40
    } 	SYNCMGRITEMFLAGS;

#define SYNCMGRITEM_ITEMFLAGMASK  0x007F
#define	MAX_SYNCMGRITEMNAME	( 128 )

typedef struct _tagSYNCMGRITEM
    {
    DWORD cbSize;
    DWORD dwFlags;
    GUID ItemID;
    DWORD dwItemState;
    HICON hIcon;
    WCHAR wszItemName[ 128 ];
    FILETIME ftLastUpdate;
    } 	SYNCMGRITEM;

typedef struct _tagSYNCMGRITEM *LPSYNCMGRITEM;


EXTERN_C const IID IID_ISyncMgrEnumItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6295DF2A-35EE-11d1-8707-00C04FD93327")
    ISyncMgrEnumItems : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ LPSYNCMGRITEM rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ISyncMgrEnumItems **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrEnumItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrEnumItems * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrEnumItems * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrEnumItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            ISyncMgrEnumItems * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ LPSYNCMGRITEM rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ISyncMgrEnumItems * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ISyncMgrEnumItems * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISyncMgrEnumItems * This,
            /* [out] */ ISyncMgrEnumItems **ppenum);
        
        END_INTERFACE
    } ISyncMgrEnumItemsVtbl;

    interface ISyncMgrEnumItems
    {
        CONST_VTBL struct ISyncMgrEnumItemsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrEnumItems_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrEnumItems_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrEnumItems_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrEnumItems_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ISyncMgrEnumItems_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define ISyncMgrEnumItems_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ISyncMgrEnumItems_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrEnumItems_Next_Proxy( 
    ISyncMgrEnumItems * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ LPSYNCMGRITEM rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB ISyncMgrEnumItems_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrEnumItems_Skip_Proxy( 
    ISyncMgrEnumItems * This,
    /* [in] */ ULONG celt);


void __RPC_STUB ISyncMgrEnumItems_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrEnumItems_Reset_Proxy( 
    ISyncMgrEnumItems * This);


void __RPC_STUB ISyncMgrEnumItems_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrEnumItems_Clone_Proxy( 
    ISyncMgrEnumItems * This,
    /* [out] */ ISyncMgrEnumItems **ppenum);


void __RPC_STUB ISyncMgrEnumItems_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrEnumItems_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrSynchronize_INTERFACE_DEFINED__
#define __ISyncMgrSynchronize_INTERFACE_DEFINED__

/* interface ISyncMgrSynchronize */
/* [uuid][object] */ 

typedef /* [unique] */ ISyncMgrSynchronize *LPSYNCMGRSYNCHRONIZE;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRFLAG
    {	SYNCMGRFLAG_CONNECT	= 0x1,
	SYNCMGRFLAG_PENDINGDISCONNECT	= 0x2,
	SYNCMGRFLAG_MANUAL	= 0x3,
	SYNCMGRFLAG_IDLE	= 0x4,
	SYNCMGRFLAG_INVOKE	= 0x5,
	SYNCMGRFLAG_SCHEDULED	= 0x6,
	SYNCMGRFLAG_EVENTMASK	= 0xff,
	SYNCMGRFLAG_SETTINGS	= 0x100,
	SYNCMGRFLAG_MAYBOTHERUSER	= 0x200
    } 	SYNCMGRFLAG;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRHANDLERFLAGS
    {	SYNCMGRHANDLER_HASPROPERTIES	= 0x1,
	SYNCMGRHANDLER_MAYESTABLISHCONNECTION	= 0x2,
	SYNCMGRHANDLER_ALWAYSLISTHANDLER	= 0x4,
	SYNCMGRHANDLER_METAHANDLER	= 0x10,
	SYNCMGRHANDLER_HIDDEN	= 0x20
    } 	SYNCMGRHANDLERFLAGS;

#define SYNCMGRHANDLERFLAG_MASK 0x003f
#define	MAX_SYNCMGRHANDLERNAME	( 32 )

typedef struct _tagSYNCMGRHANDLERINFO
    {
    DWORD cbSize;
    HICON hIcon;
    DWORD SyncMgrHandlerFlags;
    WCHAR wszHandlerName[ 32 ];
    } 	SYNCMGRHANDLERINFO;

typedef struct _tagSYNCMGRHANDLERINFO *LPSYNCMGRHANDLERINFO;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRITEMSTATE
    {	SYNCMGRITEMSTATE_UNCHECKED	= 0,
	SYNCMGRITEMSTATE_CHECKED	= 0x1
    } 	SYNCMGRITEMSTATE;


EXTERN_C const IID IID_ISyncMgrSynchronize;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6295DF40-35EE-11d1-8707-00C04FD93327")
    ISyncMgrSynchronize : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ DWORD dwReserved,
            /* [in] */ DWORD dwSyncMgrFlags,
            /* [in] */ DWORD cbCookie,
            /* [size_is][unique][in] */ const BYTE *lpCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHandlerInfo( 
            /* [out] */ LPSYNCMGRHANDLERINFO *ppSyncMgrHandlerInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumSyncMgrItems( 
            /* [out] */ ISyncMgrEnumItems **ppSyncMgrEnumItems) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemObject( 
            /* [in] */ REFGUID ItemID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowProperties( 
            /* [in] */ HWND hWndParent,
            /* [in] */ REFGUID ItemID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProgressCallback( 
            /* [unique][in] */ ISyncMgrSynchronizeCallback *lpCallBack) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PrepareForSync( 
            /* [in] */ ULONG cbNumItems,
            /* [size_is][in] */ GUID *pItemIDs,
            /* [in] */ HWND hWndParent,
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Synchronize( 
            /* [in] */ HWND hWndParent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetItemStatus( 
            /* [in] */ REFGUID pItemID,
            /* [in] */ DWORD dwSyncMgrStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowError( 
            /* [in] */ HWND hWndParent,
            /* [in] */ REFGUID ErrorID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrSynchronizeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrSynchronize * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrSynchronize * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrSynchronize * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            ISyncMgrSynchronize * This,
            /* [in] */ DWORD dwReserved,
            /* [in] */ DWORD dwSyncMgrFlags,
            /* [in] */ DWORD cbCookie,
            /* [size_is][unique][in] */ const BYTE *lpCookie);
        
        HRESULT ( STDMETHODCALLTYPE *GetHandlerInfo )( 
            ISyncMgrSynchronize * This,
            /* [out] */ LPSYNCMGRHANDLERINFO *ppSyncMgrHandlerInfo);
        
        HRESULT ( STDMETHODCALLTYPE *EnumSyncMgrItems )( 
            ISyncMgrSynchronize * This,
            /* [out] */ ISyncMgrEnumItems **ppSyncMgrEnumItems);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemObject )( 
            ISyncMgrSynchronize * This,
            /* [in] */ REFGUID ItemID,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *ShowProperties )( 
            ISyncMgrSynchronize * This,
            /* [in] */ HWND hWndParent,
            /* [in] */ REFGUID ItemID);
        
        HRESULT ( STDMETHODCALLTYPE *SetProgressCallback )( 
            ISyncMgrSynchronize * This,
            /* [unique][in] */ ISyncMgrSynchronizeCallback *lpCallBack);
        
        HRESULT ( STDMETHODCALLTYPE *PrepareForSync )( 
            ISyncMgrSynchronize * This,
            /* [in] */ ULONG cbNumItems,
            /* [size_is][in] */ GUID *pItemIDs,
            /* [in] */ HWND hWndParent,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *Synchronize )( 
            ISyncMgrSynchronize * This,
            /* [in] */ HWND hWndParent);
        
        HRESULT ( STDMETHODCALLTYPE *SetItemStatus )( 
            ISyncMgrSynchronize * This,
            /* [in] */ REFGUID pItemID,
            /* [in] */ DWORD dwSyncMgrStatus);
        
        HRESULT ( STDMETHODCALLTYPE *ShowError )( 
            ISyncMgrSynchronize * This,
            /* [in] */ HWND hWndParent,
            /* [in] */ REFGUID ErrorID);
        
        END_INTERFACE
    } ISyncMgrSynchronizeVtbl;

    interface ISyncMgrSynchronize
    {
        CONST_VTBL struct ISyncMgrSynchronizeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrSynchronize_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrSynchronize_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrSynchronize_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrSynchronize_Initialize(This,dwReserved,dwSyncMgrFlags,cbCookie,lpCookie)	\
    ( (This)->lpVtbl -> Initialize(This,dwReserved,dwSyncMgrFlags,cbCookie,lpCookie) ) 

#define ISyncMgrSynchronize_GetHandlerInfo(This,ppSyncMgrHandlerInfo)	\
    ( (This)->lpVtbl -> GetHandlerInfo(This,ppSyncMgrHandlerInfo) ) 

#define ISyncMgrSynchronize_EnumSyncMgrItems(This,ppSyncMgrEnumItems)	\
    ( (This)->lpVtbl -> EnumSyncMgrItems(This,ppSyncMgrEnumItems) ) 

#define ISyncMgrSynchronize_GetItemObject(This,ItemID,riid,ppv)	\
    ( (This)->lpVtbl -> GetItemObject(This,ItemID,riid,ppv) ) 

#define ISyncMgrSynchronize_ShowProperties(This,hWndParent,ItemID)	\
    ( (This)->lpVtbl -> ShowProperties(This,hWndParent,ItemID) ) 

#define ISyncMgrSynchronize_SetProgressCallback(This,lpCallBack)	\
    ( (This)->lpVtbl -> SetProgressCallback(This,lpCallBack) ) 

#define ISyncMgrSynchronize_PrepareForSync(This,cbNumItems,pItemIDs,hWndParent,dwReserved)	\
    ( (This)->lpVtbl -> PrepareForSync(This,cbNumItems,pItemIDs,hWndParent,dwReserved) ) 

#define ISyncMgrSynchronize_Synchronize(This,hWndParent)	\
    ( (This)->lpVtbl -> Synchronize(This,hWndParent) ) 

#define ISyncMgrSynchronize_SetItemStatus(This,pItemID,dwSyncMgrStatus)	\
    ( (This)->lpVtbl -> SetItemStatus(This,pItemID,dwSyncMgrStatus) ) 

#define ISyncMgrSynchronize_ShowError(This,hWndParent,ErrorID)	\
    ( (This)->lpVtbl -> ShowError(This,hWndParent,ErrorID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_Initialize_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ DWORD dwReserved,
    /* [in] */ DWORD dwSyncMgrFlags,
    /* [in] */ DWORD cbCookie,
    /* [size_is][unique][in] */ const BYTE *lpCookie);


void __RPC_STUB ISyncMgrSynchronize_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_GetHandlerInfo_Proxy( 
    ISyncMgrSynchronize * This,
    /* [out] */ LPSYNCMGRHANDLERINFO *ppSyncMgrHandlerInfo);


void __RPC_STUB ISyncMgrSynchronize_GetHandlerInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_EnumSyncMgrItems_Proxy( 
    ISyncMgrSynchronize * This,
    /* [out] */ ISyncMgrEnumItems **ppSyncMgrEnumItems);


void __RPC_STUB ISyncMgrSynchronize_EnumSyncMgrItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_GetItemObject_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ REFGUID ItemID,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB ISyncMgrSynchronize_GetItemObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_ShowProperties_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ HWND hWndParent,
    /* [in] */ REFGUID ItemID);


void __RPC_STUB ISyncMgrSynchronize_ShowProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_SetProgressCallback_Proxy( 
    ISyncMgrSynchronize * This,
    /* [unique][in] */ ISyncMgrSynchronizeCallback *lpCallBack);


void __RPC_STUB ISyncMgrSynchronize_SetProgressCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_PrepareForSync_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ ULONG cbNumItems,
    /* [size_is][in] */ GUID *pItemIDs,
    /* [in] */ HWND hWndParent,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB ISyncMgrSynchronize_PrepareForSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_Synchronize_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ HWND hWndParent);


void __RPC_STUB ISyncMgrSynchronize_Synchronize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_SetItemStatus_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ REFGUID pItemID,
    /* [in] */ DWORD dwSyncMgrStatus);


void __RPC_STUB ISyncMgrSynchronize_SetItemStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronize_ShowError_Proxy( 
    ISyncMgrSynchronize * This,
    /* [in] */ HWND hWndParent,
    /* [in] */ REFGUID ErrorID);


void __RPC_STUB ISyncMgrSynchronize_ShowError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrSynchronize_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrSynchronizeInvoke_INTERFACE_DEFINED__
#define __ISyncMgrSynchronizeInvoke_INTERFACE_DEFINED__

/* interface ISyncMgrSynchronizeInvoke */
/* [unique][uuid][object] */ 

typedef /* [unique] */ ISyncMgrSynchronizeInvoke *LPSYNCMGRSYNCHRONIZEINVOKE;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRINVOKEFLAGS
    {	SYNCMGRINVOKE_STARTSYNC	= 0x2,
	SYNCMGRINVOKE_MINIMIZED	= 0x4
    } 	SYNCMGRINVOKEFLAGS;


EXTERN_C const IID IID_ISyncMgrSynchronizeInvoke;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6295DF2C-35EE-11d1-8707-00C04FD93327")
    ISyncMgrSynchronizeInvoke : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UpdateItems( 
            /* [in] */ DWORD dwInvokeFlags,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ DWORD cbCookie,
            /* [size_is][unique][in] */ const BYTE *lpCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrSynchronizeInvokeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrSynchronizeInvoke * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrSynchronizeInvoke * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrSynchronizeInvoke * This);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateItems )( 
            ISyncMgrSynchronizeInvoke * This,
            /* [in] */ DWORD dwInvokeFlags,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ DWORD cbCookie,
            /* [size_is][unique][in] */ const BYTE *lpCookie);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateAll )( 
            ISyncMgrSynchronizeInvoke * This);
        
        END_INTERFACE
    } ISyncMgrSynchronizeInvokeVtbl;

    interface ISyncMgrSynchronizeInvoke
    {
        CONST_VTBL struct ISyncMgrSynchronizeInvokeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrSynchronizeInvoke_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrSynchronizeInvoke_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrSynchronizeInvoke_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrSynchronizeInvoke_UpdateItems(This,dwInvokeFlags,rclsid,cbCookie,lpCookie)	\
    ( (This)->lpVtbl -> UpdateItems(This,dwInvokeFlags,rclsid,cbCookie,lpCookie) ) 

#define ISyncMgrSynchronizeInvoke_UpdateAll(This)	\
    ( (This)->lpVtbl -> UpdateAll(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeInvoke_UpdateItems_Proxy( 
    ISyncMgrSynchronizeInvoke * This,
    /* [in] */ DWORD dwInvokeFlags,
    /* [in] */ REFCLSID rclsid,
    /* [in] */ DWORD cbCookie,
    /* [size_is][unique][in] */ const BYTE *lpCookie);


void __RPC_STUB ISyncMgrSynchronizeInvoke_UpdateItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrSynchronizeInvoke_UpdateAll_Proxy( 
    ISyncMgrSynchronizeInvoke * This);


void __RPC_STUB ISyncMgrSynchronizeInvoke_UpdateAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrSynchronizeInvoke_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrRegister_INTERFACE_DEFINED__
#define __ISyncMgrRegister_INTERFACE_DEFINED__

/* interface ISyncMgrRegister */
/* [unique][uuid][object] */ 

typedef /* [unique] */ ISyncMgrRegister *LPSYNCMGRREGISTER;

typedef /* [v1_enum] */ 
enum _tagSYNCMGRREGISTERFLAGS
    {	SYNCMGRREGISTERFLAG_CONNECT	= 0x1,
	SYNCMGRREGISTERFLAG_PENDINGDISCONNECT	= 0x2,
	SYNCMGRREGISTERFLAG_IDLE	= 0x4
    } 	SYNCMGRREGISTERFLAGS;

#define SYNCMGRREGISTERFLAGS_MASK  0x07

EXTERN_C const IID IID_ISyncMgrRegister;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6295DF42-35EE-11d1-8707-00C04FD93327")
    ISyncMgrRegister : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterSyncMgrHandler( 
            /* [in] */ REFCLSID rclsidHandler,
            /* [unique][in] */ LPCWSTR pwszDescription,
            /* [in] */ DWORD dwSyncMgrRegisterFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterSyncMgrHandler( 
            /* [in] */ REFCLSID rclsidHandler,
            /* [in] */ DWORD dwReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHandlerRegistrationInfo( 
            /* [in] */ REFCLSID rclsidHandler,
            /* [out][in] */ LPDWORD pdwSyncMgrRegisterFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrRegisterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrRegister * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrRegister * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrRegister * This);
        
        HRESULT ( STDMETHODCALLTYPE *RegisterSyncMgrHandler )( 
            ISyncMgrRegister * This,
            /* [in] */ REFCLSID rclsidHandler,
            /* [unique][in] */ LPCWSTR pwszDescription,
            /* [in] */ DWORD dwSyncMgrRegisterFlags);
        
        HRESULT ( STDMETHODCALLTYPE *UnregisterSyncMgrHandler )( 
            ISyncMgrRegister * This,
            /* [in] */ REFCLSID rclsidHandler,
            /* [in] */ DWORD dwReserved);
        
        HRESULT ( STDMETHODCALLTYPE *GetHandlerRegistrationInfo )( 
            ISyncMgrRegister * This,
            /* [in] */ REFCLSID rclsidHandler,
            /* [out][in] */ LPDWORD pdwSyncMgrRegisterFlags);
        
        END_INTERFACE
    } ISyncMgrRegisterVtbl;

    interface ISyncMgrRegister
    {
        CONST_VTBL struct ISyncMgrRegisterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrRegister_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrRegister_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrRegister_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrRegister_RegisterSyncMgrHandler(This,rclsidHandler,pwszDescription,dwSyncMgrRegisterFlags)	\
    ( (This)->lpVtbl -> RegisterSyncMgrHandler(This,rclsidHandler,pwszDescription,dwSyncMgrRegisterFlags) ) 

#define ISyncMgrRegister_UnregisterSyncMgrHandler(This,rclsidHandler,dwReserved)	\
    ( (This)->lpVtbl -> UnregisterSyncMgrHandler(This,rclsidHandler,dwReserved) ) 

#define ISyncMgrRegister_GetHandlerRegistrationInfo(This,rclsidHandler,pdwSyncMgrRegisterFlags)	\
    ( (This)->lpVtbl -> GetHandlerRegistrationInfo(This,rclsidHandler,pdwSyncMgrRegisterFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrRegister_RegisterSyncMgrHandler_Proxy( 
    ISyncMgrRegister * This,
    /* [in] */ REFCLSID rclsidHandler,
    /* [unique][in] */ LPCWSTR pwszDescription,
    /* [in] */ DWORD dwSyncMgrRegisterFlags);


void __RPC_STUB ISyncMgrRegister_RegisterSyncMgrHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrRegister_UnregisterSyncMgrHandler_Proxy( 
    ISyncMgrRegister * This,
    /* [in] */ REFCLSID rclsidHandler,
    /* [in] */ DWORD dwReserved);


void __RPC_STUB ISyncMgrRegister_UnregisterSyncMgrHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrRegister_GetHandlerRegistrationInfo_Proxy( 
    ISyncMgrRegister * This,
    /* [in] */ REFCLSID rclsidHandler,
    /* [out][in] */ LPDWORD pdwSyncMgrRegisterFlags);


void __RPC_STUB ISyncMgrRegister_GetHandlerRegistrationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrRegister_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrConflictItem_INTERFACE_DEFINED__
#define __ISyncMgrConflictItem_INTERFACE_DEFINED__

/* interface ISyncMgrConflictItem */
/* [object][local][unique][uuid] */ 


EXTERN_C const IID IID_ISyncMgrConflictItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98ce8b1c-4975-45f3-819f-60ae2a59f544")
    ISyncMgrConflictItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetId( 
            /* [out] */ DWORD_PTR *pdwId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocation( 
            /* [out] */ LPWSTR *ppszLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDevice( 
            /* [out] */ LPWSTR *ppszDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPath( 
            /* [out] */ LPWSTR *ppszPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ LPWSTR *ppszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetThumbnail( 
            /* [in] */ UINT cx,
            /* [in] */ UINT cy,
            /* [out] */ HBITMAP *phThumbnail) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrConflictItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrConflictItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrConflictItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrConflictItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetId )( 
            ISyncMgrConflictItem * This,
            /* [out] */ DWORD_PTR *pdwId);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocation )( 
            ISyncMgrConflictItem * This,
            /* [out] */ LPWSTR *ppszLocation);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ISyncMgrConflictItem * This,
            /* [out] */ LPWSTR *ppszDevice);
        
        HRESULT ( STDMETHODCALLTYPE *GetPath )( 
            ISyncMgrConflictItem * This,
            /* [out] */ LPWSTR *ppszPath);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ISyncMgrConflictItem * This,
            /* [out] */ LPWSTR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetThumbnail )( 
            ISyncMgrConflictItem * This,
            /* [in] */ UINT cx,
            /* [in] */ UINT cy,
            /* [out] */ HBITMAP *phThumbnail);
        
        HRESULT ( STDMETHODCALLTYPE *GetProperties )( 
            ISyncMgrConflictItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } ISyncMgrConflictItemVtbl;

    interface ISyncMgrConflictItem
    {
        CONST_VTBL struct ISyncMgrConflictItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrConflictItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrConflictItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrConflictItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrConflictItem_GetId(This,pdwId)	\
    ( (This)->lpVtbl -> GetId(This,pdwId) ) 

#define ISyncMgrConflictItem_GetLocation(This,ppszLocation)	\
    ( (This)->lpVtbl -> GetLocation(This,ppszLocation) ) 

#define ISyncMgrConflictItem_GetDevice(This,ppszDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,ppszDevice) ) 

#define ISyncMgrConflictItem_GetPath(This,ppszPath)	\
    ( (This)->lpVtbl -> GetPath(This,ppszPath) ) 

#define ISyncMgrConflictItem_GetName(This,ppszName)	\
    ( (This)->lpVtbl -> GetName(This,ppszName) ) 

#define ISyncMgrConflictItem_GetThumbnail(This,cx,cy,phThumbnail)	\
    ( (This)->lpVtbl -> GetThumbnail(This,cx,cy,phThumbnail) ) 

#define ISyncMgrConflictItem_GetProperties(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetProperties(This,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetId_Proxy( 
    ISyncMgrConflictItem * This,
    /* [out] */ DWORD_PTR *pdwId);


void __RPC_STUB ISyncMgrConflictItem_GetId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetLocation_Proxy( 
    ISyncMgrConflictItem * This,
    /* [out] */ LPWSTR *ppszLocation);


void __RPC_STUB ISyncMgrConflictItem_GetLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetDevice_Proxy( 
    ISyncMgrConflictItem * This,
    /* [out] */ LPWSTR *ppszDevice);


void __RPC_STUB ISyncMgrConflictItem_GetDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetPath_Proxy( 
    ISyncMgrConflictItem * This,
    /* [out] */ LPWSTR *ppszPath);


void __RPC_STUB ISyncMgrConflictItem_GetPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetName_Proxy( 
    ISyncMgrConflictItem * This,
    /* [out] */ LPWSTR *ppszName);


void __RPC_STUB ISyncMgrConflictItem_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetThumbnail_Proxy( 
    ISyncMgrConflictItem * This,
    /* [in] */ UINT cx,
    /* [in] */ UINT cy,
    /* [out] */ HBITMAP *phThumbnail);


void __RPC_STUB ISyncMgrConflictItem_GetThumbnail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictItem_GetProperties_Proxy( 
    ISyncMgrConflictItem * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB ISyncMgrConflictItem_GetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrConflictItem_INTERFACE_DEFINED__ */


#ifndef __IEnumSyncMgrConflictItem_INTERFACE_DEFINED__
#define __IEnumSyncMgrConflictItem_INTERFACE_DEFINED__

/* interface IEnumSyncMgrConflictItem */
/* [object][local][unique][uuid] */ 


EXTERN_C const IID IID_IEnumSyncMgrConflictItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("abf77854-e195-4fbd-a292-1492dbb90476")
    IEnumSyncMgrConflictItem : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncMgrConflictItem **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSyncMgrConflictItem **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumSyncMgrConflictItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSyncMgrConflictItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSyncMgrConflictItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSyncMgrConflictItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSyncMgrConflictItem * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncMgrConflictItem **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSyncMgrConflictItem * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSyncMgrConflictItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSyncMgrConflictItem * This,
            /* [out] */ IEnumSyncMgrConflictItem **ppenum);
        
        END_INTERFACE
    } IEnumSyncMgrConflictItemVtbl;

    interface IEnumSyncMgrConflictItem
    {
        CONST_VTBL struct IEnumSyncMgrConflictItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSyncMgrConflictItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSyncMgrConflictItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSyncMgrConflictItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSyncMgrConflictItem_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSyncMgrConflictItem_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumSyncMgrConflictItem_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSyncMgrConflictItem_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflictItem_Next_Proxy( 
    IEnumSyncMgrConflictItem * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ ISyncMgrConflictItem **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumSyncMgrConflictItem_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflictItem_Skip_Proxy( 
    IEnumSyncMgrConflictItem * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumSyncMgrConflictItem_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflictItem_Reset_Proxy( 
    IEnumSyncMgrConflictItem * This);


void __RPC_STUB IEnumSyncMgrConflictItem_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflictItem_Clone_Proxy( 
    IEnumSyncMgrConflictItem * This,
    /* [out] */ IEnumSyncMgrConflictItem **ppenum);


void __RPC_STUB IEnumSyncMgrConflictItem_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumSyncMgrConflictItem_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrConflictShellItem_INTERFACE_DEFINED__
#define __ISyncMgrConflictShellItem_INTERFACE_DEFINED__

/* interface ISyncMgrConflictShellItem */
/* [object][local][unique][uuid] */ 


EXTERN_C const IID IID_ISyncMgrConflictShellItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("dcefff96-f0b3-4e3b-940e-0dc0ac0edd28")
    ISyncMgrConflictShellItem : public ISyncMgrConflictItem
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetShellItem( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrConflictShellItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrConflictShellItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrConflictShellItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrConflictShellItem * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetId )( 
            ISyncMgrConflictShellItem * This,
            /* [out] */ DWORD_PTR *pdwId);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocation )( 
            ISyncMgrConflictShellItem * This,
            /* [out] */ LPWSTR *ppszLocation);
        
        HRESULT ( STDMETHODCALLTYPE *GetDevice )( 
            ISyncMgrConflictShellItem * This,
            /* [out] */ LPWSTR *ppszDevice);
        
        HRESULT ( STDMETHODCALLTYPE *GetPath )( 
            ISyncMgrConflictShellItem * This,
            /* [out] */ LPWSTR *ppszPath);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ISyncMgrConflictShellItem * This,
            /* [out] */ LPWSTR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetThumbnail )( 
            ISyncMgrConflictShellItem * This,
            /* [in] */ UINT cx,
            /* [in] */ UINT cy,
            /* [out] */ HBITMAP *phThumbnail);
        
        HRESULT ( STDMETHODCALLTYPE *GetProperties )( 
            ISyncMgrConflictShellItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetShellItem )( 
            ISyncMgrConflictShellItem * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } ISyncMgrConflictShellItemVtbl;

    interface ISyncMgrConflictShellItem
    {
        CONST_VTBL struct ISyncMgrConflictShellItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrConflictShellItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrConflictShellItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrConflictShellItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrConflictShellItem_GetId(This,pdwId)	\
    ( (This)->lpVtbl -> GetId(This,pdwId) ) 

#define ISyncMgrConflictShellItem_GetLocation(This,ppszLocation)	\
    ( (This)->lpVtbl -> GetLocation(This,ppszLocation) ) 

#define ISyncMgrConflictShellItem_GetDevice(This,ppszDevice)	\
    ( (This)->lpVtbl -> GetDevice(This,ppszDevice) ) 

#define ISyncMgrConflictShellItem_GetPath(This,ppszPath)	\
    ( (This)->lpVtbl -> GetPath(This,ppszPath) ) 

#define ISyncMgrConflictShellItem_GetName(This,ppszName)	\
    ( (This)->lpVtbl -> GetName(This,ppszName) ) 

#define ISyncMgrConflictShellItem_GetThumbnail(This,cx,cy,phThumbnail)	\
    ( (This)->lpVtbl -> GetThumbnail(This,cx,cy,phThumbnail) ) 

#define ISyncMgrConflictShellItem_GetProperties(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetProperties(This,riid,ppv) ) 


#define ISyncMgrConflictShellItem_GetShellItem(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetShellItem(This,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrConflictShellItem_GetShellItem_Proxy( 
    ISyncMgrConflictShellItem * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB ISyncMgrConflictShellItem_GetShellItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrConflictShellItem_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrConflictCategory_INTERFACE_DEFINED__
#define __ISyncMgrConflictCategory_INTERFACE_DEFINED__

/* interface ISyncMgrConflictCategory */
/* [object][local][unique][uuid] */ 

typedef /* [v1_enum] */ 
enum tagSYNCMGRRESOLUTIONGOAL
    {	SMRG_KEEPONE	= 1,
	SMRG_KEEPTWO	= 2,
	SMRG_AUTO	= 3,
	SMRG_DISABLE	= 4
    } 	SYNCMGRRESOLUTIONGOAL;


EXTERN_C const IID IID_ISyncMgrConflictCategory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("caa0281a-09ac-41ee-baad-e1392ef19733")
    ISyncMgrConflictCategory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTitle( 
            /* [string][out] */ LPWSTR **ppszTitle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectionText( 
            /* [in] */ SYNCMGRRESOLUTIONGOAL smrg,
            /* [string][out] */ LPWSTR **ppszSelection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrConflictCategoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrConflictCategory * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrConflictCategory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrConflictCategory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTitle )( 
            ISyncMgrConflictCategory * This,
            /* [string][out] */ LPWSTR **ppszTitle);
        
        HRESULT ( STDMETHODCALLTYPE *GetSelectionText )( 
            ISyncMgrConflictCategory * This,
            /* [in] */ SYNCMGRRESOLUTIONGOAL smrg,
            /* [string][out] */ LPWSTR **ppszSelection);
        
        END_INTERFACE
    } ISyncMgrConflictCategoryVtbl;

    interface ISyncMgrConflictCategory
    {
        CONST_VTBL struct ISyncMgrConflictCategoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrConflictCategory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrConflictCategory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrConflictCategory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrConflictCategory_GetTitle(This,ppszTitle)	\
    ( (This)->lpVtbl -> GetTitle(This,ppszTitle) ) 

#define ISyncMgrConflictCategory_GetSelectionText(This,smrg,ppszSelection)	\
    ( (This)->lpVtbl -> GetSelectionText(This,smrg,ppszSelection) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrConflictCategory_GetTitle_Proxy( 
    ISyncMgrConflictCategory * This,
    /* [string][out] */ LPWSTR **ppszTitle);


void __RPC_STUB ISyncMgrConflictCategory_GetTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictCategory_GetSelectionText_Proxy( 
    ISyncMgrConflictCategory * This,
    /* [in] */ SYNCMGRRESOLUTIONGOAL smrg,
    /* [string][out] */ LPWSTR **ppszSelection);


void __RPC_STUB ISyncMgrConflictCategory_GetSelectionText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrConflictCategory_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrConflict_INTERFACE_DEFINED__
#define __ISyncMgrConflict_INTERFACE_DEFINED__

/* interface ISyncMgrConflict */
/* [object][local][unique][uuid] */ 


EXTERN_C const IID IID_ISyncMgrConflict;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("cbc7653a-fcd3-4a98-9ca4-789876fc4872")
    ISyncMgrConflict : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [string][out] */ LPWSTR *ppszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetThumbnail( 
            /* [in] */ UINT cx,
            /* [in] */ UINT cy,
            /* [out] */ HBITMAP *phThumbnail) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSummary( 
            /* [string][out] */ LPWSTR *ppszSummary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUserGuid( 
            /* [out] */ GUID *pUserGuid) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDateDetected( 
            /* [out] */ FILETIME *pftDetected) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSyncHandlerClsid( 
            /* [out] */ CLSID *pclsidSyncHandler) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSyncItemGuid( 
            /* [out] */ GUID *pguidSyncItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetResolverCLSID( 
            /* [out] */ CLSID *pclsidResolver) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediatorCLSID( 
            /* [out] */ CLSID *pclsidMediator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumConflictItems( 
            /* [out] */ IEnumSyncMgrConflictItem **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDataBlob( 
            /* [out] */ LPARAM *plParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCategory( 
            /* [out] */ ISyncMgrConflictCategory **ppCategory) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGuid( 
            /* [out] */ GUID *pConflictGuid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrConflictVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrConflict * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrConflict * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrConflict * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ISyncMgrConflict * This,
            /* [string][out] */ LPWSTR *ppszName);
        
        HRESULT ( STDMETHODCALLTYPE *GetThumbnail )( 
            ISyncMgrConflict * This,
            /* [in] */ UINT cx,
            /* [in] */ UINT cy,
            /* [out] */ HBITMAP *phThumbnail);
        
        HRESULT ( STDMETHODCALLTYPE *GetSummary )( 
            ISyncMgrConflict * This,
            /* [string][out] */ LPWSTR *ppszSummary);
        
        HRESULT ( STDMETHODCALLTYPE *GetUserGuid )( 
            ISyncMgrConflict * This,
            /* [out] */ GUID *pUserGuid);
        
        HRESULT ( STDMETHODCALLTYPE *GetDateDetected )( 
            ISyncMgrConflict * This,
            /* [out] */ FILETIME *pftDetected);
        
        HRESULT ( STDMETHODCALLTYPE *GetSyncHandlerClsid )( 
            ISyncMgrConflict * This,
            /* [out] */ CLSID *pclsidSyncHandler);
        
        HRESULT ( STDMETHODCALLTYPE *GetSyncItemGuid )( 
            ISyncMgrConflict * This,
            /* [out] */ GUID *pguidSyncItem);
        
        HRESULT ( STDMETHODCALLTYPE *GetResolverCLSID )( 
            ISyncMgrConflict * This,
            /* [out] */ CLSID *pclsidResolver);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediatorCLSID )( 
            ISyncMgrConflict * This,
            /* [out] */ CLSID *pclsidMediator);
        
        HRESULT ( STDMETHODCALLTYPE *EnumConflictItems )( 
            ISyncMgrConflict * This,
            /* [out] */ IEnumSyncMgrConflictItem **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *GetDataBlob )( 
            ISyncMgrConflict * This,
            /* [out] */ LPARAM *plParam);
        
        HRESULT ( STDMETHODCALLTYPE *GetCategory )( 
            ISyncMgrConflict * This,
            /* [out] */ ISyncMgrConflictCategory **ppCategory);
        
        HRESULT ( STDMETHODCALLTYPE *GetGuid )( 
            ISyncMgrConflict * This,
            /* [out] */ GUID *pConflictGuid);
        
        END_INTERFACE
    } ISyncMgrConflictVtbl;

    interface ISyncMgrConflict
    {
        CONST_VTBL struct ISyncMgrConflictVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrConflict_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrConflict_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrConflict_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrConflict_GetName(This,ppszName)	\
    ( (This)->lpVtbl -> GetName(This,ppszName) ) 

#define ISyncMgrConflict_GetThumbnail(This,cx,cy,phThumbnail)	\
    ( (This)->lpVtbl -> GetThumbnail(This,cx,cy,phThumbnail) ) 

#define ISyncMgrConflict_GetSummary(This,ppszSummary)	\
    ( (This)->lpVtbl -> GetSummary(This,ppszSummary) ) 

#define ISyncMgrConflict_GetUserGuid(This,pUserGuid)	\
    ( (This)->lpVtbl -> GetUserGuid(This,pUserGuid) ) 

#define ISyncMgrConflict_GetDateDetected(This,pftDetected)	\
    ( (This)->lpVtbl -> GetDateDetected(This,pftDetected) ) 

#define ISyncMgrConflict_GetSyncHandlerClsid(This,pclsidSyncHandler)	\
    ( (This)->lpVtbl -> GetSyncHandlerClsid(This,pclsidSyncHandler) ) 

#define ISyncMgrConflict_GetSyncItemGuid(This,pguidSyncItem)	\
    ( (This)->lpVtbl -> GetSyncItemGuid(This,pguidSyncItem) ) 

#define ISyncMgrConflict_GetResolverCLSID(This,pclsidResolver)	\
    ( (This)->lpVtbl -> GetResolverCLSID(This,pclsidResolver) ) 

#define ISyncMgrConflict_GetMediatorCLSID(This,pclsidMediator)	\
    ( (This)->lpVtbl -> GetMediatorCLSID(This,pclsidMediator) ) 

#define ISyncMgrConflict_EnumConflictItems(This,ppEnum)	\
    ( (This)->lpVtbl -> EnumConflictItems(This,ppEnum) ) 

#define ISyncMgrConflict_GetDataBlob(This,plParam)	\
    ( (This)->lpVtbl -> GetDataBlob(This,plParam) ) 

#define ISyncMgrConflict_GetCategory(This,ppCategory)	\
    ( (This)->lpVtbl -> GetCategory(This,ppCategory) ) 

#define ISyncMgrConflict_GetGuid(This,pConflictGuid)	\
    ( (This)->lpVtbl -> GetGuid(This,pConflictGuid) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetName_Proxy( 
    ISyncMgrConflict * This,
    /* [string][out] */ LPWSTR *ppszName);


void __RPC_STUB ISyncMgrConflict_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetThumbnail_Proxy( 
    ISyncMgrConflict * This,
    /* [in] */ UINT cx,
    /* [in] */ UINT cy,
    /* [out] */ HBITMAP *phThumbnail);


void __RPC_STUB ISyncMgrConflict_GetThumbnail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetSummary_Proxy( 
    ISyncMgrConflict * This,
    /* [string][out] */ LPWSTR *ppszSummary);


void __RPC_STUB ISyncMgrConflict_GetSummary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetUserGuid_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ GUID *pUserGuid);


void __RPC_STUB ISyncMgrConflict_GetUserGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetDateDetected_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ FILETIME *pftDetected);


void __RPC_STUB ISyncMgrConflict_GetDateDetected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetSyncHandlerClsid_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ CLSID *pclsidSyncHandler);


void __RPC_STUB ISyncMgrConflict_GetSyncHandlerClsid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetSyncItemGuid_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ GUID *pguidSyncItem);


void __RPC_STUB ISyncMgrConflict_GetSyncItemGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetResolverCLSID_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ CLSID *pclsidResolver);


void __RPC_STUB ISyncMgrConflict_GetResolverCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetMediatorCLSID_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ CLSID *pclsidMediator);


void __RPC_STUB ISyncMgrConflict_GetMediatorCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_EnumConflictItems_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ IEnumSyncMgrConflictItem **ppEnum);


void __RPC_STUB ISyncMgrConflict_EnumConflictItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetDataBlob_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ LPARAM *plParam);


void __RPC_STUB ISyncMgrConflict_GetDataBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetCategory_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ ISyncMgrConflictCategory **ppCategory);


void __RPC_STUB ISyncMgrConflict_GetCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflict_GetGuid_Proxy( 
    ISyncMgrConflict * This,
    /* [out] */ GUID *pConflictGuid);


void __RPC_STUB ISyncMgrConflict_GetGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrConflict_INTERFACE_DEFINED__ */


#ifndef __IEnumSyncMgrConflict_INTERFACE_DEFINED__
#define __IEnumSyncMgrConflict_INTERFACE_DEFINED__

/* interface IEnumSyncMgrConflict */
/* [object][unique][uuid] */ 


EXTERN_C const IID IID_IEnumSyncMgrConflict;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("633d7446-a45c-4c09-a7cf-b9118236185b")
    IEnumSyncMgrConflict : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncMgrConflict **rgelt,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSyncMgrConflict **ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumSyncMgrConflictVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumSyncMgrConflict * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumSyncMgrConflict * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumSyncMgrConflict * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumSyncMgrConflict * This,
            /* [in] */ ULONG celt,
            /* [length_is][size_is][out] */ ISyncMgrConflict **rgelt,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumSyncMgrConflict * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumSyncMgrConflict * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumSyncMgrConflict * This,
            /* [out] */ IEnumSyncMgrConflict **ppenum);
        
        END_INTERFACE
    } IEnumSyncMgrConflictVtbl;

    interface IEnumSyncMgrConflict
    {
        CONST_VTBL struct IEnumSyncMgrConflictVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSyncMgrConflict_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumSyncMgrConflict_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumSyncMgrConflict_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumSyncMgrConflict_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumSyncMgrConflict_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumSyncMgrConflict_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumSyncMgrConflict_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflict_Next_Proxy( 
    IEnumSyncMgrConflict * This,
    /* [in] */ ULONG celt,
    /* [length_is][size_is][out] */ ISyncMgrConflict **rgelt,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumSyncMgrConflict_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflict_Skip_Proxy( 
    IEnumSyncMgrConflict * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumSyncMgrConflict_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflict_Reset_Proxy( 
    IEnumSyncMgrConflict * This);


void __RPC_STUB IEnumSyncMgrConflict_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSyncMgrConflict_Clone_Proxy( 
    IEnumSyncMgrConflict * This,
    /* [out] */ IEnumSyncMgrConflict **ppenum);


void __RPC_STUB IEnumSyncMgrConflict_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumSyncMgrConflict_INTERFACE_DEFINED__ */


#ifndef __ISyncMgrConflictStore_INTERFACE_DEFINED__
#define __ISyncMgrConflictStore_INTERFACE_DEFINED__

/* interface ISyncMgrConflictStore */
/* [object][unique][uuid] */ 


EXTERN_C const IID IID_ISyncMgrConflictStore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f10951b1-7b06-43c4-af27-d5c0351db0c6")
    ISyncMgrConflictStore : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumConflicts( 
            /* [out] */ IEnumSyncMgrConflict **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConflict( 
            /* [in] */ REFGUID guidConflict,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveConflict( 
            /* [in] */ ISyncMgrConflict *pConflict) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISyncMgrConflictStoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISyncMgrConflictStore * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISyncMgrConflictStore * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISyncMgrConflictStore * This);
        
        HRESULT ( STDMETHODCALLTYPE *EnumConflicts )( 
            ISyncMgrConflictStore * This,
            /* [out] */ IEnumSyncMgrConflict **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *GetConflict )( 
            ISyncMgrConflictStore * This,
            /* [in] */ REFGUID guidConflict,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveConflict )( 
            ISyncMgrConflictStore * This,
            /* [in] */ ISyncMgrConflict *pConflict);
        
        END_INTERFACE
    } ISyncMgrConflictStoreVtbl;

    interface ISyncMgrConflictStore
    {
        CONST_VTBL struct ISyncMgrConflictStoreVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISyncMgrConflictStore_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISyncMgrConflictStore_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISyncMgrConflictStore_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISyncMgrConflictStore_EnumConflicts(This,ppEnum)	\
    ( (This)->lpVtbl -> EnumConflicts(This,ppEnum) ) 

#define ISyncMgrConflictStore_GetConflict(This,guidConflict,riid,ppv)	\
    ( (This)->lpVtbl -> GetConflict(This,guidConflict,riid,ppv) ) 

#define ISyncMgrConflictStore_RemoveConflict(This,pConflict)	\
    ( (This)->lpVtbl -> RemoveConflict(This,pConflict) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISyncMgrConflictStore_EnumConflicts_Proxy( 
    ISyncMgrConflictStore * This,
    /* [out] */ IEnumSyncMgrConflict **ppEnum);


void __RPC_STUB ISyncMgrConflictStore_EnumConflicts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictStore_GetConflict_Proxy( 
    ISyncMgrConflictStore * This,
    /* [in] */ REFGUID guidConflict,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB ISyncMgrConflictStore_GetConflict_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISyncMgrConflictStore_RemoveConflict_Proxy( 
    ISyncMgrConflictStore * This,
    /* [in] */ ISyncMgrConflict *pConflict);


void __RPC_STUB ISyncMgrConflictStore_RemoveConflict_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISyncMgrConflictStore_INTERFACE_DEFINED__ */



#ifndef __SyncObjects_LIBRARY_DEFINED__
#define __SyncObjects_LIBRARY_DEFINED__

/* library SyncObjects */
/* [version][lcid][helpstring][uuid] */ 


EXTERN_C const IID LIBID_SyncObjects;

EXTERN_C const CLSID CLSID_SyncMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("6295DF27-35EE-11d1-8707-00C04FD93327")
SyncMgr;
#endif

EXTERN_C const CLSID CLSID_ConflictFolder;

#ifdef __cplusplus

class DECLSPEC_UUID("289978ac-a101-4341-a817-21eba7fd046d")
ConflictFolder;
#endif
#endif /* __SyncObjects_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HICON_UserSize(     unsigned long *, unsigned long            , HICON * ); 
unsigned char * __RPC_USER  HICON_UserMarshal(  unsigned long *, unsigned char *, HICON * ); 
unsigned char * __RPC_USER  HICON_UserUnmarshal(unsigned long *, unsigned char *, HICON * ); 
void                      __RPC_USER  HICON_UserFree(     unsigned long *, HICON * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

unsigned long             __RPC_USER  HICON_UserSize64(     unsigned long *, unsigned long            , HICON * ); 
unsigned char * __RPC_USER  HICON_UserMarshal64(  unsigned long *, unsigned char *, HICON * ); 
unsigned char * __RPC_USER  HICON_UserUnmarshal64(unsigned long *, unsigned char *, HICON * ); 
void                      __RPC_USER  HICON_UserFree64(     unsigned long *, HICON * ); 

unsigned long             __RPC_USER  HWND_UserSize64(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal64(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal64(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree64(     unsigned long *, HWND * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


