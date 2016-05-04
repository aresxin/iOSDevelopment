/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_Circle.h		円描画ヘッダファイル
 *
 * Created:	May,09,2001	Toshio Yamazaki
 */

#ifndef IMG_CIRCLE_H_INCLUDED
#define IMG_CIRCLE_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"
#include "IMG_Path.h"
#include "IMG_PathBuffer.h"

/* 構造体宣言 */
typedef struct IMG_Circle_L {
    IMG_GeometricShape	super;
    IMG_Context		*context;

    /* 円のデータ		*/
    IMG_Point		cp;
    IMG_FLOAT		r;
    IMG_FLOAT		sangle, eangle;	/* [deg]	*/
    IMG_ArcDrawMode	arcmode;

    /* 直線化された円のデータ	*/
    IMG_PathBuffer	*path_buf;
    /* 現在の円データを直線近似した	*/
    /* データが存在するフラグ		*/
    int			isLineApproximate;
} IMG_Circle;
/*
IMG_GeometricShape *IMG_Circle_Create( IMG_Context *,
				       IMG_FLOAT *,
				       IMG_Point * );
*/
IMG_GeometricShape *IMG_Circle_Create( IMG_Context *,
				       IMG_FLOAT ,
				       IMG_Point *,
				       IMG_FLOAT , IMG_FLOAT ,
				       IMG_ArcDrawMode );
/*
 * Circle オリジナル関数
 */
void IMG_Circle_SetCircle( IMG_Circle *, IMG_FLOAT *, IMG_Point *,
			   IMG_FLOAT *, IMG_FLOAT *,
			   IMG_ArcDrawMode * );
int IMG_Circle_PathTo_forCap( IMG_Circle *,
			      IMG_Path		*,
			      IMG_GraphicsContext *,
			      IMG_BOOL );

#define IMG_CIRCLE_PERMITTED_ERROR	IMG_FLOATING_ERROR		/* 許容される誤差	*/
#define IMG_CIRCLE_M_PI			3.1415926535898	/* pi			*/
#define IMG_CIRCLE_FABS(a)		(((a)<0)?-(a):(a))

/* Default のパラメータ		*/
#define IMG_CIRCLE_DEFAULT_STARTANGLE	(0.0)
#define IMG_CIRCLE_DEFAULT_ENDANGLE	(360.0)
#define IMG_CIRCLE_MIN_ANGLE		(-360.0)
#define IMG_CIRCLE_MAX_ANGLE		(360.0)
#define IMG_CIRCLE_MAXDIFF_ANGLE	(360.0)

/* Error Code は #define の羅列 */
#define IMG_CIRCLE_ERRORCODE_NOERROR	0
#define IMG_CIRCLE_ERRORCODE_ERROR	-1

#endif	/* IMG_CIRCLE_H_INCLUDED */
