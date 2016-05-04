/**
 * @file  XdwGraphicFormatEMFEMRExtSelectClipRgnRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ExtSelectClipRgnRecordクラスの定義
 *
 * @author DPCS 商開統 S開 S開部 第3S開発 TDG Yasuhiro Ito(Yasuhiro.Ito@fujixerox.co.jp)
 * @date 2002-12-11
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEMRExtSelectClipRgnRecord.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 *
 * @todo MSDNと違う解釈をしている部分あり、そうしないと正常に表示できない
 * @date 2004-03-12 Yasuhiro Ito MSDNと異なる解釈ができるように変更
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_EXT_SELECT_CLIP_RGN_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_EXT_SELECT_CLIP_RGN_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRectRecord.h"

/**
 * @brief EMR_EXTSELECTCLIPRGNを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ExtSelectClipRgnRecord : public XdwGraphicFormat::EMF::EMR::RectRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     *
     * @param generator 大きなバイナリデータを作成するクラス
     */
    ExtSelectClipRgnRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ExtSelectClipRgnRecord();
    
    /**
     * @brief EMR_EXTSELECTCLIPRGN構造体をパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();

	/**
     * @brief インスタンスを初期化する
     *
     * @param binary EMFが格納されているバイナリデータ管理インターフェースのインスタンス
     * @param bridge Imagerへアクセスするためのインターフェースのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary, XdwBridgeDrawIF* bridge);
        
protected:
    
    /********************************************/
    /* 集約 */
        
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
