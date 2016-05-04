/**
 * @file  XdwGraphicFormatWMFMetaScaleViewportExtRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ScaleViewportExtRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRScaleViewportExtRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_META_SCALE_VIEWPORT_EXT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_META_SCALE_VIEWPORT_EXT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRScaleRecord.h"

/**
 * @brief EMR_SCALEVIEWPORTEXTレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ScaleViewportExtRecord : public XdwGraphicFormat::EMF::EMR::ScaleRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ScaleViewportExtRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ScaleViewportExtRecord();
    
    /**
     * @brief EMR_SCALEVIEWPORTEXTレコードをパースする
     *
     * 倍率を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
