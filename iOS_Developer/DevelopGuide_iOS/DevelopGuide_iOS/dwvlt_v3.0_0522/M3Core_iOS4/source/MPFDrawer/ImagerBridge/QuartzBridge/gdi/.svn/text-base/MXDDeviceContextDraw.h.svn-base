//
//  MXDDeviceContextDraw.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDDeviceContext.h"
#import "MXDQuartzDrawer.h"

// 描画をまとめる際、現在どのような描画をまとめているのかを判定する時に使用する定数
typedef enum tagMXD_QDPackagingMode {
	MXD_QD00_NONE,
	MXD_QD01_RECTS_COLOR,
	MXD_QD02_RECTS_CLIPRGN,
	MXD_QD03_RECTS_CLIPPATH,
	MXD_QD04_RECTS_CLIPRGN_COLOR,
	MXD_QD05_RECTS_CLIPPATH_COLOR
}MXD_QDPackagingMode;

@interface MXDDeviceContextDraw : MXDDeviceContext {
	
	// AR17511
	// move this member to parent.
	//CGContextRef	_destContextRef;			// 描画対象
	// AR17511 end.
												// 通常描画		: 初期化時に渡されるピクセルデータを元に生成される
												// ベクター化モード : 初期化時に渡される
	
	BOOL			_isTransparency;		// 背景が透明かどうか
	
	MXDBezierPath*  _pathBracket;			// 現在操作中のパスブラケット
	BOOL			_isPathBracketOpened;	// パスブラケットが開いているかどうか
		
	MXDBezierPath*  _tmpBezier;				// 図形描画作業用のMXDBezierPath
	MXDBezierPath*  _tmpImageBezier;		// 3元ラスタオペレーションでパターンを描画するた目の作業用MXDBezierPath
	MXDBezierPath*  _tmptextClipBezier;		// テキスト描画の際にクリッピングを行なう時に使用するクリップ作業用のパス
	
	MXD_QDPackagingMode _qdMode;			// 現在の描画パッケージングモード
	MXDQuartzDrawer*	_quartzDrawer;		// 細かい描画をまとめる
}

// サブクラスに共通のプライベートメソッド
- (void)_appendPolygonPath: (CGPoint *)points
						count: (int)nCount
						toPath:(MXDBezierPath*)bezier;

- (BOOL)_writeString:(NSData*)string
			widths:(int[])lpDxWidths
			atPoint:(CGPoint)logicalPoint
			rectType:(unsigned int)nOptions
			rect:(CGRect*)logicalLpRect
			operation:(unsigned int)operation
			isUnicode:(BOOL)isUnicode		// 2008.07.11 DWVLT70 V7Format by akiyoshi.
			returnedDrawnPositions:(MXD_TextPosition*)textPosition;
@end
