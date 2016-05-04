/**
 * @file  XdwGraphicFormatEMFEMRPolyPolygonRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolyPolygonRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRPolyPolygonRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_PolyPolygon_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_PolyPolygon_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPolyRecord.h"

/**
 * @brief EMR_PolyPolygonを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PolyPolygonRecord : public XdwGraphicFormat::EMF::EMR::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     */
    PolyPolygonRecord(XdwGraphicFormat::GDI::ReadMode mode);

    /**
     * @brief デストラクタ
     */
    virtual ~PolyPolygonRecord();
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
    /* メソッド */
    
    /**
     * @brief 座標配列をPolyPolygon描画で渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Draw();
private:
    /* 座標配列を一時的に格納するクラス */
    XdwPointVector fTmpPoints;

};

#endif
