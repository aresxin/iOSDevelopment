/*!
  @file  XdwBridge.h
  @brief Bridge クラスヘッダファイル

  各種DecomposerのI/Fを隠蔽し，ControlerやPDDecoderへ
  Decomposer機能を提供するBridgeクラスの総合インクルードファイル．<br>
  I/Fを構成するクラスは，XdwBridgePrintContIF, XdwBridgeViewerContIF, XdwBridgeDrawIF
  であり，具象クラスは制御系と描画系の2つのI/Fクラスをpublic継承する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-03-28
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-03-28	Toshio Yamazaki<br>
  Modified:	2002-04-30	Toshio Yamazaki	XdwBridgeDrawIF.h,XdwBridgePrintContIF.h　に分解<br>
 */
#ifndef XDWBRIDGE_H_INCLUDED
#define XDWBRIDGE_H_INCLUDED

#include "XdwBridgeDrawIF.h"

#ifdef DOCUWORKS_VIEWER
#include "XdwBridgeViewerContIF.h"
#else
#include "XdwBridgePrintContIF.h"
#endif

#endif /* XDWBRIDGE_H_INCLUDED */
