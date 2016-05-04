// File: internaldoc.h
// Author: Toshiyuki Komoda
// Copyright (c) 2007 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Archive: /DocuWorks/70/Source/include/internaldoc.h $
// $Date: 2009/12/22 08:11:30 $
// $Revision: 1.4 $

// mpc_api.hからincludeされる

#ifndef INTERNAL_DOCUMENT_H
#define INTERNAL_DOCUMENT_H

/*!
 MetaPaperオブジェクトからインターフェイスを取得できる
 Binderオブジェクトからは取得できない
*/
MPC_EXTERN_GUID(IID_MPCInternalDocument, 0x1334);

/*!
@brief 内部文書名のread/writeを行うインターフェイス
*/
mpinterface MPCInternalDocument
{
/*!
@brief 内部文書名を取得する(MultiByte)
@param[out] documentName 内部文書名を格納する文字列オブジェクト
@param[out] tatype テキスト属性の形式が返る
@param[in] codepage コードページ Unicodeで格納された属性を読み出すときに使われる
@return HRESULT 結果コード
*/
STDMETHOD(GetDocumentName)(MP_MBString& documentName, MP_TAType& tatype, int codepage) PURE;

/*!
@brief 内部文書名を取得する(Unicode)
@param[out] documentName 内部文書名を格納する文字列オブジェクト
@param[out] tatype テキスト属性の形式が返る
@param[in] codepage コードページ MultiByteで格納された属性を読み出すときに使われる
@return HRESULT 結果コード
*/
STDMETHOD(GetDocumentNameW)(MP_String& documentName, MP_TAType& tatype, int codepage) PURE;

/*!
@brief 内部文書名を変更する(MultiByte)
@param[in] documentName 内部文書名を指定
@param[in] tatype 属性の形式を指定(MULTIBYTE/UNICODE)
@param[in] codepage コードページ 属性をUnicodeでセットするときに使われる
@return HRESULT 結果コード
@note documentNameにNULLを指定すると属性を削除する
*/
STDMETHOD(SetDocumentName)(const char* documentName, MP_TAType tatype, int codepage) PURE;

/*!
@brief 内部文書名を変更する(Unicode)
@param[in] documentName 内部文書名を指定
@param[in] tatype 属性の形式を指定(MULTIBYTE/UNICODE/UNICODE_IFNECESSARY)
@param[in] codepage コードページ 属性をMultiByteでセットするときに使われる
@return HRESULT 結果コード
@note documentNameにNULLを指定すると属性を削除する
*/
STDMETHOD(SetDocumentNameW)(const MP_Text* documentName, MP_TAType tatype, int codepage) PURE;
};

#endif
