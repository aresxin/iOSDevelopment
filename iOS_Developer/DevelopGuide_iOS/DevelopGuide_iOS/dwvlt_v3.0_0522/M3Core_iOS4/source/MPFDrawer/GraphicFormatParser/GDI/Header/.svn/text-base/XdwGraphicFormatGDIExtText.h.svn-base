/**
 * @file  XdwGraphicFormatGDIExtText.h
 * @brief XdwGraphicFormat::GDI::ExtTextクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIExtText.h,v 1.4 2009/12/22 08:10:55 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_EXT_TEXT_OBJECT_H_
#define _XDW_GRAPHIC_FORMAT_GDI_EXT_TEXT_OBJECT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"
#include "XdwFont.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief GDIで定義されている拡張TextOut命令を読み込むクラス
 */
class XdwGraphicFormat::GDI::ExtText
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExtText();

    /**
     * @brief デストラクタ
     */
    virtual ~ExtText();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param bridge Imagerにアクセスするためのインターフェース
     * @param read_mode XdwGraphicFormat::GDI::ReadMode参照
     * @param code_mode XdwGraphicFormat::GDI::CharacterCodeMode参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge, XdwGraphicFormat::GDI::ReadMode read_mode, XdwGraphicFormat::GDI::CharacterCodeMode code_mode);
    
    /**
     * @brief GDIで定義されている拡張TextOut命令をパースする
     *
     * @param record_position 描画レコード開始位置
     * @param record_bytes 描画レコードのByte数
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse(long record_position, long record_bytes);
    
protected:

    /********************************************/
    /* 列挙型 */
    
    /*! テキスト描画時のオプション */
    enum OptionMode{
        /*! クリッピング */
        CLIPE_MODE = 0x00000004,
        /*! 背景色の塗りつぶし */
        OPAQUE_MODE = 0x00000002
    };
    
    /********************************************/
    /* 集約 */
    
    /*! 座標を管理するクラス */
    XdwGraphicFormat::GDI::Point fPoint;
    /*! テキスト情報を受け渡すためのクラス */
    XdwCodeText fText;
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータにアクセスするインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    /*! Imagerにアクセスするためのインターフェース */
    XdwBridgeDrawIF* fBridge;

    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! 読み込み方法 */
    XdwGraphicFormat::GDI::ReadMode fReadMode;
    /*! テキストの文字コード */
    XdwGraphicFormat::GDI::CharacterCodeMode fCodeMode;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 集約や属性を初期化する
     */
    virtual void Clear();
    
    /**
     * @brief 16Bitデータの拡張テキスト描画命令を読み込む
     *
     * @param record_position 描画レコード開始位置
     * @param record_bytes 描画レコードのByte数
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read16(long record_position, long record_bytes);

    /**
     * @brief 32Bitデータの拡張テキスト描画命令を読み込む
     *
     * @param record_position 描画レコード開始位置
     * @param record_bytes 描画レコードのByte数
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read32(long record_position, long record_bytes);
    
    /**
     * @brief 指定された文字コードのデータを読み込む
     *
     * @param count 文字列の長さ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadString(long count);
    
    /**
     * @brief ピッチデータを読み込む
     *
     * @param count 文字列の長さ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadPitch(long count);

    /**
     * @brief 指定された読み込みモードで読み込む
     *
     * @param data 読み込みデータの戻り値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read(long& data);
};

#endif
