/***
*strlwr.c - routine to map upper-case characters in a string to lower-case
*
*       Copyright (c) 1985-2001, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Converts all the upper case characters in a string to lower case,
*       in place.
*
*******************************************************************************/

#include <cruntime.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <setlocal.h>
#include <limits.h>     /* for INT_MAX */
#include <mtdll.h>
#include <awint.h>
#include <dbgint.h>

/***
*char *_strlwr(string) - map upper-case characters in a string to lower-case
*
*Purpose:
*       _strlwr() converts upper-case characters in a null-terminated string
*       to their lower-case equivalents.  Conversion is done in place and
*       characters other than upper-case letters are not modified.
*
*       In the C locale, this function modifies only 7-bit ASCII characters
*       in the range 0x41 through 0x5A ('A' through 'Z').
*
*       If the locale is not the 'C' locale, LCMapString() is used to do
*       the work.  Assumes enough space in the string to hold result.
*
*Entry:
*       char *string - string to change to lower case
*
*Exit:
*       input string address
*
*Exceptions:
*       The original string is returned unchanged on any error.
*
*******************************************************************************/

char * __cdecl _strlwr (
        char * string
        )
{

    int dstlen;                 /* len of dst string, with null  */
    unsigned char *dst;         /* destination string */
    int malloc_flag = 0;
#ifdef _MT
    _ptiddata ptd = _getptd();
    pthreadlocinfo ptloci = ptd->ptlocinfo;

    __UPDATE_LOCALE(ptd, ptloci);
#endif  /* _MT */
    if ( __LC_HANDLE(ptloci)[LC_CTYPE] == _CLOCALEHANDLE ) {
        char *cp;       /* traverses string for C locale conversion */

        for ( cp = string ; *cp ; ++cp )
            if ( ('A' <= *cp) && (*cp <= 'Z') )
                *cp -= 'A' - 'a';

        return(string);
    }   /* C locale */

    /* Inquire size of dst string */
    if ( 0 == (dstlen = __crtLCMapStringA( __LC_HANDLE(ptloci)[LC_CTYPE],
                                           LCMAP_LOWERCASE,
                                           string,
                                           -1,
                                           NULL,
                                           0,
                                           __LC_CODEPAGE(ptloci),
                                           TRUE )) )
        return(string);

    /* Allocate space for dst */
    __try {
        dst = (unsigned char *)_alloca(dstlen * sizeof(unsigned char));
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        _resetstkoflw();
        dst = NULL;
    }

    if ( dst == NULL ) {
        dst = (unsigned char *)_malloc_crt(dstlen * sizeof(unsigned char));
        malloc_flag++;
    }

    /* Map src string to dst string in alternate case */
    if ( (dst != NULL) && (__crtLCMapStringA( __LC_HANDLE(ptloci)[LC_CTYPE],
                                             LCMAP_LOWERCASE,
                                             string,
                                             -1,
                                             dst,
                                             dstlen,
                                             __LC_CODEPAGE(ptloci),
                                             TRUE ) != 0) )
        /* copy dst string to return string */
        strcpy(string, dst);

    if ( malloc_flag )
        _free_crt(dst);

    return(string);

}
