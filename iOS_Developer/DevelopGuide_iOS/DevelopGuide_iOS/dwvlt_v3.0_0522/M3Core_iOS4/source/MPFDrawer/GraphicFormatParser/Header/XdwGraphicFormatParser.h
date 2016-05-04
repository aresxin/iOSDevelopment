/**
 * @file  XdwGraphicFormatParser.h
 * @brief XdwGraphicFormat::Parserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.01
 * $Id: XdwGraphicFormatParser.h,v 1.9 2009/12/22 08:11:41 chikyu Exp $
 *
 *
 * @date 2002-12-25 分割描画対応 Yasuhiro Ito
 * @date 2004-12-07 分割描画時のリーク対応 Yasuhiro.Ito@fujixerox.co.jp
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_PARSER_H_
#define _XDW_GRAPHIC_FORMAT_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "GraphicFormatParser/Include/XdwGraphicFormat.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"

/* インターフェースのIncludeファイル */
#include "GraphicFormatParser/Include/XdwGraphicFormatInfo.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief DocuWorksファイルのグラフィックフォーマットを読み込む抽象クラス
 *
 */
class XdwGraphicFormat::Parser : public XdwGraphicFormat::Info
{

public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Parser();

    /**
     * @brief デストラクタ
     */
    virtual ~Parser();

    /**
     * @brief インスタンスを初期化する
     *
     * @param bridge XdwBridgeDrawIFインターフェースのインスタンス
     * @param content コンテントの情報を取得するためのインターフェース
     * @param mode XdwGraphicFormat::ParseMode参照
     * @param image_leg_count イメージ分割描画の分割ライン数(デフォルト値 24：600dpiの最適値)
     * @param meta_leg_count MetaRecordを読み込む単位数(デフォルト値 1)
	 *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwBridgeDrawIF* bridge, XdwDocuWorks::ContentManager* content,XdwGraphicFormat::ParseMode mode = XdwGraphicFormat::ALL_MODE, long image_leg_count = IMAGE_DEFAULT_LEG_NUM  ,long meta_leg_count = META_RECORD_DEFAULT_LEG_NUM);
    
    /**
     * @brief パースするグラフィックデータをセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set() = 0;
    
    /**
     * @brief セットされたグラフィックデータをパースする
     *
     * グラフィックデータをパースしながら、XdwBridgeDrawIFのインスタンスに描画データを渡していく
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse();

    /**
     * @brief セットされたグラフィックデータのパースを終了する
     *
     * XdwGraphicFormat::Parser::Parseメソッドを終了する場合(正常終了/異常終了)に、必ず呼ばなければならない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Terminate() = 0;
    
protected:
    /********************************************/
    /* 関連 */
    
    /*! 描画方法を規定するインターフェース */
    XdwBridgeDrawIF* fBridge;

// WinMobile分割描画対応
// 09/10/06 M.Chikyu
public:
    /*! コンテントの情報を取得するためのインターフェース */
    XdwDocuWorks::ContentManager* fContent;
protected:

    /*! グラフィックデータが格納されているバイナリデータインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    
    /********************************************/
    /* 属性 */
    
    /*! 初期化フラグ */
    bool fInitializeFlag;
    /*! グラフィックデータのパース方法 */
    XdwGraphicFormat::ParseMode fParseMode;
    /*! 分割してパースする場合のイメージライン数 */
    long fImageLegCount;
    /*! 分割してパースする場合のメタレコード単位数*/
	long fMetaLegCount;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 関連や属性を初期化する
     */
    virtual void Clear();
    
    /**
     * @brief インスタンスを初期化する
     *
     * 継承クラスは本メソッドを実行するればよい
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize_();

    /**
     * @brief グラフィックデータを一気にパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseAll() = 0;

    /**
     * @brief LEG_MODEの時にグラフィックデータを指定された分割数だけパースする<br>イメージのは指定ライン数で分割描画される．
	 * 
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg() = 0;

protected:
	enum{
		/*! イメージ分割数のデフォルト値 600DPIの時のベスト値*/
		IMAGE_DEFAULT_LEG_NUM = 24,
		/*! メタレコード分割時のパースするレコード数*/ 
        META_RECORD_DEFAULT_LEG_NUM = 1
	};

	/* AR11895対応*/
    /*! 画像分割描画時にEndDrawDividedImageを呼ぶ必要があるときに立てるフラグ*/
	bool fEndDrawCallFlg;
};

#endif
