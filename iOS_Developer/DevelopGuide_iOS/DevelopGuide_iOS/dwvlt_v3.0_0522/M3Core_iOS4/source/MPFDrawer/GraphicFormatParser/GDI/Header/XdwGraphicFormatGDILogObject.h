/**
 * @file  XdwGraphicFormatGDILogObject.h
 * @brief XdwGraphicFormat::GDI::LogObjectクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDILogObject.h,v 1.4 2009/12/22 08:10:55 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_LOG_OBJECT_H_
#define _XDW_GRAPHIC_FORMAT_GDI_LOG_OBJECT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/**
 * @brief GDIで定義されているLOGXXX構造体を読み込む抽象クラス
 */
class XdwGraphicFormat::GDI::LogObject
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LogObject();

    /**
     * @brief デストラクタ
     */
    virtual ~LogObject();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwGraphicFormat::GDI::ReadMode mode);
    
    /**
     * @brief LOGXXX構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read() = 0;
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータにアクセスするインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;

    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! 読み込み方法 */
    XdwGraphicFormat::GDI::ReadMode fMode;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスの初期化
     *
     * 継承クラスで初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
    /**
     * @brief 指定された読み込みモードで読み込む
     *
     * @param data 読み込みデータの戻り値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read(long& data);

    /**
     * @brief 指定された読み込みモードで読み飛ばす
     *
     * @param count 読み飛ばしの個数
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Pass(long count = 1);
};

#endif
