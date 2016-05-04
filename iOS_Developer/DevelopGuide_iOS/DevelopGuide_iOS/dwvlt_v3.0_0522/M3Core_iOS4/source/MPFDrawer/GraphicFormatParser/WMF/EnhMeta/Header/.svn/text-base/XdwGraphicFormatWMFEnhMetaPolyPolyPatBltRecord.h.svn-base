/**
 * @file  XdwGraphicFormatWMFEnhMetaPolyPolyPatBltRecord.h
 * @brief XdwGraphicFormat::WMF::EnhMeta::PolyPolyPatBltRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.01
 * $Id: XdwGraphicFormatWMFEnhMetaPolyPolyPatBltRecord.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * @date 2002-12-25 分割描画対応 v1.01
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_ENH_META_POLY_POLY_PAT_BLT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_ENH_META_POLY_POLY_PAT_BLT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRasterRecord.h"

/**
 * @brief 冗長なMETA_PATBLTを1つにまとめるDocuWorks独自レコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::EnhMeta::PolyPolyPatBltRecord : public XdwGraphicFormat::WMF::Meta::RasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PolyPolyPatBltRecord();

    /**
     * @brief コンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    PolyPolyPatBltRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~PolyPolyPatBltRecord();

    /**
     * @brief WMF中の複数のPatBltに関するレコードをパースする
     *
     * WMF中のラスター描画に関するレコードを読み込んで、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    /**
     * @brief WMF中の複数のPatBltに関するレコードをパースする
     *
     * ここではダミー関数として実際はParse()を呼ぶだけ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg(long leg_count = -1);    
protected:

    /********************************************/
    /* メソッド */
    
    /**
     * @brief Imagerに描画を依頼する
     *
     * @param x x座標
     * @param y y座標
     * @param width 横幅
     * @param height 縦幅
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Draw(short x, short y, short width, short height);

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
