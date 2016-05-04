/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_BezierData.h	ベジェデータ定義ヘッダファイル
 *
 * Created:	Aug,7,2001	Toshio Yamazaki
 */

#ifndef IMG_BEZIERDATA_H_INCLUDED
#define IMG_BEZIERDATA_H_INCLUDED

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_GeometricShape.h"

/* 構造体宣言 */
typedef struct IMG_BezierData_L {
    IMG_Point		start, end, cnt1, cnt2;
} IMG_BezierData;

typedef struct IMG_Bezier_L {
    IMG_GeometricShape	super;
    IMG_Context		*context;

    /* Bezier用のデータ	*/
    IMG_FLOAT		flatteness;
    IMG_BezierData	data;
} IMG_Bezier;

/* IMG_Bezier_Flattenは，引数の値で.		*/
/* 構築されるパスの先端と終端を切り替える.	*/
/* 1bit目が先端の指定				*/
#define IMG_BEZIER_FLATTEN_MODE_START		0x01
#define IMG_BEZIER_FLATTEN_MODE_MOVETO		0x00
#define IMG_BEZIER_FLATTEN_MODE_LINETO		0x01
/* 2〜3bit目が終端の指定			*/
#define IMG_BEZIER_FLATTEN_MODE_END		0x06
#define IMG_BEZIER_FLATTEN_MODE_OPEN		0x00
#define IMG_BEZIER_FLATTEN_MODE_CLOSE		0x02
#define IMG_BEZIER_FLATTEN_MODE_CONTINUE	0x04

#endif	/* IMG_BEZIERDATA_H_INCLUDED */
