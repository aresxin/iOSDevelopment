/**
 * @file  XdwGraphicFormatWMFMetaRealizePaletteRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::RealizePaletteRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaRealizePaletteRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_REALIZE_PALETTE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_REALIZE_PALETTE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObjectRecord.h"

/**
 * @brief META_CREATEPALETTEを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::RealizePaletteRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RealizePaletteRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RealizePaletteRecord();
    
    /**
     * @brief META_CREATEPALETTEレコードをパースする
     *
     * パレット属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

};

#endif
