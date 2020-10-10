

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for jobsitf.idl:
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

#ifndef __jobsitf_h__
#define __jobsitf_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IRunningJob_FWD_DEFINED__
#define __IRunningJob_FWD_DEFINED__
typedef interface IRunningJob IRunningJob;
#endif 	/* __IRunningJob_FWD_DEFINED__ */


#ifndef __IRunningJobCollection_FWD_DEFINED__
#define __IRunningJobCollection_FWD_DEFINED__
typedef interface IRunningJobCollection IRunningJobCollection;
#endif 	/* __IRunningJobCollection_FWD_DEFINED__ */


#ifndef __IEnumJobVariableName_FWD_DEFINED__
#define __IEnumJobVariableName_FWD_DEFINED__
typedef interface IEnumJobVariableName IEnumJobVariableName;
#endif 	/* __IEnumJobVariableName_FWD_DEFINED__ */


#ifndef __IJobVariables_FWD_DEFINED__
#define __IJobVariables_FWD_DEFINED__
typedef interface IJobVariables IJobVariables;
#endif 	/* __IJobVariables_FWD_DEFINED__ */


#ifndef __IRegisteredJob_FWD_DEFINED__
#define __IRegisteredJob_FWD_DEFINED__
typedef interface IRegisteredJob IRegisteredJob;
#endif 	/* __IRegisteredJob_FWD_DEFINED__ */


#ifndef __IJobCollection_FWD_DEFINED__
#define __IJobCollection_FWD_DEFINED__
typedef interface IJobCollection IJobCollection;
#endif 	/* __IJobCollection_FWD_DEFINED__ */


#ifndef __IJobFolder_FWD_DEFINED__
#define __IJobFolder_FWD_DEFINED__
typedef interface IJobFolder IJobFolder;
#endif 	/* __IJobFolder_FWD_DEFINED__ */


#ifndef __IJobFolderCollection_FWD_DEFINED__
#define __IJobFolderCollection_FWD_DEFINED__
typedef interface IJobFolderCollection IJobFolderCollection;
#endif 	/* __IJobFolderCollection_FWD_DEFINED__ */


#ifndef __IJobService_FWD_DEFINED__
#define __IJobService_FWD_DEFINED__
typedef interface IJobService IJobService;
#endif 	/* __IJobService_FWD_DEFINED__ */


#ifndef __IHandlerStatus_FWD_DEFINED__
#define __IHandlerStatus_FWD_DEFINED__
typedef interface IHandlerStatus IHandlerStatus;
#endif 	/* __IHandlerStatus_FWD_DEFINED__ */


#ifndef __IHandlerControl_FWD_DEFINED__
#define __IHandlerControl_FWD_DEFINED__
typedef interface IHandlerControl IHandlerControl;
#endif 	/* __IHandlerControl_FWD_DEFINED__ */


#ifndef __IHandler_FWD_DEFINED__
#define __IHandler_FWD_DEFINED__
typedef interface IHandler IHandler;
#endif 	/* __IHandler_FWD_DEFINED__ */


#ifndef __IAsyncHandler_FWD_DEFINED__
#define __IAsyncHandler_FWD_DEFINED__
typedef interface IAsyncHandler IAsyncHandler;
#endif 	/* __IAsyncHandler_FWD_DEFINED__ */


#ifndef __JobService_FWD_DEFINED__
#define __JobService_FWD_DEFINED__

#ifdef __cplusplus
typedef class JobService JobService;
#else
typedef struct JobService JobService;
#endif /* __cplusplus */

#endif 	/* __JobService_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_jobsitf_0000 */
/* [local] */ 

/*******************************************************************************/
/*                                                                             */
/*    Copyright ¬ Microsoft Corporation.  All rights reserved.                 */
/*                                                                             */
/*    IDL source for WMI Jobs                                                  */
/*                                                                             */
/*******************************************************************************/
typedef 
enum tagJOBSTATE
    {	JOBSTATE_DISABLED	= 0,
	JOBSTATE_IDLE	= 1,
	JOBSTATE_RUNNING	= 2
    } 	JOBSTATE;

typedef 
enum tagJOBCREATION
    {	JOB_CREATE_ONLY	= 1,
	JOB_UPDATE_ONLY	= 2,
	JOB_CREATE_OR_UPDATE	= 4
    } 	JOBCREATION;



extern RPC_IF_HANDLE __MIDL_itf_jobsitf_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_jobsitf_0000_v0_0_s_ifspec;

#ifndef __IRunningJob_INTERFACE_DEFINED__
#define __IRunningJob_INTERFACE_DEFINED__

/* interface IRunningJob */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IRunningJob;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("653758fb-7b9a-4f1e-a471-beeb8e9b834e")
    IRunningJob : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_InstanceGuid( 
            /* [retval][out] */ BSTR *guid) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR *pPath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ BSTR *pStatus) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_ActiveStepName( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resume( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRunningJobVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRunningJob * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRunningJob * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRunningJob * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRunningJob * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRunningJob * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRunningJob * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRunningJob * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IRunningJob * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InstanceGuid )( 
            IRunningJob * This,
            /* [retval][out] */ BSTR *guid);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IRunningJob * This,
            /* [retval][out] */ BSTR *pPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            IRunningJob * This,
            /* [retval][out] */ BSTR *pStatus);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveStepName )( 
            IRunningJob * This,
            /* [retval][out] */ BSTR *name);
        
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IRunningJob * This);
        
        HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IRunningJob * This);
        
        HRESULT ( STDMETHODCALLTYPE *Resume )( 
            IRunningJob * This);
        
        HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IRunningJob * This);
        
        END_INTERFACE
    } IRunningJobVtbl;

    interface IRunningJob
    {
        CONST_VTBL struct IRunningJobVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRunningJob_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRunningJob_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRunningJob_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRunningJob_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRunningJob_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRunningJob_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRunningJob_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRunningJob_get_Name(This,pName)	\
    ( (This)->lpVtbl -> get_Name(This,pName) ) 

#define IRunningJob_get_InstanceGuid(This,guid)	\
    ( (This)->lpVtbl -> get_InstanceGuid(This,guid) ) 

#define IRunningJob_get_Path(This,pPath)	\
    ( (This)->lpVtbl -> get_Path(This,pPath) ) 

#define IRunningJob_get_Status(This,pStatus)	\
    ( (This)->lpVtbl -> get_Status(This,pStatus) ) 

#define IRunningJob_get_ActiveStepName(This,name)	\
    ( (This)->lpVtbl -> get_ActiveStepName(This,name) ) 

#define IRunningJob_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define IRunningJob_Pause(This)	\
    ( (This)->lpVtbl -> Pause(This) ) 

#define IRunningJob_Resume(This)	\
    ( (This)->lpVtbl -> Resume(This) ) 

#define IRunningJob_Refresh(This)	\
    ( (This)->lpVtbl -> Refresh(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJob_get_Name_Proxy( 
    IRunningJob * This,
    /* [retval][out] */ BSTR *pName);


void __RPC_STUB IRunningJob_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJob_get_InstanceGuid_Proxy( 
    IRunningJob * This,
    /* [retval][out] */ BSTR *guid);


void __RPC_STUB IRunningJob_get_InstanceGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJob_get_Path_Proxy( 
    IRunningJob * This,
    /* [retval][out] */ BSTR *pPath);


void __RPC_STUB IRunningJob_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJob_get_Status_Proxy( 
    IRunningJob * This,
    /* [retval][out] */ BSTR *pStatus);


void __RPC_STUB IRunningJob_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJob_get_ActiveStepName_Proxy( 
    IRunningJob * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IRunningJob_get_ActiveStepName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunningJob_Stop_Proxy( 
    IRunningJob * This);


void __RPC_STUB IRunningJob_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunningJob_Pause_Proxy( 
    IRunningJob * This);


void __RPC_STUB IRunningJob_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunningJob_Resume_Proxy( 
    IRunningJob * This);


void __RPC_STUB IRunningJob_Resume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRunningJob_Refresh_Proxy( 
    IRunningJob * This);


void __RPC_STUB IRunningJob_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRunningJob_INTERFACE_DEFINED__ */


#ifndef __IRunningJobCollection_INTERFACE_DEFINED__
#define __IRunningJobCollection_INTERFACE_DEFINED__

/* interface IRunningJobCollection */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IRunningJobCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6a67614b-6828-4fec-aa54-6d52e8f1f2db")
    IRunningJobCollection : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *retVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ IRunningJob **ppJob) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRunningJobCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRunningJobCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRunningJobCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRunningJobCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRunningJobCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRunningJobCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRunningJobCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRunningJobCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IRunningJobCollection * This,
            /* [retval][out] */ long *retVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IRunningJobCollection * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ IRunningJob **ppJob);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IRunningJobCollection * This,
            /* [retval][out] */ IUnknown **retVal);
        
        END_INTERFACE
    } IRunningJobCollectionVtbl;

    interface IRunningJobCollection
    {
        CONST_VTBL struct IRunningJobCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRunningJobCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRunningJobCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRunningJobCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRunningJobCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRunningJobCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRunningJobCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRunningJobCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRunningJobCollection_get_Count(This,retVal)	\
    ( (This)->lpVtbl -> get_Count(This,retVal) ) 

#define IRunningJobCollection_get_Item(This,index,ppJob)	\
    ( (This)->lpVtbl -> get_Item(This,index,ppJob) ) 

#define IRunningJobCollection_get__NewEnum(This,retVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJobCollection_get_Count_Proxy( 
    IRunningJobCollection * This,
    /* [retval][out] */ long *retVal);


void __RPC_STUB IRunningJobCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJobCollection_get_Item_Proxy( 
    IRunningJobCollection * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ IRunningJob **ppJob);


void __RPC_STUB IRunningJobCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IRunningJobCollection_get__NewEnum_Proxy( 
    IRunningJobCollection * This,
    /* [retval][out] */ IUnknown **retVal);


void __RPC_STUB IRunningJobCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRunningJobCollection_INTERFACE_DEFINED__ */


#ifndef __IEnumJobVariableName_INTERFACE_DEFINED__
#define __IEnumJobVariableName_INTERFACE_DEFINED__

/* interface IEnumJobVariableName */
/* [uuid][object] */ 


EXTERN_C const IID IID_IEnumJobVariableName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51325e1a-2538-4754-96b5-4d6151eaac80")
    IEnumJobVariableName : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            ULONG celt,
            BSTR **ppVar,
            ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumJobVariableName **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumJobVariableNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumJobVariableName * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumJobVariableName * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumJobVariableName * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumJobVariableName * This,
            ULONG celt,
            BSTR **ppVar,
            ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumJobVariableName * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumJobVariableName * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumJobVariableName * This,
            /* [out] */ IEnumJobVariableName **ppEnum);
        
        END_INTERFACE
    } IEnumJobVariableNameVtbl;

    interface IEnumJobVariableName
    {
        CONST_VTBL struct IEnumJobVariableNameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumJobVariableName_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumJobVariableName_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumJobVariableName_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumJobVariableName_Next(This,celt,ppVar,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,ppVar,pceltFetched) ) 

#define IEnumJobVariableName_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumJobVariableName_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#define IEnumJobVariableName_Clone(This,ppEnum)	\
    ( (This)->lpVtbl -> Clone(This,ppEnum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumJobVariableName_Next_Proxy( 
    IEnumJobVariableName * This,
    ULONG celt,
    BSTR **ppVar,
    ULONG *pceltFetched);


void __RPC_STUB IEnumJobVariableName_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumJobVariableName_Reset_Proxy( 
    IEnumJobVariableName * This);


void __RPC_STUB IEnumJobVariableName_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumJobVariableName_Skip_Proxy( 
    IEnumJobVariableName * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumJobVariableName_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumJobVariableName_Clone_Proxy( 
    IEnumJobVariableName * This,
    /* [out] */ IEnumJobVariableName **ppEnum);


void __RPC_STUB IEnumJobVariableName_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumJobVariableName_INTERFACE_DEFINED__ */


#ifndef __IJobVariables_INTERFACE_DEFINED__
#define __IJobVariables_INTERFACE_DEFINED__

/* interface IJobVariables */
/* [uuid][object] */ 


EXTERN_C const IID IID_IJobVariables;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3e4c9351-d966-4b8b-bb87-ceba68bb0107")
    IJobVariables : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetVariable( 
            BSTR Name,
            /* [retval][out] */ BSTR *pbstrValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVariable( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumVariableNames( 
            /* [retval][out] */ IEnumJobVariableName **ppVarEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobVariablesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobVariables * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobVariables * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobVariables * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetVariable )( 
            IJobVariables * This,
            BSTR Name,
            /* [retval][out] */ BSTR *pbstrValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetVariable )( 
            IJobVariables * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value);
        
        HRESULT ( STDMETHODCALLTYPE *EnumVariableNames )( 
            IJobVariables * This,
            /* [retval][out] */ IEnumJobVariableName **ppVarEnum);
        
        END_INTERFACE
    } IJobVariablesVtbl;

    interface IJobVariables
    {
        CONST_VTBL struct IJobVariablesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobVariables_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobVariables_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobVariables_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobVariables_GetVariable(This,Name,pbstrValue)	\
    ( (This)->lpVtbl -> GetVariable(This,Name,pbstrValue) ) 

#define IJobVariables_SetVariable(This,Name,Value)	\
    ( (This)->lpVtbl -> SetVariable(This,Name,Value) ) 

#define IJobVariables_EnumVariableNames(This,ppVarEnum)	\
    ( (This)->lpVtbl -> EnumVariableNames(This,ppVarEnum) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IJobVariables_GetVariable_Proxy( 
    IJobVariables * This,
    BSTR Name,
    /* [retval][out] */ BSTR *pbstrValue);


void __RPC_STUB IJobVariables_GetVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IJobVariables_SetVariable_Proxy( 
    IJobVariables * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Value);


void __RPC_STUB IJobVariables_SetVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IJobVariables_EnumVariableNames_Proxy( 
    IJobVariables * This,
    /* [retval][out] */ IEnumJobVariableName **ppVarEnum);


void __RPC_STUB IJobVariables_EnumVariableNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobVariables_INTERFACE_DEFINED__ */


#ifndef __IRegisteredJob_INTERFACE_DEFINED__
#define __IRegisteredJob_INTERFACE_DEFINED__

/* interface IRegisteredJob */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IRegisteredJob;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9c86f320-dee3-4dd1-b972-a303f26b061e")
    IRegisteredJob : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *ppName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR *ppPath) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR *pDisplayName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pDescription) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_XML( 
            /* [retval][out] */ BSTR *ppXML) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ JOBSTATE *pState) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ boolean *pEnabled) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            boolean Enabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( 
            /* [in] */ VARIANT params,
            /* [retval][out] */ IRunningJob **ppRetval) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInstances( 
            /* [retval][out] */ IRunningJobCollection **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateJob( 
            BSTR body,
            BSTR sddl,
            DWORD options) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCredentials( 
            BSTR UserId,
            BSTR Password) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCredentials( 
            /* [out] */ BSTR *pUserId) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LastRunTime( 
            /* [retval][out] */ SYSTEMTIME *retVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LastJobResult( 
            /* [retval][out] */ HRESULT *retVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_LastTaskResult( 
            /* [retval][out] */ DWORD *retVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NumberOfMissedJobs( 
            /* [retval][out] */ DWORD *retVal) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NextRunTime( 
            /* [retval][out] */ SYSTEMTIME *pstLastRun) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRunTimes( 
            /* [in] */ const LPSYSTEMTIME pstBegin,
            /* [in] */ const LPSYSTEMTIME pstEnd,
            /* [out] */ WORD *pCount,
            /* [out] */ LPSYSTEMTIME *rgstTaskTimes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRegisteredJobVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IRegisteredJob * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IRegisteredJob * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IRegisteredJob * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IRegisteredJob * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IRegisteredJob * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IRegisteredJob * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IRegisteredJob * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IRegisteredJob * This,
            /* [retval][out] */ BSTR *ppName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IRegisteredJob * This,
            /* [retval][out] */ BSTR *ppPath);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayName )( 
            IRegisteredJob * This,
            /* [retval][out] */ BSTR *pDisplayName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IRegisteredJob * This,
            /* [retval][out] */ BSTR *pDescription);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_XML )( 
            IRegisteredJob * This,
            /* [retval][out] */ BSTR *ppXML);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_State )( 
            IRegisteredJob * This,
            /* [retval][out] */ JOBSTATE *pState);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IRegisteredJob * This,
            /* [retval][out] */ boolean *pEnabled);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IRegisteredJob * This,
            boolean Enabled);
        
        HRESULT ( STDMETHODCALLTYPE *Run )( 
            IRegisteredJob * This,
            /* [in] */ VARIANT params,
            /* [retval][out] */ IRunningJob **ppRetval);
        
        HRESULT ( STDMETHODCALLTYPE *GetInstances )( 
            IRegisteredJob * This,
            /* [retval][out] */ IRunningJobCollection **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateJob )( 
            IRegisteredJob * This,
            BSTR body,
            BSTR sddl,
            DWORD options);
        
        HRESULT ( STDMETHODCALLTYPE *SetCredentials )( 
            IRegisteredJob * This,
            BSTR UserId,
            BSTR Password);
        
        HRESULT ( STDMETHODCALLTYPE *GetCredentials )( 
            IRegisteredJob * This,
            /* [out] */ BSTR *pUserId);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastRunTime )( 
            IRegisteredJob * This,
            /* [retval][out] */ SYSTEMTIME *retVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastJobResult )( 
            IRegisteredJob * This,
            /* [retval][out] */ HRESULT *retVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_LastTaskResult )( 
            IRegisteredJob * This,
            /* [retval][out] */ DWORD *retVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumberOfMissedJobs )( 
            IRegisteredJob * This,
            /* [retval][out] */ DWORD *retVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NextRunTime )( 
            IRegisteredJob * This,
            /* [retval][out] */ SYSTEMTIME *pstLastRun);
        
        HRESULT ( STDMETHODCALLTYPE *GetRunTimes )( 
            IRegisteredJob * This,
            /* [in] */ const LPSYSTEMTIME pstBegin,
            /* [in] */ const LPSYSTEMTIME pstEnd,
            /* [out] */ WORD *pCount,
            /* [out] */ LPSYSTEMTIME *rgstTaskTimes);
        
        END_INTERFACE
    } IRegisteredJobVtbl;

    interface IRegisteredJob
    {
        CONST_VTBL struct IRegisteredJobVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRegisteredJob_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IRegisteredJob_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IRegisteredJob_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IRegisteredJob_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IRegisteredJob_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IRegisteredJob_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IRegisteredJob_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IRegisteredJob_get_Name(This,ppName)	\
    ( (This)->lpVtbl -> get_Name(This,ppName) ) 

#define IRegisteredJob_get_Path(This,ppPath)	\
    ( (This)->lpVtbl -> get_Path(This,ppPath) ) 

#define IRegisteredJob_get_DisplayName(This,pDisplayName)	\
    ( (This)->lpVtbl -> get_DisplayName(This,pDisplayName) ) 

#define IRegisteredJob_get_Description(This,pDescription)	\
    ( (This)->lpVtbl -> get_Description(This,pDescription) ) 

#define IRegisteredJob_get_XML(This,ppXML)	\
    ( (This)->lpVtbl -> get_XML(This,ppXML) ) 

#define IRegisteredJob_get_State(This,pState)	\
    ( (This)->lpVtbl -> get_State(This,pState) ) 

#define IRegisteredJob_get_Enabled(This,pEnabled)	\
    ( (This)->lpVtbl -> get_Enabled(This,pEnabled) ) 

#define IRegisteredJob_put_Enabled(This,Enabled)	\
    ( (This)->lpVtbl -> put_Enabled(This,Enabled) ) 

#define IRegisteredJob_Run(This,params,ppRetval)	\
    ( (This)->lpVtbl -> Run(This,params,ppRetval) ) 

#define IRegisteredJob_GetInstances(This,ppEnum)	\
    ( (This)->lpVtbl -> GetInstances(This,ppEnum) ) 

#define IRegisteredJob_UpdateJob(This,body,sddl,options)	\
    ( (This)->lpVtbl -> UpdateJob(This,body,sddl,options) ) 

#define IRegisteredJob_SetCredentials(This,UserId,Password)	\
    ( (This)->lpVtbl -> SetCredentials(This,UserId,Password) ) 

#define IRegisteredJob_GetCredentials(This,pUserId)	\
    ( (This)->lpVtbl -> GetCredentials(This,pUserId) ) 

#define IRegisteredJob_get_LastRunTime(This,retVal)	\
    ( (This)->lpVtbl -> get_LastRunTime(This,retVal) ) 

#define IRegisteredJob_get_LastJobResult(This,retVal)	\
    ( (This)->lpVtbl -> get_LastJobResult(This,retVal) ) 

#define IRegisteredJob_get_LastTaskResult(This,retVal)	\
    ( (This)->lpVtbl -> get_LastTaskResult(This,retVal) ) 

#define IRegisteredJob_get_NumberOfMissedJobs(This,retVal)	\
    ( (This)->lpVtbl -> get_NumberOfMissedJobs(This,retVal) ) 

#define IRegisteredJob_get_NextRunTime(This,pstLastRun)	\
    ( (This)->lpVtbl -> get_NextRunTime(This,pstLastRun) ) 

#define IRegisteredJob_GetRunTimes(This,pstBegin,pstEnd,pCount,rgstTaskTimes)	\
    ( (This)->lpVtbl -> GetRunTimes(This,pstBegin,pstEnd,pCount,rgstTaskTimes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_Name_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ BSTR *ppName);


void __RPC_STUB IRegisteredJob_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_Path_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ BSTR *ppPath);


void __RPC_STUB IRegisteredJob_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_DisplayName_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ BSTR *pDisplayName);


void __RPC_STUB IRegisteredJob_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_Description_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ BSTR *pDescription);


void __RPC_STUB IRegisteredJob_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_XML_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ BSTR *ppXML);


void __RPC_STUB IRegisteredJob_get_XML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_State_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ JOBSTATE *pState);


void __RPC_STUB IRegisteredJob_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_Enabled_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ boolean *pEnabled);


void __RPC_STUB IRegisteredJob_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_put_Enabled_Proxy( 
    IRegisteredJob * This,
    boolean Enabled);


void __RPC_STUB IRegisteredJob_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegisteredJob_Run_Proxy( 
    IRegisteredJob * This,
    /* [in] */ VARIANT params,
    /* [retval][out] */ IRunningJob **ppRetval);


void __RPC_STUB IRegisteredJob_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegisteredJob_GetInstances_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ IRunningJobCollection **ppEnum);


void __RPC_STUB IRegisteredJob_GetInstances_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegisteredJob_UpdateJob_Proxy( 
    IRegisteredJob * This,
    BSTR body,
    BSTR sddl,
    DWORD options);


void __RPC_STUB IRegisteredJob_UpdateJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegisteredJob_SetCredentials_Proxy( 
    IRegisteredJob * This,
    BSTR UserId,
    BSTR Password);


void __RPC_STUB IRegisteredJob_SetCredentials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegisteredJob_GetCredentials_Proxy( 
    IRegisteredJob * This,
    /* [out] */ BSTR *pUserId);


void __RPC_STUB IRegisteredJob_GetCredentials_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_LastRunTime_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ SYSTEMTIME *retVal);


void __RPC_STUB IRegisteredJob_get_LastRunTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_LastJobResult_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ HRESULT *retVal);


void __RPC_STUB IRegisteredJob_get_LastJobResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_LastTaskResult_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ DWORD *retVal);


void __RPC_STUB IRegisteredJob_get_LastTaskResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_NumberOfMissedJobs_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ DWORD *retVal);


void __RPC_STUB IRegisteredJob_get_NumberOfMissedJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IRegisteredJob_get_NextRunTime_Proxy( 
    IRegisteredJob * This,
    /* [retval][out] */ SYSTEMTIME *pstLastRun);


void __RPC_STUB IRegisteredJob_get_NextRunTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRegisteredJob_GetRunTimes_Proxy( 
    IRegisteredJob * This,
    /* [in] */ const LPSYSTEMTIME pstBegin,
    /* [in] */ const LPSYSTEMTIME pstEnd,
    /* [out] */ WORD *pCount,
    /* [out] */ LPSYSTEMTIME *rgstTaskTimes);


void __RPC_STUB IRegisteredJob_GetRunTimes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRegisteredJob_INTERFACE_DEFINED__ */


#ifndef __IJobCollection_INTERFACE_DEFINED__
#define __IJobCollection_INTERFACE_DEFINED__

/* interface IJobCollection */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IJobCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86627eb4-42a7-41e4-a4d9-ac33a72f2d52")
    IJobCollection : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *retVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ IRegisteredJob **ppJob) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IJobCollection * This,
            /* [retval][out] */ long *retVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IJobCollection * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ IRegisteredJob **ppJob);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IJobCollection * This,
            /* [retval][out] */ IUnknown **retVal);
        
        END_INTERFACE
    } IJobCollectionVtbl;

    interface IJobCollection
    {
        CONST_VTBL struct IJobCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobCollection_get_Count(This,retVal)	\
    ( (This)->lpVtbl -> get_Count(This,retVal) ) 

#define IJobCollection_get_Item(This,index,ppJob)	\
    ( (This)->lpVtbl -> get_Item(This,index,ppJob) ) 

#define IJobCollection_get__NewEnum(This,retVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobCollection_get_Count_Proxy( 
    IJobCollection * This,
    /* [retval][out] */ long *retVal);


void __RPC_STUB IJobCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobCollection_get_Item_Proxy( 
    IJobCollection * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ IRegisteredJob **ppJob);


void __RPC_STUB IJobCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobCollection_get__NewEnum_Proxy( 
    IJobCollection * This,
    /* [retval][out] */ IUnknown **retVal);


void __RPC_STUB IJobCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobCollection_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_jobsitf_0264 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_jobsitf_0264_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_jobsitf_0264_v0_0_s_ifspec;

#ifndef __IJobFolder_INTERFACE_DEFINED__
#define __IJobFolder_INTERFACE_DEFINED__

/* interface IJobFolder */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IJobFolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8cfac062-a080-4c15-9a88-aa7c2af80dfc")
    IJobFolder : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR *ppPath) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Jobs( 
            /* [retval][out] */ IJobCollection **ppJobs) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterJob( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR JobDefinition,
            /* [in] */ BSTR sddl,
            /* [in] */ DWORD flags,
            /* [retval][out] */ IRegisteredJob **ppJob) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveJob( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_SubFolders( 
            /* [retval][out] */ IJobFolderCollection **ppFolders) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateFolder( 
            /* [in] */ BSTR FolderName,
            /* [in] */ BSTR Sddl,
            /* [retval][out] */ IJobFolder **ppFolder) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveFolder( 
            BSTR FolderName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobFolder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobFolder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobFolder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobFolder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobFolder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobFolder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobFolder * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IJobFolder * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IJobFolder * This,
            /* [retval][out] */ BSTR *ppPath);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Jobs )( 
            IJobFolder * This,
            /* [retval][out] */ IJobCollection **ppJobs);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterJob )( 
            IJobFolder * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR JobDefinition,
            /* [in] */ BSTR sddl,
            /* [in] */ DWORD flags,
            /* [retval][out] */ IRegisteredJob **ppJob);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveJob )( 
            IJobFolder * This,
            /* [in] */ BSTR Name);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SubFolders )( 
            IJobFolder * This,
            /* [retval][out] */ IJobFolderCollection **ppFolders);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateFolder )( 
            IJobFolder * This,
            /* [in] */ BSTR FolderName,
            /* [in] */ BSTR Sddl,
            /* [retval][out] */ IJobFolder **ppFolder);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveFolder )( 
            IJobFolder * This,
            BSTR FolderName);
        
        END_INTERFACE
    } IJobFolderVtbl;

    interface IJobFolder
    {
        CONST_VTBL struct IJobFolderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobFolder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobFolder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobFolder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobFolder_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobFolder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobFolder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobFolder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobFolder_get_Name(This,pName)	\
    ( (This)->lpVtbl -> get_Name(This,pName) ) 

#define IJobFolder_get_Path(This,ppPath)	\
    ( (This)->lpVtbl -> get_Path(This,ppPath) ) 

#define IJobFolder_get_Jobs(This,ppJobs)	\
    ( (This)->lpVtbl -> get_Jobs(This,ppJobs) ) 

#define IJobFolder_RegisterJob(This,Name,JobDefinition,sddl,flags,ppJob)	\
    ( (This)->lpVtbl -> RegisterJob(This,Name,JobDefinition,sddl,flags,ppJob) ) 

#define IJobFolder_RemoveJob(This,Name)	\
    ( (This)->lpVtbl -> RemoveJob(This,Name) ) 

#define IJobFolder_get_SubFolders(This,ppFolders)	\
    ( (This)->lpVtbl -> get_SubFolders(This,ppFolders) ) 

#define IJobFolder_CreateFolder(This,FolderName,Sddl,ppFolder)	\
    ( (This)->lpVtbl -> CreateFolder(This,FolderName,Sddl,ppFolder) ) 

#define IJobFolder_RemoveFolder(This,FolderName)	\
    ( (This)->lpVtbl -> RemoveFolder(This,FolderName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolder_get_Name_Proxy( 
    IJobFolder * This,
    /* [retval][out] */ BSTR *pName);


void __RPC_STUB IJobFolder_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolder_get_Path_Proxy( 
    IJobFolder * This,
    /* [retval][out] */ BSTR *ppPath);


void __RPC_STUB IJobFolder_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolder_get_Jobs_Proxy( 
    IJobFolder * This,
    /* [retval][out] */ IJobCollection **ppJobs);


void __RPC_STUB IJobFolder_get_Jobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobFolder_RegisterJob_Proxy( 
    IJobFolder * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR JobDefinition,
    /* [in] */ BSTR sddl,
    /* [in] */ DWORD flags,
    /* [retval][out] */ IRegisteredJob **ppJob);


void __RPC_STUB IJobFolder_RegisterJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobFolder_RemoveJob_Proxy( 
    IJobFolder * This,
    /* [in] */ BSTR Name);


void __RPC_STUB IJobFolder_RemoveJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolder_get_SubFolders_Proxy( 
    IJobFolder * This,
    /* [retval][out] */ IJobFolderCollection **ppFolders);


void __RPC_STUB IJobFolder_get_SubFolders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobFolder_CreateFolder_Proxy( 
    IJobFolder * This,
    /* [in] */ BSTR FolderName,
    /* [in] */ BSTR Sddl,
    /* [retval][out] */ IJobFolder **ppFolder);


void __RPC_STUB IJobFolder_CreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobFolder_RemoveFolder_Proxy( 
    IJobFolder * This,
    BSTR FolderName);


void __RPC_STUB IJobFolder_RemoveFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobFolder_INTERFACE_DEFINED__ */


#ifndef __IJobFolderCollection_INTERFACE_DEFINED__
#define __IJobFolderCollection_INTERFACE_DEFINED__

/* interface IJobFolderCollection */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IJobFolderCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("79184a66-8664-423f-97f1-637356a5d812")
    IJobFolderCollection : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *retVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ IJobFolder **ppFolder) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobFolderCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobFolderCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobFolderCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobFolderCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobFolderCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobFolderCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobFolderCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobFolderCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IJobFolderCollection * This,
            /* [retval][out] */ long *retVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IJobFolderCollection * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ IJobFolder **ppFolder);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IJobFolderCollection * This,
            /* [retval][out] */ IUnknown **retVal);
        
        END_INTERFACE
    } IJobFolderCollectionVtbl;

    interface IJobFolderCollection
    {
        CONST_VTBL struct IJobFolderCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobFolderCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobFolderCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobFolderCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobFolderCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobFolderCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobFolderCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobFolderCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobFolderCollection_get_Count(This,retVal)	\
    ( (This)->lpVtbl -> get_Count(This,retVal) ) 

#define IJobFolderCollection_get_Item(This,index,ppFolder)	\
    ( (This)->lpVtbl -> get_Item(This,index,ppFolder) ) 

#define IJobFolderCollection_get__NewEnum(This,retVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolderCollection_get_Count_Proxy( 
    IJobFolderCollection * This,
    /* [retval][out] */ long *retVal);


void __RPC_STUB IJobFolderCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolderCollection_get_Item_Proxy( 
    IJobFolderCollection * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ IJobFolder **ppFolder);


void __RPC_STUB IJobFolderCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobFolderCollection_get__NewEnum_Proxy( 
    IJobFolderCollection * This,
    /* [retval][out] */ IUnknown **retVal);


void __RPC_STUB IJobFolderCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobFolderCollection_INTERFACE_DEFINED__ */


#ifndef __IJobService_INTERFACE_DEFINED__
#define __IJobService_INTERFACE_DEFINED__

/* interface IJobService */
/* [nonextensible][oleautomation][dual][uuid][object] */ 


EXTERN_C const IID IID_IJobService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2faba4c7-4da9-4013-9697-20cc3fd40f85")
    IJobService : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetFolder( 
            /* [in] */ BSTR path,
            /* [retval][out] */ IJobFolder **ppFolder) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetJob( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ IRegisteredJob **ppJob) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE HasFolder( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ VARIANT_BOOL *pExists) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE HasJob( 
            /* [in] */ BSTR Path,
            /* [retval][out] */ VARIANT_BOOL *pExists) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_RunningJobs( 
            /* [retval][out] */ IRunningJobCollection **retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterJob( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Folder,
            /* [in] */ BSTR Job,
            /* [in] */ DWORD flags,
            BSTR sddl,
            /* [retval][out] */ IRegisteredJob **retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveJob( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateFolder( 
            /* [in] */ BSTR Path,
            /* [in] */ BSTR sddl,
            /* [retval][out] */ IJobFolder **retVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveFolder( 
            /* [in] */ BSTR Path) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobService * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobService * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetFolder )( 
            IJobService * This,
            /* [in] */ BSTR path,
            /* [retval][out] */ IJobFolder **ppFolder);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetJob )( 
            IJobService * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ IRegisteredJob **ppJob);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *HasFolder )( 
            IJobService * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ VARIANT_BOOL *pExists);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *HasJob )( 
            IJobService * This,
            /* [in] */ BSTR Path,
            /* [retval][out] */ VARIANT_BOOL *pExists);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunningJobs )( 
            IJobService * This,
            /* [retval][out] */ IRunningJobCollection **retVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterJob )( 
            IJobService * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Folder,
            /* [in] */ BSTR Job,
            /* [in] */ DWORD flags,
            BSTR sddl,
            /* [retval][out] */ IRegisteredJob **retVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveJob )( 
            IJobService * This,
            /* [in] */ BSTR Path);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateFolder )( 
            IJobService * This,
            /* [in] */ BSTR Path,
            /* [in] */ BSTR sddl,
            /* [retval][out] */ IJobFolder **retVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RemoveFolder )( 
            IJobService * This,
            /* [in] */ BSTR Path);
        
        END_INTERFACE
    } IJobServiceVtbl;

    interface IJobService
    {
        CONST_VTBL struct IJobServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobService_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobService_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobService_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobService_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobService_GetFolder(This,path,ppFolder)	\
    ( (This)->lpVtbl -> GetFolder(This,path,ppFolder) ) 

#define IJobService_GetJob(This,Path,ppJob)	\
    ( (This)->lpVtbl -> GetJob(This,Path,ppJob) ) 

#define IJobService_HasFolder(This,Path,pExists)	\
    ( (This)->lpVtbl -> HasFolder(This,Path,pExists) ) 

#define IJobService_HasJob(This,Path,pExists)	\
    ( (This)->lpVtbl -> HasJob(This,Path,pExists) ) 

#define IJobService_get_RunningJobs(This,retVal)	\
    ( (This)->lpVtbl -> get_RunningJobs(This,retVal) ) 

#define IJobService_RegisterJob(This,Name,Folder,Job,flags,sddl,retVal)	\
    ( (This)->lpVtbl -> RegisterJob(This,Name,Folder,Job,flags,sddl,retVal) ) 

#define IJobService_RemoveJob(This,Path)	\
    ( (This)->lpVtbl -> RemoveJob(This,Path) ) 

#define IJobService_CreateFolder(This,Path,sddl,retVal)	\
    ( (This)->lpVtbl -> CreateFolder(This,Path,sddl,retVal) ) 

#define IJobService_RemoveFolder(This,Path)	\
    ( (This)->lpVtbl -> RemoveFolder(This,Path) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_GetFolder_Proxy( 
    IJobService * This,
    /* [in] */ BSTR path,
    /* [retval][out] */ IJobFolder **ppFolder);


void __RPC_STUB IJobService_GetFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_GetJob_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Path,
    /* [retval][out] */ IRegisteredJob **ppJob);


void __RPC_STUB IJobService_GetJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_HasFolder_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Path,
    /* [retval][out] */ VARIANT_BOOL *pExists);


void __RPC_STUB IJobService_HasFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_HasJob_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Path,
    /* [retval][out] */ VARIANT_BOOL *pExists);


void __RPC_STUB IJobService_HasJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IJobService_get_RunningJobs_Proxy( 
    IJobService * This,
    /* [retval][out] */ IRunningJobCollection **retVal);


void __RPC_STUB IJobService_get_RunningJobs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_RegisterJob_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Folder,
    /* [in] */ BSTR Job,
    /* [in] */ DWORD flags,
    BSTR sddl,
    /* [retval][out] */ IRegisteredJob **retVal);


void __RPC_STUB IJobService_RegisterJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_RemoveJob_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IJobService_RemoveJob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_CreateFolder_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Path,
    /* [in] */ BSTR sddl,
    /* [retval][out] */ IJobFolder **retVal);


void __RPC_STUB IJobService_CreateFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IJobService_RemoveFolder_Proxy( 
    IJobService * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IJobService_RemoveFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobService_INTERFACE_DEFINED__ */


#ifndef __IHandlerStatus_INTERFACE_DEFINED__
#define __IHandlerStatus_INTERFACE_DEFINED__

/* interface IHandlerStatus */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHandlerStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("eaec7a8f-27a0-4ddc-8675-14726a01a38a")
    IHandlerStatus : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UpdateStatus( 
            /* [in] */ short PercentComplete,
            /* [in] */ BSTR StatusMessage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TaskCompleted( 
            HRESULT taskErrCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHandlerStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHandlerStatus * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHandlerStatus * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHandlerStatus * This);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateStatus )( 
            IHandlerStatus * This,
            /* [in] */ short PercentComplete,
            /* [in] */ BSTR StatusMessage);
        
        HRESULT ( STDMETHODCALLTYPE *TaskCompleted )( 
            IHandlerStatus * This,
            HRESULT taskErrCode);
        
        END_INTERFACE
    } IHandlerStatusVtbl;

    interface IHandlerStatus
    {
        CONST_VTBL struct IHandlerStatusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHandlerStatus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHandlerStatus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHandlerStatus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHandlerStatus_UpdateStatus(This,PercentComplete,StatusMessage)	\
    ( (This)->lpVtbl -> UpdateStatus(This,PercentComplete,StatusMessage) ) 

#define IHandlerStatus_TaskCompleted(This,taskErrCode)	\
    ( (This)->lpVtbl -> TaskCompleted(This,taskErrCode) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHandlerStatus_UpdateStatus_Proxy( 
    IHandlerStatus * This,
    /* [in] */ short PercentComplete,
    /* [in] */ BSTR StatusMessage);


void __RPC_STUB IHandlerStatus_UpdateStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHandlerStatus_TaskCompleted_Proxy( 
    IHandlerStatus * This,
    HRESULT taskErrCode);


void __RPC_STUB IHandlerStatus_TaskCompleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHandlerStatus_INTERFACE_DEFINED__ */


#ifndef __IHandlerControl_INTERFACE_DEFINED__
#define __IHandlerControl_INTERFACE_DEFINED__

/* interface IHandlerControl */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHandlerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("839d7762-5121-4009-9234-4f0d19394f04")
    IHandlerControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StopTask( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PauseTask( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResumeTask( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHandlerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHandlerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHandlerControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHandlerControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *StopTask )( 
            IHandlerControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *PauseTask )( 
            IHandlerControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResumeTask )( 
            IHandlerControl * This);
        
        END_INTERFACE
    } IHandlerControlVtbl;

    interface IHandlerControl
    {
        CONST_VTBL struct IHandlerControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHandlerControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHandlerControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHandlerControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHandlerControl_StopTask(This)	\
    ( (This)->lpVtbl -> StopTask(This) ) 

#define IHandlerControl_PauseTask(This)	\
    ( (This)->lpVtbl -> PauseTask(This) ) 

#define IHandlerControl_ResumeTask(This)	\
    ( (This)->lpVtbl -> ResumeTask(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHandlerControl_StopTask_Proxy( 
    IHandlerControl * This);


void __RPC_STUB IHandlerControl_StopTask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHandlerControl_PauseTask_Proxy( 
    IHandlerControl * This);


void __RPC_STUB IHandlerControl_PauseTask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHandlerControl_ResumeTask_Proxy( 
    IHandlerControl * This);


void __RPC_STUB IHandlerControl_ResumeTask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHandlerControl_INTERFACE_DEFINED__ */


#ifndef __IHandler_INTERFACE_DEFINED__
#define __IHandler_INTERFACE_DEFINED__

/* interface IHandler */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b967ba46-1b66-4e03-baf3-44eadda414be")
    IHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RunTask( 
            /* [in] */ IUnknown *pHandlerServices,
            /* [in] */ BSTR XML) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *RunTask )( 
            IHandler * This,
            /* [in] */ IUnknown *pHandlerServices,
            /* [in] */ BSTR XML);
        
        END_INTERFACE
    } IHandlerVtbl;

    interface IHandler
    {
        CONST_VTBL struct IHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHandler_RunTask(This,pHandlerServices,XML)	\
    ( (This)->lpVtbl -> RunTask(This,pHandlerServices,XML) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHandler_RunTask_Proxy( 
    IHandler * This,
    /* [in] */ IUnknown *pHandlerServices,
    /* [in] */ BSTR XML);


void __RPC_STUB IHandler_RunTask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHandler_INTERFACE_DEFINED__ */


#ifndef __IAsyncHandler_INTERFACE_DEFINED__
#define __IAsyncHandler_INTERFACE_DEFINED__

/* interface IAsyncHandler */
/* [uuid][object] */ 


EXTERN_C const IID IID_IAsyncHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5aa86d2b-8d7e-48f8-aa21-4cdf19824877")
    IAsyncHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartTask( 
            /* [in] */ IUnknown *pHandlerServices,
            /* [in] */ BSTR XML) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAsyncHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAsyncHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAsyncHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAsyncHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartTask )( 
            IAsyncHandler * This,
            /* [in] */ IUnknown *pHandlerServices,
            /* [in] */ BSTR XML);
        
        END_INTERFACE
    } IAsyncHandlerVtbl;

    interface IAsyncHandler
    {
        CONST_VTBL struct IAsyncHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsyncHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAsyncHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAsyncHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAsyncHandler_StartTask(This,pHandlerServices,XML)	\
    ( (This)->lpVtbl -> StartTask(This,pHandlerServices,XML) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAsyncHandler_StartTask_Proxy( 
    IAsyncHandler * This,
    /* [in] */ IUnknown *pHandlerServices,
    /* [in] */ BSTR XML);


void __RPC_STUB IAsyncHandler_StartTask_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAsyncHandler_INTERFACE_DEFINED__ */



#ifndef __WMIJobs_LIBRARY_DEFINED__
#define __WMIJobs_LIBRARY_DEFINED__

/* library WMIJobs */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WMIJobs;

EXTERN_C const CLSID CLSID_JobService;

#ifdef __cplusplus

class DECLSPEC_UUID("0f87369f-a4e5-4cfc-bd3e-73e6154572dd")
JobService;
#endif
#endif /* __WMIJobs_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


