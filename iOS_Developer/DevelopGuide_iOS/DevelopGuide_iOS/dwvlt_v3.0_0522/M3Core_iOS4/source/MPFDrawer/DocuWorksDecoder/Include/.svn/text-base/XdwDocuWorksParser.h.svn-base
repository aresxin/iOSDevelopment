/**
 * @file  XdwDocuWorksParser.h
 * @brief XdwDocuWorks::Parserクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksParser.h,v 1.4 2009/12/22 08:11:15 chikyu Exp $
 * 
 * @date 2004-07-15 セキュリティ対応 Yasuhiro.Ito@fujixerox.co.jp
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_PARSER_H_
#define _XDW_DOCUWORKS_PARSER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorks.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwDocuWorksPageInfo.h"

/* 依存するパッケージを記述したIncludeファイル */
#include "XdwDataObjectBase.h"

// For Security Document
class XdwPasswordManager;
/**
 * @brief DocuWorksファイルを読み込みクラス
 *
 * クライアントがファイル情報を取得する場合
 * XdwDataObjectパッケージのXdwDataObject::Base::Interfaceインターフェースを介して行う<br>
 * 大きなサイズのヒープ領域の確保も
 * XdwDataObject::BaseパッケージのXdwDataObject::Base::Generatorインターフェースを介して行う<br>
 * この実装はプラットフォームに依存しない<br>
 * <br>
 * XdwGraphicFormat::ParsingStrategy抽象クラスと本クラスとの関連クラスとして、<br>
 * XdwDocuWorks::ContentManagerインターフェースを規定しているので、<br>
 * XdwDocuWorks::ContentManagerインターフェースを介して、
 * XdwGraphicFormat::ParsingStrategy抽象クラスの実装インスタンスで、<br>
 * 直接グラフィックデータをパースするメソッドを操作することもDocuWorksファイルの全てを解釈可能である<br>
 * 少なくとも、本クラスではグラフィックデータ以外の全ての部分を解釈する
 */
class XdwDocuWorks::Parser
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Parser();

    /**
     * @brief デストラクタ
     */
    virtual ~Parser();

    /**
     * @brief インスタンスを初期化する
     *
     * @param data_object_generator XdwDataObject::Base::Generatorクラスのインスタンス
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwDataObject::Base::Generator* data_object_generator = XdwNull);

    /**
     * @brief セットされたファイルをパースする
     *
     * セキュリティがかかっていない限り、本メソッドでファイル構造をすべてパースする<br>
     * 少なくとも、DocuWorksファイルのHeaderおよびTrailerの読み込みは行う
     *
     * @param file_data  DocuWorksファイルが格納されている
     *                   XdwDataObject::Base::Interfaceインターフェースのインスタンス
     * @param XdwPasswordManager パスワードを管理するクラスのインスタンス
	 *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SetFile(XdwDataObject::Base::Interface* file_data,XdwPasswordManager* data = XdwNull);

    /**
     * @brief セキュリティがかかっているファイルをパースする
     *
     * セットされたファイルにセキュリティがかかっている場合に、
     * セットされたパスワードでセットされたファイルをパースする<br>
     * 直前のXdwDocuWorks::Parser::SetFile(XdwDataObject::Binary* file_data)メソッドで
     * セットされたファイルを、本メソッドでファイル構造をすべてパースする
     *
     * @param passwd パスワード文字列(平文)
     * @param update 一時保存するかどうかのフラグ
	 *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SetPasswd(char* passwd,bool update = false);
#if !defined _PF_WINCE_
	/**
	* @brief バイナリに登録されているパスワードコメントを得る
	* 
	* @param size コメントのサイズが格納される
	* @return コメントへのポインタ
	*/
	char* GetPasswordComment(int &size);
#endif    
	/**
     * @brief ファイル情報を取得する
     *
     * パースしたファイルのページ数やバインダの情報を取得する
     *
     * @return ファイルの各種情報を提示するXdwDocuWorks::FileInfoインターフェースのインスタンス<br>
     * @return クライアントの削除は認めない<br>
     * @return エラーの場合はXdwNullコード
     */
    virtual XdwDocuWorks::FileInfo* GetFileInfo();

    /**
     * @brief ページをセットする
     *
     * 現在のファイルの取得したいページ情報のページをセットする
     *
     * @param page_number ページID<br>
     *                    XdwDocuWorks::FileInfo::GetPageCount()メソッドで取得した
     *                    ファイル全体のページ数までの0基数
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SetPage(long page_number);

    /**
     * @brief ページをセットする
     *
     * 現在のファイルの取得したいページ情報のページをセットする
     *
     * @param binder_number バインダID<br>
     *                      XdwDocuWorks::FileInfo::GetBinderCount()メソッドで取得した
     *                      バインダ数までの0基数
     * @param page_number ページID<br>
     *                    XdwDocuWorks::FileInfo::GetPageCount(long binder_number)メソッドで取得した
     *                    バインダを構成するページ数までの0基数
     *
     * @return XdwXdwDocuWorksReturnを参照
     */
    virtual XdwErrorCode SetPage(long binder_number, long page_number);

    /**
     * @brief ページ情報を取得する
     *
     * 現在のページのペーパーサイズなどの情報を取得する
     *
     * @return ページの各種情報を提示するXdwDocuWorks::PageInfoインターフェースのインスタンス<br>
     * @return クライアントの削除は認めない<br>
     * @return エラーの場合はXdwNullコード
     */
    virtual XdwDocuWorks::PageInfo* GetPageInfo();

    /**
     * @brief ファイル構造に関するコンテント部分をセットする
     *
     * 現在のページの取得したいコンテント部分の情報をセットする<br>
     * 初期化後に、セットしたファイル構造に関するコンテントの情報を取得できる
     *
     * @param mode  ページを構成するコンテントの指定<br>
     *              XdwDocuWorks::PageInfo::ContentModeを参照
     * @param content_number コンテントID<br>
     *                       XdwDocuWorks::PageInfo::GetContentCount(XdwDocuWorks::PageInfo::ContentMode mode)メソッドで取得した
     *                       コンテント数までの0基数
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SetContent(XdwDocuWorks::PageInfo::ContentMode mode, long content_number);

    /**
     * @brief ファイル構造に関するコンテント部分をセットする
     *
     * 現在のページの取得したいコンテント部分の情報をセットする<br>
     * 初期化後に、セットしたファイル構造に関するコンテントの情報を取得できる<br>
     * そのコンテントが更に含んでいるコンテントを、現在のコンテントにセットする
     *
     * @param content_number コンテントID<br>
     *                       XdwDocuWorks::ContentInfo::GetContentCount()メソッドで取得した<br>
     *                       コンテント数までの0基数
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode SetContent(long content_number);

    /**
     * @brief ファイル構造に関するコンテントの情報を取得する
     *
     * PDタグなどの情報にも、アクセス可能
     *
     * @return コンテントの情報を提示するXdwDocuWorks::ContentManagerインターフェースのインスタンス<br>
     * @return クライアントの削除は認めない<br>
     * @return エラーの場合はXdwNullコード
     */
    virtual XdwDocuWorks::ContentManager* GetContentManager();

protected:

    /********************************************/
    /* 集約 */

    /*! バイナリデータを管理するクラス */
    XdwDocuWorks::BinaryManager* fBinaryManager;
    /*! ファイル構造をパースするクラス */
    XdwDocuWorks::FileParser* fFileParser;

	/* 関連 */
	/*! パスワードを管理するクラス*/
    XdwPasswordManager* fPasswordManager;
};

#endif
