//
//  MXDImageDataFactory.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDImageData.h"
#import "MXDBitmapInfo.h"

#import <Foundation/Foundation.h>


@interface MXDImageDataFactory : NSObject {

}

+ (MXDImageData*)createMXDImageDataWithBitmapInfo:(MXDBitmapInfo*)bitmapInfo
										paletteData:(const char*)paletteOfARGBColor
										numberOfColor:(size_t)numberOfColor
										pixelBits:(const void*)pixelBits
										clipRect:(CGRect)clipRect;


@end
