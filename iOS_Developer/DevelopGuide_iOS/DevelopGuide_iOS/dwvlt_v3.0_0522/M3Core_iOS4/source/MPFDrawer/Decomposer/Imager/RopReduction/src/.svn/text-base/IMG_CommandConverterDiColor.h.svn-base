/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverterDiColor.h - イメージの描画色変換クラスの定義
 */

#ifndef INC_IMG_CommandConverterDiColor_h
#define INC_IMG_CommandConverterDiColor_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_CommandConverter.h"

/*
 * IMG_CommandConverterDiColorクラスの定義
 *
 * 本クラスを使うと白黒イメージに色を付けて描画することができる。
 */
typedef struct img_commandconverterdicolor {

	IMG_CommandConverter	super;
	
	/*
	 * Private集約
	 */
	IMG_ColorSpace	colorSpace;		/* colorDataの色空間 */
	IMG_ColorData	colorData;		/* 設定する色値 */
	IMG_BOOL		changeWhite;	/* 白黒イメージの白ピクセルに色を付けるか?
									   TRUEなら白ピクセルに，FALSEなら黒ピクセルに
									   色を付ける */
} IMG_CommandConverterDiColor;

/* public */

extern IMG_BOOL IMG_CommandConverterDiColor_IsValid(
	IMG_CommandConverterPtr	self);

extern IMG_CommandConverterPtr IMG_CommandConverterDiColor_Create(
	IMG_Context			*context,
	IMG_ColorSpace		colorSpace,
	IMG_ColorData		*colorData,
	IMG_BOOL			changeWhite);

extern int IMG_CommandConverterDiColor_Reconstruct(
	IMG_CommandConverterPtr	self);

#endif /* INC_IMG_CommandConverterDiColor_h */

/*
 * Log
 * 27.Feb.2002 Yozo Kashima Created
 */

/* end of IMG_CommandConverterDiColor.h */
