/**
 * @file  XdwGraphicFormatWMFMetaCreatePaletteRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::CreatePaletteRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaCreatePaletteRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_CREATE_PALETTE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_CREATE_PALETTE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogPalette.h"

/**
 * @brief META_CREATEPALETTEを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::CreatePaletteRecord : public XdwGraphicFormat::WMF::Meta::ObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    CreatePaletteRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~CreatePaletteRecord();
    
    /**
     * @brief META_CREATEPALETTEレコードをパースする
     *
     * パレット属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! LOGPALETTE構造体を規定するクラス */
    XdwGraphicFormat::GDI::LogPalette fPalette;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * LOGPALETTE構造体を規定するクラスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
