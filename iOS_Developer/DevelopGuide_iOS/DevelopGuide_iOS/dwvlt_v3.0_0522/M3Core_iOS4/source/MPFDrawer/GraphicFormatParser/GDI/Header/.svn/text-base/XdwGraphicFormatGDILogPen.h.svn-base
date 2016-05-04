/**
 * @file  XdwGraphicFormatGDILogPen.h
 * @brief XdwGraphicFormat::GDI::LogPenクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDILogPen.h,v 1.4 2009/12/22 08:10:55 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_LOG_PEN_H_
#define _XDW_GRAPHIC_FORMAT_GDI_LOG_PEN_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatGDILogObject.h"

/* 集約するクラスのIncludeファイル */
#include "XdwRaster.h"
#include "XdwPen.h"

/**
 * @brief GDIで定義されているLOGPEN構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::LogPen : public XdwGraphicFormat::GDI::LogObject
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LogPen();

    /**
     * @brief デストラクタ
     */
    virtual ~LogPen();

    /**
     * @brief LOGPEN構造体を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();

    /**
     * @brief ペン属性を取得する
     *
     * @return XdwPenAttribute参照
     */
    virtual XdwPenAttribute& GetPen() const;
    
    /**
     * @brief パターン属性を取得する
     *
     * @return XdwPatternAttribute参照
     */
    virtual XdwPatternAttribute& GetPattern() const;
    
protected:

    /********************************************/
    /* 集約 */

    /*! パターンを規定するクラス */
    XdwPatternAttribute fPattern;
    /*! ペン属性を管理するクラス */
    XdwPenAttribute fPen;
    
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
