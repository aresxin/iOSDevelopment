/**
 * @file  XdwGraphicFormatWMFEnhMeta.h
 * @brief XdwGraphicFormat::WMF::EnhMetaクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwGraphicFormatWMFEnhMeta.h,v 1.4 2009/12/22 08:11:37 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_ENH_META_H_
#define _XDW_GRAPHIC_FORMAT_WMF_ENH_META_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "GraphicFormatParser/WMF/Header/XdwGraphicFormatWMF.h"

/**
 * @brief DocuWorks独自の拡張されたWMFのレコードを管理するパッケージ
 */
class XdwGraphicFormat::WMF::EnhMeta
{
public:

    /********************************************/
    /* 列挙型 */

    /*! GDIのEscapeコール */
    enum EscapeCall{
        ESCAPE_CALL_COMMENT = 15
    };
    
    /*! Escapeを利用した拡張命令 */
    enum TYPE_ID{
        /*! 参照型ラスターの描画の識別子 */
        TYPE_STRETCH_DIB_REUSE = 0x00015744,
        /*! 参照型DIBの識別子 */
        TYPE_SET_DIB = 0x00025744,
        /*! 参照型JPEGの識別子 */
        TYPE_SET_JPEG = 0x01025744,
        /*! 参照型ラスターの描画の識別子 */
        TYPE_STRETCH_DIB_REF = 0x02025744,
        /*! 複数回のPatBltの識別子 */
        TYPE_POLY_POLY_PAT_BLT = 0x03025744
    };
    
    /********************************************/
    /* クラス */
    
    /*! 参照されるラスターデータを規定する汎化クラス */
    class SetRasterRecord;
    /*! 参照されるDIBを規定するクラス */
    class SetDIBRecord;
    /*! 参照されるJpegを規定するクラス */
    class SetJpegRecord;
    /*! ラスターデータを参照して、描画するクラス */
    class StretchDIBRefRecord;
    /*! ラスターデータを参照して、描画するクラス */
    class StretchDIBReuseRecord;
    /*! 複数回のPatBltを表すクラス */
    class PolyPolyPatBltRecord;
    
};

#endif
