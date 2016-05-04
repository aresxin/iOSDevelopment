// File: imgmag.h
// Author: Toshiyuki KOMODA
// Copyright (C) 1998 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _IMGMAG_H
#define _IMGMAG_H

//#include <windows.h>
#include "win2mpf.h"

class ImageMagnify
{
public:
	// init, getLineの戻り値
	enum {
		MAGNIFY_OK = 0,
		MAGNIFY_ERROR = -1,
		MAGNIFY_COMPLETE = 0,
		MAGNIFY_INCOMPLETE = 1,
	};
	// decode 関数の戻り値
	enum {
		DECODE_OK = 0,
		DECODE_ERROR = -1
	};
	// 拡大率 : magnification に使用
	enum {
		MAGNIFY_INVALID = 0,
		MAGNIFY100 = 1,
		MAGNIFY200 = 2,
		MAGNIFY300 = 3,
	};

	typedef int (* GETFUNC)(BYTE *, void *);

	// 使用者はこれに値をセットしてinit()を呼ぶ
	int magnification;		// 拡大率
	BITMAPINFO *pSrcBI;		// 入力画像のinfoheader
	int bTrimming;			// 切り取りするかどうか
	POINT trimOffset;		// 切り取りのオフセット(左上から)
	SIZE trimSize;			// 切り取りサイズ
	GETFUNC decodeLine;		// 1ライン分の入力画像を与えるcallback関数
	void *decodeArg;		// decodeLineに与えるパラメータのポインタ
	int dstBISize;			// (return) infoheaderのサイズ
	BITMAPINFO *pDstBI;		// (return) ここにinfoheaderがallocされる
		
	ImageMagnify() {
		bTrimming = FALSE;
		pDstBI = 0;
		psrc = 0;
		pbuffer = 0;
		state = MAGNIFY_UNINITIALIZED;
	}
	~ImageMagnify() { release(); }

	int init();
	int getLine(BYTE *pDst);
	inline int getRestCount() { return dstHeight - lineCount; }
	void release();
	static int getLineDispatch(BYTE *pDst, void *pImageMagnify) {
		return ((ImageMagnify *)pImageMagnify)->getLine(pDst);
	}

private:
	enum {MAGNIFY_UNINITIALIZED = 0};
	typedef void (ImageMagnify::*LPMAGFUNC)(const BYTE *, BYTE *);
	int state;			// UNITITIALIZED or 拡大率
	int srcWidth;
	int dstWidth;
	int dstHeight;
	int srcLineBytes;
	int dstLineBytes;
	int lineCount;		// 出力ラインのカウント
	int nBuffer;		// 拡大画像バッファの有効回数 (=拡大率)
	int nBufferCount;	// 拡大画像バッファの有効カウント
	int xOffsetBytes;	// 左端からの切り取り幅
	int yOffsetCount;	// 上端からの切り取りライン数
	BYTE *psrc;			// 入力画像1ラインバッファ
	BYTE *pbuffer;		// 拡大画像1ラインバッファ
	LPMAGFUNC magFunc;	// 拡大関数のポインタ

	// 拡大関数
	void magnify100(const BYTE *, BYTE *);
	void magnify200(const BYTE *, BYTE *);
	void magnify300(const BYTE *, BYTE *);
};

#endif

//CHANGE LOG
//98.05.12 - Komoda - V3.1 新規作成
//98.05.21 - Komoda - AR2800対応 切り取り仕様の変更
