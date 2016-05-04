//
//  MXDConverterTypeO.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDConverter.h"

#import "MXDBezierPath.h"

@interface MXDConverterTypeO : MXDConverter {
	MXDBezierPath**		_pathArray;
	unsigned long*		_fillColorArray;;
	int					_pathCount;
	MXDRegion*			_clipRegion;		// DWVLT70 BTS#2 by akiyoshi.
}

@end
