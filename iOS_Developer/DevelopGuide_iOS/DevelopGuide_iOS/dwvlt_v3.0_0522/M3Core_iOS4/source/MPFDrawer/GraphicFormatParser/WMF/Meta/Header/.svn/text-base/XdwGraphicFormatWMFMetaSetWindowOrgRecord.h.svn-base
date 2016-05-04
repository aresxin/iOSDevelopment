/**
 * @file  XdwGraphicFormatWMFMetaSetWindowOrgRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetWindowOrgRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetWindowOrgRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_WINDOW_ORG_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_WINDOW_ORG_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaPointRecord.h"

/**
 * @brief META_SETWINDOWORGレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetWindowOrgRecord : public XdwGraphicFormat::WMF::Meta::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetWindowOrgRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetWindowOrgRecord();
    
    /**
     * @brief META_SETWINDOWORGレコードをパースする
     *
     * 座標値を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
