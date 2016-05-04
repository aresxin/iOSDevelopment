/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_DisplayList.h - last edit
 * Yozo Kashima 29-Mar-01
 *
 */

#ifndef INC_IMG_DisplayList_h
#define INC_IMG_DisplayList_h

#include "IMG_Builtin.h"
#include "IMG_Common.h"

#define PM_SAVE_CLIP

typedef struct img_displaylist* IMG_DisplayListPointer;
typedef struct img_displaylist {
	int (*destroy)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

#ifndef DOCUWORKS_VIEWER
	int (*startPage)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_UINT32 pageWidth,				/* デバイス空間上のページの幅(ピクセル) */
		IMG_UINT32 pageHeight,				/* デバイス空間上のページの高さ(ピクセル) */
		IMG_ColorMode colorMode,			/* カラーモード */
		COM_DeviceColorSpace *pmParameter,
		int	rotation );						/* 論理ページを物理ページへ変換する際の回転方向	*/
#else
	int (*startPage)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_UINT32 pageWidth,				/* デバイス空間上のページの幅(ピクセル) */
		IMG_UINT32 pageHeight,				/* デバイス空間上のページの高さ(ピクセル) */
		IMG_ColorMode colorMode,			/* カラーモード */
		COM_DeviceColorSpace *pmParameter,
		int rotation,						/* 論理ページを物理ページへ変換する際の回転方向	*/
		unsigned char *pageBuffer,			/* ページバッファ */
		long lineSize,						/* １ラインのドット数 */
		long depth,							/* 色の深さ */
		void *DC);							/* DDBのコンテキスト */
#endif

	int (*endPage)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

	int (*showPage)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		COM_DeviceColorSpace *rndParameter,
		void *colorParameter,				/* 色変換パラメータ */
		COM_OutputLocation *location);

	int (*setRotationAdjustment)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_INT32				x,			/* X方向の調整値(ピクセル) */
		IMG_INT32				y);			/* Y方向の調整値(ピクセル) */

	int (*setSolidColor)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_ColorData colorData);			/* 色値 */

	int (*setPatternColor)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_PatternData* patternData);		/* パターンデータの情報 */

	int (*setRopInfo)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_RopMode mode,					/* ROPモード */
		IMG_UINT32 code);					/* ROPコード */
	
	int (*startAttribute)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_ObjectTag);						/* 描画オブジェクトタグ種別 */

	int (*endAttribute)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

	int (*initClip)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

	int (*offsetClip)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		float	xOffset,					/* x軸方向の移動量 */
		float	yOffset);					/* y軸方向の移動量 */

	int (*startClip)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_ClipRopMode	clipRopMode,		/* クリップの論理演算モード */
		IMG_BOOL		isNativeClip);		/* NativeClip(ImagerI/Fを通じて指定された
												クリップ命令かどうかを指定する) */
	int (*endClip)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

#ifdef PM_SAVE_CLIP
	int (*saveClip)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

	int (*restoreClip)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */
#endif
	int (*drawEdge)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_EdgeData *edge);				/* 水平エッジデータ */

	int (*drawVEdge)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_VEdgeData *edge);				/* 垂直エッジデータ */

	int (*drawRectangle)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_RectangleData *rectangle,		/* 長方形データ */
		IMG_BOOL doAdjustX,					/* 回転時のX方向の調整をするか否か */
		IMG_BOOL doAdjustY);				/* 回転時のX方向の調整をするか否か */

	int (*drawTrapezoid)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_TrapezoidData *trapezoid);		/* 台形データ */

	int (*drawLine)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_LineData *line);				/* 線データ */

	int (*drawBitmap)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_BitmapData *bitmap,				/* Bitmapデータ */
		IMG_BOOL doAdjustX,					/* 回転時のX方向の調整をするか否か */
		IMG_BOOL doAdjustY);				/* 回転時のX方向の調整をするか否か */

	int (*drawBitmapFont)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_BitmapFontData *bitmapFont);	/* BitmapFontデータ */

	int (*drawImageInfo)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_ImageData *image,				/* Imageデータ */
		IMG_BOOL doAdjustX,					/* 回転時のX方向の調整をするか否か */
		IMG_BOOL doAdjustY);				/* 回転時のX方向の調整をするか否か */

	int (*drawImageSet)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

	int (*drawGrayMaskInfo)(
		IMG_DisplayListPointer object,		/* DisplayListオブジェクト */
		IMG_GrayMaskData *gmask,				/* GrayMaskデータ */
		IMG_BOOL doAdjustX,					/* 回転時のX方向の調整をするか否か */
		IMG_BOOL doAdjustY);				/* 回転時のX方向の調整をするか否か */

	int (*drawGrayMaskSet)(
		IMG_DisplayListPointer object);		/* DisplayListオブジェクト */

#ifndef IMG_FM_NODEFINE
	int (*startFontAttribute)(
       		IMG_DisplayListPointer object,
		IMG_ObjectTag);
 
	int (*endFontAttribute)(
               	IMG_DisplayListPointer object);
 
	int (*setLogFont)(
               	IMG_DisplayListPointer  object,
               	IMG_FM_LogFont          *logFont,
           	IMG_FM_Matrix               *device);
                                
	int (*drawCodeFont)(
               	IMG_DisplayListPointer object,
               	IMG_FM_Point            *point,
               	IMG_FM_CodeString       *codeString,
               	IMG_FM_RectOption       rectOption,
               	IMG_FM_Rect             *clipRect);
 
	int (*drawDataFont)(
               	IMG_DisplayListPointer object,
               	IMG_FM_Point            *point,
               	IMG_FM_DataCharacter    *dataCharacter,
           	IMG_FM_Matrix               *device);

	int (*startFontRegister)(
               	IMG_DisplayListPointer object);

	int (*endFontRegister)(
               	IMG_DisplayListPointer object);

	int (*getFontRegister)(
               	IMG_DisplayListPointer object,
               	char                   **dataAdress,
               	int                    *numOfChar);
#endif


} IMG_DisplayList;


#endif /* INC_IMG_DisplayList_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 06.Apr.2001 Yozo Kashima setRopInfoのcode引数の型をIMG_UINT32に変更。
 * 10.Apr.2001 Hada Toru	drawBitmapFontを追加
 * 20.Dec.2001 Yozo Kashima 障害#178(イメージに白筋)に対応。
 *							startClipにisNativeClip引数を追加。
 * 13.Mar.2003 Yozo Kashima AR#988対応。setRotationAdjustment関数とadjustmentX,adjustmentYメンバ変数を追加。
 */

/* end of IMG_DisplayList.h */
