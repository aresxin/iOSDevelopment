//
//  MXDBitmapInfo.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Windows BITMAPINFO 仕様の RGB色データを表す構造体
 * reserved は 常に 0x00.
 */
typedef struct tagMXC_RGBQUAD {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reserved;
} MXC_RGBQuad;

@interface MXDBitmapInfo : NSObject {
	unsigned char* _bitmapInfo;	// BITMAPINFO構造体を指すポインタ
	unsigned int _bitmapInfoSize; // BITMAPINFO構造体のサイズ
	unsigned int _dibSize; // イメージがDIBの場合のデータサイズ
	int _jpegSize; // イメージがJPEGの場合のデータサイズ
	int _dibObjectMode; // イメージの種類(DIB/JPEG/NONE)
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- クラスメソッド
+ (id)bitmapInfoWithBytes:(unsigned char*)bmi;
+ (int)dibObjectModeDIB;
+ (int)dibObjectModeJPEG;
+ (int)dibObjectModeNONE;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- インスタンスメソッド
- (id)initBMIWithBytes:(unsigned char*)bmi;

//-- setters and getters for BITMAPINFOHEADER's member
- (unsigned long)infoHeaderSize;
- (void)setInfoHeaderSize:(unsigned long)val;
- (long)infoHeaderWidth;
- (void)setInfoHeaderWidth:(long)val;
- (long)infoHeaderHeight;
- (void)setInfoHeaderHeight:(long)val;
- (unsigned short)infoHeaderPlanes;
- (void)setInfoHeaderPlanes:(unsigned short)val;
- (unsigned short)infoHeaderBitCount;
- (void)setInfoHeaderBitCount:(unsigned short)val;
- (unsigned long)infoHeaderCompression;
- (void)setInfoHeaderCompression:(unsigned long)val;
- (unsigned long)infoHeaderSizeImage;
- (void)setInfoHeaderSizeImage:(unsigned long)val;
- (long)infoHeaderXPelsPerMeter;
- (void)setInfoHeaderXPelsPerMeter:(long)val;
- (long)infoHeaderYPelsPerMeter;
- (void)setInfoHeaderYPelsPerMeter:(long)val;
- (unsigned long)infoHeaderClrUsed;
- (void)setInfoHeaderClrUsed:(unsigned long)val;
- (unsigned long)infoHeaderClrImportant;
- (void)setInfoHeaderClrImportant:(unsigned long)val;
- (unsigned long)numberOfColor;

//-- setters and getters for BITMAPINFO.bmiColors
- (BOOL)palColorsIndexInto:(unsigned char*)array numberOfArray:(unsigned long)num;
- (BOOL)setColors:(MXC_RGBQuad*)array numberOfArray:(unsigned long)num;

//-- getter for BITMAPINFO*
- (unsigned char*)bitmapInfo;

//-- setters and getters for others
- (void)setBitmapInfoSize:(unsigned int)size;
- (unsigned int)bitmapInfoSize;
- (void)setDibSize:(unsigned int)size;
- (unsigned int)dibSize;
- (void)setJpegSize:(int)size;
- (int)jpegSize;
- (int)dibObjectMode;

// color or monochrome
- (BOOL)isMonochrome;

// for test
- (void)printBitmapInfo;
@end
