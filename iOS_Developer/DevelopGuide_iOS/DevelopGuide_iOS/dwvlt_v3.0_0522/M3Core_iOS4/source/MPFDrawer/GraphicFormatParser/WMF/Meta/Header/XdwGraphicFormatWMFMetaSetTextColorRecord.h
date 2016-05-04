/**
 * @file  XdwGraphicFormatWMFMetaSetTextColorRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetTextColorRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetTextColorRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_TEXT_COLOR_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_TEXT_COLOR_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaColorRecord.h"

/**
 * @brief META_SETTEXTCOLORのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetTextColorRecord : public XdwGraphicFormat::WMF::Meta::ColorRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetTextColorRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetTextColorRecord();
    
    /**
     * @brief META_SETTEXTCOLORをパースする
     *
     * 前景色を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
