/*!
  @file  XdwBridgeGraphicStatePen.h
  @brief XdwBridgeGraphicStatePen クラスヘッダファイル

  XdwBridgeGraphicStatePenクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-24
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEGRAPHICSTATEPEN_H_INCLUDED
#define XDWBRIDGEGRAPHICSTATEPEN_H_INCLUDED

#include "XdwError.h"

/*! Bridge内部Graphic State内部Pen属性管理クラス

  Graphic State内のPen属性の管理を行う抽象クラス．<br>
  XdwBridgeGraphicState classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのPen属性の管理を行う．
 */
class XdwBridgeGraphicStatePen {
public:
    XdwBridgeGraphicStatePen();			//!< コンストラクタ
    virtual ~XdwBridgeGraphicStatePen();	//!< デストラクタ

    virtual XdwErrorCode Initialize( void );	//!< 初期化メソッド
};

//class imgImager;	//!< imgImagerクラスの先行宣言

class XdwBridgeGraphicStatePenForHBPS : public XdwBridgeGraphicStatePen {
private:
	void *imagerF;
public:
    XdwBridgeGraphicStatePenForHBPS( void * );	//!< コンストラクタ
    ~XdwBridgeGraphicStatePenForHBPS();		//!< デストラクタ
};

#endif /* XDWBRIDGEGRAPHICSTATEPEN_H_INCLUDED */
