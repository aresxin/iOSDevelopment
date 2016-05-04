/*!
  @file  XdwBridgeGraphicStateManager.h
  @brief XdwBridgeGraphIcStateManager クラスヘッダファイル

  XdwBridgeGraphcStateContentsクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-28
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-07-10	Toshio Yamazaki XdwBridgeGraphcStateContents, 
						XdwBridgeObjectManagerをラップするクラスとして新規作成
  Modified:	2002-09-25	Kenichi Ishida	カレント描画モードの保存を行うSetDrawMode,GetDrawModeを追加<br>
 */
#ifndef XDWBRIDGEGRAPHICSTATEMANAGER_H_INCLUDED
#define XDWBRIDGEGRAPHICSTATEMANAGER_H_INCLUDED

#include "XdwError.h"

#include "XdwRaster.h"
#include "XdwColor.h"
#include "XdwPen.h"
#include "XdwFont.h"
#include "XdwGraphicsAttribute.h"

#include "XdwBridgeGraphicStateContents.h"

class XdwBridgeObjectManager;
class XdwBridgeObjectFont;
class XdwBridgeObjectPen;
class XdwBridgeObjectBrush;
class XdwBridgeObjectPalette;

/*! Bridge内部Graphic State内部グラフィックス属性管理クラス

  Bridge内部Graphic State内部グラフィックス属性と，
  GDI オブジェクトの管理を行う．
  基本的に，各々の処理を担当するクラスをラップしてるだけ．
 */
class XdwBridgeGraphicStateManager {
private:
    XdwBridgeGraphicStateContentsVector	*gstatecontentsF;	/*!< Graphic State実体		*/
    XdwBridgeObjectManager		*objmanF;		/*!< GDI Object Manager		*/
    XdwBridgeGraphicStateContentsVector::iterator gstateF;	/*!< Current Graphic State参照	*/
    unsigned long	stackcounterF;	/*!< Stack UnderFlow確認用	*/
public:
    XdwBridgeGraphicStateManager();	/*!< コンストラクタ	*/
    ~XdwBridgeGraphicStateManager();	/*!< デストラクタ	*/

    XdwErrorCode Initialize( void );	/*!< 初期化メソッド	*/

    XdwErrorCode Save(void);
    XdwErrorCode Restore(void);

    XdwBridgeObjectManager* GetCurrentObjectManager( void );

    XdwErrorCode SetFontAlign( const XdwTextAlign & );
    XdwErrorCode GetFontAlign( XdwTextAlign * );
    XdwErrorCode SetFontExtra( const long & );
    XdwErrorCode GetFontExtra( long * );
    XdwErrorCode SetFontJustification( const long&, const long& );
    XdwErrorCode GetFontJustification( long *, long * );
    XdwErrorCode GetFontSolidColor( XdwColorSpaceID *,
				    XdwTypeUInt32 *,
				    XdwColorSpaceID *,
				    XdwTypeUInt32 * );


    XdwErrorCode SetPatternOffset( const XdwPoint & );
    XdwErrorCode GetPatternOffset( XdwPoint * );

    XdwErrorCode SetMiterLimit( const double & );
    XdwErrorCode GetMiterLimit( double * );
    XdwErrorCode GetPenSolidColor( XdwColorSpaceID *,
				   XdwTypeUInt32 *,
				   XdwColorSpaceID *,
				   XdwTypeUInt32 * );

    XdwErrorCode GetBrushSolidColor( XdwColorSpaceID *,
				     XdwTypeUInt32 *,
				     XdwColorSpaceID *,
				     XdwTypeUInt32 * );

    XdwErrorCode SetFGColor( const XdwColorSpaceID &,
			     const XdwTypeUInt32 & );
    XdwErrorCode SetBGColor( const XdwColorSpaceID &,
			     const XdwTypeUInt32 & );
    XdwErrorCode GetFGColor( XdwColorSpaceID *,
			     XdwTypeUInt32 * );
    XdwErrorCode GetBGColor( XdwColorSpaceID *,
			     XdwTypeUInt32 * );

    XdwErrorCode SetDrawMode( const XdwGSDrawMode & );
    XdwErrorCode GetDrawMode( XdwGSDrawMode * );

    XdwBridgeCTMManager* GetCurrentCTMManager( void );

    XdwErrorCode SetFillRule( const XdwGSFillRule & );
    XdwErrorCode GetFillRule( XdwGSFillRule * );
    XdwErrorCode SetRasterSmoothingMode( const XdwRasterSmoothingMode & );
    XdwErrorCode GetRasterSmoothingMode( XdwRasterSmoothingMode * );
    XdwErrorCode SetBackGroundMode( const XdwGSBackGroundMode & );
    XdwErrorCode GetBackGroundMode( XdwGSBackGroundMode * );
    XdwErrorCode SetArcWiseMode( const XdwArcWiseMode & );
    XdwErrorCode GetArcWiseMode( XdwArcWiseMode * );
    XdwErrorCode SetRopMode( const XdwGSRopMode &,
			     const XdwTypeUInt32 & );
    XdwErrorCode GetRopMode( XdwGSRopMode *,
			     XdwTypeUInt32 * );
    XdwErrorCode SetCurrentPoint( const XdwPoint & );
    XdwErrorCode GetCurrentPoint( XdwPoint * );
};

#endif /* XDWBRIDGEGRAPHICSTATEMANAGER_H_INCLUDED */
