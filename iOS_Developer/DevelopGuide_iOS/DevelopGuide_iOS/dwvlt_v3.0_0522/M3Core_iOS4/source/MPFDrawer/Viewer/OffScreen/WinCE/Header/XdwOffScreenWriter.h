/** 
 * @file  XdwOffScreenWriter.h
 * @brief XdwOffScreenWriterクラスの定義
 *
 * @author DPC DS&S STD T31G Yozo Kashima <Yozo.Kashima@fujiexreox.co.jp>
 * @date 2002-10-22
 * @version 1.0
 * $Id: XdwOffScreenWriter.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_WRITER_H_
#define _XDW_OFF_SCREEN_WRITER_H_

/* 列挙型のためのIncludeファイル */
#include "XdwError.h"

/* 文字列ライブラリ */
#include <tchar.h>

/* 関連するクラスの宣言 */
class XdwOffScreenDIB;

/**
 * @brief XdwOffScreenDIBをファイルに書き込むためのクラス
 *
 * XdwOffScreenDIBの書き込み機能を切り出し別のクラス階層とした。
 */
class XdwOffScreenWriter
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief コンストラクタ
     */
    XdwOffScreenWriter();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenWriter();
    
    /**
     * @brief ファイルに書き込むべきデータを保持するオフスクリーンをセットする
     *
     * @param offscreen 書き込み対象のオフスクリーン
     */
    XdwErrorCode SetOffScreen(XdwOffScreenDIB *offscreen);

    /**
     * @brief オフスクリーンをファイルに書き込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode WriteTo(TCHAR* file_name) = 0;

protected:
    
    /********************************************/
    /* 属性 */


    /********************************************/
    /* メソッド */
    
    /**
     * @brief 
     *
     * @param 
     *
     * @return 
     */
	long GetHeight() const;
	long GetWidth() const;

    /**
     * @brief スキャンラインサイズを取得する
     *
     * @return スキャンラインサイズ(Byte単位)
     */
    long GetScanLineBytes() const;
    
     /**
     * @brief バッファサイズを取得する
     *
     * @return バッファサイズ(Byte単位)
     */
    long GetBufferBytes() const;

     /**
     * @brief 指定された座標のバッファのポインタを取得する
     *
     * @return バッファのポインタ
     */
    unsigned char* GetPixelPointer(long x, long y);
    
    /**
     * @brief リトルエンディアンの書き込み
     *
     * @param buf 書き込みバッファ
     * @param data 書き込みデータ
     *
     * @return XdwErrorCode参照
     */
    XdwErrorCode Write(unsigned char* buf, unsigned long data);

    /**
     * @brief リトルエンディアンの書き込み
     *
     * @param buf 書き込みバッファ
     * @param data 書き込みデータ
     *
     * @return XdwErrorCode参照
     */
    XdwErrorCode Write(unsigned char* buf, unsigned short data);
    
private:
	/********************************************/
    /* 関連 */
    
    /*! 書き込み対象のオフスクリーン */
    XdwOffScreenDIB* fOffScreen;
};

#endif