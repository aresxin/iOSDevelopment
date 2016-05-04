/**
 * @file  XdwGraphicFormatWMFMetaRectangleRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::RectangleRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaRectangleRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_RECTANGLE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_RECTANGLE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRectRecord.h"

/**
 * @brief META_RECTANGLEレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::RectangleRecord : public XdwGraphicFormat::WMF::Meta::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RectangleRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RectangleRecord();
    
    /**
     * @brief META_RECTANGLEレコードをパースする
     *
     * 矩形を読み込み、描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
