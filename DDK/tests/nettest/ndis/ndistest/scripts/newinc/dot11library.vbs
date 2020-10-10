Option Explicit

Const N11LIB_REGISTRY_KEY = "HKEY_CURRENT_USER\Software\Microsoft\NDTEST\Native80211\"

' HACK These can be removed once the IM test are removed or replaced
Dim gIMTestsEnabled  : gIMTestsEnabled = 0
Dim gIMAdhoc         : gIMAdhoc        = 0

vbDot11CheckRegistry()

'================================================================================================='
Public Function vbDot11CheckRegistry()
Dim shell   : Set shell = CreateObject("WScript.Shell")
Dim result  : result    = ""

   On Error Resume Next
   
   ' HACK This is a hack until the IM test are removed or replaced
   Do
      gIMTestsEnabled          = shell.RegRead(N11LIB_REGISTRY_KEY & "EnableIMTests")
      If(Err.number <> 0) Then
         Exit Do
      End If
      
      If(gIMTestsEnabled = 1) Then
         gIMAdhoc = shell.RegRead(N11LIB_REGISTRY_KEY & "IMAdhoc")
         If(Err.number <> 0) Then
            Exit Do
         End If
      End If
       
   Loop While(False)
   
   On Error Goto 0

End Function

'================================================================================================='
Public Function vbDot11MacAddressToString(byval macArray)

   vbDot11MacAddressToString = Hex(macArray(0)) & "-" & _
                             Hex(macArray(1)) & "-" & _
                             Hex(macArray(2)) & "-" & _
                             Hex(macArray(3)) & "-" & _
                             Hex(macArray(4)) & "-" & _
                             Hex(macArray(5))
End Function

'================================================================================================='
Public Function vbDot11CreateMacAddress(byval byte1, byval byte2, byval byte3, byval byte4, byval byte5, byval byte6)

   vbDot11CreateMacAddress = Array(CByte(byte1),CByte(byte2),CByte(byte3),CByte(byte4),CByte(byte5),CByte(byte6))
   
End Function

'================================================================================================='
'/**
' This function is called to create an information element structure object. It will first create
' the structure object, allocate memory for it based on the length of the data being passed in. 
' Once the object is created and allocated it will initialize the elementID, length, set the 
' data on the object and return it. The data type must be an array or string else the function 
' will fail. The caller should always check for Is Nothing on the return.
' @params
' !number    ElementID to be set for the Information Element, must be a valid elementID value
' !variant   Data to be add to the information element, must be a string or an array
' @returns
' A reference to the information element object if successful, else returns Nothing
' @example
' Set obj = vbCreateInfoElement(0, "FOO")
' If(obj Is Nothing) Then
'    Handle Failure
' End If
' */
Function vbDot11CreateInfoElement(byval elementID, byval data)
Dim struct  : Set struct   = Nothing
Dim length  : length       = 0
Dim index   : index        = 0
Dim arr()

   Set vbDot11CreateInfoElement = Nothing
   
   Do
      
      ' Determine how much memory to allocate
      If(IsArray(data) = True) Then
         length = UBound(data) + 1 ' Must add one for the zero index
      ElseIf(VarType(data) = vbString) Then
         length = Len(data)
      ElseIf(VarType(data) = vbInteger Or VarType(data) = vbLong Or VarType(data) = vbSingle) Then
         length = 1
      Else
         oLog.FailedEx "vbN11CreateInfoElement: Invalid type, must be string, numeric or array (VarType = " & VarType(data) & ")", Null, 88888
         Exit Do
      End If
            
      ' Create the information element object, allocate enough memory for the data and 
      ' two more bytes for the elementID and length field
      Set struct = oNDTStruct.vbCreateStructureAndAllocate("InformationElement", length + 2, False)
      If(struct Is Nothing) Then
         Exit Do
      End If
      
      struct.ElementID  = elementID
      struct.Length     = length
      
      ' Set the data on the object based on the type
      If(IsArray(data) = True) Then
         ReDim arr(length)
         For index = 0 To UBound(data)
            arr(index) = CByte(data(index))
         Next
         struct.Data = arr
      ElseIf(VarType(data) = vbString) Then
         struct.Data = data
      ElseIf(VarType(data) = vbInteger Or VarType(data) = vbLong Or VarType(data) = vbSingle) Then
         struct.Data = CByte(data)
      End If
                  
      Set vbDot11CreateInfoElement = struct
      
   Loop While(False)
      
End Function


'================================================================================================='
Public Function vbDot11PowerMgmtModeToString(byval val)
Dim list(3)
   
   list(0) = "Dot11PowerModeUnknown"
   list(1) = "Dot11PowerModeActive"
   list(2) = "Dot11PowerModePowerSave"
  
   vbDot11PowerMgmtModeToString = list(val)
   
End Function
 
'================================================================================================='
Public Function vbDot11CCAModeToString(byval ccaMode)
   
   vbDot11CCAModeToString = "CCAMode: "
   
   If((ccaMode And DOT11_CCA_MODE_ED_ONLY) = DOT11_CCA_MODE_ED_ONLY) Then
      vbDot11CCAModeToString = vbDot11CCAModeToString & "DOT11_CCA_MODE_ED_ONLY "
   End If
   
   If((ccaMode And DOT11_CCA_MODE_CS_ONLY) = DOT11_CCA_MODE_CS_ONLY) Then
      vbDot11CCAModeToString = vbDot11CCAModeToString & "DOT11_CCA_MODE_CS_ONLY "
   End If
   
   If((ccaMode And DOT11_CCA_MODE_ED_and_CS) = DOT11_CCA_MODE_ED_and_CS) Then
      vbDot11CCAModeToString = vbDot11CCAModeToString & "DOT11_CCA_MODE_ED_and_CS "
   End If
   
End Function

Dim DOT11_STATUS_SCAN_CONFIRM                                   : DOT11_STATUS_SCAN_CONFIRM                                   = CLng(1)
Dim DOT11_STATUS_JOIN_CONFIRM                                   : DOT11_STATUS_JOIN_CONFIRM                                   = CLng(2)
Dim DOT11_STATUS_START_CONFIRM                                  : DOT11_STATUS_START_CONFIRM                                  = CLng(3)
Dim DOT11_STATUS_RESET_CONFIRM                                  : DOT11_STATUS_RESET_CONFIRM                                  = CLng(4)
Dim DOT11_STATUS_AP_JOIN_CONFIRM                                : DOT11_STATUS_AP_JOIN_CONFIRM                                = CLng(5)

'================================================================================================='
Public Function vbDot11StatusIndicationToString(byval val)
Dim list(6)
   
   list(1) = "DOT11_STATUS_SCAN_CONFIRM"
   list(2) = "DOT11_STATUS_JOIN_CONFIRM"
   list(3) = "DOT11_STATUS_START_CONFIRM"
   list(4) = "DOT11_STATUS_RESET_CONFIRM"
   list(5) = "DOT11_STATUS_AP_JOIN_CONFIRM"
  
   If(val <= 0 Or val > 5) Then
      vbDot11StatusIndicationToString = "DOT11_STATUS_UNKNOWN"
      Exit Function
   End If
 
   vbDot11StatusIndicationToString = list(val)
   
End Function

'================================================================================================='
Public Function vbDot11PHYTypeToString(byval val)
Dim list(6)
   
   list(0) = "Dot11PhyTypeUnknown"
   list(1) = "Dot11PhyTypeFhss"
   list(2) = "Dot11PhyTypeDsss"
   list(3) = "Dot11PhyTypeIrbaseBand"
   list(4) = "Dot11PhyTypeOfdm"
   list(5) = "Dot11PhyTypeHrdsss"
   
   vbDot11PHYTypeToString = list(val)
   
End Function

'================================================================================================='
Public Function vbDot11BSSTypeToString(byval val)
Dim list(4)
   
   list(0) = "Dot11BssTypeUnknown"
   list(1) = "Dot11BssTypeInfrastructure"
   list(2) = "Dot11BssTypeIndependent"
   list(3) = "Dot11BssTypeAny"
      
   vbDot11BSSTypeToString = bssTypeList(val)
   
End Function

'================================================================================================='
Public Function vbDot11OperationModeToString(byval mode)
Dim index   : index = 0
Dim opModeTable(3,2)
   
   opModeTable(0, 0) = DOT11_OPERATION_MODE_AP
   opModeTable(0, 1) = "DOT11_OPERATION_MODE_AP"
   
   opModeTable(1, 0) = DOT11_OPERATION_MODE_STATION
   opModeTable(1, 1) = "DOT11_OPERATION_MODE_STATION"
   
   opModeTable(2, 0) = DOT11_OPERATION_MODE_UNKNOWN
   opModeTable(3, 1) = "DOT11_OPERATION_MODE_UNKNOWN"
   
   For index = 0 To UBound(opModeTable)
      If(opModeTable(index, 0) = mode) Then
         vbDot11OperationModeToString = opModeTable(index, 1)
         Exit Function
      End If
   Next
   
   vbDot11OperationModeToString = "Unknown (" & Hex(mode) & ")"
    
End Function

'================================================================================================='
Public Function vbDot11StatusToString(byval status)
Dim index   : index = 0
Dim statusCodes(18,2)
   
   statusCodes(0, 0) = DOT11_STATUS_SUCCESS
   statusCodes(0, 1) = "DOT11_STATUS_SUCCESS"
   
   statusCodes(1, 0) = DOT11_STATUS_RETRY_LIMIT_EXCEEDED
   statusCodes(1, 1) = "DOT11_STATUS_RETRY_LIMIT_EXCEEDED"
   
   statusCodes(2, 0) = DOT11_STATUS_UNSUPPORTED_PRIORITY
   statusCodes(2, 1) = "DOT11_STATUS_UNSUPPORTED_PRIORITY"
   
   statusCodes(3, 0) = DOT11_STATUS_UNSUPPORTED_SERVICE_CLASS
   statusCodes(3, 1) = "DOT11_STATUS_UNSUPPORTED_SERVICE_CLASS"
   
   statusCodes(4, 0) = DOT11_STATUS_UNAVAILABLE_PRIORITY
   statusCodes(4, 1) = "DOT11_STATUS_UNAVAILABLE_PRIORITY"
   
   statusCodes(5, 0) = DOT11_STATUS_UNAVAILABLE_SERVICE_CLASS
   statusCodes(5, 1) = "DOT11_STATUS_UNAVAILABLE_SERVICE_CLASS"
   
   statusCodes(6, 0) = DOT11_STATUS_XMIT_MSDU_TIMER_EXPIRED
   statusCodes(6, 1) = "DOT11_STATUS_XMIT_MSDU_TIMER_EXPIRED"
   
   statusCodes(7, 0) = DOT11_STATUS_UNAVAILABLE_BSS
   statusCodes(7, 1) = "DOT11_STATUS_UNAVAILABLE_BSS"
   
   statusCodes(8, 0) = DOT11_STATUS_EXCESSIVE_DATA_LENGTH
   statusCodes(8, 1) = "DOT11_STATUS_EXCESSIVE_DATA_LENGTH"
   
   statusCodes(9, 0) = DOT11_STATUS_ENCRYPTION_FAILED
   statusCodes(9, 1) = "DOT11_STATUS_ENCRYPTION_FAILED"
   
   statusCodes(10, 0) = DOT11_STATUS_WEP_KEY_UNAVAILABLE
   statusCodes(10, 1) = "DOT11_STATUS_WEP_KEY_UNAVAILABLE"
   
   statusCodes(11, 0) = DOT11_STATUS_ICV_VERIFIED
   statusCodes(11, 1) = "DOT11_STATUS_ICV_VERIFIED"
   
   statusCodes(12, 0) = DOT11_STATUS_PACKET_REASSEMBLED
   statusCodes(12, 1) = "DOT11_STATUS_PACKET_REASSEMBLED"
   
   statusCodes(13, 0) = DOT11_STATUS_PACKET_NOT_REASSEMBLED
   statusCodes(13, 1) = "DOT11_STATUS_PACKET_NOT_REASSEMBLED"
   
   statusCodes(14, 0) = DOT11_STATUS_GENERATE_AUTH_FAILED
   statusCodes(14, 1) = "DOT11_STATUS_GENERATE_AUTH_FAILED"
   
   statusCodes(15, 0) = DOT11_STATUS_AUTH_NOT_VERIFIED
   statusCodes(15, 1) = "DOT11_STATUS_AUTH_NOT_VERIFIED"
   
   statusCodes(16, 0) = DOT11_STATUS_AUTH_VERIFIED
   statusCodes(16, 1) = "DOT11_STATUS_AUTH_VERIFIED"
   
   statusCodes(17, 0) = DOT11_STATUS_AUTH_FAILED
   statusCodes(17, 1) = "DOT11_STATUS_AUTH_FAILED"
   
   For index = 0 To UBound(statusCodes)
      If(statusCodes(index, 0) = status) Then
         vbDot11StatusToString = "(StatusType = " & statusCodes(index, 1) & ")"
         Exit Function
      End If
   Next
   
   vbDot11StatusToString = "(StatusType = Unknown (" & Hex(status) & ")"
    
End Function

'================================================================================================='
Public Function vbDot11PacketFilterToString(byval filter)
Dim index   : index = 0
Dim table(15,2)
 	                                                           
   table(0, 0) = DOT11_PACKET_TYPE_DIRECTED_CTRL
   table(0, 1) = "DOT11_PACKET_TYPE_DIRECTED_CTRL"
   
   table(1, 0) = DOT11_PACKET_TYPE_DIRECTED_MGMT
   table(1, 1) = "DOT11_PACKET_TYPE_DIRECTED_MGMT"
   
   table(2, 0) = DOT11_PACKET_TYPE_DIRECTED_DATA
   table(2, 1) = "DOT11_PACKET_TYPE_DIRECTED_DATA"
   
   table(3, 0) = DOT11_PACKET_TYPE_MULTICAST_CTRL
   table(3, 1) = "DOT11_PACKET_TYPE_MULTICAST_CTRL"
   
   table(4, 0) = DOT11_PACKET_TYPE_MULTICAST_MGMT
   table(4, 1) = "DOT11_PACKET_TYPE_MULTICAST_MGMT"
   
   table(5, 0) = DOT11_PACKET_TYPE_MULTICAST_DATA
   table(5, 1) = "DOT11_PACKET_TYPE_MULTICAST_DATA"
   
   table(6, 0) = DOT11_PACKET_TYPE_BROADCAST_CTRL
   table(6, 1) = "DOT11_PACKET_TYPE_BROADCAST_CTRL"
   
   table(7, 0) = DOT11_PACKET_TYPE_BROADCAST_MGMT
   table(7, 1) = "DOT11_PACKET_TYPE_BROADCAST_MGMT"
   
   table(8, 0) = DOT11_PACKET_TYPE_BROADCAST_DATA
   table(8, 1) = "DOT11_PACKET_TYPE_BROADCAST_DATA"
   
   table(9, 0) = DOT11_PACKET_TYPE_PROMISCUOUS_CTRL
   table(9, 1) = "DOT11_PACKET_TYPE_PROMISCUOUS_CTRL"
   
   table(10, 0) = DOT11_PACKET_TYPE_PROMISCUOUS_MGMT
   table(10, 1) = "DOT11_PACKET_TYPE_PROMISCUOUS_MGMT"
   
   table(11, 0) = DOT11_PACKET_TYPE_PROMISCUOUS_DATA
   table(11, 1) = "DOT11_PACKET_TYPE_PROMISCUOUS_DATA"
   
   table(12, 0) = DOT11_PACKET_TYPE_ALL_MULTICAST_CTRL
   table(12, 1) = "DOT11_PACKET_TYPE_ALL_MULTICAST_CTRL"
   
   table(13, 0) = DOT11_PACKET_TYPE_ALL_MULTICAST_MGMT
   table(13, 1) = "DOT11_PACKET_TYPE_ALL_MULTICAST_MGMT"
   
   table(14, 0) = DOT11_PACKET_TYPE_ALL_MULTICAST_DATA
   table(14, 1) = "DOT11_PACKET_TYPE_ALL_MULTICAST_DATA"
      
   For index = 0 To UBound(table)
      If(table(index, 0) = filter) Then
         vbDot11PacketFilterToString = "(PacketFilter = " & table(index, 1) & ")"
         Exit Function
      End If
   Next
   
   vbDot11PacketFilterToString = "(PacketFilter = Unknown (" & Hex(filter) & ")"
    
End Function

'================================================================================================='
Public Function vbDot11BSSTypeFriendlyName(byval bssType)
Dim bssTypeList(4)
   
   bssTypeList(0) = "N\A"
   bssTypeList(1) = "INFRASTRUCTURE"
   bssTypeList(2) = "IBSS"
   bssTypeList(3) = "ANY"
      
   vbDot11BSSTypeFriendlyName = bssTypeList(bssType)
   
End Function

'================================================================================================='
Public Function vbDot11StateFriendlyName(byval state)
Dim index   : index = 0
Dim stateTable(3,2)
   
   stateTable(0, 0) = N11_STATE_UNKNOWN
   stateTable(0, 1) = "UNKNOWN"
   
   stateTable(1, 0) = N11_STATE_INIT
   stateTable(1, 1) = "INIT"
   
   stateTable(2, 0) = N11_STATE_OP
   stateTable(2, 1) = "OP"
      
   For index = 0 To UBound(stateTable)
      If(stateTable(index, 0) = state) Then
         vbDot11StateFriendlyName = stateTable(index, 1)
         Exit Function
      End If
   Next
   
   vbDot11StateFriendlyName = "Unknown (" & Hex(state) & ")"
    
End Function

'================================================================================================='
Public Function vbDot11PHYTypeFriendlyName(byval phyType)
Dim phyTypeList(6)
   
   phyTypeList(0) = "Unknown"
   phyTypeList(1) = "FHSS"
   phyTypeList(2) = "DSSS"
   phyTypeList(3) = "IRBASEBAND"
   phyTypeList(4) = "OFDM"
   phyTypeList(5) = "HRDSSS"
   
   vbDot11PHYTypeFriendlyName = phyTypeList(phyType)
   
End Function

'================================================================================================='
Public Function vbDot11OperationModeFriendlyName(byval mode)
Dim index   : index = 0
Dim opModeTable(3,2)
   
   opModeTable(0, 0) = DOT11_OPERATION_MODE_AP
   opModeTable(0, 1) = "AP"
   
   opModeTable(1, 0) = DOT11_OPERATION_MODE_STATION
   opModeTable(1, 1) = "STATION"
   
   opModeTable(2, 0) = DOT11_OPERATION_MODE_UNKNOWN
   opModeTable(3, 1) = "UNKNOWN"
   
   For index = 0 To UBound(opModeTable)
      If(opModeTable(index, 0) = mode) Then
         vbDot11OperationModeFriendlyName = opModeTable(index, 1)
         Exit Function
      End If
   Next
   
   vbDot11OperationModeFriendlyName = "Unknown (" & Hex(mode) & ")"
    
End Function

'================================================================================================='
Public Function vbDot11StartAP()
Dim shell      : Set shell = CreateObject("WScript.Shell")
Dim result     : result    = False
Dim command    : command   = ""
Dim commands   : commands  = Empty

If(gIMTestsEnabled = 0) Then
   vbDot11StartAP = True
   Exit Function
End If

If(gIMAdhoc = 0) Then
   commands  = Array("-api:SetDot11CurrentOpMode -OpMode:2",                                                             _
                     "-api:SetDot11DSSSCurChannel -DSSSCurChannel:11",                                                   _
                     "-api:SetDot11DesiredSSID -DesiredSSID:NDTEST_N11_TEST_AP",                                         _  
                     "-api:SetDot118021xState -8021xState:0",                                                            _
                     "-api:SetDot11AuthAlgoList -NumberOfEntries:1 -AuthAlgoIndex_0:0 -AuthAlgo_0:1 -AuthAlgoEnabled:1", _
                     "-api:SetDot11PrivacyInvoked -PrivacyInvoked:0")
Else
   commands  = Array("-api:SetDot11CurrentOpMode -OpMode:1",                                                             _
                     "-api:SetDot11DesiredBSSType -BSSType:2",                                                           _
                     "-api:SetDot118021xState -8021xState:0",                                                            _
                     "-api:SetDot11DSSSCurChannel -DSSSCurChannel:11",                                                    _
                     "-api:SetDot11PrivacyInvoked -PrivacyInvoked:0",                                                    _
                     "-api:SetDot11DesiredSSID -DesiredSSID:NDTEST_N11_TEST_ADHOC",                                      _  
                     "-api:SetDot11Associate") 
End If

   vbDot11StartAP = False
  
   For Each command In Commands
      oLog.Write("Command: " & command)
      result = shell.Run("c:\softap.exe " & command, 1, True)
      If(result <> 0) Then
         oLog.Failed "command: " & command & " failed (Result: " & result & ")", 88888
         Exit Function
      End If
      WScript.Sleep(500)
   Next
  
   vbDot11StartAP = True
   
End Function

'================================================================================================='
Public Function vbDot11JoinAP()
Dim shell      : Set shell = CreateObject("WScript.Shell")
Dim result     : result    = False
Dim command    : command   = ""
Dim commands   : commands  = Empty
Dim commands2  : commands2 = Empty

If(gIMTestsEnabled = 0) Then
   vbDot11StartAP = True
   Exit Function
End If

If(gIMAdhoc = 0) Then
   commands2  = Array("-api:SetDot11CurrentOpMode -OpMode:1",                                                             _
                      "-api:SetDot11DesiredBSSType -BSSType:1",                                                           _
                      "-api:SetDot118021xState -8021xState:0",                                                            _
                      "-api:PerformDot11ScanRequest -bsstype:1 -bssid:00-00-00-00-00-00 -scantype:1")
   
   For Each command In commands2
      oLog.Write("Command: " & command)
      result = shell.Run("c:\softap.exe " & command, 1, True)
      If(result <> 0) Then
         oLog.Failed "command: " & command & " failed (Result: " & result & ")", 88888
         Exit Function
      End If
      WScript.Sleep(500)
   Next
   
   WScript.Sleep(2000)
   
   commands  = Array("-api:SetDot11DSSSCurChannel -DSSSCurChannel:11",                                                   _
                     "-api:SetDot11PrivacyInvoked -PrivacyInvoked:0",                                                    _
                     "-api:SetDot11DesiredSSID -DesiredSSID:NDTEST_N11_TEST_AP",                                         _  
                     "-api:SetDot11Associate")
Else
   commands  = Array("-api:SetDot11CurrentOpMode -OpMode:1",                                                             _
                     "-api:SetDot11DesiredBSSType -BSSType:2",                                                           _
                     "-api:SetDot118021xState -8021xState:0",                                                            _
                     "-api:SetDot11DSSSCurChannel -DSSSCurChannel:11",                                                   _
                     "-api:SetDot11PrivacyInvoked -PrivacyInvoked:0",                                                    _
                     "-api:SetDot11DesiredSSID -DesiredSSID:NDTEST_N11_TEST_ADHOC",                                      _  
                     "-api:SetDot11Associate") 
End If
                                
   vbDot11JoinAP = False
                        
   For Each command In Commands
      oLog.Write("Command: " & command)
      result = shell.Run("c:\softap.exe " & command, 1, True)
      If(result <> 0) Then
         oLog.Failed "command: " & command & " failed (Result: " & result & ")", 88888
         Exit Function
      End If
      WScript.Sleep(500)
   Next
   
   WScript.Sleep(3000)
   
   vbDot11JoinAP = True
   

End Function

'================================================================================================='
Public Function vbDot11Disassociate()
Dim shell      : Set shell = CreateObject("WScript.Shell")
Dim result     : result    = False
Dim command    : command   = ""
Dim commands   : commands  = Empty

If(gIMTestsEnabled = 0) Then
   vbDot11StartAP = True
   Exit Function
End If

'If(gIMAdhoc = False) Then
   commands  = Array("-api:SetDot11Disassociate -aid:0 -peermacaddress:00-00-00-00-00-00 -reason:0")
'Else
'   Exit Function
'End If
                                
   vbDot11Disassociate = False
                        
   For Each command In Commands
      oLog.Write("Command: " & command)
      result = shell.Run("c:\softap.exe " & command, 1, True)
      If(result <> 0) Then
         oLog.Failed "command: " & command & " failed (Result: " & result & ")", 88888
         Exit Function
      End If
   Next
   
   WScript.Sleep(1000)
   
   vbDot11Disassociate = True
   

End Function

'================================================================================================='
Public Function vbDot11FragmentationThreshold(byval threshold)
Dim shell      : Set shell = CreateObject("WScript.Shell")
Dim result     : result    = False
Dim arguments  : arguments = ""

   If(gIMTestsEnabled = 0) Then
      vbDot11StartAP = True
      Exit Function
   End If
  
   arguments  = "-fragmentationthreshold:" & CStr(threshold)
    
   result = shell.Run("c:\softap.exe -api:setdot11fragmentationthreshold " & arguments, 1, True)
   If(result <> 0) Then
      oLog.Failed "command fragmentationthreshold failed (Result: " & result & ")", 88888
      Exit Function
   End If
      
   vbDot11FragmentationThreshold = True
   

End Function

'================================================================================================='
Public Function vbDot11PowerMgmtMode(byval mode, byval level)
Dim shell      : Set shell = CreateObject("WScript.Shell")
Dim result     : result    = False
Dim arguments  : arguments = ""

   If(gIMTestsEnabled = 0) Then
      vbDot11StartAP = True
      Exit Function
   End If
   
   arguments  = "-powermode:" & CStr(mode) & " -powersavelevel:" & CStr(level) & " -receivedtims:1"
    
   result = shell.Run("c:\softap.exe -api:setdot11powermgmtmode " & arguments, 1, True)
   If(result <> 0) Then
      oLog.Failed "command setdot11powermgmtmode failed (Result: " & result & ")", 88888
      Exit Function
   End If
      
   vbDot11PowerMgmtMode = True
   

End Function

'<!-- CRC = 0xa0fc2aa1 --->