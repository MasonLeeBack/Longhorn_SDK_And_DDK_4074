Option Explicit

Class CDevCaps
   Public DeviceType
   Public IsWPASupported
   Public IsTKIPSupported
   Public IsAESSupported
   Public IsWPAAdhocSupported
   
   Public Sub Class_Initialize()
      DeviceType              = WLAN_DEVICE_TYPE_802_11B ' DSSS is always assumed to be supported
      IsWPASupported          = False
      IsTKIPSupported         = False
      IsAESSupported          = False
      IsWPAAdhocSupported     = False
   End Sub
   
End Class

'================================================================================================='
'/**
' This class encapsulates the various operations that can be performed on a WLAN 802.11 NDTCore::Card
' object.
' @date      7/10/2003
' @author    David Harding
'*/
Class CWlanCard
   Private m_comAdapter    
   Private m_adapterName 
   Private m_devCaps
   Private m_ndisMedium
   Private m_ndisPhysicalMedium
   
   '================================================================================================='
   Public Sub Class_Initialize()
   
      Set m_comAdapter  = Nothing  
      Set m_devCaps     = New CDevCaps 
         
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
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
   Dim deviceOpen : Set deviceOpen = Nothing
   
      Set vbSetupBasicTest = deviceOpen
      
      ' Create the adapter object
      If(Me.vbCreateAdapter(adapterInfo) = False) Then
         Exit Function
      End If
                  
      Set deviceOpen = Me.vbOpenAdapter
      If(deviceOpen Is Nothing) Then
         Exit Function
      End If
      
      deviceOpen.vbAdapterType = adapterInfo.AdapterType
      
      ' Get the adapter capabilities if this is a wireless lan device
      If(adapterInfo.NdisPhysicalMedium = NDISPHYSICALMEDIUMWIRELESSLAN) Then
      
         If(Me.vbGetDeviceCapabilities(deviceOpen) = False) Then
            Exit Function
         End If
         
         Set deviceOpen.vbCapabilities = m_devCaps
         
      End If
     
      ' Now reset the device
      deviceOpen.vbWlanReset(True)
      deviceOpen.vbPrintCapabilities()
      
	   Set vbSetupBasicTest = deviceOpen
      
   End Function
      
   '================================================================================================='
   Public Function vbCreateAdapter(byval adapterInfo)
      
      vbCreateAdapter = False
      
      Select Case adapterInfo.AdapterType
      Case 1
         m_adapterName = "Test Device"
      Case 2
         m_adapterName = "Support Device"
      Case 3
         m_adapterName = "Message Device"
      Case 4
         m_adapterName = "Virtual Wan adapter"
      Case Else
         m_adapterName = "Unknown adapter"
      End Select
      
      m_ndisMedium         = CLng(adapterInfo.NdisMedium)
      m_ndisPhysicalMedium = CLng(adapterInfo.NdisPhysicalMedium)
      
      Set m_comAdapter = oNDTCore.CreateAdapter(adapterInfo)
      If(m_comAdapter Is Nothing) Then
         oLog.Write "vbCreateAdapter: Failed to create " & m_adapterName & " object"
         Exit Function
      End If
      
      vbCreateAdapter = True
      
   End Function
    
   '================================================================================================='
   Public Function vbGetDeviceCapabilities(byref deviceOpen)
   Dim devCaps : Set devCaps = New CDevCaps
   
      vbGetDeviceCapabilities = False
      
      If(vbDiscoverSupportedPhys(deviceOpen) = False) Then
      
      End If
      
      If(vbDiscoverSupportedAuthentication(deviceOpen) = False) Then
      
      End If
      
      If(vbDiscoverSupportedEncryption(deviceOpen) = False) Then
      
      End If
                    	
	   vbGetDeviceCapabilities = True
   	 
   End Function
   
   '================================================================================================='
   Public Function vbDiscoverSupportedPhys(byref deviceOpen)
   Dim networkTypeInUse    : networkTypeInUse   = -1
   Dim ndisStatus          : ndisStatus         = -1
   Dim index               : index              = 0 
   Dim networkType         : networkType        = 0
   Dim networkTypeList     : networkTypeList    = Array(Ndis802_11OFDM5, Ndis802_11OFDM24)                     
   Dim is11ASupported      : is11ASupported     = False
   Dim is11GSupported      : is11GSupported     = False
   
      vbDiscoverSupportedPhys = False
                         
      For Each networkType In networkTypeList
         
         Do
         
            ndisStatus = deviceOpen.vbSetWlanNetworkTypeInUse(networkType)
            If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
               oLog.WarnedEx "Failed to set OID_802_11_NETWORK_TYPE_IN_USE (Type: " & vbNetworkTypeToString(networkType) & ")", Null
               Exit Do
            End If
            
            ndisStatus = deviceOpen.vbGetWlanNetworkTypeInUse(networkTypeInUse)
            If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
               oLog.WarnedEx "Failed to query OID_802_11_NETWORK_TYPE_IN_USE", Null
               Exit Do
            End If
                        
            Select Case networkTypeInUse
            'Case Ndis802_11FH
            'Case Ndis802_11DS
            Case Ndis802_11OFDM5
               is11ASupported = True
            Case Ndis802_11OFDM24
               is11GSupported = True
            End Select
            
         Loop While(False)
         
      Next
      
      ' 802.11b Device
      If(is11ASupported = False And is11GSupported = False) Then
         m_devCaps.DeviceType = WLAN_DEVICE_TYPE_802_11B
      End If
      
      ' 802.11g Device
      If(is11ASupported = False And is11GSupported = True) Then
         m_devCaps.DeviceType = WLAN_DEVICE_TYPE_802_11G
      End If
      
      ' 802.11a\b Device
      If(is11ASupported = True And is11GSupported = False) Then
         m_devCaps.DeviceType = WLAN_DEVICE_TYPE_802_11AB
      End If
      
      ' 802.11a\g Device
      If(is11ASupported = True And is11GSupported = True) Then
         m_devCaps.DeviceType = WLAN_DEVICE_TYPE_802_11AG
      End If
      
	   vbDiscoverSupportedPhys = True
   	 
   End Function
   
   '================================================================================================='
   Public Function vbDiscoverSupportedAuthentication(byref deviceOpen)
   Dim object              : Set object         = Nothing
   Dim networkTypeInUse    : networkTypeInUse   = -1
   Dim authenticationMode  : authenticationMode = -1
   Dim encryptionStatus    : encryptionStatus   = -1
   Dim ndisStatus          : ndisStatus         = -1
   Dim networkTypes(1)
   
      vbDiscoverSupportedAuthentication = False
      
      ndisStatus = deviceOpen.vbSetWlanInfrastructureMode(Ndis802_11Infrastructure)
      If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.WarnedEx "Failed to set OID_802_11_INFRASTRUCTURE_MODE", Null
         Exit Function
      End If
     
            
      '--------------------------------------------------------------------------------------------
      ' Check if driver supports WPA
      Do
                  
         ndisStatus = deviceOpen.vbSetWlanAuthenticationMode(Ndis802_11AuthModeWPA)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to set OID_802_11_AUTHENTICATION_MODE", Null
            Exit Do
         End If
      
         ndisStatus = deviceOpen.vbGetWlanAuthenticationMode(authenticationMode)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to query OID_802_11_AUTHENTICATION_MODE", Null
            Exit Do
         End If
         
         If(authenticationMode = Ndis802_11AuthModeWPA) Then
            m_devCaps.IsWPASupported = True
         End If
         
      Loop While(False)
   
      '--------------------------------------------------------------------------------------------
      ' Check if driver supports WPA adhoc
      Do
         
         ndisStatus = deviceOpen.vbSetWlanAuthenticationMode(Ndis802_11AuthModeWPANone)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to set OID_802_11_AUTHENTICATION_MODE", Null
            Exit Do
         End If 
         
         ndisStatus = deviceOpen.vbGetWlanAuthenticationMode(authenticationMode)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to query OID_802_11_AUTHENTICATION_MODE", Null
            Exit Do
         End If 
         
         If(authenticationMode = Ndis802_11AuthModeWPANone) Then
            m_devCaps.IsWPAAdhocSupported = True
         End If
      
      Loop While(False)
    
              	
	   vbDiscoverSupportedAuthentication = True
   	 
   End Function
   
   '================================================================================================='
   Public Function vbDiscoverSupportedEncryption(byref deviceOpen)
   Dim encryptionStatus    : encryptionStatus   = -1
   Dim ndisStatus          : ndisStatus         = -1
 
      vbDiscoverSupportedEncryption = False
               
      '
      ' Check if TKIP is supported
      '
      Do
      
         ndisStatus = deviceOpen.vbSetWlanEncryptionStatus(Ndis802_11Encryption2Enabled)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to set OID_802_11_ENCRYPTION_STATUS", Null
            Exit Do
         End If
               
         ndisStatus = deviceOpen.vbGetWlanEncryptionStatus(encryptionStatus)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to query OID_802_11_ENCRYPTION_STATUS", Null
            Exit Do
         End If
         
         If(encryptionStatus = Ndis802_11Encryption2Enabled Or encryptionStatus = Ndis802_11Encryption2KeyAbsent) Then
            m_devCaps.IsTKIPSupported = True
         End If
      
      Loop While(False)
      
      
      '
      ' Check if AES is supported
      '
      Do
      
         ndisStatus = deviceOpen.vbSetWlanEncryptionStatus(Ndis802_11Encryption3Enabled)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to set OID_802_11_ENCRYPTION_STATUS", Null
            Exit Do
         End If
               
         ndisStatus = deviceOpen.vbGetWlanEncryptionStatus(encryptionStatus)
         If(ndisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.WarnedEx "Failed to query OID_802_11_ENCRYPTION_STATUS", Null
            Exit Do
         End If
         
         If(encryptionStatus = Ndis802_11Encryption3Enabled Or encryptionStatus = Ndis802_11Encryption3KeyAbsent) Then
            m_devCaps.IsAESSupported = True
         End If
      
      Loop While(False)
            
      
	   vbDiscoverSupportedEncryption = True
   	 
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
      
      'If(adapterOpen.vbNdisOpen <> 0) Then
      '   Exit Function
      'End If
                  
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
   Dim wlanOpen      : Set wlanOpen   = Nothing
      
      Set vbCreateOpen = Nothing
     
      Set adapterOpen = m_comAdapter.CreateOpen()
      If(adapterOpen is Nothing) Then
         oLog.Write "vbCreateOpen: Failed to create open on " & m_adapterName 
         Exit Function
      End If
      
      If(adapterOpen.NdisOpen(m_ndisMedium, False) = False) Then
         oLog.Write "vbCreateOpen: NdisOpen() failed"
         Exit Function
      End If
      
      Set wlanOpen                     = New CWlanOpen
      Set wlanOpen.vbCOMOpen           = adapterOpen
      wlanOpen.vbNdisMedium            = m_ndisMedium
      wlanOpen.vbNdisPhysicalMedium    = m_ndisPhysicalMedium
      wlanOpen.vbAdapterName           = m_adapterName
         
      Set vbCreateOpen = wlanOpen
      
   End Function
   
   '================================================================================================='
   Public Function vbVerifyDeviceCapabilities()
      
      vbVerifyDeviceCapabilities = False
     
         
      vbVerifyDeviceCapabilities = True
     
   End Function
   
   '================================================================================================='
   Public Function vbNdisIOControl(ByVal oid, ByRef data, ByRef bytesWritten, ByRef errorStatus, ByVal queryMode)
      
      vbNdisIOControl = m_comAdapter.NdisIOControl (oid, data, bytesWritten, errorStatus, queryMode)
      If(errorStatus <> 0) Then
         oLog.Failed "vbNdisIOControl: NdisIOControl failed (Error = " & errorStatus & ")", 88888
      End If
      
   End Function
   
   '================================================================================================='
   Public Function vbFastNdisIOControl(ByVal oid, ByRef data, ByVal queryMode)
   Dim bytesWritten  : bytesWritten = 0
   Dim errorStatus   : errorStatus  = 0
   
      vbFastNdisIOControl = Me.vbNdisIOControl (oid, data, BytesWritten, ErrorStatus, queryMode)
      If((Not vbFastNdisIOControl) Or (ErrorStatus <> 0)) Then
         vbFastNdisIOControl = False
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
      If(result = True) Then 
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

'<!-- CRC = 0xb06c85ee --->