/*!
  @file  XdwBridgePatternDrawForHBPS.h
  @brief XdwBridgePatternDrawForHBPSクラスの定義を記述したIncludeファイル

  @author Kenichi Ishida (Fuji Xelox Co., Ltd. DPSC SDM PFG) <Kenichi.Ishida@fujixerox.co.jp>
  @date 2003-02-20
  @version 0.1
 
  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2003-02-20	Kenichi Ishida<br>
  modified: 2003-02-20  Kenichi Ishida<br>
 */
#ifndef XDWBRIDGEPATTERNDRAWFORHBPS_H_INCLUDED
#define XDWBRIDGEPATTERNDRAWFORHBPS_H_INCLUDED

#include "XdwError.h"
#include "XdwBridge.h"
#include "XdwBridgeObjectPattern.h"
#include "XdwBridgeRasterManagerForHBPS.h"
#include "XdwBridgeRasterOutputAdapterForHBPS.h"
#include "XdwBridgeGraphicStateManager.h"
#include "XdwBridgeColorManager.h"

#include "XdwBridgeObjectBrush.h"
#include "XdwBridgeObjectPen.h"
#include "XdwBridgeObjectManager.h"

class XdwBridgeRasterManagerForHBPS;

/*! HostBasedImagerに出力するPatternを管理する

  HostBasedImagerに出力するPatternを管理する．<br>
  本クラスは，HostBasedImager専用の具象クラスである．
 */
class XdwBridgePatternDrawForHBPS
{
private:
	void *imagerF;	/*!< 出力先 */
    XdwBridgeGraphicStateManager	*gstateF;	/*!< GraphicState管理クラス	*/
    XdwBridgeColorManager			*colorF;	/*!< 色管理クラス	*/
    XdwBridgeRasterManagerForHBPS	*raster_managerF;/*!< RasterManagerクラス*/
    XdwBridgeRasterOutputAdapterForHBPS *raster_outputF;/*!< Raster出力クラス	*/

	XdwBridgeObjectBrush *xdwBrushObjectF;
	XdwBridgeObjectPen	*xdwPenObjectF;

	XdwTypeUInt32 fgColorF,bgColorF;

	/* DrawPatternから呼ばれるHatch Patternの内部処理	*/
	XdwErrorCode SetHatchPattern(int);
	/* DrawPatternから呼ばれるRaster Patternの内部処理	*/
	XdwErrorCode SetRasterPattern(int);

public:
	XdwBridgePatternDrawForHBPS(void *);	/*!< コンストラクタ */

    virtual ~XdwBridgePatternDrawForHBPS();		/*!< デストラクタ */

	XdwErrorCode Initialize(XdwBridgeGraphicStateManager *,
				XdwBridgeColorManager *, XdwBridgeRasterManagerForHBPS *,
				XdwBridgeRasterOutputAdapterForHBPS *);

	XdwErrorCode DrawPattern();

	XdwErrorCode DrawRasterPattern(int, XdwBridgeObjectPattern*);

	XdwErrorCode DrawHatchPattern(int, XdwBridgeObjectPattern *, XdwPatternAttribute);
};

#endif /* XDWBRIDGEPATTERNDRAWFORHBPS_H_INCLUDED */
