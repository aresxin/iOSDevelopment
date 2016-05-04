/**
 * @file  XdwGraphicFormatGDIReadPointArray.h
 * @brief XdwGraphicFormat::GDI::ReadPointArrayクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIReadPointArray.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_READ_POINT_ARRAY_H_
#define _XDW_GRAPHIC_FORMAT_GDI_READ_POINT_ARRAY_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 集約するクラスのIncludeファイル */
#include "XdwPoint.h"

/**
 * @brief GDIで定義されているPOINT,POINTL,POINTS構造体の配列を読み込む関数オブジェクト
 */
class XdwGraphicFormat::GDI::ReadPointArray
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ReadPointArray();

    /**
     * @brief デストラクタ
     */
    virtual ~ReadPointArray();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     * @param start_point 初期座標
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwGraphicFormat::GDI::ReadMode mode, XdwPoint start_point);
    
    /**
     * @brief 関数オブジェクト本体
     *
     * @return XdwErrorCode参照
     */
    XdwErrorCode operator()(XdwPoint& point);
    
protected:
    
    /********************************************/
    /* 集約 */

    /*! 現在の座標 */
    XdwPoint fCurrentPoint;
    
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
     * @param point セットする座標値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read32(XdwPoint& point);
    
    /**
     * @brief 16Bitでの読み込み
     *
     * @param point セットする座標値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read16(XdwPoint& point);
    
    /**
     * @brief 逆順の16Bitでの読み込み
     *
     * @param point セットする座標値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read16Invert(XdwPoint& point);

    /**
     * @brief 8Bit差分での読み込み
     *
     * @param point セットする座標値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read8Dif(XdwPoint& point);

    /**
     * @brief 4Bit差分での読み込み
     *
     * @param point セットする座標値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read4Dif(XdwPoint& point);
    
};

#endif
