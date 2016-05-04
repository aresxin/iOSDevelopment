/**
 * @file  XdwGraphicFormatEMFEMRSetWindowExtExRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetWindowExtExRecordクラスの定義
 *
 * @author DPSC SD3 TDG Yasuhiro Ito (Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2003-09-01
 * @version 1.0
 * @todo 謎のコードがある。2004-02-10
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_WINDOW_EXT_EX_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_WINDOW_EXT_EX_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief EMR_SETWINDOWORGEXのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetWindowExtExRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetWindowExtExRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetWindowExtExRecord();
    
    /**
     * @brief EMRSETWINDOWORGEX構造体をパースする
     *
     * 座標値を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
