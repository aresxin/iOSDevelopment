/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandPath.h - パス操作コマンドクラスの定義
 *
 */

#ifndef INC_IMG_CommandPath_h
#define INC_IMG_CommandPath_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Command.h"

/*-------------------------------------------------------------------------
  IMG_Command_InitPathクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_initpath {
    IMG_Command		super;
} IMG_Command_InitPath;

extern IMG_CommandPtr IMG_Command_InitPath_Create(
	IMG_Context		*context);

extern int IMG_Command_InitPath_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_MovePointクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_movepoint {
    IMG_Command		super;
	IMG_Point		point;
} IMG_Command_MovePoint;

extern IMG_CommandPtr IMG_Command_MovePoint_Create(
	IMG_Context		*context,			/* コンテキスト */
	IMG_Point		*point);			/* 移動先の座標点 */

extern int IMG_Command_MovePoint_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_AddRectanglePathクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_addrectanglepath {
    IMG_Command		super;
	IMG_Point		point2;
} IMG_Command_AddRectanglePath;

extern IMG_CommandPtr IMG_Command_AddRectanglePath_Create(
	IMG_Context		*context,			/* コンテキスト */
	IMG_Point		*point2);			/* 対角点2の座標 */

extern int IMG_Command_AddRectanglePath_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_AddLinePathクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_addlinepath {
    IMG_Command		super;
	IMG_UINT16		numberOfPoints;
	IMG_Point		*points;
} IMG_Command_AddLinePath;

extern IMG_CommandPtr IMG_Command_AddLinePath_Create(
	IMG_Context *context,
	IMG_UINT16 num,				/* 線分数+1 */
	IMG_Point *points);

extern int IMG_Command_AddLinePath_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_ClosePathクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_closepath {
    IMG_Command		super;
} IMG_Command_ClosePath;

extern IMG_CommandPtr IMG_Command_ClosePath_Create(
	IMG_Context		*context);			/* コンテキスト */

extern int IMG_Command_ClosePath_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_DrawPathクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_drawpath {
    IMG_Command		super;
} IMG_Command_DrawPath;

extern IMG_CommandPtr IMG_Command_DrawPath_Create(
	IMG_Context		*context);			/* コンテキスト */

extern int IMG_Command_DrawPath_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_ClipPathクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_clippath {
    IMG_Command	super;
	IMG_ClipRopMode clipRopMode;
} IMG_Command_ClipPath;

extern IMG_CommandPtr IMG_Command_ClipPath_Create(
	IMG_Context *context,
	IMG_ClipRopMode clipRopMode);

extern int IMG_Command_ClipPath_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandPath_h */

/*
 * Log
 * 04.Mar.2001 Yozo Kashima IMG_Command.hよりブランチ。
 * 19.Dec.2002 Yozo Kashima IMG_Command_ClipPathクラスにclipRopModeメンバを追加。
 */


/* end of IMG_CommandPath.h */
