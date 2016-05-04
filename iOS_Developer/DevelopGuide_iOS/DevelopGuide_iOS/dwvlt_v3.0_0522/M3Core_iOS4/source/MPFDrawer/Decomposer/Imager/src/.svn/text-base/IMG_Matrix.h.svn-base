/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * IMG_Matrix.h	IMG関連ヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 石田健一
 *
 * Created:	Apr, 3,2001	Kenichi Ishida
 * Modified:	Apr,19,2001	Toshio Yamazaki		IMG_MatrixTransform()の引数変更
 *							IMG_MatrixPointTransform()の新規作成
 * Modified:	Apr,20,2001	Toshio Yamazaki		IMG_MatrixCheckAxis()の新規作成
 */

#ifndef IMGMATRIX_H_INCLUDED
#define IMGMATRIX_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_Common.h"

typedef enum img_matrix_angle {
	IMG_MATRIX_ANGLE_0			= 0,	/* 0度 */
	IMG_MATRIX_ANGLE_90			= 9,	/* 90度 */
	IMG_MATRIX_ANGLE_180		= 18,	/* 180度*/
	IMG_MATRIX_ANGLE_270		= 27,	/* 270度 */
	IMG_MATRIX_ANGLE_0_MIRROR	= 100,	/* 0度 鏡像 */
	IMG_MATRIX_ANGLE_90_MIRROR	= 109,	/* 0度 鏡像 */
	IMG_MATRIX_ANGLE_180_MIRROR	= 118,	/* 0度 鏡像 */
	IMG_MATRIX_ANGLE_270_MIRROR	= 127,	/* 0度 鏡像 */
	IMG_MATRIX_ANGLE_ERROR	= -1,	/* エラー */
} IMG_Matrix_Angle;


/*
 * matrix =	|   a   b   0 |
 *		|   c   d   0 |
 *		|  tx  ty   1 |
 */

typedef struct img_matrix{
    IMG_REAL32 a;
    IMG_REAL32 b;
    IMG_REAL32 c;
    IMG_REAL32 d;
    IMG_REAL32 tx;
    IMG_REAL32 ty;
} IMG_Matrix;

/*
 * 座標変換関数
 */
int IMG_MatrixTransform(
    IMG_Matrix*,	/* CTMデータ	*/
    IMG_UINT32,		/* 入力点数	*/
    IMG_REAL32	*,	/* 入力データ	*/
    IMG_REAL32	*,
    IMG_REAL32	*,
    IMG_REAL32	*
);

int IMG_MatrixPointTransform(
    IMG_Matrix	*ctm,	/* CTMデータ */
    IMG_UINT32	points,	/* 入力点数  */
    IMG_Point	*in,	/* 入力データ */
    IMG_Point	*out	/* 出力データ */
);

int IMG_MatrixPointTransform_NoPt(
    IMG_Matrix	*ctm,	/* CTMデータ */
    IMG_UINT32	points,	/* 入力点数  */
    IMG_Point	*in,	/* 入力データ */
    IMG_Point	*out	/* 出力データ */
);

int IMG_MatrixEdgeTransform(
    IMG_Matrix		*ctm,	/* CTMデータ */
    IMG_EdgeData	*in,	/* 入力データ */
    IMG_LineData	*out	/* 出力データ */
);

int IMG_MatrixLineTransform(
    IMG_Matrix		*ctm,	/* CTMデータ */
    IMG_LineData	*in,	/* 入力データ */
    IMG_LineData	*out	/* 出力データ */
);

int
IMG_MatrixRectangleTransform(IMG_Matrix *ctm,
			     IMG_Point *inLeftTop,IMG_Point *inRightBottom,
			     IMG_Point *outLeftTop,IMG_Point *outRightBottom);

int
IMG_MatrixFontTransform(IMG_Matrix *ctm,
			IMG_Point *inPoint,
			IMG_UINT16 width,IMG_UINT16 height,
			IMG_Point *outPoint);

int
IMG_MatrixWidthTransform(IMG_Matrix *,
			 IMG_Point *,
			 IMG_FLOAT *,
			 IMG_FLOAT * );
/*
 * Matrix演算関数
 */
int
IMG_MatrixMultiply(IMG_Matrix *inCtm1,
		   IMG_Matrix *inCtm2,
		   IMG_Matrix *outCtm);

/*
 * 座標系をチェックする関数
 */
/* 直行or非直行座標系か否か判断する */
int IMG_MatrixCheckAxis( IMG_Matrix * );
/* 座標系の回転角度を90度単位で算出する */
IMG_Matrix_Angle IMG_MatrixGetAngle(IMG_Matrix *ctm);

/*
 * 逆行列演算用3x3Matrixとその関数
 */
typedef struct img_matrix33{
    IMG_REAL64	a, b, c;
    IMG_REAL64	d, e, f;
    IMG_REAL64	g, h, i;
} IMG_Matrix33;

int		IMG_MatrixInvert( IMG_Matrix *, IMG_Matrix33 * );
IMG_REAL64	IMG_MatrixDenomi( IMG_Matrix * );
IMG_REAL64	IMG_Matrix33Denomi( IMG_Matrix33 * );
int		IMG_Matrix33PointTransform(
    IMG_Matrix33	*ctm,	/* CTMデータ */
    IMG_UINT32		points,	/* 入力点数  */
    IMG_Point		*in,	/* 入力データ */
    IMG_Point		*out	/* 出力データ */
);

int		IMG_Matrix33PointTransform_NoPt(
    IMG_Matrix33	*ctm,	/* CTMデータ */
    IMG_UINT32		points,	/* 入力点数  */
    IMG_Point		*in,	/* 入力データ */
    IMG_Point		*out	/* 出力データ */
);

#endif	/* IMGMATRIX_H_INCLUDED */
