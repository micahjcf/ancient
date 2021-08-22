#ifndef MJCF_TYPE
#define MJCF_TYPE

typedef unsigned __int64	QWORD;

typedef void (*pFunc)(void);
typedef void (*pArgFunc)(void*);

#define HI32(a)	((DWORD)(a >> 32))
#define LO32(a)	((DWORD)(a))

#define BYTE_MAX	((BYTE)-1)
#define WORD_MAX	((WORD)-1)
#define DWORD_MAX	((DWORD)-1)
#define QWORD_MAX	((QWORD)-1)

#endif

#ifndef _WINDEF_
#define _WINDEF_

#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.

#define MAX_PATH          260

#define NULL    0

#define FALSE               0
#define TRUE                1
#define IN
#define OUT
#define OPTIONAL

#if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#endif

#define CONST               const

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL				*PBOOL;
typedef BOOL				*LPBOOL;
typedef BYTE				*PBYTE;
typedef BYTE				*LPBYTE;
typedef int					*PINT;
typedef int					*LPINT;
typedef WORD				*PWORD;
typedef WORD				*LPWORD;
typedef long				*LPLONG;
typedef DWORD				*PDWORD;
typedef DWORD				*LPDWORD;
typedef void				*LPVOID;
typedef CONST void			*LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#if !defined(MIDL_PASS)
typedef int INT;
#endif
#endif

typedef struct _COORD {
    SHORT X;
    SHORT Y;
} COORD, *PCOORD;

typedef struct _SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
} SMALL_RECT, *PSMALL_RECT;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HINSTANCE);

typedef HINSTANCE HMODULE;      /* HMODULEs can be used in place of HINSTANCEs */

#endif //_WINDEF_
