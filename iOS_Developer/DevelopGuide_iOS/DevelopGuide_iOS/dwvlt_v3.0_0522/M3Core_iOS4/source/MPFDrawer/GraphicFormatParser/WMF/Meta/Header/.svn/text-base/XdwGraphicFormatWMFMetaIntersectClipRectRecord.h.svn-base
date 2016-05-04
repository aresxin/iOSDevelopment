/**
 * @file  XdwGraphicFormatWMFMetaIntersectClipRectRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::IntersectClipRectRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaIntersectClipRectRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_INTERSECT_CLIP_RECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_INTERSECT_CLIP_RECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRectRecord.h"

/**
 * @brief META_INTERSECTCLIPRECTレコードを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::IntersectClipRectRecord : public XdwGraphicFormat::WMF::Meta::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    IntersectClipRectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~IntersectClipRectRecord();
    
    /**
     * @brief META_INTERSECTCLIPRECTレコードをパースする
     *
     * 矩形を読み込み、クリッピング領域として登録する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
