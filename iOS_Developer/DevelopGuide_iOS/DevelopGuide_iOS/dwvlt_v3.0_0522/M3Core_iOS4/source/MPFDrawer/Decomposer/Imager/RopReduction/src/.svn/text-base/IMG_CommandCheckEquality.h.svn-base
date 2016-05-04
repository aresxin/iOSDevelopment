/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckEquality.h - 2つのコマンドの描画結果の同一性を判定するクラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckEquality_h
#define INC_IMG_CommandCheckEquality_h

#include "IMG_CommandCheckCompare.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandCheckEqualityクラスの定義
 *
 * 本クラスは、IMG_CommandCheckCompareクラスのサブクラスである。
 * 本クラスは、IMG_CommandCheckCompareの抽象操作であるcompareCommandの実装を提供する。
 * 本クラスのcompareDrawingCommandは、2つのコマンドの描画結果が同一になるかどうかを検査する。
 */

typedef struct img_commandcheckequality
{
	IMG_CommandCheckCompare	super;

} IMG_CommandCheckEquality;


/*
 * Public操作
 */

/*
 * [操作名]	IMG_CommandCheckEquality_Create
 *
 * [機能]	IMG_CommandCheckEqualityオブジェクトを生成する。
 */
extern IMG_CommandCheckPtr IMG_CommandCheckEquality_Create(
	IMG_Context					*context,		/* 実行環境コンテキスト(IN) */
	IMG_CommandSequencePtr		current,		/* 蓄積中のコマンド群(IN) */
	IMG_CommandSequencePtr		previous);		/* 蓄積済みのコマンド群(IN) */

extern int IMG_CommandCheckEquality_Reconstruct(
	IMG_CommandCheckPtr	self);		/* this pointer */

#endif /* INC_IMG_CommandCheckEquality_h */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandCheckEquality.h */
