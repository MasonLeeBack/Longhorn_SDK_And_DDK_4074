'================================================================================================='
' This script contains all the WLAN related library functions
'
' Author:
' - David Harding
'
' Required Includes:
'  - 
'================================================================================================='
Option Explicit

Const WLAN_REGISTRY_KEY = "HKEY_CURRENT_USER\Software\Microsoft\NDTEST\WLAN\"

Dim WLAN_WEP_AP1        : WLAN_WEP_AP1       = "NDTEST_WEP_AP1"
Dim WLAN_WEP_AP2        : WLAN_WEP_AP2       = "NDTEST_WEP_AP2"
Dim WLAN_WEP_AP3        : WLAN_WEP_AP3       = "NDTEST_WEP_AP3"

Dim WLAN_WPA_AP1        : WLAN_WPA_AP1       = "NDTEST_WPA_AP1"
Dim WLAN_WPA_AP2        : WLAN_WPA_AP2       = "NDTEST_WPA_AP2"
Dim WLAN_WPA_AP3        : WLAN_WPA_AP3       = "NDTEST_WPA_AP3"

Dim WLAN_IBSS           : WLAN_IBSS          = "NDTEST_IBSS" 

vbWlanCheckRegistry()

'================================================================================================='
'/**
' This function is called to check the regestry for changes to the AP SSID's. If the user needs
' to change the SSID names in the registry this script will get the new names and update the constants.
' */
Public Function vbWlanCheckRegistry()
Dim shell   : Set shell = CreateObject("WScript.Shell")
Dim newVal  : newVal    = ""
   
   '-----------------------------------------------------------------------------------------------
   ' WLAN WEP AP's
   '-----------------------------------------------------------------------------------------------
   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_WEP_AP1")
   If(newVal <> "") Then
      WLAN_WEP_AP1 = newVal
   End If

   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_WEP_AP2")
   If(newVal <> "") Then
      WLAN_WEP_AP2 = newVal
   End If
   
   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_WEP_AP3")
   If(newVal <> "") Then
      WLAN_WEP_AP3 = newVal
   End If
   
   '-----------------------------------------------------------------------------------------------
   ' WLAN WPA AP's
   '-----------------------------------------------------------------------------------------------
   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_WPA_AP1")
   If(newVal <> "") Then
      WLAN_WPA_AP1 = newVal
   End If

   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_WPA_AP2")
   If(newVal <> "") Then
      WLAN_WPA_AP2 = newVal
   End If
   
   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_WPA_AP3")
   If(newVal <> "") Then
      WLAN_WPA_AP3 = newVal
   End If

   '-----------------------------------------------------------------------------------------------
   ' WLAN IBSS
   '-----------------------------------------------------------------------------------------------
   newVal = shell.RegRead(WLAN_REGISTRY_KEY & "WLAN_IBSS")
   If(newVal <> "") Then
      WLAN_IBSS = newVal
   End If
   
End Function

'==================================================================================================
Public Function vbCreateMACAddress(byval byte0, byval byte1, byval byte2, byval byte3, byval byte4, byval byte5)
   
   vbCreateMACAddress = Array(CByte(byte0),CByte(byte1),CByte(byte2),CByte(byte3),CByte(byte4),CByte(byte5))
   
End Function 

'==================================================================================================                     
Function vbInfrastructureModeToString(byval value)
Dim list : list = Array("Ndis802_11IBSS",                    _
                        "Ndis802_11Infrastructure",          _
                        "Ndis802_11AutoUnknown",             _
                        "Ndis802_11InfrastructureMax")
                       
   If(value > UBound(list)) Then
      vbInfrastructureModeToString = "Unknown (" & value &")"
   Else
      vbInfrastructureModeToString = list(value)
   End If
                                   
End Function

'==================================================================================================                     
Function vbAuthenticationModeToString(byval value)
Dim list : list = Array("Ndis802_11AuthModeOpen",            _
                        "Ndis802_11AuthModeShared",          _
                        "Ndis802_11AuthModeAutoSwitch",      _
                        "Ndis802_11AuthModeWPA",             _
                        "Ndis802_11AuthModeWPAPSK",          _
                        "Ndis802_11AuthModeWPANone",         _
                        "Ndis802_11AuthModeMax")
   
   If(value > UBound(list)) Then
      vbAuthenticationModeToString = "Unknown (" & value &")"
   Else
      vbAuthenticationModeToString = list(value)
   End If
                   
End Function

'==================================================================================================                     
Function vbEncryptionModeToString(byval value)
Dim list : list = Array("Ndis802_11Encryption1Enabled",      _
                        "Ndis802_11EncryptionDisabled",      _
                        "Ndis802_11Encryption1KeyAbsent",    _
                        "Ndis802_11EncryptionNotSupported",  _
                        "Ndis802_11Encryption2Enabled",      _
                        "Ndis802_11Encryption2KeyAbsent",    _
                        "Ndis802_11Encryption3Enabled",      _
                        "Ndis802_11Encryption3KeyAbsent")
                        
   If(value > UBound(list)) Then
      vbEncryptionModeToString = "Unknown (" & value &")"
   Else
      vbEncryptionModeToString = list(value)
   End If   
   
End Function

'==================================================================================================                     
Function vbNetworkTypeToString(byval value)
Dim list : list = Array("Ndis802_11FH",                      _ 
                        "Ndis802_11DS",                      _
                        "Ndis802_11OFDM5",                   _
                        "Ndis802_11OFDM24")
   
   If(value > UBound(list)) Then
      vbNetworkTypeToString = "Unknown (" & value &")"
   Else
      vbNetworkTypeToString = list(value)
   End If
                             
End Function

'==================================================================================================                     
Function vbReloadDefaultToString(byval value)
Dim list : list = Array("Ndis802_11ReloadWEPKeys")

   If(value > UBound(list)) Then
      vbReloadDefaultToString = "Unknown (" & value &")"
   Else
      vbReloadDefaultToString = list(value)
   End If                       

End Function

'==================================================================================================                     
Function vbPowerModeToString(byval value)
Dim list : list = Array("Ndis802_11PowerModeCAM",            _
                        "Ndis802_11PowerModeMAX_PSP",        _
                        "Ndis802_11PowerModeFast_PSP")
   
   If(value > UBound(list)) Then
      vbPowerModeToString = "Unknown (" & value &")"
   Else
      vbPowerModeToString = list(value)
   End If  
   
End Function

'==================================================================================================                     
Function vbPrivacyFilterToString(byval value)
Dim list : list = Array("Ndis802_11PrivFilterAcceptAll",     _
                        "Ndis802_11PrivFilter8021xWEP")
                        
   If(value > UBound(list)) Then
      vbPrivacyFilterToString = "Unknown (" & value &")"
   Else
      vbPrivacyFilterToString = list(value)
   End If  
   
End Function

'==================================================================================================                     
Function vbDeviceTypeToString(byval value)
Dim list : list = Array("WLAN_DEVICE_TYPE_802_11B",  _
                        "WLAN_DEVICE_TYPE_802_11G",  _
                        "WLAN_DEVICE_TYPE_802_11AB", _
                        "WLAN_DEVICE_TYPE_802_11AG")
                        
   If(value > UBound(list)) Then
      vbDeviceTypeToString = "UNKNOWN"
   Else
      vbDeviceTypeToString = list(value)
   End If  
   
End Function


'==================================================================================================                     
Function vbWlanGetAPList(byval deviceType)

   Select Case deviceType
      Case WLAN_DEVICE_TYPE_802_11B
         vbWlanGetAPList = Array(WLAN_WEP_AP1, WLAN_WEP_AP2)
      Case WLAN_DEVICE_TYPE_802_11G
         vbWlanGetAPList = Array(WLAN_WEP_AP1, WLAN_WEP_AP2)
      Case WLAN_DEVICE_TYPE_802_11AB
         vbWlanGetAPList = Array(WLAN_WEP_AP1, WLAN_WEP_AP2)
      Case WLAN_DEVICE_TYPE_802_11AG
         vbWlanGetAPList = Array(WLAN_WEP_AP1, WLAN_WEP_AP2, WLAN_WEP_AP2)
   End Select
   
End Function
'<!-- CRC = 0xc01bf7b4 --->