/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandSequence.h - コマンドのコンテナクラス
 * Yozo Kashima 20.Jul.2001
 *
 */

#ifndef INC_IMG_CommandSequence_h
#define INC_IMG_CommandSequence_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_RopReduceConfig.h"
#include "IMG_ClassPointer.h"

#include "IMG_DrawingAttribute.h"
#include "IMG_Common.h"
#include "IMG_CommandList.h"

/*
 * IMG_CommandExecRequest構造体の定義
 *
 * IMG_CommandSequence_Executeの引数として使われる。
 * コマンドの実行方法を記述するためのものである。
 */
typedef struct img_commandexecrequest {
	IMG_CommandKind			beExecuted;		/* 実行すべきコマンド種別 */
	IMG_CommandKind			beSaved;		/* 実行後保存すべきコマンド種別 */
	IMG_DrawingAttributePtr	attr;			/* converterに渡す描画属性(converterが指定された時のみ必要) */
	IMG_CommandConverterPtr	converter;		/* コマンドコンバータ(IMG_NULLも許される) */
	IMG_CommandPtr			lastCmd;		/* 実行すべき最後のコマンド(IMG_NULLも許される) */
} IMG_CommandExecRequest;

/*
 * IMG_CommandSequenceクラスの定義
 */
typedef struct img_commandsequence {

	/* Private属性 */
	IMG_Context				*context;					/* 実行環境 */
	IMG_RopMode				ropMode;					/* ROPモード(ROP2,ROP3) */
	IMG_UINT32				ropCode;					/* ROPコード */
	IMG_BOOL				endOfCommand;				/* コマンドの蓄積終了を通知されたか */

	/*
	 * コマンドの集計情報
	 *
	 * drawingCommandCountはインクリメントのみ行い，コマンドが削除されても
	 * デクリメントしないことに注意。(コマンドが共有されている場合には
	 * 正しくデクリメントすることができないため)
	 */
	int						drawingCommandCount;		/* 描画コマンドの数 */
	int						drawPathCount;				/* DrawPathコマンドの数 */
	int						clipPathCount;				/* ClipPathコマンドの数 */
	int						initClipCount;				/* InitClipコマンドの数 */
	int						rectClipCount;				/* SetRectangleClip(COPY)コマンドの数 */
	int						size;						/* 蓄積コマンドの総サイズ(バイト数) */
	int						sharedSize;					/* 共有コマンドの総サイズ(バイト数) */

	/* Private集約 */
	IMG_CommandListPtr		commandList;				/* コマンドリスト */
	IMG_DrawingAttribute	initAttr;					/* 初期描画属性 */
	IMG_RopSequencePtr		observers[IMG_MAX_CANDIDATE];	/* 本オブジェクトを参照しているROP置換方法の候補 */

} IMG_CommandSequence;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandSequence_IsValid(
	IMG_CommandSequencePtr	self);

/*
 * 関数ポインタの再設定
 */
extern int IMG_CommandSequence_ResetFunction(
	IMG_CommandSequencePtr	self);


/*
 * 生成と削除
 */
extern IMG_CommandSequence *IMG_CommandSequence_Create(
	IMG_Context				*context,		/* 実行環境 */
	IMG_RopMode				ropMode,		/* ROPモード */
	IMG_UINT32				ropCode,		/* ROPコード */
	IMG_DrawingAttributePtr	initAttr);		/* 初期描画属性 */

extern int IMG_CommandSequence_Destroy(
	IMG_CommandSequencePtr	self);

extern int IMG_CommandSequence_UpdateObject(
	IMG_CommandSequencePtr	self);

/*
 * サービス関数
 */

/*-------------------------------------------------------------------------
  コマンド操作
-------------------------------------------------------------------------*/
/*
 * コマンドを蓄積する。
 */
extern 	int IMG_CommandSequence_PutCommand(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandPtr			command,		/* 蓄積対象コマンド(+)*/
	IMG_DrawingAttributePtr	attribute);		/* 描画属性(+) */

/*
 * コマンドの蓄積終了を通知する。
 */
extern int IMG_CommandSequence_EndOfCommand(
	IMG_CommandSequencePtr	self);

/*
 * コマンドを実行する
 */
extern int IMG_CommandSequence_Execute(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandFilterPtr	filter,			/* コマンドを受け付けるフィルタ */
	IMG_CommandExecRequest	*request);		/* コマンド実行方法を記述したもの */

/*
 * 初期描画属性をページに設定する。
 */
extern int IMG_CommandSequence_SetInitialAttribute(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandFilterPtr	filter,			/* コマンドを受け付けるフィルタ */
	IMG_CommandKind			beExecuted);	/* 実行すべき描画属性コマンドの種別 */

/*
 * 最初のコマンドからlastCmdで指定されたコマンドの中で
 * 指定種別に合致するコマンドを削除する。
 * lastCmdにNULLを指定すると全てのコマンドが削除される。
 */
extern int IMG_CommandSequence_DestroyCommand(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandKind			kind,			/* 削除すべきコマンドの種別 */
	IMG_CommandPtr			lastCmd);		/* 削除対象の最後のコマンド */

/*
 * カレントのコマンドを取得する。
 */
extern int IMG_CommandSequence_GetCurrentCommand(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandPtr			*cmd);			/* カレントコマンド */

/*
 * コマンドが差し替えられたことを通知する。
 */
extern int IMG_CommandSequence_CommandShared(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandPtr			oldCmd,			/* 自身からRemoveされたコマンド */
	IMG_CommandPtr			newCmd);		/* 自身に追加されたコマンド */

/*
 * 空かどうかを検査する。
 */
extern int IMG_CommandSequence_Empty(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_BOOL				*isEmpty);		/* 空かどうか? */

/*
 * pageにクリップを設定する。
 */
extern int IMG_CommandSequence_SetClipTo(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandFilterPtr	filter,			/* コマンドを受け付けるフィルタ */
	IMG_PatternPolarity		polarity,		/* 極性(イメージの時のみ有効) */
	IMG_BOOL				release,		/* コマンド実行後コマンドを削除するか? */
	IMG_CommandKind			*changedKind);	/* SetClipToで変更された描画属性の種類 */


/*-------------------------------------------------------------------------
  イテレータ作成
-------------------------------------------------------------------------*/

/*
 * コマンド評価オブジェクトを構築する。
 */
extern int IMG_CommandSequence_ConstructEvaluator(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandEvaluatorPtr	evaluator);

/*
 * コマンド評価オブジェクトを生成する。
 */
extern int IMG_CommandSequence_CreateEvaluator(
	IMG_CommandSequencePtr	self,
	IMG_CommandEvaluatorPtr	*evaluator);


/*-------------------------------------------------------------------------
  コマンド変換のためのヘルパー
-------------------------------------------------------------------------*/

typedef struct img_brushinfo {
	IMG_CommandPtr	fillBrush;
	IMG_CommandPtr	strokeBrush;
	IMG_DrawMode	drawMode;
} IMG_BrushInfo;

/*
 * 最初の描画コマンドを実行する時のブラシの情報を取得する。
 */
extern int IMG_CommandSequence_GetBrushInfoAtFirstDraw(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_BrushInfo			*brushInfo);	/* number番目の描画コマンドを実行した時のブラシ情報 */

/*
 * selfに含まれるInitClipコマンドを変換するコンバータを返す。
 * 変換が必要ないならばNULLを返す。
 */
extern int IMG_CommandSequence_CreateInitClipConverter(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandSequencePtr	clipStep,		/* InitClip実行時に再実行すべきコマンド群 */
	IMG_PatternPolarity		polarity,		/* クリップ生成時の極性(clipStepがイメージをコマンドを含む時のみ有効) */
	IMG_CommandConverterPtr	*converter);	/* InitClipのコンバータ */

/*-------------------------------------------------------------------------
  その他
-------------------------------------------------------------------------*/

extern int IMG_CommandSequence_SetRopModeCopy(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_CommandFilterPtr	filter);		/* コマンドを受け付けるフィルタ */

extern int IMG_CommandSequence_ReplaceInitialAttribute(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_DrawingAttributePtr	initAttr);		/* 初期描画属性 */

/*
 * 以下はインライン(されるだろう)関数
 */
static int IMG_CommandSequence_GetSize(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->size;
}

static int IMG_CommandSequence_GetSharedSize(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->sharedSize;
}

/*
 * Copyモードで動作するクリップを数える。
 */
static int IMG_CommandSequence_CountCopyModeClip(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->initClipCount + self->clipPathCount + self->rectClipCount;
}

static int IMG_CommandSequence_CountDrawingCommand(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->drawingCommandCount;
}

static IMG_BOOL IMG_CommandSequence_NoMoreCommand(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->endOfCommand;
}

static IMG_RopMode IMG_CommandSequence_RopMode(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->ropMode;
}

static IMG_UINT32 IMG_CommandSequence_RopCode(
	IMG_CommandSequencePtr	self)			/* this pointer */
{
	return self->ropCode;
}

/*-------------------------------------------------------------------------
  オブザーバーの管理
-------------------------------------------------------------------------*/

/*
 * オブザーバーを登録する。登録されたオブザーバー以外のオブザーバーが
 * IMG_CommandSequenceオブジェクトを占有した時には，IMG_RopSequence
 * オブジェクトにTerminateが通知される。
 */
extern int IMG_CommandSequence_AddObserver(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_RopSequencePtr		observer);		/* オブザーバー */

/*
 * オブザーバの登録を削除する。オブザーバ自身は削除されない。
 */
extern int IMG_CommandSequence_RemoveObserver(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_RopSequencePtr		observer);		/* オブザーバー */

/*
 * 指定されたoccupierによって占有されたことを通知する。
 * occupier以外のオブザーバー(IMG_RopSequenceオブジェクト)には
 * Terminateが通知される。
 */
extern int IMG_CommandSequence_BeOccupied(
	IMG_CommandSequencePtr	self,			/* this pointer */
	IMG_RopSequencePtr		occupier);		/* selfを占有するオブザーバー */

/*-------------------------------------------------------------------------
  プロファイル
-------------------------------------------------------------------------*/

typedef struct img_commandsequenceprofile {
	IMG_RopMode	mode;
	IMG_UINT32	code;
	IMG_UINT32	allCount;
	IMG_UINT32	drawCount;
	IMG_UINT32	attrCount;
	IMG_UINT32	clipCount;
	IMG_UINT32	allSize;
	IMG_UINT32	drawSize;
	IMG_UINT32	attrSize;
	IMG_UINT32	clipSize;
} IMG_CommandSequenceProfile;

extern int IMG_CommandSequence_GetProfile(
	IMG_CommandSequencePtr		self,
	IMG_CommandSequenceProfile	*prof);

#endif /* INC_IMG_CommandSequence_h */

/*
 * Log
 * 20.Jul.2001 Yozo Kashima  Created
 * 22.Aug.2001 Yozo Kashima  executeWithSavingClipメンバーを追加。
 * 28.Aug.2001 Yozo Kashima step3にInitClipが含まれているケースに対応するためのリファクタリング第2段。
 *							execute操作を変更。
 *								- 実行後にCommandオブジェクトを選択的に保存できるようにした。
 *								- IMG_CommandListIteratorRemovableを使用して実現。
 *							setClipTo操作に描画属性のSave/Restoreのための引数を追加。
 * 29.Aug.2001 Yozo Kashima putCommandをサブクラスから引き上げ、isDrawingCommandAcceptableを抽象操作として追加。
 * 17.Sep.2001 Yozo Kashima 障害#97(fh8007g0-07)の対応。
 *							isDrawingCommandAcceptableをisCommandAcceptableとし全種類のコマンドを検査する仕様に変更。
 *							コマンドを受け入れ可能かどうかの判定処理をputCommandからisCommandAcceptableに移す。
 *							統計情報取得関数を追加。
 * 27.Sep.2001 Yozo Kashima 障害#88(pb0008g0-09)の対応。
 *							IMG_CommandSequence_ChangePathCommandKind,IMG_CommandSequence_CreateCommandEvaluatorを追加。
 *							drawOrClipPathCountを追加。
 * 15.Oct.2001 Yozo Kashima IMG_USAGE_NODRAW,IMG_USAGE_NULLを追加。
 * 10.Jan.2002 Yozo Kashima 障害#195対応(it1106t0-07)。
 *							IMG_CommandSequence_BeOneTimeExecutableを追加。
 * 01.Mar.2003 Yozo Kashima AR#1037対応(2kWit043.XDW,ピーマンのへたの部分がおかしい)
 *							AR#1052(Word2k,2kグラフ.XDW,グラデーションがはみ出す)
 *							コピーモードのクリップ命令を正しく数える。
 * 20.Jul.2003 Yozo Kashima Hakugin対応(RemoveObserverを追加)。
 */

/* end of IMG_CommandSequence.h */
