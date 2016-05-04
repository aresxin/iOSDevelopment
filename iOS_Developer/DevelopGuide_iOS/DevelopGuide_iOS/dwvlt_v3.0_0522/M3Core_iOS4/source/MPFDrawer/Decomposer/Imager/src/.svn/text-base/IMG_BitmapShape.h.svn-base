/* IMG_BitmapShape.h */

#ifndef	INC_IMG_BirmapShape_h
#define	INC_IMG_BirmapShape_h

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_Matrix.h"
#include "IMG_DisplayList.h"
#include "IMG_ClassPointer.h"

/* 定義 */

/* 下記のbitmapTypeで使う値 */
#define IMG_BITMAP_FONT			1
#define IMG_BITMAP_IMAGE		2
#define	IMG_BITMAP_IMAGEMASK	3

/* オブジェクト定義 */
typedef struct IMG_BitmapShape *IMG_BitmapShapePointer;
typedef struct IMG_BitmapShape {
	int				(*destroy)(IMG_BitmapShapePointer object);
	int				(*draw)(IMG_BitmapShapePointer object,
							IMG_DisplayList *displayList,
							IMG_TagFilterPtr	tagFilter,
							IMG_Matrix *matrix);
	IMG_UINT8		bitmapType;		/* font,image,imagemaskのどれなのか */
} IMG_BitmapShape;

#endif	/* INC_IMG_BirmapShape_h */
