/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_ClipRegion.h - クリップ領域管理クラスの定義
 * Yozo Kashima 10-Aug-01
 *
 */

#ifndef INC_IMG_ClipRegion_h
#define INC_IMG_ClipRegion_h

#include "IMG_Builtin.h"
#include "IMG_Common.h"
#include "IMG_Context.h"

typedef enum img_clipstate {
	IMG_CLIP_STATE_NULL,					/* クリップ領域未指定 */
	IMG_CLIP_STATE_RECTANGLE,				/* 矩形クリップ指定 */
	IMG_CLIP_STATE_COMPLEX,					/* 複雑なクリップ指定 */
} IMG_ClipState;

typedef struct img_clipregion {
	IMG_Context		*context;
	IMG_ClipState	state;
	IMG_Point		point1, point2;				/* 矩形クリップデータ */
} IMG_ClipRegion;

extern IMG_ClipRegion *IMG_ClipRegion_Create(
	IMG_Context		*context);				/* コンテキスト */

extern int IMG_ClipRegion_Destroy(
	IMG_ClipRegion *self);						/* オブジェクト */

extern IMG_ClipRegion *IMG_ClipRegion_Clone(
	IMG_ClipRegion	*self);

extern int IMG_ClipRegion_RemenberRectangleClip(
	IMG_ClipRegion	*self,
	IMG_Point		*point1,
	IMG_Point		*point2);

extern int IMG_ClipRegion_RemenberComplexClip(
	IMG_ClipRegion	*self);

extern int IMG_ClipRegion_RemenberInitClip(
	IMG_ClipRegion	*self);

extern int IMG_ClipRegion_RestoreClip(
	IMG_ClipRegion	*self,
	void			*page);

#endif /* INC_IMG_ClipRegion_h */

/*
 * Log
 * 10.Aug.2001 Yozo Kashima Created
 * 20.Aug.2001 Yozo Kashima RestoreClipのpage引数の型をvoid*に変更(GCCでコンパイルできないため)。
 */

/* end of IMG_ClipRegion.h */
