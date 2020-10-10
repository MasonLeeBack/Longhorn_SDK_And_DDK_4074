/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    iphlpapi.h

Abstract:
    Header file for functions to interact with the IP Stack for MIB-II and
    related functionality

--*/

#ifndef __IPHLPAPI_H__
#define __IPHLPAPI_H__

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// IPRTRMIB.H has the definitions of the structures used to set and get     //
// information                                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#include <iprtrmib.h>
#include <ipexport.h>
#include <iptypes.h>

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The GetXXXTable APIs take a buffer and a size of buffer.  If the buffer  //
// is not large enough, the APIs return ERROR_INSUFFICIENT_BUFFER  and      //
// *pdwSize is the required buffer size                                     //
// The bOrder is a BOOLEAN, which if TRUE sorts the table according to      //
// MIB-II (RFC XXXX)                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Retrieves the number of interfaces in the system. These include LAN and  //
// WAN interfaces                                                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


DWORD
WINAPI
GetNumberOfInterfaces(
    OUT PDWORD  pdwNumIf
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the MIB-II ifEntry                                                  //
// The dwIndex field of the MIB_IFROW should be set to the index of the     //
// interface being queried                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIfEntry(
    IN OUT PMIB_IFROW   pIfRow
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the MIB-II IfTable                                                  //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIfTable(
    OUT    PMIB_IFTABLE pIfTable,
    IN OUT PULONG       pdwSize,
    IN     BOOL         bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the Interface to IP Address mapping                                 //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIpAddrTable(
    OUT    PMIB_IPADDRTABLE pIpAddrTable,
    IN OUT PULONG           pdwSize,
    IN     BOOL             bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the current IP Address to Physical Address (ARP) mapping            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

ULONG
WINAPI
GetIpNetTable(
    OUT PMIB_IPNETTABLE IpNetTable,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the IP Routing Table  (RFX XXXX)                                    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetIpForwardTable(
    OUT    PMIB_IPFORWARDTABLE pIpForwardTable,
    IN OUT PULONG              pdwSize,
    IN     BOOL                bOrder
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets TCP Connection/UDP Listener Table                                   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

ULONG
WINAPI
GetTcpTable(
    OUT PMIB_TCPTABLE TcpTable,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

ULONG
WINAPI
GetTcpTable2(
    OUT PMIB_TCPTABLE2 TcpTable,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

ULONG
WINAPI
GetUdpTable(
    OUT PMIB_UDPTABLE UdpTable,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

#ifdef _WS2IPDEF_
//
// The following definitions require Winsock2.
//

ULONG
WINAPI
GetTcp6Table(
    OUT PMIB_TCP6TABLE TcpTable,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

ULONG
WINAPI
GetTcp6Table2(
    OUT PMIB_TCP6TABLE2 TcpTable,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

ULONG
WINAPI
GetUdp6Table(
    OUT PMIB_UDP6TABLE Udp6Table,
    IN OUT PULONG SizePointer,
    IN BOOL Order
    );

#endif


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets IP/ICMP/TCP/UDP Statistics                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

ULONG
WINAPI
GetIpStatistics(
    OUT PMIB_IPSTATS Statistics
    );

ULONG
WINAPI
GetIpStatisticsEx(
    OUT PMIB_IPSTATS Statistics,
    IN ULONG Family
    );

ULONG
WINAPI
GetIcmpStatistics(
    OUT PMIB_ICMP Statistics
    );

ULONG
WINAPI
GetIcmpStatisticsEx(
    OUT PMIB_ICMP_EX Statistics,
    IN ULONG Family
    );

ULONG
WINAPI
GetTcpStatistics(
    OUT PMIB_TCPSTATS Statistics
    );

ULONG
WINAPI
GetTcpStatisticsEx(
    OUT PMIB_TCPSTATS Statistics,
    IN ULONG Family
    );

ULONG
WINAPI
GetUdpStatistics(
    OUT PMIB_UDPSTATS Stats
    );

ULONG
WINAPI
GetUdpStatisticsEx(
    OUT PMIB_UDPSTATS Statistics,
    IN ULONG Family
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the ifAdminStatus on an interface.  The only fields of the   //
// MIB_IFROW that are relevant are the dwIndex (index of the interface      //
// whose status needs to be set) and the dwAdminStatus which can be either  //
// MIB_IF_ADMIN_STATUS_UP or MIB_IF_ADMIN_STATUS_DOWN                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
SetIfEntry(
    IN PMIB_IFROW pIfRow
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create, modify or delete a route.  In all cases the              //
// dwForwardIfIndex, dwForwardDest, dwForwardMask, dwForwardNextHop and     //
// dwForwardPolicy MUST BE SPECIFIED. Currently dwForwardPolicy is unused   //
// and MUST BE 0.                                                           //
// For a set, the complete MIB_IPFORWARDROW structure must be specified     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
CreateIpForwardEntry(
    IN PMIB_IPFORWARDROW pRoute
    );

DWORD
WINAPI
SetIpForwardEntry(
    IN PMIB_IPFORWARDROW pRoute
    );

DWORD
WINAPI
DeleteIpForwardEntry(
    IN PMIB_IPFORWARDROW pRoute
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the ipForwarding to ON or OFF (currently only ON->OFF is     //
// allowed) and to set the defaultTTL.  If only one of the fields needs to  //
// be modified and the other needs to be the same as before the other field //
// needs to be set to MIB_USE_CURRENT_TTL or MIB_USE_CURRENT_FORWARDING as  //
// the case may be                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


DWORD
WINAPI
SetIpStatistics(
    IN PMIB_IPSTATS pIpStats
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the defaultTTL.                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
SetIpTTL(
    UINT nTTL
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create, modify or delete an ARP entry.  In all cases the dwIndex //
// dwAddr field MUST BE SPECIFIED.                                          //
// For a set, the complete MIB_IPNETROW structure must be specified         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
CreateIpNetEntry(
    IN PMIB_IPNETROW    pArpEntry
    );

DWORD
WINAPI
SetIpNetEntry(
    IN PMIB_IPNETROW    pArpEntry
    );

DWORD
WINAPI
DeleteIpNetEntry(
    IN PMIB_IPNETROW    pArpEntry
    );

DWORD
WINAPI
FlushIpNetTable(
    IN DWORD   dwIfIndex
    );


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to create or delete a Proxy ARP entry. The dwIndex is the index of  //
// the interface on which to PARP for the dwAddress.  If the interface is   //
// of a type that doesnt support ARP, e.g. PPP, then the call will fail     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
CreateProxyArpEntry(
    IN  DWORD   dwAddress,
    IN  DWORD   dwMask,
    IN  DWORD   dwIfIndex
    );

DWORD
WINAPI
DeleteProxyArpEntry(
    IN  DWORD   dwAddress,
    IN  DWORD   dwMask,
    IN  DWORD   dwIfIndex
    );

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Used to set the state of a TCP Connection. The only state that it can be //
// set to is MIB_TCP_STATE_DELETE_TCB.  The complete MIB_TCPROW structure   //
// MUST BE SPECIFIED                                                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
SetTcpEntry(
    IN PMIB_TCPROW pTcpRow
    );


DWORD
WINAPI
GetInterfaceInfo(
    IN PIP_INTERFACE_INFO pIfTable,
    OUT PULONG            dwOutBufLen
    );

DWORD
WINAPI
GetUniDirectionalAdapterInfo(OUT PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo,
                 OUT PULONG dwOutBufLen
                 );

#ifndef NHPALLOCATEANDGETINTERFACEINFOFROMSTACK_DEFINED
#define NHPALLOCATEANDGETINTERFACEINFOFROMSTACK_DEFINED

DWORD
WINAPI
NhpAllocateAndGetInterfaceInfoFromStack(
    OUT IP_INTERFACE_NAME_INFO **ppTable,
    OUT PDWORD                 pdwCount,
    IN BOOL                    bOrder,
    IN HANDLE                  hHeap,
    IN DWORD                   dwFlags
    );

#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the "best" outgoing interface for the specified destination address //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetBestInterface(
    IN  IPAddr  dwDestAddr,
    OUT PDWORD  pdwBestIfIndex
    );

#pragma warning(push)
#pragma warning(disable:4115)
DWORD
WINAPI
GetBestInterfaceEx(
    IN  struct sockaddr *pDestAddr,
    OUT PDWORD           pdwBestIfIndex
    );
#pragma warning(pop)

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Gets the best (longest matching prefix) route for the given destination  //
// If the source address is also specified (i.e. is not 0x00000000), and    //
// there are multiple "best" routes to the given destination, the returned  //
// route will be one that goes out over the interface which has an address  //
// that matches the source address                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

DWORD
WINAPI
GetBestRoute(
    IN  DWORD               dwDestAddr,
    IN  DWORD               dwSourceAddr, OPTIONAL
    OUT PMIB_IPFORWARDROW   pBestRoute
    );

DWORD
WINAPI
NotifyAddrChange(
    OUT PHANDLE      Handle,
    IN  LPOVERLAPPED overlapped
    );


DWORD
WINAPI
NotifyRouteChange(
    OUT PHANDLE      Handle,
    IN  LPOVERLAPPED overlapped
    );

BOOL
WINAPI
CancelIPChangeNotify(
    IN  LPOVERLAPPED notifyOverlapped
    );

DWORD
WINAPI
GetAdapterIndex(
    IN LPWSTR  AdapterName,
    OUT PULONG IfIndex
    );

DWORD
WINAPI
AddIPAddress(
    IPAddr  Address,
    IPMask  IpMask,
    DWORD   IfIndex,
    PULONG  NTEContext,
    PULONG  NTEInstance
    );

DWORD
WINAPI
DeleteIPAddress(
    ULONG NTEContext
    );

DWORD
WINAPI
GetNetworkParams(
    PFIXED_INFO pFixedInfo, PULONG pOutBufLen
    );

ULONG
WINAPI
GetAdaptersInfo(
    IN PIP_ADAPTER_INFO AdapterInfo, 
    IN OUT PULONG SizePointer
    );

PIP_ADAPTER_ORDER_MAP 
WINAPI
GetAdapterOrderMap(
    VOID
    );

#ifdef _WINSOCK2API_

//
// The following functions require Winsock2.
//

ULONG
WINAPI
GetAdaptersAddresses(
    IN ULONG Family,
    IN ULONG Flags,
    IN PVOID Reserved,
    OUT PIP_ADAPTER_ADDRESSES AdapterAddresses, 
    IN OUT PULONG SizePointer
    );

#endif

DWORD
WINAPI
GetPerAdapterInfo(
    ULONG IfIndex, PIP_PER_ADAPTER_INFO pPerAdapterInfo, PULONG pOutBufLen
    );

DWORD
WINAPI
IpReleaseAddress(
    PIP_ADAPTER_INDEX_MAP  AdapterInfo
    );


DWORD
WINAPI
IpRenewAddress(
    PIP_ADAPTER_INDEX_MAP  AdapterInfo
    );

DWORD
WINAPI
SendARP(
    IPAddr DestIP,
    IPAddr SrcIP,
    PVOID pMacAddr,
    PULONG  PhyAddrLen
    );

BOOL
WINAPI
GetRTTAndHopCount(
    IPAddr DestIpAddress,
    PULONG HopCount,
    ULONG  MaxHops,
    PULONG RTT
    );

DWORD
WINAPI
GetFriendlyIfIndex(
    DWORD IfIndex
    );

DWORD
WINAPI
EnableRouter(
    HANDLE* pHandle,
    OVERLAPPED* pOverlapped
    );

DWORD
WINAPI
UnenableRouter(
    OVERLAPPED* pOverlapped,
    LPDWORD lpdwEnableCount OPTIONAL
    );
DWORD
WINAPI
DisableMediaSense(
    HANDLE *pHandle,
    OVERLAPPED *pOverLapped
    );

DWORD
WINAPI
RestoreMediaSense(
    OVERLAPPED* pOverlapped,
    LPDWORD lpdwEnableCount OPTIONAL
    );

DWORD
WINAPI
GetIpErrorString(
    IN IP_STATUS ErrorCode,
    OUT PWCHAR Buffer,
    IN OUT PDWORD Size
    );

ULONG
WINAPI
ConvertLengthToIpv4Mask(
    IN ULONG MaskLength,
    OUT PULONG Mask
    );

ULONG
WINAPI
ConvertIpv4MaskToLength(
    IN ULONG Mask,
    OUT PUINT8 MaskLength
    );

//
// Generic (not IP-specific) interface definitions.
//

ULONG
WINAPI
ConvertInterfaceNameToLuidA(
    IN CONST CHAR *InterfaceName,
    OUT NET_LUID *InterfaceLuid
    );

ULONG
WINAPI
ConvertInterfaceNameToLuidW(
    IN CONST WCHAR *InterfaceName,
    OUT NET_LUID *InterfaceLuid
    );

ULONG
WINAPI
ConvertInterfaceLuidToNameA(
    IN CONST NET_LUID *InterfaceLuid,
    OUT CHAR *InterfaceName,
    IN SIZE_T Length
    );

ULONG
WINAPI
ConvertInterfaceLuidToNameW(
    IN CONST NET_LUID *InterfaceLuid,
    OUT WCHAR *InterfaceName,
    IN SIZE_T Length
    );

ULONG
WINAPI
ConvertInterfaceLuidToIndex(
    IN CONST NET_LUID *InterfaceLuid,
    OUT PNET_IFINDEX InterfaceIndex
    );

ULONG
WINAPI
ConvertInterfaceIndexToLuid(
    IN NET_IFINDEX InterfaceIndex,
    OUT PNET_LUID InterfaceLuid
    );

ULONG
WINAPI
ConvertInterfaceLuidToAlias(
    IN CONST NET_LUID *InterfaceLuid,
    OUT WCHAR *InterfaceAlias,
    IN SIZE_T Length
    );

ULONG
WINAPI
ConvertInterfaceAliasToLuid(
    IN CONST WCHAR *InterfaceAlias,
    OUT PNET_LUID InterfaceLuid
    );

ULONG
WINAPI
ConvertInterfaceLuidToGuid(
    IN CONST NET_LUID *InterfaceLuid,
    OUT GUID *InterfaceGuid
    );

ULONG
WINAPI
ConvertInterfaceGuidToLuid(
    IN CONST GUID *InterfaceGuid,
    OUT PNET_LUID InterfaceLuid
    );

#define IF_NAMESIZE NDIS_IF_MAX_STRING_SIZE
    
PCHAR
WINAPI
if_indextoname(
    IN UINT InterfaceIndex,
    OUT PCHAR InterfaceName
    );    

NET_IF_COMPARTMENT_ID
GetCurrentThreadCompartmentId(
    VOID
    );

ULONG
SetCurrentThreadCompartmentId(
    IN NET_IF_COMPARTMENT_ID CompartmentId
    );

#define NET_IF_CURRENT_SESSION ((ULONG)-1)

ULONG
SetSessionCompartmentId(
    IN ULONG SessionId,
    IN NET_IF_COMPARTMENT_ID CompartmentId
    );

NET_IF_COMPARTMENT_ID
GetSessionCompartmentId(
    IN ULONG SessionId
    );

ULONG
SetNetworkInformation(
    IN CONST NET_IF_NETWORK_GUID *NetworkGuid,
    IN NET_IF_COMPARTMENT_ID CompartmentId,
    IN ULONG SiteId,
    IN CONST WCHAR *NetworkName
    );

#ifdef __cplusplus
}
#endif

#endif //__IPHLPAPI_H__

