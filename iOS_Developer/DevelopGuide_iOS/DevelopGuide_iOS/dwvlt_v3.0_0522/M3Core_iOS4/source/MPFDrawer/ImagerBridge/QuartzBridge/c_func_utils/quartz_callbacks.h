//
//  quartz_callbacks.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#ifndef QUARTZ_CALLBACKS_H
#define QUARTZ_CALLBACKS_H

#ifdef _PF_IOS_
#import <CoreGraphics/CoreGraphics.h>
#endif

#ifdef _PF_OSX_
#include <ApplicationServices/ApplicationServices.h>
#endif

void releaseDataOfCGImage( void* info, const void* data, size_t size );

// パターン描画に必要なものをパッケージしたもの
// コールバック関数のinfoにはこれが渡されるようにする
typedef struct tagMXD_PtnPackage {
	int			ptnAngle;		// パターン描画の角度
	CGImageRef  ptnImage;
}MXD_PtnPackage;
void drawPatternOfCGImageWithYAxisReverse( void* info, CGContextRef context );
void drawPatternOfCGImage( void* info, CGContextRef context );
void releasePatternDataOfCGImage( void * info );

#endif // QUARTZ_CALLBACKS_H
