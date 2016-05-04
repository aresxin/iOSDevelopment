//
//  MXCDecodeRLE.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCDecodeRLE.h
 *
 *	RLE圧縮のデコード関数をコアライブラリ外から呼べるよう、関数を定義する。
 */
#ifndef MXCDECODERLE_H
#define MXCDECODERLE_H

#include "w2mpf_def.h"
#include "w2mpf_gdi_def.h"

// Objective-Cから呼ぶ場合にBOOL定義が重複する問題がある為、
// 本来この関数の返り値はBOOLだが、shortとして定義する。
// ソースを見る限り、DecodeRLEはFALSEしか返していないし、
// ReadRle4Bits, ReadRle8BitsはTRUEしか返していないので、
// 返り値を見る必要はないと思われる。

/**
 * RLEデコード関数
 * ビットマップヘッダを参照する為、そのままでは正常に動作しないと思われる。
 * 使用しなくてはいけない場合は注意すべし。
 *
 * DWVLT 6.0:
 * RLE圧縮解凍コードがpd3wmf.cppに定義されている関数から
 * 独立したクラスへ変更された。
 * それに伴い、コアラッパーへ実装を追加。
 *
 * 引数：
 *  pSrcBI 変換元BITMAPデータ
 *  pDstBI 変換したBITMAPデータを入れるバッファ
 *
 * 返り値：常にFALSE
 */
short DecodeRLE(BITMAPINFO *pSrcBI, void *pDstBI);

/**
 * RLEデコード関数
 * BITMAPヘッダを省いたRLE圧縮データをデコードする。
 * 関数の中身は
 *		static BOOL ReadRle4Bits (BYTE * src, BYTE * dst, int w, int h)
 * をコールしているのみ。
 *
 * DWVLT 6.0:
 * RLE圧縮解凍コードがpd3wmf.cppに定義されている関数から
 * 独立したクラスへ変更された。
 * それに伴い、コアラッパーへ実装を追加。
 *
 * 引数：
 *  src 変換元BITMAPデータ
 *  dst 変換したBITMAPデータを入れるバッファ
 *  w   幅
 *  h   高さ
 *
 * 返り値：常にTRUE
 */
short ReadRle4Bits4OSX(BYTE * src, BYTE * dst, int w, int h);

/**
 * RLEデコード関数
 * BITMAPヘッダを省いたRLE圧縮データをデコードする。
 * 関数の中身は
 *		static BOOL ReadRle8Bits (BYTE * src, BYTE * dst, int w, int h)
 * をコールしているのみ。
 *
 * DWVLT 6.0:
 * RLE圧縮解凍コードがpd3wmf.cppに定義されている関数から
 * 独立したクラスへ変更された。
 * それに伴い、コアラッパーへ実装を追加。
 *
 * 引数：
 *  src 変換元BITMAPデータ
 *  dst 変換したBITMAPデータを入れるバッファ
 *  w   幅
 *  h   高さ
 *
 * 返り値：常にTRUE
 */
short ReadRle8Bits4OSX(BYTE * src, BYTE * dst, int w, int h);

/**
 * JPEGデコードのデコード後のサイズを問い合わせる関数
 * src, srcSizeで示されたJPEG画像のデコード後のサイズを返す。
 *
 * 引数：
 *  src		IN  変換元JPEGデータ
 *  srcSize IN  変換元JPEGデータのサイズ
 *
 * 返り値： JPEGデータデコード後のDIBデータのサイズ
 */
unsigned long GetJPEGDecodeSize4OSX(unsigned char* src, unsigned long srcSize);

/**
 * JPEGデコード関数
 * src, srcSizeで示されたJPEG画像をデコードし、DIBフォーマットにしてdstにコピーして返す。
 * 引数dstはあらかじめallocateされたバッファである必要がある。
 *
 * 引数：
 *  src		IN  変換元JPEGデータ
 *  srcSize IN  変換元JPEGデータのサイズ
 *  dst		OUT デコードしたBITMAPデータを入れるバッファ
 *
 * 返り値： 成功 MXC_OK 失敗 MXC_ERROR
 */
int DecodeJPEG4OSX(unsigned char* src, unsigned long srcSize, unsigned char* dst);

#endif // MXCDECODERLE_H
