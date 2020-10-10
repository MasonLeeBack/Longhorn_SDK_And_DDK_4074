//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1998 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:   oemjtprovider.cxx
//    
//
//  PURPOSE:  Implementation of TOEMJTProvider Class.
//              The Provider class implements the IPrintOemJobTicketProvider interface functions that 
//              provide the plug-in access to Job Ticket and allow the plug-in to understand the Unidrv private
//              setting in the Job Ticket and expose its private settings to Unidrv by putting 
//              them publicly in the Job Ticket. The various provider methods make use of the IPrintJobTicketPluginHelperUI
//              Interface methods to create instances of XML objects and to communicate information with Unidrv.
//
//  Functions:
//          IPrintOemJobTicketProvider Interface Functions.
//          Private Functions of class TOEMJTProvider.
//
//
//


#include "precomp.h"


//
// Nup features values that we are interested in to perform out smart nup example
//
#define NUP_OPTIONS_COUNT  2


//
// Nup values 2 and 6 are the only Nup values we are interested in because
// if current Nup setting is one of the two, we want to change out Staple
// Location setting
//
INT nupValues[ NUP_OPTIONS_COUNT ] = { 2, 6 };

//
// Number of Staple Options supported by the Printschema
//

typedef
enum tagSTAPLEOPTIONSCOUNT
{

    STAPLE_OPTIONS_COUNT_PRINTSCHEMA = 9 ,
    STAPLE_OPTIONS_COUNT_GPD = 7 ,
    STAPLE_OPTIONS_COUNT_COMMON = 4     

}EStapleOptionsCount, * PEStapleOptionsCount;


//
// Structure to perform mapping between GPD Staple Feature and Printschema Staple Feature
//

struct tagGpdToPrintschemaConversion
{
    LPWSTR gpdOptionName;
    LPWSTR printschemaOptionName;
    LPWSTR alternateOptionNameForSmartNup;
    LPWSTR gpdDisplayName;
    INT stapleAngle;

}gpdToPrintschema[STAPLE_OPTIONS_COUNT_GPD] =
{
    //
    // Options that map to Printschema
    //
    { gpd::staple::OPTION_NONE, printschema::staple::STAPLE_LOCATION_NONE , printschema::staple::STAPLE_LOCATION_NONE, gpd::staple::VALUE_NONE , 0 },
    { gpd::staple::OPTION_ONE_PARALLEL,printschema::staple::STAPLE_LOCATION_TOP_LEFT , printschema::staple::STAPLE_LOCATION_TOP_RIGHT , gpd::staple::VALUE_ONE_PARALLEL , 0 },
    { gpd::staple::OPTION_ONE_DIAGONAL,printschema::staple::STAPLE_LOCATION_TOP_LEFT , printschema::staple::STAPLE_LOCATION_TOP_RIGHT , gpd::staple::VALUE_ONE_DIAGONAL , 45 },
    { gpd::staple::OPTION_TWO_PARALLEL,printschema::staple::STAPLE_LOCATION_DUAL_LEFT , printschema::staple::STAPLE_LOCATION_DUAL_TOP, gpd::staple::VALUE_TWO_PARALLEL , 0 } ,

    //
    // Options that do not map to Printschema
    //
    { gpd::staple::OPTION_THREE_PARALLEL, NULL , NULL, gpd::staple::VALUE_THREE_PARALLEL , 0 },
    { gpd::staple::OPTION_STITCHING, NULL , NULL , gpd::staple::VALUE_STITCHING , 0 },
    { gpd::staple::OPTION_CUSTOM, NULL , NULL , gpd::staple::VALUE_CUSTOM , 0 }
    
};


/*++

Routine Name:

    TOEMJTProvider constructor

Routine Description:

    Constructor

Arguments:

    None

Return Value:

    None

--*/
TOEMJTProvider::TOEMJTProvider()
{   
    m_pCoreDriverJTHelp = NULL;
    m_cRef = 1;     
}



/*++

Routine Name:

    TOEMJTProvider destructor

Routine Description:

    Destructor

Arguments:

    None

Return Value:

    None

--*/
TOEMJTProvider::~TOEMJTProvider()
{

    // Make sure that helper interface is released.
    
    if( m_pCoreDriverJTHelp )
    {
        m_pCoreDriverJTHelp->Release();
        m_pCoreDriverJTHelp = NULL;
    }

    //
    // If this instance of the object is being deleted, then the reference 
    // count should be zero.
    //
    ASSERT(0 == m_cRef);    

}




/*++

Routine Name:

    TOEMJTProvider QueryInterface

Routine Description:

    Returns a pointer to a specified interface on an object to which a client currently holds an 
    interface pointer. 
    This function must call IUnknown::AddRef on the pointer it returns. 

Arguments:

   riid - Identifier of requested Interface.
   ppObj - Output variable that receives the pointer to requested Interface on success

Return Value:

    HRESULT
    S_OK - If the Interface requested is supported 
    E_NOINTERFACE otherwise

--*/


STDMETHODIMP 
TOEMJTProvider::
QueryInterface(
    REFIID riid, 
    void **ppObj
    )
{
    if ( (riid == IID_IUnknown) || (riid == IID_IPrintOemJobTicketProvider) )
    {
        *ppObj = static_cast<IPrintOemJobTicketProvider *>(this);       
    }
    else
    {
        *ppObj = NULL ;
        return E_NOINTERFACE ;
    }
    reinterpret_cast<IUnknown*>(*ppObj)->AddRef();
    return S_OK ;
    
}


/*++

Routine Name:

    AddRef

Routine Description:

    The AddRef method increments the reference count for an an interface
    on an object. It should be called for every new copy of a pointer to
    an interface on a given object.

Arguments:

    None

Return Value:

    Returns the value of the new reference count.

--*/
STDMETHODIMP_(ULONG) 
TOEMJTProvider::
AddRef(
     VOID
      )
{
    return InterlockedIncrement(&m_cRef);
}



/*++

Routine Name:

    Release

Routine Description:

    The Release method decrements the reference count for the calling
    interface on a object. If the reference count on the object falls
    to 0, the object is freed from memory.

Arguments:

    None

Return Value:

    Returns the resulting value of the reference count.

--*/
STDMETHODIMP_(ULONG)
TOEMJTProvider::
Release(
    THIS
        )
{
    //OEMDBG(DBG_VERBOSE, L"TOEMJTProvider::Release() entry.");
    ULONG   cRef    = InterlockedDecrement(&m_cRef);

    if (cRef == 0)
    {
        delete this;
        return 0;
    }
    return cRef;
}




/*++

Routine Name:
        BindPrinter

Routine Description:
    Bind Printer is the part of the Unidrv's activity to bind to a device. It allows the plug-in to cache
    certain information that can be used later on.
        

Arguments:
    hPrinter - Printer Handle supplied by Unidrv
    version - version of Printschema
    pOptions - Flags passed out to set configurable options supported by caller
    cNamespaces - Count of private namespaces of plug-in 
    ppNamespaces - OUT pointer to the array of Namespace URIs filled in by plug-in

Return Value:
    HRESULT
    S_OK - On Success
    E_VERSION_NOT_SUPPORTED - if printer version specified is not supported by plug-in
    E_* - On any other failure

--*/

STDMETHODIMP TOEMJTProvider::BindPrinter
(
    IN HANDLE         hPrinter,
    IN INT            version,
    OUT POEMJTOPTS    pOptions,
    OUT INT          *cNamespaces,
    OUT BSTR        **ppNamespaces
 )
{
    HRESULT hr = S_OK;
    

    //
    // check if input parameters are NULL
    // Printer Handle should be provided by Unidrv in this call, which is cached by plug-in provider anbd
    // is later on used while making calls to Plug-in Helper Interface methods.
    //
    if( !pOptions  || !cNamespaces || !ppNamespaces || !hPrinter )
    {
        return E_INVALIDARG; 
    }


    *ppNamespaces = NULL;
    
    *cNamespaces = 0;

    //
    // Agree on the Printschema version with Unidrv
    // Version 1 is the only version currently supported
    //
    if( PRINTSCHEMA_VERSION_NUMBER != version  )
    {
        return E_VERSION_NOT_SUPPORTED;        
    }

    //
    // Bind to the Physical Printer device
    // cache the printer handle for further use if input handle is not same as the one already cached
    //
    if(  hPrinter != m_hPrinterCached )
    {       
        hPrinter = m_hPrinterCached;
    }


    //
    // Flags to set configurable options, 
    // OEMJT_DEFAULT defined in prcompem.h
    //
    *pOptions = OEMJT_DEFAULT;

    //
    //Number of private namespace URIs that the plug-in wantes to specify to Unidrv
    //
    *cNamespaces = 1;
        

    LONG namespaceLen = 0;
    
    hr = StringCchLength( printschema::PLUGIN_NAMESPACE_URI , STR_MAX_CCH , (size_t *)&namespaceLen );

    if( SUCCEEDED(hr) )
    {
        //
        // Fill in the input version array with the namespace URI strings
        //

        //
        // StringCchLength returns length of string excluding null terminator
        //
        namespaceLen = namespaceLen + 1;

        *ppNamespaces = (BSTR*)CoTaskMemAlloc( sizeof(BSTR)*(*cNamespaces) );

        if( *ppNamespaces )
        {

            (*ppNamespaces)[0] = SysAllocStringLen( NULL , namespaceLen );
            
            if( (*ppNamespaces)[0] )
            {
                hr = StringCchPrintf( **ppNamespaces, namespaceLen , L"%s" , printschema::PLUGIN_NAMESPACE_URI );
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }                   
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }

    }


    if( FAILED(hr) )
    {
        if( *ppNamespaces )
        {
            if( (*ppNamespaces)[0] )
            {
                SysFreeString( (*ppNamespaces)[0] );
                (*ppNamespaces)[0]  = NULL;
            }

            CoTaskMemFree( *ppNamespaces );
            *ppNamespaces = NULL;
        }
    }

    return hr;
    
}




/*++

Routine Name:
        GetSupportedVersions

Routine Description:
        The routine returns major versions of Printschema schema supported by the plug-in Provider.


Arguments:
        hPrinter - Printer Handle
        ppVersions - OUT pointer to array of version numbers to be filled in by the plug-in
        cVersions - OUT pointer to count of Number of versions supported by plug-in

Return Value:
        HRESULT
        S_OK - On Success
        E_* - On failure

--*/
STDMETHODIMP TOEMJTProvider::GetSupportedVersions
( 
    IN HANDLE hPrinter,
    OUT INT *ppVersions[],
    OUT INT *cVersions 
)
{
    HRESULT hr = S_OK;

    //
    // check if input parameters are valid
    //
    if( !ppVersions || !cVersions )
    {
        return E_INVALIDARG;
    }

    
    //
    // The Plug-in Provider need to allocate memory for the input version arry and
    // then fill it with version information
    //

    *ppVersions = (INT*)CoTaskMemAlloc( sizeof(INT) ); 

    if( !*ppVersions )
    {
        return E_OUTOFMEMORY;
    }
    else
    {
        //
        // version number 1 is the only version supported currently
        //
        (*ppVersions)[0] = PRINTSCHEMA_VERSION_NUMBER;          
    }

    //
    //count of number of verisons supported
    //
    *cVersions = 1;

    return hr;
} 



/*++

Routine Name:
        PublishJobTicketHelperInterface

Routine Description:
        For a number of operations, the plug-in needs to use the Helper Interface utilities provided by 
        Unidrv. Unidrv uses this method to publish the Job Ticket Helper Interface, IPrintJobTicketPluginHelperUI.
        Plug-in should return SUCCESS after successfully incrementing the reference count of the interface.

Arguments:
        pHelper - IPrintJobTicketPluginHelperUI interface pointer

Return Value:
        HRESULT
        S_OK - On Success
        E_* - On failure
    
--*/
STDMETHODIMP TOEMJTProvider::PublishJobTicketHelperInterface
( 
        IN IPrintJobTicketPluginHelperUI *pHelper
) 
{   

    if( !pHelper )
    {
        return E_INVALIDARG;
    }


    HRESULT hr = S_OK;


    //
    // Need to store pointer to Driver Helper functions, if we already haven't.
    //
    if ( NULL == m_pCoreDriverJTHelp )
    {
        //
        // Get Interface to Plug-in Helper Functions and save it.
        //
        hr = pHelper->QueryInterface( IID_IPrintJobTicketPluginHelperUIUni, (void** ) &(m_pCoreDriverJTHelp));

        if( !SUCCEEDED(hr) )
        {
            //
            // Make sure that interface pointer reflects interface query failure.
            //
            m_pCoreDriverJTHelp = NULL;
            return E_FAIL;
        }       


    }
      
    //
    // Plug-in should return success after a successful query interface.
    // If any handshake is to be performed between the Plug-in and Unidrv, it should be performed before
    // plug-in actually starts using the helper interface.
    //
    return S_OK;
}



/*++

Routine Name:
        QueryDeviceDefaultNamespace

Routine Description:
    
    Plug-in should specify the name of Private namespace URI that Unidrv should be 
    using to handle any features defined in the GPD that Unidrv does not recognize
    plug-in may specify a set of namespaces as a result of the call to BindPrinter method,
    and Unidrv needs to know which of them is to be used as default namespace
    so that, for all the features that Unidrv does not recognize, it will put them under 
    this namespace in Job Ticket

    Note: It is Unidrv's responsibility to add the private namespace URI that plug-in has spedified
    through this call in the root node of the DOM document, and also define a prefix for it
    so that plug-in should use the prefix defined by Unidrv when it wishes to add any new node 
    to the Job Ticket under its private namespace. Plug-in should not define its own prefix for this
    default private namespace URI.

Arguments:
    pbstrNamespaceUri - OUT Pointer to namespace URI to be filled in and returned by plug-in

Return Value:
    HRESULT
    S_OK - On success
    E_* - On failure

--*/

STDMETHODIMP TOEMJTProvider::QueryDeviceDefaultNamespace
(
        OUT BSTR *pbstrNamespaceUri
)
{
        
    if( ! pbstrNamespaceUri )
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;
    
    *pbstrNamespaceUri = NULL;

    LONG namespaceLen = 0;

    hr = StringCchLength( printschema::PLUGIN_NAMESPACE_URI ,STR_MAX_CCH , (size_t *)&namespaceLen );

    if( SUCCEEDED(hr) )
    {
        namespaceLen = namespaceLen + 1;

        *pbstrNamespaceUri = SysAllocStringLen( NULL, namespaceLen );

        if( *pbstrNamespaceUri )
        {
            hr = StringCchPrintf( *pbstrNamespaceUri, namespaceLen , L"%s" ,printschema::PLUGIN_NAMESPACE_URI);
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }   
    }

    if( FAILED(hr) )
    {
        if( *pbstrNamespaceUri )
        {
            SysFreeString( *pbstrNamespaceUri );
            *pbstrNamespaceUri = NULL;
        }
    }

    return hr;
    

}//End Function





/*++

Routine Name:
        ConvertJobTicketToDevMode

Routine Description:
        Unidrv will call this routine before it performs it's part of JT->DM conversion. The plug-in is passed
        with an input Job Ticket that is fully populated, and Devmode which has default setting in it.
        For this conversion, the plug-in needs to undo whatever changes it made to the Job Ticket during 
        Devmode->JT conversion. It thus needs to put the Staple feature back under private namespace and in the
        format that Unidrv understands (ie format in which Unidrv had previously put the feature in the JT 
        provided to plugin in ConvertDevmodeToJobTicket function). This is necessary so that while performing its
        part of JT->Devmode conversion Unidrv will be able to recognize the Stapling feature in the job ticket
        and reflect its settings in Unidrv Private Devmode.
    

Arguments:
        pJobTicket - pointer to input Job Ticket
        cbDevmode - size in bytes of input full devmode
        pDevmode - pointer to input full devmode buffer
        cbDrvPrivateSize - buffer size in bytes of plug-in private devmode
        pPrivateDevmode - pointer to plug-in private devmode buffer
        

Return Value:
        HRESULT
        S_OK - On Success
        E_* - On failure

--*/
STDMETHODIMP TOEMJTProvider::ConvertJobTicketToDevMode
(
    IN IXMLDOMDocument2 *pJobTicket,
    IN ULONG             cbDevmode,
    IN OUT PDEVMODE      pDevmode,            
    IN ULONG             cbDrvPrivateSize,
    IN PVOID             pPrivateDevmode
)
{   

    if( !cbDevmode || !pDevmode || !pJobTicket || !cbDrvPrivateSize || !pPrivateDevmode )
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;
    
    INT stapleIndex = 0;

    //
    //Initialize the helper class to handle JT related XML handling
    //
    ihvjthandler::JobTicketHandler jth;
        

    hr = jth.SetRoot(pJobTicket,m_pCoreDriverJTHelp);
            

    //
    // Remove the Staple Feature put in Printschema format from the input JT
    //
    
    
    if(SUCCEEDED(hr))
    {
        hr = ReadAndDeletePrintschemaStapleFeatureFromJT(&jth,&stapleIndex);
    }
    

    //
    // Now add the Staple Feature according to GPD format to the JT
    // IMPORTANT: check for hr == S_OK and not SUCCEEDED(hr) because all the Get methods
    // to get an XML element return S_FALSE if feature is not found
    //
    if( hr == S_OK )
    {
        hr = AddGPDStapleFeatureToJT(&jth,stapleIndex);
    }

    if( hr == S_FALSE )
    {
        hr = S_OK;
    }
    
    return hr;

}//End function




/*++

Routine Name:
    ConvertDevModeToJobTicket

Routine Description:
    Unidrv will call the routine with an Input Job Ticket that is populated with public and Unidrv 
    private features. For those features in the GPD that Unidrv doesnot understand, it puts them in JT
    under the private namespace (either specified by the plug-in through QueryDeviceDefaultNamespace or 
    created by itself). It is plug-ins responsibility to read the corresponding features from the input 
    JT and put them in public printschema namespace, so that any higher level application making use of 
    a job ticket can read and interpret these settings.


Arguments:
    cbDevmode - size in bytes of input full devmode
    pDevmode - pointer to input full devmode buffer
    cbDrvPrivateSize - buffer size in bytes of plug-in private devmode
    pPrivateDevmode - pointer to plug-in private devmode buffer
    pJobTicket - pointer to input Job Ticket

Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/
STDMETHODIMP TOEMJTProvider::ConvertDevModeToJobTicket
(
    IN ULONG             cbDevmode,
    IN PDEVMODE          pDevmode,
    IN ULONG             cbDrvPrivateSize,
    IN PVOID             pPrivateDevmode,
    IN IXMLDOMDocument2 *pJobTicket
)
{
    
    if( !cbDevmode || !pDevmode || !cbDrvPrivateSize || !pPrivateDevmode || !pJobTicket )
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;
    
    ihvjthandler::JobTicketHandler jth;
    
    INT stapleIndex = 0;        
    

    hr = jth.SetRoot(pJobTicket,m_pCoreDriverJTHelp);
    

    //
    // Remove the Staple Feature put in GPD format from the input JT
    //      
    
    if(SUCCEEDED(hr))
    {
        hr = ReadAndDeleteGPDStapleFeatureFromJT( &jth,&stapleIndex );
    }
    

    //
    //Now put the Staple feature under Printschema namespace in the job ticket
    //

    if ( hr == S_OK ) 
    {
        hr = AddPrintschemaStapleFeatureToJT(&jth,stapleIndex);
    }   

    if( hr == S_FALSE )
    {
        hr = S_OK;
    }
    return hr;

}



/*++

Routine Name:
        CompleteDeviceCapabilities

Routine Description:
        Unidrv calles this routine with an input Device Capabilities Document that is partially
        populated with Device capabilities information filled in by Unidrv for features that it
        understands. For GPD features like Staple that Unidrv does not understand, it puts them under the
        plug-in private namespace. Plug-in needs to read those features in the input Job Ticket, delete
        them and add them back under Printschema namespace so that any higher level Application can 
        understand them and make use of them.
        The input Devcaps provided by Unidrv might have only a subset of the 7 possible options
        for Stapling feature, hence the plug-in needs to go through the Staple Feature settings created by
        Unidrv and identify the set of options currently present in it and populate only those options
        under the featue node that it creates.
        For Staple feature, only 4 out of the 7 options specified in GPD can be mapped to corresponding
        printschema options, hence the plug-in puts these options under public printschema namespace in
        printschema format, the remaining options present in input Devcaps that do not map to any options
        in printschema are left as it is.

Arguments:
        pJobTicket - pointer to input Job Ticket ( can be NULL )
        pCapabilities - pointer to Device Capabilities Document.

Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/
STDMETHODIMP TOEMJTProvider::CompleteDeviceCapabilities
( 
    IN IXMLDOMDocument2   *pJobTicket, // can be NULL
    IN OUT IXMLDOMDocument2 *pCapabilities
) 
{    
    
    if( !pCapabilities )
    {
        return E_INVALIDARG;
    }


    HRESULT hr = S_OK;  
    IXMLDOMElement * pStapleFeatureOld = NULL;  
    ihvjthandler::JobTicketHandler jth;         
    
    INT stapleIndexArray[ STAPLE_OPTIONS_COUNT_GPD ] ;
    BSTR stapleConstrainArray[ STAPLE_OPTIONS_COUNT_GPD ] ;

    //
    // Initialize stapleIndexArray
    //

    for( INT i=0; i < STAPLE_OPTIONS_COUNT_GPD ; i++ )
    {
        stapleIndexArray[i] = -1;
    }


    for( INT i=0; i < STAPLE_OPTIONS_COUNT_GPD ; i++ )
    {
        stapleConstrainArray[i] = NULL;     
    }


    hr = jth.SetRoot(pCapabilities,m_pCoreDriverJTHelp);    
    
    if( hr == S_OK )
    {
        hr = ReadAndDeleteGPDStapleFeatureFromDevCaps( &jth, stapleIndexArray , stapleConstrainArray );
    }
    

    if( hr == S_OK )
    {
        //
        // We successfully found Staple Feature in input DC
        // Now add Staple feature according to Printschema format
        //
        hr = AddPrintschemaStapleFeatureToDevCaps( &jth, stapleIndexArray , stapleConstrainArray );
    }   
    

    for( INT i=0; i < STAPLE_OPTIONS_COUNT_GPD ; i++ )
    {
        if( stapleConstrainArray[i] )
        {
            SysFreeString( stapleConstrainArray[i] );
        }
    }

    if( hr == S_FALSE )
    {
        hr = S_OK;
    }

    return hr;     
    

}

/*++

Routine Name:
    CompleteDeviceDefaultJobTicket
    
Routine Description:
    Unidrv will call the routine with an Input Job Ticket that is populated with default settings for public 
    and Unidrv private features. For those features in the GPD that Unidrv doesnot understand, it puts them in JT
    under the private namespace corresponding to the private namespace URI specified by the plug-in through
    QueryDeviceDefaultNamespace. It is plug-ins responsibility to read the those features from the input JT 
    and default setting made by Unidrv for them and put them in public printschema namespace, so that 
    any higher level application can read and interpret them.

Arguments:
    pJobTicket - pointer to input Job Ticket

Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/

STDMETHODIMP TOEMJTProvider::CompleteDeviceDefaultJobTicket
( 
    IN OUT IXMLDOMDocument2 *pJobTicket 
)
{
    
    if(!pJobTicket)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;
    
    INT stapleIndex = 0;

    ihvjthandler::JobTicketHandler jth;
        

    hr = jth.SetRoot(pJobTicket,m_pCoreDriverJTHelp);  
    

    //
    // Remove the Staple Feature put under plug-in private namespace from the input JT
    //
    
    if(SUCCEEDED(hr))
    {
        hr = ReadAndDeleteGPDStapleFeatureFromJT( &jth,&stapleIndex );
    }
    

    //
    //Now create the feature element under public namespace in the job ticket
    // IMPORTANT: check for hr == S_OK and not SUCCEEDED(hr) because all the Get methods
    // to get an XML element return S_FALSE if feature is not found
    //

    if( hr == S_OK )
    {
        hr = AddPrintschemaStapleFeatureToJT(&jth,stapleIndex);
    }       

    if( hr == S_FALSE )
    {
        hr = S_OK;
    }

    return hr;

}//End function


/*++

Routine Name:
    ExpandIntentOptions
        
Routine Description:
    As part of its Merge and Validate Procedure, the Unidrv / Postscript driver will call this routine
    to give the plug-in a chance to expand options which represent intent into their individual settings
    in other features in the job ticket.  This has two important effects: the client sees the results of 
    the intent expansion, and unidrv resolves constraints against the individual features which are affected 
    by the intent.

    If the plug-in does not support any intent features, then the plug-in should simply return S_OK.

Arguments:
    pJobTicket - Pointer to input Job Ticket.

Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/

STDMETHODIMP TOEMJTProvider::ExpandIntentOptions(
    IN OUT IXMLDOMDocument2 *pJobTicket
    )
{
    return S_OK;
} // End Function




/*++

Routine Name:
    ValidateJobTicket
        
Routine Description:
    As part of its Merge and Validate Procedure, the base job ticket which is a result of Merge procedure performed
    by Unidrv will have Staple Feature under public Printschema namespace, 
    when Unidrv will validate the Job Ticket resultant from Merge procedure, it will again put the GPD features like 
    Staple that it doesnot recognize under plug-in private namespace in JT, irrespective of the Staple feature 
    already present in the same JT under public namespace.
    
    Plug-in therefore needs to read the feature under private namespace from input JT and delete it.

    Validate Method should also perform any conflict resolution if necessary looking at the
    settings made in public and unidrv private part of Job Ticket, to make sure that
    the resultant Job Ticket is a valid one, and it has all constraints resolved.

Arguments:
    pBaseTicket - Pointer to input Job Ticket.

Return Value:
    HRESULT
    S_NO_CONFLICT/S_CONFLICT_RESOLVED - On Success
    E_* - On failure

--*/

STDMETHODIMP TOEMJTProvider::ValidateJobTicket(
    IN OUT IXMLDOMDocument2 *pBaseTicket    
    )
{
    //
    // Here we are performing smart Nup feature with stapling, so that if Nup is set to say
    // 2 or 6 value, then since the orientation used to print the document pages on the 
    // physical page is changed, we change the stapleLocation option accordingly so that
    // the location option is with respect to short edge instead of long edge of the document
    //

    if(!pBaseTicket)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    INT stapleIndex = 0 ;
    
    ihvjthandler::JobTicketHandler jth;


    //
    //Initialize JobTicketHandler 
    //  
    hr = jth.SetRoot(pBaseTicket,m_pCoreDriverJTHelp);  
    
    
    if( SUCCEEDED(hr) )
    {
        hr = ReadAndDeleteGPDStapleFeatureFromJT( &jth, &stapleIndex );
    }
    

    if( hr == S_OK )
    {
        //
        // Staple feature was found under driver private namespace in JT
        // Now add pritnschema staple featue to JT and see if while adding that 
        // feature, Unidrv has made any changes in the 
        // settings as part of its validation and if so reflect those changes in the
        // printschema staple feature in JT
        //
        hr = AddPrintschemaStapleFeatureToJT(&jth,stapleIndex);

    }

    
    if( hr == S_OK )
    {
        //
        // We have successfully found and deleted GPD Staple feature from JT
        // Now perform smart Nup
        //
        hr = PerformSmartNup( &jth );
    }

    //
    // Important: If the plug-in performs validation successfully, it needs to send either
    // S_NO_CONFLICT or S_CONFLICT_RESOLVED as the result code, sending hr = S_OK will not work
    // since Unidrv expects one of the above two success codes to interpret successful completion  
    // of plug-in validate method
    //
    if( SUCCEEDED(hr) )
    {
        hr = S_NO_CONFLICT;
    }

    return hr;

}




/*++

Routine Name:
    ReadAndDeleteGPDStapleFeatureFromJT

Routine Description:
    Helper function to read the setting and delete Staple Feature that has been defined according to GPD
    definition from the input Job Ticket

Arguments:
   pJth - Pointer to input Job Ticket handler
   pStapleIndex - Integer index to remember the settting made by Unidrv ( can be NULL )

Return Value:
    HRESULT
    S_OK - On Successfully finding the Staple Feature Node in JT
    S_FALSE - If the Staple Feature node is not found in JT
    E_* - On failure


--*/


HRESULT 
TOEMJTProvider::ReadAndDeleteGPDStapleFeatureFromJT(
    IN OUT ihvjthandler::JobTicketHandler * pJth,
    IN OUT INT * pStapleIndex // can be NULL
    )
{

    HRESULT hr = S_OK;

    IXMLDOMElement * pStapleFeatureOld = NULL;
    IXMLDOMElement * pStapleOptionOld = NULL;

    BOOL bFound = FALSE;

    //
    //First examine the Staple Feature nod ein input JT that has been created by Unidrv 
    // based on the information about Staple Feature available in the GPD file
    // check what setting Unidrv has put
    // then remove the Staple Feature node that is created by Unidrv entirely from Job Ticket
    // and add Staple feature node under public printschema
    //

    if( !pJth )
    {
        return E_INVALIDARG;
    }

    hr = pJth->GetFeatureNode(NULL,printschema::PLUGIN_NAMESPACE_URI,gpd::staple::FEATURE_NAME,&pStapleFeatureOld);
    

    //  
    // IMPORTANT: check for hr == S_OK and not SUCCEEDED(hr) because GetFeatureNode 
    // returns S_FALSE if feature is not found
    //
    if( hr == S_OK && pStapleFeatureOld )
    {
                        
                //
                // check which option out of the 7 defined options is currently set in JT

                // If stapling is disabled, staple node will still be present in the Job Ticket
                // but staple location value will be None
                //
                
                bFound = FALSE;             

                for(INT i=0; i< STAPLE_OPTIONS_COUNT_COMMON && !bFound; i++)
                {
                    hr = pJth->GetOptionNode( pStapleFeatureOld,printschema::PLUGIN_NAMESPACE_URI,
                                              gpdToPrintschema[i].gpdOptionName,
                                              &pStapleOptionOld );
                
                    if( hr == S_OK && pStapleOptionOld )
                    {                       
                        if( pStapleIndex )
                        {
                            //
                            // Remember and return the setting made by Unidrv
                            //
                            *pStapleIndex = i;
                        }
                        bFound = TRUE;
                    }
                }//End for
    }

    if( hr == S_OK )        
    {
        //
        // Found the Staple feature node entirely in input JT, now remove it entirely       
        //
        if( bFound )
        {
            hr = pJth->DeleteFeatureNode(NULL,pStapleFeatureOld);
        }
        else
        {
            hr = S_FALSE;
        }
    }   
    
    
    //
    // Make sure that you release all Interface pointers when you no longer need them
    //
    if(pStapleFeatureOld)
    {
        pStapleFeatureOld->Release();
    }
    if(pStapleOptionOld)
    {
        pStapleOptionOld->Release();
    }   

    return hr;

}//End function




/*++

Routine Name:
    ReadAndDeletePrintschemaStapleFeatureFromJT

Routine Description:
    Helper function to read the setting and delete Staple Feature that has been defined according to Printschema 
    definition from the input Job Ticket

Arguments:
    pJth - Pointer to input Job Ticket handler

Return Value:
    HRESULT
    S_OK - On Successfully finding the Staple Feature Node in JT
    S_FALSE - If the Staple Feature node is not found in JT
    E_* - On failure

--*/

HRESULT 
TOEMJTProvider::ReadAndDeletePrintschemaStapleFeatureFromJT(
    IN OUT ihvjthandler::JobTicketHandler * pJth,
    IN OUT INT * pStapleIndex // can be NULL
    )
{

    HRESULT hr = S_OK;

    IXMLDOMElement * pStapleFeatureOld = NULL;
    IXMLDOMElement * pStapleOptionOld = NULL;
    IXMLDOMElement * pStaplePropertyOld = NULL;

    BOOL bFound = FALSE;

    INT value = 0;
    INT index = 0;
    //
    //First examine the Staple Feature node in input JT that has been created by Unidrv 
    // based on the information about Staple Feature available in the GPD file
    // check what setting Unidrv has put
    // then remove the Staple Feature node that is created by Unidrv entirely from Job Ticket
    // and add Staple feature node under public printschema
    //


    if( !pJth  )
    {
        return E_INVALIDARG;
    }


    hr = pJth->GetFeatureNode(NULL,printschema::PRINTSCHEMA_URI,
                              printschema::staple::STAPLE_FEATURE,
                              &pStapleFeatureOld);
    

    //
    //Delete Staple Feature node and all its children from the DOM tree.
    // IMPORTANT: check for hr == S_OK and not SUCCEEDED(hr) because all Get methods
    // to get an XML element return S_FALSE if feature is not found
    //
    if( hr == S_OK && pStapleFeatureOld )
    {       
                
                //
                // check which option out of the 4 options that are common between the GPD and printschema 
                // is currently set in JT . If stapling is disabled, staple node will still be present 
                // in the Job Ticket but staple location value will be None
                //
                
                bFound = FALSE;

                for(INT i=0; i< STAPLE_OPTIONS_COUNT_COMMON && !bFound; i++)
                {
                    hr = pJth->GetOptionNode(pStapleFeatureOld,
                                             printschema::PRINTSCHEMA_URI,
                                             gpdToPrintschema[i].printschemaOptionName,
                                             &pStapleOptionOld);
                
                    if( hr == S_OK && pStapleOptionOld )
                    {   
                        //
                        // Remember and return the settings in input JT
                        //
                        if( pStapleIndex )
                        {
                            *pStapleIndex = i;
                        }
                        index = i;

                        bFound = TRUE;
                    }
                }
    }

    if( hr == S_OK )
    {
        if( bFound )
        {
            hr = pJth->GetPropertyNode(pStapleOptionOld,
                                       printschema::PRINTSCHEMA_URI,
                                       printschema::staple::STAPLE_ANGLE_SCORED_PROPERTY,TRUE,
                                       &pStaplePropertyOld );  
                        
            if( hr == S_OK && pStaplePropertyOld )
            {
                hr = pJth->GetValueAsInt( pStaplePropertyOld, &value , NULL );
            }
        }
        else
        {
            hr = S_FALSE;
        }
    }


    if( hr == S_OK && gpdToPrintschema[ index ].stapleAngle == value  )
    {
        //
        // Found the Staple feature node entirely in input JT, now remove it from JT        
        //

        hr = pJth->DeleteFeatureNode( NULL,pStapleFeatureOld );
    }
    
    //
    // Make sure that you release all Interface pointers when you no longer need them
    //
    if( pStapleFeatureOld )
    {
        pStapleFeatureOld->Release();
    }
    if( pStapleOptionOld )
    {
        pStapleOptionOld->Release();
    }
    if( pStaplePropertyOld )
    {
        pStaplePropertyOld->Release();
    }
    

    return hr;

}//End function




/*++

Routine Name:
    ReadAndDeleteGPDStapleFeatureFromDevcaps

Routine Description:
    Helper function to read the setting and delete Staple Feature that has been defined according to GPD
    definition from the input Device capabilities document. Reads all the options that have been set by
    Unidrv for Staple Feature in the input device capabilities document alongwith their constrain 
    information if any. Passes this information to the caller

Arguments:
   pJth - Pointer to input Devcaps handler
   stapleIndexArray - Array of Integer indexs to remember the what subset of options
                        is present in input Devcaps
   stapleConstrainArray - Array of BSTRs specifying constrain information for each option
                            set by Unidrv

Return Value:
    HRESULT
    S_OK - On Successfully finding the Staple Feature Node in Devcaps
    S_FALSE - If the Staple Feature node is not found in Devcaps
    E_* - On failure


--*/


HRESULT 
TOEMJTProvider::ReadAndDeleteGPDStapleFeatureFromDevCaps(
    IN OUT ihvjthandler::JobTicketHandler * pJth,
    IN OUT INT stapleIndexArray[], // can be NULL
    IN OUT BSTR stapleConstrainArray[]
    )
{

    HRESULT hr = S_OK;

    IXMLDOMElement * pStapleFeatureOld = NULL;
    IXMLDOMElement * pStapleOptionOld = NULL;
    BOOL bFound = FALSE;
    

    //
    //First examine the Staple Feature nod ein input JT that has been created by Unidrv 
    // based on the information about Staple Feature available in the GPD file
    // check what setting Unidrv has put
    // then remove the Staple Feature node that is created by Unidrv entirely from Job Ticket
    // and add Staple feature node under public printschema
    //

    if( !pJth )
    {
        return E_INVALIDARG;
    }

    hr = pJth->GetFeatureNode(NULL,printschema::PLUGIN_NAMESPACE_URI,
                              gpd::staple::FEATURE_NAME,
                              &pStapleFeatureOld);
    

    //  
    // IMPORTANT: check for hr == S_OK and not SUCCEEDED(hr) because GetFeatureNode 
    // returns S_FALSE if feature is not found
    //
    if( hr == S_OK && pStapleFeatureOld )
    {
                        
                //
                // Check if any of the Staple Options that are common between GPD and Printschema
                // are present in the input Devcaps document. If yes, then only we convert the
                // Staple feature node in input Devcaps to public printschema
                //
                
                
                INT index = 0;

                for(INT i=0; i< STAPLE_OPTIONS_COUNT_GPD; i++)
                {
                    //
                    // Get the option node alongwith constrain information if any
                    //
                    hr = pJth->GetOptionNode( pStapleFeatureOld,
                                              printschema::PLUGIN_NAMESPACE_URI,
                                              gpdToPrintschema[i].gpdOptionName,
                                              &stapleConstrainArray[i], 
                                              &pStapleOptionOld );
                
                    if( hr == S_OK && pStapleOptionOld )
                    {                       
                        if( stapleIndexArray )
                        {
                            //
                            // Remember and return the setting made by Unidrv
                            //
                            stapleIndexArray[index] = i;

                            index++;

                        }                       
                    }
                    bFound = TRUE;

                }//End for
    }

    if( hr == S_OK )        
    {
        //
        // Found the Staple feature node entirely in input DC, now remove it entirely       
        //
        if( bFound )
        {
            hr = pJth->DeleteFeatureNode(NULL,pStapleFeatureOld);
        }
        else
        {
            hr = S_FALSE;
        }
    }   
    
    
    //
    // Make sure that you release all Interface pointers when you no longer need them
    //
    if(pStapleFeatureOld)
    {
        pStapleFeatureOld->Release();
    }
    if(pStapleOptionOld)
    {
        pStapleOptionOld->Release();
    }   

    return hr;

}//End function







/*++

Routine Name:
    AddPrintschemaStapleFeatureToJT

Routine Description:
    Helper function to add Staple Feature according to Printschema definition to the input Job Ticket

Arguments:
   pJth - Pointer to input Job Ticket handler

Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/


HRESULT 
TOEMJTProvider::AddPrintschemaStapleFeatureToJT(
    IN OUT ihvjthandler::JobTicketHandler * pJth,
    IN INT stapleIndex
    )
{
    HRESULT hr = S_OK;

    IXMLDOMElement * pStapleFeature = NULL;
    IXMLDOMElement * pStapleOption = NULL;

    
    if( !pJth  )
    {
        return E_INVALIDARG;
    }
    
    hr = pJth->CreateFeatureNode(NULL,printschema::PRINTSCHEMA_URI,printschema::staple::STAPLE_FEATURE,&pStapleFeature);        

    if(SUCCEEDED(hr))
    {
    
    
                        //
                        //  Add the folowing to input DOM tree:
                        //      <jt:Feature name="prn:Staple">
                        //              <jt:Option name="prn:TopLeft">
                        //                  <jt:ScoredProperty name="prn:Angle">
                        //                      <jt:Value xsi:type="xsi:Integer">45</jt:Value>
                        //                  </jt:ScoreProperty>
                        //              </jt:Option>
                        //      </jt:Feature>
                        //

            hr  = pJth->CreateOptionNode( pStapleFeature,
                                          printschema::PRINTSCHEMA_URI,
                                          gpdToPrintschema[stapleIndex].printschemaOptionName,
                                          &pStapleOption);

            if( SUCCEEDED(hr) && pStapleOption)
            {               
                    hr  = pJth->CreatePropertyNode(pStapleOption,
                                                   printschema::PRINTSCHEMA_URI,
                                                   printschema::staple::STAPLE_ANGLE_SCORED_PROPERTY,
                                                   printschema::XSI_URI,printschema::DATATYPE_INTEGER,
                                                   gpdToPrintschema[stapleIndex].stapleAngle,
                                                   TRUE,
                                                   NULL);
            }                       

    }
    
    //
    // Make sure that you release all Interface pointers when you no longer need them
    //
    if( pStapleFeature )
    {
        pStapleFeature->Release();
    }
    if( pStapleOption )
    {
        pStapleOption->Release();
    }   

    return hr;

}//End function



/*++

Routine Name:
    AddGPDStapleFeatureToJT

Routine Description:
    Helper function to add Staple Feature according to GPD definition to the input Job Ticket    

Arguments:
   pJth - Pointer to input Job Ticket handler

Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/

HRESULT 
TOEMJTProvider::AddGPDStapleFeatureToJT(
    IN OUT ihvjthandler::JobTicketHandler * pJth,
    IN INT stapleIndex
    )
{
    HRESULT hr = S_OK;

    IXMLDOMElement * pStapleFeature = NULL;
    IXMLDOMElement * pStapleOption = NULL;

    if( !pJth )
    {
        return E_INVALIDARG;
    }

                        //
                        //  Add the folowing to input DOM tree:
                        //      <jt:Feature name="plg:Stapling">
                        //              <jt:Option name="plg:_1parallel">                       
                        //              </jt:Option>
                        //      </jt:Feature>
                        //


    hr = pJth->CreateFeatureNode(NULL,printschema::PLUGIN_NAMESPACE_URI,gpd::staple::FEATURE_NAME,&pStapleFeature);
    
    
    if(SUCCEEDED(hr))
    {       
        hr  = pJth->CreateOptionNode(pStapleFeature,
                                     printschema::PLUGIN_NAMESPACE_URI,
                                     gpdToPrintschema[stapleIndex].gpdOptionName,
                                     &pStapleOption);              

    }//End if hr succeeded
    
    //
    // Make sure that you release all Interface pointers when you no longer need them
    //
    if( pStapleFeature )
    {
        pStapleFeature->Release();
    }
    if( pStapleOption )
    {
        pStapleOption->Release();
    }

    return hr;

}//End function



/*++

Routine Name:
    AddPrintschemaStapleFeatureToDevCaps

Routine Description:
    Helper function to add Staple Feature according to Printschema definition to the input Job Ticket
    Adds the subset of options specified in input Device capabilities document passed on by Unidrv
    Also adds the constrain information for each option if any set by Unidrv    

Arguments:
   pJth - Pointer to input Job Ticket handler
   stapleIndexArray - Array of Integer indexs to specify what subset of options
                        is present in input Devcaps
   stapleConstrainArray - Array of BSTRs specifying constrain information for each option
                            set by Unidrv
Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/
HRESULT 
TOEMJTProvider::AddPrintschemaStapleFeatureToDevCaps(
    IN OUT ihvjthandler::JobTicketHandler * pJth,
    IN INT stapleIndexArray[],
    IN BSTR stapleConstrainArray[]
    )

{
    HRESULT hr = S_OK;

    IXMLDOMElement * pStapleFeature = NULL;
    IXMLDOMElement * pStapleOption = NULL;

    if( ! pJth  )
    {
        return E_INVALIDARG;
    }

    hr = pJth->CreateFeatureNode(NULL,printschema::PRINTSCHEMA_URI,printschema::staple::STAPLE_FEATURE,&pStapleFeature);



    if(SUCCEEDED(hr))
    {
        hr = pJth->CreatePropertyNode(pStapleFeature,
                                      printschema::PRINTSCHEMA_URI,
                                      printschema::staple::STAPLE_SELECTIONTYPE_PROPERTY,
                                      printschema::XSI_URI,printschema::DATATYPE_STRING,
                                      printschema::staple::STAPLE_SELECTIONTYPE_PROPERTY_VALUE,
                                      FALSE,
                                      NULL);
    }
    

    if(SUCCEEDED(hr))
    {
        //
        // Add only those options that were present in the input devcaps passed by Unidrv
        //

        BOOL bRepeat = FALSE;

        for(INT i=0; i< STAPLE_OPTIONS_COUNT_GPD && SUCCEEDED(hr); i++)
        {
            if( stapleIndexArray[i] != -1 )
            {
                //
                // Add the option node only if it is originally present in input Devcaps provided by Unidrv
                //
                if( gpdToPrintschema[i].printschemaOptionName != NULL )
                {
                    //
                    // If it is a GPD option that CAN be mapped to a Printschema Option....
                    // we add it under printschema namespace and according to printschema format
                    //
                        if( wcscmp( gpdToPrintschema[i].printschemaOptionName, printschema::staple::STAPLE_LOCATION_TOP_LEFT ) == 0 )
                        {
                            if( bRepeat == TRUE )
                            {
                                continue;                       
                            }
                            else
                            {
                                bRepeat = TRUE;
                            }
                        }
                        hr = pJth->CreateOptionNode(pStapleFeature,
                                                    printschema::PRINTSCHEMA_URI,
                                                    gpdToPrintschema[i].printschemaOptionName,
                                                    printschema::PRINTSCHEMA_URI,
                                                    stapleConstrainArray[i],
                                                    &pStapleOption);

                        if(SUCCEEDED(hr))
                        {
                            if( wcscmp( gpdToPrintschema[i].printschemaOptionName, printschema::staple::STAPLE_LOCATION_NONE ) == 0 )
                            {
                                hr = pJth->CreatePropertyNode(pStapleOption,
                                                              printschema::PRINTSCHEMA_URI,
                                                              printschema::IDENTITY_PROPERTY ,
                                                              printschema::XSI_URI,
                                                              printschema::DATATYPE_STRING,
                                                              L"True",
                                                              FALSE,
                                                              NULL);
                            }
                        }

                        if(SUCCEEDED(hr))
                        {           
                            hr = pJth->CreatePropertyNode(pStapleOption,
                                                            printschema::PRINTSCHEMA_URI,
                                                            printschema::staple::STAPLE_ANGLE_SCORED_PROPERTY,
                                                            printschema::XSI_URI,printschema::DATATYPE_INTEGER,
                                                            printschema::staple::STAPLE_ANGLE_VALUE_DEFAULT,
                                                            TRUE,
                                                            NULL);
                        }
                }
                else
                {
                    //
                    // If it is a GPD option that CANNOT be mapped to ANY Printschema Option....
                    // We keep it the way Unidrv had put it in the original Devcaps, under plug-in private namespace
                    //
                    hr  = pJth->CreateOptionNode(pStapleFeature,
                                                 printschema::PLUGIN_NAMESPACE_URI,
                                                 gpdToPrintschema[i].gpdOptionName,
                                                 printschema::PRINTSCHEMA_URI,
                                                 stapleConstrainArray[i], 
                                                 &pStapleOption);              
                    
                    if( SUCCEEDED(hr) )
                    {
                        hr = pJth->CreatePropertyNode(pStapleOption,
                                                      printschema::PRINTSCHEMA_URI,
                                                      printschema::DISPLAYNAME_PROPERTY ,
                                                      NULL ,
                                                      NULL,
                                                      gpdToPrintschema[i].gpdDisplayName,
                                                      FALSE,
                                                      NULL);
                    }
                }

            }

        }//End for
    }   

    //
    // Make sure that you release all Interface pointers when you no longer need them
    //
    if( pStapleFeature )
    {
        pStapleFeature->Release();
    }
    if( pStapleOption )
    {
        pStapleOption->Release();
    }


    return hr;


}//End function





/*++

Routine Name:
    PerformSmartNup

Routine Description:
    Helper function to perform Smart Nup functionality. The routine is called as part of Validate Job Ticket.
    It looks if Nup Feature is enabled in the current Job Tciket. If it is and if Nup setting is either 2
    or 6 then it makes changes to the settign of Stapling feature. For eg if Nup is 2/6 and if current option
    set for Stapling feature is "TopLeft" it will change it to "TopRight" to make it appropriate with respect to
    current Nup setting.
    This routine thus demonstrates an example of how plug-in can read the private setting made by Unidrv through
    Job Ticket and make use of them to modify its own settings.

Arguments:
   pJth - Pointer to input Job Ticket handler
   
Return Value:
    HRESULT
    S_OK - On Success
    E_* - On failure

--*/
HRESULT 
TOEMJTProvider::PerformSmartNup(
    IN OUT ihvjthandler::JobTicketHandler * pJth
    )
{

    HRESULT hr = S_OK;
    HRESULT hrtemp = S_OK;  

    IXMLDOMElement * pNupFeature = NULL;
    IXMLDOMElement * pNupOption = NULL;
    IXMLDOMElement * pNupProperty = NULL;
    IXMLDOMElement * pStapleFeature = NULL;
    IXMLDOMElement * pStapleOption = NULL;

    INT value = 0;
    BOOL bIsNupOn = FALSE;
    BOOL bNupFound = FALSE;


    if( ! pJth  )
    {
        return E_INVALIDARG;
    }

    //
    // First see if Nup Feature exists in the current Job Ticket
    //
    hr = pJth->GetFeatureNode( NULL,printschema::PRINTSCHEMA_URI,printschema::nup::NUP_FEATURE,&pNupFeature );
        

    if( hr == S_OK && pNupFeature )
    {
        bNupFound = TRUE;

        hr = pJth->GetOptionNode( pNupFeature,&pNupOption );
    }
    else
    {
        //
        // Nup feature is not present in JT, 
        //
        bNupFound = FALSE;
    }

    if( hr == S_OK && pNupOption )
    {
        hr = pJth->GetPropertyNode( pNupOption,
                                    printschema::PRINTSCHEMA_URI,
                                    printschema::nup::NUP_PAGES_PER_SHEET_SCORED_PROPERTY,
                                    TRUE,
                                    &pNupProperty ); 
    }

    if( hr == S_OK && pNupProperty )
    {
        //
        // Get Currently set Nup value
        //
        hr = pJth->GetValueAsInt( pNupProperty, &value, NULL );
    }

    if( hr == S_OK )
    {
        //
        // Now check whether the current nup setting is of our interest ie 2 or 6
        //
        bIsNupOn = FALSE;

        for( INT i = 0; i < NUP_OPTIONS_COUNT; i++ )
        {
            if( value == nupValues[i] )
            {
                bIsNupOn = TRUE;

                break;
            }
        }//End for                      
    }

    if( hr == S_OK && bIsNupOn )
    {
            //
            //Nup feature has value of out interest, so change the StapleLocation Property in Base ticket       
            //
        hr = pJth->GetFeatureNode( NULL,
                                   printschema::PRINTSCHEMA_URI,
                                   printschema::staple::STAPLE_FEATURE,
                                   &pStapleFeature );

        if( hr == S_OK && pStapleFeature)
        {   
            //
            //If staple feature exists in delta ticket
            //
            BOOL bFound = FALSE;            

            for( INT i=0; i< STAPLE_OPTIONS_COUNT_COMMON && !bFound; i++ )
            {
                hr = pJth->GetOptionNode( pStapleFeature,
                                          printschema::PRINTSCHEMA_URI,
                                          gpdToPrintschema[i].printschemaOptionName,
                                          &pStapleOption);
                
                if( hr == S_OK && pStapleOption )
                {                   
                    hr = pJth->ChangeOption( gpdToPrintschema[i].alternateOptionNameForSmartNup, pStapleOption );   
                    
                    bFound = TRUE;

                }//End if
            }//End for                  
        }//End if
    }//End if Nup is On


    if( pNupFeature )
    {
        pNupFeature->Release();
    }
    if( pNupOption )
    {
        pNupOption->Release();
    }
    if( pNupProperty )
    {
        pNupProperty->Release();
    }

    if( pStapleFeature )
    {
        pNupFeature->Release();
    }
    if( pStapleOption )
    {
        pNupOption->Release();  
    }
    
    //
    // Nup feature is not present in JT, this is not an error
    //
    if( bNupFound == FALSE )
    {
        hr = S_OK;
    }

    return hr;



}//End function




