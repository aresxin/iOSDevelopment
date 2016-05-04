/**
 * @file  XdwGraphicFormatGDILogFont.h
 * @brief XdwGraphicFormat::GDI::LogFontクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDILogFont.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_LOG_FONT_H_
#define _XDW_GRAPHIC_FORMAT_GDI_LOG_FONT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatGDILogObject.h"

/* 集約するクラスのIncludeファイル */
#include "XdwFont.h"

/**
 * @brief GDIで定義されているLOGFONT構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::LogFont : public XdwGraphicFormat::GDI::LogObject
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LogFont();

    /**
     * @brief デストラクタ
     */
    virtual ~LogFont();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     * @param code XdwGraphicFormat::GDI::CharacterCodeMode参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwGraphicFormat::GDI::ReadMode mode, XdwGraphicFormat::GDI::CharacterCodeMode code);
    
    /**
     * @brief LOGFONT構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();

    /**
     * @brief フォント属性を取得する
     *
     * @return XdwFontInfo参照
     */
    virtual XdwFontInfo& Get() const;

protected:

    /********************************************/
    /* 列挙型 */
    
    enum {
        /*! フォント名の最大文字数 */
        FONT_NAME_COUNT = 32
    };
    
    /********************************************/
    /* 集約 */
    
    /*! Imagerにフォントをセットするためのクラス */
    XdwFontInfo fFont;

    /********************************************/
    /* 属性 */

    /*! 文字コード */
    XdwGraphicFormat::GDI::CharacterCodeMode fCode;

    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスの初期化
     *
     * フォント名を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
