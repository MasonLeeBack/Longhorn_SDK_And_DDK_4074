Option Explicit

'--------------------------------------------------------------------------
' NOTE: Though all the variables in this script are constants, we cannot use Const for defining
' all of them because VBscript assigns a type to a literal based on the minimum number of bits
' it would require. So, a &H00000001& would be typed as an integer. However, this is not
' always the behavior we are interested in (eg DIRECTED filter), and hence we are declaring
' these constants as Dims and type casting them to a long.
'--------------------------------------------------------------------------

'Variable which could be global
Dim glMinimumPacketSize
glMinimumPacketSize = 64

' Defining new globals for wireless lan percent pass, the old values below should be removed
Const gWlanPercentToPassDirected       = 90
Const gWlanPercentToPassBroadcast      = 60

Dim glPercentToPass : glPercentToPass  = 95     ' %receives required to avoid failure of directed pkts

Const glPacketsPerBurst = 4             ' size of bursts for sendpackets. legal range is 1 to 8

Const glBurstsToSend = 25               ' number of bursts for sendpackets

Const glPacketsToSend = 100

' reduced throughput requirements for directed for wireless
Const glPercentToPassWLessDirected = 90

' even more reduced throughput requirements for broadcasts and multicasts for wireless
Const glPercentToPassWLessMulticast = 60

' reduced throughput requirements for directed for wireless wan
Const glPercentToPassWWANDirected = 85

' even more reduced throughput requirements for broadcasts and multicasts for wireless wan
Const glPercentToPassWWANMulticast = 60

' reduced throughput requirements for directed for powerline devices
Const glPercentToPassPowerLineDirected = 90

' reduced throughput requirements for broadcast and multicast for powerline devices
Const glPercentToPassPowerLineMulticast = 90

' Extra 10 second delay even if WaitForLink returned success
Const glWaitForLinkExtraDelay = 10000

' Added by Suyash Sinha for Irda tests
Const glIrdaMaxBurstSize = 4
Const glPercentToPassIrdaSlow = 85
Const glFastThreshold = 1000000
Const glPercentToPassIrdaFast = 80

' ways of returning packets from the sys
Const RETURNPACKETS    = 3
Const RELEASEPACKETS   = 4

' Defined schemas for holding packets
Const FIRSTCOUNT      = &H01 ' hold the first count packets
Const EVERYSECOND     = &H02 ' hold every second packet
Const EVERYTHIRD      = &H03 ' hold every third packet
Const HOLDRANDOM      = &H04 ' hold randomly
Const REFRESHRANDOM   = &H10 ' refresh randomly

'
' These are objects for Connection-oriented media call-managers.
'
Const OID_CO_ADD_PVC =		&HFE000001&
Const OID_CO_DELETE_PVC =		&HFE000002&
Const OID_CO_GET_CALL_INFORMATION = 	&HFE000003&
Const OID_CO_ADD_ADDRESS =		&HFE000004&
Const OID_CO_DELETE_ADDRESS =		&HFE000005&
Const OID_CO_GET_ADDRESSES =		&HFE000006&
Const OID_CO_ADDRESS_CHANGE =		&HFE000007&
Const OID_CO_SIGNALING_ENABLED =	&HFE000008&
Const OID_CO_SIGNALING_DISABLED =	&HFE000009&
Const OID_CO_AF_CLOSE =		&HFE00000A&

'
'  The following bits are defined for OID_PNP_ENABLE_WAKE_UP
'
Const WAKE_UP_MAGIC_PACKET   = &H00000001&
Const WAKE_UP_PATTERN_MATCH  = &H00000002&
Const WAKE_UP_LINK_CHANGE    = &H00000004&

' The follwoing bits are defined for the logging object (NDTLog.HTNL)
'
Const LOG_WRITE		       = &H000000001&
Const LOG_FAIL		          = &H000000002&
Const LOG_WARN		          = &H000000004&
Const LOG_COMMAND           = &H000000008&
Const LOG_VARIATION         = &H000000010&
Const LOG_ENTRY			    = &H000000020&
Const LOG_NORMAL            = &H000000040&
Const LOG_LOUD              = &H000000080&
Const LOG_SERIOUS           = &H000000100&
Const LOG_KERNEL_SERIOUS    = &H000000200&
Const LOG_KERNEL_NORMAL     = &H000000400&
Const LOG_KERNEL_LOUD       = &H000000800&
Const LOG_FORBID_FAILURES	 = &H000001000&
Const LOG_FORBID_WARNINGS   = &H000002000&



'
'  The following are 1394 specific
'
Const ADDRESS_FAMILY_1394 = 5
Const TRANSMIT_VC = 4
Const RECEIVE_VC = 8
Const BIDIRECTIONAL_VC = 12

Dim NIC1394_Channel, NIC1394_FIFO
NIC1394_Channel = Clng(0)
NIC1394_FIFO = Clng(1)

Dim BROADCAST_CHAN, ANY_CHAN
BROADCAST_CHAN = Clng(-2)
ANY_CHAN = Clng(-1)

Dim CHANNEL_ALLOCATE_FLAG
CHANNEL_ALLOCATE_FLAG = Clng(8)

'
' SKU's
'
Const VER_SERVER_NT                       = &H80000000&
Const VER_WORKSTATION_NT                  = &H40000000&
Const VER_SUITE_SMALLBUSINESS             = &H00000001&
Const VER_SUITE_ENTERPRISE                = &H00000002&
Const VER_SUITE_BACKOFFICE                = &H00000004&
Const VER_SUITE_COMMUNICATIONS            = &H00000008&
Const VER_SUITE_TERMINAL                  = &H00000010&
Const VER_SUITE_SMALLBUSINESS_RESTRICTED  = &H00000020&
Const VER_SUITE_EMBEDDEDNT                = &H00000040&
Const VER_SUITE_DATACENTER                = &H00000080&
Const VER_SUITE_SINGLEUSERTS              = &H00000100&
Const VER_SUITE_PERSONAL                  = &H00000200&
Const VER_SUITE_BLADE                     = &H00000400&

Const BIND_PROTOCOL              = 1
Const UNBIND_PROTOCOL            = 2
Const PROTOCOL_WAS_BOUND         = 1
Const PROTOCOL_WAS_UNBOUND       = 2

' Used in Update Atm Address
' If updating these values, also update corresponding values in open.h
Dim ADD, REMOVE
ADD                                 = CLng(1)
REMOVE                           = CLng(2)

' ATM address length and types
Dim ATM_NSAP, ATM_E164, ATM_ADDRESS_LENGTH, SIZEOF_ATM_ADDRESS
ATM_NSAP                          = CLng(0)
ATM_E164                          = CLng(1)
ATM_ADDRESS_LENGTH                = CLng(20)
SIZEOF_ATM_ADDRESS                = CLng(28)

Dim ADDRESS_FAMILY_Q2931
ADDRESS_FAMILY_Q2931              = 1

Dim NO_TRAFFIC, BEST_EFFORT, CONTROLLED_LOAD, GUARANTEED
NO_TRAFFIC = CLng(0)
BEST_EFFORT                       = CLng(1)
CONTROLLED_LOAD                   = CLng(2)
GUARANTEED                        = CLng(3)

Dim NETADDR_LENGTH
NETADDR_LENGTH                    = CLng(6)

' Task Offload info
Dim TCP_IP_CHECKSUM_OFFLOAD_TASK
TCP_IP_CHECKSUM_OFFLOAD_TASK      = CLng(1)
Dim TCP_LARGE_SEND_OFFLOAD_TASK
TCP_LARGE_SEND_OFFLOAD_TASK       = CLng(2)
Dim IPSEC_OFFLOAD_TASK
IPSEC_OFFLOAD_TASK                = CLng(3)
Dim ADD_SA
ADD_SA                            = CLng(4)
Dim DELETE_SA
DELETE_SA                         = CLng(5)

Dim OFFLOAD_VERSION
OFFLOAD_VERSION                   = CLng(&H00000001&)
Dim ENCAPSULATION
ENCAPSULATION                     = CLng(&H00000002&)
Dim FIXED_HEADER_SIZE
FIXED_HEADER_SIZE                 = CLng(&H00000004&)
Dim ENCAP_HDR_SIZE
ENCAP_HDR_SIZE                    = CLng(&H00000008&)

Const V4                                = 4
Const V6                                = 6

Dim V4_CKSUM
V4_CKSUM                          = CLng(&H00000001&)
Dim V6_CKSUM
V6_CKSUM                          = CLng(&H00000002&)
Dim TCP_CKSUM
TCP_CKSUM                         = CLng(&H00000004&)
Dim UDP_CKSUM
UDP_CKSUM                         = CLng(&H00000008&)
Dim IP_CKSUM
IP_CKSUM                          = CLng(&H00000010&)

Dim TCP_CKSUM_RX_FAILED
TCP_CKSUM_RX_FAILED               = CLng(&H00000001&)
Dim UDP_CKSUM_RX_FAILED
UDP_CKSUM_RX_FAILED               = CLng(&H00000002&)
Dim IP_CKSUM_RX_FAILED
IP_CKSUM_RX_FAILED                = CLng(&H00000004&)
Dim TCP_CKSUM_RX_SUCCEEDED
TCP_CKSUM_RX_SUCCEEDED            = CLng(&H00000008&)
Dim UDP_CKSUM_RX_SUCCEEDED
UDP_CKSUM_RX_SUCCEEDED            = CLng(&H00000010&)
Dim IP_CKSUM_RX_SUCCEEDED
IP_CKSUM_RX_SUCCEEDED             = CLng(&H00000020&)
Dim IP_CKSUM_RX_LOOPBK
IP_CKSUM_RX_LOOPBK                = CLng(&H00000040&)

'
' Per Packet Info
'
Dim CKSUM_OFFLOAD_TX
CKSUM_OFFLOAD_TX                  = CLng(&H00000001&)
Dim CKSUM_OFFLOAD_RX
CKSUM_OFFLOAD_RX                  = CLng(&H00000002&)
Dim MSS_TX
MSS_TX                            = CLng(&H00000004&)
Dim MSS_RX
MSS_RX                            = CLng(&H00000008&)


'
' The following are the transport protocol types
'
Const TCP                               = 6
Const UDP                               = 17
Const IP                                = 4      ' for IP tunneling in IPSec
Const ESP                               = 50     ' for IPSEC
Const AH                                = 51     ' for IPSEC
Const RAW_NDISTEST                      = 255    ' want to send raw ndistest 6.0 packets

'
' The two possible IP versions
'
Const IP_VERSION_4                      = 4
Const IP_VERSION_6                      = 6

'
' The IP versions to choose
'
Const ETHERTYPE_LENGTH                  = 0
Const ETHERTYPE_IPv4                    = &H0800&
Const ETHERTYPE_IPv6                    = &H86DD&

Dim MAX_IP_ADDR_LEN
MAX_IP_ADDR_LEN                   = CLng(6)

' IPv6 Extension header types
Const    IPv6_HOP_BY_HOP_OPTION_HEADER   = 0
Const    IPv6_ROUTING_HEADER             = 43
Const    IPv6_FRAGMENT_HEADER            = 44
Const    IPv6_ESP_HEADER                 = 50
Const    IPv6_AUTHENTICATION_HEADER      = 51
Const    IPv6_DESTINATION_OPTION_HEADER  = 60
Const    IPv6_NO_NEXT_HEADER             = 59

' IPv6 Extension options types
Const    IPv6_OPTION_PAD1                = 0
Const    IPv6_OPTION_PADN                = 1
Const    IPv6_OPTION_JUMBO               = 194
Const    IPv6_OPTION_BIND_UPDATE         = 198
Const    IPv6_OPTION_BIND_ACK            = 7
Const    IPv6_OPTION_BIND_REQUEST        = 8
Const    IPv6_OPTION_HOME_ADDR           = 201

Const IP_OPTION                        = &H01&
Const TCP_OPTIONS                       = &H02&

Const SERVER_CKSUM                      = &H80&
Const PSEUDO_CKSUM                      = &H01&
Const BOGUS_CKSUM                       = &H02&
Const SNAP_HDR                          = &H04&
Const DIX_HDR                           = &H08&


Dim lINTEGRITY_NONE
lINTEGRITY_NONE                    = CLng(&H0001&)
Dim lINTEGRITY_MD5
lINTEGRITY_MD5                     = CLng(&H0002&)
Dim lINTEGRITY_SHA
lINTEGRITY_SHA					  = CLng(&H0003&)
Dim lCONF_NONE
lCONF_NONE						  = CLng(&H8001&)
Dim lCONF_DES
lCONF_DES						  = CLng(&H8002&)
Dim lCONF_3DES
lCONF_3DES						  = CLng(&H8003& )

Dim TUNNEL_SA
TUNNEL_SA                         = CLng(&H0001&)
Dim TRANSPORT_SA
TRANSPORT_SA					  = CLng(&H0002&)
Dim INBOUND_SA
INBOUND_SA						  = CLng(&H0004&)
Dim OUTBOUND_SA
OUTBOUND_SA						  = CLng(&H0008&)
Dim USE_AH
USE_AH							  = CLng(&H8000&)
Dim USE_ESP
USE_ESP							  = CLng(&H4000&)

' QueryInfo modes in glbConst.hpp
Dim QUERY_GLOBAL_STATS
QUERY_GLOBAL_STATS                = CLng(0)
Dim QUERY_ALL_STATS
QUERY_ALL_STATS                   = CLng(1)
Dim QUERY_SELECTED_STATS
QUERY_SELECTED_STATS              = CLng(2)

Dim QUERY_SINGLE_INSTANCE
QUERY_SINGLE_INSTANCE     = CLng(0)
Dim QUERY_ALL_DATA
QUERY_ALL_DATA            = CLng(1)
Dim SET_SINGLE_INSTANCE
SET_SINGLE_INSTANCE       = CLng(2)



' receive options for SetReceiveoption in glbConst.hpp
Dim RECEIVE_NOCOPY
RECEIVE_NOCOPY                    = CLng(&H00000000&)
Dim RECEIVE_DEFAULT
RECEIVE_DEFAULT                   = CLng(&H00000000&)
Dim RECEIVE_LOOKAHEAD
RECEIVE_LOOKAHEAD                 = CLng(&H00000001&)
Dim RECEIVE_TRANSFER
RECEIVE_TRANSFER                  = CLng(&H00000002&)
Dim RECEIVE_PARTIAL_TRANSFER
RECEIVE_PARTIAL_TRANSFER          = CLng(&H00000003&)
Dim MAX_NDIS30_RECEIVE_OPTION
MAX_NDIS30_RECEIVE_OPTION         = CLng(&H00000003&)
Dim RECEIVE_PACKETIGNORE
RECEIVE_PACKETIGNORE              = CLng(&H00000004&)
Dim RECEIVE_LOCCOPY
RECEIVE_LOCCOPY                   = CLng(&H00000005&)
Dim RECEIVE_QUEUE
RECEIVE_QUEUE                     = CLng(&H00000006&)
Dim RECEIVE_DOUBLE_QUEUE
RECEIVE_DOUBLE_QUEUE              = CLng(&H00000007&)
Dim RECEIVE_TRIPLE_QUEUE
RECEIVE_TRIPLE_QUEUE              = CLng(&H00000008&)
Dim DEADLOCK_REPRO_FLAG
DEADLOCK_REPRO_FLAG               = CLng(&H00000009&)
Dim RECEIVE_QUEUE_RETURNS
RECEIVE_QUEUE_RETURNS             = CLng(&H0000000A&)
Dim RECEIVE_BREAK_BAD_PADDING
RECEIVE_BREAK_BAD_PADDING         = CLng(&H0000000B&)
Dim RECEIVE_ALLOW_BUSY_NET
RECEIVE_ALLOW_BUSY_NET            = CLng(&H80000000&)

' Ndis Packet Filter Bits (OID_GEN_CURRENT_PACKET_FILTER) in ntddndis.h
Dim DIRECTED
DIRECTED                          = CLng(&H00000001&)
Dim MULTICAST
MULTICAST                         = CLng(&H00000002&)
Dim ALL_MULTICAST
ALL_MULTICAST                     = CLng(&H00000004&)
Dim BROADCAST
BROADCAST                         = CLng(&H00000008&)
Dim SOURCE_ROUTING
SOURCE_ROUTING                    = CLng(&H00000010&)
Dim PROMISCUOUS
PROMISCUOUS                       = CLng(&H00000020&)
Dim SMT
SMT                               = CLng(&H00000040&)
Dim ALL_LOCAL
ALL_LOCAL                         = CLng(&H00000080&)
Dim GROUP_PKT
GROUP_PKT                         = CLng(&H00001000&)
Dim ALL_FUNCTIONAL
ALL_FUNCTIONAL                    = CLng(&H00002000&)
Dim FUNCTIONAL
FUNCTIONAL                        = CLng(&H00004000&)
Dim MAC_FRAME
MAC_FRAME                         = CLng(&H00008000&)

' NDIS_REQUEST_TYPE in ndis.h
Dim REQUEST_QUERY_INFO
REQUEST_QUERY_INFO                = CLng(0)
Dim REQUEST_SET_INFO
REQUEST_SET_INFO                  = CLng(1)
Dim REQUEST_QUERY_STATS
REQUEST_QUERY_STATS               = CLng(2)

' send failure types for GetSendResults
Dim SEND_FAILURES_FORBIDDEN
SEND_FAILURES_FORBIDDEN           = CLng(0)
Dim SEND_FAILURES_ALLOWED
SEND_FAILURES_ALLOWED             = CLng(1)
Dim SEND_FAILURES_REQUIRED
SEND_FAILURES_REQUIRED            = CLng(2)


' stress test option Constants
' packettype
Dim STRESS_FIXEDSIZE
STRESS_FIXEDSIZE                  = CLng(&H00000000&)  ' packets are fixed size
Dim STRESS_RANDOMSIZE
STRESS_RANDOMSIZE                 = CLng(&H00000001&)  ' packets are random size
Dim STRESS_CYCLICAL
STRESS_CYCLICAL                   = CLng(&H00000002&)  ' cycles from min to max
Dim STRESS_SMALLSIZE
STRESS_SMALLSIZE                  = CLng(&H00000003&)  ' random but small ( < 128)
Dim STRESS_EXTRASMALL
STRESS_EXTRASMALL                 = CLng(&H00000004&)  ' random small, including < 60 bytes


' packet makeup
Dim STRESS_RAND
STRESS_RAND                       = CLng(&H00000000&)  ' buffers random sized
Dim STRESS_SMALL
STRESS_SMALL                      = CLng(&H00000010&)  ' bufs random but small
Dim STRESS_ZEROS
STRESS_ZEROS                      = CLng(&H00000020&) ' bufs random many 0 len
Dim STRESS_ONES
STRESS_ONES                       = CLng(&H00000030&)  ' bufs random many 1 byte

' response type
Dim STRESS_FULLRESP
STRESS_FULLRESP                   = CLng(&H00000000&)  ' resend packet
Dim STRESS_NORESP
STRESS_NORESP                     = CLng(&H00000100&)  ' just count packet
Dim STRESS_ACK
STRESS_ACK                        = CLng(&H00000200&)  ' just ACK packet
Dim STRESS_ACK10
STRESS_ACK10                      = CLng(&H00000300&)  ' ACK packet 10 times

' windowing (speed control)
Dim STRESS_WINDOWING_ON
STRESS_WINDOWING_ON               = CLng(&H00000000&)
Dim STRESS_WINDOWING_OFF
STRESS_WINDOWING_OFF              = CLng(&H00001000&)


' verify received packets, or just count them
' (or'ed in with main options)
Dim PERFORM_VERIFY_RECEIVES
PERFORM_VERIFY_RECEIVES           = CLng(&H00000008&)
Dim PERFORM_INDICATE_RECEIVES
PERFORM_INDICATE_RECEIVES         = CLng(&H00000000&)

' main performance test options
Dim PERFORM_SENDONLY
PERFORM_SENDONLY                  = CLng(&H00000000&)  ' send to oblivion
Dim PERFORM_SEND
PERFORM_SEND                      = CLng(&H00000001&)  ' send to server
Dim PERFORM_SEND_AND_RECEIVE
PERFORM_SEND_AND_RECEIVE          = CLng(&H00000002&)  ' send and receive
Dim PERFORM_RECEIVE
PERFORM_RECEIVE                   = CLng(&H00000003&)  ' receive from server

'  Send Type of priority test
Dim PRIORITY_SEND
PRIORITY_SEND                     = CLng(&H0001&)
Dim PRIORITY_SEND_PACKETS
PRIORITY_SEND_PACKETS             = CLng(&H0002&)

' media type definitions for use with scripts
Dim NDISMEDIUM802_3
NDISMEDIUM802_3          = CLng(0)
Dim NDISMEDIUM802_5
NDISMEDIUM802_5          = CLng(1)
Dim NDISMEDIUMFDDI
NDISMEDIUMFDDI           = CLng(2)
Dim NDISMEDIUMWAN
NDISMEDIUMWAN            = CLng(3)
Dim NDISMEDIUMLOCALTALK
NDISMEDIUMLOCALTALK      = CLng(4)
Dim NDISMEDIUMDIX
NDISMEDIUMDIX            = CLng(5)
Dim NDISMEDIUMMODEM
NDISMEDIUMMODEM          = CLng(5)
Dim NDISMEDIUMARCNETRAW
NDISMEDIUMARCNETRAW      = CLng(6)
Dim NDISMEDIUMARCNET878_2
NDISMEDIUMARCNET878_2    = CLng(7)
Dim NDISMEDIUMATM
NDISMEDIUMATM            = CLng(8)
Dim NDISMEDIUMWIRELESSWAN
NDISMEDIUMWIRELESSWAN    = CLng(9)
Dim NDISMEDIUMIRDA
NDISMEDIUMIRDA           = CLng(10)
Dim NDISMEDIUMBPC
NDISMEDIUMBPC            = CLng(11)
Dim NDISMEDIUMCOWAN
NDISMEDIUMCOWAN          = CLng(12)
Dim NDISMEDIUM1394
NDISMEDIUM1394           = CLng(13)
Dim NDISMEDIUMMAX
NDISMEDIUMMAX            = CLng(14)

' physical medium definitions for use with scripts
Dim NDISPHYSICALMEDIUMRESERVED0
NDISPHYSICALMEDIUMRESERVED0    = CLng(0)
Dim NDISPHYSICALMEDIUMWIRELESSLAN
NDISPHYSICALMEDIUMWIRELESSLAN  = CLng(1)
Dim NDISPHYSICALMEDIUMCABLEMODEM
NDISPHYSICALMEDIUMCABLEMODEM   = CLng(2)
Dim NDISPHYSICALMEDIUMPHONELINE
NDISPHYSICALMEDIUMPHONELINE    = CLng(3)
Dim NDISPHYSICALMEDIUMPOWERLINE
NDISPHYSICALMEDIUMPOWERLINE    = CLng(4)
Dim NDISPHYSICALMEDIUMDSL
NDISPHYSICALMEDIUMDSL          = CLng(5)
Dim NDISPHYSICALMEDIUMFIBRECHANNEL
NDISPHYSICALMEDIUMFIBRECHANNEL = CLng(6)
Dim NDISPHYSICALMEDIUM1394
NDISPHYSICALMEDIUM1394         = CLng(7)
Dim NDISPHYSICALMEDIUMWIRELESSWAN
NDISPHYSICALMEDIUMWIRELESSWAN  = CLng(8)
Dim NDISPHYSICALMEDIUMNATIVE802_11
NDISPHYSICALMEDIUMNATIVE802_11 = CLng(9)
Dim NDISPHYSICALMEDIUMMAX
NDISPHYSICALMEDIUMMAX          = CLng(10)

' Unspecified is same as reserved
Dim NDISPHYSICALMEDIUMUNSPECIFIED
NDISPHYSICALMEDIUMUNSPECIFIED  = CLng(0)

'
' General Objects
'

'
'  Required OIDs
'
Const OID_GEN_SUPPORTED_LIST            = &H00010101&
Const OID_GEN_HARDWARE_STATUS           = &H00010102&
Const OID_GEN_MEDIA_SUPPORTED           = &H00010103&
Const OID_GEN_MEDIA_IN_USE              = &H00010104&
Const OID_GEN_MAXIMUM_LOOKAHEAD         = &H00010105&
Const OID_GEN_MAXIMUM_FRAME_SIZE        = &H00010106&
Const OID_GEN_LINK_SPEED                = &H00010107&
Const OID_GEN_TRANSMIT_BUFFER_SPACE     = &H00010108&
Const OID_GEN_RECEIVE_BUFFER_SPACE      = &H00010109&
Const OID_GEN_TRANSMIT_BLOCK_SIZE       = &H0001010A&
Const OID_GEN_RECEIVE_BLOCK_SIZE        = &H0001010B&
Const OID_GEN_VENDOR_ID                 = &H0001010C&
Const OID_GEN_VENDOR_DESCRIPTION        = &H0001010D&
Const OID_GEN_CURRENT_PACKET_FILTER     = &H0001010E&
Const OID_GEN_CURRENT_LOOKAHEAD         = &H0001010F&
Const OID_GEN_DRIVER_VERSION            = &H00010110&
Const OID_GEN_MAXIMUM_TOTAL_SIZE        = &H00010111&
Const OID_GEN_PROTOCOL_OPTIONS          = &H00010112&
Const OID_GEN_MAC_OPTIONS               = &H00010113&
Const OID_GEN_MEDIA_CONNECT_STATUS      = &H00010114&
Const OID_GEN_MAXIMUM_SEND_PACKETS      = &H00010115&
Const OID_GEN_VENDOR_DRIVER_VERSION     = &H00010116&
Const OID_GEN_SUPPORTED_GUIDS           = &H00010117&
Const OID_GEN_NETWORK_LAYER_ADDRESSES   = &H00010118&  ' Set only
Const OID_GEN_TRANSPORT_HEADER_OFFSET   = &H00010119&  ' Set only
Const OID_GEN_MACHINE_NAME              = &H0001021A&

'
'  Optional OIDs
'
Const OID_GEN_MEDIA_CAPABILITIES        = &H00010201&
Const OID_GEN_PHYSICAL_MEDIUM           = &H00010202&
Const OID_GEN_RECEIVE_SCALE_CAPABILITIES= &H00010203&
Const OID_GEN_RECEIVE_SCALE_PARAMETERS  = &H00010204&
Const OID_GEN_REQUIRED_BACKFILL_SIZE    = &H00010205&

'
'  Required statistics
'
Const OID_GEN_XMIT_OK                   = &H00020101&
Const OID_GEN_RCV_OK                    = &H00020102&
Const OID_GEN_XMIT_ERROR                = &H00020103&
Const OID_GEN_RCV_ERROR                 = &H00020104&
Const OID_GEN_RCV_NO_BUFFER             = &H00020105&

'
'  Optional statistics
'
Const OID_GEN_DIRECTED_BYTES_XMIT       = &H00020201&
Const OID_GEN_DIRECTED_FRAMES_XMIT      = &H00020202&
Const OID_GEN_MULTICAST_BYTES_XMIT      = &H00020203&
Const OID_GEN_MULTICAST_FRAMES_XMIT     = &H00020204&
Const OID_GEN_BROADCAST_BYTES_XMIT      = &H00020205&
Const OID_GEN_BROADCAST_FRAMES_XMIT     = &H00020206&
Const OID_GEN_DIRECTED_BYTES_RCV        = &H00020207&
Const OID_GEN_DIRECTED_FRAMES_RCV       = &H00020208&
Const OID_GEN_MULTICAST_BYTES_RCV       = &H00020209&
Const OID_GEN_MULTICAST_FRAMES_RCV      = &H0002020A&
Const OID_GEN_BROADCAST_BYTES_RCV       = &H0002020B&
Const OID_GEN_BROADCAST_FRAMES_RCV      = &H0002020C&

Const OID_GEN_RCV_CRC_ERROR             = &H0002020D&
Const OID_GEN_TRANSMIT_QUEUE_LENGTH     = &H0002020E&

Const OID_GEN_GET_TIME_CAPS             = &H0002020F&
Const OID_GEN_GET_NETCARD_TIME          = &H00020210&
Const OID_GEN_NETCARD_LOAD              = &H00020211&
Const OID_GEN_DEVICE_PROFILE            = &H00020212&

'
' The following is exported by NDIS itself and is only queryable. It returns
' the time in milliseconds a driver took to initialize.
'
Const OID_GEN_INIT_TIME_MS              = &H00020213&

Const OID_GEN_RESET_COUNTS              = &H00020214&
Const OID_GEN_MEDIA_SENSE_COUNTS        = &H00020215&
Const OID_GEN_FRIENDLY_NAME             = &H00020216&
Const OID_GEN_MINIPORT_INFO             = &H00020217&
Const OID_GEN_RESET_VERIFY_PARAMETERS   = &H00020218&


'
' flags used for OID_GEN_MINIPORT_INFO
'

Dim NDIS_MINIPORT_BUS_MASTER
NDIS_MINIPORT_BUS_MASTER                      = CLng(&H00000001&)
Dim NDIS_MINIPORT_WDM_DRIVER
NDIS_MINIPORT_WDM_DRIVER                      = CLng(&H00000002&)
Dim NDIS_MINIPORT_SG_LIST
NDIS_MINIPORT_SG_LIST                         = CLng(&H00000004&)
Dim NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY
NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY            = CLng(&H00000008&)
Dim NDIS_MINIPORT_INDICATES_PACKETS
NDIS_MINIPORT_INDICATES_PACKETS               = CLng(&H00000010&)
Dim NDIS_MINIPORT_IGNORE_PACKET_QUEUE
NDIS_MINIPORT_IGNORE_PACKET_QUEUE             = CLng(&H00000020&)
Dim NDIS_MINIPORT_IGNORE_REQUEST_QUEUE
NDIS_MINIPORT_IGNORE_REQUEST_QUEUE            = CLng(&H00000040&)
Dim NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS
NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS        = CLng(&H00000080&)
Dim NDIS_MINIPORT_INTERMEDIATE_DRIVER
NDIS_MINIPORT_INTERMEDIATE_DRIVER             = CLng(&H00000100&)
Dim NDIS_MINIPORT_IS_NDIS_5
NDIS_MINIPORT_IS_NDIS_5                       = CLng(&H00000200&)
Dim NDIS_MINIPORT_IS_CO
NDIS_MINIPORT_IS_CO                           = CLng(&H00000400&)
Dim NDIS_MINIPORT_DESERIALIZE
NDIS_MINIPORT_DESERIALIZE                     = CLng(&H00000800&)
Dim NDIS_MINIPORT_REQUIRES_MEDIA_POLLING
NDIS_MINIPORT_REQUIRES_MEDIA_POLLING          = CLng(&H00001000&)
Dim NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE
NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE            = CLng(&H00002000&)
Dim NDIS_MINIPORT_NETBOOT_CARD
NDIS_MINIPORT_NETBOOT_CARD                    = CLng(&H00004000&)
Dim NDIS_MINIPORT_PM_SUPPORTED
NDIS_MINIPORT_PM_SUPPORTED                    = CLng(&H00008000&)
Dim NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE
NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE  = CLng(&H00010000&)
Dim NDIS_MINIPORT_USES_SAFE_BUFFER_APIS
NDIS_MINIPORT_USES_SAFE_BUFFER_APIS           = CLng(&H00020000&)
Dim NDIS_MINIPORT_HIDDEN
NDIS_MINIPORT_HIDDEN                          = CLng(&H00040000&)
Dim NDIS_MINIPORT_SWENUM
NDIS_MINIPORT_SWENUM                          = CLng(&H00080000&)
Dim NDIS_MINIPORT_SURPRISE_REMOVE_OK
NDIS_MINIPORT_SURPRISE_REMOVE_OK              = CLng(&H00100000&)
Dim NDIS_MINIPORT_NO_HALT_ON_SUSPEND
NDIS_MINIPORT_NO_HALT_ON_SUSPEND              = CLng(&H00200000&)
Dim NDIS_MINIPORT_HARDWARE_DEVICE
NDIS_MINIPORT_HARDWARE_DEVICE                 = CLng(&H00400000&)
Dim NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS
NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS    = CLng(&H00800000&)
Dim NDIS_MINIPORT_64BITS_DMA
NDIS_MINIPORT_64BITS_DMA                      = CLng(&H01000000&)
Dim NDIS_MINIPORT_USE_NEW_BITS
NDIS_MINIPORT_USE_NEW_BITS                    = CLng(&H02000000&)
Dim NDIS_MINIPORT_EXCLUSIVE_INTERRUPT
NDIS_MINIPORT_EXCLUSIVE_INTERRUPT             = CLng(&H04000000&)
Dim NDIS_MINIPORT_SENDS_PACKET_ARRAY
NDIS_MINIPORT_SENDS_PACKET_ARRAY              = CLng(&H08000000&)
Dim NDIS_MINIPORT_FILTER_IM
NDIS_MINIPORT_FILTER_IM                       = CLng(&H10000000&)
Dim NDIS_MINIPORT_CHECK_PACKET_FILTER
NDIS_MINIPORT_CHECK_PACKET_FILTER             = CLng(&H20000000&)
' Some versions of NDIS also have this bit set if NDIS is padding short packets
Dim NDIS_MINIPORT_SHORT_PACKETS_ARE_PADDED
NDIS_MINIPORT_SHORT_PACKETS_ARE_PADDED        = CLng(&H20000000&)


'
' Ndis MAC option bits (OID_GEN_MAC_OPTIONS).
'
Dim NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA
NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA            = CLng(&H00000001&)
Dim NDIS_MAC_OPTION_RECEIVE_SERIALIZED
NDIS_MAC_OPTION_RECEIVE_SERIALIZED             = CLng(&H00000002&)
Dim NDIS_MAC_OPTION_TRANSFERS_NOT_PEND
NDIS_MAC_OPTION_TRANSFERS_NOT_PEND             = CLng(&H00000004&)
Dim NDIS_MAC_OPTION_NO_LOOPBACK
NDIS_MAC_OPTION_NO_LOOPBACK                    = CLng(&H00000008&)
Dim NDIS_MAC_OPTION_FULL_DUPLEX
NDIS_MAC_OPTION_FULL_DUPLEX                    = CLng(&H00000010&)
Dim NDIS_MAC_OPTION_EOTX_INDICATION
NDIS_MAC_OPTION_EOTX_INDICATION                = CLng(&H00000020&)
Dim NDIS_MAC_OPTION_8021P_PRIORITY
NDIS_MAC_OPTION_8021P_PRIORITY                 = CLng(&H00000040&)
Dim NDIS_MAC_OPTION_SUPPORTS_MAC_ADDRESS_OVERWRITE
NDIS_MAC_OPTION_SUPPORTS_MAC_ADDRESS_OVERWRITE = CLng(&H00000080&)
Dim NDIS_MAC_OPTION_RECEIVE_AT_DPC
NDIS_MAC_OPTION_RECEIVE_AT_DPC                 = CLng(&H00000100&)
Dim NDIS_MAC_OPTION_8021Q_VLAN
NDIS_MAC_OPTION_8021Q_VLAN                     = CLng(&H00000200&)
Dim NDIS_802_3_MAC_OPTION_PRIORITY
NDIS_802_3_MAC_OPTION_PRIORITY    = CLng(&H00000001&)

'
'  The following defines the device power states.
'
Dim NDISDEVICESTATEUNSPECIFIED
NDISDEVICESTATEUNSPECIFIED = CLng(0)
Dim NDISDEVICESTATED0
NDISDEVICESTATED0			= CLng(1)
Dim NDISDEVICESTATED1
NDISDEVICESTATED1			= CLng(2)
Dim NDISDEVICESTATED2
NDISDEVICESTATED2			= CLng(3)
Dim NDISDEVICESTATED3
NDISDEVICESTATED3			= CLng(4)

'
'  These are connection-oriented general OIDs.
'  These replace the above OIDs for connection-oriented media.
'
Const OID_GEN_CO_SUPPORTED_LIST         = &H00010101&
Const OID_GEN_CO_HARDWARE_STATUS        = &H00010102&
Const OID_GEN_CO_MEDIA_SUPPORTED        = &H00010103&
Const OID_GEN_CO_MEDIA_IN_USE           = &H00010104&
Const OID_GEN_CO_LINK_SPEED             = &H00010107&
Const OID_GEN_CO_VENDOR_ID              = &H0001010C&
Const OID_GEN_CO_VENDOR_DESCRIPTION     = &H0001010D&
Const OID_GEN_CO_DRIVER_VERSION         = &H00010110&
Const OID_GEN_CO_PROTOCOL_OPTIONS       = &H00010112&
Const OID_GEN_CO_MAC_OPTIONS            = &H00010113&
Const OID_GEN_CO_MEDIA_CONNECT_STATUS   = &H00010114&
Const OID_GEN_CO_VENDOR_DRIVER_VERSION  = &H00010116&
Const OID_GEN_CO_SUPPORTED_GUIDS        = &H00010117&
Const OID_GEN_CO_GET_TIME_CAPS          = &H0002020F&
Const OID_GEN_CO_GET_NETCARD_TIME       = &H00020210&
Const OID_GEN_CO_MINIMUM_LINK_SPEED     = &H00020120&

'
'	These are connection-oriented statistics OIDs.
'
Const OID_GEN_CO_XMIT_PDUS_OK			= &H00020101&
Const OID_GEN_CO_RCV_PDUS_OK				= &H00020102&
Const OID_GEN_CO_XMIT_PDUS_ERROR			= &H00020103&
Const OID_GEN_CO_RCV_PDUS_ERROR			= &H00020104&
Const OID_GEN_CO_RCV_PDUS_NO_BUFFER		= &H00020105&



'
' 802.3 Objects (Ethernet)
'
Const OID_802_3_PERMANENT_ADDRESS       = &H01010101&
Const OID_802_3_CURRENT_ADDRESS         = &H01010102&
Const OID_802_3_MULTICAST_LIST          = &H01010103&
Const OID_802_3_MAXIMUM_LIST_SIZE       = &H01010104&
Const OID_802_3_MAC_OPTIONS             = &H01010105&
Const OID_802_3_RCV_ERROR_ALIGNMENT     = &H01020101&
Const OID_802_3_XMIT_ONE_COLLISION      = &H01020102&
Const OID_802_3_XMIT_MORE_COLLISIONS    = &H01020103&
Const OID_802_3_XMIT_DEFERRED           = &H01020201&
Const OID_802_3_XMIT_MAX_COLLISIONS     = &H01020202&
Const OID_802_3_RCV_OVERRUN             = &H01020203&
Const OID_802_3_XMIT_UNDERRUN           = &H01020204&
Const OID_802_3_XMIT_HEARTBEAT_FAILURE  = &H01020205&
Const OID_802_3_XMIT_TIMES_CRS_LOST     = &H01020206&
Const OID_802_3_XMIT_LATE_COLLISIONS    = &H01020207&


'
' 802.5 Objects (Token-Ring)
'
Const OID_802_5_PERMANENT_ADDRESS       = &H02010101&
Const OID_802_5_CURRENT_ADDRESS         = &H02010102&
Const OID_802_5_CURRENT_FUNCTIONAL      = &H02010103&
Const OID_802_5_CURRENT_GROUP           = &H02010104&
Const OID_802_5_LAST_OPEN_STATUS        = &H02010105&
Const OID_802_5_CURRENT_RING_STATUS     = &H02010106&
Const OID_802_5_CURRENT_RING_STATE      = &H02010107&

Const OID_802_5_LINE_ERRORS             = &H02020101&
Const OID_802_5_LOST_FRAMES             = &H02020102&

Const OID_802_5_BURST_ERRORS            = &H02020201&
Const OID_802_5_AC_ERRORS               = &H02020202&
Const OID_802_5_ABORT_DELIMITERS        = &H02020203&
Const OID_802_5_FRAME_COPIED_ERRORS     = &H02020204&
Const OID_802_5_FREQUENCY_ERRORS        = &H02020205&
Const OID_802_5_TOKEN_ERRORS            = &H02020206&
Const OID_802_5_INTERNAL_ERRORS         = &H02020207&

'
' FDDI Objects
'
Const OID_FDDI_LONG_PERMANENT_ADDR      = &H03010101&
Const OID_FDDI_LONG_CURRENT_ADDR        = &H03010102&
Const OID_FDDI_LONG_MULTICAST_LIST      = &H03010103&
Const OID_FDDI_LONG_MAX_LIST_SIZE       = &H03010104&
Const OID_FDDI_SHORT_PERMANENT_ADDR     = &H03010105&
Const OID_FDDI_SHORT_CURRENT_ADDR       = &H03010106&
Const OID_FDDI_SHORT_MULTICAST_LIST     = &H03010107&
Const OID_FDDI_SHORT_MAX_LIST_SIZE      = &H03010108&

Const OID_FDDI_ATTACHMENT_TYPE          = &H03020101&
Const OID_FDDI_UPSTREAM_NODE_LONG      = &H03020102&
Const OID_FDDI_DOWNSTREAM_NODE_LONG    = &H03020103&
Const OID_FDDI_FRAME_ERRORS             = &H03020104&
Const OID_FDDI_FRAMES_LOST              = &H03020105&
Const OID_FDDI_RING_MGT_STATE           = &H03020106&
Const OID_FDDI_LCT_FAILURES             = &H03020107&
Const OID_FDDI_LEM_REJECTS              = &H03020108&
Const OID_FDDI_LCONNECTION_STATE        = &H03020109&

Const OID_FDDI_SMT_STATION_ID              = &H03030201&
Const OID_FDDI_SMT_OP_VERSION_ID           = &H03030202&
Const OID_FDDI_SMT_HI_VERSION_ID           = &H03030203&
Const OID_FDDI_SMT_LO_VERSION_ID           = &H03030204&
Const OID_FDDI_SMT_MANUFACTURER_DATA       = &H03030205&
Const OID_FDDI_SMT_USER_DATA               = &H03030206&
Const OID_FDDI_SMT_MIB_VERSION_ID          = &H03030207&
Const OID_FDDI_SMT_MAC_CT                  = &H03030208&
Const OID_FDDI_SMT_NON_MASTER_CT           = &H03030209&
Const OID_FDDI_SMT_MASTER_CT               = &H0303020A&
Const OID_FDDI_SMT_AVAILABLE_PATHS         = &H0303020B&
Const OID_FDDI_SMT_CONFIG_CAPABILITIES     = &H0303020C&
Const OID_FDDI_SMT_CONFIG_POLICY           = &H0303020D&
Const OID_FDDI_SMT_CONNECTION_POLICY       = &H0303020E&
Const OID_FDDI_SMT_T_NOTIFY                = &H0303020F&
Const OID_FDDI_SMT_STAT_RPT_POLICY         = &H03030210&
Const OID_FDDI_SMT_TRACE_MAX_EXPIRATION    = &H03030211&
Const OID_FDDI_SMT_PORT_INDEXES            = &H03030212&
Const OID_FDDI_SMT_MAC_INDEXES             = &H03030213&
Const OID_FDDI_SMT_BYPASS_PRESENT          = &H03030214&
Const OID_FDDI_SMT_ECM_STATE               = &H03030215&
Const OID_FDDI_SMT_CF_STATE                = &H03030216&
Const OID_FDDI_SMT_HOLD_STATE              = &H03030217&
Const OID_FDDI_SMT_REMOTE_DISCONNECT_FLAG  = &H03030218&
Const OID_FDDI_SMT_STATION_STATUS          = &H03030219&
Const OID_FDDI_SMT_PEER_WRAP_FLAG          = &H0303021A&
Const OID_FDDI_SMT_MSG_TIME_STAMP          = &H0303021B&
Const OID_FDDI_SMT_TRANSITION_TIME_STAMP   = &H0303021C&
Const OID_FDDI_SMT_SET_COUNT               = &H0303021D&
Const OID_FDDI_SMT_LAST_SET_STATION_ID     = &H0303021E&
Const OID_FDDI_MAC_FRAME_STATUS_FUNCTIONS  = &H0303021F&
Const OID_FDDI_MAC_BRIDGE_FUNCTIONS        = &H03030220&
Const OID_FDDI_MAC_T_MAX_CAPABILITY        = &H03030221&
Const OID_FDDI_MAC_TVX_CAPABILITY          = &H03030222&
Const OID_FDDI_MAC_AVAILABLE_PATHS         = &H03030223&
Const OID_FDDI_MAC_CURRENT_PATH            = &H03030224&
Const OID_FDDI_MAC_UPSTREAM_NBR            = &H03030225&
Const OID_FDDI_MAC_DOWNSTREAM_NBR          = &H03030226&
Const OID_FDDI_MAC_OLD_UPSTREAM_NBR        = &H03030227&
Const OID_FDDI_MAC_OLD_DOWNSTREAM_NBR      = &H03030228&
Const OID_FDDI_MAC_DUP_ADDRESS_TEST        = &H03030229&
Const OID_FDDI_MAC_REQUESTED_PATHS         = &H0303022A&
Const OID_FDDI_MAC_DOWNSTREAM_PORT_TYPE    = &H0303022B&
Const OID_FDDI_MAC_INDEX                   = &H0303022C&
Const OID_FDDI_MAC_SMT_ADDRESS             = &H0303022D&
Const OID_FDDI_MAC_LONG_GRP_ADDRESS        = &H0303022E&
Const OID_FDDI_MAC_SHORT_GRP_ADDRESS       = &H0303022F&
Const OID_FDDI_MAC_T_REQ                   = &H03030230&
Const OID_FDDI_MAC_T_NEG                   = &H03030231&
Const OID_FDDI_MAC_T_MAX                   = &H03030232&
Const OID_FDDI_MAC_TVX_VALUE               = &H03030233&
Const OID_FDDI_MAC_T_PRI0                  = &H03030234&
Const OID_FDDI_MAC_T_PRI1                  = &H03030235&
Const OID_FDDI_MAC_T_PRI2                  = &H03030236&
Const OID_FDDI_MAC_T_PRI3                  = &H03030237&
Const OID_FDDI_MAC_T_PRI4                  = &H03030238&
Const OID_FDDI_MAC_T_PRI5                  = &H03030239&
Const OID_FDDI_MAC_T_PRI6                  = &H0303023A&
Const OID_FDDI_MAC_FRAME_CT                = &H0303023B&
Const OID_FDDI_MAC_COPIED_CT               = &H0303023C&
Const OID_FDDI_MAC_TRANSMIT_CT             = &H0303023D&
Const OID_FDDI_MAC_TOKEN_CT                = &H0303023E&
Const OID_FDDI_MAC_ERROR_CT                = &H0303023F&
Const OID_FDDI_MAC_LOST_CT                 = &H03030240&
Const OID_FDDI_MAC_TVX_EXPIRED_CT          = &H03030241&
Const OID_FDDI_MAC_NOT_COPIED_CT           = &H03030242&
Const OID_FDDI_MAC_LATE_CT                 = &H03030243&
Const OID_FDDI_MAC_RING_OP_CT              = &H03030244&
Const OID_FDDI_MAC_FRAME_ERROR_THRESHOLD   = &H03030245&
Const OID_FDDI_MAC_FRAME_ERROR_RATIO       = &H03030246&
Const OID_FDDI_MAC_NOT_COPIED_THRESHOLD    = &H03030247&
Const OID_FDDI_MAC_NOT_COPIED_RATIO        = &H03030248&
Const OID_FDDI_MAC_RMT_STATE               = &H03030249&
Const OID_FDDI_MAC_DA_FLAG                 = &H0303024A&
Const OID_FDDI_MAC_UNDA_FLAG               = &H0303024B&
Const OID_FDDI_MAC_FRAME_ERROR_FLAG        = &H0303024C&
Const OID_FDDI_MAC_NOT_COPIED_FLAG         = &H0303024D&
Const OID_FDDI_MAC_MA_UNITDATA_AVAILABLE   = &H0303024E&
Const OID_FDDI_MAC_HARDWARE_PRESENT        = &H0303024F&
Const OID_FDDI_MAC_MA_UNITDATA_ENABLE      = &H03030250&
Const OID_FDDI_PATH_INDEX                  = &H03030251&
Const OID_FDDI_PATH_RING_LATENCY           = &H03030252&
Const OID_FDDI_PATH_TRACE_STATUS           = &H03030253&
Const OID_FDDI_PATH_SBA_PAYLOAD            = &H03030254&
Const OID_FDDI_PATH_SBA_OVERHEAD           = &H03030255&
Const OID_FDDI_PATH_CONFIGURATION          = &H03030256&
Const OID_FDDI_PATH_T_R_MODE               = &H03030257&
Const OID_FDDI_PATH_SBA_AVAILABLE          = &H03030258&
Const OID_FDDI_PATH_TVX_LOWER_BOUND        = &H03030259&
Const OID_FDDI_PATH_T_MAX_LOWER_BOUND      = &H0303025A&
Const OID_FDDI_PATH_MAX_T_REQ              = &H0303025B&
Const OID_FDDI_PORT_MY_TYPE                = &H0303025C&
Const OID_FDDI_PORT_NEIGHBOR_TYPE          = &H0303025D&
Const OID_FDDI_PORT_CONNECTION_POLICIES    = &H0303025E&
Const OID_FDDI_PORT_MAC_INDICATED          = &H0303025F&
Const OID_FDDI_PORT_CURRENT_PATH           = &H03030260&
Const OID_FDDI_PORT_REQUESTED_PATHS        = &H03030261&
Const OID_FDDI_PORT_MAC_PLACEMENT          = &H03030262&
Const OID_FDDI_PORT_AVAILABLE_PATHS        = &H03030263&
Const OID_FDDI_PORT_MAC_LOOP_TIME          = &H03030264&
Const OID_FDDI_PORT_PMD_CLASS              = &H03030265&
Const OID_FDDI_PORT_CONNECTION_CAPABILITIES = &H03030266&
Const OID_FDDI_PORT_INDEX                  = &H03030267&
Const OID_FDDI_PORT_MAINT_LS               = &H03030268&
Const OID_FDDI_PORT_BS_FLAG                = &H03030269&
Const OID_FDDI_PORT_PC_LS                  = &H0303026A&
Const OID_FDDI_PORT_EB_ERROR_CT            = &H0303026B&
Const OID_FDDI_PORT_LCT_FAIL_CT            = &H0303026C&
Const OID_FDDI_PORT_LER_ESTIMATE           = &H0303026D&
Const OID_FDDI_PORT_LEM_REJECT_CT          = &H0303026E&
Const OID_FDDI_PORT_LEM_CT                 = &H0303026F&
Const OID_FDDI_PORT_LER_CUTOFF             = &H03030270&
Const OID_FDDI_PORT_LER_ALARM              = &H03030271&
Const OID_FDDI_PORT_CONNNECT_STATE         = &H03030272&
Const OID_FDDI_PORT_PCM_STATE              = &H03030273&
Const OID_FDDI_PORT_PC_WITHHOLD            = &H03030274&
Const OID_FDDI_PORT_LER_FLAG               = &H03030275&
Const OID_FDDI_PORT_HARDWARE_PRESENT       = &H03030276&
Const OID_FDDI_SMT_STATION_ACTION          = &H03030277&
Const OID_FDDI_PORT_ACTION                 = &H03030278&
Const OID_FDDI_IF_DESCR                    = &H03030279&
Const OID_FDDI_IF_TYPE                     = &H0303027A&
Const OID_FDDI_IF_MTU                      = &H0303027B&
Const OID_FDDI_IF_SPEED                    = &H0303027C&
Const OID_FDDI_IF_PHYS_ADDRESS             = &H0303027D&
Const OID_FDDI_IF_ADMIN_STATUS             = &H0303027E&
Const OID_FDDI_IF_OPER_STATUS              = &H0303027F&
Const OID_FDDI_IF_LAST_CHANGE              = &H03030280&
Const OID_FDDI_IF_IN_OCTETS                = &H03030281&
Const OID_FDDI_IF_IN_UCAST_PKTS            = &H03030282&
Const OID_FDDI_IF_IN_NUCAST_PKTS           = &H03030283&
Const OID_FDDI_IF_IN_DISCARDS              = &H03030284&
Const OID_FDDI_IF_IN_ERRORS                = &H03030285&
Const OID_FDDI_IF_IN_UNKNOWN_PROTOS        = &H03030286&
Const OID_FDDI_IF_OUT_OCTETS               = &H03030287&
Const OID_FDDI_IF_OUT_UCAST_PKTS           = &H03030288&
Const OID_FDDI_IF_OUT_NUCAST_PKTS          = &H03030289&
Const OID_FDDI_IF_OUT_DISCARDS             = &H0303028A&
Const OID_FDDI_IF_OUT_ERRORS               = &H0303028B&
Const OID_FDDI_IF_OUT_QLEN                 = &H0303028C&
Const OID_FDDI_IF_SPECIFIC                 = &H0303028D&


'
' WAN objects
'
Const OID_WAN_PERMANENT_ADDRESS            = &H04010101&
Const OID_WAN_CURRENT_ADDRESS              = &H04010102&
Const OID_WAN_QUALITY_OF_SERVICE           = &H04010103&
Const OID_WAN_PROTOCOL_TYPE                = &H04010104&
Const OID_WAN_MEDIUM_SUBTYPE               = &H04010105&
Const OID_WAN_HEADER_FORMAT                = &H04010106&

Const OID_WAN_GET_INFO                     = &H04010107&
Const OID_WAN_SET_LINK_INFO                = &H04010108&
Const OID_WAN_GET_LINK_INFO                = &H04010109&

Const OID_WAN_LINE_COUNT                   = &H0401010A&
Const OID_WAN_PROTOCOL_CAPS                = &H0401010B&

Const OID_WAN_GET_BRIDGE_INFO              = &H0401020A&
Const OID_WAN_SET_BRIDGE_INFO              = &H0401020B&
Const OID_WAN_GET_COMP_INFO                = &H0401020C&
Const OID_WAN_SET_COMP_INFO                = &H0401020D&
Const OID_WAN_GET_STATS_INFO               = &H0401020E&

'
'  These are connection-oriented WAN OIDs.
'  These replace the above OIDs for CoNDIS WAN Miniports
'
Const OID_WAN_CO_GET_INFO                  = &H04010180&
Const OID_WAN_CO_SET_LINK_INFO             = &H04010181&
Const OID_WAN_CO_GET_LINK_INFO             = &H04010182&
Const OID_WAN_CO_GET_COMP_INFO             = &H04010280&
Const OID_WAN_CO_SET_COMP_INFO             = &H04010281&
Const OID_WAN_CO_GET_STATS_INFO            = &H04010282&

'
' IRDA objects
'
Const OID_IRDA_RECEIVING                   = &H0A010100&
Const OID_IRDA_TURNAROUND_TIME             = &H0A010101&
Const OID_IRDA_SUPPORTED_SPEEDS            = &H0A010102&
Const OID_IRDA_LINK_SPEED                  = &H0A010103&
Const OID_IRDA_MEDIA_BUSY                  = &H0A010104&

Const OID_IRDA_EXTRA_RCV_BOFS              = &H0A010200&
Const OID_IRDA_RATE_SNIFF                  = &H0A010201&
Const OID_IRDA_UNICAST_LIST                = &H0A010202&
Const OID_IRDA_MAX_UNICAST_LIST_SIZE       = &H0A010203&
Const OID_IRDA_MAX_RECEIVE_WINDOW_SIZE     = &H0A010204&
Const OID_IRDA_MAX_SEND_WINDOW_SIZE        = &H0A010205&
Const OID_IRDA_RESERVED1                   = &H0A01020A&    ' The range between OID_IRDA_RESERVED1
Const OID_IRDA_RESERVED2                   = &H0A01020F&    ' and OID_IRDA_RESERVED2 is reserved



'
' ATM Connection Oriented OIDs
'
Const OID_ATM_SUPPORTED_VC_RATES           = &H08010101&
Const OID_ATM_SUPPORTED_SERVICE_CATEGORY   = &H08010102&
Const OID_ATM_SUPPORTED_AAL_TYPES          = &H08010103&
Const OID_ATM_HW_CURRENT_ADDRESS           = &H08010104&
Const OID_ATM_MAX_ACTIVE_VCS               = &H08010105&
Const OID_ATM_MAX_ACTIVE_VCI_BITS          = &H08010106&
Const OID_ATM_MAX_ACTIVE_VPI_BITS          = &H08010107&
Const OID_ATM_MAX_AAL0_PACKET_SIZE         = &H08010108&
Const OID_ATM_MAX_AAL1_PACKET_SIZE         = &H08010109&
Const OID_ATM_MAX_AAL34_PACKET_SIZE        = &H0801010A&
Const OID_ATM_MAX_AAL5_PACKET_SIZE         = &H0801010B&

Const OID_ATM_SIGNALING_VPIVCI             = &H08010201&
Const OID_ATM_ASSIGNED_VPI                 = &H08010202&
Const OID_ATM_ACQUIRE_ACCESS_NET_RESOURCES = &H08010203&
Const OID_ATM_RELEASE_ACCESS_NET_RESOURCES = &H08010204&
Const OID_ATM_ILMI_VPIVCI                  = &H08010205&
Const OID_ATM_DIGITAL_BROADCAST_VPIVCI     = &H08010206&
Const OID_ATM_GET_NEAREST_FLOW             = &H08010207&
Const OID_ATM_ALIGNMENT_REQUIRED           = &H08010208&
Const OID_ATM_LECS_ADDRESS                 = &H08010209&
Const OID_ATM_SERVICE_ADDRESS              = &H0801020A&

Const OID_ATM_CALL_PROCEEDING              = &H0801020B&  ' UNI 4.0
Const OID_ATM_CALL_ALERTING                = &H0801020C&  ' UNI 4.0
Const OID_ATM_PARTY_ALERTING               = &H0801020D&  ' UNI 4.0
Const OID_ATM_CALL_NOTIFY                  = &H0801020E&  ' UNI 4.0

Const OID_ATM_MY_IP_NM_ADDRESS             = &H0801020F&

'
'  ATM specific statistics OIDs.
'
Const OID_ATM_RCV_CELLS_OK                 = &H08020101&
Const OID_ATM_XMIT_CELLS_OK                = &H08020102&
Const OID_ATM_RCV_CELLS_DROPPED            = &H08020103&

Const OID_ATM_RCV_INVALID_VPI_VCI          = &H08020201&
Const OID_ATM_CELLS_HEC_ERROR              = &H08020202&
Const OID_ATM_RCV_REASSEMBLY_ERROR         = &H08020203&

'
'  IEEE 1394 specific OIDs.
'
Const OID_1394_LOCAL_NODE_INFO             = &H0C010101&
Const OID_1394_VC_INFO                     = &H0C010102&

'
' PCCA (Wireless) object
'

'
' All WirelessWAN devices must support the following OIDs
'

Const OID_WW_GEN_NETWORK_TYPES_SUPPORTED   = &H09010101&
Const OID_WW_GEN_NETWORK_TYPE_IN_USE       = &H09010102&
Const OID_WW_GEN_HEADER_FORMATS_SUPPORTED  = &H09010103&
Const OID_WW_GEN_HEADER_FORMAT_IN_USE      = &H09010104&
Const OID_WW_GEN_INDICATION_REQUEST        = &H09010105&
Const OID_WW_GEN_DEVICE_INFO               = &H09010106&
Const OID_WW_GEN_OPERATION_MODE            = &H09010107&
Const OID_WW_GEN_LOCK_STATUS               = &H09010108&
Const OID_WW_GEN_DISABLE_TRANSMITTER       = &H09010109&
Const OID_WW_GEN_NETWORK_ID                = &H0901010A&
Const OID_WW_GEN_PERMANENT_ADDRESS         = &H0901010B&
Const OID_WW_GEN_CURRENT_ADDRESS           = &H0901010C&
Const OID_WW_GEN_SUSPEND_DRIVER            = &H0901010D&
Const OID_WW_GEN_BASESTATION_ID            = &H0901010E&
Const OID_WW_GEN_CHANNEL_ID                = &H0901010F&
Const OID_WW_GEN_ENCRYPTION_SUPPORTED      = &H09010110&
Const OID_WW_GEN_ENCRYPTION_IN_USE         = &H09010111&
Const OID_WW_GEN_ENCRYPTION_STATE          = &H09010112&
Const OID_WW_GEN_CHANNEL_QUALITY           = &H09010113&
Const OID_WW_GEN_REGISTRATION_STATUS       = &H09010114&
Const OID_WW_GEN_RADIO_LINK_SPEED          = &H09010115&
Const OID_WW_GEN_LATENCY                   = &H09010116&
Const OID_WW_GEN_BATTERY_LEVEL             = &H09010117&
Const OID_WW_GEN_EXTERNAL_POWER            = &H09010118&

'
' These are optional
'
Const OID_WW_GEN_PING_ADDRESS              = &H09010201&
Const OID_WW_GEN_RSSI                      = &H09010202&
Const OID_WW_GEN_SIM_STATUS                = &H09010203&
Const OID_WW_GEN_ENABLE_SIM_PIN            = &H09010204&
Const OID_WW_GEN_CHANGE_SIM_PIN            = &H09010205&
Const OID_WW_GEN_SIM_PUK                   = &H09010206&
Const OID_WW_GEN_SIM_EXCEPTION             = &H09010207&

'
' Network Dependent OIDs - Mobitex:
'

Const OID_WW_MBX_SUBADDR                   = &H09050101&
' OID &H09050102 is reserved and may not be used
Const OID_WW_MBX_FLEXLIST                  = &H09050103&
Const OID_WW_MBX_GROUPLIST                 = &H09050104&
Const OID_WW_MBX_TRAFFIC_AREA              = &H09050105&
Const OID_WW_MBX_LIVE_DIE                  = &H09050106&
Const OID_WW_MBX_TEMP_DEFAULTLIST          = &H09050107&

'
' Network Dependent OIDs - Pinpoint:
'
'
' The following Pin Point characteristics have been deprecated by the
' PCCA and are considered reserved values. They are include here only for
' historical purposes and should not be used
'
Const OID_WW_PIN_LOC_AUTHORIZE             = &H09090101&
Const OID_WW_PIN_LAST_LOCATION             = &H09090102&
Const OID_WW_PIN_LOC_FIX                   = &H09090103&

'
' Network Dependent - CDPD:
'
Const OID_WW_CDPD_SPNI                     = &H090D0101&
Const OID_WW_CDPD_WASI                     = &H090D0102&
Const OID_WW_CDPD_AREA_COLOR               = &H090D0103&
Const OID_WW_CDPD_TX_POWER_LEVEL           = &H090D0104&
Const OID_WW_CDPD_EID                      = &H090D0105&
Const OID_WW_CDPD_HEADER_COMPRESSION       = &H090D0106&
Const OID_WW_CDPD_DATA_COMPRESSION         = &H090D0107&
Const OID_WW_CDPD_CHANNEL_SELECT           = &H090D0108&
Const OID_WW_CDPD_CHANNEL_STATE            = &H090D0109&
Const OID_WW_CDPD_NEI                      = &H090D010A&
Const OID_WW_CDPD_NEI_STATE                = &H090D010B&
Const OID_WW_CDPD_SERVICE_PROVIDER_IDENTIFIER = &H090D010C&
Const OID_WW_CDPD_SLEEP_MODE               = &H090D010D&

'
' At the request of the PCCA STD-201 Annex C working group the following OID
' value has been superceeded by more specific objects. Its value is reserved by
' the PCCA,is included here for historical purposes only, and should not be
' used.
'
Const OID_WW_CDPD_CIRCUIT_SWITCHED         = &H090D010E&

Const OID_WW_CDPD_TEI                      = &H090D010F&
Const OID_WW_CDPD_RSSI                     = &H090D0110&

'
' CDPD Circuit Switched objects
'
Const OID_WW_CDPD_CS_SERVICE_PREFERENCE    = &H090D0111&
Const OID_WW_CDPD_CS_SERVICE_STATUS        = &H090D0112&
Const OID_WW_CDPD_CS_INFO                  = &H090D0113&
Const OID_WW_CDPD_CS_SUSPEND               = &H090D0114&
Const OID_WW_CDPD_CS_DEFAULT_DIAL_CODE     = &H090D0115&
Const OID_WW_CDPD_CS_CALLBACK              = &H090D0116&
Const OID_WW_CDPD_CS_SID_LIST              = &H090D0117&
Const OID_WW_CDPD_CS_CONFIGURATION         = &H090D0118&

'
' Network Dependent - Ardis:
'
'
' At the request of Ardis these OID value have been superceeded. Their
' functionality has been merged with the DataTAC objects. Therefore
' these values are reserved by the PCCA, are include here for
' historical purposes only, and should not be used.
'
Const OID_WW_ARD_SNDCP                     = &H09110101&
Const OID_WW_ARD_TMLY_MSG                  = &H09110102&
Const OID_WW_ARD_DATAGRAM                  = &H09110103&

'
' Network Dependent - DataTac:
'

Const OID_WW_TAC_COMPRESSION               = &H09150101&

'
' At the request of Motorola, the following two OID values have been
' superceeded. Their functionality has been subsumed by other more specific
' DataTac objects and should not be used. These values are reserved by the
' PCCA and are include here only for historical purposes only.
'
Const OID_WW_TAC_SET_CONFIG                = &H09150102&
Const OID_WW_TAC_GET_STATUS                = &H09150103&
Const OID_WW_TAC_USER_HEADER               = &H09150104&

'
' DataTAC characteristic object values
'
Const OID_WW_TAC_UNIQUE_SDU_TAG            = &H09150105&
Const OID_WW_TAC_SEND_COMMAND              = &H09150106&
Const OID_WW_TAC_GET_RESPONSE              = &H09150107&
Const OID_WW_TAC_DISABLE_RECEIVER          = &H09150108&
Const OID_WW_TAC_ANTENNA_MODE              = &H09150109&
Const OID_WW_TAC_FLUSH_DATA                = &H0915010A&
Const OID_WW_TAC_SHUTDOWN_DEVICE           = &H0915010B&
Const OID_WW_TAC_DEVICE_EXCEPTION          = &H0915010C&
Const OID_WW_TAC_RECEIVE_EXCEPTION         = &H0915010D&
Const OID_WW_TAC_BUFFER_EXCEPTION          = &H0915010E&
Const OID_WW_TAC_BATTERY_EXCEPTION         = &H0915010F&
Const OID_WW_TAC_TRANSMITTER_KEYED         = &H09150110&
Const OID_WW_TAC_SYSTEM_TABLE              = &H09150111&
Const OID_WW_TAC_CHANNEL_TABLE             = &H09150112&
Const OID_WW_TAC_DCHANNEL_TABLE            = &H09150113&
Const OID_WW_TAC_RECEIVE_QUEUE_COUNT       = &H09150114&

'
' DataTac statistic object value
'
Const OID_WW_TAC_STATISTICS                = &H09160101&

'
' Network Dependent - Metricom:
'

Const OID_WW_MET_FUNCTION                  = &H09190101&

'
' IEEE 802.11 OIDs
'
Const OID_802_11_BSSID                     = &H0D010101&
Const OID_802_11_SSID                      = &H0D010102&
Const OID_802_11_NETWORK_TYPES_SUPPORTED   = &H0D010203&
Const OID_802_11_NETWORK_TYPE_IN_USE       = &H0D010204&
Const OID_802_11_TX_POWER_LEVEL            = &H0D010205&
Const OID_802_11_RSSI                      = &H0D010206&
Const OID_802_11_RSSI_TRIGGER              = &H0D010207&
Const OID_802_11_INFRASTRUCTURE_MODE       = &H0D010108&
Const OID_802_11_FRAGMENTATION_THRESHOLD   = &H0D010209&
Const OID_802_11_RTS_THRESHOLD             = &H0D01020A&
Const OID_802_11_NUMBER_OF_ANTENNAS        = &H0D01020B&
Const OID_802_11_RX_ANTENNA_SELECTED       = &H0D01020C&
Const OID_802_11_TX_ANTENNA_SELECTED       = &H0D01020D&
Const OID_802_11_SUPPORTED_RATES           = &H0D01020E&
Const OID_802_11_DESIRED_RATES             = &H0D010210&
Const OID_802_11_CONFIGURATION             = &H0D010211&
Const OID_802_11_STATISTICS                = &H0D020212&
Const OID_802_11_ADD_WEP                   = &H0D010113&
Const OID_802_11_REMOVE_WEP                = &H0D010114&
Const OID_802_11_WEP_STATUS                = &H0D01011B&
Const OID_802_11_DISASSOCIATE              = &H0D010115&
Const OID_802_11_POWER_MODE                = &H0D010216&
Const OID_802_11_BSSID_LIST                = &H0D010217&
Const OID_802_11_BSSID_LIST_SCAN           = &H0D01011A&
Const OID_802_11_AUTHENTICATION_MODE       = &H0D010118&
Const OID_802_11_PRIVACY_FILTER            = &H0D010119&
Const OID_802_11_RELOAD_DEFAULTS           = &H0D01011C&

'
' SSN Wireless OIDs
'
Const OID_802_11_ENCRYPTION_STATUS        = &H0D01011B&
Const OID_802_11_ADD_KEY                  = &H0D01011D&
Const OID_802_11_REMOVE_KEY               = &H0D01011E&
Const OID_802_11_ASSOCIATION_INFORMATION  = &H0D01011F&
Const OID_802_11_TEST                     = &H0D010120&

'
'  TCP/IP OIDs
'
Const OID_TCP_TASK_OFFLOAD                 = &HFC010201&
Const OID_TCP_TASK_IPSEC_ADD_SA            = &HFC010202&
Const OID_TCP_TASK_IPSEC_DELETE_SA         = &HFC010203&
Const OID_TCP_SAN_SUPPORT                  = &HFC010204&

Const OID_PNP_CAPABILITIES                 = &HFD010100&
Const OID_PNP_SET_POWER                    = &HFD010101&
Const OID_PNP_QUERY_POWER                  = &HFD010102&
Const OID_PNP_ADD_WAKE_UP_PATTERN          = &HFD010103&
Const OID_PNP_REMOVE_WAKE_UP_PATTERN       = &HFD010104&
Const OID_PNP_WAKE_UP_PATTERN_LIST         = &HFD010105&
Const OID_PNP_ENABLE_WAKE_UP               = &HFD010106&

Const OID_PNP_WAKE_UP_OK                   = &HFD020200&
Const OID_PNP_WAKE_UP_ERROR                = &HFD020201&

'
' RNDIS
'
Const OID_GEN_RNDIS_CONFIG_PARAMETER       = &H0001021B&

'
' PNP and Power related Constants
'
Const SLEEP_STATE_S0                       = &H00000000&
Const SLEEP_STATE_S1                       = &H00000001&
Const SLEEP_STATE_S2                       = &H00000002&
Const SLEEP_STATE_S3                       = &H00000004&
Const SLEEP_STATE_S4                       = &H00000008&

Const STANDBY_SUPPORTED                    = &H00000007&
Const HIBERNATE_SUPPORTED                  = &H00000008&
Const WAKEUP_TIMER_SUPPORTED               = &H00000010&

'
' The masks for different COM objects
'
Const PNP_POWER_OBJECT                     = &H00000001&


'
' Types of faults that can be injected by the API called
'
Const NO_FAULTS                           = &H00000000&
Const SHORT_BUFFER                        = &H00000001&
Const UNALIGNED_MEMORY                    = &H00000002&



'
' New Ndis 6.0 Multicast oids
'
Const OID_802_3_ADD_MULTICAST_ADDRESS         		= &H01010208&
Const OID_802_3_DELETE_MULTICAST_ADDRESS      		= &H01010209&

Const OID_802_5_ADD_CURRENT_FUNCTIONAL_ADDRESS    	= &H02010208&
Const OID_802_5_DELETE_CURRENT_FUNCTIONAL_ADDRESS 	= &H02010209&

Const OID_FDDI_ADD_LONG_MULTICAST_ADDRESS     		= &H03010201&
Const OID_FDDI_DELETE_LONG_MULTICAST_ADDRESS  		= &H03010202&
Const OID_FDDI_ADD_SHORT_MULTICAST_ADDRESS    		= &H03010203&
Const OID_FDDI_DELETE_SHORT_MULTICAST_ADDRESS 		= &H03010204&


' NT Error Types
Const ERROR_SUCCESS = 0
Const ERROR_MORE_DATA = 234
Const ERROR_INSUFFICIENT_BUFFER = 122




'<!-- CRC = 0x54268bfc --->