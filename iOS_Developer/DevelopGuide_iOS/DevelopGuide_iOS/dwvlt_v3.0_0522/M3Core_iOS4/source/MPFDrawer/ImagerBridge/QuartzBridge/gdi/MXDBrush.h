//
//  MXDBrush.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDGdiObject.h"
#import "MXDPalette.h"
#import "../gdi_util/MXDBitmapInfo.h"
#import "../gdi_util/MXDImage.h"

#import "w2mpf_def.h"
#import "w2mpf_gdi_def.h"

@interface MXDBrush : MXDGdiObject 
{
	// 初期化時の入力データ 
	LOGBRUSH _logBrush;
	
	// ブラシのスタイル
    unsigned int	_brushStyle;
	
	// 色に関する情報
	unsigned int	_brushColorInt;
	CGColorSpaceRef _colorSpace;
	float			_colorComponents[4];
	BOOL			_isTransparency;			// 半透明かどうか
	
	// ハッチスタイル
	unsigned long   _brushHatchStyle;
	
	// ハッチブラシ、パターンブラシ用のCGPatternRef
	CGPatternRef _pattern;
	
	// MXDImageData*に変更する
	void*   _imageData;
	int		_ptnAngle;		// パタン描画時の角度を指定する(0.1度単位)
	
	// createDIBPatternBrushで生成された場合に使用するパレット指定
	BOOL _isUseDCPalette;
	MXDPalette* _dcPalette;
	
	// add by YuFei 2010/8/28 >>>
	float _patternOffsetX;
	float _patternOffsetY;
	// <<<
	
	// AR89
	// add by tongjo for bitmap parttern 20101218
	CGAffineTransform _currentTransform;
}


// 生成メソッド------------------------------------------------------
/*
 *  ストックオブジェクト用ブラシオブジェクト生成メソッド
 */
+ (MXDBrush*)whiteBrush;
+ (MXDBrush*)lightgrayBrush;
+ (MXDBrush*)grayBrush;
+ (MXDBrush*)darkgrayBrush;
+ (MXDBrush*)blackBrush;
+ (MXDBrush*)nullBrush;
+ (MXDBrush*)hollowBrush;
+ (MXDBrush*)dcBrush;

+ (MXDBrush*)createBrushIndirect: (const LOGBRUSH*)logBrush;
+ (MXDBrush*)createPatternBrush:(char*)bitmapBits
							bitmapInfo:(MXDBitmapInfo*)bitmapInfo;
+ (MXDBrush*)createDIBPatternBrushPt:(char*)bitmapBits
							bitmapInfo:(MXDBitmapInfo*)bitmapInfo
							usePalette:(unsigned int)iUsage;

// 初期化メソッド
- (id)initNullBrush;
- (id)initHollowBrush;
- (id)initSolidBrushWithColor:(unsigned int)colorInt;
- (id)initHatchedBrushWithColor:(unsigned int)colorInt hatchStyle:(unsigned int)hatchStyle;
- (id)initPatternBrushWithBitmapPattern:(char*)bitmapBits
							bitmapInfo:(MXDBitmapInfo*)bitmapInfo;
- (id)initDIBPatternBrushWithBitmapPattern:(char*)bitmapBits
							bitmapInfo:(MXDBitmapInfo*)bitmapInfo
							usePalette:(unsigned int)iUsage;


// パターン描画の角度設定
- (void)setPatternAngle:(int)ptnAngle;
/*
 *  パレットを設定する
 *  引数:
 *  paletteHandle : 設定するパレット
 */
- (void)setPalette:(MXDPalette*)palette;

/*
 *  塗りつぶしに使用するイメージのサイズを返す
 *
 */
- (CGSize)patternImageSize;

- (void)setBrushAttribute:(CGContextRef)context;
- (void)setBrushAttribute:(CGContextRef)context  foreColor:(unsigned int)foreColor bkColor:(unsigned int)bgColor;

- (BOOL)isNullBrush;
- (BOOL)isSolidBrush;
- (BOOL)isSolidBlackBrush;
- (BOOL)isSolidWhiteBrush;
- (BOOL)isMonoPatternBrush;

- (void)setTransparency:(BOOL)isTransparency;

- (void)solidColor:(unsigned char*)color;
- (const void*)patternImageDataWithForeColor:(unsigned int)foreColor bkColor:(unsigned int)bgColor;
- (unsigned long)solidBrushColor;

// 描画色に透明色を設定する
- (void)setFillColorTransparencyToContext:(CGContextRef)context;

// デバッグ用
- (void)whoAreYou_indentWidth:(unsigned int)indentWidth;

// add by YuFei 2010/8/28 >>>
// パターンのオフセットの設定
- (void)setPatternOffset:(float)x Y:(float)y;

// AR89
// add by tongjo for bitmap parttern 20101218
- (void)setDIBPatternMatrix:(CGAffineTransform)currentTransform;
//<<<
@end
