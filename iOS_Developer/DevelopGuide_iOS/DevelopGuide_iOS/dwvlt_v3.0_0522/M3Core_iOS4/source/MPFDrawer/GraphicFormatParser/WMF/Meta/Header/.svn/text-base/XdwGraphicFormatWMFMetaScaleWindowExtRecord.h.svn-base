/**
 * @file  XdwGraphicFormatWMFMetaScaleWindowExtRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::ScaleWindowExtRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaScaleWindowExtRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SCALE_WINDOW_EXT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SCALE_WINDOW_EXT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaScaleRecord.h"

/**
 * @brief META_SCALEWINDOWEXTレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::ScaleWindowExtRecord : public XdwGraphicFormat::WMF::Meta::ScaleRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ScaleWindowExtRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ScaleWindowExtRecord();
    
    /**
     * @brief META_SCALEWINDOWEXTレコードをパースする
     *
     * 倍率を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
