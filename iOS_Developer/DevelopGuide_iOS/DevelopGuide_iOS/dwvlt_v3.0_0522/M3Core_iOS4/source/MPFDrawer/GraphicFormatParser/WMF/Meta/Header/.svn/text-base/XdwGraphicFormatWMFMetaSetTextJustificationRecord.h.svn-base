/**
 * @file  XdwGraphicFormatWMFMetaSetTextJustificationRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SetTextJustificationRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSetTextJustificationRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SET_TEXT_JUSTIFICATION_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SET_TEXT_JUSTIFICATION_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/**
 * @brief META_SETTEXTJUSTIFICATIONを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SetTextJustificationRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetTextJustificationRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetTextJustificationRecord();
    
    /**
     * @brief META_SETTEXTJUSTIFICATIONをパースする
     *
     * テキストの水平調整値を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
};

#endif
