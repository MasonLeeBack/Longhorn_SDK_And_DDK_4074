

//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1998 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:   printschema.hxx
//    
//
//  PURPOSE:  Constant definitions for print schema names.
//
//  




typedef 
enum tagPrintschemaVersion
{
    PRINTSCHEMA_VERSION_NUMBER =  1
}EPrintschemaVersion;


namespace printschema
{
 
    const LPWSTR JOBTICKET_URI = 
        L"http://schemas.microsoft.com/windows/2003/08/printing/printschemaframework";
  
    const LPWSTR PRINTSCHEMA_URI = 
        L"http://schemas.microsoft.com/windows/2003/08/printing/printschemakeywords";

    //
    // XSI and XSD URIs defined by W3C
    //
    const LPWSTR XSI_URI = L"http://www.w3.org/2001/XMLSchema-instance";

    const LPWSTR XSD_URI = L"http://www.w3.org/2001/XMLSchema";

    //
    // Plug-in private namespace URI
    //
    const LPWSTR PLUGIN_NAMESPACE_URI = L"http://schemas.microsoft.com/printing/2003/08/sampleplugin";



    //
    // Some shared / common constants
    //
    const LPWSTR IDENTITY_PROPERTY = L"IdentityOption";
    const LPWSTR DISPLAYNAME_PROPERTY = L"DisplayName";

    const LPWSTR PARAM_PROP_NEEDED = L"WhenNeeded";
    const LPWSTR PARAM_NEEDED_ALWAYS = L"Always";
    const LPWSTR PARAM_NEEDED_SELECTED_OPTION = L"SelectedOption";

    const LPWSTR PARAM_MAX_VALUE = L"MaxValue";
    const LPWSTR PARAM_MIN_VALUE = L"MinValue";
    const LPWSTR PARAM_DEFAULT = L"DefaultValue";
    const LPWSTR PARAM_MULTIPLE = L"Multiple";
    const LPWSTR PARAM_REQUIRED = L"Mandatory";
    const LPWSTR PARAM_REQUIRED_YES = L"Mandatory";
    const LPWSTR PARAM_REQUIRED_COND = L"Conditional";
    const LPWSTR PARAM_REQUIRED_NO = L"Optional";
    const LPWSTR PARAM_DATATYPE = L"DataType";

    //
    // XSI datatypes
    //

    const LPWSTR DATATYPE_INTEGER = L"integer";
    const LPWSTR DATATYPE_STRING = L"string";
    


    //
    // Element types defined in Printschema
    //

    const LPWSTR JOBTICKET_ELEMENT_NAME = L"JobTicket";
    const LPWSTR DEVCAPS_ELEMENT_NAME = L"DeviceCapabilities";

    const LPWSTR FEATURE_ELEMENT_NAME = L"Feature";

    const LPWSTR OPTION_ELEMENT_NAME = L"Option";

    const LPWSTR ATTRIBUTE_ELEMENT_NAME = L"Attribute";
    const LPWSTR ATTRIBUTE_SET_ELEMENT_NAME = L"AttributeSet";

    const LPWSTR SCORED_PROPERTY_ELEMENT_NAME = L"ScoredProperty";
    const LPWSTR PROPERTY_ELEMENT_NAME = L"Property";

    const LPWSTR NAME_ATTRIBUTE_NAME = L"name";
    const LPWSTR CONSTRAINED_ATTRIBUTE_NAME = L"constrained";
    const LPWSTR VALUE_ELEMENT_NAME = L"Value";

    const LPWSTR PARAMETER_ELEMENT_NAME = L"Parameter";
    const LPWSTR PARAMETER_INITIALIZER_ELEMENT_NAME = L"ParameterInit";
    const LPWSTR PARAMETER_REFERENCE_ELEMENT = L"ParameterReference";


    const LPWSTR CONSTRAIN_NONE = L"None";
    //
    // Printschema definition of Stapling Feature
    //
    namespace staple
    {

        const LPWSTR STAPLE_FEATURE_GPD_NAME = L"Stapling";
        const LPWSTR STAPLE_FEATURE = L"JobStaple";
        const LPWSTR STAPLE_ANGLE_SCORED_PROPERTY = L"Angle";
        const LPWSTR STAPLE_LOCATION_TOP_LEFT = L"StapleTopLeft";
        const LPWSTR STAPLE_LOCATION_BOTTOM_LEFT = L"StapleBottomLeft";
        const LPWSTR STAPLE_LOCATION_TOP_RIGHT = L"StapleTopRight";
        const LPWSTR STAPLE_LOCATION_BOTTOM_RIGHT = L"StapleBottomRight";
        const LPWSTR STAPLE_LOCATION_DUAL_TOP = L"StapleDualTop";
        const LPWSTR STAPLE_LOCATION_DUAL_BOTTOM = L"StapleDualBottom";
        const LPWSTR STAPLE_LOCATION_DUAL_LEFT = L"StapleDualLeft";
        const LPWSTR STAPLE_LOCATION_DUAL_RIGHT = L"StapleDualRight";
        const LPWSTR STAPLE_LOCATION_NONE = L"None";
        const LPWSTR STAPLE_SELECTIONTYPE_PROPERTY = L"SelectionType";
        const LPWSTR STAPLE_SELECTIONTYPE_PROPERTY_VALUE = L"PickOne";
        
        //
        //Default settings
        //

        const LPWSTR STAPLE_LOCATION_DEFAULT = L"StapleTopLeft";
        const INT STAPLE_ANGLE_VALUE_DEFAULT = 0;
        
    }

    //
    // Printschema definition of NUp Feature
    //
    namespace nup
    {
        const LPWSTR NUP_FEATURE = L"DocumentNUp";
        const LPWSTR NUP_PAGES_PER_SHEET_SCORED_PROPERTY = L"PagesPerSheet";
    }

}


