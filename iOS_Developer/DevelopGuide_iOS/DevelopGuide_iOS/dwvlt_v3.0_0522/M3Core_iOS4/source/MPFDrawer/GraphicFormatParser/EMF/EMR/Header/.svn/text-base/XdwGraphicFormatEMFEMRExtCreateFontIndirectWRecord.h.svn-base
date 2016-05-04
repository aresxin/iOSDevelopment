/**
 * @file  XdwGraphicFormatEMFEMRExtCreateFontIndirectWRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ExtCreateFontIndirectWRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRExtCreateFontIndirectWRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EXT_CREATE_FONT_INDIRECT_W_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EXT_CREATE_FONT_INDIRECT_W_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRObjectRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogFont.h"

/**
 * @brief EMR_EXTCREATEFONTNDIRECTWを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ExtCreateFontIndirectWRecord : public XdwGraphicFormat::EMF::EMR::ObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExtCreateFontIndirectWRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ExtCreateFontIndirectWRecord();
    
    /**
     * @brief EMREXTCREATEFONTNDIRECTW構造体をパースする
     *
     * フォント属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! LOGBFONT構造体を規定するクラス */
    XdwGraphicFormat::GDI::LogFont fFont;
    
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
