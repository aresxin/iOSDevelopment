/**
 * @file  XdwGraphicFormatWMFObjectManager.h
 * @brief XdwGraphicFormat::WMF::ObjectManagerクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFObjectManager.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_OBJECT_MANAGER_H_
#define _XDW_GRAPHIC_FORMAT_WMF_OBJECT_MANAGER_H_

#if defined WIN32
#pragma warning(disable : 4786)
#endif

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMF.h"
#include "GraphicFormatParser/WMF/Meta/Header/XdwGraphicFormatWMFMeta.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* STL使用のためのIncludeファイル */
#include <vector>
#include "System/SystemIF/XdwStl.h"

/**
 * @def XdwMetaObjectVector
 * \a  XdwGraphicFormat::WMF::Meta::Objectクラスを保持する配列
 */
typedef XdwStlVector(XdwGraphicFormat::WMF::Meta::Object*) XdwMetaObjectVector;

/* 関連するクラスの宣言 */
class XdwBridgeDrawIF;

/**
 * @brief DocuWorksファイルの描画オブジェクトを管理するクラス
 */
class XdwGraphicFormat::WMF::ObjectManager
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
     * @brief 管理するオブジェクト数をセットする
     *
     * @param count オブジェクト数
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetObjectCount(short count);
    
    /**
     * @brief 描画オブジェクトのレコードをパースする
     *
     * @param emr MetaRecordを読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::WMF::Meta::Record* emr);

protected:
    
    /********************************************/
    /* 集約 */

    /*! オブジェクトを管理するための配列 */
    XdwMetaObjectVector fObjectVector;

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
    /*! 管理するオブジェクト数 */
    long fObjectCount;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 集約を削除する
     */
    virtual void Delete();
    
    /**
     * @brief 各描画オブジェクトのレコードをパースする
     *
     * @param record Meta構造体を読み込んだXdwGraphicFormat::WMF::Meta::Recordのインスタンス
     * @param instance パースするレコードのだXdwGraphicFormat::WMF::Meta::Recordの継承クラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Parse(XdwGraphicFormat::WMF::Meta::Record* record, XdwGraphicFormat::WMF::Meta::Record* instance);
    
    /**
     * @brief 描画オブジェクトのセット
     *
     * @param handle 描画オブジェクトのハンドル
     * @param type 描画オブジェクトの型
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetObject(unsigned long handle, short type);
    
    /**
     * @brief IDの読み込みと描画オブジェクトの検索
     *
     * @param ret 戻り値(XdwErrorCode参照)
     * @param id 現在選択されているID
     *
     * @return 描画オブジェクトのインスタンス
     */
    virtual XdwGraphicFormat::WMF::Meta::Object* SearchObject(XdwErrorCode& ret, short& id);

    /********************************************/
    /* 以下各レコードの処理 */

    /**
     * @brief META_SELECTCLIPREGIONレコードをパースする
     *
     * IDで指定された領域をクリッピング領域として、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectClipRegion();
    
    /**
     * @brief META_SELECTOBJECTレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectObject();

    /**
     * @brief META_SELECTPALETTEレコードをパースする
     *
     * 指定されたIDを読み込み、パレットオブジェクトを検索して、Bridgeにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseSelectPalette();
    
    /**
     * @brief META_DIBCREATEPATTERNBRUSHレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseDIBCreatePatternBrush(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_DELETEOBJECTレコードをパースする
     *
     * 指定されたIDを読み込み、描画オブジェクトを検索して削除する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseDeleteObject();

    /**
     * @brief META_CREATEPALETTEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreatePalette(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_CREATEPENINDIRECTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreatePenIndirect(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_CREATEFONTINDIRECTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreateFontIndirect(XdwGraphicFormat::WMF::Meta::Record* record);

    /**
     * @brief META_CREATEBRUSHINDIRECTレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreateBrushIndirect(XdwGraphicFormat::WMF::Meta::Record* record);
    
    /**
     * @brief META_CREATEREGIONレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseCreateRegion(XdwGraphicFormat::WMF::Meta::Record* record);

    
};

#endif
