/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_UpdateAbstractObject.h - 抽象オブジェクトの再構築
 *
 */

#ifndef INC_IMG_UpdateAbstractObject_h
#define INC_IMG_UpdateAbstractObject_h

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"

extern int IMG_UpdateAbstractObject_UpdateRopSequence(
	IMG_RopSequencePtr	ropSequence);

extern int IMG_UpdateAbstractObject_UpdateCommandCheck(
	IMG_CommandCheckPtr	cmdCheck);

extern int IMG_UpdateAbstractObject_UpdateCommand(
	IMG_CommandPtr		cmd);

#endif /* INC_IMG_UpdateAbstractObject_h */

/*
 * Log
 * 27.Feb.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_UpdateAbstractObject.h */
