/**
 * @file  XdwGraphicFormatParsingStrategy.h
 * @brief XdwGraphicFormat::ParsingStrategyクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatParsingStrategy.h,v 1.4 2009/12/22 08:11:36 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_PARSING_STRATEGY_H_
#define _XDW_GRAPHIC_FORMAT_PARSING_STRATEGY_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormat.h"
#include "XdwDocuWorks.h"

/* 依存するクラスのIncludeファイル */
#include "XdwDocuWorksContentManager.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief クライアントがグラフィックフォーマットのパース方法を選択するための抽象クラス
 *
 * PD、配列指定型PDのDataタグに格納されているグラフィックデータをパースする
 */
class XdwGraphicFormat::ParsingStrategy
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ParsingStrategy();

    /**
     * @brief デストラクタ
     */
    virtual ~ParsingStrategy();

    /**
     * @brief インスタンスを初期化する
     *
     * @param bridge XdwBridgeDrawIFインターフェースのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwBridgeDrawIF* bridge = XdwNull);

    /**
     * @brief Bridgeをセットする
     *
     * @param bridge XdwBridgeDrawIFインターフェースのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SetBridge(XdwBridgeDrawIF* bridge);
    
    /**
     * @brief グラフィックフォーマットのパース方法を指定する
     *
     * @param mode XdwGraphicFormat::ParseMode参照
     * @param image_leg_count イメージ分割描画の分割ライン数
     * @param meta_leg_count MetaRecordを読み込む単位数
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetMode(XdwGraphicFormat::ParseMode mode, long image_leg_count,long meta_leg_count = 1);
    
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
    
    /**
     * @brief セットされたグラフィックデータの情報を取得するためのインターフェースのインスタンスを取得する
     *
     * @return XdwGraphicFormat::Info参照
     */
    virtual XdwGraphicFormat::Info* GetInfo();
    
    /**
     * @brief セットされたグラフィックデータをパースする
     *
     * グラフィックデータをパースしながら、XdwBridgeDrawIFのインスタンスに描画データを渡していく
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse();

    /**
     * @brief セットされたグラフィックデータのパースを終了する
     *
     * XdwGraphicFormat::ParsingStrategy::Parseメソッドを終了する場合(正常終了/異常終了)に、必ず呼ばなければならない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Terminate();
    
protected:

    /********************************************/
    /* 集約 */
    
    /*! グラフィックデータを読み込むクラス */
    XdwGraphicFormat::Parser* fParser;
    
    /********************************************/
    /* 関連 */
    
    /*! 描画方法を規定するインターフェース */
    XdwBridgeDrawIF* fBridge;
    
    /********************************************/
    /* 属性 */
    
    /*! グラフィックデータのパース方法 */
    XdwGraphicFormat::ParseMode fParseMode;
    /*! 分割してパースする場合のイメージライン数 */
    long fImageLegCount;
    /*! 分割してパースする場合のメタレコード単位数*/
	long fMetaLegCount;
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 集約しているクラスのインスタンスを削除する
     */
    virtual void Delete();

    /**
     * @brief グラフィックフォーマットを指定する
     *
     * @param format XdwDocuWorks::ContentManager::PDInfo::DataFormat参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetFormat(XdwDocuWorks::ContentManager::PDInfo::DataFormat format) = 0;
    
};

#endif
