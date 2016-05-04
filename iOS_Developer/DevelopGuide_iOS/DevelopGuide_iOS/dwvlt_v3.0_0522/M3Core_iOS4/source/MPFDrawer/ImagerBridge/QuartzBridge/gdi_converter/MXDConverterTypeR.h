//
//  MXDConverterTypeR.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDConverterTypeL.h"

@interface MXDConverterTypeR : MXDConverterTypeL {

	// 受け取った色情報を格納
	unsigned long maskColor;

	// クリッピング
	MXDRegion*   _clipRegion;
}

@end
