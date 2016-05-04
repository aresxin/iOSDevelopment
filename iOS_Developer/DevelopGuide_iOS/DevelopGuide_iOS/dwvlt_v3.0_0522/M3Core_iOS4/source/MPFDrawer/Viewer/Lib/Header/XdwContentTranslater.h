/** 
 * @file  XdwContentTranslater.h
 * @brief XdwContentTranslaterクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwContentTranslater.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_CONTENT_TRANSLATER_H_
#define _XDW_CONTENT_TRANSLATER_H_

/* 依存するパッケージのIncludeファイル */
#include "XdwDocuWorks.h"
#include "XdwGraphicFormat.h"

/* 集約するクラスのIncludeファイル */
#include "XdwMatrix.h"
#include "XdwShape.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwError.h"
#include "XdwDocuWorksPageInfo.h"

/**
 * @brief CTM作成時に単発の一次変換行列を作成する
 */
class XdwContentTranslater
{
public:

    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwContentTranslater();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwContentTranslater();

    /**
     * @brief インスタンスを初期化する
     *
     * @param dw_to_dev DW座標系からデバイス座標系への変換行列
     */
    virtual XdwErrorCode Initialize(XdwMatrix dw_to_dev);
    
    /**
     * @brief BasicコンテントのCTMやバウンディングボックスをセットする
     *
     * @param dw_info DocuWorksファイルのコンテント情報を取得するためのインターフェース
     * @param graphic_info グラフィックデータの情報を取得するためのインターフェース
     * @param mode XdwDocuWorks::PageInfo::ContentMode参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(XdwDocuWorks::ContentManager* dw_info, XdwGraphicFormat::Info* graphic_info, XdwDocuWorks::PageInfo::ContentMode mode);
    
    /**
     * @brief コンテントの座標系のCTMを取得する
     *
     * @param CTM
     */
    virtual XdwMatrix GetCTM();
    
    /**
     * @brief コンテントのバウンディングボックスを取得する
     *
     * @param コンテントのバウンディングボックス
     */
    virtual XdwRectangle GetBoundingBox();
    
protected:

    /********************************************/
    /* 集約 */

    /*! グラフィックデータの座標系からデバイス座標系への変換行列 */
    XdwMatrix fCTM;
    /*! コンテントのバウンディングボックス */
    XdwRectangle fBoundingBox;
    
    /********************************************/
    /* 関連 */
    
    /*! DocuWorks座標系からデバイス座標系への変換行列 */
    XdwMatrix fDWtoDev;
    
    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;

    /********************************************/
    /* メソッド */

};

#endif
