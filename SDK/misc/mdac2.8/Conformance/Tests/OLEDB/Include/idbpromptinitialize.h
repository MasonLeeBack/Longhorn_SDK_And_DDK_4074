//--------------------------------------------------------------------
// Microsoft OLE DB Test
//
// Copyright 1998-2000 Microsoft Corporation.  
//
// @doc
//
// @module IDBPromptInitialize_DB.H | idbprmpt header file for test modules.
//
//
// @rev 01 | 07-09-98 | Microsoft | Created
//

#ifndef _idbprmpt_H_
#define _idbprmpt_H_

#include "privlib.h"

//-----------------------------------------------------------------------------
// String constants
//-----------------------------------------------------------------------------


// external functions
WINOLEAPI CoCreateInstanceEx(REFCLSID, IUnknown *, DWORD, COSERVERINFO *, ULONG, MULTI_QI *);


// constants
const int		nMaxProv		= 200;	// maximum number of providers
const ULONG		cMaxName		= 300;	// maximum name length


#endif 	//_idbprmpt_H_
