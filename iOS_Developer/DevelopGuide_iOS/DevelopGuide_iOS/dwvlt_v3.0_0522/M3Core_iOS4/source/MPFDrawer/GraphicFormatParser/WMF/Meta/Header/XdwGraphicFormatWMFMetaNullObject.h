/**
 * @file  XdwGraphicFormatWMFMetaNullObject.h
 * @brief XdwGraphicFormat::WMF::Meta::NullObjectクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaNullObject.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_NULL_OBJECT_H_
#define _XDW_GRAPHICFORMAT_WMF_META_NULL_OBJECT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaObject.h"

/**
 * @brief 描画オブジェクトに対して、何もしないクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::NullObject : public XdwGraphicFormat::WMF::Meta::Object
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    NullObject();

    /**
     * @brief デストラクタ
     */
    virtual ~NullObject();
    
    /**
     * @brief 描画オブジェクトを選択する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Select();
    
    /**
     * @brief 描画オブジェクトを削除する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Delete();
};

#endif
