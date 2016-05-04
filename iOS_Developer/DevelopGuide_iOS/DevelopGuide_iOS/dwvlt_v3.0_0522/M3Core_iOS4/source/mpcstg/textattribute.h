// File: textattribute.h
// Author: Toshiyuki Komoda
// Copyright (c) 2007 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Archive: /DocuWorks/70/Source/mpcstg/textattribute.h $ 
// $Date: 2009/12/22 08:10:52 $ 
// $Revision: 1.4 $ 

#ifndef _MPCSTG_TEXTATTRIBUTEHELPER_H
#define _MPCSTG_TEXTATTRIBUTEHELPER_H

#include <mpc_api.h>

class ImplMPCTextAttributeHelper : public MPCTextAttributeHelper
{
public:
	STDMETHOD(GetText)(MPCObject* obj, const MP_AName* attributeName, int codepage, MP_String& text, MP_TAType &tatype);
	STDMETHOD(GetMBText)(MPCObject* obj, const MP_AName* attributeName, int codepage, MP_MBString& mbtext, MP_TAType &tatype);
	STDMETHOD(SetText)(MPCObject* obj, const MP_AName* attributeName, int codepage, const MP_Text* text, MP_TAType tatype);
	STDMETHOD(SetMBText)(MPCObject* obj, const MP_AName* attributeName, int codepage, const char* mbtext, MP_TAType tatype);
private:
	HRESULT UpdateUnicodeCheckedAttribute(MPCObject* obj);
};

MPCTextAttributeHelper* MPCTextAttributeHelper_Create();
void MPCTextAttributeHelper_Destroy(MPCTextAttributeHelper* obj);

#endif
