/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckGraphicsColor.h - ROP置換処理におけるグラフィックスコマンドの色判定クラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckGraphicsColor_h
#define INC_IMG_CommandCheckGraphicsColor_h

#include "IMG_CommandCheckAttribute.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandCheckGraphicsColorクラスの定義
 *
 * 本クラスは、IMG_CommandAttributeクラスのサブクラスである。
 * 本クラスは、IMG_CommandAttributeの抽象操作であるcheckAttributeOfの実装を提供する。
 * checkAttributeOfは、グラフィックスの色を検査する。検査すべき色は列挙型
 * IMG_GraphicsColorCheckで定義される値をオブジェクトの生成時関数
 * IMG_CommandCheckGraphicsColor_Createの引数で指定すること。
 */

/* グラフィックスの色の検査内容指定 */
typedef enum img_graphicscolorcheck {
	IMG_GRAPHICS_COLOR_CHECK_BLACK,			/* グラフィックスの色が黒であること */
	IMG_GRAPHICS_COLOR_CHECK_BW_PATTERN,	/* グラフィックスの色が黒と白のパターンであること */
} IMG_GraphicsColorCheck;

typedef struct img_commandcheckgraphicscolor {
	IMG_CommandCheckAttribute	super;

	/*
	 * Private属性
	 */
	IMG_GraphicsColorCheck	checkWhat;	/* 検査内容 */

} IMG_CommandCheckGraphicsColor;

/*
 * Public操作
 */

/*
 * [操作名]	IMG_CommandCheckGraphicsColor_Create
 *
 * [機能]	IMG_CommandCheckGraphicsColorオブジェクトを生成する。
 */
extern IMG_CommandCheckPtr IMG_CommandCheckGraphicsColor_Create(
	IMG_Context				*context,		/* 実行環境コンテキスト(IN) */
	IMG_CommandSequencePtr	target,			/* 色を判定する対象のコマンド群(IN) */
	IMG_GraphicsColorCheck	checkWhat);		/* 検査内容(IN) */

extern int IMG_CommandCheckGraphicsColor_Reconstruct(
	IMG_CommandCheckPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandCheckGraphicsColor_h */

											/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandCheckGraphicsColor.h */
