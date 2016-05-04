/*
 * Copyright(C) 2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_TagFilter.h - タグフィルタークラスの定義
 * Yozo Kashima 26.Nov.2003
 *
 */
#ifndef INC_IMG_TagFilter_h
#define INC_IMG_TagFilter_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_DisplayList.h"

/*
 * IMG_ObjectAttribute
 */
typedef struct img_objectattribute {
	IMG_ObjectTag				objectTag;	/* Graphics, Image, Fontのいずれか */
	IMG_DrawMode				drawMode;	/* FILL or STROKE */
	IMG_GraphicsContextPtr		graphicsContext;
	IMG_ThinLineDetectionPtr	thinLineDetection;
} IMG_ObjectAttribute;

#define IMG_ObjectAttribute_Construct2(self, tag, dm)		\
	{														\
		(self)->objectTag = (tag);							\
		(self)->drawMode  = (dm);							\
		(self)->graphicsContext      = IMG_NULL;			\
		(self)->thinLineDetection    = IMG_NULL;			\
	}

#define IMG_ObjectAttribute_Construct4(self, tag, dm, gc, tld)	\
	{															\
		(self)->objectTag = (tag);								\
		(self)->drawMode  = (dm);								\
		(self)->graphicsContext      = gc;						\
		(self)->thinLineDetection    = tld;						\
	}
/*
 * IMG_ThinLineDetectionクラスの定義
 */
typedef struct img_thinlinedetection {
	IMG_Context				*context;

	int (*isThinLine)(
		IMG_ThinLineDetectionPtr	self,
		IMG_DrawMode				drawMode,
		IMG_GraphicsContextPtr		graphicsContext,
		IMG_BOOL					*result);

} IMG_ThinLineDetection;

static int IMG_ThinLineDetection_Construct(
    IMG_ThinLineDetectionPtr	self,
	IMG_Context					*context)
{
	self->context			= context;
	self->isThinLine		= IMG_NULL;

	return 0;
}

/*
 * IMG_TagFilterクラスの定義
 */
typedef struct img_tagfilter {

	/* private属性 */
	IMG_Context				*context;		/* 実行環境コンテキスト */
	IMG_DisplayList			*displayList;

	/* private集約 */

	/* public 操作 */

	int (*destroy)(
		IMG_TagFilterPtr	self);			/* this pointer */

	/* virtual */

	/* abstract */

	/*
	 * Protected操作
	 */
	int (*determineTag)(
		IMG_TagFilterPtr		self,			/* this pointer */
		IMG_ObjectAttribute		*objAttr,		/* 描画オブジェクトの属性情報 */
		IMG_ObjectTag			*tag);

	/* private属性 */
	IMG_ObjectTag	fixedTag;
	IMG_UINT8		brushType;
	IMG_BOOL		isClip;
	int				startAttributeCount;
	int				endAttributeCount;

} IMG_TagFilter;

/* public */

/*
 * コンストラクタ
 */
extern int IMG_TagFilter_Construct(
	IMG_TagFilterPtr	self,				/* this pointer */
	IMG_Context			*context,			/* 実行コンテキスト */
	IMG_DisplayList		*displayList);

/*
 * デストラクタ
 */
extern int IMG_TagFilter_Destruct(
	IMG_TagFilterPtr	self);				/* this pointer */

/*
 * サービス関数
 */
extern int IMG_TagFilter_OnDrawObject(
	IMG_TagFilterPtr	self);			/* this pointer */

extern int IMG_TagFilter_OnClipObject(
	IMG_TagFilterPtr	self);			/* this pointer */

extern int IMG_TagFilter_SetBrushKind(
	IMG_TagFilterPtr	self,			/* this pointer */
	int					brushType);		/* カレントブラシのタイプ */

extern int IMG_TagFilter_StartFixedTag(
	IMG_TagFilterPtr		self,			/* this pointer */
	IMG_ObjectTag			tag);			/* 固定タグ */

extern int IMG_TagFilter_EndFixedTag(
	IMG_TagFilterPtr		self);			/* this pointer */

extern int IMG_TagFilter_StartAttribute(
	IMG_TagFilterPtr		self,			/* this pointer */
	IMG_DisplayListPointer	displayList,	/* DisplayList */
	IMG_ObjectAttribute		*objAttr);		/* 描画オブジェクトの属性情報 */
		
extern int IMG_TagFilter_EndAttribute(
	IMG_TagFilterPtr		self,			/* this pointer */
	IMG_DisplayListPointer	displayList);	/* DisplayList */

#endif /* INC_IMG_TagFilter_h */

/*
 * Log
 * 26.Nov.2003 Yozo Kashima  Created

 */

/* end of IMG_TagFilter.h */
