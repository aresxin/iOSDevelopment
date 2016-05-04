/**
 * @file  XdwDataObjectFilter.h
 * @brief XdwDataObjectFilterクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectFilter.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_FILTER_H_
#define _XDW_DATA_OBJECT_FILTER_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "XdwDataObject.h"

/**
 * @brief 圧縮/暗号化されているバイナリデータに対する操作をパッケージ化するクラス
 * 
 * OKDを伸張する実装クラスとDESを伸張する実装クラスを提供する 
 */
class XdwDataObject::Filter
{
public:

    /********************************************/
    /* クラス */

    /*! 圧縮/暗号化されているバイナリデータにアクセスする際に用いるインターフェース */
    class Interface;

    /*! OKD圧縮されているバイナリデータにアクセスするための実装クラス */
    class OKD;
    /*! DES暗号化されているバイナリデータにアクセスするための実装クラス */
    class DES;
};

#endif
