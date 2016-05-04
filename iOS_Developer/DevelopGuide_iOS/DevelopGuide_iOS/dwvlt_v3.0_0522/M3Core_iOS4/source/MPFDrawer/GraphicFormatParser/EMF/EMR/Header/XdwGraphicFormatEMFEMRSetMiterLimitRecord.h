/**
 * @file  XdwGraphicFormatEMFEMRSetMiterLimitRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetMiterLimitRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetMiterLimitRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_MITER_LIMIT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_MITER_LIMIT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/**
 * @brief EMR_SETMITERLIMITのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SetMiterLimitRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetMiterLimitRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetMiterLimitRecord();

    /**
     * @brief EMRSETMITERLIMIT構造体をパースする
     *
     * マイター制限値を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
