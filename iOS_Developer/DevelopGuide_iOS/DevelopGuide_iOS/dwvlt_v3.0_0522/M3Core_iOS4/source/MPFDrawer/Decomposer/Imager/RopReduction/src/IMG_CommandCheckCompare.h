/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckCompare.h - 2つのコマンドの比較判定クラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckCompare_h
#define INC_IMG_CommandCheckCompare_h

#include "IMG_CommandCheck.h"
#include "IMG_CommandEvaluator.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandCheckCompareクラスの定義
 *
 * 本クラスは、IMG_CommandCheckクラスのサブクラスである。
 * 本クラスは、2つのコマンドによる描画結果を比較し，要求に合致するものかどうかを判定する。
 * 本クラスではIMG_CommandCheckのdoCheckNextをオーバーライトし，doCheckNextの実装の一部を提供する。
 * doCheckNextは、本クラスで定義された抽象操作compareDrawingCommandを呼び出し，新たに蓄積された
 * コマンドと以前に蓄積されたコマンドの描画結果を比較する。(cf. Template Pattern)。
 * 本クラスを継承するサブクラスは、compareDrawingCommandの実装を提供すること。
 */

typedef struct img_commandcheckcompare {

	IMG_CommandCheck	super;

	/* Protected操作 */
	/* abstract */
	/*
	 * [操作名]	compareDrawingCommand
	 *
	 * [機能]	2つの描画コマンドを比較する。
	 *			比較が成功したらresultにIMG_TRUEを、失敗したらIMG_FALSEをセットする。
	 */
	int (*compareDrawingCommand)(
		IMG_CommandCheckComparePtr	self,		/* this pointer */
		IMG_CommandPtr				newCmd,		/* 新たに蓄積された描画コマンド(IN) */
		IMG_CommandPtr				oldCmd,		/* newCmdの位置に対応する既に蓄積されたコマンド(IN) */
		IMG_CommandCheckResultPtr	result);	/* 比較結果(OUT) */

	/* virtual */
	/*
	 * [操作名]	tryToShare
	 *
	 * [機能]	newCmdで指定されるコマンドと同じコマンドが既に蓄積されているならば，
	 *			コマンドを共有させる。共有によって得られたコマンドのポインタをsharedCmdに
	 *			セットする。本操作は抽象操作だが，デフォルト実装が提供されている。デフォルト実装は
	 *			newCmdをそのままsharedCmdにセットする。
	 */
	int (*tryToShare) (
		IMG_CommandCheckComparePtr	self,		/* this pointer */
		IMG_CommandPtr				newCmd,		/* 新たに蓄積された描画コマンド(IN) */
		IMG_CommandPtr				*sharedCmd);/* 共有化により置き換えられたコマンド(OUT) */

	/* Protected集約 */
	IMG_CommandEvaluator	previous;			/* 既に蓄積は終了しているコマンド群の評価オブジェクト */

} IMG_CommandCheckCompare;

#endif /* INC_IMG_CommandCheckCompare_h */

/*
 * Protected操作
 */

/*
 * コンストラクタ
 */
extern int IMG_CommandCheckCompare_Construct(
	IMG_CommandCheckComparePtr	self,			/* this pointer */
	IMG_Context					*context,		/* 実行環境コンテキスト(IN) */
	IMG_CommandCheckID			id,				/* コマンド検査オブジェクトID */
	IMG_CommandSequencePtr		current,		/* 蓄積中のコマンド群(IN) */
	IMG_CommandSequencePtr		previous);		/* 蓄積済みのコマンド群(IN) */

/*
 * デストラクタ
 */
extern int IMG_CommandCheckCompare_Destruct(
	IMG_CommandCheckComparePtr	self);			/* this pointer */

/*
 * 再構築
 */
extern int IMG_CommandCheckCompare_Reconstruct(
	IMG_CommandCheckComparePtr	self);			/* this pointer */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandCheckCompare.h */
