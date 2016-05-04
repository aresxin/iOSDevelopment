/**
 * @file  XdwGraphicFormatEMFEMRSelectClipPathRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SelectClipPathRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRSelectClipPathRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SELECT_CLIP_PATH_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SELECT_CLIP_PATH_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRModeRecord.h"

/**
 * @brief EMR_SETPOLYFILLMODEのレコードを規定するクラス
 */
class XdwGraphicFormat::EMF::EMR::SelectClipPathRecord : public XdwGraphicFormat::EMF::EMR::ModeRecord
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SelectClipPathRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SelectClipPathRecord();

    /**
     * @brief EMRSELECTCLIPPATH構造体をパースする
     *
     * クリッピングモードを読み込み、Imagerに新たなクリップ領域をセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

protected:
    
};

#endif
