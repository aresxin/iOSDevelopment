// $Archive: /DocuWorks/70/Source/mphcntdc/BCMF.H $
//
// Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:28 $
// $Revision: 1.7 $

// File: BCMF.h
// Author: Hidetoshi Hamada
// Copyright(C) 1997-2004 by Fuji Xerox Co,.Ltd.All rights reserved.

#ifndef _BCMF_H
#define _BCMF_H

const int NULSIZE = 1;
const int LFSIZE = 2;

#if defined _PF_WIN32_ || defined _PF_WINCE_
static const MP_Text* const LINE_FEED = L"\r\n";
#else
static const MP_Text LINE_FEED[] = {'\r', '\n', 0};
#endif

class CMF
{
public:
	CMF(HENHMETAFILE_XD hEnhMetaFIle, MP_Dim dim, MP_Integer angle, MPCSession *pSession, CEnumControl *pEC);
	CMF(METAFILEPICT_XD *pmfp, MP_Dim dim, MP_Integer angle, MPCSession *pSession, CEnumControl *pEC);
	CMF(const MP_Text* text, int* rects, int rectNum, MP_Dim dim, MP_Integer angle, MPCSession *pSession, CEnumControl *pEC);
	virtual ~CMF();
	virtual void Destroy();

	int GetCharLength();
	int GetCharLengthWithLF();	//改行付きテキストの長さ取得
	BOOL_XD GetText(MP_Text *text, int length, MP_TextInfo *textInfo);
	BOOL_XD GetTextWithLF(MP_Text *text, int length, MP_TextInfo *textInfo); //改行付きテキストの取得
	BOOL_XD SelectText(MP_Pos start, MP_Pos end, MPCSession *pSession, MP_TextInfo **pTextInfo = NULL);
	BOOL_XD GetFindTextInfo(CBodyContentFindTextInfo *pTextInfo);

private:
	BOOL_XD GetTextPrivate(MP_Text *text, int length, BOOL_XD bWithLF, MP_TextInfo *textInfo);
	void EnumToSelectText(CBodyContentSelectTextTextInfo *pTextInfo);
	void EnumToGetTextInfo(CBodyContentFindTextInfo *pTextInfo);

private:
	MP_Dim m_dim;
	int m_scaling;
	int m_charLength;
	MP_PtrArray *m_pTextRecordArray;
};

class CDummyDC
{
public:
	CDummyDC();
	~CDummyDC();
	HDC_XD GetHDC();

private:
	HDC_XD		m_hDisplayDC;
	HDC_XD		m_hCompatibleDC;
	HBITMAP_XD	m_hCompatibleBitmap;
	HGDIOBJ_XD m_hOldObj;
};

#endif // _BCMF_H

// $History: BCMF.H $
// 
// *****************  Version 3  *****************
// User: Komoda       Date: 07/12/12   Time: 20:54
// Updated in $/DocuWorks/70/Source/mphcntdc
// V7.0 Unicode用関数の追加
// 
// *****************  Version 8  *****************
// User: K-okamoto    Date: 07/07/17   Time: 13:38
// Updated in $/DocuWorks/70/Source/mphcntdc
// VS2005対応
// 
// *****************  Version 5  *****************
// User: Komoda       Date: 04/06/09   Time: 10:50
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 4  *****************
// User: Komoda       Date: 04/06/04   Time: 20:47
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 3  *****************
// User: Komoda       Date: 04/05/18   Time: 17:27
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 04/05/17   Time: 17:42
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 1  *****************
// User: Komoda       Date: 04/03/29   Time: 20:05
// Created in $/DocuWorks/60/Source/mphcntdc
