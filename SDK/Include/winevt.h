/*++

Copyright (c) 2001-2002, Microsoft Corporation

Module Name:

    winevt.h

Abstract:

    Windows Events API 

--*/


#ifndef __WINEVT_H__
#define __WINEVT_H__

#ifdef __cplusplus
extern "C"
{
#endif


typedef enum _EVT_VARIANT_TYPE
{
    EvtVarTypeNull =           0,
    EvtVarTypeBoolean =        1,
    EvtVarTypeSByte =          2,
    EvtVarTypeInt16 =          3,
    EvtVarTypeInt32 =          4,
    EvtVarTypeInt64 =          5,
    EvtVarTypeByte =           6,
    EvtVarTypeUInt16 =         7,
    EvtVarTypeUInt32 =         8,
    EvtVarTypeUInt64 =         9,
    EvtVarTypeSingle =        10,
    EvtVarTypeDouble =        11,
    EvtVarTypeDateTime =      12,
    EvtVarTypeGuid =          13,
    EvtVarTypeString =        14,
    EvtVarTypeBinary =        15,

    EvtVarTypeXmlText =       32,     // not supported
    EvtVarTypeXmlNode =       33,     // not supported
    EvtVarTypeInsertStrings = 34,     // for internal use only

} EVT_VARIANT_TYPE;

#define EVT_VARIANT_TYPE_MASK 0x7f
#define EVT_VARIANT_TYPE_ARRAY 128

typedef struct _EVT_VARIANT
{
    union {

        BOOL              BooleanVal;
        INT8              SByteVal;
        INT16             Int16Val;
        INT32             Int32Val;
        INT64             Int64Val;
	UINT8             ByteVal;
	UINT16            UInt16Val;
	UINT32            UInt32Val;
	UINT64            UInt64Val;
	float		  SingleVal;
	double		  DoubleVal;
	ULONGLONG	  DateTimeVal;
        GUID*		  GuidVal;
	LPCWSTR		  StringVal;
        PBYTE             BinaryVal;    
        
        BOOL*             BooleanArr;
        INT8*             SByteArr;
        INT16*            Int16Arr;
        INT32*            Int32Arr;
        INT64*            Int64Arr;
	UINT8*            ByteArr;
	UINT16*           UInt16Arr;
	UINT32*           UInt32Arr;
	UINT64*           UInt64Arr;
	float*		  SingleArr;
	double*		  DoubleArr;
	ULONGLONG*	  DateTimeArr;
        GUID*		  GuidArr;
        LPWSTR*		  StringArr;
    };

    DWORD Count;   // number of elements not length in bytes.  Used for arrays
                   // and binary/string types. 
    DWORD Type;

} EVT_VARIANT;


/////////////////////////////////////////////////////////////////////////////
//
//  macros / constants

/////////////////////////////////////////////////////////////////////////////
//
// enumerations

typedef enum _EVT_PUBLISHER_FLAGS 
{
    EvtPublisherManifest = 0x0,
    EvtPublisherNoManifest = 0x1,
    EvtPublisherPossibleManifest = 0x2,
    EvtPublisherLegacy = 0x4,
    EvtPublisherReserved = 0x8, // internal use only
    EvtPublisherNoSystemProperties = 0x10

} EVT_PUBLISHER_FLAGS;

typedef enum _EVT_SUBSCRIBER_FLAGS 
{
    EvtSubscriberCopyAsynEvent = 0x1
} EVT_SUBSCRIBER_FLAGS;

typedef enum _EVT_REPORT_STATUS_FLAGS
{
    EvtReportStatusFiltered = 1
};
 
typedef enum _EVT_OBJECT_INFORMATION_CLASS 
{ 
    EvtLogInfo = 0,
    
} EVT_OBJECT_INFORMATION_CLASS;
   
typedef enum _EVT_LOGIN_CLASS  
{
    EvtDefaultLogin = 0,
    EvtStandardLogin, 
    EvtRpcLogin
 
} EVT_LOGIN_CLASS; 

typedef enum _EVT_SUBSCRIBER_NOTIFY_ACTION
{
    EvtSubscriberActionDeliver = 0x1 

} EVT_SUBSCRIBER_NOTIFY_ACTION;

typedef enum _EVT_PUBLISHER_NOTIFY_ACTION
{	
    EvtPublisherActionSubscribe = 0x1, 
    EvtPublisherActionCancel = 0x2,
    EvtPublisherActionCancelAll = 0x3,
    EvtPublisherActionInfo = 0x4

} EVT_PUBLISHER_NOTIFY_ACTION;

typedef enum _EVT_QUERY_FLAGS 
{
    EvtQueryForwardDirection = 0x0,
    EvtQueryReverseDirection = 0x1,
    EvtQueryRandomAccess = 0x2,
    EvtQuerySequentialAccess = 0x4

} EVT_QUERY_FLAGS;

typedef enum _EVT_REPORT_FLAGS 
{
    EvtReportNormal = 0x0,
    EvtReportTest = 0x1

} EVT_REPORT_FLAGS;

typedef enum _EVT_COMPILE_TEMPLATE_FLAGS
{
    EvtTemplateLangV1 = 0x0
    
} EVT_COMPILE_TEMPLATE_FLAGS;

/////////////////////////////////////////////////////////////////////////////
//
// typedefs

typedef HANDLE EVT_HANDLE;

typedef DWORD (WINAPI *EVT_SUBSCRIBER_CALLBACK)(
    EVT_SUBSCRIBER_NOTIFY_ACTION Action,
    PVOID Context,
    EVT_HANDLE Event
    );

typedef DWORD (WINAPI *EVT_PUBLISHER_CALLBACK)(
    EVT_PUBLISHER_NOTIFY_ACTION Action,
    DWORD64 SubscriptionId,
    LPCWSTR SubscriptionQuery,
    PVOID Reserved,
    PVOID CallbackContext );

/////////////////////////////////////////////////////////////////////////////
//
// structure definitions

typedef struct _EVT_REPORT_STATUS
{
    DWORD     Reserved;
    DWORD     BootID;
    ULONGLONG TickCount;   
    GUID      TaskID;
    DWORD     SequenceNumber;
    DWORD     Flags;   // currently 1 = Filtered.

} EVT_REPORT_STATUS;

typedef struct _EVT_STANDARD_LOGIN
{
    DWORD Flags;
    DWORD Timeout;
    LPWSTR Server;

} EVT_STANDARD_LOGIN;

typedef struct _EVT_RPC_LOGIN
{
    DWORD Flags;
    DWORD Timeout;
    LPWSTR Server;                        
    DWORD Version;
    LPWSTR User;
    LPWSTR Password;
    LPWSTR Domain;
    DWORD AuthnSvc;
    DWORD AuthzSvc;
    LPWSTR ServerPrincipalName;
    DWORD AuthnLevel;
    DWORD ImpersonationLevel;

} EVT_RPC_LOGIN;

typedef struct _EVT_LOG_INFO { 
    FILETIME CreationTime;
    FILETIME LastAccessTime;
    FILETIME LastWriteTime;
    UINT64 FileSize;
    DWORD Attributes;
    UINT64 NumberOfLogRecords;
    UINT64 OldestRecordNumber;
    DWORD Full;
} EVT_LOG_INFO;

typedef struct _EVT_SUBSCRIBER_NOTIFY
{
    DWORD FilterId;
    EVT_SUBSCRIBER_CALLBACK Callback;
    PVOID CallbackContext;

} EVT_SUBSCRIBER_NOTIFY;

typedef struct _EVT_CORRELATION_ID
{
    GUID TaskId;
    DWORD SeqNumber;
    BOOL Present;

} EVT_CORRELATION_ID;

/////////////////////////////////////////////////////////////////////////////
//
// function definitions

EVT_HANDLE WINAPI EvtOpenSession(
    IN EVT_LOGIN_CLASS LoginClass,
    IN PVOID Login,
    IN DWORD Flags
    );

BOOL WINAPI EvtClose(
    IN EVT_HANDLE Object
    );

BOOL WINAPI EvtGetExtendedStatus(
    IN LPWSTR Buffer, 
    IN DWORD Size,
    OUT PDWORD CharsWritten
    );

BOOL WINAPI EvtGetNamedObjectInformation(
    IN EVT_HANDLE Session,      
    IN LPCWSTR Name,
    IN DWORD Flags,   
    IN EVT_OBJECT_INFORMATION_CLASS ObjectInformationClass,
    IN LPVOID ObjectInformation,
    IN DWORD ObjectInformationLength,
    OUT PDWORD ReturnLength 
    ); 

EVT_HANDLE WINAPI EvtQueryLog(
    IN EVT_HANDLE Session,
    IN LPCWSTR Query,
    IN DWORD BatchSize,
    IN DWORD Flags
    );

EVT_HANDLE WINAPI EvtNext( 
    IN EVT_HANDLE ResultObject,
    IN DWORD Flags  // NO_COPY flag supported ? 
    );

EVT_HANDLE  WINAPI EvtCompileTemplate( 
    IN LPCWSTR TemplateText,
    IN DWORD Flags 
    );

EVT_HANDLE WINAPI EvtCreateMessageRenderContext( 
    IN LCID Locale,
    IN DWORD Flags
    );

EVT_HANDLE WINAPI EvtCreateValuesRenderContext( 
    IN LPCWSTR* ValuePaths, 
    IN DWORD NumValuePaths,
    IN DWORD Flags 
    );

BOOL WINAPI EvtRender(
    IN EVT_HANDLE Fragment,
    IN EVT_HANDLE RenderContext,
    IN DWORD BuffSize,
    IN PVOID Buff,
    OUT PDWORD BuffUsed
    );

BOOL WINAPI EvtClearLog(
    IN EVT_HANDLE Context,
    IN LPCWSTR EventSelector,
    IN LPCWSTR TargetFilePath,
    IN DWORD Flags
    );

BOOL WINAPI EvtExportLog(
    IN EVT_HANDLE Context,
    IN LPCWSTR EventSelector, 
    IN LPCWSTR TargetFilePath,
    IN DWORD Flags
    );

EVT_HANDLE WINAPI EvtOpenExportLog(
    IN EVT_HANDLE Session,
    IN LPCWSTR SourceFilePath,
    IN DWORD Flags
    );

EVT_HANDLE WINAPI EvtRegisterPublisher(
    IN EVT_HANDLE Session,
    IN HMODULE PublisherModule,
    IN LPCWSTR PublisherId,
    IN DWORD Flags
    );

EVT_HANDLE WINAPI EvtScopePublisher(
    IN EVT_HANDLE Publisher,
    IN LPCWSTR ChannelPath,
    IN LPCWSTR FilterExpression, 
    IN EVT_PUBLISHER_CALLBACK Callback,
    IN PVOID CallbackContext,
    IN DWORD Flags
    );

BOOL WINAPI EvtIsActive( 
    IN EVT_HANDLE Publisher, 
    IN UINT64 EventId 
    );

BOOL WINAPI EvtReport(
    IN EVT_HANDLE Publisher,
    IN UINT64 EventId,
    IN EVT_HANDLE EventTemplate,
    IN DWORD NumValues,
    IN EVT_VARIANT Values[],
    IN DWORD Flags,
    OUT EVT_REPORT_STATUS* Status
    );

BOOL WINAPI EvtReportText(
    IN EVT_HANDLE Publisher,
    IN UINT64 EventId,
    IN LPCWSTR EventXmlText,
    IN DWORD Flags,
    OUT EVT_REPORT_STATUS* Status
    );

EVT_HANDLE WINAPI EvtRegisterSubscriber(
    IN EVT_HANDLE Session,
    IN LPCWSTR Query,
    IN DWORD MaxQueueSize,
    IN PSECURITY_DESCRIPTOR Access,
    IN DWORD NumCallbacks,
    IN EVT_SUBSCRIBER_NOTIFY* Callbacks,
    IN HANDLE OverlappedEvent,
    IN DWORD Flags
    );

BOOL WINAPI EvtAssertConfig(
    IN EVT_HANDLE Context,
    IN LPCWSTR Path,
    IN DWORD flags 
    );

BOOL WINAPI EvtRetractConfig(
    IN EVT_HANDLE Context,
    IN LPCWSTR Path,
    IN DWORD Flags 
    );

BOOL WINAPI EvtSetThreadCorrelationId( 
    EVT_CORRELATION_ID* current,
    EVT_CORRELATION_ID* parent 
    );

BOOL WINAPI EvtGetThreadCorrelationId( 
    EVT_CORRELATION_ID* current,
    EVT_CORRELATION_ID* parent 
    );

typedef enum _EVT_EVENTID_FLAGS 
{
    EvtEventIdNormal = 0x0,
    EvtEventIdLegacy = 0x1

} EVT_EVENTID_FLAGS;

#define EVENTID_FLAGS( EventId ) ((UINT8)( EventId >> 62 ))
#define EVENTID_TYPE( EventId ) ((UINT8)(EventId >> 56 ) & 0x3f )
#define EVENTID_SUBTYPE( EventId ) ((UINT8)( EventId >> 48 ) )
#define EVENTID_LEVEL( EventId ) ((UINT8)( EventId >> 40 ) ) 
#define EVENTID_SOURCECODEID( EventId) ((UINT8)( EventId >> 32 ))
#define EVENTID_CATEGORY( EventId ) ((UINT16)( EventId >> 16 ))
#define EVENTID_CODE( EventId ) ((UINT32)(EVENTID_FLAGS(EventId) != (BYTE)EvtEventIdLegacy ? EventId & 0xffff : EventId & 0xffffffff ))

#ifdef __cplusplus
}
#endif

#endif // __WINEVT_H__









