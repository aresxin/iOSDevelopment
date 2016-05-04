/**
 * @file  XdwGraphicFormatGDIExtLogPen.h
 * @brief XdwGraphicFormat::GDI::ExtLogPenクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIExtLogPen.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_EXT_LOG_PEN_H_
#define _XDW_GRAPHIC_FORMAT_GDI_EXT_LOG_PEN_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatGDILogObject.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDILogBrush.h"
#include "XdwPen.h"

/**
 * @brief GDIで定義されているEXTLOGPEN構造体を読み込むクラス
 */
class XdwGraphicFormat::GDI::ExtLogPen : public XdwGraphicFormat::GDI::LogObject
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ExtLogPen();

    /**
     * @brief デストラクタ
     */
    virtual ~ExtLogPen();

    /**
     * @brief EXTLOGPEN構造体を読み込む
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
    /* 列挙型 */

    /*! マスク値 */
    enum MaskValue{
        /*! スタイル */
        PEN_STYLE_MASK = 0x0000000F,
        /*! 終端 */
        END_CAP_MASK = 0x00000F00,
        /*! 接続 */
        JOIN_CAP_MASK = 0x0000F000
    };
    
    /********************************************/
    /* 集約 */

    /*! LOGBURSH構造体を管理するクラス */
    XdwGraphicFormat::GDI::LogBrush fLogBrush;
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

    /**
     * @brief 属性を初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode InitializeAttribute();
    

};

#endif
