/**
 * @file  XdwGraphicFormatWMFEnhMetaSetJpegRecord.h
 * @brief XdwGraphicFormat::WMF::EnhMeta::SetJpegRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFEnhMetaSetJpegRecord.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_ENH_META_SET_JPEG_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_ENH_META_SET_JPEG_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMetaSetRasterRecord.h"

/* 関連するクラスのIncludeファイル */
#include "XdwDocuWorksContentManager.h"

/**
 * @brief 参照されるJpegを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::EnhMeta::SetJpegRecord : public XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param pd_nth 配列指定型PDを管理するインターフェース
     */
    SetJpegRecord(XdwDocuWorks::ContentManager::PDNthInfo* pd_nth = XdwNull);
    
    /**
     * @brief デストラクタ
     */
    virtual ~SetJpegRecord();

    /**
     * @brief DocuWorks独自のWMF中の参照されるJpegに関するレコードをパースする
     *
     * 取得したJpegの状態は、保存する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
    /**
     * @brief ラスター属性をセットする
     *
     * @param attribute セットされる属性管理のインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetAttribute(XdwRasterImageAttribute* attribute);
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! コンテントを管理するインターフェース */
    XdwDocuWorks::ContentManager::PDNthInfo* fPDNth;

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
