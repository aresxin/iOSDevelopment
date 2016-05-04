/*
 * Copyright(C) 2001-2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandFilter.h - コマンドフィルタ抽象クラスの定義
 * Yozo Kashima 01.Dec.2003
 *
 */

#ifndef INC_IMG_CommandFilter_h
#define INC_IMG_CommandFilter_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Job.h"
#include "IMG_Page.h"
#include "IMG_Image.h"
#include "IMG_ImageMask.h"
#include "IMG_ClassPointer.h"

typedef struct img_commandfilter {
	/* Public操作 */

	int (*destroy)(
		IMG_CommandFilterPtr	self);				/* this pointer */

	/*
	 * フィルタ処理の中止
	 */
	int (*cancel)(
		IMG_CommandFilterPtr	self);				/* this pointer */

	/*
	 * 排出と終了
	 */
	int (*showPage)(
		IMG_CommandFilterPtr	self);				/* this pointer */

	int (*endPage)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*setColorParameter)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		void					*colorParameter);	/* 色変換パラメータ */
	/*
	 * 直接描画
	 */
    int (*drawLine)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_UINT16				num,				/* 線分数+1(=座標点の数) */
		IMG_Point				*points);			/* 座標点の配列 */

    int (*drawScanline)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_UINT16				num,				/* スキャンライン数 */
		IMG_Point				*points,			/* num個のスキャンラインの始点座標の配列 */
		IMG_UINT16				*lengths);			/* num個のスキャンラインの長さの配列 */

    int (*drawRectangle)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point1,			/* 対角点座標1 */
		IMG_Point				*point2,			/* 対角点座標2 */
		IMG_BOOL				drawRightBottom);	/* 右端と下端を描画するかどうか */

	int (*drawRectangleSet)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_UINT16				nrect,				/* 矩形の総数 */
		IMG_UINT16				blocks,				/* ブロック数 */
		IMG_REAL32				startY,				/* 最初の矩形の左上点のY座標 */
		IMG_UINT16				*lines,				/* ライン数の配列 */
		IMG_UINT16				*columns,			/* 列数の配列 */
		IMG_REAL32				*height,			/* 矩形高さの配列 */
		IMG_REAL32				*x,					/* 描画開始点のX座標の配列 */
		IMG_REAL32				*width,				/* 矩形の幅の配列 */
		IMG_BOOL				canOwnData);		/* xとwidthの配列を所有できるかどうか? */

    int (*drawEllipse)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*center,			/* 中心点 */
		IMG_FLOAT				rx,					/* 水平半径 */
		IMG_FLOAT				ry,					/* 垂直半径 */
		IMG_FLOAT				sangle,				/* 始点角度 */
		IMG_FLOAT				eangle,				/* 終点角度 */
		IMG_ArcDrawMode			mode);				/* 弧の描き方 */

    int (*drawCircle)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*center,			/* 中心点 */
		IMG_FLOAT				r,					/* 半径 */
		IMG_FLOAT				sangle,				/* 始点角度 */
		IMG_FLOAT				eangle,				/* 終点角度 */
		IMG_ArcDrawMode			mode);				/* 弧の描き方 */

    int (*drawBezier)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*start,				/* 描画開始点 */
		IMG_Point				*points,			/* ベジェ曲線を構成する点の配列 */
		IMG_UINT16				nBezier);			/* ベジェ曲線の数 */

    int (*drawRoundRectangle)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point1,			/* 対角点1の座標 */
		IMG_Point				*point2,			/* 対角点2の座標 */
		IMG_FLOAT				rx,					/* 角丸の外接矩形の水平半径 */
		IMG_FLOAT				ry);				/* 角丸の外接矩形の垂直半径 */

    int (*drawImageMask)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_ImageMaskParam		*maskParam,			/* イメージマスクパラメータ */
		char					*maskData);			/* イメージマスクのデータ */

    int (*drawImage)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_ImageParam			*imageParam,		/* イメージパラメータ */
		char					*maskData,			/* マスクのデータ */
		char					*paletteData,		/* パレットデータ */
		char					*imageData,			/* イメージデータ */
		char					*dataFileName);		/* イメージデータが保存されたファイルの名前 */

    int (*drawFont)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point,				/* 描画開始点 */
		char					*address);			/* データへのポインタ */

#ifndef IMG_FM_NODEFINE
    int (*setLogFont)(
		IMG_CommandFilterPtr	self,
		IMG_FM_LogFont			*logFont);

    int (*drawCodeFont)(
		IMG_CommandFilterPtr	self,
        IMG_FM_Point			*point,
		IMG_FM_CodeString		*codeString,
        IMG_FM_RectOption		rectOption,
        IMG_FM_Rect				*clipRect);

    int (*drawDataFont)(
		IMG_CommandFilterPtr	self,
        IMG_FM_Point			*point,
		IMG_FM_DataCharacter	*dataCharacter);

    int (*startFontRegister)(
		IMG_CommandFilterPtr	self);

    int (*endFontRegister)(
		IMG_CommandFilterPtr	self);

    int (*getFontRegister)(
		IMG_CommandFilterPtr	self,
		char					**dataAddress,
		int						*numOfChar);
#endif

    /*
	 * パス操作
	 */
    int (*initPath)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*moveTo)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point);			/* ポイントオブジェクト */

    int (*addRectanglePath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point2);			/* 対角点2の座標 */

    int (*addLinePath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point,				/* 座標点の配列 */
		IMG_UINT16				numberOfPoints);	/* 座標点の数 */

    int (*addEllipsePath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*center,			/* 中心点 */
		IMG_FLOAT				rx,					/* 水平半径 */
		IMG_FLOAT				ry,					/* 垂直半径 */
		IMG_FLOAT				sangle,				/* 始点角度 */
		IMG_FLOAT				eangle,				/* 終点角度 */
		IMG_ArcDrawMode			mode);				/* 弧の描き方 */

    int (*addCirclePath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*center,			/* 中心点 */
		IMG_FLOAT				r,					/* 半径 */
		IMG_FLOAT				sangle,				/* 始点角度 */
		IMG_FLOAT				eangle,				/* 終点角度 */
		IMG_ArcDrawMode			mode);				/* 弧の描き方 */

    int (*addBezierPath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*points,			/* ベジェ曲線を構成する点の配列 */
		IMG_UINT16				nBezier);			/* ベジェ曲線の数 */
	
    int (*addRoundRectanglePath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Point				*point1,			/* 対角点1の座標 */
		IMG_Point				*point2,			/* 対角点2の座標 */
		IMG_FLOAT				rx,					/* 角丸の外接矩形の水平半径 */
		IMG_FLOAT				ry);				/* 角丸の外接矩形の垂直半径 */

    int (*closePath)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*paintPath)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    /*
	 * クリップ
     */
    int (*initClip)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*setRectangleClip)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_ClipRopMode			clipRopMode,		/* クリップの論理演算モード */
		IMG_Point				*point1,			/* 対角点座標1 */
		IMG_Point				*point2);			/* 対角点座標2 */

    int (*setClipRegion)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_ClipRopMode			clipRopMode,		/* クリップの論理演算モード */
		IMG_UINT16				num,				/* 矩形情報の数 */
		IMG_FLOAT					*data);				/* 矩形情報配列 */

    int (*clipPath)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_ClipRopMode			clipRopMode);		/* クリップの論理演算モード */

    int (*offsetClip)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_FLOAT					xOffset,			/* x軸方向のオフセット */
		IMG_FLOAT					yOffset);			/* y軸方向のオフセット */

    int (*saveClip)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*restoreClip)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*startClip)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    int (*endClip)(
		IMG_CommandFilterPtr	self);				/* this pointer */

    /*
	 * 描画属性設定
	 */
    int (*setSolidColor)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_DrawMode			drawMode,			/* 描画モード */
		IMG_ColorSpace			colorSpace,			/* 色空間 */
		IMG_ColorData			*colorData);

    int (*setHatchPattern)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_DrawMode			drawMode,
		IMG_HatchPatternBrushParam *hatchParam);

    int (*setMaskPattern)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_DrawMode			drawMode,
		IMG_MaskPatternBrushParam *maskParam,
		char					*pattern);

    int (*setRasterPattern)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_DrawMode			drawMode,
		IMG_RasterPatternBrushParam *rasterParam,
		char					*pattern);

    int (*setDrawMode)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_DrawMode			drawMode);			/* 描画モード(Stoke/Fill) */

    int (*setRopMode)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_RopMode				ropMode,		/* ROPモード */
		IMG_UINT32				ropCode);		/* ROPコード */

    int (*setFillRule)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_FillRule			fillRule);		/* ROPコード */

    int (*setStrokeWidth)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_FLOAT					strokeWidth);	/* Stroke幅 */

    int (*setCapStyle)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_CapStyle			capStyle);		/* キャップスタイル */

    int (*setJoinStyle)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_JoinStyle			joinStyle);		/* ジョインスタイル */

    int (*setMiterLimit)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_FLOAT				miterLimit);	/* マイターリミット */

    int (*setLineStyle)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_LineStyle			lineStyle,		/* 線形状 */
		IMG_FLOAT				offset,			/* 任意形状スタートオフセット */
		IMG_UINT16				count,			/* 任意形状マスクデータ個数 */
		IMG_FLOAT				*data);			/* 任意形状マスクデータ列へのポインタ */

    int (*setGraphicMode)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_BOOL				fillZeroAreaRegion,		/* 面積0のFill指定 */
		IMG_BOOL				thickenOnePixelLine);	/* 細線強調指定 */

    int (*adjustStroke)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_BOOL				adjustStroke);	/* ストローク調整の指定 */

    int (*setMatrix)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_Matrix				*matrix);		/* 変換行列 */

	int (*startFixedTag)(
		IMG_CommandFilterPtr	self,				/* this pointer */
		IMG_ObjectTag			tag);

	int (*endFixedTag)(
		IMG_CommandFilterPtr	self);				/* this pointer */

	/*
	 * 属性
	 */
	/* protected */
	IMG_Context					*context;

	/*
	 * 関連
	 */
	/* protected */
	IMG_CommandFilterPtr		predecessor;	/* 前段のフィルタ */
	IMG_CommandFilterPtr		successor;		/* 後段のフィルタ */
	IMG_CommandFilterPtr		successorSaved;	/* 後段フィルタを一時的に記憶する領域 */
	IMG_INT32					pageNumber;

} IMG_CommandFilter;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandFilter_IsValid(
	IMG_CommandFilter	*self);

/*
 * コンストラクタとデストラクタ
 */

/* public */

/* protected */
extern int IMG_CommandFilter_Construct(
    IMG_CommandFilterPtr	self,			/* this pointer */
    IMG_Context				*context,		/* コンテキスト */
	IMG_INT32				pageNumber,		/* Page番号 */
	IMG_CommandFilterPtr	successor);		/* 後段のフィルタ */

extern int IMG_CommandFilter_Destruct(
	IMG_CommandFilterPtr	self);

extern IMG_DrawingAttributePtr IMG_CommandFilter_CreateInitialAttribute(
	IMG_CommandFilterPtr	self);			/* this pointer */

extern int IMG_CommandFilter_Cancel(
	IMG_CommandFilterPtr	self);			/* this pointer */

#endif /* INC_IMG_CommandFilter_h */

/*
 * Log
 * 01.Dec.2003 Yozo Kashima  Created
 */

/* end of IMG_CommandFilter.h */
