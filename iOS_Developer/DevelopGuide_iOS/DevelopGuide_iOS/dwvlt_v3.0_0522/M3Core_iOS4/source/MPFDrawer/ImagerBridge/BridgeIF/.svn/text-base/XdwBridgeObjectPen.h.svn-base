/**
 * @file  XdwBridgeObjectPen.h
 * @brief Pen Object関連クラス用ヘッダファイル
 *
 * GDIのPen Objectに対応するクラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEOBJECTPEN_H_INCLUDED
#define XDWBRIDGEOBJECTPEN_H_INCLUDED

#include "XdwBridgeObject.h"
#include "XdwPen.h"
#include "XdwRaster.h"
#include "XdwBridgeObjectPattern.h"

/*!Pen Objectクラス

  GDI Pen Objectをシミュレートする．
 */
class XdwBridgeObjectPen : public XdwBridgeObject {
public:
    XdwPenAttribute	PenAttrF;	/*!< Pen属性		*/
    XdwPatternAttribute	PatternAttrF;	/*!< Pattern属性	*/
    XdwBridgeObjectPattern	*PatternF;	/*!< Pattern属性	*/

    XdwBridgeObjectPen();
    XdwBridgeObjectPen( unsigned long ID );
    XdwBridgeObjectPen( unsigned long ID,
			const XdwPenAttribute &pen_att,
			const XdwPatternAttribute &pat_att );
    ~XdwBridgeObjectPen();
};

#endif /* XDWBRIDGEOBJECTPEN_H_INCLUDED */
