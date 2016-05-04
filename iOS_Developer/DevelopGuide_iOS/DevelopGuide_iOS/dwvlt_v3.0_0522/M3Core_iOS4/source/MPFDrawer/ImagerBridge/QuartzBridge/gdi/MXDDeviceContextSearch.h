//
//  MXDDeviceContextSearch.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDDeviceContext.h"

@interface MXDDeviceContextSearch : MXDDeviceContext {

}

- (id) initWithWidth: (int)deviceWidth
					height: (int)deviceHeight
					scale: (float)scale
					documentDpi: (int)documentDpi;

@end
