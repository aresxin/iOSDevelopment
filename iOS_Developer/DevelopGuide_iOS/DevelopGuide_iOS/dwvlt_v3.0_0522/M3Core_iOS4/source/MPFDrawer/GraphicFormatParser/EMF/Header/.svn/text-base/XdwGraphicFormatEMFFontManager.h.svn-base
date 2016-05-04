/**
 * @file  XdwGraphicFormatEMFFontManager.h
 * @brief XdwGraphicFormat::EMF::FontManagerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFFontManager.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_FONT_MANAGER_H_
#define _XDW_GRAPHIC_FORMAT_EMF_FONT_MANAGER_H_

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFObjectManager.h"

/**
 * @brief DocuWorksファイルのフォントオブジェクトを管理するクラス
 *
 * フォント以外の描画オブジェクトは読み飛ばす
 */
class XdwGraphicFormat::EMF::FontManager : public XdwGraphicFormat::EMF::ObjectManager
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    FontManager();

    /**
     * @brief デストラクタ
     */
    virtual ~FontManager();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param bridge Imagerへアクセスするためのインターフェース
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge);
    
    /**
     * @brief 描画オブジェクトのレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::EMF::EMR::Record* emr);

protected:
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief EMR_SELECTOBJECTレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectObject();

    /**
     * @brief EMR_DELETEOBJECTレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して削除する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseDeleteObject();
    
};

#endif
