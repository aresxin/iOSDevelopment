/**
 * @file  XdwGraphicFormatEMFEMRPolyDrawRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolyDrawRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_POLY_DRAW__RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_POLY_DRAW__RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"
#include "XdwGraphicFormatEMFEMRPolyRecord.h"
/* 集約*/
#include "XdwGraphicFormatGDIPoint.h"
#include "XdwGraphicFormatGDIRectangle.h"
/**
 * @brief POLYDRAWレコードを規定するクラス
 * 
 * PolyDraw16もかねる
 */
class XdwGraphicFormat::EMF::EMR::PolyDrawRecord : public XdwGraphicFormat::EMF::EMR::PolyRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     * @param XdwGraphicFormat::GDI::ReadMode
     */
    PolyDrawRecord(XdwGraphicFormat::GDI::ReadMode mode);

    /**
     * @brief デストラクタ
     */
    virtual ~PolyDrawRecord();
    
    /**
     * @brief Polyレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

	/*集約*/
	/*
	Array of values that specifies how each point in the aptl array is used. This member can be one of the following values: PT_MOVETO, PT_LINETO, or PT_BEZIERTO. The PT_LINETO or PT_BEZIERTO value can be combined with the PT_CLOSEFIGURE value by using the bitwise-XOR operator.
	  */
	unsigned char fAbTypes;
	
};

#endif
