Option Explicit

'================================================================================================='
'/**
' This class encapsulates the various operations that can be performed on a Native 802.11 NDTCore::Open
' object. 
' @date      7/10/2003
' @author    David Harding
'*/
Class CDot11Open
   Private m_comOpen
   Private m_ndisMedium
   Private m_ndisPhysicalMedium
   Private m_adapterName
   
   Private m_state
   Private m_mode
   Private m_phyType
   Private m_bssType
   Private m_nicPowerState
   
   '================================================================================================='
   Private Sub Class_Initialize
      Set m_comOpen = Nothing
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
   Public Property Get vbNdisPhysicalMedium
      vbNdisPhysicalMedium = m_ndisPhysicalMedium
   End Property
   
   Public Property Let vbNdisPhysicalMedium(byval ndisMedium)
      m_ndisPhysicalMedium = ndisMedium
   End Property
   
   '================================================================================================='
   Public Property Get vbAdapterName
      vbAdapterName = m_adapterName 
   End Property
   
   Public Property Let vbAdapterName(byval adapterName)
      m_adapterName = adapterName
   End Property
   
   '================================================================================================='
   Public Property Get vbState
      vbState = m_state 
   End Property
   
   '================================================================================================='
   '/**
   ' Returns the CurrentOpMode for example DOT11_OPERATION_MODE_STATION
   ' */
   Public Property Get vbMode
      vbMode = m_mode 
   End Property
   
   '================================================================================================='
   Public Property Get vbPHYType
      vbPHYType = m_phyType 
   End Property
   
   '================================================================================================='
   Public Property Get vbNICPowerState
      vbNICPowerState = m_nicPowerState 
   End Property
  
   Public Property Let vbNICPowerState(byval newVal)
      m_nicPowerState = newVal
   End Property
   
   '================================================================================================='
   Public Property Get vbBSSType
      vbBSSType = m_bssType 
   End Property
      
   '================================================================================================='
   Public Function vbPrintState()
   Dim mode       : mode         = "MODE: "
   Dim state      : state        = " | STATE: "
   'Dim bss       : bss          = " | BSS: "
   Dim phy        : phy          = " | PHY: "
   Dim powerState : powerState   = " | RADIO: " 
   Dim format     : format = ""
   
      Select Case Me.vbMode
         Case DOT11_OPERATION_MODE_AP
            mode = mode & "AP"
         Case DOT11_OPERATION_MODE_STATION
            mode = mode & "STA"
         Case Else
            mode = mode & "UNKNOWN (" & Me.vbMode & ")"  
      End Select
       
      Select Case Me.vbState
         Case N11_STATE_INIT
            state = state & "INIT"
         Case N11_STATE_OP
            state = state & "OP"
         Case Else
            state = state & "UNKNOWN (" & Me.vbState & ")"  
      End Select
   
      Select Case Me.vbPHYType
         Case Dot11PhyTypeFhss
            phy = phy & "FHSS"
         Case Dot11PhyTypeDsss
            phy = phy & "DSSS"
         Case Dot11PhyTypeIrbaseBand
            phy = phy & "IRBASEBAND"
         Case Dot11PhyTypeOfdm
            phy = phy & "OFDM"
         Case Dot11PhyTypeHrdsss
            phy = phy & "HRDSSS"
         Case Else
            phy = phy & "UNKNOWN (" & Me.vbPHYType & ")"  
      End Select
      
      Select Case Me.vbNICPowerState
         Case N11_RADIO_OFF
            powerState = powerState & "OFF"
         Case N11_RADIO_ON
            powerState = powerState & "ON"
         Case Else
            powerState = powerState & "UNKNOWN (" & Me.vbNICPowerState & ")"  
      End Select
   
      'Select Case Me.vbBSSType
      '   Case Dot11BssTypeInfrastructure
      '      bss = bss & "INFRASTRUCTURE"
      '   Case Dot11BssTypeIndependent
      '      bss = bss & "IBSS"
      '   Case Else
      '      bss = bss & "UNKNOWN"  
     ' End Select
      
      format = mode & state & phy & powerState   
      oLog.Write format

   End Function

   '================================================================================================='
   '/**
   'This function returns the MAC address being currently used by the device. It is only
   'valid for Lan media. It will query the appropriate CURRENT_ADDRESS oid to obtain
   'this address.
   '@return    The mac address currently in use by the media (Null Address on error)
   '@code
   '  DestAddr = oSuppOpen.vbGetCardAddress
   '@endcode
   '*/
   Public Function vbGetCardAddress
      Dim CardAddr
      Dim AddrOid
      
      Select Case Me.NdisMedium
         Case NDISMEDIUM802_3
            AddrOid = OID_802_3_CURRENT_ADDRESS
         Case NDISMEDIUM802_5
            AddrOid = OID_802_5_CURRENT_ADDRESS
         Case NDISMEDIUMFDDI
            AddrOid = OID_FDDI_LONG_CURRENT_ADDR
         Case Else
            AddrOid = 0
            Call oLog.SafeFailed ("GetCardAddress: Unknown media" , 88888)
      End Select
      
      CardAddr = NullAddr()
      
      If (AddrOid <> 0) Then
         Dim ErrorStatus
         Dim BytesWritten, BytesNeeded
         Dim NdisStatus
         
         ErrorStatus = Me.vbNdisRequest( _
               AddrOid, _
               CardAddr, _
               6, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         
         If (ErrorStatus <> 0) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_adapterName, 88888)
         End If
         
         If (NdisStatus <> 0) Then
            call oLog.SafeFailed ("Could not obtain address of " & m_adapterName , 88888)
         End If
      End If
      
      vbGetCardAddress = CardAddr
   End Function
   
   '============================================================================================='
   '/**
   'This method returns the Maximum Packet Size supported by the NIC. If the NIC reports
   'the MaxPacketSize as anything less than 40 bytes, or the query OID failes we log a 
   'safe error and report max packet size to the caller as being 50 bytes. The size is 
   'obtained using OID_GEN_MAXIMUM_TOTAL_SIZE
   '@return The maximum packet size supported by the NIC
   '@code
   'nMaxPacketSize = oTestOpen.vbGetMaxPacketSize ()
   '@endcode
   '*/ 
   Function vbGetMaxPacketSize() 
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus
      Dim ErrorStatus
      Dim lMaxTotalSize
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      ErrorStatus = Me.vbNdisRequest( _
            OID_GEN_MAXIMUM_TOTAL_SIZE, _
            lMaxTotalSize, _
            4, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)
      
      If(ErrorStatus = 0) Then
         If (lMaxTotalSize < 50) Then
            call oLog.SafeFailed ("Invalid value received from " & m_adapterName & " for maximum total size" , 88888)
            lMaxTotalSize = 50
         End If
      Else
         call oLog.SafeFailed ("Unable to get maximum total size from " & m_adapterName, 88888)
         lMaxTotalSize = 50
      End If
      
      If (NdisStatus <> 0) Then
         call oLog.SafeFailed ("Unable to get maximum total size from " & m_adapterName, 88888)
         lMaxTotalSize = 50
      End If
      
      vbGetMaxPacketSize = lMaxTotalSize
   End Function

   '============================================================================================='
   '/**
   ' The amount of time that the sender should wait, before it can assume  the
   ' driver/adapter has atleast made an attempt to send all the packets that
   ' were given to it. This time depends on the media.
   '@return The receive delay
   '@code
   '       lRecvDelay = oTestOpen.vbGetReceiveDelay()
   '@endcode
   '*/
   Public Function vbGetReceiveDelay()
      Select Case Me.NdisMedium
         Case NDISMEDIUM802_3
            vbGetReceiveDelay = 150
         Case NDISMEDIUM802_5
            vbGetReceiveDelay = 100
         Case NDISMEDIUMFDDI
            vbGetReceiveDelay = 50
         Case NDISMEDIUMIRDA
            vbGetReceiveDelay = 500
         Case Else
            oLog.Write("Receive Delay: Unsupported media" )
            vbGetReceiveDelay = 0
      End Select
   End Function   

   
   
   '================================================================================================='
   '/**
   'This function sets the packet filter. It also prints the filter it is trying to set.
   'Internally it makes a ndisrequest with oid OID_GEN_CURRENT_PACKET_FILTER.
   '@params
   ' ! number The filter we are trying to set
   '@return    True or false depending on whether the oid set was successful or not
   '@code
   '  If (Not oTestOpen.vbSetPacketFilter(DIRECTED)) Then
   '     Exit Function
   '  End If
   '@endcode
   '@sa CLanOpen6::vbGetFilters
   '*/
   Public Function vbSetPacketFilter (ByVal NewFilter)
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim strFilters, ErrorStatus
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      strFilters = "SetPacketFilter is setting the packet filter to "
      
      if (NewFilter = 0)Then
         strFilters = strFilters & "NOTHING "
      End if
      
      if (NewFilter AND DIRECTED)Then
         strFilters = strFilters & "DIRECTED "
      End If
      
      if (NewFilter AND BROADCAST)Then
         strFilters = strFilters & "BROADCAST "
      End If
      
      if (NewFilter AND PROMISCUOUS)Then
         strFilters = strFilters & "PROMISCUOUS "
      End If
      
      if (NewFilter AND MULTICAST)Then
         strFilters = strFilters & "MULTICAST "
      End If
      
      if (NewFilter AND ALL_MULTICAST)Then
         strFilters = strFilters & "ALL_MULTICAST "
      End If
      
      if (NewFilter AND FUNCTIONAL)Then
         strFilters = strFilters & "FUNCTIONAL "
      End If

      if (NewFilter AND ALL_FUNCTIONAL)Then
         strFilters = strFilters & "ALL_FUNCTIONAL "
      End If
      
      if (NewFilter AND GROUP_PKT)Then
         strFilters = strFilters & "GROUP "
      End If
      
      if (NewFilter AND MAC_FRAME)Then
         strFilters = strFilters & "MAC_FRAME "
      End If
      
      if (NewFilter AND SOURCE_ROUTING)Then
         strFilters = strFilters & "SOURCE_ROUTING "
      End If
      
      if (NewFilter AND ALL_LOCAL)Then
         strFilters = strFilters & "ALL_LOCAL "
      End If
      
      strFilters = strFilters & vblf
      
      oLog.Write(strFilters)
      
      ErrorStatus = Me.vbNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, _
            NewFilter, 4, REQUEST_SET_INFO, BytesWritten, BytesNeeded, NdisStatus, FALSE)
      
      If (ErrorStatus <> 0 Or NdisStatus <> 0) then
         call oLog.SafeFailed ("Unable to set packet filter for " & m_adapterName & " to " & Hex(NewFilter), 22852)
         vbSetPacketFilter = FALSE
      Else
         vbSetPacketFilter = TRUE
      End if
   End Function   
   
   '================================================================================================='
   '/**
   '@exclude
   'This function sets the packet filter. It only prints messages from core, and none on its own.
   'Internally it makes a ndisrequest with oid OID_GEN_CURRENT_PACKET_FILTER. This is a private function
   'for internal use only
   '@params
   ' ! number The filter we are trying to set
   '@return    True or False depending on whether the oid set was successful
   '@code
   '  If (Not oTestOpen.vbSilentSetPacketFilter(DIRECTED)) Then
   '     Exit Function
   '  End If
   '@endcode
   '@sa  CLanOpen6::vbSetPacketFilter
   '*/
   Private Function vbSilentSetPacketFilter(ParamFilterType)
      Dim BytesWritten, BytesNeeded
      Dim NdisStatus, ErrorStatus
      Dim FilterType
      FilterType = ParamFilterType ' Do this because NdisRequest can change it
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      ErrorStatus = Me.vbNdisRequest( _
            OID_GEN_CURRENT_PACKET_FILTER, _
            FilterType, _
            4, _
            REQUEST_SET_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            FALSE)

      vbSilentSetPacketFilter = TRUE
      If (ErrorStatus <> 0 Or NdisStatus <> 0) Then
         vbSilentSetPacketFilter = FALSE
      End If
      
   End Function
   
   
   '==========================================================================
   '/**
   'Gets all the filters supported by the card. The only way to obtain this
   'list is to try setting a filter, and if it suceeds, the filter is assumed
   'to be supported, else not. Because of some internal dependancies, it is
   'necessary that a Card::vbGetPhysicalMedium call must be made before 
   'vbGetFilters is invoked
   '@return    Returns a bitmask of the set of filter currently supported
   '@code
   '  AvailFilters = oTestOpen.vbGetFilters()
   '@endcode
   '@sa CLanOpen6::vbSetPacketFilter
   '*/  
   Public Function vbGetFilters()
      Dim bResult
      Dim l_nFilters
      Dim Media
      Dim OldFilter, FilterSize
      
      Media = m_ndisMedium

      ' obtain the current filter, so that we can restore it at the end of this function
      OldFilter = CLng(0)
      FilterSize = 4
      bResult = Me.vbFastNdisRequest(OID_GEN_CURRENT_PACKET_FILTER, OldFilter, FilterSize)
      If (Not bResult) Then
         oLog.Write ("Unable to obtain pretest filter state. Assuming it is NONE")
         OldFilter = 0
      End If
      
      l_nFilters = CLng(0)     
      If (Media = NDISMEDIUM802_3) Then
         l_nFilters = DIRECTED + BROADCAST + MULTICAST
         
         bResult = vbSilentSetPacketFilter(ALL_MULTICAST)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_MULTICAST
         End If
      ElseIf (Media = NDISMEDIUM802_5) Then
         l_nFilters = DIRECTED + BROADCAST + FUNCTIONAL + GROUP_PKT
         
         bResult = vbSilentSetPacketFilter(ALL_FUNCTIONAL)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_FUNCTIONAL
         End If
         
         bResult = vbSilentSetPacketFilter(SOURCE_ROUTING)
         If (bResult) Then
            l_nFilters = l_nFilters + SOURCE_ROUTING
         End If
         
         bResult = vbSilentSetPacketFilter(MAC_FRAME)
         If (bResult) Then
            l_nFilters = l_nFilters + MAC_FRAME
         End If
         
      ElseIf (Media = NDISMEDIUMFDDI) Then
         l_nFilters = DIRECTED + BROADCAST + MULTICAST
         
         bResult = vbSilentSetPacketFilter(ALL_MULTICAST)
         If (bResult) Then
            l_nFilters = l_nFilters + ALL_MULTICAST
         End If
         
         bResult = vbSilentSetPacketFilter(SOURCE_ROUTING)
         If (bResult) Then
            l_nFilters = l_nFilters + SOURCE_ROUTING
         End If
         
         bResult = vbSilentSetPacketFilter(MAC_FRAME)
         If (bResult) Then
            l_nFilters = l_nFilters + MAC_FRAME
         End If
         
         bResult = vbSilentSetPacketFilter(SMT)
         If (bResult) Then
            l_nFilters = l_nFilters + SMT
         End If
      Else
         call oLog.SafeFailed ("vbGetFilters called for invalid media type 0x" & Hex(Media), 88888)
      End If
      
      bResult = vbSilentSetPacketFilter(PROMISCUOUS)
      If (bResult) Then
         l_nFilters = l_nFilters + PROMISCUOUS
      Else
         ' Error is logged by LogoCheck.wsf
      End If
      
      bResult = vbSilentSetPacketFilter(ALL_LOCAL)
      If (bResult) Then
         l_nFilters = l_nFilters + ALL_LOCAL
      End If
      
      bResult = vbSilentSetPacketFilter(OldFilter)
      If (Not bResult) Then
         oLog.Write ("Unable to restore filter to pretest state")
      End If
      
      vbGetFilters = l_nFilters
   End Function
   
   
   '================================================================================================='
   '/**
   'This function performs an NdisOpen on the open instance. It binds ndistest.sys to the miniport 
   '@return    TRUE/FALSE depending on success of the operation
   '@code
   '   Set oSuppOpen = oSuppCard.vbCreateOpen
   '   If (oSuppOpen is Nothing) Then
   '      Exit Function
   '   End If
   '
   '   If (Not oSuppOpen.vbNdisOpen) Then
   '      Exit Function
   '   End If
   '@endcode
   '@sa CCard::vbCreateAdapter, CCard::vbCreateOpen
   '*/
   Public Function vbNdisOpen()
      ' Open instance of the adapter
      vbNdisOpen = m_comOpen.NdisOpen(m_ndisMedium)
      If (vbNdisOpen <> 0) Then
         oLog.Write "Unable to open instance of " & m_adapterName
      End If
      ' We do not need to keep count of opens because closing will anyways be done
      ' by the dlls, so not an issue
   End Function
   
   '================================================================================================='
   '/**
   'This function queries or sets oids from script.  The parameters are passed to the protocol driver
   'which calls NdisRequest.  The responses are passed back to the script in the cooresponding values.
   'This function allows us to specify if we want to allow resizing of the data buffer if the OID
   'requires more bytes than allocated for the buffer
   '@params
   '  ! number Oid to query or set
   '  ! array/number input and output buffer
   '  ! number length of buffer
   '  ! constant query or set
   '  ! number bytes written, taken from response of NdisRequest call
   '  ! number bytes needed, taken from response of NdisRequest call
   '  ! number ndistatus, taken from response of NdisRequest call
   '  ! bool tells whether we want to allow resizing of data buffer or not
   '@return value for NdisStatus that tells whether we could post the request or not (this
   '        is different from the status returned by NDIS which might be a failure
   '@code
   '  bResult = oTestOpen.vbNdisRequest (OID_GEN_SUPPORTED_LIST, arrList, 256, REQUEST_QUERY_INFO, _
         '                          nBytesWritten, nBytesNeeded, NdisStatus, TRUE)
   '@endcode
   '@sa COpen::vbFastNdisRequest, CCard::vbNdisIOControl
   '*/
   Public Function vbNdisRequest(ByVal oid, ByRef data, ByVal dataLength, ByVal requestType, ByRef bytesWritten, ByRef bytesNeeded, ByVal resize)
   Dim result        : result          = -1
   Dim ndisStatus    : ndisStatus      = -1
   Dim newSize       : newSize         = 0
   DIm bytesProvided : bytesProvided   = 0
   
      vbNdisRequest = ndisStatus
      
      
      result = m_comOpen.NdisRequest(oid, data, dataLength, requestType, bytesWritten, bytesNeeded, ndisStatus)
      If(result <> 0) Then
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
                     
                  ElseIf(VarType(DataArray(0)) = vbByte) Then
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
                  If(result <> 0) Then
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
      
      ' Update the internal state
      If(requestType = REQUEST_SET_INFO And vbNdisRequest = NDIS_STATUS_SUCCESS) Then 
         Me.vbUpdateState oid, data
      End If
      
   End Function    
   
   '================================================================================================='
   Public Function vbNdisRequestEx(byval queryType, byval oid, byref struct, byref bytesWritten, byref bytesNeeded, byval resize)
   Dim statusIndication : Set statusIndication  = Nothing
   Dim ndisStatus       : ndisStatus            = -1
   Dim result           : result                = Empty
   Dim buffer()
      
      vbNdisRequestEx = ndisStatus
                  
      If(queryType = REQUEST_SET_INFO) Then
         oNDTStruct.vbPrintStructure(struct)               
      End If
       
      If(oNDTStruct.vbStructureToArray(struct, buffer) = False) Then
         Exit Function
      End If
      
      result = m_comOpen.NdisRequest(oid, buffer, UBound(buffer), queryType, bytesWritten, bytesNeeded, ndisStatus)
      If(result <> 0) Then
         oLog.Failed "vbNdisRequestEx: NdisRequest() failed for " & m_adapterName, 88888
         Exit Function
      End If   
      
      If(queryType = REQUEST_QUERY_INFO) Then
      
         If(oNDTStruct.vbArrayToStructure(buffer, struct) = False) Then
            Exit Function
         End If    
                    
      End If
      
      ' Some of the OIDs have DOT11_STATUS_INDICATIONS returned in the input buffer
      ' We don't want to overwrite our structure data with the status indication so 
      ' the code below will pervernt this from happening and allow the object to still
      ' return status indication but keep the original data intact. 
      If(oid = OID_DOT11_AP_JOIN_REQUEST Or oid = OID_DOT11_JOIN_REQUEST Or _
         oid = OID_DOT11_START_REQUEST) Then
         
         ' Verify the structure type matches the OID
         Select Case oid
          
            Case OID_DOT11_AP_JOIN_REQUEST
               If(Not TypeName(struct) = "IDot11APJoinRequest") Then
                  Msgbox "Incorrect structure type (" & TypeName(struct) & ") for OID_DOT11_AP_JOIN_REQUEST"
                  Exit Function
               End If
            Case OID_DOT11_JOIN_REQUEST
               If(Not TypeName(struct) = "IDot11JoinRequest") Then
                  Msgbox "Incorrect structure type (" & TypeName(struct) & ") for OID_DOT11_JOIN_REQUEST"
                  Exit Function
               End If
            Case OID_DOT11_START_REQUEST
               If(Not TypeName(struct) = "IDot11StartRequest") Then
                  Msgbox "Incorrect structure type (" & TypeName(struct) & ") for OID_DOT11_START_REQUEST"
                  Exit Function
               End If
            Case OID_DOT11_RESET_REQUEST
               If(Not TypeName(struct) = "IDot11ResetRequest") Then
                  Msgbox "Incorrect structure type (" & TypeName(struct) & ") for OID_DOT11_RESET_REQUEST"
                  Exit Function
               End If
               
         End Select
         
         Set statusIndication = oNDTStruct.vbCreateStructure("Dot11StatusIndication")
         If(statusIndication Is Nothing) Then
            Exit Function
         End If
                  
         If(oNDTStruct.vbArrayToStructure(buffer, statusIndication) = False) Then
            Exit Function
         End If  
         
         'msgbox TypeName(struct) & ", " & statusIndication.StatusType & ", " & statusIndication.NdisStatus
         
         struct.Dot11StatusIndication.NdisStatus = statusIndication.NdisStatus
         struct.Dot11StatusIndication.StatusType = statusIndication.StatusType
         
         Set statusIndication = Nothing
         
      End If
                          
      If(resize = True) Then
         
         If(ndisStatus = NDIS_STATUS_BUFFER_TOO_SHORT Or ndisStatus = NDIS_STATUS_INVALID_LENGTH Or ndisStatus = NDIS_STATUS_BUFFER_OVERFLOW) Then
            
            If(oNDTStruct.vbAllocateStructure(bytesNeeded, struct) = False) Then
               Exit Function
            End If
           
            If(oNDTStruct.vbStructureToArray(struct, buffer) = False) Then
               Exit Function
            End If
         
            result = m_comOpen.NdisRequest(oid, buffer, UBound(buffer), queryType, bytesWritten, bytesNeeded, ndisStatus)
            If(result <> 0) Then
               oLog.Failed "vbNdisRequestEx: NdisRequest() failed for " & m_adapterName, 88888
               Exit Function
            End If 
            
            If(oNDTStruct.vbArrayToStructure(buffer, struct) = False) Then
               Exit Function
            End If
                                 
         End If
                
      End If
      
      If(queryType = REQUEST_QUERY_INFO) Then
         oNDTStruct.vbPrintStructure(struct)        
      End If
           
      vbNdisRequestEx = ndisStatus
      
      ' Update the internal state
      If(queryType = REQUEST_SET_INFO And vbNdisRequestEx = NDIS_STATUS_SUCCESS) Then 
         Me.vbUpdateState oid, struct
      End If
      
      
            
   End Function    

   '================================================================================================='
   '/**
   '*/
   Public Function vbClearEvents
      vbClearEvents = m_comOpen.GetEvents()
   End Function
   
   '================================================================================================='
   '/**
   'Performs an NdisClose on the COM Open object. This is used when the developer explicitly
   'wants to perform a close on the object. It then unbinds ndistest.sys from the miniport.
   'The user need not do this explicitly at the end of the scripts. It will be taken care of
   'by the NDTCore.
   '@return The return status of NdisClose
   '@code
   'bResult = oTestOpen.vbNdisClose()
   '@endcode
   '@sa  COpen::vbNdisOpen
   '*/
   Public Function vbNdisClose()
   
      vbNdisClose = m_comOpen.NdisClose ()
      If (vbNdisClose <> 0) Then
         oLog.Write ("Could not close open instance of " & m_adapterName)
         Exit Function
      End If
           
   End Function
      
   '================================================================================================='
   '/**
   'This function is a fast wrapper to ndisrequest. Unlike regular ndisrequest it does not return
   'bytes needed or ndis status. It just queries the OID and stores the result into an out
   'argument. It will resize the buffer only if the input buffer is an array. It can be used to query oids 
   'when we are sure 
   'that the query will succeed or we do not want to investigate failures. The result size make sense
   'only if the return value of the function is true, else it may be corrupted.
   '@params
   '  ! number The OID to query
   '  ! buffer The result buffer (can be an array or a number)
   '  ! number [in] Size of result buffer, [out] size of data in result buffer.
   '@return True if query succeeded with NDIS_STATUS_SUCCESS, false otherwise
   '@code
   '      Dim MacOptions
   '      bResult = oSuppOpen.vbFastNdisRequest(OID_GEN_MAC_OPTIONS, MacOptions, nResultSize)
   '      If (Not bResult) Then
   '         Call oLog.Failed ("Unable to query OID_GEN_MAC_OPTIONS on the test adapter." , 88888)
   '      End If
   '@endcode
   '@sa COpen::vbNdisRequest
   '*/
   Public Function vbFastNdisRequest(ByVal nOID, ByRef Result, ByRef ResultSize)
      Dim BytesWritten, BytesNeeded, NdisStatus, ErrorStatus
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      ' The caller generally knows what OID he is querying, and hence can give 
      ' a better message than some general one. So, no failure logging inside this
      ' function
      ErrorStatus = Me.vbNdisRequest( _
            nOID, _
            Result, _
            ResultSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            TRUE)

      vbFastNdisRequest = TRUE
      If (NdisStatus <> 0 Or ErrorStatus <> 0) Then
         vbFastNdisRequest = FALSE
      End If
      
      ResultSize =  BytesWritten
   End Function
   
   '============================================================================================='
   '/**
   ' This function, prints the information obtained from the query of the oid into the log file. 
   ' It works on the open instances of the adapter to query, and the oid to query for
   ' Internally it is just a wrapper to ndisrequest. It can be used when we do not wish to know
   ' the contents of the query, but want to just put the results of the query into the log
   ' @params  !   number OID to query
   ' @return      True if successful, false otherwise
   ' @code
   ' If (Not oTestOpen.vbPrintNdisRequest(OID_802_3_MULTICAST_LIST)) Then
   '        oLog.Failed ("Unable to query oid", 88888)
   ' End If     
   ' @endcode
   ' @sa COpen::vbNdisRequest, COpen::vbFastNdisRequest
   '*/
   Public Function vbPrintNdisRequest(nOid)
      Dim BytesWritten, BytesNeeded, NdisStatus, ErrorStatus
      Dim ResultBuffer()
      Dim BufferSize
      Dim bResult
      
      BufferSize=256
      ReDim ResultBuffer(BufferSize)
      
      BytesWritten = CLng(0)
      BytesNeeded = CLng(0)
      
      ResultBuffer(0) = CByte(0)
      ErrorStatus = Me.vbNdisRequest( _
            nOid, _
            ResultBuffer, _
            BufferSize, _
            REQUEST_QUERY_INFO, _
            BytesWritten, _
            BytesNeeded, _
            NdisStatus, _
            TRUE)

      vbPrintNdisRequest = TRUE
      If (NdisStatus <> 0 Or ErrorStatus <> 0) Then
         vbPrintNdisRequest = FALSE
      End If 
   End Function
   
   '================================================================================================='
   '/**
   'Performs an NdisReset on the COM Open object.
   '@return    The return status from NdisReset
   '@code   
   '  bResult = oTestOpen.vbNdisReset
   '@endcode
   '*/
   Public Function vbNdisReset
      Dim NdisStatus, ErrorStatus
      ErrorStatus = m_comOpen.NdisReset(NdisStatus)

      ' Our error status is higher priority than NDIS_STATUS
      If (ErrorStatus <> 0) Then
         vbNdisReset = ErrorStatus
      Else
         vbNdisReset = NdisStatus
      End If
      
   End Function
   
   '===============================================================================================//
   '/**
   'This command the number of certain events that have occured on this open.  Many of these are the
   'result of the protocol driver's StatusHandler being called.  The number of resets, disconnects,
   'and connects are returned to the script for special processing if needed.
   'This will keep track of the following events:<br>
   '   ulTotalEvents;             // total count from fields below<br>
   '   ulCompleteOpen;            // ProtocolOpenComplete calls<br>
   '   ulCompleteClose;           // ProtocolCloseComplete calls<br>
   '   ulCompleteSend;            // ProtocolSendComplete calls<br>
   '   ulCompleteTransfer;        // ProtocolTransferComplete calls<br>
   '   ulCompleteReset;           // ProtocolResetComplete calls<br>
   '   ulCompleteRequest;         // ProtocolRequestComplete calls<br>
   '   ulIndicateReceive;         // ProtocolIndicateReceive calls<br>
   '   ulIndicateStatus;          // ProtocolIndicateStatus calls<br>
   '   ulIndicateStatusComplete;  // ProtocolIndicateStatusComplete calls<br>
   '   ulMediaConnect;            // ProtocolIndicateStatus calls with Status = NDIS_STATUS_MEDIA_CONNECT<br>
   '   ulMediaDisConnect;         // ProtocolIndicateStatus calls with Status = NDIS_STATUS_MEDIA_DISCONNECT<br>
   '   ulResetStart;              // ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_START <br>
   '   ulResetEnd;                // ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_END <br>
   '   ulMultipleResetStart;      // Multiple ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_START <br>
   '   ulMultipleResetEnd;        // Multiple ProtocolIndicateStatus calls with Status = NDIS_STATUS_RESET_END <br>
   '   ulBreakpointsHit;          // number of times breakpoint situations hit
   ' A call to vbGetEvents clears all the above events
   '@command GetEvents
   '@params
   '  ! number Number resets that occured
   '  ! number Number of disconnects that occured
   '  ! number Number of connects that occured
   '@return True or false
   '@code
   'Resets = 0
   'Disconnects = 0
   'Connects = 0
   '
   'oLog.Variation("GetEvents for instance 1")
   'bResult = oTestOpen.vbGetEvents(Resets, Disconnects, Connects)
   'If(Not bResult) Then
   '   Call oLog.Write("Get events failed on first open instance" )
   'End If
   'If (Resets <> lNumResets) Then
   '   call oLog.Failed ("Incorrect number of reset events " & Resets & ". Should have been " & lNumResets , 88888)
   'End If      
   '
   'If ((Disconnects <> 0) And (Disconnects <> lNumResets)) Then
   '   call oLog.Failed ("Incorrect number of disconnect events " & Disconnects & ". Should have been 0 or " & lNumResets , 88888)
   'End If
   '
   'If ((Connects <> 0) And (Connects <> lNumResets)) Then
   '   call oLog.Failed ("Incorrect number of connect events " & Connects & ". Should have been 0 or " & lNumResets , 88888)
   'End If
   '
   'If (Connects <> Disconnects) Then
   '   call oLog.Failed ("Disconnect events " & Disconnects & " should equal connect events " & Connects , 88888)
   'End If
   '@endcode
   '@sa  COpen::vbClearEvents
   '*/
   Public Function vbGetEvents(ByRef nResets, ByRef nDisconnects, ByRef nConnects)
      Dim ErrorStatus
      ErrorStatus = m_comOpen.GetEvents (nResets, nDisconnects, nConnects)

      If (ErrorStatus <> 0) Then
         vbGetEvents = FALSE
      Else
         vbGetEvents = TRUE
      End If
   End Function   
   
   
   '============================================================================================='
   '/**
   'Adds the new multicast address into the multicast address list in the NIC
   'enabled for packet reception. It uses either OID_802_3_MULTICAST_LIST or 
   'OID_FDDI_LONG_MULTICAST_LIST for this purpose.
   '@TODO: This function will break after we move to Ndis 6.0
   '@params
   '  !  array The multicast address to be added
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbAddMuticastAddr(MultAddr)) Then 
   '   Exit Function
   'End If
   '@endcode
   '@sa CLanOpen6::vbRemoveMulticastAddr, CLanOpen6::vbSetPacketFilter
   '*/
   Public Function vbAddMulticastAddr(ByVal NewMulticastAddr)
      Dim bResult, ErrorStatus
      Dim ulOid
      Dim ulSizeOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim MaxListSize
      
      Dim MulticastAddrList()
      Dim ListLen
      
      Do
         bResult = TRUE
         
         '
         ' check for valid medium and set ulOidCode as appropriate
         '
         If((m_ndisMedium = NDISMEDIUM802_3) Or (m_ndisMedium = NDISMEDIUMDIX)) Then
            ulOid = OID_802_3_MULTICAST_LIST
            ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE 
         ElseIf (m_ndisMedium = NDISMEDIUMFDDI) Then
            ulOid = OID_FDDI_LONG_MULTICAST_LIST
            ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
         Else
            Call oLog.SafeFailed("Add Multicast Address not valid for this mediatype", 88888)
            bResult = FALSE
            Exit Do
         End If
         
         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         
         ErrorStatus = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_adapterName, 88888 )
            Exit Do
         End If
         
         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on
         
         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize
         
         Redim MulticastAddrList(ListLen-1)
         
         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))
         
         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_adapterName, 88888 )
            bResult = FALSE
            Exit Do
         Else
            ' Actual number of entries in the list
            ListLen = BytesWritten
         End If
         
         If (ListLen = 6*MaxListSize) Then
            ' In this case, the list is full, we should not try
            ' adding this address. But check if the address is already 
            ' present, in which case everything is okay
            
            Dim iIndex
            Dim iCnt
            bResult = FALSE
            iIndex = 0
            For iCnt = 0 To (ListLen \ 6 - 1)
               If (NetAddrCmpI(MulticastAddrList, NewMulticastAddr, iIndex)) Then
                  bResult = TRUE
                  Exit For
               End If
               iIndex = iIndex + 6
            Next  
            
            If (bResult) Then
               oLog.Write("Multicast address to be added already present" )
            Else
               oLog.Write("Multicast address list full. Could not add" )
            End If
            Exit Do
         End If
         
         ' If the multicast address list already contains the address we wish
         ' to add, we donot worry. We just add the new address. The adapter
         ' should be able to eliminate redundancies
         ' If we wish to remove the copy, we can use the loop from the delete 
         ' command below
         
         MulticastAddrList(ListLen+0) = NewMulticastAddr(0)
         MulticastAddrList(ListLen+1) = NewMulticastAddr(1)
         MulticastAddrList(ListLen+2) = NewMulticastAddr(2)
         MulticastAddrList(ListLen+3) = NewMulticastAddr(3)
         MulticastAddrList(ListLen+4) = NewMulticastAddr(4)
         MulticastAddrList(ListLen+5) = NewMulticastAddr(5)
         
         ListLen = ListLen + 6
         
         BytesWritten = 0
         BytesNeeded = 0 
         
         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0) Then
            Call oLog.SafeFailed("Unable to add multicast address to list on " & m_adapterName, 88888 )
         ElseIf (NdisStatus = NDIS_STATUS_MULTICAST_FULL) Then
            Call oLog.SafeFailed("Multicast address list full on " & m_adapterName, 88888)
            bResult = FALSE
         ElseIf (NdisStatus <> 0) Then
            Call oLog.SafeFailed("Add Multicast address failed on " & m_adapterName, 88888)
            bResult = FALSE
         End If
      Loop While(FALSE)

      If (bResult) Then
         If (ErrorStatus <> 0) Then
            bResult = FALSE
         End If
      End If
      vbAddMulticastAddr = bResult
   End Function
   
   '============================================================================================='
   '/**
   'Removes the given multicast address from the multicast address list
   'for the NIC.It uses either OID_802_3_MULTICAST_LIST or 
   'OID_FDDI_LONG_MULTICAST_LIST for this purpose.
   '@TODO: This function will break after we move to Ndis 6.0
   '@params
   '  !  array The multicast address to be removed
   '@return True on success, false otherwise
   '@code
   'If (Not oTestOpen.vbRemoveMulticastAddr(MultAddr)) Then 
   '   oLog.Write("Unable to remove multicast address")
   'End If
   '@endcode
   '@sa CLanOpen6::vbAddMulticastAddr, CLanOpen6::vbSetPacketFilter
   '*/
   Public Function vbRemoveMulticastAddr(ByVal OldMulticastAddr)
      Dim bResult, ErrorStatus
      Dim ulOid
      Dim ulSizeOid
      Dim BytesWritten, BytesNeeded, NdisStatus
      Dim MaxListSize
      Dim NewListLen
      Dim MulticastAddrList()
      Dim ModMulticastAddrList()
      Dim ListLen
      Dim iCnt
      Dim iNewIndex, iOldIndex
      
      Do
         bResult = TRUE
         
         '
         ' check for valid medium and set ulOidCode as appropriate
         '
         If ((m_ndisMedium = NDISMEDIUM802_3) Or (m_ndisMedium = NDISMEDIUMDIX)) Then
            ulOid = OID_802_3_MULTICAST_LIST
            ulSizeOid = OID_802_3_MAXIMUM_LIST_SIZE 
         ElseIf (m_ndisMedium = NDISMEDIUMFDDI) Then
            ulOid = OID_FDDI_LONG_MULTICAST_LIST
            ulSizeOid = OID_FDDI_LONG_MAX_LIST_SIZE
         Else
            Call oLog.SafeFailed("Delete Multicast Address not valid for this mediatype" , 88888)
            bResult = FALSE
            Exit Do
         End If
         
         ' Get the maximum number of multicast addresses possible
         MaxListSize = CLng(0)
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         ErrorStatus = Me.vbNdisRequest( _
               ulSizeOid, _
               MaxListSize, _
               4, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to get max multicast list size from " & m_adapterName, 88888 )
            bResult = FALSE
            Exit Do
         End If
         
         ' The array MulticastAddrList holds the net addresses, in sequence,
         ' with the first 6 bytes forming one address, the next 6 the second, and so on
         
         ' The maximum size of this array is then 6 times the maximum addresses
         ListLen = 6 * MaxListSize
         
         Redim MulticastAddrList(ListLen-1)
         
         ' Let it be know that MulticastAddrList is an array of bytes
         MulticastAddrList(0) = CByte(MulticastAddrList(0))
         BytesWritten = CLng(0)
         BytesNeeded = CLng(0)
         
         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               MulticastAddrList, _
               ListLen, _
               REQUEST_QUERY_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               TRUE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to obtain old multicast address list from " & m_adapterName, 88888)
            bResult = FALSE
            Exit Do
         Else
            ' Actual number of entries in the list
            ListLen = BytesWritten
         End If
         
         ' Maximum filled size of the new list that we would form
         Redim ModMulticastAddrList(ListLen-1)
         
         iNewIndex = CLng(0)
         iOldIndex = CLng(0)
         
         NewListLen = ListLen
         
         ' Here, we are deleting all the occurences of the address. But,
         ' we can modify to check if the card returns multiple copies of 
         ' an address by removing only the first occurence
         
         For iCnt = 0 To (ListLen \ 6 - 1)
            If (NetAddrCmpI(MulticastAddrList, OldMulticastAddr, iOldIndex)) Then
               NewListLen = NewListLen - 6
            Else
               ModMulticastAddrList(iNewIndex)   = MulticastAddrList(iOldIndex)
               ModMulticastAddrList(iNewIndex+1) = MulticastAddrList(iOldIndex+1)
               ModMulticastAddrList(iNewIndex+2) = MulticastAddrList(iOldIndex+2)
               ModMulticastAddrList(iNewIndex+3) = MulticastAddrList(iOldIndex+3)
               ModMulticastAddrList(iNewIndex+4) = MulticastAddrList(iOldIndex+4)
               ModMulticastAddrList(iNewIndex+5) = MulticastAddrList(iOldIndex+5)
               iNewIndex = iNewIndex + 6
            End If
            iOldIndex = iOldIndex + 6
         Next
         
         ' If we had to copy all the old addresses to the new one, we did not find the 
         ' address to delete
         If (NewListLen = ListLen) Then
            Call oLog.SafeFailed("Unable to find the multicast address to delete on " & m_adapterName, 88888)           
            bResult = FALSE
            Exit Do
         End If
         
         ListLen = NewListLen
         
         BytesWritten = 0
         BytesNeeded = 0 
         
         ErrorStatus = Me.vbNdisRequest( _
               ulOid, _
               ModMulticastAddrList, _
               ListLen, _
               REQUEST_SET_INFO, _
               BytesWritten, _
               BytesNeeded, _
               NdisStatus, _
               FALSE)
         If(ErrorStatus <> 0 Or NdisStatus <> 0) Then
            Call oLog.SafeFailed("Unable to delete multicast address from list on " & m_adapterName, 88888)
            bResult = FALSE
         End If
         
      Loop While (False)

      If (bResult) Then
         If (ErrorStatus <> 0) Then
            bResult = FALSE
         End If
      End If
      
      vbRemoveMulticastAddr = bResult
   End Function

   '================================================================================================='
   '/**
   'This API is used to Create an EndPoint on the Open Object. This API will also setup the CLanEndPoint
   'object that would be used for all the send/receive operations. 
   '@params
   '  !  number The type of endpoint that should be created
   '@return Instance of CLanEndPoint6 object created if successful, else Nothing
   '@code
   'Set oSuppEndPoint = oSuppOpen.vbCreateEndPoint (CLENDPOINT)
   'If (oSuppEndPoint Is Nothing) Then
   '   Exit Function
   'End If
   '@endcode
   '@sa  CLanEndPoint6::vbOpenCommunicationChannel, CLanEndPoint6::vbDestroyEndPoint
   '*/
   Public Function vbCreateEndPoint(EndPointType)
      Dim l_oCOMEndPoint          ' the NDTCore6::Open returned from above
      
      Set l_oCOMEndPoint = m_comOpen.CreateEndPoint(EndPointType)
      If l_oCOMEndPoint is Nothing Then
         Call oLog.SafeFailed("Failed to create endpoint on " & m_adapterName, 88888)
         Set vbCreateEndPoint = Nothing
      Else
         Dim l_oEndPoint
         Set l_oEndPoint = New CLanEndPoint6
         Set l_oEndPoint.COMEndPoint = l_oCOMEndPoint
         l_oEndPoint.AdapterType = m_adapterName
         Set vbCreateEndPoint = l_oEndPoint
      End If
   End Function

   '================================================================================================='
   '/**
   'Create a previously created CLanEndPoint6 object
   '@param  
   '  !  Object An instance of CLanEndPoint6
   '@return The error status from the operation (0 if sucessful)
   '@code
   'ErrorStatus  = oSuppOpen.vbDestroyEndPoint (oSuppEndPoint)
   '@endcode
   '@sa  CLanEndPoint6::vbCreateEndPoint
   '*/
   Public Function vbDestroyEndPoint(oVBEndPoint)
      vbDestroyEndPoint = m_comOpen.DestroyEndPoint(oVBEndPoint.COMEndPoint)
      Set oVBEndPoint = Nothing
   End Function   
   
   '================================================================================================='
   Public Function vbUpdateState(byval oid, byref object)
   Dim dot11BSSDescription       : Set dot11BSSDescription     = Nothing                                      
   Dim ndisStatus                : ndisStatus                  = -1
   Dim bytesWritten              : bytesWritten                = 0
   Dim bytesNeeded               : bytesNeeded                 = 0
                
      Select Case oid
      
         Case OID_DOT11_CURRENT_OPERATION_MODE
            m_mode   = object.CurrentOpMode
            m_state  = N11_STATE_INIT
            
         Case OID_DOT11_CURRENT_PHY_TYPE
            m_phyType = object
            
         Case OID_DOT11_RESET_REQUEST
            m_state  = N11_STATE_INIT
            
         Case OID_DOT11_NIC_POWER_STATE
            m_nicPowerState = object
            
         Case OID_DOT11_JOIN_REQUEST
            Set dot11BSSDescription = object.dot11BSSDescription
            If(dot11BSSDescription Is Nothing) Then
               oLog.Write "vbUpdateState: Failed to get dot11BSSDescription from dot11JoinRequest"
               Exit Function
            End If
            m_state     = N11_STATE_OP
            m_bssType   = dot11BSSDescription.dot11BSSType
         
         Case OID_DOT11_START_REQUEST
            Set dot11BSSDescription = object.dot11BSSDescription
            If(dot11BSSDescription Is Nothing) Then
               oLog.Write "vbUpdateState: Failed to get dot11BSSDescription from dot11StartRequest"
               Exit Function
            End If
            m_state     = N11_STATE_OP
            m_bssType   = dot11BSSDescription.dot11BSSType
         
      End Select
      
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11OperationalRateSet(byref object)
   Dim bytesWritten        : bytesWritten             = 0
   Dim bytesNeeded         : bytesNeeded              = 0
          
      vbSetDot11OperationalRateSet = Me.vbNdisRequestEx(REQUEST_SET_INFO,                   _ 
                                                        OID_DOT11_OPERATIONAL_RATE_SET,     _
                                                        object,                             _
                                                        bytesWritten,                       _
                                                        bytesNeeded,                        _
                                                        False)
      
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11OperationalRateSet(byref object)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
           
      vbGetDot11OperationalRateSet = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                 _ 
                                                        OID_DOT11_OPERATIONAL_RATE_SET,     _
                                                        object,                             _
                                                        bytesWritten,                       _
                                                        bytesNeeded,                        _
                                                        False)
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11SupportedPHYTypes(byref object)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
            
      vbGetDot11SupportedPHYTypes = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,              _ 
                                                       OID_DOT11_SUPPORTED_PHY_TYPES,   _
                                                       object,                          _
                                                       bytesWritten,                    _
                                                       bytesNeeded,                     _
                                                       False)
             
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11OperationalModeCapability(byref object)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
                   
      vbGetDot11OperationalModeCapability = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                    _ 
                                                               OID_DOT11_OPERATION_MODE_CAPABILITY,   _
                                                               object,                                _
                                                               bytesWritten,                          _
                                                               bytesNeeded,                           _
                                                               False)                 
   End Function
      
   '================================================================================================='
   Public Function vbGetDot11SupportedTxAntenna(byref object)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
           
      vbGetDot11SupportedTxAntenna = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                 _ 
                                                        OID_DOT11_SUPPORTED_TX_ANTENNA,     _
                                                        object,                             _
                                                        bytesWritten,                       _
                                                        bytesNeeded,                        _
                                                        False)
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11SupportedRxAntenna(byref object)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
           
      vbGetDot11SupportedRxAntenna = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                 _ 
                                                        OID_DOT11_SUPPORTED_RX_ANTENNA,     _
                                                        object,                             _
                                                        bytesWritten,                       _
                                                        bytesNeeded,                        _
                                                        False)
   End Function
      
   '================================================================================================='
   Public Function vbSetDot11CurrentOperationMode(byref object)
   Dim bytesWritten        : bytesWritten             = 0
   Dim bytesNeeded         : bytesNeeded              = 0
          
      vbSetDot11CurrentOperationMode = Me.vbNdisRequestEx(REQUEST_SET_INFO,                   _ 
                                                          OID_DOT11_CURRENT_OPERATION_MODE,   _
                                                          object,                             _
                                                          bytesWritten,                       _
                                                          bytesNeeded,                        _
                                                          False)
      
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11CurrentOperationMode(byref object)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
           
      vbGetDot11CurrentOperationMode = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                 _ 
                                                          OID_DOT11_CURRENT_OPERATION_MODE,   _
                                                          object,                             _
                                                          bytesWritten,                       _
                                                          bytesNeeded,                        _
                                                          False)
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11MacAddress(byref macAddress)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
      
      ReDim macAddress(6)
      
      vbGetDot11MacAddress = Me.vbNdisRequest(OID_DOT11_MAC_ADDRESS,   _
                                              macAddress,              _
                                              6,                       _
                                              REQUEST_QUERY_INFO,      _
                                              bytesWritten,            _
                                              bytesNeeded,             _
                                              False)
      
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11CurrentPacketFilter(byref filter)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
    
      vbSetDot11CurrentPacketFilter = Me.vbNdisRequest(OID_DOT11_CURRENT_PACKET_FILTER,  _
                                                       filter,                           _
                                                       4,                                _
                                                       REQUEST_SET_INFO,                 _
                                                       bytesWritten,                     _
                                                       bytesNeeded,                      _
                                                       False)
      
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11CurrentPacketFilter(byref filter)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
    
      vbGetDot11CurrentPacketFilter = Me.vbNdisRequest(OID_DOT11_CURRENT_PACKET_FILTER,  _
                                                       filter,                           _
                                                       4,                                _
                                                       REQUEST_QUERY_INFO,               _
                                                       bytesWritten,                     _
                                                       bytesNeeded,                      _
                                                       False)
      
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11FragmentationThreshold(byval threshold)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
    
      vbSetDot11FragmentationThreshold = Me.vbNdisRequest(OID_DOT11_FRAGMENTATION_THRESHOLD, _
                                                          threshold,                         _
                                                          4,                                 _
                                                          REQUEST_SET_INFO,                  _
                                                          bytesWritten,                      _
                                                          bytesNeeded,                       _
                                                          False)
      
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11FragmentationThreshold(byref threshold)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
    
      vbGetDot11FragmentationThreshold = Me.vbNdisRequest(OID_DOT11_FRAGMENTATION_THRESHOLD, _
                                                          threshold,                         _
                                                          4,                                 _
                                                          REQUEST_QUERY_INFO,                _
                                                          bytesWritten,                      _
                                                          bytesNeeded,                       _
                                                          False)
      
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11StationID(byref macAddress)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
      
      ReDim macAddress(6)
      
      vbGetDot11StationID = Me.vbNdisRequest(OID_DOT11_STATION_ID,    _
                                             macAddress,              _
                                             6,                       _
                                             REQUEST_QUERY_INFO,      _
                                             bytesWritten,            _
                                             bytesNeeded,             _
                                             False)
      
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11StationID(byref macAddress)
   Dim bytesWritten  : bytesWritten = 0
   Dim bytesNeeded   : bytesNeeded  = 0
      
      ReDim macAddress(6)
      
      vbSetDot11StationID = Me.vbNdisRequest(OID_DOT11_STATION_ID,    _
                                             macAddress,              _
                                             6,                       _
                                             REQUEST_SET_INFO,        _
                                             bytesWritten,            _
                                             bytesNeeded,             _
                                             False)
      
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11CurrentChannel(byval currentChannel)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbSetDot11CurrentChannel = Me.vbNdisRequest(OID_DOT11_CURRENT_CHANNEL,   _
                                                  currentChannel,              _
                                                  4,                           _
                                                  REQUEST_SET_INFO,            _
                                                  bytesWritten,                _
                                                  bytesNeeded,                 _
                                                  False)                   
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11CurrentChannel(byref currentChannel)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetDot11CurrentChannel = Me.vbNdisRequest(OID_DOT11_CURRENT_CHANNEL,   _
                                                  currentChannel,              _
                                                  4,                           _
                                                  REQUEST_QUERY_INFO,          _
                                                  bytesWritten,                _
                                                  bytesNeeded,                 _
                                                  False)        
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11CurrentPHYType(byval phyType)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbSetDot11CurrentPHYType = Me.vbNdisRequest(OID_DOT11_CURRENT_PHY_TYPE,  _
                                                  phyType,                     _
                                                  4,                           _
                                                  REQUEST_SET_INFO,            _
                                                  bytesWritten,                _
                                                  bytesNeeded,                 _
                                                  False)                   
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11RssiRange(byref object)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetDot11RssiRange = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,     _ 
                                               OID_DOT11_RSSI_RANGE,   _
                                               object,                 _
                                               bytesWritten,           _
                                               bytesNeeded,            _
                                               False)  
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11OptionalCapability(byref object)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetDot11OptionalCapability = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,            _ 
                                                        OID_DOT11_OPTIONAL_CAPABILITY,  _
                                                        object,                       _
                                                        bytesWritten,                 _
                                                        bytesNeeded,                  _
                                                        False)  
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11SupportedPowerLevels(byref object)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetDot11SupportedPowerLevels = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,                _ 
                                                          OID_DOT11_SUPPORTED_POWER_LEVELS,  _
                                                          object,                            _
                                                          bytesWritten,                      _
                                                          bytesNeeded,                       _
                                                          False)  
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11PowerMgmtMode(byref object)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetDot11PowerMgmtMode = Me.vbNdisRequestEx(REQUEST_QUERY_INFO,         _ 
                                                   OID_DOT11_POWER_MGMT_MODE,  _
                                                   object,                     _
                                                   bytesWritten,               _
                                                   bytesNeeded,                _
                                                   False)  
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11PowerMgmtMode(byref object)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbSetDot11PowerMgmtMode = Me.vbNdisRequestEx(REQUEST_SET_INFO,           _ 
                                                   OID_DOT11_POWER_MGMT_MODE,  _
                                                   object,                     _
                                                   bytesWritten,               _
                                                   bytesNeeded,                _
                                                   False)          
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11CurrentPHYType(byref phyType)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbGetDot11CurrentPHYType = Me.vbNdisRequest(OID_DOT11_CURRENT_PHY_TYPE,  _
                                                  phyType,                     _
                                                  4,                           _
                                                  REQUEST_QUERY_INFO,          _
                                                  bytesWritten,                _
                                                  bytesNeeded,                 _
                                                  False)        
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11ResetRequest(byref object)
   Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
    
      vbSetDot11ResetRequest = Me.vbNdisRequestEx(REQUEST_SET_INFO,        _ 
                                                  OID_DOT11_RESET_REQUEST, _
                                                  object,                  _
                                                  bytesWritten,            _
                                                  bytesNeeded,             _
                                                  False)
   
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11NICPowerState(byval powerState)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
       
      vbSetDot11NICPowerState = Me.vbNdisRequest(OID_DOT11_NIC_POWER_STATE,   _
                                                 powerState,                  _
                                                 4,                           _
                                                 REQUEST_SET_INFO,            _
                                                 bytesWritten,                _
                                                 bytesNeeded,                 _
                                                 False)  
              
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11NICPowerState(byref powerState)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
   
      vbGetDot11NICPowerState = Me.vbNdisRequest(OID_DOT11_NIC_POWER_STATE,   _
                                                 powerState,                  _
                                                 4,                           _
                                                 REQUEST_QUERY_INFO,          _
                                                 bytesWritten,                _
                                                 bytesNeeded,                 _
                                                 False)  
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11RFUsage(byref rfUsage)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
   
      vbGetDot11RFUsage = Me.vbNdisRequest(OID_DOT11_RF_USAGE, _
                                           rfUsage,            _
                                           4,                  _
                                           REQUEST_QUERY_INFO, _
                                           bytesWritten,       _
                                           bytesNeeded,        _
                                           False)   
   End Function
     
   '================================================================================================='
   Public Function vbGetDot11MPDUMaxLength(byref mpduMaxLength)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
      
      vbGetDot11MPDUMaxLength = Me.vbNdisRequest(OID_DOT11_MPDU_MAX_LENGTH,   _
                                                mpduMaxLength,               _
                                                4,                           _
                                                REQUEST_QUERY_INFO,          _
                                                bytesWritten,                _
                                                bytesNeeded,                 _
                                                False)
   End Function
     
   '================================================================================================='
   Public Function vbSetDot11BeaconPeriod(byval beaconPeriod)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
           
      vbSetDot11BeaconPeriod = Me.vbNdisRequest(OID_DOT11_BEACON_PERIOD,     _
                                                beaconPeriod,                _
                                                4,                           _
                                                REQUEST_SET_INFO,            _
                                                bytesWritten,                _
                                                bytesNeeded,                 _
                                                False)
      If(vbSetDot11BeaconPeriod <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "OID_DOT11_BEACON_PERIOD failed " & vbStatusToString(vbSetDot11BeaconPeriod)
      End If
   
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11BeaconPeriod(byref beaconPeriod)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
            
      vbGetDot11BeaconPeriod = Me.vbNdisRequest(OID_DOT11_BEACON_PERIOD,     _
                                                beaconPeriod,                _
                                                4,                           _
                                                REQUEST_QUERY_INFO,          _
                                                bytesWritten,                _
                                                bytesNeeded,                 _
                                                False)
      If(vbGetDot11BeaconPeriod <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "OID_DOT11_BEACON_PERIOD failed " & vbStatusToString(vbGetDot11BeaconPeriod)
      End If
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11CurrentCCAMode(byval ccaMode)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
           
      vbSetDot11CurrentCCAMode = Me.vbNdisRequest(OID_DOT11_CURRENT_CCA_MODE, _
                                                  ccaMode,                    _
                                                  4,                          _
                                                  REQUEST_SET_INFO,           _
                                                  bytesWritten,               _
                                                  bytesNeeded,                _
                                                  False) 
   
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11CurrentCCAMode(byref ccaMode)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
            
      vbGetDot11CurrentCCAMode = Me.vbNdisRequest(OID_DOT11_CURRENT_CCA_MODE, _
                                                  ccaMode,                    _
                                                  4,                          _
                                                  REQUEST_QUERY_INFO,         _
                                                  bytesWritten,               _
                                                  bytesNeeded,                _
                                                  False)
   End Function
   
   '================================================================================================='
   Public Function vbGetDot11CCAModeSupported(byref ccaMode)
   Dim bytesWritten     : bytesWritten       = 0
   Dim bytesNeeded      : bytesNeeded        = 0
            
      vbGetDot11CCAModeSupported = Me.vbNdisRequest(OID_DOT11_CCA_MODE_SUPPORTED, _
                                                    ccaMode,                      _
                                                    4,                            _
                                                    REQUEST_QUERY_INFO,           _
                                                    bytesWritten,                 _
                                                    bytesNeeded,                  _
                                                    False)
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11JoinRequest(byref dot11JoinRequest)  
   Dim bytesWritten              : bytesWritten                = 0
   Dim bytesNeeded               : bytesNeeded                 = 0
     
      vbSetDot11JoinRequest = Me.vbNdisRequestEx(REQUEST_SET_INFO,         _ 
                                                 OID_DOT11_JOIN_REQUEST,   _
                                                 dot11JoinRequest,         _
                                                 bytesWritten,             _
                                                 bytesNeeded,              _
                                                 False)
              
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11APJoinRequest(byref dot11APJoinRequest)  
   Dim bytesWritten              : bytesWritten                = 0
   Dim bytesNeeded               : bytesNeeded                 = 0
     
      vbSetDot11APJoinRequest = Me.vbNdisRequestEx(REQUEST_SET_INFO,            _ 
                                                   OID_DOT11_AP_JOIN_REQUEST,   _
                                                   dot11APJoinRequest,          _
                                                   bytesWritten,                _
                                                   bytesNeeded,                 _
                                                   False)
              
   End Function
      
   '================================================================================================='
   Public Function vbSetDot11StartRequest(byref dot11StartRequest)                
   Dim bytesWritten              : bytesWritten                = 0
   Dim bytesNeeded               : bytesNeeded                 = 0
     
      vbSetDot11StartRequest = Me.vbNdisRequestEx(REQUEST_SET_INFO,         _ 
                                                  OID_DOT11_START_REQUEST,  _
                                                  dot11StartRequest,        _
                                                  bytesWritten,             _
                                                  bytesNeeded,              _
                                                  False)              
      
   End Function
   
   '================================================================================================='
   Public Function vbSetDot11ScanRequest(byref object)            
   Dim bytesWritten  : bytesWritten    = 0
   Dim bytesNeeded   : bytesNeeded     = 0
                   
      vbSetDot11ScanRequest = Me.vbNdisRequestEx(REQUEST_SET_INFO,         _ 
                                                 OID_DOT11_SCAN_REQUEST,   _
                                                 object,                   _
                                                 bytesWritten,             _
                                                 bytesNeeded,              _
                                                 False)
         
   End Function
      
   '================================================================================================='
   Public Function vbStartAP(byval ssid, byval bssid, byval channel, byval filter)
   Dim dot11StartRequest   : Set dot11StartRequest = Nothing
   Dim dsParmIE            : Set dsParmIE          = Nothing 
   Dim ssidIE              : Set ssidIE            = Nothing     
	Dim ndisStatus          : ndisStatus            = -1
	    
	   vbStartAP = ndisStatus
	   
	   If(IsNull(ssid) = False) Then
         Set ssidIE = vbDot11CreateInfoElement(DOT11_INFO_ELEMENT_ID_SSID, ssid)
         If(ssidIE Is Nothing) Then
            Exit Function
         End If    
      End If
      
      Set dsParmIE = vbDot11CreateInfoElement(DOT11_INFO_ELEMENT_ID_DS_PARAM_SET, channel)
      If(dsParmIE Is Nothing) Then
         Exit Function
      End If  
      
      Set dot11StartRequest = oNDTStruct.vbCreateStructureAndAllocate("Dot11StartRequest", ssidIE.BytesAllocated + dsParmIE.BytesAllocated, True)
      If(dot11StartRequest Is Nothing) Then
         Exit Function
      End If
             
      dot11StartRequest.StartFailureTimeout                       = N11_BSSDESC_START_JOIN_TIMEOUT
      If(IsNull(bssid) = False) Then
         dot11StartRequest.dot11BSSDescription.dot11BSSID         = bssid
      End If
      dot11StartRequest.dot11BSSDescription.CapabilityInformation = DOT11_CAPABILITY_INFO_ESS
      dot11StartRequest.dot11BSSDescription.dot11BSSType          = Dot11BssTypeInfrastructure
      dot11StartRequest.dot11BSSDescription.BeaconPeriod          = N11_BSSDESC_BEACON_PERIOD
      If(IsNull(ssid) = True) Then
         dot11StartRequest.dot11BSSDescription.Buffer             = Array(dsParmIE)
      Else
         dot11StartRequest.dot11BSSDescription.Buffer             = Array(ssidIE, dsParmIE)
      End If
             
	   vbStartAP = Me.vbChangeOpMode(DOT11_OPERATION_MODE_AP, Null, Null)
      If(vbStartAP <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If  
      
      vbStartAP = Me.vbSetDot11CurrentPacketFilter(filter)
      If(vbStartAP <> NDIS_STATUS_SUCCESS) Then
         oLog.FailedEx "vbStartAP: Failed to set OID_DOT11_CURRENT_PACKET_FILTER", Null, 88888
         Exit Function
      End If  
                                                
      vbStartAP = Me.vbSetDot11StartRequest(dot11StartRequest)
               
   End Function
   
   '================================================================================================='
   Public Function vbJoinAP(byval ssid, byval bssid, byval channel, byval filter)
   Dim dot11JoinRequest    : Set dot11JoinRequest  = Nothing
   Dim dsParmIE            : Set dsParmIE          = Nothing 
   Dim ssidIE              : Set ssidIE            = Nothing 
	Dim ndisStatus          : ndisStatus            = -1
	
	   vbJoinAP = ndisStatus
	   
	   If(IsNull(ssid) = False) Then
         Set ssidIE = vbDot11CreateInfoElement(DOT11_INFO_ELEMENT_ID_SSID, ssid)
         If(ssidIE Is Nothing) Then
            Exit Function
         End If    
      End If
      
      Set dsParmIE = vbDot11CreateInfoElement(DOT11_INFO_ELEMENT_ID_DS_PARAM_SET, channel)
      If(dsParmIE Is Nothing) Then
         Exit Function
      End If  
            
      Set dot11JoinRequest = oNDTStruct.vbCreateStructureAndAllocate("Dot11JoinRequest", 40, True)
      If(dot11JoinRequest Is Nothing) Then
         Exit Function
      End If
                      
      dot11JoinRequest.JoinFailureTimeout                   = N11_BSSDESC_START_JOIN_TIMEOUT
      If(IsNull(bssid) = False) Then
         dot11JoinRequest.dot11BSSDescription.dot11BSSID    = bssid
      End If
      dot11JoinRequest.dot11BSSDescription.dot11BSSType     = Dot11BssTypeInfrastructure
      dot11JoinRequest.dot11BSSDescription.BeaconPeriod     = N11_BSSDESC_BEACON_PERIOD
      If(IsNull(ssid) = True) Then
         dot11JoinRequest.dot11BSSDescription.Buffer        = Array(dsParmIE)
      Else
         dot11JoinRequest.dot11BSSDescription.Buffer        = Array(ssidIE, dsParmIE)
      End If
     
	   vbJoinAP = Me.vbChangeOpMode(DOT11_OPERATION_MODE_STATION, Null, Null)
      If(vbJoinAP <> NDIS_STATUS_SUCCESS) Then
         Exit Function
      End If  
      
      vbJoinAP = Me.vbSetDot11CurrentPacketFilter(filter)
      If(vbJoinAP <> NDIS_STATUS_SUCCESS) Then
         oLog.FailedEx "vbJoinAP: Failed to set OID_DOT11_CURRENT_PACKET_FILTER", Null, 88888
         Exit Function
      End If  
                   
      vbJoinAP = Me.vbSetDot11JoinRequest(dot11JoinRequest)
               
   End Function
      
   '================================================================================================='
   Public Function vbChangeOpMode(byval opMode, byval resetType, byval fullReset)
   Dim dot11OpMode         : Set dot11OpMode       = Nothing
   Dim dot11ResetRequest   : Set dot11ResetRequest = Nothing
   Dim dot11BSSID          : dot11BSSID            = Empty
	Dim ndisStatus          : ndisStatus            = -1
	    
	   vbChangeOpMode = ndisStatus
	         
      Set dot11ResetRequest = oNDTStruct.vbCreateStructure("Dot11ResetRequest")
      If(dot11ResetRequest Is Nothing) Then
         Exit Function
      End If
      
      Set dot11OpMode = oNDTStruct.vbCreateStructure("Dot11CurrentOperationMode")
      If(dot11OpMode Is Nothing) Then
         Exit Function
      End If
      
      vbChangeOpMode = Me.vbGetDot11MacAddress(dot11BSSID)
      If(vbChangeOpMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "vbChangeOpMode: Failed to set OID_DOT11_MAC_ADDRESS"
         Exit Function
      End If
      
      dot11OpMode.CurrentOpMode                                = opMode
      
      dot11ResetRequest.dot11ResetType                         = Dot11ResetTypePhyAndMac
      'dot11ResetRequest.dot11MacAddress                        = dot11BSSID
      dot11ResetRequest.SetDefaultMIB                          = True
      
      If(IsNull(resetType) = False) Then
         dot11ResetRequest.dot11ResetType                      = resetType
      End If
     
      If(fullReset = True) Then
         dot11ResetRequest.SetDefaultMIB                       = True
      End If
               
	   vbChangeOpMode = Me.vbSetDot11ResetRequest(dot11ResetRequest)
      If(vbChangeOpMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "vbChangeOpMode: Failed to set OID_DOT11_RESET_REQUEST"
         Exit Function
      End If
            
      vbChangeOpMode = Me.vbSetDot11CurrentOperationMode(dot11OpMode)
      If(vbChangeOpMode <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "vbChangeOpMode: Failed to set OID_DOT11_CURRENT_OPERATION_MODE"
         Exit Function
      End If
     
   End Function
           
End Class


'<!-- CRC = 0x43afe3fe --->