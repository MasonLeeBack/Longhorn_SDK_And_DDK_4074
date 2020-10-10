/* Copyright (c) 2001-2004, Microsoft Corp. All rights reserved. */

#if _MSC_VER > 1000
#pragma once
#endif

#if defined(__cplusplus)
extern "C" {
#endif


#if !defined(RC_INVOKED) /* RC complains about long symbols in #ifs */
#if defined(ISOLATION_AWARE_ENABLED) && (ISOLATION_AWARE_ENABLED != 0)


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
FARPROC WINAPI CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY(LPCSTR pszProcName);

#endif /* ISOLATION_AWARE_USE_STATIC_LIBRARY */
BOOL WINAPI IsolationAwareGetOpenFileNameA(LPOPENFILENAMEA unnamed1);
BOOL WINAPI IsolationAwareGetOpenFileNameW(LPOPENFILENAMEW unnamed1);
BOOL WINAPI IsolationAwareGetSaveFileNameA(LPOPENFILENAMEA unnamed1);
BOOL WINAPI IsolationAwareGetSaveFileNameW(LPOPENFILENAMEW unnamed1);
short WINAPI IsolationAwareGetFileTitleA(LPCSTR unnamed1,__out_bcount(cbSize) LPSTR Buf,__in WORD cbSize);
short WINAPI IsolationAwareGetFileTitleW(LPCWSTR unnamed1,__out_bcount(cbSize) LPWSTR Buf,__in WORD cbSize);
BOOL WINAPI IsolationAwareChooseColorA(LPCHOOSECOLORA unnamed1);
BOOL WINAPI IsolationAwareChooseColorW(LPCHOOSECOLORW unnamed1);
HWND WINAPI IsolationAwareFindTextA(LPFINDREPLACEA unnamed1);
HWND WINAPI IsolationAwareFindTextW(LPFINDREPLACEW unnamed1);
HWND WINAPI IsolationAwareReplaceTextA(LPFINDREPLACEA unnamed1);
HWND WINAPI IsolationAwareReplaceTextW(LPFINDREPLACEW unnamed1);
BOOL WINAPI IsolationAwareChooseFontA(LPCHOOSEFONTA unnamed1);
BOOL WINAPI IsolationAwareChooseFontW(LPCHOOSEFONTW unnamed1);
BOOL WINAPI IsolationAwarePrintDlgA(LPPRINTDLGA unnamed1);
BOOL WINAPI IsolationAwarePrintDlgW(LPPRINTDLGW unnamed1);
#if defined(STDMETHOD) && (WINVER >= 0x0500)
HRESULT WINAPI IsolationAwarePrintDlgExA(LPPRINTDLGEXA unnamed1);
HRESULT WINAPI IsolationAwarePrintDlgExW(LPPRINTDLGEXW unnamed1);
#endif /* defined(STDMETHOD) && (WINVER >= 0x0500) */
DWORD WINAPI IsolationAwareCommDlgExtendedError(void);
BOOL WINAPI IsolationAwarePageSetupDlgA(LPPAGESETUPDLGA unnamed1);
BOOL WINAPI IsolationAwarePageSetupDlgW(LPPAGESETUPDLGW unnamed1);

ISOLATION_AWARE_INLINE HRESULT CommdlgIsolationAwarePrivateJVaQPGbueRfhYg(void)
{
    DWORD dwLastError = GetLastError();
    if (dwLastError == NO_ERROR)
        dwLastError = ERROR_INTERNAL_ERROR;
    return HRESULT_FROM_WIN32(dwLastError);
}

#if defined(UNICODE)

#define IsolationAwareChooseColor IsolationAwareChooseColorW
#define IsolationAwareChooseFont IsolationAwareChooseFontW
#define IsolationAwareFindText IsolationAwareFindTextW
#define IsolationAwareGetFileTitle IsolationAwareGetFileTitleW
#define IsolationAwareGetOpenFileName IsolationAwareGetOpenFileNameW
#define IsolationAwareGetSaveFileName IsolationAwareGetSaveFileNameW
#define IsolationAwarePageSetupDlg IsolationAwarePageSetupDlgW
#define IsolationAwarePrintDlg IsolationAwarePrintDlgW
#define IsolationAwarePrintDlgEx IsolationAwarePrintDlgExW
#define IsolationAwareReplaceText IsolationAwareReplaceTextW

#else /* UNICODE */

#define IsolationAwareChooseColor IsolationAwareChooseColorA
#define IsolationAwareChooseFont IsolationAwareChooseFontA
#define IsolationAwareFindText IsolationAwareFindTextA
#define IsolationAwareGetFileTitle IsolationAwareGetFileTitleA
#define IsolationAwareGetOpenFileName IsolationAwareGetOpenFileNameA
#define IsolationAwareGetSaveFileName IsolationAwareGetSaveFileNameA
#define IsolationAwarePageSetupDlg IsolationAwarePageSetupDlgA
#define IsolationAwarePrintDlg IsolationAwarePrintDlgA
#define IsolationAwarePrintDlgEx IsolationAwarePrintDlgExA
#define IsolationAwareReplaceText IsolationAwareReplaceTextA

#endif /* UNICODE */

#if !ISOLATION_AWARE_USE_STATIC_LIBRARY
ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareGetOpenFileNameA(LPOPENFILENAMEA unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPOPENFILENAMEA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("GetOpenFileNameA");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareGetOpenFileNameW(LPOPENFILENAMEW unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPOPENFILENAMEW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("GetOpenFileNameW");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareGetSaveFileNameA(LPOPENFILENAMEA unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPOPENFILENAMEA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("GetSaveFileNameA");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareGetSaveFileNameW(LPOPENFILENAMEW unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPOPENFILENAMEW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("GetSaveFileNameW");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE short WINAPI IsolationAwareGetFileTitleA(LPCSTR unnamed1,__out_bcount(cbSize) LPSTR Buf,__in WORD cbSize)
{
    short nResult = -1;
    typedef short (WINAPI* PFN)(LPCSTR unnamed1,__out_bcount(cbSize) LPSTR Buf,__in WORD cbSize);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return nResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("GetFileTitleA");
            if (s_pfn == NULL)
                __leave;
        }
        nResult = s_pfn(unnamed1,Buf,cbSize);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (nResult == -1);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return nResult;
}

ISOLATION_AWARE_INLINE short WINAPI IsolationAwareGetFileTitleW(LPCWSTR unnamed1,__out_bcount(cbSize) LPWSTR Buf,__in WORD cbSize)
{
    short nResult = -1;
    typedef short (WINAPI* PFN)(LPCWSTR unnamed1,__out_bcount(cbSize) LPWSTR Buf,__in WORD cbSize);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return nResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("GetFileTitleW");
            if (s_pfn == NULL)
                __leave;
        }
        nResult = s_pfn(unnamed1,Buf,cbSize);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (nResult == -1);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return nResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareChooseColorA(LPCHOOSECOLORA unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPCHOOSECOLORA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("ChooseColorA");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareChooseColorW(LPCHOOSECOLORW unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPCHOOSECOLORW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("ChooseColorW");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE HWND WINAPI IsolationAwareFindTextA(LPFINDREPLACEA unnamed1)
{
    HWND windowResult = NULL;
    typedef HWND (WINAPI* PFN)(LPFINDREPLACEA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return windowResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("FindTextA");
            if (s_pfn == NULL)
                __leave;
        }
        windowResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (windowResult == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return windowResult;
}

ISOLATION_AWARE_INLINE HWND WINAPI IsolationAwareFindTextW(LPFINDREPLACEW unnamed1)
{
    HWND windowResult = NULL;
    typedef HWND (WINAPI* PFN)(LPFINDREPLACEW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return windowResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("FindTextW");
            if (s_pfn == NULL)
                __leave;
        }
        windowResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (windowResult == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return windowResult;
}

ISOLATION_AWARE_INLINE HWND WINAPI IsolationAwareReplaceTextA(LPFINDREPLACEA unnamed1)
{
    HWND windowResult = NULL;
    typedef HWND (WINAPI* PFN)(LPFINDREPLACEA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return windowResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("ReplaceTextA");
            if (s_pfn == NULL)
                __leave;
        }
        windowResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (windowResult == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return windowResult;
}

ISOLATION_AWARE_INLINE HWND WINAPI IsolationAwareReplaceTextW(LPFINDREPLACEW unnamed1)
{
    HWND windowResult = NULL;
    typedef HWND (WINAPI* PFN)(LPFINDREPLACEW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return windowResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("ReplaceTextW");
            if (s_pfn == NULL)
                __leave;
        }
        windowResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (windowResult == NULL);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return windowResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareChooseFontA(LPCHOOSEFONTA unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPCHOOSEFONTA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("ChooseFontA");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwareChooseFontW(LPCHOOSEFONTW unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPCHOOSEFONTW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("ChooseFontW");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwarePrintDlgA(LPPRINTDLGA unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPPRINTDLGA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("PrintDlgA");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwarePrintDlgW(LPPRINTDLGW unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPPRINTDLGW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("PrintDlgW");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

#if defined(STDMETHOD) && (WINVER >= 0x0500)

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwarePrintDlgExA(LPPRINTDLGEXA unnamed1)
{
    HRESULT result = S_OK;
    typedef HRESULT (WINAPI* PFN)(LPPRINTDLGEXA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return CommdlgIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("PrintDlgExA");
            if (s_pfn == NULL)
            {
                result = CommdlgIsolationAwarePrivateJVaQPGbueRfhYg();
                __leave;
            }
        }
        result = s_pfn(unnamed1);
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

ISOLATION_AWARE_INLINE HRESULT WINAPI IsolationAwarePrintDlgExW(LPPRINTDLGEXW unnamed1)
{
    HRESULT result = S_OK;
    typedef HRESULT (WINAPI* PFN)(LPPRINTDLGEXW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return CommdlgIsolationAwarePrivateJVaQPGbueRfhYg();
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("PrintDlgExW");
            if (s_pfn == NULL)
            {
                result = CommdlgIsolationAwarePrivateJVaQPGbueRfhYg();
                __leave;
            }
        }
        result = s_pfn(unnamed1);
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

#endif /* defined(STDMETHOD) && (WINVER >= 0x0500) */

ISOLATION_AWARE_INLINE DWORD WINAPI IsolationAwareCommDlgExtendedError(void)
{
    DWORD nResult = 0 ;
    typedef DWORD (WINAPI* PFN)(void);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return nResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("CommDlgExtendedError");
            if (s_pfn == NULL)
                __leave;
        }
        nResult = s_pfn();
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (nResult == 0 );
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return nResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwarePageSetupDlgA(LPPAGESETUPDLGA unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPPAGESETUPDLGA unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("PageSetupDlgA");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE BOOL WINAPI IsolationAwarePageSetupDlgW(LPPAGESETUPDLGW unnamed1)
{
    BOOL fResult = FALSE;
    typedef BOOL (WINAPI* PFN)(LPPAGESETUPDLGW unnamed1);
    static PFN s_pfn;
    ULONG_PTR  ulpCookie = 0;
    const BOOL fActivateActCtxSuccess = IsolationAwarePrivateT_SqbjaYRiRY || IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
    if (!fActivateActCtxSuccess)
        return fResult;
    __try
    {
        if (s_pfn == NULL)
        {
            s_pfn = (PFN)CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY("PageSetupDlgW");
            if (s_pfn == NULL)
                __leave;
        }
        fResult = s_pfn(unnamed1);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            const BOOL fPreserveLastError = (fResult == FALSE);
            const DWORD dwLastError = fPreserveLastError ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (fPreserveLastError)
                SetLastError(dwLastError);
        }
    }
    return fResult;
}

ISOLATION_AWARE_INLINE FARPROC WINAPI CommdlgIsolationAwarePrivatetRgCebPnQQeRff_pbZQYTQP_QYY(LPCSTR pszProcName)
/* This function is shared by the other stubs in this header. */
{
    FARPROC proc = NULL;
    static HMODULE s_module;
    BOOL fActivateActCtxSuccess = FALSE;
    ULONG_PTR ulpCookie = 0;
    const static IsolationAwarePrivatepBAFGnAG_zBqHyr_vAsB
        c = { IsolationAwarePrivatezlybNQyVOeNeln, IsolationAwarePrivatezlybNQyVOeNelJ, "Comdlg32.dll", L"Comdlg32.dll" };
    static IsolationAwarePrivatezHGnoyr_zBqHyr_vAsB m;

    __try
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY)
        {
            fActivateActCtxSuccess = IsolationAwarePrivatenPgViNgRzlnPgpgk(&ulpCookie);
            if (!fActivateActCtxSuccess)
                __leave;
        }
        proc = IsolationAwarePrivatezltRgCebPnQQeRff(&c, &m, pszProcName);
    }
    __finally
    {
        if (!IsolationAwarePrivateT_SqbjaYRiRY && fActivateActCtxSuccess)
        {
            const DWORD dwLastError = (proc == NULL) ? GetLastError() : NO_ERROR;
            (void)IsolationAwareDeactivateActCtx(0, ulpCookie);
            if (proc == NULL)
                SetLastError(dwLastError);
        }
    }
    return proc;
}

#endif /* ISOLATION_AWARE_USE_STATIC_LIBRARY */

#define ChooseColorA IsolationAwareChooseColorA
#define ChooseColorW IsolationAwareChooseColorW
#define ChooseFontA IsolationAwareChooseFontA
#define ChooseFontW IsolationAwareChooseFontW
#define CommDlgExtendedError IsolationAwareCommDlgExtendedError
#define FindTextA IsolationAwareFindTextA
#define FindTextW IsolationAwareFindTextW
#define GetFileTitleA IsolationAwareGetFileTitleA
#define GetFileTitleW IsolationAwareGetFileTitleW
#define GetOpenFileNameA IsolationAwareGetOpenFileNameA
#define GetOpenFileNameW IsolationAwareGetOpenFileNameW
#define GetSaveFileNameA IsolationAwareGetSaveFileNameA
#define GetSaveFileNameW IsolationAwareGetSaveFileNameW
#define PageSetupDlgA IsolationAwarePageSetupDlgA
#define PageSetupDlgW IsolationAwarePageSetupDlgW
#define PrintDlgA IsolationAwarePrintDlgA
#define PrintDlgExA IsolationAwarePrintDlgExA
#define PrintDlgExW IsolationAwarePrintDlgExW
#define PrintDlgW IsolationAwarePrintDlgW
#define ReplaceTextA IsolationAwareReplaceTextA
#define ReplaceTextW IsolationAwareReplaceTextW

#endif /* ISOLATION_AWARE_ENABLED */
#endif /* RC */


#if defined(__cplusplus)
} /* __cplusplus */
#endif
