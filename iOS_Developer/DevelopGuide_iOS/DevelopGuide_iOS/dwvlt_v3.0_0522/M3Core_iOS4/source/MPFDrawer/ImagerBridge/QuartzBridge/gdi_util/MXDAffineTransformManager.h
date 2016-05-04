//
//  MXDAffineTransformManager.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDBezierPath.h"
#import "XdwBridgeCTMManager.h"

#import "w2mpf_gdi_def.h"

@interface MXDAffineTransformManager : NSObject <NSCopying>{
	int flag;
	int _documentDpi;  // 解像度
	int _deviceDpi;
	
	//float _scale;   // 全体の拡大率
	
	NSSize  _deviceSize;  //描画対象のサイズ
		
	BOOL	_isYAxisUpper;  // Y軸の向き
	
	float _scaleX; //X方向の拡大率
	float _scaleY; //Y方向の拡大率
	
	//NSPoint _physicalOrigin;	// 物理座標の原点
	//NSSize  _physicalSize;		// 物理座標でのX軸方向の描画範囲
	//NSPoint _logicalOrigin;		// 論理座標の原点
	//NSSize  _logicalSize;		// 論理座標でのX軸方向の描画範囲
	
	int _mapMode;		// マッピングモード
	
	POINT   _viewportOrg;		// 物理座標の原点
	SIZE	_viewportExt;		// 物理座標でのX軸方向の描画範囲
	POINT   _windowOrg;			// 論理座標の原点
	SIZE   _windowExt;			// 論理座標でのX軸方向の描画範囲
	
	CGAffineTransform _currentTransform;	// 現在の設定でのアフィンン変換
	
	// add this for QuartzBridge
	/*
	CGAffineTransform _winTransform;
	CGAffineTransform _viewTransform;
	CGAffineTransform _deviceTransform;
	*/
	
	// HBPS xdw CTM Manager
	XdwBridgeCTMManager _CTM;
	XdwMatrix _currentMatrix;
	unsigned long _width;
	unsigned long _height;
	unsigned long _xdpi;
	unsigned long _ydpi;
	// 2010/12/10 zhongchao modified this for AR17511 begin
	double _angle;
	bool _mirror;
	// 2010/12/10 zhongchao modified this for AR17511 end
}

- (id)initWithScale:(float)scale deviceSize:(NSSize)deveiceSize  deviceDpi:(int)deviceDpi;

//- (void)setPhysicalOrigin:(NSPoint)deviceOrigin;
//- (void)setPhysicalSize:(NSSize)deviceSize;
//- (void)setLogicalOrigin:(NSPoint)logicalOrigin;
//- (void)setLogicalSize:(NSSize)logicalSize;
//- (void)setScaleX:(float)scaleX scaleY:(float)scaleY;

- (int)setMapMode_mode:(int)fnMapMode;

- (BOOL)setViewportOrg:(POINT)viewPortOrg;
- (BOOL)setViewportExt:(SIZE)viewportExt;
- (BOOL)scaleViewportExt_xNum:(int)xNum xDenom:(int)xDenom yNum:(int)yNum yDenom:(int)yDenom;
- (BOOL)setWindowOrg:(POINT)windowOrg;
- (BOOL)setWindowExt:(SIZE)windowExt;
- (BOOL)scaleWindowExt_xNum:(int)xNum xDenom:(int)xDenom yNum:(int)yNum yDenom:(int)yDenom; // いるかな？


- (void)setDocumentDpi:(int)documentDpi;

- (void)concatTransformToContext:(CGContextRef)context;
- (void)concatUpDownReverseTransformAtPoint:(CGPoint)point toContext:(CGContextRef)context;

- (CGAffineTransform)orgAffineTransform;
#ifdef _PF_OSX_
- (NSAffineTransform*)orgNSAffineTransform;
#endif

- (CGPoint)transformPoint:(CGPoint)point;
- (CGPoint)transformPointF:(CGPoint)point;
- (CGSize)transformSize:(CGSize)size;
- (CGSize)transformSizeF:(CGSize)size;
- (CGRect)transformRect:(CGRect)rect;
- (CGRect)transformRectF:(CGRect)rect;
- (MXDBezierPath*)transformMXDBezierPath:(MXDBezierPath*)bezier;

// add this for QuartzBridge CTM
- (void)setCTM_matrix:(const XdwMatrix*)matrix width:(unsigned long)width 
			   height:(unsigned long)height xdpi:(unsigned long)xdpi 
				 ydpi:(unsigned long)ydpi;
- (BOOL)scaleViewport_x:(double)x y:(double)y;
- (BOOL)scaleWindow_x:(double)x y:(double)y;

// 2010/12/10 zhongchao modified this for AR17511 begin
- (double)transformAngle;
- (void)rotateTransform;
// 2010/12/10 zhongchao modified this for AR17511 end

// デバッグ用
- (void)printCurrentTransform;

- (XdwBridgeCTMManager*)getCTM;

@end
