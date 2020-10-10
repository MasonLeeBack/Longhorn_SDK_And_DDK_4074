/***
*dllsupp.c - Definitions of public constants
*
*       Copyright (c) 1992-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Provides definitions for public constants (absolutes) that are
*       'normally' defined in objects in the C library, but must be defined
*       here for clients of crtdll.dll & msvcrt*.dll.  These constants are:
*
*                           _fltused
*
*******************************************************************************/

int _fltused = 0x9875;
