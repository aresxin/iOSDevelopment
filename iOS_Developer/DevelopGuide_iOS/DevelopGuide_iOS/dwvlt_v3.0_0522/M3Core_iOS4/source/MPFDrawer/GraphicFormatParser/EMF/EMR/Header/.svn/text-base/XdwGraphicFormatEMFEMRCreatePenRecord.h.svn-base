/**
 * @file  XdwGraphicFormatEMFEMRCreatePenRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::CreatePenRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2002-11-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRCreatePenRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_PEN_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_PEN_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRasterObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogPen.h"
/**
 * @brief EMR_CREATEPENを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::CreatePenRecord : public XdwGraphicFormat::EMF::EMR::RasterObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    CreatePenRecord(XdwDataObject::Base::Generator* generator);

    /**
     * @brief デストラクタ
     */
    virtual ~CreatePenRecord();
    
    /**
     * @brief EMRCREATEPEN構造体をパースする
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
    XdwGraphicFormat::GDI::LogPen fPen;
    
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
