/**
 * @file  XdwDocuWorks.h
 * @brief XdwDocuWorksクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorks.h,v 1.4 2009/12/22 08:11:15 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_H_
#define _XDW_DOCUWORKS_H_

/* 本パッケージで全体的に使用するIncludeファイル */
#include "System/SystemIF/XdwError.h"
#include "System/SystemIF/XdwNew.h"
#include "System/SystemIF/XdwConfig.h"

/**
 * @brief DocuWorksファイルフォーマットへの操作をパッケージ化する
 * 
 * 提供するモジュールとして
 * DocuWorksファイルをパースするクラスや
 * DocuWorksファイルの情報を取得するためのインターフェースを規定する
 */
class XdwDocuWorks
{
public:

    /********************************************/
    /* クラス */

    /*! DocuWorksファイルフォーマットをパースするクラス */
    class Parser;

    /*! ファイル情報を取得するためのインターフェース */
    class FileInfo;
    /*! ページ情報を取得するためのインターフェース */
    class PageInfo;
    /*! コンテント情報を取得するためのインターフェース */
    class ContentInfo;
    /*! バイナリデータにアクセスするためのインターフェース */
    class BinaryInterface;
    /*! コンテント情報にアクセスするためのインターフェース */
    class ContentManager;
    
    /*! バイナリデータを管理するクラス */
    class BinaryManager;
    /*! ファイル構造をパースするクラス */
    class FileParser;
    /*! グラフィックデータをパースするクラス */
    class GraphicParser;
    
    /********************************************/
    /* パッケージ */
    
    /*! バイナリデータにアクセスするパッケージ */
    class Access;
    /*! DocuWorksファイルフォーマットをパースするパッケージ */
    class FileFormat;
    /*! DocuWorksファイル中のグラフィックスフォーマットをパースするパッケージ */
    class GraphicFormat;

};

#endif
