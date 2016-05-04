/*!
  @file IMG_PenNonOrthogonal.h
  @brief IMG_PenNonOrthogonal classヘッダファイル<br>

  IMG_Pen classを継承した，非直行座標系用のIMG_PenNonOrthogonal classヘッダファイルである<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-09
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Jun,19,2001	Toshio Yamazaki
 */
#include "IMG_Pen.h"

#ifndef IMG_PENNONORTHOGONAL_H_INCLUDED
#define IMG_PENNONORTHOGONAL_H_INCLUDED

IMG_Pen *IMG_PenNonOrthogonal_Create( IMG_Context *, IMG_DisplayList *,
				   IMG_GraphicsContext * );

/* vertual function の定義 */
int IMG_PenNonOrthogonal_Draw_JoinPoint( IMG_Pen *, IMG_Point *, IMG_Point *, IMG_Point * );
int IMG_PenNonOrthogonal_Draw_CapPoint( IMG_Pen *, IMG_Point *, IMG_Point * );
int IMG_PenNonOrthogonal_Draw_Line( IMG_Pen *, IMG_Point *, IMG_Point * );
int IMG_PenNonOrthogonal_Calc_VectorLength( IMG_Pen *, IMG_Point *, IMG_Point *, IMG_FLOAT * );

/* 継承されたクラスで使われるprotectedなメソッド*/
/* CだからGlobalになってるけどな		*/
int IMG_PenNO_Calc_OrthogonalVectorLength(IMG_Pen *, IMG_Point *, IMG_Point *, IMG_FLOAT * );
IMG_Point IMG_PenNO_CalcRelativeSidePoint(IMG_Point *, IMG_Point *, IMG_Point *, IMG_Point *);
int IMG_PenNO_CalcMiterJoinPoint(IMG_Pen *pen, IMG_Point *, IMG_Point *, IMG_Point *,
				 IMG_FLOAT, IMG_Point *, IMG_Point *, IMG_Point *);
int IMG_PenNO_CalcRoundJoinAngle(IMG_Pen *, IMG_Point *, IMG_Point *, IMG_Point *,
				 IMG_FLOAT, IMG_Point *, IMG_Point *, IMG_FLOAT *, IMG_FLOAT * );
int IMG_PenNO_CalcBevelJoinPoint(IMG_Pen *, IMG_Point *, IMG_Point *, IMG_Point *,
				 IMG_FLOAT, IMG_Point *, IMG_Point * );
int IMG_PenNO_CalcSquareCapPoint(IMG_Pen *, IMG_Point *, IMG_Point *,
				 IMG_FLOAT, IMG_Point *, IMG_Point *, IMG_Point * );

#endif /* IMG_PENNONORTHOGONAL_H_INCLUDED */
