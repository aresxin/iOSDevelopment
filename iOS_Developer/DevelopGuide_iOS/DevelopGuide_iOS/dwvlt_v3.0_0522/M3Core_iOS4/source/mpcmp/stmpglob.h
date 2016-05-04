// File: STMPGLOB.H
// Author: HIDEO FUJII
// Copyright (C) 1996 by Fuji Xerox Co., Ltd.  All rights reserved.

#ifndef _STMPGLOB_H_
#define _STMPGLOB_H_

#pragma warning(disable: 4996)

//#include "stdafx.h"

#include <mpc_api.h>
#include <mpc_gui.h>
#include <mpc_textattribute.h>

#include "stampcmm.h"

const COLORREF BLACK = RGB(0x00, 0x00, 0x00);	// 黒

/**********************************************************************
 *		前バージョンの文字列を分割するための関数
 **********************************************************************/
extern inline BOOL_XD DevDateForPrevVersion( LPCSTR bufPrev, LPSTR bufYear, LPSTR bufMonth, LPSTR bufDay )
{
	BOOL_XD bAPS, bPrd1, bPrd2, bErr;
	bAPS = bPrd1 = bPrd2 = bErr = FALSE;
	while( *bufPrev != '\0' && !bErr )
	{
		switch( *bufPrev ){
            case '\'':
                if( bAPS ) bErr = TRUE;
                else bAPS = TRUE;
                break;
            case '.':
                if( !bAPS || bPrd2 )
                {
                    bErr = TRUE;
                    break;
                }
                if( bPrd1 ) bPrd2 = TRUE;
                else bPrd1 = TRUE;
                break;
            default:
                if( bPrd2 ){ *bufDay = *bufPrev; bufDay++;}
                else if( bPrd1 ){ *bufMonth = *bufPrev; bufMonth++;}
                else{ *bufYear = *bufPrev; bufYear++;}
                break;
		}
		bufPrev++;
	}
	*bufYear = '\0'; *bufMonth = '\0'; *bufDay = '\0';
	return !bErr;
}

/**********************************************************************
 *		モデルからデータを取得するための関数群
 **********************************************************************/

// DW7.0 MultiByte/Unicodeで格納してもよい属性 : STAMPATT_NAME, STAMPATT_POST
// これらの属性に対しては Get/SetAttribute を直接使用してはならない

static inline MPCTextAttributeHelper* StampGetTextAttributeHelper(MPCObject* pObj)
{
	if (pObj != NULL) {
		MPCSession* pSession = pObj->GetSession();
		if (pSession != NULL) {
			void* ptr = pSession->GetInterface(IID_MPCTextAttributeHelper);
			return (MPCTextAttributeHelper*)ptr;
		}
	}
	return NULL;
}

extern inline STDMETHODIMP	StampGetMultiByteAttribute(MPCObject* pObj, MP_AName* aname, LPSTR buf, int length )
{
	// MultiByte/Unicodeで格納してよい属性から、デフォルト言語のMultiByteとして読み出す
    
	if (buf != NULL) buf[0] = 0;
	MPCTextAttributeHelper* textattr = StampGetTextAttributeHelper(pObj);
	if (textattr == NULL) return MP_E_UNEXPECTED;
    
	MP_MBString str;
	MP_TAType tatype = 0;
	HRESULT hres = textattr->GetMBText(pObj, aname, CP_ACP, str, tatype);
	if (hres < 0) return hres;
	// Unicode属性の場合はデフォルト言語のMultiByteに変換される
	// MultiByte属性の場合はそのまま読み出される
    
	int needlength = str.GetLength() + 1;
	if (buf != NULL) {
		if (length < needlength) return MP_E_INSUFFICIENT_BUFFER;
		strncpy(buf, str, needlength);
		return MP_NOERROR;
	}
	return needlength;
}

extern inline STDMETHODIMP	GetStampNameAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING+1 )
{
	return StampGetMultiByteAttribute(pObj, STAMPATT_NAME, buf, bufLong);
};			//下段表示文字列

extern inline STDMETHODIMP	GetStampPostAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING+1 )
{
	return StampGetMultiByteAttribute(pObj, STAMPATT_POST, buf, bufLong);
};			//上段表示文字列

extern inline STDMETHODIMP	GetStampDateAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING+1 )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { bufLong, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_DATE , &avalue);
	return hres;
};			//日付表示文字列

extern inline STDMETHODIMP	GetStampColorAttr(MPCObject* pObj, COLORREF* buf )
{	
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { sizeof( COLORREF ), MP_A_INT, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_COLOR , &avalue);
	if( hres != MP_NOERROR ) *buf = BLACK;
	return hres;
};		//スタンプの色

extern inline BOOL_XD	GetStampDateFlagAttr(MPCObject* pObj )
{
	if(pObj == NULL) return FALSE;
	BOOL_XD bHandDating = FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&bHandDating };
	HRESULT hres = pObj->GetAttribute(STAMPATT_DATEFLAG , &avalue);
	return bHandDating;
};	//日付を自動設定するかどうか


/////////
extern inline STDMETHODIMP	GetStampYearAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING+1 )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { bufLong, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_YEAR , &avalue);
	return hres;
};			//年表示文字列

extern inline STDMETHODIMP	GetStampMonthAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING+1 )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { bufLong, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_MONTH, &avalue);
	return hres;
};			//月表示文字列

extern inline STDMETHODIMP	GetStampDayAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING+1 )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { bufLong, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_DAY , &avalue);
	return hres;
};			//日表示文字列

extern inline STDMETHODIMP	GetStampYearMonthDayAttr(MPCObject* pObj, LPSTR bufYear, LPSTR bufMonth, LPSTR bufDay )
{
	if( ::GetStampYearAttr( pObj, bufYear ) != MP_NOERROR || ::GetStampMonthAttr( pObj, bufMonth ) != MP_NOERROR || ::GetStampDayAttr( pObj, bufDay ) != MP_NOERROR )
	{
		char bufPrev[MAX_STAMP_STRING];
		HRESULT hres = ::GetStampDateAttr( pObj, bufPrev );
		if(  hres == MP_NOERROR )
		{
			if( !::DevDateForPrevVersion( bufPrev, bufYear, bufMonth, bufDay ) )
			{ *bufYear = '\0'; *bufMonth = '\0'; *bufDay = '\0';}
		}
		else
		{
			*bufYear = '\0'; *bufMonth = '\0'; *bufDay = '\0';
			return hres;
		}
	}
	return MP_NOERROR;
};			//年月日表示文字列

extern inline BOOL_XD	GetStampEraAttr(MPCObject* pObj )
{
	if(pObj == NULL) return FALSE;
	BOOL_XD bEra = FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&bEra };
	HRESULT hres = pObj->GetAttribute(STAMPATT_ERA , &avalue);
	return bEra;
};	//基準年指定かどうか

extern inline STDMETHODIMP	GetStampBaseyearAttr(MPCObject* pObj, MP_Integer* buf )
{	
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { sizeof( MP_Integer ), MP_A_INT, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_BASEYEAR , &avalue);
	if( hres != MP_NOERROR ) *buf = 1;
	return hres;
};		//基準年の値

extern inline STDMETHODIMP	GetStampPrefixAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_PREFIX_STRING+1 )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { bufLong, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_PREFIX , &avalue);
	return hres;
};			//日付の先頭に表示される文字

extern inline STDMETHODIMP GetStampDateFormatAttr(MPCObject* pObj, LPSTR buf, int bufLong = MAX_STAMP_STRING + 1)
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { bufLong, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_DATEFORMAT, &avalue);
	return hres;
};	//日付の書式文字列

extern inline STDMETHODIMP GetStampDateOrderAttr(MPCObject* pObj, MP_Integer* buf)
{	
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void *)buf };
	HRESULT hres = pObj->GetAttribute(STAMPATT_DATEORDER, &avalue);
	return hres;
};	//年月日の表示順

/**********************************************************************
 *		モデルにデータを設定するための関数群
 **********************************************************************/

static inline STDMETHODIMP	StampSetMultiByteAttribute(MPCObject* pObj, MP_AName* aname, LPCSTR buf )
{
	// MultiByte/Unicodeで格納される属性に、デフォルト言語のMultiByteとして格納する
    
	MPCTextAttributeHelper* textattr = StampGetTextAttributeHelper(pObj);
	if (textattr == NULL) return MP_E_UNEXPECTED;
	return textattr->SetMBText(pObj, aname, CP_ACP, buf, MP_TA_MULTIBYTE);
}

extern inline STDMETHODIMP	SetStampNameAttr(MPCObject* pObj, LPCSTR buf )
{
	return StampSetMultiByteAttribute(pObj, STAMPATT_NAME, buf);
}			//下段表示文字列

extern inline STDMETHODIMP	SetStampPostAttr(MPCObject* pObj, LPCSTR buf )
{
	return StampSetMultiByteAttribute(pObj, STAMPATT_POST, buf);
};			//上段表示文字列

extern inline STDMETHODIMP	SetStampDateAttr(MPCObject* pObj, LPCSTR buf )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue;
	avalue.atype = MP_A_OCTS;
	avalue.adata = (void *)buf;
	if(buf == NULL ) 
		avalue.asize = 0;
	else
		avalue.asize = (MP_Integer)strlen(buf)+1;
    
	HRESULT hres = pObj->SetAttribute(STAMPATT_DATE , &avalue);
	return hres;
};			//日付表示文字列

extern inline STDMETHODIMP	SetStampDateFlagAttr(MPCObject* pObj , BOOL_XD flag)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&flag };
	return pObj->SetAttribute(STAMPATT_DATEFLAG , &avalue);
};	//日付を自動設定するかどうか

extern inline STDMETHODIMP	SetStampColorAttr(MPCObject* pObj , COLORREF color)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(COLORREF), MP_A_INT, (void*)&color };
	return pObj->SetAttribute(STAMPATT_COLOR , &avalue);
};	//スタンプの色


//////////////////////
extern inline STDMETHODIMP	SetStampYearAttr(MPCObject* pObj, LPCSTR buf )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { (MP_Integer)strlen(buf)+1, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->SetAttribute(STAMPATT_YEAR, &avalue);
	return hres;
};			//年表示文字列

extern inline STDMETHODIMP	SetStampMonthAttr(MPCObject* pObj, LPCSTR buf )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { (MP_Integer)strlen(buf)+1, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->SetAttribute(STAMPATT_MONTH , &avalue);
	return hres;
};			//月表示文字列

extern inline STDMETHODIMP	SetStampDayAttr(MPCObject* pObj, LPCSTR buf )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { (MP_Integer)strlen(buf)+1, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->SetAttribute(STAMPATT_DAY , &avalue);
	return hres;
};			//日表示文字列

extern inline STDMETHODIMP SetStampYearMonthDayAttr( MPCObject* pObj, LPCSTR bufYear, LPCSTR bufMonth, LPCSTR bufDay )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	::SetStampYearAttr( pObj, bufYear );
	::SetStampMonthAttr( pObj, bufMonth );
	::SetStampDayAttr( pObj, bufDay );
	//以前のバージョンの属性があれば削除する。
	char bufPrev[MAX_STAMP_STRING + 1];
	if( ::GetStampDateAttr( pObj, bufPrev ) == MP_NOERROR )
		::SetStampDateAttr( pObj, NULL );
	return MP_NOERROR;
}

extern inline BOOL_XD	SetStampEraAttr(MPCObject* pObj , BOOL_XD bEra )
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&bEra };
	return pObj->SetAttribute(STAMPATT_ERA , &avalue);
};	//基準年指定かどうか

extern inline STDMETHODIMP	SetStampBaseyearAttr(MPCObject* pObj, MP_Integer baseyear )
{	
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { sizeof( MP_Integer ), MP_A_INT, (void *)&baseyear };
	return pObj->SetAttribute(STAMPATT_BASEYEAR , &avalue);
};		//基準年の値

extern inline STDMETHODIMP	SetStampPrefixAttr(MPCObject* pObj, LPSTR buf)
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { (MP_Integer)strlen(buf)+1, MP_A_OCTS, (void *)buf };
	return pObj->SetAttribute(STAMPATT_PREFIX, &avalue);
};			//日付の先頭に表示される文字

extern inline STDMETHODIMP SetStampDateFormatAttr(MPCObject* pObj, LPCSTR buf)
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { lstrlen(buf) + 1, MP_A_OCTS, (void *)buf };
	return pObj->SetAttribute(STAMPATT_DATEFORMAT, &avalue);
};			//日付の書式文字列

extern inline STDMETHODIMP SetStampDateOrderAttr(MPCObject* pObj, MP_Integer dateOrder)
{	
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void *)&dateOrder };
	return pObj->SetAttribute(STAMPATT_DATEORDER, &avalue);
};		//年月日の表示順

#pragma warning(default: 4996)

#endif	//	_STMPGLOB_H_

//
// CHANGE LOG
// 96.12.02	- Fujii -	Create
// 2005.11.09 - Nakazawa - 64bit対応
// 2006.08.24 - Kawaharada - V6.2 日付書式変更対応