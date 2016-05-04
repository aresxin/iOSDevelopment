/**
 * @file  XdwGraphicFormatEMFEMRPolygonRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolygonRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRPolygonRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_POLYGON_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_POLYGON_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPolyRecord.h"

/**
 * @brief EMR_POLYGONを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PolygonRecord : public XdwGraphicFormat::EMF::EMR::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     */
    PolygonRecord(XdwGraphicFormat::GDI::ReadMode mode);

    /**
     * @brief デストラクタ
     */
    virtual ~PolygonRecord();
    
protected:

    /********************************************/
    /* メソッド */
    
    /**
     * @brief 座標配列をPolygon描画で渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Draw();
};

#endif
