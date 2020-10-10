/*++

Copyright (c) 2000-2001  Microsoft Corporation

Module Name:

    ifdef.h

Abstract:

    This module contains IF_* definitions.

Author:

    Dave Thaler (dthaler) 12-Apr-2001

Environment:

    user mode or kernel mode

--*/

#ifndef _IFDEF_
#define _IFDEF_
#pragma once


typedef ULONG32 NET_IF_OBJECT_ID, *PNET_IF_OBJECT_ID;


typedef enum _NET_IF_ADMIN_STATUS   // ifAdminStatus
{
    NET_IF_ADMIN_STATUS_UP = 1,
    NET_IF_ADMIN_STATUS_DOWN = 2,
    NET_IF_ADMIN_STATUS_TESTING = 3
} NET_IF_ADMIN_STATUS, *PNET_IF_ADMIN_STATUS;

typedef enum _NET_IF_OPER_STATUS   // ifOperStatus
{
    NET_IF_OPER_STATUS_UP = 1,
    NET_IF_OPER_STATUS_DOWN = 2,
    NET_IF_OPER_STATUS_TESTING = 3,
    NET_IF_OPER_STATUS_UNKNOWN = 4,
    NET_IF_OPER_STATUS_DORMANT = 5,
    NET_IF_OPER_STATUS_NOT_PRESENT = 6,
    NET_IF_OPER_STATUS_LOWER_LAYER_DOWN = 7
} NET_IF_OPER_STATUS, *PNET_IF_OPER_STATUS;

typedef UINT32 NET_IF_COMPARTMENT_ID, *PNET_IF_COMPARTMENT_ID;

//
// Define compartment ID type:
//
#define NET_IF_COMPARTMENT_ID_UNSPECIFIED   (NET_IF_COMPARTMENT_ID)0
#define NET_IF_COMPARTMENT_ID_PRIMARY       (NET_IF_COMPARTMENT_ID)1

#define NET_IF_OID_IF_ALIAS             0x00000001  // identifies the ifAlias string for an interface
#define NET_IF_OID_COMPARTMENT_ID       0x00000002  // identifies the compartment ID for an interface.
#define NET_IF_OID_NETWORK_GUID         0x00000003  // identifies the NetworkGuid for an interface.
#define NET_IF_OID_IF_ENTRY             0x00000004  // identifies statistics for an interface.

//
// Define NetworkGUID type:
//
typedef GUID NET_IF_NETWORK_GUID, *PNET_IF_NETWORK_GUID;

//
// Define macros for an "unspecified" NetworkGUID value to be used in structures
// that haven't had the NET_LUID field filled in yet.
//
#define NET_SET_UNSPECIFIED_NETWORK_GUID(_pNetworkGuid)
#define NET_IS_UNSPECIFIED_NETWORK_GUID(_NetworkGuidValue)


typedef enum _NET_IF_RCV_ADDRESS_TYPE // ifRcvAddressType
{
    NET_IF_RCV_ADDRESS_TYPE_OTHER = 1,
    NET_IF_RCV_ADDRESS_TYPE_VOLATILE = 2,
    NET_IF_RCV_ADDRESS_TYPE_NON_VOLATILE = 3
} NET_IF_RCV_ADDRESS_TYPE, *PNET_IF_RCV_ADDRESS_TYPE;

typedef struct _NET_IF_RCV_ADDRESS
{
    NET_IF_RCV_ADDRESS_TYPE ifRcvAddressType;
    USHORT                  ifRcvAddressLength;
    USHORT                  ifRcvAddressOffset; // from beginning of this struct
} NET_IF_RCV_ADDRESS, *PNET_IF_RCV_ADDRESS;


typedef struct _NET_IF_ALIAS
{
    USHORT  ifAliasLength;  // in bytes, of ifAlias string
    USHORT  ifAliasOffset;  // in bytes, from beginning of this struct
} NET_IF_ALIAS, *PNET_IF_ALIAS;

#pragma warning(push)
#pragma warning(disable:4214) // bit field types other than int
typedef union _NET_LUID
{
    ULONG64     Value;
    struct
    {
        ULONG64     Reserved:24;
        ULONG64     NetLuidIndex:24;
        ULONG64     IfType:16;                  // equal to IANA IF type
    }Info;
} NET_LUID, *PNET_LUID;
#pragma warning(pop)

typedef ULONG NET_IFINDEX, *PNET_IFINDEX;       // Interface Index (ifIndex)
typedef UINT16 NET_IFTYPE, *PNET_IFTYPE;        // Interface Type (IANA ifType)

#define NET_IFINDEX_UNSPECIFIED (NET_IFINDEX)(0)    // Not a valid ifIndex

//
// Definitions for NET_IF_INFORMATION.Flags
//
#define NIIF_HARDWARE_INTERFACE         0x00000001  // Set iff hardware

#define NIIF_WAN_TUNNEL_TYPE_UNKNOWN    ((ULONG)(-1))

//
// Define datalink interface access types.
//
typedef enum _NET_IF_ACCESS_TYPE
{
    NET_IF_ACCESS_LOOPBACK = 1,
    NET_IF_ACCESS_BROADCAST = 2,
    NET_IF_ACCESS_POINT_TO_POINT = 3,
    NET_IF_ACCESS_POINT_TO_MULTI_POINT = 4,
    NET_IF_ACCESS_MAXIMUM = 5
} NET_IF_ACCESS_TYPE, *PNET_IF_ACCESS_TYPE;


//
// Define datalink interface direction types.
//
typedef enum _NET_IF_DIRECTION_TYPE
{
    NET_IF_DIRECTION_SENDRECEIVE,
    NET_IF_DIRECTION_SENDONLY,
    NET_IF_DIRECTION_RECEIVEONLY,
    NET_IF_DIRECTION_MAXIMUM
} NET_IF_DIRECTION_TYPE, *PNET_IF_DIRECTION_TYPE;


typedef enum _NET_IF_CONNECTION_TYPE
{
   NET_IF_CONNECTION_DEDICATED = 1,
   NET_IF_CONNECTION_PASSIVE = 2,
   NET_IF_CONNECTION_DEMAND = 3,
   NET_IF_CONNECTION_MAXIMUM = 4
} NET_IF_CONNECTION_TYPE, *PNET_IF_CONNECTION_TYPE;


typedef enum _NET_IF_MEDIA_CONNECT_STATE
{
    MediaConnectStateUnknown,
    MediaConnectStateConnected,
    MediaConnectStateDisconnected
} NET_IF_MEDIA_CONNECT_STATE, *PNET_IF_MEDIA_CONNECT_STATE;

#define NET_IF_LINK_SPEED_UNKNOWN   ((ULONG64)(-1))

//
// Defines the duplex state of media
//
typedef enum _NET_IF_MEDIA_DUPLEX_STATE
{
    MediaDuplexStateUnknown,
    MediaDuplexStateHalf,
    MediaDuplexStateFull
} NET_IF_MEDIA_DUPLEX_STATE, *PNET_IF_MEDIA_DUPLEX_STATE;


// Special values for fields in NET_PHYSICAL_LOCATION
#define NIIF_BUS_NUMBER_UNKNOWN         ((ULONG)(-1))
#define NIIF_SLOT_NUMBER_UNKNOWN        ((ULONG)(-1))
#define NIIF_FUNCTION_NUMBER_UNKNOWN    ((ULONG)(-1))

typedef struct _NET_PHYSICAL_LOCATION
{
    ULONG                   BusNumber;          // Physical location
    ULONG                   SlotNumber;         // … for hardware
    ULONG                   FunctionNumber;     // … devices.
} NET_PHYSICAL_LOCATION, *PNET_PHYSICAL_LOCATION;

//
// maximum string size in -wchar- units
//
#define IF_MAX_STRING_SIZE 127

typedef struct _IF_COUNTED_STRING
{
    USHORT      Length; // in -Bytes-
    WCHAR       String[IF_MAX_STRING_SIZE + 1];
} IF_COUNTED_STRING, *PIF_COUNTED_STRING;

#define IF_MAX_PHYS_ADDRESS_LENGTH 32

typedef struct _IF_PHYSICAL_ADDRESS
{
    USHORT      Length;
    UCHAR       Address[IF_MAX_PHYS_ADDRESS_LENGTH];
} IF_PHYSICAL_ADDRESS, *PIF_PHYSICAL_ADDRESS;

//
// IF_LUID
//
// Define the locally unique datalink interface identifier type.
// This type is persistable.
//

typedef NET_LUID IF_LUID, *PIF_LUID;


//
// IF_INDEX
//
// Define the interface index type.
// This type is not persistable.
// This must be unsigned (not an enum) to replace previous uses of
// an index that used a DWORD type.
//

typedef NET_IFINDEX IF_INDEX, *PIF_INDEX;
#define IFI_UNSPECIFIED NET_IFINDEX_UNSPECIFIED


//
// Get definitions for IFTYPE and IF_ACCESS_TYPE.
//
#include <ipifcons.h>


//
// Types of tunnels (sub-type of IF_TYPE when IF_TYPE==IF_TYPE_TUNNEL). 
//
typedef enum {
    TUNNEL_TYPE_P2P_OVER_V4 = 0,
    TUNNEL_TYPE_P2P_OVER_V6,
    TUNNEL_TYPE_ISATAP,
    TUNNEL_TYPE_6TO4,
    TUNNEL_TYPE_TEREDO
} TUNNEL_TYPE, *PTUNNEL_TYPE;

//
// IF_ADMINISTRATIVE_STATE
//
// Datalink Interface Administrative State.
// Indicates whether the interface has been administratively enabled.
//

typedef enum _IF_ADMINISTRATIVE_STATE {
    IF_ADMINISTRATIVE_DISABLED,
    IF_ADMINISTRATIVE_ENABLED,
    IF_ADMINISTRATIVE_DEMANDDIAL,
} IF_ADMINISTRATIVE_STATE, *PIF_ADMINISTRATIVE_STATE;


//
// IF_MEDIA_SENSE_STATE
//
// Datalink Interface Media Sense State.
//

typedef enum _IF_MEDIASENSE_STATE {
    IF_MEDIASENSE_DISCONNECTING,    // Disconnecting from the remotesite.
    IF_MEDIASENSE_DISCONNECTED,     // Interface/remotesite is not connected.
    IF_MEDIASENSE_CONNECTING,       // Connecting to the remotesite.
    IF_MEDIASENSE_CONNECTED,        // Interface/remotesite is connected.
} IF_MEDIASENSE_STATE, *PIF_MEDIASENSE_STATE;


//
// Note: Interface is Operational iff
// ((MediaSense is Connected) and (AdministrativeState is Enabled))
// or
// ((MediaSense is Connected) and (AdministrativeState is OnDemand))
//
// !Operational iff
// ((MediaSense != Connected) or (AdministrativeState is Disabled))
//

//
// OperStatus values from RFC 2863
//
typedef enum {
    IfOperStatusUp = 1,
    IfOperStatusDown,
    IfOperStatusTesting,
    IfOperStatusUnknown,
    IfOperStatusDormant,
    IfOperStatusNotPresent,
    IfOperStatusLowerLayerDown
} IF_OPER_STATUS;

#endif // _IFDEF_

