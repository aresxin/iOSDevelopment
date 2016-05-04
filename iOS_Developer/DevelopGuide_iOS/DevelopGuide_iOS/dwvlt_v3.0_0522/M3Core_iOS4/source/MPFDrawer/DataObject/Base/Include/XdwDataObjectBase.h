/**
 * @file  XdwDataObjectBase.h
 * @brief XdwDataObjectBaseクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBase.h,v 1.5 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_H_
#define _XDW_DATA_OBJECT_BASE_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "DataObject/Include/XdwDataObject.h"

/**
 * @brief 大きなバイナリデータに対する操作をパッケージ化するクラス
 * 
 * インターフェースとして
 * 大きなバイナリデータにアクセスする際に用いるXdwDataObject::Base::Interfaceインターフェースと
 * XdwDataObject::Base::Interfaceインターフェースをインスタンス化する
 * XdwDataObject::Base::Generatorクラスを提供する
 */
class XdwDataObject::Base
{
public:

    /********************************************/
    /* クラス */

    /*! 大きなバイナリデータにアクセスする際に用いるインターフェース */
    class Interface;
    /*! XdwDataObject::Binaryのインスタンスを作成するインターフェース */
    class Generator;

    /*! バッファリングするXdwDataObject::Base::Interface */
    class Buffer;
    /*! ストレージを扱うXdwDataObject::Base::Interface */
    class Storage;
    /*! メモリを扱うXdwDataObject::Base::Interface */
    class Memory;
    /*! ファイルを扱うXdwDataObject::Base::Interface */
    class File;
    /*! 一時ファイルを扱うXdwDataObject::Base::Interface */
    class TmpFile;
    /*! 外部から取得したメモリを扱うXdwDataObject::Base::Interface */
    class SharedMemory;
};

#endif
