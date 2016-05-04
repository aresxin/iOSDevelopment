/**
 * @file  XdwGraphicFormatWMFMetaSetROP2Record.h
 * @brief XdwGraphicFormat::WMF::Meta::SetROP2Recordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetROP2Record.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_ROP2_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_ROP2_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaModeRecord.h"

/**
 * @brief META_SETROP2レコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetROP2Record : public XdwGraphicFormat::WMF::Meta::ModeRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetROP2Record();

    /**
     * @brief デストラクタ
     */
    virtual ~SetROP2Record();
    
    /**
     * @brief META_SETROP2レコードをパースする
     *
     * ROPコードを読み込んで、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
