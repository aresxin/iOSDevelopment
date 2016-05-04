/**
 * @file  XdwDocuWorksFileInfo.h
 * @brief XdwDocuWorks::FileInfoインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksFileInfo.h,v 1.4 2009/12/22 08:11:15 chikyu Exp $
 *
 * @date 2004-06-30 Yasuiro Ito セキュリティ文書対応
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_FILE_INFO_H_
#define _XDW_DOCUWORKS_FILE_INFO_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorks.h"

/**
 * @interface XdwDocuWorks::FileInfo XdwDocuWorksFileInfo.h
 * @brief DocuWorksファイルのファイル全体に関する情報を取得するためのインターフェース
 *
 * クライアントは本インターフェースのインスタンスの削除は認めない<br>
 * 本インターフェースを利用して、ファイル全体のページ数や
 * バインダによって管理されているXDWファイル名などを取得することができる
 */
class XdwDocuWorks::FileInfo
{
public:

    /********************************************/
    /*! セキュリティ文書のタイプを定義 
    	<br>Windows 版のMPS_CryptType と値をあわせてある(mpc_def.h)
	*/
	enum XdwCryptType{
		/*! V4パスワード文書*/
		CRYPTTYPE_DES = 1,
		/*! TripleDES文書 (未使用：未対応)<Br>
		  ここでCRYPTTYPE_TRIPLEDESが来ることはない。これよりも前の処理で、エラーとなる
		  */
		CRYPTTYPE_TRIPLEDES =2,
		/*! V5パスワード文書*/
		CRYPTTYPE_AES128 = 3,
		/*! 通常のDocuWorks文書*/
		NO_CRYPT = 999
	};
	/*! セキュリティ文書の権利を取得するためのビットフラグマスク*/
	enum XdwCryptPermission{
		/*! フルアクセス*/
		PERM_FULL = 0x01,
		/*! 文書の編集*/
		PERM_DOC_EDIT = 0x02,
		/*! アノテーション*/
		PERM_ANNO_EDIT = 0x04,
		/*! 印刷*/
		PERM_PRINT	=0x08,
		/*! 転記*/
		PERM_COPY = 0x10
	};
			
	/********************************************/
    /* メソッド */

    /**
     * @brief ファイル全体のページ数を取得する
     *
     * @return ファイル全体のページ数<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetPageCount() = 0;

    /**
     * @brief バインダの有無
     *
     * @retval true バインダーである
     * @retval false バインダーではない
     */
    virtual bool IsThisBinder() = 0;

    /**
     * @brief ファイルに格納されているバインダ数を取得する
     *
     * @return ファイルに格納されているバインダ数<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetBinderCount() = 0;

    /**
     * @brief バインダによって管理されているXDWファイル名を取得する
     *
     * @param binder_number バインダID<br>
     *                      XdwDocuWorks::FileInfo::GetBinderCount()メソッドで取得したバインダ数までの0基数
     *
     * @return XDWファイル名<br>
     * @return Shift-JISで格納されている<br>
     * ポインタの開放は認めない<br>
     * @return エラーの場合はNULLコード
     */
    virtual char* GetBinderName(long binder_number) = 0;

    /**
     * @brief バインダによって管理されているXDWファイルのページ数を取得する
     *
     * @param binder_number バインダID<br>
     *                      XdwDocuWorks::FileInfo::GetBinderCount()メソッドで取得したバインダ数までの0基数
     *
     * @return XDWファイルのページ数<br>
     * @return エラーの場合は-1以下
     */
    virtual long GetPageCount(long binder_number) = 0;

    /**
     * @brief アノテーションの表示/非表示を確認する
     *
     * XDWファイル中のアノテーションの表示/非表示を確認する
     *
     * @param binder_number バインダID<br>
     *                      XdwDocuWorks::FileInfo::GetBinderCount()メソッドで取得したバインダ数までの0基数
     *                      ただし、指定されたファイルがバインダで無い場合は、
     *                      バインダIDを指定不可
     *
     * @retval true アノテーションの表示
     * @retval false アノテーションの非表示
     */
    virtual bool IsAnnotationDisplayed(long binder_number = -1) = 0;

	/**
     * @brief 署名文書かどうかを取得する
     *
	 * 署名文書の場合は、アノテーションは常に表示（非表示にできない） 
	 *
     * @retval true 署名文書
     * @retval false 署名文書ではない
     */
    virtual bool IsSignature(void) = 0;   

	/**
     * @brief 保護文書の種類を取得する
     * 
	 * ここでCRYPTTYPE_TRIPLEDESが来ることはない。これよりも前の処理で、エラーとなる
	 *
     * @retval XdwCryptType参照
     */
	virtual XdwCryptType GetCryptType(void) = 0;

	/**
     * @brief 保護文書の権利を取得する
     * <br> XdwCryptPermissionと&をとり、権利を調べる。<br>ビットがたっている時には権利がある
	 * <Br> ビットがたってないときは、権利がない
     * @retval long :XdwCryptPermissionを使って文書の権利を得る
     */
	virtual long GetCryptPermission(void) = 0;
};

#endif
