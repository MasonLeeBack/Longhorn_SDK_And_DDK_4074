/*++

Copyright (2) 2003 Microsoft Corporation

Module Name:

    kxagplib.c

Abstract:

    This module contains routines to access the AMD K8/9 AGP registers

Author:

    Eric F. Nelson (enelson) January 13, 2003

Revision History:

--*/

#include "agp.h"
#include "kxagplib.h"

//
// Aperture Control Register
//
typedef union {
    struct {
        ULONG ApEnable:      1;
        ULONG ApSize:        3;
        ULONG CPU_ApDisable: 1;
        ULONG IO_ApDisable:  1;
        ULONG Reserved:     26;
    };
    ULONG AsULONG;
} KX_AP_CONTROL, *PKX_AP_CONTROL;

//
// Aperture Base Address Register
//
typedef union {
    struct {
        ULONG ApBase: 15;
        ULONG Reserved: 17;
    };
    ULONG AsULONG;
} KX_AP_BASE, *PKX_AP_BASE;

#define KX_AP_CONTROL_OFFSET 0x90
#define KX_AP_BASE_OFFSET 0x94
#define KX_GART_BASE_OFFSET 0x98
#define KX_GART_INV_OFFSET 0x9C

#define KX_APERTURE_FUNCTION 3
#define K8_APERTURE_DEVICE 0x11031022
#define MAX_KX_AGP_DEVICE 4

typedef struct _KX_AGP_CTX {
    ULONG KxCount;
    PCI_SLOT_NUMBER KxSlot[MAX_KX_AGP_DEVICE];
} KX_AGP_CTX;

static KX_AGP_CTX KxAgpCtx = { /* KxCount = */ 0, };

#define MIN(A, B) (((A) < (B)) ? (A): (B))

NTSTATUS
KxInitializeLib(
    VOID
    )
/*++

Routine Description:

    Find all the KX CPU AGP devices, and initialize our context structure

Arguments:

    None

Return Value:

    NTSTATUS

--*/
{
    ULONG Index;
    ULONG Length;
    ULONG DeviceID;
    ULONG SearchDepth;
    PCI_SLOT_NUMBER TestSlot;

    TestSlot.u.AsULONG = 0;
    TestSlot.u.bits.FunctionNumber = KX_APERTURE_FUNCTION;

    //
    // Search for K8/9 CPU(s) on the primary bus
    //
    KxAgpCtx.KxCount = 0;
    SearchDepth = MIN(MAX_KX_AGP_DEVICE, KeNumberProcessors);
    for (Index = 0;
         ((KxAgpCtx.KxCount < SearchDepth) &&
          (Index < PCI_MAX_DEVICES));
         Index++) {

        TestSlot.u.bits.DeviceNumber = Index;

        Length = HalGetBusDataByOffset(PCIConfiguration,
                                       0, // bus
                                       TestSlot.u.AsULONG,
                                       &DeviceID,
                                       0,
                                       sizeof(DeviceID));

        if ((Length == sizeof(DeviceID)) &&
            ((DeviceID & K8_APERTURE_DEVICE) == K8_APERTURE_DEVICE)) {

            //
            // Store this K8 info in our context
            //
            KxAgpCtx.KxSlot[KxAgpCtx.KxCount] = TestSlot;
            KxAgpCtx.KxCount++;
        }
    }

    if (KxAgpCtx.KxCount > 0) {
        return STATUS_SUCCESS;
    }

    return STATUS_NOT_FOUND;
}

#define KX_AP_BASE_MASK 0x7FFF
#define KX_AP_BASE_SHIFT 25

NTSTATUS
KxSetApertureBase(
    PHYSICAL_ADDRESS PhysAddr
    )
/*++

Routine Description:

    Program the Aperture Base address for all KX CPU

Arguments:

    PhysAddr - Physical address of Aperture Base

Return Value:

    NTSTATUS

--*/
{
    ULONG Index;
    KX_AP_BASE ApBase;
    ULONG Length;
 
    ApBase.AsULONG = 0;

    ApBase.ApBase =
        (ULONG)(PhysAddr.QuadPart >> KX_AP_BASE_SHIFT) & KX_AP_BASE_MASK;
 
    for (Index = 0; Index < KxAgpCtx.KxCount; Index++) {
        Length = HalSetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &ApBase,
                                       KX_AP_BASE_OFFSET,
                                       sizeof(ApBase));
        
        if (Length != sizeof(ApBase)) {
            return STATUS_IO_DEVICE_ERROR;
        }

        //
        // Read back what we wrote, and see if it took
        //
#if DBG
        {
            ULONG Test;

            HalGetBusDataByOffset(PCIConfiguration,
                                  0,
                                  KxAgpCtx.KxSlot[Index].u.AsULONG,
                                  &Test,
                                  KX_AP_BASE_OFFSET,
                                  sizeof(Test));

            AGP_ASSERT(Test == ApBase.AsULONG);
        }
#endif

    }

    return STATUS_SUCCESS;
}

#define KX_GART_BASE_SHIFT 8

NTSTATUS
KxSetGartBase(
    PHYSICAL_ADDRESS PhysAddr
    )
/*++

Routine Description:

    Program the Gart Table Base Address for all KX CPU

Arguments:

    PhysAddr - Phsyical address of Gart Table Base 

Return Value:

    NTSTATUS

--*/
{
    ULONG Length;
    ULONG Index;
    ULONG GartBase;

    GartBase = (ULONG)(PhysAddr.QuadPart >> KX_GART_BASE_SHIFT) &
        PCI_ADDRESS_MEMORY_ADDRESS_MASK;

    for (Index = 0; Index < KxAgpCtx.KxCount; Index++) {
        Length = HalSetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &GartBase,
                                       KX_GART_BASE_OFFSET,
                                       sizeof(GartBase));
        
        if (Length != sizeof(GartBase)) {
            return STATUS_IO_DEVICE_ERROR;
        }

        //
        // Read back what we wrote, and see if it took
        //
#if DBG
        {
            ULONG Test;

            HalGetBusDataByOffset(PCIConfiguration,
                                  0,
                                  KxAgpCtx.KxSlot[Index].u.AsULONG,
                                  &Test,
                                  KX_GART_BASE_OFFSET,
                                  sizeof(Test));

            AGP_ASSERT(Test == GartBase);
        }
#endif
    }

    return STATUS_SUCCESS;
}

typedef enum KX_AP_SIZE {
    KX_AP_32M  =  0x2000000,
    KX_AP_64M  =  0x4000000,
    KX_AP_128M =  0x8000000,
    KX_AP_256M = 0x10000000,
    KX_AP_512M = 0x20000000,
    KX_AP_1G   = 0x40000000,
    KX_AP_2G   = 0x80000000
};

NTSTATUS
KxSetApertureSize(
    ULONG Size
    )
/*++

Routine Description:

    Programs the Aperture Size for all KX CPU

Arguments:

    Size - Aperture Size in bytes

Return Value:

    NTSTATUS

--*/
{
    ULONG Length;
    KX_AP_CONTROL ApControl;
    ULONG Index;
    ULONG ApSize;
    
    //
    // There are 7 supported sizes as follows--
    //
    switch (Size) {
        case KX_AP_32M:
            ApSize = 0;
            break;
        case KX_AP_64M:
            ApSize = 1;
            break;
        case KX_AP_128M:
            ApSize = 2;
            break;
        case KX_AP_256M:
            ApSize = 3;
            break;
        case KX_AP_512M:
            ApSize = 4;
            break;
        case KX_AP_1G:
            ApSize = 5;
            break;
        case KX_AP_2G:
            ApSize = 6;
            break;
        default:
            return STATUS_INVALID_PARAMETER;
    }


    for (Index = 0; Index < KxAgpCtx.KxCount; Index++) {
        
        //
        // We must do a read-modify-write to preserve the aperture
        // access enables
        //
        Length = HalGetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &ApControl,
                                       KX_AP_CONTROL_OFFSET,
                                       sizeof(ApControl));
        
        if (Length != sizeof(ApControl)) {
            return STATUS_IO_DEVICE_ERROR;
        }

        ApControl.ApSize = ApSize;

        Length = HalSetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &ApControl,
                                       KX_AP_CONTROL_OFFSET,
                                       sizeof(ApControl));
        
        if (Length != sizeof(ApControl)) {
            return STATUS_IO_DEVICE_ERROR;
        }

        //
        // Read back what we wrote, and see if it took
        //
#if DBG
        {
            ULONG Test;

            HalGetBusDataByOffset(PCIConfiguration,
                                  0,
                                  KxAgpCtx.KxSlot[Index].u.AsULONG,
                                  &Test,
                                  KX_AP_CONTROL_OFFSET,
                                  sizeof(Test));

            AGP_ASSERT(Test == ApControl.AsULONG);
        }
#endif
    }

    return STATUS_SUCCESS;
}

NTSTATUS
KxGetApertureSize(
    PULONG Size
    )
/*++

Routine Description:

    Returns the current Aperture Size

Arguments:

    Size - Aperture Size in bytes

Return Value:

    NTSTATUS

--*/
{
    ULONG Length;
    KX_AP_CONTROL ApControl;
    ULONG Index;
    KX_AP_CONTROL ApVerify;

    //
    // Read Aperture Size from 1st K8/9 AGP device
    //
    Index = 0;
    Length = HalGetBusDataByOffset(PCIConfiguration,
                                   0,
                                   KxAgpCtx.KxSlot[Index].u.AsULONG,
                                   &ApControl,
                                   KX_AP_CONTROL_OFFSET,
                                   sizeof(ApControl));
    
    if (Length != sizeof(ApControl)) {
        return STATUS_IO_DEVICE_ERROR;
    }

#if DBG
    //
    // Check that all other K8/9 CPU AGP Aperture sizes match! 
    //
    for (Index = 1; Index < KxAgpCtx.KxCount; Index++) {
        
        Length = HalGetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &ApVerify,
                                       KX_AP_CONTROL_OFFSET,
                                       sizeof(ApVerify));
        
        if (Length == sizeof(ApVerify)) {
            AGP_ASSERT(ApControl.ApSize == ApVerify.ApSize);
        }
    }
#endif

    //
    // There are 7 supported sizes as follows--
    //
    switch (ApControl.ApSize) {
        case 0:
            *Size = KX_AP_32M;
            break;
        case 1:
            *Size = KX_AP_64M;
            break;
        case 2:
            *Size = KX_AP_128M;
            break;
        case 3:
            *Size = KX_AP_256M;
            break;
        case 4:
            *Size = KX_AP_512M;
            break;
        case 5:
            *Size = KX_AP_1G;
            break;
        case 6:
            *Size = KX_AP_2G;
            break;
        default:
            return STATUS_INVALID_PARAMETER;
    }

    return STATUS_SUCCESS;
}

#define ON  1
#define OFF 0

NTSTATUS
KxSetApertureEnable(
    BOOLEAN ApEnable,
    BOOLEAN CPU_Enable,
    BOOLEAN IO_Enable
    )
/*++

Routine Description:

    Program the Aperture Enable(s) for all KX CPU

Arguments:

    ApEnable - Aperture enabled

    CPU_Enable - CPU Aperture Access Enable

    IO_Enable - Device Aperture Access Enable

Return Value:

    NTSTATUS

--*/
{
    ULONG Length;
    KX_AP_CONTROL ApControl;
    ULONG Index;

    for (Index = 0; Index < KxAgpCtx.KxCount; Index++) {
        
        //
        // We must do a read-modify-write to preserve the aperture
        // size
        //
        Length = HalGetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &ApControl,
                                       KX_AP_CONTROL_OFFSET,
                                       sizeof(ApControl));
        
        if (Length != sizeof(ApControl)) {
            return STATUS_IO_DEVICE_ERROR;
        }
        
        ApControl.ApEnable      = (ApEnable)   ? ON: OFF;
        ApControl.CPU_ApDisable = (CPU_Enable) ? OFF: ON;
        ApControl.IO_ApDisable  = (IO_Enable)  ? OFF: ON;

        Length = HalSetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &ApControl,
                                       KX_AP_CONTROL_OFFSET,
                                       sizeof(ApControl));
        
        if (Length != sizeof(ApControl)) {
            return STATUS_IO_DEVICE_ERROR;
        }

        //
        // Read back what we wrote, and see if it took
        //
#if DBG
        {
            ULONG Test;

            HalGetBusDataByOffset(PCIConfiguration,
                                  0,
                                  KxAgpCtx.KxSlot[Index].u.AsULONG,
                                  &Test,
                                  KX_AP_CONTROL_OFFSET,
                                  sizeof(Test));

            AGP_ASSERT(Test == ApControl.AsULONG);
        }
#endif
    }

    return STATUS_SUCCESS;
}

#define KX_GART_PTE_ERROR 2
#define KX_INV_GART_TLB 1

NTSTATUS
KxInvalidateGart(
    VOID
    )
/*++

Routine Description:

    Invalidate Gart Table for all KX CPU

Arguments:

    None

Return Value:

    NTSTATUS

--*/
{
    ULONG Length;
    ULONG Index;
    ULONG Inv;
    ULONG PTE_Err;

    Inv = KX_INV_GART_TLB;

    for (Index = 0; Index < KxAgpCtx.KxCount; Index++) {

        //
        // Check whether the Gart PTE error bit is set
        //
#if DBG
        PTE_Err = 0;
        Length = HalGetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &PTE_Err,
                                       KX_GART_INV_OFFSET,
                                       sizeof(PTE_Err));
        
        if (Length != sizeof(PTE_Err)) {
            return STATUS_IO_DEVICE_ERROR;
        }
        
        if ((PTE_Err & KX_GART_PTE_ERROR) == KX_GART_PTE_ERROR) {
            
            AGPLOG(AGP_CRITICAL, ("KxInvateGart: PTE Error bit set!\n"));
            
            //
            // Clear the error bit
            //
            PTE_Err = KX_GART_PTE_ERROR;            
            Length = HalSetBusDataByOffset(PCIConfiguration,
                                           0,
                                           KxAgpCtx.KxSlot[Index].u.AsULONG,
                                           &PTE_Err,
                                           KX_GART_INV_OFFSET,
                                           sizeof(PTE_Err));
            
            if (Length != sizeof(PTE_Err)) {
                AGPLOG(AGP_CRITICAL,
                       ("KxInvateGart: Couldn't clear PTE Error bit!\n"));
            }
        }
#endif

        //
        // Invalidate Gart TLB
        //
        Length = HalSetBusDataByOffset(PCIConfiguration,
                                       0,
                                       KxAgpCtx.KxSlot[Index].u.AsULONG,
                                       &Inv,
                                       KX_GART_INV_OFFSET,
                                       sizeof(Inv));
        
        if (Length != sizeof(Inv)) {
            return STATUS_IO_DEVICE_ERROR;
        }
    }
    
    return STATUS_SUCCESS;   
}

