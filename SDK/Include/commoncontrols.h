

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0408 */
/* Compiler settings for commoncontrols.idl:
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

#ifndef __commoncontrols_h__
#define __commoncontrols_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IImageList_FWD_DEFINED__
#define __IImageList_FWD_DEFINED__
typedef interface IImageList IImageList;
#endif 	/* __IImageList_FWD_DEFINED__ */


#ifndef __IImageList2_FWD_DEFINED__
#define __IImageList2_FWD_DEFINED__
typedef interface IImageList2 IImageList2;
#endif 	/* __IImageList2_FWD_DEFINED__ */


#ifndef __IImageListSparseCallback_FWD_DEFINED__
#define __IImageListSparseCallback_FWD_DEFINED__
typedef interface IImageListSparseCallback IImageListSparseCallback;
#endif 	/* __IImageListSparseCallback_FWD_DEFINED__ */


#ifndef __IImageListContainer_FWD_DEFINED__
#define __IImageListContainer_FWD_DEFINED__
typedef interface IImageListContainer IImageListContainer;
#endif 	/* __IImageListContainer_FWD_DEFINED__ */


#ifndef __IAggregateImageList_FWD_DEFINED__
#define __IAggregateImageList_FWD_DEFINED__
typedef interface IAggregateImageList IAggregateImageList;
#endif 	/* __IAggregateImageList_FWD_DEFINED__ */


#ifndef __IGangImageList_FWD_DEFINED__
#define __IGangImageList_FWD_DEFINED__
typedef interface IGangImageList IGangImageList;
#endif 	/* __IGangImageList_FWD_DEFINED__ */


#ifndef __ImageList_FWD_DEFINED__
#define __ImageList_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageList ImageList;
#else
typedef struct ImageList ImageList;
#endif /* __cplusplus */

#endif 	/* __ImageList_FWD_DEFINED__ */


#ifndef __SparseImageList_FWD_DEFINED__
#define __SparseImageList_FWD_DEFINED__

#ifdef __cplusplus
typedef class SparseImageList SparseImageList;
#else
typedef struct SparseImageList SparseImageList;
#endif /* __cplusplus */

#endif 	/* __SparseImageList_FWD_DEFINED__ */


#ifndef __AggregateImageList_FWD_DEFINED__
#define __AggregateImageList_FWD_DEFINED__

#ifdef __cplusplus
typedef class AggregateImageList AggregateImageList;
#else
typedef struct AggregateImageList AggregateImageList;
#endif /* __cplusplus */

#endif 	/* __AggregateImageList_FWD_DEFINED__ */


#ifndef __GangImageList_FWD_DEFINED__
#define __GangImageList_FWD_DEFINED__

#ifdef __cplusplus
typedef class GangImageList GangImageList;
#else
typedef struct GangImageList GangImageList;
#endif /* __cplusplus */

#endif 	/* __GangImageList_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_commoncontrols_0000 */
/* [local] */ 

#if (_WIN32_IE >= 0x0501)
#ifndef WINCOMMCTRLAPI
#if !defined(_COMCTL32_) && defined(_WIN32)
#define WINCOMMCTRLAPI DECLSPEC_IMPORT
#else
#define WINCOMMCTRLAPI
#endif
#endif // WINCOMMCTRLAPI
#ifdef MIDL_PASS
typedef DWORD RGBQUAD;

typedef IUnknown *HIMAGELIST;

typedef struct _IMAGELIST* HIMAGELIST;
typedef struct _IMAGELISTDRAWPARAMS
    {
    DWORD cbSize;
    HIMAGELIST himl;
    int i;
    HDC hdcDst;
    int x;
    int y;
    int cx;
    int cy;
    int xBitmap;
    int yBitmap;
    COLORREF rgbBk;
    COLORREF rgbFg;
    UINT fStyle;
    DWORD dwRop;
    DWORD fState;
    DWORD Frame;
    COLORREF crEffect;
    } 	IMAGELISTDRAWPARAMS;

typedef IMAGELISTDRAWPARAMS *LPIMAGELISTDRAWPARAMS;

typedef struct tagIMAGEINFO
    {
    HBITMAP hbmImage;
    HBITMAP hbmMask;
    int Unused1;
    int Unused2;
    RECT rcImage;
    } 	IMAGEINFO;

typedef IMAGEINFO *LPIMAGEINFO;

#endif
#if (_WIN32_WINNT >= 0x0600)
WINCOMMCTRLAPI HRESULT WINAPI ImageList_CoCreateInstance(
        /* __in */ REFCLSID rclsid,
        /* __in */ const IUnknown *punkOuter,
        /* __in */ REFIID riid,
       /* __out */ void **ppv);
#endif
#define ILIF_ALPHA               0x00000001
#define ILIF_LOWQUALITY          0x00000002
#define ILDRF_IMAGELOWQUALITY    0x00000001
#define ILDRF_OVERLAYLOWQUALITY  0x00000010


extern RPC_IF_HANDLE __MIDL_itf_commoncontrols_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_commoncontrols_0000_v0_0_s_ifspec;

#ifndef __IImageList_INTERFACE_DEFINED__
#define __IImageList_INTERFACE_DEFINED__

/* interface IImageList */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IImageList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("46EB5926-582E-4017-9FDF-E8998DAA0950")
    IImageList : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Add( 
            HBITMAP hbmImage,
            HBITMAP hbmMask,
            int *pi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceIcon( 
            int i,
            HICON hicon,
            int *pi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOverlayImage( 
            int iImage,
            int iOverlay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Replace( 
            int i,
            HBITMAP hbmImage,
            HBITMAP hbmMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMasked( 
            HBITMAP hbmImage,
            COLORREF crMask,
            int *pi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            IMAGELISTDRAWPARAMS *pimldp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Remove( 
            int i) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIcon( 
            int i,
            UINT flags,
            HICON *picon) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageInfo( 
            int i,
            IMAGEINFO *pImageInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Copy( 
            int iDst,
            IUnknown *punkSrc,
            int iSrc,
            UINT uFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Merge( 
            int i1,
            IUnknown *punk2,
            int i2,
            int dx,
            int dy,
            REFIID riid,
            PVOID *ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            REFIID riid,
            PVOID *ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageRect( 
            int i,
            RECT *prc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIconSize( 
            int *cx,
            int *cy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIconSize( 
            int cx,
            int cy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageCount( 
            int *pi) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetImageCount( 
            UINT uNewCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBkColor( 
            COLORREF clrBk,
            COLORREF *pclr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBkColor( 
            COLORREF *pclr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginDrag( 
            int iTrack,
            int dxHotspot,
            int dyHotspot) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndDrag( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragEnter( 
            HWND hwndLock,
            int x,
            int y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragLeave( 
            HWND hwndLock) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragMove( 
            int x,
            int y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDragCursorImage( 
            IUnknown *punk,
            int iDrag,
            int dxHotspot,
            int dyHotspot) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragShowNolock( 
            BOOL fShow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDragImage( 
            POINT *ppt,
            POINT *pptHotspot,
            REFIID riid,
            PVOID *ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemFlags( 
            int i,
            DWORD *dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOverlayImage( 
            int iOverlay,
            int *piIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImageList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImageList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImageList * This);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            IImageList * This,
            HBITMAP hbmImage,
            HBITMAP hbmMask,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceIcon )( 
            IImageList * This,
            int i,
            HICON hicon,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *SetOverlayImage )( 
            IImageList * This,
            int iImage,
            int iOverlay);
        
        HRESULT ( STDMETHODCALLTYPE *Replace )( 
            IImageList * This,
            int i,
            HBITMAP hbmImage,
            HBITMAP hbmMask);
        
        HRESULT ( STDMETHODCALLTYPE *AddMasked )( 
            IImageList * This,
            HBITMAP hbmImage,
            COLORREF crMask,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IImageList * This,
            IMAGELISTDRAWPARAMS *pimldp);
        
        HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IImageList * This,
            int i);
        
        HRESULT ( STDMETHODCALLTYPE *GetIcon )( 
            IImageList * This,
            int i,
            UINT flags,
            HICON *picon);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageInfo )( 
            IImageList * This,
            int i,
            IMAGEINFO *pImageInfo);
        
        HRESULT ( STDMETHODCALLTYPE *Copy )( 
            IImageList * This,
            int iDst,
            IUnknown *punkSrc,
            int iSrc,
            UINT uFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Merge )( 
            IImageList * This,
            int i1,
            IUnknown *punk2,
            int i2,
            int dx,
            int dy,
            REFIID riid,
            PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IImageList * This,
            REFIID riid,
            PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageRect )( 
            IImageList * This,
            int i,
            RECT *prc);
        
        HRESULT ( STDMETHODCALLTYPE *GetIconSize )( 
            IImageList * This,
            int *cx,
            int *cy);
        
        HRESULT ( STDMETHODCALLTYPE *SetIconSize )( 
            IImageList * This,
            int cx,
            int cy);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageCount )( 
            IImageList * This,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageCount )( 
            IImageList * This,
            UINT uNewCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetBkColor )( 
            IImageList * This,
            COLORREF clrBk,
            COLORREF *pclr);
        
        HRESULT ( STDMETHODCALLTYPE *GetBkColor )( 
            IImageList * This,
            COLORREF *pclr);
        
        HRESULT ( STDMETHODCALLTYPE *BeginDrag )( 
            IImageList * This,
            int iTrack,
            int dxHotspot,
            int dyHotspot);
        
        HRESULT ( STDMETHODCALLTYPE *EndDrag )( 
            IImageList * This);
        
        HRESULT ( STDMETHODCALLTYPE *DragEnter )( 
            IImageList * This,
            HWND hwndLock,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE *DragLeave )( 
            IImageList * This,
            HWND hwndLock);
        
        HRESULT ( STDMETHODCALLTYPE *DragMove )( 
            IImageList * This,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE *SetDragCursorImage )( 
            IImageList * This,
            IUnknown *punk,
            int iDrag,
            int dxHotspot,
            int dyHotspot);
        
        HRESULT ( STDMETHODCALLTYPE *DragShowNolock )( 
            IImageList * This,
            BOOL fShow);
        
        HRESULT ( STDMETHODCALLTYPE *GetDragImage )( 
            IImageList * This,
            POINT *ppt,
            POINT *pptHotspot,
            REFIID riid,
            PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemFlags )( 
            IImageList * This,
            int i,
            DWORD *dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetOverlayImage )( 
            IImageList * This,
            int iOverlay,
            int *piIndex);
        
        END_INTERFACE
    } IImageListVtbl;

    interface IImageList
    {
        CONST_VTBL struct IImageListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImageList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImageList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImageList_Add(This,hbmImage,hbmMask,pi)	\
    ( (This)->lpVtbl -> Add(This,hbmImage,hbmMask,pi) ) 

#define IImageList_ReplaceIcon(This,i,hicon,pi)	\
    ( (This)->lpVtbl -> ReplaceIcon(This,i,hicon,pi) ) 

#define IImageList_SetOverlayImage(This,iImage,iOverlay)	\
    ( (This)->lpVtbl -> SetOverlayImage(This,iImage,iOverlay) ) 

#define IImageList_Replace(This,i,hbmImage,hbmMask)	\
    ( (This)->lpVtbl -> Replace(This,i,hbmImage,hbmMask) ) 

#define IImageList_AddMasked(This,hbmImage,crMask,pi)	\
    ( (This)->lpVtbl -> AddMasked(This,hbmImage,crMask,pi) ) 

#define IImageList_Draw(This,pimldp)	\
    ( (This)->lpVtbl -> Draw(This,pimldp) ) 

#define IImageList_Remove(This,i)	\
    ( (This)->lpVtbl -> Remove(This,i) ) 

#define IImageList_GetIcon(This,i,flags,picon)	\
    ( (This)->lpVtbl -> GetIcon(This,i,flags,picon) ) 

#define IImageList_GetImageInfo(This,i,pImageInfo)	\
    ( (This)->lpVtbl -> GetImageInfo(This,i,pImageInfo) ) 

#define IImageList_Copy(This,iDst,punkSrc,iSrc,uFlags)	\
    ( (This)->lpVtbl -> Copy(This,iDst,punkSrc,iSrc,uFlags) ) 

#define IImageList_Merge(This,i1,punk2,i2,dx,dy,riid,ppv)	\
    ( (This)->lpVtbl -> Merge(This,i1,punk2,i2,dx,dy,riid,ppv) ) 

#define IImageList_Clone(This,riid,ppv)	\
    ( (This)->lpVtbl -> Clone(This,riid,ppv) ) 

#define IImageList_GetImageRect(This,i,prc)	\
    ( (This)->lpVtbl -> GetImageRect(This,i,prc) ) 

#define IImageList_GetIconSize(This,cx,cy)	\
    ( (This)->lpVtbl -> GetIconSize(This,cx,cy) ) 

#define IImageList_SetIconSize(This,cx,cy)	\
    ( (This)->lpVtbl -> SetIconSize(This,cx,cy) ) 

#define IImageList_GetImageCount(This,pi)	\
    ( (This)->lpVtbl -> GetImageCount(This,pi) ) 

#define IImageList_SetImageCount(This,uNewCount)	\
    ( (This)->lpVtbl -> SetImageCount(This,uNewCount) ) 

#define IImageList_SetBkColor(This,clrBk,pclr)	\
    ( (This)->lpVtbl -> SetBkColor(This,clrBk,pclr) ) 

#define IImageList_GetBkColor(This,pclr)	\
    ( (This)->lpVtbl -> GetBkColor(This,pclr) ) 

#define IImageList_BeginDrag(This,iTrack,dxHotspot,dyHotspot)	\
    ( (This)->lpVtbl -> BeginDrag(This,iTrack,dxHotspot,dyHotspot) ) 

#define IImageList_EndDrag(This)	\
    ( (This)->lpVtbl -> EndDrag(This) ) 

#define IImageList_DragEnter(This,hwndLock,x,y)	\
    ( (This)->lpVtbl -> DragEnter(This,hwndLock,x,y) ) 

#define IImageList_DragLeave(This,hwndLock)	\
    ( (This)->lpVtbl -> DragLeave(This,hwndLock) ) 

#define IImageList_DragMove(This,x,y)	\
    ( (This)->lpVtbl -> DragMove(This,x,y) ) 

#define IImageList_SetDragCursorImage(This,punk,iDrag,dxHotspot,dyHotspot)	\
    ( (This)->lpVtbl -> SetDragCursorImage(This,punk,iDrag,dxHotspot,dyHotspot) ) 

#define IImageList_DragShowNolock(This,fShow)	\
    ( (This)->lpVtbl -> DragShowNolock(This,fShow) ) 

#define IImageList_GetDragImage(This,ppt,pptHotspot,riid,ppv)	\
    ( (This)->lpVtbl -> GetDragImage(This,ppt,pptHotspot,riid,ppv) ) 

#define IImageList_GetItemFlags(This,i,dwFlags)	\
    ( (This)->lpVtbl -> GetItemFlags(This,i,dwFlags) ) 

#define IImageList_GetOverlayImage(This,iOverlay,piIndex)	\
    ( (This)->lpVtbl -> GetOverlayImage(This,iOverlay,piIndex) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageList_Add_Proxy( 
    IImageList * This,
    HBITMAP hbmImage,
    HBITMAP hbmMask,
    int *pi);


void __RPC_STUB IImageList_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_ReplaceIcon_Proxy( 
    IImageList * This,
    int i,
    HICON hicon,
    int *pi);


void __RPC_STUB IImageList_ReplaceIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_SetOverlayImage_Proxy( 
    IImageList * This,
    int iImage,
    int iOverlay);


void __RPC_STUB IImageList_SetOverlayImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_Replace_Proxy( 
    IImageList * This,
    int i,
    HBITMAP hbmImage,
    HBITMAP hbmMask);


void __RPC_STUB IImageList_Replace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_AddMasked_Proxy( 
    IImageList * This,
    HBITMAP hbmImage,
    COLORREF crMask,
    int *pi);


void __RPC_STUB IImageList_AddMasked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_Draw_Proxy( 
    IImageList * This,
    IMAGELISTDRAWPARAMS *pimldp);


void __RPC_STUB IImageList_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_Remove_Proxy( 
    IImageList * This,
    int i);


void __RPC_STUB IImageList_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetIcon_Proxy( 
    IImageList * This,
    int i,
    UINT flags,
    HICON *picon);


void __RPC_STUB IImageList_GetIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetImageInfo_Proxy( 
    IImageList * This,
    int i,
    IMAGEINFO *pImageInfo);


void __RPC_STUB IImageList_GetImageInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_Copy_Proxy( 
    IImageList * This,
    int iDst,
    IUnknown *punkSrc,
    int iSrc,
    UINT uFlags);


void __RPC_STUB IImageList_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_Merge_Proxy( 
    IImageList * This,
    int i1,
    IUnknown *punk2,
    int i2,
    int dx,
    int dy,
    REFIID riid,
    PVOID *ppv);


void __RPC_STUB IImageList_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_Clone_Proxy( 
    IImageList * This,
    REFIID riid,
    PVOID *ppv);


void __RPC_STUB IImageList_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetImageRect_Proxy( 
    IImageList * This,
    int i,
    RECT *prc);


void __RPC_STUB IImageList_GetImageRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetIconSize_Proxy( 
    IImageList * This,
    int *cx,
    int *cy);


void __RPC_STUB IImageList_GetIconSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_SetIconSize_Proxy( 
    IImageList * This,
    int cx,
    int cy);


void __RPC_STUB IImageList_SetIconSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetImageCount_Proxy( 
    IImageList * This,
    int *pi);


void __RPC_STUB IImageList_GetImageCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_SetImageCount_Proxy( 
    IImageList * This,
    UINT uNewCount);


void __RPC_STUB IImageList_SetImageCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_SetBkColor_Proxy( 
    IImageList * This,
    COLORREF clrBk,
    COLORREF *pclr);


void __RPC_STUB IImageList_SetBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetBkColor_Proxy( 
    IImageList * This,
    COLORREF *pclr);


void __RPC_STUB IImageList_GetBkColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_BeginDrag_Proxy( 
    IImageList * This,
    int iTrack,
    int dxHotspot,
    int dyHotspot);


void __RPC_STUB IImageList_BeginDrag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_EndDrag_Proxy( 
    IImageList * This);


void __RPC_STUB IImageList_EndDrag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_DragEnter_Proxy( 
    IImageList * This,
    HWND hwndLock,
    int x,
    int y);


void __RPC_STUB IImageList_DragEnter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_DragLeave_Proxy( 
    IImageList * This,
    HWND hwndLock);


void __RPC_STUB IImageList_DragLeave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_DragMove_Proxy( 
    IImageList * This,
    int x,
    int y);


void __RPC_STUB IImageList_DragMove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_SetDragCursorImage_Proxy( 
    IImageList * This,
    IUnknown *punk,
    int iDrag,
    int dxHotspot,
    int dyHotspot);


void __RPC_STUB IImageList_SetDragCursorImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_DragShowNolock_Proxy( 
    IImageList * This,
    BOOL fShow);


void __RPC_STUB IImageList_DragShowNolock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetDragImage_Proxy( 
    IImageList * This,
    POINT *ppt,
    POINT *pptHotspot,
    REFIID riid,
    PVOID *ppv);


void __RPC_STUB IImageList_GetDragImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetItemFlags_Proxy( 
    IImageList * This,
    int i,
    DWORD *dwFlags);


void __RPC_STUB IImageList_GetItemFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList_GetOverlayImage_Proxy( 
    IImageList * This,
    int iOverlay,
    int *piIndex);


void __RPC_STUB IImageList_GetOverlayImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageList_INTERFACE_DEFINED__ */


#ifndef __IImageList2_INTERFACE_DEFINED__
#define __IImageList2_INTERFACE_DEFINED__

/* interface IImageList2 */
/* [object][local][helpstring][uuid] */ 

#define ILDI_PURGE       0x00000001
#define ILDI_STANDBY     0x00000002
#define ILDI_RESETACCESS 0x00000004
#define ILDI_QUERYACCESS 0x00000008
#define ILFIP_ALWAYS         0x00000000
#define ILFIP_FROMSTANDBY    0x00000001
typedef struct tagIMAGELISTSTATS
    {
    DWORD cbSize;
    int cAlloc;
    int cUsed;
    int cStandby;
    } 	IMAGELISTSTATS;


EXTERN_C const IID IID_IImageList2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a6a78d63-aad3-46a0-ba39-163be3a9050c")
    IImageList2 : public IImageList
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Resize( 
            int cxNewIconSize,
            int cyNewIconSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDevice( 
            /* [in] */ IUnknown *punk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTextureInformation( 
            /* [out] */ UINT *piCount,
            /* [out] */ UINT *piRows,
            /* [out] */ UINT *piCols) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageTextureInfo( 
            /* [in] */ DWORD fStyle,
            /* [in] */ int iImage,
            /* [out] */ UINT *piTexture,
            /* [out] */ RECT *prcImage,
            /* [out] */ IUnknown **ppTexture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectTexture( 
            /* [in] */ UINT iTexture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOriginalSize( 
            /* [in] */ int iImage,
            /* [out] */ int *pcx,
            /* [out] */ int *pcy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOriginalSize( 
            /* [in] */ int iImage,
            /* [in] */ int cx,
            /* [in] */ int cy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCallback( 
            /* [in] */ IUnknown *punk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCallback( 
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ PVOID *ppv) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ForceImagePresent( 
            /* [in] */ int iImage,
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DiscardImages( 
            /* [in] */ int iFirstImage,
            /* [in] */ int iLastImage,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreloadImages( 
            /* [in] */ IMAGELISTDRAWPARAMS *pimldp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStatistics( 
            /* [out][in] */ IMAGELISTSTATS *pils) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ int cx,
            /* [in] */ int cy,
            /* [in] */ UINT flags,
            /* [in] */ int cInitial,
            /* [in] */ int cGrow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMILBrushInformation( 
            /* [out] */ UINT *piCount,
            /* [out] */ UINT *piRows,
            /* [out] */ UINT *piCols) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageMILBrushInfo( 
            /* [in] */ DWORD fStyle,
            /* [in] */ int iImage,
            /* [out] */ UINT *piMILBrush,
            /* [out] */ RECT *prcImage,
            /* [out] */ IUnknown **ppMILBrush) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMILBrush( 
            /* [in] */ UINT iMILBrush,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ PVOID *ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageList2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImageList2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImageList2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImageList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            IImageList2 * This,
            HBITMAP hbmImage,
            HBITMAP hbmMask,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceIcon )( 
            IImageList2 * This,
            int i,
            HICON hicon,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *SetOverlayImage )( 
            IImageList2 * This,
            int iImage,
            int iOverlay);
        
        HRESULT ( STDMETHODCALLTYPE *Replace )( 
            IImageList2 * This,
            int i,
            HBITMAP hbmImage,
            HBITMAP hbmMask);
        
        HRESULT ( STDMETHODCALLTYPE *AddMasked )( 
            IImageList2 * This,
            HBITMAP hbmImage,
            COLORREF crMask,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *Draw )( 
            IImageList2 * This,
            IMAGELISTDRAWPARAMS *pimldp);
        
        HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IImageList2 * This,
            int i);
        
        HRESULT ( STDMETHODCALLTYPE *GetIcon )( 
            IImageList2 * This,
            int i,
            UINT flags,
            HICON *picon);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageInfo )( 
            IImageList2 * This,
            int i,
            IMAGEINFO *pImageInfo);
        
        HRESULT ( STDMETHODCALLTYPE *Copy )( 
            IImageList2 * This,
            int iDst,
            IUnknown *punkSrc,
            int iSrc,
            UINT uFlags);
        
        HRESULT ( STDMETHODCALLTYPE *Merge )( 
            IImageList2 * This,
            int i1,
            IUnknown *punk2,
            int i2,
            int dx,
            int dy,
            REFIID riid,
            PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IImageList2 * This,
            REFIID riid,
            PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageRect )( 
            IImageList2 * This,
            int i,
            RECT *prc);
        
        HRESULT ( STDMETHODCALLTYPE *GetIconSize )( 
            IImageList2 * This,
            int *cx,
            int *cy);
        
        HRESULT ( STDMETHODCALLTYPE *SetIconSize )( 
            IImageList2 * This,
            int cx,
            int cy);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageCount )( 
            IImageList2 * This,
            int *pi);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageCount )( 
            IImageList2 * This,
            UINT uNewCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetBkColor )( 
            IImageList2 * This,
            COLORREF clrBk,
            COLORREF *pclr);
        
        HRESULT ( STDMETHODCALLTYPE *GetBkColor )( 
            IImageList2 * This,
            COLORREF *pclr);
        
        HRESULT ( STDMETHODCALLTYPE *BeginDrag )( 
            IImageList2 * This,
            int iTrack,
            int dxHotspot,
            int dyHotspot);
        
        HRESULT ( STDMETHODCALLTYPE *EndDrag )( 
            IImageList2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *DragEnter )( 
            IImageList2 * This,
            HWND hwndLock,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE *DragLeave )( 
            IImageList2 * This,
            HWND hwndLock);
        
        HRESULT ( STDMETHODCALLTYPE *DragMove )( 
            IImageList2 * This,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE *SetDragCursorImage )( 
            IImageList2 * This,
            IUnknown *punk,
            int iDrag,
            int dxHotspot,
            int dyHotspot);
        
        HRESULT ( STDMETHODCALLTYPE *DragShowNolock )( 
            IImageList2 * This,
            BOOL fShow);
        
        HRESULT ( STDMETHODCALLTYPE *GetDragImage )( 
            IImageList2 * This,
            POINT *ppt,
            POINT *pptHotspot,
            REFIID riid,
            PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *GetItemFlags )( 
            IImageList2 * This,
            int i,
            DWORD *dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetOverlayImage )( 
            IImageList2 * This,
            int iOverlay,
            int *piIndex);
        
        HRESULT ( STDMETHODCALLTYPE *Resize )( 
            IImageList2 * This,
            int cxNewIconSize,
            int cyNewIconSize);
        
        HRESULT ( STDMETHODCALLTYPE *SetDevice )( 
            IImageList2 * This,
            /* [in] */ IUnknown *punk);
        
        HRESULT ( STDMETHODCALLTYPE *GetTextureInformation )( 
            IImageList2 * This,
            /* [out] */ UINT *piCount,
            /* [out] */ UINT *piRows,
            /* [out] */ UINT *piCols);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageTextureInfo )( 
            IImageList2 * This,
            /* [in] */ DWORD fStyle,
            /* [in] */ int iImage,
            /* [out] */ UINT *piTexture,
            /* [out] */ RECT *prcImage,
            /* [out] */ IUnknown **ppTexture);
        
        HRESULT ( STDMETHODCALLTYPE *SelectTexture )( 
            IImageList2 * This,
            /* [in] */ UINT iTexture);
        
        HRESULT ( STDMETHODCALLTYPE *GetOriginalSize )( 
            IImageList2 * This,
            /* [in] */ int iImage,
            /* [out] */ int *pcx,
            /* [out] */ int *pcy);
        
        HRESULT ( STDMETHODCALLTYPE *SetOriginalSize )( 
            IImageList2 * This,
            /* [in] */ int iImage,
            /* [in] */ int cx,
            /* [in] */ int cy);
        
        HRESULT ( STDMETHODCALLTYPE *SetCallback )( 
            IImageList2 * This,
            /* [in] */ IUnknown *punk);
        
        HRESULT ( STDMETHODCALLTYPE *GetCallback )( 
            IImageList2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ PVOID *ppv);
        
        HRESULT ( STDMETHODCALLTYPE *ForceImagePresent )( 
            IImageList2 * This,
            /* [in] */ int iImage,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *DiscardImages )( 
            IImageList2 * This,
            /* [in] */ int iFirstImage,
            /* [in] */ int iLastImage,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *PreloadImages )( 
            IImageList2 * This,
            /* [in] */ IMAGELISTDRAWPARAMS *pimldp);
        
        HRESULT ( STDMETHODCALLTYPE *GetStatistics )( 
            IImageList2 * This,
            /* [out][in] */ IMAGELISTSTATS *pils);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IImageList2 * This,
            /* [in] */ int cx,
            /* [in] */ int cy,
            /* [in] */ UINT flags,
            /* [in] */ int cInitial,
            /* [in] */ int cGrow);
        
        HRESULT ( STDMETHODCALLTYPE *GetMILBrushInformation )( 
            IImageList2 * This,
            /* [out] */ UINT *piCount,
            /* [out] */ UINT *piRows,
            /* [out] */ UINT *piCols);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageMILBrushInfo )( 
            IImageList2 * This,
            /* [in] */ DWORD fStyle,
            /* [in] */ int iImage,
            /* [out] */ UINT *piMILBrush,
            /* [out] */ RECT *prcImage,
            /* [out] */ IUnknown **ppMILBrush);
        
        HRESULT ( STDMETHODCALLTYPE *GetMILBrush )( 
            IImageList2 * This,
            /* [in] */ UINT iMILBrush,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ PVOID *ppv);
        
        END_INTERFACE
    } IImageList2Vtbl;

    interface IImageList2
    {
        CONST_VTBL struct IImageList2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageList2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImageList2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImageList2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImageList2_Add(This,hbmImage,hbmMask,pi)	\
    ( (This)->lpVtbl -> Add(This,hbmImage,hbmMask,pi) ) 

#define IImageList2_ReplaceIcon(This,i,hicon,pi)	\
    ( (This)->lpVtbl -> ReplaceIcon(This,i,hicon,pi) ) 

#define IImageList2_SetOverlayImage(This,iImage,iOverlay)	\
    ( (This)->lpVtbl -> SetOverlayImage(This,iImage,iOverlay) ) 

#define IImageList2_Replace(This,i,hbmImage,hbmMask)	\
    ( (This)->lpVtbl -> Replace(This,i,hbmImage,hbmMask) ) 

#define IImageList2_AddMasked(This,hbmImage,crMask,pi)	\
    ( (This)->lpVtbl -> AddMasked(This,hbmImage,crMask,pi) ) 

#define IImageList2_Draw(This,pimldp)	\
    ( (This)->lpVtbl -> Draw(This,pimldp) ) 

#define IImageList2_Remove(This,i)	\
    ( (This)->lpVtbl -> Remove(This,i) ) 

#define IImageList2_GetIcon(This,i,flags,picon)	\
    ( (This)->lpVtbl -> GetIcon(This,i,flags,picon) ) 

#define IImageList2_GetImageInfo(This,i,pImageInfo)	\
    ( (This)->lpVtbl -> GetImageInfo(This,i,pImageInfo) ) 

#define IImageList2_Copy(This,iDst,punkSrc,iSrc,uFlags)	\
    ( (This)->lpVtbl -> Copy(This,iDst,punkSrc,iSrc,uFlags) ) 

#define IImageList2_Merge(This,i1,punk2,i2,dx,dy,riid,ppv)	\
    ( (This)->lpVtbl -> Merge(This,i1,punk2,i2,dx,dy,riid,ppv) ) 

#define IImageList2_Clone(This,riid,ppv)	\
    ( (This)->lpVtbl -> Clone(This,riid,ppv) ) 

#define IImageList2_GetImageRect(This,i,prc)	\
    ( (This)->lpVtbl -> GetImageRect(This,i,prc) ) 

#define IImageList2_GetIconSize(This,cx,cy)	\
    ( (This)->lpVtbl -> GetIconSize(This,cx,cy) ) 

#define IImageList2_SetIconSize(This,cx,cy)	\
    ( (This)->lpVtbl -> SetIconSize(This,cx,cy) ) 

#define IImageList2_GetImageCount(This,pi)	\
    ( (This)->lpVtbl -> GetImageCount(This,pi) ) 

#define IImageList2_SetImageCount(This,uNewCount)	\
    ( (This)->lpVtbl -> SetImageCount(This,uNewCount) ) 

#define IImageList2_SetBkColor(This,clrBk,pclr)	\
    ( (This)->lpVtbl -> SetBkColor(This,clrBk,pclr) ) 

#define IImageList2_GetBkColor(This,pclr)	\
    ( (This)->lpVtbl -> GetBkColor(This,pclr) ) 

#define IImageList2_BeginDrag(This,iTrack,dxHotspot,dyHotspot)	\
    ( (This)->lpVtbl -> BeginDrag(This,iTrack,dxHotspot,dyHotspot) ) 

#define IImageList2_EndDrag(This)	\
    ( (This)->lpVtbl -> EndDrag(This) ) 

#define IImageList2_DragEnter(This,hwndLock,x,y)	\
    ( (This)->lpVtbl -> DragEnter(This,hwndLock,x,y) ) 

#define IImageList2_DragLeave(This,hwndLock)	\
    ( (This)->lpVtbl -> DragLeave(This,hwndLock) ) 

#define IImageList2_DragMove(This,x,y)	\
    ( (This)->lpVtbl -> DragMove(This,x,y) ) 

#define IImageList2_SetDragCursorImage(This,punk,iDrag,dxHotspot,dyHotspot)	\
    ( (This)->lpVtbl -> SetDragCursorImage(This,punk,iDrag,dxHotspot,dyHotspot) ) 

#define IImageList2_DragShowNolock(This,fShow)	\
    ( (This)->lpVtbl -> DragShowNolock(This,fShow) ) 

#define IImageList2_GetDragImage(This,ppt,pptHotspot,riid,ppv)	\
    ( (This)->lpVtbl -> GetDragImage(This,ppt,pptHotspot,riid,ppv) ) 

#define IImageList2_GetItemFlags(This,i,dwFlags)	\
    ( (This)->lpVtbl -> GetItemFlags(This,i,dwFlags) ) 

#define IImageList2_GetOverlayImage(This,iOverlay,piIndex)	\
    ( (This)->lpVtbl -> GetOverlayImage(This,iOverlay,piIndex) ) 


#define IImageList2_Resize(This,cxNewIconSize,cyNewIconSize)	\
    ( (This)->lpVtbl -> Resize(This,cxNewIconSize,cyNewIconSize) ) 

#define IImageList2_SetDevice(This,punk)	\
    ( (This)->lpVtbl -> SetDevice(This,punk) ) 

#define IImageList2_GetTextureInformation(This,piCount,piRows,piCols)	\
    ( (This)->lpVtbl -> GetTextureInformation(This,piCount,piRows,piCols) ) 

#define IImageList2_GetImageTextureInfo(This,fStyle,iImage,piTexture,prcImage,ppTexture)	\
    ( (This)->lpVtbl -> GetImageTextureInfo(This,fStyle,iImage,piTexture,prcImage,ppTexture) ) 

#define IImageList2_SelectTexture(This,iTexture)	\
    ( (This)->lpVtbl -> SelectTexture(This,iTexture) ) 

#define IImageList2_GetOriginalSize(This,iImage,pcx,pcy)	\
    ( (This)->lpVtbl -> GetOriginalSize(This,iImage,pcx,pcy) ) 

#define IImageList2_SetOriginalSize(This,iImage,cx,cy)	\
    ( (This)->lpVtbl -> SetOriginalSize(This,iImage,cx,cy) ) 

#define IImageList2_SetCallback(This,punk)	\
    ( (This)->lpVtbl -> SetCallback(This,punk) ) 

#define IImageList2_GetCallback(This,riid,ppv)	\
    ( (This)->lpVtbl -> GetCallback(This,riid,ppv) ) 

#define IImageList2_ForceImagePresent(This,iImage,dwFlags)	\
    ( (This)->lpVtbl -> ForceImagePresent(This,iImage,dwFlags) ) 

#define IImageList2_DiscardImages(This,iFirstImage,iLastImage,dwFlags)	\
    ( (This)->lpVtbl -> DiscardImages(This,iFirstImage,iLastImage,dwFlags) ) 

#define IImageList2_PreloadImages(This,pimldp)	\
    ( (This)->lpVtbl -> PreloadImages(This,pimldp) ) 

#define IImageList2_GetStatistics(This,pils)	\
    ( (This)->lpVtbl -> GetStatistics(This,pils) ) 

#define IImageList2_Initialize(This,cx,cy,flags,cInitial,cGrow)	\
    ( (This)->lpVtbl -> Initialize(This,cx,cy,flags,cInitial,cGrow) ) 

#define IImageList2_GetMILBrushInformation(This,piCount,piRows,piCols)	\
    ( (This)->lpVtbl -> GetMILBrushInformation(This,piCount,piRows,piCols) ) 

#define IImageList2_GetImageMILBrushInfo(This,fStyle,iImage,piMILBrush,prcImage,ppMILBrush)	\
    ( (This)->lpVtbl -> GetImageMILBrushInfo(This,fStyle,iImage,piMILBrush,prcImage,ppMILBrush) ) 

#define IImageList2_GetMILBrush(This,iMILBrush,riid,ppv)	\
    ( (This)->lpVtbl -> GetMILBrush(This,iMILBrush,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageList2_Resize_Proxy( 
    IImageList2 * This,
    int cxNewIconSize,
    int cyNewIconSize);


void __RPC_STUB IImageList2_Resize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_SetDevice_Proxy( 
    IImageList2 * This,
    /* [in] */ IUnknown *punk);


void __RPC_STUB IImageList2_SetDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetTextureInformation_Proxy( 
    IImageList2 * This,
    /* [out] */ UINT *piCount,
    /* [out] */ UINT *piRows,
    /* [out] */ UINT *piCols);


void __RPC_STUB IImageList2_GetTextureInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetImageTextureInfo_Proxy( 
    IImageList2 * This,
    /* [in] */ DWORD fStyle,
    /* [in] */ int iImage,
    /* [out] */ UINT *piTexture,
    /* [out] */ RECT *prcImage,
    /* [out] */ IUnknown **ppTexture);


void __RPC_STUB IImageList2_GetImageTextureInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_SelectTexture_Proxy( 
    IImageList2 * This,
    /* [in] */ UINT iTexture);


void __RPC_STUB IImageList2_SelectTexture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetOriginalSize_Proxy( 
    IImageList2 * This,
    /* [in] */ int iImage,
    /* [out] */ int *pcx,
    /* [out] */ int *pcy);


void __RPC_STUB IImageList2_GetOriginalSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_SetOriginalSize_Proxy( 
    IImageList2 * This,
    /* [in] */ int iImage,
    /* [in] */ int cx,
    /* [in] */ int cy);


void __RPC_STUB IImageList2_SetOriginalSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_SetCallback_Proxy( 
    IImageList2 * This,
    /* [in] */ IUnknown *punk);


void __RPC_STUB IImageList2_SetCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetCallback_Proxy( 
    IImageList2 * This,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ PVOID *ppv);


void __RPC_STUB IImageList2_GetCallback_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_ForceImagePresent_Proxy( 
    IImageList2 * This,
    /* [in] */ int iImage,
    DWORD dwFlags);


void __RPC_STUB IImageList2_ForceImagePresent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_DiscardImages_Proxy( 
    IImageList2 * This,
    /* [in] */ int iFirstImage,
    /* [in] */ int iLastImage,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IImageList2_DiscardImages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_PreloadImages_Proxy( 
    IImageList2 * This,
    /* [in] */ IMAGELISTDRAWPARAMS *pimldp);


void __RPC_STUB IImageList2_PreloadImages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetStatistics_Proxy( 
    IImageList2 * This,
    /* [out][in] */ IMAGELISTSTATS *pils);


void __RPC_STUB IImageList2_GetStatistics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_Initialize_Proxy( 
    IImageList2 * This,
    /* [in] */ int cx,
    /* [in] */ int cy,
    /* [in] */ UINT flags,
    /* [in] */ int cInitial,
    /* [in] */ int cGrow);


void __RPC_STUB IImageList2_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetMILBrushInformation_Proxy( 
    IImageList2 * This,
    /* [out] */ UINT *piCount,
    /* [out] */ UINT *piRows,
    /* [out] */ UINT *piCols);


void __RPC_STUB IImageList2_GetMILBrushInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetImageMILBrushInfo_Proxy( 
    IImageList2 * This,
    /* [in] */ DWORD fStyle,
    /* [in] */ int iImage,
    /* [out] */ UINT *piMILBrush,
    /* [out] */ RECT *prcImage,
    /* [out] */ IUnknown **ppMILBrush);


void __RPC_STUB IImageList2_GetImageMILBrushInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageList2_GetMILBrush_Proxy( 
    IImageList2 * This,
    /* [in] */ UINT iMILBrush,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ PVOID *ppv);


void __RPC_STUB IImageList2_GetMILBrush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageList2_INTERFACE_DEFINED__ */


#ifndef __IImageListSparseCallback_INTERFACE_DEFINED__
#define __IImageListSparseCallback_INTERFACE_DEFINED__

/* interface IImageListSparseCallback */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IImageListSparseCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("04CA44B2-D3BC-4ED5-A460-AEDBB6FC88EA")
    IImageListSparseCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ForceImagePresent( 
            /* [in] */ int iImage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            REFIID riid,
            /* [iid_is][out] */ void **ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageListSparseCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImageListSparseCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImageListSparseCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImageListSparseCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *ForceImagePresent )( 
            IImageListSparseCallback * This,
            /* [in] */ int iImage);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IImageListSparseCallback * This,
            REFIID riid,
            /* [iid_is][out] */ void **ppv);
        
        END_INTERFACE
    } IImageListSparseCallbackVtbl;

    interface IImageListSparseCallback
    {
        CONST_VTBL struct IImageListSparseCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageListSparseCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImageListSparseCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImageListSparseCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImageListSparseCallback_ForceImagePresent(This,iImage)	\
    ( (This)->lpVtbl -> ForceImagePresent(This,iImage) ) 

#define IImageListSparseCallback_Clone(This,riid,ppv)	\
    ( (This)->lpVtbl -> Clone(This,riid,ppv) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageListSparseCallback_ForceImagePresent_Proxy( 
    IImageListSparseCallback * This,
    /* [in] */ int iImage);


void __RPC_STUB IImageListSparseCallback_ForceImagePresent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageListSparseCallback_Clone_Proxy( 
    IImageListSparseCallback * This,
    REFIID riid,
    /* [iid_is][out] */ void **ppv);


void __RPC_STUB IImageListSparseCallback_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageListSparseCallback_INTERFACE_DEFINED__ */


#ifndef __IImageListContainer_INTERFACE_DEFINED__
#define __IImageListContainer_INTERFACE_DEFINED__

/* interface IImageListContainer */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IImageListContainer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D44E5013-2FA4-4041-99FC-40F0AD1522B3")
    IImageListContainer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetImageLists( 
            /* [in] */ ULONG celt,
            /* [size_is][in] */ IImageList **rgpiml) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetImageLists( 
            /* [out] */ ULONG *pceltFetched,
            /* [size_is][size_is][out] */ IImageList ***prgpiml) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageListContainerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IImageListContainer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IImageListContainer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IImageListContainer * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageLists )( 
            IImageListContainer * This,
            /* [in] */ ULONG celt,
            /* [size_is][in] */ IImageList **rgpiml);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageLists )( 
            IImageListContainer * This,
            /* [out] */ ULONG *pceltFetched,
            /* [size_is][size_is][out] */ IImageList ***prgpiml);
        
        END_INTERFACE
    } IImageListContainerVtbl;

    interface IImageListContainer
    {
        CONST_VTBL struct IImageListContainerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageListContainer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IImageListContainer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IImageListContainer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IImageListContainer_SetImageLists(This,celt,rgpiml)	\
    ( (This)->lpVtbl -> SetImageLists(This,celt,rgpiml) ) 

#define IImageListContainer_GetImageLists(This,pceltFetched,prgpiml)	\
    ( (This)->lpVtbl -> GetImageLists(This,pceltFetched,prgpiml) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageListContainer_SetImageLists_Proxy( 
    IImageListContainer * This,
    /* [in] */ ULONG celt,
    /* [size_is][in] */ IImageList **rgpiml);


void __RPC_STUB IImageListContainer_SetImageLists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageListContainer_GetImageLists_Proxy( 
    IImageListContainer * This,
    /* [out] */ ULONG *pceltFetched,
    /* [size_is][size_is][out] */ IImageList ***prgpiml);


void __RPC_STUB IImageListContainer_GetImageLists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageListContainer_INTERFACE_DEFINED__ */


#ifndef __IAggregateImageList_INTERFACE_DEFINED__
#define __IAggregateImageList_INTERFACE_DEFINED__

/* interface IAggregateImageList */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IAggregateImageList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8553A068-DCCC-44B6-8784-4C9E197BFBFD")
    IAggregateImageList : public IImageListContainer
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddAggregated( 
            /* [in] */ int iImageListIndex,
            /* [in] */ int iImageListImageIndex,
            /* [out] */ int *piAdded) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReplaceAggregated( 
            /* [in] */ int iImageIndex,
            /* [in] */ int iImageListIndex,
            /* [in] */ int iImageListImageIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAggregated( 
            /* [in] */ int iImageIndex,
            /* [out] */ int *piImageListIndex,
            /* [out] */ int *piImageListImageIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAggregateImageListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAggregateImageList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAggregateImageList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAggregateImageList * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageLists )( 
            IAggregateImageList * This,
            /* [in] */ ULONG celt,
            /* [size_is][in] */ IImageList **rgpiml);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageLists )( 
            IAggregateImageList * This,
            /* [out] */ ULONG *pceltFetched,
            /* [size_is][size_is][out] */ IImageList ***prgpiml);
        
        HRESULT ( STDMETHODCALLTYPE *AddAggregated )( 
            IAggregateImageList * This,
            /* [in] */ int iImageListIndex,
            /* [in] */ int iImageListImageIndex,
            /* [out] */ int *piAdded);
        
        HRESULT ( STDMETHODCALLTYPE *ReplaceAggregated )( 
            IAggregateImageList * This,
            /* [in] */ int iImageIndex,
            /* [in] */ int iImageListIndex,
            /* [in] */ int iImageListImageIndex);
        
        HRESULT ( STDMETHODCALLTYPE *GetAggregated )( 
            IAggregateImageList * This,
            /* [in] */ int iImageIndex,
            /* [out] */ int *piImageListIndex,
            /* [out] */ int *piImageListImageIndex);
        
        END_INTERFACE
    } IAggregateImageListVtbl;

    interface IAggregateImageList
    {
        CONST_VTBL struct IAggregateImageListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAggregateImageList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAggregateImageList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAggregateImageList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAggregateImageList_SetImageLists(This,celt,rgpiml)	\
    ( (This)->lpVtbl -> SetImageLists(This,celt,rgpiml) ) 

#define IAggregateImageList_GetImageLists(This,pceltFetched,prgpiml)	\
    ( (This)->lpVtbl -> GetImageLists(This,pceltFetched,prgpiml) ) 


#define IAggregateImageList_AddAggregated(This,iImageListIndex,iImageListImageIndex,piAdded)	\
    ( (This)->lpVtbl -> AddAggregated(This,iImageListIndex,iImageListImageIndex,piAdded) ) 

#define IAggregateImageList_ReplaceAggregated(This,iImageIndex,iImageListIndex,iImageListImageIndex)	\
    ( (This)->lpVtbl -> ReplaceAggregated(This,iImageIndex,iImageListIndex,iImageListImageIndex) ) 

#define IAggregateImageList_GetAggregated(This,iImageIndex,piImageListIndex,piImageListImageIndex)	\
    ( (This)->lpVtbl -> GetAggregated(This,iImageIndex,piImageListIndex,piImageListImageIndex) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAggregateImageList_AddAggregated_Proxy( 
    IAggregateImageList * This,
    /* [in] */ int iImageListIndex,
    /* [in] */ int iImageListImageIndex,
    /* [out] */ int *piAdded);


void __RPC_STUB IAggregateImageList_AddAggregated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAggregateImageList_ReplaceAggregated_Proxy( 
    IAggregateImageList * This,
    /* [in] */ int iImageIndex,
    /* [in] */ int iImageListIndex,
    /* [in] */ int iImageListImageIndex);


void __RPC_STUB IAggregateImageList_ReplaceAggregated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAggregateImageList_GetAggregated_Proxy( 
    IAggregateImageList * This,
    /* [in] */ int iImageIndex,
    /* [out] */ int *piImageListIndex,
    /* [out] */ int *piImageListImageIndex);


void __RPC_STUB IAggregateImageList_GetAggregated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAggregateImageList_INTERFACE_DEFINED__ */


#ifndef __IGangImageList_INTERFACE_DEFINED__
#define __IGangImageList_INTERFACE_DEFINED__

/* interface IGangImageList */
/* [object][local][helpstring][uuid] */ 


EXTERN_C const IID IID_IGangImageList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("50625B30-70F4-4281-B919-4B4E79BC2CA4")
    IGangImageList : public IImageListContainer
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDrawOrder( 
            /* [in] */ int cx,
            /* [in] */ int ciOrder,
            /* [size_is][out] */ int rgiOrder[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGangImageListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGangImageList * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGangImageList * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGangImageList * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetImageLists )( 
            IGangImageList * This,
            /* [in] */ ULONG celt,
            /* [size_is][in] */ IImageList **rgpiml);
        
        HRESULT ( STDMETHODCALLTYPE *GetImageLists )( 
            IGangImageList * This,
            /* [out] */ ULONG *pceltFetched,
            /* [size_is][size_is][out] */ IImageList ***prgpiml);
        
        HRESULT ( STDMETHODCALLTYPE *GetDrawOrder )( 
            IGangImageList * This,
            /* [in] */ int cx,
            /* [in] */ int ciOrder,
            /* [size_is][out] */ int rgiOrder[  ]);
        
        END_INTERFACE
    } IGangImageListVtbl;

    interface IGangImageList
    {
        CONST_VTBL struct IGangImageListVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGangImageList_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGangImageList_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGangImageList_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGangImageList_SetImageLists(This,celt,rgpiml)	\
    ( (This)->lpVtbl -> SetImageLists(This,celt,rgpiml) ) 

#define IGangImageList_GetImageLists(This,pceltFetched,prgpiml)	\
    ( (This)->lpVtbl -> GetImageLists(This,pceltFetched,prgpiml) ) 


#define IGangImageList_GetDrawOrder(This,cx,ciOrder,rgiOrder)	\
    ( (This)->lpVtbl -> GetDrawOrder(This,cx,ciOrder,rgiOrder) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGangImageList_GetDrawOrder_Proxy( 
    IGangImageList * This,
    /* [in] */ int cx,
    /* [in] */ int ciOrder,
    /* [size_is][out] */ int rgiOrder[  ]);


void __RPC_STUB IGangImageList_GetDrawOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGangImageList_INTERFACE_DEFINED__ */



#ifndef __CommonControlObjects_LIBRARY_DEFINED__
#define __CommonControlObjects_LIBRARY_DEFINED__

/* library CommonControlObjects */
/* [uuid] */ 


EXTERN_C const IID LIBID_CommonControlObjects;

EXTERN_C const CLSID CLSID_ImageList;

#ifdef __cplusplus

class DECLSPEC_UUID("7C476BA2-02B1-48f4-8048-B24619DDC058")
ImageList;
#endif

EXTERN_C const CLSID CLSID_SparseImageList;

#ifdef __cplusplus

class DECLSPEC_UUID("2AC0B4F3-6D94-4530-B889-497343D6B112")
SparseImageList;
#endif

EXTERN_C const CLSID CLSID_AggregateImageList;

#ifdef __cplusplus

class DECLSPEC_UUID("5C7827C4-7381-496F-9463-1A1522EB7F04")
AggregateImageList;
#endif

EXTERN_C const CLSID CLSID_GangImageList;

#ifdef __cplusplus

class DECLSPEC_UUID("BB8D2C61-6AC0-4850-BC0F-B1C21B4182E3")
GangImageList;
#endif
#endif /* __CommonControlObjects_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_commoncontrols_0264 */
/* [local] */ 

#endif // if (_WIN32_IE >= 0x0501)


extern RPC_IF_HANDLE __MIDL_itf_commoncontrols_0264_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_commoncontrols_0264_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


