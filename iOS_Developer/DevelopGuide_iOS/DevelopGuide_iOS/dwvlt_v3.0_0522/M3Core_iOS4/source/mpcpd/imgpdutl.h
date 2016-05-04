// File: imgpdutl.h
// Authors: Ryoji Matsumura, Toshiyuki Komoda
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _IMAGE_UTIL_H_
#define _IMAGE_UTIL_H_

#include "mpc_api.h"

//#include <windows.h>
#include "win2mpf.h"

#include "imgrot.h"

//struct WinCoord { MP_Rect log; MP_Rect dev; };
struct WinRect {
    POINT pos;
    SIZE dim;
};
struct WinCoord {
    WinRect log;
    WinRect dev;
};
bool getWindowCoordinate(MP_Canvas *canvas, int degree, MP_Dim m_dim, WinCoord *win);

// int getNeedLine(HDC_XD hDC, int prevNeedLine, int degree, SIZE cacheSize, const WinCoord *win);

//・バンド画像->cache, cache->dev に転送 (回転角に依存)
// OnDrawのみ使う
struct TransferParam {
	HDC_XD hDC;
	HDC_XD hBmpDC;
	BYTE *pbits;
	BITMAPINFO *pbi;
	int lineOfs;
	int nLine;
	int dstW;
	int dstH;
};

// WinMobile対応 メモリ不足での描画ミスを検出
// 09/12/21 M.Chikyu
#ifndef _M3CORE_MP_
void transferToDevice (int degree, const TransferParam *p, const WinCoord *win);
void transferToCacheAndDevice (int degree, const TransferParam *p, const WinCoord *win);
#else
bool transferToDevice (int degree, const TransferParam *p, const WinCoord *win);
#endif



int is_gray(BITMAPINFO *pbi);
//int set_bmp_to_file(MP_Path *path, ImageRotate *rot, unsigned long need_bytes, HRESULT *phres = 0);
int set_bmp_to_file(MP_Path *path, ImageRotate *rot, unsigned long need_bytes, HRESULT *phres = 0, MPC_AdvCancelInfo* info = NULL);
//07.09.19 - M.Chikyu UNICODE対応
// 対応関数の追加
int set_bmp_to_fileW(const MP_WPath *pathW, ImageRotate *rot, unsigned long need_bytes, HRESULT *phres = 0, MPC_AdvCancelInfo* info = NULL);

enum print_result_t { print_error = -1, print_success = 0, print_cancel = 1};
//AR2705: print_rotateをprint_rotateとprint_rotate_MonoFastに分けた
//AR4036: モノクロパレットを反転するかどうかのフラグを追加
print_result_t print_rotate(HDC_XD hDC, MP_Integer degree, WinCoord *win, ImageRotate *rot, unsigned char *buf, MPC_AdvCancelInfo *info, BOOL_XD forceUseStretchDIBits, BOOL_XD monoInvert = FALSE);
print_result_t print_rotate_MonoFast(HDC_XD hDC, MP_Integer degree, WinCoord *win, ImageRotate *rot, unsigned char *buf, MPC_AdvCancelInfo *info, BOOL_XD monoInvert = FALSE);

#ifndef WIDTHBYTES
    #define WIDTHBYTES(i)   (((i) + 31) / 32 * 4)	// BMP/DIB の１行あたりのバイト数（４バイトバウンダリ）
#endif

HPALETTE CreateMediaPalette();

enum NeedMagnifyResult { no_mag, need_mag, need_mag_with_trim };
NeedMagnifyResult needMagnify(
    HDC_XD hDC,//in
    BITMAPINFO *pbi,//in
    MP_Integer degree,//in
    WinCoord *win,//inout
    int *mag,//out
    POINT *trimOffset,//out
    SIZE *trimSize//out
);

HANDLE BitmapToDIB(HBITMAP_XD hBitmap, HPALETTE hPal);
HBITMAP_XD DIBToBitmap(HANDLE hDIB, HPALETTE hPal);

HBITMAP_XD RotateHBITMAP(MPCSession *session, HBITMAP_XD org, HPALETTE hPal, MP_Integer degree);
unsigned long get_HBITMAP_size(HBITMAP_XD hBitmap);
int getBISize(BITMAPINFO *);

int NewStretchDIBits(
    HDC_XD  hdc,     // handle of device context
    int  XDest,     // x-coordinate of upper-left corner of dest. rect.
    int  YDest,     // y-coordinate of upper-left corner of dest. rect.
    int  nDestWidth,  // width of destination rectangle
    int  nDestHeight, // height of destination rectangle
    int  XSrc,     // x-coordinate of upper-left corner of source rect.
    int  YSrc,     // y-coordinate of upper-left corner of source rect.
    int  nSrcWidth,   // width of source rectangle
    int  nSrcHeight,  // height of source rectangle
    VOID  *lpBits,    // address of bitmap bits
    BITMAPINFO *lpBitsInfo,   // address of bitmap data
    UINT  iUsage,  // usage
    DWORD  dwRop   // raster operation code
);


#ifndef _M3CORE_MP_
int NewStretchBlt(HDC_XD hdc, int xdest, int ydest, int cxdest, int cydest,
	HDC_XD hdcsrc, int xsrc, int ysrc, int cxsrc, int cysrc, DWORD rop);
#endif


//n 
enum comp_type {comp_mmr = 1, comp_mh = 2};
typedef struct tag_CompInfo {
	int nSize;
	unsigned char* pCompBuf;
	unsigned long compSize;
	unsigned long width;
	unsigned long height;
	unsigned long xreso;	// (PelsPerMeter)
	unsigned long yreso;	// (PelsPerMeter)
	comp_type compType;
} CompInfo;

//n V4 CompInfoの情報からTIFFのヘッダを作成する
HRESULT GetTiffHeaderFromCompInfo(CompInfo* pCompInfo, BYTE* pHeader = NULL);

#endif //! _IMAGE_UTIL_H_

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//97.11.11 - Sumida - AR1510: useMagnify()を追加
//97.11.11 - Sumida - AR1510: print_rotate()に引数isMonoFastPrintを追加
//97.12.10 - matsu - AR1511:モノクロイメージ変換出力(1bit->1bit)性能改善のため強制StretchDIBitsモードを追加(print_rotate)
//97.12.10 - matsu - AR1690:「イメージ切り取り・イメージ変換出力で、95だと白く抜けてしまう場合がある」の対策.NewStretchDIBits()を追加.
//97.12.18 - komoda - AR1807:回転性能改善のためRotateHBITMAP,get_HBITMAP_size,BitmapToDIB,DIBToBitmap,getBISizeを追加
//98.03.20 - matsu - AR2705: print_rotateをprint_rotateとprint_rotate_MonoFastに分けた
//98.05.06 - matsu - V3.1モノクロ高速印刷ルーチン共通化: 新規needMagnify()
//98.05.11 - matsu - V3.1対応: set_bmp_to_file()でFile I/O系のエラーを返せるようにした。
//98.05.22 - komoda - AR2800対応: needMagnify()の引数を変更
//99.05.11 - Nakazawa - V4 TIFF取り出しのため CompInfo, CompInfoToTIFF 追加
//99.05.28 - Nakazawa - V4 GetTiffHeaderFromCompInfo 作成
//99.08.03 - Nakazawa - V4 コードレビューの結果を反映
//99.09.03 - Nakazawa - V4 AR4036対応: モノクロパレットを反転するかどうかのフラグを追加
//02.02.22 - Komoda - V5 キャッシュなし表示対応
//02.07.18 - Komoda - V5 AR7530 NewStretchBltを追加
//04.10.18 - Komoda - V6 AR11201 Win9xでキャッシュビットマップのサイズが異常になる不具合の修正
