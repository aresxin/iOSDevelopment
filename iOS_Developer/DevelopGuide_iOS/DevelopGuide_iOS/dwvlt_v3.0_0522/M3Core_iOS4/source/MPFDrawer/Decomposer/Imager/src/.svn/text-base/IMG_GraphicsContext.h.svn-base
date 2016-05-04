/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_GraphicsContext.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_GraphicsContext_h
#define INC_IMG_GraphicsContext_h

#include "IMG_Builtin.h"
#include "IMG_Common.h"
#include "IMG_Matrix.h"

typedef struct img_graphicscontext {
	IMG_RectangleData	boundingBox;			/* ページのバウンディングボックス */
	IMG_DrawMode		drawMode;				/* 描画方式(Fill/Stroke) */
	IMG_RopMode			ropMode;				/* ROPモード */
	IMG_UINT32			ropCode;				/* ROPコード */
	IMG_FillRule		fillRule;				/* Fill規則 */
	IMG_FLOAT			strokeWidth;			/* ストローク幅 */
	IMG_CapStyle		capStyle;				/* キャップスタイル */
	IMG_JoinStyle		joinStyle;				/* ジョインスタイル */
	IMG_FLOAT			miterLimit;				/* マイターリミット */
	IMG_LineStyle		lineStyle;				/* ライン形状 */
	IMG_FLOAT			lineStartOffset;		/* 任意形状スタートオフセット(lineStyleがIMG_LINE_ANYの時のみ有効) */
	IMG_UINT16			lineMaskDataCount;		/* 任意形状マスクデータ個数(lineStyleがIMG_LINE_ANYの時のみ有効) */
	IMG_FLOAT			*lineMaskData;			/* 任意形状マスクデータ列へのポインタ(lineStyleがIMG_LINE_ANYの時のみ有効。ヒープ上の領域) */
	IMG_BOOL			fillZeroAreaRegion;		/* 面積0のFillを行うかどうかを示す */
	IMG_BOOL			thickenOnePixelLine;	/* 細線強調を行うかどうかを示す */
	IMG_BOOL			adjustStroke;			/* ストローク調整を行うかどうかを示す */
	IMG_Matrix			ctm;					/* カレントマトリクス*/
	IMG_BOOL			clipDrawing;			/* クリップのための描画中かどうかを示す */
} IMG_GraphicsContext;


/*
 * 微小図形を描画すべきかどうかの問い合わせ
 *
 * fillZeroAreaRegionフラグがONであって，かつ
 * クリップ描画中か上書き描画中の時だけ
 * 面積ゼロの図形を描画する。
 */
#define IMG_SHOULD_DRAW_SMALL_FIGURE(gc)	\
	gc->fillZeroAreaRegion &&										\
	  ( gc->clipDrawing ||											\
	    ( (gc->ropMode == IMG_ROP2 && gc->ropCode == 13) ||			\
	      (gc->ropMode == IMG_ROP3 && gc->ropCode == 204) ) )

/* INC_IMG_GraphicsContext_h */
#endif

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 03.Apr.2001 Yozo Kashima ropCodeの型をIMG_UINT32に修正。
 *							adjustStrokeを追加。
 * 06.Apr.2001 Yozo Kashima ctmを追加。
 * 05.Apr.2001 Yozo Kashima clipDrawingを追加。
 * 31.Aug.2001 Yozo Kashima lineStartOffset,lineMaskDataCount,lineMaskDataを追加。
 * 14.Sep.2001 Yozo Kashima miterLimitのマイターリミット長の型をIMG_UINT32からIMG_FLOATに変更。
 * 13.Mar.2003 Yozo Kashima AR#1139対応。微小図形描画判定を修正。
 */

/* end of IMG_GraphicsContext.h */
