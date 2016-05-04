// [DWVLT70 2008.02.08 by ushijima]
//
//  MXCUnicodeUtl.h
//
//  Updater : $Author: ushijima $
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCUnicodeUtl.h
 *
 *	テキストに関する関数群の定義
 */

// DWVLT62 2006.09.13 by Marumo,K.  -->
// Cocoa のヘッダーで定義されているが、Cocoaヘッダーを import できないので、同等定義を独自に行う
// うまい方法が見つかったら、この定義は削除すること。
//typedef unsigned short	MXCUniChar;
//typedef unsigned		MXCNSStringEncoding;
// add end -->

#include "MXCImage.h"

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
int MXCUnicodeCmp(char* unicharacter, int unilength, char* compchar);