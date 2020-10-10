'================================================================================================='
' This script defines all the WLAN related OIDS
' 
' Author:
' - David Harding
'
' Required Includes:
' - 
'================================================================================================='

Option Explicit

Const OID_802_11_BSSID                     	= &H0D010101&
Const OID_802_11_SSID                      	= &H0D010102&
Const OID_802_11_NETWORK_TYPES_SUPPORTED   	= &H0D010203&
Const OID_802_11_NETWORK_TYPE_IN_USE       	= &H0D010204&
Const OID_802_11_TX_POWER_LEVEL            	= &H0D010205&
Const OID_802_11_RSSI                      	= &H0D010206&
Const OID_802_11_RSSI_TRIGGER              	= &H0D010207&
Const OID_802_11_INFRASTRUCTURE_MODE       	= &H0D010108&
Const OID_802_11_FRAGMENTATION_THRESHOLD   	= &H0D010209&
Const OID_802_11_RTS_THRESHOLD             	= &H0D01020A&
Const OID_802_11_NUMBER_OF_ANTENNAS        	= &H0D01020B&
Const OID_802_11_RX_ANTENNA_SELECTED       	= &H0D01020C&
Const OID_802_11_TX_ANTENNA_SELECTED       	= &H0D01020D&
Const OID_802_11_SUPPORTED_RATES           	= &H0D01020E&
Const OID_802_11_DESIRED_RATES             	= &H0D010210&
Const OID_802_11_CONFIGURATION             	= &H0D010211&
Const OID_802_11_STATISTICS                	= &H0D020212&
Const OID_802_11_ADD_WEP                   	= &H0D010113&
Const OID_802_11_REMOVE_WEP                	= &H0D010114&
Const OID_802_11_WEP_STATUS                	= &H0D01011B&
Const OID_802_11_DISASSOCIATE              	= &H0D010115&
Const OID_802_11_POWER_MODE                	= &H0D010216&
Const OID_802_11_BSSID_LIST                	= &H0D010217&
Const OID_802_11_BSSID_LIST_SCAN           	= &H0D01011A&
Const OID_802_11_AUTHENTICATION_MODE       	= &H0D010118&
Const OID_802_11_PRIVACY_FILTER            	= &H0D010119&
Const OID_802_11_RELOAD_DEFAULTS           	= &H0D01011C&
Const OID_802_11_ENCRYPTION_STATUS        	= &H0D01011B&
Const OID_802_11_ADD_KEY                  	= &H0D01011D&
Const OID_802_11_REMOVE_KEY               	= &H0D01011E&
Const OID_802_11_ASSOCIATION_INFORMATION  	= &H0D01011F&
Const OID_802_11_TEST                     	= &H0D010120&



'<!-- CRC = 0x4d501151 --->