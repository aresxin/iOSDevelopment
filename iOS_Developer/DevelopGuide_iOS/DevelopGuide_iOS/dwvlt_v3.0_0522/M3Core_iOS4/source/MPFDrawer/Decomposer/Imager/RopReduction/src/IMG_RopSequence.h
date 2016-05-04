/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_RopSequence.h - ROP描画シーケンスの抽象クラス
 * Yozo Kashima 20.Jul.2001
 *
 */

#ifndef INC_IMG_RopSequence_h
#define INC_IMG_RopSequence_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Page.h"
#include "IMG_RopReduceConfig.h"
#include "IMG_ClassPointer.h"
#include "IMG_RopDataConversionLib.h"

/*
 * ROPコードの定義
 */

/* ROP2 */
#define IMG_R2_DPx		7		/* R2_XORPEN */
#define IMG_R2_DPa		9		/* R2_MASKPEN */
#define IMG_R2_D		11		/* R2_NOP */
#define IMG_R2_P		13		/* R2_COPYPEN */
#define IMG_R2_DPo		15		/* R2_MERGEPEN */

/* ROP3 */
#define IMG_R3_DSna		34		/* 0x22 */
#define IMG_R3_DSx		102		/* 0x66 */
#define IMG_R3_DSa		136		/* 0x88 */
#define IMG_R3_PSDPxax	184		/* 0xB8 */
#define IMG_R3_D		170		/* 0xAA */
#define IMG_R3_DSno		187		/* 0xBB */
#define IMG_R3_DSPDxax	226		/* 0xE2 */
#define IMG_R3_DSo		238		/* 0xEE */

/*
 * 置換対象ROPパターンの切り替えスイッチ
 *
 * HostBasedDrv
 *   常に全てのパターンを置換対象とする
 *
 * DocuWorksViewer
 *   IMG_ROP_REPLACEMENT_ALLが定義されているとき
 *     全てのパターンを置換対象とする
 *
 *   IMG_ROP_REPLACEMENT_ALLが定義されていないとき
 *   以下のパターンのみ置換対象とする
 *     R3_PSDPxax
 *     R3_DSPDxax
 */

/*
#define IMG_ROP_REPLACEMENT_ALL
*/

/* 1Step */
#define IMG_ROP_REDUCTION_R3_PSDPxax
#define IMG_ROP_REDUCTION_R3_DSPDxax

#if ( !defined(DOCUWORKS_VIEWER) || defined(IMG_ROP_REPLACEMENT_ALL) )
#define IMG_ROP_REDUCTION_R3_DSa
#define IMG_ROP_REDUCTION_R3_DSno

/* 1Step Nop */
#define IMG_ROP_REDUCTION_R2_D
#define IMG_ROP_REDUCTION_R3_D

/* 2Step */
#define IMG_ROP_REDUCTION_R3_DSa_R3_DSx
#define IMG_ROP_REDUCTION_R3_DSa_R3_DSo
#define IMG_ROP_REDUCTION_R3_DSo_R3_DSa
#define IMG_ROP_REDUCTION_R3_DSna_R3_DSo

/* 3Step */
#define IMG_ROP_REDUCTION_R2_DPx_R2_P_R2_DPx
#define IMG_ROP_REDUCTION_R2_DPx_R2_DPa_R2_DPx_BWPATTERN
#define IMG_ROP_REDUCTION_R2_DPx_R2_DPa_R2_DPx_SOLIDBLACK
#define IMG_ROP_REDUCTION_R3_DSx_R2_P_R3_DSx
#define IMG_ROP_REDUCTION_R2_DPx_R3_DSa_R2_DPx
#define IMG_ROP_REDUCTION_R3_DSx_R3_DSa_R3_DSx

/* 4Step */
#define IMG_ROP_REDUCTION_R3_DSx_R2_P_R3_DSx_R2_DPo

#endif


/*
 * ROP置換方式IDの定義
 *
 * このIDはサブクラス毎に用意する。
 * オブジェクトの再構築時に必要となる。
 */
typedef enum img_ropsequenceid {
	IMG_ROP_SEQUENCE_ID_NULL,			/* 定義なし */
	IMG_ROP_SEQUENCE_ID_1STEP,
	IMG_ROP_SEQUENCE_ID_1STEP_NO_DRAW,
	IMG_ROP_SEQUENCE_ID_2STEP,
	IMG_ROP_SEQUENCE_ID_3STEP,
	IMG_ROP_SEQUENCE_ID_4STEP,
} IMG_RopSequenceID;

/*
 * ROPステップの用途
 */
typedef enum img_ropstepusage {
	IMG_USAGE_NULL			= 0x00,			/* 未定義 */
	IMG_USAGE_DRAW			= 0x01,			/* 通常の描画として使用 */
	IMG_USAGE_CLIP			= 0x02,			/* グラフィック又はイメージによるクリップ指定として使用 */
	IMG_USAGE_CLIP_MASK		= 0x04,			/* グラフィックを黒と白のパターンで塗り潰したマスクとして使用 */
	IMG_USAGE_NODRAW		= 0x08,			/* 描画命令だけは実行しないシーケンス */
} IMG_RopStepUsage;

/*
 * IMG_RopSequenceのステータスコード
 */
typedef enum img_ropsequencestatuscode {
	IMG_ROP_SEQUENCE_OK,			/* 次のステップも処理可能 */
	IMG_ROP_SEQUENCE_NG,			/* 次のステップは処理不可能 */
	IMG_ROP_SEQUENCE_DONTCARE,		/* 次のステップは関知せず */
} IMG_RopSequenceStatusCode;

/*
 * IMG_RopSequenceのステータス
 */
typedef struct img_ropsequencestatus {
	IMG_RopSequenceStatusCode	code;		/* ステータスコード */
	const char					*reason;	/* ステータスがNGになる理由を示す文字列 */
	IMG_CommandPtr				failCmd;	/* NGの原因コマンド */
} IMG_RopSequenceStatus;

/*
 * ROPステップの検査項目
 */
typedef enum img_ropstepcheck {
	IMG_CHECK_NULL			= 0,	/* 検査なし */
	IMG_CHECK_BLACKNESS,			/* 黒で描画することを検査(イメージの場合は白も含む) */
	IMG_CHECK_BWPATTERN,			/* 白黒パターンで描画すること */
	IMG_CHECK_EQUAL,				/* 2つのステップの描画結果が同一になること */
	IMG_CHECK_SHAPE_EQUAL,			/* 2つのステップの描画形状が同一になること */
} IMG_RopStepCheck;

/*
 * ROPステップの仕様記述構造体
 */
typedef struct img_ropstepspec {
	IMG_RopMode			ropMode;			/* ROPモード(ROP2 or ROP3) */
	IMG_UINT32			ropCode;			/* ROPコード */
	IMG_BOOL			mandatory;			/* このステップが必須かどうか */
	IMG_RopStepCheck	check;				/* このステップの検査項目 */
	IMG_INT32			compareStepIndex;	/* 比較対象ステップのインデックス値(0以上が有効値)。
											   checkメンバーで2つのステップの比較を指定した時のみ有効 */
	IMG_RopStepUsage	usage;				/* ステップの用途 */
	IMG_PatternPolarity	polarity;			/* クリップとして使用される時のイメージの極性 
											   検査対象ステップがイメージを使うROP3の場合のみ有効 */
} IMG_RopStepSpec;


/*
 * ROPステップとその仕様記述構造体のペア
 */
typedef struct img_ropstep {
	const IMG_RopStepSpec	*spec;
	IMG_CommandSequencePtr	step;
} IMG_RopStep;

/*
 * IMG_RopSequenceクラスの定義
 */
typedef struct img_ropsequence {
	/* public操作 */

	/* abstract */
	int (*destroy)(
		IMG_RopSequencePtr	self);				/* this pointer */

	/*
	 * ROPの置き換えを実行する。
	 */
	int (*replace)(
		IMG_RopSequencePtr		self,			/* this pointer */
		IMG_CommandFilterPtr	filter);		/* コマンドを受け付けるフィルタ */

	/* protected操作 */

	/* abstract */
	/*
	 * ROPの置き換えを直ちに置き換えることができるかどうかを検査する。
	 * 置換可能ならばisOkにIMG_TRUEを，置換不可能ならばIMG_FALSEをセットする。
	 * 本操作は，置換可能であることがまだ検出されていない状態で呼び出される。
	 * 本操作を呼び出すことにより，置換可能であることが検出された後は本操作は
	 * 呼び出されない。
	 */
	int (*canReplaceNow)(
		IMG_RopSequencePtr	self,
		IMG_BOOL			*isOk);

	/* virtual */

	const IMG_RopDataConvLib_PixelMap* (*getProhibitedPixelMap)(
		IMG_RopSequencePtr	self,
		IMG_UINT32			specNo);


	/* protected属性 */

	IMG_Context				*context;			/* 実行環境コンテキスト */

	/* private属性 */

	/* 構築時に一意に決まるもの */

	IMG_RopSequenceID		id;					/* サブクラス識別子 */
	/*
	 * specArray =
	 *   { モードとコード, 必須か否か, ステップの検査項目, 比較対象ステップ, 極性 },  ↑
	 *                                      ...										  ｜
	 *                                          									  ｜maxRopStep
	 *                                      ...										  ｜
	 *   { モードとコード, 必須か否か, ステップの検査項目, 比較対象ステップ, 極性 }   ↓
	 */
	const IMG_RopStepSpec	*specArray;		/* ROPシーケンス仕様の配列 */
	IMG_INT32				maxRopStep;		/* ROPシーケンスのステップの最大値 */
	IMG_INT32				specID;			/* ROPシーケンス仕様のID */

	/*
	 * idとspecIDついて
	 * idは本クラスのサブクラスのID，specIDはサブクラス内でユニークな
	 * ROPシーケンス仕様のIDである。
	 */

	/* 構築後変化するもの */
	IMG_INT32				stepIndex;		/* ROPシーケンス内の現ステップ番号(0以上が有効値) */
	IMG_BOOL				isTerminated;	/* 終了命令を受けたか? */
	IMG_BOOL				isReplacable;	/* 置換可能状態か? */

	/* protected関連 */

	IMG_RopStep				ropSteps[IMG_MAX_ROP_STEP];	/* 各ROPステップの情報 */
	IMG_RopReducerPtr		reducer;
	IMG_CommandPtr			lastCmd;			/* 置換に関わる最後のコマンド */
	IMG_DrawingAttributePtr	snapShot;			/* 置換可能になった時点のROPステップの描画属性 */

	/* private関連 */

	IMG_CommandCheckPtr		commandCheck;		/* カレントのコマンド検査オブジェクト */

} IMG_RopSequence;

/*
 * インライン関数
 */

/*
 * 処理するステップの最大数を取得する。
 */
static IMG_INT32 IMG_RopSequence_MaxNStep(
	IMG_RopSequencePtr	self)
{
	return self->maxRopStep;
}

/*
 * 現在処理中のステップ数を取得する。
 */
static IMG_UINT32 IMG_RopSequence_CurNStep(
	IMG_RopSequencePtr	self)
{
	return self->stepIndex + 1;
}

/*
 * コンストラクタ
 */
extern int IMG_RopSequence_Construct(
	IMG_RopSequencePtr		self,				/* this pointer */
	IMG_Context				*context,			/* 実行環境コンテキスト */
	IMG_RopSequenceID		id,					/* サブクラス識別子 */
	IMG_RopReducerPtr		reducer,			/* RopReducer */
	const IMG_RopStepSpec	*specArray,			/* ROPステップ仕様配列 */
	IMG_UINT32				maxRopStep,			/* ROPステップの最大数 */
	IMG_INT32				specID,				/* ROPステップ仕様配列のID */
	IMG_CommandSequencePtr	initStep);			/* 第1ステップ */

extern int IMG_RopSequence_Reconstruct(
	IMG_RopSequencePtr		self,				/* this pointer */
	const IMG_RopStepSpec	*specArray);		/* ROPステップ仕様配列 */

/*
 * デストラクタ
 */
extern int IMG_RopSequence_Destruct(
	IMG_RopSequencePtr		self);

/*
 * サービス関数
 */

extern IMG_BOOL IMG_RopSequence_IsValid(
	IMG_RopSequencePtr		self);

/* public */

extern int IMG_RopSequence_EndOfStep(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_RopSequenceStatus	*status);	/* ステータスコード */

extern int IMG_RopSequence_NextCommand(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_RopSequenceStatus	*status);	/* ステータスコード */

extern int IMG_RopSequence_GotoNextStep(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_CommandSequencePtr	nextStep,	/* 次のステップ */
	IMG_RopSequenceStatus	*status);	/* ステータスコード */

extern int IMG_RopSequence_Select(
	IMG_RopSequencePtr		self);			/* this pointer */

extern int IMG_RopSequence_CanReplaceNow(
	IMG_RopSequencePtr		self,			/* this pointer */
	IMG_BOOL				*isOk);			/* 置換可能かどうか? */

extern int IMG_RopSequence_Replace(
	IMG_RopSequencePtr		self,			/* this pointer */
	IMG_CommandFilterPtr	filter);		/* コマンドを受け付けるフィルタ */

extern int IMG_RopSequence_Terminate(
	IMG_RopSequencePtr		self);			/* this pointer */

extern int IMG_RopSequence_IsTerminated(
	IMG_RopSequencePtr		self,			/* this pointer */
	IMG_BOOL				*isTerminated);	/* 終了通知を受けたか? */

/*
 * インライン(されるであろう)関数
 */
static IMG_RopSequenceID IMG_RopSequence_GetID(
	IMG_RopSequencePtr		self)			/* this pointer */
{
	return self->id;
}

static IMG_CommandCheckPtr IMG_RopSequence_GetCommandCheck(
	IMG_RopSequencePtr		self)			/* this pointer */
{
	return self->commandCheck;
}

/*
 * 以下は本クラスのサブクラスでのみ参照できる宣言。
 */
extern IMG_BOOL IMG_RopSequence_IsSupported(
	IMG_RopMode				ropMode,
	IMG_UINT32				ropCode,
	const IMG_RopStepSpec	*spec,
	IMG_INT32				numOfSeq,
	IMG_INT32				numOfSpecs);

extern int IMG_RopSequence_FindStep(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_RopStepUsage		usage,		/* 検索するシーケンスの用途 */
	IMG_INT32				order,		/* 用途に合致したシーケンスの中での出現順序 */
	IMG_CommandSequencePtr	*step);		/* 検索されたステップ */

extern const IMG_RopStepSpec *IMG_RopSequence_FindSpecOf(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_CommandSequencePtr	step);

extern int IMG_RopSequence_DestroyStep(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_CommandSequencePtr	step);		/* 削除すべきステップ */

extern int IMG_RopSequence_GetCurrentAttribute(
	IMG_RopSequencePtr		self,		/* this pointer */
	IMG_DrawingAttributePtr	*attr);		/* カレントの描画属性 */

/* virtual */
extern const IMG_RopDataConvLib_PixelMap* IMG_RopSequence_GetProhibitedPixelMap(
	IMG_RopSequencePtr		self,
	IMG_UINT32				specNo);

#endif /* INC_IMG_RopSequence_h */

/*
 * Log
 * 20.Jul.2001 Yozo Kashima  Created
 * 20.Aug.2001 Yozo Kashima IMG_ROP_SEQUENCE_GET_PAGE_NUMBERマクロを追加。
 * 15.Oct.2001 Yozo Kashima IMG_RopSequence1Stepクラスの追加に伴い、IMG_RopSequence3Stepとの共通部分を本クラスに抽出。
 * 16.Nov.2001 Yozo Kashima 2StepROPの置換処理を実装。
 *							IMG_RopStepSpecにpolarityを追加。
 * 06.Mar.2003 Yozo Kashima AR#1132対応。置換するROPパターンを個別に切り替えるマクロを導入。
 * 14.Jul.2003 Yozo Kashima AR#1392対応(ROP3-187(DSno)のifdefのマクロ名を修正)。
 * 20.Jul.2003 Yozo Kashima Hakugin対応(対応候補オブジェクトの多重化対応)
 */

/* end of IMG_RopSequence.h */
