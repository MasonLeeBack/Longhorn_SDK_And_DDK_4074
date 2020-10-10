/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    wsk.h

Abstract:

    This module contains the definitions and structures for
    the Windows Sockets Kernel-Mode Interface.

Environment:

    Kernel-Mode only

--*/

#ifndef _WSK_
#define _WSK_

#ifdef __cplusplus
extern "C" {
#endif

#include <ws2def.h>
#include <mswsockdef.h>

//
// Socket object. 
//
// 'FileObject' points to an NT file object that can be used in standard IO 
// routines like ZwReadFile, ZwWriteFile, etc...
//
// 'Dispatch' can be one of 4 types depending on the socket type:
// PWSK_PROVIDER_BASIC_DISPATCH, PWSK_PROVIDER_LISTEN_DISPATCH,
// PWSK_PROVIDER_DGRAM_DISPATCH, PWSK_PROVIDER_CONN_DISPATCH
//

typedef struct _WSK_SOCKET {
    CONST FILE_OBJECT *FileObject;
    CONST VOID        *Dispatch;
} WSK_SOCKET, *PWSK_SOCKET;

//
// Client object
//

typedef PVOID PWSK_CLIENT;

//
// WSK API calling convention
//

#define WSKAPI NTAPI

//
// Interface ID that WSK clients will use to
// bind to WSK providers
//

extern CONST NPIID NPI_WSK_INTERFACE_ID;

//
// WSK Provider characteristics that WSK clients use to decide
// whether to attach to a given WSK provider or not.
//

typedef struct _WSK_PROVIDER_CHARACTERISTICS {
    USHORT Version;
} WSK_PROVIDER_CHARACTERISTICS, *PWSK_PROVIDER_CHARACTERISTICS;

//
// Transport information structure
//

typedef struct _WSK_TRANSPORT {
    USHORT      Version; // Version of the transport
    USHORT      Type;    // Socket type
    ULONG       TransportProtocolId; // Protocol
    ULONG       NetworkProtocolId; // Address family
    GUID        ProviderId; 
} WSK_TRANSPORT, *PWSK_TRANSPORT;

//
// Buffer structure used for sending/receiving data.
// Mdl points to a chain of memory descriptors (scatter/gather list).
// The data described begin at 'Offset' and extend for 'Length' bytes.
// N.B. 'Offset' is required to lie entirely within the first MDL in 
// the chain.
//

typedef struct _WSK_BUF {
    PMDL          Mdl;    // Locked MDL chain
    ULONG         Offset; // Offset into the "first" Mdl in the chain
    SIZE_T        Length; // Length of data starting from Offset
} WSK_BUF, *PWSK_BUF;

//
// Opaque type used for indicating one or more WSK_BUF elements via 
// data indication upcalls
//

typedef ULONG_PTR WSK_BUF_INDICATION;

//
// WskTransmit Element
//

typedef struct _WSK_TX_ELEMENT {
    ULONG Flags;
    SIZE_T Length;
    union {
        struct {
            LARGE_INTEGER FileOffset;
            PFILE_OBJECT  FileObject;
        };
        PMDL              Mdl;
        PVOID             Address;
    };
} WSK_TX_ELEMENT, *PWSK_TX_ELEMENT;

//
// TP Element Flags
// 

#define WSK_FLAG_TXE_VA   0x1 // Virtual Address
#define WSK_FLAG_TXE_FILE 0x2 // FileObject
#define WSK_FLAG_TXE_MDL  0x8 // Locked MDL

//
// Identification structure used for conditional-accept.
//

typedef struct _WSK_INSPECT_ID {
    ULONG_PTR Key;
    ULONG SerialNumber;
} WSK_INSPECT_ID, *PWSK_INSPECT_ID;

//
// Actions that can be taken for connect request inspection
// on a conditional-accept listening socket.
//

typedef enum {
    WskInspectReject, // reject the connection request
    WskInspectAccept, // proceed with accept
    WskInspectPend,   // delay the decision (use WskResumeInspect later)
    WskInspectMax
} WSK_INSPECT_ACTION, *PWSK_INSPECT_ACTION;

//
// Event indication upcalls
//
// Event indications are delivered in arbitrary thread context, 
// likely (but not necessarily) at DPC level.
//

typedef
NTSTATUS
(WSKAPI * PFN_WSK_CLIENT_EVENT) (
    IN  PVOID  ClientContext,
    IN  ULONG  EventType,
    IN  PVOID  Information OPTIONAL,
    IN  SIZE_T InfoLength
    );
/*
 * Indicates client-specific control event. 
 *
 * Parameters:
 *  ClientContext - ClientContext value that was passed to the WSK provider
 *     during NMR attachment (in the WSK_CLIENT_NPI structure)
 *  EventType - None defined yet.
 *  Information - Optional event specific information. 
 *  InfoLength - Length of information.
 * Returns:
 *  STATUS_SUCCESS unless otherwise is specified by specific EventTypes.
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_RECVFROM_EVENT) (
    IN  PVOID              SocketContext,
    IN  ULONG              Flags,
    IN  WSK_BUF_INDICATION DataIndication OPTIONAL
    );
/*
 * Indicates that one or more datagrams have arrived on one of the datagram 
 * socket objects created by the client
 *
 * Parameters:
 *  SocketContext - Context value associated with the socket on which 
 *     datagram(s) were received.
 *  Flags - None defined yet.
 *  DataIndication - Opaque parameter that denotes one or more datagrams.
 *     Client must use WskEnumerateDatagrams to get the datagrams.
 *     NULL denotes that socket needs to be closed.
 * Returns:
 *  STATUS_SUCCESS - Datagram(s) were consumed and further indication should be
 *     made when new datagrams arrive.
 *  STATUS_PENDING - Datagram(s) were retained by the client and the data must 
 *     remain valid until released by the client. Further indication should be
 *     made when new datagrams arrive.
 *  STATUS_DATA_NOT_ACCEPTED - Datagram(s) could not be processed and should be
 *              buffered by the transport if possible or required by the 
 *              protocol. No further indication should be made until 
 *              message indication upcalls are specifically re-enabled. 
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_CONNECT_EVENT) (
    IN  PVOID       SocketContext,
    IN  PSOCKADDR   LocalAddr,
    IN  PSOCKADDR   RemoteAddr,
    IN  PWSK_SOCKET Socket OPTIONAL
    );
/*
 * Indicates that a connection request has arrived on one of the listening 
 * sockets created by the client. The WSK client should call either WskAccept
 * or WskCloseSocket on the new Socket object to accept or reject it at some
 * point. Note that when this upcall is made, the connection setup handshake
 * with the remote party may have already taken place.
 *
 * Parameters:
 *  SocketContext - Context value associated with the listening socket 
 *     on which connection request has been received.
 *  LocalAddr - The local transport address this connection request arrived on.
 *              Useful if the listening socket is bound to the wildcard address.
 *  RemoteAddr - Transport address of the remote party.
 *  Socket - The new connected socket object that represent the connection.
 *           NULL denotes that listening socket is to be closed. 
 * Returns:
 *  STATUS_SUCCESS - This is the only allowed return value.
 */

typedef
WSK_INSPECT_ACTION
(WSKAPI * PFN_WSK_INSPECT_EVENT) (
    IN  PVOID           SocketContext,
    IN  PSOCKADDR       LocalAddr,
    IN  PSOCKADDR       RemoteAddr,
    IN  PWSK_INSPECT_ID pInspectID OPTIONAL
    );
/*
 * Indicates that a connection request has arrived on a conditional-accept 
 * listening socket. This upcall is used only for conditional-accept sockets.
 * This indication allows the client to decide if it wants to proceed with 
 * regular connection acceptance before any actual connection setup handshake
 * with the remote party takes place. If the client decides to proceed with
 * regular acceptance than the WskConnectEvent upcall will be invoked later
 * if/when the connectin setup handshake with the remote party is performed
 * successfully.
 *
 * Parameters:
 *  SocketContext - Context value associated with the listening socket 
 *                  on which connection request has been received.
 *  LocalAddr - The local transport address this connection request arrived on.
 *              Useful if the listening socket is bound to the wildcard address.
 *  RemoteAddr - Transport address of the remote party.
 *  pInspectID - Pointer to the inspect ID structure. The connection request
 *               is identified via this structure (NOT via the pointer to the
 *               structure) until the WskConnectEvent upcall happens. 
 *               If the client wants to preserve the inspect ID then it needs to
 *               copy this structure to its own memory before returning from
 *               this upcall.
 *               NULL pInspectID denotes that listening socket is to be closed.
 * Returns:
 *   WskInspectReject - Reject the connection request immediately. Neither
 *                      WskConnectEvent nor WskAbortEvent will be invoked.
 *   WskInspectAccept - Proceed with regular acceptance. WskConnectEvent
 *                      or WskAbortEvent may be invoked.
 *   WskInspectPend - Delay the decision. Client may invoke WskResume later to
 *                    convey its decision. WskAbortEvent may be invoked in
 *                    the meantime.
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_ABORT_EVENT) (
    IN  PVOID           SocketContext,
    IN  PWSK_INSPECT_ID pInspectID
    );
/*
 * Indicates that a previous connection request indicated by WskInspectEvent
 * upcall is dropped. This upcall is used only for conditional-accept sockets.
 *
 * Parameters:
 *  SocketContext - Context value associated with the listening socket 
 *                  on which connection request was received.
 *  pInspectID - Pointer to the inspect ID structure. The connection request
 *               is identified via this structure (NOT via the pointer to the
 *               structure.) If the client wants to preserve the inspect ID then
 *               it needs to copy this sturcture to its own memory before 
 *               returning from this upcall.
 * Returns:
 *  STATUS_SUCCESS - This is the only allowed return value.
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_SEND_BACKLOG_EVENT) (
    IN  PVOID  SocketContext,
    IN  SIZE_T IdealBacklogSize
    );
/*
 * Indicates that the ideal send backlog size has changed for the connection.
 * The ideal send backlog size denotes the optimal amount of send data that
 * needs to be kept outstanding (passed to the WSK provider, but not completed
 * by the WSK provider yet) in order to keep the data pipe full at all times.
 *
 * Parameters:
 *  SocketContext - Context value associated with the socket object.
 *  IdealBacklogSize - Ideal send backlog size
 * Returns:
 *  STATUS_SUCCESS - This is the only allowed return value.
 */

//
// Flag that denotes out-of-band data 
//

#define WSK_FLAG_OOB 0x1

//
// Flag that denotes that the indicated buffers should NOT be
// retained by the client indefinitely. The client should
// avoid retaining such buffers, but if it does retain, then
// it has to release them ASAP.
//

#define WSK_FLAG_RELEASE_ASAP 0x2

typedef
NTSTATUS
(WSKAPI * PFN_WSK_RECV_EVENT) (
    IN  PVOID              SocketContext,
    IN  ULONG              Flags,
    IN  WSK_BUF_INDICATION DataIndication OPTIONAL
    );
/*
 * Indicates that data has arrived on one of the connected socket objects
 * created by the client
 *
 * Parameters:
 *  SockContext - Context value associated with the socket object on which
 *     data was received.
 *  Flags - WSK_FLAG_OOB, WSK_FLAG_RELEASE_ASAP
 *  DataIndication - Opaque parameter that denotes one or more data buffers
 *    Client must use WskEnumerateBuffers to get the buffers.
 *    NULL denotes that socket needs to be closed.
 * Returns:
 *  STATUS_SUCCESS - Data buffer(s) were consumed and further indication 
 *     should be made when more data arrives.
 *  STATUS_PENDING - Data buffer(s) were retained by the client and the data 
 *     must remain valid until released. Further indications should be made
 *     when more data arrives.
 *  STATUS_DATA_NOT_ACCEPTED - Data buffer(s) could not be processed and should
 *     be buffered by the transport if possible or required by the protocol.
 *     No further indications will be made until the client posts a WskRecv
 *     request and it gets completed.
 */

//
// Flags for indicating abortive/graceful connection teardown
//

#define WSK_FLAG_ABORTIVE 0x1

typedef
NTSTATUS
(WSKAPI * PFN_WSK_DISCONN_EVENT) (
    IN  PVOID         SocketContext,
    IN  ULONG         Flags
    );
/*
 * Indicates that peer of the connection has initiated disconnect sequence.
 *
 * Parameters:
 *  SocketContext - Context associated with the connected socket object.
 *  Flags - indicates whether disconnect is graceful or abortive (if the
 *     WSK_FLAG_ABORTIVE flag is set, it's abortive, otherwise it's graceful.)
 * Returns:
 *  STATUS_SUCCESS - This is the only allowed return value.
 */

//
// Flags for enabling upcalls via WskControlSocket call with SO_SETEVENT option.
//

#define WSK_FLAG_RECVFROM_UPCALL      0x00000100
#define WSK_FLAG_CONNECT_UPCALL       0x00000200
#define WSK_FLAG_SEND_BACKLOG_UPCALL  0x00000010
#define WSK_FLAG_RECV_UPCALL          0x00000040
#define WSK_FLAG_DISCONN_UPCALL       0x00000080

//
// Flag for disabling a given upcall type via WskControlSocket call with 
// SO_SETEVENT option.
//
#define WSK_FLAG_DISABLE_UPCALL       0x80000000

//
// Flags denoting WSK socket types
//

#define WSK_FLAG_LISTEN_SOCK 0x00000001
#define WSK_FLAG_CONN_SOCK   0x00000002
#define WSK_FLAG_DGRAM_SOCK  0x00000004

typedef
NTSTATUS
(WSKAPI * PFN_WSK_SOCKET) (
    IN  PWSK_CLIENT          Client,
    IN  ULONG                AddressFamily,
    IN  ULONG                Type,
    IN  ULONG                Protocol,
    IN  ULONG                Flags,
    IN  PVOID                SocketContext OPTIONAL,
    IN  CONST VOID          *Upcalls OPTIONAL,
    IN  PEPROCESS            OwningProcess OPTIONAL,
    IN  PETHREAD             OwningThread OPTIONAL,
    IN  PSECURITY_DESCRIPTOR SecurityDescriptor OPTIONAL,
    IN  PIRP                 Irp
    );
/*
 * Creates socket object
 *
 * Parameters:
 *
 *  Client - Pointer to the client object (returned in the Client field 
 *           of the WSK_PROVIDER_NPI structure during NMR attachment)
 *  AddressFamily - address family, e.g. AF_INET, AF_INET6
 *  Type - socket type, e.g. SOCK_STREAM, SOCK_DGRAM
 *  Protocol - protocol, e.g. IPPROTO_TCP, IPPROTO_UDP
 *  flags - WSK_FLAG_LISTEN_SOCK - This socket will be used for listening
 *          WSK_FLAG_CONN_SOCK - This socket will be connection-oriented
 *          WSK_FLAG_DGRAM_SOCK - This socket will be used for datagram 
 *          Not specifying any of the above flags creates a basic socket.
 *  SocketContext - Context value to pass in event upcalls
 *  Upcalls - pointer to a constant structure that contains pointers to 
 *            upcall routines. OPTIONAL if client won't be enabling upcalls.
 *            Client must provide the right upcall table based on socket type:
 *            WSK_CLIENT_LISTEN_DISPATCH if WSK_FLAG_LISTEN_SOCK was specified
 *            WSK_CLIENT_CONN_DISPATCH if WSK_FLAG_CONN_SOCK was specified
 *            WSK_CLIENT_DGRAM_DISPATCH if WSK_FLAG_DGRAM_SOCK was specified 
 *  OwningProcess - The process to retrieve the security context from. If this
 *                  is set to NULL then the current process is assumed. This is
 *                  used for implementing transport address security during bind.
 *  OwningThread  - The thread to retrieve the security context from. This is
 *                  useful only if an impersonation token is in effect and used
 *                  for implementing transport address security during bind.
 *  SecurityDescriptor - Optional security descriptor to protect the transport 
 *                       address that this socket will be bound to. Only the
 *                       security descriptors obtained from the NT object 
 *                       manager's security descriptor cache can be specified.
 *  Irp - IRP for async completion of the request
 *
 * Returns:
 *
 *  If the request is completed succesfully, the Irp.IoStatus.Information
 *  field will be holding a pointer to the new socket (PWSK_SOCKET)
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

//
// Forward declaration for connected socket upcall table
//

typedef struct _WSK_CLIENT_CONN_DISPATCH 
    WSK_CLIENT_CONN_DISPATCH, *PWSK_CLIENT_CONN_DISPATCH;

typedef
NTSTATUS
(WSKAPI * PFN_WSK_SOCKET_CONNECT) (
    IN  PWSK_CLIENT                      Client,
    IN  ULONG                            Type,
    IN  ULONG                            Protocol,
    IN  PSOCKADDR                        LocalAddr,
    IN  PSOCKADDR                        RemoteAddr,
    IN  ULONG                            Flags,
    IN  PVOID                            SocketContext OPTIONAL,
    IN  CONST WSK_CLIENT_CONN_DISPATCH  *Upcalls OPTIONAL,
    IN  PEPROCESS                        OwningProcess OPTIONAL,
    IN  PETHREAD                         OwningThread OPTIONAL,
    IN  PSECURITY_DESCRIPTOR             SecurityDescriptor OPTIONAL,
    IN  PIRP                             Irp
    );
/*
 * Creates, binds, and connects a socket object.
 *
 * Parameters:
 *  Client - Pointer to the client object (returned in the Client field 
 *           of the WSK_PROVIDER_NPI structure during NMR attachment)
 *  Type - socket type, e.g. SOCK_STREAM, SOCK_DGRAM
 *  Protocol - protocol, e.g. IPPROTO_TCP, IPPROTO_UDP
 *  LocalAddr - Local address to bind the socket to.
 *  RemoteAddr - Remote address to connect to.
 *  Flags - None defined.
 *  SocketContext - Context value to pass in event upcalls
 *  Upcalls - pointer to a constant structure that contains pointers to 
 *     upcall routines. OPTIONAL if client won't be enabling upcalls.
 *  OwningProcess - The process to retrieve the security context from. If this
 *                  is set to NULL then the current process is assumed. This is
 *                  used for implementing transport address security during bind.
 *  OwningThread  - The thread to retrieve the security context from. This is
 *                  useful only if an impersonation token is in effect and used
 *                  for implementing transport address security during bind.
 *  SecurityDescriptor - Optional security descriptor to protect the transport 
 *                       address that this socket will be bound to. Only the
 *                       security descriptors obtained from the NT object 
 *                       manager's security descriptor cache can be specified.
 *  Irp - IRP for async completion of the request
 *
 * Returns:
 *
 *  If the request is completed succesfully, the Irp.IoStatus.Information
 *  field will be holding a pointer to the new socket (PWSK_SOCKET)
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

//
// Client Level Control Codes
//

#define WSK_QUERY_IRP_STACK_SIZE 1
#define WSK_TRANSPORT_LIST_QUERY 2
#define WSK_TRANSPORT_LIST_CHANGE 3

typedef
NTSTATUS
(WSKAPI * PFN_WSK_CONTROLCLIENT) (
    IN  PWSK_CLIENT    Client,
    IN  ULONG          ControlCode,
    IN  SIZE_T         InputSize,
    IN  PVOID          InputBuffer OPTIONAL,
    IN  SIZE_T         OutputSize,
    OUT PVOID          OutputBuffer OPTIONAL,
    OUT SIZE_T        *pOutputSize OPTIONAL,
    IN  PIRP           Irp OPTIONAL
    );
/*
 * Issues control request to WSK subsystem, e.g., registration for protocol 
 * change notifications, etc.
 *
 * Parameters:
 *  Client      - client object (as described in PFN_WSK_SOCKET)
 *  ControlCode - request code. currently defined codes are:
 *               WSK_QUERY_IRP_STACK_SIZE - Query the required IRP stack size.
 *               Irp must be NULL. InputSize, InputBuffer, and pOutputSize are
 *               ignored. OutputBuffer must point to a CCHAR, OutputSize
 *               must be sizeof(CCHAR).
 *               WSK_TRANSPORT_LIST_QUERY - Retrieves the array of transports
 *               into the OutputBuffer. InputSize and InputBuffer parameters
 *               are ignored. Irp must be NULL and pOutputSize must be Non-NULL.
 *               WSK_TRANSPORT_LIST_CHANGE - Notifies the client when a 
 *               transport is added or removed. InputSize/InputBuffer, 
 *               OutputSize/OutputBuffer, and pOutputSize parameters are
 *               ignored. Irp must be specified. 
 *  InputSize - size of the input data residing in InputBuffer
 *  InputBuffer - buffer that holds input data
 *  OutputSize - size of the OutputBuffer
 *  OutputBuffer - buffer that will hold output data
 *  pOutputSize - address of a variable that will contain the actual size of
 *                data copied into the OutputBuffer. This parameter is ignored
 *                if the Irp parameter is specified.
 *  Irp - IRP for the asynchronous completion of the request. Upon completion,
 *        Irp->Iostatus.Information will hold the actual size of data copied
 *        into the OutputBuffer.
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later (Irp was specified.)
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_BIND) (
    IN  PWSK_SOCKET     Sock,
    IN  PSOCKADDR       Name,
    IN  ULONG           Flags,
    IN  PIRP            Irp
    );
/*
 * Bind local (unicast or multicast) tranport address to a socket 
 *
 * Parameters:
 *  Sock   - socket object to bind address to
 *  Name   - transport address specification
 *  Flags  - None defined.
 *  Irp    - IRP for async completion
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_CONNECT) (
    IN  PWSK_SOCKET     Sock,
    IN  PSOCKADDR       Name,
    IN  ULONG           Flags,
    IN  PIRP            Irp
    );
/*
 * Establish comunication with the entity or group specified by the transport
 * address by means appropriate for the protocol (e.g. run protocol to 
 * establish a VC and/or make sure the address is reachable and/or
 * cache the routing entry, etc)
 *
 * Parameters:
 *  Sock - socket object to establish connection for
 *  Name - transport address specification
 *  Flags - None defined yet.
 *  Irp - IRP for async completion
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

//
// Option/IOCTL Levels
//

//
// Socket Level Options specific to WSK
// (Standard socket level options are defined in netiodef.h)
//

#define SO_SET_SECURITY 0x4001
#define SO_SETEVENT 0x4002

//
// Structure used for setting security
//
typedef struct _WSK_SET_SECURITY {
    PSECURITY_DESCRIPTOR SecurityDescriptor;
} WSK_SET_SECURITY, *PWSK_SET_SECURITY;

//
// Structure used with SO_SETEVENT to enable/disable upcalls
//
typedef struct _WSK_EVENT_CONTROL {
    PNPIID NpiId;
    ULONG  EventMask;
} WSK_EVENT_CONTROL, *PWSK_EVENT_CONTROL;

//
// Socket level IOCTL codes
//

#define SIO_ADDRESS_LIST_QUERY        _WSAIOR(IOC_WS2,22)
#define SIO_ADDRESS_LIST_CHANGE       _WSAIO(IOC_WS2,23)
#define SIO_SET_PEER_ADDRESS          _WSAIOW(IOC_WS2,0x80)
#define SIO_REGISTER_EXTENSION        _WSAIORW(IOC_WS2,0x81)
#define SIO_QUERY_IDEAL_SEND_BACKLOG  _WSAIOR(IOC_WS2,0x82)
#define SIO_QUERY_RECEIVE_BACKLOG     _WSAIOR(IOC_WS2,0x83)
#define SIO_QUERY_INSPECT_ID          _WSAIOR(IOC_WS2,0x84)

//
// Structure used with SIO_ADDRESS_LIST_QUERY
//
typedef struct _WSK_SOCKADDR_LIST {
    ULONG AddressCount;
    PSOCKADDR Address[ANYSIZE_ARRAY];
} WSK_SOCKADDR_LIST, *PWSK_SOCKADDR_LIST;

//
// Input structure used with SIO_REGISTER_EXTENSION
//
typedef struct _WSK_EXTENSION_CONTROL_IN {
    PNPIID      NpiId;
    PVOID       ClientContext;
    CONST VOID* ClientDispatch;
} WSK_EXTENSION_CONTROL_IN, *PWSK_EXTENSION_CONTROL_IN;

//
// Output structure used with SIO_REGISTER_EXTENSION
//
typedef struct _WSK_EXTENSION_CONTROL_OUT {
    PVOID       ProviderContext;
    CONST VOID* ProviderDispatch;
} WSK_EXTENSION_CONTROL_OUT, *PWSK_EXTENSION_CONTROL_OUT;


typedef enum {
    WskSetOption, // set socket option
    WskGetOption, // get socket option
    WskIoctl,     // socket IOCTL
    WskControlMax
} WSK_CONTROLSOCK_TYPE, *PWSK_CONTROLSOCK_TYPE;

typedef
NTSTATUS
(WSKAPI * PFN_WSK_CONTROL_SOCKET) (
    IN  PWSK_SOCKET          Sock,
    IN  WSK_CONTROLSOCK_TYPE RequestType,
    IN  ULONG                ControlCode,
    IN  ULONG                Level,
    IN  SIZE_T               InputSize,
    IN  PVOID                InputBuffer OPTIONAL,
    IN  SIZE_T               OutputSize,
    OUT PVOID                OutputBuffer OPTIONAL,
    OUT SIZE_T              *pOutputSize OPTIONAL,
    IN  PIRP                 Irp OPTIONAL
    );
/*
 *
 * Parameters:
 *  Sock   - socket object
 *  RequestType - WskSetOption, WskGetOption, or WskIoctl
 *  ControlCode - what kind of the request
 *  Level - SOL_SOCKET for socket-level options/ioctls,
 *          Protocol number for transport/network specific options/ioctls
 *  InputSize - size of the input data residing in InputBuffer
 *  InputBuffer - buffer that holds input data
 *  OutputSize - size of the OutputBuffer
 *  OutputBuffer - buffer that will hold output data
 *  pOutputSize - if Irp is NULL for a ControlCode than this parameter
 *                must be specified to store the number of bytes written
 *                into OutputBuffer upon in-line completion of the request.
 *  Irp - IRP for the asynchronous completion of the request. Upon completion,
 *        Irp->Iostatus.Information will hold the actual size of data copied
 *        into the OutputBuffer. This will be either a required parameter or
 *        ignored (and must be NULL), or optional based on the ControlCode.
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  STATUS_REQUEST_NOT_ACCEPTED - Inline completion is not possible.
 *  PENDING - request will be completed later (Irp was specified.)
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_CLOSE_SOCKET) (
    IN  PWSK_SOCKET       Sock,
    IN  PIRP              Irp OPTIONAL
    );
/*
 * Invalidates socket object, initiates cancellation of
 * all outstanding requests. If this call is invoked with a NULL Irp then
 * the socket will be attempted to be closed inline. If inline closure
 * is not possible then STATUS_REQUEST_NOT_ACCEPTED is returned.
 * Once WskCloseSocket is invoked on a socket, it is illegal to issue any
 * further calls on that socket with one exception: If WskCloseSocket 
 * returns STATUS_REQUEST_NOT_ACCEPTED then the client is required to
 * invoke WskCloseSocket again at some point in which case the client may do 
 * one of the following:
 *   1) invoke WskCloseSocket with an Irp
 *   2) invoke WskCloseSocket with a NULL Irp and if the return code is still
 *      STATUS_REQUEST_NOT_ACCEPTED then invoke WskCloseSocket again at some 
 *      point.
 *
 * Parameters:
 *  Sock - Socket to be closed.
 *  Irp - notification method to trigger when operation completes. 
 *     This is a required parameter.
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later (Irp was specified)
 *  STATUS_REQUEST_NOT_ACCEPTED - request can not be completed inline. Client
 *                                is required to issue WskCloseSocket again.
 *  FAILURES - request failed
 */

#define WSK_FLAG_ACCEPT 0x1

typedef
NTSTATUS
(WSKAPI * PFN_WSK_LISTEN) (
    IN  PWSK_SOCKET                     ListenSock,
    IN  ULONG                           Flags,
    IN  PVOID                           SocketContext OPTIONAL,
    IN  CONST WSK_CLIENT_CONN_DISPATCH *Upcalls OPTIONAL,
    OUT PSOCKADDR                       LocalAddr OPTIONAL,
    OUT PSOCKADDR                       RemoteAddr OPTIONAL,
    OUT PWSK_SOCKET                    *AcceptSock OPTIONAL,
    IN  PIRP                            Irp OPTIONAL
    );
/*
 * Dequeue (pend if it is not there) and return incoming connection request
 * on the specified listening socket. Transports will (in general) buffer
 * some incoming connections even if app has no listen IRPs posted.
 * However, buffer depth cannot be queried since it might vary with available
 * memory size.
 *
 * Parameters:
 *  ListenSock - listening socket to dequeue request from
 *  Flags - WSK_FLAG_ACCEPT
 *  SocketContext - context to be associated with the accepted socket object.
 *                This is passed as a parameter in event upcalls.
 *  Upcalls - pointer to a constant structure that contains pointers to upcall
 *            routines. OPTIONAL if client won't be enabling upcalls.
 *  LocalAddr - Optional buffer to return the local transport address on which
 *              this connection request arrived. Useful if listening socket is
 *              bound to the wildcard address. 
 *  RemoteAddr - Optional buffer to return the remote party's transport address. 
 *  AcceptSock - Place to return the socket representing the incoming connection
 *               for non-blocking requests (i.e., when Irp parameter is NULL.)
 *               This socket is created by WSK on behalf of the client. This 
 *               parameter is ignored for asynchronous requests (i.e., when the 
 *               Irp parameter is not NULL.) in which case a pointer to the 
 *               accepted socket is returned in the Irp->IoStatus.Information.
 *  Irp    - IRP for asynchronous completion of this operation. If this 
 *           parameter is not specified, operation is attempted inline and 
 *           failed if inline completion is not possible.
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later (Irp was specified.)
 *  STATUS_REQUEST_NOT_ACCEPTED - in-line completion is impossible
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_RESUME) (
    IN  PWSK_SOCKET                     ListenSock,
    IN  PWSK_INSPECT_ID                 pInspectID,
    IN  WSK_INSPECT_ACTION              Action,
    IN  PIRP                            Irp
    );
/*
 * Resume a previously pended inspect operation. This routine is valid only
 * for conditional-accept sockets.
 * 
 * Parameters:
 *  ListenSock - listening socket on which the inspect action was pended for 
 *               the connection request identified by the structure pointed
 *               by pInspectID.
 *  pInspectID - Pointer to the inspect ID structure that identified the pended
 *               connection request.
 *  Action - Only one of the following two actions is allowed:
 *
 *    WskInspectReject - Reject the connection request. WskConnectEvent won't
 *                       be invoked. WskAbortEvent may be invoked if the
 *                       connection request is dropped during WskResume call.
 *
 *    WskInspectAccept - Proceed with regular acceptance. WskConnectEvent
 *                       or WskAbortEvent may be invoked.
 *
 *  Irp    - IRP for asynchronous completion of this operation. This is a
 *           required parameter.
 *
 * Returns:
 *
 *  STATUS_SUCCESS - request succeeded
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_SENDTO) (
    IN  PWSK_SOCKET     Sock,
    IN  PWSK_BUF        Buffer,
    IN  ULONG           Flags,
    IN  PSOCKADDR       Name,
    IN  ULONG           ControlInfoLength,
    IN  PCMSGHDR        ControlInfo OPTIONAL,
    IN  PIRP            Irp
    );
/*
 * Send to the specified remote entity or group from the specified
 * datagram socket. Socket must have been bound to a local address.
 *
 * Parameters:
 *  Sock   - datagram socket object to send from
 *  Buffer  - data to send
 *  Flags   - None defined yet.
 *  Name    - remote transport address
 *  ControlInfo - additional information to pass to the remote party. 
 *                Might not be supported by all transports.
 *  ControlInfoLength - length of control info
 *  Irp - notification method to trigger when operation completes
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_RECVFROM) (
    IN  PWSK_SOCKET     Sock,
    IN OUT PWSK_BUF     Buffer,
    IN  ULONG           Flags,
    OUT PSOCKADDR       Name OPTIONAL,
    IN OUT PULONG       ControlLength OPTIONAL,
    OUT PCMSGHDR        ControlInfo OPTIONAL,
    OUT PULONG          ControlFlags OPTIONAL,
    IN  PIRP            Irp
    );
/*
 * Dequeue (pend if it is not there) and return incoming data packet on the
 * specified datagram socket.
 *
 * Parameters:
 *  Sock   - socket to dequeue packet from
 *  Buffer  - place to put incoming data into
 *  Flags   - None defined yet.
 *  Name    - place to put transport address of the remote party that 
 *     sent the packet
 *  ControlLength - Pointer to a ULONG that specifies the length of buffer 
 *     pointed by ControlInfo on input, and the length of actual control data
 *     copied into ControlInfo buffer on output. If ControlLength is NULL
 *     then ControlInfo and ControlFlags parameters are ignored. 
 *     If ControlLength is non-NULL then ControlLength should be pointing to
 *     valid memory until the request completes. 
 *  ControlInfo - Pointer to a buffer into which WSK copies the control data 
 *     received with the datagram. This parameter is ignored if 
 *     ControlLength parameter is NULL. Otherwise, if ControlInfo should 
 *     be pointing to valid memory until the request completes. 
 *  ControlFlags - Pointer to a ULONG through which WSK may pass the following
 *     flags when the request completes: MSG_MCAST, MSG_BCAST, MSG_TRUNC, 
 *     MSG_CTRUNC. This parameter is ignored if ControlLength parameter is NULL.
 *     Otherwise, ControlFlags should be pointing to valid memory until the 
 *     request completes.  
 *  Irp - notification method to trigger when operation completes
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_GETLOCALADDR) (
    IN  PWSK_SOCKET       Sock,
    OUT PSOCKADDR       Name,
    IN  PIRP            Irp OPTIONAL
    );
/*
 * Retrieve the transport address associated with this Socket object. This is
 * useful when a socket is not bound to a transport address prior to calling 
 * connect on the socket. This call allows the client to determine the local 
 * address chosen by the transport for this connection.
 *
 * Parameters:
 *  Sock   - Socket whose local address is being queried
 *  Name    - local transport address
 *  Irp - Irp for async completion. 
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later (Irp was specified.)
 *  STATUS_REQUEST_NOT_ACCEPTED - in-line completion is impossible
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_GETPEERADDR) (
    IN  PWSK_SOCKET       Sock,
    OUT PSOCKADDR       Name,
    IN  PIRP            Irp OPTIONAL
    );
/*
 * Retrieve the transport address of the peer to which the socket is connected. 
 * Clients are always informed -- upon connection setup -- of the peer's 
 * address, so this call is useful if a socket is being shared between multiple
 * components of the client application. If one component set up the connection
 * and another component wishes to determine the peer address, it can do so via
 * this call.
 *
 * Parameters:
 *  Sock   - Socket whose local address is being queried
 *  Name    - peer's transport address
 *  Irp - Irp for async completion. 
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later (Irp was specified.)
 *  STATUS_REQUEST_NOT_ACCEPTED - in-line completion is impossible
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_RELEASE) (
    IN  PWSK_SOCKET         Sock,
    IN  WSK_BUF_INDICATION  DataIndication
    );
/*
 * Release buffer previously retained via STATUS_PENDING return code
 * in recv (connection-oriented socket) or recvfrom (datagram socket) event 
 * callback on this socket object.
 *
 * Parameters:
 *  Sock   - Socket on which buffer was received
 *  DataIndication  - Opaque parameter that denotes a list of buffers
 *
 * Returns:
 *  SUCCESS - request succeeded
 *  FAILURES - request failed
 */

typedef
PWSK_BUF
(WSKAPI * PFN_WSK_ENUMERATE_DATAGRAMS) (
    IN  PWSK_SOCKET         Sock,
    IN  WSK_BUF_INDICATION  DataIndication,
    IN  PWSK_BUF            CurrentDatagram,
    OUT PSOCKADDR          *From OPTIONAL,
    OUT ULONG              *ControlInfoLength OPTIONAL,
    OUT PCMSGHDR           *ControlInfo OPTIONAL
    );
/*
 * Enumerate the list of datagrams indicated by a recvfrom upcall.
 *
 * Parameters:
 *  Sock - Socket on which indication has arrived
 *  DataIndication - Opaque parameter that denotes a list of datagrams
 *  CurrentDatagram - pointer to last enumerated WSK_BUF. Use NULL to start.
 *  From - If not NULL, holds pointer to the sender's address on return. 
 *  ControlInfoLength - If not NULL, holds size of control information on return.
 *  ControlInfo - If not NULL, holds pointer to control information on return. 
 * Returns:
 *  NULL - There are no more datagrams left in the indication.
 *  Non-NULL - points to the WSK_BUF structure for the next datagram that 
 *    follows the CurrentDatagram
 */

typedef
PWSK_BUF
(WSKAPI * PFN_WSK_ENUMERATE_BUFFERS) (
    IN  PWSK_SOCKET         Sock,
    IN  WSK_BUF_INDICATION  DataIndication,
    IN  PWSK_BUF            CurrentBuffer
    );
/*
 * Enumerate the list of buffers indicated by a recv upcall.
 *
 * Parameters:
 *  Sock   - Socket on which indication had arrived
 *  DataIndication  - Opaque parameter that denotes a list of buffers
 *  CurrentBuffer -  pointer to last enumerated WSK_BUF. Use NULL to start.
 *
 * Returns:
 *  NULL - There are no more buffers left in the indication.
 *  Non-NULL - points to the next buffer that follows the CurrentBuffer
 */


typedef
NTSTATUS
(WSKAPI * PFN_WSK_ACCEPT) (
    IN  PWSK_SOCKET                     Sock,
    IN  ULONG                           Flags,
    IN  PVOID                           SocketContext OPTIONAL,
    IN  CONST WSK_CLIENT_CONN_DISPATCH *Upcalls OPTIONAL,
    IN  PIRP                            Irp OPTIONAL
    );
/*
 * Accept the specified connection request and optionally specify a
 * separate upcall event context and function pointers for newly accepted 
 * connection.
 *
 * Parameters:
 *  Sock - WSK_SOCKET object returned by WskListen or WskConnectEvent
 *  Flags - None defined yet.
 *  SockContext - context to pass in event upcalls for this connected socket
 *  Upcalls - pointer to a constant structure that contains pointers to upcall
 *     routines. OPTIONAL if client won't be enabling upcalls via SO_SETEVENT.
 *     This parameter (along with the SockContext parameter) is ignored if a 
 *     context  and upcall table pointer was already specified during the 
 *     original socket creation call.
 *  Irp - notification method to trigger when operation completes,
 *        if this parameter is not specified, operation is attempted
 *        inline and failed if inline completion is not possible. For
 *        connections arriving over a listening socket that was set for
 *        conditional acceptance, the IRP must always be specified.
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later (Irp was specified.)
 *  STATUS_REQUEST_NOT_ACCEPTED - in-line completion is impossible
 *  FAILURES - request failed
 */

//
// WskTransmitPackets Flags
//

#define WSK_FLAG_DISCONNECT        0x01
#define WSK_FLAG_USE_KERNEL_APC    0x20

typedef
NTSTATUS
(WSKAPI * PFN_WSK_TRANSMIT) (
    IN  PWSK_SOCKET      Sock,
    IN  PWSK_TX_ELEMENT  ElementArray,
    IN  ULONG            ElementCount,
    IN  ULONG            Flags,
    IN  PETHREAD         Thread OPTIONAL,
    IN  PIRP             Irp
    );
/*
 * Transmit an array of elements. An element can refer to a 
 * file object, virtual address, or locked MDL. 
 *
 * Parameters:
 *  Sock - Connected socket to transmit over.
 *  ElementArray - Array of WSK_TP_ELEMENTs
 *  ElementCount - Number of elements in the array
 *  Flags - WSK_FLAG_DISCONNECT, WSK_FLAG_USE_KERNEL_APC
 *  Thread - Optional parameter used for determining the process context
 *           for probing and locking VA elements. Here's how this parameter is
 *           interpreted based on the worker method:
 *
 *    If Thread is NULL:
 *
 *         Kernel APC: Current thread is assumed. If current thread's original
 *                     process is different from the current process (when
 *                     WskTransmit is called) then APCs will be queued to the
 *                     attached APC environment of the current thread, otherwise
 *                     to the original APC environment of the current thread.
 *
 *      System Thread: Current process is assumed. 
 *
 *
 *    If Thread is specified:
 *
 *         Kernel APC: APCs will be queued to the original APC environment of 
 *                     the speficied thread.
 *
 *      System Thread: Specified thread's original process is assumed.
 *
 *  Irp - notification method to trigger when operation completes.
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_SEND) (
    IN  PWSK_SOCKET     Sock,
    IN  PWSK_BUF        Buffer,
    IN  ULONG           Flags,
    IN  PIRP            Irp 
    );
/*
 * Send on the specified connected socket
 *
 * Parameters:
 *  Sock   - Socket to send on. Must have been connected or accepted
 *  Buffer  - data to send
 *  Flags   - WSK_FLAG_OOB: Expedited data is being sent
 *  Irp - notification method to trigger when operation completes
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_RECV) (
    IN  PWSK_SOCKET     Sock,
    IN OUT PWSK_BUF     Buffer,
    IN  ULONG           Flags,
    IN  PIRP            Irp
    );
/*
 * Dequeue (wait if it is not there) and return incoming data packet on the
 * specified connected socket
 *
 * Parameters:
 *  Sock   - Socket to dequeue data from. Must have been connected or accepted
 *  Buffer  - place to put incoming data into
 *  Flags   - WSK_FLAG_OOB: Receive only expedited data
 *  Irp - notification method to trigger when operation completes
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */

typedef
NTSTATUS
(WSKAPI * PFN_WSK_DISCONN) (
    IN  PWSK_SOCKET     Sock,
    IN  PWSK_BUF        Buffer OPTIONAL,
    IN  ULONG           Flags,
    IN  PIRP            Irp
    );
/*
 * Send disconnect notification on specified connected socket
 * with optional data.
 *
 * Parameters:
 *  Sock - Socket to disconnect. Must have been connected or accepted.
 *  Buffer - Optional data to send along with graceful disconnect.
 *  Flags - If WSK_FLAG_ABORTIVE is specified then perform abortive disconnect.
 *          Otherwise, perform graceful disconnect.
 *  Irp - notification method to trigger when operation completes. (Required)
 *
 * Returns:
 *
 *  SUCCESS - request succeeded
 *  PENDING - request will be completed later
 *  FAILURES - request failed
 */




//
// WSK Dispatch tables.
// WSK interface consists of routines implemented by both 
// the client and the provider. These routines operate
// at either client/provider level or socket level.
// Client/provider level function pointers are exchanged 
// during NMR attachment.
// Socket level function pointers are exchanged during
// socket creation.
//

//
// Client level upcall table
//

typedef struct _WSK_CLIENT_DISPATCH {
    USHORT               Version;
    USHORT               Reserved;
    PFN_WSK_CLIENT_EVENT WskClientEvent;
} WSK_CLIENT_DISPATCH, *PWSK_CLIENT_DISPATCH;

//
// Socket level upcalls for listening sockets
//

typedef struct _WSK_CLIENT_LISTEN_DISPATCH {
    PFN_WSK_CONNECT_EVENT       WskConnectEvent;
    PFN_WSK_INSPECT_EVENT       WskInspectEvent;
    PFN_WSK_ABORT_EVENT         WskAbortEvent;
} WSK_CLIENT_LISTEN_DISPATCH, *PWSK_CLIENT_LISTEN_DISPATCH;

//
// Socket level upcalls for datagram sockets
//

typedef struct _WSK_CLIENT_DGRAM_DISPATCH {
    PFN_WSK_RECVFROM_EVENT      WskRecvFromEvent;
} WSK_CLIENT_DGRAM_DISPATCH, *PWSK_CLIENT_DGRAM_DISPATCH;

//
// Socket level upcalls for connected sockets
//

typedef struct _WSK_CLIENT_CONN_DISPATCH {
    PFN_WSK_RECV_EVENT          WskRecvEvent;
    PFN_WSK_DISCONN_EVENT       WskDisconnEvent;
    PFN_WSK_SEND_BACKLOG_EVENT  WskSendBacklogEvent;
} WSK_CLIENT_CONN_DISPATCH, *PWSK_CLIENT_CONN_DISPATCH;


//
// Provider level downcall table
//

typedef struct _WSK_PROVIDER_DISPATCH {
    USHORT                    Version;
    USHORT                    Reserved;
    PFN_WSK_SOCKET            WskSocket;
    PFN_WSK_SOCKET_CONNECT    WskSocketConnect;
    PFN_WSK_CONTROLCLIENT     WskControlClient;
} WSK_PROVIDER_DISPATCH, *PWSK_PROVIDER_DISPATCH;

//
// Basic socket downcalls
// These routines are supported for all socket types.
//

typedef struct _WSK_PROVIDER_BASIC_DISPATCH {
    PFN_WSK_CONTROL_SOCKET       WskControlSocket;
    PFN_WSK_CLOSE_SOCKET         WskCloseSocket;
} WSK_PROVIDER_BASIC_DISPATCH, *PWSK_PROVIDER_BASIC_DISPATCH;

//
// Listening socket downcalls
//

typedef struct _WSK_PROVIDER_LISTEN_DISPATCH {
#ifdef __cplusplus
    WSK_PROVIDER_BASIC_DISPATCH Basic;
#else
    WSK_PROVIDER_BASIC_DISPATCH;
#endif
    PFN_WSK_BIND       WskBind;
    PFN_WSK_LISTEN     WskListen;
    PFN_WSK_RESUME     WskResume;
} WSK_PROVIDER_LISTEN_DISPATCH, *PWSK_PROVIDER_LISTEN_DISPATCH;

//
// Datagram socket downcalls
//

typedef struct _WSK_PROVIDER_DGRAM_DISPATCH {
#ifdef __cplusplus
    WSK_PROVIDER_BASIC_DISPATCH Basic;
#else
    WSK_PROVIDER_BASIC_DISPATCH;
#endif
    PFN_WSK_BIND                WskBind;
    PFN_WSK_SENDTO              WskSendTo;
    PFN_WSK_RECVFROM            WskRecvFrom;
    PFN_WSK_RELEASE             WskRelease;
    PFN_WSK_ENUMERATE_DATAGRAMS WskEnumerateDatagrams;
} WSK_PROVIDER_DGRAM_DISPATCH, *PWSK_PROVIDER_DGRAM_DISPATCH;


//
// Connected socket downcalls
//

typedef struct _WSK_PROVIDER_CONN_DISPATCH {
#ifdef __cplusplus
    WSK_PROVIDER_BASIC_DISPATCH Basic;
#else
    WSK_PROVIDER_BASIC_DISPATCH;
#endif
    PFN_WSK_BIND              WskBind;
    PFN_WSK_CONNECT           WskConnect;
    PFN_WSK_ACCEPT            WskAccept;
    PFN_WSK_GETLOCALADDR      WskGetLocalAddr;
    PFN_WSK_GETPEERADDR       WskGetPeerAddr;
    PFN_WSK_TRANSMIT          WskTransmit;
    PFN_WSK_SEND              WskSend;
    PFN_WSK_RECV              WskRecv;
    PFN_WSK_DISCONN           WskDisconn;
    PFN_WSK_RELEASE           WskRelease;
    PFN_WSK_ENUMERATE_BUFFERS WskEnumerateBuffers;
} WSK_PROVIDER_CONN_DISPATCH, *PWSK_PROVIDER_CONN_DISPATCH;


//
// WSK Client NPI
//

typedef struct _WSK_CLIENT_NPI {
    PVOID                        ClientContext;
    CONST WSK_CLIENT_DISPATCH   *Dispatch;    
} WSK_CLIENT_NPI, *PWSK_CLIENT_NPI;

//
// WSK Provider NPI
//

typedef struct _WSK_PROVIDER_NPI {
    PWSK_CLIENT                  Client;
    CONST WSK_PROVIDER_DISPATCH *Dispatch;    
} WSK_PROVIDER_NPI, *PWSK_PROVIDER_NPI;


#ifdef __cplusplus
}
#endif

#endif // _WSK_


