/**
 * @file  XdwGraphicFormatEMFEMRArcRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ArcRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_ARC_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_ARC_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 集約*/
#include "XdwGraphicFormatGDIPoint.h"
#include "XdwGraphicFormatGDIRectangle.h"
/**
 * @brief ARCレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ArcRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ArcRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ArcRecord();
    
    /**
     * @brief ARCレコードをパースする
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

    /**
	 * @brief レコードの属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
	
	/*集約*/

	// 描画する領域
	XdwGraphicFormat::GDI::Rectangle fBox;
	//最初の放射直線の端点
	XdwGraphicFormat::GDI::Point fStart;
	//2番目の放射直線の端点
	XdwGraphicFormat::GDI::Point fEnd;
	
};

#endif
