/**
 * @file  XdwGraphicFormatWMFMetaPatBltRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::PatBltRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaPatBltRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_PAT_BLT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_PAT_BLT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRasterRecord.h"

/**
 * @brief META_PATBLTを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::PatBltRecord : public XdwGraphicFormat::WMF::Meta::RasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PatBltRecord();

    /**
     * @brief コンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    PatBltRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~PatBltRecord();
    
protected:
    
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
     * @brief レコード内のバイナリデータをセットする
     *
     * PATMAPINFO構造体やラスターデータをセットする
     *
     * @param start_position レコードの開始位置
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(long start_position);
    
    
};

#endif
