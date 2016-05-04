/**
 * @file  XdwGraphicFormatEMFEMRSetPolyFillModeRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetPolyFillModeRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetPolyFillModeRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_POLY_FILL_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_POLY_FILL_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/**
 * @brief EMR_SETPOLYFILLMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SetPolyFillModeRecord : public XdwGraphicFormat::EMF::EMR::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetPolyFillModeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetPolyFillModeRecord();

    /**
     * @brief EMRSETPOLYFILLMODE構造体をパースする
     *
     * 塗りつぶしモードを読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
