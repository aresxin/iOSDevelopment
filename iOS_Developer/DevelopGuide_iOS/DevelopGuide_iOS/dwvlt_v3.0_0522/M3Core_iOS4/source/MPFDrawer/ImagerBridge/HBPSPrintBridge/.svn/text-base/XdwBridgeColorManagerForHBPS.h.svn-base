/*!
  @file  XdwBridgeColorManagerForHBPS.h
  @brief XdwBridgeColorManagerForHBPS クラスヘッダファイル

  XdwBridgeColorManagerクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-24
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
  Modifyed:	2002-07-11	Toshio Yamazaki	XdwBridgeGraphicStateColorから変更<br>
  Modifyed:	2002-12-16	Kenichi Ishida Palette対応のため変更<br>
 */
#ifndef XDWBRIDGECOLORMANAGERHBPS_H_INCLUDED
#define XDWBRIDGECOLORMANAGERHBPS_H_INCLUDED
#include "XdwError.h"
#include "XdwColor.h"
#include "XdwBridgeCommon.h"
#include "XdwBridgeColorManager.h"

class XdwBridgeColorManagerForHBPS : public XdwBridgeColorManager {
private:
    void	*imagerF;							/*!< 出力先		*/
public:
    XdwBridgeColorManagerForHBPS( XdwBridgeGraphicStateManager*, void * );	/*!< コンストラクタ	*/
    ~XdwBridgeColorManagerForHBPS();						/*!< デストラクタ	*/

    XdwErrorCode Initialize( void );
    XdwErrorCode SetFGColor( const XdwColorSpaceID &, const XdwTypeUInt32 &);
    XdwErrorCode SetBGColor( const XdwColorSpaceID &, const XdwTypeUInt32 &);
    bool IsSupportedColorSpace( const XdwColorSpaceID & );

};
#endif /* XDWBRIDGECOLORMANAGERHBPS_H_INCLUDED */
