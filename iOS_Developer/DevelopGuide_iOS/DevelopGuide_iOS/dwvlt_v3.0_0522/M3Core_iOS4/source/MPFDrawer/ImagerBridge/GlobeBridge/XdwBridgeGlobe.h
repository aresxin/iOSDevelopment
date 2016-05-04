/*!
  @file  XdwBridgeGlobe.h
  @brief BridgeGlobe クラスヘッダファイル

  このXdwBridgeを継承したXdwBridgeGlobe classは，
  Globe DecomposerのImagerを隠蔽してクライアントに対して，
  共通のBridge I/Fを提供する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-04-08
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-08	Toshio Yamazaki<br>
  Modified:	2002-07-08	Toshio Yamazaki	新BridgeIF用に修正<br>
 */
#ifndef XDWBRIDGEGLOBE_H_INCLUDED
#define XDWBRIDGEGLOBE_H_INCLUDED

#include "XdwError.h"
#include "XdwBridge.h"

/* imgImager クラス関連で必要なクラスの先行宣言 */
class imgImager;	/*!< imgImagerクラスの先行宣言		*/
class sifDevice_Info;	/*!< sifDevice_Infoクラスの先行宣言	*/
class imgMatrix32;	/*!< imgMatrix32クラスの先行宣言	*/
class imgSaRect;	/*!< imgSaRectクラスの先行宣言		*/

/* Bridge I/Fにて定義される共通クラスの先行宣言 */
class XdwBridgeGraphicStateManager;
class XdwBridgeObjectFont;
class XdwBridgeObjectBrush;
class XdwBridgeObjectPen;
class XdwBridgeObjectPalette;

/* Graphic描画処理を行うクラス群の先行宣言 */
class XdwBridgeGDCommonForGlobe;
class XdwBridgeGDRectangleForGlobe;

/* Font管理と描画を行うクラス群の先行宣言 */
class XdwBridgeFontManagerForGlobe;
class XdwBridgeFontDrawForGlobe;

/* Graphic State の処理を行うクラス群の先行宣言 */
class XdwBridgeGraphicStatePen;		/*!< XdwBridgePenクラスの先行宣言			*/
class XdwBridgeGraphicStateBrush;	/*!< XdwBridgeBrushクラスの先行宣言			*/
class XdwBridgeColorManager;

/* Raster の処理を行うクラス群の先行宣言 */
class XdwBridgeRasterManagerForGlobe;
class XdwBridgeRasterOutputAdapterForGlobe;

/*! Globe用のBridgeクラス

  Bridgeクラスの具象クラス．<br>
  メソッド呼び出しや引数をGlobe Imagerに合うように変換し，
  Globe Imageへ出力する．
 */
class XdwBridgeGlobe : public XdwBridgePrintContIF, public XdwBridgeDrawIF {
private:
    int			call_number_of_init;	/*!< Initializeを読んだ回数DEBUG用 */

    imgImager		*imagerF;		/*!< 出力先 */
    sifDevice_Info	*diF;			/*!< Devince Infomation class */
    XdwBridgePrintContIF::PageMode pagemodeF;	/*!< ページモード */

    XdwBridgeGDCommonForGlobe		*gd_commonF;	/*!< 共通描画クラス	*/
    XdwBridgeGDRectangleForGlobe	*gd_rectangleF;	/*!< 矩形描画クラス	*/

    XdwBridgeFontManagerForGlobe	*font_managerF;	/*!< FontManagerクラス	*/
    XdwBridgeFontDrawForGlobe		*fontF;		/*!< Font描画クラス	*/

    XdwBridgeGraphicStatePen		*penF;		/*!< Penクラス		*/
    XdwBridgeGraphicStateBrush		*brushF;	/*!< Brushクラス	*/
    XdwBridgeColorManager		*colorF;	/*!< 色管理クラス	*/

    XdwBridgeGraphicStateManager	*gstateF;	/*!< GraphicState管理クラス	*/

    XdwBridgeRasterManagerForGlobe	*raster_managerF;/*!< RasterManagerクラス*/
    XdwBridgeRasterOutputAdapterForGlobe *raster_outputF;/*!< Raster出力クラス	*/

    XdwErrorCode NewObject( void );	/*!< 内部オブジェクト生成メソッド	*/

    XdwErrorCode ConvertXdwMatrix2imgMatrix( const XdwMatrix&, imgMatrix32 * );
    XdwErrorCode ConvertXdwRectangle2imgSaRect( const XdwRectangle&, imgSaRect * );
    int ConvertXdwGSClipLogic2rndcliplogic( const XdwGSClipLogic & );

    XdwErrorCode SelectFontObject( XdwBridgeObjectFont* );
    XdwErrorCode SelectBrushObject( XdwBridgeObjectBrush* );
    XdwErrorCode SelectPenObject( XdwBridgeObjectPen* );
    XdwErrorCode SelectPaletteObject( XdwBridgeObjectPalette* );

    XdwErrorCode SetCTMtoGLOBE(void);
    XdwErrorCode InitClip( void );
    XdwErrorCode InitPath( void );
public:
    XdwBridgeGlobe();			/*!< コンストラクタ */
    ~XdwBridgeGlobe();			/*!< デストラクタ */

    XdwErrorCode Initialize( imgImager *, sifDevice_Info * );	/*!< 初期化メソッド */

    /***************************************************/
    /*! @name XdwBridgePrintContIF
     * XdwBridgePrintContIF classを継承したメソッドの実体
     */
    /***************************************************/
    /*@{*/
    XdwErrorCode InitializeContIF( void );
    XdwErrorCode StartJob( void );
    XdwErrorCode EndJob( void );
    XdwErrorCode StartPage( const XdwBridgePrintContIF::PageMode &pm );
    XdwErrorCode ShowPage( void );
    XdwErrorCode EndPage( void );
    /*@}*/

    /***************************************************/
    /*! @name XdwBridgeDrawIF
     * XdwBridgeDrawIF classを継承したメソッドの実体
     */
    /***************************************************/
    /*@{*/
    XdwErrorCode InitializeDrawIF( void );
    XdwErrorCode InitializeDrawParameter( void );
    XdwErrorCode SelectObject( const unsigned long &handle  );
    XdwErrorCode DeleteObject( const unsigned long &handle  );

    XdwErrorCode CreateFont( const XdwFontInfo &font, unsigned long &handle );
    XdwErrorCode SetFontAlign( XdwTextAlign align );
    XdwErrorCode SetFontExtra( const long &extra );
    XdwErrorCode SetFontJustification( const long &extra, const long &count );
    XdwErrorCode DrawFont( const XdwPoint &p, const XdwCodeText &text );

    XdwErrorCode SetPatternOffset( const XdwPoint &offset );

    XdwErrorCode CreatePen( const XdwPenAttribute &para,
			    const XdwPatternAttribute &pattern,
			    const XdwRasterImageAttribute &image,
			    XdwDataObject::Binary *imagedata,
			    const long &offset,
			    const long &size,
			    unsigned long &handle );
    XdwErrorCode SetMiterLimit( double limit );

    XdwErrorCode CreateBrush( const XdwPatternAttribute &pattern,
			      const XdwRasterImageAttribute &image,
			      XdwDataObject::Binary *imagedata,
			      const long &offset,
			      const long &size,
			      unsigned long &handle );
    

    XdwErrorCode SetFGColor( const XdwTypeUInt32 &color,
			     XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );
    XdwErrorCode SetBGColor( const XdwTypeUInt32 &color,
			     XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );

    XdwErrorCode CreatePalette( const XdwColorPalette &palette,
				unsigned long &handle );
    XdwErrorCode SelectPalette( const unsigned long &handle ); 
    XdwErrorCode SetPaletteEntries( const unsigned long &handle,
				    const long &position,
				    const XdwUInt32Vector &color );
    XdwErrorCode ResizePalette( const unsigned long &handle,
				const long &entries );
    XdwErrorCode RealizePalette( void );

    XdwErrorCode SetCurrentTransferMatrix( const XdwMatrix &matrix,
					   unsigned long width, unsigned long height,
					   unsigned long xdpi, unsigned long ydpi );
    XdwErrorCode SetTransferMatrixMode( XdwTransferMatrixMode mode );

    XdwErrorCode ScaleViewport( const double &xscale,
				const double &yscale );
    XdwErrorCode OffsetViewport( const double &x,
				 const double &y );
    XdwErrorCode ExtentViewport( const double &width,
				 const double &height );

    XdwErrorCode ScaleWindow( const double &xscale,
			      const double &yscale );
    XdwErrorCode OffsetWindow( const double &x,
			       const double &y );
    XdwErrorCode ExtentWindow( const double &width,
			       const double &height );

    XdwErrorCode SetFillRule( XdwGSFillRule rule );
    XdwErrorCode SetRasterSmoothingMode( XdwRasterSmoothingMode mode );
    XdwErrorCode SetBackGroundMode( XdwGSBackGroundMode mode );
    XdwErrorCode SetWiseMode( XdwArcWiseMode mode );
    XdwErrorCode SetRopMode( XdwGSRopMode ropmode,
			     XdwTypeUInt32 ropcode );

    XdwErrorCode Save( void );
    XdwErrorCode Restore( void );

    XdwErrorCode SetRectangleToClip( const XdwRectangleVector &rect,
				     XdwGSClipLogic mode);
    XdwErrorCode SetPathToClip( XdwGSClipLogic mode );
    XdwErrorCode OffsetClip( const XdwPoint & offset );

    XdwErrorCode SetCurrentPoint( const XdwPoint &p );
    XdwErrorCode ClosePath( void );
    XdwErrorCode BeginPath( void );
    XdwErrorCode EndPath( void );

    XdwErrorCode DrawLineSet( const XdwPointVector &p,
			      bool update );
    XdwErrorCode DrawPolygon( const XdwPointVector &p );

    XdwErrorCode DrawBezierSet( const XdwPointVector &p,
				bool update );
    XdwErrorCode DrawEllipse( const XdwEllipse &shape,
			      XdwGSDrawMode mode );
    XdwErrorCode DrawRectangle( const XdwRectangle &shape );
    XdwErrorCode DrawArc( const XdwArc &shape );
    XdwErrorCode DrawRoundRect( const XdwRoundRect &shape );

    XdwErrorCode DrawPath( XdwGSDrawMode mode );

    XdwErrorCode DrawImage( const XdwRasterImageAttribute &image,
			    XdwDataObject::Binary *imagedata,
			    const long &image_offset, const long &image_size,
			    const XdwRasterImageAttribute &mask,
			    XdwDataObject::Binary *maskdata,
			    const long &mask_offset, const long &mask_size );
    XdwErrorCode StartDrawDividedImage( const XdwRasterImageAttribute &image,
					XdwDataObject::Binary *imagedata,
					const long& image_offset,
					const long& image_size,
					const XdwRasterImageAttribute &mask,
					XdwDataObject::Binary *maskdata,
					const long& mask_offset,
					const long& mask_size,
					long nlines );
    XdwErrorCode DrawDividedImage( void );
    XdwErrorCode EndDrawDividedImage( void );
    /*@}*/
};

/* DEBUG用マクロ */
#ifdef XDWBRIDGEGLOBE_DEBUG
#define XDWERRPRINT_FUNCCALLPRINT(m) fprintf( stderr, "Called\tXdwBridgeGlobe::%s\n",m);
#else
#define XDWERRPRINT_FUNCCALLPRINT(m) NULL
#endif	/* XDWBRIDGEGLOBE_DEBUG */

#endif /* XDWBRIDGEGLOBE_H_INCLUDED */
