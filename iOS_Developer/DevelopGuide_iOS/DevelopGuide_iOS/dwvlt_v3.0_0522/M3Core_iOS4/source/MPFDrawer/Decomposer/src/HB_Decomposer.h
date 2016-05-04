/*
 * Copyright(C) 2001-2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: HB_Decomposer.h
 * Yozo Kashima 14.Jul.2003
 *
 */

#ifndef INC_HB_Decomposer_h
#define INC_HB_Decomposer_h

#if !defined(WIN95)
#include "COM_Windows.h"
#else
#define __declspec(a) extern
#define __stdcall
#endif

#ifndef DISABLE_HB_DLL_EXPORTS
#ifndef DOCUWORKS_VIEWER
#define HB_EXPORT	__declspec (dllexport)
#define HB_STDCALL	__stdcall
#else
#define HB_EXPORT
#define HB_STDCALL
#endif
#else
#define HB_EXPORT
#define HB_STDCALL
#endif

/*
 * 固定小数点対応
 */
#if !defined(HB_USE_FIXEDPOINT)
/* 浮動小数点使用	*/
typedef float		HB_FLOAT;
typedef float		HB_REAL32;
#else
/* 固定小数点使用	*/
#include "COM_HB_Fixed.h"
typedef float		HB_FLOAT;
typedef HB_Fixed32	HB_REAL32;
#endif


/*
 * 両面印刷指定
 */
#define	HB_PLEX_NULL		0
#define	HB_PLEX_SIMPLEX		1			/* 片面印刷 */
#define HB_PLEX_DUPLEX		2			/* 長編綴じ */
#define HB_PLEX_TUMBLE		3			/* 短編綴じ */

/*
 * ページ回転指定
 */
#define HB_PAGE_ROTATION_NULL	0
#define HB_PAGE_ROTATION_0		1		/* 回転なし */
#define	HB_PAGE_ROTATION_90		2		/* 90度回転 */
#define HB_PAGE_ROTATION_180	3		/* 180度回転 */
#define HB_PAGE_ROTATION_270	4		/* 270度回転 */
#define HB_PAGE_ROTATED_90		0x12	/* 90度回転済み	*/
#define HB_PAGE_ROTATED_180		0x13	/* 180度回転済み	*/
#define HB_PAGE_ROTATED_270		0x14	/* 270度回転済み	*/

/*
 * ジョブパラメータ構造体
 */
#define HB_SPLMAXFILENAME	260
typedef struct HB_JobParamT {
	DWORD size;				/* 構造体のサイズ */
	DWORD dlSize1;			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ1 */
	DWORD dlSize2;			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ2 */
	DWORD rbSize;			/* レンダリング用バッファのサイズ */
	WORD outputResolutionX;	/* X方向の出力解像度 */
	WORD outputResolutionY;	/* Y方向の出力解像度 */
	WORD inputResolutionX;	/* X方向の入力解像度 */
	WORD inputResolutionY;	/* Y方向の入力解像度 */
	WORD imageResolutionX;	/* X方向のイメージ蓄積解像度 */
	WORD imageResolutionY;	/* Y方向のイメージ蓄積解像度 */
	WORD maxPageSizeX;		/* X方向の最大ページサイズ */
	WORD maxPageSizeY;		/* Y方向の最大ページサイズ */
	char directoryPath[HB_SPLMAXFILENAME];	/* テンポラリファイルを作成するディレクトリのフルパス名 */
	WORD plex;				/* 両面印刷指定(HB_PLEX_XXXX参照) */
} HB_JobParam;

/*
 * Spoolパラメータ
 */
typedef struct HB_SpoolParamT {
	DWORD	size;			/* 構造体のサイズ */
	DWORD	jobHandle;						/* ジョブを識別するハンドル */
	char	splFileName[HB_SPLMAXFILENAME];	/* SpoolOutモジュールのファイル名(パス含む) */
	char	localFileName[HB_SPLMAXFILENAME];	/* SpoolOutではなく，ローカルファイルに出力する際のファイル名	*/
	WORD	localFileNoTruncate;			/* ローカルファイルOpen時に　0：内容破棄，1：内容保存	*/
	long	localFileOffset;				/* ローカルファイルOpen時の書き出し位置の指定			*/
	WORD	localFileOrigin;				/* ローカルファイルOpen時の書き出し基準位置の指定		*/
} HB_SpoolParam;

/*
 * 出力パラメータ
 */
#define	HB_ES_FILTERMAX		16

typedef enum HB_ColorModeT
{
	HB_ColorMode_UseStartPage	= 0,
	HB_ColorMode_BW,
	HB_ColorMode_Color
} HB_ColorMode;

typedef struct HB_OutputParamT {
	DWORD	size;		/* 構造体のサイズ	*/

	/* ジョブの出力モード指定	*/
	DWORD	colorMode;	/*  0:StartPage ColorMode優先
						 *  1:B/W固定
						 *  2:Color固定
						 */

	/* colorModeに応じて下記の動作モードが選択される		*/
	/* colorMode==0 && StartPage(白黒)	: rndBwxxx, esBwxxx	*/
	/* colorMode==0 && StartPage(カラー): rndClxxx, esClxxx	*/
	/* colorMode==1                     : rndBwxxx, esBwxxx	*/
	/* colorMode==2                     : rndClxxx, esClxxx	*/
	
	/* Rendererの動作モード指定	*/
	DWORD	rndBwColor;	/* B/W   Page : Color Space					*/
	DWORD	rndBwBytes;	/* B/W   Page : 1コンポーネントのバイト数	*/
	DWORD	rndBwOption;/* B/W   Page : パディング形式				*/
	DWORD	rndBwOrder;	/* B/W   Page : コンポーネントの並び		*/

	DWORD	rndClColor;	/* Color Page : Color Space					*/
	DWORD	rndClBytes;	/* Color Page : 1コンポーネントのバイト数	*/
	DWORD	rndClOption;/* Color Page : パディング形式				*/
	DWORD	rndClOrder;	/* Color Page : コンポーネントの並び		*/
	

	/* 最終出力形式指定			*/
	DWORD	esBwDepth;	/* B/W   Page : bit / component				*/
	DWORD	esBwTag;	/* B/W   Page : IOTタグ形式					*/
	DWORD	esBwColor;	/* B/W   Page : Color Space					*/
	DWORD	esBwBytes;	/* B/W   Page : 1コンポーネントのバイト数	*/
	DWORD	esBwOption;	/* B/W   Page : パディング形式				*/
	DWORD	esBwOrder;	/* B/W   Page : コンポーネントの並び		*/

	DWORD	esClDepth;	/* B/W   Page : bit / component				*/
	DWORD	esClTag;	/* Color Page : IOTタグ形式					*/
	DWORD	esClColor;	/* Color Page : Color Space					*/
	DWORD	esClBytes;	/* Color Page : 1コンポーネントのバイト数	*/
	DWORD	esClOption;	/* Color Page : パディング形式				*/
	DWORD	esClOrder;	/* Color Page : コンポーネントの並び		*/
	
	
	/* EdgeSinkの動作モード指定	*/
	DWORD	format;					/* ES_FormatterType参照		*/
	DWORD	fmtArg;					/* Formatter 初期化引数		*/

	DWORD	filter[HB_ES_FILTERMAX];/* ES_FilterType参照		*/
	DWORD	fltArg[HB_ES_FILTERMAX];/* Filter 初期化引数		*/

	DWORD	compress;				/* ES_CodecType参照			*/
	DWORD	compArg;				/* Codec 初期化引数			*/

	DWORD	formatMode;				/* Formatterの書式を指定する	*/
									/* Formatterがサポートする場合	*/
									/* 0：Jobで単一のHeader/Trailer					*/
									/* 1：Page毎にHeader/Trailer(Page独立ファイル)	*/

	/* 各初期化引数, IOTタグについては，それぞれの仕様書を参照	*/

} HB_OutputParam;


/*
 * デバッグ情報指示
 */
typedef struct HB_DebugInfoT {
	DWORD	size;							/* 構造体のサイズ									*/
	char	logFileName[HB_SPLMAXFILENAME];	/* デバッグ情報ログファイル名(パス名含む)			*/
	DWORD	logLevel;						/* 0：何も出力しない								*/
											/* 1：Level1のログ(情報量小)を出力する				*/
											/* -												*/
											/* 9：Level9のログ(情報量大)を出力する				*/
											/* 0x7FFFFFFF：オフラインデバッグ用データを出力する	*/
} HB_DebugInfo;


/*
 * ページパラメータ
 */
typedef struct HB_PageParamT {
	DWORD			size;			/* 構造体のサイズ */
	WORD			colorMode;		/* カラーモード */
	WORD			x;				/* 有効印字エリアのX方向のサイズ（単位はピクセル）*/
	WORD			y;				/* 有効印字エリアのY方向のサイズ（単位はピクセル）*/
	WORD			rotation;		/* ページ回転指示(HB_PAGE_ROTATION_XXXX参照) */
	float			fWindowX;		/* FXPS追加分。PrinterDriverでCTM計算に使用 */
	float			fWindowY;		/* FXPS追加分。PrinterDriverでCTM計算に使用 */
} HB_PageParam;

/*
 * ViewBufferのパラメータ
 */
typedef struct HB_ViewBufferParamT {
	DWORD			size;
	unsigned char	*pageBuffer;	/* ページバッファ */
	long			lineSize;		/* １ラインのドット数 */
	long			depth;			/* 色の深さ */
	void			*DC;			/* DDBのコンテキスト */
} HB_ViewBufferParam;


/*
 * 使用メモリサイズの取得
 */
HB_EXPORT int HB_STDCALL HB_GetMemSize(
	WORD resolutionX,		/* X方向の解像度 */
	WORD resolutionY,		/* Y方向の解像度 */
	DWORD *dlSize,			/* 中間データの保存用とワーク用に必要なメモリサイズ */
	DWORD *rbSize);			/* レンダリングに必要なメモリサイズ */

/*
 * 初期化と終了
 */
HB_EXPORT void* HB_STDCALL HB_Initialize(
	void *jobParam,			/* ジョブパラメータ HB_JobParam参照		*/
	void *spoolParam,		/* スプールパラメータ HB_SpoolParam参照 */
	void *outputParameter,	/* 出力パラメータ情報 HB_OutputParam参照 */
	void *cstParameter,		/* 色変換パラメータ						*/
	void *debugInfo,		/* デバッグ情報指示 HB_DebugInfo参照	*/
	void *extraParam);		/* 適用先固有のパラメータ SIFで消費すること	*/


HB_EXPORT int HB_STDCALL HB_Finalize(
	void *decomposer);		/* Decomposerのハンドル */

/* Error発生時の終了処理 AR1563 */
HB_EXPORT int HB_STDCALL HB_ErrorFinalize(
	void *decomposer);		/* Decomposerのハンドル */

/*
 * ジョブ制御
 */
HB_EXPORT int HB_STDCALL HB_StartJob(
	void *decomposer,		/* Decomposerのハンドル */
	WORD patternMode);		/* パターンデータの変換パラメータ */

HB_EXPORT int HB_STDCALL HB_EndJob(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_StartPage(
	void *decomposer,		/* Decomposerのハンドル */
	void *pageParam,		/* ページパラメータ HB_PageParam参照 */
	void *spoolParam,		/* ページ単位でのスプールパラメータ HB_SpoolParam参照	*/
	void *extraParam);		/* 適用先固有のパラメータ HB_ViewBufferParam等 */

HB_EXPORT int HB_STDCALL HB_EndPage(
	void *decomposer,		/* Decomposerのハンドル */
	void *extraParam);		/* 適用先固有のパラメータ */


/*
 * デバイス管理
 */
HB_EXPORT int HB_STDCALL HB_ShowPage(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_SetPatternResolution(
	void *decomposer,		/* Decomposerのハンドル */
	WORD resolution);		/* パターンデータ解像度(単位: dpi) */

HB_EXPORT int HB_STDCALL HB_SetColorParameter(
	void* imager,			/* Decomposerのハンドル */
	void* colorParameter);	/* 色変換パラメータ */

HB_EXPORT int HB_STDCALL HB_SetRasterSmoothingMode (
	void* imager,			/* Decomposerのハンドル */
	WORD mode,				/* イメージ縮小時の補完処理モード */
	WORD quality);			/* イメージ品質 */

HB_EXPORT int HB_STDCALL HB_SetMaskSmoothingMode(
	void* imager,			/* Decomposerのハンドル */
	WORD mode,				/* イメージマスク縮小時の補完処理モード */
	WORD quality);			/* イメージマスク品質 */

/*
 * 描画属性設定
 */
HB_EXPORT int HB_STDCALL HB_SetAxis(
	void *decomposer,		/* Decomposerのハンドル */
	HB_FLOAT a, HB_FLOAT b,		/* 変換行列のa,b成分 */
	HB_FLOAT c, HB_FLOAT d,		/* 変換行列のc,d成分 */
	HB_FLOAT tx, HB_FLOAT ty);	/* 変換行列のtx,ty成分 */

HB_EXPORT int HB_STDCALL HB_SetLineWidth(
	void *decomposer,		/* Decomposerのハンドル */
	HB_FLOAT width);			/* 線幅 */

HB_EXPORT int HB_STDCALL HB_SetLineCap(
	void *decomposer,		/* Decomposerのハンドル */
	WORD cap);				/* キャップ種類 */

HB_EXPORT int HB_STDCALL HB_SetLineJoin(
	void *decomposer,		/* Decomposerのハンドル */
	WORD join);				/* ジョイン種類 */

HB_EXPORT int HB_STDCALL HB_SetMiterLimit(
	void *decomposer,		/* Decomposerのハンドル */
	HB_FLOAT miterLimit);		/* マイター長 */

HB_EXPORT int HB_STDCALL HB_SetLineType(
	void *decomposer,		/* Decomposerのハンドル */
	WORD lineStyle,			/* 線スタイル */
	HB_FLOAT offset,			/* 任意形状スタートオフセット */
	WORD count,				/* 任意形状マスクデータ個数 */
	HB_FLOAT *data);		/* 任意形状マスクデータ列へのポインタ */

HB_EXPORT int HB_STDCALL HB_AdjustStroke(
	void *decomposer,		/* Decomposerのハンドル */
	BOOL strokeMode);		/* Stroke調整の有無 */

HB_EXPORT int HB_STDCALL HB_SetFillMode(
	void *decomposer,		/* Decomposerのハンドル */
	WORD fillMode);			/* 塗りつぶし規則 */

HB_EXPORT int HB_STDCALL HB_SetDrawMode(
	void *decomposer,		/* Decomposerのハンドル */
	WORD drawMode);			/* 描画方式 */

HB_EXPORT int HB_STDCALL HB_SetRopMode(
	void *decomposer,		/* Decomposerのハンドル */
	WORD ropMode,			/* ROPモード */
	DWORD ropNumber);		/* ROPコード */

HB_EXPORT int HB_STDCALL HB_SetGraphicsMode(
	void *decomposer,		/* Decomposerのハンドル */
	WORD fill,				/* 面積０の閉領域の塗り潰し除外指定 */
	WORD line);				/* 細線強調描画の指定 */

/*
 * 描画色設定
 */
HB_EXPORT int HB_STDCALL HB_SetSolidColor(
	void *decomposer,		/* Decomposerのハンドル */
	WORD drawMethod,		/* 適用する描画方式 */
	WORD colorSpace,		/* 色空間 */
	char *data);			/* 色値 */

HB_EXPORT int HB_STDCALL HB_SetHatchPattern(
	void *decomposer,		/* Decomposerのハンドル */
	POINT *startPoint,		/* 描画開始点 */
	WORD drawMethod,		/* 指定対象 */
	WORD foregroundColorSpace,		/* 前景色の色空間 */
	WORD backgroundColorSpace,		/* 背景色の色空間 */
	BOOL polality,			/* 極性 */
	char *foregroundColor,	/* 前景色の色データ */
	char *backgroundColor,	/* 背景色の色データ */
	WORD transparency,		/* 透過モード */
	char hatch);			/* ハッチパターン種別 */

HB_EXPORT int HB_STDCALL HB_SetMaskPattern(
	void *decomposer,		/* Decomposerのハンドル */
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

HB_EXPORT int HB_STDCALL HB_SetRasterPattern(
	void *decomposer,		/* Decomposerのハンドル */
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
HB_EXPORT int HB_STDCALL HB_InitClip(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_SetRectangleClip(
	void *decomposer,		/* Decomposerのハンドル */
	WORD  clipMode,			/* クリップの論理演算モード */
	POINT *point1,			/* 対角点座標1 */
	POINT *point2);			/* 対角点座標2 */

HB_EXPORT int HB_STDCALL HB_SetClipRegion(
	void *decomposer,		/* Decomposerのハンドル */
	WORD  clipMode,			/* クリップの論理演算モード */
	WORD  num,				/* 矩形情報の数 */
	HB_FLOAT *data);		/* 矩形情報配列 */

HB_EXPORT int HB_STDCALL HB_ClipPath(
	void *decomposer,		/* Decomposerのハンドル */
	WORD  clipMode);		/* クリップの論理演算モード */

HB_EXPORT int HB_STDCALL HB_OffsetClip(
	void *decomposer,		/* Decomposerのハンドル */
	HB_FLOAT xOffset,			/* x軸方向のオフセット */
	HB_FLOAT yOffset);			/* y軸方向のオフセット */

HB_EXPORT int HB_STDCALL HB_SaveClip(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_RestoreClip(
	void *decomposer);		/* Decomposerのハンドル */

/*
 * パス操作
 */
HB_EXPORT int HB_STDCALL HB_InitPath(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_ClosePath(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_MovePoint(
	void *decomposer,		/* Decomposerのハンドル */
	HB_FLOAT x, HB_FLOAT y);		/* 移動先座標 */

HB_EXPORT int HB_STDCALL HB_DrawPath(
	void *decomposer);		/* Decomposerのハンドル */

HB_EXPORT int HB_STDCALL HB_AddLinePath(
	void *decomposer,	/* Decomposerのハンドル */
	WORD num,		/* 線分数 */
	HB_REAL32 *data);	/* num個の折点座標(x,y)へのポインタ */

HB_EXPORT int HB_STDCALL HB_AddEllipseArcPath(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_AddEllipseChordPath(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_AddEllipsePiePath(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_AddBezierPath(
	void *decomposer,	/* Decomposerのハンドル */
	WORD num,			/* 曲線数 */
	HB_FLOAT *data);	/* num個のBezier曲線情報へのポインタ */

HB_EXPORT int HB_STDCALL HB_AddRectanglePath(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x2,			/* 対角点2のx座標 */
	HB_FLOAT y2);			/* 対角点2のy座標 */

HB_EXPORT int HB_STDCALL HB_AddRoundRectanglePath(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x1,			/* 対角点1のx座標 */
	HB_FLOAT y1,			/* 対角点1のy座標 */
	HB_FLOAT x2,			/* 対角点2のx座標 */
	HB_FLOAT y2,			/* 対角点2のy座標 */
	HB_FLOAT rx,			/* 角丸の外接矩形の水平半径 */
	HB_FLOAT ry);			/* 角丸の外接矩形の垂直半径 */

/*
 * 直接描画
 */
HB_EXPORT int HB_STDCALL HB_DrawLine(
	void *decomposer,		/* Decomposerのハンドル */
	WORD num,				/* 線分数 */
	void *data);			/* num+1個の折点座標へのポインタ */

HB_EXPORT int HB_STDCALL HB_DrawScanline(
	void *decomposer,		/* Decomposerのハンドル */
	WORD num,				/* スキャンライン数 */
	void *startPoints,		/* num個のスキャンライン始点座標へのポインタ */
	WORD *lengths);			/* num個の各スキャンラインのx方向の長さへのポインタ */

HB_EXPORT int HB_STDCALL HB_DrawRectangle(
	void *decomposer,		/* Decomposerのハンドル */
	HB_REAL32 x1, HB_REAL32 y1,	/* 対角点1の座標 */
	HB_REAL32 x2, HB_REAL32 y2,	/* 対角点2の座標 */
	WORD drawRightBottom);	/* 矩形の右端と下端を描画するかどうか */

HB_EXPORT int HB_STDCALL HB_DrawRectangleSet(
	void		*decomposer,/* Decomposerのハンドル */
	WORD		nrect,		/* 矩形の総数 */
	WORD		blocks,		/* ブロック数 */
	HB_REAL32	startY,		/* 最初の矩形の左上点のY座標 */
	WORD		*lines,		/* ライン数の配列 */
	WORD		*colums,	/* 列数の配列 */
	HB_REAL32	*heights,	/* 矩形高さの配列 */
	HB_REAL32	*x,			/* 描画開始点のX座標 */
	HB_REAL32	*width);	/* 矩形の幅 */

HB_EXPORT int HB_STDCALL HB_DrawEllipseArc (
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_DrawEllipseChord(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_DrawEllipsePie(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT rx,			/* 水平半径 */
	HB_FLOAT ry,			/* 垂直半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_DrawCircleArc(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT r,			/* 半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_DrawCirclePie(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x,			/* 中心点x座標 */
	HB_FLOAT y,			/* 中心点y座標 */
	HB_FLOAT r,			/* 半径 */
	HB_FLOAT sangle,		/* 始点角度 */
	HB_FLOAT eangle);		/* 終点角度 */

HB_EXPORT int HB_STDCALL HB_DrawBezier(
	void *decomposer,	/* Decomposerのハンドル */
	WORD num,			/* 曲線数 */
	HB_FLOAT sx,			/* 始点x */
	HB_FLOAT sy,			/* 始点y */
	HB_FLOAT *data);	/* num個のBezier曲線情報へのポインタ */

HB_EXPORT int HB_STDCALL HB_DrawRoundRectangle(
	void *decomposer,	/* Decomposerのハンドル */
	HB_FLOAT x1,			/* 対角点1のx座標 */
	HB_FLOAT y1,			/* 対角点1のy座標 */
	HB_FLOAT x2,			/* 対角点2のx座標 */
	HB_FLOAT y2,			/* 対角点2のy座標 */
	HB_FLOAT rx,			/* 角丸の外接矩形の水平半径 */
	HB_FLOAT ry);			/* 角丸の外接矩形の垂直半径 */

/*
 * イメージマスク描画
 */
HB_EXPORT int HB_STDCALL HB_DrawImageMask(
	void *decomposer,		/* Decomposerのハンドル */
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
HB_EXPORT int HB_STDCALL HB_DrawImage (
	void *decomposer,		/* Decomposerのハンドル */
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
HB_EXPORT int HB_STDCALL HB_DrawFont(
	void *decomposer,		/* Decomposerのハンドル */
	POINT *startPoint,		/* 描画開始点座標 */
	char *address);			/* ラスタフォントデータへのポインタ */

#ifndef HB_FM_NODEFINE

HB_EXPORT int HB_STDCALL HB_SetLogFont(
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

HB_EXPORT int HB_STDCALL HB_DrawCodeFont(
				 void 			*imager, 
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

HB_EXPORT int HB_STDCALL HB_DrawDataFont(
				 void 			*imager, 
				 HB_FLOAT			x,
				 HB_FLOAT			y,
				 DWORD			cacheKey,
				 char			*dataPtr
				 );

HB_EXPORT int HB_STDCALL HB_StartFontRegister(
				 void 			*imager 
				 );

HB_EXPORT int HB_STDCALL HB_EndFontRegister(
				 void 			*imager 
				 );

HB_EXPORT int HB_STDCALL HB_GetFontRegister(
				 void 			*imager ,
				 char 			**dataAddress ,
				 int 			*numOfChar
				 );

#endif

/*
 * 制御系I/F
 */
HB_EXPORT int HB_STDCALL HB_SendJobHeader(
	void *decomposer,		/* Decomposerのハンドル */
	void *jobHeader);		/* ESS ジョブヘッダ情報。ESS_Parameter_JOBHEADER参照 */

HB_EXPORT int HB_STDCALL HB_SendJobTrailer(
	void *decomposer,		/* Decomposerのハンドル */
	void *jobTrailer);		/* ESS ジョブトレイラ-情報 ESS_Parameter_JOBTRAILER参照 */

#endif /* INC_HB_Decomposer_h */

/*
 * Log
 * 14.Jul.2003 Yozo Kashima Created
 * 12.Sep.2003 Yozo Kashima HB_DrawRectangleの引数をPrinter/Viewerで統一。
 *							HB_SpoolParamのパス名を256→260(Windowsでのパス名の最大値)に変更。
 *							HB_SpoolParamにsizeメンバを追加。
 * 23.Sep.2003 Yozo Kashima HB_DrawRectangleのI/FをDriver/Viewerで統一。
 *							HB_StartPageにextraParam引数を追加。
 *							HB_JobParamTからdlAddress{1,2},rbAddressを削除。
 * 10.Aug.2004 Yozo Kashima HB_SetMaskSmoothingModeを追加(DW-V6.0 MRC対応)。
 */

/* end of HB_Decomposer.h */
