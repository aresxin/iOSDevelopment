/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_Bezier.h		ベジェ曲線直線化ヘッダファイル
 *
 * Created:	May,10,2001	Toshio Yamazaki
 */

#ifndef IMG_BEZIER_H_INCLUDED
#define IMG_BEZIER_H_INCLUDED

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Builtin.h"
#include "IMG_BezierData.h"
#include "IMG_PathBuffer.h"

/*
 * 構造体宣言 は IMG_BezierData.hに移動
 * IMG_PathBuffer.hとの間で相互参照になったから.
 */

/*
 * Bezier オリジナル関数
 */
void IMG_Bezier_TransHVScale(IMG_BezierData *, IMG_BezierData *,
			     IMG_FLOAT, IMG_FLOAT );
int IMG_Bezier_TransLineSymm( IMG_BezierData *, IMG_BezierData *, int );
int IMG_Bezier_TransParallel( IMG_Point *, IMG_BezierData *, IMG_BezierData * );
int IMG_Bezier_TransNoPt( IMG_Matrix *, IMG_BezierData *, IMG_BezierData * );
int IMG_Bezier_Flatten( IMG_BezierData *, IMG_FLOAT, IMG_PathBuffer *, int );
int IMG_Bezier_QuarterFitCircle( IMG_DOUBLE ,
				 IMG_BezierData *, int );
int IMG_Bezier_FitArc( IMG_DOUBLE *, IMG_DOUBLE *, IMG_DOUBLE *,
		       IMG_BezierData *, int );
int IMG_Bezier_FitPartCircle( IMG_DOUBLE *, IMG_DOUBLE *, IMG_DOUBLE *,
			      IMG_BezierData *, int *, int );
int IMG_Bezier_FitCircle( IMG_DOUBLE ,
			  IMG_BezierData *, int );

int IMG_Bezier_FitPartEllipse( IMG_DOUBLE *, IMG_DOUBLE *,
			       IMG_DOUBLE *, IMG_DOUBLE *,
			       IMG_BezierData *, int *, int );

#define IMG_BEZIER_PERMITTED_ERROR	IMG_FLOATING_ERROR		/* 許容される誤差	*/
#define IMG_BEZIER_FABS(a)		(((a)<0)?-(a):(a))

/*
 * いくつかの定数
 */
#define IMG_BEZIER_M_PI		3.1415926535898		/* pi			*/
#define IMG_BEZIER_COS22_5	0.9238795325113		/* cos( 22.5[deg] );	*/
#define IMG_BEZIER_SIN22_5	0.3826834323651		/* sin( 22.5[deg] );	*/
#define IMG_BEZIER_COS45	0.7071067811865		/* cos( 45.0[deg] );	*/
#define IMG_BEZIER_SIN45	0.7071067811865		/* sin( 45.0[deg] );	*/

#define IMG_BEZIER_H_PARA22_5	((4.0/3.0)*(1.0-IMG_BEZIER_COS22_5)/IMG_BEZIER_SIN22_5)
#define IMG_BEZIER_H_PARA45	((4.0/3.0)*(1.0-IMG_BEZIER_COS45)/IMG_BEZIER_SIN45)

/* Error Code は #define の羅列 */
#define IMG_BEZIER_ERRORCODE_NOERROR	0
#define IMG_BEZIER_ERRORCODE_ERROR	-1

/* DEBUG用関数 */
#ifdef IMG_DEBUG_BAZIER
#include <stdio.h>

void IMG_Bezier_Print( FILE *, IMG_BezierData *, int num );

#endif /* IMG_DEBUG_BAZIER */

#endif	/* IMG_BEZIER_H_INCLUDED */
