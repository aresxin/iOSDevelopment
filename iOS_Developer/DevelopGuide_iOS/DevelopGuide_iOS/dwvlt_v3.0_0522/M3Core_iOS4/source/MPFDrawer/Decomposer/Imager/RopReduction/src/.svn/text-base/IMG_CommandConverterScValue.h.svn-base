/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverterScValue.h - ソリッドカラー値変換クラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_CommandConverterScValue_h
#define INC_IMG_CommandConverterScValue_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_CommandConverterBrush.h"
#include "IMG_ClassPointer.h"
#include "IMG_Page.h"

/*
 * IMG_CommandConverterScValueクラスの定義
 */
typedef struct img_commandconverterscvalue {
	IMG_CommandConverterBrush	super;
	/*
	 * Private集約
	 */
	IMG_ColorSpace	colorSpace;
	IMG_ColorData	colorData;		/* 設定する色値 */

} IMG_CommandConverterScValue;

/* public */

extern IMG_BOOL IMG_CommandConverterScValue_IsValid(
	IMG_CommandConverterPtr	self);

extern IMG_CommandConverterPtr IMG_CommandConverterScValue_Create(
	IMG_Context			*context,
	IMG_ColorSpace		colorSpace,
	IMG_ColorData		*colorData);

extern int IMG_CommandConverterScValue_Reconstruct(
	IMG_CommandConverterPtr	self);

#endif /* INC_IMG_CommandConverterScValue_h */

/*
 * Log
 *
 * 08.Feb.2002 Yozo Kashima Created.
 */

/* end of IMG_CommandConverterScValue.h */
