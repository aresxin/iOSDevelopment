//
//  MXDRegion.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MXDGdiObject.h"

#import "../gdi_util/MXDBezierPath.h"

#include "../mxd_original_define.h"

@interface MXDRegion : MXDGdiObject {
	MXD_RegionData*		_rgnData;		// リージョンデータ
	
	int					_currentMode;   // 現在の表現はリージョンかパスか
	MXDBezierPath*		_pathData;		// パスデータ
	
	// 最後にクリップを設定したものを保存しておく
	int					_lastMode;
	MXD_RegionData*		_lastClipRgnData;
	MXDBezierPath*		_lastClipPathData;
	bool				_isCompareLast;		// 最後にクリップしたリージョンと比較してクリップするかどうか
	
	// 作業用
	MXD_RegionData*		_tmpResultRgn;
	MXD_RegionData*		_tmpRgn;
	MXD_RegionData*		_tmpInputRgn;
}

+ (MXDRegion*)createRegion;
+ (MXDRegion*)createRectRegion:(const CGRect*)rectPtr;
+ (MXDRegion*)createRegionWithRgnData:(const MXD_RegionData*)rgnDataPtr;
+ (MXDRegion*)createRegionWithBezierPath:(MXDBezierPath*)bezierPath;

- (id)initWithReginData:(const MXD_RegionData*)rgnDataPtr;
- (id)initWithBezierPath:(MXDBezierPath*)bezierPath;

- (bool)combineRect:(const CGRect*)rectPtr combineMode:(int)combineMode;
- (bool)combinePath:(MXDBezierPath*)path combineMode:(int)combineMode;  // やむなく
- (bool)combineRgn:(MXDRegion*)mxdRegion combineMode:(int)combineMode;

- (int)regionType;
- (CGRect)bounds;

- (void)fillToContext:(CGContextRef)context;
- (void)clipToContext:(CGContextRef)context;
- (void)clipToContextWithoutRestore:(CGContextRef)context;

- (void)clearClipToContext:(CGContextRef)context;

//テスト用
- (void)printRegionData;

@end
