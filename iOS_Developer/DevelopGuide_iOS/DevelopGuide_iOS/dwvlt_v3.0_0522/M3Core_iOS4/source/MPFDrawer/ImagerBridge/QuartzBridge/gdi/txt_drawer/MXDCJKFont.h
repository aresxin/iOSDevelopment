//
//  MXDCJKFont.h
//  DWGdi
//
//  Created by shitama on 06/09/28.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

// added @shitama DWVLT62

#import <Foundation/Foundation.h>
#import "MXDLanguageFont.h"

@interface MXDCJKFont : MXDLanguageFont {
	BOOL _isVertical;			// 縦書きフォントかどうか
}

//----- クラスメソッド -------------------------------


//----- インスタンスメソッド -------------------------------
// サブクラスへのメソッド公開のための定義
// 
- (NSString*)fontFaceNameAs:(NSString*)fontName;

#ifdef _PF_OSX_
// 指定されたスタイルに平体・長体を設定する。同時に単一文字の文字幅を設定する。
- (OSStatus)_setScaleTo:(ATSUStyle)style
				scale:(float)scale
				uniScale:(float)uniScale
				withRotate:(bool)withRotate;
#endif

#ifdef _PF_IOS_
// 指定されたスタイルに平体・長体を設定する。同時に単一文字の文字幅を設定する。
- (CGAffineTransform)_setScale:(float)scale
					  uniScale:(float)uniScale
					   uniChar:(UniChar)tgtChar
					withRotate:(bool)withRotate;

// - (BOOL)_verticalUniChar:(UniChar)tgtChar;

// - (BOOL)isVertical;
#endif
@end
