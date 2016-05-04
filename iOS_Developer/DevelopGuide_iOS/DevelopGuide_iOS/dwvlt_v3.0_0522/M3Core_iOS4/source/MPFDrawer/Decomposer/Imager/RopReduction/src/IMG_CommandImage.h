/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandImage.h - イメージ描画コマンドクラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_CommandImage_h
#define INC_IMG_CommandImage_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Command.h"
#include "IMG_Image.h"
#include "IMG_ImageMask.h"

/*-------------------------------------------------------------------------
  IMG_Command_DrawImageクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_drawimage {
    IMG_Command		super;
	IMG_ImageParam	imageParam;				/* イメージパラメータ */
	char			*maskData;				/* マスクのデータ */
	char			*paletteData;			/* パレットデータ */
	char			*imageData;				/* イメージデータ */
} IMG_Command_DrawImage;

extern IMG_CommandPtr IMG_Command_DrawImage_Create(
	IMG_Context		*context,
	IMG_ImageParam	*imageParam,		/* イメージパラメータ */
	char			*maskData,			/* マスクのデータ */
	char			*paletteData,		/* パレットデータ */
	char			*imageData,			/* イメージデータ */
	IMG_BOOL		canOwnData);		/* データ(マスク，パレット，イメージ)を所有できるか */

extern int IMG_Command_DrawImage_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_DrawImageMaskクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_drawimagemask {
    IMG_Command			super;
	IMG_ImageMaskParam	imageMaskParam;				/* イメージパラメータ */
	char				*maskData;				/* マスクのデータ */
} IMG_Command_DrawImageMask;

extern IMG_CommandPtr IMG_Command_DrawImageMask_Create(
	IMG_Context			*context,
	IMG_ImageMaskParam	*imageMaskParam,	/* イメージパラメータ */
	char				*maskData,			/* マスクのデータ */
	IMG_BOOL			canOwnData);

extern int IMG_Command_DrawImageMask_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandImage_h */

/*
 * Log
 * 04.Mar.2001 Yozo Kashima IMG_Command.hよりブランチ。
 * 06.May.2003 Yozo Kashima AR#1232対応(FH1001T0_W98,IMG_Command_DrawImage_CreateでcanOwnData引数にIMG_TRUEを追加)
 */

/* end of IMG_CommandImage.h */
