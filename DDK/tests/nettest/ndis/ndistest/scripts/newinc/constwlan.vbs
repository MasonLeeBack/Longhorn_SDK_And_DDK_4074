'<!-- CRC = 0xb6d6b6ce -->
             
Public NDISUIOAP                       : NDISUIOAP                            = "NDISUIOAP"
                                 
Public NDTEST_WPA_AP1                  : NDTEST_WPA_AP1                       = "NDTEST_WPA_AP1"
Public NDTEST_WPA_AP2                  : NDTEST_WPA_AP2                       = "NDTEST_WPA_AP2"
Public NDTEST_WPA_IBSS                 : NDTEST_WPA_IBSS                      = "NDTEST_WPA_IBSS"
Public NDTESTAP1                       : NDTESTAP1                            = "NDTESTAP1"
Public NDTESTAP2                       : NDTESTAP2                            = "NDTESTAP2"
Public NDTESTIBSS                      : NDTESTIBSS                           = "NDTESTIBSS"

Public NDTEST_WEP_KEY                  : NDTEST_WEP_KEY                       = "0123456789"
Public NDTEST_WPA_TKIP_KEY             : NDTEST_WPA_TKIP_KEY                  = "0123456789012345678901234567890123456789012345678901234567890123"
Public NDTEST_WPA_AES_KEY              : NDTEST_WPA_AES_KEY                   = "01234567890123456789012345678901"
Public NDTEST_WPA_PMK                  : NDTEST_WPA_PMK                       = "0123456789012345678901234567890123456789012345678901234567890123"

'Public MAX_NUM_NETWORKTYPEINUSE        : MAX_NUM_NETWORKTYPEINUSE             = 4
'Public MAX_NUM_AUTHENTICATIONMODE      : MAX_NUM_AUTHENTICATIONMODE           = 6
Public MAX_NUM_INFRASTRUCTUREMODE      : MAX_NUM_INFRASTRUCTUREMODE           = 4               
 
Public WLAN_SSID_TIMEOUT               : WLAN_SSID_TIMEOUT                    = 1000 * 20 ' 15 seconds
Public WLAN_BSSID_LIST_SCAN_TIMEOUT    : WLAN_BSSID_LIST_SCAN_TIMEOUT         = 1000 * 6  ' 6 seconds

Const HANDSHAKE_TIMEOUT                                                       = 5000 ' Seconds

Const SupplicantModeAuto                                                      = &H00000000&
Const SupplicantModeManual                                                    = &H00000001&

Const NDTEST_WPA_WEP_KEY                                                      = "0123456789"

Const WLAN_DEFAULT_PMK_PASSWORD                                               = "0123456789"

' Security Type
Const WLAN_SECURITY_TYPE_WEP                                                  = &H00000001&
Const WLAN_SECURITY_TYPE_WPA                                                  = &H00000002&

' Encryption Type (Bit Mask)
Const WLAN_ENCRYPTION_TYPE_WEP                                                = &H00000001&
Const WLAN_ENCRYPTION_TYPE_TKIP                                               = &H00000002&
Const WLAN_ENCRYPTION_TYPE_AES                                                = &H00000004&

' Wireless Type (Bit Mask) 
Const WLAN_WIRELESS_TYPE_11A                                                  = &H00000001&
Const WLAN_WIRELESS_TYPE_11B                                                  = &H00000002&
Const WLAN_WIRELESS_TYPE_11G                                                  = &H00000004&
       
Const WLAN_REGISTRY_KEY                                                       = "HKEY_CURRENT_USER\Software\Microsoft\NDTEST\Wireless\"
Const CWLAN_PRINT_BEGIN                                                       = "<u><font color='#8B008B'>"
Const CWLAN_PRINT_END                                                         = "</font></u>"

Const CWLAN_KEY_DEFAULT                                                       = "FF-FF-FF-FF-FF-FF"
Const CWLAN_KEYTYPE_PAIRWISE                                                  = &H00000001&
Const CWLAN_KEYTYPE_GROUP                                                     = &H00000002&
Const CWLAN_OID_QUERY                                                         = 0
Const CWLAN_OID_SET                                                           = 1
Const CWLAN_MEDIA_CONNECTED                                                   = 0
Const CWLAN_MEDIA_DISCONNECTED                                                = 1

Const WLAN_PERCENT_TO_PASS_DIRECTED                                           = 90
Const WLAN_PERCENT_TO_PASS_BROADCAST                                          = 60

Const INFORMATION_ELEMENT_SSID                                                = 0
Const INFORMATION_ELEMENT_SUPPORTED_RATES                                     = 1
Const INFORMATION_ELEMENT_FH_PARAMETER_SET                                    = 2
Const INFORMATION_ELEMENT_DS_PARAMETER_SET                                    = 3
Const INFORMATION_ELEMENT_CF_PARAMETER_SET                                    = 4
Const INFORMATION_ELEMENT_TIM                                                 = 5
Const INFORMATION_ELEMENT_IBSS_PARAMETER_SET                                  = 6
Const INFORMATION_ELEMENT_CHALLENGE_TEXT                                      = 16

' authentication/integrity fields
Const NDIS_802_11_AUTH_REQUEST_REAUTH				                              = &H00000001
Const NDIS_802_11_AUTH_REQUEST_KEYUPDATE			                              = &H00000002
Const NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR		                           = &H00000006
Const NDIS_802_11_AUTH_REQUEST_GROUP_ERROR		                              = &H0000000E

' Association Information Bits
Const NDIS_802_11_AI_REQFI_CAPABILITIES                                       = &H00000001&
Const NDIS_802_11_AI_REQFI_LISTENINTERVAL                                     = &H00000002&
Const NDIS_802_11_AI_REQFI_CURRENTAPADDRESS                                   = &H00000004&

Const NDIS_802_11_AI_RESFI_CAPABILITIES                                       = &H00000001&
Const NDIS_802_11_AI_RESFI_STATUSCODE                                         = &H00000002&
Const NDIS_802_11_AI_RESFI_ASSOCIATIONID                                      = &H00000004&

Const Ndis802_11StatusType_Authentication                                     = 0
' Network Types
Const  Ndis802_11FH                                                           = 0
Const  Ndis802_11DS                                                           = 1
Const  Ndis802_11OFDM5                                                        = 2
Const  Ndis802_11OFDM24                                                       = 3

' Infrastructure Modes
Const Ndis802_11IBSS                                                          = 0
Const Ndis802_11Infrastructure                                                = 1
Const Ndis802_11AutoUnknown                                                   = 2
Const Ndis802_11InfrastructureMax                                             = 3

' Authentication Modes
Const Ndis802_11AuthModeOpen                                                  = 0
Const Ndis802_11AuthModeShared                                                = 1
Const Ndis802_11AuthModeAutoSwitch                                            = 2
Const Ndis802_11AuthModeWPA                                                   = 3
Const Ndis802_11AuthModeWPAPSK                                                = 4
Const Ndis802_11AuthModeWPANone                                               = 5
Const Ndis802_11AuthModeMax                                                   = 6

' ReloadDefaults
Const  NDIS802_11RELOADWEPKEYS                                                = 0 

' Power Modes
Const Ndis802_11PowerModeCAM                                                  = 0
Const Ndis802_11PowerModeMAX_PSP                                              = 1
Const Ndis802_11PowerModeFast_PSP                                             = 2

' Private Filters
Const Ndis802_11PrivFilterAcceptAll                                           = 0
Const Ndis802_11PrivFilter8021xWEP                                            = 1

' EncryptionStatus
Public Ndis802_11WEPEnabled               : Ndis802_11WEPEnabled              = 0
Public Ndis802_11Encryption1Enabled       : Ndis802_11Encryption1Enabled      = Ndis802_11WEPEnabled
Public Ndis802_11WEPDisabled              : Ndis802_11WEPDisabled             = 1
Public Ndis802_11EncryptionDisabled       : Ndis802_11EncryptionDisabled      = Ndis802_11WEPDisabled
Public Ndis802_11WEPKeyAbsent             : Ndis802_11WEPKeyAbsent            = 2
Public Ndis802_11Encryption1KeyAbsent     : Ndis802_11Encryption1KeyAbsent    = Ndis802_11WEPKeyAbsent
Public Ndis802_11WEPNotSupported          : Ndis802_11WEPNotSupported         = 3
Public Ndis802_11EncryptionNotSupported   : Ndis802_11EncryptionNotSupported  = Ndis802_11WEPNotSupported
Public Ndis802_11Encryption2Enabled       : Ndis802_11Encryption2Enabled      = 4
Public Ndis802_11Encryption2KeyAbsent     : Ndis802_11Encryption2KeyAbsent    = 5
Public Ndis802_11Encryption3Enabled       : Ndis802_11Encryption3Enabled      = 6
Public Ndis802_11Encryption3KeyAbsent     : Ndis802_11Encryption13KeyAbsent    = 7 

' These arrays are used to return the string name to the enumeration value.
g_aInfrastructureMode      = Array("Ndis802_11IBSS",                    _
                                   "Ndis802_11Infrastructure",          _
                                   "Ndis802_11AutoUnknown",             _
                                   "Ndis802_11InfrastructureMax")
       
g_aAuthenticationMode      = Array("Ndis802_11AuthModeOpen",            _
                                   "Ndis802_11AuthModeShared",          _
                                   "Ndis802_11AuthModeAutoSwitch",      _
                                   "Ndis802_11AuthModeWPA",             _
                                   "Ndis802_11AuthModeWPAPSK",          _
                                   "Ndis802_11AuthModeWPANone",         _
                                   "Ndis802_11AuthModeMax")
                                  
g_aEncryptionStatus        = Array("Ndis802_11Encryption1Enabled",      _
                                   "Ndis802_11EncryptionDisabled",      _
                                   "Ndis802_11Encryption1KeyAbsent",    _
                                   "Ndis802_11EncryptionNotSupported",  _
                                   "Ndis802_11Encryption2Enabled",      _
                                   "Ndis802_11Encryption2KeyAbsent",    _
                                   "Ndis802_11Encryption3Enabled",      _
                                   "Ndis802_11Encryption3KeyAbsent")
                                  
g_aNetworkTypesSupported   = Array("Ndis802_11FH",                      _ 
                                   "Ndis802_11DS",                      _
                                   "Ndis802_11OFDM5",                   _
                                   "Ndis802_11OFDM24")
                                   
g_aReloadDefaults          = Array("Ndis802_11ReloadWEPKeys")

g_aPowerModes              = Array("Ndis802_11PowerModeCAM",            _
                                   "Ndis802_11PowerModeMAX_PSP",        _
                                   "Ndis802_11PowerModeFast_PSP")
                                   
g_aPrivateFilters          = Array("Ndis802_11PrivFilterAcceptAll",     _
                                   "Ndis802_11PrivFilter8021xWEP")
'<!-- CRC = 0xfe47c2dd --->