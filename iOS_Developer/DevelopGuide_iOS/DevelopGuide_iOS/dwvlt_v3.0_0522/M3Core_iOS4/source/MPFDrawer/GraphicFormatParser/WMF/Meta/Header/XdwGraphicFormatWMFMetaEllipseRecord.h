/**
 * @file  XdwGraphicFormatWMFMetaEllipseRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::EllipseRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaEllipseRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_ELLIPSE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_ELLIPSE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRectRecord.h"

/**
 * @brief META_ELLIPSEレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::EllipseRecord : public XdwGraphicFormat::WMF::Meta::RectRecord
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
     * @brief META_ELLIPSEレコードをパースする
     *
     * 矩形を読み込み、外接する楕円を描画する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
