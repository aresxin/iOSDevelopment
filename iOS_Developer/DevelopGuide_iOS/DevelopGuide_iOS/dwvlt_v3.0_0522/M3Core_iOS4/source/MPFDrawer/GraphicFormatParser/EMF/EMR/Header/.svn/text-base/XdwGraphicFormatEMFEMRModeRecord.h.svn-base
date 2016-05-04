/**
 * @file  XdwGraphicFormatEMFEMRModeRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ModeRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRModeRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_MODE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_MODE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/**
 * @brief EMRの描画属性を規定する抽象クラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ModeRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ModeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ModeRecord();
    
    /**
     * @brief 描画属性を格納したEMR構造体をパースする
     *
     * 描画属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 属性 */
    
    /*! 描画属性 */
    long fMode;

    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 描画属性を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
