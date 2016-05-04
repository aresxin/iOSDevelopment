/**
 * @file  XdwGraphicFormatEMFEMRObjectRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ObjectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRObjectRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_OBJECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_OBJECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/**
 * @brief EMRの描画オブジェクトを規定する抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ObjectRecord : public XdwGraphicFormat::EMF::EMR::Record
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
     * @brief オブジェクトのIDの取得
     *
     * @return オブジェクトのID
     */
    virtual long GetID();

    /**
     * @brief オブジェクトのハンドルの取得
     *
     * @return オブジェクトのハンドル
     */
    virtual unsigned long GetHandle();
    
protected:
    
    /********************************************/
    /* 属性 */
    
    /*! オブジェクトのID */
    long fID;
    /*! オブジェクトのハンドル */
    unsigned long fHandle;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * EMFデータのオブジェクトのIDを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
