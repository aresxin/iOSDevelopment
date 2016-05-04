/**
 * @file  XdwGraphicFormatEMFRasterManager.h
 * @brief XdwGraphicFormat::EMF::RasterManagerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.01
 * $Id: XdwGraphicFormatEMFRasterManager.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * @date 2002-12-23 分割描画対応 Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_RASTER_MANAGER_H_
#define _XDW_GRAPHIC_FORMAT_EMF_RASTER_MANAGER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMF.h"
#include "GraphicFormatParser/EMF/EMR/Header/XdwGraphicFormatEMFEMR.h"
#include "GraphicFormatParser/EMF/EnhEMR/Header/XdwGraphicFormatEMFEnhEMR.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief DocuWorksファイルの拡張ラスタ描画命令を管理するクラス
 */
class XdwGraphicFormat::EMF::RasterManager
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RasterManager();

    /**
     * @brief デストラクタ
     */
    virtual ~RasterManager();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param bridge Imagerへアクセスするためのインターフェース
     * @param content コンテントを管理するインターフェース
     * @param generator 大きなバイナリデータを作成するクラス
     * @param mode XdwGraphicFormat::ParseMode参照
     * @param image_leg_count イメージ分割描画の分割ライン数
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge, XdwDocuWorks::ContentManager* content, XdwDataObject::Base::Generator* generator,XdwGraphicFormat::ParseMode mode = XdwGraphicFormat::ALL_MODE, long image_leg_count = 24);
    
    /**
     * @brief 拡張ラスタ描画命令のレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::EMF::EMR::Record* emr);

protected:
    
    /********************************************/
    /* 集約 */

    /*! 参照されるラスターデータを管理するクラス */
    XdwGraphicFormat::EMF::EnhEMR::SetRasterRecord* fRaster;
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータを管理するインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    /*! Imagerへのアクセスを管理するインターフェース */
    XdwBridgeDrawIF* fBridge;
    /*! コンテントを管理するインターフェース */
    XdwDocuWorks::ContentManager* fContent;
    /*! 大きなバイナリデータを作成するクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    
    /********************************************/
    /* 属性 */

    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! 参照したJpegの回数 */
    long fJpegCount;
	/*! XdwGraphicFormat::ParseMode参照*/
	XdwGraphicFormat::ParseMode  fParseMode;
	/*! Image分割描画のさいのライン数*/
	long fImageLegCount;   
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 集約を削除する
     */
    virtual void Delete();
    
    /**
     * @brief 各描画オブジェクトのレコードをパースする<br>
	 *LEG_MODE時には指定ライン数で分割される
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @param instance パースするレコードのだXdwGraphicFormat::EMF::EMR::Recordの継承クラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::EMF::EMR::Record* instance);

    /********************************************/
    /* 以下各レコードの処理 */

    /**
     * @brief 参照されるDIBをセットするレコードをパースする
     *
     * 状態を記憶する
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetDIB(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief 参照されるJpegをセットするレコードをパースする
     *
     * 状態を記憶する
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetJpeg(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief ラスターデータを参照して描画するレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStretchDIBitsRef(XdwGraphicFormat::EMF::EMR::Record* emr);
    
};

#endif
