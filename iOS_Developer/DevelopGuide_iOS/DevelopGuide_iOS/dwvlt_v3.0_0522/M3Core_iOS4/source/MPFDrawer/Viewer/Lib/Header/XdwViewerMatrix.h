/** 
 * @file  XdwViewerMatrix.h
 * @brief XdwViewerMatrixクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwViewerMatrix.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_VIEWER_MATRIX_H_
#define _XDW_VIEWER_MATRIX_H_

/* 親クラスのためのIncludeファイル */
#include "XdwMatrix.h"

/* 依存するクラスの宣言 */
class XdwPoint;

/**
 * @brief CTM作成時に単発の一次変換行列を作成する
 */
class XdwViewerMatrix : public XdwMatrix
{
public:

    /********************************************/
    /* ネストクラス */

    /*! 座標の掛け算を行う関数オブジェクト */
    class Multiplication{
    public:

        /********************************************/
        /* メソッド */
        
        /**
         * @brief デフォルトコンストラクタ
         */
        Multiplication();
        
        /**
         * @brief デストラクタ
         */
        virtual ~Multiplication();
        
        /**
         * @brief CTMのセット
         *
         * @param CTM
         */
        virtual void Set(XdwMatrix ctm);

        /**
         * @brief 関数オブジェクト本体
         *
         * @param a 座標管理クラス
         */
        virtual void operator()(XdwPoint& a);

    protected:

        /********************************************/
        /* 集約 */
        
        /*! 変換行列 */
        XdwMatrix fCTM;
        
    };
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwViewerMatrix();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwViewerMatrix();

    /**
     * @brief 正則行列にする
     */
    virtual void Initialize();
    
    /**
     * @brief 回転行列を作成する
     *
     * @param angle 回転角度
     */
    virtual void Rotate(long angle);

    /**
     * @brief 拡縮行列を作成する
     *
     * @param scale_x x軸方向の拡縮率
     * @param scale_y y軸方向の拡縮率
     */
    virtual void Scale(double scale_x, double scale_y);
    
    /**
     * @brief オフセット行列を作成する
     *
     * @param x x軸方向のオフセット
     * @param y y軸方向のオフセット
     */
    virtual void Offset(double x, double y);
    
    /**
     * @brief 指定された角度のcos値を取得する
     *
     * @param angle 角度(0,90,180,270度のみ)
     *
     * @return cos値
     */
    static double Cos(long angle);

    /**
     * @brief 指定された角度のsin値を取得する
     *
     * @param angle 角度(0,90,180,270度のみ)
     *
     * @return sin値
     */
    static double Sin(long angle);
    
};

#endif
