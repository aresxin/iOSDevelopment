/**
 * @file  XdwGraphicFormatWMFEnhMetaStretchDIBRefRecord.h
 * @brief XdwGraphicFormat::WMF::EnhMeta::StretchDIBRefRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFEnhMetaStretchDIBRefRecord.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_ENH_META_STRETCH_DIB_REF_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_ENH_META_STRETCH_DIB_REF_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRasterRecord.h"

/**
 * @brief WMF中の参照されるラスターデータを描画するクラス
 *
 */
class XdwGraphicFormat::WMF::EnhMeta::StretchDIBRefRecord : public XdwGraphicFormat::WMF::Meta::RasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    StretchDIBRefRecord();
    
    /**
     * @brief デフォルトコンストラクタ
     *
     * @param raster 参照されるラスターデータ
     * @param generator 大きなバイナリデータを作成するクラス
     */
    StretchDIBRefRecord(XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord* raster, XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~StretchDIBRefRecord();
    
protected:

    /********************************************/
    /* 関連 */

    /*! 参照されるラスターデータ */
    XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord* fRaster;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 集約や属性の初期化
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
    /**
     * @brief レコードの属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();

    /**
     * @brief 参照されるラスターデータの属性やデータをセットする
     *
     * @param start_position レコードの開始位置
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(long start_position);
    
};

#endif
