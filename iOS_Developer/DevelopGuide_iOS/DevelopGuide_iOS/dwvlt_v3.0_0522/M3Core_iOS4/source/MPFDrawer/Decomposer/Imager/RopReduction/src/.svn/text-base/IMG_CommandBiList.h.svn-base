/*
 * Copyright(C) 2001−2004 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandBiList.h - コマンドの双方向リストクラスの定義
 */

#ifndef INC_IMG_CommandBiList_h
#define INC_IMG_CommandBiList_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_ClassPointer.h"

/*-------------------------------------------------------------------------
  Item管理
-------------------------------------------------------------------------*/

/*
 * IMG_CommandBiListItemクラスの定義
 */
typedef struct img_commandbilistitem {
	struct img_commandbilistitem	*prev;
	struct img_commandbilistitem	*next;
	IMG_CommandPtr					command;
} IMG_CommandBiListItem;

/*
 * IMG_CommandBiListItemPoolクラスの定義
 */
#define IMG_COMMAND_BILIST_ITEM_MAX	128

typedef struct img_commandbilistitempool {
	struct img_commandbilistitempool	*next;
	IMG_CommandBiListItem				items[IMG_COMMAND_BILIST_ITEM_MAX];
	int									freeIndex;
} IMG_CommandBiListItemPool;

/*-------------------------------------------------------------------------
  List本体
-------------------------------------------------------------------------*/
/*
 * IMG_CommandBiListクラスの定義
 */
typedef struct img_commandbilist {
	IMG_Context					*context;
    IMG_CommandBiListItem		*top;
	IMG_CommandBiListItem		*tail;
	IMG_CommandBiListItemPool	*pool;
	IMG_INT32					size;
} IMG_CommandBiList;

extern IMG_BOOL IMG_CommandBiList_IsValid(
	IMG_CommandBiList	*self);

extern IMG_CommandBiList *IMG_CommandBiList_Create(
	IMG_Context *context);

extern int IMG_CommandBiList_Destroy(
	IMG_CommandBiList *self);

/*
 * サービス関数
 */
extern int IMG_CommandBiList_PopFront(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			*command);

extern int IMG_CommandBiList_PopBack(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			*command);

extern int IMG_CommandBiList_PushFront(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			command);

extern int IMG_CommandBiList_PushBack(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			command);

extern int IMG_CommandBiList_ExchangeFront(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			command,
	IMG_CommandPtr			*old);

extern int IMG_CommandBiList_ExchangeBack(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			command,
	IMG_CommandPtr			*old);

extern int IMG_CommandBiList_Front(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			*command);

extern int IMG_CommandBiList_Back(
	IMG_CommandBiListPtr	self,
	IMG_CommandPtr			*command);

extern int IMG_CommandBiList_IsEqualTo(
	IMG_CommandBiListPtr	self,
	IMG_CommandBiListPtr	target,
	IMG_BOOL				*result);

extern int IMG_CommandBiList_Empty(
	IMG_CommandBiListPtr	self,
	IMG_BOOL				*isEmpty);

extern int IMG_CommandBiList_Clear(
	IMG_CommandBiListPtr	self);

extern int IMG_CommandBiList_Count(
	IMG_CommandBiListPtr	self,
	IMG_INT32				*count);

/*-------------------------------------------------------------------------
  IMG_CommandBiListIteratorForwardクラス
-------------------------------------------------------------------------*/
/*
 * IMG_CommandBiListIteratorForwardクラスの定義
 */
typedef struct img_commandbilistiteratorforward {
	IMG_CommandBiListPtr		list;
	IMG_CommandBiListItem		*current;
} IMG_CommandBiListIteratorForward;

/*
 * IMG_CommandBiListIteratorクラスのインライン関数
 */

/*
 * コンストラクタ
 */
static void IMG_CommandBiListIteratorForward_Construct(
	IMG_CommandBiListIteratorForward	*self,
	IMG_CommandBiList					*list)
{
	self->current = IMG_NULL;
	self->list = list;
}

/*
 * イテレーションを開始する。
 */
static void IMG_CommandBiListIteratorForward_Begin(
	IMG_CommandBiListIteratorForward		*self)
{
	self->current = self->list->top;
}

/*
 * 次の要素に進む。
 */
static void IMG_CommandBiListIteratorForward_Next(
	IMG_CommandBiListIteratorForward		*self)
{
	self->current = self->current->next;
}

/*
 * イテレーションが終了したかどうか調べる。
 */
static IMG_BOOL IMG_CommandBiListIteratorForward_IsDone(
	IMG_CommandBiListIteratorForward		*self)
{
	return self->current == IMG_NULL;
}

/*
 * カレントの要素を返す。
 */
static IMG_CommandPtr IMG_CommandBiListIteratorForward_Current(
	IMG_CommandBiListIteratorForward		*self)
{
	return self->current == IMG_NULL ?
				 IMG_NULL :
				 self->current->command;
}

/*-------------------------------------------------------------------------
  IMG_CommandBiListIteratorBackwardクラス
-------------------------------------------------------------------------*/
/*
 * IMG_CommandBiListIteratorBackwardクラスの定義
 */
typedef struct img_commandbilistiteratorbackward {
	IMG_CommandBiListPtr		list;
	IMG_CommandBiListItem		*current;
} IMG_CommandBiListIteratorBackward;

/*
 * IMG_CommandBiListIteratorクラスのインライン関数
 */

/*
 * コンストラクタ
 */
static void IMG_CommandBiListIteratorBackward_Construct(
	IMG_CommandBiListIteratorBackward	*self,
	IMG_CommandBiList					*list)		/* Iteration対象リスト */
{
	self->current = IMG_NULL;
	self->list = list;
}

/*
 * イテレーションを開始する。
 */
static void IMG_CommandBiListIteratorBackward_Begin(
	IMG_CommandBiListIteratorBackward		*self)
{
	self->current = self->list->tail;
}

/*
 * 次の要素に進む。
 */
static void IMG_CommandBiListIteratorBackward_Next(
	IMG_CommandBiListIteratorBackward		*self)
{
	self->current = self->current->prev;
}

/*
 * イテレーションが終了したかどうか調べる。
 */
static IMG_BOOL IMG_CommandBiListIteratorBackward_IsDone(
	IMG_CommandBiListIteratorBackward		*self)
{
	return self->current == IMG_NULL;
}

/*
 * カレントの要素を返す。
 */
static IMG_CommandPtr IMG_CommandBiListIteratorBackward_Current(
	IMG_CommandBiListIteratorBackward		*self)
{
	return self->current == IMG_NULL ?
				 IMG_NULL :
				 self->current->command;
}

/*-------------------------------------------------------------------------
  IMG_CommandBiListIteratorForwardRemovableクラスの定義
-------------------------------------------------------------------------*/
/*
 * IMG_CommandBiListIteratorクラスの定義
 */
typedef struct img_commandbilistiteratorforwardremovable {
	IMG_Context					*context;
	IMG_CommandBiListPtr		list;
	IMG_CommandBiListItem		*current;
	IMG_CommandBiListItem		*nextOfRemoved;
} IMG_CommandBiListIteratorForwardRemovable;

/*
 * IMG_CommandBiListIteratorクラスのインライン関数
 */

/*
 * コンストラクタ
 */
static void IMG_CommandBiListIteratorForwardRemovable_Construct(
	IMG_CommandBiListIteratorForwardRemovable	*self,
	IMG_Context									*context,
	IMG_CommandBiList							*list)		/* Iteration対象リスト */
{
	self->current = IMG_NULL;
	self->list = list;
	self->context = context;
	self->nextOfRemoved = IMG_NULL;
}

/*
 * コピーコンストラクタ
 *
 * 複数のiteratorが参照しているリストから要素を削除してはならない。
 * もしそのような場合でも動作させたいならば，
 * IMG_CommandListIteratro_Removableの実装を参照して拡張せよ。
 */
static void IMG_CommandBiListIteratorForwardRemovable_CopyConstruct(
	IMG_CommandBiListIteratorForwardRemovable	*self,
	IMG_CommandBiListIteratorForwardRemovable	*original)
{
	self->context       = original->context;
	self->current       = original->current;
	self->list          = original->list;
	self->nextOfRemoved = original->nextOfRemoved;
}

/*
 * イテレーションを開始する。
 */
static void IMG_CommandBiListIteratorForwardRemovable_Begin(
	IMG_CommandBiListIteratorForwardRemovable		*self)
{
	self->current = self->list->top;
	self->nextOfRemoved = IMG_FALSE;
}

/*
 * 次の要素に進む。
 */
static void IMG_CommandBiListIteratorForwardRemovable_Next(
	IMG_CommandBiListIteratorForwardRemovable		*self)
{
	if (self->current == IMG_NULL && self->nextOfRemoved == IMG_NULL)
		return;

	if (self->nextOfRemoved == IMG_NULL) {
		self->current = self->current->next;
	}
	else {
		self->current       = self->nextOfRemoved;
		self->nextOfRemoved = IMG_NULL;
	}
}

/*
 * イテレーションが終了したかどうか調べる。
 */
static IMG_BOOL IMG_CommandBiListIteratorForwardRemovable_IsDone(
	IMG_CommandBiListIteratorForwardRemovable		*self)
{
	return (self->current == IMG_NULL) && (self->nextOfRemoved == IMG_NULL);
}

static void IMG_CommandBiListIteratorForwardRemovable_End(
	IMG_CommandBiListIteratorForwardRemovable		*self)
{
	self->current = IMG_NULL;
}

/*
 * カレントの要素を返す。
 */
static IMG_CommandPtr IMG_CommandBiListIteratorForwardRemovable_Current(
	IMG_CommandBiListIteratorForwardRemovable		*self)
{
	return self->current == IMG_NULL ?
				 IMG_NULL :
				 self->current->command;
}

/*
 * イテレータの同一性判定
 */
static IMG_BOOL IMG_CommandBiListIteratorForwardRemovable_NotEqual(
	IMG_CommandBiListIteratorForwardRemovable		*self,
	IMG_CommandBiListIteratorForwardRemovable		*target)
{
	return self->current != target->current;
}

/*
 * カレントの要素をnewCmdで置き換える。
 */
extern IMG_CommandPtr IMG_CommandBiListIteratorForwardRemovable_ReplaceCurrent(
	IMG_CommandBiListIteratorForwardRemovable *self,
	IMG_CommandPtr								newCmd);

extern int IMG_CommandBiListIteratorForwardRemovable_RemoveCurrent(
	IMG_CommandBiListIteratorForwardRemovable *self);

#endif /* INC_IMG_CommandBiList_h */

/*
 * Log
 * 01.Apr.2004 Yozo Kashima AR#1463(グラデーションの省メモリ化)のため新規作成。
 */

/* end of IMG_CommandBiList.h */
