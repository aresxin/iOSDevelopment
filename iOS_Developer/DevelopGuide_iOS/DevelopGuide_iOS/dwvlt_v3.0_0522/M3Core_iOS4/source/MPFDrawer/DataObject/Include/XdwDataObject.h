/**
 * @file  XdwDataObject.h
 * @brief XdwDataObjectクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObject.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_H_
#define _XDW_DATA_OBJECT_H_

/* 本パッケージで全体的に使用するIncludeファイル */
#include "System/SystemIF/XdwError.h"
#include "System/SystemIF/XdwNew.h"
#include "System/SystemIF/XdwConfig.h"
#include "System/SystemIF/XdwAssert.h"

/**
 * @brief 大きなバイナリデータに対する操作をパッケージ化するクラス
 */
class XdwDataObject
{
public:

    /********************************************/
    /* クラス */

    /*! 大きなバイナリデータにアクセスする際に用いるインターフェース */
    class Binary;
    /*! 各実装パッケージで共通して、使用するインターフェース */
    class Common;

    /********************************************/
    /* パッケージ */
    
    /*! バイナリデータのマッピング場所を統括して、アクセスさせるパッケージ */
    class Base;
    /*! バイナリデータの圧縮方法を統括して、アクセスさせるパッケージ */
    class Filter;
};

#endif
