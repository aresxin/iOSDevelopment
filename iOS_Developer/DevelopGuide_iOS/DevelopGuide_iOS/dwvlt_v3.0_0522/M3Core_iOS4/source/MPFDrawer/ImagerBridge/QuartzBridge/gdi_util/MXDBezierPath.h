//
//  MXDBezierPath.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "../gdi/MXDGdiObject.h"
#ifdef _PF_IOS_
#import "MXDUIBezierPathExt.h"
#endif

/*
 *  MXDBezierPathが持つリスト内のノードを表す構造体
 */
typedef struct tagPATHELEMENTNODE {
	NSBezierPathElement			elementype;		// 要素の種類(CGPathElement.typeではない)
	CGPoint						points[3];		// 要素
	struct tagPATHELEMENTNODE*  next;			// 次の有効なノードへのポインタ
	
	struct tagPATHELEMENTNODE*  nextNode;		// 次のノードへのポインタ
} MXD_PathElementNode;

@interface MXDBezierPath : NSObject {
	MXD_PathElementNode*   _firstElement;		// リストの先頭
	MXD_PathElementNode*   _lastElement;		// リストの最後
	
	MXD_PathElementNode*   _firstNode;			// リストの先頭 オブジェクト破棄時に使用
	MXD_PathElementNode*   _lastNode;
	
	int _elementCount;							// リスト内の有効な要素の個数
	int _elementMax;							// リスト内の格納可能な要素の個数（現在未使用）
	
	unsigned int _fillMode;						// 塗りつぶしモード
	
	MXDGdiObject* _clipRegion;					// 描画の際のクリッピング
	
	bool			_isAllLine;					// 全て直線かどうか
	
	int				_isClockwise;				// 時計回りかどうか
	float			_currentAngle;				// 現在のパスの向き(角度)
	CGPoint			_lastPoint;
	
	// 追加ポイント計算用
#ifdef _PF_OSX_
	NSBezierPath* _tmpBezier;
	NSAffineTransform* _tmpTransform;
#endif

#ifdef _PF_IOS_
	MXDUIBezierPathExt* _tmpBezier;
	// this variable is no need. why?
	CGAffineTransform _tmpTransform;
#endif
}

+ (MXDBezierPath*)createMXDBezierPath;

- (void)setFillMode:(unsigned int)mode;
- (unsigned int)fillMode;

- (unsigned int)elementCount;
- (CGRect)bounds;
- (BOOL)isEmpty;

- (void)moveToPoint:(CGPoint)aPoint;
- (void)lineToPoint:(CGPoint)aPoint;
- (void)curveToPoint:(CGPoint)aPoint
				controlPoint1:(CGPoint)controlPoint1
				controlPoint2:(CGPoint)controlPoint2;
- (void)closePath;

- (NSBezierPathElement)elementAtIndex:(int)index associatedPoints:(CGPoint*)points;

- (void)appendBezierPath:(MXDBezierPath*)path;

- (void)copySelfElementsAtLastOfPath:(MXDBezierPath*)path;

- (void)appendBezierPathWithRect:(CGRect)aRect;
- (void)appendBezierPathWithRoundRect:(CGRect)aRect
							roundSize:(CGSize)roundSize;
- (void)appendBezierPathWithOvalInRect:(CGRect)aRect;
- (void)appendBezierPathWithArcInRect:(CGRect)lpRect
								ptStart:(CGPoint)ptStart
								ptEnd:(CGPoint)ptEnd;
- (void)appendBezierPathWithChordInRect:(CGRect)lpRect
								ptStart:(CGPoint)ptStart
								ptEnd:(CGPoint)ptEnd;
- (void)appendBezierPathWithPieInRect:(CGRect)lpRect
								ptStart:(CGPoint)ptStart
								ptEnd:(CGPoint)ptEnd;

- (void)transformUsingCGAffineTransform:(CGAffineTransform)transform;

- (void)removeAllPoints;

- (void)setPathToContext:(CGContextRef)context;
- (void)setPathToContextWithNoBegin:(CGContextRef)context;

- (void)strokeToContext:(CGContextRef)context;
- (void)fillToContext:(CGContextRef)context;
- (void)fillAndStrokeToContext:(CGContextRef)context;
- (void)addClipToContext:(CGContextRef)context;

- (BOOL)isAllLine;
- (int)loadAllPoints:(CGPoint*)points;
- (bool)isRectPath_rect:(CGRect*)rect;

- (bool)isClockWise;

- (void)setClipRegion:(MXDGdiObject*)clipRegion;

- (MXDBezierPath*)bezierPathByReversingPath;

// デバッグ用
- (void)printElements;

#pragma mark -
#pragma mark Add new methods for BridgeI/F
- (void)appendBezierPathWithArcInRect:(CGRect)aRect
						   startAngle:(float)startAngle
							 endAngle:(float)startAngle;
#pragma mark -

@end
