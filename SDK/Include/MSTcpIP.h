/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    mstcpip.h

Abstract:

    This module contains Microsoft-specific extensions to the core
    Winsock definitions.

Environment:

    user mode or kernel mode

--*/

#ifndef _MSTCPIP_
#define _MSTCPIP_

#if _MSC_VER > 1000
#pragma once
#endif
#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(push)
#pragma warning(disable:4201)

#ifndef ASSERT
#define MSTCPIP_ASSERT_UNDEFINED
#define ASSERT(exp) ((VOID) 0)
#endif

#ifdef _MSC_VER
#define MSTCPIP_INLINE __inline
#else
#define MSTCPIP_INLINE extern inline /* GNU style */
#endif

/* Argument structure for SIO_KEEPALIVE_VALS */

struct tcp_keepalive {
    ULONG onoff;
    ULONG keepalivetime;
    ULONG keepaliveinterval;
};

//
// New WSAIoctl Options
// 
#define SIO_RCVALL            _WSAIOW(IOC_VENDOR,1)
#define SIO_RCVALL_MCAST      _WSAIOW(IOC_VENDOR,2)
#define SIO_RCVALL_IGMPMCAST  _WSAIOW(IOC_VENDOR,3)
#define SIO_KEEPALIVE_VALS    _WSAIOW(IOC_VENDOR,4)
#define SIO_ABSORB_RTRALERT   _WSAIOW(IOC_VENDOR,5)
#define SIO_UCAST_IF          _WSAIOW(IOC_VENDOR,6)
#define SIO_LIMIT_BROADCASTS  _WSAIOW(IOC_VENDOR,7)
#define SIO_INDEX_BIND        _WSAIOW(IOC_VENDOR,8)
#define SIO_INDEX_MCASTIF     _WSAIOW(IOC_VENDOR,9)
#define SIO_INDEX_ADD_MCAST   _WSAIOW(IOC_VENDOR,10)
#define SIO_INDEX_DEL_MCAST   _WSAIOW(IOC_VENDOR,11)
//      SIO_UDP_CONNRESET     _WSAIOW(IOC_VENDOR,12)
#define SIO_RCVALL_MCAST_IF   _WSAIOW(IOC_VENDOR,13)
#define SIO_RCVALL_IF         _WSAIOW(IOC_VENDOR,14)

//
// Values for use with SIO_RCVALL* options
//
typedef enum {
    RCVALL_OFF             = 0,
    RCVALL_ON              = 1,
    RCVALL_SOCKETLEVELONLY = 2,
    RCVALL_IPLEVEL         = 3,
} RCVALL_VALUE, *PRCVALL_VALUE;

#define RCVALL_MAX RCVALL_IPLEVEL

typedef struct {
    RCVALL_VALUE Mode;
    ULONG Interface;
} RCVALL_IF, *PRCVALL_IF;

#ifdef _WS2DEF_

//
// Microsoft-specific IPv4 definitions.
//

#define IN4_CLASSA(i)           (((LONG)(i) & 0x00000080) == 0)
#define IN4_CLASSB(i)           (((LONG)(i) & 0x000000c0) == 0x00000080)
#define IN4_CLASSC(i)           (((LONG)(i) & 0x000000e0) == 0x000000c0)
#define IN4_CLASSD(i)           (((LONG)(i) & 0x000000f0) == 0x000000e0)
#define IN4_MULTICAST(i)        IN4_CLASSD(i)

#define IN4ADDR_ANY             INADDR_ANY
#define IN4ADDR_LOOPBACK        0x0100007f
#define IN4ADDR_BROADCAST       INADDR_BROADCAST
#define IN4ADDR_NONE            INADDR_NONE
#define IN4ADDR_ANY_INIT             { 0 }
#define IN4ADDR_LOOPBACK_INIT        { 0x7f, 0, 0, 1 }
#define IN4ADDR_LINKLOCALPREFIX_INIT { 0xa9, 0xfe, }
#define IN4ADDR_ALLNODESONLINK_INIT  { 0xe0, 0, 0, 1 }
#define IN4ADDR_ALLROUTERSONLINK_INIT { 0xe0, 0, 0, 2 }
#define IN4ADDR_ALLIGMPV3ROUTERSONLINK_INIT  { 0xe0, 0, 0, 0x16 }
#define IN4ADDR_BROADCAST_INIT { 0xff, 0xff, 0xff, 0xff }

#define IN4ADDR_LOOPBACKPREFIX_LENGTH   8
#define IN4ADDR_LINKLOCALPREFIX_LENGTH 16 

MSTCPIP_INLINE
BOOLEAN
IN4_ADDR_EQUAL(CONST IN_ADDR *a, CONST IN_ADDR *b)
{
    return (BOOLEAN)(a->s_addr == b->s_addr);
}

MSTCPIP_INLINE
BOOLEAN
IN4_UNALIGNED_ADDR_EQUAL(CONST IN_ADDR UNALIGNED *a, CONST IN_ADDR UNALIGNED *b)
{
    return (BOOLEAN)(a->s_addr == b->s_addr);
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_MULTICAST(CONST IN_ADDR *a)
{
    return (BOOLEAN)IN4_MULTICAST(a->s_addr);
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_BROADCAST(CONST IN_ADDR *a)
{
    return (BOOLEAN)(a->s_addr == IN4ADDR_BROADCAST);
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_LOOPBACK(CONST IN_ADDR *a)
{
    return (BOOLEAN)(a->s_addr == IN4ADDR_LOOPBACK);
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_UNSPECIFIED(CONST IN_ADDR *a)
{
    return (BOOLEAN)(a->s_addr == IN4ADDR_ANY);
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_UNALIGNED_ADDR_UNSPECIFIED(CONST IN_ADDR UNALIGNED *a)
{
    return (BOOLEAN)(a->s_addr == IN4ADDR_ANY);
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_LINKLOCAL(CONST IN_ADDR *a)
{
    return (BOOLEAN)((a->s_addr & 0xffff) == 0xfea9); // 169.254/16
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_SITELOCAL(CONST IN_ADDR *a)
{
    return (BOOLEAN)(((a->s_addr & 0x00ff) == 0x0a) ||   // 10/8
                     ((a->s_addr & 0xf0ff) == 0x10ac) || // 172.16/12
                     ((a->s_addr & 0xffff) == 0xa8c0));  // 192.168/16
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_MC_LINKLOCAL(CONST IN_ADDR *a)
{
    return (BOOLEAN)((a->s_addr & 0xffffff) == 0xe0); // 224.0.0/24
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_MC_ADMINLOCAL(CONST IN_ADDR *a)
{
    return (BOOLEAN)((a->s_addr & 0xffff) == 0xffef); // 239.255/16
}

MSTCPIP_INLINE
BOOLEAN
IN4_IS_ADDR_MC_SITELOCAL(CONST IN_ADDR *a)
{
    return (BOOLEAN)((a->s_addr & 0xff) == 0xef) && 
                    !IN4_IS_ADDR_MC_ADMINLOCAL(a); 
}

MSTCPIP_INLINE
SCOPE_ID
IN4ADDR_SCOPE_ID(CONST SOCKADDR_IN* a)
{
    SCOPE_ID UnspecifiedScopeId = {0};
    UNREFERENCED_PARAMETER(a);
    return UnspecifiedScopeId;
}

MSTCPIP_INLINE
VOID
IN4ADDR_SETANY(PSOCKADDR_IN a)
{
    a->sin_family = AF_INET;
    a->sin_port = 0;
    a->sin_addr.s_addr = IN4ADDR_ANY;
    a->sin_scope_id = 0;
}

MSTCPIP_INLINE
VOID
IN4ADDR_SETLOOPBACK(PSOCKADDR_IN a)
{
    a->sin_family = AF_INET;
    a->sin_port = 0;
    a->sin_addr.s_addr = IN4ADDR_LOOPBACK;
    a->sin_scope_id = 0;
}

MSTCPIP_INLINE
BOOLEAN
IN4ADDR_ISANY(CONST SOCKADDR_IN *a)
{
    ASSERT(a->sin_family == AF_INET);
    return IN4_IS_ADDR_UNSPECIFIED(&a->sin_addr);
}

MSTCPIP_INLINE
BOOLEAN
IN4ADDR_ISLOOPBACK(CONST SOCKADDR_IN *a)
{
    ASSERT(a->sin_family == AF_INET);
    return IN4_IS_ADDR_LOOPBACK(&a->sin_addr);
}

MSTCPIP_INLINE
BOOLEAN
IN4ADDR_ISEQUAL(CONST SOCKADDR_IN *a, CONST SOCKADDR_IN *b)
{
    ASSERT(a->sin_family == AF_INET);
    return (BOOLEAN)(IN4ADDR_SCOPE_ID(a).Value == IN4ADDR_SCOPE_ID(b).Value &&
                     IN4_ADDR_EQUAL(&a->sin_addr, &b->sin_addr));
}

MSTCPIP_INLINE
BOOLEAN
IN4ADDR_ISUNSPECIFIED(CONST SOCKADDR_IN *a)
{
    ASSERT(a->sin_family == AF_INET);
    return (BOOLEAN)(IN4ADDR_SCOPE_ID(a).Value == 0 && 
                     IN4_IS_ADDR_UNSPECIFIED(&a->sin_addr));
}

MSTCPIP_INLINE
SCOPE_LEVEL
Ipv4UnicastAddressScope(
    IN CONST UCHAR *Address
    )
/*++

Routine Description:

    Determines the scope of an IPv4 unicast address.
    See RFC 1918.

Arguments:

    Address - Supplies the IPv4 unicast address.

Return Value:

    Returns the scope level of the address.

Caller IRQL:

    May be called at PASSIVE through DISPATCH level.

--*/
{
    CONST IN_ADDR *V4Address = (CONST IN_ADDR *)Address;

    if ((V4Address->s_addr & 0x0000FFFF) == 0x0000FEA9) {
        //
        // 169.254/16 - auto-configured.
        //
        return ScopeLevelLink;
    } else if ((V4Address->s_addr & 0x000000FF) == 0x0000000A) {
        //
        // 10/8 - private.
        //
        return ScopeLevelSite;
    } else if ((V4Address->s_addr & 0x0000F0FF) == 0x000010AC) {
        //
        // 172.16/12 - private.
        //
        return ScopeLevelSite;
    } else if ((V4Address->s_addr & 0x0000FFFF) == 0x0000A8C0) {
        //
        // 192.168/16 - private.
        //
        return ScopeLevelSite;
    } else if ((V4Address->s_addr & 0x000000FF) == 0x0000007F) {
        //
        // 127/8 - loopback.
        //
        return ScopeLevelLink;
    } else {
        return ScopeLevelGlobal;
    }
}

MSTCPIP_INLINE
SCOPE_LEVEL
Ipv4MulticastAddressScope(
    IN CONST IN_ADDR *Address
    )
/*++

Routine Description:

    Determines the scope of an IPv4 multicast address.
    See RFC 2365.

Arguments:

    Address - Supplies the IPv4 multicast address.

Return Value:

    Returns the scope level of the multicast address.

Caller IRQL:

    May be called at PASSIVE through DISPATCH level.

--*/
{
    if (IN4_IS_ADDR_MC_LINKLOCAL(Address)) {
        return ScopeLevelLink;
    } else if (IN4_IS_ADDR_MC_ADMINLOCAL(Address)) {
        return ScopeLevelAdmin;
    } else if (IN4_IS_ADDR_MC_SITELOCAL(Address)) {
        return ScopeLevelSite;
    } else {
        return ScopeLevelGlobal;
    }
}

MSTCPIP_INLINE
SCOPE_LEVEL
Ipv4AddressScope(
    IN CONST UCHAR *Address
    )
/*++

Routine Description:

    Examines an IPv4 address and determines its scope.

Arguments:

    Address - Supplies the address to test.

Return Value:

    Returns the scope level of the address.

Caller IRQL:

    May be called at PASSIVE through DISPATCH level.

--*/
{
    IN CONST IN_ADDR V4Address = *(CONST IN_ADDR UNALIGNED *)Address;

    if (IN4_IS_ADDR_BROADCAST(&V4Address)) {
        return ScopeLevelLink;
    } else if (IN4_IS_ADDR_MULTICAST(&V4Address)) {
        return Ipv4MulticastAddressScope(&V4Address);
    } else {
        return Ipv4UnicastAddressScope((CONST UCHAR *)&V4Address);
    }
}

MSTCPIP_INLINE
VOID
IN4_UNCANONICALIZE_SCOPE_ID(
    IN CONST IN_ADDR *Address, 
    IN OUT SCOPE_ID *ScopeId
    ) 
{
    SCOPE_LEVEL ScopeLevel = Ipv4AddressScope((CONST UCHAR *)Address);

    if ((IN4_IS_ADDR_LOOPBACK(Address)) ||
        (ScopeLevel == ScopeLevelGlobal)) {
        ScopeId->Value = 0;
    }

    if ((SCOPE_LEVEL)ScopeId->Level == ScopeLevel) {
        ScopeId->Level = 0;
    }
}

#endif // _WS2DEF_


//
// Microsoft-specific IPv6 definitions.
//

#ifdef _WS2IPDEF_

#define IN6ADDR_6TO4PREFIX_INIT { 0x20, 0x02, }
#define IN6ADDR_TEREDOPREFIX_INIT { 0x3f, 0xfe, 0x83, 0x1f, }

extern CONST IN6_ADDR in6addr_6to4prefix;
extern CONST IN6_ADDR in6addr_teredoprefix;

MSTCPIP_INLINE
BOOLEAN
IN6_PREFIX_EQUAL(CONST IN6_ADDR *a, CONST IN6_ADDR *b, UINT8 len)
{
    UINT8 Bytes = len / 8;
    UINT8 Bits = len % 8;
    UINT8 Mask = 0xff << (8 - Bits);

    ASSERT(len <= (sizeof(IN6_ADDR) * 8));
    return (BOOLEAN)
        (((memcmp(a, b, Bytes)) == 0) &&
         ((Bits == 0) ||
          ((a->s6_bytes[Bytes] | Mask) == (b->s6_bytes[Bytes] | Mask))));
}

MSTCPIP_INLINE
BOOLEAN
IN6_IS_ADDR_SOLICITEDNODE(CONST IN6_ADDR *a)
{
    return IN6_PREFIX_EQUAL(a, &in6addr_solicitednodemulticastprefix, 104);
}

MSTCPIP_INLINE
BOOLEAN
IN6_IS_ADDR_ISATAP(CONST IN6_ADDR *a)
{
    return (BOOLEAN)(((a->s6_words[4] & 0xfffd) == 0x0000) &&
                     (a->s6_words[5] == 0xfe5e));
}

MSTCPIP_INLINE
BOOLEAN
IN6_IS_ADDR_6TO4(CONST IN6_ADDR *a)
{
    return (BOOLEAN)(a->s6_words[0] == 0x0220);
}

MSTCPIP_INLINE
BOOLEAN
IN6_IS_ADDR_TEREDO(CONST IN6_ADDR *a)
{
    return (BOOLEAN)((a->s6_words[0] == 0xfe3f) &&
                     (a->s6_words[1] == 0x1f83));
}

MSTCPIP_INLINE
BOOLEAN
IN6ADDR_IS6TO4(CONST SOCKADDR_IN6 *a)
{
    ASSERT(a->sin6_family == AF_INET6);
    return IN6_IS_ADDR_6TO4(&a->sin6_addr);
}

MSTCPIP_INLINE
BOOLEAN
IN6ADDR_ISTEREDO(CONST SOCKADDR_IN6 *a)
{
    ASSERT(a->sin6_family == AF_INET6);
    return IN6_IS_ADDR_TEREDO(&a->sin6_addr);
}

MSTCPIP_INLINE
CONST UCHAR*
IN6_EXTRACT_V4ADDR_FROM_6TO4(CONST IN6_ADDR *a) 
{
    return (CONST UCHAR *)&a->s6_bytes[2];
}

MSTCPIP_INLINE
SCOPE_LEVEL
Ipv6UnicastAddressScope(
    IN CONST IN6_ADDR *Address
    )
/*++

Routine Description:

    Examines a unicast address and determines its scope.
  
    Note that v4-compatible and 6to4 addresses
    are deemed to have global scope. They should
    not be derived from RFC 1918 IPv4 addresses.
    But even if they are, we will treat the IPv6
    addresses as global.

Arguments:

    Address - Supplies an IPv6 unicast address.

Return Value:

    Returns the scope level of the address.

Caller IRQL:

    May be called at PASSIVE through DISPATCH level.

--*/
{
    if (IN6_IS_ADDR_LINKLOCAL(Address)) {
        return ScopeLevelLink;
    } else if (IN6_IS_ADDR_SITELOCAL(Address)) {
        return ScopeLevelSite;
    } else if (IN6_IS_ADDR_LOOPBACK(Address)) {
        return ScopeLevelLink;
    } else {
        return ScopeLevelGlobal;
    }
}

MSTCPIP_INLINE
SCOPE_LEVEL
IN6_MULTICAST_SCOPE(
    IN CONST IN6_ADDR *Address
    )
{
    return (SCOPE_LEVEL)(Address->s6_bytes[1] & 0xf);
}

MSTCPIP_INLINE
SCOPE_LEVEL
Ipv6AddressScope(
    IN CONST UCHAR *Address
    )
/*++

Routine Description:

    Examines an IPv6 address and determines its scope.

Arguments:

    Address - Supplies an IPv6 address.

Return Value:

    Returns the scope level of the address.

Caller IRQL:

    May be called at PASSIVE through DISPATCH level.

--*/
{
    IN CONST IN6_ADDR *V6Address = (CONST IN6_ADDR *)Address;

    if (IN6_IS_ADDR_MULTICAST(V6Address)) {
        return IN6_MULTICAST_SCOPE(V6Address);
    } else {
        return Ipv6UnicastAddressScope(V6Address);
    }
}

MSTCPIP_INLINE
VOID
IN6_UNCANONICALIZE_SCOPE_ID(
    IN CONST IN6_ADDR *Address, 
    IN OUT SCOPE_ID *ScopeId
    ) 
{
    SCOPE_LEVEL ScopeLevel = Ipv6AddressScope((CONST UCHAR *)Address);

    if ((IN6_IS_ADDR_LOOPBACK(Address)) ||
        (ScopeLevel == ScopeLevelGlobal)) {
        ScopeId->Value = 0;
    }

    if ((SCOPE_LEVEL)ScopeId->Level == ScopeLevel) {
        ScopeId->Level = 0;
    }
}

//
// Define address-family-independent routines.
//

MSTCPIP_INLINE
BOOLEAN
INET_ADDR_EQUAL(ADDRESS_FAMILY af, CONST VOID* a, CONST VOID* b)
{
    if (af == AF_INET6) {
        return IN6_ADDR_EQUAL((CONST IN6_ADDR*)a, (CONST IN6_ADDR*)b);
    } else {
        ASSERT(af == AF_INET);
        return IN4_ADDR_EQUAL((CONST IN_ADDR*)a, (CONST IN_ADDR*)b);
    }
}

MSTCPIP_INLINE
BOOLEAN
INET_UNALIGNED_ADDR_EQUAL(ADDRESS_FAMILY af, CONST VOID* a, CONST VOID* b)
{
    if (af == AF_INET6) {
        return IN6_ADDR_EQUAL((CONST IN6_ADDR*)a, (CONST IN6_ADDR*)b);
    } else {
        ASSERT(af == AF_INET);
        return IN4_UNALIGNED_ADDR_EQUAL((CONST IN_ADDR*)a, (CONST IN_ADDR*)b);
    }
}

MSTCPIP_INLINE
BOOLEAN
INET_IS_ADDR_UNSPECIFIED(ADDRESS_FAMILY af, CONST VOID* a)
{
    if (af == AF_INET6) {
        return IN6_IS_ADDR_UNSPECIFIED((CONST IN6_ADDR*)a);
    } else {
        ASSERT(af == AF_INET);
        return IN4_IS_ADDR_UNSPECIFIED((CONST IN_ADDR*)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
INET_IS_UNALIGNED_ADDR_UNSPECIFIED(ADDRESS_FAMILY af, CONST VOID* a)
{
    if (af == AF_INET6) {
        return IN6_IS_ADDR_UNSPECIFIED((CONST IN6_ADDR*)a);
    } else {
        ASSERT(af == AF_INET);
        return IN4_IS_UNALIGNED_ADDR_UNSPECIFIED((CONST IN_ADDR UNALIGNED*)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
INET_IS_ADDR_LOOPBACK(ADDRESS_FAMILY af, CONST VOID* a)
{
    if (af == AF_INET6) {
        return IN6_IS_ADDR_LOOPBACK((CONST IN6_ADDR*)a);
    } else {
        ASSERT(af == AF_INET);
        return IN4_IS_ADDR_LOOPBACK((CONST IN_ADDR*)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
INET_IS_ADDR_BROADCAST(ADDRESS_FAMILY af, CONST VOID* a)
{
    if (af == AF_INET6) {
        return FALSE;
    } else {
        ASSERT(af == AF_INET);
        return IN4_IS_ADDR_BROADCAST((CONST IN_ADDR*)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
INET_IS_ADDR_MULTICAST(ADDRESS_FAMILY af, CONST VOID* a)
{
    if (af == AF_INET6) {
        return IN6_IS_ADDR_MULTICAST((CONST IN6_ADDR*)a);
    } else {
        ASSERT(af == AF_INET);
        return IN4_IS_ADDR_MULTICAST((CONST IN_ADDR*)a);
    }
}

MSTCPIP_INLINE
CONST UCHAR*
INET_ADDR_UNSPECIFIED(ADDRESS_FAMILY af)
{
    if (af == AF_INET6) {
        return (CONST UCHAR*)&in6addr_any;
    } else {
        ASSERT(af == AF_INET);
        return (CONST UCHAR*)&in4addr_any;
    }
}


MSTCPIP_INLINE
VOID
INETADDR_SETSOCKADDR(ADDRESS_FAMILY af, PSOCKADDR a, CONST VOID* addr,
                     SCOPE_ID scope, USHORT port)
{
    if (af == AF_INET6) {
        PSOCKADDR_IN6 a6 = (PSOCKADDR_IN6)a;
        a6->sin6_family = AF_INET6;
        a6->sin6_flowinfo = 0;
        a6->sin6_addr = *(CONST IN6_ADDR*)addr;
        a6->sin6_scope_struct = scope;
        IN6_UNCANONICALIZE_SCOPE_ID(&a6->sin6_addr, &a6->sin6_scope_struct);
        a6->sin6_port = port;
    } else {
        PSOCKADDR_IN a4 = (PSOCKADDR_IN)a;
        ASSERT(af == AF_INET);
        a4->sin_family = AF_INET;
        a4->sin_addr = *(CONST IN_ADDR UNALIGNED*)addr;
        a4->sin_scope_struct = scope;
        IN4_UNCANONICALIZE_SCOPE_ID(&a4->sin_addr, &a4->sin_scope_struct);
        a4->sin_port = port;
    }
}

MSTCPIP_INLINE
VOID
INETADDR_SETANY(PSOCKADDR a)
{
    if (a->sa_family == AF_INET6) {
        IN6ADDR_SETANY((PSOCKADDR_IN6)a);
    } else {
        ASSERT(a->sa_family == AF_INET);
        IN4ADDR_SETANY((PSOCKADDR_IN)a);
    }
}

MSTCPIP_INLINE
VOID
INETADDR_SETLOOPBACK(PSOCKADDR a)
{
    if (a->sa_family == AF_INET6) {
        IN6ADDR_SETLOOPBACK((PSOCKADDR_IN6)a);
    } else {
        ASSERT(a->sa_family == AF_INET);
        IN4ADDR_SETLOOPBACK((PSOCKADDR_IN)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
INETADDR_ISANY(CONST SOCKADDR *a)
{
    if (a->sa_family == AF_INET6) {
        return IN6ADDR_ISANY((CONST SOCKADDR_IN6*)a);
    } else {
        ASSERT(a->sa_family == AF_INET);
        return IN4ADDR_ISANY((CONST SOCKADDR_IN*)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
INETADDR_ISLOOPBACK(CONST SOCKADDR *a)
{
    if (a->sa_family == AF_INET6) {
        return IN6ADDR_ISLOOPBACK((CONST SOCKADDR_IN6*)a);
    } else {
        ASSERT(a->sa_family == AF_INET);
        return IN4ADDR_ISLOOPBACK((CONST SOCKADDR_IN*)a);
    }
}

MSTCPIP_INLINE
BOOLEAN
NL_ADDR_EQUAL(
    IN ADDRESS_FAMILY af,
    IN SCOPE_ID sa,
    IN CONST UCHAR* aa,
    IN SCOPE_ID sb,
    IN CONST UCHAR* ab
    )
{
    return (BOOLEAN)((sa.Value == sb.Value) && INET_ADDR_EQUAL(af, aa, ab));
}

MSTCPIP_INLINE
BOOLEAN
NL_IS_ADDR_UNSPECIFIED(
    IN ADDRESS_FAMILY af,
    IN SCOPE_ID s,
    IN CONST UCHAR* a
    )
{
    return (BOOLEAN)((s.Value == 0) && INET_IS_ADDR_UNSPECIFIED(af, a));
}

MSTCPIP_INLINE
BOOLEAN
INETADDR_ISEQUAL(CONST SOCKADDR *a, CONST SOCKADDR *b)
{
    if (a->sa_family == AF_INET6) {
        return (BOOLEAN)
            (b->sa_family == AF_INET6 &&
             IN6ADDR_ISEQUAL((CONST SOCKADDR_IN6*)a, (CONST SOCKADDR_IN6*)b));
    } else {
        ASSERT(a->sa_family == AF_INET);
        return (BOOLEAN)
            (b->sa_family == AF_INET &&
             IN4ADDR_ISEQUAL((CONST SOCKADDR_IN*)a, (CONST SOCKADDR_IN*)b));
    }
}

MSTCPIP_INLINE
BOOLEAN
INETADDR_ISUNSPECIFIED(CONST SOCKADDR *a)
{
    if (a->sa_family == AF_INET6) {
        return IN6ADDR_ISUNSPECIFIED((CONST SOCKADDR_IN6*)a);
    } else {
        ASSERT(a->sa_family == AF_INET);
        return IN4ADDR_ISUNSPECIFIED((CONST SOCKADDR_IN*)a);
    }
}

MSTCPIP_INLINE
SCOPE_ID
INETADDR_SCOPE_ID(CONST SOCKADDR *a)
{
    if (a->sa_family == AF_INET6) {
        return ((CONST SOCKADDR_IN6*)a)->sin6_scope_struct;
    } else {
        ASSERT(a->sa_family == AF_INET);
        return IN4ADDR_SCOPE_ID((CONST SOCKADDR_IN*)a);
    }
}

MSTCPIP_INLINE
USHORT
INETADDR_PORT(CONST SOCKADDR *a)
{
    if (a->sa_family == AF_INET6) {
        return ((CONST SOCKADDR_IN6*)a)->sin6_port;
    } else {
        ASSERT(a->sa_family == AF_INET);
        return ((CONST SOCKADDR_IN*)a)->sin_port;
    }
}

MSTCPIP_INLINE
PUCHAR
INETADDR_ADDRESS(CONST SOCKADDR* a)
{
    if (a->sa_family == AF_INET6) {
        return (PUCHAR)&((PSOCKADDR_IN6)a)->sin6_addr;
    } else {
        ASSERT(a->sa_family == AF_INET);
        return (PUCHAR)&((PSOCKADDR_IN)a)->sin_addr;
    }
}

MSTCPIP_INLINE
VOID
INET_UNCANONICALIZE_SCOPE_ID(
    IN ADDRESS_FAMILY AddressFamily,
    IN CONST UCHAR *Address, 
    IN OUT SCOPE_ID *ScopeId
    ) 
{
    if (AddressFamily == AF_INET6) {
        IN6_UNCANONICALIZE_SCOPE_ID((CONST IN6_ADDR*) Address, ScopeId);
    } else {
        IN4_UNCANONICALIZE_SCOPE_ID((CONST IN_ADDR*) Address, ScopeId);
    }
}

#endif // _WS2IPDEF_

#pragma warning(pop)

#ifdef MSTCPIPDEF_ASSERT_UNDEFINED
#undef ASSERT
#endif

#ifdef __cplusplus
}
#endif

#endif // !_MSTCPIP_
