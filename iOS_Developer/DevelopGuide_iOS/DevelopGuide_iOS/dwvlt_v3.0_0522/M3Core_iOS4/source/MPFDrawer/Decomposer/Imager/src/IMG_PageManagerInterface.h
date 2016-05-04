/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_PageManagerInterface.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_PageManagerInterface_h
#define INC_IMG_PageManagerInterface_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_DisplayList.h"

typedef struct IMG_PageManagerInterface {
	/*
	 * インターフェイス
	 */
	IMG_DisplayList super;

	/*
	 * 実行環境
	 */
	IMG_Context *context;	/* Imager実行環境 */

	/*
	 * Resolution
	 */
	IMG_UINT16 resoX;	/* X方向の解像度 */
	IMG_UINT16 resoY;	/* Y方向の解像度 */

	/*
	 * 回転方向(HB_Decomposer.h)
	 */
	int rotation;

	/*
	 * 回転時の調整値(ピクセル)
	 */
	int adjustmentX;
	int adjustmentY;

	/*
	 * カレントの描画属性
	 */
	/* PMのデータ構造にあわせる */
	unsigned long rop;
	unsigned long	currentColor;			/* ソリッドカラー指定時の色値 */
	void			*currentPattern;		/* PMで定義された型でパターンを保存する */
	IMG_BOOL		isSolidColorActive;		/* ソリッドカラー指定が有効かどうかを示す */

	IMG_UINT32	pageWidth;				/* ページの幅(単位はピクセル) */
	IMG_UINT32	pageHeight;				/* ページの高さ(単位はピクセル) */
	IMG_BOOL	isNativeClipDrawing;	/* ImagerのI/Fを通じて指定されたクリップ領域を
										   描画中かどうかを示す */
} IMG_PageManagerInterface;

extern IMG_DisplayList *IMG_PageManagerInterface_Create(
	IMG_Context *context,	/* Imager実行環境 */
	IMG_UINT16 resoX,		/* X方向の解像度 */
	IMG_UINT16 resoY);		/* Y方向の解像度 */


#endif /* INC_IMG_PageManagerInterface_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 16.Apr.2001 Yozo Kashima UT用にuseFileAsImageStorageメンバを追加。
 * 18.Apr.2001 Yozo Kashima forward declarationを削除。
 * 09.May.2001 Yozo Kashima IMG_PatternDataを削除。
 * 14.May.2001 Yozo Kashima pageWidth,pageHeightを追加。
 */

/* end of IMG_PageManagerInterface.h */
