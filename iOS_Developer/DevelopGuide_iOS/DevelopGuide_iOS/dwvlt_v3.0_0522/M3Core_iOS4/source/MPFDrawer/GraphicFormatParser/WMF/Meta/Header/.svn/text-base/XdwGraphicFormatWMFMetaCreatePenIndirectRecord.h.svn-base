/**
 * @file  XdwGraphicFormatWMFMetaCreatePenIndirectRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::CreatePenIndirectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaCreatePenIndirectRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_CREATE_PEN_INDIRECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_CREATE_PEN_INDIRECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogPen.h"

/**
 * @brief META_CREATEPENINDIRECTを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::CreatePenIndirectRecord : public XdwGraphicFormat::WMF::Meta::ObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    CreatePenIndirectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~CreatePenIndirectRecord();
    
    /**
     * @brief META_CREATEPENINDIRECTレコードをパースする
     *
     * ペン属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! LOGPEN構造体を規定するクラス */
    XdwGraphicFormat::GDI::LogPen fPen;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * LOGPEN構造体を規定するクラスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
