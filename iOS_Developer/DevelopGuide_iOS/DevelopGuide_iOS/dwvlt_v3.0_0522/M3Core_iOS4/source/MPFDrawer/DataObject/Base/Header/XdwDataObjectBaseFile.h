/** 
 * @file  XdwDataObjectBaseFile.h
 * @brief XdwDataObject::Base::Fileクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBaseFile.h,v 1.5 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_FILE_H_
#define _XDW_DATA_OBJECT_BASE_FILE_H_

/* パッケージを記述するためのIncludeファイル */
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 親クラスを定義したIncludeファイル */
#include "XdwDataObjectBaseStorage.h"

/**
 * @brief ファイル上のバイナリデータにアクセスするクラス
 *
 * ファイルに存在するバイナリデータをバッファリングして提供する<br>
 * 読み込み専用
 */
class XdwDataObject::Base::File : public XdwDataObject::Base::Storage
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     *
     * 初期化関数を呼ばなければ、使用できない
     *
     * @param file_name アクセスするファイル名<br>
     *                  文字コードはプラットフォームに依存させる
     * @param file_io XdwFileIOインターフェースのインスタンス
     */
    File(void* file_name, XdwFileIO* file_io);
    
    /**
     * @brief デストラクタ
     */
    virtual ~File();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize();
    
    /**
     * @brief 現在位置のバイナリデータに書き込む
     *
     * アクセスしても現在位置は移動しない
     *
     * @param buffer 書き込みデータが存在するバッファ
     * @param size バッファにアクセスできるサイズ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(void* buffer, long size);

    /**
     * @brief 現在のバイナリデータを扱う際に、ストレージは使用しない
     *
     * 初期化する前に本メソッドを使用することで、ストレージには一切アクセスしない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Lock();
    
protected:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief バッファへの書き込むのチェック
     *
     * 書き込んでいれば、バッファ上のデータを、ファイルに更新する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode CheckBufferWrited();

    /**
     * @brief 現在のファイルサイズの取得
     *
     * @return 現在のファイルサイズ<br>
     *         Byte単位
     */
    virtual long GetFileSize();
    
    /**
     * @brief Lockされているかのチェック
     *
     * @return true Lockされている
     * @return false Lockされていない
     */
    virtual bool CheckLocked();

    /**
     * @brief バッファをストレージに避難する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SaveBuffer();

};

#endif
