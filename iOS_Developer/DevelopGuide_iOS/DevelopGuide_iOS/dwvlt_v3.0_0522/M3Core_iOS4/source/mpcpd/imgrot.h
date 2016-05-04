// File: imgrot.h
// Author: Toshiyuki KOMODA
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _IMGROT_H
#define _IMGROT_H

//#include <windows.h>
#include "win2mpf.h"

class ImageRotate
{
public:
	enum {
		ROTATE_OK = 0,
		ROTATE_ERROR = -1,
		ROTATE_COMPLETE = 0,
		ROTATE_INCOMPLETE = 1
	};
	enum { MODE_PART = 1, MODE_PAGE = 0 };	// mode に使用
	typedef int (* LPGETFUNC)(BYTE *, void *);

	int mode;			// 部分かページか
	int angle;			// 回転角 : 0,90,180,270
	int nLine;			// バンド幅  (rotateで返る) 実際に処理したライン数
	BITMAPINFO *pSrcBI;	// 入力画像のbmpinfo
	int srcBISize;		// 入力画像のbmpinfoのサイズ
	BITMAPINFO *pDstBI;	// 出力画像のbmpinfo (initで返る/PARTモードならばrotate()で変化)
	int dstBISize;		// 出力画像のbmpinfoのサイズ (initで返る)
	LPGETFUNC getLine;	// srcBitsに1ライン出力する関数のポインタ
	void *getParam;		// getLineに必要なパラメータ構造体のポインタ
	int dstHeight;		// 出力画像の高さ (initで返る)
	int dstWidth;		// 出力画像の高さ (initで返る)
	int dstBufSize;		// 出力バッファのサイズ (initで返る)
	int srcLineBytes;	// 1ラインのbyte数 (initで返る)
	int dstLineBytes;	// 1ラインのbyte数 (initで返る)

	ImageRotate() {
		mode = MODE_PART;
		angle = 0;
		nLine = 0;
		pSrcBI = NULL;
		pDstBI = NULL;
		srcBISize = 0;
		dstBISize = 0;
		getLine = NULL;
		getParam = NULL;
		state = ROTATE_EMPTY;
		srcBits = NULL;
	}
	~ImageRotate() { release(); }

	int init();
	int rotate(BYTE *dstBits);
	void release();

private:
	enum { ROTATE_EMPTY = -1 };	// state に使用
	int state;				// ROTATE_UNITITIALIZED, MODE_PART, MODE_PAGE
	int lineCount;			// 処理済line数
	int columnCount;		// 左端からの列数
	int bitCount;
	int srcW, srcH;
	BYTE *pSrc, *pDst;		// カレントポインタ
	BYTE *srcBits;			// 入力buf
	typedef void (ImageRotate::*LPROTFUNC)();
	LPROTFUNC rotFunc;
	void resetPointer(BYTE *dstBits);
	void rotate1r90();
	void rotate1r180();
	void rotate1r270();
	void rotate4r90();
	void rotate4r180();
	void rotate4r270();
	void rotate8r90();
	void rotate8r180();
	void rotate8r270();
	void rotate16r90();
	void rotate16r180();
	void rotate16r270();
	void rotate24r90();
	void rotate24r180();
	void rotate24r270();
	void rotate32r90();
	void rotate32r180();
	void rotate32r270();
};

class ImageRotatePack
{
public:
	ImageRotatePack() {
		lineCount = 0;
		pSrcbuf = p = 0;
		pDstbuf = 0;
	}
	~ImageRotatePack() {
		if (pDstbuf) delete [] pDstbuf;
	}
	int rotate(ImageRotate *, const BYTE *);
	static int setDataDispatch(BYTE *pDst, void *pRotatePack) {
		return ((ImageRotatePack *)pRotatePack)->setData(pDst);
	}
	BYTE *pDstbuf;
private:
	int lineCount;
	int lineBytes;
	const BYTE *pSrcbuf, *p;
	int setData(BYTE *);
};

#endif

// 1997.09.13	Komoda		V3用新規作成
// 1997.12.18	Komoda		AR1807回転性能改善:bmpinfoを入力と出力とで別にした
// 1999.05.19	Komoda		ImageRotatePackを追加
// 1999.09.17	Komoda		V4 AR4860 16bit,32bitDIB対応
