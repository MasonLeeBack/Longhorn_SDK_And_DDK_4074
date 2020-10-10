
//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  File:       OLE2.h
//  Contents:   Main OLE2 header; Defines Linking and Emmebbeding interfaces, and API's.
//              Also includes .h files for the compobj, and oleauto  subcomponents.
//
//----------------------------------------------------------------------------
#if !defined( _OLE2_H_ )
#define _OLE2_H_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _MAC
// Set packing to 8
#include <pshpack8.h>

// Make 100% sure WIN32 is defined
#ifndef WIN32
#define WIN32    100  // 100 == NT version 1.0
#endif
#else //_MAC
#ifdef _WIN32
#include "macname1.h"
#endif // _WIN32
#endif //_MAC



// SET to remove _export from interface definitions


#include <winerror.h>

#ifdef _MAC
#if !defined(__MACPUB__)
#include <macpub.h>
#endif
#endif //_MAC

#include <objbase.h>
#include <oleauto.h>

// View OBJECT Error Codes

#define E_DRAW                  VIEW_E_DRAW

// IDataObject Error Codes
#define DATA_E_FORMATETC        DV_E_FORMATETC


#ifdef _MAC
/****** Standard Object Definitions *****************************************/

//#ifndef __COMPOBJ__
//#include <compobj.h>
//#endif



typedef enum {
	OLE_E_NOEXTENSION	= OLE_E_NOSTORAGE +1,	// no extension at startup
	OLE_E_VERSEXTENSION,						// extension has wrong version #
	OLE_E_IPBUSY,								// cannot get inplace resource
	OLE_E_NOT_FRONT_PROCESS,					// inplace container unexpectedly in background
	OLE_E_WRONG_MENU,							// holemenu != prev holemenu
	OLE_E_MENU_NOT_PATCHED,						// menubar is not hashed
	OLE_E_MENUID_NOT_HASHED,					// id was never hashed
	OLE_E_foo
} inplace_errors;


// DoDragDropMac()
typedef struct tagDRAG_FLAVORINFO {
	unsigned long	cfFormat;
	unsigned long	FlavorFlags;		// Flavor Flags as specified by the DragManager
	OLEBOOL			fAddData;			// If true, the data is added with the flavor
	long			reserved;			// must be NULL
} DRAG_FLAVORINFO;

#endif //_MAC


// Common stuff gleamed from OLE.2,

/* verbs */
#define OLEIVERB_PRIMARY            (0L)
#define OLEIVERB_SHOW               (-1L)
#define OLEIVERB_OPEN               (-2L)
#define OLEIVERB_HIDE               (-3L)
#define OLEIVERB_UIACTIVATE         (-4L)
#define OLEIVERB_INPLACEACTIVATE    (-5L)
#define OLEIVERB_DISCARDUNDOSTATE   (-6L)

// for OleCreateEmbeddingHelper flags; roles in low word; options in high word
#define EMBDHLP_INPROC_HANDLER   0x0000L
#define EMBDHLP_INPROC_SERVER    0x0001L
#define EMBDHLP_CREATENOW    0x00000000L
#define EMBDHLP_DELAYCREATE  0x00010000L

/* extended create function flags */
#define OLECREATE_LEAVERUNNING	0x00000001

/* pull in the MIDL generated header */

#include <oleidl.h>


#ifdef _MAC
typedef struct tagOleMBarRec
{
        long reserved;
} OleMBarRec, *OleMBarPtr, **OleMBarHandle;

#define noAxis  3               // indicates no grow or size in any direction
// see mac #defines noConstraint, hAxisOnly, vAxisOnly

#endif //_MAC


/****** OLE API Prototypes ************************************************/

WINOLEAPI_(DWORD) OleBuildVersion( VOID );

/* helper functions */
WINOLEAPI ReadClassStg(IN LPSTORAGE pStg, OUT CLSID FAR* pclsid);
WINOLEAPI WriteClassStg(IN LPSTORAGE pStg, IN REFCLSID rclsid);
WINOLEAPI ReadClassStm(IN LPSTREAM pStm, OUT CLSID FAR* pclsid);
WINOLEAPI WriteClassStm(IN LPSTREAM pStm, IN REFCLSID rclsid);
WINOLEAPI WriteFmtUserTypeStg (IN LPSTORAGE pstg, IN CLIPFORMAT cf, IN LPOLESTR lpszUserType);
WINOLEAPI ReadFmtUserTypeStg (IN LPSTORAGE pstg, OUT CLIPFORMAT FAR* pcf, OUT LPOLESTR FAR* lplpszUserType);


/* init/term */

WINOLEAPI OleInitialize(IN LPVOID pvReserved);
WINOLEAPI_(void) OleUninitialize(void);


/* APIs to query whether (Embedded/Linked) object can be created from
   the data object */

WINOLEAPI  OleQueryLinkFromData(IN LPDATAOBJECT pSrcDataObject);
WINOLEAPI  OleQueryCreateFromData(IN LPDATAOBJECT pSrcDataObject);


/* Object creation APIs */

WINOLEAPI  OleCreate(IN REFCLSID rclsid, IN REFIID riid, IN DWORD renderopt,
                IN LPFORMATETC pFormatEtc, IN LPOLECLIENTSITE pClientSite,
                IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateEx(IN REFCLSID rclsid, IN REFIID riid, IN DWORD dwFlags,
                IN DWORD renderopt, IN ULONG cFormats, IN DWORD* rgAdvf,
                IN LPFORMATETC rgFormatEtc, IN IAdviseSink FAR* lpAdviseSink,
                OUT DWORD FAR* rgdwConnection, IN LPOLECLIENTSITE pClientSite,
                IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromData(IN LPDATAOBJECT pSrcDataObj, IN REFIID riid,
                IN DWORD renderopt, IN LPFORMATETC pFormatEtc,
                IN LPOLECLIENTSITE pClientSite, IN LPSTORAGE pStg,
                OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromDataEx(IN LPDATAOBJECT pSrcDataObj, IN REFIID riid,
                IN DWORD dwFlags, IN DWORD renderopt, IN ULONG cFormats, IN DWORD* rgAdvf,
                IN LPFORMATETC rgFormatEtc, IN IAdviseSink FAR* lpAdviseSink,
                OUT DWORD FAR* rgdwConnection, IN LPOLECLIENTSITE pClientSite,
                IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkFromData(IN LPDATAOBJECT pSrcDataObj, IN REFIID riid,
                IN DWORD renderopt, IN LPFORMATETC pFormatEtc,
                IN LPOLECLIENTSITE pClientSite, IN LPSTORAGE pStg,
                OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkFromDataEx(IN LPDATAOBJECT pSrcDataObj, IN REFIID riid,
                IN DWORD dwFlags, IN DWORD renderopt, IN ULONG cFormats, IN DWORD* rgAdvf,
                IN LPFORMATETC rgFormatEtc, IN IAdviseSink FAR* lpAdviseSink,
                OUT IN DWORD FAR* rgdwConnection, IN LPOLECLIENTSITE pClientSite,
                IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateStaticFromData(IN LPDATAOBJECT pSrcDataObj, IN REFIID iid,
                IN DWORD renderopt, IN LPFORMATETC pFormatEtc,
                IN LPOLECLIENTSITE pClientSite, IN LPSTORAGE pStg,
                OUT LPVOID FAR* ppvObj);


WINOLEAPI  OleCreateLink(IN LPMONIKER pmkLinkSrc, IN REFIID riid,
            IN DWORD renderopt, IN LPFORMATETC lpFormatEtc,
            IN LPOLECLIENTSITE pClientSite, IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkEx(IN LPMONIKER pmkLinkSrc, IN REFIID riid,
            IN DWORD dwFlags, IN DWORD renderopt, IN ULONG cFormats, IN DWORD* rgAdvf,
            IN LPFORMATETC rgFormatEtc, IN IAdviseSink FAR* lpAdviseSink,
            OUT DWORD FAR* rgdwConnection, IN LPOLECLIENTSITE pClientSite,
            IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkToFile(IN LPCOLESTR lpszFileName, IN REFIID riid,
            IN DWORD renderopt, IN LPFORMATETC lpFormatEtc,
            IN LPOLECLIENTSITE pClientSite, IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateLinkToFileEx(IN LPCOLESTR lpszFileName, IN REFIID riid,
            IN DWORD dwFlags, IN DWORD renderopt, IN ULONG cFormats, IN DWORD* rgAdvf,
            IN LPFORMATETC rgFormatEtc, IN IAdviseSink FAR* lpAdviseSink,
            OUT DWORD FAR* rgdwConnection, IN LPOLECLIENTSITE pClientSite,
            IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromFile(IN REFCLSID rclsid, IN LPCOLESTR lpszFileName, IN REFIID riid,
            IN DWORD renderopt, IN LPFORMATETC lpFormatEtc,
            IN LPOLECLIENTSITE pClientSite, IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleCreateFromFileEx(IN REFCLSID rclsid, IN LPCOLESTR lpszFileName, IN REFIID riid,
            IN DWORD dwFlags, IN DWORD renderopt, IN ULONG cFormats, IN DWORD* rgAdvf,
            IN LPFORMATETC rgFormatEtc, IN IAdviseSink FAR* lpAdviseSink,
            OUT DWORD FAR* rgdwConnection, IN LPOLECLIENTSITE pClientSite,
            IN LPSTORAGE pStg, OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleLoad(IN LPSTORAGE pStg, IN REFIID riid, IN LPOLECLIENTSITE pClientSite,
            OUT LPVOID FAR* ppvObj);

WINOLEAPI  OleSave(IN LPPERSISTSTORAGE pPS, IN LPSTORAGE pStg, IN BOOL fSameAsLoad);

WINOLEAPI  OleLoadFromStream( IN LPSTREAM pStm, IN REFIID iidInterface, OUT LPVOID FAR* ppvObj);
WINOLEAPI  OleSaveToStream( IN LPPERSISTSTREAM pPStm, IN LPSTREAM pStm );


WINOLEAPI  OleSetContainedObject(IN LPUNKNOWN pUnknown, IN BOOL fContained);
WINOLEAPI  OleNoteObjectVisible(IN LPUNKNOWN pUnknown, IN BOOL fVisible);


/* Drag/Drop APIs */

WINOLEAPI  RegisterDragDrop(IN HWND hwnd, IN LPDROPTARGET pDropTarget);
WINOLEAPI  RevokeDragDrop(IN HWND hwnd);
WINOLEAPI  DoDragDrop(IN LPDATAOBJECT pDataObj, IN LPDROPSOURCE pDropSource,
            IN DWORD dwOKEffects, OUT LPDWORD pdwEffect);

/* Clipboard APIs */

WINOLEAPI  OleSetClipboard(IN LPDATAOBJECT pDataObj);
WINOLEAPI  OleGetClipboard(OUT LPDATAOBJECT FAR* ppDataObj);
WINOLEAPI  OleFlushClipboard(void);
WINOLEAPI  OleIsCurrentClipboard(IN LPDATAOBJECT pDataObj);


/* InPlace Editing APIs */

WINOLEAPI_(HOLEMENU)   OleCreateMenuDescriptor (IN HMENU hmenuCombined,
                                IN LPOLEMENUGROUPWIDTHS lpMenuWidths);
WINOLEAPI              OleSetMenuDescriptor (IN HOLEMENU holemenu, IN HWND hwndFrame,
                                IN HWND hwndActiveObject,
                                IN LPOLEINPLACEFRAME lpFrame,
                                IN LPOLEINPLACEACTIVEOBJECT lpActiveObj);
WINOLEAPI              OleDestroyMenuDescriptor (IN HOLEMENU holemenu);

WINOLEAPI              OleTranslateAccelerator (IN LPOLEINPLACEFRAME lpFrame,
                            IN LPOLEINPLACEFRAMEINFO lpFrameInfo, IN LPMSG lpmsg);


/* Helper APIs */
WINOLEAPI_(HANDLE) OleDuplicateData (IN HANDLE hSrc, IN CLIPFORMAT cfFormat,
                        IN UINT uiFlags);

WINOLEAPI          OleDraw (IN LPUNKNOWN pUnknown, IN DWORD dwAspect, IN HDC hdcDraw,
                    IN LPCRECT lprcBounds);

WINOLEAPI          OleRun(IN LPUNKNOWN pUnknown);
WINOLEAPI_(BOOL)   OleIsRunning(IN LPOLEOBJECT pObject);
WINOLEAPI          OleLockRunning(IN LPUNKNOWN pUnknown, IN BOOL fLock, IN BOOL fLastUnlockCloses);
WINOLEAPI_(void)   ReleaseStgMedium(IN LPSTGMEDIUM);
WINOLEAPI          CreateOleAdviseHolder(OUT LPOLEADVISEHOLDER FAR* ppOAHolder);

WINOLEAPI          OleCreateDefaultHandler(IN REFCLSID clsid, IN LPUNKNOWN pUnkOuter,
                    IN REFIID riid, OUT LPVOID FAR* lplpObj);

WINOLEAPI          OleCreateEmbeddingHelper(IN REFCLSID clsid, IN LPUNKNOWN pUnkOuter,
                    IN DWORD flags, IN LPCLASSFACTORY pCF,
                    IN REFIID riid, OUT LPVOID FAR* lplpObj);

WINOLEAPI_(BOOL)   IsAccelerator(IN HACCEL hAccel, IN int cAccelEntries, IN LPMSG lpMsg,
                                        OUT WORD FAR* lpwCmd);
/* Icon extraction Helper APIs */

WINOLEAPI_(HGLOBAL) OleGetIconOfFile(IN LPOLESTR lpszPath, IN BOOL fUseFileAsLabel);

WINOLEAPI_(HGLOBAL) OleGetIconOfClass(IN REFCLSID rclsid,     IN LPOLESTR lpszLabel,
                                        IN BOOL fUseTypeAsLabel);

WINOLEAPI_(HGLOBAL) OleMetafilePictFromIconAndLabel(IN HICON hIcon, IN LPOLESTR lpszLabel,
                                        IN LPOLESTR lpszSourceFile, IN UINT iIconIndex);



/* Registration Database Helper APIs */

WINOLEAPI                  OleRegGetUserType (IN REFCLSID clsid, IN DWORD dwFormOfType,
                                        OUT LPOLESTR FAR* pszUserType);

WINOLEAPI                  OleRegGetMiscStatus     (IN REFCLSID clsid, IN DWORD dwAspect,
                                        OUT DWORD FAR* pdwStatus);

WINOLEAPI                  OleRegEnumFormatEtc     (IN REFCLSID clsid, IN DWORD dwDirection,
                                        OUT LPENUMFORMATETC FAR* ppenum);

WINOLEAPI                  OleRegEnumVerbs (IN REFCLSID clsid, OUT LPENUMOLEVERB FAR* ppenum);

#ifdef _MAC
/* WlmOLE helper APIs */

WINOLEAPI WlmOleCheckoutMacInterface(LPUNKNOWN pUnk, LPVOID* ppv);
WINOLEAPI WlmOleCheckinMacInterface(LPUNKNOWN pUnk);
WINOLEAPI WlmOleWrapMacInterface(LPUNKNOWN pUnk, REFIID riid, LPVOID* ppv);
WINOLEAPI WlmOleUnwrapMacInterface(LPVOID pv);

WINOLEAPI WlmOleCheckoutWinInterface(LPVOID pUnk, LPUNKNOWN* ppv);
WINOLEAPI WlmOleCheckinWinInterface(LPVOID pUnk);
WINOLEAPI WlmOleWrapWinInterface(LPVOID pUnk, REFIID riid, LPUNKNOWN* ppv);
WINOLEAPI WlmOleUnwrapWinInterface(LPVOID pv);

WINOLEAPI_(void) WlmOleVersion(void);
WINOLEAPI_(void) WlmOleSetInPlaceWindow(HWND hwnd);

typedef HRESULT (STDAPICALLTYPE* OLEWRAPPROC) (REFIID riid, LPVOID* ppvWin, LPVOID* ppvMac);
WINOLEAPI WlmOleRegisterUserWrap(OLEWRAPPROC procNew, OLEWRAPPROC* pprocOld);
#endif


/* OLE 1.0 conversion APIS */

/***** OLE 1.0 OLESTREAM declarations *************************************/

typedef struct _OLESTREAM FAR*  LPOLESTREAM;

typedef struct _OLESTREAMVTBL
{
    DWORD (CALLBACK* Get)(LPOLESTREAM, void FAR*, DWORD);
    DWORD (CALLBACK* Put)(LPOLESTREAM, const void FAR*, DWORD);
} OLESTREAMVTBL;
typedef  OLESTREAMVTBL FAR*  LPOLESTREAMVTBL;

typedef struct _OLESTREAM
{
    LPOLESTREAMVTBL lpstbl;
} OLESTREAM;


WINOLEAPI OleConvertOLESTREAMToIStorage
    (IN LPOLESTREAM                lpolestream,
    OUT LPSTORAGE                   pstg,
    IN const DVTARGETDEVICE FAR*   ptd);

WINOLEAPI OleConvertIStorageToOLESTREAM
    (IN LPSTORAGE      pstg,
    OUT LPOLESTREAM     lpolestream);


/* Storage Utility APIs */
WINOLEAPI GetHGlobalFromILockBytes (IN LPLOCKBYTES plkbyt, OUT HGLOBAL FAR* phglobal);
WINOLEAPI CreateILockBytesOnHGlobal (IN HGLOBAL hGlobal, IN BOOL fDeleteOnRelease,
                                    OUT LPLOCKBYTES FAR* pplkbyt);

WINOLEAPI GetHGlobalFromStream (IN LPSTREAM pstm, OUT HGLOBAL FAR* phglobal);
WINOLEAPI CreateStreamOnHGlobal (IN HGLOBAL hGlobal, IN BOOL fDeleteOnRelease,
                                OUT LPSTREAM FAR* ppstm);


/* ConvertTo APIS */

WINOLEAPI OleDoAutoConvert(IN LPSTORAGE pStg, OUT LPCLSID pClsidNew);
WINOLEAPI OleGetAutoConvert(IN REFCLSID clsidOld, OUT LPCLSID pClsidNew);
WINOLEAPI OleSetAutoConvert(IN REFCLSID clsidOld, IN REFCLSID clsidNew);
WINOLEAPI GetConvertStg(IN LPSTORAGE pStg);
WINOLEAPI SetConvertStg(IN LPSTORAGE pStg, IN BOOL fConvert);


WINOLEAPI OleConvertIStorageToOLESTREAMEx
    (IN LPSTORAGE          pstg,
                                    // Presentation data to OLESTREAM
     IN CLIPFORMAT         cfFormat,   //      format
     IN LONG               lWidth,     //      width
     IN LONG               lHeight,    //      height
     IN DWORD              dwSize,     //      size in bytes
     IN LPSTGMEDIUM        pmedium,    //      bits
     OUT LPOLESTREAM        polestm);

WINOLEAPI OleConvertOLESTREAMToIStorageEx
    (IN LPOLESTREAM        polestm,
     OUT LPSTORAGE          pstg,
                                    // Presentation data from OLESTREAM
     OUT CLIPFORMAT FAR*    pcfFormat,  //      format
     OUT LONG FAR*          plwWidth,   //      width
     OUT LONG FAR*          plHeight,   //      height
     OUT DWORD FAR*         pdwSize,    //      size in bytes
     OUT LPSTGMEDIUM        pmedium);   //      bits

#ifndef _MAC
#ifndef RC_INVOKED
#include <poppack.h>
#endif // RC_INVOKED

#else // _MAC

#ifndef __MACAPI__
#include <macapi.h>
#endif

#ifdef _WIN32
#include "macname2.h"
#endif // _WIN32

#endif // _MAC

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
HRESULT WINAPI IsolationAwareReadClassStg(LPSTORAGE pStg,CLSID*pclsid);
HRESULT WINAPI IsolationAwareWriteClassStg(LPSTORAGE pStg,REFCLSID rclsid);
HRESULT WINAPI IsolationAwareReadClassStm(LPSTREAM pStm,CLSID*pclsid);
HRESULT WINAPI IsolationAwareWriteClassStm(LPSTREAM pStm,REFCLSID rclsid);
HRESULT WINAPI IsolationAwareWriteFmtUserTypeStg(LPSTORAGE pstg,CLIPFORMAT cf,LPOLESTR lpszUserType);
HRESULT WINAPI IsolationAwareReadFmtUserTypeStg(LPSTORAGE pstg,CLIPFORMAT*pcf,LPOLESTR*lplpszUserType);
HRESULT WINAPI IsolationAwareOleInitialize(LPVOID pvReserved);
HRESULT WINAPI IsolationAwareOleQueryLinkFromData(LPDATAOBJECT pSrcDataObject);
HRESULT WINAPI IsolationAwareOleQueryCreateFromData(LPDATAOBJECT pSrcDataObject);
HRESULT WINAPI IsolationAwareOleCreate(REFCLSID rclsid,REFIID riid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateEx(REFCLSID rclsid,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateFromData(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateFromDataEx(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateLinkFromData(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateLinkFromDataEx(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateStaticFromData(LPDATAOBJECT pSrcDataObj,REFIID iid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateLink(LPMONIKER pmkLinkSrc,REFIID riid,DWORD renderopt,LPFORMATETC lpFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateLinkEx(LPMONIKER pmkLinkSrc,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateLinkToFile(LPCOLESTR lpszFileName,REFIID riid,DWORD renderopt,LPFORMATETC lpFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateLinkToFileEx(LPCOLESTR lpszFileName,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateFromFile(REFCLSID rclsid,LPCOLESTR lpszFileName,REFIID riid,DWORD renderopt,LPFORMATETC lpFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleCreateFromFileEx(REFCLSID rclsid,LPCOLESTR lpszFileName,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleLoad(LPSTORAGE pStg,REFIID riid,LPOLECLIENTSITE pClientSite,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleSave(LPPERSISTSTORAGE pPS,LPSTORAGE pStg,BOOL fSameAsLoad);
HRESULT WINAPI IsolationAwareOleLoadFromStream(LPSTREAM pStm,REFIID iidInterface,LPVOID*ppvObj);
HRESULT WINAPI IsolationAwareOleSaveToStream(LPPERSISTSTREAM pPStm,LPSTREAM pStm);
HRESULT WINAPI IsolationAwareOleSetContainedObject(LPUNKNOWN pUnknown,BOOL fContained);
HRESULT WINAPI IsolationAwareOleNoteObjectVisible(LPUNKNOWN pUnknown,BOOL fVisible);
HRESULT WINAPI IsolationAwareRegisterDragDrop(HWND hwnd,LPDROPTARGET pDropTarget);
HRESULT WINAPI IsolationAwareRevokeDragDrop(HWND hwnd);
HRESULT WINAPI IsolationAwareDoDragDrop(LPDATAOBJECT pDataObj,LPDROPSOURCE pDropSource,DWORD dwOKEffects,LPDWORD pdwEffect);
HRESULT WINAPI IsolationAwareOleSetClipboard(LPDATAOBJECT pDataObj);
HRESULT WINAPI IsolationAwareOleGetClipboard(LPDATAOBJECT*ppDataObj);
HRESULT WINAPI IsolationAwareOleFlushClipboard(void);
HRESULT WINAPI IsolationAwareOleIsCurrentClipboard(LPDATAOBJECT pDataObj);
HOLEMENU WINAPI IsolationAwareOleCreateMenuDescriptor(HMENU hmenuCombined,LPOLEMENUGROUPWIDTHS lpMenuWidths);
HRESULT WINAPI IsolationAwareOleSetMenuDescriptor(HOLEMENU holemenu,HWND hwndFrame,HWND hwndActiveObject,LPOLEINPLACEFRAME lpFrame,LPOLEINPLACEACTIVEOBJECT lpActiveObj);
HRESULT WINAPI IsolationAwareOleDestroyMenuDescriptor(HOLEMENU holemenu);
HRESULT WINAPI IsolationAwareOleTranslateAccelerator(LPOLEINPLACEFRAME lpFrame,LPOLEINPLACEFRAMEINFO lpFrameInfo,LPMSG lpmsg);
HANDLE WINAPI IsolationAwareOleDuplicateData(HANDLE hSrc,CLIPFORMAT cfFormat,UINT uiFlags);
HRESULT WINAPI IsolationAwareOleDraw(LPUNKNOWN pUnknown,DWORD dwAspect,HDC hdcDraw,LPCRECT lprcBounds);
HRESULT WINAPI IsolationAwareOleRun(LPUNKNOWN pUnknown);
HRESULT WINAPI IsolationAwareOleLockRunning(LPUNKNOWN pUnknown,BOOL fLock,BOOL fLastUnlockCloses);
HRESULT WINAPI IsolationAwareCreateOleAdviseHolder(LPOLEADVISEHOLDER*ppOAHolder);
HRESULT WINAPI IsolationAwareOleCreateDefaultHandler(REFCLSID clsid,LPUNKNOWN pUnkOuter,REFIID riid,LPVOID*lplpObj);
HRESULT WINAPI IsolationAwareOleCreateEmbeddingHelper(REFCLSID clsid,LPUNKNOWN pUnkOuter,DWORD flags,LPCLASSFACTORY pCF,REFIID riid,LPVOID*lplpObj);
HGLOBAL WINAPI IsolationAwareOleGetIconOfFile(LPOLESTR lpszPath,BOOL fUseFileAsLabel);
HGLOBAL WINAPI IsolationAwareOleGetIconOfClass(REFCLSID rclsid,LPOLESTR lpszLabel,BOOL fUseTypeAsLabel);
HGLOBAL WINAPI IsolationAwareOleMetafilePictFromIconAndLabel(HICON hIcon,LPOLESTR lpszLabel,LPOLESTR lpszSourceFile,UINT iIconIndex);
HRESULT WINAPI IsolationAwareOleRegGetUserType(REFCLSID clsid,DWORD dwFormOfType,LPOLESTR*pszUserType);
HRESULT WINAPI IsolationAwareOleRegGetMiscStatus(REFCLSID clsid,DWORD dwAspect,DWORD*pdwStatus);
HRESULT WINAPI IsolationAwareOleRegEnumFormatEtc(REFCLSID clsid,DWORD dwDirection,LPENUMFORMATETC*ppenum);
HRESULT WINAPI IsolationAwareOleRegEnumVerbs(REFCLSID clsid,LPENUMOLEVERB*ppenum);
HRESULT WINAPI IsolationAwareOleConvertIStorageToOLESTREAM(LPSTORAGE pstg,LPOLESTREAM lpolestream);
HRESULT WINAPI IsolationAwareGetHGlobalFromILockBytes(LPLOCKBYTES plkbyt,HGLOBAL*phglobal);
HRESULT WINAPI IsolationAwareCreateILockBytesOnHGlobal(HGLOBAL hGlobal,BOOL fDeleteOnRelease,LPLOCKBYTES*pplkbyt);
HRESULT WINAPI IsolationAwareGetHGlobalFromStream(LPSTREAM pstm,HGLOBAL*phglobal);
HRESULT WINAPI IsolationAwareCreateStreamOnHGlobal(HGLOBAL hGlobal,BOOL fDeleteOnRelease,LPSTREAM*ppstm);
HRESULT WINAPI IsolationAwareOleDoAutoConvert(LPSTORAGE pStg,LPCLSID pClsidNew);
HRESULT WINAPI IsolationAwareOleGetAutoConvert(REFCLSID clsidOld,LPCLSID pClsidNew);
HRESULT WINAPI IsolationAwareOleSetAutoConvert(REFCLSID clsidOld,REFCLSID clsidNew);
HRESULT WINAPI IsolationAwareGetConvertStg(LPSTORAGE pStg);
HRESULT WINAPI IsolationAwareSetConvertStg(LPSTORAGE pStg,BOOL fConvert);
HRESULT WINAPI IsolationAwareOleConvertIStorageToOLESTREAMEx(LPSTORAGE pstg,CLIPFORMAT cfFormat,long lWidth,long lHeight,DWORD dwSize,LPSTGMEDIUM pmedium,LPOLESTREAM polestm);
HRESULT WINAPI IsolationAwareOleConvertOLESTREAMToIStorageEx(LPOLESTREAM polestm,LPSTORAGE pstg,CLIPFORMAT*pcfFormat,long*plwWidth,long*plHeight,DWORD*pdwSize,LPSTGMEDIUM pmedium);

ISOLATION_AWARE_INLINE HRESULT Ole2IsolationAwarePrivateJVaQPGbueRfhYg(void)
{
    DWORD dwLastError = GetLastError();
    if (dwLastError == NO_ERROR)
        dwLastError = ERROR_INTERNAL_ERROR;
    return HRESULT_FROM_WIN32(dwLastError);
}

#if !ISOLATION_AWARE_USE_STATIC_LIBRARY
ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareReadClassStg(LPSTORAGE pStg,CLSID*pclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = ReadClassStg(pStg,pclsid);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareWriteClassStg(LPSTORAGE pStg,REFCLSID rclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = WriteClassStg(pStg,rclsid);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareReadClassStm(LPSTREAM pStm,CLSID*pclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = ReadClassStm(pStm,pclsid);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareWriteClassStm(LPSTREAM pStm,REFCLSID rclsid)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = WriteClassStm(pStm,rclsid);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareWriteFmtUserTypeStg(LPSTORAGE pstg,CLIPFORMAT cf,LPOLESTR lpszUserType)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = WriteFmtUserTypeStg(pstg,cf,lpszUserType);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareReadFmtUserTypeStg(LPSTORAGE pstg,CLIPFORMAT*pcf,LPOLESTR*lplpszUserType)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = ReadFmtUserTypeStg(pstg,pcf,lplpszUserType);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleInitialize(LPVOID pvReserved)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleInitialize(pvReserved);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleQueryLinkFromData(LPDATAOBJECT pSrcDataObject)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleQueryLinkFromData(pSrcDataObject);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleQueryCreateFromData(LPDATAOBJECT pSrcDataObject)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleQueryCreateFromData(pSrcDataObject);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreate(REFCLSID rclsid,REFIID riid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreate(rclsid,riid,renderopt,pFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateEx(REFCLSID rclsid,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateEx(rclsid,riid,dwFlags,renderopt,cFormats,rgAdvf,rgFormatEtc,lpAdviseSink,rgdwConnection,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateFromData(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateFromData(pSrcDataObj,riid,renderopt,pFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateFromDataEx(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateFromDataEx(pSrcDataObj,riid,dwFlags,renderopt,cFormats,rgAdvf,rgFormatEtc,lpAdviseSink,rgdwConnection,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateLinkFromData(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateLinkFromData(pSrcDataObj,riid,renderopt,pFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateLinkFromDataEx(LPDATAOBJECT pSrcDataObj,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateLinkFromDataEx(pSrcDataObj,riid,dwFlags,renderopt,cFormats,rgAdvf,rgFormatEtc,lpAdviseSink,rgdwConnection,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateStaticFromData(LPDATAOBJECT pSrcDataObj,REFIID iid,DWORD renderopt,LPFORMATETC pFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateStaticFromData(pSrcDataObj,iid,renderopt,pFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateLink(LPMONIKER pmkLinkSrc,REFIID riid,DWORD renderopt,LPFORMATETC lpFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateLink(pmkLinkSrc,riid,renderopt,lpFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateLinkEx(LPMONIKER pmkLinkSrc,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateLinkEx(pmkLinkSrc,riid,dwFlags,renderopt,cFormats,rgAdvf,rgFormatEtc,lpAdviseSink,rgdwConnection,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateLinkToFile(LPCOLESTR lpszFileName,REFIID riid,DWORD renderopt,LPFORMATETC lpFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateLinkToFile(lpszFileName,riid,renderopt,lpFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateLinkToFileEx(LPCOLESTR lpszFileName,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateLinkToFileEx(lpszFileName,riid,dwFlags,renderopt,cFormats,rgAdvf,rgFormatEtc,lpAdviseSink,rgdwConnection,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateFromFile(REFCLSID rclsid,LPCOLESTR lpszFileName,REFIID riid,DWORD renderopt,LPFORMATETC lpFormatEtc,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateFromFile(rclsid,lpszFileName,riid,renderopt,lpFormatEtc,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateFromFileEx(REFCLSID rclsid,LPCOLESTR lpszFileName,REFIID riid,DWORD dwFlags,DWORD renderopt,ULONG cFormats,DWORD*rgAdvf,LPFORMATETC rgFormatEtc,IAdviseSink*lpAdviseSink,DWORD*rgdwConnection,LPOLECLIENTSITE pClientSite,LPSTORAGE pStg,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateFromFileEx(rclsid,lpszFileName,riid,dwFlags,renderopt,cFormats,rgAdvf,rgFormatEtc,lpAdviseSink,rgdwConnection,pClientSite,pStg,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleLoad(LPSTORAGE pStg,REFIID riid,LPOLECLIENTSITE pClientSite,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleLoad(pStg,riid,pClientSite,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleSave(LPPERSISTSTORAGE pPS,LPSTORAGE pStg,BOOL fSameAsLoad)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleSave(pPS,pStg,fSameAsLoad);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleLoadFromStream(LPSTREAM pStm,REFIID iidInterface,LPVOID*ppvObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleLoadFromStream(pStm,iidInterface,ppvObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleSaveToStream(LPPERSISTSTREAM pPStm,LPSTREAM pStm)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleSaveToStream(pPStm,pStm);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleSetContainedObject(LPUNKNOWN pUnknown,BOOL fContained)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleSetContainedObject(pUnknown,fContained);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleNoteObjectVisible(LPUNKNOWN pUnknown,BOOL fVisible)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleNoteObjectVisible(pUnknown,fVisible);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareRegisterDragDrop(HWND hwnd,LPDROPTARGET pDropTarget)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = RegisterDragDrop(hwnd,pDropTarget);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareRevokeDragDrop(HWND hwnd)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = RevokeDragDrop(hwnd);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareDoDragDrop(LPDATAOBJECT pDataObj,LPDROPSOURCE pDropSource,DWORD dwOKEffects,LPDWORD pdwEffect)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = DoDragDrop(pDataObj,pDropSource,dwOKEffects,pdwEffect);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleSetClipboard(LPDATAOBJECT pDataObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleSetClipboard(pDataObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleGetClipboard(LPDATAOBJECT*ppDataObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleGetClipboard(ppDataObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleFlushClipboard(void)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleFlushClipboard();
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleIsCurrentClipboard(LPDATAOBJECT pDataObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleIsCurrentClipboard(pDataObj);
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

ISOLATION_AWARE_INLINE HOLEMENU WINAPI IsolationAwareOleCreateMenuDescriptor(HMENU hmenuCombined,LPOLEMENUGROUPWIDTHS lpMenuWidths)
{
    HOLEMENU result = (SetLastError(NO_ERROR),NULL);
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return result;
    __try
    {
        result = OleCreateMenuDescriptor(hmenuCombined,lpMenuWidths);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (result == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleSetMenuDescriptor(HOLEMENU holemenu,HWND hwndFrame,HWND hwndActiveObject,LPOLEINPLACEFRAME lpFrame,LPOLEINPLACEACTIVEOBJECT lpActiveObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleSetMenuDescriptor(holemenu,hwndFrame,hwndActiveObject,lpFrame,lpActiveObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleDestroyMenuDescriptor(HOLEMENU holemenu)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleDestroyMenuDescriptor(holemenu);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleTranslateAccelerator(LPOLEINPLACEFRAME lpFrame,LPOLEINPLACEFRAMEINFO lpFrameInfo,LPMSG lpmsg)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleTranslateAccelerator(lpFrame,lpFrameInfo,lpmsg);
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

ISOLATION_AWARE_INLINE HANDLE WINAPI IsolationAwareOleDuplicateData(HANDLE hSrc,CLIPFORMAT cfFormat,UINT uiFlags)
{
    HANDLE result = (SetLastError(NO_ERROR),NULL);
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return result;
    __try
    {
        result = OleDuplicateData(hSrc,cfFormat,uiFlags);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (result == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleDraw(LPUNKNOWN pUnknown,DWORD dwAspect,HDC hdcDraw,LPCRECT lprcBounds)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleDraw(pUnknown,dwAspect,hdcDraw,lprcBounds);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleRun(LPUNKNOWN pUnknown)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleRun(pUnknown);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleLockRunning(LPUNKNOWN pUnknown,BOOL fLock,BOOL fLastUnlockCloses)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleLockRunning(pUnknown,fLock,fLastUnlockCloses);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateOleAdviseHolder(LPOLEADVISEHOLDER*ppOAHolder)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateOleAdviseHolder(ppOAHolder);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateDefaultHandler(REFCLSID clsid,LPUNKNOWN pUnkOuter,REFIID riid,LPVOID*lplpObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateDefaultHandler(clsid,pUnkOuter,riid,lplpObj);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleCreateEmbeddingHelper(REFCLSID clsid,LPUNKNOWN pUnkOuter,DWORD flags,LPCLASSFACTORY pCF,REFIID riid,LPVOID*lplpObj)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleCreateEmbeddingHelper(clsid,pUnkOuter,flags,pCF,riid,lplpObj);
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

ISOLATION_AWARE_INLINE HGLOBAL WINAPI IsolationAwareOleGetIconOfFile(LPOLESTR lpszPath,BOOL fUseFileAsLabel)
{
    HGLOBAL result = (SetLastError(NO_ERROR),NULL);
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return result;
    __try
    {
        result = OleGetIconOfFile(lpszPath,fUseFileAsLabel);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (result == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HGLOBAL WINAPI IsolationAwareOleGetIconOfClass(REFCLSID rclsid,LPOLESTR lpszLabel,BOOL fUseTypeAsLabel)
{
    HGLOBAL result = (SetLastError(NO_ERROR),NULL);
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return result;
    __try
    {
        result = OleGetIconOfClass(rclsid,lpszLabel,fUseTypeAsLabel);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (result == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HGLOBAL WINAPI IsolationAwareOleMetafilePictFromIconAndLabel(HICON hIcon,LPOLESTR lpszLabel,LPOLESTR lpszSourceFile,UINT iIconIndex)
{
    HGLOBAL result = (SetLastError(NO_ERROR),NULL);
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return result;
    __try
    {
        result = OleMetafilePictFromIconAndLabel(hIcon,lpszLabel,lpszSourceFile,iIconIndex);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (result == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return result;
}

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleRegGetUserType(REFCLSID clsid,DWORD dwFormOfType,LPOLESTR*pszUserType)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleRegGetUserType(clsid,dwFormOfType,pszUserType);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleRegGetMiscStatus(REFCLSID clsid,DWORD dwAspect,DWORD*pdwStatus)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleRegGetMiscStatus(clsid,dwAspect,pdwStatus);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleRegEnumFormatEtc(REFCLSID clsid,DWORD dwDirection,LPENUMFORMATETC*ppenum)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleRegEnumFormatEtc(clsid,dwDirection,ppenum);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleRegEnumVerbs(REFCLSID clsid,LPENUMOLEVERB*ppenum)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleRegEnumVerbs(clsid,ppenum);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleConvertIStorageToOLESTREAM(LPSTORAGE pstg,LPOLESTREAM lpolestream)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleConvertIStorageToOLESTREAM(pstg,lpolestream);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareGetHGlobalFromILockBytes(LPLOCKBYTES plkbyt,HGLOBAL*phglobal)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = GetHGlobalFromILockBytes(plkbyt,phglobal);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateILockBytesOnHGlobal(HGLOBAL hGlobal,BOOL fDeleteOnRelease,LPLOCKBYTES*pplkbyt)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateILockBytesOnHGlobal(hGlobal,fDeleteOnRelease,pplkbyt);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareGetHGlobalFromStream(LPSTREAM pstm,HGLOBAL*phglobal)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = GetHGlobalFromStream(pstm,phglobal);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareCreateStreamOnHGlobal(HGLOBAL hGlobal,BOOL fDeleteOnRelease,LPSTREAM*ppstm)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = CreateStreamOnHGlobal(hGlobal,fDeleteOnRelease,ppstm);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleDoAutoConvert(LPSTORAGE pStg,LPCLSID pClsidNew)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleDoAutoConvert(pStg,pClsidNew);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleGetAutoConvert(REFCLSID clsidOld,LPCLSID pClsidNew)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleGetAutoConvert(clsidOld,pClsidNew);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleSetAutoConvert(REFCLSID clsidOld,REFCLSID clsidNew)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleSetAutoConvert(clsidOld,clsidNew);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareGetConvertStg(LPSTORAGE pStg)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = GetConvertStg(pStg);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareSetConvertStg(LPSTORAGE pStg,BOOL fConvert)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = SetConvertStg(pStg,fConvert);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleConvertIStorageToOLESTREAMEx(LPSTORAGE pstg,CLIPFORMAT cfFormat,long lWidth,long lHeight,DWORD dwSize,LPSTGMEDIUM pmedium,LPOLESTREAM polestm)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleConvertIStorageToOLESTREAMEx(pstg,cfFormat,lWidth,lHeight,dwSize,pmedium,polestm);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwareOleConvertOLESTREAMToIStorageEx(LPOLESTREAM polestm,LPSTORAGE pstg,CLIPFORMAT*pcfFormat,long*plwWidth,long*plHeight,DWORD*pdwSize,LPSTGMEDIUM pmedium)
{
    HRESULT result = S_OK;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return Ole2IsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        result = OleConvertOLESTREAMToIStorageEx(polestm,pstg,pcfFormat,plwWidth,plHeight,pdwSize,pmedium);
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

#define CreateILockBytesOnHGlobal IsolationAwareCreateILockBytesOnHGlobal
#define CreateOleAdviseHolder IsolationAwareCreateOleAdviseHolder
#define CreateStreamOnHGlobal IsolationAwareCreateStreamOnHGlobal
#define DoDragDrop IsolationAwareDoDragDrop
#define GetConvertStg IsolationAwareGetConvertStg
#define GetHGlobalFromILockBytes IsolationAwareGetHGlobalFromILockBytes
#define GetHGlobalFromStream IsolationAwareGetHGlobalFromStream
#define OleConvertIStorageToOLESTREAM IsolationAwareOleConvertIStorageToOLESTREAM
#define OleConvertIStorageToOLESTREAMEx IsolationAwareOleConvertIStorageToOLESTREAMEx
#define OleConvertOLESTREAMToIStorageEx IsolationAwareOleConvertOLESTREAMToIStorageEx
#define OleCreate IsolationAwareOleCreate
#define OleCreateDefaultHandler IsolationAwareOleCreateDefaultHandler
#define OleCreateEmbeddingHelper IsolationAwareOleCreateEmbeddingHelper
#define OleCreateEx IsolationAwareOleCreateEx
#define OleCreateFromData IsolationAwareOleCreateFromData
#define OleCreateFromDataEx IsolationAwareOleCreateFromDataEx
#define OleCreateFromFile IsolationAwareOleCreateFromFile
#define OleCreateFromFileEx IsolationAwareOleCreateFromFileEx
#define OleCreateLink IsolationAwareOleCreateLink
#define OleCreateLinkEx IsolationAwareOleCreateLinkEx
#define OleCreateLinkFromData IsolationAwareOleCreateLinkFromData
#define OleCreateLinkFromDataEx IsolationAwareOleCreateLinkFromDataEx
#define OleCreateLinkToFile IsolationAwareOleCreateLinkToFile
#define OleCreateLinkToFileEx IsolationAwareOleCreateLinkToFileEx
#define OleCreateMenuDescriptor IsolationAwareOleCreateMenuDescriptor
#define OleCreateStaticFromData IsolationAwareOleCreateStaticFromData
#define OleDestroyMenuDescriptor IsolationAwareOleDestroyMenuDescriptor
#define OleDoAutoConvert IsolationAwareOleDoAutoConvert
#define OleDraw IsolationAwareOleDraw
#define OleDuplicateData IsolationAwareOleDuplicateData
#define OleFlushClipboard IsolationAwareOleFlushClipboard
#define OleGetAutoConvert IsolationAwareOleGetAutoConvert
#define OleGetClipboard IsolationAwareOleGetClipboard
#define OleGetIconOfClass IsolationAwareOleGetIconOfClass
#define OleGetIconOfFile IsolationAwareOleGetIconOfFile
#define OleInitialize IsolationAwareOleInitialize
#define OleIsCurrentClipboard IsolationAwareOleIsCurrentClipboard
#define OleLoad IsolationAwareOleLoad
#define OleLoadFromStream IsolationAwareOleLoadFromStream
#define OleLockRunning IsolationAwareOleLockRunning
#define OleMetafilePictFromIconAndLabel IsolationAwareOleMetafilePictFromIconAndLabel
#define OleNoteObjectVisible IsolationAwareOleNoteObjectVisible
#define OleQueryCreateFromData IsolationAwareOleQueryCreateFromData
#define OleQueryLinkFromData IsolationAwareOleQueryLinkFromData
#define OleRegEnumFormatEtc IsolationAwareOleRegEnumFormatEtc
#define OleRegEnumVerbs IsolationAwareOleRegEnumVerbs
#define OleRegGetMiscStatus IsolationAwareOleRegGetMiscStatus
#define OleRegGetUserType IsolationAwareOleRegGetUserType
#define OleRun IsolationAwareOleRun
#define OleSave IsolationAwareOleSave
#define OleSaveToStream IsolationAwareOleSaveToStream
#define OleSetAutoConvert IsolationAwareOleSetAutoConvert
#define OleSetClipboard IsolationAwareOleSetClipboard
#define OleSetContainedObject IsolationAwareOleSetContainedObject
#define OleSetMenuDescriptor IsolationAwareOleSetMenuDescriptor
#define OleTranslateAccelerator IsolationAwareOleTranslateAccelerator
#define ReadClassStg IsolationAwareReadClassStg
#define ReadClassStm IsolationAwareReadClassStm
#define ReadFmtUserTypeStg IsolationAwareReadFmtUserTypeStg
#define RegisterDragDrop IsolationAwareRegisterDragDrop
#define RevokeDragDrop IsolationAwareRevokeDragDrop
#define SetConvertStg IsolationAwareSetConvertStg
#define WriteClassStg IsolationAwareWriteClassStg
#define WriteClassStm IsolationAwareWriteClassStm
#define WriteFmtUserTypeStg IsolationAwareWriteFmtUserTypeStg

#endif /* ISOLATION_AWARE_ENABLED */
#endif /* RC */


#if defined(__cplusplus)
} /* __cplusplus */
#endif



#endif     // __OLE2_H__
