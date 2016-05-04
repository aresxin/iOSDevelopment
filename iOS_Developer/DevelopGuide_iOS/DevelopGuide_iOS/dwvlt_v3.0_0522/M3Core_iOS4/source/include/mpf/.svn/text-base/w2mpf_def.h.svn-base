//
//  w2m_def.h
//
//  Updater : $Author: komoda $
//  Version : $Revision: 1.2 $, $Date: 2009/04/07 11:25:27 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

// Windows版からの移植に際し、windef.h の必要部分をMAC用に定義
#ifndef W2M_WINDEF_H
#define W2M_WINDEF_H

#define CONST	const
typedef const char	*LPCSTR;
typedef LPCSTR		LPCTSTR;
typedef char	*LPSTR;
typedef LPSTR	LPTSTR;
typedef short	SHORT;
typedef long	LONG;
typedef long	*PLONG;
typedef float	FLOAT;
typedef FLOAT	*PFLOAT;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef DWORD	*LPDWORD;
typedef unsigned int	UINT;
typedef unsigned short	USHORT;
typedef unsigned char	BYTE;
typedef BYTE 	*LPBYTE;
typedef void	VOID;
typedef void	*LPVOID;
typedef const void *LPCVOID;
typedef unsigned char UCHAR;

typedef int	INT;

typedef LPVOID LPARAM;
typedef int WPARAM;

typedef unsigned short WCHAR;   // 16-bit UNICODE character

typedef DWORD   COLORREF;
#define RGB(r,g,b)  ((b << 16) | (g << 8) | r)

/*
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
*/

#define __int64	long long
#define _int64	long long	// add 2002/01/12 by akiyoshi

typedef unsigned __int64 ULONGLONG;
typedef ULONGLONG        DWORDLONG;

// ファイル操作用
typedef void	*HANDLE;
#define DECLARE_HANDLE(name)    typedef HANDLE name

#define GENERIC_READ	(0x80000000L)
#define GENERIC_WRITE	(0x40000000L)

#define FILE_SHARE_READ  0x00000001L
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE               0x00000004
#define FILE_ATTRIBUTE_READONLY             0x00000001
#define FILE_ATTRIBUTE_HIDDEN               0x00000002
#define FILE_ATTRIBUTE_SYSTEM               0x00000004
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020
#define FILE_ATTRIBUTE_ENCRYPTED            0x00000040
#define FILE_ATTRIBUTE_NORMAL               0x00000080
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800
#define FILE_ATTRIBUTE_OFFLINE              0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000

typedef struct _RTL_CRITICAL_SECTION {
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    DWORD SpinCount;
} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

// メモリ操作
#define RtlCopyMemory(Destination,Source,Length) memcpy((Destination),(Source),(Length))

typedef HANDLE	HGLOBAL;

//DECLARE_HANDLE(HGDIOBJ);
//DECLARE_HANDLE(HENHMETAFILE);
//DECLARE_HANDLE(HMETAFILE);
DECLARE_HANDLE(HWND);
////DECLARE_HANDLE(HDC);
//typedef int *HDC;
//DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;

typedef struct tagSIZE {
	long	cx;	//_DWVLT_MULTIPLATFORM_OSX_
	long	cy; //_DWVLT_MULTIPLATFORM_OSX_
} SIZE, *LPSIZE;

typedef struct tagSIZEL {
	long cx;
	long cy;
} SIZEL;

typedef struct tagPOINT {
    long    x;
    long    y;
} POINT, *LPPOINT;

typedef struct _POINTL      /* ptl  */
{
    long  x;
	long  y;
} POINTL, *PPOINTL;

typedef struct tagPOINTS
{
#ifndef _MAC
    SHORT   x;
    SHORT   y;
#else
    SHORT   y;     
    SHORT   x;
#endif
} POINTS, *PPOINTS, *LPPOINTS;

typedef struct tagRECT {
	long	left;
	long	top;
	long	right;
	long	bottom;
} RECT, *PRECT, *LPRECT;

typedef struct _RECTL       /* rcl */
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECTL, *PRECTL, *LPRECTL;

#endif /* W2M_WINDEF_H */

