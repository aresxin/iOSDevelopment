/**
 * @file  XdwGraphicFormatWMFMetaDIBStretchDIBRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::StretchDIBRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaStretchDIBRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_STRETCH_DIB_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_STRETCH_DIB_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaDIBBitBltRecord.h"

/**
 * @brief META_STRETCHDIBを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::StretchDIBRecord : public XdwGraphicFormat::WMF::Meta::DIBBitBltRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    StretchDIBRecord();

    /**
     * @brief コンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    StretchDIBRecord(XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief デストラクタ
     */
    virtual ~StretchDIBRecord();
    
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
