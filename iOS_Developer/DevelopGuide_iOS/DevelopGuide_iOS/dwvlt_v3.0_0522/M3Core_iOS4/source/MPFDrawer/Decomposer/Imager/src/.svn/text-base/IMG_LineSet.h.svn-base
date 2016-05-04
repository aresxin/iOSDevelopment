/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_LineSet.h	IMG関連ヘッダファイル
 *			GDI Polyline系の描画
 * Created:	Apr, 4,2001	Kenichi Ishida
 * Edited:	Apr,13,2001	Kenichi Ishida
 * Modified:	Apr,20,2001	Toshio Yamazaki		IMG_LineSetの構造をLineからPointに変更
 *							fill(), stroke()の実装
 *							
 */

#ifndef IMGLINESET_H_INCLUDED
#define IMGLINESET_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"

/* Redefinedになってるからコメントアウト by tyama
typedef struct img_context IMG_Context;
typedef struct img_linedata IMG_LineData;*/

/* 構造体宣言 */
typedef struct IMG_LineSet {
    IMG_GeometricShape	super;
    IMG_Context		*context;		/* Imager実行環境	*/
    IMG_UINT16		numberOfpoints;		/* 頂点数		*/
    IMG_Point		*points;		/* 頂点列へのポインタ	*/
} IMG_LineSet;

extern IMG_GeometricShape *IMG_LineSet_Create(
    IMG_Context *,				/* Imager実行環境	*/
    IMG_UINT16,					/* 頂点数		*/
    IMG_Point *);				/* 頂点列へのポインタ	*/

#endif	/* IMGLINESET_H_INCLUDED */
