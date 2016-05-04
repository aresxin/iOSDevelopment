/* IMG_Brush.h */

#ifndef	INC_IMG_Brush_h
#define INC_IMG_Brush_h

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_Matrix.h"
#include "IMG_DisplayList.h"

/* 定義 */
/* 下記のbrushTypeに使う値 */
#define IMG_BRUSH_SOLID		1
#define IMG_BRUSH_HATCH		2
#define IMG_BRUSH_MASK		3
#define	IMG_BRUSH_RASTER	4

/* オブジェクト定義 */
typedef struct IMG_Brush *IMG_BrushPointer;
typedef struct IMG_Brush {
	int				(*destroy)(IMG_BrushPointer brush);
	int				(*realize)(IMG_BrushPointer brush,IMG_Matrix *matrix);
	int				(*applyTo)(IMG_BrushPointer brush,IMG_DisplayList *displayList);
	IMG_UINT8		brushType;	/* SLIOD/HATCH/PATTERN/RASTER */
} IMG_Brush;

int
	IMG_BrushSyncFunctionAddress(IMG_Brush *pBrush);

/* INC_IMG_Brush_h */
#endif

