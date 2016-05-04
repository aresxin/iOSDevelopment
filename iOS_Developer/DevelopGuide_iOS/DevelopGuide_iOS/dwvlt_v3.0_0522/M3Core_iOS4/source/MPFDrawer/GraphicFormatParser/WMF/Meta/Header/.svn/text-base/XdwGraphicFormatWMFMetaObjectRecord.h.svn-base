/**
 * @file  XdwGraphicFormatWMFMetaObjectRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::ObjectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaObjectRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_OBJECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_OBJECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 依存するクラスの宣言 */
class XdwRasterImageAttribute;

/**
 * @brief wmfの描画オブジェクトを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::ObjectRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ObjectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ObjectRecord();

    /**
     * @brief オブジェクトのハンドルの取得
     *
     * @return オブジェクトのハンドル
     */
    virtual unsigned long GetHandle();
    
protected:
    
    /********************************************/
    /* 属性 */
    
    /*! オブジェクトのハンドル */
    unsigned long fHandle;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * WMFデータのオブジェクトのIDを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();

    /**
     * @brief ラスター属性を初期化する
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual void InitializeAttribute(XdwRasterImageAttribute* attribute);
    
};

#endif
