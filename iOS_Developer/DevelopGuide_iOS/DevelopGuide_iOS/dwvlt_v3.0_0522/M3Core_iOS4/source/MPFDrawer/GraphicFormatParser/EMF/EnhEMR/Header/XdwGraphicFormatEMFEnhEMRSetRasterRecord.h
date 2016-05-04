/**
 * @file  XdwGraphicFormatEMFEnhEMRSetRasterRecord.h
 * @brief XdwGraphicFormat::EMF::EnhEMR::SetRasterRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEnhEMRSetRasterRecord.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_ENH_EMR_SET_RASTER_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_ENH_EMR_SET_RASTER_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEnhEMR.h"
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"

/* 依存するクラスの宣言 */
class XdwRasterImageAttribute;

/**
 * @brief 参照されるラスターデータを規定する汎化クラス
 *
 */
class XdwGraphicFormat::EMF::EnhEMR::SetRasterRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetRasterRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~SetRasterRecord();
    
    /**
     * @brief ラスター属性をセットする
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetAttribute(XdwRasterImageAttribute* attribute) = 0;

    /**
     * @brief ラスターデータを取得する
     *
     * @return ラスターデータが格納されているXdwDocuWorks::BinaryInterfaceインターフェースのインスタンス<br>
     *         クライアントの削除は認めない
     */
    virtual XdwDocuWorks::BinaryInterface* GetBinaryData();
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! ラスターデータが格納されているXdwDocuWorks::BinaryInterfaceインターフェース */
    XdwDocuWorks::BinaryInterface* fRasterData;
};

#endif
