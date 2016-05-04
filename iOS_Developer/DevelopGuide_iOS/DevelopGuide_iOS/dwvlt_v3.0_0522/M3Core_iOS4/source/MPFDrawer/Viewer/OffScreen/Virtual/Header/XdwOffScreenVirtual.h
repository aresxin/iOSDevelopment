/** 
 * @file  XdwOffScreenVirtual.h
 * @brief XdwOffScreenVirtualクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreenVirtual.h,v 1.4 2009/12/22 08:11:40 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_VIRTUAL_H_
#define _XDW_OFF_SCREEN_VIRTUAL_H_

/* 列挙型のためのIncludeファイル */
#include "XdwError.h"

/* 親クラスの定義のためのIncludeファイル */
#include "XdwOffScreen.h"

/* 関連するクラスの宣言 */
class XdwOffScreenControlerForViewerLightVirtual;

/**
 * @brief 仮想オフスクリーンを管理するための実装クラス
 *
 * XdwOffScreenControlerForViewerVirtualクラスと関連付けをしないと、現在は使用できない
 * OSやWindow環境に依存しない
 * BitBlidを持たない
 */
class XdwOffScreenVirtual : public XdwOffScreen
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief コンストラクタ
     *
     * @param controler DC等を管理するクラス
     */
    XdwOffScreenVirtual(XdwOffScreenControlerForViewerLightVirtual* controler);
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenVirtual();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();

    /**
     * @brief オフスクリーンを作成する
     *
     * @param width 横幅
     * @param height 縦幅
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Create(long width, long height);

    /**
     * @brief オフスクリーンが作成されているかの判定
     *
     * @retval true 作成されている
     * @retval false 作成されていない
     */
    virtual bool IsCreated();
    
    /**
     * @brief 紙領域のウィンドウを描画する
     *
     * @param paper_left はみ出し領域を含めた領域の中の紙領域の左上隅のx座標(原点は左上隅)
     * @param paper_top はみ出し領域を含めた領域の中の紙領域の左上隅のy座標(原点は左上隅)
     * @param paper_right はみ出し領域を含めた領域の中の紙領域の右下隅のx座標(原点は左上隅)
     * @param paper_bottom はみ出し領域を含めた領域の中の紙領域の右下隅のy座標(原点は左上隅)
     * @param lap_x 影領域のx軸方向のオフセット
     * @param lap_y 影領域のy軸方向のオフセット
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode DrawWindow(long paper_left, long paper_top, long paper_right, long paper_bottom, long lap_x, long lap_y);

    /**
     * @brief 描画できない領域を描画する
     *
     * @param left 描画できない領域の左上隅のx座標(原点は左上隅)
     * @param top 描画できない領域の左上隅のy座標(原点は左上隅)
     * @param right 描画できない領域の右下隅のx座標(原点は左上隅)
     * @param bottom 描画できない領域の右下隅のy座標(原点は左上隅)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode DrawError(long left, long top, long right, long bottom);

	/**
     * @brief 描画できない領域を赤の×で描画する（SSTでOLEアノテーションエラーを判別）
     *
     * @param left 描画できない領域の左上隅のx座標(原点は左上隅)
     * @param top 描画できない領域の左上隅のy座標(原点は左上隅)
     * @param right 描画できない領域の右下隅のx座標(原点は左上隅)
     * @param bottom 描画できない領域の右下隅のy座標(原点は左上隅)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode DrawErrorRed(long left, long top, long right, long bottom);

   /**
     * @brief リンクアノテーション領域を描画する
     *
     * @param left リンクアノテーション領域の左上隅のx座標(原点は左上隅)
     * @param top リンクアノテーション領域の左上隅のy座標(原点は左上隅)
     * @param right リンクアノテーション領域の右下隅のx座標(原点は左上隅)
     * @param bottom リンクアノテーション領域の右下隅のy座標(原点は左上隅)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode DrawLink(long left, long top, long right, long bottom);

    /**
     * @brief 指定された領域を反転する
     *
     * @param region 指定された領域(閉じたパス)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode InvertRegion(XdwPointVector region);
    
    /**
     * @brief オフスクリーンを閉じる
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Close();

    /**
     * @brief オフスクリーンをHostBased Decomposerに関連でける
     *
     * @param imager HostBased Imagerのハンドル
     *
     * @return 各プラットフォームによるIMG_StartPageの戻り値
     */
    virtual int SetToDecomposer(void* imager);
    
    /**
     * @brief オフスクリーンをウィンドウに関連付ける
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetActive();
    
    /**
     * @brief オフスクリーンをコピーする
     *
     * オフスクリーンのバッファを含めて、全ての状態をコピーする
     *
     * @param dst コピー先のオフスクリーン
     * 
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Copy(XdwOffScreen* dst);
    
    /**
     * @brief 現在のオフスクリーンを回転させる
     *
     * @param 角度
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Rotate(long angle);
    
protected:

    /********************************************/
    /* 関連 */
    
    /*! DCやオリジナルのHBITMAPを管理するクラス */
    XdwOffScreenControlerForViewerLightVirtual* fControler;
    
    /********************************************/
    /* 属性 */
    
    /********************************************/
    /* メソッド */
    
};

#endif
