/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_QuadRangle.h	四角形 (Quadrangle) 描画ヘッダファイル
 *
 * Created:	May,01,2001	Toshio Yamazaki
 */

#ifndef IMG_QUADRANGLE_H_INCLUDED
#define IMG_QUADRANGLE_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"
/*
 *	y
 *	|
 *	|		+-------+
 *	|	       /       /
 *	|	      /	      /
 *	|	     /	     /
 *	|	    +-------+
 *	|
 *	(0,0)------------------------------------x
 *
 *	4点指定の四角形を描画する．
 *	指定される点順は必ず隣り合った点でなければならない
 *	多分凹角を持つ四角形は当面サポートされない
 *	三角形はサポートしているらしい
 */

/* 構造体宣言 */
typedef struct IMG_QuadRangle_L {
    IMG_GeometricShape	super;
    IMG_Context		*context;

    int			num;
    IMG_Point		p[4];

    /* Stroke用スキャンコンバージョン切り替えフラグ	*/
    int			isSCChange;
} IMG_QuadRangle;

IMG_GeometricShape *IMG_QuadRangle_Create( IMG_Context *,
					   int *,
					   IMG_Point * );

#define IMG_QUADRANGLE_PERMITTED_ERROR	IMG_FLOATING_ERROR		/* 許容される誤差 */
#define IMG_QUADRANGLE_FABS(a)		(((a)<0)?-(a):(a))

/* Error Code は #define の羅列 */
#define IMG_QUADRANGLE_ERRORCODE_NOERROR	0
#define IMG_QUADRANGLE_ERRORCODE_ERROR	       -1

#endif	/* IMG_QUADRANGLE_H_INCLUDED */
