/** 
 * @file  XdwDataObjectBaseMemory.h
 * @brief XdwDataObject::Base::Memoryクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBaseMemory.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_MEMORY_H_
#define _XDW_DATA_OBJECT_BASE_MEMORY_H_

/* パッケージを記述するためのIncludeファイル */
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 親クラスを定義したIncludeファイル */
#include "XdwDataObjectBaseBuffer.h"

/**
 * @brief メモリ上に存在するバイナリデータにアクセスするクラス
 *
 * XdwDataObject::Binaryの実装クラス
 */
class XdwDataObject::Base::Memory : public XdwDataObject::Base::Buffer
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     *
     * 初期化関数を呼ばなければ、使用できない
     *
     * @param data_size データを記憶させるのに、必要とするサイズ<br>
     *                  Byte単位
     */
    Memory(long data_size);

    /**
     * @brief デストラクタ
     *
     * 取得したバッファを開放する
     */
    virtual ~Memory();

    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize();

    /**
     * @brief 現在位置のバイナリデータにアクセスする
     *
     * アクセスしても、現在位置は移動しない
     *
     * @param desired_size 読み込む際に必要とするバイナリデータのbyte数
     * @param feasible_size XdwDataObjectがアクセスを許可するポインタのbyte数<br>
     *                      0ならバイナリデータの終端、0より上なら正常、0以下ならエラー
     *
     * @return メモリ上のポインタ<br>
     * @return エラー時はNULLコード。
     */
    virtual unsigned char* GetCurrentPointer(long desired_size, long& feasible_size);

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
     * @brief 現在位置を移動する
     *
     * 現在位置の移動は、本メソッドを介してしか、行えない
     *
     * @param offset 移動するオフセット
     * @param mode どの位置から開始するかの指定<br>
     *             XdwDataObject::Binary::SeekModeを参照
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Seek(long offset, XdwDataObject::Binary::SeekMode mode);

    /**
     * @brief データ先頭位置からの現在位置をbyte数で取得する
     *
     * @return データ先頭位置からのbyte数
     */
    virtual long Tell();

    /**
     * @brief データサイズを取得する
     *
     * @return データサイズのByte数
     */
    virtual long GetDataSize();
    
    /**
     * @brief 現在のバイナリデータを扱う際に、ストレージは使用しない
     *
     * 初期化する前に本メソッドを使用することで、ストレージには一切アクセスしない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Lock();

    /**
     * @brief 現在バッファ上にあるバイナリデータをいったん、ストレージに全て格納する
     *
     * その後、新たにバッファを取得し直す
     *
     * @param buffer_size 新たに取得するバッファのサイズ<br>
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Purge(long buffer_size);

protected:
    
};

#endif
