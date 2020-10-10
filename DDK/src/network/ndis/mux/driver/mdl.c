/*++

Copyright (c) 1992-2000  Microsoft Corporation
 
Module Name:
 
    mdl.c

Abstract:

    MDL allocation functions which are used in advancing and
    retreating a net buffer list.

Environment:

    Kernel mode

Revision History:


--*/

#include "precomp.h"
#pragma hdrstop

#define MODULE_NUMBER           MODULE_MDL

#define MAX_MDLS        256
#define MDL_BUF_SIZE    4

PUCHAR          MdlBuffer;
NDIS_SPIN_LOCK  MdlLock;
ULONG           MdlHead;
PMDL            MdlList[MAX_MDLS];

NDIS_STATUS MuxInitializeMdlBuffer()
{
    NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
    ULONG           Count, Count2;

    NDIS_PHYSICAL_ADDRESS noMaxAddr = NDIS_PHYSICAL_ADDRESS_CONST(-1,-1);

    do
    {

        DBGPRINT(MUX_LOUD, ("==> MuxInitializeMdlBuffer\n"));

        NdisAllocateSpinLock(&MdlLock);
        MdlHead = 0;

        Status = NdisAllocateMemory(&MdlBuffer,
                                    MAX_MDLS * MDL_BUF_SIZE,
                                    0,
                                    noMaxAddr);

        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(MUX_LOUD, ("   NdisAllocateMemory failed\n"));
            break;
        }

        for(Count = 0; Count < MAX_MDLS; Count++)
        {
            MdlList[Count] = IoAllocateMdl((PVOID)&(MdlBuffer[Count * MDL_BUF_SIZE]),
                                           MDL_BUF_SIZE,
                                           FALSE,
                                           FALSE,
                                           NULL);

            if (MdlList[Count] == NULL)
                break;

            MmBuildMdlForNonPagedPool(MdlList[Count]);
        }

        if (Count != MAX_MDLS)
        {
            for(Count2 = 0;Count2 < Count;Count2++)
            {
                IoFreeMdl(MdlList[Count2]);
            }
            Status = NDIS_STATUS_RESOURCES;
            break;
        }

    } while(FALSE);

    DBGPRINT(MUX_LOUD, ("<== MuxInitializeMdlBuffer returned with status %08lx\n", Status));

    return Status;

}

VOID MuxDeInitializeMdlBuffer()
{
    ULONG   Count;

    DBGPRINT(MUX_LOUD, ("==> MuxDeInitializeMdlBuffer\n"));

#ifdef DBG
    if (MdlHead != 0)
    {
        ASSERT(0);
    }
#endif

    for(Count = 0;Count < MAX_MDLS;Count++)
    {
        IoFreeMdl(MdlList[Count]);
    }

    DBGPRINT(MUX_LOUD, ("<== MuxDeInitializeMdlBuffer\n"));
}


PMDL MuxAllocateMdl(
    IN OUT PULONG           BufferSize
    )
{
    PMDL Mdl;

    UNREFERENCED_PARAMETER(BufferSize);

    NdisAcquireSpinLock(&MdlLock);

    if (MdlHead != MAX_MDLS)
    {
        Mdl = MdlList[MdlHead];
        MdlHead++;
    }

    NdisReleaseSpinLock(&MdlLock);

    return Mdl;
}

VOID MuxFreeMdl(
    IN PMDL                 Mdl
    )
{
    NdisAcquireSpinLock(&MdlLock);

    ASSERT(MdlHead != 0);

    MdlHead--;
    MdlList[MdlHead] = Mdl;

    NdisReleaseSpinLock(&MdlLock);

}

