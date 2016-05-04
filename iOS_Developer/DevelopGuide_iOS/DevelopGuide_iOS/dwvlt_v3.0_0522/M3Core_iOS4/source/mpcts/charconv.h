// $Archive: /DocuWorks/60/Source/mpcts/charconv.h $
//
// Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:36 $
// $Revision: 1.4 $

#ifndef CHARCONV_H
#define CHARCONV_H

#ifndef MPCOREAPI_H
#include <mpc_api.h>
#endif

/*
#ifndef _WINDOWS_
#include <windows.h>
#endif
*/

/*!
	@brief LCMapStringのUnicode版、Windows98に用意されていないので独自実装する

	@param dwMapFlag 次の3つのorによる組み合わせ LCMAP_LOWERCASE, LCMAP_HALFWIDTH, LCMAP_KATAKANA
	@param pwsSrc 入力文字列のポインタ
	@param cchSrc 入力文字列の長さ (-1はNULL終端とみなす)
	@param pwsDest 出力バッファのポインタ (NULLはサイズ問合せ)
	@param cchDest 出力バッファの長さ

	@return バッファの長さ
	@retval MP_E_INVALIDARG 引数の異常
*/
int DWLCMapString(DWORD dwMapFlag, const WCHAR* pwsSrc, int cchSrc, WCHAR* pwsDest, int cchDest);

#endif

// $History: charconv.h $
// 
// *****************  Version 2  *****************
// User: Komoda       Date: 04/07/26   Time: 17:24
// Updated in $/DocuWorks/60/Source/mpcts
// AR9591 全角半角を区別しない検索の不具合対応
// 
// *****************  Version 1  *****************
// User: Komoda       Date: 04/03/26   Time: 15:01
// Created in $/DocuWorks/60/Source/mpcts
