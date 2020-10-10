//*********************************************************************
//*                  Microsoft Windows                               **
//*        Copyright (c) Microsoft Corporation. All rights reserved. **
//*********************************************************************
#pragma once

#ifndef _RATINGS_H_
#define _RATINGS_H_

#include <winerror.h>
#include <shlwapi.h>

STDAPI RatingEnable(HWND hwndParent, LPCSTR pszUsername, BOOL fEnable);
STDAPI RatingCheckUserAccess(__opt LPCSTR pszUsername, __opt LPCSTR pszURL, __opt LPCSTR pszRatingInfo,
    __in_bcount(cbData) __opt LPBYTE pData, DWORD cbData, __out __opt void **ppRatingDetails);
STDAPI RatingAccessDeniedDialog(HWND hDlg, __opt LPCSTR pszUsername, LPCSTR pszContentDescription,\
    __out void *pRatingDetails);
STDAPI RatingAccessDeniedDialog2(HWND hDlg, __opt LPCSTR pszUsername, __out void *pRatingDetails);
STDAPI RatingFreeDetails(__in __opt void *pRatingDetails);
STDAPI RatingObtainCancel(HANDLE hRatingObtainQuery);
STDAPI RatingObtainQuery(LPCSTR pszTargetUrl, DWORD dwUserData,
    void (*fCallback)(DWORD dwUserData, HRESULT hr, LPCSTR pszRating, void *lpvRatingDetails),
    __out __opt HANDLE *phRatingObtainQuery);
STDAPI RatingSetupUI(HWND hDlg, LPCSTR pszUsername);
#ifdef _INC_COMMCTRL
STDAPI RatingAddPropertyPage(PROPSHEETHEADER *ppsh);
#endif

STDAPI RatingEnabledQuery();
STDAPI RatingInit();
STDAPI_(void) RatingTerm();

// A way to check if ratings are installed. We still need to calling
// ratings dll to find out for sure but this allows us to delay load ratings.
_inline BOOL IS_RATINGS_ENABLED()
{
    TCHAR szSup[200];
    DWORD dwType;
    DWORD cbSize = sizeof(szSup);

    return (SHGetValue(HKEY_LOCAL_MACHINE,
                       TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Ratings"),
                       TEXT("Key"),
                       &dwType, &szSup, &cbSize) == ERROR_SUCCESS);
}

#endif
// _RATINGS_H_

