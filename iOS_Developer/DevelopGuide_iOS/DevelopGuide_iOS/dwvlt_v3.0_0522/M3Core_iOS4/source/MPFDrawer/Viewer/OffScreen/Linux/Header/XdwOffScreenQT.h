/** 
 * @file  XdwOffScreenQT.h
 * @brief XdwOffScreenQTクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreenQT.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_QT_H_
#define _XDW_OFF_SCREEN_QT_H_

/* Linux QTを使用するためのIncludeファイル */
#include <qimage.h>
#include <qpixmap.h>

/* 列挙型のためのIncludeファイル */
#include "XdwError.h"

/* 親クラスの定義のためのIncludeファイル */
#include "XdwOffScreen.h"

/* 関連するクラスの宣言 */
class XdwOffScreenControlerForViewerLightOnLinuxQT;

/**
 * @brief Windows上のオフスクリーンを管理するための実装クラス
 */
class XdwOffScreenQT : public XdwOffScreen
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief コンストラクタ
     *
     * @param controler DC等を管理するクラス
     */
    XdwOffScreenQT();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenQT();
    
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
     * @brief オフスクリーンの一部をウィンドウに関連付ける
     *
     * @param x, y, w, h オフスクリーン座標系の矩形
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetActive(int x, int y, int w, int h);
    
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
    
    /**
     * @brief ウィンドウに転送する
     *
     * @param window_pd ウィンドウを構成するPaintDevice
     * @param src_x 転送元のx座標
     * @param src_y 転送元のy座標
     * @param dst_x 転送先のx座標
     * @param dst_y 転送先のy座標
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode BitBlt(QPaintDevice* window_pd, long src_x, long src_y, long dst_x, long dst_y);
    
    /**
     * @brief QPixmapを取得する
     *
     * @return XdwErrorCode参照
     */
    const QPixmap* GetPixmap() { return &fPixmap; };

protected:
    /********************************************/
    /* 属性 */

    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! オフスクリーンバッファ */
    QImage fBuffer;
    /*! Pixmapオフスクリーン(converted from QImage) */
    QPixmap fPixmap;
    long fScanLineBytes;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief スキャンラインサイズを取得する
     *
     * @return スキャンラインサイズ(Byte単位)
     */
    virtual long GetScanLineBytes();
    
    /**
     * @brief バッファサイズを取得する
     *
     * @return バッファサイズ(Byte単位)
     */
    virtual long GetBufferBytes();
    
    /**
     * @brief 指定された座標のバッファのポインタを取得する
     *
     * @return バッファのポインタ
     */
    virtual unsigned char* GetPixelPointer(long x, long y);

    /**
     * @brief 指定された矩形を、指定された色でFillする
     *
     * Create()メンバ関数でfBufferが生成される前に呼んではいけない。
     * 左上 (x1, y1)、右下 (x2, y2) も描画対象に含まれる。
     */
    virtual void FillRect(long x1, long y1, long x2, long y2, QColor color);

    /**
     * @brief 指定された矩形を、指定された色でStrokeする
     *
     * Create()メンバ関数でfBufferが生成される前に呼んではいけない。
     * 左上 (x1, y1)、右下 (x2, y2) も描画対象に含まれる。
     */
    virtual void StrokeRect(long x1, long y1, long x2, long y2, QColor color);
};

#endif
