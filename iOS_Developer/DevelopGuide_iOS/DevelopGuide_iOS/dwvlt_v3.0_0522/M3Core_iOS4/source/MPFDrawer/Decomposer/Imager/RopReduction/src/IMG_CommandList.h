/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandList.h - コマンドをリスト管理するクラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_CommandList_h
#define INC_IMG_CommandList_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandListItemクラスの定義
 */
typedef struct img_commandlistitem {
	struct img_commandlistitem	*next;
	IMG_CommandPtr				command;
} IMG_CommandListItem;

/*
 * IMG_CommandListItemPoolクラスの定義
 */
#define IMG_COMMAND_LIST_ITEM_MAX	128

typedef struct img_commandlistitempool {
	struct img_commandlistitempool	*next;
	IMG_CommandListItem				items[IMG_COMMAND_LIST_ITEM_MAX];
	int								freeIndex;
} IMG_CommandListItemPool;

/*
 * IMG_CommandListクラスの定義
 */
typedef struct img_commandlist {
	IMG_Context				*context;
    IMG_CommandListItem		*top;
	IMG_CommandListItem		*tail;
	IMG_CommandListItemPool	*pool;
	IMG_UINT32				size;
} IMG_CommandList;

extern IMG_BOOL IMG_CommandList_IsValid(
	IMG_CommandList	*self);

extern IMG_CommandList *IMG_CommandList_Create(
	IMG_Context *context);

extern int IMG_CommandList_Destroy(
	IMG_CommandList *self);

/*
 * サービス関数
 */
extern int IMG_CommandList_PopFront(
	IMG_CommandListPtr	self,
	IMG_CommandPtr		*command);

extern int IMG_CommandList_PushBack(
	IMG_CommandListPtr	self,
	IMG_CommandPtr		command);

extern int IMG_CommandList_Front(
	IMG_CommandListPtr	self,
	IMG_CommandPtr		*command);

extern int IMG_CommandList_Back(
	IMG_CommandListPtr	self,
	IMG_CommandPtr		*command);

extern int IMG_CommandList_IsEqualTo(
	IMG_CommandListPtr	self,
	IMG_CommandListPtr	target,
	IMG_BOOL			*result);

extern int IMG_CommandList_Empty(
	IMG_CommandListPtr	self,
	IMG_BOOL			*isEmpty);


/*
 * IMG_CommandListConditionクラスの定義
 */
typedef struct img_commandlistcondition {
	IMG_Context	*context;
	int	(*isSatisfied)(
		IMG_CommandListConditionPtr self,
		IMG_CommandPtr				cmd,
		IMG_BOOL					*result);
} IMG_CommandListCondition;

extern int IMG_CommandListCondition_Construct(
	IMG_CommandListConditionPtr	self,
	IMG_Context *context);

/*
 * IMG_CommandListConditionSetクラスの定義
 */
typedef struct img_commandlistconditionset {
	IMG_CommandListCondition		super;
	IMG_CommandListConditionPtr		*conditions;
	IMG_INT32						numOfConditions;
} IMG_CommandListConditionSet;

extern int IMG_CommandListConditionSet_Construct(
	IMG_CommandListConditionSetPtr	self,
	IMG_Context						*context,
	IMG_CommandListConditionPtr		*condtions,
	IMG_INT32						numOfConditions);

extern int IMG_CommandList_FindIf(
	IMG_CommandListPtr			self,			/* this pointer */
	IMG_CommandListIteratorPtr	begin,			/* 検索開始点 */
	IMG_CommandListIteratorPtr	end,			/* 検索終了点 */
	IMG_CommandListCondition	*condition,		/* 条件 */
	IMG_CommandListIteratorPtr	result);		/* 検索結果 */

/*
 * IMG_CommandListIteratorクラスの定義
 */
typedef struct img_commandlistiterator {
	IMG_CommandListPtr			list;
	IMG_CommandListItem			*current;
} IMG_CommandListIterator;

/*
 * IMG_CommandListIteratorクラスのインライン関数
 */

/*
 * コンストラクタ
 */
static void IMG_CommandListIterator_Construct(
	IMG_CommandListIterator *self,
	IMG_CommandList	*list)		/* Iteration対象リスト */
{
	self->current = IMG_NULL;
	self->list = list;
}

/*
 * イテレーションを開始する。
 */
static void IMG_CommandListIterator_Begin(
	IMG_CommandListIterator		*self)
{
	self->current = self->list->top;
}

/*
 * 次の要素に進む。
 */
static void IMG_CommandListIterator_Next(
	IMG_CommandListIterator		*self)
{
	self->current = self->current->next;
}

/*
 * イテレーションが終了したかどうか調べる。
 */
static IMG_BOOL IMG_CommandListIterator_IsDone(
	IMG_CommandListIterator		*self)
{
	return self->current == IMG_NULL;
}

static void IMG_CommandListIterator_End(
	IMG_CommandListIterator		*self)
{
	self->current = IMG_NULL;
}

/*
 * カレントの要素を返す。
 */
static IMG_CommandPtr IMG_CommandListIterator_Current(
	IMG_CommandListIterator		*self)
{
	return self->current == IMG_NULL ?
				 IMG_NULL :
				 self->current->command;
}

/*
 * イテレータの同一性判定
 */
static IMG_BOOL IMG_CommandListIterator_NotEqual(
	IMG_CommandListIterator		*self,
	IMG_CommandListIterator		*target)
{
	return self->current != target->current;
}


/*
 * カレントの要素をnewCmdで置き換える。
 */
extern IMG_CommandPtr IMG_CommandListIterator_ReplaceCurrent(
	IMG_CommandListIterator *self,
	IMG_CommandPtr			newCmd);


/*
 * IMG_CommandListIteratorRemovableクラスの定義
 *    カレントのコマンドのみを削除できるIterator
 */
typedef struct img_commandlistiteratorremovable {
	IMG_Context			*context;
	IMG_CommandListPtr	list;
	IMG_CommandListItem	*prev;
	IMG_CommandListItem	*current;
	IMG_CommandListItem	*nextOfRemoved;
	struct img_commandlistiteratorremovable *topItor;
	struct img_commandlistiteratorremovable *prevItor;
	struct img_commandlistiteratorremovable *nextItor;
} IMG_CommandListIteratorRemovable;

extern void IMG_CommandListIteratorRemovable_Construct(
	IMG_CommandListIteratorRemovable	*self,
	IMG_Context							*context,
	IMG_CommandListPtr					list);

extern void IMG_CommandListIteratorRemovable_Destruct(
	IMG_CommandListIteratorRemovable *self);

extern void IMG_CommandListIteratorRemovable_CopyConstruct(
	IMG_CommandListIteratorRemovable *self,
	IMG_CommandListIteratorRemovable *source);

extern void IMG_CommandListIteratorRemovable_First(
	IMG_CommandListIteratorRemovable *self);

extern void IMG_CommandListIteratorRemovable_Next(
	IMG_CommandListIteratorRemovable *self);

extern IMG_BOOL IMG_CommandListIteratorRemovable_IsDone(
	IMG_CommandListIteratorRemovable *self);

extern IMG_CommandPtr IMG_CommandListIteratorRemovable_Current(
	IMG_CommandListIteratorRemovable *self);

extern void IMG_CommandListIteratorRemovable_RemoveCurrent(
	IMG_CommandListIteratorRemovable *self);

extern IMG_BOOL IMG_CommandListIteratorRemovable_NotEqual(
	IMG_CommandListIteratorRemovable *self,
	IMG_CommandListIteratorRemovable *target);

#endif /* INC_IMG_CommandList_h */

/*
 * Log
 * 07.May.2001 Yozo Kashima  Created
 * 17.May.2001 Yozo Kashima Get関数からunitSize引数を削除。
 *							PeepTop関数を削除。find関数を追加。
 * 18.May.2001 Yozo Kashima IMG_CommandListIteratorを追加。
 * 23.May.2001 Yozo Kashima IMG_CommandList_DestroyAllEntriesを追加。
 * 30.May.2001 Yozo Kashima IMG_CommandList_GetByCodeを追加。
 * 27.Aug.2001 Yozo Kashima 不要メンバ、不要関数を削除。IteratorのConstruct関数を追加。
 *							IMG_CommandListIteratorRemovableクラスの定義を追加。
 * 14.Sep.2001 Yozo Kashima 障害#97(fh8007g0-07)の対応。
 *							IMG_Commandを直接リンクせずIMG_CommandListItemをリンクさせて管理する。
 * 27.Sep.2001 Yozo Kashima 障害#88(pb0008g0-09)の対応。
 *							IMG_CommandList_IsEqualToを追加。sizeメンバーを追加。
 * 01.Nov.2001 Yozo Kashima 障害#163 (fl0004t0-04.prn), #167 (fl0009g0-10.prn) #169 (lt0008g1-09.prn)に対応。
 *							IMG_COMMAND_LIST_ITERATOR_NOT_EQUALを追加。
 * 18.Jan.2003 Yozo Kashima CEViewerでのROP置換対応(パス描画シーケンス中にSetRopModeが現れるケースに対応)。
 *							IMG_CommandListIteratorRemovableをロバストイテレータに拡張
 *							(但し，イテレーションの範囲が重ならないこと)。
 * 13.Mar.2003 Yozo Kashima イテレータのEndをIsDoneに名称変更&Endをイテレータを終了状態にする関数に変更。
 */

/* end of IMG_CommandList.h */
