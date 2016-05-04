// File: pd3local.h
// Authors: Shinsuke Nakazawa
// Copyright (C) 2000 by Fuji Xerox Co., Ltd. All rights reserved.

/*
	各PDで共通に用いたいローカル関数の宣言などをここで定義する。
*/

#ifndef _PD3LOCAL_H_
#define _PD3LOCAL_H_

// AR5442対応：ビットマップの作成/解放をローカルクラスにまとめて各PD利用するように修正

class CCheckColorFromBmp
{
public:
	CCheckColorFromBmp();
	~CCheckColorFromBmp();
	HRESULT CreateBmp(MPCSession* session, MP_Dim dim);
	MP_Canvas* GetCanvas();
	HRESULT GetColorType();
	HRESULT Destroy();
private:
	MP_Canvas* canvas;
	HDC_XD hBmpDC;
	HBITMAP_XD hBmp;
	HBITMAP_XD hOldBmp;
	BITMAPINFOHEADER bih;
	BYTE *pBits;
};

#endif // _PD3LOCAL_H_

// CHANGE LOG
// 2000.05.10 - Nakazawa - 新規作成
