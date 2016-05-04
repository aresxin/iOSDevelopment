/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 * IMG_RotatedRect.h	傾いた矩形描画ヘッダファイル
 *
 * Based:	IMG_Rectangle.h	Kenichi Ishida
 * Created:	Apr,20,2001	Toshio Yamazaki
 */

#ifndef IMG_ROTATEDRECT_H_INCLUDED
#define IMG_ROTATEDRECT_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_GeometricShape.h"
/*
 *	y
 *	|		    end
 *	|		/---+---/
 *	|	       /   /   /
 *	|	    ->/	  /   /<- width
 *	|	     /	 /   /
 *	|	    /---+---/
 *	|		start
 *	(0,0)------------------------------------x
 *
 *	常に start.y <= end.y, width >= 0.0 でなければならない
 *	NOTE: fig is not virtical. but width is virtical.
 */

/* 構造体宣言 */
typedef struct IMG_RotatedRect_L {
    IMG_GeometricShape	super;
    IMG_Context		*context;

    IMG_FLOAT		width;
    IMG_Point		start, end;

    /* Stroke用スキャンコンバージョン切り替えフラグ	*/
    int			isSCChange;
} IMG_RotatedRect;

IMG_GeometricShape *IMG_RotatedRect_Create( IMG_Context *,
					    IMG_FLOAT *,
					    IMG_Point *, IMG_Point * );

#define IMG_ROTATEDRECT_PERMITTED_ERROR	IMG_FLOATING_ERROR		/* 許容される誤差 */
#define IMG_ROTATEDRECT_FABS(a)		(((a)<0)?-(a):(a))

/* Error Code は #define の羅列 */
#define IMG_ROTATEDRECT_ERRORCODE_NOERROR	0
#define IMG_ROTATEDRECT_ERRORCODE_ERROR	       -1

#endif	/* IMG_ROTATEDRECT_H_INCLUDED */
