/**
 * @file  XdwDocuWorksAccessCommon.h
 * @brief XdwDocuWorks::Access::Dataクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksAccessCommon.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_BINARY_DATA_H_
#define _XDW_DOCUWORKS_BINARY_DATA_H_

/* パッケージを記述するためのIncludeファイル */
#include "DocuWorksDecoder/Access/Include/XdwDocuWorksAccess.h"

/* 依存するパッケージのIncludeファイル */
#include "DataObject/Include/XdwDataObject.h"

/* インターフェースを規定するためのIncludeファイル */
#include "DocuWorksDecoder/Include/XdwDocuWorksBinaryInterface.h"

/**
 * @brief バイナリデータにアクセスる際に、共通化できる抽象クラス
 *
 * 小さいサイズのデータにしかアクセスさせないなど、ラッピングも行う
 */
class XdwDocuWorks::Access::Common : public XdwDocuWorks::BinaryInterface
{
public:
        
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Common();

    /**
     * @brief デストラクタ
     */
    virtual ~Common();

    /**
     * @brief セットされているXdwDataObject::Commonインターフェースのインスタンスへのアクセスを閉じる
     */
    virtual void Close();
    
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
    virtual XdwErrorCode SetDataObject(XdwDataObject::Common* binary, bool delete_flag, long start_offset, long access_size);
    
    /**
     * @brief  現在セットされているXdwDataObject::Commonインターフェースのインスタンスを取得する
     *
     * @param refine 参照するか、取得するかのフラグ<br>
     *               取得した場合には、インスタンスの管理はクライアント側に移行する
     *
     * @return XdwDataObject::Commonインターフェースのインスタンス
     */
    virtual XdwDataObject::Common* GetDataObject(bool refine = true);
    
    /**
     * @brief アクセス可能なデータサイズを取得する
     *
     * @return アクセス可能なデータサイズ
     */
    virtual long GetDataSize();
    
    /**
     * @brief 現在位置を移動する
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
     * @brief　バッファの現在位置のポインタを取得する
     *
     * @param desired_size 読み込む際に必要とするバイナリデータのbyte数
     * @param feasible_size アクセスを許可するポインタのbyte数<br>
     *                      0ならバイナリデータの終端、0より上なら正常、0以下ならエラー
     * @return バッファの現在位置のポインタ
     */
    virtual unsigned char* GetCurrentPointer(long desired_size, long& feasible_size);

    /**
     * @brief データを書き込む
     *
     * @param buffer 書き込むデータへのポインタ
     * @param size 書き込むデータのサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Write(void* buffer, long size);
    
protected:

    /********************************************/
    /* 集約 */

    /*! XdwDataObject::Commonインターフェース */
    XdwDataObject::Common* fBinary;
    
    /********************************************/
    /* 属性 */

    /*! XdwDataObject::Commonインターフェースのインスタンスの削除フラグ */
    bool fDeleteFlag;
    /*! セットされているかのフラグ */
    bool fSetFlag;
    /*! データの開始位置 */
    long fStartOffset;
    /*! アクセス可能なサイズ(Byte数) */
    long fAccessSize;
    /*! 現在のオフセット */
    long fCurrentOffset;

    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 属性を初期化する
     */
    void InitializeAttribute();
};

#endif
