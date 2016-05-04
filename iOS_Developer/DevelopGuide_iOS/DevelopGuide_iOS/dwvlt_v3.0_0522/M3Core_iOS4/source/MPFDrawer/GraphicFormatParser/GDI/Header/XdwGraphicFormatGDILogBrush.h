/**
 * @file  XdwGraphicFormatGDILogBrush.h
 * @brief XdwGraphicFormat::GDI::LogBrushクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDILogBrush.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_LOG_BRUSH_H_
#define _XDW_GRAPHIC_FORMAT_GDI_LOG_BRUSH_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatGDILogObject.h"

/* 集約するクラスのIncludeファイル */
#include "XdwRaster.h"

/**
 * @brief GDIで定義されているLOGBRUSH構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::LogBrush : public XdwGraphicFormat::GDI::LogObject
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LogBrush();

    /**
     * @brief デストラクタ
     */
    virtual ~LogBrush();

    /**
     * @brief LOGBRUSH構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
    
    /**
     * @brief パターン属性を取得する
     *
     * @return XdwPatternAttribute参照
     */
    virtual XdwPatternAttribute& Get() const;
    
protected:

    /********************************************/
    /* 集約 */

    /*! パターンを規定するクラス */
    XdwPatternAttribute fPattern;

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
