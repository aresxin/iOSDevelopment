/** 
 * @file  XdwDataObjectBaseStorage.h
 * @brief XdwDataObject::Base::Storage抽象クラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBaseStorage.h,v 1.5 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_STORAGE_H_
#define _XDW_DATA_OBJECT_BASE_STORAGE_H_

/* パッケージを記述するためのIncludeファイル */
#include "DataObject/Include/XdwDataObject.h"

/* 親クラスを定義したIncludeファイル */
#include "XdwDataObjectBaseBuffer.h"

/* 関連するインターフェースの宣言 */
class XdwFileIO;

/**
 * @brief ストレージを用いてバイナリデータにアクセスする抽象クラス
 *
 * バッファやストレージを扱うための属性や、バッファとストレージを関連付けるメソッドなどを提供する
 */
class XdwDataObject::Base::Storage : public XdwDataObject::Base::Buffer
{
public:

    /********************************************/
    /* 列挙型 */
    enum{
        /**
         * @brief バッファに使用する最大サイズ
         *
         * プロダクト毎に切り替える
         */
        BUFFER_MAX_SIZE = 524288
    };
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デストラクタ
     */
    virtual ~Storage();
    
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
     * @brief 現在バッファ上にあるバイナリデータをいったん、ストレージに全て格納する
     *
     * その後、新たにバッファを取得し直す
     *
     * @param buffer_size 新たに取得するバッファのサイズ<br>
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Purge(long buffer_size);
    
    /**
     * @brief データサイズを取得する
     *
     * @return データサイズのByte数
     */
    virtual long GetDataSize();
    
protected:
    
    /********************************************/
    /* 関連 */

    /*! ファイル入出力を提供するインターフェース */
    XdwFileIO* fFileIO;
    
    /********************************************/
    /* 属性 */

    /*! ファイルサイズ */
    long fFileSize;
    /*! 現在位置のファイル先頭からのオフセット */
    long fCurrentFileOffset;
    /*! バッファ先頭位置のファイル先頭からのオフセット */
    long fBufferOffsetOnFile;
    /*! ファイルハンドル */
    void* fFileHandle;
    /*! ファイル名 */
    void* fFileName;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief バッファの初期化
     *
     * 確保するバッファのByte数を決定する<br>
     * 決定したByte数で、ついでにバッファも確保して、
     * 全ての位置をファイルの先頭に合わせる<br>
     * ファイル内のデータはここでは読み込まない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode InitializeBuffer();

    /**
     * @brief バッファへの書き込むのチェック
     *
     * 書き込んでいれば、バッファ上のデータを、ファイルに更新する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode CheckBufferWrited() = 0;

    /**
     * @brief 現在のファイルサイズの取得
     *
     * @return 現在のファイルサイズ<br>
     *         Byte単位
     */
    virtual long GetFileSize() = 0;
    
    /**
     * @brief バッファの更新
     *
     * 書き込みフラグをチェックしてから、
     * 現在のファイルの位置を先頭にして、
     * バッファの更新を行う
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode UpdateBuffer();

    /**
     * @brief Lockされているかのチェック
     *
     * @return true Lockされている
     * @return false Lockされていない
     */
    virtual bool CheckLocked() = 0;

    /**
     * @brief バッファをストレージに避難する
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SaveBuffer() = 0;

};

#endif
