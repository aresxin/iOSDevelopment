#ifndef INC_IMG_MaskPatternBrush_h
#define INC_IMG_MaskPatternBrush_h

/* IMG_MaskPatternBrush.h */

#include "IMG_Brush.h"

/* 構造体宣言 */
typedef struct IMG_MaskPatternBrush {
	int				(*destroy)(IMG_Brush *brush);
	int				(*realize)(IMG_Brush *brush,IMG_Matrix *matrix);
	int				(*applyTo)(IMG_Brush *brush,IMG_DisplayList *displayList);
	IMG_UINT8		brushType;
	/* ここまでは共通 */
	IMG_Context					context;		/* Imager用コンテキスト */
	IMG_Point					startPoint;		/* パターン開始座標 */
	IMG_ColorSpace				fgColorSpace;	/* フォアグラウンドカラースペース */
	IMG_ColorSpace				bgColorSpace;	/* バックグラウンドカラースペース */
	IMG_ColorData				fgColor;		/* フォアグラウンドカラー値 */
	IMG_ColorData				bgColor;		/* フォアグラウンドカラー値 */
	IMG_PatternTransparency		transparency;	/* 透過値 */
	IMG_UINT16					patternId;		/* 登録用パターンID */
	IMG_Mask					mask;			/* マスク構造体 */
} IMG_MaskPatternBrush,*IMG_MaskPatternBrushPointer;

typedef struct IMG_MaskPatternBrushParam {
	IMG_Point				startPoint;		/* パターン開始座標 */
	IMG_UINT16				width;			/* パターン幅 */
	IMG_UINT16				height;			/* パターン高さ */
	IMG_UINT32				dataSize;		/* パターンデータバイトサイズ */
	IMG_BOOL				dataMallocFlg;	/* 入力データをIMG_FREEする必要があるかどうか IMG_TRUEなら必要あり */
	IMG_ColorSpace			fgColorSpace;	/* フォアグラウンドカラースペース */
	IMG_ColorSpace			bgColorSpace;	/* バックグラウンドカラースペース */
	IMG_ColorData			fgColor;		/* フォアグラウンドカラー値 */
	IMG_ColorData			bgColor;		/* フォアグラウンドカラー値 */
	IMG_PatternTransparency	transp;			/* 透過値 */
	IMG_PatternPolarity		polarity;		/* マスク極性 */
	IMG_UINT16				patternId;		/* 登録用パターンID */
} IMG_MaskPatternBrushParam,*IMG_MaskPatternBrushParamPointer;

/* 関数プロトタイプ宣言 */
IMG_BrushPointer
	IMG_MaskPatternBrushCreate(IMG_Context *context,
							IMG_MaskPatternBrushParam *maskParam,char *dataAddress);
int
	IMG_MaskPatternBrushSyncFunctionAddress(IMG_Brush *pObject);

#endif /* IMG_MaskPatternBrush_h */
