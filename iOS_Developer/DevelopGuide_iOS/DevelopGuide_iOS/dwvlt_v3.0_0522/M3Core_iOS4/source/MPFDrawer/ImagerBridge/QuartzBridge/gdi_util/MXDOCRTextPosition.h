//
//  MXDOCRTextPosition.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.3 $, $Date: 2007/02/15 10:59:14 $
//  Tag     : $Name: build4a $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#if (TARGET_OS_IPHONE == 0)
#import <Cocoa/Cocoa.h>
#endif

#import "MXDTextPosition.h"

class MXCImage;

// since DWVLT70 SelectText Marumo,K.
@interface MXDOCRTextPosition : MXDTextPosition {
	/*
	 * 矩形ごとのOCR文字列(各行末の改行なし) */
	NSString** _textArray;
	
	/*
	 * 上記_textArrayを連結した文字列（改行なし） */
	NSMutableString*	_text;
}

- (BOOL)appendStringAndPositionForOCR:(MXCImage*)coreImage
							withScale:(float)scale
							   inRect:(NSRect)rect;

// DWVLT70 SelectText 2008.09.08 by marumo
- (unsigned int)areaIndexForCharIndex:(unsigned int)charIndex;
@end
