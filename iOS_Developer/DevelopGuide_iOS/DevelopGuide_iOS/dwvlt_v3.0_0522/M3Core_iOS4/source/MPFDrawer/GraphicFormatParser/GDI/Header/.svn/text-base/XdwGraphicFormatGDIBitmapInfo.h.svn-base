/**
 * @file  XdwGraphicFormatGDIBitmapInfo.h
 * @brief XdwGraphicFormat::GDI::BitmapInfoクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIBitmapInfo.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_BITMAP_INFO_H_
#define _XDW_GRAPHIC_FORMAT_GDI_BITMAP_INFO_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIBitmapInfoHeader.h"
#include "XdwGraphicFormatGDIPalette.h"

/* 依存するクラスの宣言 */
class XdwRasterImageAttribute;

/**
 * @brief BITMAPINFO構造体を管理するクラス
 */
class XdwGraphicFormat::GDI::BitmapInfo
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    BitmapInfo();

    /**
     * @brief デストラクタ
     */
    virtual ~BitmapInfo();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary BITMAPINFO構造体が格納されているバイナリデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary);

    /**
     * @brief BITMAPINFO構造体の読み込み
     *
     * @param size BITMAPINFO構造体のサイズ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(long size = -1);

    /**
     * @brief BITMAPINFO構造体の情報をラスター属性にセットする
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetAttribute(XdwRasterImageAttribute* attribute);
    
protected:

    /********************************************/
    /* 集約 */

    /*! BITMAPINFOHEADER構造体を管理するクラス */
    XdwGraphicFormat::GDI::BitmapInfoHeader fHeader;
    /*! パレットを管理するクラス */
    XdwGraphicFormat::GDI::Palette fPalette;
    
    /********************************************/
    /* 関連 */

    /*! BITMAPINFO構造体が格納されているバイナリデータのインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    
};

#endif
