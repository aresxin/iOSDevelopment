/**
 * @file  XdwGraphicFormatThumbnailParser.h
 * @brief XdwGraphicFormat::ThumbnailParserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatThumbnailParser.h,v 1.4 2009/12/22 08:11:36 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_THUMBNAIL_PARSER_H_
#define _XDW_GRAPHIC_FORMAT_THUMBNAIL_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormat.h"
#include "XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatParsingStrategy.h"

/**
 * @brief グラフィックフォーマット中のサムネイルをパースしてXdwBridgeDrawIFインターフェースに渡すクラス
 */
class XdwGraphicFormat::ThumbnailParser : public XdwGraphicFormat::ParsingStrategy
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ThumbnailParser();

    /**
     * @brief デストラクタ
     */
    virtual ~ThumbnailParser();

    /**
     * @brief パースするグラフィックデータをセットする
     *
     * @param セットされたグラフィックデータのヘッダ情報はパースする場合も存在する
     *
     * @param content DocuWorksファイル中のグラフィックフォーマットに関する情報を取得するためのインターフェースのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetContent(XdwDocuWorks::ContentManager* content);
    
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
