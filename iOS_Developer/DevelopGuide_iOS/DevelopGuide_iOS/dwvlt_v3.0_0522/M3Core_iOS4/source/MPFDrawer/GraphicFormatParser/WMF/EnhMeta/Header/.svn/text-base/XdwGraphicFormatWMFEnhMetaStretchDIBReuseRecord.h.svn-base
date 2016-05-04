/**
 * @file  XdwGraphicFormatWMFEnhMetaStretchDIBReuseRecord.h
 * @brief XdwGraphicFormat::WMF::EnhMeta::StretchDIBReuseRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFEnhMetaStretchDIBReuseRecord.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_ENH_META_STRETCH_DIB_REUSE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_ENH_META_STRETCH_DIB_REUSE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMetaStretchDIBRefRecord.h"

/**
 * @brief WMF中の参照されるラスターデータを描画するクラス
 *
 */
class XdwGraphicFormat::WMF::EnhMeta::StretchDIBReuseRecord : public XdwGraphicFormat::WMF::EnhMeta::StretchDIBRefRecord
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
    StretchDIBReuseRecord(XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord* raster, XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~StretchDIBReuseRecord();
    
protected:
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief レコードの属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
};

#endif
