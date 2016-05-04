/*
 * Copyright(C) 2001-2004 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_DrawSequence.h - グラデーション検出における描画セグメント管理クラスの定義
 */

#ifndef INC_IMG_DrawSequence_h
#define INC_IMG_DrawSequence_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_DrawSequenceクラスの定義
 *
 * 本クラスは，描画セグメント(同一色で描画される領域)単位で
 * 描画コマンドとソリッドカラー設定コマンドを管理する機能を持つ。
 *
 * 本クラスでは，最も古いコマンドが先頭，最も新しいコマンドが最後尾に
 * なるようにコマンドを蓄積する。
 */

typedef struct img_drawsequence {
	IMG_Context				*context;		/* コンテキスト */
	IMG_UINT32				capacity;		/* 保存する描画セグメントの制限値 */
	IMG_UINT32				size;			/* 現在のdrawArea数 */
	IMG_CommandBiListPtr	areaBeginList;	/* 描画セグメントの先頭 */
	IMG_CommandBiListPtr	areaEndList;	/* 描画セグメントの最後尾 */
	IMG_CommandBiListPtr	drawCmdList;	/* 描画コマンドの系列 */
	IMG_CommandBiListPtr	brushCmdList;	/* 色指定コマンドの系列(drawCmdと1対1に対応) */
} IMG_DrawSequence;

/*
 * 生成
 */
extern IMG_DrawSequencePtr IMG_DrawSequence_Create(
	IMG_Context			*context,	/* コンテキスト */
	IMG_UINT32			capacity);	/* 保存する描画セグメントの制限値 */

/*
 * 削除
 */
extern int IMG_DrawSequence_Destroy(
	IMG_DrawSequencePtr	self);

/*
 * 蓄積済みの描画セグメント情報をすべてクリヤーする。
 */
extern int IMG_DrawSequence_Clear(
	IMG_DrawSequencePtr	self);

/*
 * 現在蓄積済みの描画セグメントの数を取得する。
 */
extern int IMG_DrawSequence_Count(
	IMG_DrawSequencePtr	self,
	IMG_UINT32			*nDrawArea);

/*
 * 新しい描画コマンドとその色指定コマンドを追加する。
 */
extern int IMG_DrawSequence_AddNew(
	IMG_DrawSequencePtr	self,
	IMG_CommandPtr		draw,
	IMG_CommandPtr		brush);

/*
 * 最も新しい描画コマンドとその色指定コマンドを取得する。
 * 削除はしない。
 */
extern int IMG_DrawSequence_GetNew(
	IMG_DrawSequencePtr	self,
	IMG_CommandPtr		*draw,
	IMG_CommandPtr		*brush);

/*
 * 最も新しい描画コマンドとその色指定コマンドを削除する。
 */
extern int IMG_DrawSequence_PopNew(
	IMG_DrawSequencePtr	self);

/*
 * 最も古い描画セグメントを削除する。
 * 結果として，最も古い描画セグメントの先頭描画コマンドと
 * 最後尾描画コマンドが得られる。
 */
extern int IMG_DrawSequence_PopOldSegment(
	IMG_DrawSequencePtr	self,
	IMG_CommandPtr		*drawBegin,
	IMG_CommandPtr		*drawEnd);

#endif /* INC_IMG_DrawSequence_h */

/*
 * Log
 * 25.Fed.2004 Yozo Kashima Created
 */

/* end of IMG_Context.h */

