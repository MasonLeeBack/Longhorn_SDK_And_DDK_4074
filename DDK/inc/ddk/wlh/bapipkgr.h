//////////////////////////////////////////////////////////////////////////////
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996 - 2002
//
// File:            bapipkgr.h
//
// Dependencies:    bio.h
//
//////////////////////////////////////////////////////////////////////////////
//
// Contents:
//
//  Contains routines for packing and unpacking common biometric item formats.
//
// History:
//
//  07-18-2002      patmasse    creation
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
// Exported Functions ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

VOID WINAPI bapipkgrPackSampleInfo(
    IN  DWORD dwMaxAge,
    IN  DWORD dwFlags,
    OUT PBYTE pbSampleInfo);

VOID WINAPI bapipkgrUnpackSampleInfo(
    IN  PBYTE pbSampleInfo,
    OUT PBIO_SAMPLEINFO pSampleInfo);

VOID WINAPI bapipkgrPackSResult(
    IN  DWORD dwResult,
    IN  DWORD dwAge,
    OUT PBYTE pbSResult);

VOID WINAPI bapipkgrUnpackSResult(
    IN  PBYTE pbSResult,
    OUT PBIO_SRESULT pSResult);

VOID WINAPI bapipkgrPackEPResult(
    IN  DWORD dwResult,
    IN  INT32 iMoveX,
    IN  INT32 iMoveY,
    IN  INT32 iMoveZ,
    IN  INT32 iRotateXY,
    IN  INT32 iRotateXZ,
    IN  INT32 iRotateYZ,
    IN  INT32 iIntensity,
    OUT PBYTE pbEPResult);

VOID WINAPI bapipkgrUnpackEPResult(
    IN  PBYTE pbEPResult,
    OUT PBIO_EPRESULT pEPResult);

VOID WINAPI bapipkgrPackAPResult(
    IN  DWORD dwResult,
    IN  INT32 iMoveX,
    IN  INT32 iMoveY,
    IN  INT32 iMoveZ,
    IN  INT32 iRotateXY,
    IN  INT32 iRotateXZ,
    IN  INT32 iRotateYZ,
    IN  INT32 iIntensity,
    OUT PBYTE pbAPResult);

VOID WINAPI bapipkgrUnpackAPResult(
    IN  PBYTE pbAPResult,
    OUT PBIO_APRESULT pAPResult);

VOID WINAPI bapipkgrPackXPResult(
    IN  DWORD dwResult,
    OUT PBYTE pbXPResult);

VOID WINAPI bapipkgrUnpackXPResult(
    IN  PBYTE pbXPResult,
    OUT PBIO_XPRESULT pXPResult);

VOID WINAPI bapipkgrPackVResult(
    IN DWORD dwResult,
    OUT PBYTE pbVResult);

VOID WINAPI bapipkgrUnpackVResult(
    IN PBYTE pbVResult,
    OUT PBIO_VRESULT pVResult);

VOID WINAPI bapipkgrPackIResult(
    IN  DWORD dwResult,
    IN  DWORD dwNumIdxs,
    IN  PDWORD rgdwIdxs,
    OUT PBYTE pbIResult);

BOOL WINAPI bapipkgrUnpackIResult(
    IN  DWORD cbIResult,
    IN  PBYTE pbIResult,
    OUT PDWORD pcbIResult,
    OUT PBIO_IRESULT pIResult);

VOID WINAPI bapipkgrPackRect(
    IN  PRECT pRect,
    OUT PBYTE pbRect);

VOID WINAPI bapipkgrUnpackRect(
    IN  PBYTE pbRect,
    OUT PRECT pRect);

VOID WINAPI bapipkgrPackDrawInfo(
    IN  HDC hDC,
    IN  PRECT pRect,
    IN  DWORD dwFlags,
    OUT PBYTE pbDrawInfo);

VOID WINAPI bapipkgrUnpackDrawInfo(
    IN  PBYTE pbDrawInfo,
    OUT PBIO_DRAWINFO pDrawInfo);

#ifdef __cplusplus
} // Matches extern "C" above
#endif

//////////////////////////////////////////////////////////////////////////////
// End Content ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


