/**
 * @file  XdwGraphicFormatGDIColorRef.h
 * @brief XdwGraphicFormat::GDI::ColorRefクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIColorRef.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_COLOR_REF_H_
#define _XDW_GRAPHIC_FORMAT_GDI_COLOR_REF_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 使用する型のIncludeファイル */
#include "XdwBridgeCommon.h"
#include "XdwColor.h"

/**
 * @brief GDIで定義されているCOLORREF型を読み込むクラス
 */
class XdwGraphicFormat::GDI::ColorRef
{
public:

    /********************************************/
    /* 列挙型 */
    
    /*! フラグの規定 */
    enum ColorFlag{
        /*! TrueColor */
        TRUE_COLOR = 0,
        /*! パレット参照ID */
        PALETTE_INDEX = 1,
        /*! パレットで規定された色に最も近い色を指定 */
        PALLETE_RGB = 2
    };
    
    /*! 色を規定するタイプ */
    enum ColorType{
        /*! COLORREF型 */
        COLOR_REF,
        /*! PALETTEENTRY構造体 */
        PALETTE_ENTRY,
        /*! RGBQUAD構造体 */
        RGB_QUAD,
        /*! 16Bit/32Bitカラーのマスク */
        COLOR_MASK,
        /*! RGBTRIPEL構造体 */
        RGB_TRIPLE
    };
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ColorRef();

    /**
     * @brief デストラクタ
     */
    virtual ~ColorRef();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param type 色を規定するタイプ<br>
     *             XdwGraphicFormat::GDI::ColorRef::ColorType参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwGraphicFormat::GDI::ColorRef::ColorType type = XdwGraphicFormat::GDI::ColorRef::COLOR_REF);
    
    /**
     * @brief 色を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
    /**
     * @brief 色の取得
     *
     * @return XdwBridgeDrawIFで規定されている色
     */
    virtual XdwTypeUInt32 GetColor();
    
    /**
     * @brief 色空間の取得
     *
     * @return XdwColorSpaceID参照
     */
    virtual XdwColorSpaceID GetColorSpace();
    
    /**
     * @brief 構成する型のByte数の取得
     *
     * @param mode 色に関する型の指定
     *
     * @return 構成する型のByte数
     */
    static long GetBytes(XdwGraphicFormat::GDI::ColorRef::ColorType mode = XdwGraphicFormat::GDI::ColorRef::COLOR_REF);
    
protected:

    /********************************************/
    /* 列挙型 */
    
    /*! 色値のシフト量 */
    enum ColorShift{
        /*! Redのシフト量 */
        RED_SHIFT = 16,
        /*! Greenのシフト量 */
        GREEN_SHIFT = 8,
        /*! Blueのシフト量 */
        BLUE_SHIFT = 0,
    };
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータ管理インターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    
    /********************************************/
    /* 属性 */
    
    /*! 色 */
    XdwTypeUInt32 fColor;
    /*! 色空間 */
    XdwColorSpaceID fColorSpace;
    /*! 色を規定する型の種類 */
    XdwGraphicFormat::GDI::ColorRef::ColorType fType;

    /********************************************/
    /* メソッド */

    /**
     * @brief COLORREF型を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadColorRef();

    /**
     * @brief PALETTEENTRY構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadPaletteEntry();
    
    /**
     * @brief RGBQUAD構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadRGBQuad();

    /**
     * @brief 16Bit/32Bitカラーのマスクを読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadColorMask();

    /**
     * @brief RGBTRIPLE構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadRGBTriple();
    
};

#endif
