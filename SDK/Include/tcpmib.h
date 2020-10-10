/*++

Copyright (c) Microsoft Corporation

Module Name:

    tcpmib.h

Abstract:

    This module contains the public definitions and structures for the
    TCP-specific parts of MIB-II.  These definitions were previously
    in iprtrmib.h, which now includes this file.

Environment:

    user mode or kernel mode

--*/

#ifndef _TCPMIB_
#define _TCPMIB_
#pragma once

#ifndef ANY_SIZE
#define ANY_SIZE 1
#endif

//
// TCP states, as defined in the MIB.
//
typedef enum {
    MIB_TCP_STATE_CLOSED     =  1,
    MIB_TCP_STATE_LISTEN     =  2,
    MIB_TCP_STATE_SYN_SENT   =  3,
    MIB_TCP_STATE_SYN_RCVD   =  4,
    MIB_TCP_STATE_ESTAB      =  5,
    MIB_TCP_STATE_FIN_WAIT1  =  6,
    MIB_TCP_STATE_FIN_WAIT2  =  7,
    MIB_TCP_STATE_CLOSE_WAIT =  8,
    MIB_TCP_STATE_CLOSING    =  9,
    MIB_TCP_STATE_LAST_ACK   = 10,
    MIB_TCP_STATE_TIME_WAIT  = 11,
    MIB_TCP_STATE_DELETE_TCB = 12,
} MIB_TCP_STATE;


//
// Various Offload states a TCP connection can be in.
//
typedef enum {
    TcpConnectionOffloadStateInHost,
    TcpConnectionOffloadStateOffloading,
    TcpConnectionOffloadStateOffloaded,
    TcpConnectionOffloadStateUploading,
    TcpConnectionOffloadStateMax
} TCP_CONNECTION_OFFLOAD_STATE, *PTCP_CONNECTION_OFFLOAD_STATE;

typedef struct _MIB_TCPROW {
    union {
        DWORD dwState;       // Old field used DWORD type.
        MIB_TCP_STATE State; // New field uses enum type.
    };
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
    DWORD dwRemoteAddr;
    DWORD dwRemotePort;
} MIB_TCPROW, *PMIB_TCPROW;

typedef struct _MIB_TCPTABLE {
    DWORD dwNumEntries;
    MIB_TCPROW table[ANY_SIZE];
} MIB_TCPTABLE, *PMIB_TCPTABLE;

#define SIZEOF_TCPTABLE(X) (FIELD_OFFSET(MIB_TCPTABLE,table[0]) + \
                            ((X) * sizeof(MIB_TCPROW)) + ALIGN_SIZE)

typedef struct _MIB_TCPROW2 {
    MIB_TCP_STATE dwState;
    DWORD dwLocalAddr;
    DWORD dwLocalPort;
    DWORD dwRemoteAddr;
    DWORD dwRemotePort;
    DWORD dwOwningPid;
    TCP_CONNECTION_OFFLOAD_STATE dwOffloadState;
} MIB_TCPROW2, *PMIB_TCPROW2;

typedef struct _MIB_TCPTABLE2 {
    DWORD dwNumEntries;
    MIB_TCPROW2 table[ANY_SIZE];
} MIB_TCPTABLE2, *PMIB_TCPTABLE2;

#define SIZEOF_TCPTABLE2(X) (FIELD_OFFSET(MIB_TCPTABLE2,table[0]) + \
                            ((X) * sizeof(MIB_TCPROW2)) + ALIGN_SIZE)

#ifdef _WS2IPDEF_
//
// The following definitions require Winsock2.
//

typedef struct _MIB_TCP6ROW {
    MIB_TCP_STATE State;
    IN6_ADDR LocalAddr;
    DWORD dwLocalScopeId;
    DWORD dwLocalPort;
    IN6_ADDR RemoteAddr;
    DWORD dwRemoteScopeId;
    DWORD dwRemotePort;
} MIB_TCP6ROW, *PMIB_TCP6ROW;

typedef struct _MIB_TCP6TABLE {
    DWORD dwNumEntries;
    MIB_TCP6ROW table[ANY_SIZE];
} MIB_TCP6TABLE, *PMIB_TCP6TABLE;

#define SIZEOF_TCP6TABLE(X) (FIELD_OFFSET(MIB_TCP6TABLE,table[0]) + \
                             ((X) * sizeof(MIB_TCP6ROW)) + ALIGN_SIZE)

typedef struct _MIB_TCP6ROW2 {
    IN6_ADDR LocalAddr;
    DWORD dwLocalScopeId;
    DWORD dwLocalPort;
    IN6_ADDR RemoteAddr;
    DWORD dwRemoteScopeId;
    DWORD dwRemotePort;
    MIB_TCP_STATE State;
    DWORD dwOwningPid;
    TCP_CONNECTION_OFFLOAD_STATE dwOffloadState;
} MIB_TCP6ROW2, *PMIB_TCP6ROW2;

typedef struct _MIB_TCP6TABLE2 {
    DWORD dwNumEntries;
    MIB_TCP6ROW2 table[ANY_SIZE];
} MIB_TCP6TABLE2, *PMIB_TCP6TABLE2;

#define SIZEOF_TCP6TABLE2(X) (FIELD_OFFSET(MIB_TCP6TABLE2,table[0]) + \
                             ((X) * sizeof(MIB_TCP6ROW2)) + ALIGN_SIZE)

#endif // _WS2IPDEF_

#define MIB_TCP_MAXCONN_DYNAMIC ((ULONG)-1)

//
// The algorithm used to determine the timeout value used for retransmitting
// unacknowledged octets.
//
// REVIEW: This enum adds another version of the defines that already
// exist in iprtrmib.h (MIB_TCP_RTO_*).  Shouldn't we just use the
// public names that already exist?
//
typedef enum {
    TcpRtoAlgorithmOther,
    TcpRtoAlgorithmConstant,
    TcpRtoAlgorithmRsre,
    TcpRtoAlgorithmVanj,

    MIB_TCP_RTO_OTHER     = 1,
    MIB_TCP_RTO_CONSTANT  = 2,
    MIB_TCP_RTO_RSRE      = 3,
    MIB_TCP_RTO_VANJ      = 4,
} TCP_RTO_ALGORITHM, *PTCP_RTO_ALGORITHM;

typedef struct _MIB_TCPSTATS {
    union {
        DWORD dwRtoAlgorithm;
        TCP_RTO_ALGORITHM RtoAlgorithm;
    };
    DWORD dwRtoMin;
    DWORD dwRtoMax;
    DWORD dwMaxConn;
    DWORD dwActiveOpens;
    DWORD dwPassiveOpens;
    DWORD dwAttemptFails;
    DWORD dwEstabResets;
    DWORD dwCurrEstab;
    DWORD dwInSegs;
    DWORD dwOutSegs;
    DWORD dwRetransSegs;
    DWORD dwInErrs;
    DWORD dwOutRsts;
    DWORD dwNumConns;
} MIB_TCPSTATS, *PMIB_TCPSTATS;

#endif // _TCPMIB_
