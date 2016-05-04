//
//  MXDRasterOperation.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "w2mpf_gdi_def2.h"

@interface MXDRasterOperation : NSObject {

}

+ (BOOL)reversePolishOfBinaryRasterOperationCode:(unsigned int)code function:(char*)function;

+ (BOOL)reversePolishOfTernaryRasterOperationCode:(unsigned int)code function:(char*)function;

+ (BOOL)reversePolishDestination:(unsigned char*)destinationByte
								pattern:(unsigned char*)patternByte
								source:(unsigned char*)sourceByte
								function:(char*)function;
@end
