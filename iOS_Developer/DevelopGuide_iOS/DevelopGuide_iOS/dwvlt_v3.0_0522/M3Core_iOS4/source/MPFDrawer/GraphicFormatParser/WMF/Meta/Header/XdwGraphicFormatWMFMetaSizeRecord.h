/**
 * @file  XdwGraphicFormatWMFMetaSizeRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::SizeRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaSizeRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_SIZE_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_SIZE_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDISize.h"

/**
 * @brief 単一の範囲を扱うMetaを規定する抽象クラス
 *
 */
class XdwGraphicFormat::WMF::Meta::SizeRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SizeRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SizeRecord();
    
    /**
     * @brief 範囲値を格納したMeta構造体をパースする
     *
     * 範囲値を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
    /**
     * @brief 横幅の取得
     *
     * @return 横幅
     */
    virtual long GetWidth();
    
    /**
     * @brief 縦幅の取得
     *
     * @return 縦幅
     */
    virtual long GetHeight();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 範囲を管理するクラス */
    XdwGraphicFormat::GDI::Size fSize;

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
