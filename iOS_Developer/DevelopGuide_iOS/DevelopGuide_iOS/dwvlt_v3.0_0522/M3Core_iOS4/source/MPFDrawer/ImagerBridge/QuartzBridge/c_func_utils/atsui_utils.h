//
//  atsui_utils.h
//
//  Updater : $Author: marumo $
//  Version : $Revision $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#ifndef ATSUI_UTILS_H
#define ATSUI_UTILS_H

#include <ApplicationServices/ApplicationServices.h>


// mau == My ATSUI Util
// style setting
OSStatus mau_setFontToStyle( ATSUStyle style, ATSUFontID  fontID );
OSStatus mau_setSizeToStyle( ATSUStyle style, float fontSize );
OSStatus mau_setVerticalToStyle( ATSUStyle style, bool isVertical );
OSStatus mau_setScaleToStyle( ATSUStyle style, CGAffineTransform transform );

// layout setting
OSStatus mau_setCGContextToLayout( ATSUTextLayout textLayout, CGContextRef context );
OSStatus mau_setLineRotationToLayout( ATSUTextLayout textLayout, float lineRotation );
OSStatus mau_getUnjustifiedBounds(
							ATSUTextLayout textLayout,
							unsigned int lineStart,
							unsigned int lineLength,
							float* textBefore,
							float* textAfter,
							float* ascent,
							float* descent
					);

#endif // ATSUI_UTILS_H
