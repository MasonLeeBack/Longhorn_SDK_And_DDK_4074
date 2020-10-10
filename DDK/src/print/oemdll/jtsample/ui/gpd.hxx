//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright  1998 - 2003  Microsoft Corporation.  All Rights Reserved.
//
//  FILE:   gpd.hxx
//    
//
//  PURPOSE:  Constant definitions for GPD names.
//
//  




#ifndef GPD_HXX_
#define GPD_HXX_


//
//Define GPD definitions of staple feature
//

namespace gpd
{

    namespace staple
    {
        const LPWSTR FEATURE_NAME = L"Stapling";

        //
        // 7 GPD options corresponding to Staple Feature
        //
        const LPWSTR OPTION_NONE = L"Option1";
        const LPWSTR OPTION_ONE_PARALLEL = L"_1parallel";
        const LPWSTR OPTION_ONE_DIAGONAL = L"_1diagonal";
        const LPWSTR OPTION_TWO_PARALLEL = L"_2parallel";
        
        const LPWSTR OPTION_THREE_PARALLEL = L"_3parallel";
        const LPWSTR OPTION_STITCHING = L"Stitching";
        const LPWSTR OPTION_CUSTOM = L"Custom";

        //
        // Display names for the 7 options
        //
        const LPWSTR VALUE_NONE = L"None";
        const LPWSTR VALUE_ONE_PARALLEL = L"One Staple";
        const LPWSTR VALUE_ONE_DIAGONAL = L"One Staple Angled";
        const LPWSTR VALUE_TWO_PARALLEL = L"Two Staples";
        
        const LPWSTR VALUE_THREE_PARALLEL = L"Three Staples";
        const LPWSTR VALUE_STITCHING = L"Six Staples";
        const LPWSTR VALUE_CUSTOM = L"Custom";        
        

    }

}
#endif
