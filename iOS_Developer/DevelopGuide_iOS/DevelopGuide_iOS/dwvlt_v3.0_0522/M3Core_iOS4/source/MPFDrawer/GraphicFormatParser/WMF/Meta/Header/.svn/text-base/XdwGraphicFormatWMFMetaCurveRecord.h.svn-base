/**
 * @file  XdwGraphicFormatWMFMetaCurveRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::CurveRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaCurveRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_CURVE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_CURVE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIEllipse.h"

/**
 * @brief 円弧を扱うレコードを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::CurveRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    CurveRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~CurveRecord();
    
    /**
     * @brief 円弧を格納したMETA_RECORDをパースする
     *
     * 円弧を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 円弧を規定するクラス */
    XdwGraphicFormat::GDI::Ellipse fEllipse;

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
