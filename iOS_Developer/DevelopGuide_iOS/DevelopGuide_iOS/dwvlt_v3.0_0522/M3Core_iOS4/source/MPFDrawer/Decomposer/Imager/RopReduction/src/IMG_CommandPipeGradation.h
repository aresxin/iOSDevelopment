/*
 * Copyright(C) 2001-2004 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandPipeGradation.h - グラデーション検出用パイプクラスの定義
 */

#ifndef INC_IMG_CommandPipeGradation_h
#define INC_IMG_CommandPipeGradation_h

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"

#define IMG_WRITE_GRADATION_LOG

/*
 * グラデーション方向の定義
 */
typedef enum img_gradationdirection {
	IMG_GRADATION_DIRECTION_NULL,
	IMG_GRADATION_DIRECTION_HORIZONTAL,
	IMG_GRADATION_DIRECTION_VERTICAL,
	IMG_GRADATION_DIRECTION_COMPOSITE,
	IMG_GRADATION_DIRECTION_UNKNOWN,
} IMG_GradationDirection;

/*
 * グラデーション判定状態の定義
 */
typedef enum img_commandpipegradationstate {
	IMG_COMMAND_PIPE_GRADATION_STATE_SUSPENDED,			/* 判定保留 */
	IMG_COMMAND_PIPE_GRADATION_STATE_INGRADATION,		/* グラデーションと判定済み */
} IMG_CommandPipeGradationState;

/*
 * IMG_CommandPipeGradationクラスの定義
 *
 * 本クラスは，追加されたコマンドに対してグラデーション判定を行い
 * コマンド排出時に，その判定結果をタグ情報として後段のフィルタに
 * 通知する機能を持つ。
 */
typedef struct img_commandpipegradation {

	/* Private集約 */

	IMG_Context				*context;
	IMG_DrawingAttributePtr	curAttr;	/* カレントの描画属性 */
	IMG_CommandBiListPtr	cmdList;	/* コマンド蓄積用リスト */
	IMG_DrawSequencePtr		drawSeq;	/* 描画領域の管理 */
	IMG_CommandFilterPtr	next;		/* 後段のフォルタ */

	/* Private属性 */

	IMG_CommandPipeGradationState	state;				/* Gradation判定状態 */
	IMG_UINT32						colorDiffThreshold;	/* 色差の絶対値の閾値 */
	IMG_UINT32						segmentsThreshold;	/* Gradationを構成する領域の閾値 */
	IMG_UINT32						numColorThreshold;	/* 異なる色の数の閾値 */
	IMG_CommandPtr					*brushHistory;		/* Segment内の色の履歴保存領域 */

#ifdef IMG_WRITE_GRADATION_LOG
	/* ログ情報 */
	IMG_GradationDirection	gradDir;			/* Gradationの方向 */
	IMG_BOOL				isInGradation;		/* Gradation内か否か? */
	IMG_INT32				count;				/* Gradation全体のコマンド数 */
	IMG_INT32				nbytes;				/* Gradation全体のバイト数 */
#endif

} IMG_CommandPipeGradation;

/*
 * Public操作
 */

/*
 * 生成
 */
extern IMG_CommandPipeGradationPtr IMG_CommandPipeGradation_Create(
	IMG_Context					*context,				/* 実行コンテキスト */
	IMG_DrawingAttributePtr		attr,					/* 描画属性 */
	IMG_CommandFilterPtr		next,					/* 後段フィルタ */
	IMG_UINT32					colorDiffThreshold,		/* 色差の閾値 */
	IMG_UINT32					segmentsThreshold,		/* 検査する領域数の閾値 */
	IMG_UINT32					numColorThreshold);		/* 異なる色の数の閾値 */

/*
 * 削除
 */
extern int IMG_CommandPipeGradation_Destroy(
	IMG_CommandPipeGradationPtr	self);		/* this pointer */

/*
 * リセット
 */
extern int IMG_CommandPipeGradation_Reset(
	IMG_CommandPipeGradationPtr	self);		/* this pointer */

/*
 * コマンドの追加
 */
extern int IMG_CommandPipeGradation_PutCommand(
	IMG_CommandPipeGradationPtr	self,		/* this pointer */
	IMG_CommandPtr				command);


#endif /* INC_IMG_CommandPipeGradation_h */

/*
 * Log
 * 01.Apr.2004 Yozo Kashima AR#1463(グラデーションの省メモリ化)のため新規作成。
 * 27.May.2004 Yozo Kashima AR#1562(表枠の一部がBGに落ちる)対応。brushHistoryメンバを追加。
 */

/* end of IMG_CommandPipeGradation.h */
