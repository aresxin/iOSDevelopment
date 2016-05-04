/**
 * @file  XdwGraphicFormatEMFEMRExtFloodFillRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ExtFloodFillRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2004-01-29
 * @version 1.0
 * $Id:
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EXT_FLOOD_FILL_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EXT_FLOOD_FILL_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約クラスのInclude */
#include "XdwGraphicFormatGDIColorRef.h"
#include "XdwGraphicFormatGDIPoint.h"
/**
 * @brief EMR_FRAMERGNを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ExtFloodFillRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExtFloodFillRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ExtFloodFillRecord();
    
    /**
     * @brief EXTFLOODFILL構造体をパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
        
protected:
    
    /********************************************/
    /* 集約 */
	long fMode;
	/*! Pointを規定するクラス */
    XdwGraphicFormat::GDI::Point fPoint;
	/*! ColorRefを規定するクラス */
    XdwGraphicFormat::GDI::ColorRef fColorRef;
	
};

#endif
