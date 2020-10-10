
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1998 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:   oemjtprovider.hxx
//    
//
//  PURPOSE:  Definition of TOEMJTProvider Class.
//
//  



#ifndef _OEMJTPROVIDER_HXX_
#define _OEMJTPROVIDER_HXX_

#include "jthandler.hxx"

//
//The Provider class to Implement IPrintOemJobTicketProvider Interface
//
class TOEMJTProvider : public IPrintOemJobTicketProvider
{   

public:

    //  
    //Public Methods go here
    //
    TOEMJTProvider();
    ~TOEMJTProvider();
    
    //
    //Basic COM Methods
    //
    STDMETHODIMP QueryInterface(THIS_ REFIID riid, void **ppvObj);

    STDMETHODIMP_(ULONG) AddRef(THIS);

    STDMETHODIMP_(ULONG) Release(THIS);


    //
    // IPrintOemJobTicketProvider methods
    //  

    STDMETHOD(GetSupportedVersions)( THIS_ 
            IN HANDLE hPrinter,
            OUT INT *ppVersions[],
            OUT INT *cVersions 
            ) ;
        
    STDMETHOD(BindPrinter)( THIS_
            IN HANDLE         hPrinter,
            IN INT            version,
            OUT POEMJTOPTS    pOptions,
            OUT INT          *cNamespaces,
            OUT BSTR        **ppNamespaces
            ) ;

    STDMETHOD(PublishJobTicketHelperInterface)( THIS_
            IN IPrintJobTicketPluginHelperUI *pHelper
            ) ;

    STDMETHOD(QueryDeviceDefaultNamespace)( THIS_
            OUT BSTR *pbstrNamespaceUri
            ) ;

    STDMETHOD(ConvertJobTicketToDevMode)( THIS_ 
            IN IXMLDOMDocument2 *pJobTicket,
            IN ULONG             cbDevmode,
            IN OUT PDEVMODE      pDevmode,
            IN ULONG             cbDrvPrivateSize,
            IN PVOID             pPrivateDevmode
            ) ;
        
    STDMETHOD(ConvertDevModeToJobTicket)( THIS_ 
            IN ULONG             cbDevmode,
            IN PDEVMODE          pDevmode,
            IN ULONG             cbDrvPrivateSize,
            IN PVOID             pPrivateDevmode,
            IN OUT IXMLDOMDocument2 *pJobTicket
            ) ;
        
    STDMETHOD(CompleteDeviceCapabilities)( THIS_ 
            IN IXMLDOMDocument2     *pJobTicket,
            IN OUT IXMLDOMDocument2 *pCapabilities
            ) ;
        
    STDMETHOD(CompleteDeviceDefaultJobTicket)( THIS_ 
            IN OUT IXMLDOMDocument2 *pJobTicket 
            ) ;
        
    STDMETHOD(ExpandIntentOptions)( THIS_
            IN OUT IXMLDOMDocument2 *pJobTicket
            );

    STDMETHOD(ValidateJobTicket)( THIS_ 
            IN OUT IXMLDOMDocument2 *pBaseTicket
            ) ;



    private:
        //
        //Data members go here
        //
        LONG m_cRef; // COM reference count 
        HANDLE  m_hPrinterCached; // printer handle cached 
        IPrintJobTicketPluginHelperUI * m_pCoreDriverJTHelp; //cached pointer to plug-in helper interface       
        
        //
        //Private Methods 
        //              

        HRESULT ReadAndDeleteGPDStapleFeatureFromJT(
            IN OUT ihvjthandler::JobTicketHandler * jth,
            IN OUT INT * stapleIndex
            );

        HRESULT AddGPDStapleFeatureToJT(
            IN OUT ihvjthandler::JobTicketHandler * jth,
            IN INT stapleIndex
            );

        HRESULT ReadAndDeletePrintschemaStapleFeatureFromJT(
            IN OUT ihvjthandler::JobTicketHandler * jth,
            IN OUT INT * stapleIndex
            );

        HRESULT ReadAndDeleteGPDStapleFeatureFromDevCaps(
            IN OUT ihvjthandler::JobTicketHandler * pJth,
            OUT INT stapleIndexArray[], // can be NULL
            OUT BSTR stapleConstrainArray[]
            );

        HRESULT AddPrintschemaStapleFeatureToJT(
            IN OUT ihvjthandler::JobTicketHandler * jth,
            IN INT stapleIndex
            );

        HRESULT AddPrintschemaStapleFeatureToDevCaps(
            IN OUT ihvjthandler::JobTicketHandler * jth,
            IN OUT INT stapleIndexArray[],
            IN OUT BSTR stapleConstrainArray[]
            );      

        HRESULT PerformSmartNup(
            IN OUT ihvjthandler::JobTicketHandler * pJth
            );

}; 


#endif

