/**
 * @file  XdwGraphicFormatEMFEMRPointRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PointRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRPointRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_POINT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_POINT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"

/**
 * @brief 単一の座標を扱うEMRを規定する抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PointRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PointRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~PointRecord();
    
    /**
     * @brief 座標値を格納したEMR構造体をパースする
     *
     * 座標値を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 座標を管理するクラス */
    XdwGraphicFormat::GDI::Point fPoint;

    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
