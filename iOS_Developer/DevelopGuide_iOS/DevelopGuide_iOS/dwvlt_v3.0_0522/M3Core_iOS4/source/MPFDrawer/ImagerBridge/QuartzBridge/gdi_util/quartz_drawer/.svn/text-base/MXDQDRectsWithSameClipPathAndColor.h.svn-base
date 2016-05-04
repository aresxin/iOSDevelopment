//
//  MXDQDRectsWithSameClipPathAndColor.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDQDRectsWithSameClipAndColor.h"

#import "MXDBezierPath.h"

@interface MXDQDRectsWithSameClipPathAndColor : MXDQDRectsWithSameClipAndColor {
	MXDBezierPath*  _clipPath;
}

- (id)initWithClipPath:(MXDBezierPath*)clipPath
			solidColor:(unsigned long)solidColor;

- (bool)isEqualClipToClipPath:(MXDBezierPath*)clipPath
				colorToColor:(unsigned long)solidColor;


@end
