// File: magnify.h
// Auther: Toshiyuki Komoda
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef _MAGNIFY_H
#define _MAGNIFY_H

//#include <windows.h>
#include "win2mpf.h"

class Magnify {
public:
	enum Magnification {
		INVALID_MAG,
		MAG200,			// 2倍拡大
		MAG300,			// 3倍拡大
		MAG150,			// 1.5倍拡大
		MAG100,			// 等倍
	};
	Magnify() { finish(); }
	~Magnify() { finish(); }
	void begin(const BITMAPINFO *psrcbi, BITMAPINFO *pdstbi, Magnification magnification);
	void get(const BYTE *psrcbits, BYTE *pdstbits);
	void finish();
private:
	Magnification mag;
	int srcWidth;
	int srcLineBytes;
	int dstLineBytes;
	void mag200(const BYTE *, BYTE *);
	void mag300(const BYTE *, BYTE *);
	void mag150(const BYTE *, BYTE *);
	void mag100(const BYTE *, BYTE *);
};

#endif

//CHANGE LOG
//97.11.05 - Komoda - 新規作成
//97.12.19 - Sumida - AR1510：mag100()を追加
