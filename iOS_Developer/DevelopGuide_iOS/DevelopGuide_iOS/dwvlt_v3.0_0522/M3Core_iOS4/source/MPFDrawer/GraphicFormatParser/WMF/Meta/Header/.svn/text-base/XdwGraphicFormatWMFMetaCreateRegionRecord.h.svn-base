/**
 * @file  XdwGraphicFormatWMFMetaCreateRegionRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::CreateRegionRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaCreateRegionRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_CREATE_REGION_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_CREATE_REGION_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"
#include "XdwGraphicFormatWMFMetaObject.h"

/* 集約するクラスのIncludeファイル */
#include "XdwShape.h"

/**
 * @brief META_CREATEREGIONを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::CreateRegionRecord : public XdwGraphicFormat::WMF::Meta::Record, public XdwGraphicFormat::WMF::Meta::Object
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    CreateRegionRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~CreateRegionRecord();

    /**
     * @brief META_CREATEREGIONレコードをパースする
     *
     * Regionを読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

    /**
     * @brief クリッピング領域を選択する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Select();
    
    /**
     * @brief 何もしない
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Delete();
    
protected:

    /********************************************/
    /* 列挙型 */
    
    enum{
        /*! スキャンラインデータ中のx値の矩形であることの定数 */
        REGION_IS_RECTANGLE = 2
    };
    
    /********************************************/
    /* 集約 */
    
    /*! 矩形の配列 */
    XdwRectangleVector fRectangleVector;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * WMFデータのオブジェクトのIDを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
};

#endif
