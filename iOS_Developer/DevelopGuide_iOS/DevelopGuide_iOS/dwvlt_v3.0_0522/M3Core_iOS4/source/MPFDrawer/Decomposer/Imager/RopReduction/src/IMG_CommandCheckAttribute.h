/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheckAttribute.h - ROP置換処理における描画属性判定クラスの定義
 *
 */

#ifndef INC_IMG_CommandCheckAttribute_h
#define INC_IMG_CommandCheckAttribute_h

#include "IMG_CommandCheck.h"
#include "IMG_CommandEvaluator.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandCheckAttributeクラスの定義
 *
 * 本クラスは、IMG_CommandCheckクラスのサブクラスである。
 * 本クラスは、コマンドによって描画される描画オブジェクトの色を検査する。本クラスでは，
 * IMG_CommandCheckのdoCheckNextをオーバーライトし、doCheckNextの実装の一部を提供する。
 * doCheckNextは、本クラスで定義された抽象操作checkAttributeOfを呼び出し，新たに蓄積された
 * コマンドの属性を検査する(cf. Template Pattern)。
 * 本クラスを継承するサブクラスは、checkAttributeOfの実装を提供すること。
 */

typedef struct img_commandcheckattribute {

	IMG_CommandCheck	super;

	/* Protected操作 */

	/*
	 * [操作名]	checkAttributeOf
	 *
	 * [機能]	描画コマンドの属性を検査する。
	 *			検査が成功したらresult->isOkにIMG_TRUEを、失敗したらIMG_FALSEをセットする。
	 *			本操作は抽象操作である。サブクラスで実装を提供しなければならない。
	 */

	int (*checkAttributeOf)(
		IMG_CommandCheckAttributePtr	self,			/* this pointer */
		IMG_CommandPtr					newDrawCmd,		/* 新たに蓄積された描画コマンド(IN) */
		IMG_CommandCheckResultPtr		result);		/* 比較結果(OUT) */

	/* Protected関連 */

} IMG_CommandCheckAttribute;

/*
 * Protected操作
 */
extern int IMG_CommandCheckAttribute_IsEqualTo(
	IMG_CommandCheckPtr			self,		/* this pointer */
	IMG_CommandCheckPtr			target,		/* 比較対象のコマンド検査オブジェクト */
	IMG_BOOL					*result);	/* 比較結果 */

/*
 * コンストラクタ
 */
extern int IMG_CommandCheckAttribute_Construct(
	IMG_CommandCheckAttributePtr	self,		/* this pointer */
	IMG_Context						*context,	/* 実行環境コンテキスト(IN) */
	IMG_CommandCheckID				id,			/* コマンド検査オブジェクトID */
	IMG_CommandSequencePtr			target);	/* 色判定する対象のコマンド群(IN) */

/*
 * デストラクタ
 */
extern int IMG_CommandCheckAttribute_Destruct(
	IMG_CommandCheckAttributePtr	self);		/* this pointer */


/*
 * 再構築
 */
extern int IMG_CommandCheckAttribute_Reconstruct(
	IMG_CommandCheckAttributePtr	self);		/* this pointer */

#endif /* INC_IMG_CommandCheckAttribute_h */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 * 20.Jul.2003 Yozo Kashima Hakugin対応(IsEqualToをprotectedに変更)。
 */

/* end of IMG_CommandCheckAttribute_h */
