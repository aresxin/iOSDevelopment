/**
 * @file  XdwGraphicFormatGDIRectangle.h
 * @brief XdwGraphicFormat::GDI::Rectangleクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIRectangle.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_RECTANGLE_H_
#define _XDW_GRAPHIC_FORMAT_GDI_RECTANGLE_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "ImagerBridge/BridgeIF/XdwShape.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"

/**
 * @brief GDIで定義されているRECTANGLE,RECTANGLEL,RECTANGLES構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::Rectangle : public XdwRectangle
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Rectangle();

    /**
     * @brief デストラクタ
     */
    virtual ~Rectangle();

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
     * @brief 座標値を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
    /**
     * @brief 指定された読み込み方法での読み込みByte数を取得する
     *
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     *
     * @return 指定された読み込み方法での読み込みByte数
     */
    static long GetBytes(XdwGraphicFormat::GDI::ReadMode mode);
    
    /**
     * @brief Point + Size = Rectangle
     *
     * @param point 左上隅
     * @param size サイズ
     *
     * @return Rectangleのインスタンス
     */
    friend XdwGraphicFormat::GDI::Rectangle operator + (XdwGraphicFormat::GDI::Point& point, XdwGraphicFormat::GDI::Size& size);
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 座標を読み込むクラス */
    XdwGraphicFormat::GDI::Point fPoint;

    /********************************************/
    /* 属性 */
    
    /*! 読み込み方法 */
    XdwGraphicFormat::GDI::ReadMode fMode;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 順方向での読み込み
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadForward();
    
    /**
     * @brief 逆順での読み込み
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ReadInvert();
    
};

#endif
