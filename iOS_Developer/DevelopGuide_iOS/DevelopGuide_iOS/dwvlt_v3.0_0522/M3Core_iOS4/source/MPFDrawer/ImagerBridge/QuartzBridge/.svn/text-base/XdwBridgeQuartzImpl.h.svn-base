/*
 *  XdwBridgeQuartz.h
 *  DWMacBridge
 *
 *  Created by FX Neusoft on 10-7-27.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "../BridgeIF/XdwBridgeDrawIF.h"
#import "../BridgeIF/XdwBridgeViewerContIF.h"

#import "./gdi/MXDDeviceContext.h"

// Draw Image from HBPS
#import "XdwRasterDrawImage.h"
#import "XdwBridgeRasterOutputAdapterMac.h"

class XdwBridgeQuartzImpl : public XdwBridgeDrawIF, public XdwBridgeViewerContIF
{
	// member variables and functions
protected:
	
	XdwRectangle pageBoundingBox;
	
	// 解像度
	unsigned short resoX;
	unsigned short resoY;

	// オフスクリーンサイズ
	long pageWidth;
	long pageHeight;
	
	// draw mode
	XdwGSDrawMode _drawMode;
	XdwGSFillRule _fillMode;
	XdwGSBackGroundMode _bkMode;
	XdwGSRopMode _ropMode;
	XdwTransferMatrixMode _ctmMode;
	
	// wise mode
	XdwArcWiseMode _wiseMode;
	
	// text position
	MXD_TextPosition _textPosition;
	
	/* Mac GDI device conxt eumulator */
	MXDDeviceContext *dc;
	
	// Draw Image from HBPS
	XdwRasterDrawImage* _raster_draw_image;
	XdwBridgeRasterOutputAdapter* _rester_outputF;
	NSAutoreleasePool *autoReleasePool;
	int dc_relative_clip;
	
	// for Font
	unsigned char _currentFontCharset;
	long _currentFontHeight;
	
#ifdef _XDW2BMP_DEBUG
	// CGContextRef for output
	CGContextRef imageContext;
#endif

public:
	XdwBridgeQuartzImpl();
	virtual ~XdwBridgeQuartzImpl();
	
#pragma mark TODO::List debug interface
	// XdwErrorCode Initialize(XdwLogInterface *);	/*!< 初期化メソッド */
	
#pragma mark -
#pragma mark XdwBridgeViewerContIF class methods
	/***************************************************/
    /*! @name XdwBridgeViewerContIF
     * XdwBridgeViewerContIF classを継承したメソッドの実体
     */
    /***************************************************/
    /*@{*/
	XdwErrorCode InitializeContIF( void );
	XdwErrorCode InitializeContIF( unsigned short , unsigned short , long , long  );
	XdwErrorCode SetBoundingBox( const XdwRectangle & );
	/*	AR1170 (オフスクリーン切替時のImager終了処理は呼び出し側で行う)
	 XdwErrorCode SetOffScreen( XdwOffScreen *, bool  ); */
	XdwErrorCode SetOffScreen( XdwOffScreen *);
	XdwErrorCode StartJob( void );
	XdwErrorCode EndJob( void );
	XdwErrorCode Terminate( void );
	XdwErrorCode StartPage( int, int, long, long, unsigned char *, long , void * );
	XdwErrorCode ShowPage( void );
	XdwErrorCode EndPage( void );
    /*@{*/
	
#pragma mark -
#pragma mark XdwBridgeDrawIF classを継承したメソッドの実体
	/***************************************************/
    /*! @name XdwBridgeDrawIF
     * XdwBridgeDrawIF classを継承したメソッドの実体
     */
    /***************************************************/
    /*@{*/
	
	// Draw interface initialize
	XdwErrorCode InitializeDrawIF( void );
	XdwErrorCode InitializeDrawParameter( void );
	XdwErrorCode SelectObject( const unsigned long & );
	XdwErrorCode DeleteObject( const unsigned long & );
    
    XdwErrorCode CreateFont( const XdwFontInfo &, unsigned long & );
    XdwErrorCode SetFontAlign( XdwTextAlign );
    XdwErrorCode SetFontExtra( const long & );
    XdwErrorCode SetFontJustification( const long &, const long & );
    XdwErrorCode DrawFont( const XdwPoint &, const XdwCodeText & );
	
    XdwErrorCode SetPatternOffset( const XdwPoint & );
    XdwErrorCode CreatePen( const XdwPenAttribute &,
						   const XdwPatternAttribute &, const XdwRasterImageAttribute &,
						   XdwDataObject::Binary *, const long &, const long &, unsigned long & );
    XdwErrorCode SetMiterLimit( double limit );
    XdwErrorCode CreateBrush( const XdwPatternAttribute &, const XdwRasterImageAttribute &,
							 XdwDataObject::Binary *, const long &, const long &, unsigned long & );
    
    XdwErrorCode SetFGColor( const XdwTypeUInt32 &, XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );
    XdwErrorCode SetBGColor( const XdwTypeUInt32 &, XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );
	
    XdwErrorCode CreatePalette( const XdwColorPalette &, unsigned long & );
    XdwErrorCode SelectPalette( const unsigned long & ); 
    XdwErrorCode SetPaletteEntries( const unsigned long &,
								   const long &, const XdwUInt32Vector & );
    XdwErrorCode ResizePalette( const unsigned long &, const long & );
    XdwErrorCode RealizePalette( void );
	
    XdwErrorCode SetCurrentTransferMatrix( const XdwMatrix &,
										  unsigned long , unsigned long ,
										  unsigned long , unsigned long );
    XdwErrorCode SetTransferMatrixMode( XdwTransferMatrixMode );
    XdwErrorCode ScaleViewport( const double &, const double & );
    XdwErrorCode OffsetViewport( const double &, const double & );
    XdwErrorCode ExtentViewport( const double &, const double & );
    XdwErrorCode ScaleWindow( const double &, const double & );
    XdwErrorCode OffsetWindow( const double &, const double & );
    XdwErrorCode ExtentWindow( const double &, const double & );
	
    XdwErrorCode SetFillRule( XdwGSFillRule rule );
    XdwErrorCode SetRasterSmoothingMode( XdwRasterSmoothingMode );
    XdwErrorCode SetBackGroundMode( XdwGSBackGroundMode );
    XdwErrorCode SetWiseMode( XdwArcWiseMode );
    XdwErrorCode SetRopMode( XdwGSRopMode , XdwTypeUInt32 );
	
    XdwErrorCode Save( void );
    XdwErrorCode Restore( void );
	
	// 最後の引数は、矩形座標値がデバイス座標系での値かどうかを指定する (trueならデバイス座標系)
	// ExtSelectClipRegionの引数は (他のレコードと異なり) デバイス座標系指定のため,
	// このメンバを追加した. デフォルトはfalse (ユーザー座標系).
	XdwErrorCode SetRectangleToClip(const XdwRectangleVector&, XdwGSClipLogic, bool device_unit = false);
	
    XdwErrorCode SetPathToClip( XdwGSClipLogic );
    XdwErrorCode OffsetClip( const XdwPoint & );
	
    XdwErrorCode SetCurrentPoint( const XdwPoint &p );
    XdwErrorCode ClosePath( void );
    XdwErrorCode BeginPath( void );
    XdwErrorCode EndPath( void );
	
    XdwErrorCode DrawLineSet( const XdwPointVector &, bool );
    XdwErrorCode DrawPolygon( const XdwPointVector & );
    XdwErrorCode DrawBezierSet( const XdwPointVector &, bool );
    XdwErrorCode DrawEllipse( const XdwEllipse &, XdwGSDrawMode );
    XdwErrorCode DrawRectangle( const XdwRectangle & );
    XdwErrorCode DrawPolyPolyPatBlt( XdwGSRopMode ropMode, XdwTypeUInt32 ropCode,
									short nrect, short blocks, short startY,
									XdwShortVector	&lines,	XdwShortVector	&colums,
									XdwShortVector	&height, XdwShortVector	&x,	XdwShortVector &width );
    XdwErrorCode DrawArc( const XdwArc & );
    XdwErrorCode DrawRoundRect( const XdwRoundRect & );
    XdwErrorCode DrawPath( XdwGSDrawMode );
    XdwErrorCode DrawPixel( const XdwPoint &, const XdwTypeUInt32 &, XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );
	
    XdwErrorCode DrawImage( const XdwRasterImageAttribute &, XdwDataObject::Binary *,
						   const long &, const long &, const XdwRasterImageAttribute &,
						   XdwDataObject::Binary *, const long &mask_offset, const long & );
    XdwErrorCode StartDrawDividedImage(
									   const XdwRasterImageAttribute &, XdwDataObject::Binary *,
									   const long &, const long &, const XdwRasterImageAttribute &,
									   XdwDataObject::Binary *, const long &, const long &, long);
	XdwErrorCode DrawDividedImage( void );
	XdwErrorCode EndDrawDividedImage( void );
    /*@}*/

#pragma mark -
#pragma mark private methods
private:
	/*
	 *  Convert a decimal to fraction.
	 *
	 *  引数:
	 *		decimal	: IN  : a decimal to be converted.
	 *		num     : OUT : numerator
	 *		denom	: OUT : denominator
	 *
	 *  返り値: 成功したらYESを返す
	 */
	XdwErrorCode DecimalToFraction(const double &decimal, int &num, int &denom);
	
	DWORD RGBColorChange(DWORD color);
	
#ifdef _XDW2BMP_DEBUG
	CGContextRef DebugCreateBitmapContext (int pixelsWide, int pixelsHigh);
	BOOL SaveCGImageToFile(CGImageRef imageRef);
#endif
};

#pragma mark -

