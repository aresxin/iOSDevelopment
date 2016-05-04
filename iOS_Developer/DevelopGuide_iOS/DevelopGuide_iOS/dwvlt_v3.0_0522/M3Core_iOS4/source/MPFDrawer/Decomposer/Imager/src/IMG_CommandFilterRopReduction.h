/*
 * Copyright(C) 2001-2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandFilterRopReduction.h - ROP置換を行うコマンドフィルタクラスの定義
 * Yozo Kashima 01.Dec.2003
 *
 */

#ifndef INC_IMG_CommandFilterRopReduction_h
#define INC_IMG_CommandFilterRopReduction_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_CommandFilter.h"

typedef enum {
		IMG_COMMAND_FILTER_ROP_REDUCTION_STATE_NORMAL,
		IMG_COMMAND_FILTER_ROP_REDUCTION_STATE_REPLACING,
		IMG_COMMAND_FILTER_ROP_REDUCTION_STATE_JUST_REPLACED
} IMG_CommandFilterRopReductionState;

typedef struct img_commandfilterropreduction {
	IMG_CommandFilter	super;
	/*
	 * 属性
	 */
	IMG_RopMode					currentRopMode;
	IMG_UINT32					currentRopCode;
	IMG_CommandFilterRopReductionState state;
	IMG_DrawingAttributePtr		currentAttr;	/* カレントの描画属性 */

	/*
	 * 関連
	 */
	IMG_RopReducerPtr	ropReducer;

} IMG_CommandFilterRopReduction;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandFilterRopReduction_IsValid(
	IMG_CommandFilterRopReduction	*self);

/*
 * コンストラクタとデストラクタ
 */

/* public */

/* protected */
extern IMG_CommandFilterPtr IMG_CommandFilterRopReduction_Create(
    IMG_Context				*context,			/* コンテキスト */
	IMG_INT32				pageNumber,			/* Page番号 */
	IMG_CommandFilterPtr	successor);			/* 後続フィルタ */

#endif /* INC_IMG_CommandFilterRopReduction_h */

/*
 * Log
 * 01.Dec.2003 Yozo Kashima  Created
 */

/* end of IMG_CommandFilterRopReduction.h */
