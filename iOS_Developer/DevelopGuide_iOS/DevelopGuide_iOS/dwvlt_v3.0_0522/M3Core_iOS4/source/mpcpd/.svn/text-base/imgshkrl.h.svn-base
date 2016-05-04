// File: imgshkrl.h
// Author: Shinsuke Nakazawa
// Copyright (C) 1998 by Fuji Xerox Co., Ltd. All rights reserved.

// ランレングスデータを受け取り、DIB伸長せずに縮小するクラス

#ifndef _IMGSHKRL_H
#define _IMGSHKRL_H

//#include <windows.h>
#include "win2mpf.h"

class ImageShrinkRL
{
public:
	enum {
		SHRINK_OK = 0,
		SHRINK_ERROR = -1,
		SHRINK_COMPLETE = 0,
		SHRINK_INCOMPLETE = 1,
	}; // init, getLineの戻り値
	enum {
		CONTRAST_NONE = 0,
		CONTRAST_BIN = 1,
		CONTRAST_CONT = 2,
		CONTRAST_CONT_REV = 3,
		CONTRAST_BIN_REV = 4 };

	BITMAPINFO *pSrcBI;		// 入力画像のinfoheader
	int dstWidth;			// 要求サイズ
	int dstHeight;			// 要求サイズ
	int dstBISize;			// (return) infoheaderのサイズ
	BITMAPINFO *pDstBI;		// (return) ここにinfoheaderがallocされる
	unsigned char* pRL;				// ランレングスデータへのポインタ
	int getLine(unsigned char *pDst);	// ランレングスデータから縮小後の1Lineを取得する

	int iContrastMode;
	BYTE ForeColor[3];
	BYTE BackColor[3];

	ImageShrinkRL();
	~ImageShrinkRL();

	int init();
	void release();
	inline int getRestCount() { return dstHeight - lineCount; }
	static int getLineDispatch(unsigned char *pDst, void *pshrinkrl) {
		return ((ImageShrinkRL*)pshrinkrl)->getLine(pDst);
	}

private:
	typedef void (ImageShrinkRL::*LPSHKFUNC)(unsigned char *);
	enum {SHRINK_UNINITIALIZED = 0, SHRINK_INITIALIZED = 1};
	int state;
	int srcWidth;
	int srcHeight;
	int srcBitCount;
	int dstBitCount;
	int dstLineBytes;
	int *xBlockSizeArray;
	int *yBlockSizeArray;
	int lineCount;
	LPSHKFUNC shkFunc;
	unsigned char* pCurrentRL;		// 現在見ているランレングスデータへのポインタ
	int* countLine;					// 縮小後1Line分の画素カウント用

	int putDstHeader();
	int setBlockSizeArray();
	void shrink1to4g(unsigned char *pDst);
	void shrinkThrough(unsigned char *);

	int setContrastFunc();

};

#endif

//CHANGE LOG
//1998.11.11 - Nakazawa	- V4用新規作成
//1999.08.03 - Nakazawa - V4 コードレビューの結果を反映
//1999.08.27 - Nakazawa - AR4580対応: ImageShrinkとの互換性維持のためgetRestCount追加
