/*++

Copyright (c) 2003 Microsoft Corporation. All rights reserved.

Module Name:

    rpcsal.h

Abstract:

    Definitions for SAL related annotations

--*/

#pragma once


#include <specstrings.h>


#ifdef  __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

#if (_MSC_VER >= 1000) && !defined(MIDL_PASS) && defined(_PREFAST_)

#define __begin                 __declspec("SAL_begin")
#define __end                   __declspec("SAL_end")

#define __dot                   __declspec("SAL_dot")
#define __index                 __declspec("SAL_index")

#define __init                  __declspec("SAL_init")
#define __maybeinit             __declspec("SAL_maybeinit")

#define __maybealiased          __declspec("SAL_maybealiased")
#define __notaliased            __declspec("SAL_notaliased")

#define __pattern               __declspec("SAL_pattern")
#define __spec                  __declspec("SAL_spec")
#define __state(state)          __declspec("SAL_state(" SPECSTRINGIZE(state) ")")

#define __readableToElementCount(size) __declspec("SAL_readableTo(elementCount(" SPECSTRINGIZE(size) "))")
#define __readableToSentinel(sentinel) __declspec("SAL_readableTo(sentinel(" SPECSTRINGIZE(sentinel) "))")
#define __writableToElementCount(size) __declspec("SAL_writableTo(elementCount(" SPECSTRINGIZE(size) "))")

#define __specoverride(state)   __declspec("SAL_specOverride(" SPECSTRINGIZE(state) ")")

typedef void *                  SAL_ANY_SCALAR;
typedef void *                  SAL_ANY_POINTER;
typedef void *                  SAL_ANY_STRUCT;
typedef void *                  SAL_ANY_ARRAY;


__spec struct RPCinit
{
   __pattern
   __maybeinit
   SAL_ANY_SCALAR RPCinit_scalardefault;

   __pattern
   __init
//   RPC_POINTER_DEFAULT
   __readableToElementCount(1)
   __deref __state(RPCinit)
   SAL_ANY_POINTER RPCinit_pointerdefault;

   __pattern

// BUGBUG:  SAL grammar (section 2.1.1) indicates dot(field) and dot are dot
// acceptable; how do we do this with macros ?  (same for index).

   __dot __state(RPCinit)
   SAL_ANY_STRUCT RPCinit_structdefault;

   __pattern
   __readableToElementCount(explicitlength)
   __index __state(RPCinit)
   SAL_ANY_ARRAY RPCinit_embeddedarraydefault;
};

__spec struct VALID
{
   __pattern
   __init
   SAL_ANY_SCALAR scalardefault;

   __pattern
   __init
//   RPC_POINTER_DEFAULT
   __readableToElementCount(1)
   __deref __state(NESTEDVALID)
   SAL_ANY_POINTER pointerdefault;

   __pattern
   __dot __state(NESTEDVALID)
   SAL_ANY_STRUCT structdefault;

   __pattern
   __readableToElementCount(__explicitarraylength)
   __index __state(NESTEDVALID)
   SAL_ANY_ARRAY arraydefault;
};

//#define __state(x)                  __maybenull

#define __RPC_ref_pointer           __notaliased __notnull

#define __RPC_unique_pointer        __notaliased __maybenull

#define __RPC_full_pointer          __maybenull __maybealiased

#define __RPC_deref                 __deref

#define __RPC_in                    __pre __state(VALID)

#define __RPC_out                   __notnull \
                                    __pre __deref __state(RPCinit) \
                                    __post __deref __state(VALID)

#define __RPC_inout                 __pre __state(VALID) \
                                    __post __state(VALID)

#define RPC_range(min,max)

#define __RPC_sizeis(x)             __readableToElementCount(x)

#define __RPC_lengthis(x)           __readableToElementCount(x)

#define __RPC_inout_sizeis(x)       __RPC_sizeis(x)

#define __RPC_out_sizeis(x)         __begin  \
                                        __pre __readableToElementCount(x) \
                                        __post __readableToElementCount(x) \
                                    __end
#define __RPC_embedded_sizeis(x)    __readableToElementCount(x)

#define __RPC_embedded_lengthis(x)  __readableToElementCount(x)

#define __RPC_out_sizeis_lengthis(x, y) \
                                    __begin \
                                        __pre __readableToElementCount(x) \
                                        __post __readableToElementCount(y) \
                                    __end

#define __RPC_sizeis_lengthis(x, y) \
                                    __begin \
                                        __writableToElementCount(x) \
                                        __readableToElementCount(y) \
                                    __end

// BUGBUG:  something missing here ?
#define __RPC_embedded_sizeis_lengthis(x, y) \
                                    __readableTo(x)

#define __RPC_out_sized_string(x) \
                                    __begin \
                                        __pre __writableToElementCount(x) \
                                        __post __readableToSentinel(0) \
                                    __end

#define __RPC_string()           __readableToSentinel(0)
#define __RPC_out_string()           __readableToSentinel(0)
#define __RPC_sized_string(x)    __readableToSentinel(0)

#define __RPC_begin     __begin
#define __RPC_end       __end

#else   // not prefast

#define __state(x)

#define __RPC_ref_pointer

#define __RPC_unique_pointer

#define __RPC_full_pointer

#define __RPC_deref

#define __RPC_in

#define __RPC_out

#define __RPC_inout

#define RPC_range(min,max)

#define __RPC_sizeis(x)
#define __RPC_lengthis(x)
#define __RPC_sizeis_lengthis(x, y)
#define __RPC_inout_sizeis(x)
#define __RPC_out_sizeis(x)


#define __RPC_out_sizeis_lengthis(x, y)
#define __RPC_inout_sizeis_lengthis(x, y)

#define __RPC_embedded_sizeis(x)
#define __RPC_embedded_lengthis(x)
#define __RPC_embedded_sizeis_lengthis(x, y)

#define __RPC_out_sized_string(x)

#define __RPC_string()
#define __RPC_sized_string(x)
#define __RPC_out_string()    

#define __RPC_begin
#define __RPC_end

#endif

#ifdef  __cplusplus
}
#endif


