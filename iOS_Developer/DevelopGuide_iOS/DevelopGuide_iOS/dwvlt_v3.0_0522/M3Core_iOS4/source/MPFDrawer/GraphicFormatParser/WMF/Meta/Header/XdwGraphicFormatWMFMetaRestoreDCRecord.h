/**
 * @file  XdwGraphicFormatWMFMetaRestoreDCRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::RestoreDCRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaRestoreDCRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_RESTORE_DC_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_RESTORE_DC_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObjectRecord.h"

/**
 * @brief META_RESTOREDCを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::RestoreDCRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RestoreDCRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RestoreDCRecord();
    
    /**
     * @brief META_RESTOREDCレコードをパースする
     *
     * 描画属性を復元する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

};

#endif
