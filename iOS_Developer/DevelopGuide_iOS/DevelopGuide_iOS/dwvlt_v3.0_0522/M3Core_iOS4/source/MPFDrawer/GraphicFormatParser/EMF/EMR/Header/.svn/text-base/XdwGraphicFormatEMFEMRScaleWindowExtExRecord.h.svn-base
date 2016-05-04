/**
 * @file  XdwGraphicFormatEMFEMRScaleWindowExtExRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ScaleWindowExtExRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SCALE_WINDOW_EXT_EX_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SCALE_WINDOW_EXT_EX_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRScaleRecord.h"

/**
 * @brief META_SCALEVIEWPORTEXTレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ScaleWindowExtExRecord : public XdwGraphicFormat::EMF::EMR::ScaleRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ScaleWindowExtExRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ScaleWindowExtExRecord();
    
    /**
     * @brief META_SCALEWindowEXTレコードをパースする
     *
     * 倍率を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
