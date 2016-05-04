//
//  MXDTextPosition.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.4 $, $Date: 2006/12/26 05:56:53 $
//  Tag     : $Name: build4a $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "buildenvironment.h"

// 矩形情報を表す構造体を定義
typedef struct {
	Point point[4];
} MXD_CHARAREA;

// <<<--- DWVLT70 SelectText Marumo,K.
// 矩形からインデックスを逆引きする為の構造体を定義
typedef struct {
	int index;
	NSRect rect;
} MXD_AREAINDEX;
// --->>>

/*
 *  描画された文字列を囲む矩形を保存するためのクラス
 *
 */
@interface MXDTextPosition : NSObject {	
	MXD_CHARAREA*		_areaArray;		// 各文字を囲む矩形を表すRegionの配列
	
	/*
	 * ポリゴン配列に格納可能な最大数（DWVLT70pre unsigned に変更） */
	unsigned int		_areaCapacity;
	
	// <<<--- DWVLT70 SelectText Marumo,K.
	MXD_AREAINDEX*		_indexArray;	// 矩形ポイントからインデックスを逆引きする配列
	// --->>>
}

// ゲッター
- (NSString*)text;
- (int)charNum;
- (const NSRect*)rectAtIndex:(int)index; // DWVLT70 Overlay by marumo
- (const MXD_CHARAREA*)areaAtIndex:(int)index;

// DWVLT70 SelectText 2006.12.11 by Marumo,K. <<<---
- (BOOL)indexAtArea:(NSRect)rect minIndex:(int*)min maxIndex:(int*)max;
- (NSString*)stringFromIndex:(int)from toIndex:(int)to;
- (void)appendAreaIndex:(int)index;
// --->>>
@end
