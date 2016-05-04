/**
 * @file  XdwGraphicFormatEMFEMRPolylineRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolylineRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRPolylineRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_POLYLINE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_POLYLINE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPolyRecord.h"

/**
 * @brief EMR_POLYLINEを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PolylineRecord : public XdwGraphicFormat::EMF::EMR::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param mode XdwGraphicFormat::GDI::ReadMode参照
     * @param update 現在位置の更新フラグ
     * @param move 現在位置をセットするかのフラグ
     * @param close パスを閉じるかのフラグ
     */
    PolylineRecord(XdwGraphicFormat::GDI::ReadMode mode, bool update, bool move = false, bool close = false);

    /**
     * @brief デストラクタ
     */
    virtual ~PolylineRecord();
    
protected:

    /********************************************/
    /* 属性 */

    /*! 現在位置の更新フラグ */
    bool fUpdateFlag;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 座標配列をPolyline描画で渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Draw();
};

#endif
