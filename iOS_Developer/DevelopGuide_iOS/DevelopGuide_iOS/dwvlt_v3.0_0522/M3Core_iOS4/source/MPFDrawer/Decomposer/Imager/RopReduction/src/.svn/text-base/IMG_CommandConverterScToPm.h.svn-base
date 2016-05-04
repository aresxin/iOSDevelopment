/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverterScToPm.h - コマンド変換クラスの定義
 * Yozo Kashima 27.Feb.2002
 *
 */

#ifndef INC_IMG_CommandConverterScToPm_h
#define INC_IMG_CommandConverterScToPm_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_CommandConverterBrush.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandConverterScToPmクラスの定義
 */
typedef struct img_commandconvertersctopm {
	IMG_CommandConverterBrush	super;
	/*
	 * Private集約
	 */
	IMG_CommandPtr		patternBrush;		/* 変換の元になるパターンコマンド */
	IMG_PatternPolarity	requestPolarity;	/* 要求極性 */

} IMG_CommandConverterScToPm;

/* public */

extern IMG_BOOL IMG_CommandConverterScToPm_IsValid(
	IMG_CommandConverterPtr	self);

extern IMG_CommandConverterPtr IMG_CommandConverterScToPm_Create(
	IMG_Context				*context,
	IMG_CommandPtr			patternBrush,
	IMG_PatternPolarity		requestPolarity);

extern int IMG_CommandConverterScToPm_Reconstruct(
	IMG_CommandConverterPtr	self);

#endif /* INC_IMG_CommandConverterScToPm_h */

/*
 * Log
 *
 * 08.Feb.2002 Yozo Kashima 旧IMG_CommandConverter.ｈよりブランチ。
 * 04.Apr.2003 Yozo Kashima AR#1186,AR#1187対応(requestPolarityを追加)。
 */

/* end of IMG_CommandConverterScToPm.h */
