/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandEvaluator.h - コマンドを部分実行するクラスの定義
 * Yozo Kashima 10.Aug.2001
 *
 */

#ifndef INC_IMG_CommandEvaluator_h
#define INC_IMG_CommandEvaluator_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_CommandList.h"
#include "IMG_ClassPointer.h"
#include "IMG_DrawingAttribute.h"

/*
 * IMG_CommandEvaluatorクラスの定義
 */
typedef struct img_commandevaluator {
	/*
	 * 属性
	 */
	IMG_Context	*context;
	IMG_BOOL	hasIterationStarted;	/* Iterationが開始されているかどうか */

	/*
	 * 関連
	 */
	IMG_CommandSequencePtr	target;			/* 評価対象ステップ */
	IMG_CommandListIterator	itor;			/* リストを走査するIterator */
	IMG_DrawingAttribute	attribute;		/* Iterationされるコマンドによって更新される
												仮想的なカレントの描画属性 */

} IMG_CommandEvaluator;

extern IMG_CommandEvaluatorPtr IMG_CommandEvaluator_Create(
	IMG_Context				*context,
	IMG_CommandSequencePtr	target);

extern int IMG_CommandEvaluator_Construct(
	IMG_CommandEvaluatorPtr	self,
	IMG_Context				*context,
	IMG_CommandSequencePtr	target);

extern int IMG_CommandEvaluator_Destroy(
	IMG_CommandEvaluatorPtr	self);

extern int IMG_CommandEvaluator_Destruct(
	IMG_CommandEvaluatorPtr	self);

/*
 * サービス関数
 */
extern int IMG_CommandEvaluator_IsEqualTo(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandEvaluatorPtr	target,
	IMG_BOOL				*result);

extern int IMG_CommandEvaluator_EvaluateUntil(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandKind			kind);

extern int IMG_CommandEvaluator_EvaluateUntilRealDrawing(
	IMG_CommandEvaluatorPtr	self);

extern int IMG_CommandEvaluator_GetCurrentCommand(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandPtr			*command);

extern int IMG_CommandEvaluator_PeekLatestCommand(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandPtr			*command);

extern int IMG_CommandEvaluator_FindSameCommand(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandPtr			command,
	IMG_CommandKind			kindToStop,
	IMG_CommandPtr			*same);

extern int IMG_CommandEvaluator_IsSameAs(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandEvaluatorPtr	target,
	IMG_BOOL				*isSame);

extern int IMG_CommandEvaluator_IsDrawingWithSolidBlack(
	IMG_CommandEvaluatorPtr	self,
	IMG_BOOL				*isSolidBlack);

extern int IMG_CommandEvaluator_IsDrawingWithBlackAndWhitePattern(
	IMG_CommandEvaluatorPtr	self,
	IMG_BOOL				*isBwPattern);

extern int IMG_CommandEvaluator_GetDrawMode(
	IMG_CommandEvaluatorPtr	self,
	IMG_DrawMode			*drawMode);

extern int IMG_CommandEvaluator_GetBrushCommand(
	IMG_CommandEvaluatorPtr	self,
	IMG_DrawMode			drawMode,
	IMG_CommandPtr			*brushCommand);

/*
 * targetをsourceで置き換える。
 */
extern int IMG_CommandEvaluator_ReplaceCurrent(
	IMG_CommandEvaluatorPtr	self,
	IMG_CommandPtr			source);	/* 置き換えに使うコマンド(IN) */

extern IMG_BOOL IMG_CommandEvaluator_IsValid(
	IMG_CommandEvaluatorPtr	self);

#endif /* INC_IMG_CommandEvaluator_h */

/*
 * Log
 * 10.Aug.2001 Yozo Kashima  Created
 * 27.Aug.2001 Yozo Kashima itorを値で保持。
 * 27.Sep.2001 Yozo Kashima 障害#88(pb0008g0-09)の対応。
 *							IMG_CommandEvaluator_FindSameCommandを追加。
 * 06.Sep.2002 Yozo Kashima IMG_CommandEvaluator_EvaluateUntilRealDrawingを追加(障害#11:vi0009i0.prn)。
 */

/* end of IMG_CommandEvaluator.h */
