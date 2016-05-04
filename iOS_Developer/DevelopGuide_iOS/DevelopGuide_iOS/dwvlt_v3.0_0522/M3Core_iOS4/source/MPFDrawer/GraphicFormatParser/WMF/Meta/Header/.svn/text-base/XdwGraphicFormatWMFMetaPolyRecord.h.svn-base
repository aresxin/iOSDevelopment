/**
 * @file  XdwGraphicFormatWMFMetaPolyRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::PolyRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaPolyRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_POLY_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_POLY_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwPoint.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/**
 * @brief META_RECORDの座標配列を扱う抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::PolyRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PolyRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PolyRecord();
    
    /**
     * @brief 座標配列を格納したMETA_RECORDをパースする
     *
     * 座標配列格納したMETA_RECORDをパースして、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

    /********************************************/
    /* 集約 */
    
    /* 座標配列を格納するクラス */
    XdwPointVector fPoints;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 集約を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
};

#endif
