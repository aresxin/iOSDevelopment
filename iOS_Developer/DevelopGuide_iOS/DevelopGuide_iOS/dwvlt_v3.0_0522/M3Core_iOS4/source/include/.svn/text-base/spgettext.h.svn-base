// $Archive: /DocuWorks/701/Source/include/spgettext.h $
//
// Copyright (C) 2008 Fuji Xerox Co., Ltd. All right reserved.
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:30 $
// $Revision: 1.5 $

#ifndef _SPGETTEXT_H_
#define _SPGETTEXT_H_

#include "mpc_text.h"

/*
§X.X.X ISpecialGetText インタフェース

§X.X.X.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_ISpecialGetText, 0x1336);

/*
§X.X.X.2 メソッド一覧
*/
mpinterface ISpecialGetText : public MPCText {
STDMETHOD(GetTextSpecial)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL) PURE;
STDMETHOD(GetTextWithLFSpecial)(MP_Text *text, MP_Integer length, MP_TextInfo *textInfo = NULL) PURE;
};

/*
§X.X.X.3 各メソッドの定義

§GetTextSpecial, GetTextWithLFSpecial

・説明
転記権なしでも取り出せる点を除けば、MPC_Text::GetText, GetTextWithLF と同じ動作をする。
*/

#endif
