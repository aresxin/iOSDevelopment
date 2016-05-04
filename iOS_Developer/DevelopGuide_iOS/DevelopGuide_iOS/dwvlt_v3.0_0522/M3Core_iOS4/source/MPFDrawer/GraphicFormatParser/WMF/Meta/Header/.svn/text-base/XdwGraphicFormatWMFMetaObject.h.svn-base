/**
 * @file  XdwGraphicFormatWMFMetaObject.h
 * @brief XdwGraphicFormat::WMF::Meta::Objectクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaObject.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_OBJECT_H_
#define _XDW_GRAPHICFORMAT_WMF_META_OBJECT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief 描画オブジェクトのハンドルを管理するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::Object
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Object();

    /**
     * @brief デストラクタ
     */
    virtual ~Object();

    /**
     * @brief インスタンスを初期化する
     *
     * @param bridge Imagerへアクセスするためのインターフェースのインスタンス
     * @param handle 描画ハンドル
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwBridgeDrawIF* bridge, unsigned long handle);
    
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
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! Imagerへアクセスするためのインターフェース */
    XdwBridgeDrawIF* fBridgeIF;

    /********************************************/
    /* 属性 */
    
    /*! ハンドル */
    unsigned long fHandle;

};

#endif
