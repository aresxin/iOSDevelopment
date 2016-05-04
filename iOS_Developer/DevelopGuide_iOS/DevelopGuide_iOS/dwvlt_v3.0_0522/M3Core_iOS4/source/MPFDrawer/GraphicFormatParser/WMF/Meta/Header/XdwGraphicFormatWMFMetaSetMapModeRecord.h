/**
 * @file  XdwGraphicFormatWMFMetaSetMapModeRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetMapModeRecordクラスの定義
 *
 * @author DPSC SD3 TDG Yasuhiro Ito (Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2003-09-01
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetMapModeRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_Meta_SET_MAP_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_Meta_SET_MAP_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaModeRecord.h"

/**
 * @brief Meta_SetMapMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::WMF::Meta::SetMapModeRecord : public XdwGraphicFormat::WMF::Meta::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetMapModeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetMapModeRecord();

    /**
     * @brief MetaSetMapMODE構造体をパースする
     *
     * 背景モードを読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
