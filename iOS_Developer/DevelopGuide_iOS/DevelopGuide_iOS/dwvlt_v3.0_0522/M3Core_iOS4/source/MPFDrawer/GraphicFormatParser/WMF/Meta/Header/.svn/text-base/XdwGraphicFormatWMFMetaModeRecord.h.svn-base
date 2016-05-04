/**
 * @file  XdwGraphicFormatWMFMetaModeRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::ModeRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaModeRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/**
 * @brief META_RECORDの描画属性を規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::ModeRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ModeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ModeRecord();
    
    /**
     * @brief 描画属性を格納したMETA_RECORDをパースする
     *
     * 描画属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 属性 */
    
    /*! 描画属性 */
    short fMode;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 描画属性を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
