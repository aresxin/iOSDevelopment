/**
 * @file  XdwGraphicFormatWMFMetaSetViewportExtRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetViewportExtRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetViewportExtRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_VIEWPORT_EXT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_VIEWPORT_EXT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaSizeRecord.h"

/**
 * @brief META_SETVIEWPORTEXTレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetViewportExtRecord : public XdwGraphicFormat::WMF::Meta::SizeRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetViewportExtRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetViewportExtRecord();
    
    /**
     * @brief META_SETVIEWPORTEXTレコードをパースする
     *
     * 座標値を読み込み、CTMを変更する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
