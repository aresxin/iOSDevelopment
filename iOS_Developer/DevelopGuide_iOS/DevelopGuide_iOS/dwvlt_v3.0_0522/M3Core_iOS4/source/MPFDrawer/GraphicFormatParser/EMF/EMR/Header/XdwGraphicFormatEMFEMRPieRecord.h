/**
 * @file  XdwGraphicFormatEMFEMRPieRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PieRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id :
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_PIE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_PIE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRArcRecord.h"

/**
 * @brief Pieレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PieRecord : public XdwGraphicFormat::EMF::EMR::ArcRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PieRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PieRecord();
    
    /**
     * @brief Pieレコードをパースする
     *
     * ARCTO
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

};

#endif
