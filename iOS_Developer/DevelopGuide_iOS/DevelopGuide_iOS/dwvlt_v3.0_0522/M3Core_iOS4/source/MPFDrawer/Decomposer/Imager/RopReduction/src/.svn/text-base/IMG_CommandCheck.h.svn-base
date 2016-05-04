/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandCheck.h - ROP置換処理におけるコマンドの検査クラスの定義
 *
 */

#ifndef INC_IMG_CommandCheck_h
#define INC_IMG_CommandCheck_h

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_RopReduceConfig.h"
#include "IMG_CommandEvaluator.h"


/*
 * IMG_CommandCheckResult構造体の定義
 *
 * IMG_CommandCheck_CheckNextの引数として使用される。
 */
typedef struct img_commandcheckresult  {
	IMG_BOOL		isOk;		/* 成功か失敗 */
	IMG_CommandPtr	cmd;		/* 検査されたコマンド */
	const char		*reason;	/* 失敗原因．成功の時はNULL値 */
} IMG_CommandCheckResult;

/*
 * コマンド検査IDの定義
 *
 * このIDはサブクラス毎に用意する。
 * IMG_CommandCheckオブジェクトの同一性検査とサブクラスの型判定
 * (オブジェクト再構築時に必要)に使用する。
 */
typedef enum img_commandcheckid {
	IMG_COMMAND_CHECK_ID_NULL,						/* 定義なし */
	IMG_COMMAND_CHECK_ID_GRAPHICS_COLOR,			/* グラフィクスの色検査 */
	IMG_COMMAND_CHECK_ID_IMAGE_COLOR,				/* イメージの色検査 */
	IMG_COMMAND_CHECK_ID_GRAPHICS_SHAPE_EQUALITY,	/* グラフィックス形状の同一性検査 */
	IMG_COMMAND_CHECK_ID_IMAGE_SHAPE_EQUALITY,		/* イメージ形状の同一性検査 */
	IMG_COMMAND_CHECK_ID_EQUALITY,					/* 描画結果の同一性検査 */
} IMG_CommandCheckID;

/*
 * IMG_CommandCheckクラスの定義
 *
 * 本クラスはROP置換におけるコマンド検査の抽象クラスである。
 */

typedef struct img_commandcheck {

	/* Public操作 */

	/*
	 * [操作名]	isEqualTo
	 * [機能]	targetのコマンド検査オブジェクトとの同一性を検査する。
	 *			検査の結果がOKならresultにはIMG_TRUE、NGならIMG_FALSEを設定する。
	 */
	int (*isEqualTo)(
		IMG_CommandCheckPtr			self,		/* this pointer */
		IMG_CommandCheckPtr			target,		/* 比較対象のコマンド検査オブジェクト */
		IMG_BOOL					*result);	/* 比較結果 */

	/* Protected操作 */

	/*
	 * [操作名]	destroy
	 * [機能]	オブジェクトを削除する。
	 * [注意]	本操作はProtectedなので，クライアントは呼んではならない。
	 *			クライアントはIMG_CommandCheck_Releaseを使うこと。
	 */
	int (*destroy)(
		IMG_CommandCheckPtr			self);		/* this pointer */

	/*
	 * [操作名]	doCheckNext
	 * [機能]	新たに蓄積された描画コマンドを検査する。
	 *			検査の結果がOKならresult->isOkにはIMG_TRUE、NGならIMG_FALSEを設定する。
	 * [注意]	本操作はProtectedなので，クライアントは呼んではならない。
	 *			クライアントはIMG_CommandCheck_CheckNextを使うこと。
	 */
	int (*doCheckNext)(
		IMG_CommandCheckPtr			self,		/* this pointer */
		IMG_CommandPtr				newCmd,		/* 新たに蓄積されたコマンド */
		IMG_CommandCheckResultPtr	result);	/* コマンド検査結果 */
	
	/* Protected集約 */

	IMG_Context				*context;
	IMG_CommandEvaluator	current;		/* 現在蓄積が継続しているコマンド群の評価オブジェクト */

	/* Private属性 */
	
	IMG_CommandCheckResult	cachedRes;		/* 検査結果のキャッシュ */
	IMG_CommandCheckID		id;				/* サブクラスの識別子 */
	IMG_UINT32				refCounter;		/* 参照カウンタ */

} IMG_CommandCheck;

/*
 * Public操作
 */

extern int IMG_CommandCheck_Release(
	IMG_CommandCheckPtr			self);		/* this pointer */

extern int IMG_CommandCheck_CheckNext(
	IMG_CommandCheckPtr			self,		/* this pointer */
	IMG_CommandCheckResultPtr	result);	/* コマンド検査結果 */

extern int IMG_CommandCheck_Refer(
	IMG_CommandCheckPtr	*lhs,		/* left hand side */
	IMG_CommandCheckPtr	rhs);		/* right hand side */

static IMG_CommandCheckID IMG_CommandCheck_GetID(
	IMG_CommandCheckPtr			self)		/* this pointer */
{
	return self->id;
}

/*
 * Protected操作
 */

extern int IMG_CommandCheck_Construct(
	IMG_CommandCheck		*self,			/* this pointer */
	IMG_Context				*context,		/*	実行環境コンテキスト */
	IMG_CommandCheckID		id,				/* コマンド検査オブジェクトID */
	IMG_CommandSequencePtr	current);		/* 比較対象のコマンド群(IN) */

extern int IMG_CommandCheck_Destruct(
	IMG_CommandCheckPtr		self);			/* this pointer */

extern int IMG_CommandCheck_Reconstruct(
	IMG_CommandCheckPtr		self);			/* this pointer */

/*
 * resultにコマンド検査結果を設定する。
 */
extern void IMG_CommandCheckResult_SetInfo(
	IMG_CommandCheckResult	*result,
	IMG_BOOL				isOk,
	IMG_CommandPtr			cmd,
	const char				*reason);

#endif /* INC_IMG_CommandCheck_h */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 * 01.Apr.2004 Yozo Kashima AR#1463(Gradation検出用クラスのIDを削除)
 */

/* end of IMG_CommandCheck.h */
