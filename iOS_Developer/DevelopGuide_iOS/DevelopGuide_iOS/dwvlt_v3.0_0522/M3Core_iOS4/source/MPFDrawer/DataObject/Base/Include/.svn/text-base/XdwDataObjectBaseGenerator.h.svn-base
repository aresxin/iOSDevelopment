/** 
 * @file  XdwDataObjectBaseGenerator.h
 * @brief XdwDataObject::Generatorインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBaseGenerator.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_GENERATOR_H_
#define _XDW_DATA_OBJECT_BASE_GENERATOR_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDataObjectBase.h"

/* 関連するFileIOインターフェースの宣言 */
class XdwFileIO;

/**
 * @brief XdwDataObject::Binaryのインスタンスを作成するクラス
 *
 * ストレージ上に存在するバイナリデータにアクセスするXdwDataObject::Base::Interfaceと
 * メモリ上に存在させるバイナリデータにアクセスするXdwDataObject::Base::Interfaceをインスタンス化する<br>
 * メソッドの2つをクライアントが使い分ける
 */
class XdwDataObject::Base::Generator
{
public:
    /********************************************/
    /* 列挙型 */

    /*! Generatorを使用するプロダクトの種類 */
    enum ProductType{
        /*! 何も指定していない状態(エラー) */
        INVALID_TYPE,
        /*! DocuWorks Direct Printのデバッグ用 */
        DIRECT_PRINT_DEBUG,
        /*! DocuWorks Viewer Light for Windows CE */
        VIEWER_FOR_CE,
        /*! DocuWorks Converter Library */
        CONVERTER_LIBRARY
    };

    /*! 作成するメモリオブジェクトの使用方法 */
    enum MemoryLimitMode{
        /*! メモリオブジェクトを普通に使用する場合 */
        NORMAL,
        /*! メモリオブジェクトをロックする場合 */
        LOCKED
    };
    
    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     *
     * 初期化関数を呼ばなければ、使用できない
     */
    Generator();

    /**
     * @brief デストラクタ
     */
    virtual ~Generator();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @param file_io インスタンスが関連をはるXdwFileIOインターフェースのインスタンス
     * @param type 本クラスのインスタンスを作成するプロダクトの種類<br>
     *             XdwDataObject::Generator::ProductTypeを参照
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwFileIO* file_io, XdwDataObject::Base::Generator::ProductType type);

    /**
     * @brief ストレージ上に存在するバイナリデータにアクセスするXdwDataObject::Binaryのインスタンスを作成する
     *
     * @param file ストレージ上のファイルを識別する(基本的にはファイル名)
     *
     * @return XdwDataObject::Base::Interfaceインターフェースのインスタンス
     */
    virtual XdwDataObject::Base::Interface* CreateFileDataObject(void* file);

    /**
     * @brief メモリ上に存在させるバイナリデータにアクセスするXdwDataObject::Binaryをインスタンスを作成する
     *
     * @param size バイナリデータが必要とするサイズ
     *
     * @return XdwDataObject::Base::Interfaceインターフェースのインスタンス
     */
    virtual XdwDataObject::Base::Interface* CreateMemoryDataObject(long size);

    /**
     * @brief メモリオブジェクトがする可能性がある最大メモリサイズを取得する
     *
     * @param mode XdwDataObject::Generator::MemoryLimitModeを参照
     *
     * @return メモリオブジェクトがする可能性がある最大メモリサイズ<br>
     *         byte数
     */
    virtual long GetMemoryLimit(XdwDataObject::Base::Generator::MemoryLimitMode mode);
    
protected:
    /********************************************/
    /* 依存 */

    /*! ファイル入出力ラッパー */
    XdwFileIO* fFileIO;
    
    /********************************************/
    /* 属性 */

    /*! プロダクトの種類 */
    XdwDataObject::Base::Generator::ProductType fProductType;
    
};

#endif
