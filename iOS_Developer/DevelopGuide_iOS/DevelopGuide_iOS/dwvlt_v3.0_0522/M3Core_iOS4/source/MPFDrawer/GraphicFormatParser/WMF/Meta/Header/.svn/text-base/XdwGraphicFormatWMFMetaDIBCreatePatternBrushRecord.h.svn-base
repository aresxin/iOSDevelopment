/**
 * @file  XdwGraphicFormatWMFMetaDIBCreatePatternBrushRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::DIBCreatePatternBrushRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaDIBCreatePatternBrushRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_RASTER_OBJECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_RASTER_OBJECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObjectRecord.h"

/**
 * @brief META_DIBCREATEPATTERNBRUSHレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::DIBCreatePatternBrushRecord : public XdwGraphicFormat::WMF::Meta::ObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    DIBCreatePatternBrushRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~DIBCreatePatternBrushRecord();

    /**
     * @brief META_DIBCREATEPATTERNBRUSHレコードをパースする
     *
     * ラスターパターンの属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief ラスター属性を初期化する
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual void InitializeAttribute(XdwRasterImageAttribute* attribute);

    /**
     * @brief BITMAPINFO構造体を読み込み
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadAttribute(XdwRasterImageAttribute* attribute);
    
};

#endif
