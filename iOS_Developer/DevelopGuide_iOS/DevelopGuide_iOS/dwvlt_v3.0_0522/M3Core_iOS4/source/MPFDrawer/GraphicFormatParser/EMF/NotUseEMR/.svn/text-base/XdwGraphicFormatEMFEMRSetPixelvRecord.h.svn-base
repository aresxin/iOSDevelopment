/**
 * @file  XdwGraphicFormatEMFEMRSetPixelvRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetPixelvRecordクラスの定義
 *
 * @author Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-1-27
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_PIXCEL_V__RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_PIXCEL_V__RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"
/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRColorRecord.h"
/**
 * @brief EMR_SETWINDOWORGEXのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetPixelvRecord : public XdwGraphicFormat::EMF::EMR::PointRecord , public XdwGraphicFormat::EMF::EMR::ColorRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetPixelvRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetPixelvRecord();
    
    /**
     * @brief EMRSETPixcelv構造体をパースする
     *
     * 座標値とカラーを読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

   /********************************************/
    /* 集約 */

};

#endif
