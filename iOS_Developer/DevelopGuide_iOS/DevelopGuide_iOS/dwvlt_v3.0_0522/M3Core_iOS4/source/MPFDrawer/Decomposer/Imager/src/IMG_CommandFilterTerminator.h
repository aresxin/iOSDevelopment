/*
 * Copyright(C) 2001-2003 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandFilterTerminator.h - コマンドフィルタのターミネータクラスの定義
 * Yozo Kashima 01.Dec.2003
 *
 */

#ifndef INC_IMG_CommandFilterTerminator_h
#define INC_IMG_CommandFilterTerminator_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_Job.h"
#include "IMG_Page.h"
#include "IMG_Image.h"
#include "IMG_ImageMask.h"
#include "IMG_ClassPointer.h"
#include "IMG_CommandFilter.h"

typedef struct img_commandfilterterminator {
	IMG_CommandFilter	super;
	/*
	 * Private属性
	 */
	IMG_Page	*page;
} IMG_CommandFilterTerminator;

/*
 * オブジェクトの妥当性検査
 */
extern IMG_BOOL IMG_CommandFilterTerminator_IsValid(
	IMG_CommandFilterTerminator	*self);

/*
 * コンストラクタとデストラクタ
 */

/* public */

/* protected */
extern IMG_CommandFilterPtr IMG_CommandFilterTerminator_Create(
    IMG_Context				*context,			/* コンテキスト */
	IMG_Page				*page,				/* Page */
	IMG_INT32				pageNumber);		/* ページ番号 */

#endif /* INC_IMG_CommandFilterTerminator_h */

/*
 * Log
 * 01.Dec.2003 Yozo Kashima  Created
 */

/* end of IMG_CommandFilterTerminator.h */
