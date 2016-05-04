//
//  stampcont.h
//  dwcore(iOS4)
//
//  Created by KOJI BITO on 12/04/04.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dwcore_iOS4__stampcont_h
#define dwcore_iOS4__stampcont_h

#include "mpc_text.h"

typedef struct tag_DATE_FORMAT_ELEMENT {
	char* lpFormat;
} DATE_FORMAT_ELEMENT;

class ImplBasicMedia;
class CStampContentFind;
class StampContForFind : public ImplBasicMedia
{
public:
    STDMETHOD_(void*, GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL);
	StampContForFind(MP_RefObjectType type);
	virtual ~StampContForFind();
    
   	STDMETHOD_(int, GetTextForFind)(MP_Text *text, int len);
    
private:
	StampContForFind();
    CStampContentFind* m_pMpcFind;

    void ReplaceDateElement(char* strTarget, DATE_FORMAT_ELEMENT* pElement, char* strElement);
	void GetStampDateString(char* srcStr);
};

class CStampContentFind : public MPCFind6
{
public:
	CStampContentFind(MPCObject *pObject);
	STDMETHOD_(MPCObject *, Find)(MPCTextSearch *pTextSearch, MP_TextInfo **textInfo, MP_FindInfo *findInfo = NULL, HRESULT *result = NULL);
    
private:
	MPCObject *m_pObject;
};

class CStampContentTextInfo : public MP_TextInfo
{
public:
	CStampContentTextInfo(MP_Integer position, MP_Integer length);
	STDMETHOD(Destroy)();
};

MPCObject* StampContForFind_Create(MP_RefObjectType type, HRESULT *phres);

#endif
