/**
 * @file  XdwGraphicFormatGDIRoundRect.h
 * @brief XdwGraphicFormat::GDI::RoundRectクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIRoundRect.h,v 1.4 2009/12/22 08:10:54 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_ROUND_RECT_H_
#define _XDW_GRAPHIC_FORMAT_GDI_ROUND_RECT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwShape.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"

/**
 * @brief GDIで定義されている円弧を読み込むクラス
 */
class XdwGraphicFormat::GDI::RoundRect : public XdwRoundRect
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RoundRect();

    /**
     * @brief デストラクタ
     */
    virtual ~RoundRect();

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
