/*++

Copyright (c) 1992-2000  Microsoft Corporation

Module Name:

    miniport.c

Abstract:

    NDIS Miniport Entry points and utility functions for the NDIS
    MUX Intermediate Miniport sample. The driver exposes zero or more
    Virtual Ethernet LANs (VELANs) as NDIS miniport instances over
    each lower (protocol-edge) binding to an underlying adapter.

Environment:

    Kernel mode.

Revision History:


--*/

#include "precomp.h"
#include "offload.h"

#pragma hdrstop

#define MODULE_NUMBER           MODULE_MINI

NDIS_OID VElanSupportedOids[] =
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
    OID_GEN_PROTOCOL_OPTIONS,
    OID_GEN_MAC_OPTIONS,
    OID_GEN_MEDIA_CONNECT_STATUS,
    OID_GEN_MAXIMUM_SEND_PACKETS,
    OID_GEN_XMIT_OK,
    OID_GEN_RCV_OK,
    OID_GEN_XMIT_ERROR,
    OID_GEN_RCV_ERROR,
    OID_GEN_RCV_NO_BUFFER,
    OID_GEN_RCV_CRC_ERROR,
    OID_GEN_TRANSMIT_QUEUE_LENGTH,
    OID_GEN_STATISTICS,
    OID_GEN_REQUIRED_BACKFILL_SIZE,
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
    OID_PNP_CAPABILITIES,
    OID_PNP_SET_POWER,
    OID_PNP_QUERY_POWER,
    OID_PNP_ADD_WAKE_UP_PATTERN,
    OID_PNP_REMOVE_WAKE_UP_PATTERN,
#if IEEE_VLAN_SUPPORT
    OID_GEN_VLAN_ID,
    OID_GEN_VLAN_STRIPING,
#endif    
    OID_PNP_ENABLE_WAKE_UP,
    OID_TCP_TASK_OFFLOAD
};


NDIS_STATUS
MPInitialize(
    IN  NDIS_HANDLE                     MiniportAdapterHandle,
    IN  NDIS_HANDLE                     MiniportDriverContext,
    IN  PNDIS_MINIPORT_INIT_PARAMETERS  MiniportInitParameters
    )
/*++

Routine Description:

    This is the Miniport Initialize routine which gets called as a
    result of our call to NdisIMInitializeDeviceInstanceEx.
    The context parameter which we pass there is the VELan structure
    which we retrieve here.

Arguments:

    OpenErrorStatus            Not used by us.
    SelectedMediumIndex        Place-holder for what media we are using
    MediumArray                Array of ndis media passed down to us to pick from
    MediumArraySize            Size of the array
    MiniportAdapterHandle       The handle NDIS uses to refer to us
    WrapperConfigurationContext    For use by NdisOpenConfiguration

Return Value:

    NDIS_STATUS_SUCCESS unless something goes wrong

--*/
{
    PVELAN                          pVElan;
    UINT                            i;
    NDIS_STATUS                     Status = NDIS_STATUS_FAILURE;
    NDIS_HANDLE                     ConfigurationHandle;
    PVOID                           NetworkAddress;

#if IEEE_VLAN_SUPPORT
    PNDIS_CONFIGURATION_PARAMETER   Params;
    NDIS_STRING                     strVlanId = NDIS_STRING_CONST("VlanID");
    NDIS_STRING                     strVlanId1 = NDIS_STRING_CONST("VlanID1");
    NDIS_STRING                     strVlanId2 = NDIS_STRING_CONST("VlanID2");
    NDIS_STRING                     strVlanId3 = NDIS_STRING_CONST("VlanID3");
#endif

    NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES   RegistrationAttributes;
    NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES        GenericAttributes;
    NDIS_PNP_CAPABILITIES          PowerManagementCapabilities;



    UNREFERENCED_PARAMETER(MiniportDriverContext);
    
    //
    // Start off by retrieving our virtual miniport context (VELAN) and 
    // storing the Miniport handle in it.
    //

    pVElan = MiniportInitParameters->IMDeviceInstanceContext;

    DBGPRINT(MUX_LOUD, ("==> Miniport Initialize: VELAN %p\n", pVElan));

    ASSERT(pVElan != NULL);
    ASSERT(pVElan->pAdapt != NULL);

    do
    {
        pVElan->MiniportAdapterHandle = MiniportAdapterHandle;

        //
        // Create an ioctl interface
        //
        (VOID)PtRegisterDevice();

        //
        // register this miniport with NDIS
        //

        NdisZeroMemory(&RegistrationAttributes, sizeof(NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES));
        NdisZeroMemory(&GenericAttributes, sizeof(NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES));

        //
        // setting registration attributes
        //
        RegistrationAttributes.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES;
        RegistrationAttributes.Header.Revision = NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES_REVISION_1;
        RegistrationAttributes.Header.Size = sizeof(NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES);

        RegistrationAttributes.MiniportAdapterContext = (NDIS_HANDLE)pVElan;


        RegistrationAttributes.AttributeFlags = NDIS_MINIPORT_ATTRIBUTES_NO_HALT_ON_SUSPEND;

        RegistrationAttributes.CheckForHangTimeInSeconds = 0;
        RegistrationAttributes.InterfaceType = 0;

        Status = NdisMSetMiniportAttributes(MiniportAdapterHandle,
                                            (PNDIS_MINIPORT_ADAPTER_ATTRIBUTES)&RegistrationAttributes);

        

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }
        

        //
        // Access configuration parameters for this miniport.
        //
        Status = NdisOpenConfigurationEx(
                    pVElan->MiniportAdapterHandle,
                    &ConfigurationHandle);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }


        NdisReadNetworkAddress(
            &Status,
            &NetworkAddress,
            &i,
            ConfigurationHandle);

        //
        // If there is a NetworkAddress override, use it 
        //
        if (((Status == NDIS_STATUS_SUCCESS) 
                && (i == ETH_LENGTH_OF_ADDRESS))
                && ((!ETH_IS_MULTICAST(NetworkAddress)) 
                && (ETH_IS_LOCALLY_ADMINISTERED (NetworkAddress))))
        {
            
            ETH_COPY_NETWORK_ADDRESS(
                        pVElan->CurrentAddress,
                        NetworkAddress);
        }
        else
        {
            MPGenerateMacAddr(pVElan);
        }

        //
        // ignore error reading the network address
        //
        Status = NDIS_STATUS_SUCCESS;
   
#if IEEE_VLAN_SUPPORT
        //
        // Read VLAN ID
        //
        NdisReadConfiguration(
                &Status,
                &Params,
                ConfigurationHandle,
                &strVlanId,
                NdisParameterInteger);
        if (Status == NDIS_STATUS_SUCCESS)
        {
            //
            // Check for out of bound
            //
            if (Params->ParameterData.IntegerData > VLAN_ID_MAX)
            {
                pVElan->VlanId = VLANID_DEFAULT;
                pVElan->MultipleVlanIds = FALSE;
            }
            else
            {
                pVElan->VlanId = Params->ParameterData.IntegerData;
            }

            NdisReadConfiguration(&Status, &Params, ConfigurationHandle, 
                    &strVlanId1, NdisParameterInteger);

            if (Status == NDIS_STATUS_SUCCESS)
            {
                if (Params->ParameterData.IntegerData <= VLAN_ID_MAX)
                {
                    pVElan->MultipleVlanIds = TRUE;
                    pVElan->VlanIds[pVElan->VlanId / 8] = 1 << (pVElan->VlanId % 8);
                    pVElan->VlanIds[Params->ParameterData.IntegerData / 8] |=
                        1 << (Params->ParameterData.IntegerData % 8);
                    
                    NdisReadConfiguration(&Status, &Params, ConfigurationHandle, 
                        &strVlanId2, NdisParameterInteger);

                    if (Status == NDIS_STATUS_SUCCESS)
                    {
                        if (Params->ParameterData.IntegerData <= VLAN_ID_MAX)
                        {
                            pVElan->VlanIds[Params->ParameterData.IntegerData / 8] |=
                                1 << (Params->ParameterData.IntegerData % 8);
                        }
                    }

                    NdisReadConfiguration(&Status, &Params, ConfigurationHandle, 
                        &strVlanId3, NdisParameterInteger);

                    if (Status == NDIS_STATUS_SUCCESS)
                    {
                        if (Params->ParameterData.IntegerData <= VLAN_ID_MAX)
                        {
                            pVElan->VlanIds[Params->ParameterData.IntegerData / 8] |=
                                1 << (Params->ParameterData.IntegerData % 8);
                        }
                    }
                }
            }

            Status = NDIS_STATUS_SUCCESS;
        }
        else 
        {
            //
            // Should fail the initialization or use default value
            //
            pVElan->MultipleVlanIds = FALSE;
            pVElan->VlanId = VLANID_DEFAULT;
            Status = NDIS_STATUS_SUCCESS;
            
        }
                
#endif    
        
        NdisCloseConfiguration(ConfigurationHandle);

        //
        // set up generic attributes
        //

        GenericAttributes.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES;
        GenericAttributes.Header.Revision = NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES_REVISION_1;
        GenericAttributes.Header.Size = sizeof(NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES);   

        GenericAttributes.MediaType = VELAN_MEDIA_TYPE;
        GenericAttributes.MtuSize = pVElan->pAdapt->BindParameters.MtuSize;
        GenericAttributes.MaxXmitLinkSpeed = pVElan->pAdapt->BindParameters.MaxXmitLinkSpeed;
        GenericAttributes.MaxRcvLinkSpeed = pVElan->pAdapt->BindParameters.MaxRcvLinkSpeed;
        GenericAttributes.XmitLinkSpeed = pVElan->pAdapt->BindParameters.XmitLinkSpeed;
        GenericAttributes.RcvLinkSpeed = pVElan->pAdapt->BindParameters.RcvLinkSpeed;
        GenericAttributes.MediaConnectState = pVElan->pAdapt->BindParameters.MediaConnectState;
        GenericAttributes.MediaDuplexState =  pVElan->pAdapt->BindParameters.MediaDuplexState ;
        GenericAttributes.LookaheadSize = pVElan->pAdapt->BindParameters.LookaheadSize;
        GenericAttributes.MaxMulticastListSize = pVElan->pAdapt->BindParameters.MaxMulticastListSize;
        GenericAttributes.MacAddressLength = pVElan->pAdapt->BindParameters.MacAddressLength;
        
        GenericAttributes.PhysicalMediumType = pVElan->pAdapt->BindParameters.PhysicalMediumType ;
        GenericAttributes.AccessType = pVElan->pAdapt->BindParameters.AccessType ; 
        GenericAttributes.DirectionType = pVElan->pAdapt->BindParameters.DirectionType;         
        GenericAttributes.ConnectionType = pVElan->pAdapt->BindParameters.ConnectionType ; 
        GenericAttributes.IfType = pVElan->pAdapt->BindParameters.IfType ; 
        GenericAttributes.IfConnectorPresent = FALSE; // RFC 2665 TRUE if physical adapter

        if (pVElan->pAdapt->BindParameters.RcvScaleCapabilities)
        {
            GenericAttributes.RecvScaleCapabilities = pVElan->pAdapt->BindParameters.RcvScaleCapabilities;
        }
        else
        {
            GenericAttributes.RecvScaleCapabilities = NULL;
        }
        
        GenericAttributes.MacOptions = NDIS_MAC_OPTION_NO_LOOPBACK;


#if IEEE_VLAN_SUPPORT
        GenericAttributes.MacOptions |= (NDIS_MAC_OPTION_8021P_PRIORITY |
                                         NDIS_MAC_OPTION_8021Q_VLAN);

#endif
        
        GenericAttributes.SupportedPacketFilters = pVElan->pAdapt->BindParameters.SupportedPacketFilters;

        GenericAttributes.SupportedStatistics = NDIS_STATISTICS_XMIT_OK_SUPPORTED |
                                                NDIS_STATISTICS_RCV_OK_SUPPORTED |
                                                NDIS_STATISTICS_XMIT_ERROR_SUPPORTED |
                                                NDIS_STATISTICS_RCV_ERROR_SUPPORTED |
                                                NDIS_STATISTICS_RCV_CRC_ERROR_SUPPORTED |
                                                NDIS_STATISTICS_RCV_NO_BUFFER_SUPPORTED |
                                                NDIS_STATISTICS_TRANSMIT_QUEUE_LENGTH_SUPPORTED |
                                                NDIS_STATISTICS_GEN_STATISTICS_SUPPORTED;

        
        NdisMoveMemory(&GenericAttributes.CurrentMacAddress,
                       &pVElan->CurrentAddress,
                       ETH_LENGTH_OF_ADDRESS);

        NdisMoveMemory(&GenericAttributes.PermanentMacAddress,
                       &pVElan->PermanentAddress,
                       ETH_LENGTH_OF_ADDRESS);

        GenericAttributes.PowerManagementCapabilities = &pVElan->pAdapt->PowerManagementCapabilities;
                                                        
        Status = NdisMSetMiniportAttributes(MiniportAdapterHandle,
                                            (PNDIS_MINIPORT_ADAPTER_ATTRIBUTES)&GenericAttributes);

    } while (FALSE);

    
    //
    // If we had received an UnbindAdapter notification on the underlying
    // adapter, we would have blocked that thread waiting for the IM Init
    // process to complete. Wake up any such thread.
    //
    // See PtUnbindAdapter for more details.
    //
    //

    ASSERT(pVElan->MiniportInitPending == TRUE);

    if (Status == NDIS_STATUS_SUCCESS)
    {
        //
        // we should set this to FALSE only if we successfully initialized the adapter
        // otherwise the unbind routine will wait forever for this VElan to go away
        //
        pVElan->MiniportInitPending = FALSE;
    }
    
    // TODO: check to see if we can set the init event in a failure case?
    
    NdisSetEvent(&pVElan->MiniportInitEvent);

    DBGPRINT(MUX_INFO, ("<== Miniport Initialize: VELAN %p, Status %x\n", pVElan, Status));

    return Status;
}

NDIS_STATUS
MPQueryInformation(
    IN    NDIS_HANDLE               MiniportAdapterContext,
    IN    PNDIS_REQUEST_EX          NdisRequest
    )
/*++

Routine Description:

    Entry point called by NDIS to query for the value of the specified OID.
    All OID values are responded to right here, since this is a virtual
    device (not pass-through).

Arguments:

    MiniportAdapterContext      Pointer to the adapter structure
    Oid                         Oid for this query
    InformationBuffer           Buffer for information
    InformationBufferLength     Size of this buffer
    BytesWritten                Specifies how much info is written
    BytesNeeded                 In case the buffer is smaller than 
                                what we need, tell them how much is needed


Return Value:

    Return code from the NdisRequest below.

--*/
{
    NDIS_STATUS                 Status = NDIS_STATUS_SUCCESS;
    PVELAN                      pVElan;
    NDIS_HARDWARE_STATUS HardwareStatus = NdisHardwareStatusReady;
    NDIS_MEDIUM                 Medium = VELAN_MEDIA_TYPE;
    UCHAR                       VendorDesc[] = VELAN_VENDOR_DESC;
    ULONG                       ulInfo;
    ULONG64                     ulInfo64;
    USHORT                      usInfo;
    PVOID                       pInfo = (PVOID) &ulInfo;
    ULONG                       ulInfoLen = sizeof(ulInfo);
    // Should we forward the request to the miniport below?
    BOOLEAN                     bForwardRequest = FALSE;

    NDIS_OID                    Oid;
    PVOID                       InformationBuffer;
    ULONG                       InformationBufferLength;
    PULONG                      BytesWritten;
    PULONG                      BytesNeeded;
    NDIS_STATISTICS_INFO        StatisticsInfo;

    Oid = NdisRequest->DATA.QUERY_INFORMATION.Oid;
    InformationBuffer = NdisRequest->DATA.QUERY_INFORMATION.InformationBuffer;
    InformationBufferLength = NdisRequest->DATA.QUERY_INFORMATION.InformationBufferLength;
    BytesWritten = &(NdisRequest->DATA.QUERY_INFORMATION.BytesWritten);
    BytesNeeded = &(NdisRequest->DATA.QUERY_INFORMATION.BytesNeeded);
    
    pVElan = (PVELAN) MiniportAdapterContext;

    // Initialize the result
    *BytesWritten = 0;
    *BytesNeeded = 0;

    switch (Oid)
    {
        case OID_GEN_SUPPORTED_LIST:
            pInfo = (PVOID) VElanSupportedOids;
            ulInfoLen = sizeof(VElanSupportedOids);
            break;

        case OID_GEN_SUPPORTED_GUIDS:
            //
            // Do NOT forward this down, otherwise we will
            // end up with spurious instances of private WMI
            // classes supported by the lower driver(s).
            //
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;

        case OID_GEN_HARDWARE_STATUS:
            pInfo = (PVOID) &HardwareStatus;
            ulInfoLen = sizeof(NDIS_HARDWARE_STATUS);
            break;

        case OID_GEN_MEDIA_SUPPORTED:
        case OID_GEN_MEDIA_IN_USE:
            pInfo = (PVOID) &Medium;
            ulInfoLen = sizeof(NDIS_MEDIUM);
            break;

        case OID_GEN_CURRENT_LOOKAHEAD:
        case OID_GEN_MAXIMUM_LOOKAHEAD:
            ulInfo = pVElan->LookAhead - ETH_HEADER_SIZE;
            break;            
            
        case OID_GEN_MAXIMUM_FRAME_SIZE:
            ulInfo = ETH_MAX_PACKET_SIZE - ETH_HEADER_SIZE;

#if IEEE_VLAN_SUPPORT
            ulInfo -= VLAN_TAG_HEADER_SIZE;
#endif
            
            break;

        case OID_GEN_MAXIMUM_TOTAL_SIZE:
        case OID_GEN_TRANSMIT_BLOCK_SIZE:
        case OID_GEN_RECEIVE_BLOCK_SIZE:
            ulInfo = (ULONG) ETH_MAX_PACKET_SIZE;
#if IEEE_VLAN_SUPPORT
            ulInfo -= VLAN_TAG_HEADER_SIZE;
#endif            
            break;
            
        case OID_GEN_MAC_OPTIONS:
            ulInfo = NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA | 
                     NDIS_MAC_OPTION_TRANSFERS_NOT_PEND |
                     NDIS_MAC_OPTION_NO_LOOPBACK;

#if IEEE_VLAN_SUPPORT
            ulInfo |= (NDIS_MAC_OPTION_8021P_PRIORITY |
                        NDIS_MAC_OPTION_8021Q_VLAN);
#endif
            
            break;

        case OID_GEN_LINK_SPEED:
            bForwardRequest = TRUE;
            break;

        case OID_GEN_TRANSMIT_BUFFER_SPACE:
            ulInfo = ETH_MAX_PACKET_SIZE * pVElan->MaxBusySends;
#if IEEE_VLAN_SUPPORT
            ulInfo -= VLAN_TAG_HEADER_SIZE * pVElan->MaxBusySends;
#endif            
            break;

        case OID_GEN_RECEIVE_BUFFER_SPACE:
            ulInfo = ETH_MAX_PACKET_SIZE * pVElan->MaxBusyRecvs;
#if IEEE_VLAN_SUPPORT
            ulInfo -= VLAN_TAG_HEADER_SIZE * pVElan->MaxBusyRecvs;
#endif            
            
            break;

        case OID_GEN_VENDOR_ID:
            ulInfo = VELAN_VENDOR_ID;
            break;

        case OID_GEN_VENDOR_DESCRIPTION:
            pInfo = VendorDesc;
            ulInfoLen = sizeof(VendorDesc);
            break;
            
        case OID_GEN_VENDOR_DRIVER_VERSION:
            ulInfo = VELAN_VENDOR_ID;
            break;

        case OID_GEN_DRIVER_VERSION:
            usInfo = (USHORT) VELAN_DRIVER_VERSION;
            pInfo = (PVOID) &usInfo;
            ulInfoLen = sizeof(USHORT);
            break;

        case OID_802_3_PERMANENT_ADDRESS:
            pInfo = pVElan->PermanentAddress;
            ulInfoLen = ETH_LENGTH_OF_ADDRESS;
            break;

        case OID_802_3_CURRENT_ADDRESS:
            pInfo = pVElan->CurrentAddress;
            ulInfoLen = ETH_LENGTH_OF_ADDRESS;
            break;

        case OID_802_3_MAXIMUM_LIST_SIZE:
            ulInfo = VELAN_MAX_MCAST_LIST;
            break;

        case OID_GEN_MAXIMUM_SEND_PACKETS:
            ulInfo = VELAN_MAX_SEND_PKTS;
            break;

        case OID_GEN_MEDIA_CONNECT_STATUS:
            //
            // Get this from the adapter below.
            //
            bForwardRequest = TRUE;
            break;

        case OID_PNP_QUERY_POWER:
            // simply succeed this.
            ulInfoLen = sizeof(ULONG);
            break;

        case OID_PNP_CAPABILITIES:
        case OID_PNP_WAKE_UP_PATTERN_LIST:
        case OID_TCP_TASK_OFFLOAD:
        case OID_TCP4_OFFLOAD_STATS:
        case OID_TCP6_OFFLOAD_STATS:
        case OID_IP4_OFFLOAD_STATS:
        case OID_IP6_OFFLOAD_STATS:
            //
            // Pass down these power management/PNP OIDs.
            //
            bForwardRequest = TRUE;
            break;

        case OID_GEN_XMIT_OK:
            ulInfo64 = pVElan->GoodTransmits;
            pInfo = &ulInfo64;
            if (InformationBufferLength >= sizeof(ULONG64) ||
                InformationBufferLength == 0)
            {
                ulInfoLen = sizeof(ULONG64);
            }
            else
            {
                ulInfoLen = sizeof(ULONG);
            }
            break;
    
        case OID_GEN_RCV_OK:
            ulInfo64 = pVElan->GoodReceives;
            pInfo = &ulInfo64;
            if (InformationBufferLength >= sizeof(ULONG64) ||
                InformationBufferLength == 0)
            {
                ulInfoLen = sizeof(ULONG64);
            }
            else
            {
                ulInfoLen = sizeof(ULONG);
            }
            break;
    
        case OID_GEN_XMIT_ERROR:
            ulInfo = pVElan->TxAbortExcessCollisions +
                pVElan->TxDmaUnderrun +
                pVElan->TxLostCRS +
                pVElan->TxLateCollisions+
                pVElan->TransmitFailuresOther;
            break;
    
        case OID_GEN_RCV_ERROR:
            ulInfo = pVElan->RcvCrcErrors +
                pVElan->RcvAlignmentErrors +
                pVElan->RcvResourceErrors +
                pVElan->RcvDmaOverrunErrors +
                pVElan->RcvRuntErrors;
#if IEEE_VLAN_SUPPORT
            ulInfo +=
                (pVElan->RcvVlanIdErrors +
                pVElan->RcvFormatErrors);
#endif

            break;
    
        case OID_GEN_RCV_NO_BUFFER:
            ulInfo = pVElan->RcvResourceErrors;
            break;
    
        case OID_GEN_RCV_CRC_ERROR:
            ulInfo = pVElan->RcvCrcErrors;
            break;
    
        case OID_GEN_TRANSMIT_QUEUE_LENGTH:
            ulInfo = pVElan->RegNumTcb;
            break;
        
        case OID_GEN_STATISTICS:
            ulInfoLen = sizeof (NDIS_STATISTICS_INFO);
            NdisZeroMemory(&StatisticsInfo, sizeof(NDIS_STATISTICS_INFO));

            StatisticsInfo.Header.Revision = NDIS_OBJECT_REVISION_1;
            StatisticsInfo.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
            StatisticsInfo.Header.Size = sizeof(NDIS_STATISTICS_INFO);
            StatisticsInfo.SupportedStatistics = NDIS_STATISTICS_FLAGS_VALID_RCV_DISCARDS          |
                                                 NDIS_STATISTICS_FLAGS_VALID_RCV_ERROR             |
                                                 NDIS_STATISTICS_FLAGS_VALID_XMIT_ERROR;
                    
            StatisticsInfo.ifInDiscards = pVElan->RcvCrcErrors +
                                          pVElan->RcvAlignmentErrors +
                                          pVElan->RcvResourceErrors +
                                          pVElan->RcvDmaOverrunErrors +
                                          pVElan->RcvRuntErrors;
            
            StatisticsInfo.ifInErrors = StatisticsInfo.ifInDiscards -
                                            pVElan->RcvResourceErrors;
            
            StatisticsInfo.ifOutErrors = pVElan->TxAbortExcessCollisions +
                                         pVElan->TxDmaUnderrun +
                                         pVElan->TxLostCRS +
                                         pVElan->TxLateCollisions;

            pInfo = &StatisticsInfo;
            break;

        case OID_GEN_REQUIRED_BACKFILL_SIZE:
#if IEEE_VLAN_SUPPORT
            ulInfo = VLAN_TAG_HEADER_SIZE;
#else
            ulInfo = 0;
#endif
            break;
    
        case OID_802_3_RCV_ERROR_ALIGNMENT:
            ulInfo = pVElan->RcvAlignmentErrors;
            break;
    
        case OID_802_3_XMIT_ONE_COLLISION:
        	ulInfo = pVElan->OneRetry;
            break;
    
        case OID_802_3_XMIT_MORE_COLLISIONS:
        	ulInfo = pVElan->MoreThanOneRetry;
            break;
    
        case OID_802_3_XMIT_DEFERRED:
        	ulInfo = pVElan->TxOKButDeferred;
            break;
    
        case OID_802_3_XMIT_MAX_COLLISIONS:
            ulInfo = pVElan->TxAbortExcessCollisions;
            break;
    
        case OID_802_3_RCV_OVERRUN:
            ulInfo = pVElan->RcvDmaOverrunErrors;
            break;
    
        case OID_802_3_XMIT_UNDERRUN:
            ulInfo = pVElan->TxDmaUnderrun;
            break;
    
        case OID_802_3_XMIT_HEARTBEAT_FAILURE:
            ulInfo = pVElan->TxLostCRS;
            break;
    
        case OID_802_3_XMIT_TIMES_CRS_LOST:
            ulInfo = pVElan->TxLostCRS;
            break;
    
        case OID_802_3_XMIT_LATE_COLLISIONS:
            ulInfo = pVElan->TxLateCollisions;
            break;
   
#if IEEE_VLAN_SUPPORT            
        case OID_GEN_VLAN_ID:
            if (pVElan->MultipleVlanIds)
            {
                ulInfoLen = pVElan->VlanIdListCount * sizeof(ULONG);
                pInfo = (PVOID)pVElan->VlanIdList;

                if (ulInfoLen == sizeof(ULONG))
                {
                    ulInfo = pVElan->VlanIdList[0];
                }
            }
            else
            {
                ulInfo = pVElan->VlanId;
            }
            break;

        case OID_GEN_VLAN_STRIPING:
             if (pVElan->Striping)
             {
                 ulInfo = 1;
             }
             else
             {
                 ulInfo = 0;
             }

#endif

        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }

    if (bForwardRequest == FALSE)
    {
        //
        // No need to forward this request down.
        //
        if (Status == NDIS_STATUS_SUCCESS)
        {
            if (ulInfoLen <= InformationBufferLength)
            {
                // Copy result into InformationBuffer
                *BytesWritten = ulInfoLen;
                if(ulInfoLen)
                {
                    NdisMoveMemory(InformationBuffer, pInfo, ulInfoLen);
                }
            }
            else
            {
                // too short
                *BytesNeeded = ulInfoLen;
                Status = NDIS_STATUS_BUFFER_TOO_SHORT;
            }
        }
    }
    else
    {
        //
        // Send this request to the binding below.
        //
        Status = MPForwardRequest(pVElan,NdisRequest);
    }

    if ((Status != NDIS_STATUS_SUCCESS) &&
        (Status != NDIS_STATUS_PENDING))
    {
        DBGPRINT(MUX_WARN, ("MPQueryInformation VELAN %p, OID 0x%08x, Status = 0x%08x\n",
                    pVElan, Oid, Status));
    }
    
    return(Status);

}


NDIS_STATUS
MPSetInformation(
    IN    NDIS_HANDLE               MiniportAdapterContext,
    IN    PNDIS_REQUEST_EX          NdisRequest
    )
/*++

Routine Description:

    This is the handler for an OID set operation. Relevant
    OIDs are forwarded down to the lower miniport for handling.

Arguments:

    MiniportAdapterContext      Pointer to the adapter structure
    Oid                         Oid for this query
    InformationBuffer           Buffer for information
    InformationBufferLength     Size of this buffer
    BytesRead                   Specifies how much info is read
    BytesNeeded                 In case the buffer is smaller than what 
                                we need, tell them how much is needed

Return Value:

    Return code from the NdisRequest below.

--*/
{
    NDIS_STATUS             Status = NDIS_STATUS_SUCCESS;
    PVELAN                  pVElan = (PVELAN) MiniportAdapterContext;
    ULONG                   PacketFilter;
    NDIS_DEVICE_POWER_STATE NewDeviceState;

    NDIS_OID                Oid;
    PVOID                   InformationBuffer;
    ULONG                   InformationBufferLength;
    PULONG                  BytesRead;
    PULONG                  BytesNeeded;
    
    // Should we forward the request to the miniport below?
    BOOLEAN                 bForwardRequest = FALSE;
    
    ULONG                   Count;
    ULONG                   VlanId;
    NDIS_STATUS_INDICATION  StatusIndication;

    Oid = NdisRequest->DATA.SET_INFORMATION.Oid;
    InformationBuffer = NdisRequest->DATA.SET_INFORMATION.InformationBuffer;
    InformationBufferLength = NdisRequest->DATA.SET_INFORMATION.InformationBufferLength;
    BytesRead = &(NdisRequest->DATA.SET_INFORMATION.BytesRead);
    BytesNeeded = &(NdisRequest->DATA.SET_INFORMATION.BytesNeeded);

    *BytesRead = 0;
    *BytesNeeded = 0;

    switch (Oid)
    {
        //
        // Let the miniport below handle these OIDs:
        //
        case OID_PNP_ADD_WAKE_UP_PATTERN:
        case OID_PNP_REMOVE_WAKE_UP_PATTERN:
        case OID_PNP_ENABLE_WAKE_UP:
        case OID_TCP_TASK_OFFLOAD:
            bForwardRequest = TRUE;
            break;

        case OID_PNP_SET_POWER:
            //
            // Store new power state and succeed the request.
            //
            *BytesNeeded = sizeof(NDIS_DEVICE_POWER_STATE);
            if (InformationBufferLength < *BytesNeeded)
            {
                Status = NDIS_STATUS_INVALID_LENGTH;
                break;
            }
           
            NewDeviceState = (*(PNDIS_DEVICE_POWER_STATE)InformationBuffer);
            
            //
            // Check if the VELAN adapter goes from lower power state to D0
            // 
            if ((MUX_IS_LOW_POWER_STATE(pVElan->MPDevicePowerState)) 
                    && (!MUX_IS_LOW_POWER_STATE(NewDeviceState)))
            {
                //
                // Indicate the media status is necessary
                // 
                if (pVElan->LastIndicatedStatus != pVElan->LatestUnIndicateStatus)
                {
                    StatusIndication.Header.Type = NDIS_OBJECT_TYPE_STATUS_INDICATION;
                    StatusIndication.Header.Revision = NDIS_STATUS_INDICATION_REVISION_1;
                    StatusIndication.Header.Size = sizeof(NDIS_STATUS_INDICATION);
                    
                    StatusIndication.SourceHandle = pVElan->MiniportAdapterHandle;
                    StatusIndication.StatusCode = pVElan->LatestUnIndicateStatus;
                    StatusIndication.StatusBuffer = NULL;
                    StatusIndication.StatusBufferSize = 0;

                    NdisMIndicateStatusEx(pVElan->MiniportAdapterHandle, &StatusIndication);
                                        
                    pVElan->LastIndicatedStatus = pVElan->LatestUnIndicateStatus;
                }
            }
            //
            // Check if the VELAN adapter goes from D0 to lower power state
            // 
            if ((!MUX_IS_LOW_POWER_STATE(pVElan->MPDevicePowerState)) 
                    && (MUX_IS_LOW_POWER_STATE(NewDeviceState)))
            {
                //
                //  Initialize LastUnIndicateStatus 
                // 
                pVElan->LatestUnIndicateStatus = pVElan->LastIndicatedStatus;
            }
            
            NdisMoveMemory(&pVElan->MPDevicePowerState,
                           InformationBuffer,
                           *BytesNeeded);

            DBGPRINT(MUX_INFO, ("SetInfo: VElan %p, new miniport power state --- %d\n",
                    pVElan, pVElan->MPDevicePowerState));

            break;

        case OID_802_3_MULTICAST_LIST:
            Status = MPSetMulticastList(pVElan,
                                        InformationBuffer,
                                        InformationBufferLength,
                                        BytesRead,
                                        BytesNeeded);
            break;

        case OID_GEN_CURRENT_PACKET_FILTER:
            if (InformationBufferLength != sizeof(ULONG))
            {
                Status = NDIS_STATUS_INVALID_LENGTH;
                *BytesNeeded = sizeof(ULONG);
                break;
            }

            NdisMoveMemory(&PacketFilter, InformationBuffer, sizeof(ULONG));
            *BytesRead = sizeof(ULONG);

            Status = MPSetPacketFilter(pVElan,
                                       PacketFilter);
            break;

        case OID_GEN_CURRENT_LOOKAHEAD:
#if IEEE_VLAN_SUPPORT
            //
            // In order to simplify parsing and to avoid excessive
            // copying, we need the tag header also to be present in the
            // lookahead buffer. Make sure that the driver below
            // includes that.
            //
            *(UNALIGNED PULONG)InformationBuffer += VLAN_TAG_HEADER_SIZE;
#endif            
            bForwardRequest = TRUE;
            break;
            
#if IEEE_VLAN_SUPPORT
        case OID_GEN_VLAN_ID:
            if (InformationBufferLength == sizeof(ULONG))
            {
                NdisMoveMemory((&pVElan->VlanId), InformationBuffer, sizeof(ULONG));
                pVElan->MultipleVlanIds = TRUE;
            } 
            else if ( ((InformationBufferLength % sizeof(ULONG)) == 0)
                        && (InformationBufferLength <= (sizeof(ULONG) * VLAN_ID_MAX)))
            {
                NdisMoveMemory(&(pVElan->VlanIdList), InformationBuffer, InformationBufferLength);
                pVElan->VlanIdListCount = InformationBufferLength / sizeof(ULONG);
                NdisZeroMemory(&(pVElan->VlanIds),sizeof(pVElan->VlanIds));
                

                for(Count = 0; Count < pVElan->VlanIdListCount; Count++)
                {
                    VlanId = pVElan->VlanIdList[Count];

                    pVElan->VlanIds[VlanId / 8] |= 1 << (VlanId % 8);
                }

            } 
            else
            {
                *BytesNeeded = sizeof(ULONG);
                Status = NDIS_STATUS_INVALID_LENGTH;
            }

            break;

        case OID_GEN_VLAN_STRIPING:
            if (InformationBufferLength != sizeof(ULONG))
            {
                *BytesNeeded = sizeof(ULONG);
                Status = NDIS_STATUS_INVALID_LENGTH;
            } 
            else
            {
                if (*(UNALIGNED PULONG)InformationBuffer == 1)
                {
                    pVElan->Striping = TRUE;
                }
                else
                {
                    pVElan->Striping = FALSE;
                }
            }
#endif
            
        default:
            Status = NDIS_STATUS_INVALID_OID;
            break;

    }
    
    if (bForwardRequest == FALSE)
    {
        if (Status == NDIS_STATUS_SUCCESS)
        {
            *BytesRead = InformationBufferLength;
        }
    }
    else
    {
        //
        // Send this request to the binding below.
        //
        Status = MPForwardRequest(pVElan,NdisRequest);
    }

    return(Status);
}

NDIS_STATUS
MpMethodRequest(
    IN    NDIS_HANDLE             MiniportAdapterContext,
    IN    PNDIS_REQUEST_EX        Request
    )
/*++
Routine Description:

    WMI method request handler

Arguments:

    MiniportAdapterContext          Pointer to the adapter structure
    Request                         Pointer to the request sent down by NDIS

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    NDIS_STATUS_BUFFER_TOO_SHORT
    NDIS_STATUS_XXX

--*/
{
    PVELAN          pVElan = (PVELAN)MiniportAdapterContext;
    NDIS_OID        Oid;
    ULONG           MethodId;
    PVOID           InformationBuffer;
    ULONG           InputBufferLength;
    ULONG           OutputBufferLength;
    ULONG           BytesNeeded;


    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;

    DBGPRINT(MUX_LOUD, ("==> MpMethodRequest\n"));

    Oid = Request->DATA.METHOD_INFORMATION.Oid;
    InformationBuffer = (PVOID)(Request->DATA.METHOD_INFORMATION.InformationBuffer);
    InputBufferLength = Request->DATA.METHOD_INFORMATION.InputBufferLength;
    OutputBufferLength = Request->DATA.METHOD_INFORMATION.OutputBufferLength;
    MethodId = Request->DATA.METHOD_INFORMATION.MethodId;

    BytesNeeded = 0;

    switch(Oid)
    {
        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }


    DBGPRINT(MUX_LOUD, ("<== MpMethodRequest returning %08lx\n",Status));

    return Status;

}



NDIS_STATUS
MPRequest(
    IN    NDIS_HANDLE             MiniportAdapterContext,
    IN    PNDIS_REQUEST_EX        NdisRequest
    )
/*++
Routine Description:

    MiniportRequest dispatch handler

Arguments:

    MiniportAdapterContext      Pointer to the adapter structure
    NdisRequest                 Pointer to NDIS_REQUEST

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    NDIS_STATUS_BUFFER_TOO_SHORT

--*/
{
    PVELAN                  pVElan = (PVELAN)MiniportAdapterContext;
    NDIS_REQUEST_TYPE       RequestType;
    NDIS_STATUS             Status;

    DBGPRINT(MUX_LOUD,("==>MPRequest\n"));

    RequestType = NdisRequest->RequestType;

    switch(RequestType)
    {
        case NdisRequestMethod:
            Status = MpMethodRequest(MiniportAdapterContext, NdisRequest);
            break;

        case NdisRequestSetInformation:
            Status = MPSetInformation(MiniportAdapterContext, NdisRequest);
            break;

        case NdisRequestQueryInformation:
        case NdisRequestQueryStatistics:
            Status = MPQueryInformation(MiniportAdapterContext, NdisRequest);
            break;

        default:
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
    }

    DBGPRINT(MUX_LOUD,("<==MPRequest Status: %08lx\n", Status));

    return Status;
}



VOID
MPHalt(
    IN    NDIS_HANDLE                MiniportAdapterContext,
    IN    NDIS_HALT_ACTION           HaltAction
    )
/*++

Routine Description:

    Halt handler. Add any further clean-up for the VELAN to this
    function.

    We wait for all pending I/O on the VELAN to complete and then
    unlink the VELAN from the adapter.

Arguments:

    MiniportAdapterContext    Pointer to the pVElan

Return Value:

    None.

--*/
{
    PVELAN            pVElan = (PVELAN)MiniportAdapterContext;

    UNREFERENCED_PARAMETER(HaltAction);
    

    DBGPRINT(MUX_LOUD, ("==>MiniportHalt: VELAN %p\n", pVElan));

    //
    // Mark the VELAN so that we don't send down any new requests or
    // sends to the adapter below, or new receives/indications to
    // protocols above.
    //
    pVElan->MiniportHalting = TRUE;

    //
    // Update the packet filter on the underlying adapter if needed.
    //
    if (pVElan->PacketFilter != 0)
    {
        MPSetPacketFilter(pVElan, 0);
    }

    //
    // Wait for any outstanding sends or requests to complete.
    //
    while (pVElan->OutstandingSends)
    {
        DBGPRINT(MUX_INFO, ("MiniportHalt: VELAN %p has %d outstanding sends\n",
                            pVElan, pVElan->OutstandingSends));
        NdisMSleep(20000);
    }

    //
    // Wait for all outstanding indications to be completed and
    // any pended receive packets to be returned to us.
    //
    while (pVElan->OutstandingReceives)
    {
        DBGPRINT(MUX_INFO, ("MiniportHalt: VELAN %p has %d outstanding receives\n",
                            pVElan, pVElan->OutstandingReceives));
        NdisMSleep(20000);
    }

    //
    // Delete the ioctl interface that was created when the miniport
    // was created.
    //
    (VOID)PtDeregisterDevice();

    //
    // Unlink the VELAN from its parent ADAPT structure. This will
    // dereference the VELAN.
    //
    pVElan->MiniportAdapterHandle = NULL;
    PtUnlinkVElanFromAdapter(pVElan);
    
    DBGPRINT(MUX_LOUD, ("<== MiniportHalt: pVElan %p\n", pVElan));
}


NDIS_STATUS
MPForwardRequest(
    IN PVELAN                       pVElan,
    IN PNDIS_REQUEST_EX             Request
    )
/*++

Routine Description:

    Utility routine that forwards an NDIS request made on a VELAN to the
    lower binding. Since at most a single request can be pended on a VELAN,
    we use the pre-allocated request structure embedded in the VELAN struct.

Arguments:


Return Value:

    NDIS_STATUS_PENDING if a request was sent down.

--*/
{
    NDIS_STATUS                  Status;
    PMUX_NDIS_REQUEST            pMuxNdisRequest = &pVElan->Request;
    

    DBGPRINT(MUX_LOUD, ("MPForwardRequest: VELAN %p, OID %x\n", pVElan, Request->DATA.QUERY_INFORMATION.Oid));

    do
    {
        MUX_INCR_PENDING_SENDS(pVElan);

        //
        // If the miniport below is going away, fail the request
        // 
        NdisAcquireSpinLock(&pVElan->Lock);
        if (pVElan->DeInitializing == TRUE)
        {
            NdisReleaseSpinLock(&pVElan->Lock);
            MUX_DECR_PENDING_SENDS(pVElan);
            Status = NDIS_STATUS_FAILURE;
            break;
        }
        NdisReleaseSpinLock(&pVElan->Lock);    

        //
        // If the virtual miniport edge is at a low power
        // state, fail this request.
        //
        if (MUX_IS_LOW_POWER_STATE(pVElan->MPDevicePowerState))
        {
            MUX_DECR_PENDING_SENDS(pVElan);
            Status = NDIS_STATUS_ADAPTER_NOT_READY;
            break;
        }
        
        NdisAcquireSpinLock(&pVElan->Lock);
        pMuxNdisRequest->OrigRequest = Request;
        pMuxNdisRequest->pCallback = PtCompleteForwardedRequest;
        pMuxNdisRequest->Request.RequestType = Request->RequestType;
        pMuxNdisRequest->Refcount =1;
        NdisReleaseSpinLock(&pVElan->Lock);    

        switch (Request->RequestType)
        {
            case NdisRequestQueryInformation:
            case NdisRequestQueryStatistics:
                pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.Oid = Request->DATA.QUERY_INFORMATION.Oid;
                pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.InformationBuffer = 
                                            Request->DATA.QUERY_INFORMATION.InformationBuffer;
                pMuxNdisRequest->Request.DATA.QUERY_INFORMATION.InformationBufferLength = 
                                            Request->DATA.QUERY_INFORMATION.InformationBufferLength;
                break;

            case NdisRequestSetInformation:
                pMuxNdisRequest->Request.DATA.SET_INFORMATION.Oid = Request->DATA.SET_INFORMATION.Oid;
                pMuxNdisRequest->Request.DATA.SET_INFORMATION.InformationBuffer = 
                                            Request->DATA.SET_INFORMATION.InformationBuffer;
                pMuxNdisRequest->Request.DATA.SET_INFORMATION.InformationBufferLength = 
                                            Request->DATA.SET_INFORMATION.InformationBufferLength;
                break;

            default:
                ASSERT(FALSE);
                break;
        }

        //
        // If the miniport below is going away
        //
        NdisAcquireSpinLock(&pVElan->Lock);
        if (pVElan->DeInitializing == TRUE)
        {
            pMuxNdisRequest->OrigRequest = NULL;
            NdisReleaseSpinLock(&pVElan->Lock);
            MUX_DECR_PENDING_SENDS(pVElan);
            Status = NDIS_STATUS_FAILURE;
            break;
        }
        
        // If the lower binding has been notified of a low
        // power state, queue this request; it will be picked
        // up again when the lower binding returns to D0.
        //
        if (MUX_IS_LOW_POWER_STATE(pVElan->pAdapt->PtDevicePowerState))
        {
            DBGPRINT(MUX_INFO, ("ForwardRequest: VELAN %p, Adapt %p power"
                                " state is %d, queueing OID %x\n",
                                pVElan, pVElan->pAdapt,
                                pVElan->pAdapt->PtDevicePowerState, 
                                Request->DATA.QUERY_INFORMATION.Oid));

            pVElan->QueuedRequest = TRUE;
            NdisReleaseSpinLock(&pVElan->Lock);
            Status = NDIS_STATUS_PENDING;
            break;
        }
        NdisReleaseSpinLock(&pVElan->Lock);

        Status  = NdisOidRequest(pVElan->BindingHandle,
                                &pMuxNdisRequest->Request);

        if (Status != NDIS_STATUS_PENDING)
        {
            PtRequestComplete(pVElan->pAdapt, &pMuxNdisRequest->Request, Status);
            Status = NDIS_STATUS_PENDING;
            break;
        }
    }
    while (FALSE);

    return (Status);
}

NDIS_STATUS
MPSetPacketFilter(
    IN PVELAN               pVElan,
    IN ULONG                PacketFilter
    )
/*++
Routine Description:

    This routine will set up the VELAN so that it accepts packets 
    that match the specified packet filter.  The only filter bits   
    that can truly be toggled are for broadcast and promiscuous.

    The MUX driver always sets the lower binding to promiscuous
    mode, but we do some optimization here to avoid turning on
    receives too soon. That is, we set the packet filter on the lower
    binding to a non-zero value iff at least one of the VELANs
    has a non-zero filter value.
    
    NOTE: setting the lower binding to promiscuous mode can
    impact CPU utilization. The only reason we set the lower binding
    to promiscuous mode in this sample is that we need to be able
    to receive unicast frames directed to MAC address(es) that do not
    match the local adapter's MAC address. If VELAN MAC addresses
    are set to be equal to that of the adapter below, it is sufficient
    to set the lower packet filter to the bitwise OR'ed value of
    packet filter settings on all VELANs.
                                    

Arguments:

    pVElan - pointer to VELAN
    PacketFilter - the new packet filter 
    
Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_NOT_SUPPORTED
    
--*/
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    PADAPT          pAdapt;
    PVELAN          pTmpVElan;
    PLIST_ENTRY     p;
    ULONG           AdapterFilter;
    BOOLEAN         bSendUpdate = FALSE;
    LOCK_STATE      LockState;

    DBGPRINT(MUX_LOUD, ("=> SetPacketFilter VELAN %p, Filter %x\n", pVElan, PacketFilter));
    
    do
    {
        //
        // Any bits not supported?
        //
        if (PacketFilter & ~VELAN_SUPPORTED_FILTERS)
        {
            Status = NDIS_STATUS_NOT_SUPPORTED;
            break;
        }
    
        AdapterFilter = 0;
        pAdapt = pVElan->pAdapt;

        //
        // Grab a Write lock on the adapter so that this operation
        // does not interfere with any receives that might be accessing
        // filter information.
        //
        MUX_ACQUIRE_ADAPT_WRITE_LOCK(pAdapt, &LockState);

        //
        // Save the new packet filter value
        //
        pVElan->PacketFilter = PacketFilter;

        //
        // Compute the new combined filter for all VELANs on this
        // adapter.
        //
        for (p = pAdapt->VElanList.Flink;
             p != &pAdapt->VElanList;
             p = p->Flink)
        {
            pTmpVElan = CONTAINING_RECORD(p, VELAN, Link);
            AdapterFilter |= pTmpVElan->PacketFilter;
        }

        //
        // If all VELANs have packet filters set to 0, turn off
        // receives on the lower adapter, if not already done.
        //
        if ((AdapterFilter == 0) && (pAdapt->PacketFilter != 0))
        {
            bSendUpdate = TRUE;
            pAdapt->PacketFilter = 0;
        }
        else
        //
        // If receives had been turned off on the lower adapter, and
        // the new filter is non-zero, turn on the lower adapter.
        // We set the adapter to promiscuous mode in this sample
        // so that we are able to receive packets directed to
        // any of the VELAN MAC addresses.
        //
        if ((AdapterFilter != 0) && (pAdapt->PacketFilter == 0))
        {
            bSendUpdate = TRUE;
            pAdapt->PacketFilter = MUX_ADAPTER_PACKET_FILTER;
        }
        
        MUX_RELEASE_ADAPT_WRITE_LOCK(pAdapt, &LockState);

        if (bSendUpdate)
        {
            PtRequestAdapterAsync(
                pAdapt,
                NdisRequestSetInformation,
                OID_GEN_CURRENT_PACKET_FILTER,
                &pAdapt->PacketFilter,
                sizeof(pAdapt->PacketFilter),
                PtDiscardCompletedRequest);
        }

    }
    while (FALSE);

    DBGPRINT(MUX_INFO, ("<= SetPacketFilter VELAN %p, Status %x\n", pVElan, Status));
    
    return(Status);
}


NDIS_STATUS
MPSetMulticastList(
    IN PVELAN                   pVElan,
    IN PVOID                    InformationBuffer,
    IN ULONG                    InformationBufferLength,
    OUT PULONG                  pBytesRead,
    OUT PULONG                  pBytesNeeded
    )
/*++

Routine Description:

    Set the multicast list on the specified VELAN miniport.
    We simply validate all information and copy in the multicast
    list.

    We don't forward the multicast list information down since
    we set the lower binding to promisc. mode.

Arguments:

    pVElan - VELAN on which to set the multicast list
    InformationBuffer - pointer to new multicast list
    InformationBufferLength - length in bytes of above list
    pBytesRead - place to return # of bytes read from the above
    pBytesNeeded - place to return expected min # of bytes

Return Value:

    NDIS_STATUS

--*/
{
    NDIS_STATUS         Status;
    PADAPT              pAdapt;
    LOCK_STATE          LockState;

    //
    // Initialize.
    //
    *pBytesNeeded = sizeof(MUX_MAC_ADDRESS);
    *pBytesRead = 0;
    Status = NDIS_STATUS_SUCCESS;

    do
    {
        if (InformationBufferLength % sizeof(MUX_MAC_ADDRESS))
        {
            Status = NDIS_STATUS_INVALID_LENGTH;
            break;
        }

        if (InformationBufferLength > (VELAN_MAX_MCAST_LIST * sizeof(MUX_MAC_ADDRESS)))
        {
            Status = NDIS_STATUS_MULTICAST_FULL;
            *pBytesNeeded = VELAN_MAX_MCAST_LIST * sizeof(MUX_MAC_ADDRESS);
            break;
        }

        pAdapt = pVElan->pAdapt;

        //
        // Grab a Write lock on the adapter so that this operation
        // does not interfere with any receives that might be accessing
        // multicast list information.
        //
        MUX_ACQUIRE_ADAPT_WRITE_LOCK(pAdapt, &LockState);

        NdisZeroMemory(pVElan->McastAddrs,
                       VELAN_MAX_MCAST_LIST * sizeof(MUX_MAC_ADDRESS));
        
        NdisMoveMemory(&pVElan->McastAddrs[0],
                       InformationBuffer,
                       InformationBufferLength);
        
        pVElan->McastAddrCount = InformationBufferLength / sizeof(MUX_MAC_ADDRESS);
        
        MUX_RELEASE_ADAPT_WRITE_LOCK(pAdapt, &LockState);
    }
    while (FALSE);

    return (Status);
}


//
// Careful! Uses static storage for string. Used to simplify DbgPrints
// of MAC addresses.
//
PUCHAR
MacAddrToString(PVOID In)
{
    static UCHAR String[20];
    static PCHAR HexChars = "0123456789abcdef";
    PUCHAR EthAddr = (PUCHAR) In;
    UINT i;
    PUCHAR s;
    
    for (i = 0, s = String; i < 6; i++, EthAddr++)
    {
        *s++ = HexChars[(*EthAddr) >> 4];
        *s++ = HexChars[(*EthAddr) & 0xf];
    }
    *s = '\0';
    return String; 
}


VOID
MPGenerateMacAddr(
    PVELAN                    pVElan
)
/*++

Routine Description:

    Generates a "virtual" MAC address for a VELAN.
    NOTE: this is only a sample implementation of selecting
    a MAC address for the VELAN. Other implementations are possible,
    including using the MAC address of the underlying adapter as
    the MAC address of the VELAN.
    
Arguments:

    pVElan  - Pointer to velan structure

Return Value:

    None

--*/
{
    ETH_COPY_NETWORK_ADDRESS(
            pVElan->CurrentAddress,
            pVElan->PermanentAddress);
    
    DBGPRINT(MUX_LOUD, ("%d CurrentAddress %s\n",
        pVElan->VElanNumber, MacAddrToString(&pVElan->CurrentAddress)));
    DBGPRINT(MUX_LOUD, ("%d PermanentAddress  %s\n",
        pVElan->VElanNumber, MacAddrToString(&pVElan->PermanentAddress)));

}



VOID
MPCancelSendPackets(
    IN NDIS_HANDLE              MiniportAdapterContext,
    IN PVOID                    CancelId
    )
/*++

Routine Description:

    The miniport entry point to handle cancellation of all send packets
    that match the given CancelId. If we have queued any packets that match
    this, then we should dequeue them and call NdisMSendComplete for all
    such packets, with a status of NDIS_STATUS_REQUEST_ABORTED.

    We should also call NdisCancelSendPackets in turn, on each lower binding
    that this adapter corresponds to. This is to let miniports below cancel
    any matching packets.

Arguments:

    MiniportAdapterContext    - pointer to VELAN structure
    CancelId    - ID of packets to be cancelled.

Return Value:

    None

--*/
{
    PVELAN  pVElan = (PVELAN)MiniportAdapterContext;

    //
    // If we queue packets on our VELAN/adapter structure, this would be 
    // the place to acquire a spinlock to it, unlink any packets whose
    // Id matches CancelId, release the spinlock and call NdisMSendComplete
    // with NDIS_STATUS_REQUEST_ABORTED for all unlinked packets.
    //

    //
    // Next, pass this down so that we let the miniport(s) below cancel
    // any packets that they might have queued.
    //
    NdisCancelSendPackets(pVElan->pAdapt->BindingHandle, CancelId);

    return;
}

VOID
MPDevicePnPEvent(
    IN NDIS_HANDLE              MiniportAdapterContext,
    IN NDIS_DEVICE_PNP_EVENT    DevicePnPEvent,
    IN PVOID                    InformationBuffer,
    IN ULONG                    InformationBufferLength
    )
/*++

Routine Description:

    This handler is called to notify us of PnP events directed to
    our miniport device object.

Arguments:

    MiniportAdapterContext - pointer to VELAN structure
    DevicePnPEvent - the event
    InformationBuffer - Points to additional event-specific information
    InformationBufferLength - length of above

Return Value:

    None
--*/
{
    // TBD - add code/comments about processing this.
    //
    
    DBGPRINT(MUX_LOUD, ("==> MPDevicePnPEvent: AdapterContext %08lx\n",MiniportAdapterContext));

	UNREFERENCED_PARAMETER(MiniportAdapterContext);
    UNREFERENCED_PARAMETER(DevicePnPEvent);
    UNREFERENCED_PARAMETER(InformationBuffer);
    UNREFERENCED_PARAMETER(InformationBufferLength);

    DBGPRINT(MUX_LOUD, ("<== MPDevicePnPEvent"));
    
    return;
}


VOID
MPAdapterShutdown(
    IN NDIS_HANDLE              MiniportAdapterContext,
    IN NDIS_SHUTDOWN_ACTION     ShutdownAction
    )
/*++

Routine Description:

    This handler is called to notify us of an impending system shutdown.
    Since this is not a hardware driver, there isn't anything specific
    we need to do about this.

Arguments:

    MiniportAdapterContext  - pointer to VELAN structure

Return Value:

    None
--*/
{
    PVELAN      pVElan = (PVELAN)MiniportAdapterContext;

    DBGPRINT(MUX_LOUD,("==> MPAdapterShutdown\n"));

    UNREFERENCED_PARAMETER(ShutdownAction);

    DBGPRINT(MUX_LOUD,("<== MPAdapterShutdown\n"));
    
    return;
}


VOID
MPUnload(
    IN    PDRIVER_OBJECT        DriverObject
    )
/*++

Routine Description:
    This handler is used to unload the miniport

Arguments:
    DriverObject            Pointer to the system's driver object structure 
                            for this driver.

Return Value:
    None


--*/
{
    NDIS_STATUS Status = NDIS_STATUS_SUCCESS;
    
#if !DBG
    UNREFERENCED_PARAMETER(DriverObject);
#endif
    
    DBGPRINT(MUX_LOUD, ("==> MPUnload: DriverObj %p\n", DriverObject));  

#ifdef OFFLOAD_SUPPORT
    OffloadCleanup();
#endif

    if (ProtHandle != NULL)
    {
        NdisDeregisterProtocolDriver(ProtHandle);
    }
    NdisMDeregisterMiniportDriver(DriverHandle);
    MuxDeInitializeMdlBuffer();
    DBGPRINT(MUX_LOUD, ("<== MPUnload with status %08lx\n", Status));    
}

NDIS_STATUS
MPPause(
    IN  NDIS_HANDLE     MiniportAdapterContext,
    IN  PNDIS_MINIPORT_PAUSE_PARAMETERS  MiniportPauseParameters
    )
/*++

Routine Description:
    This handler is used to pause the miniport. During which, no NET_BUFFER_LIST
    will be indicated to the upper binding as well as status indications.

Arguments:
    MiniportAdapterContext      Pointer to our VELAN
    MiniportPauseParameters

Return Value:
    NDIS_STATUS_SUCCESS

--*/
{
    PVELAN pVElan = (PVELAN)MiniportAdapterContext;

    UNREFERENCED_PARAMETER(MiniportPauseParameters);

    DBGPRINT(MUX_LOUD,("==>MPPause  Adapter %08lx\n",MiniportAdapterContext));

    // Whilst the miniport is being paused, it cannot be restart

    NdisAcquireSpinLock(&pVElan->PauseLock);

    pVElan->Paused = TRUE;

    NdisReleaseSpinLock(&pVElan->PauseLock);

    DBGPRINT(MUX_LOUD,("<==MPPause\n"));

    return NDIS_STATUS_SUCCESS;
}


NDIS_STATUS
MPRestart(
    IN  NDIS_HANDLE     MiniportAdapterContext,
    IN  PNDIS_MINIPORT_RESTART_PARAMETERS  MiniportRestartParameters
    )
/*++

Routine Description:
    This handler is used to restart the miniport.  When the miniport is
    back in the restart state, it can indicate NET_BUFFER_LISTs to the
    upper binding

Arguments:
    MiniportAdapterContext      Pointer to our VELAN
    MiniportRestartParameters

Return Value:
    NDIS_STATUS_SUCCESS

--*/
{
    PVELAN              pVElan = (PVELAN)MiniportAdapterContext;
    PNET_BUFFER_LIST    CurrentNetBufferList;
    NDIS_STATUS         Status;
#ifdef IEEE_VLAN_SUPPORT
    NDIS_PACKET_8021Q_INFO  NdisPacket8021qInfo;
    PUCHAR                  pEthFrameHdr;
    PUCHAR                  pVlanFrameHdr;
    PUCHAR                  pTagHeader;
#endif

    UNREFERENCED_PARAMETER(MiniportRestartParameters);

    DBGPRINT(MUX_LOUD,("==>MPRestart  Adapter %08lx\n",MiniportAdapterContext));

    // While the miniport edge is being restarted, the miniport cannot be paused

    NdisAcquireSpinLock(&pVElan->PauseLock);

    // Indicate the queued NET_BUFFER_LIST to the upper binding.
    
    while(pVElan->PendingNBLs != NULL)
    {
        CurrentNetBufferList = pVElan->PendingNBLs;
        pVElan->PendingNBLs = pVElan->PendingNBLs->Next;
        CurrentNetBufferList->Next = NULL;

        Status = NDIS_STATUS_SUCCESS;

        do
        {
#ifdef IEEE_VLAN_SUPPORT
            Status = PtHandleReceiveTaggingNB(pVElan, CurrentNetBufferList);

            if (Status != NDIS_STATUS_SUCCESS)
            {
                DBGPRINT(MUX_LOUD,("Cloned NBL %08lx receive tagging failed\n",CurrentNetBufferList));
                
                continue;
            }
#endif

            MUX_INCR_STATISTICS64(&pVElan->GoodReceives);

#ifdef IEEE_VLAN_SUPPORT
            NdisPacket8021qInfo.Value = NET_BUFFER_LIST_INFO(CurrentNetBufferList, Ieee8021QNetBufferListInfo);

            if (NdisPacket8021qInfo.Value)
            {
                NdisAdvanceNetBufferDataStart(CurrentNetBufferList->FirstNetBuffer,
                                              VLAN_TAG_HEADER_SIZE,
                                              NULL);
            }
#endif
            NdisReleaseSpinLock(&pVElan->PauseLock);

            NdisMIndicateReceiveNetBufferLists(pVElan->MiniportAdapterHandle,
                                                CurrentNetBufferList,
                                                NDIS_STATUS_RESOURCES,
                                                FALSE);

            NdisAcquireSpinLock(&pVElan->PauseLock);


        } while(FALSE);

        NdisFreeCloneNetBufferList(CurrentNetBufferList, TRUE);
    }

    pVElan->Paused = FALSE;

    pVElan->PendingNBLs = NULL;
    pVElan->PendingNBLsTail = NULL;

    NdisReleaseSpinLock(&pVElan->PauseLock);

    DBGPRINT(MUX_LOUD,("<==MPRestart\n"));

    return NDIS_STATUS_SUCCESS;
}


VOID
MPSendNetBufferLists(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN PNET_BUFFER_LIST NetBufferLists,
    IN ULONG SendFlags,
    IN BOOLEAN DispatchLevel
    )
/*++

Routine Description:

    Send NET_BUFFER_LISTs to the lower binding

Arguments:
    MiniportAdapterContext          Pointer to our VELAN
    NetBufferLists                  Set of NET_BUFFER_LISTs to send
    SendFlags
    DispatchLevel                   TRUE if IRQL == DISPATCH_LEVEL

Return Value:
    None

--*/
{
    // BUGBUG: synchronise with the bind/unbind code and pause
    // BUGBUG: need protection
    // BUGBUG: mention in documentation about halt and the need not to proect
    // this segment of code.

    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PADAPT                      pAdapt = pVElan->pAdapt;
    PNET_BUFFER_LIST            CurrentNetBufferList;
    PNET_BUFFER_LIST            ClonedNetBufferList;
    NDIS_STATUS                 Status = NDIS_STATUS_SUCCESS;
    PVOID                       *pData;

    DBGPRINT(MUX_VERY_LOUD,("==>MpSendNetBufferLists MiniportAdapterContext=%08lx, NetBufferLists=%08lx\n",MiniportAdapterContext,NetBufferLists));

    while(NetBufferLists != NULL)
    {
        CurrentNetBufferList = NetBufferLists;
        NetBufferLists = NetBufferLists->Next;
        CurrentNetBufferList->Next = NULL;

        do
        {
            Status = NdisAllocateNetBufferListContext(CurrentNetBufferList,
                                                      2 * sizeof(PVOID),
                                                      2 * sizeof(PVOID),
                                                      '6XUM');

            if (Status != NDIS_STATUS_SUCCESS)
            {
                break;
            }
            
            pData = (PVOID *)NET_BUFFER_LIST_CONTEXT_DATA_START(CurrentNetBufferList);
            pData[0] = (PVOID)(CurrentNetBufferList->SourceHandle);
            pData[1] = (PVOID)pVElan;


#ifdef IEEE_VLAN_SUPPORT
            Status = MPHandleSendTaggingNB(pVElan, CurrentNetBufferList);

            if (Status != NDIS_STATUS_SUCCESS)
            {
                NdisFreeNetBufferListContext(CurrentNetBufferList,
                                             2 * sizeof(PVOID));
                break;
            }

#endif

            CurrentNetBufferList->SourceHandle = pAdapt->BindingHandle;

            MUX_INCR_PENDING_SENDS(pVElan);
            //
            // Remove this flag, so NDIS will not try to loopback the packets to mux
            //
            SendFlags &= ~SEND_FLAGS_CHECK_FOR_LOOPBACK;

            NdisSendNetBufferLists(pAdapt->BindingHandle,
                                   CurrentNetBufferList,
                                   SendFlags,
                                   DispatchLevel);
        } while(FALSE);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            // Handle failure case

            CurrentNetBufferList->Status = Status;

            NdisMSendNetBufferListsComplete(pVElan->MiniportAdapterHandle,
                                            CurrentNetBufferList,
                                            DispatchLevel);
        }
    }

    DBGPRINT(MUX_VERY_LOUD,("<==MpSendNetBufferLists\n"));
}

VOID MPReturnNetBufferLists(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN PNET_BUFFER_LIST NetBufferLists,
    IN BOOLEAN DispatchLevel
    )
/*++

Routine Description:
    NDIS Miniport entry point called whenever protocols are done with
    a packet that we had indicated up and they had queued up for returning
    later.

Arguments:
    MiniportAdapterContext          Pointer to VELAN structure
    NetBufferLists                  NetBufferLists being returned
    Dispatch                        TRUE if IRQL == DISPATCH_LEVEL

Return Value:
    None

--*/
{
    DBGPRINT(MUX_VERY_LOUD,("==>MPReturnNetBufferLists MiniportAdapterContext=%08lx, NetBufferList=%08lx\n",MiniportAdapterContext,NetBufferLists));

    UNREFERENCED_PARAMETER(MiniportAdapterContext);
    UNREFERENCED_PARAMETER(NetBufferLists);
    UNREFERENCED_PARAMETER(DispatchLevel);

    // Do nothing

    DBGPRINT(MUX_VERY_LOUD,("<==MpReturnNetBufferLists\n"));
}

VOID 
MPCancelSendNetBufferLists(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN PVOID CancelId
    )
/*++

Routine Description:

    The miniport entry point to hanadle cancellation of all send packets that
    match the given CancelId. If we have queued any packets that match this,
    then we should dequeue them and call NdisMSendCompleteNetBufferLists for
    all such packets, with a status of NDIS_STATUS_REQUEST_ABORTED.

    We should also call NdisCancelSendPackets in turn, on each lower binding
    that this adapter corresponds to. This is to let miniports below cancel
    any matching packets.

Arguments:

    MiniportAdapterContext          Pointer to VELAN structure
    CancelID                        ID of NetBufferLists to be cancelled

Return Value:
    None

--*/
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;

    NdisCancelSendNetBufferLists(pVElan->pAdapt->BindingHandle,CancelId);
}

VOID 
MPCancelRequest(
    IN NDIS_HANDLE MiniportAdapterContext,
    IN PNDIS_OID_REQUEST Request
    )
/*++

Routine Description:

    The miniport entry point to hanadle cancellation of a request. This function 
    checks to see if the CancelRequest should be terminated at this level
    or passed down to the next driver. 

Arguments:

    MiniportAdapterContext          Pointer to VELAN structure
    Request                         Request to be cancelled

Return Value:
    None

--*/
{
    PVELAN                      pVElan = (PVELAN)MiniportAdapterContext;
    PMUX_NDIS_REQUEST           pMuxNdisRequest = &pVElan->Request;
    BOOLEAN                     fCancelRequest = FALSE;
    BOOLEAN                     fCompleteRequest = FALSE;


    DBGPRINT(MUX_LOUD, ("MPCancelRequest: VELAN %p, OID %x\n", pVElan, Request->DATA.QUERY_INFORMATION.Oid));
        
    NdisAcquireSpinLock(&pVElan->Lock);
    if (pMuxNdisRequest->OrigRequest == Request)
    {
        fCancelRequest = TRUE;
        pMuxNdisRequest->Refcount++;

    }
    
    NdisReleaseSpinLock(&pVElan->Lock);    

    NdisCancelRequest(pVElan->pAdapt->BindingHandle, &pMuxNdisRequest->Request);

    PtCompleteForwardedRequest(pVElan->pAdapt, 
                                pMuxNdisRequest, 
                                NDIS_STATUS_REQUEST_ABORTED);
   
    
}



#ifdef IEEE_VLAN_SUPPORT

NDIS_STATUS 
MPHandleSendTaggingNB(
    IN PVELAN pVElan,
    IN PNET_BUFFER_LIST NetBufferList
    )
/*++

Routine Description:
    This function is called when the driver supports IEEE 802.1Q taggng. It checks
    the netbuffer to be sent on a VELAN and inserts a tag header if necessary.

Arguments:
    pVElan                          Pointer to VELAN structure
    NetBufferList                   Net Buffer List that 

Return Value:


--*/
{
    NDIS_STATUS             Status;
    NDIS_PACKET_8021Q_INFO  NdisPacket8021qInfo;
    PUCHAR                  pEthFrame = NULL;
    PUCHAR                  pEthFrameNew = NULL;
    PUSHORT                 pTpid;
    PVLAN_TAG_HEADER        pTagHeader;
    PUSHORT                 pTypeLength;


    NdisPacket8021qInfo.Value = NET_BUFFER_LIST_INFO(NetBufferList, Ieee8021QNetBufferListInfo);

    do
    {
        Status = NDIS_STATUS_SUCCESS;

        // If the vlan ID of the virtual miniport is 0, the miniport should act like it doesn't
        // support VELAN tag processing

        if (MuxRecognizedVlanId(pVElan,0))
        {
            break;
        }

        //
        //  Insert a tag only if we have a configured VLAN ID. Note that we do not
        //  support E-RIF
        //

        if (NdisPacket8021qInfo.TagHeader.CanonicalFormatId)
        {
            // Skip the packet, return NDIS_STATUS_FAILURE

            Status = NDIS_STATUS_INVALID_PACKET;
            break;
        }

        // If the there is a tag header and it doesn't match the VLAN ID
        // then the packet is invalid .. ignore!

        if ((NdisPacket8021qInfo.TagHeader.VlanId)
            && (MuxRecognizedVlanId(pVElan,NdisPacket8021qInfo.TagHeader.VlanId)))
        {
            Status = NDIS_STATUS_INVALID_PACKET;
            break;
        }

        // If it already has a VLAN ID then this will be ready to send down

        if (NdisPacket8021qInfo.TagHeader.VlanId)
        {
            Status = NDIS_STATUS_SUCCESS;
            break;
        }

        // Find the start address of the frame
        // CHECK 

        pEthFrame = NdisGetDataBuffer(NetBufferList->FirstNetBuffer,
                                      2 * ETH_LENGTH_OF_ADDRESS,
                                      NULL,
                                      1,
                                      0);

        if (pEthFrame == NULL)
        {
            Status = NDIS_STATUS_INVALID_PACKET;
            break;
        }

        // Retreat the net buffer list

        Status = NdisRetreatNetBufferDataStart(NetBufferList->FirstNetBuffer,
                                               VLAN_TAG_HEADER_SIZE,
                                               0,
                                               MuxAllocateMdl);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        // Get new start address of frame

        pEthFrameNew = NdisGetDataBuffer(NetBufferList->FirstNetBuffer,
                                         VLAN_TAG_HEADER_SIZE,
                                         NULL,
                                         1,
                                         0);

#ifdef DBG
        if ((pEthFrame == NULL) || (pEthFrameNew == NULL))
        {
            ASSERT(0);      // BUGBUG: remove on ship
        }
#endif

        if (pEthFrameNew == NULL)
        {
            NdisAdvanceNetBufferDataStart(NetBufferList->FirstNetBuffer,
                                          VLAN_TAG_HEADER_SIZE,
                                          MuxFreeMdl);

            Status = NDIS_STATUS_INVALID_PACKET;
            
            break;
        }


        RtlMoveMemory(pEthFrameNew, pEthFrame, VLAN_TAG_HEADER_SIZE);

        RtlMoveMemory(pEthFrame, pEthFrame + VLAN_TAG_HEADER_SIZE, (2 * ETH_LENGTH_OF_ADDRESS) - VLAN_TAG_HEADER_SIZE);

        pTpid = (PUSHORT)((PUCHAR)pEthFrame + 2 * ETH_LENGTH_OF_ADDRESS - VLAN_TAG_HEADER_SIZE);
        *pTpid = TPID;
        pTagHeader = (PVLAN_TAG_HEADER)(pTpid + 1);

        //
        // Write IEEE 802.1Q info to packet frame
        //

        INITIALIZE_TAG_HEADER_TO_ZERO(pTagHeader);

        if (NdisPacket8021qInfo.Value)
        {
            SET_USER_PRIORITY_TO_TAG(pTagHeader, NdisPacket8021qInfo.TagHeader.UserPriority);
        }
        else
        {
            SET_USER_PRIORITY_TO_TAG(pTagHeader, 0);
        }

        SET_CANONICAL_FORMAT_ID_TO_TAG(pTagHeader, 0);

        if (NdisPacket8021qInfo.TagHeader.VlanId)
        {
            SET_VLAN_ID_TO_TAG(pTagHeader, NdisPacket8021qInfo.TagHeader.VlanId);
        }
        else
        {
            SET_VLAN_ID_TO_TAG(pTagHeader, pVElan->VlanId);
        }


        pTypeLength = (PUSHORT)((PUCHAR)pTagHeader + sizeof(pTagHeader->TagInfo));
        *pTypeLength = *((PUSHORT)((PUCHAR)pEthFrame + 2 * ETH_LENGTH_OF_ADDRESS));

    } while(FALSE);

    return Status;
}
#endif

