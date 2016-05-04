/**
 * @file  XdwBridgeObjectFont.h
 * @brief Font Object関連クラス用ヘッダファイル
 *
 * GDIのFont Objectに対応するクラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEOBJECTFONT_H_INCLUDED
#define XDWBRIDGEOBJECTFONT_H_INCLUDED

#include "XdwBridgeObject.h"
#include "XdwFont.h"

/*!Font Objectクラス

  GDI Font Objectをシミュレートする．
 */
class XdwBridgeObjectFont : public XdwBridgeObject {
public:
    XdwFontInfo		FontInfoF;	/*!< Font属性	*/

    XdwBridgeObjectFont();
    XdwBridgeObjectFont( unsigned long ID );
    XdwBridgeObjectFont( unsigned long ID, const XdwFontInfo &FontInfo );
    ~XdwBridgeObjectFont();
};

#endif /* XDWBRIDGEOBJECTFONT_H_INCLUDED */
