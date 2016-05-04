/**
 * @file  XdwGraphicFormatEMFEMRRectangleRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::RectangleRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRRectangleRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_RECTANGLE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_RECTANGLE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRectRecord.h"

/**
 * @brief EMR_RECTANGLEのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::RectangleRecord : public XdwGraphicFormat::EMF::EMR::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RectangleRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RectangleRecord();
    
    /**
     * @brief EMRRECTANGLE構造体をパースする
     *
     * 矩形を読み込み、描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
