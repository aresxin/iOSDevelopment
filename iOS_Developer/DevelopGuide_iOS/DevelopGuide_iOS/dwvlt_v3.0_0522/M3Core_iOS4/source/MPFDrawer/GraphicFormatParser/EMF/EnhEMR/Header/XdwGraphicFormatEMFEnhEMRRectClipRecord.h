/**
 * @file  XdwGraphicFormatEMFEnhEMRRectClipRecord.h
 * @brief XdwGraphicFormat::EMF::EnhEMR::RectClipRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEnhEMRRectClipRecord.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_ENH_EMR_RECT_CLIP_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_ENH_EMR_RECT_CLIP_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEnhEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRectRecord.h"

/**
 * @brief 指定された矩形をクリッピング領域とするクラス
 *
 */
class XdwGraphicFormat::EMF::EnhEMR::RectClipRecord : public XdwGraphicFormat::EMF::EMR::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    RectClipRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~RectClipRecord();
    
    /**
     * @brief 指定された矩形をクリッピング領域とする拡張レコードをパーする
     *
     * 矩形を読み込み、クリッピング領域にする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
