/*++ BUILD Version: 0104    // Increment this if a change has global effects

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    ndis.h

Abstract:

    This module defines the structures, macros, and functions available
    to NDIS drivers.

Revision History:

--*/

#if !defined(_NDIS_)
#define _NDIS_

#if !defined(NDIS_WDM)
#define NDIS_WDM        0
#endif

//
// If we're building a miniport on x86, set BINARY_COMPATIBLE so that
// we don't use functions that aren't available on Windows 9x.
//

#if !defined(BINARY_COMPATIBLE)
#if defined(NDIS_MINIPORT_DRIVER) && defined(_M_IX86)
#define BINARY_COMPATIBLE 1
#else
#define BINARY_COMPATIBLE 0
#endif
#endif

#if !defined(_M_IX86)
#undef BINARY_COMPATIBLE
#define BINARY_COMPATIBLE 0
#endif

//
// BEGIN INTERNAL DEFINITIONS
//

//
// BINARY_COMPATIBLE = 1 and NDIS_WDM = 1 then use wdm.h
// BINARY_COMPATIBLE = 1 and NDIS_WDM = 0 then use ndis.h only
// BINARY_COMPATIBLE = 0 and NDIS_WDM = 1 then use ntddk.h
// BINARY_COMPATIBLE = 0 and NDIS_WDM = 0 then use ntddk.h
//

#if (BINARY_COMPATIBLE && !NDIS_WDM)

//
// BINARY_COMPATIBLE = 1 and NDIS_WDM = 0 then use ndis.h only
//
// The following internal definitions are included here in order to allow
// the exported NDIS structures, macros, and functions to compile.  They
// must not be used directly by miniport drivers.
//

#define _NTDDK_

#include <ctype.h>  

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef NOTHING
#define NOTHING
#endif

#ifndef CRITICAL
#define CRITICAL
#endif

#ifndef ANYSIZE_ARRAY
#define ANYSIZE_ARRAY 1       // winnt
#endif

// begin_winnt

#include <specstrings.h>


#if defined(_M_MRX000) && !(defined(MIDL_PASS) || defined(RC_INVOKED)) && defined(ENABLE_RESTRICTED)
#define RESTRICTED_POINTER __restrict
#else
#define RESTRICTED_POINTER
#endif

#if defined(_M_MRX000) || defined(_M_ALPHA) || defined(_M_PPC) || defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#if defined(_WIN64)
#define UNALIGNED64 __unaligned
#else
#define UNALIGNED64
#endif
#else
#define UNALIGNED
#define UNALIGNED64
#endif

#ifndef MAX_NATURAL_ALIGNMENT
#if defined(_WIN64) || defined(_M_ALPHA)
#define MAX_NATURAL_ALIGNMENT sizeof(ULONGLONG)
#define MEMORY_ALLOCATION_ALIGNMENT 16
#else
#define MAX_NATURAL_ALIGNMENT sizeof(ULONG)
#define MEMORY_ALLOCATION_ALIGNMENT 8
#endif
#endif

//
// TYPE_ALIGNMENT will return the alignment requirements of a given type for
// the current platform.
//

#ifdef __cplusplus
#if _MSC_VER >= 1300
#define TYPE_ALIGNMENT( t ) __alignof(t)
#endif
#else
#define TYPE_ALIGNMENT( t ) \
    FIELD_OFFSET( struct { char x; t test; }, test )
#endif

#ifndef PROBE_ALIGNMENT
#if defined(_WIN64)

#define PROBE_ALIGNMENT( _s ) (TYPE_ALIGNMENT( _s ) > TYPE_ALIGNMENT( ULONG ) ? \
                               TYPE_ALIGNMENT( _s ) : TYPE_ALIGNMENT( ULONG ))

#define PROBE_ALIGNMENT32( _s ) TYPE_ALIGNMENT( ULONG )

#else

#define PROBE_ALIGNMENT( _s ) TYPE_ALIGNMENT( ULONG )

#endif
#endif

#if !defined(SORTPP_PASS)

//
// C_ASSERT() can be used to perform many compile-time assertions:
//            type sizes, field offsets, etc.
//
// An assertion failure results in error C2118: negative subscript.
//

#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]

#else

#define C_ASSERT(e) /* nothing */

#endif

#if !defined(_MAC) && (defined(_M_MRX000) || defined(_M_AMD64) || defined(_M_IA64)) && (_MSC_VER >= 1100) && !(defined(MIDL_PASS) || defined(RC_INVOKED))
#define POINTER_64 __ptr64
typedef unsigned __int64 POINTER_64_INT;
#if defined(_WIN64)
#define POINTER_32 __ptr32
#else
#define POINTER_32
#endif
#else
#if defined(_MAC) && defined(_MAC_INT_64)
#define POINTER_64 __ptr64
typedef unsigned __int64 POINTER_64_INT;
#else
#define POINTER_64
typedef unsigned long POINTER_64_INT;
#endif
#define POINTER_32
#endif

#if defined(_IA64_) || defined(_AMD64_)
#define FIRMWARE_PTR
#else
#define FIRMWARE_PTR POINTER_32
#endif

#include <basetsd.h>

// end_winnt

#ifndef CONST
#define CONST               const
#endif

// begin_winnt

#if (defined(_M_IX86) || defined(_M_IA64) || defined(_M_AMD64)) && !defined(MIDL_PASS)
#define DECLSPEC_IMPORT __declspec(dllimport)
#else
#define DECLSPEC_IMPORT
#endif

#ifndef DECLSPEC_NORETURN
#if (_MSC_VER >= 1200) && !defined(MIDL_PASS)
#define DECLSPEC_NORETURN   __declspec(noreturn)
#else
#define DECLSPEC_NORETURN
#endif
#endif

#ifndef DECLSPEC_ALIGN
#if (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#define DECLSPEC_ALIGN(x)   __declspec(align(x))
#else
#define DECLSPEC_ALIGN(x)
#endif
#endif

#ifndef DECLSPEC_CACHEALIGN
#define DECLSPEC_CACHEALIGN DECLSPEC_ALIGN(128)
#endif

#ifndef DECLSPEC_UUID
#if (_MSC_VER >= 1100) && defined (__cplusplus)
#define DECLSPEC_UUID(x)    __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif
#endif

#ifndef DECLSPEC_NOVTABLE
#if (_MSC_VER >= 1100) && defined(__cplusplus)
#define DECLSPEC_NOVTABLE   __declspec(novtable)
#else
#define DECLSPEC_NOVTABLE
#endif
#endif

#ifndef DECLSPEC_SELECTANY
#if (_MSC_VER >= 1100)
#define DECLSPEC_SELECTANY  __declspec(selectany)
#else
#define DECLSPEC_SELECTANY
#endif
#endif

#ifndef NOP_FUNCTION
#if (_MSC_VER >= 1210)
#define NOP_FUNCTION __noop
#else
#define NOP_FUNCTION (void)0
#endif
#endif

#ifndef DECLSPEC_ADDRSAFE
#if (_MSC_VER >= 1200) && (defined(_M_ALPHA) || defined(_M_AXP64))
#define DECLSPEC_ADDRSAFE  __declspec(address_safe)
#else
#define DECLSPEC_ADDRSAFE
#endif
#endif

#ifndef DECLSPEC_NOINLINE
#if (_MSC_VER >= 1300)
#define DECLSPEC_NOINLINE  __declspec(noinline)
#else
#define DECLSPEC_NOINLINE
#endif
#endif

#ifndef FORCEINLINE
#if (_MSC_VER >= 1200)
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __inline
#endif
#endif

#ifndef DECLSPEC_DEPRECATED
#if (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#define DECLSPEC_DEPRECATED   __declspec(deprecated)
#define DEPRECATE_SUPPORTED
#else
#define DECLSPEC_DEPRECATED
#undef  DEPRECATE_SUPPORTED
#endif
#endif

#ifdef DEPRECATE_DDK_FUNCTIONS
#if defined(_NTDDK_) || defined(_WDMDDK_)
#define DECLSPEC_DEPRECATED_DDK DECLSPEC_DEPRECATED
#ifdef DEPRECATE_SUPPORTED
#define PRAGMA_DEPRECATED_DDK 1
#endif
#else
#define DECLSPEC_DEPRECATED_DDK
#define PRAGMA_DEPRECATED_DDK 1
#endif
#else
#define DECLSPEC_DEPRECATED_DDK
#define PRAGMA_DEPRECATED_DDK 0
#endif


//
// Void
//

typedef void *PVOID;
typedef void * POINTER_64 PVOID64;

// end_winnt

#if defined(_M_IX86)
#define FASTCALL _fastcall
#else
#define FASTCALL
#endif


#if ((_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)) && !defined(_M_AMD64)
#define NTAPI __stdcall
#else
#define _cdecl
#define NTAPI
#endif

//
// Define API decoration for direct importing system DLL references.
//

#if !defined(_NTSYSTEM_)
#define NTSYSAPI     DECLSPEC_IMPORT
#define NTSYSCALLAPI DECLSPEC_IMPORT
#else
#define NTSYSAPI
#if defined(_NTDLLBUILD_)
#define NTSYSCALLAPI
#else
#define NTSYSCALLAPI DECLSPEC_ADDRSAFE
#endif

#endif


//
// Basics
//

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#if !defined(MIDL_PASS)
typedef int INT;
#endif
#endif

//
// UNICODE (Wide Character) types
//

#ifndef _MAC
typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
#else
// some Macintosh compilers don't define wchar_t in a convenient location, or define it as a char
typedef unsigned short WCHAR;    // wc,   16-bit UNICODE character
#endif

typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;
typedef WCHAR UNALIGNED *LPUWSTR, *PUWSTR;

typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef CONST WCHAR UNALIGNED *LPCUWSTR, *PCUWSTR;

//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

#if _WIN32_WINNT >= 0x0600

//
//  UCS (Universal Character Set) types
//

typedef unsigned __int32 UCSCHAR;

//
//  Even pre-Unicode agreement, UCS values are always in the
//  range U+00000000 to U+7FFFFFFF, so we'll pick an obvious
//  value.

#define UCSCHAR_INVALID_CHARACTER (0xffffffff)

#define MIN_UCSCHAR (0)

//
//  We'll assume here that the ISO-10646 / Unicode agreement
//  not to assign code points after U+0010FFFF holds so that
//  we don't have to have separate "UCSCHAR" and "UNICODECHAR"
//  types.
//

#define MAX_UCSCHAR (0x0010FFFF)

typedef UCSCHAR *PUCSCHAR;
typedef const UCSCHAR *PCUCSCHAR;

typedef UCSCHAR *PUCSSTR;
typedef UCSCHAR UNALIGNED *PUUCSSTR;

typedef const UCSCHAR *PCUCSSTR;
typedef const UCSCHAR UNALIGNED *PCUUCSSTR;

#endif

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     // r_winnt

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TUCHAR, *PTUCHAR;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR PCTSTR, LPCTSTR;
typedef LPUWSTR PUTSTR, LPUTSTR;
typedef LPCUWSTR PCUTSTR, LPCUTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote      // r_winnt

#else   /* UNICODE */               // r_winnt

#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TUCHAR, *PTUCHAR;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR, PUTSTR, LPUTSTR;
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
#define __TEXT(quote) quote         // r_winnt

#endif /* UNICODE */                // r_winnt
#define TEXT(quote) __TEXT(quote)   // r_winnt


// end_winnt

typedef double DOUBLE;

typedef struct _QUAD {              // QUAD is for those times we want
    double  DoNotUseThisField;      // an 8 byte aligned 8 byte long structure
} QUAD;                             // which is NOT really a floating point
                                    // number.  Use DOUBLE if you want an FP
                                    // number.

//
// Pointer to Basics
//

typedef SHORT *PSHORT;  // winnt
typedef LONG *PLONG;    // winnt
typedef QUAD *PQUAD;

//
// Unsigned Basics
//

// Tell windef.h that some types are already defined.
#define BASETYPES

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef QUAD UQUAD;

//
// Pointer to Unsigned Basics
//

typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef ULONG *PULONG;
typedef UQUAD *PUQUAD;

//
// Signed characters
//

typedef signed char SCHAR;
typedef SCHAR *PSCHAR;

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif

//
// Handle to an Object
//

// begin_winnt

#ifdef STRICT
typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

//
// Flag (bit) fields
//

typedef UCHAR  FCHAR;
typedef USHORT FSHORT;
typedef ULONG  FLONG;

// Component Object Model defines, and macros

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef LONG HRESULT;

#endif // !_HRESULT_DEFINED

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

#if defined(_WIN32) || defined(_MPPC_)

// Win32 doesn't support __export

#ifdef _68K_
#define STDMETHODCALLTYPE       __cdecl
#else
#define STDMETHODCALLTYPE       __stdcall
#endif
#define STDMETHODVCALLTYPE      __cdecl

#define STDAPICALLTYPE          __stdcall
#define STDAPIVCALLTYPE         __cdecl

#else

#define STDMETHODCALLTYPE       __export __stdcall
#define STDMETHODVCALLTYPE      __export __cdecl

#define STDAPICALLTYPE          __export __stdcall
#define STDAPIVCALLTYPE         __export __cdecl

#endif


#define STDAPI                  EXTERN_C HRESULT STDAPICALLTYPE
#define STDAPI_(type)           EXTERN_C type STDAPICALLTYPE

#define STDMETHODIMP            HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE

#define STDOVERRIDEMETHODIMP        __override STDMETHODIMP
#define STDOVERRIDEMETHODIMP_(type) __override STDMETHODIMP_(type)

#define IFACEMETHODIMP          __override STDMETHODIMP
#define IFACEMETHODIMP_(type)   __override STDMETHODIMP_(type)

// The 'V' versions allow Variable Argument lists.

#define STDAPIV                 EXTERN_C HRESULT STDAPIVCALLTYPE
#define STDAPIV_(type)          EXTERN_C type STDAPIVCALLTYPE

#define STDMETHODIMPV           HRESULT STDMETHODVCALLTYPE
#define STDMETHODIMPV_(type)    type STDMETHODVCALLTYPE

#define STDOVERRIDEMETHODIMPV        __override STDMETHODIMPV
#define STDOVERRIDEMETHODIMPV_(type) __override STDMETHODIMPV_(type)

#define IFACEMETHODIMPV          __override STDMETHODIMPV
#define IFACEMETHODIMPV_(type)   __override STDMETHODIMPV_(type)

// end_winnt


//
// Low order two bits of a handle are ignored by the system and available
// for use by application code as tag bits.  The remaining bits are opaque
// and used to store a serial number and table index.
//

#define OBJ_HANDLE_TAGBITS  0x00000003L

//
// Cardinal Data Types [0 - 2**N-2)
//

typedef char CCHAR;          // winnt
typedef short CSHORT;
typedef ULONG CLONG;

typedef CCHAR *PCCHAR;
typedef CSHORT *PCSHORT;
typedef CLONG *PCLONG;

//
// NTSTATUS
//

typedef LONG NTSTATUS;
/*lint -save -e624 */  // Don't complain about different typedefs.
typedef NTSTATUS *PNTSTATUS;
/*lint -restore */  // Resume checking for different typedefs.

//
//  Status values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

//
// Generic test for information on any status value.
//

#define NT_INFORMATION(Status) ((ULONG)(Status) >> 30 == 1)

//
// Generic test for warning on any status value.
//

#define NT_WARNING(Status) ((ULONG)(Status) >> 30 == 2)

//
// Generic test for error on any status value.
//

#define NT_ERROR(Status) ((ULONG)(Status) >> 30 == 3)

// end_windbgkd
// begin_winnt
#define APPLICATION_ERROR_MASK       0x20000000
#define ERROR_SEVERITY_SUCCESS       0x00000000
#define ERROR_SEVERITY_INFORMATIONAL 0x40000000
#define ERROR_SEVERITY_WARNING       0x80000000
#define ERROR_SEVERITY_ERROR         0xC0000000
// end_winnt

#ifndef __SECSTATUS_DEFINED__
typedef long SECURITY_STATUS;
#define __SECSTATUS_DEFINED__
#endif



//
// __int64 is only supported by 2.0 and later midl.
// __midl is set by the 2.0 midl and not by 1.0 midl.
//

#define _ULONGLONG_
#if (!defined (_MAC) && (!defined(MIDL_PASS) || defined(__midl)) && (!defined(_M_IX86) || (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64)))
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define MAXLONGLONG                      (0x7fffffffffffffff)
#define MINLONGLONG                      (0x8000000000000000i64)
#else

#if defined(_MAC) && defined(_MAC_INT_64)
typedef __int64 LONGLONG;
typedef unsigned __int64 ULONGLONG;

#define MAXLONGLONG                      (0x7fffffffffffffff)
#define MINLONGLONG                      (0x8000000000000000i64)
#else
typedef double LONGLONG;
typedef double ULONGLONG;
#endif //_MAC and int64

#endif

typedef LONGLONG *PLONGLONG;
typedef ULONGLONG *PULONGLONG;

// Update Sequence Number

typedef LONGLONG USN;

#ifndef _LARGE_INTEGER_DEFINED
#define _LARGE_INTEGER_DEFINED

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
    struct {
        ULONG LowPart;
        LONG HighPart;
    };
    struct {
        ULONG LowPart;
        LONG HighPart;
    } u;
#endif //MIDL_PASS
    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

#if defined(MIDL_PASS)
typedef struct _ULARGE_INTEGER {
#else // MIDL_PASS
typedef union _ULARGE_INTEGER {
    struct {
        ULONG LowPart;
        ULONG HighPart;
    };
    struct {
        ULONG LowPart;
        ULONG HighPart;
    } u;
#endif //MIDL_PASS
    ULONGLONG QuadPart;
} ULARGE_INTEGER;

typedef ULARGE_INTEGER *PULARGE_INTEGER;

#endif // _LARGE_INTEGER_DEFINED


//
// Physical address.
//

typedef LARGE_INTEGER PHYSICAL_ADDRESS, *PPHYSICAL_ADDRESS;

//
// Counted String
//

typedef USHORT RTL_STRING_LENGTH_TYPE;

typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength), length_is(Length) ]
#endif // MIDL_PASS
    PCHAR Buffer;
} STRING;
typedef STRING *PSTRING;

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef CONST STRING* PCOEM_STRING;

//
// CONSTCounted String
//

typedef struct _CSTRING {
    USHORT Length;
    USHORT MaximumLength;
    CONST char *Buffer;
} CSTRING;
typedef CSTRING *PCSTRING;
#define ANSI_NULL ((CHAR)0)     // winnt

typedef STRING CANSI_STRING;
typedef PSTRING PCANSI_STRING;

//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
#else // MIDL_PASS
    PWSTR  Buffer;
#endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
#define UNICODE_NULL ((WCHAR)0) // winnt

#if _WIN32_WINNT >= 0x0501

#define UNICODE_STRING_MAX_BYTES ((USHORT) 65534) // winnt
#define UNICODE_STRING_MAX_CHARS (32767) // winnt

#define DECLARE_CONST_UNICODE_STRING(_variablename, _string) \
const WCHAR _variablename ## _buffer[] = _string; \
const UNICODE_STRING _variablename = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWSTR) _variablename ## _buffer };

#endif // _WIN32_WINNT >= 0x0501


// begin_ntminiport begin_ntminitape

//
// Boolean
//

typedef UCHAR BOOLEAN;           // winnt
typedef BOOLEAN *PBOOLEAN;       // winnt

// end_ntminiport end_ntminitape

// begin_winnt
//
//  Doubly linked list structure.  Can be used as either a list head, or
//  as link words.
//

typedef struct _LIST_ENTRY {
   struct _LIST_ENTRY *Flink;
   struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, *RESTRICTED_POINTER PRLIST_ENTRY;

//
//  Singly linked list structure. Can be used as either a list head, or
//  as link words.
//

typedef struct _SINGLE_LIST_ENTRY {
    struct _SINGLE_LIST_ENTRY *Next;
} SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;

//
// Constants
//

#define FALSE   0
#define TRUE    1

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#define NULL64  0
#else
#define NULL    ((void *)0)
#define NULL64  ((void * POINTER_64)0)
#endif
#endif // NULL


#include <guiddef.h>

#ifndef __OBJECTID_DEFINED
#define __OBJECTID_DEFINED

typedef struct  _OBJECTID {     // size is 20
    GUID Lineage;
    ULONG Uniquifier;
} OBJECTID;
#endif // !_OBJECTID_DEFINED

//
// Determine if an argument is present by testing the value of the pointer
// to the argument value.
//

#define ARGUMENT_PRESENT(ArgumentPointer)    (\
    (CHAR *)((ULONG_PTR)(ArgumentPointer)) != (CHAR *)(NULL) )

// begin_winnt begin_ntminiport
//
// Calculate the byte offset of a field in a structure of type type.
//

#define FIELD_OFFSET(type, field)    ((LONG)(LONG_PTR)&(((type *)0)->field))

//
// Calculate the size of a field in a structure of type type, without
// knowing or stating the type of the field.
//
#define RTL_FIELD_SIZE(type, field) (sizeof(((type *)0)->field))

//
// Calculate the size of a structure of type type up through and
// including a field.
//
#define RTL_SIZEOF_THROUGH_FIELD(type, field) \
    (FIELD_OFFSET(type, field) + RTL_FIELD_SIZE(type, field))

//
//  RTL_CONTAINS_FIELD usage:
//
//      if (RTL_CONTAINS_FIELD(pBlock, pBlock->cbSize, dwMumble)) { // safe to use pBlock->dwMumble
//
#define RTL_CONTAINS_FIELD(Struct, Size, Field) \
    ( (((PCHAR)(&(Struct)->Field)) + sizeof((Struct)->Field)) <= (((PCHAR)(Struct))+(Size)) )

//
// Return the number of elements in a statically sized array.
//   ULONG Buffer[100];
//   RTL_NUMBER_OF(Buffer) == 100
// This is also popularly known as: NUMBER_OF, ARRSIZE, _countof, NELEM, etc.
//
#define RTL_NUMBER_OF_V1(A) (sizeof(A)/sizeof((A)[0]))

#if defined(__cplusplus) && \
    !defined(MIDL_PASS) && \
    !defined(RC_INVOKED) && \
    (_MSC_FULL_VER >= 13009466) && \
    (_WIN32_WINNT >= 0x0600) && \
    !defined(SORTPP_PASS)
//
// RtlpNumberOf is a function that takes a reference to an array of N Ts.
//
// typedef T array_of_T[N];
// typedef array_of_T & reference_to_array_of_T;
//
// RtlpNumberOf returns a reference to an array of N chars.
//
// typedef char array_of_char[N];
// typedef T3 & reference_to_array_of_char;
//
// sizeof(array_of_char) == N
// sizeof(reference_to_array_of_char) == N
//
// reference_to_array_of_char RtlpNumberOf(reference_to_array_of_T);
//
// We never even call RtlpNumberOf, we just take the size of its return type.
// We do not even implement RtlpNumberOf, we just decare it.
//
// Attempts to pass pointers instead of arrays to this macro result in compile time errors.
// That is the point.
//
extern "C++" // templates cannot be declared to have 'C' linkage
template <typename T, size_t N>
char (*RtlpNumberOf( UNALIGNED T (&)[N] ))[N];

#define RTL_NUMBER_OF_V2(A) (sizeof(*RtlpNumberOf(A)))

//
// This does not work with:
//
// void Foo()
// {
//    struct { int x; } y[2] = {{0},{1}};
//    RTL_NUMBER_OF_V2(y); // illegal use of anonymous local type in template instantiation
// }
//
// You must instead do:
//
// struct Foo1;
//
// void Foo()
// {
//    struct ::Foo1 { int x; } y[2] = {{0},{1}};
//    RTL_NUMBER_OF_V2(y);
// }
//

#else
#define RTL_NUMBER_OF_V2(A) RTL_NUMBER_OF_V1(A)
#endif

#ifdef ENABLE_RTL_NUMBER_OF_V2
#define RTL_NUMBER_OF(A) RTL_NUMBER_OF_V2(A)
#else
#define RTL_NUMBER_OF(A) RTL_NUMBER_OF_V1(A)
#endif


#if _WIN32_WINNT >= 0x0600
//
// ARRAYSIZE is more readable version of RTL_NUMBER_OF_V2, and uses
// it regardless of ENABLE_RTL_NUMBER_OF_V2
//
// _ARRAYSIZE is a version useful for anonymous types
//
#define ARRAYSIZE(A)    RTL_NUMBER_OF_V2(A)
#define _ARRAYSIZE(A)   RTL_NUMBER_OF_V1(A)
#endif

//
// An expression that yields the type of a field in a struct.
//
#define RTL_FIELD_TYPE(type, field) (((type*)0)->field)

// RTL_ to avoid collisions in the global namespace.
//
// Given typedef struct _FOO { BYTE Bar[123]; } FOO;
// RTL_NUMBER_OF_FIELD(FOO, Bar) == 123
//
#define RTL_NUMBER_OF_FIELD(type, field) (RTL_NUMBER_OF(RTL_FIELD_TYPE(type, field)))

//
// eg:
// typedef struct FOO {
//   ULONG Integer;
//   PVOID Pointer;
// } FOO;
//
// RTL_PADDING_BETWEEN_FIELDS(FOO, Integer, Pointer) == 0 for Win32, 4 for Win64
//
#define RTL_PADDING_BETWEEN_FIELDS(T, F1, F2) \
    ((FIELD_OFFSET(T, F2) > FIELD_OFFSET(T, F1)) \
        ? (FIELD_OFFSET(T, F2) - FIELD_OFFSET(T, F1) - RTL_FIELD_SIZE(T, F1)) \
        : (FIELD_OFFSET(T, F1) - FIELD_OFFSET(T, F2) - RTL_FIELD_SIZE(T, F2)))

// RTL_ to avoid collisions in the global namespace.
#if defined(__cplusplus)
#define RTL_CONST_CAST(type) const_cast<type>
#else
#define RTL_CONST_CAST(type) (type)
#endif

// end_winnt

// RTL_ to avoid collisions in the global namespace.
#if defined(__cplusplus)
#define RTL_STATIC_CAST(type) static_cast<type>
#else
#define RTL_STATIC_CAST(type) (type)
#endif

//
// RTL_SIZEOF is like sizeof, but the type is SIZE_T instead of size_t.
//
// SIZE_T and size_t are not the same type.
//
// This makes a difference for template parameter deduction in functions like
// template <typename T> NTSTATUS AddWithOverflowCheck(const T& in1, const T& in2, T& out);
//
// SIZE_T a,b;
// AddWithOverflowCheck(a, sizeof(...), b);
// vs.
// AddWithOverflowCheck(a, RTL_SIZEOF(...), b);
// 
#define RTL_SIZEOF(x) (RTL_STATIC_CAST<SIZE_T>(sizeof(x)))

//
// This works "generically" for Unicode and Ansi/Oem strings.
// Usage:
//   const static UNICODE_STRING FooU = RTL_CONSTANT_STRING(L"Foo");
//   const static         STRING Foo  = RTL_CONSTANT_STRING( "Foo");
// instead of the slower:
//   UNICODE_STRING FooU;
//           STRING Foo;
//   RtlInitUnicodeString(&FooU, L"Foo");
//          RtlInitString(&Foo ,  "Foo");
//
#define RTL_CONSTANT_STRING(s) { sizeof( s ) - sizeof( (s)[0] ), sizeof( s ), s }
#define RTL_CONSTANT_STRING_WITH_CONST_CAST(s) { sizeof( s ) - sizeof( (s)[0] ), sizeof( s ), RTL_CONST_CAST(PWSTR)(s) }
// begin_winnt

// like sizeof
// usually this would be * CHAR_BIT, but we don't necessarily have #include <limits.h>
#define RTL_BITS_OF(sizeOfArg) (sizeof(sizeOfArg) * 8)

#define RTL_BITS_OF_FIELD(type, field) (RTL_BITS_OF(RTL_FIELD_TYPE(type, field)))

//
// Calculate the address of the base of the structure given its type, and an
// address of a field within the structure.
//

#define CONTAINING_RECORD(address, type, field) ((type *)( \
                                                  (PCHAR)(address) - \
                                                  (ULONG_PTR)(&((type *)0)->field)))


//
// Interrupt Request Level (IRQL)
//

typedef UCHAR KIRQL;

typedef KIRQL *PKIRQL;


//
// Macros used to eliminate compiler warning generated when formal
// parameters or local variables are not declared.
//
// Use DBG_UNREFERENCED_PARAMETER() when a parameter is not yet
// referenced but will be once the module is completely developed.
//
// Use DBG_UNREFERENCED_LOCAL_VARIABLE() when a local variable is not yet
// referenced but will be once the module is completely developed.
//
// Use UNREFERENCED_PARAMETER() if a parameter will never be referenced.
//
// DBG_UNREFERENCED_PARAMETER and DBG_UNREFERENCED_LOCAL_VARIABLE will
// eventually be made into a null macro to help determine whether there
// is unfinished work.
//

#if ! defined(lint)
#define UNREFERENCED_PARAMETER(P)          (P)
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)

#else // lint

// Note: lint -e530 says don't complain about uninitialized variables for
// this varible.  Error 527 has to do with unreachable code.
// -restore restores checking to the -save state

#define UNREFERENCED_PARAMETER(P)          \
    /*lint -save -e527 -e530 -e550 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#define DBG_UNREFERENCED_PARAMETER(P)      \
    /*lint -save -e527 -e530 -e550 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) \
    /*lint -save -e527 -e530 -e550 */ \
    { \
        (V) = (V); \
    } \
    /*lint -restore */

#endif // lint

//
// Macro used to eliminate compiler warning 4715 within a switch statement
// when all possible cases have already been accounted for.
//
// switch (a & 3) {
//     case 0: return 1;
//     case 1: return Foo();
//     case 2: return Bar();
//     case 3: return 1;
//     DEFAULT_UNREACHABLE;
//

#if (_MSC_VER > 1200)
#define DEFAULT_UNREACHABLE default: __assume(0)
#else

//
// Older compilers do not support __assume(), and there is no other free
// method of eliminating the warning.
//

#define DEFAULT_UNREACHABLE

#endif

// end_winnt

//
//  Define standard min and max macros
//

#ifndef NOMINMAX

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#endif  // NOMINMAX

//
// Processor modes.
//

typedef CCHAR KPROCESSOR_MODE;

typedef enum _MODE {
    KernelMode,
    UserMode,
    MaximumMode
} MODE;

//
// DPC routine
//

struct _KDPC;

typedef
VOID
(*PKDEFERRED_ROUTINE) (
    IN struct _KDPC *Dpc,
    IN PVOID DeferredContext,
    IN PVOID SystemArgument1,
    IN PVOID SystemArgument2
    );

//
// Define DPC importance.
//
// LowImportance - Queue DPC at end of target DPC queue.
// MediumImportance - Queue DPC at end of target DPC queue.
// HighImportance - Queue DPC at front of target DPC DPC queue.
//
// If there is currently a DPC active on the target processor, or a DPC
// interrupt has already been requested on the target processor when a
// DPC is queued, then no further action is necessary. The DPC will be
// executed on the target processor when its queue entry is processed.
//
// If there is not a DPC active on the target processor and a DPC interrupt
// has not been requested on the target processor, then the exact treatment
// of the DPC is dependent on whether the host system is a UP system or an
// MP system.
//
// UP system.
//
// If the DPC is of medium or high importance, the current DPC queue depth
// is greater than the maximum target depth, or current DPC request rate is
// less the minimum target rate, then a DPC interrupt is requested on the
// host processor and the DPC will be processed when the interrupt occurs.
// Otherwise, no DPC interupt is requested and the DPC execution will be
// delayed until the DPC queue depth is greater that the target depth or the
// minimum DPC rate is less than the target rate.
//
// MP system.
//
// If the DPC is being queued to another processor and the depth of the DPC
// queue on the target processor is greater than the maximum target depth or
// the DPC is of high importance, then a DPC interrupt is requested on the
// target processor and the DPC will be processed when the interrupt occurs.
// Otherwise, the DPC execution will be delayed on the target processor until
// the DPC queue depth on the target processor is greater that the maximum
// target depth or the minimum DPC rate on the target processor is less than
// the target mimimum rate.
//
// If the DPC is being queued to the current processor and the DPC is not of
// low importance, the current DPC queue depth is greater than the maximum
// target depth, or the minimum DPC rate is less than the minimum target rate,
// then a DPC interrupt is request on the current processor and the DPV will
// be processed whne the interrupt occurs. Otherwise, no DPC interupt is
// requested and the DPC execution will be delayed until the DPC queue depth
// is greater that the target depth or the minimum DPC rate is less than the
// target rate.
//

typedef enum _KDPC_IMPORTANCE {
    LowImportance,
    MediumImportance,
    HighImportance
} KDPC_IMPORTANCE;

//
// Define DPC type indicies.
//

#define DPC_NORMAL 0
#define DPC_THREADED 1

//
// Deferred Procedure Call (DPC) object
//

#define ASSERT_DPC(Object)                                                 \
    ASSERT(((Object)->Type == DpcObject) ||                                 \
           ((Object)->Type == ThreadedDpcObject) ||                         \
           ((Object)->Type == ForceThreadedDpcObject))

typedef struct _KDPC {
    CSHORT Type;
    UCHAR Number;
    UCHAR Importance;
    LIST_ENTRY DpcListEntry;
    PKDEFERRED_ROUTINE DeferredRoutine;
    PVOID DeferredContext;
    PVOID SystemArgument1;
    PVOID SystemArgument2;
    PVOID DpcData;
} KDPC, *PKDPC, *PRKDPC;

//
// Interprocessor interrupt worker routine function prototype.
//

typedef PVOID PKIPI_CONTEXT;

typedef
VOID
(*PKIPI_WORKER)(
    IN PKIPI_CONTEXT PacketContext,
    IN PVOID Parameter1,
    IN PVOID Parameter2,
    IN PVOID Parameter3
    );

//
// Define interprocessor interrupt performance counters.
//

typedef struct _KIPI_COUNTS {
    ULONG Freeze;
    ULONG Packet;
    ULONG DPC;
    ULONG APC;
    ULONG FlushSingleTb;
    ULONG FlushMultipleTb;
    ULONG FlushEntireTb;
    ULONG GenericCall;
    ULONG ChangeColor;
    ULONG SweepDcache;
    ULONG SweepIcache;
    ULONG SweepIcacheRange;
    ULONG FlushIoBuffers;
    ULONG GratuitousDPC;
} KIPI_COUNTS, *PKIPI_COUNTS;


//
// I/O system definitions.
//
// Define a Memory Descriptor List (MDL)
//
// An MDL describes pages in a virtual buffer in terms of physical pages.  The
// pages associated with the buffer are described in an array that is allocated
// just after the MDL header structure itself.
//
// One simply calculates the base of the array by adding one to the base
// MDL pointer:
//
//      Pages = (PPFN_NUMBER) (Mdl + 1);
//
// Notice that while in the context of the subject thread, the base virtual
// address of a buffer mapped by an MDL may be referenced using the following:
//
//      Mdl->StartVa | Mdl->ByteOffset
//


typedef struct _MDL {
    struct _MDL *Next;
    CSHORT Size;
    CSHORT MdlFlags;
    struct _EPROCESS *Process;
    PVOID MappedSystemVa;
    PVOID StartVa;
    ULONG ByteCount;
    ULONG ByteOffset;
} MDL, *PMDL;

#define MDL_MAPPED_TO_SYSTEM_VA     0x0001
#define MDL_PAGES_LOCKED            0x0002
#define MDL_SOURCE_IS_NONPAGED_POOL 0x0004
#define MDL_ALLOCATED_FIXED_SIZE    0x0008
#define MDL_PARTIAL                 0x0010
#define MDL_PARTIAL_HAS_BEEN_MAPPED 0x0020
#define MDL_IO_PAGE_READ            0x0040
#define MDL_WRITE_OPERATION         0x0080
#define MDL_PARENT_MAPPED_SYSTEM_VA 0x0100
#define MDL_FREE_EXTRA_PTES         0x0200
#define MDL_DESCRIBES_AWE           0x0400
#define MDL_IO_SPACE                0x0800
#define MDL_NETWORK_HEADER          0x1000
#define MDL_MAPPING_CAN_FAIL        0x2000
#define MDL_ALLOCATED_MUST_SUCCEED  0x4000


#define MDL_MAPPING_FLAGS (MDL_MAPPED_TO_SYSTEM_VA     | \
                           MDL_PAGES_LOCKED            | \
                           MDL_SOURCE_IS_NONPAGED_POOL | \
                           MDL_PARTIAL_HAS_BEEN_MAPPED | \
                           MDL_PARENT_MAPPED_SYSTEM_VA | \
                           MDL_SYSTEM_VA               | \
                           MDL_IO_SPACE )

#define NTKERNELAPI DECLSPEC_IMPORT     
#define NTHALAPI DECLSPEC_IMPORT            
//
// Common dispatcher object header
//
// N.B. The size field contains the number of dwords in the structure.
//

typedef struct _DISPATCHER_HEADER {
    union {
        struct {
            UCHAR Type;
            UCHAR Flags;
            UCHAR Size;
            union {
                UCHAR Inserted;
                BOOLEAN DebugActive;
            };
        };

        volatile LONG Lock;
    };

    LONG SignalState;
    LIST_ENTRY WaitListHead;
} DISPATCHER_HEADER;

//
// Event object
//

#define ASSERT_EVENT(object)                                                 \
    ASSERT(((object)->Header.Type == EventNotificationObject) ||             \
           ((object)->Header.Type == EventSynchronizationObject))

typedef struct _KEVENT {
    DISPATCHER_HEADER Header;
} KEVENT, *PKEVENT, *PRKEVENT;

//
// Gate object
//
// N.B. Gate object services allow the specification of synchronization
//      events. This allows fast mutex to be transparently replaced with
//      gates.
//

#define ASSERT_GATE(object)                                                  \
    ASSERT((((object)->Header.Type) == GateObject) ||    \
          (((object)->Header.Type) == EventSynchronizationObject))

typedef struct _KGATE {
    DISPATCHER_HEADER Header;
} KGATE, *PKGATE;

//
// Timer object
//

#define ASSERT_TIMER(object)                                                 \
    ASSERT(((object)->Header.Type == TimerNotificationObject) ||             \
           ((object)->Header.Type == TimerSynchronizationObject))

typedef struct _KTIMER {
    DISPATCHER_HEADER Header;
    ULARGE_INTEGER DueTime;
    LIST_ENTRY TimerListEntry;
    struct _KDPC *Dpc;
    LONG Period;
} KTIMER, *PKTIMER, *PRKTIMER;

typedef enum _LOCK_OPERATION {
    IoReadAccess,
    IoWriteAccess,
    IoModifyAccess
} LOCK_OPERATION;


typedef ULONG_PTR KSPIN_LOCK;
typedef KSPIN_LOCK *PKSPIN_LOCK;

//
// Define the I/O bus interface types.
//

typedef enum _INTERFACE_TYPE {
    InterfaceTypeUndefined = -1,
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    PCIBus,
    VMEBus,
    NuBus,
    PCMCIABus,
    CBus,
    MPIBus,
    MPSABus,
    ProcessorInternal,
    InternalPowerBus,
    PNPISABus,
    PNPBus,
    MaximumInterfaceType
}INTERFACE_TYPE, *PINTERFACE_TYPE;

//
// Define the DMA transfer widths.
//

typedef enum _DMA_WIDTH {
    Width8Bits,
    Width16Bits,
    Width32Bits,
    MaximumDmaWidth
}DMA_WIDTH, *PDMA_WIDTH;

//
// Define DMA transfer speeds.
//

typedef enum _DMA_SPEED {
    Compatible,
    TypeA,
    TypeB,
    TypeC,
    TypeF,
    MaximumDmaSpeed
}DMA_SPEED, *PDMA_SPEED;

//
// Define Interface reference/dereference routines for
//  Interfaces exported by IRP_MN_QUERY_INTERFACE
//

typedef VOID (*PINTERFACE_REFERENCE)(PVOID Context);
typedef VOID (*PINTERFACE_DEREFERENCE)(PVOID Context);

// end_wdm
// begin_ntddk

//
// Define types of bus information.
//

typedef enum _BUS_DATA_TYPE {
    ConfigurationSpaceUndefined = -1,
    Cmos,
    EisaConfiguration,
    Pos,
    CbusConfiguration,
    PCIConfiguration,
    VMEConfiguration,
    NuBusConfiguration,
    PCMCIAConfiguration,
    MPIConfiguration,
    MPSAConfiguration,
    PNPISAConfiguration,
    SgiInternalConfiguration,
    MaximumBusDataType
} BUS_DATA_TYPE, *PBUS_DATA_TYPE;


#ifndef _SLIST_HEADER_
#define _SLIST_HEADER_

#if defined(_WIN64)

//
// The type SINGLE_LIST_ENTRY is not suitable for use with SLISTs.  For
// WIN64, an entry on an SLIST is required to be 16-byte aligned, while a
// SINGLE_LIST_ENTRY structure has only 8 byte alignment.
//
// Therefore, all SLIST code should use the SLIST_ENTRY type instead of the
// SINGLE_LIST_ENTRY type.
//

#pragma warning(push)
#pragma warning(disable:4324)   // structure padded due to align()
typedef struct DECLSPEC_ALIGN(16) _SLIST_ENTRY *PSLIST_ENTRY;
typedef struct DECLSPEC_ALIGN(16) _SLIST_ENTRY {
    PSLIST_ENTRY Next;
} SLIST_ENTRY;
#pragma warning(pop)

#else

#define SLIST_ENTRY SINGLE_LIST_ENTRY
#define _SLIST_ENTRY _SINGLE_LIST_ENTRY
#define PSLIST_ENTRY PSINGLE_LIST_ENTRY

#endif

#if defined(_WIN64)

typedef struct DECLSPEC_ALIGN(16) _SLIST_HEADER {
    ULONGLONG Alignment;
    ULONGLONG Region;
} SLIST_HEADER;

typedef struct _SLIST_HEADER *PSLIST_HEADER;

#else

typedef union _SLIST_HEADER {
    ULONGLONG Alignment;
    struct {
        SLIST_ENTRY Next;
        USHORT Depth;
        USHORT Sequence;
    };
} SLIST_HEADER, *PSLIST_HEADER;

#endif

#endif // _SLIST_HEADER_

//
// If debugging support enabled, define an ASSERT macro that works.  Otherwise
// define the ASSERT macro to expand to an empty expression.
//
// The ASSERT macro has been updated to be an expression instead of a statement.
//

NTSYSAPI
VOID
NTAPI
RtlAssert(
    PVOID FailedAssertion,
    PVOID FileName,
    ULONG LineNumber,
    PCHAR Message
    );

#if DBG

#define ASSERT( exp ) \
    ((!(exp)) ? \
        (RtlAssert( #exp, __FILE__, __LINE__, NULL ),FALSE) : \
        TRUE)

#define ASSERTMSG( msg, exp ) \
    ((!(exp)) ? \
        (RtlAssert( #exp, __FILE__, __LINE__, msg ),FALSE) : \
        TRUE)

#define RTL_SOFT_ASSERT(_exp) \
    ((!(_exp)) ? \
        (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n", __FILE__, __LINE__, #_exp),FALSE) : \
        TRUE)

#define RTL_SOFT_ASSERTMSG(_msg, _exp) \
    ((!(_exp)) ? \
        (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n   Message: %s\n", __FILE__, __LINE__, #_exp, (_msg)),FALSE) : \
        TRUE)

#if _MSC_VER >= 1300

#define NT_ASSERT(_exp) \
    ((!(_exp)) ? \
        (__annotation(L"Debug", L"AssertFail", L#_exp), \
         DbgRaiseAssertionFailure(), FALSE) : \
        TRUE)

#define NT_ASSERTMSG(_msg, _exp) \
    ((!(_exp)) ? \
        (__annotation(L"Debug", L"AssertFail", L##_msg), \
         DbgRaiseAssertionFailure(), FALSE) : \
        TRUE)

#define NT_ASSERTMSGW(_msg, _exp) \
    ((!(_exp)) ? \
        (__annotation(L"Debug", L"AssertFail", _msg), \
         DbgRaiseAssertionFailure(), FALSE) : \
        TRUE)

#define NT_VERIFY     NT_ASSERT
#define NT_VERIFYMSG  NT_ASSERTMSG
#define NT_VERIFYMSGW NT_ASSERTMSGW

#endif // #if _MSC_VER >= 1300
             
#define RTL_VERIFY         ASSERT
#define RTL_VERIFYMSG      ASSERTMSG

#define RTL_SOFT_VERIFY    RTL_SOFT_ASSERT
#define RTL_SOFT_VERIFYMSG RTL_SOFT_ASSERTMSG

#else
#define ASSERT( exp )         ((void) 0)
#define ASSERTMSG( msg, exp ) ((void) 0)

#if _MSC_VER >= 1300

#define NT_ASSERT(_exp)           ((void) 0)
#define NT_ASSERTMSG(_msg, _exp)  ((void) 0)
#define NT_ASSERTMSGW(_msg, _exp) ((void) 0)

#define NT_VERIFY(_exp)           ((_exp) ? TRUE : FALSE)
#define NT_VERIFYMSG(_msg, _exp ) ((_exp) ? TRUE : FALSE)
#define NT_VERIFYMSGW(_msg, _exp) ((_exp) ? TRUE : FALSE)

#endif // #if _MSC_VER >= 1300

#define RTL_SOFT_ASSERT(_exp)          ((void) 0)
#define RTL_SOFT_ASSERTMSG(_msg, _exp) ((void) 0)

#define RTL_VERIFY( exp )         ((exp) ? TRUE : FALSE)
#define RTL_VERIFYMSG( msg, exp ) ((exp) ? TRUE : FALSE)

#define RTL_SOFT_VERIFY(_exp)         ((_exp) ? TRUE : FALSE)
#define RTL_SOFT_VERIFYMSG(msg, _exp) ((_exp) ? TRUE : FALSE)

#endif // DBG

//
//  Doubly-linked list manipulation routines.
//


//
//  VOID
//  InitializeListHead32(
//      PLIST_ENTRY32 ListHead
//      );
//

#if (NTDDI_VERSION >= NTDDI_WIN2K)

#define InitializeListHead32(ListHead) (\
    (ListHead)->Flink = (ListHead)->Blink = PtrToUlong((ListHead)))

#if !defined(MIDL_PASS) && !defined(SORTPP_PASS)


VOID
FORCEINLINE
InitializeListHead(
    IN PLIST_ENTRY ListHead
    )
{
    ListHead->Flink = ListHead->Blink = ListHead;
}

BOOLEAN
FORCEINLINE
IsListEmpty(
    IN const LIST_ENTRY * ListHead
    )
{
    return (BOOLEAN)(ListHead->Flink == ListHead);
}

BOOLEAN
FORCEINLINE
RemoveEntryList(
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Flink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;
    return (BOOLEAN)(Flink == Blink);
}

PLIST_ENTRY
FORCEINLINE
RemoveHeadList(
    IN PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Flink;
    PLIST_ENTRY Entry;

    Entry = ListHead->Flink;
    Flink = Entry->Flink;
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;
    return Entry;
}



PLIST_ENTRY
FORCEINLINE
RemoveTailList(
    IN PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Entry;

    Entry = ListHead->Blink;
    Blink = Entry->Blink;
    ListHead->Blink = Blink;
    Blink->Flink = ListHead;
    return Entry;
}


VOID
FORCEINLINE
InsertTailList(
    IN PLIST_ENTRY ListHead,
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;

    Blink = ListHead->Blink;
    Entry->Flink = ListHead;
    Entry->Blink = Blink;
    Blink->Flink = Entry;
    ListHead->Blink = Entry;
}


VOID
FORCEINLINE
InsertHeadList(
    IN PLIST_ENTRY ListHead,
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Flink;

    Flink = ListHead->Flink;
    Entry->Flink = Flink;
    Entry->Blink = ListHead;
    Flink->Blink = Entry;
    ListHead->Flink = Entry;
}

FORCEINLINE
PSINGLE_LIST_ENTRY
PopEntryList(
    PSINGLE_LIST_ENTRY ListHead
    )
{
    PSINGLE_LIST_ENTRY FirstEntry;
    FirstEntry = ListHead->Next;
    if (FirstEntry != NULL) {
        ListHead->Next = FirstEntry->Next;
    }

    return FirstEntry;
}

FORCEINLINE
VOID
PushEntryList(
    PSINGLE_LIST_ENTRY ListHead,
    PSINGLE_LIST_ENTRY Entry
    )
{
    Entry->Next = ListHead->Next; 
    ListHead->Next = Entry;
}

#endif // !MIDL_PASS
#endif // NTDDI_VERSION >= NTDDI_WIN2K


#if defined (_MSC_VER) && ( _MSC_VER >= 900 )

PVOID
_ReturnAddress (
    VOID
    );

#pragma intrinsic(_ReturnAddress)

#endif

#if (defined(_M_AMD64) || defined(_M_IA64)) && !defined(_REALLY_GET_CALLERS_CALLER_)

#define RtlGetCallersAddress(CallersAddress, CallersCaller) \
    *CallersAddress = (PVOID)_ReturnAddress(); \
    *CallersCaller = NULL;

#else

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
VOID
NTAPI
RtlGetCallersAddress(
    OUT PVOID *CallersAddress,
    OUT PVOID *CallersCaller
    );
#endif

#endif

//
// Define procedure prototypes for replaceable Stack Walker routine
//

typedef ULONG (* PRTL_WALK_FRAME_CHAIN)(
    OUT PVOID *Callers,
    IN ULONG Count,
    IN ULONG Flags
    );

#if (NTDDI_VERSION >= NTDDI_WIN2K)    
NTSYSAPI
ULONG
NTAPI
RtlWalkFrameChain (
    OUT PVOID *Callers,
    IN ULONG Count,
    IN ULONG Flags
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToAnsiString(
    PANSI_STRING DestinationString,
    PCUNICODE_STRING SourceString,
    BOOLEAN AllocateDestinationString
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeString(
    PCUNICODE_STRING String1,
    PCUNICODE_STRING String2,
    BOOLEAN CaseInSensitive
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualUnicodeString(
    PCUNICODE_STRING String1,
    PCUNICODE_STRING String2,
    BOOLEAN CaseInSensitive
    );
#endif

#define HASH_STRING_ALGORITHM_DEFAULT   (0)
#define HASH_STRING_ALGORITHM_X65599    (1)
#define HASH_STRING_ALGORITHM_INVALID   (0xffffffff)

#if (NTDDI_VERSION >= NTDDI_WINXP)

NTSYSAPI
NTSTATUS
NTAPI
RtlHashUnicodeString(
    IN const UNICODE_STRING *String,
    IN BOOLEAN CaseInSensitive,
    IN ULONG HashAlgorithm,
    OUT PULONG HashValue
    );

#endif // NTDDI_VERSION >= NTDDI_WINXP


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
BOOLEAN
NTAPI
RtlPrefixUnicodeString(
    IN PCUNICODE_STRING String1,
    IN PCUNICODE_STRING String2,
    IN BOOLEAN CaseInSensitive
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeString(
    PUNICODE_STRING DestinationString,
    PCUNICODE_STRING SourceString,
    BOOLEAN AllocateDestinationString
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
VOID
NTAPI
RtlCopyUnicodeString(
    IN OUT PUNICODE_STRING DestinationString,
    IN PCUNICODE_STRING SourceString
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
NTSTATUS
NTAPI
RtlAppendUnicodeStringToString (
    IN OUT PUNICODE_STRING Destination,
    IN PCUNICODE_STRING Source
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
NTSTATUS
NTAPI
RtlAppendUnicodeToString (
    IN OUT PUNICODE_STRING Destination,
    IN PCWSTR Source
    );
#endif


#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
SIZE_T
NTAPI
RtlCompareMemory (
    const VOID *Source1,
    const VOID *Source2,
    SIZE_T Length
    );
#endif

#define RtlEqualMemory(Destination,Source,Length) (!memcmp((Destination),(Source),(Length)))

#if !defined(MIDL_PASS)
        
#if defined(_M_AMD64)

NTSYSAPI
VOID
NTAPI
RtlCopyMemory (
    VOID UNALIGNED *Destination,
    CONST VOID UNALIGNED *Source,
    SIZE_T Length
    );

NTSYSAPI
VOID
NTAPI
RtlMoveMemory (
    VOID UNALIGNED *Destination,
    CONST VOID UNALIGNED *Source,
    SIZE_T Length
    );

#else

// Use different name so old code can continue to link to exports if desired
#define RtlCopyMemory _RtlCopyMemory
#define RtlMoveMemory _RtlMoveMemory		

// Inline functions so x86/ia64 match amd64 (ie: return type is VOID, not VOID *)

VOID
FORCEINLINE
RtlCopyMemory (
    VOID UNALIGNED *Destination,
    CONST VOID UNALIGNED *Source,
    SIZE_T Length
    )
{
    memcpy(Destination, Source, Length);
}

VOID
FORCEINLINE
RtlMoveMemory (
    VOID UNALIGNED *Destination,
    CONST VOID UNALIGNED *Source,
    SIZE_T Length
    )
{
    memmove(Destination, Source, Length);
}

#endif

#define RtlFillMemory(Destination,Length,Fill) memset((Destination),(Fill),(Length))
#define RtlZeroMemory(Destination,Length) memset((Destination),0,(Length))

FORCEINLINE
PVOID
RtlSecureZeroMemory(
    IN PVOID ptr,
    IN SIZE_T cnt
    )
{
    volatile char *vptr = (volatile char *)ptr;
    while (cnt) {
        *vptr = 0;
        vptr++;
        cnt--;
    }
    return ptr;
}
#endif

//
// Define kernel debugger print prototypes and macros.
//
// N.B. The following function cannot be directly imported because there are
//      a few places in the source tree where this function is redefined.
//

#if (NTDDI_VERSION >= NTDDI_WIN2K)
VOID
NTAPI
DbgBreakPoint(
    VOID
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTSYSAPI
VOID
NTAPI
DbgBreakPointWithStatus(
    IN ULONG Status
    );
#endif

#define DBG_STATUS_CONTROL_C        1
#define DBG_STATUS_SYSRQ            2
#define DBG_STATUS_BUGCHECK_FIRST   3
#define DBG_STATUS_BUGCHECK_SECOND  4
#define DBG_STATUS_FATAL            5
#define DBG_STATUS_DEBUG_CONTROL    6
#define DBG_STATUS_WORKER           7

#if DBG

#define KdPrint(_x_) DbgPrint _x_
#define KdPrintEx(_x_) DbgPrintEx _x_
#define vKdPrintEx(_x_) vDbgPrintEx _x_
#define vKdPrintExWithPrefix(_x_) vDbgPrintExWithPrefix _x_
#define KdBreakPoint() DbgBreakPoint()

#define KdBreakPointWithStatus(s) DbgBreakPointWithStatus(s)

#else

#define KdPrint(_x_)
#define KdPrintEx(_x_)
#define vKdPrintEx(_x_)
#define vKdPrintExWithPrefix(_x_)
#define KdBreakPoint()

#define KdBreakPointWithStatus(s)


#endif // DBG

#ifndef _DBGNT_

ULONG
__cdecl
DbgPrint(
    PCH Format,
    ...
    );

#if (NTDDI_VERSION >= NTDDI_WINXP)
ULONG
__cdecl
DbgPrintEx(
    IN ULONG ComponentId,
    IN ULONG Level,
    IN PCH Format,
    ...
    );
#endif    

#ifdef _VA_LIST_DEFINED

#if (NTDDI_VERSION >= NTDDI_WINXP)
ULONG
vDbgPrintEx(
    IN ULONG ComponentId,
    IN ULONG Level,
    IN PCH Format,
    va_list arglist
    );

ULONG
vDbgPrintExWithPrefix(
    IN PCH Prefix,
    IN ULONG ComponentId,
    IN ULONG Level,
    IN PCH Format,
    va_list arglist
    );
#endif     

#endif // _VA_LIST_DEFINED

ULONG
__cdecl
DbgPrintReturnControlC(
    PCH Format,
    ...
    );

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTSYSAPI
NTSTATUS
DbgQueryDebugFilterState(
    IN ULONG ComponentId,
    IN ULONG Level
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)   

NTSYSAPI
NTSTATUS
DbgSetDebugFilterState(
    IN ULONG ComponentId,
    IN ULONG Level,
    IN BOOLEAN State
    );
#endif    

#endif // _DBGNT_

#if (NTDDI_VERSION >= NTDDI_WINXP)
#include <dpfilter.h>
#endif
//
// Define I/O Driver error log packet structure.  This structure is filled in
// by the driver.
//

typedef struct _IO_ERROR_LOG_PACKET {
    UCHAR MajorFunctionCode;
    UCHAR RetryCount;
    USHORT DumpDataSize;
    USHORT NumberOfStrings;
    USHORT StringOffset;
    USHORT EventCategory;
    NTSTATUS ErrorCode;
    ULONG UniqueErrorValue;
    NTSTATUS FinalStatus;
    ULONG SequenceNumber;
    ULONG IoControlCode;
    LARGE_INTEGER DeviceOffset;
    ULONG DumpData[1];
}IO_ERROR_LOG_PACKET, *PIO_ERROR_LOG_PACKET;

//
// Define the I/O error log message.  This message is sent by the error log
// thread over the lpc port.
//

typedef struct _IO_ERROR_LOG_MESSAGE {
    USHORT Type;
    USHORT Size;
    USHORT DriverNameLength;
    LARGE_INTEGER TimeStamp;
    ULONG DriverNameOffset;
    IO_ERROR_LOG_PACKET EntryData;
}IO_ERROR_LOG_MESSAGE, *PIO_ERROR_LOG_MESSAGE;

//
// Define the maximum message size that will be sent over the LPC to the
// application reading the error log entries.
//

//
// Regardless of LPC size restrictions, ERROR_LOG_MAXIMUM_SIZE must remain
// a value that can fit in a UCHAR.
//

#define ERROR_LOG_LIMIT_SIZE (256-16)

//
// This limit, exclusive of IO_ERROR_LOG_MESSAGE_HEADER_LENGTH, also applies
// to IO_ERROR_LOG_MESSAGE_LENGTH
//

#define IO_ERROR_LOG_MESSAGE_HEADER_LENGTH (sizeof(IO_ERROR_LOG_MESSAGE) -    \
                                            sizeof(IO_ERROR_LOG_PACKET) +     \
                                            (sizeof(WCHAR) * 40))

#define ERROR_LOG_MESSAGE_LIMIT_SIZE                                          \
    (ERROR_LOG_LIMIT_SIZE + IO_ERROR_LOG_MESSAGE_HEADER_LENGTH)

//
// IO_ERROR_LOG_MESSAGE_LENGTH is
// min(PORT_MAXIMUM_MESSAGE_LENGTH, ERROR_LOG_MESSAGE_LIMIT_SIZE)
//

#define IO_ERROR_LOG_MESSAGE_LENGTH                                           \
    ((PORT_MAXIMUM_MESSAGE_LENGTH > ERROR_LOG_MESSAGE_LIMIT_SIZE) ?           \
        ERROR_LOG_MESSAGE_LIMIT_SIZE :                                        \
        PORT_MAXIMUM_MESSAGE_LENGTH)

//
// Define the maximum packet size a driver can allocate.
//

#define ERROR_LOG_MAXIMUM_SIZE (IO_ERROR_LOG_MESSAGE_LENGTH -                 \
                                IO_ERROR_LOG_MESSAGE_HEADER_LENGTH)


#if defined(_X86_)
// end_ntddk end_nthal

//
// Types to use to contain PFNs and their counts.
//

typedef ULONG PFN_COUNT;

typedef LONG SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG PFN_NUMBER, *PPFN_NUMBER;

//
// Define maximum size of flush multiple TB request.
//

#define FLUSH_MULTIPLE_MAXIMUM 32

//
// Indicate that the i386 compiler supports the pragma textout construct.
//

#define ALLOC_PRAGMA 1
//
// Indicate that the i386 compiler supports the DATA_SEG("INIT") and
// DATA_SEG("PAGE") pragmas
//

#define ALLOC_DATA_PRAGMA 1


//
// I/O space read and write macros.
//
//  These have to be actual functions on the 386, because we need
//  to use assembler, but cannot return a value if we inline it.
//
//  The READ/WRITE_REGISTER_* calls manipulate I/O registers in MEMORY space.
//  (Use x86 move instructions, with LOCK prefix to force correct behavior
//   w.r.t. caches and write buffers.)
//
//  The READ/WRITE_PORT_* calls manipulate I/O registers in PORT space.
//  (Use x86 in/out instructions.)
//

NTKERNELAPI
UCHAR
NTAPI
READ_REGISTER_UCHAR(
    PUCHAR  Register
    );

NTKERNELAPI
USHORT
NTAPI
READ_REGISTER_USHORT(
    PUSHORT Register
    );

NTKERNELAPI
ULONG
NTAPI
READ_REGISTER_ULONG(
    PULONG  Register
    );

NTKERNELAPI
VOID
NTAPI
READ_REGISTER_BUFFER_UCHAR(
    PUCHAR  Register,
    PUCHAR  Buffer,
    ULONG   Count
    );

NTKERNELAPI
VOID
NTAPI
READ_REGISTER_BUFFER_USHORT(
    PUSHORT Register,
    PUSHORT Buffer,
    ULONG   Count
    );

NTKERNELAPI
VOID
NTAPI
READ_REGISTER_BUFFER_ULONG(
    PULONG  Register,
    PULONG  Buffer,
    ULONG   Count
    );


NTKERNELAPI
VOID
NTAPI
WRITE_REGISTER_UCHAR(
    PUCHAR  Register,
    UCHAR   Value
    );

NTKERNELAPI
VOID
NTAPI
WRITE_REGISTER_USHORT(
    PUSHORT Register,
    USHORT  Value
    );

NTKERNELAPI
VOID
NTAPI
WRITE_REGISTER_ULONG(
    PULONG  Register,
    ULONG   Value
    );

NTKERNELAPI
VOID
NTAPI
WRITE_REGISTER_BUFFER_UCHAR(
    PUCHAR  Register,
    PUCHAR  Buffer,
    ULONG   Count
    );

NTKERNELAPI
VOID
NTAPI
WRITE_REGISTER_BUFFER_USHORT(
    PUSHORT Register,
    PUSHORT Buffer,
    ULONG   Count
    );

NTKERNELAPI
VOID
NTAPI
WRITE_REGISTER_BUFFER_ULONG(
    PULONG  Register,
    PULONG  Buffer,
    ULONG   Count
    );

NTHALAPI
UCHAR
NTAPI
READ_PORT_UCHAR(
    PUCHAR  Port
    );

NTHALAPI
USHORT
NTAPI
READ_PORT_USHORT(
    PUSHORT Port
    );

NTHALAPI
ULONG
NTAPI
READ_PORT_ULONG(
    PULONG  Port
    );

NTHALAPI
VOID
NTAPI
READ_PORT_BUFFER_UCHAR(
    PUCHAR  Port,
    PUCHAR  Buffer,
    ULONG   Count
    );

NTHALAPI
VOID
NTAPI
READ_PORT_BUFFER_USHORT(
    PUSHORT Port,
    PUSHORT Buffer,
    ULONG   Count
    );

NTHALAPI
VOID
NTAPI
READ_PORT_BUFFER_ULONG(
    PULONG  Port,
    PULONG  Buffer,
    ULONG   Count
    );

NTHALAPI
VOID
NTAPI
WRITE_PORT_UCHAR(
    PUCHAR  Port,
    UCHAR   Value
    );

NTHALAPI
VOID
NTAPI
WRITE_PORT_USHORT(
    PUSHORT Port,
    USHORT  Value
    );

NTHALAPI
VOID
NTAPI
WRITE_PORT_ULONG(
    PULONG  Port,
    ULONG   Value
    );

NTHALAPI
VOID
NTAPI
WRITE_PORT_BUFFER_UCHAR(
    PUCHAR  Port,
    PUCHAR  Buffer,
    ULONG   Count
    );

NTHALAPI
VOID
NTAPI
WRITE_PORT_BUFFER_USHORT(
    PUSHORT Port,
    PUSHORT Buffer,
    ULONG   Count
    );

NTHALAPI
VOID
NTAPI
WRITE_PORT_BUFFER_ULONG(
    PULONG  Port,
    PULONG  Buffer,
    ULONG   Count
    );


#define KeFlushIoBuffers(Mdl, ReadOperation, DmaOperation)

//
// i386 Specific portions of mm component
//

//
// Define the page size for the Intel 386 as 4096 (0x1000).
//

#define PAGE_SIZE 0x1000

//
// Define the number of trailing zeroes in a page aligned virtual address.
// This is used as the shift count when shifting virtual addresses to
// virtual page numbers.
//

#define PAGE_SHIFT 12L


//++
//
// VOID
// KeMemoryBarrier (
//    VOID
//    )
//
// VOID
// KeMemoryBarrierWithoutFence (
//    VOID
//    )
//
//
// Routine Description:
//
//    These functions order memory accesses as seen by other processors.
//
// Arguments:
//
//    None.
//
// Return Value:
//
//    None.
//
//--

#ifdef __cplusplus
extern "C" {
#endif

VOID
_ReadWriteBarrier(
    VOID
    );

#ifdef __cplusplus
}
#endif

#pragma intrinsic (_ReadWriteBarrier)


FORCEINLINE
VOID
KeMemoryBarrier (
    VOID
    )
{
    LONG Barrier;
    __asm {
        xchg Barrier, eax
    }
}

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()


#endif // defined(_X86_)


#if defined(_M_AMD64) && !defined(RC_INVOKED) && !defined(MIDL_PASS) 

//
// Define intrinsic function to do in's and out's.
//

#ifdef __cplusplus
extern "C" {
#endif

UCHAR
__inbyte (
    IN USHORT Port
    );

USHORT
__inword (
    IN USHORT Port
    );

ULONG
__indword (
    IN USHORT Port
    );

VOID
__outbyte (
    IN USHORT Port,
    IN UCHAR Data
    );

VOID
__outword (
    IN USHORT Port,
    IN USHORT Data
    );

VOID
__outdword (
    IN USHORT Port,
    IN ULONG Data
    );

VOID
__inbytestring (
    IN USHORT Port,
    IN PUCHAR Buffer,
    IN ULONG Count
    );

VOID
__inwordstring (
    IN USHORT Port,
    IN PUSHORT Buffer,
    IN ULONG Count
    );

VOID
__indwordstring (
    IN USHORT Port,
    IN PULONG Buffer,
    IN ULONG Count
    );

VOID
__outbytestring (
    IN USHORT Port,
    IN PUCHAR Buffer,
    IN ULONG Count
    );

VOID
__outwordstring (
    IN USHORT Port,
    IN PUSHORT Buffer,
    IN ULONG Count
    );

VOID
__outdwordstring (
    IN USHORT Port,
    IN PULONG Buffer,
    IN ULONG Count
    );

#ifdef __cplusplus
}
#endif

#pragma intrinsic(__inbyte)
#pragma intrinsic(__inword)
#pragma intrinsic(__indword)
#pragma intrinsic(__outbyte)
#pragma intrinsic(__outword)
#pragma intrinsic(__outdword)
#pragma intrinsic(__inbytestring)
#pragma intrinsic(__inwordstring)
#pragma intrinsic(__indwordstring)
#pragma intrinsic(__outbytestring)
#pragma intrinsic(__outwordstring)
#pragma intrinsic(__outdwordstring)

//
// Interlocked intrinsic functions.
//

#define InterlockedIncrement16 _InterlockedIncrement16
#define InterlockedDecrement16 _InterlockedDecrement16
#define InterlockedCompareExchange16 _InterlockedCompareExchange16

#define InterlockedAnd _InterlockedAnd
#define InterlockedOr _InterlockedOr
#define InterlockedXor _InterlockedXor
#define InterlockedIncrement _InterlockedIncrement
#define InterlockedIncrementAcquire InterlockedIncrement
#define InterlockedIncrementRelease InterlockedIncrement
#define InterlockedDecrement _InterlockedDecrement
#define InterlockedDecrementAcquire InterlockedDecrement
#define InterlockedDecrementRelease InterlockedDecrement
#define InterlockedAdd _InterlockedAdd
#define InterlockedExchange _InterlockedExchange
#define InterlockedExchangeAdd _InterlockedExchangeAdd
#define InterlockedCompareExchange _InterlockedCompareExchange
#define InterlockedCompareExchangeAcquire InterlockedCompareExchange
#define InterlockedCompareExchangeRelease InterlockedCompareExchange

#define InterlockedAnd64 _InterlockedAnd64
#define InterlockedAndAffinity InterlockedAnd64
#define InterlockedOr64 _InterlockedOr64
#define InterlockedOrAffinity InterlockedOr64
#define InterlockedXor64 _InterlockedXor64
#define InterlockedIncrement64 _InterlockedIncrement64
#define InterlockedDecrement64 _InterlockedDecrement64
#define InterlockedAdd64 _InterlockedAdd64
#define InterlockedExchange64 _InterlockedExchange64
#define InterlockedExchangeAcquire64 InterlockedExchange64
#define InterlockedExchangeAdd64 _InterlockedExchangeAdd64
#define InterlockedCompareExchange64 _InterlockedCompareExchange64
#define InterlockedCompareExchangeAcquire64 InterlockedCompareExchange64
#define InterlockedCompareExchangeRelease64 InterlockedCompareExchange64
#define InterlockedExchangePointer _InterlockedExchangePointer
#define InterlockedCompareExchangePointer _InterlockedCompareExchangePointer
#define InterlockedCompareExchangePointerAcquire _InterlockedCompareExchangePointer
#define InterlockedCompareExchangePointerRelease _InterlockedCompareExchangePointer

#define InterlockedExchangeAddSizeT(a, b) InterlockedExchangeAdd64((LONG64 *)a, b)
#define InterlockedIncrementSizeT(a) InterlockedIncrement64((LONG64 *)a)
#define InterlockedDecrementSizeT(a) InterlockedDecrement64((LONG64 *)a)

#ifdef __cplusplus
extern "C" {
#endif

SHORT
InterlockedIncrement16 (
    IN OUT SHORT volatile *Addend
    );

SHORT
InterlockedDecrement16 (
    IN OUT SHORT volatile *Addend
    );

SHORT
InterlockedCompareExchange16 (
    IN OUT SHORT volatile *Destination,
    IN SHORT ExChange,
    IN SHORT Comperand
    );

LONG
InterlockedAnd (
    IN OUT LONG volatile *Destination,
    IN LONG Value
    );

LONG
InterlockedOr (
    IN OUT LONG volatile *Destination,
    IN LONG Value
    );

LONG
InterlockedXor (
    IN OUT LONG volatile *Destination,
    IN LONG Value
    );

LONG64
InterlockedAnd64 (
    IN OUT LONG64 volatile *Destination,
    IN LONG64 Value
    );

LONG64
InterlockedOr64 (
    IN OUT LONG64 volatile *Destination,
    IN LONG64 Value
    );

LONG64
InterlockedXor64 (
    IN OUT LONG64 volatile *Destination,
    IN LONG64 Value
    );

LONG
InterlockedIncrement(
    IN OUT LONG volatile *Addend
    );

LONG
InterlockedDecrement(
    IN OUT LONG volatile *Addend
    );

LONG
InterlockedExchange(
    IN OUT LONG volatile *Target,
    IN LONG Value
    );

LONG
InterlockedExchangeAdd(
    IN OUT LONG volatile *Addend,
    IN LONG Value
    );

#if !defined(_X86AMD64_)

__forceinline
LONG
InterlockedAdd(
    IN OUT LONG volatile *Addend,
    IN LONG Value
    )

{
    return InterlockedExchangeAdd(Addend, Value) + Value;
}

#endif

LONG
InterlockedCompareExchange (
    IN OUT LONG volatile *Destination,
    IN LONG ExChange,
    IN LONG Comperand
    );

LONG64
InterlockedIncrement64(
    IN OUT LONG64 volatile *Addend
    );

LONG64
InterlockedDecrement64(
    IN OUT LONG64 volatile *Addend
    );

LONG64
InterlockedExchange64(
    IN OUT LONG64 volatile *Target,
    IN LONG64 Value
    );

LONG64
InterlockedExchangeAdd64(
    IN OUT LONG64 volatile *Addend,
    IN LONG64 Value
    );

#if !defined(_X86AMD64_)

__forceinline
LONG64
InterlockedAdd64(
    IN OUT LONG64 volatile *Addend,
    IN LONG64 Value
    )

{
    return InterlockedExchangeAdd64(Addend, Value) + Value;
}

#endif

LONG64
InterlockedCompareExchange64 (
    IN OUT LONG64 volatile *Destination,
    IN LONG64 ExChange,
    IN LONG64 Comperand
    );

PVOID
InterlockedCompareExchangePointer (
    IN OUT PVOID volatile *Destination,
    IN PVOID Exchange,
    IN PVOID Comperand
    );

PVOID
InterlockedExchangePointer(
    IN OUT PVOID volatile *Target,
    IN PVOID Value
    );

#pragma intrinsic(_InterlockedIncrement16)
#pragma intrinsic(_InterlockedDecrement16)
#pragma intrinsic(_InterlockedCompareExchange16)
#pragma intrinsic(_InterlockedAnd)
#pragma intrinsic(_InterlockedOr)
#pragma intrinsic(_InterlockedXor)
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedDecrement)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
#pragma intrinsic(_InterlockedCompareExchange)
#pragma intrinsic(_InterlockedAnd64)
#pragma intrinsic(_InterlockedOr64)
#pragma intrinsic(_InterlockedXor64)
#pragma intrinsic(_InterlockedIncrement64)
#pragma intrinsic(_InterlockedDecrement64)
#pragma intrinsic(_InterlockedExchange64)
#pragma intrinsic(_InterlockedExchangeAdd64)
#pragma intrinsic(_InterlockedCompareExchange64)
#pragma intrinsic(_InterlockedExchangePointer)
#pragma intrinsic(_InterlockedCompareExchangePointer)

#ifdef __cplusplus
}
#endif

#endif // defined(_M_AMD64) && !defined(RC_INVOKED) && !defined(MIDL_PASS)

#if defined(_AMD64_) // ntddk nthal

//
// Types to use to contain PFNs and their counts.
//

typedef ULONG PFN_COUNT;

typedef LONG64 SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG64 PFN_NUMBER, *PPFN_NUMBER;

//
// Define maximum size of flush multiple TB request.
//

#define FLUSH_MULTIPLE_MAXIMUM 32

//
// Indicate that the AMD64 compiler supports the allocate pragmas.
//

#define ALLOC_PRAGMA 1
#define ALLOC_DATA_PRAGMA 1


// begin_ntminiport

#if defined(_AMD64_) && !defined(_IOACCESS_)

//
// I/O space read and write macros.
//
//  The READ/WRITE_REGISTER_* calls manipulate I/O registers in MEMORY space.
//
//  The READ/WRITE_PORT_* calls manipulate I/O registers in PORT space.
//

__forceinline
UCHAR
READ_REGISTER_UCHAR (
    volatile UCHAR *Register
    )
{
    return *Register;
}

__forceinline
USHORT
READ_REGISTER_USHORT (
    volatile USHORT *Register
    )
{
    return *Register;
}

__forceinline
ULONG
READ_REGISTER_ULONG (
    volatile ULONG *Register
    )
{
    return *Register;
}

__forceinline
VOID
READ_REGISTER_BUFFER_UCHAR (
    PUCHAR Register,
    PUCHAR Buffer,
    ULONG Count
    )
{
    __movsb(Buffer, Register, Count);
    return;
}

__forceinline
VOID
READ_REGISTER_BUFFER_USHORT (
    PUSHORT Register,
    PUSHORT Buffer,
    ULONG Count
    )
{
    __movsw(Buffer, Register, Count);
    return;
}

__forceinline
VOID
READ_REGISTER_BUFFER_ULONG (
    PULONG Register,
    PULONG Buffer,
    ULONG Count
    )
{
    __movsd(Buffer, Register, Count);
    return;
}

__forceinline
VOID
WRITE_REGISTER_UCHAR (
    PUCHAR Register,
    UCHAR Value
    )
{

    *Register = Value;
    StoreFence();
    return;
}

__forceinline
VOID
WRITE_REGISTER_USHORT (
    PUSHORT Register,
    USHORT Value
    )
{

    *Register = Value;
    StoreFence();
    return;
}

__forceinline
VOID
WRITE_REGISTER_ULONG (
    PULONG Register,
    ULONG Value
    )
{

    *Register = Value;
    StoreFence();
    return;
}

__forceinline
VOID
WRITE_REGISTER_BUFFER_UCHAR (
    PUCHAR Register,
    PUCHAR Buffer,
    ULONG Count
    )
{

    __movsb(Register, Buffer, Count);
    StoreFence();
    return;
}

__forceinline
VOID
WRITE_REGISTER_BUFFER_USHORT (
    PUSHORT Register,
    PUSHORT Buffer,
    ULONG Count
    )
{

    __movsw(Register, Buffer, Count);
    StoreFence();
    return;
}

__forceinline
VOID
WRITE_REGISTER_BUFFER_ULONG (
    PULONG Register,
    PULONG Buffer,
    ULONG Count
    )
{

    __movsd(Register, Buffer, Count);
    StoreFence();
    return;
}

__forceinline
UCHAR
READ_PORT_UCHAR (
    PUCHAR Port
    )

{
    return __inbyte((USHORT)((ULONG64)Port));
}

__forceinline
USHORT
READ_PORT_USHORT (
    PUSHORT Port
    )

{
    return __inword((USHORT)((ULONG64)Port));
}

__forceinline
ULONG
READ_PORT_ULONG (
    PULONG Port
    )

{
    return __indword((USHORT)((ULONG64)Port));
}


__forceinline
VOID
READ_PORT_BUFFER_UCHAR (
    PUCHAR Port,
    PUCHAR Buffer,
    ULONG Count
    )

{
    __inbytestring((USHORT)((ULONG64)Port), Buffer, Count);
    return;
}

__forceinline
VOID
READ_PORT_BUFFER_USHORT (
    PUSHORT Port,
    PUSHORT Buffer,
    ULONG Count
    )

{
    __inwordstring((USHORT)((ULONG64)Port), Buffer, Count);
    return;
}

__forceinline
VOID
READ_PORT_BUFFER_ULONG (
    PULONG Port,
    PULONG Buffer,
    ULONG Count
    )

{
    __indwordstring((USHORT)((ULONG64)Port), Buffer, Count);
    return;
}

__forceinline
VOID
WRITE_PORT_UCHAR (
    PUCHAR Port,
    UCHAR Value
    )

{
    __outbyte((USHORT)((ULONG64)Port), Value);
    return;
}

__forceinline
VOID
WRITE_PORT_USHORT (
    PUSHORT Port,
    USHORT Value
    )

{
    __outword((USHORT)((ULONG64)Port), Value);
    return;
}

__forceinline
VOID
WRITE_PORT_ULONG (
    PULONG Port,
    ULONG Value
    )

{
    __outdword((USHORT)((ULONG64)Port), Value);
    return;
}

__forceinline
VOID
WRITE_PORT_BUFFER_UCHAR (
    PUCHAR Port,
    PUCHAR Buffer,
    ULONG Count
    )

{
    __outbytestring((USHORT)((ULONG64)Port), Buffer, Count);
    return;
}

__forceinline
VOID
WRITE_PORT_BUFFER_USHORT (
    PUSHORT Port,
    PUSHORT Buffer,
    ULONG Count
    )

{
    __outwordstring((USHORT)((ULONG64)Port), Buffer, Count);
    return;
}

__forceinline
VOID
WRITE_PORT_BUFFER_ULONG (
    PULONG Port,
    PULONG Buffer,
    ULONG Count
    )

{
    __outdwordstring((USHORT)((ULONG64)Port), Buffer, Count);
    return;
}

#endif // defined(_AMD64_) && !defined(_IOACCESS_)

// end_ntminiport


#define KeFlushIoBuffers(Mdl, ReadOperation, DmaOperation)

//
// AMD64 Specific portions of mm component.
//
// Define the page size for the AMD64 as 4096 (0x1000).
//

#define PAGE_SIZE 0x1000

//
// Define the number of trailing zeroes in a page aligned virtual address.
// This is used as the shift count when shifting virtual addresses to
// virtual page numbers.
//

#define PAGE_SHIFT 12L


//++
//
//
// VOID
// KeMemoryBarrier (
//    VOID
//    )
//
// VOID
// KeMemoryBarrierWithoutFence (
//    VOID
//    )
//
//
// Routine Description:
//
//    These functions order memory accesses as seen by other processors.
//
// Arguments:
//
//    None.
//
// Return Value:
//
//    None.
//
//--

#if !defined(_CROSS_PLATFORM_)

#ifdef __cplusplus
extern "C" {
#endif

VOID
_ReadWriteBarrier (
    VOID
    );

#pragma intrinsic(_ReadWriteBarrier)

#ifdef __cplusplus
}
#endif

#define KeMemoryBarrier() MemoryFence()
#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

#else

#define KeMemoryBarrier()
#define KeMemoryBarrierWithoutFence()

#endif


#endif // defined(_AMD64_)


#if defined(_IA64_)
// end_ntddk end_nthal

//
// Types to use to contain PFNs and their counts.
//

typedef ULONG PFN_COUNT;

typedef LONG_PTR SPFN_NUMBER, *PSPFN_NUMBER;
typedef ULONG_PTR PFN_NUMBER, *PPFN_NUMBER;

//
// Indicate that the IA64 compiler supports the pragma textout construct.
//

#define ALLOC_PRAGMA 1

//
// Define intrinsic calls and their prototypes
//

#include "ia64reg.h"


#ifdef __cplusplus
extern "C" {
#endif

unsigned __int64 __getReg (int);
void __setReg (int, unsigned __int64);
void __isrlz (void);
void __dsrlz (void);
void __fwb (void);
void __mf (void);
void __mfa (void);
void __synci (void);
__int64 __thash (__int64);
__int64 __ttag (__int64);
void __ptcl (__int64, __int64);
void __ptcg (__int64, __int64);
void __ptcga (__int64, __int64);
void __ptri (__int64, __int64);
void __ptrd (__int64, __int64);
void __invalat (void);
void __break (int);
void __fc (__int64);
void __fci (__int64);
void __sum (int);
void __rsm (int);
void _ReleaseSpinLock( unsigned __int64 *);
void __yield();
void __lfetch(int, void const *);
void __lfetchfault(int, void const *);

#ifdef _M_IA64
#pragma intrinsic (__getReg)
#pragma intrinsic (__setReg)
#pragma intrinsic (__isrlz)
#pragma intrinsic (__dsrlz)
#pragma intrinsic (__fwb)
#pragma intrinsic (__mf)
#pragma intrinsic (__mfa)
#pragma intrinsic (__synci)
#pragma intrinsic (__thash)
#pragma intrinsic (__ttag)
#pragma intrinsic (__ptcl)
#pragma intrinsic (__ptcg)
#pragma intrinsic (__ptcga)
#pragma intrinsic (__ptri)
#pragma intrinsic (__ptrd)
#pragma intrinsic (__invalat)
#pragma intrinsic (__break)
#pragma intrinsic (__fc)
#pragma intrinsic (__fci)
#pragma intrinsic (__sum)
#pragma intrinsic (__rsm)
#pragma intrinsic (_ReleaseSpinLock)
#pragma intrinsic (__yield)
#pragma intrinsic (__lfetch)
#pragma intrinsic (__lfetchfault)
#endif // _M_IA64

#ifdef __cplusplus
}
#endif




//
//
// VOID
// KeMemoryBarrierWithoutFence (
//    VOID
//    )
//
//
// Routine Description:
//
//    This function cases ordering of memory acceses generated by the compiler.
//
//
// Arguments:
//
//    None.
//
// Return Value:
//
//    None.
//--

#ifdef __cplusplus
extern "C" {
#endif

VOID
_ReadWriteBarrier (
    VOID
    );

#ifdef __cplusplus
}
#endif

#pragma intrinsic(_ReadWriteBarrier)

#define KeMemoryBarrierWithoutFence() _ReadWriteBarrier()

//++
//
//
// VOID
// KeMemoryBarrier (
//    VOID
//    )
//
//
// Routine Description:
//
//    This function cases ordering of memory acceses as generated by the compiler and 
//    as seen by other processors.
//
//
// Arguments:
//
//    None.
//
// Return Value:
//
//    None.
//--

#define KE_MEMORY_BARRIER_REQUIRED

#define KeMemoryBarrier() __mf()

//
// Define the page size
//

#define PAGE_SIZE 0x2000

//
// Define the number of trailing zeroes in a page aligned virtual address.
// This is used as the shift count when shifting virtual addresses to
// virtual page numbers.
//

#define PAGE_SHIFT 13L

//
// Cache and write buffer flush functions.
//

NTKERNELAPI
VOID
KeFlushIoBuffers (
    IN PMDL Mdl,
    IN BOOLEAN ReadOperation,
    IN BOOLEAN DmaOperation
    );

//
// I/O space read and write macros.
//

NTHALAPI
UCHAR
READ_PORT_UCHAR (
    PUCHAR RegisterAddress
    );

NTHALAPI
USHORT
READ_PORT_USHORT (
    PUSHORT RegisterAddress
    );

NTHALAPI
ULONG
READ_PORT_ULONG (
    PULONG RegisterAddress
    );

NTHALAPI
VOID
READ_PORT_BUFFER_UCHAR (
    PUCHAR portAddress,
    PUCHAR readBuffer,
    ULONG  readCount
    );

NTHALAPI
VOID
READ_PORT_BUFFER_USHORT (
    PUSHORT portAddress,
    PUSHORT readBuffer,
    ULONG  readCount
    );

NTHALAPI
VOID
READ_PORT_BUFFER_ULONG (
    PULONG portAddress,
    PULONG readBuffer,
    ULONG  readCount
    );

NTHALAPI
VOID
WRITE_PORT_UCHAR (
    PUCHAR portAddress,
    UCHAR  Data
    );

NTHALAPI
VOID
WRITE_PORT_USHORT (
    PUSHORT portAddress,
    USHORT  Data
    );

NTHALAPI
VOID
WRITE_PORT_ULONG (
    PULONG portAddress,
    ULONG  Data
    );

NTHALAPI
VOID
WRITE_PORT_BUFFER_UCHAR (
    PUCHAR portAddress,
    PUCHAR writeBuffer,
    ULONG  writeCount
    );

NTHALAPI
VOID
WRITE_PORT_BUFFER_USHORT (
    PUSHORT portAddress,
    PUSHORT writeBuffer,
    ULONG  writeCount
    );

NTHALAPI
VOID
WRITE_PORT_BUFFER_ULONG (
    PULONG portAddress,
    PULONG writeBuffer,
    ULONG  writeCount
    );


#define READ_REGISTER_UCHAR(x) \
    (__mf(), *(volatile UCHAR * const)(x))

#define READ_REGISTER_USHORT(x) \
    (__mf(), *(volatile USHORT * const)(x))

#define READ_REGISTER_ULONG(x) \
    (__mf(), *(volatile ULONG * const)(x))

#define READ_REGISTER_BUFFER_UCHAR(x, y, z) {                           \
    PUCHAR registerBuffer = x;                                          \
    PUCHAR readBuffer = y;                                              \
    ULONG readCount;                                                    \
    __mf();                                                             \
    for (readCount = z; readCount--; readBuffer++, registerBuffer++) {  \
        *readBuffer = *(volatile UCHAR * const)(registerBuffer);        \
    }                                                                   \
}

#define READ_REGISTER_BUFFER_USHORT(x, y, z) {                          \
    PUSHORT registerBuffer = x;                                         \
    PUSHORT readBuffer = y;                                             \
    ULONG readCount;                                                    \
    __mf();                                                             \
    for (readCount = z; readCount--; readBuffer++, registerBuffer++) {  \
        *readBuffer = *(volatile USHORT * const)(registerBuffer);       \
    }                                                                   \
}

#define READ_REGISTER_BUFFER_ULONG(x, y, z) {                           \
    PULONG registerBuffer = x;                                          \
    PULONG readBuffer = y;                                              \
    ULONG readCount;                                                    \
    __mf();                                                             \
    for (readCount = z; readCount--; readBuffer++, registerBuffer++) {  \
        *readBuffer = *(volatile ULONG * const)(registerBuffer);        \
    }                                                                   \
}

#define WRITE_REGISTER_UCHAR(x, y) {    \
    *(volatile UCHAR * const)(x) = y;   \
    KeFlushWriteBuffer();               \
}

#define WRITE_REGISTER_USHORT(x, y) {   \
    *(volatile USHORT * const)(x) = y;  \
    KeFlushWriteBuffer();               \
}

#define WRITE_REGISTER_ULONG(x, y) {    \
    *(volatile ULONG * const)(x) = y;   \
    KeFlushWriteBuffer();               \
}

#define WRITE_REGISTER_BUFFER_UCHAR(x, y, z) {                            \
    PUCHAR registerBuffer = x;                                            \
    PUCHAR writeBuffer = y;                                               \
    ULONG writeCount;                                                     \
    for (writeCount = z; writeCount--; writeBuffer++, registerBuffer++) { \
        *(volatile UCHAR * const)(registerBuffer) = *writeBuffer;         \
    }                                                                     \
    KeFlushWriteBuffer();                                                 \
}

#define WRITE_REGISTER_BUFFER_USHORT(x, y, z) {                           \
    PUSHORT registerBuffer = x;                                           \
    PUSHORT writeBuffer = y;                                              \
    ULONG writeCount;                                                     \
    for (writeCount = z; writeCount--; writeBuffer++, registerBuffer++) { \
        *(volatile USHORT * const)(registerBuffer) = *writeBuffer;        \
    }                                                                     \
    KeFlushWriteBuffer();                                                 \
}

#define WRITE_REGISTER_BUFFER_ULONG(x, y, z) {                            \
    PULONG registerBuffer = x;                                            \
    PULONG writeBuffer = y;                                               \
    ULONG writeCount;                                                     \
    for (writeCount = z; writeCount--; writeBuffer++, registerBuffer++) { \
        *(volatile ULONG * const)(registerBuffer) = *writeBuffer;         \
    }                                                                     \
    KeFlushWriteBuffer();                                                 \
}

#endif // defined(_IA64_)

//
// Defines the Type in the RESOURCE_DESCRIPTOR
//
// NOTE:  For all CM_RESOURCE_TYPE values, there must be a
// corresponding ResType value in the 32-bit ConfigMgr headerfile
// (cfgmgr32.h).  Values in the range [0x6,0x80) use the same values
// as their ConfigMgr counterparts.  CM_RESOURCE_TYPE values with
// the high bit set (i.e., in the range [0x80,0xFF]), are
// non-arbitrated resources.  These correspond to the same values
// in cfgmgr32.h that have their high bit set (however, since
// cfgmgr32.h uses 16 bits for ResType values, these values are in
// the range [0x8000,0x807F).  Note that ConfigMgr ResType values
// cannot be in the range [0x8080,0xFFFF), because they would not
// be able to map into CM_RESOURCE_TYPE values.  (0xFFFF itself is
// a special value, because it maps to CmResourceTypeDeviceSpecific.)
//

typedef int CM_RESOURCE_TYPE;

// CmResourceTypeNull is reserved

#define CmResourceTypeNull                0   // ResType_All or ResType_None (0x0000)
#define CmResourceTypePort                1   // ResType_IO (0x0002)
#define CmResourceTypeInterrupt           2   // ResType_IRQ (0x0004)
#define CmResourceTypeMemory              3   // ResType_Mem (0x0001)
#define CmResourceTypeDma                 4   // ResType_DMA (0x0003)
#define CmResourceTypeDeviceSpecific      5   // ResType_ClassSpecific (0xFFFF)
#define CmResourceTypeBusNumber           6   // ResType_BusNumber (0x0006)
// end_wdm
// begin_ntddk
#define CmResourceTypeMaximum             7
// end_ntddk
// begin_wdm
#define CmResourceTypeNonArbitrated     128   // Not arbitrated if 0x80 bit set
#define CmResourceTypeConfigData        128   // ResType_Reserved (0x8000)
#define CmResourceTypeDevicePrivate     129   // ResType_DevicePrivate (0x8001)
#define CmResourceTypePcCardConfig      130   // ResType_PcCardConfig (0x8002)
#define CmResourceTypeMfCardConfig      131   // ResType_MfCardConfig (0x8003)

//
// Defines the ShareDisposition in the RESOURCE_DESCRIPTOR
//

typedef enum _CM_SHARE_DISPOSITION {
    CmResourceShareUndetermined = 0,    // Reserved
    CmResourceShareDeviceExclusive,
    CmResourceShareDriverExclusive,
    CmResourceShareShared
} CM_SHARE_DISPOSITION;

//
// Define the bit masks for Flags when type is CmResourceTypeInterrupt
//

#define CM_RESOURCE_INTERRUPT_LEVEL_SENSITIVE 0
#define CM_RESOURCE_INTERRUPT_LATCHED         1
#define CM_RESOURCE_INTERRUPT_MESSAGE         2
#define CM_RESOURCE_INTERRUPT_POLICY_INCLUDED 4

//
// Define the token value used for an interrupt vector to mean that 
// the vector is message-signaled.  This value is used in the 
// MaximumVector field.
//

#define CM_RESOURCE_INTERRUPT_MESSAGE_TOKEN   ((ULONG)-2)

//
// Define the bit masks for Flags when type is CmResourceTypeMemory
//

#define CM_RESOURCE_MEMORY_READ_WRITE       0x0000
#define CM_RESOURCE_MEMORY_READ_ONLY        0x0001
#define CM_RESOURCE_MEMORY_WRITE_ONLY       0x0002
#define CM_RESOURCE_MEMORY_PREFETCHABLE     0x0004

#define CM_RESOURCE_MEMORY_COMBINEDWRITE    0x0008
#define CM_RESOURCE_MEMORY_24               0x0010
#define CM_RESOURCE_MEMORY_CACHEABLE        0x0020
#define CM_RESOURCE_MEMORY_WINDOW_DECODE    0x0040
#define CM_RESOURCE_MEMORY_BAR              0x0080

//
// Define the bit masks for Flags when type is CmResourceTypePort
//

#define CM_RESOURCE_PORT_MEMORY                             0x0000
#define CM_RESOURCE_PORT_IO                                 0x0001
#define CM_RESOURCE_PORT_10_BIT_DECODE                      0x0004
#define CM_RESOURCE_PORT_12_BIT_DECODE                      0x0008
#define CM_RESOURCE_PORT_16_BIT_DECODE                      0x0010
#define CM_RESOURCE_PORT_POSITIVE_DECODE                    0x0020
#define CM_RESOURCE_PORT_PASSIVE_DECODE                     0x0040
#define CM_RESOURCE_PORT_WINDOW_DECODE                      0x0080
#define CM_RESOURCE_PORT_BAR                                0x0100

//
// Define the bit masks for Flags when type is CmResourceTypeDma
//

#define CM_RESOURCE_DMA_8                   0x0000
#define CM_RESOURCE_DMA_16                  0x0001
#define CM_RESOURCE_DMA_32                  0x0002
#define CM_RESOURCE_DMA_8_AND_16            0x0004
#define CM_RESOURCE_DMA_BUS_MASTER          0x0008
#define CM_RESOURCE_DMA_TYPE_A              0x0010
#define CM_RESOURCE_DMA_TYPE_B              0x0020
#define CM_RESOURCE_DMA_TYPE_F              0x0040


#include "pshpack4.h"
typedef struct _CM_PARTIAL_RESOURCE_DESCRIPTOR {
    UCHAR Type;
    UCHAR ShareDisposition;
    USHORT Flags;
    union {

        //
        // Range of resources, inclusive.  These are physical, bus relative.
        // It is known that Port and Memory below have the exact same layout
        // as Generic.
        //

        struct {
            PHYSICAL_ADDRESS Start;
            ULONG Length;
        } Generic;

        //
        // Range of port numbers, inclusive. These are physical, bus
        // relative. The value should be the same as the one passed to
        // HalTranslateBusAddress().
        // begin_wdm
        //

        struct {
            PHYSICAL_ADDRESS Start;
            ULONG Length;
        } Port;

        //
        // end_wdm 
        // IRQL and vector. Should be same values as were passed to
        // HalGetInterruptVector().
        // begin_wdm 
        //

        struct {
            ULONG Level;
            ULONG Vector;
            KAFFINITY Affinity;
        } Interrupt;

        //
        // Values for message-signaled interrupts are distinct in the
        // raw and translated cases.
        //
        
        struct {
            union {
               struct {
                   USHORT DataPayload;
                   USHORT MessageCount;
                   ULONG  Vector;
                   ULONG_PTR MessageTargetAddress;
               } Raw;
               
               struct {
                   ULONG Level;
                   ULONG Vector;
                   KAFFINITY Affinity;
               } Translated;        
            };
        } MessageInterrupt;

        //
        // Range of memory addresses, inclusive. These are physical, bus
        // relative. The value should be the same as the one passed to
        // HalTranslateBusAddress().
        //

        struct {
            PHYSICAL_ADDRESS Start;    // 64 bit physical addresses.
            ULONG Length;
        } Memory;

        //
        // Physical DMA channel.
        //

        struct {
            ULONG Channel;
            ULONG Port;
            ULONG Reserved1;
        } Dma;

        //
        // Device driver private data, usually used to help it figure
        // what the resource assignments decisions that were made.
        //

        struct {
            ULONG Data[3];
        } DevicePrivate;

        //
        // Bus Number information.
        //

        struct {
            ULONG Start;
            ULONG Length;
            ULONG Reserved;
        } BusNumber;

        //
        // Device Specific information defined by the driver.
        // The DataSize field indicates the size of the data in bytes. The
        // data is located immediately after the DeviceSpecificData field in
        // the structure.
        //

        struct {
            ULONG DataSize;
            ULONG Reserved1;
            ULONG Reserved2;
        } DeviceSpecificData;
    } u;
} CM_PARTIAL_RESOURCE_DESCRIPTOR, *PCM_PARTIAL_RESOURCE_DESCRIPTOR;
#include "poppack.h"

//
// A Partial Resource List is what can be found in the ARC firmware
// or will be generated by ntdetect.com.
// The configuration manager will transform this structure into a Full
// resource descriptor when it is about to store it in the regsitry.
//
// Note: There must a be a convention to the order of fields of same type,
// (defined on a device by device basis) so that the fields can make sense
// to a driver (i.e. when multiple memory ranges are necessary).
//

typedef struct _CM_PARTIAL_RESOURCE_LIST {
    USHORT Version;
    USHORT Revision;
    ULONG Count;
    CM_PARTIAL_RESOURCE_DESCRIPTOR PartialDescriptors[1];
} CM_PARTIAL_RESOURCE_LIST, *PCM_PARTIAL_RESOURCE_LIST;

//
// A Full Resource Descriptor is what can be found in the registry.
// This is what will be returned to a driver when it queries the registry
// to get device information; it will be stored under a key in the hardware
// description tree.
//
// end_wdm
// Note: The BusNumber and Type are redundant information, but we will keep
// it since it allows the driver _not_ to append it when it is creating
// a resource list which could possibly span multiple buses.
//
// begin_wdm
// Note: There must a be a convention to the order of fields of same type,
// (defined on a device by device basis) so that the fields can make sense
// to a driver (i.e. when multiple memory ranges are necessary).
//

typedef struct _CM_FULL_RESOURCE_DESCRIPTOR {
    INTERFACE_TYPE InterfaceType; // unused for WDM
    ULONG BusNumber; // unused for WDM
    CM_PARTIAL_RESOURCE_LIST PartialResourceList;
} CM_FULL_RESOURCE_DESCRIPTOR, *PCM_FULL_RESOURCE_DESCRIPTOR;

//
// The Resource list is what will be stored by the drivers into the
// resource map via the IO API.
//

typedef struct _CM_RESOURCE_LIST {
    ULONG Count;
    CM_FULL_RESOURCE_DESCRIPTOR List[1];
} CM_RESOURCE_LIST, *PCM_RESOURCE_LIST;


#include "pshpack1.h"


//
// Define Mca POS data block for slot
//

typedef struct _CM_MCA_POS_DATA {
    USHORT AdapterId;
    UCHAR PosData1;
    UCHAR PosData2;
    UCHAR PosData3;
    UCHAR PosData4;
} CM_MCA_POS_DATA, *PCM_MCA_POS_DATA;

//
// Memory configuration of eisa data block structure
//

typedef struct _EISA_MEMORY_TYPE {
    UCHAR ReadWrite: 1;
    UCHAR Cached : 1;
    UCHAR Reserved0 :1;
    UCHAR Type:2;
    UCHAR Shared:1;
    UCHAR Reserved1 :1;
    UCHAR MoreEntries : 1;
} EISA_MEMORY_TYPE, *PEISA_MEMORY_TYPE;

typedef struct _EISA_MEMORY_CONFIGURATION {
    EISA_MEMORY_TYPE ConfigurationByte;
    UCHAR DataSize;
    USHORT AddressLowWord;
    UCHAR AddressHighByte;
    USHORT MemorySize;
} EISA_MEMORY_CONFIGURATION, *PEISA_MEMORY_CONFIGURATION;


//
// Interrupt configurationn of eisa data block structure
//

typedef struct _EISA_IRQ_DESCRIPTOR {
    UCHAR Interrupt : 4;
    UCHAR Reserved :1;
    UCHAR LevelTriggered :1;
    UCHAR Shared : 1;
    UCHAR MoreEntries : 1;
} EISA_IRQ_DESCRIPTOR, *PEISA_IRQ_DESCRIPTOR;

typedef struct _EISA_IRQ_CONFIGURATION {
    EISA_IRQ_DESCRIPTOR ConfigurationByte;
    UCHAR Reserved;
} EISA_IRQ_CONFIGURATION, *PEISA_IRQ_CONFIGURATION;


//
// DMA description of eisa data block structure
//

typedef struct _DMA_CONFIGURATION_BYTE0 {
    UCHAR Channel : 3;
    UCHAR Reserved : 3;
    UCHAR Shared :1;
    UCHAR MoreEntries :1;
} DMA_CONFIGURATION_BYTE0;

typedef struct _DMA_CONFIGURATION_BYTE1 {
    UCHAR Reserved0 : 2;
    UCHAR TransferSize : 2;
    UCHAR Timing : 2;
    UCHAR Reserved1 : 2;
} DMA_CONFIGURATION_BYTE1;

typedef struct _EISA_DMA_CONFIGURATION {
    DMA_CONFIGURATION_BYTE0 ConfigurationByte0;
    DMA_CONFIGURATION_BYTE1 ConfigurationByte1;
} EISA_DMA_CONFIGURATION, *PEISA_DMA_CONFIGURATION;


//
// Port description of eisa data block structure
//

typedef struct _EISA_PORT_DESCRIPTOR {
    UCHAR NumberPorts : 5;
    UCHAR Reserved :1;
    UCHAR Shared :1;
    UCHAR MoreEntries : 1;
} EISA_PORT_DESCRIPTOR, *PEISA_PORT_DESCRIPTOR;

typedef struct _EISA_PORT_CONFIGURATION {
    EISA_PORT_DESCRIPTOR Configuration;
    USHORT PortAddress;
} EISA_PORT_CONFIGURATION, *PEISA_PORT_CONFIGURATION;


//
// Eisa slot information definition
// N.B. This structure is different from the one defined
//      in ARC eisa addendum.
//

typedef struct _CM_EISA_SLOT_INFORMATION {
    UCHAR ReturnCode;
    UCHAR ReturnFlags;
    UCHAR MajorRevision;
    UCHAR MinorRevision;
    USHORT Checksum;
    UCHAR NumberFunctions;
    UCHAR FunctionInformation;
    ULONG CompressedId;
} CM_EISA_SLOT_INFORMATION, *PCM_EISA_SLOT_INFORMATION;


//
// Eisa function information definition
//

typedef struct _CM_EISA_FUNCTION_INFORMATION {
    ULONG CompressedId;
    UCHAR IdSlotFlags1;
    UCHAR IdSlotFlags2;
    UCHAR MinorRevision;
    UCHAR MajorRevision;
    UCHAR Selections[26];
    UCHAR FunctionFlags;
    UCHAR TypeString[80];
    EISA_MEMORY_CONFIGURATION EisaMemory[9];
    EISA_IRQ_CONFIGURATION EisaIrq[7];
    EISA_DMA_CONFIGURATION EisaDma[4];
    EISA_PORT_CONFIGURATION EisaPort[20];
    UCHAR InitializationData[60];
} CM_EISA_FUNCTION_INFORMATION, *PCM_EISA_FUNCTION_INFORMATION;

//
// The following defines the way pnp bios information is stored in
// the registry \\HKEY_LOCAL_MACHINE\HARDWARE\Description\System\MultifunctionAdapter\x
// key, where x is an integer number indicating adapter instance. The
// "Identifier" of the key must equal to "PNP BIOS" and the
// "ConfigurationData" is organized as follow:
//
//      CM_PNP_BIOS_INSTALLATION_CHECK        +
//      CM_PNP_BIOS_DEVICE_NODE for device 1  +
//      CM_PNP_BIOS_DEVICE_NODE for device 2  +
//                ...
//      CM_PNP_BIOS_DEVICE_NODE for device n
//

//
// Pnp BIOS device node structure
//

typedef struct _CM_PNP_BIOS_DEVICE_NODE {
    USHORT Size;
    UCHAR Node;
    ULONG ProductId;
    UCHAR DeviceType[3];
    USHORT DeviceAttributes;
    // followed by AllocatedResourceBlock, PossibleResourceBlock
    // and CompatibleDeviceId
} CM_PNP_BIOS_DEVICE_NODE,*PCM_PNP_BIOS_DEVICE_NODE;

//
// Pnp BIOS Installation check
//

typedef struct _CM_PNP_BIOS_INSTALLATION_CHECK {
    UCHAR Signature[4];             // $PnP (ascii)
    UCHAR Revision;
    UCHAR Length;
    USHORT ControlField;
    UCHAR Checksum;
    ULONG EventFlagAddress;         // Physical address
    USHORT RealModeEntryOffset;
    USHORT RealModeEntrySegment;
    USHORT ProtectedModeEntryOffset;
    ULONG ProtectedModeCodeBaseAddress;
    ULONG OemDeviceId;
    USHORT RealModeDataBaseAddress;
    ULONG ProtectedModeDataBaseAddress;
} CM_PNP_BIOS_INSTALLATION_CHECK, *PCM_PNP_BIOS_INSTALLATION_CHECK;

#include "poppack.h"

//
// Masks for EISA function information
//

#define EISA_FUNCTION_ENABLED                   0x80
#define EISA_FREE_FORM_DATA                     0x40
#define EISA_HAS_PORT_INIT_ENTRY                0x20
#define EISA_HAS_PORT_RANGE                     0x10
#define EISA_HAS_DMA_ENTRY                      0x08
#define EISA_HAS_IRQ_ENTRY                      0x04
#define EISA_HAS_MEMORY_ENTRY                   0x02
#define EISA_HAS_TYPE_ENTRY                     0x01
#define EISA_HAS_INFORMATION                    EISA_HAS_PORT_RANGE + \
                                                EISA_HAS_DMA_ENTRY + \
                                                EISA_HAS_IRQ_ENTRY + \
                                                EISA_HAS_MEMORY_ENTRY + \
                                                EISA_HAS_TYPE_ENTRY

//
// Masks for EISA memory configuration
//

#define EISA_MORE_ENTRIES                       0x80
#define EISA_SYSTEM_MEMORY                      0x00
#define EISA_MEMORY_TYPE_RAM                    0x01

//
// Returned error code for EISA bios call
//

#define EISA_INVALID_SLOT                       0x80
#define EISA_INVALID_FUNCTION                   0x81
#define EISA_INVALID_CONFIGURATION              0x82
#define EISA_EMPTY_SLOT                         0x83
#define EISA_INVALID_BIOS_CALL                  0x86


//
// Interrupt modes.
//

typedef enum _KINTERRUPT_MODE {
    LevelSensitive,
    Latched
} KINTERRUPT_MODE;

typedef enum  {
    InterruptPolarityUnknown,
    InterruptActiveHigh,
    InterruptActiveLow
} KINTERRUPT_POLARITY, *PKINTERRUPT_POLARITY;

typedef struct _KINTERRUPT *PKINTERRUPT, *PRKINTERRUPT; 

//
// On X86 the following routines are defined in the HAL and imported by
// all other modules.
//

#if defined(_X86_) && !defined(_NTHAL_)

#define _DECL_HAL_KE_IMPORT  __declspec(dllimport)

#else

#define _DECL_HAL_KE_IMPORT

#endif

//
// spin lock functions
//

#if defined(_X86_) && (defined(_WDM_INCLUDED_) || defined(WIN9X_COMPAT_SPINLOCK))

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
NTAPI
KeInitializeSpinLock (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#else

__inline
VOID
NTAPI
KeInitializeSpinLock (
    IN PKSPIN_LOCK SpinLock
    ) 
{
    *SpinLock = 0;
}

#endif

// begin_nthal
#if defined(_X86_) // ntifs

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
FASTCALL
KefAcquireSpinLockAtDpcLevel (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
FASTCALL
KefReleaseSpinLockFromDpcLevel (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#define KeAcquireSpinLockAtDpcLevel(a)      KefAcquireSpinLockAtDpcLevel(a)
#define KeReleaseSpinLockFromDpcLevel(a)    KefReleaseSpinLockFromDpcLevel(a)

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_DECL_HAL_KE_IMPORT
KIRQL
FASTCALL
KfAcquireSpinLock (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
_DECL_HAL_KE_IMPORT
VOID
FASTCALL
KfReleaseSpinLock (
    IN PKSPIN_LOCK SpinLock,
    IN KIRQL NewIrql
    );
#endif
// end_wdm
// begin_ntifs
#if (NTDDI_VERSION >= NTDDI_WIN2K)
_DECL_HAL_KE_IMPORT
KIRQL
FASTCALL
KeAcquireSpinLockRaiseToSynch (
    IN PKSPIN_LOCK SpinLock
    );
#endif
// end_ntifs
// begin_wdm

#define KeAcquireSpinLock(a,b)  *(b) = KfAcquireSpinLock(a)
#define KeReleaseSpinLock(a,b)  KfReleaseSpinLock(a,b)

#if (NTDDI_VERSION >= NTDDI_WS03)
NTKERNELAPI
BOOLEAN
FASTCALL
KeTestSpinLock (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTKERNELAPI
BOOLEAN
FASTCALL
KeTryToAcquireSpinLockAtDpcLevel (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#else // ntifs

//
// These functions are imported for IA64, ntddk, ntifs, nthal, ntosp, and wdm.
// They can be inlined for the system on AMD64.
//

#define KeAcquireSpinLock(SpinLock, OldIrql) \
    *(OldIrql) = KeAcquireSpinLockRaiseToDpc(SpinLock)

// begin_ntifs
#if defined(_IA64_) || defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_) || defined(_WDMDDK_)
// end_ntifs
// end_wdm 
// begin_ntifs

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
KIRQL
FASTCALL
KeAcquireSpinLockRaiseToSynch (
    IN PKSPIN_LOCK SpinLock
    );
#endif

// end_ntifs
// begin_wdm 
#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
KeAcquireSpinLockAtDpcLevel (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
KIRQL
KeAcquireSpinLockRaiseToDpc (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
KeReleaseSpinLock (
    IN PKSPIN_LOCK SpinLock,
    IN KIRQL NewIrql
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
KeReleaseSpinLockFromDpcLevel (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTKERNELAPI
BOOLEAN
FASTCALL
KeTestSpinLock (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTKERNELAPI
BOOLEAN
FASTCALL
KeTryToAcquireSpinLockAtDpcLevel (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#else

#if defined(_AMD64_)

//
// The system version of these functions are defined in amd64.h for AMD64.
//

#endif // _AMD64_

// begin_ntifs
#endif // _IA64_ || _NTDRIVER_ || _NTDDK_ || _NTIFS_ || _NTHAL_ || _NTOSP_ || _WDMDDK_

#endif
// end_ntifs 
// end_nthal 
// end_wdm

// begin_wdm

#if (NTDDI_VERSION >= NTDDI_LONGHORN)
NTKERNELAPI
KIRQL
FASTCALL
KeAcquireSpinLockForDpc (
    IN PKSPIN_LOCK SpinLock
    );
#endif

#if (NTDDI_VERSION >= NTDDI_LONGHORN)
NTKERNELAPI
VOID
FASTCALL
KeReleaseSpinLockForDpc (
    IN PKSPIN_LOCK SpinLock,
    IN KIRQL OldIrql
    );
#endif

// end_wdm
//
// Define I/O system data structure type codes.  Each major data structure in
// the I/O system has a type code  The type field in each structure is at the
// same offset.  The following values can be used to determine which type of
// data structure a pointer refers to.
//

#define IO_TYPE_ADAPTER                 0x00000001
#define IO_TYPE_CONTROLLER              0x00000002
#define IO_TYPE_DEVICE                  0x00000003
#define IO_TYPE_DRIVER                  0x00000004
#define IO_TYPE_FILE                    0x00000005
#define IO_TYPE_IRP                     0x00000006
#define IO_TYPE_MASTER_ADAPTER          0x00000007
#define IO_TYPE_OPEN_PACKET             0x00000008
#define IO_TYPE_TIMER                   0x00000009
#define IO_TYPE_VPB                     0x0000000a
#define IO_TYPE_ERROR_LOG               0x0000000b
#define IO_TYPE_ERROR_MESSAGE           0x0000000c
#define IO_TYPE_DEVICE_OBJECT_EXTENSION 0x0000000d


//
// Define the major function codes for IRPs.
//


#define IRP_MJ_CREATE                   0x00
#define IRP_MJ_CREATE_NAMED_PIPE        0x01
#define IRP_MJ_CLOSE                    0x02
#define IRP_MJ_READ                     0x03
#define IRP_MJ_WRITE                    0x04
#define IRP_MJ_QUERY_INFORMATION        0x05
#define IRP_MJ_SET_INFORMATION          0x06
#define IRP_MJ_QUERY_EA                 0x07
#define IRP_MJ_SET_EA                   0x08
#define IRP_MJ_FLUSH_BUFFERS            0x09
#define IRP_MJ_QUERY_VOLUME_INFORMATION 0x0a
#define IRP_MJ_SET_VOLUME_INFORMATION   0x0b
#define IRP_MJ_DIRECTORY_CONTROL        0x0c
#define IRP_MJ_FILE_SYSTEM_CONTROL      0x0d
#define IRP_MJ_DEVICE_CONTROL           0x0e
#define IRP_MJ_INTERNAL_DEVICE_CONTROL  0x0f
#define IRP_MJ_SHUTDOWN                 0x10
#define IRP_MJ_LOCK_CONTROL             0x11
#define IRP_MJ_CLEANUP                  0x12
#define IRP_MJ_CREATE_MAILSLOT          0x13
#define IRP_MJ_QUERY_SECURITY           0x14
#define IRP_MJ_SET_SECURITY             0x15
#define IRP_MJ_POWER                    0x16
#define IRP_MJ_SYSTEM_CONTROL           0x17
#define IRP_MJ_DEVICE_CHANGE            0x18
#define IRP_MJ_QUERY_QUOTA              0x19
#define IRP_MJ_SET_QUOTA                0x1a
#define IRP_MJ_PNP                      0x1b
#define IRP_MJ_PNP_POWER                IRP_MJ_PNP      // Obsolete....
#define IRP_MJ_MAXIMUM_FUNCTION         0x1b

//
// Make the Scsi major code the same as internal device control.
//

#define IRP_MJ_SCSI                     IRP_MJ_INTERNAL_DEVICE_CONTROL

//
// Define the minor function codes for IRPs.  The lower 128 codes, from 0x00 to
// 0x7f are reserved to Microsoft.  The upper 128 codes, from 0x80 to 0xff, are
// reserved to customers of Microsoft.
//

#if (NTDDI_VERSION >= NTDDI_LONGHORN)

typedef struct _FILE_OBJECT_WINLH FILE_OBJECT, *PFILE_OBJECT_WINLH; 

#elif (NTDDI_VERSION >= NTDDI_WIN2K)

typedef struct _FILE_OBJECT_WIN2K FILE_OBJECT, *PFILE_OBJECT_WIN2K;
#endif

typedef FILE_OBJECT *PFILE_OBJECT;
typedef FILE_OBJECT _FILE_OBJECT;
//
// Define driver cancel routine type.
//

typedef
VOID
(*PDRIVER_CANCEL) (
    IN struct _DEVICE_OBJECT *DeviceObject,
    IN struct _IRP *Irp
    );

//
// Define driver dispatch routine type.
//

typedef
NTSTATUS
(*PDRIVER_DISPATCH) (
    IN struct _DEVICE_OBJECT *DeviceObject,
    IN struct _IRP *Irp
    );

//
// Define driver start I/O routine type.
//

typedef
VOID
(*PDRIVER_STARTIO) (
    IN struct _DEVICE_OBJECT *DeviceObject,
    IN struct _IRP *Irp
    );

//
// Define driver unload routine type.
//
typedef
VOID
(*PDRIVER_UNLOAD) (
    IN struct _DRIVER_OBJECT *DriverObject
    );
//
// Define driver AddDevice routine type.
//

typedef
NTSTATUS
(*PDRIVER_ADD_DEVICE) (
    IN struct _DRIVER_OBJECT *DriverObject,
    IN struct _DEVICE_OBJECT *PhysicalDeviceObject
    );

typedef struct _ADAPTER_OBJECT *PADAPTER_OBJECT; 
typedef struct _DEVICE_OBJECT *PDEVICE_OBJECT; 
typedef struct _DRIVER_OBJECT *PDRIVER_OBJECT; 

#if defined(_WIN64)
#define POINTER_ALIGNMENT DECLSPEC_ALIGN(8)
#else
#define POINTER_ALIGNMENT
#endif

#if defined(_IA64_)                             
                                                
#if (NTDDI_VERSION >= NTDDI_WIN2K)
DECLSPEC_DEPRECATED_DDK                 // Use GetDmaRequirement
NTHALAPI
ULONG
HalGetDmaAlignmentRequirement (
    VOID
    );
#endif
#endif                                          
                                                
#if defined(_M_IX86) || defined(_M_AMD64)       
                                                
#define HalGetDmaAlignmentRequirement() 1L      
#endif                                          
                                                

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTHALAPI                    
VOID                        
KeFlushWriteBuffer (        
    VOID                    
    );
#endif
//
// Stall processor execution function.
//

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTHALAPI
VOID
KeStallExecutionProcessor (
    IN ULONG MicroSeconds
    );
#endif
typedef struct _MAP_REGISTER_ENTRY {
    PVOID   MapRegister;
    BOOLEAN WriteToDevice;
} MAP_REGISTER_ENTRY, *PMAP_REGISTER_ENTRY;

typedef struct _SCATTER_GATHER_ELEMENT {
    PHYSICAL_ADDRESS Address;
    ULONG Length;
    ULONG_PTR Reserved;
} SCATTER_GATHER_ELEMENT, *PSCATTER_GATHER_ELEMENT;

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4200)
typedef struct _SCATTER_GATHER_LIST {
    ULONG NumberOfElements;
    ULONG_PTR Reserved;
    SCATTER_GATHER_ELEMENT Elements[];
} SCATTER_GATHER_LIST, *PSCATTER_GATHER_LIST;
#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning(default:4200)
#endif

//
// Pool Allocation routines (in pool.c)
//

typedef enum _POOL_TYPE {
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS,
    MaxPoolType,
    //
    // Note these per session types are carefully chosen so that the appropriate
    // masking still applies as well as MaxPoolType above.
    //

    NonPagedPoolSession = 32,
    PagedPoolSession = NonPagedPoolSession + 1,
    NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
    DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
    NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
    PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
    NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,

    } POOL_TYPE;

#define POOL_COLD_ALLOCATION 256     // Note this cannot encode into the header.

//

#if defined(_WIN64)

#define ExInterlockedAddLargeStatistic(Addend, Increment)                   \
    (VOID) InterlockedAdd64(&(Addend)->QuadPart, Increment)

#else

#ifdef __cplusplus
extern "C" {
#endif

LONG
_InterlockedAddLargeStatistic (
    IN PLONGLONG Addend,
    IN ULONG Increment
    );

#ifdef __cplusplus
}
#endif

#pragma intrinsic (_InterlockedAddLargeStatistic)

#define ExInterlockedAddLargeStatistic(Addend,Increment)                     \
    (VOID) _InterlockedAddLargeStatistic ((PLONGLONG)&(Addend)->QuadPart, Increment)

#endif // defined(_WIN64)

//
// Define interlocked sequenced listhead functions.
//
// A sequenced interlocked list is a singly linked list with a header that
// contains the current depth and a sequence number. Each time an entry is
// inserted or removed from the list the depth is updated and the sequence
// number is incremented. This enables AMD64, IA64, and Pentium and later
// machines to insert and remove from the list without the use of spinlocks.
//

#if !defined(_WINBASE_)

/*++

Routine Description:

    This function initializes a sequenced singly linked listhead.

Arguments:

    SListHead - Supplies a pointer to a sequenced singly linked listhead.

Return Value:

    None.

--*/

#if defined(_WIN64) && (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))

NTKERNELAPI
VOID
InitializeSListHead (
    IN PSLIST_HEADER SListHead
    );

#else

__inline
VOID
InitializeSListHead (
    IN PSLIST_HEADER SListHead
    )

{

#ifdef _WIN64

    //
    // Slist headers must be 16 byte aligned.
    //

    if ((ULONG_PTR) SListHead & 0x0f) {

        DbgPrint( "InitializeSListHead unaligned Slist header.  Address = %p, Caller = %p\n", SListHead, _ReturnAddress());
        RtlRaiseStatus(STATUS_DATATYPE_MISALIGNMENT);
    }

#endif

    SListHead->Alignment = 0;

    //
    // For IA-64 we save the region number of the elements of the list in a
    // separate field.  This imposes the requirement that all elements stored
    // in the list are from the same region.

#if defined(_IA64_)

    SListHead->Region = (ULONG_PTR)SListHead & VRN_MASK;

#elif defined(_AMD64_)

    SListHead->Region = 0;

#endif

    return;
}

#endif

#endif // !defined(_WINBASE_)

#define ExInitializeSListHead InitializeSListHead

#if (NTDDI_VERSION >= NTDDI_WINXP)
PSLIST_ENTRY
FirstEntrySList (
    IN const SLIST_HEADER *SListHead
    );
#endif     

/*++

Routine Description:

    This function queries the current number of entries contained in a
    sequenced single linked list.

Arguments:

    SListHead - Supplies a pointer to the sequenced listhead which is
        be queried.

Return Value:

    The current number of entries in the sequenced singly linked list is
    returned as the function value.

--*/

#if defined(_WIN64)

#if (defined(_NTDRIVER_) || defined(_NTDDK_) || defined(_NTIFS_) || defined(_NTHAL_) || defined(_NTOSP_))

NTKERNELAPI
USHORT
ExQueryDepthSList (
    IN PSLIST_HEADER SListHead
    );

#else

__inline
USHORT
ExQueryDepthSList (
    IN PSLIST_HEADER SListHead
    )

{

    return (USHORT)(SListHead->Alignment & 0xffff);
}

#endif

#else

FORCEINLINE
USHORT
ExQueryDepthSList (
    IN PSLIST_HEADER SListHead
    )
{
    return SListHead->Depth;
}

#endif

#if defined(_WIN64)

#define ExInterlockedPopEntrySList(Head, Lock) \
    ExpInterlockedPopEntrySList(Head)

#define ExInterlockedPushEntrySList(Head, Entry, Lock) \
    ExpInterlockedPushEntrySList(Head, Entry)

#define ExInterlockedFlushSList(Head) \
    ExpInterlockedFlushSList(Head)

#if !defined(_WINBASE_)

#define InterlockedPopEntrySList(Head) \
    ExpInterlockedPopEntrySList(Head)

#define InterlockedPushEntrySList(Head, Entry) \
    ExpInterlockedPushEntrySList(Head, Entry)

#define InterlockedFlushSList(Head) \
    ExpInterlockedFlushSList(Head)

#define QueryDepthSList(Head) \
    ExQueryDepthSList(Head)

#endif // !defined(_WINBASE_)

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedPopEntrySList (
    IN PSLIST_HEADER ListHead
    );

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedPushEntrySList (
    IN PSLIST_HEADER ListHead,
    IN PSLIST_ENTRY ListEntry
    );

NTKERNELAPI
PSLIST_ENTRY
ExpInterlockedFlushSList (
    IN PSLIST_HEADER ListHead
    );

#else

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
ExInterlockedPopEntrySList (
    IN PSLIST_HEADER ListHead,
    IN PKSPIN_LOCK Lock
    );

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
ExInterlockedPushEntrySList (
    IN PSLIST_HEADER ListHead,
    IN PSLIST_ENTRY ListEntry,
    IN PKSPIN_LOCK Lock
    );

#else

#define ExInterlockedPopEntrySList(ListHead, Lock) \
    InterlockedPopEntrySList(ListHead)

#define ExInterlockedPushEntrySList(ListHead, ListEntry, Lock) \
    InterlockedPushEntrySList(ListHead, ListEntry)

#endif

NTKERNELAPI
PSLIST_ENTRY
FASTCALL
ExInterlockedFlushSList (
    IN PSLIST_HEADER ListHead
    );

#if !defined(_WINBASE_)

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTKERNELAPI
PSLIST_ENTRY
FASTCALL
InterlockedPopEntrySList (
    IN PSLIST_HEADER ListHead
    );
#endif // NTDDI_VERSION >= NTDDI_WINXP

#if (NTDDI_VERSION >= NTDDI_WINXP)
NTKERNELAPI
PSLIST_ENTRY
FASTCALL
InterlockedPushEntrySList (
    IN PSLIST_HEADER ListHead,
    IN PSLIST_ENTRY ListEntry
    );
#endif // NTDDI_VERSION >= NTDDI_WINXP

#define InterlockedFlushSList(Head) \
    ExInterlockedFlushSList(Head)

#define QueryDepthSList(Head) \
    ExQueryDepthSList(Head)

#endif // !defined(_WINBASE_)

#endif // defined(_WIN64)

// end_wdm end_ntosp
// begin_ntifs begin_nthal

#if (NTDDI_VERSION >= NTDDI_WINXP)
PSLIST_ENTRY
FASTCALL
InterlockedPushListSList (
    IN PSLIST_HEADER ListHead,
    IN PSLIST_ENTRY List,
    IN PSLIST_ENTRY ListEnd,
    IN ULONG Count
    );
#endif // NTDDI_VERSION >= NTDDI_WINXP

//
// Define interlocked lookaside list structure and allocation functions.
//

#if (NTDDI_VERSION >= NTDDI_WIN2K)
VOID
ExAdjustLookasideDepth (
    VOID
    );
#endif

// end_ntifs end_nthal
// begin_wdm begin_ntosp

typedef
PVOID
(*PALLOCATE_FUNCTION) (
    IN POOL_TYPE PoolType,
    IN SIZE_T NumberOfBytes,
    IN ULONG Tag
    );

typedef
VOID
(*PFREE_FUNCTION) (
    IN PVOID Buffer
    );

#if !defined(_WIN64) && (defined(_NTDDK_) || defined(_NTIFS_) || defined(_NDIS_))

typedef struct _GENERAL_LOOKASIDE {

#else

typedef struct DECLSPEC_CACHEALIGN _GENERAL_LOOKASIDE {

#endif

    SLIST_HEADER ListHead;
    USHORT Depth;
    USHORT MaximumDepth;
    ULONG TotalAllocates;
    union {
        ULONG AllocateMisses;
        ULONG AllocateHits;
    };

    ULONG TotalFrees;
    union {
        ULONG FreeMisses;
        ULONG FreeHits;
    };

    POOL_TYPE Type;
    ULONG Tag;
    ULONG Size;
    PALLOCATE_FUNCTION Allocate;
    PFREE_FUNCTION Free;
    LIST_ENTRY ListEntry;
    ULONG LastTotalAllocates;
    union {
        ULONG LastAllocateMisses;
        ULONG LastAllocateHits;
    };

    ULONG Future[2];
} GENERAL_LOOKASIDE, *PGENERAL_LOOKASIDE;

#if !defined(_WIN64) && (defined(_NTDDK_) || defined(_NTIFS_) || defined(_NDIS_))

typedef struct _NPAGED_LOOKASIDE_LIST {

#else

typedef struct DECLSPEC_CACHEALIGN _NPAGED_LOOKASIDE_LIST {

#endif

    GENERAL_LOOKASIDE L;

#if !defined(_AMD64_) && !defined(_IA64_)

    KSPIN_LOCK Lock__ObsoleteButDoNotDelete;

#endif

} NPAGED_LOOKASIDE_LIST, *PNPAGED_LOOKASIDE_LIST;

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
ExInitializeNPagedLookasideList (
    IN PNPAGED_LOOKASIDE_LIST Lookaside,
    IN PALLOCATE_FUNCTION Allocate,
    IN PFREE_FUNCTION Free,
    IN ULONG Flags,
    IN SIZE_T Size,
    IN ULONG Tag,
    IN USHORT Depth
    );
#endif

#if (NTDDI_VERSION >= NTDDI_WIN2K)
NTKERNELAPI
VOID
ExDeleteNPagedLookasideList (
    IN PNPAGED_LOOKASIDE_LIST Lookaside
    );
#endif

__inline
PVOID
ExAllocateFromNPagedLookasideList(
    IN PNPAGED_LOOKASIDE_LIST Lookaside
    )

/*++

Routine Description:

    This function removes (pops) the first entry from the specified
    nonpaged lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a nonpaged lookaside list structure.

Return Value:

    If an entry is removed from the specified lookaside list, then the
    address of the entry is returned as the function value. Otherwise,
    NULL is returned.

--*/

{

    PVOID Entry;

    Lookaside->L.TotalAllocates += 1;

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

    Entry = ExInterlockedPopEntrySList(&Lookaside->L.ListHead,
                                       &Lookaside->Lock__ObsoleteButDoNotDelete);


#else

    Entry = InterlockedPopEntrySList(&Lookaside->L.ListHead);

#endif

    if (Entry == NULL) {
        Lookaside->L.AllocateMisses += 1;
        Entry = (Lookaside->L.Allocate)(Lookaside->L.Type,
                                        Lookaside->L.Size,
                                        Lookaside->L.Tag);
    }

    return Entry;
}

__inline
VOID
ExFreeToNPagedLookasideList(
    IN PNPAGED_LOOKASIDE_LIST Lookaside,
    IN PVOID Entry
    )

/*++

Routine Description:

    This function inserts (pushes) the specified entry into the specified
    nonpaged lookaside list.

Arguments:

    Lookaside - Supplies a pointer to a nonpaged lookaside list structure.

    Entry - Supples a pointer to the entry that is inserted in the
        lookaside list.

Return Value:

    None.

--*/

{

    Lookaside->L.TotalFrees += 1;
    if (ExQueryDepthSList(&Lookaside->L.ListHead) >= Lookaside->L.Depth) {
        Lookaside->L.FreeMisses += 1;
        (Lookaside->L.Free)(Entry);

    } else {

#if defined(_WIN2K_COMPAT_SLIST_USAGE) && defined(_X86_)

        ExInterlockedPushEntrySList(&Lookaside->L.ListHead,
                                    (PSLIST_ENTRY)Entry,
                                    &Lookaside->Lock__ObsoleteButDoNotDelete);

#else

        InterlockedPushEntrySList(&Lookaside->L.ListHead,
                                  (PSLIST_ENTRY)Entry);

#endif

    }
    return;
}


typedef struct _PCI_SLOT_NUMBER {
    union {
        struct {
            ULONG   DeviceNumber:5;
            ULONG   FunctionNumber:3;
            ULONG   Reserved:24;
        } bits;
        ULONG   AsULONG;
    } u;
} PCI_SLOT_NUMBER, *PPCI_SLOT_NUMBER;


#define PCI_TYPE0_ADDRESSES             6
#define PCI_TYPE1_ADDRESSES             2
#define PCI_TYPE2_ADDRESSES             5

typedef struct _PCI_COMMON_CONFIG {
    USHORT  VendorID;                   // (ro)
    USHORT  DeviceID;                   // (ro)
    USHORT  Command;                    // Device control
    USHORT  Status;
    UCHAR   RevisionID;                 // (ro)
    UCHAR   ProgIf;                     // (ro)
    UCHAR   SubClass;                   // (ro)
    UCHAR   BaseClass;                  // (ro)
    UCHAR   CacheLineSize;              // (ro+)
    UCHAR   LatencyTimer;               // (ro+)
    UCHAR   HeaderType;                 // (ro)
    UCHAR   BIST;                       // Built in self test

    union {
        struct _PCI_HEADER_TYPE_0 {
            ULONG   BaseAddresses[PCI_TYPE0_ADDRESSES];
            ULONG   CIS;
            USHORT  SubVendorID;
            USHORT  SubSystemID;
            ULONG   ROMBaseAddress;
            UCHAR   CapabilitiesPtr;
            UCHAR   Reserved1[3];
            ULONG   Reserved2;
            UCHAR   InterruptLine;      //
            UCHAR   InterruptPin;       // (ro)
            UCHAR   MinimumGrant;       // (ro)
            UCHAR   MaximumLatency;     // (ro)
        } type0;


    } u;

    UCHAR   DeviceSpecific[192];

} PCI_COMMON_CONFIG, *PPCI_COMMON_CONFIG;


#define PCI_COMMON_HDR_LENGTH (FIELD_OFFSET (PCI_COMMON_CONFIG, DeviceSpecific))
#define PCI_EXTENDED_CONFIG_LENGTH          0x1000


#define PCI_MAX_DEVICES                     32
#define PCI_MAX_FUNCTION                    8
#define PCI_MAX_BRIDGE_NUMBER               0xFF

#define PCI_INVALID_VENDORID                0xFFFF

//
// Bit encodings for  PCI_COMMON_CONFIG.HeaderType
//

#define PCI_MULTIFUNCTION                   0x80
#define PCI_DEVICE_TYPE                     0x00
#define PCI_BRIDGE_TYPE                     0x01
#define PCI_CARDBUS_BRIDGE_TYPE             0x02

#define PCI_CONFIGURATION_TYPE(PciData) \
    (((PPCI_COMMON_CONFIG)(PciData))->HeaderType & ~PCI_MULTIFUNCTION)

#define PCI_MULTIFUNCTION_DEVICE(PciData) \
    ((((PPCI_COMMON_CONFIG)(PciData))->HeaderType & PCI_MULTIFUNCTION) != 0)

//
// Bit encodings for PCI_COMMON_CONFIG.Command
//

#define PCI_ENABLE_IO_SPACE                 0x0001
#define PCI_ENABLE_MEMORY_SPACE             0x0002
#define PCI_ENABLE_BUS_MASTER               0x0004
#define PCI_ENABLE_SPECIAL_CYCLES           0x0008
#define PCI_ENABLE_WRITE_AND_INVALIDATE     0x0010
#define PCI_ENABLE_VGA_COMPATIBLE_PALETTE   0x0020
#define PCI_ENABLE_PARITY                   0x0040  // (ro+)
#define PCI_ENABLE_WAIT_CYCLE               0x0080  // (ro+)
#define PCI_ENABLE_SERR                     0x0100  // (ro+)
#define PCI_ENABLE_FAST_BACK_TO_BACK        0x0200  // (ro)
#define PCI_DISABLE_LEVEL_INTERRUPT         0x0400

//
// Bit encodings for PCI_COMMON_CONFIG.Status
//

#define PCI_STATUS_INTERRUPT_PENDING        0x0008
#define PCI_STATUS_CAPABILITIES_LIST        0x0010  // (ro)
#define PCI_STATUS_66MHZ_CAPABLE            0x0020  // (ro)
#define PCI_STATUS_UDF_SUPPORTED            0x0040  // (ro)
#define PCI_STATUS_FAST_BACK_TO_BACK        0x0080  // (ro)
#define PCI_STATUS_DATA_PARITY_DETECTED     0x0100
#define PCI_STATUS_DEVSEL                   0x0600  // 2 bits wide
#define PCI_STATUS_SIGNALED_TARGET_ABORT    0x0800
#define PCI_STATUS_RECEIVED_TARGET_ABORT    0x1000
#define PCI_STATUS_RECEIVED_MASTER_ABORT    0x2000
#define PCI_STATUS_SIGNALED_SYSTEM_ERROR    0x4000
#define PCI_STATUS_DETECTED_PARITY_ERROR    0x8000

//
// The NT PCI Driver uses a WhichSpace parameter on its CONFIG_READ/WRITE
// routines.   The following values are defined-
//

#define PCI_WHICHSPACE_CONFIG               0x0
#define PCI_WHICHSPACE_ROM                  0x52696350

//
// PCI Capability IDs
//

#define PCI_CAPABILITY_ID_POWER_MANAGEMENT  0x01
#define PCI_CAPABILITY_ID_AGP               0x02
#define PCI_CAPABILITY_ID_VPD               0x03
#define PCI_CAPABILITY_ID_SLOT_ID           0x04
#define PCI_CAPABILITY_ID_MSI               0x05
#define PCI_CAPABILITY_ID_CPCI_HOTSWAP      0x06
#define PCI_CAPABILITY_ID_PCIX              0x07
#define PCI_CAPABILITY_ID_HYPERTRANSPORT    0x08
#define PCI_CAPABILITY_ID_VENDOR_SPECIFIC   0x09
#define PCI_CAPABILITY_ID_DEBUG_PORT        0x0A
#define PCI_CAPABILITY_ID_CPCI_RES_CTRL     0x0B
#define PCI_CAPABILITY_ID_SHPC              0x0C
#define PCI_CAPABILITY_ID_P2P_SSID          0x0D
#define PCI_CAPABILITY_ID_AGP_TARGET        0x0E
#define PCI_CAPABILITY_ID_SECURE            0x0F
#define PCI_CAPABILITY_ID_PCI_EXPRESS       0x10
#define PCI_CAPABILITY_ID_MSIX              0x11

//
// All PCI Capability structures have the following header.
//
// CapabilityID is used to identify the type of the structure (is
// one of the PCI_CAPABILITY_ID values above.
//
// Next is the offset in PCI Configuration space (0x40 - 0xfc) of the
// next capability structure in the list, or 0x00 if there are no more
// entries.
//
typedef struct _PCI_CAPABILITIES_HEADER {
    UCHAR   CapabilityID;
    UCHAR   Next;
} PCI_CAPABILITIES_HEADER, *PPCI_CAPABILITIES_HEADER;

//
// Power Management Capability
//

typedef struct _PCI_PMC {
    UCHAR       Version:3;
    UCHAR       PMEClock:1;
    UCHAR       Rsvd1:1;
    UCHAR       DeviceSpecificInitialization:1;
    UCHAR       Rsvd2:2;
    struct _PM_SUPPORT {
        UCHAR   Rsvd2:1;
        UCHAR   D1:1;
        UCHAR   D2:1;
        UCHAR   PMED0:1;
        UCHAR   PMED1:1;
        UCHAR   PMED2:1;
        UCHAR   PMED3Hot:1;
        UCHAR   PMED3Cold:1;
    } Support;
} PCI_PMC, *PPCI_PMC;

typedef struct _PCI_PMCSR {
    USHORT      PowerState:2;
    USHORT      Rsvd1:6;
    USHORT      PMEEnable:1;
    USHORT      DataSelect:4;
    USHORT      DataScale:2;
    USHORT      PMEStatus:1;
} PCI_PMCSR, *PPCI_PMCSR;


typedef struct _PCI_PMCSR_BSE {
    UCHAR       Rsvd1:6;
    UCHAR       D3HotSupportsStopClock:1;       // B2_B3#
    UCHAR       BusPowerClockControlEnabled:1;  // BPCC_EN
} PCI_PMCSR_BSE, *PPCI_PMCSR_BSE;


typedef struct _PCI_PM_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;

    //
    // Power Management Capabilities (Offset = 2)
    //

    union {
        PCI_PMC         Capabilities;
        USHORT          AsUSHORT;
    } PMC;

    //
    // Power Management Control/Status (Offset = 4)
    //

    union {
        PCI_PMCSR       ControlStatus;
        USHORT          AsUSHORT;
    } PMCSR;

    //
    // PMCSR PCI-PCI Bridge Support Extensions
    //

    union {
        PCI_PMCSR_BSE   BridgeSupport;
        UCHAR           AsUCHAR;
    } PMCSR_BSE;

    //
    // Optional read only 8 bit Data register.  Contents controlled by
    // DataSelect and DataScale in ControlStatus.
    //

    UCHAR   Data;

} PCI_PM_CAPABILITY, *PPCI_PM_CAPABILITY;

// end_wdm
// begin_ntddk

//
// AGP Capabilities
//
typedef struct _PCI_AGP_CAPABILITY {
    
    PCI_CAPABILITIES_HEADER Header;

    USHORT  Minor:4;
    USHORT  Major:4;
    USHORT  Rsvd1:8;

    struct _PCI_AGP_STATUS {
        ULONG   Rate:3;
        ULONG   Agp3Mode:1;
        ULONG   FastWrite:1;
        ULONG   FourGB:1;
        ULONG   HostTransDisable:1;
        ULONG   Gart64:1;
        ULONG   ITA_Coherent:1;
        ULONG   SideBandAddressing:1;                   // SBA
        ULONG   CalibrationCycle:3;
        ULONG   AsyncRequestSize:3;
        ULONG   Rsvd1:1;
        ULONG   Isoch:1;
        ULONG   Rsvd2:6;
        ULONG   RequestQueueDepthMaximum:8;             // RQ
    } AGPStatus;

    struct _PCI_AGP_COMMAND {
        ULONG   Rate:3;
        ULONG   Rsvd1:1;
        ULONG   FastWriteEnable:1;
        ULONG   FourGBEnable:1;
        ULONG   Rsvd2:1;
        ULONG   Gart64:1;
        ULONG   AGPEnable:1;
        ULONG   SBAEnable:1;
        ULONG   CalibrationCycle:3;
        ULONG   AsyncReqSize:3;
        ULONG   Rsvd3:8;
        ULONG   RequestQueueDepth:8;
    } AGPCommand;

} PCI_AGP_CAPABILITY, *PPCI_AGP_CAPABILITY;

//
// An AGPv3 Target must have an extended capability,
// but it's only present for a Master when the Isoch
// bit is set in its status register
//
typedef enum _EXTENDED_AGP_REGISTER {
    IsochStatus,
    AgpControl,
    ApertureSize,
    AperturePageSize,
    GartLow,
    GartHigh,
    IsochCommand
} EXTENDED_AGP_REGISTER, *PEXTENDED_AGP_REGISTER;

typedef struct _PCI_AGP_ISOCH_STATUS {
    ULONG ErrorCode: 2;
    ULONG Rsvd1: 1;
    ULONG Isoch_L: 3;
    ULONG Isoch_Y: 2;
    ULONG Isoch_N: 8;
    ULONG Rsvd2: 16;
} PCI_AGP_ISOCH_STATUS, *PPCI_AGP_ISOCH_STATUS;

typedef struct _PCI_AGP_CONTROL {
    ULONG Rsvd1: 7;
    ULONG GTLB_Enable: 1;
    ULONG AP_Enable: 1;
    ULONG CAL_Disable: 1;
    ULONG Rsvd2: 22;
} PCI_AGP_CONTROL, *PPCI_AGP_CONTROL;

typedef struct _PCI_AGP_APERTURE_PAGE_SIZE {
    USHORT PageSizeMask: 11;
    USHORT Rsvd1: 1;
    USHORT PageSizeSelect: 4;
} PCI_AGP_APERTURE_PAGE_SIZE, *PPCI_AGP_APERTURE_PAGE_SIZE;

typedef struct _PCI_AGP_ISOCH_COMMAND {
    USHORT Rsvd1: 6;
    USHORT Isoch_Y: 2;
    USHORT Isoch_N: 8;
} PCI_AGP_ISOCH_COMMAND, *PPCI_AGP_ISOCH_COMMAND;

typedef struct PCI_AGP_EXTENDED_CAPABILITY {

    PCI_AGP_ISOCH_STATUS IsochStatus;

//
// Target only ----------------<<-begin->>
//
    PCI_AGP_CONTROL AgpControl;
    USHORT ApertureSize;
    PCI_AGP_APERTURE_PAGE_SIZE AperturePageSize;
    ULONG GartLow;
    ULONG GartHigh;
//
// ------------------------------<<-end->>
//

    PCI_AGP_ISOCH_COMMAND IsochCommand;

} PCI_AGP_EXTENDED_CAPABILITY, *PPCI_AGP_EXTENDED_CAPABILITY;


#define PCI_AGP_RATE_1X     0x1
#define PCI_AGP_RATE_2X     0x2
#define PCI_AGP_RATE_4X     0x4

// end_ntddk
// begin_wdm
//
// MSI (Message Signalled Interrupts) Capability
//

typedef struct {

      PCI_CAPABILITIES_HEADER Header;

      struct _PCI_MSI_MESSAGE_CONTROL {
         USHORT  MSIEnable:1;
         USHORT  MultipleMessageCapable:3;
         USHORT  MultipleMessageEnable:3;
         USHORT  CapableOf64Bits:1;
         USHORT  PerVectorMaskCapable:1;
         USHORT  Reserved:7;
      } MessageControl;

      union {
            struct _PCI_MSI_MESSAGE_ADDRESS {
               ULONG Reserved:2;              // always zero, DWORD aligned address
               ULONG Address:30;
            } Register;
            ULONG Raw;
      } MessageAddressLower;

      //
      // This is only valid if CapableOf64Bits is 1.
      //

      union {
          struct {
              USHORT    MessageData;
          } Option32Bit;
          struct {
              ULONG     MessageAddressUpper;
              USHORT    MessageData;
              USHORT    Reserved;
              ULONG     MaskBits;
              ULONG     PendingBits;
          } Option64Bit;
      };

} PCI_MSI_CAPABILITY, *PPCI_MSI_CAPABILITY;

//
// MSI-X (Message Signalled Interrupts eXtended) Capability
//

#define MSIX_TABLE_OFFSET_MASK    0xfffffff8

typedef struct {
    union {
        struct {
            ULONG BaseIndexRegister:3;
            ULONG Reserved:29;
        };
        ULONG TableOffset;
    };

} PCIX_TABLE_POINTER, *PPCIX_TABLE_POINTER;

typedef struct {

      PCI_CAPABILITIES_HEADER Header;

      struct {
          USHORT TableSize:11;
          USHORT Reserved:3;
          USHORT FunctionMask:1;
          USHORT MSIXEnable:1;
      } MessageControl;

      PCIX_TABLE_POINTER  MessageTable;
      PCIX_TABLE_POINTER  PBATable;   // Pending Bit Array

} PCI_MSIX_CAPABILITY, *PPCI_MSIX_CAPABILITY;

typedef struct {

    PHYSICAL_ADDRESS    MessageAddress;
    ULONG               MessageData;
    
    union {
        ULONG           Mask:1;
        ULONG           Reserved:31;
    } VectorControl;
} PCI_MSIX_TABLE_ENTRY, *PPCI_MSIX_TABLE_ENTRY;

//
// PCI-X Capability
//

typedef struct {

    PCI_CAPABILITIES_HEADER Header;

    union {
        struct {
            USHORT  DataParityErrorRecoveryEnable:1;
            USHORT  EnableRelaxedOrdering:1;
            USHORT  MaxMemoryReadByteCount:2;
            USHORT  MaxOutstandingSplitTransactions:3;
            USHORT  Reserved:9;
        } bits;
        USHORT  AsUSHORT;
    } Command;

    union {
        struct {
            ULONG   FunctionNumber:3;
            ULONG   DeviceNumber:5;
            ULONG   BusNumber:8;
            ULONG   Device64Bit:1;
            ULONG   Capable133MHz:1;
            ULONG   SplitCompletionDiscarded:1;
            ULONG   UnexpectedSplitCompletion:1;
            ULONG   DeviceComplexity:1;
            ULONG   DesignedMaxMemoryReadByteCount:2;
            ULONG   DesignedMaxOutstandingSplitTransactions:3;
            ULONG   DesignedMaxCumulativeReadSize:3;
            ULONG   ReceivedSplitCompletionErrorMessage:1;
            ULONG   Reserved:2;
        } bits;
        ULONG   AsULONG;
    } Status;
} PCI_X_CAPABILITY, *PPCI_X_CAPABILITY;

//
// PCI-X Bridge Capability
//

//
// Values for BusModeFrequency in the SecondaryStatus register
//
#define PCIX_MODE_CONVENTIONAL_PCI  0x0
#define PCIX_MODE1_66MHZ            0x1
#define PCIX_MODE1_100MHZ           0x2
#define PCIX_MODE1_133MHZ           0x3
#define PCIX_MODE2_266_66MHZ        0x9
#define PCIX_MODE2_266_100MHZ       0xA
#define PCIX_MODE2_266_133MHZ       0xB
#define PCIX_MODE2_533_66MHZ        0xD
#define PCIX_MODE2_533_100MHZ       0xE
#define PCIX_MODE2_533_133MHZ       0xF

//
// Values for the Version in the SecondaryStatus register
//
#define PCIX_VERSION_MODE1_ONLY     0x0
#define PCIX_VERSION_MODE2_ECC      0x1
#define PCIX_VERSION_DUAL_MODE_ECC  0x2

typedef struct _PCIX_BRIDGE_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;

    union {
        struct {
            USHORT Bus64Bit:1;
            USHORT Bus133MHzCapable:1;
            USHORT SplitCompletionDiscarded:1;
            USHORT UnexpectedSplitCompletion:1;
            USHORT SplitCompletionOverrun:1;
            USHORT SplitRequestDelayed:1;
            USHORT BusModeFrequency:4;  // PCIX_MODE_x
            USHORT Rsvd:2;
            USHORT Version:2;           // PCIX_VERSION_x
            USHORT Bus266MHzCapable:1;
            USHORT Bus533MHzCapable:1;
        };
        USHORT AsUSHORT;
    } SecondaryStatus;
    
    union {
        struct {
            ULONG FunctionNumber:3;
            ULONG DeviceNumber:5;
            ULONG BusNumber:8;
            ULONG Device64Bit:1;
            ULONG Device133MHzCapable:1;
            ULONG SplitCompletionDiscarded:1;
            ULONG UnexpectedSplitCompletion:1;
            ULONG SplitCompletionOverrun:1;
            ULONG SplitRequestDelayed:1;
            ULONG Rsvd:7;
            ULONG DIMCapable:1;
            ULONG Device266MHzCapable:1;
            ULONG Device533MHzCapable:1;
        };
        ULONG AsULONG;
    } BridgeStatus;

    USHORT UpstreamSplitTransactionCapacity;
    USHORT UpstreamSplitTransactionLimit;

    USHORT DownstreamSplitTransactionCapacity;
    USHORT DownstreamSplitTransactionLimit;

    union {
        struct {
            ULONG SelectSecondaryRegisters:1;
            ULONG ErrorPresentInOtherBank:1;
            ULONG AdditionalCorrectableError:1;
            ULONG AdditionalUncorrectableError:1;
            ULONG ErrorPhase:3;
            ULONG ErrorCorrected:1;
            ULONG Syndrome:8;
            ULONG ErrorFirstCommand:4;
            ULONG ErrorSecondCommand:4;
            ULONG ErrorUpperAttributes:4;
            ULONG ControlUpdateEnable:1;
            ULONG Rsvd:1;
            ULONG DisableSingleBitCorrection:1;
            ULONG EccMode:1;
        };
        ULONG AsULONG;
    } EccControlStatus;
    
    ULONG EccFirstAddress;
    ULONG EccSecondAddress;
    ULONG EccAttribute;

} PCIX_BRIDGE_CAPABILITY, *PPCIX_BRIDGE_CAPABILITY;

//
// AMD HyperTransport (TM) Capabilities structure
//

typedef enum {
    HTSlavePrimary0 = 0,
    HTSlavePrimary1 = 1,
    HTSlavePrimary2 = 2,
    HTSlavePrimary3 = 3,
    HTHostSecondary0 = 4,
    HTHostSecondary1 = 5,
    HTHostSecondary2 = 6,
    HTHostSecondary3 = 7,
    HTInterruptDiscoveryConfig = 0x10,
    HTAddressMapping = 0x14,
    HTInterruptMsiMapping = 0x15
} PCI_HT_CapabilitiesType, *PPCI_HT_CapabilitiesType;

typedef struct {
    USHORT  Reserved1:1;
    USHORT  CFlE:1;
    USHORT  CST:1;
    USHORT  CFE:1;
    USHORT  LkFail:1;
    USHORT  Init:1;
    USHORT  EOC:1;
    USHORT  TXO:1;
    USHORT  CRCError:4;
    USHORT  IsocEn:1;
    USHORT  LSEn:1;
    USHORT  ExtCTL:1;
    USHORT  Reserved2:1;
} PCI_HT_LinkControl, *PPCI_HT_LinkControl;

typedef struct {
    USHORT  MaxLinkWidthIn:3;
    USHORT  DwFlowControlIn:1;
    USHORT  MaxLinkWidthOut:3;
    USHORT  DwFlowControlOut:1;
    USHORT  LinkWidthIn:3;
    USHORT  DwFlowControlInEn:1;
    USHORT  LinkWidthOut:3;
    USHORT  DwFlowControlOutEn:1;
} PCI_HT_LinkConfig, *PPCI_HT_LinkConfig;

typedef enum {
    HTMaxLinkWidth8bits = 0,
    HTMaxLinkWidth16bits,
    HTMaxLinkWidthResevered1,
    HTMaxLinkWidth32bits,
    HTMaxLinkWidth2bits,
    HTMaxLinkWidth4bits,
    HTMaxLinkWidthResevered2,
    HTMaxLinkWidthNotConnected
} PCI_HT_MaxLinkWidth, *PPCI_HT_MaxLinkWidth;

typedef struct {
    UCHAR   MinorRev:4;
    UCHAR   MajorRev:4;
} PCI_HT_RevisionID, *PPCI_HT_RevisionID;

typedef enum {
    HTFreq200MHz = 0,
    HTFreq300MHz,
    HTFreq400MHz,
    HTFreq500MHz,
    HTFreq600MHz,
    HTFreq800MHz,
    HTFreq1000MHz,
    HTFreqReserved,
    HTFreqVendorDefined
} PCI_HT_Frequency, *PPCI_HT_Frequency;

typedef struct {
    UCHAR   LinkFrequency:4;    // use PCI_HT_Frequency
    UCHAR   ProtocolError:1;
    UCHAR   OverflowError:1;
    UCHAR   EndOfChainError:1;
    UCHAR   CTLTimeout:1;
} PCI_HT_Frequency_Error, *PPCI_HT_Frequency_Error;

typedef struct {
    UCHAR  IsocMode:1;
    UCHAR  LDTSTOP:1;
    UCHAR  CRCTestMode:1;
    UCHAR  ExtendedCTLTimeReq:1;
    UCHAR  Reserved:4;
} PCI_HT_FeatureCap, *PPCI_HT_FeatureCap;

typedef struct {
  UCHAR  ExtendedRegisterSet:1;
  UCHAR  Reserved:7; 
} PCI_HT_FeatureCap_Ex, *PPCI_HT_FeatureCap_Ex;

typedef struct {
    USHORT  ProtFloodEn:1;
    USHORT  OverflowFloodEn:1;
    USHORT  ProtFatalEn:1;
    USHORT  OverflowFatalEn:1;
    USHORT  EOCFatalEn:1;
    USHORT  RespFatalEn:1;
    USHORT  CRCFatalEn:1;
    USHORT  SERRFataEn:1;
    USHORT  ChainFail:1;
    USHORT  ResponseError:1;
    USHORT  ProtNonFatalEn:1;
    USHORT  OverflowNonFatalEn:1;
    USHORT  EOCNonFatalEn:1;
    USHORT  RespNonFatalEn:1;
    USHORT  CRCNonFatalEn:1;
    USHORT  SERRNonFatalEn:1;
} PCI_HT_ErrorHandling, *PPCI_HT_ErrorHandling;

typedef struct {
    USHORT  Reserved1;
    UCHAR   LastInterrupt;
    UCHAR   Reserved2;
} PCI_HT_INTERRUPT_INDEX_1, *PPCI_HT_INTERRUPT_INDEX_1;

typedef struct {
    
    union {
        struct {
            ULONG   Mask:1;             // bit 0
            ULONG   Polarity:1;         // bit 1
            ULONG   MessageType:3;      // bits [4:2]
            ULONG   RequestEOI:1;       // bit 5
            ULONG   DestinationMode:1;  // bit 6
            ULONG   MessageType3:1;     // bit 7
            ULONG   Destination:8;      // bits [15:8]
            ULONG   Vector:8;           // bits [23:16]
            ULONG   ExtendedAddress:8;  // bits [31:24] -- always set to 0xF8
        } bits;
        ULONG   AsULONG;
    } LowPart;

    union {
        struct {
            ULONG   ExtendedDestination:24;
            ULONG   Reserved:6;
            ULONG   PassPW:1;
            ULONG   WaitingForEOI:1;
        } bits;
        ULONG   AsULONG;
    } HighPart;

} PCI_HT_INTERRUPT_INDEX_N, *PPCI_HT_INTERRUPT_INDEX_N;

typedef struct {

    PCI_CAPABILITIES_HEADER Header;

    //
    // Offset 2
    //
    
    union {
        struct {
            USHORT  Reserved:11;
            USHORT  CapabilityType:5; // use PCI_HT_CapabilitiesType
        } Generic;

        struct {
            USHORT  BaseUnitID:5;
            USHORT  UnitCount:5;
            USHORT  MasterHost:1;
            USHORT  DefaultDirection:1;
            USHORT  DropOnUnitinit:1;
            USHORT  CapabilityType:3; // use PCI_HT_CapabilitiesType
        } SlavePrimary;

        struct {
            USHORT  WarmReset:1;
            USHORT  DoubleEnded:1;
            USHORT  DeviceNumber:5;
            USHORT  ChainSide:1;
            USHORT  HostHide:1;
            USHORT  Rsv:1;
            USHORT  ActAsSlave:1;
            USHORT  InboundEOCError:1;
            USHORT  DropOnUnitinit:1;
            USHORT  CapabilityType:3; // use PCI_HT_CapabilitiesType
        } HostSecondary;

        struct {
            USHORT  Index:8;
            USHORT  Reserved:3;
            USHORT  CapabilityType:5; // use PCI_HT_CapabilitiesType
        } Interrupt;

        struct {
            USHORT  Enable:1;
            USHORT  Fixed:1;
            USHORT  Reserved:9;
            USHORT  CapabilityType:5;
        } MsiMapping;

    } Command;

    //
    // Offset 4
    //
    union {
        
        struct {
            PCI_HT_LinkControl  LinkControl_0;
            PCI_HT_LinkConfig   LinkConfig_0;
        } Link;

        ULONG InterruptDataPort;     // Interrupt DataPort

        struct {
            ULONG   Reserved:20;
            ULONG   AddressLow:12;
        } MsiMapping;
    
    } Offset04;
    
    //
    // Offset 8
    //

    union {

        struct {
            
            // Offset 0x8
            PCI_HT_LinkControl      LinkControl_1;
            PCI_HT_LinkConfig       LinkConfig_1;
            // Offset 0xc
            PCI_HT_RevisionID       RevisionID;
            // Offset 0xd
            PCI_HT_Frequency_Error  FreqErr_0;
            // Offset 0xe
            USHORT                  LinkFreqCap_0;
            // Offset 0x10
            PCI_HT_FeatureCap       FeatureCap;
            // Offset 0x11
            PCI_HT_Frequency_Error  FreqErr_1;
            // Offset 0x12
            USHORT                  LinkFreqCap_1;
            // Offset 0x14
            USHORT                  EnumerationScratchpad;
            // Offset 0x16
            PCI_HT_ErrorHandling    ErrorHandling;
            // Offset 0x18
            UCHAR                   MemoryBaseUpper8Bits;
            // Offset 0x19          
            UCHAR                   MemoryLimitUpper8Bits;
            // Offset 0x20
            USHORT                  Reserved;

        } SlavePrimary;

        struct {
            
            // Offset 0x8
            PCI_HT_RevisionID       RevisionID;
            // Offset 0x9
            PCI_HT_Frequency_Error  FreqErr_0;
            // Offset 0xa
            USHORT                  LinkFreqCap_0;
            // Offset 0xc
            PCI_HT_FeatureCap       FeatureCap;
            PCI_HT_FeatureCap_Ex    FeatureCapEx;
            // Offset 0xe
            USHORT                  Reserved1;
            // Offset 0x10
            USHORT                  EnumerationScratchpad;
            // Offset 0x12
            PCI_HT_ErrorHandling    ErrorHandling;
            // Offset 0x14
            UCHAR                   MemoryBaseUpper8Bits;
            // Offset 0x15
            UCHAR                   MemoryLimitUpper8Bits;
            // Offset 0x16
            USHORT                  Reserved2;

        } HostSecondary;

        struct {
            
            // Offset 0x8
            ULONG   AddressUpper;
        
        } MsiMapping;

    } Offset08;
} PCI_HT_CAPABILITY, *PPCI_HT_CAPABILITY;

//
// PCI to PCI Bridge Subsystem ID Capability
//
typedef struct _PCI_SUBSYSTEM_IDS_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;
    USHORT Reserved;

    USHORT SubVendorID;
    USHORT SubSystemID;

} PCI_SUBSYSTEM_IDS_CAPABILITY, *PPCI_SUBSYSTEM_IDS_CAPABILITY;


//
// PCI Express Capability
//

typedef union _PCI_EXPRESS_CAPABILITIES_REGISTER {

    struct {

        USHORT CapabilityVersion:4;
        USHORT DeviceType:4;               // PCI_EXPRESS_DEVICE_TYPE
        USHORT SlotImplemented:1;
        USHORT InterruptMessageNumber:5;
        USHORT Rsvd:2;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_CAPABILITIES_REGISTER, *PPCI_EXPRESS_CAPABILITIES_REGISTER;

typedef union _PCI_EXPRESS_DEVICE_CAPABILITIES {

    struct {

        ULONG MaxPayloadSizeSupported:3;     // PCI_EXPRESS_MAX_PAYLOAD_SIZE
        ULONG PhantomFunctionsSupported:2;
        ULONG ExtendedTagSupported:1;
        ULONG L0sAcceptableLatency:3;        // PCI_EXPRESS_L0S_LATENCY
        ULONG L1AcceptableLatency:3;         // PCI_EXPRESS_L1_LATENCY
        ULONG AttentionButtonPresent:1;
        ULONG AttentionIndicatorPresent:1;
        ULONG PowerIndicatorPresent:1;
        ULONG Rsvd1:3;
        ULONG CapturedSlotPowerLimit:8;
        ULONG CapturedSlotPowerLimitScale:2;
        ULONG Rsvd2:4;
    };

    ULONG AsULONG;

} PCI_EXPRESS_DEVICE_CAPABILITIES, *PPCI_EXPRESS_DEVICE_CAPABILITIES;

typedef union _PCI_EXPRESS_DEVICE_CONTROL {

    struct {

        USHORT CorrectableErrorEnable:1;
        USHORT NonFatalErrorEnable:1;
        USHORT FatalErrorEnable:1;
        USHORT UnsupportedRequestErrorEnable:1;
        USHORT EnableRelaxedOrder:1;
        USHORT MaxPayloadSize:3;                 // PCI_EXPRESS_MAX_PAYLOAD_SIZE
        USHORT ExtendedTagEnable:1;
        USHORT PhantomFunctionsEnable:1;
        USHORT AuxPowerEnable:1;
        USHORT NoSnoopEnable:1;
        USHORT MaxReadRequestSize:3;             // PCI_EXPRESS_MAX_PAYLOAD_SIZE
        USHORT Rsvd:1;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_DEVICE_CONTROL, *PPCI_EXPRESS_DEVICE_CONTROL;

typedef union _PCI_EXPRESS_DEVICE_STATUS {

    struct {

        USHORT CorrectableErrorDetected:1;
        USHORT NonFatalErrorDetected:1;
        USHORT FatalErrorDetected:1;
        USHORT UnsupportedRequestDetected:1;
        USHORT AuxPowerDetected:1;
        USHORT TransactionsPending:1;
        USHORT Rsvd:10;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_DEVICE_STATUS, *PPCI_EXPRESS_DEVICE_STATUS;

typedef union _PCI_EXPRESS_LINK_CAPABILITIES {

    struct {

        ULONG MaximumLinkSpeed:4;
        ULONG MaximumLinkWidth:6;
        ULONG ActiveStatePMSupport:2;   // PCI_EXPRESS_ASPM_CONFIG
        ULONG L0sExitLatency:3;         // PCI_EXPRESS_L0S_LATENCY
        ULONG L1ExitLatency:3;          // PCI_EXPRESS_L1_LATENCY
        ULONG Rsvd:6;
        ULONG PortNumber:8;
    };
    
    ULONG AsULONG;

} PCI_EXPRESS_LINK_CAPABILITIES, *PPCI_EXPRESS_LINK_CAPABILITIES;

typedef union _PCI_EXPRESS_LINK_CONTROL {

    struct {

        USHORT ActiveStatePMControl:2;    // PCI_EXPRESS_ASPM_CONFIG
        USHORT Rsvd1:1;
        USHORT ReadCompletionBoundary:1;  // PCI_EXPRESS_RCB
        USHORT LinkDisable:1;
        USHORT RetrainLink:1;
        USHORT CommonClockConfig:1;
        USHORT ExtendedSynch:1;
        USHORT Rsvd2:8;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_LINK_CONTROL, *PPCI_EXPRESS_LINK_CONTROL;

typedef union _PCI_EXPRESS_LINK_STATUS {

    struct {

        USHORT LinkSpeed:4;
        USHORT LinkWidth:6;
        USHORT LinkTrainingError:1;
        USHORT LinkTraining:1;
        USHORT SlotClockConfig:1;
        USHORT Rsvd:3;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_LINK_STATUS, *PPCI_EXPRESS_LINK_STATUS;

// end_wdm

typedef union _PCI_EXPRESS_SLOT_CAPABILITIES {

    struct {

        ULONG AttentionButtonPresent:1;
        ULONG PowerControllerPresent:1;
        ULONG MRLSensorPresent:1;
        ULONG AttentionIndicatorPresent:1;
        ULONG PowerIndicatorPresent:1;
        ULONG HotPlugSurprise:1;
        ULONG HotPlugCapable:1;
        ULONG SlotPowerLimit:8;
        ULONG SlotPowerLimitScale:2;
        ULONG Rsvd:2;
        ULONG PhysicalSlotNumber:13;
    };

    ULONG AsULONG;

} PCI_EXPRESS_SLOT_CAPABILITIES, *PPCI_EXPRESS_SLOT_CAPABILITIES;

typedef union _PCI_EXPRESS_SLOT_CONTROL {

    struct {

        USHORT AttentionButtonEnable:1;
        USHORT PowerFaultDetectedEnable:1;
        USHORT MRLSensorEnable:1;
        USHORT PresenceDetectEnable:1;
        USHORT CommandCompletedEnable:1;
        USHORT HotPlugInterruptEnable:1;
        USHORT AttentionIndicatorControl:2;  // PCI_EXPRESS_INDICATOR_STATE
        USHORT PowerIndicatorControl:2;      // PCI_EXPRESS_INDICATOR_STATE
        USHORT PowerControllerControl:1;     // PCI_EXPRESS_POWER_STATE
        USHORT Rsvd:5;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_SLOT_CONTROL, *PPCI_EXPRESS_SLOT_CONTROL;

typedef union _PCI_EXPRESS_SLOT_STATUS {

    struct {

        USHORT AttentionButtonPressed:1;
        USHORT PowerFaultDetected:1;
        USHORT MRLSensorChanged:1;
        USHORT PresenceDetectChanged:1;
        USHORT CommandCompleted:1;
        USHORT MRLSensorState:1;        // PCI_EXPRESS_MRL_STATE
        USHORT PresenceDetectState:1;   // PCI_EXPRESS_CARD_PRESENCE
        USHORT Rsvd:9;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_SLOT_STATUS, *PPCI_EXPRESS_SLOT_STATUS;

typedef union _PCI_EXPRESS_ROOT_CONTROL {

    struct {

        USHORT CorrectableSerrEnable:1;
        USHORT NonFatalSerrEnable:1;
        USHORT FatalSerrEnable:1;
        USHORT PMEInterruptEnable:1;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_ROOT_CONTROL, *PPCI_EXPRESS_ROOT_CONTROL;

typedef union _PCI_EXPRESS_ROOT_STATUS {

    struct {

        ULONG PMERequesterId:16;  // PCI_EXPRESS_REQUESTER_ID
        ULONG PMEStatus:1;
        ULONG PMEPending:1;
        ULONG Rsvd:14;
    };

    ULONG AsULONG;

} PCI_EXPRESS_ROOT_STATUS, *PPCI_EXPRESS_ROOT_STATUS;

// begin_wdm

//
// PCI Express Capability
//
typedef struct _PCI_EXPRESS_CAPABILITY {

    PCI_CAPABILITIES_HEADER Header;
    PCI_EXPRESS_CAPABILITIES_REGISTER ExpressCapabilities;

    PCI_EXPRESS_DEVICE_CAPABILITIES DeviceCapabilities;
    PCI_EXPRESS_DEVICE_CONTROL DeviceControl;
    PCI_EXPRESS_DEVICE_STATUS DeviceStatus;

    PCI_EXPRESS_LINK_CAPABILITIES LinkCapabilities;
    PCI_EXPRESS_LINK_CONTROL LinkControl;
    PCI_EXPRESS_LINK_STATUS LinkStatus;

// end_wdm
    PCI_EXPRESS_SLOT_CAPABILITIES SlotCapabilities;
    PCI_EXPRESS_SLOT_CONTROL SlotControl;
    PCI_EXPRESS_SLOT_STATUS SlotStatus;

    PCI_EXPRESS_ROOT_CONTROL RootControl;
    USHORT Rsvd;
    PCI_EXPRESS_ROOT_STATUS RootStatus;

// begin_wdm
} PCI_EXPRESS_CAPABILITY, *PPCI_EXPRESS_CAPABILITY;

//
// Definitions of bitfields
//
#define PCI_EXPRESS_CAPABILITY_VERSION 1

typedef enum {

    PciExpressEndpoint = 0,
    PciExpressLegacyEndpoint,
    PciExpressRootPort = 4,
    PciExpressUpstreamSwitchPort,
    PciExpressDownstreamSwitchPort,
    PciExpressToPciXBridge,
    PciXToExpressBridge,
    PciExpressRootComplexIntegratedEndpoint

} PCI_EXPRESS_DEVICE_TYPE;

typedef enum {

    RCB64Bytes = 0,
    RCB128Bytes

} PCI_EXPRESS_RCB;

typedef enum {

    L0sEntry = 1,
    L1Entry,
    L0sAndL1Entry

} PCI_EXPRESS_ASPM_CONFIG;

typedef enum {

    MaxPayload128Bytes = 0,
    MaxPayload256Bytes,
    MaxPayload512Bytes,
    MaxPayload1024Bytes,
    MaxPayload2048Bytes,
    MaxPayload4096Bytes

} PCI_EXPRESS_MAX_PAYLOAD_SIZE;

typedef enum {

    L0s_Below64ns = 0,
    L0s_64ns_128ns,
    L0s_128ns_256ns,
    L0s_256ns_512ns,
    L0s_512ns_1us,
    L0s_1us_2us,
    L0s_2us_4us,
    L0s_Above4us

} PCI_EXPRESS_L0S_LATENCY;

typedef enum {

    L1_Below1us = 0,
    L1_1us_2us,
    L1_2us_4us,
    L1_4us_8us,
    L1_8us_16us,
    L1_16us_32us,
    L1_32us_64us,
    L1_Above64us

} PCI_EXPRESS_L1_LATENCY;

// end_wdm

typedef enum {

    MRLClosed = 0,
    MRLOpen

} PCI_EXPRESS_MRL_STATE;

typedef enum {

    SlotEmpty = 0,
    CardPresent

} PCI_EXPRESS_CARD_PRESENCE;

typedef enum {

    IndicatorOn = 1,
    IndicatorBlink,
    IndicatorOff

} PCI_EXPRESS_INDICATOR_STATE;

typedef enum {

    PowerOn = 0,
    PowerOff

} PCI_EXPRESS_POWER_STATE;

typedef union _PCI_EXPRESS_REQUESTER_ID {

    struct {

        USHORT FunctionNumber:3;
        USHORT DeviceNumber:5;
        USHORT BusNumber:8;
    };

    USHORT AsUSHORT;

} PCI_EXPRESS_REQUESTER_ID, *PPCI_EXPRESS_REQUESTER_ID;

// begin_wdm


//
// PCI Express Enhanced capabilities
//

#define PCI_ENHANCED_CAPABILITY_ADVANCED_ERROR  0x01
#define PCI_ENHANCED_CAPABILITY_VIRTUAL_CHANNEL 0x02
#define PCI_ENHANCED_CAPABILITY_SERIAL_NUMBER   0x03
#define PCI_ENHANCED_CAPABILITY_POWER_BUDGETING 0x04

//
// All Enhanced capabilities have the following header
//
typedef struct _PCI_ENHANCED_CAPABILITY_HEADER {

    USHORT CapabilityID;
    USHORT Version:4;
    USHORT Next:12;

} PCI_ENHANCED_CAPABILITY_HEADER, *PPCI_ENHANCED_CAPABILITY_HEADER;

//
// Serial Number Capability
//
typedef struct _PCI_EXPRESS_SERIAL_NUMBER_CAPABILITY {

    PCI_ENHANCED_CAPABILITY_HEADER Header;

    ULONG LowSerialNumber;
    ULONG HighSerialNumber;

} PCI_EXPRESS_SERIAL_NUMBER_CAPABILITY, *PPCI_EXPRESS_SERIAL_NUMBER_CAPABILITY;
    


//
// Base Class Code encodings for Base Class (from PCI spec rev 2.1).
//

#define PCI_CLASS_PRE_20                    0x00
#define PCI_CLASS_MASS_STORAGE_CTLR         0x01
#define PCI_CLASS_NETWORK_CTLR              0x02
#define PCI_CLASS_DISPLAY_CTLR              0x03
#define PCI_CLASS_MULTIMEDIA_DEV            0x04
#define PCI_CLASS_MEMORY_CTLR               0x05
#define PCI_CLASS_BRIDGE_DEV                0x06
#define PCI_CLASS_SIMPLE_COMMS_CTLR         0x07
#define PCI_CLASS_BASE_SYSTEM_DEV           0x08
#define PCI_CLASS_INPUT_DEV                 0x09
#define PCI_CLASS_DOCKING_STATION           0x0a
#define PCI_CLASS_PROCESSOR                 0x0b
#define PCI_CLASS_SERIAL_BUS_CTLR           0x0c
#define PCI_CLASS_WIRELESS_CTLR             0x0d
#define PCI_CLASS_INTELLIGENT_IO_CTLR       0x0e
#define PCI_CLASS_SATELLITE_COMMS_CTLR      0x0f
#define PCI_CLASS_ENCRYPTION_DECRYPTION     0x10
#define PCI_CLASS_DATA_ACQ_SIGNAL_PROC      0x11

// 0d thru fe reserved

#define PCI_CLASS_NOT_DEFINED               0xff

//
// Sub Class Code encodings (PCI rev 2.1).
//

// Class 00 - PCI_CLASS_PRE_20

#define PCI_SUBCLASS_PRE_20_NON_VGA         0x00
#define PCI_SUBCLASS_PRE_20_VGA             0x01

// Class 01 - PCI_CLASS_MASS_STORAGE_CTLR

#define PCI_SUBCLASS_MSC_SCSI_BUS_CTLR      0x00
#define PCI_SUBCLASS_MSC_IDE_CTLR           0x01
#define PCI_SUBCLASS_MSC_FLOPPY_CTLR        0x02
#define PCI_SUBCLASS_MSC_IPI_CTLR           0x03
#define PCI_SUBCLASS_MSC_RAID_CTLR          0x04
#define PCI_SUBCLASS_MSC_OTHER              0x80

// Class 02 - PCI_CLASS_NETWORK_CTLR

#define PCI_SUBCLASS_NET_ETHERNET_CTLR      0x00
#define PCI_SUBCLASS_NET_TOKEN_RING_CTLR    0x01
#define PCI_SUBCLASS_NET_FDDI_CTLR          0x02
#define PCI_SUBCLASS_NET_ATM_CTLR           0x03
#define PCI_SUBCLASS_NET_ISDN_CTLR          0x04
#define PCI_SUBCLASS_NET_OTHER              0x80

// Class 03 - PCI_CLASS_DISPLAY_CTLR

// N.B. Sub Class 00 could be VGA or 8514 depending on Interface byte

#define PCI_SUBCLASS_VID_VGA_CTLR           0x00
#define PCI_SUBCLASS_VID_XGA_CTLR           0x01
#define PCI_SUBLCASS_VID_3D_CTLR            0x02
#define PCI_SUBCLASS_VID_OTHER              0x80

// Class 04 - PCI_CLASS_MULTIMEDIA_DEV

#define PCI_SUBCLASS_MM_VIDEO_DEV           0x00
#define PCI_SUBCLASS_MM_AUDIO_DEV           0x01
#define PCI_SUBCLASS_MM_TELEPHONY_DEV       0x02
#define PCI_SUBCLASS_MM_OTHER               0x80

// Class 05 - PCI_CLASS_MEMORY_CTLR

#define PCI_SUBCLASS_MEM_RAM                0x00
#define PCI_SUBCLASS_MEM_FLASH              0x01
#define PCI_SUBCLASS_MEM_OTHER              0x80

// Class 06 - PCI_CLASS_BRIDGE_DEV

#define PCI_SUBCLASS_BR_HOST                0x00
#define PCI_SUBCLASS_BR_ISA                 0x01
#define PCI_SUBCLASS_BR_EISA                0x02
#define PCI_SUBCLASS_BR_MCA                 0x03
#define PCI_SUBCLASS_BR_PCI_TO_PCI          0x04
#define PCI_SUBCLASS_BR_PCMCIA              0x05
#define PCI_SUBCLASS_BR_NUBUS               0x06
#define PCI_SUBCLASS_BR_CARDBUS             0x07
#define PCI_SUBCLASS_BR_RACEWAY             0x08
#define PCI_SUBCLASS_BR_OTHER               0x80

// Class 07 - PCI_CLASS_SIMPLE_COMMS_CTLR

// N.B. Sub Class 00 and 01 additional info in Interface byte

#define PCI_SUBCLASS_COM_SERIAL             0x00
#define PCI_SUBCLASS_COM_PARALLEL           0x01
#define PCI_SUBCLASS_COM_MULTIPORT          0x02
#define PCI_SUBCLASS_COM_MODEM              0x03
#define PCI_SUBCLASS_COM_OTHER              0x80

// Class 08 - PCI_CLASS_BASE_SYSTEM_DEV

// N.B. See Interface byte for additional info.

#define PCI_SUBCLASS_SYS_INTERRUPT_CTLR     0x00
#define PCI_SUBCLASS_SYS_DMA_CTLR           0x01
#define PCI_SUBCLASS_SYS_SYSTEM_TIMER       0x02
#define PCI_SUBCLASS_SYS_REAL_TIME_CLOCK    0x03
#define PCI_SUBCLASS_SYS_GEN_HOTPLUG_CTLR   0x04
#define PCI_SUBCLASS_SYS_OTHER              0x80

// Class 09 - PCI_CLASS_INPUT_DEV

#define PCI_SUBCLASS_INP_KEYBOARD           0x00
#define PCI_SUBCLASS_INP_DIGITIZER          0x01
#define PCI_SUBCLASS_INP_MOUSE              0x02
#define PCI_SUBCLASS_INP_SCANNER            0x03
#define PCI_SUBCLASS_INP_GAMEPORT           0x04
#define PCI_SUBCLASS_INP_OTHER              0x80

// Class 0a - PCI_CLASS_DOCKING_STATION

#define PCI_SUBCLASS_DOC_GENERIC            0x00
#define PCI_SUBCLASS_DOC_OTHER              0x80

// Class 0b - PCI_CLASS_PROCESSOR

#define PCI_SUBCLASS_PROC_386               0x00
#define PCI_SUBCLASS_PROC_486               0x01
#define PCI_SUBCLASS_PROC_PENTIUM           0x02
#define PCI_SUBCLASS_PROC_ALPHA             0x10
#define PCI_SUBCLASS_PROC_POWERPC           0x20
#define PCI_SUBCLASS_PROC_COPROCESSOR       0x40

// Class 0c - PCI_CLASS_SERIAL_BUS_CTLR

#define PCI_SUBCLASS_SB_IEEE1394            0x00
#define PCI_SUBCLASS_SB_ACCESS              0x01
#define PCI_SUBCLASS_SB_SSA                 0x02
#define PCI_SUBCLASS_SB_USB                 0x03
#define PCI_SUBCLASS_SB_FIBRE_CHANNEL       0x04
#define PCI_SUBCLASS_SB_SMBUS               0x05

// Class 0d - PCI_CLASS_WIRELESS_CTLR

#define PCI_SUBCLASS_WIRELESS_IRDA          0x00
#define PCI_SUBCLASS_WIRELESS_CON_IR        0x01
#define PCI_SUBCLASS_WIRELESS_RF            0x10
#define PCI_SUBCLASS_WIRELESS_OTHER         0x80

// Class 0e - PCI_CLASS_INTELLIGENT_IO_CTLR

#define PCI_SUBCLASS_INTIO_I2O              0x00

// Class 0f - PCI_CLASS_SATELLITE_CTLR

#define PCI_SUBCLASS_SAT_TV                 0x01
#define PCI_SUBCLASS_SAT_AUDIO              0x02
#define PCI_SUBCLASS_SAT_VOICE              0x03
#define PCI_SUBCLASS_SAT_DATA               0x04

// Class 10 - PCI_CLASS_ENCRYPTION_DECRYPTION

#define PCI_SUBCLASS_CRYPTO_NET_COMP        0x00
#define PCI_SUBCLASS_CRYPTO_ENTERTAINMENT   0x10
#define PCI_SUBCLASS_CRYPTO_OTHER           0x80

// Class 11 - PCI_CLASS_DATA_ACQ_SIGNAL_PROC

#define PCI_SUBCLASS_DASP_DPIO              0x00
#define PCI_SUBCLASS_DASP_OTHER             0x80




typedef enum _MM_PAGE_PRIORITY {
    LowPagePriority,
    NormalPagePriority = 16,
    HighPagePriority = 32
} MM_PAGE_PRIORITY;


#define    PCCARD_PCI_CONFIGURATION_SPACE    0  // for cardbus cards
#define    PCCARD_ATTRIBUTE_MEMORY           1
#define    PCCARD_COMMON_MEMORY              2
#define    PCCARD_ATTRIBUTE_MEMORY_INDIRECT  3
#define    PCCARD_COMMON_MEMORY_INDIRECT     4


#else // BINARY_COMPATIBLE && !NDIS_WDM

#if (!BINARY_COMPATIBLE)

//
// BINARY_COMPATIBLE = 0 and NDIS_WDM = 1 then use ntddk.h
// BINARY_COMPATIBLE = 0 and NDIS_WDM = 0 then use ntddk.h
//
//
// The definitions available in ntddk.h must not be used directly by non-WDM miniport drivers.
//

#include <ntddk.h>

#else // !BINARY_COMPATIBLE

//
// BINARY_COMPATIBLE = 1 and NDIS_WDM = 1 then use wdm.h
//

#include <wdm.h>

#endif  // else !BINARY_COMPATIBLE

#endif //  else BINARY_COMPATIBLE && !NDIS_WDM
//
// END INTERNAL DEFINITIONS
//
// The following definitions may be used by NDIS drivers, except as noted.
//

#ifndef __NET_PNP__
#define __NET_PNP__

//
//  PnP and PM event codes that can be indicated up to transports
//  and clients.
//
typedef enum _NET_PNP_EVENT_CODE
{
    NetEventSetPower,
    NetEventQueryPower,
    NetEventQueryRemoveDevice,
    NetEventCancelRemoveDevice,
    NetEventReconfigure,
    NetEventBindList,
    NetEventBindsComplete,
    NetEventPnPCapabilities,
    NetEventPause,
    NetEventRestart,
    NetEventFilterListChanged,
    NetEventPortArrival,
    NetEventPortRemoval,
    NetEventMaximum
} NET_PNP_EVENT_CODE, *PNET_PNP_EVENT_CODE;

//
//  Networking PnP event indication structure.
//
typedef struct _NET_PNP_EVENT
{
    //
    //  Event code describing action to take.
    //
    NET_PNP_EVENT_CODE  NetEvent;

    //
    //  Event specific data.
    //
    PVOID               Buffer;

    //
    //  Length of event specific data.
    //
    ULONG               BufferLength;

    //
    //  Reserved values are for use by respective components only.
    //
    //  Note: these reserved areas must be pointer aligned.
    //  

    ULONG_PTR           NdisReserved[4];
    ULONG_PTR           TransportReserved[4];
    ULONG_PTR           TdiReserved[4];
    ULONG_PTR           TdiClientReserved[4];
} NET_PNP_EVENT, *PNET_PNP_EVENT;

//
//  The following structure defines the device power states.
//
typedef enum _NET_DEVICE_POWER_STATE
{
    NetDeviceStateUnspecified = 0,
    NetDeviceStateD0,
    NetDeviceStateD1,
    NetDeviceStateD2,
    NetDeviceStateD3,
    NetDeviceStateMaximum
} NET_DEVICE_POWER_STATE, *PNET_DEVICE_POWER_STATE;

#endif // __NET_PNP__

//
// Indicate that we're building for NT. NDIS_NT is always used for
// miniport builds.
//

#define NDIS_NT 1

#if defined(NDIS_DOS)
#undef NDIS_DOS
#endif


#if !defined(NDIS_CHIMNEY_OFFLOAD)
#define NDIS_CHIMNEY_OFFLOAD 1
#endif

//
// Define status codes and event log codes.
//

#include <ntstatus.h>
#include <netevent.h>

//
// Define a couple of extra types.
//

#if !defined(_WINDEF_)      // these are defined in windows.h too
typedef signed int INT, *PINT;
typedef unsigned int UINT, *PUINT;
#endif

typedef UNICODE_STRING NDIS_STRING, *PNDIS_STRING;

//
// Portability extentions
//

#define NDIS_INIT_FUNCTION(_F)      alloc_text(INIT,_F)
#define NDIS_PAGABLE_FUNCTION(_F)   alloc_text(PAGE,_F)
#define NDIS_PAGEABLE_FUNCTION(_F)  alloc_text(PAGE,_F)

//
// This file contains the definition of an NDIS_OID as
// well as #defines for all the current OID values.
//

//
// Define NDIS_STATUS and NDIS_HANDLE here
//
typedef PVOID NDIS_HANDLE, *PNDIS_HANDLE;

typedef int NDIS_STATUS, *PNDIS_STATUS; // note default size


//
// for Miniports versions 5.0 and up, provide a consistent way to match
// Ndis version in their characteristics with their makefile defines
//
#if (!defined(NDIS_MINIPORT_MAJOR_VERSION) && !defined(NDIS_MINIPORT_MINOR_VERSION))
#if (defined(NDIS60_MINIPORT))
#define NDIS_MINIPORT_MAJOR_VERSION 6
#define NDIS_MINIPORT_MINOR_VERSION 0
#elif (defined(NDIS51_MINIPORT))
#define NDIS_MINIPORT_MAJOR_VERSION 5
#define NDIS_MINIPORT_MINOR_VERSION 1
#elif (defined(NDIS50_MINIPORT))
#define NDIS_MINIPORT_MAJOR_VERSION 5
#define NDIS_MINIPORT_MINOR_VERSION 0
#endif
#endif // (!defined(NDIS_MINIPORT_MAJOR_VERSION) && !defined(NDIS_MINIPORT_MINOR_VERSION))

//
// for protocol versions 5.0 and up, provide a consistent way to match
// Ndis version in their characteristics with their makefile defines
//
#if (!defined(NDIS_PROTOCOL_MAJOR_VERSION) && !defined(NDIS_PROTOCOL_MINOR_VERSION))
#if (defined(NDIS60))
#define NDIS_PROTOCOL_MAJOR_VERSION 6
#define NDIS_PROTOCOL_MINOR_VERSION 0
#elif (defined(NDIS51))
#define NDIS_PROTOCOL_MAJOR_VERSION 5
#define NDIS_PROTOCOL_MINOR_VERSION 1
#elif (defined(NDIS50))
#define NDIS_PROTOCOL_MAJOR_VERSION 5
#define NDIS_PROTOCOL_MINOR_VERSION 0
#endif
#endif // (!defined(NDIS_PROTOCOL_MAJOR_VERSION) && !defined(NDIS_PROTOCOL_MINOR_VERSION))


#include <ntddndis.h>



//
// Ndis defines for configuration manager data structures
//
typedef CM_MCA_POS_DATA NDIS_MCA_POS_DATA, *PNDIS_MCA_POS_DATA;
typedef CM_EISA_SLOT_INFORMATION NDIS_EISA_SLOT_INFORMATION, *PNDIS_EISA_SLOT_INFORMATION;
typedef CM_EISA_FUNCTION_INFORMATION NDIS_EISA_FUNCTION_INFORMATION, *PNDIS_EISA_FUNCTION_INFORMATION;

//
// Define an exported function.
//
#if defined(NDIS_WRAPPER)
#define EXPORT
#else
#define EXPORT DECLSPEC_IMPORT
#endif

typedef struct _NDIS_GENERIC_OBJECT
{
    NDIS_OBJECT_HEADER  Header;
    PVOID               Caller;
    PVOID               CallersCaller;
    PDRIVER_OBJECT      DriverObject;
} NDIS_GENERIC_OBJECT, *PNDIS_GENERIC_OBJECT;

EXPORT
PNDIS_GENERIC_OBJECT
NdisAllocateGenericObject(
    PDRIVER_OBJECT          DriverObject OPTIONAL,
    ULONG                   Tag,
    USHORT                  Size
    );

EXPORT
VOID
NdisFreeGenericObject(
    IN PNDIS_GENERIC_OBJECT   NdisObject
    );



//
// Memory manipulation functions.
//
#define NdisMoveMemory(Destination, Source, Length) RtlCopyMemory(Destination, Source, Length)
#define NdisZeroMemory(Destination, Length)         RtlZeroMemory(Destination, Length)
#define NdisEqualMemory(Source1, Source2, Length)   RtlEqualMemory(Source1, Source2, Length)
#define NdisFillMemory(Destination, Length, Fill)   RtlFillMemory(Destination, Length, Fill)
#define NdisRetrieveUlong(Destination, Source)      RtlRetrieveUlong(Destination, Source)
#define NdisStoreUlong(Destination, Value)          RtlStoreUlong(Destination, Value)

#define NDIS_STRING_CONST(x)    {sizeof(L##x)-2, sizeof(L##x), L##x}

//
// On a RISC machine, I/O mapped memory can't be accessed with
// the Rtl routines.
//
#if defined(_M_IX86) || defined(_M_AMD64)

#define NdisMoveMappedMemory(Destination,Source,Length) RtlCopyMemory(Destination,Source,Length)
#define NdisZeroMappedMemory(Destination,Length)        RtlZeroMemory(Destination,Length)

#elif defined(_M_IA64)

#define NdisMoveMappedMemory(Destination,Source,Length)                     \
{                                                                           \
    PUCHAR _Src = (Source);                                                 \
    PUCHAR _Dest = (Destination);                                           \
    PUCHAR _End = _Dest + (Length);                                         \
    while (_Dest < _End)                                                    \
    {                                                                       \
        *_Dest++ = *_Src++;                                                 \
    }                                                                       \
}

#define NdisZeroMappedMemory(Destination,Length)                            \
{                                                                           \
    PUCHAR _Dest = (Destination);                                           \
    PUCHAR _End = _Dest + (Length);                                         \
    while (_Dest < _End)                                                    \
    {                                                                       \
        *_Dest++ = 0;                                                       \
    }                                                                       \
}
#endif


#define NdisMoveToMappedMemory(Destination,Source,Length)                   \
                            NdisMoveMappedMemory(Destination,Source,Length)
#define NdisMoveFromMappedMemory(Destination,Source,Length)                 \
                            NdisMoveMappedMemory(Destination,Source,Length)


//
// definition of the basic spin lock structure
//

typedef struct _NDIS_SPIN_LOCK
{
    KSPIN_LOCK  SpinLock;
    KIRQL       OldIrql;
} NDIS_SPIN_LOCK, * PNDIS_SPIN_LOCK;


//
// definition of the ndis event structure
//
typedef struct _NDIS_EVENT
{
    KEVENT      Event;
} NDIS_EVENT, *PNDIS_EVENT;

#pragma warning(push)
#pragma warning(disable:4115) // named type definition in parenthesis
typedef VOID    (*NDIS_PROC)(struct _NDIS_WORK_ITEM *, PVOID);
#pragma warning(pop)

//
// Definition of an ndis work-item
//
typedef struct _NDIS_WORK_ITEM
{
    PVOID           Context;
    NDIS_PROC       Routine;
    UCHAR           WrapperReserved[8*sizeof(PVOID)];
} NDIS_WORK_ITEM, *PNDIS_WORK_ITEM;

#define NdisInterruptLatched            Latched
#define NdisInterruptLevelSensitive     LevelSensitive
typedef KINTERRUPT_MODE NDIS_INTERRUPT_MODE, *PNDIS_INTERRUPT_MODE;

//
// Configuration definitions
//

//
// Possible data types
//

typedef enum _NDIS_PARAMETER_TYPE
{
    NdisParameterInteger,
    NdisParameterHexInteger,
    NdisParameterString,
    NdisParameterMultiString,
    NdisParameterBinary
} NDIS_PARAMETER_TYPE, *PNDIS_PARAMETER_TYPE;

typedef struct
{
    USHORT          Length;
    PVOID           Buffer;
} BINARY_DATA;

//
// To store configuration information
//
typedef struct _NDIS_CONFIGURATION_PARAMETER
{
    NDIS_PARAMETER_TYPE ParameterType;
    union
    {
        ULONG           IntegerData;
        NDIS_STRING     StringData;
        BINARY_DATA     BinaryData;
    } ParameterData;
} NDIS_CONFIGURATION_PARAMETER, *PNDIS_CONFIGURATION_PARAMETER;


//
// Definitions for the "ProcessorType" keyword
//
typedef enum _NDIS_PROCESSOR_TYPE
{
    NdisProcessorX86,
    NdisProcessorMips,
    NdisProcessorAlpha,
    NdisProcessorPpc,
    NdisProcessorAmd64,
    NdisProcessorIA64
} NDIS_PROCESSOR_TYPE, *PNDIS_PROCESSOR_TYPE;

//
// Definitions for the "Environment" keyword
//
typedef enum _NDIS_ENVIRONMENT_TYPE
{
    NdisEnvironmentWindows,
    NdisEnvironmentWindowsNt
} NDIS_ENVIRONMENT_TYPE, *PNDIS_ENVIRONMENT_TYPE;


//
// Possible Hardware Architecture. Define these to
// match the HAL INTERFACE_TYPE enum.
//
typedef enum _NDIS_INTERFACE_TYPE
{
    NdisInterfaceInternal = Internal,
    NdisInterfaceIsa = Isa,
    NdisInterfaceEisa = Eisa,
    NdisInterfaceMca = MicroChannel,
    NdisInterfaceTurboChannel = TurboChannel,
    NdisInterfacePci = PCIBus,
    NdisInterfacePcMcia = PCMCIABus,
    NdisInterfaceCBus = CBus,
    NdisInterfaceMPIBus = MPIBus,
    NdisInterfaceMPSABus = MPSABus,
    NdisInterfaceProcessorInternal = ProcessorInternal,
    NdisInterfaceInternalPowerBus = InternalPowerBus,
    NdisInterfacePNPISABus = PNPISABus,
    NdisInterfacePNPBus = PNPBus,
    NdisMaximumInterfaceType
} NDIS_INTERFACE_TYPE, *PNDIS_INTERFACE_TYPE;

//
// Stuff for PCI configuring
//

typedef CM_PARTIAL_RESOURCE_LIST NDIS_RESOURCE_LIST, *PNDIS_RESOURCE_LIST;


//
// The structure passed up on a WAN_LINE_UP indication
//

typedef struct _NDIS_WAN_LINE_UP
{
    IN ULONG                LinkSpeed;          // 100 bps units
    IN ULONG                MaximumTotalSize;   // suggested max for send packets
    IN NDIS_WAN_QUALITY     Quality;
    IN USHORT               SendWindow;         // suggested by the MAC
    IN UCHAR                RemoteAddress[6];
    IN OUT UCHAR            LocalAddress[6];
    IN ULONG                ProtocolBufferLength;   // Length of protocol info buffer
    IN PUCHAR               ProtocolBuffer;     // Information used by protocol
    IN USHORT               ProtocolType;       // Protocol ID
    IN OUT NDIS_STRING      DeviceName;
} NDIS_WAN_LINE_UP, *PNDIS_WAN_LINE_UP;


//
// The structure passed up on a WAN_LINE_DOWN indication
//

typedef struct _NDIS_WAN_LINE_DOWN
{
    IN UCHAR    RemoteAddress[6];
    IN UCHAR    LocalAddress[6];
} NDIS_WAN_LINE_DOWN, *PNDIS_WAN_LINE_DOWN;

//
// The structure passed up on a WAN_FRAGMENT indication
//

typedef struct _NDIS_WAN_FRAGMENT
{
    IN UCHAR    RemoteAddress[6];
    IN UCHAR    LocalAddress[6];
} NDIS_WAN_FRAGMENT, *PNDIS_WAN_FRAGMENT;

//
// The structure passed up on a WAN_GET_STATS indication
//

typedef struct _NDIS_WAN_GET_STATS
{
    IN  UCHAR   LocalAddress[6];
    OUT ULONG   BytesSent;
    OUT ULONG   BytesRcvd;
    OUT ULONG   FramesSent;
    OUT ULONG   FramesRcvd;
    OUT ULONG   CRCErrors;                      // Serial-like info only
    OUT ULONG   TimeoutErrors;                  // Serial-like info only
    OUT ULONG   AlignmentErrors;                // Serial-like info only
    OUT ULONG   SerialOverrunErrors;            // Serial-like info only
    OUT ULONG   FramingErrors;                  // Serial-like info only
    OUT ULONG   BufferOverrunErrors;            // Serial-like info only
    OUT ULONG   BytesTransmittedUncompressed;   // Compression info only
    OUT ULONG   BytesReceivedUncompressed;      // Compression info only
    OUT ULONG   BytesTransmittedCompressed;     // Compression info only
    OUT ULONG   BytesReceivedCompressed;        // Compression info only
} NDIS_WAN_GET_STATS, *PNDIS_WAN_GET_STATS;


//
// DMA Channel information
//
typedef struct _NDIS_DMA_DESCRIPTION
{
    BOOLEAN     DemandMode;
    BOOLEAN     AutoInitialize;
    BOOLEAN     DmaChannelSpecified;
    DMA_WIDTH   DmaWidth;
    DMA_SPEED   DmaSpeed;
    ULONG       DmaPort;
    ULONG       DmaChannel;
} NDIS_DMA_DESCRIPTION, *PNDIS_DMA_DESCRIPTION;

//
// Internal structure representing an NDIS DMA channel
//
typedef struct _NDIS_DMA_BLOCK
{
    PVOID                   MapRegisterBase;
    KEVENT                  AllocationEvent;
    PVOID                   SystemAdapterObject;
    PVOID                   Miniport;
    BOOLEAN                 InProgress;
} NDIS_DMA_BLOCK, *PNDIS_DMA_BLOCK;



#if defined(NDIS_WRAPPER)
//
// definitions for PnP state
//

typedef enum _NDIS_PNP_DEVICE_STATE
{
    NdisPnPDeviceAdded,
    NdisPnPDeviceStarted,
    NdisPnPDeviceQueryStopped,
    NdisPnPDeviceStopped,
    NdisPnPDeviceQueryRemoved,
    NdisPnPDeviceRemoved,
    NdisPnPDeviceSurpriseRemoved
} NDIS_PNP_DEVICE_STATE;

typedef enum _NDIS_MINIPORT_STATE
{
    NdisMiniportUndefindState,
    NdisMiniportHalted,
    NdisMiniportInitializing,
    NdisMiniportRestarting,
    NdisMiniportRunning,
    NdisMiniportPausing,
    NdisMiniportPaused
} NDIS_MINIPORT_STATE;

//
// flags to use in PnPCapabilities Flag
//
#define NDIS_DEVICE_NOT_STOPPABLE                   0x00000001      // the debvice is not stoppable i.e. ISA
#define NDIS_DEVICE_NOT_REMOVEABLE                  0x00000002      // the device can not be safely removed
#define NDIS_DEVICE_NOT_SUSPENDABLE                 0x00000004      // the device can not be safely suspended
#define NDIS_DEVICE_DISABLE_PM                      0x00000008      // disable all PM features
#define NDIS_DEVICE_DISABLE_WAKE_UP                 0x00000010      // disable device waking up the system
#define NDIS_DEVICE_DISABLE_WAKE_ON_RECONNECT       0x00000020      // disable device waking up the -system- due to a cable re-connect
#define NDIS_DEVICE_RESERVED                        0x00000040      // should not be used
#define NDIS_DEVICE_DISABLE_WAKE_ON_MAGIC_PACKET    0x00000080      // disable device waking up the -system- due to a magic packet
#define NDIS_DEVICE_DISABLE_WAKE_ON_PATTERN_MATCH   0x00000100      // disable device waking up the -system- due to a pattern match



#endif // NDIS_WRAPPER defined

//
// Ndis Buffer is actually an Mdl
//
typedef MDL NDIS_BUFFER, *PNDIS_BUFFER;

struct _NDIS_PACKET;
typedef NDIS_HANDLE PNDIS_PACKET_POOL;

//
//
// wrapper-specific part of a packet
//
typedef struct _NDIS_PACKET_PRIVATE
{
    UINT                PhysicalCount;  // number of physical pages in packet.
    UINT                TotalLength;    // Total amount of data in the packet.
    PNDIS_BUFFER        Head;           // first buffer in the chain
    PNDIS_BUFFER        Tail;           // last buffer in the chain

    // if Head is NULL the chain is empty; Tail doesn't have to be NULL also

    PNDIS_PACKET_POOL   Pool;           // so we know where to free it back to
    UINT                Count;
    ULONG               Flags;
    BOOLEAN             ValidCounts;
    UCHAR               NdisPacketFlags;    // See fPACKET_xxx bits below
    USHORT              NdisPacketOobOffset;
} NDIS_PACKET_PRIVATE, * PNDIS_PACKET_PRIVATE;

//
// The bits define the bits in the Flags
//
#define NDIS_FLAGS_PROTOCOL_ID_MASK             0x0000000F  // The low 4 bits are defined for protocol-id
                                                            // The values are defined in ntddndis.h
#define NDIS_FLAGS_MULTICAST_PACKET             0x00000010  // don't use
#define NDIS_FLAGS_RESERVED2                    0x00000020  // don't use
#define NDIS_FLAGS_RESERVED3                    0x00000040  // don't use
#define NDIS_FLAGS_DONT_LOOPBACK                0x00000080  // Write only
#define NDIS_FLAGS_IS_LOOPBACK_PACKET           0x00000100  // Read only
#define NDIS_FLAGS_LOOPBACK_ONLY                0x00000200  // Write only
#define NDIS_FLAGS_RESERVED4                    0x00000400  // don't use
#define NDIS_FLAGS_DOUBLE_BUFFERED              0x00000800  // used by ndis
#define NDIS_FLAGS_SENT_AT_DPC                  0x00001000  // the protocol sent this packet at DPC
#define NDIS_FLAGS_USES_SG_BUFFER_LIST          0x00002000  // used by Ndis
#define NDIS_FLAGS_USES_ORIGINAL_PACKET         0x00004000  // used by Ndis
#define NDIS_FLAGS_ALLOCATED_XFER_DATA_PKT      0x00008000  // used by Ndis
#define NDIS_FLAGS_UIO                          0x00010000  // used by Ndis

//
// Low-bits in the NdisPacketFlags are reserved by NDIS Wrapper for internal use
//
#define fPACKET_WRAPPER_RESERVED                0x3F
#define fPACKET_CONTAINS_MEDIA_SPECIFIC_INFO    0x40
#define fPACKET_ALLOCATED_BY_NDIS               0x80

//
// Definition for layout of the media-specific data. More than one class of media-specific
// information can be tagged onto a packet.
//
typedef enum _NDIS_CLASS_ID
{
    NdisClass802_3Priority,
    NdisClassWirelessWanMbxMailbox,
    NdisClassIrdaPacketInfo,
    NdisClassAtmAALInfo

} NDIS_CLASS_ID;

typedef struct _MEDIA_SPECIFIC_INFORMATION
{
    UINT            NextEntryOffset;
    NDIS_CLASS_ID   ClassId;
    UINT            Size;
    UCHAR           ClassInformation[1];

} MEDIA_SPECIFIC_INFORMATION, *PMEDIA_SPECIFIC_INFORMATION;

typedef struct _NDIS_PACKET_OOB_DATA
{
    union
    {
        ULONGLONG   TimeToSend;
        ULONGLONG   TimeSent;
    };
    ULONGLONG       TimeReceived;
    UINT            HeaderSize;
    UINT            SizeMediaSpecificInfo;
    PVOID           MediaSpecificInformation;

    NDIS_STATUS     Status;
} NDIS_PACKET_OOB_DATA, *PNDIS_PACKET_OOB_DATA;

#define NDIS_GET_PACKET_PROTOCOL_TYPE(_Packet_) ((_Packet_)->Private.Flags & NDIS_PROTOCOL_ID_MASK)

#define NDIS_OOB_DATA_FROM_PACKET(_p)                                   \
                        (PNDIS_PACKET_OOB_DATA)((PUCHAR)(_p) +          \
                        (_p)->Private.NdisPacketOobOffset)
#define NDIS_GET_PACKET_HEADER_SIZE(_Packet)                            \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->HeaderSize
#define NDIS_GET_PACKET_STATUS(_Packet)                                 \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->Status
#define NDIS_GET_PACKET_TIME_TO_SEND(_Packet)                           \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->TimeToSend
#define NDIS_GET_PACKET_TIME_SENT(_Packet)                              \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->TimeSent
#define NDIS_GET_PACKET_TIME_RECEIVED(_Packet)                          \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->TimeReceived
#define NDIS_GET_PACKET_MEDIA_SPECIFIC_INFO(_Packet,                    \
                                            _pMediaSpecificInfo,        \
                                            _pSizeMediaSpecificInfo)    \
{                                                                       \
    if (!((_Packet)->Private.NdisPacketFlags & fPACKET_ALLOCATED_BY_NDIS) ||\
        !((_Packet)->Private.NdisPacketFlags & fPACKET_CONTAINS_MEDIA_SPECIFIC_INFO))\
    {                                                                   \
        *(_pMediaSpecificInfo) = NULL;                                  \
        *(_pSizeMediaSpecificInfo) = 0;                                 \
    }                                                                   \
    else                                                                \
    {                                                                   \
        *(_pMediaSpecificInfo) =((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +\
                    (_Packet)->Private.NdisPacketOobOffset))->MediaSpecificInformation;\
        *(_pSizeMediaSpecificInfo) = ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +\
                    (_Packet)->Private.NdisPacketOobOffset))->SizeMediaSpecificInfo;\
    }                                                                   \
}

#define NDIS_SET_PACKET_HEADER_SIZE(_Packet, _HdrSize)                  \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->HeaderSize = (_HdrSize)
#define NDIS_SET_PACKET_STATUS(_Packet, _Status)                        \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->Status = (_Status)
#define NDIS_SET_PACKET_TIME_TO_SEND(_Packet, _TimeToSend)              \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->TimeToSend = (_TimeToSend)
#define NDIS_SET_PACKET_TIME_SENT(_Packet, _TimeSent)                   \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->TimeSent = (_TimeSent)
#define NDIS_SET_PACKET_TIME_RECEIVED(_Packet, _TimeReceived)           \
                        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +    \
                        (_Packet)->Private.NdisPacketOobOffset))->TimeReceived = (_TimeReceived)
#define NDIS_SET_PACKET_MEDIA_SPECIFIC_INFO(_Packet,                    \
                                            _MediaSpecificInfo,         \
                                            _SizeMediaSpecificInfo)     \
{                                                                       \
    if ((_Packet)->Private.NdisPacketFlags & fPACKET_ALLOCATED_BY_NDIS) \
    {                                                                   \
        (_Packet)->Private.NdisPacketFlags |= fPACKET_CONTAINS_MEDIA_SPECIFIC_INFO;\
        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +                    \
                                          (_Packet)->Private.NdisPacketOobOffset))->MediaSpecificInformation = (_MediaSpecificInfo);\
        ((PNDIS_PACKET_OOB_DATA)((PUCHAR)(_Packet) +                    \
                                          (_Packet)->Private.NdisPacketOobOffset))->SizeMediaSpecificInfo = (_SizeMediaSpecificInfo);\
    }                                                                   \
}

//
// packet definition
//
typedef struct _NDIS_PACKET
{
    NDIS_PACKET_PRIVATE Private;

    union
    {
        struct                  // For Connection-less miniports
        {
            UCHAR   MiniportReserved[2*sizeof(PVOID)];
            UCHAR   WrapperReserved[2*sizeof(PVOID)];
        };

        struct
        {
            //
            // For de-serialized miniports. And by implication conn-oriented miniports.
            //
            UCHAR   MiniportReservedEx[3*sizeof(PVOID)];
            UCHAR   WrapperReservedEx[sizeof(PVOID)];
        };

        struct
        {
            UCHAR   MacReserved[4*sizeof(PVOID)];
        };
    };

    ULONG_PTR       Reserved[2];            // For compatibility with Win95
    UCHAR           ProtocolReserved[1];

} NDIS_PACKET, *PNDIS_PACKET, **PPNDIS_PACKET;

//
//  NDIS per-packet information.
//
typedef enum _NDIS_PER_PACKET_INFO
{
    TcpIpChecksumPacketInfo,
    IpSecPacketInfo,
    TcpLargeSendPacketInfo,
    ClassificationHandlePacketInfo,
    NdisReserved,
    ScatterGatherListPacketInfo,
    Ieee8021QInfo,
    OriginalPacketInfo,
    PacketCancelId,
    OriginalNetBufferList,
    CachedNetBufferList,
    NdisuioReserved,
    MaxPerPacketInfo
} NDIS_PER_PACKET_INFO, *PNDIS_PER_PACKET_INFO;

typedef struct _NDIS_PACKET_EXTENSION
{
    PVOID       NdisPacketInfo[MaxPerPacketInfo];
} NDIS_PACKET_EXTENSION, *PNDIS_PACKET_EXTENSION;

#define NDIS_PACKET_EXTENSION_FROM_PACKET(_P)       ((PNDIS_PACKET_EXTENSION)((PUCHAR)(_P) + (_P)->Private.NdisPacketOobOffset + sizeof(NDIS_PACKET_OOB_DATA)))
#define NDIS_PER_PACKET_INFO_FROM_PACKET(_P, _Id)   ((PNDIS_PACKET_EXTENSION)((PUCHAR)(_P) + (_P)->Private.NdisPacketOobOffset + sizeof(NDIS_PACKET_OOB_DATA)))->NdisPacketInfo[(_Id)]
#define NDIS_GET_ORIGINAL_PACKET(_P)                NDIS_PER_PACKET_INFO_FROM_PACKET(_P, OriginalPacketInfo)
#define NDIS_SET_ORIGINAL_PACKET(_P, _OP)           NDIS_PER_PACKET_INFO_FROM_PACKET(_P, OriginalPacketInfo) = _OP
#define NDIS_GET_PACKET_CANCEL_ID(_P)               NDIS_PER_PACKET_INFO_FROM_PACKET(_P, PacketCancelId)
#define NDIS_SET_PACKET_CANCEL_ID(_P, _cId)         NDIS_PER_PACKET_INFO_FROM_PACKET(_P, PacketCancelId) = _cId

#define NDIS_PACKET_SET_HASH_TYPE(_P, _HashType)           \
    (NDIS_PER_PACKET_INFO_FROM_PACKET(_P, NdisReserved)  = \
    UlongToPtr((PtrToUlong(NDIS_PER_PACKET_INFO_FROM_PACKET(_P, NdisReserved)) & (~NDIS_HASH_TYPE_MASK)) | ((_HashType) & (NDIS_HASH_TYPE_MASK))))

#define NDIS_PACKET_SET_HASH_FUNCTION(_P, _HashFunction)   \
    (NDIS_PER_PACKET_INFO_FROM_PACKET(_P, NdisReserved)  = \
    UlongToPtr((PtrToUlong(NDIS_PER_PACKET_INFO_FROM_PACKET(_P, NdisReserved)) & (~NDIS_HASH_FUNCTION_MASK)) | ((_HashFunction) & (NDIS_HASH_FUNCTION_MASK))))

#define NDIS_PACKET_SET_HASH_VALUE(_P, _HashValue)         \
    (NDIS_PER_PACKET_INFO_FROM_PACKET(_P, ScatterGatherListPacketInfo) = UlongToPtr(_HashValue))

#define NDIS_PACKET_GET_HASH_TYPE(_P)                      \
    (PtrToUlong(NDIS_PER_PACKET_INFO_FROM_PACKET(_P, NdisReserved)) & (NDIS_HASH_TYPE_MASK))

#define NDIS_PACKET_GET_HASH_FUNCTION(_P)                  \
    (PtrToUlong(NDIS_PER_PACKET_INFO_FROM_PACKET(_P, NdisReserved)) & (NDIS_HASH_FUNCTION_MASK))

#define NDIS_PACKET_GET_HASH_VALUE(_P)                     \
    (PtrToUlong(NDIS_PER_PACKET_INFO_FROM_PACKET(_P, ScatterGatherListPacketInfo)))

typedef struct _NDIS_PACKET_STACK
{
    ULONG_PTR   IMReserved[2];
    ULONG_PTR   NdisReserved[4];
} NDIS_PACKET_STACK, *PNDIS_PACKET_STACK;

//
//  Per-packet information for TcpIpChecksumPacketInfo.
//
typedef struct _NDIS_TCP_IP_CHECKSUM_PACKET_INFO
{
    union
    {
        struct
        {
            ULONG   NdisPacketChecksumV4:1;
            ULONG   NdisPacketChecksumV6:1;
            ULONG   NdisPacketTcpChecksum:1;
            ULONG   NdisPacketUdpChecksum:1;
            ULONG   NdisPacketIpChecksum:1;
        } Transmit;

        struct
        {
            ULONG   NdisPacketTcpChecksumFailed:1;
            ULONG   NdisPacketUdpChecksumFailed:1;
            ULONG   NdisPacketIpChecksumFailed:1;
            ULONG   NdisPacketTcpChecksumSucceeded:1;
            ULONG   NdisPacketUdpChecksumSucceeded:1;
            ULONG   NdisPacketIpChecksumSucceeded:1;
            ULONG   NdisPacketLoopback:1;
        } Receive;

        ULONG   Value;
    };
} NDIS_TCP_IP_CHECKSUM_PACKET_INFO, *PNDIS_TCP_IP_CHECKSUM_PACKET_INFO;


//
//  Per-packet information for Ieee8021QInfo.
//
typedef struct _NDIS_PACKET_8021Q_INFO
{
    union
    {
        struct
        {
            UINT32      UserPriority:3;         // 802.1p priority
            UINT32      CanonicalFormatId:1;    // always 0
            UINT32      VlanId:12;              // VLAN Identification
            UINT32      Reserved:16;            // set to 0
        }   TagHeader;

        PVOID  Value;
    };
} NDIS_PACKET_8021Q_INFO, *PNDIS_PACKET_8021Q_INFO;

//
//  Old definitions, to be obsoleted.
//
#define Ieee8021pPriority   Ieee8021QInfo
typedef UINT                IEEE8021PPRIORITY;

//
// WAN Packet. This is used by WAN miniports only. This is the legacy model.
// Co-Ndis is the preferred model for WAN miniports
//
typedef struct _NDIS_WAN_PACKET
{
    LIST_ENTRY          WanPacketQueue;
    PUCHAR              CurrentBuffer;
    ULONG               CurrentLength;
    PUCHAR              StartBuffer;
    PUCHAR              EndBuffer;
    PVOID               ProtocolReserved1;
    PVOID               ProtocolReserved2;
    PVOID               ProtocolReserved3;
    PVOID               ProtocolReserved4;
    PVOID               MacReserved1;
    PVOID               MacReserved2;
    PVOID               MacReserved3;
    PVOID               MacReserved4;
} NDIS_WAN_PACKET, *PNDIS_WAN_PACKET;

//
// Routines to get/set packet flags
//

/*++

UINT
NdisGetPacketFlags(
    IN  PNDIS_PACKET    Packet
    );

--*/

#define NdisGetPacketFlags(_Packet)         (_Packet)->Private.Flags

/*++

VOID
NdisSetPacketFlags(
    IN  PNDIS_PACKET Packet,
    IN  UINT Flags
    );

--*/

#define NdisSetPacketFlags(_Packet, _Flags)     (_Packet)->Private.Flags |= (_Flags)
#define NdisClearPacketFlags(_Packet, _Flags)   (_Packet)->Private.Flags &= ~(_Flags)

//
// Request types used by NdisRequest; constants are added for
// all entry points in the MAC, for those that want to create
// their own internal requests.
//

typedef enum _NDIS_REQUEST_TYPE
{
    NdisRequestQueryInformation,
    NdisRequestSetInformation,
    NdisRequestQueryStatistics,
    NdisRequestOpen,
    NdisRequestClose,
    NdisRequestSend,
    NdisRequestTransferData,
    NdisRequestReset,
    NdisRequestGeneric1,
    NdisRequestGeneric2,
    NdisRequestGeneric3,
    NdisRequestGeneric4,
    NdisRequestMethod,
} NDIS_REQUEST_TYPE, *PNDIS_REQUEST_TYPE;


//
// Structure of requests sent via NdisRequest
//

typedef struct _NDIS_REQUEST
{
    UCHAR               MacReserved[4*sizeof(PVOID)];
    NDIS_REQUEST_TYPE   RequestType;
    union _DATA
    {
        struct _QUERY_INFORMATION
        {
            NDIS_OID    Oid;
            PVOID       InformationBuffer;
            UINT        InformationBufferLength;
            UINT        BytesWritten;
            UINT        BytesNeeded;
        } QUERY_INFORMATION;

        struct _SET_INFORMATION
        {
            NDIS_OID    Oid;
            PVOID       InformationBuffer;
            UINT        InformationBufferLength;
            UINT        BytesRead;
            UINT        BytesNeeded;
        } SET_INFORMATION;

        struct _METHOD_INFORMATION
        {
            NDIS_OID            Oid;
            PVOID               InformationBuffer;
            ULONG               InputBufferLength;
            ULONG               OutputBufferLength;
            ULONG               MethodId;
            UINT                BytesWritten;
            UINT                BytesRead;
            UINT                BytesNeeded;
        } METHOD_INFORMATION;

    } DATA;
#if NDIS_CHIMNEY_OFFLOAD
#if (defined(NDIS50) || defined(NDIS51) || defined(NDIS52) || defined(NDIS60) || defined(NDIS50_MINIPORT) || defined(NDIS51_MINIPORT) || defined(NDIS52_MINIPORT) || defined(NDIS60_MINIPORT))
    UCHAR               NdisReserved[9*sizeof(PVOID)];
    union
    {
        UCHAR           CallMgrReserved[2*sizeof(PVOID)];
        UCHAR           ProtocolReserved[2*sizeof(PVOID)];
    };
    UCHAR               MiniportReserved[2*sizeof(PVOID)];
#endif
#else
#if (defined(NDIS50) || defined(NDIS51) || defined(NDIS60) || defined(NDIS50_MINIPORT) || defined(NDIS51_MINIPORT) || defined(NDIS60_MINIPORT))
    UCHAR               NdisReserved[9*sizeof(PVOID)];
    union
    {
        UCHAR           CallMgrReserved[2*sizeof(PVOID)];
        UCHAR           ProtocolReserved[2*sizeof(PVOID)];
    };
    UCHAR               MiniportReserved[2*sizeof(PVOID)];
#endif
#endif
} NDIS_REQUEST, *PNDIS_REQUEST;



//
// NDIS Address Family definitions.
//
typedef ULONG           NDIS_AF, *PNDIS_AF;
#define CO_ADDRESS_FAMILY_Q2931             ((NDIS_AF)0x1)  // ATM
#define CO_ADDRESS_FAMILY_PSCHED            ((NDIS_AF)0x2)  // Packet scheduler
#define CO_ADDRESS_FAMILY_L2TP              ((NDIS_AF)0x3)
#define CO_ADDRESS_FAMILY_IRDA              ((NDIS_AF)0x4)
#define CO_ADDRESS_FAMILY_1394              ((NDIS_AF)0x5)
#define CO_ADDRESS_FAMILY_PPP               ((NDIS_AF)0x6)
#define CO_ADDRESS_FAMILY_INFINIBAND        ((NDIS_AF)0x7)
#define CO_ADDRESS_FAMILY_TAPI              ((NDIS_AF)0x800)
#define CO_ADDRESS_FAMILY_TAPI_PROXY        ((NDIS_AF)0x801)

//
// The following is OR'ed with the base AF to denote proxy support
//
#define CO_ADDRESS_FAMILY_PROXY             0x80000000


//
//  Address family structure registered/opened via
//      NdisCmRegisterAddressFamily
//      NdisClOpenAddressFamily
//
typedef struct
{
    NDIS_AF                     AddressFamily;  // one of the CO_ADDRESS_FAMILY_xxx values above
    ULONG                       MajorVersion;   // the major version of call manager
    ULONG                       MinorVersion;   // the minor version of call manager
} CO_ADDRESS_FAMILY, *PCO_ADDRESS_FAMILY;

//
// Definition for a SAP
//
typedef struct
{
    ULONG                       SapType;
    ULONG                       SapLength;
    UCHAR                       Sap[1];
} CO_SAP, *PCO_SAP;

//
// Definitions for physical address.
//

typedef PHYSICAL_ADDRESS NDIS_PHYSICAL_ADDRESS, *PNDIS_PHYSICAL_ADDRESS;
typedef struct _NDIS_PHYSICAL_ADDRESS_UNIT
{
    NDIS_PHYSICAL_ADDRESS       PhysicalAddress;
    UINT                        Length;
} NDIS_PHYSICAL_ADDRESS_UNIT, *PNDIS_PHYSICAL_ADDRESS_UNIT;


/*++

ULONG
NdisGetPhysicalAddressHigh(
    IN  NDIS_PHYSICAL_ADDRESS   PhysicalAddress
    );

--*/

#define NdisGetPhysicalAddressHigh(_PhysicalAddress)            \
        ((_PhysicalAddress).HighPart)

/*++

VOID
NdisSetPhysicalAddressHigh(
    IN  NDIS_PHYSICAL_ADDRESS   PhysicalAddress,
    IN  ULONG                   Value
    );

--*/

#define NdisSetPhysicalAddressHigh(_PhysicalAddress, _Value)    \
     ((_PhysicalAddress).HighPart) = (_Value)


/*++

ULONG
NdisGetPhysicalAddressLow(
    IN  NDIS_PHYSICAL_ADDRESS PhysicalAddress
    );

--*/

#define NdisGetPhysicalAddressLow(_PhysicalAddress)             \
    ((_PhysicalAddress).LowPart)


/*++

VOID
NdisSetPhysicalAddressLow(
    IN  NDIS_PHYSICAL_ADDRESS   PhysicalAddress,
    IN  ULONG                   Value
    );

--*/

#define NdisSetPhysicalAddressLow(_PhysicalAddress, _Value)     \
    ((_PhysicalAddress).LowPart) = (_Value)

//
// Macro to initialize an NDIS_PHYSICAL_ADDRESS constant
//

#define NDIS_PHYSICAL_ADDRESS_CONST(_Low, _High)                \
    { (ULONG)(_Low), (LONG)(_High) }


//
// block used for references...
//
typedef struct _REFERENCE
{
    KSPIN_LOCK                  SpinLock;
    USHORT                      ReferenceCount;
    BOOLEAN                     Closing;
} REFERENCE, * PREFERENCE;

//
// block used for references using a ULONG
//
typedef struct _ULONG_REFERENCE
{
    KSPIN_LOCK                  SpinLock;
    ULONG                       ReferenceCount;
    BOOLEAN                     Closing;
} ULONG_REFERENCE, *PULONG_REFERENCE;


//
// Types of Memory (not mutually exclusive)
//

#define NDIS_MEMORY_CONTIGUOUS      0x00000001
#define NDIS_MEMORY_NONCACHED       0x00000002

//
// Open options
//
#define NDIS_OPEN_RECEIVE_NOT_REENTRANT 0x00000001

//
// NDIS_STATUS values
//

#define NDIS_STATUS_SUCCESS                     ((NDIS_STATUS)STATUS_SUCCESS)
#define NDIS_STATUS_PENDING                     ((NDIS_STATUS) STATUS_PENDING)
#define NDIS_STATUS_NOT_RECOGNIZED              ((NDIS_STATUS)0x00010001L)
#define NDIS_STATUS_NOT_COPIED                  ((NDIS_STATUS)0x00010002L)
#define NDIS_STATUS_NOT_ACCEPTED                ((NDIS_STATUS)0x00010003L)
#define NDIS_STATUS_CALL_ACTIVE                 ((NDIS_STATUS)0x00010007L)

#define NDIS_STATUS_ONLINE                      ((NDIS_STATUS)0x40010003L)
#define NDIS_STATUS_RESET_START                 ((NDIS_STATUS)0x40010004L)
#define NDIS_STATUS_RESET_END                   ((NDIS_STATUS)0x40010005L)
#define NDIS_STATUS_RING_STATUS                 ((NDIS_STATUS)0x40010006L)
#define NDIS_STATUS_CLOSED                      ((NDIS_STATUS)0x40010007L)
#define NDIS_STATUS_WAN_LINE_UP                 ((NDIS_STATUS)0x40010008L)
#define NDIS_STATUS_WAN_LINE_DOWN               ((NDIS_STATUS)0x40010009L)
#define NDIS_STATUS_WAN_FRAGMENT                ((NDIS_STATUS)0x4001000AL)
#define NDIS_STATUS_MEDIA_CONNECT               ((NDIS_STATUS)0x4001000BL)
#define NDIS_STATUS_MEDIA_DISCONNECT            ((NDIS_STATUS)0x4001000CL)
#define NDIS_STATUS_HARDWARE_LINE_UP            ((NDIS_STATUS)0x4001000DL)
#define NDIS_STATUS_HARDWARE_LINE_DOWN          ((NDIS_STATUS)0x4001000EL)
#define NDIS_STATUS_INTERFACE_UP                ((NDIS_STATUS)0x4001000FL)
#define NDIS_STATUS_INTERFACE_DOWN              ((NDIS_STATUS)0x40010010L)
#define NDIS_STATUS_MEDIA_BUSY                  ((NDIS_STATUS)0x40010011L)
#define NDIS_STATUS_MEDIA_SPECIFIC_INDICATION   ((NDIS_STATUS)0x40010012L)
#define NDIS_STATUS_WW_INDICATION               NDIS_STATUS_MEDIA_SPECIFIC_INDICATION
#define NDIS_STATUS_LINK_SPEED_CHANGE           ((NDIS_STATUS)0x40010013L)
#define NDIS_STATUS_WAN_GET_STATS               ((NDIS_STATUS)0x40010014L)
#define NDIS_STATUS_WAN_CO_FRAGMENT             ((NDIS_STATUS)0x40010015L)
#define NDIS_STATUS_WAN_CO_LINKPARAMS           ((NDIS_STATUS)0x40010016L)
#define NDIS_STATUS_LINK_STATE                  ((NDIS_STATUS)0x40010017L)
#define NDIS_STATUS_MEDIA_CONNECT_STATE         ((NDIS_STATUS)0x40010018L)
#define NDIS_STATUS_DUPLEX_STATE                ((NDIS_STATUS)0x40010019L)
#define NDIS_STATUS_LINK_SPEED                  ((NDIS_STATUS)0x4001001AL)
#define NDIS_STATUS_PORT_ARRIVAL                ((NDIS_STATUS)0x40010020L)
#define NDIS_STATUS_PORT_REMOVAL                ((NDIS_STATUS)0x40010021L)
#define NDIS_STATUS_PORT_STATE_CHANGE           ((NDIS_STATUS)0x40010022L)

#define NDIS_STATUS_OFFLOAD_PAUSE               ((NDIS_STATUS)0x40020001L)
#define NDIS_STATUS_UPLOAD_ALL                  ((NDIS_STATUS)0x40020002L)
#define NDIS_STATUS_OFFLOAD_RESUME              ((NDIS_STATUS)0x40020003L)
#define NDIS_STATUS_OFFLOAD_PARTIAL_SUCCESS     ((NDIS_STATUS)0x40020004L)
#define NDIS_STATUS_OFFLOAD_STATE_ALLOCATED     ((NDIS_STATUS)0x40020005L)

#define NDIS_STATUS_NOT_RESETTABLE              ((NDIS_STATUS)0x80010001L)
#define NDIS_STATUS_SOFT_ERRORS                 ((NDIS_STATUS)0x80010003L)
#define NDIS_STATUS_HARD_ERRORS                 ((NDIS_STATUS)0x80010004L)
#define NDIS_STATUS_BUFFER_OVERFLOW             ((NDIS_STATUS)STATUS_BUFFER_OVERFLOW)

#define NDIS_STATUS_FAILURE                     ((NDIS_STATUS) STATUS_UNSUCCESSFUL)
#define NDIS_STATUS_RESOURCES                   ((NDIS_STATUS)STATUS_INSUFFICIENT_RESOURCES)
#define NDIS_STATUS_CLOSING                     ((NDIS_STATUS)0xC0010002L)
#define NDIS_STATUS_BAD_VERSION                 ((NDIS_STATUS)0xC0010004L)
#define NDIS_STATUS_BAD_CHARACTERISTICS         ((NDIS_STATUS)0xC0010005L)
#define NDIS_STATUS_ADAPTER_NOT_FOUND           ((NDIS_STATUS)0xC0010006L)
#define NDIS_STATUS_OPEN_FAILED                 ((NDIS_STATUS)0xC0010007L)
#define NDIS_STATUS_DEVICE_FAILED               ((NDIS_STATUS)0xC0010008L)
#define NDIS_STATUS_MULTICAST_FULL              ((NDIS_STATUS)0xC0010009L)
#define NDIS_STATUS_MULTICAST_EXISTS            ((NDIS_STATUS)0xC001000AL)
#define NDIS_STATUS_MULTICAST_NOT_FOUND         ((NDIS_STATUS)0xC001000BL)
#define NDIS_STATUS_REQUEST_ABORTED             ((NDIS_STATUS)0xC001000CL)
#define NDIS_STATUS_RESET_IN_PROGRESS           ((NDIS_STATUS)0xC001000DL)
#define NDIS_STATUS_CLOSING_INDICATING          ((NDIS_STATUS)0xC001000EL)
#define NDIS_STATUS_NOT_SUPPORTED               ((NDIS_STATUS)STATUS_NOT_SUPPORTED)
#define NDIS_STATUS_INVALID_PACKET              ((NDIS_STATUS)0xC001000FL)
#define NDIS_STATUS_OPEN_LIST_FULL              ((NDIS_STATUS)0xC0010010L)
#define NDIS_STATUS_ADAPTER_NOT_READY           ((NDIS_STATUS)0xC0010011L)
#define NDIS_STATUS_ADAPTER_NOT_OPEN            ((NDIS_STATUS)0xC0010012L)
#define NDIS_STATUS_NOT_INDICATING              ((NDIS_STATUS)0xC0010013L)
#define NDIS_STATUS_INVALID_LENGTH              ((NDIS_STATUS)0xC0010014L)
#define NDIS_STATUS_INVALID_DATA                ((NDIS_STATUS)0xC0010015L)
#define NDIS_STATUS_BUFFER_TOO_SHORT            ((NDIS_STATUS)0xC0010016L)
#define NDIS_STATUS_INVALID_OID                 ((NDIS_STATUS)0xC0010017L)
#define NDIS_STATUS_ADAPTER_REMOVED             ((NDIS_STATUS)0xC0010018L)
#define NDIS_STATUS_UNSUPPORTED_MEDIA           ((NDIS_STATUS)0xC0010019L)
#define NDIS_STATUS_GROUP_ADDRESS_IN_USE        ((NDIS_STATUS)0xC001001AL)
#define NDIS_STATUS_FILE_NOT_FOUND              ((NDIS_STATUS)0xC001001BL)
#define NDIS_STATUS_ERROR_READING_FILE          ((NDIS_STATUS)0xC001001CL)
#define NDIS_STATUS_ALREADY_MAPPED              ((NDIS_STATUS)0xC001001DL)
#define NDIS_STATUS_RESOURCE_CONFLICT           ((NDIS_STATUS)0xC001001EL)
#define NDIS_STATUS_NO_CABLE                    ((NDIS_STATUS)0xC001001FL)

#define NDIS_STATUS_INVALID_SAP                 ((NDIS_STATUS)0xC0010020L)
#define NDIS_STATUS_SAP_IN_USE                  ((NDIS_STATUS)0xC0010021L)
#define NDIS_STATUS_INVALID_ADDRESS             ((NDIS_STATUS)0xC0010022L)
#define NDIS_STATUS_VC_NOT_ACTIVATED            ((NDIS_STATUS)0xC0010023L)
#define NDIS_STATUS_DEST_OUT_OF_ORDER           ((NDIS_STATUS)0xC0010024L)  // cause 27
#define NDIS_STATUS_VC_NOT_AVAILABLE            ((NDIS_STATUS)0xC0010025L)  // cause 35,45
#define NDIS_STATUS_CELLRATE_NOT_AVAILABLE      ((NDIS_STATUS)0xC0010026L)  // cause 37
#define NDIS_STATUS_INCOMPATABLE_QOS            ((NDIS_STATUS)0xC0010027L)  // cause 49
#define NDIS_STATUS_AAL_PARAMS_UNSUPPORTED      ((NDIS_STATUS)0xC0010028L)  // cause 93
#define NDIS_STATUS_NO_ROUTE_TO_DESTINATION     ((NDIS_STATUS)0xC0010029L)  // cause 3
#define NDIS_STATUS_PAUSED                      ((NDIS_STATUS)0xC001002AL)
#define NDIS_STATUS_INTERFACE_NOT_FOUND         ((NDIS_STATUS)0xC001002BL)
#define NDIS_STATUS_INVALID_PARAMETER           ((NDIS_STATUS)STATUS_INVALID_PARAMETER)
#define NDIS_STATUS_UNSUPPORTED_REVISION        ((NDIS_STATUS)0xC001002CL)

#define NDIS_STATUS_TOKEN_RING_OPEN_ERROR       ((NDIS_STATUS)0xC0011000L)
#define NDIS_STATUS_INVALID_DEVICE_REQUEST      ((NDIS_STATUS)STATUS_INVALID_DEVICE_REQUEST)
#define NDIS_STATUS_NETWORK_UNREACHABLE         ((NDIS_STATUS)STATUS_NETWORK_UNREACHABLE)


#define NDIS_STATUS_UPLOAD_IN_PROGRESS          ((NDIS_STATUS)0xC0020001L)
#define NDIS_STATUS_REQUEST_UPLOAD              ((NDIS_STATUS)0xC0020002L)
#define NDIS_STATUS_UPLOAD_REQUESTED            ((NDIS_STATUS)0xC0020003L)
#define NDIS_STATUS_OFFLOAD_TCP_ENTRIES         ((NDIS_STATUS)0xC0020004L)
#define NDIS_STATUS_OFFLOAD_PATH_ENTRIES        ((NDIS_STATUS)0xC0020005L)
#define NDIS_STATUS_OFFLOAD_NEIGHBOR_ENTRIES    ((NDIS_STATUS)0xC0020006L)
#define NDIS_STATUS_OFFLOAD_IP_ADDRESS_ENTRIES  ((NDIS_STATUS)0xC0020007L)
#define NDIS_STATUS_OFFLOAD_HW_ADDRESS_ENTRIES  ((NDIS_STATUS)0xC0020008L)
#define NDIS_STATUS_OFFLOAD_VLAN_ENTRIES        ((NDIS_STATUS)0xC0020009L)
#define NDIS_STATUS_OFFLOAD_TCP_XMIT_BUFFER     ((NDIS_STATUS)0xC002000AL)
#define NDIS_STATUS_OFFLOAD_TCP_RCV_BUFFER      ((NDIS_STATUS)0xC002000BL)
#define NDIS_STATUS_OFFLOAD_TCP_RCV_WINDOW      ((NDIS_STATUS)0xC002000CL)


//
// used in error logging
//

#define NDIS_ERROR_CODE ULONG

#define NDIS_ERROR_CODE_RESOURCE_CONFLICT           EVENT_NDIS_RESOURCE_CONFLICT
#define NDIS_ERROR_CODE_OUT_OF_RESOURCES            EVENT_NDIS_OUT_OF_RESOURCE
#define NDIS_ERROR_CODE_HARDWARE_FAILURE            EVENT_NDIS_HARDWARE_FAILURE
#define NDIS_ERROR_CODE_ADAPTER_NOT_FOUND           EVENT_NDIS_ADAPTER_NOT_FOUND
#define NDIS_ERROR_CODE_INTERRUPT_CONNECT           EVENT_NDIS_INTERRUPT_CONNECT
#define NDIS_ERROR_CODE_DRIVER_FAILURE              EVENT_NDIS_DRIVER_FAILURE
#define NDIS_ERROR_CODE_BAD_VERSION                 EVENT_NDIS_BAD_VERSION
#define NDIS_ERROR_CODE_TIMEOUT                     EVENT_NDIS_TIMEOUT
#define NDIS_ERROR_CODE_NETWORK_ADDRESS             EVENT_NDIS_NETWORK_ADDRESS
#define NDIS_ERROR_CODE_UNSUPPORTED_CONFIGURATION   EVENT_NDIS_UNSUPPORTED_CONFIGURATION
#define NDIS_ERROR_CODE_INVALID_VALUE_FROM_ADAPTER  EVENT_NDIS_INVALID_VALUE_FROM_ADAPTER
#define NDIS_ERROR_CODE_MISSING_CONFIGURATION_PARAMETER EVENT_NDIS_MISSING_CONFIGURATION_PARAMETER
#define NDIS_ERROR_CODE_BAD_IO_BASE_ADDRESS         EVENT_NDIS_BAD_IO_BASE_ADDRESS
#define NDIS_ERROR_CODE_RECEIVE_SPACE_SMALL         EVENT_NDIS_RECEIVE_SPACE_SMALL
#define NDIS_ERROR_CODE_ADAPTER_DISABLED            EVENT_NDIS_ADAPTER_DISABLED

#if BINARY_COMPATIBLE

#if USE_KLOCKS

#define DISPATCH_LEVEL      2

#define NdisAllocateSpinLock(_SpinLock) KeInitializeSpinLock(&(_SpinLock)->SpinLock)

#define NdisFreeSpinLock(_SpinLock)

#define NdisAcquireSpinLock(_SpinLock)  KeAcquireSpinLock(&(_SpinLock)->SpinLock, &(_SpinLock)->OldIrql)

#define NdisReleaseSpinLock(_SpinLock)  KeReleaseSpinLock(&(_SpinLock)->SpinLock,(_SpinLock)->OldIrql)

#define NdisDprAcquireSpinLock(_SpinLock)                       \
{                                                               \
    KeAcquireSpinLockAtDpcLevel(&(_SpinLock)->SpinLock);        \
}

#define NdisDprReleaseSpinLock(_SpinLock) KeReleaseSpinLockFromDpcLevel(&(_SpinLock)->SpinLock)

#else

//
// Ndis Spin Locks
//
EXPORT
VOID
NdisAllocateSpinLock(
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
VOID
NdisFreeSpinLock(
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
VOID
NdisAcquireSpinLock(
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
VOID
NdisReleaseSpinLock(
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
VOID
NdisDprAcquireSpinLock(
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
VOID
NdisDprReleaseSpinLock(
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

#endif


EXPORT
VOID
NdisGetCurrentSystemTime(
    PLARGE_INTEGER              pSystemTime
    );

//
// Interlocked support functions
//

EXPORT
LONG
NdisInterlockedIncrement(
    IN  PLONG                   Addend
    );

EXPORT
LONG
NdisInterlockedDecrement(
    IN  PLONG                   Addend
    );

EXPORT
VOID
NdisInterlockedAddUlong(
    IN  PULONG                  Addend,
    IN  ULONG                   Increment,
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
PLIST_ENTRY
NdisInterlockedInsertHeadList(
    IN  PLIST_ENTRY             ListHead,
    IN  PLIST_ENTRY             ListEntry,
    IN  PNDIS_SPIN_LOCK         SpinLock
    );


EXPORT
PLIST_ENTRY
NdisInterlockedInsertTailList(
    IN  PLIST_ENTRY             ListHead,
    IN  PLIST_ENTRY             ListEntry,
    IN  PNDIS_SPIN_LOCK         SpinLock
    );


EXPORT
PLIST_ENTRY
NdisInterlockedRemoveHeadList(
    IN  PLIST_ENTRY             ListHead,
    IN  PNDIS_SPIN_LOCK         SpinLock
    );

EXPORT
LARGE_INTEGER
NdisInterlockedAddLargeInteger(
    IN  PLARGE_INTEGER          Addend,
    IN  ULONG                   Increment,
    IN  PKSPIN_LOCK             Lock
    );

#else // BINARY_COMPATIBLE

#define NdisAllocateSpinLock(_SpinLock) KeInitializeSpinLock(&(_SpinLock)->SpinLock)

#define NdisFreeSpinLock(_SpinLock)

#define NdisAcquireSpinLock(_SpinLock)  KeAcquireSpinLock(&(_SpinLock)->SpinLock, &(_SpinLock)->OldIrql)

#define NdisReleaseSpinLock(_SpinLock)  KeReleaseSpinLock(&(_SpinLock)->SpinLock,(_SpinLock)->OldIrql)

#define NdisDprAcquireSpinLock(_SpinLock)                                   \
{                                                                           \
    KeAcquireSpinLockAtDpcLevel(&(_SpinLock)->SpinLock);                    \
}

#define NdisDprReleaseSpinLock(_SpinLock) KeReleaseSpinLockFromDpcLevel(&(_SpinLock)->SpinLock)

#define NdisGetCurrentSystemTime(_pSystemTime)                              \
    {                                                                       \
        KeQuerySystemTime(_pSystemTime);                                    \
    }

//
// Interlocked support functions
//

#define NdisInterlockedIncrement(Addend)    InterlockedIncrement(Addend)

#define NdisInterlockedDecrement(Addend)    InterlockedDecrement(Addend)

#define NdisInterlockedAddUlong(_Addend, _Increment, _SpinLock) \
    ExInterlockedAddUlong(_Addend, _Increment, &(_SpinLock)->SpinLock)

#define NdisInterlockedInsertHeadList(_ListHead, _ListEntry, _SpinLock) \
    ExInterlockedInsertHeadList(_ListHead, _ListEntry, &(_SpinLock)->SpinLock)

#define NdisInterlockedInsertTailList(_ListHead, _ListEntry, _SpinLock) \
    ExInterlockedInsertTailList(_ListHead, _ListEntry, &(_SpinLock)->SpinLock)

#define NdisInterlockedRemoveHeadList(_ListHead, _SpinLock) \
    ExInterlockedRemoveHeadList(_ListHead, &(_SpinLock)->SpinLock)

#define NdisInterlockedPushEntryList(ListHead, ListEntry, Lock) \
    ExInterlockedPushEntryList(ListHead, ListEntry, &(Lock)->SpinLock)

#define NdisInterlockedPopEntryList(ListHead, Lock) \
    ExInterlockedPopEntryList(ListHead, &(Lock)->SpinLock)

#endif // BINARY_COMPATIBLE

#ifndef MAXIMUM_PROCESSORS
#ifdef _WIN64
#define MAXIMUM_PROCESSORS 64
#else
#define MAXIMUM_PROCESSORS 32
#endif
#endif

typedef union _NDIS_RW_LOCK_REFCOUNT
{
    UINT                        RefCount;
    UCHAR                       cacheLine[16];  // One refCount per cache line
} NDIS_RW_LOCK_REFCOUNT;

typedef struct _NDIS_RW_LOCK
{
    union
    {
        struct
        {
            KSPIN_LOCK          SpinLock;
            PVOID               Context;
        };
        UCHAR                   Reserved[16];
    };

    NDIS_RW_LOCK_REFCOUNT       RefCount[MAXIMUM_PROCESSORS];
} NDIS_RW_LOCK, *PNDIS_RW_LOCK;

typedef struct _LOCK_STATE
{
    USHORT                      LockState;
    KIRQL                       OldIrql;
} LOCK_STATE, *PLOCK_STATE;


EXPORT
VOID
NdisInitializeReadWriteLock(
    IN  PNDIS_RW_LOCK           Lock
    );


EXPORT
VOID
NdisAcquireReadWriteLock(
    IN  PNDIS_RW_LOCK           Lock,
    IN  BOOLEAN                 fWrite,         // TRUE -> Write, FALSE -> Read
    IN  PLOCK_STATE             LockState
    );


EXPORT
VOID
NdisReleaseReadWriteLock(
    IN  PNDIS_RW_LOCK           Lock,
    IN  PLOCK_STATE             LockState
    );


#define NdisInterlockedAddLargeStatistic(_Addend, _Increment)   \
    ExInterlockedAddLargeStatistic((PLARGE_INTEGER)_Addend, _Increment)

//
// S-List support
//

#define NdisInterlockedPushEntrySList(SListHead, SListEntry, Lock) \
    ExInterlockedPushEntrySList(SListHead, SListEntry, &(Lock)->SpinLock)

#define NdisInterlockedPopEntrySList(SListHead, Lock) \
    ExInterlockedPopEntrySList(SListHead, &(Lock)->SpinLock)

#define NdisInterlockedFlushSList(SListHead) ExInterlockedFlushSList(SListHead)

#define NdisInitializeSListHead(SListHead)  ExInitializeSListHead(SListHead)

#define NdisQueryDepthSList(SListHead)  ExQueryDepthSList(SListHead)

EXPORT
VOID
NdisGetCurrentProcessorCpuUsage(
    OUT PULONG                  pCpuUsage
    );

EXPORT
VOID
NdisGetCurrentProcessorCounts(
    OUT PULONG                  pIdleCount,
    OUT PULONG                  pKernelAndUser,
    OUT PULONG                  pIndex
    );

EXPORT
VOID
NdisGetSystemUpTime(
    OUT PULONG                  pSystemUpTime
    );

//
// List manipulation
//

/*++

VOID
NdisInitializeListHead(
    IN  PLIST_ENTRY ListHead
    );

--*/
#define NdisInitializeListHead(_ListHead) InitializeListHead(_ListHead)


//
// Configuration Requests
//

EXPORT
VOID
NdisOpenConfiguration(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            ConfigurationHandle,
    IN  NDIS_HANDLE             WrapperConfigurationContext
    );

EXPORT
VOID
NdisOpenConfigurationKeyByName(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             ConfigurationHandle,
    IN  PNDIS_STRING            SubKeyName,
    OUT PNDIS_HANDLE            SubKeyHandle
    );

EXPORT
VOID
NdisOpenConfigurationKeyByIndex(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             ConfigurationHandle,
    IN  ULONG                   Index,
    OUT PNDIS_STRING            KeyName,
    OUT PNDIS_HANDLE            KeyHandle
    );

EXPORT
VOID
NdisReadConfiguration(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_CONFIGURATION_PARAMETER *ParameterValue,
    IN  NDIS_HANDLE             ConfigurationHandle,
    IN  PNDIS_STRING            Keyword,
    IN  NDIS_PARAMETER_TYPE     ParameterType
    );

EXPORT
VOID
NdisWriteConfiguration(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             ConfigurationHandle,
    IN  PNDIS_STRING            Keyword,
    IN  PNDIS_CONFIGURATION_PARAMETER ParameterValue
    );

EXPORT
VOID
NdisCloseConfiguration(
    IN  NDIS_HANDLE             ConfigurationHandle
    );

EXPORT
VOID
NdisReadNetworkAddress(
    OUT PNDIS_STATUS            Status,
    OUT PVOID *                 NetworkAddress,
    OUT PUINT                   NetworkAddressLength,
    IN  NDIS_HANDLE             ConfigurationHandle
    );


EXPORT
VOID
NdisWriteNetworkAddress(
    OUT PNDIS_STATUS                Status,
    IN  PUCHAR                      NetworkAddress,
    IN  UINT                        NetworkAddressLength,
    IN  NDIS_HANDLE                 ConfigurationHandle
    );

EXPORT
VOID
NdisReadEisaSlotInformation(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             WrapperConfigurationContext,
    OUT PUINT                   SlotNumber,
    OUT PNDIS_EISA_FUNCTION_INFORMATION EisaData
    );

EXPORT
VOID
NdisReadEisaSlotInformationEx(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             WrapperConfigurationContext,
    OUT PUINT                   SlotNumber,
    OUT PNDIS_EISA_FUNCTION_INFORMATION *EisaData,
    OUT PUINT                   NumberOfFunctions
    );

EXPORT
ULONG
NdisReadPciSlotInformation(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   SlotNumber,
    IN  ULONG                   Offset,
    IN  PVOID                   Buffer,
    IN  ULONG                   Length
    );

EXPORT
ULONG
NdisWritePciSlotInformation(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   SlotNumber,
    IN  ULONG                   Offset,
    IN  PVOID                   Buffer,
    IN  ULONG                   Length
    );

EXPORT
ULONG
NdisReadPcmciaAttributeMemory(
    IN NDIS_HANDLE              NdisAdapterHandle,
    IN ULONG                    Offset,
    IN PVOID                    Buffer,
    IN ULONG                    Length
    );

EXPORT
ULONG
NdisWritePcmciaAttributeMemory(
    IN NDIS_HANDLE              NdisAdapterHandle,
    IN ULONG                    Offset,
    IN PVOID                    Buffer,
    IN ULONG                    Length
    );

//
// Buffer Pool
//

EXPORT
VOID
NdisAllocateBufferPool(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            PoolHandle,
    IN  UINT                    NumberOfDescriptors
    );

EXPORT
VOID
NdisFreeBufferPool(
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
VOID
NdisAllocateBuffer(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_BUFFER *          Buffer,
    IN  NDIS_HANDLE             PoolHandle,
    IN  PVOID                   VirtualAddress,
    IN  UINT                    Length
    );

EXPORT
VOID
NdisCopyBuffer(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_BUFFER *          Buffer,
    IN  NDIS_HANDLE             PoolHandle,
    IN  PVOID                   MemoryDescriptor,
    IN  UINT                    Offset,
    IN  UINT                    Length
    );


//
//  VOID
//  NdisCopyLookaheadData(
//      IN  PVOID               Destination,
//      IN  PVOID               Source,
//      IN  ULONG               Length,
//      IN  ULONG               ReceiveFlags
//      );
//

#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisCopyLookaheadData(_Destination, _Source, _Length, _MacOptions)  \
        RtlCopyMemory(_Destination, _Source, _Length)
#else
#define NdisCopyLookaheadData(_Destination, _Source, _Length, _MacOptions)  \
    {                                                                       \
        if ((_MacOptions) & NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA)            \
        {                                                                   \
            RtlCopyMemory(_Destination, _Source, _Length);                  \
        }                                                                   \
        else                                                                \
        {                                                                   \
            PUCHAR _Src = (PUCHAR)(_Source);                                \
            PUCHAR _Dest = (PUCHAR)(_Destination);                          \
            PUCHAR _End = _Dest + (_Length);                                \
            while (_Dest < _End)                                            \
            {                                                               \
                *_Dest++ = *_Src++;                                         \
            }                                                               \
        }                                                                   \
    }
#endif

//
// Packet Pool
//
EXPORT
VOID
NdisAllocatePacketPool(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            PoolHandle,
    IN  UINT                    NumberOfDescriptors,
    IN  UINT                    ProtocolReservedLength
    );

EXPORT
VOID
NdisAllocatePacketPoolEx(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            PoolHandle,
    IN  UINT                    NumberOfDescriptors,
    IN  UINT                    NumberOfOverflowDescriptors,
    IN  UINT                    ProtocolReservedLength
    );

EXPORT
VOID
NdisSetPacketPoolProtocolId(
    IN  NDIS_HANDLE             PacketPoolHandle,
    IN  UINT                    ProtocolId
    );

EXPORT
UINT
NdisPacketPoolUsage(
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
UINT
NdisPacketSize(
    IN  UINT                    ProtocolReservedSize
    );

EXPORT
NDIS_HANDLE
NdisGetPoolFromPacket(
    IN  PNDIS_PACKET            Packet
    );

EXPORT
PNDIS_PACKET_STACK
NdisIMGetCurrentPacketStack(
    IN  PNDIS_PACKET            Packet,
    OUT BOOLEAN *               StacksRemaining
    );

EXPORT
VOID
NdisFreePacketPool(
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
VOID
NdisFreePacket(
    IN  PNDIS_PACKET            Packet
    );

EXPORT
VOID
NdisDprFreePacket(
    IN  PNDIS_PACKET            Packet
    );

EXPORT
VOID
NdisDprFreePacketNonInterlocked(
    IN  PNDIS_PACKET            Packet
    );


EXPORT
VOID
NdisAllocatePacket(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_PACKET *          Packet,
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
VOID
NdisDprAllocatePacket(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_PACKET *          Packet,
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
VOID
NdisDprAllocatePacketNonInterlocked(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_PACKET *          Packet,
    IN  NDIS_HANDLE             PoolHandle
    );

// VOID
// NdisReinitializePacket(
//  IN OUT PNDIS_PACKET         Packet
//  );
#define NdisReinitializePacket(Packet)                                      \
{                                                                           \
    (Packet)->Private.Head = (PNDIS_BUFFER)NULL;                            \
    (Packet)->Private.ValidCounts = FALSE;                                  \
}


//
// Block Pool APIs
//
typedef
VOID
(__stdcall *NDIS_BLOCK_INITIALIZER) (
    IN  PUCHAR                  Block,
    IN  SIZE_T                  NumberOfBytes
    );

NDIS_HANDLE
NdisCreateBlockPool(
    IN  USHORT                  BlockSize,
    IN  USHORT                  FreeBlockLinkOffset,
    IN  ULONG                   Tag,
    IN  NDIS_BLOCK_INITIALIZER  InitFunction OPTIONAL
    );

VOID
NdisDestroyBlockPool(
    IN  NDIS_HANDLE             BlockPoolHandle
    );

PUCHAR
NdisAllocateFromBlockPool(
    IN  NDIS_HANDLE             BlockPoolHandle
    );

VOID
NdisFreeToBlockPool(
    IN  PUCHAR                  Block
    );


PUCHAR
NdisAllocateFromBlockPoolAtDpcLevel(
    IN  NDIS_HANDLE             BlockPoolHandle
    );

VOID
NdisFreeToBlockPoolAtDpcLevel(
    IN  PUCHAR                  Block
    );


#if BINARY_COMPATIBLE

EXPORT
VOID
NdisFreeBuffer(
    IN  PNDIS_BUFFER            Buffer
    );

EXPORT
VOID
NdisQueryBuffer(
    IN  PNDIS_BUFFER            Buffer,
    OUT PVOID *                 VirtualAddress OPTIONAL,
    OUT PUINT                   Length
    );

EXPORT
VOID
NdisQueryBufferSafe(
    IN  PNDIS_BUFFER            Buffer,
    OUT PVOID *                 VirtualAddress OPTIONAL,
    OUT PUINT                   Length,
    IN  MM_PAGE_PRIORITY        Priority
    );

EXPORT
VOID
NdisQueryBufferOffset(
    IN  PNDIS_BUFFER            Buffer,
    OUT PUINT                   Offset,
    OUT PUINT                   Length
    );

//
// This is a combination of NdisQueryPacket and NdisQueryBuffer and
// optimized for protocols to get the first Buffer, its VA and its size.
//
VOID
NdisGetFirstBufferFromPacket(
    IN  PNDIS_PACKET            Packet,
    OUT PNDIS_BUFFER *          FirstBuffer,
    OUT PVOID *                 FirstBufferVA,
    OUT PUINT                   FirstBufferLength,
    OUT PUINT                   TotalBufferLength
    );

VOID
NdisGetFirstBufferFromPacketSafe(
    IN  PNDIS_PACKET            Packet,
    OUT PNDIS_BUFFER *          FirstBuffer,
    OUT PVOID *                 FirstBufferVA,
    OUT PUINT                   FirstBufferLength,
    OUT PUINT                   TotalBufferLength,
    IN  MM_PAGE_PRIORITY        Priority
    );


//
// This is used to determine how many physical pieces
// an NDIS_BUFFER will take up when mapped.
//

EXPORT
ULONG
NDIS_BUFFER_TO_SPAN_PAGES(
    IN  PNDIS_BUFFER                Buffer
    );

EXPORT
VOID
NdisGetBufferPhysicalArraySize(
    IN  PNDIS_BUFFER                Buffer,
    OUT PUINT                       ArraySize
    );

#else // BINARY_COMPATIBLE

#define NdisFreeBuffer(Buffer)  IoFreeMdl(Buffer)

#define NdisQueryBuffer(_Buffer, _VirtualAddress, _Length)                  \
{                                                                           \
    if (ARGUMENT_PRESENT(_VirtualAddress))                                  \
    {                                                                       \
        *(PVOID *)(_VirtualAddress) = MmGetSystemAddressForMdl(_Buffer);    \
    }                                                                       \
    *(_Length) = MmGetMdlByteCount(_Buffer);                                \
}

#define NdisQueryBufferSafe(_Buffer, _VirtualAddress, _Length, _Priority)   \
{                                                                           \
    if (ARGUMENT_PRESENT(_VirtualAddress))                                  \
    {                                                                       \
        *(PVOID *)(_VirtualAddress) = MmGetSystemAddressForMdlSafe(_Buffer, _Priority); \
    }                                                                       \
    *(_Length) = MmGetMdlByteCount(_Buffer);                                \
}

#define NdisQueryBufferOffset(_Buffer, _Offset, _Length)                    \
{                                                                           \
    *(_Offset) = MmGetMdlByteOffset(_Buffer);                               \
    *(_Length) = MmGetMdlByteCount(_Buffer);                                \
}


#define NdisGetFirstBufferFromPacket(_Packet,                               \
                                     _FirstBuffer,                          \
                                     _FirstBufferVA,                        \
                                     _FirstBufferLength,                    \
                                     _TotalBufferLength)                    \
    {                                                                       \
        PNDIS_BUFFER    _pBuf;                                              \
                                                                            \
        _pBuf = (_Packet)->Private.Head;                                    \
        *(_FirstBuffer) = _pBuf;                                            \
        if (_pBuf)                                                          \
        {                                                                   \
            *(_FirstBufferVA) = MmGetSystemAddressForMdl(_pBuf);            \
            *(_FirstBufferLength) =                                         \
            *(_TotalBufferLength) = MmGetMdlByteCount(_pBuf);               \
            for (_pBuf = _pBuf->Next;                                       \
                 _pBuf != NULL;                                             \
                 _pBuf = _pBuf->Next)                                       \
            {                                                               \
                *(_TotalBufferLength) += MmGetMdlByteCount(_pBuf);          \
            }                                                               \
        }                                                                   \
        else                                                                \
        {                                                                   \
            *(_FirstBufferVA) = 0;                                          \
            *(_FirstBufferLength) = 0;                                      \
            *(_TotalBufferLength) = 0;                                      \
        }                                                                   \
    }

#define NdisGetFirstBufferFromPacketSafe(_Packet,                           \
                                         _FirstBuffer,                      \
                                         _FirstBufferVA,                    \
                                         _FirstBufferLength,                \
                                         _TotalBufferLength,                \
                                         _Priority)                         \
    {                                                                       \
        PNDIS_BUFFER    _pBuf;                                              \
                                                                            \
        _pBuf = (_Packet)->Private.Head;                                    \
        *(_FirstBuffer) = _pBuf;                                            \
        if (_pBuf)                                                          \
        {                                                                   \
            *(_FirstBufferVA) = MmGetSystemAddressForMdlSafe(_pBuf, _Priority); \
            *(_FirstBufferLength) = *(_TotalBufferLength) = MmGetMdlByteCount(_pBuf); \
            for (_pBuf = _pBuf->Next;                                       \
                 _pBuf != NULL;                                             \
                 _pBuf = _pBuf->Next)                                       \
            {                                                               \
                *(_TotalBufferLength) += MmGetMdlByteCount(_pBuf);          \
            }                                                               \
        }                                                                   \
        else                                                                \
        {                                                                   \
            *(_FirstBufferVA) = 0;                                          \
            *(_FirstBufferLength) = 0;                                      \
            *(_TotalBufferLength) = 0;                                      \
        }                                                                   \
    }


#define NDIS_BUFFER_TO_SPAN_PAGES(_Buffer)                                  \
    (MmGetMdlByteCount(_Buffer)==0 ?                                        \
                1 :                                                         \
                (ADDRESS_AND_SIZE_TO_SPAN_PAGES(                            \
                        MmGetMdlVirtualAddress(_Buffer),                    \
                        MmGetMdlByteCount(_Buffer))))

#define NdisGetBufferPhysicalArraySize(Buffer, ArraySize)                   \
    (*(ArraySize) = NDIS_BUFFER_TO_SPAN_PAGES(Buffer))

#endif // BINARY_COMPATIBLE


/*++

NDIS_BUFFER_LINKAGE(
    IN  PNDIS_BUFFER            Buffer
    );

--*/

#define NDIS_BUFFER_LINKAGE(Buffer) ((Buffer)->Next)


/*++

VOID
NdisRecalculatePacketCounts(
    IN OUT PNDIS_PACKET         Packet
    );

--*/

#define NdisRecalculatePacketCounts(Packet)                                 \
{                                                                           \
    {                                                                       \
        PNDIS_BUFFER TmpBuffer = (Packet)->Private.Head;                    \
        if (TmpBuffer)                                                      \
        {                                                                   \
            while (TmpBuffer->Next)                                         \
            {                                                               \
                TmpBuffer = TmpBuffer->Next;                                \
            }                                                               \
            (Packet)->Private.Tail = TmpBuffer;                             \
        }                                                                   \
        (Packet)->Private.ValidCounts = FALSE;                              \
    }                                                                       \
}


/*++

VOID
NdisChainBufferAtFront(
    IN OUT PNDIS_PACKET         Packet,
    IN OUT PNDIS_BUFFER         Buffer
    );

--*/

#define NdisChainBufferAtFront(Packet, Buffer)                              \
{                                                                           \
    PNDIS_BUFFER TmpBuffer = (Buffer);                                      \
                                                                            \
    for (;;)                                                                \
    {                                                                       \
        if (TmpBuffer->Next == (PNDIS_BUFFER)NULL)                          \
            break;                                                          \
        TmpBuffer = TmpBuffer->Next;                                        \
    }                                                                       \
    if ((Packet)->Private.Head == NULL)                                     \
    {                                                                       \
        (Packet)->Private.Tail = TmpBuffer;                                 \
    }                                                                       \
    TmpBuffer->Next = (Packet)->Private.Head;                               \
    (Packet)->Private.Head = (Buffer);                                      \
    (Packet)->Private.ValidCounts = FALSE;                                  \
}

/*++

VOID
NdisChainBufferAtBack(
    IN OUT PNDIS_PACKET         Packet,
    IN OUT PNDIS_BUFFER         Buffer
    );

--*/

#define NdisChainBufferAtBack(Packet, Buffer)                               \
{                                                                           \
    PNDIS_BUFFER TmpBuffer = (Buffer);                                      \
                                                                            \
    for (;;)                                                                \
    {                                                                       \
        if (TmpBuffer->Next == NULL)                                        \
            break;                                                          \
        TmpBuffer = TmpBuffer->Next;                                        \
    }                                                                       \
    if ((Packet)->Private.Head != NULL)                                     \
    {                                                                       \
        (Packet)->Private.Tail->Next = (Buffer);                            \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        (Packet)->Private.Head = (Buffer);                                  \
    }                                                                       \
    (Packet)->Private.Tail = TmpBuffer;                                     \
    (Packet)->Private.ValidCounts = FALSE;                                  \
}

EXPORT
VOID
NdisUnchainBufferAtFront(
    IN OUT PNDIS_PACKET         Packet,
    OUT PNDIS_BUFFER *          Buffer
    );

EXPORT
VOID
NdisUnchainBufferAtBack(
    IN OUT PNDIS_PACKET         Packet,
    OUT PNDIS_BUFFER *          Buffer
    );


/*++

VOID
NdisQueryPacket(
    IN  PNDIS_PACKET            _Packet,
    OUT PUINT                   _PhysicalBufferCount OPTIONAL,
    OUT PUINT                   _BufferCount OPTIONAL,
    OUT PNDIS_BUFFER *          _FirstBuffer OPTIONAL,
    OUT PUINT                   _TotalPacketLength OPTIONAL
    );

--*/

#pragma warning(push)
#pragma warning(disable:4127)
__inline
VOID
NdisQueryPacket(
    IN  PNDIS_PACKET            _Packet,
    OUT PUINT                   _PhysicalBufferCount OPTIONAL,
    OUT PUINT                   _BufferCount OPTIONAL,
    OUT PNDIS_BUFFER *          _FirstBuffer OPTIONAL,
    OUT PUINT                   _TotalPacketLength OPTIONAL
    )
{
    if ((_FirstBuffer) != NULL)
    {
        PNDIS_BUFFER * __FirstBuffer = (_FirstBuffer);
        *(__FirstBuffer) = (_Packet)->Private.Head;
    }
    if ((_TotalPacketLength) || (_BufferCount) || (_PhysicalBufferCount))
    {
        if (!(_Packet)->Private.ValidCounts)
        {
            PNDIS_BUFFER TmpBuffer = (_Packet)->Private.Head;
            UINT PTotalLength = 0, PPhysicalCount = 0, PAddedCount = 0;
            UINT PacketLength, Offset;

            while (TmpBuffer != (PNDIS_BUFFER)NULL)
            {
                NdisQueryBufferOffset(TmpBuffer, &Offset, &PacketLength);
                PTotalLength += PacketLength;
                PPhysicalCount += (UINT)NDIS_BUFFER_TO_SPAN_PAGES(TmpBuffer);
                ++PAddedCount;
                TmpBuffer = TmpBuffer->Next;
            }
            (_Packet)->Private.Count = PAddedCount;
            (_Packet)->Private.TotalLength = PTotalLength;
            (_Packet)->Private.PhysicalCount = PPhysicalCount;
            (_Packet)->Private.ValidCounts = TRUE;
        }

        if (_PhysicalBufferCount)
        {
            PUINT __PhysicalBufferCount = (_PhysicalBufferCount);
            *(__PhysicalBufferCount) = (_Packet)->Private.PhysicalCount;
        }
        if (_BufferCount)
        {
            PUINT __BufferCount = (_BufferCount);
            *(__BufferCount) = (_Packet)->Private.Count;
        }
        if (_TotalPacketLength)
        {
            PUINT __TotalPacketLength = (_TotalPacketLength);
            *(__TotalPacketLength) = (_Packet)->Private.TotalLength;
        }
    }
}
#pragma warning(pop)

/*++

VOID
NdisQueryPacketLength(
    IN  PNDIS_PACKET            _Packet,
    OUT PUINT                   _TotalPacketLength OPTIONAL
    );

--*/

#define NdisQueryPacketLength(_Packet,                                      \
                              _TotalPacketLength)                           \
{                                                                           \
    if (!(_Packet)->Private.ValidCounts)                                    \
    {                                                                       \
        NdisQueryPacket(_Packet, NULL, NULL, NULL, _TotalPacketLength);     \
    }                                                                       \
    else *(_TotalPacketLength) = (_Packet)->Private.TotalLength;            \
}


/*++

VOID
NdisGetNextBuffer(
    IN  PNDIS_BUFFER            CurrentBuffer,
    OUT PNDIS_BUFFER *          NextBuffer
    );

--*/

#define NdisGetNextBuffer(CurrentBuffer, NextBuffer)                        \
{                                                                           \
    *(NextBuffer) = (CurrentBuffer)->Next;                                  \
}

#if BINARY_COMPATIBLE

VOID
NdisAdjustBufferLength(
    IN  PNDIS_BUFFER            Buffer,
    IN  UINT                    Length
    );

#else // BINARY_COMPATIBLE

#define NdisAdjustBufferLength(Buffer, Length)  (((Buffer)->ByteCount) = (Length))

#endif // BINARY_COMPATIBLE

/*
VOID
NdisAdjustMdlLength(
    IN  PMDL                    Mdl,
    IN  UINT                    Length
    );

*/
#define NdisAdjustMdlLength(_Mdl, _Length)  (((Mdl)->ByteCount) = (Length))

EXPORT
VOID
NdisCopyFromPacketToPacket(
    IN  PNDIS_PACKET            Destination,
    IN  UINT                    DestinationOffset,
    IN  UINT                    BytesToCopy,
    IN  PNDIS_PACKET            Source,
    IN  UINT                    SourceOffset,
    OUT PUINT                   BytesCopied
    );

EXPORT
VOID
NdisCopyFromPacketToPacketSafe(
    IN  PNDIS_PACKET            Destination,
    IN  UINT                    DestinationOffset,
    IN  UINT                    BytesToCopy,
    IN  PNDIS_PACKET            Source,
    IN  UINT                    SourceOffset,
    OUT PUINT                   BytesCopied,
    IN  MM_PAGE_PRIORITY        Priority
    );

DECLSPEC_DEPRECATED_DDK
EXPORT
NDIS_STATUS
NdisAllocateMemory(
    OUT PVOID *                 VirtualAddress,
    IN  UINT                    Length,
    IN  UINT                    MemoryFlags,
    IN  NDIS_PHYSICAL_ADDRESS   HighestAcceptableAddress
    );

EXPORT
NDIS_STATUS
NdisAllocateMemoryWithTag(
    OUT PVOID *                 VirtualAddress,
    IN  UINT                    Length,
    IN  ULONG                   Tag
    );

EXPORT
VOID
NdisFreeMemory(
    IN  PVOID                   VirtualAddress,
    IN  UINT                    Length,
    IN  UINT                    MemoryFlags
    );


/*++
VOID
NdisStallExecution(
    IN  UINT                    MicrosecondsToStall
    )
--*/

#define NdisStallExecution(MicroSecondsToStall)     KeStallExecutionProcessor(MicroSecondsToStall)





EXPORT
VOID
NdisInitializeEvent(
    IN  PNDIS_EVENT             Event
);

EXPORT
VOID
NdisSetEvent(
    IN  PNDIS_EVENT             Event
);

EXPORT
VOID
NdisResetEvent(
    IN  PNDIS_EVENT             Event
);

EXPORT
BOOLEAN
NdisWaitEvent(
    IN  PNDIS_EVENT             Event,
    IN  UINT                    msToWait
);

/*++
VOID
NdisInitializeWorkItem(
    IN  PNDIS_WORK_ITEM         WorkItem,
    IN  NDIS_PROC               Routine,
    IN  PVOID                   Context
    );
--*/

#define NdisInitializeWorkItem(_WI_, _R_, _C_)  \
    {                                           \
        (_WI_)->Context = _C_;                  \
        (_WI_)->Routine = _R_;                  \
    }

EXPORT
NDIS_STATUS
NdisScheduleWorkItem(
    IN  PNDIS_WORK_ITEM         WorkItem
    );

//
// Simple I/O support
//

EXPORT
VOID
NdisOpenFile(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            FileHandle,
    OUT PUINT                   FileLength,
    IN  PNDIS_STRING            FileName,
    IN  NDIS_PHYSICAL_ADDRESS   HighestAcceptableAddress
    );

EXPORT
VOID
NdisCloseFile(
    IN  NDIS_HANDLE             FileHandle
    );

EXPORT
VOID
NdisMapFile(
    OUT PNDIS_STATUS            Status,
    OUT PVOID *                 MappedBuffer,
    IN  NDIS_HANDLE             FileHandle
    );

EXPORT
VOID
NdisUnmapFile(
    IN  NDIS_HANDLE             FileHandle
    );


//
// Portability extensions
//

/*++
VOID
NdisFlushBuffer(
    IN  PNDIS_BUFFER            Buffer,
    IN  BOOLEAN                 WriteToDevice
    )
--*/

#define NdisFlushBuffer(Buffer,WriteToDevice)                               \
        KeFlushIoBuffers((Buffer),!(WriteToDevice), TRUE)

EXPORT
ULONG
NdisGetSharedDataAlignment(
    VOID
    );


//
// Write Port
//

/*++
VOID
NdisWritePortUchar(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    IN  UCHAR                   Data
    )
--*/
#define NdisWritePortUchar(Handle,Port,Data)                                \
        WRITE_PORT_UCHAR((PUCHAR)(NDIS_PORT_TO_PORT(Handle,Port)),(UCHAR)(Data))

/*++
VOID
NdisWritePortUshort(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    IN  USHORT                  Data
    )
--*/
#define NdisWritePortUshort(Handle,Port,Data)                               \
        WRITE_PORT_USHORT((PUSHORT)(NDIS_PORT_TO_PORT(Handle,Port)),(USHORT)(Data))


/*++
VOID
NdisWritePortUlong(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    IN  ULONG                   Data
    )
--*/
#define NdisWritePortUlong(Handle,Port,Data)                                \
        WRITE_PORT_ULONG((PULONG)(NDIS_PORT_TO_PORT(Handle,Port)),(ULONG)(Data))


//
// Write Port Buffers
//

/*++
VOID
NdisWritePortBufferUchar(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    IN  PUCHAR                  Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisWritePortBufferUchar(Handle,Port,Buffer,Length)                 \
        NdisRawWritePortBufferUchar(NDIS_PORT_TO_PORT((Handle),(Port)),(Buffer),(Length))

/*++
VOID
NdisWritePortBufferUshort(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    IN  PUSHORT                 Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisWritePortBufferUshort(Handle,Port,Buffer,Length)                \
        NdisRawWritePortBufferUshort(NDIS_PORT_TO_PORT((Handle),(Port)),(Buffer),(Length))


/*++
VOID
NdisWritePortBufferUlong(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    IN  PULONG                  Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisWritePortBufferUlong(Handle,Port,Buffer,Length)                 \
        NdisRawWritePortBufferUlong(NDIS_PORT_TO_PORT((Handle),(Port)),(Buffer),(Length))


//
// Read Ports
//

/*++
VOID
NdisReadPortUchar(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    OUT PUCHAR                  Data
    )
--*/
#define NdisReadPortUchar(Handle,Port, Data)                                \
        NdisRawReadPortUchar(NDIS_PORT_TO_PORT((Handle),(Port)),(Data))

/*++
VOID
NdisReadPortUshort(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    OUT PUSHORT                 Data
    )
--*/
#define NdisReadPortUshort(Handle,Port,Data)                                \
        NdisRawReadPortUshort(NDIS_PORT_TO_PORT((Handle),(Port)),(Data))


/*++
VOID
NdisReadPortUlong(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    OUT PULONG                  Data
    )
--*/
#define NdisReadPortUlong(Handle,Port,Data)                                 \
        NdisRawReadPortUlong(NDIS_PORT_TO_PORT((Handle),(Port)),(Data))

//
// Read Buffer Ports
//

/*++
VOID
NdisReadPortBufferUchar(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    OUT PUCHAR                  Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisReadPortBufferUchar(Handle,Port,Buffer,Length)                  \
        NdisRawReadPortBufferUchar(NDIS_PORT_TO_PORT((Handle),(Port)),(Buffer),(Length))

/*++
VOID
NdisReadPortBufferUshort(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    OUT PUSHORT                 Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisReadPortBufferUshort(Handle,Port,Buffer,Length)                 \
        NdisRawReadPortBufferUshort(NDIS_PORT_TO_PORT((Handle),(Port)),(Buffer),(Length))

/*++
VOID
NdisReadPortBufferUlong(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  ULONG                   Port,
    OUT PULONG                  Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisReadPortBufferUlong(Handle,Port,Buffer)                         \
        NdisRawReadPortBufferUlong(NDIS_PORT_TO_PORT((Handle),(Port)),(Buffer),(Length))

//
// Raw Routines
//

//
// Write Port Raw
//

/*++
VOID
NdisRawWritePortUchar(
    IN  ULONG_PTR               Port,
    IN  UCHAR                   Data
    )
--*/
#define NdisRawWritePortUchar(Port,Data)                                    \
        WRITE_PORT_UCHAR((PUCHAR)(Port),(UCHAR)(Data))

/*++
VOID
NdisRawWritePortUshort(
    IN  ULONG_PTR               Port,
    IN  USHORT                  Data
    )
--*/
#define NdisRawWritePortUshort(Port,Data)                                   \
        WRITE_PORT_USHORT((PUSHORT)(Port),(USHORT)(Data))

/*++
VOID
NdisRawWritePortUlong(
    IN  ULONG_PTR               Port,
    IN  ULONG                   Data
    )
--*/
#define NdisRawWritePortUlong(Port,Data)                                    \
        WRITE_PORT_ULONG((PULONG)(Port),(ULONG)(Data))


//
// Raw Write Port Buffers
//

/*++
VOID
NdisRawWritePortBufferUchar(
    IN  ULONG_PTR               Port,
    IN  PUCHAR                  Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisRawWritePortBufferUchar(Port,Buffer,Length) \
        WRITE_PORT_BUFFER_UCHAR((PUCHAR)(Port),(PUCHAR)(Buffer),(Length))

/*++
VOID
NdisRawWritePortBufferUshort(
    IN  ULONG_PTR               Port,
    IN  PUSHORT                 Buffer,
    IN  ULONG                   Length
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisRawWritePortBufferUshort(Port,Buffer,Length)                    \
        WRITE_PORT_BUFFER_USHORT((PUSHORT)(Port),(PUSHORT)(Buffer),(Length))
#else
#define NdisRawWritePortBufferUshort(Port,Buffer,Length)                    \
{                                                                           \
        ULONG_PTR _Port = (ULONG_PTR)(Port);                                \
        PUSHORT _Current = (Buffer);                                        \
        PUSHORT _End = _Current + (Length);                                 \
        for ( ; _Current < _End; ++_Current)                                \
        {                                                                   \
            WRITE_PORT_USHORT((PUSHORT)_Port,*(UNALIGNED USHORT *)_Current);\
        }                                                                   \
}
#endif


/*++
VOID
NdisRawWritePortBufferUlong(
    IN  ULONG_PTR               Port,
    IN  PULONG                  Buffer,
    IN  ULONG                   Length
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisRawWritePortBufferUlong(Port,Buffer,Length)                     \
        WRITE_PORT_BUFFER_ULONG((PULONG)(Port),(PULONG)(Buffer),(Length))
#else
#define NdisRawWritePortBufferUlong(Port,Buffer,Length)                     \
{                                                                           \
        ULONG_PTR _Port = (ULONG_PTR)(Port);                                \
        PULONG _Current = (Buffer);                                         \
        PULONG _End = _Current + (Length);                                  \
        for ( ; _Current < _End; ++_Current)                                \
        {                                                                   \
            WRITE_PORT_ULONG((PULONG)_Port,*(UNALIGNED ULONG *)_Current);   \
        }                                                                   \
}
#endif


//
// Raw Read Ports
//

/*++
VOID
NdisRawReadPortUchar(
    IN  ULONG_PTR               Port,
    OUT PUCHAR                  Data
    )
--*/
#define NdisRawReadPortUchar(Port, Data) \
        *(Data) = READ_PORT_UCHAR((PUCHAR)(Port))

/*++
VOID
NdisRawReadPortUshort(
    IN  ULONG_PTR               Port,
    OUT PUSHORT                 Data
    )
--*/
#define NdisRawReadPortUshort(Port,Data) \
        *(Data) = READ_PORT_USHORT((PUSHORT)(Port))

/*++
VOID
NdisRawReadPortUlong(
    IN  ULONG_PTR               Port,
    OUT PULONG                  Data
    )
--*/
#define NdisRawReadPortUlong(Port,Data) \
        *(Data) = READ_PORT_ULONG((PULONG)(Port))


//
// Raw Read Buffer Ports
//

/*++
VOID
NdisRawReadPortBufferUchar(
    IN  ULONG_PTR               Port,
    OUT PUCHAR                  Buffer,
    IN  ULONG                   Length
    )
--*/
#define NdisRawReadPortBufferUchar(Port,Buffer,Length)                      \
        READ_PORT_BUFFER_UCHAR((PUCHAR)(Port),(PUCHAR)(Buffer),(Length))


/*++
VOID
NdisRawReadPortBufferUshort(
    IN  ULONG_PTR               Port,
    OUT PUSHORT                 Buffer,
    IN  ULONG                   Length
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisRawReadPortBufferUshort(Port,Buffer,Length)                     \
        READ_PORT_BUFFER_USHORT((PUSHORT)(Port),(PUSHORT)(Buffer),(Length))
#else
#define NdisRawReadPortBufferUshort(Port,Buffer,Length)                     \
{                                                                           \
        ULONG_PTR _Port = (ULONG_PTR)(Port);                                \
        PUSHORT _Current = (Buffer);                                        \
        PUSHORT _End = _Current + (Length);                                 \
        for ( ; _Current < _End; ++_Current)                                \
        {                                                                   \
            *(UNALIGNED USHORT *)_Current = READ_PORT_USHORT((PUSHORT)_Port); \
        }                                                                   \
}
#endif


/*++
VOID
NdisRawReadPortBufferUlong(
    IN  ULONG_PTR               Port,
    OUT PULONG                  Buffer,
    IN  ULONG                   Length
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisRawReadPortBufferUlong(Port,Buffer,Length)                      \
        READ_PORT_BUFFER_ULONG((PULONG)(Port),(PULONG)(Buffer),(Length))
#else
#define NdisRawReadPortBufferUlong(Port,Buffer,Length)                      \
{                                                                           \
        ULONG_PTR _Port = (ULONG_PTR)(Port);                                \
        PULONG _Current = (Buffer);                                         \
        PULONG _End = _Current + (Length);                                  \
        for ( ; _Current < _End; ++_Current)                                \
        {                                                                   \
            *(UNALIGNED ULONG *)_Current = READ_PORT_ULONG((PULONG)_Port);  \
        }                                                                   \
}
#endif


//
// Write Registers
//

/*++
VOID
NdisWriteRegisterUchar(
    IN  PUCHAR                  Register,
    IN  UCHAR                   Data
    )
--*/

#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisWriteRegisterUchar(Register,Data)                               \
        WRITE_REGISTER_UCHAR((Register),(Data))
#else
#define NdisWriteRegisterUchar(Register,Data)                               \
    {                                                                       \
        WRITE_REGISTER_UCHAR((Register),(Data));                            \
        READ_REGISTER_UCHAR(Register);                                      \
    }
#endif

/*++
VOID
NdisWriteRegisterUshort(
    IN  PUCHAR                  Register,
    IN  USHORT                  Data
    )
--*/

#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisWriteRegisterUshort(Register,Data)                              \
        WRITE_REGISTER_USHORT((Register),(Data))
#else
#define NdisWriteRegisterUshort(Register,Data)                              \
    {                                                                       \
        WRITE_REGISTER_USHORT((Register),(Data));                           \
        READ_REGISTER_USHORT(Register);                                     \
    }
#endif

/*++
VOID
NdisWriteRegisterUlong(
    IN  PUCHAR                  Register,
    IN  ULONG                   Data
    )
--*/

#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisWriteRegisterUlong(Register,Data)   WRITE_REGISTER_ULONG((Register),(Data))
#else
#define NdisWriteRegisterUlong(Register,Data)                               \
    {                                                                       \
        WRITE_REGISTER_ULONG((Register),(Data));                            \
        READ_REGISTER_ULONG(Register);                                      \
    }
#endif

/*++
VOID
NdisReadRegisterUchar(
    IN  PUCHAR                  Register,
    OUT PUCHAR                  Data
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisReadRegisterUchar(Register,Data)    *(Data) = *((volatile UCHAR * const)(Register))
#else
#define NdisReadRegisterUchar(Register,Data)    *(Data) = READ_REGISTER_UCHAR((PUCHAR)(Register))
#endif

/*++
VOID
NdisReadRegisterUshort(
    IN  PUSHORT                 Register,
    OUT PUSHORT                 Data
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisReadRegisterUshort(Register,Data)   *(Data) = *((volatile USHORT * const)(Register))
#else
#define NdisReadRegisterUshort(Register,Data)   *(Data) = READ_REGISTER_USHORT((PUSHORT)(Register))
#endif

/*++
VOID
NdisReadRegisterUlong(
    IN  PULONG                  Register,
    OUT PULONG                  Data
    )
--*/
#if defined(_M_IX86) || defined(_M_AMD64)
#define NdisReadRegisterUlong(Register,Data)    *(Data) = *((volatile ULONG * const)(Register))
#else
#define NdisReadRegisterUlong(Register,Data)    *(Data) = READ_REGISTER_ULONG((PULONG)(Register))
#endif

#define NdisEqualString(_String1, _String2, _CaseInsensitive)               \
            RtlEqualUnicodeString(_String1, _String2, _CaseInsensitive)

#define NdisEqualUnicodeString(_String1, _String2, _CaseInsensitive)        \
            RtlEqualUnicodeString(_String1, _String2, _CaseInsensitive)

EXPORT
VOID __cdecl
NdisWriteErrorLogEntry(
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  NDIS_ERROR_CODE         ErrorCode,
    IN  ULONG                   NumberOfErrorValues,
    ...
    );

EXPORT
VOID
NdisInitializeString(
    OUT PNDIS_STRING    Destination,
    IN  PUCHAR          Source
    );

#define NdisFreeString(String) NdisFreeMemory((String).Buffer, (String).MaximumLength, 0)

#define NdisPrintString(String) DbgPrint("%ls",(String).Buffer)


/*++

VOID
NdisCreateLookaheadBufferFromSharedMemory(
    IN  PVOID                   pSharedMemory,
    IN  UINT                    LookaheadLength,
    OUT PVOID *                 pLookaheadBuffer
    );

--*/

#define NdisCreateLookaheadBufferFromSharedMemory(_S, _L, _B)   ((*(_B)) = (_S))

/*++

VOID
NdisDestroyLookaheadBufferFromSharedMemory(
    IN  PVOID                   pLookaheadBuffer
    );

--*/

#define NdisDestroyLookaheadBufferFromSharedMemory(_B)


//
// The following declarations are shared between ndismac.h and ndismini.h. They
// are meant to be for internal use only. They should not be used directly by
// miniport drivers.
//

//
// declare these first since they point to each other
//

typedef struct _NDIS_WRAPPER_HANDLE     NDIS_WRAPPER_HANDLE, *PNDIS_WRAPPER_HANDLE;
typedef struct _NDIS_PROTOCOL_BLOCK     NDIS_PROTOCOL_BLOCK, *PNDIS_PROTOCOL_BLOCK;
typedef struct _NDIS_OPEN_BLOCK         NDIS_OPEN_BLOCK, *PNDIS_OPEN_BLOCK;
typedef struct _NDIS_M_DRIVER_BLOCK     NDIS_M_DRIVER_BLOCK, *PNDIS_M_DRIVER_BLOCK;
typedef struct _NDIS_MINIPORT_BLOCK     NDIS_MINIPORT_BLOCK,*PNDIS_MINIPORT_BLOCK;
typedef struct _NDIS_FILTER_DRIVER_BLOCK NDIS_FILTER_DRIVER_BLOCK, *PNDIS_FILTER_DRIVER_BLOCK;
typedef struct _NDIS_FILTER_BLOCK       NDIS_FILTER_BLOCK, *PNDIS_FILTER_BLOCK;
typedef struct _CO_CALL_PARAMETERS      CO_CALL_PARAMETERS, *PCO_CALL_PARAMETERS;
typedef struct _CO_MEDIA_PARAMETERS     CO_MEDIA_PARAMETERS, *PCO_MEDIA_PARAMETERS;
typedef struct _NDIS_CALL_MANAGER_CHARACTERISTICS *PNDIS_CALL_MANAGER_CHARACTERISTICS;
typedef struct _NDIS_AF_LIST            NDIS_AF_LIST, *PNDIS_AF_LIST;
typedef struct _X_FILTER                ETH_FILTER, *PETH_FILTER;
typedef struct _X_FILTER                TR_FILTER, *PTR_FILTER;
typedef struct _X_FILTER                NULL_FILTER, *PNULL_FILTER;
typedef enum _NDIS_NDIS5_DRIVER_STATE   NDIS_NDIS5_DRIVER_STATE, *PNDIS_NDIS5_DRIVER_STATE;
typedef enum _NDIS_OPEN_TRANSLATION_STATE NDIS_OPEN_TRANSLATION_STATE, *PNDIS_OPEN_TRANSLATION_STATE;



typedef USHORT NET_FRAME_TYPE, *PNET_FRAME_TYPE;




//
// Timers.
//

typedef
VOID
(*PNDIS_TIMER_FUNCTION) (
    IN  PVOID                   SystemSpecific1,
    IN  PVOID                   FunctionContext,
    IN  PVOID                   SystemSpecific2,
    IN  PVOID                   SystemSpecific3
    );

typedef struct _NDIS_TIMER
{
    KTIMER      Timer;
    KDPC        Dpc;
} NDIS_TIMER, *PNDIS_TIMER;

EXPORT
VOID
NdisInitializeTimer(
    IN OUT PNDIS_TIMER          Timer,
    IN  PNDIS_TIMER_FUNCTION    TimerFunction,
    IN  PVOID                   FunctionContext
    );

VOID
NdisCancelTimer(
    IN  PNDIS_TIMER             Timer,
    OUT PBOOLEAN                TimerCancelled
    );

EXPORT
VOID
NdisSetTimer(
    IN  PNDIS_TIMER             Timer,
    IN  UINT                    MillisecondsToDelay
    );


EXPORT
VOID
NdisSetPeriodicTimer(
    IN  PNDIS_TIMER             NdisTimer,
    IN  UINT                    MillisecondsPeriod
    );

EXPORT
VOID
NdisSetTimerEx(
    IN  PNDIS_TIMER             Timer,
    IN  UINT                    MillisecondsToDelay,
    IN  PVOID                   FunctionContext
    );

//
// DMA operations.
//

EXPORT
VOID
NdisAllocateDmaChannel(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            NdisDmaHandle,
    IN  NDIS_HANDLE             NdisAdapterHandle,
    IN  PNDIS_DMA_DESCRIPTION   DmaDescription,
    IN  ULONG                   MaximumLength
    );

EXPORT
VOID
NdisSetupDmaTransfer(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisDmaHandle,
    IN  PNDIS_BUFFER            Buffer,
    IN  ULONG                   Offset,
    IN  ULONG                   Length,
    IN  BOOLEAN                 WriteToDevice
    );

EXPORT
VOID
NdisCompleteDmaTransfer(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisDmaHandle,
    IN  PNDIS_BUFFER            Buffer,
    IN  ULONG                   Offset,
    IN  ULONG                   Length,
    IN  BOOLEAN                 WriteToDevice
    );

//
// Wrapper initialization and termination.
//

EXPORT
VOID
NdisInitializeWrapper(
    OUT PNDIS_HANDLE            NdisWrapperHandle,
    IN  PVOID                   SystemSpecific1,
    IN  PVOID                   SystemSpecific2,
    IN  PVOID                   SystemSpecific3
    );

EXPORT
VOID
NdisTerminateWrapper(
    IN  NDIS_HANDLE             NdisWrapperHandle,
    IN  PVOID                   SystemSpecific
    );

//
// Shared memory
//

#define NdisUpdateSharedMemory(_H, _L, _V, _P)

//
// System processor count
//

EXPORT
CCHAR
NdisSystemProcessorCount(
    VOID
    );

EXPORT
ULONG
NdisGetCurrentProcessorNumber(
    VOID
    );

EXPORT
PVOID
NdisGetRoutineAddress(
    IN PNDIS_STRING     NdisRoutineName
    );


EXPORT
UINT
NdisGetVersion(
    VOID
    );

//
// Ansi/Unicode support routines
//

#if BINARY_COMPATIBLE

EXPORT
VOID
NdisInitAnsiString(
    IN OUT  PANSI_STRING        DestinationString,
    IN      PCSTR               SourceString
    );

EXPORT
VOID
NdisInitUnicodeString(
    IN OUT  PUNICODE_STRING     DestinationString,
    IN      PCWSTR              SourceString
    );

EXPORT
NDIS_STATUS
NdisAnsiStringToUnicodeString(
    IN OUT  PUNICODE_STRING     DestinationString,
    IN      PANSI_STRING        SourceString
    );

EXPORT
NDIS_STATUS
NdisUnicodeStringToAnsiString(
    IN OUT  PANSI_STRING        DestinationString,
    IN      PUNICODE_STRING     SourceString
    );

EXPORT
NDIS_STATUS
NdisUpcaseUnicodeString(
    OUT PUNICODE_STRING         DestinationString,
    IN  PUNICODE_STRING         SourceString
    );


#else // BINARY_COMPATIBLE

#define NdisInitAnsiString(_as, s)              RtlInitString(_as, s)
#define NdisInitUnicodeString(_us, s)           RtlInitUnicodeString(_us, s)
#define NdisAnsiStringToUnicodeString(_us, _as) RtlAnsiStringToUnicodeString(_us, _as, FALSE)
#define NdisUnicodeStringToAnsiString(_as, _us) RtlUnicodeStringToAnsiString(_as, _us, FALSE)
#define NdisUpcaseUnicodeString(_d, _s)         RtlUpcaseUnicodeString(_d, _s, FALSE)

#endif // BINARY_COMPATIBLE

//
// Non-paged lookaside list support routines
//

#define NdisInitializeNPagedLookasideList(_L, _AR, _FR, _Fl, _S, _T, _D) \
                ExInitializeNPagedLookasideList(_L, _AR, _FR, _Fl, _S, _T, _D)

#define NdisDeleteNPagedLookasideList(_L)           ExDeleteNPagedLookasideList(_L)
#define NdisAllocateFromNPagedLookasideList(_L)     ExAllocateFromNPagedLookasideList(_L)
#define NdisFreeToNPagedLookasideList(_L, _E)       ExFreeToNPagedLookasideList(_L, _E)


EXPORT
VOID
NdisSetPacketStatus(
    IN          PNDIS_PACKET    Packet,
    IN          NDIS_STATUS     Status,
    IN          NDIS_HANDLE     Handle,
    IN          ULONG           Code
    );

#define NDIS_MAX_EVENT_LOG_DATA_SIZE ((ERROR_LOG_MAXIMUM_SIZE - sizeof(IO_ERROR_LOG_PACKET) + sizeof(ULONG)) & ~3)

#define NDIS_MAX_PROCESSOR_COUNT   32

#define NDIS_RECEIVE_SCALE_CAPABILITIES_REVISION_1     1

//
// What kind the receive scale capabilities the miniport can support, miniport drivers return
// some of these flags as CapabilitiesFlags in a structure _NDIS_RECEIVE_SCALE_CAPABILITIES 
// when they get a query about theire receive side scale capabilities.
//
#define NDIS_RSS_CAPS_MESSAGE_SIGNALED_INTERRUPTS                    0x01000000
#define NDIS_RSS_CAPS_CLASSIFICATION_AT_ISR                          0x02000000
#define NDIS_RSS_CAPS_CLASSIFICATION_AT_DPC                          0x04000000

//
// What kind of hash field type the miniport can support
//
#define NDIS_RSS_CAPS_HASH_TYPE_TCP_IPV4                             0x00000100
#define NDIS_RSS_CAPS_HASH_TYPE_TCP_IPV6                             0x00000200
#define NDIS_RSS_CAPS_HASH_TYPE_TCP_IPV6_EX                          0x00000400


//
// the following structure defines the Receive scale capabilities of the miniport
//
typedef struct _NDIS_RECEIVE_SCALE_CAPABILITIES
{
    NDIS_OBJECT_HEADER  Header;
    ULONG   CapabilitiesFlags;
    ULONG   NumberOfInterruptMessages;
    ULONG   NumberOfReceiveQueues;

} NDIS_RECEIVE_SCALE_CAPABILITIES, *PNDIS_RECEIVE_SCALE_CAPABILITIES;


//
// What hash functions does NDIS support
//
#define NdisHashFunctionToeplitz                            0x00000001 // supported hash function 1 -- Main RSS hash function 
#define NdisHashFunctionReserved1                           0x00000002 // supported hash function 2
#define NdisHashFunctionReserved2                           0x00000004 // supported hash function 3
#define NdisHashFunctionReserved3                           0x00000008 // supported hash function 4

#define NDIS_HASH_FUNCTION_MASK                             0x000000FF
#define NDIS_HASH_TYPE_MASK                                 0x00FFFF00

#define NDIS_RSS_HASH_FUNC_FROM_HASH_INFO(_HashInfo)  \
        ((_HashInfo) & (NDIS_HASH_FUNCTION_MASK))

#define NDIS_RSS_HASH_TYPE_FROM_HASH_INFO(_HashInfo)  \
        ((_HashInfo) & (NDIS_HASH_TYPE_MASK))

#define NDIS_RSS_HASH_INFO_FROM_TYPE_AND_FUNC(_HashType, _HashFunction) \
        ((_HashType) | (_HashFunction))

//
// What kind of hash field type the protocol what the miniport to do
//
#define NDIS_HASH_IPV4                                         0x00000100
#define NDIS_HASH_TCP_IPV4                                     0x00000200
#define NDIS_HASH_IPV6                                         0x00000400
#define NDIS_HASH_IPV6_EX                                      0x00000800
#define NDIS_HASH_TCP_IPV6                                     0x00001000
#define NDIS_HASH_TCP_IPV6_EX                                  0x00002000

//
// Flags to denote the parameters that are kept unmodified.
//
#define NDIS_RSS_PARAM_FLAG_BASE_CPU_UNCHANGED              0x0001
#define NDIS_RSS_PARAM_FLAG_HASH_INFO_UNCHANGED             0x0002
#define NDIS_RSS_PARAM_FLAG_ITABLE_UNCHANGED                0x0004
#define NDIS_RSS_PARAM_FLAG_HASH_KEY_UNCHANGED              0x0008

//
// used in OID_GEN_RECEIVE_SCALE_PARAMETERS
//
#define NDIS_RECEIVE_SCALE_PARAMETERS_REVISION_1     1

typedef struct _NDIS_RECEIVE_SCALE_PARAMETERS
{
    NDIS_OBJECT_HEADER      Header;

    // Qualifies the rest of the information.
    USHORT                  Flags;

    // The base CPU number to do receive processing.
    USHORT                  BaseCpuNumber;

    // This describes the hash function and type being enabled.
    ULONG                   HashInformation;

    // The size of indirection table array.
    USHORT                  IndirectionTableSize;    
    // The offset of the indirection table from the beginning of this structure.
    ULONG                   IndirectionTableOffset;  

    // The size of the secret key.
    USHORT                  HashSecretKeySize;   
    // The offset of the secret key from the beginning of this structure.
    ULONG                   HashSecretKeyOffset; 

    // The hash map table is a CCHAR array.
} NDIS_RECEIVE_SCALE_PARAMETERS, *PNDIS_RECEIVE_SCALE_PARAMETERS;



#define NDIS_CURRENT_PROCESSOR                       KeGetCurrentProcessorNumber()

#if defined(NDIS_WRAPPER)
typedef struct _OID_LIST    OID_LIST, *POID_LIST;
#endif // NDIS_WRAPPER defined

//
// used in all NDIS drivers
//
typedef
NDIS_STATUS
(*SET_OPTIONS_HANDLER)(
    IN  NDIS_HANDLE             NdisDriverHandle,
    IN  NDIS_HANDLE             DriverContext
    );

//
// the following definition are included here so they can be part of NDIS_OPEN_BLOCK
// structure that is included by component that do not have NDIS_MINIPORT_DRIVER defined.
//
typedef struct _NET_BUFFER_LIST NET_BUFFER_LIST, *PNET_BUFFER_LIST;

typedef
VOID
(*MINIPORT_SEND_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  ULONG                   SendFlags,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*MINIPORT_RETURN_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
NDIS_STATUS
(*WAN_SEND_HANDLER)(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             LinkHandle,
    IN  PVOID                   Packet
    );

typedef
NDIS_STATUS
(*SEND_HANDLER)(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_PACKET            Packet
    );

typedef
NDIS_STATUS
(*TRANSFER_DATA_HANDLER)(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  UINT                    ByteOffset,
    IN  UINT                    BytesToTransfer,
    OUT PNDIS_PACKET            Packet,
    OUT PUINT                   BytesTransferred
    );

typedef
NDIS_STATUS
(*RESET_HANDLER)(
    IN  NDIS_HANDLE             NdisBindingHandle
    );

typedef
NDIS_STATUS
(*REQUEST_HANDLER)(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_REQUEST           NdisRequest
    );

typedef
VOID
(*SEND_PACKETS_HANDLER)(
    IN NDIS_HANDLE              MiniportAdapterContext,
    IN PPNDIS_PACKET            PacketArray,
    IN UINT                     NumberOfPackets
    );

//
// NDIS object types created by NDIS drivers
//
#define NDIS_OBJECT_TYPE_DEFAULT                            0x80    // used when object type is implicit in the API call
#define NDIS_OBJECT_TYPE_MINIPORT_INIT_PARAMETERS           0x81    // used by NDIS in NDIS_MINIPORT_INIT_PARAMETERS
#define NDIS_OBJECT_TYPE_SG_DMA_DESCRIPTION                 0x83    // used by miniport drivers in NDIS_SG_DMA_DESCRIPTION
#define NDIS_OBJECT_TYPE_MINIPORT_INTERRUPT                 0x84    // used by miniport drivers in NDIS_MINIPORT_INTERRUPT_EX
#define NDIS_OBJECT_TYPE_DEVICE_OBJECT_ATTRIBUTES           0x85    // used by miniport or filter drivers in NDIS_DEVICE_OBJECT_ATTRIBUTES
#define NDIS_OBJECT_TYPE_BIND_PARAMETERS                    0x86    // used by NDIS in NDIS_BIND_PARAMETERS
#define NDIS_OBJECT_TYPE_OPEN_PARAMETERS                    0x87    // used by protocols in NDIS_OPEN_PARAMETERS
#define NDIS_OBJECT_TYPE_RSS_CAPABILITIES                   0x88    // used by miniport in NDIS_RECEIVE_SCALE_CAPABILITIES
#define NDIS_OBJECT_TYPE_RSS_PARAMETERS                     0x89    // used by miniport and protocol in NDIS_RECEIVE_SCALE_PARAMETERS
#define NDIS_OBJECT_TYPE_MINIPORT_DRIVER_CHARACTERISTICS    0x8A
#define NDIS_OBJECT_TYPE_FILTER_DRIVER_CHARACTERISTICS      0x8B
#define NDIS_OBJECT_TYPE_FILTER_PARTIAL_CHARACTERISTICS     0x8C
#define NDIS_OBJECT_TYPE_FILTER_ATTRIBUTES                  0x8D
#define NDIS_OBJECT_TYPE_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS     0x8E
#define NDIS_OBJECT_TYPE_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS   0x8F
#define NDIS_OBJECT_TYPE_CO_PROTOCOL_CHARACTERISTICS        0x90
#define NDIS_OBJECT_TYPE_CO_MINIPORT_CHARACTERISTICS        0x91
#define NDIS_OBJECT_TYPE_CO_FILTER_CHARACTERISTICS          0x92
#define NDIS_OBJECT_TYPE_CLIENT_CHIMNEY_OFFLOAD_CHARACTERISTICS     0x93
#define NDIS_OBJECT_TYPE_PROVIDER_CHIMNEY_OFFLOAD_CHARACTERISTICS   0x94
#define NDIS_OBJECT_TYPE_PROTOCOL_DRIVER_CHARACTERISTICS    0x95
#define NDIS_OBJECT_TYPE_REQUEST_EX                         0x96
#define NDIS_OBJECT_TYPE_OID_REQUEST                        0x96
#define NDIS_OBJECT_TYPE_TIMER_CHARACTERISTICS              0x97
#define NDIS_OBJECT_TYPE_STATUS_INDICATION                  0x98
#define NDIS_OBJECT_TYPE_FILTER_ATTACH_PARAMETERS           0x99
#define NDIS_OBJECT_TYPE_FILTER_PAUSE_PARAMETERS            0x9A
#define NDIS_OBJECT_TYPE_FILTER_RESTART_PARAMETERS          0x9B
#define NDIS_OBJECT_TYPE_PORT_CHARACTERISTICS               0x9C
#define NDIS_OBJECT_TYPE_PORT_STATE                         0x9D

#define NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES       0x9E
#define NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES            0x9F
#define NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_OFFLOAD_ATTRIBUTES            0xA0
#define NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_NATIVE_802_11_ATTRIBUTES      0xA1


#define NDIS_CURRENT_PROCESSOR_NUMBER KeGetCurrentProcessorNumber()

#define NDIS_CURRENT_IRQL() KeGetCurrentIrql()

#define NDIS_RAISE_IRQL_TO_DISPATCH(_pIrql_)     KeRaiseIrql(DISPATCH_LEVEL, _pIrql_)

#define NDIS_LOWER_IRQL(_OldIrql_, _CurIrql_)                   \
{                                                               \
    if (_OldIrql_ != _CurIrql_) KeLowerIrql(_OldIrql_);         \
}

EXPORT
ULONG
NdisMGetBusData(
    IN NDIS_HANDLE              NdisMiniportHandle,
    IN ULONG                    WhichSpace,
    IN ULONG                    Offset,
    IN PVOID                    Buffer,
    IN ULONG                    Length
    );

EXPORT
ULONG
NdisMSetBusData(
    IN NDIS_HANDLE              NdisMiniportHandle,
    IN ULONG                    WhichSpace,
    IN ULONG                    Offset,
    IN PVOID                    Buffer,
    IN ULONG                    Length
    );

#if (defined(NDIS60) || (NDIS60_MINIPORT))

EXPORT
NDIS_STATUS
NdisOpenConfigurationEx(
    IN      NDIS_HANDLE     NdisHandle,
    OUT     PNDIS_HANDLE    ConfigurationHandle
    );

EXPORT
PMDL
NdisAllocateMdl(
    IN  NDIS_HANDLE             NdisHandle,
    IN  PVOID                   VirtualAddress,
    IN  UINT                    Length
    );

EXPORT
PVOID
NdisAllocateMemoryWithTagPriority(
    IN  NDIS_HANDLE             NdisHandle,
    IN  UINT                    Length,
    IN  ULONG                   Tag,
    IN  EX_POOL_PRIORITY        Priority
    );


typedef struct _NDIS_DRIVER_OPTIONAL_HANDLERS
{
    NDIS_OBJECT_HEADER  Header;
} NDIS_DRIVER_OPTIONAL_HANDLERS, *PNDIS_DRIVER_OPTIONAL_HANDLERS;

EXPORT
NDIS_STATUS
NdisSetOptionalHandlers(
    NDIS_HANDLE                     NdisDriverHandle,
    PNDIS_DRIVER_OPTIONAL_HANDLERS  OptionalHandlers
    );




#endif

//
// new request and status structures
//

#define  NDIS_OID_REQUEST_REVISION_1             1
#define  NDIS_OID_REQUEST_TIMEOUT_INFINITE       0
#define  NDIS_OID_REQUEST_NDIS_RESERVED_SIZE     12

typedef struct _NDIS_OID_REQUEST
{
    //
    // Caller must set Header to
    //     Type = NDIS_OBJECT_TYPE_OID_REQUEST
    //     Revision = NDIS_OID_REQUEST_REVISION_1
    //     Size = sizeof(_NDIS_OID_REQUEST)
    //
    NDIS_OBJECT_HEADER          Header;
    NDIS_REQUEST_TYPE           RequestType;
    UINT                        PortId;
    UINT                        Timeout; // in Seconds
    PVOID                       RequestID;

    //
    // OID - Information
    //
    union _REQUEST_DATA
    {
        struct QUERY
        {
            NDIS_OID    Oid;
            PVOID       InformationBuffer;
            UINT        InformationBufferLength;
            UINT        BytesWritten;
            UINT        BytesNeeded;
        } QUERY_INFORMATION;
    
        struct _SET
        {
            NDIS_OID    Oid;
            PVOID       InformationBuffer;
            UINT        InformationBufferLength;
            UINT        BytesRead;
            UINT        BytesNeeded;
        } SET_INFORMATION;
    
        struct _METHOD
        {
            NDIS_OID            Oid;
            PVOID               InformationBuffer;
            ULONG               InputBufferLength;
            ULONG               OutputBufferLength;
            ULONG               MethodId;
            UINT                BytesWritten;
            UINT                BytesRead;
            UINT                BytesNeeded;
        } METHOD_INFORMATION;
    } DATA;
    //
    // NDIS Reserved
    //
    UCHAR       NdisReserved[NDIS_OID_REQUEST_NDIS_RESERVED_SIZE * sizeof(PVOID)];
    UCHAR       MiniportReserved[2*sizeof(PVOID)];
    UCHAR       SourceReserved[2*sizeof(PVOID)];

}NDIS_OID_REQUEST, *PNDIS_OID_REQUEST;


typedef struct _NDIS_OID_REQUEST _NDIS_REQUEST_EX, NDIS_REQUEST_EX, *PNDIS_REQUEST_EX;
#define  NDIS_REQUEST_EX_REVISION_1                 1
#define  NDIS_REQUEST_EX_TIMEOUT_INFINITE           0
#define  NDIS_REQUEST_EX_NDIS_RESERVED_SIZE     NDIS_OID_REQUEST_NDIS_RESERVED_SIZE     

#define  NDIS_STATUS_INDICATION_FLAGS_NDIS_RESERVED    0xFFF


#define  NDIS_STATUS_INDICATION_REVISION_1             1

typedef struct _NDIS_STATUS_INDICATION 
{
    NDIS_OBJECT_HEADER      Header;
    NDIS_HANDLE             SourceHandle;
    ULONG                   PortNumber;
    NDIS_STATUS             StatusCode;
    ULONG                   Flags;             
    NDIS_HANDLE             DestinationHandle;
    PVOID                   RequestId; 
    PVOID                   StatusBuffer;
    ULONG                   StatusBufferSize;
    GUID                    Guid;               // optional and valid only if StatusCode = NDIS_STATUS_MEDIA_SPECIFIC_INDICATION
    PVOID                   NdisReserved[4];
}NDIS_STATUS_INDICATION, *PNDIS_STATUS_INDICATION;



//
// Generic Timer support
//

#define NDIS_TIMER_CHARACTERISTICS_REVISION_1 1

typedef struct _NDIS_TIMER_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                  Header;
    NDIS_HANDLE                         Handle;
    ULONG                               Tag;
    PNDIS_TIMER_FUNCTION                TimerFunction;
    PVOID                               FunctionContext;
} NDIS_TIMER_CHARACTERISTICS, *PNDIS_TIMER_CHARACTERISTICS;

EXPORT
NDIS_STATUS
NdisInitializeTimerEx(
    IN  PNDIS_TIMER_CHARACTERISTICS     TimerCharacteristics,
    OUT PNDIS_HANDLE                    TimerHandle);

EXPORT
VOID
NdisActivateTimer(
    IN  PNDIS_HANDLE                    TimerHandle,
    IN  UINT                            MilliSecondsToDelay,
    IN  PVOID                           FunctionContext);

EXPORT
VOID
NdisActivatePeriodicTimer(
    IN  PNDIS_HANDLE                    TimerHandle,
    IN  UINT                            MilliSecondsToDelay);

EXPORT
NDIS_STATUS
NdisCancelTimerEx(
    IN  NDIS_HANDLE                     TimerHandle);

EXPORT
VOID
NdisRemoveTimer(
    IN  NDIS_HANDLE                     TimerHandle);

EXPORT
NDIS_STATUS
NdisAllocateCloneRequest(
    IN NDIS_HANDLE         SourceHandle,
    IN PNDIS_REQUEST_EX    Request,
    IN UINT                PoolTag,
    OUT PNDIS_REQUEST_EX*  CloneRequest
    );

EXPORT    
VOID
NdisFreeCloneRequest(
    IN NDIS_HANDLE         SourceHandle,
    IN PNDIS_REQUEST_EX    Request
    );
        
EXPORT
PNDIS_OID_REQUEST
NdisAllocateOidRequest(
    IN NDIS_HANDLE                      NdisHandle,
    IN  ULONG                           Tag
    );

EXPORT
VOID
NdisFreeOidRequest(
    IN PNDIS_OID_REQUEST                NdisOidRequest
    );



//
// NET_BUFFER data structures, APIs and macros
//

typedef struct _NET_BUFFER NET_BUFFER, *PNET_BUFFER;
typedef struct _NET_BUFFER_LIST_CONTEXT NET_BUFFER_LIST_CONTEXT, *PNET_BUFFER_LIST_CONTEXT;
typedef struct _NET_BUFFER_LIST NET_BUFFER_LIST, *PNET_BUFFER_LIST;

typedef union _NET_BUFFER_DATA_LENGTH
{
    ULONG   DataLength;
    SIZE_T  stDataLength;
} NET_BUFFER_DATA_LENGTH, *PNET_BUFFER_DATA_LENGTH;
    
    
typedef struct _NET_BUFFER_DATA
{
    PNET_BUFFER Next;
    PMDL        MdlChain;
#ifdef __cplusplus
    NET_BUFFER_DATA_LENGTH NbDataLength;
#else
    NET_BUFFER_DATA_LENGTH;
#endif
    ULONG       DataOffset;
    PMDL        CurrentMdl;
    ULONG       CurrentMdlOffset;
} NET_BUFFER_DATA, *PNET_BUFFER_DATA;

typedef union _NET_BUFFER_HEADER
{
#ifdef __cplusplus
    NET_BUFFER_DATA NetBufferData;
#else
    NET_BUFFER_DATA;
#endif
    SLIST_HEADER    Link;

} NET_BUFFER_HEADER, *PNET_BUFFER_HEADER;

typedef struct _NET_BUFFER
{

#ifdef __cplusplus
    NET_BUFFER_HEADER NetBufferHeader;
#else
    NET_BUFFER_HEADER;
#endif

    USHORT          ChecksumBias;
    USHORT          Reserved;
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)PVOID NdisReserved[2];
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)PVOID ProtocolReserved[3];
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)PVOID MiniportReserved[2];
}NET_BUFFER, *PNET_BUFFER;

#pragma warning(push)
#pragma warning(disable:4200)   // nonstandard extension used : zero-sized array in struct/union

typedef struct _NET_BUFFER_LIST_CONTEXT
{
    PNET_BUFFER_LIST_CONTEXT    Next;
    USHORT                      Size;
    USHORT                      Offset;
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)     UCHAR      ContextData[];
} NET_BUFFER_LIST_CONTEXT, *PNET_BUFFER_LIST_CONTEXT;

#pragma warning(pop)

typedef enum _NDIS_NET_BUFFER_LIST_INFO
{
    TcpIpChecksumNetBufferListInfo,
    TcpOffloadBytesTransferred = TcpIpChecksumNetBufferListInfo,
    IpSecNetBufferListInfo,
    TcpLargeSendNetBufferListInfo,
    TcpReceiveNoPush = TcpLargeSendNetBufferListInfo,
    ClassificationHandleNetBufferListInfo,
    Ieee8021QNetBufferListInfo,
    NetBufferListCancelId,
    MediaSpecificInformation,
    NetBufferListFrameType,
    NetBufferListProtocolId = NetBufferListFrameType,
    NetBufferListHashValue,
    NetBufferListHashInfo,
    MaxNetBufferListInfo
} NDIS_NET_BUFFER_LIST_INFO, *PNDIS_NET_BUFFER_LIST_INFO;

typedef struct _NET_BUFFER_LIST_DATA
{
    PNET_BUFFER_LIST    Next;           // Next NetBufferList in the chain
    PNET_BUFFER         FirstNetBuffer; // First NetBuffer on this NetBufferList
} NET_BUFFER_LIST_DATA, *PNET_BUFFER_LIST_DATA;

typedef union _NET_BUFFER_LIST_HEADER
{
#ifdef __cplusplus
    NET_BUFFER_LIST_DATA NetBufferListData;
#else
    NET_BUFFER_LIST_DATA;
#endif
    SLIST_HEADER            Link;           // used in SLIST of free NetBuffers in the block
} NET_BUFFER_LIST_HEADER, *PNET_BUFFER_LIST_HEADER;


typedef struct _NET_BUFFER_LIST
{

#ifdef __cplusplus
    NET_BUFFER_LIST_HEADER      NetBufferListHeader;
#else
    NET_BUFFER_LIST_HEADER;
#endif

    PNET_BUFFER_LIST_CONTEXT    Context;
    PNET_BUFFER_LIST            ParentNetBufferList;
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)PVOID NdisReserved[2];
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)PVOID ProtocolReserved[4];
    DECLSPEC_ALIGN(MEMORY_ALLOCATION_ALIGNMENT)PVOID MiniportReserved[2];
    PVOID                       Scratch;
    NDIS_HANDLE                 SourceHandle;
    ULONG                       PortNumber;
    LONG                        ChildRefCount;
    ULONG                       Flags;
    NDIS_STATUS                 Status;
    PVOID                       NetBufferListInfo[MaxNetBufferListInfo];
} NET_BUFFER_LIST, *PNET_BUFFER_LIST;



#ifdef __cplusplus
#define NET_BUFFER_NEXT_NB(_NB)                     ((_NB)->NetBufferHeader.NetBufferData.Next)
#define NET_BUFFER_FIRST_MDL(_NB)                   ((_NB)->NetBufferHeader.NetBufferData.MdlChain)
#define NET_BUFFER_DATA_LENGTH(_NB)                 ((_NB)->NetBufferHeader.NetBufferData.NbDataLength.DataLength)
#define NET_BUFFER_DATA_OFFSET(_NB)                 ((_NB)->NetBufferHeader.NetBufferData.DataOffset)
#define NET_BUFFER_CURRENT_MDL(_NB)                 ((_NB)->NetBufferHeader.NetBufferData.CurrentMdl)
#define NET_BUFFER_CURRENT_MDL_OFFSET(_NB)          ((_NB)->NetBufferHeader.NetBufferData.CurrentMdlOffset)
#else
#define NET_BUFFER_NEXT_NB(_NB)                     ((_NB)->Next)
#define NET_BUFFER_FIRST_MDL(_NB)                   ((_NB)->MdlChain)
#define NET_BUFFER_DATA_LENGTH(_NB)                 ((_NB)->DataLength)
#define NET_BUFFER_DATA_OFFSET(_NB)                 ((_NB)->DataOffset)
#define NET_BUFFER_CURRENT_MDL(_NB)                 ((_NB)->CurrentMdl)
#define NET_BUFFER_CURRENT_MDL_OFFSET(_NB)          ((_NB)->CurrentMdlOffset)
#endif

#define NET_BUFFER_PROTOCOL_RESERVED(_NB)           ((_NB)->ProtocolReserved)
#define NET_BUFFER_MINIPORT_RESERVED(_NB)           ((_NB)->MiniportReserved)
#define NET_BUFFER_CHECKSUM_BIAS(_NB)               ((_NB)->ChecksumBias)

#ifdef __cplusplus
#define NET_BUFFER_LIST_NEXT_NBL(_NBL)              ((_NBL)->NetBufferListHeader.NetBufferListData.Next)
#define NET_BUFFER_LIST_FIRST_NB(_NBL)              ((_NBL)->NetBufferListHeader.NetBufferListData.FirstNetBuffer)
#else
#define NET_BUFFER_LIST_NEXT_NBL(_NBL)              ((_NBL)->Next)
#define NET_BUFFER_LIST_FIRST_NB(_NBL)              ((_NBL)->FirstNetBuffer)
#endif

#define NET_BUFFER_LIST_FLAGS(_NBL)                 ((_NBL)->Flags)
#define NET_BUFFER_LIST_PROTOCOL_RESERVED(_NBL)     ((_NBL)->ProtocolReserved)
#define NET_BUFFER_LIST_MINIPORT_RESERVED(_NBL)     ((_NBL)->MiniportReserved)
#define NET_BUFFER_LIST_CONTEXT_DATA_START(_NBL)    ((PUCHAR)(((_NBL)->Context)+1)+(_NBL)->Context->Offset)
#define NET_BUFFER_LIST_CONTEXT_DATA_SIZE(_NBL)     (((_NBL)->Context)->Size)

#define NET_BUFFER_LIST_INFO(_NBL, _Id)             ((_NBL)->NetBufferListInfo[(_Id)])
#define NET_BUFFER_LIST_STATUS(_NBL)                ((_NBL)->Status)
#define NET_BUFFER_LIST_COMPLETION_STATUS(_NBL)     ((_NBL)->Status)
#define NET_BUFFER_LIST_PORT_NUMBER(_NBL)           ((_NB)->PortNumber)


#define NDIS_GET_NET_BUFFER_LIST_CANCEL_ID(_NBL)     (NET_BUFFER_LIST_INFO(_NBL, NetBufferListCancelId))
#define NDIS_SET_NET_BUFFER_LIST_CANCEL_ID(_NBL, _CancelId)            \
    NET_BUFFER_LIST_INFO(_NBL, NetBufferListCancelId) = _CancelId

//
// The following macros are used by miniport driver and protocol driver to set and get
// the hash value, hash type and hash function.
//
#define NET_BUFFER_LIST_SET_HASH_TYPE(_NBL, _HashType)           \
    (NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashInfo)  = \
    UlongToPtr(((PtrToUlong (NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashInfo)) & (~NDIS_HASH_TYPE_MASK)) | ((_HashType) & (NDIS_HASH_TYPE_MASK)))))

#define NET_BUFFER_LIST_SET_HASH_FUNCTION(_NBL, _HashFunction)   \
    (NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashInfo)  = \
    UlongToPtr(((PtrToUlong(NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashInfo)) & (~NDIS_HASH_FUNCTION_MASK)) | ((_HashFunction) & (NDIS_HASH_FUNCTION_MASK)))))

#define NET_BUFFER_LIST_SET_HASH_VALUE(_NBL, _HashValue)         \
    (NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashValue) = UlongToPtr(_HashValue))

#define NET_BUFFER_LIST_GET_HASH_TYPE(_NBL)                      \
    (PtrToUlong(NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashInfo)) & (NDIS_HASH_TYPE_MASK))

#define NET_BUFFER_LIST_GET_HASH_FUNCTION(_NBL)                  \
    (PtrToUlong(NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashInfo)) & (NDIS_HASH_FUNCTION_MASK))

#define NET_BUFFER_LIST_GET_HASH_VALUE(_NBL)                     \
    (PtrToUlong(NET_BUFFER_LIST_INFO(_NBL, NetBufferListHashValue)))

#define NdisSetNetBufferListProtocolId(_NBL,_ProtocolId)   \
    *((PUCHAR)(&NET_BUFFER_LIST_INFO(_NBL, NetBufferListProtocolId))) = _ProtocolId

UCHAR
NdisGetNetBufferListProtocolId(
    IN PNET_BUFFER_LIST NetBufferList
    );

VOID
NdisAdjustNetBufferCurrentMdl(
    IN  PNET_BUFFER NetBuffer
    );


//
// The flags that can be set at NET_BUFFER_LIST.Flags are defined below. 
//
#define NBL_FLAGS_PROTOCOL_RESERVED                 0xFF000000
#define NBL_FLAGS_MINIPORT_RESERVED                 0x00F00000
#define NBL_FLAGS_SCRATCH                           0x000F0000
#define NBL_FLAGS_NDIS_RESERVED                     0x00000FFF

#define NBL_FLAGS_SEND_READ_ONLY                    0x00001000
#define NBL_FLAGS_RECV_READ_ONLY                    0x00002000


#define NBL_TEST_FLAG(_NBL, _F)                     (((_NBL)->Flags & (_F)) != 0)
#define NBL_SET_FLAG(_NBL, _F)                      ((_NBL)->Flags |= (_F))
#define NBL_CLEAR_FLAG(_NBL, _F)                    ((_NBL)->Flags &= ~(_F))

#define NBL_SET_PROTOCOL_RSVD_FLAG(_NBL, _F)        ((_NBL)->Flags |= ((_F) & NBL_FLAGS_PROTOCOL_RESERVED))
#define NBL_CLEAR_PROTOCOL_RSVD_FLAG(_NBL, _F)      ((_NBL)->Flags &= ~((_F) & NBL_FLAGS_PROTOCOL_RESERVED))
#define NBL_TEST_PROTOCOL_RSVD_FLAG(_NBL, _F)       (((_NBL)->Flags & ((_F) & NBL_FLAGS_PROTOCOL_RESERVED)) != 0)


//
// Define some flags for protocols' own use
//
#define NBL_PROT_RSVD_FLAGS                     NBL_FLAGS_PROTOCOL_RESERVED
#define NBL_SET_PROT_RSVD_FLAG(_NBL, _F)        NBL_SET_PROTOCOL_RSVD_FLAG(_NBL,_F)
#define NBL_CLEAR_PROT_RSVD_FLAG(_NBL, _F)      NBL_CLEAR_PROTOCOL_RSVD_FLAG(_NBL, _F)
#define NBL_TEST_PROT_RSVD_FLAG(_NBL, _F)       NBL_TEST_PROTOCOL_RSVD_FLAG(_NBL, _F)


#define NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1 1

typedef struct _NET_BUFFER_LIST_POOL_PARAMETERS
{
    //
    // Set ObjectHeader.Type to NDIS_OBJECT_TYPE_DEFAULT   
    //
    NDIS_OBJECT_HEADER      Header;
    UCHAR                   ProtocolId;
    BOOLEAN                 fAllocateNetBuffer;
    USHORT                  ContextSize;
    ULONG                   PoolTag;
    ULONG                   DataSize;
}NET_BUFFER_LIST_POOL_PARAMETERS, *PNET_BUFFER_LIST_POOL_PARAMETERS;

#define NET_BUFFER_POOL_PARAMETERS_REVISION_1 1

typedef struct _NET_BUFFER_POOL_PARAMETERS 
{
    //
    // Set ObjectHeader.Type to NDIS_OBJECT_TYPE_DEFAULT
    //
    NDIS_OBJECT_HEADER      Header;
    ULONG                   PoolTag;
    ULONG                   DataSize;
}NET_BUFFER_POOL_PARAMETERS,*PNET_BUFFER_POOL_PARAMETERS; 

//
// Prototypes of the MDL allocation and free callback.
//

typedef
PMDL
(*ALLOCATE_MDL_HANDLER)(
    IN OUT PULONG               BufferSize
    );

typedef
VOID
(*FREE_MDL_HANDLER)(
    IN  PMDL                    Mdl
    );

EXPORT
NDIS_HANDLE
NdisAllocateNetBufferPool(
    IN NDIS_HANDLE                  NdisHandle,
    IN PNET_BUFFER_POOL_PARAMETERS  Parameters
    );

EXPORT
VOID
NdisFreeNetBufferPool(
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
PNET_BUFFER
NdisAllocateNetBuffer(
    IN  NDIS_HANDLE             PoolHandle,
    IN  PMDL                    MdlChain,
    IN  ULONG                   DataOffset,
    IN  SIZE_T                  DataLength,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisFreeNetBuffer(
    IN  PNET_BUFFER             NetBuffer,
    IN  BOOLEAN                 DispatchLevel
    );


EXPORT
PNET_BUFFER
NdisAllocateNetBufferMdlAndData(
    IN NDIS_HANDLE              PoolHandle,
    IN BOOLEAN                  DispatchLevel
    );
    
    
EXPORT
NDIS_HANDLE
NdisAllocateNetBufferListPool(
    IN  NDIS_HANDLE                         NdisHandle,
    IN  PNET_BUFFER_LIST_POOL_PARAMETERS    Parameters                    
    );

EXPORT
VOID
NdisFreeNetBufferListPool(
    IN  NDIS_HANDLE             PoolHandle
    );

EXPORT
PNET_BUFFER_LIST
NdisAllocateNetBufferList(
    IN  NDIS_HANDLE             PoolHandle,
    IN  USHORT                  ContextSize,
    IN  USHORT                  ContextBackFill,
    IN  BOOLEAN                 DispatchLevel
    );


EXPORT
VOID
NdisFreeNetBufferList(
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
NDIS_STATUS
NdisRetreatNetBufferDataStart(
    IN  PNET_BUFFER             NetBuffer,
    IN  ULONG                   DataOffsetDelta,
    IN  ULONG                   DataBackFill OPTIONAL,
    IN  ALLOCATE_MDL_HANDLER    AllocateMdl OPTIONAL
    );

EXPORT
VOID
NdisAdvanceNetBufferDataStart(
    IN  PNET_BUFFER             NetBuffer,
    IN  ULONG                   DataOffsetDelta,
    IN  FREE_MDL_HANDLER        FreeMdl OPTIONAL
    );

EXPORT
NDIS_STATUS
NdisRetreatNetBufferListDataStart(
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  ULONG                   DataOffsetDelta,
    IN  ULONG                   DataBackFill,
    IN  ALLOCATE_MDL_HANDLER    AllocateMdl OPTIONAL,
    IN  FREE_MDL_HANDLER        FreeMdl OPTIONAL
    );

EXPORT
VOID
NdisAdvanceNetBufferListDataStart(
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  ULONG                   DataOffsetDelta,
    IN  FREE_MDL_HANDLER        FreeMdl OPTIONAL
    );

EXPORT
NDIS_STATUS
NdisAllocateNetBufferListContext(
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  USHORT                  ContextSize,
    IN  USHORT                  ContextBackFill,
    IN  ULONG                   PoolTag
    );

EXPORT
VOID
NdisFreeNetBufferListContext(
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  USHORT                  ContextSize
    );

EXPORT
PNET_BUFFER_LIST
NdisAllocateCloneNetBufferList(
    IN PNET_BUFFER_LIST         OriginalNetBufferList,
    IN PNDIS_HANDLE             NetBufferListPoolHandle OPTIONAL, 
    IN PNDIS_HANDLE             NetBufferPoolHandle OPTIONAL, 
    IN BOOLEAN                  DispatchLevel
    );

EXPORT
VOID
NdisFreeCloneNetBufferList(
    IN PNET_BUFFER_LIST         CloneNetBufferList,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
PNET_BUFFER_LIST
NdisAllocateFragmentNetBufferList(
    IN  PNET_BUFFER_LIST        OriginalNetBufferList,
    IN  NDIS_HANDLE             NetBufferListPool OPTIONAL,
    IN  NDIS_HANDLE             NetBufferPool OPTIONAL,
    IN  ULONG                   StartOffset,
    IN  ULONG                   MaximumLength,
    IN  ULONG                   DataOffsetDelta,
    IN  ULONG                   DataBackFill,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisFreeFragmentNetBufferList(
    IN  PNET_BUFFER_LIST        FragmentNetBufferList,
    IN  ULONG                   DataOffsetDelta,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
PNET_BUFFER_LIST
NdisAllocateReassembledNetBufferList(
    IN  PNET_BUFFER_LIST        FagmentNetBufferList,
    IN  NDIS_HANDLE             NetBufferAndNetBufferListPoolHandle OPTIONAL,
    IN  ULONG                   StartOffset,
    IN  ULONG                   DataOffsetDelta,
    IN  ULONG                   DataBackFill,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisFreeReassembledNetBufferList(
    IN  PNET_BUFFER_LIST        ReassembledNetBufferList,
    IN  ULONG                   DataOffsetDelta,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
PNET_BUFFER_LIST
NdisAllocateNetBufferAndNetBufferList(
    IN  NDIS_HANDLE             PoolHandle,
    IN  USHORT                  ContextSize,
    IN  USHORT                  ContextBackFill,
    IN  PMDL                    MdlChain,
    IN  ULONG                   DataOffset,
    IN  SIZE_T                  DataLength,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
PVOID
NdisGetDataBuffer(
    IN PNET_BUFFER  NetBuffer,
    IN ULONG        BytesNeeded,
    IN PVOID        Storage,
    IN UINT         AlignMultiple,
    IN UINT         AlignOffset
    );


EXPORT
NDIS_HANDLE
NdisGetPoolFromNetBufferList(
    IN PNET_BUFFER_LIST     NetBufferList
    );

EXPORT
NDIS_HANDLE
NdisGetPoolFromNetBuffer(
    IN PNET_BUFFER          NetBuffer
    );

EXPORT
VOID
NdisCopyFromNetBufferToNetBuffer(
    IN PNET_BUFFER         Destination,
    IN UINT                DestinationOffset,
    IN UINT                BytesToCopy,
    IN PNET_BUFFER         Source,
    IN UINT                SourceOffset,
    OUT PUINT              BytesCopied
    );

EXPORT
VOID
NdisCopySendNetBufferListInfo(
    IN PNET_BUFFER_LIST DestNetBufferList,
    IN PNET_BUFFER_LIST SrcNetBufferList
    );

EXPORT
VOID
NdisCopyReceiveNetBufferListInfo(
    IN PNET_BUFFER_LIST DestNetBufferList,
    IN PNET_BUFFER_LIST SrcNetBufferList
    );
    
EXPORT
ULONG
NdisQueryNetBufferPhysicalCount(
    IN  PNET_BUFFER             NetBuffer
    );

EXPORT
PMDL
NdisAllocateMdl(
    IN  NDIS_HANDLE             NdisHandle,
    IN  PVOID                   VirtualAddress,
    IN  UINT                    Length
    );

EXPORT
VOID
NdisFreeMdl(
    IN PMDL                     Mdl
    );
    


#define NDIS_TASK_OFFLOAD_VERSION 1

#define MAX_HASHES          4
#define TRUNCATED_HASH_LEN  12

#define CRYPTO_SUCCESS                      0
#define CRYPTO_GENERIC_ERROR                1
#define CRYPTO_TRANSPORT_AH_AUTH_FAILED     2
#define CRYPTO_TRANSPORT_ESP_AUTH_FAILED    3
#define CRYPTO_TUNNEL_AH_AUTH_FAILED        4
#define CRYPTO_TUNNEL_ESP_AUTH_FAILED       5
#define CRYPTO_INVALID_PACKET_SYNTAX        6
#define CRYPTO_INVALID_PROTOCOL             7

typedef struct _NDIS_IPSEC_PACKET_INFO
{
    union
    {
        struct
        {
            NDIS_HANDLE OffloadHandle;
            NDIS_HANDLE NextOffloadHandle;

        } Transmit;

        struct
        {
            ULONG   SA_DELETE_REQ:1;
            ULONG   CRYPTO_DONE:1;
            ULONG   NEXT_CRYPTO_DONE:1;
            ULONG   CryptoStatus;
        } Receive;
    };
} NDIS_IPSEC_PACKET_INFO, *PNDIS_IPSEC_PACKET_INFO;

//
//  The following defines are used in the Task field above to define
//  the type of task offloading necessary.
//
typedef enum _NDIS_TASK
{
    TcpIpChecksumNdisTask,
    IpSecNdisTask,
    TcpLargeSendNdisTask,
    TcpConnectionOffloadNdisTask,
    IpsecChimneyOffloadNdisTask,
    SslChimneyOffloadNdisTask,
    RdmaChimneyOffloadNdisTask,
    MaxNdisTask
} NDIS_TASK, *PNDIS_TASK;


typedef enum _NDIS_ENCAPSULATION
{
    UNSPECIFIED_Encapsulation,
    NULL_Encapsulation,
    IEEE_802_3_Encapsulation,
    IEEE_802_5_Encapsulation,
    LLC_SNAP_ROUTED_Encapsulation,
    LLC_SNAP_BRIDGED_Encapsulation

} NDIS_ENCAPSULATION;

//
// Encapsulation header format
//
typedef struct _NDIS_ENCAPSULATION_FORMAT
{
    NDIS_ENCAPSULATION  Encapsulation;              // Encapsulation type
    struct
    {
        ULONG   FixedHeaderSize:1;
        ULONG   Reserved:31;
    } Flags;

    ULONG    EncapsulationHeaderSize;               // Encapsulation header size

} NDIS_ENCAPSULATION_FORMAT,*PNDIS_ENCAPSULATION_FORMAT;


//
// OFFLOAD header structure for OID_TCP_TASK_OFFLOAD
//
typedef struct _NDIS_TASK_OFFLOAD_HEADER
{
    ULONG       Version;                            // set to NDIS_TASK_OFFLOAD_VERSION
    ULONG       Size;                               // Size of this structure
    ULONG       Reserved;                           // Reserved for future use
    ULONG       OffsetFirstTask;                    // Offset to the first
    NDIS_ENCAPSULATION_FORMAT  EncapsulationFormat; // Encapsulation information.
                                                    // NDIS_TASK_OFFLOAD structure(s)

} NDIS_TASK_OFFLOAD_HEADER, *PNDIS_TASK_OFFLOAD_HEADER;


//
//  Task offload Structure, which follows the above header in ndis query
//
typedef struct _NDIS_TASK_OFFLOAD
{
    ULONG       Version;                            // NDIS_TASK_OFFLOAD_VERSION
    ULONG       Size;                               //  Size of this structure. Used for version checking.
    NDIS_TASK   Task;                               //  Task.
    ULONG       OffsetNextTask;                     //  Offset to the next NDIS_TASK_OFFLOAD
    ULONG       TaskBufferLength;                   //  Length of the task offload information.
    UCHAR       TaskBuffer[1];                      //  The task offload information.
} NDIS_TASK_OFFLOAD, *PNDIS_TASK_OFFLOAD;

//
//  Offload structure for NDIS_TASK_TCP_IP_CHECKSUM
//
typedef struct _NDIS_TASK_TCP_IP_CHECKSUM
{
    struct
    {
        ULONG       IpOptionsSupported:1;
        ULONG       TcpOptionsSupported:1;
        ULONG       TcpChecksum:1;
        ULONG       UdpChecksum:1;
        ULONG       IpChecksum:1;
    } V4Transmit;

    struct
    {
        ULONG       IpOptionsSupported:1;
        ULONG       TcpOptionsSupported:1;
        ULONG       TcpChecksum:1;
        ULONG       UdpChecksum:1;
        ULONG       IpChecksum:1;
    } V4Receive;


    struct
    {
        ULONG       IpOptionsSupported:1;
        ULONG       TcpOptionsSupported:1;
        ULONG       TcpChecksum:1;
        ULONG       UdpChecksum:1;

    } V6Transmit;

    struct
    {
        ULONG       IpOptionsSupported:1;
        ULONG       TcpOptionsSupported:1;
        ULONG       TcpChecksum:1;
        ULONG       UdpChecksum:1;

    } V6Receive;


} NDIS_TASK_TCP_IP_CHECKSUM, *PNDIS_TASK_TCP_IP_CHECKSUM;

//
//  Off-load structure for NDIS_TASK_TCP_LARGE_SEND
//
typedef struct _NDIS_TASK_TCP_LARGE_SEND
{
    ULONG     Version;
    ULONG     MaxOffLoadSize;
    ULONG     MinSegmentCount;
    BOOLEAN   TcpOptions;
    BOOLEAN   IpOptions;

} NDIS_TASK_TCP_LARGE_SEND, *PNDIS_TASK_TCP_LARGE_SEND;


typedef struct _NDIS_TASK_IPSEC
{
    struct
    {
        ULONG   AH_ESP_COMBINED;
        ULONG   TRANSPORT_TUNNEL_COMBINED;
        ULONG   V4_OPTIONS;
        ULONG   RESERVED;
    } Supported;

    struct
    {
        ULONG   MD5:1;
        ULONG   SHA_1:1;
        ULONG   Transport:1;
        ULONG   Tunnel:1;
        ULONG   Send:1;
        ULONG   Receive:1;
    } V4AH;

    struct
    {
        ULONG   DES:1;
        ULONG   RESERVED:1;
        ULONG   TRIPLE_DES:1;
        ULONG   NULL_ESP:1;
        ULONG   Transport:1;
        ULONG   Tunnel:1;
        ULONG   Send:1;
        ULONG   Receive:1;
    } V4ESP;

} NDIS_TASK_IPSEC, *PNDIS_TASK_IPSEC;

#define IPSEC_TPT_UDPESP_ENCAPTYPE_IKE                 0x00000001
#define IPSEC_TUN_UDPESP_ENCAPTYPE_IKE                 0x00000002
#define IPSEC_TPTOVERTUN_UDPESP_ENCAPTYPE_IKE          0x00000004
#define IPSEC_TPT_UDPESP_OVER_PURE_TUN_ENCAPTYPE_IKE   0x00000008
#define IPSEC_TPT_UDPESP_ENCAPTYPE_OTHER               0x00000010
#define IPSEC_TUN_UDPESP_ENCAPTYPE_OTHER               0x00000020
#define IPSEC_TPTOVERTUN_UDPESP_ENCAPTYPE_OTHER        0x00000040
#define IPSEC_TPT_UDPESP_OVER_PURE_TUN_ENCAPTYPE_OTHER 0x00000080

#if NDIS_CHIMNEY_OFFLOAD

#ifndef _CHIMNEY_OFFLOAD_
#define _CHIMNEY_OFFLOAD_

//
// NDIS_CHIMNEY_OFFLOAD_TYPE
//
// Specifies the chimney type.
//
typedef enum {
    NdisTcpChimneyOffload = 1,
    NdisIpsecChimneyOffload,
    NdisRdmaChimneyOffload,
    NdisMaxChimneyOffload
} NDIS_CHIMNEY_OFFLOAD_TYPE, *PNDIS_CHIMNEY_OFFLOAD_TYPE;

//
// INDICATE_OFFLOAD_EVENT
//
// Qualifies a Offload Event indication.
//
typedef enum {
    NeighborReachabilityInDoubt = 0x0001,
    NeighborReachabilityQuery,
    MaxOffloadEvent
} INDICATE_OFFLOAD_EVENT, *PINDICATE_OFFLOAD_EVENT;

//
// Describes the TCP Offload capabilities of the NIC. Support for TCP Options 
// is a must.
//
typedef struct _NDIS_TASK_TCP_CONNECTION_OFFLOAD
{
    IN OUT ULONG SupportIp4:1;
    IN OUT ULONG SupportIp6:1;
    IN OUT ULONG SupportIp6ExtensionHeaders:1;
    IN OUT ULONG SupportSack:1;
    OUT ULONG TcpConnectionOffloadCapacity;
    IN ULONG TicksPerSecond;
    IN UCHAR TcpAckFrequency;
    IN UCHAR TcpDelayedAckTicks;
    IN UCHAR TcpMaximumRetransmissions;
    IN UCHAR TcpDoubtReachabilityRetransmissions;
    IN ULONG TcpSwsPreventionTicks;
    IN ULONG TcpDuplicateAckThreshold;
    IN ULONG TcpPushTicks;
    IN ULONG NceStaleTicks;
    IN USHORT InitialIp4Id;
} NDIS_TASK_TCP_CONNECTION_OFFLOAD, *PNDIS_TASK_TCP_CONNECTION_OFFLOAD;

//
// OFFLOAD_STATE_TYPE
//
// State type at each layer in the stack.
//
typedef enum {
    NeighborOffloadConstState = 0x1,
    NeighborOffloadCachedState,
    NeighborOffloadDelegatedState,
    NeighborOffloadState,
    Ip4OffloadConstState,
    Ip4OffloadCachedState,
    Ip4OffloadDelegatedState,
    Ip4OffloadState,
    Ip6OffloadConstState,
    Ip6OffloadCachedState,
    Ip6OffloadDelegatedState,
    Ip6OffloadState,
    TcpOffloadConstState,
    TcpOffloadCachedState,
    TcpOffloadDelegatedState,
    TcpOffloadResourceState,
    TcpOffloadState,
    FilterReservedOffloadState = 0xFE,
    MaximumOffloadState
} OFFLOAD_STATE_TYPE, *POFFLOAD_STATE_TYPE;

//
// OFFLOAD_STATE_HEADER
//
// Offload state header, precedes each offload state.
//
typedef struct _OFFLOAD_STATE_HEADER {
    ULONG Length;
    ULONG RecognizedOptions;
} OFFLOAD_STATE_HEADER, *POFFLOAD_STATE_HEADER;

//
//
// TCP_OFFLOAD_CONNECTION_STATE
//
// TCP connection state [RFC 793].
//
typedef enum {
    TcpConnectionClosed,
    TcpConnectionListen,
    TcpConnectionSynSent,
    TcpConnectionSynRcvd,
    TcpConnectionEstablished,
    TcpConnectionFinWait1,
    TcpConnectionFinWait2,
    TcpConnectionCloseWait,
    TcpConnectionClosing,
    TcpConnectionLastAck,
    TcpConnectionTimeWait,
    TcpConnectionMaxState
} TCP_OFFLOAD_CONNECTION_STATE, *PTCP_OFFLOAD_CONNECTION_STATE;

//
// TCP_UPLOAD_REASON
//
// Reason for upoloading an offloaded TCP connection back to the host.
//
typedef enum {
    LowActivity = 1,
    HighDropRate,
    SmallIO,
    NoBufferProposting,
    ReceivedUrgentData,
    HighFragmentation,
    HighOutOfOrderPackets,
    TimeoutExpiration,
    InvalidState,
    UploadRequested,
    HardwareFailure,
    MaxUploadReason
} TCP_UPLOAD_REASON, *PTCP_UPLOAD_REASON;

//
// Qualifies a disconnect event or a disconnect request on a TCP connection.
//
#define TCP_DISCONNECT_GRACEFUL_CLOSE   0x01
#define TCP_DISCONNECT_ABORTIVE_CLOSE   0x02

//
// TCP_OFFLOAD_EVENT_TYPE
//
// Event indications possible on an offloaded TCP connection.
//
typedef enum {
    TcpIndicateSendBacklogChange = 1,
    TcpIndicateDisconnect,
    TcpIndicateRetrieve,
    TcpIndicateAbort
} TCP_OFFLOAD_EVENT_TYPE, *PTCP_OFFLOAD_EVENT_TYPE;


//
// Flags part of the TCP constant state.
//
#define TCP_FLAG_TIMESTAMP_ENABLED      0x01
#define TCP_FLAG_SACK_ENABLED           0x02
#define TCP_FLAG_WINDOW_SCALING_ENABLED 0x04

//
// TCP_OFFLOAD_STATE_CONST
//
// Constant fields of a Connection.
//
typedef struct _TCP_OFFLOAD_STATE_CONST {
    OFFLOAD_STATE_HEADER Header;
    USHORT Flags;
    USHORT RemotePort;
    USHORT LocalPort;
    UCHAR SndWindScale: 4;
    UCHAR RcvWindScale: 4;
    USHORT RemoteMss;
    ULONG HashValue;
} TCP_OFFLOAD_STATE_CONST, *PTCP_OFFLOAD_STATE_CONST;

//
// Flags part of the TCP cached state.
//
#define TCP_FLAG_KEEP_ALIVE_ENABLED     0x01
#define TCP_FLAG_NAGLING_ENABLED        0x02
#define TCP_FLAG_KEEP_ALIVE_RESTART     0x04
#define TCP_FLAG_MAX_RT_RESTART         0x08
#define TCP_FLAG_UPDATE_RCV_WND         0x10

//
// TCP_OFFLOAD_STATE_CACHED
//
// Cached fields of a TCB.
//
typedef struct _TCP_OFFLOAD_STATE_CACHED {
    OFFLOAD_STATE_HEADER Header;
    USHORT Flags;
    ULONG InitialRcvWnd;
    ULONG RcvIndicationSize;
    UCHAR KaProbeCount;
    ULONG KaTimeout;
    ULONG KaInterval;
    ULONG MaxRT;
    ULONG FlowLabel:20;
    UCHAR TtlOrHopLimit;
    UCHAR TosOrTrafficClass;
    UCHAR UserPriority:3;
} TCP_OFFLOAD_STATE_CACHED, *PTCP_OFFLOAD_STATE_CACHED;

//
// TCP_OFFLOAD_STATE_DELEGATED
//
// Delegated fields of a TCB.
//
typedef struct _TCP_OFFLOAD_STATE_DELEGATED {
    OFFLOAD_STATE_HEADER Header;
    TCP_OFFLOAD_CONNECTION_STATE State;
    USHORT Flags;
    ULONG RcvNxt;
    ULONG RcvWnd;
    ULONG SndUna;
    ULONG SndNxt;
    ULONG SndMax;
    ULONG SndWnd;
    ULONG MaxSndWnd;
    ULONG SendWL1;
    ULONG CWnd;
    ULONG SsThresh;
    USHORT SRtt;
    USHORT RttVar;
    ULONG TsRecent;
    ULONG TsRecentAge;
    ULONG TsTime;
    ULONG TotalRT;
    UCHAR DupAckCount;
    UCHAR SndWndProbeCount;

    struct {
        UCHAR ProbeCount;
        ULONG TimeoutDelta;
    } KeepAlive;

    struct {
        UCHAR Count;
        ULONG TimeoutDelta;
    } Retransmit;

    union {
        struct {
            PNET_BUFFER_LIST SendDataHead;
            PNET_BUFFER_LIST SendDataTail;
        };

        ULONG SendBacklogSize;
    };

    union {
        PNET_BUFFER_LIST BufferedData;
        ULONG ReceiveBacklogSize;
    };
} TCP_OFFLOAD_STATE_DELEGATED, *PTCP_OFFLOAD_STATE_DELEGATED;

//
// TCP_OFFLOAD_STATE
// 
typedef struct _TCP_OFFLOAD_STATE {
    TCP_OFFLOAD_STATE_CONST TcpConstState;
    TCP_OFFLOAD_STATE_CACHED TcpCachedState;
    TCP_OFFLOAD_STATE_DELEGATED TcpDelegatedState;
} TCP_OFFLOAD_STATE, *PTCP_OFFLOAD_STATE;

//
// TCP_OFFLOAD_RESOURCE_STATE
// 
typedef struct _TCP_OFFLOAD_RESOURCE_STATE {
    TCP_OFFLOAD_STATE_CONST TcpConstState;
    TCP_OFFLOAD_STATE_CACHED TcpCachedState;
} TCP_OFFLOAD_RESOURCE_STATE, *PTCP_OFFLOAD_RESOURCE_STATE;

//
// PATH_OFFLOAD_STATE_CONST
//
// IP path constant parameters.
//
typedef struct _PATH_OFFLOAD_STATE_CONST {
    OFFLOAD_STATE_HEADER Header;
    CONST UCHAR *SourceAddress;
    CONST UCHAR *DestinationAddress;
} PATH_OFFLOAD_STATE_CONST, *PPATH_OFFLOAD_STATE_CONST;

//
// PATH_OFFLOAD_STATE_CACHED
//
// IP path cached parameters.
//
typedef struct _PATH_OFFLOAD_STATE_CACHED {
    OFFLOAD_STATE_HEADER Header;
    ULONG PathMtu;
} PATH_OFFLOAD_STATE_CACHED, *PPATH_OFFLOAD_STATE_CACHED;

//
// PATH_OFFLOAD_STATE_DELEGATED
//
// IP path delegated parameters.
//
typedef struct _PATH_OFFLOAD_STATE_DELEGATED {
    OFFLOAD_STATE_HEADER Header;
} PATH_OFFLOAD_STATE_DELEGATED, *PPATH_OFFLOAD_STATE_DELEGATED;

//
// PATH_OFFLOAD_STATE
//
// All IP path parameters.
//
typedef struct _PATH_OFFLOAD_STATE {
    PATH_OFFLOAD_STATE_CONST ConstState;
    PATH_OFFLOAD_STATE_CACHED CachedState;
    PATH_OFFLOAD_STATE_DELEGATED DelegatedState;
} PATH_OFFLOAD_STATE, *PPATH_OFFLOAD_STATE;

//
// NEIGHBOR_OFFLOAD_STATE_CONST
//
// Neighbor const parameters.
//
typedef struct _NEIGHBOR_OFFLOAD_STATE_CONST {
    OFFLOAD_STATE_HEADER Header;
    UCHAR DlSourceAddress[32];
    ULONG VlanId: 12;
} NEIGHBOR_OFFLOAD_STATE_CONST, *PNEIGHBOR_OFFLOAD_STATE_CONST;

//
// NEIGHBOR_OFFLOAD_STATE_CACHED
//
// Neighbor cached parameters.
//
typedef struct _NEIGHBOR_OFFLOAD_STATE_CACHED {
    OFFLOAD_STATE_HEADER Header;
    UCHAR DlDestinationAddress[32];
    ULONG HostReachabilityDelta;
} NEIGHBOR_OFFLOAD_STATE_CACHED, *PNEIGHBOR_OFFLOAD_STATE_CACHED;

//
// NEIGHBOR_OFFLOAD_STATE_DELEGATED
//
// Neighbor cached parameters.
//
typedef struct _NEIGHBOR_OFFLOAD_STATE_DELEGATED {
    OFFLOAD_STATE_HEADER Header;
    ULONG NicReachabilityDelta;
} NEIGHBOR_OFFLOAD_STATE_DELEGATED, *PNEIGHBOR_OFFLOAD_STATE_DELEGATED;

//
// NEIGHBOR_OFFLOAD_STATE
//
typedef struct _NEIGHBOR_OFFLOAD_STATE {
    NEIGHBOR_OFFLOAD_STATE_CONST ConstState;
    NEIGHBOR_OFFLOAD_STATE_CACHED CachedState;
    NEIGHBOR_OFFLOAD_STATE_DELEGATED DelegatedState;
} NEIGHBOR_OFFLOAD_STATE, *PNEIGHBOR_OFFLOAD_STATE;

//
// TCP_OFFLOAD_STATS
//
// Statistics definitions in TCP on a per interface basis
//
typedef struct _TCP_OFFLOAD_STATS {
    ULONG64 InSegments;
    ULONG64 OutSegments;
    ULONG CurrentlyEstablished;
    ULONG ResetEstablished;
    ULONG RetransmittedSegments;
    ULONG InErrors;
    ULONG OutResets;
} TCP_OFFLOAD_STATS, *PTCP_OFFLOAD_STATS;

//
// IP_OFFLOAD_STATS
//
// Stats definitions in IPV4/IPV6 on a per interface basis
//
typedef struct _IP_OFFLOAD_STATS {
    ULONG64 InReceives;
    ULONG64 InOctets;
    ULONG64 InDelivers;
    ULONG64 OutRequests;
    ULONG64 OutOctets;
    ULONG InHeaderErrors;
    ULONG InTruncatedPackets;
    ULONG InDiscards;
    ULONG OutDiscards;
    ULONG OutNoRoutes;
} IP_OFFLOAD_STATS, *PIP_OFFLOAD_STATS;

#endif // _CHIMNEY_OFFLOAD_

#endif // NDIS_CHIMNEY_OFFLOAD


//
// Function types for NDIS_PROTOCOL_CHARACTERISTICS
//
 
typedef
VOID
(*OPEN_ADAPTER_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_STATUS             Status,
    IN  NDIS_STATUS             OpenErrorStatus
    );

typedef
VOID
(*CLOSE_ADAPTER_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*RESET_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_STATUS             Status
    );
 
typedef
VOID
(*REQUEST_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_REQUEST           NdisRequest,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*STATUS_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_STATUS             GeneralStatus,
    IN  PVOID                   StatusBuffer,
    IN  UINT                    StatusBufferSize
    );
 
typedef
VOID
(*STATUS_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext
    );

typedef
VOID
(*SEND_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_PACKET            Packet,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*WAN_SEND_COMPLETE_HANDLER) (
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_WAN_PACKET        Packet,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*TRANSFER_DATA_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_PACKET            Packet,
    IN  NDIS_STATUS             Status,
    IN  UINT                    BytesTransferred
    );

typedef
VOID
(*WAN_TRANSFER_DATA_COMPLETE_HANDLER)(
    VOID
    );

typedef
NDIS_STATUS
(*RECEIVE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookAheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize
    );

typedef
NDIS_STATUS
(*WAN_RECEIVE_HANDLER)(
    IN  NDIS_HANDLE             NdisLinkHandle,
    IN  PUCHAR                  Packet,
    IN  ULONG                   PacketSize
    );

typedef
VOID
(*RECEIVE_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext
    );

//
// Protocol characteristics for down-level NDIS 3.0 protocols
//
typedef struct _NDIS30_PROTOCOL_CHARACTERISTICS
{
    UCHAR                           MajorNdisVersion;
    UCHAR                           MinorNdisVersion;
    USHORT                          Filler;
    union
    {
        UINT                        Reserved;
        UINT                        Flags;
    };
    OPEN_ADAPTER_COMPLETE_HANDLER   OpenAdapterCompleteHandler;
    CLOSE_ADAPTER_COMPLETE_HANDLER  CloseAdapterCompleteHandler;
    union
    {
        SEND_COMPLETE_HANDLER       SendCompleteHandler;
        WAN_SEND_COMPLETE_HANDLER   WanSendCompleteHandler;
    };
    union
    {
     TRANSFER_DATA_COMPLETE_HANDLER TransferDataCompleteHandler;
     WAN_TRANSFER_DATA_COMPLETE_HANDLER WanTransferDataCompleteHandler;
    };

    RESET_COMPLETE_HANDLER          ResetCompleteHandler;
    REQUEST_COMPLETE_HANDLER        RequestCompleteHandler;
    union
    {
        RECEIVE_HANDLER             ReceiveHandler;
        WAN_RECEIVE_HANDLER         WanReceiveHandler;
    };
    RECEIVE_COMPLETE_HANDLER        ReceiveCompleteHandler;
    STATUS_HANDLER                  StatusHandler;
    STATUS_COMPLETE_HANDLER         StatusCompleteHandler;
    NDIS_STRING                     Name;
} NDIS30_PROTOCOL_CHARACTERISTICS;

//
// Function types extensions for NDIS 4.0 Protocols
//
typedef
INT
(*RECEIVE_PACKET_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_PACKET            Packet
    );

typedef
VOID
(*BIND_HANDLER)(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             BindContext,
    IN  PNDIS_STRING            DeviceName,
    IN  PVOID                   SystemSpecific1,
    IN  PVOID                   SystemSpecific2
    );

typedef
VOID
(*UNBIND_HANDLER)(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_HANDLE             UnbindContext
    );
 
typedef
NDIS_STATUS
(*PNP_EVENT_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNET_PNP_EVENT          NetPnPEvent
    );

typedef
VOID
(*UNLOAD_PROTOCOL_HANDLER)(
    VOID
    );

//
// Protocol characteristics for NDIS 4.0 protocols
//
typedef struct _NDIS40_PROTOCOL_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS30_PROTOCOL_CHARACTERISTICS Ndis30Chars;
#else
    NDIS30_PROTOCOL_CHARACTERISTICS;
#endif

    //
    // Start of NDIS 4.0 extensions.
    //
    RECEIVE_PACKET_HANDLER          ReceivePacketHandler;

    //
    // PnP protocol entry-points
    //
    BIND_HANDLER                    BindAdapterHandler;
    UNBIND_HANDLER                  UnbindAdapterHandler;
    PNP_EVENT_HANDLER               PnPEventHandler;
    UNLOAD_PROTOCOL_HANDLER         UnloadHandler;

} NDIS40_PROTOCOL_CHARACTERISTICS;


//
// Protocol (5.0) handler proto-types - used by clients as well as call manager modules
//
typedef
VOID
(*CO_SEND_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PNDIS_PACKET            Packet
    );

typedef
VOID
(*CO_STATUS_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_HANDLE             ProtocolVcContext   OPTIONAL,
    IN  NDIS_STATUS             GeneralStatus,
    IN  PVOID                   StatusBuffer,
    IN  UINT                    StatusBufferSize
    );

typedef
UINT
(*CO_RECEIVE_PACKET_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PNDIS_PACKET            Packet
    );

typedef
NDIS_STATUS
(*CO_REQUEST_HANDLER)(
    IN  NDIS_HANDLE             ProtocolAfContext,
    IN  NDIS_HANDLE             ProtocolVcContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    IN OUT PNDIS_REQUEST        NdisRequest
    );

typedef
VOID
(*CO_REQUEST_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolAfContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolVcContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    IN  PNDIS_REQUEST           NdisRequest
    );

typedef
NDIS_STATUS
(*CO_REQUEST_HANDLER_EX)(
    IN  NDIS_HANDLE             ProtocolAfContext,
    IN  NDIS_HANDLE             ProtocolVcContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    IN OUT PNDIS_REQUEST_EX     NdisRequest
    );

typedef
NDIS_STATUS
(*CO_OID_REQUEST_HANDLER)(
    IN  NDIS_HANDLE             ProtocolAfContext,
    IN  NDIS_HANDLE             ProtocolVcContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    IN OUT PNDIS_REQUEST_EX     NdisRequest
    );
    
typedef
VOID
(*CO_REQUEST_COMPLETE_HANDLER_EX)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolAfContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolVcContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    IN  PNDIS_REQUEST_EX        NdisRequest
    );

typedef
VOID
(*CO_OID_REQUEST_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolAfContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolVcContext       OPTIONAL,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    IN  PNDIS_REQUEST_EX        NdisRequest
    );
    
//
// CO_CREATE_VC_HANDLER and CO_DELETE_VC_HANDLER are synchronous calls
//
typedef
NDIS_STATUS
(*CO_CREATE_VC_HANDLER)(
    IN  NDIS_HANDLE             ProtocolAfContext,
    IN  NDIS_HANDLE             NdisVcHandle,
    OUT PNDIS_HANDLE            ProtocolVcContext
    );

typedef
NDIS_STATUS
(*CO_DELETE_VC_HANDLER)(
    IN  NDIS_HANDLE             ProtocolVcContext
    );

typedef
VOID
(*CO_AF_REGISTER_NOTIFY_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PCO_ADDRESS_FAMILY      AddressFamily
    );

typedef struct _NDIS50_PROTOCOL_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS40_PROTOCOL_CHARACTERISTICS Ndis40Chars;
#else
    NDIS40_PROTOCOL_CHARACTERISTICS;
#endif

    //
    // Placeholders for protocol extensions for PnP/PM etc.
    //
    PVOID                           ReservedHandlers[4];

    //
    // Start of NDIS 5.0 extensions.
    //

    CO_SEND_COMPLETE_HANDLER        CoSendCompleteHandler;
    CO_STATUS_HANDLER               CoStatusHandler;
    CO_RECEIVE_PACKET_HANDLER       CoReceivePacketHandler;
    CO_AF_REGISTER_NOTIFY_HANDLER   CoAfRegisterNotifyHandler;

} NDIS50_PROTOCOL_CHARACTERISTICS;


//BUGBUG6 #if (defined(NDIS60) || defined(NDIS52))
typedef struct _NDIS_OFFLOAD_HANDLE
{
    PVOID NdisReserved[1];    
    PVOID MiniportOffloadContext;
} NDIS_OFFLOAD_HANDLE, *PNDIS_OFFLOAD_HANDLE;


typedef struct _NDIS_PROTOCOL_OFFLOAD_BLOCK_LIST {
    IN NDIS_OBJECT_HEADER Header;
    IN struct _NDIS_PROTOCOL_OFFLOAD_BLOCK_LIST *NextBlock;
    IN struct _NDIS_PROTOCOL_OFFLOAD_BLOCK_LIST *DependentBlockList;
    OUT NDIS_STATUS Status;
    IN PVOID NdisReserved[3];
    IN OUT PNDIS_OFFLOAD_HANDLE OffloadHandle;
    IN PVOID ProtocolReserved[2];
    IN PVOID MiniportReserved[2];
    IN PVOID ImReserved[2];
    IN PVOID Scratch[2];    
    IN PVOID SourceHandle;
    IN OUT PNET_BUFFER_LIST NetBufferListChain;    
    //
    // The state specific information (if any)  will follow this.
    //
} NDIS_PROTOCOL_OFFLOAD_BLOCK_LIST, *PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST;

//
// Generic offload functions supported by the protocol.
//
typedef
VOID
(*INITIATE_OFFLOAD_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

typedef
VOID
(*TERMINATE_OFFLOAD_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

typedef
VOID
(*INVALIDATE_OFFLOAD_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

typedef
VOID
(*UPDATE_OFFLOAD_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

typedef
VOID
(*QUERY_OFFLOAD_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

//
// Generic indication handlers supported by the protocol.
//
typedef
VOID
(*INDICATE_OFFLOAD_EVENT_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList,
    IN ULONG                                 IndicationCode
    );

//
// Tcp offload specific functions supported by the protocol, for completions.
//
typedef
VOID
(*TCP_OFFLOAD_SEND_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
VOID
(*TCP_OFFLOAD_RECV_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
VOID
(*TCP_OFFLOAD_DISCONNECT_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
VOID
(*TCP_OFFLOAD_FORWARD_COMPLETE_HANDLER)(
    IN NDIS_HANDLE                           ProtocolBindingContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

//
// Tcp offload specific functions supported by the protocol, for indications.
//
typedef
VOID
(*TCP_OFFLOAD_EVENT_HANDLER)(
    IN PVOID                                 OffloadContext,
    IN ULONG                                 EventType,
    IN ULONG                                 EventSpecificInformation
    );

typedef
NDIS_STATUS
(*TCP_OFFLOAD_RECEIVE_INDICATE_HANDLER)(
    IN PVOID                                 OffloadContext,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN NDIS_STATUS                           Status
    );

typedef struct _NDIS_OFFLOAD_CLIENT_HANDLERS {
    NDIS_OBJECT_HEADER                       Header;
} NDIS_OFFLOAD_CLIENT_HANDLERS, *PNDIS_OFFLOAD_CLIENT_HANDLERS;

typedef struct _NDIS_TCP_OFFLOAD_CLIENT_HANDLERS
{
    NDIS_OBJECT_HEADER                       Header;
    TCP_OFFLOAD_SEND_COMPLETE_HANDLER        TcpOffloadSendCompleteHandler;
    TCP_OFFLOAD_RECV_COMPLETE_HANDLER        TcpOffloadReceiveCompleteHandler;
    TCP_OFFLOAD_DISCONNECT_COMPLETE_HANDLER  TcpOffloadDisconnectCompleteHandler;
    TCP_OFFLOAD_FORWARD_COMPLETE_HANDLER     TcpOffloadForwardCompleteHandler;
    TCP_OFFLOAD_EVENT_HANDLER                TcpOffloadEventHandler;
    TCP_OFFLOAD_RECEIVE_INDICATE_HANDLER     TcpOffloadReceiveIndicateHandler;
} NDIS_TCP_OFFLOAD_CLIENT_HANDLERS, *PNDIS_TCP_OFFLOAD_CLIENT_HANDLERS;

//BUGBUG6 #endif // (defined(NDIS60) || defined(NDIS52))


//BUGBUG6 #if (defined(NDIS60))

//
// CONDIS 6.0 protocol's entry points
//

typedef
VOID
(*CO_RECEIVE_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*CO_SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*CO_STATUS_HANDLER_EX)(
    IN NDIS_HANDLE              ProtocolBindingContext,
    IN NDIS_HANDLE              ProtocolVcContext,
    IN PNDIS_STATUS_INDICATION  StatusIndication
    );
 
//BUGBUG6 #endif

#if (defined(NDIS60) || defined(NDIS52))

typedef struct _NDIS52_PROTOCOL_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS50_PROTOCOL_CHARACTERISTICS Ndis50Chars;
#else
    NDIS50_PROTOCOL_CHARACTERISTICS;
#endif
    //
    // Generic Offload initiation and termination completion handlers.
    //
    INITIATE_OFFLOAD_COMPLETE_HANDLER        InitiateOffloadCompleteHandler;
    TERMINATE_OFFLOAD_COMPLETE_HANDLER       TerminateOffloadCompleteHandler;

    //
    // Generic offload state control request completion handlers.
    //
    UPDATE_OFFLOAD_COMPLETE_HANDLER          UpdateOffloadCompleteHandler;
    INVALIDATE_OFFLOAD_COMPLETE_HANDLER      InvalidateOffloadCompleteHandler;
    QUERY_OFFLOAD_COMPLETE_HANDLER           QueryOffloadCompleteHandler;

    //
    // Generic offload state indication handlers.
    //
    INDICATE_OFFLOAD_EVENT_HANDLER           IndicateOffloadEventHandler;

} NDIS52_PROTOCOL_CHARACTERISTICS;

#endif

//
// Requests used by Protocol Modules
//

EXPORT
VOID
NdisDeregisterProtocolDriver(
    IN  NDIS_HANDLE             NdisProtocolHandle
    );

EXPORT
VOID
NdisDeregisterProtocol(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisProtocolHandle
    );


EXPORT
VOID
NdisOpenAdapter(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_STATUS            OpenErrorStatus,
    OUT PNDIS_HANDLE            NdisBindingHandle,
    OUT PUINT                   SelectedMediumIndex,
    IN  PNDIS_MEDIUM            MediumArray,
    IN  UINT                    MediumArraySize,
    IN  NDIS_HANDLE             NdisProtocolHandle,
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_STRING            AdapterName,
    IN  UINT                    OpenOptions,
    IN  PSTRING                 AddressingInformation OPTIONAL
    );


EXPORT
VOID
NdisCloseAdapter(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle
    );


EXPORT
VOID
NdisCompleteBindAdapter(
    IN   NDIS_HANDLE            BindAdapterContext,
    IN   NDIS_STATUS            Status,
    IN   NDIS_STATUS            OpenStatus
    );

EXPORT
VOID
NdisCompleteUnbindAdapter(
    IN   NDIS_HANDLE            UnbindAdapterContext,
    IN   NDIS_STATUS            Status
    );

EXPORT
VOID
NdisSetProtocolFilter(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  RECEIVE_HANDLER         ReceiveHandler,
    IN  RECEIVE_PACKET_HANDLER  ReceivePacketHandler,
    IN  NDIS_MEDIUM             Medium,
    IN  UINT                    Offset,
    IN  UINT                    Size,
    IN  PUCHAR                  Pattern
    );

EXPORT
VOID
NdisOpenProtocolConfiguration(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            ConfigurationHandle,
    IN  PNDIS_STRING            ProtocolSection
);

EXPORT
VOID
NdisGetDriverHandle(
    IN  NDIS_HANDLE             NdisBindingHandle,
    OUT PNDIS_HANDLE            NdisDriverHandle
    );

EXPORT
VOID
NdisReEnumerateProtocolBindings(
    IN  NDIS_HANDLE             NdisProtocolHandle
    );

EXPORT
NDIS_STATUS
NdisWriteEventLogEntry(
    IN  PVOID                   LogHandle,
    IN  NDIS_STATUS             EventCode,
    IN  ULONG                   UniqueEventValue,
    IN  USHORT                  NumStrings,
    IN  PVOID                   StringsList    OPTIONAL,
    IN  ULONG                   DataSize,
    IN  PVOID                   Data           OPTIONAL
    );

//
//  The following routine is used by transports to complete pending
//  network PnP events.
//
EXPORT
VOID
NdisCompletePnPEvent(
    IN  NDIS_STATUS     Status,
    IN  NDIS_HANDLE     NdisBindingHandle,
    IN  PNET_PNP_EVENT  NetPnPEvent
    );

//
//  The following routine is used by a transport to query the localized
//  friendly instance name of the adapter that they are bound to. There
//  are two variations of this, one uses the binding handle and the other
//  the binding context. Some transports need this before they bind - like
//  TCP/IP for instance.
//
EXPORT
NDIS_STATUS
NdisQueryAdapterInstanceName(
    OUT PNDIS_STRING    pAdapterInstanceName,
    IN  NDIS_HANDLE     NdisBindingHandle
    );

EXPORT
NDIS_STATUS
NdisQueryBindInstanceName(
    OUT PNDIS_STRING    pAdapterInstanceName,
    IN  NDIS_HANDLE     BindingContext
    );

//
// The following is used by TDI/NDIS interface as part of Network PnP.
// For use by TDI alone.
//
typedef
NTSTATUS
(*TDI_REGISTER_CALLBACK)(
    IN  PUNICODE_STRING         DeviceName,
    OUT HANDLE  *               TdiHandle
    );

typedef
NTSTATUS
(*TDI_PNP_HANDLER)(
    IN  PUNICODE_STRING         UpperComponent,
    IN  PUNICODE_STRING         LowerComponent,
    IN  PUNICODE_STRING         BindList,
    IN  PVOID                   ReconfigBuffer,
    IN  UINT                    ReconfigBufferSize,
    IN  UINT                    Operation
    );

EXPORT
VOID
NdisRegisterTdiCallBack(
    IN  TDI_REGISTER_CALLBACK   RegisterCallback,
    IN  TDI_PNP_HANDLER         PnPHandler
    );

EXPORT
VOID
NdisRegisterTdiPnpHandler(
    IN  TDI_PNP_HANDLER         PnPHandler
    );


EXPORT
VOID
NdisDeregisterTdiCallBack(
    VOID
    );

VOID
NdisReset(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle
    );

VOID
NdisRequest(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_REQUEST           NdisRequest
    );

#if BINARY_COMPATIBLE

VOID
NdisSend(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_PACKET            Packet
    );

VOID
NdisSendPackets(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );

VOID
NdisTransferData(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  UINT                    ByteOffset,
    IN  UINT                    BytesToTransfer,
    IN OUT  PNDIS_PACKET        Packet,
    OUT PUINT                   BytesTransferred
    );


#else // BINARY_COMPATIBLE


#ifdef __cplusplus

#define NdisSend(Status, NdisBindingHandle, Packet)                                     \
{                                                                                       \
    *(Status) =                                                                         \
        (((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.SendHandler)(     \
            ((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.BindingHandle, \
        (Packet));                                                                      \
}

#define NdisSendPackets(NdisBindingHandle, PacketArray, NumberOfPackets)                \
{                                                                                       \
    (((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.SendPacketsHandler)(  \
        (PNDIS_OPEN_BLOCK)(NdisBindingHandle),                                          \
        (PacketArray),                                                                  \
        (NumberOfPackets));                                                             \
}

#define WanMiniportSend(Status,                                                         \
                        NdisBindingHandle,                                              \
                        NdisLinkHandle,                                                 \
                        WanPacket)                                                      \
{                                                                                       \
    *(Status) =                                                                         \
        ((((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.WanSendHandler))( \
            ((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.BindingHandle, \
            (NdisLinkHandle),                                                           \
            (PNDIS_PACKET)(WanPacket));                                                 \
}

#define NdisTransferData(Status,                                                        \
                         NdisBindingHandle,                                             \
                         MacReceiveContext,                                             \
                         ByteOffset,                                                    \
                         BytesToTransfer,                                               \
                         Packet,                                                        \
                         BytesTransferred)                                              \
{                                                                                       \
    *(Status) =                                                                         \
        (((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.TransferDataHandler)( \
            ((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->NdisCommonOpenBlock.BindingHandle, \
            (MacReceiveContext),                                                        \
            (ByteOffset),                                                               \
            (BytesToTransfer),                                                          \
            (Packet),                                                                   \
            (BytesTransferred));                                                        \
}

#else

#define NdisSend(Status, NdisBindingHandle, Packet)                         \
{                                                                           \
    *(Status) =                                                             \
        (((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->SendHandler)(             \
            ((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->BindingHandle,         \
        (Packet));                                                          \
}


#define NdisSendPackets(NdisBindingHandle, PacketArray, NumberOfPackets)    \
{                                                                           \
    (((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->SendPacketsHandler)(          \
        (PNDIS_OPEN_BLOCK)(NdisBindingHandle),                              \
        (PacketArray),                                                      \
        (NumberOfPackets));                                                 \
}

#define WanMiniportSend(Status,                                             \
                        NdisBindingHandle,                                  \
                        NdisLinkHandle,                                     \
                        WanPacket)                                          \
{                                                                           \
    *(Status) =                                                             \
        ((((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->WanSendHandler))(        \
            ((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->BindingHandle,         \
            (NdisLinkHandle),                                               \
            (PNDIS_PACKET)(WanPacket));                                     \
}

#define NdisTransferData(Status,                                            \
                         NdisBindingHandle,                                 \
                         MacReceiveContext,                                 \
                         ByteOffset,                                        \
                         BytesToTransfer,                                   \
                         Packet,                                            \
                         BytesTransferred)                                  \
{                                                                           \
    *(Status) =                                                             \
        (((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->TransferDataHandler)(     \
            ((PNDIS_OPEN_BLOCK)(NdisBindingHandle))->BindingHandle,         \
            (MacReceiveContext),                                            \
            (ByteOffset),                                                   \
            (BytesToTransfer),                                              \
            (Packet),                                                       \
            (BytesTransferred));                                            \
}

#endif // ifdef __cplusplus

#endif // BINARY_COMPATIBLE

//
// Routines to access packet flags
//

/*++

VOID
NdisSetSendFlags(
    IN  PNDIS_PACKET            Packet,
    IN  UINT                    Flags
    );

--*/

#define NdisSetSendFlags(_Packet,_Flags)    (_Packet)->Private.Flags = (_Flags)

/*++

VOID
NdisQuerySendFlags(
    IN  PNDIS_PACKET            Packet,
    OUT PUINT                   Flags
    );

--*/

#define NdisQuerySendFlags(_Packet,_Flags)  *(_Flags) = (_Packet)->Private.Flags

//
// The following is the minimum size of packets a miniport must allocate
// when it indicates packets via NdisMIndicatePacket or NdisMCoIndicatePacket
//
#define PROTOCOL_RESERVED_SIZE_IN_PACKET    (4 * sizeof(PVOID))

EXPORT
VOID
NdisReturnPackets(
    IN  PNDIS_PACKET    *       PacketsToReturn,
    IN  UINT                    NumberOfPackets
    );

EXPORT
PNDIS_PACKET
NdisGetReceivedPacket(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             MacContext
    );

//
// Macros to portably manipulate NDIS buffers.
//
#if BINARY_COMPATIBLE

EXPORT
ULONG
NdisBufferLength(
    IN  PNDIS_BUFFER            Buffer
    );

EXPORT
PVOID
NdisBufferVirtualAddress(
    IN  PNDIS_BUFFER            Buffer
    );

#else // BINARY_COMPATIBLE

#define NdisBufferLength(Buffer)                            MmGetMdlByteCount(Buffer)
#define NdisBufferVirtualAddress(_Buffer)                   MmGetSystemAddressForMdl(_Buffer)
#define NdisBufferVirtualAddressSafe(_Buffer, _Priority)    MmGetSystemAddressForMdlSafe(_Buffer, _Priority)

#endif  // BINARY_COMPATIBLE

//
// Ndis 5.1 entry points for setting/gettign packet's CancelId and cancelling send packets
//

// #if (defined(NDIS50) || defined(NDIS51) || defined(NDIS50_MINIPORT) || defined(NDIS51_MINIPORT))
/*
EXPORT
VOID
NdisSetPacketCancelId(
    IN  PNDIS_PACKET    Packet,
    IN  PVOID           CancelId
    );
*/
#define  NdisSetPacketCancelId(_Packet, _CancelId) NDIS_SET_PACKET_CANCEL_ID(_Packet, _CancelId);

/*
EXPORT
PVOID
NdisGetPacketCancelId(
    IN  PNDIS_PACKET    Packet
    );
*/
#define  NdisGetPacketCancelId(_Packet) NDIS_GET_PACKET_CANCEL_ID(_Packet);

EXPORT
VOID
NdisCancelSendPackets(
    IN  NDIS_HANDLE     NdisBindingHandle,
    IN  PVOID           CancelId
    );

EXPORT
NDIS_STATUS
NdisQueryPendingIOCount(
    IN      PVOID       NdisBindingHandle,
    IN OUT  PULONG      IoCount
    );

EXPORT
UCHAR
NdisGeneratePartialCancelId(
    VOID
    );


//BUGBUG6 #if (defined(NDIS60) || defined(NDIS60_MINIPORT))

//
// NDIS 6.0 protocol's entry points
//
typedef
VOID
(*OID_REQUEST_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_REQUEST_EX        Request,
    IN  NDIS_STATUS             Status
    );
    
typedef
VOID
(*REQUEST_COMPLETE_HANDLER_EX)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_REQUEST_EX        Request,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*RECEIVE_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_STATUS             Status,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  BOOLEAN                 DispatchLevel
    );

//
// structure passed to protocol's BIND_HANDLER_EX
//
#define NDIS_BIND_PARAMETERS_REVISION_1     1

typedef struct _NDIS_BIND_PARAMETERS
{
    NDIS_OBJECT_HEADER              Header;
    PNDIS_STRING                    ProtocolSection;
    PNDIS_STRING                    AdapterName;
    PDEVICE_OBJECT                  PhysicalDeviceObject;
    NDIS_MEDIUM                     MediaType;
    ULONG                           MtuSize;
    ULONG64                         MaxXmitLinkSpeed;
    ULONG64                         XmitLinkSpeed;
    ULONG64                         MaxRcvLinkSpeed;
    ULONG64                         RcvLinkSpeed;
    NDIS_MEDIA_CONNECT_STATE        MediaConnectState;
    NDIS_MEDIA_DUPLEX_STATE         MediaDuplexState;
    ULONG                           LookaheadSize;
    PNDIS_PNP_CAPABILITIES          PowerManagementCapabilities;
    ULONG                           SupportedPacketFilters;
    ULONG                           MaxMulticastListSize;
    USHORT                          MacAddressLength;
    UCHAR                           CurrentMacAddress[NDIS_MAX_PHYS_ADDRESS_LENGTH];
    NDIS_PHYSICAL_MEDIUM            PhysicalMediumType;
    PNDIS_RECEIVE_SCALE_CAPABILITIES RcvScaleCapabilities;
    NET_LUID                        BoundIfNetluid;
    NET_IFINDEX                     BoundIfIndex;
    NET_LUID                        LowestIfNetluid;
    NET_IFINDEX                     LowestIfIndex;
    NET_IF_ACCESS_TYPE              AccessType; // NET_IF_ACCESS_BROADCAST for a typical ethernet adapter
    NET_IF_DIRECTION_TYPE           DirectionType; // NET_IF_DIRECTION_SENDRECEIVE for a typical ethernet adapter
    NET_IF_CONNECTION_TYPE          ConnectionType; // NET_IF_CONNECTION_DEDICATED for a typical ethernet adapter
    NET_IFTYPE                      IfType; // IF_TYPE_ETHERNET_CSMACD for a typical ethernet adapter (regardless of speed)
    BOOLEAN                         IfConnectorPresent; // RFC 2665 TRUE if physical adapter
    
}NDIS_BIND_PARAMETERS, *PNDIS_BIND_PARAMETERS;


/*
typedef struct _NDIS_BIND_PARAMETERS
{
    NDIS_OBJECT_HEADER              Header;
    PNDIS_STRING                    ProtocolSection;
    PNDIS_STRING                    AdapterName;
    PDEVICE_OBJECT                  PhysicalDeviceObject;
}NDIS_BIND_PARAMETERS, *PNDIS_BIND_PARAMETERS;
*/

typedef
NDIS_STATUS
(*BIND_HANDLER_EX)(
    IN  NDIS_HANDLE             ProtocolDriverContext,
    IN  NDIS_HANDLE             BindContext,
    IN  PNDIS_BIND_PARAMETERS   BindParameters
    );

typedef
NDIS_STATUS
(*UNBIND_HANDLER_EX)(
    IN  NDIS_HANDLE             UnbindContext,
    IN  NDIS_HANDLE             ProtocolBindingContext
    );

typedef
VOID
(*OPEN_ADAPTER_COMPLETE_HANDLER_EX)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*CLOSE_ADAPTER_COMPLETE_HANDLER_EX)(
    IN  NDIS_HANDLE             ProtocolBindingContext
    );


typedef
VOID
(*STATUS_HANDLER_EX)(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_STATUS_INDICATION StatusIndication
    );


#define NDIS_PROTOCOL_CO_CHARACTERISTICS_REVISION_1     1

typedef struct _NDIS_PROTOCOL_CO_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                      Header;     // Header.Type = NDIS_OBJECT_TYPE_PROTOCOL_CO_CHARACTERISTICS
    ULONG                                   Flags;
    CO_STATUS_HANDLER_EX                    CoStatusHandlerEx;
    CO_AF_REGISTER_NOTIFY_HANDLER           CoAfRegisterNotifyHandler;
    CO_RECEIVE_NET_BUFFER_LISTS_HANDLER     CoReceiveNetBufferListsHandler;
    CO_SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER CoSendNetBufferListsCompleteHandler;
} NDIS_PROTOCOL_CO_CHARACTERISTICS, *PNDIS_PROTOCOL_CO_CHARACTERISTICS;

//BUGBUG6 #endif // defined(NDIS60)

#if (defined(NDIS60) || defined(NDIS52))
#define NDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS_REVISION_1     1

typedef struct _NDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                      Header;     // Header.Type = NDIS_OBJECT_TYPE_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS
    ULONG                                   Flags;
    //
    // Generic Offload initiation and termination completion handlers.
    //
    INITIATE_OFFLOAD_COMPLETE_HANDLER        InitiateOffloadCompleteHandler;
    TERMINATE_OFFLOAD_COMPLETE_HANDLER       TerminateOffloadCompleteHandler;
    
    //
    // Generic offload state control request completion handlers.
    //
    UPDATE_OFFLOAD_COMPLETE_HANDLER          UpdateOffloadCompleteHandler;
    INVALIDATE_OFFLOAD_COMPLETE_HANDLER      InvalidateOffloadCompleteHandler;
    QUERY_OFFLOAD_COMPLETE_HANDLER           QueryOffloadCompleteHandler;
    
    //
    // Generic offload state indication handlers.
    //
    INDICATE_OFFLOAD_EVENT_HANDLER           IndicateOffloadEventHandler;
    
} NDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS, *PNDIS_CLIENT_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS;

#define NDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS_REVISION_1  1

typedef struct _NDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                          Header;         // Header.Type = NDIS_OBJECT_TYPE_CLIENT_CHIMNEY_OFFLOAD_CHARACTERISTICS
    ULONG                                       Flags;
    NDIS_CHIMNEY_OFFLOAD_TYPE                   OffloadType;    // NdisTcpChimneyOffload
    TCP_OFFLOAD_SEND_COMPLETE_HANDLER           TcpOffloadSendCompleteHandler;
    TCP_OFFLOAD_RECV_COMPLETE_HANDLER           TcpOffloadReceiveCompleteHandler;
    TCP_OFFLOAD_DISCONNECT_COMPLETE_HANDLER     TcpOffloadDisconnectCompleteHandler;
    TCP_OFFLOAD_FORWARD_COMPLETE_HANDLER        TcpOffloadForwardCompleteHandler;
    TCP_OFFLOAD_EVENT_HANDLER                   TcpOffloadEventHandler;
    TCP_OFFLOAD_RECEIVE_INDICATE_HANDLER        TcpOffloadReceiveIndicateHandler;
} NDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS, *PNDIS_CLIENT_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS;
#endif // (defined(NDIS60) || defined(NDIS52))

#if (defined(NDIS60))

#define NDIS_PROTOCOL_DRIVER_CHARACTERISTICS_REVISION_1     1

typedef struct _NDIS_PROTOCOL_DRIVER_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                      Header;
    UCHAR                                   MajorNdisVersion;
    UCHAR                                   MinorNdisVersion;
    UCHAR                                   MajorDriverVersion;
    UCHAR                                   MinorDriverVersion;
    ULONG                                   Flags;
    NDIS_STRING                             Name;
    SET_OPTIONS_HANDLER                     SetOptionsHandler;
    BIND_HANDLER_EX                         BindAdapterHandlerEx;
    UNBIND_HANDLER_EX                       UnbindAdapterHandlerEx;
    OPEN_ADAPTER_COMPLETE_HANDLER_EX        OpenAdapterCompleteHandlerEx;
    CLOSE_ADAPTER_COMPLETE_HANDLER_EX       CloseAdapterCompleteHandlerEx;
    PNP_EVENT_HANDLER                       PnPEventHandler;
    UNLOAD_PROTOCOL_HANDLER                 UnloadHandler;
    union
    {
        OID_REQUEST_COMPLETE_HANDLER            OidRequestCompleteHandler;
        REQUEST_COMPLETE_HANDLER_EX             RequestCompleteHandlerEx;
    };
    STATUS_HANDLER_EX                       StatusHandlerEx;
    RECEIVE_NET_BUFFER_LISTS_HANDLER        ReceiveNetBufferListHandler;
    SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER  SendNetBufferListsCompleteHandler;
    REQUEST_COMPLETE_HANDLER                RequestCompleteHandler;  //temporarily present.
} NDIS_PROTOCOL_DRIVER_CHARACTERISTICS, *PNDIS_PROTOCOL_DRIVER_CHARACTERISTICS;

#endif


#if (defined(NDIS52))
typedef NDIS52_PROTOCOL_CHARACTERISTICS  NDIS_PROTOCOL_CHARACTERISTICS;
#else
#if (defined(NDIS50) || defined(NDIS51))
typedef NDIS50_PROTOCOL_CHARACTERISTICS  NDIS_PROTOCOL_CHARACTERISTICS;
#else
#if NDIS40
typedef NDIS40_PROTOCOL_CHARACTERISTICS  NDIS_PROTOCOL_CHARACTERISTICS;
#else
typedef NDIS30_PROTOCOL_CHARACTERISTICS  NDIS_PROTOCOL_CHARACTERISTICS;
#endif
#endif
#endif


typedef NDIS_PROTOCOL_CHARACTERISTICS *PNDIS_PROTOCOL_CHARACTERISTICS;

EXPORT
VOID
NdisRegisterProtocol(
    OUT PNDIS_STATUS            Status,
    OUT PNDIS_HANDLE            NdisProtocolHandle,
    IN  PNDIS_PROTOCOL_CHARACTERISTICS ProtocolCharacteristics,
    IN  UINT                    CharacteristicsLength
    );

#if (defined(NDIS60))

EXPORT
NDIS_STATUS
NdisRegisterProtocolDriver(
    IN  NDIS_HANDLE             ProtocolDriverContext,
    IN  PNDIS_PROTOCOL_DRIVER_CHARACTERISTICS ProtocolCharacteristics,
    OUT PNDIS_HANDLE            NdisProtocolHandle
    );

//
// This flag is passed to NdisSendNetBufferList and is used if the protocol wants
// NDIS to check the NetBufferList for Loopback and loop the NetBufferList if necessary
//
#define SEND_FLAGS_CHECK_FOR_LOOPBACK                 0x00000001

EXPORT
VOID
NdisSendNetBufferLists(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  ULONG                   SendFlags,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisReturnNetBufferLists(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisCancelSendNetBufferLists(
    IN  NDIS_HANDLE     NdisBindingHandle,
    IN  PVOID           CancelId
    );

EXPORT
NDIS_STATUS
NdisRequestEx(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_REQUEST_EX        NdisRequest
    );

EXPORT
NDIS_STATUS
NdisOidRequest(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_REQUEST_EX        NdisRequest
    );

EXPORT
VOID
NdisCancelRequest(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PNDIS_OID_REQUEST       NdisRequest
    );

#endif // (defined(NDIS60))

#if (defined(NDIS60) || defined(NDIS52))

//
// Generic offload functions supported by NDIS, for use by the protocol.
//
EXPORT
VOID
NdisInitiateOffload(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

EXPORT
VOID
NdisTerminateOffload(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

EXPORT
VOID
NdisInvalidateOffload(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

EXPORT
VOID
NdisUpdateOffload(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

EXPORT
VOID
NdisQueryOffload(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

//
// Tcp specific offload functions supported by NDIS, for use by the protocol.
//
EXPORT
NDIS_STATUS
NdisOffloadTcpSend(
    IN PNDIS_OFFLOAD_HANDLE                  NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

EXPORT
NDIS_STATUS
NdisOffloadTcpReceive(
    IN PNDIS_OFFLOAD_HANDLE                  NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

EXPORT
NDIS_STATUS
NdisOffloadTcpDisconnect(
    IN PNDIS_OFFLOAD_HANDLE                  NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN ULONG                                 Flags
    );

EXPORT
NDIS_STATUS
NdisOffloadTcpForward(
    IN PNDIS_OFFLOAD_HANDLE                  NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

VOID
NdisOffloadTcpReceiveReturn(
    IN NDIS_HANDLE                           NdisBindingHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

#endif // defined(NDIS60) || defined(NDIS52)

EXPORT
NDIS_STATUS
NdisUnbindAdapter(
    IN  NDIS_HANDLE                     NdisBindingHandle
    );

#if (defined(NDIS60))

//
// structure passed to NdisOpenAdapterEx
//

#define NDIS_OPEN_PARAMETERS_REVISION_1     1
typedef struct _NDIS_OPEN_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
    PNDIS_STRING                AdapterName;
    PNDIS_MEDIUM                MediumArray;
    UINT                        MediumArraySize;
    PUINT                       SelectedMediumIndex;
    PNET_FRAME_TYPE             FrameTypeArray;
    UINT                        FrameTypeArraySize;
} NDIS_OPEN_PARAMETERS, *PNDIS_OPEN_PARAMETERS;

EXPORT
NDIS_STATUS
NdisOpenAdapterEx(
    IN  NDIS_HANDLE             NdisProtocolHandle,
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  PNDIS_OPEN_PARAMETERS   OpenParameters,
    OUT PNDIS_HANDLE            NdisBindingHandle
    );

EXPORT
VOID
NdisCompleteBindAdapterEx(
    IN  NDIS_HANDLE             BindAdapterContext,
    IN  NDIS_STATUS             Status
    );

EXPORT
NDIS_STATUS
NdisCloseAdapterEx(
    IN  NDIS_HANDLE             NdisBindingHandle
    );

EXPORT
VOID
NdisCompleteUnbindAdapterEx(
    IN  NDIS_HANDLE             UnbindContext
    );

EXPORT
NDIS_STATUS
NdisEnumerateBindingFilters(
    IN      NDIS_HANDLE     NdisBindingHandle,
    IN      PVOID           InformationBuffer,
    IN      ULONG           InformationBufferLength,
    IN OUT  PULONG          BytesNeeded,
    IN OUT  PULONG          BytesWritten
    );

#define NDIS_PROTOCOL_PAUSE_PARAMETERS_REVISION_1     1
    
typedef struct _NDIS_PROTOCOL_PAUSE_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
} NDIS_PROTOCOL_PAUSE_PARAMETERS, *PNDIS_PROTOCOL_PAUSE_PARAMETERS;

#define NDIS_PROTOCOL_RESTART_PARAMETERS_REVISION_1     1

typedef struct _NDIS_PROTOCOL_RESTART_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
} NDIS_PROTOCOL_RESTART_PARAMETERS, *PNDIS_PROTOCOL_RESTART_PARAMETERS;

#endif // defined(NDIS60)

#include <xfilter.h>

#define NDIS_M_MAX_LOOKAHEAD 526

#ifdef NDIS_WRAPPER
#define MAX_HASH_MAP_TABLE_SIZE     128
#define HASH_SECRET_KEY_SIZE        40
#define MAX_RSS_PARAMETERS_LENGTH   (sizeof(NDIS_RECEIVE_SCALE_PARAMETERS) + MAX_HASH_MAP_TABLE_SIZE + HASH_SECRET_KEY_SIZE)
#endif


//
// Function types for NDIS_MINIPORT_CHARACTERISTICS
//


typedef
BOOLEAN
(*W_CHECK_FOR_HANG_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
VOID
(*W_DISABLE_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
VOID
(*W_ENABLE_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
VOID
(*W_HALT_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
VOID
(*W_HANDLE_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
NDIS_STATUS
(*W_INITIALIZE_HANDLER)(
    OUT PNDIS_STATUS            OpenErrorStatus,
    OUT PUINT                   SelectedMediumIndex,
    IN  PNDIS_MEDIUM            MediumArray,
    IN  UINT                    MediumArraySize,
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             WrapperConfigurationContext
    );

typedef
VOID
(*W_ISR_HANDLER)(
    OUT PBOOLEAN                InterruptRecognized,
    OUT PBOOLEAN                QueueMiniportHandleInterrupt,
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
NDIS_STATUS
(*W_QUERY_INFORMATION_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_OID                Oid,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength,
    OUT PULONG                  BytesWritten,
    OUT PULONG                  BytesNeeded
    );

typedef
NDIS_STATUS
(*W_RECONFIGURE_HANDLER)(
    OUT PNDIS_STATUS            OpenErrorStatus,
    IN  NDIS_HANDLE             MiniportAdapterContext  OPTIONAL,
    IN  NDIS_HANDLE             WrapperConfigurationContext
    );

typedef
NDIS_STATUS
(*W_RESET_HANDLER)(
    OUT PBOOLEAN                AddressingReset,
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
NDIS_STATUS
(*W_SEND_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNDIS_PACKET            Packet,
    IN  UINT                    Flags
    );

typedef
NDIS_STATUS
(*WM_SEND_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             NdisLinkHandle,
    IN  PNDIS_WAN_PACKET        Packet
    );

typedef
NDIS_STATUS
(*W_SET_INFORMATION_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_OID                Oid,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength,
    OUT PULONG                  BytesRead,
    OUT PULONG                  BytesNeeded
    );

typedef
NDIS_STATUS
(*W_TRANSFER_DATA_HANDLER)(
    OUT PNDIS_PACKET            Packet,
    OUT PUINT                   BytesTransferred,
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             MiniportReceiveContext,
    IN  UINT                    ByteOffset,
    IN  UINT                    BytesToTransfer
    );

typedef
NDIS_STATUS
(*WM_TRANSFER_DATA_HANDLER)(
    VOID
    );

//
// Definition for shutdown handler
//

typedef
VOID
(*ADAPTER_SHUTDOWN_HANDLER) (
    IN  PVOID ShutdownContext
    );

typedef struct _NDIS30_MINIPORT_CHARACTERISTICS
{
    UCHAR                       MajorNdisVersion;
    UCHAR                       MinorNdisVersion;
    USHORT                      Filler;
    UINT                        Reserved;
    W_CHECK_FOR_HANG_HANDLER    CheckForHangHandler;
    W_DISABLE_INTERRUPT_HANDLER DisableInterruptHandler;
    W_ENABLE_INTERRUPT_HANDLER  EnableInterruptHandler;
    W_HALT_HANDLER              HaltHandler;
    W_HANDLE_INTERRUPT_HANDLER  HandleInterruptHandler;
    W_INITIALIZE_HANDLER        InitializeHandler;
    W_ISR_HANDLER               ISRHandler;
    W_QUERY_INFORMATION_HANDLER QueryInformationHandler;
    W_RECONFIGURE_HANDLER       ReconfigureHandler;
    W_RESET_HANDLER             ResetHandler;
    union
    {
        W_SEND_HANDLER          SendHandler;
        WM_SEND_HANDLER         WanSendHandler;
    };
    W_SET_INFORMATION_HANDLER   SetInformationHandler;
    union
    {
        W_TRANSFER_DATA_HANDLER TransferDataHandler;
        WM_TRANSFER_DATA_HANDLER WanTransferDataHandler;
    };
} NDIS30_MINIPORT_CHARACTERISTICS;

//
// Miniport extensions for NDIS 4.0
//
typedef
VOID
(*W_RETURN_PACKET_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNDIS_PACKET            Packet
    );

//
// NDIS 4.0 extension
//
typedef
VOID
(*W_SEND_PACKETS_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );

typedef
VOID
(*W_ALLOCATE_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PVOID                   VirtualAddress,
    IN  PNDIS_PHYSICAL_ADDRESS  PhysicalAddress,
    IN  ULONG                   Length,
    IN  PVOID                   Context
    );

typedef struct _NDIS40_MINIPORT_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS30_MINIPORT_CHARACTERISTICS Ndis30Chars;
#else
    NDIS30_MINIPORT_CHARACTERISTICS;
#endif
    //
    // Extensions for NDIS 4.0
    //
    W_RETURN_PACKET_HANDLER     ReturnPacketHandler;
    W_SEND_PACKETS_HANDLER      SendPacketsHandler;
    W_ALLOCATE_COMPLETE_HANDLER AllocateCompleteHandler;

} NDIS40_MINIPORT_CHARACTERISTICS;


//
// Miniport extensions for NDIS 5.0
//
//
// NDIS 5.0 extension - however available for miniports only
//

//
// W_CO_CREATE_VC_HANDLER is a synchronous call
//
typedef
NDIS_STATUS
(*W_CO_CREATE_VC_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             NdisVcHandle,
    OUT PNDIS_HANDLE            MiniportVcContext
    );

typedef
NDIS_STATUS
(*W_CO_DELETE_VC_HANDLER)(
    IN  NDIS_HANDLE             MiniportVcContext
    );

typedef
NDIS_STATUS
(*W_CO_ACTIVATE_VC_HANDLER)(
    IN  NDIS_HANDLE             MiniportVcContext,
    IN OUT PCO_CALL_PARAMETERS  CallParameters
    );

typedef
NDIS_STATUS
(*W_CO_DEACTIVATE_VC_HANDLER)(
    IN  NDIS_HANDLE             MiniportVcContext
    );

typedef
VOID
(*W_CO_SEND_PACKETS_HANDLER)(
    IN  NDIS_HANDLE             MiniportVcContext,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );

typedef
NDIS_STATUS
(*W_CO_REQUEST_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HANDLE             MiniportVcContext   OPTIONAL,
    IN OUT PNDIS_REQUEST        NdisRequest
    );

//
// CONDIS 6.0 handlers
//

typedef
VOID
(*W_CO_SEND_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             MiniportVcContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 bDispatch
    );

typedef 
NDIS_STATUS
(*W_CO_REQUEST_HANDLER_EX)(
    IN NDIS_HANDLE          MiniportAdapterContext,
    IN NDIS_HANDLE          MiniportVcContext OPTIONAL,
    IN OUT PNDIS_REQUEST_EX NdisRequest
    );

typedef 
NDIS_STATUS
(*W_CO_OID_REQUEST_HANDLER)(
    IN NDIS_HANDLE           MiniportAdapterContext,
    IN NDIS_HANDLE           MiniportVcContext OPTIONAL,
    IN OUT PNDIS_OID_REQUEST NdisRequest
    );


typedef struct _NDIS50_MINIPORT_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS40_MINIPORT_CHARACTERISTICS Ndis40Chars;
#else
    NDIS40_MINIPORT_CHARACTERISTICS;
#endif
    //
    // Extensions for NDIS 5.0
    //
    W_CO_CREATE_VC_HANDLER      CoCreateVcHandler;
    W_CO_DELETE_VC_HANDLER      CoDeleteVcHandler;
    W_CO_ACTIVATE_VC_HANDLER    CoActivateVcHandler;
    W_CO_DEACTIVATE_VC_HANDLER  CoDeactivateVcHandler;
    W_CO_SEND_PACKETS_HANDLER   CoSendPacketsHandler;
    W_CO_REQUEST_HANDLER        CoRequestHandler;
} NDIS50_MINIPORT_CHARACTERISTICS;

//
// Miniport extensions for NDIS 5.1
//
typedef VOID
(*W_CANCEL_SEND_PACKETS_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PVOID                   CancelId
    );

//
// power profiles
//
typedef enum _NDIS_POWER_PROFILE
{
    NdisPowerProfileBattery,
    NdisPowerProfileAcOnLine
} NDIS_POWER_PROFILE, *PNDIS_POWER_PROFILE;

typedef enum _NDIS_DEVICE_PNP_EVENT
{
    NdisDevicePnPEventQueryRemoved,
    NdisDevicePnPEventRemoved,
    NdisDevicePnPEventSurpriseRemoved,
    NdisDevicePnPEventQueryStopped,
    NdisDevicePnPEventStopped,
    NdisDevicePnPEventPowerProfileChanged,
    NdisDevicePnPEventFilterListChanged,
    NdisDevicePnPEventMaximum
} NDIS_DEVICE_PNP_EVENT, *PNDIS_DEVICE_PNP_EVENT;

typedef VOID
(*W_PNP_EVENT_NOTIFY_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_DEVICE_PNP_EVENT   DevicePnPEvent,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength
    );

typedef VOID
(*W_MINIPORT_SHUTDOWN_HANDLER) (
    IN  NDIS_HANDLE                     MiniportAdapterContext
    );

typedef
BOOLEAN
(*MINIPORT_ISR_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext,
    OUT PBOOLEAN                QueueDefaultInterruptDpc,
    OUT PULONG                  TargetProcessors
    );

typedef
VOID
(*MINIPORT_INTERRUPT_DPC_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext
    );

typedef
VOID
(*MINIPORT_DISABLE_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext
    );

typedef
VOID
(*MINIPORT_ENABLE_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext
    );

#if (defined(NDIS60) || defined(NDIS60_MINIPORT) || defined(NDIS52_MINIPORT) || defined(NDIS52))
//
// MSI support handlers
//
typedef
BOOLEAN
(*MINIPORT_MSI_ISR_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext,
    IN  ULONG                   MessageId,
    OUT PBOOLEAN                QueueDefaultInterruptDpc,
    OUT PULONG                  TargetProcessors
    );

typedef
VOID
(*MINIPORT_MSI_INTERRUPT_DPC_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext,
    IN  ULONG                   MessageId
    );


typedef
VOID
(*MINIPORT_DISABLE_MSI_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext,
    IN  ULONG                   MessageId
    );

typedef
VOID
(*MINIPORT_ENABLE_MSI_INTERRUPT_HANDLER)(
    IN  NDIS_HANDLE             MiniportInterruptContext,
    IN  ULONG                   MessageId
    );

typedef enum _NDIS_INTERRUPT_TYPE
{
    NDIS_CONNECT_LINE_BASED = 1,
    NDIS_CONNECT_MESSAGE_BASED
} NDIS_INTERRUPT_TYPE, *PNDIS_INTERRUPT_TYPE;
    
#define NDIS_MINIPORT_INTERRUPT_REVISION_1          1

typedef struct _NDIS_MINIPORT_INTERRUPT_CHARACTERISTICS
{
    IN NDIS_OBJECT_HEADER                      Header;
    IN MINIPORT_ISR_HANDLER                    InterruptHandler;
    IN MINIPORT_INTERRUPT_DPC_HANDLER          InterruptDpcHandler;
    IN MINIPORT_DISABLE_INTERRUPT_HANDLER      DisableInterruptHandler;
    IN MINIPORT_ENABLE_INTERRUPT_HANDLER       EnableInterruptHandler;
    IN BOOLEAN                                 SharedInterrupt;
    IN BOOLEAN                                 MsiSupported;
    IN BOOLEAN                                 MsiSyncWithAllMessages;
    IN MINIPORT_MSI_ISR_HANDLER                MessageInterruptHandler;
    IN MINIPORT_MSI_INTERRUPT_DPC_HANDLER      MessageInterruptDpcHandler;
    IN MINIPORT_DISABLE_MSI_INTERRUPT_HANDLER  DisableMessageInterruptHandler;
    IN MINIPORT_ENABLE_MSI_INTERRUPT_HANDLER   EnableMessageInterruptHandler;
    OUT PNDIS_INTERRUPT_TYPE                   InterruptType;
    OUT PIO_INTERRUPT_MESSAGE_INFO            *MessageInfoTable;
} NDIS_MINIPORT_INTERRUPT_CHARACTERISTICS, *PNDIS_MINIPORT_INTERRUPT_CHARACTERISTICS;


EXPORT
NDIS_STATUS
NdisMRegisterInterruptEx(
    IN  NDIS_HANDLE                                 MiniportAdapterHandle,
    IN  NDIS_HANDLE                                 MiniportInterruptContext,
    IN  PNDIS_MINIPORT_INTERRUPT_CHARACTERISTICS    MiniportInterruptCharacteristics,
    OUT PNDIS_HANDLE                                NdisInterruptHandle
    );



EXPORT
VOID
NdisMDeregisterInterruptEx(
    IN  NDIS_HANDLE                     NdisInterruptHandle
    );


EXPORT
BOOLEAN
NdisMSynchronizeWithInterruptEx(
    IN NDIS_HANDLE                      NdisInterruptHandle,
    IN ULONG                            MessageId,
    IN PVOID                            SynchronizeFunction,
    IN PVOID                            SynchronizeContext
    );
#endif

EXPORT
ULONG
NdisMQueueDpc(
    IN  NDIS_HANDLE     NdisInterruptHandle,
    IN  ULONG           TargetProcessors
    );


typedef struct _NDIS51_MINIPORT_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS50_MINIPORT_CHARACTERISTICS Ndis50Chars;
#else
    NDIS50_MINIPORT_CHARACTERISTICS;
#endif
    //
    // Extensions for NDIS 5.1
    //
    W_CANCEL_SEND_PACKETS_HANDLER   CancelSendPacketsHandler;
    W_PNP_EVENT_NOTIFY_HANDLER      PnPEventNotifyHandler;
    W_MINIPORT_SHUTDOWN_HANDLER     AdapterShutdownHandler;
#if NDIS_CHIMNEY_OFFLOAD
#if (NDIS52_MINIPORT)
    //
    // this is to allow 5.2 miniports to do RSS
    //
    MINIPORT_ISR_HANDLER            MiniportISRHandler;
    MINIPORT_INTERRUPT_DPC_HANDLER  InterruptDpcHandler;
#else
    PVOID                           Reserved1;
    PVOID                           Reserved2;
#endif
#else
    PVOID                           Reserved1;
    PVOID                           Reserved2;
#endif // NDIS_CHIMNEY_OFFLOAD
    PVOID                           Reserved3;
    PVOID                           Reserved4;
} NDIS51_MINIPORT_CHARACTERISTICS;


#if NDIS_CHIMNEY_OFFLOAD

typedef struct _NDIS_MINIPORT_OFFLOAD_BLOCK_LIST {
    IN NDIS_OBJECT_HEADER Header;
    IN struct _NDIS_MINIPORT_OFFLOAD_BLOCK_LIST *NextBlock;
    IN struct _NDIS_MINIPORT_OFFLOAD_BLOCK_LIST *DependentBlockList;
    OUT NDIS_STATUS Status;
    IN PVOID NdisReserved[2];
    IN OUT PVOID *MiniportOffloadContext;
    IN NDIS_HANDLE NdisOffloadHandle;
    IN PVOID ProtocolReserved[2];
    IN PVOID MiniportReserved[2];
    IN PVOID ImReserved[2];
    IN PVOID Scratch[2];
    IN PVOID SourceHandle;
    IN OUT PNET_BUFFER_LIST NetBufferListChain;
    //
    // The state specific information (if any) will follow this.
    //
} NDIS_MINIPORT_OFFLOAD_BLOCK_LIST, *PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST;

//
// Generic offload functions supported by the miniport.
//
typedef
VOID
(*W_INITIATE_OFFLOAD_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

typedef
VOID
(*W_TERMINATE_OFFLOAD_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

typedef
VOID
(*W_INVALIDATE_OFFLOAD_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

typedef
VOID
(*W_UPDATE_OFFLOAD_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

typedef
VOID
(*W_QUERY_OFFLOAD_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN OUT PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST OffloadBlockList
    );

//
// Tcp specific offload functions supported by the miniport.
//
typedef
NDIS_STATUS
(*W_TCP_OFFLOAD_SEND_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 MiniportOffloadContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
NDIS_STATUS
(*W_TCP_OFFLOAD_RECEIVE_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 MiniportOffloadContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
NDIS_STATUS
(*W_TCP_OFFLOAD_DISCONNECT_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 MiniportOffloadContext,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN ULONG                                        Flags
   );

typedef
NDIS_STATUS
(*W_TCP_OFFLOAD_FORWARD_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PVOID                                 MiniportOffloadContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );


typedef
NDIS_STATUS
(*W_TCP_OFFLOAD_RECEIVE_RETURN_HANDLER)(
    IN NDIS_HANDLE                           MiniportAdapterContext,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef struct _NDIS52_MINIPORT_CHARACTERISTICS
{
#ifdef __cplusplus
    NDIS51_MINIPORT_CHARACTERISTICS Ndis51Chars;
#else
    NDIS51_MINIPORT_CHARACTERISTICS;
#endif
    //
    // Generic Offload initiation and termination handlers.
    //
    W_INITIATE_OFFLOAD_HANDLER               InitiateOffloadHandler;
    W_TERMINATE_OFFLOAD_HANDLER              TerminateOffloadHandler;

    //
    // Generic offload state control functions.
    //
    W_UPDATE_OFFLOAD_HANDLER                 UpdateOffloadHandler;
    W_INVALIDATE_OFFLOAD_HANDLER             InvalidateOffloadHandler;
    W_QUERY_OFFLOAD_HANDLER                  QueryOffloadHandler;

    //
    // TCP function handlers
    //
    W_TCP_OFFLOAD_SEND_HANDLER               TcpOffloadSendHandler;
    W_TCP_OFFLOAD_RECEIVE_HANDLER            TcpOffloadReceiveHandler;
    W_TCP_OFFLOAD_DISCONNECT_HANDLER         TcpOffloadDisconnectHandler;
    W_TCP_OFFLOAD_FORWARD_HANDLER            TcpOffloadForwardHandler;

    //
    // Receive return handler.
    //
    W_TCP_OFFLOAD_RECEIVE_RETURN_HANDLER     TcpOffloadReceiveReturnHandler;

} NDIS52_MINIPORT_CHARACTERISTICS;

#endif // NDIS_CHIMNEY_OFFLOAD

typedef struct _NDIS_MINIPORT_INTERRUPT
{
    PKINTERRUPT                 InterruptObject;
    KSPIN_LOCK                  DpcCountLock;
    PVOID                       Reserved;
    W_ISR_HANDLER               MiniportIsr;
    W_HANDLE_INTERRUPT_HANDLER  MiniportDpc;
    KDPC                        InterruptDpc;
    PNDIS_MINIPORT_BLOCK        Miniport;

    UCHAR                       DpcCount;
    BOOLEAN                     Filler1;

    //
    // This is used to tell when all the Dpcs for the adapter are completed.
    //

    KEVENT                      DpcsCompletedEvent;

    BOOLEAN                     SharedInterrupt;
    BOOLEAN                     IsrRequested;

} NDIS_MINIPORT_INTERRUPT, *PNDIS_MINIPORT_INTERRUPT;

typedef struct _NDIS_MINIPORT_TIMER
{
    KTIMER                      Timer;
    KDPC                        Dpc;
    PNDIS_TIMER_FUNCTION        MiniportTimerFunction;
    PVOID                       MiniportTimerContext;
    PNDIS_MINIPORT_BLOCK        Miniport;
    struct _NDIS_MINIPORT_TIMER *NextTimer;
} NDIS_MINIPORT_TIMER, *PNDIS_MINIPORT_TIMER;

typedef
VOID
(*ETH_RCV_INDICATE_HANDLER)(
    IN  PETH_FILTER             Filter,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  PCHAR                   Address,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookaheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize
    );

typedef
VOID
(*ETH_RCV_COMPLETE_HANDLER)(
    IN  PETH_FILTER             Filter
    );

typedef
VOID
(*TR_RCV_INDICATE_HANDLER)(
    IN  PTR_FILTER              Filter,
    IN  NDIS_HANDLE             MacReceiveContext,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookaheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize
    );

typedef
VOID
(*TR_RCV_COMPLETE_HANDLER)(
    IN  PTR_FILTER              Filter
    );

typedef
VOID
(*WAN_RCV_HANDLER)(
    OUT PNDIS_STATUS            Status,
    IN NDIS_HANDLE              MiniportAdapterHandle,
    IN NDIS_HANDLE              NdisLinkContext,
    IN PUCHAR                   Packet,
    IN ULONG                    PacketSize
    );

typedef
VOID
(*WAN_RCV_COMPLETE_HANDLER)(
    IN NDIS_HANDLE              MiniportAdapterHandle,
    IN NDIS_HANDLE              NdisLinkContext
    );

typedef
VOID
(*NDIS_M_SEND_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_PACKET            Packet,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*NDIS_WM_SEND_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PVOID                   Packet,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*NDIS_M_TD_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_PACKET            Packet,
    IN  NDIS_STATUS             Status,
    IN  UINT                    BytesTransferred
    );

typedef
VOID
(*NDIS_M_SEND_RESOURCES_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle
    );

typedef
VOID
(*NDIS_M_STATUS_HANDLER)(
    IN  NDIS_HANDLE             MiniportHandle,
    IN  NDIS_STATUS             GeneralStatus,
    IN  PVOID                   StatusBuffer,
    IN  UINT                    StatusBufferSize
    );

typedef
VOID
(*NDIS_M_STS_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle
    );

typedef
VOID
(*NDIS_M_REQ_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_STATUS             Status
    );

typedef
VOID
(*NDIS_M_RESET_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_STATUS             Status,
    IN  BOOLEAN                 AddressingReset
    );

typedef
BOOLEAN
(FASTCALL *NDIS_M_START_SENDS)(
    IN  PNDIS_MINIPORT_BLOCK    Miniport
    );

//
//  Defines the type of work item.
//
typedef enum _NDIS_WORK_ITEM_TYPE
{
    NdisWorkItemRequest,
    NdisWorkItemSend,
    NdisWorkItemReturnPackets,
    NdisWorkItemResetRequested,
    NdisWorkItemResetInProgress,
    NdisWorkItemReserved,
    NdisWorkItemMiniportCallback,
    NdisMaxWorkItems
} NDIS_WORK_ITEM_TYPE, *PNDIS_WORK_ITEM_TYPE;


#define NUMBER_OF_WORK_ITEM_TYPES   NdisMaxWorkItems
#define NUMBER_OF_SINGLE_WORK_ITEMS 6

//
//  Work item structure
//
typedef struct _NDIS_MINIPORT_WORK_ITEM
{
    //
    //  Link for the list of work items of this type.
    //
    SINGLE_LIST_ENTRY   Link;

    //
    //  type of work item and context information.
    //
    NDIS_WORK_ITEM_TYPE WorkItemType;
    PVOID               WorkItemContext;
} NDIS_MINIPORT_WORK_ITEM, *PNDIS_MINIPORT_WORK_ITEM;


#if defined(NDIS_WRAPPER)

//
// Structure used by the logging apis
//
typedef struct _NDIS_LOG
{
    PNDIS_MINIPORT_BLOCK        Miniport;   // The owning miniport block
    KSPIN_LOCK                  LogLock;    // For serialization
    PIRP                        Irp;        // Pending Irp to consume this log
    UINT                        TotalSize;  // Size of the log buffer
    UINT                        CurrentSize;// Size of the log buffer
    UINT                        InPtr;      // IN part of the circular buffer
    UINT                        OutPtr;     // OUT part of the circular buffer
    UCHAR                       LogBuf[1];  // The circular buffer
} NDIS_LOG, *PNDIS_LOG;

#endif

typedef struct _NDIS_BIND_PATHS
{
    UINT                        Number;
    NDIS_STRING                 Paths[1];
} NDIS_BIND_PATHS, *PNDIS_BIND_PATHS;

typedef
VOID
(*MINIPORT_PROCESS_SG_LIST_HANDLER)(
    IN  PDEVICE_OBJECT          pDO,
    IN  PVOID                   Reserved,
    IN  PSCATTER_GATHER_LIST    pSGL,
    IN  PVOID                   Context
    );

//
// NDIS DMA description structure
//

typedef
VOID
(*MINIPORT_ALLOCATE_SHARED_MEM_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PVOID                   VirtualAddress,
    IN  PNDIS_PHYSICAL_ADDRESS  PhysicalAddress,
    IN  ULONG                   Length,
    IN  PVOID                   Context
    );

/*
NDIS_STATUS
NdisMAllocateSharedMemoryAsyncEx(
    IN  NDIS_HANDLE             MiniportDmaHandle,
    IN  ULONG                   Length,
    IN  BOOLEAN                 Cached,
    IN  PVOID                   Context
    );
*/
#define NdisMAllocateSharedMemoryAsyncEx(_H, _L, _C, _X) NdisMAllocateSharedMemoryAsync(_H, _L, _C, _X)


//
// NDIS DMA description structure
//


//
// Flags used in NDIS_SG_DMA_DESCRIPTION
//

#define NDIS_SG_DMA_64_BIT_ADDRESS      0x00000001

//
// supported revision
//
#define NDIS_SG_DMA_DESCRIPTION_REVISION_1      1

typedef struct _NDIS_SG_DMA_DESCRIPTION
{
    NDIS_OBJECT_HEADER                              Header;
    ULONG                                           Flags;
    ULONG                                           MaximumPhysicalMapping;
    MINIPORT_PROCESS_SG_LIST_HANDLER                ProcessSGListHandler;
    MINIPORT_ALLOCATE_SHARED_MEM_COMPLETE_HANDLER   SharedMemAllocateCompleteHandler;
    ULONG                                           ScatterGatherListSize;
} NDIS_SG_DMA_DESCRIPTION, *PNDIS_SG_DMA_DESCRIPTION;


//BUGBUG6 #if (NDIS60_MINIPORT)


#define NDIS_MINIPORT_INIT_PARAMETERS_REVISION_1     1

//
// NDIS 6.0 miniport's entry points
//


typedef struct _NDIS_MINIPORT_INIT_PARAMETERS
{
    IN  NDIS_OBJECT_HEADER              Header;
    IN  ULONG                           Flags;
    IN  PNDIS_RESOURCE_LIST             AllocatedResources;
    IN  NDIS_HANDLE                     IMDeviceInstanceContext;
} NDIS_MINIPORT_INIT_PARAMETERS, *PNDIS_MINIPORT_INIT_PARAMETERS;



#define NDIS_MINIPORT_RESTART_PARAMETERS_REVISION_1     1

typedef struct _NDIS_MINIPORT_RESTART_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
    NET_IFINDEX                 IfIndex;
    NET_LUID                    NetLuid;
} NDIS_MINIPORT_RESTART_PARAMETERS, *PNDIS_MINIPORT_RESTART_PARAMETERS;


#define NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES_REVISION_1     1

typedef struct _NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES
{
    NDIS_OBJECT_HEADER              Header;
    NDIS_HANDLE                     MiniportAdapterContext;
    ULONG                           AttributeFlags;
    UINT                            CheckForHangTimeInSeconds;
    NDIS_INTERFACE_TYPE             InterfaceType;
} NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES, *PNDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES;


//
// flags used in NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES->SupportedStatistics
//

#define NDIS_STATISTICS_XMIT_OK_SUPPORTED                       0x00000001
#define NDIS_STATISTICS_RCV_OK_SUPPORTED                        0x00000002 
#define NDIS_STATISTICS_XMIT_ERROR_SUPPORTED                    0x00000004 
#define NDIS_STATISTICS_RCV_ERROR_SUPPORTED                     0x00000008 
#define NDIS_STATISTICS_RCV_NO_BUFFER_SUPPORTED                 0x00000010 
#define NDIS_STATISTICS_DIRECTED_BYTES_XMIT_SUPPORTED           0x00000020 
#define NDIS_STATISTICS_DIRECTED_FRAMES_XMIT_SUPPORTED          0x00000040 
#define NDIS_STATISTICS_MULTICAST_BYTES_XMIT_SUPPORTED          0x00000080 
#define NDIS_STATISTICS_MULTICAST_FRAMES_XMIT_SUPPORTED         0x00000100 
#define NDIS_STATISTICS_BROADCAST_BYTES_XMIT_SUPPORTED          0x00000200 
#define NDIS_STATISTICS_BROADCAST_FRAMES_XMIT_SUPPORTED         0x00000400 
#define NDIS_STATISTICS_DIRECTED_BYTES_RCV_SUPPORTED            0x00000800 
#define NDIS_STATISTICS_DIRECTED_FRAMES_RCV_SUPPORTED           0x00001000 
#define NDIS_STATISTICS_MULTICAST_BYTES_RCV_SUPPORTED           0x00002000 
#define NDIS_STATISTICS_MULTICAST_FRAMES_RCV_SUPPORTED          0x00004000 
#define NDIS_STATISTICS_BROADCAST_BYTES_RCV_SUPPORTED           0x00008000 
#define NDIS_STATISTICS_BROADCAST_FRAMES_RCV_SUPPORTED          0x00010000 
#define NDIS_STATISTICS_RCV_CRC_ERROR_SUPPORTED                 0x00020000 
#define NDIS_STATISTICS_TRANSMIT_QUEUE_LENGTH_SUPPORTED         0x00040000 
#define NDIS_STATISTICS_BYTES_RCV_SUPPORTED                     0x00080000 
#define NDIS_STATISTICS_BYTES_XMIT_SUPPORTED                    0x00100000 
#define NDIS_STATISTICS_RCV_DISCARDS_SUPPORTED                  0x00200000 
#define NDIS_STATISTICS_GEN_STATISTICS_SUPPORTED                0x00400000




#define NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES_REVISION_1     1

typedef struct _NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES
{
    NDIS_OBJECT_HEADER              Header;
    ULONG                           Flags;
    NDIS_MEDIUM                     MediaType;
    NDIS_PHYSICAL_MEDIUM            PhysicalMediumType;
    ULONG                           MtuSize;
    ULONG64                         MaxXmitLinkSpeed;
    ULONG64                         XmitLinkSpeed;
    ULONG64                         MaxRcvLinkSpeed;
    ULONG64                         RcvLinkSpeed;
    NDIS_MEDIA_CONNECT_STATE        MediaConnectState;
    NDIS_MEDIA_DUPLEX_STATE         MediaDuplexState;
    ULONG                           LookaheadSize;
    PNDIS_PNP_CAPABILITIES          PowerManagementCapabilities;
    ULONG                           MacOptions;
    ULONG                           SupportedPacketFilters;
    ULONG                           MaxMulticastListSize;
    USHORT                          MacAddressLength;
    UCHAR                           PermanentMacAddress[NDIS_MAX_PHYS_ADDRESS_LENGTH];
    UCHAR                           CurrentMacAddress[NDIS_MAX_PHYS_ADDRESS_LENGTH];
    PNDIS_RECEIVE_SCALE_CAPABILITIES RecvScaleCapabilities;
    NET_IF_ACCESS_TYPE              AccessType; // NET_IF_ACCESS_BROADCAST for a typical ethernet adapter
    NET_IF_DIRECTION_TYPE           DirectionType; // NET_IF_DIRECTION_SENDRECEIVE for a typical ethernet adapter
    NET_IF_CONNECTION_TYPE          ConnectionType; // IF_CONNECTION_DEDICATED for a typical ethernet adapter
    NET_IFTYPE                      IfType; // IF_TYPE_ETHERNET_CSMACD for a typical ethernet adapter (regardless of speed)
    BOOLEAN                         IfConnectorPresent; // RFC 2665 TRUE if physical adapter
    ULONG                           SupportedStatistics; // use NDIS_STATISTICS_XXXX_SUPPORTED    
    ULONG                           SupportedPauseFunctions; // IEEE 802.3 37.2.1
} NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES, *PNDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES;


#define NDIS_MINIPORT_ADAPTER_OFFLOAD_ATTRIBUTES_REVISION_1     1

typedef struct _NDIS_MINIPORT_ADAPTER_OFFLOAD_ATTRIBUTES
{
    NDIS_OBJECT_HEADER              Header;
    NDIS_TASK_OFFLOAD_HEADER        TaskOffloadHeader;
    NDIS_TASK_OFFLOAD               TaskOffload[1];
} NDIS_MINIPORT_ADAPTER_OFFLOAD_ATTRIBUTES, *PNDIS_MINIPORT_ADAPTER_OFFLOAD_ATTRIBUTES;


#define NDIS_MINIPORT_ADAPTER_802_11_ATTRIBUTES_REVISION_1     1

typedef struct _NDIS_MINIPORT_ADAPTER_NATIVE_802_11_ATTRIBUTES
{
    NDIS_OBJECT_HEADER              Header;
    // TBD
        
} NDIS_MINIPORT_ADAPTER_NATIVE_802_11_ATTRIBUTES, *PNDIS_MINIPORT_ADAPTER_NATIVE_802_11_ATTRIBUTES;


typedef union _NDIS_MINIPORT_ADAPTER_ATTRIBUTES
{
    NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES   RegistrationAttributes;
    NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES        GenericAttributes;
    NDIS_MINIPORT_ADAPTER_OFFLOAD_ATTRIBUTES        OffloadAttributes;
    NDIS_MINIPORT_ADAPTER_NATIVE_802_11_ATTRIBUTES  Native_802_11_Attributes;
} NDIS_MINIPORT_ADAPTER_ATTRIBUTES, *PNDIS_MINIPORT_ADAPTER_ATTRIBUTES;


//
// flags used in NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES
//

#define NDIS_MINIPORT_ATTRIBUTES_HARDWARE_DEVICE            0x00000001
#define NDIS_MINIPORT_ATTRIBUTES_NDIS_WDM                   0x00000002
#define NDIS_MINIPORT_ATTRIBUTES_SURPRISE_REMOVE_OK         0x00000004
#define NDIS_MINIPORT_ATTRIBUTES_NOT_CO_NDIS                0x00000008
#define NDIS_MINIPORT_ATTRIBUTES_DO_NOT_BIND_TO_ALL_CO      0x00000010
#define NDIS_MINIPORT_ATTRIBUTES_NO_HALT_ON_SUSPEND         0x00000020
#define NDIS_MINIPORT_ATTRIBUTES_BUS_MASTER                 0x00000040
#define NDIS_MINIPORT_CREATES_DEFAULT_PORT                  0x00000080



EXPORT
NDIS_STATUS
NdisMSetMiniportAttributes(
    IN  NDIS_HANDLE                             NdisMiniportHandle,
    IN  PNDIS_MINIPORT_ADAPTER_ATTRIBUTES       MiniportAttributes
    );

typedef
NDIS_STATUS
(*MINIPORT_INITIALIZE_HANDLER)(
    IN  NDIS_HANDLE                         NdisMiniportHandle,
    IN  NDIS_HANDLE                         MiniportDriverContext,
    IN  PNDIS_MINIPORT_INIT_PARAMETERS      MiniportInitParameters
    );

typedef enum _NDIS_HALT_ACTION
{
    NdisHaltDeviceDisabled,
    NdisHaltDeviceInstanceDeInitialized,
    NdisHaltDevicePoweredDown,
    NdisHaltDeviceSurpriseRemoved,
    NdisHaltDeviceFailed,
    NdisHaltDeviceInitializationFailed,
    NdisHaltDeviceStopped
} NDIS_HALT_ACTION, *PNDIS_HALT_ACTION;

typedef
VOID
(*MINIPORT_HALT_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HALT_ACTION        HaltAction
    );

#define NDIS_MINIPORT_PAUSE_PARAMETERS_REVISION_1     1

typedef struct _NDIS_MINIPORT_PAUSE_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
} NDIS_MINIPORT_PAUSE_PARAMETERS, *PNDIS_MINIPORT_PAUSE_PARAMETERS;


typedef
NDIS_STATUS
(*MINIPORT_PAUSE_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNDIS_MINIPORT_PAUSE_PARAMETERS   PauseParameters
    );

typedef
NDIS_STATUS
(*MINIPORT_RESTART_HANDLER)(
    IN  NDIS_HANDLE                             MiniportAdapterContext,
    IN  PNDIS_MINIPORT_RESTART_PARAMETERS       RestartParameters
    );

typedef
NDIS_STATUS
(*MINIPORT_REQUEST_HANDLER) (
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PNDIS_REQUEST_EX        NdisRequest
    );

typedef
VOID
(*MINIPORT_DRIVER_UNLOAD) (
    IN PDRIVER_OBJECT           DriverObject
    );

//
// reasons for calling shutdown handler
//
typedef enum _NDIS_SHUTDOWN_ACTION {
    NdisShutdownPowerOff,
    NdisShutdownBugCheck
} NDIS_SHUTDOWN_ACTION, PNDIS_SHUTDOWN_ACTION;

typedef
VOID
(*MINIPORT_SHUTDOWN_HANDLER) (
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_SHUTDOWN_ACTION    ShutdownAction
    );

typedef
VOID
(*MINIPORT_PNP_EVENT_NOTIFY_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_DEVICE_PNP_EVENT   DevicePnPEvent,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength
    );

typedef
VOID
(*MINIPORT_CANCEL_SEND_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PVOID                   CancelId
    );


typedef
BOOLEAN
(*MINIPORT_CHECK_FOR_HANG_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext
    );

typedef
NDIS_STATUS
(*MINIPORT_RESET_HANDLER)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    OUT PBOOLEAN                AddressingReset
    );

typedef
VOID
(*MINIPORT_CANCEL_REQUEST_HANDLER)(
    IN NDIS_HANDLE              MiniportAdapterContext,
    IN PNDIS_REQUEST_EX         NdisRequest
    );

typedef struct _NDIS_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER  Header;                 // Header.Type = NDIS_OBJECT_TYPE_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS
    ULONG                                    Flags;

    //
    // Generic Offload initiation and termination handlers.
    //
    W_INITIATE_OFFLOAD_HANDLER               InitiateOffloadHandler;
    W_TERMINATE_OFFLOAD_HANDLER              TerminateOffloadHandler;

    //
    // Generic offload state control functions.
    //
    W_UPDATE_OFFLOAD_HANDLER                 UpdateOffloadHandler;
    W_INVALIDATE_OFFLOAD_HANDLER             InvalidateOffloadHandler;
    W_QUERY_OFFLOAD_HANDLER                  QueryOffloadHandler;

} NDIS_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS, *PNDIS_PROVIDER_CHIMNEY_OFFLOAD_GENERIC_CHARACTERISTICS;

typedef struct _NDIS_PROVIDER_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER  Header;                 // Header.Type = NDIS_OBJECT_TYPE_PROVIDER_CHIMNEY_OFFLOAD_CHARACTERISTICS
    ULONG                                    Flags;
    NDIS_CHIMNEY_OFFLOAD_TYPE                OffloadType;    // NdisTcpChimneyOffload
    //
    // TCP function handlers
    //
    W_TCP_OFFLOAD_SEND_HANDLER               TcpOffloadSendHandler;
    W_TCP_OFFLOAD_RECEIVE_HANDLER            TcpOffloadReceiveHandler;
    W_TCP_OFFLOAD_DISCONNECT_HANDLER         TcpOffloadDisconnectHandler;
    W_TCP_OFFLOAD_FORWARD_HANDLER            TcpOffloadForwardHandler;

    //
    // Receive return handler.
    //
    W_TCP_OFFLOAD_RECEIVE_RETURN_HANDLER     TcpOffloadReceiveReturnHandler;

} NDIS_PROVIDER_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS, *PNDIS_PROVIDER_CHIMNEY_OFFLOAD_TCP_CHARACTERISTICS;



//
// flags used in Flags field of NDIS60_MINIPORT_CHARACTERISTICS
//
#define NDIS_INTERMEDIATE_DRIVER                0x00000001
#define NDIS_WDM_DRIVER                         0x00000002


#define NDIS_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_1     1

typedef struct _NDIS_MINIPORT_DRIVER_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                          Header;
    UCHAR                                       MajorNdisVersion;
    UCHAR                                       MinorNdisVersion;
    UCHAR                                       MajorDriverVersion;
    UCHAR                                       MinorDriverVersion;
    ULONG                                       Flags;
    SET_OPTIONS_HANDLER                         SetOptionsHandler;
    MINIPORT_INITIALIZE_HANDLER                 InitializeHandlerEx;
    MINIPORT_HALT_HANDLER                       HaltHandlerEx;
    MINIPORT_DRIVER_UNLOAD                      UnloadHandler;
    MINIPORT_PAUSE_HANDLER                      PauseHandler;
    MINIPORT_RESTART_HANDLER                    RestartHandler;
    MINIPORT_REQUEST_HANDLER                    RequestHandler;
    MINIPORT_SEND_NET_BUFFER_LISTS_HANDLER      SendNetBufferListsHandler;
    MINIPORT_RETURN_NET_BUFFER_LISTS_HANDLER    ReturnNetBufferListsHandler;
    MINIPORT_CANCEL_SEND_HANDLER                CancelSendHandler;
    MINIPORT_CHECK_FOR_HANG_HANDLER             CheckForHangHandlerEx;
    MINIPORT_RESET_HANDLER                      ResetHandlerEx;
    MINIPORT_PNP_EVENT_NOTIFY_HANDLER           PnPEventNotifyHandlerEx;
    MINIPORT_SHUTDOWN_HANDLER                   ShutdownHandlerEx;
    MINIPORT_CANCEL_REQUEST_HANDLER             CancelRequestHandler;
} NDIS_MINIPORT_DRIVER_CHARACTERISTICS, *PNDIS_MINIPORT_DRIVER_CHARACTERISTICS;

//
// CO NDIS 6.0 handlers
//

#define NDIS_MINIPORT_CO_CHARACTERISTICS_REVISION_1      1

typedef struct _NDIS_MINIPORT_CO_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                          Header;     // Header.Type = NDIS_OBJECT_TYPE_PROTOCOL_CO_CHARACTERISTICS
    ULONG                                       Flags;
    W_CO_CREATE_VC_HANDLER                      CoCreateVcHandler;
    W_CO_DELETE_VC_HANDLER                      CoDeleteVcHandler;
    W_CO_ACTIVATE_VC_HANDLER                    CoActivateVcHandler;
    W_CO_DEACTIVATE_VC_HANDLER                  CoDeactivateVcHandler;
    W_CO_SEND_NET_BUFFER_LISTS_HANDLER          CoSendNetBufferListsHandler;
    union 
    {
        W_CO_OID_REQUEST_HANDLER                    CoOidRequestHandler;
        W_CO_REQUEST_HANDLER_EX                     CoRequestHandlerEx;
    };
} NDIS_MINIPORT_CO_CHARACTERISTICS, *PNDIS_MINIPORT_CO_CHARACTERISTICS;



//BUGBUG6 #endif // NDIS60_MINIPORT



#if NDIS_CHIMNEY_OFFLOAD


#if (defined(NDIS60_MINIPORT) || defined(NDIS52_MINIPORT))
typedef struct _NDIS52_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
#ifdef NDIS51_MINIPORT
typedef struct _NDIS51_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
#ifdef NDIS50_MINIPORT
typedef struct _NDIS50_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
#ifdef NDIS40_MINIPORT
typedef struct _NDIS40_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
typedef struct _NDIS30_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#endif
#endif
#endif
#endif

#else

#if (defined(NDIS60_MINIPORT) || defined(NDIS51_MINIPORT))
typedef struct _NDIS51_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
#ifdef NDIS50_MINIPORT
typedef struct _NDIS50_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
#ifdef NDIS40_MINIPORT
typedef struct _NDIS40_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#else
typedef struct _NDIS30_MINIPORT_CHARACTERISTICS NDIS_MINIPORT_CHARACTERISTICS;
#endif
#endif
#endif

#endif // NDIS_CHIMNEY_OFFLOAD

typedef NDIS_MINIPORT_CHARACTERISTICS * PNDIS_MINIPORT_CHARACTERISTICS;
typedef NDIS_MINIPORT_CHARACTERISTICS   NDIS_WAN_MINIPORT_CHARACTERISTICS;
typedef NDIS_WAN_MINIPORT_CHARACTERISTICS * PNDIS_MINIPORT_CHARACTERISTICS;

typedef struct _NDIS_SG_DMA_BLOCK   NDIS_SG_DMA_BLOCK, *PNDIS_SG_DMA_BLOCK;

//
// Do not change the structure below !!!
//
typedef struct
{
    union
    {
        PETH_FILTER             EthDB;
        PNULL_FILTER            NullDB;             // Default Filter
    };
    PTR_FILTER                  TrDB;

    PVOID                       YYYDB;

    PVOID                       XXXDB;
} FILTERDBS, *PFILTERDBS;

typedef
VOID
(*FILTER_PACKET_INDICATION_HANDLER)(
    IN  NDIS_HANDLE             Miniport,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );



#if !NDIS_WRAPPER
//
// one of these per mini-port registered on a Driver
//


struct _NDIS_MINIPORT_BLOCK
{
    NDIS_OBJECT_HEADER          Header;
    PNDIS_MINIPORT_BLOCK        NextMiniport;       // used by driver's MiniportQueue
    PNDIS_MINIPORT_BLOCK        BaseMiniport;
    NDIS_HANDLE                 MiniportAdapterContext; // context when calling mini-port functions
    UNICODE_STRING              Reserved4;
    PNDIS_BIND_PATHS            Reserved10;
    NDIS_HANDLE                 OpenQueue;          // queue of opens for this mini-port
    REFERENCE                   ShortRef;           // contains spinlock for OpenQueue

    NDIS_HANDLE                 Reserved12;

    UCHAR                       Padding1;           // DO NOT REMOVE OR NDIS WILL BREAK!!!

    //
    // Synchronization stuff.
    //
    // The boolean is used to lock out several DPCs from running at the same time.
    //
    UCHAR                       LockAcquired;       // EXPOSED via macros. Do not move

    UCHAR                       PmodeOpens;         // Count of opens which turned on pmode/all_local

    //
    //  This is the processor number that the miniport's
    //  interrupt DPC and timers are running on.
    //
    UCHAR                       AssignedProcessor;

    KSPIN_LOCK                  Lock;

    PNDIS_REQUEST               MediaRequest;

    PNDIS_MINIPORT_INTERRUPT                    Interrupt;
    
    ULONG                       Flags;              // Flags to keep track of the miniport's state.
    ULONG                       PnPFlags;

    //
    // Send information
    //
    LIST_ENTRY                  PacketList;
    PNDIS_PACKET                FirstPendingPacket; // This is head of the queue of packets
                                                    // waiting to be sent to miniport.
    PNDIS_PACKET                ReturnPacketsQueue;

    //
    // Space used for temp. use during request processing
    //
    ULONG                       RequestBuffer;
    PVOID                       SetMCastBuffer;

    PNDIS_MINIPORT_BLOCK        PrimaryMiniport;
    PVOID                       Reserved11;

    //
    // context to pass to bus driver when reading or writing config space
    //
    PVOID                       BusDataContext;
    ULONG                       Reserved3;

    //
    // Resource information
    //
    PCM_RESOURCE_LIST           Resources;

    //
    // Watch-dog timer
    //
    NDIS_TIMER                  WakeUpDpcTimer;

    //
    // Needed for PnP. Upcased version. The buffer is allocated as part of the
    // NDIS_MINIPORT_BLOCK itself.
    //
    // Note:
    // the following two fields should be explicitly UNICODE_STRING because
    // under Win9x the NDIS_STRING is an ANSI_STRING
    //
    UNICODE_STRING              Reserved20;
    UNICODE_STRING              SymbolicLinkName;

    //
    // Check for hang stuff
    //
    ULONG                       CheckForHangSeconds;
    USHORT                      CFHangTicks;
    USHORT                      CFHangCurrentTick;

    //
    // Reset information
    //
    NDIS_STATUS                 ResetStatus;
    NDIS_HANDLE                 ResetOpen;

    //
    // Holds media specific information.
    //
#ifdef __cplusplus
    FILTERDBS                   FilterDbs;          // EXPOSED via macros. Do not move
#else
    FILTERDBS;                                      // EXPOSED via macros. Do not move
#endif

    FILTER_PACKET_INDICATION_HANDLER PacketIndicateHandler;
    NDIS_M_SEND_COMPLETE_HANDLER    SendCompleteHandler;
    NDIS_M_SEND_RESOURCES_HANDLER   SendResourcesHandler;
    NDIS_M_RESET_COMPLETE_HANDLER   ResetCompleteHandler;

    NDIS_MEDIUM                 MediaType;

    //
    // contains mini-port information
    //
    ULONG                       BusNumber;
    NDIS_INTERFACE_TYPE         BusType;
    NDIS_INTERFACE_TYPE         AdapterType;

    PDEVICE_OBJECT              Reserved6;
    PDEVICE_OBJECT              Reserved7;
    PDEVICE_OBJECT              Reserved8;


    PNDIS_SG_DMA_BLOCK          MiniportSGDmaBlock;

    //
    // List of registered address families. Valid for the call-manager, Null for the client
    //
    PNDIS_AF_LIST               CallMgrAfList;

    PVOID                       MiniportThread;
    PVOID                       SetInfoBuf;
    USHORT                      SetInfoBufLen;
    USHORT                      MaxSendPackets;

    //
    //  Status code that is returned from the fake handlers.
    //
    NDIS_STATUS                 FakeStatus;

    PVOID                       LockHandler;        // For the filter lock

    PUNICODE_STRING             Reserved9;

    PNDIS_MINIPORT_TIMER        TimerQueue;

    UINT                        MacOptions;

    //
    // RequestInformation
    //
    PNDIS_REQUEST               PendingRequest;
    UINT                        MaximumLongAddresses;
    UINT                        MaximumShortAddresses;
    UINT                        CurrentLookahead;
    UINT                        MaximumLookahead;

    //
    //  For efficiency
    //
    ULONG_PTR                   Reserved1;
    W_DISABLE_INTERRUPT_HANDLER DisableInterruptHandler;
    W_ENABLE_INTERRUPT_HANDLER  EnableInterruptHandler;
    W_SEND_PACKETS_HANDLER      SendPacketsHandler;
    NDIS_M_START_SENDS          DeferredSendHandler;

    //
    // The following cannot be unionized.
    //
    ETH_RCV_INDICATE_HANDLER    EthRxIndicateHandler;   // EXPOSED via macros. Do not move
    TR_RCV_INDICATE_HANDLER     TrRxIndicateHandler;    // EXPOSED via macros. Do not move
    PVOID                       Reserved2;

    ETH_RCV_COMPLETE_HANDLER    EthRxCompleteHandler;   // EXPOSED via macros. Do not move
    TR_RCV_COMPLETE_HANDLER     TrRxCompleteHandler;    // EXPOSED via macros. Do not move
    PVOID                       Reserved21;

    NDIS_M_STATUS_HANDLER       StatusHandler;          // EXPOSED via macros. Do not move
    NDIS_M_STS_COMPLETE_HANDLER StatusCompleteHandler;  // EXPOSED via macros. Do not move
    NDIS_M_TD_COMPLETE_HANDLER  TDCompleteHandler;      // EXPOSED via macros. Do not move
    NDIS_M_REQ_COMPLETE_HANDLER QueryCompleteHandler;   // EXPOSED via macros. Do not move
    NDIS_M_REQ_COMPLETE_HANDLER SetCompleteHandler;     // EXPOSED via macros. Do not move

    NDIS_WM_SEND_COMPLETE_HANDLER WanSendCompleteHandler;// EXPOSED via macros. Do not move
    WAN_RCV_HANDLER             WanRcvHandler;          // EXPOSED via macros. Do not move
    WAN_RCV_COMPLETE_HANDLER    WanRcvCompleteHandler;  // EXPOSED via macros. Do not move

    RECEIVE_NET_BUFFER_LISTS_HANDLER IndicateNetBufferListsHandler; // EXPOSED via macros. Do not move
    NDIS_HANDLE                  IndicateNetBufferListsContext; // EXPOSED via macros. Do not move
    SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER   SendNetBufferListsCompleteHandler;  // EXPOSED via macros. Do not move

    /********************************************************************************************/
    /****************                                                                  **********/
    /**************** STUFF ABOVE IS POTENTIALLY ACCESSED BY MACROS. ADD STUFF BELOW   **********/
    /**************** SEVERE POSSIBILITY OF BREAKING SOMETHING IF STUFF ABOVE IS MOVED **********/
    /****************                                                                  **********/
    /********************************************************************************************/


};
#endif // NDIS_WRAPPER not defined

//
//  Routines for intermediate miniport drivers.
//
typedef
VOID
(*W_MINIPORT_CALLBACK)(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PVOID                   CallbackContext
    );

EXPORT
NDIS_STATUS
NdisIMRegisterLayeredMiniport(
    IN  NDIS_HANDLE                     NdisWrapperHandle,
    IN  PNDIS_MINIPORT_CHARACTERISTICS  MiniportCharacteristics,
    IN  UINT                            CharacteristicsLength,
    OUT PNDIS_HANDLE                    DriverHandle
    );

EXPORT
VOID
NdisIMDeregisterLayeredMiniport(
    IN  NDIS_HANDLE         DriverHandle
    );

EXPORT
VOID
NdisIMAssociateMiniport(
    IN  NDIS_HANDLE         DriverHandle,
    IN  NDIS_HANDLE         ProtocolHandle
    );

EXPORT
NDIS_STATUS
NdisMRegisterDevice(
    IN  NDIS_HANDLE             NdisWrapperHandle,
    IN  PNDIS_STRING            DeviceName,
    IN  PNDIS_STRING            SymbolicName,
    IN  PDRIVER_DISPATCH        MajorFunctions[],
    OUT PDEVICE_OBJECT      *   pDeviceObject,
    OUT NDIS_HANDLE         *   NdisDeviceHandle
    );

EXPORT
NDIS_STATUS
NdisMDeregisterDevice(
    IN  NDIS_HANDLE             NdisDeviceHandle
    );

EXPORT
VOID
NdisMRegisterUnloadHandler(
    IN  NDIS_HANDLE             NdisWrapperHandle,
    IN  PDRIVER_UNLOAD          UnloadHandler
    );

//
// Operating System Requests
//
typedef UCHAR   NDIS_DMA_SIZE;

#define NDIS_DMA_24BITS             ((NDIS_DMA_SIZE)0)
#define NDIS_DMA_32BITS             ((NDIS_DMA_SIZE)1)
#define NDIS_DMA_64BITS             ((NDIS_DMA_SIZE)2)

EXPORT
NDIS_STATUS
NdisMAllocateMapRegisters(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  UINT                    DmaChannel,
    IN  NDIS_DMA_SIZE           DmaSize,
    IN  ULONG                   BaseMapRegistersNeeded,
    IN  ULONG                   MaximumPhysicalMapping
    );

EXPORT
VOID
NdisMFreeMapRegisters(
    IN  NDIS_HANDLE             MiniportAdapterHandle
    );

EXPORT
NDIS_STATUS
NdisMInitializeScatterGatherDma(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  BOOLEAN                 Dma64BitAddresses,
    IN  ULONG                   MaximumPhysicalMapping
    );

EXPORT
NDIS_STATUS
NdisMRegisterIoPortRange(
    OUT PVOID *                 PortOffset,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  UINT                    InitialPort,
    IN  UINT                    NumberOfPorts
    );

EXPORT
VOID
NdisMDeregisterIoPortRange(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  UINT                    InitialPort,
    IN  UINT                    NumberOfPorts,
    IN  PVOID                   PortOffset
    );

EXPORT
NDIS_STATUS
NdisMMapIoSpace(
    OUT PVOID *                 VirtualAddress,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_PHYSICAL_ADDRESS   PhysicalAddress,
    IN  UINT                    Length
    );

EXPORT
VOID
NdisMUnmapIoSpace(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PVOID                   VirtualAddress,
    IN  UINT                    Length
    );

EXPORT
NDIS_STATUS
NdisMRegisterInterrupt(
    OUT PNDIS_MINIPORT_INTERRUPT Interrupt,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  UINT                    InterruptVector,
    IN  UINT                    InterruptLevel,
    IN  BOOLEAN                 RequestIsr,
    IN  BOOLEAN                 SharedInterrupt,
    IN  NDIS_INTERRUPT_MODE     InterruptMode
    );

EXPORT
VOID
NdisMDeregisterInterrupt(
    IN  PNDIS_MINIPORT_INTERRUPT Interrupt
    );

EXPORT
BOOLEAN
NdisMSynchronizeWithInterrupt(
    IN  PNDIS_MINIPORT_INTERRUPT Interrupt,
    IN  PVOID                   SynchronizeFunction,
    IN  PVOID                   SynchronizeContext
    );

EXPORT
VOID
NdisMQueryAdapterResources(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             WrapperConfigurationContext,
    OUT PNDIS_RESOURCE_LIST     ResourceList,
    IN  OUT PUINT               BufferSize
    );

//
// Timers
//
// VOID
// NdisMSetTimer(
//  IN  PNDIS_MINIPORT_TIMER    Timer,
//  IN  UINT                    MillisecondsToDelay
//  );
#define NdisMSetTimer(_Timer, _Delay)   NdisSetTimer((PNDIS_TIMER)_Timer, _Delay)

EXPORT
VOID
NdisMSetPeriodicTimer(
    IN  PNDIS_MINIPORT_TIMER     Timer,
    IN  UINT                     MillisecondPeriod
    );

EXPORT
VOID
NdisMInitializeTimer(
    IN  OUT PNDIS_MINIPORT_TIMER Timer,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_TIMER_FUNCTION    TimerFunction,
    IN  PVOID                   FunctionContext
    );

EXPORT
VOID
NdisMCancelTimer(
    IN  PNDIS_MINIPORT_TIMER    Timer,
    OUT PBOOLEAN                TimerCancelled
    );

EXPORT
VOID
NdisMSleep(
    IN  ULONG                   MicrosecondsToSleep
    );

//
// Physical Mapping
//
EXPORT
VOID
NdisMStartBufferPhysicalMapping(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_BUFFER            Buffer,
    IN  ULONG                   PhysicalMapRegister,
    IN  BOOLEAN                 WriteToDevice,
    OUT PNDIS_PHYSICAL_ADDRESS_UNIT PhysicalAddressArray,
    OUT PUINT                   ArraySize
    );

EXPORT
VOID
NdisMCompleteBufferPhysicalMapping(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_BUFFER            Buffer,
    IN  ULONG                   PhysicalMapRegister
    );


EXPORT
ULONG
NdisMGetDmaAlignment(
    IN  NDIS_HANDLE MiniportAdapterHandle
    );

//
// Shared memory
//
EXPORT
VOID
NdisMAllocateSharedMemory(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  ULONG                   Length,
    IN  BOOLEAN                 Cached,
    OUT PVOID *                 VirtualAddress,
    OUT PNDIS_PHYSICAL_ADDRESS  PhysicalAddress
    );

EXPORT
NDIS_STATUS
NdisMAllocateSharedMemoryAsync(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  ULONG                   Length,
    IN  BOOLEAN                 Cached,
    IN  PVOID                   Context
    );

/*++
VOID
NdisMUpdateSharedMemory(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  ULONG                   Length,
    IN  PVOID                   VirtualAddress,
    IN  NDIS_PHYSICAL_ADDRESS   PhysicalAddress
    )
--*/
#define NdisMUpdateSharedMemory(_H, _L, _V, _P) NdisUpdateSharedMemory(_H, _L, _V, _P)


EXPORT
VOID
NdisMFreeSharedMemory(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  ULONG                   Length,
    IN  BOOLEAN                 Cached,
    IN  PVOID                   VirtualAddress,
    IN  NDIS_PHYSICAL_ADDRESS   PhysicalAddress
    );


//
// DMA operations.
//
EXPORT
NDIS_STATUS
NdisMRegisterDmaChannel(
    OUT PNDIS_HANDLE            MiniportDmaHandle,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  UINT                    DmaChannel,
    IN  BOOLEAN                 Dma32BitAddresses,
    IN  PNDIS_DMA_DESCRIPTION   DmaDescription,
    IN  ULONG                   MaximumLength
    );


EXPORT
VOID
NdisMDeregisterDmaChannel(
    IN  NDIS_HANDLE             MiniportDmaHandle
    );

/*++
VOID
NdisMSetupDmaTransfer(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             MiniportDmaHandle,
    IN  PNDIS_BUFFER            Buffer,
    IN  ULONG                   Offset,
    IN  ULONG                   Length,
    IN  BOOLEAN                 WriteToDevice
    )
--*/
#define NdisMSetupDmaTransfer(_S, _H, _B, _O, _L, _M_) \
        NdisSetupDmaTransfer(_S, _H, _B, _O, _L, _M_)

/*++
VOID
NdisMCompleteDmaTransfer(
    OUT PNDIS_STATUS            Status,
    IN  NDIS_HANDLE             MiniportDmaHandle,
    IN  PNDIS_BUFFER            Buffer,
    IN  ULONG                   Offset,
    IN  ULONG                   Length,
    IN  BOOLEAN                 WriteToDevice
    )
--*/
#define NdisMCompleteDmaTransfer(_S, _H, _B, _O, _L, _M_) \
        NdisCompleteDmaTransfer(_S, _H, _B, _O, _L, _M_)

EXPORT
ULONG
NdisMReadDmaCounter(
    IN  NDIS_HANDLE             MiniportDmaHandle
    );


//
// Requests Used by Miniport Drivers
//
#define NdisMInitializeWrapper(_a,_b,_c,_d) NdisInitializeWrapper((_a),(_b),(_c),(_d))

EXPORT
NDIS_STATUS
NdisMRegisterMiniport(
    IN  NDIS_HANDLE                     NdisWrapperHandle,
    IN  PNDIS_MINIPORT_CHARACTERISTICS  MiniportCharacteristics,
    IN  UINT                            CharacteristicsLength
    );

// EXPORT
// NDIS_STATUS
// NdisIMInitializeDeviceInstance(
//  IN  NDIS_HANDLE             DriverHandle,
//  IN  PNDIS_STRING            DriverInstance
//  );
#define NdisIMInitializeDeviceInstance(_H_, _I_)    \
                                NdisIMInitializeDeviceInstanceEx(_H_, _I_, NULL)

EXPORT
NDIS_STATUS
NdisIMInitializeDeviceInstanceEx(
    IN  NDIS_HANDLE             DriverHandle,
    IN  PNDIS_STRING            DriverInstance,
    IN  NDIS_HANDLE             DeviceContext   OPTIONAL
    );

EXPORT
NDIS_STATUS
NdisIMCancelInitializeDeviceInstance(
    IN  NDIS_HANDLE             DriverHandle,
    IN  PNDIS_STRING            DeviceInstance
    );

EXPORT
NDIS_HANDLE
NdisIMGetDeviceContext(
    IN  NDIS_HANDLE             MiniportAdapterHandle
    );

EXPORT
NDIS_HANDLE
NdisIMGetBindingContext(
    IN  NDIS_HANDLE             NdisBindingHandle
    );

EXPORT
NDIS_STATUS
NdisIMDeInitializeDeviceInstance(
    IN  NDIS_HANDLE             NdisMiniportHandle
    );

EXPORT
VOID
NdisIMCopySendPerPacketInfo(
    OUT PNDIS_PACKET            DstPacket,
    IN  PNDIS_PACKET            SrcPacket
    );

EXPORT
VOID
NdisIMCopySendCompletePerPacketInfo(
    OUT PNDIS_PACKET            DstPacket,
    IN  PNDIS_PACKET            SrcPacket
    );

// EXPORT
// VOID
// NdisMSetAttributes(
//  IN  NDIS_HANDLE             MiniportAdapterHandle,
//  IN  NDIS_HANDLE             MiniportAdapterContext,
//  IN  BOOLEAN                 BusMaster,
//  IN  NDIS_INTERFACE_TYPE     AdapterType
//  );
#define NdisMSetAttributes(_H_, _C_, _M_, _T_)                                      \
                        NdisMSetAttributesEx(_H_,                                   \
                                             _C_,                                   \
                                             0,                                     \
                                             (_M_) ? NDIS_ATTRIBUTE_BUS_MASTER : 0, \
                                             _T_)                                   \


EXPORT
VOID
NdisMSetAttributesEx(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  UINT                    CheckForHangTimeInSeconds OPTIONAL,
    IN  ULONG                   AttributeFlags,
    IN  NDIS_INTERFACE_TYPE     AdapterType OPTIONAL
    );

#define NDIS_ATTRIBUTE_IGNORE_PACKET_TIMEOUT        0x00000001
#define NDIS_ATTRIBUTE_IGNORE_REQUEST_TIMEOUT       0x00000002
#define NDIS_ATTRIBUTE_IGNORE_TOKEN_RING_ERRORS     0x00000004
#define NDIS_ATTRIBUTE_BUS_MASTER                   0x00000008
#define NDIS_ATTRIBUTE_INTERMEDIATE_DRIVER          0x00000010
#define NDIS_ATTRIBUTE_DESERIALIZE                  0x00000020
#define NDIS_ATTRIBUTE_NO_HALT_ON_SUSPEND           0x00000040
#define NDIS_ATTRIBUTE_SURPRISE_REMOVE_OK           0x00000080
#define NDIS_ATTRIBUTE_NOT_CO_NDIS                  0x00000100
#define NDIS_ATTRIBUTE_USES_SAFE_BUFFER_APIS        0x00000200
#define NDIS_ATTRIBUTE_DO_NOT_BIND_TO_ALL_CO        0x00000400


EXPORT
NDIS_STATUS
NdisMSetMiniportSecondary(
    IN  NDIS_HANDLE             MiniportHandle,
    IN  NDIS_HANDLE             PrimaryMiniportHandle
    );

EXPORT
NDIS_STATUS
NdisMPromoteMiniport(
    IN  NDIS_HANDLE             MiniportHandle
    );

EXPORT
NDIS_STATUS
NdisMRemoveMiniport(
    IN  NDIS_HANDLE             MiniportHandle
    );

#define NdisMSendComplete(_M, _P, _S)   (*((PNDIS_MINIPORT_BLOCK)(_M))->SendCompleteHandler)(_M, _P, _S)

#define NdisMSendResourcesAvailable(_M) (*((PNDIS_MINIPORT_BLOCK)(_M))->SendResourcesHandler)(_M)

#define NdisMResetComplete(_M, _S, _A)  (*((PNDIS_MINIPORT_BLOCK)(_M))->ResetCompleteHandler)(_M, _S, _A)

#define NdisMTransferDataComplete(_M, _P, _S, _B)   \
                                        (*((PNDIS_MINIPORT_BLOCK)(_M))->TDCompleteHandler)(_M, _P, _S, _B)

/*++

VOID
NdisMWanSendComplete(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PVOID                   Packet,
    IN  NDIS_STATUS             Status
    );

--*/

#define NdisMWanSendComplete(_M_, _P_, _S_)                                             \
                (*((PNDIS_MINIPORT_BLOCK)(_M_))->WanSendCompleteHandler)(_M_, _P_, _S_)

#define NdisMQueryInformationComplete(_M, _S)   \
                                        (*((PNDIS_MINIPORT_BLOCK)(_M))->QueryCompleteHandler)(_M, _S)

#define NdisMSetInformationComplete(_M, _S) \
                                        (*((PNDIS_MINIPORT_BLOCK)(_M))->SetCompleteHandler)(_M, _S)

/*++

VOID
NdisMIndicateReceivePacket(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PPNDIS_PACKET           ReceivedPackets,
    IN  UINT                    NumberOfPackets
    );

--*/
#define NdisMIndicateReceivePacket(_H, _P, _N)                                  \
{                                                                               \
    (*((PNDIS_MINIPORT_BLOCK)(_H))->PacketIndicateHandler)(                     \
                        _H,                                                     \
                        _P,                                                     \
                        _N);                                                    \
}

/*++

VOID
NdisMWanIndicateReceive(
    OUT PNDIS_STATUS            Status,
    IN NDIS_HANDLE              MiniportAdapterHandle,
    IN NDIS_HANDLE              NdisLinkContext,
    IN PUCHAR                   Packet,
    IN ULONG                    PacketSize
    );

--*/

#define NdisMWanIndicateReceive(_S_, _M_, _C_, _P_, _Z_)                        \
                (*((PNDIS_MINIPORT_BLOCK)(_M_))->WanRcvHandler)(_S_, _M_, _C_, _P_, _Z_)

/*++

VOID
NdisMWanIndicateReceiveComplete(
    IN NDIS_HANDLE              MiniportAdapterHandle,
    IN NDIS_HANDLE              NdisLinkContext
    );

--*/

#define NdisMWanIndicateReceiveComplete(_M_, _C_)                                   \
                (*((PNDIS_MINIPORT_BLOCK)(_M_))->WanRcvCompleteHandler)(_M_, _C_)

/*++

VOID
NdisMEthIndicateReceive(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_HANDLE             MiniportReceiveContext,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookaheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize
    )

--*/
#define NdisMEthIndicateReceive( _H, _C, _B, _SZ, _L, _LSZ, _PSZ)               \
{                                                                               \
    (*((PNDIS_MINIPORT_BLOCK)(_H))->EthRxIndicateHandler)(                      \
        ((PNDIS_MINIPORT_BLOCK)(_H))->EthDB,                                    \
        _C,                                                                     \
        _B,                                                                     \
        _B,                                                                     \
        _SZ,                                                                    \
        _L,                                                                     \
        _LSZ,                                                                   \
        _PSZ                                                                    \
        );                                                                      \
}

/*++

VOID
NdisMTrIndicateReceive(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_HANDLE             MiniportReceiveContext,
    IN  PVOID                   HeaderBuffer,
    IN  UINT                    HeaderBufferSize,
    IN  PVOID                   LookaheadBuffer,
    IN  UINT                    LookaheadBufferSize,
    IN  UINT                    PacketSize
    )

--*/
#define NdisMTrIndicateReceive( _H, _C, _B, _SZ, _L, _LSZ, _PSZ)                \
{                                                                               \
    (*((PNDIS_MINIPORT_BLOCK)(_H))->TrRxIndicateHandler)(                       \
        ((PNDIS_MINIPORT_BLOCK)(_H))->TrDB,                                     \
        _C,                                                                     \
        _B,                                                                     \
        _SZ,                                                                    \
        _L,                                                                     \
        _LSZ,                                                                   \
        _PSZ                                                                    \
        );                                                                      \
}


/*++

VOID
NdisMEthIndicateReceiveComplete(
    IN  NDIS_HANDLE             MiniportHandle
    );

--*/

#define NdisMEthIndicateReceiveComplete( _H )                                   \
{                                                                               \
    (*((PNDIS_MINIPORT_BLOCK)(_H))->EthRxCompleteHandler)(                      \
                                        ((PNDIS_MINIPORT_BLOCK)_H)->EthDB);     \
}

/*++

VOID
NdisMTrIndicateReceiveComplete(
    IN  NDIS_HANDLE             MiniportHandle
    );

--*/

#define NdisMTrIndicateReceiveComplete( _H )                                    \
{                                                                               \
    (*((PNDIS_MINIPORT_BLOCK)(_H))->TrRxCompleteHandler)(                       \
                                        ((PNDIS_MINIPORT_BLOCK)_H)->TrDB);      \
}


EXPORT
VOID
NdisMIndicateStatus(
    IN  NDIS_HANDLE             MiniportHandle,
    IN  NDIS_STATUS             GeneralStatus,
    IN  PVOID                   StatusBuffer,
    IN  UINT                    StatusBufferSize
    );


EXPORT
VOID
NdisMIndicateStatusEx(
    IN NDIS_HANDLE              MiniportAdapterHandle,
    IN PNDIS_STATUS_INDICATION  StatusIndication
    );
   

EXPORT
VOID
NdisMIndicateStatusComplete(
    IN  NDIS_HANDLE             MiniportHandle
    );

EXPORT
VOID
NdisMRegisterAdapterShutdownHandler(
    IN  NDIS_HANDLE             MiniportHandle,
    IN  PVOID                   ShutdownContext,
    IN  ADAPTER_SHUTDOWN_HANDLER ShutdownHandler
    );

EXPORT
VOID
NdisMDeregisterAdapterShutdownHandler(
    IN  NDIS_HANDLE             MiniportHandle
    );

EXPORT
NDIS_STATUS
NdisMPciAssignResources(
    IN  NDIS_HANDLE             MiniportHandle,
    IN  ULONG                   SlotNumber,
    IN  PNDIS_RESOURCE_LIST *   AssignedResources
    );

EXPORT
NDIS_STATUS
NdisIMNotifyPnPEvent(
    IN  NDIS_HANDLE             MiniportHandle,
    IN  PNET_PNP_EVENT          NetPnPEvent
    );


//
// Logging support for miniports
//

EXPORT
NDIS_STATUS
NdisMCreateLog(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  UINT                    Size,
    OUT PNDIS_HANDLE            LogHandle
    );

EXPORT
VOID
NdisMCloseLog(
    IN  NDIS_HANDLE             LogHandle
    );

EXPORT
NDIS_STATUS
NdisMWriteLogData(
    IN  NDIS_HANDLE             LogHandle,
    IN  PVOID                   LogBuffer,
    IN  UINT                    LogBufferSize
    );

EXPORT
VOID
NdisMFlushLog(
    IN  NDIS_HANDLE             LogHandle
    );

EXPORT
VOID
NdisMGetDeviceProperty(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN OUT PDEVICE_OBJECT *     PhysicalDeviceObject        OPTIONAL,
    IN OUT PDEVICE_OBJECT *     FunctionalDeviceObject      OPTIONAL,
    IN OUT PDEVICE_OBJECT *     NextDeviceObject            OPTIONAL,
    IN OUT PCM_RESOURCE_LIST *  AllocatedResources          OPTIONAL,
    IN OUT PCM_RESOURCE_LIST *  AllocatedResourcesTranslated OPTIONAL
    );

//
//  Get a pointer to the adapter's localized instance name.
//
EXPORT
NDIS_STATUS
NdisMQueryAdapterInstanceName(
    OUT PNDIS_STRING            pAdapterInstanceName,
    IN  NDIS_HANDLE             MiniportHandle
    );

//
// NDIS 5.0 extensions for miniports
//

EXPORT
VOID
NdisMCoIndicateReceivePacket(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );

EXPORT
VOID
NdisMCoIndicateStatus(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_STATUS             GeneralStatus,
    IN  PVOID                   StatusBuffer    OPTIONAL,
    IN  ULONG                   StatusBufferSize
    );

EXPORT
VOID
NdisMCoReceiveComplete(
    IN  NDIS_HANDLE             MiniportAdapterHandle
    );

EXPORT
VOID
NdisMCoSendComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PNDIS_PACKET            Packet
    );

EXPORT
VOID
NdisMCoActivateVcComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

EXPORT
VOID
NdisMCoDeactivateVcComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle
    );

EXPORT
VOID
NdisMCoRequestComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_REQUEST           Request
    );

EXPORT
VOID
NdisMCoOidRequestComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_OID_REQUEST       Request
    );

EXPORT
NDIS_STATUS
NdisMCmRegisterAddressFamily(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PCO_ADDRESS_FAMILY      AddressFamily,
    IN  PNDIS_CALL_MANAGER_CHARACTERISTICS CmCharacteristics,
    IN  UINT                    SizeOfCmCharacteristics
    );

EXPORT
NDIS_STATUS
NdisMCmCreateVc(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             MiniportVcContext,
    OUT PNDIS_HANDLE            NdisVcHandle
    );

EXPORT
NDIS_STATUS
NdisMCmDeleteVc(
    IN  NDIS_HANDLE             NdisVcHandle
    );


EXPORT
NDIS_STATUS
NdisMCmActivateVc(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

EXPORT
NDIS_STATUS
NdisMCmDeactivateVc(
    IN  NDIS_HANDLE             NdisVcHandle
    );


EXPORT
NDIS_STATUS
NdisMCmRequest(
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
    IN OUT PNDIS_REQUEST        NdisRequest
    );

EXPORT
NDIS_STATUS
NdisMCmOidRequest(
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
    IN OUT PNDIS_OID_REQUEST    NdisRequest
    );


EXPORT
VOID
NdisMCoIndicateStatusEx(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  PNDIS_STATUS_INDICATION StatusIndication
    );


// EXPORT
// VOID
// NdisMCmRequestComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisAfHandle,
//  IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
//  IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
//  IN  PNDIS_REQUEST           NdisRequest
//  );
#define NdisMCmRequestComplete(_S_, _AH_, _VH_, _PH_, _R_) \
                                        NdisCoRequestComplete(_S_, _AH_, _VH_, _PH_, _R_)

// EXPORT
// VOID
// NdisMCmRequestCompleteEx(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisAfHandle,
//  IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
//  IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
//  IN  PNDIS_REQUEST_EX        NdisRequest
//  );
#define NdisMCmRequestCompleteEx(_S_, _AH_, _VH_, _PH_, _R_) \
                                        NdisCoRequestComplete(_S_, _AH_, _VH_, _PH_, _R_)

// EXPORT
// VOID
// NdisMCmOpenAddressFamilyComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisAfHandle,
//  IN  NDIS_HANDLE             CallMgrAfContext
//  );

#define NdisMCmOpenAddressFamilyComplete(_S_, _H_, _C_) \
                                        NdisCmOpenAddressFamilyComplete(_S_, _H_, _C_)


// EXPORT
// VOID
// NdisMCmCloseAddressFamilyComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisAfHandle
//  );

#define NdisMCmCloseAddressFamilyComplete(_S_, _H_)     \
                                        NdisCmCloseAddressFamilyComplete(_S_, _H_)



// EXPORT
// VOID
// NdisMCmRegisterSapComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisSapHandle,
//  IN  NDIS_HANDLE             CallMgrSapContext
//  );

#define NdisMCmRegisterSapComplete(_S_, _H_, _C_)       \
                                        NdisCmRegisterSapComplete(_S_, _H_, _C_)


// EXPORT
// VOID
// NdisMCmDeregisterSapComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisSapHandle
//  );

#define NdisMCmDeregisterSapComplete(_S_, _H_)          \
                                        NdisCmDeregisterSapComplete(_S_, _H_)


// EXPORT
// VOID
// NdisMCmMakeCallComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisVcHandle,
//  IN  NDIS_HANDLE             NdisPartyHandle     OPTIONAL,
//  IN  NDIS_HANDLE             CallMgrPartyContext OPTIONAL,
//  IN  PCO_CALL_PARAMETERS     CallParameters
//  );

#define NdisMCmMakeCallComplete(_S_, _VH_, _PH_, _CC_, _CP_)    \
                                        NdisCmMakeCallComplete(_S_, _VH_, _PH_, _CC_, _CP_)


// EXPORT
// VOID
// NdisMCmCloseCallComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisVcHandle,
//  IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL
//  );

#define NdisMCmCloseCallComplete(_S_, _VH_, _PH_)       \
                                        NdisCmCloseCallComplete(_S_, _VH_, _PH_)


// EXPORT
// VOID
// NdisMCmAddPartyComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisPartyHandle,
//  IN  NDIS_HANDLE             CallMgrPartyContext OPTIONAL,
//  IN  PCO_CALL_PARAMETERS     CallParameters
//  );

#define NdisMCmAddPartyComplete(_S_, _H_, _C_, _P_)     \
                                        NdisCmAddPartyComplete(_S_, _H_, _C_, _P_)


// EXPORT
// VOID
// NdisMCmDropPartyComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisPartyHandle
//  );

#define NdisMCmDropPartyComplete(_S_, _H_)              \
                                        NdisCmDropPartyComplete(_S_, _H_)


// EXPORT
// NDIS_STATUS
// NdisMCmDispatchIncomingCall(
//  IN  NDIS_HANDLE             NdisSapHandle,
//  IN  NDIS_HANDLE             NdisVcHandle,
//  IN  PCO_CALL_PARAMETERS     CallParameters
//  );

#define NdisMCmDispatchIncomingCall(_SH_, _VH_, _CP_)   \
                                        NdisCmDispatchIncomingCall(_SH_, _VH_, _CP_)


// EXPORT
// VOID
// NdisMCmDispatchCallConnected(
//  IN  NDIS_HANDLE             NdisVcHandle
//  );

#define NdisMCmDispatchCallConnected(_H_)               \
                                        NdisCmDispatchCallConnected(_H_)


// EXPORT
// NdisMCmModifyCallQoSComplete(
//  IN  NDIS_STATUS             Status,
//  IN  NDIS_HANDLE             NdisVcHandle,
//  IN  PCO_CALL_PARAMETERS     CallParameters
//  );

#define NdisMCmModifyCallQoSComplete(_S_, _H_, _P_)     \
                                        NdisCmModifyCallQoSComplete(_S_, _H_, _P_)


// EXPORT
// VOID
// VOID
// NdisMCmDispatchIncomingCallQoSChange(
//  IN  NDIS_HANDLE             NdisVcHandle,
//  IN  PCO_CALL_PARAMETERS     CallParameters
//  );

#define NdisMCmDispatchIncomingCallQoSChange(_H_, _P_)  \
                                        NdisCmDispatchIncomingCallQoSChange(_H_, _P_)


// EXPORT
// VOID
// NdisMCmDispatchIncomingCloseCall(
//   IN  NDIS_STATUS             CloseStatus,
//   IN  NDIS_HANDLE             NdisVcHandle,
//   IN  PVOID                   Buffer         OPTIONAL,
//   IN  UINT                    Size
//   );

#define NdisMCmDispatchIncomingCloseCall(_S_, _H_, _B_, _Z_)    \
                                        NdisCmDispatchIncomingCloseCall(_S_, _H_, _B_, _Z_)


//  EXPORT
//  VOID
//  NdisMCmDispatchIncomingDropParty(
//      IN  NDIS_STATUS         DropStatus,
//      IN  NDIS_HANDLE         NdisPartyHandle,
//      IN  PVOID               Buffer      OPTIONAL,
//      IN  UINT                Size
//      );
#define NdisMCmDispatchIncomingDropParty(_S_, _H_, _B_, _Z_)    \
                                        NdisCmDispatchIncomingDropParty(_S_, _H_, _B_, _Z_)


//
// make the new SG DMA APIs available to 5.2 miniports as well as NDIS 6.0
//
#if (defined(NDIS60_MINIPORT) || defined(NDIS52_MINIPORT))

EXPORT
NDIS_STATUS
NdisMRegisterScatterGatherDma(
    IN  NDIS_HANDLE                     MiniportAdapterHandle,
    IN  PNDIS_SG_DMA_DESCRIPTION        DmaDescription,
    OUT PNDIS_HANDLE                    NdisMiniportDmaHandle
    );

EXPORT
VOID
NdisMDeregisterScatterGatherDma(
    IN  NDIS_HANDLE                     NdisMiniportDmaHandle
    );

EXPORT
NDIS_STATUS
NdisMAllocateNetBufferSGList(
    IN  NDIS_HANDLE             NdisMiniportDmaHandle,
    IN  PNET_BUFFER             NetBuffer,
    IN  PVOID                   Context,
    IN  PVOID                   ScatterGatherListBuffer OPTIONAL,
    IN  ULONG                   ScatterGatherListBufferSize OPTIONAL
    );

EXPORT
VOID
NdisMFreeNetBufferSGList(
    IN  NDIS_HANDLE             NdisMiniportDmaHandle,
    IN  PSCATTER_GATHER_LIST    pSGL,
    IN  PNET_BUFFER             NetBuffer
    );

#endif // NDIS60_MINIPORT || NDIS52_MINIPORT

#if ((NDIS60_MINIPORT))

EXPORT
NDIS_STATUS
NdisMRegisterMiniportDriver(
    IN  PDRIVER_OBJECT                              DriverObject,
    IN  PUNICODE_STRING                             RegistryPath,
    IN  NDIS_HANDLE                                 MiniportDriverContext,
    IN  PNDIS_MINIPORT_DRIVER_CHARACTERISTICS       MiniportDriverCharacteristics,
    OUT PNDIS_HANDLE                                NdisMiniportDriverHandle
    );

EXPORT
VOID
NdisMDeregisterMiniportDriver(
    IN NDIS_HANDLE              NdisMiniportDriverHandle
    );

EXPORT
VOID
NdisMPauseComplete(
    IN  NDIS_HANDLE             MiniportAdapterHandle
    );

EXPORT
VOID
NdisMRestartComplete(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  NDIS_STATUS             Status
    );


EXPORT
VOID
NdisMRequestComplete(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_REQUEST_EX        Request,
    IN  NDIS_STATUS             Status
    );
    

EXPORT
VOID
NdisMSendNetBufferListsComplete(
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  BOOLEAN                 DispatchLevel
    );
/*
#define NdisMSendNetBufferListsComplete(_M, _NBL, _DL)   (*((PNDIS_MINIPORT_BLOCK)(_M))->SendNetBufferListsCompleteHandler)(_M, _NBL, _DL)
*/
#define NdisMIndicateReceiveNetBufferLists(_M, _NBL, _S, _DL)   \
    (*((PNDIS_MINIPORT_BLOCK)(_M))->IndicateNetBufferListsHandler)(((PNDIS_MINIPORT_BLOCK)(_M))->IndicateNetBufferListsContext, _NBL, _S, _DL)


#endif


#if NDIS_CHIMNEY_OFFLOAD

#if ((NDIS52_MINIPORT) || (NDIS60_MINIPORT))


//
// Generic offload functions supported by NDIS for use by the miniport.
//
EXPORT
VOID
NdisMInitiateOffloadComplete(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

EXPORT
VOID
NdisMTerminateOffloadComplete(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

EXPORT
VOID
NdisMInvalidateOffloadComplete(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

EXPORT
VOID
NdisMUpdateOffloadComplete(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

EXPORT
VOID
NdisMQueryOffloadComplete(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList
    );

//
// Generic offload event indication handlers.
//
EXPORT
VOID
NdisMOffloadEventIndicate(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNDIS_MINIPORT_OFFLOAD_BLOCK_LIST     OffloadBlockList,
    IN ULONG                                 IndicationCode
    );

//
// Tcp offload specific functions supported by NDIS used for completions.
//
typedef
VOID
(*NDIS_TCP_OFFLOAD_SEND_COMPLETE)(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
VOID
(*NDIS_TCP_OFFLOAD_RECEIVE_COMPLETE)(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
VOID
(*NDIS_TCP_OFFLOAD_DISCONNECT_COMPLETE)(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

typedef
VOID
(*NDIS_TCP_OFFLOAD_FORWARD_COMPLETE)(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN PNET_BUFFER_LIST                      NetBufferList
    );

//
// Tcp offload specific functions supported by NDIS used for indication.
//
typedef
VOID
(*NDIS_TCP_OFFLOAD_EVENT_INDICATE)(
    IN NDIS_HANDLE                           NdisOffloadHandle,
    IN ULONG                                 EventType,
    IN ULONG                                 EventSpecificInformation
    );

typedef
NDIS_STATUS
(*NDIS_TCP_OFFLOAD_RECEIVE_INDICATE)(
    IN NDIS_HANDLE                           NdisOffloadHandle,
    IN PNET_BUFFER_LIST                      NetBufferList,
    IN NDIS_STATUS                           Status
    );

typedef struct _NDIS_OFFLOAD_EVENT_HANDLERS
{
    NDIS_OBJECT_HEADER                       Header;
} NDIS_OFFLOAD_EVENT_HANDLERS, *PNDIS_OFFLOAD_EVENT_HANDLERS;


EXPORT
NDIS_STATUS
NdisMGetOffloadHandlers(
    IN NDIS_HANDLE                           NdisMiniportHandle,
    IN NDIS_CHIMNEY_OFFLOAD_TYPE             ChimneyType,
    OUT PNDIS_OFFLOAD_EVENT_HANDLERS         *OffloadHandlers
    );


#define NDIS_OBJECT_TCP_OFFLOAD_REVISION_1      1

typedef struct _NDIS_TCP_OFFLOAD_EVENT_HANDLERS
{
    NDIS_OBJECT_HEADER                       Header;
    NDIS_TCP_OFFLOAD_EVENT_INDICATE          NdisTcpOffloadEventHandler;
    NDIS_TCP_OFFLOAD_RECEIVE_INDICATE        NdisTcpOffloadReceiveHandler;
    NDIS_TCP_OFFLOAD_SEND_COMPLETE           NdisTcpOffloadSendComplete;
    NDIS_TCP_OFFLOAD_RECEIVE_COMPLETE        NdisTcpOffloadReceiveComplete;
    NDIS_TCP_OFFLOAD_DISCONNECT_COMPLETE     NdisTcpOffloadDisconnectComplete;
    NDIS_TCP_OFFLOAD_FORWARD_COMPLETE        NdisTcpOffloadForwardComplete;
} NDIS_TCP_OFFLOAD_EVENT_HANDLERS, *PNDIS_TCP_OFFLOAD_EVENT_HANDLERS;


#endif

#endif // NDIS_CHIMNEY_OFFLOAD


//
// IO workitem routines
//

EXPORT
NDIS_HANDLE
NdisAllocateIoWorkItem(
    IN  NDIS_HANDLE                 NdisObjectHandle
    );

typedef
VOID
(*NDIS_IO_WORKITEM_ROUTINE)(
    IN PVOID                        WorkItemContext
    );

EXPORT
VOID
NdisQueueIoWorkItem(
    IN NDIS_HANDLE                  NdisIoWorkItemHandle,
    IN NDIS_IO_WORKITEM_ROUTINE     Routine,
    IN PVOID                        WorkItemContext
    );

EXPORT
VOID
NdisFreeIoWorkItem(
    IN NDIS_HANDLE                  NdisIoWorkItemHandle
    );

#define NDIS_DEVICE_OBJECT_ATTRIBUTES_REVISION_1    1

typedef struct _NDIS_DEVICE_OBJECT_ATTRIBUTES
{
    NDIS_OBJECT_HEADER          Header;
    PNDIS_STRING                DeviceName;
    PNDIS_STRING                SymbolicName;
    PDRIVER_DISPATCH*           MajorFunctions;
    ULONG                       ExtensionSize;
    PCUNICODE_STRING            DefaultSDDLString;
    LPCGUID                     DeviceClassGuid;
} NDIS_DEVICE_OBJECT_ATTRIBUTES, *PNDIS_DEVICE_OBJECT_ATTRIBUTES;

EXPORT
NDIS_STATUS
NdisRegisterDeviceEx(
    IN  NDIS_HANDLE                     NdisObjectHandle,
    IN  PNDIS_DEVICE_OBJECT_ATTRIBUTES  DeviceObjectAttributes,
    OUT PDEVICE_OBJECT *                pDeviceObject,
    OUT PNDIS_HANDLE                    NdisDeviceHandle
    );

EXPORT
VOID
NdisDeregisterDeviceEx(
    IN  NDIS_HANDLE                    NdisDeviceHandle
    );

EXPORT
PVOID
NdisGetDeviceReservedExtension(
    IN  NDIS_HANDLE                    NdisDeviceHandle
    );


//
// CONDIS 6.0 extensions
//

EXPORT
VOID
NdisMCoSendNetBufferListsComplete(
    IN PNDIS_HANDLE         NdisVcHandle,
    IN PNET_BUFFER_LIST     NetBufferLists,
    IN BOOLEAN              DispatchLevel
    );

EXPORT
VOID
NdisMCoIndicateReceiveNetBufferLists(
    IN NDIS_HANDLE          NdisVcHandle,
    IN PNET_BUFFER_LIST     NetBufferLists,
    IN BOOLEAN              DispatchLevel
    );

EXPORT
VOID
NdisMCoRequestCompleteEx(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             MiniportAdapterHandle,
    IN  PNDIS_REQUEST_EX        Request
    );




typedef struct _CO_CALL_PARAMETERS      CO_CALL_PARAMETERS, *PCO_CALL_PARAMETERS;
typedef struct _CO_MEDIA_PARAMETERS     CO_MEDIA_PARAMETERS, *PCO_MEDIA_PARAMETERS;

//
// CoNdis client only handler proto-types - used by clients of call managers
//
typedef
VOID
(*CL_OPEN_AF_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolAfContext,
    IN  NDIS_HANDLE             NdisAfHandle
    );

typedef
VOID
(*CL_CLOSE_AF_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolAfContext
    );

typedef
VOID
(*CL_REG_SAP_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolSapContext,
    IN  PCO_SAP                 Sap,
    IN  NDIS_HANDLE             NdisSapHandle
    );

typedef
VOID
(*CL_DEREG_SAP_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolSapContext
    );

typedef
VOID
(*CL_MAKE_CALL_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  NDIS_HANDLE             NdisPartyHandle     OPTIONAL,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef
VOID
(*CL_CLOSE_CALL_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  NDIS_HANDLE             ProtocolPartyContext OPTIONAL
    );

typedef
VOID
(*CL_ADD_PARTY_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolPartyContext,
    IN  NDIS_HANDLE             NdisPartyHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef
VOID
(*CL_DROP_PARTY_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolPartyContext
    );

typedef
NDIS_STATUS
(*CL_INCOMING_CALL_HANDLER)(
    IN  NDIS_HANDLE             ProtocolSapContext,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN OUT PCO_CALL_PARAMETERS  CallParameters
    );

typedef
VOID
(*CL_CALL_CONNECTED_HANDLER)(
    IN  NDIS_HANDLE             ProtocolVcContext
    );

typedef
VOID
(*CL_INCOMING_CLOSE_CALL_HANDLER)(
    IN  NDIS_STATUS             CloseStatus,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PVOID                   CloseData   OPTIONAL,
    IN  UINT                    Size        OPTIONAL
    );

typedef
VOID
(*CL_INCOMING_DROP_PARTY_HANDLER)(
    IN  NDIS_STATUS             DropStatus,
    IN  NDIS_HANDLE             ProtocolPartyContext,
    IN  PVOID                   CloseData   OPTIONAL,
    IN  UINT                    Size        OPTIONAL
    );

typedef
VOID
(*CL_MODIFY_CALL_QOS_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef
VOID
(*CL_INCOMING_CALL_QOS_CHANGE_HANDLER)(
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef struct _NDIS_CLIENT_CHARACTERISTICS
{
    UCHAR                           MajorVersion;
    UCHAR                           MinorVersion;

    USHORT                          Filler;
    UINT                            Reserved;

    CO_CREATE_VC_HANDLER            ClCreateVcHandler;
    CO_DELETE_VC_HANDLER            ClDeleteVcHandler;
    CO_REQUEST_HANDLER              ClRequestHandler;
    CO_REQUEST_COMPLETE_HANDLER     ClRequestCompleteHandler;
    CL_OPEN_AF_COMPLETE_HANDLER     ClOpenAfCompleteHandler;
    CL_CLOSE_AF_COMPLETE_HANDLER    ClCloseAfCompleteHandler;
    CL_REG_SAP_COMPLETE_HANDLER     ClRegisterSapCompleteHandler;
    CL_DEREG_SAP_COMPLETE_HANDLER   ClDeregisterSapCompleteHandler;
    CL_MAKE_CALL_COMPLETE_HANDLER   ClMakeCallCompleteHandler;
    CL_MODIFY_CALL_QOS_COMPLETE_HANDLER ClModifyCallQoSCompleteHandler;
    CL_CLOSE_CALL_COMPLETE_HANDLER  ClCloseCallCompleteHandler;
    CL_ADD_PARTY_COMPLETE_HANDLER   ClAddPartyCompleteHandler;
    CL_DROP_PARTY_COMPLETE_HANDLER  ClDropPartyCompleteHandler;
    CL_INCOMING_CALL_HANDLER        ClIncomingCallHandler;
    CL_INCOMING_CALL_QOS_CHANGE_HANDLER ClIncomingCallQoSChangeHandler;
    CL_INCOMING_CLOSE_CALL_HANDLER  ClIncomingCloseCallHandler;
    CL_INCOMING_DROP_PARTY_HANDLER  ClIncomingDropPartyHandler;
    CL_CALL_CONNECTED_HANDLER       ClCallConnectedHandler;

} NDIS_CLIENT_CHARACTERISTICS, *PNDIS_CLIENT_CHARACTERISTICS;

//
// CoNdis call-manager only handler proto-types - used by call managers only
//
typedef
NDIS_STATUS
(*CM_OPEN_AF_HANDLER)(
    IN  NDIS_HANDLE             CallMgrBindingContext,
    IN  PCO_ADDRESS_FAMILY      AddressFamily,
    IN  NDIS_HANDLE             NdisAfHandle,
    OUT PNDIS_HANDLE            CallMgrAfContext
    );

typedef
NDIS_STATUS
(*CM_CLOSE_AF_HANDLER)(
    IN  NDIS_HANDLE             CallMgrAfContext
    );

typedef
NDIS_STATUS
(*CM_REG_SAP_HANDLER)(
    IN  NDIS_HANDLE             CallMgrAfContext,
    IN  PCO_SAP                 Sap,
    IN  NDIS_HANDLE             NdisSapHandle,
    OUT PNDIS_HANDLE            CallMgrSapContext
    );

typedef
NDIS_STATUS
(*CM_DEREG_SAP_HANDLER)(
    IN  NDIS_HANDLE             CallMgrSapContext
    );

typedef
NDIS_STATUS
(*CM_MAKE_CALL_HANDLER)(
    IN  NDIS_HANDLE             CallMgrVcContext,
    IN OUT PCO_CALL_PARAMETERS  CallParameters,
    IN  NDIS_HANDLE             NdisPartyHandle     OPTIONAL,
    OUT PNDIS_HANDLE            CallMgrPartyContext OPTIONAL
    );

typedef
NDIS_STATUS
(*CM_CLOSE_CALL_HANDLER)(
    IN  NDIS_HANDLE             CallMgrVcContext,
    IN  NDIS_HANDLE             CallMgrPartyContext OPTIONAL,
    IN  PVOID                   CloseData           OPTIONAL,
    IN  UINT                    Size                OPTIONAL
    );

typedef
NDIS_STATUS
(*CM_MODIFY_CALL_QOS_HANDLER)(
    IN  NDIS_HANDLE             CallMgrVcContext,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef
VOID
(*CM_INCOMING_CALL_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             CallMgrVcContext,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef
VOID
(*CM_ACTIVATE_VC_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             CallMgrVcContext,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );

typedef
VOID
(*CM_DEACTIVATE_VC_COMPLETE_HANDLER)(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             CallMgrVcContext
    );

typedef
NDIS_STATUS
(*CM_ADD_PARTY_HANDLER)(
    IN  NDIS_HANDLE             CallMgrVcContext,
    IN OUT PCO_CALL_PARAMETERS  CallParameters,
    IN  NDIS_HANDLE             NdisPartyHandle,
    OUT PNDIS_HANDLE            CallMgrPartyContext
    );

typedef
NDIS_STATUS
(*CM_DROP_PARTY_HANDLER)(
    IN  NDIS_HANDLE             CallMgrPartyContext,
    IN  PVOID                   CloseData   OPTIONAL,
    IN  UINT                    Size        OPTIONAL
    );

typedef struct _NDIS_CALL_MANAGER_CHARACTERISTICS
{
    UCHAR                           MajorVersion;
    UCHAR                           MinorVersion;
    USHORT                          Filler;
    UINT                            Reserved;

    CO_CREATE_VC_HANDLER            CmCreateVcHandler;
    CO_DELETE_VC_HANDLER            CmDeleteVcHandler;
    CM_OPEN_AF_HANDLER              CmOpenAfHandler;
    CM_CLOSE_AF_HANDLER             CmCloseAfHandler;
    CM_REG_SAP_HANDLER              CmRegisterSapHandler;
    CM_DEREG_SAP_HANDLER            CmDeregisterSapHandler;
    CM_MAKE_CALL_HANDLER            CmMakeCallHandler;
    CM_CLOSE_CALL_HANDLER           CmCloseCallHandler;
    CM_INCOMING_CALL_COMPLETE_HANDLER CmIncomingCallCompleteHandler;
    CM_ADD_PARTY_HANDLER            CmAddPartyHandler;
    CM_DROP_PARTY_HANDLER           CmDropPartyHandler;
    CM_ACTIVATE_VC_COMPLETE_HANDLER CmActivateVcCompleteHandler;
    CM_DEACTIVATE_VC_COMPLETE_HANDLER CmDeactivateVcCompleteHandler;
    CM_MODIFY_CALL_QOS_HANDLER      CmModifyCallQoSHandler;
    CO_REQUEST_HANDLER              CmRequestHandler;
    CO_REQUEST_COMPLETE_HANDLER     CmRequestCompleteHandler;
    
} NDIS_CALL_MANAGER_CHARACTERISTICS, *PNDIS_CALL_MANAGER_CHARACTERISTICS;

//
// this send flag is used on ATM net cards to set ( turn on ) the CLP bit
// (Cell Loss Priority) bit
//
#define CO_SEND_FLAG_SET_DISCARD_ELIBILITY  0x00000001

//
// the Address structure used on NDIS_CO_ADD_ADDRESS or NDIS_CO_DELETE_ADDRESS
//
typedef struct _CO_ADDRESS
{
    ULONG                       AddressSize;
    UCHAR                       Address[1];
} CO_ADDRESS, *PCO_ADDRESS;

//
// the list of addresses returned from the CallMgr on a NDIS_CO_GET_ADDRESSES
//
typedef struct _CO_ADDRESS_LIST
{
    ULONG                       NumberOfAddressesAvailable;
    ULONG                       NumberOfAddresses;
    CO_ADDRESS                  AddressList;
} CO_ADDRESS_LIST, *PCO_ADDRESS_LIST;

#ifndef FAR
#define FAR
#endif
#include <qos.h>

typedef struct _CO_SPECIFIC_PARAMETERS
{
    ULONG                       ParamType;
    ULONG                       Length;
    UCHAR                       Parameters[1];
} CO_SPECIFIC_PARAMETERS, *PCO_SPECIFIC_PARAMETERS;

typedef struct _CO_CALL_MANAGER_PARAMETERS
{
    FLOWSPEC                    Transmit;
    FLOWSPEC                    Receive;
    CO_SPECIFIC_PARAMETERS      CallMgrSpecific;
} CO_CALL_MANAGER_PARAMETERS, *PCO_CALL_MANAGER_PARAMETERS;


//
// this is the generic portion of the media parameters, including the media
// specific component too.
//
typedef struct _CO_MEDIA_PARAMETERS
{
    ULONG                       Flags;
    ULONG                       ReceivePriority;
    ULONG                       ReceiveSizeHint;
    CO_SPECIFIC_PARAMETERS POINTER_ALIGNMENT      MediaSpecific;
} CO_MEDIA_PARAMETERS, *PCO_MEDIA_PARAMETERS;


//
// definitions for the flags in CO_MEDIA_PARAMETERS
//
#define RECEIVE_TIME_INDICATION 0x00000001
#define USE_TIME_STAMPS         0x00000002
#define TRANSMIT_VC             0x00000004
#define RECEIVE_VC              0x00000008
#define INDICATE_ERRED_PACKETS  0x00000010
#define INDICATE_END_OF_TX      0x00000020
#define RESERVE_RESOURCES_VC    0x00000040
#define ROUND_DOWN_FLOW         0x00000080
#define ROUND_UP_FLOW           0x00000100
//
// define a flag to set in the flags of an Ndis packet when the miniport
// indicates a receive with an error in it
//
#define ERRED_PACKET_INDICATION 0x00000001

//
// this is the structure passed during call-setup
//
typedef struct _CO_CALL_PARAMETERS
{
    ULONG                       Flags;
    PCO_CALL_MANAGER_PARAMETERS CallMgrParameters;
    PCO_MEDIA_PARAMETERS        MediaParameters;
} CO_CALL_PARAMETERS, *PCO_CALL_PARAMETERS;

//
// Definitions for the Flags in CO_CALL_PARAMETERS
//
#define PERMANENT_VC            0x00000001
#define CALL_PARAMETERS_CHANGED 0x00000002
#define QUERY_CALL_PARAMETERS   0x00000004
#define BROADCAST_VC            0x00000008
#define MULTIPOINT_VC           0x00000010

//
// The format of the Request for adding/deleting a PVC
//
typedef struct _CO_PVC
{
    NDIS_HANDLE                 NdisAfHandle;
    CO_SPECIFIC_PARAMETERS      PvcParameters;
} CO_PVC,*PCO_PVC;


typedef struct _ATM_ADDRESS     ATM_ADDRESS, *PATM_ADDRESS;

EXPORT
VOID
NdisConvertStringToAtmAddress(
    OUT PNDIS_STATUS            Status,
    IN  PNDIS_STRING            String,
    OUT PATM_ADDRESS            AtmAddress
    );

//
// NDIS 5.0 Extensions for protocols
//

EXPORT
NDIS_STATUS
NdisCoAssignInstanceName(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PNDIS_STRING            BaseInstanceName,
    OUT PNDIS_STRING            VcInstanceName
    );

EXPORT
VOID
NdisCoSendPackets(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PPNDIS_PACKET           PacketArray,
    IN  UINT                    NumberOfPackets
    );


EXPORT
NDIS_STATUS
NdisCoCreateVc(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             NdisAfHandle        OPTIONAL,   // For CM signalling VCs
    IN  NDIS_HANDLE             ProtocolVcContext,
    IN OUT PNDIS_HANDLE         NdisVcHandle
    );


EXPORT
NDIS_STATUS
NdisCoDeleteVc(
    IN  NDIS_HANDLE             NdisVcHandle
    );


EXPORT
NDIS_STATUS
NdisCoRequest(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             NdisAfHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
    IN OUT PNDIS_REQUEST        NdisRequest
    );


EXPORT
VOID
NdisCoRequestComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
    IN  PNDIS_REQUEST           NdisRequest
    );

#ifndef __NDISTAPI_VAR_STRING_DECLARED
#define __NDISTAPI_VAR_STRING_DECLARED

typedef struct _VAR_STRING
{
    ULONG   ulTotalSize;
    ULONG   ulNeededSize;
    ULONG   ulUsedSize;

    ULONG   ulStringFormat;
    ULONG   ulStringSize;
    ULONG   ulStringOffset;

} VAR_STRING, *PVAR_STRING;

#endif // __NDISTAPI_VAR_STRING_DECLARED


#ifndef __NDISTAPI_STRINGFORMATS_DEFINED
#define __NDISTAPI_STRINGFORMATS_DEFINED

#define STRINGFORMAT_ASCII                          0x00000001
#define STRINGFORMAT_DBCS                           0x00000002
#define STRINGFORMAT_UNICODE                        0x00000003
#define STRINGFORMAT_BINARY                         0x00000004

#endif // __NDISTAPI_STRINGFORMATS_DEFINED

EXPORT
NDIS_STATUS
NdisCoGetTapiCallId(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  OUT PVAR_STRING         TapiCallId
    );

//
// Client Apis
//
EXPORT
NDIS_STATUS
NdisClOpenAddressFamily(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PCO_ADDRESS_FAMILY      AddressFamily,
    IN  NDIS_HANDLE             ProtocolAfContext,
    IN  PNDIS_CLIENT_CHARACTERISTICS ClCharacteristics,
    IN  UINT                    SizeOfClCharacteristics,
    OUT PNDIS_HANDLE            NdisAfHandle
    );


EXPORT
NDIS_STATUS
NdisClCloseAddressFamily(
    IN  NDIS_HANDLE             NdisAfHandle
    );


EXPORT
NDIS_STATUS
NdisClRegisterSap(
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             ProtocolSapContext,
    IN  PCO_SAP                 Sap,
    OUT PNDIS_HANDLE            NdisSapHandle
    );


EXPORT
NDIS_STATUS
NdisClDeregisterSap(
    IN  NDIS_HANDLE             NdisSapHandle
    );


EXPORT
NDIS_STATUS
NdisClMakeCall(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN OUT PCO_CALL_PARAMETERS  CallParameters,
    IN  NDIS_HANDLE             ProtocolPartyContext    OPTIONAL,
    OUT PNDIS_HANDLE            NdisPartyHandle         OPTIONAL
    );


EXPORT
NDIS_STATUS
NdisClCloseCall(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  NDIS_HANDLE             NdisPartyHandle         OPTIONAL,
    IN  PVOID                   Buffer                  OPTIONAL,
    IN  UINT                    Size                    OPTIONAL
    );


EXPORT
NDIS_STATUS
NdisClModifyCallQoS(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
VOID
NdisClIncomingCallComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
NDIS_STATUS
NdisClAddParty(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  NDIS_HANDLE             ProtocolPartyContext,
    IN OUT PCO_CALL_PARAMETERS  CallParameters,
    OUT PNDIS_HANDLE            NdisPartyHandle
    );


EXPORT
NDIS_STATUS
NdisClDropParty(
    IN  NDIS_HANDLE             NdisPartyHandle,
    IN  PVOID                   Buffer      OPTIONAL,
    IN  UINT                    Size        OPTIONAL
    );


EXPORT
NDIS_STATUS
NdisClGetProtocolVcContextFromTapiCallId(
    IN  UNICODE_STRING          TapiCallId,
    OUT PNDIS_HANDLE            ProtocolVcContext
    );

//
// Call Manager Apis
//
EXPORT
NDIS_STATUS
NdisCmRegisterAddressFamily(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  PCO_ADDRESS_FAMILY      AddressFamily,
    IN  PNDIS_CALL_MANAGER_CHARACTERISTICS CmCharacteristics,
    IN  UINT                    SizeOfCmCharacteristics
    );


EXPORT
VOID
NdisCmOpenAddressFamilyComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             CallMgrAfContext
    );


EXPORT
VOID
NdisCmCloseAddressFamilyComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisAfHandle
    );


EXPORT
VOID
NdisCmRegisterSapComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisSapHandle,
    IN  NDIS_HANDLE             CallMgrSapContext
    );


EXPORT
VOID
NdisCmDeregisterSapComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisSapHandle
    );


EXPORT
NDIS_STATUS
NdisCmActivateVc(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN OUT PCO_CALL_PARAMETERS  CallParameters
    );


EXPORT
NDIS_STATUS
NdisCmDeactivateVc(
    IN  NDIS_HANDLE             NdisVcHandle
    );


EXPORT
VOID
NdisCmMakeCallComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  NDIS_HANDLE             NdisPartyHandle     OPTIONAL,
    IN  NDIS_HANDLE             CallMgrPartyContext OPTIONAL,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
VOID
NdisCmCloseCallComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL
    );


EXPORT
VOID
NdisCmAddPartyComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisPartyHandle,
    IN  NDIS_HANDLE             CallMgrPartyContext OPTIONAL,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
VOID
NdisCmDropPartyComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisPartyHandle
    );


EXPORT
NDIS_STATUS
NdisCmDispatchIncomingCall(
    IN  NDIS_HANDLE             NdisSapHandle,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
VOID
NdisCmDispatchCallConnected(
    IN  NDIS_HANDLE             NdisVcHandle
    );


EXPORT
VOID
NdisCmModifyCallQoSComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
VOID
NdisCmDispatchIncomingCallQoSChange(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PCO_CALL_PARAMETERS     CallParameters
    );


EXPORT
VOID
NdisCmDispatchIncomingCloseCall(
    IN  NDIS_STATUS             CloseStatus,
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PVOID                   Buffer      OPTIONAL,
    IN  UINT                    Size        OPTIONAL
    );


EXPORT
VOID
NdisCmDispatchIncomingDropParty(
    IN  NDIS_STATUS             DropStatus,
    IN  NDIS_HANDLE             NdisPartyHandle,
    IN  PVOID                   Buffer      OPTIONAL,
    IN  UINT                    Size        OPTIONAL
    );

//
// CONDIS 6.0 extensions
//

EXPORT
VOID
NdisCoSendNetBufferLists(
    IN  NDIS_HANDLE             NdisVcHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
NDIS_STATUS
NdisCoOidRequest(
    IN  NDIS_HANDLE             NdisBindingHandle,
    IN  NDIS_HANDLE             NdisAfHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
    IN OUT PNDIS_OID_REQUEST    NdisRequest
    );


EXPORT
VOID
NdisCoOidRequestComplete(
    IN  NDIS_STATUS             Status,
    IN  NDIS_HANDLE             NdisAfHandle,
    IN  NDIS_HANDLE             NdisVcHandle    OPTIONAL,
    IN  NDIS_HANDLE             NdisPartyHandle OPTIONAL,
    IN  PNDIS_OID_REQUEST       NdisRequest
    );


//
// Ndis Light Weight filters
// 

    
//
// init / de-init
//

#define NDIS_FILTER_ATTACH_PARAMETERS_REVISION_1     1

typedef struct _NDIS_FILTER_ATTACH_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
    NET_IFINDEX                 IfIndex;
    PNDIS_STRING                FilterModuleGuidName;
    PNDIS_STRING                MiniportInstanceName;
} NDIS_FILTER_ATTACH_PARAMETERS, *PNDIS_FILTER_ATTACH_PARAMETERS;

typedef
NDIS_STATUS
(*FILTER_ATTACH_HANDLER)(
    IN  NDIS_HANDLE                     NdisFilterHandle,
    IN  NDIS_HANDLE                     FilterDriverContext,
    IN  PNDIS_FILTER_ATTACH_PARAMETERS  AttachParameters
    );

typedef
NDIS_STATUS
(*FILTER_DETACH_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext
    );

typedef
NDIS_STATUS
(*FILTER_SET_FILTER_MODULE_OPTIONS_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext
    );


#define NDIS_FILTER_RESTART_PARAMETERS_REVISION_1     1

typedef struct _NDIS_FILTER_RESTART_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
    NET_IFINDEX                 IfIndex;
    NET_LUID                    NetLuid;
} NDIS_FILTER_RESTART_PARAMETERS, *PNDIS_FILTER_RESTART_PARAMETERS;

typedef
NDIS_STATUS
(*FILTER_RESTART_HANDLER)(
    IN  NDIS_HANDLE                     FilterModuleContext,
    IN  PNDIS_FILTER_RESTART_PARAMETERS RestartParameters
    );

#define NDIS_FILTER_PAUSE_PARAMETERS_REVISION_1     1

typedef struct _NDIS_FILTER_PAUSE_PARAMETERS
{
    NDIS_OBJECT_HEADER          Header;
} NDIS_FILTER_PAUSE_PARAMETERS, *PNDIS_FILTER_PAUSE_PARAMETERS;


typedef
NDIS_STATUS
(*FILTER_PAUSE_HANDLER)(
    IN  NDIS_HANDLE                     FilterModuleContext,
    IN  PNDIS_FILTER_PAUSE_PARAMETERS   PauseParameters
    );

//
// inbound requests/data
//

typedef
NDIS_STATUS
(*FILTER_REQUEST_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNDIS_OID_REQUEST       Request
    );    

typedef
VOID
(*FILTER_CANCEL_REQUEST_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNDIS_OID_REQUEST       Request
    );


typedef
VOID
(*FILTER_SEND_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  ULONG                   SendFlags,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*FILTER_CANCEL_SEND_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PVOID                   CancelId
    );

typedef
VOID
(*FILTER_RETURN_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*FILTER_SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  BOOLEAN                 DispatchLevel
    );

typedef
VOID
(*FILTER_RECEIVE_NET_BUFFER_LISTS_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_STATUS             Status,
    IN  BOOLEAN                 DispatchLevel
    );

typedef 
VOID
(*FILTER_PNP_EVENT_NOTIFY_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  NDIS_DEVICE_PNP_EVENT   DevicePnPEvent,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength
    );


typedef
VOID
(*FILTER_PNP_EVENT_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNET_PNP_EVENT          NetPnPEvent
    );


typedef
VOID
(*FILTER_STATUS_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNDIS_STATUS_INDICATION StatusIndication
    );


typedef
VOID
(*FILTER_REQUEST_COMPLETE_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PNDIS_OID_REQUEST       Request,
    IN  NDIS_STATUS             Status
    );

#define NDIS_FILTER_PARTIAL_CHARACTERISTICS_REVISION_1      1

typedef struct _NDIS_FILTER_PARTIAL_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                              Header; // Header.Type = NDIS_OBJECT_TYPE_FILTER_PARTIAL_CHARACTERISTICS
    ULONG                                           Flags;
    FILTER_SEND_NET_BUFFER_LISTS_HANDLER            SendNetBufferListsHandler;
    FILTER_SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER   SendNetBufferListsCompleteHandler;
    FILTER_RECEIVE_NET_BUFFER_LISTS_HANDLER         ReceiveNetBufferListsHandler;
    FILTER_RETURN_NET_BUFFER_LISTS_HANDLER          ReturnNetBufferListsHandler;
} NDIS_FILTER_PARTIAL_CHARACTERISTICS, *PNDIS_FILTER_PARTIAL_CHARACTERISTICS;


//
// filter co NDIS nadlers
//


typedef
NDIS_STATUS
(*FILTER_CO_CREATE_VC_HANDLER)(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  NDIS_HANDLE             NdisVcHandle,
    OUT PNDIS_HANDLE            FilterVcContext
    );

typedef
NDIS_STATUS
(*FILTER_CO_DELETE_VC_HANDLER)(
    IN  NDIS_HANDLE             FilterVcContext
    );

typedef
NDIS_STATUS
(*FILTER_CO_ACTIVATE_VC_HANDLER)(
    IN  NDIS_HANDLE             FilterVcContext,
    IN OUT PCO_CALL_PARAMETERS  CallParameters
    );

typedef
NDIS_STATUS
(*FILTER_CO_DEACTIVATE_VC_HANDLER)(
    IN  NDIS_HANDLE             FilterVcContext
    );

#define NDIS_FILTER_CO_CHARACTERISTICS_REVISION_1      1

typedef struct _NDIS_FILTER_CO_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                              Header; // Header.Type = NDIS_OBJECT_TYPE_CO_FILTER_CHARACTERISTICS
    ULONG                                           Flags;
    FILTER_CO_CREATE_VC_HANDLER                     CoCreateVcHandler;
    FILTER_CO_DELETE_VC_HANDLER                     CoDeleteVcHandler;
    FILTER_CO_ACTIVATE_VC_HANDLER                   CoActivateVcHandler;
    FILTER_CO_DEACTIVATE_VC_HANDLER                 CoDeactivateVcHandler;
} NDIS_FILTER_CO_CHARACTERISTICS, *PNDIS_FILTER_CO_CHARACTERISTICS;


#define NDIS_FILTER_CHARACTERISTICS_REVISION_1      1

typedef struct _NDIS_FILTER_DRIVER_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER                              Header;
    UCHAR                                           MajorNdisVersion;
    UCHAR                                           MinorNdisVersion;
    UCHAR                                           MajorDriverVersion;
    UCHAR                                           MinorDriverVersion;
    ULONG                                           Flags;
    NDIS_STRING                                     FriendlyName;
    NDIS_STRING                                     UniqueName;
    NDIS_STRING                                     ServiceName;
    SET_OPTIONS_HANDLER                             SetOptionsHandler;
    FILTER_SET_FILTER_MODULE_OPTIONS_HANDLER        SetFilterModuleOptionsHandler;
    FILTER_ATTACH_HANDLER                           AttachHandler;
    FILTER_DETACH_HANDLER                           DetachHandler;
    FILTER_RESTART_HANDLER                          RestartHandler;
    FILTER_PAUSE_HANDLER                            PauseHandler;
    FILTER_SEND_NET_BUFFER_LISTS_HANDLER            SendNetBufferListsHandler;
    FILTER_SEND_NET_BUFFER_LISTS_COMPLETE_HANDLER   SendNetBufferListsCompleteHandler;
    FILTER_RECEIVE_NET_BUFFER_LISTS_HANDLER         ReceiveNetBufferListsHandler;
    FILTER_RETURN_NET_BUFFER_LISTS_HANDLER          ReturnNetBufferListsHandler;
    FILTER_REQUEST_HANDLER                          RequestHandler;
    FILTER_REQUEST_COMPLETE_HANDLER                 RequestCompleteHandler;
    FILTER_CANCEL_REQUEST_HANDLER                   CancelRequestHandler;
    FILTER_PNP_EVENT_NOTIFY_HANDLER                 PnPEventNotifyHandler;
    FILTER_PNP_EVENT_HANDLER                        PnPEventHandler;  
    FILTER_STATUS_HANDLER                           StatusHandler;
    FILTER_CANCEL_SEND_HANDLER                      CancelSendNetBufferListsHandler;
} NDIS_FILTER_DRIVER_CHARACTERISTICS, *PNDIS_FILTER_DRIVER_CHARACTERISTICS;

#define NDIS_FILTER_ATTRIBUTES_REVISION_1       1

typedef struct _NDIS_FILTER_ATTRIBUTES
{
    NDIS_OBJECT_HEADER                      Header;
    ULONG                                   Flags;
} NDIS_FILTER_ATTRIBUTES, *PNDIS_FILTER_ATTRIBUTES;


EXPORT
NDIS_STATUS
NdisFRegisterFilterDriver(
    IN  PDRIVER_OBJECT                          DriverObject,
    IN  NDIS_HANDLE                             FilterDriverContext,
    IN  PNDIS_FILTER_DRIVER_CHARACTERISTICS     FilterDriverCharacteristics,
    OUT PNDIS_HANDLE                            NdisFilterDriverHandle
    );


EXPORT
VOID
NdisFDeregisterFilterDriver(
    IN NDIS_HANDLE                      NdisFilterDriverHandle
    );
    
EXPORT
NDIS_STATUS
NdisFSetAttributes(
    IN  NDIS_HANDLE                     NdisFilterHandle,
    IN  NDIS_HANDLE                     FilterModuleContext,
    IN  PNDIS_FILTER_ATTRIBUTES         FilterAttributes
    );    

EXPORT
NDIS_STATUS
NdisFRestartFilter(
    IN  NDIS_HANDLE             NdisFilterHandle
    );

EXPORT
VOID
NdisFSendNetBufferLists(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  ULONG                   SendFlags,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisFReturnNetBufferLists(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisFSendNetBufferListsComplete(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  BOOLEAN                 DispatchLevel
    );

EXPORT
VOID
NdisFIndicateReceiveNetBufferLists(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNET_BUFFER_LIST        NetBufferLists,
    IN  NDIS_STATUS             Status,
    IN  BOOLEAN                 DispatchLevel
    );


EXPORT
NDIS_STATUS
NdisFRequest(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNDIS_OID_REQUEST       Request
    );

EXPORT
VOID
NdisFRequestComplete(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNDIS_OID_REQUEST       Request,
    IN  NDIS_STATUS             Status
    );

EXPORT
VOID
NdisFIndicateStatus(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNDIS_STATUS_INDICATION StatusIndication
    );

EXPORT
VOID
NdisFPnPEventComplete(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNET_PNP_EVENT          NetPnPEvent,
    IN  NDIS_STATUS             Status
    );


EXPORT
VOID
NdisFRestartComplete(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  NDIS_STATUS             Status
    );

EXPORT
VOID
NdisFPauseComplete(
    IN  NDIS_HANDLE             NdisFilterHandle
    );


EXPORT
NDIS_STATUS
NdisFEnumerateFilters(
    IN      NDIS_HANDLE     NdisFilterHandle,
    IN      PVOID           InformationBuffer,
    IN      ULONG           InformationBufferLength,
    IN OUT  PULONG          BytesNeeded,
    IN OUT  PULONG          BytesWritten
    );

EXPORT
VOID
NdisFPnPEventNotify(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  NDIS_DEVICE_PNP_EVENT   DevicePnPEvent,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength
    );

EXPORT
VOID
NdisFPnPEvent(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNET_PNP_EVENT          NetPnPEvent
    );


EXPORT
VOID
NdisFCancelSendNetBufferLists(
    IN  NDIS_HANDLE     NdisFilterHandle,
    IN  PVOID           CancelId
    );
    
EXPORT
VOID
NdisFCancelRequest(
    IN  NDIS_HANDLE             NdisFilterHandle,
    IN  PNDIS_OID_REQUEST       Request
    );


//
// NDIS IF data structures, function prototypes and macros
//

typedef enum _NET_IF_GET_TYPE
{
    NIGT_GET_EXACT = 0,
    NIGT_GET_FIRST = 1,
    NIGT_GET_NEXT = 2
} NET_IF_GET_TYPE, *PNET_IF_GET_TYPE;

typedef
NDIS_STATUS
(*IFP_QUERY_OBJECT)(
    IN NDIS_HANDLE          ProviderIfContext,
    IN NET_IF_OBJECT_ID     ObjectId,
    IN ULONG                Index,
    IN NET_IF_GET_TYPE      GetType,
    IN ULONG                InputBufferLength,
    IN PVOID                pInputBuffer OPTIONAL,
    IN OUT PULONG           pOutputBufferLength,
    OUT PVOID               pOutputBuffer
    );

typedef enum _NET_IF_SET_TYPE
{
    NIST_SET_DEFAULT = 0,       // Set only if instance already exists
    NIST_SET_CREATE_ONLY = 1,   // Create only if instance not already exists
    NIST_SET_CREATE_OR_SET = 2, // Set if instance exists, create if not
    NIST_SET_DELETE = 3         // Delete this instance
} NET_IF_SET_TYPE, *PNET_IF_SET_TYPE;

typedef
NDIS_STATUS
(*IFP_SET_OBJECT)(
    IN NDIS_HANDLE          ProviderIfContext,
    IN NET_IF_OBJECT_ID     ObjectId,
    IN ULONG                Index,
    IN NET_IF_SET_TYPE      SetType,
    IN ULONG                InputBufferLength,
    IN PVOID                pInputBuffer
    );


typedef struct _NDIS_IF_PROVIDER_CHARACTERISTICS
{
    NDIS_OBJECT_HEADER      Header;

    //
    // Generic query and set handlers:
    //
    IFP_QUERY_OBJECT        QueryObjectHandler;
    IFP_SET_OBJECT          SetObjectHandler;

    PVOID                   Reserved1;
    PVOID                   Reserved2;

} NDIS_IF_PROVIDER_CHARACTERISTICS, *PNDIS_IF_PROVIDER_CHARACTERISTICS;

//
// NET_IF_INFORMATION is passed to NdisIfRegisterInterface
//
typedef struct _NET_IF_INFORMATION
{
    NDIS_OBJECT_HEADER      Header;
    ULONG                   Flags;              // Misc. information
    NET_PHYSICAL_LOCATION   PhysicalLocation;   // physical location on machine
    ULONG                   WanTunnelType;      // tunnelIfEncapsMethod (RFC 2667)
    ULONG                   PortNumber;         // for WAN devices.
    NET_IF_ACCESS_TYPE      AccessType;
    NET_IF_DIRECTION_TYPE   DirectionType;
    NET_IF_CONNECTION_TYPE  ConnectionType;
    BOOLEAN                 ifConnectorPresent;
    USHORT                  PhysAddressLength;  // in bytes (ifPhysAddress). this is -current- mac address
    USHORT                  PhysAddressOffset;  // from beginning of this struct
    USHORT                  PermanentPhysAddressOffset;  // from beginning of this struct
    //
    //  The "friendly name" represents ifDescr:
    //
    USHORT                  FriendlyNameLength; // in bytes
    USHORT                  FriendlyNameOffset; // from beginning of this struct
    GUID                    InterfaceGuid;
    NET_IF_NETWORK_GUID     NetworkGuid;
} NET_IF_INFORMATION, *PNET_IF_INFORMATION;

EXPORT
NDIS_STATUS
NdisIfRegisterProvider(
    IN  PNDIS_IF_PROVIDER_CHARACTERISTICS   ProviderCharacteristics,
    IN  NDIS_HANDLE                         IfProviderContext,
    OUT PNDIS_HANDLE                        pNdisIfProviderHandle
    );

EXPORT
VOID
NdisIfDeregisterProvider(
    IN NDIS_HANDLE          NdisProviderHandle
    );

EXPORT
NDIS_STATUS
NdisIfAllocateNetLuidIndex(
    IN  NET_IFTYPE          ifType,
    OUT PUINT32             pNetLuidIndex
    );

EXPORT
NDIS_STATUS
NdisIfFreeNetLuidIndex(
    IN NET_IFTYPE           ifType,
    IN UINT32               NetLuidIndex
    );

EXPORT
NDIS_STATUS
NdisIfRegisterInterface(
    IN NDIS_HANDLE          NdisProviderHandle,
    IN NET_LUID             NetLuid,
    IN NDIS_HANDLE          ProviderIfContext,
    IN PNET_IF_INFORMATION  pIfInfo,
    OUT PNET_IFINDEX        pfIndex
    );

EXPORT
VOID
NdisIfDeregisterInterface(
    IN NET_IFINDEX          ifIndex
    );

EXPORT
NDIS_STATUS
NdisIfGetInterfaceIndexFromNetLuid(
    IN  NET_LUID            NetLuid,
    OUT PNET_IFINDEX        pIfIndex
    );

EXPORT
NDIS_STATUS
NdisIfGetNetLuidFromInterfaceIndex(
    IN  NET_IFINDEX         ifIndex,
    OUT PNET_LUID           pNetLuid
    );

EXPORT
NDIS_STATUS
NdisIfQueryBindingIfIndex(
    IN  NDIS_HANDLE         NdisBindingHandle,
    OUT PNET_IFINDEX        pIfIndex,
    OUT PNET_LUID           pNetLuid,
    OUT PNET_IFINDEX        pLowestIfIndex,
    OUT PNET_LUID           pLowestNetLuid
    );

EXPORT
NDIS_STATUS
NdisMQueryAdapterIfIndex(
    IN  NDIS_HANDLE         NdisMiniportHandle,
    OUT PNET_IFINDEX        pIfIndex,
    OUT PNET_LUID           pNetLuid
    );

EXPORT
NDIS_STATUS
NdisIfAddIfStackEntry(
    IN NDIS_HANDLE          NdisProviderHandle,
    IN NET_IFINDEX          HigherLayerIfIndex,
    IN NET_IFINDEX          LowerLayerIfIndex
    );

EXPORT
VOID
NdisIfDeleteIfStackEntry(
    IN NDIS_HANDLE          NdisProviderHandle,
    IN NET_IFINDEX          HigherLayerIfIndex,
    IN NET_IFINDEX          LowerLayerIfIndex
    );




#if !defined(NDIS_WRAPPER)

typedef struct _NDIS_COMMON_OPEN_BLOCK
{
    PVOID                       MacHandle;          // needed for backward compatibility
 
    NDIS_HANDLE                 BindingHandle;
    NDIS_HANDLE                 Reserved6;
    NDIS_HANDLE                 Reserved7;
    NDIS_HANDLE                 Reserved8;

    PVOID                       Reserved9;
    NDIS_HANDLE                 Reserved10;

    NDIS_HANDLE                 Reserved11;
    BOOLEAN                     Reserved12;
    BOOLEAN                     Reserved2;
    BOOLEAN                     Reserved3;
    BOOLEAN                     Reserved4;
    PVOID                       Reserved13;
    KSPIN_LOCK                  Reserved5;
    NDIS_HANDLE                 Reserved14;

    //
    // These are referenced by the macros used by protocols to call.
    // All of the ones referenced by the macros are internal NDIS handlers for the miniports
    //
    union
    {
        SEND_HANDLER            SendHandler;
        WAN_SEND_HANDLER        WanSendHandler;
    };
    TRANSFER_DATA_HANDLER       TransferDataHandler;

    //
    // These are referenced internally by NDIS
    //
    SEND_COMPLETE_HANDLER       SendCompleteHandler;
    TRANSFER_DATA_COMPLETE_HANDLER TransferDataCompleteHandler;
    RECEIVE_HANDLER             ReceiveHandler;
    RECEIVE_COMPLETE_HANDLER    ReceiveCompleteHandler;
    WAN_RECEIVE_HANDLER         WanReceiveHandler;
    REQUEST_COMPLETE_HANDLER    RequestCompleteHandler;

    //
    // NDIS 4.0 extensions
    //
    RECEIVE_PACKET_HANDLER      ReceivePacketHandler;
    SEND_PACKETS_HANDLER        SendPacketsHandler;

    //
    // More Cached Handlers
    //
    RESET_HANDLER               ResetHandler;
    REQUEST_HANDLER             RequestHandler;
    RESET_COMPLETE_HANDLER      ResetCompleteHandler;
    STATUS_HANDLER              StatusHandler;
    STATUS_COMPLETE_HANDLER     StatusCompleteHandler;

}NDIS_COMMON_OPEN_BLOCK, *PNDIS_COMMON_OPEN_BLOCK;
//
// one of these per open on an adapter/protocol
//
struct _NDIS_OPEN_BLOCK
{
#ifdef __cplusplus
    NDIS_COMMON_OPEN_BLOCK NdisCommonOpenBlock;
#else
    NDIS_COMMON_OPEN_BLOCK;
#endif

};

#endif


#endif // _NDIS_

