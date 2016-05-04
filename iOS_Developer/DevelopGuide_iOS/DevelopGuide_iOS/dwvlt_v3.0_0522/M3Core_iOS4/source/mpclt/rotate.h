// File: rotate.h
// Auther: Hideki Ichiriki
// Copyright(C) 1996,1997 by Fuji Xerox Co,. Ltd. All right reserved.

#include "mpc_api.h"

//#include <windows.h>

#include "win2mpf.h"

#ifdef _DEBUG
#ifndef _M3CORE_MP_
#include <crtdbg.h>
#endif
#endif

#define WIDTHBYTES(i)   ((i+31)/32*4)	// BMP/DIB の１行あたりのバイト数（４バイトバウンダリ）

HGLOBAL RotateBit1Angle90(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit1Angle180(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit1Angle270(const BITMAPINFO* bi, const unsigned char* imagedata);

HGLOBAL RotateBit4Angle90(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit4Angle180(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit4Angle270(const BITMAPINFO* bi, const unsigned char* imagedata);

HGLOBAL RotateBit8Angle90(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit8Angle180(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit8Angle270(const BITMAPINFO* bi, const unsigned char* imagedata);

HGLOBAL RotateBit16Angle90(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit16Angle180(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit16Angle270(const BITMAPINFO* bi, const unsigned char* imagedata);

HGLOBAL RotateBit24Angle90(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit24Angle180(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit24Angle270(const BITMAPINFO* bi, const unsigned char* imagedata);

HGLOBAL RotateBit32Angle90(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit32Angle180(const BITMAPINFO* bi, const unsigned char* imagedata);
HGLOBAL RotateBit32Angle270(const BITMAPINFO* bi, const unsigned char* imagedata);


inline unsigned short DibNumColors (const BITMAPINFOHEADER* lpbi)
{
    INT                 bits;
    LPBITMAPCOREHEADER  lpbc;

    lpbc = ((LPBITMAPCOREHEADER)lpbi);

    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits){
        case 1:
                return 2;
        case 4:
                return 16;
        case 8:
                return 256;
        default:
                /* A 24 bitcount DIB has no color table */
                return 0;
    }
}

inline unsigned short PaletteSize (const BITMAPINFOHEADER* lpbi)
{
    WORD               NumColors;

    NumColors = DibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return (WORD)(NumColors * sizeof(RGBTRIPLE));
    else
        return (WORD)(NumColors * sizeof(RGBQUAD));
}

//CHANGE LOG
//97.1.24 - Ichiriki - 作成
