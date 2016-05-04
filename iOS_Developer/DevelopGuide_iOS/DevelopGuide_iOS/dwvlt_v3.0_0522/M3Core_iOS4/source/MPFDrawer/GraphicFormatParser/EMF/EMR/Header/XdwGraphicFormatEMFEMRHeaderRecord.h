/**
 * @file  XdwGraphicFormatEMFEMRHeaderRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::HeaderRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRHeaderRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * @date 2003-09-25 OLE描画対応で、EMFHEADERの詳細情報を取得できるよう追加  Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_HEADER_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_HEADER_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "GraphicFormatParser/GDI/Header/XdwGraphicFormatGDISize.h"
#include"GraphicFormatParser/GDI/Header/XdwGraphicFormatGDIRectangle.h"

/**
 * @brief ENHMETAHEADER構造体を規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::HeaderRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    HeaderRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~HeaderRecord();
    
    /**
     * @brief ENHMETAHEADER構造体をパースする
     *
     * EMFデータの画素サイズとパレット数以外は読み飛ばす
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
    /**
     * @brief エントリーされているパレット数の取得
     *
     * @return エントリーされているパレット数
     */
    virtual long GetPaletteCount();
    
    /**
     * @brief デバイスサイズの横幅の取得
     *
     * @return デバイスサイズの横幅(pixel単位)
     */
    virtual long GetDeviceWidth();
    
    /**
     * @brief デバイスサイズの縦幅の取得
     *
     * @return デバイスサイズの縦幅(pixel単位)
     */
    virtual long GetDeviceHeight();
    /**
     * @brief デバイスサイズの横幅の取得
     *
     * @return デバイスサイズの横幅(1/100 mm 単位)
     */
    virtual long GetSzlMillimeterWidth();
    
    /**
     * @brief デバイスサイズの縦幅の取得
     *
     * @return デバイスサイズの縦幅(1/100 mm 単位)
     */
    virtual long GetSzlMillimeterHeight();

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
	virtual bool GetRclBounds(long* topX , long* topY , long* bottomX ,long* bottomY);

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
	virtual bool GetRclFrame(long* topX , long* topY , long* bottomX ,long* bottomY);
	
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! EMFデータの画素サイズ */
    XdwGraphicFormat::GDI::Size fDeviceSize;
    /*! EMFデータの画素サイズ(1/100 mm) */
	XdwGraphicFormat::GDI::Size fMillimeterSize;
    /*! EMFHeaderのBoundsRect(pixel) */
	XdwGraphicFormat::GDI::Rectangle fRclBoundsRect;
    /*! EMFHeaderのFrameRect(1/100 mm) */
	XdwGraphicFormat::GDI::Rectangle fRclFrameRect;

    /********************************************/
    /* 属性 */
    
    /*! EMFデータにエントリーされているパレット数 */
    long fPaletteCount;
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * EMFデータの画素サイズを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
