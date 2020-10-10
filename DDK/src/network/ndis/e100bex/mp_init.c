/*++

Copyright (c) 1999  Microsoft Corporation

Module Name:
    mp_init.c

Abstract:
    This module contains miniport initialization related routines

Revision History:
    Who         When        What
    --------    --------    ----------------------------------------------
    DChen       11-01-99    created

Notes:

--*/

#include "precomp.h"

#if DBG
#define _FILENUMBER     'TINI'
#endif

typedef struct _MP_REG_ENTRY
{
    NDIS_STRING RegName;                // variable name text
    BOOLEAN     bRequired;              // 1 -> required, 0 -> optional
    UINT        FieldOffset;            // offset to MP_ADAPTER field
    UINT        FieldSize;              // size (in bytes) of the field
    UINT        Default;                // default value to use
    UINT        Min;                    // minimum value allowed
    UINT        Max;                    // maximum value allowed
} MP_REG_ENTRY, *PMP_REG_ENTRY;

MP_REG_ENTRY NICRegTable[] = {
// reg value name                           Offset in MP_ADAPTER            Field size                  Default Value           Min             Max
#if DBG                                                                                                                          
    {NDIS_STRING_CONST("Debug"),            0, MP_OFFSET(Debug),            MP_SIZE(Debug),             MP_WARN,                0,              0xffffffff},
#endif
    {NDIS_STRING_CONST("NumRfd"),           0, MP_OFFSET(NumRfd),           MP_SIZE(NumRfd),            128,                     NIC_MIN_RFDS,   NIC_MAX_RFDS},
    {NDIS_STRING_CONST("NumTcb"),           0, MP_OFFSET(NumTcb),           MP_SIZE(NumTcb),            NIC_DEF_TCBS,           1,              NIC_MAX_TCBS},
    {NDIS_STRING_CONST("PhyAddress"),       0, MP_OFFSET(PhyAddress),       MP_SIZE(PhyAddress),        0xFF,                   0,              0xFF},
    {NDIS_STRING_CONST("Connector"),        0, MP_OFFSET(Connector),        MP_SIZE(Connector),         0,                      0,              0x2},
    {NDIS_STRING_CONST("TxFifo"),           0, MP_OFFSET(AiTxFifo),         MP_SIZE(AiTxFifo),          DEFAULT_TX_FIFO_LIMIT,  0,              15},
    {NDIS_STRING_CONST("RxFifo"),           0, MP_OFFSET(AiRxFifo),         MP_SIZE(AiRxFifo),          DEFAULT_RX_FIFO_LIMIT,  0,              15},
    {NDIS_STRING_CONST("TxDmaCount"),       0, MP_OFFSET(AiTxDmaCount),     MP_SIZE(AiTxDmaCount),      0,                      0,              63},
    {NDIS_STRING_CONST("RxDmaCount"),       0, MP_OFFSET(AiRxDmaCount),     MP_SIZE(AiRxDmaCount),      0,                      0,              63},
    {NDIS_STRING_CONST("UnderrunRetry"),    0, MP_OFFSET(AiUnderrunRetry),  MP_SIZE(AiUnderrunRetry),   DEFAULT_UNDERRUN_RETRY, 0,              3},
    {NDIS_STRING_CONST("Threshold"),        0, MP_OFFSET(AiThreshold),      MP_SIZE(AiThreshold),       200,                    0,              200},
    {NDIS_STRING_CONST("MWIEnable"),        0, MP_OFFSET(MWIEnable),        MP_SIZE(MWIEnable),         1,                      0,              1},
    {NDIS_STRING_CONST("Congest"),          0, MP_OFFSET(Congest),          MP_SIZE(Congest),           0,                      0,              0x1},
    {NDIS_STRING_CONST("SpeedDuplex"),      0, MP_OFFSET(SpeedDuplex),      MP_SIZE(SpeedDuplex),       0,                      0,              4}
};

#define NIC_NUM_REG_PARAMS (sizeof (NICRegTable) / sizeof(MP_REG_ENTRY))

NDIS_STATUS 
MpFindAdapter(
    IN  PMP_ADAPTER             Adapter,
    IN  PNDIS_RESOURCE_LIST     resList
    )
/*++
Routine Description:

    Find the adapter and get all the assigned resources

Arguments:

    Adapter     Pointer to our adapter
    resList     Pointer to our resources

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_ADAPTER_NOT_FOUND (event is logged as well)    

--*/    
{

    
    NDIS_STATUS         Status = NDIS_STATUS_ADAPTER_NOT_FOUND;
    ULONG               ErrorCode = 0;
    ULONG               ErrorValue = 0;

    ULONG               ulResult;
    UCHAR               buffer[NIC_PCI_E100_HDR_LENGTH ];
    PPCI_COMMON_CONFIG  pPciConfig = (PPCI_COMMON_CONFIG) buffer;
    USHORT              usPciCommand;
       
    PCM_PARTIAL_RESOURCE_DESCRIPTOR pResDesc;
    ULONG               index;
    BOOLEAN             bResPort = FALSE, bResInterrupt = FALSE, bResMemory = FALSE;

    DBGPRINT(MP_TRACE, ("---> MpFindAdapter\n"));

    do
    {
        //
        // Make sure the adpater is present
        //

        ulResult = NdisMGetBusData(
                       Adapter->AdapterHandle,
                       PCI_WHICHSPACE_CONFIG,
                       FIELD_OFFSET(PCI_COMMON_CONFIG, VendorID),
                       buffer,
                       NIC_PCI_E100_HDR_LENGTH );
                       
                       


        if (ulResult != NIC_PCI_E100_HDR_LENGTH )
        {
            DBGPRINT(MP_ERROR, 
                ("NdisMGetBusData (PCI_COMMON_CONFIG) ulResult=%d\n", ulResult));

            ErrorCode = NDIS_ERROR_CODE_ADAPTER_NOT_FOUND;
            ErrorValue = ERRLOG_READ_PCI_SLOT_FAILED;
                   
            break;
        }

        //     
        // Right type of adapter?
        //
        if (pPciConfig->VendorID != NIC_PCI_VENDOR_ID || 
            pPciConfig->DeviceID != NIC_PCI_DEVICE_ID)
        {
            DBGPRINT(MP_ERROR, ("VendorID/DeviceID don't match - %x/%x\n", 
                pPciConfig->VendorID, pPciConfig->DeviceID));

            ErrorCode = NDIS_ERROR_CODE_ADAPTER_NOT_FOUND;
            ErrorValue = ERRLOG_VENDOR_DEVICE_NOMATCH;

            break;
        }

        DBGPRINT(MP_INFO, ("Adapter is found - VendorID/DeviceID=%x/%x\n", 
            pPciConfig->VendorID, pPciConfig->DeviceID));

        // save info from config space
        Adapter->RevsionID = pPciConfig->RevisionID;
        Adapter->SubVendorID = pPciConfig->u.type0.SubVendorID;
        Adapter->SubSystemID = pPciConfig->u.type0.SubSystemID;

        MpExtractPMInfoFromPciSpace (Adapter, (PUCHAR)pPciConfig);
        
        // --- HW_START   

        usPciCommand = pPciConfig->Command;
        if ((usPciCommand & PCI_ENABLE_WRITE_AND_INVALIDATE) && (Adapter->MWIEnable))
            Adapter->MWIEnable = TRUE;
        else
            Adapter->MWIEnable = FALSE;

        // Enable bus matering if it isn't enabled by the BIOS
        if (!(usPciCommand & PCI_ENABLE_BUS_MASTER))
        {
            DBGPRINT(MP_WARN, ("Bus master is not enabled by BIOS! usPciCommand=%x\n", 
                usPciCommand));

            usPciCommand |= CMD_BUS_MASTER;
            ulResult = NdisMSetBusData(
                           Adapter->AdapterHandle,
                           PCI_WHICHSPACE_CONFIG,
                           FIELD_OFFSET(PCI_COMMON_CONFIG, Command),
                           &usPciCommand,
                           sizeof(USHORT) );
            
            if (ulResult != sizeof(USHORT))
            {
                DBGPRINT(MP_ERROR, 
                    ("NdisMSetBusData (Command) ulResult=%d\n", ulResult));

                ErrorCode = NDIS_ERROR_CODE_ADAPTER_NOT_FOUND;
                ErrorValue = ERRLOG_WRITE_PCI_SLOT_FAILED;

                break;
            }
            ulResult = NdisMGetBusData(
                           Adapter->AdapterHandle,
                           PCI_WHICHSPACE_CONFIG,
                           FIELD_OFFSET(PCI_COMMON_CONFIG, Command),
                           &usPciCommand,
                           sizeof(USHORT) );
            
            if (ulResult != sizeof(USHORT))
            {
                DBGPRINT(MP_ERROR, 
                    ("NdisMGetBusData (Command) ulResult=%d\n", ulResult));

                ErrorCode = NDIS_ERROR_CODE_ADAPTER_NOT_FOUND;
                ErrorValue = ERRLOG_READ_PCI_SLOT_FAILED;

                break;
            }

            if (!(usPciCommand & PCI_ENABLE_BUS_MASTER))
            {
                DBGPRINT(MP_ERROR, ("Failed to enable bus master! usPciCommand=%x\n", 
                    usPciCommand));

                ErrorCode = NDIS_ERROR_CODE_ADAPTER_DISABLED;
                ErrorValue = ERRLOG_BUS_MASTER_DISABLED;

                break;
            }
        }

        DBGPRINT(MP_INFO, ("Bus master is enabled. usPciCommand=%x\n", usPciCommand));

        // --- HW_END

    
        if (resList == NULL)
        {
            ErrorCode = NDIS_ERROR_CODE_RESOURCE_CONFLICT;
            ErrorValue = ERRLOG_QUERY_ADAPTER_RESOURCES;
            break;
        }

        for (index=0; index < resList->Count; index++)
        {
            pResDesc = &resList->PartialDescriptors[index];

            switch(pResDesc->Type)
            {
                case CmResourceTypePort:
                    Adapter->IoBaseAddress = NdisGetPhysicalAddressLow(pResDesc->u.Port.Start); 
                    Adapter->IoRange = pResDesc->u.Port.Length;
                    bResPort = TRUE;

                    DBGPRINT(MP_INFO, ("IoBaseAddress = 0x%x\n", Adapter->IoBaseAddress));
                    DBGPRINT(MP_INFO, ("IoRange = x%x\n", Adapter->IoRange));
                    break;

                case CmResourceTypeInterrupt:
                    Adapter->InterruptLevel = pResDesc->u.Interrupt.Level;
                    Adapter->InterruptVector = pResDesc->u.Interrupt.Vector;
                    bResInterrupt = TRUE;
                    
                    DBGPRINT(MP_INFO, ("InterruptLevel = x%x\n", Adapter->InterruptLevel));
                    break;

                case CmResourceTypeMemory:
                    // Our CSR memory space should be 0x1000, other memory is for 
                    // flash address, a boot ROM address, etc.
                    if (pResDesc->u.Memory.Length == 0x1000)
                    {
                        Adapter->MemPhysAddress = pResDesc->u.Memory.Start;
                        bResMemory = TRUE;
                        
                        DBGPRINT(MP_INFO, 
                            ("MemPhysAddress(Low) = 0x%0x\n", NdisGetPhysicalAddressLow(Adapter->MemPhysAddress)));
                        DBGPRINT(MP_INFO, 
                            ("MemPhysAddress(High) = 0x%0x\n", NdisGetPhysicalAddressHigh(Adapter->MemPhysAddress)));
                    }
                    break;
            }
        } 
        
        if (!bResPort || !bResInterrupt || !bResMemory)
        {
            Status = NDIS_STATUS_RESOURCE_CONFLICT;
            ErrorCode = NDIS_ERROR_CODE_RESOURCE_CONFLICT;
            
            if (!bResPort)
            {
                ErrorValue = ERRLOG_NO_IO_RESOURCE;
            }
            else if (!bResInterrupt)
            {
                ErrorValue = ERRLOG_NO_INTERRUPT_RESOURCE;
            }
            else 
            {
                ErrorValue = ERRLOG_NO_MEMORY_RESOURCE;
            }
            
            break;
        }
        
        Status = NDIS_STATUS_SUCCESS;

    } while (FALSE);
    
    if (Status != NDIS_STATUS_SUCCESS)
    {
        NdisWriteErrorLogEntry(
            Adapter->AdapterHandle,
            ErrorCode,
            1,
            ErrorValue);
    }

    DBGPRINT_S(Status, ("<--- MpFindAdapter, Status=%x\n", Status));

    return Status;

}

NDIS_STATUS NICReadAdapterInfo(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Read the mac addresss from the adapter

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_INVALID_ADDRESS

--*/    
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    USHORT          usValue; 
    int             i;

    DBGPRINT(MP_TRACE, ("--> NICReadAdapterInfo\n"));

    Adapter->EepromAddressSize = 
        GetEEpromAddressSize(GetEEpromSize(Adapter->PortOffset));
    DBGPRINT(MP_WARN, ("EepromAddressSize = %d\n", Adapter->EepromAddressSize));
        
               
    //
    // Read node address from the EEPROM
    //
    for (i=0; i< ETH_LENGTH_OF_ADDRESS; i += 2)    
    {
        usValue = ReadEEprom(Adapter->PortOffset,
                      (USHORT)(EEPROM_NODE_ADDRESS_BYTE_0 + (i/2)),
                      Adapter->EepromAddressSize);

        *((PUSHORT)(&Adapter->PermanentAddress[i])) = usValue;
    }

    DBGPRINT(MP_INFO, ("Permanent Address = %02x-%02x-%02x-%02x-%02x-%02x\n", 
        Adapter->PermanentAddress[0], Adapter->PermanentAddress[1], 
        Adapter->PermanentAddress[2], Adapter->PermanentAddress[3], 
        Adapter->PermanentAddress[4], Adapter->PermanentAddress[5]));

    if (ETH_IS_MULTICAST(Adapter->PermanentAddress) || 
        ETH_IS_BROADCAST(Adapter->PermanentAddress))
    {
        DBGPRINT(MP_ERROR, ("Permanent address is invalid\n")); 

        NdisWriteErrorLogEntry(
            Adapter->AdapterHandle,
            NDIS_ERROR_CODE_NETWORK_ADDRESS,
            0);
        Status = NDIS_STATUS_INVALID_ADDRESS;         
    }
    else
    {
        if (!Adapter->bOverrideAddress)
        {
            ETH_COPY_NETWORK_ADDRESS(Adapter->CurrentAddress, Adapter->PermanentAddress);
        }

        DBGPRINT(MP_INFO, ("Current Address = %02x-%02x-%02x-%02x-%02x-%02x\n", 
            Adapter->CurrentAddress[0], Adapter->CurrentAddress[1],
            Adapter->CurrentAddress[2], Adapter->CurrentAddress[3],
            Adapter->CurrentAddress[4], Adapter->CurrentAddress[5]));
    }

    DBGPRINT_S(Status, ("<-- NICReadAdapterInfo, Status=%x\n", Status));

    return Status;
}

NDIS_STATUS MpAllocAdapterBlock(
    OUT PMP_ADAPTER     *pAdapter,
    IN  NDIS_HANDLE     MiniportAdapterHandle)
/*++
Routine Description:

    Allocate MP_ADAPTER data block and do some initialization

Arguments:

    Adapter     Pointer to receive pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_FAILURE

--*/    
{
    PMP_ADAPTER     Adapter;
    NDIS_STATUS     Status;

    DBGPRINT(MP_TRACE, ("--> NICAllocAdapter\n"));

    *pAdapter = NULL;

    do
    {
        // Allocate MP_ADAPTER block
        (PVOID)Adapter = MP_ALLOCMEMTAG(MiniportAdapterHandle, sizeof(MP_ADAPTER));
        if (Adapter == NULL)
        {
            Status = NDIS_STATUS_RESOURCES;
            DBGPRINT(MP_ERROR, ("Failed to allocate memory - ADAPTER\n"));
            break;
        }
        
        Status = NDIS_STATUS_SUCCESS;

        // Clean up the memory block
        NdisZeroMemory(Adapter, sizeof(MP_ADAPTER));

        MP_INC_REF(Adapter);

        //
        // Init lists, spinlocks, etc.
        // 
        InitializeQueueHeader(&Adapter->SendWaitQueue);
        InitializeQueueHeader(&Adapter->SendCancelQueue);
        //
        // PendingRequestQueue
        //
        InitializeQueueHeader(&Adapter->PendingRequestQueue);
        
        InitializeListHead(&Adapter->RecvList);
        InitializeListHead(&Adapter->RecvPendList);
        InitializeListHead(&Adapter->PoMgmt.PatternList);

        NdisInitializeEvent(&Adapter->ExitEvent);
        NdisInitializeEvent(&Adapter->AllPacketsReturnedEvent);

        NdisAllocateSpinLock(&Adapter->Lock);
        NdisAllocateSpinLock(&Adapter->SendLock);
        NdisAllocateSpinLock(&Adapter->RcvLock);

    } while (FALSE);

    *pAdapter = Adapter;

    DBGPRINT_S(Status, ("<-- NICAllocAdapter, Status=%x\n", Status));

    return Status;

}

VOID MpFreeAdapter(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Free all the resources and MP_ADAPTER data block

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    None                                                    

--*/    
{
    PMP_TXBUF       pMpTxBuf;
    PMP_RFD         pMpRfd;

    DBGPRINT(MP_TRACE, ("--> NICFreeAdapter\n"));

    // No active and waiting sends
    ASSERT(Adapter->nBusySend == 0);
    ASSERT(Adapter->nWaitSend == 0);
    ASSERT(IsQueueEmpty(&Adapter->SendWaitQueue));
    ASSERT(IsQueueEmpty(&Adapter->SendCancelQueue));

    // No other pending operations
    ASSERT(IsListEmpty(&Adapter->RecvPendList));
    ASSERT(Adapter->bAllocNewRfd == FALSE);
    ASSERT(!MP_TEST_FLAG(Adapter, fMP_ADAPTER_LINK_DETECTION));
    ASSERT(MP_GET_REF(Adapter) == 0);

    //
    // Free hardware resources
    //      
    if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_INTERRUPT_IN_USE))
    {
        NdisMDeregisterInterruptEx(Adapter->NdisInterruptHandle);
        MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_INTERRUPT_IN_USE);
    }

    if (Adapter->CSRAddress)
    {
        NdisMUnmapIoSpace(
            Adapter->AdapterHandle,
            Adapter->CSRAddress,
            NIC_MAP_IOSPACE_LENGTH);
        Adapter->CSRAddress = NULL;
    }

    if (Adapter->PortOffset)
    {
        NdisMDeregisterIoPortRange(
            Adapter->AdapterHandle,
            Adapter->IoBaseAddress,
            Adapter->IoRange,
            Adapter->PortOffset);
        Adapter->PortOffset = NULL;
    }

    //               
    // Free RECV memory/NDIS buffer/NDIS packets/shared memory
    //
    ASSERT(Adapter->nReadyRecv == Adapter->CurrNumRfd);

    while (!IsListEmpty(&Adapter->RecvList))
    {
        pMpRfd = (PMP_RFD)RemoveHeadList(&Adapter->RecvList);
        NICFreeRfd(Adapter, pMpRfd, FALSE);
    }
    //
    // Free the chunk of memory
    // 
    if (Adapter->HwRfds)
    {
        NdisMFreeSharedMemory(
            Adapter->AdapterHandle,
            Adapter->HwRfdSize * Adapter->NumHwRfds,
            FALSE,
            Adapter->HwRfds,
            Adapter->HwRfdsPa);
    }

    //
    // Free receive buffer pool
    // 
    if (Adapter->RecvBufferPool)
    {
        NdisFreeBufferPool(Adapter->RecvBufferPool);
        Adapter->RecvBufferPool = NULL;
    }

    //
    // Free receive packet pool
    // 
    if (Adapter->RecvNetBufferListPool)
    {
        NdisFreeNetBufferListPool(Adapter->RecvNetBufferListPool);
        Adapter->RecvNetBufferListPool = NULL;
    }
    
    if (MP_TEST_FLAG(Adapter, fMP_ADAPTER_RECV_LOOKASIDE))
    {
        NdisDeleteNPagedLookasideList(&Adapter->RecvLookaside);
        MP_CLEAR_FLAG(Adapter, fMP_ADAPTER_RECV_LOOKASIDE);
    }
            
    //               
    // Free SEND memory/NDIS buffer/NDIS packets/shared memory
    //
    while (!IsSListEmpty(&Adapter->SendBufList))
    {
        pMpTxBuf = (PMP_TXBUF)PopEntryList(&Adapter->SendBufList);
        ASSERT(pMpTxBuf);
            
        //
        // Free the NDIS buffer
        // 
        if (pMpTxBuf->NdisBuffer)
        {
            NdisFreeBuffer(pMpTxBuf->NdisBuffer);
            pMpTxBuf->NdisBuffer = NULL;
        }
    }

    if (Adapter->MpTxBufAllocVa != NULL)
    {
        NdisMFreeSharedMemory(
            Adapter->AdapterHandle,
            Adapter->MpTxBufAllocSize,
            TRUE,
            Adapter->MpTxBufAllocVa,
            Adapter->MpTxBufAllocPa);
    
        Adapter->MpTxBufAllocVa = NULL;
    }

    //
    // Free the send buffer pool
    // 
    if (Adapter->SendBufferPool)
    {
        NdisFreeBufferPool(Adapter->SendBufferPool);
        Adapter->SendBufferPool = NULL;
    }

    //
    // Free the shared memory for HW_TCB structures
    // 
    if (Adapter->HwSendMemAllocVa)
    {
        NdisMFreeSharedMemory(
            Adapter->AdapterHandle,
            Adapter->HwSendMemAllocSize,
            FALSE,
            Adapter->HwSendMemAllocVa,
            Adapter->HwSendMemAllocPa);
        Adapter->HwSendMemAllocVa = NULL;
    }

    //
    // Free the shared memory for other command data structures                       
    // 
    if (Adapter->HwMiscMemAllocVa)
    {
        NdisMFreeSharedMemory(
            Adapter->AdapterHandle,
            Adapter->HwMiscMemAllocSize,
            FALSE,
            Adapter->HwMiscMemAllocVa,
            Adapter->HwMiscMemAllocPa);
        Adapter->HwMiscMemAllocVa = NULL;
    }

    //
    // Deregister the DMA handle after freeing all shared memory
    //
    if (Adapter->NdisMiniportDmaHandle != NULL)
    {
        NdisMDeregisterScatterGatherDma(Adapter->NdisMiniportDmaHandle);
    }
    Adapter->NdisMiniportDmaHandle = NULL;


    if (Adapter->pSGListMem)
    {
        MP_FREEMEM(Adapter->pSGListMem);
        Adapter->pSGListMem = NULL;
    }
    //
    // Free the memory for MP_TCB structures
    // 
    if (Adapter->MpTcbMem)
    {
        MP_FREEMEM(Adapter->MpTcbMem);
        Adapter->MpTcbMem = NULL;
    }

    //
    //Free all the wake up patterns on this adapter
    //
    MPRemoveAllWakeUpPatterns(Adapter);
    
    NdisFreeSpinLock(&Adapter->Lock);
    NdisFreeSpinLock(&Adapter->SendLock);
    NdisFreeSpinLock(&Adapter->RcvLock);    

    MP_FREEMEM(Adapter);  

#if DBG
    if (MPInitDone)
    {
        NdisFreeSpinLock(&MPMemoryLock);
    }
#endif

    DBGPRINT(MP_TRACE, ("<-- NICFreeAdapter\n"));
}

NDIS_STATUS
NICReadRegParameters(
    IN  PMP_ADAPTER     Adapter
    )
/*++
Routine Description:

    Read the following from the registry
    1. All the parameters
    2. NetworkAddres

Arguments:

    Adapter                         Pointer to our adapter
    MiniportAdapterHandle           For use by NdisOpenConfiguration
    
Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_FAILURE
    NDIS_STATUS_RESOURCES                                       

--*/    
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    NDIS_HANDLE     ConfigurationHandle;
    PMP_REG_ENTRY   pRegEntry;
    UINT            i;
    UINT            value;
    PUCHAR          pointer;
    PNDIS_CONFIGURATION_PARAMETER ReturnedValue;
    PUCHAR          NetworkAddress;
    UINT            Length;

    DBGPRINT(MP_TRACE, ("--> NICReadRegParameters\n"));


    Status = NdisOpenConfigurationEx(Adapter->AdapterHandle,
                                     &ConfigurationHandle);
    
    if (Status != NDIS_STATUS_SUCCESS)
    {
        DBGPRINT(MP_ERROR, ("NdisOpenConfiguration failed\n"));
        DBGPRINT_S(Status, ("<-- NICReadRegParameters, Status=%x\n", Status));
        return Status;
    }
    // read all the registry values 
    for (i = 0, pRegEntry = NICRegTable; i < NIC_NUM_REG_PARAMS; i++, pRegEntry++)
    {
        //
        // Driver should NOT fail the initialization only because it can not
        // read the registry
        //
        ASSERT(pRegEntry->bRequired == FALSE);                
        pointer = (PUCHAR) Adapter + pRegEntry->FieldOffset;

        DBGPRINT_UNICODE(MP_INFO, &pRegEntry->RegName);

        // Get the configuration value for a specific parameter.  Under NT the
        // parameters are all read in as DWORDs.
        NdisReadConfiguration(
            &Status,
            &ReturnedValue,
            ConfigurationHandle,
            &pRegEntry->RegName,
            NdisParameterInteger);

        // If the parameter was present, then check its value for validity.
        if (Status == NDIS_STATUS_SUCCESS)
        {
            // Check that param value is not too small or too large
            if (ReturnedValue->ParameterData.IntegerData < pRegEntry->Min ||
                ReturnedValue->ParameterData.IntegerData > pRegEntry->Max)
            {
                value = pRegEntry->Default;
            }
            else
            {
                value = ReturnedValue->ParameterData.IntegerData;
            }

            DBGPRINT_RAW(MP_INFO, ("= 0x%x\n", value));
        }
        else if (pRegEntry->bRequired)
        {
            DBGPRINT_RAW(MP_ERROR, (" -- failed\n"));

            ASSERT(FALSE);

            Status = NDIS_STATUS_FAILURE;
            break;
        }
        else
        {
            value = pRegEntry->Default;
            DBGPRINT_RAW(MP_INFO, ("= 0x%x (default)\n", value));
            Status = NDIS_STATUS_SUCCESS;
        }

        //
        // Store the value in the adapter structure.
        //
        switch(pRegEntry->FieldSize)
        {
            case 1:
                *((PUCHAR) pointer) = (UCHAR) value;
                break;

            case 2:
                *((PUSHORT) pointer) = (USHORT) value;
                break;

            case 4:
                *((PULONG) pointer) = (ULONG) value;
                break;

            default:
                DBGPRINT(MP_ERROR, ("Bogus field size %d\n", pRegEntry->FieldSize));
                break;
        }
    }

    // Read NetworkAddress registry value 
    // Use it as the current address if any
    if (Status == NDIS_STATUS_SUCCESS)
    {
        NdisReadNetworkAddress(
            &Status,
            &NetworkAddress,
            &Length,
            ConfigurationHandle);
        // If there is a NetworkAddress override in registry, use it 
        if ((Status == NDIS_STATUS_SUCCESS) && (Length == ETH_LENGTH_OF_ADDRESS))
        {
            if ((ETH_IS_MULTICAST(NetworkAddress) 
                    || ETH_IS_BROADCAST(NetworkAddress))
                    || !ETH_IS_LOCALLY_ADMINISTERED (NetworkAddress))
            {
                DBGPRINT(MP_ERROR, 
                    ("Overriding NetworkAddress is invalid - %02x-%02x-%02x-%02x-%02x-%02x\n", 
                    NetworkAddress[0], NetworkAddress[1], NetworkAddress[2],
                    NetworkAddress[3], NetworkAddress[4], NetworkAddress[5]));
            }
            else
            {
                ETH_COPY_NETWORK_ADDRESS(Adapter->CurrentAddress, NetworkAddress);
                Adapter->bOverrideAddress = TRUE;
            }
        }

        Status = NDIS_STATUS_SUCCESS;
    }

    // Close the registry
    NdisCloseConfiguration(ConfigurationHandle);
    
    // Decode SpeedDuplex
    if (Status == NDIS_STATUS_SUCCESS && Adapter->SpeedDuplex)
    {
        switch(Adapter->SpeedDuplex)
        {
            case 1:
            Adapter->AiTempSpeed = 10; Adapter->AiForceDpx = 1;
            break;
            
            case 2:
            Adapter->AiTempSpeed = 10; Adapter->AiForceDpx = 2;
            break;
            
            case 3:
            Adapter->AiTempSpeed = 100; Adapter->AiForceDpx = 1;
            break;
            
            case 4:
            Adapter->AiTempSpeed = 100; Adapter->AiForceDpx = 2;
            break;
        }
    
    }

    DBGPRINT_S(Status, ("<-- NICReadRegParameters, Status=%x\n", Status));

    return Status;
}

NDIS_STATUS 
NICAllocAdapterMemory(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Allocate all the memory blocks for send, receive and others

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_FAILURE
    NDIS_STATUS_RESOURCES

--*/    
{
    NDIS_STATUS     Status;
    PMP_TXBUF       pMpTxbuf;
    PUCHAR          pMem;
    ULONG           MemPhys;
    LONG            index;
    ULONG           ErrorValue = 0;
    UINT            MaxNumBuffers;
    NDIS_SG_DMA_DESCRIPTION     DmaDescription;
    ULONG           pMemSize;
    PUCHAR          AllocVa;
    NDIS_PHYSICAL_ADDRESS   AllocPa;
    PVOID           MpTxBufMem;
    NET_BUFFER_LIST_POOL_PARAMETERS PoolParameters;
    
    DBGPRINT(MP_TRACE, ("--> NICAllocMemory\n"));

    DBGPRINT(MP_INFO, ("NumTcb=%d\n", Adapter->NumTcb));
    Adapter->NumTbd = Adapter->NumTcb * NIC_MAX_PHYS_BUF_COUNT;

    do
    {

        NdisZeroMemory(&DmaDescription, sizeof(DmaDescription));

        DmaDescription.Header.Type = NDIS_OBJECT_TYPE_SG_DMA_DESCRIPTION;
        DmaDescription.Header.Revision = NDIS_SG_DMA_DESCRIPTION_REVISION_1;
        DmaDescription.Header.Size = sizeof(NDIS_SG_DMA_DESCRIPTION);

        DmaDescription.Flags = 0;       // we don't do 64 bit DMA
        
        //
        // Even if offload is enabled, the packet size for mapping shouldn't change
        //
        DmaDescription.MaximumPhysicalMapping = NIC_MAX_PACKET_SIZE;
        
        DmaDescription.ProcessSGListHandler = MpProcessSGList;
        DmaDescription.SharedMemAllocateCompleteHandler = MPAllocateComplete;

        Status = NdisMRegisterScatterGatherDma(
                    Adapter->AdapterHandle,
                    &DmaDescription,
                    &Adapter->NdisMiniportDmaHandle);
                    
        if (Status == NDIS_STATUS_SUCCESS)
        {
            Adapter->ScatterGatherListSize = DmaDescription.ScatterGatherListSize;
            MP_SET_FLAG(Adapter, fMP_ADAPTER_SCATTER_GATHER);
        }
        else
        {
            DBGPRINT(MP_WARN, ("Failed to init ScatterGather DMA\n"));

            //
            // NDIS 6.0 miniport should NOT use map register
            //
            ErrorValue = ERRLOG_OUT_OF_SG_RESOURCES;
            DBGPRINT(MP_ERROR, ("Failed to allocate map registers\n"));
            
            break;  
        }
        //
        // Send + Misc
        //

        //
        // Allocate MP_TCB's
        // 
        Adapter->MpTcbMemSize = Adapter->NumTcb * (sizeof(MP_TCB) + sizeof(MP_TXBUF));

        pMem = MP_ALLOCMEMTAG(Adapter->AdapterHandle, Adapter->MpTcbMemSize);
        if (pMem == NULL)
        {
            Status = NDIS_STATUS_RESOURCES;
            ErrorValue = ERRLOG_OUT_OF_MEMORY;
            DBGPRINT(MP_ERROR, ("Failed to allocate MP_TCB's\n"));
            break;
        }
        NdisZeroMemory(pMem, Adapter->MpTcbMemSize);
        Adapter->MpTcbMem = pMem;
        MpTxBufMem = pMem + (Adapter->NumTcb * sizeof(MP_TCB));
        

        //
        // Allocate memory for scatter-gather list
        //
        pMemSize = Adapter->NumTcb * Adapter->ScatterGatherListSize;
        pMem = MP_ALLOCMEMTAG(Adapter->AdapterHandle, pMemSize);
        
        if (pMem == NULL)
        {
            Status = NDIS_STATUS_RESOURCES;                
            ErrorValue = ERRLOG_OUT_OF_MEMORY;
            DBGPRINT(MP_ERROR, ("Failed to allocate Satter Gether list buffer\n"));
            break;
        }
        NdisZeroMemory(pMem, pMemSize);
        Adapter->pSGListMem = pMem;

        //
        // Allocate send buffers
        //

        pMpTxbuf = (PMP_TXBUF)MpTxBufMem;         

        Adapter->CacheFillSize = NdisMGetDmaAlignment(Adapter->AdapterHandle);
        DBGPRINT(MP_INFO, ("CacheFillSize=%d\n", Adapter->CacheFillSize));

        Adapter->MpTxBufAllocSize = Adapter->NumTcb * (NIC_MAX_PACKET_SIZE + Adapter->CacheFillSize);
        
        NdisMAllocateSharedMemory(
                        Adapter->AdapterHandle,
                        Adapter->MpTxBufAllocSize,
                        TRUE,                           // CACHED
                        &Adapter->MpTxBufAllocVa,  
                        &Adapter->MpTxBufAllocPa);

        if (Adapter->MpTxBufAllocVa == NULL)
        {
            ErrorValue = ERRLOG_OUT_OF_SHARED_MEMORY;
            DBGPRINT(MP_ERROR, ("Failed to allocate a big buffer\n"));
            Status = NDIS_STATUS_RESOURCES;
            break;
        }
        
        AllocVa = Adapter->MpTxBufAllocVa;
        AllocPa = Adapter->MpTxBufAllocPa;
        
        for (index = 0; index < Adapter->NumTcb; index++)
        {
            pMpTxbuf->AllocSize = NIC_MAX_PACKET_SIZE + Adapter->CacheFillSize;
            pMpTxbuf->BufferSize = NIC_MAX_PACKET_SIZE;
            pMpTxbuf->AllocVa = AllocVa;
            pMpTxbuf->AllocPa = AllocPa;
            //
            // Align the buffer on the cache line boundary
            //
            pMpTxbuf->pBuffer = MP_ALIGNMEM(pMpTxbuf->AllocVa, Adapter->CacheFillSize);
            pMpTxbuf->BufferPa.QuadPart = MP_ALIGNMEM_PA(pMpTxbuf->AllocPa, Adapter->CacheFillSize);

            NdisAllocateBuffer(
                &Status,
                &pMpTxbuf->NdisBuffer,
                NULL,
                pMpTxbuf->pBuffer,
                pMpTxbuf->BufferSize);

            if (Status != NDIS_STATUS_SUCCESS)
            {
                ErrorValue = ERRLOG_OUT_OF_NDIS_BUFFER;
                DBGPRINT(MP_ERROR, ("Failed to allocate NDIS buffer for a big buffer\n"));
                break;
            }

            PushEntryList(&Adapter->SendBufList, &pMpTxbuf->SList);
            

            pMpTxbuf++;
            AllocVa += NIC_MAX_PACKET_SIZE;
            AllocPa.QuadPart += NIC_MAX_PACKET_SIZE; 
        }

        if (Status != NDIS_STATUS_SUCCESS) 
            break;

        // HW_START

        //
        // Allocate shared memory for send
        //
        Adapter->HwSendMemAllocSize = Adapter->NumTcb * (sizeof(TXCB_STRUC) + 
                                          NIC_MAX_PHYS_BUF_COUNT * sizeof(TBD_STRUC));

        NdisMAllocateSharedMemory(
            Adapter->AdapterHandle,
            Adapter->HwSendMemAllocSize,
            FALSE,
            (PVOID) &Adapter->HwSendMemAllocVa,
            &Adapter->HwSendMemAllocPa);

        if (!Adapter->HwSendMemAllocVa)
        {
            ErrorValue = ERRLOG_OUT_OF_SHARED_MEMORY;
            DBGPRINT(MP_ERROR, ("Failed to allocate send memory\n"));
            Status = NDIS_STATUS_RESOURCES;
            break;
        }

        NdisZeroMemory(Adapter->HwSendMemAllocVa, Adapter->HwSendMemAllocSize);

        //
        // Allocate shared memory for other uses
        //
        Adapter->HwMiscMemAllocSize =
            sizeof(SELF_TEST_STRUC) + ALIGN_16 +
            sizeof(DUMP_AREA_STRUC) + ALIGN_16 +
            sizeof(NON_TRANSMIT_CB) + ALIGN_16 +
            sizeof(ERR_COUNT_STRUC) + ALIGN_16;

        //
        // Allocate the shared memory for the command block data structures.
        //
        NdisMAllocateSharedMemory(
            Adapter->AdapterHandle,
            Adapter->HwMiscMemAllocSize,
            FALSE,
            (PVOID *) &Adapter->HwMiscMemAllocVa,
            &Adapter->HwMiscMemAllocPa);
        if (!Adapter->HwMiscMemAllocVa)
        {
            ErrorValue = ERRLOG_OUT_OF_SHARED_MEMORY;
            DBGPRINT(MP_ERROR, ("Failed to allocate misc memory\n"));
            Status = NDIS_STATUS_RESOURCES;
            break;
        }

        NdisZeroMemory(Adapter->HwMiscMemAllocVa, Adapter->HwMiscMemAllocSize);

        pMem = Adapter->HwMiscMemAllocVa; 
        MemPhys = NdisGetPhysicalAddressLow(Adapter->HwMiscMemAllocPa);

        Adapter->SelfTest = (PSELF_TEST_STRUC)MP_ALIGNMEM(pMem, ALIGN_16);
        Adapter->SelfTestPhys = MP_ALIGNMEM_PHYS(MemPhys, ALIGN_16);
        pMem = (PUCHAR)Adapter->SelfTest + sizeof(SELF_TEST_STRUC);
        MemPhys = Adapter->SelfTestPhys + sizeof(SELF_TEST_STRUC);

        Adapter->NonTxCmdBlock = (PNON_TRANSMIT_CB)MP_ALIGNMEM(pMem, ALIGN_16);
        Adapter->NonTxCmdBlockPhys = MP_ALIGNMEM_PHYS(MemPhys, ALIGN_16);
        pMem = (PUCHAR)Adapter->NonTxCmdBlock + sizeof(NON_TRANSMIT_CB);
        MemPhys = Adapter->NonTxCmdBlockPhys + sizeof(NON_TRANSMIT_CB);

        Adapter->DumpSpace = (PDUMP_AREA_STRUC)MP_ALIGNMEM(pMem, ALIGN_16);
        Adapter->DumpSpacePhys = MP_ALIGNMEM_PHYS(MemPhys, ALIGN_16);
        pMem = (PUCHAR)Adapter->DumpSpace + sizeof(DUMP_AREA_STRUC);
        MemPhys = Adapter->DumpSpacePhys + sizeof(DUMP_AREA_STRUC);

        Adapter->StatsCounters = (PERR_COUNT_STRUC)MP_ALIGNMEM(pMem, ALIGN_16);
        Adapter->StatsCounterPhys = MP_ALIGNMEM_PHYS(MemPhys, ALIGN_16);

        // HW_END

        //
        // Recv
        //

        NdisInitializeNPagedLookasideList(
            &Adapter->RecvLookaside,
            NULL,
            NULL,
            0,
            sizeof(MP_RFD),
            NIC_TAG, 
            0);

        MP_SET_FLAG(Adapter, fMP_ADAPTER_RECV_LOOKASIDE);

        //
        // set the max number of RFDs
        // disable the RFD grow/shrink scheme if user specifies a NumRfd value 
        // larger than NIC_MAX_GROW_RFDS
        // 
        Adapter->MaxNumRfd = max(Adapter->NumRfd, NIC_MAX_GROW_RFDS);
        DBGPRINT(MP_INFO, ("NumRfd = %d\n", Adapter->NumRfd));
        DBGPRINT(MP_INFO, ("MaxNumRfd = %d\n", Adapter->MaxNumRfd));

        //
        // The driver should allocate more data than sizeof(RFD_STRUC) to allow the
        // driver to align the data(after ethernet header) at 8 byte boundary
        //
        Adapter->HwRfdSize = sizeof(RFD_STRUC) + MORE_DATA_FOR_ALIGN;    

        //
        // alloc the recv net buffer list pool with net buffer inside the list
        //
        NdisZeroMemory(&PoolParameters, sizeof(NET_BUFFER_LIST_POOL_PARAMETERS));
        PoolParameters.Header.Type = NDIS_OBJECT_TYPE_DEFAULT;
        PoolParameters.Header.Revision = NET_BUFFER_LIST_POOL_PARAMETERS_REVISION_1;
        PoolParameters.Header.Size = sizeof(PoolParameters);
        PoolParameters.ProtocolId = 0;
        PoolParameters.ContextSize = 0;
        PoolParameters.fAllocateNetBuffer = TRUE;
        PoolParameters.PoolTag = NIC_TAG;

        Adapter->RecvNetBufferListPool = NdisAllocateNetBufferListPool(
                    MP_GET_ADAPTER_HANDLE(Adapter),
                    &PoolParameters); 


        if (Adapter->RecvNetBufferListPool == NULL)
        {
            ErrorValue = ERRLOG_OUT_OF_PACKET_POOL;
            break;
        }
        
        
        Status = NDIS_STATUS_SUCCESS;

    } while (FALSE);

    if (Status != NDIS_STATUS_SUCCESS)
    {
        NdisWriteErrorLogEntry(
            Adapter->AdapterHandle,
            NDIS_ERROR_CODE_OUT_OF_RESOURCES,
            1,
            ErrorValue);
    }
    DBGPRINT_S(Status, ("<-- NICAllocMemory, Status=%x\n", Status));

    return Status;

}

VOID NICInitSend(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Initialize send data structures

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    None                                                    

--*/    
{
    PMP_TCB         pMpTcb;
    PHW_TCB         pHwTcb;
    ULONG           HwTcbPhys;
    LONG            TcbCount;
    PMP_TXBUF       pMpTxBuf;

    PTBD_STRUC      pHwTbd;  
    ULONG           HwTbdPhys;     

    DBGPRINT(MP_TRACE, ("--> NICInitSend\n"));

    Adapter->TransmitIdle = TRUE;
    Adapter->ResumeWait = TRUE;

    //
    // Setup the initial pointers to the SW and HW TCB data space
    //
    pMpTcb = (PMP_TCB) Adapter->MpTcbMem;
    pMpTxBuf = (PMP_TXBUF) (pMpTcb + Adapter->NumTcb);
    pHwTcb = (PHW_TCB) Adapter->HwSendMemAllocVa;
    HwTcbPhys = NdisGetPhysicalAddressLow(Adapter->HwSendMemAllocPa);

    // Setup the initial pointers to the TBD data space.
    // TBDs are located immediately following the TCBs
    pHwTbd = (PTBD_STRUC) (Adapter->HwSendMemAllocVa +
                 (sizeof(TXCB_STRUC) * Adapter->NumTcb));
    HwTbdPhys = HwTcbPhys + (sizeof(TXCB_STRUC) * Adapter->NumTcb);

    // Go through and set up each TCB
    for (TcbCount = 0; TcbCount < Adapter->NumTcb; TcbCount++)
    {
        pMpTcb->HwTcb = pHwTcb;                 // save ptr to HW TCB
        pMpTcb->HwTcbPhys = HwTcbPhys;      // save HW TCB physical address

        pMpTcb->HwTbd = pHwTbd;                 // save ptr to TBD array
        pMpTcb->HwTbdPhys = HwTbdPhys;      // save TBD array physical address
        pMpTcb->MpTxBuf = pMpTxBuf;

        if (TcbCount)
            pMpTcb->PrevHwTcb = pHwTcb - 1;
        else
            pMpTcb->PrevHwTcb   = (PHW_TCB)((PUCHAR)Adapter->HwSendMemAllocVa +
                                      ((Adapter->NumTcb - 1) * sizeof(HW_TCB)));

        ASSERT(Adapter->pSGListMem != NULL);
        pMpTcb->ScatterGatherListBuffer = Adapter->pSGListMem + TcbCount * Adapter->ScatterGatherListSize;
        
        pHwTcb->TxCbHeader.CbStatus = 0;        // clear the status 
        pHwTcb->TxCbHeader.CbCommand = CB_EL_BIT | CB_TX_SF_BIT | CB_TRANSMIT;

        //
        // Set the link pointer in HW TCB to the next TCB in the chain.  
        // If this is the last TCB in the chain, then set it to the first TCB.
        //
        if (TcbCount < Adapter->NumTcb - 1)
        {
            pMpTcb->Next = pMpTcb + 1;
            pHwTcb->TxCbHeader.CbLinkPointer = HwTcbPhys + sizeof(HW_TCB);
        }
        else
        {
            pMpTcb->Next = (PMP_TCB) Adapter->MpTcbMem;
            pHwTcb->TxCbHeader.CbLinkPointer = 
                NdisGetPhysicalAddressLow(Adapter->HwSendMemAllocPa);
        }

        //
        // Set the previous TCB, if this is the first TCB in the chain, set it to the last
        // TCB.
        //
        if (TcbCount)
        {
            pMpTcb->Prev = pMpTcb - 1;
        }
        else
        {
            pMpTcb->Prev = (PMP_TCB)((PUCHAR)Adapter->MpTcbMem + ((Adapter->NumTcb - 1) * sizeof(MP_TCB)));
        }
          

        pHwTcb->TxCbThreshold = (UCHAR) Adapter->AiThreshold;
        pHwTcb->TxCbTbdPointer = HwTbdPhys;

        pMpTcb++; 
        pMpTxBuf++;
        pHwTcb++;
        HwTcbPhys += sizeof(TXCB_STRUC);
        pHwTbd = (PTBD_STRUC)((PUCHAR)pHwTbd + sizeof(TBD_STRUC) * NIC_MAX_PHYS_BUF_COUNT);
        HwTbdPhys += sizeof(TBD_STRUC) * NIC_MAX_PHYS_BUF_COUNT;
    }

    // set the TCB head/tail indexes
    // head is the olded one to free, tail is the next one to use
    Adapter->CurrSendHead = (PMP_TCB) Adapter->MpTcbMem;
    Adapter->CurrSendTail = (PMP_TCB) Adapter->MpTcbMem;

    DBGPRINT(MP_TRACE, ("<-- NICInitSend, Status=%x\n"));
}

NDIS_STATUS NICInitRecv(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Initialize receive data structures

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_RESOURCES

--*/    
{
    NDIS_STATUS             Status = NDIS_STATUS_RESOURCES;

    PMP_RFD                 pMpRfd;      
    ULONG                   RfdCount;
    ULONG                   ErrorValue = 0;
    PUCHAR                  HwRfds;
    NDIS_PHYSICAL_ADDRESS   HwRfdsPa;
    
    DBGPRINT(MP_TRACE, ("--> NICInitRecv\n"));

    do
    {
        //
        // Allocate shared memory for all the RFDs
        // If the allocation fails, try a smaller size
        //
        for (RfdCount = Adapter->NumRfd; RfdCount > NIC_MIN_RFDS; RfdCount >>= 1)
        {
            NdisMAllocateSharedMemory(
                Adapter->AdapterHandle,
                Adapter->HwRfdSize * RfdCount,
                FALSE,
                &Adapter->HwRfds,
                &Adapter->HwRfdsPa);
            if (Adapter->HwRfds)
            {
                break;
            }
        }
        Adapter->NumHwRfds = RfdCount;
        
        if (!Adapter->HwRfds)
        {
            ErrorValue = ERRLOG_OUT_OF_SHARED_MEMORY;
            break;
        }
        
        //
        // Setup each RFD
        // 
        HwRfds =  Adapter->HwRfds;
        HwRfdsPa = Adapter->HwRfdsPa;
        for (RfdCount = 0; RfdCount < Adapter->NumHwRfds; RfdCount++)
        {
            pMpRfd = NdisAllocateFromNPagedLookasideList(&Adapter->RecvLookaside);
            if (!pMpRfd)
            {
                ErrorValue = ERRLOG_OUT_OF_LOOKASIDE_MEMORY;
                continue;
            }
            //
            // Allocate the shared memory for this RFD.
            // 

            //
            // Get a 8-byts aligned memory from the original HwRfd
            //
            pMpRfd->HwRfd = (PHW_RFD)DATA_ALIGN(HwRfds);
        
            //
            // Now HwRfd is already 8-bytes aligned, and the size of HwPfd header(not data part) is a multiple of 8,
            // If we shift HwRfd 0xA bytes up, the Ethernet header size is 14 bytes long, then the data will be at
            // 8 byte boundary. 
            // 
            pMpRfd->HwRfd = (PHW_RFD)((PUCHAR)(pMpRfd->HwRfd) + HWRFD_SHIFT_OFFSET);
            //
            // Update physical address accordingly
            // 
            pMpRfd->HwRfdPa.QuadPart = HwRfdsPa.QuadPart + BYTES_SHIFT(pMpRfd->HwRfd, HwRfds);
            
            
            ErrorValue = NICAllocRfd(Adapter, pMpRfd);
            if (ErrorValue)
            {
                NdisFreeToNPagedLookasideList(&Adapter->RecvLookaside, pMpRfd);
                continue;
            }
            //
            // Add this RFD to the RecvList
            // 
            Adapter->CurrNumRfd++;                      
            HwRfds += Adapter->HwRfdSize;
            HwRfdsPa.QuadPart += Adapter->HwRfdSize;
            
            MP_SET_FLAG(pMpRfd, fMP_RFD_ALLOC_FROM_MEM_CHUNK);

            NICReturnRFD(Adapter, pMpRfd);
        }
    }
    while (FALSE);

    if (Adapter->CurrNumRfd > NIC_MIN_RFDS)
    {
        Status = NDIS_STATUS_SUCCESS;
    }

    //
    // Adapter->CurrNumRfd < NIC_MIN_RFDs
    //
    if (Status != NDIS_STATUS_SUCCESS)
    {
        NdisWriteErrorLogEntry(
            Adapter->AdapterHandle,
            NDIS_ERROR_CODE_OUT_OF_RESOURCES,
            1,
            ErrorValue);
    }

    DBGPRINT_S(Status, ("<-- NICInitRecv, Status=%x\n", Status));

    return Status;
}

ULONG NICAllocRfd(
    IN  PMP_ADAPTER     Adapter,
    IN  PMP_RFD         pMpRfd)
/*++
Routine Description:

    Allocate NDIS_PACKET and NDIS_BUFFER associated with a RFD

Arguments:

    Adapter     Pointer to our adapter
    pMpRfd      pointer to a RFD

Return Value:

    ERRLOG_OUT_OF_NDIS_PACKET
    ERRLOG_OUT_OF_NDIS_BUFFER

--*/    
{
    NDIS_STATUS         Status;
    PHW_RFD             pHwRfd;    
    ULONG               HwRfdPhys;  
    ULONG               ErrorValue = 0;

    do
    {
        pHwRfd = pMpRfd->HwRfd;
        pMpRfd->HwRfdPhys = NdisGetPhysicalAddressLow(pMpRfd->HwRfdPa);

        pMpRfd->Flags = 0;
        pMpRfd->NetBufferList = NULL;
        pMpRfd->NdisBuffer = NULL;
        
        //
        // point our buffer for receives at this Rfd
        // 
        NdisAllocateBuffer(
            &Status,
            &pMpRfd->NdisBuffer,
            NULL,
            (PVOID)&pHwRfd->RfdBuffer.RxMacHeader,
            NIC_MAX_PACKET_SIZE);
        
        if (Status != NDIS_STATUS_SUCCESS)
        {
            ASSERT(pMpRfd->NdisBuffer == NULL);
            ErrorValue = ERRLOG_OUT_OF_NDIS_BUFFER;
            break;
        }
        //
        // the NetBufferList may change later(RequestControlSize is not enough)
        //
        pMpRfd->NetBufferList = NdisAllocateNetBufferAndNetBufferList(
                                        Adapter->RecvNetBufferListPool,
                                        0,                      // RequestContolOffsetDelta
                                        0,                      // BackFill Size
                                        pMpRfd->NdisBuffer,     // MdlChain
                                        0,                      // DataOffset
                                        0,                      // DataLength
                                        FALSE);
        
        if (pMpRfd->NetBufferList == NULL)
        {
            ErrorValue = ERRLOG_OUT_OF_NDIS_PACKET;
            break;
        }
        pMpRfd->NetBufferList->SourceHandle = MP_GET_ADAPTER_HANDLE(Adapter);
        //
        // Init each RFD header
        // 
        pHwRfd->RfdRbdPointer = DRIVER_NULL;
        pHwRfd->RfdSize = NIC_MAX_PACKET_SIZE;

        
        //
        // Initialize the NetBufferList
        //
        // Save ptr to MP_RFD in the NBL, used in MPReturnNetBufferLists 
        // 
        MP_GET_NET_BUFFER_LIST_RFD(pMpRfd->NetBufferList) = pMpRfd;


    } while (FALSE);

    if (ErrorValue)
    {
        if (pMpRfd->NdisBuffer)
        {
            NdisFreeBuffer(pMpRfd->NdisBuffer);
        }
        //
        // Do not free the shared memory
        //

    }

    return ErrorValue;

}

VOID NICFreeRfd(
    IN  PMP_ADAPTER     Adapter,
    IN  PMP_RFD         pMpRfd,
    IN  BOOLEAN         DispatchLevel)
/*++
Routine Description:

    Free a RFD and assocaited NDIS_PACKET and NDIS_BUFFER

Arguments:

    Adapter         Pointer to our adapter
    pMpRfd          Pointer to a RFD
    DisptchLevel    Specify if the caller is at DISPATCH level

Return Value:

    None                                                    

--*/    
{
    ASSERT(pMpRfd->NdisBuffer);      
    ASSERT(pMpRfd->NetBufferList);  
    ASSERT(pMpRfd->HwRfd);    

    NdisFreeBuffer(pMpRfd->NdisBuffer);
    NdisFreeNetBufferList(pMpRfd->NetBufferList, DispatchLevel);
    
    pMpRfd->NdisBuffer = NULL;
    pMpRfd->NetBufferList = NULL;

    //
    // Free HwRfd, we need to free the original memory pointed by OriginalHwRfd.
    // 
    if (!MP_TEST_FLAG(pMpRfd, fMP_RFD_ALLOC_FROM_MEM_CHUNK))
    {
        NdisMFreeSharedMemory(
            Adapter->AdapterHandle,
            Adapter->HwRfdSize,
            FALSE,
            pMpRfd->OriginalHwRfd,
            pMpRfd->OriginalHwRfdPa);
    }

    pMpRfd->HwRfd = NULL;
    pMpRfd->OriginalHwRfd = NULL;

    NdisFreeToNPagedLookasideList(&Adapter->RecvLookaside, pMpRfd);
}


NDIS_STATUS NICSelfTest(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Perform a NIC self-test

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_DEVICE_FAILED

--*/    
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    ULONG           SelfTestCommandCode;

    DBGPRINT(MP_TRACE, ("--> NICSelfTest\n"));

    DBGPRINT(MP_INFO, ("SelfTest=%x, SelfTestPhys=%x\n", 
        Adapter->SelfTest, Adapter->SelfTestPhys));

    //
    // Issue a software reset to the adapter
    //
    HwSoftwareReset(Adapter);

    //
    // Execute The PORT Self Test Command On The 82558.
    //
    ASSERT(Adapter->SelfTestPhys != 0);
    SelfTestCommandCode = Adapter->SelfTestPhys;

    //
    // Setup SELF TEST Command Code in D3 - D0
    //
    SelfTestCommandCode |= PORT_SELFTEST;

    //
    // Initialize the self-test signature and results DWORDS
    //
    Adapter->SelfTest->StSignature = 0;
    Adapter->SelfTest->StResults = 0xffffffff;

    //
    // Do the port command
    //
    Adapter->CSRAddress->Port = SelfTestCommandCode;

    MP_STALL_EXECUTION(NIC_DELAY_POST_SELF_TEST_MS);

    //
    // if The First Self Test DWORD Still Zero, We've timed out.  If the second
    // DWORD is not zero then we have an error.
    //
    if ((Adapter->SelfTest->StSignature == 0) || (Adapter->SelfTest->StResults != 0))
    {
        DBGPRINT(MP_ERROR, ("StSignature=%x, StResults=%x\n", 
            Adapter->SelfTest->StSignature, Adapter->SelfTest->StResults));

        NdisWriteErrorLogEntry(
            Adapter->AdapterHandle,
            NDIS_ERROR_CODE_HARDWARE_FAILURE,
            1,
            ERRLOG_SELFTEST_FAILED);

        Status = NDIS_STATUS_DEVICE_FAILED;
    }

    DBGPRINT_S(Status, ("<-- NICSelfTest, Status=%x\n", Status));

    return Status;
}

NDIS_STATUS NICInitializeAdapter(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Initialize the adapter and set up everything

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRORS

--*/    
{
    NDIS_STATUS     Status;

    DBGPRINT(MP_TRACE, ("--> NICInitializeAdapter\n"));

    do
    {

        // set up our link indication variable
        // it doesn't matter what this is right now because it will be
        // set correctly if link fails
        Adapter->MediaState = MediaConnectStateUnknown;
        Adapter->MediaDuplexState = MediaDuplexStateUnknown;
        Adapter->LinkSpeed = NDIS_LINK_SPEED_UNKNOWN;
            
        Adapter->CurrentPowerState = NdisDeviceStateD0;
        Adapter->NextPowerState    = NdisDeviceStateD0;

        // Issue a software reset to the D100
        HwSoftwareReset(Adapter);

        // Load the CU BASE (set to 0, because we use linear mode)
        Adapter->CSRAddress->ScbGeneralPointer = 0;
        Status = D100IssueScbCommand(Adapter, SCB_CUC_LOAD_BASE, FALSE);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        // Wait for the SCB command word to clear before we set the general pointer
        if (!WaitScb(Adapter))
        {
            Status = NDIS_STATUS_HARD_ERRORS;
            break;
        }

        // Load the RU BASE (set to 0, because we use linear mode)
        Adapter->CSRAddress->ScbGeneralPointer = 0;
        Status = D100IssueScbCommand(Adapter, SCB_RUC_LOAD_BASE, FALSE);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        // Configure the adapter
        Status = HwConfigure(Adapter);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }
         
        Status = HwSetupIAAddress(Adapter);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        // Clear the internal counters
        HwClearAllCounters(Adapter);


    } while (FALSE);
    
    if (Status != NDIS_STATUS_SUCCESS)
    {
        NdisWriteErrorLogEntry(
            Adapter->AdapterHandle,
            NDIS_ERROR_CODE_HARDWARE_FAILURE,
            1,
            ERRLOG_INITIALIZE_ADAPTER);
    }

    DBGPRINT_S(Status, ("<-- NICInitializeAdapter, Status=%x\n", Status));

    return Status;
}    


VOID HwSoftwareReset(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Issue a software reset to the hardware    

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    None                                                    

--*/    
{
    DBGPRINT(MP_TRACE, ("--> HwSoftwareReset\n"));

    // Issue a PORT command with a data word of 0
    Adapter->CSRAddress->Port = PORT_SOFTWARE_RESET;

    // wait after the port reset command
    NdisStallExecution(NIC_DELAY_POST_RESET);

    // Mask off our interrupt line -- its unmasked after reset
    NICDisableInterrupt(Adapter);

    DBGPRINT(MP_TRACE, ("<-- HwSoftwareReset\n"));
}


NDIS_STATUS HwConfigure(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Configure the hardware    

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRORS

--*/    
{
    NDIS_STATUS         Status;
    PCB_HEADER_STRUC    NonTxCmdBlockHdr = (PCB_HEADER_STRUC)Adapter->NonTxCmdBlock;
    UINT                i;

    DBGPRINT(MP_TRACE, ("--> HwConfigure\n"));

    //
    // Init the packet filter to nothing.
    // 
    Adapter->OldPacketFilter = Adapter->PacketFilter;
    Adapter->PacketFilter = 0;
    
    //
    // Store the current setting for BROADCAST/PROMISCUOS modes
    Adapter->OldParameterField = CB_557_CFIG_DEFAULT_PARM15;
    
    // Setup the non-transmit command block header for the configure command.
    NonTxCmdBlockHdr->CbStatus = 0;
    NonTxCmdBlockHdr->CbCommand = CB_CONFIGURE;
    NonTxCmdBlockHdr->CbLinkPointer = DRIVER_NULL;

    // Fill in the configure command data.

    // First fill in the static (end user can't change) config bytes
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
    Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[21] = CB_557_CFIG_DEFAULT_PARM21;

    // Now fill in the rest of the configuration bytes (the bytes that contain
    // user configurable parameters).

    // Set the Tx and Rx Fifo limits
    Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[1] =
        (UCHAR) ((Adapter->AiTxFifo << 4) | Adapter->AiRxFifo);

    if (Adapter->MWIEnable)
    {
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[3] |= CB_CFIG_B3_MWI_ENABLE;
    }

    // Set the Tx and Rx DMA maximum byte count fields.
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


    Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[7] =
        (UCHAR) ((CB_557_CFIG_DEFAULT_PARM7 & (~CB_CFIG_URUN_RETRY)) |
        (Adapter->AiUnderrunRetry << 1)
        );

    // Setup for MII or 503 operation.  The CRS+CDT bit should only be set
    // when operating in 503 mode.
    if (Adapter->PhyAddress == 32)
    {
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[8] =
            (CB_557_CFIG_DEFAULT_PARM8 & (~CB_CFIG_503_MII));
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[15] =
            (CB_557_CFIG_DEFAULT_PARM15 | CB_CFIG_CRS_OR_CDT);
    }
    else
    {
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[8] =
            (CB_557_CFIG_DEFAULT_PARM8 | CB_CFIG_503_MII);
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[15] =
            ((CB_557_CFIG_DEFAULT_PARM15 & (~CB_CFIG_CRS_OR_CDT)) | CB_CFIG_BROADCAST_DIS);
    }


    // Setup Full duplex stuff

    // If forced to half duplex
    if (Adapter->AiForceDpx == 1)
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
            (CB_557_CFIG_DEFAULT_PARM19 &
            (~(CB_CFIG_FORCE_FDX| CB_CFIG_FDX_ENABLE)));

    // If forced to full duplex
    else if (Adapter->AiForceDpx == 2)
        Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
            (CB_557_CFIG_DEFAULT_PARM19 | CB_CFIG_FORCE_FDX);

    // If auto-duplex
    else
    {
        // We must force full duplex on if we are using PHY 0, and we are
        // supposed to run in FDX mode.  We do this because the D100 has only
        // one FDX# input pin, and that pin will be connected to PHY 1.
        if ((Adapter->PhyAddress == 0) && (Adapter->usDuplexMode == 2))
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
                (CB_557_CFIG_DEFAULT_PARM19 | CB_CFIG_FORCE_FDX);
        else
            Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[19] =
            CB_557_CFIG_DEFAULT_PARM19;
    }


    // display the config info to the debugger
    DBGPRINT(MP_INFO, ("   Issuing Configure command\n"));
    DBGPRINT(MP_INFO, ("   Config Block at virt addr "PTR_FORMAT", phys address %x\n",
        &NonTxCmdBlockHdr->CbStatus, Adapter->NonTxCmdBlockPhys));

    for (i=0; i < CB_CFIG_BYTE_COUNT; i++)
        DBGPRINT(MP_INFO, ("   Config byte %x = %.2x\n", 
            i, Adapter->NonTxCmdBlock->NonTxCb.Config.ConfigBytes[i]));

    // Wait for the SCB command word to clear before we set the general pointer
    if (!WaitScb(Adapter))
    {
        Status = NDIS_STATUS_HARD_ERRORS;
    }
    else
    {
        ASSERT(Adapter->CSRAddress->ScbCommandLow == 0)
        Adapter->CSRAddress->ScbGeneralPointer = Adapter->NonTxCmdBlockPhys;
    
        // Submit the configure command to the chip, and wait for it to complete.
        Status = D100SubmitCommandBlockAndWait(Adapter);
    }

    DBGPRINT_S(Status, ("<-- HwConfigure, Status=%x\n", Status));

    return Status;
}


NDIS_STATUS HwSetupIAAddress(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    Set up the individual MAC address                             

Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_SUCCESS_HARD_ERRORS

--*/    
{
    NDIS_STATUS         Status;
    UINT                i;
    PCB_HEADER_STRUC    NonTxCmdBlockHdr = (PCB_HEADER_STRUC)Adapter->NonTxCmdBlock;

    DBGPRINT(MP_TRACE, ("--> HwSetupIAAddress\n"));

    // Individual Address Setup
    NonTxCmdBlockHdr->CbStatus = 0;
    NonTxCmdBlockHdr->CbCommand = CB_IA_ADDRESS;
    NonTxCmdBlockHdr->CbLinkPointer = DRIVER_NULL;

    // Copy in the station's individual address
    for (i = 0; i < ETH_LENGTH_OF_ADDRESS; i++)
        Adapter->NonTxCmdBlock->NonTxCb.Setup.IaAddress[i] = Adapter->CurrentAddress[i];

    // Update the command list pointer.  We don't need to do a WaitSCB here
    // because this command is either issued immediately after a reset, or
    // after another command that runs in polled mode.  This guarantees that
    // the low byte of the SCB command word will be clear.  The only commands
    // that don't run in polled mode are transmit and RU-start commands.
    ASSERT(Adapter->CSRAddress->ScbCommandLow == 0)
    Adapter->CSRAddress->ScbGeneralPointer = Adapter->NonTxCmdBlockPhys;

    // Submit the IA configure command to the chip, and wait for it to complete.
    Status = D100SubmitCommandBlockAndWait(Adapter);

    DBGPRINT_S(Status, ("<-- HwSetupIAAddress, Status=%x\n", Status));

    return Status;
}

NDIS_STATUS HwClearAllCounters(
    IN  PMP_ADAPTER     Adapter)
/*++
Routine Description:

    This routine will clear the hardware error statistic counters
    
Arguments:

    Adapter     Pointer to our adapter

Return Value:

    NDIS_STATUS_SUCCESS
    NDIS_STATUS_HARD_ERRORS

--*/    
{
    NDIS_STATUS     Status;
    BOOLEAN         bResult;

    DBGPRINT(MP_TRACE, ("--> HwClearAllCounters\n"));

    do
    {
        // Load the dump counters pointer.  Since this command is generated only
        // after the IA setup has complete, we don't need to wait for the SCB
        // command word to clear
        ASSERT(Adapter->CSRAddress->ScbCommandLow == 0)
        Adapter->CSRAddress->ScbGeneralPointer = Adapter->StatsCounterPhys;

        // Issue the load dump counters address command
        Status = D100IssueScbCommand(Adapter, SCB_CUC_DUMP_ADDR, FALSE);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        // Now dump and reset all of the statistics
        Status = D100IssueScbCommand(Adapter, SCB_CUC_DUMP_RST_STAT, TRUE);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            break;
        }

        // Now wait for the dump/reset to complete, timeout value 2 secs
        MP_STALL_AND_WAIT(Adapter->StatsCounters->CommandComplete == 0xA007, 2000, bResult);
        if (!bResult)
        {
            MP_SET_HARDWARE_ERROR(Adapter);
            Status = NDIS_STATUS_HARD_ERRORS;
            break;
        }

        // init packet counts
        Adapter->GoodTransmits = 0;
        Adapter->GoodReceives = 0;

        // init transmit error counts
        Adapter->TxAbortExcessCollisions = 0;
        Adapter->TxLateCollisions = 0;
        Adapter->TxDmaUnderrun = 0;
        Adapter->TxLostCRS = 0;
        Adapter->TxOKButDeferred = 0;
        Adapter->OneRetry = 0;
        Adapter->MoreThanOneRetry = 0;
        Adapter->TotalRetries = 0;

        // init receive error counts
        Adapter->RcvCrcErrors = 0;
        Adapter->RcvAlignmentErrors = 0;
        Adapter->RcvResourceErrors = 0;
        Adapter->RcvDmaOverrunErrors = 0;
        Adapter->RcvCdtFrames = 0;
        Adapter->RcvRuntErrors = 0;

    } while (FALSE);

    DBGPRINT_S(Status, ("<-- HwClearAllCounters, Status=%x\n", Status));

    return Status;
}





