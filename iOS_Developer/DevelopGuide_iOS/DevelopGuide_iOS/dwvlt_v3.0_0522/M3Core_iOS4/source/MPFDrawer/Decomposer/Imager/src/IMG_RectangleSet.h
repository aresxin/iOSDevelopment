/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2004. All rights reserved.
 *
 * IMG_RectangleSet.h	- 矩形集合オブジェクトの定義
 *
 * Created: 2004/6/2 Yozo Kashima
 */

#ifndef INC_IMG_RectangleSet_H
#define INC_IMG_RectangleSet_H

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"

/* 構造体宣言 */
typedef struct img_rectangleset {
	IMG_GeometricShape super;

	IMG_Context *context;		/* Imager実行環境 */
	IMG_UINT16	nrect;			/* 総矩形数 */
	IMG_UINT16	blocks;			/* ブロック数 */
	IMG_REAL32	startY;			/* 最初の矩形の左上点のY座標 */
	IMG_UINT16	*lines;			/* ライン数 */
	IMG_UINT16	*columns;		/* 列数 */
	IMG_REAL32	*height;		/* 矩形群の高さ */
	IMG_REAL32	*x;				/* num個の描画開始点のX座標 */
	IMG_REAL32	*width;			/* num個の矩形の幅 */
	IMG_BOOL	canOwnData;		/* xとwidthの配列を所有できるかどうか? */

} IMG_RectangleSet;

extern IMG_GeometricShape *IMG_RectangleSet_Create(
	IMG_Context *context,	/* Imager実行環境 */
	IMG_UINT16	nrect,		/* 総矩形数 */
	IMG_UINT16	blocks,		/* ブロック数 */
	IMG_REAL32	startY,		/* 最初の矩形の左上点のY座標 */
	IMG_UINT16	*lines,		/* ライン数 */
	IMG_UINT16	*columns,	/* 列数 */
	IMG_REAL32	*height,	/* 矩形群の高さ */
	IMG_REAL32	*x,			/* num個の描画開始点のX座標 */
	IMG_REAL32	*width,		/* num個の矩形の幅 */
	IMG_BOOL	canOwnData);/* データを所有できるかどうか? */

#endif /* INC_IMG_RectangleSet_H */
