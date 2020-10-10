/*++

Copyright(c) 1992-2000  Microsoft Corporation

Module Name:

    protocol.c

Abstract:

    NDIS Protocol Entry points and utility functions for the NDIS
    MUX Intermediate Miniport sample.

    The protocol edge binds to Ethernet (NdisMedium802_3) adapters,
    and initiates creation of zero or more Virtual Ethernet LAN (VELAN)
    miniport instances by calling NdisIMInitializeDeviceInstanceEx once
    for each VELAN configured over a lower binding.

Environment:

    Kernel mode.

Revision History:


--*/


#include "precomp.h"
#include "offload.h"
#pragma hdrstop


#define MODULE_NUMBER           MODULE_PROT


NDIS_STATUS
PtBindAdapter(
    IN  NDIS_HANDLE             ProtocolDriverContext,
    IN  NDIS_HANDLE             BindContext,
    IN  PNDIS_BIND_PARAMETERS   BindParameters
    )
/*++

Routine Description:

    Called by NDIS to bind to a miniport below. This routine
    creates a binding by calling NdisOpenAdapter, and then
    initiates creation of all configured VELANs on this binding.

Arguments:

Return Value:

    *Status is set to NDIS_STATUS_SUCCESS if no failure occurred
    while handling this call, otherwise an error code.

--*/
{
    PADAPT                            pAdapt = NULL;
    NDIS_STATUS                       OpenErrorStatus;
    UINT                              MediumIndex;
    PNDIS_STRING                      pConfigString;
    ULONG                             Length;
    NDIS_STATUS                       Status = NDIS_STATUS_SUCCESS;
    NDIS_OPEN_PARAMETERS              OpenParameters;

    UNREFERENCED_PARAMETER(ProtocolDriverContext);
    
    pConfigString = (PNDIS_STRING)BindParameters->ProtocolSection;
    
    DBGPRINT(MUX_LOUD, ("==> Protocol BindAdapter: %ws\n", pConfigString->Buffer));
   
    do
    {

        //
        // Allocate memory for Adapter struct plus the config
        // string with two extra WCHARs for NULL termination.
        //
        Length = sizeof(ADAPT) + 
                    pConfigString->MaximumLength + sizeof(WCHAR);
        
        NdisAllocateMemoryWithTag(&pAdapt, Length , TAG);

        if (pAdapt == NULL)
        {
             Status = NDIS_STATUS_RESOURCES;
             break;
        }
        
        //
        // Initialize the adapter structure
        //
        NdisZeroMemory(pAdapt, sizeof(ADAPT));        

        (VOID)PtReferenceAdapter(pAdapt, (PUCHAR)"openadapter");        
        

        //
        //  Copy in the Config string - we will use this to open the
        //  registry section for this adapter at a later point.
        //
        pAdapt->ConfigString.MaximumLength = pConfigString->MaximumLength;
        pAdapt->ConfigString.Length = pConfigString->Length;
        pAdapt->ConfigString.Buffer = (PWCHAR)((PUCHAR)pAdapt + 
                            sizeof(ADAPT));

        NdisMoveMemory(pAdapt->ConfigString.Buffer,
                       pConfigString->Buffer,
                       pConfigString->Length);
        pAdapt->ConfigString.Buffer[pConfigString->Length/sizeof(WCHAR)] = 
                                    ((WCHAR)0);

        NdisInitializeEvent(&pAdapt->Event);
        NdisInitializeListHead(&pAdapt->VElanList);

        pAdapt->PtDevicePowerState = NdisDeviceStateD0;

        MUX_INIT_ADAPT_RW_LOCK(pAdapt);

        //
        // Now open the adapter below and complete the initialization
        //

        NdisZeroMemory(&OpenParameters,sizeof(NDIS_OPEN_PARAMETERS));

        OpenParameters.Header.Type = NDIS_OBJECT_TYPE_OPEN_PARAMETERS;
        OpenParameters.Header.Revision = NDIS_OPEN_PARAMETERS_REVISION_1;
        OpenParameters.Header.Size = sizeof(NDIS_OPEN_PARAMETERS);
        OpenParameters.AdapterName = BindParameters->AdapterName;
        OpenParameters.MediumArray = MediumArray;
        OpenParameters.MediumArraySize = sizeof(MediumArray) / sizeof(NDIS_MEDIUM);
        OpenParameters.SelectedMediumIndex = &MediumIndex;

        OpenParameters.FrameTypeArray = NULL;
        OpenParameters.FrameTypeArraySize = 0;

        Status = NdisOpenAdapterEx(ProtHandle,
                                   pAdapt,
                                   &OpenParameters,
                                   &pAdapt->BindingHandle);

        if (Status == NDIS_STATUS_PENDING)
        {
              NdisWaitEvent(&pAdapt->Event, 0);
              Status = pAdapt->Status;
        }

        if (Status != NDIS_STATUS_SUCCESS)
        {
              pAdapt->BindingHandle = NULL;
              break;
        }
       
        pAdapt->Medium = MediumArray[MediumIndex];

        //
        // Add this adapter to the global AdapterList
        //
        MUX_ACQUIRE_MUTEX(&GlobalMutex);

        InsertTailList(&AdapterList, &pAdapt->Link);

        MUX_RELEASE_MUTEX(&GlobalMutex);

        //
        // Copy all the relevant information about the Adapter into 
        // the local structure
        //
        pAdapt->BindParameters = *BindParameters;

        if (BindParameters->RcvScaleCapabilities)
        {
            pAdapt->RcvScaleCapabilities = (*BindParameters->RcvScaleCapabilities);
            pAdapt->BindParameters.RcvScaleCapabilities = &pAdapt->RcvScaleCapabilities;
        }
        
        pAdapt->PowerManagementCapabilities = (*BindParameters->PowerManagementCapabilities); 

        
        PtPostProcessPnPCapabilities(&pAdapt->PowerManagementCapabilities,
                                     sizeof(pAdapt->PowerManagementCapabilities));

        //
        // Zeroing out fields that are not needed by the MUX driver
        //
        pAdapt->BindParameters.ProtocolSection= NULL;
        pAdapt->BindParameters.AdapterName = NULL;
        pAdapt->BindParameters.PhysicalDeviceObject = NULL;
        

        //
        // Start all VELANS configured on this adapter.
        //
        Status = PtBootStrapVElans(pAdapt);

#ifdef OFFLOAD_SUPPORT

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        Status = PtSetTcpOffloadClientHandlers(pAdapt->BindingHandle);
#endif       
    } while(FALSE);

    if (Status != NDIS_STATUS_SUCCESS)
    {
        
        if (pAdapt != NULL)
        {
            //
            // For some reason, the driver cannot create velan for the binding
            //
            if (pAdapt->BindingHandle != NULL)
            {
                NDIS_STATUS LocalStatus;
                //
                // Close the binding the driver opened above
                // 
                PtCloseAdapter(pAdapt);

                MUX_ACQUIRE_MUTEX(&GlobalMutex);

                RemoveEntryList(&pAdapt->Link);

                MUX_RELEASE_MUTEX(&GlobalMutex);
            }
            PtDereferenceAdapter(pAdapt, (PUCHAR)"openadapter");
            pAdapt = NULL;
        }
    }


    DBGPRINT(MUX_INFO, ("<== Protocol BindAdapter: pAdapt %p, Status %x\n", pAdapt, Status));

    return Status;
}


VOID
PtOpenAdapterComplete(
    IN  NDIS_HANDLE             ProtocolBindingContext,
    IN  NDIS_STATUS             Status
    )
/*++

Routine Description:

    Completion routine for NdisOpenAdapter issued from within the 
    PtBindAdapter. Simply unblock the caller.

Arguments:

    ProtocolBindingContext    Pointer to the adapter
    Status                    Status of the NdisOpenAdapter call
    OpenErrorStatus            Secondary status(ignored by us).

Return Value:

    None

--*/
{
    PADAPT      pAdapt =(PADAPT)ProtocolBindingContext;

    DBGPRINT(MUX_LOUD, ("==> PtOpenAdapterComplete: Adapt %p, Status %x\n", pAdapt, Status));
    pAdapt->Status = Status;
    NdisSetEvent(&pAdapt->Event);
}


VOID
PtQueryAdapterInfo(
    IN  PADAPT                  pAdapt
    )
/*++

Routine Description:

    Query the adapter we are bound to for some standard OID values
    which we cache.

Arguments:

    pAdapt              Pointer to the adapter


Return Value:

    None
--*/
{
    //Insert code here to query Adapter info if needed

    UNREFERENCED_PARAMETER(pAdapt);
    
}


VOID
PtRequestAdapterSync(
    IN  PADAPT                      pAdapt,
    IN  NDIS_REQUEST_TYPE           RequestType,
    IN  NDIS_OID                    Oid,
    IN  PVOID                       InformationBuffer,
    IN  ULONG                       InformationBufferLength
    )
/*++

Routine Description:

    Utility routine to query the adapter for a single OID value. This
    blocks for the query to complete.

Arguments:

    pAdapt                      Pointer to the adapter
    Oid                         OID to query for
    InformationBuffer           Place for the result
    InformationBufferLength     Length of the above

Return Value:

    None.

--*/
{
    PMUX_NDIS_REQUEST       pMuxNdisRequest = NULL;
    NDIS_STATUS             Status;

    do
    {
        NdisAllocateMemoryWithTag(&pMuxNdisRequest, sizeof(MUX_NDIS_REQUEST), TAG);
        if (pMuxNdisRequest == NULL)
        {
            break;
        }

        pMuxNdisRequest->pVElan = NULL; // internal request

        //
        // Set up completion routine.
        //
        pMuxNdisRequest->pCallback = PtCompleteBlockingRequest;
        NdisInitializeEvent(&pMuxNdisRequest->Event);

        pMuxNdisRequest->Request.RequestType = RequestType;
        pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.Oid = Oid;
        pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.InformationBuffer =
                            InformationBuffer;
        pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.InformationBufferLength =
                                                InformationBufferLength;

        Status = NdisRequestEx(pAdapt->BindingHandle,
                            &pMuxNdisRequest->Request);
        
        if (Status == NDIS_STATUS_PENDING)
        {
            NdisWaitEvent(&pMuxNdisRequest->Event, 0);
            Status = pMuxNdisRequest->Status;
        }
    }
    while (FALSE);

    if (NULL != pMuxNdisRequest)
    {
        NdisFreeMemory(pMuxNdisRequest, sizeof(MUX_NDIS_REQUEST), 0);
    }
}



VOID
PtRequestAdapterAsync(
    IN  PADAPT                      pAdapt,
    IN  NDIS_REQUEST_TYPE           RequestType,
    IN  NDIS_OID                    Oid,
    IN  PVOID                       InformationBuffer,
    IN  ULONG                       InformationBufferLength,
    IN  PMUX_REQ_COMPLETE_HANDLER   pCallback
    )
/*++

Routine Description:

    Utility routine to query the adapter for a single OID value.
    This completes asynchronously, i.e. the calling thread is
    not blocked until the request completes.

Arguments:

    pAdapt                      Pointer to the adapter
    RequestType                 NDIS request type
    Oid                         OID to set/query
    InformationBuffer           Input/output buffer
    InformationBufferLength     Length of the above
    pCallback                   Function to call on request completion

Return Value:

    None.

--*/
{
    PMUX_NDIS_REQUEST       pMuxNdisRequest = NULL;
    PNDIS_REQUEST_EX        pNdisRequest;
    NDIS_STATUS             Status;

    do
    {
        NdisAllocateMemoryWithTag(&pMuxNdisRequest, sizeof(MUX_NDIS_REQUEST), TAG);
        if (pMuxNdisRequest == NULL)
        {
            break;
        }

        pMuxNdisRequest->pVElan = NULL; // internal request

        //
        // Set up completion routine.
        //
        pMuxNdisRequest->pCallback = pCallback;

        pNdisRequest = &pMuxNdisRequest->Request;

        pNdisRequest->RequestType = RequestType;

        switch (RequestType)
        {
            case NdisRequestQueryInformation:
                pNdisRequest->DATA.QUERY_INFORMATION.Oid = Oid;
                pNdisRequest->DATA.QUERY_INFORMATION.InformationBuffer =
                                    InformationBuffer;
                pNdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength =
                                    InformationBufferLength;
        
                break;

            case NdisRequestSetInformation:
                pNdisRequest->DATA.SET_INFORMATION.Oid = Oid;
                pNdisRequest->DATA.SET_INFORMATION.InformationBuffer =
                                    InformationBuffer;
                pNdisRequest->DATA.SET_INFORMATION.InformationBufferLength =
                                    InformationBufferLength;
        
                break;
            
            default:
                ASSERT(FALSE);
                break;
        }

        Status = NdisRequestEx(
                    pAdapt->BindingHandle,
                    pNdisRequest);
        
        if (Status != NDIS_STATUS_PENDING)
        {
            PtRequestComplete(
                (NDIS_HANDLE)pAdapt,
                pNdisRequest,
                Status);
        }
    }
    while (FALSE);
}



VOID
PtCloseAdapter(
    IN PADAPT pAdapt
    )
/*++

Routine Description:

    Call either when the protocol is unbinding or the miniport is halting to set 
    the packet filters back to zero and multicast filter back to zero

Arguments:

    PADAPT Adapter below
Return Value:
    None

--*/

{
    ULONG                   PacketFilter = 0;
    PVOID                   MCastBuf = NULL;
    ULONG                   MCastBufSize = 0;

    ASSERT (KeGetCurrentIrql() == PASSIVE_LEVEL);

    //
    // Clear out the packet filter and multicast list before unbinding
    // from the adapter below is required for NDIS 6.0 protocols
    //
    
    PtRequestAdapterSync(pAdapt,
                            NdisRequestSetInformation, 
                            OID_GEN_CURRENT_PACKET_FILTER,
                            &PacketFilter, 
                            sizeof(PacketFilter));

    PtRequestAdapterSync(pAdapt,
                            NdisRequestSetInformation, 
                            OID_802_3_MULTICAST_LIST,
                            MCastBuf, 
                            MCastBufSize);

    //
    // Now Close the binding with the adapter below
    //
    
    NdisResetEvent(&pAdapt->Event);

    NdisCloseAdapterEx(pAdapt->BindingHandle);

    //
    // Wait for it to complete.
    //
    NdisWaitEvent(&pAdapt->Event, 0);

    pAdapt->BindingHandle = NULL;
}

NDIS_STATUS
PtUnbindAdapter(
    IN  NDIS_HANDLE             UnbindContext,
    IN  NDIS_HANDLE             ProtocolBindingContext
    )
/*++

Routine Description:

    Called by NDIS when we are required to unbind to the adapter below.
    Go through all VELANs on the adapter and shut them down.

Arguments:

    Status                    Placeholder for return status
    ProtocolBindingContext    Pointer to the adapter structure
    UnbindContext             Context for NdisUnbindComplete() if this pends

Return Value:

    Status from closing the binding.

--*/
{
    PADAPT          pAdapt =(PADAPT)ProtocolBindingContext;
    PLIST_ENTRY     p;
    PVELAN          pVElan = NULL;
    LOCK_STATE      LockState;
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;

	UNREFERENCED_PARAMETER(UnbindContext);
	
    DBGPRINT(MUX_LOUD, ("==> PtUnbindAdapter: Adapt %p\n", pAdapt));

    //
    // Stop all VELANs associated with the adapter.
    // Repeatedly find the first unprocessed VELAN on
    // the adapter, mark it, and stop it.
    //
    MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);

    do
    {
        for (p = pAdapt->VElanList.Flink;
             p != &pAdapt->VElanList;
             p = p->Flink)
        {
            pVElan = CONTAINING_RECORD(p, VELAN, Link);
            if (!pVElan->DeInitializing)
            {
                pVElan->DeInitializing = TRUE;
                break;
            }
        }

        if (p != &pAdapt->VElanList)
        {
            ASSERT(pVElan == CONTAINING_RECORD(p, VELAN, Link));

            //
            // Got a VELAN to stop. Add a temp ref
            // so that the VELAN won't go away when
            // we release the ADAPT lock below.
            //
            PtReferenceVElan(pVElan, (PUCHAR)"UnbindTemp");

            //
            // Release the read lock because we want to
            // run StopVElan at passive IRQL.
            //
            MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);
    
            PtStopVElan(pVElan);
    
            PtDereferenceVElan(pVElan, (PUCHAR)"UnbindTemp");

            MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);
        }
        else
        {
            //
            // No unmarked VELAN, so exit.
            //
            break;
        }
    }
    while (TRUE);

    //
    // Wait until all VELANs are unlinked from the adapter.
    // This is so that we don't attempt to forward down packets
    // and/or requests from VELANs after calling NdisCloseAdapter.
    //
    while (!IsListEmpty(&pAdapt->VElanList))
    {
        MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);

        DBGPRINT(MUX_INFO, ("PtUnbindAdapter: pAdapt %p, VELANlist not yet empty\n",
                    pAdapt));

        NdisMSleep(2000);

        MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);
    }

    MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);

    //
    // Close the binding to the lower adapter.
    //
    if (pAdapt->BindingHandle != NULL)
    {
        PtCloseAdapter(pAdapt);
    }
    else
    {
        //
        // Binding Handle should not be NULL.
        //
        Status = NDIS_STATUS_FAILURE;
        ASSERT(0);
    }

    //
    // Remove the adapter from the global AdapterList
    //
    
    MUX_ACQUIRE_MUTEX(&GlobalMutex);

    RemoveEntryList(&pAdapt->Link);

    MUX_RELEASE_MUTEX(&GlobalMutex);

    //
    // Free all the resources associated with this Adapter except the
    // ADAPT struct itself, because that will be freed by 
    // PtDereferenceAdapter call when the reference drops to zero. 
    // Note: Every VELAN associated with this Adapter takes a ref count
    // on it. So the adapter memory wouldn't be freed until all the VELANs
    // are shutdown. 
    //
    
    PtDereferenceAdapter(pAdapt, (PUCHAR)"Unbind");

    DBGPRINT(MUX_INFO, ("<== PtUnbindAdapter: Adapt %p, Status=%08lx", pAdapt, Status));

    return Status;
}



VOID
PtCloseAdapterComplete(
    IN    NDIS_HANDLE            ProtocolBindingContext
    )
/*++

Routine Description:

    Completion for the CloseAdapter call.

Arguments:

    ProtocolBindingContext    Pointer to the adapter structure
    Status                    Completion status

Return Value:

    None.

--*/
{
    PADAPT      pAdapt =(PADAPT)ProtocolBindingContext;

    DBGPRINT(MUX_INFO, ("==> PtCloseAdapterComplete: Adapt %p\n", 
                                pAdapt));

    NdisSetEvent(&pAdapt->Event);
}


VOID
PtRequestComplete(
    IN  NDIS_HANDLE                 ProtocolBindingContext,
    IN  PNDIS_REQUEST_EX            NdisRequest,
    IN  NDIS_STATUS                 Status
    )
/*++

Routine Description:

    Completion handler for an NDIS request sent to a lower
    miniport.

Arguments:

    ProtocolBindingContext    Pointer to the adapter structure
    NdisRequest               The completed request
    Status                    Completion status

Return Value:

    None

--*/
{
    PADAPT              pAdapt = (PADAPT)ProtocolBindingContext;
    PMUX_NDIS_REQUEST   pMuxNdisRequest;

    pMuxNdisRequest = CONTAINING_RECORD(NdisRequest, MUX_NDIS_REQUEST, Request);

    ASSERT(pMuxNdisRequest->pCallback != NULL);

    //
    // Completion is handled by the callback routine:
    //
    (*pMuxNdisRequest->pCallback)(pAdapt, 
                                  pMuxNdisRequest,
                                  Status);

}


VOID
PtCompleteForwardedRequest(
    IN PADAPT                       pAdapt,
    IN PMUX_NDIS_REQUEST            pMuxNdisRequest,
    IN NDIS_STATUS                  Status
    )
/*++

Routine Description:

    Handle completion of an NDIS request that was originally
    submitted to our VELAN miniport and was forwarded down
    to the lower binding.

    We do some postprocessing, to cache the results of
    certain queries.

Arguments:

    pAdapt  - Adapter on which the request was forwarded
    pMuxNdisRequest - super-struct for request
    Status - request completion status

Return Value:

    None

--*/
{
    PVELAN              pVElan = NULL;
    PNDIS_REQUEST_EX    pNdisRequest = &pMuxNdisRequest->Request;
    NDIS_OID            Oid = pNdisRequest->DATA.SET_INFORMATION.Oid;
    PNDIS_OID_REQUEST   OrigRequest = NULL;
    BOOLEAN             fCompleteRequest = FALSE;

    UNREFERENCED_PARAMETER(pAdapt);
    
    //
    // Get the originating VELAN. The VELAN will not be dereferenced
    // away until the pended request is completed.
    //
    pVElan = pMuxNdisRequest->pVElan;

    ASSERT(pVElan != NULL);
    ASSERT(pMuxNdisRequest == &pVElan->Request);
    
    if (Status != NDIS_STATUS_SUCCESS)
    {
        DBGPRINT(MUX_WARN, ("PtCompleteForwardedReq: pVElan %p, OID %x, Status %x\n", 
                    pVElan,
                    pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.Oid,
                    Status));
    }

    NdisAcquireSpinLock(&pVElan->Lock);

    pMuxNdisRequest->Refcount --;
    if (pMuxNdisRequest->Refcount == 0)
    {
        fCompleteRequest = TRUE;
        OrigRequest = pMuxNdisRequest->OrigRequest;
        pMuxNdisRequest->OrigRequest = NULL;
    }
    

    NdisReleaseSpinLock(&pVElan->Lock);    

    if (fCompleteRequest == FALSE)
    {
        return;
    }

    //
    // Complete the original request.
    //
    switch (pNdisRequest->RequestType)
    {
        case NdisRequestQueryInformation:
        case NdisRequestQueryStatistics:

            OrigRequest->DATA.QUERY_INFORMATION.BytesWritten = 
                    pNdisRequest->DATA.QUERY_INFORMATION.BytesWritten;
            OrigRequest->DATA.QUERY_INFORMATION.BytesNeeded = 
                    pNdisRequest->DATA.QUERY_INFORMATION.BytesNeeded;

            //
            // Before completing the request, do any necessary
            // post-processing.
            //
            Oid = pNdisRequest->DATA.QUERY_INFORMATION.Oid;
            if (Status == NDIS_STATUS_SUCCESS)
            {
                if (Oid == OID_GEN_LINK_SPEED)
                {
                    NdisMoveMemory (&pVElan->LinkSpeed,
                                    pNdisRequest->DATA.QUERY_INFORMATION.InformationBuffer,
                                    sizeof(ULONG));
                }
                else if (Oid == OID_PNP_CAPABILITIES)
                {
                    PtPostProcessPnPCapabilities(pNdisRequest->DATA.QUERY_INFORMATION.InformationBuffer,
                                                 pNdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength);
                }
            }

            break;

        case NdisRequestSetInformation:

            OrigRequest->DATA.SET_INFORMATION.BytesRead=
                    pNdisRequest->DATA.SET_INFORMATION.BytesRead;
            OrigRequest->DATA.QUERY_INFORMATION.BytesNeeded=
                    pNdisRequest->DATA.SET_INFORMATION.BytesNeeded;

            //
            // Before completing the request, cache relevant information
            // in our structure.
            //
            if (Status == NDIS_STATUS_SUCCESS)
            {
                Oid = pNdisRequest->DATA.SET_INFORMATION.Oid;
                switch (Oid)
                {
                    case OID_GEN_CURRENT_LOOKAHEAD:
                        NdisMoveMemory(&pVElan->LookAhead,
                                 pNdisRequest->DATA.QUERY_INFORMATION.InformationBuffer,
                                 sizeof(ULONG));
                        break;

                    default:
                        break;
                }
            }

            break;

        default:
            ASSERT(FALSE);
            break;
    }

    NdisMRequestComplete(pVElan->MiniportAdapterHandle,OrigRequest,Status);

    MUX_DECR_PENDING_SENDS(pVElan);

}



VOID
PtPostProcessPnPCapabilities(
    IN PVOID                    InformationBuffer,
    IN ULONG                    InformationBufferLength
    )
/*++

Routine Description:

    Postprocess a successfully completed query for OID_PNP_CAPABILITIES.
    We modify the returned information slightly before completing
    it to the VELAN above.

Arguments:

    InformationBuffer - points to buffer for the OID
    InformationBufferLength - byte length of the above.

Return Value:

    None

--*/
{
    PNDIS_PNP_CAPABILITIES          pPNPCapabilities;
    PNDIS_PM_WAKE_UP_CAPABILITIES   pPMstruct;

    if (InformationBufferLength >= sizeof(NDIS_PNP_CAPABILITIES))
    {
        pPNPCapabilities = (PNDIS_PNP_CAPABILITIES)InformationBuffer;

        //
        // The following fields must be overwritten by an IM driver.
        //
        pPMstruct= &pPNPCapabilities->WakeUpCapabilities;
        pPMstruct->MinMagicPacketWakeUp = NdisDeviceStateUnspecified;
        pPMstruct->MinPatternWakeUp = NdisDeviceStateUnspecified;
        pPMstruct->MinLinkChangeWakeUp = NdisDeviceStateUnspecified;
    }
}

VOID
PtCompleteBlockingRequest(
    IN PADAPT                   pAdapt,
    IN PMUX_NDIS_REQUEST        pMuxNdisRequest,
    IN NDIS_STATUS              Status
    )
/*++

Routine Description:

    Handle completion of an NDIS request that was originated
    by this driver and the calling thread is blocked waiting
    for completion.

Arguments:

    pAdapt  - Adapter on which the request was forwarded
    pMuxNdisRequest - super-struct for request
    Status - request completion status

Return Value:

    None

--*/
{
	UNREFERENCED_PARAMETER(pAdapt);
	
    pMuxNdisRequest->Status = Status;

    //
    // The request was originated from this driver. Wake up the
    // thread blocked for its completion.
    //
    pMuxNdisRequest->Status = Status;
    NdisSetEvent(&pMuxNdisRequest->Event);
}


VOID
PtDiscardCompletedRequest(
    IN PADAPT                   pAdapt,
    IN PMUX_NDIS_REQUEST        pMuxNdisRequest,
    IN NDIS_STATUS              Status
    )
/*++

Routine Description:

    Handle completion of an NDIS request that was originated
    by this driver - the request is to be discarded.

Arguments:

    pAdapt  - Adapter on which the request was forwarded
    pMuxNdisRequest - super-struct for request
    Status - request completion status

Return Value:

    None

--*/
{
    UNREFERENCED_PARAMETER(pAdapt);
    UNREFERENCED_PARAMETER(Status);

    NdisFreeMemory(pMuxNdisRequest, sizeof(MUX_NDIS_REQUEST), 0);
}


VOID
PtStatus(
    IN  NDIS_HANDLE                 ProtocolBindingContext,
    IN  PNDIS_STATUS_INDICATION     StatusIndication
    )
/*++

Routine Description:

    Handle a status indication on the lower binding (ADAPT).
    If this is a media status indication, we also pass this
    on to all associated VELANs.

Arguments:

    ProtocolBindingContext      Pointer to the adapter structure
    GeneralStatus               Status code
    StatusBuffer                Status buffer
    StatusBufferSize            Size of the status buffer

Return Value:

    None

--*/
{
    PADAPT      pAdapt = (PADAPT)ProtocolBindingContext;
    PLIST_ENTRY p;
    PVELAN      pVElan;
    LOCK_STATE  LockState;
    NDIS_STATUS GeneralStatus = StatusIndication->StatusCode;
    

    DBGPRINT(MUX_LOUD, ("PtStatus: Adapt %p, Status %x\n", pAdapt, GeneralStatus));

    do
    {
        //
        // Ignore status indications that we aren't going
        // to pass up.
        //
        if ((GeneralStatus != NDIS_STATUS_MEDIA_CONNECT) &&
            (GeneralStatus != NDIS_STATUS_MEDIA_DISCONNECT) &&
            (GeneralStatus != NDIS_STATUS_OFFLOAD_PAUSE) &&
            (GeneralStatus != NDIS_STATUS_OFFLOAD_RESUME) &&
            (GeneralStatus != NDIS_STATUS_UPLOAD_ALL))
        {
            break;
        }
        MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);

        for (p = pAdapt->VElanList.Flink;
             p != &pAdapt->VElanList;
             p = p->Flink)
        {
            
            pVElan = CONTAINING_RECORD(p, VELAN, Link);

            MUX_INCR_PENDING_RECEIVES(pVElan);

            //
            // Should the indication be sent on this VELAN?
            //
            if ((pVElan->MiniportInitPending) ||
                (pVElan->MiniportHalting) ||
                (pVElan->MiniportAdapterHandle == NULL) ||   
                MUX_IS_LOW_POWER_STATE(pVElan->MPDevicePowerState))
            {
                MUX_DECR_PENDING_RECEIVES(pVElan);
                if (MUX_IS_LOW_POWER_STATE(pVElan->MPDevicePowerState))
                {
                    //
                    // Keep track of the lastest status to indicated when VELAN power is on
                    // 
                    ASSERT((GeneralStatus == NDIS_STATUS_MEDIA_CONNECT) || (GeneralStatus == NDIS_STATUS_MEDIA_DISCONNECT));
                    pVElan->LatestUnIndicateStatus = GeneralStatus;
                }
                
                continue;
            }

            //
            // Save the last indicated status when 
            pVElan->LastIndicatedStatus = GeneralStatus;

            NdisMIndicateStatusEx(pVElan->MiniportAdapterHandle, StatusIndication);
            
            //
            // Mark this so that we forward a status complete
            // indication as well.
            //
            pVElan->IndicateStatusComplete = TRUE;

            MUX_DECR_PENDING_RECEIVES(pVElan);
        }

        MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);
    }
    while (FALSE);

}


BOOLEAN
PtMulticastMatch(
    IN PVELAN                       pVElan,
    IN PUCHAR                       pDstMac
    )
/*++

Routine Description:

    Check if the given multicast destination MAC address matches
    any of the multicast address entries set on the VELAN.

    NOTE: the caller is assumed to hold a READ/WRITE lock
    to the parent ADAPT structure. This is so that the multicast
    list on the VELAN is invariant for the duration of this call.

Arguments:

    pVElan  - VELAN to look in
    pDstMac - Destination MAC address to compare

Return Value:

    TRUE iff the address matches an entry in the VELAN

--*/
{
    ULONG           i;
    UINT            AddrCompareResult;

    for (i = 0; i < pVElan->McastAddrCount; i++)
    {
        ETH_COMPARE_NETWORK_ADDRESSES_EQ(pVElan->McastAddrs[i],
                                         pDstMac,
                                         &AddrCompareResult);
        
        if (AddrCompareResult == 0)
        {
            break;
        }
    }

    return (i != pVElan->McastAddrCount);
}


BOOLEAN
PtMatchPacketToVElan(
    IN PVELAN                       pVElan,
    IN PUCHAR                       pDstMac,
    IN BOOLEAN                      bIsMulticast,
    IN BOOLEAN                      bIsBroadcast
    )
/*++

Routine Description:

    Check if the destination address of a received packet
    matches the receive criteria on the specified VELAN.

    NOTE: the caller is assumed to hold a READ/WRITE lock
    to the parent ADAPT structure.

Arguments:

    pVElan  - VELAN to check on
    pDstMac - Destination MAC address in received packet
    bIsMulticast - is this a multicast address
    bIsBroadcast - is this a broadcast address

Return Value:

    TRUE iff this packet should be received on the VELAN

--*/
{
    UINT            AddrCompareResult;
    ULONG           PacketFilter;
    BOOLEAN         bPacketMatch;

    PacketFilter = pVElan->PacketFilter;

    //
    // Handle the directed packet case first.
    //
    if (!bIsMulticast)
    {
        //
        // If the VELAN is not in promisc. mode, check if
        // the destination MAC address matches the local
        // address.
        //
        if ((PacketFilter & NDIS_PACKET_TYPE_PROMISCUOUS) == 0)
        {
            ETH_COMPARE_NETWORK_ADDRESSES_EQ(pVElan->CurrentAddress,
                                             pDstMac,
                                             &AddrCompareResult);

            bPacketMatch = ((AddrCompareResult == 0) &&
                           ((PacketFilter & NDIS_PACKET_TYPE_DIRECTED) != 0));
        }
        else
        {
            bPacketMatch = TRUE;
        }
     }
     else
     {
        //
        // Multicast or broadcast packet.
        //

        //
        // Indicate if the filter is set to promisc mode ...
        //
        if ((PacketFilter & NDIS_PACKET_TYPE_PROMISCUOUS)
                ||

            //
            // or if this is a broadcast packet and the filter
            // is set to receive all broadcast packets...
            //
            (bIsBroadcast &&
             (PacketFilter & NDIS_PACKET_TYPE_BROADCAST))
                ||

            //
            // or if this is a multicast packet, and the filter is
            // either set to receive all multicast packets, or
            // set to receive specific multicast packets. In the
            // latter case, indicate receive only if the destn
            // MAC address is present in the list of multicast
            // addresses set on the VELAN.
            //
            (!bIsBroadcast &&
             ((PacketFilter & NDIS_PACKET_TYPE_ALL_MULTICAST) ||
              ((PacketFilter & NDIS_PACKET_TYPE_MULTICAST) &&
               PtMulticastMatch(pVElan, pDstMac))))
           )
        {
            bPacketMatch = TRUE;
        }
        else
        {
            //
            // No protocols above are interested in this
            // multicast/broadcast packet.
            //
            bPacketMatch = FALSE;
        }
    }

    return (bPacketMatch);
}


NDIS_STATUS
PtPnPNetEventSetPower(
    IN PADAPT                   pAdapt,
    IN PNET_PNP_EVENT           pNetPnPEvent
    )
/*++
Routine Description:

    This is a notification to our protocol edge of the power state
    of the lower miniport. If it is going to a low-power state, we must
    wait here for all outstanding sends and requests to complete.

Arguments:

    pAdapt - Pointer to the adpater structure
    pNetPnPEvent - The Net Pnp Event. this contains the new device state

Return Value:

    NDIS_STATUS_SUCCESS

--*/
{
    PLIST_ENTRY                 p;
    PVELAN                      pVElan;
    LOCK_STATE                  LockState;
    NDIS_STATUS                 Status;

    //
    // Store the new power state.
    //
    
    pAdapt->PtDevicePowerState = *(PNDIS_DEVICE_POWER_STATE)pNetPnPEvent->Buffer;

    DBGPRINT(MUX_LOUD, ("PnPNetEventSetPower: Adapt %p, SetPower to %d\n",
            pAdapt, pAdapt->PtDevicePowerState));

    //
    // Check if the miniport below is going to a low power state.
    //
    if (MUX_IS_LOW_POWER_STATE(pAdapt->PtDevicePowerState))
    {
        ULONG       i;

        //
        // It is going to a low power state. Wait for outstanding
        // I/O to complete on the adapter.
        //
        for (i = 0; i < 10000; i++)
        {
            MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);

            for (p = pAdapt->VElanList.Flink;
                 p != &pAdapt->VElanList;
                 p = p->Flink)
            {
                pVElan = CONTAINING_RECORD(p, VELAN, Link);
                if ((pVElan->OutstandingSends != 0) ||
                    (pVElan->OutstandingReceives != 0))
                {
                    break;
                }
            }

            MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);

            if (p == &pAdapt->VElanList)
            {
                //
                // There are no VELANs with pending I/O.
                //
                break;
            }
            
            DBGPRINT(MUX_INFO, ("SetPower: Adapt %p, waiting for pending IO to complete\n",
                                pAdapt));

            NdisMSleep(1000);
        }

    }
    else
    {
        //
        // The device below is powered on. If we had requests
        // pending on any VELANs, send them down now.
        //
        MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);

        for (p = pAdapt->VElanList.Flink;
             p != &pAdapt->VElanList;
             p = p->Flink)
        {
            pVElan = CONTAINING_RECORD(p, VELAN, Link);

            //
            // Need to make sure other threads do not try to acquire the write lock while holding
            // the same spin lock
            //
            NdisAcquireSpinLock(&pVElan->Lock);
            if (pVElan->QueuedRequest)
            {
                pVElan->QueuedRequest = FALSE;
                NdisReleaseSpinLock(&pVElan->Lock);

                Status = NdisRequestEx(
                            pAdapt->BindingHandle,
                            &pVElan->Request.Request);
                
                if (Status != NDIS_STATUS_PENDING)
                {
                    PtRequestComplete(pAdapt,
                                      &pVElan->Request.Request,
                                      Status);
                }
            }
            else
            {
                NdisReleaseSpinLock(&pVElan->Lock);
            }
        }

        MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);
    }

    return (NDIS_STATUS_SUCCESS);
}


NDIS_STATUS
PtPNPHandler(
    IN NDIS_HANDLE              ProtocolBindingContext,
    IN PNET_PNP_EVENT           pNetPnPEvent
    )

/*++
Routine Description:

    This is called by NDIS to notify us of a PNP event related to a lower
    binding. Based on the event, this dispatches to other helper routines.

Arguments:

    ProtocolBindingContext - Pointer to our adapter structure. Can be NULL
                for "global" notifications

    pNetPnPEvent - Pointer to the PNP event to be processed.

Return Value:

    NDIS_STATUS code indicating status of event processing.

--*/
{
    PADAPT              pAdapt  =(PADAPT)ProtocolBindingContext;
    NDIS_STATUS         Status  = NDIS_STATUS_SUCCESS;
    PLIST_ENTRY         p;

    DBGPRINT(MUX_LOUD, ("PtPnPHandler: Adapt %p, NetPnPEvent %d\n", pAdapt, 
                            pNetPnPEvent->NetEvent));

    switch (pNetPnPEvent->NetEvent)
    {
        case NetEventSetPower:

            Status = PtPnPNetEventSetPower(pAdapt, pNetPnPEvent);
            break;

        case NetEventReconfigure:
            //
            // Rescan configuration and bring up any VELANs that
            // have been newly added. Make sure that the global
            // adapter list is undisturbed while we traverse it.
            //
            MUX_ACQUIRE_MUTEX(&GlobalMutex);

            for (p = AdapterList.Flink;
                 p != &AdapterList;
                 p = p->Flink)
            {
                pAdapt = CONTAINING_RECORD(p, ADAPT, Link);

                PtBootStrapVElans(pAdapt);
            }

            MUX_RELEASE_MUTEX(&GlobalMutex);
                
            Status = NDIS_STATUS_SUCCESS;
            break;

        default:
            Status = NDIS_STATUS_SUCCESS;

            break;
    }

    return Status;
}

NDIS_STATUS
PtCreateAndStartVElan(
    IN  PADAPT                      pAdapt,
    IN  PNDIS_STRING                pVElanKey
)
/*++

Routine Description:

    Create and start a VELAN with the given key name. Check if a VELAN
    with this key name already exists; if so do nothing.

    ASSUMPTION: this is called from either the BindAdapter handler for
    the underlying adapter, or from the PNP reconfig handler. Both these
    routines are protected by NDIS against pre-emption by UnbindAdapter.
    If this routine will be called from any other context, it should
    be protected against a simultaneous call to our UnbindAdapter handler.
    
Arguments:

    pAdapt        - Pointer to Adapter structure
    pVElanKey     - Points to a Unicode string naming the VELAN to create. 
    
Return Value:

    NDIS_STATUS_SUCCESS if we either found a duplicate VELAN or
    successfully initiated a new ELAN with the given key.

    NDIS_STATUS_XXX error code otherwise (failure initiating a new VELAN).

--*/
{
    NDIS_STATUS             Status;
    PVELAN                  pVElan;
    
    Status = NDIS_STATUS_SUCCESS;
    pVElan = NULL;

    DBGPRINT(MUX_LOUD, ("=> Create VElan: Adapter %p, ElanKey %ws\n", 
                            pAdapt, pVElanKey->Buffer));

    do
    {
        //
        //  Weed out duplicates.
        //
        if (pVElanKey != NULL)
        {

            pVElan = PtFindVElan(pAdapt, pVElanKey);

            if (NULL != pVElan)
            {
                //
                // Duplicate - bail out silently.
                //
                DBGPRINT(MUX_WARN, ("CreateElan: found duplicate pVElan %x\n", pVElan));

                Status = NDIS_STATUS_SUCCESS;
                pVElan = NULL;
                break;
            }
        }

        pVElan = PtAllocateAndInitializeVElan(pAdapt, pVElanKey);
        if (pVElan == NULL)
        {
            Status = NDIS_STATUS_RESOURCES;
            break;
        }
        //
        // Request NDIS to initialize the virtual miniport. Set
        // the flag below just in case an unbind occurs before
        // MiniportInitialize is called.
        //
        pVElan->MiniportInitPending = TRUE;
        NdisInitializeEvent(&pVElan->MiniportInitEvent);

        Status = NdisIMInitializeDeviceInstanceEx(DriverHandle,
                                                  &pVElan->CfgDeviceName,
                                                  pVElan);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            PtUnlinkVElanFromAdapter(pVElan);   // IMInit failed
            pVElan = NULL;
            break;
        }
    
    }
    while (FALSE);

    DBGPRINT(MUX_INFO, ("<= Create VElan: Adapter %p, VELAN %p\n", pAdapt, pVElan));

    return Status;
}


PVELAN
PtAllocateAndInitializeVElan(
    IN PADAPT                       pAdapt,
    IN PNDIS_STRING                 pVElanKey
    )
/*++

Routine Description:

    Allocates and initializes a VELAN structure. Also links it to
    the specified ADAPT.

Arguments:

    pAdapt - Adapter to link VELAN to
    pVElanKey - Key to the VELAN

Return Value:

    Pointer to VELAN structure if successful, NULL otherwise.

--*/
{
    PVELAN          pVElan;
    ULONG           Length;
    NDIS_STATUS     Status;
    LOCK_STATE      LockState;

    pVElan = NULL;
    Status = NDIS_STATUS_SUCCESS;

    do
    {
        Length = sizeof(VELAN) + pVElanKey->Length + sizeof(WCHAR);
        
        //
        // Allocate a VELAN data structure.
        //
        NdisAllocateMemoryWithTag(&pVElan, Length, TAG);
        if (pVElan == NULL)
        {
            DBGPRINT(MUX_FATAL, ("AllocateVElan: Failed to allocate %d bytes for VELAN\n",
                                 Length));
            Status = NDIS_STATUS_RESOURCES;
            break;
        }

        //
        // Initialize it.
        //
        NdisZeroMemory(pVElan, Length);
        NdisInitializeListHead(&pVElan->Link);
        
        //
        // Initialize the built-in request structure to signify
        // that it is used to forward NDIS requests.
        //
        pVElan->Request.pVElan = pVElan;
        NdisInitializeEvent(&pVElan->Request.Event);
       
        //
        // Store in the key name.
        //
        pVElan->CfgDeviceName.Length = 0;
        pVElan->CfgDeviceName.Buffer = (PWCHAR)((PUCHAR)pVElan + 
                    sizeof(VELAN));       
        pVElan->CfgDeviceName.MaximumLength = 
                pVElanKey->MaximumLength + sizeof(WCHAR);
        (VOID)NdisUpcaseUnicodeString(&pVElan->CfgDeviceName, pVElanKey);
        pVElan->CfgDeviceName.Buffer[pVElanKey->Length/sizeof(WCHAR)] =
                        ((WCHAR)0);

        // 
        // Initialize LastIndicatedStatus to media connect
        //
        pVElan->LastIndicatedStatus = NDIS_STATUS_MEDIA_CONNECT;

        //
        // Set power state of virtual miniport to D0.
        //
        pVElan->MPDevicePowerState = NdisDeviceStateD0;

        //
        // Cache the binding handle for quick reference.
        //
        pVElan->BindingHandle = pAdapt->BindingHandle;
        pVElan->pAdapt = pAdapt;

        //
        // Copy in some adapter parameters.
        //
        pVElan->LookAhead = pAdapt->BindParameters.LookaheadSize;
        pVElan->LinkSpeed = pAdapt->BindParameters.RcvLinkSpeed;
        ASSERT(pAdapt->BindParameters.MacAddressLength == 6);

        NdisMoveMemory(pVElan->PermanentAddress,
                       &pAdapt->BindParameters.CurrentMacAddress,
                       pAdapt->BindParameters.MacAddressLength);

        NdisMoveMemory(pVElan->CurrentAddress,
                       &pAdapt->BindParameters.CurrentMacAddress,
                       pAdapt->BindParameters.MacAddressLength);

        DBGPRINT(MUX_LOUD, ("Alloced VELAN %p, MAC addr %s\n",
                    pVElan, MacAddrToString(pVElan->CurrentAddress)));

        NdisAllocateSpinLock(&pVElan->Lock);

        NdisAllocateSpinLock(&pVElan->PauseLock);

#if IEEE_VLAN_SUPPORT
        //
        // Allocate lookaside list for tag headers.
        // 
        NdisInitializeNPagedLookasideList (
                &pVElan->TagLookaside,
                NULL,
                NULL,
                0,
                ETH_HEADER_SIZE + VLAN_TAG_HEADER_SIZE,
                'TxuM',
                0);
        
#endif
        //
        // Allocate a packet pool for sends.
        //
        NdisAllocatePacketPoolEx(&Status,
                                 &pVElan->SendPacketPoolHandle,
                                 MIN_PACKET_POOL_SIZE,
                                 MAX_PACKET_POOL_SIZE - MIN_PACKET_POOL_SIZE,
                                 sizeof(MUX_SEND_RSVD));

        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MUX_FATAL, ("PtAllocateVElan: failed to allocate send packet pool\n"));
            break;
        }

        //
        // NOTE: this sample driver does not -originate- packets in the
        // send or receive directions. If the driver must originate packets,
        // here is a good place to allocate NDIS buffer pool(s) for
        // this purpose.
        //
#if IEEE_VLAN_SUPPORT
        //
        // Allocate a buffer pool for tag headers.
        //
        NdisAllocateBufferPool (&Status,
                                &pVElan->BufferPoolHandle,
                                MIN_PACKET_POOL_SIZE);

        ASSERT(Status == NDIS_STATUS_SUCCESS);
        
#endif
        
        //
        // Allocate a packet pool for receives.
        //
        NdisAllocatePacketPoolEx(&Status,
                                 &pVElan->RecvPacketPoolHandle,
                                 MIN_PACKET_POOL_SIZE,
                                 MAX_PACKET_POOL_SIZE - MIN_PACKET_POOL_SIZE,
                                 PROTOCOL_RESERVED_SIZE_IN_PACKET);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MUX_FATAL, ("PtAllocateVElan: failed to allocate receive packet pool\n"));
            break;
        }

        //
        // Finally link this VELAN to the Adapter's VELAN list. 
        //
        PtReferenceVElan(pVElan, (PUCHAR)"adapter");        

        MUX_ACQUIRE_ADAPT_WRITE_LOCK(pAdapt, &LockState);

        PtReferenceAdapter(pAdapt, (PUCHAR)"VElan");
        InsertTailList(&pAdapt->VElanList, &pVElan->Link);

        pAdapt->VElanCount++;
        pVElan->VElanNumber = NdisInterlockedIncrement((PLONG)&NextVElanNumber);

        MUX_RELEASE_ADAPT_WRITE_LOCK(pAdapt, &LockState);
    }
    while (FALSE);

    if (Status != NDIS_STATUS_SUCCESS)
    {
        if (pVElan)
        {
            PtDeallocateVElan(pVElan);
            pVElan = NULL;
        }
    }

    return (pVElan);
}


VOID
PtDeallocateVElan(
    IN PVELAN                   pVElan
    )
/*++

Routine Description:

    Free up all resources allocated to a VELAN, and then the VELAN
    structure itself.

Arguments:

    pVElan - Pointer to VELAN to be deallocated.

Return Value:

    None

--*/
{
    
    if (pVElan->SendPacketPoolHandle != NULL)
    {
        NdisFreePacketPool(pVElan->SendPacketPoolHandle);
    }

    if (pVElan->RecvPacketPoolHandle != NULL)
    {
        NdisFreePacketPool(pVElan->RecvPacketPoolHandle);
    }
#if IEEE_VLAN_SUPPORT 
    NdisFreeBufferPool(pVElan->BufferPoolHandle);
    NdisDeleteNPagedLookasideList(&pVElan->TagLookaside);
#endif    
    NdisFreeMemory(pVElan, 0, 0);
}


VOID
PtStopVElan(
    IN  PVELAN            pVElan
)
/*++

Routine Description:

    Stop a VELAN by requesting NDIS to halt the virtual miniport.
    The caller has a reference on the VELAN, so it won't go away
    while we are executing in this routine.

    ASSUMPTION: this is only called in the context of unbinding
    from the underlying miniport. If it may be called from elsewhere,
    this should protect itself from re-entrancy.
    
Arguments:

    pVElan      - Pointer to VELAN to be stopped.
    
Return Value:

    None

--*/
{
    NDIS_STATUS             Status;
    NDIS_HANDLE             MiniportAdapterHandle;
    BOOLEAN                 bMiniportInitCancelled = FALSE;

    DBGPRINT(MUX_LOUD, ("=> StopVElan: VELAN %p, Adapt %p\n", pVElan, pVElan->pAdapt));

    //
    // We make blocking calls below.
    //
    ASSERT_AT_PASSIVE();

    //
    // If there was a queued request on this VELAN, fail it now.
    //
    NdisAcquireSpinLock(&pVElan->Lock);
    ASSERT(pVElan->DeInitializing == TRUE);
    if (pVElan->QueuedRequest)
    {
        pVElan->QueuedRequest = FALSE;
        NdisReleaseSpinLock(&pVElan->Lock);

        PtRequestComplete(pVElan->pAdapt,
                          &pVElan->Request.Request,
                          NDIS_STATUS_FAILURE);
    }

    else
    {
        NdisReleaseSpinLock(&pVElan->Lock);
    }
    //
    // Check if we had called NdisIMInitializeDeviceInstanceEx and
    // we are awaiting a call to MiniportInitialize.
    //
    if (pVElan->MiniportInitPending)
    {
        //
        // Attempt to cancel miniport init.
        //
        Status = NdisIMCancelInitializeDeviceInstance(
                    DriverHandle,
                    &pVElan->CfgDeviceName);

        if (Status == NDIS_STATUS_SUCCESS)
        {
            //
            // Successfully cancelled IM initialization; our
            // Miniport Init routine will not be called for this
            // VELAN miniport.
            //
            pVElan->MiniportInitPending = FALSE;
            ASSERT(pVElan->MiniportAdapterHandle == NULL);
            bMiniportInitCancelled = TRUE;
        }
        else
        {
            //
            // Our Miniport Initialize routine will be called
            // (may be running on another thread at this time).
            // Wait for it to finish.
            //
            NdisWaitEvent(&pVElan->MiniportInitEvent, 0);
            ASSERT(pVElan->MiniportInitPending == FALSE);
        }
    }

    //
    // Check if Miniport Init has run. If so, deinitialize the virtual
    // miniport. This will result in a call to our Miniport Halt routine,
    // where the VELAN will be cleaned up.
    //
    MiniportAdapterHandle = pVElan->MiniportAdapterHandle;

    if ((NULL != MiniportAdapterHandle) &&
        (!pVElan->MiniportHalting))
    {
        //
        // The miniport was initialized, and has not yet halted.
        //
        ASSERT(bMiniportInitCancelled == FALSE);
        (VOID)NdisIMDeInitializeDeviceInstance(MiniportAdapterHandle);
    }
    else
    {
        if (bMiniportInitCancelled)
        {
            //
            // No NDIS events can come to this VELAN since it
            // was never initialized as a miniport. We need to unlink
            // it explicitly here.
            //
            PtUnlinkVElanFromAdapter(pVElan);
        }
    }
}


VOID
PtUnlinkVElanFromAdapter(
    IN PVELAN               pVElan
)
/*++

Routine Description:

    Utility routine to unlink a VELAN from its parent ADAPT structure.
    
Arguments:

    pVElan      - Pointer to VELAN to be unlinked.
    
Return Value:

    None

--*/
{
    PADAPT pAdapt = pVElan->pAdapt;    
    LOCK_STATE      LockState;
    
    ASSERT(pAdapt != NULL);

    //
    // Remove this VELAN from the Adapter list
    //
    MUX_ACQUIRE_ADAPT_WRITE_LOCK(pAdapt, &LockState);

    RemoveEntryList(&pVElan->Link);
    pAdapt->VElanCount--;
        
    MUX_RELEASE_ADAPT_WRITE_LOCK(pAdapt, &LockState);
    pVElan->pAdapt = NULL;
    PtDereferenceVElan(pVElan, (PUCHAR)"adapter");

    PtDereferenceAdapter(pAdapt, (PUCHAR)"VElan");
}


PVELAN
PtFindVElan(
    IN    PADAPT                pAdapt,
    IN    PNDIS_STRING          pVElanKey
)
/*++

Routine Description:

    Find an ELAN by bind name/key

Arguments:

    pAdapt     -    Pointer to an adapter struct.
    pVElanKey  -    The VELAN's device name

Return Value:

    Pointer to matching VELAN or NULL if not found.
    
--*/
{
    PLIST_ENTRY         p;
    PVELAN              pVElan;
    BOOLEAN             Found;
    NDIS_STRING         VElanKeyName;
    LOCK_STATE          LockState;

    ASSERT_AT_PASSIVE();

    DBGPRINT(MUX_LOUD, ("FindElan: Adapter %p, ElanKey %ws\n", pAdapt, 
                                        pVElanKey->Buffer));

    pVElan = NULL;
    Found = FALSE;
    VElanKeyName.Buffer = NULL;

    do
    {
        //
        // Make an up-cased copy of the given string.
        //
        NdisAllocateMemoryWithTag(&VElanKeyName.Buffer, 
                                pVElanKey->MaximumLength, TAG);
        if (VElanKeyName.Buffer == NULL)
        {
            break;
        }

        VElanKeyName.Length = pVElanKey->Length;
        VElanKeyName.MaximumLength = pVElanKey->MaximumLength;

        (VOID)NdisUpcaseUnicodeString(&VElanKeyName, pVElanKey);

        //
        // Go through all VELANs on the ADAPT structure, looking
        // for a VELAN that has a matching device name.
        //
        MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);

        p = pAdapt->VElanList.Flink;
        while (p != &pAdapt->VElanList)
        {
            pVElan = CONTAINING_RECORD(p, VELAN, Link);

            if ((VElanKeyName.Length == pVElan->CfgDeviceName.Length) &&
                (memcmp(VElanKeyName.Buffer, pVElan->CfgDeviceName.Buffer, 
                VElanKeyName.Length) == 0))
            {
                Found = TRUE;
                break;
            }
        
            p = p->Flink;
        }

        MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);

    }
    while (FALSE);

    if (!Found)
    {
        DBGPRINT(MUX_INFO, ( "FindElan: No match found!\n"));
        pVElan = NULL;
    }

    if (VElanKeyName.Buffer)
    {
        NdisFreeMemory(VElanKeyName.Buffer, VElanKeyName.Length, 0);
    }

    return pVElan;
}


NDIS_STATUS
PtBootStrapVElans(
    IN  PADAPT            pAdapt
)
/*++

Routine Description:

    Start up the VELANs configured for an adapter.

Arguments:

    pAdapt    - Pointer to ATMLANE Adapter structure

Return Value:

    None

--*/
{
    NDIS_STATUS                     Status;
    NDIS_HANDLE                     AdapterConfigHandle;
    PNDIS_CONFIGURATION_PARAMETER   Param;
    NDIS_STRING                     DeviceStr = NDIS_STRING_CONST("UpperBindings");
    PWSTR                           buffer;
    LOCK_STATE                      LockState;
    //
    //  Initialize.
    //
    Status = NDIS_STATUS_SUCCESS;
    AdapterConfigHandle = NULL;
    
    do
    {
        DBGPRINT(MUX_LOUD, ("BootStrapElans: Starting ELANs on adapter %x\n", pAdapt));

        //
        //  Open the protocol configuration section for this adapter.
        //

        NdisOpenProtocolConfiguration(&Status,
                                       &AdapterConfigHandle,
                                       &pAdapt->ConfigString);

        if (NDIS_STATUS_SUCCESS != Status)
        {
            AdapterConfigHandle = NULL;
            DBGPRINT(MUX_ERROR, ("BootStrapElans: OpenProtocolConfiguration failed\n"));
            Status = NDIS_STATUS_OPEN_FAILED;
            break;
        }
        
        //
        // Read the "UpperBindings" reserved key that contains a list
        // of device names representing our miniport instances corresponding
        // to this lower binding. The UpperBindings is a 
        // MULTI_SZ containing a list of device names. We will loop through
        // this list and initialize the virtual miniports.
        //
        NdisReadConfiguration(&Status,
                              &Param,
                              AdapterConfigHandle,
                              &DeviceStr,
                              NdisParameterMultiString);
        if (NDIS_STATUS_SUCCESS != Status)
        {
            DBGPRINT(MUX_ERROR, ("BootStrapElans: NdisReadConfiguration failed\n"));
            break;
        }

        //
        // Parse the Multi_sz string to extract the device name of each VELAN.
        // This is used as the key name for the VELAN.
        //
        buffer = (PWSTR)Param->ParameterData.StringData.Buffer;
        while(*buffer != L'\0')
        {
            NDIS_STRING     DeviceName;
            
            NdisInitUnicodeString(&DeviceName, buffer);
           

            Status = PtCreateAndStartVElan(pAdapt, &DeviceName); 
            if (NDIS_STATUS_SUCCESS != Status)
            {
                DBGPRINT(MUX_ERROR, ("BootStrapElans: CreateVElan failed\n"));
                break;
            }
            buffer = (PWSTR)((PUCHAR)buffer + DeviceName.Length + sizeof(WCHAR));
        };
          
    } while (FALSE);

    //
    //    Close config handles
    //        
    if (NULL != AdapterConfigHandle)
    {
        NdisCloseConfiguration(AdapterConfigHandle);
    }
    //
    // If the driver cannot create any velan for the adapter
    // 
    if (Status != NDIS_STATUS_SUCCESS)
    {
        MUX_ACQUIRE_ADAPT_WRITE_LOCK(pAdapt, &LockState);
        //
        // No VElan is created for this adapter
        //
        if (pAdapt->VElanCount != 0)
        {
            Status = NDIS_STATUS_SUCCESS;
        }
        MUX_RELEASE_ADAPT_WRITE_LOCK(pAdapt, &LockState);
    }   

    return Status;
}

VOID
PtReferenceVElan(
    IN    PVELAN            pVElan,
    IN    PUCHAR            String
    )
/*++

Routine Description:

    Add a references to an Elan structure.

Arguments:

    pElan    -    Pointer to the Elan structure.


Return Value:

    None.

--*/
{
    
    NdisInterlockedIncrement((PLONG)&pVElan->RefCount);

#if !DBG
    UNREFERENCED_PARAMETER(String);
#endif

    DBGPRINT(MUX_LOUD, ("ReferenceElan: Elan %p (%s) new count %d\n",
             pVElan, String, pVElan->RefCount));

    return;
}

ULONG
PtDereferenceVElan(
    IN    PVELAN            pVElan,
    IN    PUCHAR            String
    )
/*++

Routine Description:

    Subtract a reference from an VElan structure. 
    If the reference count becomes zero, deallocate it.

Arguments:

    pElan    -    Pointer to an VElan structure.


Return Value:

    None.

--*/
{
    ULONG        rc;

#if !DBG
    UNREFERENCED_PARAMETER(String);
#endif

    ASSERT(pVElan->RefCount > 0);

    rc = NdisInterlockedDecrement((PLONG)&pVElan->RefCount);

    if (rc == 0)
    {
        //
        // Free memory if there is no outstanding reference.
        // Note: Length field is not required if the memory 
        // is allocated with NdisAllocateMemoryWithTag.
        //
        PtDeallocateVElan(pVElan);
    }
    
    DBGPRINT(MUX_LOUD, ("DereferenceElan: VElan %p (%s) new count %d\n", 
                                    pVElan, String, rc));
    return (rc);
}


BOOLEAN
PtReferenceAdapter(
    IN    PADAPT            pAdapt,
    IN    PUCHAR            String
    )
/*++

Routine Description:

    Add a references to an Adapter structure.

Arguments:

    pAdapt    -    Pointer to the Adapter structure.

Return Value:

    None.

--*/
{
    
#if !DBG
    UNREFERENCED_PARAMETER(String);
#endif

    NdisInterlockedIncrement((PLONG)&pAdapt->RefCount);
    
    DBGPRINT(MUX_LOUD, ("ReferenceAdapter: Adapter %x (%s) new count %d\n",
                    pAdapt, String, pAdapt->RefCount));

    return TRUE;
}

ULONG
PtDereferenceAdapter(
    IN    PADAPT    pAdapt,
    IN    PUCHAR    String
    )
/*++

Routine Description:

    Subtract a reference from an Adapter structure. 
    If the reference count becomes zero, deallocate it.

Arguments:

    pAdapt    -    Pointer to an adapter structure.


Return Value:

    None.

--*/
{
    ULONG        rc;

#if !DBG
    UNREFERENCED_PARAMETER(String);
#endif

    ASSERT(pAdapt->RefCount > 0);


    rc = NdisInterlockedDecrement ((PLONG)&pAdapt->RefCount);

    if (rc == 0)
    {
        //
        // Free memory if there is no outstanding reference.
        // Note: Length field is not required if the memory 
        // is allocated with NdisAllocateMemoryWithTag.
        //
        NdisFreeMemory(pAdapt, 0, 0);
    }

    DBGPRINT(MUX_LOUD, ("DereferenceAdapter: Adapter %x (%s) new count %d\n", 
                        pAdapt, String, rc));

    return (rc);
}


VOID PtReceiveNBL(IN NDIS_HANDLE ProtocolBindingContext,
                  IN PNET_BUFFER_LIST NetBufferLists,
                  IN NDIS_STATUS Status,
                  IN BOOLEAN DispatchLevel)
/*++

Routine Description:
    ReceiveNetBufferList handler. 

Arguments:
    ProtocolBindingContext                  Pointer to our PADAPT structure
    NetBufferLists                          Net Buffer Lists received
    Status                                  Status of the receive
    DispatchLevel                           TRUE if IRQL == DISPATCH_LEVEL

Return Value:
    None

--*/
{
    PADAPT                  pAdapt = (PADAPT)ProtocolBindingContext;
    PVELAN                  pVElan = NULL;
    PUCHAR                  pDstMac;
    BOOLEAN                 bIsMulticast;
    BOOLEAN                 bIsBroadcast;
    BOOLEAN                 bIndicated = FALSE;
    PNET_BUFFER_LIST        CurrentNetBufferList;
    PNET_BUFFER_LIST        ClonedNetBufferList;
    PNET_BUFFER_LIST        HeadNetBufferList;
    LOCK_STATE              LockState;
    PLIST_ENTRY             p;
    UCHAR                   Data[6];
    NDIS_STATUS             NdisStatus;
#ifdef IEEE_VLAN_SUPPORT
    NDIS_PACKET_8021Q_INFO  NdisPacket8021qInfo;
    PUCHAR                  pEthFrameHdr;
    PUCHAR                  pVlanFrameHdr;
    PUCHAR                  pTagHeader;
#endif

    DBGPRINT(MUX_VERY_LOUD,("==>PtReceiveNBL ProtocolBindingContext=%08lx, NetBufferLists=%08lx\n",ProtocolBindingContext,NetBufferLists));


    HeadNetBufferList = NetBufferLists; 

    ASSERT(HeadNetBufferList != NULL);

    while (NetBufferLists != NULL)
    {
        CurrentNetBufferList = NetBufferLists;
        
        NetBufferLists = NetBufferLists->Next;

        // We could get receives in the interval between
        // initiating a request to set the packet filter on
        // the binding to 0 and completion of that request.

        if (pAdapt->PacketFilter == 0)
        {
            break;
        }

        // Collect some information about the packet


        pDstMac = NdisGetDataBuffer(CurrentNetBufferList->FirstNetBuffer, 
                                    6,
                                    (PVOID)Data,
                                    1,
                                    0);

        if (pDstMac == NULL)
        {
            ASSERT(0);
        }

        // Determine if the packet is broadcast or multicast

        bIsMulticast = ETH_IS_MULTICAST(pDstMac);
        bIsBroadcast = ETH_IS_BROADCAST(pDstMac);

        // Lock down the VLAN list on the adapter so that no insertions
        // deletions to this list happen while we loop through it. The packet
        // filter will also not change during this time we hold the read lock.

        MUX_ACQUIRE_ADAPT_READ_LOCK(pAdapt, &LockState);

        // Set up the ref count before we start indicating the packet

        for (p = pAdapt->VElanList.Flink;
             p != &pAdapt->VElanList;
             p = p->Flink)
        {
            BOOLEAN  bIndicateReceive;

            pVElan = CONTAINING_RECORD(p, VELAN, Link);

            // Should the packet be indicated up on this VELAN ?

            bIndicateReceive = PtMatchPacketToVElan(pVElan,
                                                    pDstMac,
                                                    bIsMulticast,
                                                    bIsBroadcast);

            if (!bIndicateReceive)
            {
                continue;
            }

            MUX_INCR_PENDING_RECEIVES(pVElan);

            if ((pVElan->MiniportInitPending)
                 || (pVElan->MiniportHalting)
                 || (MUX_IS_LOW_POWER_STATE(pVElan->MPDevicePowerState)))
            {
                MUX_DECR_PENDING_RECEIVES(pVElan);
                continue;
            }
            
            bIndicated = FALSE;
            // Clone the net buffer list

            ClonedNetBufferList = NdisAllocateCloneNetBufferList(CurrentNetBufferList,NULL,NULL, DispatchLevel);

            if (ClonedNetBufferList != NULL)
            {

                do
                {
#ifdef IEEE_VLAN_SUPPORT

                    if (ClonedNetBufferList->FirstNetBuffer->DataLength < VLAN_TAG_HEADER_SIZE)
                    {
                        DBGPRINT(MUX_LOUD,("Cloned NBL %08lx size < VLAN_TAG_HEADER_SIZE\n",ClonedNetBufferList));

                        continue;
                    }
#endif


                    NdisAcquireSpinLock(&pVElan->PauseLock);

                    if (!pVElan->Paused)
                    {
                        NdisReleaseSpinLock(&pVElan->PauseLock);

#ifdef IEEE_VLAN_SUPPORT
                        NdisStatus = PtHandleReceiveTaggingNB(pVElan, ClonedNetBufferList);

                        if (NdisStatus != NDIS_STATUS_SUCCESS)
                        {
                            DBGPRINT(MUX_LOUD,("Cloned NBL %08lx receive tagging failed\n",ClonedNetBufferList));

                            continue;
                        }
#endif

                        MUX_INCR_STATISTICS64(&pVElan->GoodReceives);

#ifdef IEEE_VLAN_SUPPORT
                        NdisPacket8021qInfo.Value = NET_BUFFER_LIST_INFO(ClonedNetBufferList, Ieee8021QNetBufferListInfo);

                        if (NdisPacket8021qInfo.Value)
                        {
                            NdisAdvanceNetBufferDataStart(ClonedNetBufferList->FirstNetBuffer,
                                                          VLAN_TAG_HEADER_SIZE,
                                                          NULL);
                        }
#endif


                        // Indicate to the protocol(s) bound to the Miniport
                
                        NdisMIndicateReceiveNetBufferLists(pVElan->MiniportAdapterHandle,
                                                           ClonedNetBufferList,
                                                           NDIS_STATUS_RESOURCES,
                                                           TRUE);

                        bIndicated = TRUE;
                    }
                    else
                    {
                        if (pVElan->PendingNBLs != NULL)
                        {
                            pVElan->PendingNBLsTail->Next = ClonedNetBufferList;
                            pVElan->PendingNBLsTail = ClonedNetBufferList;
                        } else
                        {
                            pVElan->PendingNBLs = ClonedNetBufferList;
                            pVElan->PendingNBLs->Next = NULL;
                            pVElan->PendingNBLsTail = pVElan->PendingNBLs;
                        }

                        bIndicated = FALSE;
                        NdisReleaseSpinLock(&pVElan->PauseLock);
                    }


                } while(FALSE);

                if (bIndicated)
                {
                    NdisFreeCloneNetBufferList(ClonedNetBufferList,DispatchLevel);
                }

            }

            MUX_DECR_PENDING_RECEIVES(pVElan);

        }

        MUX_RELEASE_ADAPT_READ_LOCK(pAdapt, &LockState);

    }

    if (Status != NDIS_STATUS_RESOURCES)
    {
        NdisReturnNetBufferLists(pAdapt->BindingHandle,
                                 HeadNetBufferList,
                                 DispatchLevel);
    }
                             

    DBGPRINT(MUX_VERY_LOUD,("<==PtReceiveNBL\n"));
}


VOID PtSendNBLComplete(IN NDIS_HANDLE ProtocolBindingHandle,
                       IN PNET_BUFFER_LIST NetBufferLists,
                       IN BOOLEAN DispatchLevel)
/*++

Routine Description:
    Called by NDIS when the miniport below has completed a send.
    We complete the corresponding upper-edge send this represents.

Arguments:
    ProtocolBindingHandle           Points to our PADAPT structure
    NetBufferLists                  Packet being completed by the lower miniport
    Dispatch                        TRUE if IRQL == DISPATCH_LEVEL

Return Value:
    None

--*/
{
    PVELAN                  pVElan;
    PNET_BUFFER_LIST        OriginalNBL;
    NDIS_STATUS             Status;
    PVOID                   *pData;
#ifdef IEEE_VLAN_SUPPORT
    NDIS_PACKET_8021Q_INFO  NdisPacket8021qInfo;
#endif

    DBGPRINT(MUX_VERY_LOUD,("==>PtSendNBLComplete ProtocolBindingContext=%08lx, NetBufferLists=%08lx\n",ProtocolBindingHandle,NetBufferLists));

    pData = (PVOID *)NET_BUFFER_LIST_CONTEXT_DATA_START(NetBufferLists);

    pVElan = (PVELAN)pData[1];

    NetBufferLists->SourceHandle = (NDIS_HANDLE)pData[0];

    Status = NetBufferLists->Status;

    NdisFreeNetBufferListContext(NetBufferLists,
                                     2 * sizeof(PVOID));

#ifdef IEEE_VLAN_SUPPORT
    NdisPacket8021qInfo.Value = NET_BUFFER_LIST_INFO(NetBufferLists, Ieee8021QNetBufferListInfo);

    if ((!MuxRecognizedVlanId(pVElan,0)) && (!NdisPacket8021qInfo.TagHeader.VlanId))
    {
        NdisAdvanceNetBufferDataStart(NetBufferLists->FirstNetBuffer,
                                      VLAN_TAG_HEADER_SIZE,
                                      MuxFreeMdl);
    }

#endif

    if (Status == NDIS_STATUS_SUCCESS)
    {
        MUX_INCR_STATISTICS64(&pVElan->GoodTransmits);
    }
    else
    {
        MUX_INCR_STATISTICS(&pVElan->TransmitFailuresOther);
    }

    NdisMSendNetBufferListsComplete(pVElan->MiniportAdapterHandle,
                                    NetBufferLists,
                                    DispatchLevel);

    MUX_DECR_PENDING_SENDS(pVElan);

    DBGPRINT(MUX_VERY_LOUD,("<==PtSendNBLComplete\n"));
}

#ifdef IEEE_VLAN_SUPPORT
NDIS_STATUS PtHandleReceiveTaggingNB(IN PVELAN pVElan,
                           IN PNET_BUFFER_LIST NetBufferList)
/*++

Routine Description:

    Parse a received Ethernet frame for 802.1Q tag information.
    If a tag header is present, copy in relevant field values to
    per-packet inforation to the new NET_BUFFER_LIST used
    to indicate up this frame.

Arguments:
    pVElan              Pointer to the VELAN structure
    NetBufferList       Pointer to the indicated packet from the lower miniport

Return Value:
    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_ACCEPTED


--*/
{

    VLAN_TAG_HEADER UNALIGNED *     pTagHeader;
    USHORT UNALIGNED *              pTpid;
    PVOID                           pFrame = NULL;
    PVOID                           pDst;
    ULONG                           BufferLength;
    NDIS_PACKET_8021Q_INFO          NdisPacket8021qInfo;
    NDIS_STATUS                     Status = NDIS_STATUS_SUCCESS;

#ifdef DBG
    ULONG                           Count = 0;
#endif

    do
    {
        //
        // If the vlan ID of the virtual miniport is 0, the miniport should
        // act like it doesn't support VELAN tag processing
        //

        if (MuxRecognizedVlanId(pVElan,0))
            break;

        if ((pVElan->Striping)
             && (NET_BUFFER_LIST_INFO(NetBufferList, Ieee8021QNetBufferListInfo) != 0))
        {
            Status = NDIS_STATUS_NOT_ACCEPTED;
            MUX_INCR_STATISTICS(&pVElan->RcvVlanIdErrors);
            break;
        }

        pFrame = NdisGetDataBuffer(NetBufferList->FirstNetBuffer,
                                   2 * ETH_LENGTH_OF_ADDRESS + VLAN_TAG_HEADER_SIZE,
                                   NULL,
                                   1,
                                   0);

#ifdef DBG
        if (pFrame == NULL)
        {
            ASSERT(0);
        }
#endif

        // Get at the Ethertype field

        pTpid = (USHORT UNALIGNED *)((PUCHAR)pFrame + 2 * ETH_LENGTH_OF_ADDRESS);

        // Check if Tag header is present

        if (*pTpid != TPID)
        {
            NET_BUFFER_LIST_INFO(NetBufferList, Ieee8021QNetBufferListInfo) = 0;
            break;
        }

        //
        // If E-RIF present then discard header as we do not support
        // this variation
        //

        pTagHeader = (VLAN_TAG_HEADER UNALIGNED *)(pTpid + 1);

        if (GET_CANONICAL_FORMAT_ID_FROM_TAG(pTagHeader) != 0)
        {
            //
            // Drop packet
            //

            Status = NDIS_STATUS_NOT_ACCEPTED;
            MUX_INCR_STATISTICS(&pVElan->RcvFormatErrors);
            break;
        }

        if ((GET_VLAN_ID_FROM_TAG(pTagHeader) != 0)
            && (!MuxRecognizedVlanId(pVElan,GET_VLAN_ID_FROM_TAG(pTagHeader))))
        {
            //
            // Drop
            //
            
            Status = NDIS_STATUS_NOT_ACCEPTED;

            MUX_INCR_STATISTICS(&pVElan->RcvVlanIdErrors);
            break;
        }

        NdisPacket8021qInfo.Value = NULL;

        COPY_TAG_INFO_FROM_HEADER_TO_PACKET_INFO(NdisPacket8021qInfo,pTagHeader);

        // Strip off header
        
        pDst = (PVOID)((PUCHAR)pFrame + VLAN_TAG_HEADER_SIZE);

        RtlMoveMemory(pDst, pFrame, 2 * ETH_LENGTH_OF_ADDRESS);

        if (pVElan->Striping)
        {
            NET_BUFFER_LIST_INFO(NetBufferList, Ieee8021QNetBufferListInfo) = 0;
        }
        else
        {
            NET_BUFFER_LIST_INFO(NetBufferList, Ieee8021QNetBufferListInfo) = NdisPacket8021qInfo.Value;
        }

        RtlCopyMemory((PVOID UNALIGNED)&(NetBufferList->MiniportReserved[1]), pTagHeader, 2);

    } while(FALSE);

    return Status;
}
#endif

