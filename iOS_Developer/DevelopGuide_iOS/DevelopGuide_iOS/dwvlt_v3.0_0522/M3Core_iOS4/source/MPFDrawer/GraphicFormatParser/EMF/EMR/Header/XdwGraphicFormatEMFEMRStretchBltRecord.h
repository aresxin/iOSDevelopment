/**
 * @file  XdwGraphicFormatEMFEMRStretchBltRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::StretchBltRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRStretchBltRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_Stretch_BLT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_Stretch_BLT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRasterRecord.h"

/**
 * @brief EMR_StretchBLTを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::StretchBltRecord : public XdwGraphicFormat::EMF::EMR::RasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    StretchBltRecord();
    
    /**
     * @brief コンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    StretchBltRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~StretchBltRecord();
    
protected:

    /********************************************/
    /* 属性 */

    /*! BITMAPINFO構造体へのオフセット */
    long fBitmapInfoOffset;
    /*! BITMAPINFO構造体のサイズ */
    long fBitmapInfoBytes;
    /*! イメージデータへのオフセット */
    long fBitsOffset;
    
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
     * BITMAPINFO構造体やラスターデータをセットする
     *
     * @param start_position レコードの開始位置
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(long start_position);
    
    /**
     * @brief BITMAPINFO構造体を読み込み
     *
     * @param attribute セットされる属性管理のインスタンス
     * @param size BITMAPINFO構造体のサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadAttribute(XdwRasterImageAttribute* attribute, long size);
    
};

#endif
