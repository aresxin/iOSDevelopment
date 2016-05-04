// Copyright (C) 2003 by Fuji Xerox Co.,Ltd All rights reserved.

/**
 *  @file    QTFontManagerGlobal.h
 *  @brief   HBPS (C言語) からQTFontManagerクラス関連グローバル関数を使うために,
 *           Cリンケージを指定する.
 *
 *  @author  DPSC サービス開発部 第3サービス開発室 TD-G 山本紀夫
 *  @version 1.0
 *  @date    2003年4月2日
 */

////////////////////////////////////////////////////////////////////////////////

#ifndef QT_FONT_MANAGER_GLOBAL_H_INCLUDED
#define QT_FONT_MANAGER_GLOBAL_H_INCLUDED

#if !defined(CXX_DECOMPOSER)
extern "C" {
#include "FM_ProcessorViewLinux.h"
#include "QTFontManagerHeaderForHBPS.h"
} // extern "C"
#else
#include "FM_ProcessorViewLinux.h"
#include "QTFontManagerHeaderForHBPS.h"
#endif

#endif // QT_FONT_MANAGER_GLOBAL_H_INCLUDED
