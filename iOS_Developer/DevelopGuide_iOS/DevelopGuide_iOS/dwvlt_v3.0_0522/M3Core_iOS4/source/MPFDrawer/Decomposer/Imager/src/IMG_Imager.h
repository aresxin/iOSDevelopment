/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Imager.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_Imager_h
#define INC_IMG_Imager_h

#include "IMG_Builtin.h"

#include "COM_Windows.h"
#include "COM_DeviceColorSpace.h"
#include "COM_OutputLocation.h"

/*
 * 使用メモリサイズの取得
 */
int IMG_GetMemSize(
	WORD resolutionX,		/* X方向の解像度 */
	WORD resolutionY,		/* Y方向の解像度 */
	DWORD *dlSize,			/* 中間データの保存用とワーク用に必要なメモリサイズ */
	DWORD *rbSize);			/* レンダリングに必要なメモリサイズ */

/*
 * 初期化と終了
 */
void* IMG_Initialize(
	void* dlAddress1,		/* 中間コードの蓄積、及びワーク用に使用するメモリのアドレス1 */
	DWORD dlSize1,			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ1 */
	void* dlAddress2,		/* 中間コードの蓄積、及びワーク用に使用するメモリのアドレス2 */
	DWORD dlSize2,			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ2 */
	void* rbAddress,		/* レンダリング用バッファのアドレス */
	DWORD rbSize,			/* レンダリング用バッファのサイズ */
	WORD outputResolutionX,	/* X方向の出力解像度 */
	WORD outputResolutionY,	/* Y方向の出力解像度 */
	WORD inputResolutionX,	/* X方向の入力解像度 */
	WORD inputResolutionY,	/* Y方向の入力解像度 */
	WORD imageResolutionX,	/* X方向のイメージ蓄積解像度 */
	WORD imageResolutionY,	/* Y方向のイメージ蓄積解像度 */
	WORD maxPageSizeX,		/* X方向の最大ページサイズ */
	WORD maxPageSizeY,		/* Y方向の最大ページサイズ */
	char *directryPath,		/* テンポラリファイルを作成するディレクトリのフルパス名 */
	void *edgeSinkSet,	/* EdgeSinkSetのハンドル */
	void *cstParameter);	/* 色変換パラメータ */

int IMG_Finalize(
	void *imager);			/* Imagerのハンドル */

/*
 * ジョブ制御
 */
int IMG_StartJob(
	void *imager,			/* Imagerのハンドル */
	WORD patternMode);		/* パターンデータの変換パラメータ */

int IMG_EndJob(
	void *imager);			/* Imagerのハンドル */

int IMG_StartPage(
	void *imager,			/* Imagerのハンドル */
    void *pageParam,		/* ページパラメータ HB_PageParam参照 */
	void *extraParam,		/* 適用先固有のパラメータ HB_ViewBufferParam */
	COM_DeviceColorSpace *pmParameter); /* ページ生成用パラメータ */

int IMG_EndPage(
	void *imager);			/* Imagerのハンドル */

/*
 * デバイス管理
 */
int IMG_ShowPage(
	void *imager,			/* Imagerのハンドル */
	COM_OutputLocation *location, /* 出力先情報 */
	COM_DeviceColorSpace *rndParameter); /* レンダリングパラメータ */

int IMG_SetPatternResolution(
	void *imager,			/* Imagerのハンドル */
	WORD resolution);		/* パターンデータ解像度(単位: dpi) */

int IMG_SetColorParameter(
	void* imager,			/* Imagerのハンドル */
	void* colorParameter);	/* 色変換パラメータ */

int IMG_SetRasterSmoothingMode (
	void* imager,			/* Imagerのハンドル */
	WORD mode,				/* イメージ縮小時の補完処理モード */
	WORD quality);			/* イメージ品質 */

int IMG_SetMaskSmoothingMode (
	void* imager,			/* Imagerのハンドル */
	WORD mode,				/* イメージマスク縮小時の補完処理モード */
	WORD quality);			/* イメージマスク品質 */

/*
 * 描画属性設定
 */
int IMG_SetAxis(
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT a, IMG_FLOAT b,		/* 変換行列のa,b成分 */
	IMG_FLOAT c, IMG_FLOAT d,		/* 変換行列のc,d成分 */
	IMG_FLOAT tx, IMG_FLOAT ty);	/* 変換行列のtx,ty成分 */

int IMG_SetLineWidth(
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT width);			/* 線幅 */

int IMG_SetLineCap(
	void *imager,			/* Imagerのハンドル */
	WORD cap);				/* キャップ種類 */

int IMG_SetLineJoin(
	void *imager,			/* Imagerのハンドル */
	WORD join);				/* ジョイン種類 */

int IMG_SetMiterLimit(
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT miterLimit);		/* マイター長 */

int IMG_SetLineType(
	void *imager,			/* Imagerのハンドル */
	WORD lineStyle,			/* 線スタイル */
	IMG_FLOAT offset,			/* 任意形状スタートオフセット */
	WORD count,				/* 任意形状マスクデータ個数 */
	IMG_FLOAT *data);			/* 任意形状マスクデータ列へのポインタ */

int IMG_AdjustStroke(
	void *imager,			/* Imagerのハンドル */
	BOOL strokeMode);		/* Stroke調整の有無 */

int IMG_SetFillMode(
	void *imager,			/* Imagerのハンドル */
	WORD fillMode);			/* 塗りつぶし規則 */

int IMG_SetDrawMode(
	void *imager,			/* Imagerのハンドル */
	WORD drawMode);			/* 描画方式 */

int IMG_SetRopMode(
	void *imager,			/* Imagerのハンドル */
	WORD ropMode,			/* ROPモード */
	DWORD ropNumber);		/* ROPコード */

int IMG_SetGraphicsMode(
	void *imager,			/* Imagerのハンドル */
	WORD fill,				/* 面積０の閉領域の塗り潰し除外指定 */
	WORD line);				/* 細線強調描画の指定 */

/*
 * 描画色設定
 */
int IMG_SetSolidColor(
	void *imager,			/* Imagerのハンドル */
	WORD drawMethod,		/* 適用する描画方式 */
	WORD colorSpace,		/* 色空間 */
	char *data);			/* 色値 */

int IMG_SetHatchPattern(
	void *imager,			/* Imagerのハンドル */
	POINT *startPoint,		/* 描画開始点 */
	WORD drawMethod,		/* 指定対象 */
	WORD foregroundColorSpace,		/* 前景色の色空間 */
	WORD backgroundColorSpace,		/* 背景色の色空間 */
	BOOL polality,			/* 極性 */
	char *foregroundColor,	/* 前景色の色データ */
	char *backgroundColor,	/* 背景色の色データ */
	WORD transparency,		/* 透過モード */
	char hatch);			/* ハッチパターン種別 */

int IMG_SetMaskPattern(
	void *imager,			/* Imagerのハンドル */
	POINT *startPoint,		/* 描画開始点 */
	WORD drawMethod,		/* 指定対象 */
	WORD foregroundColorSpace,		/* 前景色の色空間 */
	WORD backgroundColorSpace,		/* 背景色の色空間 */
	BOOL polality,			/* 極性 */
	char *foregroundColor,	/* 前景色の色データ */
	char *backgroundColor,	/* 背景色の色データ */
	WORD transparency,		/* 透過モード */
	WORD width,				/* パターンの幅 */
	WORD height,			/* パターンの高さ */
	char *pattern);			/* パターンデータ */

int IMG_SetRasterPattern(
	void *imager,			/* Imagerのハンドル */
	POINT *startPoint,		/* 描画開始点 */
	WORD drawMethod,		/* 指定対象 */
	WORD colorSpace,		/* 色空間 */
	WORD depth,				/* 色の深さ */
	WORD width,				/* パターンの幅 */
	WORD height,			/* パターンの高さ */
	WORD order,				/* ラスターフォーマット(色順次タイプ) */
	DWORD size,				/* パターンデータのバイトサイズ */
	char *pattern);			/* パターンデータ */

/*
 * クリップ操作
 */
int IMG_InitClip(
	void *imager);			/* Imagerのハンドル */

int IMG_SetRectangleClip(
	void *imager,			/* Imagerのハンドル */
	WORD  clipMode,			/* クリップの論理演算モード */
	POINT *point1,			/* 対角点座標1 */
	POINT *point2);			/* 対角点座標2 */

int IMG_SetClipRegion(
	void *imager,			/* Imagerのハンドル */
	WORD  clipMode,			/* クリップの論理演算モード */
	WORD  num,				/* 矩形情報の数 */
	IMG_FLOAT *data);			/* 矩形情報配列 */

int IMG_ClipPath(
	void *imager,			/* Imagerのハンドル */
	WORD  clipMode);		/* クリップの論理演算モード */

int IMG_OffsetClip(
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT xOffset,			/* x軸方向のオフセット */
	IMG_FLOAT yOffset);			/* y軸方向のオフセット */

int IMG_SaveClip(
	void *imager);			/* Imagerのハンドル */

int IMG_RestoreClip(
	void *imager);			/* Imagerのハンドル */

/*
 * パス操作
 */
int IMG_InitPath(
	void *imager);			/* Imagerのハンドル */

int IMG_ClosePath(
	void *imager);			/* Imagerのハンドル */

int IMG_MovePoint(
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT x, IMG_FLOAT y);		/* 移動先座標 */

int IMG_DrawPath(
	void *imager);			/* Imagerのハンドル */

int IMG_AddLinePath(
	void *imager,			/* Imagerのハンドル */
	WORD num,			/* 線分数 */
	IMG_REAL32 *data);		/* num個の折点座標(x,y)へのポインタ */

int IMG_AddEllipseArcPath(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT rx,			/* 水平半径 */
	IMG_FLOAT ry,			/* 垂直半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_AddEllipseChordPath(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT rx,			/* 水平半径 */
	IMG_FLOAT ry,			/* 垂直半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_AddEllipsePiePath(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT rx,			/* 水平半径 */
	IMG_FLOAT ry,			/* 垂直半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_AddBezierPath(
	void *imager,		/* Imagerのハンドル */
	WORD num,			/* 曲線数 */
	IMG_FLOAT *data);		/* num個のBezier曲線情報へのポインタ */

int IMG_AddRectanglePath(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x2,			/* 対角点2のx座標 */
	IMG_FLOAT y2);			/* 対角点2のy座標 */

int IMG_AddRoundRectanglePath(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x1,			/* 対角点1のx座標 */
	IMG_FLOAT y1,			/* 対角点1のy座標 */
	IMG_FLOAT x2,			/* 対角点2のx座標 */
	IMG_FLOAT y2,			/* 対角点2のy座標 */
	IMG_FLOAT rx,			/* 角丸の外接矩形の水平半径 */
	IMG_FLOAT ry);			/* 角丸の外接矩形の垂直半径 */

/*
 * 直接描画
 */
int IMG_DrawLine(
	void *imager,			/* Imagerのハンドル */
	WORD num,				/* 線分数 */
	void *data);			/* num+1個の折点座標へのポインタ */

int IMG_DrawScanline(
	void *imager,			/* Imagerのハンドル */
	WORD num,				/* スキャンライン数 */
	void *startPoints,		/* num個のスキャンライン始点座標へのポインタ */
	WORD *lengths);			/* num個の各スキャンラインのx方向の長さへのポインタ */

int IMG_DrawRectangle(
	void *imager,			/* Imagerのハンドル */
	IMG_REAL32 x1, IMG_REAL32 y1,	/* 対角点1の座標 */
	IMG_REAL32 x2, IMG_REAL32 y2,	/* 対角点2の座標 */
	WORD drawRightBottom);	/* 矩形の右端と下端を描画するかどうか */

int IMG_DrawRectangleSet(
	void *imager,			/* Imagerのハンドル */
	IMG_UINT16	nrect,		/* 矩形の総数 */
	IMG_UINT16	blocks,		/* ブロック数 */
	IMG_REAL32	startY,		/* 最初の矩形の左上点のY座標 */
	IMG_UINT16	*lines,		/* ライン数の配列 */
	IMG_UINT16	*colums,	/* 列数の配列 */
	IMG_REAL32	*heights,	/* 矩形高さの配列 */
	IMG_REAL32	*x,			/* 描画開始点のX座標 */
	IMG_REAL32	*width);	/* 矩形の幅 */

int IMG_DrawEllipseArc (
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT rx,			/* 水平半径 */
	IMG_FLOAT ry,			/* 垂直半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_DrawEllipseChord(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT rx,			/* 水平半径 */
	IMG_FLOAT ry,			/* 垂直半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_DrawEllipsePie(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT rx,			/* 水平半径 */
	IMG_FLOAT ry,			/* 垂直半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_DrawCircleArc(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT r,			/* 半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_DrawCirclePie(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x,			/* 中心点x座標 */
	IMG_FLOAT y,			/* 中心点y座標 */
	IMG_FLOAT r,			/* 半径 */
	IMG_FLOAT sangle,		/* 始点角度 */
	IMG_FLOAT eangle);		/* 終点角度 */

int IMG_DrawBezier(
	void *imager,		/* Imagerのハンドル */
	WORD num,			/* 曲線数 */
	IMG_FLOAT sx,			/* 始点x */
	IMG_FLOAT sy,			/* 始点y */
	IMG_FLOAT *data);		/* num個のBezier曲線情報へのポインタ */

int IMG_DrawRoundRectangle(
	void *imager,		/* Imagerのハンドル */
	IMG_FLOAT x1,			/* 対角点1のx座標 */
	IMG_FLOAT y1,			/* 対角点1のy座標 */
	IMG_FLOAT x2,			/* 対角点2のx座標 */
	IMG_FLOAT y2,			/* 対角点2のy座標 */
	IMG_FLOAT rx,			/* 角丸の外接矩形の水平半径 */
	IMG_FLOAT ry);			/* 角丸の外接矩形の垂直半径 */

/*
 * イメージマスク描画
 */
int IMG_DrawImageMask(
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT x, IMG_FLOAT y,		/* 描画開始座標 */
	IMG_FLOAT a, IMG_FLOAT b,		/* イメージ変換行列のa,b成分 */
	IMG_FLOAT c, IMG_FLOAT d,		/* イメージ変換行列のc,d成分 */
	IMG_FLOAT tx, IMG_FLOAT ty,		/* イメージ変換行列のtx,ty成分 */
	WORD width,				/* イメージマスクの幅 */
	WORD height,			/* イメージマスクの高さ */
	BOOL polarity,			/* イメージマスクの極性 */
	DWORD dataSize,			/* イメージマスクのデータサイズ */
	char *maskData);		/* イメージマスクのデータ */

/*
 * イメージ描画
 */
int IMG_DrawImage (
	void *imager,			/* Imagerのハンドル */
	IMG_FLOAT x, IMG_FLOAT y,		/* 描画開始座標 */
	IMG_FLOAT a, IMG_FLOAT b,		/* イメージ変換行列のa,b成分 */
	IMG_FLOAT c, IMG_FLOAT d,		/* イメージ変換行列のc,d成分 */
	IMG_FLOAT tx, IMG_FLOAT ty,		/* イメージ変換行列のtx,ty成分 */
	WORD width, WORD height,/* マスク＆イメージデータの幅と高さ */
	BOOL mask,				/* マスクの有無 */
	BOOL polarity,			/* マスクの極性（マスクなしの場合は未使用）*/
	DWORD maskSize,			/* マスクデータのバイト数（マスクなしの場合は未使用）*/
	BOOL image,				/* イメージの有無 */
	WORD colorSpace,		/* 色空間(イメージなしの場合は未使用) */
	WORD colorDepth,		/* paletteDataのdepth(Indexed Colorでない場合は未使用）*/
	WORD paletteEntries,	/* palette tableのエントリー数(Indexed Colorでない場合は未使用）*/
	WORD paletteByteSizes,	/* palette tableのバイト数(Indexed Colorでない場合は未使用）*/
	char *paletteData,		/* palette tableデータ */
	WORD order,				/* イメージデータの色順次 */
	WORD imageDataDepth,	/* イメージデータの深さ */
	WORD compressionMethod,	/* 圧縮方式 */
	DWORD imageSize,		/* イメージデータサイズ */
	char *maskData,			/* マスクデータ（マスクなしの場合は未使用）*/
	char *imageData,		/* イメージデータ（イメージデータなしの場合は未使用）*/
	char *dataFileName);	/* イメージデータが保存されたファイルの名前 */

/*
 * 文字描画
 */
int IMG_DrawFont(
	void *imager,			/* Imagerのハンドル */
	POINT *startPoint,		/* 描画開始点座標 */
	char *address);			/* ラスタフォントデータへのポインタ */

#ifndef IMG_FM_NODEFINE

int IMG_SetLogFont(
			       void 	*imager, 
			       int 	lfHeight,
			       int 	lfWidth,
			       int 	lfEscapement,
			       int 	lfOrientation,
			       int 	lfWeight,
			       unsigned char 	lfItalic,
			       unsigned char 	lfUnderline,
			       unsigned char 	lfStrikeOut,
			       unsigned char 	lfCharSet,
			       unsigned char 	lfOutPrecision,
			       unsigned char 	lfClipPrecision,
			       unsigned char 	lfQuality,
			       unsigned char 	lfPitchAndFamily,
			       unsigned char	lfFaceNameSize,
			       unsigned char*	lfFaceName,
			       unsigned char	lfFaceNameEncoding,
			       unsigned char	lfEmulation,
			       unsigned char*	lfPhysicalCharSet
			       );

int IMG_DrawCodeFont(
				 void 			*imager, 
				 IMG_FLOAT			x,
				 IMG_FLOAT			y,
				 char			pitchMode,
				 WORD			pitchLength,
				 IMG_FLOAT			*pitchData,
				 WORD			codeSize,
				 char			*codePtr,
				 unsigned char		codeEncoding,	
				 WORD			textAlign,
				 WORD			transparency,
				 WORD			bkColorSpace,
				 unsigned char		*bkColor,
				 WORD			rectOption,
				 IMG_FLOAT			lx,
				 IMG_FLOAT			ly,
				 IMG_FLOAT			ux,
				 IMG_FLOAT			uy
				 );

int IMG_DrawDataFont(
				 void 			*imager, 
				 IMG_FLOAT			x,
				 IMG_FLOAT			y,
				 DWORD			cacheKey,
				 char			*dataPtr
				 );

int IMG_StartFontRegister(
				 void 			*imager 
				 );

int IMG_EndFontRegister(
				 void 			*imager 
				 );

int IMG_GetFontRegister(
				 void 			*imager ,
				 char 			**dataAddress ,
				 int 			*numOfChar
				 );

#endif

#endif /* INC_IMG_Imager_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 03.Apr.2001 Yozo Kashima IMG_SetRopModeにropNumber引数を追加。
 *							IMG_StartPageのx,yの型をWORDに変更。
 * 04.Apr.2001 Yozo Kashima IMG_Initializeのimager引数を削除し、
 *							戻り値でハンドルを返すよう変更。
 *							IMG_InitializeでdlAddress,dlSizeの引数を2つに変更。
 *							IMG_InitializeのdirectryPathの型を変更。
 * 06.Apr.2001 Yozo Kashima DLL化のためEXPORT宣言を追加。
 * 11.Apr.2001 Yozo Kashima POINT型の引数をPOINTへのポインタ型に変更。
 *							IMG_InitClipを追加。
 * 12.Apr.2001 Yozo Kashima IMG_AddRectanglePathの引数x1,y1を削除。
 *							IMG_DrawLineの引数startPointを削除。開始点はdata引数に含める。
 *							IMG_DrawRectangleのPOINT型の引数p1,p2を4つのfloat型に変更。
 * 13.Apr.2001 Yozo Kashima IMG_Initializeのアドレスの型をDWORDからvoid*に修正。
 *							IMG_SetRasterPatternのsizeの型をWORDからDWORDに修正。 
 * 16.Apr.2001 Yozo Kashima IMG_InitializeのjobHandle引数の型をHANDLEからWORDに修正。
 * 25.Apr.2001 Yozo Yamaguchi 複数のPOINTへのポインタ型の引数をvoidへのポインタ型に変更。
 * 07.May.2001 Yozo Kashima IMG_SetHatchPattern,IMG_SetMaskPatternに背景色の色空間を指定する引数を追加。
 * 23.Aug.2001 Yozo Kashima IMG_InitializeのjobHandle引数の型をWORDからDWORDに変更。
 *							stdcall宣言を追加(Windows2000対応)。
 * 14.Sep.2001 Yozo Kashima IMG_SetLineWidthの線幅の型をWORDからfloatに変更。
 *							IMG_SetMiterLimitのマイターリミット長の型をWORDからfloatに変更。
 *							IMG_DrawImageにファイル名の引数を追加。
 * 11.Dec.2002 Yozo Kashima イメージの独立解像度指定のためのI/F変更。
 *							IMG_Initializeに入力解像度，イメージ蓄積解像度，最大ページサイズを指定する引数を追加。
 * 25.Dec.2002 Yozo Kashima IMG_SetClipRegionを追加(CEViewerのOLEアノテ対応)。
 * 26.Fed.2003 Yozo Kashima IMG_CommmandProceossr_DrawRectangleに矩形の右端と下端を描画する/しないの切り替え引数を追加(AR#1103)。
 * 28.May.2003 Yozo Kashima IMG_SaveClip,IMG_RestoreClipを追加(AR#845)。
 * 23.Sep.2003 Yozo Kashima IMG_StartPage,IMG_DrawRectangleのI/FをDriver/Viewerで統一。
 * 10.Aug.2004 Yozo Kashima IMG_SetMaskSmoothingModeを追加(DW-V6.0 MRC対応)。
 */

/* end of IMG_Imager.h */
