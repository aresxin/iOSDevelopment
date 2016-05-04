/*!
  @file  XdwBridgeGraphicStateBrush.h
  @brief XdwBridgeGraphicStateBrush クラスヘッダファイル

  XdwBridgeGraphicStateBrushクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-24
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEGRAPHICSTATEBRUSH_H_INCLUDED
#define XDWBRIDGEGRAPHICSTATEBRUSH_H_INCLUDED

#include "XdwError.h"

/*! Bridge内部Graphic State内部Brush属性管理クラス

  Graphic State内のBrush属性の管理を行う抽象クラス．<br>
  XdwBridgeGraphicState classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのBrush属性の管理を行う．
 */
class XdwBridgeGraphicStateBrush {
public:
    XdwBridgeGraphicStateBrush();		//!< コンストラクタ
    virtual ~XdwBridgeGraphicStateBrush();	//!< デストラクタ

    virtual XdwErrorCode Initialize( void );	//!< 初期化メソッド
};

//class imgImager;	//!< imgImagerクラスの先行宣言

class XdwBridgeGraphicStateBrushForHBPS : public XdwBridgeGraphicStateBrush {
private:
	void *imagerF;
public:
    XdwBridgeGraphicStateBrushForHBPS( void * );	//!< コンストラクタ
    ~XdwBridgeGraphicStateBrushForHBPS();		//!< デストラクタ
};

#endif /* XDWBRIDGEGRAPHICSTATEBRUSH_H_INCLUDED */
