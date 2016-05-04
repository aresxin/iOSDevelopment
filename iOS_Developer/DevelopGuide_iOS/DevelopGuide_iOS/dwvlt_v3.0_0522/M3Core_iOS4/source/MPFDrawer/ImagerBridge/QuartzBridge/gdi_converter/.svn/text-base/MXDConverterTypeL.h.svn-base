//
//  MXDConverterTypeL.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDConverter.h"
#import "MXDImageData.h"

@interface MXDConverterTypeL : MXDConverter {
	// 受け取った画像の数
	int _imageCount;
	// 受け取った画像の描画領域
	CGRect* _rectInfo;
	// 受け取った画像データ
	MXDImageData** _imageInfo;
	
	MXDRegion**		_clipRegionArray;
}

// 初期化を行う
- (id)initWith:(MXDVectorSource*)src;

// 代替描画を行う
- (void)drawMethod:(CGContextRef)context rect:(CGRect)_rect image:(MXDImageData*)_image;

- (void)changeDraw:(unsigned char*)tmpicData size:(long)size;

- (BOOL)changeDrawWhiteToTransparent:(unsigned char*)tmpicData index:(int)index;

- (BOOL)changeDrawBlackToTransparent:(unsigned char*)tmpicData index:(int)index;

- (void)dealloc;

@end
