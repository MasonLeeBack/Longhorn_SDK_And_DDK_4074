/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 17 14:29:19 2000
 */
/* Compiler settings for OSPModify.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __OSPModify_h__
#define __OSPModify_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DataSource_FWD_DEFINED__
#define __DataSource_FWD_DEFINED__
typedef interface DataSource DataSource;
#endif 	/* __DataSource_FWD_DEFINED__ */


#ifndef __IModifyDataSource_FWD_DEFINED__
#define __IModifyDataSource_FWD_DEFINED__
typedef interface IModifyDataSource IModifyDataSource;
#endif 	/* __IModifyDataSource_FWD_DEFINED__ */


#ifndef __OLEDBSimpleProvider_FWD_DEFINED__
#define __OLEDBSimpleProvider_FWD_DEFINED__
typedef interface OLEDBSimpleProvider OLEDBSimpleProvider;
#endif 	/* __OLEDBSimpleProvider_FWD_DEFINED__ */


#ifndef __IModifyOSP_FWD_DEFINED__
#define __IModifyOSP_FWD_DEFINED__
typedef interface IModifyOSP IModifyOSP;
#endif 	/* __IModifyOSP_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __OSPModify_LIBRARY_DEFINED__
#define __OSPModify_LIBRARY_DEFINED__

/* library OSPModify */
/* [helpstring][version][uuid] */ 

typedef 
enum tagOSP_OPTIONS
    {	OSP_NOOPTS	= 0,
	OSP_READONLY	= 0x1,
	OSP_SINGLELISTENER	= 0x2,
	OSP_WRITEUNKNOWN	= 0x4,
	OSP_DBTYPE_ARRAY	= 0x10,
	OSP_ASYNCH	= 0x100,
	OSP_ASYNCH_ATOMIC	= 0x200,
	OSP_ASYNCH_COLUMNS	= 0x400
    }	OSP_OPTIONS;


EXTERN_C const IID LIBID_OSPModify;

#ifndef __DataSource_INTERFACE_DEFINED__
#define __DataSource_INTERFACE_DEFINED__

/* interface DataSource */
/* [object][oleautomation][uuid] */ 


EXTERN_C const IID IID_DataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7c0ffab3-cd84-11d0-949a-00a0c91110ed")
    DataSource : public IUnknown
    {
    public:
        virtual /* [restricted][hidden] */ HRESULT STDMETHODCALLTYPE getDataMember( 
            /* [in] */ DataMember bstrDM,
            /* [in] */ REFIID riid,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE getDataMemberName( 
            /* [in] */ long lIndex,
            /* [retval][out] */ DataMember __RPC_FAR *pbstrDM) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE getDataMemberCount( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE addDataSourceListener( 
            /* [in] */ DataSourceListener __RPC_FAR *pDSL) = 0;
        
        virtual /* [hidden] */ HRESULT STDMETHODCALLTYPE removeDataSourceListener( 
            /* [in] */ DataSourceListener __RPC_FAR *pDSL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct DataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DataSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DataSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DataSource __RPC_FAR * This);
        
        /* [restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMember )( 
            DataSource __RPC_FAR * This,
            /* [in] */ DataMember bstrDM,
            /* [in] */ REFIID riid,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMemberName )( 
            DataSource __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ DataMember __RPC_FAR *pbstrDM);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMemberCount )( 
            DataSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addDataSourceListener )( 
            DataSource __RPC_FAR * This,
            /* [in] */ DataSourceListener __RPC_FAR *pDSL);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeDataSourceListener )( 
            DataSource __RPC_FAR * This,
            /* [in] */ DataSourceListener __RPC_FAR *pDSL);
        
        END_INTERFACE
    } DataSourceVtbl;

    interface DataSource
    {
        CONST_VTBL struct DataSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DataSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DataSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DataSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DataSource_getDataMember(This,bstrDM,riid,ppunk)	\
    (This)->lpVtbl -> getDataMember(This,bstrDM,riid,ppunk)

#define DataSource_getDataMemberName(This,lIndex,pbstrDM)	\
    (This)->lpVtbl -> getDataMemberName(This,lIndex,pbstrDM)

#define DataSource_getDataMemberCount(This,plCount)	\
    (This)->lpVtbl -> getDataMemberCount(This,plCount)

#define DataSource_addDataSourceListener(This,pDSL)	\
    (This)->lpVtbl -> addDataSourceListener(This,pDSL)

#define DataSource_removeDataSourceListener(This,pDSL)	\
    (This)->lpVtbl -> removeDataSourceListener(This,pDSL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][hidden] */ HRESULT STDMETHODCALLTYPE DataSource_getDataMember_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ DataMember bstrDM,
    /* [in] */ REFIID riid,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB DataSource_getDataMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_getDataMemberName_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [retval][out] */ DataMember __RPC_FAR *pbstrDM);


void __RPC_STUB DataSource_getDataMemberName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_getDataMemberCount_Proxy( 
    DataSource __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB DataSource_getDataMemberCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_addDataSourceListener_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ DataSourceListener __RPC_FAR *pDSL);


void __RPC_STUB DataSource_addDataSourceListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden] */ HRESULT STDMETHODCALLTYPE DataSource_removeDataSourceListener_Proxy( 
    DataSource __RPC_FAR * This,
    /* [in] */ DataSourceListener __RPC_FAR *pDSL);


void __RPC_STUB DataSource_removeDataSourceListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __DataSource_INTERFACE_DEFINED__ */


#ifndef __IModifyDataSource_INTERFACE_DEFINED__
#define __IModifyDataSource_INTERFACE_DEFINED__

/* interface IModifyDataSource */
/* [oleautomation][unique][uuid][object] */ 


EXTERN_C const IID IID_IModifyDataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C03852E-17C1-11d1-9503-00C04FB66A50")
    IModifyDataSource : public DataSource
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE addDataMember( 
            /* [in] */ BSTR btrDM,
            /* [in] */ DB_LORDINAL cColumns,
            /* [in] */ DBROWCOUNT cRows,
            /* [in] */ long ulAsynchTime,
            /* [in] */ OSP_OPTIONS dwOptFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE modifyDataMember( 
            /* [in] */ BSTR strDM,
            /* [in] */ DB_LORDINAL cColumns,
            /* [in] */ DBROWCOUNT cRows,
            /* [in] */ long ulAsynchTime,
            /* [in] */ OSP_OPTIONS dwOptFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE removeDataMember( 
            /* [in] */ BSTR strDM) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModifyDataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IModifyDataSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IModifyDataSource __RPC_FAR * This);
        
        /* [restricted][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMember )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ DataMember bstrDM,
            /* [in] */ REFIID riid,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMemberName )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [retval][out] */ DataMember __RPC_FAR *pbstrDM);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getDataMemberCount )( 
            IModifyDataSource __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addDataSourceListener )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ DataSourceListener __RPC_FAR *pDSL);
        
        /* [hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeDataSourceListener )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ DataSourceListener __RPC_FAR *pDSL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addDataMember )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ BSTR btrDM,
            /* [in] */ DB_LORDINAL cColumns,
            /* [in] */ DBROWCOUNT cRows,
            /* [in] */ long ulAsynchTime,
            /* [in] */ OSP_OPTIONS dwOptFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *modifyDataMember )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ BSTR strDM,
            /* [in] */ DB_LORDINAL cColumns,
            /* [in] */ DBROWCOUNT cRows,
            /* [in] */ long ulAsynchTime,
            /* [in] */ OSP_OPTIONS dwOptFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeDataMember )( 
            IModifyDataSource __RPC_FAR * This,
            /* [in] */ BSTR strDM);
        
        END_INTERFACE
    } IModifyDataSourceVtbl;

    interface IModifyDataSource
    {
        CONST_VTBL struct IModifyDataSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModifyDataSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IModifyDataSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IModifyDataSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IModifyDataSource_getDataMember(This,bstrDM,riid,ppunk)	\
    (This)->lpVtbl -> getDataMember(This,bstrDM,riid,ppunk)

#define IModifyDataSource_getDataMemberName(This,lIndex,pbstrDM)	\
    (This)->lpVtbl -> getDataMemberName(This,lIndex,pbstrDM)

#define IModifyDataSource_getDataMemberCount(This,plCount)	\
    (This)->lpVtbl -> getDataMemberCount(This,plCount)

#define IModifyDataSource_addDataSourceListener(This,pDSL)	\
    (This)->lpVtbl -> addDataSourceListener(This,pDSL)

#define IModifyDataSource_removeDataSourceListener(This,pDSL)	\
    (This)->lpVtbl -> removeDataSourceListener(This,pDSL)


#define IModifyDataSource_addDataMember(This,btrDM,cColumns,cRows,ulAsynchTime,dwOptFlags)	\
    (This)->lpVtbl -> addDataMember(This,btrDM,cColumns,cRows,ulAsynchTime,dwOptFlags)

#define IModifyDataSource_modifyDataMember(This,strDM,cColumns,cRows,ulAsynchTime,dwOptFlags)	\
    (This)->lpVtbl -> modifyDataMember(This,strDM,cColumns,cRows,ulAsynchTime,dwOptFlags)

#define IModifyDataSource_removeDataMember(This,strDM)	\
    (This)->lpVtbl -> removeDataMember(This,strDM)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IModifyDataSource_addDataMember_Proxy( 
    IModifyDataSource __RPC_FAR * This,
    /* [in] */ BSTR btrDM,
    /* [in] */ DB_LORDINAL cColumns,
    /* [in] */ DBROWCOUNT cRows,
    /* [in] */ long ulAsynchTime,
    /* [in] */ OSP_OPTIONS dwOptFlags);


void __RPC_STUB IModifyDataSource_addDataMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModifyDataSource_modifyDataMember_Proxy( 
    IModifyDataSource __RPC_FAR * This,
    /* [in] */ BSTR strDM,
    /* [in] */ DB_LORDINAL cColumns,
    /* [in] */ DBROWCOUNT cRows,
    /* [in] */ long ulAsynchTime,
    /* [in] */ OSP_OPTIONS dwOptFlags);


void __RPC_STUB IModifyDataSource_modifyDataMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IModifyDataSource_removeDataMember_Proxy( 
    IModifyDataSource __RPC_FAR * This,
    /* [in] */ BSTR strDM);


void __RPC_STUB IModifyDataSource_removeDataMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModifyDataSource_INTERFACE_DEFINED__ */


#ifndef __OLEDBSimpleProvider_INTERFACE_DEFINED__
#define __OLEDBSimpleProvider_INTERFACE_DEFINED__

/* interface OLEDBSimpleProvider */
/* [version][oleautomation][unique][uuid][object] */ 


EXTERN_C const IID IID_OLEDBSimpleProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E0E270C0-C0BE-11d0-8FE4-00A0C90A6341")
    OLEDBSimpleProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE getRowCount( 
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getColumnCount( 
            /* [retval][out] */ DB_LORDINAL __RPC_FAR *pcColumns) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getRWStatus( 
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [retval][out] */ OSPRW __RPC_FAR *prwStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getVariant( 
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ OSPFORMAT format,
            /* [retval][out] */ VARIANT __RPC_FAR *pVar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setVariant( 
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ OSPFORMAT format,
            /* [in] */ VARIANT Var) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getLocale( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLocale) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE deleteRows( 
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsDeleted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE insertRows( 
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsInserted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE find( 
            /* [in] */ DBROWCOUNT iRowStart,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ VARIANT val,
            /* [in] */ OSPFIND findFlags,
            /* [in] */ OSPCOMP compType,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRowFound) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE addOLEDBSimpleProviderListener( 
            /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE removeOLEDBSimpleProviderListener( 
            /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE isAsync( 
            /* [retval][out] */ BOOL __RPC_FAR *pbAsynch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getEstimatedRows( 
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRows) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE stopTransfer( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct OLEDBSimpleProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            OLEDBSimpleProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            OLEDBSimpleProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRowCount )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getColumnCount )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [retval][out] */ DB_LORDINAL __RPC_FAR *pcColumns);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRWStatus )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [retval][out] */ OSPRW __RPC_FAR *prwStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getVariant )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ OSPFORMAT format,
            /* [retval][out] */ VARIANT __RPC_FAR *pVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setVariant )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ OSPFORMAT format,
            /* [in] */ VARIANT Var);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLocale )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLocale);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deleteRows )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsDeleted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertRows )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsInserted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *find )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRowStart,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ VARIANT val,
            /* [in] */ OSPFIND findFlags,
            /* [in] */ OSPCOMP compType,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRowFound);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addOLEDBSimpleProviderListener )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeOLEDBSimpleProviderListener )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isAsync )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbAsynch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getEstimatedRows )( 
            OLEDBSimpleProvider __RPC_FAR * This,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *stopTransfer )( 
            OLEDBSimpleProvider __RPC_FAR * This);
        
        END_INTERFACE
    } OLEDBSimpleProviderVtbl;

    interface OLEDBSimpleProvider
    {
        CONST_VTBL struct OLEDBSimpleProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define OLEDBSimpleProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define OLEDBSimpleProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define OLEDBSimpleProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define OLEDBSimpleProvider_getRowCount(This,pcRows)	\
    (This)->lpVtbl -> getRowCount(This,pcRows)

#define OLEDBSimpleProvider_getColumnCount(This,pcColumns)	\
    (This)->lpVtbl -> getColumnCount(This,pcColumns)

#define OLEDBSimpleProvider_getRWStatus(This,iRow,iColumn,prwStatus)	\
    (This)->lpVtbl -> getRWStatus(This,iRow,iColumn,prwStatus)

#define OLEDBSimpleProvider_getVariant(This,iRow,iColumn,format,pVar)	\
    (This)->lpVtbl -> getVariant(This,iRow,iColumn,format,pVar)

#define OLEDBSimpleProvider_setVariant(This,iRow,iColumn,format,Var)	\
    (This)->lpVtbl -> setVariant(This,iRow,iColumn,format,Var)

#define OLEDBSimpleProvider_getLocale(This,pbstrLocale)	\
    (This)->lpVtbl -> getLocale(This,pbstrLocale)

#define OLEDBSimpleProvider_deleteRows(This,iRow,cRows,pcRowsDeleted)	\
    (This)->lpVtbl -> deleteRows(This,iRow,cRows,pcRowsDeleted)

#define OLEDBSimpleProvider_insertRows(This,iRow,cRows,pcRowsInserted)	\
    (This)->lpVtbl -> insertRows(This,iRow,cRows,pcRowsInserted)

#define OLEDBSimpleProvider_find(This,iRowStart,iColumn,val,findFlags,compType,piRowFound)	\
    (This)->lpVtbl -> find(This,iRowStart,iColumn,val,findFlags,compType,piRowFound)

#define OLEDBSimpleProvider_addOLEDBSimpleProviderListener(This,pospIListener)	\
    (This)->lpVtbl -> addOLEDBSimpleProviderListener(This,pospIListener)

#define OLEDBSimpleProvider_removeOLEDBSimpleProviderListener(This,pospIListener)	\
    (This)->lpVtbl -> removeOLEDBSimpleProviderListener(This,pospIListener)

#define OLEDBSimpleProvider_isAsync(This,pbAsynch)	\
    (This)->lpVtbl -> isAsync(This,pbAsynch)

#define OLEDBSimpleProvider_getEstimatedRows(This,piRows)	\
    (This)->lpVtbl -> getEstimatedRows(This,piRows)

#define OLEDBSimpleProvider_stopTransfer(This)	\
    (This)->lpVtbl -> stopTransfer(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_getRowCount_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRows);


void __RPC_STUB OLEDBSimpleProvider_getRowCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_getColumnCount_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [retval][out] */ DB_LORDINAL __RPC_FAR *pcColumns);


void __RPC_STUB OLEDBSimpleProvider_getColumnCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_getRWStatus_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRow,
    /* [in] */ DB_LORDINAL iColumn,
    /* [retval][out] */ OSPRW __RPC_FAR *prwStatus);


void __RPC_STUB OLEDBSimpleProvider_getRWStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_getVariant_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRow,
    /* [in] */ DB_LORDINAL iColumn,
    /* [in] */ OSPFORMAT format,
    /* [retval][out] */ VARIANT __RPC_FAR *pVar);


void __RPC_STUB OLEDBSimpleProvider_getVariant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_setVariant_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRow,
    /* [in] */ DB_LORDINAL iColumn,
    /* [in] */ OSPFORMAT format,
    /* [in] */ VARIANT Var);


void __RPC_STUB OLEDBSimpleProvider_setVariant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_getLocale_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrLocale);


void __RPC_STUB OLEDBSimpleProvider_getLocale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_deleteRows_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRow,
    /* [in] */ DBROWCOUNT cRows,
    /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsDeleted);


void __RPC_STUB OLEDBSimpleProvider_deleteRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_insertRows_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRow,
    /* [in] */ DBROWCOUNT cRows,
    /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsInserted);


void __RPC_STUB OLEDBSimpleProvider_insertRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_find_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRowStart,
    /* [in] */ DB_LORDINAL iColumn,
    /* [in] */ VARIANT val,
    /* [in] */ OSPFIND findFlags,
    /* [in] */ OSPCOMP compType,
    /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRowFound);


void __RPC_STUB OLEDBSimpleProvider_find_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_addOLEDBSimpleProviderListener_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener);


void __RPC_STUB OLEDBSimpleProvider_addOLEDBSimpleProviderListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_removeOLEDBSimpleProviderListener_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener);


void __RPC_STUB OLEDBSimpleProvider_removeOLEDBSimpleProviderListener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_isAsync_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pbAsynch);


void __RPC_STUB OLEDBSimpleProvider_isAsync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_getEstimatedRows_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This,
    /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRows);


void __RPC_STUB OLEDBSimpleProvider_getEstimatedRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE OLEDBSimpleProvider_stopTransfer_Proxy( 
    OLEDBSimpleProvider __RPC_FAR * This);


void __RPC_STUB OLEDBSimpleProvider_stopTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __OLEDBSimpleProvider_INTERFACE_DEFINED__ */


#ifndef __IModifyOSP_INTERFACE_DEFINED__
#define __IModifyOSP_INTERFACE_DEFINED__

/* interface IModifyOSP */
/* [oleautomation][unique][uuid][object] */ 


EXTERN_C const IID IID_IModifyOSP;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C03852F-17C1-11d1-9503-00C04FB66A50")
    IModifyOSP : public OLEDBSimpleProvider
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE addRows( 
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IModifyOSPVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IModifyOSP __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IModifyOSP __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRowCount )( 
            IModifyOSP __RPC_FAR * This,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getColumnCount )( 
            IModifyOSP __RPC_FAR * This,
            /* [retval][out] */ DB_LORDINAL __RPC_FAR *pcColumns);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getRWStatus )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [retval][out] */ OSPRW __RPC_FAR *prwStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getVariant )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ OSPFORMAT format,
            /* [retval][out] */ VARIANT __RPC_FAR *pVar);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setVariant )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ OSPFORMAT format,
            /* [in] */ VARIANT Var);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getLocale )( 
            IModifyOSP __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrLocale);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *deleteRows )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsDeleted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertRows )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *pcRowsInserted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *find )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRowStart,
            /* [in] */ DB_LORDINAL iColumn,
            /* [in] */ VARIANT val,
            /* [in] */ OSPFIND findFlags,
            /* [in] */ OSPCOMP compType,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRowFound);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addOLEDBSimpleProviderListener )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeOLEDBSimpleProviderListener )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ OLEDBSimpleProviderListener __RPC_FAR *pospIListener);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *isAsync )( 
            IModifyOSP __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pbAsynch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getEstimatedRows )( 
            IModifyOSP __RPC_FAR * This,
            /* [retval][out] */ DBROWCOUNT __RPC_FAR *piRows);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *stopTransfer )( 
            IModifyOSP __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addRows )( 
            IModifyOSP __RPC_FAR * This,
            /* [in] */ DBROWCOUNT iRow,
            /* [in] */ DBROWCOUNT cRows);
        
        END_INTERFACE
    } IModifyOSPVtbl;

    interface IModifyOSP
    {
        CONST_VTBL struct IModifyOSPVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IModifyOSP_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IModifyOSP_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IModifyOSP_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IModifyOSP_getRowCount(This,pcRows)	\
    (This)->lpVtbl -> getRowCount(This,pcRows)

#define IModifyOSP_getColumnCount(This,pcColumns)	\
    (This)->lpVtbl -> getColumnCount(This,pcColumns)

#define IModifyOSP_getRWStatus(This,iRow,iColumn,prwStatus)	\
    (This)->lpVtbl -> getRWStatus(This,iRow,iColumn,prwStatus)

#define IModifyOSP_getVariant(This,iRow,iColumn,format,pVar)	\
    (This)->lpVtbl -> getVariant(This,iRow,iColumn,format,pVar)

#define IModifyOSP_setVariant(This,iRow,iColumn,format,Var)	\
    (This)->lpVtbl -> setVariant(This,iRow,iColumn,format,Var)

#define IModifyOSP_getLocale(This,pbstrLocale)	\
    (This)->lpVtbl -> getLocale(This,pbstrLocale)

#define IModifyOSP_deleteRows(This,iRow,cRows,pcRowsDeleted)	\
    (This)->lpVtbl -> deleteRows(This,iRow,cRows,pcRowsDeleted)

#define IModifyOSP_insertRows(This,iRow,cRows,pcRowsInserted)	\
    (This)->lpVtbl -> insertRows(This,iRow,cRows,pcRowsInserted)

#define IModifyOSP_find(This,iRowStart,iColumn,val,findFlags,compType,piRowFound)	\
    (This)->lpVtbl -> find(This,iRowStart,iColumn,val,findFlags,compType,piRowFound)

#define IModifyOSP_addOLEDBSimpleProviderListener(This,pospIListener)	\
    (This)->lpVtbl -> addOLEDBSimpleProviderListener(This,pospIListener)

#define IModifyOSP_removeOLEDBSimpleProviderListener(This,pospIListener)	\
    (This)->lpVtbl -> removeOLEDBSimpleProviderListener(This,pospIListener)

#define IModifyOSP_isAsync(This,pbAsynch)	\
    (This)->lpVtbl -> isAsync(This,pbAsynch)

#define IModifyOSP_getEstimatedRows(This,piRows)	\
    (This)->lpVtbl -> getEstimatedRows(This,piRows)

#define IModifyOSP_stopTransfer(This)	\
    (This)->lpVtbl -> stopTransfer(This)


#define IModifyOSP_addRows(This,iRow,cRows)	\
    (This)->lpVtbl -> addRows(This,iRow,cRows)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IModifyOSP_addRows_Proxy( 
    IModifyOSP __RPC_FAR * This,
    /* [in] */ DBROWCOUNT iRow,
    /* [in] */ DBROWCOUNT cRows);


void __RPC_STUB IModifyOSP_addRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IModifyOSP_INTERFACE_DEFINED__ */

#endif /* __OSPModify_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
