/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandProcessor.h - コマンド処理クラス
 * Yozo Kashima 10.Aug.2001
 *
 */

#ifndef INC_IMG_CommandProcessor_h
#define INC_IMG_CommandProcessor_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_DrawingAttribute.h"
#include "IMG_Job.h"
#include "IMG_Page.h"
#include "IMG_RopSequence.h"
#include "IMG_Image.h"
#include "IMG_ImageMask.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandProcessor_DrawLineにおいて1点からなる図形を
 * 検出し除去するかどうか?
 */
#define IMG_DETECT_POINT_ON_DRAWLINE

/*
 * IMG_CommandProcessor_DrawLineにおいて矩形を検出し
 * 矩形専用の描画に切り替えるかどうか?
 */
#define IMG_DETECT_RECTANGLE_ON_DRAWLINE

typedef struct img_commandprocessor {
	/*
	 * 属性
	 */
	IMG_Context					*context;

	IMG_RopMode					curRopMode;
	IMG_UINT32					curRopCode;

#ifdef IMG_DETECT_USELESS_ROP
	IMG_RopMode					sentRopMode;
	IMG_UINT32					sentRopCode;
#endif

#ifdef IMG_DETECT_RECTANGLE_ON_DRAWLINE
	IMG_DrawMode				drawMode;
#endif

	/*
	 * 関連
	 */
	IMG_CommandFilterPtr		filter;
	IMG_Page					*page;

} IMG_CommandProcessor;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandProcessor_IsValid(
	IMG_CommandProcessor	*self);

/*
 * コンストラクタとデストラクタ
 */

/* public */
extern IMG_CommandProcessor* IMG_CommandProcessor_Create(
	IMG_Context		*context,				/* コンテキスト */
	IMG_Job			*job,
	IMG_UINT16		pageHeight,				/* ページの高さ(単位はピクセル) */
	IMG_UINT16		pageWidth,				/* ページの幅(単位はピクセル) */
	IMG_ColorMode	colorMode);				/* カラーモード */

extern int IMG_CommandProcessor_Destroy(
	IMG_CommandProcessor	*self);

/*
 * サービス関数
 */

 /*
 * 排出と終了
 */
extern int IMG_CommandProcessor_ShowPage(
	IMG_CommandProcessor	*self);				/* this pointer */

extern int IMG_CommandProcessor_EndPage(
	IMG_CommandProcessor	*self);				/* this pointer */

extern int IMG_CommandProcessor_SetColorParameter(
	IMG_CommandProcessor	*self,				/* this pointer */
	void					*colorParameter);	/* 色変換パラメータ */

/*
 * 直接描画
 */
extern int IMG_CommandProcessor_DrawLine(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_UINT16				num,				/* 線分数+1(=座標点の数) */
	IMG_Point16				*points);			/* 座標点の配列 */

extern int IMG_CommandProcessor_DrawScanline(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_UINT16				num,				/* スキャンライン数 */
	IMG_Point16				*points,			/* num個のスキャンラインの始点座標の配列 */
	IMG_UINT16				*lengths);			/* num個のスキャンラインの長さの配列 */

extern int IMG_CommandProcessor_DrawRectangle(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*point1,			/* 対角点座標1 */
	IMG_Point				*point2,			/* 対角点座標2 */
	IMG_BOOL				drawRightBottom);	/* 右端と下端を描画するかどうか */

extern int IMG_CommandProcessor_DrawRectangleSet(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_UINT16				nrect,				/* 矩形の総数 */
	IMG_UINT16				blocks,				/* ブロック数 */
	IMG_REAL32				startY,				/* 最初の矩形の左上点のY座標 */
	IMG_UINT16				*lines,				/* ライン数の配列 */
	IMG_UINT16				*columns,			/* 列数の配列 */
	IMG_REAL32				*height,			/* 矩形高さの配列 */
	IMG_REAL32				*x,					/* 描画開始点のX座標の配列 */
	IMG_REAL32				*width);			/* 矩形の幅の配列 */

extern int IMG_CommandProcessor_DrawEllipse(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*center,			/* 中心点 */
	IMG_FLOAT				rx,					/* 水平半径 */
	IMG_FLOAT				ry,					/* 垂直半径 */
	IMG_FLOAT				sangle,				/* 始点角度 */
	IMG_FLOAT				eangle,				/* 終点角度 */
	IMG_ArcDrawMode			mode);				/* 弧の描き方 */

extern int IMG_CommandProcessor_DrawCircle(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*center,			/* 中心点 */
	IMG_FLOAT				r,					/* 半径 */
	IMG_FLOAT				sangle,				/* 始点角度 */
	IMG_FLOAT				eangle,				/* 終点角度 */
	IMG_ArcDrawMode			mode);				/* 弧の描き方 */

extern int IMG_CommandProcessor_DrawBezier(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*start,				/* 描画開始点 */
	IMG_FLOAT				*points,			/* ベジェ曲線を構成する点の配列 */
	IMG_UINT16				nPoints);			/* 点の数(3の倍数) */

extern int IMG_CommandProcessor_DrawRoundRectangle(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*point1,			/* 対角点1の座標 */
	IMG_Point				*point2,			/* 対角点2の座標 */
	IMG_FLOAT				rx,					/* 角丸の外接矩形の水平半径 */
	IMG_FLOAT				ry);				/* 角丸の外接矩形の垂直半径 */

extern int IMG_CommandProcessor_DrawImageMask(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_ImageMaskParam		*maskParam,			/* イメージマスクパラメータ */
	char					*maskData);			/* イメージマスクのデータ */

extern int IMG_CommandProcessor_DrawImage(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_ImageParam			*imageParam,		/* イメージパラメータ */
	char					*maskData,			/* マスクのデータ */
	char					*paletteData,		/* パレットデータ */
	char					*imageData,			/* イメージデータ */
	char					*dataFileName);		/* イメージデータが保存されたファイルの名前 */

extern int IMG_CommandProcessor_DrawFont(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*point,				/* 描画開始点 */
	char					*address);			/* データへのポインタ */

#ifndef IMG_FM_NODEFINE
extern int IMG_CommandProcessor_SetLogFont(
	IMG_CommandProcessor	*self,
	IMG_FM_LogFont		*logFont);

extern int IMG_CommandProcessor_DrawCodeFont(
	IMG_CommandProcessor	*self,
        IMG_FM_Point		*point,
	IMG_FM_CodeString	*codeString,
        IMG_FM_RectOption	rectOption,
        IMG_FM_Rect		*clipRect);

extern int IMG_CommandProcessor_DrawDataFont(
	IMG_CommandProcessor	*self,
        IMG_FM_Point		*point,
	IMG_FM_DataCharacter	*dataCharacter);

extern int IMG_CommandProcessor_StartFontRegister(
	IMG_CommandProcessor	*self);

extern int IMG_CommandProcessor_EndFontRegister(
	IMG_CommandProcessor	*self);

extern int IMG_CommandProcessor_GetFontRegister(
	IMG_CommandProcessor	*self,
	char			**dataAddress,
	int			*numOfChar
	);

#endif

/*
 * パス操作
 */
extern int IMG_CommandProcessor_InitPath(
	IMG_CommandProcessor	*self);				/* this pointer */

extern int IMG_CommandProcessor_MoveTo(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*point);			/* ポイントオブジェクト */

extern int IMG_CommandProcessor_AddRectanglePath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*point2);			/* 対角点2の座標 */

extern int IMG_CommandProcessor_AddLinePath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_REAL32				*xyData,			/* num個の折点座標(x,y)へのポインタ */
	IMG_UINT16				numberOfPoints);	/* 座標点の数 */

extern int IMG_CommandProcessor_AddEllipsePath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*center,			/* 中心点 */
	IMG_FLOAT				rx,					/* 水平半径 */
	IMG_FLOAT				ry,					/* 垂直半径 */
	IMG_FLOAT				sangle,				/* 始点角度 */
	IMG_FLOAT				eangle,				/* 終点角度 */
	IMG_ArcDrawMode			mode);				/* 弧の描き方 */

extern int IMG_CommandProcessor_AddCirclePath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*center,			/* 中心点 */
	IMG_FLOAT				r,					/* 半径 */
	IMG_FLOAT				sangle,				/* 始点角度 */
	IMG_FLOAT				eangle,				/* 終点角度 */
	IMG_ArcDrawMode			mode);				/* 弧の描き方 */

extern int IMG_CommandProcessor_AddBezierPath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_FLOAT				*points,			/* ベジェ曲線を構成する点の配列 */
	IMG_UINT16				nPoints);			/* 点の数(3の倍数) */

extern int IMG_CommandProcessor_AddRoundRectanglePath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_Point				*point1,			/* 対角点1の座標 */
	IMG_Point				*point2,			/* 対角点2の座標 */
	IMG_FLOAT				rx,					/* 角丸の外接矩形の水平半径 */
	IMG_FLOAT				ry);				/* 角丸の外接矩形の垂直半径 */

extern int IMG_CommandProcessor_ClosePath(
	IMG_CommandProcessor	*self);				/* this pointer */

extern int IMG_CommandProcessor_PaintPath(
	IMG_CommandProcessor	*self);				/* this pointer */

/*
 * クリップ
 */

extern int IMG_CommandProcessor_InitClip(
	IMG_CommandProcessor	*self);				/* this pointer */

extern int IMG_CommandProcessor_SetRectangleClip(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_ClipRopMode			clipRopMode,		/* クリップの論理演算モード */
	IMG_Point				*point1,			/* 対角点座標1 */
	IMG_Point				*point2);			/* 対角点座標2 */

extern int IMG_CommandProcessor_SetClipRegion(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_ClipRopMode			clipRopMode,		/* クリップの論理演算モード */
	IMG_UINT16				num,				/* 矩形情報の数 */
	IMG_FLOAT				*data);				/* 矩形情報配列 */

extern int IMG_CommandProcessor_ClipPath(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_ClipRopMode			clipRopMode);		/* クリップの論理演算モード */

extern int IMG_CommandProcessor_OffsetClip(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_FLOAT					xOffset,			/* x軸方向のオフセット */
	IMG_FLOAT					yOffset);			/* y軸方向のオフセット */

extern int IMG_CommandProcessor_SaveClip(
	IMG_CommandProcessor	*self);				/* this pointer */

extern int IMG_CommandProcessor_RestoreClip(
	IMG_CommandProcessor	*self);				/* this pointer */

/*
 * 描画属性設定
 */
extern int IMG_CommandProcessor_SetSolidColor(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_DrawMode			drawMode,			/* 描画モード */
	IMG_ColorSpace			colorSpace,			/* 色空間 */
	IMG_ColorData			*colorData);

extern int IMG_CommandProcessor_SetHatchPattern(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_DrawMode drawMode,
	IMG_HatchPatternBrushParam *hatchParam);

extern int IMG_CommandProcessor_SetMaskPattern(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_DrawMode drawMode,
	IMG_MaskPatternBrushParam *maskParam,
	char *pattern);

extern int IMG_CommandProcessor_SetRasterPattern(
	IMG_CommandProcessor	*self,				/* this pointer */
	IMG_DrawMode drawMode,
	IMG_RasterPatternBrushParam *rasterParam,
	char *pattern);

extern int IMG_CommandProcessor_SetDrawMode(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_DrawMode			drawMode);		/* 描画モード(Stoke/Fill) */

extern int IMG_CommandProcessor_SetRopMode(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_RopMode				ropMode,		/* ROPモード */
	IMG_UINT32				ropCode);		/* ROPコード */

extern int IMG_CommandProcessor_SetFillRule(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_FillRule			fillRule);		/* ROPコード */

extern int IMG_CommandProcessor_SetStrokeWidth(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_FLOAT					strokeWidth);	/* Stroke幅 */

extern int IMG_CommandProcessor_SetCapStyle(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_CapStyle			capStyle);		/* キャップスタイル */

extern int IMG_CommandProcessor_SetJoinStyle(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_JoinStyle			joinStyle);		/* ジョインスタイル */

extern int IMG_CommandProcessor_SetMiterLimit(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_FLOAT				miterLimit);	/* マイターリミット */

extern int IMG_CommandProcessor_SetLineStyle(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_LineStyle			lineStyle,		/* 線形状 */
	IMG_FLOAT				offset,			/* 任意形状スタートオフセット */
	IMG_UINT16				count,			/* 任意形状マスクデータ個数 */
	IMG_FLOAT				*data);			/* 任意形状マスクデータ列へのポインタ */

extern int IMG_CommandProcessor_SetGraphicMode(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_BOOL				fillZeroAreaRegion,		/* 面積0のFill指定 */
	IMG_BOOL				thickenOnePixelLine);	/* 細線強調指定 */

extern int IMG_CommandProcessor_AdjustStroke(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_BOOL				adjustStroke);	/* ストローク調整の指定 */

extern int IMG_CommandProcessor_SetMatrix(
	IMG_CommandProcessor	*self,			/* this pointer */
	IMG_Matrix				*matrix);		/* 変換行列 */

#endif /* INC_IMG_CommandProcessor_h */

/*
 * Log
 * 10.Aug.2001 Yozo Kashima  Created
 * 31.Aug.2001 Yozo Kashima IMG_CommandProcessor_SetLineStyleに任意形状の線データを指定する引数を追加。
 * 10.Sep.2001 Yozo Kashima IMG_CommandProcessor_Replacedを削除。
 * 14.Sep.2001 Yozo Kashima IMG_CommandProcessor_SetMiterLimitのマイターリミット長の型をIMG_UINT32からIMG_FLOATに変更。
 * 17.Sep.2001 Yozo Kashima 障害#97(fh8007g0-07)の対応。
 *							蓄積コマンドのサイズを削減するためIMG_CommandProcessor_AddLinePathを追加。
 * 18.Sep.2001 Yozo Kashima 障害#22(SDPT087)イメージング対応。
 *							IMG_CommandProcessor_DrawImageにdataFileName引数を追加。
 * 02.Oct.2001 Yozo Kashima IMG_CommandProcessor_LineTo,IMG_CommandProcessor_GetCurrentPointを削除。
 * 03.Oct.2001 Yozo Kashima 障害#129(fh8008g0-08)の対応。
 *							IMG_CommandProcessor_{DrawLine,DrawScanlime}のI/Fを変更。
 * 21.Feb.2002 Yozo Kashima 曲線対応(I/Fを追加).
 * 19.Dec.2002 Yozo Kashima IMG_CommandProcessor_SetRectangleClip,IMG_CommandProcessor_ClipPathに
 *							クリップの論理演算指定引数を追加。
 * 25.Dec.2002 Yozo Kashima IMG_CommandProcessor_SetClipRegionを追加(OLEアノテ対応)。
 * 26.Fed.2003 Yozo Kashima IMG_CommandProceossr_DrawRectangleに矩形の右端と下端を描画する/しないの切り替え引数を追加(AR#1103)。
 * 28.May.2003 Yozo Kashima IMG_CommandProcessor_{SaveClip,RestoreClip}を追加(AR#845)。
 * 23.Dec.2003 Yozo Kashima AR#1439(ROP置換処理をIMG_CommandFilterRopReductionに移動).
 * 08.Apr.2004 Yozo Kashima AR#1468(冗長なROPの除去)
 * 13.Apr.2004 Yozo Kashima AR#1475(XDW2MRCTESTでJ11_W2K_600.XDWの7ページ目の文字の下線が消える)
 *							IMG_CommandProcessor_DrawLineで矩形を検出する。
 * 15.Apr.2004 Yozo Kashima AR#1474(一太郎から作成したＤＷファイルの文字飾りの色がおかしい)
 */

/* end of IMG_CommandProcessor.h */
