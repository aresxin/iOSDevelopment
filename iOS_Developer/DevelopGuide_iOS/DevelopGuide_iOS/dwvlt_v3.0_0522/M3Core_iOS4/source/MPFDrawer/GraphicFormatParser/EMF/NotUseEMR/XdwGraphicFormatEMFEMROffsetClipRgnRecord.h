/**
 * @file  XdwGraphicFormatEMFEMROffsetClipRgn.h
 * @brief XdwGraphicFormat::EMF::EMR::OffsetClipRgnクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_OFFSET_CLIP_RGN_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_OFFSET_CLIP_RGN_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRPointRecord.h"

/**
 * @brief EMR_SETWINDOWORGEXのレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::OffsetClipRgnRecord : public XdwGraphicFormat::EMF::EMR::PointRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    OffsetClipRgnRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~OffsetClipRgnRecord();
    
    /**
     * @brief EMROFFSETCLIPRGN構造体をパースする
     *
     * 
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif
