//
//  MXDConverterTypeM.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDConverterTypeL.h"

@interface MXDConverterTypeM : MXDConverterTypeL {
	// 受け取ったマスク画像の描画領域
	CGRect* _maskRectInfo;
	// 受け取ったマスク画像データ
	MXDImageData** _maskImageInfo;
}

- (void)drawMethod:(CGContextRef)context rect:(CGRect)_rect maskRect:(CGRect)_maskRect image:(MXDImageData*)_image maskImage:(MXDImageData*)_maskImage;

@end
