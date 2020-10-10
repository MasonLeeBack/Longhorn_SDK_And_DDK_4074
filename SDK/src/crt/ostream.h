/***
*ostream.h - definitions/declarations for the ostream class
*
*       Copyright (c) 1991-2001, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       This file defines the classes, values, macros, and functions
*       used by the ostream class.
*       [AT&T C++]
*
*       [Public]
*
****/

#if _MSC_VER > 1000
#pragma once
#endif  /* _MSC_VER > 1000 */

#ifdef __cplusplus

#ifndef _INC_OSTREAM
#define _INC_OSTREAM

#if !defined (_WIN32)
#error ERROR: Only Win32 target supported!
#endif  /* !defined (_WIN32) */

#ifndef _CRTBLD
/* This version of the header files is NOT for user programs.
 * It is intended for use when building the C runtimes ONLY.
 * The version intended for public use will not have this message.
 */
#error ERROR: Use of C runtime library internal header file.
#endif  /* _CRTBLD */

#ifdef _MSC_VER
// Currently, all MS C compilers for Win32 platforms default to 8 byte
// alignment.
#pragma pack(push,8)

#include <useoldio.h>

#endif  /* _MSC_VER */

/* Define _CRTIMP */

#ifndef _CRTIMP
#ifdef CRTDLL
#define _CRTIMP __declspec(dllexport)
#else  /* CRTDLL */
#ifdef _DLL
#define _CRTIMP __declspec(dllimport)
#else  /* _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* CRTDLL */
#endif  /* _CRTIMP */

#ifndef _INTERNAL_IFSTRIP_
/* Define _CRTIMP1 */

#ifndef _CRTIMP1
#ifdef CRTDLL1
#define _CRTIMP1 __declspec(dllexport)
#else  /* CRTDLL1 */
#define _CRTIMP1 _CRTIMP
#endif  /* CRTDLL1 */
#endif  /* _CRTIMP1 */
#endif  /* _INTERNAL_IFSTRIP_ */

#include <ios.h>

#ifdef _MSC_VER
// C4514: "unreferenced inline function has been removed"
#pragma warning(disable:4514) // disable C4514 warning
// #pragma warning(default:4514)        // use this to reenable, if desired
#endif  /* _MSC_VER */

typedef long streamoff, streampos;

class _CRTIMP1 ostream : virtual public ios {

public:
        ostream(streambuf*);
        virtual ~ostream();

        ostream& flush();
        int  opfx();
        void osfx();

inline  ostream& operator<<(ostream& (__cdecl * _f)(ostream&));
inline  ostream& operator<<(ios& (__cdecl * _f)(ios&));
        ostream& operator<<(const char *);
inline  ostream& operator<<(const unsigned char *);
inline  ostream& operator<<(const signed char *);
inline  ostream& operator<<(char);
        ostream& operator<<(unsigned char);
inline  ostream& operator<<(signed char);
        ostream& operator<<(short);
        ostream& operator<<(unsigned short);
        ostream& operator<<(int);
        ostream& operator<<(unsigned int);
        ostream& operator<<(long);
        ostream& operator<<(unsigned long);
inline  ostream& operator<<(float);
        ostream& operator<<(double);
        ostream& operator<<(long double);
        ostream& operator<<(const void *);
        ostream& operator<<(streambuf*);
inline  ostream& put(char);
        ostream& put(unsigned char);
inline  ostream& put(signed char);
        ostream& write(const char *,int);
inline  ostream& write(const unsigned char *,int);
inline  ostream& write(const signed char *,int);
        ostream& seekp(streampos);
        ostream& seekp(streamoff,ios::seek_dir);
        streampos tellp();

protected:
        ostream();
        ostream(const ostream&);        // treat as private
        ostream& operator=(streambuf*); // treat as private
        ostream& operator=(const ostream& _os) {return operator=(_os.rdbuf()); }
        int do_opfx(int);               // not used
        void do_osfx();                 // not used

private:
        ostream(ios&);
        ostream& writepad(const char *, const char *);
        int x_floatused;
};

inline ostream& ostream::operator<<(ostream& (__cdecl * _f)(ostream&)) { (*_f)(*this); return *this; }
inline ostream& ostream::operator<<(ios& (__cdecl * _f)(ios& )) { (*_f)(*this); return *this; }

inline  ostream& ostream::operator<<(char _c) { return operator<<((unsigned char) _c); }
inline  ostream& ostream::operator<<(signed char _c) { return operator<<((unsigned char) _c); }

inline  ostream& ostream::operator<<(const unsigned char * _s) { return operator<<((const char *) _s); }
inline  ostream& ostream::operator<<(const signed char * _s) { return operator<<((const char *) _s); }

inline  ostream& ostream::operator<<(float _f) { x_floatused = 1; return operator<<((double) _f); }

inline  ostream& ostream::put(char _c) { return put((unsigned char) _c); }
inline  ostream& ostream::put(signed char _c) { return put((unsigned char) _c); }

inline  ostream& ostream::write(const unsigned char * _s, int _n) { return write((char *) _s, _n); }
inline  ostream& ostream::write(const signed char * _s, int _n) { return write((char *) _s, _n); }


class _CRTIMP1 ostream_withassign : public ostream {
        public:
                ostream_withassign();
                ostream_withassign(streambuf* _is);
                ~ostream_withassign();
    ostream& operator=(const ostream& _os) { return ostream::operator=(_os.rdbuf()); }
    ostream& operator=(streambuf* _sb) { return ostream::operator=(_sb); }
};

extern ostream_withassign _CRTIMP1 cout;
extern ostream_withassign _CRTIMP1 cerr;
extern ostream_withassign _CRTIMP1 clog;

inline _CRTIMP1 ostream& __cdecl flush(ostream& _outs) { return _outs.flush(); }
inline _CRTIMP1 ostream& __cdecl endl(ostream& _outs) { return _outs << '\n' << flush; }
inline _CRTIMP1 ostream& __cdecl ends(ostream& _outs) { return _outs << char('\0'); }

_CRTIMP1 ios&           __cdecl dec(ios&);
_CRTIMP1 ios&           __cdecl hex(ios&);
_CRTIMP1 ios&           __cdecl oct(ios&);

#ifdef _MSC_VER
// Restore default packing
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif  /* _INC_OSTREAM */

#endif  /* __cplusplus */
