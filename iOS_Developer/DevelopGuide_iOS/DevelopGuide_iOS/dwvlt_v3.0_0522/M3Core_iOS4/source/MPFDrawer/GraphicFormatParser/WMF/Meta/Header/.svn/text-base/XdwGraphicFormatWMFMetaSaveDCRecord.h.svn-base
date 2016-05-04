/**
 * @file  XdwGraphicFormatWMFMetaSaveDCRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SaveDCRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSaveDCRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SAVE_DC_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SAVE_DC_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObjectRecord.h"

/**
 * @brief META_SAVEDCを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SaveDCRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SaveDCRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SaveDCRecord();
    
    /**
     * @brief META_SAVEDCレコードをパースする
     *
     * 描画属性を保存する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

};

#endif
