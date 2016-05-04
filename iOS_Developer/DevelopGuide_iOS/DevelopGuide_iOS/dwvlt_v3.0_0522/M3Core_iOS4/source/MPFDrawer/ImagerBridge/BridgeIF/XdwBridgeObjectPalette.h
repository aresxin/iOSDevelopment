/**
 * @file  XdwBridgeObjectPalette.h
 * @brief Palette Object関連クラス用ヘッダファイル
 *
 * GDIのPalette Objectに対応するクラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEOBJECTPALLET_H_INCLUDED
#define XDWBRIDGEOBJECTPALLET_H_INCLUDED

#include "XdwBridgeObject.h"
#include "XdwColor.h"

/*!Palette Objectクラス

  GDI Palette Objectをシミュレートする．
 */
class XdwBridgeObjectPalette : public XdwBridgeObject {
public:
    XdwColorPalette	PaletteAttrF;	/*!< Palette属性		*/

    XdwBridgeObjectPalette();
    XdwBridgeObjectPalette( unsigned long ID );
    XdwBridgeObjectPalette( unsigned long ID, const XdwColorPalette &pal_att );
    ~XdwBridgeObjectPalette();
};

#endif /* XDWBRIDGEOBJECTPALLET_H_INCLUDED */
