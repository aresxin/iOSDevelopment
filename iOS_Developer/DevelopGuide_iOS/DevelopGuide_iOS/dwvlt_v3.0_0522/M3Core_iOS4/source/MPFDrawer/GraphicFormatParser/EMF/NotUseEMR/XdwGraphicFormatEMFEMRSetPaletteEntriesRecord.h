/**
 * @file  XdwGraphicFormatEMFEMRSetPaletteEntriesRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetPaletteEntriesRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2004-01-29
 * @version 1.0
 * $Id:
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_PALETTEENTRIES_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_PALETTEENTRIES_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約クラスのInclude */
#include "XdwGraphicFormatGDIPalette.h"

/**
 * @brief EMR_FRAMERGNを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetPaletteEntriesRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    SetPaletteEntriesRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetPaletteEntriesRecord();
    
    /**
     * @brief EMRCREATEPEN構造体をパースする
     *
     * パレット属性を読み込んで、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
        
protected:
    
    /********************************************/
    /* 集約 */
	//Palette handle index. 
	long fPaletteHandle;
	//Index of first entry to set. 	
	long fIndexOfEntry;
	// Number of entries.
	long fEntries;
	/*! パレットを規定するクラス */
    XdwGraphicFormat::GDI::Palette fPaletteEntries;	
};

#endif
