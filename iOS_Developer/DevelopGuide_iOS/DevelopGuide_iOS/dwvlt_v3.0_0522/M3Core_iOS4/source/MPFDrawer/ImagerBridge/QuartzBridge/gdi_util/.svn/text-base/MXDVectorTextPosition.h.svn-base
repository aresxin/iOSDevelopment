//
//  MXDVectorTextPosition.m
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.2 $, $Date: 2006/12/26 05:56:53 $
//  Tag     : $Name: build4a $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#ifdef _PF_OSX_
#import <Cocoa/Cocoa.h>
#endif
#import "MXDTextPosition.h"

@interface MXDVectorTextPosition : MXDTextPosition {
	
	/* DWVLT70 SelectText by Marumo,K. MXDTextPosition から移動
	 * メタレコード内のテキストを保持するNSString */
	NSMutableString*	_text;
	
	/* DWVLT70 SelectText by Marumo,K. MXDTextPosition から移動
	 * 文字数かつrgnHandle配列に格納している数（DWVLT70pre unsigned に変更） */
	unsigned int		_charNum; 
	
	// DWVLT70 TextNoOverlap(AR13944) Tamayama,C. <<--
	/* 浮き文字／影付き文字で重なる文字を除いた文字列 */
	NSMutableString*	_textNoOverlap;
	
	/* _text に文字列が追加されたかどうか */
	BOOL				_appendedText;
	// --> DWVLT70 TextNoOverlap(AR13944) Tamayama,C.
}

- (BOOL)appendStringAndPosition_string:(NSString*)string
							  position:(const Point*)pointArray
							pointCount:(unsigned int)pointCount;

@end
