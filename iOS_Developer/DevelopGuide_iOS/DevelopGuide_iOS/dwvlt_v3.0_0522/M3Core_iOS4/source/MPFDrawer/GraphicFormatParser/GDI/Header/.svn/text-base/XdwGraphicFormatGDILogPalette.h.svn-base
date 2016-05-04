/**
 * @file  XdwGraphicFormatGDILogPalette.h
 * @brief XdwGraphicFormat::GDI::LogPaletteクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDILogPalette.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_LOG_PALETTE_H_
#define _XDW_GRAPHIC_FORMAT_GDI_LOG_PALETTE_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatGDILogObject.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPalette.h"

/**
 * @brief GDIで定義されているLOGPALETTE構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::LogPalette : public XdwGraphicFormat::GDI::LogObject
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LogPalette();

    /**
     * @brief デストラクタ
     */
    virtual ~LogPalette();

    /**
     * @brief LOGPALETTE構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
    /**
     * @brief パレット属性を取得する
     *
     * @return XdwColorPalette参照
     */
    virtual XdwColorPalette& Get() const;
    
protected:

    /********************************************/
    /* 集約 */

    /*! パレットを規定するクラス */
    XdwGraphicFormat::GDI::Palette fPalette;

    /********************************************/
    /* メソッド */

    /**
     * @brief 初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
};

#endif
