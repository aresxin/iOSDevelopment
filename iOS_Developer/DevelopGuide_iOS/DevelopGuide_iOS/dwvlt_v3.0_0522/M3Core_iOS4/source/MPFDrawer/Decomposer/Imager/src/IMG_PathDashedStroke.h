/*!
  @file IMG_PathDashedStroke.h
  @brief PathDashedStroke classヘッダファイル

  HBPS Imager内部でPathの破線のStroke描画機能を提供するIMG_PathDashedStroke classのヘッダファイルである．<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-04
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Apr,13,2001	Toshio Yamazaki
 */
#include "IMG_PathStroke.h"

#ifndef IMG_PATHDASHEDSTROKE_H_INCLUDED
#define IMG_PATHDASHEDSTROKE_H_INCLUDED

IMG_PathStroke *IMG_PathDashedStroke_Create( IMG_Context*, IMG_DisplayList*,
					     IMG_GraphicsContext*, IMG_Path*, IMG_Pen* );

int IMG_PathDashedStroke_Draw_JoinPoint( IMG_PathStroke *,
					 IMG_Point *, IMG_Point *, IMG_Point * );
int IMG_PathDashedStroke_Draw_CapPoint( IMG_PathStroke *,
					IMG_Point *, IMG_Point * );
int IMG_PathDashedStroke_Draw_Line( IMG_PathStroke *,
				    IMG_Point *, IMG_Point * );

/* AR1505 */
int IMG_PathDashedStroke_Reset( IMG_PathStroke * );

#if 0
/* AR565 */
#define IMG_PATHDASHEDSTROKE_LINESTYLE_MAG_PARA		(48)	/*!< グラフィック属性の破線長の倍率 */
#endif

/* AR1509 */
#define IMG_PATHDASHEDSTROKE_LINESTYLE_MAG_PARA		(3)

#endif /* IMG_PATHDASHEDSTROKE_H_INCLUDED */
