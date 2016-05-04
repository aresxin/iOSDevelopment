/**
 * @file  XdwGraphicFormatWMFMetaExtTextOutRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::ExtTextOutRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaExtTextOutRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_EXT_TEXT_OUT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_EXT_TEXT_OUT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIExtText.h"

/**
 * @brief META_EXTTEXTOUTを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::Meta::ExtTextOutRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExtTextOutRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~ExtTextOutRecord();
    
    /**
     * @brief META_EXTTEXTOUTをパースする
     *
     * 拡張テキスト描画命令をパースして、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    
    /********************************************/
    /* 集約 */
    
    /*! 拡張テキスト描画命令を管理するクラス */
    XdwGraphicFormat::GDI::ExtText fExtText;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 集約や属性の初期化
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
};

#endif
