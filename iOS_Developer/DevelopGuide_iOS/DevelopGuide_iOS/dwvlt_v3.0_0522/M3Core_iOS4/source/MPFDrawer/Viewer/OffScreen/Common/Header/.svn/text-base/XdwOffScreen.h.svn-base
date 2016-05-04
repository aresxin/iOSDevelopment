/** 
 * @file  XdwOffScreen.h
 * @brief XdwOffScreenクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreen.h,v 1.5 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_H_
#define _XDW_OFF_SCREEN_H_

/* 集約するクラスのためのIncludeファイル */
#include "ImagerBridge/BridgeIF/XdwPoint.h"

/* 列挙型のためのIncludeファイル */
#include "System/SystemIF/XdwError.h"

/**
 * @brief オフスクリーンを管理するための抽象クラス
 *
 * 各プラットフォーム毎に異なるオフスクリーンを共通化して管理するためのインターフェースを規定する<br>
 * 指定されるサイズや、紙領域はあくまで回転後のサイズであり、クライアントは考慮しなければならない
 *   2009/7/17 ページ枠描画、×描画、領域反転、SetActiveメソッド、デフォルト色列挙型を削除
 *             ページ枠描画はViewer Lightアプリ側で実装する
 */
class XdwOffScreen
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwOffScreen();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreen();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize() = 0;
    
    /**
     * @brief オフスクリーンを作成する
     *
     * @param width 横幅
     * @param height 縦幅
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Create(long width, long height) = 0;
    
    /**
     * @brief オフスクリーンが作成されているかの判定
     *
     * @retval true 作成されている
     * @retval false 作成されていない
     */
    virtual bool IsCreated() = 0;
    
    /**
     * @brief オフスクリーンを閉じる
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Close() = 0;
    
    /**
     * @brief オフスクリーンをHostBased Decomposerに関連でける
     *
     * @param imager HostBased Imagerのハンドル
     *
     * @return 各プラットフォームによるIMG_StartPageの戻り値
     */
    virtual int SetToDecomposer(void* imager) = 0;
    
    /**
     * @brief オフスクリーンをコピーする
     *
     * オフスクリーンのバッファを含めて、全ての状態をコピーする
     *
     * @param dst コピー先のオフスクリーン
     * 
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Copy(XdwOffScreen* dst) = 0;
    
    /**
     * @brief 現在のオフスクリーンを回転させる
     *
     * @param 角度
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Rotate(long angle) = 0;
    
    /**
     * @brief 横幅を取得する
     *
     * @return 横幅(pixel値)
     */
    virtual long GetWidth();
    
    /**
     * @brief 縦幅を取得する
     *
     * @return 縦幅(pixel値)
     */
    virtual long GetHeight();
    
protected:
    
    /********************************************/
    /* 属性 */

    /*! 管理するオフスクリーンの横幅 */
    long fWidth;
    /*! 管理するオフスクリーンの縦幅 */
    long fHeight;
    
};

#endif
