/**
 * @file  XdwDocuWorksPageInfo.h
 * @brief XdwDocuWorks::PageInfoインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksPageInfo.h,v 1.4 2009/12/22 08:11:15 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_PAGE_INFO_H_
#define _XDW_DOCUWORKS_PAGE_INFO_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorks.h"

/**
 * @interface XdwDocuWorks::PageInfo XdwDocuWorksPageInfo.h
 * @brief DocuWorksファイルの指定されたページに関する情報を取得するためのインターフェース
 *
 * クライアントは本インターフェースのインスタンスの削除は認めない<br>
 * 本インターフェースを利用して、ページを構成する中身のサイズや
 * ページを構成するコンテント数などを取得することができる
 */
class XdwDocuWorks::PageInfo
{
public:
    /********************************************/
    /* 列挙型 */

    /*! ページを構成するサイズの指定 */
    enum PageSizeMode{
        /*! 紙のサイズ */
        PAPER_MODE,
        /*! 紙をはみ出しているコンテントを含めたサイズ */
        FULL_MODE
    };

    /*! ページを構成するコンテントの指定 */
    enum ContentMode{
        /*! 地のコンテント */
        BASIC_CONTENT_MODE,
        /*! ページヘッダなどを構成するコンテント */
        PAGE_HEADER_MODE,
        /*! アノテーションコンテント */
        ANNOTATION_MODE,
        /*! 紙をはみ出しているアノテーションコンテント(付箋) */
        BORDER_IGNORED_MODE,
    };
    
    /*! ページのカラーモード */
    enum ColorMode{
        /*! モノクロ */
        MONOCHROME,
        /*! カラー */
        COLOR,
        /*! 分からない */
        UNKOWN
    };
        
    /********************************************/
    /* メソッド */

    /**
     * @brief ページを構成するために使用する横幅を取得する
     *
     * @param mode ページを構成するサイズの指定<br>
     *             XdwDocuWorks::PageInfo::PageSizeModeを参照
     *
     * @return ページを構成するために使用する横幅(1/100mm単位)<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetWidth(XdwDocuWorks::PageInfo::PageSizeMode mode) = 0;

    /**
     * @biref ページを構成するために使用する縦幅を取得する
     *
     * @param mode ページを構成するサイズの指定<br>
     *             XdwDocuWorks::PageInfo::PageSizeModeを参照
     *
     * @return ページを構成するために使用する縦幅(1/100mm単位)<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetHeight(XdwDocuWorks::PageInfo::PageSizeMode mode) = 0;
    
    /**
     * @brief ページ領域を構成する領域の左上隅のx座標を取得する
     *
     * @return ページ領域を構成する領域の左上隅のx座標(原点は紙領域の左上隅)
     */
    virtual long GetPageLeft() = 0;

    /**
     * @brief ページ領域を構成する領域の左上隅のy座標を取得する
     *
     * @return ページ領域を構成する領域の左上隅のy座標(原点は紙領域の左上隅)
     */
    virtual long GetPageTop() = 0;

    /**
     * @brief ページ領域を構成する領域の右下隅のx座標を取得する
     *
     * @return ページ領域を構成する領域の右下隅のx座標(原点は紙領域の左上隅)
     */
    virtual long GetPageRight() = 0;

    /**
     * @brief ページ領域を構成する領域の右下隅のy座標を取得する
     *
     * @return ページ領域を構成する領域の右下隅のy座標(原点は紙領域の左上隅)
     */
    virtual long GetPageBottom() = 0;
    
    /**
     * @brief ページを構成するコンテント数を取得する
     *
     * ページを構成するコンテントの総数は<br>
     * &nbsp; 地のコンテント数 + ページヘッダのコンテント数 + アノテーションコンテント数<br>
     * である
     *
     * @param mode ページを構成するコンテントの指定<br>
     *             XdwDocuWorks::PageInfo::ContentModeを参照
     *
     * @return ページを構成する指定された種類のコンテント数<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetContentCount(XdwDocuWorks::PageInfo::ContentMode mode) = 0;
    
    /**
     * @brief ページのカラーモードの取得
     *
     * @return XdwDocuWorks::PageInfo::ColorModeを参照
     */
    virtual XdwDocuWorks::PageInfo::ColorMode GetColorMode() = 0;

    /**
     * @brief ページ内にサムネイルが存在するかの確認
     *
     * サムネイルが存在する場合にはXdwDocuWorks::PageInfo::BASIC_CONTENT_MODEで取得できるXdwDocuWorks::ContentManagerインターフェースからアクセスできる
     *
     * @retval true 存在する
     * @retval false 存在しない
     */
    virtual bool IsThumbnailExisted() = 0;
    
};

#endif
