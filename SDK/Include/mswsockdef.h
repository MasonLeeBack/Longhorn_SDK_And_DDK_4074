/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    mswsock.h

Abstract:

    This module contains the Microsoft-specific extensions to the Windows
    Sockets API.

Revision History:

--*/

#ifndef _MSWSOCKDEF_
#define _MSWSOCKDEF_

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef _MSC_VER
#define MSWSOCKDEF_INLINE __inline
#else
#define MSWSOCKDEF_INLINE extern inline /* GNU style */
#endif

#ifndef ASSERT
#define MSWSOCKDEF_ASSERT_UNDEFINED
#define ASSERT(exp) ((VOID) 0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _WSAMSG {
    LPSOCKADDR       name;              /* Remote address */
    INT              namelen;           /* Remote address length */
    LPWSABUF         lpBuffers;         /* Data buffer array */
    ULONG            dwBufferCount;     /* Number of elements in the array */
    WSABUF           Control;           /* Control buffer */
    ULONG            dwFlags;           /* Flags */
} WSAMSG, *PWSAMSG, * FAR LPWSAMSG;

/*
 * Layout of ancillary data objects in the control buffer (RFC 2292).
 */
#define _WSACMSGHDR cmsghdr

typedef struct _WSACMSGHDR {
    SIZE_T      cmsg_len;
    INT         cmsg_level;
    INT         cmsg_type;
    /* followed by UCHAR cmsg_data[] */
} WSACMSGHDR, *PWSACMSGHDR, FAR *LPWSACMSGHDR;

typedef WSACMSGHDR CMSGHDR, *PCMSGHDR;


/*
 * Alignment macros for header and data members of
 * the control buffer.
 */
#define WSA_CMSGHDR_ALIGN(length)                           \
            ( ((length) + TYPE_ALIGNMENT(WSACMSGHDR)-1) &   \
                (~(TYPE_ALIGNMENT(WSACMSGHDR)-1)) )         \

#define WSA_CMSGDATA_ALIGN(length)                          \
            ( ((length) + MAX_NATURAL_ALIGNMENT-1) &        \
                (~(MAX_NATURAL_ALIGNMENT-1)) )

#define CMSGHDR_ALIGN WSA_CMSGHDR_ALIGN
#define CMSGDATA_ALIGN WSA_CMSGDATA_ALIGN

/*
 *  WSA_CMSG_FIRSTHDR
 *
 *  Returns a pointer to the first ancillary data object, 
 *  or a null pointer if there is no ancillary data in the 
 *  control buffer of the WSAMSG structure.
 *
 *  LPCMSGHDR 
 *  WSA_CMSG_FIRSTHDR (
 *      LPWSAMSG    msg
 *      );
 */
#define WSA_CMSG_FIRSTHDR(msg) \
    ( ((msg)->Control.len >= sizeof(WSACMSGHDR))            \
        ? (LPWSACMSGHDR)(msg)->Control.buf                  \
        : (LPWSACMSGHDR)NULL )

#define CMSG_FIRSTHDR WSA_CMSG_FIRSTHDR

/* 
 *  WSA_CMSG_NXTHDR
 *
 *  Returns a pointer to the next ancillary data object,
 *  or a null if there are no more data objects.
 *
 *  LPCMSGHDR 
 *  WSA_CMSG_NEXTHDR (
 *      LPWSAMSG        msg,
 *      LPWSACMSGHDR    cmsg
 *      );
 */
#define WSA_CMSG_NXTHDR(msg, cmsg)                          \
    ( ((cmsg) == NULL)                                      \
        ? WSA_CMSG_FIRSTHDR(msg)                            \
        : ( ( ((PUCHAR)(cmsg) +                             \
                    WSA_CMSGHDR_ALIGN((cmsg)->cmsg_len) +   \
                    sizeof(WSACMSGHDR) ) >                  \
                (PUCHAR)((msg)->Control.buf) +              \
                    (msg)->Control.len )                    \
            ? (LPWSACMSGHDR)NULL                            \
            : (LPWSACMSGHDR)((PUCHAR)(cmsg) +               \
                WSA_CMSGHDR_ALIGN((cmsg)->cmsg_len)) ) )

#define CMSG_NXTHDR WSA_CMSG_NXTHDR

/* 
 *  WSA_CMSG_DATA
 *
 *  Returns a pointer to the first byte of data (what is referred 
 *  to as the cmsg_data member though it is not defined in 
 *  the structure).
 *
 *  Note that RFC 2292 defines this as CMSG_DATA, but that name
 *  is already used by wincrypt.h, and so Windows has used WSA_CMSG_DATA.
 *
 *  PUCHAR
 *  WSA_CMSG_DATA (
 *      LPWSACMSGHDR   pcmsg
 *      );
 */
#define WSA_CMSG_DATA(cmsg)             \
            ( (PUCHAR)(cmsg) + WSA_CMSGDATA_ALIGN(sizeof(WSACMSGHDR)) )

/*
 *  WSA_CMSG_SPACE
 *
 *  Returns total size of an ancillary data object given 
 *  the amount of data. Used to allocate the correct amount 
 *  of space.
 *
 *  SIZE_T
 *  WSA_CMSG_SPACE (
 *      SIZE_T length
 *      );
 */
#define WSA_CMSG_SPACE(length)  \
        (WSA_CMSGDATA_ALIGN(sizeof(WSACMSGHDR) + WSA_CMSGHDR_ALIGN(length)))

#define CMSG_SPACE WSA_CMSG_SPACE

/*
 *  WSA_CMSG_LEN
 *
 *  Returns the value to store in cmsg_len given the amount of data.
 *
 *  SIZE_T
 *  WSA_CMSG_LEN (
 *      SIZE_T length
 *  );
 */
#define WSA_CMSG_LEN(length)    \
         (WSA_CMSGDATA_ALIGN(sizeof(WSACMSGHDR)) + length)

#define CMSG_LEN WSA_CMSG_LEN


/*
 * Definition for flags member of the WSAMSG structure
 * This is in addition to other MSG_xxx flags defined
 * for recv/recvfrom/send/sendto.
 */
#define MSG_TRUNC       0x0100
#define MSG_CTRUNC      0x0200
#define MSG_BCAST       0x0400
#define MSG_MCAST       0x0800

#ifdef _WS2DEF_

extern CONST UCHAR sockaddr_size[AF_MAX];

MSWSOCKDEF_INLINE
UCHAR
SOCKADDR_SIZE(ADDRESS_FAMILY af)
{
    ASSERT(af < AF_MAX);
    return sockaddr_size[af];
}

MSWSOCKDEF_INLINE
SCOPE_LEVEL
ScopeLevel(
    IN SCOPE_ID ScopeId
    )
{
    //
    // We can't declare the Level field of type SCOPE_LEVEL directly,
    // since it gets sign extended to be negative.  We can, however,
    // safely cast.
    //
    return (SCOPE_LEVEL)ScopeId.Level;
}

#endif // _WS2DEF_

#ifdef __cplusplus
}
#endif

#ifdef MSWSOCKDEF_ASSERT_UNDEFINED
#undef ASSERT
#endif

#endif  /* _MSWSOCKDEF_ */
