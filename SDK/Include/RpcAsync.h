/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    rpcasync.h

Abstract:

    This module contains the RPC runtime APIs needed to use
    [async] RPC features.

--*/

#ifndef __RPCASYNC_H__
#define __RPCASYNC_H__

#if _MSC_VER > 1000
#pragma once
#endif

#if defined(__RPC_WIN64__)
#include <pshpack8.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_KRPCENV_)

#include <ntddk.h>
#include <windef.h>

#endif // _KRPCENV_

#define RPC_ASYNC_VERSION_1_0     sizeof(RPC_ASYNC_STATE)

typedef
enum _RPC_NOTIFICATION_TYPES
{
    RpcNotificationTypeNone,
    RpcNotificationTypeEvent,
#if !defined(_KRPCENV_)
    RpcNotificationTypeApc,
    RpcNotificationTypeIoc,
    RpcNotificationTypeHwnd,
#endif
    RpcNotificationTypeCallback
} RPC_NOTIFICATION_TYPES;

typedef
enum _RPC_ASYNC_EVENT {
    RpcCallComplete,
    RpcSendComplete,
    RpcReceiveComplete,
    RpcClientDisconnect
    } RPC_ASYNC_EVENT;

struct _RPC_ASYNC_STATE;

typedef void RPC_ENTRY
RPCNOTIFICATION_ROUTINE (
                  struct _RPC_ASYNC_STATE *pAsync,
                  void *Context,
                  RPC_ASYNC_EVENT Event);
typedef RPCNOTIFICATION_ROUTINE *PFN_RPCNOTIFICATION_ROUTINE;

typedef union _RPC_ASYNC_NOTIFICATION_INFO {
#if !defined(_KRPCENV_)
    //
    // Notification by APC
    //
    struct {
        PFN_RPCNOTIFICATION_ROUTINE NotificationRoutine;
        HANDLE hThread;
        } APC;

    //
    // Notification by IO completion port
    //
    struct {
        HANDLE hIOPort;
        DWORD dwNumberOfBytesTransferred;
        DWORD_PTR dwCompletionKey;
        LPOVERLAPPED lpOverlapped;
        } IOC;

    //
    // Notification by window message
    //
    struct {
        HWND hWnd;
        UINT Msg;
        } HWND;
    #endif // _KRPCENV_


    #if !defined(_KRPCENV_)
    //
    // Notification by event
    //
    HANDLE hEvent;
    #else   // _KRPCENV_
    //
    // Notification by event
    //
    PKEVENT Event;
    #endif  // _KRPCENV_

    //
    // Notification by callback function
    //
    // This option is available only to OLE
    //
    PFN_RPCNOTIFICATION_ROUTINE NotificationRoutine;
} RPC_ASYNC_NOTIFICATION_INFO, *PRPC_ASYNC_NOTIFICATION_INFO;

typedef struct _RPC_ASYNC_STATE {
    unsigned int    Size; // size of this structure
    unsigned long   Signature;
    long   Lock;
    unsigned long   Flags;
    void           *StubInfo;
    void           *UserInfo;
    void           *RuntimeInfo;
    RPC_ASYNC_EVENT Event;

    RPC_NOTIFICATION_TYPES NotificationType;
    RPC_ASYNC_NOTIFICATION_INFO u;

    LONG_PTR Reserved[4];
    } RPC_ASYNC_STATE, *PRPC_ASYNC_STATE;

// Possible values for Flags
#define RPC_C_NOTIFY_ON_SEND_COMPLETE      0x1
#define RPC_C_NOTIFY_ON_CLIENT_DISCONNECT  0x2
#define RPC_C_INFINITE_TIMEOUT             INFINITE

#define RpcAsyncGetCallHandle(pAsync) (((PRPC_ASYNC_STATE) pAsync)->RuntimeInfo)

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncInitializeHandle (
    PRPC_ASYNC_STATE pAsync,
    unsigned int     Size
    );

#if !defined(_KRPCENV_)
RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncRegisterInfo (
    PRPC_ASYNC_STATE pAsync
    ) ;
#endif

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncGetCallStatus (
    PRPC_ASYNC_STATE pAsync
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncCompleteCall (
    PRPC_ASYNC_STATE pAsync,
    void *Reply
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncAbortCall (
    PRPC_ASYNC_STATE pAsync,
    unsigned long ExceptionCode
    ) ;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncCancelCall (
    IN PRPC_ASYNC_STATE pAsync,
    IN BOOL fAbort
    ) ;

typedef enum tagExtendedErrorParamTypes
{
    eeptAnsiString = 1,
    eeptUnicodeString,
    eeptLongVal,
    eeptShortVal,
    eeptPointerVal,
    eeptNone,
    eeptBinary
} ExtendedErrorParamTypes;

#define MaxNumberOfEEInfoParams    4
#define RPC_EEINFO_VERSION         1

typedef struct tagBinaryParam
{
    void *Buffer;
    short Size;
} BinaryParam;

typedef struct tagRPC_EE_INFO_PARAM
{
    ExtendedErrorParamTypes ParameterType;
    union
        {
        LPSTR AnsiString;
        LPWSTR UnicodeString;
        long LVal;
        short SVal;
        ULONGLONG PVal;
        BinaryParam BVal;
        } u;
} RPC_EE_INFO_PARAM;

#define EEInfoPreviousRecordsMissing     1
#define EEInfoNextRecordsMissing         2
#define EEInfoUseFileTime                4

#define EEInfoGCCOM                     11
#define EEInfoGCFRS                     12

typedef struct tagRPC_EXTENDED_ERROR_INFO
{
    ULONG Version;
    LPWSTR ComputerName;
    ULONG ProcessID;
    union
        {
#if !defined(_KRPCENV_)
        SYSTEMTIME SystemTime;
        FILETIME FileTime;
#else    // _KRPCENV_
        LARGE_INTEGER KernelTime;
#endif   // _KRPCENV_
        } u;
    ULONG GeneratingComponent;
    ULONG Status;
    USHORT DetectionLocation;
    USHORT Flags;
    int NumberOfParameters;
    RPC_EE_INFO_PARAM Parameters[MaxNumberOfEEInfoParams];
} RPC_EXTENDED_ERROR_INFO;

typedef struct tagRPC_ERROR_ENUM_HANDLE
{
    ULONG Signature;
    void *CurrentPos;
    void *Head;
} RPC_ERROR_ENUM_HANDLE;

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorStartEnumeration (
    IN OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorGetNextRecord (
    IN RPC_ERROR_ENUM_HANDLE *EnumHandle, 
    IN BOOL CopyStrings, 
    OUT RPC_EXTENDED_ERROR_INFO *ErrorInfo
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorEndEnumeration (
    IN OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorResetEnumeration (
    IN OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorGetNumberOfRecords (
    IN RPC_ERROR_ENUM_HANDLE *EnumHandle, 
    OUT int *Records
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorSaveErrorInfo (
    IN RPC_ERROR_ENUM_HANDLE *EnumHandle, 
    OUT PVOID *ErrorBlob, 
    OUT size_t *BlobSize
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorLoadErrorInfo (
    IN PVOID ErrorBlob, 
    IN size_t BlobSize, 
    OUT RPC_ERROR_ENUM_HANDLE *EnumHandle
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcErrorAddRecord (
    IN RPC_EXTENDED_ERROR_INFO *ErrorInfo
    );

RPCRTAPI
void 
RPC_ENTRY
RpcErrorClearInformation (
    void
    );

#if !defined(_KRPCENV_)

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcAsyncCleanupThread (
    IN DWORD dwTimeout
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcGetAuthorizationContextForClient (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    IN BOOL ImpersonateOnReturn,
    IN PVOID Reserved1,
    IN OPTIONAL PLARGE_INTEGER pExpirationTime,
    IN LUID Reserved2,
    IN DWORD Reserved3,
    IN PVOID Reserved4,
    OUT PVOID *pAuthzClientContext
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY
RpcFreeAuthorizationContext (
    IN OUT PVOID *pAuthzClientContext
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcSsContextLockExclusive (
    IN RPC_BINDING_HANDLE ServerBindingHandle,
    IN PVOID UserContext
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcSsContextLockShared (
    IN RPC_BINDING_HANDLE ServerBindingHandle,
    IN PVOID UserContext
    );

typedef enum tagRpcLocalAddressFormat
{
    rlafInvalid = 0,
    rlafIPv4,
    rlafIPv6
} RpcLocalAddressFormat;

typedef struct _RPC_CALL_LOCAL_ADDRESS_V1
{
    unsigned int Version;
    void *Buffer;
    unsigned long BufferSize;
    RpcLocalAddressFormat AddressFormat;
} RPC_CALL_LOCAL_ADDRESS_V1, *PRPC_CALL_LOCAL_ADDRESS_V1;

#define RPC_CALL_ATTRIBUTES_VERSION                         (1)

#define RPC_QUERY_SERVER_PRINCIPAL_NAME                     (0x02)
#define RPC_QUERY_CLIENT_PRINCIPAL_NAME                     (0x04)
#define RPC_QUERY_CALL_LOCAL_ADDRESS                        (0x08)
#define RPC_QUERY_CLIENT_PID                                (0x10)
#define RPC_QUERY_IS_CLIENT_LOCAL                           (0x20)

typedef struct tagRPC_CALL_ATTRIBUTES_V1_W
{
    unsigned int Version;
    unsigned long Flags;
    unsigned long ServerPrincipalNameBufferLength;
    unsigned short *ServerPrincipalName;
    unsigned long ClientPrincipalNameBufferLength;
    unsigned short *ClientPrincipalName;
    unsigned long AuthenticationLevel;
    unsigned long AuthenticationService;
    BOOL NullSession;
} RPC_CALL_ATTRIBUTES_V1_W;

typedef struct tagRPC_CALL_ATTRIBUTES_V1_A
{
    unsigned int Version;
    unsigned long Flags;
    unsigned long ServerPrincipalNameBufferLength;
    unsigned char *ServerPrincipalName;
    unsigned long ClientPrincipalNameBufferLength;
    unsigned char *ClientPrincipalName;
    unsigned long AuthenticationLevel;
    unsigned long AuthenticationService;
    BOOL NullSession;
} RPC_CALL_ATTRIBUTES_V1_A;


typedef enum tagRpcCallStatus
{
    rcsInvalid = 0,
    rcsInProgress,
    rcsCancelled,
    rcsClientDisconnected,
    rcsQuotaExceeded
} RpcCallStatus;

typedef enum tagRpcCallType
{
    rctInvalid = 0,
    rctNormal,
    rctTraining,
    rctGuaranteed
} RpcCallType;

typedef enum tagRpcCallClientLocality
{
    rcclInvalid = 0,
    rcclLocal,
    rcclRemote,
    rcclClientUnknownLocality
} RpcCallClientLocality;


typedef struct tagRPC_CALL_ATTRIBUTES_V2_W
{
    unsigned int Version;
    unsigned long Flags;
    unsigned long ServerPrincipalNameBufferLength;
    unsigned short *ServerPrincipalName;
    unsigned long ClientPrincipalNameBufferLength;
    unsigned short *ClientPrincipalName;
    unsigned long AuthenticationLevel;
    unsigned long AuthenticationService;
    BOOL NullSession;
    BOOL KernelModeCaller;
    unsigned long ProtocolSequence;
    RpcCallClientLocality IsClientLocal;
    HANDLE ClientPID; 
    RpcCallStatus CallStatus;
    RpcCallType CallType;
    RPC_CALL_LOCAL_ADDRESS_V1 *CallLocalAddress;	// one of the CallLocalAddress flavors
    unsigned short OpNum;
    UUID InterfaceUuid;        
} RPC_CALL_ATTRIBUTES_V2_W;
    
typedef struct tagRPC_CALL_ATTRIBUTES_V2_A
{
    unsigned int Version;
    unsigned long Flags;
    unsigned long ServerPrincipalNameBufferLength;
    unsigned char *ServerPrincipalName;
    unsigned long ClientPrincipalNameBufferLength;
    unsigned char *ClientPrincipalName;
    unsigned long AuthenticationLevel;
    unsigned long AuthenticationService;
    BOOL NullSession;
    BOOL KernelModeCaller;
    unsigned long ProtocolSequence;
    unsigned long IsClientLocal;
    HANDLE ClientPID; 
    RpcCallStatus CallStatus;
    RpcCallType CallType;
    RPC_CALL_LOCAL_ADDRESS_V1 *CallLocalAddress;	// one of the CallLocalAddress flavors
    unsigned short OpNum;
    UUID InterfaceUuid;    
} RPC_CALL_ATTRIBUTES_V2_A;

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqCallAttributesW (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    IN OUT void *RpcCallAttributes
    );

RPCRTAPI
RPC_STATUS
RPC_ENTRY
RpcServerInqCallAttributesA (
    IN OPTIONAL RPC_BINDING_HANDLE ClientBinding,
    IN OUT void *RpcCallAttributes
    );

#ifdef UNICODE
#  define RPC_CALL_ATTRIBUTES_V1 RPC_CALL_ATTRIBUTES_V1_W
#  define RPC_CALL_ATTRIBUTES_V2 RPC_CALL_ATTRIBUTES_V2_W
#  define RpcServerInqCallAttributes RpcServerInqCallAttributesW
#else
#  define RPC_CALL_ATTRIBUTES_V1 RPC_CALL_ATTRIBUTES_V1_A
#  define RPC_CALL_ATTRIBUTES_V2 RPC_CALL_ATTRIBUTES_V2_A
#  define RpcServerInqCallAttributes RpcServerInqCallAttributesA
#endif // !UNICODE

typedef RPC_CALL_ATTRIBUTES_V2 RPC_CALL_ATTRIBUTES;

typedef enum _RPC_NOTIFICATIONS
{
    RpcNotificationCallStatusChange
} RPC_NOTIFICATIONS;

RPCRTAPI
RPC_STATUS 
RPC_ENTRY 
RpcServerSubscribeForNotification (
    IN RPC_BINDING_HANDLE *Binding,
    IN RPC_NOTIFICATIONS Notification,
    IN RPC_NOTIFICATION_TYPES NotificationType,
    IN RPC_ASYNC_NOTIFICATION_INFO *NotificationInfo
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY 
RpcServerUnsubscribeForNotification (
    IN RPC_BINDING_HANDLE *Binding,
    IN RPC_NOTIFICATIONS Notification,
    OUT unsigned long *NotificationsQueued
    );

#endif // _KRPCENV_
 
RPCRTAPI
RPC_STATUS 
RPC_ENTRY 
RpcBindingBind (
    IN PRPC_ASYNC_STATE pAsync,
    IN RPC_BINDING_HANDLE Binding,
    IN RPC_IF_HANDLE IfSpec
    );

RPCRTAPI
RPC_STATUS 
RPC_ENTRY 
RpcBindingUnbind (
    IN RPC_BINDING_HANDLE Binding
    );

//
// Internal APIs
//
RPC_STATUS RPC_ENTRY
I_RpcAsyncSetHandle (
    IN  PRPC_MESSAGE Message,
    IN  PRPC_ASYNC_STATE pAsync
    );

RPC_STATUS RPC_ENTRY
I_RpcAsyncAbortCall (
    IN PRPC_ASYNC_STATE pAsync,
    IN unsigned long ExceptionCode
    ) ;

int 
RPC_ENTRY
I_RpcExceptionFilter (
    unsigned long ExceptionCode
    );

#ifdef __cplusplus
}
#endif

#if defined(__RPC_WIN64__)
#include <poppack.h>
#endif

#endif /* __RPCASYNC_H__ */

