// w2m_gdi.h
//
//  Updater : $Author: chikyu $
//  Version : $Revision: 1.5 $, $Date: 2009/12/22 08:11:31 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//
// windows版からの移植に際し、wingdi.h の定義をOSX用に定義
//

#ifndef W2WM_WINGDI_H
#define W2WM_WINGDI_H


#include "w2mpf_gdi_def.h"


#define MM_ANISOTROPIC		 8

// add 2002/01/20 by akiyoshi
#define LF_FACESIZE			32


// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

/* constants for the biCompression field */
#define BI_RGB        0L

//#include <pshpack1.h>

typedef struct tagRGBTRIPLE
{
    BYTE    rgbtBlue;
    BYTE    rgbtGreen;
    BYTE    rgbtRed;
} RGBTRIPLE;

//#include <poppack.h>

typedef struct tagHANDLETABLE
{
	HGDIOBJ_XD	objectHandle[1];
} HANDLETABLE, *PHANDLETABLE, *LPHANDLETABLE;

#endif

HMETAFILE_XD	MPF_SetMetaFileBitsEx(
					UINT nSize,			// size of Windows-format metafile
					CONST BYTE *lpData	// pointer to metafile data
				);

HENHMETAFILE_XD	MPF_SetEnhMetaFileBits(
					UINT cbBuffer,			// buffer size
					CONST BYTE *lpData		// buffer that contains enhanced metafile data
				);

HMETAFILE_XD	MPF_CopyMetaFileA(
					HMETAFILE_XD hmfSrc,	// handle to Windows-format metafile
					LPCSTR lpszFile			// pointer to a filename string
				);

BOOL_XD			MPF_DeleteMetaFile(
					HMETAFILE_XD hmf // handle to Windows-format metafile
				);

BOOL_XD			MPF_DeleteEnhMetaFile(
					HENHMETAFILE_XD hemf // handle to an enhanced metafile
				);

typedef int (CALLBACK* MFENUMPROC_XD)(HDC_XD	, PHANDLETABLE, PMETARECORD, int, LPARAM);

BOOL_XD			MPF_EnumMetaFile(
					HDC_XD	 hdc,				// handle to device context
					HMETAFILE_XD hmf,			// handle to Windows-format metafile
					MFENUMPROC_XD lpMetaFunc,	// pointer to callback function
					LPARAM lParam				// pointer to callback-function data
				);

typedef int (CALLBACK* ENHMFENUMPROC_XD)(HDC_XD	, HANDLETABLE*, const ENHMETARECORD*, int, LPVOID);

BOOL_XD			MPF_EnumEnhMetaFile(
					HDC_XD	 hdc,					// handle to device context
					HENHMETAFILE_XD hemf,			// handle to enhanced metafile
					ENHMFENUMPROC_XD lpEnhMetaFunc,	// pointer to callback function
					LPVOID lpData,					// pointer to callback-function data
					CONST RECT *lpRect				// pointer to bounding rectangle
				);

UINT			MPF_GetEnhMetaFileHeader(
					HENHMETAFILE_XD	hemf,		// handle of enhanced metafile
					UINT			cbBuffer,	// size of buffer, in bytes
					LPENHMETAHEADER	lpemh		// address of buffer to receive data
				);

UINT			MPF_GetEnhMetaFileBits(
									   HENHMETAFILE_XD hemf,	// メタファイルのハンドル
									   UINT cbBuffer,			// バッファのサイズ（バイト数）
									   LPBYTE lpbBuffer		// データバッファへのポインタ
									   ); 

HGDIOBJ_XD		MPF_GetStockObject(
					LONG fnObject		// type of stock object
				);

HDC_XD			MPF_CreateDrawDC(int width, int height, int xresolution, int yresolution);

void			MPF_DeleteDrawDC(HDC_XD	 hdc);

HDC_XD			MPF_CreateCompatibleDC(
					HDC_XD	hdc		// handle to the device context
				);

HBITMAP_XD		MPF_CreateCompatibleBitmap(
					HDC_XD	hdc,	// handle to device context
					int		nWidth,	// width of bitmap, in pixels
					int		nHeight	// height of bitmap, in pixels
				);

int				MPF_SaveDC(
					HDC_XD	hdc		// handle of device context
				);

BOOL_XD			MPF_RestoreDC(
					HDC_XD	hdc,		// handle of device context
					int		nSavedDC	// specifies state to be restored
				);

BOOL_XD			MPF_DeleteDC(
					HDC_XD hdc	// handle to device context
				);

HPALETTE		MPF_SelectPalette(
					HDC_XD		hdc,				// handle of device context
					HPALETTE	hpal,				// handle of logical color palette
					BOOL_XD		bForceBackground	// foreground/background mode
				);

BOOL_XD			MPF_Rectangle(
					HDC_XD	hdc,		// handle of device context
					int		nLeftRect,	// x-coord. of bounding rectangle's upper-left corner
					int		nTopRect,	// y-coord. of bounding rectangle's upper-left corner
					int		nRightRect,	// x-coord. of bounding rectangle's lower-right corner
					int		nBottomRect	// y-coord. of bounding rectangle's lower-right corner
				);

BOOL_XD			MPF_SetWindowOrgEx(
					HDC_XD	hdc,	// handle of device context
					int		X,		// new x-coordinate of window origin
					int		Y,		// new y-coordinate of window origin
					LPPOINT	lpPoint	// address of structure receiving original origin
				);

BOOL_XD			MPF_SetWindowExtEx(
					HDC_XD	hdc,		// handle of device context
					int		nXExtent,	// new horizontal window extent
					int		nYExtent,	// new vertical window extent
					LPSIZE	lpSize		// original window extent
				);

BYTE			MPF_GetCurrentCharSet(HDC_XD hdc);

int             MPF_GetCurrentHeight(HDC_XD hdc);

int             MPF_GetCurrentEscapement(HDC_XD hdc);

/*
HENHMETAFILE_XD	MPF_CopyEnhMetaFileA(
					HENHMETAFILE_XD hemfSrc, // handle to an enhanced metafile
					LPCSTR lpszFile // pointer to a filename string
				);
*/

/*
HDC_XD			CreateMetaFileA(
					LPCSTR lpszFile   // pointer to filename string
				);
*/

/*
HMETAFILE_XD	MPF_CloseMetaFile(
					HDC_XD	 hdc   // handle to metafile device context
				);
*/

/*
int				GetDeviceCaps(HDC_XD	 hdc, int nIndex);
*/

/*
HGDIOBJ_XD		SelectObject(
					HDC_XD	 hdc,		// handle of device context
					HGDIOBJ_XD hgdiobj	// handle of object
				);
*/

/*
DWORD			MPF_GetObjectType(HGDIOBJ_XD h);

DWORD			MPF_GetObjectType(HDC_XD hdc);
*/

BOOL_XD			MPF_DeleteObject(HGDIOBJ_XD hObject);

/*
HDC_XD			MPF_GetDC(
					HWND_XD	hWnd	// handle to a window
				);
*/

/*
int				MPF_ReleaseDC(
					HWND_XD	hWnd,	// handle of window
					HDC_XD	hDC		// handle of device context
				);
*/

/*

typedef int (CALLBACK* FONTENUMPROC_XD)(const LOGFONT *plf, const TEXTMETRIC *, DWORD, LPARAM);

int				MPF_EnumFontFamiliesEx(
					HDC_XD			hdc,					// デバイスコンテキストのハンドル
					PLOGFONT		lpLogfont,				// フォント情報
					FONTENUMPROC_XD	lpEnumFontFamExProc,	// コールバック関数
					LPARAM			lParam,					// 追加データ
					DWORD			dwFlags					// 未使用；必ず 0 を指定
				);
*/

#endif /* W2M_WINGDI_H */

