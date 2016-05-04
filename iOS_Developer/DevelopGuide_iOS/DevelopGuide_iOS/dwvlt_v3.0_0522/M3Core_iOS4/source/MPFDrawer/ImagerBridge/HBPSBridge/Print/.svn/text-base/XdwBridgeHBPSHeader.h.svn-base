/*!
  @file  XdwBridgeHBPSHeader.h
  @brief XdwBridgeHBPSHeaderクラスの定義を記述したIncludeファイル

  @author Tomohiro Yamada (Fuji Xelox Co., Ltd. DPC DS&S STD) <Tomohiro.Yamada@fujixerox.co.jp>
  @date 2002-04-24
  @version 0.1
 
  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Tomohiro Yamada<br>
  modified: 2002-07-19  Kenichi Ishida<br>
  分割描画対応:	2002-10-07	Kenichi.Ishida<br>
 */
#ifndef _XDW_BRIDGE_HBPS_HEADER_H_
#define _XDW_BRIDGE_HBPS_HEADER_H_


#include "XdwError.h"
#include "XdwBridge.h"

#ifdef BRIDGE_HBPS_PRINT

/* 
将来的には用途依存にしないようにする
工夫ができればいいが
必要になったら変数を増やす
*/

typedef struct{
	long out_format;
	long out_formatMode;
	long job_dlSize1;
	long job_dlSize2;
	long job_rbSize;
	long job_outputResolutionX;
	long job_outputResolutionY;
	long job_imageResolutionX;
	long job_imageResolutionY;
	char job_directoryPath[260];
	char spl_localFileName[260];
	long spl_localFileNoTruncate;			/* ローカルファイルOpen時に　0：内容破棄，1：内容保存	*/
	long spl_localFileOffset;				/* ローカルファイルOpen時の書き出し位置の指定			*/
	long spl_localFileOrigin;				/* ローカルファイルOpen時の書き出し基準位置の指定		*/
	long patternResolution;
	void *extraParam; 
} BridgeHBPSPrintJobInfo;

typedef struct{
	long page_colorMode;
    long page_pageWidth;
    long page_pageHeight;
	char spl_localFileName[260];
	long spl_localFileNoTruncate;			/* ローカルファイルOpen時に　0：内容破棄，1：内容保存	*/
	long spl_localFileOffset;				/* ローカルファイルOpen時の書き出し位置の指定			*/
	long spl_localFileOrigin;				/* ローカルファイルOpen時の書き出し基準位置の指定		*/
	long *extraParam; 
} BridgeHBPSPrintPageInfo;

#endif


/* インターフェースの定義のためのIncludeファイル */
#include "XdwBridgeDrawIF.h"
#include "XdwBridgeViewerContIF.h"
#ifdef BRIDGE_HBPS_PRINT
#include "XdwBridgePrintContIF.h"
#endif
#include "XdwBridgeHBPSInternal.h"

/* ログ出力用インターフェースの宣言 */
class XdwLogInterface;

/* Bridge I/Fにて定義される共通クラスの先行宣言 */
class XdwBridgeGraphicStateManager;
class XdwBridgeObjectFont;
class XdwBridgeObjectBrush;
class XdwBridgeObjectPattern;
class XdwBridgeObjectPen;
class XdwBridgeObjectPalette;

/* Graphic描画処理を行うクラス群の先行宣言 */
class XdwBridgeGDCommonForHBPS;
class XdwBridgeGDRectangleForHBPS;

/* Graphic State の処理を行うクラス群の先行宣言 */
class XdwBridgeGraphicStatePen;
class XdwBridgeGraphicStateBrush;
class XdwBridgeGraphicStatePalette;
class XdwBridgeColorManager;

/* Raster の処理を行うクラス群の先行宣言 */
class XdwBridgeRasterManagerForHBPS;
class XdwBridgeRasterOutputAdapterForHBPS;
class XdwBridgePatternDrawForHBPS;
class XdwBridgeRopStateForHBPS;

/**
 * @brief DocuWorksDecoder用の各メソッドのパラメータをLogファイルに記述するクラス
 */
#ifdef BRIDGE_HBPS_PRINT
class XdwBridgeHBPS : public XdwBridgePrintContIF, public XdwBridgeDrawIF
#else
class XdwBridgeHBPS : public XdwBridgeViewerContIF, public XdwBridgeDrawIF
#endif
{
protected:
	/*! HostBasedイメージャ関連 */

	XdwRectangle pageBoundingBox;

#ifdef BRIDGE_HBPS_PRINT

	/* 直接宣言するとなぜかエラーとなる
	CST_Parameter CSTparam;
	HB_JobParam jobParam;
	HB_SpoolParam spoolParam;
	HB_OutputParam outParam;
	HB_PageParam pageParam;
	*/

	void *CSTParam;
	void *jobParam;
	void *outParam;
	void *jobSplParam;
	void *pageSplParam;
	void *pageParam;

	/* 上記に含まれないもの */

	long patternResolution;

	void *jobExtraParam;
	void *pageExtraParam;

#else

	unsigned short resoX;
	unsigned short resoY;
	long pageWidth;
	long pageHeight;

#endif

	/* パス構築状態　*/
	int	path_state;

	/* カレントフォント情報 */
	XdwFontInfo *currentFont;
	unsigned char currentFontCharSet;

    /*! Logファイルを記述するためのインターフェース */
    XdwLogInterface* fXdwLogInterface;
    
    /********************************************/
    char fBuffer[1024];
    char fString[1024];
    XdwErrorCode fState;
    unsigned long fHandleCount;
    /********************************************/
    
    void *imagerF;		/*!< 出力先 */

	XdwBridgeGDCommonForHBPS		*gd_commonF;	/*!< 共通描画クラス	*/
	XdwBridgeGDRectangleForHBPS		*gd_rectangleF;	/*!< 矩形描画クラス	*/

    XdwBridgeGraphicStatePen		*penF;		/*!< Penクラス		*/
    XdwBridgeGraphicStateBrush		*brushF;	/*!< Brushクラス	*/
    XdwBridgeColorManager			*colorF;	/*!< 色管理クラス	*/
    XdwBridgeGraphicStateManager	*gstateF;	/*!< GraphicState管理クラス	*/

    XdwBridgeRasterManagerForHBPS	*raster_managerF;/*!< RasterManagerクラス*/
    XdwBridgeRasterOutputAdapterForHBPS *raster_outputF;/*!< Raster出力クラス	*/
	XdwBridgePatternDrawForHBPS		*pattern_drawF; /*!< FG,BG設定が必要なパターン描画用クラス */
	XdwBridgeRopStateForHBPS		*rop_stateF;	/*!< ROP設定状態管理クラス */

    XdwErrorCode NewObject( void );				/*!< 内部オブジェクト生成メソッド	*/

    XdwErrorCode SelectFontObject( XdwBridgeObjectFont* );
    XdwErrorCode SelectBrushObject( XdwBridgeObjectBrush* );
    XdwErrorCode SelectPenObject( XdwBridgeObjectPen* );
    XdwErrorCode SelectPaletteObject( XdwBridgeObjectPalette* );

    XdwErrorCode InitClip( void );
    XdwErrorCode InitPath( void );

    char* UnicodeToMBCS(unsigned char *, long );	    /*!< Unicode -> MBCS変換 */

    /***************************************************/
    /*! @name XdwBridgeHBPSPrivate */
    /***************************************************/
    XdwErrorCode ConvertXdwMatrix2imgMatrix( const XdwMatrix&, HBPS_Matrix * );
    XdwErrorCode ConvertXdwRectangle2imgSaRect( const XdwRectangle&, HBPS_RectangleData * );
	XdwErrorCode GetInvertMatrix33( XdwMatrix *, XdwMatrix * );
	XdwErrorCode TransRectangle( XdwRectangle *, XdwRectangle *, XdwMatrix * );
	XdwErrorCode MatrixRectangleTransform( XdwMatrix *, XdwRectangle * );
    XdwErrorCode SetCTMtoHBPS(void);
    XdwErrorCode SetDrawMode( const XdwGSDrawMode );

	int ConvertDrawMode( const XdwGSDrawMode & );
    int ConvertXdwGSClipLogic2rndcliplogic( const XdwGSClipLogic & );
	double GetArcAngle(const XdwPoint &, double, double);

	XdwErrorCode ApplyPageBBoxClipWithAndLogic();	//< カレントクリップ領域にページバウンディングボックス領域のクリップをANDロジックで適用する


#ifdef BRIDGE_HBPS_PRINT
	XdwErrorCode CreateDefaultParameter( void );
	XdwErrorCode DeleteDefaultParameter( void );
#endif

public:

	XdwBridgeHBPS();			/*!< コンストラクタ */
	~XdwBridgeHBPS();			/*!< デストラクタ */

	XdwErrorCode Initialize(XdwLogInterface *);	/*!< 初期化メソッド */

    /***************************************************/
    /*! @name XdwBridgeViewerContIF
     * XdwBridgeViewerContIF classを継承したメソッドの実体
     */
    /***************************************************/
    /*@{*/
#ifdef BRIDGE_HBPS_PRINT
	XdwErrorCode InitializeContIF( void );
	XdwErrorCode StartJob( void );
	XdwErrorCode EndJob( void );
	XdwErrorCode StartPage( const XdwBridgePrintContIF::PageMode &pm );
	XdwErrorCode ShowPage( void );
	XdwErrorCode EndPage( void );
	XdwErrorCode Terminate( void ); /* added */
	XdwErrorCode SetJobInfo( void* jobinfo); /* added */
	XdwErrorCode SetPageInfo( void* pageinfo ); /* added */
	XdwErrorCode ErrorTerminate( void ); /* added AR1563 */
#else
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
#endif
    /*@{*/
    
    /***************************************************/
    /*! @name XdwBridgeDrawIF
     * XdwBridgeDrawIF classを継承したメソッドの実体
     */
    /***************************************************/
    /*@{*/
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
    XdwErrorCode DrawPixel( const XdwPoint &, const XdwTypeUInt32 &, XdwColorSpaceID );

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
};

#endif /*_XDW_BRIDGE_HBPS_H_*/
