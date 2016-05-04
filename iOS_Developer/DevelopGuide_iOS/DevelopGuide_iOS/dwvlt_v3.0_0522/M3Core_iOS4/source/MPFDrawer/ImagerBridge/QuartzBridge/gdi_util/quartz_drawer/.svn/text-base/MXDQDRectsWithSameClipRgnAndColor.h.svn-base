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

#import "MXDREgion.h"

@interface MXDQDRectsWithSameClipRgnAndColor : MXDQDRectsWithSameClipAndColor {
	MXDRegion*		_clipRegion;
	

}
- (id)initWithClipRegion:(MXDRegion*)clipRegion
			solidColor:(unsigned long)solidColor;

- (bool)isEqualClipToClipRegion:(MXDRegion*)clipRegion
				colorToColor:(unsigned long)solidColor;

@end
