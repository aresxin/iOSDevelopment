// $Archive: /DocuWorks/70/Source/include/mpprfile.h $
//
// Copyright (c) 1996-2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:29 $
// $Revision: 1.4 $

// File: mpprfile.h
// Auther: Takashi Matsumoto
// Copyright(C) 1996-1998 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef MPPRFILE_H
#define MPPRFILE_H

#include "mpc_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// GetMpProfileInt() GetMpProfileString()の仕様
//	(V5.0から)
//	bUserにTRUEを指定したとき、もしHKCUから読み出しに失敗したら
//	HKLMのMPMX以下の同じ場所から読み出しを試みる。それでもだめならエラー。
//	XDWAPIをサービスから呼ぶ連携製品で障害がでたときの回避手段のため。
//	V4までは、bUserにTRUEを指定したとき、もしHKCUから読み出しに失敗したら
//	HKLMのMPM3を読む動作があったが、これは廃止。
// 書き込み系は上記MPMXに書く動作はしない。

/*!
@brief DocuWorksのレジストリから数値を読み出す

@param lpszSection		セクション名
@param lpszKey			キー名
@param dwDefault		デフォルト値
@param bUser			TRUE: HKCUをアクセス/FALSE: HKLMをアクセス
@return DWORD			読み出した値
*/
DWORD __stdcall GetMpProfileInt(
	LPCSTR lpszSection, LPCSTR lpszKey, DWORD dwDefault, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリから文字列の値を読み出す

@param lpszSection		セクション名
@param lpszKey			キー名
@param lpszDefault		デフォルト値
@param lpszReturnBuffer	値を受け取るバッファ
@param cchReturnBuffer	バッファのサイズ(バイト数)
@param bUser			TRUE: HKCUをアクセス/FALSE: HKLMをアクセス
@return DWORD			値のサイズ(バイト数)
*/
DWORD __stdcall GetMpProfileString(
	LPCSTR lpszSection, LPCSTR lpszKey, LPCSTR lpszDefault,
	LPSTR lpszReturnBuffer, DWORD cchReturnBuffer, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリからWideChar文字列の値を読み出す

@param lpszSection		セクション名
@param lpszKey			キー名
@param lpwszDefault		デフォルト値(Unicode)
@param lpwszReturnBuffer 値を受け取るバッファ(Unicode)
@param cchReturnBuffer	バッファのサイズ(文字数)
@param bUser			TRUE: HKCUをアクセス/FALSE: HKLMをアクセス
@return DWORD			値のサイズ(文字数)
*/
DWORD __stdcall GetMpProfileWideCharString(
	LPCSTR lpszSection, LPCSTR lpszKey, LPCWSTR lpwszDefault,
	LPWSTR lpwszReturnBuffer, DWORD cchReturnBuffer, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリに数値を書き込む

@param lpszSection		セクション名
@param lpszKey			キー名
@param dwValue			書き込む数値
@param bUser			TRUE: HKCUをアクセス/FALSE: HKLMをアクセス
@return BOOL_XD			成功したかどうか
*/
BOOL_XD __stdcall WriteMpProfileInt(
	LPCSTR lpszSection, LPCSTR lpszKey, DWORD dwValue, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリに文字列の値を書き込む

@param lpszSection		セクション名
@param lpszKey			キー名
@param lpszValue		書き込む文字列の値
@param bUser			TRUE: HKCUをアクセス/FALSE: HKLMをアクセス
@return BOOL_XD			成功したかどうか
*/
BOOL_XD __stdcall WriteMpProfileString(
	LPCSTR lpszSection, LPCSTR lpszKey, LPCSTR lpszValue, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリにWideChar文字列の値を書き込む

@param lpszSection		セクション名
@param lpszKey			キー名
@param lpwszValue		書き込む文字列の値(Unicode)
@param bUser			TRUE: HKCUをアクセス/FALSE: HKLMをアクセス
@return BOOL_XD			成功したかどうか
*/
BOOL_XD __stdcall WriteMpProfileWideCharString(
	LPCSTR lpszSection, LPCSTR lpszKey, LPCWSTR lpwszValue, BOOL_XD bUser);


// 注意: 5.0.2以降でインストールされているDWバージョンを取るときは
//  GetMpVersionString()を用いるか、同等の動作をするように実装する必要がある。

/*!
@brief DocuWorks本体のバージョン文字列をレジストリから取得する 

5.0.2で新設。
AR8349対策でインストールされているDocuWorksのバージョンの読み出し動作が
変更になり、その動作を隠蔽化するための関数

@param strDefault	デフォルト値
@param strReturn	読み出した値を格納する文字列オブジェクト
@return DWORD バージョン文字列の長さ
*/
DWORD __stdcall GetMpVersionString(
	LPCSTR lpszDefault, LPSTR lpszReturnBuffer, DWORD cchReturnBuffer);

/*!
@brief 体験版の期限切れチェック

@retval TRUE 期限切れ
@retval FALSE 期限切れではない
*/
BOOL_XD __stdcall TimeExpired();



// V7で追加 Unicode版

/*!
@brief DocuWorksのレジストリから数値を読み出す (Unicode版)

@param section		セクション名
@param key			キー名
@param dwDefalut	デフォルト値
@param bUser		TRUE:HKCUをアクセス,FALSE:HKLMをアクセス
@return DWORD レジストリの値(キーが存在しないときは入力したデフォルト値)
*/
DWORD __stdcall GetMpProfileIntW(
	const MP_Text *section, const MP_Text *key, DWORD dwDefault, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリから文字列の値を読み出す (Unicode版)

@param section		セクション名
@param key			キー名
@param strDefault	デフォルト値(NULLならば空文字列とみなす)
@param strReturn	読み出した値
@param bUser		GetMpProfileIntと同様
@return DWORD	値のサイズ(文字数)
*/
DWORD __stdcall GetMpProfileStringW(
	const MP_Text *section, const MP_Text *key, const MP_Text *strDefault,
	MP_String &strReturn, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリに数値を書き込む (Unicode版)

@param section		セクション名
@param key			キー名
@param strDefault	デフォルト値
@param strReturn	読み出した値
@param bUser		GetMpProfileIntと同様
@return BOOL_XD	成功したかどうか
*/
BOOL_XD __stdcall WriteMpProfileIntW(
	const MP_Text *section, const MP_Text *key, DWORD dwValue, BOOL_XD bUser);

/*!
@brief DocuWorksのレジストリに文字列の値を書き込む (Unicode版)

@param section		セクション名
@param key			キー名
@param strValue		書き込む文字列
@param bUser		GetMpProfileIntと同様
@return BOOL_XD	成功したかどうか
*/
BOOL_XD __stdcall WriteMpProfileStringW(
	const MP_Text *section, const MP_Text *key, const MP_Text *strValue,
	BOOL_XD bUser);

/*!
@brief DocuWorks本体のバージョン文字列をレジストリから取得する (Unicode版)

@param strDefault	デフォルト値(NULLならば空文字列とみなす)
@param strReturn	読み出した値を格納する文字列オブジェクト
@return DWORD バージョン文字列の長さ
*/
DWORD __stdcall GetMpVersionStringW(
	const MP_Text *strDefault, MP_String &strReturn);


#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // MPPRFILE_H 

//CHANGE LOG
//96.6.6 - Matsumoto - 作成
//98.4.15 - Matsumoto - TimeExpired()追加
//2002.7.25 - Tashiro - V5 AR8097 動作仕様をコメントに追加
//2004.3.16 - Komoda - V60 GetMpProfileWideCharString, WriteMpProfileWideCharStringを追加
//2007.8.10 - Komoda - V70 Unicode I/Fを追加
