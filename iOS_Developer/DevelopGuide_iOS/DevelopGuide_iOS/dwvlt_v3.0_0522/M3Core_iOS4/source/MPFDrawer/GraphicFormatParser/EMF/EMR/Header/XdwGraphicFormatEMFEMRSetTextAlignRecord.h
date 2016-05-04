/**
 * @file  XdwGraphicFormatEMFEMRSetTextAlignRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetTextAlignRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetTextAlignRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_TEXT_ALIGN_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_TEXT_ALIGN_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/* 列挙型の定義 */
#include "XdwFont.h"

/**
 * @brief EMR_SETTEXTALIGNのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetTextAlignRecord : public XdwGraphicFormat::EMF::EMR::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetTextAlignRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetTextAlignRecord();

    /**
     * @brief EMRSETTEXTALIGN構造体をパースする
     *
     * フォント配置位置を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
