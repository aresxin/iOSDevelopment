/**
 * @file  XdwBridgeObjectPattern.h
 * @brief Pattern Object関連クラス用ヘッダファイル
 *
 * GDIのPatternに対応するクラスの宣言やグローバルな関数を提供する．
 *
 * @author Kenichi Ishida (Fuji Xelox Co., Ltd. DPC DS&S STD) <Kenichi.Ishida@fujixerox.co.jp>
 * @date 2002-09-13
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Kenichi Ishida<br>
 * Created:	2002-09-13	Kenichi Ishida<br>
 */
#ifndef XDWBRIDGEOBJECTPATTERN_H_INCLUDED
#define XDWBRIDGEOBJECTPATTERN_H_INCLUDED

#include "XdwBridgeObject.h"
#include "XdwRaster.h"
#include "XdwDataObjectBinary.h"

/*!Pattern Objectクラス */
class XdwBridgeObjectPattern : public XdwBridgeObject {
public:
    XdwPatternAttribute	PatternAttrF;	/*!< Pattern属性	*/
    XdwRasterImageAttribute imageF;
    XdwDataObject::Binary *imagedataF;
	XdwPatternAttribute pat_att;
    long offsetF;
    long sizeF;

    XdwBridgeObjectPattern();
    XdwBridgeObjectPattern( unsigned long ID);
    XdwBridgeObjectPattern( unsigned long ID,  const XdwPatternAttribute &pat_att );
    ~XdwBridgeObjectPattern();
};

#endif /* XDWBRIDGEOBJECTPATTERN_H_INCLUDED */
