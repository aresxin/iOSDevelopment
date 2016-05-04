/**
 * @file  XdwGraphicFormatGDI.h
 * @brief XdwGraphicFormat::GDIクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwGraphicFormatGDI.h,v 1.4 2009/12/22 08:10:56 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_H_
#define _XDW_GRAPHIC_FORMAT_GDI_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "GraphicFormatParser/Include/XdwGraphicFormat.h"

/**
 * @brief GDIで使用される構造体を管理するパッケージ
 */
class XdwGraphicFormat::GDI
{
public:

    /********************************************/
    /* クラス */

    /*! 読み込み方法 */
    enum ReadMode{
        /*! 32Bitで読み込み */
        BIT_32 = 0x00,
        /*! 16Bitでの読み込み */
        BIT_16 = 0x02,
        /*! 8Bit差分での読み込み */
        BIT_8 = 0x04,
        /*! 4Bitまたは8Bit差分での読み込み */
        BIT_4 = 0x08,
        /*! 16Bitで逆順での読み込み */
        BIT_16_INVERT = 0x10,
    };

    /*! 文字コード */
    enum CharacterCodeMode{
        /*! Shift-JISなど */
        MULTIBYTE_MODE,
        /*! UNICODE */
        UNICODE_MODE
    };

    /*! POINT構造体を読み込むクラス */
    class Point;
    /*! SIZE構造体を読み込むクラス */
    class Size;
    /*! RECT構造体を読み込むクラス */
    class Rectangle;
    /*! 円弧を読み込むくラス */
    class Ellipse;
    /*! 角丸矩形を読み込みクラス */
    class RoundRect;
    /*! XFORM構造体を読み込むクラス */
    class XForm;

    /*! POINT構造体の配列を読み込む関数オブジェクト */
    class ReadPointArray;

    /*! Windows中の色を読み込むクラス */
    class ColorRef;
    /*! パレットを規定するクラス */
    class Palette;

    /*! LogXXX構造体の読み込み抽象クラス */
    class LogObject;
    /*! LOGBRUSH構造体の読み込みクラス */
    class LogBrush;
    /*! LOGPEN構造体の読み込みクラス */
    class LogPen;
    /*! LOGFONT構造体を読み込むクラス */
    class LogFont;
    /*! LOGPALETTE構造体を読み込むクラス */
    class LogPalette;
    /*! EXTLOGPEN構造体を読み込むクラス */
    class ExtLogPen;

    /*! BITMAPINFO構造体を読み込むクラス */ 
    class BitmapInfo;
    /*! BITMAPINFOHEADER構造体を読み込むクラス */
    class BitmapInfoHeader;
    
    /*! 拡張テキスト描画命令を扱う構造体のクラス */
    class ExtText;

};

#endif
