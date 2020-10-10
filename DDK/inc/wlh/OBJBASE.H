
//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  File:       objbase.h
//
//  Contents:   Component object model defintions.
//
//----------------------------------------------------------------------------

#include <rpc.h>
#include <rpcndr.h>

#if !defined( _OBJBASE_H_ )
#define _OBJBASE_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include <pshpack8.h>

#ifdef _MAC
#ifndef _WLM_NOFORCE_LIBS

#ifdef _WLMDLL
        #ifdef _DEBUG
                #pragma comment(lib, "oledlgd.lib")
                #pragma comment(lib, "msvcoled.lib")
        #else
                #pragma comment(lib, "oledlg.lib")
                #pragma comment(lib, "msvcole.lib")
        #endif
#else
        #ifdef _DEBUG
                #pragma comment(lib, "wlmoled.lib")
                #pragma comment(lib, "ole2uid.lib")
        #else
                #pragma comment(lib, "wlmole.lib")
                #pragma comment(lib, "ole2ui.lib")
        #endif
        #pragma data_seg(".drectve")
        static char _gszWlmOLEUIResourceDirective[] = "/macres:ole2ui.rsc";
        #pragma data_seg()
#endif

#pragma comment(lib, "uuid.lib")

#ifdef _DEBUG
    #pragma comment(lib, "ole2d.lib")
    #pragma comment(lib, "ole2autd.lib")
#else
    #pragma comment(lib, "ole2.lib")
    #pragma comment(lib, "ole2auto.lib")
#endif

#endif // !_WLM_NOFORCE_LIBS
#endif // _MAC

#ifdef _OLE32_
#define WINOLEAPI        STDAPI
#define WINOLEAPI_(type) STDAPI_(type)
#else

#ifdef _68K_
#ifndef REQUIRESAPPLEPASCAL
#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT HRESULT PASCAL
#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT type PASCAL
#else
#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT PASCAL HRESULT
#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT PASCAL type
#endif
#else
#define WINOLEAPI        EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define WINOLEAPI_(type) EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#endif

#endif

/****** Interface Declaration ***********************************************/

/*
 *      These are macros for declaring interfaces.  They exist so that
 *      a single definition of the interface is simulataneously a proper
 *      declaration of the interface structures (C++ abstract classes)
 *      for both C and C++.
 *
 *      DECLARE_INTERFACE(iface) is used to declare an interface that does
 *      not derive from a base interface.
 *      DECLARE_INTERFACE_(iface, baseiface) is used to declare an interface
 *      that does derive from a base interface.
 *
 *      By default if the source file has a .c extension the C version of
 *      the interface declaratations will be expanded; if it has a .cpp
 *      extension the C++ version will be expanded. if you want to force
 *      the C version expansion even though the source file has a .cpp
 *      extension, then define the macro "CINTERFACE".
 *      eg.     cl -DCINTERFACE file.cpp
 *
 *      Example Interface declaration:
 *
 *          #undef  INTERFACE
 *          #define INTERFACE   IClassFactory
 *
 *          DECLARE_INTERFACE_(IClassFactory, IUnknown)
 *          {
 *              // *** IUnknown methods ***
 *              STDMETHOD(QueryInterface) (THIS_
 *                                        REFIID riid,
 *                                        LPVOID FAR* ppvObj) PURE;
 *              STDMETHOD_(ULONG,AddRef) (THIS) PURE;
 *              STDMETHOD_(ULONG,Release) (THIS) PURE;
 *
 *              // *** IClassFactory methods ***
 *              STDMETHOD(CreateInstance) (THIS_
 *                                        LPUNKNOWN pUnkOuter,
 *                                        REFIID riid,
 *                                        LPVOID FAR* ppvObject) PURE;
 *          };
 *
 *      Example C++ expansion:
 *
 *          struct FAR IClassFactory : public IUnknown
 *          {
 *              virtual HRESULT STDMETHODCALLTYPE QueryInterface(
 *                                                  IID FAR& riid,
 *                                                  LPVOID FAR* ppvObj) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE AddRef(void) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE Release(void) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE CreateInstance(
 *                                              LPUNKNOWN pUnkOuter,
 *                                              IID FAR& riid,
 *                                              LPVOID FAR* ppvObject) = 0;
 *          };
 *
 *          NOTE: Our documentation says '#define interface class' but we use
 *          'struct' instead of 'class' to keep a lot of 'public:' lines
 *          out of the interfaces.  The 'FAR' forces the 'this' pointers to
 *          be far, which is what we need.
 *
 *      Example C expansion:
 *
 *          typedef struct IClassFactory
 *          {
 *              const struct IClassFactoryVtbl FAR* lpVtbl;
 *          } IClassFactory;
 *
 *          typedef struct IClassFactoryVtbl IClassFactoryVtbl;
 *
 *          struct IClassFactoryVtbl
 *          {
 *              HRESULT (STDMETHODCALLTYPE * QueryInterface) (
 *                                                  IClassFactory FAR* This,
 *                                                  IID FAR* riid,
 *                                                  LPVOID FAR* ppvObj) ;
 *              HRESULT (STDMETHODCALLTYPE * AddRef) (IClassFactory FAR* This) ;
 *              HRESULT (STDMETHODCALLTYPE * Release) (IClassFactory FAR* This) ;
 *              HRESULT (STDMETHODCALLTYPE * CreateInstance) (
 *                                                  IClassFactory FAR* This,
 *                                                  LPUNKNOWN pUnkOuter,
 *                                                  IID FAR* riid,
 *                                                  LPVOID FAR* ppvObject);
 *              HRESULT (STDMETHODCALLTYPE * LockServer) (
 *                                                  IClassFactory FAR* This,
 *                                                  BOOL fLock);
 *          };
 */

#if defined(__cplusplus) && !defined(CINTERFACE)
//#define interface               struct FAR
#define __STRUCT__ struct
#define interface __STRUCT__
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
#define STDMETHODV(method)       virtual HRESULT STDMETHODVCALLTYPE method
#define STDMETHODV_(type,method) virtual type STDMETHODVCALLTYPE method
#define PURE                    = 0
#define THIS_
#define THIS                    void
#define DECLARE_INTERFACE(iface)                        interface DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_(iface, baseiface)            interface DECLSPEC_NOVTABLE iface : public baseiface
#define DECLARE_INTERFACE_IID(iface, iid)               interface DECLSPEC_UUID(iid) DECLSPEC_NOVTABLE iface
#define DECLARE_INTERFACE_IID_(iface, baseiface, iid)   interface DECLSPEC_UUID(iid) DECLSPEC_NOVTABLE iface : public baseiface


#if !defined(BEGIN_INTERFACE)
#if defined(_MPPC_)  && \
    ( (defined(_MSC_VER) || defined(__SC__) || defined(__MWERKS__)) && \
    !defined(NO_NULL_VTABLE_ENTRY) )
   #define BEGIN_INTERFACE virtual void a() {}
   #define END_INTERFACE
#else
   #define BEGIN_INTERFACE
   #define END_INTERFACE
#endif
#endif

//  IID_PPV_ARGS(ppType)
//      ppType is the variable of type IType that will be filled
//
//      RESULTS in:  IID_IType, ppvType
//      will create a compiler error if wrong level of indirection is used.
//
#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), (static_cast<IUnknown *>(*(ppType)),reinterpret_cast<void**>(ppType))

#else

#define interface               struct

#define STDMETHOD(method)       HRESULT (STDMETHODCALLTYPE * method)
#define STDMETHOD_(type,method) type (STDMETHODCALLTYPE * method)
#define STDMETHODV(method)       HRESULT (STDMETHODVCALLTYPE * method)
#define STDMETHODV_(type,method) type (STDMETHODVCALLTYPE * method)

#if !defined(BEGIN_INTERFACE)
#if defined(_MPPC_)
    #define BEGIN_INTERFACE       void    *b;
    #define END_INTERFACE
#else
    #define BEGIN_INTERFACE
    #define END_INTERFACE
#endif
#endif


#define PURE
#define THIS_                   INTERFACE FAR* This,
#define THIS                    INTERFACE FAR* This
#ifdef CONST_VTABLE
#undef CONST_VTBL
#define CONST_VTBL const
#define DECLARE_INTERFACE(iface)    typedef interface iface { \
                                    const struct iface##Vtbl FAR* lpVtbl; \
                                } iface; \
                                typedef const struct iface##Vtbl iface##Vtbl; \
                                const struct iface##Vtbl
#else
#undef CONST_VTBL
#define CONST_VTBL
#define DECLARE_INTERFACE(iface)    typedef interface iface { \
                                    struct iface##Vtbl FAR* lpVtbl; \
                                } iface; \
                                typedef struct iface##Vtbl iface##Vtbl; \
                                struct iface##Vtbl
#endif
#define DECLARE_INTERFACE_(iface, baseiface)            DECLARE_INTERFACE(iface)
#define DECLARE_INTERFACE_IID(iface, iid)               DECLARE_INTERFACE(iface)
#define DECLARE_INTERFACE_IID_(iface, baseiface, iid)   DECLARE_INTERFACE_(iface, baseiface)
#endif




/****** Additional basic types **********************************************/


#ifndef FARSTRUCT
#ifdef __cplusplus
#define FARSTRUCT   FAR
#else
#define FARSTRUCT
#endif  // __cplusplus
#endif  // FARSTRUCT



#ifndef HUGEP
#if defined(_WIN32) || defined(_MPPC_)
#define HUGEP
#else
#define HUGEP __huge
#endif // WIN32
#endif // HUGEP


#ifdef _MAC
#if !defined(OLE2ANSI)
#define OLE2ANSI
#endif
#endif

#include <stdlib.h>

#define LISet32(li, v) ((li).HighPart = ((LONG) (v)) < 0 ? -1 : 0, (li).LowPart = (v))

#define ULISet32(li, v) ((li).HighPart = 0, (li).LowPart = (v))






#define CLSCTX_INPROC           (CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER)

// With DCOM, CLSCTX_REMOTE_SERVER should be included
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
#define CLSCTX_ALL              (CLSCTX_INPROC_SERVER| \
                                 CLSCTX_INPROC_HANDLER| \
                                 CLSCTX_LOCAL_SERVER| \
                                 CLSCTX_REMOTE_SERVER)

#define CLSCTX_SERVER           (CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER|CLSCTX_REMOTE_SERVER)
#else
#define CLSCTX_ALL              (CLSCTX_INPROC_SERVER| \
                                 CLSCTX_INPROC_HANDLER| \
                                 CLSCTX_LOCAL_SERVER )

#define CLSCTX_SERVER           (CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER)
#endif


// class registration flags; passed to CoRegisterClassObject
typedef enum tagREGCLS
{
    REGCLS_SINGLEUSE = 0,       // class object only generates one instance
    REGCLS_MULTIPLEUSE = 1,     // same class object genereates multiple inst.
                                // and local automatically goes into inproc tbl.
    REGCLS_MULTI_SEPARATE = 2,  // multiple use, but separate control over each
                                // context.
    REGCLS_SUSPENDED      = 4,  // register is as suspended, will be activated
                                // when app calls CoResumeClassObjects
    REGCLS_SURROGATE      = 8   // must be used when a surrogate process
                                // is registering a class object that will be
                                // loaded in the surrogate
} REGCLS;

// interface marshaling definitions
#define MARSHALINTERFACE_MIN 500 // minimum number of bytes for interface marshl


//
// Common typedefs for paramaters used in Storage API's, gleamed from storage.h
// Also contains Storage error codes, which should be moved into the storage
// idl files.
//


#define CWCSTORAGENAME 32

/* Storage instantiation modes */
#define STGM_DIRECT             0x00000000L
#define STGM_TRANSACTED         0x00010000L
#define STGM_SIMPLE             0x08000000L

#define STGM_READ               0x00000000L
#define STGM_WRITE              0x00000001L
#define STGM_READWRITE          0x00000002L

#define STGM_SHARE_DENY_NONE    0x00000040L
#define STGM_SHARE_DENY_READ    0x00000030L
#define STGM_SHARE_DENY_WRITE   0x00000020L
#define STGM_SHARE_EXCLUSIVE    0x00000010L

#define STGM_PRIORITY           0x00040000L
#define STGM_DELETEONRELEASE    0x04000000L
#if (WINVER >= 400)
#define STGM_NOSCRATCH          0x00100000L
#endif /* WINVER */

#define STGM_CREATE             0x00001000L
#define STGM_CONVERT            0x00020000L
#define STGM_FAILIFTHERE        0x00000000L

#define STGM_NOSNAPSHOT         0x00200000L
#if (_WIN32_WINNT >= 0x0500)
#define STGM_DIRECT_SWMR        0x00400000L
#endif

/*  flags for internet asyncronous and layout docfile */
#define ASYNC_MODE_COMPATIBILITY    0x00000001L
#define ASYNC_MODE_DEFAULT          0x00000000L

#define STGTY_REPEAT                0x00000100L
#define STG_TOEND                   0xFFFFFFFFL

#define STG_LAYOUT_SEQUENTIAL       0x00000000L
#define STG_LAYOUT_INTERLEAVED      0x00000001L

#define STGFMT_STORAGE          0
#define STGFMT_NATIVE           1
#define STGFMT_FILE             3
#define STGFMT_ANY              4
#define STGFMT_DOCFILE          5

// This is a legacy define to allow old component to builds
#define STGFMT_DOCUMENT         0

/* here is where we pull in the MIDL generated headers for the interfaces */
typedef interface    IRpcStubBuffer     IRpcStubBuffer;
typedef interface    IRpcChannelBuffer  IRpcChannelBuffer;

#include <wtypes.h>
#include <unknwn.h>
#include <objidl.h>

#ifdef _OLE32_
#ifdef _OLE32PRIV_
BOOL _fastcall wIsEqualGUID(REFGUID rguid1, REFGUID rguid2);
#define IsEqualGUID(rguid1, rguid2) wIsEqualGUID(rguid1, rguid2)
#else
#define __INLINE_ISEQUAL_GUID
#endif  // _OLE32PRIV_
#endif  // _OLE32_

#include <guiddef.h>

#ifndef INITGUID
#include <cguid.h>
#endif

// COM initialization flags; passed to CoInitialize.
typedef enum tagCOINIT
{
  COINIT_APARTMENTTHREADED  = 0x2,      // Apartment model

#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
  // These constants are only valid on Windows NT 4.0
  COINIT_MULTITHREADED      = 0x0,      // OLE calls objects on any thread.
  COINIT_DISABLE_OLE1DDE    = 0x4,      // Don't use DDE for Ole1 support.
  COINIT_SPEED_OVER_MEMORY  = 0x8,      // Trade memory for speed.
#endif // DCOM
} COINIT;





/****** STD Object API Prototypes *****************************************/

WINOLEAPI_(DWORD) CoBuildVersion( VOID );

/* init/uninit */

WINOLEAPI  CoInitialize(IN LPVOID pvReserved);
WINOLEAPI_(void)  CoUninitialize(void);
WINOLEAPI  CoGetMalloc(IN DWORD dwMemContext, OUT LPMALLOC FAR* ppMalloc);
WINOLEAPI_(DWORD) CoGetCurrentProcess(void);
WINOLEAPI  CoRegisterMallocSpy(IN LPMALLOCSPY pMallocSpy);
WINOLEAPI  CoRevokeMallocSpy(void);
WINOLEAPI  CoCreateStandardMalloc(IN DWORD memctx, OUT IMalloc FAR* FAR* ppMalloc);

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM

WINOLEAPI  CoInitializeEx(IN LPVOID pvReserved, IN DWORD dwCoInit);


WINOLEAPI  CoGetCallerTID( LPDWORD lpdwTID );
#endif // DCOM

#if (_WIN32_WINNT >= 0x0501)

WINOLEAPI  CoRegisterInitializeSpy(IN LPINITIALIZESPY pSpy, OUT ULARGE_INTEGER *puliCookie);
WINOLEAPI  CoRevokeInitializeSpy(IN ULARGE_INTEGER uliCookie);

WINOLEAPI  CoGetContextToken(ULONG_PTR* pToken);
#endif

#if (_WIN32_WINNT >= 0x0600 )

WINOLEAPI  CoSetApartmentLockState(IN APTTYPE eAptType, IN BOOL fLock);
#endif

#if DBG == 1
WINOLEAPI_(ULONG) DebugCoGetRpcFault( void );
WINOLEAPI_(void) DebugCoSetRpcFault( ULONG );
#endif

#if (_WIN32_WINT >= 0x0500)

typedef struct tagSOleTlsData
{
    void *pvReserved0[2];
    DWORD dwReserved0[3];
    void *pvReserved1[1];
    DWORD dwReserved1[3];
    void *pvReserved2[4];
    DWORD dwReserved2[1];
    void *pCurrentCtx;
} SOleTlsData;

#endif

/* COM+ APIs */

WINOLEAPI     CoGetObjectContext(IN REFIID riid, OUT LPVOID FAR* ppv);

/* register/revoke/get class objects */

WINOLEAPI  CoGetClassObject(IN REFCLSID rclsid, IN DWORD dwClsContext, IN LPVOID pvReserved,
                    IN REFIID riid, OUT LPVOID FAR* ppv);
WINOLEAPI  CoRegisterClassObject(IN REFCLSID rclsid, IN LPUNKNOWN pUnk,
                    IN DWORD dwClsContext, IN DWORD flags, OUT LPDWORD lpdwRegister);
WINOLEAPI  CoRevokeClassObject(IN DWORD dwRegister);
WINOLEAPI  CoResumeClassObjects(void);
WINOLEAPI  CoSuspendClassObjects(void);
WINOLEAPI_(ULONG) CoAddRefServerProcess(void);
WINOLEAPI_(ULONG) CoReleaseServerProcess(void);
WINOLEAPI  CoGetPSClsid(IN REFIID riid, OUT CLSID *pClsid);
WINOLEAPI  CoRegisterPSClsid(IN REFIID riid, IN REFCLSID rclsid);

// Registering surrogate processes
WINOLEAPI  CoRegisterSurrogate(IN LPSURROGATE pSurrogate);

/* marshaling interface pointers */

WINOLEAPI CoGetMarshalSizeMax(OUT ULONG *pulSize, IN REFIID riid, IN LPUNKNOWN pUnk,
                    IN DWORD dwDestContext, IN LPVOID pvDestContext, IN DWORD mshlflags);
WINOLEAPI CoMarshalInterface(IN LPSTREAM pStm, IN REFIID riid, IN LPUNKNOWN pUnk,
                    IN DWORD dwDestContext, IN LPVOID pvDestContext, IN DWORD mshlflags);
WINOLEAPI CoUnmarshalInterface(IN LPSTREAM pStm, IN REFIID riid, OUT LPVOID FAR* ppv);
WINOLEAPI CoMarshalHresult(IN LPSTREAM pstm, IN HRESULT hresult);
WINOLEAPI CoUnmarshalHresult(IN LPSTREAM pstm, OUT HRESULT FAR * phresult);
WINOLEAPI CoReleaseMarshalData(IN LPSTREAM pStm);
WINOLEAPI CoDisconnectObject(IN LPUNKNOWN pUnk, IN DWORD dwReserved);
WINOLEAPI CoLockObjectExternal(IN LPUNKNOWN pUnk, IN BOOL fLock, IN BOOL fLastUnlockReleases);
WINOLEAPI CoGetStandardMarshal(IN REFIID riid, IN LPUNKNOWN pUnk,
                    IN DWORD dwDestContext, IN LPVOID pvDestContext, IN DWORD mshlflags,
                    OUT LPMARSHAL FAR* ppMarshal);
WINOLEAPI CoStdMarshalObject(IStream *pStm, REFIID riid, IUnknown *pUnk,
                          void *pServerCtx, DWORD dwDestCtx,
                          void *pvDestCtx, DWORD mshlflags);
WINOLEAPI CoGetStdMarshalEx(IN LPUNKNOWN pUnkOuter, IN DWORD smexflags,
                            OUT LPUNKNOWN FAR* ppUnkInner);

/* flags for CoGetStdMarshalEx */
typedef enum tagSTDMSHLFLAGS
{
    SMEXF_SERVER     = 0x01,       // server side aggregated std marshaler
    SMEXF_HANDLER    = 0x02        // client side (handler) agg std marshaler
} STDMSHLFLAGS;


WINOLEAPI_(BOOL) CoIsHandlerConnected(IN LPUNKNOWN pUnk);

// Apartment model inter-thread interface passing helpers
WINOLEAPI CoMarshalInterThreadInterfaceInStream(IN REFIID riid, IN LPUNKNOWN pUnk,
                    OUT LPSTREAM *ppStm);

WINOLEAPI CoGetInterfaceAndReleaseStream(IN LPSTREAM pStm, IN REFIID iid,
                    OUT LPVOID FAR* ppv);

WINOLEAPI CoCreateFreeThreadedMarshaler(IN LPUNKNOWN  punkOuter,
                    OUT LPUNKNOWN *ppunkMarshal);

/* dll loading helpers; keeps track of ref counts and unloads all on exit */

WINOLEAPI_(HINSTANCE) CoLoadLibrary(IN LPOLESTR lpszLibName, IN BOOL bAutoFree);
WINOLEAPI_(void) CoFreeLibrary(IN HINSTANCE hInst);
WINOLEAPI_(void) CoFreeAllLibraries(void);
WINOLEAPI_(void) CoFreeUnusedLibraries(void);
#if  (_WIN32_WINNT >= 0x0501)

WINOLEAPI_(void) CoFreeUnusedLibrariesEx(IN DWORD dwUnloadDelay, IN DWORD dwReserved);
#endif

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM

/* Call Security. */


WINOLEAPI CoInitializeSecurity(
                    IN PSECURITY_DESCRIPTOR         pSecDesc,
                    IN LONG                         cAuthSvc,
                    IN SOLE_AUTHENTICATION_SERVICE *asAuthSvc,
                    IN void                        *pReserved1,
                    IN DWORD                        dwAuthnLevel,
                    IN DWORD                        dwImpLevel,
                    IN void                        *pAuthList,
                    IN DWORD                        dwCapabilities,
                    IN void                        *pReserved3 );


WINOLEAPI CoGetCallContext( IN REFIID riid, OUT void **ppInterface );


WINOLEAPI CoQueryProxyBlanket(
    IN  IUnknown                  *pProxy,
    OUT DWORD                     *pwAuthnSvc,
    OUT DWORD                     *pAuthzSvc,
    OUT OLECHAR                  **pServerPrincName,
    OUT DWORD                     *pAuthnLevel,
    OUT DWORD                     *pImpLevel,
    OUT RPC_AUTH_IDENTITY_HANDLE  *pAuthInfo,
    OUT DWORD                     *pCapabilites );


WINOLEAPI CoSetProxyBlanket(
    IN IUnknown                 *pProxy,
    IN DWORD                     dwAuthnSvc,
    IN DWORD                     dwAuthzSvc,
    IN OLECHAR                  *pServerPrincName,
    IN DWORD                     dwAuthnLevel,
    IN DWORD                     dwImpLevel,
    IN RPC_AUTH_IDENTITY_HANDLE  pAuthInfo,
    IN DWORD                     dwCapabilities );


WINOLEAPI CoCopyProxy(
    IN  IUnknown    *pProxy,
    OUT IUnknown   **ppCopy );


WINOLEAPI CoQueryClientBlanket(
    OUT DWORD             *pAuthnSvc,
    OUT DWORD             *pAuthzSvc,
    OUT OLECHAR          **pServerPrincName,
    OUT DWORD             *pAuthnLevel,
    OUT DWORD             *pImpLevel,
    OUT RPC_AUTHZ_HANDLE  *pPrivs,
    OUT DWORD             *pCapabilities );


WINOLEAPI CoImpersonateClient(void);


WINOLEAPI CoRevertToSelf(void);


WINOLEAPI CoQueryAuthenticationServices(
    OUT DWORD *pcAuthSvc,
    OUT SOLE_AUTHENTICATION_SERVICE **asAuthSvc );


WINOLEAPI CoSwitchCallContext( IN IUnknown *pNewObject, OUT IUnknown **ppOldObject );

#define COM_RIGHTS_EXECUTE 1
#define COM_RIGHTS_SAFE_FOR_SCRIPTING 2

#endif // DCOM

/* helper for creating instances */

WINOLEAPI CoCreateInstance(IN REFCLSID rclsid, IN LPUNKNOWN pUnkOuter,
                    IN DWORD dwClsContext, IN REFIID riid, OUT LPVOID FAR* ppv);


#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM


WINOLEAPI CoGetInstanceFromFile(
    IN COSERVERINFO *              pServerInfo,
    IN CLSID       *               pClsid,
    IN IUnknown    *               punkOuter, // only relevant locally
    IN DWORD                       dwClsCtx,
    IN DWORD                       grfMode,
    IN OLECHAR *                   pwszName,
    IN DWORD                       dwCount,
    IN OUT MULTI_QI    *           pResults );


WINOLEAPI CoGetInstanceFromIStorage(
    IN COSERVERINFO *              pServerInfo,
    IN CLSID       *               pClsid,
    IN IUnknown    *               punkOuter, // only relevant locally
    IN DWORD                       dwClsCtx,
    IN struct IStorage *           pstg,
    IN DWORD                       dwCount,
    IN OUT MULTI_QI    *           pResults );


WINOLEAPI CoCreateInstanceEx(
    IN REFCLSID                    Clsid,
    IN IUnknown    *               punkOuter, // only relevant locally
    IN DWORD                       dwClsCtx,
    IN COSERVERINFO *              pServerInfo,
    IN DWORD                       dwCount,
    IN OUT MULTI_QI    *           pResults );

#endif // DCOM

/* Call related APIs */
#if (_WIN32_WINNT >= 0x0500 ) || defined(_WIN32_DCOM) // DCOM


WINOLEAPI CoGetCancelObject(IN DWORD dwThreadId, IN REFIID iid, OUT void **ppUnk);


WINOLEAPI CoSetCancelObject(IN IUnknown *pUnk);


WINOLEAPI CoCancelCall(IN DWORD dwThreadId, IN ULONG ulTimeout);


WINOLEAPI CoTestCancel(void);


WINOLEAPI CoEnableCallCancellation(IN LPVOID pReserved);


WINOLEAPI CoDisableCallCancellation(IN LPVOID pReserved);


WINOLEAPI CoAllowSetForegroundWindow(IN IUnknown *pUnk, IN LPVOID lpvReserved);


WINOLEAPI DcomChannelSetHResult(IN LPVOID pvReserved, IN ULONG* pulReserved, IN HRESULT appsHR);

#endif

/* other helpers */

WINOLEAPI StringFromCLSID(IN REFCLSID rclsid, OUT LPOLESTR FAR* lplpsz);
WINOLEAPI CLSIDFromString(IN LPOLESTR lpsz, OUT LPCLSID pclsid);
WINOLEAPI StringFromIID(IN REFIID rclsid, OUT LPOLESTR FAR* lplpsz);
WINOLEAPI IIDFromString(IN LPOLESTR lpsz, OUT LPIID lpiid);
WINOLEAPI_(BOOL) CoIsOle1Class(IN REFCLSID rclsid);
WINOLEAPI ProgIDFromCLSID (IN REFCLSID clsid, OUT LPOLESTR FAR* lplpszProgID);
WINOLEAPI CLSIDFromProgID (IN LPCOLESTR lpszProgID, OUT LPCLSID lpclsid);
WINOLEAPI CLSIDFromProgIDEx (IN LPCOLESTR lpszProgID, OUT LPCLSID lpclsid);
WINOLEAPI_(int) StringFromGUID2(IN REFGUID rguid, OUT LPOLESTR lpsz, IN int cchMax);

WINOLEAPI CoCreateGuid(OUT GUID FAR *pguid);

WINOLEAPI_(BOOL) CoFileTimeToDosDateTime(
                 IN FILETIME FAR* lpFileTime, OUT LPWORD lpDosDate, OUT LPWORD lpDosTime);
WINOLEAPI_(BOOL) CoDosDateTimeToFileTime(
                       IN WORD nDosDate, IN WORD nDosTime, OUT FILETIME FAR* lpFileTime);
WINOLEAPI  CoFileTimeNow( OUT FILETIME FAR* lpFileTime );


WINOLEAPI CoRegisterMessageFilter( IN LPMESSAGEFILTER lpMessageFilter,
                                OUT LPMESSAGEFILTER FAR* lplpMessageFilter );

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM

WINOLEAPI CoRegisterChannelHook( IN REFGUID ExtensionUuid, IN IChannelHook *pChannelHook );
#endif // DCOM

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
/* Synchronization API */


WINOLEAPI CoWaitForMultipleHandles (IN DWORD dwFlags,
                                    IN DWORD dwTimeout,
                                    IN ULONG cHandles,
                                    IN LPHANDLE pHandles,
                                    OUT LPDWORD  lpdwindex);

/* Flags for Synchronization API and Classes */

typedef enum tagCOWAIT_FLAGS
{
  COWAIT_WAITALL = 1,
  COWAIT_ALERTABLE = 2,
  COWAIT_INPUTAVAILABLE = 4
}COWAIT_FLAGS;

#endif // DCOM

/* for flushing OLESCM remote binding handles */

#if  (_WIN32_WINNT >= 0x0501)

WINOLEAPI CoInvalidateRemoteMachineBindings(LPOLESTR pszMachineName);
#endif

/* TreatAs APIS */

WINOLEAPI CoGetTreatAsClass(IN REFCLSID clsidOld, OUT LPCLSID pClsidNew);
WINOLEAPI CoTreatAsClass(IN REFCLSID clsidOld, IN REFCLSID clsidNew);


/* the server dlls must define their DllGetClassObject and DllCanUnloadNow
 * to match these; the typedefs are located here to ensure all are changed at
 * the same time.
 */

//#ifdef _MAC
//typedef STDAPICALLTYPE HRESULT (* LPFNGETCLASSOBJECT) (REFCLSID, REFIID, LPVOID *);
//#else
typedef HRESULT (STDAPICALLTYPE * LPFNGETCLASSOBJECT) (REFCLSID, REFIID, LPVOID *);
//#endif

//#ifdef _MAC
//typedef STDAPICALLTYPE HRESULT (* LPFNCANUNLOADNOW)(void);
//#else
typedef HRESULT (STDAPICALLTYPE * LPFNCANUNLOADNOW)(void);
//#endif

STDAPI  DllGetClassObject(IN REFCLSID rclsid, IN REFIID riid, OUT LPVOID FAR* ppv);

STDAPI  DllCanUnloadNow(void);


/****** Default Memory Allocation ******************************************/
WINOLEAPI_(LPVOID) CoTaskMemAlloc(IN SIZE_T cb);
WINOLEAPI_(LPVOID) CoTaskMemRealloc(IN LPVOID pv, IN SIZE_T cb);
WINOLEAPI_(void)   CoTaskMemFree(IN LPVOID pv);

/****** DV APIs ***********************************************************/

/* This function is declared in objbase.h and ole2.h */
WINOLEAPI CreateDataAdviseHolder(OUT LPDATAADVISEHOLDER FAR* ppDAHolder);

WINOLEAPI CreateDataCache(IN LPUNKNOWN pUnkOuter, IN REFCLSID rclsid,
                                        IN REFIID iid, OUT LPVOID FAR* ppv);


/****** Storage API Prototypes ********************************************/


WINOLEAPI StgCreateDocfile(IN const OLECHAR FAR* pwcsName,
            IN DWORD grfMode,
            IN DWORD reserved,
            OUT IStorage FAR * FAR *ppstgOpen);

WINOLEAPI StgCreateDocfileOnILockBytes(IN ILockBytes FAR *plkbyt,
                    IN DWORD grfMode,
                    IN DWORD reserved,
                    OUT IStorage FAR * FAR *ppstgOpen);

WINOLEAPI StgOpenStorage(IN const OLECHAR FAR* pwcsName,
              IN  IStorage FAR *pstgPriority,
              IN  DWORD grfMode,
              IN  SNB snbExclude,
              IN  DWORD reserved,
              OUT IStorage FAR * FAR *ppstgOpen);
WINOLEAPI StgOpenStorageOnILockBytes(IN ILockBytes FAR *plkbyt,
                  IN  IStorage FAR *pstgPriority,
                  IN  DWORD grfMode,
                  IN  SNB snbExclude,
                  IN  DWORD reserved,
                  OUT IStorage FAR * FAR *ppstgOpen);

WINOLEAPI StgIsStorageFile(IN const OLECHAR FAR* pwcsName);
WINOLEAPI StgIsStorageILockBytes(IN ILockBytes FAR* plkbyt);

WINOLEAPI StgSetTimes(IN OLECHAR const FAR* lpszName,
                   IN FILETIME const FAR* pctime,
                   IN FILETIME const FAR* patime,
                   IN FILETIME const FAR* pmtime);

WINOLEAPI StgOpenAsyncDocfileOnIFillLockBytes( IN IFillLockBytes *pflb,
             IN  DWORD grfMode,
             IN  DWORD asyncFlags,
             OUT IStorage **ppstgOpen);

WINOLEAPI StgGetIFillLockBytesOnILockBytes( IN ILockBytes *pilb,
             OUT IFillLockBytes **ppflb);

WINOLEAPI StgGetIFillLockBytesOnFile(IN OLECHAR const *pwcsName,
             OUT IFillLockBytes **ppflb);


WINOLEAPI StgOpenLayoutDocfile(IN OLECHAR const *pwcsDfName,
             IN  DWORD grfMode,
             IN  DWORD reserved,
             OUT IStorage **ppstgOpen);

// STG initialization options for StgCreateStorageEx and StgOpenStorageEx
#define STGOPTIONS_VERSION 2

typedef struct tagSTGOPTIONS
{
    USHORT usVersion;            // Versions 1 and 2 supported
    USHORT reserved;             // must be 0 for padding
    ULONG ulSectorSize;          // docfile header sector size (512)
    const WCHAR *pwcsTemplateFile;  // version 2 or above 
} STGOPTIONS;

WINOLEAPI StgCreateStorageEx (IN const WCHAR* pwcsName,
            IN  DWORD grfMode,
            IN  DWORD stgfmt,              // enum
            IN  DWORD grfAttrs,             // reserved
            IN  STGOPTIONS * pStgOptions,
            IN  void * reserved,
            IN  REFIID riid,
            OUT void ** ppObjectOpen);

WINOLEAPI StgOpenStorageEx (IN const WCHAR* pwcsName,
            IN  DWORD grfMode,
            IN  DWORD stgfmt,              // enum
            IN  DWORD grfAttrs,             // reserved
            IN  STGOPTIONS * pStgOptions,
            IN  void * reserved,
            IN  REFIID riid,
            OUT void ** ppObjectOpen);


//
//  Moniker APIs
//

WINOLEAPI  BindMoniker(IN LPMONIKER pmk, IN DWORD grfOpt, IN REFIID iidResult, OUT LPVOID FAR* ppvResult);

WINOLEAPI  CoInstall(
    IN  IBindCtx     * pbc,
    IN  DWORD          dwFlags,
    IN  uCLSSPEC     * pClassSpec,
    IN  QUERYCONTEXT * pQuery,
    IN  LPWSTR         pszCodeBase);

WINOLEAPI  CoGetObject(IN LPCWSTR pszName, IN BIND_OPTS *pBindOptions, IN REFIID riid, OUT void **ppv);
WINOLEAPI  MkParseDisplayName(IN LPBC pbc, IN LPCOLESTR szUserName,
                OUT ULONG FAR * pchEaten, OUT LPMONIKER FAR * ppmk);
WINOLEAPI  MonikerRelativePathTo(IN LPMONIKER pmkSrc, IN LPMONIKER pmkDest, OUT LPMONIKER
                FAR* ppmkRelPath, IN BOOL dwReserved);
WINOLEAPI  MonikerCommonPrefixWith(IN LPMONIKER pmkThis, IN LPMONIKER pmkOther,
                OUT LPMONIKER FAR* ppmkCommon);
WINOLEAPI  CreateBindCtx(IN DWORD reserved, OUT LPBC FAR* ppbc);
WINOLEAPI  CreateGenericComposite(IN LPMONIKER pmkFirst, IN LPMONIKER pmkRest,
    OUT LPMONIKER FAR* ppmkComposite);
WINOLEAPI  GetClassFile (IN LPCOLESTR szFilename, OUT CLSID FAR* pclsid);

WINOLEAPI  CreateClassMoniker(IN REFCLSID rclsid, OUT LPMONIKER FAR* ppmk);

WINOLEAPI  CreateFileMoniker(IN LPCOLESTR lpszPathName, OUT LPMONIKER FAR* ppmk);

WINOLEAPI  CreateItemMoniker(IN LPCOLESTR lpszDelim, IN LPCOLESTR lpszItem,
    OUT LPMONIKER FAR* ppmk);
WINOLEAPI  CreateAntiMoniker(OUT LPMONIKER FAR* ppmk);
WINOLEAPI  CreatePointerMoniker(IN LPUNKNOWN punk, OUT LPMONIKER FAR* ppmk);
WINOLEAPI  CreateObjrefMoniker(IN LPUNKNOWN punk, OUT LPMONIKER FAR * ppmk);

WINOLEAPI  GetRunningObjectTable( IN DWORD reserved, OUT LPRUNNINGOBJECTTABLE FAR* pprot);

#include <urlmon.h>
#include <propidl.h>

//
// Standard Progress Indicator impolementation
//
WINOLEAPI CreateStdProgressIndicator(IN HWND hwndParent,
                                   IN  LPCOLESTR pszTitle,
                                   IN  IBindStatusCallback * pIbscCaller,
                                   OUT IBindStatusCallback ** ppIbsc);

//
#if defined(__cplusplus)
extern "C" {
#endif


#if !defined(RC_INVOKED) /* RC complains about long symbols in #ifs */
#if defined(ISOLATION_AWARE_ENABLED) && (ISOLATION_AWARE_ENABLED != 0) && defined(ISOLATION_AWARE_VERSION) && (ISOLATION_AWARE_VERSION >= 0x0200)


#if !defined(ISOLATION_AWARE_USE_STATIC_LIBRARY)
#define ISOLATION_AWARE_USE_STATIC_LIBRARY 0
#endif

#if !defined(ISOLATION_AWARE_BUILD_STATIC_LIBRARY)
#define ISOLATION_AWARE_BUILD_STATIC_LIBRARY 0
#endif

#if !defined(ISOLATION_AWARE_INLINE)
#if ISOLATION_AWARE_BUILD_STATIC_LIBRARY
#define ISOLATION_AWARE_INLINE /* nothing */
#else
#if defined(__cplusplus)
#define ISOLATION_AWARE_INLINE inline
#else
#define ISOLATION_AWARE_INLINE __inline
#endif
#endif
#endif

#if !ISOLATION_AWARE_USE_STATIC_LIBRARY
#endif /* ISOLATION_AWARE_USE_STATIC_LIBRARY */
HRESULT WINAPI IsolationAwareCoInitialize(LPVOID pvReserved);
HRESULT WINAPI IsolationAwareCoGetMalloc(DWORD dwMemContext,LPMALLOC*ppMalloc);
HRESULT WINAPI IsolationAwareCoRegisterMallocSpy(LPMALLOCSPY pMallocSpy);
HRESULT WINAPI IsolationAwareCoRevokeMallocSpy(void);
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)
HRESULT WINAPI IsolationAwareCoInitializeEx(LPVOID pvReserved,DWORD dwCoInit);
HRESULT WINAPI IsolationAwareCoGetCallerTID(LPDWORD lpdwTID);
#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
#if _WIN32_WINNT >= 0x0501
HRESULT WINAPI IsolationAwareCoRegisterInitializeSpy(LPINITIALIZESPY pSpy,ULARGE_INTEGER*puliCookie);
HRESULT WINAPI IsolationAwareCoRevokeInitializeSpy(ULARGE_INTEGER uliCookie);
HRESULT WINAPI IsolationAwareCoGetContextToken(ULONG_PTR*pToken);
#endif /* _WIN32_WINNT >= 0x0501 */
#if _WIN32_WINNT >= 0x0600
HRESULT WINAPI IsolationAwareCoSetApartmentLockState(APTTYPE eAptType,BOOL fLock);
#endif /* _WIN32_WINNT >= 0x0600 */
HRESULT WINAPI IsolationAwareCoGetObjectContext(REFIID riid,LPVOID*ppv);
HRESULT WINAPI IsolationAwareCoGetClassObject(REFCLSID rclsid,DWORD dwClsContext,LPVOID pvReserved,REFIID riid,LPVOID*ppv);
HRESULT WINAPI IsolationAwareCoRegisterClassObject(REFCLSID rclsid,LPUNKNOWN pUnk,DWORD dwClsContext,DWORD flags,LPDWORD lpdwRegister);
HRESULT WINAPI IsolationAwareCoRevokeClassObject(DWORD dwRegister);
HRESULT WINAPI IsolationAwareCoResumeClassObjects(void);
HRESULT WINAPI IsolationAwareCoSuspendClassObjects(void);
HRESULT WINAPI IsolationAwareCoGetPSClsid(REFIID riid,CLSID*pClsid);
HRESULT WINAPI IsolationAwareCoRegisterPSClsid(REFIID riid,REFCLSID rclsid);
HRESULT WINAPI IsolationAwareCoRegisterSurrogate(LPSURROGATE pSurrogate);
HRESULT WINAPI IsolationAwareCoGetMarshalSizeMax(ULONG*pulSize,REFIID riid,LPUNKNOWN pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags);
HRESULT WINAPI IsolationAwareCoMarshalInterface(LPSTREAM pStm,REFIID riid,LPUNKNOWN pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags);
HRESULT WINAPI IsolationAwareCoUnmarshalInterface(LPSTREAM pStm,REFIID riid,LPVOID*ppv);
HRESULT WINAPI IsolationAwareCoMarshalHresult(LPSTREAM pstm,HRESULT hresult);
HRESULT WINAPI IsolationAwareCoUnmarshalHresult(LPSTREAM pstm,HRESULT*phresult);
HRESULT WINAPI IsolationAwareCoReleaseMarshalData(LPSTREAM pStm);
HRESULT WINAPI IsolationAwareCoDisconnectObject(LPUNKNOWN pUnk,DWORD dwReserved);
HRESULT WINAPI IsolationAwareCoLockObjectExternal(LPUNKNOWN pUnk,BOOL fLock,BOOL fLastUnlockReleases);
HRESULT WINAPI IsolationAwareCoGetStandardMarshal(REFIID riid,LPUNKNOWN pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags,LPMARSHAL*ppMarshal);
HRESULT WINAPI IsolationAwareCoStdMarshalObject(IStream*pStm,REFIID riid,IUnknown*pUnk,void*pServerCtx,DWORD dwDestCtx,void*pvDestCtx,DWORD mshlflags);
HRESULT WINAPI IsolationAwareCoGetStdMarshalEx(LPUNKNOWN pUnkOuter,DWORD smexflags,LPUNKNOWN*ppUnkInner);
HRESULT WINAPI IsolationAwareCoMarshalInterThreadInterfaceInStream(REFIID riid,LPUNKNOWN pUnk,LPSTREAM*ppStm);
HRESULT WINAPI IsolationAwareCoGetInterfaceAndReleaseStream(LPSTREAM pStm,REFIID iid,LPVOID*ppv);
HRESULT WINAPI IsolationAwareCoCreateFreeThreadedMarshaler(LPUNKNOWN punkOuter,LPUNKNOWN*ppunkMarshal);
HINSTANCE WINAPI IsolationAwareCoLoadLibrary(LPOLESTR lpszLibName,BOOL bAutoFree);
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)
HRESULT WINAPI IsolationAwareCoInitializeSecurity(PSECURITY_DESCRIPTOR pSecDesc,long cAuthSvc,SOLE_AUTHENTICATION_SERVICE*asAuthSvc,void*pReserved1,DWORD dwAuthnLevel,DWORD dwImpLevel,void*pAuthList,DWORD dwCapabilities,void*pReserved3);
HRESULT WINAPI IsolationAwareCoGetCallContext(REFIID riid,void**ppInterface);
HRESULT WINAPI IsolationAwareCoQueryProxyBlanket(IUnknown*pProxy,DWORD*pwAuthnSvc,DWORD*pAuthzSvc,OLECHAR**pServerPrincName,DWORD*pAuthnLevel,DWORD*pImpLevel,RPC_AUTH_IDENTITY_HANDLE*pAuthInfo,DWORD*pCapabilites);
HRESULT WINAPI IsolationAwareCoSetProxyBlanket(IUnknown*pProxy,DWORD dwAuthnSvc,DWORD dwAuthzSvc,OLECHAR*pServerPrincName,DWORD dwAuthnLevel,DWORD dwImpLevel,RPC_AUTH_IDENTITY_HANDLE pAuthInfo,DWORD dwCapabilities);
HRESULT WINAPI IsolationAwareCoCopyProxy(IUnknown*pProxy,IUnknown**ppCopy);
HRESULT WINAPI IsolationAwareCoQueryClientBlanket(DWORD*pAuthnSvc,DWORD*pAuthzSvc,OLECHAR**pServerPrincName,DWORD*pAuthnLevel,DWORD*pImpLevel,RPC_AUTHZ_HANDLE*pPrivs,DWORD*pCapabilities);
HRESULT WINAPI IsolationAwareCoImpersonateClient(void);
HRESULT WINAPI IsolationAwareCoRevertToSelf(void);
HRESULT WINAPI IsolationAwareCoQueryAuthenticationServices(DWORD*pcAuthSvc,SOLE_AUTHENTICATION_SERVICE**asAuthSvc);
HRESULT WINAPI IsolationAwareCoSwitchCallContext(IUnknown*pNewObject,IUnknown**ppOldObject);
#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
HRESULT WINAPI IsolationAwareCoCreateInstance(REFCLSID rclsid,LPUNKNOWN pUnkOuter,DWORD dwClsContext,REFIID riid,LPVOID*ppv);
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)
HRESULT WINAPI IsolationAwareCoGetInstanceFromFile(COSERVERINFO*pServerInfo,CLSID*pClsid,IUnknown*punkOuter,DWORD dwClsCtx,DWORD grfMode,OLECHAR*pwszName,DWORD dwCount,MULTI_QI*pResults);
HRESULT WINAPI IsolationAwareCoGetInstanceFromIStorage(COSERVERINFO*pServerInfo,CLSID*pClsid,IUnknown*punkOuter,DWORD dwClsCtx,struct IStorage*pstg,DWORD dwCount,MULTI_QI*pResults);
HRESULT WINAPI IsolationAwareCoCreateInstanceEx(REFCLSID Clsid,IUnknown*punkOuter,DWORD dwClsCtx,COSERVERINFO*pServerInfo,DWORD dwCount,MULTI_QI*pResults);
#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
#if (_WIN32_WINNT >= 0x0500 ) || defined(_WIN32_DCOM)
HRESULT WINAPI IsolationAwareCoGetCancelObject(DWORD dwThreadId,REFIID iid,void**ppUnk);
HRESULT WINAPI IsolationAwareCoSetCancelObject(IUnknown*pUnk);
HRESULT WINAPI IsolationAwareCoCancelCall(DWORD dwThreadId,ULONG ulTimeout);
HRESULT WINAPI IsolationAwareCoTestCancel(void);
HRESULT WINAPI IsolationAwareCoEnableCallCancellation(LPVOID pReserved);
HRESULT WINAPI IsolationAwareCoDisableCallCancellation(LPVOID pReserved);
HRESULT WINAPI IsolationAwareCoAllowSetForegroundWindow(IUnknown*pUnk,LPVOID lpvReserved);
HRESULT WINAPI IsolationAwareDcomChannelSetHResult(LPVOID pvReserved,ULONG*pulReserved,HRESULT appsHR);
#endif /* (_WIN32_WINNT >= 0x0500 ) || defined(_WIN32_DCOM) */
HRESULT WINAPI IsolationAwareCLSIDFromString(LPOLESTR lpsz,LPCLSID pclsid);
HRESULT WINAPI IsolationAwareIIDFromString(LPOLESTR lpsz,LPIID lpiid);
HRESULT WINAPI IsolationAwareProgIDFromCLSID(REFCLSID clsid,LPOLESTR*lplpszProgID);
HRESULT WINAPI IsolationAwareCLSIDFromProgID(LPCOLESTR lpszProgID,LPCLSID lpclsid);
HRESULT WINAPI IsolationAwareCLSIDFromProgIDEx(LPCOLESTR lpszProgID,LPCLSID lpclsid);
HRESULT WINAPI IsolationAwareCoCreateGuid(GUID*pguid);
HRESULT WINAPI IsolationAwareCoFileTimeNow(FILETIME*lpFileTime);
HRESULT WINAPI IsolationAwareCoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter,LPMESSAGEFILTER*lplpMessageFilter);
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)
HRESULT WINAPI IsolationAwareCoRegisterChannelHook(REFGUID ExtensionUuid,IChannelHook*pChannelHook);
HRESULT WINAPI IsolationAwareCoWaitForMultipleHandles(DWORD dwFlags,DWORD dwTimeout,ULONG cHandles,LPHANDLE pHandles,LPDWORD lpdwindex);
#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
#if _WIN32_WINNT >= 0x0501
HRESULT WINAPI IsolationAwareCoInvalidateRemoteMachineBindings(LPOLESTR pszMachineName);
#endif /* _WIN32_WINNT >= 0x0501 */
HRESULT WINAPI IsolationAwareCoGetTreatAsClass(REFCLSID clsidOld,LPCLSID pClsidNew);
HRESULT WINAPI IsolationAwareCoTreatAsClass(REFCLSID clsidOld,REFCLSID clsidNew);
HRESULT WINAPI IsolationAwareCreateDataAdviseHolder(LPDATAADVISEHOLDER*ppDAHolder);
HRESULT WINAPI IsolationAwareCreateDataCache(LPUNKNOWN pUnkOuter,REFCLSID rclsid,REFIID iid,LPVOID*ppv);
HRESULT WINAPI IsolationAwareStgCreateDocfile(const OLECHAR*pwcsName,DWORD grfMode,DWORD reserved,IStorage**ppstgOpen);
HRESULT WINAPI IsolationAwareStgCreateDocfileOnILockBytes(ILockBytes*plkbyt,DWORD grfMode,DWORD reserved,IStorage**ppstgOpen);
HRESULT WINAPI IsolationAwareStgOpenStorage(const OLECHAR*pwcsName,IStorage*pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage**ppstgOpen);
HRESULT WINAPI IsolationAwareStgOpenStorageOnILockBytes(ILockBytes*plkbyt,IStorage*pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage**ppstgOpen);
HRESULT WINAPI IsolationAwareStgIsStorageFile(const OLECHAR*pwcsName);
HRESULT WINAPI IsolationAwareStgIsStorageILockBytes(ILockBytes*plkbyt);
HRESULT WINAPI IsolationAwareStgSetTimes(OLECHAR const*lpszName,FILETIME const*pctime,FILETIME const*patime,FILETIME const*pmtime);
HRESULT WINAPI IsolationAwareStgOpenAsyncDocfileOnIFillLockBytes(IFillLockBytes*pflb,DWORD grfMode,DWORD asyncFlags,IStorage**ppstgOpen);
HRESULT WINAPI IsolationAwareStgGetIFillLockBytesOnILockBytes(ILockBytes*pilb,IFillLockBytes**ppflb);
HRESULT WINAPI IsolationAwareStgGetIFillLockBytesOnFile(OLECHAR const*pwcsName,IFillLockBytes**ppflb);
HRESULT WINAPI IsolationAwareStgCreateStorageEx(const WCHAR*pwcsName,DWORD grfMode,DWORD stgfmt,DWORD grfAttrs,STGOPTIONS*pStgOptions,void*reserved,REFIID riid,void**ppObjectOpen);
HRESULT WINAPI IsolationAwareStgOpenStorageEx(const WCHAR*pwcsName,DWORD grfMode,DWORD stgfmt,DWORD grfAttrs,STGOPTIONS*pStgOptions,void*reserved,REFIID riid,void**ppObjectOpen);
HRESULT WINAPI IsolationAwareBindMoniker(LPMONIKER pmk,DWORD grfOpt,REFIID iidResult,LPVOID*ppvResult);
HRESULT WINAPI IsolationAwareCoInstall(IBindCtx*pbc,DWORD dwFlags,uCLSSPEC*pClassSpec,QUERYCONTEXT*pQuery,LPWSTR pszCodeBase);
HRESULT WINAPI IsolationAwareCoGetObject(LPCWSTR pszName,BIND_OPTS*pBindOptions,REFIID riid,void**ppv);
HRESULT WINAPI IsolationAwareMkParseDisplayName(LPBC pbc,LPCOLESTR szUserName,ULONG*pchEaten,LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareMonikerRelativePathTo(LPMONIKER pmkSrc,LPMONIKER pmkDest,LPMONIKER*ppmkRelPath,BOOL dwReserved);
HRESULT WINAPI IsolationAwareMonikerCommonPrefixWith(LPMONIKER pmkThis,LPMONIKER pmkOther,LPMONIKER*ppmkCommon);
HRESULT WINAPI IsolationAwareCreateBindCtx(DWORD reserved,LPBC*ppbc);
HRESULT WINAPI IsolationAwareCreateGenericComposite(LPMONIKER pmkFirst,LPMONIKER pmkRest,LPMONIKER*ppmkComposite);
HRESULT WINAPI IsolationAwareGetClassFile(LPCOLESTR szFilename,CLSID*pclsid);
HRESULT WINAPI IsolationAwareCreateClassMoniker(REFCLSID rclsid,LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareCreateFileMoniker(LPCOLESTR lpszPathName,LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareCreateItemMoniker(LPCOLESTR lpszDelim,LPCOLESTR lpszItem,LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareCreateAntiMoniker(LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareCreatePointerMoniker(LPUNKNOWN punk,LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareCreateObjrefMoniker(LPUNKNOWN punk,LPMONIKER*ppmk);
HRESULT WINAPI IsolationAwareGetRunningObjectTable(DWORD reserved,LPRUNNINGOBJECTTABLE*pprot);
HRESULT WINAPI IsolationAwareCreateStdProgressIndicator(HWND hwndParent,LPCOLESTR pszTitle,IBindStatusCallback*pIbscCaller,IBindStatusCallback**ppIbsc);

ISOLATION_AWARE_INLINE HRESULT ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg(void)
{
    DWORD dwLastError = GetLastError();
    if (dwLastError == NO_ERROR)
        dwLastError = ERROR_INTERNAL_ERROR;
    return HRESULT_FROM_WIN32(dwLastError);
}

#if !ISOLATION_AWARE_USE_STATIC_LIBRARY
ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoInitialize(LPVOID pvReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoInitialize(pvReserved);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetMalloc(DWORD dwMemContext,LPMALLOC*ppMalloc)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetMalloc(dwMemContext,ppMalloc);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterMallocSpy(LPMALLOCSPY pMallocSpy)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterMallocSpy(pMallocSpy);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRevokeMallocSpy(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRevokeMallocSpy();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoInitializeEx(LPVOID pvReserved,DWORD dwCoInit)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoInitializeEx(pvReserved,dwCoInit);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetCallerTID(LPDWORD lpdwTID)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetCallerTID(lpdwTID);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
#if _WIN32_WINNT >= 0x0501

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterInitializeSpy(LPINITIALIZESPY pSpy,ULARGE_INTEGER*puliCookie)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterInitializeSpy(pSpy,puliCookie);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRevokeInitializeSpy(ULARGE_INTEGER uliCookie)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRevokeInitializeSpy(uliCookie);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetContextToken(ULONG_PTR*pToken)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetContextToken(pToken);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* _WIN32_WINNT >= 0x0501 */
#if _WIN32_WINNT >= 0x0600

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoSetApartmentLockState(APTTYPE eAptType,BOOL fLock)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoSetApartmentLockState(eAptType,fLock);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* _WIN32_WINNT >= 0x0600 */

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetObjectContext(REFIID riid,LPVOID*ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetObjectContext(riid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetClassObject(REFCLSID rclsid,DWORD dwClsContext,LPVOID pvReserved,REFIID riid,LPVOID*ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetClassObject(rclsid,dwClsContext,pvReserved,riid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterClassObject(REFCLSID rclsid,LPUNKNOWN pUnk,DWORD dwClsContext,DWORD flags,LPDWORD lpdwRegister)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterClassObject(rclsid,pUnk,dwClsContext,flags,lpdwRegister);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRevokeClassObject(DWORD dwRegister)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRevokeClassObject(dwRegister);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoResumeClassObjects(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoResumeClassObjects();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoSuspendClassObjects(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoSuspendClassObjects();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetPSClsid(REFIID riid,CLSID*pClsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetPSClsid(riid,pClsid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterPSClsid(REFIID riid,REFCLSID rclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterPSClsid(riid,rclsid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterSurrogate(LPSURROGATE pSurrogate)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterSurrogate(pSurrogate);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetMarshalSizeMax(ULONG*pulSize,REFIID riid,LPUNKNOWN pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetMarshalSizeMax(pulSize,riid,pUnk,dwDestContext,pvDestContext,mshlflags);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoMarshalInterface(LPSTREAM pStm,REFIID riid,LPUNKNOWN pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoMarshalInterface(pStm,riid,pUnk,dwDestContext,pvDestContext,mshlflags);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoUnmarshalInterface(LPSTREAM pStm,REFIID riid,LPVOID*ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoUnmarshalInterface(pStm,riid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoMarshalHresult(LPSTREAM pstm,HRESULT hresult)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoMarshalHresult(pstm,hresult);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoUnmarshalHresult(LPSTREAM pstm,HRESULT*phresult)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoUnmarshalHresult(pstm,phresult);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoReleaseMarshalData(LPSTREAM pStm)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoReleaseMarshalData(pStm);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoDisconnectObject(LPUNKNOWN pUnk,DWORD dwReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoDisconnectObject(pUnk,dwReserved);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoLockObjectExternal(LPUNKNOWN pUnk,BOOL fLock,BOOL fLastUnlockReleases)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoLockObjectExternal(pUnk,fLock,fLastUnlockReleases);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetStandardMarshal(REFIID riid,LPUNKNOWN pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags,LPMARSHAL*ppMarshal)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetStandardMarshal(riid,pUnk,dwDestContext,pvDestContext,mshlflags,ppMarshal);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoStdMarshalObject(IStream*pStm,REFIID riid,IUnknown*pUnk,void*pServerCtx,DWORD dwDestCtx,void*pvDestCtx,DWORD mshlflags)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoStdMarshalObject(pStm,riid,pUnk,pServerCtx,dwDestCtx,pvDestCtx,mshlflags);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetStdMarshalEx(LPUNKNOWN pUnkOuter,DWORD smexflags,LPUNKNOWN*ppUnkInner)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetStdMarshalEx(pUnkOuter,smexflags,ppUnkInner);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoMarshalInterThreadInterfaceInStream(REFIID riid,LPUNKNOWN pUnk,LPSTREAM*ppStm)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoMarshalInterThreadInterfaceInStream(riid,pUnk,ppStm);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetInterfaceAndReleaseStream(LPSTREAM pStm,REFIID iid,LPVOID*ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetInterfaceAndReleaseStream(pStm,iid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoCreateFreeThreadedMarshaler(LPUNKNOWN punkOuter,LPUNKNOWN*ppunkMarshal)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoCreateFreeThreadedMarshaler(punkOuter,ppunkMarshal);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HINSTANCE WINAPI IsolationAwareCoLoadLibrary(LPOLESTR lpszLibName,BOOL bAutoFree)
{
    HINSTANCE instanceResult = (SetLastError(NO_ERROR),NULL);
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return instanceResult;
    __try
    {
        instanceResult = CoLoadLibrary(lpszLibName,bAutoFree);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (instanceResult == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return instanceResult;
}

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoInitializeSecurity(PSECURITY_DESCRIPTOR pSecDesc,long cAuthSvc,SOLE_AUTHENTICATION_SERVICE*asAuthSvc,void*pReserved1,DWORD dwAuthnLevel,DWORD dwImpLevel,void*pAuthList,DWORD dwCapabilities,void*pReserved3)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoInitializeSecurity(pSecDesc,cAuthSvc,asAuthSvc,pReserved1,dwAuthnLevel,dwImpLevel,pAuthList,dwCapabilities,pReserved3);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetCallContext(REFIID riid,void**ppInterface)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetCallContext(riid,ppInterface);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoQueryProxyBlanket(IUnknown*pProxy,DWORD*pwAuthnSvc,DWORD*pAuthzSvc,OLECHAR**pServerPrincName,DWORD*pAuthnLevel,DWORD*pImpLevel,RPC_AUTH_IDENTITY_HANDLE*pAuthInfo,DWORD*pCapabilites)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoQueryProxyBlanket(pProxy,pwAuthnSvc,pAuthzSvc,pServerPrincName,pAuthnLevel,pImpLevel,pAuthInfo,pCapabilites);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoSetProxyBlanket(IUnknown*pProxy,DWORD dwAuthnSvc,DWORD dwAuthzSvc,OLECHAR*pServerPrincName,DWORD dwAuthnLevel,DWORD dwImpLevel,RPC_AUTH_IDENTITY_HANDLE pAuthInfo,DWORD dwCapabilities)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoSetProxyBlanket(pProxy,dwAuthnSvc,dwAuthzSvc,pServerPrincName,dwAuthnLevel,dwImpLevel,pAuthInfo,dwCapabilities);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoCopyProxy(IUnknown*pProxy,IUnknown**ppCopy)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoCopyProxy(pProxy,ppCopy);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoQueryClientBlanket(DWORD*pAuthnSvc,DWORD*pAuthzSvc,OLECHAR**pServerPrincName,DWORD*pAuthnLevel,DWORD*pImpLevel,RPC_AUTHZ_HANDLE*pPrivs,DWORD*pCapabilities)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoQueryClientBlanket(pAuthnSvc,pAuthzSvc,pServerPrincName,pAuthnLevel,pImpLevel,pPrivs,pCapabilities);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoImpersonateClient(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoImpersonateClient();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRevertToSelf(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRevertToSelf();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoQueryAuthenticationServices(DWORD*pcAuthSvc,SOLE_AUTHENTICATION_SERVICE**asAuthSvc)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoQueryAuthenticationServices(pcAuthSvc,asAuthSvc);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoSwitchCallContext(IUnknown*pNewObject,IUnknown**ppOldObject)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoSwitchCallContext(pNewObject,ppOldObject);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoCreateInstance(REFCLSID rclsid,LPUNKNOWN pUnkOuter,DWORD dwClsContext,REFIID riid,LPVOID*ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoCreateInstance(rclsid,pUnkOuter,dwClsContext,riid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetInstanceFromFile(COSERVERINFO*pServerInfo,CLSID*pClsid,IUnknown*punkOuter,DWORD dwClsCtx,DWORD grfMode,OLECHAR*pwszName,DWORD dwCount,MULTI_QI*pResults)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetInstanceFromFile(pServerInfo,pClsid,punkOuter,dwClsCtx,grfMode,pwszName,dwCount,pResults);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetInstanceFromIStorage(COSERVERINFO*pServerInfo,CLSID*pClsid,IUnknown*punkOuter,DWORD dwClsCtx,struct IStorage*pstg,DWORD dwCount,MULTI_QI*pResults)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetInstanceFromIStorage(pServerInfo,pClsid,punkOuter,dwClsCtx,pstg,dwCount,pResults);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoCreateInstanceEx(REFCLSID Clsid,IUnknown*punkOuter,DWORD dwClsCtx,COSERVERINFO*pServerInfo,DWORD dwCount,MULTI_QI*pResults)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoCreateInstanceEx(Clsid,punkOuter,dwClsCtx,pServerInfo,dwCount,pResults);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
#if (_WIN32_WINNT >= 0x0500 ) || defined(_WIN32_DCOM)

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetCancelObject(DWORD dwThreadId,REFIID iid,void**ppUnk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetCancelObject(dwThreadId,iid,ppUnk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoSetCancelObject(IUnknown*pUnk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoSetCancelObject(pUnk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoCancelCall(DWORD dwThreadId,ULONG ulTimeout)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoCancelCall(dwThreadId,ulTimeout);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoTestCancel(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoTestCancel();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoEnableCallCancellation(LPVOID pReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoEnableCallCancellation(pReserved);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoDisableCallCancellation(LPVOID pReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoDisableCallCancellation(pReserved);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoAllowSetForegroundWindow(IUnknown*pUnk,LPVOID lpvReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoAllowSetForegroundWindow(pUnk,lpvReserved);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareDcomChannelSetHResult(LPVOID pvReserved,ULONG*pulReserved,HRESULT appsHR)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = DcomChannelSetHResult(pvReserved,pulReserved,appsHR);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* (_WIN32_WINNT >= 0x0500 ) || defined(_WIN32_DCOM) */

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCLSIDFromString(LPOLESTR lpsz,LPCLSID pclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CLSIDFromString(lpsz,pclsid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareIIDFromString(LPOLESTR lpsz,LPIID lpiid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = IIDFromString(lpsz,lpiid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareProgIDFromCLSID(REFCLSID clsid,LPOLESTR*lplpszProgID)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = ProgIDFromCLSID(clsid,lplpszProgID);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCLSIDFromProgID(LPCOLESTR lpszProgID,LPCLSID lpclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CLSIDFromProgID(lpszProgID,lpclsid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCLSIDFromProgIDEx(LPCOLESTR lpszProgID,LPCLSID lpclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CLSIDFromProgIDEx(lpszProgID,lpclsid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoCreateGuid(GUID*pguid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoCreateGuid(pguid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoFileTimeNow(FILETIME*lpFileTime)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoFileTimeNow(lpFileTime);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterMessageFilter(LPMESSAGEFILTER lpMessageFilter,LPMESSAGEFILTER*lplpMessageFilter)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterMessageFilter(lpMessageFilter,lplpMessageFilter);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM)

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoRegisterChannelHook(REFGUID ExtensionUuid,IChannelHook*pChannelHook)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoRegisterChannelHook(ExtensionUuid,pChannelHook);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoWaitForMultipleHandles(DWORD dwFlags,DWORD dwTimeout,ULONG cHandles,LPHANDLE pHandles,LPDWORD lpdwindex)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoWaitForMultipleHandles(dwFlags,dwTimeout,cHandles,pHandles,lpdwindex);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) */
#if _WIN32_WINNT >= 0x0501

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoInvalidateRemoteMachineBindings(LPOLESTR pszMachineName)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoInvalidateRemoteMachineBindings(pszMachineName);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* _WIN32_WINNT >= 0x0501 */

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetTreatAsClass(REFCLSID clsidOld,LPCLSID pClsidNew)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetTreatAsClass(clsidOld,pClsidNew);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoTreatAsClass(REFCLSID clsidOld,REFCLSID clsidNew)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoTreatAsClass(clsidOld,clsidNew);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateDataAdviseHolder(LPDATAADVISEHOLDER*ppDAHolder)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateDataAdviseHolder(ppDAHolder);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateDataCache(LPUNKNOWN pUnkOuter,REFCLSID rclsid,REFIID iid,LPVOID*ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateDataCache(pUnkOuter,rclsid,iid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgCreateDocfile(const OLECHAR*pwcsName,DWORD grfMode,DWORD reserved,IStorage**ppstgOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgCreateDocfile(pwcsName,grfMode,reserved,ppstgOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgCreateDocfileOnILockBytes(ILockBytes*plkbyt,DWORD grfMode,DWORD reserved,IStorage**ppstgOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgCreateDocfileOnILockBytes(plkbyt,grfMode,reserved,ppstgOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgOpenStorage(const OLECHAR*pwcsName,IStorage*pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage**ppstgOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgOpenStorage(pwcsName,pstgPriority,grfMode,snbExclude,reserved,ppstgOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgOpenStorageOnILockBytes(ILockBytes*plkbyt,IStorage*pstgPriority,DWORD grfMode,SNB snbExclude,DWORD reserved,IStorage**ppstgOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgOpenStorageOnILockBytes(plkbyt,pstgPriority,grfMode,snbExclude,reserved,ppstgOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgIsStorageFile(const OLECHAR*pwcsName)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgIsStorageFile(pwcsName);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgIsStorageILockBytes(ILockBytes*plkbyt)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgIsStorageILockBytes(plkbyt);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgSetTimes(OLECHAR const*lpszName,FILETIME const*pctime,FILETIME const*patime,FILETIME const*pmtime)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgSetTimes(lpszName,pctime,patime,pmtime);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgOpenAsyncDocfileOnIFillLockBytes(IFillLockBytes*pflb,DWORD grfMode,DWORD asyncFlags,IStorage**ppstgOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgOpenAsyncDocfileOnIFillLockBytes(pflb,grfMode,asyncFlags,ppstgOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgGetIFillLockBytesOnILockBytes(ILockBytes*pilb,IFillLockBytes**ppflb)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgGetIFillLockBytesOnILockBytes(pilb,ppflb);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgGetIFillLockBytesOnFile(OLECHAR const*pwcsName,IFillLockBytes**ppflb)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgGetIFillLockBytesOnFile(pwcsName,ppflb);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgCreateStorageEx(const WCHAR*pwcsName,DWORD grfMode,DWORD stgfmt,DWORD grfAttrs,STGOPTIONS*pStgOptions,void*reserved,REFIID riid,void**ppObjectOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgCreateStorageEx(pwcsName,grfMode,stgfmt,grfAttrs,pStgOptions,reserved,riid,ppObjectOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareStgOpenStorageEx(const WCHAR*pwcsName,DWORD grfMode,DWORD stgfmt,DWORD grfAttrs,STGOPTIONS*pStgOptions,void*reserved,REFIID riid,void**ppObjectOpen)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = StgOpenStorageEx(pwcsName,grfMode,stgfmt,grfAttrs,pStgOptions,reserved,riid,ppObjectOpen);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareBindMoniker(LPMONIKER pmk,DWORD grfOpt,REFIID iidResult,LPVOID*ppvResult)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = BindMoniker(pmk,grfOpt,iidResult,ppvResult);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoInstall(IBindCtx*pbc,DWORD dwFlags,uCLSSPEC*pClassSpec,QUERYCONTEXT*pQuery,LPWSTR pszCodeBase)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoInstall(pbc,dwFlags,pClassSpec,pQuery,pszCodeBase);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCoGetObject(LPCWSTR pszName,BIND_OPTS*pBindOptions,REFIID riid,void**ppv)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CoGetObject(pszName,pBindOptions,riid,ppv);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareMkParseDisplayName(LPBC pbc,LPCOLESTR szUserName,ULONG*pchEaten,LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = MkParseDisplayName(pbc,szUserName,pchEaten,ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareMonikerRelativePathTo(LPMONIKER pmkSrc,LPMONIKER pmkDest,LPMONIKER*ppmkRelPath,BOOL dwReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = MonikerRelativePathTo(pmkSrc,pmkDest,ppmkRelPath,dwReserved);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareMonikerCommonPrefixWith(LPMONIKER pmkThis,LPMONIKER pmkOther,LPMONIKER*ppmkCommon)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = MonikerCommonPrefixWith(pmkThis,pmkOther,ppmkCommon);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateBindCtx(DWORD reserved,LPBC*ppbc)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateBindCtx(reserved,ppbc);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateGenericComposite(LPMONIKER pmkFirst,LPMONIKER pmkRest,LPMONIKER*ppmkComposite)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateGenericComposite(pmkFirst,pmkRest,ppmkComposite);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareGetClassFile(LPCOLESTR szFilename,CLSID*pclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = GetClassFile(szFilename,pclsid);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateClassMoniker(REFCLSID rclsid,LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateClassMoniker(rclsid,ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateFileMoniker(LPCOLESTR lpszPathName,LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateFileMoniker(lpszPathName,ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateItemMoniker(LPCOLESTR lpszDelim,LPCOLESTR lpszItem,LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateItemMoniker(lpszDelim,lpszItem,ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateAntiMoniker(LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateAntiMoniker(ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreatePointerMoniker(LPUNKNOWN punk,LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreatePointerMoniker(punk,ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateObjrefMoniker(LPUNKNOWN punk,LPMONIKER*ppmk)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateObjrefMoniker(punk,ppmk);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareGetRunningObjectTable(DWORD reserved,LPRUNNINGOBJECTTABLE*pprot)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = GetRunningObjectTable(reserved,pprot);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateStdProgressIndicator(HWND hwndParent,LPCOLESTR pszTitle,IBindStatusCallback*pIbscCaller,IBindStatusCallback**ppIbsc)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return ObjbaseIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateStdProgressIndicator(hwndParent,pszTitle,pIbscCaller,ppIbsc);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
        }
    }
    return result;
}

#endif /* ISOLATION_AWARE_USE_STATIC_LIBRARY */

#define BindMoniker IsolationAwareBindMoniker
#define CLSIDFromProgID IsolationAwareCLSIDFromProgID
#define CLSIDFromProgIDEx IsolationAwareCLSIDFromProgIDEx
#define CLSIDFromString IsolationAwareCLSIDFromString
#define CoAllowSetForegroundWindow IsolationAwareCoAllowSetForegroundWindow
#define CoCancelCall IsolationAwareCoCancelCall
#define CoCopyProxy IsolationAwareCoCopyProxy
#define CoCreateFreeThreadedMarshaler IsolationAwareCoCreateFreeThreadedMarshaler
#define CoCreateGuid IsolationAwareCoCreateGuid
#define CoCreateInstance IsolationAwareCoCreateInstance
#define CoCreateInstanceEx IsolationAwareCoCreateInstanceEx
#define CoDisableCallCancellation IsolationAwareCoDisableCallCancellation
#define CoDisconnectObject IsolationAwareCoDisconnectObject
#define CoEnableCallCancellation IsolationAwareCoEnableCallCancellation
#define CoFileTimeNow IsolationAwareCoFileTimeNow
#define CoGetCallContext IsolationAwareCoGetCallContext
#define CoGetCallerTID IsolationAwareCoGetCallerTID
#define CoGetCancelObject IsolationAwareCoGetCancelObject
#define CoGetClassObject IsolationAwareCoGetClassObject
#define CoGetContextToken IsolationAwareCoGetContextToken
#define CoGetInstanceFromFile IsolationAwareCoGetInstanceFromFile
#define CoGetInstanceFromIStorage IsolationAwareCoGetInstanceFromIStorage
#define CoGetInterfaceAndReleaseStream IsolationAwareCoGetInterfaceAndReleaseStream
#define CoGetMalloc IsolationAwareCoGetMalloc
#define CoGetMarshalSizeMax IsolationAwareCoGetMarshalSizeMax
#define CoGetObject IsolationAwareCoGetObject
#define CoGetObjectContext IsolationAwareCoGetObjectContext
#define CoGetPSClsid IsolationAwareCoGetPSClsid
#define CoGetStandardMarshal IsolationAwareCoGetStandardMarshal
#define CoGetStdMarshalEx IsolationAwareCoGetStdMarshalEx
#define CoGetTreatAsClass IsolationAwareCoGetTreatAsClass
#define CoImpersonateClient IsolationAwareCoImpersonateClient
#define CoInitialize IsolationAwareCoInitialize
#define CoInitializeEx IsolationAwareCoInitializeEx
#define CoInitializeSecurity IsolationAwareCoInitializeSecurity
#define CoInstall IsolationAwareCoInstall
#define CoInvalidateRemoteMachineBindings IsolationAwareCoInvalidateRemoteMachineBindings
#define CoLoadLibrary IsolationAwareCoLoadLibrary
#define CoLockObjectExternal IsolationAwareCoLockObjectExternal
#define CoMarshalHresult IsolationAwareCoMarshalHresult
#define CoMarshalInterThreadInterfaceInStream IsolationAwareCoMarshalInterThreadInterfaceInStream
#define CoMarshalInterface IsolationAwareCoMarshalInterface
#define CoQueryAuthenticationServices IsolationAwareCoQueryAuthenticationServices
#define CoQueryClientBlanket IsolationAwareCoQueryClientBlanket
#define CoQueryProxyBlanket IsolationAwareCoQueryProxyBlanket
#define CoRegisterChannelHook IsolationAwareCoRegisterChannelHook
#define CoRegisterClassObject IsolationAwareCoRegisterClassObject
#define CoRegisterInitializeSpy IsolationAwareCoRegisterInitializeSpy
#define CoRegisterMallocSpy IsolationAwareCoRegisterMallocSpy
#define CoRegisterMessageFilter IsolationAwareCoRegisterMessageFilter
#define CoRegisterPSClsid IsolationAwareCoRegisterPSClsid
#define CoRegisterSurrogate IsolationAwareCoRegisterSurrogate
#define CoReleaseMarshalData IsolationAwareCoReleaseMarshalData
#define CoResumeClassObjects IsolationAwareCoResumeClassObjects
#define CoRevertToSelf IsolationAwareCoRevertToSelf
#define CoRevokeClassObject IsolationAwareCoRevokeClassObject
#define CoRevokeInitializeSpy IsolationAwareCoRevokeInitializeSpy
#define CoRevokeMallocSpy IsolationAwareCoRevokeMallocSpy
#define CoSetApartmentLockState IsolationAwareCoSetApartmentLockState
#define CoSetCancelObject IsolationAwareCoSetCancelObject
#define CoSetProxyBlanket IsolationAwareCoSetProxyBlanket
#define CoStdMarshalObject IsolationAwareCoStdMarshalObject
#define CoSuspendClassObjects IsolationAwareCoSuspendClassObjects
#define CoSwitchCallContext IsolationAwareCoSwitchCallContext
#define CoTestCancel IsolationAwareCoTestCancel
#define CoTreatAsClass IsolationAwareCoTreatAsClass
#define CoUnmarshalHresult IsolationAwareCoUnmarshalHresult
#define CoUnmarshalInterface IsolationAwareCoUnmarshalInterface
#define CoWaitForMultipleHandles IsolationAwareCoWaitForMultipleHandles
#define CreateAntiMoniker IsolationAwareCreateAntiMoniker
#define CreateBindCtx IsolationAwareCreateBindCtx
#define CreateClassMoniker IsolationAwareCreateClassMoniker
#define CreateDataAdviseHolder IsolationAwareCreateDataAdviseHolder
#define CreateDataCache IsolationAwareCreateDataCache
#define CreateFileMoniker IsolationAwareCreateFileMoniker
#define CreateGenericComposite IsolationAwareCreateGenericComposite
#define CreateItemMoniker IsolationAwareCreateItemMoniker
#define CreateObjrefMoniker IsolationAwareCreateObjrefMoniker
#define CreatePointerMoniker IsolationAwareCreatePointerMoniker
#define CreateStdProgressIndicator IsolationAwareCreateStdProgressIndicator
#define DcomChannelSetHResult IsolationAwareDcomChannelSetHResult
#define GetClassFile IsolationAwareGetClassFile
#define GetRunningObjectTable IsolationAwareGetRunningObjectTable
#define IIDFromString IsolationAwareIIDFromString
#define MkParseDisplayName IsolationAwareMkParseDisplayName
#define MonikerCommonPrefixWith IsolationAwareMonikerCommonPrefixWith
#define MonikerRelativePathTo IsolationAwareMonikerRelativePathTo
#define ProgIDFromCLSID IsolationAwareProgIDFromCLSID
#define StgCreateDocfile IsolationAwareStgCreateDocfile
#define StgCreateDocfileOnILockBytes IsolationAwareStgCreateDocfileOnILockBytes
#define StgCreateStorageEx IsolationAwareStgCreateStorageEx
#define StgGetIFillLockBytesOnFile IsolationAwareStgGetIFillLockBytesOnFile
#define StgGetIFillLockBytesOnILockBytes IsolationAwareStgGetIFillLockBytesOnILockBytes
#define StgIsStorageFile IsolationAwareStgIsStorageFile
#define StgIsStorageILockBytes IsolationAwareStgIsStorageILockBytes
#define StgOpenAsyncDocfileOnIFillLockBytes IsolationAwareStgOpenAsyncDocfileOnIFillLockBytes
#define StgOpenStorage IsolationAwareStgOpenStorage
#define StgOpenStorageEx IsolationAwareStgOpenStorageEx
#define StgOpenStorageOnILockBytes IsolationAwareStgOpenStorageOnILockBytes
#define StgSetTimes IsolationAwareStgSetTimes

#endif /* ISOLATION_AWARE_ENABLED */
#endif /* RC */


#if defined(__cplusplus)
} /* __cplusplus */
#endif



#ifndef RC_INVOKED
#include <poppack.h>
#endif // RC_INVOKED

#endif     // __OBJBASE_H__

