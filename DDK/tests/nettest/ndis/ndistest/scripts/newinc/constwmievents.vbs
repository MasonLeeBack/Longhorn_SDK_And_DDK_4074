Option Explicit


' Event Type Constants
Const EVENT_MSNDIS_STATUS_MEDIA_SPECIFIC_INDICATION      = &H00000001&
Const EVENT_MSNDIS_STATUS_MEDIA_DISCONNECT               = &H00000002&
Const EVENT_MSNDIS_STATUS_MEDIA_CONNECT                  = &H00000003&
Const EVENT_MSNDIS_STATUS_RESETSTART                     = &H00000004&
Const EVENT_MSNDIS_STATUS_RESETEND                       = &H00000005&
Const EVENT_MSNDIS_NOTIFYADAPTERREMOVAL                  = &H00000006&
Const EVENT_MSNDIS_NOTIFYADAPTERARRIVAL                  = &H00000007&

' Event Data Type Constants                                  
Const EVENT_TYPE_DOT11_STATUS_INDICATION                 = &H00000001&
Const EVENT_TYPE_STRING                                  = &H00000002&
Const EVENT_TYPE_BOOLEAN                                 = &H00000003&

' Event Status Constants
Const EVENT_STATUS_SUCCESS                               = &H00000000&
'<!-- CRC = 0xf7e1d5e3 --->