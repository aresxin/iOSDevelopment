//
//  MXDPen.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDGdiObject.h"
#import "MXDBrush.h"

#import "w2mpf_gdi_def.h"

@interface MXDPen : MXDGdiObject 
{
	LOGPEN			_logPen;		// 入力時のLOGPEN

	unsigned int	_penType;		// ペンの型
	unsigned int	_penStyle;		// ペンのスタイル
	unsigned int	_penEndcap;		// ペンの端点キャップ
	unsigned int	_penJoin;		// ペンの結合
	
	int		_styleCount;	// 破線などのスタイルの定義
	float*  _styleArray;
	
    float			_penWidth;		// ペンの太さ
	
	unsigned int	_penColorInt;   // ペンの色
	CGColorSpaceRef _colorSpace;			// カラースペース
	float			_colorComponents[4];	// カラーコンポーネント

	BOOL			_isTransparency;			// 半透明かどうか
}


// *****生成用クラスメソッド*****
//  ストックオブジェクト生成メソッド
+ (MXDPen*)whitePen;
+ (MXDPen*)blackPen;
+ (MXDPen*)nullPen;
+ (MXDPen*)dcPen;


// createメソッド
+ (MXDPen*)createPen: (int)nPenStyle
              width: (int)nWidth
             color: (COLORREF)nColor;
+ (MXDPen*)createPen: (unsigned int)nPenStyle
              width: (float)nWidth
           logBrush: (const LOGBRUSH*)pLogBrush
         dotStyleCount: (int)nDotStyleCount
             dotStyle: (const unsigned long *)lpDotStyle;
+ (MXDPen*)createPenIndirect: (const LOGPEN*)lplgpn;
+ (MXDPen*)extCreatePen: (unsigned long)dwPenStyle
                width: (float)dwWidth
			logBrush: (const LOGBRUSH*)pLogBrysh
           dotStyleCount: (unsigned long)dwStyleCount
                dotStyle: (const unsigned long *)lpStyle;


//----- インスタンスメソッド ------------------------------------------------
// 初期化メソッド１
- (id)initWithStyle:(int)nPenStyle
				width:(int)nWidth
				color:(COLORREF)nColor;

// 初期化メソッド２
- (id)initWithStyle:(unsigned int)nPenStyle
				width:(float)nWidth
				logBrush:(const LOGBRUSH*)pLogBrysh
		dotStyleCount: (unsigned long)dwStyleCount
			dotStyle: (const unsigned long *)lpStyle;

- (void)setPenAttribute:(CGContextRef)context withAffineTransform:(CGAffineTransform)transform;

- (unsigned int)penStyle;
- (float)penWidth;
- (unsigned long)solidPenColor;

- (BOOL)isNullPen;

- (void)setTransparency:(BOOL)isTransparency;

@end
