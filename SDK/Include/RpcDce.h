/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    rpcdce.h

Abstract:

    This module contains the DCE RPC runtime APIs.

--*/

#ifndef __RPCDCE_H__
#define __RPCDCE_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef DECLSPEC_NORETURN
#if (_MSC_VER >= 1200) && !defined(MIDL_PASS)
#define DECLSPEC_NORETURN   __declspec(noreturn)
#else
#define DECLSPEC_NORETURN
#endif
#endif

/*typedef char small;*/
/*typedef unsigned char byte;*/
/*typedef unsigned char boolean;*/

typedef I_RPC_HANDLE RPC_BINDING_HANDLE;
typedef RPC_BINDING_HANDLE handle_t;
#define rpc_binding_handle_t RPC_BINDING_HANDLE

#ifndef GUID_DEFINED
#include <guiddef.h>
#endif /* GUID_DEFINED */

#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef GUID UUID;
#ifndef uuid_t
#define uuid_t UUID
#endif
#endif

typedef struct _RPC_BINDING_VECTOR
{
    unsigned long Count;
    RPC_BINDING_HANDLE BindingH[1];
} RPC_BINDING_VECTOR;
#ifndef rpc_binding_vector_t
#define rpc_binding_vector_t RPC_BINDING_VECTOR
#endif

typedef struct _UUID_VECTOR
{
  unsigned long Count;
  UUID *Uuid[1];
} UUID_VECTOR;
#ifndef uuid_vector_t
#define uuid_vector_t UUID_VECTOR
#endif

typedef void __RPC_FAR * RPC_IF_HANDLE;

#ifndef IFID_DEFINED
#define IFID_DEFINED
typedef struct _RPC_IF_ID
{
    UUID Uuid;
    unsigned short VersMajor;
    unsigned short VersMinor;
} RPC_IF_ID;
#endif

#define RPC_C_BINDING_INFINITE_TIMEOUT 10
#define RPC_C_BINDING_MIN_TIMEOUT 0
#define RPC_C_BINDING_DEFAULT_TIMEOUT 5
#define RPC_C_BINDING_MAX_TIMEOUT 9

#define RPC_C_CANCEL_INFINITE_TIMEOUT -1

#define RPC_C_LISTEN_MAX_CALLS_DEFAULT 1234
#define RPC_C_PROTSEQ_MAX_REQS_DEFAULT 10

// RPC_POLICY EndpointFlags.
#define RPC_C_BIND_TO_ALL_NICS          1
#define RPC_C_USE_INTERNET_PORT         0x1
#define RPC_C_USE_INTRANET_PORT         0x2
#define RPC_C_DONT_FAIL                          0x4

// RPC_POLICY EndpointFlags specific to the Falcon/RPC transport (deprecated):
/*
#define RPC_C_MQ_TEMPORARY                  0x0000
#define RPC_C_MQ_PERMANENT                  0x0001
#define RPC_C_MQ_CLEAR_ON_OPEN              0x0002
#define RPC_C_MQ_USE_EXISTING_SECURITY      0x0004
#define RPC_C_MQ_AUTHN_LEVEL_NONE           0x0000
#define RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY  0x0008
#define RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY    0x0010
*/

// Client: RpcBindingSetOption() values for the Falcon/RPC transport (some are deprecated):
/*
#define RPC_C_OPT_MQ_DELIVERY            1
#define RPC_C_OPT_MQ_PRIORITY            2
#define RPC_C_OPT_MQ_JOURNAL             3
#define RPC_C_OPT_MQ_ACKNOWLEDGE         4
#define RPC_C_OPT_MQ_AUTHN_SERVICE       5
#define RPC_C_OPT_MQ_AUTHN_LEVEL         6
#define RPC_C_OPT_MQ_TIME_TO_REACH_QUEUE 7
#define RPC_C_OPT_MQ_TIME_TO_BE_RECEIVED 8
*/
#define RPC_C_OPT_BINDING_NONCAUSAL      9
#define RPC_C_OPT_SECURITY_CALLBACK      10
#define RPC_C_OPT_UNIQUE_BINDING         11
#define RPC_C_OPT_CALL_TIMEOUT           12
#define RPC_C_OPT_DONT_LINGER            13
#define RPC_C_OPT_TRUST_PEER             14
#define RPC_C_OPT_ASYNC_BLOCK            15
#define RPC_C_OPT_OPTIMIZE_TIME          16
#define RPC_C_OPT_MAX_OPTIONS            17

/*
Falcon/Rpc options are deprecated
#define RPC_C_MQ_EXPRESS                0  // Client: RPC_C_MQ_DELIVERY.
#define RPC_C_MQ_RECOVERABLE            1

#define RPC_C_MQ_JOURNAL_NONE           0  // Client: RPC_C_MQ_JOURNAL.
#define RPC_C_MQ_JOURNAL_DEADLETTER     1
#define RPC_C_MQ_JOURNAL_ALWAYS         2
*/

// flags for RpcServerInqAuthClientEx
//
#define RPC_C_FULL_CERT_CHAIN 0x0001



#ifdef RPC_UNICODE_SUPPORTED
typedef struct _RPC_PROTSEQ_VECTORA
{
    unsigned int Count;
    unsigned char __RPC_FAR * Protseq[1];
} RPC_PROTSEQ_VECTORA;

typedef struct _RPC_PROTSEQ_VECTORW
{
    unsigned int Count;
    unsigned short __RPC_FAR * Protseq[1];
} RPC_PROTSEQ_VECTORW;

#ifdef UNICODE
#define RPC_PROTSEQ_VECTOR RPC_PROTSEQ_VECTORW
#else /* UNICODE */
#define RPC_PROTSEQ_VECTOR RPC_PROTSEQ_VECTORA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

typedef struct _RPC_PROTSEQ_VECTOR
{
    unsigned int Count;
    unsigned char __RPC_FAR * Protseq[1];
} RPC_PROTSEQ_VECTOR;

#endif /* RPC_UNICODE_SUPPORTED */
typedef struct _RPC_POLICY {
    unsigned int Length ;
    unsigned long EndpointFlags ;
    unsigned long NICFlags ;
    } RPC_POLICY,  __RPC_FAR *PRPC_POLICY ;

typedef void __RPC_USER
RPC_OBJECT_INQ_FN (
    IN UUID __RPC_FAR * ObjectUuid,
    OUT UUID __RPC_FAR * TypeUuid,
    OUT RPC_STATUS __RPC_FAR * Status
    );

typedef RPC_STATUS RPC_ENTRY
RPC_IF_CALLBACK_FN (
    IN RPC_IF_HANDLE  InterfaceUuid,
    IN void *Context
    ) ;

typedef void RPC_ENTRY
RPC_SECURITY_CALLBACK_FN (
    IN void *Context
    ) ;

#define RPC_MGR_EPV void

typedef struct
{
    unsigned int Count;
    unsigned long Stats[1];
} RPC_STATS_VECTOR;

#define RPC_C_STATS_CALLS_IN 0
#define RPC_C_STATS_CALLS_OUT 1
#define RPC_C_STATS_PKTS_IN 2
#define RPC_C_STATS_PKTS_OUT 3

typedef struct
{
  unsigned long Count;
  RPC_IF_ID __RPC_FAR * IfId[1];
} RPC_IF_ID_VECTOR;

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingCopy (
    IN RPC_BINDING_HANDLE SourceBinding,
    OUT RPC_BINDING_HANDLE __RPC_FAR * DestinationBinding
    );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingFree (
    IN OUT RPC_BINDING_HANDLE __RPC_FAR * Binding
    );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetOption( IN RPC_BINDING_HANDLE hBinding,
                     IN unsigned long      option,
                     IN ULONG_PTR          optionValue );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqOption( IN  RPC_BINDING_HANDLE hBinding,
                     IN  unsigned long      option,
                     OUT ULONG_PTR         *pOptionValue );

/* client */

#if !defined(_KRPCENV_)

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingFromStringBindingA (
    IN unsigned char __RPC_FAR * StringBinding,
    OUT RPC_BINDING_HANDLE __RPC_FAR * Binding
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingFromStringBindingW (
    IN unsigned short __RPC_FAR * StringBinding,
    OUT RPC_BINDING_HANDLE __RPC_FAR * Binding
    );

#ifdef UNICODE
#define RpcBindingFromStringBinding RpcBindingFromStringBindingW
#else /* UNICODE */
#define RpcBindingFromStringBinding RpcBindingFromStringBindingA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingFromStringBinding (
    IN unsigned char __RPC_FAR * StringBinding,
    OUT RPC_BINDING_HANDLE __RPC_FAR * Binding
    );

#endif /* RPC_UNICODE_SUPPORTED */

#endif /* _KRPCENV_ */

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcSsGetContextBinding (
    IN void *ContextHandle,
    OUT RPC_BINDING_HANDLE __RPC_FAR * Binding
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqObject (
    IN RPC_BINDING_HANDLE Binding,
    OUT UUID __RPC_FAR * ObjectUuid
    );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingReset (
    IN RPC_BINDING_HANDLE Binding
    );

/* RpcBindingServerFromClient : UNSUPPORTED */
/* RpcBindingSetAuthInfo */

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetObject (
    IN RPC_BINDING_HANDLE Binding,
    IN UUID __RPC_FAR * ObjectUuid
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqDefaultProtectLevel(
    IN  unsigned long AuthnSvc,
    OUT unsigned long __RPC_FAR *AuthnLevel
    );

/* client/server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingToStringBindingA (
    IN RPC_BINDING_HANDLE Binding,
    OUT unsigned char __RPC_FAR * __RPC_FAR * StringBinding
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingToStringBindingW (
    IN RPC_BINDING_HANDLE Binding,
    OUT unsigned short __RPC_FAR * __RPC_FAR * StringBinding
    );

#ifdef UNICODE
#define RpcBindingToStringBinding RpcBindingToStringBindingW
#else /* UNICODE */
#define RpcBindingToStringBinding RpcBindingToStringBindingA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingToStringBinding (
    IN RPC_BINDING_HANDLE Binding,
    OUT unsigned char __RPC_FAR * __RPC_FAR * StringBinding
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingVectorFree (
    IN OUT RPC_BINDING_VECTOR __RPC_FAR * __RPC_FAR * BindingVector
    );

/* client/server */

#if !defined(_KRPCENV_)

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringBindingComposeA (
    IN OPTIONAL unsigned char __RPC_FAR * ObjUuid,
    IN OPTIONAL unsigned char __RPC_FAR * Protseq,
    IN OPTIONAL unsigned char __RPC_FAR * NetworkAddr,
    IN OPTIONAL unsigned char __RPC_FAR * Endpoint,
    IN OPTIONAL unsigned char __RPC_FAR * Options,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * StringBinding
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringBindingComposeW (
    IN OPTIONAL unsigned short __RPC_FAR * ObjUuid,
    IN OPTIONAL unsigned short __RPC_FAR * Protseq,
    IN OPTIONAL unsigned short __RPC_FAR * NetworkAddr,
    IN OPTIONAL unsigned short __RPC_FAR * Endpoint,
    IN OPTIONAL unsigned short __RPC_FAR * Options,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * StringBinding
    );

#ifdef UNICODE
#define RpcStringBindingCompose RpcStringBindingComposeW
#else /* UNICODE */
#define RpcStringBindingCompose RpcStringBindingComposeA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringBindingCompose (
    IN OPTIONAL unsigned char __RPC_FAR * ObjUuid,
    IN OPTIONAL unsigned char __RPC_FAR * Protseq,
    IN OPTIONAL unsigned char __RPC_FAR * NetworkAddr,
    IN OPTIONAL unsigned char __RPC_FAR * Endpoint,
    IN OPTIONAL unsigned char __RPC_FAR * Options,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * StringBinding
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* client/server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringBindingParseA (
    IN unsigned char __RPC_FAR * StringBinding,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ObjUuid,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * Protseq,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * NetworkAddr,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * Endpoint,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * NetworkOptions
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringBindingParseW (
    IN unsigned short __RPC_FAR * StringBinding,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * ObjUuid,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * Protseq,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * NetworkAddr,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * Endpoint,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * NetworkOptions
    );

#ifdef UNICODE
#define RpcStringBindingParse RpcStringBindingParseW
#else /* UNICODE */
#define RpcStringBindingParse RpcStringBindingParseA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringBindingParse (
    IN unsigned char __RPC_FAR * StringBinding,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ObjUuid,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * Protseq,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * NetworkAddr,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * Endpoint,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * NetworkOptions
    );

#endif /* RPC_UNICODE_SUPPORTED */

#endif /* _KRPCENV_ */

/* client/server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringFreeA (
    IN OUT unsigned char __RPC_FAR * __RPC_FAR * String
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringFreeW (
    IN OUT unsigned short __RPC_FAR * __RPC_FAR * String
    );

#ifdef UNICODE
#define RpcStringFree RpcStringFreeW
#else /* UNICODE */
#define RpcStringFree RpcStringFreeA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcStringFree (
    IN OUT unsigned char __RPC_FAR * __RPC_FAR * String
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcIfInqId (
    IN RPC_IF_HANDLE RpcIfHandle,
    OUT RPC_IF_ID __RPC_FAR * RpcIfId
    );

/* client/server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNetworkIsProtseqValidA (
    IN unsigned char __RPC_FAR * Protseq
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNetworkIsProtseqValidW (
    IN unsigned short __RPC_FAR * Protseq
    );

#ifdef UNICODE
#define RpcNetworkIsProtseqValid RpcNetworkIsProtseqValidW
#else /* UNICODE */
#define RpcNetworkIsProtseqValid RpcNetworkIsProtseqValidA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNetworkIsProtseqValid (
    IN unsigned char __RPC_FAR * Protseq
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqComTimeout (
    IN RPC_BINDING_HANDLE Binding,
    OUT unsigned int __RPC_FAR * Timeout
    );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtSetComTimeout (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned int Timeout
    );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtSetCancelTimeout(
    long Timeout
    );


/* server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNetworkInqProtseqsA (
    OUT RPC_PROTSEQ_VECTORA __RPC_FAR * __RPC_FAR * ProtseqVector
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNetworkInqProtseqsW (
    OUT RPC_PROTSEQ_VECTORW __RPC_FAR * __RPC_FAR * ProtseqVector
    );

#ifdef UNICODE
#define RpcNetworkInqProtseqs RpcNetworkInqProtseqsW
#else /* UNICODE */
#define RpcNetworkInqProtseqs RpcNetworkInqProtseqsA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNetworkInqProtseqs (
    OUT RPC_PROTSEQ_VECTOR __RPC_FAR * __RPC_FAR * ProtseqVector
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcObjectInqType (
    IN UUID __RPC_FAR * ObjUuid,
    OUT OPTIONAL UUID __RPC_FAR * TypeUuid
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcObjectSetInqFn (
    IN RPC_OBJECT_INQ_FN __RPC_FAR * InquiryFn
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcObjectSetType (
    IN UUID __RPC_FAR * ObjUuid,
    IN OPTIONAL UUID __RPC_FAR * TypeUuid
    );

/* server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcProtseqVectorFreeA (
    IN OUT RPC_PROTSEQ_VECTORA __RPC_FAR * __RPC_FAR * ProtseqVector
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcProtseqVectorFreeW (
    IN OUT RPC_PROTSEQ_VECTORW __RPC_FAR * __RPC_FAR * ProtseqVector
    );

#ifdef UNICODE
#define RpcProtseqVectorFree RpcProtseqVectorFreeW
#else /* UNICODE */
#define RpcProtseqVectorFree RpcProtseqVectorFreeA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcProtseqVectorFree (
    IN OUT RPC_PROTSEQ_VECTOR __RPC_FAR * __RPC_FAR * ProtseqVector
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqBindings (
    OUT RPC_BINDING_VECTOR __RPC_FAR * __RPC_FAR * BindingVector
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqIf (
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL UUID __RPC_FAR * MgrTypeUuid,
    OUT RPC_MGR_EPV __RPC_FAR * __RPC_FAR * MgrEpv
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerListen (
    IN unsigned int MinimumCallThreads,
    IN unsigned int MaxCalls,
    IN unsigned int DontWait
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerRegisterIf (
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL UUID __RPC_FAR * MgrTypeUuid,
    IN OPTIONAL RPC_MGR_EPV __RPC_FAR * MgrEpv
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerRegisterIfEx (
    IN RPC_IF_HANDLE IfSpec,
    IN UUID __RPC_FAR * MgrTypeUuid,
    IN RPC_MGR_EPV __RPC_FAR * MgrEpv,
    IN unsigned int Flags,
    IN unsigned int MaxCalls,
    IN RPC_IF_CALLBACK_FN __RPC_FAR *IfCallback
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerRegisterIf2 (
    IN RPC_IF_HANDLE IfSpec,
    IN UUID * MgrTypeUuid,
    IN RPC_MGR_EPV * MgrEpv,
    IN unsigned int Flags,
    IN unsigned int MaxCalls,
    IN unsigned int MaxRpcSize,
    IN RPC_IF_CALLBACK_FN *IfCallbackFn
    );


/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUnregisterIf (
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL UUID __RPC_FAR * MgrTypeUuid,
    IN unsigned int WaitForCallsToComplete
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUnregisterIfEx (
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL UUID __RPC_FAR * MgrTypeUuid,
    IN int RundownContextHandles
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseAllProtseqs (
    IN unsigned int MaxCalls,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseAllProtseqsEx (
    IN unsigned int MaxCalls,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseAllProtseqsIf (
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseAllProtseqsIfEx (
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );


/* server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqA (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqExA (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqW (
    IN unsigned short __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqExW (
    IN unsigned short __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

#ifdef UNICODE
#define RpcServerUseProtseq RpcServerUseProtseqW
#define RpcServerUseProtseqEx RpcServerUseProtseqExW
#else /* UNICODE */
#define RpcServerUseProtseq RpcServerUseProtseqA
#define RpcServerUseProtseqEx RpcServerUseProtseqExA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseq (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEx (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEpA (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN unsigned char __RPC_FAR * Endpoint,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEpExA (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN unsigned char __RPC_FAR * Endpoint,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEpW (
    IN unsigned short __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN unsigned short __RPC_FAR * Endpoint,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEpExW (
    IN unsigned short __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN unsigned short __RPC_FAR * Endpoint,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

#ifdef UNICODE
#define RpcServerUseProtseqEp RpcServerUseProtseqEpW
#define RpcServerUseProtseqEpEx RpcServerUseProtseqEpExW
#else /* UNICODE */
#define RpcServerUseProtseqEp RpcServerUseProtseqEpA
#define RpcServerUseProtseqEpEx RpcServerUseProtseqEpExA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEp (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN unsigned char __RPC_FAR * Endpoint,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqEpEx (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN unsigned char __RPC_FAR * Endpoint,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* server */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqIfA (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqIfExA (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqIfW (
    IN unsigned short __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqIfExW (
    IN unsigned short __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

#ifdef UNICODE
#define RpcServerUseProtseqIf RpcServerUseProtseqIfW
#define RpcServerUseProtseqIfEx RpcServerUseProtseqIfExW
#else /* UNICODE */
#define RpcServerUseProtseqIf RpcServerUseProtseqIfA
#define RpcServerUseProtseqIfEx RpcServerUseProtseqIfExA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqIf (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN OPTIONAL void __RPC_FAR * SecurityDescriptor
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerUseProtseqIfEx (
    IN unsigned char __RPC_FAR * Protseq,
    IN unsigned int MaxCalls,
    IN RPC_IF_HANDLE IfSpec,
    IN void __RPC_FAR * SecurityDescriptor,
    IN PRPC_POLICY Policy
    );

#endif /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
void
RPC_ENTRY
RpcServerYield (
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtStatsVectorFree (
    IN RPC_STATS_VECTOR ** StatsVector
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqStats (
    IN RPC_BINDING_HANDLE Binding,
    OUT RPC_STATS_VECTOR ** Statistics
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtIsServerListening (
    IN RPC_BINDING_HANDLE Binding
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtStopServerListening (
    IN RPC_BINDING_HANDLE Binding
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtWaitServerListen (
    void
    );

/* server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtSetServerStackSize (
    IN unsigned long ThreadStackSize
    );

/* server */
RPCRTAPI
void
RPC_ENTRY
RpcSsDontSerializeContext (
    void
    );

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEnableIdleCleanup (
    void
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqIfIds (
    IN RPC_BINDING_HANDLE Binding,
    OUT RPC_IF_ID_VECTOR __RPC_FAR * __RPC_FAR * IfIdVector
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcIfIdVectorFree (
    IN OUT RPC_IF_ID_VECTOR __RPC_FAR * __RPC_FAR * IfIdVector
    );

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqServerPrincNameA (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned long AuthnSvc,
    OUT unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqServerPrincNameW (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned long AuthnSvc,
    OUT unsigned short __RPC_FAR * __RPC_FAR * ServerPrincName
    );

#ifdef UNICODE
#define RpcMgmtInqServerPrincName RpcMgmtInqServerPrincNameW
#else /* UNICODE */
#define RpcMgmtInqServerPrincName RpcMgmtInqServerPrincNameA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtInqServerPrincName (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned long AuthnSvc,
    OUT unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName
    );

#endif /* RPC_UNICODE_SUPPORTED */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqDefaultPrincNameA (
    IN unsigned long AuthnSvc,
    OUT unsigned char __RPC_FAR * __RPC_FAR * PrincName
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqDefaultPrincNameW (
    IN unsigned long AuthnSvc,
    OUT unsigned short __RPC_FAR * __RPC_FAR * PrincName
    );

#ifdef UNICODE
#define RpcServerInqDefaultPrincName RpcServerInqDefaultPrincNameW
#else /* UNICODE */
#define RpcServerInqDefaultPrincName RpcServerInqDefaultPrincNameA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqDefaultPrincName (
    IN unsigned long AuthnSvc,
    OUT unsigned char __RPC_FAR * __RPC_FAR * PrincName
    );

#endif /* RPC_UNICODE_SUPPORTED */

/* client */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpResolveBinding (
    IN RPC_BINDING_HANDLE Binding,
    IN RPC_IF_HANDLE IfSpec
    );

/* client */

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNsBindingInqEntryNameA (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned long EntryNameSyntax,
    OUT unsigned char __RPC_FAR * __RPC_FAR * EntryName
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNsBindingInqEntryNameW (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned long EntryNameSyntax,
    OUT unsigned short __RPC_FAR * __RPC_FAR * EntryName
    );

#ifdef UNICODE
#define RpcNsBindingInqEntryName RpcNsBindingInqEntryNameW
#else /* UNICODE */
#define RpcNsBindingInqEntryName RpcNsBindingInqEntryNameA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcNsBindingInqEntryName (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned long EntryNameSyntax,
    OUT unsigned char __RPC_FAR * __RPC_FAR * EntryName
    );

#endif /* RPC_UNICODE_SUPPORTED */

typedef void __RPC_FAR * RPC_AUTH_IDENTITY_HANDLE;
typedef void __RPC_FAR * RPC_AUTHZ_HANDLE;

#define RPC_C_AUTHN_LEVEL_DEFAULT       0
#define RPC_C_AUTHN_LEVEL_NONE          1
#define RPC_C_AUTHN_LEVEL_CONNECT       2
#define RPC_C_AUTHN_LEVEL_CALL          3
#define RPC_C_AUTHN_LEVEL_PKT           4
#define RPC_C_AUTHN_LEVEL_PKT_INTEGRITY 5
#define RPC_C_AUTHN_LEVEL_PKT_PRIVACY   6

#define RPC_C_IMP_LEVEL_DEFAULT      0
#define RPC_C_IMP_LEVEL_ANONYMOUS    1
#define RPC_C_IMP_LEVEL_IDENTIFY     2
#define RPC_C_IMP_LEVEL_IMPERSONATE  3
#define RPC_C_IMP_LEVEL_DELEGATE     4

#define RPC_C_QOS_IDENTITY_STATIC    0
#define RPC_C_QOS_IDENTITY_DYNAMIC   1

#define RPC_C_QOS_CAPABILITIES_DEFAULT                        0x0
#define RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH                    0x1
#define RPC_C_QOS_CAPABILITIES_MAKE_FULLSIC                   0x2
#define RPC_C_QOS_CAPABILITIES_ANY_AUTHORITY                  0x4
#define RPC_C_QOS_CAPABILITIES_IGNORE_DELEGATE_FAILURE        0x8
#define RPC_C_QOS_CAPABILITIES_LOCAL_MA_HINT                 0x10

#define RPC_C_PROTECT_LEVEL_DEFAULT       (RPC_C_AUTHN_LEVEL_DEFAULT)
#define RPC_C_PROTECT_LEVEL_NONE          (RPC_C_AUTHN_LEVEL_NONE)
#define RPC_C_PROTECT_LEVEL_CONNECT       (RPC_C_AUTHN_LEVEL_CONNECT)
#define RPC_C_PROTECT_LEVEL_CALL          (RPC_C_AUTHN_LEVEL_CALL)
#define RPC_C_PROTECT_LEVEL_PKT           (RPC_C_AUTHN_LEVEL_PKT)
#define RPC_C_PROTECT_LEVEL_PKT_INTEGRITY (RPC_C_AUTHN_LEVEL_PKT_INTEGRITY)
#define RPC_C_PROTECT_LEVEL_PKT_PRIVACY   (RPC_C_AUTHN_LEVEL_PKT_PRIVACY)

#define RPC_C_AUTHN_NONE          0
#define RPC_C_AUTHN_DCE_PRIVATE   1
#define RPC_C_AUTHN_DCE_PUBLIC    2
#define RPC_C_AUTHN_DEC_PUBLIC    4
#define RPC_C_AUTHN_GSS_NEGOTIATE 9
#define RPC_C_AUTHN_WINNT        10
#define RPC_C_AUTHN_GSS_SCHANNEL 14
#define RPC_C_AUTHN_GSS_KERBEROS 16
#define RPC_C_AUTHN_DPA          17
#define RPC_C_AUTHN_MSN          18
#define RPC_C_AUTHN_DIGEST       21
#define RPC_C_AUTHN_MQ          100
#define RPC_C_AUTHN_DEFAULT     0xFFFFFFFFL

#define RPC_C_NO_CREDENTIALS ((RPC_AUTH_IDENTITY_HANDLE) MAXUINT_PTR)

#define RPC_C_SECURITY_QOS_VERSION  1L
#define RPC_C_SECURITY_QOS_VERSION_1  1L

typedef struct _RPC_SECURITY_QOS {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
} RPC_SECURITY_QOS, *PRPC_SECURITY_QOS;

#ifndef _AUTH_IDENTITY_DEFINED
#define _AUTH_IDENTITY_DEFINED

#define SEC_WINNT_AUTH_IDENTITY_ANSI    0x1
#define SEC_WINNT_AUTH_IDENTITY_UNICODE 0x2

typedef struct _SEC_WINNT_AUTH_IDENTITY_W {
  unsigned short __RPC_FAR *User;
  unsigned long UserLength;
  unsigned short __RPC_FAR *Domain;
  unsigned long DomainLength;
  unsigned short __RPC_FAR *Password;
  unsigned long PasswordLength;
  unsigned long Flags;
} SEC_WINNT_AUTH_IDENTITY_W, *PSEC_WINNT_AUTH_IDENTITY_W;

#define _AUTH_IDENTITY_A_DEFINED

typedef struct _SEC_WINNT_AUTH_IDENTITY_A {
  unsigned char __RPC_FAR *User;
  unsigned long UserLength;
  unsigned char __RPC_FAR *Domain;
  unsigned long DomainLength;
  unsigned char __RPC_FAR *Password;
  unsigned long PasswordLength;
  unsigned long Flags;
} SEC_WINNT_AUTH_IDENTITY_A, *PSEC_WINNT_AUTH_IDENTITY_A;

#ifdef UNICODE
#define SEC_WINNT_AUTH_IDENTITY SEC_WINNT_AUTH_IDENTITY_W
#define PSEC_WINNT_AUTH_IDENTITY PSEC_WINNT_AUTH_IDENTITY_W
#define _SEC_WINNT_AUTH_IDENTITY _SEC_WINNT_AUTH_IDENTITY_W
#else // UNICODE
#define SEC_WINNT_AUTH_IDENTITY SEC_WINNT_AUTH_IDENTITY_A
#define PSEC_WINNT_AUTH_IDENTITY PSEC_WINNT_AUTH_IDENTITY_A
#define _SEC_WINNT_AUTH_IDENTITY _SEC_WINNT_AUTH_IDENTITY_A
#endif // UNICODE

#define RPC_C_SECURITY_QOS_VERSION_2 2L

#define RPC_C_AUTHN_INFO_TYPE_HTTP                  1

#define RPC_C_HTTP_AUTHN_TARGET_SERVER              1
#define RPC_C_HTTP_AUTHN_TARGET_PROXY               2

#define RPC_C_HTTP_AUTHN_SCHEME_BASIC      0x00000001
#define RPC_C_HTTP_AUTHN_SCHEME_NTLM       0x00000002
#define RPC_C_HTTP_AUTHN_SCHEME_PASSPORT   0x00000004
#define RPC_C_HTTP_AUTHN_SCHEME_DIGEST     0x00000008
#define RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE  0x00000010
#define RPC_C_HTTP_AUTHN_SCHEME_CERT       0x00010000

#define RPC_C_HTTP_FLAG_USE_SSL                     1
#define RPC_C_HTTP_FLAG_USE_FIRST_AUTH_SCHEME       2

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_W
{
    SEC_WINNT_AUTH_IDENTITY_W *TransportCredentials;
    unsigned long Flags;
    unsigned long AuthenticationTarget;
    unsigned long NumberOfAuthnSchemes;
    unsigned long *AuthnSchemes;
    unsigned short __RPC_FAR *ServerCertificateSubject;
} RPC_HTTP_TRANSPORT_CREDENTIALS_W, *PRPC_HTTP_TRANSPORT_CREDENTIALS_W;

typedef struct _RPC_HTTP_TRANSPORT_CREDENTIALS_A
{
    SEC_WINNT_AUTH_IDENTITY_A *TransportCredentials;
    unsigned long Flags;
    unsigned long AuthenticationTarget;
    unsigned long NumberOfAuthnSchemes;
    unsigned long *AuthnSchemes;
    unsigned char __RPC_FAR *ServerCertificateSubject;
} RPC_HTTP_TRANSPORT_CREDENTIALS_A, *PRPC_HTTP_TRANSPORT_CREDENTIALS_A;

typedef struct _RPC_SECURITY_QOS_V2_W {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union 
      {
      RPC_HTTP_TRANSPORT_CREDENTIALS_W *HttpCredentials;
      } u;
} RPC_SECURITY_QOS_V2_W, *PRPC_SECURITY_QOS_V2_W;

typedef struct _RPC_SECURITY_QOS_V2_A {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union 
      {
      RPC_HTTP_TRANSPORT_CREDENTIALS_A *HttpCredentials;
      } u;
} RPC_SECURITY_QOS_V2_A, *PRPC_SECURITY_QOS_V2_A;

#define RPC_C_SECURITY_QOS_VERSION_3 3L

typedef struct _RPC_SECURITY_QOS_V3_W {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union 
      {
      RPC_HTTP_TRANSPORT_CREDENTIALS_W *HttpCredentials;
      } u;
  void *Sid;
} RPC_SECURITY_QOS_V3_W, *PRPC_SECURITY_QOS_V3_W;

typedef struct _RPC_SECURITY_QOS_V3_A {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union 
      {
      RPC_HTTP_TRANSPORT_CREDENTIALS_A *HttpCredentials;
      } u;
  void *Sid;
} RPC_SECURITY_QOS_V3_A, *PRPC_SECURITY_QOS_V3_A;

#define RPC_C_SECURITY_QOS_VERSION_4 4L

typedef struct _RPC_SECURITY_QOS_V4_W {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union 
      {
      RPC_HTTP_TRANSPORT_CREDENTIALS_W *HttpCredentials;
      } u;
  void *Sid;
  unsigned int EffectiveOnly;
} RPC_SECURITY_QOS_V4_W, *PRPC_SECURITY_QOS_V4_W;

typedef struct _RPC_SECURITY_QOS_V4_A {
  unsigned long Version;
  unsigned long Capabilities;
  unsigned long IdentityTracking;
  unsigned long ImpersonationType;
  unsigned long AdditionalSecurityInfoType;
  union 
      {
      RPC_HTTP_TRANSPORT_CREDENTIALS_A *HttpCredentials;
      } u;
  void *Sid;
  unsigned int EffectiveOnly;
} RPC_SECURITY_QOS_V4_A, *PRPC_SECURITY_QOS_V4_A;

#endif //_AUTH_IDENTITY_DEFINED

#ifdef UNICODE

#define RPC_SECURITY_QOS_V2 RPC_SECURITY_QOS_V2_W
#define PRPC_SECURITY_QOS_V2 PRPC_SECURITY_QOS_V2_W
#define _RPC_SECURITY_QOS_V2 _RPC_SECURITY_QOS_V2_W

#define RPC_HTTP_TRANSPORT_CREDENTIALS RPC_HTTP_TRANSPORT_CREDENTIALS_W
#define PRPC_HTTP_TRANSPORT_CREDENTIALS PRPC_HTTP_TRANSPORT_CREDENTIALS_W
#define _RPC_HTTP_TRANSPORT_CREDENTIALS _RPC_HTTP_TRANSPORT_CREDENTIALS_W

#define RPC_SECURITY_QOS_V3 RPC_SECURITY_QOS_V3_W
#define PRPC_SECURITY_QOS_V3 PRPC_SECURITY_QOS_V3_W
#define _RPC_SECURITY_QOS_V3 _RPC_SECURITY_QOS_V3_W

#define RPC_SECURITY_QOS_V4 RPC_SECURITY_QOS_V4_W
#define PRPC_SECURITY_QOS_V4 PRPC_SECURITY_QOS_V4_W
#define _RPC_SECURITY_QOS_V4 _RPC_SECURITY_QOS_V4_W

#else // UNICODE

#define RPC_SECURITY_QOS_V2 RPC_SECURITY_QOS_V2_A
#define PRPC_SECURITY_QOS_V2 PRPC_SECURITY_QOS_V2_A
#define _RPC_SECURITY_QOS_V2 _RPC_SECURITY_QOS_V2_A

#define RPC_HTTP_TRANSPORT_CREDENTIALS RPC_HTTP_TRANSPORT_CREDENTIALS_A
#define PRPC_HTTP_TRANSPORT_CREDENTIALS PRPC_HTTP_TRANSPORT_CREDENTIALS_A
#define _RPC_HTTP_TRANSPORT_CREDENTIALS _RPC_HTTP_TRANSPORT_CREDENTIALS_A

#define RPC_SECURITY_QOS_V3 RPC_SECURITY_QOS_V3_A
#define PRPC_SECURITY_QOS_V3 PRPC_SECURITY_QOS_V3_A
#define _RPC_SECURITY_QOS_V3 _RPC_SECURITY_QOS_V3_A

#define RPC_SECURITY_QOS_V4 RPC_SECURITY_QOS_V4_A
#define PRPC_SECURITY_QOS_V4 PRPC_SECURITY_QOS_V4_A
#define _RPC_SECURITY_QOS_V4 _RPC_SECURITY_QOS_V4_A

#endif // UNICODE

#define RPC_PROTSEQ_TCP                             (0x1)
#define RPC_PROTSEQ_NMP                             (0x2)
#define RPC_PROTSEQ_LRPC                            (0x3)
#define RPC_PROTSEQ_HTTP                            (0x4)

#define RPC_BHT_OBJECT_UUID_VALID                   (0x1)

#define RPC_BHO_NONCAUSAL                           (0x1)
#define RPC_BHO_DONTLINGER                          (0x2)
#define RPC_BHO_EXCLUSIVE_AND_GUARANTEED            (0x4)

typedef struct _RPC_BINDING_HANDLE_TEMPLATE_V1_W {
    unsigned long Version;
    unsigned long Flags;
    unsigned long ProtocolSequence;
    unsigned short *NetworkAddress;
    unsigned short *StringEndpoint;
    union
    {
        unsigned short *Reserved;
    } u1;
    UUID ObjectUuid;
} RPC_BINDING_HANDLE_TEMPLATE_V1_W, *PRPC_BINDING_HANDLE_TEMPLATE_V1_W;

typedef struct _RPC_BINDING_HANDLE_TEMPLATE_V1_A {
    unsigned long Version;
    unsigned long Flags;
    unsigned long ProtocolSequence;
    unsigned char *NetworkAddress;
    unsigned char *StringEndpoint;
    union
    {
        unsigned char *Reserved;
    } u1;
    UUID ObjectUuid;
} RPC_BINDING_HANDLE_TEMPLATE_V1_A, *PRPC_BINDING_HANDLE_TEMPLATE_V1_A;

typedef struct _RPC_BINDING_HANDLE_SECURITY_V1_W {
    unsigned long Version;
    unsigned short *ServerPrincName;
    unsigned long AuthnLevel;
    unsigned long AuthnSvc;
    SEC_WINNT_AUTH_IDENTITY_W *AuthIdentity;
    RPC_SECURITY_QOS *SecurityQos;
} RPC_BINDING_HANDLE_SECURITY_V1_W, *PRPC_BINDING_HANDLE_SECURITY_V1_W;

#ifdef _AUTH_IDENTITY_A_DEFINED

typedef struct _RPC_BINDING_HANDLE_SECURITY_V1_A {
    unsigned long Version;
    unsigned char *ServerPrincName;
    unsigned long AuthnLevel;
    unsigned long AuthnSvc;
    SEC_WINNT_AUTH_IDENTITY_A *AuthIdentity;
    RPC_SECURITY_QOS *SecurityQos;
} RPC_BINDING_HANDLE_SECURITY_V1_A, *PRPC_BINDING_HANDLE_SECURITY_V1_A;

#endif // _AUTH_IDENTITY_A_DEFINED

typedef struct _RPC_BINDING_HANDLE_OPTIONS_V1 {
    unsigned long Version;
    unsigned long Flags;
    unsigned long ComTimeout;
    unsigned long CallTimeout;
} RPC_BINDING_HANDLE_OPTIONS_V1, *PRPC_BINDING_HANDLE_OPTIONS_V1;

#ifdef UNICODE

#define RPC_BINDING_HANDLE_TEMPLATE_V1 RPC_BINDING_HANDLE_TEMPLATE_V1_W
#define PRPC_BINDING_HANDLE_TEMPLATE_V1 PRPC_BINDING_HANDLE_TEMPLATE_V1_W
#define _RPC_BINDING_HANDLE_TEMPLATE_V1 _RPC_BINDING_HANDLE_TEMPLATE_V1_W

#define RPC_BINDING_HANDLE_SECURITY_V1 RPC_BINDING_HANDLE_SECURITY_V1_W
#define PRPC_BINDING_HANDLE_SECURITY_V1 PRPC_BINDING_HANDLE_SECURITY_V1_W
#define _RPC_BINDING_HANDLE_SECURITY_V1 _RPC_BINDING_HANDLE_SECURITY_V1_W

#else

#define RPC_BINDING_HANDLE_TEMPLATE_V1 RPC_BINDING_HANDLE_TEMPLATE_V1_A
#define PRPC_BINDING_HANDLE_TEMPLATE_V1 PRPC_BINDING_HANDLE_TEMPLATE_V1_A
#define _RPC_BINDING_HANDLE_TEMPLATE_V1 _RPC_BINDING_HANDLE_TEMPLATE_V1_A

#define RPC_BINDING_HANDLE_SECURITY_V1 RPC_BINDING_HANDLE_SECURITY_V1_A
#define PRPC_BINDING_HANDLE_SECURITY_V1 PRPC_BINDING_HANDLE_SECURITY_V1_A
#define _RPC_BINDING_HANDLE_SECURITY_V1 _RPC_BINDING_HANDLE_SECURITY_V1_A

#endif // !UNICODE

#ifdef _AUTH_IDENTITY_A_DEFINED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingCreateA (
    IN RPC_BINDING_HANDLE_TEMPLATE_V1_A *Template,
    IN RPC_BINDING_HANDLE_SECURITY_V1_A *Security OPTIONAL,
    IN RPC_BINDING_HANDLE_OPTIONS_V1 *Options OPTIONAL,
    OUT RPC_BINDING_HANDLE *Binding
    );

#endif // _AUTH_IDENTITY_A_DEFINED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingCreateW (
    IN RPC_BINDING_HANDLE_TEMPLATE_V1_W *Template,
    IN RPC_BINDING_HANDLE_SECURITY_V1_W *Security OPTIONAL,
    IN RPC_BINDING_HANDLE_OPTIONS_V1 *Options OPTIONAL,
    OUT RPC_BINDING_HANDLE *Binding
    );

#ifdef UNICODE
#define RpcBindingCreate RpcBindingCreateW
#else /* UNICODE */
#define RpcBindingCreate RpcBindingCreateA
#endif /* UNICODE */

RPCRTAPI
RPC_STATUS 
RPC_ENTRY 
RpcBindingGetTrainingContextHandle (
    IN RPC_BINDING_HANDLE Binding,
    OUT void **ContextHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY 
RpcServerInqBindingHandle (
    OUT RPC_BINDING_HANDLE *Binding
    );

typedef RPC_STATUS
(__RPC_USER * RPC_NEW_HTTP_PROXY_CHANNEL) (
    IN unsigned short __RPC_FAR *ServerName,
    IN unsigned short __RPC_FAR *ServerPort,
    IN unsigned char __RPC_FAR *RemoteUser,
    OUT unsigned short __RPC_FAR **NewServerName
    );

typedef void
(__RPC_USER * RPC_HTTP_PROXY_FREE_STRING) (
    IN unsigned short __RPC_FAR *ServerName
    );

#define RPC_C_AUTHZ_NONE    0
#define RPC_C_AUTHZ_NAME    1
#define RPC_C_AUTHZ_DCE     2
#define RPC_C_AUTHZ_DEFAULT 0xffffffff

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcImpersonateClient (
    IN OPTIONAL RPC_BINDING_HANDLE BindingHandle
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcRevertToSelfEx (
    IN OPTIONAL RPC_BINDING_HANDLE BindingHandle
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcRevertToSelf (
    );

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthClientA (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_AUTHZ_HANDLE __RPC_FAR * Privs,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthClientW (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_AUTHZ_HANDLE __RPC_FAR * Privs,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthClientExA (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_AUTHZ_HANDLE __RPC_FAR * Privs,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc,
    IN  unsigned long             Flags
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthClientExW (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_AUTHZ_HANDLE __RPC_FAR * Privs,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc,
    IN  unsigned long             Flags
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthInfoA (
    IN RPC_BINDING_HANDLE Binding,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL RPC_AUTH_IDENTITY_HANDLE __RPC_FAR * AuthIdentity,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthInfoW (
    IN RPC_BINDING_HANDLE Binding,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL RPC_AUTH_IDENTITY_HANDLE __RPC_FAR * AuthIdentity,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetAuthInfoA (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned char __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnLevel,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_IDENTITY_HANDLE AuthIdentity,
    IN unsigned long AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetAuthInfoExA (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned char __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnLevel,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_IDENTITY_HANDLE AuthIdentity,
    IN unsigned long AuthzSvc,
    IN OPTIONAL RPC_SECURITY_QOS *SecurityQos
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetAuthInfoW (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned short __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnLevel,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_IDENTITY_HANDLE AuthIdentity,
    IN unsigned long AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetAuthInfoExW (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned short __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnLevel,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_IDENTITY_HANDLE AuthIdentity,
    IN OPTIONAL unsigned long AuthzSvc,
    IN RPC_SECURITY_QOS *SecurityQOS
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthInfoExA (
    IN RPC_BINDING_HANDLE Binding,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL RPC_AUTH_IDENTITY_HANDLE __RPC_FAR * AuthIdentity,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc,
    IN  unsigned long RpcQosVersion,
    OUT RPC_SECURITY_QOS *SecurityQOS
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthInfoExW (
    IN RPC_BINDING_HANDLE Binding,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL RPC_AUTH_IDENTITY_HANDLE __RPC_FAR * AuthIdentity,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc,
    IN  unsigned long RpcQosVersion,
    OUT RPC_SECURITY_QOS *SecurityQOS
    );

typedef void
(__RPC_USER * RPC_AUTH_KEY_RETRIEVAL_FN) (
    IN void __RPC_FAR * Arg,
    IN unsigned short __RPC_FAR * ServerPrincName,
    IN unsigned long KeyVer,
    OUT void __RPC_FAR * __RPC_FAR * Key,
    OUT RPC_STATUS __RPC_FAR * Status
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY 
RpcServerCompleteSecurityCallback(
    IN RPC_BINDING_HANDLE BindingHandle,
    IN RPC_STATUS Status
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerRegisterAuthInfoA (
    IN unsigned char __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_KEY_RETRIEVAL_FN GetKeyFn,
    IN OPTIONAL void __RPC_FAR * Arg
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerRegisterAuthInfoW (
    IN unsigned short __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_KEY_RETRIEVAL_FN GetKeyFn,
    IN OPTIONAL void __RPC_FAR * Arg
    );

#ifdef UNICODE
#define RpcBindingInqAuthClient RpcBindingInqAuthClientW
#define RpcBindingInqAuthClientEx RpcBindingInqAuthClientExW
#define RpcBindingInqAuthInfo RpcBindingInqAuthInfoW
#define RpcBindingSetAuthInfo RpcBindingSetAuthInfoW
#define RpcServerRegisterAuthInfo RpcServerRegisterAuthInfoW
#define RpcBindingInqAuthInfoEx RpcBindingInqAuthInfoExW
#define RpcBindingSetAuthInfoEx RpcBindingSetAuthInfoExW
#else /* UNICODE */
#define RpcBindingInqAuthClient RpcBindingInqAuthClientA
#define RpcBindingInqAuthClientEx RpcBindingInqAuthClientExA
#define RpcBindingInqAuthInfo RpcBindingInqAuthInfoA
#define RpcBindingSetAuthInfo RpcBindingSetAuthInfoA
#define RpcServerRegisterAuthInfo RpcServerRegisterAuthInfoA
#define RpcBindingInqAuthInfoEx RpcBindingInqAuthInfoExA
#define RpcBindingSetAuthInfoEx RpcBindingSetAuthInfoExA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthClient (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_AUTHZ_HANDLE __RPC_FAR * Privs,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthClientEx (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_AUTHZ_HANDLE __RPC_FAR * Privs,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc,
    IN  unsigned long             Flags
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingInqAuthInfo (
    IN RPC_BINDING_HANDLE Binding,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * ServerPrincName,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnLevel,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthnSvc,
    OUT OPTIONAL RPC_AUTH_IDENTITY_HANDLE __RPC_FAR * AuthIdentity,
    OUT OPTIONAL unsigned long __RPC_FAR * AuthzSvc
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingSetAuthInfo (
    IN RPC_BINDING_HANDLE Binding,
    IN unsigned char __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnLevel,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_IDENTITY_HANDLE AuthIdentity,
    IN unsigned long AuthzSvc
    );

typedef void
(__RPC_USER * RPC_AUTH_KEY_RETRIEVAL_FN) (
    IN void __RPC_FAR * Arg,
    IN unsigned char __RPC_FAR * ServerPrincName,
    IN unsigned long KeyVer,
    OUT void __RPC_FAR * __RPC_FAR * Key,
    OUT RPC_STATUS __RPC_FAR * Status
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerRegisterAuthInfo (
    IN unsigned char __RPC_FAR * ServerPrincName,
    IN unsigned long AuthnSvc,
    IN OPTIONAL RPC_AUTH_KEY_RETRIEVAL_FN GetKeyFn,
    IN OPTIONAL void __RPC_FAR * Arg
    );

#endif /* RPC_UNICODE_SUPPORTED */

#if !defined(_M_IA64)
typedef struct {
    unsigned char __RPC_FAR * UserName;
    unsigned char __RPC_FAR * ComputerName;
    unsigned short Privilege;
    unsigned long AuthFlags;
} RPC_CLIENT_INFORMATION1, __RPC_FAR * PRPC_CLIENT_INFORMATION1;
#endif

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcBindingServerFromClient (
    IN RPC_BINDING_HANDLE ClientBinding,
    OUT RPC_BINDING_HANDLE __RPC_FAR * ServerBinding
    );

RPCRTAPI
DECLSPEC_NORETURN
void
RPC_ENTRY
RpcRaiseException (
    IN RPC_STATUS exception
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcTestCancel(
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerTestCancel (
    IN OPTIONAL RPC_BINDING_HANDLE BindingHandle
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcCancelThread(
    IN void * Thread
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcCancelThreadEx(
    IN void * Thread,
    IN long Timeout
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreate (
    OUT UUID __RPC_FAR * Uuid
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreateSequential (
    OUT UUID __RPC_FAR * Uuid
    );

#ifdef RPC_UNICODE_SUPPORTED

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidToStringA (
    IN UUID __RPC_FAR * Uuid,
    OUT unsigned char __RPC_FAR * __RPC_FAR * StringUuid
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidFromStringA (
    IN unsigned char __RPC_FAR * StringUuid,
    OUT UUID __RPC_FAR * Uuid
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidToStringW (
    IN UUID __RPC_FAR * Uuid,
    OUT unsigned short __RPC_FAR * __RPC_FAR * StringUuid
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidFromStringW (
    IN unsigned short __RPC_FAR * StringUuid,
    OUT UUID __RPC_FAR * Uuid
    );

#ifdef UNICODE
#define UuidFromString UuidFromStringW
#define UuidToString UuidToStringW
#else /* UNICODE */
#define UuidFromString UuidFromStringA
#define UuidToString UuidToStringA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidToString (
    IN UUID __RPC_FAR * Uuid,
    OUT unsigned char __RPC_FAR * __RPC_FAR * StringUuid
    );

/* client/server */
RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidFromString (
    IN unsigned char __RPC_FAR * StringUuid,
    OUT UUID __RPC_FAR * Uuid
    );

#endif /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
signed int
RPC_ENTRY
UuidCompare (
    IN UUID __RPC_FAR * Uuid1,
    IN UUID __RPC_FAR * Uuid2,
    OUT RPC_STATUS __RPC_FAR * Status
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
UuidCreateNil (
    OUT UUID __RPC_FAR * NilUuid
    );

RPCRTAPI
int
RPC_ENTRY
UuidEqual (
    IN UUID __RPC_FAR * Uuid1,
    IN UUID __RPC_FAR * Uuid2,
    OUT RPC_STATUS __RPC_FAR * Status
    );

RPCRTAPI
unsigned short
RPC_ENTRY
UuidHash (
    IN UUID __RPC_FAR * Uuid,
    OUT RPC_STATUS __RPC_FAR * Status
    );

RPCRTAPI
int
RPC_ENTRY
UuidIsNil (
    IN UUID __RPC_FAR * Uuid,
    OUT RPC_STATUS __RPC_FAR * Status
    );

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpRegisterNoReplaceA (
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN OPTIONAL UUID_VECTOR * UuidVector,
    IN unsigned char * Annotation
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpRegisterNoReplaceW (
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN OPTIONAL UUID_VECTOR * UuidVector,
    IN unsigned short  * Annotation
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpRegisterA (
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN OPTIONAL UUID_VECTOR * UuidVector,
    IN unsigned char * Annotation
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpRegisterW (
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN OPTIONAL UUID_VECTOR * UuidVector,
    IN unsigned short * Annotation
    );

#ifdef UNICODE
#define RpcEpRegisterNoReplace RpcEpRegisterNoReplaceW
#define RpcEpRegister RpcEpRegisterW
#else /* UNICODE */
#define RpcEpRegisterNoReplace RpcEpRegisterNoReplaceA
#define RpcEpRegister RpcEpRegisterA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpRegisterNoReplace (
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN OPTIONAL UUID_VECTOR * UuidVector,
    IN unsigned  char * Annotation
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpRegister (
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN OPTIONAL UUID_VECTOR * UuidVector,
    IN unsigned char * Annotation
    );

#endif /* RPC_UNICODE_SUPPORTED */


RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcEpUnregister(
    IN RPC_IF_HANDLE IfSpec,
    IN RPC_BINDING_VECTOR * BindingVector,
    IN UUID_VECTOR * UuidVector
    );

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
DceErrorInqTextA (
    IN RPC_STATUS RpcStatus,
    OUT unsigned char __RPC_FAR * ErrorText
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
DceErrorInqTextW (
    IN RPC_STATUS RpcStatus,
    OUT unsigned short __RPC_FAR * ErrorText
    );

#ifdef UNICODE
#define DceErrorInqText DceErrorInqTextW
#else /* UNICODE */
#define DceErrorInqText DceErrorInqTextA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
DceErrorInqText (
    IN RPC_STATUS RpcStatus,
    OUT unsigned char __RPC_FAR * ErrorText
    );

#endif /* RPC_UNICODE_SUPPORTED */

#define DCE_C_ERROR_STRING_LEN 256

typedef I_RPC_HANDLE * RPC_EP_INQ_HANDLE;

#define  RPC_C_EP_ALL_ELTS        0
#define  RPC_C_EP_MATCH_BY_IF     1
#define  RPC_C_EP_MATCH_BY_OBJ    2
#define  RPC_C_EP_MATCH_BY_BOTH   3

#define  RPC_C_VERS_ALL           1
#define  RPC_C_VERS_COMPATIBLE    2
#define  RPC_C_VERS_EXACT         3
#define  RPC_C_VERS_MAJOR_ONLY    4
#define  RPC_C_VERS_UPTO          5

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEpEltInqBegin (
    IN OPTIONAL RPC_BINDING_HANDLE EpBinding,
    IN unsigned long InquiryType,
    IN OPTIONAL RPC_IF_ID __RPC_FAR * IfId,
    IN OPTIONAL unsigned long VersOption,
    IN OPTIONAL UUID __RPC_FAR * ObjectUuid,
    OUT RPC_EP_INQ_HANDLE __RPC_FAR * InquiryContext
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEpEltInqDone (
    IN OUT RPC_EP_INQ_HANDLE __RPC_FAR * InquiryContext
    );

#ifdef RPC_UNICODE_SUPPORTED

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEpEltInqNextA (
    IN RPC_EP_INQ_HANDLE InquiryContext,
    OUT RPC_IF_ID __RPC_FAR * IfId,
    OUT OPTIONAL RPC_BINDING_HANDLE __RPC_FAR * Binding,
    OUT OPTIONAL UUID __RPC_FAR * ObjectUuid,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * Annotation
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEpEltInqNextW (
    IN RPC_EP_INQ_HANDLE InquiryContext,
    OUT RPC_IF_ID __RPC_FAR * IfId,
    OUT OPTIONAL RPC_BINDING_HANDLE __RPC_FAR * Binding,
    OUT OPTIONAL UUID __RPC_FAR * ObjectUuid,
    OUT OPTIONAL unsigned short __RPC_FAR * __RPC_FAR * Annotation
    );

#ifdef UNICODE
#define RpcMgmtEpEltInqNext RpcMgmtEpEltInqNextW
#else /* UNICODE */
#define RpcMgmtEpEltInqNext RpcMgmtEpEltInqNextA
#endif /* UNICODE */

#else /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEpEltInqNext (
    IN RPC_EP_INQ_HANDLE InquiryContext,
    OUT RPC_IF_ID __RPC_FAR * IfId,
    OUT OPTIONAL RPC_BINDING_HANDLE __RPC_FAR * Binding,
    OUT OPTIONAL unsigned char __RPC_FAR * __RPC_FAR * Annotation
    );

#endif /* RPC_UNICODE_SUPPORTED */

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtEpUnregister (
    IN OPTIONAL RPC_BINDING_HANDLE EpBinding,
    IN RPC_IF_ID __RPC_FAR * IfId,
    IN RPC_BINDING_HANDLE Binding,
    IN OPTIONAL UUID __RPC_FAR * ObjectUuid
    );

typedef int
(__RPC_API * RPC_MGMT_AUTHORIZATION_FN) (
    IN RPC_BINDING_HANDLE ClientBinding,
    IN unsigned long RequestedMgmtOperation,
    OUT RPC_STATUS __RPC_FAR * Status
    );

#define RPC_C_MGMT_INQ_IF_IDS         0
#define RPC_C_MGMT_INQ_PRINC_NAME     1
#define RPC_C_MGMT_INQ_STATS          2
#define RPC_C_MGMT_IS_SERVER_LISTEN   3
#define RPC_C_MGMT_STOP_SERVER_LISTEN 4

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcMgmtSetAuthorizationFn (
    IN RPC_MGMT_AUTHORIZATION_FN AuthorizationFn
    );


#define RPC_C_PARM_MAX_PACKET_LENGTH    1
#define RPC_C_PARM_BUFFER_LENGTH        2

#define RPC_IF_AUTOLISTEN                   0x0001
#define RPC_IF_OLE                          0x0002
#define RPC_IF_ALLOW_UNKNOWN_AUTHORITY      0x0004
#define RPC_IF_ALLOW_SECURE_ONLY            0x0008
#define RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH 0x0010
#define RPC_IF_SEC_NO_CACHE                 0x0040
#define RPC_IF_SEC_CACHE_PER_PROC           0x0080
#define RPC_IF_ASYNC_CALLBACK               0x0100

#include <rpcdcep.h>

#ifdef __cplusplus
}
#endif

#endif /* __RPCDCE_H__ */
