//---------------------------------------------------------------------------
//
// uxtheme.h - theming API header file.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//---------------------------------------------------------------------------

#ifndef _UXTHEME_H_
#define _UXTHEME_H_

#include <commctrl.h>
#include <SpecStrings.h>

#ifndef THEMEAPI
#if !defined(_UXTHEME_)
#define THEMEAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define THEMEAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#else
#define THEMEAPI          STDAPI
#define THEMEAPI_(type)   STDAPI_(type)
#endif /* _UXTHEME_ */
#endif /* THEMEAPI */

typedef HANDLE HTHEME;          // handle to a section of theme data for class

#define MAX_THEMECOLOR  64
#define MAX_THEMESIZE   64

THEMEAPI_(HTHEME)
OpenThemeData(
    HWND hwnd,
    LPCWSTR pszClassList
    );

#define OTD_FORCE_RECT_SIZING   0x00000001          // make all parts size to rect
#define OTD_NONCLIENT           0x00000002          // set if hTheme to be used for nonclient area
#define OTD_VALIDBITS           (OTD_FORCE_RECT_SIZING | \
                                 OTD_NONCLIENT)

THEMEAPI_(HTHEME)
OpenThemeDataEx(
    HWND hwnd,
    LPCWSTR pszClassList,
    DWORD dwFlags
    );

THEMEAPI
CloseThemeData(
    HTHEME hTheme
    );

THEMEAPI
DrawThemeBackground(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in LPCRECT pRect,
    __in __opt LPCRECT pClipRect
    );

#define DTBG_CLIPRECT           0x00000001  // rcClip has been specified
#define DTBG_DRAWSOLID          0x00000002  // draw transparent/alpha images as solid
#define DTBG_OMITBORDER         0x00000004  // don't draw border of part
#define DTBG_OMITCONTENT        0x00000008  // don't draw content area of part
#define DTBG_COMPUTINGREGION    0x00000010  // TRUE if calling to compute region
#define DTBG_MIRRORDC           0x00000020  // assume the hdc is mirrorred and
                                            // flip images as appropriate (currently 
                                            // only supported for bgtype=imagefile)
#define DTBG_VALIDBITS          (DTBG_CLIPRECT | \
                                 DTBG_DRAWSOLID | \
                                 DTBG_OMITBORDER | \
                                 DTBG_OMITCONTENT | \
                                 DTBG_COMPUTINGREGION | \
                                 DTBG_MIRRORDC)

typedef struct _DTBGOPTS
{
    DWORD dwSize;           // size of the struct
    DWORD dwFlags;          // which options have been specified
    RECT rcClip;            // clipping rectangle
} DTBGOPTS, *PDTBGOPTS;

THEMEAPI
DrawThemeBackgroundEx(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    LPCRECT pRect,
    __in __opt const DTBGOPTS *pOptions
    );

THEMEAPI
DrawThemeBackgroundTransition(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateIdFrom,
    int iStateIdTo,
    DWORD dwElapsed,
    DWORD dwDuration,
    __in LPCRECT pRect,
    __in __opt const DTBGOPTS *pOptions
    );

#define DTT_GRAYED              0x00000001          // draw a grayed-out string (this is deprecated)
#define DTT_FLAGS2VALIDBITS     (DTT_GRAYED)

THEMEAPI
DrawThemeText(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in_ecount(cchText) LPCWSTR pszText,
    int cchText,
    DWORD dwTextFlags,
    DWORD dwTextFlags2,
    __in LPCRECT pRect
    );

#define DTT_TEXTCOLOR       (1UL << 0)      // crText has been specified
#define DTT_BORDERCOLOR     (1UL << 1)      // crBorder has been specified
#define DTT_SHADOWCOLOR     (1UL << 2)      // crShadow has been specified
#define DTT_SHADOWTYPE      (1UL << 3)      // iTextShadowType has been specified
#define DTT_SHADOWOFFSET    (1UL << 4)      // ptShadowOffset has been specified
#define DTT_BORDERSIZE      (1UL << 5)      // iBorderSize has been specified
#define DTT_FONTPROP        (1UL << 6)      // iFontPropId has been specified
#define DTT_COLORPROP       (1UL << 7)      // iColorPropId has been specified
#define DTT_STATEID         (1UL << 8)      // IStateId has been specified
#define DTT_CALCRECT        (1UL << 9)      // Use pRect as and in/out parameter
#define DTT_APPLYOVERLAY    (1UL << 10)     // fApplyOverlay has been specified
#define DTT_GLOWSIZE        (1UL << 11)     // iGlowSize has been specified
#define DTT_VALIDBITS       (DTT_TEXTCOLOR | \
                             DTT_BORDERCOLOR | \
                             DTT_SHADOWCOLOR | \
                             DTT_SHADOWTYPE | \
                             DTT_SHADOWOFFSET | \
                             DTT_BORDERSIZE | \
                             DTT_FONTPROP | \
                             DTT_COLORPROP | \
                             DTT_STATEID | \
                             DTT_CALCRECT | \
                             DTT_APPLYOVERLAY | \
                             DTT_GLOWSIZE)

typedef struct _DTTOPTS
{
    DWORD       dwSize;             // size of the struct
    DWORD       dwFlags;            // which options have been specified
    COLORREF    crText;             // color to use for text fill
    COLORREF    crBorder;           // color to use for text outline
    COLORREF    crShadow;           // color to use for text shadow
    int         eTextShadowType;    // TST_SINGLE or TST_CONTINUOUS
    POINT       ptShadowOffset;     // where shadow is drawn (relative to text)
    int         iBorderSize;        // Border radius around text
    int         iFontPropId;        // Font property to use for the text instead of TMT_FONT
    int         iColorPropId;       // Color property to use for the text instead of TMT_TEXTCOLOR
    int         iStateId;           // Alternate state id
    BOOL        fApplyOverlay;      // Overlay text on top of any text effect?
    int         iGlowSize;          // Glow radious around text
} DTTOPTS, *PDTTOPTS;

THEMEAPI
DrawThemeTextEx(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in_ecount(cchText) LPCWSTR pszText,
    int cchText,
    DWORD dwTextFlags,
    __in __out LPRECT pRect,
    __in __opt const DTTOPTS *pOptions
    );

THEMEAPI
DrawThemeTextTransition(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateIdFrom,
    int iStateIdTo,
    DWORD dwElapsed,
    DWORD dwDuration,
    __in_ecount(cchText) LPCWSTR pszText,
    int cchText,
    DWORD dwTextFlags,
    __in __out LPRECT pRect,
    __in __opt const DTTOPTS *pOptions
    );

THEMEAPI
GetThemeBackgroundContentRect(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in LPCRECT pBoundingRect,
    __out LPRECT pContentRect
    );

THEMEAPI
GetThemeBackgroundExtent(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in LPCRECT pContentRect,
    __out LPRECT pExtentRect
    );

THEMEAPI
GetThemeBackgroundRegion(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    LPCRECT pRect,
    __out HRGN *pRegion
    );

enum THEMESIZE
{
    TS_MIN,             // minimum size
    TS_TRUE,            // size without stretching
    TS_DRAW             // size that theme mgr will use to draw part
};

THEMEAPI
GetThemePartSize(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in __opt LPCRECT prc,
    enum THEMESIZE eSize,
    __out SIZE *psz
    );

THEMEAPI
GetThemeTextExtent(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __in_ecount(cchCharCount) LPCWSTR pszText,
    int cchCharCount,
    DWORD dwTextFlags,
    LPCRECT pBoundingRect,
    __out LPRECT pExtentRect
    );

THEMEAPI
GetThemeTextMetrics(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    __out TEXTMETRICW *ptm
    );

THEMEAPI
GetThemeTransitionDuration(
    HTHEME hTheme,
    int iPartId,
    int iStateIdFrom,
    int iStateIdTo,
    int iPropId,
    __out DWORD *pdwDuration
    );

#define HTTB_BACKGROUNDSEG          0x00000000
#define HTTB_FIXEDBORDER            0x00000002      // Return code may be either HTCLIENT or HTBORDER. 
#define HTTB_CAPTION                0x00000004
#define HTTB_RESIZINGBORDER_LEFT    0x00000010      // Hit test left resizing border, 
#define HTTB_RESIZINGBORDER_TOP     0x00000020      // Hit test top resizing border
#define HTTB_RESIZINGBORDER_RIGHT   0x00000040      // Hit test right resizing border
#define HTTB_RESIZINGBORDER_BOTTOM  0x00000080      // Hit test bottom resizing border
#define HTTB_RESIZINGBORDER         (HTTB_RESIZINGBORDER_LEFT | \
                                     HTTB_RESIZINGBORDER_TOP | \
                                     HTTB_RESIZINGBORDER_RIGHT | \
                                     HTTB_RESIZINGBORDER_BOTTOM)
#define HTTB_SIZINGTEMPLATE         0x00000100
#define HTTB_SYSTEMSIZINGMARGINS    0x00000200

THEMEAPI
HitTestThemeBackground(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    DWORD dwOptions,
    LPCRECT pRect,
    HRGN hrgn,
    POINT ptTest,
    __out WORD *pwHitTestCode
    );

THEMEAPI
DrawThemeEdge(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    LPCRECT pDestRect,
    UINT uEdge,
    UINT uFlags,
    __out __opt LPRECT pContentRect
    );

THEMEAPI
DrawThemeIcon(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    LPCRECT pRect,
    HIMAGELIST himl,
    int iImageIndex
    );

THEMEAPI_(BOOL)
IsThemePartDefined(
    HTHEME hTheme,
    int iPartId,
    int iStateId
    );

THEMEAPI_(BOOL)
IsThemeBackgroundPartiallyTransparent(
    HTHEME hTheme,
    int iPartId,
    int iStateId
    );

THEMEAPI
GetThemeColor(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out COLORREF *pColor
    );

THEMEAPI
GetThemeMetric(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    int iPropId,
    __out int *piVal
    );

THEMEAPI
GetThemeString(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out_ecount(cchMaxBuffChars) LPWSTR pszBuff,
    int cchMaxBuffChars
    );

THEMEAPI
GetThemeBool(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out BOOL *pfVal
    );

THEMEAPI
GetThemeInt(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out int *piVal
    );

THEMEAPI
GetThemeEnumValue(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out int *piVal
    );

THEMEAPI
GetThemePosition(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out POINT *pPoint
    );

THEMEAPI
GetThemeFont(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    int iPropId,
    __out LOGFONTW *pFont
    );

THEMEAPI
GetThemeRect(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out LPRECT pRect
    );

typedef struct _MARGINS
{
    int cxLeftWidth;
    int cxRightWidth;
    int cyTopHeight;
    int cyBottomHeight;
} MARGINS, *PMARGINS;

THEMEAPI
GetThemeMargins(
    HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    int iPropId,
    __in __opt LPCRECT prc,
    __out MARGINS *pMargins
    );

#if WINVER >= 0x0600
#define MAX_INTLIST_COUNT 250
#else
#define MAX_INTLIST_COUNT 10
#endif

typedef struct _INTLIST
{
    int iValueCount;
    int iValues[MAX_INTLIST_COUNT];
} INTLIST, *PINTLIST;

THEMEAPI
GetThemeIntList(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out INTLIST *pIntList
    );

THEMEAPI
GetThemeStream(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out VOID **ppvStream,
    __out __opt DWORD *pcbStream
    );

enum PROPERTYORIGIN
{
    PO_STATE,           // property was found in the state section
    PO_PART,            // property was found in the part section
    PO_CLASS,           // property was found in the class section
    PO_GLOBAL,          // property was found in [globals] section
    PO_NOTFOUND         // property was not found
};

THEMEAPI
GetThemePropertyOrigin(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out enum PROPERTYORIGIN *pOrigin
    );

enum THEMEPROPERTYIDTYPE
{
    TIDTYPE_HTHEME,     // valid theme handle + part ID, state ID and property ID.
    TIDTYPE_CLASS,      // class name string + part ID, state ID and property ID.
    TIDTYPE_SYMBOL      // symbolic form: "ClassName.PartName.StateName.PropertyName"
};

typedef struct _THEMEPROPERTYID
{
    enum THEMEPROPERTYIDTYPE type;   // property type discriminator
    union
    {
        HTHEME hTheme;          // valid theme handle (TIDTYPE_HTHEME)
        LPWSTR pszClass;        // valid class name (TIDTYPE_CLASS)
        LPWSTR pszSymbolicName; // property symbol in the form "ClassName.PartName.StateName.Propertyname"
                                //    (TIDTYPE_SYMBOLIC)
    } cid;
    int    iPartId;             // part number (ignored for TIDTYPE_SYMBOLIC)
    int    iStateId;            // state number (ignored for TIDTYPE_SYMBOLIC)
    int    iPropId;             // property number (ignored for TIDTYPE_SYMBOLIC)
} THEMEPROPERTYID, *PTHEMEPROPERTYID;

typedef struct _THEMEPROPERTYVALUEHDR
{
    HRESULT     hrValue;    // error code if retrieval failed.
    int         iType;      // data type for the value
    BYTE *      pbValue;    // value data (points to the beginning of the value data)
    int         cbValue;    // count of bytes of value data
} THEMEPROPERTYVALUEHDR, *PTHEMEPROPERTYVALUEHDR;

THEMEAPI
GetThemePropertyValues(
    const THEMEPROPERTYID* prgProperties,
    int cProperties,
    __out BYTE** ppbValues,
    __out ULONG* pcbValues
    );

THEMEAPI
FreeThemePropertyValues(
    __in BYTE* pbValues
    );

THEMEAPI
SetWindowTheme(
    HWND hwnd,
    LPCWSTR pszSubAppName,
    LPCWSTR pszSubIdList
    );

enum WINDOWTHEMEATTRIBUTETYPE
{
    WTA_NONCLIENT = 1
};

typedef struct _WTA_OPTIONS
{
    DWORD dwFlags;          // values for each style option specified in the bitmask
    DWORD dwMask;           // bitmask for flags that are changing
                            // valid options are: WTNCA_NODRAWCAPTION, WTNCA_NODRAWICON, WTNCA_NOSYSMENU
} WTA_OPTIONS, *PWTA_OPTIONS;

#define WTNCA_NODRAWCAPTION       0x00000001    // don't draw the window caption
#define WTNCA_NODRAWICON          0x00000002    // don't draw the system icon
#define WTNCA_NOSYSMENU           0x00000004    // don't expose the system menu icon functionality
#define WTNCA_VALIDBITS           (WTNCA_NODRAWCAPTION | \
                                   WTNCA_NODRAWICON | \
                                   WTNCA_NOSYSMENU)

THEMEAPI
SetWindowThemeAttribute(
    HWND hwnd,
    enum WINDOWTHEMEATTRIBUTETYPE eAttribute,
    __in_bcount(cbParam) PVOID pvAttribute,
    DWORD cbAttribute
    );

__inline HRESULT SetWindowThemeNonClientAttributes(HWND hwnd, DWORD dwMask, DWORD dwAttributes)    
{
    WTA_OPTIONS wta;
    wta.dwFlags = dwAttributes;
    wta.dwMask = dwMask;
    return SetWindowThemeAttribute(hwnd, WTA_NONCLIENT, (void*)&(wta), sizeof(wta));
}

THEMEAPI
GetWindowTitleWithInk(
    HWND hWnd,
    __in_bcount(cbInk) LPBYTE pbInk,
    UINT *pcbInk,
    LPWSTR pszText,
    UINT *pcchText
    );

THEMEAPI
SetWindowTitleWithInk(
    HWND hWnd,
    __in_bcount(cbInk) LPBYTE pbInk,
    UINT cbInk,
    LPCWSTR pszText
    );

THEMEAPI
GetThemeFilename(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    __out_ecount(cchMaxBuffChars) LPWSTR pszThemeFileName,
    int cchMaxBuffChars
    );

THEMEAPI_(COLORREF)
GetThemeSysColor(
    HTHEME hTheme,
    int iColorId
    );

THEMEAPI_(HBRUSH)
GetThemeSysColorBrush(
    HTHEME hTheme,
    int iColorId
    );

THEMEAPI_(BOOL)
GetThemeSysBool(
    HTHEME hTheme,
    int iBoolId
    );

THEMEAPI_(int)
GetThemeSysSize(
    HTHEME hTheme,
    int iSizeId
    );

THEMEAPI
GetThemeSysFont(
    HTHEME hTheme,
    int iFontId,
    __out LOGFONTW *plf
    );

THEMEAPI
GetThemeSysString(
    HTHEME hTheme,
    int iStringId,
    __out_ecount(cchMaxStringChars) LPWSTR pszStringBuff,
    int cchMaxStringChars
    );

THEMEAPI
GetThemeSysInt(
    HTHEME hTheme,
    int iIntId,
    __out int *piValue
    );

THEMEAPI_(BOOL)
IsThemeActive(
    VOID
    );

THEMEAPI_(BOOL)
IsAppThemed(
    VOID
    );

THEMEAPI_(HTHEME)
GetWindowTheme(
    HWND hwnd
    );

#define ETDT_DISABLE        0x00000001
#define ETDT_ENABLE         0x00000002
#define ETDT_USETABTEXTURE  0x00000004
#define ETDT_ENABLETAB      (ETDT_ENABLE | \
                             ETDT_USETABTEXTURE)
#define ETDT_VALIDBITS      (ETDT_DISABLE | \
                             ETDT_ENABLE | \
                             ETDT_USETABTEXTURE)

THEMEAPI
EnableThemeDialogTexture(
    __in HWND hwnd,
    __in DWORD dwFlags
    );

THEMEAPI_(BOOL)
IsThemeDialogTextureEnabled(
    __in HWND hwnd
    );

#define STAP_ALLOW_NONCLIENT    (1UL << 0)
#define STAP_ALLOW_CONTROLS     (1UL << 1)
#define STAP_ALLOW_WEBCONTENT   (1UL << 2)
#define STAP_VALIDBITS          (STAP_ALLOW_NONCLIENT | \
                                 STAP_ALLOW_CONTROLS | \
                                 STAP_ALLOW_WEBCONTENT)

THEMEAPI_(DWORD)
GetThemeAppProperties(
    VOID
    );

THEMEAPI_(void)
SetThemeAppProperties(
    DWORD dwFlags
    );

THEMEAPI GetCurrentThemeName(
    __out_ecount(cchMaxNameChars) LPWSTR pszThemeFileName,
    int cchMaxNameChars,
    __out_ecount(cchMaxColorChars) __opt LPWSTR pszColorBuff,
    int cchMaxColorChars,
    __out_ecount(cchMaxSizeChars) __opt LPWSTR pszSizeBuff,
    int cchMaxSizeChars
    );

#define SZ_THDOCPROP_DISPLAYNAME    L"DisplayName"
#define SZ_THDOCPROP_CANONICALNAME  L"ThemeName"
#define SZ_THDOCPROP_TOOLTIP        L"ToolTip"
#define SZ_THDOCPROP_AUTHOR         L"author"

THEMEAPI
GetThemeDocumentationProperty(
    LPCWSTR pszThemeName,
    __in LPCWSTR pszPropertyName,
    __out_ecount(cchMaxValChars) LPWSTR pszValueBuff,
    int cchMaxValChars
    );

THEMEAPI
DrawThemeParentBackground(
    HWND hwnd,
    HDC hdc,
    __in __opt const RECT* prc
    );

THEMEAPI
EnableTheming(
    BOOL fEnable
    );

typedef HANDLE HTHEMESYMBOLS;

THEMEAPI
LoadThemeSymbols(
    LPCWSTR pszThemeFile,
    __out HTHEMESYMBOLS* phSymbols
    );

THEMEAPI
FreeThemeSymbols(
    HTHEMESYMBOLS hSymbols
    );

THEMEAPI
ParseThemeSymbol(
    HTHEMESYMBOLS hThemeSymbol,
    __in LPCWSTR pszSpec,
    __out __opt LPWSTR pszClass,
    __inout __opt int* pcchClass,
    __out __opt int* piPart,
    __out __opt int* piState,
    __out __opt int* piProperty,
    __out __opt int* piType
    );

#define GBF_DIRECT      0x00000001      // direct dereferencing.
#define GBF_COPY        0x00000002      // create a copy of the bitmap
#define GBF_VALIDBITS   (GBF_DIRECT | \
                         GBF_COPY)

THEMEAPI
GetThemeBitmap(
    HTHEME hTheme,
    int iPartId,
    int iStateId,
    int iPropId,
    ULONG dwFlags,
    __out HANDLE* phGdiObj
    );

#endif /* _UXTHEME_H_ */

