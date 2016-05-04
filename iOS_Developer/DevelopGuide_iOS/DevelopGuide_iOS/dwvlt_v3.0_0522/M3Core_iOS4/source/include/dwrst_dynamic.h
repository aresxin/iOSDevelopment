// File: dwrst_dynamic.cpp
// Copyright (C) 2004 Fuji Xerox Co,. Ltd. All rights reserved.

#ifndef _DWMODULE_DYNAMICLOAD_DWRST_
#define _DWMODULE_DYNAMICLOAD_DWRST_

/////////////////////////////////////////////////////////////////////////////
// dwrst.dll を動的にロードするためのヘッダ

#include <dwdllins.h>
#include <mpc_api.h>
#include <dwrst.h>

#ifndef DWMODULE_STATIC_DWRST

#ifdef DWMODULE_DYNAMICLOAD_DWRST_INIT_ONCE

/////////////////////////////////////////////////////////////////////////////
// DLLのHINSTANCEを管理するクラス

// DLLの名前
static const char* const DWRST_DLL_NAME = "dwrst.dll";
static inline FARPROC GetProcDwRst(LPCSTR pszProcName);

class CDwRstInstance : public CDwDllInstance
{
public:
	CDwRstInstance();
	virtual ~CDwRstInstance();
};

/////////////////////////////////////////////////////////////////////////
// 動的ロード(遅延ロード)をしたいときは、Appクラスあたりで以下の宣言を
// 1度することで、モジュールのロードを遅延させて関数を呼ぶことができる
/////////////////////////////////////////////////////////////////////////

CDwRstInstance::CDwRstInstance()
: CDwDllInstance()
{
	strcpy(m_pszDllName, DWRST_DLL_NAME);
}

CDwRstInstance::~CDwRstInstance()
{
	CDwDllInstance::~CDwDllInstance();
}

// 1個だけスタティックに持つ
static CDwRstInstance s_instDwRst;

#include <assert.h>

/////////////////////////////////////////////////////////////////////////////
// Load/Freeのタイミングを明示的にしたい場合のグローバル関数

void LoadDwRstInstance()
{
	s_instDwRst.GetInstance();
}

void FreeDwRstInstance()
{
	s_instDwRst.FreeInstance();
}
static FARPROC GetProcDwRst(LPCSTR pszProcName)
{
	HINSTANCE hInst = s_instDwRst.GetInstance();
	if (hInst != NULL) {
		FARPROC proc = ::GetProcAddress(hInst, pszProcName);
		if (proc != NULL) {
			return proc;
		}
	}
	assert(0);
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// DLLのエクスポート関数をラップすることで遅延ロードを行う。
// 以下ラッパー関数の実装

extern "C" HRESULT __stdcall DwRst_IMSFileToPDFFile( const char* pszInputFile, const char* pOutputFile, MP_Dim dimPage, MP_Pos posHetero, MP_Integer iReso )
{
	typedef HRESULT (__stdcall *FUNC)( const char*, const char*, MP_Dim, MP_Pos, MP_Integer );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_IMSFileToPDFFile@28");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_IMSFileToPDFFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pszInputFile, pOutputFile, dimPage, posHetero, iReso );

	return MP_E_NOINTERFACE;
}

extern "C" HRESULT __stdcall DwRst_DIBFileToIMSFile( const char* pszDibPath, const char* pszImsPath, MP_Integer level, MPC_AdvCancelInfo *info )
{
	typedef HRESULT (__stdcall *FUNC)(  const char*, const char*, MP_Integer, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_DIBFileToIMSFile@16");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_DIBFileToIMSFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pszDibPath, pszImsPath, level, info );

	return MP_E_NOINTERFACE;
}

extern "C" HGLOBAL __stdcall DwRst_DIBMemToIMSMem( const unsigned char* pDibMem, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo *info )
{
	typedef HGLOBAL (__stdcall *FUNC)( const unsigned char*, MP_Integer, HRESULT*, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_DIBMemToIMSMem@16");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_DIBMemToIMSMem");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pDibMem, level, phres, info );

	if ( phres != NULL ) *phres = MP_E_NOINTERFACE;
	return NULL;
}

extern "C" int __stdcall DwRst_StartMultiTiffFile( LPCSTR destPath, void** pTiffConverter )
{
	typedef int (__stdcall *FUNC)( LPCSTR, void** );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_StartMultiTiffFile@8");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_StartMultiTiffFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( destPath, pTiffConverter );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_AppendMultiTiffFile( LPCSTR bmpPath, DwRst_TiffCompType nCompression, int isColor, int nBitsPerPixel, void* pTiffConverter, int iJpegQuality, MPC_AdvCancelInfo* pCancelInfo )
{
	typedef int (__stdcall *FUNC)( LPCSTR, DwRst_TiffCompType, int, int, void*, int, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_AppendMultiTiffFile@28");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_AppendMultiTiffFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( bmpPath, nCompression, isColor, nBitsPerPixel, pTiffConverter, iJpegQuality, pCancelInfo );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_EndMultiTiffFile( void* pTiffConverter )
{
	typedef int (__stdcall *FUNC)( void* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_EndMultiTiffFile@4");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_EndMultiTiffFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pTiffConverter );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_StartMultiPdfFile( LPCSTR destPath, void** pTiffConverter)
{
	typedef int (__stdcall *FUNC)( LPCSTR, void** );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_StartMultiPdfFile@8");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_StartMultiPdfFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( destPath, pTiffConverter );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_AppendMultiPdfFile( LPCSTR imgPath, DwRst_PdfCompType nCompression, int isColor, int nBitsPerPixel, void* pTiffConverter, int iJpegQuality, int iPageW, int iPageH, int iImgX, int iImgY, int iReso, int bDirect, MPC_AdvCancelInfo* pCancelInfo )
{
	typedef int (__stdcall *FUNC)( LPCSTR, DwRst_PdfCompType, int, int, void*, int, int, int, int, int, int, int, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_AppendMultiPdfFile@52");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_AppendMultiPdfFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( imgPath, nCompression, isColor, nBitsPerPixel, pTiffConverter, iJpegQuality, iPageW, iPageH, iImgX, iImgY, iReso, bDirect, pCancelInfo );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_EndMultiPdfFile( void* pTiffConverter )
{
	typedef int (__stdcall *FUNC)( void* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_EndMultiPdfFile@4");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_EndMultiPdfFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pTiffConverter );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_CreateTiffFile( LPCSTR bmpPath, LPCSTR destPath, int isColor, int nBitsPerPixel, DwRst_TiffCompType iCompressionType, int iJpegQuality, MPC_AdvCancelInfo* pCancelInfo )
{
	typedef int (__stdcall *FUNC)( LPCSTR, LPCSTR, int, int, DwRst_TiffCompType, int, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_CreateTiffFile@28");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_CreateTiffFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( bmpPath, destPath, isColor, nBitsPerPixel, iCompressionType, iJpegQuality, pCancelInfo );

	return MP_E_NOINTERFACE;
}

extern "C" BOOL __stdcall DwRst_CanSeparateBitmap( LPCSTR imgfile, int nthImage, int iDefaultReso )
{
	typedef BOOL (__stdcall *FUNC)( LPCSTR, int, int );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_CanSeparateBitmap@12");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_CanSeparateBitmap");
#endif	// _WIN64
	if (proc != NULL)
		return proc( imgfile, nthImage, iDefaultReso );

	return FALSE;
}

extern "C" int __stdcall DwRst_JpegToBmp( LPCSTR pszJpegPath, LPCSTR pszBmpPath, int iXdpi, int iYdpi, MPC_AdvCancelInfo* pCancelInfo )
{
	typedef int (__stdcall *FUNC)( LPCSTR, LPCSTR, int, int, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_JpegToBmp@20");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_JpegToBmp");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pszJpegPath, pszBmpPath, iXdpi, iYdpi, pCancelInfo );

	return MP_E_NOINTERFACE;
}

extern "C" HRESULT __stdcall DwRst_GetImageInfo( const char* pszImageFile, int nPage, LONG* piXpix, LONG* piYpix, LONG* piXppm, LONG* piYppm )
{
	typedef HRESULT (__stdcall *FUNC)( const char*, int, LONG*, LONG*, LONG*, LONG* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_GetImageInfo@24");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_GetImageInfo");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pszImageFile, nPage, piXpix, piYpix, piXppm, piYppm );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_SeparateBitmap( LPCSTR imgfile, int pNthImage, int iDefaultReso, int* height, int* npage, char*** pSepbitmap, MPC_AdvCancelInfo* pCancelInfo )
{
	typedef int (__stdcall *FUNC)( LPCSTR, int, int, int*, int*, char***, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_SeparateBitmap@28");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_SeparateBitmap");
#endif	// _WIN64
	if (proc != NULL)
		return proc( imgfile, pNthImage, iDefaultReso, height, npage, pSepbitmap, pCancelInfo );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_ConvertTIFFtoDIB( LPCSTR pszTiffPath, LPCSTR pszBmpPath, int iPage, MPC_AdvCancelInfo* pCancelInfo )
{
	typedef int (__stdcall *FUNC)( LPCSTR, LPCSTR, int, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_ConvertTIFFtoDIB@16");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_ConvertTIFFtoDIB");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pszTiffPath, pszBmpPath, iPage, pCancelInfo );

	return MP_E_NOINTERFACE;
}

extern "C" DwRst_FormatType __stdcall DwRst_GetImageType( LPCSTR fileName, HRESULT* phres )
{
	typedef DwRst_FormatType (__stdcall *FUNC)( LPCSTR, HRESULT* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_GetImageType@8");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_GetImageType");
#endif	// _WIN64
	if (proc != NULL)
		return proc( fileName, phres );

	if ( phres != NULL ) *phres = MP_E_NOINTERFACE;
	return DWRST_FORMAT_ERROR;
}

extern "C" int __stdcall DwRst_GetPageNo( LPCSTR fileName )
{
	typedef int (__stdcall *FUNC)( LPCSTR );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_GetPageNo@4");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_GetPageNo");
#endif	// _WIN64
	if (proc != NULL)
		return proc( fileName );

	return MP_E_NOINTERFACE;
}

extern "C" HRESULT __stdcall DwRst_AssertImportablePdf( LPCSTR pPdfPath, int* pRetErrPage, DwRst_PdfError* pRetErrCode, int iCreatorMaxBytes, char* pszCreator, MPC_AdvCancelInfo* pCallBackInfo )
{
	typedef HRESULT (__stdcall *FUNC)( LPCSTR, int*, DwRst_PdfError*, int, char*, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_AssertImportablePdf@24");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_AssertImportablePdf");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pPdfPath, pRetErrPage, pRetErrCode, iCreatorMaxBytes, pszCreator, pCallBackInfo );

	return MP_E_NOINTERFACE;
}

extern "C" int __stdcall DwRst_GetPdfPageNum( const char* pszSrcPath, HRESULT *phres )
{
	typedef int (__stdcall *FUNC)( const char*, HRESULT* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_GetPdfPageNum@8");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_GetPdfPageNum");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pszSrcPath, phres );

	if ( phres != NULL ) *phres = MP_E_NOINTERFACE;
	return -1;
}

extern "C" HRESULT __stdcall DwRst_NthPageInPdfToImsFile( MPCSession* pSession, const char* pszSrcPath, const char* pszImsFile, int iNth, int iCompLevel, MP_Dim* pImageReso, MP_Dim* pImagePix, MP_Dim* pPageDim, MP_Pos* pImagePos, int* piRotate, MPC_AdvCancelInfo* pCallBackInfo )
{
	typedef HRESULT (__stdcall *FUNC)( MPCSession*, const char*, const char*, int, int, MP_Dim*, MP_Dim*, MP_Dim*, MP_Pos*, int*, MPC_AdvCancelInfo* );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_NthPageInPdfToImsFile@44");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_NthPageInPdfToImsFile");
#endif	// _WIN64
	if (proc != NULL)
		return proc( pSession, pszSrcPath, pszImsFile, iNth, iCompLevel, pImageReso, pImagePix, pPageDim, pImagePos, piRotate, pCallBackInfo );

	return MP_E_NOINTERFACE;
}

extern "C" HRESULT __stdcall DwRst_CleanSeparateBitmapPaths( int iNpage, char** ppszSepBmpPaths )
{
	typedef int (__stdcall *FUNC)( int, char** );
#ifndef _WIN64
	FUNC proc = (FUNC)GetProcDwRst("_DwRst_CleanSeparateBitmapPaths@8");
#else	// _WIN64
	FUNC proc = (FUNC)GetProcDwRst("DwRst_CleanSeparateBitmapPaths");
#endif	// _WIN64
	if (proc != NULL)
		return proc( iNpage, ppszSepBmpPaths );

	return MP_E_NOINTERFACE;
}

// ラッパー関数の実装ここまで
/////////////////////////////////////////////////////////////////////////////

#endif // DWMODULE_DYNAMICLOAD_RWRST_INIT_ONCE

#else	// DWMODULE_STATIC_DWRST
// スタティックリンクにした場合はこちらが適用される
#pragma comment (lib, "..\\lib\\dwrst.lib")
#endif	// DWMODULE_STATIC_DWRST

#endif // _DWMODULE_DYNAMICLOAD_DWRST_

// CHANGE LOG
// 2004.10.07 - Tashiro - V6.0 mppmodel_dynamic.hを流用、変更
// 2004.10.18 - Tashiro - AR11421 PDFの回転状態をDWページに反映させるための機能追加
// 2004.10.21 - Tashiro - V6.0 AR10917 PDF判定関数にキャンセル機能を追加
// 2004.11.08 - Tashiro - AR10669 PDF読み込み時のエラーを詳細化
// 2005.05.18 - Tashiro - AR12107 DwRst_CleanSeparateBitmapPaths()関数を追加
// 2005.11.08 - Nakazawa - 64bit対応 エクスポート関数の名前をifdefで分けた(※今後関数を追加するときも同様にしてください)
