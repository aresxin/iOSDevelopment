/* IMG_HatchPatternBrush.h */

#ifndef IMG_HatchPatternBrush_h
#define IMG_HatchPatternBrush_h

#include "IMG_Brush.h"

/* 構造体宣言 */
typedef struct IMG_HatchPatternBrush {
	int				(*destroy)(IMG_Brush *brush);
	int				(*realize)(IMG_Brush *brush,IMG_Matrix *matrix);
	int				(*applyTo)(IMG_Brush *brush,IMG_DisplayList *displayList);
	IMG_UINT8		brushType;
	/* ここまでは共通 */
	IMG_Context				context;		/* Imager用コンテキスト */
	IMG_Point				startPoint;		/* パターン開始位置 */
	IMG_ColorSpace			fgColorSpace;	/* フォアグラウンドカラースペース */
	IMG_ColorSpace			bgColorSpace;	/* バックグラウンドカラースペース */
	IMG_ColorData			fgColor;		/* フォアグラウンドカラー値 */
	IMG_ColorData			bgColor;		/* バックグラウンドカラー値 */
	IMG_PatternTransparency	transp;			/* 透過値 */
	IMG_HatchPatternKind	hatch;			/* ハッチ種類 */
	IMG_UINT16				patternId;		/* 登録用パターンID */
	IMG_Mask				mask;			/* マスク構造体 */
} IMG_HatchPatternBrush,*IMG_HatchPatternBrushPointer;

typedef struct IMG_HatchPatternBrushParam {
	IMG_Point				startPoint;		/* パターン開始位置 */
	IMG_ColorSpace			fgColorSpace;	/* フォアグラウンドカラースペース */
	IMG_ColorSpace			bgColorSpace;	/* バックグラウンドカラースペース */
	IMG_ColorData			fgColor;		/* フォアグラウンドカラー値 */
	IMG_ColorData			bgColor;		/* バックグラウンドカラー値 */
	IMG_PatternTransparency	transp;			/* 透過値 */
	IMG_PatternPolarity		polarity;		/* マスク極性 */
	IMG_HatchPatternKind	hatch;			/* ハッチ種類 */
	IMG_UINT16				patternId;		/* 登録用パターンID */
} IMG_HatchPatternBrushParam,*IMG_HatchPatternBrushParamPointer;

/* 関数プロトタイプ宣言 */
IMG_BrushPointer
	IMG_HatchPatternBrushCreate(IMG_Context *context,
							IMG_HatchPatternBrushParam  *hatchParam);
int
	IMG_HatchPatternBrushSyncFunctionAddress(IMG_Brush *pObject);

#endif /* IMG_HatchPatternBrush_h */
