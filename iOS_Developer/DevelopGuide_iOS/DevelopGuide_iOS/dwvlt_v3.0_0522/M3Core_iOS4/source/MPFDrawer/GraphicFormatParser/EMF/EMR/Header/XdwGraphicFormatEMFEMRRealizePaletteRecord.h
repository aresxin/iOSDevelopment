/**
 * @file  XdwGraphicFormatEMFMetaRealizePaletteRecord.h
 * @brief XdwGraphicFormat::EMF::Meta::RealizePaletteRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2002-12-16
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRRealizePaletteRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMF_REALIZE_PALETTE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMF_REALIZE_PALETTE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRObjectRecord.h"

/**
 * @brief EMR_REALIZEPALETTEを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::RealizePaletteRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RealizePaletteRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RealizePaletteRecord();
    
    /**
     * @brief EMR_REALIZEPALETTEレコードをパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

};

#endif
