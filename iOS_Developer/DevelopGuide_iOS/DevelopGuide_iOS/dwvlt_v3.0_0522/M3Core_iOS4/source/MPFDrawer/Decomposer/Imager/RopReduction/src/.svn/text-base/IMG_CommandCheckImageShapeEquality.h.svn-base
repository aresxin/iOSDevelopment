/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckImageShapeEquality.h - 2つのコマンド群の描画結果の同一性を判定するクラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckImageShapeEquality_h
#define INC_IMG_CommandCheckImageShapeEquality_h

#include "IMG_CommandCheckCompare.h"
#include "IMG_ClassPointer.h"
#include "IMG_RopDataConversionLib.h"

/*
 * IMG_CommandCheckImageShapeEqualityクラスの定義
 *
 * 本クラスは、IMG_CommandCheckCompareクラスのサブクラスである。
 * 本クラスは、IMG_CommandCheckCompareの抽象操作であるcompareCommandの実装を提供する。
 * 本クラスのcompareDrawingCommandは、2つのイメージ描画コマンドの描画結果が同一の形状
 * になるかどうかを検査する。
 *
 * イメージ形状の詳細を記述すること。
 */

typedef struct img_commandcheckimageshapeequality
{

	IMG_CommandCheckCompare	super;

	/*
	 * Private属性
	 */
	const IMG_RopDataConvLib_PixelMap *prohibited;	/* イメージの形状比較結果で許されないパターン */

} IMG_CommandCheckImageShapeEquality;


/*
 * Public操作
 */

/*
 * [操作名]	IMG_CommandCheckImageShapeEquality_Create
 *
 * [機能]	IMG_CommandCheckImageShapeEqualityオブジェクトを生成する。
 */
extern IMG_CommandCheckPtr IMG_CommandCheckImageShapeEquality_Create(
	IMG_Context				*context,				/* 実行環境コンテキスト(IN) */
	IMG_CommandSequencePtr	current,				/* 蓄積中のコマンド群(IN) */
	IMG_CommandSequencePtr	previous,				/* 蓄積済みのコマンド群(IN) */
	const IMG_RopDataConvLib_PixelMap *prohibited);	/* イメージの形状比較で許されないパターン(IN) */

extern int IMG_CommandCheckImageShapeEquality_Reconstruct(
	IMG_CommandCheckPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandCheckImageShapeEquality_h */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandCheckImageShapeEquality.h */
