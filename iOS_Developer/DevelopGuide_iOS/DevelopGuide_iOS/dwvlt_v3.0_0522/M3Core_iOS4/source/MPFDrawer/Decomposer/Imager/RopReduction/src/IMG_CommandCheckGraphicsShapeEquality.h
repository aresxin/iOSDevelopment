/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckGraphicsShapeEquality.h - 2つのコマンド群の描画結果の同一性を判定するクラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckGraphicsShapeEquality_h
#define INC_IMG_CommandCheckGraphicsShapeEquality_h

#include "IMG_CommandCheckCompare.h"
#include "IMG_ClassPointer.h"
#include "IMG_RopDataConversionLib.h"

/*
 * IMG_CommandCheckGraphicsShapeEqualityクラスの定義
 *
 * 本クラスは、IMG_CommandCheckCompareクラスのサブクラスである。
 * 本クラスは、IMG_CommandCheckCompareの抽象操作であるcompareCommandの実装を提供する。
 * 本クラスのcompareDrawingCommandは、2つのグラフィックス描画コマンドの描画結果が同一
 * の形状になるかどうかを検査する。
 *
 * イメージ形状の詳細を記述すること。
 */

typedef struct img_commandcheckgraphicsshapeequality
{
	IMG_CommandCheckCompare	super;
} IMG_CommandCheckGraphicsShapeEquality;


/*
 * Public操作
 */

/*
 * [操作名]	IMG_CommandCheckGraphicsShapeEquality_Create
 *
 * [機能]	IMG_CommandCheckGraphicsShapeEqualityオブジェクトを生成する。
 */
extern IMG_CommandCheckPtr IMG_CommandCheckGraphicsShapeEquality_Create(
	IMG_Context				*context,		/* 実行環境コンテキスト(IN) */
	IMG_CommandSequencePtr	current,		/* 蓄積中のコマンド群(IN) */
	IMG_CommandSequencePtr	previous);		/* 蓄積済みのコマンド群(IN) */

extern int IMG_CommandCheckGraphicsShapeEquality_Reconstruct(
	IMG_CommandCheckPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandCheckGraphicsShapeEquality_h */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandCheckGraphicsShapeEquality.h */
