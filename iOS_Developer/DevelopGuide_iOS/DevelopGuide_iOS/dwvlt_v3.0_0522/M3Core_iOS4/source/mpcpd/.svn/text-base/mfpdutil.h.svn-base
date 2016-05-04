// $Archive: /DocuWorks/62/Source/mpcpd/mfpdutil.h $
//
// Copyright (c) 2004-2006 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:25 $
// $Revision: 1.6 $

#ifndef _MFPDUTIL_H_
#define _MFPDUTIL_H_

#ifndef _VECTOR_
#include <vector>
#endif

/*
#ifndef _WINDOWS_
#include <windows.h>
#endif
*/
#include "win2mpf.h"


/*!
	@brief パスの頂点のデータを管理するクラス@par
	Win32APIのGetPathでも頂点データは取れるが、デバイス座標(拡縮後)のサイズに
	なるのでなめらか描画には使用できないため、自分で管理する@par
	Win32APIのGetPathと同じ形式のデータを扱う
*/
class MfpdPathData
{
public:
	void Clear();
	void Add(POINT p, BYTE t);
	bool IsCreating() const;
	void Begin();
	void End();
	int GetSize() const;
	POINT* GetPoints();
	BYTE* GetTypes();

private:
	std::vector<POINT> m_points;
	std::vector<BYTE> m_types;
	bool m_bPathCreate;
};

/*!
	@brief なめらか描画を行うクラス@par
	Win32APIと同じ名前のメソッドを呼び出せば、なめらか描画を行う
*/
class MfpdSmoothDraw
{
public:
	static void Polygon(HDC_XD hdc, const POINT* points, int nPoints);
	static void FillPath(HDC_XD hdc, MfpdPathData* pathData);

private:
	MfpdSmoothDraw();
	~MfpdSmoothDraw();
	bool Create(HDC_XD hdc, POINT* points, int nPoints);
	bool CreateCommon(HDC_XD hdc);
	bool CopyBackground(HDC_XD hdc);
	void Scale(POINT* points, int nPoints) const;
	HDC_XD GetHDC() const;
	void CopyGDIObjects(HDC_XD hdc, HPEN_XD& hPen, HGDIOBJ_XD& hpnOld, HGDIOBJ_XD& hbrOld);
	void DestroyGDIObjects(HPEN_XD hPen, HGDIOBJ_XD hpnOld, HGDIOBJ_XD hbrOld);
	bool Draw(HDC_XD hdc);

	HDC_XD m_hdc;
	HBITMAP_XD m_hbm;
	HGDIOBJ_XD m_hbmOld;
	BITMAPINFO m_bi;
	BYTE* m_pbits;
	RECT m_bound;
	SIZE m_bmpSize;
	int m_ratio;
};

/*!
	@brief RLE圧縮されたDIBを伸長するクラス@par
*/
class MfpdRLEDecoder
{
public:
	static BOOL_XD Decode(const BITMAPINFO* pSrcBI, void* pDstBI);
	static int GetUncompressedBitsSize(const BITMAPINFO* pbi);

//private:
	static BOOL_XD ReadRle4Bits (const BYTE * src, BYTE * dst, int w, int h);
	static BOOL_XD ReadRle8Bits (const BYTE * src, BYTE * dst, int w, int h);
};

/*!
	@brief DIBのヘッダやビットデータのサイズを求めるクラス@par
*/
class MfpdDIBSize
{
public:
	static int GetBISize(const BITMAPINFO *pbi);
	static int GetBitsSize(const BITMAPINFO *pbi);
	static int GetDIBSize(const BITMAPINFO *pbi);
};

/*!
	@brief DIBを特殊な方法で描画するためのクラス@par
	OSやデバイスの種類などの呼び出し条件は呼び出し側で判断すること@par
*/
class MfpdDIBDraw
{
public:
	struct Rect {
		long x;
		long y;
		long cx;
		long cy;
	};
	struct Param {
		Rect src;
		Rect dst;
	};
	struct DIB {
		BITMAPINFO* pbi;
		BYTE* pbits;
	};
	//! エラー対策されたStretchDIBits
	static int NewStretchDIBits(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop);
	//! 画像縮小モジュールを利用したStretchDIBits
	static void StretchDIBitsWithShrink(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop, BOOL_XD isAdvance);
	//! 特殊なROPの場合にPatBltで出力する
	static void StretchDIBitsWithPatBlt(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop);
	//! MERGEPAINTのPS用出力
	static bool StretchDIBitsMergePaint(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop);
	//! プリンタの不具合回避のためにStretchBltで出力する
	static bool StretchDIBitsWithStretchBlt(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop);
	//! 複雑なクリップがかけられた場合に1ラインずつに分割して出力するStretchDIBits
	static void StretchDIBitsForComplexClip(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop);
	//! 複雑なクリップがかけられた場合にクリップも分割して出力するStretchDIBits
	static bool StretchDIBitsForComplexClipWin9xPS(HDC_XD hdc, const Param& p, const DIB& dib, DWORD dwRop);
	//! Win9xのPSプリンタドライバの不具合回避のため出力パラメータを補正する
	static void ModifyParamForWin9xPS(HDC_XD hdc, long& ryPrev, long& rcyPrev, long& ryDest, long& rcyDest);
	//! クリップよりも大きい領域に出力する場合に時間がかかるのを回避する
	static void ModifyParamForClip(HDC_XD hdc, Param& p);
	//! モノクロビットマップかどうかを判断する
	static bool IsBlackAndWhite(const DIB& dib);

private:
	//! 指定領域のビットデータを切り取る
	static void TrimBits(const Rect& trimRect, const DIB& srcDib, DIB& dstDib);
};

/*!
	@brief MPF_EnumMetaFileに使用するデバイスコンテキストを提供するクラス@par
	レコードの中のデータを参照するだけでなく、デバイスコンテキストから
	現在のフォントなどを取得する場合に必要
*/
class MfpdDummyDC
{
private:
	HDC_XD m_hdc;
	HBITMAP_XD m_hbmp;
	HGDIOBJ_XD m_hold;
public:
	MfpdDummyDC();
	~MfpdDummyDC();
	HDC_XD GetHDC();
};

/*!
	@brief Meiryoフォントが置換されたときに文字が重なる問題対策用クラス
*/
class MfpdFontReplacer
{
public:
	static int CALLBACK EnumFontFamExProc(const LOGFONT *plf, const TEXTMETRIC *ptm, DWORD fontType, LPARAM lParam);
	static bool IsMeiryoFont(const LOGFONTA* plf);
	static bool IsMeiryoFont(const LOGFONTW* plf);
	static bool HasMeiryoFont() { return m_static.hasMeiryo; }
	static void ReplaceMeiryoFont(LOGFONTW* plf);
private:
	struct Data {
		Data() { SearchMeiryoFont(); }
		~Data() {}
		bool hasMeiryo;
	};
	friend class Data;
	static Data m_static;
	MfpdFontReplacer() {}
	~MfpdFontReplacer() {}
	static void SearchMeiryoFont();
};

#endif

// $History: mfpdutil.h $
// 
// *****************  Version 11  *****************
// User: Komoda       Date: 06/09/20   Time: 21:43
// Updated in $/DocuWorks/62/Source/mpcpd
// DW6.2 メイリオフォント対策
// 
// *****************  Version 9  *****************
// User: Komoda       Date: 04/10/18   Time: 17:08
// Updated in $/DocuWorks/60/Source/mpcpd
// AR11113対応
// 
// *****************  Version 8  *****************
// User: Komoda       Date: 04/07/29   Time: 21:09
// Updated in $/DocuWorks/60/Source/mpcpd
// AR10121 Polygon,FillPathのなめらか描画方法を変更
// 
// *****************  Version 7  *****************
// User: Komoda       Date: 04/07/26   Time: 20:57
// Updated in $/DocuWorks/60/Source/mpcpd
// AR10219 StretchDIBitsのなめらか描画方法を変更
// 
// *****************  Version 6  *****************
// User: Komoda       Date: 04/06/18   Time: 19:20
// Updated in $/DocuWorks/60/Source/mpcpd
// 
// *****************  Version 5  *****************
// User: Komoda       Date: 04/06/14   Time: 19:22
// Updated in $/DocuWorks/60/Source/mpcpd
// なめらか描画のon/off対応
// 
// *****************  Version 4  *****************
// User: Komoda       Date: 04/05/27   Time: 18:52
// Updated in $/DocuWorks/60/Source/mpcpd
// 
// *****************  Version 3  *****************
// User: Komoda       Date: 04/04/14   Time: 16:59
// Updated in $/DocuWorks/60/Source/mpcpd
// MfpdDIBDrawを追加
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 04/04/12   Time: 17:34
// Updated in $/DocuWorks/60/Source/mpcpd
// MfpdDummyDCを追加
// 
// *****************  Version 1  *****************
// User: Komoda       Date: 04/03/18   Time: 15:48
// Created in $/DocuWorks/60/Source/mpcpd
