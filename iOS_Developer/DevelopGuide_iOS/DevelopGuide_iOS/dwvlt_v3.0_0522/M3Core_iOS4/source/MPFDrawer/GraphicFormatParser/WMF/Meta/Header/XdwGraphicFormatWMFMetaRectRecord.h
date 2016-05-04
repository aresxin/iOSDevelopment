/**
 * @file  XdwGraphicFormatWMFMetaRectRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::RectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaRectRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_RECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_RECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIRectangle.h"

/**
 * @brief 単一の矩形を扱うレコードを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::RectRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RectRecord();
    
    /**
     * @brief 矩形を格納したMeta構造体をパースする
     *
     * 矩形を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 座標を管理するクラス */
    XdwGraphicFormat::GDI::Rectangle fRect;

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
