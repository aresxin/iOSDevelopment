/**
 * @file  XdwGraphicFormatEMFEMRExtTextOutRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ExtTextOutRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRExtTextOutRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EXT_TEXT_OUT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EXT_TEXT_OUT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIExtText.h"

/**
 * @brief EMREXTTEXTOUTA構造体およびEMREXTTEXTOUTW構造体を規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ExtTextOutRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExtTextOutRecord(XdwGraphicFormat::GDI::CharacterCodeMode mode);
    
    /**
     * @brief デストラクタ
     */
    virtual ~ExtTextOutRecord();
    
    /**
     * @brief EMREXTTEXTOUTA構造体およびEMREXTTEXTOUTW構造体をパースする
     *
     * 拡張テキスト描画命令をパースして、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 拡張テキスト描画命令を管理するクラス */
    XdwGraphicFormat::GDI::ExtText fExtText;

    /********************************************/
    /* 属性 */

    /*! 文字コードの指定 */
    XdwGraphicFormat::GDI::CharacterCodeMode fCodeMode;
    
    /*! グラフィックモード */
    long fGraphicMode;
    /*! 水平方向への比率 */
    float fXScale;
    /*! 垂直方向への比率 */
    float fYScale;
    
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
