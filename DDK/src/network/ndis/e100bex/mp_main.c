/*++

Copyright (c) 1999  Microsoft Corporation

Module Name:
    mp_main.c

Abstract:
    This module contains NDIS miniport handlers

Revision History:
    Who         When        What
    --------    --------    ----------------------------------------------
    DChen       11-01-99    created

Notes:

--*/

#include "precomp.h"

#if DBG
#define _FILENUMBER     "NIAM"
#endif

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#endif

NDIS_HANDLE     NdisMiniportDriverHandle = NULL;
NDIS_HANDLE     MiniportDriverContext = NULL;


NDIS_STATUS DriverEntry(
    IN  PDRIVER_OBJECT   DriverObject,
    IN  PUNICODE_STRING  RegistryPath
    )
/*++
Routine Description:

Arguments:

    DriverObject    -   pointer to the driver object
    RegistryPath    -   pointer to the driver registry path
     
Return Value:
    
    NDIS_STATUS - the value returned by NdisMRegisterMiniport 
    
--*/
{
    NDIS_STATUS                         Status;
    NDIS_MINIPORT_DRIVER_CHARACTERISTICS MPChar;
    
    DBGPRINT(MP_TRACE, ("====> DriverEntry\n"));

    //
    // Fill in the Miniport characteristics structure with the version numbers 
    // and the entry points for driver-supplied MiniportXxx 
    //
    NdisZeroMemory(&MPChar, sizeof(MPChar));

    MPChar.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_DRIVER_CHARACTERISTICS,
    MPChar.Header.Size = sizeof(NDIS_MINIPORT_DRIVER_CHARACTERISTICS);
    MPChar.Header.Revision = NDIS_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_1;

    MPChar.MajorNdisVersion             = MP_NDIS_MAJOR_VERSION;
    MPChar.MinorNdisVersion             = MP_NDIS_MINOR_VERSION;
    MPChar.MajorDriverVersion           = NIC_MAJOR_DRIVER_VERSION;
    MPChar.MinorDriverVersion           = NIC_MINOR_DRIVER_VERISON;

    MPChar.SetOptionsHandler = MpSetOptions;
    
    MPChar.InitializeHandlerEx          = MPInitialize;
    MPChar.HaltHandlerEx                = MPHalt;

    MPChar.UnloadHandler                = MPUnload,
    
    MPChar.PauseHandler                 = MPPause;      // NEED IMP
    MPChar.RestartHandler               = MPRestart;    // NEED IMP
    MPChar.RequestHandler               = MPRequest;    
    MPChar.SendNetBufferListsHandler    = MPSendNetBufferLists;
    MPChar.ReturnNetBufferListsHandler  = MPReturnNetBufferLists;
    MPChar.CancelSendHandler            = MPCancelSendNetBufferLists;
    MPChar.PnPEventNotifyHandlerEx      = MPPnPEventNotify;
    MPChar.ShutdownHandlerEx            = MPShutdown;
    MPChar.CheckForHangHandlerEx        = MPCheckForHang;
    MPChar.ResetHandlerEx               = MPReset;
    MPChar.CancelRequestHandler         = MPCancelRequest;
    
    
    DBGPRINT(MP_LOUD, ("Calling NdisMRegisterMiniportDriver...\n"));

    Status = NdisMRegisterMiniportDriver(DriverObject,
                                         RegistryPath,
                                         (PNDIS_HANDLE)MiniportDriverContext,
                                         &MPChar,
                                         &NdisMiniportDriverHandle);
    

    DBGPRINT_S(Status, ("<==== DriverEntry, Status=%x\n", Status));

    return Status;
}


NDIS_STATUS
MpSetOptions(
    IN NDIS_HANDLE  NdisMiniportDriverHandle,
    IN NDIS_HANDLE  MiniportDriverContext
    )
{
    UNREFERENCED_PARAMETER(NdisMiniportDriverHandle);
    UNREFERENCED_PARAMETER(MiniportDriverContext);
    
    DBGPRINT(MP_TRACE, ("====> MpSetOptions\n"));

    DBGPRINT(MP_TRACE, ("<==== MpSetOptions\n"));

    return (NDIS_STATUS_SUCCESS);
}


NDIS_STATUS 
MPInitialize(
    IN  NDIS_HANDLE                        MiniportAdapterHandle,
    IN  NDIS_HANDLE                        MiniportDriverContext,
    IN  PNDIS_MINIPORT_INIT_PARAMETERS     MiniportInitParameters
    )
/*++
Routine Description:

    MiniportInitialize handler

Arguments:

    MiniportAdapterHandle   The handle NDIS uses to refer to us
    MiniportDriverContext   Handle passed to NDIS when we registered the driver
    MiniportInitParameters  Initialization parameters
    
Return Value:

    NDIS_STATUS_SUCCESS unless something goes wrong

--*/
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    NDIS_MINIPORT_INTERRUPT_CHARACTERISTICS  Interrupt;
    NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES   RegistrationAttributes;
    NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES        GenericAttributes;
    NDIS_PNP_CAPABILITIES          PowerManagementCapabilities;    
    PMP_ADAPTER     Adapter = NULL;
    PVOID           NetworkAddress;
    UINT            index;
    UINT            uiPnpCommandValue;
    ULONG           ulInfoLen;
    ULONG           InterruptVersion;
    PIO_INTERRUPT_MESSAGE_INFO     InterruptMessageInfo = NULL;
    
#if DBG
    LARGE_INTEGER   TS, TD, TE;
#endif

    DBGPRINT(MP_TRACE, ("====> MPInitialize\n"));


    UNREFERENCED_PARAMETER(MiniportDriverContext);
    
#if DBG
    NdisGetCurrentSystemTime(&TS);
#endif    

    do
    {

        //
        // Allocate MP_ADAPTER structure
        //
        Status = MpAllocAdapterBlock(&Adapter, MiniportAdapterHandle);
        if (Status != NDIS_STATUS_SUCCESS) 
        {
            break;
        }

        Adapter->AdapterHandle = MiniportAdapterHandle;

        NdisZeroMemory(&RegistrationAttributes, sizeof(NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES));
        NdisZeroMemory(&GenericAttributes, sizeof(NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES));

        //
        // setting registration attributes
        //
        RegistrationAttributes.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES;
        RegistrationAttributes.Header.Revision = NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES_REVISION_1;
        RegistrationAttributes.Header.Size = sizeof(NDIS_MINIPORT_ADAPTER_REGISTRATION_ATTRIBUTES);

        RegistrationAttributes.MiniportAdapterContext = (NDIS_HANDLE)Adapter;
        RegistrationAttributes.AttributeFlags = NDIS_MINIPORT_ATTRIBUTES_HARDWARE_DEVICE | 
                                                NDIS_MINIPORT_ATTRIBUTES_BUS_MASTER;
        
        RegistrationAttributes.CheckForHangTimeInSeconds = 2;
        RegistrationAttributes.InterfaceType = NIC_INTERFACE_TYPE;

        Status = NdisMSetMiniportAttributes(MiniportAdapterHandle,
                                            (PNDIS_MINIPORT_ADAPTER_ATTRIBUTES)&RegistrationAttributes);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }
        
        //
        // Read the registry parameters
        //
        Status = NICReadRegParameters(Adapter);
        
        if (Status != NDIS_STATUS_SUCCESS) 
        {
            break;
        }


        
        //
        // Find the physical adapter
        //
        Status = MpFindAdapter(Adapter, MiniportInitParameters->AllocatedResources);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        //
        // Map bus-relative IO range to system IO space
        //
        Status = NdisMRegisterIoPortRange(
                     (PVOID *)&Adapter->PortOffset,
                     Adapter->AdapterHandle,
                     Adapter->IoBaseAddress,
                     Adapter->IoRange);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MP_ERROR, ("NdisMRegisterioPortRange failed\n"));
    
            NdisWriteErrorLogEntry(
                Adapter->AdapterHandle,
                NDIS_ERROR_CODE_BAD_IO_BASE_ADDRESS,
                0);
        
            break;
        }
        
        //
        // Read additional info from NIC such as MAC address
        //
        Status = NICReadAdapterInfo(Adapter);
        if (Status != NDIS_STATUS_SUCCESS) 
        {
            break;
        }


        //
        // set up generic attributes
        //

        GenericAttributes.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES;
        GenericAttributes.Header.Revision = NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES_REVISION_1;
        GenericAttributes.Header.Size = sizeof(NDIS_MINIPORT_ADAPTER_GENERIC_ATTRIBUTES);

        GenericAttributes.MediaType = NIC_MEDIA_TYPE;

        GenericAttributes.MtuSize = NIC_MAX_PACKET_SIZE - NIC_HEADER_SIZE;
        GenericAttributes.MaxXmitLinkSpeed = NIC_MEDIA_MAX_SPEED;
        GenericAttributes.MaxRcvLinkSpeed = NIC_MEDIA_MAX_SPEED;
        GenericAttributes.XmitLinkSpeed = NDIS_LINK_SPEED_UNKNOWN;
        GenericAttributes.RcvLinkSpeed = NDIS_LINK_SPEED_UNKNOWN;
        GenericAttributes.MediaConnectState = MediaConnectStateUnknown;
        GenericAttributes.MediaDuplexState = MediaDuplexStateUnknown;
        GenericAttributes.LookaheadSize = NIC_MAX_PACKET_SIZE - NIC_HEADER_SIZE;

        MPFillPoMgmtCaps (Adapter, 
                          &PowerManagementCapabilities, 
                          &Status,
                          &ulInfoLen);

        GenericAttributes.PowerManagementCapabilities = &PowerManagementCapabilities;

        //
        // do not fail the call because of failure to get PM caps
        //
        Status = NDIS_STATUS_SUCCESS;

        GenericAttributes.MacOptions = NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA | 
                                       NDIS_MAC_OPTION_TRANSFERS_NOT_PEND |
                                       NDIS_MAC_OPTION_NO_LOOPBACK;

        GenericAttributes.SupportedPacketFilters = NDIS_PACKET_TYPE_DIRECTED |
                                                   NDIS_PACKET_TYPE_MULTICAST |
                                                   NDIS_PACKET_TYPE_ALL_MULTICAST |
                                                   NDIS_PACKET_TYPE_BROADCAST;
        
        GenericAttributes.MaxMulticastListSize = NIC_MAX_MCAST_LIST;
        GenericAttributes.MacAddressLength = ETH_LENGTH_OF_ADDRESS;
        NdisMoveMemory(GenericAttributes.PermanentMacAddress,
                       Adapter->PermanentAddress,
                       ETH_LENGTH_OF_ADDRESS);

        NdisMoveMemory(GenericAttributes.CurrentMacAddress,
                       Adapter->CurrentAddress,
                       ETH_LENGTH_OF_ADDRESS);

        
        GenericAttributes.PhysicalMediumType = NdisPhysicalMediumUnspecified;
        GenericAttributes.RecvScaleCapabilities = NULL;
        GenericAttributes.AccessType = NET_IF_ACCESS_BROADCAST; // NET_IF_ACCESS_BROADCAST for a typical ethernet adapter
        GenericAttributes.DirectionType = NET_IF_DIRECTION_SENDRECEIVE; // NET_IF_DIRECTION_SENDRECEIVE for a typical ethernet adapter
        GenericAttributes.ConnectionType = NET_IF_CONNECTION_DEDICATED;  // NET_IF_CONNECTION_DEDICATED for a typical ethernet adapter
        GenericAttributes.IfType = IF_TYPE_ETHERNET_CSMACD; // IF_TYPE_ETHERNET_CSMACD for a typical ethernet adapter (regardless of speed)
        GenericAttributes.IfConnectorPresent = TRUE; // RFC 2665 TRUE if physical adapter

        GenericAttributes.SupportedStatistics = NDIS_STATISTICS_XMIT_OK_SUPPORTED |
                                                NDIS_STATISTICS_RCV_OK_SUPPORTED |
                                                NDIS_STATISTICS_XMIT_ERROR_SUPPORTED |
                                                NDIS_STATISTICS_RCV_ERROR_SUPPORTED |
                                                NDIS_STATISTICS_RCV_CRC_ERROR_SUPPORTED |
                                                NDIS_STATISTICS_RCV_NO_BUFFER_SUPPORTED |
                                                NDIS_STATISTICS_TRANSMIT_QUEUE_LENGTH_SUPPORTED |
                                                NDIS_STATISTICS_GEN_STATISTICS_SUPPORTED;
                                                

        Status = NdisMSetMiniportAttributes(MiniportAdapterHandle,
                                            (PNDIS_MINIPORT_ADAPTER_ATTRIBUTES)&GenericAttributes);



        
        //
        // Allocate all other memory blocks including shared memory
        //
        Status = NICAllocAdapterMemory(Adapter);
        if (Status != NDIS_STATUS_SUCCESS) 
        {
            break;
        }

        //
        // Init send data structures
        //
        NICInitSend(Adapter);

        //
        // Init receive data structures
        //
        Status = NICInitRecv(Adapter);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }
        //
        // Map bus-relative registers to virtual system-space
        // 
        Status = NdisMMapIoSpace(
                     (PVOID *) &(Adapter->CSRAddress),
                     Adapter->AdapterHandle,
                     Adapter->MemPhysAddress,
                     NIC_MAP_IOSPACE_LENGTH);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MP_ERROR, ("NdisMMapIoSpace failed\n"));
    
            NdisWriteErrorLogEntry(
                Adapter->AdapterHandle,
                NDIS_ERROR_CODE_RESOURCE_CONFLICT,
                1,
                ERRLOG_MAP_IO_SPACE);
        
            break;
        }

        DBGPRINT(MP_INFO, ("CSRAddress="PTR_FORMAT"\n", Adapter->CSRAddress));

        //
        // Disable interrupts here which is as soon as possible
        //
        NICDisableInterrupt(Adapter);
                     
        //
        // Register the interrupt
        //
        //
        
        //
        // the embeded NDIS interrupt structure is already zero'ed out
        // as part of the adapter structure
        //
        NdisZeroMemory(&Interrupt, sizeof(NDIS_MINIPORT_INTERRUPT_CHARACTERISTICS));
        
        Interrupt.Header.Type = NDIS_OBJECT_TYPE_MINIPORT_INTERRUPT;
        Interrupt.Header.Revision = NDIS_MINIPORT_INTERRUPT_REVISION_1;
        Interrupt.Header.Size = sizeof(NDIS_MINIPORT_INTERRUPT_CHARACTERISTICS);

        Interrupt.InterruptHandler = MPIsr;
        Interrupt.InterruptDpcHandler = MPHandleInterrupt;
        Interrupt.DisableInterruptHandler = MPDisableInterrupt;
        Interrupt.EnableInterruptHandler = MPEnableInterrupt;
        Interrupt.SharedInterrupt = TRUE;

        //
        // If the driver support MSI
        //
        Interrupt.MessageInfoTable = &Adapter->MessageInfoTable;
        Interrupt.InterruptType = &Adapter->InterruptType;


        Status = NdisMRegisterInterruptEx(Adapter->AdapterHandle,
                                          Adapter,
                                          &Interrupt,
                                          &Adapter->NdisInterruptHandle
                                          );
        
                                        
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MP_ERROR, ("NdisMRegisterInterrupt failed\n"));
    
            NdisWriteErrorLogEntry(
                Adapter->AdapterHandle,
                NDIS_ERROR_CODE_INTERRUPT_CONNECT,
                0);
        
            break;
        }
        //
        // If the driver supports MSI, here it should what kind of interrupt is granted. If MSI is granted,
        // the driver can check Adapter->MessageInfoTable to get MSI information
        //
        
        
        MP_SET_FLAG(Adapter, fMP_ADAPTER_INTERRUPT_IN_USE);

        //
        // Test our adapter hardware
        //
        Status = NICSelfTest(Adapter);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }
        
        //
        // Init the hardware and set up everything
        //
        Status = NICInitializeAdapter(Adapter);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }
        
        //
        // initial state is paused
        //
        Adapter->AdapterState = NicPaused;
        
        //
        // Set the link detection flag
        //
        MP_SET_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION);
      
        //
        // Increment the reference count so halt handler will wait 
        //
        MP_INC_REF(Adapter);        

        //
        // Enable the interrupt
        //
        NICEnableInterrupt(Adapter);

        //
        // Minimize init-time
        //
        NdisMInitializeTimer(
            &Adapter->LinkDetectionTimer, 
            Adapter->AdapterHandle,
            MpLinkDetectionDpc, 
            Adapter);
        
        NdisMSetTimer(&Adapter->LinkDetectionTimer, NIC_LINK_DETECTION_DELAY);

        
    } while (FALSE);

    if (Adapter && (Status != NDIS_STATUS_SUCCESS))
    {
        //
        // Undo everything if it failed
        //
        MP_DEC_REF(Adapter);
        MpFreeAdapter(Adapter);
    }
    
    DBGPRINT_S(Status, ("<==== MPInitialize, Status=%x\n", Status));
    
    return Status;
}


NDIS_STATUS 
MPPause(
    IN  NDIS_HANDLE                         MiniportAdapterContext,    
    IN  PNDIS_MINIPORT_PAUSE_PARAMETERS     MiniportPauseParameters
    )
/*++
 
Routine Description:
    
    MiniportPause handler
    The driver can't indicate any packet, send complete all the pending send requests. 
    and wait for all the packets returned to it.
    
Argument:

    MiniportAdapterContext  Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_PENDING

NOTE: A miniport can't fail the pause request

--*/
{
    PMP_ADAPTER         Adapter = (PMP_ADAPTER) MiniportAdapterContext;
    NDIS_STATUS         Status; 
    LONG                Count;

    UNREFERENCED_PARAMETER(MiniportPauseParameters);
    
    DBGPRINT(MP_TRACE, ("====> MPPause\n"));

    ASSERT(Adapter->AdapterState == NicRunning);

    NdisAcquireSpinLock(&Adapter->RcvLock);
    Adapter->AdapterState = NicPausing;
    NdisReleaseSpinLock(&Adapter->RcvLock);    

    do 
    {
        //
        // Complete all the pending sends
        // 
        NdisAcquireSpinLock(&Adapter->SendLock);
    
        MpFreeQueuedSendNetBufferLists(Adapter);
        NdisReleaseSpinLock(&Adapter->SendLock);

        NdisAcquireSpinLock(&Adapter->RcvLock);        
        MP_DEC_RCV_REF(Adapter);
        Count = MP_GET_RCV_REF(Adapter);
        if (Count ==0)
        {
            Adapter->AdapterState = NicPaused;            
            Status = NDIS_STATUS_SUCCESS;
        }
        else
        {
            Status = NDIS_STATUS_PENDING;
        }
        NdisReleaseSpinLock(&Adapter->RcvLock);    
        
    }
    while (FALSE);
    
    DBGPRINT(MP_TRACE, ("<==== MPPause\n"));
    return Status;
}
        
    
NDIS_STATUS 
MPRestart(
    IN  NDIS_HANDLE                         MiniportAdapterContext,    
    IN  PNDIS_MINIPORT_RESTART_PARAMETERS   MiniportRestartParameters
    )
/*++
 
Routine Description:
    
    MiniportRestart handler
    The driver resumes its normal working state
    
Argument:

    MiniportAdapterContext  Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_PENDING  Can it return pending
    NDIS_STATUS_XXX      The driver fails to restart


--*/
{
    PMP_ADAPTER         Adapter = (PMP_ADAPTER)MiniportAdapterContext;

    UNREFERENCED_PARAMETER(MiniportRestartParameters);

    DBGPRINT(MP_TRACE, ("====> MPRestart\n"));
    NdisAcquireSpinLock(&Adapter->RcvLock);
    MP_INC_RCV_REF(Adapter);
    Adapter->AdapterState = NicRunning;
    NdisReleaseSpinLock(&Adapter->RcvLock);    

    DBGPRINT(MP_TRACE, ("<==== MPRestart\n"));
    return NDIS_STATUS_SUCCESS;

}
 
  
BOOLEAN 
MPCheckForHang(
    IN  NDIS_HANDLE     MiniportAdapterContext
    )
/*++

Routine Description:
    
    MiniportCheckForHang handler
    Ndis call this handler forcing the miniport to check if it needs reset or not,
    If the miniport needs reset, then it should call its reset function
    
Arguments:

    MiniportAdapterContext  Pointer to our adapter

Return Value:

    None.

Note: 
    CheckForHang handler is called in the context of a timer DPC. 
    take advantage of this fact when acquiring/releasing spinlocks

    NOTE: NDIS60 Miniport won't have CheckForHang handler.

--*/
{
    PMP_ADAPTER         Adapter = (PMP_ADAPTER) MiniportAdapterContext;
    NDIS_MEDIA_CONNECT_STATE CurrMediaState;
    NDIS_STATUS         Status;
    PMP_TCB             pMpTcb;
    BOOLEAN             NeedReset = TRUE;
    NDIS_REQUEST_TYPE   RequestType;
    BOOLEAN             DispatchLevel = (NDIS_CURRENT_IRQL() == DISPATCH_LEVEL);
    
    //
    // Just skip this part if the adapter is doing link detection
    //
    do
    {
        if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION))
        {
            NeedReset = FALSE;
            break;
        }

        //
        // any nonrecoverable hardware error?
        //
        if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_NON_RECOVER_ERROR))
        {
            DBGPRINT(MP_WARN, ("Non recoverable error - remove\n"));
            break;
        }
            
        //
        // hardware failure?
        //
        if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_HARDWARE_ERROR))
        {
            DBGPRINT(MP_WARN, ("hardware error - reset\n"));
            break;
        }
          
        //
        // Is send stuck?                  
        //
        MP_ACQUIRE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
        if (Adapter->nBusySend > 0)
        {
            pMpTcb = Adapter->CurrSendHead;
            pMpTcb->Count++;
            if (pMpTcb->Count > NIC_SEND_HANG_THRESHOLD)
            {
                MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
                DBGPRINT(MP_WARN, ("Send stuck - reset\n"));
                break;
            }
        }
    
        NeedReset = FALSE;

        MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
        MP_ACQUIRE_SPIN_LOCK(&Adapter->RcvLock, DispatchLevel);

        //
        // Update the RFD shrink count                                          
        //
        if (Adapter->CurrNumRfd > Adapter->NumRfd)
        {
            Adapter->RfdShrinkCount++;          
        }

        MP_RELEASE_SPIN_LOCK(&Adapter->RcvLock, DispatchLevel);
        MP_ACQUIRE_SPIN_LOCK(&Adapter->Lock, DispatchLevel);
        CurrMediaState = NICGetMediaState(Adapter);

        if (CurrMediaState != Adapter->MediaState)
        {
            Adapter->MediaState = CurrMediaState;
            MPIndicateLinkState(Adapter);
        }
        
        MP_RELEASE_SPIN_LOCK(&Adapter->Lock, DispatchLevel);
    }
    while (FALSE);
    //
    // If need reset, ask NDIS to reset the miniport
    //
    return NeedReset;
}


VOID MPHalt(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_HALT_ACTION        HaltAction
    )

/*++

Routine Description:
    
    MiniportHalt handler
    
Arguments:

    MiniportAdapterContext  Pointer to our adapter
    HaltAction              The reason adapter is being halted

Return Value:

    None
    
--*/
{
    LONG            Count;

    PMP_ADAPTER     Adapter = (PMP_ADAPTER) MiniportAdapterContext;

    if (HaltAction == NdisHaltDeviceSurpriseRemoved)
    {
        //
        // do something here. For example make sure halt will not rely on hardware
        // to generate an interrupt in order to complete a pending operation.
        //
    }

    ASSERT(Adapter->AdapterState == NicPaused);
        
    MP_SET_FLAG(Adapter, fMP_ADAPTER_HALT_IN_PROGRESS);
                                           
    DBGPRINT(MP_TRACE, ("====> MPHalt\n"));

    //
    // Call Shutdown handler to disable interrupts and turn the hardware off 
    // by issuing a full reset. since we are not calling our shutdown handler
    // as a result of a bugcheck, we can use NdisShutdownPowerOff as the reason for
    // shutting down the adapter.
    //
    MPShutdown(MiniportAdapterContext, NdisShutdownPowerOff);
    
    //
    // Deregister interrupt as early as possible
    //
    if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_INTERRUPT_IN_USE))
    {
        NdisMDeregisterInterruptEx(Adapter->NdisInterruptHandle);                           
        MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_INTERRUPT_IN_USE);
    }
    //
    // Decrement the ref count which was incremented in MPInitialize
    //
    Count = MP_DEC_REF(Adapter);

    //
    // Possible non-zero ref counts mean one or more of the following conditions: 
    // 1) Pending async shared memory allocation;
    // 2) DPC's are not finished (e.g. link detection)
    //
    if (Count)
    {
        DBGPRINT(MP_WARN, ("RefCount=%d --- waiting!\n", MP_GET_REF(Adapter)));

        while (TRUE)
        {
            if (NdisWaitEvent(&Adapter->ExitEvent, 2000))
            {
                break;
            }

            DBGPRINT(MP_WARN, ("RefCount=%d --- rewaiting!\n", MP_GET_REF(Adapter)));
        }
    }        

    //
    // Reset the PHY chip.  We do this so that after a warm boot, the PHY will
    // be in a known state, with auto-negotiation enabled.
    //
    ResetPhy(Adapter);

    //
    // Free the entire adapter object, including the shared memory structures.
    //
    MpFreeAdapter(Adapter);

    DBGPRINT(MP_TRACE, ("<==== MPHalt\n"));
}

NDIS_STATUS 
MPReset(
    IN  NDIS_HANDLE     MiniportAdapterContext,
    OUT PBOOLEAN        AddressingReset
    )
/*++

Routine Description:
    
    MiniportReset handler
    
Arguments:

    AddressingReset         To let NDIS know whether we need help from it with our reset
    MiniportAdapterContext  Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_PENDING
    NDIS_STATUS_RESET_IN_PROGRESS
    NDIS_STATUS_HARD_ERRORS

Note:
    
--*/
{
    NDIS_STATUS         Status;
    PNDIS_OID_REQUEST   PendingRequest;
    PMP_ADAPTER         Adapter = (PMP_ADAPTER) MiniportAdapterContext;

    DBGPRINT(MP_TRACE, ("====> MPReset\n"));

    *AddressingReset = TRUE;

    NdisAcquireSpinLock(&Adapter->Lock);
    NdisDprAcquireSpinLock(&Adapter->SendLock);
    NdisDprAcquireSpinLock(&Adapter->RcvLock);

    do
    {
        ASSERT(!MP_TEST_FLAG(Adapter, fMP_ADAPTER_HALT_IN_PROGRESS));
  
        //
        // Is this adapter already doing a reset?
        //
        if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS))
        {
            Status = NDIS_STATUS_RESET_IN_PROGRESS;
            MP_EXIT;
        }

        MP_SET_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS);
        //
        // Abort any pending request
        //
        if (Adapter->PendingRequest != NULL)
        {
            PendingRequest = Adapter->PendingRequest;
            Adapter->PendingRequest = NULL;

            NdisDprReleaseSpinLock(&Adapter->RcvLock);
            NdisDprReleaseSpinLock(&Adapter->SendLock);
            NdisReleaseSpinLock(&Adapter->Lock);
            
            NdisMRequestComplete(Adapter->AdapterHandle, PendingRequest, NDIS_STATUS_REQUEST_ABORTED);

            NdisAcquireSpinLock(&Adapter->Lock);
            NdisDprAcquireSpinLock(&Adapter->SendLock);
            NdisDprAcquireSpinLock(&Adapter->RcvLock);
    
        } 
        //
        // Is this adapter doing link detection?                                      
        //
        if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION))
        {
            DBGPRINT(MP_WARN, ("Reset is pended...\n"));
        
            Status = NDIS_STATUS_PENDING;
            Adapter->bResetPending = TRUE;
            MP_EXIT;
        }
        //
        // Is this adapter going to be removed
        //
        if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_NON_RECOVER_ERROR))
        {
           Status = NDIS_STATUS_HARD_ERRORS;
           if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_REMOVE_IN_PROGRESS))
           {
               MP_EXIT;
           }
           //                       
           // This is an unrecoverable hardware failure. 
           // We need to tell NDIS to remove this miniport
           // 
           MP_SET_FLAG(Adapter, fMP_ADAPTER_REMOVE_IN_PROGRESS);
           MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS);
           
           NdisDprReleaseSpinLock(&Adapter->RcvLock);
           NdisDprReleaseSpinLock(&Adapter->SendLock);
           NdisReleaseSpinLock(&Adapter->Lock);
           
           NdisWriteErrorLogEntry(
               Adapter->AdapterHandle,
               NDIS_ERROR_CODE_HARDWARE_FAILURE,
               1,
               ERRLOG_REMOVE_MINIPORT);
           
           NdisMRemoveMiniport(Adapter->AdapterHandle);
           
           DBGPRINT_S(Status, ("<==== MPReset, Status=%x\n", Status));
            
           return Status;
        }   
                

        //
        // Disable the interrupt and issue a reset to the NIC
        //
        NICDisableInterrupt(Adapter);
        NICIssueSelectiveReset(Adapter);


        //
        // release all the locks and then acquire back the send lock
        // we are going to clean up the send queues
        // which may involve calling Ndis APIs
        // release all the locks before grabbing the send lock to
        // avoid deadlocks
        //
        NdisDprReleaseSpinLock(&Adapter->RcvLock);
        NdisDprReleaseSpinLock(&Adapter->SendLock);
        NdisReleaseSpinLock(&Adapter->Lock);
        
        NdisAcquireSpinLock(&Adapter->SendLock);


        //
        // This is a deserialized miniport, we need to free all the send packets
        // Free the packets on SendWaitList                                                           
        //
        MpFreeQueuedSendNetBufferLists(Adapter);

        //
        // Free the packets being actively sent & stopped
        //
        MpFreeBusySendNetBufferLists(Adapter);

#if DBG
        if (MP_GET_REF(Adapter) > 1)
        {
            DBGPRINT(MP_WARN, ("RefCount=%d\n", MP_GET_REF(Adapter)));
        }
#endif

        NdisZeroMemory(Adapter->MpTcbMem, Adapter->NumTcb * sizeof(MP_TCB));

        //
        // Re-initialize the send structures
        //
        NICInitSend(Adapter);
        
        NdisReleaseSpinLock(&Adapter->SendLock);

        //
        // get all the locks again in the right order
        //
        NdisAcquireSpinLock(&Adapter->Lock);
        NdisDprAcquireSpinLock(&Adapter->SendLock);
        NdisDprAcquireSpinLock(&Adapter->RcvLock);

        //
        // Reset the RFD list and re-start RU         
        //
        NICResetRecv(Adapter);
        Status = NICStartRecv(Adapter);
        if (Status != NDIS_STATUS_SUCCESS) 
        {
            //
            // Are we having failures in a few consecutive resets?                  
            // 
            if (Adapter->HwErrCount < NIC_HARDWARE_ERROR_THRESHOLD)
            {
                //
                // It's not over the threshold yet, let it to continue
                // 
                Adapter->HwErrCount++;
            }
            else
            {
                //
                // This is an unrecoverable hardware failure. 
                // We need to tell NDIS to remove this miniport
                // 
                MP_SET_FLAG(Adapter, fMP_ADAPTER_REMOVE_IN_PROGRESS);
                MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS);
                
                NdisDprReleaseSpinLock(&Adapter->RcvLock);
                NdisDprReleaseSpinLock(&Adapter->SendLock);
                NdisReleaseSpinLock(&Adapter->Lock);
                
                NdisWriteErrorLogEntry(
                    Adapter->AdapterHandle,
                    NDIS_ERROR_CODE_HARDWARE_FAILURE,
                    1,
                    ERRLOG_REMOVE_MINIPORT);
                     
                NdisMRemoveMiniport(Adapter->AdapterHandle);
                
                DBGPRINT_S(Status, ("<==== MPReset, Status=%x\n", Status));
                return Status;
            }
            
            break;
        }
        
        Adapter->HwErrCount = 0;
        MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_HARDWARE_ERROR);

        NICEnableInterrupt(Adapter);

    } 
    while (FALSE);

    MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_RESET_IN_PROGRESS);

    exit:

    NdisDprReleaseSpinLock(&Adapter->RcvLock);
    NdisDprReleaseSpinLock(&Adapter->SendLock);
    NdisReleaseSpinLock(&Adapter->Lock);
        
    DBGPRINT_S(Status, ("<==== MPReset, Status=%x\n", Status));
    return(Status);
}

VOID 
MPReturnNetBufferLists(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PNET_BUFFER_LIST    NetBufferLists,
    IN  BOOLEAN             DispatchLevel
    )
/*++

Routine Description:
    
    MiniportReturnNetBufferLists handler
    NDIS calls this handler to return the ownership of one or more NetBufferLists and 
    their embedded NetBuffers to the miniport driver.
    
Arguments:

    MiniportAdapterContext  Pointer to our adapter
    NetBufferLists          A linked list of NetBufferLists that miniport driver allocated for one or more 
                            previous receive indications. The list can include NetBuferLists from different
                            previous calls to NdisMIndicateNetBufferLists.
    DispatchLevel           A boolean specifying if the caller is at DISPATCH level                            

Return Value:

    None

    
--*/
{
    PMP_ADAPTER         Adapter = (PMP_ADAPTER)MiniportAdapterContext;
    PMP_RFD             pMpRfd;
    ULONG               Count;
    PNET_BUFFER_LIST    NetBufList;
    PNET_BUFFER_LIST    NextNetBufList;

    DBGPRINT(MP_TRACE, ("====> MPReturnNetBufferLists\n"));
    //
    // Later we need to check if the request control size change
    // If yes, return the NetBufferList  to pool, and reallocate 
    // one the RFD
    // 
    MP_ACQUIRE_SPIN_LOCK(&Adapter->RcvLock, DispatchLevel);
    
    for (NetBufList = NetBufferLists;
            NetBufList != NULL;
            NetBufList = NextNetBufList)
    {
        NextNetBufList = NET_BUFFER_LIST_NEXT_NBL(NetBufList);

        pMpRfd = MP_GET_NET_BUFFER_LIST_RFD(NetBufList);
    
        ASSERT(pMpRfd);

        ASSERT(MP_TEST_FLAG(pMpRfd, fMP_RFD_RECV_PEND));
        MP_CLEAR_FLAG(pMpRfd, fMP_RFD_RECV_PEND);

        RemoveEntryList((PLIST_ENTRY)pMpRfd);

        //
        // Decrement the Power Mgmt Ref.
        // 
        Adapter->PoMgmt.OutstandingRecv--;

        //
        // If we have set power request pending, then complete it
        //
        if (((Adapter->PendingRequest)
                && ((Adapter->PendingRequest->RequestType == NdisRequestSetInformation)
                && (Adapter->PendingRequest->DATA.SET_INFORMATION.Oid == OID_PNP_SET_POWER)))
                && (Adapter->PoMgmt.OutstandingRecv == 0))
        {
            MpSetPowerLowComplete(Adapter);
        }
            

        if (Adapter->RfdShrinkCount < NIC_RFD_SHRINK_THRESHOLD
                || MP_TEST_FLAG(pMpRfd, fMP_RFD_ALLOC_FROM_MEM_CHUNK))
        {
            NICReturnRFD(Adapter, pMpRfd);
        }
        else
        {
            //
            // Need to shrink the count of RFDs, if the RFD is not allocated during
            // initialization time, free it.
            // 
            ASSERT(Adapter->CurrNumRfd > Adapter->NumRfd);

            Adapter->RfdShrinkCount = 0;
            NICFreeRfd(Adapter, pMpRfd, TRUE);
            Adapter->CurrNumRfd--;

            DBGPRINT(MP_TRACE, ("Shrink... CurrNumRfd = %d\n", Adapter->CurrNumRfd));
        }

        
        //
        // note that we get the ref count here, but check
        // to see if it is zero and signal the event -after-
        // releasing the SpinLock. otherwise, we may let the Halthandler
        // continue while we are holding a lock.
        //
        MP_DEC_RCV_REF(Adapter);
    }
    

    Count =  MP_GET_RCV_REF(Adapter);
    if ((Count == 0) && (Adapter->AdapterState == NicPausing))
    {
        //
        // If all the NetBufferLists are returned and miniport is pausing,
        // complete the pause
        // 
        
        Adapter->AdapterState = NicPaused;
        MP_RELEASE_SPIN_LOCK(&Adapter->RcvLock, DispatchLevel);
        NdisMPauseComplete(Adapter->AdapterHandle);
        MP_ACQUIRE_SPIN_LOCK(&Adapter->RcvLock, DispatchLevel);
    }
    
    MP_RELEASE_SPIN_LOCK(&Adapter->RcvLock, DispatchLevel);
    
    //
    // Only halting the miniport will set AllPacketsReturnedEvent
    //
    if (Count == 0)
    {
        NdisSetEvent(&Adapter->AllPacketsReturnedEvent);
    }

    DBGPRINT(MP_TRACE, ("<==== MPReturnNetBufferLists\n"));
}


VOID 
MPSendNetBufferLists(
    IN  NDIS_HANDLE         MiniportAdapterContext,
    IN  PNET_BUFFER_LIST    NetBufferList,
    IN  ULONG               SendFlags,
    IN  BOOLEAN             DispatchLevel)
/*++

Routine Description:
    
    MiniportSendNetBufferList handler
    
Arguments:

    MiniportAdapterContext  Pointer to our adapter
    NetBufferList           Pointer to a list of Net Buffer Lists.
    Dispatchlevel           Whether that caller is at DISPATCH_LEVEL or not
    
Return Value:

    None
    
--*/
{

    PMP_ADAPTER         Adapter;
    NDIS_STATUS         Status = NDIS_STATUS_PENDING;
    UINT                NetBufferCount = 0;
    PNET_BUFFER         NetBuffer;
    PNET_BUFFER_LIST    CurrNetBufferList;
    PNET_BUFFER_LIST    NextNetBufferList;
    KIRQL               OldIrql = 0;
    
    DBGPRINT(MP_TRACE, ("====> MPSendNetBufferLists\n"));

    Adapter = (PMP_ADAPTER)MiniportAdapterContext;

    do
    {
        //
        // If the adapter is in Pausing or paused state, just fail the send.
        //
        if ((Adapter->AdapterState == NicPausing) || (Adapter->AdapterState == NicPaused))
        {
            Status =  NDIS_STATUS_PAUSED;
            break;
        }

        MP_ACQUIRE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
        OldIrql = Adapter->SendLock.OldIrql;
    
        //
        // Is this adapter ready for sending?
        // 
        if (MP_IS_NOT_READY(Adapter))
        {
            //
            // there  is link
            //
            if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION))
            {
                //
                // Insert Net Buffer List into the queue
                // 
                for (CurrNetBufferList = NetBufferList;
                        CurrNetBufferList != NULL;
                        CurrNetBufferList = NextNetBufferList)
                {
                    NextNetBufferList = NET_BUFFER_LIST_NEXT_NBL(CurrNetBufferList);
                    //
                    // Get how many net buffers inside the net buffer list
                    //
                    NetBufferCount = 0;
                    for (NetBuffer = NET_BUFFER_LIST_FIRST_NB(CurrNetBufferList);
                            NetBuffer != NULL; 
                            NetBuffer = NET_BUFFER_NEXT_NB(NetBuffer))
                    {
                        NetBufferCount++;
                    }
                    ASSERT(NetBufferCount > 0);
                    MP_GET_NET_BUFFER_LIST_REF_COUNT(CurrNetBufferList) = NetBufferCount;
                    MP_GET_NET_BUFFER_LIST_NEXT_SEND(CurrNetBufferList) = NET_BUFFER_LIST_FIRST_NB(CurrNetBufferList);
                    NET_BUFFER_LIST_COMPLETION_STATUS(CurrNetBufferList) = NDIS_STATUS_SUCCESS;
                    InsertTailQueue(&Adapter->SendWaitQueue, 
                               MP_GET_NET_BUFFER_LIST_LINK(CurrNetBufferList));
                    Adapter->nWaitSend++;
                    DBGPRINT(MP_WARN, ("MPSendNetBufferLists: link detection - queue NetBufferList "PTR_FORMAT"\n", CurrNetBufferList));
                }
                Adapter->SendLock.OldIrql = OldIrql;
                MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
                
                break;
            }
        
            //
            // Adapter is not ready and there is not link
            //
            Status = MP_GET_STATUS_FROM_FLAGS(Adapter);
            
            Adapter->SendLock.OldIrql = OldIrql;  
            MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
            break;
        }

        //
        // Adapter is ready, send this net buffer list, in this case, we always return pending     
        //
        for (CurrNetBufferList = NetBufferList;
                CurrNetBufferList != NULL;
                CurrNetBufferList = NextNetBufferList)
        {
            NextNetBufferList = NET_BUFFER_LIST_NEXT_NBL(CurrNetBufferList);
            //
            // Get how many net buffers inside the net buffer list
            //
            NetBufferCount = 0;
            for (NetBuffer = NET_BUFFER_LIST_FIRST_NB(CurrNetBufferList);
                    NetBuffer != NULL; 
                    NetBuffer = NET_BUFFER_NEXT_NB(NetBuffer))
            {
                NetBufferCount++;
            }
            ASSERT(NetBufferCount > 0);
            MP_GET_NET_BUFFER_LIST_REF_COUNT(CurrNetBufferList) = NetBufferCount;
            //
            // queue is not empty or tcb is not available, or another thread is sending
            // a NetBufferList.
            //
            if (!IsQueueEmpty(&Adapter->SendWaitQueue) || 
                (!MP_TCB_RESOURCES_AVAIABLE(Adapter) ||
                 Adapter->SendingNetBufferList != NULL))
            {
                //
                // The first net buffer is the buffer to send
                //
                MP_GET_NET_BUFFER_LIST_NEXT_SEND(CurrNetBufferList) = NET_BUFFER_LIST_FIRST_NB(CurrNetBufferList);
                NET_BUFFER_LIST_COMPLETION_STATUS(CurrNetBufferList) = NDIS_STATUS_SUCCESS;
                InsertTailQueue(&Adapter->SendWaitQueue, 
                            MP_GET_NET_BUFFER_LIST_LINK(CurrNetBufferList));
                Adapter->nWaitSend++;
            }
            else
            {
                Adapter->SendingNetBufferList = CurrNetBufferList;
                NET_BUFFER_LIST_COMPLETION_STATUS(CurrNetBufferList) = NDIS_STATUS_SUCCESS;
                MiniportSendNetBufferList(Adapter, CurrNetBufferList, FALSE);
            }
                
        }
    
        Adapter->SendLock.OldIrql = OldIrql;
        MP_RELEASE_SPIN_LOCK(&Adapter->SendLock, DispatchLevel);
    }
    while (FALSE);

    if (Status != NDIS_STATUS_PENDING)
    {
        for (CurrNetBufferList = NetBufferList;
                 CurrNetBufferList != NULL;
                 CurrNetBufferList = NextNetBufferList)
        {
            NextNetBufferList = NET_BUFFER_LIST_NEXT_NBL(CurrNetBufferList);
            NET_BUFFER_LIST_COMPLETION_STATUS(CurrNetBufferList) = Status;
        }
                  
        NdisMSendNetBufferListsComplete(
            MP_GET_ADAPTER_HANDLE(Adapter),
            NetBufferList,
            DispatchLevel);   
    }
    DBGPRINT(MP_TRACE, ("<==== MPSendNetBufferLists\n"));
}

VOID MPShutdown(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_SHUTDOWN_ACTION    ShutdownAction
    )
/*++

Routine Description:
    
    MiniportShutdown handler
    
Arguments:

    MiniportAdapterContext  Pointer to our adapter
    ShutdownAction          The reason for Shutdown

Return Value:

    None
    
--*/
{
    PMP_ADAPTER     Adapter = (PMP_ADAPTER)MiniportAdapterContext;

    UNREFERENCED_PARAMETER(ShutdownAction);
    
    DBGPRINT(MP_TRACE, ("====> MPShutdown\n"));

    //
    // Disable interrupt and issue a full reset
    //
    NICDisableInterrupt(Adapter);
    NICIssueFullReset(Adapter);

    DBGPRINT(MP_TRACE, ("<==== MPShutdown\n"));
}

VOID 
MPAllocateComplete(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  PVOID                   VirtualAddress,
    IN  PNDIS_PHYSICAL_ADDRESS  PhysicalAddress,
    IN  ULONG                   Length,
    IN  PVOID                   Context)
/*++

Routine Description:
    
    MiniportAllocateComplete handler
    This handler is needed because we make calls to NdisMAllocateSharedMemoryAsync
    
Arguments:

    MiniportAdapterContext  Pointer to our adapter
    VirtualAddress          Pointer to the allocated memory block 
    PhysicalAddress         Physical address of the memory block       
    Length                  Length of the memory block                
    Context                 Context in NdisMAllocateSharedMemoryAsync              

Return Value:

    None
    
--*/
{
    ULONG           ErrorValue;
    PMP_ADAPTER     Adapter = (PMP_ADAPTER)MiniportAdapterContext;
    PMP_RFD         pMpRfd = (PMP_RFD)Context;

    DBGPRINT(MP_TRACE, ("==== MPAllocateComplete\n"));

    ASSERT(pMpRfd);
    ASSERT(MP_TEST_FLAG(pMpRfd, fMP_RFD_ALLOC_PEND));
    MP_CLEAR_FLAG(pMpRfd, fMP_RFD_ALLOC_PEND);

    NdisAcquireSpinLock(&Adapter->RcvLock);

    //
    // Is allocation successful?  
    //
    if (VirtualAddress)
    {
        ASSERT(Length == Adapter->HwRfdSize);
        
        pMpRfd->OriginalHwRfd = (PHW_RFD)VirtualAddress;
        pMpRfd->OriginalHwRfdPa = *PhysicalAddress;

        //
        // First get a HwRfd at 8 byte boundary from OriginalHwRfd
        //
        pMpRfd->HwRfd = (PHW_RFD)DATA_ALIGN(pMpRfd->OriginalHwRfd);
        //
        // Then shift HwRfd so that the data(after ethernet header) is at 8 bytes boundary
        //
        pMpRfd->HwRfd = (PHW_RFD)((PUCHAR)pMpRfd->HwRfd + HWRFD_SHIFT_OFFSET);
        //
        // Update physical address as well
        //
        pMpRfd->HwRfdPa.QuadPart = pMpRfd->OriginalHwRfdPa.QuadPart 
                                   + BYTES_SHIFT(pMpRfd->HwRfd, pMpRfd->OriginalHwRfd);
        
        ErrorValue = NICAllocRfd(Adapter, pMpRfd);
        if (ErrorValue == 0)
        {
            // Add this RFD to the RecvList
            Adapter->CurrNumRfd++;                      
            NICReturnRFD(Adapter, pMpRfd);

            ASSERT(Adapter->CurrNumRfd <= Adapter->MaxNumRfd);
            DBGPRINT(MP_TRACE, ("CurrNumRfd=%d\n", Adapter->CurrNumRfd));
        }
        else
        {
            NdisFreeToNPagedLookasideList(&Adapter->RecvLookaside, pMpRfd);
        }
    }
    else
    {
        NdisFreeToNPagedLookasideList(&Adapter->RecvLookaside, pMpRfd);
    }

    Adapter->bAllocNewRfd = FALSE;
    MP_DEC_REF(Adapter);

    if (MP_GET_REF(Adapter) == 0)
    {
        NdisSetEvent(&Adapter->ExitEvent);
    }

    NdisReleaseSpinLock(&Adapter->RcvLock);
}

BOOLEAN 
MPIsr(
    IN  NDIS_HANDLE     MiniportInterruptContext,
    OUT PBOOLEAN        QueueMiniportInterruptDpcHandler,
    OUT PULONG          TargetProcessors)
/*++

Routine Description:
    
    MiniportIsr handler
    
Arguments:

    MiniportInterruptContext: Pointer to the interrupt context.
        In our case, this is a pointer to our adapter structure.
        
    QueueMiniportInterruptDpcHandler: TRUE on return if MiniportHandleInterrupt 
        should be called on default CPU
        
    TargetProcessors: Pointer to a bitmap specifying 
        Target processors which should run the DPC

Return Value:

    TRUE  --- The miniport recognizes the interrupt
    FALSE   --- Otherwise
    
--*/
{
    PMP_ADAPTER  Adapter = (PMP_ADAPTER)MiniportInterruptContext;
    BOOLEAN                         InterruptRecognized = FALSE;
    
    DBGPRINT(MP_LOUD, ("====> MPIsr\n"));
    
    do 
    {
        
        //
        // If the adapter is in low power state, then it should not 
        // recognize any interrupt
        // 
        if (Adapter->CurrentPowerState > NdisDeviceStateD0)
        {
            InterruptRecognized = FALSE;
            *QueueMiniportInterruptDpcHandler = FALSE;
            break;
        }
        //
        // We process the interrupt if it's not disabled and it's active                  
        //
        if (!NIC_INTERRUPT_DISABLED(Adapter) && NIC_INTERRUPT_ACTIVE(Adapter))
        {
            InterruptRecognized = TRUE;
            *QueueMiniportInterruptDpcHandler = TRUE;
        
            //
            // Disable the interrupt (will be re-enabled in MPHandleInterrupt
            //
            NICDisableInterrupt(Adapter);
        }
        else
        {
            InterruptRecognized = FALSE;
            *QueueMiniportInterruptDpcHandler = FALSE;
        }
    }
    while (FALSE);    

    DBGPRINT(MP_LOUD, ("<==== MPIsr\n"));
    
    return InterruptRecognized;
}


VOID 
MPHandleInterrupt(
    IN  NDIS_HANDLE  MiniportInterruptContext
    )
/*++

Routine Description:
    
    MiniportHandleInterrupt handler
    
Arguments:

    MiniportInterruptContext:  Pointer to the interrupt context.
        In our case, this is a pointer to our adapter structure.

Return Value:

    None
    
--*/
{
    PMP_ADAPTER  Adapter = (PMP_ADAPTER)MiniportInterruptContext;
    USHORT       IntStatus;

    //
    // Acknowledge the interrupt(s) and get the interrupt status
    //
    NIC_ACK_INTERRUPT(Adapter, IntStatus);
    //    
    // Handle receive interrupt    
    //
    NdisDprAcquireSpinLock(&Adapter->RcvLock);

    MpHandleRecvInterrupt(Adapter);

    NdisDprReleaseSpinLock(&Adapter->RcvLock);
    
    //
    // Handle send interrupt    
    //
    NdisDprAcquireSpinLock(&Adapter->SendLock);

    MpHandleSendInterrupt(Adapter);

    NdisDprReleaseSpinLock(&Adapter->SendLock);

    //
    // Start the receive unit if it had stopped
    //
    NdisDprAcquireSpinLock(&Adapter->RcvLock);

    NICStartRecv(Adapter);

    NdisDprReleaseSpinLock(&Adapter->RcvLock);

    
    //
    // Re-enable the interrupt (disabled in MPIsr)
    //
    NdisMSynchronizeWithInterruptEx(
        Adapter->NdisInterruptHandle,
        0,
        NICEnableInterrupt,
        Adapter);
}


VOID
MPDisableInterrupt(
    IN  NDIS_HANDLE  MiniportInterruptContext
    )
/*++

Routine Description:
    
    MiniportDisableInterrupt handler
    
Arguments:

    MiniportInterruptContext:  Pointer to the interrupt context.
        In our case, this is a pointer to our adapter structure.

Return Value:

    None
    
--*/
{
    PMP_ADAPTER  Adapter = (PMP_ADAPTER)MiniportInterruptContext;

    //
    // Re-enable the interrupt (disabled in MPIsr)
    //
    NdisMSynchronizeWithInterruptEx(
        Adapter->NdisInterruptHandle,
        0,
        NICDisableInterrupt,
        Adapter);
}

VOID
MPEnableInterrupt(
    IN  NDIS_HANDLE  MiniportInterruptContext
)
/*++

Routine Description:
    
    MiniportEnableInterrupt handler
    
Arguments:

    MiniportInterruptContext:  Pointer to the interrupt context.
        In our case, this is a pointer to our adapter structure.

Return Value:

    None
    
--*/

{
    PMP_ADAPTER  Adapter = (PMP_ADAPTER)MiniportInterruptContext;
    
    //
    // Re-enable the interrupt
    //
    NdisMSynchronizeWithInterruptEx(
        Adapter->NdisInterruptHandle,
        0,
        NICEnableInterrupt,
        Adapter);
    
}



//
// NOTE: We need to change Cancel APIs
//
VOID 
MPCancelSendNetBufferLists(
    IN  NDIS_HANDLE     MiniportAdapterContext,
    IN  PVOID           CancelId)
/*++

Routine Description:
    
    MiniportCancelSendpackets handler - NDIS51 and later
    
Arguments:

    MiniportAdapterContext      Pointer to our adapter
    CancelId                    All the Net Buffer Lists with this Id should be cancelled

Return Value:

    None
    
--*/
{

    UNREFERENCED_PARAMETER(MiniportAdapterContext);
    UNREFERENCED_PARAMETER(CancelId);
    
    DBGPRINT(MP_TRACE, ("====> MPCancelSendNetBufferLists\n"));
    //
    // for the time being, do nothing. this will be replaced with
    // the actual function after NCC
    //
    
    DBGPRINT(MP_TRACE, ("<==== MPCancelSendNetBufferLists\n"));
    return;

}

VOID 
MPPnPEventNotify(
    IN  NDIS_HANDLE             MiniportAdapterContext,
    IN  NDIS_DEVICE_PNP_EVENT   PnPEvent,
    IN  PVOID                   InformationBuffer,
    IN  ULONG                   InformationBufferLength
    )
/*++

Routine Description:
    
    MiniportPnPEventNotify handler - NDIS51 and later
    
Arguments:

    MiniportAdapterContext      Pointer to our adapter
    PnPEvent                    Self-explanatory 
    InformationBuffer           Self-explanatory 
    InformationBufferLength     Self-explanatory 

Return Value:

    None
    
--*/
{
    PMP_ADAPTER     Adapter = (PMP_ADAPTER)MiniportAdapterContext;

    //
    // Turn off the warings.
    //
    UNREFERENCED_PARAMETER(InformationBuffer);
    UNREFERENCED_PARAMETER(InformationBufferLength);
    UNREFERENCED_PARAMETER(Adapter);
    
    DBGPRINT(MP_TRACE, ("====> MPPnPEventNotify\n"));

    switch (PnPEvent)
    {
        case NdisDevicePnPEventQueryRemoved:
            DBGPRINT(MP_WARN, ("MPPnPEventNotify: NdisDevicePnPEventQueryRemoved\n"));
            break;

        case NdisDevicePnPEventRemoved:
            DBGPRINT(MP_WARN, ("MPPnPEventNotify: NdisDevicePnPEventRemoved\n"));
            break;       

        case NdisDevicePnPEventSurpriseRemoved:
            DBGPRINT(MP_WARN, ("MPPnPEventNotify: NdisDevicePnPEventSurpriseRemoved\n"));
            break;

        case NdisDevicePnPEventQueryStopped:
            DBGPRINT(MP_WARN, ("MPPnPEventNotify: NdisDevicePnPEventQueryStopped\n"));
            break;

        case NdisDevicePnPEventStopped:
            DBGPRINT(MP_WARN, ("MPPnPEventNotify: NdisDevicePnPEventStopped\n"));
            break;      
            
        case NdisDevicePnPEventPowerProfileChanged:
            DBGPRINT(MP_WARN, ("MPPnPEventNotify: NdisDevicePnPEventPowerProfileChanged\n"));
            break;      
            
        default:
            DBGPRINT(MP_ERROR, ("MPPnPEventNotify: unknown PnP event %x \n", PnPEvent));
            break;         
    }

    DBGPRINT(MP_TRACE, ("<==== MPPnPEventNotify\n"));

}


VOID 
MPUnload(
    IN  PDRIVER_OBJECT  DriverObject
    )
/*++

Routine Description:
    
    The Unload handler
    This handler is registered through NdisMRegisterUnloadHandler
    
Arguments:

    DriverObject        Not used

Return Value:

    None
    
--*/
{
    //
    // Deregister Miniport driver
    //
    NdisMDeregisterMiniportDriver(NdisMiniportDriverHandle);
}

