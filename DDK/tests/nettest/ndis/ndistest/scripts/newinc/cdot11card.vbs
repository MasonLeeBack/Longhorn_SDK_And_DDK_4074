Option Explicit

'================================================================================================='
'/**
' This class encapsulates the various operations that can be performed on a Native 802.11 NDTCore::Card
' object.
' @date      7/10/2003
' @author    David Harding
'*/
Class CDot11Card
   Private m_comAdapter    
   Private m_adapterName 
      
   Private m_ndisMedium
   Private m_ndisPhysicalMedium
   
   Private m_supportedPHYTypes
   Private m_currentPHYType
   Private m_nicPowerState
   Private m_supportedOperationalModes
   Private m_currentOperationalMode
   
   '================================================================================================='
   Private Sub Class_Initialize()
      Set m_comAdapter = Nothing   
   End Sub
   
   '================================================================================================='
   Private Sub Class_Terminate()
      Set m_comAdapter = Nothing
   End Sub

   '================================================================================================='
   Public Property Get vbCOMAdapter
      Set vbCOMAdapter = m_comAdapter
   End Property
   
   '================================================================================================='
   '/**
   ' This property will return the literal string name of the device this card class is using
   ' For example Test Adapater or Support Adapter
   ' @returns
   ' String name of the device this card class is using
   ' */
   Public Property Get vbAdapterName
      vbAdapterName = m_adapterName
   End Property  
   
   '================================================================================================='
   '/**
   ' This property will return the devices NdisMedium
   ' @returns
   ' The underling devices NdisMedium
   ' */
   Public Property Get vbNdisMedium
      vbNdisMedium = m_ndisMedium
   End Property
   
   '================================================================================================='
   '/**
   ' This property will return the devices NdisPhysicalMedium
   ' @returns
   ' The underling devices NdisPhysicalMedium
   ' */
   Public Property Get vbNdisPhysicalMedium
      vbNdisPhysicalMedium = m_ndisPhysicalMedium
   End Property
   
   '================================================================================================='
   Public Property Get vbSupportedPHYTypes
	   vbSupportedPHYTypes = m_supportedPHYTypes
   End Property
   
   '================================================================================================='
   Public Property Get vbCurrentPHYType
	   vbCurrentPHYType = m_currentPhyType
   End Property
   
   '================================================================================================='
   Public Property Get vbSupportedOperationalModes
	   vbOperationalModes = m_supportedOperationalModes
   End Property
   
   '================================================================================================='
   Public Property Get vbCurrentOperationalMode
	   vbCurrentOperationalMode = m_currentOperationalMode
   End Property 
   
   '================================================================================================='
   '/**
   ' This function takes an NDInfo adapter object and returns a CLanOpen object containing
   ' a "NdisOpened" instance
   ' @params
   ' !object   A NDInfo::Adapter object (element from ndinfo::adapterlist)
   ' @return    
   ' A CLanOpen object or Nothing depending on success
   ' @example
   ' Set oTestCard = New CLanCard6
   ' Set oTestOpen = oTestCard.vbSetupBasicTest(oNDInfo.AdapterList(lTestAdapterIndex))
   ' If (oTestOpen is Nothing) Then
   '   Exit Function
   ' End If
   '*/
   Public Function vbSetupBasicTest(byval adapterInfo)
  
      Set vbSetupBasicTest = Nothing
      
      ' Create the adapter object
      If(Me.vbCreateAdapter(adapterInfo) = False) Then
         Exit Function
      End If
      
      ' Get the adapter capabilities
      If(Me.vbGetDeviceCapabilities(adapterInfo) = False) Then
         Exit Function
      End If
      
      ' Verify the adapter supports the required capablities
	   If(Me.vbVerifyDeviceCapabilities() = False) Then
         Exit Function
	   End If
      
      Set vbSetupBasicTest = Me.vbOpenAdapter
      
   End Function
      
   '================================================================================================='
   Public Function vbCreateAdapter(byval adapterInfo)
      
      vbCreateAdapter = False
      
      Select Case adapterInfo.AdapterType
      Case 1
         m_adapterName = "Test adapter"
      Case 2
         m_adapterName = "Support adapter"
      Case 3
         m_adapterName = "Message adapter"
      Case 4
         m_adapterName = "Virtual Wan adapter"
      Case Else
         m_adapterName = "Unknown adapter"
      End Select
            
      m_ndisMedium         = CLng(adapterInfo.NdisMedium)
      m_ndisPhysicalMedium = CLng(adapterInfo.NdisPhysicalMedium)
      
      Set m_comAdapter = oNDTCore6.CreateAdapter(adapterInfo)
      If(m_comAdapter Is Nothing) Then
         oLog.Write "vbCreateAdapter: Failed to create " & m_adapterName & " object"
         Exit Function
      End If
      
      vbCreateAdapter = True
      
   End Function
    
   '================================================================================================='
   Public Function vbGetDeviceCapabilities(byval adapter)
   Dim object        : object       = Null
   Dim bytesWritten  : bytesWritten = CLng(0)
   Dim errorStatus   : errorStatus  = CLng(0)
   Dim controlCode   : controlCode  = CLng(0)
      
      ' Query operation mode capability                  
      Set object = oNDTStruct.vbCreateStructure("Dot11OperationModeCapability")
      If(object Is Nothing) Then
         Exit Function
      End If
          
      If(Me.vbNdisIOControlEx(QUERY_GLOBAL_STATS, OID_DOT11_OPERATION_MODE_CAPABILITY, object) = False) Then
         oLog.Write "vbGetDeviceCapabilities: Failed to query OID_DOT11_OPERATION_MODE_CAPABILITY"
         Exit Function
      End If
      
      m_supportedOperationalModes = object.OpModeCapability
      
      ' Qusery supported phy types   
      Set object = oNDTStruct.vbCreateStructureAndAllocate("Dot11SupportedPHYTypes", 8, True)
      If(object Is Nothing) Then
         Exit Function
      End If
                  
      If(Me.vbNdisIOControlEx(QUERY_GLOBAL_STATS, OID_DOT11_SUPPORTED_PHY_TYPES, object) = False) Then
         oLog.Write "vbGetDeviceCapabilities: Failed to query OID_DOT11_SUPPORTED_PHY_TYPES"
         Exit Function
      End If
      
      m_supportedPHYTypes  = object.dot11PHYType
      
      ' Query supported data rates
      Set object = oNDTStruct.vbCreateStructure("Dot11SupportedDataRatesValue")
      If(object Is Nothing) Then
         Exit Function
      End If
               
      If(Me.vbNdisIOControlEx(QUERY_GLOBAL_STATS, OID_DOT11_SUPPORTED_DATA_RATES_VALUE, object) = False) Then
         oLog.Write "vbGetDeviceCapabilities: Failed to query OID_DOT11_SUPPORTED_DATA_RATES_VALUE"
         Exit Function
      End If
                  
      ' Query the minports current PHY type 
      If(Me.vbNdisIOControl(OID_DOT11_CURRENT_PHY_TYPE, 1, m_currentPHYType, 4, bytesWritten, errorStatus, controlCode) <> 0) Then
          oLog.Write "vbGetDeviceCapabilities: Failed to query OID_DOT11_CURRENT_PHY_TYPE"     
          Exit Function
      End If
            
      ' Query the minports NIC power state (Radio)
      Dim dot11NicPowerState : dot11NicPowerState = CLng(0)
      If(Me.vbNdisIOControl(OID_DOT11_NIC_POWER_STATE, 1, m_nicPowerState, 4, bytesWritten, errorStatus, controlCode) <> 0) Then
          oLog.Write "vbGetDeviceCapabilities: Failed to query OID_DOT11_CURRENT_PHY_TYPE"     
          Exit Function
      End If
         	
	   vbGetDeviceCapabilities = True
   	 
   End Function
               
   '================================================================================================='
   '/**
   ' This function works on the adapter object held within the hierarchy, 
   ' creating an open object and performing an ndisopen on that object.
   ' Internally, it relies on vbCreateOpen and vbNdisOpen to do the work
   ' for it
   ' @return The CLanOpen object that has a "NdisOpened" instance
   ' @example
   ' Set oTestOpen = oTestCard.vbOpenAdapter
   ' If (oTestOpen is Nothing) Then
   '   Exit Function
   ' End If
   '*/
   Public Function vbOpenAdapter
   Dim adapterOpen : Set adapterOpen = Nothing
      
      Set vbOpenAdapter = Nothing
      
      Set adapterOpen = Me.vbCreateOpen     
      If(adapterOpen Is Nothing) Then
         Exit Function
      End If
      
      If(adapterOpen.vbNdisOpen <> 0) Then
         Exit Function
      End If
                  
      Set vbOpenAdapter = adapterOpen
      
   End Function
   
   '================================================================================================='
   '/**
   ' This API is used to Create an Open on the Adapter Object. This API will also setup the CLanOpen
   ' object that would be used for all the open operations. 
   ' @return Instance of CLanOpen object created if successful, else Nothing
   ' @example
   ' Set oSuppOpen = oSuppCard.vbCreateOpen ()
   ' If (oSuppOpen Is Nothing) Then
   '    Exit Function
   ' End If
   '*/
   Public Function vbCreateOpen()
   Dim adapterOpen   : Set adapterOpen = Nothing
   Dim dot11Open     : Set dot11Open   = Nothing
      
      Set vbCreateOpen = Nothing
      
      Set adapterOpen = m_comAdapter.CreateOpen(m_ndisMedium)
      If(adapterOpen is Nothing) Then
         oLog.Write "vbCreateOpen: Failed to create open on " & m_adapterName 
         Exit Function
      End If
      
      Set dot11Open                    = New CDot11Open
      Set dot11Open.vbCOMOpen          = adapterOpen
      dot11Open.vbNdisMedium           = m_ndisMedium
      dot11Open.vbNdisPhysicalMedium   = m_ndisPhysicalMedium
      dot11Open.vbAdapterName          = m_adapterName
      dot11Open.vbNICPowerState        = m_nicPowerState
         
      Set vbCreateOpen = dot11Open
      
   End Function
   
   '================================================================================================='
   Public Function vbVerifyDeviceCapabilities()
      
      vbVerifyDeviceCapabilities = False
      
      If(m_supportedOperationalModes <> (DOT11_OPERATION_MODE_STATION Or DOT11_OPERATION_MODE_AP)) Then
         oLog.Write "vbVerifyDeviceCapabilities: Device does not support required operational modes DOT11_OPERATION_MODE_STATION and DOT11_OPERATION_MODE_AP"
         Exit Function
      End If
         
      vbVerifyDeviceCapabilities = True
     
   End Function
     
   '================================================================================================='
   Public Function vbNdisIOControl(byval oidList, byval numOids, byref buffer, byval length, byref bytesWritten, byref errorStatus, byval ioControlCode)
   Dim result        : result          = False
   Dim requestStatus : requestStatus   = 0

      requestStatus = m_comAdapter.NdisIoControl(ioControlCode, oidList, numOids, buffer, length, bytesWritten, errorStatus)
      If(requestStatus <> 0) Then
          oLog.SafeFailed "vbNdisIOControl: First attempt at NdisIoControl failed", 88888
          Exit Function
      End If

      Do While(errorStatus = ERROR_INSUFFICIENT_BUFFER Or errorStatus = ERROR_MORE_DATA)
         
         If(IsArray(buffer)) Then
            ' Its an array, lets try increasing the size of the array and redoing the call
            oLog.Write "vbNdisIOControl: Insufficient buffer " & length & " provided to NdisRequest. Adjusting array length to " & length + 1024 & " and retrying"

            ' The previous call may return a size not a multiple of 4. So, adjust it to a multiple of 4
            length = length + 1024             

            ReDim Preserve buffer(length)
         Else
            oLog.Write "vbNdisIOControl: Not retrying with data type: " & TypeName(buffer)            
            requestStatus = NDIS_STATUS_FAILURE
            Exit Do
         End If

         ' Retry the request
         requestStatus = m_comAdapter.NdisIoControl(ioControlCode, oidList, numOids, buffer, length, bytesWritten, errorStatus)
         If(requestStatus <> 0) Then
            oLog.SafeFailed "vbNdisIOControl: Second attempt at NdisIoControl failed", 88888
            Exit Do
         End If         

      Loop

      If (errorStatus <> 0) Then
         oLog.Write "Status returned = " & errorStatus
      End If

      ' We return the STATUS code returned from the NdisIOControl call
      vbNdisIOControl = requestStatus
      
   End Function
     
   '================================================================================================='
   Public Function vbNdisIOControlEx(byval requestType, byval oid, byref struct)
   Dim bytesWritten        : bytesWritten          = 0
   Dim ndisIoControlStatus : ndisIoControlStatus   = 0
   Dim errorStatus         : errorStatus           = 0
   Dim bufferLen           : bufferLen             = 0
   Dim result              : result                = Empty
   Dim buffer()
  
      vbNdisIOControlEx = False
       
      If(oNDTStruct.vbStructureToArray(struct, buffer) = False) Then
         Exit Function
      End If
      
      ndisIoControlStatus = m_comAdapter.NdisIoControl(QUERY_GLOBAL_STATS, oid, 1, buffer, UBound(buffer), bytesWritten, errorStatus)
      If(ndisIoControlStatus <> 0) Then
          oLog.Failed "vbNdisIOControlEx: NdisIoControl() failed", 88888        
          Exit Function
      End If
      
      If(oNDTStruct.vbArrayToStructure(buffer, struct) = False) Then
         Exit Function
      End If
         
      oNDTStruct.vbPrintStructure(struct)
      
      vbNdisIOControlEx = True
                
   End Function
   
   '================================================================================================='
   '/**
   ' This is a backward compatibility function. No new script should use this function (use the 
   ' Ex version instead).
   ' This works like the old NdisIoControl and actually allocates space in the input buffer,
   ' and copies the results of NdisIoControl into that buffer and returns that to the caller
   '*/
   Public Function vbFastNdisIOControl(byval oid, byref buffer, byval queryType)
   Dim bytesWritten        : bytesWritten          = 0
   Dim ndisIoControlStatus : ndisIoControlStatus   = 0
   Dim errorStatus         : errorStatus           = 0
   Dim length              : length                = 0

      ' The old scripts do not pass an allocated buffer in, they expect us to create and populate
      ' the buffer
      If(IsArray(buffer)) Then
         If (UBound(buffer) > 0) Then
            If (VarType(buffer(0)) = vbLong) Then
               length = (UBound(buffer) + 1)* 4
               oLog.Write "vbFastNdisIOControl: Long Array  " & length
            Else
               length = (UBound(buffer) + 1)
               oLog.Write "vbFastNdisIOControl: Byte Array  " & length
            End If
         Else         
            oLog.Write "vbFastNdisIOControl: Empty Array  "
            length = 0
         End If
      Else
         If (VarType(buffer) = vbLong) Then
            oLog.Write "vbFastNdisIOControl: Long variable"
            length = 4
         ElseIf (VarType(buffer) = vbEmpty) Then
            ' For empty input variable, the length is zero
            oLog.Write "vbFastNdisIOControl: Empty variable"
            length = 0
         Else
            oLog.Write "vbFastNdisIOControl: Byte variable"
            length = 1
         End If
      End If

      ' We always assume that we get called with one (and only one) OID
      ndisIoControlStatus = Me.vbNdisIOControl(Oid, 1, buffer, length, bytesWritten, errorStatus, queryType)
      If((ndisIoControlStatus <> 0) Or (errorStatus <> 0)) Then
         vbFastNdisIOControl = False
      Else
         vbFastNdisIOControl = True
      End If
      
   End Function
   
   '============================================================================================='
   '/**
   'This method returns the Maximum Packet Size supported by the NIC. If the NIC reports
   'the MaxPacketSize as anything less than 40 bytes, or the query OID failes we log a 
   'safe error and report max packet size to the caller as being 50 bytes. Internally it 
   'is a query to OID_GEN_MAXIMUM_TOTAL_SIZE.
   '@return The maximum packet size supported by the NIC
   '@code
   'nMaxPacketSize = oTestCard.vbGetMaxPacketSize
   '@endcode
   '*/        
   Public Function vbGetMaxPacketSize()
   Dim result        : result          = False
   Dim maxPacketSize : maxPacketSize   = 0
      
      result = Me.vbFastNdisIOControl(OID_GEN_MAXIMUM_TOTAL_SIZE, maxPacketSize, QUERY_GLOBAL_STATS)
      vbGetMaxPacketSize = maxPacketSize
      
      If(result = True) Then
         If(maxPacketSize < 50) Then
            oLog.SafeFailed "vbGetMaxPacketSize: Invalid MaxPacketSize = " & maxPacketSize & " received from " & m_adapterName, 88888
            vbGetMaxPacketSize = 50
         End If
      Else
         oLog.SafeFailed "vbGetMaxPacketSize: Unable to get maximum total size for " & m_adapterName, 88888
         vbGetMaxPacketSize = 50
      End If
      
   End Function
   
   '============================================================================================='
   '/**
   'This method is used to get the maximum speed of the NIC in kbps. It is 
   'a query to the oid OID_GEN_LINK_SPEED.
   '@return The link speed on success and -1 on failure
   '@code
   'If (oTestCard.vbGetLinkSpeed () < 0 )Then
   '   oLog.Failed ("Failed to get link speed", 88888)
   '   Exit Function
   'End If
   '@endcode
   '*/
   Function vbGetLinkSpeed()
   Dim result     : result    = 0  
   Dim oid        : oid       = Empty
   Dim linkSpeed  : linkSpeed = 0
      
      oid = OID_GEN_LINK_SPEED
      result = Me.vbFastNdisIOControl(oid, linkSpeed, QUERY_GLOBAL_STATS)
      If(bResult = True) Then 
         oLog.Write "Link speed = " & linkSpeed
      Else
         linkSpeed = -1
         oLog.Write "vbGetLinkSpeed: Unable to obtain link speed from " & m_adapterName
      End If
      
      vbGetLinkSpeed = linkSpeed
      
   End Function
   
   '============================================================================================='
   '/**
   'Returns the broadcast address to be used with the particular media
   '@return The broadcast address
   '@code
   '       lBroadcastAddr = oTestCard.vbGetBroadcastAddress()
   '@endcode
   '*/
   Public Function vbGetBroadcastAddress()
   Dim broadcastAddr : broadcastAddr = Empty
      
      Select Case m_ndisMedium
         Case NDISMEDIUM802_3
            broadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
         Case NDISMEDIUM802_5
            broadcastAddr = NetAddr(&Hc0&, &H00&, &Hff&, &Hff&, &Hff&, &Hff&)
         Case NDISMEDIUMFDDI
            broadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
         Case Else
            oLog.Write "vbGetBroadcastAddress: BroadCast Address: Unknown media. Set to all 1s"
            broadcastAddr = NetAddr(&Hff&, &Hff&, &Hff&, &Hff&, &Hff&, &Hff&)
      End Select
      
      vbGetBroadcastAddress = broadcastAddr
      
   End Function
   
   '============================================================================================='
   '/**
   'Wait for the MEDIA_CONNECT_STATUS to change to connected. It does this by repeatedly
   'quering the oid OID_GEN_MEDIA_CONNECT_STATUS until it returns status connected, or 
   'until it has queries WaitTime number of times.
   '@params WaitTime  The time to wait for the link to be established 
   '@return  True if could establish link before timeout, else false
   '@code
   '   If (Not oTestCard.vbWaitForLink(90)) Then
   '       oLog.Write("Unable to establish link status")
   '   End If
   '@endcode
   '*/
   Function vbWaitForLink(byval waitTime)
   Dim connectStatus : connectStatus   = CLng(0)
   Dim connected     : connected       = 0
   Dim count         : count           = 0
   Dim result        : result          = False
     
      vbWaitForLink = False
      
      Do While (True)
      
         ' Sleep for a second
         Wscript.Sleep 1000
         
         result = Me.vbFastNdisIOControl(OID_GEN_MEDIA_CONNECT_STATUS, connectStatus, QUERY_GLOBAL_STATS)
         If(result = False) Then
            oLog.Write "vbWaitForLink: Unable to query media connect status.  If this is transient then it is not a failure."
         ElseIf (connectStatus = connected) Then
            ' If connected, then we are done! Return success
            vbWaitForLink = True
            Exit Do
         End If
         
         If(count = waitTime) Then
            oLog.SafeFailed "vbWaitForLink: Could not establish the link in " & waitTime & " seconds! Bailing out", 88888
            Exit Do
         End If
         
         count = count + 1
         
      Loop
      
   End Function
   
   '================================================================================================='
   '/**
   'This function queries and parses the OID_PNP_CAPABILITIES on the nic. It finds out if the
   'nic supporst wake up with magic packet, pattern match and link change
   '@params ! number returns the wake on lan capability for the nic on this system
   '@sa CLanOpen::vbSetWakeupType
   '*/
   Public Function vbWakeOnLanSupportInfo(byref systemWakeOnLanSupport)
   Dim wolSupport             : wolSupport            = CLng(0)
   Dim size                   : size                  = 0
   Dim flags                  : flags                 = 0
   Dim result                 : result                = False
   Dim minMagicPacketWakeUp   : minMagicPacketWakeUp  = 0
   Dim minPatternWakeUp       : minPatternWakeUp      = 0
   Dim minLinkChangeWakeUp    : minLinkChangeWakeUp   = 0
   Dim levels()
   
      systemWakeOnLanSupport = 0
     
      result = Me.vbFastNdisIOControl(OID_PNP_CAPABILITIES, levels, QUERY_GLOBAL_STATS)
      If(result = True) Then
      
         size = UBound(levels) + 1
         If(size = 16) Then
            
            ' Levels contains NDIS_PNP_CAPABILITIES structure
            ' which was retieved from driver by sending 
            ' IOCTL_NDIS_QUERY_GLOBAL_STATS ioctl to ndis stack.
            ' As a result of going through COM, Levels is an array of bytes
            ' in BIG ENDIAN format.
            ' The following code coverts the values back to 4 ULONGs
            '   	 
            flags = levels(0) + (2^8 * levels(1)) + (2^16 * levels(2)) + (2^24 * levels(3))
            minMagicPacketWakeUp = levels(4) + (2^8 * levels(5)) + (2^16 * levels(6)) + (2^24 * levels(7))
            minPatternWakeUp     = levels(8) + (2^8 * levels(9)) + (2^16 * levels(10)) + (2^24 * levels(11))
            minLinkChangeWakeUp  = levels(12) + (2^8 * levels(13)) + (2^16 * levels(14)) + (2^24 * levels(15))
            
            If(minMagicPacketWakeUp > 2) Then
               wolSupport = wolSupport Or WAKE_UP_MAGIC_PACKET
            End If
            
            If(minPatternWakeUp > 2) Then
               wolSupport = wolSupport Or WAKE_UP_PATTERN_MATCH
            End If
            
            If(minLinkChangeWakeUp > 2) Then
               wolSupport = wolSupport Or WAKE_UP_LINK_CHANGE
            End If
            
            ' This bit indicates whether the system and card will work together
            ' in their current abilities.  This bit is set by NDIS and cannot be
            ' modified by the drivers.
            
            ' This part is not used yet, but would be useful in future scripts
            If(flags <> 0) Then
               systemWakeOnLanSupport = 1
            Else
               If(wolSupport = 0) Then
                  oLog.Write "vbWakeOnLanSupportInfo: WakeOnLan is not enabled/supported for this adapter on this machine."
               End If
            End If
         Else
            oLog.SafeFailed "vbWakeOnLanSupportInfo: Unexpected array size " & size & " from oTestCard.NdisIOControl", 22859
         End If
         
      End If
      
      vbWakeOnLanSupportInfo = wolSupport
      
   End Function
End Class

'<!-- CRC = 0x546fe499 --->