/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_BezierSet.h - ベジェ曲線の集まりクラスの定義
 * Yozo Kashima(DS&S-STD-T31) 21.Feb.2002
 */

#ifndef INC_IMG_BezierSet_h
#define INC_IMG_BezierSet_h

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"

/*
 * IMG_BezierSetクラスの定義
 */
typedef struct img_bezierset {
    IMG_GeometricShape	super;			/* Super Class */
    IMG_Context			*context;		/* Imager実行環境	*/
    IMG_UINT16			nPoints;		/* 頂点数		*/
	IMG_Point			startp;			/* 描画開始点 */
    IMG_Point			*points;		/* 頂点列へのポインタ	*/
	IMG_BOOL			hasStartPoint;	/* startpが指定されているか? */
} IMG_BezierSet;

extern IMG_GeometricShape *IMG_BezierSet_Create(
	IMG_Context	*context,		/* Imager実行環境 */
	IMG_UINT16	nPoints,		/* 座標数 */
	IMG_Point	*startp,		/* 描画開始点 */
	IMG_Point	*points);		/* 座標データへのポインタ */

#endif	/* INC_IMG_BezierSet_h */
