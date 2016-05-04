/**
 * @file  XdwGraphicFormatEMFEnhEMRStretchDIBitsRefRecord.h
 * @brief XdwGraphicFormat::EMF::EnhEMR::StretchDIBitsRefRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEnhEMRStretchDIBitsRefRecord.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_ENH_EMR_STRETCH_DIB_REF_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_ENH_EMR_STRETCH_DIB_REF_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEnhEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRasterRecord.h"

/**
 * @brief EMF中の参照されるラスターデータを描画するクラス
 *
 */
class XdwGraphicFormat::EMF::EnhEMR::StretchDIBitsRefRecord : public XdwGraphicFormat::EMF::EMR::RasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param raster 参照されるラスターデータ
     * @param generator 大きなバイナリデータを作成するクラス
     */
    StretchDIBitsRefRecord(XdwGraphicFormat::EMF::EnhEMR::SetRasterRecord* raster, XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~StretchDIBitsRefRecord();
    
protected:

    /********************************************/
    /* 関連 */

    /*! 参照されるラスターデータ */
    XdwGraphicFormat::EMF::EnhEMR::SetRasterRecord* fRaster;
    
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
