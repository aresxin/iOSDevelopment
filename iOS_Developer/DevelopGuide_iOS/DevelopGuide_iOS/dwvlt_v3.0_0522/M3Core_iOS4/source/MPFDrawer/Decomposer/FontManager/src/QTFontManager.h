// Copyright (C) 2003 by Fuji Xerox Co.,Ltd All rights reserved.

/**
 *  @file    QTFontManager.h
 *  @brief   Qt用フォントマネージャ定義.
 *
 *  @author  DPSC サービス開発部 第3サービス開発室 TD-G 山本紀夫
 *  @version 1.0
 *  @date    2003年4月2日
 */

#ifndef QT_FONT_MANAGER_H_INCLUDED
#define QT_FONT_MANAGER_H_INCLUDED

#include <qfont.h>
#include <qfontmetrics.h>

#if !defined(CXX_DECOMPOSER)
extern "C" {
#include "FM_ProcessorViewLinux.h"
}
#else
#include "FM_ProcessorViewLinux.h"
#endif

#include "QTFontSelector.h"

////////////////////////////////////////////////////////////////////////////////
/**
 * Qt用フォントマネージャクラス.
 */
class QTFontManager {
public:
    QTFontManager();
    ~QTFontManager();

    bool initialize();
    void terminate();

    bool setLogFont(FM_ProcessorViewLinux*, FM_LogFont*, unsigned short*, int);
    bool getFontMetrics(long*, long*, long*, long*);
    bool getTextExtentPoint32W(unsigned short*, int, long*, long*);

    bool drawFontImage(unsigned short*, int, int*, FM_StringArea*, FM_ProcessorViewLinux*, FM_Point*, FM_Rect*);

private:
    QTFontSelector* fontSelector_;
    QFont* curFont_;
    QFontMetrics* fontMetrics_;

    unsigned char mask_[8];
};

#endif // QT_FONT_MANAGER_H_INCLUDED
