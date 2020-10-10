
#if defined(WPP_GLOBALLOGGER) && defined(WPP_AUTOLOGGER)
#error Only one of WPP)GLOBALLOGGER or WPP_AUTOLOGGER can be defined 
#endif

#ifdef WPP_STRSAFE
#include <strsafe.h>
#endif // ifndef WPP_STRSAFE

#ifndef WPP_MOF_RESOURCENAME
#define WPP_REG_TRACE_REGKEY            L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Tracing"

#define WPP_REG_TRACE_ENABLED           L"EnableTracing"

#define WPP_REG_TRACE_LOG_FILE_NAME     L"LogFileName"
#define WPP_REG_TRACE_LOG_SESSION_NAME  L"LogSessionName"
#define WPP_REG_TRACE_LOG_BUFFER_SIZE   L"BufferSize"
#define WPP_REG_TRACE_LOG_MIN_BUFFERS   L"MinBuffers"
#define WPP_REG_TRACE_LOG_MAX_BUFFERS   L"MaxBuffers"
#define WPP_REG_TRACE_LOG_MAX_FILESIZE  L"MaxFileSize"
#define WPP_REG_TRACE_LOG_MAX_HISTORY   L"MaxHistorySize"
#define WPP_REG_TRACE_LOG_MAX_BACKUPS   L"MaxBackups"

#define WPP_REG_TRACE_ACTIVE            L"Active"
#define WPP_REG_TRACE_CONTROL           L"ControlFlags"
#define WPP_REG_TRACE_LEVEL             L"Level"
#define WPP_REG_TRACE_GUID              L"Guid"
#define WPP_REG_TRACE_BITNAMES          L"BitNames"
#endif  // #ifndef WPP_MOF_RESOURCENAME

#define DEFAULT_LOGGER_NAME             L"stdout"
#define DEFAULT_GLOBAL_LOGGER_KEY       L"WMI\\GlobalLogger\\"
#define DEFAULT_LOGGER_KEY              L"WMI\\AutoLogger\\"

#if !defined(WppDebug)
#  define WppDebug(a,b)
#endif

#if !defined(WPPINIT_STATIC)
#  define WPPINIT_STATIC
#endif

#if !defined(WPPINIT_EXPORT)
#  define WPPINIT_EXPORT
#endif

#define WPP_GUID_FORMAT     "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
#define WPP_GUID_ELEMENTS(p) \
    p->Data1,                 p->Data2,    p->Data3,\
    p->Data4[0], p->Data4[1], p->Data4[2], p->Data4[3],\
    p->Data4[4], p->Data4[5], p->Data4[6], p->Data4[7]



WPPINIT_STATIC
void WppIntToHex(
    LPWSTR Buf,
    unsigned int value,
    int digits
    )
{
    static LPCWSTR hexDigit = L"0123456789abcdef";
    while (--digits >= 0) {
        Buf[digits] = hexDigit[ value & 15 ];
        value /= 16; // compiler is smart enough to change it to bitshift
    }
}

#define WPP_TEXTGUID_LEN 37

// b1e5deaf-1524-4a04-82c4-c9dfbce6cf97<NULL>
// 0         1         2         3
// 0123456789012345678901234567890123456
WPPINIT_STATIC
void WppGuidToStr(LPWSTR buf, LPCGUID guid) {
    WppIntToHex(buf + 0, guid->Data1, 8);
    buf[8]  = '-';
    WppIntToHex(buf + 9, guid->Data2, 4);
    buf[13] = '-';
    WppIntToHex(buf + 14, guid->Data3, 4);
    buf[18] = '-';
    WppIntToHex(buf + 19, guid->Data4[0], 2);
    WppIntToHex(buf + 21, guid->Data4[1], 2);
    buf[23] = '-';
    WppIntToHex(buf + 24, guid->Data4[2], 2);
    WppIntToHex(buf + 26, guid->Data4[3], 2);
    WppIntToHex(buf + 28, guid->Data4[4], 2);
    WppIntToHex(buf + 30, guid->Data4[5], 2);
    WppIntToHex(buf + 32, guid->Data4[6], 2);
    WppIntToHex(buf + 34, guid->Data4[7], 2);
    buf[36] = 0;
}

#if defined (WPP_GLOBALLOGGER) || defined(WPP_AUTOLOGGER)

#ifndef MAX_LOGGER_NAME_SIZE
#define MAX_LOGGER_NAME_SIZE 32
#endif

#define GREGVALUENAMELENGTH 60 + WPP_TEXTGUID_LEN + MAX_LOGGER_NAME_SIZE + 1 // wslen(L"SYSTEM\\CurrentControlSet\\Control\\WMI\\GlobalLogger\\") + GUIDLENGTH

WPPINIT_EXPORT
void WppInitGlobalLogger(
        PWCHAR LoggerName,
        LPCGUID pControlGuid,
        PTRACEHANDLE pLogger,
        PULONG pFlags,
        PUCHAR pLevel )
{
WCHAR    GRegValueName[GREGVALUENAMELENGTH] ; // L"WMI\\GlobalLogger\\d58c126f-b309-11d1-969e-0000f875a5bc" ;
ULONG    Lflags = 0,
         Llevel = 0;
DWORD    Lstart = 0,
         Lsize ;
ULONG    status ;
HKEY     hKeyG, hKeyV ;
#ifdef WPP_STRSAFE
HRESULT  hr ;
#endif

#ifndef WPP_STRSAFE
#ifndef WPP_AUTOLOGGER
   _snwprintf(GRegValueName,GREGVALUENAMELENGTH,L"SYSTEM\\CurrentControlSet\\Control\\Wmi\\%ws",LoggerName);
   GRegValueName[GREGVALUENAMELENGTH-1] = L'\0' ;
#else
   _snwprintf(GRegValueName,GREGVALUENAMELENGTH,L"SYSTEM\\CurrentControlSet\\Control\\Wmi\\AutoLogger\\%ws",LoggerName);
   GRegValueName[GREGVALUENAMELENGTH-1] = L'\0' ;
#endif
#else
#ifndef WPP_AUTOLOGGER
   hr = StringCbPrintfW(GRegValueName,GREGVALUENAMELENGTH*sizeof(WCHAR),L"SYSTEM\\CurrentControlSet\\Control\\Wmi\\%ws",LoggerName);
#else
   hr = StringCbPrintfW(GRegValueName,GREGVALUENAMELENGTH*sizeof(WCHAR),L"SYSTEM\\CurrentControlSet\\Control\\Wmi\\AutoLogger\\%ws",LoggerName);
#endif
   if FAILED(hr) {
       WppDebug(0,("WPP Failed to make Key name for %S(%S) ",LoggerName, GRegValueName));
       return ;
   }
#endif //#ifndef WPP_STRSAFE

   WppDebug(0,("WPP checking Global Logger %S",GRegValueName));

   if ((status = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                        (LPWSTR)GRegValueName,
                        0,
                        KEY_READ,
                        &hKeyG
                        )) != ERROR_SUCCESS) {
       WppDebug(0,("Global/Auto Logger key %ws does not exist (0x%08X)",LoggerName,status));
       return ;
   }
   
   Lsize = sizeof(DWORD);
   status = RegQueryValueExW(hKeyG,
                             (LPWSTR)L"Start",
                             0,
                             NULL,
                             (LPBYTE)&Lstart,
                             &Lsize);
    if (status != ERROR_SUCCESS || Lstart == 0 ) {
        WppDebug(0,("Global Logger not started (0x%08X)",status));
        status = RegCloseKey(hKeyG);  
        return ;
    }
    
   WppDebug(0,("Global Logger exists and is set to be started"));

   WppGuidToStr(GRegValueName, pControlGuid) ;       

   //
   // Perform the query
   //
   
   if ((status = RegOpenKeyExW(hKeyG,
                        (LPWSTR)GRegValueName,
                        0,
                        KEY_READ,
                        &hKeyV
                        )) != ERROR_SUCCESS) {
       WppDebug(0,("Global Logger Key not set for this Control Guid %S (0x%08X)",GRegValueName,status));
       status = RegCloseKey(hKeyG);
       return ;
   }
   // Get the Flags Parameter
   Lsize = sizeof(DWORD);
   status = RegQueryValueExW(hKeyV,
                             (LPWSTR)L"Flags",
                             0,
                             NULL,
                             (LPBYTE)&Lflags,
                             &Lsize);
    if (status != ERROR_SUCCESS || Lflags == 0 ) {
        WppDebug(0,("Global/Auto Logger for %S Flags not set (0x%08X)",GRegValueName,status));
    }
   // Get the levels Parameter
   Lsize = sizeof(DWORD);
   status = RegQueryValueExW(hKeyV,
                             (LPWSTR)L"Level",
                             0,
                             NULL,
                             (LPBYTE)&Llevel,
                             &Lsize);
    if (status != ERROR_SUCCESS || Llevel == 0 ) {
        WppDebug(0,("Global/Auto Logger for %S Level not set (0x%08X)",GRegValueName,status));
    }
   
    if (Lstart==1) {
       if ((*pLogger= WppQueryLogger(LoggerName)) != (TRACEHANDLE)NULL) {
           *pFlags = Lflags & 0x7FFFFFFF ;
           *pLevel = (UCHAR)(Llevel & 0xFF) ;
           WppDebug(0,("WPP Enabled via Global Logger Flags=0x%08X Level=0x%02X",Lflags,Llevel));
       } else {
           WppDebug(0,("Global/Auto Logger set for start but not running (Flags=0x%08X Level=0x%02X)",Lflags,Llevel));
       }
    }
   status = RegCloseKey(hKeyG);
   status = RegCloseKey(hKeyV);                                   
}
#endif  //#ifdef WPP_GLOBALLOGGER


#ifndef WPP_MOF_RESOURCENAME
WPPINIT_STATIC
ULONG
WppPublishTraceInfo(
    PWPP_REGISTRATION_BLOCK Head,
    LPCWSTR ProductName)
{
    DWORD status;
    DWORD disposition= REG_OPENED_EXISTING_KEY;
    HKEY  TracingKey = 0;
    HKEY  ProductKey = 0;
    DWORD dwValue;
    const DWORD dwSizeLoggerName=sizeof(DEFAULT_LOGGER_NAME);

    //
    //  Enforce security on Trace Registry Key
    //      only system, admin usera are allowed to full access
    //      LocalService and NetworkService R/W access
    //      normal and power users are NOT allowed to R the key
    //
    SECURITY_ATTRIBUTES     seAttrib = {0};
    PSECURITY_DESCRIPTOR    pSD      = NULL;

#ifndef WPP_TRACE_W2K_COMPATABILITY 
#ifndef WPP_DLL
    TCHAR                   szSD[]   = TEXT("D:")                   // DACL
                                       TEXT("(A;OICI;GA;;;SY)")     // System Full Access
                                       TEXT("(A;OICI;GRGW;;;LS)")   // Local service R/W Access
                                       TEXT("(A;OICI;GRGW;;;NS)")   // Network service R/W Access
                                       TEXT("(A;OICI;GA;;;BA)");    // Built-in Adminstrator Full Access
#endif
#endif

    seAttrib.nLength        = sizeof(SECURITY_ATTRIBUTES);
    seAttrib.bInheritHandle = FALSE;

#ifndef WPP_TRACE_W2K_COMPATABILITY 
#ifndef WPP_DLL
    if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
                                szSD,
                                SDDL_REVISION_1,
                                &pSD,
                                NULL )) {
        status = GetLastError();
        WppDebug(1,("[WppInit] Failed to create security descriptor, %d", status) );
        goto exit_gracefully;    
    }
#endif
#endif

    seAttrib.lpSecurityDescriptor = pSD;
    
    status = RegCreateKeyExW(HKEY_LOCAL_MACHINE, 
                            WPP_REG_TRACE_REGKEY, 
                            0, 
                            NULL, // Class
                            REG_OPTION_NON_VOLATILE,
                            KEY_WRITE,
                            &seAttrib, // Sec Attributes
                            &TracingKey,
                            &disposition
                            );
    if (status != ERROR_SUCCESS) {
        WppDebug(1,("[WppInit] Failed to create Trace Key, %d", status) );
        goto exit_gracefully;
    }

    status = RegCreateKeyExW(TracingKey, 
                            ProductName, 
                            0, 
                            NULL, // Class
                            REG_OPTION_NON_VOLATILE,
                            KEY_WRITE, 
                            NULL, // Sec Attributes
                            &ProductKey,
                            &disposition
                            );
    if (status != ERROR_SUCCESS) {
        WppDebug(1,("[WppInit] Failed to create Product Key, %d", status) );
        goto exit_gracefully;
    }

    status = RegSetValueExW(ProductKey,
                  WPP_REG_TRACE_LOG_SESSION_NAME,
                  0, // Reserved
                  REG_EXPAND_SZ,
                  (const BYTE*)DEFAULT_LOGGER_NAME,
	          dwSizeLoggerName
            );

    if (status != ERROR_SUCCESS) {
        WppDebug(1,("[WppInit] Failed to create LogSession value, %d", status) );
        goto exit_gracefully;
    }
    

    dwValue = 1;
    status = RegSetValueExW(ProductKey,
                  WPP_REG_TRACE_ACTIVE,
                  0, // Reserved
                  REG_DWORD,
                  (const BYTE*)&dwValue,
                  sizeof(dwValue) );
    if (status != ERROR_SUCCESS) {
        WppDebug(1, ("[WppInit] Failed to create Active value, %d", status) );
        goto exit_gracefully;
    }
    dwValue = 1;
    status = RegSetValueExW(ProductKey,
                  WPP_REG_TRACE_CONTROL,
                  0, // Reserved
                  REG_DWORD,
                  (const BYTE*)&dwValue,
                  sizeof(dwValue) );
    if (status != ERROR_SUCCESS) {
        WppDebug(1,("[WppInit] Failed to create Control value, %d", status) );
        goto exit_gracefully;
    }

    for(;Head;Head = Head->Next) {
        HKEY ComponentKey=0;
        
        status = RegCreateKeyExW(ProductKey, 
                                Head->FriendlyName, 
                                0, 
                                NULL, // Class
                                REG_OPTION_NON_VOLATILE,
                                KEY_WRITE, 
                                NULL, // Sec Attributes
                                &ComponentKey,
                                &disposition
                                );
        if (status != ERROR_SUCCESS) {
            WppDebug(1,("[WppInit] Failed to create %ws Key, %d", 
                Head->FriendlyName, status) );
        } else {
            GUID guid;
            WCHAR guidBuf[WPP_TEXTGUID_LEN];
            
            guid = *Head->ControlGuid;
            WppGuidToStr(guidBuf, &guid);
                    
            status = RegSetValueExW(ComponentKey,
                          WPP_REG_TRACE_GUID,
                          0, // Reserved
                          REG_SZ,
                          (const BYTE*)guidBuf,
                          sizeof(guidBuf) );
            if (status != ERROR_SUCCESS) {
                WppDebug(1,("[WppInit] Failed to create GUID value, %d", status) );
            }
            status = RegSetValueExW(ComponentKey,
                          WPP_REG_TRACE_BITNAMES,
                          0, // Reserved
                          REG_SZ,
                          (const BYTE*)Head->BitNames,
                          (DWORD)((wcslen(Head->BitNames) + 1) * sizeof(WCHAR)) );
            if (status != ERROR_SUCCESS) {
                WppDebug(1,("[WppInit] Failed to create GUID value, %d", status) );
            }
        }
        if (ComponentKey) {
            RegCloseKey(ComponentKey);    
        }
    }
             
exit_gracefully:

    LocalFree( pSD );

    if (ProductKey) {
        RegCloseKey(ProductKey);
    }
    if (TracingKey) {
        RegCloseKey(TracingKey);
    }

    return status;
}
#endif  // #ifndef WPP_MOF_RESOURCENAME


ULONG
WINAPI
WppControlCallback(
    IN WMIDPREQUESTCODE RequestCode,
    IN PVOID Context,
    IN OUT ULONG *InOutBufferSize,
    IN OUT PVOID Buffer
    )
{
    PWPP_TRACE_CONTROL_BLOCK Ctx = (PWPP_TRACE_CONTROL_BLOCK)Context;
    TRACEHANDLE Logger;
    UCHAR Level;
    DWORD Flags;

    *InOutBufferSize = 0;

    switch (RequestCode)
    {
    case WMI_ENABLE_EVENTS:
        {
#ifdef  WPP_TRACE_W2K_COMPATABILITY
// Public routines to break down the Loggerhandle in W2k Only

typedef struct _TRACE_ENABLE_CONTEXT {
    USHORT  LoggerId;           // Actual Id of the logger
    UCHAR   Level;              // Enable level passed by control caller
    UCHAR   InternalFlag;       // Reserved
    ULONG   EnableFlags;        // Enable flags passed by control caller
} TRACE_ENABLE_CONTEXT, *PTRACE_ENABLE_CONTEXT;


        Logger = (TRACEHANDLE)((PWNODE_HEADER)Buffer)->HistoricalContext;
        Level =((PTRACE_ENABLE_CONTEXT) (&Logger))->Level ;
        Flags = ((PTRACE_ENABLE_CONTEXT) (&Logger))->EnableFlags ;
#else // #ifdef  WPP_TRACE_W2K_COMPATABILITY
            Logger = GetTraceLoggerHandle( Buffer );
            Level = GetTraceEnableLevel(Logger);
            Flags = GetTraceEnableFlags(Logger);
#endif  // #ifdef WPP_TRACE_W2K_COMPATABILITY
            WppDebug(1, ("[WppInit] WMI_ENABLE_EVENTS Ctx %p Flags %x"
                     " Lev %d Logger %I64x\n", 
                     Ctx, Flags, Level, Logger) );
            break;
        }
    case WMI_DISABLE_EVENTS:
        {
            Logger = 0;
            Flags  = 0;
            Level  = 0;
            WppDebug(1, ("[WppInit] WMI_DISABLE_EVENTS Ctx 0x%08p\n", Ctx));
            break;
        }
    default:
        {
            return(ERROR_INVALID_PARAMETER);
        }
    }
    if (Ctx->Options & WPP_VER_WIN2K_CB_FORWARD_PTR && Ctx->Win2kCb) {
        Ctx->Win2kCb->Logger = Logger;
        Ctx->Win2kCb->Level  = Level;
        Ctx->Win2kCb->Flags  = Flags;
    } else {
	if (Ctx->Options & WPP_VER_WHISTLER_CB_FORWARD_PTR && Ctx->Cb) {
            Ctx = Ctx->Cb; // use forwarding address
        }
        Ctx->Logger   = Logger;
        Ctx->Level    = Level;
        Ctx->Flags[0] = Flags;
    }
    return(ERROR_SUCCESS);
}


WPPINIT_EXPORT
VOID WppInitUm(LPCWSTR AppName, PWPP_REGISTRATION_BLOCK Registration)
{
    PWPP_REGISTRATION_BLOCK p = Registration;
#ifdef WPP_MOF_RESOURCENAME
#ifdef WPP_DLL
    HMODULE hModule = NULL ;    
#endif
    WCHAR ImagePath[MAX_PATH] = {UNICODE_NULL} ;
    WCHAR WppMofResourceName[] = WPP_MOF_RESOURCENAME ;
#endif //#ifdef WPP_MOF_RESOURCENAME

#ifndef WPP_MOF_RESOURCENAME    
    if (AppName) {
        WppPublishTraceInfo(Registration, AppName);
    }
#endif  // #ifndef WPP_MOF_RESOURCENAME

    WppDebug(1, ("Registering %ws\n", AppName) );
    for(; p; p = p->Next) {
        TRACE_GUID_REGISTRATION FakeTraceGuid;
        WPP_REGISTRATION_BLOCK RegBlock = *p;
        PWPP_TRACE_CONTROL_BLOCK cb = (PWPP_TRACE_CONTROL_BLOCK)p;
        ULONG status;

        WppDebug(1,(WPP_GUID_FORMAT " %ws : %d:%ws\n", 
                    WPP_GUID_ELEMENTS(p->ControlGuid),
                    p->FriendlyName, p->FlagsLen, p->BitNames));

        ZeroMemory(cb, sizeof(WPP_TRACE_CONTROL_BLOCK) 
                     + sizeof(ULONG) * (RegBlock.FlagsLen - 1) );
        p->Next     = RegBlock.Next;
        cb->FlagsLen = RegBlock.FlagsLen;
        cb->Options  = RegBlock.Options;
        cb->Ptr      = RegBlock.Ptr;

        // Jee, do we need this fake trace guid? //
        FakeTraceGuid.Guid = RegBlock.ControlGuid;
        FakeTraceGuid.RegHandle = 0;
#ifdef WPP_MOF_RESOURCENAME      
        if (AppName != NULL) {
           DWORD Status ;
#ifdef WPP_DLL
           if ((hModule = GetModuleHandleW(AppName)) != NULL) {
               Status = GetModuleFileNameW(hModule, ImagePath, MAX_PATH) ;
               ImagePath[MAX_PATH-1] = '\0';
               if (Status == 0) {
                  WppDebug(1,("RegisterTraceGuids => GetModuleFileName(DLL) Failed 0x%08X\n",GetLastError()));
               }
           } else {
               WppDebug(1,("RegisterTraceGuids => GetModuleHandleW failed for %ws (0x%08X)\n",AppName,GetLastError()));
           }
#else   // #ifdef WPP_DLL
           Status = GetModuleFileNameW(NULL,ImagePath,MAX_PATH);
           if (Status == 0) {
               WppDebug(1,("GetModuleFileName(EXE) Failed 0x%08X\n",GetLastError()));
           }
#endif  //  #ifdef WPP_DLL
        }
        WppDebug(1,("registerTraceGuids => registering with WMI, App=%ws, Mof=%ws, ImagePath=%ws\n",AppName,WppMofResourceName,ImagePath));

        status = RegisterTraceGuidsW(                   // Always use Unicode
#else   // ifndef WPP_MOF_RESOURCENAME

        status = RegisterTraceGuids(                    // So no change for existing users
#endif  // ifndef WPP_MOF_RESOURCENAME

            WppControlCallback,
            cb,                    // Context for the callback
            RegBlock.ControlGuid,  // Control Guid
            1, &FakeTraceGuid,     // #TraceGuids, TraceGuid
#ifndef WPP_MOF_RESOURCENAME
            0, //ImagePath,
            0, //ResourceName,
#else   // #ifndef WPP_MOF_RESOURCENAME
            ImagePath,
            WppMofResourceName,
#endif // #ifndef WPP_MOF_RESOURCENAME
            &cb->UmRegistrationHandle
        );

        WppDebug(1, ("RegisterTraceGuid => %d\n", status) );
#if defined (WPP_GLOBALLOGGER) || defined(WPP_AUTOLOGGER)
        // Check if Global logger is active if we have not been immediately activated
        // There is still a posibility of a race, but if you can be enabled normally
        // don't use the global logger.
        if (cb->Logger == (TRACEHANDLE)NULL) {          
                WppInitGlobalLogger(
#ifdef WPP_AUTOLOGGER
                                WPP_AUTOLOGGER,
#else
                                L"GlobalLogger",
#endif
                                RegBlock.ControlGuid,
                                (PTRACEHANDLE)&cb->Logger,
                                &cb->Flags[0],
                                &cb->Level);
        }
#endif  //#if defined (WPP_GLOBALLOGGER) || defined(WPP_AUTOLOGGER)

    }
}

WPPINIT_EXPORT
VOID WppCleanupUm(PWPP_REGISTRATION_BLOCK Registration)
{
    PWPP_TRACE_CONTROL_BLOCK x = (PWPP_TRACE_CONTROL_BLOCK)Registration;
    WppDebug(1, ("Cleanup\n") );
    for(; x; x = x->Next) {
        WppDebug(1,("UnRegistering %I64x\n", x->UmRegistrationHandle) );
        if (x->UmRegistrationHandle) {
            UnregisterTraceGuids(x->UmRegistrationHandle);
            x->UmRegistrationHandle = (TRACEHANDLE)NULL ;
        }
    }    
}

