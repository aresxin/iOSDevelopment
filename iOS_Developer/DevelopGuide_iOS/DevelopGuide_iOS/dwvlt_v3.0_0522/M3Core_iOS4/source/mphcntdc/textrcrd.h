// $Archive: /DocuWorks/70/Source/mphcntdc/textrcrd.h $
//
// Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:28 $
// $Revision: 1.5 $

// File: TEXTRCRD.h
// Author: Hidetoshi Hamada
// Copyright(C) 1997-2004 by Fuji Xerox Co,.Ltd.All rights reserved.

#ifndef _TEXTRCRD_H
#define _TEXTRCRD_H

class CTextRecord 
{
private:
	int m_order;			// レコードの番号
	MP_Text *m_pText;		// テキスト
	int m_charIndex;		// 全体のテキストに対する位置
	int m_length;			// テキストの文字数
	MP_Pos m_origin;		// テキストの描画位置
	int m_orientation;		// 回転角
	MP_Rect m_rect;			// テキストの矩形領域
	int *m_pWidth;			// 各文字の幅
	BOOL_XD m_bOcrRecord;		// OCRかどうか
	BOOL_XD m_bWithLF;			// 直前に改行を挿入するかどうか

private:
	BOOL_XD IntersectRect(MP_Rect rect) const;
	void SetLF(BOOL_XD bWithLF = TRUE);
	BOOL_XD CreateText (int codePage, int length, const char* pText);
	BOOL_XD CreateText (int length, const MP_Text* pText);
	BOOL_XD CreateDxWidth (int codePage, const WORD* pDxWidth);
	BOOL_XD CreateDxWidth (int codePage, const DWORD* pDxWidth);
	BOOL_XD CreateDxWidth (const DWORD* pDxWidth);
	void CreateOriginAndRect(HDC_XD hDC, const LOGFONT *pLogfont);
	void CalcIsSameLine(CTextRecord* preTR);
	BOOL_XD CheckOverlap(CTextRecord* preTR);

public:
	CTextRecord();
	~CTextRecord();
	BOOL_XD CreateFromMetaRecordA(HDC_XD hDC, int order, int index, EMREXTTEXTOUTW *lpEMFR, MP_Dim pageDim, int angle, CTextRecord* pPreTR);
	BOOL_XD CreateFromMetaRecordW(HDC_XD hDC, int order, int index, EMREXTTEXTOUTW *lpEMFR, MP_Dim pageDim, int angle, CTextRecord* pPreTR);
	BOOL_XD CreateFromMetaRecord(HDC_XD hDC, int order, int index, METARECORD FAR *lpWMFR, MP_Dim pageDim, int angle, CTextRecord* pPreTR);
	BOOL_XD CreateFromOcrRecord(HDC_XD hDC, int order, int index, const MP_Text* text, int nChars, RECT rect, MP_Dim pageDim, int angle);

	int GetOrder() const;		// レコードの番号
	int GetLength() const;		// テキストの長さ
	int GetCharIndex() const;	// テキストの全体に対するこのレコードのテキストの位置
	BOOL_XD GetLF() const;			// テキストの先頭に改行コードが入るかどうか
	MP_Pos GetOrigin() const;	// テキストの描画位置
	MP_Text *GetText() const;	// テキストの取得
	int GetOrientation() const;	// テキストの回転角度
	MP_Rect GetRect() const;	// テキストの矩形領域
	MP_Rect GetRect(int first, int end) const;	// 指定した範囲の文字列の矩形領域

	BOOL_XD IntersectRect(MP_Rect rect, long* pFirst, long* pLast, BOOL_XD bCheckWhole = FALSE) const;
};
#endif // _TEXTRCRD_H

// $History: textrcrd.h $
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 07/12/12   Time: 20:51
// Updated in $/DocuWorks/70/Source/mphcntdc
// V7.0 Unicode用関数の追加
// 
// *****************  Version 6  *****************
// User: Komoda       Date: 04/06/17   Time: 18:25
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 5  *****************
// User: Komoda       Date: 04/06/10   Time: 22:17
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 4  *****************
// User: Komoda       Date: 04/06/10   Time: 19:56
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 3  *****************
// User: Komoda       Date: 04/06/09   Time: 16:56
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 04/06/04   Time: 20:49
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 1  *****************
// User: Komoda       Date: 04/05/18   Time: 17:25
// Created in $/DocuWorks/60/Source/mphcntdc
