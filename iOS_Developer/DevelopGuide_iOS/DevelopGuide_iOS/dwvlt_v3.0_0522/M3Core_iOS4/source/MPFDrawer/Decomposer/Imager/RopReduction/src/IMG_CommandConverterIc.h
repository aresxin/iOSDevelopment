/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverterIc.h - クリップ初期化コマンドの変換クラスの定義
 */

#ifndef INC_IMG_CommandConverterIc_h
#define INC_IMG_CommandConverterIc_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Page.h"
#include "IMG_CommandConverter.h"
#include "IMG_ClassPointer.h"

 /*
 * IMG_CommandConverterIcクラスの定義
 */
typedef struct img_commandconverteric {
	IMG_CommandConverter	super;

	/* Private関連 */
	IMG_CommandSequencePtr	clipStep;			/* 初期クリップを構築するコマンドを含むステップ */
	
	/* Private属性 */
	IMG_BOOL				isInitClipSaved;	/* 初期クリップが生成され保存されているか */
	IMG_PatternPolarity		polarity;			/* 極性(clipStepがイメージコマンドからなる時のみ有効) */
} IMG_CommandConverterIc;


/* public操作 */

extern IMG_CommandConverterPtr IMG_CommandConverterIc_Create(
	IMG_Context				*context,		/* 実行環境コンテキスト */
	IMG_CommandSequencePtr	clipStep,		/* 初期クリップを構築するコマンドを含むステップ */
	IMG_PatternPolarity		polarity);		/* 極性(clipStepがイメージコマンドからなる時のみ有効) */

extern int IMG_CommandConverterIc_Reconstruct(
	IMG_CommandConverterPtr	self);

#endif /* INC_IMG_CommandConverterIc_h */

/*
 * Log
 *
 * 08.Feb.2002 Yozo Kashima 旧IMG_CommandConverter.ｈよりブランチ。
 */

/* end of IMG_CommandConverterIc.h */
