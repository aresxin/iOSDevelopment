/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandAttribute.h - 属性設定コマンドクラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_CommandAttribute_h
#define INC_IMG_CommandAttribute_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Command.h"
#include "IMG_RasterPatternBrush.h"
#include "IMG_MaskPatternBrush.h"
#include "IMG_HatchPatternBrush.h"

/*
 * マクロ定義
 *
 * IMG_DECLARE_SET_VALUE_COMMANDは簡単なコマンドクラスを宣言するためのマクロ。
 */
#define IMG_COMMAND_CAT(x,y)	x ## y
#define IMG_COMMAND_XCAT(x,y)	IMG_COMMAND_CAT(x,y)
#define IMG_COMMAND_CAT3(x,y,z)	IMG_COMMAND_XCAT(IMG_COMMAND_XCAT(x,y),z)
#define IMG_COMMAND_GLOBAL_FUNC(className,funcName)	IMG_COMMAND_CAT3(IMG_Command_,className,funcName)

#define IMG_DECLARE_SET_VALUE_COMMAND(className, structTag, valueType, member)	\
typedef struct img_command_##structTag {										\
		IMG_Command		super;													\
		valueType		member;													\
} IMG_Command_##className;														\
																				\
extern IMG_CommandPtr IMG_COMMAND_GLOBAL_FUNC(className,_Create)(				\
	IMG_Context *context,														\
	valueType	member);														\
extern int IMG_COMMAND_GLOBAL_FUNC(className,_Reconstruct)(						\
	IMG_CommandPtr self);

/*-------------------------------------------------------------------------
  属性設定命令クラスの定義
-------------------------------------------------------------------------*/

IMG_DECLARE_SET_VALUE_COMMAND(SetFillRule, setfillrule, IMG_FillRule, fillRule)
IMG_DECLARE_SET_VALUE_COMMAND(SetDrawMode, setdrawmode, IMG_DrawMode, drawMode)
IMG_DECLARE_SET_VALUE_COMMAND(SetCapStyle, setcapstyle, IMG_CapStyle, capStyle)
IMG_DECLARE_SET_VALUE_COMMAND(SetJoinStyle, setjoinstyle, IMG_JoinStyle, joinStyle)
IMG_DECLARE_SET_VALUE_COMMAND(SetMiterLimit, setmiterlimit, IMG_FLOAT, miterLimit)
IMG_DECLARE_SET_VALUE_COMMAND(SetStrokeWidth, setstrokewidth, IMG_FLOAT, strokeWidth)

/*-------------------------------------------------------------------------
  IMG_Command_SetLineStyleクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setlinestyle {
    IMG_Command		super;
	IMG_LineStyle	lineStyle;
	IMG_FLOAT		offset;
	IMG_UINT16		count;
	IMG_FLOAT		*data;
} IMG_Command_SetLineStyle;

extern IMG_CommandPtr IMG_Command_SetLineStyle_Create(
	IMG_Context		*context,
	IMG_LineStyle	lineStyle,
	IMG_FLOAT		offset,
	IMG_UINT16		count,
	IMG_FLOAT		*data);

extern int IMG_Command_SetLineStyle_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_SetMatrixクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setmatrix {
    IMG_Command		super;
    IMG_Matrix		matrix;
} IMG_Command_SetMatrix;

extern IMG_CommandPtr IMG_Command_SetMatrix_Create(
	IMG_Context		*context,
	IMG_Matrix		*matrix);

extern int IMG_Command_SetMatrix_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_SetSolidColorクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setbrush {
    IMG_Command		super;
    IMG_DrawMode	drawMode;
} IMG_Command_SetBrush;

/*-------------------------------------------------------------------------
  IMG_Command_SetSolidColorクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setsolidcolor {
    IMG_Command_SetBrush	super;
    IMG_ColorSpace	colorSpace;
    IMG_ColorData	colorData;
} IMG_Command_SetSolidColor;

extern IMG_CommandPtr IMG_Command_SetSolidColor_Create(
	IMG_Context *context,
	IMG_DrawMode imgDrawMode,
	IMG_ColorSpace imgColorSpace,
	IMG_ColorData *imgColorData);

extern int IMG_Command_SetSolidColor_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_SetRasterPatternクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setrasterpattern {
    IMG_Command_SetBrush	super;
    IMG_RasterPatternBrushParam rasterParam;
    char *data;
} IMG_Command_SetRasterPattern;

extern IMG_CommandPtr IMG_Command_SetRasterPattern_Create(
	IMG_Context *context,
	IMG_DrawMode imgDrawMode,
	IMG_RasterPatternBrushParam *rasterParam,
	char *pattern);			/* パターンデータ */

extern int IMG_Command_SetRasterPattern_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_SetMaskPatternクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setmaskpattern {
    IMG_Command_SetBrush	super;
    IMG_MaskPatternBrushParam maskParam;
    char *data;
} IMG_Command_SetMaskPattern;

extern IMG_CommandPtr IMG_Command_SetMaskPattern_Create(
	IMG_Context		*context,
	IMG_DrawMode	drawMode,
	IMG_MaskPatternBrushParam *maskParam,
	char			*pattern,
	IMG_BOOL		canOwnPattern);

extern int IMG_Command_SetMaskPattern_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_SetHatchPatternクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_sethatchpattern {
    IMG_Command_SetBrush	super;
    IMG_HatchPatternBrushParam hatchParam;
} IMG_Command_SetHatchPattern;

extern IMG_CommandPtr IMG_Command_SetHatchPattern_Create(
	IMG_Context		*context,
	IMG_DrawMode	drawMode,
	IMG_HatchPatternBrushParam *hatchParam);

extern int IMG_Command_SetHatchPattern_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_InitClipクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_initclip {
    IMG_Command	super;
} IMG_Command_InitClip;

extern IMG_CommandPtr IMG_Command_InitClip_Create(
	IMG_Context *context);

extern int IMG_Command_InitClip_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_SetRectangleClipクラスの定義
-------------------------------------------------------------------------*/
typedef struct img_command_setrectangleclip {
    IMG_Command	super;
	IMG_ClipRopMode	clipRopMode;
	IMG_Point		point1;
	IMG_Point		point2;
} IMG_Command_SetRectangleClip;

extern IMG_CommandPtr IMG_Command_SetRectangleClip_Create(
	IMG_Context	*context,
	IMG_ClipRopMode clipRopMode,
	IMG_Point	*point1,
	IMG_Point	*point2);

extern int IMG_Command_SetRectangleClip_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandAttribute_h */

/*
 * Log
 * 04.Mar.2001 Yozo Kashima IMG_Command.hよりブランチ。
 * 19.Dec.2002 Yozo Kashima IMG_Command_SetRectangleClipクラスにropClipModeメンバを追加。
 * 06.Mar.2003 Yozo Kashima AR#1157対応。IMG_Command_SetBrushを作成し，
 *							SC,PC,PM,PHのBrushコマンドクラスはそのサブクラスとする。
 */

/* end of IMG_CommandAttribute.h */
