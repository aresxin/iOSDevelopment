/**
 * @file  XdwGraphicFormatEMFEMRSetMapModeRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetMapModeRecordクラスの定義
 *
 * @author DPSC SD3 TDG Yasuhiro Ito (Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2003-09-01
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetMapModeRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_MAP_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_MAP_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/**
 * @brief EMR_SetMapMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SetMapModeRecord : public XdwGraphicFormat::EMF::EMR::ModeRecord
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
     * @brief EMRSetMapMODE構造体をパースする
     *
     * 背景モードを読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
