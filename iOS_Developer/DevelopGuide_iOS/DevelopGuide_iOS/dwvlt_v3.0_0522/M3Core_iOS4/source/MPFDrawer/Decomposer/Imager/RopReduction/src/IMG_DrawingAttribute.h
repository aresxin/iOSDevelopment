/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_DrawingAttribute.h - 描画属性データ
 * Yozo Kashima 20.Jul.2001
 *
 */

#ifndef INC_IMG_DrawingAttribute_h
#define INC_IMG_DrawingAttribute_h

#include "IMG_Builtin.h"
#include "IMG_Common.h"
#include "IMG_ClassPointer.h"
#include "IMG_Command.h"

/*
 * defineした場合は，IMG_DrawingAttribute_Createで
 * 作成したオブジェクトでは，drawnPath,currentClipを
 * saveしないようになる。
 */
#define IMG_ATTR_PARTIAL_SAVE

typedef struct img_attributecommandset {
	IMG_CommandPtr	fillRule;				/* 塗りつぶし規則 */
	IMG_CommandPtr	drawMode;				/* 描画モード(Fill/Stroke/FillAndStroke) */
	IMG_CommandPtr	fillBrush;				/* 塗りつぶし用ブラシ */
	IMG_CommandPtr	strokeBrush;			/* ストローク用ブラシ */

	IMG_CommandPtr	capStyle;
	IMG_CommandPtr	joinStyle;
	IMG_CommandPtr	miterLimit;
	IMG_CommandPtr	strokeWidth;
	IMG_CommandPtr	lineStyle;
	IMG_CommandPtr	matrix;
} IMG_AttributeCommandSet;

/*
 * IMG_DrawingAttributeクラスの定義
 *
 * - 命令を受け取り命令による描画状態を蓄積する。
 *   (名称は描画属性だが、描画属性に限らないことに注意。いずれ名前を返るべき)
 *
 * - 描画状態は以下のものからなる。
 *     1. 描画属性設定命令により設定されたカレントの描画属性
 *     2. 描画命令を適用した描画結果
 *     3. パス構築命令により構築されたパス
 */
typedef struct img_drawingattribute {
	IMG_Context		*context;

	/*
	 * 属性
	 */
#ifdef IMG_ATTR_PARTIAL_SAVE
	/*
	 * fullSaveは全状態を保存するかどうかを示すフラグである。
	 *	IMG_TRUE	drawnObject,currentPath,drawnPath,currentClip全てをSaveする。
	 *  IMG_FALSE	currentPathのみSaveする。
	 */
	IMG_BOOL		fullSave;
#endif

	IMG_CommandPtr	fillRule;				/* 塗りつぶし規則 */
	IMG_CommandPtr	drawMode;				/* 描画モード(Fill/Stroke/FillAndStroke) */
	IMG_CommandPtr	fillBrush;				/* 塗りつぶし用ブラシ */
	IMG_CommandPtr	strokeBrush;			/* ストローク用ブラシ */

	IMG_CommandPtr	capStyle;
	IMG_CommandPtr	joinStyle;
	IMG_CommandPtr	miterLimit;
	IMG_CommandPtr	strokeWidth;
	IMG_CommandPtr	lineStyle;
	IMG_CommandPtr	matrix;

	IMG_CommandPtr				drawnObject;	/* 描画したオブジェクトを示すコマンド */
	IMG_PathCommandStoragePtr	currentPath;	/* カレントパス */
	IMG_PathCommandStoragePtr	drawnPath;		/* 描画結果としてのパス */
	IMG_CurrentClipStoragePtr	currentClip;	/* カレントクリップ */

} IMG_DrawingAttribute;

extern IMG_DrawingAttributePtr IMG_DrawingAttribute_Create(
	IMG_Context					*context,	/* コンテキスト (+) */
	IMG_AttributeCommandSet		*commandSet);	/* 初期属性のコマンド群 */

extern IMG_DrawingAttribute *IMG_DrawingAttribute_Clone(
	IMG_DrawingAttributePtr	self);		/* 描画属性オブジェクト(+) */

extern int IMG_DrawingAttribute_CopyConstruct(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_DrawingAttributePtr	refer);

extern int IMG_DrawingAttribute_Destruct(
	IMG_DrawingAttributePtr	self);		/* 描画属性オブジェクト(+) */

extern int IMG_DrawingAttribute_Destroy(
	IMG_DrawingAttributePtr	self);		/* 描画属性オブジェクト(+) */

/*
 * オブジェクトの更新
 */
extern int IMG_DrawingAttribute_UpdateObject(
	IMG_DrawingAttributePtr	self);

extern int IMG_DrawingAttribute_Identical(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_DrawingAttributePtr	target,	/* 描画属性オブジェクト(+) */
	IMG_BOOL				*result);	/* コマンドオブジェクト(+)*/

extern int IMG_DrawingAttribute_HaveDrawnSameObject(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_DrawingAttributePtr	target,	/* 描画属性オブジェクト(+) */
	IMG_BOOL				*result);	/* コマンドオブジェクト(+)*/

extern int IMG_DrawingAttribute_Update(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_CommandPtr			command);	/* コマンドオブジェクト(+)*/

extern int IMG_DrawingAttribute_IsDrawingWithSolidBlack(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_BOOL				*result);	/* 結果(-)*/

extern int IMG_DrawingAttribute_IsDrawingWithBlackAndWhitePattern(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_BOOL				*result);	/* 結果(-)*/

extern int IMG_DrawingAttribute_GetDrawMode(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_DrawMode			*drawMode);	/* 結果(-)*/

extern int IMG_DrawingAttribute_GetBrushCommand(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_DrawMode			drawMode,	/* 描画モード */
	IMG_CommandPtr			*brush);	/* ブラシコマンド(-)*/

extern int IMG_DrawingAttribute_ExecuteCommand(
	IMG_DrawingAttributePtr	self,		/* 描画属性オブジェクト(+) */
	IMG_CommandKind			kind,		/* 実行すべきコマンド種別(+) */
	IMG_CommandFilterPtr	filter);	/* コマンドを受け付けるフィルタ(+) */

extern IMG_BOOL IMG_DrawingAttribute_IsValid(
	IMG_DrawingAttributePtr	self);

#endif /* INC_IMG_DrawingAttribute_h */

/*
 * Log
 * 20.Jul.2001 Yozo Kashima  Created
 * 02.Oct.2001 Yozo Kashima 障害#88(pb0008g0-09)の対応。
 *							描画結果、描画したパス及びカレントパスを蓄積し、比較する機能を追加。
 * 08.Oct.2001 Yozo Kashima Win2000(Xor-Mask-Xorの置換)対応
 *							IsDrawingWithBwRasterPattern→IsDrawingWithBlackAndWhitePatternに変更。
 * 15.Oct.2001 Yozo Kashima Win2000(Nopの置換)対応
 *							ストローク関連の属性をメンバに追加。
 * 26.Oct.2001 Yozo Kashima 障害#143対応(ROP2-11が置換されない。w2k:dw4008g0-08,pb0008g0-09,pb0009i0-11)
 *							matrixメンバーを追加。
 * 08.May.2003 Yozo Kashima AR#1199対応。(IMG_DrawingAttribute_Createで作成した場合は
 *							drawnPath,currentClipを保存しないように修正。
 */

/* end of IMG_DrawingAttribute.h */
