//
//  MXCTextUtl.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.7 $, $Date: 2007/03/12 07:45:25 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCTextUtl.h
 *
 *	テキストに関する関数群の定義
 */

#ifndef MXCTEXTUTL_H
#define MXCTEXTUTL_H

// DWVLT62 2006.09.13 by Marumo,K.  -->
// Cocoa のヘッダーで定義されているが、Cocoaヘッダーを import できないので、同等定義を独自に行う
// うまい方法が見つかったら、この定義は削除すること。
//typedef unsigned short	MXCUniChar;
//typedef unsigned		MXCNSStringEncoding;
// add end -->

#include "MXCImage.h"

/**
 * MXCGetOcrText : OCRテキストを引数のバッファにコピーする
 * 
 * 引数：
 * MXCImage* raster         IN  コアラッパー ラスタ画像オブジェクト
 * UniChar** buf			IN/OUT OCRテキストバッファ(Unicode)
 * int* length				OUT  OCRテキストバッファのサイズ
 *
 * 返り値：
 * MXC_OK           OK
 * MXC_ERROR        エラー
 *
 * [DWVLT62 2006.09.13 by akiyoshi]
 * 引数を変更 char* → UniChar**
 *          int → int*
 */
int MXCGetOcrText(MXCImage* raster, UniChar** buf, int* length);

/**
 * MXCGetOcrRectSize : OCR領域情報のサイズを返す
 * OCRテキストの選択領域情報の配列サイズを返す
 * 
 * 引数：
 * MXCImage* raster   IN	コアラッパー 画像オブジェクト
 *							（ラスタ画像でないMXCImageを指定された場合は0が返る）
 *
 * 返り値：
 * OCR領域情報の配列のサイズ
 * OCR領域情報が無い場合は0を返す。
 */
int MXCGetOcrRectSize(MXCImage* raster);

/**
 * MXCGetOcrRect : OCR領域情報を引数のバッファにコピーする
 * OCRテキストの選択領域情報を引数の配列にコピーする
 * 
 * 引数：
 * MXCImage* raster			IN  コアラッパー 画像オブジェクト
 *							（ラスタ画像でないMXCImageを指定された場合は何もコピーされない）
 * int* rect				OUT OCRテキストをコピーするバッファ
 * int size					IN  バッファのサイズ
 *
 * 返り値：
 * MXC_OK           OK
 * MXC_ERROR        エラー
 */
int MXCGetOcrRect(MXCImage* raster, int* rect, int size);

/**
 * MXCConvertReturn : 改行コードを変換する
 * Windowsの改行コード(¥r¥n)をMacOSXの改行コードに変換する。
 * 
 * 引数：
 * char* buf				IN/OUT  変換対象テキスト
 * int* length				IN/OUT  変換対象テキストの長さ
 *
 * [DWVLT62 2006.09.21 by Marumo,K.]
 * OSXテキストエディタの改行コードの初期値に倣い、LFを残す。
 * また、文字列をUniCharで扱うように統一されたことを受けて、引数の型を変更
 */
void MXCConvertReturn(UniChar* buf, int* length);

/**
 * DWVLT62 2006.09.13 by Marumo,K.
 * フォント情報に含まれる Windows CHARSET を、NSStringEncoding に変換する。
 *
 * 引数：
 * unsigned char charset				IN  Windows CHARSET
 *
 * 返り値：
 * Windows CHARSET に対応する NSStringEncoding
 */
NSStringEncoding MXCGetNSStringEncoding(unsigned char charset);

/**
 * DWVLT62 2006.09.13 by Marumo,K.
 * 引数で指定された文字列を１文字ずつチェックして、必要であれば文字コードを変換する。
 * 現在サポートしている変換は以下の通り。
 * (1) SHIFTJIS_CHARSETの場合のみ、バックスラッシュ(U+005C)を円マーク(U+00A5)に変換する。
 *
 * 引数：
 * UniChar* charset				IN/OUT  変換対象文字列
 * unsigned int* charLength     IN/OUT  文字列長。処理後に文字列長が変わった場合に対応
 * unsigned char charset        IN      CHARSET
 */
void MXCConvertChar(UniChar* uniCharPtr, unsigned int* charLength, unsigned char charset);

/**
 * DWVLT62 BTS#44 Marumo,K.
 * システムデフォルトのエンコーディングをWindowsの対応するエンコーディングとして取得する。
 */
NSStringEncoding MXCGetDefaultEncodingAsWindows();

/**
 * DWVLT62 BTS#44 Marumo,K.
 * 指定されたchar*をデフォルトエンコーディングで文字列に変換する。
 */
NSString* MXCGetStringWithCString(char* cString);

/**[DWVLT70 2008.02.08 by ushijima]
 * DWVLT70 ushijima
 * 指定されたchar*をNSUnicodeStringEncodingで文字列に変換する。
 */
NSString* MXCGetStringWithUTF16(char* cStringW,int numChar);

#endif // MXCTEXTUTL_H
