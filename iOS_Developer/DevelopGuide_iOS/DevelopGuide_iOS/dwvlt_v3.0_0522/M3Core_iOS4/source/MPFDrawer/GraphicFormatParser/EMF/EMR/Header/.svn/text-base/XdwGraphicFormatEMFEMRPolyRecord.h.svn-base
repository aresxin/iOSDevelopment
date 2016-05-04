/**
 * @file  XdwGraphicFormatEMFEMRPolyRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolyRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRPolyRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_POLY_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_POLY_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwPoint.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/**
 * @brief EMRの座標配列を扱う抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PolyRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PolyRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PolyRecord();
    
    /**
     * @brief 座標配列を格納したEMR構造体をパースする
     *
     * 座標配列格納したEMR構造体をパースして、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

    /********************************************/
    /* 集約 */
    
    /* 座標配列を格納するクラス */
    XdwPointVector fPoints;
    
    /********************************************/
    /* 属性 */
    
    /*! 読み込みモード */
    XdwGraphicFormat::GDI::ReadMode fReadMode;
    /*! 現在位置の設定フラグ */
    bool fMoveFlag;
    /*! クローズフラグ */
    bool fCloseFlag;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 集約を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
    /**
     * @brief 座標配列をImagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Draw() = 0;
};

#endif
