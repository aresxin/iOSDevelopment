/**
 * @file  XdwGraphicFormatEMFEMRExtCreatePenRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ExtCreatePenRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRExtCreatePenRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EXT_CREATE_PEN_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EXT_CREATE_PEN_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRasterObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIExtLogPen.h"

/**
 * @brief EMR_EXTCREATEPENを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ExtCreatePenRecord : public XdwGraphicFormat::EMF::EMR::RasterObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    ExtCreatePenRecord(XdwDataObject::Base::Generator* generator);

    /**
     * @brief デストラクタ
     */
    virtual ~ExtCreatePenRecord();
    
    /**
     * @brief EMREXTCREATEPEN構造体をパースする
     *
     * ペン属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! EXTLOGPEN構造体を規定するクラス */
    XdwGraphicFormat::GDI::ExtLogPen fPen;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * LOGFONT構造体を規定するクラスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
