/* IMG_SolidColorBrush.h */
/* */
#include "IMG_Brush.h"

/* 構造体宣言 */
typedef struct IMG_SolidColorBrush {
	int				(*destroy)(IMG_Brush *brush);
	int				(*realize)(IMG_Brush *brush,IMG_Matrix *matrix);
	int				(*applyTo)(IMG_Brush *brush,IMG_DisplayList *displayList);
	IMG_UINT8		brushType;
	/* ここまでは共通 */
	IMG_Context		context;		/* Imager用コンテキスト */
	IMG_ColorSpace	colorSpace;		/* カラースペース */
	IMG_ColorData	color;			/* カラー値 */
} IMG_SolidColorBrush,*IMG_SolidColorBrushPointer;

/* 関数プロトタイプ宣言 */
IMG_BrushPointer
	IMG_SolidColorBrushCreate(IMG_Context *context,IMG_ColorSpace colorSpace,IMG_ColorData *color);
int
	IMG_SolidColorBrushSyncFunctionAddress(IMG_Brush *pObject);


