/*++

Copyright (c) 1999  Microsoft Corporation

Module Name:
    mp_req.c

Abstract:
    This module contains miniport OID related handlers

Revision History:
    Who         When        What
    --------    --------    ----------------------------------------------
    DChen       11-01-99    created

Notes:

--*/


    
#include "precomp.h"
#include "e100_wmi.h"


#if DBG
#define _FILENUMBER     'QERM'
#endif

ULONG VendorDriverVersion = NIC_VENDOR_DRIVER_VERSION;

NDIS_OID NICSupportedOids[] =
{
    OID_GEN_SUPPORTED_LIST,
    OID_GEN_HARDWARE_STATUS,
    OID_GEN_MEDIA_SUPPORTED,
    OID_GEN_MEDIA_IN_USE,
    OID_GEN_MAXIMUM_LOOKAHEAD,
    OID_GEN_MAXIMUM_FRAME_SIZE,
    OID_GEN_LINK_SPEED,
    OID_GEN_TRANSMIT_BUFFER_SPACE,
    OID_GEN_RECEIVE_BUFFER_SPACE,
    OID_GEN_TRANSMIT_BLOCK_SIZE,
    OID_GEN_RECEIVE_BLOCK_SIZE,
    OID_GEN_VENDOR_ID,
    OID_GEN_VENDOR_DESCRIPTION,
    OID_GEN_VENDOR_DRIVER_VERSION,
    OID_GEN_CURRENT_PACKET_FILTER,
    OID_GEN_CURRENT_LOOKAHEAD,
    OID_GEN_DRIVER_VERSION,
    OID_GEN_MAXIMUM_TOTAL_SIZE,
    OID_GEN_MAC_OPTIONS,
    OID_GEN_MEDIA_CONNECT_STATUS,
    OID_GEN_MAXIMUM_SEND_PACKETS,
    OID_GEN_SUPPORTED_GUIDS,
    OID_GEN_XMIT_OK,
    OID_GEN_RCV_OK,
    OID_GEN_XMIT_ERROR,
    OID_GEN_RCV_ERROR,
    OID_GEN_RCV_NO_BUFFER,
    OID_GEN_STATISTICS,
    OID_GEN_RCV_CRC_ERROR,
    OID_GEN_TRANSMIT_QUEUE_LENGTH,
    OID_GEN_PHYSICAL_MEDIUM,
    OID_802_3_PERMANENT_ADDRESS,
    OID_802_3_CURRENT_ADDRESS,
    OID_802_3_MULTICAST_LIST,
    OID_802_3_MAXIMUM_LIST_SIZE,
    OID_802_3_RCV_ERROR_ALIGNMENT,
    OID_802_3_XMIT_ONE_COLLISION,
    OID_802_3_XMIT_MORE_COLLISIONS,
    OID_802_3_XMIT_DEFERRED,
    OID_802_3_XMIT_MAX_COLLISIONS,
    OID_802_3_RCV_OVERRUN,
    OID_802_3_XMIT_UNDERRUN,
    OID_802_3_XMIT_HEARTBEAT_FAILURE,
    OID_802_3_XMIT_TIMES_CRS_LOST,
    OID_802_3_XMIT_LATE_COLLISIONS,

    OID_GEN_REQUIRED_BACKFILL_SIZE,
    OID_GEN_LINK_SPEED_EX,
    OID_GEN_MAX_LINK_SPEED,
    OID_GEN_MEDIA_CONNECT_STATUS_EX,
    OID_GEN_MEDIA_DUPLEX_STATE,
    OID_GEN_SUPPORTED_PACKET_FILTERS,
    OID_GEN_LINK_STATE,

#define OID_GEN_LINK_SPEED_EX                   0x00010206  // query only
#define OID_GEN_MEDIA_CONNECT_STATUS_EX         0x00010208  // query only
#define OID_GEN_MEDIA_DUPLEX_STATE              0x00010209  // query only
#define OID_GEN_SUPPORTED_PACKET_FILTERS        0x0001020A  // query only
#define OID_GEN_LINK_STATE                      0x0001020B  // query only

/* powermanagement */

    OID_PNP_CAPABILITIES,
    OID_PNP_SET_POWER,
    OID_PNP_QUERY_POWER,
    OID_PNP_ADD_WAKE_UP_PATTERN,
    OID_PNP_REMOVE_WAKE_UP_PATTERN,
    OID_PNP_ENABLE_WAKE_UP,


/* custom oid WMI support */
    OID_CUSTOM_DRIVER_SET,
    OID_CUSTOM_DRIVER_QUERY,
    OID_CUSTOM_ARRAY,
    OID_CUSTOM_STRING,
    OID_CUSTOM_METHOD
};

//
// WMI support
// check out the e100.mof file for examples of how the below
// maps into a .mof file for external advertisement of GUIDs
//
#define NIC_NUM_CUSTOM_GUIDS  5       
//
// Define the following values to demonstrate that the driver should
// always validat the content in the information buffer whether the OID
// is for set or query
//
#define CUSTOM_DRIVER_SET_MIN   0x1       
#define CUSTOM_DRIVER_SET_MAX   0xFFFFFF     

static const NDIS_GUID NICGuidList[NIC_NUM_CUSTOM_GUIDS] = {
    { // {F4A80276-23B7-11d1-9ED9-00A0C9010057} example of a uint set
        E100BExampleSetUINT_OIDGuid,
        OID_CUSTOM_DRIVER_SET,
        sizeof(ULONG),
        // Not setting fNDIS_GUID_ALLOW_WRITE flag means that we don't allow
        // users without administrator privilege to set this value, but we do 
        // allow any user to query this value
        (fNDIS_GUID_TO_OID | fNDIS_GUID_ALLOW_READ)
    },
    { // {F4A80277-23B7-11d1-9ED9-00A0C9010057} example of a uint query
        E100BExampleQueryUINT_OIDGuid,
            OID_CUSTOM_DRIVER_QUERY,
            sizeof(ULONG),
            // setting fNDIS_GUID_ALLOW_READ flag means that we allow any
            // user to query this value.
            (fNDIS_GUID_TO_OID | fNDIS_GUID_ALLOW_READ)
    },
    { // {F4A80278-23B7-11d1-9ED9-00A0C9010057} example of an array query
        E100BExampleQueryArrayOIDGuid,
            OID_CUSTOM_ARRAY,
            sizeof(UCHAR),  // size is size of each element in the array
            // setting fNDIS_GUID_ALLOW_READ flag means that we allow any
            // user to query this value.
            (fNDIS_GUID_TO_OID|fNDIS_GUID_ARRAY | fNDIS_GUID_ALLOW_READ)
    },
    { // {F4A80279-23B7-11d1-9ED9-00A0C9010057} example of a string query
        E100BExampleQueryStringOIDGuid,
            OID_CUSTOM_STRING,
            (ULONG) -1, // size is -1 for ANSI or NDIS_STRING string types
            // setting fNDIS_GUID_ALLOW_READ flag means that we allow any
            // user to query this value.
            (fNDIS_GUID_TO_OID|fNDIS_GUID_ANSI_STRING | fNDIS_GUID_ALLOW_READ)
    },
    { // {07f8e235-ddde-4c32-9225-36a1e15a9d64} example of a execute method
        E100BExampleExecuteMethodGuid,
            OID_CUSTOM_METHOD,
            (ULONG) -1, // size is -1 for ANSI or NDIS_STRING string types
            // setting fNDIS_GUID_ALLOW_READ flag means that we allow any
            // user to query this value.
            (fNDIS_GUID_METHOD|fNDIS_GUID_ALLOW_WRITE| fNDIS_GUID_ALLOW_READ)
    }
};

/**
Local Prototypes
**/
NDIS_STATUS
MPSetPower(
    PMP_ADAPTER     Adapter ,
    NDIS_DEVICE_POWER_STATE   PowerState 
    );

NDIS_STATUS
MPAddWakeUpPattern(
    IN PMP_ADAPTER   pAdapter,
    IN PVOID         InformationBuffer, 
    IN UINT          InformationBufferLength,
    IN OUT PULONG    BytesRead,
    IN OUT PULONG    BytesNeeded    
    );

NDIS_STATUS
MPRemoveWakeUpPattern(
    IN PMP_ADAPTER  pAdapter,
    IN PVOID        InformationBuffer, 
    IN UINT         InformationBufferLength,
    OUT PULONG      BytesRead,
    OUT PULONG      BytesNeeded
    );

BOOLEAN 
MPAreTwoPatternsEqual(
    IN PNDIS_PM_PACKET_PATTERN pNdisPattern1,
    IN PNDIS_PM_PACKET_PATTERN pNdisPattern2
    );

//
// Macros used to walk a doubly linked list. Only macros that are not defined in ndis.h
// The List Next macro will work on Single and Doubly linked list as Flink is a common
// field name in both
//

/*
PLIST_ENTRY
ListNext (
    IN PLIST_ENTRY
    );

PSINGLE_LIST_ENTRY
ListNext (
    IN PSINGLE_LIST_ENTRY
    );
*/
#define ListNext(_pL)                       (_pL)->Flink

/*
PLIST_ENTRY
ListPrev (
    IN LIST_ENTRY *
    );
*/
#define ListPrev(_pL)                       (_pL)->Blink


__inline 
BOOLEAN  
MPIsPoMgmtSupported(
   IN PMP_ADAPTER pAdapter
   )
{

    if (pAdapter->RevsionID  >= E100_82559_A_STEP   && 
         pAdapter->RevsionID <= E100_82559_C_STEP )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}


NDIS_STATUS 
MPRequest(
    IN  NDIS_HANDLE        MiniportAdapterContext,
    IN  PNDIS_OID_REQUEST  NdisRequest
    )

/*++
Routine Description:

    MiniportRequest dispatch handler            

Arguments:

    MiniportAdapterContext  Pointer to the adapter structure
    NdisRequest             Pointer to NDIS_OID_REQUEST
    
Return Value:
    
    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    NDIS_STATUS_BUFFER_TOO_SHORT
    
--*/
{
    PMP_ADAPTER             Adapter = (PMP_ADAPTER)MiniportAdapterContext;
    NDIS_STATUS             Status = NDIS_STATUS_SUCCESS;
    NDIS_REQUEST_TYPE       RequestType;

    DBGPRINT(MP_TRACE, ("====> MPRequest\n"));

    //
    // Should abort the request if reset is in process
    //
    NdisAcquireSpinLock(&Adapter->Lock);

    //
    // If there is a request pending then assert.
    //

    ASSERT(Adapter->PendingRequest == NULL);

    if (MP_TEST_FLAG(Adapter, 
        (fMP_ADAPTER_RESET_IN_PROGRESS | fMP_ADAPTER_REMOVE_IN_PROGRESS)))
    {
        NdisReleaseSpinLock(&Adapter->Lock);
        return NDIS_STATUS_REQUEST_ABORTED;
    }
    NdisReleaseSpinLock(&Adapter->Lock);    
    
    RequestType = NdisRequest->RequestType;
    
    switch (RequestType)
    {
        case NdisRequestMethod:
            Status = MpMethodRequest(Adapter, NdisRequest);
            break;

        case NdisRequestSetInformation:            
            Status = MpSetInformation(Adapter, NdisRequest);
            break;
                
        case NdisRequestQueryInformation:
        case NdisRequestQueryStatistics:
            Status = MpQueryInformation(Adapter, NdisRequest);
            break;

        default:
            //
            // Later the entry point may by used by all the requests
            //
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }
    

    DBGPRINT(MP_TRACE, ("<==== MPRequest Status: %x\n", Status));
    return Status;
}



NDIS_STATUS MpQueryInformation(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PNDIS_OID_REQUEST   NdisRequest
    )
/*++
Routine Description:

    MiniportQueryInformation handler            

Arguments:

    MiniportAdapterContext  Pointer to the adapter structure
    NdisRequest             Pointer to the query request

Return Value:
    
    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    NDIS_STATUS_BUFFER_TOO_SHORT
    
--*/
{
    NDIS_STATUS                 Status = NDIS_STATUS_SUCCESS;
    PMP_ADAPTER                 Adapter;
    NDIS_OID                    Oid;
    PVOID                       InformationBuffer;
    ULONG                       InformationBufferLength;
    ULONG                       BytesWritten;
    ULONG                       BytesNeeded;

    NDIS_HARDWARE_STATUS        HardwareStatus = NdisHardwareStatusReady;
    NDIS_MEDIUM                 Medium = NIC_MEDIA_TYPE;
    NDIS_PHYSICAL_MEDIUM        PhysMedium = NdisPhysicalMediumUnspecified;
    UCHAR                       VendorDesc[] = NIC_VENDOR_DESC;
    ULONG                       VendorDescSize;
    ULONG                       i;
    ANSI_STRING                 strAnsi;
    WCHAR                      *WcharBuf;
    NDIS_PNP_CAPABILITIES       Power_Management_Capabilities;

    ULONG                       ulInfo = 0;
    ULONG64                     ul64Info = 0;
    
    USHORT                      usInfo = 0;                                              
    PVOID                       pInfo = (PVOID) &ulInfo;
    ULONG                       ulInfoLen = sizeof(ulInfo);
    ULONG                       ulBytesAvailable = ulInfoLen;
    NDIS_MEDIA_CONNECT_STATE    CurrMediaState;
    NDIS_MEDIA_STATE            LegacyMediaState;
    BOOLEAN                     DoCopy = TRUE;
    NDIS_LINK_SPEED             LinkSpeed;

    DBGPRINT(MP_TRACE, ("====> MpQueryInformation\n"));

    Adapter = (PMP_ADAPTER) MiniportAdapterContext;

    Oid = NdisRequest->DATA.QUERY_INFORMATION.Oid;
    InformationBuffer = NdisRequest->DATA.QUERY_INFORMATION.InformationBuffer;
    InformationBufferLength = NdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength;

    //
    // Initialize the result
    //
    BytesWritten = 0;
    BytesNeeded = 0;

    //
    // Process different type of requests
    //
    switch(Oid)
    {
        case OID_GEN_SUPPORTED_LIST:
            pInfo = (PVOID) NICSupportedOids;
            ulBytesAvailable = ulInfoLen = sizeof(NICSupportedOids);
            break;

        case OID_GEN_HARDWARE_STATUS:
            pInfo = (PVOID) &HardwareStatus;
            ulBytesAvailable = ulInfoLen = sizeof(NDIS_HARDWARE_STATUS);
            break;

        case OID_GEN_MEDIA_SUPPORTED:
        case OID_GEN_MEDIA_IN_USE:
            pInfo = (PVOID) &Medium;
            ulBytesAvailable = ulInfoLen = sizeof(NDIS_MEDIUM);
            break;

        case OID_GEN_PHYSICAL_MEDIUM:
            pInfo = (PVOID) &PhysMedium;
            ulBytesAvailable = ulInfoLen = sizeof(NDIS_PHYSICAL_MEDIUM);
            break;

        case OID_GEN_CURRENT_LOOKAHEAD:
        case OID_GEN_MAXIMUM_LOOKAHEAD:
            if (Adapter->ulLookAhead == 0)
            {
                Adapter->ulLookAhead = NIC_MAX_PACKET_SIZE - NIC_HEADER_SIZE;
            }
            ulInfo = Adapter->ulLookAhead;
            break;         

        case OID_GEN_MAXIMUM_FRAME_SIZE:
            ulInfo = NIC_MAX_PACKET_SIZE - NIC_HEADER_SIZE;
            break;

        case OID_GEN_MAXIMUM_TOTAL_SIZE:
        case OID_GEN_TRANSMIT_BLOCK_SIZE:
        case OID_GEN_RECEIVE_BLOCK_SIZE:
            ulInfo = (ULONG) NIC_MAX_PACKET_SIZE;
            break;

        case OID_GEN_MAC_OPTIONS:
            // Notes: 
            // The protocol driver is free to access indicated data by any means. 
            // Some fast-copy functions have trouble accessing on-board device 
            // memory. NIC drivers that indicate data out of mapped device memory 
            // should never set this flag. If a NIC driver does set this flag, it 
            // relaxes the restriction on fast-copy functions. 

            // This miniport indicates receive with NdisMIndicateReceivePacket 
            // function. It has no MiniportTransferData function. Such a driver 
            // should set this flag. 

            ulInfo = NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA | 
                     NDIS_MAC_OPTION_TRANSFERS_NOT_PEND |
                     NDIS_MAC_OPTION_NO_LOOPBACK;
            
            break;
            
        case OID_GEN_LINK_SPEED:
        case OID_GEN_MEDIA_CONNECT_STATUS:
            if (InformationBufferLength < ulInfoLen)
            {
                break;
            }
            NdisAcquireSpinLock(&Adapter->Lock);
            if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION))
            {
                ASSERT(Adapter->PendingRequest == NULL);
                Adapter->PendingRequest = NdisRequest;
                NdisReleaseSpinLock(&Adapter->Lock);

                DBGPRINT(MP_WARN, ("MPQueryInformation: OID 0x%08x is pended\n", Oid));

                Status = NDIS_STATUS_PENDING;   
                break;
            }
            else
            {
                NdisReleaseSpinLock(&Adapter->Lock);
                if (Oid == OID_GEN_LINK_SPEED)
                {
                    ulInfo = Adapter->usLinkSpeed * 10000;
                }
                else  // OID_GEN_MEDIA_CONNECT_STATUS
                {
                    CurrMediaState = NICGetMediaState(Adapter);
                    if (CurrMediaState == MediaConnectStateConnected)
                    {
                        LegacyMediaState = NdisMediaStateConnected;
                    }
                    else
                    {
                        //
                        // treat unknown media state the same as disconnected
                        //
                    
                        LegacyMediaState = NdisMediaStateDisconnected;
                    }

                    NdisAcquireSpinLock(&Adapter->Lock);
                    if (Adapter->MediaState != CurrMediaState)
                    {
                        Adapter->MediaState = CurrMediaState;                     
                        //
                        // indicate the new state up
                        //
                        MPIndicateLinkState(Adapter);
                    }
                    
                    NdisReleaseSpinLock(&Adapter->Lock);
                    
                    ulInfo = LegacyMediaState;
                }
            }
            
            break;

        case OID_GEN_TRANSMIT_BUFFER_SPACE:
            ulInfo = NIC_MAX_PACKET_SIZE * Adapter->NumTcb;
            break;

        case OID_GEN_RECEIVE_BUFFER_SPACE:
            ulInfo = NIC_MAX_PACKET_SIZE * Adapter->CurrNumRfd;
            break;

        case OID_GEN_VENDOR_ID:
            NdisMoveMemory(&ulInfo, Adapter->PermanentAddress, 3);
            break;

        case OID_GEN_VENDOR_DESCRIPTION:
            pInfo = VendorDesc;
            ulBytesAvailable = ulInfoLen = sizeof(VendorDesc);
            break;

        case OID_GEN_VENDOR_DRIVER_VERSION:
            ulInfo = VendorDriverVersion;
            break;

        case OID_GEN_DRIVER_VERSION:
            usInfo = (USHORT) NIC_DRIVER_VERSION;
            pInfo = (PVOID) &usInfo;
            ulBytesAvailable = ulInfoLen = sizeof(USHORT);
            break;

        case OID_GEN_SUPPORTED_GUIDS:
            pInfo = (PUCHAR) &NICGuidList;
            ulBytesAvailable = ulInfoLen =  sizeof(NICGuidList);
            break;
            
        case OID_802_3_PERMANENT_ADDRESS:
            pInfo = Adapter->PermanentAddress;
            ulBytesAvailable = ulInfoLen = ETH_LENGTH_OF_ADDRESS;
            break;

        case OID_802_3_CURRENT_ADDRESS:
            pInfo = Adapter->CurrentAddress;
            ulBytesAvailable = ulInfoLen = ETH_LENGTH_OF_ADDRESS;
            break;

        case OID_802_3_MAXIMUM_LIST_SIZE:
            ulInfo = NIC_MAX_MCAST_LIST;
            break;

        case OID_GEN_MAXIMUM_SEND_PACKETS:
            ulInfo = NIC_MAX_SEND_PACKETS;
            break;

        case OID_PNP_CAPABILITIES:

            MPFillPoMgmtCaps (Adapter, 
                                &Power_Management_Capabilities, 
                                &Status,
                                &ulInfoLen);
            if (Status == NDIS_STATUS_SUCCESS)
            {
                pInfo = (PVOID) &Power_Management_Capabilities;
            }
            else
            {
                pInfo = NULL;
            }

            break;

        case OID_PNP_QUERY_POWER:
            // Status is pre-set in this routine to Success

            Status = NDIS_STATUS_SUCCESS; 

            break;
        
        case OID_GEN_REQUIRED_BACKFILL_SIZE:

            ulInfo = 0; // backfill size
            break;

            // WMI support
        case OID_CUSTOM_DRIVER_QUERY:
            // this is the uint case
            DBGPRINT(MP_INFO,("CUSTOM_DRIVER_QUERY got a QUERY\n"));
            ulInfo = ++Adapter->CustomDriverSet;
            break;

        case OID_CUSTOM_DRIVER_SET:
            DBGPRINT(MP_INFO,("CUSTOM_DRIVER_SET got a QUERY\n"));
            ulInfo = Adapter->CustomDriverSet;
            break;

        case OID_CUSTOM_ARRAY:
            
            DBGPRINT(MP_INFO,("CUSTOM_ARRAY got a QUERY\n"));
                
            //
            // Fill in the correct format
            //
            BytesNeeded = sizeof(ULONG) + 4;
            if (InformationBufferLength < BytesNeeded)
            {
                Status = NDIS_STATUS_BUFFER_TOO_SHORT;
                NdisRequest->DATA.QUERY_INFORMATION.BytesNeeded = BytesNeeded;
                return Status;
            }
            //
            // Buffer length is enough
            // 
            *(PULONG)InformationBuffer = 4;
            
            NdisMoveMemory((PUCHAR)InformationBuffer+sizeof(ULONG), 
                            Adapter->PermanentAddress, 
                            4);
            NdisRequest->DATA.QUERY_INFORMATION.BytesWritten = sizeof(ULONG) + 4;
    
            return Status;
            
        case OID_CUSTOM_STRING:
            //
            // ANSI string, convert to unicode string
            // 
            DBGPRINT(MP_INFO, ("CUSTOM_STRING got a QUERY\n"));

            VendorDescSize = sizeof(VendorDesc);
            
            BytesNeeded = sizeof(USHORT) + (VendorDescSize * sizeof(WCHAR));
            if (InformationBufferLength < BytesNeeded)
            {
                Status = NDIS_STATUS_BUFFER_TOO_SHORT;
                NdisRequest->DATA.QUERY_INFORMATION.BytesNeeded = BytesNeeded;

                return Status;
            }
            NdisInitAnsiString(&strAnsi, VendorDesc); 

            WcharBuf = (WCHAR *)((PUCHAR)InformationBuffer + sizeof(USHORT));
            for (i = 0; i < strAnsi.Length; i++)
            {
                WcharBuf[i] = (WCHAR)(strAnsi.Buffer[i]);
            }
            Status = NDIS_STATUS_SUCCESS;
            
            if (NDIS_STATUS_SUCCESS == Status)
            {
                *(PUSHORT)InformationBuffer = 2 * strAnsi.Length;
                NdisRequest->DATA.QUERY_INFORMATION.BytesWritten = BytesNeeded ;
            }
            
            return Status;
            

        case OID_GEN_XMIT_OK:
        case OID_GEN_RCV_OK:
        case OID_GEN_XMIT_ERROR:
        case OID_GEN_RCV_ERROR:
        case OID_GEN_RCV_NO_BUFFER:
        case OID_GEN_RCV_CRC_ERROR:
        case OID_GEN_TRANSMIT_QUEUE_LENGTH:
        case OID_802_3_RCV_ERROR_ALIGNMENT:
        case OID_802_3_XMIT_ONE_COLLISION:
        case OID_802_3_XMIT_MORE_COLLISIONS:
        case OID_802_3_XMIT_DEFERRED:
        case OID_802_3_XMIT_MAX_COLLISIONS:
        case OID_802_3_RCV_OVERRUN:
        case OID_802_3_XMIT_UNDERRUN:
        case OID_802_3_XMIT_HEARTBEAT_FAILURE:
        case OID_802_3_XMIT_TIMES_CRS_LOST:
        case OID_802_3_XMIT_LATE_COLLISIONS:
        case OID_GEN_BYTES_RCV:
        case OID_GEN_BYTES_XMIT:
        case OID_GEN_RCV_DISCARDS:
            Status = NICGetStatsCounters(Adapter, Oid, &ul64Info);
            ulBytesAvailable = ulInfoLen = sizeof(ul64Info);
            if (Status == NDIS_STATUS_SUCCESS)
            {
                if (InformationBufferLength < sizeof(ULONG))
                {
                    Status = NDIS_STATUS_BUFFER_TOO_SHORT;
                    BytesNeeded = ulBytesAvailable;
                    break;
                }

                ulInfoLen = MIN(InformationBufferLength, ulBytesAvailable);
                pInfo = &ul64Info;
            }
                    
        break;         

        case OID_GEN_STATISTICS:
            // we are going to directly fill the information buffer
            DoCopy = FALSE;
            
            ulBytesAvailable = ulInfoLen = sizeof(NDIS_STATISTICS_INFO);
            if (InformationBufferLength < ulInfoLen)
            {
                break;
            }
            Status = NICGetStatsCounters(Adapter, Oid, (PULONG64)InformationBuffer);
            break;
            
        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }

    if (Status == NDIS_STATUS_SUCCESS)
    {
        BytesNeeded = ulBytesAvailable;
        if (ulInfoLen <= InformationBufferLength)
        {
            //
            // Copy result into InformationBuffer
            //
            BytesWritten = ulInfoLen;
            if (ulInfoLen && DoCopy)
            {
                NdisMoveMemory(InformationBuffer, pInfo, ulInfoLen);
            }
        }
        else
        {
            //
            // too short
            //
            BytesNeeded = ulInfoLen;
            Status = NDIS_STATUS_BUFFER_TOO_SHORT;
        }
    }
    NdisRequest->DATA.QUERY_INFORMATION.BytesWritten = BytesWritten;
    NdisRequest->DATA.QUERY_INFORMATION.BytesNeeded = BytesNeeded;

    DBGPRINT(MP_TRACE, ("<==== MPQueryInformation, OID=0x%08x, Status=%x\n", Oid, Status));

    return(Status);
}   

NDIS_STATUS NICGetStatsCounters(
    IN  PMP_ADAPTER  Adapter, 
    IN  NDIS_OID     Oid,
    OUT PULONG64     pCounter
    )
/*++
Routine Description:

    Get the value for a statistics OID

Arguments:

    Adapter     Pointer to our adapter 
    Oid         Self-explanatory   
    pCounter    Pointer to receive the value
    
Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    
--*/
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    PNDIS_STATISTICS_INFO StatisticsInfo;

    DBGPRINT(MP_TRACE, ("--> NICGetStatsCounters\n"));

    *pCounter = 0; 

    DumpStatsCounters(Adapter);
            
    switch(Oid)
    {
        case OID_GEN_XMIT_OK:
            *pCounter = Adapter->GoodTransmits;
            break;

        case OID_GEN_RCV_OK:
            *pCounter = Adapter->GoodReceives;
            break;

        case OID_GEN_XMIT_ERROR:
            *pCounter = Adapter->TxAbortExcessCollisions +
                        Adapter->TxDmaUnderrun +
                        Adapter->TxLostCRS +
                        Adapter->TxLateCollisions;
            break;

        case OID_GEN_RCV_ERROR:
            *pCounter = Adapter->RcvCrcErrors +
                        Adapter->RcvAlignmentErrors +
                        Adapter->RcvDmaOverrunErrors +
                        Adapter->RcvRuntErrors;
            break;

        case OID_GEN_RCV_NO_BUFFER:
            *pCounter = Adapter->RcvResourceErrors;
            break;

        case OID_GEN_RCV_CRC_ERROR:
            *pCounter = Adapter->RcvCrcErrors;
            break;

        case OID_GEN_TRANSMIT_QUEUE_LENGTH:
            *pCounter = Adapter->nWaitSend;
            break;

        case OID_802_3_RCV_ERROR_ALIGNMENT:
            *pCounter = Adapter->RcvAlignmentErrors;
            break;

        case OID_802_3_XMIT_ONE_COLLISION:
            *pCounter = Adapter->OneRetry;
            break;

        case OID_802_3_XMIT_MORE_COLLISIONS:
            *pCounter = Adapter->MoreThanOneRetry;
            break;

        case OID_802_3_XMIT_DEFERRED:
            *pCounter = Adapter->TxOKButDeferred;
            break;

        case OID_802_3_XMIT_MAX_COLLISIONS:
            *pCounter = Adapter->TxAbortExcessCollisions;
            break;

        case OID_802_3_RCV_OVERRUN:
            *pCounter = Adapter->RcvDmaOverrunErrors;
            break;

        case OID_802_3_XMIT_UNDERRUN:
            *pCounter = Adapter->TxDmaUnderrun;
            break;

        case OID_802_3_XMIT_HEARTBEAT_FAILURE:
            *pCounter = Adapter->TxLostCRS;
            break;

        case OID_802_3_XMIT_TIMES_CRS_LOST:
            *pCounter = Adapter->TxLostCRS;
            break;

        case OID_802_3_XMIT_LATE_COLLISIONS:
            *pCounter = Adapter->TxLateCollisions;
            break;

        case OID_GEN_RCV_DISCARDS:
            *pCounter = Adapter->RcvCrcErrors +
                        Adapter->RcvAlignmentErrors +
                        Adapter->RcvResourceErrors +
                        Adapter->RcvDmaOverrunErrors +
                        Adapter->RcvRuntErrors;;
            break;

        case OID_GEN_STATISTICS:

            StatisticsInfo = (PNDIS_STATISTICS_INFO)pCounter;
            StatisticsInfo->Header.Revision = NDIS_OBJECT_REVISION_1;
            StatisticsInfo->Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
            StatisticsInfo->Header.Size = sizeof(NDIS_STATISTICS_INFO);
            StatisticsInfo->SupportedStatistics = NDIS_STATISTICS_FLAGS_VALID_RCV_DISCARDS          |
                                                  NDIS_STATISTICS_FLAGS_VALID_RCV_ERROR             |
                                                  NDIS_STATISTICS_FLAGS_VALID_XMIT_ERROR;
                    
            
            StatisticsInfo->ifInDiscards = Adapter->RcvCrcErrors +
                                           Adapter->RcvAlignmentErrors +
                                           Adapter->RcvResourceErrors +
                                           Adapter->RcvDmaOverrunErrors +
                                           Adapter->RcvRuntErrors;
            
            StatisticsInfo->ifInErrors = StatisticsInfo->ifInDiscards -
                                         Adapter->RcvResourceErrors;
            
            StatisticsInfo->ifHCInOctets = 0;         
            StatisticsInfo->ifHCInUcastPkts = 0;
            StatisticsInfo->ifHCInMulticastPkts = 0;  
            StatisticsInfo->ifHCInBroadcastPkts = 0;  
            StatisticsInfo->ifHCOutOctets = 0;        
            StatisticsInfo->ifHCOutUCastPkts = 0;     
            StatisticsInfo->ifHCOutMulticastPkts = 0; 
            StatisticsInfo->ifHCOutBroadcastPkts = 0; 
            StatisticsInfo->ifOutErrors = Adapter->TxAbortExcessCollisions +
                                          Adapter->TxDmaUnderrun +
                                          Adapter->TxLostCRS +
                                          Adapter->TxLateCollisions;

            break;


        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }

    DBGPRINT(MP_TRACE, ("<-- NICGetStatsCounters\n"));

    return(Status);
}

NDIS_STATUS NICSetPacketFilter(
    IN PMP_ADAPTER Adapter,
    IN ULONG PacketFilter
    )
/*++
Routine Description:

    This routine will set up the adapter so that it accepts packets 
    that match the specified packet filter.  The only filter bits   
    that can truly be toggled are for broadcast and promiscuous     

Arguments:
    
    Adapter         Pointer to our adapter
    PacketFilter    The new packet filter 
    
Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    
--*/
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    UCHAR           NewParameterField;
    UINT            i;
    BOOLEAN         bResult;

    DBGPRINT(MP_TRACE, ("--> NICSetPacketFilter, PacketFilter=%08x\n", PacketFilter));

    //
    // Need to enable or disable broadcast and promiscuous support depending
    // on the new filter
    //
    NewParameterField = CB_557_CFIG_DEFAULT_PARM15;

    if (PacketFilter & NDIS_PACKET_TYPE_BROADCAST) 
    {
        NewParameterField &= ~CB_CFIG_BROADCAST_DIS;
    }
    else 
    {
        NewParameterField |= CB_CFIG_BROADCAST_DIS;
    }

    if (PacketFilter & NDIS_PACKET_TYPE_PROMISCUOUS) 
    {
        NewParameterField |= CB_CFIG_PROMISCUOUS;
    }
    else 
    {
        NewParameterField &= ~CB_CFIG_PROMISCUOUS;
    }

    do
    {
        if ((Adapter->OldParameterField == NewParameterField ) &&
            !(PacketFilter & NDIS_PACKET_TYPE_ALL_MULTICAST))
        {
            break;
        }

        //
        // Only need to do something to the HW if the filter bits have changed.
        //
        Adapter->OldParameterField = NewParameterField;
        ((PCB_HEADER_STRUC)Adapter->NonTxCmdBlock)->CbCommand = CB_CONFIGURE;
        ((PCB_HEADER_STRUC)Adapter->NonTxCmdBlock)->CbStatus = 0;
        ((PCB_HEADER_STRUC)Adapter->NonTxCmdBlock)->CbLinkPointer = DRIVER_NULL;

        //
        // First fill in the static (end user can't change) config bytes
        //
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[0] = CB_557_CFIG_DEFAULT_PARM0;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[2] = CB_557_CFIG_DEFAULT_PARM2;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[3] = CB_557_CFIG_DEFAULT_PARM3;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[6] = CB_557_CFIG_DEFAULT_PARM6;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[9] = CB_557_CFIG_DEFAULT_PARM9;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[10] = CB_557_CFIG_DEFAULT_PARM10;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[11] = CB_557_CFIG_DEFAULT_PARM11;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[12] = CB_557_CFIG_DEFAULT_PARM12;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[13] = CB_557_CFIG_DEFAULT_PARM13;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[14] = CB_557_CFIG_DEFAULT_PARM14;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[16] = CB_557_CFIG_DEFAULT_PARM16;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[17] = CB_557_CFIG_DEFAULT_PARM17;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[18] = CB_557_CFIG_DEFAULT_PARM18;
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[20] = CB_557_CFIG_DEFAULT_PARM20;

        //
        // Set the Tx underrun retries
        //
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[7] =
            (UCHAR) (CB_557_CFIG_DEFAULT_PARM7 | (Adapter->AiUnderrunRetry << 1));

        //
        // Set the Tx and Rx Fifo limits
        //
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[1] =
            (UCHAR) ((Adapter->AiTxFifo << 4) | Adapter->AiRxFifo);

        //
        // set the MWI enable bit if needed
        //
        if (Adapter->MWIEnable)
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[3] |= CB_CFIG_B3_MWI_ENABLE;

        //
        // Set the Tx and Rx DMA maximum byte count fields.
        //
        if ((Adapter->AiRxDmaCount) || (Adapter->AiTxDmaCount))
        {
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[4] =
                Adapter->AiRxDmaCount;
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[5] =
                (UCHAR) (Adapter->AiTxDmaCount | CB_CFIG_DMBC_EN);
        }
        else
        {
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[4] =
                CB_557_CFIG_DEFAULT_PARM4;
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[5] =
                CB_557_CFIG_DEFAULT_PARM5;
        }

        //
        // Setup for MII or 503 operation.  The CRS+CDT bit should only be
        // set when operating in 503 mode.
        //
        if (Adapter->PhyAddress == 32)
        {
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[8] =
                (CB_557_CFIG_DEFAULT_PARM8 & (~CB_CFIG_503_MII));
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[15] =
                (UCHAR) (NewParameterField | CB_CFIG_CRS_OR_CDT);
        }
        else
        {
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[8] =
                (CB_557_CFIG_DEFAULT_PARM8 | CB_CFIG_503_MII);
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[15] =
                (UCHAR) (NewParameterField & (~CB_CFIG_CRS_OR_CDT));
        }

        //
        // Setup Full duplex stuff
        //

        //
        // If forced to half duplex
        //
        if (Adapter->AiForceDpx == 1) 
    	{
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
                (CB_557_CFIG_DEFAULT_PARM19 &
                (~(CB_CFIG_FORCE_FDX| CB_CFIG_FDX_ENABLE)));
        }
        //
        // If forced to full duplex
        //
        else if (Adapter->AiForceDpx == 2)
	    {
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
                (CB_557_CFIG_DEFAULT_PARM19 | CB_CFIG_FORCE_FDX);
        }
        //
        // If auto-duplex
        //
        else 
    	{
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
                                                CB_557_CFIG_DEFAULT_PARM19;
        }

        //
        // if multicast all is being turned on, set the bit
        //
        if (PacketFilter & NDIS_PACKET_TYPE_ALL_MULTICAST) 
	    {
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[21] =
                                 (CB_557_CFIG_DEFAULT_PARM21 | CB_CFIG_MULTICAST_ALL);
        }
        else 
    	{
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[21] =
                                                CB_557_CFIG_DEFAULT_PARM21;
        }


        //
        // Wait for the SCB to clear before we check the CU status.
        //
        if (!WaitScb(Adapter))
        {
            Status = NDIS_STATUS_HARD_ERRORS;
            break;
        }

        //
        // If we have issued any transmits, then the CU will either be active,
        // or in the suspended state.  If the CU is active, then we wait for
        // it to be suspended.
        //
        if (Adapter->TransmitIdle == FALSE)
        {
            //
            // Wait for suspended state
            //
            MP_STALL_AND_WAIT((Adapter->CSRAddress->ScbStatus & SCB_CUS_MASK) != SCB_CUS_ACTIVE, 5000, bResult);
            if (!bResult)
            {
                MP_SET_HARDWARE_ERROR(Adapter);
                Status = NDIS_STATUS_HARD_ERRORS;
                break;
            }

            //
            // Check the current status of the receive unit
            //
            if ((Adapter->CSRAddress->ScbStatus & SCB_RUS_MASK) != SCB_RUS_IDLE)
            {
                // Issue an RU abort.  Since an interrupt will be issued, the
                // RU will be started by the DPC.
                Status = D100IssueScbCommand(Adapter, SCB_RUC_ABORT, TRUE);
                if (Status != NDIS_STATUS_SUCCESS)
                {
                    break;
                }
            }
            
            if (!WaitScb(Adapter))
            {
                Status = NDIS_STATUS_HARD_ERRORS;
                break;
            }
           
            //
            // Restore the transmit software flags.  After the multicast
            // command is issued, the command unit will be idle, because the
            // EL bit will be set in the multicast commmand block.
            //
            Adapter->TransmitIdle = TRUE;
            Adapter->ResumeWait = TRUE;
        }
        
        //
        // Display config info
        //
        DBGPRINT(MP_INFO, ("Re-Issuing Configure command for filter change\n"));
        DBGPRINT(MP_INFO, ("Config Block at virt addr "PTR_FORMAT", phys address %x\n",
            &((PCB_HEADER_STRUC)Adapter->NonTxCmdBlock)->CbStatus, Adapter->NonTxCmdBlockPhys));

        for (i = 0; i < CB_CFIG_BYTE_COUNT; i++)
            DBGPRINT(MP_INFO, ("  Config byte %x = %.2x\n", i, Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[i]));

        //
        // Submit the configure command to the chip, and wait for it to complete.
        //
        Adapter->CSRAddress->ScbGeneralPointer = Adapter->NonTxCmdBlockPhys;
        Status = D100SubmitCommandBlockAndWait(Adapter);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            Status = NDIS_STATUS_NOT_ACCEPTED;
        }

    } while (FALSE);

    DBGPRINT_S(Status, ("<-- NICSetPacketFilter, Status=%x\n", Status));

    return(Status);
}

NDIS_STATUS NICSetMulticastList(
    IN  PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    This routine will set up the adapter for a specified multicast address list
    
Arguments:
    
    Adapter     Pointer to our adapter
    
Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_ACCEPTED
    
--*/
{
    NDIS_STATUS     Status;
    PUCHAR          McAddress;
    UINT            i, j;
    BOOLEAN         bResult;

    DBGPRINT(MP_TRACE, ("--> NICSetMulticastList\n"));

    //
    // Setup the command block for the multicast command.
    //
    for (i = 0; i < Adapter->MCAddressCount; i++)
    {
        DBGPRINT(MP_INFO, ("MC(%d) = %02x-%02x-%02x-%02x-%02x-%02x\n", 
            i,
            Adapter->MCList[i][0],
            Adapter->MCList[i][1],
            Adapter->MCList[i][2],
            Adapter->MCList[i][3],
            Adapter->MCList[i][4],
            Adapter->MCList[i][5]));

        McAddress = &Adapter->NonTxCmdBlock->NonTxCb.Multicast.McAddress[i*ETHERNET_ADDRESS_LENGTH];

        for (j = 0; j < ETH_LENGTH_OF_ADDRESS; j++)
            *(McAddress++) = Adapter->MCList[i][j];
    }

    Adapter->NonTxCmdBlock->NonTxCb.Multicast.McCount =
        (USHORT)(Adapter->MCAddressCount * ETH_LENGTH_OF_ADDRESS);
    ((PCB_HEADER_STRUC)Adapter->NonTxCmdBlock)->CbStatus = 0;
    ((PCB_HEADER_STRUC)Adapter->NonTxCmdBlock)->CbCommand = CB_MULTICAST;

    //
    // Wait for the SCB to clear before we check the CU status.
    //
    if (!WaitScb(Adapter))
    {
        Status = NDIS_STATUS_HARD_ERRORS;
        MP_EXIT;
    }

    //
    // If we have issued any transmits, then the CU will either be active, or
    // in the suspended state.  If the CU is active, then we wait for it to be
    // suspended.
    //
    if (Adapter->TransmitIdle == FALSE)
    {
        //
        // Wait for suspended state
        //
        MP_STALL_AND_WAIT((Adapter->CSRAddress->ScbStatus & SCB_CUS_MASK) != SCB_CUS_ACTIVE, 5000, bResult);
        if (!bResult)
        {
            MP_SET_HARDWARE_ERROR(Adapter);
            Status = NDIS_STATUS_HARD_ERRORS;
        }

        //
        // Restore the transmit software flags.  After the multicast command is
        // issued, the command unit will be idle, because the EL bit will be
        // set in the multicast commmand block.
        //
        Adapter->TransmitIdle = TRUE;
        Adapter->ResumeWait = TRUE;
    }

    //
    // Update the command list pointer.
    //
    Adapter->CSRAddress->ScbGeneralPointer = Adapter->NonTxCmdBlockPhys;

    //
    // Submit the multicast command to the adapter and wait for it to complete.
    //
    Status = D100SubmitCommandBlockAndWait(Adapter);
    if (Status != NDIS_STATUS_SUCCESS)
    {
        Status = NDIS_STATUS_NOT_ACCEPTED;
    }
    
    exit:

    DBGPRINT_S(Status, ("<-- NICSetMulticastList, Status=%x\n", Status));

    return(Status);

}

NDIS_STATUS MpSetInformation(
    IN NDIS_HANDLE           MiniportAdapterContext,
    IN PNDIS_OID_REQUEST     NdisRequest
    )
/*++
Routine Description:

    This is the handler for an OID set operation.
    The only operations that really change the configuration of the adapter are
    set PACKET_FILTER, and SET_MULTICAST.       
    
Arguments:
    
    MiniportAdapterContext  Pointer to the adapter structure
    NdisRequest             Pointer to the request needed to process
    
Return Value:

    NDIS_STATUS_SUCCESS        
    NDIS_STATUS_INVALID_LENGTH 
    NDIS_STATUS_INVALID_OID    
    NDIS_STATUS_NOT_SUPPORTED  
    NDIS_STATUS_NOT_ACCEPTED   
    
--*/
{
    NDIS_STATUS                 Status = NDIS_STATUS_SUCCESS;
    PMP_ADAPTER                 Adapter = (PMP_ADAPTER) MiniportAdapterContext;
    NDIS_OID                    Oid;
    PVOID                       InformationBuffer;
    ULONG                       InformationBufferLength;
    ULONG                       BytesRead;
    ULONG                       BytesNeeded;
    
    ULONG                       PacketFilter;
    NDIS_DEVICE_POWER_STATE     NewPowerState;
    ULONG                       CustomDriverSet;
    
    DBGPRINT(MP_TRACE, ("====> MPSetInformation\n"));

    Oid = NdisRequest->DATA.SET_INFORMATION.Oid;
    InformationBuffer = NdisRequest->DATA.SET_INFORMATION.InformationBuffer;
    InformationBufferLength = NdisRequest->DATA.SET_INFORMATION.InformationBufferLength;

    BytesRead = 0;
    BytesNeeded = 0;

    switch(Oid)
    {
        case OID_802_3_MULTICAST_LIST:
            //
            // Verify the length
            //
            if (InformationBufferLength % ETH_LENGTH_OF_ADDRESS != 0)
            {
                return(NDIS_STATUS_INVALID_LENGTH);
            }

            //
            // Save the number of MC list size
            //
            Adapter->MCAddressCount = InformationBufferLength / ETH_LENGTH_OF_ADDRESS;
            ASSERT(Adapter->MCAddressCount <= NIC_MAX_MCAST_LIST);

            //
            // Save the MC list
            //
            NdisMoveMemory(
                Adapter->MCList, 
                InformationBuffer, 
                InformationBufferLength);

            BytesRead = InformationBufferLength;
            NdisAcquireSpinLock(&Adapter->Lock);
            NdisAcquireSpinLock(&Adapter->RcvLock);
            
            Status = NICSetMulticastList(Adapter);

            NdisReleaseSpinLock(&Adapter->RcvLock);
            NdisReleaseSpinLock(&Adapter->Lock);
            break;

        case OID_GEN_CURRENT_PACKET_FILTER:
            //
            // Verify the Length
            //
            if (InformationBufferLength != sizeof(ULONG))
            {
                return(NDIS_STATUS_INVALID_LENGTH);
            }

            BytesRead = InformationBufferLength;

            NdisMoveMemory(&PacketFilter,
                          InformationBuffer,
                          sizeof(ULONG));

            //
            // any bits not supported?
            //
            if (PacketFilter & ~NIC_SUPPORTED_FILTERS)
            {
                return(NDIS_STATUS_NOT_SUPPORTED);
            }

            //
            // any filtering changes?
            //
            if (PacketFilter == Adapter->PacketFilter)
            {
                return(NDIS_STATUS_SUCCESS);
            }

            NdisAcquireSpinLock(&Adapter->Lock);
            NdisAcquireSpinLock(&Adapter->RcvLock);
            
            if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION))
            {
                ASSERT(Adapter->PendingRequest == NULL);
                Adapter->PendingRequest = NdisRequest;
                NdisReleaseSpinLock(&Adapter->RcvLock);
                NdisReleaseSpinLock(&Adapter->Lock);
                Status = NDIS_STATUS_PENDING;   
                break;
            }

            Status = NICSetPacketFilter(
                         Adapter,
                         PacketFilter);

            NdisReleaseSpinLock(&Adapter->RcvLock);
            NdisReleaseSpinLock(&Adapter->Lock);
            if (Status == NDIS_STATUS_SUCCESS)
            {
                Adapter->PacketFilter = PacketFilter;
            }

            break;

        case OID_GEN_CURRENT_LOOKAHEAD:
            //
            // Verify the Length
            //
            if (InformationBufferLength < sizeof(ULONG))
            {
                BytesNeeded = sizeof(ULONG);
                Status = NDIS_STATUS_INVALID_LENGTH;
                break;
            }

            NdisMoveMemory(&Adapter->ulLookAhead, InformationBuffer, sizeof(ULONG));
            
            BytesRead = sizeof(ULONG);
            Status = NDIS_STATUS_SUCCESS;
            break;


        case OID_PNP_SET_POWER:

            DBGPRINT(MP_LOUD, ("SET: Power State change, "PTR_FORMAT"!!!\n", InformationBuffer));

            if (InformationBufferLength != sizeof(NDIS_DEVICE_POWER_STATE ))
            {
                return(NDIS_STATUS_INVALID_LENGTH);
            }

            NewPowerState = *(PNDIS_DEVICE_POWER_STATE UNALIGNED)InformationBuffer;

            //
            // Set the power state - Cannot fail this request
            //
            Status = MPSetPower(Adapter ,NewPowerState );
            if (Status == NDIS_STATUS_PENDING)
            {
                Adapter->PendingRequest = NdisRequest;
                break;
            }
            if (Status != NDIS_STATUS_SUCCESS)
            {
                DBGPRINT(MP_ERROR, ("SET power: Hardware error !!!\n"));
                break;
            }
                    
        
            BytesRead = sizeof(NDIS_DEVICE_POWER_STATE    );
            Status = NDIS_STATUS_SUCCESS; 
            break;

        case OID_PNP_ADD_WAKE_UP_PATTERN:
            //
            // call a function that would program the adapter's wake
            // up pattern, return success
            //
            DBGPRINT(MP_LOUD, ("SET: Add Wake Up Pattern, !!!\n"));

            if (MPIsPoMgmtSupported(Adapter) )
            {
                Status = MPAddWakeUpPattern(Adapter,
                                            InformationBuffer, 
                                            InformationBufferLength, 
                                            &BytesRead, 
                                            &BytesNeeded);      
            }
            else
            {
                Status = NDIS_STATUS_NOT_SUPPORTED;
            }
            break;

    
        case OID_PNP_REMOVE_WAKE_UP_PATTERN:
            DBGPRINT(MP_LOUD, ("SET: Got a WakeUpPattern REMOVE Call\n"));
            //
            // call a function that would remove the adapter's wake
            // up pattern, return success
            //
            if (MPIsPoMgmtSupported(Adapter) )
            {
                Status = MPRemoveWakeUpPattern(Adapter, 
                                               InformationBuffer, 
                                               InformationBufferLength,
                                               &BytesRead,
                                               &BytesNeeded);
            }
            else
            {
                Status = NDIS_STATUS_NOT_SUPPORTED;
            }
            break;

        case OID_PNP_ENABLE_WAKE_UP:
            DBGPRINT(MP_LOUD, ("SET: Got a EnableWakeUp Call, "PTR_FORMAT"\n",InformationBuffer));
            //
            // call a function that would enable wake up on the adapter
            // return success
            //
            if (MPIsPoMgmtSupported(Adapter) )
            {
                ULONG       WakeUpEnable;
                NdisMoveMemory(&WakeUpEnable, InformationBuffer,sizeof(ULONG));
                //
                // The WakeUpEable can only be 0, or NDIS_PNP_WAKE_UP_PATTERN_MATCH since the driver only
                // supports wake up pattern match
                //
                if ((WakeUpEnable != 0)
                       && ((WakeUpEnable & NDIS_PNP_WAKE_UP_PATTERN_MATCH) != NDIS_PNP_WAKE_UP_PATTERN_MATCH ))
                {
                    Status = NDIS_STATUS_NOT_SUPPORTED;
                    Adapter->WakeUpEnable = 0;    
                    break;
                }
                //
                // When the driver goes to low power state, it would check WakeUpEnable to decide
                // which wake up methed it should use to wake up the machine. If WakeUpEnable is 0,
                // no wake up method is enabled.
                //
                Adapter->WakeUpEnable = WakeUpEnable;
                
                BytesRead = sizeof(ULONG);   
                Status = NDIS_STATUS_SUCCESS; 
            }
            else
            {
                Status = NDIS_STATUS_NOT_SUPPORTED;
            }

            break;

            //
            // this OID is for showing how to work with driver specific (custom)
            // OIDs and the NDIS 5 WMI interface using GUIDs
            //
        case OID_CUSTOM_DRIVER_SET:
            DBGPRINT(MP_INFO, ("OID_CUSTOM_DRIVER_SET got a set\n"));
            if (InformationBufferLength < sizeof(ULONG))
            {
                BytesNeeded = sizeof(ULONG);
                Status = NDIS_STATUS_BUFFER_TOO_SHORT;
                break;
            }
            //
            // The driver need to validate the set data in the buffer
            //
            NdisMoveMemory(&CustomDriverSet, InformationBuffer, sizeof(ULONG));
            if ((CustomDriverSet < CUSTOM_DRIVER_SET_MIN) 
                || (CustomDriverSet > CUSTOM_DRIVER_SET_MAX))
            {
               Status = NDIS_STATUS_INVALID_DATA;
               break;
            }
            BytesRead = sizeof(ULONG);
            
            Adapter->CustomDriverSet = CustomDriverSet;
            break;

        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;

    }

    if (Status == NDIS_STATUS_SUCCESS)
    {
        NdisRequest->DATA.SET_INFORMATION.BytesRead = BytesRead;
    }
    NdisRequest->DATA.SET_INFORMATION.BytesNeeded = BytesNeeded;

    DBGPRINT(MP_TRACE, ("<==== MpSetInformationSet, OID=0x%08x, Status=%x\n", Oid, Status));

    return(Status);
}


VOID
MPSetPowerD0(
    PMP_ADAPTER  Adapter
    )
/*++
Routine Description:

    This routine is called when the adapter receives a SetPower 
    to D0.
    
Arguments:
    
    Adapter                 Pointer to the adapter structure
    PowerState              NewPowerState
    
Return Value:

    
--*/
{
    NDIS_STATUS    Status;

    //
    // MPSetPowerD0Private initializes the adapter, issues a selective reset
    // 
    MPSetPowerD0Private (Adapter);       
    Adapter->CurrentPowerState = NdisDeviceStateD0;

    //
    // Set up the packet filter
    //
    NdisAcquireSpinLock(&Adapter->Lock);
    Status = NICSetPacketFilter(
                Adapter, 
                Adapter->OldPacketFilter);
    //
    // If set packet filter succeeds, restore the old packet filter
    //
    if (Status == NDIS_STATUS_SUCCESS)
    {
        Adapter->PacketFilter = Adapter->OldPacketFilter;
    }

    //
    // Set up the multicast list address
    //
    NdisAcquireSpinLock(&Adapter->RcvLock);
    Status = NICSetMulticastList(Adapter);
    NICStartRecv(Adapter);
    NdisReleaseSpinLock(&Adapter->RcvLock);
    NdisReleaseSpinLock(&Adapter->Lock);

    //
    // Enable the interrupt, so the driver can send/receive packets
    //
    NICEnableInterrupt(Adapter);
}

NDIS_STATUS
MPSetPowerLow(
    PMP_ADAPTER              Adapter ,
    NDIS_DEVICE_POWER_STATE  PowerState 
    )
/*++
Routine Description:

    This routine is called when the adapter receives a SetPower 
    to a PowerState > D0
    
Arguments:
    
    Adapter                 Pointer to the adapter structure
    PowerState              NewPowerState
    
Return Value:
    
    NDIS_STATUS_SUCCESS
    NDIS_STATUS_PENDING
    NDIS_STATUS_HARDWARE_ERRORS

    
--*/
{

    NDIS_STATUS Status = NDIS_STATUS_SUCCESS;

    do
    {
        Adapter->NextPowerState = PowerState;

        //        
        // Stop sending packets. Create a new flag and make it part 
        // of the Send Fail Mask
        //

        //
        // Stop hardware from receiving packets - Set the RU to idle 
        //
        
        //
        // Check the current status of the receive unit
        //
        if ((Adapter->CSRAddress->ScbStatus & SCB_RUS_MASK) != SCB_RUS_IDLE)
        {
            //
            // Issue an RU abort.  Since an interrupt will be issued, the
            // RU will be started by the DPC.
            //
            Status = D100IssueScbCommand(Adapter, SCB_RUC_ABORT, TRUE);
        }

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        //
        // If there are any outstanding receive packets, return NDIS_STATUS_PENDING.
        // When all the packets are returned later, the driver will complete the request.
        //
        if (Adapter->PoMgmt.OutstandingRecv != 0)
        {
            Status = NDIS_STATUS_PENDING;
            break;
        }

        //
        // Wait for all incoming sends to complete
        //

        //
        // MPSetPowerLowPrivate first disables the interrupt, acknowledges all the pending 
        // interrupts and sets pAdapter->CurrentPowerState to the given low power state
        // then starts Hardware specific part of the transition to low power state
        // Setting up wake-up patterns, filters, wake-up events etc
        //
        NdisMSynchronizeWithInterruptEx(
                Adapter->NdisInterruptHandle,
                0,
                (PVOID)MPSetPowerLowPrivate,
                Adapter);

        Status = NDIS_STATUS_SUCCESS;

    } while (FALSE);

    return Status;
}

VOID
MpSetPowerLowComplete(
    IN PMP_ADAPTER Adapter
    )
/*++
Routine Description:
    This routine is called when all the packets are returned to the driver and the driver has 
    a pending OID_PNP_SET_POWER request to set it to lower power state 

Arguments:

    Adapter                 Pointer to the adapter structure

Return Value:
    NOTE: this function is called with RcvLock held

--*/
{
    NDIS_STATUS        Status = NDIS_STATUS_SUCCESS;
    PNDIS_OID_REQUEST  NdisRequest;

    NdisReleaseSpinLock(&Adapter->RcvLock);
    //
    // MPSetPowerLowPrivate first disables the interrupt, acknowledges all the pending 
    // interrupts and sets pAdapter->CurrentPowerState to the given low power state
    // then starts Hardware specific part of the transition to low power state
    // Setting up wake-up patterns, filters, wake-up events etc
    //
    NdisMSynchronizeWithInterruptEx(
                        Adapter->NdisInterruptHandle,
                        0,
                        (PVOID)MPSetPowerLowPrivate,
                        Adapter);

    NdisAcquireSpinLock(&Adapter->Lock);

    NdisRequest = Adapter->PendingRequest;
    Adapter->PendingRequest = NULL;

    NdisReleaseSpinLock(&Adapter->Lock);

    if (NdisRequest != NULL)
    {
        NdisRequest->DATA.SET_INFORMATION.BytesRead = sizeof(NDIS_DEVICE_POWER_STATE);
        NdisMRequestComplete(Adapter->AdapterHandle, NdisRequest, Status);
    }

    NdisAcquireSpinLock(&Adapter->RcvLock);
}
    

NDIS_STATUS
MPSetPower(
    PMP_ADAPTER     Adapter ,
    NDIS_DEVICE_POWER_STATE   PowerState 
    )
/*++
Routine Description:

    This routine is called when the adapter receives a SetPower 
    request. It redirects the call to an appropriate routine to
    Set the New PowerState
    
Arguments:
    
    Adapter                 Pointer to the adapter structure
    PowerState              NewPowerState
    
Return Value:
 
    NDIS_STATUS_SUCCESS
    NDIS_STATUS_PENDING
    NDIS_STATUS_HARDWARE_ERRORS

    
--*/
{
    NDIS_STATUS       Status = NDIS_STATUS_SUCCESS;
    
    if (PowerState == NdisDeviceStateD0)
    {
        MPSetPowerD0 (Adapter);
    }
    else
    {
        Status = MPSetPowerLow (Adapter, PowerState);
    }

    return Status;
}


VOID
MPFillPoMgmtCaps (
    IN PMP_ADAPTER                 pAdapter, 
    IN OUT PNDIS_PNP_CAPABILITIES  pPower_Management_Capabilities, 
    IN OUT PNDIS_STATUS            pStatus,
    IN OUT PULONG                  pulInfoLen
    )
/*++
Routine Description:

    Fills in the Power  Managment structure depending the capabilities of 
    the software driver and the card.

    Currently this is only supported on 82559 Version of the driver

Arguments:
    
    Adapter                 Pointer to the adapter structure
    pPower_Management_Capabilities - Power management struct as defined in the DDK, 
    pStatus                 Status to be returned by the request,
    pulInfoLen              Length of the pPowerManagmentCapabilites
    
Return Value:

    Success or failure depending on the type of card
--*/

{

    BOOLEAN bIsPoMgmtSupported; 
    
    bIsPoMgmtSupported = MPIsPoMgmtSupported(pAdapter);

    if (bIsPoMgmtSupported == TRUE)
    {
        pPower_Management_Capabilities->Flags = NDIS_DEVICE_WAKE_UP_ENABLE ;
        pPower_Management_Capabilities->WakeUpCapabilities.MinMagicPacketWakeUp = NdisDeviceStateUnspecified;
        pPower_Management_Capabilities->WakeUpCapabilities.MinPatternWakeUp = NdisDeviceStateD3;
        pPower_Management_Capabilities->WakeUpCapabilities.MinLinkChangeWakeUp  = NdisDeviceStateUnspecified;
        *pulInfoLen = sizeof (*pPower_Management_Capabilities);
        *pStatus = NDIS_STATUS_SUCCESS;
    }
    else
    {
        NdisZeroMemory (pPower_Management_Capabilities, sizeof(*pPower_Management_Capabilities));
        *pStatus = NDIS_STATUS_NOT_SUPPORTED;
        *pulInfoLen = 0;
            
    }
}

NDIS_STATUS
MPAddWakeUpPattern(
    IN PMP_ADAPTER  pAdapter,
    IN PVOID        InformationBuffer, 
    IN UINT         InformationBufferLength,
    OUT PULONG      BytesRead,
    OUT PULONG      BytesNeeded   
    )
/*++
Routine Description:

    This routine will allocate a local memory structure, copy the pattern, 
    insert the pattern into a linked list and return success

    We are gauranteed that we wll get only one request at a time, so this is implemented
    without locks.
    
Arguments:
    
    Adapter                 Adapter structure
    InformationBuffer       Wake up Pattern
    InformationBufferLength Wake Up Pattern Length
    
Return Value:

    Success - if successful.
    NDIS_STATUS_FAILURE - if memory allocation fails. 
    
--*/
{

    NDIS_STATUS             Status = NDIS_STATUS_FAILURE;
    PMP_WAKE_PATTERN        pWakeUpPattern = NULL;
    UINT                    AllocationLength = 0;
    PNDIS_PM_PACKET_PATTERN pPmPattern = NULL;
    ULONG                   Signature = 0;
    ULONG                   CopyLength = 0;
    
    do
    {
        pPmPattern = (PNDIS_PM_PACKET_PATTERN) InformationBuffer;

        if (InformationBufferLength < sizeof(NDIS_PM_PACKET_PATTERN))
        {
            Status = NDIS_STATUS_BUFFER_TOO_SHORT;
            
            *BytesNeeded = sizeof(NDIS_PM_PACKET_PATTERN);
            break;
        }
        if (InformationBufferLength < pPmPattern->PatternOffset + pPmPattern->PatternSize)
        {
            Status = NDIS_STATUS_BUFFER_TOO_SHORT;
            
            *BytesNeeded = pPmPattern->PatternOffset + pPmPattern->PatternSize;
            break;
        }
        
        *BytesRead = pPmPattern->PatternOffset + pPmPattern->PatternSize;
        
        //
        // Calculate the e100 signature
        //
        Status = MPCalculateE100PatternForFilter (
            (PUCHAR)pPmPattern+ pPmPattern->PatternOffset,
            pPmPattern->PatternSize,
            (PUCHAR)pPmPattern +sizeof(NDIS_PM_PACKET_PATTERN),
            pPmPattern->MaskSize,
            &Signature );
        
        if ( Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        CopyLength = pPmPattern->PatternOffset + pPmPattern->PatternSize;
        
        //
        // Allocate the memory to hold the WakeUp Pattern
        //
        AllocationLength = sizeof (MP_WAKE_PATTERN) + CopyLength;

        pWakeUpPattern = MP_ALLOCMEMTAG(pAdapter->AdapterHandle, AllocationLength);
        
        if (pWakeUpPattern == NULL)
        {
            Status = NDIS_STATUS_RESOURCES;
            break;
        }

        //
        // Initialize pWakeUpPattern
        //
        NdisZeroMemory (pWakeUpPattern, AllocationLength);

        pWakeUpPattern->AllocationSize = AllocationLength;
        
        pWakeUpPattern->Signature = Signature;

        //
        // Copy the pattern into local memory
        //
        NdisMoveMemory (&pWakeUpPattern->Pattern[0], InformationBuffer, CopyLength);
            
        //
        // Insert the pattern into the list 
        //
        NdisInterlockedInsertHeadList (&pAdapter->PoMgmt.PatternList, 
                                        &pWakeUpPattern->linkListEntry, 
                                        &pAdapter->Lock);

        Status = NDIS_STATUS_SUCCESS;

    } while (FALSE);

    return Status;
}

NDIS_STATUS
MPRemoveWakeUpPattern(
    IN PMP_ADAPTER  pAdapter,
    IN PVOID        InformationBuffer, 
    IN UINT         InformationBufferLength,
    OUT PULONG      BytesRead,
    OUT PULONG      BytesNeeded
    )
/*++
Routine Description:

    This routine will walk the list of wake up pattern and attempt to match the wake up pattern. 
    If it finds a copy , it will remove that WakeUpPattern     

Arguments:
    
    Adapter                 Adapter structure
    InformationBuffer       Wake up Pattern
    InformationBufferLength Wake Up Pattern Length
    
Return Value:

    Success - if successful.
    NDIS_STATUS_FAILURE - if memory allocation fails. 
    
--*/
{

    NDIS_STATUS              Status = NDIS_STATUS_FAILURE;
    PNDIS_PM_PACKET_PATTERN  pReqPattern = (PNDIS_PM_PACKET_PATTERN)InformationBuffer;
    PLIST_ENTRY              pPatternEntry = ListNext(&pAdapter->PoMgmt.PatternList) ;

    do
    {
        if (InformationBufferLength < sizeof(NDIS_PM_PACKET_PATTERN))
        {
            Status = NDIS_STATUS_BUFFER_TOO_SHORT;
            
            *BytesNeeded = sizeof(NDIS_PM_PACKET_PATTERN);
            break;
        }
        if (InformationBufferLength < pReqPattern->PatternOffset + pReqPattern->PatternSize)
        {
            Status = NDIS_STATUS_BUFFER_TOO_SHORT;
            
            *BytesNeeded = pReqPattern->PatternOffset + pReqPattern->PatternSize;
            break;
        }
        
        *BytesRead = pReqPattern->PatternOffset + pReqPattern->PatternSize;
    
        while (pPatternEntry != (&pAdapter->PoMgmt.PatternList))
        {
            BOOLEAN                  bIsThisThePattern = FALSE;
            PMP_WAKE_PATTERN         pWakeUpPattern = NULL;
            PNDIS_PM_PACKET_PATTERN  pCurrPattern = NULL;;

            //
            // initialize local variables
            //
            pWakeUpPattern = CONTAINING_RECORD(pPatternEntry, MP_WAKE_PATTERN, linkListEntry);

            pCurrPattern = (PNDIS_PM_PACKET_PATTERN)&pWakeUpPattern->Pattern[0];

            //
            // increment the iterator
            //
            pPatternEntry = ListNext (pPatternEntry);

            //
            // Begin Check : Is (pCurrPattern  == pReqPattern) 
            //
            bIsThisThePattern = MPAreTwoPatternsEqual(pReqPattern, pCurrPattern);
                                                      

            if (bIsThisThePattern == TRUE)
            {
                //
                // we have a match - remove the entry
                //
                RemoveEntryList (&pWakeUpPattern->linkListEntry);

                //
                // Free the entry
                //
                MP_FREEMEM (pWakeUpPattern);
                
                Status = NDIS_STATUS_SUCCESS;
                break;
            }

        } 
    }
    while (FALSE);
    
    return Status;
}

VOID
MPRemoveAllWakeUpPatterns(
    PMP_ADAPTER pAdapter
    )
/*++
Routine Description:

    This routine will walk the list of wake up pattern and free it 

Arguments:
    
    Adapter                 Adapter structure
    
Return Value:

    Success - if successful.
    
--*/
{

    PLIST_ENTRY  pPatternEntry = ListNext(&pAdapter->PoMgmt.PatternList) ;
    
    while (pPatternEntry != (&pAdapter->PoMgmt.PatternList))
    {
        PMP_WAKE_PATTERN  pWakeUpPattern = NULL;

        //
        // initialize local variables
        //
        pWakeUpPattern = CONTAINING_RECORD(pPatternEntry, MP_WAKE_PATTERN,linkListEntry);

        //
        // increment the iterator
        //
        pPatternEntry = ListNext (pPatternEntry);
       
        //
        // Remove the entry from the list
        //
        RemoveEntryList (&pWakeUpPattern->linkListEntry);

        //
        // Free the memory
        //
        MP_FREEMEM (pWakeUpPattern);
    } 
}

BOOLEAN 
MPAreTwoPatternsEqual(
    IN PNDIS_PM_PACKET_PATTERN pNdisPattern1,
    IN PNDIS_PM_PACKET_PATTERN pNdisPattern2
    )
/*++
Routine Description:

    This routine will compare two wake up patterns to see if they are equal

Arguments:
    
    pNdisPattern1 - Pattern1 
    pNdisPattern2 - Pattern 2
    
    
Return Value:

    True - if patterns are equal
    False - Otherwise
--*/
{
    BOOLEAN bEqual = FALSE;

    // Local variables used later in the compare section of this function
    PUCHAR  pMask1, pMask2;
    PUCHAR  pPattern1, pPattern2;
    UINT    MaskSize, PatternSize;

    do
    {
    	
        bEqual = (BOOLEAN)(pNdisPattern1->Priority == pNdisPattern2->Priority);

        if (bEqual == FALSE)
        {
            break;
        }

        bEqual = (BOOLEAN)(pNdisPattern1->MaskSize == pNdisPattern2->MaskSize);
        if (bEqual == FALSE)
        {
            break;
        }

        //
        // Verify the Mask 
        //
        MaskSize = pNdisPattern1->MaskSize ; 
        pMask1 = (PUCHAR) pNdisPattern1 + sizeof (NDIS_PM_PACKET_PATTERN);
        pMask2 = (PUCHAR) pNdisPattern2 + sizeof (NDIS_PM_PACKET_PATTERN);
        
        bEqual = (BOOLEAN)NdisEqualMemory (pMask1, pMask2, MaskSize);

        if (bEqual == FALSE)
        {
            break;
        }

        //
        // Verify the Pattern
        //
        bEqual = (BOOLEAN)(pNdisPattern1->PatternSize == pNdisPattern2->PatternSize);
        
        if (bEqual == FALSE)
        {
            break;
        }

        PatternSize = pNdisPattern2->PatternSize;
        pPattern1 = (PUCHAR) pNdisPattern1 + pNdisPattern1->PatternOffset;
        pPattern2 = (PUCHAR) pNdisPattern2 + pNdisPattern2->PatternOffset;
        
        bEqual  = (BOOLEAN)NdisEqualMemory (pPattern1, pPattern2, PatternSize );

        if (bEqual == FALSE)
        {
            break;
        }

    } while (FALSE);

    return bEqual;
}

#define     ADD_TWO_INTEGERS        1
#define     MINUS_TWO_INTEGERS      2

NDIS_STATUS
MpMethodRequest(
    IN  PMP_ADAPTER            Adapter,
    IN  PNDIS_OID_REQUEST      Request
    )
/*++
Routine Description:

    WMI method request handler            

Arguments:

    MiniportAdapterContext  Pointer to the adapter structure
    Request                 Piointer to the request sent down by NDIS
    
Return Value:
    
    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    NDIS_STATUS_BUFFER_TOO_SHORT
    NDIS_STATUS_XXX
    
--*/
{

    NDIS_OID                Oid;
    ULONG                   MethodId;
    PVOID                   InformationBuffer;
    ULONG                   InputBufferLength;
    ULONG                   OutputBufferLength;
    NDIS_STATUS             Status = NDIS_STATUS_SUCCESS;
    ULONG                   FirstInt;
    ULONG                   SecondInt;
    ULONG                   BytesNeeded = 0;
    ULONG                   BytesWritten = 0;
    ULONG                   BytesRead = 0;

    
    DBGPRINT(MP_TRACE, ("====> MpMethodRequest\n"));
    
    Oid = Request->DATA.METHOD_INFORMATION.Oid;
    InformationBuffer = (PVOID)(Request->DATA.METHOD_INFORMATION.InformationBuffer);
    InputBufferLength = Request->DATA.METHOD_INFORMATION.InputBufferLength;
    OutputBufferLength = Request->DATA.METHOD_INFORMATION.OutputBufferLength;
    MethodId = Request->DATA.METHOD_INFORMATION.MethodId;   //Only for method oids

    BytesNeeded = 0;
    
    switch (Oid)
    {
        case OID_CUSTOM_METHOD:
            switch(MethodId)
            {
                case ADD_TWO_INTEGERS:
            
                    if (InputBufferLength < 2 * sizeof(ULONG))
                    {
                        Status = NDIS_STATUS_INVALID_DATA;
                        break;
                    }
                    FirstInt = *((PULONG UNALIGNED)InformationBuffer);
                    SecondInt = *((PULONG)((PULONG UNALIGNED)InformationBuffer+1));

                    BytesRead = 2 * sizeof(ULONG);
                    
                    BytesNeeded = sizeof(ULONG);
                    if (OutputBufferLength < BytesNeeded)
                    {
                        Status = NDIS_STATUS_BUFFER_TOO_SHORT;
                        break;
                    }
                    
                    *((PULONG UNALIGNED)InformationBuffer) = FirstInt + SecondInt;
                    BytesWritten = sizeof(ULONG);
                    
                    break;
                
                case MINUS_TWO_INTEGERS:
            
                    if (InputBufferLength < 2 * sizeof(ULONG))
                    {
                        Status = NDIS_STATUS_INVALID_DATA;
                        break;
                    }
                    FirstInt = *((PULONG UNALIGNED)InformationBuffer);
                    SecondInt = *((PULONG)((PULONG UNALIGNED)InformationBuffer+1));

                    BytesRead = 2 * sizeof(ULONG);
                    
                    BytesNeeded = sizeof(ULONG);
                    if (OutputBufferLength < BytesNeeded)
                    {
                        Status = NDIS_STATUS_BUFFER_TOO_SHORT;
                        break;
                    }
                    if (FirstInt < SecondInt)
                    {
                        Status = NDIS_STATUS_INVALID_DATA;
                        break;
                    }
                        
                    *((PULONG UNALIGNED)InformationBuffer) = FirstInt - SecondInt;
                    BytesWritten = sizeof(ULONG);
                    break;
            
                default:
                    Status = NDIS_STATUS_NOT_SUPPORTED;
                    break;
            }
            break;
            
        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }

    if (Status != NDIS_STATUS_SUCCESS)
    {
        Request->DATA.METHOD_INFORMATION.BytesNeeded = BytesNeeded;
    }
    else
    {
        Request->DATA.METHOD_INFORMATION.BytesWritten = BytesWritten;
        Request->DATA.METHOD_INFORMATION.BytesRead = BytesRead;
    }
            
    DBGPRINT(MP_TRACE, ("<====> MpMethodRequest Status: %x\n", Status));
    return Status;
}


VOID
MPCancelRequest(
    IN  NDIS_HANDLE            MiniportAdapterContext,
    IN  PNDIS_OID_REQUEST      Request
    )
/*++
Routine Description:

    This function aborts the request pending in the miniport.

Arguments:

    MiniportAdapterContext  Pointer to the adapter structure
    Request                 Piointer to the request sent down by NDIS
    
Return Value:
    
--*/
{
    PNDIS_OID_REQUEST    PendingRequest;
    PMP_ADAPTER         Adapter = (PMP_ADAPTER) MiniportAdapterContext;

    DBGPRINT(MP_TRACE, ("====> MPCancelRequest\n"));

    NdisAcquireSpinLock(&Adapter->Lock);
    
    if (Adapter->PendingRequest == Request)
    {
        PendingRequest = Adapter->PendingRequest;
        Adapter->PendingRequest = NULL;

        NdisReleaseSpinLock(&Adapter->Lock);
        
        NdisMRequestComplete(Adapter->AdapterHandle, 
                            PendingRequest, 
                            NDIS_STATUS_REQUEST_ABORTED);

    } 
    else
    {
        NdisReleaseSpinLock(&Adapter->Lock);
    }

    DBGPRINT(MP_TRACE, ("<==== MPCancelRequest\n"));

}

