/** 
 * @file  XdwScaleControler.h
 * @brief XdwScaleControlerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwScaleControler.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_SCALE_CONTROLER_H__
#define _XDW_SCALE_CONTROLER_H__

/* 依存するパッケージのIncludeファイル */
#include "XdwDocuWorks.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwError.h"
#include "XdwOffScreenControlerForViewerLight.h"

/**
 * @brief 拡縮率をdpi値に変換するクラス
 */
class XdwScaleControler
{
public:

    /********************************************/
    /* 列挙型 */
    
    /*! 拡縮率の限界値 */
    enum LimitScale{
        MIN_SCALE_LIMIT = 10,
        MAX_SCALE_LIMIT = 1600
    };

    /*! 表示デバイスデフォルト解像度 */
    enum {
        DEVICE_DPI = 75
    };

    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwScaleControler();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwScaleControler();

    /**
     * @brief インスタンスを初期化する
     *
     * @param scale 拡縮率
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(long scale = 100);
    
    /**
     * @brief 拡縮率を元に拡縮率とdpi値をセットする
     *
     * @param scale 拡縮率
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetScale(long scale);

    /**
     * @brief dpi値を元に拡縮率とdpi値をセットする
     *
     * @param dpi dpi値
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetDpi(long dpi);
    
    /**
     * @brief ページ横幅を基準にセット
     *
     * @param page ページ情報のインターフェース
     * @param angle 回転角度
     * @param width 描画領域の横幅
     * @param mode アノテーション表示/非表示状態
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetPageWidth(XdwDocuWorks::PageInfo* page, long angle, long width,
            XdwOffScreenControlerForViewerLight::OffScreenMode mode =
            XdwOffScreenControlerForViewerLight::ANNOTATION_MODE);

    /**
     * @brief ページ縦幅を基準にセット
     *
     * @param page ページ情報のインターフェース
     * @param angle 回転角度
     * @param height 描画領域の縦幅
     * @param mode アノテーション表示/非表示状態
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetPageHeight(XdwDocuWorks::PageInfo* page, long angle, long height,
            XdwOffScreenControlerForViewerLight::OffScreenMode mode =
            XdwOffScreenControlerForViewerLight::ANNOTATION_MODE);
    
    /**
     * @brief ページ全体を基準にセット
     *
     * @param page ページ情報のインターフェース
     * @param angle 回転角度
     * @param width 描画領域の横幅
     * @param height 描画領域の縦幅
     * @param mode アノテーション表示/非表示状態
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetPageAll(XdwDocuWorks::PageInfo* page, long angle, long width,
            long height, XdwOffScreenControlerForViewerLight::OffScreenMode mode =
            XdwOffScreenControlerForViewerLight::ANNOTATION_MODE);
    
    /**
     * @brief 拡縮率を増加させる（Linux Zaurus Viewerでは使っていない）
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Increment();

    /**
     * @brief 拡縮率を減少させる（Linux Zaurus Viewerでは使っていない）
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Decrement();
    
    /**
     * @brief 拡縮率を取得する
     *
     * @param 拡縮率
     */
    virtual long GetScale();
    
    /**
     * @brief dpi値を取得する
     *
     * @param dpi値
     */
    virtual long GetDpi();
    
protected:
    
    /********************************************/
    /* 属性 */
    
    /*! 拡縮率 */
    long fScale;
    /*! dpi値 */
    long fDpi;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief ページの横幅を取得する
     *
     * @param page ページ情報のインターフェース
     * @param angle 回転角度
     * @param mode アノテーション表示/非表示状態
     *
     * @return ページ横幅(mm単位)
     */
    virtual long GetPageWidth(XdwDocuWorks::PageInfo* page, long angle,
            XdwOffScreenControlerForViewerLight::OffScreenMode mode);

    /**
     * @brief ページの縦幅を取得する
     *
     * @param page ページ情報のインターフェース
     * @param angle 回転角度
     * @param mode アノテーション表示/非表示状態
     *
     * @return ページ横幅(mm単位)
     */
    virtual long GetPageHeight(XdwDocuWorks::PageInfo* page, long angle,
            XdwOffScreenControlerForViewerLight::OffScreenMode mode);
    
    /**
     * @brief 各属性のセット
     *
     * @param paper 紙領域のサイズ
     * @param window ウィンドウ領域のサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetParameter(long paper, long window);
    
};

#endif
