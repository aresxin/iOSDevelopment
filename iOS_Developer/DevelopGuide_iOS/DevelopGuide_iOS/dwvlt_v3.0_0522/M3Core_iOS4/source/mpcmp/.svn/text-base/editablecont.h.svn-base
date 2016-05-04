// File: EDITABLECONT.H
// Auther: Koji Bito
// Copyright(C) 2011 by Fuji Xerox Co,. Ltd. All right reserved.
//
// EDITABLECONT : アノテ編集コアに使用するコンテントの共通実装

#include "compcont.h"
#include "objtypes.h"

/***********************************************************
*  ImplEditableAnnotation : 子供を持たないコンテントの共通実装
***********************************************************/

class ImplEditableAnnotation : public ImplBasicMedia
{
public:
	ImplEditableAnnotation(MP_RefObjectType type);
	
	// attribute manipulations
	STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;	
};

/***************************************************************
 *  ImplParentEditableAnnotation : 子供を持つコンテントの共通実装
 **************************************************************/

class ImplParentEditableAnnotation : public ImplCompositeMedia
{
public:
	ImplParentEditableAnnotation(MP_RefObjectType type);
	
	// attribute manipulations
	STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;	
	
	STDMETHOD(GetPartType)();
};

/*********************************************************************************
 *  ImplSearchableEditableAnnotation : テキスト検索／取り出しが可能な代理ペンオブジェクト
 *                                   : （BasicContForGetTextと同じ機能を備える）
 ********************************************************************************/

class BasicContText;
class BasicContFind;
class ImplSearchableEditableAnnotation : public ImplEditableAnnotation
{
public:
	STDMETHOD_(void*, GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL);
	ImplSearchableEditableAnnotation(MP_RefObjectType type);
	virtual ~ImplSearchableEditableAnnotation();
private:
	ImplSearchableEditableAnnotation();
	BasicContText* m_pMpcText;
    BasicContFind* m_pMpcFind;
};

// ImplSearchableEditableAnnotationを生成する関数（mpmain.cppで呼ばれる）
MPCObject* SearchableEditableAnnotation_Create(MP_RefObjectType type, HRESULT *phres);

//
//CHANGE LOG
//11.9.21 - Bito - 作成
