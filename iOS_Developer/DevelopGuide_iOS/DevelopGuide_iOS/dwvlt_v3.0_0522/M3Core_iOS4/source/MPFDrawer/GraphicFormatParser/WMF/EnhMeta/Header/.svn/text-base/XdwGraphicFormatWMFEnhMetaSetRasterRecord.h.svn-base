/**
 * @file  XdwGraphicFormatWMFEnhMetaSetRasterRecord.h
 * @brief XdwGraphicFormat::WMF::EnhMeta::SetRasterRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFEnhMetaSetRasterRecord.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_ENH_META_SET_RASTER_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_ENH_META_SET_RASTER_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMeta.h"
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 依存するクラスの宣言 */
class XdwRasterImageAttribute;

/**
 * @brief 参照されるラスターデータを規定する汎化クラス
 *
 */
class XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord : public XdwGraphicFormat::WMF::Meta::Record
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
