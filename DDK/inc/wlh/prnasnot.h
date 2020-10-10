/*++

Copyright (c) 2001  Microsoft Corporation

Module Name:

    prnasnot.h

Abstract:

    Header file for Print APIs

Revision History:

--*/
#ifndef _PRINTASYNCNOTIFY_H_
#define _PRINTASYNCNOTIFY_H_


#include "initguid.h"
#include <objbase.h>

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif 

DEFINE_GUID(IID_IPrintAsyncNotify,               0x532818f7, 0x921b, 0x4fb2, 0xbf, 0xf8, 0x2f, 0x4f, 0xd5, 0x2e, 0xbe, 0xbf);
DEFINE_GUID(IID_IPrintAsyncNotifyChannel,        0x4a5031b1, 0x1f3f, 0x4db0, 0xa4, 0x62, 0x45, 0x30, 0xed, 0x8b, 0x04, 0x51);
DEFINE_GUID(IID_IPrintAsyncNotifyCallback,       0x7def34c1, 0x9d92, 0x4c99, 0xb3, 0xb3, 0xdb, 0x94, 0xa9, 0xd4, 0x19, 0x1b);
DEFINE_GUID(IID_IPrintAsyncNotifyRegistration,   0x0f6f27b6, 0x6f86, 0x4591, 0x92, 0x03, 0x64, 0xc3, 0xbf, 0xad, 0xed, 0xfe);
DEFINE_GUID(IID_IPrintNameRouting,               0xca670c50, 0xb5fc, 0x49fd, 0xaa, 0x9a, 0xa4, 0xd5, 0x2b, 0x41, 0x22, 0xad);
DEFINE_GUID(IID_IPrintAsyncNotifyDataObject,     0x77cf513e, 0x5d49, 0x4789, 0x9f, 0x30, 0xd0, 0x82, 0x2b, 0x33, 0x5c, 0x0d);

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
    kPerUser,
    kPerSession,
    kAllUsers,

} PrintAsyncNotifyUserFilter;

typedef enum 
{
    kBiDirectional,
    kUniDirectional

} PrintAsyncNotifyConversationStyle;

typedef GUID PrintAsyncNotificationType;

//#undef IUnknown

#undef  INTERFACE
#define INTERFACE IPrintAsyncNotifyDataObject
DECLARE_INTERFACE_(IPrintAsyncNotifyDataObject, IUnknown)
{
    STDMETHOD(QueryInterface)(
        THIS_ 
        REFIID riid, 
        void** ppvObj
        ) PURE;

    STDMETHOD_(ULONG, AddRef)(
        THIS
        ) PURE;

    STDMETHOD_(ULONG, Release)(
        THIS
        ) PURE;

    STDMETHOD(AcquireData)(
         THIS_
         OUT BYTE**,
         OUT ULONG*,
         OUT PrintAsyncNotificationType**
         ) PURE;

    STDMETHOD(ReleaseData)(
        THIS
        ) PURE;
};

typedef interface IPrintAsyncNotifyCallback IPrintAsyncNotifyCallback;

#undef  INTERFACE
#define INTERFACE IPrintAsyncNotifyChannel
DECLARE_INTERFACE_(IPrintAsyncNotifyChannel, IUnknown)
{
    STDMETHOD(QueryInterface)(
        THIS_ 
        REFIID riid, 
        void** ppvObj
        ) PURE;

    STDMETHOD_(ULONG, AddRef)(
        THIS
        ) PURE;

    STDMETHOD_(ULONG, Release)(
        THIS
        ) PURE;

    STDMETHOD(SendNotification)(            
         THIS_
         IN IPrintAsyncNotifyDataObject*
         ) PURE;

    STDMETHOD(CloseChannel)(            
         THIS_
         IN IPrintAsyncNotifyDataObject*
         ) PURE;

    /*
    STDMETHOD(GetPrintName)(            
         THIS_
         IN IPrintAsyncNotifyDataObject**
         ) PURE;

    STDMETHOD(GetChannelNotificationType)(            
         THIS_
         IN IPrintAsyncNotifyDataObject**
         ) PURE;

    STDMETHOD(GetChannelConversationType)(            
         THIS_
         IN IPrintAsyncNotifyDataObject**
         ) PURE;

    STDMETHOD(GetChannelAsyncNotifyCallbackInterface)(            
         THIS_
         IN IPrintAsyncNotifyDataObject**
         ) PURE;

    */
};
 

#undef  INTERFACE
#define INTERFACE IPrintAsyncNotifyCallback
DECLARE_INTERFACE_(IPrintAsyncNotifyCallback, IUnknown)
{
    STDMETHOD(QueryInterface)(
        THIS_ 
        REFIID riid, 
        void** ppvObj
        ) PURE;

    STDMETHOD_(ULONG, AddRef)(
        THIS
        ) PURE;

    STDMETHOD_(ULONG, Release)(
        THIS
        ) PURE;

    STDMETHOD(OnEventNotify)(            
         THIS_
         IN IPrintAsyncNotifyChannel*,
         IN IPrintAsyncNotifyDataObject*
         ) PURE;

    STDMETHOD(ChannelClosed)(            
         THIS_
         IN IPrintAsyncNotifyChannel*,
         IN IPrintAsyncNotifyDataObject*
         ) PURE;
};


#undef  INTERFACE
#define INTERFACE IPrintAsyncNotifyRegistration
DECLARE_INTERFACE_(IPrintAsyncNotifyRegistration, IUnknown)
{
    STDMETHOD(QueryInterface)(
        THIS_ 
        REFIID riid, 
        void** ppvObj
        ) PURE;

    STDMETHOD_(ULONG, AddRef)(
        THIS
        ) PURE;

    STDMETHOD_(ULONG, Release)(
        THIS
        ) PURE;

    STDMETHOD(RegisterForNotifications)(            
         THIS
         ) PURE;

    STDMETHOD(UnregisterForNotifications)(            
        THIS
        ) PURE;   
};


#undef  INTERFACE
#define INTERFACE IPrintNameRouting
DECLARE_INTERFACE_(IPrintNameRouting, IUnknown)
{
    STDMETHOD(QueryInterface)(
        THIS_ 
        REFIID riid, 
        void** ppvObj
        ) PURE;

    STDMETHOD_(ULONG, AddRef)(
        THIS
        ) PURE;

    STDMETHOD_(ULONG, Release)(
        THIS
        ) PURE;

    STDMETHOD(SetPrintRoute)(          
        THIS_
        IN  const WCHAR*) PURE;
};

#undef  INTERFACE
#define INTERFACE IPrintAsyncNotify
DECLARE_INTERFACE_(IPrintAsyncNotify, IUnknown)
{
    STDMETHOD(QueryInterface)(
        THIS_ 
        REFIID riid, 
        void** ppvObj
        ) PURE;

    STDMETHOD_(ULONG, AddRef)(
        THIS
        ) PURE;

    STDMETHOD_(ULONG, Release)(
        THIS
        ) PURE;

    STDMETHOD(CreatePrintAsyncNotifyChannel)(            
         THIS_
         IN  PrintAsyncNotificationType*,
         IN  PrintAsyncNotifyUserFilter,
         IN  PrintAsyncNotifyConversationStyle,
         IN  IPrintAsyncNotifyCallback*,
         OUT IPrintAsyncNotifyChannel** 
         ) PURE;

    STDMETHOD(CreatePrintAsyncNotifyRegistration)(            
         THIS_
         IN  PrintAsyncNotificationType*,
         IN  PrintAsyncNotifyUserFilter,
         IN  PrintAsyncNotifyConversationStyle,
         IN  IPrintAsyncNotifyCallback*,
         OUT IPrintAsyncNotifyRegistration**
         ) PURE;

};

#undef INTERFACE

HRESULT
RegisterForPrintAsyncNotifications(
    IN  LPCWSTR,          
    IN  PrintAsyncNotificationType*,      
    IN  PrintAsyncNotifyUserFilter,   
    IN  PrintAsyncNotifyConversationStyle,
    IN  IPrintAsyncNotifyCallback*,        
    OUT HANDLE*
    );

HRESULT
UnRegisterForPrintAsyncNotifications(
    IN  HANDLE
    );

HRESULT
CreatePrintAsyncNotifyChannel(
    IN  LPCWSTR,               
    IN  PrintAsyncNotificationType*,          
    IN  PrintAsyncNotifyUserFilter,         
    IN  PrintAsyncNotifyConversationStyle,      
    IN  IPrintAsyncNotifyCallback*,             
    IN  IPrintAsyncNotifyChannel**
    );

typedef enum 
{
    CHANNEL_CLOSED_BY_SERVER                    = 0x01,
    CHANNEL_CLOSED_BY_ANOTHER_LISTENER          = 0x02,
    CHANNEL_CLOSED_BY_SAME_LISTENER             = 0x03,
    CHANNEL_RELEASED_BY_LISTENER                = 0x04,
    SERVER_DIED                                 = 0x05,
    CLIENT_DIED                                 = 0x06,
    NO_LISTENERS                                = 0x07,
    CHANNEL_ALREADY_CLOSED                      = 0x08,
    CHANNEL_ALREADY_OPENED                      = 0x09,
    CHANNEL_WAITING_FOR_CLIENT_NOTIFICATION     = 0x0a,
    CHANNEL_NOT_OPENED                          = 0x0b,
    ASYNC_CALL_ALREADY_PARKED                   = 0x0c,
    NOT_REGISTERED                              = 0x0d,
    ALREADY_UNREGISTERED                        = 0x0e,
    ALREADY_REGISTERED                          = 0x0f,
    CHANNEL_ACQUIRED                            = 0x10,
    ASYNC_CALL_IN_PROGRESS                      = 0x11,
    MAX_NOTIFICATION_SIZE_EXCEEDED              = 0x12,
    INTERNAL_NOTIFICATION_QUEUE_IS_FULL         = 0x13,
    INVALID_NOTIFICATION_TYPE                   = 0x14,

} PrintAsyncNotifyError;

#ifdef __cplusplus
}
#endif
#endif //  _PRINTASYNCNOTIFY_H_






