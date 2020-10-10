/**************************************************************************

    BDA/AVStream Simulated Hardware Sample

    Copyright (c) 2001, Microsoft Corporation.

    File:

        cafilter.h

    Abstract:

    This file contains the definition of properties, events and methods
    for a custom  filter. It is important to read the notes below to understand
    the limitations of such a custom filter.

**************************************************************************/

#include "bdacap.h"

// Please read the notes below. They are very important.

// The main purpose of this filter is to illustrate the process of defining custom
// properties, methods and events. A user mode plugin can send DeviceIoControl requests
// to this filter to access the various handlers. There is no attempt to design a CA solution. 
// In particular, while it works when this custom filter is present, THE BDA NETWORK PROVIDER 
// DOES NOT CONTROL SUCH A CUSTOM FILTER.

// This is a single stream transform filter and is meant for custom use by applications only.
// It departs from the BDA model where transforms are represented by nodes. The BDA 
// Network provider does not control such a custom filter because there is no way for
// it to discover such a filter and query its nodes and types of transforms. The filter 
// is meant to be a template for custom solutions that extend outside of the usual model.

// The properties, methods and events defined in this sample are completely generic

// Begin GUID definition for properties, events and methods

// This category shows up as BDA CP/CA Filters in graphedt. This GUID alone is _not_ arbitrary.
#define STATIC_KSCATEGORY_CAFILTER \
   C4C4C4FC, 0x0049, 0x4E2B, 0x98, 0xFB, 0x95, 0x37, 0xF6, 0xCE, 0x51, 0x6D
DEFINE_GUIDSTRUCT("{C4C4C4FC-0049-4E2B-98FB-9537F6CE516D}", KSCATEGORY_CAFILTER);
#define KSCATEGORY_CAFILTER DEFINE_GUIDNAMED(KSCATEGORY_CAFILTER)

DEFINE_GUIDSTRUCT("{61C615EC-2579-46d6-AD33-558841EEC1AE}", KSNAME_BdaCAFilter);
#define KSNAME_BdaCAFilter DEFINE_GUIDNAMED(KSNAME_BdaCAFilter)

#define STATIC_KSPROPSETID_CAPROPERTIES \
    0xa3dd7f83, 0x645f, 0x43fe, 0xa4, 0xcf, 0xce, 0x4d, 0xdb, 0x3, 0xe5, 0x4a
DEFINE_GUIDSTRUCT("{A3DD7F83-645F-43fe-A4CF-CE4DDB03E54A}", KSPROPSETID_CAPROPERTIES);
#define KSPROPSETID_CAPROPERTIES DEFINE_GUIDNAMED(KSPROPSETID_CAPROPERTIES)

typedef enum {
    KSPROPERTY_CAPROPERTY_A = 0,
    KSPROPERTY_CAPROPERTY_B
} KSPROPERTY_CAPROPERTY, *PKSPROPERTY_CAPROPERTY;

#define STATIC_KSEVENTSETID_CAEVENTS \
   0x297e43cf, 0x37c5, 0x4c7c, 0x84, 0x3b, 0x7c, 0x24, 0xf, 0x85, 0xb6, 0xe4   
DEFINE_GUIDSTRUCT("{297E43CF-37C5-4c7c-843B-7C240F85B6E4}", KSEVENTSETID_CAEVENTS);
#define KSEVENTSETID_CAEVENTS DEFINE_GUIDNAMED(KSEVENTSETID_CAEVENTS)

typedef enum {
    KSEVENT_CAEVENT_A = 0,
    KSEVENT_CAEVENT_B
} KSEVENT_CAEVENT, *PKSEVENT_CAEVENT;

#define STATIC_KSMETHODSETID_CAMETHODS\
   0xbc1658ab, 0x893c, 0x4abb, 0xae, 0x31, 0xbd, 0xc, 0x20, 0x4d, 0xe8, 0x3e
DEFINE_GUIDSTRUCT("{BC1658AB-893C-4abb-AE31-BD0C204DE83E}", KSMETHODSETID_CAMETHODS);
#define KSMETHODSETID_CAMETHODS DEFINE_GUIDNAMED(KSMETHODSETID_CAMETHODS)

typedef enum {
    KSMETHOD_CAMETHOD_A = 0,
    KSMETHOD_CAMETHOD_B
} KSMETHOD_CAMETHOD, *PKSMETHOD_CAMETHOD;

// End of GUID definitions for properties events and methods.


NTSTATUS FilterCreate(IN PKSFILTER Filter, IN PIRP Irp); 
NTSTATUS FilterClose(IN PKSFILTER Filter, IN PIRP Irp);

// Filter Dispatch
const KSFILTER_DISPATCH CAFilterDispatch = 
{
    FilterCreate, // Filter Create
    FilterClose,  // Filter Close
    NULL,         // Filter Process
    NULL          // Filter Reset
};

//Property Handler (Get)
NTSTATUS CAFilterPropertyGetHandlerA
(
    IN PIRP Irp,
    IN PVOID pRequest,
    IN OUT PVOID pData
) {
    KdPrint(("Property A : Get Handler\n"));
    return STATUS_SUCCESS;
}

// Property Handler (Set)
NTSTATUS CAFilterPropertySetHandlerA
(
    IN PIRP Irp,
    IN PVOID pRequest,
    IN OUT PVOID pData
) {
    KdPrint(("Property A : Set Handler\n"));

    PKSFILTER pFilter = KsGetFilterFromIrp(Irp);
    if (!pFilter)
    {
        return STATUS_UNSUCCESSFUL;
    }

    KSEVENT_ENTRY **ppEventEntry = (KSEVENT_ENTRY **) pFilter->Context;
    ASSERT(ppEventEntry);

    // Signal event
    return KsGenerateEvent(ppEventEntry[0]);
}

// Property Handler (Get)
NTSTATUS CAFilterPropertyGetHandlerB
(
    IN PIRP Irp,
    IN PVOID pRequest,
    IN OUT PVOID pData
) {
    KdPrint(("Property B : Get Handler\n"));
    return STATUS_SUCCESS;
}

// Property Handler (Set)
NTSTATUS CAFilterPropertySetHandlerB
(
    IN PIRP Irp,
    IN PVOID pRequest,
    IN OUT PVOID pData
) {
    KdPrint(("Property B : Set Handler\n"));

    PKSFILTER pFilter = KsGetFilterFromIrp(Irp);
    if (!pFilter)
    {
        return STATUS_UNSUCCESSFUL;
    }

    KSEVENT_ENTRY **ppEventEntry = (KSEVENT_ENTRY **) pFilter->Context;
    ASSERT(ppEventEntry);

    // Signal event
    return KsGenerateEvent(ppEventEntry[1]);
}

//Method Handler
NTSTATUS CAFilterKSMethodHandlerMethodA
(
    IN PIRP Irp,
    IN PKSIDENTIFIER pRequest,
    IN OUT PVOID pData
) {
    KdPrint(("Method A : Method Handler\n"));
    return STATUS_SUCCESS;
}

// Method Handler
NTSTATUS CAFilterKSMethodHandlerMethodB
(
    IN PIRP Irp,
    IN PKSIDENTIFIER pRequest,
    IN OUT PVOID pData
) {
    KdPrint(("Method B : Method Handler\n"));
    return STATUS_SUCCESS;
}

// Event Handler
NTSTATUS CAFilterKSAddEventA
(
    IN PIRP Irp,
    IN PKSEVENTDATA EventData,
    IN struct _KSEVENT_ENTRY* EventEntry
) {
    KdPrint(("Event A : Add\n"));
    PKSFILTER pFilter = KsGetFilterFromIrp(Irp);
    if (!pFilter)
    {
        return STATUS_UNSUCCESSFUL;
    }

    KSEVENT_ENTRY **ppEventEntry = (KSEVENT_ENTRY**) pFilter->Context;
    ASSERT(ppEventEntry);
    ppEventEntry[0] = EventEntry;

    // Enable event
    return KsDefaultAddEventHandler(Irp, EventData, ppEventEntry[0]);
}

// Event Handler
NTSTATUS CAFilterKSAddEventB
(
    IN PIRP Irp,
    IN PKSEVENTDATA EventData,
    IN struct _KSEVENT_ENTRY* EventEntry
) {
    KdPrint(("Event B : Add\n"));

    PKSFILTER pFilter = KsGetFilterFromIrp(Irp);
    if (!pFilter)
    {
        return STATUS_UNSUCCESSFUL;
    }

    KSEVENT_ENTRY **ppEventEntry = (KSEVENT_ENTRY**) pFilter->Context;
    ASSERT(ppEventEntry);
    ppEventEntry[1] = EventEntry;

    // Enable event
    return KsDefaultAddEventHandler(Irp, EventData, ppEventEntry[1]);
}

// Filter Property Table
DEFINE_KSPROPERTY_TABLE(CAFilterPropertyTable)
{
    DEFINE_KSPROPERTY_ITEM
    (
        KSPROPERTY_CAPROPERTY_A,
        CAFilterPropertyGetHandlerA,
        sizeof(KSPROPERTY_CAPROPERTY),
        0,
        CAFilterPropertySetHandlerA,
        NULL,
        0,
        NULL,
        NULL,
        0
        ),
    DEFINE_KSPROPERTY_ITEM
    (
        KSPROPERTY_CAPROPERTY_B,
        CAFilterPropertyGetHandlerB,
        sizeof(KSPROPERTY_CAPROPERTY),
        0,
        CAFilterPropertySetHandlerB,
        NULL,
        0,
        NULL,
        NULL,
        0
    )
};


// Filter Property Sets
DEFINE_KSPROPERTY_SET_TABLE(CAFilterPropertySetTable)
{
    DEFINE_KSPROPERTY_SET
    (
        &KSPROPSETID_CAPROPERTIES,
        SIZEOF_ARRAY(CAFilterPropertyTable),
        CAFilterPropertyTable,
        0,
        NULL
    )
};

// Method Table for the filter
DEFINE_KSMETHOD_TABLE(CAFilterMethodTable)
{
    DEFINE_KSMETHOD_ITEM
    (
        KSMETHOD_CAMETHOD_A,
        KSMETHOD_TYPE_NONE,
        CAFilterKSMethodHandlerMethodA,
        sizeof(KSMETHOD),
        0,
        NULL
    ),
    DEFINE_KSMETHOD_ITEM
    (
        KSMETHOD_CAMETHOD_B,
        KSMETHOD_TYPE_NONE,
        CAFilterKSMethodHandlerMethodB,
        sizeof(KSMETHOD),
        0,
        NULL
    )
};

// Method set for the filter
DEFINE_KSMETHOD_SET_TABLE(CAFilterMethodSetTable)
{
    DEFINE_KSMETHOD_SET
    (
         &KSMETHODSETID_CAMETHODS,
         SIZEOF_ARRAY(CAFilterMethodTable),
         CAFilterMethodTable,
         0,
         NULL
    )
};

// Event item table for the filter
DEFINE_KSEVENT_TABLE(CAFilterEventTable)
{
    DEFINE_KSEVENT_ITEM
    (
        KSEVENT_CAEVENT_A,
        sizeof(KSEVENTDATA),
        0,
        CAFilterKSAddEventA,
        NULL,
        NULL
    ),
    DEFINE_KSEVENT_ITEM
    (
        KSEVENT_CAEVENT_B,
        sizeof(KSEVENTDATA),
        0,
        CAFilterKSAddEventB,
        NULL,
        NULL
    )
};

// Event sets supported by the filter
DEFINE_KSEVENT_SET_TABLE(CAFilterEventSetTable)
{
    DEFINE_KSEVENT_SET
    (
        &KSEVENTSETID_CAEVENTS,
        SIZEOF_ARRAY(CAFilterEventTable),
        CAFilterEventTable
    )
};

// Filter Automation Table
DEFINE_KSAUTOMATION_TABLE(CAFilterAutomation) 
{
    DEFINE_KSAUTOMATION_PROPERTIES (CAFilterPropertySetTable),
    DEFINE_KSAUTOMATION_METHODS (CAFilterMethodSetTable),
    DEFINE_KSAUTOMATION_EVENTS (CAFilterEventSetTable)
};


#define GUID_BdaSWRcv   0xf102c41f, 0x7fa1, 0x4842, 0xa0, 0xc8, 0xdc, 0x41, 0x17, 0x6e, 0xc8, 0x44
const KSPIN_MEDIUM TunerPinMedium =
{
    GUID_BdaSWRcv, 0, 0
};

// {B6CF1567-AE45-4aff-904F-46CB8062F099}
#define GUID_CAOut      0xb6cf1567, 0xae45, 0x4aff, 0x90, 0x4f, 0x46, 0xcb, 0x80, 0x62, 0xf0, 0x99
const KSPIN_MEDIUM TransportPinMedium =
{
    GUID_CAOut, 0, 0
};

// Intersect Handler
NTSTATUS
IntersectDataFormat(
    IN PVOID pContext,
    IN PIRP pIrp,
    IN PKSP_PIN Pin,
    IN PKSDATARANGE DataRange,
    IN PKSDATARANGE MatchingDataRange,
    IN ULONG DataBufferSize,
    OUT PVOID Data OPTIONAL,
    OUT PULONG DataSize
    );

// Pin Descriptors
const KSPIN_DESCRIPTOR_EX PinDescriptors[] =
{ 
    {
        NULL, 
        NULL, 
        { 
            0,
            NULL, 
            1, 
            &TunerPinMedium,
            SIZEOF_ARRAY(CaptureInPinDataRanges),
            CaptureInPinDataRanges,
            KSPIN_DATAFLOW_IN,
            KSPIN_COMMUNICATION_BOTH,
            NULL,
            NULL,
            0 
        },
        KSPIN_FLAG_DO_NOT_USE_STANDARD_TRANSPORT | 
        KSPIN_FLAG_FRAMES_NOT_REQUIRED_FOR_PROCESSING | 
        KSPIN_FLAG_FIXED_FORMAT,
        1,
        1,
        NULL,
        NULL
    },
    {
        NULL, 
        NULL, 
        { 
            0,
            NULL, 
            1, 
            &TransportPinMedium,
            SIZEOF_ARRAY(CaptureInPinDataRanges),
            CaptureInPinDataRanges,
            KSPIN_DATAFLOW_OUT,
            KSPIN_COMMUNICATION_BOTH,
            NULL,
            NULL,
            0 
        },
        KSPIN_FLAG_DO_NOT_USE_STANDARD_TRANSPORT | 
        KSPIN_FLAG_FRAMES_NOT_REQUIRED_FOR_PROCESSING | 
        KSPIN_FLAG_FIXED_FORMAT,
        1,
        1,
        NULL,
        &IntersectDataFormat
    }
};

//
// Create a connection through the CA filter so that the network
// provider can autorender
//
const
KSTOPOLOGY_CONNECTION FilterConnections[] =
{   
    { KSFILTER_NODE, 0,                 KSFILTER_NODE, 1 }
};


// Filter Descriptor
extern
DEFINE_KSFILTER_DESCRIPTOR(CAFilterDescriptor)
{
    &CAFilterDispatch,                              // Dispatch
    &CAFilterAutomation,                            // AutomationTable
    KSFILTER_DESCRIPTOR_VERSION,                    // Version
    0,                                              // Flags
    &KSNAME_BdaCAFilter,                            // ReferenceGuid
    DEFINE_KSFILTER_PIN_DESCRIPTORS(PinDescriptors),// PinDescriptorsCount
    DEFINE_KSFILTER_CATEGORY(KSCATEGORY_CAFILTER),  // CategoriesCount
    DEFINE_KSFILTER_NODE_DESCRIPTORS_NULL,          // Node descriptors
    DEFINE_KSFILTER_CONNECTIONS(FilterConnections), // Topology
    NULL                                            // ComponentId
};


