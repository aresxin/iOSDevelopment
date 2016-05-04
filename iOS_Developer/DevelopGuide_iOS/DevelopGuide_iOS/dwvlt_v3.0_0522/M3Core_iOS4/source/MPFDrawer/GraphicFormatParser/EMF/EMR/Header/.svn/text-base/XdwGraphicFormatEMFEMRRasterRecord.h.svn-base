/**
 * @file  XdwGraphicFormatEMFEMRRasterRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::RasterRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRRasterRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * @date 2004-12-07 分割描画時のリーク対応 Yasuhiro.Ito@fujixerox.co.jp
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_RASTER_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_RASTER_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"
#include "XdwDataObject.h"
#include "XdwGraphicFormatGDI.h"
#include "XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwRaster.h"

/**
 * @brief EMF中のラスター描画に関するレコードを規定する抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::RasterRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RasterRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~RasterRecord();
    
    /**
     * @brief EMF中のラスター描画に関するレコードをパースする
     *
     * EMF中のラスター描画に関するレコードを読み込んで、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    virtual XdwErrorCode ParseLeg(long leg_count = -1);
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
    /*! マスク属性 */
    XdwRasterImageAttribute fMaskAttribute;
    /*! イメージデータ */
    XdwDataObject::Common* fImageBinary;
    /*! マスクデータ */
    XdwDataObject::Common* fMaskBinary;

    /********************************************/
    /* 関連 */
    
    /*! 大きなバイナリデータを作成するためのクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    
    /********************************************/
    /* 属性 */

    /*! イメージデータ削除のフラグ */
    bool fImageFlag;
    /*! マスクデータ削除のフラグ */
    bool fMaskFlag;
    /*! イメージデータのByte数 */
    long fImageBytes;   
	/*! 分割描画EndDrawImageを呼ぶかどうかのフラグ*/
	bool fEndDrawCallFlg;
    /*! マスクデータのByte数 */
    long fMaskBytes;
    /*! イメージデータへのオフセット */
    long fImageOffset;
    /*! マスクデータへのオフセット */
    long fMaskOffset;
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
     * @brief レコードの属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read() = 0;

    /**
     * @brief レコード内のバイナリデータをセットする
     *
     * BITMAPINFO構造体やラスターデータをセットする
     *
     * @param start_position レコードの開始位置
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(long start_position) = 0;
    
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
