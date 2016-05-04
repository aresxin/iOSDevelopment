/**
 * @file  XdwGraphicFormatWMFMetaSetBKColorRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetBKColorRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetBKColorRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_BK_COLOR_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_BK_COLOR_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaColorRecord.h"

/**
 * @brief META_SETBKCOLORのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetBKColorRecord : public XdwGraphicFormat::WMF::Meta::ColorRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetBKColorRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetBKColorRecord();
    
    /**
     * @brief META_SETBKCOLORをパースする
     *
     * 背景色を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
