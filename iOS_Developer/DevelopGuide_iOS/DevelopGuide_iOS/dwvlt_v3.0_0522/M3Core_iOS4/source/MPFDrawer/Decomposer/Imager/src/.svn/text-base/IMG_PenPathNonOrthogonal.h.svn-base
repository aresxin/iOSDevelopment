/*!
  @file IMG_PenPathNonOrthogonal.h
  @brief IMG_PenPathNonOrthogonal classヘッダファイル<br>

  IMG_Pen classを継承した，非直行座標系用のIMG_PenPathNonOrthogonal classヘッダファイルである<br>
  このクラスはIMG_DisplayListに描画するのではなく，IMG_Pen内部のIMG_Pathオブジェクトに対して，
  パスのストローク結果の外殻のパスを生成する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-09
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Jun,17,2003	Toshio Yamazaki
 */
#include "IMG_Pen.h"

#ifndef IMG_PENPATHNONORTHOGONAL_H_INCLUDED
#define IMG_PENPATHNONORTHOGONAL_H_INCLUDED

IMG_Pen *IMG_PenPathNonOrthogonal_Create( IMG_Context *, IMG_DisplayList *,
				   IMG_GraphicsContext * );

/* vertual function の定義 */
int IMG_PenPathNonOrthogonal_Draw_JoinPoint( IMG_Pen *, IMG_Point *, IMG_Point *, IMG_Point * );
int IMG_PenPathNonOrthogonal_Draw_CapPoint( IMG_Pen *, IMG_Point *, IMG_Point * );
int IMG_PenPathNonOrthogonal_Draw_Line( IMG_Pen *, IMG_Point *, IMG_Point * );

#endif /* IMG_PENPATHNONORTHOGONAL_H_INCLUDED */
