/**
 * @file  XdwGraphicFormatEMFEMRCreateDIBPatternBrushPtRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::CreateDIBPatternBrushPtRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRCreateDIBPatternBrushPTRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_DIB_PATTERN_BRUSH_PT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_CREATE_DIB_PATTERN_BRUSH_PT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRasterObjectRecord.h"

/**
 * @brief EMR_CREATEDIBPATTERNBRUSHPTを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::CreateDIBPatternBrushPTRecord : public XdwGraphicFormat::EMF::EMR::RasterObjectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    CreateDIBPatternBrushPTRecord(XdwDataObject::Base::Generator* generator);

    /**
     * @brief デストラクタ
     */
    virtual ~CreateDIBPatternBrushPTRecord();
    
    /**
     * @brief EMRCREATEDIBPATTERNBRUSHPT構造体をパースする
     *
     * ブラシ属性であるラスターパターンを読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
};

#endif
