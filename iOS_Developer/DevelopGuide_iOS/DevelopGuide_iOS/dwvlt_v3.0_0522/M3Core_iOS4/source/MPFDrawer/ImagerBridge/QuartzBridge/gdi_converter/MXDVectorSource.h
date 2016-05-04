//
//  MXDVectorSource.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDBezierPath.h"
#import "MXDImageData.h"

#import "MXDRegion.h"

// 保存用の構造体定義
// パス用の構造体
typedef struct tagMXD_PathInfo
{
	MXDBezierPath*  path;			// パス
	unsigned long   fillColor;		// 塗りつぶす色
	MXDImageData*   ptnImgData;		// パターンイメージ
	int				ptnAngle;		// パターン描画の角度(0.1度単位)
	unsigned long   ptnMaskColor;   // パターンのマスク色
	
	unsigned long   strokeColor;	// ペンの色
	float			lineWidth;		// 線描画の際の太さ
	
	BOOL			isInsideFrame;
}MXD_PathInfo;

// クリッピングパス用の構造体
typedef struct tagMXD_ClipPathInfo
{
	MXDBezierPath*  clipPath;			// パス

}MXD_ClipPathInfo;

// イメージデータ
typedef struct tagMXD_ImageInfo
{
	MXDImageData*		imageData;			// イメージの配列
	CGRect				rect;				// イメージの描画先矩形
	unsigned long		maskColor;			// マスク色
	MXDImageData*		maskImageData;		// マスクイメージ
	CGRect				rectForMask;		// マスクイメージの描画先矩形
	
	CGRect				clipRect;			// バグDB #63対策
	MXDRegion*			clipRegion;			// 上 plus バグDB #91対策
	
}MXD_ImageInfo;

@interface MXDVectorSource : NSObject {

	// ベクターモード用の保存場所
	MXD_PathInfo*		_pathInfoArray;				// パスの情報を保持する構造体の配列
	int					_pathInfoCounter;			// パスの数
	int					_pathInfoCapacity;			// 格納可能なパスの最大値
	
	MXD_ClipPathInfo*   _clipPathInfoArray;			// クリッピングパスの情報を保持する構造体の配列
	int					_clipPathInfoCounter;		// パスの数
	int					_clipPathInfoCapacity;		// 格納可能なパスの最大値
	
	
	MXD_ImageInfo*		_imgInfoArray;				// イメージの情報を保持する構造体の配列
	int					_imgInfoCounter;			// イメージの数
	int					_imgInfoCapacity;			// 格納可能なイメージの最大値
	
	MXDRegion*			_clipRegion;				// 描画エリアをクリップする単一のRegion DWVLT70 BTS#2 by akiyoshi 2008.10.21
	
}

- (void)releaseAll;

- (bool)addPath:(MXDBezierPath*)path
			fillColor:(unsigned long)fillColor;
- (bool)addPath:(MXDBezierPath*)path
			strokeColor:(unsigned long)strokeColor
			lineWidth:(float)lineWidth
			isInsideFrame:(BOOL)isInsideFrame;
- (bool)addPath:(MXDBezierPath*)path
			fillColor:(unsigned long)fillColor
			strokeColor:(unsigned long)strokeColor
			lineWidth:(float)lineWidth
			isInsideFrame:(BOOL)isInsideFrame;
- (bool)addPath:(MXDBezierPath*)path
			ptnImgData:(MXDImageData*)ptnImgData
			ptnAngle:(int)pntAngle
			maskColor:(unsigned long)maskColor;
- (bool)addClipPath:(MXDBezierPath*)clipPath;
- (bool)setClipPathFromPath;
- (bool)addImageData:(MXDImageData*)imageData
				rect:(const CGRect*)rectPtr;
- (bool)removeImageDataAtIndex:(int)index;
- (bool)changeImageData:(MXDImageData*)imageData
					rect:(const CGRect*)rectPtr
					atIndex:(int)index;
- (bool)addMaskImageData:(MXDImageData*)maskImageData
					rect:(const CGRect*)rectPtr
					atIndex:(int)index;
- (bool)addClipRect:(const CGRect*)rectPtr
					atIndex:(int)index;
- (bool)addClipRegionForImage:(MXDRegion*)region
						atIndex:(int)index;
- (bool)addMaskColor:(unsigned long)maskColor
					atIndex:(int)index;
- (bool)setMaskColorFromFillColorOfPathAtIndex:(int)index;

- (void)setClipRegion:(MXDRegion*)region;	// DWVLT70 BTS#2 by akiyoshi.

// 各種情報の取得
- (int)pathCount;
- (MXDBezierPath*)pathAtIndex:(int)index;
- (unsigned long)fillColorAtIndex:(int)index;
- (unsigned long)strokeColorAtIndex:(int)index;
- (MXDImageData*)patternImageDataAtIndex:(int)index;
- (int)ptnAngleAtIndex:(int)index;
- (unsigned long)ptnMaskColorAtIndex:(int)index;
- (float)lineWidthAtIndex:(int)index;
- (BOOL)isInsideFrameAtIndex:(int)index;

- (int)clipPathCount;
- (MXDBezierPath*)clipPathAtIndex:(int)index;

- (int)imageCount;
- (MXDImageData*)imageDataAtIndex:(int)index;
- (const CGRect*)rectForImageAtIndex:(int)index;
- (MXDImageData*)maskImageDataAtIndex:(int)index;
- (const CGRect*)rectForMaskImageAtIndex:(int)index;
- (const CGRect*)rectForClipAtIndex:(int)index;
- (MXDRegion*)clipRegionForImageAtIndex:(int)index;
- (unsigned long)maskColor;

- (MXDRegion*)clipRegion;	// DWVLT70 BTS#2 by akiyoshi.

// テスト用　内容確認メソッド
- (void)vectorDataThatIHave;

@end
