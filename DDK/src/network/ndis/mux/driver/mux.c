/*++

Copyright (c) 1992-2000  Microsoft Corporation
 
Module Name:
 
    mux.c

Abstract:

    DriverEntry and NT dispatch functions for the NDIS MUX Intermediate
    Miniport driver sample.

Environment:

    Kernel mode

Revision History:


--*/


#include "precomp.h"
#include "offload.h"
#pragma hdrstop

#define MODULE_NUMBER           MODULE_MUX

#pragma NDIS_INIT_FUNCTION(DriverEntry)


#if DBG
//
// Debug level for mux driver
// 
INT     muxDebugLevel = MUX_WARN;

#endif //DBG
//
//  G L O B A L   V A R I A B L E S
//  -----------   -----------------
//

NDIS_MEDIUM        MediumArray[1] =
                    {
                        NdisMedium802_3,    // Ethernet
                    };


//
// Global Mutex protects the AdapterList;
// see macros MUX_ACQUIRE/RELEASE_MUTEX
//
MUX_MUTEX          GlobalMutex = {0};

//
// List of all bound adapters.
//
LIST_ENTRY         AdapterList;

//
// Total number of VELAN miniports in existance:
//
LONG               MiniportCount = 0;

//
// Used to assign VELAN numbers (which are used to generate MAC
// addresses).
//
ULONG              NextVElanNumber = 0; // monotonically increasing count

//
// Some global NDIS handles:
//
NDIS_HANDLE        ProtHandle = NULL;       // From NdisRegisterProtocolDriver
NDIS_HANDLE        DriverHandle = NULL;     // From NdisMRegisterMiniportDriver
NDIS_HANDLE        NdisDeviceHandle = NULL; // From NdisMRegisterDeviceEx

PDEVICE_OBJECT     ControlDeviceObject = NULL;  // Device for IOCTLs
MUX_MUTEX          ControlDeviceMutex;



NTSTATUS
DriverEntry(
    IN    PDRIVER_OBJECT        DriverObject,
    IN    PUNICODE_STRING       RegistryPath
    )
/*++

Routine Description:

    First entry point to be called, when this driver is loaded.
    Register with NDIS as an intermediate driver.

Arguments:

    DriverObject - pointer to the system's driver object structure
        for this driver
    
    RegistryPath - system's registry path for this driver
    
Return Value:

    STATUS_SUCCESS if all initialization is successful, STATUS_XXX
    error code if not.

--*/
{
    NDIS_STATUS                     Status;
    NDIS_PROTOCOL_DRIVER_CHARACTERISTICS   PChars;
    NDIS_MINIPORT_DRIVER_CHARACTERISTICS   MChars;
    NDIS_STRING                     Name;
    

    NdisInitializeListHead(&AdapterList);
    MUX_INIT_MUTEX(&GlobalMutex);
    MUX_INIT_MUTEX(&ControlDeviceMutex);


    do
    {
        //
        // Preallocate MDLs for Netbuffer advance and retreat operation
        //

        Status = MuxInitializeMdlBuffer();

        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MUX_LOUD,("MDL allocation failed\n"));
            break;
        }

        //
        // Register the miniport with NDIS. Note that it is the
        // miniport which was started as a driver and not the protocol.
        // Also the miniport must be registered prior to the protocol
        // since the protocol's BindAdapter handler can be initiated
        // anytime and when it is, it must be ready to
        // start driver instances.
        //
        NdisZeroMemory(&MChars, sizeof(NDIS_MINIPORT_DRIVER_CHARACTERISTICS));

        MChars.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
        MChars.Header.Size = sizeof(NDIS_MINIPORT_DRIVER_CHARACTERISTICS);
        MChars.Header.Revision = NDIS_MINIPORT_DRIVER_CHARACTERISTICS_REVISION_1;
        
        MChars.MajorNdisVersion = MUX_MAJOR_NDIS_VERSION;
        MChars.MinorNdisVersion = MUX_MINOR_NDIS_VERSION;

        // BUGBUG: rewrite comment
        // it is better to report something other than NDIS version for the driver version
        //
        MChars.MajorDriverVersion = MUX_MAJOR_DRIVER_VERSION;
        MChars.MinorDriverVersion = MUX_MINOR_DRIVER_VERSION;

        MChars.SetOptionsHandler = MpSetOptions;
        MChars.InitializeHandlerEx = MPInitialize;
        MChars.UnloadHandler = MPUnload;
        MChars.HaltHandlerEx = MPHalt;

        MChars.RequestHandler = MPRequest;

        MChars.CancelSendHandler = MPCancelSendNetBufferLists;
        MChars.PnPEventNotifyHandlerEx = MPDevicePnPEvent;
        MChars.ShutdownHandlerEx = MPAdapterShutdown;
        MChars.CancelRequestHandler =  MPCancelRequest;

        //
        // We will disable the check for hang timeout so we do not
        // need a check for hang handler!
        //
        MChars.CheckForHangHandlerEx = NULL;

        MChars.ReturnNetBufferListsHandler = MPReturnNetBufferLists;
        MChars.SendNetBufferListsHandler = MPSendNetBufferLists;

        MChars.PauseHandler = MPPause;
        MChars.RestartHandler = MPRestart;

        MChars.Flags = NDIS_INTERMEDIATE_DRIVER;

        Status = NdisMRegisterMiniportDriver(DriverObject,
                                             RegistryPath,
                                             NULL,
                                             &MChars,
                                             &DriverHandle);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        //
        // Now register the protocol.
        //
        NdisZeroMemory(&PChars, sizeof(NDIS_PROTOCOL_DRIVER_CHARACTERISTICS));

        PChars.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
        PChars.Header.Size = sizeof(NDIS_PROTOCOL_DRIVER_CHARACTERISTICS);
        PChars.Header.Revision = NDIS_PROTOCOL_DRIVER_CHARACTERISTICS_REVISION_1;
            
        PChars.MajorNdisVersion = MUX_PROT_MAJOR_NDIS_VERSION;
        PChars.MinorNdisVersion = MUX_PROT_MINOR_NDIS_VERSION;
        
        PChars.MajorDriverVersion = MUX_MAJOR_DRIVER_VERSION;
        PChars.MinorDriverVersion = MUX_MINOR_DRIVER_VERSION;

        PChars.SetOptionsHandler = PtSetOptions;
        
        //
        // Make sure the protocol-name matches the service-name
        // (from the INF) under which this protocol is installed.
        // This is needed to ensure that NDIS can correctly determine
        // the binding and call us to bind to miniports below.
        //
        NdisInitUnicodeString(&Name, L"MUXP");    // Protocol name
        PChars.Name = Name;
        PChars.OpenAdapterCompleteHandlerEx = PtOpenAdapterComplete;
        PChars.CloseAdapterCompleteHandlerEx = PtCloseAdapterComplete;

        PChars.ReceiveNetBufferListHandler = PtReceiveNBL;
        PChars.SendNetBufferListsCompleteHandler = PtSendNBLComplete;
        PChars.RequestCompleteHandlerEx = PtRequestComplete;
        PChars.StatusHandlerEx = PtStatus;
        PChars.BindAdapterHandlerEx = PtBindAdapter;
        PChars.UnbindAdapterHandlerEx = PtUnbindAdapter;
        PChars.PnPEventHandler= PtPNPHandler;

        Status = NdisRegisterProtocolDriver(NULL,
                                            &PChars,
                                            &ProtHandle);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            NdisMDeregisterMiniportDriver(DriverHandle);
            break;
        }

#ifdef OFFLOAD_SUPPORT        
        Status = OffloadInitialize();
        if (Status != NDIS_STATUS_SUCCESS) {
            NdisDeregisterProtocolDriver(ProtHandle);
            NdisMDeregisterMiniportDriver(DriverHandle);
            break;
        }
#endif

        //
        // Let NDIS know of the association between our protocol
        // and miniport entities.
        //
        NdisIMAssociateMiniport(DriverHandle, ProtHandle);
    }
    while (FALSE);

    return(Status);
}

NDIS_STATUS
MpSetOptions(
    IN  NDIS_HANDLE             NdisDriverHandle,
    IN  NDIS_HANDLE             DriverContext
    )
/*++

Routine Description:
    This routine registers the optional handlers for the MUX MINIPORT driver
    with NDIS.
    
Arguments:

    None

Return Value:

    NDIS_STATUS_SUCCESS if we successfully register a device object.

--*/
{
#ifndef OFFLOAD_SUPPORT
    UNREFERENCED_PARAMETER(NdisDriverHandle);
    UNREFERENCED_PARAMETER(DriverContext);
    return NDIS_STATUS_SUCCESS;
#else
    NDIS_STATUS Status;
    UNREFERENCED_PARAMETER(DriverContext);

    Status = MPSetGenericOffloadClientHandlers(NdisDriverHandle);

    if (Status != NDIS_STATUS_SUCCESS) {
        return Status;
    }
    
    Status = MPSetTcpOffloadClientHandlers(NdisDriverHandle);

    if (Status != NDIS_STATUS_SUCCESS) {
        return Status;
    }

    Status = NdisMGetOffloadHandlers(NdisDriverHandle, NdisTcpChimneyOffload,
                (PNDIS_OFFLOAD_EVENT_HANDLERS*)&TcpOffloadEventHandlers);

    return Status;
#endif
}


NDIS_STATUS
PtSetOptions(
    IN  NDIS_HANDLE             NdisDriverHandle,
    IN  NDIS_HANDLE             DriverContext
    )
/*++

Routine Description:
    This routine registers the optional handlers for the MUX PROTOCOL driver
    with NDIS.
    
Arguments:

    None

Return Value:

    NDIS_STATUS_SUCCESS if we successfully register a device object.

--*/
{
#ifndef OFFLOAD_SUPPORT
    UNREFERENCED_PARAMETER(NdisDriverHandle);
    UNREFERENCED_PARAMETER(DriverContext);
    return NDIS_STATUS_SUCCESS;
#else
    UNREFERENCED_PARAMETER(DriverContext);
    return PtSetGenericOffloadClientHandlers(NdisDriverHandle);
#endif
}


NDIS_STATUS
PtRegisterDevice(
    VOID
    )
/*++

Routine Description:

    Register an ioctl interface - a device object to be used for this
    purpose is created by NDIS when we call NdisMRegisterDevice.

    This routine is called whenever a new miniport instance is
    initialized. However, we only create one global device object,
    when the first miniport instance is initialized. This routine
    handles potential race conditions with PtDeregisterDevice via
    the ControlDeviceMutex.

    NOTE: do not call this from DriverEntry; it will prevent the driver
    from being unloaded (e.g. on uninstall).

Arguments:

    None

Return Value:

    NDIS_STATUS_SUCCESS if we successfully register a device object.

--*/
{
    NDIS_STATUS         Status = NDIS_STATUS_SUCCESS;
    UNICODE_STRING      DeviceName;
    UNICODE_STRING      DeviceLinkUnicodeString;
    NDIS_DEVICE_OBJECT_ATTRIBUTES   DeviceObjectAttributes;
    PDRIVER_DISPATCH    DispatchTable[IRP_MJ_MAXIMUM_FUNCTION+1];



    DBGPRINT(MUX_LOUD, ("==>PtRegisterDevice\n"));

    MUX_ACQUIRE_MUTEX(&ControlDeviceMutex);

    ++MiniportCount;
    
    if (1 == MiniportCount)
    {
        NdisZeroMemory(DispatchTable, (IRP_MJ_MAXIMUM_FUNCTION+1) * sizeof(PDRIVER_DISPATCH));
        
        DispatchTable[IRP_MJ_CREATE] = PtDispatch;
        DispatchTable[IRP_MJ_CLEANUP] = PtDispatch;
        DispatchTable[IRP_MJ_CLOSE] = PtDispatch;
        DispatchTable[IRP_MJ_DEVICE_CONTROL] = PtDispatch;
        

        NdisInitUnicodeString(&DeviceName, NTDEVICE_STRING);
        NdisInitUnicodeString(&DeviceLinkUnicodeString, LINKNAME_STRING);

        NdisZeroMemory(&DeviceObjectAttributes, sizeof(NDIS_DEVICE_OBJECT_ATTRIBUTES));

        DeviceObjectAttributes.Header.Type = NDIS_OBJECT_TYPE_DEFAULT; // type implicit from the context
        DeviceObjectAttributes.Header.Revision = NDIS_DEVICE_OBJECT_ATTRIBUTES_REVISION_1;
        DeviceObjectAttributes.Header.Size = sizeof(NDIS_DEVICE_OBJECT_ATTRIBUTES);
        DeviceObjectAttributes.DeviceName = &DeviceName;
        DeviceObjectAttributes.SymbolicName = &DeviceLinkUnicodeString;
        DeviceObjectAttributes.MajorFunctions = &DispatchTable[0];
        DeviceObjectAttributes.ExtensionSize = 0;
        DeviceObjectAttributes.DefaultSDDLString = NULL;
        DeviceObjectAttributes.DeviceClassGuid = 0;

        Status = NdisRegisterDeviceEx(
                    DriverHandle,
                    &DeviceObjectAttributes,
                    &ControlDeviceObject,
                    &NdisDeviceHandle);
        
    }

    MUX_RELEASE_MUTEX(&ControlDeviceMutex);

    DBGPRINT(MUX_INFO, ("<==PtRegisterDevice: %x\n", Status));

    return (Status);
}


NTSTATUS
PtDispatch(
    IN PDEVICE_OBJECT           DeviceObject,
    IN PIRP                     Irp
    )
/*++
Routine Description:

    Process IRPs sent to this device.

Arguments:

    DeviceObject - pointer to a device object
    Irp      - pointer to an I/O Request Packet

Return Value:

    NTSTATUS - STATUS_SUCCESS always - change this when adding
    real code to handle ioctls.

--*/
{
    PIO_STACK_LOCATION  irpStack;
    NTSTATUS            status = STATUS_SUCCESS;
    ULONG               inlen;
    PVOID               buffer;

	DeviceObject;
	
    irpStack = IoGetCurrentIrpStackLocation(Irp);
    DBGPRINT(MUX_LOUD, ("==>PtDispatch %d\n", irpStack->MajorFunction));
      
    switch (irpStack->MajorFunction)
    {
        case IRP_MJ_CREATE:
            break;
        
        case IRP_MJ_CLEANUP:
            break;
        
        case IRP_MJ_CLOSE:
            break;        
        
        case IRP_MJ_DEVICE_CONTROL: 
        {

          buffer = Irp->AssociatedIrp.SystemBuffer;  
          inlen = irpStack->Parameters.DeviceIoControl.InputBufferLength;
          
          switch (irpStack->Parameters.DeviceIoControl.IoControlCode) 
          {
            //
            // Add code here to handle ioctl commands.
            //
          }
          break;  
        }
        default:
            break;
    }
    Irp->IoStatus.Information = 0;
    Irp->IoStatus.Status = status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    DBGPRINT(MUX_LOUD, ("<== Pt Dispatch\n"));

    return status;

} 


NDIS_STATUS
PtDeregisterDevice(
    VOID
    )
/*++

Routine Description:

    Deregister the ioctl interface. This is called whenever a miniport
    instance is halted. When the last miniport instance is halted, we
    request NDIS to delete the device object

Arguments:

    NdisDeviceHandle - Handle returned by NdisMRegisterDevice

Return Value:

    NDIS_STATUS_SUCCESS if everything worked ok

--*/
{
    NDIS_STATUS Status = NDIS_STATUS_SUCCESS;

    DBGPRINT(MUX_LOUD, ("==>PassthruDeregisterDevice\n"));

    MUX_ACQUIRE_MUTEX(&ControlDeviceMutex);

    ASSERT(MiniportCount > 0);

    --MiniportCount;
    
    if (0 == MiniportCount)
    {
        //
        // All VELAN miniport instances have been halted.
        // Deregister the control device.
        //

        if (NdisDeviceHandle != NULL)
        {
            Status = NdisMDeregisterDevice(NdisDeviceHandle);
            NdisDeviceHandle = NULL;
        }
    }

    MUX_RELEASE_MUTEX(&ControlDeviceMutex);

    DBGPRINT(MUX_INFO, ("<== PassthruDeregisterDevice: %x\n", Status));
    return Status;
    
}

#if IEEE_VLAN_SUPPORT
BOOLEAN 
MuxRecognizedVlanId(
    PVELAN pVElan, 
    ULONG VlanId
    )
{
    BOOLEAN bResult;

    if (pVElan->MultipleVlanIds)
    {
        bResult = (pVElan->VlanIds[VlanId / 8] >> (VlanId % 8)) & 0x01;
    }
    else
    {
        bResult = (pVElan->VlanId == VlanId);
    }

    return bResult;
}
#endif

