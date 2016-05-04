/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverterBrush.h - ブラシ変換クラスの定義
 */

#ifndef INC_IMG_CommandConverterBrush_h
#define INC_IMG_CommandConverterBrush_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_CommandConverter.h"
#include "IMG_ClassPointer.h"
#ifndef MRC
#include "IMG_Page.h"
#endif

/*
 * IMG_CommandConverterBrushクラスの定義
 */
typedef struct img_commandconverterbrush {
	IMG_CommandConverter	super;

	/* Protected操作 */

	/*
	 * [操作名]	applyBursh
	 *
	 * [機能]	ページに対してブラシを適用する。
	 *			本操作は抽象操作である。サブクラスで実装を提供しなければならない。
	 */

	int (*applyBrush)(
		IMG_CommandConverterBrushPtr	self,			/* this pointer */
		IMG_DrawingAttributePtr			currentAttr,	/* 描画コマンド実行直前の描画属性 */
		IMG_DrawMode					drawMode,		/* 変換対象の描画モード */
		IMG_CommandFilterPtr			filter);		/* ブラシを適用するコマンドフィルタ */

} IMG_CommandConverterBrush;

/* protected */

extern int IMG_CommandConverterBrush_Construct(
	IMG_CommandConverterBrushPtr	self,
	IMG_Context						*context);

extern int IMG_CommandConverterBrush_Destruct(
	IMG_CommandConverterBrushPtr	self);

extern int IMG_CommandConverterBrush_Reconstruct(
	IMG_CommandConverterBrushPtr	self);

#endif /* INC_IMG_CommandConverterBrush_h */

/*
 * Log
 * 14.Feb.2002 Yozo Kashima Created
 * 23.Dec.2003 Yozo Kashima AR#1439(Imagerでのタグ拡張のため実行対象をpageでなくfilterに変更)。
 */

/* end of IMG_CommandConverterBrush.h */
