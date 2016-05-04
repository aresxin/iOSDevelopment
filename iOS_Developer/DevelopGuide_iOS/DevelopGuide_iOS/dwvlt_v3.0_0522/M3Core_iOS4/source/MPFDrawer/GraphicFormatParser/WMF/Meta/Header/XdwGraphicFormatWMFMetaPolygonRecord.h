/**
 * @file  XdwGraphicFormatWMFMetaPolygonRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::PolygonRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaPolygonRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_POLYGON_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_POLYGON_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaPolyRecord.h"

/**
 * @brief META_POLYGONレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::PolygonRecord : public XdwGraphicFormat::WMF::Meta::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PolygonRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PolygonRecord();
    
    /**
     * @brief META_POLYGONレコードをパースする
     *
     * 座標配列を読み込み、描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
