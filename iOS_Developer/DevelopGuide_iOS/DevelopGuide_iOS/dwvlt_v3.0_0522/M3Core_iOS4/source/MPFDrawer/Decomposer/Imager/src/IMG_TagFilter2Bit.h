/*
 * Copyright(C) 2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_TagFilter2Bit.h - 2ビットのタグフィルタークラスの定義
 * Yozo Kashima 26.Nov.2003
 *
 */
#ifndef INC_IMG_TagFilter2Bit_h
#define INC_IMG_TagFilter2Bit_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_TagFilter.h"

/*
 * IMG_TagFilter2Bitクラスの定義
 */
typedef struct img_tagfilter2bit {
	IMG_TagFilter			super;			/* Super Class */
} IMG_TagFilter2Bit;

/* public */

/*
 * 生成
 */
extern IMG_TagFilterPtr IMG_TagFilter2Bit_Create(
	IMG_Context			*context,			/* 実行コンテキスト */
	IMG_DisplayList		*displayList);

#endif /* INC_IMG_TagFilter2Bit_h */

/*
 * Log
 * 26.Nov.2003 Yozo Kashima  Created

 */

/* end of IMG_TagFilter2Bit.h */
