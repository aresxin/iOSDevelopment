/*
 * Copyright(C) 2001-2004 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_ScanlineCombiner.h - 高さ1の矩形群をスキャンラインに纏めるクラスの定義
 *
 * Yozo Kashima 06.Apr.2004
 *
 */

#ifndef INC_IMG_ScanlineCombiner_h
#define INC_IMG_ScanlineCombiner_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"

typedef struct img_scanlinecombiner {
	IMG_Context				*context;
	IMG_CommandFilterPtr	successor;
	IMG_CommandBiListPtr	cmdList;	/* コマンド蓄積用リスト */
	IMG_ScanlineCombinerPtr	next;
	IMG_BOOL				hasAdjacent;
} IMG_ScanlineCombiner;

extern IMG_ScanlineCombinerPtr IMG_ScanlineCombiner_Create(
	IMG_Context				*context,
	IMG_CommandFilterPtr	successor,
	IMG_ScanlineCombinerPtr	next);

extern int IMG_ScanlineCombiner_Destroy(
	IMG_ScanlineCombinerPtr	self);

extern int IMG_ScanlineCombiner_Reset(
	IMG_ScanlineCombinerPtr	self);

extern int IMG_ScanlineCombiner_PutCommand(
	IMG_ScanlineCombinerPtr	self,
	IMG_CommandPtr			cmd,
	IMG_BOOL				*result);

extern int IMG_ScanlineCombiner_CountScanlines(
	IMG_ScanlineCombinerPtr	self,
	IMG_INT32				*nScanlines);

extern int IMG_ScanlineCombiner_IsAdjoining(
	IMG_ScanlineCombinerPtr	self,
	IMG_ScanlineCombinerPtr	target,
	IMG_BOOL				*result);

extern int IMG_ScanlineCombiner_MarkAdjoining(
	IMG_ScanlineCombinerPtr	self);

#endif /* INC_IMG_ScanlineCombiner_h */

/*
 * Log
 * 09.Apr.2004 Yozo Kashima Created(AR#1471 XdwToMRCでJ11_W98_600.XDWを処理すると時間がかかる)
 * 17.May.2004 Yozo Kashima AR#1497(孤立したScanlineの隣接性判定を追加)。
 */

/* end of IMG_ScanlineCombiner.h */
