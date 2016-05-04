/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Page.h - last edit
 * Yozo Kashima 29-Mar-01
 *
 */

#ifndef INC_IMG_Page_h
#define INC_IMG_Page_h

#include "IMG_Builtin.h"
#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_ClassPointer.h"
#include "IMG_Job.h"
#include "IMG_Matrix.h"
#include "IMG_GraphicsContext.h"
#include "IMG_Brush.h"
#include "IMG_BitmapShape.h"
#include "IMG_GeometricShape.h"
#include "IMG_Path.h"
#include "IMG_ClipRegion.h"

#include "IMG_HatchPatternBrush.h"
#include "IMG_MaskPatternBrush.h"
#include "IMG_RasterPatternBrush.h"

/*
 * IMG_Pageクラスの定義
 */
typedef struct img_page {
	IMG_Context			*context;					/* コンテキストへのハンドル */
	IMG_Job				*job;						/* ジョブデータ */
	void				*colorParameter;			/* 色変換パラメータ */
	IMG_GraphicsContext graphicsContext;			/* グラフィックス属性 */
	IMG_Brush			*currentFillBrush;			/* カレントのFill用ブラシ */
	IMG_Brush			*currentStrokeBrush;		/* カレントのStroke用ブラシ */
	IMG_Path			*currentPath;				/* カレントパスオブジェクト */
	IMG_UINT16			patternIdCounter;			/* パターンID配布のためのカウンタ */
	IMG_TagFilterPtr	tagFilter;					/* タグフィルター */
} IMG_Page;

/*
 * オブジェクトの生成と削除
 */
extern IMG_Page *IMG_Page_Create(
	IMG_Context		*context,				/* コンテキスト */
	IMG_Job			*job,
	IMG_UINT16		pageWidth,				/* ページの幅(単位はピクセル) */
	IMG_UINT16		pageHeight,				/* ページの高さ(単位はピクセル) */
	IMG_ColorMode	colorMode);				/* カラーモード */

extern int IMG_Page_Destroy(
	IMG_Page *page);						/* ページオブジェクト */

/*
 * 排出と終了
 */
extern int IMG_Page_Show(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_End(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_SetColorParameter(
	IMG_Page *page,							/* ページオブジェクト */
	void *colorParameter);					/* 色変換パラメータ */

/*
 * 直接描画
 */
extern int IMG_Page_PaintGeometricShape(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_GeometricShape *geometricShape);	/* 幾何学図形オブジェクト */

extern int IMG_Page_PaintBitmapShape(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_BitmapShape *bitmapShape);			/* 幾何学図形オブジェクト */

/*
 * パス操作
 */
extern int IMG_Page_InitPath(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_GetCurrentPoint(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_Point *currentPoint);				/* カレントポイントオブジェクト */

extern int IMG_Page_MoveTo(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_Point *point);						/* ポイントオブジェクト */

extern int IMG_Page_LineTo(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_Point *point,						/* 点の配列 */
	IMG_UINT16 nPoints);					/* 点の数 */ 

extern int IMG_Page_AddPathOf(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_GeometricShape *shape);				/* 図形オブジェクト */

extern int IMG_Page_ClosePath(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_PaintPath(
	IMG_Page *page);						/* ページオブジェクト */

/*
 * クリップ操作
 */
extern int IMG_Page_InitClip(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_SetRectangleClip(
	IMG_Page	*page,						/* ページオブジェクト */
	IMG_ClipRopMode clipRopMode,			/* クリップの論理演算モード */
	IMG_Point	*point1,
	IMG_Point	*point2);

extern int IMG_Page_SetClipRegion(
	IMG_Page				*page,				/* this pointer */
	IMG_ClipRopMode			clipRopMode,		/* クリップの論理演算モード */
	IMG_UINT16				num,				/* 矩形情報の数 */
	IMG_FLOAT				*data);				/* 矩形情報配列 */

extern int IMG_Page_ClipPath(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_ClipRopMode clipRopMode);			/* クリップの論理演算モード */

extern int IMG_Page_OffsetClip(
	IMG_Page *page,			/* ページオブジェクト */
	IMG_FLOAT xOffset,		/* x軸方向のオフセット */
	IMG_FLOAT yOffset);		/* y軸方向のオフセット */

/*
 * クリップ操作の内部I/F
 */
extern int IMG_Page_StartClip(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_EndClip(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_SaveClip(
	IMG_Page *page);						/* ページオブジェクト */

extern int IMG_Page_RestoreClip(
	IMG_Page *page);						/* ページオブジェクト */

/*
 * 描画属性設定
 */

extern int IMG_Page_SetSolidColor(
	IMG_Page *page,
	IMG_DrawMode drawMode,
	IMG_ColorSpace colorSpace,
	IMG_ColorData *colorData);

extern int IMG_Page_SetHatchPattern(
	IMG_Page *page,
	IMG_DrawMode drawMode,
	IMG_HatchPatternBrushParam *hatchParam);

extern int IMG_Page_SetMaskPattern(
	IMG_Page *page,
	IMG_DrawMode drawMode,
	IMG_MaskPatternBrushParam *maskParam,
	char *pattern);

extern int IMG_Page_SetRasterPattern(
	IMG_Page *page,
	IMG_DrawMode drawMode,
	IMG_RasterPatternBrushParam *rasterParam,
	char *pattern);

extern int IMG_Page_GetCurrentBrush(
	IMG_Page *page,							/* ページオブジェクト */
    IMG_Brush **brush,						/* ブラシオブジェクト (-) */
	IMG_DrawMode drawMode);					/* 描画方式(Fill/Stroke) */
		
extern int IMG_Page_SetDrawMode(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_DrawMode drawMode);					/* 描画モード(Stoke/Fill) */

extern int IMG_Page_SetRopMode(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_RopMode ropMode,					/* ROPモード */
	IMG_UINT32 ropCode);						/* ROPコード */

extern int IMG_Page_SetFillRule(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_FillRule fillRule);					/* ROPコード */

extern int IMG_Page_SetStrokeWidth(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_FLOAT strokeWidth);						/* Stroke幅 */

extern int IMG_Page_SetCapStyle(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_CapStyle capStyle);					/* キャップスタイル */

extern int IMG_Page_SetJoinStyle(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_JoinStyle joinStyle);				/* ジョインスタイル */

extern int IMG_Page_SetMiterLimit(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_FLOAT miterLimit);					/* マイターリミット */

extern int IMG_Page_SetLineStyle(
	IMG_Page				*page,			/* ページオブジェクト */
	IMG_LineStyle			lineStyle,		/* 線形状 */
	IMG_FLOAT				offset,			/* 任意形状スタートオフセット */
	IMG_UINT16				count,			/* 任意形状マスクデータ個数 */
	IMG_FLOAT				*data);			/* 任意形状マスクデータ列へのポインタ(ヒープ上の領域) */

extern int IMG_Page_SetGraphicMode(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_BOOL fillZeroAreaRegion,			/* 面積0のFill指定 */
	IMG_BOOL thickenOnePixelLine);			/* 細線強調指定 */

extern int IMG_Page_AdjustStroke(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_BOOL adjustStroke);					/* ストローク調整の指定 */

extern int IMG_Page_SetMatrix(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_Matrix *matrix);					/* 変換行列 */

/*
 * 描画属性取得
 */
extern int IMG_Page_GetGraphicsContext(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_GraphicsContext *graphicsContext);	/* グラフィックスコンテキスト */

extern int IMG_Page_IsOverwriteMode(
	IMG_Page *page,							/* ページオブジェクト */
	IMG_BOOL *isOverwriteMode);				/* ROPが上書きモードかどうか */

extern IMG_BOOL IMG_Page_IsValid(
	IMG_Page *page);						/* ページオブジェクト */

/*
 * 文字描画
 */

#ifndef IMG_FM_NODEFINE
extern int IMG_Page_SetLogFont(
	IMG_Page		*self,
	IMG_FM_LogFont		*logFont);

extern int IMG_Page_DrawCodeFont(
	IMG_Page		*self,
        IMG_FM_Point		*point,
	IMG_FM_CodeString	*codeString,
        IMG_FM_RectOption	rectOption,
        IMG_FM_Rect		*clipRect);

extern int IMG_Page_DrawDataFont(
	IMG_Page		*self,
        IMG_FM_Point		*point,
	IMG_FM_DataCharacter	*dataCharacter);

extern int IMG_Page_StartFontRegister(
	IMG_Page		*self);

extern int IMG_Page_EndFontRegister(
	IMG_Page		*self);
				      
extern int IMG_Page_GetFontRegister(
	IMG_Page		*self,
	char			**dataAddress,
	int			*numOfChar);
				      
#endif

/*
 * 固定タグモード設定/解除
 */
extern int IMG_Page_StartFixedTag(
	IMG_Page		*page,
	IMG_ObjectTag	tag);

extern int IMG_Page_EndFixedTag(
	IMG_Page		*page);

#endif /* INC_IMG_Page_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 17.Apr.2001 Yozo Kashima IMG_Page_GetCurrentPointを追加。
 * 18,Apr.2001 Yozo Kashima forward declarationを削除。
 * 08.May.2001 Yozo Kashima IMG_PageにpatternIDCounterを追加。
 * 23.May.2001 Yozo Kashima IMG_Page_GetGraphicsContextを追加。
 *							コメントを追加。
 * 10.Aug.2001 Yozo Kashima ROP置換のためのリファクタリングに伴い、クリップ操作I/Fを修正。
 * 31.Aug.2001 Yozo Kashima IMG_Page_SetLineStyleに任意形状の線データを指定する引数を追加。
 * 14.Sep.2001 Yozo Kashima IMG_Page_SetMiterLimitのマイターリミット長の型をIMG_UINT32からIMG_FLOATに変更。
 * 16.Nov.2001 Yozo Kashima 2StepROPの置換処理を実装。
 *							IMG_Page_ChangeClipPathBehaviorを追加。
 * 21.Feb.2002 Yozo Kashima 曲線対応(IMG_Page_AddPathOfを追加).
 * 19.Dec.2002 Yozo Kashima IMG_Page_SetRectangleClip,IMG_Page_ClipPathにクリップの論理演算指定引数を追加。
 * 25.Dec.2002 Yozo Kashima IMG_Page_SetClipRegionを追加(OLEアノテ対応)。
 *							追加に伴いIMG_Page_SetRectangleClip,IMG_Page_ClipPathのリファクタリングを実施。
 * 12.May.2003 Yozo Kashima AR#1231対応(IMG_Page_LineTo I/Fの改善)。
 */

/* end of IMG_Page.h */
