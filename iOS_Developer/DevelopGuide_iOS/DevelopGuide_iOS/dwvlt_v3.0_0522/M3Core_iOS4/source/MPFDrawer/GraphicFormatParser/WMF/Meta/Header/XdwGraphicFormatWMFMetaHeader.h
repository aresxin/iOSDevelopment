/**
 * @file  XdwGraphicFormatWMFMetaHeader.h
 * @brief XdwGraphicFormat::WMF::Meta::Headerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaHeader.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_HEADERD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_HEADERD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"
#include "XdwDocuWorks.h"

/**
 * @brief METAHEADER構造体を規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::Header
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Header();

    /**
     * @brief デストラクタ
     */
    virtual ~Header();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary WMFが格納されているバイナリデータ管理インターフェースのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary);
    
    /**
     * @brief METAHEADER構造体をパースする
     *
     * 各MetaHeaderにあわせて、必要な処理を行う
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
    /**
     * @brief オブジェクトハンドル数を取得する
     *
     * @return オブジェクトハンドル数
     */
    virtual short GetObjectCount();
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータ管理インターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;

    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! オブジェクト数 */
    short fObjectCount;
    
};

#endif
