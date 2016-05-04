/*!
  @file IMG_PenOrthogonal.h
  @brief IMG_PenOrthogonal classヘッダファイル<br>

  IMG_Pen classを継承した，直行座標系用のIMG_PenOrthogonal classヘッダファイルである<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-09
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Apr,17,2001	Toshio Yamazaki
 */
#include "IMG_Pen.h"

#ifndef IMG_PENORTHOGONAL_H_INCLUDED
#define IMG_PENORTHOGONAL_H_INCLUDED

IMG_Pen *IMG_PenOrthogonal_Create( IMG_Context *, IMG_DisplayList *,
				   IMG_GraphicsContext * );

/* vertual function の定義 */
int IMG_PenOrthogonal_Draw_JoinPoint( IMG_Pen *, IMG_Point *, IMG_Point *, IMG_Point * );
int IMG_PenOrthogonal_Draw_CapPoint( IMG_Pen *, IMG_Point *, IMG_Point * );
int IMG_PenOrthogonal_Draw_Line( IMG_Pen *, IMG_Point *, IMG_Point * );
int IMG_PenOrthogonal_Calc_VectorLength( IMG_Pen *, IMG_Point *, IMG_Point *, IMG_FLOAT * );

#endif /* IMG_PENORTHOGONAL_H_INCLUDED */
