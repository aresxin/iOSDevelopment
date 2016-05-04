/**
 * @file  XdwGraphicFormatGDIXForm.h
 * @brief XdwGraphicFormat::GDI::XFormクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIXForm.h,v 1.4 2009/12/22 08:10:55 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_XFORM_H_
#define _XDW_GRAPHIC_FORMAT_GDI_XFORM_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"

/* 親クラスのIncludeファイル */
#include "ImagerBridge/BridgeIF/XdwMatrix.h"

/**
 * @brief GDIで定義されているXFORM構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::XForm : public XdwMatrix
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    XForm();

    /**
     * @brief デストラクタ
     */
    virtual ~XForm();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary バイナリデータ管理インターフェースのインスタンス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary);
    
    /**
     * @brief 座標値を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();

    /**
     * @brief XForm構造体のByte数を取得する
     *
     * @return XForm構造体のByte数
     */
    static long GetBytes();
    
    /**
     * @brief 正則行列の判定
     *
     * @retval true 正則行列
     * @retval false 非正則行列
     */
    virtual bool IsRegular();
     
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! バイナリデータ管理インターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;
};

#endif
