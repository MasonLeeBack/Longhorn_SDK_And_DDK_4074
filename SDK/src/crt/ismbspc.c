/***
*ismbspc.c - Test is character is whitespace (MBCS)
*
*       Copyright (c) 1985-2001, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Test is character is whitespace (MBCS)
*
*******************************************************************************/

#ifdef _MBCS

#include <windows.h>
#include <awint.h>

#include <mtdll.h>
#include <cruntime.h>
#include <ctype.h>
#include <mbdata.h>
#include <mbctype.h>
#include <mbstring.h>


/***
* _ismbcspace - Test is character is whitespace (MBCS)
*
*Purpose:
*       Test if the character is a whitespace character.
*       Handles MBCS chars correctly.
*
*       Note:  Use test against 0x00FF instead of _ISLEADBYTE
*       to ensure that we don't call SBCS routine with a two-byte
*       value.
*
*Entry:
*       unsigned int c = character to test
*
*Exit:
*       Returns TRUE if character is whitespace, else FALSE
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _ismbcspace(
        unsigned int c
        )
{
        if (c > 0x00FF)
        {


            char buf[2];
            unsigned short ctype[2] = {0};

#ifdef _MT
            pthreadmbcinfo ptmbci = _getptd()->ptmbcinfo;

            if ( ptmbci != __ptmbcinfo )
                ptmbci = __updatetmbcinfo();
#endif  /* _MT */

            buf[0] = (c >> 8) & 0xFF;
            buf[1] = c & 0xFF;

            /* return FALSE if not in supported MB code page */
#ifdef _MT
            if ( _ISNOTMBCP_MT(ptmbci) )
#else  /* _MT */
            if ( _ISNOTMBCP )
#endif  /* _MT */
                return 0;

            /*
             * Since 'c' could be two one-byte MB chars, we need room in the
             * ctype return array to handle this. In this case, the
             * second word in the return array will be non-zero.
             */

            if ( __crtGetStringTypeA( CT_CTYPE1,
                                      buf,
                                      2,
                                      ctype,
#ifdef _MT
                                      ptmbci->mbcodepage,
                                      ptmbci->mblcid,
#else  /* _MT */
                                      __mbcodepage,
                                      __mblcid,
#endif  /* _MT */
                                      TRUE ) == 0 )
                return 0;

            /* ensure single MB character and test for type */
            return (ctype[1] == 0 && ctype[0] & (_SPACE));


        } else

            return isspace(c);
}

#endif  /* _MBCS */
