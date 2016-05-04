/**
 * @file  XdwGraphicFormatWMFRasterManager.h
 * @brief XdwGraphicFormat::WMF::RasterManagerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFRasterManager.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * @date 2002-12-24 分割描画対応(クリスマスイブYasuhiroIto)
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_RASTER_MANAGER_H_
#define _XDW_GRAPHIC_FORMAT_WMF_RASTER_MANAGER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMF.h"
#include "GraphicFormatParser/WMF/Meta/Header/XdwGraphicFormatWMFMeta.h"
#include "GraphicFormatParser/WMF/EnhMeta/Header/XdwGraphicFormatWMFEnhMeta.h"

#include "DocuWorksDecoder/Include/XdwDocuWorks.h"
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief DocuWorksファイルの拡張ラスタ描画命令を管理するクラス
 */
class XdwGraphicFormat::WMF::RasterManager
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
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge, XdwDocuWorks::ContentManager* content, XdwDataObject::Base::Generator* generator,XdwGraphicFormat::ParseMode mode = XdwGraphicFormat::ALL_MODE, long image_leg_count = -1);
    
    /**
     * @brief 拡張ラスタ描画命令のレコードをパースする
     *
     * @param record META_RECORDを読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     * @param type 拡張命令の識別子
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::WMF::Meta::Record* record, unsigned long type);

protected:
    
    /********************************************/
    /* 集約 */

    /*! 参照されるラスターデータを管理するクラス */
    XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord* fRaster;
    
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
	XdwGraphicFormat::ParseMode fParseMode;
	/*! Image分割描画のさいのライン数*/
	long fImageLegCount;       
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 集約を削除する
     */
    virtual void Delete();
    
    /**
     * @brief 各描画オブジェクトのレコードをパースする/分割描画時は，指定ライン数で分割描画
     *
     * @param record Meta構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     * @param instance パースするレコードのだXdwGraphicFormat::WMF::Meta::Recordの継承クラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::WMF::Meta::Record* record, XdwGraphicFormat::WMF::Meta::Record* instance);

    /********************************************/
    /* 以下各レコードの処理 */

    /**
     * @brief 参照されるDIBをセットするレコードをパースする
     *
     * 状態を記憶する
     *
     * @param record Meta構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetDIB(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief 参照されるJpegをセットするレコードをパースする
     *
     * 状態を記憶する
     *
     * @param record Meta構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetJpeg(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief ラスターデータを参照して描画するレコードをパースする
     *
     * @param record Meta構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStretchDIBRef(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief ラスターデータを参照して描画するレコードをパースする
     *
     * @param record Meta構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStretchDIBReuse(XdwGraphicFormat::WMF::Meta::Record* record);
protected:
	enum {
		/*! イメージ分割数のデフォルト値 600DPIの時のベスト値*/
		IMAGE_DEFAULT_LEG_NUM = 24
	};

};

#endif
