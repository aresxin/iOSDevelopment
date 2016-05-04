/**
 * @file  XdwGraphicFormatRasterDIB.h
 * @brief XdwGraphicFormat::Raster::DIBクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatRasterDIB.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_RASTER_DIB_H_
#define _XDW_GRAPHIC_FORMAT_RASTER_DIB_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatRaster.h"
#include "XdwGraphicFormatGDI.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatRasterParser.h"

/* 関連するクラスのIncludeファイル */
#include "XdwDocuWorksContentManager.h"

/**
 * @brief DocuWorksファイルのDIBデータを読み込むクラス
 *
 */
class XdwGraphicFormat::Raster::DIB : public XdwGraphicFormat::Raster::Parser
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    DIB();

    /**
     * @brief デストラクタ
     */
    virtual ~DIB();

    /**
     * @brief パースするグラフィックデータをセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set();

protected:

    /********************************************/
    /* 列挙型 */
    
    enum{
        /*! BITMAPHEADER構造体のサイズ */
        BITMAP_HEADER_BYTES = 14
    };
    
    /********************************************/
    /* メソッド */

    /**
     * @brief PD情報を取得する
     *
     * @return XdwDocuWorks::ContentManager::PDInfoインターフェース参照
     */
    virtual XdwDocuWorks::ContentManager::PDInfo* GetPD();
    
    /**
     * @brief 古いバージョンのOKD圧縮されたDIBをセットする
     *
     * @param info BITMAPINFO構造体を管理するクラス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetOldOKD(XdwGraphicFormat::GDI::BitmapInfo* info);

    /**
     * @brief OKD圧縮されたDIBをセットする
     *
     * @param info BITMAPINFO構造体を管理するクラス
     * @param size BITMAPINFO構造体のサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetOKD(XdwGraphicFormat::GDI::BitmapInfo* info, long size);

    /**
     * @brief Adaptive圧縮されたDIBをセットする
     *
     * @param info BITMAPINFO構造体を管理するクラス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetAdaptive(XdwGraphicFormat::GDI::BitmapInfo* info);
    
};

#endif
