'==========================================================================
'
' NAME: ndisstatus.vbs
'
' AUTHOR: David Harding , Microsoft
' DATE  : 3/26/2001
'
'==========================================================================
Option Explicit

Const GEN_NDIS_REQUEST_FAILURE                = &H80000000&
Const GEN_CREATE_OBJECT_FAILURE               = &H80000001&

Const GENERIC_FAILURE                         = &H80000008&

Const NDIS_STATUS_SUCCESS                     = &H00000000&
Const NDIS_STATUS_PENDING                     = &H00000103&
Const NDIS_STATUS_NOT_RECOGNIZED              = &H00010001&
Const NDIS_STATUS_NOT_COPIED                  = &H00010002&
Const NDIS_STATUS_NOT_ACCEPTED                = &H00010003&
Const NDIS_STATUS_CALL_ACTIVE                 = &H00010007&

Const NDIS_STATUS_ONLINE                      = &H40010003&
Const NDIS_STATUS_RESET_START                 = &H40010004&
Const NDIS_STATUS_RESET_END                   = &H40010005&
Const NDIS_STATUS_RING_STATUS                 = &H40010006&
Const NDIS_STATUS_CLOSED                      = &H40010007&
Const NDIS_STATUS_WAN_LINE_UP                 = &H40010008& 
Const NDIS_STATUS_WAN_LINE_DOWN               = &H40010009&
Const NDIS_STATUS_WAN_FRAGMENT                = &H4001000A&
Const NDIS_STATUS_MEDIA_CONNECT               = &H4001000B&
Const NDIS_STATUS_MEDIA_DISCONNECT            = &H4001000C& 
Const NDIS_STATUS_HARDWARE_LINE_UP            = &H4001000D& 
Const NDIS_STATUS_HARDWARE_LINE_DOWN          = &H4001000E& 
Const NDIS_STATUS_INTERFACE_UP                = &H4001000F& 
Const NDIS_STATUS_INTERFACE_DOWN              = &H40010010& 
Const NDIS_STATUS_MEDIA_BUSY                  = &H40010011&
Const NDIS_STATUS_MEDIA_SPECIFIC_INDICATION   = &H40010012&
'Const NDIS_STATUS_WW_INDICATION               NDIS_STATUS_MEDIA_SPECIFIC_INDICATION
Const NDIS_STATUS_LINK_SPEED_CHANGE           = &H40010013&
Const NDIS_STATUS_WAN_GET_STATS               = &H40010014&
Const NDIS_STATUS_WAN_CO_FRAGMENT             = &H40010015&
Const NDIS_STATUS_WAN_CO_LINKPARAMS           = &H40010016&

Const NDIS_STATUS_NOT_RESETTABLE              = &H80010001&
Const NDIS_STATUS_SOFT_ERRORS                 = &H80010003&
Const NDIS_STATUS_HARD_ERRORS                 = &H80010004&
Const NDIS_STATUS_BUFFER_OVERFLOW             = &H80000005&

Const NDIS_STATUS_FAILURE                     = &HC0000001&
Const NDIS_STATUS_RESOURCES                   = &HC000009A&
Const NDIS_STATUS_CLOSING                     = &HC0010002&
Const NDIS_STATUS_BAD_VERSION                 = &HC0010004&
Const NDIS_STATUS_BAD_CHARACTERISTICS         = &HC0010005&
Const NDIS_STATUS_ADAPTER_NOT_FOUND           = &HC0010006&
Const NDIS_STATUS_OPEN_FAILED                 = &HC0010007&
Const NDIS_STATUS_DEVICE_FAILED               = &HC0010008&
Const NDIS_STATUS_MULTICAST_FULL              = &HC0010009&
Const NDIS_STATUS_MULTICAST_EXISTS            = &HC001000A&
Const NDIS_STATUS_MULTICAST_NOT_FOUND         = &HC001000B&
Const NDIS_STATUS_REQUEST_ABORTED             = &HC001000C&
Const NDIS_STATUS_RESET_IN_PROGRESS           = &HC001000D&
Const NDIS_STATUS_CLOSING_INDICATING          = &HC001000E&
Const NDIS_STATUS_NOT_SUPPORTED               = &HC00000BB&
Const NDIS_STATUS_INVALID_PACKET              = &HC001000F&
Const NDIS_STATUS_OPEN_LIST_FULL              = &HC0010010&
Const NDIS_STATUS_ADAPTER_NOT_READY           = &HC0010011&
Const NDIS_STATUS_ADAPTER_NOT_OPEN            = &HC0010012&
Const NDIS_STATUS_NOT_INDICATING              = &HC0010013&
Const NDIS_STATUS_INVALID_LENGTH              = &HC0010014&
Const NDIS_STATUS_INVALID_DATA                = &HC0010015&
Const NDIS_STATUS_BUFFER_TOO_SHORT            = &HC0010016&
Const NDIS_STATUS_INVALID_OID                 = &HC0010017&
Const NDIS_STATUS_ADAPTER_REMOVED             = &HC0010018&
Const NDIS_STATUS_UNSUPPORTED_MEDIA           = &HC0010019&
Const NDIS_STATUS_GROUP_ADDRESS_IN_USE        = &HC001001A&
Const NDIS_STATUS_FILE_NOT_FOUND              = &HC001001B&
Const NDIS_STATUS_ERROR_READING_FILE          = &HC001001C&
Const NDIS_STATUS_ALREADY_MAPPED              = &HC001001D&
Const NDIS_STATUS_RESOURCE_CONFLICT           = &HC001001E&
Const NDIS_STATUS_NO_CABLE                    = &HC001001F&

Const NDIS_STATUS_INVALID_SAP                 = &HC0010020&
Const NDIS_STATUS_SAP_IN_USE                  = &HC0010021&
Const NDIS_STATUS_INVALID_ADDRESS             = &HC0010022&
Const NDIS_STATUS_VC_NOT_ACTIVATED            = &HC0010023&
Const NDIS_STATUS_DEST_OUT_OF_ORDER           = &HC0010024&  ' cause 27
Const NDIS_STATUS_VC_NOT_AVAILABLE            = &HC0010025&  ' cause 35,45
Const NDIS_STATUS_CELLRATE_NOT_AVAILABLE      = &HC0010026&  ' cause 37
Const NDIS_STATUS_INCOMPATABLE_QOS            = &HC0010027&  ' cause 49
Const NDIS_STATUS_AAL_PARAMS_UNSUPPORTED      = &HC0010028&  ' cause 93
Const NDIS_STATUS_NO_ROUTE_TO_DESTINATION     = &HC0010029&  ' cause 3

Const NDIS_STATUS_CAPABILITY_UNAVAILABLE      = &HC0001114&
Const NDIS_STATUS_MEDIA_IN_USE                = &HC0001113&
Const NDIS_STATUS_INVALID_STATE               = &HC0001112&
Const NDIS_STATUS_POWER_STATE_INVALID         = &HC0001111&

Const NDIS_STATUS_TOKEN_RING_OPEN_ERROR       = &HC0011000&
'Const NDIS_STATUS_INVALID_DEVICE_REQUEST      = STATUS_INVALID_DEVICE_REQUEST)
'Const NDIS_STATUS_NETWORK_UNREACHABLE         = STATUS_NETWORK_UNREACHABLE)
Const NDT_STATUS_TIMEOUT                      = &H00000102&  ' STATUS_TIMEOUT from ntstatus.h

' Status codes added by vinaykul
Const NDIS_STATUS_MORE_ENTRIES                = &H00000105&
Const NDIS_STATUS_NO_MORE_ENTRIES             = &H8000001A&


'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
' NDISTest Status Codes
'++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Const NDT_STATUS_SUCCESS                     = &H00003000&
Const NDT_STATUS_ASSOCIATION_FAILED          = &H00003001&

' Creating a dictionary of NDIS_STATUS's so we can print the status name in the logs
Public Function vbGetNdisStatus(byref nStatus)
Dim oNdisStatus   : Set oNdisStatus = CreateObject("Scripting.Dictionary")

   oNdisStatus.Add NDIS_STATUS_SUCCESS,               "NDIS_STATUS_SUCCESS"
   oNdisStatus.Add NDIS_STATUS_PENDING,               "NDIS_STATUS_PENDING"
   oNdisStatus.Add NDIS_STATUS_FAILURE,               "NDIS_STATUS_FAILURE"
   oNdisStatus.Add NDIS_STATUS_RESOURCES,             "NDIS_STATUS_RESOURCES"
   oNdisStatus.Add NDIS_STATUS_NOT_SUPPORTED,         "NDIS_STATUS_NOT_SUPPORTED"
   oNdisStatus.Add NDIS_STATUS_ADAPTER_NOT_READY,     "NDIS_STATUS_ADAPTER_NOT_READY"
   oNdisStatus.Add NDIS_STATUS_INVALID_DATA,          "NDIS_STATUS_INVALID_DATA"
   oNdisStatus.Add NDIS_STATUS_NOT_ACCEPTED,          "NDIS_STATUS_NOT_ACCEPTED"
   oNdisStatus.Add NDIS_STATUS_INVALID_LENGTH,        "NDIS_STATUS_INVALID_LENGTH"
   oNdisStatus.Add NDIS_STATUS_DEVICE_FAILED,         "NDIS_STATUS_DEVICE_FAILED"
   oNdisStatus.Add NDIS_STATUS_BUFFER_TOO_SHORT,      "NDIS_STATUS_BUFFER_TOO_SHORT"
   oNdisStatus.Add NDIS_STATUS_INVALID_OID,           "NDIS_STATUS_INVALID_OID"
   oNdisStatus.Add GENERIC_FAILURE,                   "GENERIC_FAILURE"
   oNdisStatus.Add NDIS_STATUS_RESET_IN_PROGRESS,     "NDIS_STATUS_RESET_IN_PROGRESS"
   oNdisStatus.Add GEN_NDIS_REQUEST_FAILURE,          "GEN_NDIS_REQUEST_FAILURE"
   oNdisStatus.Add GEN_CREATE_OBJECT_FAILURE,         "GEN_CREATE_OBJECT_FAILURE"
   oNdisStatus.Add NDIS_STATUS_BUFFER_OVERFLOW,       "NDIS_STATUS_BUFFER_OVERFLOW"
   
   oNdisStatus.Add NDIS_STATUS_MEDIA_IN_USE,          "NDIS_STATUS_MEDIA_IN_USE"
   oNdisStatus.Add NDIS_STATUS_INVALID_STATE,         "NDIS_STATUS_INVALID_STATE"
   oNdisStatus.Add NDIS_STATUS_POWER_STATE_INVALID,   "NDIS_STATUS_POWER_STATE_INVALID"
   
   If(oNdisStatus.Exists(nStatus)) Then
      vbGetNdisStatus = " STATUS = " & oNdisStatus.Item(nStatus)
   Else
      vbGetNdisStatus = " STATUS = UNKNOWN_STATUS (0x" & Hex(nStatus) & ")"
   End If

End Function

'==================================================================================================
Public Function vbStatusToString(byref status)
Dim dictionary   : Set dictionary = CreateObject("Scripting.Dictionary")

   dictionary.Add NDIS_STATUS_SUCCESS,               "NDIS_STATUS_SUCCESS"
   dictionary.Add NDIS_STATUS_PENDING,               "NDIS_STATUS_PENDING"
   dictionary.Add NDIS_STATUS_FAILURE,               "NDIS_STATUS_FAILURE"
   dictionary.Add NDIS_STATUS_RESOURCES,             "NDIS_STATUS_RESOURCES"
   dictionary.Add NDIS_STATUS_NOT_SUPPORTED,         "NDIS_STATUS_NOT_SUPPORTED"
   dictionary.Add NDIS_STATUS_ADAPTER_NOT_READY,     "NDIS_STATUS_ADAPTER_NOT_READY"
   dictionary.Add NDIS_STATUS_INVALID_DATA,          "NDIS_STATUS_INVALID_DATA"
   dictionary.Add NDIS_STATUS_NOT_ACCEPTED,          "NDIS_STATUS_NOT_ACCEPTED"
   dictionary.Add NDIS_STATUS_INVALID_LENGTH,        "NDIS_STATUS_INVALID_LENGTH"
   dictionary.Add NDIS_STATUS_DEVICE_FAILED,         "NDIS_STATUS_DEVICE_FAILED"
   dictionary.Add NDIS_STATUS_BUFFER_TOO_SHORT,      "NDIS_STATUS_BUFFER_TOO_SHORT"
   dictionary.Add NDIS_STATUS_INVALID_OID,           "NDIS_STATUS_INVALID_OID"
   dictionary.Add GENERIC_FAILURE,                   "GENERIC_FAILURE"
   dictionary.Add NDIS_STATUS_RESET_IN_PROGRESS,     "NDIS_STATUS_RESET_IN_PROGRESS"
   dictionary.Add GEN_NDIS_REQUEST_FAILURE,          "GEN_NDIS_REQUEST_FAILURE"
   dictionary.Add GEN_CREATE_OBJECT_FAILURE,         "GEN_CREATE_OBJECT_FAILURE"
   dictionary.Add NDIS_STATUS_BUFFER_OVERFLOW,       "NDIS_STATUS_BUFFER_OVERFLOW"
   
   dictionary.Add NDIS_STATUS_MEDIA_IN_USE,          "NDIS_STATUS_MEDIA_IN_USE"
   dictionary.Add NDIS_STATUS_INVALID_STATE,         "NDIS_STATUS_INVALID_STATE"
   dictionary.Add NDIS_STATUS_POWER_STATE_INVALID,   "NDIS_STATUS_POWER_STATE_INVALID"
   dictionary.Add NDIS_STATUS_CAPABILITY_UNAVAILABLE,"NDIS_STATUS_CAPABILITY_UNAVAILABLE"
   
   dictionary.Add NDT_STATUS_SUCCESS,                 "NDT_STATUS_SUCCESS"
   dictionary.Add NDT_STATUS_ASSOCIATION_FAILED,      "NDT_STATUS_ASSOCIATION_FAILED"
     
   If(dictionary.Exists(status)) Then
      vbStatusToString = " (STATUS: " & dictionary.Item(status) & ")"
   Else
      vbStatusToString = " (STATUS: UNKNOWN_STATUS 0x" & Hex(status) & ")"
   End If

End Function


'<!-- CRC = 0xc48a872e --->