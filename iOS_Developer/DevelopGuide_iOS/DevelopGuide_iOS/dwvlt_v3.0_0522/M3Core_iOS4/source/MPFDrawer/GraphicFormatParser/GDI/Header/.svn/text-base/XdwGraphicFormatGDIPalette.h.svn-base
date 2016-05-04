/**
 * @file  XdwGraphicFormatGDIPalette.h
 * @brief XdwGraphicFormat::GDI::Paletteクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIPalette.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_PALETTE_H_
#define _XDW_GRAPHIC_FORMAT_GDI_PALETTE_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwColor.h"

/* 依存するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIColorRef.h"

/**
 * @brief GDIで各々定義されているパレットを読み込むクラス
 */
class XdwGraphicFormat::GDI::Palette : public XdwColorPalette
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Palette();

    /**
     * @brief デストラクタ
     */
    virtual ~Palette();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param type 読み込む色の型<br>
     *             XdwGraphicFormat::GDI::ColorRef::ColorType参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwGraphicFormat::GDI::ColorRef::ColorType type = XdwGraphicFormat::GDI::ColorRef::PALETTE_ENTRY);
    
    /**
     * @brief 色数をセットする
     *
     * @param セットする色数
     *
     * @return XdwErrorCode
     */
    virtual XdwErrorCode Set(long count);
    
    /**
     * @brief 座標値を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータ管理インターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;

    /********************************************/
    /* 属性 */
    
    /*! 色を規定する型の種類 */
    XdwGraphicFormat::GDI::ColorRef::ColorType fType;
    
};

#endif
