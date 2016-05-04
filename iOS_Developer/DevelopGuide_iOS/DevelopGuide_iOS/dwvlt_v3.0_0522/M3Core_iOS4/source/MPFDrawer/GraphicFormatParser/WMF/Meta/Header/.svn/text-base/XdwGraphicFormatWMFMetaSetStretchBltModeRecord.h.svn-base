/**
 * @file  XdwGraphicFormatWMFMetaSetStretchBltModeRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetStretchBltModeRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetStretchBltModeRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_STRETCH_BLT_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_STRETCH_BLT_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaModeRecord.h"

/**
 * @brief META_SETSTRETCHBLTMODEレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetStretchBltModeRecord : public XdwGraphicFormat::WMF::Meta::ModeRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetStretchBltModeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetStretchBltModeRecord();
    
    /**
     * @brief META_SETSTRETCHBLTMODEレコードをパースする
     *
     * 拡縮モードを読み込んで、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
