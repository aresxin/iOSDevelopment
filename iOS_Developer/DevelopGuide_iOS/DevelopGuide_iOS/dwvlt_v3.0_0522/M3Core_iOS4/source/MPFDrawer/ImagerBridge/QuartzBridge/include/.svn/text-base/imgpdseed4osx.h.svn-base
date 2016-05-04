//
//  IMAGEPDSEED4OSX.H
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

//
// FOR DWVLT4OSX Only
//
// ImgPDSeedに共通の親を定義する

#include "mpc_api.h"
#include "w2m_gdi.h"

#ifndef IMAGEPDSEED4OSX_H
#define IMAGEPDSEED4OSX_H

// GetLine()の返り値の定義
#define MPPD_GETLINE_CONTINUE	0
#define MPPD_GETLINE_COMPLETE	1
#define MPPD_GETLINE_ERROR	-1

class ImageShrink;

class ImgPDSeed4OSX {

private:

	
public:
	virtual ~ImgPDSeed4OSX(){};
	
    // PDが持つ画像データを丸ごと返す。
    // デコード済みか否かはPDによって異なる。
    virtual MP_Octet* GetOctStr() PURE;

    // GetOctStrで変えるデータのサイズを返す。
    virtual long GetOctLen() PURE;
    
    // ビットマップヘッダを返す
    virtual unsigned char* GetBitmapHeader() PURE;    

    // ビットマップヘッダのサイズを返す
    virtual long GetBitmapHeaderSize() PURE;    

    // デコード済みDIBフォーマットの画像データを一行返す
    virtual int GetLine(unsigned char* buffer) PURE;

    // GetLineが呼べるかどうか返す
    virtual int	EnableGetLine() PURE;

    // １ラインのバッファのサイズを返す
    virtual long GetLineWidthBytes() PURE;

    // PDの圧縮形式の種類を返す
    virtual int	GetPDCompressMode() PURE;

    // ビットマップヘッダを解放する
    virtual void FreeBitmapHeader(unsigned char *pInfo) PURE;

    // 出力画像サイズを指定する
    virtual void SetDstSize(int width, int height) PURE;
};

#endif // IMAGEPDSEED4OSX_H
