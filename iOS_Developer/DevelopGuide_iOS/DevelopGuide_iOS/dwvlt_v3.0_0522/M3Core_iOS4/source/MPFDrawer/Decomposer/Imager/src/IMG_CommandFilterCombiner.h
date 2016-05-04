/*
 * Copyright(C) 2001-2004 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandFilterCombiner.h - 連続する高さ1の矩形を検出しScanline化するフィルタクラスの定義
 *
 * Yozo Kashima 09.Apr.2004
 */

#ifndef INC_IMG_CommandFilterCombiner_h
#define INC_IMG_CommandFilterCombiner_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_CommandFilter.h"

typedef struct img_commandfiltercombiner {
	IMG_CommandFilter	super;

	IMG_ScanlineCombinerPtr	scanline;

} IMG_CommandFilterCombiner;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandFilterCombiner_IsValid(
	IMG_CommandFilterCombinerPtr	self);

/*
 * コンストラクタとデストラクタ
 */

/* public */

/* protected */
extern IMG_CommandFilterPtr IMG_CommandFilterCombiner_Create(
    IMG_Context				*context,			/* コンテキスト */
	IMG_INT32				pageNumber,			/* Page番号 */
	IMG_CommandFilterPtr	successor);			/* 後続フィルタ */

#endif /* INC_IMG_CommandFilterCombiner_h */

/*
 * Log
 * 09.Apr.2004 Yozo Kashima Created(AR#1471 XdwToMRCでJ11_W98_600.XDWを処理すると時間がかかる)
 */

/* end of IMG_CommandFilterCombiner.h */
