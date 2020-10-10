/*++

Copyright (c) 1999  Microsoft Corporation

Module Name:
    mp_dbg.c

Abstract:
    This module contains all debug-related code.

Revision History:
    Who         When        What
    --------    --------    ----------------------------------------------
    DChen       11-01-99    created

Notes:

--*/

#include "precomp.h"

#if DBG

/**
Constants
**/

#define _FILENUMBER     'GBED'

// Bytes to appear on each line of dump output.
//
#define DUMP_BytesPerLine 16

ULONG               MPDebugLevel = MP_WARN;
ULONG               MPAllocCount = 0;       // the number of outstanding allocs
NDIS_SPIN_LOCK      MPMemoryLock;           // spinlock for the debug mem list
LIST_ENTRY          MPMemoryList;
BOOLEAN             MPInitDone = FALSE;     // debug mem list init flag 


PVOID 
MPAuditAllocMemTag(
    UINT        Size,
    ULONG       FileNumber,
    ULONG       LineNumber,
    NDIS_HANDLE MiniportAdapterHandle
    )
{
    PMP_ALLOCATION  pAllocInfo;
    PVOID           Pointer;

    if (!MPInitDone)
    {
        NdisAllocateSpinLock(&MPMemoryLock);
        InitializeListHead(&MPMemoryList);
        MPInitDone = TRUE;
    }

    (PVOID)pAllocInfo = NdisAllocateMemoryWithTagPriority(
                 MiniportAdapterHandle,
                 (UINT)(Size + sizeof(MP_ALLOCATION)), 
                 NIC_TAG,
                 LowPoolPriority);

    if (pAllocInfo == (PMP_ALLOCATION)NULL)
    {
        Pointer = NULL;

        DBGPRINT(MP_LOUD,
            ("MPAuditAllocMemCore: file %d, line %d, Size %d failed!\n",
            FileNumber, LineNumber, Size));
    }
    else
    {
        Pointer = (PVOID)&(pAllocInfo->UserData);
        MP_MEMSET(Pointer, Size, 0xc);

        pAllocInfo->Signature = 'DOOG';
        pAllocInfo->FileNumber = FileNumber;
        pAllocInfo->LineNumber = LineNumber;
        pAllocInfo->Size = Size;

        NdisAcquireSpinLock(&MPMemoryLock);
        InsertTailList(&MPMemoryList, &pAllocInfo->List);
        MPAllocCount++;
        NdisReleaseSpinLock(&MPMemoryLock);
    }

    DBGPRINT(MP_LOUD,
        ("MPAuditAllocMemTag: file %c%c%c%c, line %d, %d bytes, [0x"PTR_FORMAT"]\n",
        (CHAR)(FileNumber & 0xff),
        (CHAR)((FileNumber >> 8) & 0xff),
        (CHAR)((FileNumber >> 16) & 0xff),
        (CHAR)((FileNumber >> 24) & 0xff),
        LineNumber, Size, Pointer));

    return(Pointer);
}

VOID MPAuditFreeMem(
    IN PVOID  Pointer
    )
{
    PMP_ALLOCATION  pAllocInfo;

    pAllocInfo = CONTAINING_RECORD(Pointer, MP_ALLOCATION, UserData);

    ASSERT(pAllocInfo->Signature == (ULONG)'DOOG');

    NdisAcquireSpinLock(&MPMemoryLock);
    pAllocInfo->Signature = (ULONG)'DEAD';
    RemoveEntryList(&pAllocInfo->List);
    MPAllocCount--;
    NdisReleaseSpinLock(&MPMemoryLock);

    NdisFreeMemory(pAllocInfo, 0, 0);
}

VOID mpDbgPrintUnicodeString(
    IN  PUNICODE_STRING UnicodeString
    )
{
    UCHAR Buffer[256];

    USHORT i;

    for (i = 0; (i < UnicodeString->Length / 2) && (i < 255); i++) 
    {
        Buffer[i] = (UCHAR)UnicodeString->Buffer[i];
    }

    Buffer[i] = '\0';

    DbgPrint("%s", Buffer);
}



// Hex dump 'cb' bytes starting at 'p' grouping 'ulGroup' bytes together.
// For example, with 'ulGroup' of 1, 2, and 4:
//
// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 |................|
// 0000 0000 0000 0000 0000 0000 0000 0000 |................|
// 00000000 00000000 00000000 00000000 |................|
//
// If 'fAddress' is true, the memory address dumped is prepended to each
// line.
//
VOID
Dump(
    IN CHAR*   p,
    IN ULONG   cb,
    IN BOOLEAN fAddress,
    IN ULONG   ulGroup 
    )
{
    INT cbLine;

    while (cb)
    {

        cbLine = (cb < DUMP_BytesPerLine) ? cb : DUMP_BytesPerLine;
        DumpLine( p, cbLine, fAddress, ulGroup );
        cb -= cbLine;
        p += cbLine;
    }
}


VOID
DumpLine(
    IN CHAR*   p,
    IN ULONG   cb,
    IN BOOLEAN fAddress,
    IN ULONG   ulGroup 
    )
{

    CHAR* pszDigits = "0123456789ABCDEF";
    CHAR szHex[ ((2 + 1) * DUMP_BytesPerLine) + 1 ];
    CHAR* pszHex = szHex;
    CHAR szAscii[ DUMP_BytesPerLine + 1 ];
    CHAR* pszAscii = szAscii;
    ULONG ulGrouped = 0;

    if (fAddress) 
    {
        DbgPrint( "E100: %p: ", p );
    }
    else 
    {
        DbgPrint( "E100: " );
    }

    while (cb)
    {
        *pszHex++ = pszDigits[ ((UCHAR )*p) / 16 ];
        *pszHex++ = pszDigits[ ((UCHAR )*p) % 16 ];

        if (++ulGrouped >= ulGroup)
        {
            *pszHex++ = ' ';
            ulGrouped = 0;
        }

        *pszAscii++ = (*p >= 32 && *p < 128) ? *p : '.';

        ++p;
        --cb;
    }

    *pszHex = '\0';
    *pszAscii = '\0';

    DbgPrint(
        "%-*s|%-*s|\n",
        (2 * DUMP_BytesPerLine) + (DUMP_BytesPerLine / ulGroup), szHex,
        DUMP_BytesPerLine, szAscii );
}



#endif // DBG

