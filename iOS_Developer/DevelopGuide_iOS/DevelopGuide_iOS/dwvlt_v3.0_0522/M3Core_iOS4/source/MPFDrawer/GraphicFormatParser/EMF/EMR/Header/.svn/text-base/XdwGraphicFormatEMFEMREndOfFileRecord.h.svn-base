/**
 * @file  XdwGraphicFormatEMFEMREndOfFileRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::EndOfFileRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMREndOfFileRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EOF_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EOF_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPalette.h"

/**
 * @brief ENHMETAEOF構造体を規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::EndOfFileRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    EndOfFileRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~EndOfFileRecord();
    
    /**
     * @brief EMREOF構造体をパースする
     *
     * パレットが存在する場合には、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! EMFデータの画素サイズ */
    XdwGraphicFormat::GDI::Palette fPalette;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * EMFデータの画素サイズを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
