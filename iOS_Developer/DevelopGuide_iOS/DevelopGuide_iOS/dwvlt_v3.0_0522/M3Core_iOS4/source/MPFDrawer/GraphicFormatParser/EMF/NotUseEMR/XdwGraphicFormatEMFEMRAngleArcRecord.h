/**
 * @file  XdwGraphicFormatEMFEMRAngleArcRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::AngleArcRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-30
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_ANGLE_ARC_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_ANGLE_ARC_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"

/**
 * @brief EMRANGLEARC構造体を規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::AngleArcRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    AngleArcRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~AngleArcRecord();
    
    /**
     * @brief AngleArc構造体をパースする
     *
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
    /* 属性 */

    /*! Radius */
	long   fRadius;
	/*! Start Angle*/
	float   fStartAngle;
	/*! Sweep Angle*/
	float   fSweepAngle;

	bool fInitializeFlag;
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 集約や属性の初期化
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
