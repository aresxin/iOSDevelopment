/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_ProcCorrect.h	色補正処理モジュールヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	May,28,2001	Toshio Yamazaki
 */
#include "CST_IF.h"

#ifndef CST_PROCCORRECT_H_INCLUDED
#define CST_PROCCORRECT_H_INCLUDED

/*
 * I/F の宣言
 */
int CST_ProcRGBCorrect_TransValueWithTag( CST_RGBcrParaData *,
					  unsigned char *, CST_TagName );
int CST_ProcRGBCorrect_TransBufferWithTag( CST_RGBcrParaData *,
					   CST_PixelBufferInfo *,
					   CST_PixelBufferInfo *,
					   CST_TagName );

int CST_ProcLCCCorrect_TransValueWithTag( CST_LCCcrParaData *,
					  unsigned char *, CST_TagName );
int CST_ProcLCCCorrect_TransBufferWithTag( CST_LCCcrParaData *,
					   CST_PixelBufferInfo *,
					   CST_PixelBufferInfo *,
					   CST_TagName );

int CST_ProcLCCCorrectsGray_TransValueWithTag( CST_LCCcrParaData *,
					       unsigned char *, CST_TagName );
int CST_ProcLCCCorrectsGray_TransBufferWithTag( CST_LCCcrParaData *,
						CST_PixelBufferInfo *,
						CST_PixelBufferInfo *,
						CST_TagName );
int CST_ProcICCCorrect_TransValueWithTag( CST_ICCProfileData *,
					  unsigned char *, CST_TagName );
int CST_ProcICCCorrect_TransBufferWithTag( CST_ICCProfileData *,
					   CST_PixelBufferInfo *,
					   CST_PixelBufferInfo *,
					   CST_TagName );

#endif /* CST_PROCCORRECT_H_INCLUDED */
