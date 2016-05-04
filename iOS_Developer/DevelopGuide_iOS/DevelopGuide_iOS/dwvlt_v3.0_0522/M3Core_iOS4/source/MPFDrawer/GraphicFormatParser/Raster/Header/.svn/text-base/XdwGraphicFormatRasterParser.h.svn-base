/**
 * @file  XdwGraphicFormatRasterParser.h
 * @brief XdwGraphicFormat::Raster::Parserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatRasterParser.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_RASTER_PARSER_H_
#define _XDW_GRAPHIC_FORMAT_RASTER_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatRaster.h"
#include "DataObject/Include/XdwDataObject.h"

/* 親クラスのIncludeファイル */
#include "GraphicFormatParser/Header/XdwGraphicFormatParser.h"

/* 集約するクラスのIncludeファイル */
#include "ImagerBridge/BridgeIF/XdwRaster.h"

/**
 * @brief DocuWorksファイルのラスターデータを読み込むクラス
 *
 */
class XdwGraphicFormat::Raster::Parser : public XdwGraphicFormat::Parser
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
     * @brief グラフィックデータの横幅を取得する
     *
     * @return グラフィックデータの横幅(pixel単位)
     */
    virtual long GetWidth();

    /**
     * @brief グラフィックデータの縦幅を取得する
     *
     * @return グラフィックデータの縦幅(pixel単位)
     */
    virtual long GetHeight();

    /**
     * @brief パースするグラフィックデータをセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set();

    /**
     * @brief セットされたグラフィックデータのパースを終了する
     *
     * XdwGraphicFormat::Parser::Parseメソッドを終了する場合(正常終了/異常終了)に、必ず呼ばなければならない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Terminate();
    
protected:

    /********************************************/
    /* 列挙型 */
    enum{
        /* イメージを単純にコピーする */
        ROP_COPY_IMAGE = 0x00CC0020
    };
    
    
    /********************************************/
    /* 集約 */
    
    /* イメージの描画属性 */
    XdwRasterImageAttribute fImageAttribute;
    /* マスクデータの描画属性 */
    XdwRasterImageAttribute fMaskAttribute;

    /********************************************/
    /* 関連 */
    
    /* イメージデータを管理するクラス */
    XdwDataObject::Common* fImageData;
    
    /********************************************/
    /* 属性 */
    
    /*! イメージデータのオフセット */
    long fImageOffset;
    /*! イメージデータのサイズ */
    long fImageBytes;
    
    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスを初期化する
     *
     * 継承クラスは本メソッドを実行するればよい
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();

    /**
     * @brief ラスターの描画属性を初期化する
     *
     * @param attribute 初期化するラスターの描画属性
     *
     * @return XdwErrorCode参照
     */
    virtual void InitializeAttribute(XdwRasterImageAttribute* attribute);

    /**
     * @brief BridgeIFに描画属性をセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetBridge();
    
    /**
     * @brief ラスターデータを一気にパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseAll();

    /**
     * @brief ラスターデータを指定されたライン数だけパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg();
private:
	/*! Divided 描画のときのStartフラグ */
	bool fIsDividedInitialize;
};

#endif
