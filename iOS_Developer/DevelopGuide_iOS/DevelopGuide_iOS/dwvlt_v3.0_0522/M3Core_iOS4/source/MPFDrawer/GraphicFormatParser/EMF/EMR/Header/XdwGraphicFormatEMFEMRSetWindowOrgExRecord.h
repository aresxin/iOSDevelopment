/**
 * @file  XdwGraphicFormatEMFEMRSetWindowOrgExRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetWindowOrgExRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSetWindowOrgExRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_WINDOW_ORG_EX_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_WINDOW_ORG_EX_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief EMR_SETWINDOWORGEXのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetWindowOrgExRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetWindowOrgExRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetWindowOrgExRecord();
    
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
