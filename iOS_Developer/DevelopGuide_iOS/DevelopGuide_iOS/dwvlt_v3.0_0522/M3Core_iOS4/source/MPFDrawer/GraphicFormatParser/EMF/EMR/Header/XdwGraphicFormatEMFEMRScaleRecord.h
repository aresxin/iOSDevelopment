/**
 * @file  XdwGraphicFormatWMFMetaScaleRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ScaleRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRScaleRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SCALE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SCALE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief 座標系の倍率を扱うMETA_RECORDを規定する抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ScaleRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ScaleRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ScaleRecord();
    
    /**
     * @brief 座標系の倍率を扱うMETA_RECORDをパースする
     *
     * 倍率を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
};

#endif
