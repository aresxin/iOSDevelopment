/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_Ellipse.h	楕円描画ヘッダファイル
 *
 * Created:	May,04,2002	Toshio Yamazaki
 */

#ifndef IMG_ELLIPSE_H_INCLUDED
#define IMG_ELLIPSE_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"
#include "IMG_PathBuffer.h"

/* 構造体宣言 */
typedef struct IMG_Ellipse_L {
    IMG_GeometricShape	super;
    IMG_Context		*context;

    /* 楕円のデータ		*/
    IMG_Point		cp;
    IMG_FLOAT		rx, ry;
    IMG_FLOAT		sangle, eangle;	/* [deg]	*/
    IMG_ArcDrawMode	arcmode;

} IMG_Ellipse;

IMG_GeometricShape *IMG_Ellipse_Create( IMG_Context *,
					IMG_FLOAT , IMG_FLOAT,
					IMG_Point *,
					IMG_FLOAT , IMG_FLOAT ,
					IMG_ArcDrawMode );
/*
 * Circle オリジナル関数
 */
void IMG_Ellipse_SetEllipse( IMG_Ellipse *, IMG_FLOAT *, IMG_FLOAT *, IMG_Point *,
			     IMG_FLOAT *, IMG_FLOAT *,
			     IMG_ArcDrawMode * );

#define IMG_ELLIPSE_PERMITTED_ERROR	IMG_FLOATING_ERROR		/* 許容される誤差	*/
#define IMG_ELLIPSE_M_PI		3.1415926535898	/* pi			*/
#define IMG_ELLIPSE_FABS(a)		(((a)<0)?-(a):(a))

/* Default のパラメータ		*/
#define IMG_ELLIPSE_DEFAULT_STARTANGLE	(0.0)
#define IMG_ELLIPSE_DEFAULT_ENDANGLE	(360.0)
#define IMG_ELLIPSE_MIN_ANGLE		(-360.0)
#define IMG_ELLIPSE_MAX_ANGLE		(360.0)
#define IMG_ELLIPSE_MAXDIFF_ANGLE	(360.0)

/* Error Code は #define の羅列 */
#define IMG_ELLIPSE_ERRORCODE_NOERROR	0
#define IMG_ELLIPSE_ERRORCODE_ERROR	-1

#endif	/* IMG_ELLIPSE_H_INCLUDED */
