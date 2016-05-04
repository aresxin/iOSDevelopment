/**
 * @file  XdwGraphicFormatInfo.h
 * @brief XdwGraphicFormat::Infoクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatInfo.h,v 1.4 2009/12/22 08:11:36 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_INFO_H_
#define _XDW_GRAPHIC_FORMAT_INFO_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormat.h"

/**
 * @interface XdwGraphicFormat::Info XdwGraphicFormatInfo.h
 * @brief セットされたコンテントのグラフィックデータの情報を取得する
 *
 * クライアントは本インターフェースのインスタンスの削除は認めない<br>
 * 本インターフェースを利用して、グラフィックデータのサイズなどを取得できる
 */
class XdwGraphicFormat::Info
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief グラフィックデータの横幅を取得する
     *
     * @return グラフィックデータの横幅(pixel単位)
     */
    virtual long GetWidth() = 0;
    
    
    /**
     * @brief グラフィックデータの縦幅を取得する
     *
     * @return グラフィックデータの縦幅(pixel単位)
     */
    virtual long GetHeight() = 0;

	/**
     * @brief EMFHeader中のrclBoundsのデータを返す。<b>EMFデータ以外の時は何もしない</b>
     *
	 *
     * @param LeftTopX
     * @param LeftTopY
     * @param RightBottomX
     * @param RightBottomY 
     *
	 * @return bool
     */
	virtual bool GetRclBounds(long* topX , long* topY , long* bottomX ,long* bottomY){
		return true;
	}

	/**
     * @brief EMFHeader中のrclFrameのデータを返す。<b>EMFデータ以外の時は何もしない</b>
     * 1/100 millimeter units
	 *
     * @param LeftTopX
     * @param LeftTopY
     * @param RightBottomX
     * @param RightBottomY 
     *
	 * @return bool
     */
	virtual bool GetRclFrame(long* topX , long* topY , long* bottomX ,long* bottomY){
		return true;
	}

	/**
     * @brief 参照デバイスのミリメータ EMF以外のときは-1を返す
     *
     * @return グラフィックデータの縦幅(1/100 mm単位)
     */
	virtual long  GetSzlMillimeterHeight(){
		return -1;
	}
	/**
     * @brief 参照デバイスのミリメータ EMF以外のときは-1を返す
     *
     * @return グラフィックデータの横幅(1/100 mm単位)
     */
	virtual long  GetSzlMillimeterWidth(){
		return -1;
	}


};

#endif
