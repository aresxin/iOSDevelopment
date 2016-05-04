/** 
 * @file  XdwDataObjectFilterInterface.h
 * @brief XdwDataObject::Filter::Interfaceインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectFilterInterface.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_FILTER_INTERFACE_H_
#define _XDW_DATA_OBJECT_FILTER_INTERFACE_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDataObjectFilter.h"

/* 親クラスのIncludeファイル */
#include "XdwDataObjectCommon.h"

/**
 * @interface XdwDataObject::Filter::Interface XdwDataObjectFilterInterface.h
 * @brief 圧縮/暗号化されていることを気にすることなく、バイナリデータに対してアクセスするためのインターフェース
 *
 * 実装クラスをインスタンス化して、使用する<br>
 * 基本的には現在位置より前に移動することは許さない
 */
class XdwDataObject::Filter::Interface : public XdwDataObject::Common
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デストラクタ
     */
    virtual ~Interface() = 0;
    
    /**
     * @brief 自身の複製を作成する
     *
     * @return 現在の状態をコピーしたXdwDataObject::Filter::Interfaceのインスタンス
     */
    virtual XdwDataObject::Filter::Interface* Clone() = 0;

    /**
     * @brief 複製作成に必要なサイズの取得
     *
     * 伸張に必要なサイズと一致する
     *
     * @return 複製作成に必要なサイズ
     */
    virtual long GetCloneSize() = 0;
    
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwDataObject::Filter::Interface::~Interface()
{
}

#endif
