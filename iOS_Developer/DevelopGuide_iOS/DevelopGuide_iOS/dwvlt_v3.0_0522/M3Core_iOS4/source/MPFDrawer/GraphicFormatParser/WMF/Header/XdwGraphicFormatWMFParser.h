/**
 * @file  XdwGraphicFormatWMFParser.h
 * @brief XdwGraphicFormat::WMF::Parserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFParser.h,v 1.5 2009/12/22 08:11:39 chikyu Exp $
 *
 * @date 2002-12-25 分割描画対応 Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_PARSER_H_
#define _XDW_GRAPHIC_FORMAT_WMF_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMF.h"
#include "GraphicFormatParser/WMF/Meta/Header/XdwGraphicFormatWMFMeta.h"
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "GraphicFormatParser/Header/XdwGraphicFormatParser.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatWMFObjectManager.h"
#include "XdwGraphicFormatWMFRasterManager.h"

/* 関連するクラスのIncludeファイル */
#include "DocuWorksDecoder/Include/XdwDocuWorksContentManager.h"

/* 列挙型の定義のためのIncludeファイル */
#include "GraphicFormatParser/GDI/Header/XdwGraphicFormatGDI.h"

/**
 * @brief DocuWorksファイルのWMFを読み込むクラス
 *
 */
class XdwGraphicFormat::WMF::Parser : public XdwGraphicFormat::Parser
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     */
    Parser();
    
    /**
     * @brief コンストラクタ
     *
     * @param generator XdwDataObject::Base::Generatorのインスタンス
     */
    Parser(XdwDataObject::Base::Generator* generator);

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
    /* 集約 */
    
    /*! 描画オブジェクトを管理するクラス */
    XdwGraphicFormat::WMF::ObjectManager fObjectManager;
    /*! ラスターを管理するクラス */
    XdwGraphicFormat::WMF::RasterManager fRasterManager;
    
    /********************************************/
    /* 関連 */
    
    /*! 大きなバイナリデータを作成するクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    
    /********************************************/
    /* 属性 */
    
    /*! パースメソッドを実行されたかのフラグ */
    bool fStartFlag;
    /*! グラフィックデータの横幅 */
    long fWidth;
    /*! グラフィックデータの縦幅 */
    long fHeight;
    /*! パース開始時のバイナリデータの位置 */
    long fParsePosition;
    
    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスを初期化する
     *
     * 継承クラスは本メソッドを実行するればよい
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize_();

    /**
     * @brief 任意のユーザ座標系の描画範囲の設定
     *
     * @param pd PD情報取得インターフェース
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetIsotropicUserExtent(XdwDocuWorks::ContentManager::PDInfo* pd);

    /**
     * @brief 各種ユーザ座標系の描画範囲の設定
     *
     * @param pd PD情報取得インターフェース
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetUserExtent(XdwDocuWorks::ContentManager::PDInfo* pd);
    
    /**
     * @brief パース開始時の設定
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetStartParameter();
    
    /**
     * @brief WMFを一気にパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseAll();

    /**
     * @brief WMFを指定されたレコード数だけパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg();

    /**
     * @brief WMF中の一つのレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRecord();

    /**
     * @brief 各種レコードをパースする
     *
     * @param record METARECORD構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     * @param instance パースするレコードのXdwGraphicFormat::WMF::Meta::Recordの継承クラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse_(XdwGraphicFormat::WMF::Meta::Record* record, XdwGraphicFormat::WMF::Meta::Record* instance);

    /********************************************/
    /* 以下各レコードの処理 */

    /**
     * @brief META_SETBKCOLORレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetBKColor(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETBKMODEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetBKMode(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETROP2レコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetROP2(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETPOLYFILLMODEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetPolyFillMode(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETSTRETCHBLTMODEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetStretchBltMode(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETTEXTCHAREXTRAレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetTextCharExtra(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_SETTEXTCOLORレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetTextColor(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETTEXTJUSTIFICATIONレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetTextJustification(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_SETWINDOWORGレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetWindowOrg(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETWINDOWEXTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetWindowExt(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETVIEWPORTORGレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetViewportOrg(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETVIEWPORTEXTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetViewportExt(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SCALEWINDOWEXTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseScaleWindowExt(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SCALEVIEWPORTEXTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseScaleViewportExt(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_LINETOレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLineTo(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_MOVETOレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseMoveTo(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_INTERSECTCLIPRECTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseIntersectClipRect(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_ARCレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseArc(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_ELLIPSEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseEllipse(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_PIEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePie(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_RECTANGLEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRectangle(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_ROUNDRECTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRoundRect(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_PATBLTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePatBlt(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SAVEDCレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSaveDC(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_SETPIXELレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetPixel(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_POLYGONレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolygon(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_POLYLINEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolyline(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_ESCAPEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseEscape(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_RESTOREDCレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRestoreDC(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_SETTEXTALIGNレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetTextAlign(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_CHORDレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseChord(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_EXTTEXTOUTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseExtTextOut(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_REALIZEPALETTEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRealizePalette(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_DIBBITBLTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseDIBBitBlt(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_DIBSTRETCHBLTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseDIBStretchBlt(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_STRETCHDIBレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStretchDIB(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief WMFPOLYPOLYPATBLTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolyPolyPatBlt(XdwGraphicFormat::WMF::Meta::Record* record);
    /**
     * @brief SETMAPMODEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetMapMode(XdwGraphicFormat::WMF::Meta::Record* record);
  
    
    /**
     * @brief META_TEXTOUTレコードをパースする
     * <br><b>AR11957対応：電子証明書文書以外での使用は想定していない</b>
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseTextOut(XdwGraphicFormat::WMF::Meta::Record* record);

};

#endif
