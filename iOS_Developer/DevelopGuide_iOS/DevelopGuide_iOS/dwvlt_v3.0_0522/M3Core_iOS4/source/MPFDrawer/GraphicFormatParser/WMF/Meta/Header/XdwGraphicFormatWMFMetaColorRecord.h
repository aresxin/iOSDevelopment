/**
 * @file  XdwGraphicFormatWMFMetaColorRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::ColorRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaColorRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_COLOR_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_COLOR_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIColorRef.h"

/**
 * @brief 単一色を扱うMetaを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::ColorRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ColorRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ColorRecord();
    
    /**
     * @brief COLORREF型を格納したMETARECORDをパースする
     *
     * COLORREF型を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 色を管理するクラス */
    XdwGraphicFormat::GDI::ColorRef fColor;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * WMFデータの色を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
