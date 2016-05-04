/**
 * @file  XdwGraphicFormatWMFMetaDIBStretchBltRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::DIBStretchBltRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaDIBStretchBltRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_DIB_STRETCH_BLT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_DIB_STRETCH_BLT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaDIBBitBltRecord.h"

/**
 * @brief META_DIBSTRETCHBLTを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::DIBStretchBltRecord : public XdwGraphicFormat::WMF::Meta::DIBBitBltRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    DIBStretchBltRecord();

    /**
     * @brief コンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    DIBStretchBltRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~DIBStretchBltRecord();
    
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
