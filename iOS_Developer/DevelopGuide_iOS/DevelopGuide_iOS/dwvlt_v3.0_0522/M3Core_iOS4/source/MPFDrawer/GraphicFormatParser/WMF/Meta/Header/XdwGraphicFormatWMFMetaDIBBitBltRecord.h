/**
 * @file  XdwGraphicFormatWMFMetaDIBBitBltRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::DIBBitBltRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.01
 * $Id: XdwGraphicFormatWMFMetaDIBBitBltRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * @date 2002-12-17 パースを親クラスでなくこのクラスで実施し，
 *  SrcWidth,SrcHeightに値をセット Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_DIB_BIT_BLT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_DIB_BIT_BLT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRasterRecord.h"

/**
 * @brief META_DIBBITBLTを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::DIBBitBltRecord : public XdwGraphicFormat::WMF::Meta::RasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    DIBBitBltRecord();

    /**
     * @brief コンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    DIBBitBltRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~DIBBitBltRecord();
    
    /**
     * @brief WMF中のラスター描画に関するレコードをパースする
     *
     * WMF中のラスター描画に関するレコードを読み込んで、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();   
protected:
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief レコードの属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();

    /**
     * @brief ラスター属性の読み込み
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadAttribute(XdwRasterImageAttribute* attribute);
    
    /**
     * @brief レコード内のバイナリデータをセットする
     *
     * BITMAPINFO構造体やラスターデータをセットする
     *
     * @param start_position レコードの開始位置
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(long start_position);
};

#endif
