//
//  MXDDeviceContextFactory.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDDeviceContext.h"

@interface MXDDeviceContextFactory : NSObject {

}

+ (MXDDeviceContext*)createDeviceContextWithSize:(NSRect)rect
											scale:(float)scale
											isTransparency:(BOOL)isTransparency
											isPrint:(BOOL)isPrint
											withCGContextRef:(CGContextRef)canvas;
+ (MXDDeviceContext*)createDeviceContextForSearchWithSize:(NSRect)rect
											scale:(float)scale
											isPrint:(BOOL)isPrint;
@end
