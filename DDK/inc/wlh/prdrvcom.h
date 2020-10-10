/*++

Copyright (c) 2003 Microsoft Corporation

Module Name:

    prdrvcom.h

Abstract:

    Interface declaration for Windows NT printer driver COM interfaces

--*/

#ifndef _PRDRVCOM_H_
#define _PRDRVCOM_H_

// 
// This file has to be included after objbase.h or comcat.h from sdk\inc.
//

//
// Each dll/exe must initialize the GUIDs once.If you are not using precompiled
// headers for the file(s) which initializes the GUIDs, define INITGUID before
// including objbase.h.
//

//
// Class ID for Job Ticket Provider.
//
// {46AC151B-8490-4531-96CC-55BF2BF19E11}
//

DEFINE_GUID(CLSID_JTPROVIDER, 0x46ac151b, 0x8490, 0x4531, 0x96, 0xcc, 0x55, 0xbf, 0x2b, 0xf1, 0x9e, 0x11);

//
// Interface ID for IPrintJobTicketProvider interface
//
// {BB5116DB-0A23-4c3a-A6B6-89E5558DFB5D}
//

DEFINE_GUID(IID_IPrintJobTicketProvider, 0xbb5116db, 0xa23, 0x4c3a, 0xa6, 0xb6, 0x89, 0xe5, 0x55, 0x8d, 0xfb, 0x5d);


#undef IUnknown

#ifdef __cplusplus
extern "C" {
#endif



#define E_VERSION_NOT_SUPPORTED       (0x80040001)


#define S_NO_CONFLICT                 (0x00040001)
#define S_CONFLICT_RESOLVED           (0x00040002)

typedef 
enum tagSHIMOPTS
{	
    JTSHIM_DEFAULT	= 0,
    JTSHIM_NOSNAPSHOT = 0x1
} SHIMOPTS, *PSHIMOPTS;

//
//****************************************************************************
//  IPrintJobTicketProvider interface
//****************************************************************************
//
#undef INTERFACE
#define INTERFACE IPrintJobTicketProvider


DECLARE_INTERFACE_(IPrintJobTicketProvider, IUnknown)
{
    //
    // IUnknown methods
    //

    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID* ppvObj)PURE;
    STDMETHOD_(ULONG, AddRef) (THIS)PURE;
    STDMETHOD_(ULONG, Release) (THIS)PURE;

    //
    // IPrintJobTicketProvider methods
    //

    STDMETHOD(GetSupportedVersions)( THIS_ 
            IN HANDLE hPrinter,
            OUT INT *ppVersions[],
            OUT INT *cVersions 
            ) PURE;
        
    STDMETHOD(BindPrinter)( THIS_
            IN HANDLE         hPrinter,
            IN INT            version,
            OUT PSHIMOPTS     pOptions,
            OUT DWORD        *pDevModeFlags,
            OUT INT          *cNamespaces,
            OUT BSTR        **ppNamespaces
            ) PURE;
        
    STDMETHOD(ConvertJobTicketToDevMode)( THIS_ 
            IN IXMLDOMDocument2 *pJobTicket,
            IN ULONG             cbDevmode,
            IN OUT PDEVMODE      pDevmode
            ) PURE;
        
    STDMETHOD(ConvertDevModeToJobTicket)( THIS_ 
            IN ULONG             cbDevmode,
            IN PDEVMODE          pDevmode,
            IN IXMLDOMDocument2 *pJobTicket
            ) PURE;
        
    STDMETHOD(AcquireDeviceCapabilities)( THIS_ 
            IN IXMLDOMDocument2   *pJobTicket,
            OUT IXMLDOMDocument2 **ppCapabilities
            ) PURE;
        
    STDMETHOD(GetDeviceDefaultJobTicket)( THIS_ 
            IN OUT IXMLDOMDocument2 *pTicket 
            ) PURE;
        
    STDMETHOD(ValidateJobTicket)( THIS_ 
            IN OUT IXMLDOMDocument2 *pBaseTicket
            ) PURE;

};


#ifdef __cplusplus
}
#endif

#endif  // !_PRDRVCOM_H_




