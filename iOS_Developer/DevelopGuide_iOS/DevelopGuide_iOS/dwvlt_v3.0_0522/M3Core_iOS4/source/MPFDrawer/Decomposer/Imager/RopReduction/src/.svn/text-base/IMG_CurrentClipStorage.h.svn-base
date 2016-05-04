/*
 * Copyright(C) 2001-2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CurrentClipStorage.h - カレントクリップの蓄積クラスの定義
 * Yozo Kashima 15-Jan-02
 *
 */

#ifndef INC_IMG_CurrentClipStorage_h
#define INC_IMG_CurrentClipStorage_h

#include "IMG_Builtin.h"
#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_ClassPointer.h"

typedef struct img_currentclipstorage {
	IMG_Context					*context;
	/*
	 * パスクリップの論理演算モードはCOPY，矩形クリップの論理演算モードは
	 * ANDである時のみ対応する。従って，クリップの状態は以下の4つのみである。
	 *
	 *								initClip	pathClip	rectClip
	 * 1. なし						Null		Null		Null
	 * 2. InitClip					NotNull		Null		Null
	 * 2. ClipPath					Null		NotNull		Null
	 * 3. ClipPath,Rect1,...,Rectn	Null		NotNull		NotNull
	 * 4. Rect1,...,Rectn			Null		Null		NotNull
	 *
	 */
	IMG_PathCommandStoragePtr	storage;	/* クリップ設定のためのコマンドのリスト */
	IMG_CommandPtr				initMatrix;	/* 初期変換行列 */
	IMG_CommandPtr				curMatrix;	/* カレントの変換行列 */
} IMG_CurrentClipStorage;

extern IMG_CurrentClipStorage *IMG_CurrentClipStorage_Create(
	IMG_Context		*context,				/* コンテキスト */
	IMG_CommandPtr	initMatrix);			/* 初期行列 */

extern int IMG_CurrentClipStorage_Destroy(
	IMG_CurrentClipStoragePtr	self);		/* this pointer */

extern int IMG_CurrentClipStorage_UpdateObject(
	IMG_CurrentClipStoragePtr	self);		/* this pointer */

extern IMG_CurrentClipStorage *IMG_CurrentClipStorage_Clone(
	IMG_CurrentClipStoragePtr	self);		/* this pointer */

extern int IMG_CurrentClipStorage_SetRectangleClip(
	IMG_CurrentClipStoragePtr	self,		/* this pointer */
	IMG_CommandPtr				rectClip);

extern int IMG_CurrentClipStorage_ClipPath(
	IMG_CurrentClipStoragePtr	self,		/* this pointer */
	IMG_CommandPtr				command,
	IMG_PathCommandStoragePtr	rectClip);

extern int IMG_CurrentClipStorage_InitClip(
	IMG_CurrentClipStoragePtr	self,		/* this pointer */
	IMG_CommandPtr				initClip);

extern int IMG_CurrentClipStorage_SetMatrix(
	IMG_CurrentClipStoragePtr	self,		/* this pointer */
	IMG_CommandPtr				setMatrix);

extern int IMG_CurrentClipStorage_Execute(
	IMG_CurrentClipStoragePtr	self,		/* this pointer */
	IMG_CommandFilterPtr		filter);	/* コマンドを受け付けるフィルタ */

#endif /* INC_IMG_CurrentClipStorage_h */

/*
 * Log
 * 15.Jan.2003 Yozo Kashima Created
 * 27.Mar.2003 Yozo Kashima AR#1017,#1083対応。
 *							curMatrixとinitMatrixをメンバ変数に追加し，
 *							CTMとクリップ命令の順序関係を管理する。
 */

/* end of IMG_CurrentClipStorage.h */
