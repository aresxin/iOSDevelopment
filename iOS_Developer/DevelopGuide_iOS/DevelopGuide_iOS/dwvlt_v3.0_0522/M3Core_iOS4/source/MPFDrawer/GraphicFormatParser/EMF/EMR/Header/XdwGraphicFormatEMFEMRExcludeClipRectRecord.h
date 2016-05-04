/**
 * @file  XdwGraphicFormatEMFEMFExcludeClipRectRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ExcludeClipRectRecordクラス
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2002-12-20
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRExcludeClipRectRecord.h,v 1.5 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */



#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EXCLUDE_CLIP_RECT_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EXCLUDE_CLIP_RECT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRectRecord.h"

/**
 * @brief EMR_EXCLUDECLIPRECTレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ExcludeClipRectRecord : public XdwGraphicFormat::EMF::EMR::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExcludeClipRectRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ExcludeClipRectRecord();
    
    /**
     * @brief EMR_EXCLUDECLIPRECTレコードをパースする
     *
     * 矩形を読み込み、クリッピング領域として登録する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
};

#endif

