//
//  win2mac.h
//
//  Updater : $Author: chikyu $
//  Version : $Revision: 1.4 $, $Date: 2009/12/22 08:11:31 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//
// windows版からの移植に際し、MS/C++のAPIを GNU C++ に移植。
#ifndef WIN2MAC_H
#define WIN2MAC_H

#ifdef __cplusplus
#include <algorithm>
#include <string>
#endif

/*
// LittleEndian <-> BigEndian 対応
#include "reverseendian.h"
*/
bool reverseEndian(char *value, int size);

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

#ifdef _DEBUG
#define W2M_NOTIMPL_DEBUG_WRITE	printf("Is it really required?(%s:line-%d)\n", __FILE__, __LINE__);
#define W2M_TRACE_DEBUG_WRITE	printf("***TRACE***(%s:line-%d)\n", __FILE__, __LINE__);
#else
#define W2M_NOTIMPL_DEBUG_WRITE	;
#define W2M_TRACE_DEBUG_WRITE ;
#endif


#define pascal
#define __stdcall
#define __declspec(x)
#define _declspec(x)

#define FAR	pascal

typedef long	HRESULT;

#ifdef TRUE
#undef TRUE
#endif
#ifdef FALSE
#undef FALSE
#endif

/*
#ifdef __cplusplus
typedef bool	BOOL;
#define TRUE	true
#define FALSE	false
#else
typedef short	BOOL;
#define FALSE	0
#define TRUE	!FALSE
#endif
*/

#define CALLBACK

//#define _MAX_PATH	260
#define _MAX_PATH	4096
#define _MAX_DRIVE	3
//#define _MAX_DIR	256
#define _MAX_DIR	4096
#define _MAX_FNAME	256
#define _MAX_EXT	256

void _splitpath(
	const char *path,
	char *drive,
	char *dir,
	char *fname,
	char *ext
);

/*
#define __int64	long long
#define _int64	long long	// add 2002/01/12 by akiyoshi
*/

/*
#ifndef _forNotesDomino_
#define _mbschr(s, c)	strchr((const char *)(s), (int)(c))
#else
#include <wchar.h>
#define _mbschr(s, c)	wcschr((const wchar_t *)(s), (wchar_t)(c))
#endif
*/

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_


// 名前をラッパー関数名に変える

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

#define _splitpath		my_splitpath

void my_splitpath(
    const char *path,
	char *drive,
	char *dir,
	char *fname,
	char *ext
);

#define Sleep(m)		usleep(m*1000)

/*
#define     DeleteBitmap(hbm)       DeleteObject((HGDIOBJ)(HBITMAP)(hbm))

#define stricmp(s1,s2)	strcasecmp(s1,s2)
*/

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_


// stricmpは_stricmpの旧関数
#define stricmp _stricmp

// strnicmpは_strnicmpの旧関数
#define strnicmp _strnicmp


// [XDWAPI for Spotlight Importer V70 2008.02.14 by akiyoshi] >>>
//#ifdef _XDWAPI_
// Wide文字関数群を独自実装
// win2mpf.hに定義を移動

/*
LPWSTR MPF_wcsncpy(
	LPWSTR	strDest,
	LPCWSTR	strSource,
	size_t count
);

LPWSTR MPF_wcscpy(
	LPWSTR	strDest,
	LPCWSTR	strSource
);

LPWSTR MPF_wcscat(
	LPWSTR	strDest,
	LPCWSTR	strSource
);

int MPF_wcscmp(
	LPCWSTR	string1,
	LPCWSTR	string2
);

int MPF_wcsncmp(
	LPCWSTR	string1,
	LPCWSTR	string2,
	size_t count
);

size_t MPF_wcslen(
	LPCWSTR	string
);
*/

//#endif //def _XDWAPI_
// <<< [XDWAPI]

#endif /* WIN2MAC_H */

