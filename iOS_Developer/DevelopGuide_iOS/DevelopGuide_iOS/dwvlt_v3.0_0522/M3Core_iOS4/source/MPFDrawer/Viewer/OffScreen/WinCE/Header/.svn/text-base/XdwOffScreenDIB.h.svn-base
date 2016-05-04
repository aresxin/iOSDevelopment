/** 
 * @file  XdwOffScreenDIB.h
 * @brief XdwOffScreenDIBクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreenDIB.h,v 1.5 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_DIB_H_
#define _XDW_OFF_SCREEN_DIB_H_

/* Windows GDIを使用するためのIncludeファイル */
#include <windows.h>

/* 列挙型のためのIncludeファイル */
#include "System/SystemIF/XdwError.h"

/* 親クラスの定義のためのIncludeファイル */
#include "Viewer/OffScreen/Common/Header/XdwOffScreen.h"

/**
 * @brief Windows上のオフスクリーンを管理するための実装クラス
 *
 * 2009/7/16 Offscreen Controllerクラスとの関連を廃止
 *           ページ枠描画、×描画、領域反転メソッドを削除
 *           ページ枠描画はViewer Lightアプリ側で実装する
 */
class XdwOffScreenDIB : public XdwOffScreen
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief コンストラクタ
     */
    XdwOffScreenDIB();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenDIB();
    
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
     * @brief ビットマップハンドルを取得する
     *
     * @return HBITMAP ビットマップハンドル
     */
    virtual HBITMAP GetBitmapHandle();

    /**
     * @brief メモリDCを取得する
	 *
	 * 取得側はこれを用いて紙片（ページ枠）の描画、オフスクリーンのBitBltを行う
     *
     * @return  メモリDC
     */
    virtual HDC GetMemoryDC();

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
     * @brief オフスクリーンのバッファを取得する
     *
     * @return バッファのポインタ
     */
    virtual unsigned char* GetBuffer();
    
    /**
     * @brief ビットマップインフォのサイズを取得する
     *
     * @return バッファサイズ(Byte単位)
     */
    virtual long GetBitmapInfoBytes();
    
    /**
     * @brief ビットマップインフォのバッファを取得する
     *
     * @return バッファのポインタ
     */
    virtual unsigned char* GetBitmapInfo();
    
    /**
     * @brief 指定された座標のバッファのポインタを取得する
     *
     * @return バッファのポインタ
     */
    virtual unsigned char* GetPixelPointer(long x, long y);
    
protected:
	friend class XdwOffScreenWriter;
    
    /********************************************/
    /* 属性 */

    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! ビットマップハンドル */
    HBITMAP fHandle;
    /*! オフスクリーンバッファ */
    unsigned char* fBuffer;
    /*! スキャンラインのサイズ */
    long fScanLineBytes;
	/*! メモリDC */
	// 2009/7/16 Offscreen Controllerから移動した
    HDC fMemoryDC;

	/*! ビットマップインフォのバッファ */
    BITMAPINFOHEADER fBitmapInfo;
    /*! ビットマップインフォのサイズ */    
    long fBitmapInfoBytes;
    
    /********************************************/
    /* メソッド */

    /**
     * @brief オフスクリーンの90度回転
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Rotate90();

    /**
     * @brief オフスクリーンの180度回転
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Rotate180();

    /**
     * @brief オフスクリーンの270度回転
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Rotate270();
};

#endif
