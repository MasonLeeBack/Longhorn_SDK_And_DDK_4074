'================================================================================================='
' This script defines all the WLAN related constants and enumerations
'
' Author:
' - David Harding
'
' Required Includes:
'  - 
'================================================================================================='
Option Explicit

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
' Generic WLAN Constants
'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
Const NDISUIOAP                                                               = "NDISUIOAP"


'TODO: Change this to at a 128 bit key
Const WLAN_KEY_WEP                                                            = "0123456789" 
Const WLAN_KEY_TKIP                                                           = "0123456789012345678901234567890123456789012345678901234567890123"
Const WLAN_KEY_AES                                                            = "01234567890123456789012345678901"

Const WLAN_KEYTYPE_DEFAULT                                                    = "FF-FF-FF-FF-FF-FF"
Const WLAN_KEYTYPE_PAIRWISE                                                   = &H00000001&
Const WLAN_KEYTYPE_GROUP                                                      = &H00000002&

Const WLAN_ENCRYPTION_TYPE_WEP                                                = &H00000001&
Const WLAN_ENCRYPTION_TYPE_TKIP                                               = &H00000002&
Const WLAN_ENCRYPTION_TYPE_AES                                                = &H00000004&

Const WLAN_PHY_TYPE_11A                                                       = &H00000001&
Const WLAN_PHY_TYPE_11B                                                       = &H00000002&
Const WLAN_PHY_TYPE_11G                                                       = &H00000004&

Public WLAN_MEDIA_CONNECTED                        : WLAN_MEDIA_CONNECTED                          = CLng(0)
Public WLAN_MEDIA_DISCONNECTED                     : WLAN_MEDIA_DISCONNECTED                       = CLng(1)

Public WLAN_IE_SID                                 : WLAN_IE_SID                                   = CLng(0)
Public WLAN_IE_SUPPORTED_RATES                     : WLAN_IE_SUPPORTED_RATES                       = CLng(1)
Public WLAN_IE_FH_PARAMETER_SET                    : WLAN_IE_FH_PARAMETER_SET                      = CLng(2)
Public WLAN_IE_DS_PARAMETER_SET                    : WLAN_IE_DS_PARAMETER_SET                      = CLng(3)
Public WLAN_IE_CF_PARAMETER_SET                    : WLAN_IE_CF_PARAMETER_SET                      = CLng(4)
Public WLAN_IE_TIM                                 : WLAN_IE_TIM                                   = CLng(5)
Public WLAN_IE_IBSS_PARAMETER_SET                  : WLAN_IE_IBSS_PARAMETER_SET                    = CLng(6)
Public WLAN_IE_CHALLENGE_TEXT                      : WLAN_IE_CHALLENGE_TEXT                        = CLng(16)
Public WLAN_IE_WPA                                 : WLAN_IE_WPA                                   = CLng(221)

Public WLAN_PERCENT_TO_PASS_DIRECTED               : WLAN_PERCENT_TO_PASS_DIRECTED                 = CLng(90)
Public WLAN_PERCENT_TO_PASS_BROADCAST              : WLAN_PERCENT_TO_PASS_BROADCAST                = CLng(60)

Public WLAN_ASSOCIATE_TIMEOUT                      : WLAN_ASSOCIATE_TIMEOUT                        = CLng(15)
Public WLAN_SSID_TIMEOUT                           : WLAN_SSID_TIMEOUT                             = CLng(1000 * 20) ' 20 seconds
Public WLAN_BSSID_LIST_SCAN_TIMEOUT                : WLAN_BSSID_LIST_SCAN_TIMEOUT                  = CLng(1000 * 6)  ' 6 seconds
              
'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
' WLAN Constants
'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
Public NDIS_802_11_AUTH_REQUEST_REAUTH	            : NDIS_802_11_AUTH_REQUEST_REAUTH			      = CLng(&H00000001&)
Public NDIS_802_11_AUTH_REQUEST_KEYUPDATE          : NDIS_802_11_AUTH_REQUEST_KEYUPDATE			   = CLng(&H00000002&)
Public NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR     : NDIS_802_11_AUTH_REQUEST_PAIRWISE_ERROR       = CLng(&H00000006&)
Public NDIS_802_11_AUTH_REQUEST_GROUP_ERROR	      : NDIS_802_11_AUTH_REQUEST_GROUP_ERROR	         = CLng(&H0000000E&)

Public NDIS_802_11_AI_REQFI_CAPABILITIES           : NDIS_802_11_AI_REQFI_CAPABILITIES             = CLng(&H00000001&)
Public NDIS_802_11_AI_REQFI_LISTENINTERVAL         : NDIS_802_11_AI_REQFI_LISTENINTERVAL           = CLng(&H00000002&)
Public NDIS_802_11_AI_REQFI_CURRENTAPADDRESS       : NDIS_802_11_AI_REQFI_CURRENTAPADDRESS         = CLng(&H00000004&)

Public NDIS_802_11_AI_RESFI_CAPABILITIES           : NDIS_802_11_AI_RESFI_CAPABILITIES             = CLng(&H00000001&)
Public NDIS_802_11_AI_RESFI_STATUSCODE             : NDIS_802_11_AI_RESFI_STATUSCODE               = CLng(&H00000002&)
Public NDIS_802_11_AI_RESFI_ASSOCIATIONID          : NDIS_802_11_AI_RESFI_ASSOCIATIONID            = CLng(&H00000004&)

'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
' WLAN Enumerations
'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
Public Ndis802_11StatusType_Authentication         : Ndis802_11StatusType_Authentication           = CLng(0)

Public  Ndis802_11FH                               : Ndis802_11FH                                  = CLng(0)
Public  Ndis802_11DS                               : Ndis802_11DS                                  = CLng(1)
Public  Ndis802_11OFDM5                            : Ndis802_11OFDM5                               = CLng(2)
Public  Ndis802_11OFDM24                           : Ndis802_11OFDM24                              = CLng(3)

Public Ndis802_11IBSS                              : Ndis802_11IBSS                                = CLng(0)
Public Ndis802_11Infrastructure                    : Ndis802_11Infrastructure                      = CLng(1)
Public Ndis802_11AutoUnknown                       : Ndis802_11AutoUnknown                         = CLng(2)
Public Ndis802_11InfrastructureMax                 : Ndis802_11InfrastructureMax                   = CLng(3)

Public Ndis802_11AuthModeOpen                      : Ndis802_11AuthModeOpen                        = CLng(0)
Public Ndis802_11AuthModeShared                    : Ndis802_11AuthModeShared                      = CLng(1)
Public Ndis802_11AuthModeAutoSwitch                : Ndis802_11AuthModeAutoSwitch                  = CLng(2)
Public Ndis802_11AuthModeWPA                       : Ndis802_11AuthModeWPA                         = CLng(3)
Public Ndis802_11AuthModeWPAPSK                    : Ndis802_11AuthModeWPAPSK                      = CLng(4)
Public Ndis802_11AuthModeWPANone                   : Ndis802_11AuthModeWPANone                     = CLng(5)
Public Ndis802_11AuthModeMax                       : Ndis802_11AuthModeMax                         = CLng(6)

Public Ndis802_11ReloadWEPKeys                     : Ndis802_11ReloadWEPKeys                       = CLng(0)

Public Ndis802_11PowerModeCAM                      : Ndis802_11PowerModeCAM                        = CLng(0)
Public Ndis802_11PowerModeMAX_PSP                  : Ndis802_11PowerModeMAX_PSP                    = CLng(1)
Public Ndis802_11PowerModeFast_PSP                 : Ndis802_11PowerModeFast_PSP                   = CLng(2)

Public Ndis802_11PrivFilterAcceptAll               : Ndis802_11PrivFilterAcceptAll                 = CLng(0)
Public Ndis802_11PrivFilter8021xWEP                : Ndis802_11PrivFilter8021xWEP                  = CLng(1)

Public Ndis802_11WEPEnabled                        : Ndis802_11WEPEnabled                          = CLng(0)
Public Ndis802_11Encryption1Enabled                : Ndis802_11Encryption1Enabled                  = CLng(Ndis802_11WEPEnabled)
Public Ndis802_11WEPDisabled                       : Ndis802_11WEPDisabled                         = CLng(1)
Public Ndis802_11EncryptionDisabled                : Ndis802_11EncryptionDisabled                  = CLng(Ndis802_11WEPDisabled)
Public Ndis802_11WEPKeyAbsent                      : Ndis802_11WEPKeyAbsent                        = CLng(2)
Public Ndis802_11Encryption1KeyAbsent              : Ndis802_11Encryption1KeyAbsent                = CLng(Ndis802_11WEPKeyAbsent)
Public Ndis802_11WEPNotSupported                   : Ndis802_11WEPNotSupported                     = CLng(3)
Public Ndis802_11EncryptionNotSupported            : Ndis802_11EncryptionNotSupported              = CLng(Ndis802_11WEPNotSupported)
Public Ndis802_11Encryption2Enabled                : Ndis802_11Encryption2Enabled                  = CLng(4)
Public Ndis802_11Encryption2KeyAbsent              : Ndis802_11Encryption2KeyAbsent                = CLng(5)
Public Ndis802_11Encryption3Enabled                : Ndis802_11Encryption3Enabled                  = CLng(6)
Public Ndis802_11Encryption3KeyAbsent              : Ndis802_11Encryption3KeyAbsent                = CLng(7)
'<!-- CRC = 0x2ee61791 --->