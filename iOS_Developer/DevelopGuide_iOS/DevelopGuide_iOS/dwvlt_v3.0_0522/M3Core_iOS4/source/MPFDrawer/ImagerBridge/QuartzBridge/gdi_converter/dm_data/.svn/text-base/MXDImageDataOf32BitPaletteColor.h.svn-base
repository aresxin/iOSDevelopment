//
//  MXDImageDataOf32BitPaletteColor.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDImageData.h"

@interface MXDImageDataOf32BitPaletteColor : MXDImageData {
	unsigned char*  _paletteOfARGBColor;
	size_t			_numberOfColor;
}
- (id)initWithWidth:(size_t)width
				height:(size_t)height
				bitsPerComponent:(size_t)bitsPerComponent
				bitsPerPixel:(size_t)bitsPerPixel
				bytesPerRow:(size_t)bytesPerRow
				paletteData:(unsigned char*)paletteOfARGBColor
				numberOfColor:(size_t)numberOfColor
				data:(void*)data
				dataSize:(size_t)dataSize
				alphaInfo:(CGImageAlphaInfo)info;

- (size_t)numberOfColor;

- (void)setColor:(unsigned long)color AtIndex:(int)index;
- (unsigned long)colorOfPaletteAtIndex:(int)index;

@end
