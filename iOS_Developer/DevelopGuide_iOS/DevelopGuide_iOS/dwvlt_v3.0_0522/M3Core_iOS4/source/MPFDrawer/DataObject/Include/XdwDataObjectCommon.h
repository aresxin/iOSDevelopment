/** 
 * @file  XdwDataObjectCommon.h
 * @brief XdwDataObject::Commonインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectCommon.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_COMMON_H_
#define _XDW_DATA_OBJECT_COMMON_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDataObject.h"

/* 親クラスのIncludeファイル */
#include "XdwDataObjectBinary.h"

/**
 * @interface XdwDataObject::Common XdwDataObjectCommon.h
 * @brief 各実装パッケージで共通して、使用するインターフェース
 */
class XdwDataObject::Common : public XdwDataObject::Binary
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デストラクタ
     */
    virtual ~Common() = 0;
    
    /**
     * @brief 複製可能かの確認
     *
     * @retval true 可能
     * @retval false 不可能
     */
    virtual bool IsClonable() = 0;
    
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwDataObject::Common::~Common()
{
}

#endif
