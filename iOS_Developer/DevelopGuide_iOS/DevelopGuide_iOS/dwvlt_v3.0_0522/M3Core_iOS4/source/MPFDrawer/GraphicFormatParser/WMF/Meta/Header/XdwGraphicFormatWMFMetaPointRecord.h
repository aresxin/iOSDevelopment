/**
 * @file  XdwGraphicFormatWMFMetaPointRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::PointRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaPointRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_POINT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_POINT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"

/**
 * @brief 単一の座標を扱うMetaを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::PointRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PointRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PointRecord();
    
    /**
     * @brief 座標値を格納したMeta構造体をパースする
     *
     * 座標値を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 座標を管理するクラス */
    XdwGraphicFormat::GDI::Point fPoint;

    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
