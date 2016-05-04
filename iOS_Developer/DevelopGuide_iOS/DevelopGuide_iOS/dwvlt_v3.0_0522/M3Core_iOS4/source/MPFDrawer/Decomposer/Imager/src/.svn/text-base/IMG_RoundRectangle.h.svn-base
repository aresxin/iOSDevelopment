/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_RoundRectangle.h	IMG関連ヘッダファイル
 * Created: Feb, 22,2002 Kenichi Ishida
 * Edited:
 * Modified:
 */

#ifndef IMGROUNDRECTANGLE_H_INCLUDED
#define IMGROUNDRECTANGLE_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_GeometricShape.h"

/* 構造体宣言
 *
 *		y
 *		|
 *		|             ○-------○ <- 対角点2 
 *		|             |		 　|
 *		|             |		 　|
 *		|             |		　 |
 *		| 対角点1 ->  ○-------○
 *		|
 *	(0,0)------------------------------------x
 *
 */
typedef struct img_roundrectangle {
	IMG_GeometricShape super;
	
	IMG_Context *context;	/* Imager実行環境 */
	IMG_Point point1;		/* 矩形対角点1の座標 */
	IMG_Point point2;		/* 矩形対角点2の座標 */
	IMG_FLOAT rx;			/* 各丸の外接矩形の水平半径 */
	IMG_FLOAT ry;			/* 各丸の外接矩形の垂直半径 */

} IMG_RoundRectangle;

extern IMG_GeometricShape *IMG_RoundRectangle_Create(
	IMG_Context *context,	/* Imager実行環境 */
	IMG_Point *point1,		/* 矩形対角点1の座標 */
	IMG_Point *point2,		/* 矩形対角点2の座標 */
	IMG_FLOAT rx,			/* 各丸の外接矩形の水平半径 */
	IMG_FLOAT ry);			/* 各丸の外接矩形の垂直半径 */

#endif	/* IMGROUNDRECTANGLE_H_INCLUDED */
