/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckImageColor.h - ROP置換処理におけるイメージコマンドの色判定クラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckImageColor_h
#define INC_IMG_CommandCheckImageColor_h

#include "IMG_CommandCheckAttribute.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandCheckImageColorクラスの定義
 *
 * 本クラスは、IMG_CommandAttributeクラスのサブクラスである。
 * 本クラスは、IMG_CommandAttributeの抽象操作であるcheckAttributeOfの実装を提供する。
 * checkAttributeOfは、イメージの色を検査する。現状の実装では、イメージが黒と白の
 * ピクセルから構成されるかどうかを検査する機能だけ提供している。
 */

/* イメージの色の検査内容指定 */
typedef enum img_imagecolorcheck {
	IMG_IMAGE_COLOR_CHECK_BW,				/* イメージの色が黒と白であること */
} IMG_ImageColorCheck;

typedef struct img_commandcheckimagecolor {
	IMG_CommandCheckAttribute	super;
	IMG_ImageColorCheck			checkWhat;	/* 検査内容 */
} IMG_CommandCheckImageColor;

/*
 * Public操作
 */

/*
 * [操作名]	IMG_CommandCheckImageColor_Create
 *
 * [機能]	IMG_CommandCheckImageColorオブジェクトを生成する。
 */
extern IMG_CommandCheckPtr IMG_CommandCheckImageColor_Create(
	IMG_Context				*context,		/* 実行環境コンテキスト(IN) */
	IMG_CommandSequencePtr	target,			/* 白黒判定する対象のコマンド群(IN) */
	IMG_ImageColorCheck		checkWhat);		/* 検査内容(IN) */

extern int IMG_CommandCheckImageColor_Reconstruct(
	IMG_CommandCheckPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandCheckImageColor_h */

											/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandCheckImageColor.h */
