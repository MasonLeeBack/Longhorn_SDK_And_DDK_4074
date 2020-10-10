/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    netiok.h

Abstract:

    This module contains the kernel mode definitions and structures for the
    network I/O subsystem.

Environment:

    kernel mode only

--*/

#ifndef _NETIOK_
#define _NETIOK_
#pragma once

#include <netiodef.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(push)
#pragma warning(disable:4200) // zero-sized array in struct/union


typedef ULONG POOL_TAG;

#if DBG
#define PASSIVE_CODE() \
    if (KeGetCurrentIrql() > PASSIVE_LEVEL) { \
        KeBugCheckEx(DRIVER_IRQL_NOT_LESS_OR_EQUAL, (ULONG_PTR)KeGetCurrentIrql(), PASSIVE_LEVEL, 0, 0); \
    }
#define DISPATCH_CODE() \
    if (KeGetCurrentIrql() < DISPATCH_LEVEL) { \
        KeBugCheckEx(IRQL_NOT_GREATER_OR_EQUAL, (ULONG_PTR)KeGetCurrentIrql(), DISPATCH_LEVEL, 0, 0); \
    }
#else
#define PASSIVE_CODE()
#define DISPATCH_CODE()
#endif


//
// Deleting = TRUE, ReferenceCount = 0;
//
#define RO_VALUE_INVALID 1

//
// Deleting = FALSE, ReferenceCount = 1;
//
#define RO_VALUE_INITIALIZED 2

typedef union _REFERENCE_OBJECT {
    struct {
        ULONG Deleting : 1;         // least significant bit
        ULONG ReferenceCount : 30;  // mid 30 bits
        ULONG Overflow : 1;         // most significant bit
    };
    LONG Value;                     // ReferenceCount * 2 + Deleting
} REFERENCE_OBJECT, *PREFERENCE_OBJECT;


__inline
VOID
FASTCALL
RoInitialize(
    OUT PREFERENCE_OBJECT ReferenceObject
    )
/*++

Routine Description:

    This function is called to initialize a REFERENCE_OBJECT.

Arguments:

    ReferenceObject - Returns an initialized reference object (stored at
        the caller supplied address).

Return Value:

    None.

--*/
{
    //
    // ReferenceObject->Deleting = FALSE;
    // ReferenceObject->ReferenceCount = 1;
    //
    ReferenceObject->Value = RO_VALUE_INITIALIZED;
}


__inline
VOID
FASTCALL
RoInitializeAsInvalid(
    OUT PREFERENCE_OBJECT ReferenceObject
    )
/*++

Routine Description:

    This function is called to initialize a REFERENCE_OBJECT to an invalid
    state.  Subsequent calls to RoReference will always return FALSE until
    RoInitialize is called.

Arguments:

    ReferenceObject - Returns an initialized reference object (stored at
        the caller supplied address).

Return Value:

    None.

--*/
{
    //
    // ReferenceObject->Deleting = TRUE;
    // ReferenceObject->ReferenceCount = 0;
    //
    ReferenceObject->Value = RO_VALUE_INVALID;
}


__inline
BOOLEAN
FASTCALL
RoInitializeIfInvalid(
    IN OUT PREFERENCE_OBJECT ReferenceObject
    )
/*++

Routine Description:

    This function is called to initialize a REFERENCE_OBJECT,
    but only if it is found to be in an invalid state.

Arguments:

    ReferenceObject - Supplies a reference object which is returned initialized
        if it is in an invalid state.

Return Value:

    TRUE if the reference object was successfully initialized.
    FALSE if the reference object was already initialized.

--*/
{
    LONG Old;
    
    Old = InterlockedCompareExchange(
        &(ReferenceObject->Value), RO_VALUE_INITIALIZED, RO_VALUE_INVALID);

    return (BOOLEAN) (Old == RO_VALUE_INVALID);
}


__inline
BOOLEAN
FASTCALL
RoIsInitialized(
    IN PREFERENCE_OBJECT ReferenceObject
    )
/*++

Routine Description:

    This function is called to determine if a REFERENCE_OBJECT is initialized.

Arguments:

    ReferenceObject - Supplies a reference object.

Return Value:

    TRUE if the reference object was initialized, FALSE if not.

--*/
{
    return (BOOLEAN) (ReferenceObject->Value != RO_VALUE_INVALID);
}


__inline
BOOLEAN
FASTCALL
RoUnInitialize(
    IN OUT PREFERENCE_OBJECT ReferenceObject
    )
/*++

Routine Description:

    This function is called to start uninitializing a REFERENCE_OBJECT.
    It might indicate completion asynchronously.

Arguments:

    ReferenceObject - Supplies the reference object to uninitialize.
        Returns its update.

Return Value:

    TRUE if uninitialization is complete.  FALSE if completion will be
    signalled asynchronously (from an RoDereference call).

--*/
{
    REFERENCE_OBJECT New;

    //
    // ReferenceObject->Deleting = TRUE;    // Mark Deleting
    // ReferenceObject->ReferenceCount--;   // Decrement ReferenceCount
    // The former is achieved by adding 1 to the reference object value
    // and the latter by subtracting 2 from it.  We decrement by 1 to
    // achieve the combined effect!
    //
    New.Value = InterlockedDecrement(&(ReferenceObject->Value));

    //
    // Deleting should never get marked more than once.  A successive
    // attempt to do so would flip this bit resulting in an assert.
    //
    ASSERT(New.Deleting);

    //
    // If ReferenceCount falls to 0 and Deleting has been set, then
    // indicate to the caller that the object can now be deleted.
    //
    if (New.Value == 1) {
        return TRUE;
    }
    return FALSE;
}


__inline
BOOLEAN
FASTCALL
RoReInitialize(
    IN OUT PREFERENCE_OBJECT ReferenceObject
    )
/*++

Routine Description:

    This function is called to re-initialize a REFERENCE_OBJECT. 

Arguments:

    ReferenceObject - Supplies the reference object to re-initialize.

Return Value:

    TRUE if uninitialization was complete when the re-initialization happened.
    Otherwise FALSE.

--*/
{
    REFERENCE_OBJECT New;

    //
    // ReferenceObject->Deleting = FALSE;    // Unmark Deleting flag
    // ReferenceObject->ReferenceCount++;    // Increment ReferenceCount
    // The former is achieved by subtracting 1 from the reference object value
    // and the latter by adding 2 to it.  We increment by 1 to
    // achieve the combined effect!
    //
    New.Value = InterlockedIncrement(&(ReferenceObject->Value));

    //
    // This should be called only if the object is guaranteed to have the
    // Deleting flag set. 
    //
    ASSERT(!New.Deleting);

    //
    // If ReferenceCount becomes the same as RO_VALUE_INITIALIZED as a result
    // of this operation, then it was uninitialized before.  So, return TRUE.
    //
    if (New.Value == RO_VALUE_INITIALIZED) {
        return TRUE;
    }
    return FALSE;
}


__inline
VOID
FASTCALL
RoReferenceValidObject(
    IN OUT PREFERENCE_OBJECT ReferenceObject,
    IN ULONG Count
    )
/*++

Routine Description:

    This function is called to reference a REFERENCE_OBJECT that is guaranteed
    to be valid, for example when the caller already holds a reference.
    This ensures that we can safely add more references.
    
Arguments:

    ReferenceObject - Supplies the reference object to reference.
        Returns its update.

    Count - Supplies the number of references to take.
    
Return Value:

    None.
    
--*/
{
    REFERENCE_OBJECT Old;
    
    ASSERT(Count < 0x40000000); // 2^30.

    //
    // ReferenceObject.ReferenceCount += Count;
    // This is achieved by adding 2*Count to the ReferenceObject value.
    //
    Old.Value = InterlockedExchangeAdd(
        &(ReferenceObject->Value),  (2 * Count));

    //
    // InterlockedExchangeAdd returns the original value!
    // The reference object must not have been invalid.
    //
    ASSERT(Old.Value != RO_VALUE_INVALID);

    //
    // Finally, this is the affect our operation had.
    // Do the number of outstanding references exceed our limit?
    // That would cause the most significant bit to get set!
    //
    Old.Value += (2 * Count);
    ASSERT(!Old.Overflow);
}


__inline
BOOLEAN
FASTCALL
RoReferenceMultiple(
    IN OUT PREFERENCE_OBJECT ReferenceObject,
    IN ULONG Count
    )
/*++

Routine Description:

    This function is called to reference a REFERENCE_OBJECT.

Arguments:

    ReferenceObject - Supplies the reference object to reference.
        Returns its update.

    Count - Supplies the number of references to take.
    
Return Value:

    TRUE if the reference object was successfully referenced.  FALSE if
    the reference object is being uninitialized and cannot be referenced.

--*/
{
    REFERENCE_OBJECT Snapshot, Old, New;

    ASSERT(Count < 0x40000000); // 2^30.
    
    do {
        //
        // Take a snapshot of the current value.
        //
        Snapshot.Value = ReferenceObject->Value;

        //
        // Fail if Deleting.
        //
        if (Snapshot.Deleting) {
            return FALSE;
        }

        //
        // New.Deleting = Snapshot.Deleting;
        // New.ReferenceCount = Snapshot.ReferenceCount + Count;
        // This is achieved by adding 2*Count to the snapshot value.
        //
        New.Value = Snapshot.Value + (2 * Count);

        //
        // Do the number of outstanding references exceed our limit?
        // That would cause the most significant bit to get set!
        //
        ASSERT(!New.Overflow);

        //
        // Update ReferenceCount, but only if the current value is the
        // same as that obtained in the snapshot.  Hence this operation
        // will fail if the reference object has been marked Deleting.
        //
        Old.Value = InterlockedCompareExchange(
            &(ReferenceObject->Value), New.Value, Snapshot.Value);

        //
        // Repeat until the ReferenceCount is successfully updated or
        // the Deleting bit is observed to be set.
        //
    } while (Old.Value != Snapshot.Value);

    return TRUE;
}

#define RoReference(ReferenceObject)    \
    RoReferenceMultiple((ReferenceObject), 1)


__inline
BOOLEAN
FASTCALL
RoDereferenceMultiple(
    IN OUT PREFERENCE_OBJECT ReferenceObject,
    IN ULONG Count
    )
/*++

Routine Description:

    This function is called to dereference a REFERENCE_OBJECT.

Arguments:

    ReferenceObject - Supplies the reference object to dereference.
        Returns its update.

    Count - Supplies the number of references to remove.
        
Return Value:

    TRUE to signal completion of a previous uninitialization request.
    FALSE otherwise.

--*/
{
    REFERENCE_OBJECT New;

    ASSERT(Count < 0x40000000);
    
    //
    // ReferenceObject->ReferenceCount -= Count;
    // This is achieved by subtracting (2 * Count).
    //
    New.Value = InterlockedExchangeAdd(
        &(ReferenceObject->Value), -(2 * (LONG) Count));

    //
    // InterlockedExchangeAdd returns the original value!
    //
    New.Value -= 2 * (LONG) Count;
        
    //
    // Did we take away more references than we actually had?
    // That would have caused the most significant bit to get set!
    //
    ASSERT(!New.Overflow);

    //
    // ReferenceCount should never fall to 0 before Deleting gets set.
    //
    ASSERT(New.Value != 0);

    //
    // If ReferenceCount falls to 0 and Deleting has been set, then
    // indicate to the caller that the object can now be deleted.
    //
    if (New.Value == 1) {
        return TRUE;
    }
    return FALSE;
}

#define RoDereference(ReferenceObject)  \
    RoDereferenceMultiple((ReferenceObject), 1)


#ifndef USER_MODE
#include <ndis.h>
#else
#include <ndisuser.h>
#endif
//
// DUMMY_VA is the argument we pass as the base address to MmSizeOfMdl when we
// haven't allocated space yet.  (PAGE_SIZE - 1) gives a worst case value for
// number of pages required.
//
#define DUMMY_VA UlongToPtr(PAGE_SIZE - 1)

//
// PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE
//
// Define a prototype for the NetBufferList completion routine.
//
// Invoked when the last reference to a (chain of) NetBufferLists is released.
// In case of Clones, Fragments, and Reassemblies, the MDL chain inherited from
// the parent NetBufferList may have been freed (since the reference to Parent
// is released before the CompletionRoutine is invoked).
//
// The completion routine is guaranteed to be called without any lock held.
//

typedef
VOID
(NTAPI NETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE)(
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN ULONG Count,
    IN BOOLEAN DispatchLevel
    );

typedef NETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE
    *PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE;

//
// Protocol specific NET_BUFFER_LIST flags used by NETIO.
//

//
// Reserved for use by NAT.
//

#define NBL_NAT_RESERVED 0x01000000

//
// Reserved for use by WFP.
//

#define NBL_WFP_RESERVED 0x02000000

//
// Indicates that the stack can hang onto that NET_BUFFER_LIST indefinitely
// (because the NET_BUFFER_LIST and its resources were allocated by the stack).
//

#define NBL_STACK_OWNED 0x10000000

//
// Indicates that the NET_BUFFER_LIST & its resources are owned by a miniport.
//

#define NBL_MINIPORT_OWNED 0x20000000

//
// Indicates that the NET_BUFFER_LIST was received link-layer unicast.
//

#define NBL_LINK_LAYER_UNICAST 0x40000000

//
// Reserved for internal use within a component.
//

#define NBL_RESERVED 0x80000000

//
// Routines used to set and query the NetBufferList context.
//

VOID
NetioInitializeNetBufferListContext(
    IN PNET_BUFFER_LIST NetBufferList,
    IN PNET_BUFFER_LIST Parent,
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext
    );

VOID
NetioUpdateNetBufferListContext(
    IN PNET_BUFFER_LIST NetBufferList,
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext
    );

PVOID
NetioQueryNetBufferListCompletionContext(
    IN PNET_BUFFER_LIST NetBufferList
    );

PNET_BUFFER_LIST
NetioQueryNetBufferListParent(
    IN PNET_BUFFER_LIST NetBufferList
    );


//
// Routines used to reference or dereference a NetBufferList.
//

VOID
NetioReferenceNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList
    );

VOID
NetioDereferenceNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN BOOLEAN DispatchLevel
    );

ULONG
NetioReferenceNetBufferListChain(
    IN PNET_BUFFER_LIST NetBufferListChain
    );

ULONG
NetioDereferenceNetBufferListChain(
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN BOOLEAN DispatchLevel
    );


//
// Routines used to manipulate or query a NetBuffer's MDL Chain.
//

VOID
NetioExpandNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN PMDL MdlChain,
    IN ULONG Length
    );

VOID
NetioExtendNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN ULONG AdditionalLength
    );

VOID
NetioTruncateNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN ULONG Length
    );

ULONG
NetioQueryNetBufferOriginalDataLength(
    IN PNET_BUFFER NetBuffer
    );


//
// Routines used to restore the NetBuffer(List) to its former glory.
//

VOID
NetioRestoreNetBuffer(
    IN PNET_BUFFER NetBuffer
    );

VOID
NetioRestoreNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList
    );


//
// Default completion functions.
//

VOID
NTAPI
NetioCompleteNetBufferListChain(
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN ULONG Count,
    IN BOOLEAN DispatchLevel
    );

VOID
NTAPI
NetioCompleteNetBufferAndNetBufferListChain(
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN ULONG Count,
    IN BOOLEAN DispatchLevel
    );

VOID
NTAPI
NetioCompleteCopyNetBufferListChain(
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN ULONG Count,
    IN BOOLEAN DispatchLevel
    );

VOID
NTAPI
NetioCompleteCloneNetBufferListChain(
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN ULONG Count,
    IN BOOLEAN DispatchLevel
    );


//
// Functions to allocate and free resources.
// Most of these are wrappers for NDIS NetBufferList library functions.
//

VOID
NetioInitializeMdl(
    IN PMDL Mdl,
    IN ULONG ByteCount,
    IN ULONG InitialHeaderSize
    );

PMDL
NetioAllocateMdl(
    IN OUT PULONG BufferSize
    );

VOID
NetioFreeMdl(
    IN PMDL Mdl
    );

PNET_BUFFER
NetioAllocateNetBuffer(
    IN PMDL MdlChain,
    IN ULONG DataOffset,
    IN ULONG DataLength,
    IN BOOLEAN DispatchLevel
    );

VOID
NetioFreeNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceNetBufferList(
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext,
    IN BOOLEAN DispatchLevel
    );

VOID
NetioFreeNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceNetBufferAndNetBufferList(
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext,
    IN PMDL MdlChain,
    IN ULONG DataOffset,
    IN ULONG DataLength,
    IN BOOLEAN DispatchLevel
    );

VOID
NetioFreeNetBufferAndNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceCopyNetBufferListEx(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext,
    IN BOOLEAN DispatchLevel
    );

__inline
PNET_BUFFER_LIST
NetioAllocateAndReferenceCopyNetBufferList(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN BOOLEAN DispatchLevel
    )
{
    return NetioAllocateAndReferenceCopyNetBufferListEx(
        OriginalNetBufferList,
        NetioCompleteCopyNetBufferListChain,
        NULL,
        DispatchLevel);
}

VOID
NetioFreeCopyNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceCloneNetBufferListEx(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext,
    IN BOOLEAN DispatchLevel
    );

__inline
PNET_BUFFER_LIST
NetioAllocateAndReferenceCloneNetBufferList(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN BOOLEAN DispatchLevel
    )
{
    return NetioAllocateAndReferenceCloneNetBufferListEx(
        OriginalNetBufferList,
        NetioCompleteCloneNetBufferListChain,
        NULL,
        DispatchLevel);
}

VOID
NetioFreeCloneNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceVacantNetBufferList(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN ULONG TrailerLength,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceFragmentNetBufferList(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN ULONG StartOffset,
    IN ULONG MaximumLength,
    IN ULONG DataOffsetDelta,
    IN ULONG DataBackFill,
    IN BOOLEAN DispatchLevel
    );

PNET_BUFFER_LIST
NetioAllocateAndReferenceReassembledNetBufferList(
    IN PNET_BUFFER_LIST OriginalNetBufferList,
    IN ULONG StartOffset,
    IN ULONG DataOffsetDelta,
    IN ULONG DataBackFill,
    IN BOOLEAN DispatchLevel
    );

//
// Routines to retreat over constructed headers & advance over parsed headers.
//

NTSTATUS
NetioRetreatNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN ULONG DataOffsetDelta,
    IN ULONG DataBackFill OPTIONAL
    );

VOID
NetioAdvanceNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN ULONG DataOffsetDelta
    );

VOID
NetioAdvanceToLocationInNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN ULONG DataOffsetDelta,
    IN PMDL DataMdl,
    IN ULONG DataMdlOffset
    );

NTSTATUS
NetioRetreatNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN ULONG DataOffsetDelta,
    IN ULONG DataBackFill OPTIONAL
    );

VOID
NetioAdvanceNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN ULONG DataOffsetDelta
    );

#define NetioGetDataBuffer NdisGetDataBuffer


//
// Routines for in-place construction of NetBuffers and NetBufferLists.
//

VOID
NetioInitializeNetBuffer(
    IN PNET_BUFFER NetBuffer,
    IN PMDL Mdl,
    IN ULONG InitialHeaderSize
    );

VOID
NetioInitializeNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList,
    IN PNETIO_NET_BUFFER_LIST_COMPLETION_ROUTINE CompletionRoutine,
    IN PVOID CompletionContext
    );

PVOID
NetioGetDataBufferSafe(
    IN PNET_BUFFER NetBuffer,
    IN ULONG BytesNeeded
    );

ULONG
NetioGetContiguousBufferSize(
    IN PNET_BUFFER NetBuffer
    );

BOOLEAN
NetioValidateNetBuffer(
    IN PNET_BUFFER NetBuffer
    );

BOOLEAN
NetioValidateNetBufferList(
    IN PNET_BUFFER_LIST NetBufferList
    );



//
// Network Programming Interface Registration Instance: represents a
// registration of an implementation of a specific network programming
// interface by a specific network module.  The information in this structure
// is specified by the module implementing an instance of a network
// programming interface.
//
typedef struct _NPI_REGISTRATION_INSTANCE {
    //
    // Pointer to the network programming interface identifier
    // being represented.
    //
    PNPIID NpiId;

    //
    // Pointer to the module identifier of the module implementing a
    // particular side of the network programming interface above.
    //
    PNPI_MODULEID ModuleId;

    //
    // Size (in bytes) of the context area the module would like
    // the NMR to allocate for each attachment involving the module.
    //
    ULONG ContextLength;

    //
    // Pool tag that the NMR may use for the context area allocation.
    //
    ULONG ContextPoolTag;

    //
    // In the case of multiple implementations of the same network
    // programming interface by the same network module, this number
    // allows for telling those instances apart.  Usually, the module will
    // set this to zero in the case of only one implementation of the
    // given network programming interface.
    //
    ULONG Number;

} NPI_REGISTRATION_INSTANCE;

//
// A Network Programming Interface (NPI) is a well-defined table of function
// pointers and a caller-specific handle representing the caller of the
// functions.  The handle is usually passed as a parameter to the functions
// as defined by the specific network programming interface definition.
// This structure is a place holder to opaquely describe network programming
// interfaces.  It is usually cast to a specific NPI structure for use.
//
typedef struct _NPI {
    HANDLE Handle;
    CONST VOID* Dispatch;
} NPI;

//
// These types define the pointers to constant data supplied by a client
// or provider during its registration.  The data pointed to must be
// kept valid for the life of the registration.
//
typedef CONST struct _NPI_CLIENT_NOTIFY* PNPI_CLIENT_NOTIFY;
typedef CONST struct _NPI_PROVIDER_NOTIFY* PNPI_PROVIDER_NOTIFY;

typedef HANDLE NPI_CLIENT_HANDLE, *PNPI_CLIENT_HANDLE;
typedef HANDLE NPI_PROVIDER_HANDLE, *PNPI_PROVIDER_HANDLE;
typedef HANDLE NPI_BINDING_HANDLE, *PNPI_BINDING_HANDLE;


typedef
NTSTATUS
(NTAPI NPI_CLIENT_NOTIFY_ATTACH_PROVIDER_FN)(
    IN PNPI_CLIENT_NOTIFY ClientNotify,
    IN PVOID ProviderContext,
    IN PNPI_PROVIDER_NOTIFY ProviderNotify,
    IN PVOID ClientContext
    );
typedef NPI_CLIENT_NOTIFY_ATTACH_PROVIDER_FN *PNPI_CLIENT_NOTIFY_ATTACH_PROVIDER_FN;

typedef
NTSTATUS
(NTAPI NPI_CLIENT_NOTIFY_DETACH_PROVIDER_FN)(
    IN PNPI_CLIENT_NOTIFY ClientNotify,
    IN NPI_BINDING_HANDLE BindingHandle,
    IN PVOID ProviderContext
    );
typedef NPI_CLIENT_NOTIFY_DETACH_PROVIDER_FN *PNPI_CLIENT_NOTIFY_DETACH_PROVIDER_FN;

typedef
VOID
(NTAPI NPI_CLIENT_NOTIFY_CLEANUP_PROVIDER_CONTEXT_FN)(
    IN PNPI_CLIENT_NOTIFY ClientNotify,
    IN PVOID ProviderContext
    );
typedef NPI_CLIENT_NOTIFY_CLEANUP_PROVIDER_CONTEXT_FN *PNPI_CLIENT_NOTIFY_CLEANUP_PROVIDER_CONTEXT_FN;

typedef
VOID
(NTAPI NPI_CLIENT_NOTIFY_DEREGISTER_COMPLETE_FN)(
    IN PNPI_CLIENT_NOTIFY ClientNotify
    );
typedef NPI_CLIENT_NOTIFY_DEREGISTER_COMPLETE_FN *PNPI_CLIENT_NOTIFY_DEREGISTER_COMPLETE_FN;

typedef struct _NPI_CLIENT_NOTIFY {
    USHORT Length;

    //
    // Identifies the instance of the registration.
    //
    NPI_REGISTRATION_INSTANCE Instance;

    //
    // Callback routines.
    //
    PNPI_CLIENT_NOTIFY_ATTACH_PROVIDER_FN AttachProvider;
    PNPI_CLIENT_NOTIFY_DETACH_PROVIDER_FN DetachProvider;
    PNPI_CLIENT_NOTIFY_CLEANUP_PROVIDER_CONTEXT_FN CleanupProviderContext;
    PNPI_CLIENT_NOTIFY_DEREGISTER_COMPLETE_FN DeregisterComplete;

} NPI_CLIENT_NOTIFY;


typedef
NTSTATUS
(NTAPI NPI_PROVIDER_NOTIFY_ATTACH_CLIENT_FN)(
    IN PNPI_PROVIDER_NOTIFY ProviderNotify,
    IN PVOID ClientContext,

    //
    // The client's NPI that this provider will use to communicate
    // with the client.
    //
    IN CONST NPI* ClientNpi,

    //
    // Pointer to where this provider should return the provider's NPI
    // that the client will use to communicate with the provider.
    //
    OUT NPI* ProviderNpi
    );
typedef NPI_PROVIDER_NOTIFY_ATTACH_CLIENT_FN *PNPI_PROVIDER_NOTIFY_ATTACH_CLIENT_FN;

typedef
NTSTATUS
(NTAPI NPI_PROVIDER_NOTIFY_DETACH_CLIENT_FN)(
    IN PNPI_PROVIDER_NOTIFY ProviderNotify,
    IN NPI_BINDING_HANDLE BindingHandle,
    IN PVOID ClientContext
    );
typedef NPI_PROVIDER_NOTIFY_DETACH_CLIENT_FN *PNPI_PROVIDER_NOTIFY_DETACH_CLIENT_FN;

typedef
VOID
(NTAPI NPI_PROVIDER_NOTIFY_CLEANUP_CLIENT_CONTEXT_FN)(
    IN PNPI_PROVIDER_NOTIFY ProviderNotify,
    IN PVOID ClientContext
    );
typedef NPI_PROVIDER_NOTIFY_CLEANUP_CLIENT_CONTEXT_FN *PNPI_PROVIDER_NOTIFY_CLEANUP_CLIENT_CONTEXT_FN;

typedef
VOID
(NTAPI NPI_PROVIDER_NOTIFY_DEREGISTER_COMPLETE_FN)(
    IN PNPI_PROVIDER_NOTIFY ProviderNotify
    );
typedef NPI_PROVIDER_NOTIFY_DEREGISTER_COMPLETE_FN *PNPI_PROVIDER_NOTIFY_DEREGISTER_COMPLETE_FN;

typedef struct _NPI_PROVIDER_NOTIFY {
    USHORT Length;

    //
    // Identifies the instance of the registration.
    //
    NPI_REGISTRATION_INSTANCE Instance;

    //
    // Callback routines.
    //
    PNPI_PROVIDER_NOTIFY_ATTACH_CLIENT_FN AttachClient;
    PNPI_PROVIDER_NOTIFY_DETACH_CLIENT_FN DetachClient;
    PNPI_PROVIDER_NOTIFY_CLEANUP_CLIENT_CONTEXT_FN CleanupClientContext;
    PNPI_PROVIDER_NOTIFY_DEREGISTER_COMPLETE_FN DeregisterComplete;

    //
    // Characteristic data specific to this provider that can be
    // examined by the client during AttachProvider in order to
    // determine if the client will call this provider's AttachClient.
    // This data is specific to the NPIID and therefore the structure of
    // this data is known by both client and provider.
    //
    CONST VOID* NpiSpecificCharacter OPTIONAL;

} NPI_PROVIDER_NOTIFY;


//
// Called by a module to register an instance of an implementation of the
// client side of a particular network programming interface.
//
NTSTATUS
NmrRegisterClient(
    IN PNPI_CLIENT_NOTIFY Notify,
    OUT PNPI_CLIENT_HANDLE Handle
    );

//
// Called by a module to register an instance of an implementation of the
// provider side of a particular network programming interface.
//
NTSTATUS
NmrRegisterProvider(
    IN PNPI_PROVIDER_NOTIFY Notify,
    OUT PNPI_PROVIDER_HANDLE Handle
    );

//
// Called by a module to un-register an instance of an implementation of the
// client side of a particular network programming interface.
//
NTSTATUS
NmrDeregisterClient(
    IN NPI_CLIENT_HANDLE Handle
    );

//
// Called by a module to un-register an instance of an implementation of the
// provider side of a particular network programming interface.
//
NTSTATUS
NmrDeregisterProvider(
    IN NPI_PROVIDER_HANDLE Handle
    );


NTSTATUS
NmrDetachClientComplete(
    IN NPI_BINDING_HANDLE Handle
    );

NTSTATUS
NmrDetachProviderComplete(
    IN NPI_BINDING_HANDLE Handle
    );


extern CONST NPIID NPI_DATALINK_LAYER_ID;

typedef struct _NPI_DATALINK_LAYER_CLIENT {
    NTSTATUS (NTAPI *Method)(
        IN );

} NPI_DATALINK_LAYER_CLIENT;

typedef struct _NPI_DATALINK_LAYER_PROVIDER {
    NTSTATUS (NTAPI *Method)(
        IN );

} NPI_DATALINK_LAYER_PROVIDER;





////////////////////////////////////////////////////////////////////////
// STRUCTURES, ENUMERATIONS and DEFINES
//
// Extensibility: These structures might be extended in future versions
//     of the FLNPI.  This will update the version number indicated in
//     FL_CLIENT_DISPATCH,
//     FL_PROVIDER_DISPATCH,
//     FL_PROVIDER_CHARACTERISTICS. 
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
// Interface
////////////////////////////////////////////////////////////////////////

//
// FL_INTERFACE_CHARACTERISTICS:
//
// Define Interface characteristics.
//
// Sets: RequestedPacketFilter, *WakeUpPattern, Offload.
// Updates: DlAddress.
//
// NOTE: NDIS does not allow DlAddress to be set.
//
typedef enum {
    FlicRequestedPacketFilter,
    FlicAddWakeUpPattern,
    FlicRemoveWakeUpPattern,
    FlicOffload,
    FlicReferOid
} FLIC_CODE, *PFLIC_CODE;

#define FLICFLAG_HEADERLENGTH           0x00000001 // UPDATE
#define FLICFLAG_DLADDRESS              0x00000002 // UPDATE

typedef struct _FL_INTERFACE_CHARACTERISTICS {
    COMPARTMENT_ID CompartmentId;
    
    UCHAR HeaderLength;                 // Size of link layer header (bytes).
    UCHAR IdentifierLength;             // Size of interface identifier (bits).
    USHORT DlAddressLength;             // Size of link layer address (bytes).

    UCHAR DadTransmits;                 // Default value for 
                                        // DupAddrDetectTransmits (RFC 2462).
    UCHAR AccessType;                   // IF_ACCESS_TYPE
    IFTYPE InterfaceType;               // IFTYPE
    TUNNEL_TYPE TunnelType;             // If IFTYPE == IF_TYPE_TUNNEL.
    struct {
        UCHAR Unicasts : 1;             // Supports unicast.
        UCHAR Multicasts : 1;           // Supports multicast.
        UCHAR Transmits : 1;            // Supports packet transmission.
        UCHAR Receives : 1;             // Supports packet reception.
        UCHAR DiscoversNeighbors : 1;   // Supports neighbor discovery.
        UCHAR DiscoversRouters : 1;     // Supports router discovery.
        UCHAR DefaultUseNud : 1;        // Supports NUD by default?
        UCHAR WakeUpPatterns : 1;       // Supports wake-on-lan patterns.
    };
    
    //
    // The types of packets for which the framing layer client requests
    // receive indications, on this interface, from the framing layer
    // provider.  Specified by bitwise OR'ing NDIS_PACKET_TYPE_* flags.
    //
    ULONG RequestedPacketFilter;

    NDIS_HANDLE NdisBindingHandle;
    
    //
    // The interface identifier used for auto-configured addresses by the
    // network layer. 
    // TODO: The interface identifier can be > 64 bits. Make this generic so
    // that larger identifiers can be supported. 
    //
    DL_EUI64 Eui64;
    
    //
    // Local data link layer address of the interface followed by the remote
    // address (for point to point tunnels). 
    //
    UCHAR DlAddress[0];
    
} FL_INTERFACE_CHARACTERISTICS, *PFL_INTERFACE_CHARACTERISTICS;


//
// FL_INTERFACE_IDENTIFIERS
//
// Define (sub) interface identifiers.
//
// Each local interface is assigned a unique and persistent interface
// LUID and a unique runtime interface index.  Moreover, sub interfaces
// corresponding to remote stations on an NBMA interface are also
// provided LUIDs and interface indicies that are unique with respect
// those provided to local interfaces.
//

typedef struct _FL_INTERFACE_IDENTIFIERS {
    IF_LUID Luid;
    IF_INDEX Index;
} FL_INTERFACE_IDENTIFIERS, *PFL_INTERFACE_IDENTIFIERS;



////////////////////////////////////////////////////////////////////////
// SubInterface
////////////////////////////////////////////////////////////////////////

//
// FL_SUBINTERFACE_CHARACTERISTICS
//
// Define SubInterface characteristics.
//
// Updates: MediaSenseState, Mtu, Speed.
//

typedef struct _FL_SUBINTERFACE_CHARACTERISTICS {
    IF_MEDIASENSE_STATE MediaSenseState;
    ULONG Mtu;                  // Maximum transmission unit.
    ULONG64 Speed;              // Subinterface speed in bps.
} FL_SUBINTERFACE_CHARACTERISTICS, *PFL_SUBINTERFACE_CHARACTERISTICS;



////////////////////////////////////////////////////////////////////////
// Address Mapping
////////////////////////////////////////////////////////////////////////

//
// FL_ADDRESS_MAPPING_TYPE
//
// Define network layer address to datalink layer address mapping type.
//

typedef enum {
    FlAddressMappingStatic,
    FlAddressMappingDynamic,
    FlAddressMappingMaximum,
} FL_ADDRESS_MAPPING_TYPE, *PFL_ADDRESS_MAPPING_TYPE;



////////////////////////////////////////////////////////////////////////
// FUNCTIONS
//
// Extensibility: These functions might be extended in future versions
//     of the FLNPI.  This will update the version number indicated in
//     FL_CLIENT_DISPATCH,
//     FL_PROVIDER_DISPATCH,
//     FL_PROVIDER_CHARACTERISTICS. 
//
// Locking: For functions that may complete asynchronously, the
//     completion routine might be called in the context of the call
//     itself.  Hence the caller must not make the call while holding
//     any locks that might be acquired in the completion routine.  In
//     general, it's not a good idea to hold any locks while calling
//     outside the module.  And, whenever possible, locks should only be
//     acquired long enough to grab a reference on the object.
//
// ProviderHandle: Since each framing layer provider has at most one
//     framing layer client (network layer provider), the provider
//     handle, given to the client at attach time, need not be included
//     in calls into the provider.
// 
// ClientHandle: Each framing layer client (network layer provider) may
//     register with multiple framing layer providers.  Hence callbacks
//     into the client, that do not have any means for the client to
//     identify the provider, should supply the client handle given to
//     the provider at attach time.
////////////////////////////////////////////////////////////////////////


typedef struct _FL_REQUEST_COMPLETE {
    IN HANDLE ProviderObjectHandle;
    IN PVOID RequestContext;
    IN NTSTATUS Status;
} FL_REQUEST_COMPLETE, *PFL_REQUEST_COMPLETE;

typedef struct _FL_INDICATE_COMPLETE {
    IN HANDLE ClientObjectHandle;
    IN PVOID RequestContext;
    IN NTSTATUS Status;
} FL_INDICATE_COMPLETE, *PFL_INDICATE_COMPLETE;


////////////////////////////////////////////////////////////////////////
// Interface Management
////////////////////////////////////////////////////////////////////////

typedef
VOID
(NTAPI FL_PROVIDER_ADD_INTERFACE_COMPLETE)(
    IN PFL_REQUEST_COMPLETE Args
    );
typedef FL_PROVIDER_ADD_INTERFACE_COMPLETE
*PFL_PROVIDER_ADD_INTERFACE_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer client to inform the
    provider of the status upon completion of a previous call to
    AddInterface.
    
Arguments:

    ProviderObjectHandle - Supplies the provider's handle to the
        interface, supplied to a previous call to AddInterface.
        Used by the provider to identify the interface.
        
    Status - Supplies the completion status of the AddInterface call.
    
Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef struct _FL_INDICATE_ADD_INTERFACE {
    IN PFL_PROVIDER_ADD_INTERFACE_COMPLETE IndicateComplete;
    IN HANDLE ClientHandle;
    IN HANDLE ProviderInterfaceHandle;
    IN CONST FL_INTERFACE_IDENTIFIERS *Identifiers;
    IN CONST FL_INTERFACE_CHARACTERISTICS *Characteristics;
    OUT PHANDLE ClientInterfaceHandle;
} FL_INDICATE_ADD_INTERFACE, *PFL_INDICATE_ADD_INTERFACE;

typedef
NTSTATUS
(NTAPI FL_CLIENT_ADD_INTERFACE)(
    IN PFL_INDICATE_ADD_INTERFACE Args
    );
typedef FL_CLIENT_ADD_INTERFACE
*PFL_CLIENT_ADD_INTERFACE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of the addition of a new interface.
    
Arguments:

    ClientHandle - Supplies the client's handle to the provider
        (FL_CLIENT_NPI::ProviderHandle).  Typically set by the client
        to the ProviderContext supplied to the AttachProvider call.
        
    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface.  This must be supplied to subsequent calls made by
        the client that refer to this interface.
        
    Identifiers - Supplies the interface's luid and index.
    
    Characteristics - Supplies the interface's properties.

    ClientInterfaceHandle - Returns the client's handle to the
        interface.  This must be supplied to subsequent calls made by
        the provider that refer to this interface.

        The provider can supply a pointer to a field within its internal
        structure.  If the client wishes, it can set this field and start
        using the interface before the function returns.
        
Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed. 

Caller IRQL: PASSIVE_LEVEL.

--*/


typedef
VOID
(NTAPI FL_PROVIDER_DELETE_INTERFACE_COMPLETE)(
    IN PFL_REQUEST_COMPLETE Args
    );
typedef FL_PROVIDER_DELETE_INTERFACE_COMPLETE
*PFL_PROVIDER_DELETE_INTERFACE_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer client to inform the
    provider of the status upon completion of a previous call to
    DeleteInterface.
    
Arguments:

    ProviderObjectHandle - Supplies the provider's handle to the
        interface, supplied to a previous call to AddInterface.
        Used by the provider to identify the interface.

        Henceforth, this handle should be considered invalid by the
        client and it should not make any subsequent call to the
        provider with it.
        
    Status - Supplies the completion status of the DeleteInterface call.
    
Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef struct _FL_INDICATE_DELETE_INTERFACE {
    IN PFL_PROVIDER_DELETE_INTERFACE_COMPLETE IndicateComplete;
    IN HANDLE ClientInterfaceHandle;
} FL_INDICATE_DELETE_INTERFACE, *PFL_INDICATE_DELETE_INTERFACE;

typedef
NTSTATUS
(NTAPI FL_CLIENT_DELETE_INTERFACE)(
    IN PFL_INDICATE_DELETE_INTERFACE Args
    );
typedef FL_CLIENT_DELETE_INTERFACE
*PFL_CLIENT_DELETE_INTERFACE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of the deletion of an existing interface.
    
Arguments:

    ClientInterfaceHandle - Supplies the client's handle to the
        interface, returned by a previous call to AddInterface.
        Used by the client to identify the interface.

        Henceforth, this handle should be considered invalid by the
        provider and it should not make any subsequent call to the
        client with it.  The provider should call AddInterface
        again to create a fresh binding if the interface is re-added.
    
Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed. 
    
Caller IRQL: PASSIVE_LEVEL.

--*/


typedef struct _FL_INDICATE_UPDATE_INTERFACE {
    IN HANDLE ClientInterfaceHandle;
    IN ULONG Flags;
    IN CONST FL_INTERFACE_CHARACTERISTICS *Characteristics;
} FL_INDICATE_UPDATE_INTERFACE, *PFL_INDICATE_UPDATE_INTERFACE;

typedef
NTSTATUS
(NTAPI FL_CLIENT_UPDATE_INTERFACE)(
    IN PFL_INDICATE_UPDATE_INTERFACE Args
    );
typedef FL_CLIENT_UPDATE_INTERFACE
*PFL_CLIENT_UPDATE_INTERFACE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of an update in an existing interface's properties.
    
Arguments:

    ClientInterfaceHandle - Supplies the client's handle to the
        interface, returned by a previous call to AddInterface.
        Used by the client to identify the interface.

    Flags - Supplies flags ('UPDATE' FLICFLAG_*) that identify the
        properties to be updated. 
    
    Characteristics - Supplies the interface's updated characteristics.
    
Return Value:

    Completes synchronously with STATUS_SUCCESS or a failure code.

Caller IRQL: <= DISPATCH_LEVEL.
    
--*/

typedef struct _FL_REQUEST_QUERY_INTERFACE {
    IN HANDLE ProviderInterfaceHandle;
    IN FLIC_CODE RequestCode;
    IN NDIS_OID Oid;
    OUT PVOID RequestBuffer;
    IN OUT ULONG RequestLength;
} FL_REQUEST_QUERY_INTERFACE, *PFL_REQUEST_QUERY_INTERFACE;


typedef
NTSTATUS
(NTAPI FL_PROVIDER_QUERY_INTERFACE)(
    IN PFL_REQUEST_QUERY_INTERFACE Args
    );
typedef FL_PROVIDER_QUERY_INTERFACE
*PFL_PROVIDER_QUERY_INTERFACE; 

/*++

Routine Description:

    This function retrieves information about an interface.

Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle for the
        interface (obtained from the AddInterface call).  Indicates
        the interface whose properties should be returned.

    RequestCode - Supplies the code identifying the request type.

    Oid - Supplies the NDIS_OID (optionally) that needs to be used in the
        query request.

    RequestBuffer - Returns, in this caller supplied buffer, the
        requested interface property.

    RequestLength - Supplies the size, in bytes, of RequestBuffer.
        Returns, on STATUS_BUFFER_TOO_SMALL, the minimum size buffer
        required to return the interface's properties.  Otherwise, the
        value of RequestLength remains unchanged.
        
Return Value:

    Completes synchronously with STATUS_SUCCESS or a failure code.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_SET_INTERFACE_COMPLETE)(
    IN PFL_INDICATE_COMPLETE Args
    );
typedef FL_CLIENT_SET_INTERFACE_COMPLETE
*PFL_CLIENT_SET_INTERFACE_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of the status upon completion of a previous request to SetInterface.

Arguments:

    ClientObjectHandle - Supplies the client's handle to the
        interface, returned by a previous call to AddInterface.
        Used by the client to identify the interface.

    RequestContext - Supplies the context registered by the client during set.

    Status - Supplies the completion status of the SetInterface request.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/

typedef struct _FL_REQUEST_SET_INTERFACE {
    IN PFL_CLIENT_SET_INTERFACE_COMPLETE RequestComplete;
    IN PVOID RequestContext;
    IN HANDLE ProviderInterfaceHandle;
    IN FLIC_CODE RequestCode;
    IN NDIS_OID Oid;
    IN PVOID RequestBuffer;
    IN ULONG RequestLength;
} FL_REQUEST_SET_INTERFACE, *PFL_REQUEST_SET_INTERFACE;

typedef
NTSTATUS
(NTAPI FL_PROVIDER_SET_INTERFACE)(
    IN PFL_REQUEST_SET_INTERFACE Args
    );
typedef FL_PROVIDER_SET_INTERFACE
*PFL_PROVIDER_SET_INTERFACE; 

/*++

Routine Description:

    This function is used by a framing layer client to update the
    characteristics of an interface. 
    
Arguments:

    RequestComplete - Supplies the completion function.

    RequestContext - Supplies the completion context.

    ProviderInterfaceHandle - Supplies the provider's handle for the
        interface (obtained from the AddInterface call).  Indicates
        the interface whose properties should be updated.

    RequestCode - Supplies the code identifying the update type.

    Oid - Supplies the NDIS_OID (optionally) that needs to be used in the
        set request.

    RequestBuffer - Supplies the updated interface property.

    RequestLength - Supplies the size, in bytes, of RequestBuffer.
    
Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed.

Caller Lock: The client may hold any lock during this request.
    The provider ensures that no indication is made to the client
    in the context of this request.

--*/


////////////////////////////////////////////////////////////////////////
// SubInterface Management
////////////////////////////////////////////////////////////////////////

typedef
VOID
(NTAPI FL_PROVIDER_ADD_SUBINTERFACE_COMPLETE)(
    IN PFL_REQUEST_COMPLETE Args
    );
typedef FL_PROVIDER_ADD_SUBINTERFACE_COMPLETE
*PFL_PROVIDER_ADD_SUBINTERFACE_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer client to inform the
    provider of the status upon completion of a previous call to
    AddSubInterface.
    
Arguments:

    ProviderObjectHandle - Supplies the provider's handle to the
        subinterface, supplied to a previous call to AddSubInterface.
        Used by the provider to identify the subinterface.
        
    Status - Supplies the completion status of the AddSubInterface call.
    
Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef struct _FL_INDICATE_ADD_SUBINTERFACE {
    IN PFL_PROVIDER_ADD_SUBINTERFACE_COMPLETE IndicateComplete;
    IN HANDLE ClientInterfaceHandle;
    IN HANDLE ProviderSubInterfaceHandle;
    IN CONST FL_INTERFACE_IDENTIFIERS *Identifiers;
    IN CONST FL_SUBINTERFACE_CHARACTERISTICS *Characteristics;
    OUT PHANDLE ClientSubInterfaceHandle;
} FL_INDICATE_ADD_SUBINTERFACE, *PFL_INDICATE_ADD_SUBINTERFACE; 

typedef
NTSTATUS
(NTAPI FL_CLIENT_ADD_SUBINTERFACE)(
    IN PFL_INDICATE_ADD_SUBINTERFACE Args
    );
typedef FL_CLIENT_ADD_SUBINTERFACE
*PFL_CLIENT_ADD_SUBINTERFACE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of the creation of a new subinterface.  Sub-interface add/delete calls are
    guaranteed to be serialized.  So, the framing layer client cannot get two
    sub-interface adds/deletes for the same interface at the same time. 
    
Arguments:

    ClientInterfaceHandle - Supplies the client's handle to the
        interface (obtained from the AddInterface call).  Indicates
        the interface over which the subinterface should be added.

    ProviderSubInterfaceHandle - Supplies the provider's handle to the
        subinterface.  This must be supplied to subsequent calls made by
        the client that refer to this subinterface.
        
    Identifiers - Supplies the subinterface's luid and index.
    
    Characteristics - Supplies the subinterface's properties.

    ClientSubInterfaceHandle - Returns the client's handle to the
        subinterface.  This must be supplied to subsequent calls made by
        the provider that refer to this subinterface.
        
        The provider can supply a pointer to a field within its internal
        structure.  If the client wishes, it can set this field and start
        using the subinterface before the function returns.
        
Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed. 

Caller IRQL: PASSIVE_LEVEL.

--*/


typedef
VOID
(NTAPI FL_PROVIDER_DELETE_SUBINTERFACE_COMPLETE)(
    IN PFL_REQUEST_COMPLETE Args
    );
typedef FL_PROVIDER_DELETE_SUBINTERFACE_COMPLETE
*PFL_PROVIDER_DELETE_SUBINTERFACE_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer client to inform the
    provider of the status upon completion of a previous call to
    DeleteSubInterface.

    The provider is responsible for ensuring that all subinterfaces on
    an interface are deleted before that interface itself goes away.
    Hence, before indicating DeleteInterface, the provider should
    indicate DeleteSubInterface for each of its subinterfaces and wait
    for the corresponding DeleteSubInterfaceComplete notifications.
    
    Sub-interface add/delete calls are guaranteed to be serialized.  So, the
    framing layer client cannot get two sub-interface adds/deletes for the same
    interface at the same time.  

Arguments:

    ProviderObjectHandle - Supplies the provider's handle to the
        subinterface, supplied to a previous call to AddSubInterface.
        Used by the provider to identify the subinterface.

        Henceforth, this handle should be considered invalid by the
        client and it should not make any subsequent call to the
        provider with it.
        
    Status - Supplies the completion status of the DeleteSubInterface call.
    
Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef struct _FL_INDICATE_DELETE_SUBINTERFACE {
    IN PFL_PROVIDER_DELETE_SUBINTERFACE_COMPLETE IndicateComplete;
    IN HANDLE ClientSubInterfaceHandle;
} FL_INDICATE_DELETE_SUBINTERFACE, *PFL_INDICATE_DELETE_SUBINTERFACE;

typedef
NTSTATUS
(NTAPI FL_CLIENT_DELETE_SUBINTERFACE)(
    IN PFL_INDICATE_DELETE_SUBINTERFACE Args
    );
typedef FL_CLIENT_DELETE_SUBINTERFACE
*PFL_CLIENT_DELETE_SUBINTERFACE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of the deletion of an existing subinterface.
    
Arguments:

    ClientSubInterfaceHandle - Supplies the client's handle to the
        subinterface, returned by a previous call to AddSubInterface.
        Used by the client to identify the subinterface.

        Henceforth, this handle should be considered invalid by the
        provider and it should not make subsequent calls to the client
        with it.  The provider should call AddSubInterface again to
        create a fresh binding if the subinterface is re-added.
    
Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed. 
    
Caller IRQL: PASSIVE_LEVEL.

--*/


typedef struct _FL_INDICATE_UPDATE_SUBINTERFACE {
    IN HANDLE ClientSubInterfaceHandle;
    struct {
        IN UCHAR MediaSenseStateChange : 1;
        IN UCHAR MtuChange : 1;
        IN UCHAR SpeedChange : 1;
    };
    IN CONST FL_SUBINTERFACE_CHARACTERISTICS *Characteristics;
} FL_INDICATE_UPDATE_SUBINTERFACE, *PFL_INDICATE_UPDATE_SUBINTERFACE;

typedef
NTSTATUS
(NTAPI FL_CLIENT_UPDATE_SUBINTERFACE)(
    IN PFL_INDICATE_UPDATE_SUBINTERFACE Args
    );
typedef FL_CLIENT_UPDATE_SUBINTERFACE
*PFL_CLIENT_UPDATE_SUBINTERFACE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of an update in an existing subinterface's properties.
    
Arguments:

    ClientSubInterfaceHandle - Supplies the client's handle to the
        subinterface, returned by a previous call to AddSubInterface.
        Used by the client to identify the subinterface.

    Flags - Supplies flags that identify the properties to be updated.
    
    Characteristics - Supplies the subinterface's updated characteristics.
    
Return Value:

    Completes synchronously with STATUS_SUCCESS or a failure code.

Caller IRQL: <= DISPATCH_LEVEL.
    
--*/


typedef struct _FL_REQUEST_QUERY_SUBINTERFACE {
    IN HANDLE ProviderSubInterfaceHandle;
    OUT PFL_SUBINTERFACE_CHARACTERISTICS Characteristics;
    IN OUT ULONG CharacteristicsLength;
} FL_REQUEST_QUERY_SUBINTERFACE, *PFL_REQUEST_QUERY_SUBINTERFACE; 

typedef
NTSTATUS
(NTAPI FL_PROVIDER_QUERY_SUBINTERFACE)(
    IN PFL_REQUEST_QUERY_SUBINTERFACE Args
    );
typedef FL_PROVIDER_QUERY_SUBINTERFACE
*PFL_PROVIDER_QUERY_SUBINTERFACE; 

/*++

Routine Description:

    This function retrieves information about an subinterface.

Arguments:

    ProviderSubInterfaceHandle - Supplies the provider's handle for the
        subinterface (obtained from the AddSubInterface call).
        Indicates the subinterface whose properties should be returned.

    Characteristics - Returns, in this caller supplied buffer, the
        subinterface's properties.

    CharacteristicsLength - Supplies the size, in bytes, of the buffer
        (Characteristics) to return the subinterface's's properties in.

        Returns, on ERROR_INSUFFICIENT_BUFFER, the minimum size buffer
        required to return the subinterface's properties.  Otherwise,
        the value of CharacteristicsLength remains unchanged.
        
Return Value:

    Completes synchronously with STATUS_SUCCESS or a failure code.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


////////////////////////////////////////////////////////////////////////
// PnP Event Management
////////////////////////////////////////////////////////////////////////

typedef
VOID
(NTAPI FL_PROVIDER_PNP_EVENT_COMPLETE)(
    IN PFL_REQUEST_COMPLETE Args
    );
typedef FL_PROVIDER_PNP_EVENT_COMPLETE
*PFL_PROVIDER_PNP_EVENT_COMPLETE;


typedef struct _FL_INDICATE_PNP_EVENT {
    IN PFL_PROVIDER_PNP_EVENT_COMPLETE IndicateComplete;
    IN PNET_PNP_EVENT NetPnpEvent;
    IN HANDLE ClientInterfaceHandle;
    IN PVOID PhysicalDeviceObject;
} FL_INDICATE_PNP_EVENT, *PFL_INDICATE_PNP_EVENT;

typedef
NTSTATUS
(NTAPI FL_CLIENT_PNP_EVENT)(
    IN PFL_INDICATE_PNP_EVENT Args
    );
typedef FL_CLIENT_PNP_EVENT
*PFL_CLIENT_PNP_EVENT;

/*++

Routine Description:

    This function is used by a framing layer provider to indicate PnP events
    to a client.

Arguments:

    IndicateComplete - Supplies the completion function.

    NetPnpEvent - Supplies the PnP event object provided by NDIS in its PnP
        notification to the provider.  This is returned as the ProviderContext
        in the completion function.
        
    ClientInterfaceHandle - Supplies the client's handle to the interface,
        returned by a previous call to AddInterface.  Used by the client to
        identify the interface.

    PhysicalDeviceObject - Supplies the physical device object provided by NDIS
        when the interface is first created.

Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed.
    
Caller IRQL: PASSIVE_LEVEL.

--*/


////////////////////////////////////////////////////////////////////////
// Group Management
////////////////////////////////////////////////////////////////////////

typedef
VOID
(NTAPI FL_CLIENT_ADD_GROUP_COMPLETE)(
    IN PFL_INDICATE_COMPLETE Args
    );
typedef FL_CLIENT_ADD_GROUP_COMPLETE
*PFL_CLIENT_ADD_GROUP_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of the status upon completion of a previous request to AddGroup.
    
Arguments:

    ClientObjectHandle - Supplies the client's handle to the group,
        supplied in a previous request to AddGroup.
        Used by the client to identify the group.

    RequestContext - Supplies the context registered by the client in AddGroup.
    
    Status - Supplies the completion status of the AddGroup request.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.
    
--*/

typedef struct _FL_REQUEST_ADD_GROUP {
    IN PFL_CLIENT_ADD_GROUP_COMPLETE RequestComplete;
    IN PVOID RequestContext;
    IN HANDLE ProviderInterfaceHandle;
    IN HANDLE ClientGroupHandle;    
    IN CONST UCHAR *NlGroup;
    OUT PHANDLE ProviderGroupHandle;
} FL_REQUEST_ADD_GROUP, *PFL_REQUEST_ADD_GROUP;

typedef
NTSTATUS
(NTAPI FL_PROVIDER_ADD_GROUP)(
    IN PFL_REQUEST_ADD_GROUP Args
    );
typedef FL_PROVIDER_ADD_GROUP
*PFL_PROVIDER_ADD_GROUP;

/*++

Routine Description:

    This function enables, on the interface, reception of packets sent to the
    specified network layer multicast group address.  The client may make
    multiple requests to add the same group.

Arguments:

    RequestComplete - Supplies the completion function.

    RequestContext - Supplies the completion context.
    
    ProviderInterfaceHandle - Supplies the provider's handle for the
        interface (obtained from the AddInterface call).  Indicates
        the interface over which the multicast group should be added.

    ClientGroupHandle - Supplies the client's handle to the group.
    
    NlGroup - Supplies a pointer to the network layer multicast group
        address for which packets should be received.  The address
        should be of valid length.

    ProviderGroupHandle - Returns, on success, the framing layer provider's
        handle to the added group.
        
Return Value:

    STATUS_PENDING indicates that completion will be asynchronous.
    STATUS_SUCCESS indicates successful synchronous completion.
    Else a failure code is returned to indicate that the call failed. 

Caller Lock: The client may hold any lock during this request.
    The provider ensures that no indication is made to the client
    in the context of this request.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef struct _FL_REQUEST_DELETE_GROUP {
    IN HANDLE ProviderGroupHandle;
} FL_REQUEST_DELETE_GROUP, *PFL_REQUEST_DELETE_GROUP;

typedef
VOID
(NTAPI FL_PROVIDER_DELETE_GROUP)(
    IN PFL_REQUEST_DELETE_GROUP Args
    );
typedef FL_PROVIDER_DELETE_GROUP
*PFL_PROVIDER_DELETE_GROUP;

/*++

Routine Description:

    This function disables, on the interface, reception of packets sent to the
    specified network layer multicast group address.  The client must delete
    the group as many times as it was added.

Arguments:

    ProviderGroupHandle - Supplies the provider's handle to the group
        (obtained from the AddGroup call).  Indicates the group to be deleted.

        Henceforth, this handle should be considered invalid by the
        client and it should not make any subsequent call to the
        provider with it.
        
Return Value:

    None.

Caller Lock: The client may hold any lock during this request.
    The provider ensures that no indication is made to the client
    in the context of this request.
    
Caller IRQL: <= DISPATCH_LEVEL.

--*/



////////////////////////////////////////////////////////////////////////
// Address Mapping
////////////////////////////////////////////////////////////////////////

typedef struct _FL_REQUEST_MAP_ADDRESS {
    IN HANDLE ProviderInterfaceHandle;
    IN CONST UCHAR *NlAddress;
    OUT UCHAR *DlAddress;
} FL_REQUEST_MAP_ADDRESS, *PFL_REQUEST_MAP_ADDRESS;

typedef
FL_ADDRESS_MAPPING_TYPE
(NTAPI FL_PROVIDER_MAP_ADDRESS)(
    IN PFL_REQUEST_MAP_ADDRESS Args
    );
typedef FL_PROVIDER_MAP_ADDRESS
*PFL_PROVIDER_MAP_ADDRESS;

/*++

Routine Description:

    This function maps a network layer address to a datalink layer address.
    
Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface (obtained from the AddInterface call).
        Indicates the interface over which the address is to be mapped.
        
    NlAddress - Supplies a pointer to the network layer address.
        The address should be of valid length.
    
    DlAddress - Returns, in this caller supplied buffer, the corresponding
        datalink layer address.  The buffer should be of valid length.
        
Return Value:

    FlAddressMappingStatic indicates that mapping was successful
    (e.g. mapping for multicast addresses or neighbors on p2p interfaces).
    FlAddressMappingDynamic indicates the use of neighbor discovery.

Caller IRQL: <= DISPATCH_LEVEL.

--*/

typedef struct _FL_REQUEST_SEND_NEIGHBOR_SOLICITATION {
    IN HANDLE ProviderSubInterfaceHandle;
    IN CONST UCHAR *NlSourceAddress;
    IN CONST UCHAR *DlDestinationAddress;
    IN CONST UCHAR *NlTargetAddress;
    IN CONST UCHAR *DlTargetAddress;
} FL_REQUEST_SEND_NEIGHBOR_SOLICITATION, 
  *PFL_REQUEST_SEND_NEIGHBOR_SOLICITATION;

typedef
VOID
(NTAPI FL_PROVIDER_SEND_NEIGHBOR_SOLICITATION)(
    IN PFL_REQUEST_SEND_NEIGHBOR_SOLICITATION Args
    );
typedef FL_PROVIDER_SEND_NEIGHBOR_SOLICITATION
*PFL_PROVIDER_SEND_NEIGHBOR_SOLICITATION;

/*++

Routine Description:

    Send an ARP request.

Arguments:

    ProviderSubInterfaceHandle - Supplies the provider's handle to the
        subinterface (obtained from the AddSubInterface call).
        Indicates the subinterface over which the request is to be sent.
        
    SourceAddress - Supplies the source address for the request.

    DestinationAddress - Supplies the destination address for the request.

    TargetAddress - Supplies the target address for the request.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/

typedef struct _FL_REQUEST_SEND_NEIGHBOR_ADVERTISEMENT {
    IN HANDLE ProviderSubInterfaceHandle;
    IN CONST UCHAR *NlSourceAddress;
    IN CONST UCHAR *NlTargetAddress;
    IN CONST UCHAR *DlTargetAddress;
    IN BOOLEAN LinkLayerUnicast;
} FL_REQUEST_SEND_NEIGHBOR_ADVERTISEMENT,
  *PFL_REQUEST_SEND_NEIGHBOR_ADVERTISEMENT;

typedef
VOID
(NTAPI FL_PROVIDER_SEND_NEIGHBOR_ADVERTISEMENT)(
    IN PFL_REQUEST_SEND_NEIGHBOR_ADVERTISEMENT Args
    );
typedef FL_PROVIDER_SEND_NEIGHBOR_ADVERTISEMENT
*PFL_PROVIDER_SEND_NEIGHBOR_ADVERTISEMENT;

/*++

Routine Description:

    Send an ARP response.

Arguments:

    ProviderSubInterfaceHandle - Supplies the provider's handle to the
        subinterface (obtained from the AddSubInterface call).
        Indicates the subinterface over which the response is to be sent.

    NlSourceAddress - Supplies the source address for the response.

    DlTargetAddress - Supplies the target address for the response.

    NlTargetAddress - Supplies the target address for the response.

    LinkLayerUnicast - Supplies TRUE if the response should be link-layer
        unicast, or FALSE if it should be broadcast.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/

////////////////////////////////////////////////////////////////////////
// Packet Transmission and Reception.
////////////////////////////////////////////////////////////////////////

typedef struct _FL_SEND_PACKETS {
    IN struct _FL_SEND_PACKETS *Next;
    IN PNET_BUFFER_LIST NetBufferList;
    IN CONST UCHAR *DlDestination;
    IN PVOID CancelId;
} FL_SEND_PACKETS, *PFL_SEND_PACKETS;

typedef
VOID
(NTAPI FL_PROVIDER_SEND_PACKETS)(
    IN HANDLE ProviderSubInterfaceHandle,
    IN BOOLEAN DispatchLevel,
    IN PFL_SEND_PACKETS PacketList
    );
typedef FL_PROVIDER_SEND_PACKETS
*PFL_PROVIDER_SEND_PACKETS;

/*++

Routine Description:

    This function handles the framing and transmission of fully formed
    network layer packets.
    
Arguments:

    NOTE: The following parameters should be the same for all packets indicated
    in a single call, hence these are directly passed to the function.
        
    ProviderSubInterfaceHandle - Supplies the provider's handle to the
        subinterface (obtained from the AddSubInterface call).
        Indicates the interface over which the packet should be sent.

    DispatchLevel - Supplies TRUE if IRQL is known to be at DISPATCH level.

    
    NOTE: The following parameters may be different for each set of
    packets indicated in a single call, hence these are passed to the
    function in an FL_SEND_PACKETS structure, which may be linked with
    other FL_SEND_PACKETS structures to form a list.
        
    Next - Supplies the pointer to the next set of packets to send.
        Packets are sent in the order they are linked in this list.

    Packets - Supplies the packets to send.  The client initializes each
        NetBufferList with an appropriate completion routine and transfers
        ownership to the provider in this request.  Upon completion of the
        request, the provider invokes NetioDereferenceNetBufferList(Chain)
        to signal completion and return ownership in the completion routine.

    DlDestination - Supplies a pointer to the datalink layer destination
        address. This address should be of valid length. 

    CancelId - Supplies the ID to be associated with this packet.
        This is used when cancelling this send request.  A value of
        NULL implies that this send request will not be cancelled.
   
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.
    
--*/


typedef struct _FL_REQUEST_CANCEL_SEND_PACKETS {
    IN HANDLE ProviderSubInterfaceHandle;
    IN PVOID CancelId;
} FL_REQUEST_CANCEL_SEND_PACKETS, *PFL_REQUEST_CANCEL_SEND_PACKETS;

typedef
VOID
(NTAPI FL_PROVIDER_CANCEL_SEND_PACKETS)(
    IN PFL_REQUEST_CANCEL_SEND_PACKETS Args
    );
typedef FL_PROVIDER_CANCEL_SEND_PACKETS
*PFL_PROVIDER_CANCEL_SEND_PACKETS;

/*++

Routine Description:

    This function cancels a previously submitted SendPackets request.
    CAVEAT: This results in invokation of the SendComplete handler
    (if not done already).

Arguments:

    ProviderSubInterfaceHandle - Supplies the provider's handle to the
        subinterface (obtained from the AddSubInterface call).
        Indicates the interface over which the packet were sent.
        
    CancelId - Supplies the ID used in a previous request to SendPackets.
        Used to identify the packets to stop sending.        
        
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.
    
--*/


typedef
VOID
(NTAPI FL_CLIENT_RECEIVE_PACKETS)(
    IN HANDLE ClientSubInterfaceHandle,
    IN PNET_BUFFER_LIST NetBufferListChain,
    IN BOOLEAN DispatchLevel
    );
typedef FL_CLIENT_RECEIVE_PACKETS
*PFL_CLIENT_RECEIVE_PACKETS;

/*++

Routine Description:

    This function is used by a framing layer provider to inform a client
    of network layer packets that arrived on the given interface.

Arguments:

    ClientSubInterfaceHandle - Supplies the client's handle to the
        subinterface (obtained from the AddSubInterface call).
        Indicates the subinterface over which the packets arrived.

    NetBufferListChain - Supplies the chain of received NetBufferLists.
        The provider initializes each NetBufferList with an appropriate
        completion routine and transfers ownership to the client in this
        indication.  The last layer to process the NetBufferList invokes
        NetioDereferenceNetBufferList(Chain) to signal completion and return
        ownership in the completion routine.

    DispatchLevel - Supplies TRUE if IRQL is known to be at DISPATCH level.

Return Value:

    None.
    
Caller IRQL: DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_RECEIVE_NEIGHBOR_SOLICITATION)(
    IN HANDLE ClientSubInterfaceHandle,
    IN CONST UCHAR *DlSourceAddress,
    IN CONST UCHAR *NlSourceAddress,
    IN CONST UCHAR *NlTargetAddress
    );
typedef FL_CLIENT_RECEIVE_NEIGHBOR_SOLICITATION
*PFL_CLIENT_RECEIVE_NEIGHBOR_SOLICITATION;


typedef
VOID
(NTAPI FL_CLIENT_RECEIVE_NEIGHBOR_ADVERTISEMENT)(
    IN HANDLE ClientSubInterfaceHandle,
    IN CONST UCHAR *DlSourceAddress,
    IN CONST UCHAR *NlSourceAddress,
    IN BOOLEAN LinkLayerUnicast
    );
typedef FL_CLIENT_RECEIVE_NEIGHBOR_ADVERTISEMENT
*PFL_CLIENT_RECEIVE_NEIGHBOR_ADVERTISEMENT;


////////////////////////////////////////////////////////////////////////
// Chimney Offload
////////////////////////////////////////////////////////////////////////

typedef
VOID
(NTAPI FL_PROVIDER_INITIATE_OFFLOAD)(
    IN HANDLE ProviderInterfaceHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_PROVIDER_INITIATE_OFFLOAD
*PFL_PROVIDER_INITIATE_OFFLOAD;

/*++

Routine Description:

    This function is used by a framing layer client to initiate offload
    of a TCP connection.

Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface (obtained from the AddInterface call).
        Indicates the interface to use when issuing request to Ndis.

    OffloadBlockList - Supplies the list of blocks containing initial
        state information for each layer of the protocol stack.
        
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_INITIATE_OFFLOAD_COMPLETE)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_CLIENT_INITIATE_OFFLOAD_COMPLETE
*PFL_CLIENT_INITIATE_OFFLOAD_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to indicate the
    completion of a previously pended initiate offload call from the
    framing layer client.

Arguments:
      
    OffloadBlockList - Supplies the list of blocks allocated by the
        protocol layers containing state information that was passed
        in by the client when offload was initiated.

Return Value:

    None.
    
Caller IRQL: PASSIVE_LEVEL.

--*/


typedef
VOID
(NTAPI FL_PROVIDER_TERMINATE_OFFLOAD)(
    IN HANDLE ProviderInterfaceHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_PROVIDER_TERMINATE_OFFLOAD
*PFL_PROVIDER_TERMINATE_OFFLOAD;

/*++

Routine Description:

    This function is used by a framing layer client to terminate offload
    of a TCP connection.

Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface (obtained from the AddInterface call).
        Indicates the interface to use when issuing request to Ndis.

    OffloadBlockList - Supplies the list of blocks containing state to
        be uploaded.
        
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_TERMINATE_OFFLOAD_COMPLETE)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_CLIENT_TERMINATE_OFFLOAD_COMPLETE
*PFL_CLIENT_TERMINATE_OFFLOAD_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to indicate the
    completion of a previously pended terminate offload call from the
    framing layer client.

Arguments:

    OffloadBlockList - Supplies a list fromb the framing layer client
        containing information on what states to upload.
        
Return Value:

    None.
    
Caller IRQL: PASSIVE_LEVEL.

--*/


typedef
VOID
(NTAPI FL_PROVIDER_UPDATE_OFFLOAD_STATE)(
    IN HANDLE ProviderInterfaceHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_PROVIDER_UPDATE_OFFLOAD_STATE
*PFL_PROVIDER_UPDATE_OFFLOAD_STATE;

/*++

Routine Description:

    This function is used by a framing layer client to update states
    that were offloaded to the miniport.

Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface (obtained from the AddInterface call).
        Indicates the interface to use when issuing request to Ndis.

    OffloadBlockList - Supplies a list of blocks containing information
        regarding the states to be updated.
                
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_UPDATE_OFFLOAD_COMPLETE)(
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_CLIENT_UPDATE_OFFLOAD_COMPLETE
*PFL_CLIENT_UPDATE_OFFLOAD_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to indicate the
    completion of a previously pended update request from the framing
    layer client.

Arguments:

    OffloadBlockList - Supplies a list of blocks containing information
        regarding the states that were updated.
        
Return Value:

    None.
    
Caller IRQL: PASSIVE_LEVEL.

--*/


typedef
VOID
(NTAPI FL_PROVIDER_INVALIDATE_OFFLOAD_STATE)(
    IN HANDLE ProviderInterfaceHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_PROVIDER_INVALIDATE_OFFLOAD_STATE
*PFL_PROVIDER_INVALIDATE_OFFLOAD_STATE;

/*++

Routine Description:

    This function is used by a framing layer client to invalidate
    an offloaded state.

Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface (obtained from the AddInterface call).
        Indicates the interface to use when issuing request to Ndis.

    OffloadBlockList - Supplies a list of blocks containing information
        regarding the states to be invalidated.
        
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_INVALIDATE_OFFLOAD_COMPLETE)(
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_CLIENT_INVALIDATE_OFFLOAD_COMPLETE
*PFL_CLIENT_INVALIDATE_OFFLOAD_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to indicate the
    completion of a previously pended invalidate call from the framing
    layer client.

Arguments:

    OffloadBlockList - Supplies a list of blocks containing information
        regarding the states that were invalidated.
    
Return Value:

    None.
    
Caller IRQL: PASSIVE_LEVEL.

--*/


typedef
VOID
(NTAPI FL_PROVIDER_QUERY_OFFLOAD_STATE)(
    IN HANDLE ProviderInterfaceHandle,
    IN OUT PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_PROVIDER_QUERY_OFFLOAD_STATE
*PFL_PROVIDER_QUERY_OFFLOAD_STATE;

/*++

Routine Description:

    This function is used by a framing layer client to query states
    that were offloaded.

Arguments:

    ProviderInterfaceHandle - Supplies the provider's handle to the
        interface (obtained from the AddInterface call).
        Indicates the interface to use when issuing request to Ndis.

    OffloadBlockList - Supplies the list of blocks containing initial
        state information for each layer of the protocol stack. On
        return the blocks will contain information for each layer of
        the stack.
                
Return Value:

    None.
    
Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef
VOID
(NTAPI FL_CLIENT_QUERY_OFFLOAD_COMPLETE)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef FL_CLIENT_QUERY_OFFLOAD_COMPLETE
*PFL_CLIENT_QUERY_OFFLOAD_COMPLETE;

/*++

Routine Description:

    This function is used by a framing layer provider to indicate the
    completion of a previously pended query request from the framing
    layer client.

Arguments:

    OffloadBlockList - Suppplies the list that was passed in when the
        framing layer client requested a query containing information
        on what states to query. On successful return, each element in
        this list contains the queried information.

Return Value:

    None.
    
Caller IRQL: PASSIVE_LEVEL.

--*/

typedef
VOID
(NTAPI FL_CLIENT_QUERY_NEIGHBOR_REACHABILITY)(
    IN PNDIS_OFFLOAD_HANDLE OffloadHandle,
    IN ULONG NicReachabilityDelta,
    OUT PULONG StackReachabilityDelta
    );
typedef FL_CLIENT_QUERY_NEIGHBOR_REACHABILITY
*PFL_CLIENT_QUERY_NEIGHBOR_REACHABILITY;

/*++

Routine Description:

    This function is used by a NIC when it sends a packet and it 
    believes the neighbor stale timeout has passed.  It notifies
    the stack of its own elapsed time, and gets back the stack's
    updated elapsed time.

Arguments:

    OffloadHandle - Supplies a pointer to the offload handle storage
        area associated with the neighbor.

    NicReachabilityDelta - Supplies the elapsed time (in milliseconds)
        since last forward reachability confirmation inside the NIC.

    StackReachabilityDelta - Receives the elapsed time (in milliseconds)
        since last forward reachability confirmation.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/

typedef
VOID
(NTAPI FL_CLIENT_SUSPECT_NEIGHBOR_REACHABILITY)(
    IN PNDIS_OFFLOAD_HANDLE OffloadHandle
    );
typedef FL_CLIENT_SUSPECT_NEIGHBOR_REACHABILITY
*PFL_CLIENT_SUSPECT_NEIGHBOR_REACHABILITY;

/*++

Routine Description:

    This function is used by a NIC when it has reason to suspect
    that forward reachability of a given offloaded neighbor is in doubt.

Arguments:

    OffloadHandle - Supplies a pointer to the offload handle storage
        area associated with the neighbor.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


typedef enum {
    FloeTerminateOffload,
    FloePauseOffload,
    FloeResumeOffload,
    FloePauseProtocol,
    FloeRestartProtocol,
    FloeMax
} FL_OFFLOAD_EVENT, *PFL_OFFLOAD_EVENT;

typedef
VOID
(NTAPI FL_CLIENT_INDICATE_OFFLOAD_EVENT)(
    IN HANDLE ClientInterfaceHandle,
    IN FL_OFFLOAD_EVENT EventCode
    );

typedef FL_CLIENT_INDICATE_OFFLOAD_EVENT
*PFL_CLIENT_INDICATE_OFFLOAD_EVENT;

/*++

Routine Description:

    This function is used to indicate offload events (enumerated above) to 
    the framing layer client. This could be a result of the corresponding NDIS 
    events generated by the offload target or generated by the framing layer 
    because of other events.

Arguments:

    ClientInterfaceHandle - Supplies the client's handle to the
        interface, returned by a previous call to AddInterface.
        Used by the client to identify the interface.

    EventCode - Offload event code.

Return Value:

    None.

Caller IRQL: <= DISPATCH_LEVEL.

--*/


    
////////////////////////////////////////////////////////////////////////
// Registration
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
// Client
////////////////////////////////////////////////////////////////////////

//
// FL_CLIENT_DISPATCH
//
// Define framing layer client (network layer provider) dispatch table.
// This information is required by the framing layer provider.
//

typedef struct _FL_CLIENT_DISPATCH {
    USHORT Version; // (0)
    USHORT Length;

    //
    // The protocol family of the upper layer protocol.  This must be
    // one of the possible values that appear in the first argument
    // (address family) to the winsock socket call.
    //
    ULONG UpperLayerProtocolId;

    //
    // Interface Management.
    //
    PFL_CLIENT_ADD_INTERFACE AddInterface;
    PFL_CLIENT_DELETE_INTERFACE DeleteInterface;
    PFL_CLIENT_UPDATE_INTERFACE UpdateInterface;
    
    //
    // SubInterface Management.
    //
    PFL_CLIENT_ADD_SUBINTERFACE AddSubInterface;
    PFL_CLIENT_DELETE_SUBINTERFACE DeleteSubInterface;
    PFL_CLIENT_UPDATE_SUBINTERFACE UpdateSubInterface;

    //
    // PnP Event Management.
    //
    PFL_CLIENT_PNP_EVENT PnpEvent;
    
    //
    // Packet Transmission and Reception.
    //
    PFL_CLIENT_RECEIVE_PACKETS ReceivePackets;
    PFL_CLIENT_RECEIVE_NEIGHBOR_SOLICITATION ReceiveNeighborSolicitation;
    PFL_CLIENT_RECEIVE_NEIGHBOR_ADVERTISEMENT ReceiveNeighborAdvertisement;

    //
    // Chimney Offload.
    //
    PFL_CLIENT_INITIATE_OFFLOAD_COMPLETE InitiateOffloadComplete;
    PFL_CLIENT_TERMINATE_OFFLOAD_COMPLETE TerminateOffloadComplete;
    PFL_CLIENT_UPDATE_OFFLOAD_COMPLETE UpdateOffloadComplete;
    PFL_CLIENT_INVALIDATE_OFFLOAD_COMPLETE InvalidateOffloadComplete;
    PFL_CLIENT_QUERY_OFFLOAD_COMPLETE QueryOffloadComplete;
    PFL_CLIENT_QUERY_NEIGHBOR_REACHABILITY QueryNeighborReachability;
    PFL_CLIENT_SUSPECT_NEIGHBOR_REACHABILITY SuspectNeighborReachability;
    PFL_CLIENT_INDICATE_OFFLOAD_EVENT IndicateOffloadEvent;
    
} FL_CLIENT_DISPATCH, *PFL_CLIENT_DISPATCH;


typedef struct _FL_CLIENT_NPI {
    HANDLE ProviderHandle;
    CONST FL_CLIENT_DISPATCH *Dispatch;
} FL_CLIENT_NPI;



////////////////////////////////////////////////////////////////////////
// Provider
////////////////////////////////////////////////////////////////////////

//
// FL_PROVIDER_DISPATCH
//
// Define framing layer provider's dispatch table.  This information is
// required by a framing layer client (network layer provider).
//

typedef struct _FL_PROVIDER_DISPATCH {
    USHORT Version; // (0)
    USHORT Length;

    //
    // Backfill requested for the NET_BUFFER_LISTs in SendPackets. 
    //
    USHORT DefaultDataBackfill;
    
    //
    // Interface Management.
    //
    PFL_PROVIDER_QUERY_INTERFACE QueryInterface;
    PFL_PROVIDER_SET_INTERFACE SetInterface;
     
    //
    // SubInterface Management.
    //
    PFL_PROVIDER_QUERY_SUBINTERFACE QuerySubInterface;

    //
    // Group Management
    //
    PFL_PROVIDER_ADD_GROUP AddGroup;
    PFL_PROVIDER_DELETE_GROUP DeleteGroup;
    // TODO: PFL_PROVIDER_MODIFY_SOURCE_LIST ModifySourceList;

    //
    // Address Mapping
    //
    PFL_PROVIDER_MAP_ADDRESS MapAddress;

    //
    // Packet Transmission and Reception.
    //
    PFL_PROVIDER_SEND_PACKETS SendPackets;
    PFL_PROVIDER_CANCEL_SEND_PACKETS CancelSendPackets;
    PFL_PROVIDER_SEND_NEIGHBOR_SOLICITATION SendNeighborSolicitation;
    PFL_PROVIDER_SEND_NEIGHBOR_ADVERTISEMENT SendNeighborAdvertisement;

    //
    // Chimney Offload.
    //
    PFL_PROVIDER_INITIATE_OFFLOAD InitiateOffload;
    PFL_PROVIDER_TERMINATE_OFFLOAD TerminateOffload;
    PFL_PROVIDER_UPDATE_OFFLOAD_STATE UpdateOffloadState;
    PFL_PROVIDER_INVALIDATE_OFFLOAD_STATE InvalidateOffloadState;
    PFL_PROVIDER_QUERY_OFFLOAD_STATE QueryOffloadState;
    
} FL_PROVIDER_DISPATCH, *PFL_PROVIDER_DISPATCH;

typedef struct _FL_PROVIDER_NPI {
    HANDLE ClientHandle;
    CONST FL_PROVIDER_DISPATCH *Dispatch;
} FL_PROVIDER_NPI;


//
// FL_PROVIDER_CHARACTERISTICS
//
// Define characteristic data specific to the framing layer provider
// that can be examined by the client during AttachProvider in order to
// determine if the client will call this provider's AttachClient.  This
// data is specific to the framing layer and therefore the structure of
// this data is known by both client and provider.
//

typedef struct _FL_PROVIDER_CHARACTERISTICS {
    USHORT Version; // (0)
    USHORT Length;  // Length of the provider characteristics.

    //
    // The framing layer can be identified by the supported network
    // layer protocol and any one of its data link interface types.
    //
    ULONG NetworkLayerProtocolId;   // AF_* 
    ULONG DataLinkLayerProtocolId;  // IFTYPE
} FL_PROVIDER_CHARACTERISTICS, *PFL_PROVIDER_CHARACTERISTICS;


//
// Define structures and prototypes for compartment management.
//

typedef struct _NL_COMPARTMENT {
    COMPARTMENT_ID CompartmentId;
} NL_COMPARTMENT, *PNL_COMPARTMENT;

typedef struct _NL_COMPARTMENT_ARG {
    CONST NL_COMPARTMENT *Compartment OPTIONAL;
    COMPARTMENT_ID Id;
} NL_COMPARTMENT_ARG, *PNL_COMPARTMENT_ARG;

typedef struct _NL_REQUEST_COMPARTMENT {
    IN HANDLE ProviderHandle;
    IN OUT NL_COMPARTMENT_ARG NlCompartment;
} NL_REQUEST_COMPARTMENT, *PNL_REQUEST_COMPARTMENT;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_REFERENCE_COMPARTMENT)(
    IN OUT PNL_REQUEST_COMPARTMENT Args
    );
typedef NL_PROVIDER_REFERENCE_COMPARTMENT
    *PNL_PROVIDER_REFERENCE_COMPARTMENT;

typedef
VOID
(NTAPI NL_PROVIDER_DEREFERENCE_COMPARTMENT)(
    IN PNL_REQUEST_COMPARTMENT Args
    );
typedef NL_PROVIDER_DEREFERENCE_COMPARTMENT
    *PNL_PROVIDER_DEREFERENCE_COMPARTMENT;


//
// Define structures and prototypes for interface management.
//

typedef enum {
    NlInterfaceUp,
    NlInterfaceDown
} NL_INTERFACE_STATE, *PNL_INTERFACE_STATE;

typedef struct _NL_INTERFACE_CHARACTERISTICS {
    ULONG UlMtu;
    NL_INTERFACE_STATE State;
    BOOLEAN Forwards;
    CONST FL_INTERFACE_CHARACTERISTICS *FlCharacteristics;
} NL_INTERFACE_CHARACTERISTICS, *PNL_INTERFACE_CHARACTERISTICS;

typedef struct _NL_INTERFACE {
    CONST NL_COMPARTMENT *Compartment;
    IF_LUID Luid;
    IF_INDEX Index;
} NL_INTERFACE, *PNL_INTERFACE;

typedef struct _NL_INTERFACE_ARG {
    CONST NL_INTERFACE *Interface OPTIONAL;
    IF_INDEX Index;
} NL_INTERFACE_ARG, *PNL_INTERFACE_ARG;

typedef struct _NL_INDICATE_INTERFACE {
    IN HANDLE ClientHandle;
    IN CONST NL_INTERFACE *Interface;
} NL_INDICATE_INTERFACE, *PNL_INDICATE_INTERFACE;

typedef struct _NL_REQUEST_INTERFACE {
    IN HANDLE ProviderHandle;
    IN NL_COMPARTMENT_ARG NlCompartment;
    IN OUT NL_INTERFACE_ARG NlInterface;
} NL_REQUEST_INTERFACE, *PNL_REQUEST_INTERFACE;

typedef
VOID
(NTAPI NL_CLIENT_ADD_INTERFACE)(
    IN PNL_INDICATE_INTERFACE Args,
    IN CONST NL_INTERFACE_CHARACTERISTICS *Characteristics
    );
typedef NL_CLIENT_ADD_INTERFACE *PNL_CLIENT_ADD_INTERFACE;

typedef
VOID
(NTAPI NL_CLIENT_DELETE_INTERFACE)(
    IN PNL_INDICATE_INTERFACE Args
    );
typedef NL_CLIENT_DELETE_INTERFACE *PNL_CLIENT_DELETE_INTERFACE;

typedef
VOID
(NTAPI NL_CLIENT_UPDATE_INTERFACE)(
    IN PNL_INDICATE_INTERFACE Args,
    IN CONST NL_INTERFACE_CHARACTERISTICS *Characteristics
    );
typedef NL_CLIENT_UPDATE_INTERFACE *PNL_CLIENT_UPDATE_INTERFACE;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_QUERY_INTERFACE)(
    IN PNL_REQUEST_INTERFACE Args,
    OUT PNL_INTERFACE_CHARACTERISTICS Characteristics
    );
typedef NL_PROVIDER_QUERY_INTERFACE *PNL_PROVIDER_QUERY_INTERFACE;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_SET_INTERFACE)(
    IN PNL_REQUEST_INTERFACE Args,
    IN CONST NL_INTERFACE_CHARACTERISTICS *Characteristics
    );
typedef NL_PROVIDER_SET_INTERFACE *PNL_PROVIDER_SET_INTERFACE;

typedef struct _NL_REQUEST_INTERFACE_PROPERTY {
    IN FLIC_CODE FlicCode;
    IN NDIS_OID Oid;
    IN PVOID RequestBuffer;
    IN ULONG RequestLength;
} NL_REQUEST_INTERFACE_PROPERTY, *PNL_REQUEST_INTERFACE_PROPERTY;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_QUERY_INTERFACE_PROPERTY)(
    IN PNL_REQUEST_INTERFACE Args,
    IN OUT PNL_REQUEST_INTERFACE_PROPERTY Property
    );
typedef NL_PROVIDER_QUERY_INTERFACE_PROPERTY *PNL_PROVIDER_QUERY_INTERFACE_PROPERTY;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_SET_INTERFACE_PROPERTY)(
    IN PNL_REQUEST_INTERFACE Args,
    IN PNL_REQUEST_INTERFACE_PROPERTY Property
    );
typedef NL_PROVIDER_SET_INTERFACE_PROPERTY *PNL_PROVIDER_SET_INTERFACE_PROPERTY;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_REFERENCE_INTERFACE)(
    IN OUT PNL_REQUEST_INTERFACE Args
    );
typedef NL_PROVIDER_REFERENCE_INTERFACE *PNL_PROVIDER_REFERENCE_INTERFACE;

typedef
VOID
(NTAPI NL_PROVIDER_DEREFERENCE_INTERFACE)(
    IN PNL_REQUEST_INTERFACE Args
    );
typedef NL_PROVIDER_DEREFERENCE_INTERFACE *PNL_PROVIDER_DEREFERENCE_INTERFACE;

//
// Define structure and prototype for next hop. 
//

typedef VOID NL_NEXT_HOP, *PNL_NEXT_HOP;

typedef
VOID
(NTAPI NL_PROVIDER_REFERENCE_NEXT_HOP)(
    IN CONST NL_NEXT_HOP *NextHop
    );
typedef NL_PROVIDER_REFERENCE_NEXT_HOP *PNL_PROVIDER_REFERENCE_NEXT_HOP;

typedef
VOID
(NTAPI NL_PROVIDER_DEREFERENCE_NEXT_HOP)(
    IN PNL_NEXT_HOP NextHop
    );
typedef NL_PROVIDER_DEREFERENCE_NEXT_HOP *PNL_PROVIDER_DEREFERENCE_NEXT_HOP;

//
// Define structures and prototypes for local-address management.
//
typedef struct _NL_ADDRESS_IDENTIFIER {
    CONST UCHAR *Address;
    SCOPE_ID ScopeId;
} NL_ADDRESS_IDENTIFIER, *PNL_ADDRESS_IDENTIFIER;

typedef struct _NL_LOCAL_ADDRESS {
    ULONG Signature;
    NL_INTERFACE *Interface;
    CONST NL_ADDRESS_IDENTIFIER *Identifier;
    NL_ADDRESS_TYPE Type;
} NL_LOCAL_ADDRESS, *PNL_LOCAL_ADDRESS;

//
// Macros for accessing address identifier fields from the local address
// structure. 
//

#define NL_ADDRESS(_Address) ((_Address)->Identifier->Address)
#define NL_ADDRESS_SCOPE_ID(_Address) ((_Address)->Identifier->ScopeId)
#define NL_ADDRESS_SCOPE_LEVEL(_Address) \
    ((_Address)->Identifier->ScopeId.Level)
#define NL_ADDRESS_SCOPE_ZONE(_Address) \
    ((_Address)->Identifier->ScopeId.Zone)
#define NL_ADDRESS_TYPE(_Address) ((_Address)->Type)


typedef struct _NL_LOCAL_ADDRESS_ARG {
    IN OUT CONST NL_LOCAL_ADDRESS *LocalAddress OPTIONAL;
    IN SCOPE_ID ScopeId;
    IN CONST UCHAR *Address;
} NL_LOCAL_ADDRESS_ARG, *PNL_LOCAL_ADDRESS_ARG;

typedef struct _NL_LOCAL_ADDRESS_RW_ARG {
    IN OUT CONST NL_LOCAL_ADDRESS *LocalAddress OPTIONAL;
    IN OUT SCOPE_ID ScopeId;
    IN OUT PUCHAR Address;
} NL_LOCAL_ADDRESS_RW_ARG, *PNL_LOCAL_ADDRESS_RW_ARG;

typedef struct _NL_INDICATE_LOCAL_ADDRESS {
    IN HANDLE ClientHandle;
    IN CONST NL_LOCAL_ADDRESS *LocalAddress;
} NL_INDICATE_LOCAL_ADDRESS, *PNL_INDICATE_LOCAL_ADDRESS;

typedef struct _NL_REQUEST_LOCAL_ADDRESS {
    IN HANDLE ProviderHandle;
    IN NL_COMPARTMENT_ARG NlCompartment;
    IN OUT NL_LOCAL_ADDRESS_ARG NlLocalAddress;
} NL_REQUEST_LOCAL_ADDRESS, *PNL_REQUEST_LOCAL_ADDRESS;

typedef
VOID
(NTAPI NL_CLIENT_ADD_LOCAL_ADDRESS)(
    IN PNL_INDICATE_LOCAL_ADDRESS Args
    );
typedef NL_CLIENT_ADD_LOCAL_ADDRESS *PNL_CLIENT_ADD_LOCAL_ADDRESS;

typedef
VOID
(NTAPI NL_CLIENT_DELETE_LOCAL_ADDRESS)(
    IN PNL_INDICATE_LOCAL_ADDRESS Args
    );
typedef NL_CLIENT_DELETE_LOCAL_ADDRESS *PNL_CLIENT_DELETE_LOCAL_ADDRESS;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_REFERENCE_LOCAL_ADDRESS)(
    IN OUT PNL_REQUEST_LOCAL_ADDRESS Args
    );
typedef NL_PROVIDER_REFERENCE_LOCAL_ADDRESS
    *PNL_PROVIDER_REFERENCE_LOCAL_ADDRESS;

typedef
VOID
(NTAPI NL_PROVIDER_DEREFERENCE_LOCAL_ADDRESS)(
    IN PNL_REQUEST_LOCAL_ADDRESS Args
    );
typedef NL_PROVIDER_DEREFERENCE_LOCAL_ADDRESS
    *PNL_PROVIDER_DEREFERENCE_LOCAL_ADDRESS;

typedef
BOOLEAN
(NTAPI NL_PROVIDER_VALIDATE_LOCAL_ADDRESS)(
    IN OUT PNL_REQUEST_LOCAL_ADDRESS Args
    );
typedef NL_PROVIDER_VALIDATE_LOCAL_ADDRESS
    *PNL_PROVIDER_VALIDATE_LOCAL_ADDRESS;

    
//
// Define structures and prototypes for packetization.            .
//

typedef struct _NL_PATH {
    CONST NL_LOCAL_ADDRESS *SourceAddress;
    CONST UCHAR *DestinationAddress;
    SCOPE_ID ScopeId;
} NL_PATH, *PNL_PATH;


typedef struct _NL_REQUEST_CHECKSUM_DATAGRAM {
    IN HANDLE ProviderHandle;
    IN PNET_BUFFER NetBuffer;
    IN CONST UCHAR *Source;
    IN CONST UCHAR *Dest;
    IN ULONG NextHeaderValue;
    IN NDIS_TCP_IP_CHECKSUM_PACKET_INFO *NdisChecksum OPTIONAL;
    IN ULONG PseudoHeaderChecksum OPTIONAL;
    IN ULONG DataLength OPTIONAL;
} NL_REQUEST_CHECKSUM_DATAGRAM, *PNL_REQUEST_CHECKSUM_DATAGRAM;

typedef
ULONG 
(NTAPI NL_PROVIDER_CHECKSUM_DATAGRAM)(
    IN PNL_REQUEST_CHECKSUM_DATAGRAM Args
    );
typedef NL_PROVIDER_CHECKSUM_DATAGRAM *PNL_PROVIDER_CHECKSUM_DATAGRAM;

#define NL_CHECKSUM_OFFSET_NONE 0xFFFF

//
// NLP_REQUEST_SEND_DATAGRAM_GENERIC.
//
// Generic arguments for sending datagrams through the network layer. This
// structure is used for sending datagrams with (NLP_SEND_DATAGRAM_ON_PATH) or
// without a path (NLP_SEND_DATAGRAM). 
//
typedef struct _NLP_SEND_DATAGRAM_GENERIC {
    IN OUT PNET_BUFFER_LIST NetBufferList;

    IN OUT USHORT DestProtocol;

    //
    // Pointer to transport-layer data to be passed to      
    // filters.                                             
    //
    IN PVOID TransportData;

    //                                                      
    // Offset (into upper-layer header) of checksum field.  
    // A value of NL_CHECKSUM_OFFSET_NONE means that the NL 
    // module should not fill in a checksum.                
    //
    IN USHORT UlChecksumOffset;
    IN USHORT UlChecksumOptions;
    IN ULONG PseudoHeaderChecksum OPTIONAL;

    //                                                      
    // NL Session State                                     
    //
    IN PVOID NlSessionState;

    //                                                      
    // Ancillary data (for sendmsg) if any                  
    //
    IN ULONG AncillaryDataLength OPTIONAL;
    IN PVOID AncillaryData OPTIONAL;

    //                                                      
    // Client context passed to cancel routine              
    //
    IN PVOID CancelKey;

    //                                                      
    // Provider context to pass to cancel routine           
    //
    OUT PVOID *CancelContext;

    IN CONST NL_PATH *Path;
    IN HANDLE NlSecurityContext;

    //
    // The next hop to be used for the send.  The NL client is supposed to take
    // a reference on the next hop.  The reference is consumed by the NL
    // provider.
    //
    IN CONST NL_NEXT_HOP *NextHop;
    
    IN OUT NL_INTERFACE_ARG NlInterface OPTIONAL;
    IN OUT NL_LOCAL_ADDRESS_ARG NlLocalAddress OPTIONAL;
    IN SCOPE_ID RemoteScopeId;
    IN CONST UCHAR *RemoteAddress;
    IN NL_COMPARTMENT_ARG NlCompartment;
} NLP_SEND_DATAGRAM_GENERIC, *PNLP_SEND_DATAGRAM_GENERIC;


//
// NL_REQUEST_SEND_DATAGRAMS. 
//
// Defines a argument structure for sending datagrams without a path.
//
typedef struct _NL_REQUEST_SEND_DATAGRAMS {
#ifdef __cplusplus
    NLP_SEND_DATAGRAM_GENERIC SendDatagram;
#else
    NLP_SEND_DATAGRAM_GENERIC;
#endif
    struct _NL_REQUEST_SEND_DATAGRAMS *Next;
} NL_REQUEST_SEND_DATAGRAMS, *PNL_REQUEST_SEND_DATAGRAMS;


typedef
VOID
(NTAPI NL_PROVIDER_SEND_DATAGRAMS)(
    IN HANDLE ProviderHandle,
    IN PNL_REQUEST_SEND_DATAGRAMS FirstDatagramList
    );
typedef NL_PROVIDER_SEND_DATAGRAMS *PNL_PROVIDER_SEND_DATAGRAMS;

typedef struct _NL_INDICATE_CANCEL_DATAGRAMS_COMPLETE {
    //
    // Client context passed in send routine
    //
    IN PVOID CompletionContext;

    IN NTSTATUS Status;
} NL_INDICATE_CANCEL_DATAGRAMS_COMPLETE,
    *PNL_INDICATE_CANCEL_DATAGRAMS_COMPLETE;

typedef
VOID
(NTAPI NL_CLIENT_CANCEL_DATAGRAMS_COMPLETE)(
    IN PNL_INDICATE_CANCEL_DATAGRAMS_COMPLETE Args
    );

typedef NL_CLIENT_CANCEL_DATAGRAMS_COMPLETE
    *PNL_CLIENT_CANCEL_DATAGRAMS_COMPLETE;


typedef struct _NL_REQUEST_CANCEL_SEND_DATAGRAMS {
    //
    // Handle given to client
    //
    IN HANDLE ProviderHandle;

    //
    // Completion routine
    //
    PNL_CLIENT_CANCEL_DATAGRAMS_COMPLETE CompletionRoutine;

    //
    // Client's context passed in the send call
    //
    IN PVOID CancelKey;

    //
    // Provider's context obtained from the send call
    //
    IN PVOID CancelContext;
} NL_REQUEST_CANCEL_SEND_DATAGRAMS, *PNL_REQUEST_CANCEL_SEND_DATAGRAMS;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_CANCEL_SEND_DATAGRAMS)(
    IN PNL_REQUEST_CANCEL_SEND_DATAGRAMS Args
    );
typedef NL_PROVIDER_CANCEL_SEND_DATAGRAMS *PNL_PROVIDER_CANCEL_SEND_DATAGRAMS;

typedef struct _NL_REQUEST_GENERATE_CONTROL_MESSAGE {
#ifdef __cplusplus
    NLP_SEND_DATAGRAM_GENERIC SendDatagram;
#else
    NLP_SEND_DATAGRAM_GENERIC;
#endif
    struct _NL_REQUEST_GENERATE_CONTROL_MESSAGE *Next;
    IN ULONG Type;
    IN ULONG Code;
    IN ULONG Parameter;
} NL_REQUEST_GENERATE_CONTROL_MESSAGE, *PNL_REQUEST_GENERATE_CONTROL_MESSAGE;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_GENERATE_CONTROL_MESSAGE)(
    IN HANDLE ProviderHandle,
    IN PNL_REQUEST_GENERATE_CONTROL_MESSAGE Args
    );
typedef NL_PROVIDER_GENERATE_CONTROL_MESSAGE
    *PNL_PROVIDER_GENERATE_CONTROL_MESSAGE;

#define NLC_RECEIVE_DATAGRAM_FIELDS(Type)                                   \
    IN struct _NLC_RECEIVE_DATAGRAM *Next;                                  \
    IN OUT PNET_BUFFER_LIST NetBufferList;                                  \
                                                                            \
    /*                                                                      \
     * Status values the upper-layer can set in the NetBufferList include:  \
     *  STATUS_SUCCESS - Upper-layer accepts the packet.                    \
     *  STATUS_PORT_UNREACHABLE - Network-layer should send the appropriate \
     *      "port unreachable" control message.                             \
     *  STATUS_PROTOCOL_UNREACHABLE - Network-layer should process as if    \
     *      upper-layer client had not registered (i.e. send to Raw module).\
     *  STATUS_ARBITRATION_UNHANDLED - Network-layer should give Raw a      \
     *      chance to deliver the packet, but should afterwards treat this  \
     *      the same as if the upper-layer accepted the packet.  This is    \
     *      used by protocols such as ICMP and IGMP for which the protocol  \
     *      handler handles some message types, and Raw sockets can handle  \
     *      other message types which would normally be silently dropped.   \
     *      (This is a success code.)                                       \
     *  STATUS_MORE_ENTRIES - Upper layer has updated the NextHeaderValue   \
     *      field, and network-layer should continue parsing farther into   \
     *      the packet.  This can be used by IPsec-in-UDP for example.      \
     *  Other codes - Network-layer should silently drop the packet.        \
     */                                                                     \
                                                                            \
    IN BOOLEAN Loopback;                                                    \
    IN SCOPE_ID RemoteScopeId;                                              \
    IN CONST UCHAR *RemoteAddress;                                          \
                                                                            \
    IN CONST NL_LOCAL_ADDRESS *LocalAddress;                                \
                                                                            \
    IN ULONG NextHeaderValue;                                               \
                                                                            \
    /*                                                                      \
     * Number of bytes from start of network-layer header, to the start     \
     * of the upper-layer header identified by NextHeaderValue.  The        \
     * main purpose of this field is so that IPv4 Raw can retreat by this   \
     * amount since it needs to pass the complete IP packet to its client.  \
     */                                                                     \
    IN ULONG NetworkLayerHeadersSize;                                       \
                                                                            \
    /*                                                                      \
     * Reserved for clients.  Set to NULL before making the indication.     \
     */                                                                     \
    IN PVOID TransportLayerContext

typedef struct _NLC_RECEIVE_DATAGRAM {
    NLC_RECEIVE_DATAGRAM_FIELDS(struct _NLC_RECEIVE_DATAGRAM);
} NLC_RECEIVE_DATAGRAM, *PNLC_RECEIVE_DATAGRAM;

typedef struct _NL_INDICATE_RECEIVE_DATAGRAMS {
    IN HANDLE ClientHandle;
    IN NLC_RECEIVE_DATAGRAM *FirstDatagramList;
} NL_INDICATE_RECEIVE_DATAGRAMS, *PNL_INDICATE_RECEIVE_DATAGRAMS;

typedef
VOID
(NTAPI NL_CLIENT_RECEIVE_DATAGRAMS)(
    IN PNL_INDICATE_RECEIVE_DATAGRAMS Args
    );
typedef NL_CLIENT_RECEIVE_DATAGRAMS *PNL_CLIENT_RECEIVE_DATAGRAMS;

typedef struct _NLC_RECEIVE_CONTROL_MESSAGE {
    NLC_RECEIVE_DATAGRAM_FIELDS(struct _NLC_RECEIVE_CONTROL_MESSAGE);
    
    IN ULONG Type;
    IN ULONG Code;
    IN ULONG Parameter;
} NLC_RECEIVE_CONTROL_MESSAGE, *PNLC_RECEIVE_CONTROL_MESSAGE;

typedef struct _NL_INDICATE_RECEIVE_CONTROL_MESSAGE {
    //
    // Handle given to provider during attach
    //
    IN HANDLE ClientHandle;
    IN NLC_RECEIVE_CONTROL_MESSAGE *ControlMessage;
} NL_INDICATE_RECEIVE_CONTROL_MESSAGE, *PNL_INDICATE_RECEIVE_CONTROL_MESSAGE;

typedef
VOID
(NTAPI NL_CLIENT_RECEIVE_CONTROL_MESSAGE)(
    IN PNL_INDICATE_RECEIVE_CONTROL_MESSAGE Args
    );
typedef NL_CLIENT_RECEIVE_CONTROL_MESSAGE *PNL_CLIENT_RECEIVE_CONTROL_MESSAGE;

typedef struct _NL_REQUEST_QUERY_ANCILLARY_DATA {
    IN HANDLE ProviderHandle;
    IN PVOID NlSessionState;
    IN PNLC_RECEIVE_DATAGRAM Datagram;
    IN OUT ULONG BufferLength;
    OUT PUCHAR Buffer;
} NL_REQUEST_QUERY_ANCILLARY_DATA, *PNL_REQUEST_QUERY_ANCILLARY_DATA;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_QUERY_ANCILLARY_DATA)(
    IN PNL_REQUEST_QUERY_ANCILLARY_DATA Args
    );
typedef NL_PROVIDER_QUERY_ANCILLARY_DATA *PNL_PROVIDER_QUERY_ANCILLARY_DATA;

typedef enum {
    NlsfDrop,
    NlsfAllowIfBindMatches,
    NlsfAllowAlways
} NL_SESSION_FILTER_ACTION, *PNL_SESSION_FILTER_ACTION;

typedef struct _NL_REQUEST_FILTER_DATAGRAM_BY_SESSION_INFORMATION {
    IN PVOID NlSessionState;
    IN PNLC_RECEIVE_DATAGRAM Datagram;
} NL_REQUEST_FILTER_DATAGRAM_BY_SESSION_INFORMATION, 
    *PNL_REQUEST_FILTER_DATAGRAM_BY_SESSION_INFORMATION;

typedef
NL_SESSION_FILTER_ACTION
(NTAPI NL_PROVIDER_FILTER_DATAGRAM_BY_SESSION_INFORMATION)(
    IN PNL_REQUEST_FILTER_DATAGRAM_BY_SESSION_INFORMATION Args
    );
typedef NL_PROVIDER_FILTER_DATAGRAM_BY_SESSION_INFORMATION 
    *PNL_PROVIDER_FILTER_DATAGRAM_BY_SESSION_INFORMATION;

typedef struct _NL_REQUEST_FILTER_INDICATION_BY_SESSION_INFORMATION {
    IN PVOID NlSessionState;
    IN CONST NL_LOCAL_ADDRESS* LocalAddress;
    IN CONST NL_LOCAL_ADDRESS* IndicationLocalAddress;
} NL_REQUEST_FILTER_INDICATION_BY_SESSION_INFORMATION, 
    *PNL_REQUEST_FILTER_INDICATION_BY_SESSION_INFORMATION;

typedef
NL_SESSION_FILTER_ACTION
(NTAPI NL_PROVIDER_FILTER_INDICATION_BY_SESSION_INFORMATION)(
    IN PNL_REQUEST_FILTER_INDICATION_BY_SESSION_INFORMATION Args
    );
typedef NL_PROVIDER_FILTER_INDICATION_BY_SESSION_INFORMATION 
    *PNL_PROVIDER_FILTER_INDICATION_BY_SESSION_INFORMATION;

//
// Define structures and prototypes for path management.
//

typedef struct _NL_REQUEST_JOIN_PATH {
    IN NL_COMPARTMENT_ARG NlCompartment;
    IN PVOID NlSessionState OPTIONAL;
    IN ULONG AncillaryDataLength OPTIONAL;
    IN PVOID AncillaryData OPTIONAL;
    IN NL_INTERFACE_ARG NlInterface OPTIONAL;
    IN SCOPE_ID RemoteScopeId;
    IN CONST UCHAR *RemoteAddress;

    //
    // This field is only used for protocols like ECSRM which have
    // a multicast destination address and multiple unicast remote addresses.
    //
    IN CONST UCHAR *DestinationAddress OPTIONAL;

    IN OUT NL_LOCAL_ADDRESS_ARG NlLocalAddress OPTIONAL;

    //
    // Upper-layer-protocol specific identifiers (i.e., other than 
    // compartment, source address, destination address, scope id)
    // used by the NL security system when sending.
    //
    IN PVOID UlSecurityInformation OPTIONAL;
    IN USHORT UlSecurityInformationSize;

    OUT ULONG DataBackfill;
    OUT ULONG ControlBackfill;

    //
    // NL security association context usable with send.
    //
    OUT HANDLE NlSecurityContext;

    //
    // Path handle usable with send and leave.
    //
    IN OUT CONST NL_PATH *Path;
} NL_REQUEST_JOIN_PATH, *PNL_REQUEST_JOIN_PATH;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_JOIN_PATH)(
    IN HANDLE ProviderHandle,
    IN PNL_REQUEST_JOIN_PATH Args
    );
typedef NL_PROVIDER_JOIN_PATH *PNL_PROVIDER_JOIN_PATH;

typedef struct _NL_REQUEST_LEAVE_PATH {
    IN CONST NL_PATH *Path;
    IN HANDLE NlSecurityContext;
} NL_REQUEST_LEAVE_PATH, *PNL_REQUEST_LEAVE_PATH;

typedef
VOID
(NTAPI NL_PROVIDER_LEAVE_PATH)(
    IN PNL_REQUEST_LEAVE_PATH Args
    );
typedef NL_PROVIDER_LEAVE_PATH *PNL_PROVIDER_LEAVE_PATH;

typedef struct _NL_PATH_INFO {
    USHORT DataBackfill;
    USHORT RequestControlBackfill;

    ULONG UlMtu;
    ULONG RttMean;
    ULONG RttDeviation;
    ULONG64 PathSpeed;
    ULONG64 LinkSpeed;
    IF_MEDIASENSE_STATE MediaSenseState;

    PNL_NEXT_HOP NextHop;
    
    LONG PathEpoch;
    IF_INDEX InterfaceIndex;
} NL_PATH_INFO, *PNL_PATH_INFO;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_QUERY_PATH_INFO)(
    IN CONST NL_PATH *Path,
    IN OUT PNL_PATH_INFO PathInfo
    );
typedef NL_PROVIDER_QUERY_PATH_INFO *PNL_PROVIDER_QUERY_PATH_INFO;

typedef struct _NL_REQUEST_SET_PATH_INFO {
    IN CONST NL_PATH *Path;
    IN ULONG Flags;
    IN ULONG RttSample;
    IN ULONG SpeedSample;
    IN BOOLEAN SymmetricReachability;
} NL_REQUEST_SET_PATH_INFO, *PNL_REQUEST_SET_PATH_INFO;

#define NL_SET_PATH_FLAG_RTT               0x01
#define NL_SET_PATH_FLAG_SPEED             0x02
#define NL_SET_PATH_FLAG_REACHABILITY      0x04

typedef
NTSTATUS
(NTAPI NL_PROVIDER_SET_PATH_INFO)(
    IN PNL_REQUEST_SET_PATH_INFO Args
    );
typedef NL_PROVIDER_SET_PATH_INFO *PNL_PROVIDER_SET_PATH_INFO;

//
// TODO: Once TCP is in the same driver as IP, move these offload
// functions out of the public header file.
//

typedef
VOID
(NTAPI NL_CLIENT_INITIATE_OFFLOAD_COMPLETE)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef NL_CLIENT_INITIATE_OFFLOAD_COMPLETE
    *PNL_CLIENT_INITIATE_OFFLOAD_COMPLETE;

typedef 
VOID
(NTAPI NL_PROVIDER_INITIATE_OFFLOAD)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef NL_PROVIDER_INITIATE_OFFLOAD *PNL_PROVIDER_INITIATE_OFFLOAD;

//
// In each block passed in the initiate offload call, we reuse two 
// fields in this API.  Their values will be overwritten during the call.
// NlioPath is also used in the terminate offload call.
//
#define NlioPath         NdisReserved[0]
#define NlioSessionState NdisReserved[1]
#define NlioCachedState  NdisReserved[2]
#define NlioDesiredIndex Scratch[0]


typedef
VOID
(NTAPI NL_CLIENT_TERMINATE_OFFLOAD_COMPLETE)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef NL_CLIENT_TERMINATE_OFFLOAD_COMPLETE
    *PNL_CLIENT_TERMINATE_OFFLOAD_COMPLETE;

typedef 
VOID
(NTAPI NL_PROVIDER_TERMINATE_OFFLOAD)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef NL_PROVIDER_TERMINATE_OFFLOAD *PNL_PROVIDER_TERMINATE_OFFLOAD;

typedef
VOID
(NTAPI NL_CLIENT_UPDATE_OFFLOAD_COMPLETE)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef NL_CLIENT_UPDATE_OFFLOAD_COMPLETE
    *PNL_CLIENT_UPDATE_OFFLOAD_COMPLETE;

typedef
VOID
(NTAPI NL_CLIENT_INDICATE_OFFLOAD_EVENT)(
    IN PNL_INDICATE_INTERFACE Args,
    IN FL_OFFLOAD_EVENT EventCode
    );
typedef NL_CLIENT_INDICATE_OFFLOAD_EVENT *PNL_CLIENT_INDICATE_OFFLOAD_EVENT;

typedef
VOID
(NTAPI NL_PROVIDER_UPDATE_OFFLOAD)(
    IN PNDIS_PROTOCOL_OFFLOAD_BLOCK_LIST OffloadBlockList
    );
typedef NL_PROVIDER_UPDATE_OFFLOAD *PNL_PROVIDER_UPDATE_OFFLOAD;

typedef struct _NL_INDICATE_UPDATE_PATH {
    //
    // Handle given to provider
    //
    IN HANDLE ClientHandle;

    IN NL_PATH_INFO PathInfo;
} NL_INDICATE_UPDATE_PATH, *PNL_INDICATE_UPDATE_PATH;

typedef
NTSTATUS
(NTAPI NL_CLIENT_UPDATE_PATH)(
    IN PNL_INDICATE_UPDATE_PATH Args
    );
typedef NL_CLIENT_UPDATE_PATH *PNL_CLIENT_UPDATE_PATH;


//
// Define structures and prototypes for session management.
//

typedef struct _NL_REQUEST_INITIALIZE_SESSION_INFO {
    IN HANDLE ProviderHandle;
    OUT PVOID NlSessionState;
} NL_REQUEST_INITIALIZE_SESSION_INFO, *PNL_REQUEST_INITIALIZE_SESSION_INFO;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_INITIALIZE_SESSION_INFO)(
    IN OUT PNL_REQUEST_INITIALIZE_SESSION_INFO Args
    );
typedef NL_PROVIDER_INITIALIZE_SESSION_INFO 
    *PNL_PROVIDER_INITIALIZE_SESSION_INFO;

typedef struct _NL_REQUEST_QUERY_SESSION_INFO {
    IN HANDLE ProviderHandle;
    IN OUT NL_COMPARTMENT_ARG NlCompartment;
    IN PVOID NlSessionState;
    IN LONG Level;
    IN LONG OptName;
    OUT PUCHAR OptValBuffer;
    IN OUT ULONG OptValBufferLength;
} NL_REQUEST_QUERY_SESSION_INFO, *PNL_REQUEST_QUERY_SESSION_INFO;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_QUERY_SESSION_INFO)(
    IN OUT PNL_REQUEST_QUERY_SESSION_INFO Args
    );
typedef NL_PROVIDER_QUERY_SESSION_INFO *PNL_PROVIDER_QUERY_SESSION_INFO;

typedef
VOID
(NTAPI NL_CLIENT_SET_SESSION_INFO_COMPLETE)(
    IN PVOID RequestContext,
    IN NTSTATUS Status
    );
typedef NL_CLIENT_SET_SESSION_INFO_COMPLETE
    *PNL_CLIENT_SET_SESSION_INFO_COMPLETE;

#define NL_ANCILLARY_DATA_LENGTH_VARIABLE ((ULONG)-1)

typedef struct _NL_REQUEST_SET_SESSION_INFO {
    IN HANDLE ProviderHandle;
    IN OUT NL_COMPARTMENT_ARG NlCompartment;

    //
    // Interface the session is bound to, if any.
    //
    IN OUT NL_INTERFACE_ARG NlInterface;

    IN PVOID NlSessionState;
    IN ULONG Level;
    IN ULONG OptName;
    IN PUCHAR OptValBuffer;
    IN ULONG OptValBufferLength;

    //
    // The output buffer is used to support IOCTL's that have both 
    // an input and an output buffer.
    //
    OUT PUCHAR OutputBuffer;
    IN OUT ULONG OutputBufferLength;

    IN PVOID Context;
    IN PNL_CLIENT_SET_SESSION_INFO_COMPLETE CompletionRoutine;

    //
    // Length in bytes of ancillary data available for received datagrams.
    // A value of NL_ANCILLARY_DATA_LENGTH_VARIABLE indicates that the
    // caller of QueryAncillaryData should use the call-twice semantics.
    //
    OUT ULONG AncillaryDataLength;

    IN HANDLE InspectHandle;

    //
    // Indicates that the session state change that occurred is relevant to the
    // offload state.
    //
    OUT BOOLEAN OffloadStateAffected;
} NL_REQUEST_SET_SESSION_INFO, *PNL_REQUEST_SET_SESSION_INFO;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_SET_SESSION_INFO)(
    IN OUT PNL_REQUEST_SET_SESSION_INFO Args
    );
typedef NL_PROVIDER_SET_SESSION_INFO *PNL_PROVIDER_SET_SESSION_INFO;

typedef
VOID
(NTAPI NL_PROVIDER_CLEANUP_SESSION_INFO)(
    IN PVOID NlSessionState
    );
typedef NL_PROVIDER_CLEANUP_SESSION_INFO *PNL_PROVIDER_CLEANUP_SESSION_INFO;

typedef struct _NL_REQUEST_INHERIT_SESSION_INFO {
    IN HANDLE ProviderHandle;
    IN OUT PVOID OriginalSessionState;
    OUT PVOID NewSessionState;
} NL_REQUEST_INHERIT_SESSION_INFO, *PNL_REQUEST_INHERIT_SESSION_INFO;

typedef
NTSTATUS
(NTAPI NL_PROVIDER_INHERIT_SESSION_INFO)(
    IN OUT PNL_REQUEST_INHERIT_SESSION_INFO Args
    );
typedef NL_PROVIDER_INHERIT_SESSION_INFO *PNL_PROVIDER_INHERIT_SESSION_INFO;


typedef struct _NL_PROVIDER_CHARACTERISTICS {
    USHORT Version;
    USHORT Length;

    //
    // The protocol family of the network-layer protocol.
    // This value must match the value that appears in the
    // first argument to the Winsock socket() call.
    //
    ADDRESS_FAMILY NetworkProtocolId;

    USHORT AddressBytes;
    USHORT DefaultDataBackfill;
    USHORT DefaultRequestControlBackfill;
} NL_PROVIDER_CHARACTERISTICS, *PNL_PROVIDER_CHARACTERISTICS;

typedef struct _NL_PROVIDER_DISPATCH {
    USHORT Version;
    USHORT Length;

    //
    // Packetization entrypoints
    //
    PNL_PROVIDER_CHECKSUM_DATAGRAM ChecksumDatagram;
    PNL_PROVIDER_SEND_DATAGRAMS SendDatagrams;
    PNL_PROVIDER_CANCEL_SEND_DATAGRAMS CancelSendDatagrams;
    PNL_PROVIDER_GENERATE_CONTROL_MESSAGE GenerateControlMessage;

    //
    // Delivery entrypoints
    //
    PNL_PROVIDER_QUERY_ANCILLARY_DATA QueryAncillaryData;
    PNL_PROVIDER_FILTER_DATAGRAM_BY_SESSION_INFORMATION 
        FilterDatagramBySessionInformation;
    PNL_PROVIDER_FILTER_INDICATION_BY_SESSION_INFORMATION 
        FilterIndicationBySessionInformation;

    //
    // Path management entrypoints
    //
    PNL_PROVIDER_JOIN_PATH JoinPath;
    PNL_PROVIDER_LEAVE_PATH LeavePath;
    PNL_PROVIDER_QUERY_PATH_INFO QueryPathInformation;
    PNL_PROVIDER_SET_PATH_INFO SetPathInformation;
    PNL_PROVIDER_INITIATE_OFFLOAD InitiateOffload;
    PNL_PROVIDER_TERMINATE_OFFLOAD TerminateOffload;
    PNL_PROVIDER_UPDATE_OFFLOAD UpdateOffload;

    //
    // Next hop management entrypoints. 
    //
    PNL_PROVIDER_REFERENCE_NEXT_HOP ReferenceNextHop;
    PNL_PROVIDER_DEREFERENCE_NEXT_HOP DereferenceNextHop;
    
    //
    // Address management entrypoints
    //
    PNL_PROVIDER_REFERENCE_LOCAL_ADDRESS ReferenceLocalAddress;
    PNL_PROVIDER_DEREFERENCE_LOCAL_ADDRESS DereferenceLocalAddress;
    PNL_PROVIDER_VALIDATE_LOCAL_ADDRESS ValidateLocalAddress;
    
    //
    // Interface management entrypoints
    //
    PNL_PROVIDER_QUERY_INTERFACE QueryInterface;
    PNL_PROVIDER_SET_INTERFACE SetInterface;
    PNL_PROVIDER_QUERY_INTERFACE_PROPERTY QueryInterfaceProperty;
    PNL_PROVIDER_SET_INTERFACE_PROPERTY SetInterfaceProperty;
    PNL_PROVIDER_REFERENCE_INTERFACE ReferenceInterface;
    PNL_PROVIDER_DEREFERENCE_INTERFACE DereferenceInterface;
    
    //
    // Compartment management entrypoints
    //
    PNL_PROVIDER_REFERENCE_COMPARTMENT ReferenceCompartment;
    PNL_PROVIDER_DEREFERENCE_COMPARTMENT DereferenceCompartment;

    //
    // Session management entrypoints
    //
    PNL_PROVIDER_INITIALIZE_SESSION_INFO InitializeSessionInformation;
    PNL_PROVIDER_QUERY_SESSION_INFO QuerySessionInformation;
    PNL_PROVIDER_SET_SESSION_INFO SetSessionInformation;
    PNL_PROVIDER_CLEANUP_SESSION_INFO CleanupSessionInformation;
    PNL_PROVIDER_INHERIT_SESSION_INFO InheritSessionInformation;

    //
    // Generic entrypoints
    // Not currently used
    //
    // PNL_PROVIDER_QUERY_INFORMATION QueryInformation;
    // PNL_PROVIDER_SET_INFORMATION SetInformation;
    // PNL_PROVIDER_NOTIFY_CHANGE NotifyChange;

} NL_PROVIDER_DISPATCH, *PNL_PROVIDER_DISPATCH;

typedef struct _NL_CLIENT_DISPATCH {
    USHORT Version;
    USHORT Length;

    //
    // The protocol number of the upper-layer protocol.
    // This value must match the value that appears in packets,
    // as well as in the third argument to the Winsock socket() call.
    //
    USHORT UpperLayerProtocolId;

    USHORT DefaultRequestControlBackfill;

    BOOLEAN AllowMulticast : 1;
    BOOLEAN DefaultDontFragment : 1;

    //
    // This is set to TRUE by any clients who call the WFP transport layer
    // send themselves.  The NL provider will call it on behalf of any
    // clients who set this to FALSE.
    //
    BOOLEAN SendInvokesWfpTlCallout : 1;

    PNL_CLIENT_RECEIVE_DATAGRAMS ReceiveDatagrams;
    PNL_CLIENT_RECEIVE_CONTROL_MESSAGE ReceiveControlMessage;

    PNL_CLIENT_ADD_INTERFACE AddInterfaceNotification;
    PNL_CLIENT_DELETE_INTERFACE DeleteInterfaceNotification;
    PNL_CLIENT_UPDATE_INTERFACE UpdateInterfaceNotification;
    
    PNL_CLIENT_ADD_LOCAL_ADDRESS AddLocalAddressNotification;
    PNL_CLIENT_DELETE_LOCAL_ADDRESS DeleteLocalAddressNotification;

    PNL_CLIENT_UPDATE_PATH UpdatePathNotification;

    PNL_CLIENT_INITIATE_OFFLOAD_COMPLETE InitiateOffloadComplete;
    PNL_CLIENT_TERMINATE_OFFLOAD_COMPLETE TerminateOffloadComplete;
    PNL_CLIENT_UPDATE_OFFLOAD_COMPLETE UpdateOffloadComplete;

    PNL_CLIENT_INDICATE_OFFLOAD_EVENT IndicateOffloadEvent;
} NL_CLIENT_DISPATCH, *PNL_CLIENT_DISPATCH;

typedef struct _NL_CLIENT_NPI {
    HANDLE ProviderHandle;
    CONST NL_CLIENT_DISPATCH *Dispatch;
} NL_CLIENT_NPI, *PNL_CLIENT_NPI;

typedef struct _NL_PROVIDER_NPI {
    HANDLE ClientHandle;
    CONST NL_PROVIDER_DISPATCH *Dispatch;
} NL_PROVIDER_NPI, *PNL_PROVIDER_NPI;


//
// PNP event interface. 
//
typedef struct _NL_REQUEST_PNP_EVENT_COMPLETE {
    IN NTSTATUS Status;
    IN PNET_PNP_EVENT NetPnpEvent;
    IN PVOID ProviderContext;
} NL_REQUEST_PNP_EVENT_COMPLETE, *PNL_REQUEST_PNP_EVENT_COMPLETE;

typedef
VOID
(NTAPI NL_PNP_EVENT_PROVIDER_COMPLETE)(
    IN PNL_REQUEST_PNP_EVENT_COMPLETE Args
    );
typedef NL_PNP_EVENT_PROVIDER_COMPLETE *PNL_PNP_EVENT_PROVIDER_COMPLETE;

typedef struct _NL_INDICATE_PNP_EVENT {
    IN IPPROTO ProviderProtocol;
    IN IF_LUID Luid;
    IN PVOID PhysicalDeviceObject;
    IN PNET_PNP_EVENT NetPnpEvent;
    IN HANDLE ProviderContext;
} NL_INDICATE_PNP_EVENT, *PNL_INDICATE_PNP_EVENT;

typedef
NTSTATUS
(NTAPI NL_INDICATE_PNP_EVENT_CLIENT)(
    IN PNL_INDICATE_PNP_EVENT Args
    );
typedef NL_INDICATE_PNP_EVENT_CLIENT *PNL_INDICATE_PNP_EVENT_CLIENT;


typedef struct _NL_PNP_EVENT_PROVIDER_CHARACTERISTICS {
    USHORT Version;
    USHORT Length;

    //
    // The protocol family of the network-layer protocol.
    //
    ADDRESS_FAMILY NetworkProtocolId;
} NL_PNP_EVENT_PROVIDER_CHARACTERISTICS, *PNL_PNP_EVENT_PROVIDER_CHARACTERISTICS;

typedef struct _NL_PNP_EVENT_PROVIDER_DISPATCH {
    USHORT Version;
    USHORT Length;
    
    PNL_PNP_EVENT_PROVIDER_COMPLETE PnpEventCompleteInterface;
} NL_PNP_EVENT_PROVIDER_DISPATCH, *PNL_PNP_EVENT_PROVIDER_DISPATCH;

typedef struct _NL_PNP_EVENT_CLIENT_DISPATCH {
    USHORT Version;
    USHORT Length;

    PNL_INDICATE_PNP_EVENT_CLIENT PnpEventInterfaceNotification;
} NL_PNP_EVENT_CLIENT_DISPATCH, *PNL_PNP_EVENT_CLIENT_DISPATCH;

typedef struct _NL_PNP_EVENT_CLIENT_NPI {
    HANDLE ProviderHandle;
    CONST NL_PNP_EVENT_CLIENT_DISPATCH *Dispatch;
} NL_PNP_EVENT_CLIENT_NPI, *PNL_PNP_EVENT_CLIENT_NPI;

typedef struct _NL_PNP_EVENT_PROVIDER_NPI {
    HANDLE ClientHandle;
    CONST NL_PNP_EVENT_PROVIDER_DISPATCH *Dispatch;
} NL_PNP_EVENT_PROVIDER_NPI, *PNL_PNP_EVENT_PROVIDER_NPI;



#define NLS_PACKET_LIST_FIELDS                     \
    IN NET_BUFFER_LIST *NetBufferList;             \
                                                   \
    /*                                             \
     * Context to pass to inspect-complete routine \
     */                                            \
    IN PVOID CompletionContext;                    \
                                                   \
    /*                                             \
     * Service context to pass to cancel routine   \
     */                                            \
    OUT PVOID *CancelContext

typedef struct _NLS_PACKET_LIST {
    NLS_PACKET_LIST_FIELDS;
} NLS_PACKET_LIST;

typedef struct _NLS_PACKET_LIST_ENTRY {
    IN struct _NLS_PACKET_LIST_ENTRY *Next;
    NLS_PACKET_LIST_FIELDS;
} NLS_PACKET_LIST_ENTRY, *PNLS_PACKET_LIST_ENTRY;

//
// Local-Packet Inspection Definitions
//
typedef struct _NLS_INDICATE_INSPECT_LOCAL_PACKETS_OUT {
    NLS_PACKET_LIST_FIELDS;
    IN HANDLE ServiceHandle;
    IN COMPARTMENT_ID CompartmentId;
} NLS_INDICATE_INSPECT_LOCAL_PACKETS_OUT, *PNLS_INDICATE_INSPECT_LOCAL_PACKETS_OUT;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_LOCAL_PACKETS_OUT)(
    IN NLS_INDICATE_INSPECT_LOCAL_PACKETS_OUT *Args
    );

typedef NLS_CLIENT_INSPECT_LOCAL_PACKETS_OUT *PNLS_CLIENT_INSPECT_LOCAL_PACKETS_OUT;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_CANCEL_INSPECT_LOCAL_PACKETS_OUT)(   
    IN PVOID CancelContext
    );

typedef NLS_CLIENT_CANCEL_INSPECT_LOCAL_PACKETS_OUT *PNLS_CLIENT_CANCEL_INSPECT_LOCAL_PACKETS_OUT;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_LOCAL_PACKETS_OUT_COMPLETE)(
    IN PVOID CompletionContext,
    IN NTSTATUS Status
    );

typedef NLS_PROVIDER_INSPECT_LOCAL_PACKETS_OUT_COMPLETE *PNLS_PROVIDER_INSPECT_LOCAL_PACKETS_OUT_COMPLETE;

typedef struct _NLS_INDICATE_INSPECT_LOCAL_PACKETS_IN {
    IN HANDLE ServiceHandle;
    IN IF_INDEX InterfaceIndex;
    IN COMPARTMENT_ID CompartmentId;
    IN OUT NLS_PACKET_LIST_ENTRY FirstPacketList;
} NLS_INDICATE_INSPECT_LOCAL_PACKETS_IN, *PNLS_INDICATE_INSPECT_LOCAL_PACKETS_IN;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_LOCAL_PACKETS_IN)(
    IN NLS_INDICATE_INSPECT_LOCAL_PACKETS_IN *Args
    );

typedef NLS_CLIENT_INSPECT_LOCAL_PACKETS_IN *PNLS_CLIENT_INSPECT_LOCAL_PACKETS_IN;

typedef struct _NLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE {
    IN struct _NLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE *Next;
    IN PVOID CompletionContext;
    IN NTSTATUS Status;
} NLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE_ARGS, *PNLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE_ARGS;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE)(
    IN NLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE_ARGS *Args
    );

typedef NLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE *PNLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE;

//
// Remote-Packet Inspection Definitions
//

typedef struct _NLS_INDICATE_INSPECT_REMOTE_PACKETS_OUT {
    NLS_PACKET_LIST_FIELDS;
    IN HANDLE ServiceHandle;
    IN IF_INDEX InterfaceIndex;
    IN COMPARTMENT_ID CompartmentId;
} NLS_INDICATE_INSPECT_REMOTE_PACKETS_OUT, *PNLS_INDICATE_INSPECT_REMOTE_PACKETS_OUT;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_REMOTE_PACKETS_OUT)(
    IN NLS_INDICATE_INSPECT_REMOTE_PACKETS_OUT *Args
    );

typedef NLS_CLIENT_INSPECT_REMOTE_PACKETS_OUT *PNLS_CLIENT_INSPECT_REMOTE_PACKETS_OUT;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_CANCEL_INSPECT_REMOTE_PACKETS_OUT)(   
    IN PVOID CancelContext
    );

typedef NLS_CLIENT_CANCEL_INSPECT_REMOTE_PACKETS_OUT *PNLS_CLIENT_CANCEL_INSPECT_REMOTE_PACKETS_OUT;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_REMOTE_PACKETS_OUT_COMPLETE)(
    IN PVOID CompletionContext,
    IN NTSTATUS Status
    );

typedef NLS_PROVIDER_INSPECT_REMOTE_PACKETS_OUT_COMPLETE *PNLS_PROVIDER_INSPECT_REMOTE_PACKETS_OUT_COMPLETE;

typedef struct _NLS_INDICATE_INSPECT_REMOTE_PACKETS_IN {
    IN HANDLE ServiceHandle;
    IN IF_INDEX InterfaceIndex;
    IN COMPARTMENT_ID CompartmentId;
    IN OUT NLS_PACKET_LIST_ENTRY FirstPacketList;
} NLS_INDICATE_INSPECT_REMOTE_PACKETS_IN, *PNLS_INDICATE_INSPECT_REMOTE_PACKETS_IN;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_REMOTE_PACKETS_IN)(
    IN NLS_INDICATE_INSPECT_REMOTE_PACKETS_IN *Args
    );

typedef NLS_CLIENT_INSPECT_REMOTE_PACKETS_IN *PNLS_CLIENT_INSPECT_REMOTE_PACKETS_IN;

typedef struct _NLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE {
    IN struct _NLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE *Next;
    IN PVOID CompletionContext;
    IN NTSTATUS Status;
} NLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE_ARGS, *PNLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE_ARGS;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE)(
    IN NLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE_ARGS *Args
    );

typedef NLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE *PNLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE;

//
// Fragment Inspection Definitions
//

typedef struct _NLS_INDICATE_INSPECT_FRAGMENTS_OUT_ARGS {
    NLS_PACKET_LIST_FIELDS;
    IN HANDLE ServiceHandle;
    IN IF_INDEX InterfaceIndex;
    IN COMPARTMENT_ID CompartmentId;
} NLS_CLIENT_INSPECT_FRAGMENTS_OUT_ARGS, *PNLS_CLIENT_INSPECT_FRAGMENTS_OUT_ARGS;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_FRAGMENTS_OUT)(
    IN NLS_CLIENT_INSPECT_FRAGMENTS_OUT_ARGS *Args
    );

typedef NLS_CLIENT_INSPECT_FRAGMENTS_OUT *PNLS_CLIENT_INSPECT_FRAGMENTS_OUT;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_CANCEL_INSPECT_FRAGMENTS_OUT)(   
    IN PVOID CancelContext
    );

typedef NLS_CLIENT_CANCEL_INSPECT_FRAGMENTS_OUT *PNLS_CLIENT_CANCEL_INSPECT_FRAGMENTS_OUT;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_FRAGMENTS_OUT_COMPLETE)(
    IN PVOID CompletionContext,
    IN NTSTATUS Status
    );

typedef NLS_PROVIDER_INSPECT_FRAGMENTS_OUT_COMPLETE *PNLS_PROVIDER_INSPECT_FRAGMENTS_OUT_COMPLETE;

//
// Datagram Inspection Definitions
//

typedef struct _NLS_CLIENT_INSPECT_DATAGRAMS_IN_ARGS {
    IN HANDLE ServiceHandle;
    IN IF_INDEX InterfaceIndex;
    IN OUT NLS_PACKET_LIST_ENTRY FirstPacketList;
    IN COMPARTMENT_ID CompartmentId;
    IN SCOPE_ID RemoteScopeId;
    IN CONST VOID *RemoteAddress;
    IN SCOPE_ID LocalScopeId;
    IN CONST VOID *LocalAddress;
} NLS_CLIENT_INSPECT_DATAGRAMS_IN_ARGS, *PNLS_CLIENT_INSPECT_DATAGRAMS_IN_ARGS;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_DATAGRAMS_IN)(
    IN NLS_CLIENT_INSPECT_DATAGRAMS_IN_ARGS *Args
    );

typedef NLS_CLIENT_INSPECT_DATAGRAMS_IN *PNLS_CLIENT_INSPECT_DATAGRAMS_IN;

typedef struct _NLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE {
    IN struct _NLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE *Next;
    IN PVOID CompletionContext;
    IN NTSTATUS Status;
} NLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE_ARGS, *PNLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE_ARGS;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE)(
    IN NLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE_ARGS *Args
    );

typedef NLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE *PNLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE;

typedef struct _NLS_CLIENT_INSPECT_DATAGRAMS_OUT_ARGS {
    IN HANDLE ServiceHandle;
    IN IF_INDEX InterfaceIndex;
    IN OUT NLS_PACKET_LIST_ENTRY PacketList;
    IN SCOPE_ID RemoteScopeId;
    IN CONST UCHAR *RemoteAddress;
    IN CONST UCHAR *LocalAddress;
} NLS_CLIENT_INSPECT_DATAGRAMS_OUT_ARGS, *PNLS_CLIENT_INSPECT_DATAGRAMS_OUT_ARGS;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_INSPECT_DATAGRAMS_OUT)(
    IN OUT NLS_CLIENT_INSPECT_DATAGRAMS_OUT_ARGS *Args
    );

typedef NLS_CLIENT_INSPECT_DATAGRAMS_OUT *PNLS_CLIENT_INSPECT_DATAGRAMS_OUT;

typedef
NTSTATUS
(NTAPI NLS_CLIENT_CANCEL_INSPECT_DATAGRAMS_OUT)(   
    IN PVOID CancelContext
    );

typedef NLS_CLIENT_CANCEL_INSPECT_DATAGRAMS_OUT *PNLS_CLIENT_CANCEL_INSPECT_DATAGRAMS_OUT;

typedef struct _NLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE {
    IN struct _NLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE *Next;
    IN PVOID CompletionContext;
    IN NTSTATUS Status;
} NLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE_ARGS, *PNLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE_ARGS;

typedef
VOID
(NTAPI NLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE)(
    IN NLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE_ARGS *Args
    );

typedef NLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE *PNLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE;


//
// Attachment Definitions
//

//
// The NLS Provider is the network-layer protocol (e.g. IP).
// The NLS Client is the service wishing to add value.
//
typedef struct _NLS_PROVIDER_CHARACTERISTICS {
    USHORT Version;
    USHORT Length;

    //
    // The protocol family of the network-layer protocol.
    // This value must match the value that appears in the
    // first argument to the Winsock socket() call.
    //
    ULONG NetworkProtocolId;
} NLS_PROVIDER_CHARACTERISTICS, *PNLS_PROVIDER_CHARACTERISTICS;

typedef struct _NLS_PROVIDER_DISPATCH {
    USHORT Version;
    USHORT Length;

    PNLS_PROVIDER_INSPECT_LOCAL_PACKETS_OUT_COMPLETE InspectLocalPacketsOutComplete;
    PNLS_PROVIDER_INSPECT_LOCAL_PACKETS_IN_COMPLETE InspectLocalPacketsInComplete;

    PNLS_PROVIDER_INSPECT_REMOTE_PACKETS_OUT_COMPLETE InspectRemotePacketsOutComplete;
    PNLS_PROVIDER_INSPECT_REMOTE_PACKETS_IN_COMPLETE InspectRemotePacketsInComplete;

    PNLS_PROVIDER_INSPECT_FRAGMENTS_OUT_COMPLETE InspectFragmentsOutComplete;

    PNLS_PROVIDER_INSPECT_DATAGRAMS_IN_COMPLETE InspectDatagramsInComplete;
    PNLS_PROVIDER_INSPECT_DATAGRAMS_OUT_COMPLETE InspectDatagramsOutComplete;

    // PNLS_PROVIDER_XXX
} NLS_PROVIDER_DISPATCH, *PNLS_PROVIDER_DISPATCH;

typedef struct _NLS_CLIENT_DISPATCH {
    USHORT Version;
    USHORT Length;

    PNLS_CLIENT_INSPECT_LOCAL_PACKETS_OUT InspectLocalPacketsOut OPTIONAL;
    PNLS_CLIENT_CANCEL_INSPECT_LOCAL_PACKETS_OUT CancelInspectLocalPacketsOut OPTIONAL;
    PNLS_CLIENT_INSPECT_LOCAL_PACKETS_IN InspectLocalPacketsIn OPTIONAL;

    PNLS_CLIENT_INSPECT_REMOTE_PACKETS_OUT InspectRemotePacketsOut OPTIONAL;
    PNLS_CLIENT_CANCEL_INSPECT_REMOTE_PACKETS_OUT CancelInspectRemotePacketsOut OPTIONAL;

    PNLS_CLIENT_INSPECT_REMOTE_PACKETS_IN InspectRemotePacketsIn OPTIONAL;

    PNLS_CLIENT_INSPECT_FRAGMENTS_OUT InspectFragmentsOut OPTIONAL;
    PNLS_CLIENT_CANCEL_INSPECT_FRAGMENTS_OUT CancelInspectFragmentsOut OPTIONAL;

    PNLS_CLIENT_INSPECT_DATAGRAMS_IN InspectDatagramsIn OPTIONAL;
    PNLS_CLIENT_INSPECT_DATAGRAMS_OUT InspectDatagramsOut OPTIONAL;
    PNLS_CLIENT_CANCEL_INSPECT_DATAGRAMS_OUT CancelInspectDatagramsOut OPTIONAL;
} NLS_CLIENT_DISPATCH, *PNLS_CLIENT_DISPATCH;


extern CONST NPIID NPI_NETWORK_LAYER_SERVICE_ID;

typedef struct _NLS_CLIENT_NPI {
    HANDLE ServiceHandle;
    CONST NLS_CLIENT_DISPATCH *Dispatch;
} NLS_CLIENT_NPI, *PNLS_CLIENT_NPI;

typedef struct _NLS_PROVIDER_NPI {
    HANDLE ServiceHandle;
    CONST NLS_PROVIDER_DISPATCH *Dispatch;
} NLS_PROVIDER_NPI, *PNLS_PROVIDER_NPI;


#pragma warning(pop)

#ifdef __cplusplus
}
#endif

#endif // _NETIOK_

