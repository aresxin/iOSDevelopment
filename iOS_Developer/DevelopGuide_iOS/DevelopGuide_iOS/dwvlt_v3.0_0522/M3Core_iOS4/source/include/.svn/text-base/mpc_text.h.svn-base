// File: MPC_TEXT.h
// Author: Hidetoshi Hamada
// Copyright(C) 1997-2007 by Fuji Xerox Co,.Ltd.All rights reserved.

#ifndef _MPC_TEXT_H_
#define _MPC_TEXT_H_

#ifndef MPCOREAPI_H
#include "mpc_api.h"
#endif



struct MP_TextRect
{
	MP_Integer orientation;
	MP_Pos origin;
	MP_Rect	rect;
    
    // 12.03.02 Bito
    // 矩形領域から計算した4点の座標を格納
#ifdef _M3CORE_MP_
    MP_Pos point[4];
#endif
};

const int MPC_TEXT_FIND_FIT_TEXT_LEN = 512;

typedef enum mpc_text_foud_obj_type {
	MPC_TEXT_FOUND_OBJ_TYPE_NIL = 0,
	MPC_TEXT_FOUND_OBJ_TYPE_EMF,
	MPC_TEXT_FOUND_OBJ_TYPE_WMF,
	MPC_TEXT_FOUND_OBJ_TYPE_OCR,
	MPC_TEXT_FOUND_OBJ_TYPE_TEXT_ANN,
	MPC_TEXT_FOUND_OBJ_TYPE_STAMP_ANN,
	MPC_TEXT_FOUND_OBJ_TYPE_HEADER_FOOTER
} MPC_TEXT_FOUND_OBJ_TYPE;

struct	MP_TextInfo
{
	MP_Integer nStartIndex;			// 最初の文字のインデックス
	MP_Integer nEndIndex;			// 最後の文字の次のインデックス
	MP_Integer nCharLength;
	MP_Integer nCharLengthWithLF;	// 改行挿入した場合の文字列長
	// The follows are for Body Text. So the value may be 0 / NULL.
	MP_Integer nRecordCount;		// TextRectの個数
	MP_TextRect *pTextRects;

	//検索でヒットしたオブジェクトのタイプ
	MPC_TEXT_FOUND_OBJ_TYPE	foundObjectType;

	STDMETHOD(Destroy)() PURE;
};

struct	MP_HitText
{
	MP_Text	beforeText[MPC_TEXT_FIND_FIT_TEXT_LEN + 1];
	MP_Text	hitText[MPC_TEXT_FIND_FIT_TEXT_LEN + 1];
	MP_Text	afterText[MPC_TEXT_FIND_FIT_TEXT_LEN + 1];
};

struct	MP_FindInfo
{
	MPCObject *pObject;
	MP_TextInfo *pTextInfo;
};

//for Find4
typedef unsigned long MP_FindParam;
//find target
const MP_FindParam MP_FT_Null = 0x00000000;				//
const MP_FindParam MP_FT_All = 0x0000ffff;				// AR12029対応で追加
const MP_FindParam MP_FT_AppPage = 0x00000001;			// text in application's pages
const MP_FindParam MP_FT_TextAnnotation = 0x00000002;	// text in text annotations
const MP_FindParam MP_FT_ImgPage = 0x00000004;			// text in OCR-processed pages 
const MP_FindParam MP_FT_StampAnnotation = 0x00000008;	// text in Stump annotations
const MP_FindParam MP_FT_HeaderAndFooter = 0x00000010;	// text in Header and Footer on Page

const MP_FindParam MP_FI_Null = 0x00000000;				//
const MP_FindParam MP_FI_All = 0xffff0000;				// AR12029対応で追加
const MP_FindParam MP_FI_Case = 0x00010000;				// ignore case of characters
const MP_FindParam MP_FI_ZenHan = 0x00020000;			// ignore width of S-JIS multi-byte characters
const MP_FindParam MP_FI_HiraKata = 0x00040000;			// ignore hiragana/katakana

const MP_FindParam MP_FD_Forward = 0x00000000;	 		//Forward Find
const MP_FindParam MP_FD_Backward = 0x01000000;			//backward find

// followings are result of MP_PDCache::GetCacheStatus
const HRESULT MP_S_AVAILABLE = 0x80000001;
const HRESULT MP_S_PREPARING = 0x80000010;
const HRESULT MP_S_NOT_AVAILABLE = 0x80000000;
const HRESULT MP_S_NA = 0x00000000;

#define	_MAX_FIND_TEXT	255

typedef	unsigned long MP_CacheCreateMode;
const MP_CacheCreateMode MP_CCM_Delayed = 0x00000001L;
const MP_CacheCreateMode MP_CCM_Foreground = 0x00000002L;
const MP_CacheCreateMode MP_CCM_Background = 0x00000003L;

MPC_EXTERN_GUID(IID_MPCText, 0x131A);

/*
	GetText および GetTextWithLF
	引数textがNULLの場合は、NUL文字を含んだ文字数、あるいはMP_S_FALSEを返す。
	引数textがNULLでない場合は、MP_S_OK, MP_S_FALSEのどちらかを返す。
	テキストを出力する際は、NUL文字まで出力する。
*/

mpinterface MPCText
{
	STDMETHOD(GetText)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL) PURE;
	STDMETHOD(GetTextWithLF)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL) PURE; //get text with line feeds
};

MPC_EXTERN_GUID(IID_MPCSelectText, 0x131B);

mpinterface MPCSelectText
{
	STDMETHOD(SelectText)(MP_Pos start, MP_Pos end, MP_TextInfo **textInfo) PURE;
	STDMETHOD(SelectTextAll)(MP_TextInfo **textInfo) PURE;// added by yusa 99/6/11
};

mpinterface MPCTextSearch
{
	STDMETHOD(SetParam)(MP_FindParam param, const MP_Text *text) PURE;
	STDMETHOD(Find)(MP_Text *pszContentText, MP_TextInfo* textInfoResult, MP_TextInfo* textInfoInput) PURE;
	STDMETHOD_(MP_FindParam,GetFindParam)() PURE;
	STDMETHOD(GetHitText)(MP_HitText* hitText) PURE;
	STDMETHOD(Destroy)() PURE;
};

DLLBINDFUNC_(MPCTextSearch*,MPCCreateTextSearch)(MPCSession *pSession, HRESULT *result = NULL);

MPC_EXTERN_GUID(IID_MPCFind6, 0x132F);

mpinterface MPCFind6
{
	STDMETHOD_(MPCObject *,Find)(MPCTextSearch *pTextSearch, MP_TextInfo **textInfo, MP_FindInfo *findInfo = NULL, HRESULT *result = NULL) PURE;
};

MPC_EXTERN_GUID(IID_MP_PDCache, 0x131D);

mpinterface MP_PDCache
{
	STDMETHOD(CreateCache)(MP_CacheCreateMode mode = MP_CCM_Delayed) PURE;
	STDMETHOD(DeleteCache)() PURE;
};

#endif	// _MPC_TEXT_H_

//
//CHANGE LOG
//97.10.21 - Ichiriki - \\DocuWorks\user0\hamada\include（濱田作成）をコアに取り込み
//99.06.03 - ysato - V4検索I/F(Fond4)の追加
//04.03.26 - Komoda - V6他言語対応:テキストの型,検索I/Fの変更
//05.02.14 - Nakamura - AR12029の修正。MP_FT_All, MP_FI_Allを追加。
//07.08.10 - Komoda - V7 MP_Textをmpc_api.hに移動
