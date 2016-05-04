// File: GETTEXTCONT.H $ 

#ifdef _M3CORE_MP_

#ifndef GETTEXTCONT_H
#define GETTEXTCONT_H


#include "mpc_text.h"

// アノテーションのソースを追加せずにCoreだけでテキスト取得するための代理オブジェクト

class BasicContText;
class ImplBasicMedia;
class BasicContForGetText : public ImplBasicMedia
{
public:
	STDMETHOD_(void*, GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL);
	BasicContForGetText(MP_RefObjectType type);
	virtual ~BasicContForGetText();
private:
	BasicContForGetText();
	BasicContText* m_pMpcText;
};

class BasicContText : public MPCText
{
public:
	STDMETHOD(GetText)(MP_Text* text, MP_Integer length, MP_TextInfo* textInfo = NULL);
	STDMETHOD(GetTextWithLF)(MP_Text* text, MP_Integer length, MP_TextInfo* textInfo = NULL);
	HRESULT GetTextSpecial(MP_Text *text, MP_Integer length);
	BasicContText(MPCObject* pObject);
	virtual ~BasicContText();
private:
	BasicContText();
	HRESULT TextAnnotationGetText(MP_Text* text, MP_Integer length);
	MPCObject* m_pObject;
};

class BasicContFind : public MPCFind6
{
public:
	BasicContFind(MPCObject* pObject, BasicContText* pMpcText);
	STDMETHOD_(MPCObject*, Find)(MPCTextSearch *pTextSearch, MP_TextInfo **textInfo, MP_FindInfo *findInfo = NULL, HRESULT *result = NULL);

private:
	MPCObject* m_pObject;
	BasicContText* m_pMpcText;
};

class BasicContTextInfo : public MP_TextInfo
{
public:
	BasicContTextInfo(MP_Integer position, MP_Integer length);
	STDMETHOD(Destroy)();
};

MPCObject* BasicContForGetText_Create(MP_RefObjectType type, HRESULT *phres);

#endif // GETTEXTCONT_H

#endif

//
//CHANGE LOG
//11.9.21 - Bito - アノテ編集コア対応：BasicContTextクラスをEditableコンテントに使用するため定義をヘッダファイルに分離した
//12.2.15 - Bito - テキスト検索対応：テキスト検索のI/Fを追加するためのBasicContFindクラスを追加した