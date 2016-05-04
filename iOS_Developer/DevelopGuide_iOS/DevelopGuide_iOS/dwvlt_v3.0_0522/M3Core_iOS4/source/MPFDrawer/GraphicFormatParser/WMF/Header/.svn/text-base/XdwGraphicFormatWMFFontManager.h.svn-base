/**
 * @file  XdwGraphicFormatWMFFontManager.h
 * @brief XdwGraphicFormat::WMF::FontManagerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFFontManager.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_FONT_MANAGER_H_
#define _XDW_GRAPHIC_FORMAT_WMF_FONT_MANAGER_H_

/* 親クラスのためのIncludeファイル */
#include "XdwGraphicFormatWMFObjectManager.h"

/**
 * @brief DocuWorksファイルのフォントオブジェクトを管理するクラス
 */
class XdwGraphicFormat::WMF::FontManager : public XdwGraphicFormat::WMF::ObjectManager
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
     * @param emr MetaRecordを読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::WMF::Meta::Record* emr);

protected:
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 描画オブジェクトのセット
     *
     * @param handle 描画オブジェクトのハンドル
     * @param type 描画オブジェクトの型
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetObject(unsigned long handle, short type);

};

#endif
