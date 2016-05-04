/**
 * @file  XdwGraphicFormatEMFEMRCreateBrushIndirectRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::CreateBrushIndirectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRCreateBrushIndirectRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_BRUSH_INDIRECT_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_BRUSH_INDIRECT_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogBrush.h"

/**
 * @brief EMR_CREATEBRUSHINDIRECTを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::CreateBrushIndirectRecord : public XdwGraphicFormat::EMF::EMR::ObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    CreateBrushIndirectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~CreateBrushIndirectRecord();
    
    /**
     * @brief EMRCREATEBRUSHINDIRECT構造体をパースする
     *
     * 必要なブラシ属性をImagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! LOGBRUSH構造体を規定するクラス */
    XdwGraphicFormat::GDI::LogBrush fBrush;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * LOGBRUSH構造体を規定するクラスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
