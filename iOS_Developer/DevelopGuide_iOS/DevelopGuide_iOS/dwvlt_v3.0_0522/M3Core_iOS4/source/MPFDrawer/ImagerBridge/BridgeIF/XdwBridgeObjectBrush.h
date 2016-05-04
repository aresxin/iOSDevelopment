/**
 * @file  XdwBridgeObjectBrush.h
 * @brief Brush Object関連クラス用ヘッダファイル
 *
 * GDIのBrush Objectに対応するクラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-04	Toshio Yamazaki<br>
 * Modified:	2002-09-25	Kenichi Ishida	ブラシのパターンを保存する PatternFを追加<br>
 */
#ifndef XDWBRIDGEOBJECTBRUSH_H_INCLUDED
#define XDWBRIDGEOBJECTBRUSH_H_INCLUDED

#include "XdwBridgeObject.h"
#include "XdwRaster.h"
#include "XdwBridgeObjectPattern.h"

/*!Brush Objectクラス

  GDI Brush Objectをシミュレートする．
 */
class XdwBridgeObjectBrush : public XdwBridgeObject {
public:
    XdwPatternAttribute	PatternAttrF;	/*!< Pattern属性	*/
    XdwBridgeObjectPattern	*PatternF;	/*!< Pattern属性	*/

    XdwBridgeObjectBrush();
    XdwBridgeObjectBrush( unsigned long ID);

// CEでは例外が正しく動作せず, コンストラクタで例外を返せないため,
// メモリ確保を別な関数で行い, エラーを返すように変更する.
#if 0
    XdwBridgeObjectBrush( unsigned long ID,  const XdwPatternAttribute &pat_att );
#endif	// 0

	bool setPattern(const XdwPatternAttribute&);

    ~XdwBridgeObjectBrush();
};

#endif /* XDWBRIDGEOBJECTBRUSH_H_INCLUDED */
