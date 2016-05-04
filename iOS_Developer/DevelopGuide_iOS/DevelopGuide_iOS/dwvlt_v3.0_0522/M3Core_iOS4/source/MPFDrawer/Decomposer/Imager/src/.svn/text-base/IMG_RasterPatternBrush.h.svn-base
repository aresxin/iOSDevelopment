/* IMG_RasterPatternBrush.h */

#ifndef	INC_IMG_RasterPatternBrush_h
#define	INC_IMG_RasterPatternBrush_h

#include "IMG_Brush.h"

/* 構造体宣言 */
typedef struct IMG_RasterPatternBrush {
	int				(*destroy)(IMG_Brush *brush);
	int				(*realize)(IMG_Brush *brush,IMG_Matrix *matrix);
	int				(*applyTo)(IMG_Brush *brush,IMG_DisplayList *displayList);
	IMG_UINT8		brushType;
	/* ここまでは共通 */
	IMG_Context				context;			/* Imager用コンテキスト */
	IMG_Point				startPoint;			/* パターン表示開始座標 */
	IMG_UINT16				width;				/* パターン幅 */
	IMG_UINT16				widthBytes;			/* パターン幅バイト数 */
	IMG_UINT16				height;				/* パターン高さ */
	IMG_ColorSpace			colorSpace;			/* カラースペース */
	IMG_ColorInterleave		colorInterleave;	/* 色順次 */
	IMG_UINT8				dataDepth;			/* データ深さ */
	IMG_UINT32				dataSize;			/* データバイトサイズ*/
	char					*dataAddress;		/* ラスターデータアドレス */
	IMG_BOOL				dataMallocFlg;		/* メモリを開放しなければいけないかどうか */
	IMG_UINT16				patternId;			/* 登録用パターンID */
} IMG_RasterPatternBrush,*IMG_RasterPatternBrushPointer;

typedef struct IMG_RasterPatternBrushParam {
	IMG_Point				startPoint;			/* パターン表示開始座標 */
	IMG_UINT16				width;				/* パターン幅 */
	IMG_UINT16				height;				/* パターン高さ */
	IMG_UINT32				dataSize;			/* データバイトサイズ */
	IMG_BOOL				dataMallocFlg;		/* 入力データをIMG_FREEする必要があるかどうか IMG_TRUEなら必要あり */
	IMG_ColorSpace			colorSpace;			/* カラースペース */
	IMG_ColorInterleave		colorInterleave;	/* 色順次 */
	IMG_UINT8				dataDepth;			/* データ深さ */
	IMG_UINT16				patternId;			/* 登録用パターンID */
} IMG_RasterPatternBrushParam,*IMG_RasterPatternBrushParamPointer;

/* 関数プロトタイプ宣言 */
IMG_BrushPointer
	IMG_RasterPatternBrushCreate(IMG_Context *context,
							IMG_RasterPatternBrushParam *rasterParam,
							char *dataAddress);
int
	IMG_RasterPatternBrushSyncFunctionAddress(IMG_Brush *pObject);

#endif	/* INC_IMG_RasterPatternBrush_h */
