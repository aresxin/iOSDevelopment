/** 
 * @file  XdwDataObjectBinary.h
 * @brief XdwDataObject::Binaryインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBinary.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BINARY_H_
#define _XDW_DATA_OBJECT_BINARY_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDataObject.h"

/**
 * @interface XdwDataObject::Binary XdwDataObjectBinary.h
 * @brief 大きなバイナリデータにアクセスする際に用いるインターフェース
 */
class XdwDataObject::Binary
{
public:
    /********************************************/
    /* 列挙型 */

    /*! Seek時の指定 */
    enum SeekMode{
        /*! データ先頭から */
        START,
        /*! データ終端から */
        END,
        /*! 現在位置から */
        CURRENT
    };

    /********************************************/
    /* メソッド */

    /**
     * @brief デストラクタ
     */
    virtual ~Binary() = 0;
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize() = 0;

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
    virtual unsigned char* GetCurrentPointer(long desired_size, long& feasible_size) = 0;

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
    virtual XdwErrorCode Write(void* buffer, long size) = 0;

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
    virtual XdwErrorCode Seek(long offset, XdwDataObject::Binary::SeekMode mode) = 0;

    /**
     * @brief データ先頭位置からの現在位置をbyte数で取得する
     *
     * @return データ先頭位置からのbyte数
     */
    virtual long Tell() = 0;

    /**
     * @brief データサイズを取得する
     *
     * @return データサイズのByte数
     */
    virtual long GetDataSize() = 0;
    
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwDataObject::Binary::~Binary()
{
}

#endif
