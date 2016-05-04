/*!
  @file  XdwLogInterface.h
  @brief XdwLogInterfaceクラスの定義を記述したIncludeファイル

  @author Tomohiro Yamada (Fuji Xelox Co., Ltd. DPC DS&S STD) <Tomohiro.Yamada@fujixerox.co.jp>
  @date 2002-04-24
  @version 0.1
 
  Copyright (C) Fuji Xerox Co., Ltd. DPC CS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
 */
#ifndef _XDW_LOG_INTERFACE_H_
#define _XDW_LOG_INTERFACE_H_

/* 列挙型の定義のためのIncludeファイル */
#include "System/SystemIF/XdwError.h"

/**
 * @interface XdwLogInterface XdwLogInterface.h
 * @brief DocuWorksDecoder用にLogファイルを記述するためのインターフェース
 */
class XdwLogInterface
{
public:
    /********************************************/
    /* メソッド */

    /**
     * @brief Logを記述する
     *
     * @param log 記述するlogの文字列<br>
     *            ASCIIコード以外は認めない
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode WriteLog(const char* log) = 0;
};

#endif
