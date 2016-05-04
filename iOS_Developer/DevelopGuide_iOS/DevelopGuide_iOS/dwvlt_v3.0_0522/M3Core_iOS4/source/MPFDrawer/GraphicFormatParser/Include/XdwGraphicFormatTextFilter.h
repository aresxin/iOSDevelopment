/**
 * @file  XdwGraphicFormatTextFilter.h
 * @brief XdwGraphicFormat::TextFilterクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatTextFilter.h,v 1.4 2009/12/22 08:11:36 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_TEXT_FILTER_H_
#define _XDW_GRAPHIC_FORMAT_TEXT_FILTER_H_

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatParsingStrategy.h"

/**
 * @brief グラフィックフォーマット中のテキスト情報をXdwBridgeDrawIFインターフェースに渡すクラス
 */
class XdwGraphicFormat::TextFilter : public XdwGraphicFormat::ParsingStrategy
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    TextFilter();

    /**
     * @brief デストラクタ
     */
    virtual ~TextFilter();
    
protected:
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief グラフィックフォーマットを指定する
     *
     * @param format XdwDocuWorks::ContentManager::PDInfo::DataFormat参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetFormat(XdwDocuWorks::ContentManager::PDInfo::DataFormat format);
    
};

#endif
