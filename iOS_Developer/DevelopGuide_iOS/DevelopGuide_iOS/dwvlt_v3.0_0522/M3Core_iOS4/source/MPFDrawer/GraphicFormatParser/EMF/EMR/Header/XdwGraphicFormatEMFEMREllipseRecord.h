/**
 * @file  XdwGraphicFormatEMFEMREllipseRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::EllipseRecordクラスの定義
 *
 * @author DPSC SD SD3 TDG Yasuhiro Ito (yasuhiro.ito@fujixerox.co.jp)
 * @date 2003-8-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_ELLIPSE_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_ELLIPSE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRectRecord.h"

/**
 * @brief EMR_ELLIPSEのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::EllipseRecord : public XdwGraphicFormat::EMF::EMR::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    EllipseRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~EllipseRecord();
    
    /**
     * @brief EMRRECTANGLE構造体をパースする
     *
     * 矩形を読み込み、描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
	/**
	* @brief 座標値正規化する
	*
	* @return bool
	*/
	virtual void Regulate(XdwGraphicFormat::GDI::Rectangle &rect);
};

#endif
