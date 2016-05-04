/**
 * @file  XdwGraphicFormatWMFMetaSetViewportOrgRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetViewportOrgRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetViewportOrgRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_VIEWPORT_ORG_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_VIEWPORT_ORG_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaPointRecord.h"

/**
 * @brief META_SETVIEWPORTORGレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetViewportOrgRecord : public XdwGraphicFormat::WMF::Meta::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetViewportOrgRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetViewportOrgRecord();
    
    /**
     * @brief META_SETVIEWPORTORGレコードをパースする
     *
     * 座標値を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
