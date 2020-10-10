/*++

Copyright (c) 2001  Microsoft Corporation

Module Name:

    Filter.c

Abstract:

    This module contains all  PnP related code.
    Later, we would seperate the data code to another file

Revision History:

    Who         When        What
    --------    --------    ----------------------------------------------

Notes:

--*/

#include "precomp.h"

#define __FILENUMBER    'PNPF'

#pragma NDIS_INIT_FUNCTION(DriverEntry)

//
// Global variables
// 
NDIS_HANDLE         FilterDriverHandle; // NDIS handle for filter driver
NDIS_HANDLE         FilterDriverObject;
NDIS_HANDLE         NdisFilterDeviceHandle = NULL;
PDEVICE_OBJECT      DeviceObject = NULL;

FILTER_LOCK         FilterListLock;
LIST_ENTRY          FilterModuleList;
PWCHAR              InstanceStrings = NULL;



NDIS_FILTER_PARTIAL_CHARACTERISTICS DefaultChars = {
{ 0, 0, 0},
      0,
      FilterSendNetBufferLists,
      FilterSendNetBufferListsComplete,
      FilterReceiveNetBufferLists,
      FilterReturnNetBufferLists
};    




NDIS_STATUS 
DriverEntry(
        IN  PDRIVER_OBJECT      DriverObject,
        IN  PUNICODE_STRING     RegistryPath
    )
/*++
 
Routine Description:

    First entry point to be called, when this driver is loaded.
    Register with NDIS as a filter driver.

Arguments:

    DriverObject - pointer to the system's driver object structure
                   for this driver

    RegistryPath - system's registry path for this driver

Return Value:

    STATUS_SUCCESS if all initialization is successful, STATUS_XXX
    error code if not.

--*/

{
    NDIS_STATUS                             Status;
    NDIS_FILTER_DRIVER_CHARACTERISTICS      FChars;
    NDIS_STRING                             ServiceName;
    NDIS_STRING                             UniqueName;
    NDIS_STRING                             FriendlyName;

    DEBUGP(DL_TRACE,("===>DriverEntry...\n"));
   
    RtlInitUnicodeString(&ServiceName, FILTER_SERVICE_NAME);
    RtlInitUnicodeString(&FriendlyName, FILTER_FRIENDLY_NAME);
    RtlInitUnicodeString(&UniqueName, FILTER_UNIQUE_NAME);
    FilterDriverObject = DriverObject;
    
    do
    {
        NdisZeroMemory(&FChars, sizeof(NDIS_FILTER_DRIVER_CHARACTERISTICS));
        FChars.Header.Type = NDIS_OBJECT_TYPE_FILTER_DRIVER_CHARACTERISTICS;
        FChars.Header.Size = sizeof(NDIS_FILTER_DRIVER_CHARACTERISTICS);
        FChars.Header.Revision = NDIS_FILTER_CHARACTERISTICS_REVISION_1;
        FChars.MajorNdisVersion = FILTER_MAJOR_NDIS_VERSION;
        FChars.MinorNdisVersion = FILTER_MINOR_NDIS_VERSION;
        //
        // BUGBUG: Filter's version and Flags
        //
        FChars.MajorDriverVersion = 1;
        FChars.MinorDriverVersion = 0;
        FChars.Flags = 0;

        FChars.FriendlyName = FriendlyName;
        FChars.UniqueName = UniqueName;
        FChars.ServiceName = ServiceName;

        //
        // for the time being, there is no additional options to register
        // but let's have this handler anyway
        //
        FChars.SetOptionsHandler = FilterRegisterOptions;        
        FChars.AttachHandler = FilterAttach;
        FChars.DetachHandler = FilterDetach;
        FChars.RestartHandler = FilterRestart;
        FChars.PauseHandler = FilterPause;
        FChars.SetFilterModuleOptionsHandler = FilterSetModuleOptions;           
        FChars.RequestHandler = FilterRequest;
        FChars.RequestCompleteHandler = FilterRequestComplete;
        FChars.SendNetBufferListsHandler = FilterSendNetBufferLists;        
        FChars.ReturnNetBufferListsHandler = FilterReturnNetBufferLists;
        FChars.SendNetBufferListsCompleteHandler = FilterSendNetBufferListsComplete;
        FChars.ReceiveNetBufferListsHandler = FilterReceiveNetBufferLists;
        FChars.PnPEventNotifyHandler = FilterPnPEventNotify;
        FChars.PnPEventHandler = FilterPnPEvent;
        FChars.StatusHandler = FilterStatus;
        FChars.CancelSendNetBufferListsHandler = FilterCancelSend;
      
        DriverObject->DriverUnload = FilterUnload;
    
        FilterDriverHandle = NULL;

        FILTER_INIT_LOCK(&FilterListLock);

        InitializeListHead(&FilterModuleList);
        
        Status = NdisFRegisterFilterDriver(DriverObject,
                                           (NDIS_HANDLE)FilterDriverObject,
                                           &FChars, 
                                           &FilterDriverHandle);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DEBUGP(DL_WARN, ("MSFilter: Register filter driver failed.\n")); 
            break;
        }
        //
        // Initilize spin locks
        //

        Status = FilterRegisterDevice();

        if (Status != NDIS_STATUS_SUCCESS)
        {
            FILTER_FREE_LOCK(&FilterListLock);
            DEBUGP(DL_WARN, ("MSFilter: Register device for the filter driver failed.\n")); 
            break;
        }

        
    } 
    while(FALSE);
    
    
    DEBUGP(DL_TRACE, ("<===DriverEntry, Status = %8x\n", Status));
    return Status;
    
}


NDIS_STATUS
FilterRegisterOptions(
        IN NDIS_HANDLE  NdisFilterDriverHandle,
        IN NDIS_HANDLE  FilterDriverContext
        )
{
    DEBUGP(DL_TRACE, ("===>FilterRegisterOptions\n"));
    
    ASSERT(NdisFilterDriverHandle == FilterDriverHandle);
    ASSERT(FilterDriverContext == (NDIS_HANDLE)FilterDriverObject);

    if ((NdisFilterDriverHandle != (NDIS_HANDLE)FilterDriverHandle) ||
        (FilterDriverContext != (NDIS_HANDLE)FilterDriverObject))
    {
        //
        // BUGBUG: replace with NDIS_STATUS_INVALID_PARAMETR when we have one
        //
        return NDIS_STATUS_NOT_RECOGNIZED;
    }

    DEBUGP(DL_TRACE, ("<===FilterRegisterOptions\n"));

    return (NDIS_STATUS_SUCCESS);
}

    
NDIS_STATUS
FilterAttach(
        IN  NDIS_HANDLE                     NdisFilterHandle,
        IN  NDIS_HANDLE                     FilterDriverContext,
        IN  PNDIS_FILTER_ATTACH_PARAMETERS  AttachParameters
        )
/*++

Routine Description:

    Filter attach routine.
    Create filter's context, and allocate NetBufferLists and NetBuffers pools and any 
    other resources, read configuration if needed.

Arguments:

    NdisFilterHandle - Specify a handle identifying this instance of the filter. FilterAttach
                       should save this handle. It is a required  parameter in subsequent calls
                       to NdisFxxx functions.
    BUGBUG: document other parameters as well
 

Return Value:

    NDIS_STATUS_SUCCESS: FilterAttach successfully allocated and initialize data structures
                         for this filter instance.
    NDIS_STATUS_RESOURCES: FilterAttach failed due to insufficient resources.
    NDIS_STATUS_FAILURE: FilterAttach could not set up this instance of this fitler and it has called
                         NDisWriteErrorLogEntry with parameters spedifying the reason for failure.
                         
NOTE: Called at PASSIVE_LEVEL

    FILTER can can NdisFCreateDevice to create a device, so the upper layer can send Irps to the filter.
    The IRP may be a restart IRP, so NdisFRestartFilter may be called.
--*/
{
    PMS_FILTER              pFilter;
    NDIS_STATUS             Status = NDIS_STATUS_SUCCESS;
    PFL_NDIS_FILTER_LIST    FilterHandleEntry;
    NDIS_FILTER_ATTRIBUTES  FilterAttributes;
    ULONG                   Size;
   
    ASSERT(FilterDriverContext == (NDIS_HANDLE)FilterDriverObject);
    if (FilterDriverContext != (NDIS_HANDLE)FilterDriverObject)
    {
        //
        // BUGBUG: replace with NDIS_STATUS_INVALID_PARAMETR when we have one
        //
        return NDIS_STATUS_NOT_RECOGNIZED;
    }
    UNREFERENCED_PARAMETER(AttachParameters);
    
    DEBUGP(DL_TRACE, ("===>FilterAttach: NdisFilterHandle %p\n", NdisFilterHandle));
    do
    {
        Size = sizeof(MS_FILTER) + AttachParameters->FilterModuleGuidName->MaximumLength + AttachParameters->MiniportInstanceName->MaximumLength;
        pFilter = (PMS_FILTER)FILTER_ALLOC_MEM(NdisFilterHandle, Size);
        if (pFilter == NULL)
        {
            DEBUGP(DL_WARN, ("MSFilter: Failed to allocate context structure.\n"));
            Status = NDIS_STATUS_RESOURCES;
            break;
        }
        
        NdisZeroMemory(pFilter, sizeof(MS_FILTER));

        pFilter->FilterModuleName.Length = AttachParameters->FilterModuleGuidName->Length;
        pFilter->FilterModuleName.MaximumLength = AttachParameters->FilterModuleGuidName->MaximumLength;
        pFilter->FilterModuleName.Buffer = (PWSTR)((PUCHAR)pFilter + sizeof(MS_FILTER));
        NdisMoveMemory(pFilter->FilterModuleName.Buffer, 
                        AttachParameters->FilterModuleGuidName->Buffer,
                        pFilter->FilterModuleName.MaximumLength);


        
        pFilter->MiniportFriendlyName.Length = AttachParameters->MiniportInstanceName->Length;
        pFilter->MiniportFriendlyName.MaximumLength = AttachParameters->MiniportInstanceName->MaximumLength;
        pFilter->MiniportFriendlyName.Buffer = (PWSTR)((PUCHAR)pFilter + sizeof(MS_FILTER) + AttachParameters->FilterModuleGuidName->MaximumLength);
        NdisMoveMemory(pFilter->MiniportFriendlyName.Buffer, 
                        AttachParameters->MiniportInstanceName->Buffer,
                        pFilter->MiniportFriendlyName.MaximumLength);

        pFilter->MiniportIfIndex = AttachParameters->IfIndex;
        //
        // The filter should intialize NoTrackRecieves and NoTrackSends properly, for this
        // driver, since its default characteristic has both send and receive handler, so they
        // are initiazed to FALSE.
        //
        pFilter->TrackReceives = TRUE;
        pFilter->TrackSends = TRUE;
        pFilter->FilterHandle = NdisFilterHandle;


        NdisZeroMemory(&FilterAttributes, sizeof(NDIS_FILTER_ATTRIBUTES));
        FilterAttributes.Header.Revision = NDIS_FILTER_ATTRIBUTES_REVISION_1;
        FilterAttributes.Header.Size = sizeof(NDIS_FILTER_ATTRIBUTES);
        FilterAttributes.Header.Type = NDIS_OBJECT_TYPE_FILTER_ATTRIBUTES;
        FilterAttributes.Flags = 0;
        
        Status = NdisFSetAttributes(NdisFilterHandle, 
                                    pFilter,
                                    &FilterAttributes);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DEBUGP(DL_WARN, ("MSFilter: Failed to set attributes.\n"));
            break;
        }
        //
        // Allocate send and receive Net Buffer List pools
        //
        {
            NET_BUFFER_LIST_POOL_PARAMETERS PoolParameters;

            NdisZeroMemory(&PoolParameters, sizeof(NET_BUFFER_LIST_POOL_PARAMETERS));
            
            PoolParameters.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
            PoolParameters.Header.Revision = NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
            PoolParameters.Header.Size = sizeof(PoolParameters);
            PoolParameters.ProtocolId = 0;
            PoolParameters.ContextSize = 0;
            PoolParameters.fAllocateNetBuffer = TRUE;
            PoolParameters.PoolTag = FILTER_TAG;

            pFilter->SendNetBufferListPoolHandle = NdisAllocateNetBufferListPool(
                                                    NdisFilterHandle,
                                                    &PoolParameters);
                                                        
            if (pFilter->SendNetBufferListPoolHandle == NULL)
            {
                DEBUGP(DL_WARN, ("MSFilter: Failed to allocate send NBL pool.\n"));
                Status = NDIS_STATUS_RESOURCES;
                break;
            }
            
            pFilter->RcvNetBufferListPoolHandle = NdisAllocateNetBufferListPool(
                                                        NdisFilterHandle,
                                                        &PoolParameters);
                                                        
            if (pFilter->RcvNetBufferListPoolHandle == NULL)
            {
                DEBUGP(DL_WARN, ("FilterAttach: Failed to allocate recv NBL pool.\n"));
                Status = NDIS_STATUS_RESOURCES;
                break;
            }
        }

        FILTER_INIT_LOCK(&pFilter->SendLock);
        
        FILTER_INIT_LOCK(&pFilter->RcvLock);
        InitializeQueueHeader(&pFilter->SendNBLQueue);
        InitializeQueueHeader(&pFilter->RcvNBLQueue);
        
        pFilter->State = FilterPaused;

        FILTER_ACQUIRE_LOCK(&FilterListLock, FALSE);
        InsertHeadList(&FilterModuleList, &pFilter->FilterModuleLink);
        FILTER_RELEASE_LOCK(&FilterListLock, FALSE);
        
    }
    while (FALSE);
    
    //
    // BUGBUG: need a API to call NdisWriteErrorLogEntry
    //
    if (Status != NDIS_STATUS_SUCCESS)
    {
        if (pFilter != NULL)
        {
        
            if (pFilter->SendNetBufferListPoolHandle != NULL)
            {
                NdisFreeNetBufferListPool(pFilter->SendNetBufferListPoolHandle);
            }
            if (pFilter->RcvNetBufferListPoolHandle != NULL)
            {
                NdisFreeNetBufferListPool(pFilter->RcvNetBufferListPoolHandle);
            }
            
            FILTER_FREE_MEM(pFilter);
        }
    }
    
    DEBUGP(DL_TRACE, ("<===FilterAttach:    Status %x\n", Status));
    return Status;
}

NDIS_STATUS
FilterPause(
        IN  NDIS_HANDLE     FilterModuleContext,
        IN  PNDIS_FILTER_PAUSE_PARAMETERS   PauseParameters
        )
/*++
 
Routine Description:

    Filter pause routine.
    Complete all the outstanding sends and queued sends,
    Waiting for all the outstanding recvs to be returned 
    and return all the queued receives

Arguments:

    FilterModuleContext - pointer to the filter context stucture.

Return Value:

    STATUS_SUCCESS if filter pauses successful, STATUS_PENDING
    if not.

NOTE: when the filter is in pause state, it can still process requests, complete sending,
    and returning packets to the lower filter, and also indicate status.
    Called at PASSIVE_LEVEL
      
--*/
{
    PMS_FILTER          pFilter = (PMS_FILTER)(FilterModuleContext);
    PQUEUE_ENTRY        pEntry;
    PNET_BUFFER_LIST    NetBufList;
    NDIS_STATUS         Status;
    PNET_BUFFER_LIST    pNBL; 
    PNET_BUFFER_LIST    LastNBL;

    UNREFERENCED_PARAMETER(PauseParameters);
    
    DEBUGP(DL_TRACE, ("===>NDISLWF FilterPause: FilterInstance %p\n", FilterModuleContext));
    
    //
    // Set the flag that the filter is going to pause
    // 
    FILTER_ASSERT(pFilter->State == FilterRunning); 
    
    FILTER_ACQUIRE_LOCK(&pFilter->Lock, FALSE);
    pFilter->State = FilterPausing;
    FILTER_RELEASE_LOCK(&pFilter->Lock, FALSE);
    
    
    //
    // Checks the send queue 
    //
    FILTER_ACQUIRE_LOCK(&pFilter->SendLock, FALSE);
   
    filterCompleteQueuedSend(pFilter, FALSE);
    
    FILTER_RELEASE_LOCK(&pFilter->SendLock, FALSE);
    //
    // Check the recv queue
    //
    NetBufList = NULL;
    
    FILTER_ACQUIRE_LOCK(&pFilter->RcvLock, FALSE);

    filterReturnQueuedRecv(pFilter, FALSE);
    
    FILTER_RELEASE_LOCK(&pFilter->RcvLock, FALSE);
    
    //
    // Stop the timers, handle later
    //

    //
    // Is there any outstanding request or sending
    // 
    Status = NDIS_STATUS_SUCCESS;
    //
    // BUGBUG: Pause has nothing to do with requests
    //
    
    //
    // If a filter needs to pause, it has to wait all 
    // outstanding sends, which is modified or initiate by itself, to be completed
    // and all the outstanding indications, which is initiated by itself, to be 
    // returned.
    // 
    FILTER_ACQUIRE_LOCK(&pFilter->Lock,  FALSE);
    if (pFilter->OutstandingSends || pFilter->OutstandingRcvs)
    {
        Status =  NDIS_STATUS_PENDING;
    }
    else
    {
        pFilter->State = FilterPaused;
        
    }
    FILTER_RELEASE_LOCK(&pFilter->Lock, FALSE);
    
    DEBUGP(DL_TRACE, ("<===FilterPause:  Status %x\n", Status));
    return Status;
}

NDIS_STATUS
FilterRestart(
    IN  NDIS_HANDLE     FilterModuleContext,
    IN  PNDIS_FILTER_RESTART_PARAMETERS RestartParameters
    )
/*++

Routine Description:
 
    Filter restart routine.
    Restart the filter

Arguments:

    FilterModuleContext - pointer to the filter context stucture.

Return Value:

    NDIS_STATUS_SUCCESS: if filter restarts successfully
    NDIS_STATUS_XXX: Otherwise.


NOTE: called at PASSIVE_LEVEL

--*/
{
    NDIS_STATUS     Status;
    PMS_FILTER      pFilter = (PMS_FILTER)FilterModuleContext; // BUGBUG, the cast may be wrong
    NDIS_HANDLE     ConfigurationHandle = NULL;
    
    DEBUGP(DL_TRACE, ("===>FilterRestart:   FilterModuleContext %p\n", FilterModuleContext));
    
    UNREFERENCED_PARAMETER(RestartParameters);
    FILTER_ASSERT(pFilter->State == FilterPaused);

    
    Status = NdisOpenConfigurationEx(FilterDriverHandle, &ConfigurationHandle);
    if (Status != NDIS_STATUS_SUCCESS)
    {
        //
        // Filter driver can choose to faile the restart if it cannot open the configuration
        //
        DEBUGP(DL_WARN, ("FilterRestart: Cannot open configuration.\n"));
    }


    if (Status == NDIS_STATUS_SUCCESS)
    {
        NdisCloseConfiguration(ConfigurationHandle);
    }

    //
    // If everything is OK, set the filter in running state
    // If it get preempted, it doesn't matter 
    //
    pFilter->State = FilterRunning; // when successful
                    
    
    Status = NDIS_STATUS_SUCCESS;
    
    DEBUGP(DL_TRACE, ("<===FilterRestart:   Status %x\n", Status));
    return NDIS_STATUS_SUCCESS;
}


NDIS_STATUS
FilterDetach(
        IN  NDIS_HANDLE     FilterModuleContext
        )
/*++

Routine Description:

    Filter detach routine.
    This is a required function that will deallocate all the resources allocated during
    FitlerAttach. NDIS calls FilterAttachto remove a filter instance from a fitler stack.

Arguments:

    FilterModuleContext - pointer to the filter context area.

Return Value:

    NDIS_STATUS_SUCCESS: if filter is detached successfully.
    NDIS_STATUS_XXX: Otherwise.

NOTE: return STATUS_SUCCESS only     

NOTE: Called at PASSIVE_LEVEL and the filter is in paused state

--*/
{
    PMS_FILTER                  pFilter = (PMS_FILTER)FilterModuleContext;
    PFL_NDIS_FILTER_LIST        pEntry;
    PLIST_ENTRY                 pLink;
    
    DEBUGP(DL_TRACE, ("===>FilterDetach:    FilterInstance %p\n", FilterModuleContext));
    
    //
    // Filter must be in paused state
    // 
    FILTER_ASSERT(pFilter->State == FilterPaused);

    //
    // Free Packet pools
    // 
    if (pFilter->SendNetBufferListPoolHandle)
    {
        NdisFreeNetBufferListPool(pFilter->SendNetBufferListPoolHandle);
    }
    if (pFilter->RcvNetBufferListPoolHandle)
    {
        NdisFreeNetBufferListPool(pFilter->RcvNetBufferListPoolHandle);
    }

    //
    // Free spin locks
    // 
    NdisFreeSpinLock(&pFilter->SendLock);
    NdisFreeSpinLock(&pFilter->RcvLock);
                
    //
    // Don't come up anything that would prevent the filter from detaching
    //
    
    //
    // Free filter instance name if allocated.
    //
    if (pFilter->FilterName.Buffer != NULL)
    {
        FILTER_FREE_MEM(pFilter->FilterName.Buffer);
    }

    FILTER_ACQUIRE_LOCK(&FilterListLock, FALSE);
    RemoveEntryList(&pFilter->FilterModuleLink);
    FILTER_RELEASE_LOCK(&FilterListLock, FALSE);
    //
    // Free the memory allocated
    FILTER_FREE_MEM(pFilter);

    //
    // Alway return success
    //
    DEBUGP(DL_TRACE, ("<===FilterDetach Successfully\n"));
    
    return NDIS_STATUS_SUCCESS;
}

VOID
FilterUnload(
        IN  PDRIVER_OBJECT      DriverObject
        )
/*++

Routine Description:

    Filter driver's unload routine.
    Deregister the driver from NDIS

Arguments:

    DriverObject - pointer to the system's driver object structure
                   for this driver

Return Value:

    NONE
 
--*/
{
    DEBUGP(DL_TRACE, ("===>FilterUnload\n"));
    //
    // Should free the filter context list
    // 
    FilterDeregisterDevice();
    NdisFDeregisterFilterDriver(FilterDriverHandle);
    
#if DBG    
    FILTER_ACQUIRE_LOCK(&FilterListLock, FALSE);
    ASSERT(IsListEmpty(&FilterModuleList));

    FILTER_RELEASE_LOCK(&FilterListLock, FALSE);
    
#endif    
    
    FILTER_FREE_LOCK(&FilterListLock);
    
    DEBUGP(DL_TRACE, ("<===FilterUnload\n"));
    
}

NDIS_STATUS
FilterRequest(
        IN  NDIS_HANDLE         FilterModuleContext,
        IN  PNDIS_OID_REQUEST   Request
        )

/*++

Routine Description:

    Request handler 
    Handle requests from upper layers

Arguments:

    FilterModuleContext: Pointer to out filter
    Request: Pointer to request passed down
   

Return Value:

     NDIS_STATUS_SUCCESS
     NDIS_STATUS_PENDING
     NDIS_STATUS_XXX

NOTE: Called at <= DISPATCH_LEVEL      
 
--*/
{
    PMS_FILTER              pFilter = (PMS_FILTER)FilterModuleContext;
    NDIS_STATUS             Status;
    PNDIS_OID_REQUEST       ClonedRequest=NULL;
    BOOLEAN                 bSubmitted = FALSE;
    PFILTER_REQUEST_CONTEXT Context;
    
    
    DEBUGP(DL_TRACE, ("===>FilterRequest: Request %p.\n", Request));

    do
    {
        Status = NdisAllocateCloneRequest(pFilter->FilterHandle,
                                            Request,
                                            FILTER_TAG,
                                            &ClonedRequest);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DEBUGP(DL_WARN, ("FilerRequest: Cannot Clone Request\n"));
            break;
        }

        Context = (PFILTER_REQUEST_CONTEXT)(&ClonedRequest->SourceReserved[0]);
        *Context = Request;

        bSubmitted = TRUE;

        Status = NdisFRequest(pFilter->FilterHandle, ClonedRequest);

        if (Status != NDIS_STATUS_PENDING)
        {
            FilterRequestComplete(pFilter, ClonedRequest,Status);
            Status = NDIS_STATUS_PENDING;
        } 
        
    }while (FALSE);

    if (bSubmitted == FALSE)
    {
        switch(Request->RequestType)
        {
            case NdisRequestMethod:
                Request->DATA.METHOD_INFORMATION.BytesRead = 0;
                Request->DATA.METHOD_INFORMATION.BytesNeeded = 0; 
                Request->DATA.METHOD_INFORMATION.BytesWritten = 0; 
                break;

            case NdisRequestSetInformation:
            
                Request->DATA.SET_INFORMATION.BytesRead = 0;
                Request->DATA.SET_INFORMATION.BytesNeeded = 0; 
                break;

            case NdisRequestQueryInformation:
            case NdisRequestQueryStatistics:
            default:
            
                Request->DATA.QUERY_INFORMATION.BytesWritten = 0;
                Request->DATA.QUERY_INFORMATION.BytesNeeded = 0; 
                break;
        }

    }
    DEBUGP(DL_TRACE, ("<===FilterRequest: Status %8x.\n", Status));

    return Status;

}
    
VOID
FilterRequestComplete(
        IN  NDIS_HANDLE         FilterModuleContext,
        IN  PNDIS_OID_REQUEST   Request,
        IN  NDIS_STATUS         Status
        )
/*++

Routine Description:

    Same operation we need to do when outstanding request are completed

Arguments:

    FilterModuleContext -- Pointer to the filter context area
    NdisRequest - The request to complete
    Status - The completion status
  
Return Value:

    NONE
 
--*/
{
    PMS_FILTER                          pFilter = (PMS_FILTER)FilterModuleContext;
    PNDIS_OID_REQUEST                   OriginalRequest;
    PFILTER_REQUEST_CONTEXT             Context;
    
    DEBUGP(DL_TRACE, ("===>RequestComplete, Request %p.\n", Request));
    Context = (PFILTER_REQUEST_CONTEXT)(&Request->SourceReserved[0]);
    OriginalRequest = (*Context);

    //
    // This is the internal request
    //
    if (OriginalRequest == NULL)
    {
        filterInternalRequestComplete(pFilter, Request, Status);
        return;
    }
        
    //
    // Copy the information from the returned request to the original request
    //
    switch(Request->RequestType)
    {
        case NdisRequestMethod:
            OriginalRequest->DATA.METHOD_INFORMATION.OutputBufferLength =  Request->DATA.METHOD_INFORMATION.OutputBufferLength;
            OriginalRequest->DATA.METHOD_INFORMATION.BytesRead = Request->DATA.METHOD_INFORMATION.BytesRead;
            OriginalRequest->DATA.METHOD_INFORMATION.BytesNeeded = Request->DATA.METHOD_INFORMATION.BytesNeeded;; 
            OriginalRequest->DATA.METHOD_INFORMATION.BytesWritten = Request->DATA.METHOD_INFORMATION.BytesWritten; 
            break;

        case NdisRequestSetInformation:
        
            OriginalRequest->DATA.SET_INFORMATION.BytesRead = Request->DATA.SET_INFORMATION.BytesRead;
            OriginalRequest->DATA.SET_INFORMATION.BytesNeeded = Request->DATA.SET_INFORMATION.BytesNeeded;; 
            break;

        case NdisRequestQueryInformation:
        case NdisRequestQueryStatistics:
        default:
        
            OriginalRequest->DATA.QUERY_INFORMATION.BytesWritten = Request->DATA.QUERY_INFORMATION.BytesWritten;
            OriginalRequest->DATA.QUERY_INFORMATION.BytesNeeded = Request->DATA.QUERY_INFORMATION.BytesNeeded;; 
            break;
    }


    (*Context) = NULL;

    NdisFreeCloneRequest(pFilter->FilterHandle, Request);

    NdisFRequestComplete(pFilter->FilterHandle, OriginalRequest, Status);
    
    DEBUGP(DL_TRACE, ("<===RequestComplete.\n"));
}


VOID
FilterStatus(
        IN  NDIS_HANDLE             FilterModuleContext,
        IN  PNDIS_STATUS_INDICATION StatusIndication
        )
/*++

Routine Description:

    Indicate Status Handle

Arguments:
 
    FilterModuleContext: Pointer to our filter 
    GeneralStatus: 
    StatusBuffer:
    StatusBufferSize:
   
Return Value:

    NONE
NOTE: called at <= DISPATCH_LEVEL     
 
  FILTER driver may call NdisFIndicateStatus to generate status indication to all higher layer modules.
  
--*/
{
    PMS_FILTER              pFilter = (PMS_FILTER)FilterModuleContext;
    NDIS_STATUS             GeneralStatus = StatusIndication->StatusCode;
    PVOID                   StatusBuffer = StatusIndication->StatusBuffer;
    UINT                    StatusBufferSize = StatusIndication->StatusBufferSize;

    DEBUGP(DL_TRACE, ("===>FilterStaus, IndicateStatus = %8x.\n", GeneralStatus));

#if DBG
    FILTER_ACQUIRE_LOCK(&pFilter->Lock, FALSE);
    ASSERT(pFilter->bIndicating == FALSE);
    pFilter->bIndicating = TRUE;
    FILTER_RELEASE_LOCK(&pFilter->Lock, FALSE);
#endif    
    
    
    // Now, No status need to handle by the filter. May get one later
    //
    NdisFIndicateStatus(pFilter->FilterHandle, StatusIndication);

#if DBG    
    FILTER_ACQUIRE_LOCK(&pFilter->Lock, FALSE);
    ASSERT(pFilter->bIndicating == TRUE);
    pFilter->bIndicating = FALSE;
    
    FILTER_RELEASE_LOCK(&pFilter->Lock, FALSE);


#endif
    
    DEBUGP(DL_TRACE, ("<===FilterStaus.\n"));

}

VOID
FilterPnPEventNotify(
        IN  NDIS_HANDLE             FilterModuleContext,
        IN  NDIS_DEVICE_PNP_EVENT   DevicePnPEvent,
        IN  PVOID                   InformationBuffer,
        IN  ULONG                   InformationBufferLength
        )
/*++

Routine Description:

    FilterPnpEvent handler
 
Arguments:

    FilterModuleContext: Pointer to our filter
    NetPnPEvent: Pointer to an PnP event
  
Return Value:

     NONE

NOTE: called at PASSIVE_LEVEL      
  
--*/
{
    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    

    DEBUGP(DL_TRACE, ("===>FilterPnPEventNotify: NetPnPEvent = %p.\n", DevicePnPEvent));

    //
    // BUGBUG: how to process this??
    //
    switch (DevicePnPEvent)
    {

        case NdisDevicePnPEventQueryRemoved: 
            //
            // If the lower miniport power state changed, what does the filter should do???
            //
            
            
        case NdisDevicePnPEventRemoved:
        case NdisDevicePnPEventSurpriseRemoved:
        case NdisDevicePnPEventQueryStopped:
        case NdisDevicePnPEventStopped:
        case NdisDevicePnPEventPowerProfileChanged:
        case NdisDevicePnPEventFilterListChanged:
            
           //  NdisFPnPEventComplete(pFilter->FilterHandle, NetPnPEvent, Status);
            
            break;
            
        default:
            //
            // Any other PnP Event need to handle?
            //
            DEBUGP(DL_ERROR, ("PnPEventNotify: Invalid event.\n"));
            FILTER_ASSERT(FALSE);
            
            break;
    }
            
    DEBUGP(DL_TRACE, ("<===FilterPnPEventNotify\n"));

}


VOID
FilterPnPEvent(
        IN  NDIS_HANDLE             FilterModuleContext,
        IN  PNET_PNP_EVENT          NetPnPEvent
        )
{
    PMS_FILTER                pFilter = (PMS_FILTER)FilterModuleContext;

    NdisFPnPEvent(pFilter->FilterHandle, NetPnPEvent);
}

VOID
FilterSendNetBufferListsComplete(
        IN  NDIS_HANDLE         FilterModuleContext,
        IN  PNET_BUFFER_LIST    NetBufferLists,
        IN  BOOLEAN             DispatchLevel
        )
/*++
 
Routine Description:

    SendNetBufferListComplete 

Arguments:

      
     
Return Value:

     NONE
 
--*/
{
    PMS_FILTER         pFilter = (PMS_FILTER)FilterModuleContext;
    PNET_BUFFER_LIST   CurrNbl, NextNbl, PrevNbl = NULL, LastNbl = NULL;
    ULONG              NumOfSendCompletes = 0;
    
   
    DEBUGP(DL_TRACE, ("===>SendNBLComplete, NetBufferList: %p.\n", NetBufferLists));

    CurrNbl= NetBufferLists;
    
    while (CurrNbl)
    {
        //
        // If the NetBufferList is owned by the filter
        // 
        if (NdisGetPoolFromNetBufferList(CurrNbl) == pFilter->SendNetBufferListPoolHandle)
        {
            //
            // Should we free the netbufferlist and all the netbuffers and data???
            //
                        
            NextNbl= CurrNbl->Next;
            //
            // Free the Net Buffer List
            //
            filterFreeNetBufferList(CurrNbl, DispatchLevel);
            CurrNbl= NextNbl;
        }
        else
        {
            NumOfSendCompletes++;
            if (PrevNbl == NULL)
            {
                PrevNbl = CurrNbl;
            }
            else
            {
                LastNbl->Next = CurrNbl;
            }
            LastNbl = CurrNbl;
            CurrNbl = CurrNbl->Next;
        }
        
    }
            
    //
    // If there is any NetBufferList needed to be returned?
    //
    if (PrevNbl != NULL)
    {
        //
        // if necessary, undo any modifications to the NetBufferList thate were performed "on the way down"
        // BUGBUG: Need this APIs
        //
        NdisFSendNetBufferListsComplete(pFilter->FilterHandle, PrevNbl, DispatchLevel);
    }
 
    if (pFilter->TrackSends)
    {
    FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
    pFilter->OutstandingSends -= NumOfSendCompletes;
    FILTER_LOG_SEND_REF(2, pFilter, PrevNbl, pFilter->OutstandingSends);
    
    //
    // If we need to call PauseComplet
    // 
    if (FILTER_READY_TO_PAUSE(pFilter))
    {
        pFilter->State = FilterPaused;
            
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
            
         
        DEBUGP(DL_INFO, ("MSFilter: Pause is complete.\n"));
        NdisFPauseComplete( pFilter->FilterHandle);
    }
    else
    {
    
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
    }
    }
    
    DEBUGP(DL_TRACE, ("<===SendNBLComplete.\n"));
}


VOID
FilterSendNetBufferLists(
        IN  NDIS_HANDLE         FilterModuleContext,
        IN  PNET_BUFFER_LIST    NetBufferLists,
        IN  ULONG               SendFlags,
        IN  BOOLEAN             DispatchLevel
        )
/*++
 
Routine Description:

    Send Net Buffer List handler
    This function is an optional function for filter drivers. If provided, NDIS
    will call this function to transmit a linked list of NetBuffers, described by a 
    NetBuferList, over the network. If this handler is NULL, NDIS will skip calling
    this fitler when sending a NetBufferList and will call the next lower fitler 
    in the stack with a non_NULL FilterSendNetBufferList handleror the miniport driver.
    A filter that doesn't provide a FilerSendNetBufferList handler can not initiate a 
    send o its own.

Arguments:

    FilterModuleContext: Pointer to our filter context area.
    NetBufferLists: Pointer to a List of NetBufferLists.
    DispatchLevel: A boolean specifying if the called is at DISPATCH_LEVEL                     
  

Return Value:
 
    NDIS_STATUS_SUCCESS: 
    NDIS_STATUS_PENDING:
    NDIS_STATUS_INVALID_PACKET:
    NDIS_STATUS_RESOURCES:
    NDIS_STATUS_FAILURE:


NOTE: The filter will act like a passthru filter.       
 
--*/
{
    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    NDIS_STATUS         Status = NDIS_STATUS_SUCCESS;
    PNET_BUFFER_LIST    CurrNbl;
    
    DEBUGP(DL_TRACE, ("===>SendNetBufferList: NBL = %x.\n", NetBufferLists));
            
    //
    // If the filter is not in running state, fail the send
    // 
    do
    {
        FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
        if (pFilter->State != FilterRunning)
        {
            FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
            NdisFSendNetBufferListsComplete(pFilter->FilterHandle, NetBufferLists, DispatchLevel);
            break;
            
        }
        CurrNbl = NetBufferLists;
        if (pFilter->TrackSends)
        {
        while (CurrNbl)
        {
            pFilter->OutstandingSends++;
            FILTER_LOG_SEND_REF(1, pFilter, CurrNbl, pFilter->OutstandingSends);
            
            CurrNbl = CurrNbl->Next;
        }
        }
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
        //
        // If necessary, queue the NetBufferList in a local structure for later processing
        //
        NdisFSendNetBufferLists(pFilter->FilterHandle, NetBufferLists, SendFlags, DispatchLevel);
        
        
    }
    while (FALSE);
    
    DEBUGP(DL_TRACE, ("<===SendNetBufferList: Status = %8x.\n", Status));
}




VOID
FilterReturnNetBufferLists(
        IN  NDIS_HANDLE         FilterModuleContext,
        IN  PNET_BUFFER_LIST    NetBufferLists,
        IN  BOOLEAN             DispatchLevel
        )
/*++

Routine Description:

    FilerReturnNetBufferLists handler
    FilterReturnNetBufferLists is an optional function. If provided NDIS calls 
    FitlerReturnNetBufferLists to return the ownership of one or more NetBufferLists
    and their embedded NetBuffers to the filter driver. If this handler is NULL, NDIS
    will skip calling this fitler when returning NetBufferLists to the underlying 
    miniport and will call the next lower fitler in the stack with a non_NULL 
    FilterReturnNetBufferLists handler or the miniport driver. A filter that doesn't
    provide a FitlerReturnNetBufferLists handler cannot initiate a receive indication
    on its own.

Arguments:

    FitlerInstanceContext: Pointer to our filter context area.
    NetBufferLists: A linked list of NetBufferLists that filter driver indicated by a 
                    previous call to NdisFIndicateReceiveNetBufferLists.
    DispatchLevel: A boolean specifying if the caller is at DISPATCH_LEVEL
   

Return Value:

     NONE

--*/
{
    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    PNET_BUFFER_LIST    PrevNbl = NULL, LastNbl = NULL;
    PNET_BUFFER_LIST    CurrNbl = NULL;
    PNET_BUFFER_LIST    NextNbl = NULL;
    UINT                NumOfNetBufferLists = 0;
    ULONG               Ref;
    
    DEBUGP(DL_TRACE, ("===>ReturnNetBufferLists, NetBufferLists is %p.\n", NetBufferLists));

    CurrNbl = NetBufferLists;
    while (CurrNbl)
    {
        //
        // If the NetBufferList is owned by the filter
        // 
        if (NdisGetPoolFromNetBufferList(CurrNbl) == pFilter->RcvNetBufferListPoolHandle)
        {
            //
            // Should we free the netbufferlist and all the netbuffers and data???
            //
            
            NextNbl = CurrNbl->Next;
            //
            // Free the Net Buffer List
            //
            filterFreeNetBufferList(CurrNbl, DispatchLevel);
            CurrNbl = NextNbl;
        }
        else
        {
            //
            // Undo the operations it did with the NetBufferList on the receive indication
            //
            NumOfNetBufferLists ++;
            if (PrevNbl == NULL)
            {
                PrevNbl = CurrNbl;
            }
            else
            {
                LastNbl->Next = CurrNbl;
            }
            LastNbl = CurrNbl;
            CurrNbl = CurrNbl->Next;
        }
        
    }
            
    //
    // If there is any NetBufferList needed to be returned?
    //
    if (PrevNbl!= NULL)
    {
        //
        // 
        //
        NdisFReturnNetBufferLists(pFilter->FilterHandle, PrevNbl, DispatchLevel);
    }
 
    //
    // If the filter is in the process of pausing
    // 
    if (pFilter->TrackReceives)
    {
    FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);

    pFilter->OutstandingRcvs -= NumOfNetBufferLists;
    Ref = pFilter->OutstandingRcvs;
    FILTER_LOG_RCV_REF(3, pFilter, NetBufferLists, Ref);
            

    if (FILTER_READY_TO_PAUSE(pFilter))
    {
        pFilter->State = FilterPaused;
        
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
        NdisFPauseComplete(pFilter->FilterHandle);
    }
    else
    {
        //
        // Pause still pending
        //
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
    }
    }
    DEBUGP(DL_TRACE, ("<===ReturnNetBufferLists.\n"));
    

}



VOID
FilterReceiveNetBufferLists(
        IN  NDIS_HANDLE         FilterModuleContext,
        IN  PNET_BUFFER_LIST    NetBufferLists,
        IN  NDIS_STATUS         Status,
        IN  BOOLEAN             DispatchLevel
        )
/*++

Routine Description:

    FilerReceiveNetBufferLists is an optional function for filter drivers. If provided, this function
    process receive indications made by underlying NIC or lower level filter drivers. This function
    can also be called as a result of loopback. If this handler is NULL, NDIS will skip calling this
    filter when processing a receive indication and will call the next upper filter in the stack with
    a non-NULL FitlerReceiveNetBufferLists handler or the procotol driver. A filter that doesn't 
    provide a FilterReceiveNetBufferLists handler can not provided a FilterReturnNetBufferLists handler
    or a initiate a receive indication on its own.

Arguments:

    FilterModuleContext: Pointer to our filter context area.
    NetBufferLists: A linked list of NetBufferLists allocated by underlying driver each containing
                    one NetBuffer.
    Status: Specify whether or not NDIS will reclaim the NetBufferLists and embedded NetBuffers upon
            return of the call
    DispatchLevel: A Boolean specifying if the caller is at DISPATCH_LEVEL        
  

Return Value:

    None
 
--*/
{

    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    NDIS_STATUS         ReturnStatus = NDIS_STATUS_SUCCESS;
    UINT                NumOfNetBufferLists = 0;
    PNET_BUFFER_LIST    NextNetBufferList;

    ULONG               Ref;
    
    DEBUGP(DL_TRACE, ("===>ReceiveNetBufferList: NetBufferLists = %p.\n", NetBufferLists));
    
    //
    // If filter is not in running state
    // 
    FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
    if (pFilter->State != FilterRunning)
    {
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);

        if (Status != NDIS_STATUS_RESOURCES)
        {
            NdisFReturnNetBufferLists(pFilter->FilterHandle, NetBufferLists, DispatchLevel);
        }
        
    }
    else
    {
        //
        // Check if any of the NetBufferList doesn't need to be indicated
        //

        for (NextNetBufferList = NetBufferLists; 
             NextNetBufferList != NULL; 
             NextNetBufferList = NextNetBufferList->Next)
        {
            NumOfNetBufferLists ++;
        }
        ASSERT(NumOfNetBufferLists >= 1);
            
        // 
        // If necessary, queue the NetBufferList in a local structure for later processing.
        // We may need to travel the list, some of them may not need post processing
        //
        if (pFilter->TrackReceives)
        {
            pFilter->OutstandingRcvs += NumOfNetBufferLists;
        }
        Ref = pFilter->OutstandingRcvs;
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);

        FILTER_LOG_RCV_REF(1, pFilter, NetBufferLists, Ref);

        NdisFIndicateReceiveNetBufferLists(
                   pFilter->FilterHandle,
                   NetBufferLists,
                   Status,
                   DispatchLevel);

        if (Status == NDIS_STATUS_RESOURCES)
        {
            FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
            if (pFilter->TrackReceives)
            {
                pFilter->OutstandingRcvs -= NumOfNetBufferLists;
            }
            Ref = pFilter->OutstandingRcvs;
            
            FILTER_LOG_RCV_REF(2, pFilter, NetBufferLists, Ref);
            //
            // If between this, a pause is issued
            // 
            if (FILTER_READY_TO_PAUSE(pFilter))
            {
                pFilter->State = FilterPaused;
                
                FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
                NdisFPauseComplete(pFilter->FilterHandle);
                
            }
            else
            {
                
                FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
            }
        }
    }
    
    DEBUGP(DL_TRACE, ("<===ReceiveNetBufferList: Status = %8x.\n", Status));
    
}



VOID
FilterCancelSend(
    IN  NDIS_HANDLE             FilterModuleContext,
    IN  PVOID                   CancelId
    )
/*++

Routine Description:

    This function cancels any NET_BUFFER_LISTs pended in the filter and then
    calls the NdisFCancelSendNetBufferLists to propagate the CancelSend to the next filter 
    miniport

Arguments:

    
Return Value:

    None

*/
{
    PMS_FILTER                               pFilter = (PMS_FILTER)FilterModuleContext;

    NdisFCancelSendNetBufferLists(pFilter->FilterHandle,CancelId);
}


 
NDIS_STATUS
FilterSetModuleOptions(
    IN  NDIS_HANDLE             FilterModuleContext
    )
/*++

Routine Description:

    This function set the optional handlers for on the filter
      
Arguments:

    NetBufferLists: Pointer to the NetBufferList to be freed.
    DispatchLevel: A Boolean specifying if the caller is at DISPATCH_LEVEL        
  
Return Value:

    None
 
 NOTE: NetBufferList has to be allocated by the fitler
 
--*/
{
    
   PMS_FILTER                               pFilter = (PMS_FILTER)FilterModuleContext;
   NDIS_FILTER_PARTIAL_CHARACTERISTICS      OptionalHandlers;
   NDIS_STATUS                              Status = NDIS_STATUS_SUCCESS;

   //
   // Demonstrate how to change send/receive handlers at runtime.
   //
   if (FALSE)
   {
       UINT      i;

      
       pFilter->CallsRestart++;

       i = pFilter->CallsRestart % 8;

       pFilter->TrackReceives = TRUE;
       pFilter->TrackSends = TRUE;

       NdisMoveMemory(&OptionalHandlers, &DefaultChars, sizeof(OptionalHandlers));
       OptionalHandlers.Header.Type = NDIS_OBJECT_TYPE_FILTER_PARTIAL_CHARACTERISTICS;
       OptionalHandlers.Header.Size = sizeof(OptionalHandlers);
       switch (i)
       {
           
            case 0: 
                OptionalHandlers.ReceiveNetBufferListsHandler = NULL;
                pFilter->TrackReceives = FALSE;
                break;

            case 1:
                
                OptionalHandlers.ReturnNetBufferListsHandler = NULL;
                pFilter->TrackReceives = FALSE;
                break;

            case 2:
                OptionalHandlers.SendNetBufferListsHandler = NULL;
                pFilter->TrackSends = FALSE;
                break;

            case 3:
                OptionalHandlers.SendNetBufferListsCompleteHandler = NULL;
                pFilter->TrackSends = FALSE;
                break;

            case 4:
                OptionalHandlers.ReceiveNetBufferListsHandler = NULL;
                OptionalHandlers.ReturnNetBufferListsHandler = NULL;
                break;

            case 5:
                OptionalHandlers.SendNetBufferListsHandler = NULL;
                OptionalHandlers.SendNetBufferListsCompleteHandler = NULL;
                break;

            case 6:
                
                OptionalHandlers.ReceiveNetBufferListsHandler = NULL;
                OptionalHandlers.ReturnNetBufferListsHandler = NULL;
                OptionalHandlers.SendNetBufferListsHandler = NULL;
                OptionalHandlers.SendNetBufferListsCompleteHandler = NULL;
                break;
                
            case 7:
                break;
       }
       Status = NdisSetOptionalHandlers(pFilter->FilterHandle, (PNDIS_DRIVER_OPTIONAL_HANDLERS)&OptionalHandlers );
   }
   return Status;
}



VOID
filterFreeNetBufferList(
    IN  PNET_BUFFER_LIST        NetBufferList,
    IN  BOOLEAN                 DispatchLevel
    )
/*++
 
Routine Description:

    Free all the NetBuffers in the list(exept the one allocated with NetBufferList
    and free all the memory associated with the NetBuffers
    and finally free the NetBufferList
    
Arguments:

    NetBufferLists: Pointer to the NetBufferList to be freed.
    DispatchLevel: A Boolean specifying if the caller is at DISPATCH_LEVEL        
   
Return Value:

    None

NOTE: NetBufferList has to be allocated by the fitler

--*/
{
    PNET_BUFFER         NetBuffer = NULL;
    PNET_BUFFER         NextNetBuffer = NULL;
    PNDIS_BUFFER        NdisBuffer = NULL;
    PVOID               Va = NULL;
    UINT                BufferLength;
    
    
    DEBUGP(DL_TRACE, ("===>filterFreeNetBufferList.\n"));

    NetBuffer = NetBufferList->FirstNetBuffer->Next;

    ASSERT(NetBuffer != NULL);

    while (NetBuffer)
    {
        //
        // Free all the data contained in the NetBuffer
        // 
        NdisBuffer = NetBuffer->MdlChain;
        while (NdisBuffer)
        {
            NdisQueryBufferSafe(NdisBuffer, &Va, &BufferLength, NormalPagePriority);
            
            if (Va == NULL)
            {
                //
                // BUGBUG: what should do?
                //
            }
            else
            {
                FILTER_FREE_MEM(Va);
            }
            NdisGetNextBuffer(NdisBuffer, &NdisBuffer);
        }
        NextNetBuffer = NetBuffer->Next;
        if (NetBuffer != NetBufferList->FirstNetBuffer)
        {
            NdisFreeNetBuffer(NetBuffer, DispatchLevel);
        }
        NetBuffer = NextNetBuffer;
    }
    //
    // Free the NetBufferList
    //
    NdisFreeNetBufferList(NetBufferList, DispatchLevel);

    DEBUGP(DL_TRACE, ("<=== filterFreeNetBufferList.\n"));
} 

VOID
filterCompleteQueuedSend(
    IN  PMS_FILTER      pFilter,
    IN  BOOLEAN         DispatchLevel
    )
/*++
 
Routine Description:

    Complete all the queued send in the filter's local structure. Some filters, such as Passthru filters,
    may not need to queue any NetBufferList.
      
Arguments:

    FilterModuleContext: Pointer to our filter context area.
    DispatchLevel: A Boolean specifying if the caller is at DISPATCH_LEVEL        
   
Return Value:

    None

NOTE: called with SendLock held     

--*/ 
{
    PQUEUE_ENTRY        pEntry;
    PNET_BUFFER_LIST    NetBufList;
    NDIS_STATUS         Status;

    
    //
    // SendNBLQueue contains all the NetBufferLists which the filter hasn't
    // sent out 
    //

    Status = NDIS_STATUS_FAILURE;
    while (!IsQueueEmpty(&pFilter->SendNBLQueue))
    {

        pEntry = RemoveHeadQueue(&pFilter->SendNBLQueue);
        
        FILTER_RELEASE_LOCK(&pFilter->SendLock, DispatchLevel);
        
        ASSERT(pEntry);
        
        NetBufList = ENTRY_TO_NET_BUFFER_LIST(pEntry);
      
        //
        // BUGBUG: API not available
        //
        // NdisMSendNetBufferListComplete(pFilter->FilterHandle, NetBufList, Status, DispatchLevel);
        
        FILTER_ACQUIRE_LOCK(&pFilter->SendLock, DispatchLevel);
    }
    
}


VOID
filterReturnQueuedRecv(
    IN  PMS_FILTER      pFilter,
    IN  BOOLEAN         DispatchLevel
    )
/*++
 
Routine Description:

    Return all the recvs in the filter's local structure, some filters, such passthru filter,
    may not need to queue any recvs
     
Arguments:

    FilterModuleContext: Pointer to our filter context area.
    DispatchLevel: A Boolean specifying if the caller is at DISPATCH_LEVEL        
  
Return Value:

    None

NOTE: Called with RcvLock held     

--*/ 
{
    PNET_BUFFER_LIST        NetBufList = NULL;
    PNET_BUFFER_LIST        pNBL = NULL;
    PNET_BUFFER_LIST        LastNBL = NULL;
    PQUEUE_ENTRY            pEntry = NULL;
    
    while (!IsQueueEmpty(&pFilter->RcvNBLQueue))
    {
        pEntry = RemoveHeadQueue(&pFilter->RcvNBLQueue);
        
        
        ASSERT(pEntry);
        //
        // Figure out a STATUS for packets
        // 
        pNBL = ENTRY_TO_NET_BUFFER_LIST(pEntry);
        if (NetBufList == NULL)
        {
            NetBufList = pNBL;
        }
        else
        {
            LastNBL->Next = pNBL;
        }
        LastNBL = pNBL;
    }
    

    if (NetBufList != NULL)
    {
        FILTER_RELEASE_LOCK(&pFilter->RcvLock, DispatchLevel);

        NdisFReturnNetBufferLists(pFilter->FilterHandle, NetBufList, FALSE);

        FILTER_ACQUIRE_LOCK(&pFilter->RcvLock, DispatchLevel);
    }
}

NDIS_STATUS
filterDoInternalRequest(
    IN PMS_FILTER                   FilterModuleContext,
    IN NDIS_REQUEST_TYPE            RequestType,
    IN NDIS_OID                     Oid,
    IN PVOID                        InformationBuffer,
    IN ULONG                        InformationBufferLength,
    IN ULONG                        OutputBufferLength, OPTIONAL
    IN ULONG                        MethodId, OPTIONAL
    OUT PULONG                      pBytesProcessed
    )
/*++

Routine Description:

    Utility routine that forms and sends an NDIS_OID_REQUEST to the
    miniport, waits for it to complete, and returns status
    to the caller.

    NOTE: this assumes that the calling routine ensures validity
    of the filter handle until this returns.

Arguments:

    FilterModuleContext - pointer to our filter module context
    RequestType - NdisRequest[Set|Query|method]Information
    Oid - the object being set/queried
    InformationBuffer - data for the request
    InformationBufferLength - length of the above
    OutputBufferLength  - valid only for method request
    MethodId - valid only for method request
    pBytesProcessed - place to return bytes read/written

Return Value:

    Status of the set/query request

--*/
{
    FILTER_REQUEST              FilterRequest;
    PNDIS_OID_REQUEST           NdisRequest = &FilterRequest.Request;
    NDIS_STATUS                 Status;


    NdisZeroMemory(NdisRequest, sizeof(NDIS_OID_REQUEST));

    NdisInitializeEvent(&FilterRequest.ReqEvent);
    
    NdisRequest->Header.Type = NDIS_OBJECT_TYPE_OID_REQUEST;
    NdisRequest->Header.Revision = NDIS_OID_REQUEST_REVISION_1;
    NdisRequest->Header.Size = sizeof(NDIS_OID_REQUEST);
    NdisRequest->RequestType = RequestType;

    switch (RequestType)
    {
        case NdisRequestQueryInformation:
             NdisRequest->DATA.QUERY_INFORMATION.Oid = Oid;
             NdisRequest->DATA.QUERY_INFORMATION.InformationBuffer =
                                    InformationBuffer;
             NdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength =
                                    InformationBufferLength;
            break;

        case NdisRequestSetInformation:
             NdisRequest->DATA.SET_INFORMATION.Oid = Oid;
             NdisRequest->DATA.SET_INFORMATION.InformationBuffer =
                                    InformationBuffer;
             NdisRequest->DATA.SET_INFORMATION.InformationBufferLength =
                                    InformationBufferLength;
            break;

        case NdisRequestMethod:
             NdisRequest->DATA.METHOD_INFORMATION.Oid = Oid;
             NdisRequest->DATA.METHOD_INFORMATION.MethodId = MethodId;
             NdisRequest->DATA.METHOD_INFORMATION.InformationBuffer =
                                    InformationBuffer;
             NdisRequest->DATA.METHOD_INFORMATION.InputBufferLength =
                                    InformationBufferLength;
             NdisRequest->DATA.METHOD_INFORMATION.OutputBufferLength = OutputBufferLength;
             break;
             
                

        default:
            FILTER_ASSERT(FALSE);
            break;
    }

    Status = NdisFRequest(FilterModuleContext->FilterHandle,
                            NdisRequest);
    

    if (Status == NDIS_STATUS_PENDING)
    {
        NdisWaitEvent(&FilterRequest.ReqEvent, 0);
        Status = FilterRequest.Status;
    }

    if (Status == NDIS_STATUS_SUCCESS)
    {
        if (RequestType == NdisRequestSetInformation)
        {
            *pBytesProcessed = NdisRequest->DATA.SET_INFORMATION.BytesRead;
        }

        if (RequestType == NdisRequestQueryInformation)
        {
            *pBytesProcessed = NdisRequest->DATA.QUERY_INFORMATION.BytesWritten;
        }

        if (RequestType == NdisRequestMethod)
        {
            *pBytesProcessed = NdisRequest->DATA.METHOD_INFORMATION.BytesWritten;
        }
        
        //
        // The driver below should set the correct value to BytesWritten 
        // or BytesRead. But now, we just truncate the value to InformationBufferLength
        //
        if (RequestType == NdisRequestMethod)
        {
            if (*pBytesProcessed > OutputBufferLength)
            {
                *pBytesProcessed = OutputBufferLength;
            }
        }
        else
        {
            
            if (*pBytesProcessed > InformationBufferLength)
            {
                *pBytesProcessed = InformationBufferLength;
            }
        }
    }

    return (Status);
}

VOID
filterInternalRequestComplete(
    IN NDIS_HANDLE                  FilterModuleContext,
    IN PNDIS_OID_REQUEST            NdisRequest,
    IN NDIS_STATUS                  Status
    )
/*++

Routine Description:

    NDIS entry point indicating completion of a pended NDIS_OID_REQUEST.

Arguments:

    FilterModuleContext - pointer to filter module context
    NdisRequest - pointer to NDIS request
    Status - status of request completion

Return Value:

    None

--*/
{
    PFILTER_REQUEST              FilterRequest;


    UNREFERENCED_PARAMETER(FilterModuleContext);
 
    //
    //  Get at the request context.
    //
    FilterRequest = CONTAINING_RECORD(NdisRequest, FILTER_REQUEST, Request);

    //
    //  Save away the completion status.
    //
    FilterRequest->Status = Status;

    //
    //  Wake up the thread blocked for this request to complete.
    //
    NdisSetEvent(&FilterRequest->ReqEvent);
}


