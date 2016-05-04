/**
 * @file  XdwGraphicFormatEMFEMRRoundRectRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::RoundRectRecordクラスの定義
 *
  * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-30
 * @version 1.0
 * $Id :
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_ROUND_RECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_ROUND_RECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIRoundRect.h"

/**
 * @brief EMR_ROUNDRECTを規定する抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::RoundRectRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RoundRectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RoundRectRecord();
    
    /**
     * @brief EMR_ROUNDRECTをパースする
     *
     * 角丸矩形を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 角丸矩形を規定するクラス */
    XdwGraphicFormat::GDI::RoundRect fRoundRect;
    
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
