// File: IDecoder.h
// Authors: Kiyoshi Tashiro
// Copyright (C) 2004 by Fuji Xerox Co., Ltd. All rights reserved.

// IDecoderインタフェースクラスを定義する。
// MRC-PDなどでいろいろな圧縮画像を扱うためにデコーダを抽象化する

#include "mpc_api.h"

//#include <windows.h>
#include "win2mpf.h"

#ifndef _IDECODER_H_
#define _IDECODER_H_

/// IDecoderインタフェースクラス
mpinterface IDecoder
{
	typedef enum {
		DECODE_SUCCESS = 0,
		DECODE_CONTINUE = 1,
		DECODE_ERROR = -1
	} DecodeResult;
	typedef enum {
		DECODE_ZERO_WHITE = 0,
		DECODE_ZERO_BLACK = 1
	} PaletteType;

	/// デコード対象のデータを指定する
	/// @param iLen データのバイト数
	/// @param pData データの先頭ポインタ
	/// @return エラーコード
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData) PURE;
	/// デコード後の画像を貼るサイズを指定する
	/// @param dim サイズ
	/// @return エラーコード
	STDMETHOD(SetDimension)(MP_Dim dim) PURE;
	/// デコード後の画像の画素数を指定する
	/// @param size 画素数
	/// @return エラーコード
	STDMETHOD(SetBMPSize)(SIZE size) PURE;
	/// デコード後の画像の解像度を指定する
	/// @param size 解像度
	/// @return エラーコード
	STDMETHOD(SetBMPResolution)(SIZE size) PURE;
	/// デコード後の画像のパレットタイプを指定する
	/// @param iType パレットタイプ
	/// @return エラーコード
	STDMETHOD(SetPaletteType)(PaletteType iType) PURE;

	/// デコード可能かどうか調べる
	/// @return エラーコード
	STDMETHOD(AssertDecodable)() PURE;

	/// 画面表示用にデコーダを初期化する
	/// @param logicalDim デコード後の画像を利用時のサイズ
	/// @param hdc デコード後の画像を利用するデバイスコンテクスト
	/// @param degree デコード後の画像を貼る角度
	/// @return デコーダが出力する画像の情報を示すBITMAPINFOヘッダ
	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree) PURE;
	/// 画面表示用に1ラインを得る
	/// @param pLineBuff 1ライン分の画像データを書き出すポインタ
	/// @return デコード結果コード
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff ) PURE;
	/// 画面表示用にデコーダを終了処理する
	STDMETHOD_(void, FinishForDraw)() PURE;

	/// 印刷用にデコーダを初期化する
	/// @param logicalDim デコード後の画像を利用時のサイズ
	/// @param hdc デコード後の画像を利用するデバイスコンテクスト
	/// @param degree デコード後の画像を貼る角度
	/// @return デコーダが出力する画像の情報を示すBITMAPINFOヘッダ
	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree) PURE;
	/// 印刷用に1ラインを得る
	/// @param pLineBuff 1ライン分の画像データを書き出すポインタ
	/// @return デコード結果コード
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff ) PURE;
	/// 印刷用にデコーダを終了処理する
	STDMETHOD_(void, FinishForPrint)() PURE;

	/// 画像取得用にデコーダを初期化する
	/// @param iPercent デコード後の画像を利用時の拡大率(%)
	/// @return デコーダが出力する画像の情報を示すBITMAPINFOヘッダ
	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100) PURE;
	/// 画像取得用に1ラインを得る
	/// @param pLineBuff 1ライン分の画像データを書き出すポインタ
	/// @return デコード結果コード
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff ) PURE;
	/// 画像取得用にデコーダを終了処理する
	STDMETHOD_(void, FinishForGetDIB)() PURE;

	typedef DecodeResult ( __stdcall GetLineFunctionType)(IDecoder* pMe, unsigned char* pLineBuff);
	//STDMETHOD_(MP_Integer	( __stdcall *callback) (void *userData, MP_Integer percent), GetFuncToDrawLine)() PURE;
	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)() PURE;

	/// 画像の色深度をビット数で返す
	/// @return 色深度。負値の場合はエラーコード
	STDMETHOD(GetImageDepth)() PURE;

	/// オブジェクト間で共通のデータを渡す(JBIG2のグローバルデータ用)
	/// @return エラーコード
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData) PURE;

	/// オブジェクトを破棄する
	STDMETHOD_(void, Destroy)() PURE;
};

#endif //_IDECODER_H_


//CHANGE LOG
//2004.04.07 - Tashiro - 新規作成(V6)
