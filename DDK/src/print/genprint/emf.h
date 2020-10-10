/*++

Copyright (c) 1990-2003  Microsoft Corporation
All rights reserved

FileName:

    emf.h

Abstract:

    Header for emf.c

--*/

#ifndef _EMF_H
#define _EMF_H

typedef enum _EBookletMode {
    kNoBooklet        = 0,
    kBookletLeftEdge  = 1,
    kBookletRightEdge = 2
} EBookletMode, *PEBookletMode;

//
// Four n-up directions supported. The numbers given with each option are not to be changed
//
typedef enum _ENupDirection {
    kRightThenDown = 0,
    kDownThenRight = 1,
    kLeftThenDown  = 2,
    kDownThenLeft  = 3
}ENupDirection, *PENupDirection;


#define EMF_ATTRIBUTE_INFO_SIGNATURE '1fme' //in debugger, displayed as emf1

//
// Flags for dwFlags attribute in PAGE_NUMBER
// Note:
//
#define NEW_PHYSICAL_SIDE               (0x1)
#define PRINT_BLANK_BEFORE_THISPAGE     (0x1 << 1)
#define PRINT_BLANK_AFTER_THISPAGE      (0x1 << 2)


//   PAGE_NUMBER is used to save a list of the page numbers to start new sides while
//   Reverse Printing.

typedef struct _PAGE_NUMBER {
    struct _PAGE_NUMBER *pNextSide;     //first page on the next side.
    struct _PAGE_NUMBER *pNextLogPage;  //next logical page on the same side.
    DWORD               dwPageNumber;
    DWORD               dwFlags;
} PAGE_NUMBER, *PPAGE_NUMBER;

typedef struct _UpdateRect {
        double  top;
        double  bottom;
        double  left;
        double  right;
}  UpdateRect, *PUpdateRect;

typedef struct _EMF_ATTRIBUTE_INFO
    {
        DWORD         dwSignature;                    //EMF_ATTRIBUTE_INFO_SIGNATURE

        LONG          lXResolution;                   //dpi in x-direction
        LONG          lYResolution;                   //dpi in y-direction
        LONG          lXPrintArea;                    //length of printable area (x direction) (in number of pixels).
        LONG          lYPrintArea;                    //length of printable area (y direction) (in number of pixels).
    
        DWORD         dwTotalNumberOfPages;           //Number of Pages in the job. Not always valid.
                                                    //To get this value, we need to wait for the    
                                                    //job to finish spooling first. So this is
                                                    //valid only for certain cases like reverse
                                                    //printing.
        DWORD         dwNumberOfPagesPerSide;       //n-up
        DWORD         dwDrvNumberOfPagesPerSide;    //For printers that handle n-up themselves.
        DWORD         dwNupBorderFlags;             //What kind of borders to draw
        DWORD         dwJobNumberOfCopies;          //Num of copies (simulated by print proc)
        DWORD         dwDrvNumberOfCopies;          //Num of copies (simulated by driver)
        DWORD         dwDuplexMode;
        ENupDirection eNupDirection;                //Direction:Left then down, right then down.
                                                    //down then right, down then left.
        EBookletMode  eBookletMode;                //Left edge binding(=0) or right edge(=1) 
        DWORD         dwMultiPartJob;               //Whether job has to broken into multiple jobs
        BOOL          bReverseOrderPrinting;        //To print last page first (mostly)
        BOOL          bBookletPrint;
        BOOL          bCollate;                     //In case of multiple copies, should we play
                                                    //n-copies of page1, ncopies of page 2 
                                                    // (bCollate = 0) OR
                                                    //print full job at a time (bCollate = 1)
    } EMF_ATTRIBUTE_INFO, *PEMF_ATTRIBUTE_INFO;

BOOL BOrderPagesForDuplexReverse(
            IN OUT  PPAGE_NUMBER            *ppHead,
            IN      PEMF_ATTRIBUTE_INFO     pEMFAttr,
            IN      ULONG                   ulNumNodes,
            IN      BOOL                    bOdd);

BOOL BRetrievePvtSettings (
            IN  LPCTSTR        lpPrinterName,
            OUT PENupDirection peNupDirection,
            OUT PEBookletMode  peBookletMode,
            OUT PDWORD         pdwMultiPartJob,
            IN  BOOL           bBookletPrint);

BOOL
PlaySpecificEMF(
    HANDLE       hSpoolHandle,
    HDC          hPrinterDC,
    RECT        *lpRect);

VOID VThrowSheetTurnUI(VOID);

BOOL BPlayEmptySides(
        IN  HANDLE                 hSpoolHandle,
        IN  HDC                    hPrinterDC,
        IN  PEMF_ATTRIBUTE_INFO    pEMFAttr,
        IN  DWORD                  dwNumCopies,
        IN  DWORD                  dwOptimization,
        IN  LPDEVMODEW             pDevmode);

BOOL BPlayEmptyPages(
        IN  HANDLE                 hSpoolHandle,
        IN  PEMF_ATTRIBUTE_INFO    pEMFAttr,
        IN  DWORD                  dwNumPages,
        IN  DWORD                  dwOptimization);

BOOL
BGetPageCoordinatesForNUpFromArray(
                IN  PEMF_ATTRIBUTE_INFO   pEMFAttr,
                IN  PUpdateRect *         ppURect,
                IN  BOOL                  bLandscape);


BOOL
PrintOneSideReverseEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODE             pDevmode);

BOOL
PrintOneSideReverseForDriverEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODE             pDevmode);

BOOL
PrintOneSideBookletEMF(
    HANDLE                hSpoolHandle,
    HDC                   hPrinterDC,
    PEMF_ATTRIBUTE_INFO   pEMFAttr,
    PPAGE_NUMBER          pHead,
    BOOL                  bDuplex,
    DWORD                 dwOptimization,
    LPDEVMODE             pDevmode);


BOOL
BPrintOnePagePosterEMF(
            IN  HANDLE                hSpoolHandle,
            IN  HDC                   hPrinterDC,
            IN  PEMF_ATTRIBUTE_INFO   pEMFAttr,
            IN  DWORD                 dwPageNumber,
            IN  DWORD                 dwOptimization,
            IN  FLOAT                 fOverlapX,
            IN  FLOAT                 fOverlapY,
            IN  FLOAT                 fExpFactorX,
            IN  FLOAT                 fExpFactorY,
            IN  PRECT                 pRectDocument,
            IN  LPDEVMODE             pDevmode);

BOOL
BCalcExpFactor(
        OUT PFLOAT pfExpFactor,
        IN  DWORD  dwNumSheets,
        IN  LONG   lNumPixels,
        IN  LONG   lResolution,
        IN  FLOAT  fOverlapLength) ;

BOOL
BPrintEMFJobNow (
        IN     HANDLE                hSpoolHandle,
        IN     HDC                   hPrinterDC,
        IN     PEMF_ATTRIBUTE_INFO   pEMFAttr,
        IN     BOOL                  bOdd,
        IN     DWORD                 dwOptimization,
        IN     LPDEVMODEW            pDevmode,
        IN OUT PPAGE_NUMBER          pPageList,
        IN     PPRINTPROCESSORDATA   pData );

BOOL
BUpdateAttributes(
        IN     HDC                   hPrinterDC,
        IN OUT PEMF_ATTRIBUTE_INFO   pEMFAttr);

#endif


