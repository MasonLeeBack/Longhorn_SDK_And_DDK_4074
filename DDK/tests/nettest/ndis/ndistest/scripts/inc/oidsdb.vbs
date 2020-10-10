'
' THIS is a HiGhLy CaSe SeNsItIvE file.
'
' Database tag format:
' [DATABASE INTERFACE[!|=]={WMI}|{NDISREQUEST}|{DEVIOCTL}|{WMIEVENTS}|{ALL}; MEDIA[!|=]=..; OIDSUPPORT[!|=]={REQUIRED}|{OPTIONAL}]
' Note that items withing a tag cannot contain spaces and are ofcourse case sensitive
'
' Database entry format:
' OIDHexVal, OIDString, DataLength, DataType, Required/Optional (OID), Set/Query (OID), Fault Severity (OID), ClassName (GUID), PropertyName (GUID), Set/Query (GUID), Fault Severity (GUID), WMIFlags (GUID)
' Items must be separated by a "," and 0 or 1 space.
'
' ALL ALL is not a good idea

'
' All the required general oids
'
[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==ALL; OIDSUPPORT==REQUIRED]
&H00010101, "OID_GEN_SUPPORTED_LIST", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010102, "OID_GEN_HARDWARE_STATUS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_HardwareStatus", "NdisHardwareStatus", "{5ec10354-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010103, "OID_GEN_MEDIA_SUPPORTED", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MediaSupported", "NdisMediaSupported#NumberElements", "{5ec10355-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000519
&H00010104, "OID_GEN_MEDIA_IN_USE", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MediaInUse", "NdisMediaInUse#NumberElements", "{5ec10356-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000519
&H00010105, "OID_GEN_MAXIMUM_LOOKAHEAD", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MaximumLookahead", "NdisMaximumLookahead", "{5ec10357-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010106, "OID_GEN_MAXIMUM_FRAME_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MaximumFrameSize", "NdisMaximumFrameSize", "{5ec10358-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010107, "OID_GEN_LINK_SPEED", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_LinkSpeed", "NdisLinkSpeed", "{5ec10359-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010108, "OID_GEN_TRANSMIT_BUFFER_SPACE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TransmitBufferSpace", "NdisTransmitBufferSpace", "{5ec1035a-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010109, "OID_GEN_RECEIVE_BUFFER_SPACE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_ReceiveBufferSpace", "NdisReceiveBufferSpace", "{5ec1035b-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0001010A, "OID_GEN_TRANSMIT_BLOCK_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TransmitBlockSize", "NdisTransmitBlockSize", "{5ec1035b-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0001010B, "OID_GEN_RECEIVE_BLOCK_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_ReceiveBlockSize", "NdisReceiveBlockSize", "{5ec1035d-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0001010D, "OID_GEN_VENDOR_DESCRIPTION", -1, STRINGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_VendorDescription", "NdisVendorDescription", "{5ec1035f-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000115
&H0001010F, "OID_GEN_CURRENT_LOOKAHEAD", 4, LONGDATA, QUERYSET, LOG_AS_WARN, "MSNdis_CurrentLookahead", "NdisCurrentLookahead", "{5ec10361-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010110, "OID_GEN_DRIVER_VERSION", 2, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_DriverVersion", "NdisDriverVersion", "{5ec10362-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010111, "OID_GEN_MAXIMUM_TOTAL_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MaximumTotalSize", "NdisMaximumTotalSize", "{5ec10363-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010113, "OID_GEN_MAC_OPTIONS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MacOptions", "NdisMacOptions", "{5ec10365-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010115, "OID_GEN_MAXIMUM_SEND_PACKETS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MaximumSendPackets", "NdisMaximumSendPackets", "{5ec10367-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010116, "OID_GEN_VENDOR_DRIVER_VERSION", 4, LONGDATA, QUERY_REQUEST, LOG_AS_WARN, "MSNdis_VendorDriverVersion", "NdisVendorDriverVersion", "{447956f9-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
[/DATABASE]

'
' This is the only settable guid in WMI
'
'[DATABASE INTERFACE==WMI; MEDIA!=NDISMEDIUMIRDA; OIDSUPPORT==OPTIONAL]
'&H0001021C, "OID_GEN_VLAN_ID", 4, LONGDATA, QUERYSET, LOG_AS_WARN, "MSNdis_VlanIdentifier", "NdisVlanId", "{765dc702-c5e8-4b67-84-3b-3f-5a-4f-f2-64-8b}", QUERYSET, LOG_AS_FAIL, &H00000011
'[/DATABASE]

'
' Oids that are actually required, but we allow irda devices to not support them (for now)
'
[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA!=NDISMEDIUMIRDA; OIDSUPPORT==REQUIRED]
&H0001010C, "OID_GEN_VENDOR_ID", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_VendorId", "NdisVendorID", "{5ec1035e-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0001010E, "OID_GEN_CURRENT_PACKET_FILTER", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_CurrentPacketFilter", "NdisCurrentPacketFilter", "{5ec10360-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00010114, "OID_GEN_MEDIA_CONNECT_STATUS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_MediaConnectStatus", "NdisMediaConnectStatus", "{5ec10366-a61a-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
'
'  Required statistics OIDs
'
&H00020101, "OID_GEN_XMIT_OK", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TransmitsOk", "NdisTransmitsOk", "{447956fa-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00020102, "OID_GEN_RCV_OK", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_ReceivesOk", "NdisReceivesOk", "{447956fb-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00020103, "OID_GEN_XMIT_ERROR", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TransmitsError", "NdisTransmitsError", "{447956fc-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00020104, "OID_GEN_RCV_ERROR", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_ReceiveError", "NdisReceiveError", "{447956fd-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H00020105, "OID_GEN_RCV_NO_BUFFER", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_ReceiveNoBuffer", "NdisReceiveNoBuffer", "{447956fe-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
[/DATABASE]

'
' Some optional general and statistical oids
'
[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==ALL; OIDSUPPORT==OPTIONAL]
&H00010117, "OID_GEN_SUPPORTED_GUIDS", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010118, "OID_GEN_NETWORK_LAYER_ADDRESSES", -1, OTHER, SET_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010202, "OID_GEN_PHYSICAL_MEDIUM", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_PhysicalMediumType", "NdisPhysicalMediumType", "{418ca16d-3937-4208-94-0a-ec-61-96-27-80-85}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0001021A, "OID_GEN_MACHINE_NAME", -1, STRINGDATA, SET_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010112, "OID_GEN_PROTOCOL_OPTIONS", 4, LONGDATA, SET_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010203, "OID_GEN_RECEIVE_SCALE_CAPABILITIES", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010204, "OID_GEN_RECEIVE_SCALE_PARAMETERS", -1, OTHER, QUERYSET, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010205, "OID_GEN_REQUIRED_BACKFILL_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000

' Optional statistics OIDs
&H00020201, "OID_GEN_DIRECTED_BYTES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020202, "OID_GEN_DIRECTED_FRAMES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020203, "OID_GEN_MULTICAST_BYTES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020204, "OID_GEN_MULTICAST_FRAMES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020205, "OID_GEN_BROADCAST_BYTES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020206, "OID_GEN_BROADCAST_FRAMES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020207, "OID_GEN_DIRECTED_BYTES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020208, "OID_GEN_DIRECTED_FRAMES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020209, "OID_GEN_MULTICAST_BYTES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002020A, "OID_GEN_MULTICAST_FRAMES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002020B, "OID_GEN_BROADCAST_BYTES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002020C, "OID_GEN_BROADCAST_FRAMES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002020D, "OID_GEN_RCV_CRC_ERROR", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002020E, "OID_GEN_TRANSMIT_QUEUE_LENGTH", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

'
' Media specific OIDs
'         

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==NDISMEDIUM802_3; OIDSUPPORT==REQUIRED]
&H01010101, "OID_802_3_PERMANENT_ADDRESS", 6, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetPermanentAddress", "NdisPermanentAddress", "{447956ff-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H01010102, "OID_802_3_CURRENT_ADDRESS", 6, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetCurrentAddress", "NdisCurrentAddress", "{44795700-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H01010103, "OID_802_3_MULTICAST_LIST", -1, ARRAYDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_EthernetMulticastList", "NdisMulticastList#NumberElements", "{44795701-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000519
&H01010104, "OID_802_3_MAXIMUM_LIST_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetMaximumMulticastListSize", "NdisEthernetMaximumMulticastListSize", "{44795702-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H01020101, "OID_802_3_RCV_ERROR_ALIGNMENT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetReceiveErrorAlignment", "NdisEthernetReceiveErrorAlignment", "{44795704-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H01020102, "OID_802_3_XMIT_ONE_COLLISION", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetOneTransmitCollision", "NdisEthernetOneTransmitCollision", "{44795705-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H01020103, "OID_802_3_XMIT_MORE_COLLISIONS", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetMoreTransmitCollisions", "NdisEthernetMoreTransmitCollisions", "{44795706-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==NDISMEDIUM802_3; OIDSUPPORT==OPTIONAL]
&H01010105, "OID_802_3_MAC_OPTIONS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_EthernetMacOptions", "NdisEthernetMacOptions", "{44795703-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H01020201, "OID_802_3_XMIT_DEFERRED", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H01020202, "OID_802_3_XMIT_MAX_COLLISIONS", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H01020203, "OID_802_3_RCV_OVERRUN", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H01020204, "OID_802_3_XMIT_UNDERRUN", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H01020205, "OID_802_3_XMIT_HEARTBEAT_FAILURE", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H01020206, "OID_802_3_XMIT_TIMES_CRS_LOST", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H01020207, "OID_802_3_XMIT_LATE_COLLISIONS", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==NDISMEDIUM802_5; OIDSUPPORT==REQUIRED]
&H02010101, "OID_802_5_PERMANENT_ADDRESS", 6, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingPermanentAddress", "NdisPermanentAddress", "{44795707-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02010102, "OID_802_5_CURRENT_ADDRESS", 6, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingCurrentAddress", "NdisCurrentAddress", "{44795708-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02010103, "OID_802_5_CURRENT_FUNCTIONAL", 4, ADDRESS, QUERYSET, LOG_AS_FAIL, "MSNdis_TokenRingCurrentFunctional", "NdisCurrentFunctional", "{44795709-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02010104, "OID_802_5_CURRENT_GROUP", 4, ADDRESS, QUERYSET, LOG_AS_FAIL, "MSNdis_TokenRingCurrentGroup", "NdisCurrentGroup", "{4479570a-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02010105, "OID_802_5_LAST_OPEN_STATUS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingLastOpenStatus", "NdisLastOpenStatus", "{4479570b-a61b-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02010106, "OID_802_5_CURRENT_RING_STATUS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingCurrentRingStatus", "NdisCurrentRingStatus", "{890a36ec-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02010107, "OID_802_5_CURRENT_RING_STATE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingCurrentRingState", "NdisCurrentRingState", "{acf14032-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02020101, "OID_802_5_LINE_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingLineErrors", "NdisLineErrors", "{acf14033-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H02020102, "OID_802_5_LOST_FRAMES", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_TokenRingLostFrames", "NdisLostFrames", "{acf14034-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL; MEDIA==NDISMEDIUM802_5; OIDSUPPORT==OPTIONAL]
&H02020201, "OID_802_5_BURST_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H02020202, "OID_802_5_AC_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H02020203, "OID_802_5_ABORT_DELIMITERS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H02020204, "OID_802_5_FRAME_COPIED_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H02020205, "OID_802_5_FREQUENCY_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H02020206, "OID_802_5_TOKEN_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H02020207, "OID_802_5_INTERNAL_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==NDISMEDIUMFDDI; OIDSUPPORT==REQUIRED]
&H03010101, "OID_FDDI_LONG_PERMANENT_ADDR", 6, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLongPermanentAddress", "NdisPermanentAddress", "{acf14035-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03010102, "OID_FDDI_LONG_CURRENT_ADDR", 6, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLongCurrentAddress", "NdisCurrentAddress", "{acf14036-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03010103, "OID_FDDI_LONG_MULTICAST_LIST", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLongMulticastList", "NdisMulticastList#NumberElements", "{acf14037-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000519
&H03010104, "OID_FDDI_LONG_MAX_LIST_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLongMaximumListSize", "NdisFddiLongMaximumListSize", "{acf14038-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020101, "OID_FDDI_ATTACHMENT_TYPE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiAttachmentType", "NdisFddiAttachmentType", "{acf1403d-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020102, "OID_FDDI_UPSTREAM_NODE_LONG", 6, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiUpstreamNodeLong", "NdisFddiUpstreamNodeLong", "{acf1403e-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020103, "OID_FDDI_DOWNSTREAM_NODE_LONG", 6, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiDownstreamNodeLong", "NdisFddiDownstreamNodeLong", "{acf1403f-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020104, "OID_FDDI_FRAME_ERRORS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiFrameErrors", "NdisFddiFrameErrors", "{acf14040-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020105, "OID_FDDI_FRAMES_LOST", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiFramesLost", "NdisFddiFramesLost", "{acf14041-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020106, "OID_FDDI_RING_MGT_STATE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiRingManagmentState", "NdisFddiRingManagmentState", "{acf14042-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020107, "OID_FDDI_LCT_FAILURES", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLctFailures", "NdisFddiLctFailures", "{acf14043-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020108, "OID_FDDI_LEM_REJECTS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLemRejects", "NdisFddiLemRejects", "{acf14044-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03020109, "OID_FDDI_LCONNECTION_STATE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiLConnectionState", "NdisFddiLConnectionState", "{acf14045-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==NDISMEDIUMFDDI; OIDSUPPORT==OPTIONAL]
&H03010105, "OID_FDDI_SHORT_PERMANENT_ADDR", 2, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiShortPermanentAddress", "NdisPermanentAddress", "{acf14039-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03010106, "OID_FDDI_SHORT_CURRENT_ADDR", 2, ADDRESS, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiShortCurrentAddress", "NdisCurrentAddress", "{acf1403a-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H03010107, "OID_FDDI_SHORT_MULTICAST_LIST", -1, ARRAYDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_FddiShortMulticastList", "NdisMulticastList#NumberElements", "{acf1403b-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000519
&H03010108, "OID_FDDI_SHORT_MAX_LIST_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_FddiShortMaximumListSize", "NdisFddiShortMaximumListSize", "{acf1403c-a61c-11d0-8d-d4-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL; MEDIA!=NDISMEDIUMIRDA; OIDSUPPORT==OPTIONAL]
&HFD010100, "OID_PNP_CAPABILITIES", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD010101, "OID_PNP_SET_POWER", 4, LONGDATA, SET_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD010102, "OID_PNP_QUERY_POWER", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD010103, "OID_PNP_ADD_WAKE_UP_PATTERN", -1, ARRAYDATA, SET_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD010104, "OID_PNP_REMOVE_WAKE_UP_PATTERN", -1, ARRAYDATA, SET_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD010105, "OID_PNP_WAKE_UP_PATTERN_LIST", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD010106, "OID_PNP_ENABLE_WAKE_UP", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD020200, "OID_PNP_WAKE_UP_OK", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&HFD020201, "OID_PNP_WAKE_UP_ERROR", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL; MEDIA==NDISMEDIUMIRDA; OIDSUPPORT==REQUIRED]
' OIDs that are supported only by Win 9x IRDA miniport drivers are not included
&H0A010101, "OID_IRDA_TURNAROUND_TIME", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0A010102, "OID_IRDA_SUPPORTED_SPEEDS", -1, ARRAYDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0A010103, "OID_IRDA_LINK_SPEED", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0A010104, "OID_IRDA_MEDIA_BUSY", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL; MEDIA==NDISMEDIUMIRDA; OIDSUPPORT==OPTIONAL] 
&H0A010200, "OID_IRDA_EXTRA_RCV_BOFS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0A010204, "OID_IRDA_MAX_RECEIVE_WINDOW_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0A010205, "OID_IRDA_MAX_SEND_WINDOW_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

' Keeping data type as other helps us ensure that we do not run our buffer/set tests on these
[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL,WMI; MEDIA==NDISPHYSICALMEDIUMWIRELESSLAN; OIDSUPPORT==REQUIRED]
&H0D010101, "OID_802_11_BSSID", 6, ADDRESS, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_BaseServiceSetIdentifier", "Ndis80211MacAddress", "{2504b6c2-1fa5-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010102, "OID_802_11_SSID", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_ServiceSetIdentifier", "Ndis80211SsId", "{7d2a90ea-2041-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010204, "OID_802_11_NETWORK_TYPE_IN_USE", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_NetworkTypeInUse", "Ndis80211NetworkTypeInUse", "{857e2326-2041-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010206, "OID_802_11_RSSI", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_ReceivedSignalStrength", "Ndis80211ReceivedSignalStrength", "{1507db16-2053-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0D010108, "OID_802_11_INFRASTRUCTURE_MODE", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_InfrastructureMode", "Ndis80211InfrastructureMode", "{697d5a7e-2062-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D01020E, "OID_802_11_SUPPORTED_RATES", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_DataRates", "Ndis80211DataRate", "{49db8722-2068-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0D010211, "OID_802_11_CONFIGURATION", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_Configuration", "Ndis80211Config", "{4a4df982-2068-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010113, "OID_802_11_ADD_WEP", -1, OTHER, SET_REQUEST, LOG_AS_FAIL, "MSNdis_80211_AddWEP", "KeyIndex#KeyLength#KeyMaterial#Length", "{4307bff0-2129-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000411
&H0D010114, "OID_802_11_REMOVE_WEP", -1, OTHER, SET_REQUEST, LOG_AS_FAIL, "MSNdis_80211_RemoveWEP", "Ndis80211KeyIndex", "{433c345c-2129-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D01011B, "OID_802_11_WEP_STATUS", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_WEPStatus", "Ndis80211WEPStatus", "{b027a21f-3cfa-4125-80-0b-3f-7a-18-fd-dc-dc}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010115, "OID_802_11_DISASSOCIATE", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_Disassociate", "", "{43671f40-2129-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010217, "OID_802_11_BSSID_LIST", -1, OTHER, SET_REQUEST, LOG_AS_FAIL, "MSNdis_80211_BSSIList", "Ndis80211BSSIList#NumberOfItems", "{69526f9a-2062-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000511
&H0D01011A, "OID_802_11_BSSID_LIST_SCAN", -1, OTHER, SET_REQUEST, LOG_AS_FAIL, "MSNdis_80211_BssIdListScan", "", "{0d9e01e1-ba70-11d4-b6-75-00-20-48-57-03-37}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010118, "OID_802_11_AUTHENTICATION_MODE", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_AuthenticationMode", "Ndis80211AuthenticationMode", "{43920a24-2129-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D01011C, "OID_802_11_RELOAD_DEFAULTS", -1, OTHER, SET_REQUEST, LOG_AS_FAIL, "MSNdis_80211_ReloadDefaults", "Ndis80211ReloadDefaults", "{748b14e8-32ee-4425-b9-1b-c9-84-8c-58-b5-5a}", QUERYSET, LOG_AS_FAIL, &H00000011
[/DATABASE]

[DATABASE INTERFACE==WMI; MEDIA==NDISPHYSICALMEDIUMWIRELESSLAN; OIDSUPPORT==OPTIONAL]
&H0D010203, "OID_802_11_NETWORK_TYPES_SUPPORTED", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_NetworkTypesSupported", "Ndis80211NetworkTypes#NumberOfItems", "{8531d6e6-2041-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000511
&H0D010216, "OID_802_11_POWER_MODE", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_PowerMode", "Ndis80211PowerMode", "{85be837c-2041-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010205, "OID_802_11_TX_POWER_LEVEL", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_TransmitPowerLevel", "Ndis80211TransmitPowerLevel", "{11e6ba76-2053-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010207, "OID_802_11_RSSI_TRIGGER", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_ReceivedSignalStrengthEventTrigger", "Ndis80211ReceivedSignalStrengthTrigger", "{155689b8-2053-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010209, "OID_802_11_FRAGMENTATION_THRESHOLD", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_FragmentationThreshold", "Ndis80211FragmentationThreshold", "{69aaa7c4-2062-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D01020A, "OID_802_11_RTS_THRESHOLD", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_RTSThreshold", "Ndis80211RTSThreshold", "{0134d07e-2064-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D01020B, "OID_802_11_NUMBER_OF_ANTENNAS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_NumberOfAntennas", "Ndis80211NumberOfAntennas", "{01779336-2064-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0D01020C, "OID_802_11_RX_ANTENNA_SELECTED", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_ReceiveAntennaSelected", "Ndis80211ReceiveAntennaSelected", "{01ac07a2-2064-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000111
&H0D01020D, "OID_802_11_TX_ANTENNA_SELECTED", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_TransmitAntennaSelected", "Ndis80211TransmitAntennaSelected", "{01dbb74a-2064-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D010210, "OID_802_11_DESIRED_RATES", -1, OTHER, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_DesiredDataRates", "Ndis80211DesiredRate", "{452ee08e-2536-11d4-97-eb-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
&H0D020212, "OID_802_11_STATISTICS", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "MSNdis_80211_Statistics", "ACKFailureCount#Active#FailedCount#FCSErrorCount#FrameDuplicateCount#InstanceName#MulticastReceivedFrameCount#MulticastTransmittedFrameCount#MultipleRetryCount#ReceivedFragmentCount#RetryCount#RTSFailureCount#RTSSuccessCount#StatisticsLength#TransmittedFragmentCount", "{42bb73b0-2129-11d4-97-eb-00-c0-4f-79-c4-03}", QUERY_REQUEST, LOG_AS_FAIL, &H00000511
&H0D010119, "OID_802_11_PRIVACY_FILTER", 4, LONGDATA, QUERYSET, LOG_AS_FAIL, "MSNdis_80211_PrivacyFilter", "Ndis80211PrivacyFilter", "{6733c4e9-4792-11d4-97-f1-00-c0-4f-79-c4-03}", QUERYSET, LOG_AS_FAIL, &H00000011
[/DATABASE]

[DATABASE INTERFACE==WMI; MEDIA==NDISGUIDS; OIDSUPPORT==NOTREQUIRED]
&HFFFFFFFF, "GUID_NDIS_ENUMERATE_ADAPTER", -1, OTHER, INVALID, INVALID, "MSNdis_EnumerateAdapter", "DeviceName", "{981f2d7f-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000190
&HFFFFFFFF, "GUID_NDIS_WAKE_ON_MAGIC_PACKET_ONLY", -1, OTHER, INVALID, INVALID, "MSNdis_DeviceWakeOnMagicPacketOnly", "EnableWakeOnMagicPacketOnly", "{a14f1c97-8839-4f8a-99-96-a2-89-96-eb-bf-1d}", QUERY_REQUEST, LOG_AS_FAIL, &H00000080
[/DATABASE]

[DATABASE INTERFACE==WMIEVENTS; MEDIA==NDISEVENTS; OIDSUPPORT==NOTREQUIRED]
&HFFFFFFFF, "NDIS_Notify_Adapter_Removal", -1, OTHER, INVALID, INVALID, "MSNdis_NotifyAdapterRemoval", "DeviceName", "{981f2d80-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Notify_Adapter_Arrival", -1, OTHER, INVALID, INVALID, "MSNdis_NotifyAdapterArrival", "DeviceName", "{981f2d81-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Status_Reset_Start", -1, OTHER, INVALID, INVALID, "MSNdis_StatusResetStart", "", "{981f2d76-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Status_Reset_End", -1, OTHER, INVALID, INVALID, "MSNdis_StatusResetEnd", "", "{981f2d77-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Status_Media_Disconnect", -1, OTHER, INVALID, INVALID, "MSNdis_StatusMediaDisconnect", "", "{981f2d7e-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Status_Media_Connect", -1, OTHER, INVALID, INVALID, "MSNdis_StatusMediaConnect", "", "{981f2d7d-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Status_Link_Speed_Change", -1, OTHER, INVALID, INVALID, "MSNdis_StatusLinkSpeedChange", "NdisStatusLinkSpeedChange", "{981f2d85-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000182
&HFFFFFFFF, "NDIS_Status_Media_Specific_Indication", -1, OTHER, INVALID, INVALID, "MSNdis_StatusMediaSpecificIndication", "NdisStatusMediaSpecificIndication#NumberElements", "{981f2d84-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000582
[/DATABASE]

' These are OIDs required by NDIS 6.0 miniports
[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL; MEDIA==ALL; OIDSUPPORT==NDIS6REQUIRED]
&H00010205, "OID_GEN_REQUIRED_BACKFILL_SIZE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010206, "OID_GEN_LINK_SPEED_EX", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010207, "OID_GEN_MAX_LINK_SPEED_EX", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010208, "OID_GEN_MEDIA_CONNECT_STATUS_EX", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010209, "OID_GEN_MEDIA_DUPLEX_STATE", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0001020A, "OID_GEN_SUPPORTED_PACKET_FILTERS", 4, LONGDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0001020B, "OID_GEN_LINK_STATE", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020106, "OID_GEN_STATISTICS", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

' These are optional OIDs that NDIS 6.0 miniports can support
[DATABASE INTERFACE==NDISREQUEST,DEVIOCTL; MEDIA==ALL; OIDSUPPORT==NDIS6OPTIONAL]
&H00010203, "OID_GEN_RECEIVE_SCALE_CAPABILITIES", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00010204, "OID_GEN_RECEIVE_SCALE_PARAMETERS", -1, OTHER, QUERYSET, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0001020C, "OID_GEN_ENUMERATE_PORTS", -1, OTHER, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0001020D, "OID_GEN_PORT_ATTRIBUTES", -1, OTHER, QUERYSET, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H00020219, "OID_GEN_BYTES_RCV", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002021A, "OID_GEN_BYTES_XMIT", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
&H0002021B, "OID_GEN_RCV_DISCARDS", -1, STATDATA, QUERY_REQUEST, LOG_AS_FAIL, "INVALID", "INVALID", "{FFFFFFFF-FFFF-FFFF-FF-FF-FF-FF-FF-FF-FF-FF}", INVALID, INVALID, &H00000000
[/DATABASE]

'[DATABASE INTERFACE==WMI; MEDIA==UNKNOWN; OIDSUPPORT==NOTREQUIRED]
'&HFFFFFFFF, "GUID_POWER_DEVICE_ENABLE", -1, OTHER, INVALID, INVALID, "MSNdis_", "", "{827c0a6f-feb0-11d0-bd-26-00-aa-00-b7-b3-2a}", QUERY_REQUEST, LOG_AS_FAIL, &H00000080
'&HFFFFFFFF, "GUID_POWER_DEVICE_WAKE_ENABLE", -1, OTHER, INVALID, INVALID, "MSNdis_", "", "{a9546a82-feb0-11d0-bd-26-00-aa-00-b7-b3-2a}", QUERY_REQUEST, LOG_AS_FAIL, &H00000080
'&HFFFFFFFF, "GUID_NDIS_ENUMERATE_VC", 0, OTHER, INVALID, INVALID, "MSNdis_NdisEnumerateVc", "", "{981f2d82-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H00000190
'&HFFFFFFFF, "GUID_NDIS_NOTIFY_VC_REMOVAL", 0, OTHER, INVALID, INVALID, "MSNdis_", "", "{981f2d79-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H000001C2
'&HFFFFFFFF, "GUID_NDIS_NOTIFY_VC_ARRIVAL", 0, OTHER, INVALID, INVALID, "MSNdis_", "", "{182f9e0c-b1f3-11d0-8d-d7-00-c0-4f-c3-35-8c}", QUERY_REQUEST, LOG_AS_FAIL, &H000001C2
'[/DATABASE]


'<!-- CRC = 0x0ec05ff1 --->