Option Explicit

Const NUIO_IOCTL_NDISUIO_OPEN_DEVICE        = 0
Const NUIO_IOCTL_NDISUIO_QUERY_OID_VALUE    = 1
Const NUIO_IOCTL_NDISUIO_SET_OID_VALUE      = 2
Const NUIO_IOCTL_NDISUIO_QUERY_BINDING      = 3
Const NUIO_IOCTL_NDISUIO_BIND_WAIT          = 4

Const NUIO_EVALSIZE         = 3
Const NUIO_MAX_PACKET_LOSS  = 5

const NUIO_ACTION_NONE						    = &H00000000&
const NUIO_ACTION_MULTITHREADED				    = &H00000001&
const NUIO_ACTION_INVALID_INPUT_DATA		    = &H00000002&
const NUIO_ACTION_INVALID_INPUT_DATA_LENGTH	    = &H00000004&
const NUIO_ACTION_INVALID_OUTPUT_DATA		    = &H00000008&
const NUIO_ACTION_INVALID_OUTPUT_DATA_LENGTH    = &H00000010&
const NUIO_ACTION_INVALID_IOCTL            	    = &H00000020&
const NUIO_ACTION_ASYNC                         = &H00000040&
const NUIO_ACTION_NO_OVERLAPPED                 = &H00000080&
const NUIO_ACTION_RECV_AND_CANCELIO			    = &H00000100&
const NUIO_ACTION_ALLOC_INPUT_POINTER           = &H00000200&
const NUIO_ACTION_ALLOC_OUTPUT_POINTER		    = &H00000400&

const NUIO_QUERY_STRESS						    = &H00000001&
const NUIO_SET_STRESS							= &H00000002&
const NUIO_QUERYSET_STRESS					    = &H00000003&		

Function FindDevice()
Dim oDeviceList     : set oDeviceList   = nothing
Dim oDevice         : set oDevice       = nothing
Dim oLong           : set oLong         = nothing
Dim oMac            : set oMac          = nothing

Dim sDeviceName     : sDeviceName       = ""
Dim bSuccess        : bSuccess	        = false
Dim nPhysicalMedium : nPhysicalMedium   = -1
Dim nConnectStatus  : nConnectStatus    = -1
    
    FindDevice  = ""
    
    set oLong = oStructRep.Alloc("ULONG")
    if(oLong is nothing) then
        call oLog.Failed("Failed to create Structure", 88888)
        exit function
    end if
    
    set oMac = oStructRep.Alloc("NDIS_802_11_MAC_ADDRESS")
    if(oMac is nothing) then
        call oLog.Failed("Failed to create Structure", 88888)
        exit function
    end if
   
    set oDeviceList = oNdtnuio.Enumerate
    for each oDevice in oDeviceList
    
        sDeviceName = oDevice.Name
        
        'oLog.MaskWrite()
        
        do
        
            '
            ' Open this device
            '
            bSuccess = oNdtnuio.OpenDevice(sDeviceName)
            if(bSuccess = false) then
                exit do
            end if
                   
            '
            'Get the physical medium
            '
            bSuccess = oNdtnuio.GetRequest(OID_GEN_PHYSICAL_MEDIUM, oLong)
            if(bSuccess = false) then
                exit do            
            end if
            
            nPhysicalMedium = oLong.Value
            
            '
            ' Get the connect status
            '
            bSuccess = oNdtnuio.GetRequest(OID_GEN_MEDIA_CONNECT_STATUS, oLong)
            if(bSuccess = false) then
                exit do
            end if
            
            nConnectStatus = oLong.Value
            
            '
            ' Close this device
            ' 
            bSuccess = oNdtnuio.CloseDevice()
            if(bSuccess = false) then
                exit do
            end if
            
            if(nPhysicalMedium = 1 And nConnectStatus = 0) then
                exit do
            end if
        
        loop while(false)
        
        'oLog.UnMaskWrite()
        
        if(nPhysicalMedium = 1 And nConnectStatus = 0) then
            FindDevice = sDeviceName
            exit for
        end if
        
    next
        
End Function
'<!-- CRC = 0x0bac08af --->