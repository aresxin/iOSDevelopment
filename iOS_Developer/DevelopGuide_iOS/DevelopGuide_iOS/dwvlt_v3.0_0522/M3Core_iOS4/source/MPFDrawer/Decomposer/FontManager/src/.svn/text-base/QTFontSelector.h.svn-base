// Copyright (C) 2003 by Fuji Xerox Co.,Ltd All rights reserved.

/**
 *  @file    QTFontSelector.h
 *  @brief   要求された属性に基づきQtにおけるフォントを撰択するクラス定義.
 *
 *  @author  DPSC サービス開発部 第3サービス開発室 TD-G 山本紀夫
 *  @version 1.0
 *  @date    2003年4月7日
 */

#ifndef QT_FONT_SELECTOR_H_INCLUDED
#define QT_FONT_SELECTOR_H_INCLUDED

#include <qfont.h>

#if !defined(CXX_DECOMPOSER)
extern "C" {
#include "FM_ProcessorViewLinux.h"
}
#else
#include "FM_ProcessorViewLinux.h"
#endif

////////////////////////////////////////////////////////////////////////////////
/**
 * Qt用フォント撰択クラス.
 */
class QTFontSelector {
public:
    QTFontSelector() {};
    virtual ~QTFontSelector() {};

    virtual QFont* select(FM_ProcessorViewLinux*, FM_LogFont*, unsigned short*, int) = 0;

private:
};

#endif // QT_FONT_SELECTOR_H_INCLUDED
