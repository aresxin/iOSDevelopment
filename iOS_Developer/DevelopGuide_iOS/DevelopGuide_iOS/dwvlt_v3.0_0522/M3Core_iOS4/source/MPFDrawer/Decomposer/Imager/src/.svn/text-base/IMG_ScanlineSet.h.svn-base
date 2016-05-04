/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_ScanlineSet.h	IMG関連ヘッダファイル
 * Created: Apr,4,2001	Yozo Kashima
 * Edited : Apr,4,2001	Kenichi Ishida
 */

#ifndef IMGSCANLINESET_H_INCLUDED
#define IMGSCANLINESET_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"

/*typedef struct img_context IMG_Context;*/
/*typedef struct img_point IMG_Point;*/

/* 構造体宣言 */
typedef struct img_scanlineset {
	IMG_GeometricShape super;

	IMG_Context *context;			/* Imager実行環境 */
	IMG_UINT16 numberOfScanlines;	/* スキャンライン数 */
	IMG_Point *startPoints;			/* スキャンライン開始点座標の配列 */
	IMG_UINT16 *lengths;			/* スキャンラインの長さの配列 */

} IMG_ScanlineSet;

extern IMG_GeometricShape *IMG_ScanlineSet_Create(
	IMG_Context *context,	/* Imager実行環境 */
	IMG_UINT16 num,			/* スキャンライン数 */
	IMG_Point *startPoints,	/* num個のスキャンライン始点座標へのポインタ */
	IMG_UINT16 *lengths);	/* num個の各スキャンラインのx方向の長さへのポインタ */

#endif	/* IMGSCANLINESET_H_INCLUDED */
