/**
 * @file  XdwGraphicFormatWMFMetaPolylineRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::PolylineRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaPolylineRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_POLYLINE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_POLYLINE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaPolyRecord.h"

/**
 * @brief META_POLYLINEレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::PolylineRecord : public XdwGraphicFormat::WMF::Meta::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PolylineRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PolylineRecord();
    
    /**
     * @brief META_POLYLINEレコードをパースする
     *
     * 座標配列を読み込み、描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
