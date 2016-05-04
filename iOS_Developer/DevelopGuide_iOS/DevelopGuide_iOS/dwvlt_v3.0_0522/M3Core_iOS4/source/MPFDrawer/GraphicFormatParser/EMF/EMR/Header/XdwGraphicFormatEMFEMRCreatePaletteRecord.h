/**
 * @file  XdwGraphicFormatEMFEMRCreatePaletteRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::CreatePaletteRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2002-12-11
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRCreatePaletteRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_PALETTE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_PALETTE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRasterObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogPalette.h"
/**
 * @brief EMR_CREATEPALETTEを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::CreatePaletteRecord : public XdwGraphicFormat::EMF::EMR::RasterObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    CreatePaletteRecord(XdwDataObject::Base::Generator* generator);

    /**
     * @brief デストラクタ
     */
    virtual ~CreatePaletteRecord();
    
    /**
     * @brief EMRCREATEPEN構造体をパースする
     *
     * パレット属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! EXTLOGPALETTE構造体を規定するクラス */
    XdwGraphicFormat::GDI::LogPalette fPalette;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * LOGPALETTE構造体を規定するクラスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
