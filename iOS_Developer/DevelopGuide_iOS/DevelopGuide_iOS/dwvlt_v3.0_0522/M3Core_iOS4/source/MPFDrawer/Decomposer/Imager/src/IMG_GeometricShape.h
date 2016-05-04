/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001-2002. All rights reserved.
 * IMG_GeometricShape.h	IMG関連ヘッダファイル
 * Created: Apr, 4,2001	Yozo Kashima
 * Edited : Apr, 4,2001	Kenichi Ishida
 * Edited : Apr,17,2001	Toshio Yamazaki
 * Edited : Apr,24,2001	Toshio Yamazaki		座標変換無しfill I/F追加
 * Edited : Feb,21,2001	Yozo Kashima		pathTo I/F追加
 */

#ifndef INC_IMG_GeometricShape_h
#define INC_IMG_GeometricShape_h

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_Matrix.h"
#include "IMG_DisplayList.h"
#include "IMG_GraphicsContext.h"
#include "IMG_ClassPointer.h"

/* オブジェクト定義 */
/* IMG_DisplayList.hとIMG_GraphicsContext.hで
   定義されているからコメントアウト
   Apr,17,2001 Toshio Yamazaki
typedef struct img_graphicscontext IMG_GraphicsContext;
typedef struct img_displaylist IMG_DisplayList;*/
struct img_path;

typedef struct img_geometricshape *IMG_GeometricShapePointer;
typedef struct img_geometricshape {

	int (*destroy)(
		IMG_GeometricShapePointer object);		/* GeometricShapeオブジェクト */

	int (*fill)(
		IMG_GeometricShapePointer object,		/* GeometricShapeオブジェクト */
		IMG_DisplayList		*displayList,		/* DisplayListオブジェクト */
		IMG_TagFilterPtr	tagFilter,
		IMG_GraphicsContext *graphicsContext);	/* 描画属性 */

	int (*fill_NOTRANSFORM)(
		IMG_GeometricShapePointer object,		/* GeometricShapeオブジェクト */
		IMG_DisplayList		*displayList,		/* DisplayListオブジェクト */
		IMG_GraphicsContext *graphicsContext);	/* 描画属性 */

	int (*stroke)(
		IMG_GeometricShapePointer object,		/* GeometricShapeオブジェクト*/
		IMG_DisplayList		*displayList,		/* DisplayListオブジェクト */
		IMG_TagFilterPtr	tagFilter,
		IMG_GraphicsContext *graphicsContext);	/* 描画属性 */

	int (*pathTo)(
		IMG_GeometricShapePointer object,		/* GeometricShapeオブジェクト*/
		struct img_path			*path,			/* Pathオブジェクト */
		IMG_GraphicsContext *graphicsContext,	/* 描画属性 */
		IMG_BOOL				transform);		/* 座標変換が必要か? */

} IMG_GeometricShape;

/* INC_IMG_GeometricShape_h */
#endif

