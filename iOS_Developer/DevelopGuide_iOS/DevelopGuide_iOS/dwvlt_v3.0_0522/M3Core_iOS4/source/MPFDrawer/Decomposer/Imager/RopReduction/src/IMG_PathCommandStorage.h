/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_PathCommandStorage.h - パスコマンド蓄積クラス
 * Yozo Kashima 02.Oct.2001
 *
 */

#ifndef INC_IMG_PathCommandStorage_h
#define INC_IMG_PathCommandStorage_h

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_Command.h"

/*
 * IMG_PathCommandStorageクラスの定義
 */
typedef struct img_pathcommandstorage {
	IMG_Context			*context;
	IMG_CommandListPtr	list;
} IMG_PathCommandStorage;

extern IMG_PathCommandStoragePtr IMG_PathCommandStorage_Create(
	IMG_Context				*context);

extern int IMG_PathCommandStorage_Destroy(
	IMG_PathCommandStoragePtr	self);

extern int IMG_PathCommandStorage_UpdateObject(
	IMG_PathCommandStoragePtr	self);

extern IMG_PathCommandStorage *IMG_PathCommandStorage_Clone(
	IMG_PathCommandStoragePtr	self);

extern int IMG_PathCommandStorage_PutCommand(
	IMG_PathCommandStoragePtr	self,
	IMG_CommandPtr				command);

extern int IMG_PathCommandStorage_RemoveAll(
	IMG_PathCommandStoragePtr	self);

extern int IMG_PathCommandStorage_MoveAllTo(
	IMG_PathCommandStoragePtr	self,
	IMG_PathCommandStoragePtr	target);

extern int IMG_PathCommandStorage_IsEqualTo(
	IMG_PathCommandStoragePtr	self,
	IMG_PathCommandStoragePtr	target,
	IMG_BOOL					*result);

extern int IMG_PathCommandStorage_Execute(
	IMG_PathCommandStoragePtr	self,
	IMG_CommandFilterPtr		filter);

#endif /* INC_IMG_PathCommandStorage_h */

/*
 * Log
 * 02.Oct.2001 Yozo Kashima 障害#88(pb0008g0-09)に対応するために作成。
 * 15.Jan.2003 Yozo Kashima IMG_PathCommandStrage_Executeを追加。
 */

/* end of IMG_PathCommandStorage.h */
