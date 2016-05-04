/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_RopReducer.h - ROP置換の実行管理クラス
 * Yozo Kashima 20.Jul.2001
 *
 */

#ifndef INC_IMG_RopReducer_h
#define INC_IMG_RopReducer_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_RopReduceConfig.h"

/*
 * IMG_RopReducerが呼び出し元に返すステータス
 */
typedef enum img_ropreducerstatus {
	IMG_ROP_REDUCTION_COMPLETE,		/* ROP置き換え完了 */
	IMG_ROP_REDUCTION_CANCELED,		/* ROP置き換えを途中で終了 */
	IMG_ROP_REDUCTION_PROCESSING,	/* ROP置き換えを実行中 */
} IMG_RopReducerStatus;

/*
 * IMG_RopReducerクラスの定義
 */
typedef struct img_ropreducer {

	/* private属性 */
	IMG_Context				*context;		/* 実行環境コンテキスト */

	IMG_UINT32				marginBytes;	/* 総メモリに対する蓄積サイズのマージン値(バイト数) */
	IMG_INT32				stepIndex;		/* 現ROPステップ番号(0以上が有効値) */

	/* private集約 */

	IMG_INT32				pageNumber;						/* 処理中のページ番号(ログ用) */
	IMG_DrawingAttributePtr	initAttr;						/* 描画属性オブジェクトの初期値 */
	IMG_DrawingAttributePtr	curAttr;						/* 描画属性オブジェクトの現在の状態 */
	IMG_CommandSequencePtr	steps[IMG_MAX_ROP_STEP];		/* ROPステップ */
	IMG_RopSequencePtr		candidates[IMG_MAX_CANDIDATE];	/* ROP置換方法の候補 */

} IMG_RopReducer;

/* public */

/*
 * 生成
 */
extern IMG_RopReducerPtr IMG_RopReducer_Create(
	IMG_Context					*context,			/* 実行コンテキスト */
	IMG_DrawingAttributePtr		initAttr,			/* 初期描画属性 */
	IMG_INT32					pageNumber,			/* 処理中のページ番号 */
	IMG_RopMode					ropMode,			/* 第1ステップのROPモード */
	IMG_UINT32					ropCode);			/* 第1ステップのROPコード */

/*
 * 削除
 */
extern int IMG_RopReducer_Destroy(
	IMG_RopReducerPtr			self);				/* this pointer */

/*
 * オブジェクトの更新
 */
extern int IMG_RopReducer_UpdateObject(
	IMG_RopReducerPtr		self);

/*
 * クラスメソッド
 */
extern IMG_BOOL IMG_RopReducer_IsSupported(
	IMG_RopMode				ropMode,
	IMG_UINT32				ropCode);

extern IMG_BOOL IMG_RopReducer_IsValid(
	IMG_RopReducerPtr		self);

/*
 * サービス関数
 */
extern int IMG_RopReducer_EndOfCommand(
	IMG_RopReducerPtr		self,		/* this pointer */
	IMG_CommandFilterPtr	filter);	/* ROP置換後のコマンドを受けるフィルタ */

extern int IMG_RopReducer_SetRopMode(
	IMG_RopReducerPtr		self,		/* this pointer */
	IMG_RopMode				ropMode,	/* ROPモード */
	IMG_UINT32				ropCode,	/* ROPコード */
	IMG_CommandFilterPtr	filter,		/* ROP置換後のコマンドを受けるフィルタ */
	IMG_RopReducerStatus	*status);	/* ステータスコード */

extern int IMG_RopReducer_PutCommand(
	IMG_RopReducerPtr		self,
	IMG_CommandPtr			command,
	IMG_CommandFilterPtr	filter,		/* ROP置換後のコマンドを受けるフィルタ */
	IMG_RopReducerStatus	*status);

extern int IMG_RopReducer_Cancel(
	IMG_RopReducerPtr		self,
	IMG_CommandFilterPtr	filter);	/* ROP置換後のコマンドを受けるフィルタ */

/*
 * IMG_RopSequenceクラスが使用する関数の宣言。
 */

extern int IMG_RopReducer_DestroyStep(
	IMG_RopReducerPtr		self,		/* this pointer */
	IMG_CommandSequencePtr	step);

extern int IMG_RopReducer_FindCommandCheck(
	IMG_RopReducerPtr		self,		/* this pointer */
	IMG_CommandCheckPtr		key,
	IMG_CommandCheckPtr		*result);

extern int IMG_RopReducer_AddCommandCheck(
	IMG_RopReducerPtr		self,		/* this pointer */
	IMG_CommandCheckPtr		cmdCheck);

extern int IMG_RopReducer_GetPageNumber(
	IMG_RopReducerPtr		self);		/* this pointer */

#endif /* INC_IMG_RopReducer_h */

/*
 * Log
 * 15.Feb.2002 Yozo Kashima  Created

 */

/* end of IMG_RopSequence.h */

