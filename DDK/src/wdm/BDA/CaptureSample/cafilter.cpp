/**************************************************************************

    AVStream Simulated Hardware Sample

    Copyright (c) 2001, Microsoft Corporation.

    File:

        cafilter.h

    Abstract:
        This file contains some dispatch routines for a custom filter. Please read
        the notes in cafilter.h to understand the limitations of such a custom filter.
            
**************************************************************************/
#include "cafilter.h"

NTSTATUS FilterCreate(IN PKSFILTER Filter, IN PIRP Irp) 
{
    NTSTATUS status = STATUS_SUCCESS;

    // Create filter extension to hold the event pointers
    KSEVENT_ENTRY **ppEventEntry = new (NonPagedPool, MS_SAMPLE_CAPTURE_POOL_TAG) KSEVENT_ENTRY* [2];
    if (!ppEventEntry)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Filter->Context = (PVOID) ppEventEntry;
    return status;
}

NTSTATUS FilterClose(IN PKSFILTER Filter, IN PIRP Irp)
{
    if (Filter->Context)
    {
        KSEVENT_ENTRY** ppEventEntry = (KSEVENT_ENTRY**) Filter->Context;
        delete[] ppEventEntry;
        Filter->Context = NULL;
    }

    return STATUS_SUCCESS;
}

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
    )
{
    if ( DataBufferSize < sizeof(KS_DATARANGE_BDA_TRANSPORT) )
    {
        *DataSize = sizeof( KS_DATARANGE_BDA_TRANSPORT );
        return STATUS_BUFFER_OVERFLOW;
    }
    else if (DataRange -> FormatSize < sizeof (KS_DATARANGE_BDA_TRANSPORT)) 
    {
	return STATUS_NO_MATCH;
    } else
    {
        ASSERT(DataBufferSize == sizeof(KS_DATARANGE_BDA_TRANSPORT));

        *DataSize = sizeof( KS_DATARANGE_BDA_TRANSPORT );
        RtlCopyMemory( Data, (PVOID)DataRange, sizeof(KS_DATARANGE_BDA_TRANSPORT));

        return STATUS_SUCCESS;
    }
}




