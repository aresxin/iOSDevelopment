/**
 * @file  XdwGraphicFormatEMFEMRMaskBltRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::MaskBltRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRMaskBltRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_MASK_BLT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_MASK_BLT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRBitBltRecord.h"

/**
 * @brief EMR_MASKBLTを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::MaskBltRecord : public XdwGraphicFormat::EMF::EMR::BitBltRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    MaskBltRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~MaskBltRecord();
    
protected:
    
    /********************************************/
    /* 属性 */

    /*! マスクデータのBITMAPINFO構造体へのオフセット */
    long fMaskInfoOffset;
    /*! マスクデータのBITMAPINFO構造体のサイズ */
    long fMaskInfoBytes;
    /*! マスクデータへのオフセット */
    long fMaskBitsOffset;
    
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
     * @brief マスクデータをセットする
     *
     * @param save 現在の状態を保存させる必要の有無
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetMask(bool save);
    
};

#endif
