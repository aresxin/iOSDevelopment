// $Archive: /DocuWorks/701/Source/mphcntdc/BCTEXT.H $
//
// Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:28 $
// $Revision: 1.5 $

// File: BCTEXT.h
// Author: Hidetoshi Hamada
// Copyright(C) 1997-2004 by Fuji Xerox Co,.Ltd.All rights reserved.

#ifndef _BCTEXT_H
#define _BCTEXT_H

// SELECT TEXT

class HeteroBodyCont;

class CBodyContentSelectText : public MPCSelectText
{
public:
	CBodyContentSelectText(HeteroBodyCont *pObject);
	STDMETHOD(SelectText)(MP_Pos start, MP_Pos end, MP_TextInfo **textInfo);
	STDMETHOD(SelectTextAll)(MP_TextInfo **textInfo);
private:
	HeteroBodyCont *m_pHBC;
};

// GET TEXT

class CBodyContentText : public ISpecialGetText
{
public:
	CBodyContentText(HeteroBodyCont *pObject);
	STDMETHOD(GetText)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL);
	STDMETHOD(GetTextWithLF)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL); // 改行付きテキストを取得する関数
	STDMETHOD(GetTextSpecial)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL);
	STDMETHOD(GetTextWithLFSpecial)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL);
private:
	HeteroBodyCont *m_pHBC;
};

// FIND 6

class CBodyContentFindTextInfo;

class CBodyContentFind : public MPCFind6
{
public:
	CBodyContentFind(HeteroBodyCont *pObject);
	STDMETHOD_(MPCObject *, Find)(MPCTextSearch *pTextSearch, MP_TextInfo **textInfo, MP_FindInfo *findInfo = NULL, HRESULT *result = NULL);
private:
	void GetFindTextInfo(CBodyContentFindTextInfo* pMyTextInfo);
	HeteroBodyCont *m_pHBC;
};

// PDCache

class CMF;

class CEnumControl
{
public:
	virtual BOOL_XD IsAborted() = 0;
};

class CPSCacheEnumControl : public CEnumControl
{
public:
	CPSCacheEnumControl(BOOL_XD bInit);
	~CPSCacheEnumControl();
	BOOL_XD IsAborted();
	void SetAbort(BOOL_XD bAbort);

protected:
	CRITICAL_SECTION m_cs;
	BOOL_XD m_bAborted;
};

class CBodyContentPDCache : public MP_PDCache
{
public:
	CBodyContentPDCache(HeteroBodyCont *pObject);
	~CBodyContentPDCache();

	STDMETHOD(CreateCache)(MP_CacheCreateMode mode = MP_CCM_Delayed);
	STDMETHOD(DeleteCache)();

	CMF *GetMF(BOOL_XD bCache = TRUE);
	void ReleaseMF();

	enum {
		PDTYPE_UNKNOWN = 0,
		PDTYPE_WMF = 11,
		PDTYPE_EMF = 12,
		PDTYPE_IMAGE = 20,
	};
	int GetPDType();

protected:
	BOOL_XD SetupPD();
	void DeleteCacheInternal();
	CMF *GetMFInternal(BOOL_XD bCache);

private:
	enum CacheStatus {
		CS_NONE = 0,
		CS_CREATING,
		CS_CACHED,
		CS_NOT_CACHED,
	};
	HeteroBodyCont *m_pHBC;
	MP_PD *m_pPD;
	CRITICAL_SECTION m_csMF;
	CMF *m_pMF;
	BOOL_XD m_bCreateAsCache;
	CacheStatus m_status;
	CPSCacheEnumControl m_ec;
	int m_pdType;
};


// TEXT INFO

class CTextRecord;
class CBodyContentSelectTextTextInfo : public MP_TextInfo
{
public:
	CBodyContentSelectTextTextInfo(MP_Pos start, MP_Pos end, MPCSession *pSession);
	~CBodyContentSelectTextTextInfo();
	STDMETHOD(Destroy)();

public:
	BOOL_XD Found();
	BOOL_XD FixedUp();
	BOOL_XD Match(CTextRecord *pTR);
	void Add(CTextRecord *pTR);
	CTextRecord* GetLast();
	BOOL_XD Intersect(CTextRecord *pTR);

    // 12.03.02 Bito - テキスト選択・検索対応
    // 選択表示に使用する4点座標(point)を計算する処理を追加
    void Convert4PointsFromTextRect();

private:
	struct MatchInfo
	{
		MP_Rect rect;
		BOOL_XD match;
		long record;
		long pos;
		long charIndex;
	};

	int m_currentRecord;
	MPCSession *m_pSession;
	BOOL_XD m_bFound;
	MatchInfo m_start;
	MatchInfo m_end;
	MatchInfo m_first;
	MatchInfo m_last;
	MP_Rect m_rect;

	MP_PtrArray *m_pTextRecordArray;
};

class CBodyContentFindTextInfo : public MP_TextInfo
{
public:
	CBodyContentFindTextInfo(MPCSession *pSession);
	~CBodyContentFindTextInfo();
	STDMETHOD(Destroy)();

public:
	void Add(CTextRecord *pTR);
	CTextRecord *GetAt(int at);
	int GetSize();

    // 12.03.02 Bito - テキスト選択・検索対応
    // 選択表示に使用する4点座標(point)を計算する処理を追加
    void Convert4PointsFromTextRect();
    
private:
	MP_PtrArray *m_pTextRecordArray;
};

#endif // _BCTEXT_H

// $History: BCTEXT.H $
// 
// *****************  Version 4  *****************
// User: Komoda       Date: 09/02/05   Time: 21:17
// Updated in $/DocuWorks/701/Source/mphcntdc
// AR16240 GetTextSpecialが動作しない問題の修正
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 08/07/25   Time: 21:12
// Updated in $/DocuWorks/70/Source/mphcntdc
// AR15339
// 
// *****************  Version 9  *****************
// User: Komoda       Date: 04/09/17   Time: 10:54
// Updated in $/DocuWorks/60/Source/mphcntdc
// AR10915対応
// 
// *****************  Version 8  *****************
// User: Komoda       Date: 04/06/09   Time: 10:59
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 7  *****************
// User: Komoda       Date: 04/06/04   Time: 21:17
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 6  *****************
// User: Komoda       Date: 04/06/04   Time: 20:50
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 5  *****************
// User: Komoda       Date: 04/05/18   Time: 17:29
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 4  *****************
// User: Komoda       Date: 04/05/17   Time: 17:44
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 3  *****************
// User: Komoda       Date: 04/04/01   Time: 14:47
// Updated in $/DocuWorks/60/Source/mphcntdc
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 04/03/29   Time: 20:02
// Updated in $/DocuWorks/60/Source/mphcntdc
// MPCFind, MP_TextInfoの変更に伴う変更
