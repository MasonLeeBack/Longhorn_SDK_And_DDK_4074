Option Explicit

' NDIS NSI NM provider interface information objects
Const   NDIS_NSI_MIN_OBJECT                = -1
Const   NDIS_NSI_INTERFACE_INFORMATION     = 0
Const   NDIS_NSI_INTERFACE_ENUM            = 1
Const   NDIS_NSI_INTERFACE_LOOKUP          = 2
Const   NDIS_NSI_IF_RCV_ADDRESS            = 3
Const   NDIS_NSI_STACK_IF_ENTRY            = 4
Const   NDIS_NSI_INVERTED_STACK_IF_ENTRY   = 5
Const   NDIS_NSI_NETWORK                   = 6
Const   NDIS_NSI_COMPARTMENT               = 7
Const   NDIS_NSI_MAX_OBJECT                = 8


' NSI Store types
Const   NSI_STORE_PERSISTENT               = 0
Const   NSI_STORE_ACTIVE                   = 1
Const   NSI_STORE_BOTH                     = 2
Const   NSI_STORE_CURRENT                  = 3
Const   NSI_STORE_MAX                      = 4

' NSI Get Action types
Const   NSI_GET_EXACT                      = 0
Const   NSI_GET_FIRST                      = 1
Const   NSI_GET_NEXT                       = 2
Const   NSI_GET_MAX                        = 3

' NSI Set Action types
Const   NSI_SET_DEFAULT                    = 0
Const   NSI_SET_CREATE_ONLY                = 1
Const   NSI_SET_CREATE_OR_SET              = 2
Const   NSI_SET_DELETE                     = 3
Const   NSI_SET_RESET                      = 4
Const   NSI_SET_CREATE_OR_SET_WITH_REFERENCE = 5
Const   NSI_SET_DELETE_WITH_REFERENCE      = 6
Const   NSI_SET_MAX                        = 7

' NSI Struct type - used for Get & Set Parameter calls
Const   NSI_STRUCT_RW                      = 0
Const   NSI_STRUCT_RODYNAMIC               = 1
Const   NSI_STRUCT_ROSTATIC                = 2
Const   NSI_STRUCT_MAX                     = 3

' NSI notification types
Const   NSI_PARAMETER_CHANGE      = 0
Const   NSI_ADD_INSTANCE          = 1
Const   NSI_DELETE_INSTANCE       = 2
Const   NSI_INITIAL_NOTIFICATION  = 3
Const   NSI_NOTIFICATION_MAX      = 4

' Stored change notification Get Actions
Const   NSI_NOTIF_GET_NORMAL      = 0  ' Get one event, do not delete
Const   NSI_NOTIF_GET_DELETE      = 1  ' Get one event, delete in kernel
Const   NSI_NOTIF_GET_RESET       = 2  ' Delete all stored kernel events
Const   NSI_NOTIF_PURGE_CONTEXT   = 3  ' Purge this context (lose this)


Const   SIZEOF_ULONG    = 4

'<!-- CRC = 0x04dcb1cb --->