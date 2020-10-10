Option Explicit

'================================================================================================='
'/**
' This class encapsulates the various operations that can be performed on a WLAN 802.11 NDTCore::Open
' object. 
' @date      7/10/2003
' @author    David Harding
'*/
Class CWlanOpen
   Private m_comOpen
   Private m_ndisMedium
   Private m_ndisPhysicalMedium
   Private m_adapterName
   Private m_networkTypeInUse
   Private m_networkTypesSupported
   Private m_adapterType
   Private m_devCaps
   Private m_isWPASupported
   Private m_isTKIPSupported
   Private m_isAESSupported
   Private m_enableSupplicant
   Private m_supplicant
   
   '================================================================================================='
   Private Sub Class_Initialize
      Set m_comOpen     = Nothing
   End Sub
   
   '================================================================================================='
   Private Sub Class_Terminate
       
      Set m_comOpen = Nothing
      
   End Sub
    
   '================================================================================================='
   Public Property Set vbCOMOpen(byval comOpen)
      Set m_comOpen = comOpen
   End Property
   
   '================================================================================================='
   Public Property Get vbCOMOpen
      Set vbCOMOpen = m_comOpen
   End Property

   '================================================================================================='
   Public Property Let vbNdisMedium(byval ndisMedium)
      m_ndisMedium = ndisMedium
   End Property
   
   '================================================================================================='
   Public Property Get vbNdisMedium
      vbNdisMedium = m_ndisMedium
   End Property
   
   '================================================================================================='
   Public Property Let vbNdisPhysicalMedium(byval ndisMedium)
      m_ndisPhysicalMedium = ndisMedium
   End Property
   
   '================================================================================================='
   Public Property Get vbNdisPhysicalMedium
      vbNdisPhysicalMedium = m_ndisPhysicalMedium
   End Property
   
   '================================================================================================='
   Public Property Let vbAdapterName(byval adapterName)
      m_adapterName = adapterName
   End Property
   
   '================================================================================================='
   Public Property Get vbAdapterName
      vbAdapterName = m_adapterName 
   End Property
   
   '================================================================================================='
   Public Property Let vbAdapterType(byval adapterType)
      m_adapterType = adapterType
   End Property
   
   '================================================================================================='
   Public Property Get vbAdapterType
      vbAdapterType = m_adapterType 
   End Property
      
   '================================================================================================='
   Public Property Get vbDeviceType
      vbDeviceType = m_devCaps.DeviceType      
   End Property
      
   '================================================================================================='
   Public Property Get vbIsWPAAdhocSupported
      vbIsWPAAdhocSupported = m_devCaps.IsWPAAdhocSupported
   End Property 
   
   '================================================================================================='
   Public Property Get vbIsWPASupported
      vbIsWPASupported = m_devCaps.IsWPASupported
   End Property 
     
   '================================================================================================='
   Public Property Get vbIsTKIPSupported
      vbIsTKIPSupported = m_devCaps.IsTKIPSupported
   End Property 
      
   '================================================================================================='
   Public Property Get vbIsAESSupported
      vbIsAESSupported = m_devCaps.IsAESSupported
   End Property 
  
   '================================================================================================='
   Public Property Set vbCapabilities(byval newVal)
      Set m_devCaps = newVal
   End Property
   
   '================================================================================================='
   Public Function vbInitializeSupplicant(byval guid)
      
      vbInitializeSupplicant = False
      
      Set m_supplicant = New CNDT1xSupp
      
      ' Open supplicant for test device
      If(m_supplicant.vbOpenDevice(guid) = False) Then
         Exit Function
      End If 
      
      m_enableSupplicant = True
      
      vbInitializeSupplicant = True
      
   End Function
   
   '================================================================================================='
   Public Property Let vbAddPairwiseKey(newVal)
      m_supplicant.vbAddPairwiseKey = newVal
   End Property
   
   '================================================================================================='
   Public Property Let vbAddGroupKey(newVal)
      m_supplicant.vbAddGroupKey = newVal
   End Property
   
   Public Property Get vbGroupKeyIndex
      vbGroupKeyIndex = m_supplicant.vbGroupKeyIndex
   End Property
   
   '================================================================================================='
   Public Function vbPrintCapabilities()
      
      oLog.Write("")
      oLog.Write("****************************** " & m_adapterName & " Capabilities ******************************")
      oLog.Write("Device Type:         "  & vbDeviceTypeToString(m_devCaps.DeviceType))
      oLog.Write("WPA Supported:       "  & m_devCaps.IsWPASupported)
      oLog.Write("WPA Adhoc Supported: "  & m_devCaps.IsWPAAdhocSupported)
      oLog.Write("TKIP Supported:      "  & m_devCaps.IsTKIPSupported)
      oLog.Write("AES Supported:       "  & m_devCaps.IsAESSupported)
      
   End Function
    
   '================================================================================================='
   Public Function vbNdisClose()
  
      vbNdisClose = m_comOpen.NdisClose()
            
   End Function
   
   '================================================================================================='
   Public Function vbNdisOpen()
  
      vbNdisOpen = m_comOpen.NdisOpen(m_ndisMedium, False)
            
   End Function
   
   '================================================================================================='
   Public Function vbSetPacketFilter(byval filter)
   Dim bytesWritten  : bytesWritten = CLng(0)
   Dim bytesNeeded   : bytesNeeded  = CLng(0)
   Dim ndisStatus    : ndisStatus   = -1
   Dim result        : result       = 0
      
      vbSetPacketFilter = False
      
      ndisStatus = Me.vbNdisRequest(OID_GEN_CURRENT_PACKET_FILTER,     _
                                    filter,                            _
                                    4,                                 _
                                    REQUEST_SET_INFO,                  _
                                    bytesWritten,                      _
                                    bytesNeeded,                       _
                                    False)   
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "vbSetPacketFilter: Failed to set OID_GEN_CURRENT_PACKET_FILTER" & StatusToString(ndisStatus)
         Exit Function
      End If 
      
      vbSetPacketFilter = True
                                              
   End Function   
   
   '================================================================================================='
   Public Function vbStartReceive
      
      vbStartReceive = m_comOpen.StartReceive()
      If(vbStartReceive = False) Then
         oLog.Write "vbStartReceive: StartReceive() failed" 
      End If
      
   End Function
   
   '================================================================================================='
   Public Function vbStopReceive()
      
      vbStopReceive = m_comOpen.StopReceive()
      If(vbStopReceive = False) Then
         oLog.SWrite "vbStopReceive: StopReceive() failed"
      End If
   
   End Function
   
   '================================================================================================='
   Public Function vbSendAndWait(destAddr, packetSize, packetsToSend, burstSize, resendAddr)
   Dim packetsSent   : packetsSent  = 0
    
      vbSendAndWait = 0
      
      If(Me.vbSend(destAddr, packetSize, packetsToSend, burstSize, resendAddr) = False) Then
         Exit Function
      End If
      
      If(Me.vbWaitSend() = False) Then
         Exit Function
      End If
      
      If(Me.vbGetSendResults(packetsSent, SEND_FAILURES_FORBIDDEN) = False) Then
         Exit Function
      End If
            
      vbSendAndWait = packetsSent
                 
   End Function
   
   '================================================================================================='
   Public Function vbGetSendResults(byref packetsSent, byval sendFailureType)
   
      vbGetSendResults = m_comOpen.GetSendResults(packetsSent, sendFailureType)
      If(vbGetSendResults = False) Then
         oLog.Write "vbGetSendResults: Failed to get send results"
      End If
      
   End Function
   
    '================================================================================================='
   Public Function vbGetReceiveResults(byref packetsReceived, byref packetsResent)
   
      vbGetReceiveResults = m_comOpen.GetReceiveResults(packetsReceived, packetsResent)
      If(vbGetReceiveResults = False) Then
         oLog.Write "vbGetReceiveResults: GetReceiveResults() failed"
      End If
   
   End Function
   
   '================================================================================================='
   Public Function vbWaitSend()
           
      vbWaitSend = m_comOpen.WaitSend()
      If(vbWaitSend = False) Then
         oLog.Write "vbWaitSend: WaitSend failed"
         Exit Function
      End If
            
   End Function
   
   '================================================================================================='
   Public Function vbSend(destAddr, packetSize, packetsToSend, burstSize, resendAddr)
           
      vbSend = m_comOpen.Send(destAddr, packetSize, packetsToSend, burstSize, resendAddr)
      If(vbSend = False) Then
         oLog.Write "vbSend: Failed to send packets"
         Exit Function
      End If
            
   End Function
     
   '================================================================================================='
	Public Function vbDirectedSend(byref receiver, byval packetsToSend, byref packetsSent, byref packetsReceived)
	Dim retval           : retval             = False
	Dim packetsResent    : packetsResent      = 0
	DIm ndisStatus       : ndisStatus         = -1
	Dim receiverAddr     : receiverAddr       = Empty
	
	   vbDirectedSend = False
	  
	   If(receiver.vbSetPacketFilter(DIRECTED) = False) Then
	      Exit Function
	   End If
	   
      If(receiver.vbStartReceive() = False) Then
         Exit Function
      End If
      
      If(receiver.vbGetCardAddress(receiverAddr) = False) Then
         Exit Function
      End If
      
      packetsSent = Me.vbSendAndWait(receiverAddr, 250, packetsToSend, 0, Null)
                
      If(receiver.vbStopReceive() = False) Then
         Exit Function
      End If
      
      If(receiver.vbGetReceiveResults(packetsReceived, packetsResent) = False) Then
         Exit Function
      End If
           
      vbDirectedSend = True
	
	End Function
	
	'================================================================================================='
	Public Function vbBroadcastSend(byref receiver, byval packetsToSend, byref packetsSent, byref packetsReceived)
	Dim retval           : retval             = False
	Dim packetsResent    : packetsResent      = 0
	DIm ndisStatus       : ndisStatus         = -1
	Dim receiverAddr     : receiverAddr       = Empty
	
	   vbBroadcastSend = False
	   
	   If(receiver.vbSetPacketFilter(BROADCAST) = False) Then
	      Exit Function
	   End If
	   	   
      If(receiver.vbStartReceive() = False) Then
         Exit Function
      End If
      
      If(receiver.vbGetBroadcastAddress(receiverAddr) = False) Then
         Exit Function
      End If
      
      packetsSent = Me.vbSendAndWait(receiverAddr, 250, packetsToSend, 0, Null)
                
      If(receiver.vbStopReceive() = False) Then
         Exit Function
      End If
      
      If(receiver.vbGetReceiveResults(packetsReceived, packetsResent) = False) Then
         Exit Function
      End If
           
      vbBroadcastSend = True
      
	End Function
	
	'===============================================================================================//
	Function vbStartPerformance(receiver, destAddrress, testMode, packetSize, pktsPerBurst, numPackets, duration, delay, cancelPkts)
      vbStartPerformance = m_comOpen.StartPerformance(receiver.vbCOMOpen,     _
                                                       destAddrress, _
                                                       testMode,     _
                                                       packetSize,   _
                                                       pktsPerBurst, _
                                                       numPackets,   _
                                                       duration,     _
                                                       delay,        _
                                                       cancelPkts)
   End Function
   
      
   '===============================================================================================//
   Public Function vbWaitPerformance ()
      vbWaitPerformance = m_comOpen.WaitPerformance()
   End Function
   
   '===============================================================================================//
   Public Function vbGetPerformanceResults(duration, bytesSent, bytesReceived)
      vbGetPerformanceResults = m_comOpen.GetPerformanceResults(duration, bytesSent, bytesReceived)
   End Function
   
	'============================================================================================='
	Public Function vbStartWaitForEvent(byval eventID)
	 	   
	   vbStartWaitForEvent = m_comOpen.StartWaitForEvent(eventID)
	    
	End Function
	
	'============================================================================================='
	Public Function vbEndWaitForEvent(byval timeout)

	   vbEndWaitForEvent = m_comOpen.EndWaitForEvent(timeout)
	
	End Function
	
	'================================================================================================='
	Public Function vbGetBroadcastAddress(byref addr)
      
      vbGetBroadcastAddress = False
      
      addr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
      
      vbGetBroadcastAddress = True
      
   End Function
   
	'================================================================================================='
	Public Function vbGetCardAddress(byref cardAddr)
   Dim result        : result       = 0
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
   Dim ndisStatus    : ndisStatus   = -1
   Dim oid           : oid          = OID_802_3_CURRENT_ADDRESS
         
         vbGetCardAddress = False
         
         cardAddr = NullAddr()
        
         ndisStatus = Me.vbNdisRequest(oid,                 _
                                       cardAddr,            _
                                       6,                   _
                                       REQUEST_QUERY_INFO,  _
                                       bytesWritten,        _
                                       bytesNeeded,         _
                                       False)   
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "vbGetCardAddress: Failed to query OID_802_3_CURRENT_ADDRESS" & StatusToString(ndisStatus)
         Exit Function
      End If 
      
      vbGetCardAddress = True
      
   End Function
	
   '============================================================================================='
   '/**
   'This function will reset the media events associated with the current open instance. This is used
   'when the script does not need the events, it just wants to reset the counters
   '@return   True if the call is successful, otherwise returns false
   '@code
   '    bRetval = oTestOpen.vbClearEvents()
   '@endcode
   '@sa COpen::vbGetEvents
   '*/  
   Public Function vbClearEvents()
   
      vbClearEvents = m_comOpen.GetEvents()
      If(vbClearEvents = False) Then
         oLog.Write ("vbClearEvents: GetEvents failed for " & m_adapterName)
      End if 
      
   End Function
   
   '===============================================================================================
   Public Function vbGetEvents(ByRef resets, ByRef disconnects, ByRef connects)
      vbGetEvents = m_comOpen.GetEvents(resets, disconnects, connects)
   End Function
   
   '================================================================================================='
   Public Function vbMediaConnectStatus(byref connectStatus)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
   Dim ndisStatus       : ndisStatus         = -1
      
      vbMediaConnectStatus = False
      
      ndisStatus = Me.vbNdisRequest(OID_GEN_MEDIA_CONNECT_STATUS, _
                                    connectStatus,                _
                                    4,                            _
                                    REQUEST_QUERY_INFO,           _
                                    bytesWritten,                 _
                                    bytesNeeded,                  _
                                    False)
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "vbMediaConnectStatus: Failed to query OID_GEN_CURRENT_PACKET_FILTER" & StatusToString(ndisStatus)
         Exit Function
      End If 
      
      vbMediaConnectStatus = True
      
   End Function
   
   '================================================================================================='
   Public Function vbNdisRequest(ByVal oid, ByRef data, ByVal dataLength, ByVal requestType, ByRef bytesWritten, ByRef bytesNeeded, ByVal resize)
   Dim result        : result          = -1
   Dim ndisStatus    : ndisStatus      = -1
   Dim newSize       : newSize         = 0
   DIm bytesProvided : bytesProvided   = 0
   
      vbNdisRequest = ndisStatus
            
      result = m_comOpen.NdisRequest(oid, data, dataLength, requestType, bytesWritten, bytesNeeded, ndisStatus)
      If(result = False) Then
         oLog.Failed "vbNdisRequest: NdisRequest() failed for " & m_adapterName, 88888
         Exit Function
      End If
      
      If(resize) Then
      
         If(ndisStatus = NDIS_STATUS_BUFFER_TOO_SHORT Or ndisStatus = NDIS_STATUS_INVALID_LENGTH) Then
         
            If(IsArray(data)) Then
            
               If(UBound(data) > 0) Then
               
                  ' Its an array, lets try increasing the size of the array and redoing the call
                  ' The previous call may return a size not a multiple of 4. So, adjust it to a multiple of 4
                  If (VarType(data(0)) = vbLong) Then
                  
                     ' if it is a long/integer, the resize is more controlled
                     If(bytesNeeded Mod 4 > 0) Then
                        newSize = bytesNeeded\4 + 1
                     Else
                        newSize = bytesNeeded\4
                     End If

                     bytesProvided = 4 * newSize
                     
                  ElseIf(VarType(data(0)) = vbByte) Then
                     newSize        = bytesNeeded
                     bytesProvided = bytesNeeded
                  Else
                     oLog.Write ("Cannot resize non byte and non long arrays")
                     vbNdisRequest = False
                     Exit Function
                  End If

                  oLog.Write ("Insufficient buffer " & dataLength & " provided to NdisRequest. Adjusting buffer size to " & newSize & " and retrying" )
                  ReDim Preserve data(newSize)
                  result = m_comOpen.NdisRequest(oid, data, dataLength, requestType, bytesWritten, bytesNeeded, ndisStatus)
                  If(result = False) Then
                     oLog.Failed "vbNdisRequest: NdisRequest() failed for " & m_adapterName, 88888
                     Exit Function
                  End If          
                    
               Else 
                  oLog.Write ("Will not resize a non array or zero length data buffer")
               End If
         
            End If  
         
         End If
         
      End If
      
      vbNdisRequest = ndisStatus
      
   End Function    
   
   '================================================================================================='
   Public Function vbFastNdisRequest(byval oid, byref data, byref size)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
   
      vbFastNdisRequest = Me.vbNdisRequest(oid, _
                                           data,               _
                                           size,               _
                                           REQUEST_QUERY_INFO, _
                                           bytesWritten,       _
                                           bytesNeeded,        _
                                           False) 
      If(vbFastNdisRequest <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID(" & oid & ") failed" & vbStatusToString(vbFastNdisRequest)
      End If 
      
   End Function
   
   '================================================================================================='
   Public Sub vbSetReceiveOption(receiveOption)
      m_comOpen.SetReceiveOption(receiveOption)
   End Sub
   
   '================================================================================================='
   Public Function vbNdisReset()
      vbNdisReset = m_comOpen.NdisReset()
   End Function
   
   '================================================================================================='
   Public Function vbNdisRequestEx(byval queryType, byval oid, byref struct, byref bytesWritten, byref bytesNeeded, byval resize)
   Dim ndisStatus : ndisStatus = -1
   Dim result     : result     = Empty
   Dim buffer()
      
      vbNdisRequestEx = ndisStatus
      
      'If(queryType = REQUEST_SET_INFO) Then
      '   oNDTStruct.vbPrintStructure(struct)               
      'End If
      
      If(oNDTStruct.vbStructureToArray(struct, buffer) = False) Then
         Exit Function
      End If
            
      ndisStatus = vbNdisRequest(oid, buffer, UBound(buffer), queryType, bytesWritten, bytesNeeded, False)
                        
      If(oNDTStruct.vbArrayToStructure(buffer, struct) = False) Then
         Exit Function
      End If
                  
      'If(resize = True) Then
      '   
      '   If(ndisStatus = NDIS_STATUS_BUFFER_TOO_SHORT Or ndisStatus = NDIS_STATUS_INVALID_LENGTH Or ndisStatus = NDIS_STATUS_BUFFER_OVERFLOW) Then
      '      If(oNDTStruct.vbAllocateStructure(bytesNeeded, struct) = False) Then
      '         Exit Function
      '      End If
      '     
      '      If(oNDTStruct.vbStructureToArray(struct, buffer) = False) Then
      '         Exit Function
      '      End If
      '   
      '      result = m_comOpen.NdisRequest(oid, buffer, UBound(buffer), queryType, bytesWritten, bytesNeeded, ndisStatus)
      '      If(result = False) Then
      '         oLog.Failed "vbNdisRequestEx: NdisRequest() failed for " & m_adapterName, 88888
      '         Exit Function
      '      End If 
      '     
      '      If(queryType = REQUEST_QUERY_INFO) Then
      '        
      '         If(oNDTStruct.vbArrayToStructure(buffer, struct) = False) Then
      '            Exit Function
      '         End If
      '         
      '      End If
      '                
      '   End If
      '          
      'End If
      
      'If(queryType = REQUEST_QUERY_INFO) Then
      '   oNDTStruct.vbPrintStructure(struct)        
      'End If
      
      vbNdisRequestEx = ndisStatus
            
   End Function    

   '================================================================================================='
   Public Function vbGetWlanNetworkTypeInUse(byref networkTypeInUse)	
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetWlanNetworkTypeInUse = Me.vbNdisRequest(OID_802_11_NETWORK_TYPE_IN_USE,   _
                                                   networkTypeInUse,                 _
                                                   4,                                _
                                                   REQUEST_QUERY_INFO,               _
                                                   bytesWritten,                     _
                                                   bytesNeeded,                      _
                                                   False)   
      If(vbGetWlanNetworkTypeInUse <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_NETWORK_TYPE_IN_USE failed" & vbStatusToString(vbGetWlanNetworkTypeInUse)
      Else
         oLog.Write "NetworkTypeInUse = " & vbNetworkTypeToString(networkTypeInUse)
      End If
       
	End Function
	
	'================================================================================================='
   Public Function vbSetWlanNetworkTypeInUse(byval networkTypeInUse)	
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
            
      vbSetWlanNetworkTypeInUse = Me.vbNdisRequest(OID_802_11_NETWORK_TYPE_IN_USE,     _
                                                   networkTypeInUse,                   _
                                                   4,                                  _
                                                   REQUEST_SET_INFO,                   _
                                                   bytesWritten,                       _
                                                   bytesNeeded,                        _
                                                   False)
      oLog.Write "NetworkTypeInUse = " & vbNetworkTypeToString(networkTypeInUse)
      If(vbSetWlanNetworkTypeInUse <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_NETWORK_TYPE_IN_USE failed" & vbStatusToString(vbSetWlanNetworkTypeInUse)
      End If
            
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanNetworkTypesSuppported(byref object)	
   Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbGetWlanNetworkTypesSuppported = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                  _ 
                                                           OID_802_11_NETWORK_TYPES_SUPPORTED,  _
                                                           object,                              _
                                                           bytesWritten,                        _
                                                           bytesNeeded,                         _
                                                           True)
      If(vbGetWlanNetworkTypesSuppported <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_NETWORK_TYPES_SUPPORTED failed" & vbStatusToString(vbGetWlanNetworkTypesSuppported)
      Else
         oNDTStruct.vbPrintStructure(object)
      End If                                                        
   
	End Function
	
	
	'================================================================================================='
   Public Function vbGetWlanSupportedRates(byref rates)	
         		
	End Function
	
	'================================================================================================='
   Public Function vbSetWlanSupportedRates(byval rates)	

   End Function
				
	'================================================================================================='
   Public Function vbSetWlanDisassociate()
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
   Dim data             : data               = 0
   
      vbSetWlanDisassociate = Me.vbNdisRequest(OID_802_11_DISASSOCIATE,   _
                                               data,                      _
                                               4,                         _
                                               REQUEST_SET_INFO,          _
                                               bytesWritten,              _
                                               bytesNeeded,               _
                                               False) 
	   If(vbSetWlanDisassociate <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_DISASSOCIATE failed" & vbStatusToString(vbSetWlanDisassociate)
      End If
      
	End Function
		
	'================================================================================================='
   Public Function vbSetWlanInfrastructureMode(byval infrastructureMode)	
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbSetWlanInfrastructureMode = Me.vbNdisRequest(OID_802_11_INFRASTRUCTURE_MODE,   _
                                                     infrastructureMode,               _
                                                     4,                                _
                                                     REQUEST_SET_INFO,                 _
                                                     bytesWritten,                     _
                                                     bytesNeeded,                      _
                                                     False) 
      oLog.Write "InfrastructureMode = " & vbInfrastructureModeToString(infrastructureMode)
      If(vbSetWlanInfrastructureMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_INFRASTRUCTURE_MODE failed" & vbStatusToString(vbSetWlanInfrastructureMode)
      End If
          
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanInfrastructureMode(byref infrastructureMode)	
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetWlanInfrastructureMode = Me.vbNdisRequest(OID_802_11_INFRASTRUCTURE_MODE,   _
                                                     infrastructureMode,               _
                                                     4,                                _
                                                     REQUEST_QUERY_INFO,               _
                                                     bytesWritten,                     _
                                                     bytesNeeded,                      _
                                                     False)    
	   If(vbSetWlanInfrastructureMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_INFRASTRUCTURE_MODE failed" & vbStatusToString(vbGetWlanInfrastructureMode)
      Else
         oLog.Write "InfrastructureMode = " & vbInfrastructureModeToString(infrastructureMode)
      End If
      
	End Function
			
	'================================================================================================='
   Public Function vbSetWlanAuthenticationMode(byval authenticationMode)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
      
      vbSetWlanAuthenticationMode = Me.vbNdisRequest(OID_802_11_AUTHENTICATION_MODE,   _
                                                     authenticationMode,               _
                                                     4,                                _
                                                     REQUEST_SET_INFO,                 _
                                                     bytesWritten,                     _
                                                     bytesNeeded,                      _
                                                     False)
      oLog.Write "AuthenticationMode = " & vbAuthenticationModeToString(authenticationMode)
      If(vbSetWlanAuthenticationMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_AUTHENTICATION_MODE failed" & vbStatusToString(vbSetWlanAuthenticationMode)
      End If 
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanAuthenticationMode(byref authenticationMode)
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetWlanAuthenticationMode = Me.vbNdisRequest(OID_802_11_AUTHENTICATION_MODE,   _
                                                     authenticationMode,               _
                                                     4,                                _
                                                     REQUEST_QUERY_INFO,               _
                                                     bytesWritten,                     _
                                                     bytesNeeded,                      _
                                                     False) 
	   If(vbGetWlanAuthenticationMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_AUTHENTICATION_MODE failed" & vbStatusToString(vbGetWlanAuthenticationMode)
      Else
         oLog.Write "AuthenticationMode = " & vbAuthenticationModeToString(authenticationMode)
      End If 
      	   
	End Function
	
   '================================================================================================='
   Public Function vbSetWlanEncryptionStatus(byval encryptionStatus)
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
           
      vbSetWlanEncryptionStatus = Me.vbNdisRequest(OID_802_11_ENCRYPTION_STATUS,   _
                                                   encryptionStatus,               _
                                                   4,                              _
                                                   REQUEST_SET_INFO,               _
                                                   bytesWritten,                   _
                                                   bytesNeeded,                    _
                                                   False)
      oLog.Write "EncryptionStatus = " & vbEncryptionModeToString(encryptionStatus)
      If(vbSetWlanEncryptionStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_ENCRYPTION_STATUS failed" & vbStatusToString(vbSetWlanEncryptionStatus)
      End If 
      
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanEncryptionStatus(byref encryptionStatus)
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetWlanEncryptionStatus = Me.vbNdisRequest(OID_802_11_ENCRYPTION_STATUS,   _
                                                   encryptionStatus,               _
                                                   4,                              _
                                                   REQUEST_QUERY_INFO,             _
                                                   bytesWritten,                   _
                                                   bytesNeeded,                    _
                                                   False) 
      If(vbGetWlanEncryptionStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_ENCRYPTION_STATUS failed" & vbStatusToString(vbGetWlanEncryptionStatus)
      Else
         oLog.Write "EncryptionStatus = " & vbEncryptionModeToString(encryptionStatus)
      End If
          
	End Function
	
	'================================================================================================='
   Public Function vbSetWlanPowerMode(byval powerMode)
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
     
      vbSetWlanPowerMode = Me.vbNdisRequest(OID_802_11_POWER_MODE,  _
                                            powerMode,              _
                                            4,                      _
                                            REQUEST_SET_INFO,       _
                                            bytesWritten,           _
                                            bytesNeeded,            _
                                            False)
      oLog.Write "PowerMode = " & vbPowerModeToString(powerMode)
      If(vbSetWlanPowerMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_POWER_MODE failed" & vbStatusToString(vbSetWlanPowerMode)
      End If 
      
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanPowerMode(byref powerMode)
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
      
      vbGetWlanPowerMode = Me.vbNdisRequest(OID_802_11_POWER_MODE,  _
                                            powerMode,              _
                                            4,                      _
                                            REQUEST_QUERY_INFO,     _
                                            bytesWritten,           _
                                            bytesNeeded,            _
                                            False)                                
      If(vbGetWlanPowerMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_POWER_MODE failed" & vbStatusToString(vbGetWlanPowerMode)
      Else
         oLog.Write "PowerMode = " & vbPowerModeToString(powerMode)
      End If 
      
	End Function
		
	'================================================================================================='
   Public Function vbSetWlanSsid(byval object)
   Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetWlanSsid = Me.vbNdisRequestEx(REQUEST_SET_INFO,  _ 
                                         OID_802_11_SSID,   _
                                         object,            _
                                         bytesWritten,      _
                                         bytesNeeded,       _
                                         False)
      oLog.Write "SSID = " & object.Ssid
      If(vbSetWlanSsid <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_SSID failed" & vbStatusToString(vbSetWlanSsid)
      End If 
      
   End Function
    
   '================================================================================================='
   Public Function vbGetWlanSsid(byref object)
   Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbGetWlanSsid = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,   _ 
                                         OID_802_11_SSID,      _
                                         object,               _
                                         bytesWritten,         _
                                         bytesNeeded,          _
                                         False)
      If(vbGetWlanSsid <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_SSID failed" & vbStatusToString(vbGetWlanSsid)
      Else
         oLog.Write "SSID = " & object.Ssid
      End If 
      
   End Function
          
   '================================================================================================='
   Public Function vbGetWlanBssid(byref bssid)
      
      vbGetWlanBssid = Me.vbNdisRequest(OID_802_11_BSSID,    _
                                        bssid,               _
                                        6,                   _
                                        REQUEST_QUERY_INFO,  _
                                        bytesWritten,        _
                                        bytesNeeded,         _
                                        False)
      If(vbGetWlanBssid <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_BSSID failed" & vbStatusToString(vbGetWlanBssid)
      End If 
      
   End Function
	
   '================================================================================================='
   Private Function vbSetWlanBssid(byval nType, byref oBssid)
   
   End Function
   
   '================================================================================================='
	Public Function vbSetWlanRemoveKey(byval object)
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetWlanRemoveKey = Me.vbNdisRequestEx(REQUEST_SET_INFO,      _ 
                                              OID_802_11_REMOVE_KEY, _
                                              object,                _
                                              bytesWritten,          _
                                              bytesNeeded,           _
                                              False)
      oNDTStruct.vbPrintStructure(object)
      If(vbSetWlanRemoveKey <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_REMOVE_KEY failed" & vbStatusToString(vbSetWlanRemoveKey)
      End If 
      
	End Function
	
   '================================================================================================='
   Public Function vbSetWlanBssidListScan()
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
   Dim data             : data               = CLng(0)
   
      vbSetWlanBssidListScan = Me.vbNdisRequest(OID_802_11_BSSID_LIST_SCAN,   _
                                                data,                      _
                                                4,                         _
                                                REQUEST_SET_INFO,          _
                                                bytesWritten,              _
                                                bytesNeeded,               _
                                                False)
      If(vbSetWlanBssidListScan <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_BSSID_LIST_SCAN failed" & vbStatusToString(vbSetWlanBssidListScan)
      End If 
      
   End Function
  	
	'================================================================================================='
   Public Function vbGetWlanBssidList(byref object) 
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
      
      If(oNDTStruct.vbAllocateStructure(object.SizeOf, object) = False) Then
         Exit Function
      End If
            
      Do
      
         vbGetWlanBssidList = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,    _ 
                                                 OID_802_11_BSSID_LIST, _
                                                 object,                _
                                                 bytesWritten,          _
                                                 bytesNeeded,           _
                                                 False)
         If(vbGetWlanBssidList = NDIS_STATUS_BUFFER_TOO_SHORT Or _
            vbGetWlanBssidList = NDIS_STATUS_INVALID_LENGTH Or _
            vbGetWlanBssidList = NDIS_STATUS_BUFFER_OVERFLOW) Then
            
            ' We use the value 104 because the driver could be using the 
            ' old NDIS_802_11_BSSID_LIST structure
            If(bytesNeeded < 104) Then
               oLog.Failed "vbGetWlanBssidList(): Invalid BytesNeeded returned (Returned: " & bytesNeeded & ", Expected: >= 104)" & vbStatusToString(vbGetWlanBssidList), 88888
               Exit Do
            End If
            
            oLog.Write "vbGetWlanBssidList(): Buffer to short, allocating " & bytesNeeded & " bytes" & vbStatusToString(vbGetWlanBssidList)
            If(oNDTStruct.vbAllocateStructure(bytesNeeded, object) = False) Then
               Exit Do
            End If
               
         ElseIf(vbGetWlanBssidList <> NDIS_STATUS_SUCCESS) Then
            oLog.Write "Query OID_802_11_BSSID_LIST failed" & vbStatusToString(vbGetWlanBssidList)
            Exit Do
         ElseIf(vbGetWlanBssidList = NDIS_STATUS_SUCCESS) Then
            oNDTStruct.vbPrintStructure(object)
            Exit Do
         End If 
         
	   Loop While(True)
	   
	End Function
	      
   '================================================================================================='
   Public Function vbSetWlanAddKey(byval object)
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetWlanAddKey = Me.vbNdisRequestEx(REQUEST_SET_INFO,      _ 
                                           OID_802_11_ADD_KEY,    _
                                           object,                _
                                           bytesWritten,          _
                                           bytesNeeded,           _
                                           False)
      oNDTStruct.vbPrintStructure(object)
      If(vbSetWlanAddKey <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_ADD_KEY failed" & vbStatusToString(vbSetWlanAddKey)
      End If 
      
	End Function
			
	'================================================================================================='
   Public Function vbSetWlanAssociationInformation(byval object)	
   Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetWlanAssociationInformation = Me.vbNdisRequestEx(REQUEST_SET_INFO,                  _ 
                                                           OID_802_11_ASSOCIATION_INFORMATION,_
                                                           object,                            _
                                                           bytesWritten,                      _
                                                           bytesNeeded,                       _
                                                           False)
	   If(vbSetWlanAssociationInformation <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_ASSOCIATION_INFORMATION failed" & vbStatusToString(vbSetWlanAssociationInformation)
      End If 
      
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanAssociationInformation(byref object)	
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
          
      If(oNDTStruct.vbAllocateStructure(object.SizeOf, object) = False) Then
         Exit Function
      End If
            
      Do
      
         vbGetWlanAssociationInformation = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                   _ 
                                                              OID_802_11_ASSOCIATION_INFORMATION,   _
                                                              object,                               _
                                                              bytesWritten,                         _
                                                              bytesNeeded,                          _
                                                               False)
         If(vbGetWlanAssociationInformation = NDIS_STATUS_BUFFER_TOO_SHORT Or _
            vbGetWlanAssociationInformation = NDIS_STATUS_INVALID_LENGTH Or _
            vbGetWlanAssociationInformation = NDIS_STATUS_BUFFER_OVERFLOW) Then
            
            ' We use the value 104 because the driver could be using the 
            ' old NDIS_802_11_BSSID_LIST structure
            If(bytesNeeded < 104) Then
               oLog.Failed "vbGetWlanAssociationInformation(): Invalid BytesNeeded returned (Returned: " & bytesNeeded & ", Expected: >= 104)" & vbStatusToString(vbGetWlanAssociationInformation), 88888
               Exit Do
            End If
            
            oLog.Write "vbGetWlanAssociationInformation(): Buffer to short, allocating " & bytesNeeded & " bytes" & vbStatusToString(vbGetWlanAssociationInformation)
            If(oNDTStruct.vbAllocateStructure(bytesNeeded, object) = False) Then
               Exit Do
            End If
               
         ElseIf(vbGetWlanAssociationInformation <> NDIS_STATUS_SUCCESS) Then
            oLog.Write "Query OID_802_11_ASSOCIATION_INFORMATION failed" & vbStatusToString(vbGetWlanAssociationInformation)
            Exit Do
         ElseIf(vbGetWlanAssociationInformation = NDIS_STATUS_SUCCESS) Then
            oNDTStruct.vbPrintStructure(object)
            Exit Do
         End If 
         
	   Loop While(True)
	         
	End Function
	
	'================================================================================================='
   Public Function vbSetWlanReloadDefaults(byval defaults)	
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
      
      vbSetWlanReloadDefaults = Me.vbNdisRequest(OID_802_11_RELOAD_DEFAULTS, _
                                                 defaults,                   _
                                                 4,                          _
                                                 REQUEST_QUERY_INFO,         _
                                                 bytesWritten,               _
                                                 bytesNeeded,                _
                                                 False) 
      oLog.Write "Defaults = " & vbReloadDefaultToString(defaults)
      If(vbSetWlanReloadDefaults <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_RELOAD_DEFAULTS failed" & vbStatusToString(vbSetWlanReloadDefaults)
      End If 
      
	End Function
	
	'================================================================================================='
   Public Function vbSetWlanTest(byval object)
	 
	End Function
	
	'================================================================================================='
   Public Function vbGetWlanConfiguration(byref object) 
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbGetWlanConfiguration = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,          _ 
                                                  OID_802_11_CONFIGURATION,    _
                                                  object,                      _
                                                  bytesWritten,                _
                                                  bytesNeeded,                 _
                                                  False)
      If(vbGetWlanConfiguration <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Query OID_802_11_CONFIGURATION failed" & vbStatusToString(vbGetWlanConfiguration)
      Else
         oNDTStruct.vbPrintStructure(object)
      End If                                         
	
	End Function
	
	'================================================================================================='
	Public Function vbSetWlanConfiguration(byval object)
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetWlanConfiguration = Me.vbNdisRequestEx(REQUEST_SET_INFO,         _ 
                                                  OID_802_11_CONFIGURATION, _
                                                  object,                   _
                                                  bytesWritten,             _  
                                                  bytesNeeded,              _
                                                  False)
      oNDTStruct.vbPrintStructure(object)
	   If(vbSetWlanConfiguration <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_CONFIGURATION failed" & vbStatusToString(vbSetWlanConfiguration)
      End If 
	
	End Function

   '================================================================================================='
	Public Function vbGetWlanRssi(byref rssi)
	 
	End Function
			
	'================================================================================================='
   Public Function vbSetWlanAddWep(byval object)
	Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetWlanAddWep = Me.vbNdisRequestEx(REQUEST_SET_INFO,      _ 
                                           OID_802_11_ADD_WEP,    _
                                           object,                _
                                           bytesWritten,          _
                                           bytesNeeded,           _
                                           False)
	   oNDTStruct.vbPrintStructure(object)
	   If(vbSetWlanAddWep <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_ADD_WEP failed" & vbStatusToString(vbSetWlanAddWep)
      End If 
      
	End Function
	
	'================================================================================================='
	Public Function vbSetWlanRemoveWep(byval keyIndex)
	Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
      
      vbSetWlanRemoveWep = Me.vbNdisRequest(OID_802_11_REMOVE_WEP,   _
                                            keyIndex,                _
                                            4,                       _
                                            REQUEST_SET_INFO,        _
                                            bytesWritten,            _
                                            bytesNeeded,             _
                                            False) 
      oLog.Write "KeyIndex = " & keyIndex
      If(vbSetWlanRemoveWep <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Set OID_802_11_REMOVE_WEP failed" & vbStatusToString(vbSetWlanRemoveWep)
      End If 
                                                 
	End Function
		
	'================================================================================================='
   Public Function vbAssociate(byval infraMode, byval authMode, byval encryption, byval keyIndex, byval keyMaterial, byval bssid, byval ssid, byval timeout)
   Dim object        : Set object   = Nothing
   Dim result        : result       = False
   Dim ndisStatus    : ndisStatus   = -1
   Dim eventID       : eventID      = 0
   
      vbAssociate = ndisStatus
   	
      oLog.Write "- InfrastructureMode   = "   & vbInfrastructureModeToString(infraMode)
      oLog.Write "- AuthenticationMode   = "   & vbAuthenticationModeToString(authMode)
      oLog.Write "- SSID                 = "   & ssid
      oLog.Write "- KeyIndex             = 0x" & Hex(keyIndex)
      oLog.Write "- KeyMaterial          = "   & keyMaterial
      oLog.Write "- Encryption           = "   & vbEncryptionModeToString(encryption)
      oLog.Write "- Timeout              = "   & timeout & " Seconds"
      
            
      Do 
         
         ndisStatus = vbSetWlanInfrastructureMode(infraMode)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
        
         ndisStatus = vbSetWlanAuthenticationMode(authMode)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
         
         ' If the key material is null, then don't try to enable encryption
         If(IsNull(keyMaterial) = False) Then
         
            ' If bssid is not null then use the AddKey() function
            ' otherwise use the AddWep() function
            If(IsNull(bssid) = False) Then
            
               Set object = oNDTStruct.vbCreateStructure("Ndis80211Key")
               If(object Is Nothing) Then
                  Exit Function
               End If
               
               object.KeyIndex      = keyIndex
               object.KeyMaterial   = keyMaterial
               object.BSSID         = bssid
               
               ndisStatus = Me.vbSetWlanAddKey(object)
      	      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      	         Exit Do
      	      End If
      	   
   	      Else
      	      
   	         If(Not keyMaterial = "") Then
      	      
   	            Set object = oNDTStruct.vbCreateStructure("Ndis80211Wep")
                  If(object Is Nothing) Then
                     Exit Function
                  End If
                  
                  object.KeyIndex      = keyIndex
                  object.KeyMaterial   = keyMaterial
                  
                  ndisStatus = Me.vbSetWlanAddWep(object)
      	         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      	            Exit Do
      	         End If
         	   
      	      End If
      	      
   	      End If
   	        	   
   	   End If
   	   
   	   ' Set the encryption
   	   If(IsNull(encryption) = False) Then
   	   
   	      ndisStatus = vbSetWlanEncryptionStatus(encryption)
            If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
               Exit Do
            End If
            
         End If
                  
         Set object = oNDTStruct.vbCreateStructure("Ndis80211Ssid")
         If(object Is Nothing) Then
            Exit Function
         End If
         
         object.Ssid = ssid
         
         ndisStatus = vbSetWlanSsid(object)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         ' If timeout is Null then don't wait for a connect event
         If(IsNull(timeout) = False) Then
         
            Dim connectStatus : connectStatus   = False
            Dim counter       : counter         = 0
                       
            Do
               
               WScript.Sleep(1000)
               
               counter = counter + 1
               
               oLog.MaskWrite()
               result = Me.vbMediaConnectStatus(connectStatus)
               oLog.UnMaskWrite()
               
               If(result = False) Then
                  oLog.Write "vbAssociate: Failed to get media connect status"
                  ndisStatus = NDT_STATUS_ASSOCIATION_FAILED
                  Exit Do
               End If
               
               If(connectStatus = WLAN_MEDIA_CONNECTED) Then
                  Exit Do
               End If
               
               If(counter >= timeout) Then
                  oLog.Write "vbAssociate: Media connect status not connected after " & timeout & " seconds"
                  ndisStatus = NDT_STATUS_ASSOCIATION_FAILED
                  Exit Do
               End If
            
            Loop While(True)
            
         End If
         
         If(encryption = Ndis802_11AuthModeWPAPSK And m_enableSupplicant = True) Then
            
            If(m_supplicant.vbWaitForAuthenticationComplete(WLAN_HANDSHAKE_TIMEOUT) = False) Then
               vbAssociate = NDIS_STATUS_FAILURE'NDT_STATUS_PSK_AUTHENTICATION_FAILED
               'TODO: Remove this message box
               msgbox "Handshake Failed"
               Exit Do
            End If
            
         End If
              
     Loop While(False)
 			      	    
     vbAssociate = ndisStatus
     If(vbAssociate <> NDIS_STATUS_SUCCESS) Then
      oLog.Write "vbAssociate() failed" & vbStatusToString(vbAssociate)
     End If 
     
   End Function
    
   '================================================================================================='
   Public Function vbCreateIBSS(byval authentication, byval encryption, byval keyIndex, byval keyMaterial, byval bssid, byval ssid)
   Dim object        : Set object   = Nothing
   Dim result        : result       = False
   Dim ndisStatus    : ndisStatus   = -1
   Dim eventID       : eventID      = 0
   
      vbCreateIBSS = ndisStatus
   	
      oLog.Write "- KeyIndex             = 0x" & Hex(keyIndex)
      oLog.Write "- KeyMaterial          = "   & keyMaterial
      oLog.Write "- Authentication       = "   & vbAuthenticationModeToString(authentication)
      oLog.Write "- Encryption           = "   & vbEncryptionModeToString(encryption)
      oLog.Write "- SSID                 = "   & ssid
           
      Do 
         
         ndisStatus = vbSetWlanInfrastructureMode(Ndis802_11IBSS)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
        
         ndisStatus = vbSetWlanAuthenticationMode(authentication)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
         
         ndisStatus = vbSetWlanEncryptionStatus(encryption)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
         
         ' If bssid is not null then use the AddKey() function
         ' otherwise use the AddWep() function
         If(IsNull(bssid) = False) Then
         
            Set object = oNDTStruct.vbCreateStructure("Ndis80211Key")
            If(object Is Nothing) Then
               Exit Function
            End If
            
            object.KeyIndex      = keyIndex
            object.KeyMaterial   = keyMaterial
            object.BSSID         = bssid
            
            ndisStatus = Me.vbSetWlanAddKey(object)
      	   If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      	      Exit Do
      	   End If
   	   
   	   Else
   	      
   	      If(Not keyMaterial = "") Then
   	      
   	         Set object = oNDTStruct.vbCreateStructure("Ndis80211Wep")
               If(object Is Nothing) Then
                  Exit Function
               End If
               
               object.KeyIndex      = keyIndex
               object.KeyMaterial   = keyMaterial
               
               ndisStatus = Me.vbSetWlanAddWep(object)
      	      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      	         Exit Do
      	      End If
      	   
      	   End If
   	      
   	   End If
   	                     
         Set object = oNDTStruct.vbCreateStructure("Ndis80211Ssid")
         If(object Is Nothing) Then
            Exit Function
         End If
         
         object.Ssid = ssid
         
                
 		   ndisStatus = vbSetWlanSsid(object)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
               
     Loop While(False)
 			      	    
     vbCreateIBSS = ndisStatus
     If(vbCreateIBSS <> NDIS_STATUS_SUCCESS) Then
      oLog.Write "vbCreateIBSS() failed" & vbStatusToString(vbCreateIBSS)
     End If 
     
    End Function
    
    '================================================================================================='
   Public Function vbJoinIBSS(byval authentication, byval encryption, byval keyIndex, byval keyMaterial, byval bssid, byval ssid, byval timeout)
   Dim object        : Set object      = Nothing
   Dim result        : result          = False
   Dim ndisStatus    : ndisStatus      = -1
   Dim connectStatus : connectStatus   = -1

      vbJoinIBSS = ndisStatus
   	
      oLog.Write "- KeyIndex             = 0x" & Hex(keyIndex)
      oLog.Write "- KeyMaterial          = "   & keyMaterial
      oLog.Write "- Authentication       = "   & vbAuthenticationModeToString(authentication)
      oLog.Write "- Encryption           = "   & vbEncryptionModeToString(encryption)
      oLog.Write "- SSID                 = "   & ssid
      oLog.Write "- Timeout              = "   & timeout
           
      Do 
         
         ndisStatus = vbSetWlanInfrastructureMode(Ndis802_11IBSS)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
        
         ndisStatus = vbSetWlanAuthenticationMode(authentication)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
         
         ndisStatus = vbSetWlanEncryptionStatus(encryption)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
             Exit Do
         End If
         
         ' If bssid is not null then use the AddKey() function
         ' otherwise use the AddWep() function
         If(IsNull(bssid) = False) Then
         
            Set object = oNDTStruct.vbCreateStructure("Ndis80211Key")
            If(object Is Nothing) Then
               Exit Function
            End If
            
            object.KeyIndex      = keyIndex
            object.KeyMaterial   = keyMaterial
            object.BSSID         = bssid
            
            ndisStatus = Me.vbSetWlanAddKey(object)
      	   If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      	      Exit Do
      	   End If
   	   
   	   Else
   	      
   	      If(Not keyMaterial = "") Then
   	      
   	         Set object = oNDTStruct.vbCreateStructure("Ndis80211Wep")
               If(object Is Nothing) Then
                  Exit Function
               End If
               
               object.KeyIndex      = keyIndex
               object.KeyMaterial   = keyMaterial
               
               ndisStatus = Me.vbSetWlanAddWep(object)
      	      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      	         Exit Do
      	      End If
      	   
      	   End If
   	      
   	   End If
   	          
         Set object = oNDTStruct.vbCreateStructure("Ndis80211Ssid")
         If(object Is Nothing) Then
            Exit Function
         End If
         
         object.Ssid = ssid
         
 		   ndisStatus = vbSetWlanSsid(object)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) then
             Exit Do
         End If
         
         ' If timeout is Null then don't wait for a connect event
         If(IsNull(timeout) = False) Then
        
            Dim counter       : counter         = 0
                       
            Do
               
               WScript.Sleep(1000)
               
               counter = counter + 1
               
               oLog.MaskWrite()
               result = Me.vbMediaConnectStatus(connectStatus)
               oLog.UnMaskWrite()
               
               If(result = False) Then
                  oLog.Write "vbAssociate: Failed to get media connect status"
                  ndisStatus = NDT_STATUS_ASSOCIATION_FAILED
                  Exit Do
               End If
               
               If(connectStatus = WLAN_MEDIA_CONNECTED) Then
                  Exit Do
               End If
               
               If(counter >= timeout) Then
                  oLog.Write "vbAssociate: Media connect status not connected after " & timeout & " seconds"
                  ndisStatus = NDT_STATUS_ASSOCIATION_FAILED
                  Exit Do
               End If
            
            Loop While(True)
            
         End If
               
     Loop While(False)
 			      	    
     vbJoinIBSS = ndisStatus
     If(vbJoinIBSS <> NDIS_STATUS_SUCCESS) Then
      oLog.Write "vbJoinIBSS() failed" & vbStatusToString(vbJoinIBSS)
     End If 
     
   End Function
	
   '================================================================================================='
	Public Function vbWlanReset(byval removeKeys)
	Dim ssid       : Set ssid     = Nothing
   Dim ndisStatus : ndisStatus   = -1
   
      vbWlanReset = False
      
      Set ssid = oNDTStruct.vbCreateStructure("Ndis80211Ssid")
      If(ssid Is Nothing) Then
         Exit Function
      End If
         
      ndisStatus = Me.vbSetWlanDisassociate()
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
      'TODO: Need to enable this after we get a working driver
         'Exit Function
      End If
      
      If(removeKeys = True) Then
      
         If(vbRemoveAllKeys() = False) Then
            Exit Function
         End If
         
      End If
      
      ndisStatus = Me.vbSetWlanInfrastructureMode(Ndis802_11Infrastructure)
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If     
            
      ' Set this bogus SSID here to turn the radio back on after the 
      ' call to disassociate above                
      ssid.Ssid = WLAN_RADIO_ON_SSID
 		ndisStatus = Me.vbSetWlanSsid(ssid)
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If
      
      WScript.Sleep(2000)
      
      If(Me.vbClearEvents() = False) Then
         Exit Function
      End If 
      
      vbWlanReset = True  
				
   End Function
   
   '================================================================================================='
	Public Function vbRemoveAllKeys()
	Dim removeKey  : Set removeKey   = Nothing
	Dim ndisStatus : ndisStatus      = -1
   Dim index      : index           = 0
   
	   vbRemoveAllKeys = False
	        
	   'oLog.MaskWrite()   
	   
      Do
	      
	      ' If the device supports WPA
	      If(m_IsWPASupported = True) Then
	      	
	      	Set removeKey = oNDTStruct.vbCreateStructure("Ndis80211RemoveKey")
            If(removeKey Is Nothing) Then
               Exit Do
            End If
            
            removeKey.BSSID = WLAN_KEYTYPE_DEFAULT
      
            ' The scripts will never use more than 4 group keys
            ' so this should remove all the group keys added by the test.
            For index = 0 To 3
            
               removeKey.KeyIndex   = index
               
               ndisStatus = Me.vbSetWlanRemoveKey(removeKey)
               If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
                  Exit Do         
               End If
               
            Next
            
            removeKey.KeyIndex   = &H40000000&
                        
            ndisStatus = Me.vbSetWlanRemoveKey(removeKey)
            If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
               Exit Do         
            End If
                       
         Else
         
            ' The scripts will never use more than three group keys
            ' so this should remove all the group keys added by the test.
            For index = 0 To 3
            
               ndisStatus = Me.vbSetWlanRemoveWep(CLng(index))
               If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
                  Exit Do         
               End If
            
            Next
            
         End If
         
         vbRemoveAllKeys = True
         
      Loop While(False)
      
      'oLog.UnMaskWrite()
          	     		
	End Function
         
End Class


'<!-- CRC = 0x5507b8fb --->