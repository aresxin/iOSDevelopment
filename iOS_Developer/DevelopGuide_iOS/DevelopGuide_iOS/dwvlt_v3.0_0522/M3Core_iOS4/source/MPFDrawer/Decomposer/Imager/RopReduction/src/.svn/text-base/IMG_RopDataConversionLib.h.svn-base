/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_RopDataConversionLib.h - ROP置換におけるデータ変換処理のライブラリヘッダ
 * Yozo Kashima 26.Oct.2001
 *
 */

#ifndef INC_IMG_RopDataConversionLib_h
#define INC_IMG_RopDataConversionLib_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"

/*
 * 構造体の定義
 */

typedef struct img_ropdataconvpalette {
	IMG_UINT8	depth;		/* paletteDataのdepth */
	IMG_UINT16	entries;	/* palette tableのエントリー数 */
	IMG_UINT16	size;		/* palette tableのバイト数 */
	IMG_UINT8	*table;		/* palette tableデータ */
} IMG_RopDataConvLib_Palette;

typedef struct img_ropdataconvlib_image {
	IMG_Context					*context;
	IMG_ColorSpace				space;
	IMG_ColorInterleave			interleave;
	IMG_UINT8					depth;
	IMG_UINT32					width;
	IMG_UINT32					height;
	IMG_UINT8					*data;
	IMG_RopDataConvLib_Palette	palette;
} IMG_RopDataConvLib_Image;

/*
 * イメージを変換した結果得られるマスクデータの情報
 */
typedef struct img_ropdataconvlib_mask {
	IMG_UINT8		*data;			/* マスクデータ */
	IMG_UINT32		size;			/* マスクデータサイズ */
	IMG_BOOL		isInverted;		/* ビット反転されたかどうか */
} IMG_RopDataConvLib_Mask;

/*
 * ピクセルのビットパターン識別子
 */
typedef enum {
	IMG_PIXEL_NULL	= 0x00,		/* 指定なし */
	IMG_PIXEL_BLACK	= 0x01,		/* 黒のピクセル(BGRなら全ビット0，PrinterGrayなら全ビット1) */
	IMG_PIXEL_WHITE	= 0x02,		/* 白のピクセル(BGRなら全ビット1，PrinterGrayなら全ビット0) */
	IMG_PIXEL_COLOR	= 0x04,		/* カラー値のピクセル */
} IMG_PixelType;

typedef struct img_ropdataconvlib_pixelmap {
	IMG_PixelType	whitePixel;
	IMG_PixelType	blackPixel;
} IMG_RopDataConvLib_PixelMap;

/*
 * サービス関数
 */
extern int IMG_RopDataConvLib_IsBlackAndWhiteImage(
	IMG_RopDataConvLib_Image	*info,
	IMG_BOOL					*result);

/*
 * イメージをマスクに変換する。
 *
 * ピクセルをビットに割り当てた結果は以下のようになる。
 *
 * - isInvertedがIMG_TRUEの場合 -
 *     白のピクセルは，'1'に割り当てられている。
 *     黒のピクセルは，'0'に割り当てられている。
 *
 * - isInvertedがIMG_FALSEの場合 -
 *     白のピクセルは，'0'に割り当てられている。
 *     黒のピクセルは，'1'に割り当てられている。
 *
 * ここで，白のピクセルはBGRではFFFFFFh，PrinterGrayでは00hであり，
 * 黒のピクセルはBGRでは000000h，PrinterGrayではFFhのことである。
 */
extern int IMG_RopDataConvLib_ConvertImageToMask(
	IMG_RopDataConvLib_Image	*image,				/* 変換対象イメージ情報 */
	IMG_RopDataConvLib_Mask		*mask);				/* 変換後のマスク情報 */

extern int IMG_RopDataConvLib_GetPixelMap(
	IMG_RopDataConvLib_Image	*info1,
	IMG_RopDataConvLib_Image	*info2,
	IMG_BOOL					*result,
	IMG_RopDataConvLib_PixelMap	*pixelMap);

#endif /* INC_IMG_RopDataConversionLib_h */

/*
 * Log
 * 25.Oct.2001 Yozo Kashima Created
 * 30.Oct.2001 Yozo Kashima ROP3-136(DSa)がクリップとして使用されるケースに対応。
 *							(qx4001t0-01,qx4003t0-03,wx4004t1-04,qx4013l0-13)
 * 16.Nov.2001 Yozo Kashima 2StepROPの置換処理を実装。
 *							I/Fを変更。
 *							高速化のためマクロ化。
 * 02.Apr.2003 Yozo Kashima AR#1090,AR#1167対応(ピクセルのタイプを0,1のビットパターンとして扱う)。
 * 04.Apr.2003 Yozo Kashima AR#1186,AR#1187対応(ピクセルタイプの考え方を元に戻す)。
 */

/* end of IMG_RopDataConversionLib.h */
