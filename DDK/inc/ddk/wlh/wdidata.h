
/*++

Copyright (c) Microsoft Corporation.  All rights reserved.

Module Name:

    WdiData.h

Abstract:

    Public headers Windows Diagnostic Infrastructure(WDI) applications,
    
    DAata structures available

--*/

// begin_ntddk begin_wdm begin_ntifs begin_wmikm
#ifndef __WDIDATA__

#ifdef __cplusplus
extern "C" {
#endif

#define __WDIDATA__


#define SCENARIO_VERSION    1

// for now we will make SCENARIO Instance ID be a GUID but we will keep that fact opaque as we may
// want to change it (Size will remain the same)

typedef GUID    SCENARIOIID ;
typedef GUID *  PSCENARIOIID ;
typedef ULONG   SCENARIOVERSION ;
typedef ULONG   SCENARIOFLAGS ;
typedef ULONG   SCENARIOSTATUS ;


#define NULL_SCENARIO_IID  {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0} }
#define SCENARIOIID_IS_NULL(id) ((id.Data1==0)&&(id.Data2==0)&&(id.Data3==0)&&\
                                (id.Data4[0]==0)&&(id.Data4[1]==0)&&(id.Data4[2]==0)&&\
                                (id.Data4[3]==0)&&(id.Data4[4]==0)&&(id.Data4[5]==0)&&\
                                (id.Data4[6]==0)&&(id.Data4[7]==0))
                                

typedef ULONG_PTR   TRACEREGHANDLE, *PTRACEREGHANDLE ;

//
// Event ID? From Crimson  *** TEMP ***
typedef struct _EVENTIDD {
    UCHAR        Reserved1;    // flags and type
    UCHAR        Level;                         
    USHORT       Reserved2;    // category       
    UCHAR        Version;    // Use source instance for Our Version
    UCHAR        SubType;                                          
    USHORT      ID;                                                
} EVENTIDD, *PEVENTIDD;


typedef struct _CORRELATIONID {
    GUID        ActivityID;
    GUID        RelatedActivityID;
} CORRELATIONID, *PCORRELATIONID;

typedef ULONG       SUBCOMPONENT ;


//
// The TRACE_CONTEXT_EVENT structure is the structure the user sees, its mostly opaque
//
typedef struct _TRACE_CONTEXT_EVENT {
    PVOID   Header ;
    PVOID   UserData ;
} TRACE_CONTEXT_EVENT, *PTRACE_CONTEXT_EVENT ;

//
// The TRACE_CONTEXT structure defines the contexts the user wishes
// this is passed in on the allocation call
//
typedef struct TRACE_CONTEXT {
    USHORT		ContextFlags	;	// Flags defined per context
    USHORT  	Type ;			    // Type of this context
    PVOID       ContextPointer;	    // Pointer to an object associated with this context.
}	TRACE_CONTEXT, *PTRACE_CONTEXT;

#ifdef __cplusplus
}       // extern "C"
#endif


#endif  // #ifndef __WDIDATA__

// end_ntddk end_wdm end_wmikm end_ntifs



