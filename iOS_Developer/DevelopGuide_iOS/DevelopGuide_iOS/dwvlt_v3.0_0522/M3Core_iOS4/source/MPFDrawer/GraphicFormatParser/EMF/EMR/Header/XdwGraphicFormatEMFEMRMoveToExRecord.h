/**
 * @file  XdwGraphicFormatEMFEMRMoveToExRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::MoveToExRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRMoveToExRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_MOVE_TO_EX_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_MOVE_TO_EX_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief EMR_MOVETOEXのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::MoveToExRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    MoveToExRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~MoveToExRecord();
    
    /**
     * @brief EMRMOVETOEX構造体をパースする
     *
     * 座標値を読み込み、Imagerのパスの現在地にセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
