/**
 * @file  XdwGraphicFormatEMFEMRSetROP2Record.h
 * @brief XdwGraphicFormat::EMF::EMR::SetROP2Recordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetROP2Record.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_ROP2_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_ROP2_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/**
 * @brief EMR_SETPOLYFILLMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SetROP2Record : public XdwGraphicFormat::EMF::EMR::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetROP2Record();

    /**
     * @brief デストラクタ
     */
    virtual ~SetROP2Record();

    /**
     * @brief EMRSETROP2構造体をパースする
     *
     * ROP2コードを読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
