// File: LINKGLOB.H
// Author: HIDEO FUJII
// Copyright (C) 1996 by Fuji Xerox Co., Ltd.  All rights reserved.

#ifndef _LINKGLOB_H_
#define _LINKGLOB_H_

#pragma warning(disable: 4996)

#ifndef _M3CORE_MP_
#include <datatype.h>
#endif	///2002/04/09 多重定義になるので、#ifndef〜#endifで制御

//
//	@ (s)
//		ViewerLight / for Webでリンクアノテの操作を行うため、
//		不必要な関数は、#ifndef で区別した。	('99/02/23 T.Matsuo)
//
//		言語依存モジュールからデフォルトのLOGFONT情報を取得するため、
//		このヘッダーファイルをincludeしているプロジェクトは、
//		dwlocale.libをリンクするなどをする必要があります。
//
#ifndef _M3CORE_MP_
const MP_Dim MIN_LINK_SIZE = {500, 500};
#endif	//_M3CORE_MP_

/**********************************************************************
 *		モデルからデータを取得するための関数群
 **********************************************************************/

// DW7.0 MultiByte/Unicodeで格納してもよい属性 : LINKATT_TITLESTR, LINKATT_URLSTR,
//  LINKATT_XDWSTR, LINKATT_SHEAFNAME, LINKATT_USER_TOOLTIP_STR, LINKATT_LINKTITLE,
//  LINKATT_OTHERFILE_PATH, LINKATT_MAILADDRESS
// これらの属性に対しては Get/SetAttribute を直接使用してはならない

static inline MPCTextAttributeHelper* LinkGetTextAttributeHelper(MPCObject* pObj)
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

static inline STDMETHODIMP	LinkGetMultiByteAttribute(MPCObject* pObj, const MP_AName* aname, LPSTR buf, int length )
{
	// MultiByte/Unicodeで格納してよい属性から、デフォルト言語のMultiByteとして読み出す

	if (buf != NULL) buf[0] = 0;
	MPCTextAttributeHelper* textattr = LinkGetTextAttributeHelper(pObj);
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

static inline STDMETHODIMP	LinkGetMultiByteAttribute(MPCObject* pObj, const MP_AName* aname, LPSTR buf, int* pnlength )
{
	// 最後の引数がバッファ長のポインタになっている関数

	int length = 0;
	if (buf != NULL) {
		buf[0] = 0;
		if (pnlength != NULL) length = *pnlength;
	}

	HRESULT hres = LinkGetMultiByteAttribute(pObj, aname, buf, length);

	if (buf == NULL) {
		if (hres >= 0 && pnlength != NULL) *pnlength = hres;
	}
	if (hres >= 0) hres = MP_NOERROR;
	return hres;
}

//
//	この関数は、VLT/forWebでは使用しない
//	↑V50から、タイトルへのジャンプがはいるので、infdefは削除
//#ifndef _M3CORE_MP_
extern inline STDMETHODIMP	GetLinkTitleStrAttr(MPCObject* pObj, LPSTR buf )
{
	//buf: 呼び出し元で十分な領域を確保しておいてください
	int length = 256 + 1; // MAX_LINK_URL + 1
	return LinkGetMultiByteAttribute(pObj, LINKATT_TITLESTR, buf, length);
};			//リンクタイトル文字列

//#endif	//_M3CORE_MP_

/**
* @brief	URL文字列の取得
* @param [in]
* @param [out]
* @param [i/o]
* @return 
* @retval	エラーが発生した場合、buf,pnLengthの値は不定
* @retval 
* @note		AR12633対応で引数を追加
*/	
extern inline STDMETHODIMP	GetLinkURLStrAttr(MPCObject* pObj, LPSTR buf, int *pnLength )
{
	return LinkGetMultiByteAttribute(pObj, LINKATT_URLSTR, buf, pnLength);
}			//URL文字列

/**
* @brief	DW文書のパスを取得
* @param [in]
* @param [out]
* @param [i/o]
* @return 
* @retval	エラーが発生した場合、buf,pnLengthの値は不定
* @retval 
* @note		AR12633対応で引数を追加
*/	
extern inline STDMETHODIMP	GetLinkXDWStrAttr(MPCObject* pObj, LPSTR buf, int *pnlength )
{
	return LinkGetMultiByteAttribute(pObj, LINKATT_XDWSTR, buf, pnlength);
}			//XDW文書パス文字列

//
//	この関数は、VLT/forWebでは使用しない
//
#ifndef _M3CORE_MP_
extern inline BOOL_XD	GetLinkIsDisplayIconAttr(MPCObject* pObj )
{
	if(pObj == NULL) return FALSE;
	BOOL_XD bDisplay = FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&bDisplay };
	HRESULT hres = pObj->GetAttribute(LINKATT_ISDISPLAYICON , &avalue);
	return bDisplay;
};	//アイコンを表示するかどうか
#endif	//_M3CORE_MP_


extern inline int	GetLinkLinkToAttr(MPCObject* pObj )
{
	if(pObj == NULL) return FALSE;
	int nLinkTo = LINK_TO_ME;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nLinkTo };
	HRESULT hres = pObj->GetAttribute(LINKATT_LINKTO , &avalue);
	return nLinkTo;
};	//リンク先がどこか(自分自身:LINK_TO_ME、URL:LINK_TO_URL、XDW:LINK_TO_XDW)

extern inline int	GetLinkPageNumAttr(MPCObject* pObj )
{
	if(pObj == NULL) return FALSE;
	int nPageNum = 1;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nPageNum };
	HRESULT hres = pObj->GetAttribute(LINKATT_XDWPAGENUM , &avalue);
	return nPageNum;
};	//XDW文書のページ番号（0ならPROFILE)

//
//	for DocuWorks V4.0 Viewer / Viewer Light / for Web
//
//
//  機能     : 「透過表示」の取得関数
//  
//  機能説明 : 
//  
//  返り値   : 設定されている場合はTRUE、それ以外はFALSEを返す
//  
//  備考     : 
//  
extern inline BOOL_XD	GetLinkIsTransparentAttr(MPCObject* pObj)
{
	if(pObj == NULL) return FALSE;
	BOOL_XD bTransparent = FALSE;	///初期値は、"透過ではない"
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bTransparent };
	HRESULT hres = pObj->GetAttribute(LINKATT_TRANSPARENT , &avalue);
	return bTransparent;
}

//
//  機能     : 「自動リサイズ」の取得関数
//  
//  機能説明 : 
//  
//  返り値   : チェックされているならTRUE、それ以外はFALSE
//  
//  備考     : 
//  
extern inline BOOL_XD GetLinkIsAutoResizeAttr(MPCObject* pObj)
{
	if(pObj == NULL) return FALSE;
	BOOL_XD bAutoResize = TRUE;	///V30に合わせて初期値はTRUE
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bAutoResize };
	HRESULT hres = pObj->GetAttribute(LINKATT_AUTO_RESIZE , &avalue);
	return bAutoResize;
}


//
//  機能     : 「ページ設定」の取得関数
//  
//  機能説明 : 
//  
//  返り値   : 0：「この文書のページ」、1:「このバインダの通しページ」、
//			   2：「このバインダの他の文書のページ」 が返る
//  
//  備考     : 
//  
extern inline int GetLinkPageCheckAttr(MPCObject* pObj)
{
	if(pObj == NULL) return FALSE;
	int nPageAttr = 0;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&nPageAttr };
	HRESULT hres = pObj->GetAttribute(LINKATT_PAGECHECK , &avalue);
	return nPageAttr;
}


//
//  機能     : 「内部文書名」取得関数
//  
//  機能説明 : 
//  
//  返り値   : 取得できれば、NP_NOERRORが返る。この時、bufに内部文書名が入っている。
//  
//  備考     : 
//  @note	:	AR12633対応で引数を追加
//
extern inline STDMETHODIMP GetLinkInternalSheafNameAttr(MPCObject* pObj , LPSTR buf, int *pnLength)
{
	return LinkGetMultiByteAttribute(pObj, LINKATT_SHEAFNAME, buf, pnLength);
}

//
// 関数名	:	GetLinkMailAddress	
//
// 機能		:	リンクアノテーションに設定されたメールアドレスを取得する
//
// 機能説明	: 
//
// 返り値	: 
//
// 備考		:	V50新規
//  @note	:	AR12633対応で引数を追加
//	
extern inline STDMETHODIMP GetLinkMailAddress( MPCObject* pObj , LPSTR buf,int *pnLength)
{
	return LinkGetMultiByteAttribute(pObj, LINKATT_MAILADDRESS, buf, pnLength);
}

//
// 関数名	:	GetLinkOtherFilePath
//
// 機能		: 
//
// 機能説明	:	その他のファイル、へのリンクで設定されているパスを取得する
//
// 返り値	: 
//
// 備考		:	V50新規
// @note	:	AR12633対応のために引数を追加
//	
extern inline STDMETHODIMP GetLinkOtherFilePath( MPCObject* pObj , LPSTR buf , int* pnLength)
{
	return LinkGetMultiByteAttribute(pObj, LINKATT_OTHERFILE_PATH, buf, pnLength);
}			//その他のファイル

//
// 関数名	:	GetLinkOtherFileRelative
//
// 機能		: 
//
// 機能説明	:	その他のファイルで、相対パスチェックの値の取得
//
// 返り値	:	
//	
// 備考		:	V50新規 
//	
extern inline STDMETHODIMP GetLinkOtherFileRelative( MPCObject* pObj , BOOL_XD* bRelative)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)bRelative };
	HRESULT hres = pObj->GetAttribute(LINKATT_OTHERFILE_RELATIVE , &avalue);
	return hres;
}

//
// 関数名	:	GetLinkDWLinkType
//
// 機能		: 
//
// 機能説明	:	DocuWorksのリンクの中で、ページ指定なのか？リンクアノテへのジャンプなのか？
//				を取得する
//
// 返り値	: 
//
// 備考		:	V50新規。
//	
extern inline int GetLinkDWLinkType( MPCObject* pObj)// , int* nLinkType )
{
	if(pObj == NULL) return FALSE;
	int nDWLinkType = LINK_TO_DWTYPE_PAGE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&nDWLinkType };
	HRESULT hres = pObj->GetAttribute(LINKATT_DW_JUMPTYPE , &avalue);
	return nDWLinkType;
}

//
// 関数名	:	GetLinkDWFileRelative
//
// 機能		: 
//
// 機能説明	:	DocuWorks文書リンクの、その他のファイルでの、相対パスチェックの値の取得
//
// 返り値	:	
//	
// 備考		:	V50新規 
//	
extern inline STDMETHODIMP GetLinkDWFileRelative( MPCObject* pObj , BOOL_XD* bRelative)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)bRelative };
	HRESULT hres = pObj->GetAttribute(LINKATT_DW_RELATIVE , &avalue);
	return hres;
}

//
// 関数名	:	GetLinkJumpName
//
// 機能		: 
//
// 機能説明	: 
//
// 返り値	: 
//
// 備考		: 
//	@note	:	AR12633対応で引数を追加
//	
extern inline STDMETHODIMP GetLinkJumpTitle(MPCObject* pObj , LPSTR buf, int* pnLength)
{
	return LinkGetMultiByteAttribute(pObj, LINKATT_LINKTITLE, buf, pnLength);
}

//
// 関数名	:	GetLinkUserTooltip
//
// 機能		:	
//
// 機能説明	:	ツールチップを設定するかどうかの属性の取得
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP GetLinkUserTooltip( MPCObject* pObj , BOOL_XD* bUserTooltip)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)bUserTooltip };
	HRESULT hres = pObj->GetAttribute(LINKATT_USERTOOLTIP , &avalue);
	return hres;
}

//
// 関数名	:	GetLinkUserTooltipString
//
// 機能		: 
//
// 機能説明	:	ツールチップ文字列属性を取得
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP GetLinkUserTooltipString( MPCObject* pObj , LPSTR buf )
{
	int length = 512; // MAX_TOOLTIP_LENGTH_BUFFER linkcmm.h
	return LinkGetMultiByteAttribute(pObj, LINKATT_USER_TOOLTIP_STR, buf, length);
}

//
// 関数名	:	GetLinkDWFileType
//
// 機能		: 
//
// 機能説明	:	DocuWorks文書へのリンクで、このファイル/他のファイル属性を取得する。
//
// 返り値	: 
//
// 備考		:	V50以降で有効。V4xは、GetLinkLinkToAttrを使用しているので、
//				V50以降で互換性の維持に注意すること。
//	
extern inline STDMETHODIMP	GetLinkDWFileType(MPCObject* pObj , int* nDWFileType)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)nDWFileType };
	return pObj->GetAttribute(LINKATT_DWJUMP_FILETYPE, &avalue);
};

//
//	これ以降は、VLT/forWebでは使用しない
//	
#ifndef _M3CORE_MP_
/*
//以下、タイトル文字の属性//
*/
extern inline STDMETHODIMP	GetLinkTitleColorAttr(MPCObject* pObj, COLORREF* buf )
{	
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { sizeof( COLORREF ), MP_A_INT, (void *)buf };
	HRESULT hres = pObj->GetAttribute(LINKATT_TITLE_COLOR , &avalue);
	if( hres != MP_NOERROR ) *buf = BLACK;
	return hres;
};		//タイトル文字の色

extern inline STDMETHODIMP	GetLinkTitleFaceNameAttr(MPCObject* pObj, char *fontName)
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = {LF_FACESIZE, MP_A_OCTS, (void *) fontName};
	HRESULT hres = pObj->GetAttribute(LINKATT_TITLE_FACE, &avalue);

	// 言語依存モジュールから値を取得
	if( hres != MP_NOERROR) {
		LOGFONT defaultLogFont = GetDefaultLogFont();
		strcpy(fontName, defaultLogFont.lfFaceName);
	}
	return hres;
};		//タイトル文字のフォント名

extern inline int	GetLinkTitleStyleAttr(MPCObject* pObj)
{
	int nStyle = 0;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nStyle };
	pObj->GetAttribute(LINKATT_TITLE_STYLE, &avalue);
	return nStyle;
};		//タイトル文字のスタイル

extern inline int	GetLinkTitlePointSizeAttr(MPCObject* pObj)
{
	int nPoint = MP_DEFAULT_FONT_SIZE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nPoint };
	pObj->GetAttribute(LINKATT_TITLE_POINTSIZE, &avalue);
	return nPoint;
};		//タイトル文字のポイントサイズ

extern inline int	GetLinkTitlePitchAndFamilyAttr(MPCObject* pObj)
{
	// 言語依存モジュールから値を取得
	LOGFONT defaultLogFont = GetDefaultLogFont();
	int nPF = defaultLogFont.lfPitchAndFamily;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nPF };
	pObj->GetAttribute(LINKATT_TITLE_PITCHANDFAMILY, &avalue);
	return nPF;
};		//タイトル文字のピッチアンドファミリー

extern inline int	GetLinkTitleCharSetAttr(MPCObject* pObj)
{
	// 言語依存モジュールから値を取得
	LOGFONT defaultLogFont = GetDefaultLogFont();
	int nPF = defaultLogFont.lfCharSet;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nPF };
	pObj->GetAttribute(LINKATT_TITLE_CHARSET, &avalue);
	return nPF;
};		//タイトル文字のピッチアンドファミリー

/**********************************************************************
 *		モデルにデータを設定するための関数群
 **********************************************************************/
static inline STDMETHODIMP	LinkSetMultiByteAttribute(MPCObject* pObj, const MP_AName* aname, LPCSTR buf )
{
	// MultiByte/Unicodeで格納される属性に、デフォルト言語のMultiByteとして格納する

	MPCTextAttributeHelper* textattr = LinkGetTextAttributeHelper(pObj);
	if (textattr == NULL) return MP_E_UNEXPECTED;
	return textattr->SetMBText(pObj, aname, CP_ACP, buf, MP_TA_MULTIBYTE);
}

extern inline STDMETHODIMP	SetLinkTitleStrAttr(MPCObject* pObj , LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_TITLESTR, buf);
}			//タイトル文字列

extern inline STDMETHODIMP	SetLinkURLStrAttr(MPCObject* pObj , LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_URLSTR, buf);
}			//URL文字列

extern inline STDMETHODIMP	SetLinkXDWStrAttr(MPCObject* pObj , LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_XDWSTR, buf);
}			//XDW文字列

extern inline STDMETHODIMP	SetLinkIsDisplayIconAttr(MPCObject* pObj , BOOL_XD flag)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&flag };
	return pObj->SetAttribute(LINKATT_ISDISPLAYICON , &avalue);
};	//アイコンを表示するかどうか

extern inline STDMETHODIMP	SetLinkLinkToAttr(MPCObject* pObj , int n)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&n };
	return pObj->SetAttribute(LINKATT_LINKTO, &avalue);
};	//リンク先がどこか(自分自身:LINK_TO_ME、URL:LINK_TO_URL、XDW:LINK_TO_XDW)

extern inline STDMETHODIMP	SetLinkPageNumAttr(MPCObject* pObj , int n)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&n };
	return pObj->SetAttribute(LINKATT_XDWPAGENUM, &avalue);
};	//XDW文書のページ番号（0ならPROFILE)

//
//	for DocuWorks V4.0 Viewer
//
//
//  機能     : 「透過表示」の設定関数
//  
//  機能説明 : 
//  
//  返り値   : 
//  
//  備考     : 
//  
extern inline STDMETHODIMP SetLinkIsTransparentAttr(MPCObject* pObj , BOOL_XD bFlag)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bFlag };
	return pObj->SetAttribute(LINKATT_TRANSPARENT , &avalue);
}


//
//  機能     : 「自動リサイズ」の設定関数
//  
//  機能説明 : 
//  
//  返り値   : 
//  
//  備考     : 
//  
extern inline STDMETHODIMP SetLinkIsAutoResizeAttr(MPCObject* pObj , BOOL_XD bFlag)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bFlag };
	return pObj->SetAttribute(LINKATT_AUTO_RESIZE , &avalue);
}


//
//  機能     : ページ設定の設定関数
//  
//  機能説明 : 
//  
//  返り値   : 
//  
//  備考     : 
//  
extern inline STDMETHODIMP SetLinkIsPageCheckAttr(MPCObject* pObj , int nPageCheck)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&nPageCheck };
	return pObj->SetAttribute(LINKATT_PAGECHECK , &avalue);
}

//
//  機能     : 内部文書名の設定関数
//  
//  機能説明 : 
//  
//  返り値   : 
//  
//  備考     : 
//  
extern inline STDMETHODIMP	SetLinkInternalSheafName(MPCObject* pObj, LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_SHEAFNAME, buf);
}
//
//	ここまで新規に作成
//


//
// 関数名	:	SetLinkMailAddress
//
// 機能		:	設定されたメールアドレスを格納
//
// 機能説明	: 
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkMailAddress(MPCObject* pObj, LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_MAILADDRESS, buf);
}

//
// 関数名	:	SetLinkOtherFilePath
//
// 機能		: 
//
// 機能説明	:	その他のファイルへのリンクに設定されたファイルパスを格納
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkOtherFilePath(MPCObject* pObj, LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_OTHERFILE_PATH, buf);
}

//
// 関数名	:	SetLinkOtherFileRelative
//
// 機能		:	
//
// 機能説明	:	その他のファイルで、相対パスチェックの有無の値の格納
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkOtherFileRelative( MPCObject* pObj , const BOOL_XD bRelative)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bRelative };
	HRESULT hres = pObj->SetAttribute(LINKATT_OTHERFILE_RELATIVE , &avalue);
	return hres;
}

//
// 関数名	:	SetLinkDWLinkType
//
// 機能		: 
//
// 機能説明	:	DocuWorksのリンクの中で、ページ指定なのか？リンクアノテへのジャンプなのか？
//				を格納する
//
// 返り値	: 
//
// 備考		:	V50新規。
//	
extern inline STDMETHODIMP SetLinkDWLinkType( MPCObject* pObj , const int nLinkType )
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&nLinkType };
	HRESULT hres = pObj->SetAttribute(LINKATT_DW_JUMPTYPE , &avalue);
	return hres;
}

//
// 関数名	:	SetLinkDWFileRelative
//
// 機能		:	
//
// 機能説明	:	その他のファイルで、相対パスチェックの有無の値の格納
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkDWFileRelative( MPCObject* pObj , const BOOL_XD bRelative)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bRelative };
	HRESULT hres = pObj->SetAttribute(LINKATT_DW_RELATIVE , &avalue);
	return hres;
}

//
// 関数名	:	SetLinkJumpTitle
//
// 機能		: 
//
// 機能説明	:	リンクジャンプ先のタイトル名属性を格納。
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkJumpTitle(MPCObject* pObj, LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_LINKTITLE, buf);
}

//
// 関数名	:	SetLinkUserTooltip
//
// 機能		:	
//
// 機能説明	:	ツールチップを設定するかどうかの属性の取得
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkUserTooltip( MPCObject* pObj , const BOOL_XD bUserTooltip)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer) , MP_A_INT , (void*)&bUserTooltip };
	HRESULT hres = pObj->SetAttribute(LINKATT_USERTOOLTIP , &avalue);
	return hres;
}

//
// 関数名	:	SetLinkUserTooltipString
//
// 機能		: 
//
// 機能説明	:	ツールチップ文字列属性を格納。
//
// 返り値	: 
//
// 備考		:	V50新規
//	
extern inline STDMETHODIMP SetLinkUserTooltipString(MPCObject* pObj, LPCSTR buf )
{
	return LinkSetMultiByteAttribute(pObj, LINKATT_USER_TOOLTIP_STR, buf);
}

//
// 関数名	:	SetLinkDWFileType
//
// 機能		: 
//
// 機能説明	:	DocuWorks文書へのリンクで、このファイル/他のファイル属性を格納する。
//
// 返り値	: 
//
// 備考		:	V50以降で有効。V40は、SetLinkLinkToAttrを使用しているので、
//				V50以降で互換性の維持に注意すること。
//	
extern inline STDMETHODIMP	SetLinkDWFileType(MPCObject* pObj , int nDWFileType)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&nDWFileType };
	return pObj->SetAttribute(LINKATT_DWJUMP_FILETYPE, &avalue);
};

/*
//以下、タイトル文字の属性//
*/
extern inline STDMETHODIMP	SetLinkTitleColorAttr(MPCObject* pObj , COLORREF color)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(COLORREF), MP_A_INT, (void*)&color };
	return pObj->SetAttribute(LINKATT_TITLE_COLOR , &avalue);
};	//タイトル文字列の色

extern inline STDMETHODIMP	SetLinkTitleFaceNameAttr(MPCObject* pObj, LPCSTR buf )
{
	if(pObj == NULL) return MP_E_UNEXPECTED;
	MP_AValue avalue = { (MP_Integer)strlen(buf)+1, MP_A_OCTS, (void *)buf };
	HRESULT hres = pObj->SetAttribute(LINKATT_TITLE_FACE , &avalue);
	return hres;
};	//タイトル文字列のフォント名

extern inline STDMETHODIMP	SetLinkTitleStyleAttr(MPCObject* pObj , int n)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&n };
	return pObj->SetAttribute(LINKATT_TITLE_STYLE, &avalue);
};	//タイトル文字列のスタイル

extern inline STDMETHODIMP	SetLinkTitlePointSizeAttr(MPCObject* pObj , int n)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&n };
	return pObj->SetAttribute(LINKATT_TITLE_POINTSIZE, &avalue);
};	//タイトル文字列のポイントサイズ

extern inline STDMETHODIMP	SetLinkTitlePitchAndFamilyAttr(MPCObject* pObj , int n)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&n };
	return pObj->SetAttribute(LINKATT_TITLE_PITCHANDFAMILY, &avalue);
};	//タイトル文字列のピッチアンドファミリー

extern inline STDMETHODIMP	SetLinkTitleCharSetAttr(MPCObject* pObj , int n)
{
	if(pObj == NULL) return FALSE;
	MP_AValue avalue = { sizeof(MP_Integer), MP_A_INT, (void*)&n };
	return pObj->SetAttribute(LINKATT_TITLE_CHARSET, &avalue);
};	//タイトル文字列のキャラクタセット

extern inline STDMETHODIMP SetMetaPenName(MPCObject *pObj , LPCSTR name)
{
	ASSERT(pObj != NULL);
	ASSERT(name != NULL);
	MP_AValue avalue = {(MP_Integer)strlen(name) + 1, MP_A_OCTS , (void*)name};
	return pObj->SetAttribute("#name" , &avalue);
}//メタペンの名前を変更する

#endif	//_M3CORE_MP_


//
//	@(h)	('99/07/26 T.Matsuo)
//	@(s)
//		Viewer / Viewer Light / for Webで使用する共通関数
//
//
//

//  機能     :	リンクアノテのツールチップを省略する
//  
//  機能説明 :	80文字程度しか表示しないようにした。
//  
//  返り値   :	
//  
//  備考     :	AR7269。文字列の初期化不具合。

// 2009/8/31 Windows Mobileでは未対応
#ifndef _M3CORE_MP_

#define MAX_TOOLTIP_LENGTH		75
#define MAX_TOOLTIP_LENGTH_LOW	35
#define MAX_TOOLTIP_LENGTH_HI	MAX_TOOLTIP_LENGTH_LOW
extern inline void CreateShortToolTip(char* szLongToolTip , char* szShortToolTip )
{
	ZeroMemory( szShortToolTip , strlen(szShortToolTip) );
	int nToolTipLength = (int)strlen( szLongToolTip );
	if( nToolTipLength <= MAX_TOOLTIP_LENGTH )
		strcpy( szShortToolTip , szLongToolTip );
	else
	{
		char* szTmpLow = new char[MAX_TOOLTIP_LENGTH_LOW+1];
		ZeroMemory( szTmpLow , MAX_TOOLTIP_LENGTH_LOW + 1);
	
		///元々のツールチップの先頭からの文字列を取得
		///2バイトコードだったら、最後の文字をNULLに設定
		strncpy(szTmpLow , szLongToolTip , MAX_TOOLTIP_LENGTH_LOW );

		///以下、AR7711対応。
		///_mbsbtypeの使い方が間違っていた。
		int nCheck = _mbsbtype((const unsigned char*)szTmpLow , MAX_TOOLTIP_LENGTH_LOW - 1 );
		switch( nCheck )
		{
		case _MBC_LEAD:
			szTmpLow[ MAX_TOOLTIP_LENGTH_LOW - 1 ] = '\0';
			break;
		case _MBC_TRAIL:
		case _MBC_SINGLE:
		case _MBC_ILLEGAL:
		default:
			szTmpLow[ MAX_TOOLTIP_LENGTH_LOW ] = '\0';
			break;
		}

		///元々のツールチップの最後のほうの文字列を取得
		///取り出す前に2バイトコードかどうかを確認して、必要に応じて位置をずらす。
		nCheck = _mbsbtype( (const unsigned char*)szLongToolTip , 
			nToolTipLength - MAX_TOOLTIP_LENGTH_HI );
		switch( nCheck )
		{
		case _MBC_LEAD:
		case _MBC_SINGLE:
		case _MBC_ILLEGAL:
		default:
			szLongToolTip += (nToolTipLength - MAX_TOOLTIP_LENGTH_HI );
			break;
		case _MBC_TRAIL:
			szLongToolTip += (nToolTipLength - MAX_TOOLTIP_LENGTH_HI + 1);
			break;
		}

		///文字列の連結。
		wsprintfA( szShortToolTip , "%s...%s" , szTmpLow , szLongToolTip );
		delete []szTmpLow;
	}
}

#endif // _M3CORE_MP_

#pragma warning(default: 4996)

#endif	//	_LINKGLOB_H_

//
// CHANGE LOG
// 96.12.02	- Fujii -	Create
//
//	--------- DocuWorks V4.0 ----------
//	99/05/10	- T.Matsuo -	Viewer/VLT/forWeb共通で使えるような関数の作成
//	--------- DocuWorks V4.1.1 ----------
//	2001/04/25	T.Matsuo	AR6361対応
//