

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for jobbuilder.idl:
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


#ifndef __jobbuilder_h__
#define __jobbuilder_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IJobTrigger_FWD_DEFINED__
#define __IJobTrigger_FWD_DEFINED__
typedef interface IJobTrigger IJobTrigger;
#endif 	/* __IJobTrigger_FWD_DEFINED__ */


#ifndef __IEventTrigger_FWD_DEFINED__
#define __IEventTrigger_FWD_DEFINED__
typedef interface IEventTrigger IEventTrigger;
#endif 	/* __IEventTrigger_FWD_DEFINED__ */


#ifndef __ITimeTrigger_FWD_DEFINED__
#define __ITimeTrigger_FWD_DEFINED__
typedef interface ITimeTrigger ITimeTrigger;
#endif 	/* __ITimeTrigger_FWD_DEFINED__ */


#ifndef __IDailyTrigger_FWD_DEFINED__
#define __IDailyTrigger_FWD_DEFINED__
typedef interface IDailyTrigger IDailyTrigger;
#endif 	/* __IDailyTrigger_FWD_DEFINED__ */


#ifndef __IWeeklyTrigger_FWD_DEFINED__
#define __IWeeklyTrigger_FWD_DEFINED__
typedef interface IWeeklyTrigger IWeeklyTrigger;
#endif 	/* __IWeeklyTrigger_FWD_DEFINED__ */


#ifndef __IMonthlyTrigger_FWD_DEFINED__
#define __IMonthlyTrigger_FWD_DEFINED__
typedef interface IMonthlyTrigger IMonthlyTrigger;
#endif 	/* __IMonthlyTrigger_FWD_DEFINED__ */


#ifndef __IMonthlyDOWTrigger_FWD_DEFINED__
#define __IMonthlyDOWTrigger_FWD_DEFINED__
typedef interface IMonthlyDOWTrigger IMonthlyDOWTrigger;
#endif 	/* __IMonthlyDOWTrigger_FWD_DEFINED__ */


#ifndef __IIdleTrigger_FWD_DEFINED__
#define __IIdleTrigger_FWD_DEFINED__
typedef interface IIdleTrigger IIdleTrigger;
#endif 	/* __IIdleTrigger_FWD_DEFINED__ */


#ifndef __IImmediateTrigger_FWD_DEFINED__
#define __IImmediateTrigger_FWD_DEFINED__
typedef interface IImmediateTrigger IImmediateTrigger;
#endif 	/* __IImmediateTrigger_FWD_DEFINED__ */


#ifndef __IJobStep_FWD_DEFINED__
#define __IJobStep_FWD_DEFINED__
typedef interface IJobStep IJobStep;
#endif 	/* __IJobStep_FWD_DEFINED__ */


#ifndef __IExecutableStep_FWD_DEFINED__
#define __IExecutableStep_FWD_DEFINED__
typedef interface IExecutableStep IExecutableStep;
#endif 	/* __IExecutableStep_FWD_DEFINED__ */


#ifndef __IServiceStartStep_FWD_DEFINED__
#define __IServiceStartStep_FWD_DEFINED__
typedef interface IServiceStartStep IServiceStartStep;
#endif 	/* __IServiceStartStep_FWD_DEFINED__ */


#ifndef __IServiceStopStep_FWD_DEFINED__
#define __IServiceStopStep_FWD_DEFINED__
typedef interface IServiceStopStep IServiceStopStep;
#endif 	/* __IServiceStopStep_FWD_DEFINED__ */


#ifndef __IServicePauseStep_FWD_DEFINED__
#define __IServicePauseStep_FWD_DEFINED__
typedef interface IServicePauseStep IServicePauseStep;
#endif 	/* __IServicePauseStep_FWD_DEFINED__ */


#ifndef __IServiceResumeStep_FWD_DEFINED__
#define __IServiceResumeStep_FWD_DEFINED__
typedef interface IServiceResumeStep IServiceResumeStep;
#endif 	/* __IServiceResumeStep_FWD_DEFINED__ */


#ifndef __ITriggerCollection_FWD_DEFINED__
#define __ITriggerCollection_FWD_DEFINED__
typedef interface ITriggerCollection ITriggerCollection;
#endif 	/* __ITriggerCollection_FWD_DEFINED__ */


#ifndef __IStepCollection_FWD_DEFINED__
#define __IStepCollection_FWD_DEFINED__
typedef interface IStepCollection IStepCollection;
#endif 	/* __IStepCollection_FWD_DEFINED__ */


#ifndef __IJobBuilder_FWD_DEFINED__
#define __IJobBuilder_FWD_DEFINED__
typedef interface IJobBuilder IJobBuilder;
#endif 	/* __IJobBuilder_FWD_DEFINED__ */


#ifndef __JobBuilder_FWD_DEFINED__
#define __JobBuilder_FWD_DEFINED__

#ifdef __cplusplus
typedef class JobBuilder JobBuilder;
#else
typedef struct JobBuilder JobBuilder;
#endif /* __cplusplus */

#endif 	/* __JobBuilder_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __builderLib_LIBRARY_DEFINED__
#define __builderLib_LIBRARY_DEFINED__

/* library builderLib */
/* [helpstring][version][uuid] */ 

typedef 
enum tagTriggerType
    {	Event	= 0,
	Time	= 1,
	Daily	= 2,
	Weekly	= 3,
	Monthly	= 4,
	MonthlyDOW	= 5,
	Idle	= 6,
	Immediate	= 7
    } 	TriggerType;

typedef 
enum tagJobTimeUnit
    {	Seconds	= 0,
	Minutes	= 1,
	Hours	= 2,
	Days	= 3
    } 	JobTimeUnit;

typedef 
enum tagStepType
    {	ExecutableStep	= 0,
	ServiceStartStep	= 1,
	ServiceStopStep	= 2,
	ServicePauseStep	= 3,
	ServiceResumeStep	= 4,
	HandlerStep	= 5
    } 	StepType;


EXTERN_C const IID LIBID_builderLib;

#ifndef __IJobTrigger_INTERFACE_DEFINED__
#define __IJobTrigger_INTERFACE_DEFINED__

/* interface IJobTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IJobTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09941815-ea89-4b5b-89e0-2a773801fac3")
    IJobTrigger : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ TriggerType *pType) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RepetitionInterval( 
            /* [retval][out] */ DWORD *pInterval) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RepetitionInterval( 
            /* [in] */ DWORD interval) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RepetitionUnit( 
            /* [retval][out] */ JobTimeUnit *pUnit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RepetitionUnit( 
            /* [in] */ JobTimeUnit unit) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RepetitionDuration( 
            /* [retval][out] */ DWORD *pDuration) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RepetitionDuration( 
            /* [in] */ DWORD duration) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DurationUnit( 
            /* [retval][out] */ JobTimeUnit *pUnit) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DurationUnit( 
            /* [in] */ JobTimeUnit unit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IJobTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IJobTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IJobTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IJobTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IJobTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IJobTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IJobTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IJobTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IJobTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        END_INTERFACE
    } IJobTriggerVtbl;

    interface IJobTrigger
    {
        CONST_VTBL struct IJobTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IJobTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IJobTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IJobTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IJobTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IJobTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IJobTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IJobTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IJobTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IJobTrigger_get_Type_Proxy( 
    IJobTrigger * This,
    /* [retval][out] */ TriggerType *pType);


void __RPC_STUB IJobTrigger_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobTrigger_get_RepetitionInterval_Proxy( 
    IJobTrigger * This,
    /* [retval][out] */ DWORD *pInterval);


void __RPC_STUB IJobTrigger_get_RepetitionInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobTrigger_put_RepetitionInterval_Proxy( 
    IJobTrigger * This,
    /* [in] */ DWORD interval);


void __RPC_STUB IJobTrigger_put_RepetitionInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobTrigger_get_RepetitionUnit_Proxy( 
    IJobTrigger * This,
    /* [retval][out] */ JobTimeUnit *pUnit);


void __RPC_STUB IJobTrigger_get_RepetitionUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobTrigger_put_RepetitionUnit_Proxy( 
    IJobTrigger * This,
    /* [in] */ JobTimeUnit unit);


void __RPC_STUB IJobTrigger_put_RepetitionUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobTrigger_get_RepetitionDuration_Proxy( 
    IJobTrigger * This,
    /* [retval][out] */ DWORD *pDuration);


void __RPC_STUB IJobTrigger_get_RepetitionDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobTrigger_put_RepetitionDuration_Proxy( 
    IJobTrigger * This,
    /* [in] */ DWORD duration);


void __RPC_STUB IJobTrigger_put_RepetitionDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobTrigger_get_DurationUnit_Proxy( 
    IJobTrigger * This,
    /* [retval][out] */ JobTimeUnit *pUnit);


void __RPC_STUB IJobTrigger_get_DurationUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobTrigger_put_DurationUnit_Proxy( 
    IJobTrigger * This,
    /* [in] */ JobTimeUnit unit);


void __RPC_STUB IJobTrigger_put_DurationUnit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobTrigger_INTERFACE_DEFINED__ */


#ifndef __IEventTrigger_INTERFACE_DEFINED__
#define __IEventTrigger_INTERFACE_DEFINED__

/* interface IEventTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IEventTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d45b0167-9653-4eef-b94f-0732ca7af251")
    IEventTrigger : public IJobTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Query( 
            /* [retval][out] */ BSTR *query) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Query( 
            /* [in] */ BSTR query) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEventTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEventTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEventTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEventTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEventTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEventTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEventTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEventTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IEventTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IEventTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IEventTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IEventTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IEventTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IEventTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IEventTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IEventTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IEventTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Query )( 
            IEventTrigger * This,
            /* [retval][out] */ BSTR *query);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Query )( 
            IEventTrigger * This,
            /* [in] */ BSTR query);
        
        END_INTERFACE
    } IEventTriggerVtbl;

    interface IEventTrigger
    {
        CONST_VTBL struct IEventTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEventTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEventTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEventTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEventTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEventTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEventTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEventTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IEventTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IEventTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IEventTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IEventTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IEventTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IEventTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IEventTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IEventTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IEventTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define IEventTrigger_get_Query(This,query)	\
    ( (This)->lpVtbl -> get_Query(This,query) ) 

#define IEventTrigger_put_Query(This,query)	\
    ( (This)->lpVtbl -> put_Query(This,query) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IEventTrigger_get_Query_Proxy( 
    IEventTrigger * This,
    /* [retval][out] */ BSTR *query);


void __RPC_STUB IEventTrigger_get_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IEventTrigger_put_Query_Proxy( 
    IEventTrigger * This,
    /* [in] */ BSTR query);


void __RPC_STUB IEventTrigger_put_Query_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEventTrigger_INTERFACE_DEFINED__ */


#ifndef __ITimeTrigger_INTERFACE_DEFINED__
#define __ITimeTrigger_INTERFACE_DEFINED__

/* interface ITimeTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_ITimeTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b45747e0-eba7-4276-9f29-85c5bb300006")
    ITimeTrigger : public IJobTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ BSTR *starttime) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StartTime( 
            /* [in] */ BSTR starttime) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StopTime( 
            /* [retval][out] */ BSTR *stoptime) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StopTime( 
            /* [in] */ BSTR stoptime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITimeTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITimeTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITimeTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITimeTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITimeTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITimeTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITimeTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            ITimeTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            ITimeTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            ITimeTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            ITimeTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            ITimeTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            ITimeTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            ITimeTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            ITimeTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            ITimeTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            ITimeTrigger * This,
            /* [retval][out] */ BSTR *starttime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartTime )( 
            ITimeTrigger * This,
            /* [in] */ BSTR starttime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopTime )( 
            ITimeTrigger * This,
            /* [retval][out] */ BSTR *stoptime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopTime )( 
            ITimeTrigger * This,
            /* [in] */ BSTR stoptime);
        
        END_INTERFACE
    } ITimeTriggerVtbl;

    interface ITimeTrigger
    {
        CONST_VTBL struct ITimeTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITimeTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITimeTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITimeTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITimeTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITimeTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITimeTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITimeTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define ITimeTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define ITimeTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define ITimeTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define ITimeTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define ITimeTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define ITimeTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define ITimeTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define ITimeTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define ITimeTrigger_get_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> get_StartTime(This,starttime) ) 

#define ITimeTrigger_put_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> put_StartTime(This,starttime) ) 

#define ITimeTrigger_get_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> get_StopTime(This,stoptime) ) 

#define ITimeTrigger_put_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> put_StopTime(This,stoptime) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE ITimeTrigger_get_StartTime_Proxy( 
    ITimeTrigger * This,
    /* [retval][out] */ BSTR *starttime);


void __RPC_STUB ITimeTrigger_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITimeTrigger_put_StartTime_Proxy( 
    ITimeTrigger * This,
    /* [in] */ BSTR starttime);


void __RPC_STUB ITimeTrigger_put_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE ITimeTrigger_get_StopTime_Proxy( 
    ITimeTrigger * This,
    /* [retval][out] */ BSTR *stoptime);


void __RPC_STUB ITimeTrigger_get_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE ITimeTrigger_put_StopTime_Proxy( 
    ITimeTrigger * This,
    /* [in] */ BSTR stoptime);


void __RPC_STUB ITimeTrigger_put_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeTrigger_INTERFACE_DEFINED__ */


#ifndef __IDailyTrigger_INTERFACE_DEFINED__
#define __IDailyTrigger_INTERFACE_DEFINED__

/* interface IDailyTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IDailyTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("126c5cd8-b288-41d5-8dbf-e491446adc5c")
    IDailyTrigger : public ITimeTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Days( 
            /* [retval][out] */ short *days) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Days( 
            /* [in] */ short days) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDailyTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDailyTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDailyTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDailyTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDailyTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDailyTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDailyTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDailyTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IDailyTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IDailyTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IDailyTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IDailyTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IDailyTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IDailyTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IDailyTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IDailyTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IDailyTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            IDailyTrigger * This,
            /* [retval][out] */ BSTR *starttime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartTime )( 
            IDailyTrigger * This,
            /* [in] */ BSTR starttime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopTime )( 
            IDailyTrigger * This,
            /* [retval][out] */ BSTR *stoptime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopTime )( 
            IDailyTrigger * This,
            /* [in] */ BSTR stoptime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Days )( 
            IDailyTrigger * This,
            /* [retval][out] */ short *days);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Days )( 
            IDailyTrigger * This,
            /* [in] */ short days);
        
        END_INTERFACE
    } IDailyTriggerVtbl;

    interface IDailyTrigger
    {
        CONST_VTBL struct IDailyTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDailyTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDailyTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDailyTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDailyTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDailyTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDailyTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDailyTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IDailyTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IDailyTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IDailyTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IDailyTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IDailyTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IDailyTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IDailyTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IDailyTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IDailyTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define IDailyTrigger_get_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> get_StartTime(This,starttime) ) 

#define IDailyTrigger_put_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> put_StartTime(This,starttime) ) 

#define IDailyTrigger_get_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> get_StopTime(This,stoptime) ) 

#define IDailyTrigger_put_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> put_StopTime(This,stoptime) ) 


#define IDailyTrigger_get_Days(This,days)	\
    ( (This)->lpVtbl -> get_Days(This,days) ) 

#define IDailyTrigger_put_Days(This,days)	\
    ( (This)->lpVtbl -> put_Days(This,days) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IDailyTrigger_get_Days_Proxy( 
    IDailyTrigger * This,
    /* [retval][out] */ short *days);


void __RPC_STUB IDailyTrigger_get_Days_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IDailyTrigger_put_Days_Proxy( 
    IDailyTrigger * This,
    /* [in] */ short days);


void __RPC_STUB IDailyTrigger_put_Days_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDailyTrigger_INTERFACE_DEFINED__ */


#ifndef __IWeeklyTrigger_INTERFACE_DEFINED__
#define __IWeeklyTrigger_INTERFACE_DEFINED__

/* interface IWeeklyTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IWeeklyTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5038fc98-82ff-436d-8728-a512a57c9dc1")
    IWeeklyTrigger : public ITimeTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DaysOfWeek( 
            /* [retval][out] */ short *days) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DaysOfWeek( 
            /* [in] */ short days) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Weeks( 
            /* [retval][out] */ short *weeks) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Weeks( 
            /* [in] */ short weeks) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWeeklyTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWeeklyTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWeeklyTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWeeklyTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWeeklyTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWeeklyTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWeeklyTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWeeklyTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IWeeklyTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IWeeklyTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IWeeklyTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IWeeklyTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ BSTR *starttime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartTime )( 
            IWeeklyTrigger * This,
            /* [in] */ BSTR starttime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopTime )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ BSTR *stoptime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopTime )( 
            IWeeklyTrigger * This,
            /* [in] */ BSTR stoptime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DaysOfWeek )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ short *days);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DaysOfWeek )( 
            IWeeklyTrigger * This,
            /* [in] */ short days);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Weeks )( 
            IWeeklyTrigger * This,
            /* [retval][out] */ short *weeks);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Weeks )( 
            IWeeklyTrigger * This,
            /* [in] */ short weeks);
        
        END_INTERFACE
    } IWeeklyTriggerVtbl;

    interface IWeeklyTrigger
    {
        CONST_VTBL struct IWeeklyTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWeeklyTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWeeklyTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWeeklyTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWeeklyTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWeeklyTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWeeklyTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWeeklyTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWeeklyTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IWeeklyTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IWeeklyTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IWeeklyTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IWeeklyTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IWeeklyTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IWeeklyTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IWeeklyTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IWeeklyTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define IWeeklyTrigger_get_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> get_StartTime(This,starttime) ) 

#define IWeeklyTrigger_put_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> put_StartTime(This,starttime) ) 

#define IWeeklyTrigger_get_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> get_StopTime(This,stoptime) ) 

#define IWeeklyTrigger_put_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> put_StopTime(This,stoptime) ) 


#define IWeeklyTrigger_get_DaysOfWeek(This,days)	\
    ( (This)->lpVtbl -> get_DaysOfWeek(This,days) ) 

#define IWeeklyTrigger_put_DaysOfWeek(This,days)	\
    ( (This)->lpVtbl -> put_DaysOfWeek(This,days) ) 

#define IWeeklyTrigger_get_Weeks(This,weeks)	\
    ( (This)->lpVtbl -> get_Weeks(This,weeks) ) 

#define IWeeklyTrigger_put_Weeks(This,weeks)	\
    ( (This)->lpVtbl -> put_Weeks(This,weeks) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IWeeklyTrigger_get_DaysOfWeek_Proxy( 
    IWeeklyTrigger * This,
    /* [retval][out] */ short *days);


void __RPC_STUB IWeeklyTrigger_get_DaysOfWeek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IWeeklyTrigger_put_DaysOfWeek_Proxy( 
    IWeeklyTrigger * This,
    /* [in] */ short days);


void __RPC_STUB IWeeklyTrigger_put_DaysOfWeek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IWeeklyTrigger_get_Weeks_Proxy( 
    IWeeklyTrigger * This,
    /* [retval][out] */ short *weeks);


void __RPC_STUB IWeeklyTrigger_get_Weeks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IWeeklyTrigger_put_Weeks_Proxy( 
    IWeeklyTrigger * This,
    /* [in] */ short weeks);


void __RPC_STUB IWeeklyTrigger_put_Weeks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWeeklyTrigger_INTERFACE_DEFINED__ */


#ifndef __IMonthlyTrigger_INTERFACE_DEFINED__
#define __IMonthlyTrigger_INTERFACE_DEFINED__

/* interface IMonthlyTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IMonthlyTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("97c45ef1-6b02-4a1a-9c0e-1ebfba1500ac")
    IMonthlyTrigger : public ITimeTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DaysOfMonth( 
            /* [retval][out] */ long *days) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DaysOfMonth( 
            /* [in] */ long days) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MonthsOfYear( 
            /* [retval][out] */ short *months) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MonthsOfYear( 
            /* [in] */ short months) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMonthlyTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMonthlyTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMonthlyTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMonthlyTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMonthlyTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMonthlyTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMonthlyTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMonthlyTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IMonthlyTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IMonthlyTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IMonthlyTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IMonthlyTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ BSTR *starttime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartTime )( 
            IMonthlyTrigger * This,
            /* [in] */ BSTR starttime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopTime )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ BSTR *stoptime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopTime )( 
            IMonthlyTrigger * This,
            /* [in] */ BSTR stoptime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DaysOfMonth )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ long *days);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DaysOfMonth )( 
            IMonthlyTrigger * This,
            /* [in] */ long days);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MonthsOfYear )( 
            IMonthlyTrigger * This,
            /* [retval][out] */ short *months);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MonthsOfYear )( 
            IMonthlyTrigger * This,
            /* [in] */ short months);
        
        END_INTERFACE
    } IMonthlyTriggerVtbl;

    interface IMonthlyTrigger
    {
        CONST_VTBL struct IMonthlyTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMonthlyTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMonthlyTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMonthlyTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMonthlyTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMonthlyTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMonthlyTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMonthlyTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMonthlyTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IMonthlyTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IMonthlyTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IMonthlyTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IMonthlyTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IMonthlyTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IMonthlyTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IMonthlyTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IMonthlyTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define IMonthlyTrigger_get_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> get_StartTime(This,starttime) ) 

#define IMonthlyTrigger_put_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> put_StartTime(This,starttime) ) 

#define IMonthlyTrigger_get_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> get_StopTime(This,stoptime) ) 

#define IMonthlyTrigger_put_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> put_StopTime(This,stoptime) ) 


#define IMonthlyTrigger_get_DaysOfMonth(This,days)	\
    ( (This)->lpVtbl -> get_DaysOfMonth(This,days) ) 

#define IMonthlyTrigger_put_DaysOfMonth(This,days)	\
    ( (This)->lpVtbl -> put_DaysOfMonth(This,days) ) 

#define IMonthlyTrigger_get_MonthsOfYear(This,months)	\
    ( (This)->lpVtbl -> get_MonthsOfYear(This,months) ) 

#define IMonthlyTrigger_put_MonthsOfYear(This,months)	\
    ( (This)->lpVtbl -> put_MonthsOfYear(This,months) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMonthlyTrigger_get_DaysOfMonth_Proxy( 
    IMonthlyTrigger * This,
    /* [retval][out] */ long *days);


void __RPC_STUB IMonthlyTrigger_get_DaysOfMonth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMonthlyTrigger_put_DaysOfMonth_Proxy( 
    IMonthlyTrigger * This,
    /* [in] */ long days);


void __RPC_STUB IMonthlyTrigger_put_DaysOfMonth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMonthlyTrigger_get_MonthsOfYear_Proxy( 
    IMonthlyTrigger * This,
    /* [retval][out] */ short *months);


void __RPC_STUB IMonthlyTrigger_get_MonthsOfYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMonthlyTrigger_put_MonthsOfYear_Proxy( 
    IMonthlyTrigger * This,
    /* [in] */ short months);


void __RPC_STUB IMonthlyTrigger_put_MonthsOfYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMonthlyTrigger_INTERFACE_DEFINED__ */


#ifndef __IMonthlyDOWTrigger_INTERFACE_DEFINED__
#define __IMonthlyDOWTrigger_INTERFACE_DEFINED__

/* interface IMonthlyDOWTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IMonthlyDOWTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77d025a3-90fa-43aa-b52e-cda5499b946a")
    IMonthlyDOWTrigger : public ITimeTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DaysOfWeek( 
            /* [retval][out] */ short *days) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DaysOfWeek( 
            /* [in] */ short days) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WeeksOfMonth( 
            /* [retval][out] */ short *days) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WeeksOfMonth( 
            /* [in] */ short days) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MonthsOfYear( 
            /* [retval][out] */ short *months) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MonthsOfYear( 
            /* [in] */ short months) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMonthlyDOWTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMonthlyDOWTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMonthlyDOWTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMonthlyDOWTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartTime )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ BSTR *starttime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartTime )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ BSTR starttime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StopTime )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ BSTR *stoptime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StopTime )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ BSTR stoptime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DaysOfWeek )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ short *days);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DaysOfWeek )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ short days);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_WeeksOfMonth )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ short *days);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_WeeksOfMonth )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ short days);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_MonthsOfYear )( 
            IMonthlyDOWTrigger * This,
            /* [retval][out] */ short *months);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_MonthsOfYear )( 
            IMonthlyDOWTrigger * This,
            /* [in] */ short months);
        
        END_INTERFACE
    } IMonthlyDOWTriggerVtbl;

    interface IMonthlyDOWTrigger
    {
        CONST_VTBL struct IMonthlyDOWTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMonthlyDOWTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMonthlyDOWTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMonthlyDOWTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMonthlyDOWTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMonthlyDOWTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMonthlyDOWTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMonthlyDOWTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IMonthlyDOWTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IMonthlyDOWTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IMonthlyDOWTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IMonthlyDOWTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IMonthlyDOWTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IMonthlyDOWTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IMonthlyDOWTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IMonthlyDOWTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IMonthlyDOWTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define IMonthlyDOWTrigger_get_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> get_StartTime(This,starttime) ) 

#define IMonthlyDOWTrigger_put_StartTime(This,starttime)	\
    ( (This)->lpVtbl -> put_StartTime(This,starttime) ) 

#define IMonthlyDOWTrigger_get_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> get_StopTime(This,stoptime) ) 

#define IMonthlyDOWTrigger_put_StopTime(This,stoptime)	\
    ( (This)->lpVtbl -> put_StopTime(This,stoptime) ) 


#define IMonthlyDOWTrigger_get_DaysOfWeek(This,days)	\
    ( (This)->lpVtbl -> get_DaysOfWeek(This,days) ) 

#define IMonthlyDOWTrigger_put_DaysOfWeek(This,days)	\
    ( (This)->lpVtbl -> put_DaysOfWeek(This,days) ) 

#define IMonthlyDOWTrigger_get_WeeksOfMonth(This,days)	\
    ( (This)->lpVtbl -> get_WeeksOfMonth(This,days) ) 

#define IMonthlyDOWTrigger_put_WeeksOfMonth(This,days)	\
    ( (This)->lpVtbl -> put_WeeksOfMonth(This,days) ) 

#define IMonthlyDOWTrigger_get_MonthsOfYear(This,months)	\
    ( (This)->lpVtbl -> get_MonthsOfYear(This,months) ) 

#define IMonthlyDOWTrigger_put_MonthsOfYear(This,months)	\
    ( (This)->lpVtbl -> put_MonthsOfYear(This,months) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMonthlyDOWTrigger_get_DaysOfWeek_Proxy( 
    IMonthlyDOWTrigger * This,
    /* [retval][out] */ short *days);


void __RPC_STUB IMonthlyDOWTrigger_get_DaysOfWeek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMonthlyDOWTrigger_put_DaysOfWeek_Proxy( 
    IMonthlyDOWTrigger * This,
    /* [in] */ short days);


void __RPC_STUB IMonthlyDOWTrigger_put_DaysOfWeek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMonthlyDOWTrigger_get_WeeksOfMonth_Proxy( 
    IMonthlyDOWTrigger * This,
    /* [retval][out] */ short *days);


void __RPC_STUB IMonthlyDOWTrigger_get_WeeksOfMonth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMonthlyDOWTrigger_put_WeeksOfMonth_Proxy( 
    IMonthlyDOWTrigger * This,
    /* [in] */ short days);


void __RPC_STUB IMonthlyDOWTrigger_put_WeeksOfMonth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMonthlyDOWTrigger_get_MonthsOfYear_Proxy( 
    IMonthlyDOWTrigger * This,
    /* [retval][out] */ short *months);


void __RPC_STUB IMonthlyDOWTrigger_get_MonthsOfYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMonthlyDOWTrigger_put_MonthsOfYear_Proxy( 
    IMonthlyDOWTrigger * This,
    /* [in] */ short months);


void __RPC_STUB IMonthlyDOWTrigger_put_MonthsOfYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMonthlyDOWTrigger_INTERFACE_DEFINED__ */


#ifndef __IIdleTrigger_INTERFACE_DEFINED__
#define __IIdleTrigger_INTERFACE_DEFINED__

/* interface IIdleTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IIdleTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d537d2b0-9fb3-4d34-9739-1ff5ce7b1ef3")
    IIdleTrigger : public IJobTrigger
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Delay( 
            /* [retval][out] */ unsigned long *delay) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Delay( 
            /* [in] */ unsigned long delay) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIdleTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIdleTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIdleTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIdleTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIdleTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIdleTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIdleTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIdleTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IIdleTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IIdleTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IIdleTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IIdleTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IIdleTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IIdleTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IIdleTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IIdleTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IIdleTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Delay )( 
            IIdleTrigger * This,
            /* [retval][out] */ unsigned long *delay);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Delay )( 
            IIdleTrigger * This,
            /* [in] */ unsigned long delay);
        
        END_INTERFACE
    } IIdleTriggerVtbl;

    interface IIdleTrigger
    {
        CONST_VTBL struct IIdleTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIdleTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIdleTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIdleTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIdleTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IIdleTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IIdleTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IIdleTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IIdleTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IIdleTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IIdleTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IIdleTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IIdleTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IIdleTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IIdleTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IIdleTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IIdleTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#define IIdleTrigger_get_Delay(This,delay)	\
    ( (This)->lpVtbl -> get_Delay(This,delay) ) 

#define IIdleTrigger_put_Delay(This,delay)	\
    ( (This)->lpVtbl -> put_Delay(This,delay) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IIdleTrigger_get_Delay_Proxy( 
    IIdleTrigger * This,
    /* [retval][out] */ unsigned long *delay);


void __RPC_STUB IIdleTrigger_get_Delay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IIdleTrigger_put_Delay_Proxy( 
    IIdleTrigger * This,
    /* [in] */ unsigned long delay);


void __RPC_STUB IIdleTrigger_put_Delay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIdleTrigger_INTERFACE_DEFINED__ */


#ifndef __IImmediateTrigger_INTERFACE_DEFINED__
#define __IImmediateTrigger_INTERFACE_DEFINED__

/* interface IImmediateTrigger */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IImmediateTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4c8fec3a-c218-4e0c-b23d-629024db91a2")
    IImmediateTrigger : public IJobTrigger
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IImmediateTriggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImmediateTrigger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImmediateTrigger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImmediateTrigger * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IImmediateTrigger * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IImmediateTrigger * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IImmediateTrigger * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IImmediateTrigger * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IImmediateTrigger * This,
            /* [retval][out] */ TriggerType *pType);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionInterval )( 
            IImmediateTrigger * This,
            /* [retval][out] */ DWORD *pInterval);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionInterval )( 
            IImmediateTrigger * This,
            /* [in] */ DWORD interval);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionUnit )( 
            IImmediateTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionUnit )( 
            IImmediateTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepetitionDuration )( 
            IImmediateTrigger * This,
            /* [retval][out] */ DWORD *pDuration);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepetitionDuration )( 
            IImmediateTrigger * This,
            /* [in] */ DWORD duration);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DurationUnit )( 
            IImmediateTrigger * This,
            /* [retval][out] */ JobTimeUnit *pUnit);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DurationUnit )( 
            IImmediateTrigger * This,
            /* [in] */ JobTimeUnit unit);
        
        END_INTERFACE
    } IImmediateTriggerVtbl;

    interface IImmediateTrigger
    {
        CONST_VTBL struct IImmediateTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImmediateTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImmediateTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImmediateTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImmediateTrigger_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IImmediateTrigger_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IImmediateTrigger_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IImmediateTrigger_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IImmediateTrigger_get_Type(This,pType)	\
    ( (This)->lpVtbl -> get_Type(This,pType) ) 

#define IImmediateTrigger_get_RepetitionInterval(This,pInterval)	\
    ( (This)->lpVtbl -> get_RepetitionInterval(This,pInterval) ) 

#define IImmediateTrigger_put_RepetitionInterval(This,interval)	\
    ( (This)->lpVtbl -> put_RepetitionInterval(This,interval) ) 

#define IImmediateTrigger_get_RepetitionUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_RepetitionUnit(This,pUnit) ) 

#define IImmediateTrigger_put_RepetitionUnit(This,unit)	\
    ( (This)->lpVtbl -> put_RepetitionUnit(This,unit) ) 

#define IImmediateTrigger_get_RepetitionDuration(This,pDuration)	\
    ( (This)->lpVtbl -> get_RepetitionDuration(This,pDuration) ) 

#define IImmediateTrigger_put_RepetitionDuration(This,duration)	\
    ( (This)->lpVtbl -> put_RepetitionDuration(This,duration) ) 

#define IImmediateTrigger_get_DurationUnit(This,pUnit)	\
    ( (This)->lpVtbl -> get_DurationUnit(This,pUnit) ) 

#define IImmediateTrigger_put_DurationUnit(This,unit)	\
    ( (This)->lpVtbl -> put_DurationUnit(This,unit) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IImmediateTrigger_INTERFACE_DEFINED__ */


#ifndef __IJobStep_INTERFACE_DEFINED__
#define __IJobStep_INTERFACE_DEFINED__

/* interface IJobStep */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IJobStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("74345086-3cc0-4d48-b986-79e9db7ea8d2")
    IJobStep : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ StepType *type) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobStep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobStep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobStep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobStep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IJobStep * This,
            /* [retval][out] */ StepType *type);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IJobStep * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IJobStep * This,
            /* [in] */ BSTR name);
        
        END_INTERFACE
    } IJobStepVtbl;

    interface IJobStep
    {
        CONST_VTBL struct IJobStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobStep_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobStep_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobStep_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobStep_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobStep_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IJobStep_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IJobStep_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IJobStep_get_Type_Proxy( 
    IJobStep * This,
    /* [retval][out] */ StepType *type);


void __RPC_STUB IJobStep_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobStep_get_Name_Proxy( 
    IJobStep * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IJobStep_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobStep_put_Name_Proxy( 
    IJobStep * This,
    /* [in] */ BSTR name);


void __RPC_STUB IJobStep_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobStep_INTERFACE_DEFINED__ */


#ifndef __IExecutableStep_INTERFACE_DEFINED__
#define __IExecutableStep_INTERFACE_DEFINED__

/* interface IExecutableStep */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IExecutableStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4c3d624d-fd6b-49a3-b9b7-09cb3cd3f047")
    IExecutableStep : public IJobStep
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR *path) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ BSTR path) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Argument( 
            /* [retval][out] */ BSTR *argument) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Argument( 
            /* [in] */ BSTR argument) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExecutableStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IExecutableStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IExecutableStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IExecutableStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IExecutableStep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IExecutableStep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IExecutableStep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IExecutableStep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IExecutableStep * This,
            /* [retval][out] */ StepType *type);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IExecutableStep * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IExecutableStep * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Path )( 
            IExecutableStep * This,
            /* [retval][out] */ BSTR *path);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Path )( 
            IExecutableStep * This,
            /* [in] */ BSTR path);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Argument )( 
            IExecutableStep * This,
            /* [retval][out] */ BSTR *argument);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Argument )( 
            IExecutableStep * This,
            /* [in] */ BSTR argument);
        
        END_INTERFACE
    } IExecutableStepVtbl;

    interface IExecutableStep
    {
        CONST_VTBL struct IExecutableStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExecutableStep_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IExecutableStep_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IExecutableStep_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IExecutableStep_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IExecutableStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IExecutableStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IExecutableStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IExecutableStep_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IExecutableStep_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IExecutableStep_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 


#define IExecutableStep_get_Path(This,path)	\
    ( (This)->lpVtbl -> get_Path(This,path) ) 

#define IExecutableStep_put_Path(This,path)	\
    ( (This)->lpVtbl -> put_Path(This,path) ) 

#define IExecutableStep_get_Argument(This,argument)	\
    ( (This)->lpVtbl -> get_Argument(This,argument) ) 

#define IExecutableStep_put_Argument(This,argument)	\
    ( (This)->lpVtbl -> put_Argument(This,argument) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IExecutableStep_get_Path_Proxy( 
    IExecutableStep * This,
    /* [retval][out] */ BSTR *path);


void __RPC_STUB IExecutableStep_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IExecutableStep_put_Path_Proxy( 
    IExecutableStep * This,
    /* [in] */ BSTR path);


void __RPC_STUB IExecutableStep_put_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IExecutableStep_get_Argument_Proxy( 
    IExecutableStep * This,
    /* [retval][out] */ BSTR *argument);


void __RPC_STUB IExecutableStep_get_Argument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IExecutableStep_put_Argument_Proxy( 
    IExecutableStep * This,
    /* [in] */ BSTR argument);


void __RPC_STUB IExecutableStep_put_Argument_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExecutableStep_INTERFACE_DEFINED__ */


#ifndef __IServiceStartStep_INTERFACE_DEFINED__
#define __IServiceStartStep_INTERFACE_DEFINED__

/* interface IServiceStartStep */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IServiceStartStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4F11EB3-7103-4bfc-8D9E-A7EDC2D7E12F")
    IServiceStartStep : public IJobStep
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ServiceName( 
            /* [retval][out] */ BSTR *serviceName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ServiceName( 
            /* [in] */ BSTR serviceName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServiceStartStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceStartStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceStartStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceStartStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServiceStartStep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServiceStartStep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServiceStartStep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServiceStartStep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IServiceStartStep * This,
            /* [retval][out] */ StepType *type);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IServiceStartStep * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IServiceStartStep * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServiceName )( 
            IServiceStartStep * This,
            /* [retval][out] */ BSTR *serviceName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServiceName )( 
            IServiceStartStep * This,
            /* [in] */ BSTR serviceName);
        
        END_INTERFACE
    } IServiceStartStepVtbl;

    interface IServiceStartStep
    {
        CONST_VTBL struct IServiceStartStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceStartStep_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceStartStep_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceStartStep_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceStartStep_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServiceStartStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServiceStartStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServiceStartStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServiceStartStep_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IServiceStartStep_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IServiceStartStep_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 


#define IServiceStartStep_get_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> get_ServiceName(This,serviceName) ) 

#define IServiceStartStep_put_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> put_ServiceName(This,serviceName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IServiceStartStep_get_ServiceName_Proxy( 
    IServiceStartStep * This,
    /* [retval][out] */ BSTR *serviceName);


void __RPC_STUB IServiceStartStep_get_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IServiceStartStep_put_ServiceName_Proxy( 
    IServiceStartStep * This,
    /* [in] */ BSTR serviceName);


void __RPC_STUB IServiceStartStep_put_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServiceStartStep_INTERFACE_DEFINED__ */


#ifndef __IServiceStopStep_INTERFACE_DEFINED__
#define __IServiceStopStep_INTERFACE_DEFINED__

/* interface IServiceStopStep */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IServiceStopStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A8EB6CFE-B084-4fa7-90F4-A5112390BDC5")
    IServiceStopStep : public IJobStep
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ServiceName( 
            /* [retval][out] */ BSTR *serviceName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ServiceName( 
            /* [in] */ BSTR serviceName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServiceStopStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceStopStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceStopStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceStopStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServiceStopStep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServiceStopStep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServiceStopStep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServiceStopStep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IServiceStopStep * This,
            /* [retval][out] */ StepType *type);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IServiceStopStep * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IServiceStopStep * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServiceName )( 
            IServiceStopStep * This,
            /* [retval][out] */ BSTR *serviceName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServiceName )( 
            IServiceStopStep * This,
            /* [in] */ BSTR serviceName);
        
        END_INTERFACE
    } IServiceStopStepVtbl;

    interface IServiceStopStep
    {
        CONST_VTBL struct IServiceStopStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceStopStep_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceStopStep_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceStopStep_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceStopStep_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServiceStopStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServiceStopStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServiceStopStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServiceStopStep_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IServiceStopStep_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IServiceStopStep_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 


#define IServiceStopStep_get_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> get_ServiceName(This,serviceName) ) 

#define IServiceStopStep_put_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> put_ServiceName(This,serviceName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IServiceStopStep_get_ServiceName_Proxy( 
    IServiceStopStep * This,
    /* [retval][out] */ BSTR *serviceName);


void __RPC_STUB IServiceStopStep_get_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IServiceStopStep_put_ServiceName_Proxy( 
    IServiceStopStep * This,
    /* [in] */ BSTR serviceName);


void __RPC_STUB IServiceStopStep_put_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServiceStopStep_INTERFACE_DEFINED__ */


#ifndef __IServicePauseStep_INTERFACE_DEFINED__
#define __IServicePauseStep_INTERFACE_DEFINED__

/* interface IServicePauseStep */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IServicePauseStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7FC9D520-380A-448f-8685-9F03F3B53C88")
    IServicePauseStep : public IJobStep
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ServiceName( 
            /* [retval][out] */ BSTR *serviceName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ServiceName( 
            /* [in] */ BSTR serviceName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServicePauseStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServicePauseStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServicePauseStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServicePauseStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServicePauseStep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServicePauseStep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServicePauseStep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServicePauseStep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IServicePauseStep * This,
            /* [retval][out] */ StepType *type);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IServicePauseStep * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IServicePauseStep * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServiceName )( 
            IServicePauseStep * This,
            /* [retval][out] */ BSTR *serviceName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServiceName )( 
            IServicePauseStep * This,
            /* [in] */ BSTR serviceName);
        
        END_INTERFACE
    } IServicePauseStepVtbl;

    interface IServicePauseStep
    {
        CONST_VTBL struct IServicePauseStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServicePauseStep_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServicePauseStep_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServicePauseStep_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServicePauseStep_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServicePauseStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServicePauseStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServicePauseStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServicePauseStep_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IServicePauseStep_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IServicePauseStep_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 


#define IServicePauseStep_get_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> get_ServiceName(This,serviceName) ) 

#define IServicePauseStep_put_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> put_ServiceName(This,serviceName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IServicePauseStep_get_ServiceName_Proxy( 
    IServicePauseStep * This,
    /* [retval][out] */ BSTR *serviceName);


void __RPC_STUB IServicePauseStep_get_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IServicePauseStep_put_ServiceName_Proxy( 
    IServicePauseStep * This,
    /* [in] */ BSTR serviceName);


void __RPC_STUB IServicePauseStep_put_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServicePauseStep_INTERFACE_DEFINED__ */


#ifndef __IServiceResumeStep_INTERFACE_DEFINED__
#define __IServiceResumeStep_INTERFACE_DEFINED__

/* interface IServiceResumeStep */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IServiceResumeStep;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4D0CE83-BD64-4385-88BD-AE07A3C0E761")
    IServiceResumeStep : public IJobStep
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ServiceName( 
            /* [retval][out] */ BSTR *serviceName) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ServiceName( 
            /* [in] */ BSTR serviceName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServiceResumeStepVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceResumeStep * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceResumeStep * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceResumeStep * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServiceResumeStep * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServiceResumeStep * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServiceResumeStep * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServiceResumeStep * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IServiceResumeStep * This,
            /* [retval][out] */ StepType *type);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IServiceResumeStep * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IServiceResumeStep * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ServiceName )( 
            IServiceResumeStep * This,
            /* [retval][out] */ BSTR *serviceName);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ServiceName )( 
            IServiceResumeStep * This,
            /* [in] */ BSTR serviceName);
        
        END_INTERFACE
    } IServiceResumeStepVtbl;

    interface IServiceResumeStep
    {
        CONST_VTBL struct IServiceResumeStepVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceResumeStep_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceResumeStep_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceResumeStep_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceResumeStep_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServiceResumeStep_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServiceResumeStep_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServiceResumeStep_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServiceResumeStep_get_Type(This,type)	\
    ( (This)->lpVtbl -> get_Type(This,type) ) 

#define IServiceResumeStep_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IServiceResumeStep_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 


#define IServiceResumeStep_get_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> get_ServiceName(This,serviceName) ) 

#define IServiceResumeStep_put_ServiceName(This,serviceName)	\
    ( (This)->lpVtbl -> put_ServiceName(This,serviceName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IServiceResumeStep_get_ServiceName_Proxy( 
    IServiceResumeStep * This,
    /* [retval][out] */ BSTR *serviceName);


void __RPC_STUB IServiceResumeStep_get_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IServiceResumeStep_put_ServiceName_Proxy( 
    IServiceResumeStep * This,
    /* [in] */ BSTR serviceName);


void __RPC_STUB IServiceResumeStep_put_ServiceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IServiceResumeStep_INTERFACE_DEFINED__ */


#ifndef __ITriggerCollection_INTERFACE_DEFINED__
#define __ITriggerCollection_INTERFACE_DEFINED__

/* interface ITriggerCollection */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_ITriggerCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85df5081-1b24-4f32-878a-d9d14df4cb77")
    ITriggerCollection : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pCount) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IJobTrigger **ppTrigger) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ TriggerType type,
            /* [retval][out] */ IJobTrigger **ppTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITriggerCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITriggerCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITriggerCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITriggerCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITriggerCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITriggerCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITriggerCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITriggerCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ITriggerCollection * This,
            /* [retval][out] */ long *pCount);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ITriggerCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IJobTrigger **ppTrigger);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ITriggerCollection * This,
            /* [retval][out] */ IUnknown **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            ITriggerCollection * This,
            /* [in] */ TriggerType type,
            /* [retval][out] */ IJobTrigger **ppTrigger);
        
        HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ITriggerCollection * This,
            /* [in] */ VARIANT index);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            ITriggerCollection * This);
        
        END_INTERFACE
    } ITriggerCollectionVtbl;

    interface ITriggerCollection
    {
        CONST_VTBL struct ITriggerCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITriggerCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITriggerCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITriggerCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITriggerCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ITriggerCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ITriggerCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ITriggerCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ITriggerCollection_get_Count(This,pCount)	\
    ( (This)->lpVtbl -> get_Count(This,pCount) ) 

#define ITriggerCollection_get_Item(This,Index,ppTrigger)	\
    ( (This)->lpVtbl -> get_Item(This,Index,ppTrigger) ) 

#define ITriggerCollection_get__NewEnum(This,ppEnum)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppEnum) ) 

#define ITriggerCollection_Add(This,type,ppTrigger)	\
    ( (This)->lpVtbl -> Add(This,type,ppTrigger) ) 

#define ITriggerCollection_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ITriggerCollection_RemoveAll(This)	\
    ( (This)->lpVtbl -> RemoveAll(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITriggerCollection_get_Count_Proxy( 
    ITriggerCollection * This,
    /* [retval][out] */ long *pCount);


void __RPC_STUB ITriggerCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITriggerCollection_get_Item_Proxy( 
    ITriggerCollection * This,
    /* [in] */ long Index,
    /* [retval][out] */ IJobTrigger **ppTrigger);


void __RPC_STUB ITriggerCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE ITriggerCollection_get__NewEnum_Proxy( 
    ITriggerCollection * This,
    /* [retval][out] */ IUnknown **ppEnum);


void __RPC_STUB ITriggerCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITriggerCollection_Add_Proxy( 
    ITriggerCollection * This,
    /* [in] */ TriggerType type,
    /* [retval][out] */ IJobTrigger **ppTrigger);


void __RPC_STUB ITriggerCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITriggerCollection_Remove_Proxy( 
    ITriggerCollection * This,
    /* [in] */ VARIANT index);


void __RPC_STUB ITriggerCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITriggerCollection_RemoveAll_Proxy( 
    ITriggerCollection * This);


void __RPC_STUB ITriggerCollection_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITriggerCollection_INTERFACE_DEFINED__ */


#ifndef __IStepCollection_INTERFACE_DEFINED__
#define __IStepCollection_INTERFACE_DEFINED__

/* interface IStepCollection */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IStepCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bcec2274-1153-4e36-b706-3057402e9c68")
    IStepCollection : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pCount) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IJobStep **ppStep) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ StepType type,
            /* [retval][out] */ IJobStep **ppStep) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT index) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStepCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStepCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStepCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStepCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IStepCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IStepCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IStepCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IStepCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IStepCollection * This,
            /* [retval][out] */ long *pCount);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IStepCollection * This,
            /* [in] */ long Index,
            /* [retval][out] */ IJobStep **ppStep);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IStepCollection * This,
            /* [retval][out] */ IUnknown **ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            IStepCollection * This,
            /* [in] */ StepType type,
            /* [retval][out] */ IJobStep **ppStep);
        
        HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IStepCollection * This,
            /* [in] */ VARIANT index);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IStepCollection * This);
        
        END_INTERFACE
    } IStepCollectionVtbl;

    interface IStepCollection
    {
        CONST_VTBL struct IStepCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStepCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStepCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStepCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStepCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IStepCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IStepCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IStepCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IStepCollection_get_Count(This,pCount)	\
    ( (This)->lpVtbl -> get_Count(This,pCount) ) 

#define IStepCollection_get_Item(This,Index,ppStep)	\
    ( (This)->lpVtbl -> get_Item(This,Index,ppStep) ) 

#define IStepCollection_get__NewEnum(This,ppEnum)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppEnum) ) 

#define IStepCollection_Add(This,type,ppStep)	\
    ( (This)->lpVtbl -> Add(This,type,ppStep) ) 

#define IStepCollection_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define IStepCollection_RemoveAll(This)	\
    ( (This)->lpVtbl -> RemoveAll(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IStepCollection_get_Count_Proxy( 
    IStepCollection * This,
    /* [retval][out] */ long *pCount);


void __RPC_STUB IStepCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IStepCollection_get_Item_Proxy( 
    IStepCollection * This,
    /* [in] */ long Index,
    /* [retval][out] */ IJobStep **ppStep);


void __RPC_STUB IStepCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IStepCollection_get__NewEnum_Proxy( 
    IStepCollection * This,
    /* [retval][out] */ IUnknown **ppEnum);


void __RPC_STUB IStepCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStepCollection_Add_Proxy( 
    IStepCollection * This,
    /* [in] */ StepType type,
    /* [retval][out] */ IJobStep **ppStep);


void __RPC_STUB IStepCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStepCollection_Remove_Proxy( 
    IStepCollection * This,
    /* [in] */ VARIANT index);


void __RPC_STUB IStepCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStepCollection_RemoveAll_Proxy( 
    IStepCollection * This);


void __RPC_STUB IStepCollection_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStepCollection_INTERFACE_DEFINED__ */


#ifndef __IJobBuilder_INTERFACE_DEFINED__
#define __IJobBuilder_INTERFACE_DEFINED__

/* interface IJobBuilder */
/* [nonextensible][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IJobBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f5bc8fc5-536d-4f77-b852-fbc1356fdeb6")
    IJobBuilder : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Triggers( 
            /* [retval][out] */ ITriggerCollection **ppTriggers) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Steps( 
            /* [retval][out] */ IStepCollection **ppSteps) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_ErrorStep( 
            /* [retval][out] */ IJobStep **ppErrorStep) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_ErrorStep( 
            /* [in] */ IJobStep *pErrorStep) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_UserId( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_UserId( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR password) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR path) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR name,
            /* [in] */ BSTR path) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Author( 
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Author( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Documentation( 
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Documentation( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_UIVersion( 
            /* [retval][out] */ BSTR *retVal) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_UIVersion( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StartWhenAvailable( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StartWhenAvailable( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_NoHardTerminate( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_NoHardTerminate( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Restart( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Restart( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RunOnce( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RunOnce( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DeleteWhenFinished( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DeleteWhenFinished( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_KillPreviousInstance( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_KillPreviousInstance( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AllowMultipleInstances( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AllowMultipleInstances( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_KillIfGoingOnBatteries( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_KillIfGoingOnBatteries( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DontStartIfOnBatteries( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DontStartIfOnBatteries( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_KillOnIdleEnd( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_KillOnIdleEnd( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StartOnlyIfIdle( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StartOnlyIfIdle( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Hidden( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Hidden( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Disabled( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Disabled( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RunOnlyIfLoggedOn( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_RunOnlyIfLoggedOn( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Interactive( 
            /* [retval][out] */ VARIANT_BOOL *pb) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Interactive( 
            /* [in] */ VARIANT_BOOL b) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IJobBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IJobBuilder * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IJobBuilder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IJobBuilder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IJobBuilder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IJobBuilder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IJobBuilder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IJobBuilder * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Triggers )( 
            IJobBuilder * This,
            /* [retval][out] */ ITriggerCollection **ppTriggers);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Steps )( 
            IJobBuilder * This,
            /* [retval][out] */ IStepCollection **ppSteps);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorStep )( 
            IJobBuilder * This,
            /* [retval][out] */ IJobStep **ppErrorStep);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_ErrorStep )( 
            IJobBuilder * This,
            /* [in] */ IJobStep *pErrorStep);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_UserId )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_UserId )( 
            IJobBuilder * This,
            /* [in] */ BSTR name);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Password )( 
            IJobBuilder * This,
            /* [in] */ BSTR password);
        
        HRESULT ( STDMETHODCALLTYPE *Save )( 
            IJobBuilder * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR path);
        
        HRESULT ( STDMETHODCALLTYPE *Load )( 
            IJobBuilder * This,
            /* [in] */ BSTR name,
            /* [in] */ BSTR path);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *retVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            IJobBuilder * This,
            /* [in] */ BSTR val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Author )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *retVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Author )( 
            IJobBuilder * This,
            /* [in] */ BSTR val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayName )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *retVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DisplayName )( 
            IJobBuilder * This,
            /* [in] */ BSTR val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *retVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Version )( 
            IJobBuilder * This,
            /* [in] */ BSTR val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Documentation )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *retVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Documentation )( 
            IJobBuilder * This,
            /* [in] */ BSTR val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_UIVersion )( 
            IJobBuilder * This,
            /* [retval][out] */ BSTR *retVal);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_UIVersion )( 
            IJobBuilder * This,
            /* [in] */ BSTR val);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartWhenAvailable )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartWhenAvailable )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_NoHardTerminate )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_NoHardTerminate )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Restart )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Restart )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunOnce )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RunOnce )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DeleteWhenFinished )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DeleteWhenFinished )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_KillPreviousInstance )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_KillPreviousInstance )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_AllowMultipleInstances )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_AllowMultipleInstances )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_KillIfGoingOnBatteries )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_KillIfGoingOnBatteries )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_DontStartIfOnBatteries )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_DontStartIfOnBatteries )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_KillOnIdleEnd )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_KillOnIdleEnd )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartOnlyIfIdle )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartOnlyIfIdle )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Hidden )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Hidden )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Disabled )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Disabled )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_RunOnlyIfLoggedOn )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_RunOnlyIfLoggedOn )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Interactive )( 
            IJobBuilder * This,
            /* [retval][out] */ VARIANT_BOOL *pb);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Interactive )( 
            IJobBuilder * This,
            /* [in] */ VARIANT_BOOL b);
        
        END_INTERFACE
    } IJobBuilderVtbl;

    interface IJobBuilder
    {
        CONST_VTBL struct IJobBuilderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IJobBuilder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IJobBuilder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IJobBuilder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IJobBuilder_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IJobBuilder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IJobBuilder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IJobBuilder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IJobBuilder_get_Triggers(This,ppTriggers)	\
    ( (This)->lpVtbl -> get_Triggers(This,ppTriggers) ) 

#define IJobBuilder_get_Steps(This,ppSteps)	\
    ( (This)->lpVtbl -> get_Steps(This,ppSteps) ) 

#define IJobBuilder_get_ErrorStep(This,ppErrorStep)	\
    ( (This)->lpVtbl -> get_ErrorStep(This,ppErrorStep) ) 

#define IJobBuilder_put_ErrorStep(This,pErrorStep)	\
    ( (This)->lpVtbl -> put_ErrorStep(This,pErrorStep) ) 

#define IJobBuilder_get_UserId(This,name)	\
    ( (This)->lpVtbl -> get_UserId(This,name) ) 

#define IJobBuilder_put_UserId(This,name)	\
    ( (This)->lpVtbl -> put_UserId(This,name) ) 

#define IJobBuilder_put_Password(This,password)	\
    ( (This)->lpVtbl -> put_Password(This,password) ) 

#define IJobBuilder_Save(This,name,path)	\
    ( (This)->lpVtbl -> Save(This,name,path) ) 

#define IJobBuilder_Load(This,name,path)	\
    ( (This)->lpVtbl -> Load(This,name,path) ) 

#define IJobBuilder_get_Description(This,retVal)	\
    ( (This)->lpVtbl -> get_Description(This,retVal) ) 

#define IJobBuilder_put_Description(This,val)	\
    ( (This)->lpVtbl -> put_Description(This,val) ) 

#define IJobBuilder_get_Author(This,retVal)	\
    ( (This)->lpVtbl -> get_Author(This,retVal) ) 

#define IJobBuilder_put_Author(This,val)	\
    ( (This)->lpVtbl -> put_Author(This,val) ) 

#define IJobBuilder_get_DisplayName(This,retVal)	\
    ( (This)->lpVtbl -> get_DisplayName(This,retVal) ) 

#define IJobBuilder_put_DisplayName(This,val)	\
    ( (This)->lpVtbl -> put_DisplayName(This,val) ) 

#define IJobBuilder_get_Version(This,retVal)	\
    ( (This)->lpVtbl -> get_Version(This,retVal) ) 

#define IJobBuilder_put_Version(This,val)	\
    ( (This)->lpVtbl -> put_Version(This,val) ) 

#define IJobBuilder_get_Documentation(This,retVal)	\
    ( (This)->lpVtbl -> get_Documentation(This,retVal) ) 

#define IJobBuilder_put_Documentation(This,val)	\
    ( (This)->lpVtbl -> put_Documentation(This,val) ) 

#define IJobBuilder_get_UIVersion(This,retVal)	\
    ( (This)->lpVtbl -> get_UIVersion(This,retVal) ) 

#define IJobBuilder_put_UIVersion(This,val)	\
    ( (This)->lpVtbl -> put_UIVersion(This,val) ) 

#define IJobBuilder_get_StartWhenAvailable(This,pb)	\
    ( (This)->lpVtbl -> get_StartWhenAvailable(This,pb) ) 

#define IJobBuilder_put_StartWhenAvailable(This,b)	\
    ( (This)->lpVtbl -> put_StartWhenAvailable(This,b) ) 

#define IJobBuilder_get_NoHardTerminate(This,pb)	\
    ( (This)->lpVtbl -> get_NoHardTerminate(This,pb) ) 

#define IJobBuilder_put_NoHardTerminate(This,b)	\
    ( (This)->lpVtbl -> put_NoHardTerminate(This,b) ) 

#define IJobBuilder_get_Restart(This,pb)	\
    ( (This)->lpVtbl -> get_Restart(This,pb) ) 

#define IJobBuilder_put_Restart(This,b)	\
    ( (This)->lpVtbl -> put_Restart(This,b) ) 

#define IJobBuilder_get_RunOnce(This,pb)	\
    ( (This)->lpVtbl -> get_RunOnce(This,pb) ) 

#define IJobBuilder_put_RunOnce(This,b)	\
    ( (This)->lpVtbl -> put_RunOnce(This,b) ) 

#define IJobBuilder_get_DeleteWhenFinished(This,pb)	\
    ( (This)->lpVtbl -> get_DeleteWhenFinished(This,pb) ) 

#define IJobBuilder_put_DeleteWhenFinished(This,b)	\
    ( (This)->lpVtbl -> put_DeleteWhenFinished(This,b) ) 

#define IJobBuilder_get_KillPreviousInstance(This,pb)	\
    ( (This)->lpVtbl -> get_KillPreviousInstance(This,pb) ) 

#define IJobBuilder_put_KillPreviousInstance(This,b)	\
    ( (This)->lpVtbl -> put_KillPreviousInstance(This,b) ) 

#define IJobBuilder_get_AllowMultipleInstances(This,pb)	\
    ( (This)->lpVtbl -> get_AllowMultipleInstances(This,pb) ) 

#define IJobBuilder_put_AllowMultipleInstances(This,b)	\
    ( (This)->lpVtbl -> put_AllowMultipleInstances(This,b) ) 

#define IJobBuilder_get_KillIfGoingOnBatteries(This,pb)	\
    ( (This)->lpVtbl -> get_KillIfGoingOnBatteries(This,pb) ) 

#define IJobBuilder_put_KillIfGoingOnBatteries(This,b)	\
    ( (This)->lpVtbl -> put_KillIfGoingOnBatteries(This,b) ) 

#define IJobBuilder_get_DontStartIfOnBatteries(This,pb)	\
    ( (This)->lpVtbl -> get_DontStartIfOnBatteries(This,pb) ) 

#define IJobBuilder_put_DontStartIfOnBatteries(This,b)	\
    ( (This)->lpVtbl -> put_DontStartIfOnBatteries(This,b) ) 

#define IJobBuilder_get_KillOnIdleEnd(This,pb)	\
    ( (This)->lpVtbl -> get_KillOnIdleEnd(This,pb) ) 

#define IJobBuilder_put_KillOnIdleEnd(This,b)	\
    ( (This)->lpVtbl -> put_KillOnIdleEnd(This,b) ) 

#define IJobBuilder_get_StartOnlyIfIdle(This,pb)	\
    ( (This)->lpVtbl -> get_StartOnlyIfIdle(This,pb) ) 

#define IJobBuilder_put_StartOnlyIfIdle(This,b)	\
    ( (This)->lpVtbl -> put_StartOnlyIfIdle(This,b) ) 

#define IJobBuilder_get_Hidden(This,pb)	\
    ( (This)->lpVtbl -> get_Hidden(This,pb) ) 

#define IJobBuilder_put_Hidden(This,b)	\
    ( (This)->lpVtbl -> put_Hidden(This,b) ) 

#define IJobBuilder_get_Disabled(This,pb)	\
    ( (This)->lpVtbl -> get_Disabled(This,pb) ) 

#define IJobBuilder_put_Disabled(This,b)	\
    ( (This)->lpVtbl -> put_Disabled(This,b) ) 

#define IJobBuilder_get_RunOnlyIfLoggedOn(This,pb)	\
    ( (This)->lpVtbl -> get_RunOnlyIfLoggedOn(This,pb) ) 

#define IJobBuilder_put_RunOnlyIfLoggedOn(This,b)	\
    ( (This)->lpVtbl -> put_RunOnlyIfLoggedOn(This,b) ) 

#define IJobBuilder_get_Interactive(This,pb)	\
    ( (This)->lpVtbl -> get_Interactive(This,pb) ) 

#define IJobBuilder_put_Interactive(This,b)	\
    ( (This)->lpVtbl -> put_Interactive(This,b) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Triggers_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ ITriggerCollection **ppTriggers);


void __RPC_STUB IJobBuilder_get_Triggers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Steps_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ IStepCollection **ppSteps);


void __RPC_STUB IJobBuilder_get_Steps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_ErrorStep_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ IJobStep **ppErrorStep);


void __RPC_STUB IJobBuilder_get_ErrorStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_ErrorStep_Proxy( 
    IJobBuilder * This,
    /* [in] */ IJobStep *pErrorStep);


void __RPC_STUB IJobBuilder_put_ErrorStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_UserId_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *name);


void __RPC_STUB IJobBuilder_get_UserId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_UserId_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR name);


void __RPC_STUB IJobBuilder_put_UserId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Password_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR password);


void __RPC_STUB IJobBuilder_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IJobBuilder_Save_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR path);


void __RPC_STUB IJobBuilder_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IJobBuilder_Load_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR name,
    /* [in] */ BSTR path);


void __RPC_STUB IJobBuilder_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Description_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *retVal);


void __RPC_STUB IJobBuilder_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Description_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR val);


void __RPC_STUB IJobBuilder_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Author_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *retVal);


void __RPC_STUB IJobBuilder_get_Author_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Author_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR val);


void __RPC_STUB IJobBuilder_put_Author_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_DisplayName_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *retVal);


void __RPC_STUB IJobBuilder_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_DisplayName_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR val);


void __RPC_STUB IJobBuilder_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Version_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *retVal);


void __RPC_STUB IJobBuilder_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Version_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR val);


void __RPC_STUB IJobBuilder_put_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Documentation_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *retVal);


void __RPC_STUB IJobBuilder_get_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Documentation_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR val);


void __RPC_STUB IJobBuilder_put_Documentation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_UIVersion_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ BSTR *retVal);


void __RPC_STUB IJobBuilder_get_UIVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_UIVersion_Proxy( 
    IJobBuilder * This,
    /* [in] */ BSTR val);


void __RPC_STUB IJobBuilder_put_UIVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_StartWhenAvailable_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_StartWhenAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_StartWhenAvailable_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_StartWhenAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_NoHardTerminate_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_NoHardTerminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_NoHardTerminate_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_NoHardTerminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Restart_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_Restart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Restart_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_Restart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_RunOnce_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_RunOnce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_RunOnce_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_RunOnce_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_DeleteWhenFinished_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_DeleteWhenFinished_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_DeleteWhenFinished_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_DeleteWhenFinished_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_KillPreviousInstance_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_KillPreviousInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_KillPreviousInstance_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_KillPreviousInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_AllowMultipleInstances_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_AllowMultipleInstances_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_AllowMultipleInstances_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_AllowMultipleInstances_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_KillIfGoingOnBatteries_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_KillIfGoingOnBatteries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_KillIfGoingOnBatteries_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_KillIfGoingOnBatteries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_DontStartIfOnBatteries_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_DontStartIfOnBatteries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_DontStartIfOnBatteries_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_DontStartIfOnBatteries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_KillOnIdleEnd_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_KillOnIdleEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_KillOnIdleEnd_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_KillOnIdleEnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_StartOnlyIfIdle_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_StartOnlyIfIdle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_StartOnlyIfIdle_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_StartOnlyIfIdle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Hidden_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_Hidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Hidden_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_Hidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Disabled_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_Disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Disabled_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_Disabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_RunOnlyIfLoggedOn_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_RunOnlyIfLoggedOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_RunOnlyIfLoggedOn_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_RunOnlyIfLoggedOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IJobBuilder_get_Interactive_Proxy( 
    IJobBuilder * This,
    /* [retval][out] */ VARIANT_BOOL *pb);


void __RPC_STUB IJobBuilder_get_Interactive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IJobBuilder_put_Interactive_Proxy( 
    IJobBuilder * This,
    /* [in] */ VARIANT_BOOL b);


void __RPC_STUB IJobBuilder_put_Interactive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IJobBuilder_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_JobBuilder;

#ifdef __cplusplus

class DECLSPEC_UUID("99f2d7a7-bd1e-46d6-a3a9-e741533b74e4")
JobBuilder;
#endif
#endif /* __builderLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


