// File: mpc_textattribute.h
// Author: Toshiyuki Komoda
// Copyright (c) 2007 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Archive: /DocuWorks/70/Source/include/mpc_textattribute.h $ 
// $Date: 2009/12/22 08:11:29 $ 
// $Revision: 1.4 $ 

// mpc_api.hからincludeされる

#ifndef _MPC_TEXTATTRIBUTE_H
#define _MPC_TEXTATTRIBUTE_H

/*!
テキスト属性のタイプ
*/
typedef int MP_TAType;

const MP_TAType MP_TA_UNKNOWN = 0;
const MP_TAType MP_TA_MULTIBYTE = 1;
const MP_TAType MP_TA_UNICODE = 2;
const MP_TAType MP_TA_UNICODE_IFNECESSARY = 3;

MPC_EXTERN_GUID(IID_MPCTextAttributeHelper, 0x1333);

/*!
MPCTextAttributeHelperのインスタンスは
MPCSessionのGetInterface(IID_MPCTextAttributeHelper)によって取得できる。
破棄はMPCSessionのDestroyの中で行われる。
*/
mpinterface MPCTextAttributeHelper
{
/*!
@brief テキスト属性をUnicode形式で読み込む
@param[in] obj オブジェクト
@param[in] attributeName 属性名
@param[in] codepage コードページ
@param[out] text テキスト属性の値(Unicode)
@param[out] tatype テキスト属性のタイプ
@return HRESULT 結果コード
@note 属性がMultiByteであってもUnicodeであってもUnicodeテキストの形で取得する。
コードページはMultiByteの属性をUnicodeに変換する際に使用される。
*/
STDMETHOD(GetText)(MPCObject* obj, const MP_AName* attributeName, int codepage, MP_String& text, MP_TAType &tatype) PURE;
/*!
@brief テキスト属性をMultiByte形式で読み込む
@param[in] obj オブジェクト
@param[in] attributeName 属性名
@param[in] codepage コードページ
@param[out] mbtext テキスト属性の値(MultiByte)
@param[out] tatype テキスト属性のタイプ
@return HRESULT 結果コード
@note 属性がMultiByteであってもUnicodeであってもMultiByteテキストの形で取得する。
コードページはUnicodeの属性をMultiByteに変換する際に使用される。
*/
STDMETHOD(GetMBText)(MPCObject* obj, const MP_AName* attributeName, int codepage, MP_MBString& mbtext, MP_TAType &tatype) PURE;
/*!
@brief テキスト属性をセットする
@param[in] obj オブジェクト
@param[in] attributeName 属性名
@param[in] codepage コードページ
@param[in] text テキスト属性の値(Unicode)
@param[in] tatype テキスト属性のタイプ
@return HRESULT 結果コード
@note 実際に書き込む属性の形式を{Unicode/MultiByte/必要な場合のみUnicode}から選択する。
コードページはUnicodeテキストをMultiByteの属性に変換する際に使用される。
*/
STDMETHOD(SetText)(MPCObject* obj, const MP_AName* attributeName, int codepage, const MP_Text* text, MP_TAType tatype) PURE;
/*!
@brief テキスト属性をセットする
@param[in] obj オブジェクト
@param[in] attributeName 属性名
@param[in] codepage コードページ
@param[in] mbtext テキスト属性の値(MultiByte)
@param[in] tatype テキスト属性のタイプ
@return HRESULT 結果コード
@note 実際に書き込む属性の形式を{Unicode/MultiByte}から選択する。
コードページはMultiByteのテキストをUnicodeの属性に変換する際に使用される。
*/
STDMETHOD(SetMBText)(MPCObject* obj, const MP_AName* attributeName, int codepage, const char* mbtext, MP_TAType tatype) PURE;
};

#endif

