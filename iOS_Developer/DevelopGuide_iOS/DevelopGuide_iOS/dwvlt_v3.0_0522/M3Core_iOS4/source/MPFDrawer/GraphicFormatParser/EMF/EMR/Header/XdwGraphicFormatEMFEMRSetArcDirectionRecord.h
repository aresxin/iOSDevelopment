/**
 * @file  XdwGraphicFormatEMFEMRSetArcDirectionRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetArcDirectionRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-30
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_ARC_DIRECTION_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_ARC_DIRECTION_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"


/**
 * @brief EMRSETARCDICETION構造体を規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetArcDirectionRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetArcDirectionRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~SetArcDirectionRecord();
    
    /**
     * @brief SetArcDirection構造体をパースする
     *
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    

};

#endif
