/** 
 * @file  XdwDataObjectFilterOKD.h
 * @brief XdwDataObject::Filter::OKDクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectFilterOKD.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_FILTER_OKD_H_
#define _XDW_DATA_OBJECT_FILTER_OKD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDataObjectFilter.h"

/* 親クラスのIncludeファイル */
#include "XdwOkdCommon.h"
#include "XdwDataObjectFilterInterface.h"

/**
 * @brief OKD圧縮されていることを気にすることなく、バイナリデータに対してアクセスするための実装クラス
 *
 * 基本的には現在位置のバッファサイズより前に移動すると、<br>
 * データ先頭から伸張しなおすため、速度は遅くなる
 */
class XdwDataObject::Filter::OKD : public XdwOkdCommon, public XdwDataObject::Filter::Interface
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     *
     * @param src 圧縮データが格納されているXdwDataObject::Commonのインスタンス
     * @param src_offset 圧縮データまでのデータ先頭からのオフセット
     * @param src_size 圧縮データのサイズ
     * @param dst_size 伸張データのサイズ
     * @param delete_flag 圧縮データのサイズの削除の有無
     */
    OKD(XdwDataObject::Common* src, long src_offset, long src_size, long dst_size, bool delete_flag);
    
    /**
     * @brief デストラクタ
     */
    virtual ~OKD();

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
     * @brief 複製可能かの確認
     *
     * @retval true 可能
     * @retval false 不可能
     */
    virtual bool IsClonable();
    
    /**
     * @brief 自身の複製を作成する
     *
     * @return 現在の状態をコピーしたXdwDataObject::Filter::Interfaceのインスタンス
     */
    virtual XdwDataObject::Filter::Interface* Clone();

    /**
     * @brief 複製作成に必要なサイズの取得
     *
     * 伸張に必要なサイズと一致する
     *
     * @return 複製作成に必要なサイズ
     */
    virtual long GetCloneSize();
    
protected:
    
    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! 削除フラグ */
    bool fDeleteFlag;
    
    /*! 伸張データを格納するバッファ */
    unsigned char* fBuffer;
    /*! 現在位置のバッファポインタ */
    unsigned char* fCurrentPointer;
    /*! 伸張位置のバッファポインタ */
    unsigned char* fDecodePointer;
    /*! バッファ終端位置のポインタ */
    unsigned char* fEndPointer;
    
    /*! 伸張データのサイズ */
    long fDstSize;
    /*! 伸張データの現在位置 */
    long fDstOffset;
    /*! 伸張データの伸張位置 */
    long fDecodeOffset;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 1文字 or 1一致分だけ伸張して、伸張位置を更新する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Decode();
    
    /**
     * @brief オフセット分移動したポインタの取得
     *
     * バッファ領域を常に確認して、移動させる
     *
     * @param pointer 参照するポインタ
     * @param offset 移動量
     *
     * @return バッファ領域内のポインタ
     */
    virtual unsigned char* OffsetPointer(unsigned char* pointer, long offset = 1);
};

#endif
