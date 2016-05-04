/**
 * @file  XdwGraphicFormatEMFEMRResizePaletteRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ResizePaletteRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2004-01-29
 * @version 1.0
 * $Id:
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_RESIZE_PALETTE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_RESIZE_PALETTE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/**
 * @brief EMR_RESIZEPALETTEを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ResizePaletteRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     */
    ResizePaletteRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ResizePaletteRecord();
    
    /**
     * @brief EMRRESIZEPALETTE構造体をパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
        
protected:
    
    /********************************************/
    /* 属性*/
	/*! パレットハンドル*/
	long fPaletteHandle;
	/*! Entry */
	long fEntry;
};

#endif
