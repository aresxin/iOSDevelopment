/**
 * @file  XdwGraphicFormatEMFEMRPolyPolygonRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolyPolygonRecordクラスの定義
 *
 * @author Yasuhiro.ito@fujixerox.co.jp
 * @date 2003-1-27
 * @version 1.0
 * $Id :
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_PolyPolyline_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_PolyPolyline_RECORD_H_

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPolyRecord.h"

/**
 * @brief EMR_PolyPolylineを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PolyPolylineRecord :public XdwGraphicFormat::EMF::EMR::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     */
    PolyPolylineRecord(XdwGraphicFormat::GDI::ReadMode mode);

    /**
     * @brief デストラクタ
     */
    virtual ~PolyPolylineRecord();
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
     * @brief 座標配列をPolyPolyline描画で渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Draw();
private:

    /*! 座標配列を一時的に格納するクラス */
    XdwPointVector fTmpPoints;

};

#endif
