/***
*stdarg.h - defines ANSI-style macros for variable argument functions
*
*       Copyright (c) 1985-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file defines ANSI-style macros for accessing arguments
*       of functions which take a variable number of arguments.
*       [ANSI]
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifndef _INC_STDARG
#define _INC_STDARG

#if !defined (_WIN32)
#error ERROR: Only Win32 target supported!
#endif  /* !defined (_WIN32) */

#ifndef _CRTBLD
/* This version of the header files is NOT for user programs.
 * It is intended for use when building the C runtimes ONLY.
 * The version intended for public use will not have this message.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#ifdef _MSC_VER
/*
 * Currently, all MS C compilers for Win32 platforms default to 8 byte
 * alignment.
 */
#pragma pack(push,8)
#endif  /* _MSC_VER */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef _INTERNAL_IFSTRIP_
#include <cruntime.h>
#endif  /* _INTERNAL_IFSTRIP_ */

#if !defined (_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#define _W64 __w64
#else  /* !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300 */
#define _W64
#endif  /* !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300 */
#endif  /* !defined (_W64) */

#ifndef _UINTPTR_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64    uintptr_t;
#else  /* _WIN64 */
typedef _W64 unsigned int   uintptr_t;
#endif  /* _WIN64 */
#define _UINTPTR_T_DEFINED
#endif  /* _UINTPTR_T_DEFINED */

#ifndef _VA_LIST_DEFINED
typedef char *  va_list;
#define _VA_LIST_DEFINED
#endif  /* _VA_LIST_DEFINED */

#ifdef __cplusplus
#define _ADDRESSOF(v)   ( &reinterpret_cast<const char &>(v) )
#else  /* __cplusplus */
#define _ADDRESSOF(v)   ( &(v) )
#endif  /* __cplusplus */

#if defined (_M_IA64)
#define _VA_ALIGN       8
#define _SLOTSIZEOF(t)   ( (sizeof(t) + _VA_ALIGN - 1) & ~(_VA_ALIGN - 1) )

#define _VA_STRUCT_ALIGN  16

#define _ALIGNOF(ap) ((((ap)+_VA_STRUCT_ALIGN - 1) & ~(_VA_STRUCT_ALIGN -1)) \
        - (ap))
#define _APALIGN(t,ap)  (__alignof(t) > 8 ? _ALIGNOF((uintptr_t) ap) : 0)

#else  /* defined (_M_IA64) */
#define _SLOTSIZEOF(t)   (sizeof(t))
#define _APALIGN(t,ap)  (__builtin_alignof(t))
#endif  /* defined (_M_IA64) */

#if defined (_M_CEE)

extern void __cdecl __va_start(va_list*, ...);
extern void * __cdecl __va_arg(va_list*, ...);
extern void __cdecl __va_end(va_list*);

#define va_start(ap,v)  ( __va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), \
                                __builtin_alignof(v), _ADDRESSOF(v)) )
#define va_arg(ap,t)    ( *(t *)__va_arg(&ap, _SLOTSIZEOF(t), \
                                _APALIGN(t,ap), (t *)0) )
#define va_end(ap)      ( __va_end(&ap) )

#elif defined (_M_IX86)

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

#elif defined (_M_IA64)

#ifdef __cplusplus
extern void __cdecl __va_start(va_list*, ...);
#define va_start(ap,v)  ( __va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), \
                          _ADDRESSOF(v)) )
#else  /* __cplusplus */
#define va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _SLOTSIZEOF(v) )
#endif  /* __cplusplus */

#define va_arg(ap,t)    (*(t *)((ap += _SLOTSIZEOF(t)+ _APALIGN(t,ap)) \
                                                     -_SLOTSIZEOF(t)))

#define va_end(ap)      ( ap = (va_list)0 )

#elif defined (_M_AMD64)


extern void __cdecl __va_start(va_list *, ...);

#define va_start(ap, x) ( __va_start(&ap, x) )
#define va_arg(ap, t)   \
    ( ( sizeof(t) > sizeof(__int64) || ( sizeof(t) & (sizeof(t) - 1) ) != 0 ) \
        ? **(t **)( ( ap += sizeof(__int64) ) - sizeof(__int64) ) \
        :  *(t  *)( ( ap += sizeof(__int64) ) - sizeof(__int64) ) )
#define va_end(ap)      ( ap = (va_list)0 )

#else  /* defined (_M_AMD64) */

/* A guess at the proper definitions for other platforms */

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

#endif  /* defined (_M_AMD64) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#ifdef _MSC_VER
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_STDARG */
