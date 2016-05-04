/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverterDiToDm.h - イメージ描画コマンドをイメージマスクに変換して実行するクラスの定義
 */

#ifndef INC_IMG_CommandConverterDiToDm_h
#define INC_IMG_CommandConverterDiToDm_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_CommandConverter.h"
#include "IMG_ClassPointer.h"
#include "IMG_Page.h"

/*
 * IMG_CommandConverterDiToDmクラスの定義
 */
typedef struct img_commandconverterditodm {
	IMG_CommandConverter	super;

	/* Private属性 */
	IMG_PatternPolarity	polarity;
	IMG_BOOL			changeColor;	/* Maskを描画がする直前に色を変更するかどうか */
	IMG_ColorSpace		colorSpace;		/* Mask描画時に使用されるソリッドカラーの色空間 */
	IMG_ColorData		colorData;		/* と色値(共にchangeColorがIMG_TRUEの時のみ有効) */
	IMG_BOOL			drawSmall;		/* 微小なImageMaskを描画するかどうか */
} IMG_CommandConverterDiToDm;

/* public */

extern IMG_BOOL IMG_CommandConverterDiToDm_IsValid(
	IMG_CommandConverterPtr	self);

extern IMG_CommandConverterPtr IMG_CommandConverterDiToDm_Create(
	IMG_Context				*context,
	IMG_PatternPolarity		polarity,
	IMG_BOOL				changeColor,
	IMG_ColorSpace			colorSpace,
	IMG_ColorData			*colorData,
	IMG_BOOL				drawSmall);

extern int IMG_CommandConverterDiToDim_Reconstruct(
	IMG_CommandConverterPtr	self);

#endif /* INC_IMG_CommandConverterDiToDm_h */

/*
 * Log
 *
 * 08.Feb.2002 Yozo Kashima 旧IMG_CommandConverter.hよりブランチ。
 * 10.Jan.2003 Yozo Kashima AR#599対応(QX4006T0,中抜き文字が黒くなる).
 *							Createでクリップの用途か通常描画かを指定する引数と
 *							通常描画時には色情報を指定する引数を追加。
 * 06.Mar.2003 Yozo Kashima AR#1132対応。isClipUsageをchangeColorに名称変更。drawSmall属性を追加。
 */

/* end of IMG_CommandConverterDiToDm.h */
