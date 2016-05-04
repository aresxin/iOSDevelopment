/**
 * @file  XdwGraphicFormatWMFEnhMetaSetDIBRecord.h
 * @brief XdwGraphicFormat::WMF::EnhMeta::SetDIBRecordクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatWMFEnhMetaSetDIBRecord.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_ENH_META_SET_DIB_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_ENH_META_SET_DIB_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMeta.h"
#include "XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFEnhMetaSetRasterRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIBitmapInfo.h"

/**
 * @brief 参照されるDIBを規定するクラス
 *
 */
class XdwGraphicFormat::WMF::EnhMeta::SetDIBRecord : public XdwGraphicFormat::WMF::EnhMeta::SetRasterRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param content コンテントを管理するインターフェース
     */
    SetDIBRecord(XdwDocuWorks::ContentManager* content = XdwNull);
    
    /**
     * @brief デストラクタ
     */
    virtual ~SetDIBRecord();

    /**
     * @brief DocuWorks独自のWMF中の参照されるDIBに関するレコードをパースする
     *
     * パースしたDIBの状態は、保存する
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
    /* 集約 */
    
    /*! BITMAPINFO構造体を管理するクラス */
    XdwGraphicFormat::GDI::BitmapInfo fBitmapInfo;
    
    /********************************************/
    /* 関連 */
    
    /*! コンテントを管理するインターフェース */
    XdwDocuWorks::ContentManager* fContent;

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
