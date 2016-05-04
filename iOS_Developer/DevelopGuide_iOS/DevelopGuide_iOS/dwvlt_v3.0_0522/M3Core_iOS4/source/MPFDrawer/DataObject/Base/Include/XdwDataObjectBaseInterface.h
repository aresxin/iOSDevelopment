/** 
 * @file  XdwDataObjectBaseInterface.h
 * @brief XdwDataObject::Binaryインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBaseInterface.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_INTERFACE_H_
#define _XDW_DATA_OBJECT_BASE_INTERFACE_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "DataObject/Include/XdwDataObjectCommon.h"

/**
 * @interface XdwDataObject::Base::Interface XdwDataObjectBaseInterface.h
 * @brief バイナリデータのマッピング場所を気にすることなく、アクセスする際に用いるインターフェース
 *
 * XdwDataObject::Base::Geberatorクラスでインスタンス化されたものを用いる<br>
 * 全てのバイナリデータはバッファリングされている
 */
class XdwDataObject::Base::Interface : public XdwDataObject::Common
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デストラクタ
     */
    virtual ~Interface() = 0;
    
    /**
     * @brief 現在のバイナリデータを扱う際に、ストレージは使用しない
     *
     * 初期化する前に本メソッドを使用することで、ストレージには一切アクセスしない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Lock() = 0;

    /**
     * @brief 現在バッファ上にあるバイナリデータをいったん、ストレージに全て格納する
     *
     * その後、新たにバッファを取得し直す
     *
     * @param buffer_size 新たに取得するバッファのサイズ<br>
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Purge(long buffer_size) = 0;
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwDataObject::Base::Interface::~Interface()
{
}

#endif
