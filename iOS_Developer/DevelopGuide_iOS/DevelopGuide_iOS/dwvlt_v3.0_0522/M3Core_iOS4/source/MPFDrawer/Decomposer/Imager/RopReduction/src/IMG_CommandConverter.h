/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandConverter.h - コマンド変換クラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_CommandConverter_h
#define INC_IMG_CommandConverter_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"

/*
 * IMG_CommandConverterクラスの定義
 */
typedef struct img_commandconverter {

	/* Publics操作 */

	int (*endOfCommand)(
		IMG_CommandConverterPtr	self,
		IMG_CommandFilterPtr	filter);

	/* Protected操作 */

	/*
	 * [操作名]	destroy
	 * [機能]	オブジェクトを削除する。
	 * [注意]	本操作はProtectedなので，クライアントは呼んではならない。
	 *			クライアントはIMG_CommandConverter_Releaseを使うこと。
	 */
	int (*destroy)(
		IMG_CommandConverterPtr	self);		/* this pointer */

	/*
	 * [操作名]	doExecute
	 * [機能]	コマンドを変換して実行する。
	 *			currentAttributeはコマンドを実行する直前の描画属性状態を指定する。
	 * [注意]	本操作はProtectedなので，クライアントは呼んではならない。
	 *			クライアントはIMG_CommandConverter_Executeを使うこと。
	 */
	int (*doExecute)(
		IMG_CommandConverterPtr	self,			/* this pointer */
		IMG_DrawingAttributePtr	currentAttr,	/* コマンド実行直前の描画属性(IN) */
		IMG_CommandPtr			command,		/* 変換して実行すべきコマンド(IN)*/
		IMG_CommandFilterPtr	filter,			/* 変換後のコマンドの実行を受け付けるフィルタ(IN) */
		IMG_BOOL				release);		/* コマンド実行後リソースを解放すべきか(IN) */

	/* Protected属性 */
	IMG_Context					*context;

	/* Protected集約 */
	IMG_CommandConverterPtr		next;			/* 後続するIMG_CommandConverter */

	/* Private属性 */
	IMG_UINT8					refCounter;		/* 参照カウンタ */

} IMG_CommandConverter;

/* public操作 */

extern IMG_BOOL IMG_CommandConverter_IsValid(
	IMG_CommandConverterPtr	self);

extern int IMG_CommandConverter_Release(
	IMG_CommandConverterPtr	self);

extern int IMG_CommandConverter_AddSuccessor(
	IMG_CommandConverterPtr	self,
	IMG_CommandConverterPtr	successor);

extern int IMG_CommandConverter_Execute(
	IMG_CommandConverterPtr	self,			/* this pointer */
	IMG_DrawingAttributePtr	currentAttr,	/* コマンド実行直前の描画属性(IN) */
	IMG_CommandPtr			command,		/* 変換して実行すべきコマンド(IN)*/
	IMG_CommandFilterPtr	filter,			/* 変換後のコマンドを受け付けるフィルタ(IN) */
	IMG_BOOL				release);		/* コマンド実行後リソースを解放すべきか(IN) */

extern int IMG_CommandConverter_Refer(
	IMG_CommandConverterPtr	*lhs,		/* left hand side */
	IMG_CommandConverterPtr	rhs);		/* right hand side */

extern int IMG_CommandConverter_MakeReference(
	IMG_CommandConverterPtr	*lhs,		/* left hand side */
	IMG_CommandConverterPtr	rhs);		/* right hand side */

/* Protected操作 */

extern int IMG_CommandConverter_Construct(
	IMG_CommandConverterPtr	self,					/* this pointer */
	IMG_Context				*context);				/* 実行環境コンテキスト */

extern int IMG_CommandConverter_Destruct(
	IMG_CommandConverterPtr	self);

extern int IMG_CommandConverter_Reconstruct(
	IMG_CommandConverterPtr	self);

extern int IMG_CommandConverter_ThrowCommandToNext(
	IMG_CommandConverterPtr	self,			/* this pointer */
	IMG_DrawingAttributePtr	currentAttr,	/* コマンド実行直前の描画属性(IN) */
	IMG_CommandPtr			command,		/* 後段に投げるコマンド(IN) */
	IMG_CommandFilterPtr	filter,			/* コマンドを受け付けるフィルタ(IN) */
	IMG_BOOL				release);		/* コマンド実行後リソースを解放すべきか(IN) */

extern int IMG_CommandConverter_ThrowEocToNext(
	IMG_CommandConverterPtr	self,			/* this pointer */
	IMG_CommandFilterPtr	filter);		/* EOCを受け付けるフィルタ */

#endif /* INC_IMG_CommandConverter_h */

/*
 * Old Log
 * 10.Aug.2001 Yozo Kashima Created
 * 27.Aug.2001 Yozo Kashima step3にInitClipが含まれているケースに対応するためのリファクタリング第2段。
 *							ExecuteにsaveIt引数を追加。
 * 08.Oct.2001 Yozo Kashima Win2000(Xor-Mask-Xorの置換)対応
 *							属性名をrasterPatternBrushからpatternBrushに変更。
 * 24.Oct.2001 Yozo Kashima 障害#139(chicken.prn,fh8008g0-08.prn)対応。
 *							isInitClipSavedメンバーを追加。
 *							IMG_CommandConverter_EndOfCommandを追加。
 * 23.Dec.2003 Yozo Kashima AR#1439(Imagerでのタグ拡張のため実行対象をpageでなくfilterに変更)。
 */

/* end of IMG_CommandConverter.h */
