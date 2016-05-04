/**
 * @file  XdwGraphicFormatEMFObjectManager.h
 * @brief XdwGraphicFormat::EMF::ObjectManagerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFObjectManager.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * @date 2002-11-28 CreatePen Add Yasuhiro Ito
 * @date 2004-02-26 Save Restoreのオブジェクト管理について追加と修正 Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_OBJECT_MANAGER_H_
#define _XDW_GRAPHIC_FORMAT_EMF_OBJECT_MANAGER_H_

#if defined WIN32
#pragma warning(disable : 4786)
#endif

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMF.h"
#include "GraphicFormatParser/EMF/EMR/Header/XdwGraphicFormatEMFEMR.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/* STL使用のためのIncludeファイル */
#include <list>
#include <vector>
#include "System/SystemIF/XdwStl.h"

/**
 * @brief DocuWorksファイルの描画オブジェクトを管理するクラス
 */
class XdwGraphicFormat::EMF::ObjectManager
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ObjectManager();

    /**
     * @brief デストラクタ
     */
    virtual ~ObjectManager();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     * @param bridge Imagerへアクセスするためのインターフェース
     * @param generator 大きなバイナリデータを作成するクラス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge, XdwDataObject::Base::Generator* generator);
    
    /**
     * @brief 描画オブジェクトのレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::EMF::EMR::Record* emr);

protected:

    /********************************************/
    /* 列挙型 */
    
    enum{
        /*! システムで使用される描画オブジェクトのIDのためのマスク */
        SYSTEM_MASK = 0x80000000
    };
    
    /********************************************/
    /* クラス */
    
    /*! オブジェクトIDを管理するクラス */
    class ObjectID{
    public:

        /********************************************/
        /* メソッド */
        
        /**
         * @brief デフォルトコンストラクタ
         */
        ObjectID();
        
        /**
         * @brief デストラクタ
         */
        virtual ~ObjectID();
        
        /**
         * @brief セット
         */
        virtual void Set(long id, unsigned long handle);

        /**
         * @brief IDの取得
         *
         * @return ID
         */
        virtual long GetID();

        /**
         * @brief ハンドルの取得
         *
         * @return ハンドル
         */
        virtual unsigned long GetHandle();

    protected:
        
        /********************************************/
        /* 属性 */

        /*! ID */
        long fID;
        /*! ハンドル */
        unsigned long fHandle;
    };
    
    /*! オブジェクトのIDを検索する関数オブジェクト */
    class PredicateID;

    /**
     * @def XdwEMFObjectList
     * \a XdwGraphicFormat::EMF::ObjectManager::ObjectIDクラスを保持するリスト
     */
    typedef XdwStlList(ObjectID) ObjectList;
    
    /********************************************/
    /* 集約 */

    /*! オブジェクトを管理するためのリスト */
    ObjectList fObjectList;

    /********************************************/
    /* 関連 */
    
    /*! バイナリデータを管理するインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
    /*! Imagerへのアクセスを管理するインターフェース */
    XdwBridgeDrawIF* fBridge;
    /*! 大きなバイナリデータを作成するクラス */
    XdwDataObject::Base::Generator* fDataObjectGenerator;
    
    /********************************************/
    /* 属性 */

    /*! 初期化フラグ */
    bool fInitializeFlag;
    
	/*! Saveの階層を数える*/
	long fReferenceCount;
	/*! Saveの階層毎の参照オブジェクトのリスト管理*/
	XdwStlList(long) fReferenceList;
	/*! Saveの階層管理*/
	XdwStlList(XdwStlList(long)) fReferenceCountList;

	/**
     * @brief Resotre時の整合性を取る
     *
    */
	bool Restore();
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 各描画オブジェクトのレコードをパースする
     *
     * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     * @param instance パースするレコードのだXdwGraphicFormat::EMF::EMR::ObjectRecordの継承クラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::EMF::EMR::Record* emr, XdwGraphicFormat::EMF::EMR::ObjectRecord* instance);
    
    /**
     * @brief IDの読み込みと描画オブジェクトの検索
     *
     * @param i 検索したイテレーターの戻り値
     * @param handle 検索した描画オブジェクトのハンドル
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SearchObject(ObjectList::iterator& i, unsigned long& handle);

    /********************************************/
    /* 以下各レコードの処理 */

    /**
     * @brief EMR_SELECTOBJECTレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectObject();

    /**
     * @brief EMR_DELETEOBJECTレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して削除する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseDeleteObject();
    
    /**
     * @brief EMR_CREATEBRUSHINDIRECTレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreateBrushIndirect(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_EXTCREATEFONTINDIRECTWレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseExtCreateFontIndirectW(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_CREATEDIBPATTERNBRUSHPTレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreateDIBPatternBrushPT(XdwGraphicFormat::EMF::EMR::Record* emr);

    /**
     * @brief EMR_EXTCREATEPENレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseExtCreatePen(XdwGraphicFormat::EMF::EMR::Record* emr);
	/**
     * @brief EMR_CREATEPENレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreatePen(XdwGraphicFormat::EMF::EMR::Record* emr);
  	/**
     * @brief EMR_CREATEPALETTEレコードをパースする
     *
	 * @param emr EMR構造体を読み込んだXdwGraphicFormat::EMF::EMR::Recordのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreatePalette(XdwGraphicFormat::EMF::EMR::Record* emr);
    /**
     * @brief EMR_SELECTPALETTEレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectPalette();
	/**
     * @brief EMR_REALIZEPALETTEレコードをパースする
     *
     * Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseRealizePalette();
 	/**
     * @brief EMR_EXTSELECTCLIPRGNレコードをパースする
     *
     * Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseExtSelectClipRgn();
 
};

#endif
