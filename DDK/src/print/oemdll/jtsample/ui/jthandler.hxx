//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1998 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:   jthandler.hxx
//    
//
//  PURPOSE:  Helper Class that handles all functionality related to processing of input 
//              Job Ticket/Devcaps XML document
//
//  




/*++

Copyright (c) 1996-2003 Microsoft Corporation
All rights reserved.

Module Name:

    jthandler.hxx

Abstract:
    
    Helper Class that handles all functionality related to processing of input 
    Job Ticket/Devcaps XML document

Author:

    Madhura Sharangpani (t-madsha) 16-Aug-2003

--*/




#ifndef JTHANDLER_H_
#define JTHANDLER_H_



#include "prcomoem.h"


//
// Job ticket handler class that performs all XML handling for the sample code
//

namespace ihvjthandler
{
class JobTicketHandler
{       
    public:
        JobTicketHandler();
        virtual ~JobTicketHandler();
        
        //
        //basic methods
        //

        HRESULT CreateRoot(BOOL bIsDocFromFile);
        
        HRESULT SetRoot(
            IN IXMLDOMDocument2 *pRoot,
            IN IPrintJobTicketPluginHelperUI * m_pCoreDriverJTHelp
            );

        HRESULT GetRoot(OUT IXMLDOMDocument2 **ppRoot);     
        
        HRESULT LoadXML(char *xmlFileName);
        
        HRESULT GetXML(OUT BSTR *xml);      
                
        //
        //Node creation methods     
        //
        
        
        HRESULT CreateFeatureNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszNamespaceURI,
            IN LPTSTR pszFeatureName,
            OUT IXMLDOMElement **ppFeatureNode OPTIONAL
            );

        HRESULT CreateOptionNode(
            IN IXMLDOMElement *pParent,
            OUT IXMLDOMElement **ppOptionElement OPTIONAL
            );

        HRESULT CreateOptionNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszNamespaceURI,
            IN LPTSTR pszOptionName,
            OUT IXMLDOMElement **ppOptionElement OPTIONAL
            );

        HRESULT CreateOptionNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszNamespaceURI, //print schema URI that corresponds to prefix "prn:"
            IN LPTSTR pszOptionName, // name attribute, "TopLeft" etc
            IN LPTSTR pszConstrainNamespaceURI, //print schema URI that corresponds to prefix "prn:" etc
            IN LPTSTR pszConstrainName, //constrained attribute "none" etc
            OUT IXMLDOMElement **ppOptionElement OPTIONAL
            );

        HRESULT CreatePropertyNode(
            IN IXMLDOMElement *pTargetContext, 
            OPTIONAL IN LPTSTR pszUri, 
            IN LPTSTR pszName,
            IN LPTSTR pszValueAttrUri,
            IN LPTSTR pszValueAttrName,
            IN DOUBLE value,
            IN BOOL isScored,
            OUT IXMLDOMElement **ppPropertyNode OPTIONAL
            );

        HRESULT CreatePropertyNode(
            IN IXMLDOMElement *pTargetContext, 
            OPTIONAL IN LPTSTR pszUri,
            IN LPTSTR pszName,
            IN LPTSTR pszValueAttrUri,
            IN LPTSTR pszValueAttrName,
            IN INT value,
            IN BOOL isScored,
            OUT IXMLDOMElement **ppPropertyNode OPTIONAL
            );

        HRESULT CreatePropertyNode(
            IN IXMLDOMElement *pTargetContext, 
            OPTIONAL IN LPTSTR pszUri,
            IN LPTSTR pszName,
            IN LPTSTR pszValueUri,
            IN LPTSTR pszValueName,
            IN LPTSTR pszValueAttrUri,
            IN LPTSTR pszValueAttrName,
            IN BOOL isScored,
            OUT IXMLDOMElement **ppPropertyNode OPTIONAL
            );

        HRESULT CreatePropertyNode(
            IN IXMLDOMElement *pTargetContext, 
            OPTIONAL IN LPTSTR pszUri,
            IN LPTSTR pszName,
            IN LPTSTR pszValueAttrUri,
            IN LPTSTR pszValueAttrName,
            IN LPTSTR pszValue, OPTIONAL 
            IN BOOL isScored,
            OUT IXMLDOMElement **ppPropertyNode OPTIONAL
            );

        HRESULT CreateValueNode(
            IN IXMLDOMElement *pTargetContext,
            IN LPTSTR pszValueAttrUri,
            IN LPTSTR pszValueAttrName,
            IN INT value,
            OUT IXMLDOMElement **ppValueElement OPTIONAL
            );

        HRESULT CreateValueNode(
            IN IXMLDOMElement *pTargetContext,
            IN LPTSTR pszValueAttrUri,
            IN LPTSTR pszValueAttrName,
            IN LPTSTR pszValue,OPTIONAL 
            OUT IXMLDOMElement **ppValueElement OPTIONAL
            );

        //
        //Get methods
        //
        HRESULT GetXMLElement(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszElementNamespaceURI,
            IN LPTSTR pszElementName, 
            IN LPTSTR pszAttrNamespaceURI, 
            IN LPTSTR pszAttrName, 
            OUT BSTR * ppConstrainName, //can be NULL
            OUT IXMLDOMElement **ppElement
            );

        HRESULT GetXMLElementWithoutAttribute(
            IN IXMLDOMElement *pContext,
            IN LPTSTR pszElementNamespaceURI,
            IN LPTSTR pszElementName,
            OUT IXMLDOMElement **ppChildElement
            );

        HRESULT GetXMLAttribute(
            IN IXMLDOMElement *pElement,
            OUT BSTR * pszAttrNamespaceURI, 
            OUT BSTR * pszAttrName
            );

        HRESULT GetXMLConstrain(
            IN IXMLDOMElement *pElement,
            OUT BSTR *ppAttrNamespaceURI, 
            OUT BSTR *ppAttrName
            );

        HRESULT GetFeatureNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszAttrNamespaceURI, 
            IN LPTSTR pszAttrName, 
            OUT IXMLDOMElement **ppElement
            );

        HRESULT GetOptionNode(
            IN IXMLDOMElement *pParent,
            OUT IXMLDOMElement **ppElement
            );      

        HRESULT GetOptionNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszAttrNamespaceURI, 
            IN LPTSTR pszAttrName, 
            OUT IXMLDOMElement **ppElement
            );      

        HRESULT GetOptionNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszAttrNamespaceURI, 
            IN LPTSTR pszAttrName, 
            OUT BSTR * ppConstrainName,
            OUT IXMLDOMElement **ppElement
            );

        HRESULT GetPropertyNode(
            IN IXMLDOMElement *pParent,
            IN LPTSTR pszAttrNamespaceURI, 
            IN LPTSTR pszAttrName, 
            BOOL bIsScored, 
            OUT IXMLDOMElement **ppElement
            );

        HRESULT GetValueAsBSTR(
            IN IXMLDOMElement *pContext, // Property, ScoredProperty, Attribute, or Parameter
            OUT BSTR *pbstrValue,
            OUT IXMLDOMElement **ppElement            
            );

        HRESULT GetValueAsInt(IN IXMLDOMElement *pContext, // Property, ScoredProperty, Attribute, or Parameter
            OUT INT *pValue,
            OUT IXMLDOMElement **ppElement
            );

        HRESULT GetValueAsQName(IN IXMLDOMElement *pContext, // Property, ScoredProperty, Attribute, or Parameter
            OUT BSTR *pValueUri,
            OUT BSTR *pValueLocalName,
            OUT IXMLDOMElement **ppElement
            );

        
        HRESULT ChangeOption(
            IN IXMLDOMElement * pNew,
            IN IXMLDOMElement *pOld
            );

        HRESULT ChangeOption(
            IN LPTSTR newOption,
            IN IXMLDOMElement *pOld
            );

        HRESULT ChangeValue(
            IN IXMLDOMElement * pNew,
            IN IXMLDOMElement *pOld
            );

        HRESULT ChangeValue(    
            IN INT newValue,
            IN IXMLDOMElement *pOld     
            );

        HRESULT ReplaceXMLElement(
            IN IXMLDOMElement * pParent,
            IN IXMLDOMElement * pNew,
            IN IXMLDOMElement *pOld,
            OUT IXMLDOMElement **ppOld
            );

        HRESULT DeleteFeatureNode(
            IN IXMLDOMNode * pParent,
            IN IXMLDOMNode * pElement
            );
        
        
    private:
        IXMLDOMDocument2 *m_pRootDocument;
        IXMLDOMElement * m_pRootElement;
        IMXNamespaceManager * m_pNSManager;

        HRESULT getPrefix(
            IN IXMLDOMElement *pContext,
            IN LPWSTR pszUri,
            OUT BSTR *pbstrPrefix OPTIONAL
            );

        HRESULT declarePrefix(
            IN IXMLDOMElement *pContext,
            IN LPWSTR pszUri,
            IN LPWSTR pszPreferredPrefix, 
            OUT BSTR*newPrefix
            );

        
        HRESULT CreateQName(
            IN IXMLDOMElement * pElement,
            LPTSTR pszUri, 
            LPTSTR pszLocalName, 
            BSTR * pQName 
            ); 
        
        //
        //adds attributes to existing XML element
        //
        HRESULT CreateXMLAttribute(
            IN IXMLDOMElement *pElement,
            IN LPTSTR pszAttributeName,
            IN LPTSTR pszNamespaceURI,
            IN LPTSTR pszAttributeValue,
            OUT IXMLDOMAttribute **ppAttribute OPTIONAL
            );

        //
        //Creates new XML element node
        //
        HRESULT CreateXMLElement(
            IN IXMLDOMElement *pParent, 
            IN BSTR pszElementName, 
            IN BSTR pszNamespaceURI,
            OUT IXMLDOMElement **ppElementz OPTIONAL
            );

        //
        //Helpers
        //
        HRESULT getLocalName(
            IN LPTSTR pszQName,
            OUT BSTR *ppbstrLocalName
            );

        HRESULT getUri(
            IXMLDOMElement *pContext,
            IN LPWSTR pszQName,
            OUT BSTR *pbstrURI
            );

        HRESULT DeleteNodeAndAllChildren(
            IN IXMLDOMNode * pParent,
            IN IXMLDOMNode * pElement
            );
        
}; // end class JobTicketHandler
}//End namespace ihvjthandler


#endif












