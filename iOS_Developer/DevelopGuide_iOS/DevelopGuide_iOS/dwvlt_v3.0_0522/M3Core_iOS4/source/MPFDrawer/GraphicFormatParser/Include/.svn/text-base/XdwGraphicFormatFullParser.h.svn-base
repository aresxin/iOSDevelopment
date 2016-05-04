/**
 * @file  XdwGraphicFormatFullParser.h
 * @brief XdwGraphicFormat::FullParserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatFullParser.h,v 1.4 2009/12/22 08:11:36 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_FULL_PARSER_H_
#define _XDW_GRAPHIC_FORMAT_FULL_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormat.h"
#include "XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatParsingStrategy.h"

/**
 * @brief グラフィックフォーマットを完全にパースしてXdwBridgeDrawIFインターフェースに渡すクラス
 */
class XdwGraphicFormat::FullParser : public XdwGraphicFormat::ParsingStrategy
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    FullParser();

    /**
     * @brief デストラクタ
     */
    virtual ~FullParser();

    /**
     * @brief インスタンスを初期化する
     *
     * @param bridge XdwBridgeDrawIFインターフェースのインスタンス
     * @param generator XdwDataObject::Base::Generatorクラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwBridgeDrawIF* bridge = XdwNull, XdwDataObject::Base::Generator* generator = XdwNull);
    
protected:

    /********************************************/
    /* 関連 */
    
    /*! 大きなサイズのバイナリデータを作成するクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    
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
