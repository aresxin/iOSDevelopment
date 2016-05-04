/** 
 * @file  XdwOffScreenControlerForViewerLight.h
 * @brief XdwOffScreenControlerForViewerLightクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreenControlerForViewerLight.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_CONTROLER_FOR_VIEWER_LIGHT_H_
#define _XDW_OFF_SCREEN_CONTROLER_FOR_VIEWER_LIGHT_H_

/* 依存するパッケージのIncludeファイル */
#include "XdwDocuWorks.h"

/* 列挙型のためのIncludeファイル */
#include "XdwError.h"

/* 集約するクラスのIncludeファイル */
#include "XdwMatrix.h"
#include "XdwShape.h"

/* 集約するクラスの宣言 */
class XdwOffScreen;

/**
 * @brief DocuWorks Viewer Light用のオフスクリーンを管理するための抽象クラス
 *
 * 共通化されたXdwOffScreen抽象クラスを管理する<br>
 * アプリケーションは本クラスを利用して、オフスクリーンを管理する
 */
class XdwOffScreenControlerForViewerLight
{
public:

    /********************************************/
    /* 列挙型 */

    /*! オフスクリーンの選択モード */
    enum OffScreenMode{
        /*! Basicコンテント + ヘッダ */
        PAPER_MODE,
        /*! Basicコンテント + ヘッダ + アノテーション */
        ANNOTATION_MODE
    };
    
    /*! オフスクリーンの活性化状態 */
    enum ActiveState{
        /*! 描画状態 */
        DRAW_STATE,
        /*! 表示状態 */
        DISPLAY_STATE
    };

    /*! 各種オフセット */
    enum OffsetSize{
        /*! ウィンドウの左端から紙の左端までの間隔 */
#ifdef RESTRICT_OFFSCREEN_SIZE
		OFFSET_VALUE = 10,
#elif defined(OFFSCREEN_NO_OFFSET)
        OFFSET_VALUE = 0,
#else
        OFFSET_VALUE = 20,
#endif

        /*! 重なり部分の間隔 */
        LAP_VALUE = 5
    };

#ifdef RESTRICT_OFFSCREEN_SIZE
	enum OffScreenSize{
#ifdef LINUX
		OFFSCREEN_WIDTH = 1200,
		OFFSCREEN_HEIGHT = 1200
#else
		OFFSCREEN_WIDTH = 900,
		OFFSCREEN_HEIGHT = 900
#endif
	};
#endif

    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwOffScreenControlerForViewerLight();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenControlerForViewerLight();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize() = 0;
    
    /**
     * @brief オフスクリーンをセットする
     *
     * @param page DocuWorksファイルのページ情報を取得するためのインスタンス
     * @param shade 紙に影をつけるかの有無
     * @param dpi 解像度
     * @param pos_x pos_y 画面左上のスクロール座標(固定オフスクリーンの位置計算用)
     * @param client_w client_h 表示ウインドウサイズ(固定オフスクリーンの位置計算用)
     * @param angle 現在の角度に対しての、回転角度<br>
     *              引数を指定しない場合は、DWファイルを基準とした0度にセットされる
     * @param create オフスクリーンを生成するかどうか<br>
     *               falseの時はパラメータの計算のみ行う
     *
     * @return XdwErrorCode参照
     */
#ifdef RESTRICT_OFFSCREEN_SIZE
	virtual XdwErrorCode Set(XdwDocuWorks::PageInfo* page, bool shade, long dpi, long pos_x, long pos_y, long client_w, long client_h, long angle = -1, bool create = true);
#else
	virtual XdwErrorCode Set(XdwDocuWorks::PageInfo* page, bool shade, long dpi, long angle = -1, bool create = true);
#endif

    /**
     * @brief オフスクリーンを閉じる
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Close();
    
    /**
     * @brief 表示モードをセットする
     *
     * @param mode XdwOffScreenControlerForViewerLight::OffScreenMode参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetDisplayMode(XdwOffScreenControlerForViewerLight::OffScreenMode mode);

    /**
     * @brief 現在セットされている表示モードを取得する
     *
     * @return XdwOffScreenControlerForViewerLight::OffScreenMode参照
     */
    virtual XdwOffScreenControlerForViewerLight::OffScreenMode GetDisplayMode();
    
    /**
     * @brief オフスクリーンの活性化状態をセットする
     *
     * @param state XdwOffScreenControlerForViewerLight::ActiveState参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetActiveState(XdwOffScreenControlerForViewerLight::ActiveState state);
    
    /**
     * @brief オフスクリーンを取得する
     *
     * @return オフスクリーンのインスタンス
     */
    virtual XdwOffScreen* GetActiveScreen();
    
    /**
     * @brief 角度を取得する
     *
     * @return DWファイルを基準とした角度
     */
    virtual long GetAngle();
    
    /**
     * @brief 解像度を取得する
     *
     * @return 紙領域を表示する場合の解像度(dpi)
     */
    virtual long GetDpi();

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
    
    /**
     * @brief DocuWorks座標系からデバイス座標系への変換行列を取得する
     *
     * @return 変換行列
     */
    virtual XdwMatrix GetTransferMatrix();

   /**
     * @brief 紙領域（黒枠の内側）を取得する
     *
     * @return 紙領域
     */
    virtual XdwRectangle GetPaperRect();

   /**
     * @brief マージンを含む紙領域（コンテント座標系）を取得する
     *
     * @return 紙領域
     */
    virtual XdwRectangle GetPaperRectWithMargin();

#ifdef RESTRICT_OFFSCREEN_SIZE
	long fPosX; //ページ上におけるオフスクリーンの位置(左上x座標)
	long fPosY; //ページ上におけるオフスクリーンの位置(左上y座標)
	long fContentWidth; //ページの幅
	long fContentHeight; //ページの高さ 
#endif
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! オフスクリーン */
    XdwOffScreen* fPaper;
    /*! DocuWorks座標系からデバイス座標系への変換行列 */
    XdwMatrix fDWtoDev;
    
    /********************************************/
    /* 属性 */

    /*! 初期化フラグ */
    bool fInitializeFlag;
    
    /*! 表示モード */
    XdwOffScreenControlerForViewerLight::OffScreenMode fDisplayMode;
    /*! 活性化状態 */
    XdwOffScreenControlerForViewerLight::ActiveState fActiveState;

    /*! 管理するオフスクリーンの横幅 */
    long fWidth;
    /*! 管理するオフスクリーンの縦幅 */
    long fHeight;
    /*! DW座標系の原点へのx軸方向のオフセット */
    long fOffsetX;
    /*! DW座標系の原点へのy軸方向のオフセット */
    long fOffsetY;
    /*! オフスクリーンの解像度(dpi) */
    long fDpi;
    /*! 回転角度 */
    long fAngle;
    /*! 紙の領域(黒枠の内側) */
    XdwRectangle fPaperRect;
    /*! 紙の領域(マージンを含む、コンテント座標系) */
    XdwRectangle fPaperRectWithMargin;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief 角度の計算
     *
     * @param 現在の角度から回転する角度
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CalculateAngle(long& angle);

    /**
     * @brief 1/100mm単位からpixel単位に変換する
     *
     * @param 1/100mm単位
     *
     * @return pixel単位
     */
    virtual long DWtoPixel(long value);
    
    /**
     * @brief 現在の属性から変換行列を計算する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CalculateTM();
};

#endif
