//
//  MXDFont.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDGdiObject.h"

#import "../buildenvironment.h"

@class MXDLanguageFont;

#ifdef _PF_OSX_
// 日本語明朝フォント
#define JP_MINCHO   @"Hiragino Mincho Pro W3"
// 日本語ゴシックフォント
#define JP_GOTHIC   @"Hiragino Kaku Gothic Pro W3"
#endif

#ifdef _PF_IOS_
// 日本語明朝フォント
//#define JP_MINCHO   @"Hiragino Mincho ProN W3"
#define JP_MINCHO   @"Hiragino Mincho ProN"
// 日本語ゴシックフォント
//#define JP_GOTHIC   @"Hiragino Kaku Gothic ProN W3"
#define JP_GOTHIC   @"Hiragino Kaku Gothic ProN"
#endif

// 論理フォントのpitchAndFamilyからフォントピッチのみを取り出す
#define fontPitch(pitchAndFamily) (pitchAndFamily & 0x0f)
// 論理フォントのpitchAndFamilyからフォントファミリのみを取り出す
#define fontFamily(pitchAndFamily) (pitchAndFamily & 0xf0)
// デフォルトフォントサイズ(point)
#define DEFAULT_FONT_SIZE   12

// add for font italic support
#define DEFAULT_ITALIC_FACTOR	0.320

/*
 * 論理フォント構造体
 *   Windowsの論理フォント構造体(LOGFONT)とほぼ互換性を保っている
 */
//typedef struct tagLOGFONT {
typedef struct {
   long int lfHeight;				// 論理フォントの高さを指定します
   long int lfWidth;				// 論理フォントのキャラクタの平均幅を指定します
   long int lfEscapement;			// 文字送りの方向のX軸に対する角度（反時計回り 1/10 度単位）
   long int lfOrientation;			// 文字のベースラインのX軸に対する角度（同上）
   long int lfWeight;				// フォントの太さを指定します
   BOOL lfItalic;					// TRUE を指定すれば斜体になります
   BOOL lfUnderline;				// TRUE を指定すると下線付きフォントになります
   BOOL lfStrikeOut;				// TRUE を指定すると、打消し線付きのフォントになります
   unsigned char lfCharSet;			// フォントのキャラクタセットを指定します
   unsigned char lfOutPrecision;	// 物理フォントを検索する方法を指定します
   unsigned char lfClipPrecision;   // クリッピング領域からはみ出した文字の処理方法を指定します
   unsigned char lfQuality;			// 論理フォントと物理フォントの属性をどの程度一致させるかを指定します
   unsigned char lfPitchAndFamily;  // フォントのピッチとファミリを指定します
   NSString* lfFaceName;			// タイプフェイス名を指定します
} MXD_Logfont;

/*
 * テキスト描画位置
 */
typedef struct tagTextPosition {
	int   charNumber;	// 描画した文字数
	// 角度付き文字列の矩形取得のためRect-->>Pointに変更 2005/1/28
	Point* charPosition;	// 文字毎の矩形（物理座標)の配列。配列の要素数はcharNumberの４倍。
	NSString* encodedStr;	// エンコーディング後の文字列
} MXD_TextPosition;

@interface MXDFont : MXDGdiObject  {
	long int _escapement;		// 文字送りの方向のX軸に対する角度（反時計回り 1/10 度単位）
	long int _orientation;		// 文字のベースラインのX軸に対する角度（同上）
	
	long int _weight;			// フォントの太さを指定します
	BOOL _isItalic;				// TRUE を指定すれば斜体になります
	BOOL _hasUnderline;			// TRUE を指定すると下線付きフォントになります
	BOOL _hasStrikeOut;			// TRUE を指定すると、打消し線付きのフォントになります
	unsigned int _textAlign;	// テキスト配置モード
   
	float _sinEscapement;		// 文字の正弦回転角
	float _cosEscapement;		// 文字の余弦回転角
	
	long _fontHeight;			// font height for Bridge I/F
	float _fontSize;			// ポイント（デバイスサイズでのフォントの高さ）
	
	unsigned int _textColor;	// テキストカラー 0xAABBGGRR
	
	long _logicalCellInterval;  // 現在選択されているフォントに対して文字間隔 [add by YuFei 2010/8/25]

#ifdef _PF_OSX_
	ATSUStyle _currentStyle;			// ATSUIのフォントスタイル = 文字のスタイル
	ATSUTextLayout _currentLayout;		// ATSUIのテキストレイアウト = 文字列のスタイル
#endif

#ifdef _PF_IOS_
	CFMutableDictionaryRef stringAttributes;
	CFMutableDictionaryRef fontAttributes;
	CTFontSymbolicTraits fontTraits;
	float _layoutRotation;
	BOOL _isItalicSupport;
	BOOL _isBoldSupport;
	BOOL _isBoldAndItalicSupport;
	BOOL _isBold;
#endif

	MXDLanguageFont* _languageFont;		// 言語をあらわすフォント（選択フォントの適正化を行うためのオブジェクト）
}

//----- クラスメソッド -------------------------------
// textAligne確認用
+ (BOOL)isUpdateCP:(unsigned int)status;
// 従来のオプションに、引数で指定されたオプションの妥当な部分だけを更新する。
+ (unsigned int)margeTextAlignNew:(unsigned int)newOption andOld:(unsigned int)oldOption;

// インスタンス生成
+ (MXDFont*)createFontIndirect:(MXD_Logfont*)lpLogFont;

// ストックオブジェクト生成
+ (MXDFont*)oemFixedFont;
+ (MXDFont*)ansiFixedFont;
+ (MXDFont*)ansiVarFont;
+ (MXDFont*)systemFont;
+ (MXDFont*)deviceDefaultFont;
+ (MXDFont*)systemFixedFont;
+ (MXDFont*)defaultGuiFont;

//----- インスタンスメソッド -------------------------------
- (id)initWithLogFont:(MXD_Logfont*)lpLogFont;
- (BOOL)setTextAlign:(unsigned int)textAlign;
- (BOOL)setTextColor:(unsigned int)nColor;
- (NSString*)getEncodedString:(NSData*)strData;

// 描画
- (BOOL)drawTextToCanvas:(NSData*)textData
		widths:(int*)LogicalellIntervals
		atPointX:(long)pointX
		andY:(long)pointY
		bkMode:(int)bkMode
		bkColor:(unsigned int)bkColor
		onCGContext:(void*)canvas
		isUnicode:(BOOL)isUnicode	// DWVLT70 V7Format by akiyoshi.
		withAffineTransform:(CGAffineTransform)transform
		returnedDrawnPositions:(MXD_TextPosition*)textPosition;	// DWVLT70 SelectText by akiyoshi.

// 検索時の疑似描画
- (BOOL)drawTextForSearch:(NSData*)string
		widths:(int*)LogicalellIntervals
		atPointX:(long)pointX
		andY:(long)pointY
		withAffineTransform:(CGAffineTransform)transform
		isUnicode:(BOOL)isUnicode
		returnedDrawnPositions:(MXD_TextPosition*)textPosition;

// add by YuFei 2010/8/25
- (BOOL)setLogicalCellInterval:(long)interval;
- (unsigned char)getCharSet;
- (long)getHeight;
@end
