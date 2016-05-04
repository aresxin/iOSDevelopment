/**
 * @file  XdwGraphicFormatWMFTextFilter.h
 * @brief XdwGraphicFormat::WMF::TextFilterクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFTextFilter.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_TEXT_FILTER_H_
#define _XDW_GRAPHIC_FORMAT_WMF_TEXT_FILTER_H_

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFParser.h"

/* 集約する親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFFontManager.h"

/**
 * @brief DocuWorksファイルのWMF中のテキストをフィルタリングするクラス
 */
class XdwGraphicFormat::WMF::TextFilter : public XdwGraphicFormat::WMF::Parser
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator XdwDataObject::Base::Generatorのインスタンス
     */
    TextFilter();

    /**
     * @brief デストラクタ
     */
    virtual ~TextFilter();

protected:

    /********************************************/
    /* 集約 */

    /*! フォント管理クラス */
    XdwGraphicFormat::WMF::FontManager fFontManager;
    
    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスを初期化する
     *
     * 継承クラスは本メソッドを実行するればよい
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
    /**
     * @brief WMF中の一つのレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRecord();
    
};

#endif
