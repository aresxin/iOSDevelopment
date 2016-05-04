/**
 * @file  XdwGraphicFormatWMFMetaLineToRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::LineToRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaLineToRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_LINE_TO_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_LINE_TO_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaPointRecord.h"

/**
 * @brief META_LINETOレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::LineToRecord : public XdwGraphicFormat::WMF::Meta::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LineToRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~LineToRecord();
    
    /**
     * @brief META_LINETOレコードをパースする
     *
     * 座標値を読み込み、線分を描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
