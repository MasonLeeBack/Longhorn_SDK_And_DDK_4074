Option Explicit

'
' Contains all the constants used by the NDTCore6 and NdisTest 6.0 protocol driver.
'

'------------------------------------------------------------------------------------
' These are the logging level controls
'------------------------------------------------------------------------------------
' Kernel Breakpoint levels
' Most serious breakpoint, generally enabled
Const FATAL_BREAK             = &H00000001
' Not totally fatal, but recommended (for internal debugging/problem states)
Const LEVEL1_BREAK            = &H00000002
' Breakpoint that would help in test failure debugging, but not vital
Const LEVEL2_BREAK            = &H00000004
' Enable assertions
Const ASSERT_ON_FAIL          = &H00000008

' Kernel Debugger log levels
' Enable serious output on kernel debugger
Const K_DBG_SERIOUS           = &H00000010
' Enable normal output on kernel debugger
Const K_DBG_NORMAL            = &H00000020
' Enable loud output on kernel debugger
Const K_DBG_LOUD              = &H00000040
' Enable debugger only logging messages
Const K_DBG_ONLY              = &H00000080

' Kernel Custom log levels
' These are the (kernel mode) logging levels for the custom logging mechanisms
' provided by the clients of the driver shell library.
' Enable serious output using custom logging
Const CUSTOM_LOG_SERIOUS      = &H00000100
' Enable normal output using custom logging
Const CUSTOM_LOG_NORMAL       = &H00000200
' Enable loud output using custom logging
Const CUSTOM_LOG_LOUD         = &H00000400
' Enable custom only logging messages
Const CUSTOM_LOG_ONLY         = &H00000800

' Kernel Tracing levels
' These are not the same as levels from the tracing mechanism, which should
' just have a single logging message TraceOut
' Enable serious output using tracing
Const K_TRACE_SERIOUS         = &H000001000
' Enable normal output using tracing
Const K_TRACE_NORMAL          = &H000002000
' Enable loud output using tracing
Const K_TRACE_LOUD            = &H000004000
' Enable trace only logging messages (unused, controlled using logman/tracelog)
Const K_TRACE_ONLY            = &H000008000

' User Debugger log levels
' Enable serious output on debugger
Const U_DBG_SERIOUS           = &H00010000
' Enable normal output on debugger
Const U_DBG_NORMAL            = &H00020000
' Enable loud output on debugger
Const U_DBG_LOUD              = &H00040000
' Enable entry/exit messages on debugger
Const U_DBG_ENTRY             = &H00080000

' User File logging levels (putting stuff into log file)
'
' These are the levels for writing messages into a log file.
' Enable writing regular messages into file
Const U_LOG_WRITE             = &H00100000
' Enable writing warnings into file
Const U_LOG_WARN              = &H00200000
' Enable writing failures into file
Const U_LOG_FAIL              = &H00400000
' Enable printing of results into the log file
Const U_LOG_RESULTS           = &H00800000

' User Tracing levels
' These are not the same as levels from the tracing mechanism, which
' just have a single logging message TraceOut
' Enable serious output using tracing
Const U_TRACE_SERIOUS         = &H01000000
' Enable normal output using tracing
Const U_TRACE_NORMAL          = &H02000000
' Enable loud output using tracing
Const U_TRACE_LOUD            = &H04000000

' Enable listening for WMI log messages from sys an write them to log
Const U_LOG_SYS_EVENTS        = &H08000000

' These are script contants for the logging levels we use
'
' The least stuff going to log file
Const SERIOUS_LOGGING_LEVEL   = &H01F1999B
' The normal logging that we use
Const NORMAL_LOGGING_LEVEL    = &H03F3BBBB
' The loud logging level
Const LOUD_LOGGING_LEVEL      = &H07F7FFFF

'------------------------------------------------------------------------------------
' These are the different kinds of communication managers that can be used by
' the CommEngine.lib and its clients.
'------------------------------------------------------------------------------------
Const    COMM_MGR_ABSENT            = 0
Const    SIMPLE_SEND_COMM_MGR       = 1
Const    PERFORMANCE_COMM_MGR       = 2
Const    SENDRECVTEST_COMM_MGR      = 3

'------------------------------------------------------------------------------------
' These are the different kinds of NetBuffer Constructors that are exported by
' the CommEngine.lib and its clients. These have to be bit fields in a 32 bit
' value, as we use them for confirming compatiblity between comm manager and
' the communication manager.
'------------------------------------------------------------------------------------
Const    CONSTRUCTOR_ABSENT         = 0
Const    NDISTEST_CONSTRUCTOR       = &H00000001&
Const    IP_PERF_CONSTRUCTOR        = &H00000002&
Const    SENDRECVTEST_CONSTRUCTOR   = &H00000004&
Const    IP_CONSTRUCTOR             = &H00000008&
Const    IP_RSS_CONSTRUCTOR         = &H00000010&
Const    NDISTEST_PERF_CONSTRUCTOR  = &H00000020&

'------------------------------------------------------------------------------------
' These are the different types of media module subtypes. These would always
' be considered along with the medium type. These have to be bit fields, as they
' are used for compatibility checking.
'------------------------------------------------------------------------------------
Const    MEDIA_MODULE_ABSENT                 = 0
Const    NDIS_MEDIUM_802_3_MEDIA_MODULE      = &H00000001&

'------------------------------------------------------------------------------------
' These are the different types of endpoints that are supported by the ndistest 6.0
'------------------------------------------------------------------------------------
Const    CLENDPOINT                 = 1
Const    CLENDPOINT_EX              = 2
Const    COENDPOINT                 = 3

'------------------------------------------------------------------------------------
' These are the different kinds of objects that can be used to create
' and verify IP options/extensions.
'------------------------------------------------------------------------------------
Const    RAW_IPV6_EXTENSION_HELPER  = 1

'------------------------------------------------------------------------------------
' These are the different kinds of traffic managers that can be used by
' the CommEngine.lib and its clients.
'------------------------------------------------------------------------------------
Const    TRAFFIC_MGR_ABSENT         = 0
Const    SIMPLE_TRAFFIC_MGR         = 1
Const    STRESS_TRAFFIC_MGR         = 2

'------------------------------------------------------------------------------------
' These are the different kinds of Net Buffer Module Stack that are exported by
' the CommEngine.lib and its clients. These have to be bit fields in a 32 bit
' value, as we use them for confirming compatiblity between traffic manager and
' the net buffer module stack manager
'------------------------------------------------------------------------------------
Const    NB_MODULE_STACK_ABSENT     = 0
Const    SIMPLE_NB_MODULE_STACK     = &H00000001&

'------------------------------------------------------------------------------------
' These are the different types of net buffer module subtypes.
'------------------------------------------------------------------------------------
Const    NET_BUFFER_MODULE_ABSENT   = 0
Const    SIMPLE_NB_ALLOCATOR_MODULE          = &H00000001&
Const    SIMPLE_NDISTEST_PAYLOAD_MODULE      = &H00000002&
Const    NDISTEST_HEADER_MODULE              = &H00000004&
Const    LLC_SNAP_HEADER_MODULE              = &H00000008&
Const    ETHERNET_MEDIA_HEADER_MODULE        = &H00000010&
Const    EMPTY_NB_ALLOCATOR_MODULE           = &H00000040&
Const    STRESS_PAYLOAD_MODULE               = &H00000080&

' The various object types whose statistics are held in statistics objects
' (Type field in the STATS_HEADER) (the first 3 are not supported)
Const   COMMUNICATION_MANAGER_OBJECT_CLASS   = 1
Const   NET_BUFFER_CONSTRUCTOR_OBJECT_CLASS  = 2
Const   MEDIA_MODULE_OBJECT_CLASS            = 3

Const   TRAFFIC_MANAGER_OBJECT_CLASS         = 4
Const   NET_BUFFER_MODULE_STACK_OBJECT_CLASS = 5
Const   NET_BUFFER_MODULE_OBJECT_CLASS       = 6

' These are the various types of send receive helpers available
Const    SIMPLE_SEND_RECEIVE_TRAFFIC         = 1
Const    STRESS_SEND_RECEIVE_TRAFFIC         = 2

'------------------------------------------------------------------------------------
' These are the flags that would be passed to requests (NdisRequest and NdisIoControl)
' They are used to obtain special behaviour in those calls
'------------------------------------------------------------------------------------

Const    fREQUEST_FLAG_PARAMETER_1           = &H00000001&
Const    fREQUEST_FLAG_PARAMETER_2           = &H00000002&
Const    fREQUEST_FLAG_PARAMETER_3           = &H00000003&
Const    fREQUEST_FLAG_PARAMETER_4           = &H00000004&
Const    fREQUEST_FLAG_PARAMETER_8           = &H00000008&

' Unalign the input buffer to the request by some byte
Const    fREQUEST_UNALIGN_IN_BUFFER          = &H00000010&
' Unalign the output buffer for the request by some byte
Const    fREQUEST_UNALIGN_OUT_BUFFER         = &H00000020&
' Fill the input buffer with a repeated pattern from 0 to 255
Const    fREQUEST_FILL_IN_BUFFER_PATTERN     = &H00000040&
' Fill the output buffer with a repeated pattern from 0 to 255
Const    fREQUEST_FILL_OUT_BUFFER_PATTERN    = &H00000080&

' Do not log the input parameters for this request
Const    fREQUEST_SILENCE_INPUT              = &H00000100&
' Do not log the response from the request
Const    fREQUEST_SILENCE_OUTPUT             = &H00000200&

' Do not adjust the size of the output buffer to handle the NDIS_STATISTICS_VALUE structure
Const    fREQUEST_NO_OUT_BUFFER_RESIZE       = &H00001000&
' Return the NDIS_STATISTICS_VALUE structure to the caller
Const    fREQUEST_RETURN_STAT_STRUCTURE      = &H00002000&
' Do not send request down if currently in reset
Const    fREQUEST_FAIL_ON_RESET              = &H00004000&


'
' Various mechanisms of doing sends
'
Const    SEND_AT_DISPATCH                    = 1
Const    SEND_AT_PASSIVE                     = 2
Const    SEND_AT_PASSIVE_AND_DISPATCH        = 3

'
' How long to wait looping for link to be established
'
Const    WAIT_FOR_LINK_TIME                  = 90


'
' Number of stack modules
'
Const    MAX_NET_BUFFER_MODULES_COUNT        = 32

'------------------------------------------------------------------------------------
' These are the flags decide how much verification we would do for any received
' packet
'------------------------------------------------------------------------------------
Const    fNDT_CONSTRUCTOR_CHECK_MEDIA_HEADER     = &H00000001&
Const    fNDT_CONSTRUCTOR_CHECK_NDISTEST_HEADER  = &H00000002&
Const    fNDT_CONSTRUCTOR_CHECK_NDISTEST_DATA    = &H00000004&
Const    fNDT_CONSTRUCTOR_CHECK_SEQUENCE_NUMBER  = &H00000008&

Const    fNDT_NDISTEST_VERIFY_NO_RSS_HASH_INFO   = &H00010000&

' This is an aggregation of the above symbols
Const    NDT_NDISTEST_DEFAULT_VERIFICATION       = &H0000000F&

Const    fNDT_CONSTRUCTOR_CHECK_IP_HEADER        = &H00000010&
Const    fNDT_CONSTRUCTOR_CHECK_IP_PROT_HEADER   = &H00000020&
Const    fNDT_CONSTRUCTOR_CHECK_IP_PROT_CHECKSUM = &H00000040&
Const    fNDT_CONSTRUCTOR_CHECK_IP_HEADER_ALIGN  = &H00000080&

' This is the default verification level for IP constructor
Const    NDT_IP_DEFAULT_VERIFICATION             = &H0000003F&

Const    fNDT_RSS_CONSTRUCTOR_CHECK_SEQUENCE     = &H00010000&
Const    fNDT_RSS_CONSTRUCTOR_CHECK_PROCESSOR_ON = &H00020000&
Const    fNDT_RSS_CONSTRUCTOR_CHECK_CACHING      = &H00040000&
Const    fNDT_RSS_CONSTRUCTOR_CHECK_HASH_INFO    = &H00080000&
Const    fNDT_RSS_CONSTRUCTOR_CHECK_HASH_VALUE   = &H00100000&
Const    fNDT_RSS_CONSTRUCTOR_CHECK_FIRST_HASH   = &H00200000&  ' Check hash for first packet
Const    fNDT_RSS_CONSTRUCTOR_CHECK_HASH_USED    = &H00400000&  ' Check hash for every packet
Const    fNDT_RSS_CONSTRUCTOR_ALLOW_NO_HASH      = &H00800000&  ' Allow no hashing

' This is the default verification level for RSS constructor (no regular
' ndistest packet sequence number verification)
Const    NDT_RSS_DEFAULT_VERIFICATION            = &H003F0037&

Const    NDT_RSS_MINIMAL_VERIFICATION            = &H00010037&

Const   fNDT_NB_MODULE_CHECK_MEDIA_HEADER        = &H00000001&
Const   fNDT_NB_MODULE_CHECK_NDISTEST_HEADER     = &H00000002&
Const   fNDT_NB_MODULE_CHECK_NDISTEST_DATA       = &H00000004&
Const   fNDT_NB_MODULE_CHECK_SEQUENCE_NUMBER     = &H00000008&
Const   fNDT_NB_MODULE_CHECK_IP_HEADER           = &H00000010&
Const   fNDT_NB_MODULE_CHECK_IP_PROT_HEADER      = &H00000020&
Const   fNDT_NB_MODULE_CHECK_IP_PROT_CHECKSUM    = &H00000040&
Const   fNDT_NB_MODULE_CHECK_IP_HEADER_ALIGN     = &H00000080&
Const   fNDT_STRESS_MODULE_CHECK_PAYLOAD_LENGTH  = &H00010000&   ' Only count, dont break

Const   NDT_STRESS_DEFAULT_VERIFICATION          = &H0001000E&   ' Header + seq no + data (no pad)
Const   NDT_STRESS_MINIMAL_VERIFICATION          = &H00010006&   ' Header + data corruption only

'------------------------------------------------------------------------------------
' Below are the Ndis 6.0 related constants (ie. not NDISTest 6.0)
'------------------------------------------------------------------------------------

Const    SEND_FLAGS_CHECK_FOR_LOOPBACK           = &H00000001&


'------------------------------------------------------------------------------
' Constants for CoNDIS, ATM, QoS
'------------------------------------------------------------------------------
Const    fPERMANENT_VC                           = &H00000001&
Const    fTRANSMIT_VC                            = &H00000004&
Const    fRECEIVE_VC                             = &H00000008&

' Various Address Families
' ------------------------
Const    CO_ADDRESS_FAMILY_Q2931                 = &H00000001& 
Const    CO_ADDRESS_FAMILY_PSCHED                = &H00000002& 
Const    CO_ADDRESS_FAMILY_L2TP                  = &H00000003&
Const    CO_ADDRESS_FAMILY_IRDA                  = &H00000004&
Const    CO_ADDRESS_FAMILY_1394                  = &H00000005&
Const    CO_ADDRESS_FAMILY_PPP                   = &H00000006&
Const    CO_ADDRESS_FAMILY_INFINIBAND            = &H00000007&
Const    CO_ADDRESS_FAMILY_TAPI                  = &H00000800&
Const    CO_ADDRESS_FAMILY_TAPI_PROXY            = &H00000801&

' Specific param type
' -------------------
Const    ATM_MEDIA_SPECIFIC                      = &H00000001&
Const    CALLMGR_SPECIFIC_Q2931                  = &H00000001&

' AAL type
' --------
Const    AAL_TYPE_AAL0                           = &H00000001&
Const    AAL_TYPE_AAL1                           = &H00000002&
Const    AAL_TYPE_AAL34                          = &H00000004&
Const    AAL_TYPE_AAL5                           = &H00000008&

' ATM Service category
' --------------------
Const    ATM_SERVICE_CATEGORY_CBR                = &H00000001&
Const    ATM_SERVICE_CATEGORY_VBR                = &H00000002&
Const    ATM_SERVICE_CATEGORY_UBR                = &H00000004&
Const    ATM_SERVICE_CATEGORY_ABR                = &H00000008&

' Qos Service Types
' -----------------
Const    SERVICETYPE_NOTRAFFIC                   = &H00000000&  
Const    SERVICETYPE_BESTEFFORT                  = &H00000001&
Const    SERVICETYPE_CONTROLLEDLOAD              = &H00000002& 
Const    SERVICETYPE_GUARANTEED                  = &H00000003& 
Const    SERVICETYPE_NETWORK_UNAVAILABLE         = &H00000004& 
Const    SERVICETYPE_GENERAL_INFORMATION         = &H00000005& 
Const    SERVICETYPE_NOCHANGE                    = &H00000006&
Const    SERVICETYPE_NONCONFORMING               = &H00000009& 
Const    SERVICETYPE_NETWORK_CONTROL             = &H0000000A& 
Const    SERVICETYPE_QUALITATIVE                 = &H0000000D& 




'<!-- CRC = 0x768516a2 --->