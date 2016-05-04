/*!
  @file  XdwBridgeHBPS.h
  @brief XdwBridgeHBPSクラスの定義を記述したIncludeファイル

  @author Tomohiro Yamada (Fuji Xelox Co., Ltd. DPC DS&S STD) <Tomohiro.Yamada@fujixerox.co.jp>
  @date 2002-04-24
  @version 0.1
 
  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Tomohiro Yamada<br>
  modified: 2002-07-19  Kenichi Ishida<br>
  分割描画対応:	2002-10-07	Kenichi.Ishida<br>
  ファイル構成変更：2003-09-01　Kunihiko.Kobayashi<br>
  View用とPrint用の２つのI/Fに分離．このヘッダから実装ヘッダを呼ぶ.
  実装ヘッダ名はXdwBridgeHBPSHeader.hとしPrintとViewで格納場所が異なる．
  それぞれアプリ側のプロジェクトファイルでリンクするファイルを選択する．<br>
 */
#ifndef _XDW_BRIDGE_HBPS_H_
#define _XDW_BRIDGE_HBPS_H_

#include "./View/XdwBridgeHBPSHeader.h"

#if !defined(HB_USE_FIXEDPOINT)
typedef float HBPS_REAL32;
typedef double HBPS_REAL64;
#define HBPS_FLT_EQ(a, b) (fabs((a) - (b)) < FLT_EPSILON)
#define HBPS_FLT_NE(a, b) (fabs((a) - (b)) >= FLT_EPSILON)
#define HBPS_FLT_EQ_ZERO(a) (fabs(a) < FLT_EPSILON)
#define HBPS_FLT_NE_ZERO(a) (fabs(a) >= FLT_EPSILON)
#define HBPS_FLT_IS_PLUS(a) ((a) > 0)
#define HBPS_FLT_IS_MINUS(a) ((a) < 0)
#else
#include "COM_HB_Fixed.h"
typedef float HBPS_REAL32;
typedef double HBPS_REAL64;
#define HBPS_FLT_EQ(a, b) ((a) == (b))
#define HBPS_FLT_NE(a, b) ((a) != (b))
#define HBPS_FLT_EQ_ZERO(a) ((a) == 0)
#define HBPS_FLT_NE_ZERO(a) ((a) != 0)
#define HBPS_FLT_IS_PLUS(a) ((a) > 0)
#define HBPS_FLT_IS_MINUS(a) ((a) < 0)
#endif

#endif /*_XDW_BRIDGE_HBPS_H_*/
