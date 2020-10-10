/*++

Copyright (c) 2000-2001  Microsoft Corporation

Module Name:

    nldef.h

Abstract:

    This module contains basic network layer definitions.
    Previously some of these were duplicated in both routprot.h and
    iprtrmib.h.

Author:

    Dave Thaler (dthaler) 12-Apr-2001

Environment:

    user mode or kernel mode

--*/

#ifndef _NLDEF_
#define _NLDEF_
#pragma once

typedef enum {
    //
    // These values are from iptypes.h.
    // They need to fit in a 4 bit field.
    //
    IpPrefixOriginOther = 0,
    IpPrefixOriginManual,
    IpPrefixOriginWellKnown,
    IpPrefixOriginDhcp,
    IpPrefixOriginRouterAdvertisement,
    IpPrefixOriginUnchanged = 1 << 4
} NL_PREFIX_ORIGIN;

//
// TODO: Remove these definitions.
//
#define NlpoOther               IpPrefixOriginOther
#define NlpoManual              IpPrefixOriginManual
#define NlpoWellKnown           IpPrefixOriginWellKnown
#define NlpoDhcp                IpPrefixOriginDhcp
#define NlpoRouterAdvertisement IpPrefixOriginRouterAdvertisement

typedef enum {
    //
    // TODO: Remove the Nlso* definitions.
    //
    NlsoOther = 0,
    NlsoManual,
    NlsoWellKnown,
    NlsoDhcp,
    NlsoLinkLayerAddress,
    NlsoRandom,

    //
    // These values are from in iptypes.h.
    // They need to fit in a 4 bit field.
    //
    IpSuffixOriginOther = 0,
    IpSuffixOriginManual,
    IpSuffixOriginWellKnown,
    IpSuffixOriginDhcp,
    IpSuffixOriginLinkLayerAddress,
    IpSuffixOriginRandom,
    IpSuffixOriginUnchanged = 1 << 4
} NL_SUFFIX_ORIGIN;

typedef enum {
    //
    // TODO: Remove the Nlds* definitions.
    //
    NldsInvalid,
    NldsTentative,
    NldsDuplicate,
    NldsDeprecated,
    NldsPreferred,

    //
    // These values are from in iptypes.h.
    //
    IpDadStateInvalid    = 0,
    IpDadStateTentative,
    IpDadStateDuplicate,
    IpDadStateDeprecated,
    IpDadStatePreferred,
} NL_DAD_STATE;

//
// MIB_IPPROTO_* values were previously in iprtrmib.h.
// PROTO_IP_* values were previously in routprot.h.
//
#define MAKE_ROUTE_PROTOCOL(suffix, value) \
    MIB_IPPROTO_ ## suffix = value, \
    PROTO_IP_ ## suffix    = value

//
// Routing protocol values from RFC.
//
typedef enum {
    //
    // TODO: Remove the RouteProtocol* definitions.
    //
    RouteProtocolOther   = 1,
    RouteProtocolLocal   = 2,
    RouteProtocolNetMgmt = 3,
    RouteProtocolIcmp    = 4,
    RouteProtocolEgp     = 5,
    RouteProtocolGgp     = 6,
    RouteProtocolHello   = 7,
    RouteProtocolRip     = 8,
    RouteProtocolIsIs    = 9,
    RouteProtocolEsIs    = 10,
    RouteProtocolCisco   = 11,
    RouteProtocolBbn     = 12,
    RouteProtocolOspf    = 13,
    RouteProtocolBgp     = 14,

    MAKE_ROUTE_PROTOCOL(OTHER,   1),
    MAKE_ROUTE_PROTOCOL(LOCAL,   2),
    MAKE_ROUTE_PROTOCOL(NETMGMT, 3),
    MAKE_ROUTE_PROTOCOL(ICMP,    4),
    MAKE_ROUTE_PROTOCOL(EGP,     5),
    MAKE_ROUTE_PROTOCOL(GGP,     6),
    MAKE_ROUTE_PROTOCOL(HELLO,   7),
    MAKE_ROUTE_PROTOCOL(RIP,     8),
    MAKE_ROUTE_PROTOCOL(IS_IS,   9),
    MAKE_ROUTE_PROTOCOL(ES_IS,  10),
    MAKE_ROUTE_PROTOCOL(CISCO,  11),
    MAKE_ROUTE_PROTOCOL(BBN,    12),
    MAKE_ROUTE_PROTOCOL(OSPF,   13),
    MAKE_ROUTE_PROTOCOL(BGP,    14),

    //
    // Windows-specific definitions.
    //
    MAKE_ROUTE_PROTOCOL(NT_AUTOSTATIC,     10002),
    MAKE_ROUTE_PROTOCOL(NT_STATIC,         10006),
    MAKE_ROUTE_PROTOCOL(NT_STATIC_NON_DOD, 10007),

} NL_ROUTE_PROTOCOL, *PNL_ROUTE_PROTOCOL;

typedef enum {
    NlatUnspecified,
    NlatUnicast,
    NlatAnycast,
    NlatMulticast,
    NlatBroadcast
} NL_ADDRESS_TYPE, *PNL_ADDRESS_TYPE;

#endif // _NLDEF_
