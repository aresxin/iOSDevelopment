/**
 * @file  XdwDocuWorksBinaryInterface.h
 * @brief XdwDocuWorks::BinaryInterfaceインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksBinaryInterface.h,v 1.4 2009/12/22 08:11:15 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_BINARY_INTERFACE_H_
#define _XDW_DOCUWORKS_BINARY_INTERFACE_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorks.h"

/* 依存するパッケージのIncludeファイル */
#include "DataObject/Include/XdwDataObject.h"

/* 列挙型の定義のIncludeファイル */
#include "DataObject/Include/XdwDataObjectBinary.h"

/**
 * @interface XdwDocuWorks::BinaryInterface XdwDocuWorksBinaryInterface.h
 * @brief DocuWorksファイルの読み込みで必要なバイナリデータへアクセスするためのインターフェース
 *
 * エンディアンの差などを吸収する<br>
 * 小さいサイズのデータにしかアクセスさせないなど、ラッピングも行う
 */
class XdwDocuWorks::BinaryInterface
{
public:

    /********************************************/
    /* 列挙型 */

    /*! DocuWorksファイルフォーマットのエンディアン吸収時のByte数 */
    enum EndianBytes{
        /*! BYTEデータのByte数 */
        BYTE_BYTES = 1,
        /*! WORDデータのByte数 */
        WORD_BYTES = 2,
        /*! DWORDデータのByte数 */
        DOUBLE_WORD_BYTES = 4
    };
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デストラクタ
     */
    virtual ~BinaryInterface() = 0;
    
    /**
     * @brief セットされているXdwDataObject::Commonインターフェースのインスタンスへのアクセスを閉じる
     */
    virtual void Close() = 0;
    
    /**
     * @brief XdwDataObject::Commonインターフェースのインスタンスをセットする
     *
     * @param binary XdwDataObject::Commonインターフェースのインスタンス
     * @param delete_flag 受け取ったXdwDataObject::Commonインターフェースのインスタンスを削除するかのフラグ
     * @param start_offset データアクセス開始オフセット
     * @param access_size 開始オフセットからアクセスしていいデータサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetDataObject(XdwDataObject::Common* binary, bool delete_flag, long start_offset, long access_size) = 0;
    
    /**
     * @brief  現在セットされているXdwDataObject::Commonインターフェースのインスタンスを取得する
     *
     * @param refine 参照するか、取得するかのフラグ<br>
     *               取得した場合には、インスタンスの管理はクライアント側に移行する
     *
     * @return XdwDataObject::Commonインターフェースのインスタンス
     */
    virtual XdwDataObject::Common* GetDataObject(bool refine = true) = 0;
    
    /**
     * @brief アクセス可能なデータサイズを取得する
     *
     * @return アクセス可能なデータサイズ
     */
    virtual long GetDataSize() = 0;
    
    /**
     * @brief 現在位置を移動する
     *
     * @param offset 移動するオフセット
     * @param mode どの位置から開始するかの指定<br>
     *             XdwDataObject::Binary::SeekModeを参照
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Seek(long offset, XdwDataObject::Binary::SeekMode mode) = 0;

    /**
     * @brief データ先頭位置からの現在位置をbyte数で取得する
     *
     * @return データ先頭位置からのbyte数
     */
    virtual long Tell() = 0;

    /**
     * @brief　バッファの現在位置のポインタを取得する
     *
     * @param desired_size 読み込む際に必要とするバイナリデータのbyte数
     * @param feasible_size アクセスを許可するポインタのbyte数<br>
     *                      0ならバイナリデータの終端、0より上なら正常、0以下ならエラー
     * @return バッファの現在位置のポインタ
     */
    virtual unsigned char* GetCurrentPointer(long desired_size, long& feasible_size) = 0;

    /**
     * @brief 8BitのByteデータの読み込み
     *
     * 読み込みに成功すると1Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(unsigned char& data) = 0;
    
    /**
     * @brief 32BitのLong Wordデータの読み込み
     *
     * 読み込みに成功すると4Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(unsigned long& data) = 0;

    /**
     * @brief 32BitのLong Wordデータの読み込み
     *
     * 読み込みに成功すると4Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(long& data) = 0;
    
    /**
     * @brief 16BitのWordデータの読み込み
     *
     * 読み込みに成功すると2Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(unsigned short& data) = 0;

    /**
     * @brief 16BitのWordデータの読み込み
     *
     * 読み込みに成功すると2Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(short& data) = 0;
    
    /**
     * @brief 32BitのFloatデータの読み込み
     *
     * 読み込みに成功すると4Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(float& data) = 0;

    /**
     * @brief データを書き込む
     *
     * @param buffer 書き込むデータへのポインタ
     * @param size 書き込むデータのサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Write(void* buffer, long size) = 0;

    /**
     * @brief 32BitのLong Wordデータの書き込み
     *
     * 書き込みに成功すると4Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(unsigned long data) = 0;

    /**
     * @brief 32BitのLong Wordデータの書き込み
     *
     * 書き込みに成功すると4Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(long data) = 0;
    
    /**
     * @brief 16BitのWordデータの書き込み
     *
     * 書き込みに成功すると2Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(unsigned short data) = 0;

    /**
     * @brief 16BitのWordデータの書き込み
     *
     * 書き込みに成功すると2Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(short data) = 0;
    
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwDocuWorks::BinaryInterface::~BinaryInterface()
{
}

#endif
