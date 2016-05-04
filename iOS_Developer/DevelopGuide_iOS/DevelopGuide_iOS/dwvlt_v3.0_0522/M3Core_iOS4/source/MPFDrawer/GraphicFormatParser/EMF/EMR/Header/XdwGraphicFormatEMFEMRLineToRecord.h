/**
 * @file  XdwGraphicFormatEMFEMRLineToRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::LineToRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRLineToRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_LINE_TO_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_LINE_TO_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief EMR_LINETOのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::LineToRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LineToRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~LineToRecord();
    
    /**
     * @brief EMRLINETO構造体をパースする
     *
     * 座標値を読み込み、現在位置と直線を構成するようにImagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
