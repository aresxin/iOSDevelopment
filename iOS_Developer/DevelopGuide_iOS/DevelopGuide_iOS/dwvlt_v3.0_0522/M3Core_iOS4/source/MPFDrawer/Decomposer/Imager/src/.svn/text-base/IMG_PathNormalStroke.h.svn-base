/*!
  @file IMG_PathNormalStroke.h
  @brief PathNormalStroke classヘッダファイル

  HBPS Imager内部でPathの実線のStroke描画機能を提供するIMG_PathNormalStroke classのヘッダファイルである．<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-04
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Apr,13,2001	Toshio Yamazaki
 */
#include "IMG_PathStroke.h"

#ifndef IMG_PATHNORMALSTROKE_H_INCLUDED
#define IMG_PATHNORMALSTROKE_H_INCLUDED

IMG_PathStroke *IMG_PathNormalStroke_Create( IMG_Context*, IMG_DisplayList*,
					     IMG_GraphicsContext*, IMG_Path*, IMG_Pen* );

int IMG_PathNormalStroke_Draw_JoinPoint( IMG_PathStroke *,
					 IMG_Point *, IMG_Point *, IMG_Point * );
int IMG_PathNormalStroke_Draw_CapPoint( IMG_PathStroke *,
					IMG_Point *, IMG_Point * );
int IMG_PathNormalStroke_Draw_Line( IMG_PathStroke *,
				    IMG_Point *, IMG_Point * );

/* AR1505 */
int IMG_PathNormalStroke_Reset( IMG_PathStroke * );

#endif /* IMG_PATHNORMALSTROKE_H_INCLUDED */
