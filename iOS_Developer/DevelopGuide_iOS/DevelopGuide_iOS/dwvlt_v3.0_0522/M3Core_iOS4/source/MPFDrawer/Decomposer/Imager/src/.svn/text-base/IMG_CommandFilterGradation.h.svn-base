/*
 * Copyright(C) 2001-2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandFilterGradation.h - グラデーションを検知するコマンドフィルタクラスの定義
 *
 * Yozo Kashima 01.Dec.2003
 *
 */

#ifndef INC_IMG_CommandFilterGradation_h
#define INC_IMG_CommandFilterGradation_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Job.h"
#include "IMG_Page.h"
#include "IMG_Image.h"
#include "IMG_ImageMask.h"
#include "IMG_ClassPointer.h"
#include "IMG_CommandFilter.h"

typedef struct img_commandfiltergradation {
	IMG_CommandFilter	super;

	IMG_DrawingAttributePtr		curAttr;
	IMG_CommandPipeGradationPtr	pipe;

	IMG_UINT32 segmentsThreshold;		/* グラデーションを構成するセグメントの数の閾値 */
	IMG_UINT32 colorDiffThreshold;		/* グラデーションを構成するセグメントの色差の閾値 */
	IMG_UINT32 numColorThreshold;		/* グラデーションを構成するセグメント内の色数の閾値 */
} IMG_CommandFilterGradation;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandFilterGradation_IsValid(
	IMG_CommandFilterGradation	*self);

/*
 * コンストラクタとデストラクタ
 */

/* public */

/* protected */
extern IMG_CommandFilterPtr IMG_CommandFilterGradation_Create(
    IMG_Context				*context,			/* コンテキスト */
	IMG_INT32				pageNumber,			/* Page番号 */
	IMG_CommandFilterPtr	successor);			/* 後続フィルタ */

#endif /* INC_IMG_CommandFilterGradation_h */

/*
 * Log
 * 01.Dec.2003 Yozo Kashima  Created
 * 01.Apr.2004 Yozo Kashima AR#1463(グラデーションの省メモリ化)
 * 27.May.2004 Yozo Kashima AR#1562(表枠の一部がBGに落ちる)対応。Segment内の色値が閾値
 */

/* end of IMG_CommandFilterGradation.h */
