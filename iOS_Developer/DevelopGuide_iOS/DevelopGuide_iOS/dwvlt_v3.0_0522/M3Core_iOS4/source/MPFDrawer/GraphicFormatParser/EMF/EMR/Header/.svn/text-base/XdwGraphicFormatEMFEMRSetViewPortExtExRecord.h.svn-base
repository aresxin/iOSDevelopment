/**
 * @file  XdwGraphicFormatEMFEMRSetViewPortExtExRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetViewPortExtExRecordクラスの定義
 *
 * @author DPSC SD3 TDG Yasuhiro Ito (Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2003-09-01
 *
 * @version 1.0
 *
 * Copyright (C) 2003 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_VIEW_PORT_EXT_EX_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_VIEW_PORT_EXT_EX_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief EMR_SETWINDOWORGEXのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetViewPortExtExRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetViewPortExtExRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetViewPortExtExRecord();
    
    /**
     * @brief EMRSETVIEWPORTEXTEX構造体をパースする
     *
     * 座標値を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
