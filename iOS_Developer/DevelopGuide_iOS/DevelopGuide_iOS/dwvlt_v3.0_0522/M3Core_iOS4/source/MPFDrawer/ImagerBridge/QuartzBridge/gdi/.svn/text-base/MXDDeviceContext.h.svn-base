//
//  MXDDeviceContext.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//


#import <Foundation/Foundation.h>

#import "MXDPen.h"
#import "MXDFont.h"
#import "../gdi_util/MXDAffineTransformManager.h" 
#import "../gdi_util/MXDBitmapInfo.h"
#import "MXDRegion.h"

#import "w2mpf_gdi_def.h"		// 中でw2m_gdi_def2.hをincludeしている
//#import "w2m_gdi_def2.h"

// saveDC,restoreDC用の保存データ
typedef struct tagSAVED_DC_STATE
{
	MXDAffineTransformManager* win32Mapper;			//描画環境のアフィン変換管理
	
	// 各種描画モード
	int mapMode;		// マッピングモード
    int bkMode;			// バックグラウンド モード
	int drawMode;		// ラスターオペレーション
    int	polyFillMode;   // 多角形塗りつぶしモード
	int stretchMode;	// 画像描画の品質
	int drawMode3;		// ROP3 mode
	
    unsigned int	textAlign;						// テキスト出力時の配置指定（センタリング、上詰め、etc）
	
	COLORREF	bkColor;					// バックグラウンドカラー
	COLORREF	textColor;					// フォアグランドカラー
												
	MXDPen*			currentPen;						// 現在のペン
    MXDBrush*		currentBrush;					// 現在のブラシ
	BOOL			isPenTransparency;				// YESならselectObjectされたペンは半透明になる
	BOOL			isBrushTransparency;			// YESならselectObjectされたブラシは半透明になる
	MXDFont*		currentFont;					// 現在のフォント
	MXDPalette*		currentPalette;					// 現在の論理パレット
	CGPoint			currentPoint;					// パスブラケット中の現在位置

	MXDRegion*		currentRegion;					// 現在のクリッピング領域
	
	struct tagSAVED_DC_STATE*	next;				// スタックの次の要素
} MXD_SavedDCState;

@interface MXDDeviceContext : NSObject
{
	int _deviceWidth;		// デバイスの幅
	int _deviceHeight;		// デバイスの高さ
	
	//int _documentDpi;   // 文書の解像度		delete DWVLT70 Resolution by akiyoshi.
	
	int _ptnAngle;		// パターン描画の角度(0.1度単位)
	
	// DCの保存場所
	MXD_SavedDCState* _lastDC;
	
	// 各種描画モード
	int _mapMode;		// マッピングモード
	int _drawMode;		// ラスターオペレーション
	int _bkMode;		// バックグラウンド モード
	int	_polyFillMode;  // 多角形塗りつぶしモード
	int _stretchMode;   // 画像描画品質
	// add this for Bridge I/F ROP3 mode
	int _drawMode3;		// ROP3 mode

    unsigned int	_textAlign;      // テキスト出力時の配置指定（センタリング、上詰め、etc）
	
	// add by YuFei 2010/9/7 >>>
	long _textExtra; 
	// <<<
	
	COLORREF	_bkColor;		// 背景色
	COLORREF	_textColor;		// 前景色（テキストのフォアグランドカラー）
	
	MXDAffineTransformManager* _win32Mapper;	//描画環境のアフィン変換管理
	
	MXDPen*			_currentPen;	 // 現在のペン
    MXDBrush*		_currentBrush;	 // 現在のブラシ
	BOOL			_isPenTransparency;	// YESならselectObjectされたペンは半透明になる
	BOOL			_isBrushTransparency;	// YESならselectObjectされたブラシは半透明になる
	MXDFont*		_currentFont;	 // 現在のフォント
	MXDPalette*		_currentPalette; // 現在の論理パレット
	
	MXDRegion*		_currentRegion;		// 現在のクリッピング領域
	
	CGPoint			_currentPoint;		// パスブラケット中の現在位置
	
	// add DWVLT70 Resolution 2008.07.18 by akiyoshi. >>>
	// メタファイル画像のX方向／Y方向の解像度
	// EMF画像において、物理座標で指定される数値に関しては解像度と描画スケールから
	// 描画時のデバイスサイズを割り出す必要がある。
	// WMFについては現状不明。
	// 関係するメタレコード（現状判明しているもの）:
	//   VIEWPORTORGEX, VIEWPORTEXTEX, INTERSECTCLIPRECT
	int _documentDpiX;	// 文書のX方向解像度
	int _documentDpiY;	// 文書のY方向解像度
	int _deviceDpi;		// 描画デバイス解像度(現状75固定)
	float _scale;		// 描画スケール
	
@protected
	// 以下はこのデバイスコンテキストで使用するGDIオブジェクトを管理する為の属性である。
	// 操作メソッドはプライベートメソッドとして実装する。
	NSMutableDictionary*	_gdiObjectTable;	// このデバイスコンテキストで使用するGDIオブジェクトを格納しているテーブル
	MXDGdiObject* _stockObject[STOCK_LAST+1];   // ストックオブジェクト
	unsigned char _gdiObjectIndexTable[8192];	// _gdiObjectの格納時に使用するインデックスを管理するテーブル
	
	// AR17511
	CGContextRef	_destContextRef;
}

//---------------------------------------------------------------------
//-- クラスメソッド
// 初期化メソッド
- (id) initWithWidth: (int)deviceWidth
					height: (int)deviceHeight
					scale: (float)scale
					documentDpi: (int)documentDpi
					isTransparency: (BOOL)isTransparency;

//---------------------------------------------------------------------
//-- インスタンスメソッド
// ベクター化モード対応
- (void)startDraw;
- (void)endDraw;

//-- 描画前の設定
- (void)setPatternAngle:(int)ptnAngle;


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- setter/getter
- (NSSize)size;
//- (void)setScaleX:(float)scaleX scaleY:(float)scaleY;

//- (NSImage*)destination;

//- (void)setDocumentDpi:(int)docucmentDpi;

// add DWVLT70 Resolution 2008.07.18 by akiyoshi. >>>
- (void)setDocumentDpiX:(int)dpiX Y:(int)dpiY;
- (float)scale;
// <<<

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- デバイスコンテキストの状態に関するメソッド群
- (int)saveDC;
- (int)restoreDCRelativeTo:(int)relative;
//- (int)restoreDC;   //Win32

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- 描画全般に関わる設定を行うメソッド群
- (int)setMapMode:(int)mode;
- (int)getMapMode;

- (int)setROP2:(int)rasterOperation;
- (int)getROP2;

- (int)setBkMode:(int)nBkMode;
- (int)getBkMode;

- (int)setPolyFillMode:(int)nPolyFillMode;
- (int)getPolyFillMode;

- (int)setStretchBltMode:(int)nStretchMode;
- (int)getStretchBltMode;

- (unsigned int)setTextAlign:(unsigned int)nFlags;
- (unsigned int)getTextAlign;


// 背景色・前景色の設定・取得
- (COLORREF)setTextColor:(COLORREF)crColor;
- (COLORREF)getTextColor;
- (COLORREF)setBkColor:(COLORREF)crColor;
- (COLORREF)getBkColor;

// マッピングのスケールの設定
- (BOOL)setWindowOrgEx:(POINT)point;
- (POINT)getWindowOrgEx;
- (BOOL)setWindowExtEx:(SIZE)size;
- (SIZE)getWindowExtEx;
- (BOOL)setViewportOrgEx:(POINT)point;
- (POINT)getViewportOrgEx;
- (BOOL)setViewportExtEx:(SIZE)size;
- (SIZE)getViewportExtEx;
- (BOOL)scaleViewportExt:(int)xNum xDenom:(int)xDenom yNum:(int)yNum yDenom:(int)yDenom;
- (BOOL)scaleViewport_x:(double)x y:(double)y;
- (BOOL)scaleWindow_x:(double)x y:(double)y;
- (BOOL)SetCurrentTransforMatrix:(const XdwMatrix*)matrix width:(long)width
						  height:(long)height xDpi:(long)xdpi yDpi:(long)ydpi;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- GDIオブジェクトを生成／管理するメソッド群
- (MXDPen*)createPenIndirectUseAutoIndex:(const LOGPEN*)logPen
								 atIndex:(unsigned long*)pIndex;// add pIndex by YuFei[2010/8/18]
- (MXDPen*)createPenIndirect:(const LOGPEN*)logPen atIndex:(unsigned long)index;
- (MXDPen*)extCreatePenUseAutoIndex:(unsigned long)dwPenStyle
							  width: (float)dwWidth
						   logBrush: (const LOGBRUSH*)pLogBrush
					  dotStyleCount: (unsigned long)dwStyleCount
						   dotStyle: (const unsigned long *)lpStyle
							atIndex:(unsigned long*)pIndex;
- (MXDPen*)extCreatePen:(unsigned long)dwPenStyle
	width: (float)dwWidth
	logBrush: (const LOGBRUSH*)pLogBrush
	dotStyleCount: (unsigned long)dwStyleCount
	dotStyle: (const unsigned long *)lpStyle
	atIndex:(unsigned long)index;
- (MXDBrush*)createBrushIndirectUseAutoIndex:(const LOGBRUSH*)logBrush
									 atIndex:(unsigned long*)pIndex;// add pIndex by YuFei[2010/8/18]
- (MXDBrush*)createBrushIndirect:(const LOGBRUSH*)logBrush atIndex:(unsigned long)index;
- (MXDBrush*)createDIBPatternBrushPtUseAutoIndex:(char*)bitmapBits
							bitmapInfo:(MXDBitmapInfo*)bitmapInfo
							usePalette:(unsigned int)iUsage
										 atIndex:(unsigned long*)pIndex; // add pIndex by YuFei[2010/8/18]
- (MXDBrush*)createDIBPatternBrushPt:(char*)bitmapBits
							bitmapInfo:(MXDBitmapInfo*)bitmapInfo
							usePalette:(unsigned int)iUsage
							atIndex:(unsigned long)index;
- (void)setPenTransparency:(BOOL)isTransparency;  // selectObjectするペンを半透明ぶらしにする
- (void)setBrushTransparency:(BOOL)isTransparency;  // selectObjectするブラシを半透明ぶらしにする
- (MXDPalette*)createPaletteUseAutoIndex:(MXD_LogPalette*)lpLogPalette
								 atIndex:(unsigned long*)pIndex; // add pIndex by YuFei[2010/8/18]
- (MXDPalette*)createPalette:(MXD_LogPalette*)lpLogPalette atIndex:(unsigned long)index;
- (MXDFont*)createFontIndirectUseAutoIndex:(const LOGFONTW*)lpLogFont 
								   atIndex:(unsigned long*)pIndex
								 isUnicode:(BOOL)bUnicode; // add pIndex by YuFei[2010/8/18]
- (MXDFont*)createFontIndirect:(const LOGFONTW*)lpLogFont atIndex:(unsigned long)index isUnicode:(BOOL)bUnicode;
- (MXDRegion*)createRectRegionUseAutoIndex:(NSRect)rect
								   atIndex:(unsigned long*)pIndex; // add pIndex by YuFei[2010/8/18]

- (MXDGdiObject*)selectObjectAtIndex:(unsigned long)index;
- (MXDGdiObject*)selectObject:(MXDGdiObject*)gdiObject;
- (MXDGdiObject*)selectPaletteAtIndex:(unsigned long)index bForceBackground:(BOOL)bForceBackground;
- (MXDPalette*)selectPalette:(MXDPalette*)pPalette bForceBackground:(BOOL)bForceBackground;
- (unsigned int)realizePalette; 

- (BOOL)deleteObjectAtIndex:(unsigned long)index;

- (MXDGdiObject*)selectStockObject:(int)index;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- 描画するパスの管理／操作を行うメソッド群
- (void)beginPath;

- (void)endPath;

- (void)fillPath;

// add this for Bridge I/F 20101003
- (void)strokeAndFillPath;

- (void)closeFigure;

- (void)strokePath;

- (void)moveTo_x: (int)x y: (int)y;
- (void)moveTo_point: (POINT)point;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- 線を描画するメソッド群（塗りつぶさない）
- (void)lineTo_x: (int)x y: (int)y;
- (void)lineTo_point:(POINT)point;

- (void)polyline_lpPoints: (const POINT*)lpPoints
				nCount: (int)nCount;

- (void)polylineTo_lpPoints: (const POINT*)lpPoints
				nCount: (int)nCount;

- (void)polyBezier_lpPoints: (const POINT*)lpPoints
				nCount: (int)nCount;

- (void)polyBezierTo_lpPoints: (const POINT*)lpPoints
				nCount: (int)nCount;

- (void)arc_x1: (int)x1 y1: (int)y1
			x2: (int)x2 y2: (int)y2
			x3: (int)x3 y3: (int)y3
			x4: (int)x4 y4: (int)y4;
- (void)arc_lpRect: (LPRECT)lpRect
			ptStart: (POINT)ptStart
			ptEnd: (POINT)ptEnd;
- (void)arc_lpRect: (LPRECT)lpRect
		   ptStart: (POINT)ptStart
			 ptEnd: (POINT)ptEnd
	withGSDrawMode: (XdwGSDrawMode)gsDrawMode;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- 図形を描画するメソッド群（塗りつぶす）
- (void)rectangle_x1: (int)x1 y1: (int)y1
				x2: (int)x2 y2: (int)y2;
- (void)rectangle_lpRect: (LPRECT)lpRect;
- (void)rectangle_lpRect: (LPRECT)lpRect
		  withGSDrawMode: (XdwGSDrawMode)gsDrawMode;

- (void)roundRect_x1: (int)x1 y1: (int)y1
               x2: (int)x2 y2: (int)y2
               x3: (int)x3 y3: (int)y3;
- (void)roundRect_lpRect: (LPRECT)lpRect
            point: (POINT)point;

- (void)polyPolygon_lpPoints: (const POINT*)lpPoints
					lpPolyCounts: (const INT*)lpPolyCounts
					nCount: (int)nCount;

- (void)polygon_lpPoints: (const POINT*)lpPoints
				nCount: (int)nCount;

- (void)ellipse_x1: (int)x1 y1: (int)y1
				x2: (int)x2 y2: (int)y2;
- (void)ellipse_lpRect: (LPRECT)lpRect;

- (void)chord_x1: (int)x1 y1: (int)y1
				x2: (int)x2 y2: (int)y2
				x3: (int)x3 y3: (int)y3
				x4: (int)x4 y4: (int)y4;
- (void)chord_lpRect: (LPRECT)lpRect
				ptStart: (POINT)ptStart
				ptEnd: (POINT)ptEnd;
- (void)chord_lpRect: (LPRECT)lpRect
			 ptStart: (POINT)ptStart
			   ptEnd: (POINT)ptEnd
	  withGSDrawMode: (XdwGSDrawMode)gsDrawMode;

- (void)pie_x1: (int)x1 y1: (int)y1
			x2: (int)x2 y2: (int)y2
			x3: (int)x3 y3: (int)y3
			x4: (int)x4 y4: (int)y4;
- (void)pie_lpRect: (LPRECT)lpRect
			ptStart: (POINT)ptStart
			ptEnd: (POINT)ptEnd;
- (void)pie_lpRect: (LPRECT)lpRect
		   ptStart: (POINT)ptStart
			 ptEnd: (POINT)ptEnd
	withGSDrawMode: (XdwGSDrawMode)gsDrawMode;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- テキスト出力に関するメソッド群
- (BOOL)extTextOut:(char*)lpszString
			count:(int)nCount
			x:(int)x y:(int)y
			rectType:(unsigned int)nOptions
			rect:(RECT*)lpRect
			widths:(int[])lpDxWidths
			isUnicode:(BOOL)isUnicode	// 2008.07.11 DWVLT70 V7Format by akiyoshi.
			returnedDrawnPositions:(MXD_TextPosition*)textPosition;

- (BOOL)extTextOut:(NSData*)str
			x:(int)x y:(int)y
			rectType:(unsigned int)nOptions
			rect:(RECT*)lpRect
			widths:(int[])lpDxWidths
			isUnicode:(BOOL)isUnicode	// 2008.07.11 DWVLT70 V7Format by akiyoshi.
			returnedDrawnPositions:(MXD_TextPosition*)textPosition;

/*
-(BOOL)extTextOut_x:(int)x
					y:(int)y
					fuOptions:(UINT)fuOptions
					lprc:(const RECT*)lprc
					lpString:(LPCTSTR)lpString
					cbCount:(UINT)cbCount
					lpDx:(const int*)lpDx
					returnedDrawnPositions:(MXD_TextPosition*)textPosition;*/
					

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- ビットマップ描画メソッド群
- (BOOL)bitBlt_nXDest:(int)nXDest
				nYDest:(int)nYDest
				nWidth:(int)nWidth
				nHeight:(int)nHeight
				lpBits:(char*)lpBits
				lpBitsInfo:(MXDBitmapInfo*)lpBitsInfo
				nXSrc:(int)nXSrc
				nYSrc:(int)nYSrc
				dwRop:(DWORD)dwRop;

- (BOOL)stretchBlt_nXOriginDest:(float)nXOriginDest
					nYOriginDest:(float)nYOriginDest
					nWidthDest:(float)nWidthDest
					nHeightDest:(float)nHeightDest
					lpBits:(char*)lpBits
					lpBitsInfo:(MXDBitmapInfo*)lpBitsInfo
					nXOriginSrc:(float)nXOriginSrc
					nYOriginSrc:(float)nYOriginSrc
					nWidthSrc:(float)nWidthSrc
					nHeightSrc:(float)nHeightSrc
					dwRop:(DWORD)dwRop
					bReverse:(BOOL)bReverse;

- (BOOL)stretchBltUseDeviceCoordinate_nXOriginDest:(float)nXOriginDestDevice
									  nYOriginDest:(float)nYOriginDestDevice
										nWidthDest:(float)nWidthDestDevice
									   nHeightDest:(float)nHeightDestDevice
											lpBits:(char*)lpBits
										lpBitsInfo:(MXDBitmapInfo*)lpBitsInfo
									   nXOriginSrc:(float)nXOriginSrcDevice
									   nYOriginSrc:(float)nYOriginSrcDevice
										 nWidthSrc:(float)nWidthSrcDevice
										nHeightSrc:(float)nHeightSrcDevice
								  nXOriginSrcLogic:(float)nXOriginSrcLogic
								  nYOriginSrcLogic:(float)nYOriginSrcLogic
									nWidthSrcLogic:(float)nWidthSrcLogic
								   nHeightSrcLogic:(float)nHeightSrcLogic
											 dwRop:(DWORD)dwRop
										  bReverse:(BOOL)bReverse;

- (BOOL)patBlt_x:(int)x
				y:(int)y
				nWidth:(int)nWidth
				nHeight:(int)nHeight
				dwRop:(DWORD)dwRop;

- (BOOL)stretchDIBits_XDest:(int)XDest
						YDest:(int)YDest
						nDestWidth:(int)nDestWidth
						nDestHeight:(int)nDestHeight
						XSrc:(int)XSrc
						YSrc:(int)YSrc
						nSrcWidth:(int)nSrcWidth
						nSrcHeight:(int)nSrcHeight
						lpBits:(char*)lpBits
						lpBitsInfo:(MXDBitmapInfo*)lpBitsInfo
						iUsage:(UINT)iUsage
						dwRop:(DWORD)dwRop;


- (void)setPixel:(int)x y:(int)y color:(COLORREF)color;
- (void)setPixel:(NSPoint)point color:(COLORREF)color;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- クリッピング関連メソッド群
- (int)selectClipRgn:(NSRect*)nsRects count:(int)count;
- (int)selectClipRgn:(NSRect*)nsRects count:(int)count mode:(int)nMode;


//はみ出し付箋　の　対応　start 20110331
//- (int)initClipRgn:(CGRect)clipeRect;
- (int)initClipRgnWithBoundingBox:(CGRect)clipeRect;
//はみ出し付箋　の　対応　end 20110331
- (int)extSelectClipRgn:(NSRect*)nsRects count:(int)count mode:(int)fnMode;

- (BOOL)selectClipPath:(int)nMode;

- (int)intersectClipRect_x1:(int)x1 y1:(int)y1 x2:(int)x2 y2:(int)y2;
- (int)intersectClipRect_lpRect:(LPRECT)lpRect;


// 指定されたテキストデータを適切にエンコーッディングした文字列にして返す add by C.Tamayama
- (NSString*) encodedString:(NSData*)textData;


#pragma mark -
#pragma mark Add new methods for BridgeI/F
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- new method --- added by YuFei[2010/8/18]

// Sets the miter limit for the joins of connected lines.
- (void)setMiterLimit:(float)limit;
- (BOOL)scaleWindowExt:(int)xNum xDenom:(int)xDenom yNum:(int)yNum yDenom:(int)yDenom;
- (BOOL)resizePalette:(unsigned int)palNumEntries atIndex:(unsigned long)index;
- (BOOL)setPaletteEntries:(unsigned int)position length:(unsigned int)length colorTable:(unsigned int*)color atIndex:(const unsigned long)index;
- (BOOL)setFontExtra:(long)extra;
- (BOOL)setPatternOffset:(float)x Y:(float)y;

- (CGPoint)getCurrentPoint;

// 楕円の円弧を描画します。
- (void)arc_lpRect: (LPRECT)lpRect
		startAngle: (float)startAngle
		  endAngle: (float)endAngle;

- (int)setROP3:(int)rasterOperation;
- (int)getROP3;


// For adjust divide draw location.
- (CGRect)transformRectF:(CGRect)rect;
- (CGSize)transformSizeF:(CGSize)size;

- (MXDAffineTransformManager*)getWin32Mapper;

- (bool)_isRop3Mode:(unsigned int)operation;
#pragma mark -

@end
