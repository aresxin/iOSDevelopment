/**
 * @file  XdwGraphicFormatEMFEMRRasterObjectRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::RasterObjectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRRasterObjectRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_RASTER_OBJECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_RASTER_OBJECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"
#include "XdwDataObject.h"
#include "XdwGraphicFormatGDI.h"
#include "XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwRaster.h"

/**
 * @brief EMF中のラスターパターンを管理する描画オブジェクトに関するレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::RasterObjectRecord : public XdwGraphicFormat::EMF::EMR::ObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RasterObjectRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~RasterObjectRecord();
    
protected:

    /********************************************/
    /* 列挙型 */
    
    enum{
        /*! メモリ使用量の閾値 */
        MEMORY_THRESHOLD_DIVISOR = 4
    };
    
    /********************************************/
    /* 集約 */
    
    /*! イメージ属性 */
    XdwRasterImageAttribute fImageAttribute;
    /*! イメージデータ */
    XdwDataObject::Common* fImageBinary;

    /********************************************/
    /* 関連 */
    
    /*! 大きなバイナリデータを作成するためのクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    
    /********************************************/
    /* 属性 */

    /*! イメージデータ削除のフラグ */
    bool fImageFlag;
    /*! イメージデータへのオフセット */
    long fImageOffset;
    /*! イメージデータのByte数 */
    long fImageBytes;
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
     * @brief ラスター属性を初期化する
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual void InitializeAttribute(XdwRasterImageAttribute* attribute);
    
    /**
     * @brief 集約を削除する
     */
    virtual void Delete();
    
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
    
    /**
     * @brief ラスターデータをセットする
     *
     * @param save 現在の状態を保存させる必要の有無
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetRaster(bool save);
};

#endif
