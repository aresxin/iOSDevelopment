/**
 * @file  XdwGraphicFormatEMFParser.h
 * @brief XdwGraphicFormat::EMF::Parserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.09
 * $Id: XdwGraphicFormatEMFParser.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * @date 2002-11-28 CreatePen Add Yasuhiro Ito
 * @date 2002-12-11 Palette関連追加 Yasuhiro Ito
 * @date 2002-12-23 分割描画対応 Yasuhiro Ito
 * @date 2003-09-01 OLE描画対応  Yasuhiro Ito
 * @date 2003-09-25 OLE描画対応で、EMFHEADERの詳細情報を取得できるよう追加  Yasuhiro Ito
 * @date 2003-10-23 OLE描画対応  Yasuhiro Ito
 * @date 2004-01-22 OLE描画対応  Yasuhiro Ito
 * @date 2004-03-09 コメント整理  Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_PARSER_H_
#define _XDW_GRAPHIC_FORMAT_EMF_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMF.h"
#include "GraphicFormatParser/EMF/EMR/Header/XdwGraphicFormatEMFEMR.h"
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 親クラスのIncludeファイル */
#include "GraphicFormatParser/Header/XdwGraphicFormatParser.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatEMFObjectManager.h"
#include "XdwGraphicFormatEMFRasterManager.h"
#include "GraphicFormatParser/EMF/EMR/Header/XdwGraphicFormatEMFEMRHeaderRecord.h"
/* 列挙型の定義のためのIncludeファイル */
#include "GraphicFormatParser/GDI/Header/XdwGraphicFormatGDI.h"

/**
 * @brief DocuWorksファイルのEMFを読み込むクラス
 *
 */
class XdwGraphicFormat::EMF::Parser : public XdwGraphicFormat::Parser
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
    
    /*! 描画オブジェクトを管理するクラス */
    XdwGraphicFormat::EMF::ObjectManager fObjectManager;
    /*! ラスタ描画を管理するクラス */
    XdwGraphicFormat::EMF::RasterManager fRasterManager;
	/*! GraphicInfoの情報保持するヘッダークラス*/
	XdwGraphicFormat::EMF::EMR::HeaderRecord fHeader;
    /********************************************/
    /* 関連 */
    
    /*! 大きなバイナリデータを作成するクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    /********************************************/
    /* 属性 */
    
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
     * @brief EMFを一気にパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseAll();

    /**
     * @brief LEG_MODE時にEMFを指定されたレコード数だけパースする.イメージは指定ライン数で分割される
	 * 
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg();
    
    /**
     * @brief EMF中の一つのレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRecord();
    
    /**
     * @brief 各種レコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @param instance パースするレコードのXdwGraphicFormat::EMF::EMR::Recordの継承クラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse_(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::EMF::EMR::Record* instance);
    
    
    /********************************************/
    /* 以下各レコードの処理 */

    /**
     * @brief EMR_POLYBEZIERレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @param mode XdwGraphicFormat::GDI::ReadMode
     * @param update 現在位置の更新フラグ
     * @param move 現在位置をセットするかのフラグ
     * @param close パスを閉じるかのフラグ
	 *
	 * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolyBezier(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::GDI::ReadMode mode, bool update, bool move = false, bool close = false);
    
    /**
     * @brief EMR_POLYGONレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @param mode XdwGraphicFormat::GDI::ReadMode
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolygon(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::GDI::ReadMode mode);

    /**
     * @brief EMR_POLYLINEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @param mode XdwGraphicFormat::GDI::ReadMode
     * @param update 現在位置の更新フラグ
     * @param move 現在位置をセットするかのフラグ
     * @param close パスを閉じるかのフラグ
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolyline(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::GDI::ReadMode mode, bool update, bool move = false, bool close = false);
    
    /**
     * @brief EMR_SETWINDOWORGEXレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
	 * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetWindowOrgEx(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_SETBRUSHORGEXレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetBrushOrgEx(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_SETBKMODEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetBKMode(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_SETPOLYFILLMODEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetPolyFillMode(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_SETROP2レコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetROP2(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_SETSTRETCHBLTMODEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetStretchBltMode(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_SETTEXTALIGNレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetTextAlign(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_SETTEXTCOLORレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetTextColor(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_SETBKCOLORレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetBKColor(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_MOVETOEXレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseMoveToEx(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_RECTANGLEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRectangle(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_LINETOレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLineTo(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_SETMITERLIMITレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetMiterLimit(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_BEGINPATHレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseBeginPath();

    /**
     * @brief EMR_ENDPATHレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseEndPath();

    /**
     * @brief EMR_CLOSEFIGUREレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCloseFigure();

    /**
     * @brief EMR_FILLPATHレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseFillPath();

    /**
     * @brief EMR_STROKEPATHレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStrokePath();

    /**
     * @brief EMR_SELECTCLIPPATHレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectClipPath(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_GDICOMMENTレコードをパースする<br>この先で拡張命令をパーすする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseGDIComment(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_BITBLTレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseBitBlt(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_MASKBLTレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseMaskBlt(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_STRETCHDIBITSレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStretchDIBits(XdwGraphicFormat::EMF::EMR::Record* emr);
    
    /**
     * @brief EMR_EXTTEXTOUTAレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseExtTextOutA(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief 指定された矩形をクリッピング領域とする拡張レコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseEnhRectClip(XdwGraphicFormat::EMF::EMR::Record* emr);


	/******************************************************/
	/* 以下DocuWorks標準付属OLEアノテーション対応時に追加 */
	
	/**
     * @brief 指定された矩形をクリッピング領域とするレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseIntersectClipRect(XdwGraphicFormat::EMF::EMR::Record* emr);
	/**
     * @brief 指定された矩形をクリッピング領域とするレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseExcludeClipRect(XdwGraphicFormat::EMF::EMR::Record* emr);
    /**
     * @brief EMR_ELLIPSEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseEllipse(XdwGraphicFormat::EMF::EMR::Record* emr);
    /**
     * @brief EMR_MAP_MODEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseSetMapMode(XdwGraphicFormat::EMF::EMR::Record* emr);
    /**
     * @brief EMR_SETWINDOWEXTEXレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetWindowExtEx(XdwGraphicFormat::EMF::EMR::Record* emr);
      /**
     * @brief EMR_SETVIEWPORTORGEXレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseSetViewPortOrgEx(XdwGraphicFormat::EMF::EMR::Record* emr);
      /**
     * @brief EMR_SCALEVIEWPORTORGEXレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseScaleViewPortEx(XdwGraphicFormat::EMF::EMR::Record* emr);

     /**
     * @brief EMR_SETVIEWPORTEXTEXコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
	 *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseSetViewPortExtEx(XdwGraphicFormat::EMF::EMR::Record* emr);
  /**
     * @brief EMR_POLYPOLYGONレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
	 * @param mode XdwGraphicFormat::GDI::ReadMode
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolyPolygon(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::GDI::ReadMode mode);
  /**
     * @brief EMR_StretchBltレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseStretchBlt(XdwGraphicFormat::EMF::EMR::Record* emr);



//#if ( defined( _DEBUG ) || defined( DEBUG))

	/******************************************************/
	/* 以下OLEアノテーション対応対応時に追加 040127*/

	/**
     * @brief EMR_POLYPOLYLINEレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
	 * @param mode XdwGraphicFormat::GDI::ReadMode
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePolyPolyline(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::GDI::ReadMode mode);
    /**
     * @brief EMR_EXTTEXTOUTWレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseExtTextOutW(XdwGraphicFormat::EMF::EMR::Record* emr);
    /**
     * @brief EMR_ROUNDRECTレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRoundRect(XdwGraphicFormat::EMF::EMR::Record* record);
    /**
     * @brief EMR_ARCレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseArc(XdwGraphicFormat::EMF::EMR::Record* record);
    /**
     * @brief EMR_PIEレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParsePie(XdwGraphicFormat::EMF::EMR::Record* record);
   	/**
     * @brief EMR_REALIZEPALETTEレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseResizePalette(XdwGraphicFormat::EMF::EMR::Record* emr);   	
	/**
     * @brief EMR_SETARCDIRECTIONレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSetArcDirection(XdwGraphicFormat::EMF::EMR::Record* emr);
#if 0
	/**
     * @brief EMR_SET_PIXELVコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseSetPixelv(XdwGraphicFormat::EMF::EMR::Record* emr);

     /**
     * @brief EMR_SCALEWINDOWEXTEXEXレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
	virtual XdwErrorCode ParseScaleWindowExtEx(XdwGraphicFormat::EMF::EMR::Record* emr);

	/**
     * @brief EMR_STROKEANDFILLPATHレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseStrokeAndFillPath();

#endif
//#endif //_DEBUG
};
#endif
