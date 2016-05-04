// File: DwRst.h
// Author: Kiyoshi Tashiro
// Copyright(C) 2004 by Fuji Xerox Co,. Ltd. All right reserved.

// dwrstモジュールを利用するためのヘッダ

// dwrstはRST(3.5)の機能を利用する実装を集めたもの
// dwrstはRST(3.5)をスタティックリンクする

// mppmodel、dwimgutlなどXDWAPIから呼ばれてRSTを利用する
// モジュールでは、直接RSTのDLLを使わずdwrst経由で使う。
// (XDWAPI利用モジュールがすでにRSTの古いDLLをロードしている場合に
// バージョン不整合による問題を回避するため。(AR11356)

// dwrstを遅延ロードしたい場合は、dwrst_dynamic.hを使う。

// V7.0でdwrstはCIP 1,2をスタティックリンクする
// 利用者からみた関数仕様などは変わらないので、このヘッダをそのまま使う

#if !defined(__DWRST_H__INCLUDED_)
#define __DWRST_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "windows.h"
#include "mpc_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	DWRST_TIFF_COMP_NONE = 0,
	DWRST_TIFF_COMP_PACKBITS = 1,
	DWRST_TIFF_COMP_JPEG = 2,
	DWRST_TIFF_COMP_MMR = 3,
	DWRST_TIFF_COMP_ERROR = -1
} DwRst_TiffCompType;

typedef enum {
	DWRST_PDF_COMP_NONE = 10,
	DWRST_PDF_COMP_JPEG = 11,
	DWRST_PDF_COMP_MRC = 12,
	DWRST_PDF_COMP_MMR = 13,
	DWRST_PDF_COMP_ERROR = -1
} DwRst_PdfCompType;

typedef enum {
	DWRST_FORMAT_BITMAP = 0,
	DWRST_FORMAT_JPEG = 1,
	DWRST_FORMAT_TIFF = 3,
	DWRST_FORMAT_IMS = 5,
	DWRST_FORMAT_PDF = 6,
	DWRST_FORMAT_ERROR = -1
} DwRst_FormatType;

typedef enum {
	DWRST_PDF_ODD_OBJECT = -1,
	DWRST_PDF_NO_IMAGE = -2,
	DWRST_PDF_BROKEN = -3,
	DWRST_PDF_OTHER = -999
} DwRst_PdfError;

// 画像から解像度が取得できない場合などに用いる値(dpi)
// この値を変更すると外部仕様も変わるので注意
const int DwRst_DEFAULT_DPI = 200;

__declspec(dllexport) HRESULT __stdcall DwRst_IMSFileToPDFFile( const char* pszInputFile, const char* pOutputFile, MP_Dim dimPage, MP_Pos posHetero, MP_Integer iReso );
__declspec(dllexport) HRESULT __stdcall DwRst_DIBFileToIMSFile( const char* pszDibPath, const char* pszImsPath, MP_Integer level, MPC_AdvCancelInfo *info );
__declspec(dllexport) HGLOBAL __stdcall DwRst_DIBMemToIMSMem( const unsigned char* pDibMem, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo *info );

__declspec(dllexport) int __stdcall DwRst_StartMultiTiffFile( LPCSTR destPath, void** pTiffConverter);
__declspec(dllexport) int __stdcall DwRst_AppendMultiTiffFile( LPCSTR bmpPath, DwRst_TiffCompType nCompression, int isColor, int nBitsPerPixel,
		void* pTiffConverter, int iJpegQuality, MPC_AdvCancelInfo* pCancelInfo );
__declspec(dllexport) int __stdcall DwRst_EndMultiTiffFile( void* pTiffConverter);

__declspec(dllexport) int __stdcall DwRst_StartMultiPdfFile( LPCSTR destPath, void** pTiffConverter);
__declspec(dllexport) int __stdcall DwRst_AppendMultiPdfFile( LPCSTR imgPath, DwRst_PdfCompType nCompression, int isColor, int nBitsPerPixel,
		void* pTiffConverter, int iJpegQuality,
		int iPageW, int iPageH, int iImgX, int iImgY, int iReso,
		int bDirect, MPC_AdvCancelInfo* pCancelInfo );
__declspec(dllexport) int __stdcall DwRst_EndMultiPdfFile( void* pTiffConverter);

__declspec(dllexport) int __stdcall DwRst_CreateTiffFile( LPCSTR bmpPath, LPCSTR destPath,int isColor, int nBitsPerPixel,
		DwRst_TiffCompType iCompressionType, int iJpegQuality, MPC_AdvCancelInfo* pCancelInfo );

__declspec(dllexport) BOOL_XD __stdcall DwRst_CanSeparateBitmap(LPCSTR imgfile, int nthImage, int iDefaultReso);
__declspec(dllexport) int __stdcall DwRst_JpegToBmp( LPCSTR pszJpegPath, LPCSTR pszBmpPath,
		int iXdpi, int iYdpi, MPC_AdvCancelInfo* pCancelInfo );
__declspec(dllexport) HRESULT __stdcall DwRst_GetImageInfo( const char* pszImageFile, int nPage, LONG* piXpix, LONG* piYpix, LONG* piXppm, LONG* piYppm );
__declspec(dllexport) int __stdcall DwRst_SeparateBitmap(LPCSTR imgfile, int pNthImage,
		int iDefaultReso, int* height, int* npage, char*** pSepbitmap,
		MPC_AdvCancelInfo* pCancelInfo );
__declspec(dllexport) int __stdcall DwRst_ConvertTIFFtoDIB(LPCSTR pszTiffPath, LPCSTR pszBmpPath,
		int iPage, MPC_AdvCancelInfo* pCancelInfo );
__declspec(dllexport) DwRst_FormatType __stdcall DwRst_GetImageType( LPCSTR fileName, HRESULT* phres );
__declspec(dllexport) int __stdcall DwRst_GetPageNo( LPCSTR fileName );


__declspec(dllexport) HRESULT __stdcall DwRst_AssertImportablePdf( LPCSTR pPdfPath, int* pRetErrPage, DwRst_PdfError* pRetErrCode, int iCreatorMaxBytes, char* pszCreator, MPC_AdvCancelInfo* pCallBackInfo );
__declspec(dllexport) int __stdcall DwRst_GetPdfPageNum( const char* pszSrcPath, HRESULT *phres );

__declspec(dllexport) HRESULT __stdcall DwRst_NthPageInPdfToImsFile( MPCSession* pSession, const char* pszSrcPath, const char* pszImsFile, int iNth, int iCompLevel, MP_Dim* pImageReso, MP_Dim* pImagePix, MP_Dim* pPageDim, MP_Pos* pImagePos, int* piRotate, MPC_AdvCancelInfo* pCallBackInfo );

__declspec(dllexport) HRESULT __stdcall DwRst_CleanSeparateBitmapPaths( int iNpage, char** ppszSepBmpPaths );

#ifdef __cplusplus
} // end of extern "C"
#endif


#endif //__DWRST_H__INCLUDED_


// CHANGE LOG
// 2004.10.07 - Tashiro - V6.0 新規作成
// 2004.10.18 - Tashiro - AR11421 PDFの回転状態をDWページに反映させるための機能追加
// 2004.10.21 - Tashiro - V6.0 AR10917 PDF判定関数にキャンセル機能を追加
// 2004.11.08 - Tashiro - AR10669 PDF読み込み時のエラーを詳細化
// 2005.05.18 - Tashiro - AR12107 DwRst_CleanSeparateBitmapPaths()関数を追加
