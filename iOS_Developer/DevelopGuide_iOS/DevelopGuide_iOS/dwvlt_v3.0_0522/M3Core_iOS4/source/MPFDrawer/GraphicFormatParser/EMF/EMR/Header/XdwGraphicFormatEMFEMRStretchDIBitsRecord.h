/**
 * @file  XdwGraphicFormatEMFEMRStretchDIBitsRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::StretchDIBitsRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRStretchDIBitsRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_STRETCH_DIBITS_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_STRETCH_DIBITS_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRBitBltRecord.h"

/**
 * @brief EMR_STRETCHDIBITSを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::StretchDIBitsRecord : public XdwGraphicFormat::EMF::EMR::BitBltRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    StretchDIBitsRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~StretchDIBitsRecord();
    
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
