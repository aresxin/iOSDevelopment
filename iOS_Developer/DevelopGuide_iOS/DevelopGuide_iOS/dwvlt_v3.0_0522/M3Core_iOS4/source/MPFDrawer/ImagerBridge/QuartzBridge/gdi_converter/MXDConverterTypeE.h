//
//  MXDConverterTypeE.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDConverterTypeL.h"

@interface MXDConverterTypeE : MXDConverterTypeL {

	// 受け取ったマスク画像データ
	MXDImageData** _maskImageInfo;
}

- (void)drawMethod:(CGContextRef)context rect:(CGRect)_rect image:(MXDImageData*)_image maskImage:(MXDImageData*)_maskImage;

- (void)changeDraw:(MXDImageData*)_image maskImage:(MXDImageData*)_maskImage
				tmpicData:(unsigned char*)_tmpicData maskData:(unsigned char*)_maskData color:(unsigned long)_color;

@end
