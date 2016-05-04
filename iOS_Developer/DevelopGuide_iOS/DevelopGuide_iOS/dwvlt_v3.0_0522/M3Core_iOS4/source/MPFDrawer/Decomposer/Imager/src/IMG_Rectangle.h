/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_Rectangle.h	IMG関連ヘッダファイル
 * Edited:	Apr, 4,2001	Kenichi Ishida
 * Modified:	Apr,20,2001	Toshio Yamazaki		stroke()の実装
 */

#ifndef IMGRECTANGLE_H_INCLUDED
#define IMGRECTANGLE_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_GeometricShape.h"

/* Redefinedになってるからコメントアウト by tyama
typedef struct img_context IMG_Context;
typedef struct img_rectangledata IMG_RectangleData;*/

/* 構造体宣言 */
/*
 *	y
 *	|
 *	| left top ->	+-------+
 *	|		|	|
 *	|		|	|
 *	|		|	|
 *	|		+-------+ <- right bottom 
 *	|
 *	(0,0)------------------------------------x
 *
 *	IMG_Rectangle.point1 == left top,
 *	IMG_Rectangle.point2 == right bottom,
 */
typedef struct img_rectangle {
	IMG_GeometricShape super;
	
	IMG_Context *context;			/* Imager実行環境 */
	IMG_Point point1;				/* 矩形座標 */
	IMG_Point point2;				/* 矩形座標 */
	IMG_BOOL drawRightBottom;		/* 右端と下端を描画するかどうか */
} IMG_Rectangle;

extern IMG_GeometricShape *IMG_Rectangle_Create(
	IMG_Context *context,			/* Imager実行環境 */
	IMG_Point *point1,				/* 矩形座標 */
	IMG_Point *point2,				/* 矩形座標 */
	IMG_BOOL drawRightBottom);		/* 右端と下端を描画するかどうか */

#endif	/* IMGRECTANGLE_H_INCLUDED */
