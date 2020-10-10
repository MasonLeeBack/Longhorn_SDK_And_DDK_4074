'<!-- CRC = 0xab9eb05f -->
'================================================================================================='
Function vbWlan2xSetup(byref oTestOpen, byref oSupportOpen)
Dim bRetval       : bRetval         = False
Dim nNdisStatus   : nNdisStatus     = NDIS_STATUS_FAILURE
   
   vbWlan2xSetup = False

   nNdisStatus = oTestOpen.vbAssociateEx(Ndis802_11Infrastructure,   _
                                         Ndis802_11AuthModeOpen,     _
                                         NDTESTAP1,                  _
                                         &H80000000&,                _
                                         NDTEST_WEP_KEY,             _
                                         Ndis802_11WEPEnabled,       _
                                         True)            
   If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
      oLog.Write "Failed to associate with " & NDTESTAP1 & "!" & vbGetNdisStatus(nNdisStatus)
      Exit Function
   End If	

   nNdisStatus = oSupportOpen.vbAssociateEx(Ndis802_11Infrastructure,   _
                                            Ndis802_11AuthModeOpen,     _
                                            NDTESTAP2,                  _
                                            &H80000000&,                _
                                            NDTEST_WEP_KEY,             _
                                            Ndis802_11WEPEnabled,       _
                                            True)            
   If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
      oLog.Failed "Failed to associate with " & NDTESTAP2 & "!" & vbGetNdisStatus(nNdisStatus), 88888
      Exit Function
   End If	

   vbWlan2xSetup = True                  
       
End Function

'================================================================================================='
Function vbWlan1xSetup(byref oTest)
Dim oTestCard     : Set oTestCard   = New CWlan
Dim bRetval       : bRetval         = False
Dim nNdisStatus   : nNdisStatus     = NDIS_STATUS_FAILURE
   
   vbWlan1xSetup = False
   
   Set oOpen = oTest.CreateOpen 
   oTestCard.vbAdapterOpen = oOpen

   nNdisStatus = oTestCard.vbAssociateEx(Ndis802_11Infrastructure,   _
                                         Ndis802_11AuthModeOpen,     _
                                         oAP1Config.vbSsid,          _
                                         &H80000000&,                _
                                         oAP1Config.vbWEP40BitKey,   _
                                         Ndis802_11WEPEnabled,       _
                                         True)            
   If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
      oLog.Failed "Failed to associate with " & oAP1Config.vbSsid & "!" & vbGetNdisStatus(nNdisStatus), 88888
      oOpen.Close()
      Exit Function
   End If	
   
   oOpen.Close()
   
   vbWlan1xSetup = True
    
End Function

'================================================================================================='
Function vbInitializeGlobalsForWirelessLan()

End Function

'================================================================================================='
Function vbAssociateWep(byref oOpen, byval sSsid)
Dim oUlong        : Set oUlong         = Nothing
Dim oKey          : Set oKey           = Nothing
Dim oSsid         : Set oSsid          = Nothing
Dim bRetval       : bRetval            = False
Dim nNdisStatus   : nNdisStatus        = GENERIC_FAILURE
Dim nBytesWritten : nBytesWritten      = CLng(0)
Dim nBytesNeeded  : nBytesNeeded       = CLng(0)
Dim nStatus       : nStatus            = 0
Dim nEndTime      : nEndTime           = 0
Dim nStartTime    : nStartTime         = Timer
Dim nTimeout      : nTimeout           = 0

   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbAssociateWep" & CWLAN_PRINT_END & vbCrLf
   
   vbInitializeGlobalsForWirelessLan()
   
   vbAssociate = GENERIC_FAILURE
   
   Do
   
      Set oUlong = CreateObject("StructRep.SO_ULONG.1")
      If(oUlong Is Nothing) Then
         oLog.Write "vbAssociateWep(): Failed to create ULONG structure object"
         Exit Do
      End If
      
      Set oKey = CreateObject("StructRep.SO_NDIS_802_11_WEP.1")
      If(oKey Is Nothing) Then
         oLog.Write "vbAssociateWep(): Failed to create NDIS_802_11_WEP structure object"
         Exit Do
      End If
      
      Set oSsid = CreateObject("StructRep.SO_NDIS_802_11_SSID.1")
      If(oSsid Is Nothing) Then
         oLog.Write "vbAssociateWep(): Failed to create NDIS_802_11_SSID structure object"
         Exit Function
      End If
           	
      oUlong.Ulong = Ndis802_11Infrastructure
         				
      bRetval = oOpen.COMOpen.NdisRequest2(OID_802_11_INFRASTRUCTURE_MODE, oUlong, CWLAN_OID_SET, nNdisStatus)
      If(bRetval = False) Then
         oLog.Write "vbAssociateWep(): NdisRequest2() failed to set OID_802_11_INFRASTRUCTURE_MODE"
         Exit Do
      ElseIf(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If		
      
      oUlong.Ulong = Ndis802_11AuthModeOpen
         				
      bRetval = oOpen.COMOpen.NdisRequest2(OID_802_11_AUTHENTICATION_MODE, oUlong, CWLAN_OID_SET, nNdisStatus)
      If(bRetval = False) Then
         oLog.Write "vbAssociateWep(): NdisRequest2() failed to set OID_802_11_AUTHENTICATION_MODE"
         Exit Do
      ElseIf(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If	
      
      oKey.KeyIndex     = &H80000000&
 	   oKey.KeyMaterial  = NDTEST_WEP_KEY
 	   
 	   bRetval = oOpen.COMOpen.NdisRequest2(OID_802_11_ADD_WEP, oKey, CWLAN_OID_SET, nNdisStatus)
      If(bRetval = False) Then
         oLog.Write "vbAssociateWep(): NdisRequest2() failed to set OID_802_11_ADD_WEP"
         Exit Do
      ElseIf(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If		
      
      oUlong.Ulong = Ndis802_11WEPEnabled
            
      bRetval = oOpen.COMOpen.NdisRequest2(OID_802_11_WEP_STATUS, oUlong, CWLAN_OID_SET, nNdisStatus)
      If(bRetval = False) Then
         oLog.Write "vbAssociateWep(): NdisRequest2() failed to set OID_802_11_WEP_STATUS"
         Exit Do
      ElseIf(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If		
      
      oSsid.Ssid = sSsid
      
      bRetval = oOpen.COMOpen.NdisRequest2(OID_802_11_SSID, oSsid, CWLAN_OID_SET, nNdisStatus)
      If(bRetval = False) Then
         oLog.Write "vbAssociateWep(): NdisRequest2() failed to set OID_802_11_SSID"
         Exit Do
      ElseIf(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         Exit Do
      End If		
      
      Do 
        
         WScript.Sleep(1000)
         nEndTime = Timer
         nTimeout = nEndTime - nStartTime
                  
         oLog.MaskWrite()
         bRetval = oOpen.COMOpen.NdisRequest(OID_GEN_MEDIA_CONNECT_STATUS, _
                                             nStatus,                      _
                                             4,                            _
                                             REQUEST_QUERY_INFO,           _
                                             nBytesWritten,                _
                                             nBytesNeeded,                 _
                                             nNdisStatus)
         If(bRetval = False) Then
            oLog.Write "vbAssociateWep(): NdisRequest2() failed to query OID_GEN_MEDIA_CONNECT_STATUS"
            oLog.UnMaskWrite
            Exit Do
         ElseIf(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
            oLog.UnMaskWrite
            Exit Do
         End If	
         oLog.UnMaskWrite
         
         If(nStatus = CWLAN_MEDIA_CONNECTED) Then
            Exit Do
         End If
         
         If(nTimeout > (WLAN_SSID_TIMEOUT / 1000)) Then
            oLog.Write "vbAssociateWep(): Device not connected within " & WLAN_SSID_TIMEOUT / 1000 & " seconds"
            nNdisStatus = GENERIC_FAILURE
            Exit Do
         End If
         
      Loop While(True)
      
      If(oOpen.COMOpen.GetEvents() = False) Then
         oLog.Write "vbAssociateWep(): Failed to get events"
         nNdisStatus = GENERIC_FAILURE
         Exit Do
      End If
      
   Loop While(False)
      
   vbAssociateWep = nNdisStatus
   
   oLog.Write vbCrLf & "<b>" & vbGetNdisStatus(nNdisStatus) & "</b>" & vbCrLf
      
End Function

'================================================================================================='
Function vbVerifyWlanConfiguration()
Dim oTestCard           : Set oTestCard      = New CWlanBase
Dim oShell              : Set oShell         = CreateObject("WScript.Shell")
Dim sValue              : sValue             = ""
Dim bRetval	            : bRetval	         = False
Dim nNdisStatus         : nNdisStatus        = NDIS_STATUS_FAILURE
Dim nIndex              : nIndex             = 0 
Dim bVerified           : bVerified          = False
Dim nTestAdapterIndex   : nTestAdapterIndex  = 0

   vbVerifyWlanConfiguration = False
   
   ' Verifying the configuration can be overridden in the regiestry,
   ' so check to see if we should continue
   sValue = oShell.RegRead(WLAN_REGISTRY_KEY & "RunConfigCheck")
   If(sValue = "No") Then
      vbVerifyWlanConfiguration = True
      Exit Function
   End If
      
   nTestAdapterIndex = GetTestAdapterIndex(oNDInfo.AdapterList, 0)
              
   Do
      
      oNDTSession("WlanConfigVerified") = False
      
      bRetval = oTestCard.vbCreateAdapter(nTestAdapterIndex)
      If(bRetval = False) Then
         oLog.Failed "Failed to create device!", 88888
         Exit Do
      End If
      
      nNdisStatus = oTestCard.vbWaitForSSID(NDTESTAP1, 15)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Unable to find " & NDTESTAP1 & " in BSSID_LIST!" & vbGetNdisStatus(nNdisStatus)
         Exit Do
      End If	 
      
      nNdisStatus = oTestCard.vbWaitForSSID(NDTESTAP2, 15)
      If(nNdisStatus <> NDIS_STATUS_SUCCESS) Then
         oLog.Write "Unable to find " & NDTESTAP2 & " in BSSID_LIST!" & vbGetNdisStatus(nNdisStatus)
         Exit Do
      End If	
                                
      vbVerifyWlanConfiguration           = True 
      oNDTSession("WlanConfigVerified")   = True
      
   Loop While(False)
                 
   Set oTestCard = Nothing
          
End Function

'================================================================================================='
Function vbConvertToRate(byval nVal)
Dim bBasicRateSet : bBasicRateSet   = False
Dim nValue        : nValue          = nVal AND &H80&
   
   If(nValue = &H80&) Then
      bBasicRateSet = True
      nVal = nVal XOR &H80&
      vbConvertToRate = nVal / 2
   Else
      vbConvertToRate = nVal / 2
   End If
   
End Function

'================================================================================================='
Function vbCheckForRegistryChange()
Dim oShell  : Set oShell   = CreateObject("WScript.Shell")
Dim sValue  : sValue       = ""

sValue = oShell.RegRead(WLAN_REGISTRY_KEY & "NDTEST_WPA_AP1")
If(sValue <> "") Then
   NDTEST_WPA_AP1 = sValue
End If

sValue = oShell.RegRead(WLAN_REGISTRY_KEY & "NDTEST_WPA_AP2")
If(sValue <> "") Then
   NDTEST_WPA_AP2 = sValue
End If

sValue = oShell.RegRead(WLAN_REGISTRY_KEY & "NDTEST_WPA_IBSS")
If(sValue <> "") Then
   NDTEST_WPA_IBSS = sValue
End If
   
End Function

'=============================================================================================='
Function vbPrintAssociationInformation(byref oAssocInfo)
Dim oVarIE  : Set oVarIE   = Nothing
Dim oIE     : Set oIE      = Nothing
Dim nCount  : nCount       = 0
Dim nIndex  : nIndex       = 0
Dim sByte   : sByte        = ""
Dim aArr
   
   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbPrintAssociationInformation" & CWLAN_PRINT_END
   
   oLog.Write "---------- NDIS_802_11_ASSOCIATION_INFORMATION -------------"  
   oLog.Write "->Length:                           " & oAssocInfo.Length
   oLog.Write "->AvailableRequestFixedIEs:         " & oAssocInfo.AvailableRequestFixedIEs
   If(oAssocInfo.AvailableRequestFixedIEs And NDIS_802_11_AI_REQFI_CAPABILITIES) Then
      oLog.Write "->RequestFixedIEs.Capabilities:     " & oAssocInfo.ReqFixedCapabilities
   End If   
   If(oAssocInfo.AvailableRequestFixedIEs And NDIS_802_11_AI_REQFI_LISTENINTERVAL) Then
      oLog.Write "->RequestFixedIEs.ListenInterval:   " & oAssocInfo.ReqFixedListenInterval
   End If          
   oLog.Write "->RequestIELength:                  " & oAssocInfo.RequestIELength
   oLog.Write "->OffsetRequestIEs:                 " & oAssocInfo.OffsetRequestIEs
   oLog.Write "->AvailableResponseFixedIEs:        " & oAssocInfo.AvailableResponseFixedIEs 
   If(oAssocInfo.AvailableResponseFixedIEs And NDIS_802_11_AI_RESFI_CAPABILITIES) Then
      oLog.Write "->RequestFixedIEs.Capabilities:     " & oAssocInfo.ResFixedCapabilities
   End If   
   If(oAssocInfo.AvailableResponseFixedIEs And NDIS_802_11_AI_RESFI_STATUSCODE) Then
      oLog.Write "->RequestFixedIEs.StatusCode:       " & oAssocInfo.ResFixedStatusCode
   End If 
   If(oAssocInfo.AvailableResponseFixedIEs And NDIS_802_11_AI_RESFI_ASSOCIATIONID) Then
      oLog.Write "->RequestFixedIEs.AssociationID:    " & oAssocInfo.ResFixedAssociationID
   End If   
   oLog.Write "->ResponseIELength:                 " & oAssocInfo.ResponseIELength
   oLog.Write "->OffsetResponseIEs:                " & oAssocInfo.OffsetResponseIEs
   oLog.Write "->ResponseIELength:                 " & oAssocInfo.ResponseIELength
   oLog.Write "->OffsetResponseIEs:                " & oAssocInfo.OffsetResponseIEs
   oLog.Write "------------------------------------------------------------"  
   
   If(oAssocInfo.RequestIELength = 0) Then
      Exit Function
   End If
   
   nCount = 0
      
   Do
      
      Set oVarIE = oAssocInfo.GetRequestIE(nCount)  
      If(oVarIE Is Nothing) Then
         Exit Do
      End If   
      oLog.Write "--------------------- Request IE ---------------------------"   
      oLog.Write "Element ID:                   0x" & Hex(oVarIE.ElementID)
      oLog.Write "Length:                       " & oVarIE.Length
      Select Case oVarIE.ElementID
         
      Case 0:
         Set oIE = oVarIE.data
         If(IsObject(oIE)) Then
            oLog.Write "SSID:                         " & oIE.Ssid
         End If
            
       Case 1:
         Set oIE = oVarIE.data
         If(IsObject(oIE)) Then
            sByte = ""
            aArr  = Empty
            aArr = oIE.SupportedRates
            For nIndex = LBound(aArr) To UBound(aArr)
               sByte = sByte & " " & Hex(aArr(nIndex))
            Next
            oLog.Write "Supported Rates:             " & sByte
         End If
            
      Case 221:
         Set oIE = oVarIE.data
         If(IsObject(oIE)) Then
            sByte = ""
            aArr  = Empty
            aArr = oIE.WPA
            For nIndex = LBound(aArr) To UBound(aArr)
               sByte = sByte & " " & Hex(aArr(nIndex))
            Next
            oLog.Write "WPA:                         " & sByte
         End If
            
      End Select
      oLog.Write "------------------------------------------------------------"
      nCount = nCount + 1
         
   Loop While(True)
      
   nCount = 0
   
   If(oAssocInfo.ResponseIELength = 0) Then
      Exit Function
   End If
   
   Do
      
      Set oVarIE = oAssocInfo.GetResponseIE(nCount)  
      If(oVarIE Is Nothing) Then
         Exit Do
      End If   
      oLog.Write "--------------------- Response IE --------------------------"   
      oLog.Write "Element ID:                   0x" & Hex(oVarIE.ElementID)
      oLog.Write "Length:                       " & oVarIE.Length
      Select Case oVarIE.ElementID
         
      Case 0:
         Set oIE = oVarIE.data
         If(IsObject(oIE)) Then
            oLog.Write "SSID:                         " & oIE.Ssid
         End If
            
       Case 1:
         Set oIE = oVarIE.data
         If(IsObject(oIE)) Then
            sByte = ""
            aArr  = Empty
            aArr = oIE.SupportedRates
            For nIndex = LBound(aArr) To UBound(aArr)
               sByte = sByte & " " & Hex(aArr(nIndex))
            Next
            oLog.Write "Supported Rates:             " & sByte
         End If
            
      Case 221:
         Set oIE = oVarIE.data
         If(IsObject(oIE)) Then
            sByte = ""
            aArr  = Empty
            aArr = oIE.WPA
            For nIndex = LBound(aArr) To UBound(aArr)
               sByte = sByte & " " & Hex(aArr(nIndex))
            Next
            oLog.Write "WPA:                         " & sByte
         End If
            
      End Select
      oLog.Write "------------------------------------------------------------"
      nCount = nCount + 1
         
   Loop While(True)
   
End Function

'================================================================================================='
Function vbPrintConfiguation(byref oConfiguration, byref oConfigurationFH)
   
   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbPrintConfiguation" & CWLAN_PRINT_END
   
   oLog.Write "---------------- NDIS_802_11_CONFIGURATION ----------------"
   oLog.Write "Length:              " & oConfiguration.Length
   oLog.Write "BeaconPeriod:        " & oConfiguration.BeaconPeriod & " Kusec"
   oLog.Write "ATIMWindow:          " & oConfiguration.ATIMWindow   & " Kusec"
   oLog.Write "DSConfig:            " & oConfiguration.DSConfig     & " kHz"
   oLog.Write "  CONFIGURATION_FH-> "
   oLog.Write "     Length:         " & oConfigurationFH.Length
   oLog.Write "     HopPattern:     " & oConfigurationFH.HopPattern
   oLog.Write "     HopSet:         " & oConfigurationFH.HopSet
   oLog.Write "     DwellTime:      " & oConfigurationFH.DwellTime  & " Kusec"
      
End Function

'=================================================================================================='
Function vbPrintBssidList(byref oBssidList)
Dim oNull         : Set oNull       = Nothing
Dim oBssid        : Set oBssid      = Nothing
Dim oConfig       : Set oConfig     = Nothing
Dim oConfigFH     : Set oConfigFH   = Nothing
Dim bRetval       : bRetval         = False
Dim nNdisStatus   : nNdisStatus     = GENERIC_FAILURE
Dim nIndex        : nIndex          = 0
Dim nCount        : nCount          = 0
Dim nRate         : nRate           = 0
Dim sByte         : sByte           = ""
Dim i             : i               = 0
Dim aSuppRates
Dim aBssid
   
   oLog.Write vbCrLf & CWLAN_PRINT_BEGIN & "vbPrintBssidList" & CWLAN_PRINT_END
   
   vbBssidListScan = nNdisStatus
   
   If(oBssidList Is Nothing) Then
      oLog.Write "vbPrintBssidList(): oBssidList was equal to Nothing!"
      Exit Function
   End If
   
   For nIndex = 0 To oBssidList.NumberOfItems - 1
      
      Do
      
         Set oBssid = oBssidList.Bssid(nIndex)
         If(oBssid Is Nothing) Then
            oLog.Write "vbPrintBssidList(): Failed to get BSSID list Item!"
            Exit Do
         End If
                 
         Set oConfig       = oBssid.Configuration
         Set oConfigFH     = oConfig.FHConfig
                        
         oLog.Write "------------------------------ NDIS_WLAN_BSSID_EX (Item " & nIndex & ") ------------------------------"
         oLog.Write "Length:                          " & oBssid.Length
         oLog.Write "Bssid:                           " & oBssid.MacAddress
         oLog.Write "Ssid:                            " & oBssid.Ssid
         oLog.Write "Privacy:                         " & oBssid.Privacy
         oLog.Write "Rssi:                            " & oBssid.Rssi & " dBm"
         
         If(oBssid.NetworkTypeInUse > UBound(g_aNetworkTypesSupported)) Then
            oLog.Write "NetworkTypeInUse:                " & oBssid.NetworkTypeInUse & " (Unknown)"
         Else
            oLog.Write "NetworkTypeInUse:                " & oBssid.NetworkTypeInUse & " (" & g_aNetworkTypesSupported(oBssid.NetworkTypeInUse) & ")"
         End If
         
         oLog.Write "NDIS_802_11_CONFIGURATION->      "
         oLog.Write "   BeaconPeriod:                 " & oConfig.BeaconPeriod & " Kusec"
         oLog.Write "   ATIMWindow:                   " & oConfig.ATIMWindow & " Kusec"
         oLog.Write "   DSConfig:                     " & oConfig.DSConfig & " kHz"
         oLog.Write "NDIS_802_11_CONFIGURATION_FH->   "
         oLog.Write "   Length:                       " & oConfigFH.Length
         oLog.Write "   HopPattern:                   " & oConfigFH.HopPattern
         oLog.Write "   HopSet:                       " & oConfigFH.HopSet
         oLog.Write "   DwellTime:                    " & oConfigFH.DwellTime & " Kusec"
         
         If(oBssid.InfrastructureMode > UBound(g_aInfrastructureMode)) Then
            oLog.Write "InfrastructureMode:              " & oBssid.InfrastructureMode & " (Unknown)"
         Else
            oLog.Write "InfrastructureMode:              " & oBssid.InfrastructureMode & " (" & g_aInfrastructureMode(oBssid.InfrastructureMode) & ")"
         End If
         
         aSuppRates  = Empty
         sByte       = ""
         aSuppRates = oBssid.SupportedRates
         If(IsArray(aSuppRates) = False) Then
            oLog.Write "vbPrintBssidList(): Failed to get supported rates"  
         Else
            sByte = ""
            For i = LBound(aSuppRates) To UBound(aSuppRates)
               sByte = sByte & " " & Hex(aSuppRates(i))
            Next     
            oLog.Write "SupportedRates:                 " & sByte
         End If
         
         If(oBssid.IELength > 0) Then
            
            Dim oVarIE     : Set oVarIE   = Nothing
            Dim oFixIE     : Set oFixIE   = Nothing
            Dim oVarData   : Set oVarData = Nothing
            Dim nIECount   : nIECount     = 0
                                      
            oLog.Write "IELength:                        " & oBssid.IELength
            
            Do
                   
               Set oFixIE = oBssid.FixedIEs
               If(oFixIE Is Nothing) Then
                  oLog.Write "vbPrintBssidList(): Failed to get Fixed IEs"
                  Exit Do
               End If
               
               oLog.Write "NDIS_802_11_FIXED_IEs->          "
               oLog.Write "   Timestamp:                    " '& oFixIE.Timestamp
               oLog.Write "   BeaconInterval:               " & oFixIE.BeaconInterval
               oLog.Write "   Capabilities:                 0x" & Hex(oFixIE.Capabilities)
               
               ' These bits are defined in the IEEE 802.11 spec
               If((oFixIE.Capabilities AND &H1&) = &H1&) Then
               oLog.Write "    ESS:                         1"
               Else
               oLog.Write "    ESS:                         0"
               End If
               If((oFixIE.Capabilities AND &H2&) = &H2&) Then
               oLog.Write "    IBSS:                        1"
               Else
               oLog.Write "    IBSS:                        0"
               End If
               If((oFixIE.Capabilities AND &H4&) = &H4&) Then
               oLog.Write "    CF Pollable:                 1"
               Else
               oLog.Write "    CF Pollable:                 0"
               End If
               If((oFixIE.Capabilities AND &H8&) = &H8&) Then
               oLog.Write "    CF Poll Request:             1"
               Else
               oLog.Write "    CF Poll Request:             0"
               End If
               If((oFixIE.Capabilities AND &H10&) = &H10&) Then
               oLog.Write "    Privacy:                     1"
               Else
               oLog.Write "    Privacy:                     0"     
               End If   
                                          
            Loop While(False)
            
            Do    
                  
               Set oVarIE = oBssid.VariableIEs(nIECount)      
               If(oVarIE Is Nothing) Then
                  ' No more variable IEs
                  Exit Do
               End If
               
               nIECount = nIECount + 1
                                                                         
               oLog.Write "NDIS_802_11_VARIABLE_IEs->       "   
               oLog.Write "ElementID:                       " & oVarIE.ElementID
               oLog.Write "Length:                          " & oVarIE.Length
                     
               Do
               
                  Set oVarData = oVarIE.data 
                  If(oVarData Is Nothing) Then
                     oLog.Write "vbPrintBssidList(): Failed to get variable IE data"
                     Exit Do
                  End If       
            
                  Select Case(oVarIE.ElementID)
                  
                  Case INFORMATION_ELEMENT_SSID                                   
                  oLog.Write "SSID:                            " & oVarData.Ssid 
                                 
                  Case INFORMATION_ELEMENT_SUPPORTED_RATES 
                     aSuppRates  = Empty
                     sByte       = ""
                     aSuppRates = oVarData.SupportedRates
                     If(IsArray(aSuppRates) = False) Then
                        oLog.Write "vbPrintBssidList(): Failed to get supported rates"  
                     Else
                        For i = LBound(aSuppRates) To UBound(aSuppRates)
                           sByte = sByte & " " & Hex(aSuppRates(i))
                        Next     
                        oLog.Write "SupportedRates:                 " & sByte
                     End If      
                                                                                              
                  Case INFORMATION_ELEMENT_FH_PARAMETER_SET
                     oLog.Write "DwellTime:                       " & oVarData.DwellTime
                     oLog.Write "HopSet:                          " & oVarData.HopSet
                     oLog.Write "HopPattern:                      " & oVarData.HopPattern
                     oLog.Write "HopIndex:                        " & oVarData.HopIndex
                  
                  Case INFORMATION_ELEMENT_DS_PARAMETER_SET 
                     oLog.Write "CurrentChannelNumber:            " & oVarData.CurrentChannelNumber
                  
                  Case INFORMATION_ELEMENT_CF_PARAMETER_SET
                     oLog.Write "CFPCount:                        " & oVarData.CFPCount
                     oLog.Write "CFPPeriod:                       " & oVarData.CFPPeriod
                     oLog.Write "CFPMaxDuration:                  " & oVarData.CFPMaxDuration
                     oLog.Write "CFPDurRemaining:                 " & oVarData.CFPDurRemaining
                                 
                  Case INFORMATION_ELEMENT_TIM
                     oLog.Write "DTIMCount:                       " & oVarData.DTIMCount
                     oLog.Write "DTIMPeriod:                      " & oVarData.DTIMPeriod
                     oLog.Write "BitmapControl:                   " & oVarData.BitmapControl
                     oLog.Write "PartialVirtualBitmap:            " & oVarData.PartialVirtualBitmap
                  
                  Case INFORMATION_ELEMENT_IBSS_PARAMETER_SET
                     oLog.Write "ATIMWindow:                      " & oVarData.ATIMWindow
                                                                
                  End Select
               
               Loop While(False)
                                 
            Loop While(True)        
                        
         End If
         
      Loop While(False)            
   
   Next                   	
                             		
   vbBssidListScan = nNdisStatus
		
End Function
'<!-- CRC = 0x4b855565 --->