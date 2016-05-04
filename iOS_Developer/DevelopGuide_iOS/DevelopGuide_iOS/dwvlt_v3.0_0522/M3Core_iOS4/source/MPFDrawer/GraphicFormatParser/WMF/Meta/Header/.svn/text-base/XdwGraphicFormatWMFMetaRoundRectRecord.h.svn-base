/**
 * @file  XdwGraphicFormatWMFMetaRoundRectRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::RoundRectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaRoundRectRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_ROUND_RECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_ROUND_RECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIRoundRect.h"

/**
 * @brief META_ROUNDRECTを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::RoundRectRecord : public XdwGraphicFormat::WMF::Meta::Record
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
     * @brief META_ROUNDRECTをパースする
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
