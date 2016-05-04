/**
 * @file  XdwGraphicFormatEMFEMRPolyTextOutRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::PolyTextOutRecordクラスの定義
 *
 * @author Yasuhiro Ito (Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2004-3-12
 * @version 1.0
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_POLY_TEXT_OUT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_POLY_TEXT_OUT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPolyText.h"

/**
 * @brief EMREXTTEXTOUTA構造体およびEMREXTTEXTOUTW構造体を規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::PolyTextOutRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    PolyTextOutRecord(XdwGraphicFormat::GDI::CharacterCodeMode mode);
    
    /**
     * @brief デストラクタ
     */
    virtual ~PolyTextOutRecord();
    
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
    XdwGraphicFormat::GDI::PolyText fPolyText;

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
	/*! Textの数*/
	long fStrings;
    
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
