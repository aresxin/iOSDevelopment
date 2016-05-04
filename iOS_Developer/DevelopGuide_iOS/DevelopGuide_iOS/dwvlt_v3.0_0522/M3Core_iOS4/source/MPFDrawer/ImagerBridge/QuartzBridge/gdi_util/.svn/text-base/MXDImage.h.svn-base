//
//  MXDImage.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDFileMap.h"

#import "../buildenvironment.h"

@interface MXDImage : NSObject {
    /*
	 * 作成された画像データ
	 */
	CGImageRef _imageRef;
	
	/*
	 * 画像の実データが入った構造体
	 */
	CGDataProviderRef _dataProviderRef;
	
	/*
	 * 画像の色情報を持った構造体
	 */
	CGColorSpaceRef _colorSpaceRef;
	
	/*
	 * 色テーブルを表すデータ
	 * 注) 画像の種類によっては使用しない場合がある。
	 */
	unsigned char* _colorIndex;
	
	/*
	 * ピクセル間のスムージングを行うかどうか
	 */
	BOOL _shouldInterpolate;
	
	/*
	 * オリジナルの自身の高さ
	 */
	size_t _originalHeight;
	
	/*
	 * オリジナルの自身の幅
	 */
	size_t _originalWidth;
}
- (void*) providerCallback;

- (id) initWithData:(unsigned char*)data
					dataSize:(size_t)dataSize
                    width:(size_t)width
                    height:(size_t)height
					compornentBits:(size_t)compornentBits 
                    pixecBits:(size_t)pixelBits
                    bytesPerRow:(size_t)bytesPerRow
                    alphaInfo:(CGImageAlphaInfo)info
                    shouldInterpolate:(BOOL)shouldInterpolate;

- (id) initWithData:(unsigned char*)data
					dataSize:(size_t)dataSize
                    width:(size_t)width
                    height:(size_t)height
					compornentBits:(size_t)compornentBits 
                    pixecBits:(size_t)pixelBits
                    bytesPerRow:(size_t)bytesPerRow
                    alphaInfo:(CGImageAlphaInfo)info
                    shouldInterpolate:(BOOL)shouldInterpolate
					map:(MXDFileMap*)map;
					

- (id) initJPEGWithData:(unsigned char*)data
						 dataSize:(size_t)dataSize
						 shouldInterpolate:(BOOL)shouldInterpolate;       

- (id) initWithPaletteData:(unsigned char*)paletteData
							numberOfColor:(size_t)numberOfColor
						    pixcelData: (unsigned char*)data
							dataSize:(size_t)dataSize
							width:(size_t)width
							height:(size_t)height
							compornentBits:(size_t)compornentBits 
							pixecBits:(size_t)pixelBits
							bytesPerRow:(size_t)bytesPerRow
							alphaInfo:(CGImageAlphaInfo)info
							shouldInterpolate:(int)shouldInterpolate;
- (void) releaseData;
- (CGImageAlphaInfo) alphaInfo;
- (CGColorSpaceRef) colorSpace;
- (size_t) width;
- (size_t) height;
- (size_t) bytesPerRow;
- (size_t) bitsPerPixel;
- (size_t) bitsPerCompornent;
- (void) drawImage:(CGContextRef) context inCGRect:(CGRect)rect;
- (void) drawImage:(CGContextRef) context inNSRect:(NSRect)rect;
- (void) reverceImage;
//- (void) rotationForDisplayByDegree:(float)degree;

// for test
- (void)outputImageData;
@end
