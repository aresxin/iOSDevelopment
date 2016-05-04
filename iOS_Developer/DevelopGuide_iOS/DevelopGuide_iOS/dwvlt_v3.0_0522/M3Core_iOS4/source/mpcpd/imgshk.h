// File: imgshk.h
// Author: Toshiyuki KOMODA
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _IMGSHK_H
#define _IMGSHK_H

//#include <windows.h>
#include "win2mpf.h"

class ImageShrink
{
public:
	enum {
		SHRINK_OK = 0,
		SHRINK_ERROR = -1,
		SHRINK_COMPLETE = 0,
		SHRINK_INCOMPLETE = 1,
	}; // init, getLineの戻り値

	enum {
		DECODE_OK = 0,
		DECODE_ERROR = -1
	}; // decode 関数の戻り値

	enum {
		CONTRAST_NONE = 0,
		CONTRAST_BIN = 1,
		CONTRAST_CONT = 2,
		CONTRAST_CONT_REV = 3,
		CONTRAST_BIN_REV = 4 };

	typedef int (* GETFUNC)(BYTE *, void *);

	BITMAPINFO *pSrcBI;		// 入力画像のinfoheader
	int dstWidth;			// 要求サイズ
	int dstHeight;			// 要求サイズ
	int isGray;				// Gray ならば TRUE
	int colorReduction;		// 減色してほしい場合は TRUE
	int useDither;			// 減色時にditherを使用するならば TRUE
	GETFUNC decodeLine;		// 1ライン分の入力画像を与えるcallback関数
	void *decodeArg;		// decodeLineに与えるパラメータのポインタ
	int dstBISize;			// (return) infoheaderのサイズ
	BITMAPINFO *pDstBI;		// (return) ここにinfoheaderがallocされる

	// V7 ハイコントラスト指定
	int iContrastMode;
	BYTE ForeColor[3];
	BYTE BackColor[3];

	ImageShrink() {
		xBlockSizeArray = yBlockSizeArray = NULL;
		pDstBI = NULL;
		isGray = FALSE;
		colorReduction = FALSE;
		useDither =TRUE;
		srcBits = NULL;
		state = SHRINK_UNINITIALIZED;
		iContrastMode = CONTRAST_NONE;
		contrastFunc = NULL;
	}
	~ImageShrink() { release(); }

	int init();
	int getLine(BYTE *pDst);
	inline int getRestCount() { return dstHeight - lineCount; }
	void release();
	static int getLineDispatch(BYTE *pDst, void *pshrink) {
		return ((ImageShrink *)pshrink)->getLine(pDst);
	}

private:
	typedef void (ImageShrink::*LPSHKFUNC)(BYTE *);
	enum { SHRINK_UNINITIALIZED = 0, SHRINK_INITIALIZED = 1 };
	int state;
	int srcWidth;
	int srcHeight;
	int srcBitCount;
	int dstBitCount;
	int srcLineBytes;
	int dstLineBytes;
	BYTE *palette;
	int *xBlockSizeArray;
	int *yBlockSizeArray;
	BYTE *srcBits;
	int lineCount;
	BYTE *pSrc;
	BYTE *pDst;
	LPSHKFUNC shkFunc;
	const BYTE *ditherTable;

	int selectDstColor();
	int putDstHeader();
	int setBlockSizeArray();

	// 縮小関数
	void shrinkThrough(BYTE *);
	void shrink1to24(BYTE *);
	void shrink1to8(BYTE *);
	void shrink1to4g(BYTE *);
	void shrink1to4g_A(BYTE *);
	void shrink1to4g_B(BYTE *);
	void shrink1to4g_C(BYTE *);
	void shrink1to4g_D(BYTE *);
	void shrink4to24(BYTE *);
	void shrink4to8(BYTE *);
	void shrink8to24(BYTE *);
	void shrink8to8(BYTE *);
	void shrink8to4g(BYTE *);
	void shrink8to8g(BYTE *);
	void shrink24to24(BYTE *);
	void shrink24to8(BYTE *);

	// ハイコントラスト化する関数
	typedef void (ImageShrink::*LPCONTRASTFUNC)(BYTE *);
	LPCONTRASTFUNC contrastFunc;

	int setContrastFunc();
	
	void addContrastContTo24(BYTE *);
	void addContrastContRevTo24(BYTE *);
	void addContrastBinTo24(BYTE *);
	void addContrastBinRevTo24(BYTE *);
};

class ImageShrinkPack
{
public:
	ImageShrinkPack() {
		lineCount = 0;
		pSrcbuf = p = 0;
		pDstbuf = 0;
	}
	~ImageShrinkPack() {
		if (pDstbuf) delete [] pDstbuf;
	}
	int shrink(ImageShrink *, const BYTE *);
	static int setDataDispatch(BYTE *pDst, void *pshrink) {
		return ((ImageShrinkPack *)pshrink)->setData(pDst);
	}
	BYTE *pDstbuf;
private:
	int lineCount;
	int lineBytes;
	const BYTE *pSrcbuf, *p;
	int setData(BYTE *);
};

// 強調フィルタ関数
void sharpenColor24(const BITMAPINFO *pbih, BYTE *pbits, int grade = 0);

#endif

// 1997.09.17	Komoda		V3用新規作成
// 1997.10.21	Komoda		ImageShrinkPackを追加
// 1997.10.28	Komoda		1bitカラー縮小関数を追加
// 1997.11.07	Komoda		1bit等倍出力ならばデータをそのまま出すモードを追加(モノクロ印刷高速化)
// 1997.12.18	Komoda		AR1807回転性能改善に伴う変更.getRestCount()を追加
// 1998.07.07	Komoda		V3.1モノクロ縮小の高速化
// 2004.10.18	Komoda		V6 AR11135 1bitカラーも24bitで出力する
// 2008.02.25   Tashiro     V7 ハイコントラスト描画対応
