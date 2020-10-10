'<!-- CRC = 0xb69db55a -->
' Specifies the list of calls drivers are allowed / restricted to make
' The rule for format to be applied to the database file is as follows:
'
' 1) A remark is signified by a single quote as FIRST char of the line
' 2) The name of the database MUST be the name of the corresponding module
' 3) There can be multiple databases with the same name. This can be used to gain
'    granularity in function checking. For example NDIS.SYS has three databases. One
'    database makes sure a mandatory call is being made by all drivers and the
'    the other two check to make sure that Safe Ndis calls are being used by drivers
' 4) There can be no spaces on either side of an = when specifying DB attributes
' 5) There can be no white spaces on either side of the comma when specifying
'    the function name and error message pair for a database
' 6) There can be multiple database files if needed. An extra call to ParseDBFile has
'    to be made in the script with the name of the new database file
' 7) All database files must have a .vbs extension and be placed in scripts\inc folder.
'    This gives them a CRC automatically when propgated

'
' History of editions made
' ========================
'
'  1. KeBugCheck is an acceptable call because it is brought in with the -GS compiler option 04/19/02
'  2. KeBugCheckEx is being removed as -GS compiler options brings it in (BufferOverflowK.lib) 08/22/02
'  3. Removed restriction on registry read operations.
'  4. Adding NdisAllocateMemory as bad functions for WinXP and above 05/12/2003
'  5. Removing KeRemoveEntryDeviceQueue, KeRemoveDeviceQueue, KeRemoveByKeyDeviceQueue. Needed for IRP handling and cancelling 05/12/03
'  6. IoWmiRegistrationControl API is now allowed. Event tracing places it in the driver 12/15/2003


' ALL drivers have to be checked against this database! Use of these calls by any driver is prohibited
[DATABASE NAME=NTOSKRNL.EXE]
   "IoAllocateDriverObjectExtension","Do not use this call."
   "IoAttachDevice","Do not use this call."
   "IoAttachDeviceToDeviceStack","Do not use this call."   
   "IoConnectInterrupt","Use NdisMRegisterInterrupt instead"
   "IoCreateSymbolicLink","Do not use this call."
   "IoDeleteSymbolicLink","Do not use this call."
   "IoCreateDevice","Use NdisMRegisterDevice instead"
   "IoCreateUnprotectedSymbolicLink","Do not use this call."
   "IoDeleteDevice","Do not use this call."
   "IoDetachDevice","Do not use this call."   
   "IoDisconnectInterrupt","Use NdisMDeregisterInterrupt,NdisRemoveInterrupt instead"
   "IoGetAttachedDeviceReference","Do not use this call."   
   "IoGetDmaAdapter","Do not use this call."
   "IoGetDriverObjectExtension","Do not use this call."   
   "IoInvalidateDeviceRelations","Do not use this call."
   "IoInvalidateDeviceState","Do not use this call."
   "IoOpenDeviceRegistryKey","Do not use this call."
   "IoRegisterDeviceInterface","Do not use this call."
   "IoSetDeviceInterfaceState","Do not use this call."
   "IoRegisterShutdownNotification","Use NdisMRegisterAdapterShutdownHandler instead."
   "IoUnregisterShutdownNotification","Use NdisMDeRegisterAdapterShutdownHandler instead."
   "IoReportTargetDeviceChange","Do not use this call."
   "IoWMIAllocateInstanceIds","Do not use this call."
   "IoWMIDeviceObjectToProviderId","Do not use this call."
   "IoWMISuggestInstanceName","Do not use this call."   
   "IoWMIWriteEvent","Use NdisIndicateStatus instead."   
   "DbgPrint","This is a debug version of the driver."
   "DbgPrintEx","This is a debug version of the driver."
   "DbgBreakPoint","This is a debug version of the driver."
   "DbgBreakPointWithStatus","This is a debug version of the driver."
   "KeRemoveQueueDpc","Do not use this call."
   "KeSynchronizeExecution","Use NdisMSynchronizeWithInterrupt instead"
   "MmUnmapIoSpace","Use NdisMUnmapIoSpace instead"
   "MmMapIoSpace","Use NdisMMapIoSpace instead"
   "MmGetSystemRoutineAddress","Do not use this call."
   "PoCallDriver","Do not use this call."
   "PoRegisterDeviceForIdleDetection","Do not use this call."
   "PoRegisterSystemState","Do not use this call."
   "PoRequestPowerIrp","Do not use this call."
   "PoSetPowerState","Do not use this call."
   "PoSetSystemState","Do not use this call."
   "PoStartNextPowerIrp","Do not use this call."
   "PoUnregisterSystemState","Do not use this call."   
[/DATABASE]


' ALL drivers have to be checked against this database
' Use of these API implies a bad design so discourage strongly
[DATABASE NAME=NTOSKRNL.EXE]
   "RtlDeleteRegistryValue","Do not use this call."
   "RtlWriteRegistryValue","Do not use this call."
   "ZwCreateDirectoryObject","Do not use this call."
   "ZwCreateKey","Do not use this call."
   "ZwDeleteKey","Do not use this call."
   "ZwQueryInformationFile","Do not use this call."
   "ZwReadFile","Use NdisMapFile,NdisUnmapFile instead"
   "ZwSetValueKey","Do not use this call."
[/DATABASE]


' The script only supports NDISVERSION 5.1 as a valid value. Please contact "adeels" if there is need for a new
' NDIS Version related functionality
[DATABASE NAME=NTOSKRNL.EXE NDISVERSION=51]
   ' Some of the safe API are macros using this call! So we flag on this call instead if NDIS 5.1 drivers use non-safe API
   "MmMapLockedPages","NDIS drivers version 5.1 or higher must use Safe NDIS API's that can be found in the callsdb.vbs"
[/DATABASE]


' If NDIS Version is not an issue, then check and warn to make
' sure SAFE versions are being for following calls
[DATABASE NAME=NDIS.SYS ERRORLEVEL=WARN]
   "NdisGetFirstBufferFromPacket","NdisGetFirstBufferFromPacketSafe should be used instead of NdisGetFirstBufferFromPacket."
   "NdisQueryBuffer","NdisQueryBufferSafe should be used instead of NdisQueryBuffer."
   "NdisBufferVirtualAddress","NdisBufferVirtualAddressSafe should be used instead of NdisBufferVirtualAddress."
[/DATABASE]

' If driver was written using NDISVersion 5.1, it MUST use the SAFE versions and NdisAllocateMemoryWithTag
[DATABASE NAME=NDIS.SYS NDISVERSION=51]
   "NdisGetFirstBufferFromPacket","NdisGetFirstBufferFromPacketSafe should be used instead of NdisGetFirstBufferFromPacket."
   "NdisQueryBuffer","NdisQueryBufferSafe should be used instead of NdisQueryBuffer."
   "NdisBufferVirtualAddress","NdisBufferVirtualAddressSafe should be used instead of NdisBufferVirtualAddress."
   "NdisAllocateMemory","NDIS 5.1 drivers must use NdisAllocateMemoryWithTag instead!"
[/DATABASE]

'<!-- CRC = 0xd2d91e87 --->