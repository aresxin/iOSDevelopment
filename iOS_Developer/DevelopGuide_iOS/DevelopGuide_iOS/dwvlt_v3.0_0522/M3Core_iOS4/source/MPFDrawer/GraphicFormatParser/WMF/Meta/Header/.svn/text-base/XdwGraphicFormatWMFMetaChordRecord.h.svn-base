/**
 * @file  XdwGraphicFormatWMFMetaChordRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::ChordRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaChordRecord.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_CHORD_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_CHORD_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaCurveRecord.h"

/**
 * @brief META_CHORDを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::ChordRecord : public XdwGraphicFormat::WMF::Meta::CurveRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ChordRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ChordRecord();
    
    /**
     * @brief META_CHORDをパースする
     *
     * 円弧を読み込み、Imagerにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:

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
