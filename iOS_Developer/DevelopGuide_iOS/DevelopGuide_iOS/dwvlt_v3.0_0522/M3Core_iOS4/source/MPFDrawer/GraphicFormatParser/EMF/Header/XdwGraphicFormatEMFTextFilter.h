/**
 * @file  XdwGraphicFormatEMFTextFilter.h
 * @brief XdwGraphicFormat::EMF::TextFilterクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFTextFilter.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_TEXT_FILTER_H_
#define _XDW_GRAPHIC_FORMAT_EMF_TEXT_FILTER_H_

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFParser.h"

/* 集約する親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFFontManager.h"

/**
 * @brief DocuWorksファイルのEMF中のテキストをフィルタリングするクラス
 */
class XdwGraphicFormat::EMF::TextFilter : public XdwGraphicFormat::EMF::Parser
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
    XdwGraphicFormat::EMF::FontManager fFontManager;
    
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
     * @brief EMF中の一つのレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRecord();
    
};

#endif
