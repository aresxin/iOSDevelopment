//
//  MXDQDRectsWithSameColor.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDQuartzDrawer.h"


@interface MXDQDRectsWithSameColor : MXDQuartzDrawer {
	unsigned long   _solidColor;
	float			_colorComponent[4];
	
	CGRect*			_rectArray;
	int				_rectNum;
	int				_rentCapacity;
}

- (id)initWithSolidColor:(unsigned long)solidColor;

- (bool)isEqualColorToColor:(unsigned long)solidColor;
- (bool)addRect:(CGRect)rect;



@end
