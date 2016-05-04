/**
 * @file  XdwGraphicFormatEMFEMRSetMapperFlagsRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetMapperFlagsRecordクラスの定義
 *
 * @author DPSC SD3 TDG Yasuhiro Ito (Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2003-01-27
 * @version 1.0
 * $Id:
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_MAPPER_FLAGS_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_MAPPER_FLAGS_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/**
 * @brief EMR_SetMapMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SetMapperFlagsRecord : public XdwGraphicFormat::EMF::EMR::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetMapperFlagsRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetMapperFlagsRecord();

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
