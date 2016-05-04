/**
 * @file  XdwGraphicFormat.h
 * @brief XdwGraphicFormatクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwGraphicFormat.h,v 1.4 2009/12/22 08:11:36 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_H_
#define _XDW_GRAPHIC_FORMAT_H_

/* 本パッケージで全体的に使用するIncludeファイル */
#include "System/SystemIF/XdwError.h"
#include "System/SystemIF/XdwNew.h"
#include "System/SystemIF/XdwConfig.h"

/**
 * @brief DocuWorksファイル中のグラフィックスフォーマットをパースするパッケージ
 */
class XdwGraphicFormat
{
public:

    /********************************************/
    /* 列挙型 */

    /*! パース方法の指定 */
    enum ParseMode{
        /*! 一斉にコンテントをパースする */
        ALL_MODE,
        /*! コンテントを指定されたレコード数、ライン数でパースする <br>
		イメージ描画には，指定ライン数毎に描画される */
		LEG_MODE
    };
    
    /********************************************/
    /* クライアントに提示するクラス */

    /*! クライアントがグラフィックフォーマットのパース方法を選択するための抽象クラス */
    class ParsingStrategy;
    /*! グラフィックフォーマットを完全にパースしてXdwBridgeDrawIFインターフェースに渡すクラス */
    class FullParser;
    /*! グラフィックフォーマット中に存在するテキストだけを抽出するクラス */
    class TextFilter;
    /*! グラフィックフォーマット中のサムネイルをパースしてXdwBridgeDrawIFインターフェースに渡すクラス */
    class ThumbnailParser;
    
    /*! セットされたグラフィックフォーマットのデータの情報を取得するためのインターフェース */
    class Info;

    /********************************************/
    /* クライアントにしないクラス */
    
    /*! セットされたグラフィックフォーマットのデータを読み込むための抽象クラス */
    class Parser;
    
    /********************************************/
    /* パッケージ */
    
    /*! GDIで使用される構造体を管理するパッケージ */
    class GDI;
    /*! EMFを管理するパッケージ */
    class EMF;
    /*! WMFを管理するパッケージ */
    class WMF;
    /*! ラスターデータを管理するパッケージ */
    class Raster;
    
};

#endif
