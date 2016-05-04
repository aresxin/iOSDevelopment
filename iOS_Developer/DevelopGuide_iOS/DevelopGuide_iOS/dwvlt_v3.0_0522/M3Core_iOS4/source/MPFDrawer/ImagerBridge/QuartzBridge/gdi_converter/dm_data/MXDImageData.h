//
//  MXDImageData.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "buildenvironment.h"

@interface MXDImageData : NSObject {
	size_t		_width;
	size_t		_height;
	size_t		_bitsPerComponent;
	size_t		_bitsPerPixel;
	size_t		_bytesPerRow;
	
	void*		_data;
	size_t		_dataSize;
	
	CGImageAlphaInfo	_alphaInfo;
	
	CGImageRef _imageRef;
}

/*
 *  圧縮したデータは渡さない
 *
 */
- (id)initWithWidth:(size_t)width
				height:(size_t)height
				bitsPerComponent:(size_t)bitsPerComponent
				bitsPerPixel:(size_t)bitsPerPixel
				bytesPerRow:(size_t)bytesPerRow
				data:(void*)data
				dataSize:(size_t)dataSize
				alphaInfo:(CGImageAlphaInfo)alphaInfo;

- (CGImageRef)createCGImageRef;
- (CGImageRef)createCGImageMaskMaskColor:(unsigned long)maskColor;
- (CGImageRef)createCGImageRefWithColors:(const unsigned long*)color;

- (size_t)width;
- (size_t)height;
- (size_t)bitsPerComponent;
- (size_t)bitsPerPixel;
- (size_t)bytesPerRow;
	
- (const void*)data;
- (size_t)dataSize;

- (void) drawImage:(CGContextRef) context inCGRect:(CGRect)rect;

- (bool)isMonoImage;

- (void*)copyAs32Bit;

- (void)reverse;

- (MXDImageData*)copyImageData;
- (MXDImageData*)invertImageData;

- (unsigned long)getImageColorAtX:(unsigned int)x y: (unsigned int)y;


// デバッグ用
- (void)whoAreYou_indentWidth:(unsigned int)indentWidth;
- (void)outputImageData;
@end
