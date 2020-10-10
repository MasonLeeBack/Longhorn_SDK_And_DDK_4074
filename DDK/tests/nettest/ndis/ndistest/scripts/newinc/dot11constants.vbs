Option Explicit
Dim NdisPhysicalMediumNative802_11                              : NdisPhysicalMediumNative802_11                              = CLng(&H00000009&                                          )

Dim DOT11_CURRENT_VERSION                                       : DOT11_CURRENT_VERSION                                       = CInt(0)

Dim DOT11_INFO_ELEMENT_ID_SSID                                  : DOT11_INFO_ELEMENT_ID_SSID                                  = CLng(0)
Dim DOT11_INFO_ELEMENT_ID_SUPPORTED_RATES                       : DOT11_INFO_ELEMENT_ID_SUPPORTED_RATES                       = CLng(1)
Dim DOT11_INFO_ELEMENT_ID_FH_PARAM_SET                          : DOT11_INFO_ELEMENT_ID_FH_PARAM_SET                          = CLng(2)
Dim DOT11_INFO_ELEMENT_ID_DS_PARAM_SET                          : DOT11_INFO_ELEMENT_ID_DS_PARAM_SET                          = CLng(3)
Dim DOT11_INFO_ELEMENT_ID_CF_PARAM_SET                          : DOT11_INFO_ELEMENT_ID_CF_PARAM_SET                          = CLng(4)
Dim DOT11_INFO_ELEMENT_ID_TIM                                   : DOT11_INFO_ELEMENT_ID_TIM                                   = CLng(5)
Dim DOT11_INFO_ELEMENT_ID_IBSS_PARAM_SET                        : DOT11_INFO_ELEMENT_ID_IBSS_PARAM_SET                        = CLng(6)
Dim DOT11_INFO_ELEMENT_ID_COUNTRY_INFO                          : DOT11_INFO_ELEMENT_ID_COUNTRY_INFO                          = CLng(7)
Dim DOT11_INFO_ELEMENT_ID_FH_PARAM                              : DOT11_INFO_ELEMENT_ID_FH_PARAM                              = CLng(8)
Dim DOT11_INFO_ELEMENT_ID_FH_PATTERN_TABLE                      : DOT11_INFO_ELEMENT_ID_FH_PATTERN_TABLE                      = CLng(9)
Dim DOT11_INFO_ELEMENT_ID_REQUESTED                             : DOT11_INFO_ELEMENT_ID_REQUESTED                             = CLng(10)
Dim DOT11_INFO_ELEMENT_ID_CHALLENGE                             : DOT11_INFO_ELEMENT_ID_CHALLENGE                             = CLng(16)
Dim DOT11_INFO_ELEMENT_ID_VENDOR_SPECIFIC                       : DOT11_INFO_ELEMENT_ID_VENDOR_SPECIFIC                       = CLng(221) ' WPA

Dim DOT11_MAX_PDU_SIZE                                          : DOT11_MAX_PDU_SIZE                                          = CLng(2346)
Dim DOT11_MIN_PDU_SIZE                                          : DOT11_MIN_PDU_SIZE                                          = CLng(256)
Dim DOT11_MAX_NUM_DEFAULT_KEY                                   : DOT11_MAX_NUM_DEFAULT_KEY                                   = CLng(4)

Dim DOT11_HW_WEP_SUPPORTED_TX                                   : DOT11_HW_WEP_SUPPORTED_TX                                   = CLng(&H00000001&)
Dim DOT11_HW_WEP_SUPPORTED_RX                                   : DOT11_HW_WEP_SUPPORTED_RX                                   = CLng(&H00000002&)
Dim DOT11_HW_FRAGMENTATION_SUPPORTED                            : DOT11_HW_FRAGMENTATION_SUPPORTED                            = CLng(&H00000004&)
Dim DOT11_HW_DEFRAGMENTATION_SUPPORTED                          : DOT11_HW_DEFRAGMENTATION_SUPPORTED                          = CLng(&H00000008&)
Dim DOT11_HW_MSDU_AUTH_SUPPORTED_TX                             : DOT11_HW_MSDU_AUTH_SUPPORTED_TX                             = CLng(&H00000010&)
Dim DOT11_HW_MSDU_AUTH_SUPPORTED_RX                             : DOT11_HW_MSDU_AUTH_SUPPORTED_RX                             = CLng(&H00000020&)

 'WEP Algorithm flags
Dim DOT11_CONF_ALGO_WEP_RC4                                     : DOT11_CONF_ALGO_WEP_RC4                                     = CLng(&H00000001&)   ' WEP RC4)
Dim DOT11_CONF_ALGO_TKIP                                        : DOT11_CONF_ALGO_TKIP                                        = CLng(&H00000002&)   ' BUGBUG: Remove after Review! TKIP RC4)

' Integrity Algorithm flags
Dim DOT11_AUTH_ALGO_MICHAEL                                     : DOT11_AUTH_ALGO_MICHAEL                                     = CLng(&H00000001&)   ' Michael )
Dim DOT11_ADDRESS_TYPE_UNICAST                                  : DOT11_ADDRESS_TYPE_UNICAST                                  = CLng(&H00000001&)
Dim DOT11_ADDRESS_TYPE_MULTICAST                                : DOT11_ADDRESS_TYPE_MULTICAST                                = CLng(&H00000002&)

Dim DOT11_OPERATION_MODE_UNKNOWN                                : DOT11_OPERATION_MODE_UNKNOWN                                = CLng(&H00000000&)
Dim DOT11_OPERATION_MODE_STATION                                : DOT11_OPERATION_MODE_STATION                                = CLng(&H00000001&)
Dim DOT11_OPERATION_MODE_AP                                     : DOT11_OPERATION_MODE_AP                                     = CLng(&H00000002&)
   
Dim DOT11_PACKET_TYPE_DIRECTED_CTRL                            : DOT11_PACKET_TYPE_DIRECTED_CTRL                            = CLng(&H00000001&)
Dim DOT11_PACKET_TYPE_DIRECTED_MGMT                            : DOT11_PACKET_TYPE_DIRECTED_MGMT                            = CLng(&H00000002&)
Dim DOT11_PACKET_TYPE_DIRECTED_DATA                            : DOT11_PACKET_TYPE_DIRECTED_DATA                            = CLng(&H00000004&)
Dim DOT11_PACKET_TYPE_MULTICAST_CTRL                           : DOT11_PACKET_TYPE_MULTICAST_CTRL                           = CLng(&H00000008&)
Dim DOT11_PACKET_TYPE_MULTICAST_MGMT                           : DOT11_PACKET_TYPE_MULTICAST_MGMT                           = CLng(&H00000010&)
Dim DOT11_PACKET_TYPE_MULTICAST_DATA                           : DOT11_PACKET_TYPE_MULTICAST_DATA                           = CLng(&H00000020&)
Dim DOT11_PACKET_TYPE_BROADCAST_CTRL                           : DOT11_PACKET_TYPE_BROADCAST_CTRL                           = CLng(&H00000040&)
Dim DOT11_PACKET_TYPE_BROADCAST_MGMT                           : DOT11_PACKET_TYPE_BROADCAST_MGMT                           = CLng(&H00000080&)
Dim DOT11_PACKET_TYPE_BROADCAST_DATA                           : DOT11_PACKET_TYPE_BROADCAST_DATA                           = CLng(&H00000100&)
Dim DOT11_PACKET_TYPE_PROMISCUOUS_CTRL                         : DOT11_PACKET_TYPE_PROMISCUOUS_CTRL                         = CLng(&H00000200&)
Dim DOT11_PACKET_TYPE_PROMISCUOUS_MGMT                         : DOT11_PACKET_TYPE_PROMISCUOUS_MGMT                         = CLng(&H00000400&)
Dim DOT11_PACKET_TYPE_PROMISCUOUS_DATA                         : DOT11_PACKET_TYPE_PROMISCUOUS_DATA                         = CLng(&H00000800&)
Dim DOT11_PACKET_TYPE_ALL_MULTICAST_CTRL                       : DOT11_PACKET_TYPE_ALL_MULTICAST_CTRL                       = CLng(&H00001000&)
Dim DOT11_PACKET_TYPE_ALL_MULTICAST_MGMT                       : DOT11_PACKET_TYPE_ALL_MULTICAST_MGMT                       = CLng(&H00002000&)
Dim DOT11_PACKET_TYPE_ALL_MULTICAST_DATA                       : DOT11_PACKET_TYPE_ALL_MULTICAST_DATA                       = CLng(&H00004000&)

Dim DOT11_SSID_MAX_LENGTH                                       : DOT11_SSID_MAX_LENGTH                                       = CLng(32)
Dim DOT11_RATE_SET_MAX_LENGTH                                   : DOT11_RATE_SET_MAX_LENGTH                                   = CLng(126)
    
Dim DOT11_CAPABILITY_INFO_ESS                                   : DOT11_CAPABILITY_INFO_ESS                                   = CLng(&H0001&)
Dim DOT11_CAPABILITY_INFO_IBSS                                  : DOT11_CAPABILITY_INFO_IBSS                                  = CLng(&H0002&)
Dim DOT11_CAPABILITY_INFO_CF_POLLABLE                           : DOT11_CAPABILITY_INFO_CF_POLLABLE                           = CLng(&H0004&)
Dim DOT11_CAPABILITY_INFO_CF_POLL_REQ                           : DOT11_CAPABILITY_INFO_CF_POLL_REQ                           = CLng(&H0008&)
Dim DOT11_CAPABILITY_INFO_PRIVACY                               : DOT11_CAPABILITY_INFO_PRIVACY                               = CLng(&H0010&)
Dim DOT11_CAPABILITY_SHORT_PREAMBLE                             : DOT11_CAPABILITY_SHORT_PREAMBLE                             = CLng(&H0020&)
Dim DOT11_CAPABILITY_PBCC                                       : DOT11_CAPABILITY_PBCC                                       = CLng(&H0040&)
Dim DOT11_CAPABILITY_CHANNEL_AGILITY                            : DOT11_CAPABILITY_CHANNEL_AGILITY                            = CLng(&H0080&)

Dim DOT11_POWER_SAVE_LEVEL_MAX_PSP                              : DOT11_POWER_SAVE_LEVEL_MAX_PSP                              = CLng(1)
Dim DOT11_POWER_SAVE_LEVEL_FAST_PSP                             : DOT11_POWER_SAVE_LEVEL_FAST_PSP                             = CLng(2)
Dim DOT11_POWER_SAVE_LEVEL_NO_PSP                               : DOT11_POWER_SAVE_LEVEL_NO_PSP                               = CLng(3)

Dim DOT11_REG_DOMAIN_OTHER                                      : DOT11_REG_DOMAIN_OTHER                                      = CLng(&H00000000&)
Dim DOT11_REG_DOMAIN_FCC                                        : DOT11_REG_DOMAIN_FCC                                        = CLng(&H00000010&)
Dim DOT11_REG_DOMAIN_DOC                                        : DOT11_REG_DOMAIN_DOC                                        = CLng(&H00000020&)
Dim DOT11_REG_DOMAIN_ETSI                                       : DOT11_REG_DOMAIN_ETSI                                       = CLng(&H00000030&)
Dim DOT11_REG_DOMAIN_SPAIN                                      : DOT11_REG_DOMAIN_SPAIN                                      = CLng(&H00000031&)
Dim DOT11_REG_DOMAIN_FRANCE                                     : DOT11_REG_DOMAIN_FRANCE                                     = CLng(&H00000032&)
Dim DOT11_REG_DOMAIN_MKK                                        : DOT11_REG_DOMAIN_MKK                                        = CLng(&H00000040&)

Dim DOT11_CCA_MODE_ED_ONLY                                      : DOT11_CCA_MODE_ED_ONLY                                      = CLng(&H00000001&)
Dim DOT11_CCA_MODE_CS_ONLY                                      : DOT11_CCA_MODE_CS_ONLY                                      = CLng(&H00000002&)
Dim DOT11_CCA_MODE_ED_and_CS                                    : DOT11_CCA_MODE_ED_and_CS                                    = CLng(&H00000004&)
  
Dim DOT11_FREQUENCY_BANDS_LOWER                                 : DOT11_FREQUENCY_BANDS_LOWER                                 = CLng(&H00000001&)
Dim DOT11_FREQUENCY_BANDS_MIDDLE                                : DOT11_FREQUENCY_BANDS_MIDDLE                                = CLng(&H00000002&)
Dim DOT11_FREQUENCY_BANDS_UPPER                                 : DOT11_FREQUENCY_BANDS_UPPER                                 = CLng(&H00000004&)

Dim DOT11_HR_CCA_MODE_ED_ONLY                                   : DOT11_HR_CCA_MODE_ED_ONLY                                   = CLng(&H00000001&)
Dim DOT11_HR_CCA_MODE_CS_ONLY                                   : DOT11_HR_CCA_MODE_CS_ONLY                                   = CLng(&H00000002&)
Dim DOT11_HR_CCA_MODE_CS_AND_ED                                 : DOT11_HR_CCA_MODE_CS_AND_ED                                 = CLng(&H00000004&)
Dim DOT11_HR_CCA_MODE_CS_WITH_TIMER                             : DOT11_HR_CCA_MODE_CS_WITH_TIMER                             = CLng(&H00000008&)
Dim DOT11_HR_CCA_MODE_HRCS_AND_ED                               : DOT11_HR_CCA_MODE_HRCS_AND_ED                               = CLng(&H00000010&)

Dim DOT11_MAX_NUM_OF_FRAGMENTS                                  : DOT11_MAX_NUM_OF_FRAGMENTS                                  = CLng(16)

Dim DOT11_PRIORITY_CONTENTION                                   : DOT11_PRIORITY_CONTENTION                                   = CLng(0)
Dim DOT11_PRIORITY_CONTENTION_FREE                              : DOT11_PRIORITY_CONTENTION_FREE                              = CLng(1)

Dim DOT11_SERVICE_CLASS_REORDERABLE_MULTICAST                   : DOT11_SERVICE_CLASS_REORDERABLE_MULTICAST                   = CLng(0)
Dim DOT11_SERVICE_CLASS_STRICTLY_ORDERED                        : DOT11_SERVICE_CLASS_STRICTLY_ORDERED                        = CLng(1)

Dim DOT11_FLAGS_80211B_SHORT_PREAMBLE                           : DOT11_FLAGS_80211B_SHORT_PREAMBLE                           = CLng(&H00000001&)
Dim DOT11_FLAGS_80211B_PBCC                                     : DOT11_FLAGS_80211B_PBCC                                     = CLng(&H00000002&)
Dim DOT11_FLAGS_80211B_CHANNEL_AGILITY                          : DOT11_FLAGS_80211B_CHANNEL_AGILITY                          = CLng(&H00000004&)
Dim DOT11_FLAGS_PS_ON                                           : DOT11_FLAGS_PS_ON                                           = CLng(&H00000008&)

Dim DOT11_STATUS_SUCCESS                                        : DOT11_STATUS_SUCCESS                                        = CLng(&H00000001&)
Dim DOT11_STATUS_RETRY_LIMIT_EXCEEDED                           : DOT11_STATUS_RETRY_LIMIT_EXCEEDED                           = CLng(&H00000002&)
Dim DOT11_STATUS_UNSUPPORTED_PRIORITY                           : DOT11_STATUS_UNSUPPORTED_PRIORITY                           = CLng(&H00000004&)
Dim DOT11_STATUS_UNSUPPORTED_SERVICE_CLASS                      : DOT11_STATUS_UNSUPPORTED_SERVICE_CLASS                      = CLng(&H00000008&)
Dim DOT11_STATUS_UNAVAILABLE_PRIORITY                           : DOT11_STATUS_UNAVAILABLE_PRIORITY                           = CLng(&H00000010&)
Dim DOT11_STATUS_UNAVAILABLE_SERVICE_CLASS                      : DOT11_STATUS_UNAVAILABLE_SERVICE_CLASS                      = CLng(&H00000020&)
Dim DOT11_STATUS_XMIT_MSDU_TIMER_EXPIRED                        : DOT11_STATUS_XMIT_MSDU_TIMER_EXPIRED                        = CLng(&H00000040&)
Dim DOT11_STATUS_UNAVAILABLE_BSS                                : DOT11_STATUS_UNAVAILABLE_BSS                                = CLng(&H00000080&)
Dim DOT11_STATUS_EXCESSIVE_DATA_LENGTH                          : DOT11_STATUS_EXCESSIVE_DATA_LENGTH                          = CLng(&H00000100&)
Dim DOT11_STATUS_ENCRYPTION_FAILED                              : DOT11_STATUS_ENCRYPTION_FAILED                              = CLng(&H00000200&)
Dim DOT11_STATUS_WEP_KEY_UNAVAILABLE                            : DOT11_STATUS_WEP_KEY_UNAVAILABLE                            = CLng(&H00000400&)
Dim DOT11_STATUS_ICV_VERIFIED                                   : DOT11_STATUS_ICV_VERIFIED                                   = CLng(&H00000800&)
Dim DOT11_STATUS_PACKET_REASSEMBLED                             : DOT11_STATUS_PACKET_REASSEMBLED                             = CLng(&H00001000&)
Dim DOT11_STATUS_PACKET_NOT_REASSEMBLED                         : DOT11_STATUS_PACKET_NOT_REASSEMBLED                         = CLng(&H00002000&)
Dim DOT11_STATUS_GENERATE_AUTH_FAILED                           : DOT11_STATUS_GENERATE_AUTH_FAILED                           = CLng(&H00004000&)
Dim DOT11_STATUS_AUTH_NOT_VERIFIED                              : DOT11_STATUS_AUTH_NOT_VERIFIED                              = CLng(&H00008000&)
Dim DOT11_STATUS_AUTH_VERIFIED                                  : DOT11_STATUS_AUTH_VERIFIED                                  = CLng(&H00010000&)
Dim DOT11_STATUS_AUTH_FAILED                                    : DOT11_STATUS_AUTH_FAILED                                    = CLng(&H00020000&)

Dim DOT11_STATUS_SCAN_CONFIRM                                   : DOT11_STATUS_SCAN_CONFIRM                                   = CLng(1)
Dim DOT11_STATUS_JOIN_CONFIRM                                   : DOT11_STATUS_JOIN_CONFIRM                                   = CLng(2)
Dim DOT11_STATUS_START_CONFIRM                                  : DOT11_STATUS_START_CONFIRM                                  = CLng(3)
Dim DOT11_STATUS_RESET_CONFIRM                                  : DOT11_STATUS_RESET_CONFIRM                                  = CLng(4)
Dim DOT11_STATUS_AP_JOIN_CONFIRM                                : DOT11_STATUS_AP_JOIN_CONFIRM                                = CLng(5)
Dim DOT11_STATUS_MPDU_MAX_LENGTH_CHANGED                        : DOT11_STATUS_MPDU_MAX_LENGTH_CHANGED                        = CLng(6)

Dim DOT11_FRAME_TYPE_MANAGEMENT                                 : DOT11_FRAME_TYPE_MANAGEMENT                                 = CInt(0)
Dim DOT11_FRAME_TYPE_CONTROL                                    : DOT11_FRAME_TYPE_CONTROL                                    = CInt(1)
Dim DOT11_FRAME_TYPE_DATA                                       : DOT11_FRAME_TYPE_DATA                                       = CInt(2)
Dim DOT11_FRAME_TYPE_RESERVED                                   : DOT11_FRAME_TYPE_RESERVED                                   = CInt(3)
    
Dim DOT11_MGMT_SUBTYPE_ASSOCIATION_REQUEST                      : DOT11_MGMT_SUBTYPE_ASSOCIATION_REQUEST                      = CInt(0)
Dim DOT11_MGMT_SUBTYPE_ASSOCIATION_RESPONSE                     : DOT11_MGMT_SUBTYPE_ASSOCIATION_RESPONSE                     = CInt(1)
Dim DOT11_MGMT_SUBTYPE_REASSOCIATION_REQUEST                    : DOT11_MGMT_SUBTYPE_REASSOCIATION_REQUEST                    = CInt(2)
Dim DOT11_MGMT_SUBTYPE_REASSOCIATION_RESPONSE                   : DOT11_MGMT_SUBTYPE_REASSOCIATION_RESPONSE                   = CInt(3)
Dim DOT11_MGMT_SUBTYPE_PROBE_REQUEST                            : DOT11_MGMT_SUBTYPE_PROBE_REQUEST                            = CInt(4)
Dim DOT11_MGMT_SUBTYPE_PROBE_RESPONSE                           : DOT11_MGMT_SUBTYPE_PROBE_RESPONSE                           = CInt(5)
Dim DOT11_MGMT_SUBTYPE_BEACON                                   : DOT11_MGMT_SUBTYPE_BEACON                                   = CInt(8)
Dim DOT11_MGMT_SUBTYPE_ATIM                                     : DOT11_MGMT_SUBTYPE_ATIM                                     = CInt(9)
Dim DOT11_MGMT_SUBTYPE_DISASSOCIATION                           : DOT11_MGMT_SUBTYPE_DISASSOCIATION                           = CInt(10)
Dim DOT11_MGMT_SUBTYPE_AUTHENTICATION                           : DOT11_MGMT_SUBTYPE_AUTHENTICATION                           = CInt(11)
Dim DOT11_MGMT_SUBTYPE_DEAUTHENTICATION                         : DOT11_MGMT_SUBTYPE_DEAUTHENTICATION                         = CInt(12)
    
' Native 802.11 enumeration values
Dim Dot11OffloadTypeWep                    : Dot11OffloadTypeWep                    = CLng(1)
Dim Dot11OffloadTypeAuth                   : Dot11OffloadTypeAuth                   = CLng(2)

Dim Dot11KeyDirectionBoth                  : Dot11KeyDirectionBoth                  = CLng(1)
Dim Dot11KeyDirectionInBound               : Dot11KeyDirectionInBound               = CLng(2)
Dim Dot11KeyDirectionOutBound              : Dot11KeyDirectionOutBound              = CLng(3)
 
Dim Dot11BssTypeInfrastructure             : Dot11BssTypeInfrastructure             = CLng(1)
Dim Dot11BssTypeIndependent                : Dot11BssTypeIndependent                = CLng(2)
Dim Dot11BssTypeAny                        : Dot11BssTypeAny                        = CLng(3)
    
Dim Dot11ScanTypeActive                    : Dot11ScanTypeActive                    = CLng(1)
Dim Dot11ScanTypePassive                   : Dot11ScanTypePassive                   = CLng(2)

Dim Dot11PhyTypeUnknown                    : Dot11PhyTypeUnknown                    = CLng(0)
Dim Dot11PhyTypeFhss                       : Dot11PhyTypeFhss                       = CLng(1)
Dim Dot11PhyTypeDsss                       : Dot11PhyTypeDsss                       = CLng(2)
Dim Dot11PhyTypeIrbaseBand                 : Dot11PhyTypeIrbaseBand                 = CLng(3)
Dim Dot11PhyTypeOfdm                       : Dot11PhyTypeOfdm                       = CLng(4)
Dim Dot11PhyTypeHrdsss                     : Dot11PhyTypeHrdsss                     = CLng(5)

Dim Dot11UpdateIeOpCreateReplace           : Dot11UpdateIeOpCreateReplace           = CLng(1)
Dim Dot11UpdateIeOpDelete                  : Dot11UpdateIeOpDelete                  = CLng(2)

Dim Dot11ResetTypePhy                      : Dot11ResetTypePhy                      = CLng(1)
Dim Dot11ResetTypeMac                      : Dot11ResetTypeMac                      = CLng(2)
Dim Dot11ResetTypePhyAndMac                : Dot11ResetTypePhyAndMac                = CLng(3)

Dim Dot11PowerModeUnknown                  : Dot11PowerModeUnknown                  = CLng(0)
Dim Dot11PowerModeActive                   : Dot11PowerModeActive                   = CLng(1)
Dim Dot11PowerModePowerSave                : Dot11PowerModePowerSave                = CLng(2)
  
Dim Dot11TempTypeUnknown                   : Dot11TempTypeUnknown                   = CLng(0)
Dim Dot11TempType1                         : Dot11TempType1                         = CLng(1)
Dim Dot11TempType2                         : Dot11TempType2                         = CLng(2)

Dim Dot11DiversitySupportUnknown           : Dot11DiversitySupportUnknown           = CLng(0)
Dim Dot11DiversitySupportFixedList         : Dot11DiversitySupportFixedList         = CLng(1)
Dim Dot11DiversitySupportNotSupported      : Dot11DiversitySupportNotSupported      = CLng(2)
Dim Dot11DiversitySupportDynamic           : Dot11DiversitySupportDynamic           = CLng(3)
    
Dim Dot11HopAlgoCurrent                    : Dot11HopAlgoCurrent                    = CLng(0)
Dim Dot11HopAlgoHopIndex                   : Dot11HopAlgoHopIndex                   = CLng(1)
Dim Dot11HopAlgoHcc                        : Dot11HopAlgoHcc                        = CLng(2)


Dim N11_BSSDESC_START_JOIN_TIMEOUT                              : N11_BSSDESC_START_JOIN_TIMEOUT                              = CLng(10)
Dim N11_BSSDESC_BEACON_PERIOD                                   : N11_BSSDESC_BEACON_PERIOD                                   = CLng(100)

Dim N11_MEDIA_CONNECTED                                         : N11_MEDIA_CONNECTED                                         = CLng(&H00000000&)
Dim N11_MEDIA_DISCONNECTED                                      : N11_MEDIA_DISCONNECTED                                      = CLng(&H00000001&)

Dim N11_MODE_STA                                                : N11_MODE_STA                                                = CLng(0)
Dim N11_MODE_AP                                                 : N11_MODE_AP                                                 = CLng(1)
Dim N11_MODE_CUSTOM                                             : N11_MODE_CUSTOM                                             = CLng(2)

Dim N11_STATE_INIT                                              : N11_STATE_INIT                                              = CLng(0)
Dim N11_STATE_OP                                                : N11_STATE_OP                                                = CLng(1)
Dim N11_STATE_CUSTOM                                            : N11_STATE_CUSTOM                                            = CLng(2)

'Dim N11_STATE_UNKNOWN                                           : N11_STATE_UNKNOWN                                           = CLng(&H00000000&)
'Dim N11_STATE_INIT                                              : N11_STATE_INIT                                              = CLng(&H00000001&)
'Dim N11_STATE_OP                                                : N11_STATE_OP                                                = CLng(&H00000002&)

Dim N11_SSID_1                                                  : N11_SSID_1                                                  = "DOT11_NDTEST_SSID1"
Dim N11_SSID_2                                                  : N11_SSID_2                                                  = "DOT11_NDTEST_SSID2"
Dim N11_SSID_3                                                  : N11_SSID_3                                                  = "DOT11_NDTEST_SSID3"

Dim N11_DEFAULT_SSID                                            : N11_DEFAULT_SSID                                            = "DOT11_NDTEST_SSID"
Dim N11_DEFAULT_CHANNEL                                         : N11_DEFAULT_CHANNEL                                         = CLng(11)
Dim N11_DEFAULT_FILTER                                          : N11_DEFAULT_FILTER                                          = DOT11_PACKET_TYPE_DIRECTED_DATA    Or _
	                                                                                                                             DOT11_PACKET_TYPE_MULTICAST_DATA   Or _
	                                                                                                                             DOT11_PACKET_TYPE_BROADCAST_DATA   Or _
	                                                                                                                             DOT11_PACKET_TYPE_DIRECTED_MGMT    Or _
	                                                                                                                             DOT11_PACKET_TYPE_BROADCAST_MGMT

Dim N11_RADIO_OFF                                               : N11_RADIO_OFF                                               = CLng(0)
Dim N11_RADIO_ON                                                : N11_RADIO_ON                                                = CLng(1)

Dim N11_STATUS_INDICATION_TIMEOUT                               : N11_STATUS_INDICATION_TIMEOUT                               = CLng(10) ' 10 seconds

Dim NATIVE_80211_MAJOR_VERSION                                  : NATIVE_80211_MAJOR_VERSION                                  = CLng(&H00000002&)
Dim NATIVE_80211_MINOR_VERSION                                  : NATIVE_80211_MINOR_VERSION                                  = CLng(&H00000000&)

' These constants define the test levels used by each script
Dim N11_TEST_LEVEL_STA_INIT                                     : N11_TEST_LEVEL_STA_INIT                                     = CLng(&H00000001&)
Dim N11_TEST_LEVEL_STA_OP                                       : N11_TEST_LEVEL_STA_OP                                       = CLng(&H00000002&)
Dim N11_TEST_LEVEL_AP_INIT                                      : N11_TEST_LEVEL_AP_INIT                                      = CLng(&H00000004&)
Dim N11_TEST_LEVEL_AP_OP                                        : N11_TEST_LEVEL_AP_OP                                        = CLng(&H00000008&)
Dim N11_TEST_LEVEL_CUSTOM                                       : N11_TEST_LEVEL_CUSTOM                                       = CLng(&H00000010&)
Dim N11_TEST_LEVEL_DEFAULT                                      : N11_TEST_LEVEL_DEFAULT                                      = N11_TEST_LEVEL_STA_INIT  Or _
                                                                                                                                N11_TEST_LEVEL_STA_OP    Or _
                                                                                                                                N11_TEST_LEVEL_AP_INIT   Or _
                                                                                                                                N11_TEST_LEVEL_AP_OP      Or _
                                                                                                                                N11_TEST_LEVEL_CUSTOM
'<!-- CRC = 0xa05eb765 --->