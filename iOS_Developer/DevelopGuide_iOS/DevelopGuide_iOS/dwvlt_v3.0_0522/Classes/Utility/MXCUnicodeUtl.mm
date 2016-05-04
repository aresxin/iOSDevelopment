// [DWVLT70 2008.02.08 by ushijima]
//
//  MXCUnicodeUtl.cpp
//
//  Updater : $Author: ushijima $
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCUnicodeUtl.cpp
 *
 *	テキストに関する関数群の定義
 */
#include "MXCUnicodeUtl.h"
#include "secret.h"
#include "hcntdoc.h"
#include "MXCTextUtl.h"

/**
 * MXCUnicodeCmp : 指定された文字列をUnicode変換後に比較する
 * 
 * 引数：
 * char* unicharacter	IN  Unicodeの文字列
 * int   unilength		IN	Unicode文字列の長さ
 * char* compchar		IN	比較する文字列
 *
 * 返り値：
 * MXC_OK           OK
 * MXC_ERROR        エラー
 */
int MXCUnicodeCmp(char* unicharacter, int unilength, char* compchar)
{
	if (compchar == NULL) return MXC_ERROR;

	// URTF16エンコード
	NSString *uniStr = MXCGetStringWithUTF16(unicharacter,unilength);
	if ((uniStr == nil) && (compchar != NULL)) return MXC_ERROR;

	// NSStringからcharを抽出する。
	const char *tdata;
	tdata = [uniStr UTF8String];
	
	// char同士の比較
	if (strcmp(tdata,compchar) != 0)  {
		return MXC_ERROR;
	}

	return MXC_OK;
}
