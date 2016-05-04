/**
 * @file  XdwGraphicFormatEMFEMRRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::Recordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * @date 2002-12-25 分割描画対応 Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief EMRを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Record();

    /**
     * @brief デストラクタ
     */
    virtual ~Record();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary EMFが格納されているバイナリデータ管理インターフェースのインスタンス
     * @param bridge Imagerへアクセスするためのインターフェースのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge);
    
    /**
     * @brief 属性をセットする
     *
     * @param type 識別子
     * @param size 構造体のサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(long type, long size);
    
    /**
     * @brief EMR構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
    /**
     * @brief 各種EMR構造体を読み飛ばす
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Pass();
    
    /**
     * @brief 各種EMR構造体をパースする
     *
     * 各EMR構造体にあわせて、必要な処理を行う
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
     /**
     * @brief EMF中のラスター描画に関するレコードをパースする(LEG MODE)
     *
     * EMF中のラスター描画に関するレコードを読み込んで、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg(long leg_count = 1);
    
    /**
     * @brief 識別子を取得する
     *
     * @return EMRの識別子
     */
    virtual long GetType();
    
    /**
     * @brief サイズを取得する
     *
     * @return 各種EMR構造体のサイズ
     */
    virtual long GetSize();

    /**
     * @brief パースするバイナリデータのサイズを取得する
     *
     * @return 各種EMR構造体のサイズ - EMR構造体のサイズ
     */
    virtual long GetParseSize();
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータ管理インターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    /*! Imagerへアクセスするためのインターフェース */
    XdwBridgeDrawIF* fBridge;

    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! 識別子 */
    long fType;
    /*! サイズ */
    long fSize;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 継承クラスは本メソッドを実行するればよい
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
