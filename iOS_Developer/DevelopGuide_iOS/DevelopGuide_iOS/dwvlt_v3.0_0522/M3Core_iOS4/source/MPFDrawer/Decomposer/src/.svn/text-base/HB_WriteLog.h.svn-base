/*
 * Copyright(C) 2001-2004 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: HB_WriteLog.h
 * Masao Morita 16.Jun.2003
 *
 */

#include <stdio.h>
#include "COM_ES_EdgeSinkMgrIF.h"


#if 0
/* ログファイルをスプールに書く場合	*/
#define HB_LOG_WRITESPOOL
#endif

#define HB_DEBUGINFO_LEVEL_NONE		0
#define HB_DEBUGINFO_LEVEL_1		1
#define HB_DEBUGINFO_LEVEL_IMGLOG	8
#define HB_DEBUGINFO_LEVEL_9		9
#define HB_DEBUGINFO_LEVEL_DUMP		0x7FFFFFFF

/*
 * Log出力情報
 */
typedef struct HB_LogInfoT 
{
	long	level;		/* ログレベル		*/
	FILE	*logfile;	/* ログ出力ファイル	*/
#if defined(HB_LOG_WRITESPOOL)
	void	*splfunc;	/* ファイル出力関数	*/
	int		fd;			/* 出力記述子		*/
#endif
} HB_LogInfo;


/*
 * Log出力後のStatus
 */
/* Log出力時のエラー				*/
#define HB_LOG_ERROR	(-1)

/* Log出力後も処理を続ける			*/
#define HB_LOG_CONTINUE	(0)

/* Log出力後上位モジュールへ戻る	*/
#define HB_LOG_BREAK	(1)




/*
 * 初期化と終了
 */
int  HB_Log_Initialize(
	void *logParam,
	void *jobParam,			/* ジョブパラメータ HB_JobParam参照		*/
	void *spoolParam,		/* スプールパラメータ HB_SpoolParam参照 */
	void *outputParameter,	/* 出力パラメータ情報 HB_OutputParam参照 */
	void *cstParameter,		/* 色変換パラメータ						*/
	void *debugInfo,		/* デバッグ情報指示 HB_DebugInfo参照	*/
	void *extraParam);		/* 適用先固有のパラメータ SIFで消費すること	*/


int  HB_Log_Finalize(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

/* Error発生時の終了処理 AR1563 */
int  HB_Log_ErrorFinalize(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

/*
 * ジョブ制御
 */
int  HB_Log_StartJob(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD patternMode);		/* パターンデータの変換パラメータ */

int  HB_Log_EndJob(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_StartPage(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	void *pageParam,		/* ページパラメータ HB_PageParam参照 */
	void *spoolParam,		/* ページ単位でのスプールパラメータ HB_SpoolParam参照	*/
	void *extraParam);		/* 適用先固有のパラメータ HB_ViewBufferParam等 */

int  HB_Log_EndPage(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	void *extraParam);		/* 適用先固有のパラメータ */


/*
 * デバイス管理
 */
int  HB_Log_ShowPage(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_SetPatternResolution(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD resolution);		/* パターンデータ解像度(単位: dpi) */

int  HB_Log_SetColorParameter(
	void* imager,			/* ログ情報パラメータ HB_LogInfo参照 */
	void* colorParameter);	/* 色変換パラメータ */

int  HB_Log_SetRasterSmoothingMode (
	void* imager,			/* ログ情報パラメータ HB_LogInfo参照 */
	WORD mode,				/* イメージ縮小時の補完処理モード */
	WORD quality);			/* イメージ品質 */

int  HB_Log_SetMaskSmoothingMode (
	void* imager,			/* ログ情報パラメータ HB_LogInfo参照 */
	WORD mode,				/* イメージマスク縮小時の補完処理モード */
	WORD quality);			/* イメージマスク品質 */

/*
 * 描画属性設定
 */
int  HB_Log_SetAxis(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT a, HB_FLOAT b,		/* 変換行列のa,b成分 */
	HB_FLOAT c, HB_FLOAT d,		/* 変換行列のc,d成分 */
	HB_FLOAT tx, HB_FLOAT ty);	/* 変換行列のtx,ty成分 */

int  HB_Log_SetLineWidth(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT width);			/* 線幅 */

int  HB_Log_SetLineCap(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD cap);				/* キャップ種類 */

int  HB_Log_SetLineJoin(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD join);				/* ジョイン種類 */

int  HB_Log_SetMiterLimit(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT miterLimit);		/* マイター長 */

int  HB_Log_SetLineType(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD lineStyle,			/* 線スタイル */
	HB_FLOAT offset,			/* 任意形状スタートオフセット */
	WORD count,				/* 任意形状マスクデータ個数 */
	HB_FLOAT *data);		/* 任意形状マスクデータ列へのポインタ */

int  HB_Log_AdjustStroke(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	BOOL strokeMode);		/* Stroke調整の有無 */

int  HB_Log_SetFillMode(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD fillMode);			/* 塗りつぶし規則 */

int  HB_Log_SetDrawMode(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD drawMode);			/* 描画方式 */

int  HB_Log_SetRopMode(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD ropMode,			/* ROPモード */
	DWORD ropNumber);		/* ROPコード */

int  HB_Log_SetGraphicsMode(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD fill,				/* 面積０の閉領域の塗り潰し除外指定 */
	WORD line);				/* 細線強調描画の指定 */

/*
 * 描画色設定
 */
int  HB_Log_SetSolidColor(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD drawMethod,		/* 適用する描画方式 */
	WORD colorSpace,		/* 色空間 */
	char *data);			/* 色値 */

int  HB_Log_SetHatchPattern(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	POINT *startPoint,		/* 描画開始点 */
	WORD drawMethod,		/* 指定対象 */
	WORD foregroundColorSpace,		/* 前景色の色空間 */
	WORD backgroundColorSpace,		/* 背景色の色空間 */
	BOOL polality,			/* 極性 */
	char *foregroundColor,	/* 前景色の色データ */
	char *backgroundColor,	/* 背景色の色データ */
	WORD transparency,		/* 透過モード */
	char hatch);			/* ハッチパターン種別 */

int  HB_Log_SetMaskPattern(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
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

int  HB_Log_SetRasterPattern(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
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
int  HB_Log_InitClip(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_SetRectangleClip(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD  clipMode,			/* クリップの論理演算モード */
	POINT *point1,			/* 対角点座標1 */
	POINT *point2);			/* 対角点座標2 */

int  HB_Log_SetClipRegion(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD  clipMode,			/* クリップの論理演算モード */
	WORD  num,				/* 矩形情報の数 */
	HB_FLOAT *data);		/* 矩形情報配列 */

int  HB_Log_ClipPath(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD  clipMode);		/* クリップの論理演算モード */

int  HB_Log_OffsetClip(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT xOffset,			/* x軸方向のオフセット */
	HB_FLOAT yOffset);			/* y軸方向のオフセット */

int  HB_Log_SaveClip(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_RestoreClip(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

/*
 * パス操作
 */
int  HB_Log_InitPath(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_ClosePath(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_MovePoint(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x, HB_FLOAT y);		/* 移動先座標 */

int  HB_Log_DrawPath(
	void *logParam);		/* ログ情報パラメータ HB_LogInfo参照 */

int  HB_Log_AddLinePath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	WORD num,		/* 線分数 */
	HB_REAL32 *data);	/* num個の折点座標(x,y)へのポインタ */

int  HB_Log_AddEllipseArcPath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_AddEllipseChordPath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_AddEllipsePiePath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_AddBezierPath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	WORD num,			/* 曲線数 */
	HB_FLOAT *data);	/* num個のBezier曲線情報へのポインタ */

int  HB_Log_AddRectanglePath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x2,			/* 対角点2のx座標 */
	HB_FLOAT y2);			/* 対角点2のy座標 */

int  HB_Log_AddRoundRectanglePath(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x1,			/* 対角点1のx座標 */
	HB_FLOAT y1,			/* 対角点1のy座標 */
	HB_FLOAT x2,			/* 対角点2のx座標 */
	HB_FLOAT y2,			/* 対角点2のy座標 */
	HB_FLOAT rx,			/* 角丸の外接矩形の水平半径 */
	HB_FLOAT ry);			/* 角丸の外接矩形の垂直半径 */

/*
 * 直接描画
 */
int  HB_Log_DrawLine(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD num,				/* 線分数 */
	void *data);			/* num+1個の折点座標へのポインタ */

int  HB_Log_DrawScanline(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD num,				/* スキャンライン数 */
	void *startPoints,		/* num個のスキャンライン始点座標へのポインタ */
	WORD *lengths);			/* num個の各スキャンラインのx方向の長さへのポインタ */

int  HB_Log_DrawRectangle(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_REAL32 x1, HB_REAL32 y1,	/* 対角点1の座標 */
	HB_REAL32 x2, HB_REAL32 y2,	/* 対角点2の座標 */
	WORD drawRightBottom);	/* 矩形の右端と下端を描画するかどうか */

int  HB_Log_DrawRectangleSet(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	WORD		nrect,		/* 矩形の総数 */
	WORD		blocks,		/* ブロック数 */
	HB_REAL32	startY,		/* 最初の矩形の左上点のY座標 */
	WORD		*lines,		/* ライン数の配列 */
	WORD		*columns,	/* 列数の配列 */
	HB_REAL32	*height,	/* 矩形高さの配列 */
	HB_REAL32	*x,			/* 描画開始点のX座標の配列 */
	HB_REAL32	*width);		/* 矩形の幅の配列 */
	
int  HB_Log_DrawEllipseArc (
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_DrawEllipseChord(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_DrawEllipsePie(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_DrawCircleArc(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT r,			/* 半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_DrawCirclePie(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT r,			/* 半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

int  HB_Log_DrawBezier(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	WORD num,			/* 曲線数 */
	HB_FLOAT sx,			/* 始点x */
	HB_FLOAT sy,			/* 始点y */
	HB_FLOAT *data);	/* num個のBezier曲線情報へのポインタ */

int  HB_Log_DrawRoundRectangle(
	void *logParam,	/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x1,			/* 対角点1のx座標 */
	HB_FLOAT y1,			/* 対角点1のy座標 */
	HB_FLOAT x2,			/* 対角点2のx座標 */
	HB_FLOAT y2,			/* 対角点2のy座標 */
	HB_FLOAT rx,			/* 角丸の外接矩形の水平半径 */
	HB_FLOAT ry);			/* 角丸の外接矩形の垂直半径 */

/*
 * イメージマスク描画
 */
int  HB_Log_DrawImageMask(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x, HB_FLOAT y,		/* 描画開始座標 */
	HB_FLOAT a, HB_FLOAT b,		/* イメージ変換行列のa,b成分 */
	HB_FLOAT c, HB_FLOAT d,		/* イメージ変換行列のc,d成分 */
	HB_FLOAT tx, HB_FLOAT ty,		/* イメージ変換行列のtx,ty成分 */
	WORD width,				/* イメージマスクの幅 */
	WORD height,			/* イメージマスクの高さ */
	BOOL polarity,			/* イメージマスクの極性 */
	DWORD dataSize,			/* イメージマスクのデータサイズ */
	char *maskData);		/* イメージマスクのデータ */

/*
 * イメージ描画
 */
int  HB_Log_DrawImage (
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	HB_FLOAT x, HB_FLOAT y,		/* 描画開始座標 */
	HB_FLOAT a, HB_FLOAT b,		/* イメージ変換行列のa,b成分 */
	HB_FLOAT c, HB_FLOAT d,		/* イメージ変換行列のc,d成分 */
	HB_FLOAT tx, HB_FLOAT ty,		/* イメージ変換行列のtx,ty成分 */
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
int  HB_Log_DrawFont(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	POINT *startPoint,		/* 描画開始点座標 */
	char *address);			/* ラスタフォントデータへのポインタ */

#ifndef HB_FM_NODEFINE

int  HB_Log_SetLogFont(
			       void 	*logParam, 
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

int  HB_Log_DrawCodeFont(
				 void 			*logParam, 
				 HB_FLOAT			x,
				 HB_FLOAT			y,
				 char			pitchMode,
				 WORD			pitchLength,
				 HB_FLOAT			*pitchData,
				 WORD			codeSize,
				 char			*codePtr,
				 unsigned char		codeEncoding,	
				 WORD			textAlign,
				 WORD			transparency,
				 WORD			bkColorSpace,
				 unsigned char		*bkColor,
				 WORD			rectOption,
				 HB_FLOAT			lx,
				 HB_FLOAT			ly,
				 HB_FLOAT			ux,
				 HB_FLOAT			uy
				 );

int  HB_Log_DrawDataFont(
				 void 			*logParam, 
				 HB_FLOAT			x,
				 HB_FLOAT			y,
				 DWORD			cacheKey,
				 char			*dataPtr
				 );

int  HB_Log_StartFontRegister(
				 void 			*logParam 
				 );

int  HB_Log_EndFontRegister(
				 void 			*logParam 
				 );

int  HB_Log_GetFontRegister(
				 void 			*logParam ,
				 char 			**dataAddress ,
				 int 			*numOfChar
				 );

#endif

/*
 * 制御系I/F
 */
int  HB_Log_SendJobHeader(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	void *jobHeader);		/* ESS ジョブヘッダ情報。ESS_Parameter_JOBHEADER参照 */

int  HB_Log_SendJobTrailer(
	void *logParam,		/* ログ情報パラメータ HB_LogInfo参照 */
	void *jobTrailer);		/* ESS ジョブトレイラ-情報 ESS_Parameter_JOBTRAILER参照 */


/*
 * Log
 * 14.Jul.2003 Yozo Kashima Created
 * 12.Sep.2003 Yozo Kashima HB_DrawRectangleの引数をPrinter/Viewerで統一。
 *							HB_SpoolParamのパス名を256→260(Windowsでのパス名の最大値)に変更。
 *							HB_SpoolParamにsizeメンバを追加。
 * 23.Sep.2003 Yozo Kashima HB_DrawRectangleのI/FをDriver/Viewerで統一。
 *							HB_StartPageにextraParam引数を追加。
 *							HB_JobParamTからdlAddress{1,2},rbAddressを削除。
 */

/* end of HB_Decomposer.h */

	
