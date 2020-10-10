Option Explicit

Dim OID_DOT11_NDIS_START                           : OID_DOT11_NDIS_START                             = &H0D010300&

Dim OID_DOT11_OFFLOAD_CAPABILITY                   : OID_DOT11_OFFLOAD_CAPABILITY                     = (OID_DOT11_NDIS_START + 0)
Dim OID_DOT11_CURRENT_OFFLOAD_CAPABILITY           : OID_DOT11_CURRENT_OFFLOAD_CAPABILITY             = (OID_DOT11_NDIS_START + 1)
Dim OID_DOT11_WEP_OFFLOAD                          : OID_DOT11_WEP_OFFLOAD                            = (OID_DOT11_NDIS_START + 2)
Dim OID_DOT11_WEP_UPLOAD                           : OID_DOT11_WEP_UPLOAD                             = (OID_DOT11_NDIS_START + 3)
Dim OID_DOT11_DEFAULT_WEP_OFFLOAD                  : OID_DOT11_DEFAULT_WEP_OFFLOAD                    = (OID_DOT11_NDIS_START + 4)
Dim OID_DOT11_DEFAULT_WEP_UPLOAD                   : OID_DOT11_DEFAULT_WEP_UPLOAD                     = (OID_DOT11_NDIS_START + 5)
Dim OID_DOT11_MPDU_MAX_LENGTH                      : OID_DOT11_MPDU_MAX_LENGTH                        = (OID_DOT11_NDIS_START + 6)
Dim OID_DOT11_OPERATION_MODE_CAPABILITY            : OID_DOT11_OPERATION_MODE_CAPABILITY              = (OID_DOT11_NDIS_START + 7)
Dim OID_DOT11_CURRENT_OPERATION_MODE               : OID_DOT11_CURRENT_OPERATION_MODE                 = (OID_DOT11_NDIS_START + 8)
Dim OID_DOT11_CURRENT_PACKET_FILTER                : OID_DOT11_CURRENT_PACKET_FILTER                  = (OID_DOT11_NDIS_START + 9)
Dim OID_DOT11_ATIM_WINDOW                          : OID_DOT11_ATIM_WINDOW                            = (OID_DOT11_NDIS_START + 10)
Dim OID_DOT11_SCAN_REQUEST                         : OID_DOT11_SCAN_REQUEST                           = (OID_DOT11_NDIS_START + 11)
Dim OID_DOT11_CURRENT_PHY_TYPE                     : OID_DOT11_CURRENT_PHY_TYPE                       = (OID_DOT11_NDIS_START + 12)
Dim OID_DOT11_JOIN_REQUEST                         : OID_DOT11_JOIN_REQUEST                           = (OID_DOT11_NDIS_START + 13)
Dim OID_DOT11_START_REQUEST                        : OID_DOT11_START_REQUEST                          = (OID_DOT11_NDIS_START + 14)
Dim OID_DOT11_UPDATE_IE                            : OID_DOT11_UPDATE_IE                              = (OID_DOT11_NDIS_START + 15)
Dim OID_DOT11_RESET_REQUEST                        : OID_DOT11_RESET_REQUEST                          = (OID_DOT11_NDIS_START + 16)
Dim OID_DOT11_NIC_POWER_STATE                      : OID_DOT11_NIC_POWER_STATE                        = (OID_DOT11_NDIS_START + 17)
Dim OID_DOT11_OPTIONAL_CAPABILITY                  : OID_DOT11_OPTIONAL_CAPABILITY                    = (OID_DOT11_NDIS_START + 18)
Dim OID_DOT11_CURRENT_OPTIONAL_CAPABILITY          : OID_DOT11_CURRENT_OPTIONAL_CAPABILITY            = (OID_DOT11_NDIS_START + 19)
Dim OID_DOT11_STATION_ID                           : OID_DOT11_STATION_ID                             = (OID_DOT11_NDIS_START + 20)
Dim OID_DOT11_MEDIUM_OCCUPANCY_LIMIT               : OID_DOT11_MEDIUM_OCCUPANCY_LIMIT                 = (OID_DOT11_NDIS_START + 21)
Dim OID_DOT11_CF_POLLABLE                          : OID_DOT11_CF_POLLABLE                            = (OID_DOT11_NDIS_START + 22)
Dim OID_DOT11_CFP_PERIOD                           : OID_DOT11_CFP_PERIOD                             = (OID_DOT11_NDIS_START + 23)
Dim OID_DOT11_CFP_MAX_DURATION                     : OID_DOT11_CFP_MAX_DURATION                       = (OID_DOT11_NDIS_START + 24)
Dim OID_DOT11_POWER_MGMT_MODE                      : OID_DOT11_POWER_MGMT_MODE                        = (OID_DOT11_NDIS_START + 25)
Dim OID_DOT11_OPERATIONAL_RATE_SET                 : OID_DOT11_OPERATIONAL_RATE_SET                   = (OID_DOT11_NDIS_START + 26)
Dim OID_DOT11_BEACON_PERIOD                        : OID_DOT11_BEACON_PERIOD                          = (OID_DOT11_NDIS_START + 27)
Dim OID_DOT11_DTIM_PERIOD                          : OID_DOT11_DTIM_PERIOD                            = (OID_DOT11_NDIS_START + 28)
Dim OID_DOT11_WEP_ICV_ERROR_COUNT                  : OID_DOT11_WEP_ICV_ERROR_COUNT                    = (OID_DOT11_NDIS_START + 29)
Dim OID_DOT11_MAC_ADDRESS                          : OID_DOT11_MAC_ADDRESS                            = (OID_DOT11_NDIS_START + 30)
Dim OID_DOT11_RTS_THRESHOLD                        : OID_DOT11_RTS_THRESHOLD                          = (OID_DOT11_NDIS_START + 31)
Dim OID_DOT11_SHORT_RETRY_LIMIT                    : OID_DOT11_SHORT_RETRY_LIMIT                      = (OID_DOT11_NDIS_START + 32)
Dim OID_DOT11_LONG_RETRY_LIMIT                     : OID_DOT11_LONG_RETRY_LIMIT                       = (OID_DOT11_NDIS_START + 33)
Dim OID_DOT11_FRAGMENTATION_THRESHOLD              : OID_DOT11_FRAGMENTATION_THRESHOLD                = (OID_DOT11_NDIS_START + 34)
Dim OID_DOT11_MAX_TRANSMIT_MSDU_LIFETIME           : OID_DOT11_MAX_TRANSMIT_MSDU_LIFETIME             = (OID_DOT11_NDIS_START + 35)
Dim OID_DOT11_MAX_RECEIVE_LIFETIME                 : OID_DOT11_MAX_RECEIVE_LIFETIME                   = (OID_DOT11_NDIS_START + 36)
Dim OID_DOT11_COUNTERS_ENTRY                       : OID_DOT11_COUNTERS_ENTRY                         = (OID_DOT11_NDIS_START + 37)
Dim OID_DOT11_SUPPORTED_PHY_TYPES                  : OID_DOT11_SUPPORTED_PHY_TYPES                    = (OID_DOT11_NDIS_START + 38)
Dim OID_DOT11_CURRENT_REG_DOMAIN                   : OID_DOT11_CURRENT_REG_DOMAIN                     = (OID_DOT11_NDIS_START + 39)
Dim OID_DOT11_TEMP_TYPE                            : OID_DOT11_TEMP_TYPE                              = (OID_DOT11_NDIS_START + 40)
Dim OID_DOT11_CURRENT_TX_ANTENNA                   : OID_DOT11_CURRENT_TX_ANTENNA                     = (OID_DOT11_NDIS_START + 41)
Dim OID_DOT11_DIVERSITY_SUPPORT                    : OID_DOT11_DIVERSITY_SUPPORT                      = (OID_DOT11_NDIS_START + 42)
Dim OID_DOT11_CURRENT_RX_ANTENNA                   : OID_DOT11_CURRENT_RX_ANTENNA                     = (OID_DOT11_NDIS_START + 43)
Dim OID_DOT11_SUPPORTED_POWER_LEVELS               : OID_DOT11_SUPPORTED_POWER_LEVELS                 = (OID_DOT11_NDIS_START + 44)
Dim OID_DOT11_CURRENT_TX_POWER_LEVEL               : OID_DOT11_CURRENT_TX_POWER_LEVEL                 = (OID_DOT11_NDIS_START + 45)
Dim OID_DOT11_HOP_TIME                             : OID_DOT11_HOP_TIME                               = (OID_DOT11_NDIS_START + 46)
Dim OID_DOT11_CURRENT_CHANNEL_NUMBER               : OID_DOT11_CURRENT_CHANNEL_NUMBER                 = (OID_DOT11_NDIS_START + 47)
Dim OID_DOT11_MAX_DWELL_TIME                       : OID_DOT11_MAX_DWELL_TIME                         = (OID_DOT11_NDIS_START + 48)
Dim OID_DOT11_CURRENT_DWELL_TIME                   : OID_DOT11_CURRENT_DWELL_TIME                     = (OID_DOT11_NDIS_START + 49)
Dim OID_DOT11_CURRENT_SET                          : OID_DOT11_CURRENT_SET                            = (OID_DOT11_NDIS_START + 50)
Dim OID_DOT11_CURRENT_PATTERN                      : OID_DOT11_CURRENT_PATTERN                        = (OID_DOT11_NDIS_START + 51)
Dim OID_DOT11_CURRENT_INDEX                        : OID_DOT11_CURRENT_INDEX                          = (OID_DOT11_NDIS_START + 52)
Dim OID_DOT11_CURRENT_CHANNEL                      : OID_DOT11_CURRENT_CHANNEL                        = (OID_DOT11_NDIS_START + 53)
Dim OID_DOT11_CCA_MODE_SUPPORTED                   : OID_DOT11_CCA_MODE_SUPPORTED                     = (OID_DOT11_NDIS_START + 54)
Dim OID_DOT11_CURRENT_CCA_MODE                     : OID_DOT11_CURRENT_CCA_MODE                       = (OID_DOT11_NDIS_START + 55)
Dim OID_DOT11_ED_THRESHOLD                         : OID_DOT11_ED_THRESHOLD                           = (OID_DOT11_NDIS_START + 56)
Dim OID_DOT11_CCA_WATCHDOG_TIMER_MAX               : OID_DOT11_CCA_WATCHDOG_TIMER_MAX                 = (OID_DOT11_NDIS_START + 57)
Dim OID_DOT11_CCA_WATCHDOG_COUNT_MAX               : OID_DOT11_CCA_WATCHDOG_COUNT_MAX                 = (OID_DOT11_NDIS_START + 58)
Dim OID_DOT11_CCA_WATCHDOG_TIMER_MIN               : OID_DOT11_CCA_WATCHDOG_TIMER_MIN                 = (OID_DOT11_NDIS_START + 59)
Dim OID_DOT11_CCA_WATCHDOG_COUNT_MIN               : OID_DOT11_CCA_WATCHDOG_COUNT_MIN                 = (OID_DOT11_NDIS_START + 60)
Dim OID_DOT11_REG_DOMAINS_SUPPORT_VALUE            : OID_DOT11_REG_DOMAINS_SUPPORT_VALUE              = (OID_DOT11_NDIS_START + 61)
Dim OID_DOT11_SUPPORTED_TX_ANTENNA                 : OID_DOT11_SUPPORTED_TX_ANTENNA                   = (OID_DOT11_NDIS_START + 62)
Dim OID_DOT11_SUPPORTED_RX_ANTENNA                 : OID_DOT11_SUPPORTED_RX_ANTENNA                   = (OID_DOT11_NDIS_START + 63)
Dim OID_DOT11_DIVERSITY_SELECTION_RX               : OID_DOT11_DIVERSITY_SELECTION_RX                 = (OID_DOT11_NDIS_START + 64)
Dim OID_DOT11_SUPPORTED_DATA_RATES_VALUE           : OID_DOT11_SUPPORTED_DATA_RATES_VALUE             = (OID_DOT11_NDIS_START + 65)
Dim OID_DOT11_CURRENT_FREQUENCY                    : OID_DOT11_CURRENT_FREQUENCY                      = (OID_DOT11_NDIS_START + 66)
Dim OID_DOT11_TI_THRESHOLD                         : OID_DOT11_TI_THRESHOLD                           = (OID_DOT11_NDIS_START + 67)
Dim OID_DOT11_FREQUENCY_BANDS_SUPPORTED            : OID_DOT11_FREQUENCY_BANDS_SUPPORTED              = (OID_DOT11_NDIS_START + 68)
Dim OID_DOT11_SHORT_PREAMBLE_OPTION_IMPLEMENTED    : OID_DOT11_SHORT_PREAMBLE_OPTION_IMPLEMENTED      = (OID_DOT11_NDIS_START + 69)
Dim OID_DOT11_PBCC_OPTION_IMPLEMENTED              : OID_DOT11_PBCC_OPTION_IMPLEMENTED                = (OID_DOT11_NDIS_START + 70)
Dim OID_DOT11_CHANNEL_AGILITY_PRESENT              : OID_DOT11_CHANNEL_AGILITY_PRESENT                = (OID_DOT11_NDIS_START + 71)
Dim OID_DOT11_CHANNEL_AGILITY_ENABLED              : OID_DOT11_CHANNEL_AGILITY_ENABLED                = (OID_DOT11_NDIS_START + 72)
Dim OID_DOT11_HR_CCA_MODE_SUPPORTED                : OID_DOT11_HR_CCA_MODE_SUPPORTED                  = (OID_DOT11_NDIS_START + 73)
Dim OID_DOT11_MULTI_DOMAIN_CAPABILITY_IMPLEMENTED  : OID_DOT11_MULTI_DOMAIN_CAPABILITY_IMPLEMENTED    = (OID_DOT11_NDIS_START + 74)
Dim OID_DOT11_MULTI_DOMAIN_CAPABILITY_ENABLED      : OID_DOT11_MULTI_DOMAIN_CAPABILITY_ENABLED        = (OID_DOT11_NDIS_START + 75)
Dim OID_DOT11_COUNTRY_STRING                       : OID_DOT11_COUNTRY_STRING                         = (OID_DOT11_NDIS_START + 76)
Dim OID_DOT11_MULTI_DOMAIN_CAPABILITY              : OID_DOT11_MULTI_DOMAIN_CAPABILITY                = (OID_DOT11_NDIS_START + 77)
Dim OID_DOT11_EHCC_PRIME_RADIX                     : OID_DOT11_EHCC_PRIME_RADIX                       = (OID_DOT11_NDIS_START + 78)
Dim OID_DOT11_EHCC_NUMBER_OF_CHANNELS_FAMILY_INDEX : OID_DOT11_EHCC_NUMBER_OF_CHANNELS_FAMILY_INDEX   = (OID_DOT11_NDIS_START + 79)
Dim OID_DOT11_EHCC_CAPABILITY_IMPLEMENTED          : OID_DOT11_EHCC_CAPABILITY_IMPLEMENTED            = (OID_DOT11_NDIS_START + 80)
Dim OID_DOT11_EHCC_CAPABILITY_ENABLED              : OID_DOT11_EHCC_CAPABILITY_ENABLED                = (OID_DOT11_NDIS_START + 81)
Dim OID_DOT11_HOP_ALGORITHM_ADOPTED                : OID_DOT11_HOP_ALGORITHM_ADOPTED                  = (OID_DOT11_NDIS_START + 82)
Dim OID_DOT11_RANDOM_TABLE_FLAG                    : OID_DOT11_RANDOM_TABLE_FLAG                      = (OID_DOT11_NDIS_START + 83)
Dim OID_DOT11_NUMBER_OF_HOPPING_SETS               : OID_DOT11_NUMBER_OF_HOPPING_SETS                 = (OID_DOT11_NDIS_START + 84)
Dim OID_DOT11_HOP_MODULUS                          : OID_DOT11_HOP_MODULUS                            = (OID_DOT11_NDIS_START + 85)
Dim OID_DOT11_HOPPING_PATTERN                      : OID_DOT11_HOPPING_PATTERN                        = (OID_DOT11_NDIS_START + 87)
Dim OID_DOT11_RANDOM_TABLE_FIELD_NUMBER            : OID_DOT11_RANDOM_TABLE_FIELD_NUMBER              = (OID_DOT11_NDIS_START + 88)
Dim OID_DOT11_WPA_TSC                              : OID_DOT11_WPA_TSC                                = (OID_DOT11_NDIS_START + 89)
Dim OID_DOT11_RSSI_RANGE                           : OID_DOT11_RSSI_RANGE                             = (OID_DOT11_NDIS_START + 90)
Dim OID_DOT11_RF_USAGE                             : OID_DOT11_RF_USAGE                               = (OID_DOT11_NDIS_START + 91)
Dim OID_DOT11_NIC_SPECIFIC_EXTENSION               : OID_DOT11_NIC_SPECIFIC_EXTENSION                 = (OID_DOT11_NDIS_START + 92)
Dim OID_DOT11_AP_JOIN_REQUEST                      : OID_DOT11_AP_JOIN_REQUEST                        = (OID_DOT11_NDIS_START + 93)

'-------------------------------------------------------------------------------------------------'
' The section below define a set of class used to descover OID info such as when the OID can
' be used and what PHY types it can be used with

Const N11_OID_QUERY              = &H00000001&
Const N11_OID_SET                = &H00000002&

Const N11_PHY_TYPE_ANY           = &H00000001&
Const N11_PHY_TYPE_FHSS          = &H00000002&
Const N11_PHY_TYPE_DSSS          = &H00000004&
Const N11_PHY_TYPE_IRBASEBAND    = &H00000008&
Const N11_PHY_TYPE_OFDM          = &H00000010&
Const N11_PHY_TYPE_HRDSSS        = &H00000020&

'#################################################################################################'
Class COID
   Private   m_oid
   Private   m_oidName
   Private   m_structtureName
   Private   m_requestTypes
   Private   m_modes
   Private   m_phy
   
   '================================================================================================='
   Public Property Get vbPHY
      vbPHY = m_phy
   End Property 
   
   '================================================================================================='
   Public Property Get vbModes
      vbModes = m_modes
   End Property 
   
   '================================================================================================='
   Public Property Get vbOID
      vbOID = m_oid
   End Property 
   
   '================================================================================================='
   Public Property Get vbOIDName
      vbOIDName = m_oidName
   End Property 
   
   '================================================================================================='
   Public Property Get vbStructureName
      vbStructureName = m_structtureName
   End Property
   
   '================================================================================================='
   Public Property Get vbRequestTypes
      vbRequestTypes = m_requestTypes
   End Property 
   
   '================================================================================================='
   Public Sub Class_Initialize()
   
   End Sub
   
   '================================================================================================='
   Function Add(byval oid, byval oidName, byval structureName, byval requestTypes, byval modes, byval phy)
      
      m_oid             = oid
      m_oidName         = oidName
      m_structtureName  = structureName
      m_requestTypes    = requestTypes
      m_modes           = modes
      m_phy             = phy
   
   End Function
   
End Class

'#################################################################################################'
Class COIDInfo
   
   Private m_oidList
   
   '================================================================================================='
   Public Sub Class_Initialize()
      
      Set m_oidList = CreateObject("Scripting.Dictionary")
                 
      vbAddOIDToList OID_DOT11_RESET_REQUEST,                                           _
                     "OID_DOT11_RESET_REQUEST",                                         _
                     "Dot11ResetRequest",                                               _
                     N11_OID_SET,                                                       _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                       
      vbAddOIDToList OID_DOT11_CURRENT_OPERATION_MODE,                                  _
                     "OID_DOT11_CURRENT_OPERATION_MODE",                                _
                     "Dot11CurrentOperationMode",                                       _
                     N11_OID_QUERY Or N11_OID_SET,                                      _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                       
      vbAddOIDToList OID_DOT11_OPERATION_MODE_CAPABILITY,                               _
                     "OID_DOT11_OPERATION_MODE_CAPABILITY",                             _
                     "Dot11CurrentOperationMode",                                       _
                     N11_OID_QUERY,                                                     _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                       
      vbAddOIDToList OID_DOT11_START_REQUEST,                                           _
                     "OID_DOT11_START_REQUEST",                                         _
                     "Dot11StartRequest",                                               _
                     N11_OID_SET,                                                       _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                       
      vbAddOIDToList OID_DOT11_JOIN_REQUEST,                                            _
                     "OID_DOT11_JOIN_REQUEST",                                          _
                     "Dot11JoinRequest",                                                _
                     N11_OID_SET,                                                       _
                     DOT11_OPERATION_MODE_STATION,                                      _
                     N11_PHY_TYPE_ANY
                       
      vbAddOIDToList OID_DOT11_SUPPORTED_DATA_RATES_VALUE,                              _
                     "OID_DOT11_SUPPORTED_DATA_RATES_VALUE",                            _
                     "Dot11SupportedDataRatesValue",                                    _
                     N11_OID_QUERY,                                                     _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                        
      vbAddOIDToList OID_DOT11_SUPPORTED_PHY_TYPES,                                     _
                     "OID_DOT11_SUPPORTED_PHY_TYPES",                                   _
                     "Dot11SupportedPhyTypes",                                          _
                     N11_OID_QUERY,                                                     _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                     
      vbAddOIDToList OID_DOT11_AP_JOIN_REQUEST,                                         _
                     "OID_DOT11_AP_JOIN_REQUEST",                                       _
                     "Dot11APJoinRequest",                                              _
                     N11_OID_SET,                                                       _
                     DOT11_OPERATION_MODE_AP,                                           _
                     N11_PHY_TYPE_ANY
                     
      vbAddOIDToList OID_DOT11_NIC_POWER_STATE,                                         _
                     "OID_DOT11_NIC_POWER_STATE",                                       _
                     "",                                                                _
                     N11_OID_SET Or N11_OID_QUERY,                                      _
                     DOT11_OPERATION_MODE_AP Or DOT11_OPERATION_MODE_STATION,           _
                     N11_PHY_TYPE_ANY
                    
        
                 
   End Sub
   
   '================================================================================================='
   Public Sub Class_Terminate()
   
   End Sub
   
   '================================================================================================='
   '/**
   ' This function is called to create an COID class and initialize it, then the oid value and the 
   ' COID class will be added to a dictionary object where it can be retreived later
   ' @params
   ' ! number     OID value that will be used as the key in the dictionary object
   ' ! string     The string representation of the OID constant
   ' ! string     The string name of the structure objects progID used by this OID
   ' ! number     A bit mask of the request types this OID supports, this could be SET and\or QUERY
   ' ! number     A bit mask of the operational modes this OID can be used with
   ' ! number     A bit mask of the PHY types this OID can be used with
   ' */
   Private Function vbAddOIDToList(byval oid, byval oidName, byval structureName, byval requestType, byval opMode, byval phyTypes)
   Dim oidInfo : Set oidInfo  = New COID

      If(m_oidList.Exists(oid) = True) Then
         MsgBox "OID " & name & " already exists"
         Exit Function
      End If
      
      oidInfo.Add oid, oidName, structureName, requestType, opMode, phyTypes
      m_oidList.Add oid, oidInfo
      
   End Function
   
   '================================================================================================='
   '/**
   ' This function is called to return an existing COID class from the dictionary object
   ' @params
   ' ! number This is the OID value which is used as the key to look up the dictionary entry
   ' @returns
   ' A COID class if the entry is found in the dictionary, otherwise retuns nothing
   ' */
   Public Function vbGetOIDInfo(byval oid)
   Dim items   : items  = m_oidList.Items
   Dim keys    : keys   = m_oidList.Keys
   Dim index   : index  = 0
      
      Set vbGetOIDInfo = Nothing
      
      If(m_oidList.Exists(oid) = False) Then
         Exit Function
      End If
         
      For index = 0 To m_oidList.Count - 1
      
         If(keys(index) = oid) Then
            Set vbGetOIDInfo = items(index)
            Exit For
         End If
         
      Next
         
   End Function
   
End Class
'<!-- CRC = 0x194f5861 --->