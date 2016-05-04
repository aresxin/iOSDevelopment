/**
 * @file  XdwGraphicFormatEMFEMRSetBKModeRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetBKModeRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetBKModeRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_BK_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_BK_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/**
 * @brief EMR_SETBKMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SetBKModeRecord : public XdwGraphicFormat::EMF::EMR::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetBKModeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetBKModeRecord();

    /**
     * @brief EMRSETBKMODE構造体をパースする
     *
     * 背景モードを読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
