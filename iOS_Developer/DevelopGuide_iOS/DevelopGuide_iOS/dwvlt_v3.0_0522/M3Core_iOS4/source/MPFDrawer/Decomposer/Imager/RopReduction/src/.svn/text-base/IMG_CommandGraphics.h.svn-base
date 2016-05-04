/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandGraphics.h - グラフィックス描画コマンドクラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_CommandGraphics_h
#define INC_IMG_CommandGraphics_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Command.h"
#include "IMG_ClassPointer.h"

/*-------------------------------------------------------------------------
  IMG_Command_DrawLineクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_drawline {
    IMG_Command		super;
    IMG_UINT16		numberOfPoints;
    IMG_Point		*points;
} IMG_Command_DrawLine;

extern IMG_CommandPtr IMG_Command_DrawLine_Create(
	IMG_Context *context,
	IMG_UINT16 num,				/* 線分数+1 */
	IMG_Point *points);

extern int IMG_Command_DrawLine_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */


/*-------------------------------------------------------------------------
  IMG_Command_DrawRectangleクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_drawrectangle {
    IMG_Command	super;
    IMG_Point		point1;
    IMG_Point		point2;
	IMG_BOOL		drawRightBottom;
} IMG_Command_DrawRectangle;

extern IMG_CommandPtr IMG_Command_DrawRectangle_Create(
	IMG_Context *context,
	IMG_Point *point1,
	IMG_Point *point2,
	IMG_BOOL		drawRightBottomLine);

extern int IMG_Command_DrawRectangle_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_DrawRectangleSetクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_drawrectangleset {
    IMG_Command		super;
	IMG_UINT16		nrect;				/* 矩形の総数 */
	IMG_UINT16		blocks;				/* ブロック数 */
	IMG_REAL32		startY;				/* 最初の矩形の左上点のY座標 */
	IMG_UINT16		*lines;				/* ライン数 */
	IMG_UINT16		*columns;			/* 列数 */
	IMG_REAL32		*height;			/* 矩形群の高さ */
	IMG_REAL32		*x;					/* num個の描画開始点のX座標 */
	IMG_REAL32		*width;				/* num個の矩形の幅 */

	IMG_BOOL		isCacheValid;
	IMG_Point		lt;
	IMG_Point		rb;
} IMG_Command_DrawRectangleSet;

extern IMG_CommandPtr IMG_Command_DrawRectangleSet_Create(
	IMG_Context		*context,
	IMG_UINT16		nrect,				/* 矩形の総数 */
	IMG_UINT16		blocks,				/* ブロック数 */
	IMG_REAL32		startY,				/* 最初の矩形の左上点のY座標 */
	IMG_UINT16		*lines,				/* ライン数 */
	IMG_UINT16		*colums,			/* 列数 */
	IMG_REAL32		*height,			/* 矩形群の高さ */
	IMG_REAL32		*x,					/* num個の描画開始点のX座標 */
	IMG_REAL32		*width,				/* num個の矩形の幅 */
	IMG_BOOL		canOwnData);

extern int IMG_Command_DrawRectangleSet_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_DrawScanlineクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_drawscanline {
    IMG_Command		super;
	IMG_UINT16		numberOfScanlines;		/* スキャンライン数 */
    IMG_Point		*startPoints;			/* スキャンラインの開始座標点の配列 */
    IMG_UINT16		*lengths;				/* スキャンラインの長さの配列 */
} IMG_Command_DrawScanline;

extern IMG_CommandPtr IMG_Command_DrawScanline_Create(
	IMG_Context		*context,
	IMG_UINT16		numberOfScanlines,		/* スキャンライン数 */
    IMG_Point		*startPoints,			/* スキャンラインの開始座標点の配列 */
    IMG_UINT16		*lengths);				/* スキャンラインの長さの配列 */

extern int IMG_Command_DrawScanline_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_Circleクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_circle {
    IMG_Command		super;
	IMG_Point		center;			/* 中心点 */
	IMG_FLOAT		r;				/* 半径 */
	IMG_FLOAT		sangle;			/* 始点角度 */
	IMG_FLOAT		eangle;			/* 終点角度 */
	IMG_ArcDrawMode	mode;			/* 弧の描き方 */
	IMG_BOOL		isDraw;			/* 描画命令か(でなければパス構築) */
} IMG_Command_Circle;

extern IMG_CommandPtr IMG_Command_Circle_Create(
	IMG_Context		*context,
	IMG_Point		*center,			/* 中心点 */
	IMG_FLOAT		r,					/* 半径 */
	IMG_FLOAT		sangle,				/* 始点角度 */
	IMG_FLOAT		eangle,				/* 終点角度 */
	IMG_ArcDrawMode	mode,				/* 弧の描き方 */
	IMG_BOOL		isDraw);			/* 描画命令か(でなければパス構築) */

extern int IMG_Command_Circle_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_Ellipseクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_ellipse {
    IMG_Command		super;
	IMG_Point		center;			/* 中心点 */
	IMG_FLOAT		rx;				/* 水平半径 */
	IMG_FLOAT		ry;				/* 垂直半径 */
	IMG_FLOAT		sangle;			/* 始点角度 */
	IMG_FLOAT		eangle;			/* 終点角度 */
	IMG_ArcDrawMode	mode;			/* 弧の描き方 */
	IMG_BOOL		isDraw;			/* 描画命令か(でなければパス構築) */
} IMG_Command_Ellipse;

extern IMG_CommandPtr IMG_Command_Ellipse_Create(
	IMG_Context		*context,
	IMG_Point		*center,		/* 中心点 */
	IMG_FLOAT		rx,				/* 水平半径 */
	IMG_FLOAT		ry,				/* 垂直半径 */
	IMG_FLOAT		sangle,			/* 始点角度 */
	IMG_FLOAT		eangle,			/* 終点角度 */
	IMG_ArcDrawMode	mode,			/* 弧の描き方 */
	IMG_BOOL		isDraw);		/* 描画命令か(でなければパス構築) */

extern int IMG_Command_Ellipse_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_RoundRectangleクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_roundrectangle {
    IMG_Command		super;
	IMG_Point		point1;			/* 対角点1の座標 */
	IMG_Point		point2;			/* 対角点2の座標 */
	IMG_FLOAT		rx;				/* 角丸の外接矩形の水平半径 */
	IMG_FLOAT		ry;				/* 角丸の外接矩形の垂直半径 */
	IMG_BOOL		isDraw;			/* 描画命令か(でなければパス構築) */
} IMG_Command_RoundRectangle;

extern IMG_CommandPtr IMG_Command_RoundRectangle_Create(
	IMG_Context		*context,
	IMG_Point		*point1,		/* 対角点1の座標 */
	IMG_Point		*point2,		/* 対角点2の座標 */
	IMG_FLOAT		rx,				/* 角丸の外接矩形の水平半径 */
	IMG_FLOAT		ry,				/* 角丸の外接矩形の垂直半径 */
	IMG_BOOL		isDraw);		/* 描画命令か(でなければパス構築) */

extern int IMG_Command_RoundRectangle_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

/*-------------------------------------------------------------------------
  IMG_Command_Bezierクラスの定義
-------------------------------------------------------------------------*/

typedef struct img_command_bezier {
    IMG_Command		super;
	IMG_Point		start;			/* 描画開始点(直接描画の時だけ有効) */
	IMG_Point		*points;		/* ベジェ曲線を構成する点の配列 */
	IMG_UINT16		nBezier;		/* ベジェ曲線の数 */
	IMG_BOOL		isDraw;			/* 描画命令か(でなければパス構築) */
} IMG_Command_Bezier;

extern IMG_CommandPtr IMG_Command_Bezier_Create(
	IMG_Context		*context,
	IMG_Point		*start,			/* 描画開始点(直接描画の時だけ有効) */
	IMG_Point		*points,		/* ベジェ曲線を構成する点の配列 */
	IMG_UINT16		nBezier,		/* ベジェ曲線の数 */
	IMG_BOOL		isDraw);		/* 描画命令か(でなければパス構築) */

extern int IMG_Command_Bezier_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandGraphics_h */

/*
 * Log
 * 04.Mar.2001 Yozo Kashima IMG_Command.hよりブランチ。
 * 26.Fed.2003 Yozo Kashima IMG_Command_DrawRectangleに矩形の右端と下端を描画する/しないの切り替え属性を追加(AR#1103)。
 */

/* end of IMG_CommandGraphics.h */
