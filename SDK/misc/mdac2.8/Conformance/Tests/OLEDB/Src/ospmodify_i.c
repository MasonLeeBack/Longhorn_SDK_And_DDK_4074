/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jul 13 17:36:48 2000
 */
/* Compiler settings for OSPModify.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_OSPModify = {0x7C03852D,0x17C1,0x11d1,{0x95,0x03,0x00,0xC0,0x4F,0xB6,0x6A,0x50}};


const IID IID_IModifyDataSource = {0x7C03852E,0x17C1,0x11d1,{0x95,0x03,0x00,0xC0,0x4F,0xB6,0x6A,0x50}};


const IID IID_IModifyOSP = {0x7C03852F,0x17C1,0x11d1,{0x95,0x03,0x00,0xC0,0x4F,0xB6,0x6A,0x50}};


const CLSID CLSID_OSPModify = {0x7C03852C,0x17C1,0x11d1,{0x95,0x03,0x00,0xC0,0x4F,0xB6,0x6A,0x50}};


#ifdef __cplusplus
}
#endif

