//
//  MXDLanguageFont.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.3 $, $Date: 2006/10/20 12:49:49 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDFont.h"

// フォントごとのデフォルトの幅高さ係数
#define DEFAULT_WH_COEFFICIENT  1.0
#define MSP_WH_COEFFICIENT		0.825
#define TNR_WH_COEFFICIENT		0.825
#define AUMS_WH_COEFFICIENT		0.875
#define CEN_WH_COEFFICIENT		0.725
// added @shitama DWVLT62
// 環境にメイリオフォントがない場合の幅高さ係数
#define MEI_WH_COEFFICIENT		0.825

// DWVLT70 PDFFont 2008.09.01 by marumo <<--
// 文字幅調整を無視する範囲。
#define IGNORE_SCALE_MIN		0.975
#define IGNORE_SCALE_MAX		1.025
// -->> DWVLT70 PDFFont 

@class MXDWinFont;

@interface MXDLanguageFont : NSObject  {
	unsigned char _charSet;		// キャラクタセット
	NSString* _faceName;		// タイプフェイス名を指定します
	NSString* _winFaceName;		// Windowsタイプフェイス名
	BOOL _matchFont;			// 一致したフォントかどうか
	MXDWinFont* _winFont;		// Windowsフォントの特徴を調整するためのクラス
	float _scaleWidth;			// 倍角
	long int _escapement;		// 文字送り方向のX軸に対する角度(半時計回り 1/10 度単位) DWVLT62 BTS#2 Marumo,K.
}


#pragma mark -
#pragma mark Common Methods
//----- クラスメソッド -------------------------------

// サブクラスがオーバーライドすべきメソッドの定義
// 初期化
- (id)initWithLogFont:(MXD_Logfont*)lpLogFont charSet:(unsigned char)charSet;
//----- インスタンスメソッド -------------------------------
// サブクラスへのメソッド公開のための定義
// フォントが一致しない場合かつプロポーショナルフォントの場合に使用されるWindowsフォントを生成する
- (MXDWinFont*)createProportionalFont;
// フォントが一致しない場合かつ等幅フォントの場合に使用されるWindowsフォントを生成する
- (MXDWinFont*)createFixedFont;
// フォントが一致した場合に使用されるMSフォントを生成する
- (MXDWinFont*)createMspFont;
// フォントが一致した場合に使用されるMSPフォントを生成する
- (MXDWinFont*)createMsFont;
// プロポーショナルフォントかどうかを返す
- (bool)_isProportionalFont:(unsigned char)pitchAndFamily;
// キャラクタセットを返す
- (unsigned char)charSet;
// テキストエンコーディングを返す
- (NSStringEncoding)getStringEncoding;

// 指定されたNSDataを元に、エンコーディングと文字コード変換を施したNSStringを返す。
-(NSString*)getEncodedString:(NSData*)strData;
// 指定されたcharの値が1バイトの文字として存在するかどうかを返す
- (BOOL)is1ByteString:(unsigned char)c;
// Unicode文字列を返す（フォント情報に従って適切な置き換えを提供すること）
- (bool)_getCharacters:(UniChar*)uniCharPtr
			  arrayMax:(unsigned long)arrayMax
				ofText:(NSString*)string
			charLength:(unsigned int*)charLength;
// ascent, descentを設定する（フォントの一致、不一致を考慮した適切な値を設定すること）				
- (void)_setAscent:(float*)ascent
		   descent:(float*)descent
	deviceFontSize:(float)deviceFontSize;
// 単一文字ごとの位置調整を設定する
- (void)_setPositionTo:(UniChar*)tgtChar
				pointX:(float*)pointX
				pointY:(float*)pointY
		 cosEscapement:(float)cos
		 sinEscapement:(float)sin
		deviceFontSize:(float)deviceFontSize;
// textAlignによる横方向の文字位置を調整
- (void)_setHorizontalAlign:(int)horizontalAlign
					 pointX:(float*)pointX
				 basePointX:(float)basePointX
				  textWidth:(float)textWidth;
// textAlignによる縦方向の文字位置を調整
- (void)_setVerticalAlign:(int)verticalAlign
				   pointY:(float*)pointY
			   basePointY:(float)basePointY
				textWidth:(float)textWidth
				   ascent:(float)ascent
				  descent:(float)descent;
// 文字の幅・高さの割合を返す
-(float)whCoefficient;
- (void)dumpInfo;


#pragma mark -
#pragma mark Mac Methods

#ifdef _PF_OSX_
// 指定されたスタイルに平体・長体を設定する。同時に単一文字の文字幅を設定する。
- (OSStatus)_setDefaultScaleTo:(ATSUStyle)style;
// 指定されたスタイルに自身のフォントIDを設定する
- (OSStatus)_setFontTo:(ATSUStyle)style;
- (OSStatus)_setScaleTo:(ATSUStyle)style
				  scale:(float)scale
			   uniScale:(float)uniScale;
// 指定されたスタイルに適切な文字幅調整を設定する
- (OSStatus)_setUniScaleTo:(ATSUStyle)style
				   tgtChar:(UniChar)tgtChar
			deviceFontSize:(float)deviceFontSize
				  uniScale:(float)uniScale
					adjust:(float*)adjustmentInterval;


// ATSUIフォントIDを返す（フォント情報に従って適切なscriptとlanguageタグを指定すること）
- (OSStatus)getATSUIFontId:(NSString*)fontName fontID:(ATSUFontID*)fontID;

// ATSUIフォント名を返す
- (NSString*)getATUIFontName:(NSString*)faceName
					 charSet:(unsigned char*)charSet
			  pitchAndFamily:(unsigned char)pitchAndFamily;

// インストールされているフォントかどうか
- (bool)_isValidFontName:(NSString*)fontName;
#endif


#pragma mark -
#pragma mark iOS Methods

#ifdef _PF_IOS_
// ATSUIフォント名を返す
- (NSString*)getATUIFontName:(NSString*)faceName
					 charSet:(unsigned char*)charSet
			  pitchAndFamily:(unsigned char)pitchAndFamily;

// インストールされているフォントかどうか
- (bool)_isValidFontName:(NSString*)fontName;

- (NSString*)facename;


- (CGAffineTransform)_setScale:(float)scale
					  uniScale:(float)uniScale;

- (CGAffineTransform)_setDefaultScale;

- (CGAffineTransform)_setUniScaleTotgtChar:(UniChar)tgtChar
							deviceFontSize:(float)deviceFontSize
								  uniScale:(float)uniScale
									adjust:(float*)adjustmentInterval;

- (BOOL)_verticalUniChar:(UniChar)tgtChar;
- (BOOL)isVertical;
#endif

@end
