/**
 * @file  XdwGraphicFormatGDIPoint.h
 * @brief XdwGraphicFormat::GDI::Pointクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIPoint.h,v 1.4 2009/12/22 08:10:55 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_POINT_H_
#define _XDW_GRAPHIC_FORMAT_GDI_POINT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "ImagerBridge/BridgeIF/XdwPoint.h"

/**
 * @brief GDIで定義されているPOINT,POINTL,POINTS構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::Point : public XdwPoint
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Point();

    /**
     * @brief デストラクタ
     */
    virtual ~Point();

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
     * @brief Point *= Double
     */
    XdwGraphicFormat::GDI::Point& operator *= (double value);
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータ管理インターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;

    /********************************************/
    /* 属性 */
    
    /*! 読み込み方法 */
    XdwGraphicFormat::GDI::ReadMode fMode;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 32Bitでの読み込み
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read32();
    
    /**
     * @brief 16Bitでの読み込み
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read16();
    
    /**
     * @brief 逆順の16Bitでの読み込み
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read16Invert();
    
};

#endif
