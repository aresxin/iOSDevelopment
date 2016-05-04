//
//  MXDWinFont.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Windowsでの元々のフォントを表すクラスのインタフェースです。
 */
@interface MXDWinFont : NSObject  {
	BOOL _isVertical;			// 縦書きフォントかどうか
}

//----- インスタンスメソッド -------------------------------
// 縦書きかどうかを設定する
- (void)_setVertical:(bool)isVertical;
// 文字によって必要な描画位置の調整を設定する
- (void)_setJpPositionTo:(UniChar*)tgtChar
			pointX:(float*)pointX
			pointY:(float*)pointY
			cosEscapement:(float)cos
			sinEscapement:(float)sin
			deviceFontSize:(float)deviceFontSize;
// 代替日本語フォント選択時の文字によって必要な文字幅の調整を返す
- (float)getJpUniScale:(UniChar)tgtChar
			uniScale:(float)uniScale
			adjust:(float*)adjustmentInterval
			deviceFontSize:(float)deviceFontSize;
// 文字のascent,descent,文字列の幅を計算する
- (void)_setAscent:(float*)ascent
			descent:(float*)descent
			deviceFontSize:(float)deviceFontSize;
// 代替日本語フォント選択時に文字を回転するかどうかを返す
-(bool)withRotateJp:(UniChar)tgtChar;

- (BOOL)isVertical;			
@end
