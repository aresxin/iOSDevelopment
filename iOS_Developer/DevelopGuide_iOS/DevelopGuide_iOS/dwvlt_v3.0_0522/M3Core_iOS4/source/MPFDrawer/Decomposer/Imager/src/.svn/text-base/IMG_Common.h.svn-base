/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Common.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_Common_h
#define INC_IMG_Common_h

#include <math.h>
#include <memory.h>
#include "IMG_Builtin.h"

#include "COM_DeviceColorSpace.h"
#include "COM_OutputLocation.h"

/*
 * 各種設定値
 */
#define IMG_MAX_SAVE_LEVEL	31
#define IMG_MAX_PAGE_WIDTH     11.6929       /* A3 width  (inch) */
#define IMG_MAX_PAGE_HEIGHT    16.5354       /* A3 height (inch) */

#define IMG_FLOATING_ERROR	0.0001


/*
 * ハーフスキャンコンバージョン用マクロ
 */
#define IMG_HSCONV_DBL_X(x)		( (IMG_REAL64)(x) + 0.5 )
#define IMG_HSCONV_DBL_Y(y)		( (IMG_REAL64)(y) + 0.5 )

#if !defined(HB_WINDRAW_ADJUST)
#define IMG_HSCONV_INT32_X(x)	( (IMG_INT32) IMG_HSCONV_DBL_X(x) )
#define IMG_HSCONV_INT32_Y(y)	( (IMG_INT32) IMG_HSCONV_DBL_Y(y) )
#else
#define IMG_HSCONV_INT32_X(x)	( (IMG_INT32)((IMG_REAL32)IMG_HSCONV_DBL_X(x)) )
#define IMG_HSCONV_INT32_Y(y)	( (IMG_INT32)((IMG_REAL32)IMG_HSCONV_DBL_Y(y)) )
#endif

 /*
 * 列挙型
 */
typedef enum img_objecttag {
	IMG_TAG_NULL,				/* 未定義 */
	IMG_TAG_GRAPHIC,			/* 描画オブジェクトがグラフィックであることを示すタグ値 */
	IMG_TAG_FONT,				/* 描画オブジェクトがフォントであることを示すタグ値 */
	IMG_TAG_IMAGE,				/* 描画オブジェクトがイメージであることを示すタグ値 */
	IMG_TAG_GRAPHIC_WIDE,		/* 広い領域をソリッドカラーで塗られたグラフィック */
	IMG_TAG_GRAPHIC_THIN,		/* 細線 */
	IMG_TAG_GRAPHIC_PATTERN,	/* パターンで描画されたグラフィック */
	IMG_TAG_GRAPHIC_GRADATION,	/* グラデーション */
	IMG_TAG_GRAPHIC_RECTSET     /* WMFの矩形集合 */
} IMG_ObjectTag;

typedef enum img_drawmode {
	IMG_DRAW_FILL,				/* 塗りつぶし描画 */
	IMG_DRAW_STROKE,			/* 線描画 */
	IMG_DRAW_FILL_AND_STROKE,	/* NotUsed */
} IMG_DrawMode;

typedef enum img_fillrule {
	IMG_FILL_EVEN_ODD,				/* EvenOdd Fill */
	IMG_FILL_NON_ZERO_WINDING,		/* NonZeroWinding　Fill */
} IMG_FillRule;

typedef enum img_capstyle {
	IMG_CAP_BUTT,			/* バットキャップ */
	IMG_CAP_ROUND,			/* ラウンドキャップ */
	IMG_CAP_SQUARE,			/* スクエアキャップ */
} IMG_CapStyle;

typedef enum img_joinstyle {
	IMG_JOIN_MITER,			/* マイタージョイン */
	IMG_JOIN_ROUND,			/* ラウンドジョイン */
	IMG_JOIN_BEVEL,			/* べベルジョイン */
} IMG_JoinStyle;

typedef enum img_linestyle {
	IMG_LINE_SOLID1,		/* 実線1(WindowsのINSIDEFRAME) */
	IMG_LINE_SOLID2,		/* 実線2 */
	IMG_LINE_DASH,			/* 破線 */
	IMG_LINE_DOT,			/* 点線 */
	IMG_LINE_DASHDOT,		/* 一点破線 */
	IMG_LINE_DASHDOTDOT,	/* 二点破線 */
	IMG_LINE_ANY,			/* 任意形状 */
} IMG_LineStyle;

typedef enum img_colormode {
	IMG_COLOR_MODE,		/* RGBカラーでデータを出力するモード */
	IMG_GRAY_MODE,		/* モノクロでデータを出力するモード */
} IMG_ColorMode;

typedef enum img_colorspace {
	IMG_COLOR_SPACE_BGR,			/* BGR空間 */
	IMG_COLOR_SPACE_GRAY,			/* GRAY空間 */
	IMG_COLOR_SPACE_INDEXED_BGR,	/* Indexed　BGR空間 */
	IMG_COLOR_SPACE_INDEXED_GRAY,	/* Indexed　GRAY空間 */
} IMG_ColorSpace;

typedef enum img_coloInterleave {
	IMG_COLOR_INTERLEAVE_LINE,			/* 線順次 */
	IMG_COLOR_INTERLEAVE_DOT,			/* 点順次 */
} IMG_ColorInterleave;

typedef enum img_patterntype {
	IMG_PATTERN_HATCH,		/* ハッチタイプ */
	IMG_PATTERN_MASK,		/* マスクタイプ */
	IMG_PATTERN_RASTER,		/* ラスターパターン */
} IMG_PatternType;

typedef enum img_patternpolarity {
	IMG_PATTERN_BIT_ON	 = 1,	/* ON(1)のビットに適用 */
	IMG_PATTERN_BIT_OFF	 = 0,	/* OFF(0)のビットに適用 */
	IMG_PATTERN_BIT_NULL = 2,	/* 指定なし */
} IMG_PatternPolarity;

typedef enum img_patterntransparency {
	IMG_PATTERN_TRANSPARENT,	/* 背景透過モード */
	IMG_PATTERN_OPAQUE,			/* 上書きモード */
} IMG_PatternTransparency;

typedef enum img_hatchpatternkind {
	IMG_HATCH_SOLID,		/* ソリッドカラー（ベタ塗り） */
	IMG_HATCH_HORIZONTAL,	/* 水平 */
	IMG_HATCH_VERTICAL,		/* 垂直 */
	IMG_HATCH_FDIAGONAL,	/* 45度右上がり */
	IMG_HATCH_BDIAGONAL,	/* 45度右下がり */
	IMG_HATCH_CROSS,		/* 水平垂直クロス */
	IMG_HATCH_DIAGCROSS,	/* 45度クロス */
} IMG_HatchPatternKind;

typedef enum img_ropmode {
	IMG_ROP2,	/* ROP2を示す */
	IMG_ROP3,	/* ROP3を示す */
} IMG_RopMode;

typedef enum img_storemethod {
	IMG_STORE_METHOD_FILE,		/* ファイルに格納する */
	IMG_STORE_METHOD_MEMORY,	/* メモリに格納する */
} IMG_StoreMethod;

typedef enum img_imagetype {
	IMG_IMAGE_TYPE_24BPP		= 0,
	IMG_IMAGE_TYPE_INDEX_1BPP	= 1,
	IMG_IMAGE_TYPE_INDEX_8BPP	= 2,
} IMG_ImageType;

/*
 * Arc(弧)の描画モード
 */
typedef enum img_arcdrawmode {
	IMG_ARC_DRAW_ARC,		/* 弧だけを描画する */
	IMG_ARC_DRAW_CHORD,		/* 弓形を描画する */
	IMG_ARC_DRAW_PIE,		/* パイを描画する */
} IMG_ArcDrawMode;

/*
 * クリップの論理演算モード
 */
typedef enum img_clipropmode {
	IMG_CLIP_ROP_MODE_AND	= 1,
	IMG_CLIP_ROP_MODE_COPY	= 2,
	IMG_CLIP_ROP_MODE_DIFF	= 3,
	IMG_CLIP_ROP_MODE_OR	= 4,
	IMG_CLIP_ROP_MODE_XOR	= 5,
} IMG_ClipRopMode;

/*
 * 構造体
 */
typedef union img_colordata {
	struct bgr {
		IMG_UINT8	blue;		/* Blueの色値 */
		IMG_UINT8	green;		/* Greenの色値 */
		IMG_UINT8	red;		/* Redの色値 */
	} bgr;
	IMG_UINT8	gray;
} IMG_ColorData;

/*	Mask構造体
	HatchBrush,PatternBrush,MaskImage,Imageで使用する */
typedef struct img_mask {
	IMG_UINT16			width;
	IMG_UINT16			widthBytes;
	IMG_UINT16			height;
	IMG_PatternPolarity	polarity;
	IMG_UINT32			dataSize;
	char				*dataAddress;
	IMG_BOOL	dataMallocFlg;
} IMG_Mask,*IMG_MaskPointer;


/*
 * 以下はIMG_DisplayListに設定するための構造体を集めたもの
 * 共通で使うことがなければIMG_DisplayList.hに移す方がよい。
 */
typedef struct img_point {
	IMG_REAL32		x;		/* 点のX座標値 */
	IMG_REAL32		y;		/* 点のY座標値 */
} IMG_Point;

typedef struct img_point16 {
	IMG_INT16 x;
	IMG_INT16 y;
}IMG_Point16;

typedef struct img_edgedata {
	IMG_INT32	y;		/* エッジのY座標値 */
	IMG_REAL32	sx;		/* エッジの始点Ｘ座標値 */
	IMG_REAL32	ex;		/* エッジの終点Ｘ座標値 */
} IMG_EdgeData;

typedef struct img_vedgedata {
	IMG_INT32	x;		/* エッジのX座標値 */
	IMG_REAL32	sy;		/* エッジの始点Y座標値 */
	IMG_REAL32	ey;		/* エッジの終点Y座標値 */
} IMG_VEdgeData;

typedef struct img_rectangledata {
	IMG_INT32	ly;		/* 矩形の原点から最近点のY座標値 */
	IMG_INT32	uy;		/* 矩形の原点から最遠点のY座標値 */
	IMG_REAL32	lx;		/* 矩形の原点から最近点のX座標値 */
	IMG_REAL32	ux;		/* 矩形の原点から最遠点のX座標値 */
} IMG_RectangleData;

typedef struct img_trapezoiddata {
	IMG_INT32	ly;			/* 台形の下底辺のY座標 */
	IMG_INT32	uy;			/* 台形の上底辺のY座標 */
	IMG_REAL32	lx;			/* 台形の底辺のX始点座標 */
	IMG_REAL32	rx;			/* 台形の底辺のX終点座標 */
	IMG_SHOULDBE_DOUBLE	lslant;		/* 台形の右斜辺の傾き */
	IMG_SHOULDBE_DOUBLE	rslant;		/* 台形の左斜辺の傾き */
} IMG_TrapezoidData;

typedef struct img_linedata {
	IMG_REAL32	sx; 		/* 直線始点X座標 */
	IMG_REAL32	sy; 		/* 直線始点Y座標 */
	IMG_REAL32	ex; 		/* 直線終点X座標 */
	IMG_REAL32	ey; 		/* 直線終点Y座標 */
} IMG_LineData;

typedef struct img_bitmapdata {
	IMG_INT32	offsetx; 	/* オフセットX座標 */
	IMG_INT32	offsety; 	/* オフセットY座標 */
	IMG_UINT32	sw;			/* 拡大前の幅 */
	IMG_UINT32	sh;			/* 拡大前の高さ */
	IMG_UINT32	dw;			/* 拡大後の幅 */
	IMG_UINT32	dh;			/* 拡大後の幅 */
	IMG_UINT8	*buffer;	/* データ格納用バッファアドレス */
	IMG_UINT32	size;		/* データ格納用バッファサイズ */
	IMG_BOOL	polarity;	/* 極性 */
} IMG_BitmapData;

typedef struct img_bitmapfontdata {
	IMG_INT32	offsetx; 	/* オフセットX座標 */
	IMG_INT32	offsety; 	/* オフセットY座標 */
	IMG_UINT32	width;		/* フォントの幅 */
	IMG_UINT32	height;		/* フォントの高さ */
	IMG_UINT8	*buffer;	/* データ格納用バッファアドレス */
	IMG_UINT32	size;		/* データ格納用バッファサイズ */
	IMG_BOOL	polarity;	/* 極性 */
} IMG_BitmapFontData;

typedef struct { 
	IMG_INT32		offsetx; 	/* 拡大後のオフセットX座標	呼び出し側設定 */
	IMG_INT32		offsety; 	/* 拡大後のオフセットY座標	呼び出し側設定 */
	IMG_UINT16		dw; 		/* 拡大後の幅				呼び出し側設定 */
	IMG_UINT16		dh; 		/* 拡大後の高さ				呼び出し側設定 */
	IMG_UINT32		sw;			/* 拡大前の幅				呼び出し側設定 */
	IMG_UINT32		sh;			/* 拡大前の高さ				呼び出し側設定 */
	IMG_ImageType	type;		/* データ形式				呼び出し側設定 */
	IMG_BOOL		smoothing;	/* 拡大情報					呼び出し側設定 */
	IMG_StoreMethod	mode;		/* 格納方式指定				受け取り側設定 */
	IMG_UINT8		*buffer;	/* 格納先バッファアドレス	受け取り側設定 */
	void			*file;		/* 格納先ファイルアドレス	受け取り側設定 */
} IMG_ImageData;

typedef struct img_patterndata {
	IMG_INT32	offsetx;		/* 基準パターンオフセットＸ座標 */
	IMG_INT32	offsety;		/* 基準パターンオフセットＹ座標 */
	IMG_UINT16	width;			/* 基準パターン幅 */
	IMG_UINT16	height;			/* 基準パターン高さ */
	IMG_INT8	*buffer;		/* データ格納用バッファアドレス */
	IMG_UINT32	size;			/* データ格納用バッファサイズ */
	IMG_PatternType	type;		/* パターンタイプ */
	IMG_PatternTransparency	transparency;		/* 極性 */
	IMG_ColorData fgcolor;		/* 前景色値 */
	IMG_ColorData bgcolor;		/* 背景色値 */
	IMG_UINT32	id;				/* パターンデータを識別するユニークなID */
} IMG_PatternData;

typedef struct { 
	IMG_INT32		offsetx; 	/* 拡大後のオフセットX座標	呼び出し側設定 */
	IMG_INT32		offsety; 	/* 拡大後のオフセットY座標	呼び出し側設定 */
	IMG_UINT16		dw; 		/* 拡大後の幅				呼び出し側設定 */
	IMG_UINT16		dh; 		/* 拡大後の高さ				呼び出し側設定 */
	IMG_UINT32		sw;			/* 拡大前の幅				呼び出し側設定 */
	IMG_UINT32		sh;			/* 拡大前の高さ				呼び出し側設定 */
	IMG_StoreMethod	mode;		/* 格納方式指定				受け取り側設定 */
	IMG_UINT8		*buffer;	/* 格納先バッファアドレス	受け取り側設定 */
	void			*file;		/* 格納先ファイルアドレス	受け取り側設定 */
} IMG_GrayMaskData;

/*
 * 以下，IMG_Common.hで定義されているIMG_Point
 * 用のベクトル演算関数
 * 
 * 定義は次の通り

typedef struct img_point {
	float		x;	点のX座標値
	float		y;	点のY座標値
} IMG_Point;

 */

void IMG_Point_CalcSubtract( IMG_Point *, IMG_Point * );
void IMG_Point_CalcAddition( IMG_Point *, IMG_Point * );
IMG_REAL64 IMG_Point_CalcLength( IMG_Point * );
void IMG_Point_CalcScale( IMG_Point *, IMG_REAL32 );
IMG_REAL32 IMG_Point_CalcInnerProduct( IMG_Point *, IMG_Point * );

void IMG_Point_Trans_UnitVector( IMG_Point * );
void IMG_Point_Trans_45( IMG_Point * );
void IMG_Point_Trans_135( IMG_Point * );
void IMG_Point_Trans_90( IMG_Point * );
void IMG_Point_Trans_180( IMG_Point * );
void IMG_Point_Trans_45_90_180( IMG_Point * );

int IMG_ProcLineCrossPoint(IMG_FLOAT p1x, IMG_FLOAT p1y,
						   IMG_FLOAT p2x, IMG_FLOAT p2y,
						   IMG_FLOAT q1x, IMG_FLOAT q1y,
						   IMG_FLOAT q2x, IMG_FLOAT q2y,
						   IMG_REAL32 *px, IMG_REAL32 *py );

#ifndef IMG_FM_NODEFINE
/***************************************************/
/********* For Font Drawing (FontManager) **********/
/***************************************************/

/* PageInfo */
typedef struct {
  void			*DC;
  long			height;
  long			width;
  long			widthBytes;
  unsigned char*	buffer;
} IMG_FM_PageInfo;

/* Encoding */
typedef enum {
  IMG_FM_ENCODE_ANSI	= 1,
  IMG_FM_ENCODE_UNICODE	= 2,
  IMG_FM_ENCODE_SJIS	= 3,
  IMG_FM_ENCODE_SYMBOL	= 4,
  IMG_FM_ENCODE_HANGEUL	= 5,
  IMG_FM_ENCODE_JOHAB	= 6,
  IMG_FM_ENCODE_GB2312	= 7,
  IMG_FM_ENCODE_CHINESEBIG5= 8
} IMG_FM_Encoding;

/* LogFont */
typedef struct {
  int 			lfHeight;
  int 			lfWidth;
  int 			lfEscapement;
  int 			lfOrientation;
  int 			lfWeight;
  unsigned char 	lfItalic;
  unsigned char 	lfUnderline;
  unsigned char 	lfStrikeOut;
  unsigned char 	lfCharSet;
  unsigned char 	lfOutPrecision;
  unsigned char 	lfClipPrecision;
  unsigned char 	lfQuality;
  unsigned char 	lfPitchAndFamily;
  unsigned char 	lfFaceNameSize;
  unsigned char		lfFaceName[64];
  IMG_FM_Encoding 	lfFaceNameEncoding;
  unsigned char 	lfEmulation;
  unsigned char 	lfPhysicalCharSet;
} IMG_FM_LogFont;
/* Defineded By Win-API without fmFaceNameStringEncode. */

/* Matrix */
typedef struct {
  IMG_DOUBLE			a;   /* | a     b | */
  IMG_DOUBLE			b;   /* |         | */
  IMG_DOUBLE			c;   /* | c     d | */
  IMG_DOUBLE			d;   /* |         | */
  IMG_DOUBLE			tx;  /* | tx   ty | */
  IMG_DOUBLE			ty;  /* |         | */
} IMG_FM_Matrix;

/* Point */
typedef struct {
  IMG_DOUBLE			x;
  IMG_DOUBLE			y;
} IMG_FM_Point;

/* Rect */
typedef struct {
  IMG_DOUBLE			lx;
  IMG_DOUBLE			ly;
  IMG_DOUBLE			ux;
  IMG_DOUBLE			uy;
} IMG_FM_Rect;

/* PitchMode */
typedef enum {
  IMG_FM_PITCH_MODE_ABS = 1,
  IMG_FM_PITCH_MODE_REL = 2,
  IMG_FM_PITCH_MODE_ADD = 3
} IMG_FM_PitchMode;

/* TextAlign */
typedef enum {
    /* 2bit */
    IMG_FM_TEXT_ALIGN_V_NOT		= 0x00,
    IMG_FM_TEXT_ALIGN_V_TOP		= 0x01,
    IMG_FM_TEXT_ALIGN_V_BASELINE    = 0x02,
    IMG_FM_TEXT_ALIGN_V_BOTTOM      = 0x03,
    IMG_FM_TEXT_ALIGN_V_MASK        = 0x03,
    /* 2bit */
    IMG_FM_TEXT_ALIGN_H_NOT         = 0x00,
    IMG_FM_TEXT_ALIGN_H_LEFT        = 0x04,
    IMG_FM_TEXT_ALIGN_H_CENTER      = 0x08,
    IMG_FM_TEXT_ALIGN_H_RIGHT       = 0x0c,
    IMG_FM_TEXT_ALIGN_H_MASK        = 0x0c,
    /* 2bit */
    IMG_FM_TEXT_ALIGN_CP_NOT        = 0x00,
    IMG_FM_TEXT_ALIGN_CP_NOUPDATE   = 0x10,
    IMG_FM_TEXT_ALIGN_CP_UPDATE     = 0x20,
    IMG_FM_TEXT_ALIGN_CP_MASK       = 0x30
} IMG_FM_TextAlign;

/* RectOption */
typedef enum {
  IMG_FM_RECT_OPTION_NO_USE	= 0x00,
  IMG_FM_RECT_OPTION_CLIP	= 0x01,
  IMG_FM_RECT_OPTION_QPAQUE	= 0x02
} IMG_FM_RectOption;

/* ColorMode */
typedef enum {
  IMG_FM_COLOR_MODE_TRANSPARENT	= 1,
  IMG_FM_COLOR_MODE_OPAQUE	= 2
} IMG_FM_ColorMode;

/* String */
typedef struct {
  IMG_FM_PitchMode	 	pitchMode;
  long 					pitchLength;
  IMG_FLOAT*			pitchData;
  long 					codeSize;
  unsigned char* 		codePtr;
  IMG_FM_Encoding	 	codeEncoding;
  IMG_FM_TextAlign		textAlign;
  IMG_FM_ColorMode		bkColorMode;
  unsigned char			bkColor[3];
} IMG_FM_CodeString;

typedef struct {
  unsigned long			cacheKey;
  unsigned char			*dataPtr;
} IMG_FM_DataCharacter;
  
/* Emulation */
typedef enum {
    IMG_FM_EMULATION_NO_USE	= 0x00,
    IMG_FM_EMULATION_BOLD	= 0x01,
    IMG_FM_EMULATION_SPECIAL	= 0x02
} IMG_FM_Emulation;

/***************************************************/
/***************************************************/
#endif

#endif /* INC_IMG_Common_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 16.Apr.2001 Yozo Kashima IMG_PatternDataのpolarityをtransparencyで置き換えた。
 * 17.Apr.2001 Yozo Kashima IMG_STROKE_AND_FILLをIMG_FILL_AND_STROKEに修正。
 * 24.Apr.2001 Toshio Yamazaki IMG_Pointのベクトル演算マクロ&関数を追加
 * 16.Nov.2001 Yozo Kashima IMG_PatternPolarityにNULL値を追加。
 * 21.Feb.2002 Yozo Kashima IMG_ArcDrawModeを追加(曲線対応)。
 * 19.Dec.2002 Yozo Kashima IMG_RopClipModeを追加(CEViewerのクリップの論理演算対応
 * 28.May.2003 Yozo Kashima IMG_MAX_SAVE_LEVELを追加(AR#845)。
 */

/* end of IMG_Common.h */
