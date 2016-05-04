/*!
  @file  XdwBridgeGraphicStateContents.h
  @brief XdwBridgeGraphcStateContents クラスヘッダファイル

  XdwBridgeGraphcStateContentsクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-28
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-28	Toshio Yamazaki<br>
  Modified:	2002-07-05	Toshio Yamazaki	BridgeIF以下に移動<br>
  Modified:	2002-07-05	Toshio Yamazaki	新BridgeIF用に修正<br>
  Modified:	2002-09-25	Kenichi Ishida	カレント描画モードの保存を行う SetDrawMode, GetDrawModeを追加<br>
										描画モードのパラメータは drawmodeF<br>
 */
#ifndef XDWBRIDGEGRAPHICSTATECONTENTS_H_INCLUDED
#define XDWBRIDGEGRAPHICSTATECONTENTS_H_INCLUDED

#include "XdwError.h"
#include "XdwStl.h"

#include "XdwRaster.h"
#include "XdwColor.h"
#include "XdwPen.h"
#include "XdwFont.h"
#include "XdwGraphicsAttribute.h"

#include "XdwBridgeCTMManager.h"

/*! Bridge内部Graphic State内部グラフィックス属性の実データクラス

  Bridge内部Graphic State内部グラフィックス属性のスタック上に積まれる，
  グラフィックス属性の実データである．実際は，vector テンプレートにより，
  スタック構造を構成する．
 */
class XdwBridgeGraphicStateContents {
private:
    XdwTextAlign		textalignF;	/*!< Text Align属性		*/
    long			text_charextraF;/*!< 文字毎に追加する文字間隔	*/
    long			text_lineextraF;/*!< 行に追加するスペース量	*/
    long			text_spacenumF;	/*!< 行内の空白文字数		*/

    XdwPoint			pattern_offsetF;/*!< Patternオフセット値	*/

    double			miterlimitF;	/*!< Miter Limit値		*/

    XdwColorSpaceID		fgcolorspaceF;	/*!< FG Color Space		*/
    XdwTypeUInt32		fgcolorF;	/*!< FG Color			*/
    XdwColorSpaceID		bgcolorspaceF;	/*!< BG Color Space		*/
    XdwTypeUInt32		bgcolorF;	/*!< BG Color			*/

    XdwGSDrawMode		drawmodeF;	/*!< DrawMode			*/

    XdwBridgeCTMManager		ctm_managerF;	/*!< CTM関連属性の実体と操作	*/

    XdwGSFillRule		fillruleF;	/*!< Fill Rule			*/
    XdwRasterSmoothingMode	rastermodeF;	/*!< Raster Smooth Mode		*/
    XdwGSBackGroundMode		bgmodeF;	/*!< Back Ground Mode		*/
    XdwArcWiseMode		arcmodeF;	/*!< Arc Wise Mode		*/
    XdwGSRopMode		ropmodeF;	/*!< Rop Mode多分2固定		*/
    XdwTypeUInt32		ropcodeF;	/*!< Rop Code MSDN参照		*/

    XdwPoint			current_pointF;	/*!< Current Point		*/

public:
    XdwBridgeGraphicStateContents();	/*!< コンストラクタ	*/
    ~XdwBridgeGraphicStateContents();	/*!< デストラクタ	*/

    XdwErrorCode Initialize( void );	/*!< 初期化メソッド	*/

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

#include <vector>
typedef XdwStlVector(XdwBridgeGraphicStateContents)	XdwBridgeGraphicStateContentsVector;	/*!< GStat用Vector */

#endif /* XDWBRIDGEGRAPHICSTATECONTENTS_H_INCLUDED */
