//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1998 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:    Devmode.cpp
//    
//
//  PURPOSE:  Implementation of Devmode functions shared with OEM UI and OEM rendering modules.
//
//


#include "precomp.h"
#include "oemui.h"
#include "debug.h"
#include "devmode.h"

// StrSafe.h needs to be included last
// to disallow bad string functions.
#include <STRSAFE.H>


//
//Performs operation on UI Plugins Private DevMode Members.
//Called via IOemUI::DevMode
//

HRESULT hrOEMDevMode(DWORD dwMode, POEMDMPARAM pOemDMParam)
{
    POEMDEV pOEMDevIn;
    POEMDEV pOEMDevOut;


    // Verify parameters.
    if( (NULL == pOemDMParam)
        ||
        ( (OEMDM_SIZE != dwMode)
          &&
          (OEMDM_DEFAULT != dwMode)
          &&
          (OEMDM_CONVERT != dwMode)
          &&
          (OEMDM_MERGE != dwMode)
        )
      )
    {
        ERR(ERRORTEXT("DevMode() ERROR_INVALID_PARAMETER.\r\n"));
        VERBOSE(DLLTEXT("\tdwMode = %d, pOemDMParam = %#lx.\r\n"), dwMode, pOemDMParam);

        SetLastError(ERROR_INVALID_PARAMETER);
        return E_FAIL;
    }

    // Cast generic (i.e. PVOID) to OEM private devomode pointer type.
    pOEMDevIn = (POEMDEV) pOemDMParam->pOEMDMIn;
    pOEMDevOut = (POEMDEV) pOemDMParam->pOEMDMOut;

    switch(dwMode)
    {
		//
		//The Method should return the size of the memory allocation needed to store the UI plugin Private DEVMODE.
		//
        case OEMDM_SIZE:
            pOemDMParam->cbBufSize = sizeof(OEMDEV);
            break;

		//
		//Should fill the Private DEVMODE with the default values.
		//
        case OEMDM_DEFAULT:
			//
			//OEM_DMEXTRAHEADER Members
			//
            pOEMDevOut->dmOEMExtra.dwSize       = sizeof(OEMDEV);
            pOEMDevOut->dmOEMExtra.dwSignature  = OEM_SIGNATURE;
            pOEMDevOut->dmOEMExtra.dwVersion    = OEM_VERSION;

			//
			//Private members
			//
            pOEMDevOut->dwDriverDataUi            = 0;
            pOEMDevOut->dwAdvancedData          = 0;
			

            VERBOSE(DLLTEXT("pOEMDevOut after setting default values:\r\n"));
            Dump(pOEMDevOut);			
            break;
			
		//
		//The method should convert private DEVMODE members to the current version, if necessary.
		//
        case OEMDM_CONVERT:
            bConvertOEMDevmode(pOEMDevIn, pOEMDevOut);
            break;
		
		//
		//The method should validate the information contained in private DEVMODE members and merge validated values into a private DEVMODE structure containing default values
		//
        case OEMDM_MERGE:
            bConvertOEMDevmode(pOEMDevIn, pOEMDevOut);
            bMakeOEMDevmodeValid(pOEMDevOut);
            break;
    }
    Dump(pOemDMParam);

    return S_OK;
}


BOOL bConvertOEMDevmode(PCOEMDEV pOEMDevIn, POEMDEV pOEMDevOut)
{
    if( (NULL == pOEMDevIn)
        ||
        (NULL == pOEMDevOut)
      )
    {
        ERR(ERRORTEXT("bConvertOEMDevmode() invalid parameters.\r\n"));
        return FALSE;
    }

    // Check OEM Signature, if it doesn't match ours,
    // then just assume DMIn is bad and use defaults.
    if(pOEMDevIn->dmOEMExtra.dwSignature == pOEMDevOut->dmOEMExtra.dwSignature)
    {
        VERBOSE(DLLTEXT("Converting private OEM Devmode.\r\n"));
        VERBOSE(DLLTEXT("pOEMDevIn:\r\n"));
        Dump(pOEMDevIn);

        // Set the devmode defaults so that anything that isn't copied over will
        // be set to the default value.
        pOEMDevOut->dwDriverDataUi    = 0;
        pOEMDevOut->dwAdvancedData  = 0;
		

        // Copy the old structure in to the new using which ever size is the smaller.
        // Devmode maybe from newer Devmode (not likely since there is only one), or
        // Devmode maybe a newer Devmode, in which case it maybe larger,
        // but the first part of the structure should be the same.

        // DESIGN ASSUMPTION: the private DEVMODE structure only gets added to;
        // the fields that are in the DEVMODE never change only new fields get added to the end.

        memcpy(pOEMDevOut, pOEMDevIn, __min(pOEMDevOut->dmOEMExtra.dwSize, pOEMDevIn->dmOEMExtra.dwSize));

        // Re-fill in the size and version fields to indicated 
        // that the DEVMODE is the current private DEVMODE version.
        pOEMDevOut->dmOEMExtra.dwSize       = sizeof(OEMDEV);
        pOEMDevOut->dmOEMExtra.dwVersion    = OEM_VERSION;
    }
    else
    {
        WARNING(DLLTEXT("Unknown DEVMODE signature, pOEMDMIn ignored.\r\n"));

        // Don't know what the input DEVMODE is, so just use defaults.
        pOEMDevOut->dmOEMExtra.dwSize       = sizeof(OEMDEV);
        pOEMDevOut->dmOEMExtra.dwSignature  = OEM_SIGNATURE;
        pOEMDevOut->dmOEMExtra.dwVersion    = OEM_VERSION;
        pOEMDevOut->dwDriverDataUi            = 0;
        pOEMDevOut->dwAdvancedData          = 0;

		
    }

    return TRUE;
}


BOOL bMakeOEMDevmodeValid(POEMDEV pOEMDevmode)
{
    if(NULL == pOEMDevmode)
    {
        return FALSE;
    }

    // ASSUMPTION: pOEMDevmode is large enough to contain OEMDEV structure.

    // Make sure that dmOEMExtra indicates the current OEMDEV structure.
    pOEMDevmode->dmOEMExtra.dwSize       = sizeof(OEMDEV);
    pOEMDevmode->dmOEMExtra.dwSignature  = OEM_SIGNATURE;
    pOEMDevmode->dmOEMExtra.dwVersion    = OEM_VERSION;

    // Set driver data, if not valid.
    if(pOEMDevmode->dwDriverDataUi > 100)
    {
        pOEMDevmode->dwDriverDataUi = 0;
    }

    // Set Advanced driver data, if not valid.
    if(pOEMDevmode->dwAdvancedData > 100)
    {
        pOEMDevmode->dwAdvancedData = 0;
    }

    return TRUE;
}


void Dump(PCOEMDEV pOEMDevmode)
{
    if( (NULL != pOEMDevmode)
        &&
        (pOEMDevmode->dmOEMExtra.dwSize >= sizeof(OEMDEV))
        &&
        (OEM_SIGNATURE == pOEMDevmode->dmOEMExtra.dwSignature)
      )
    {
        VERBOSE(TEXT("\tdmOEMExtra.dwSize      = %d\r\n"), pOEMDevmode->dmOEMExtra.dwSize);
        VERBOSE(TEXT("\tdmOEMExtra.dwSignature = %#x\r\n"), pOEMDevmode->dmOEMExtra.dwSignature);
        VERBOSE(TEXT("\tdmOEMExtra.dwVersion   = %#x\r\n"), pOEMDevmode->dmOEMExtra.dwVersion);
        VERBOSE(TEXT("\tdwDriverDataUi           = %#x\r\n"), pOEMDevmode->dwDriverDataUi);
        VERBOSE(TEXT("\tdwAdvancedData         = %#x\r\n"), pOEMDevmode->dwAdvancedData);
    }
    else
    {
        ERR(ERRORTEXT("Dump(POEMDEV) unknown private OEM DEVMODE.\r\n"));
    }
}



