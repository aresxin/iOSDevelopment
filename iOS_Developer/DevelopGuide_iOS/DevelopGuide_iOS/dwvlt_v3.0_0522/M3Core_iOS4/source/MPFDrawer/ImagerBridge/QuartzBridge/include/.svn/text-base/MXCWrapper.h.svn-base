//
//  MXCWrapper.h
//
//  Updater : $Author: akiyoshi $
//  Version : $Revision: 1.2 $, $Date: 2006/09/19 12:00:55 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCWrapper.h	DWCORE Wrapper Class
 *
 *	DWCOREの機能をU/I側から使用できるようにするラッパークラス定義
 */

#ifndef MXCWRAPPER_H
#define MXCWRAPPER_H

#include <stdio.h>
#include "MXCWrapperConst.h"

#ifdef __cplusplus

class MXCBinder;
class MXCDWDocument;
class MXCDocument;
class MXCDocumentInBinder;
class MXCPage;
class MXCSecurity;
class MXCImage;
class MXCPageform;
class MXCAnnotation;
class MXCOriginalDataMgr;
class MXCOriginalData;
class MXCDocumentSummary; //DWVLT62 2006.09.19 add by akiyoshi.

/**
 * MXCBinder : バインダー文書クラス
 * 
 * バインダー文書を表すクラス。
 * バインダー文書を構成するオブジェクトのルートオブジェクトになる。
 *
 */ 
class MXCBinder {

public:
	virtual ~MXCBinder(){};
	
    /**
     * openFile : ファイルオープンメソッド
     * DW文書をオープンする。文書の解析が行われコアのオブジェクトが作成される。
     * データのロードは行われない。
     *
     * 引数：
     * char* path   DW文書へのパス文字列 (UTF-8である必要がある)
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     * MXC_AUTH_FAILED  認証エラーもしくは認証が失敗した
     * MXC_AUTH_NEEDED  認証が必要
     */
    // 2004/01/13現在
    // 保護文書の場合はすべて(パスワード保護されているか否かにかかわらず)MXC_AUTH_FAILEDが返る。
    // MXC_AUTH_NEEDED は返らない。
    virtual int openFile(char *path) = 0;

    /**
     * closeFile : ファイルクローズメソッド
     * DW文書をクローズする。
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int closeFile() = 0;

    /*
     * passwordComment : パスワードのコメントを返す
     * パスワード入力ダイアログを表示するときにコメントの表示が必要。
     * 文字コードはShiftJISでしょう多分
     *
     * 返り値：
     * コメントを格納するバッファのポインタ(char *)
     */
    virtual char* passwordComment() = 0;
    
    /*
     * authenticate : パスワード認証メソッド
     * 引数で指定されたパスワードでパスワード認証を行う。
     *
     * 引数：
     * char *pass   入力されたパスワード
	 * int saveFlg  パスワードを保管するかどうかのフラグ
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     * MXC_AUTH_FAILED  認証が失敗した
     */
    virtual int authenticate(char *pass, int saveFlg) = 0;

    /**
     * documentCount : 内部文書の数を返す
     * バインダーの内部文書の数を返す
     *
     * 返り値：
     * 内部文書数
     * 内部文書数が取得できない場合は 0
     */
    virtual int documentCount() = 0;
    
    /**
     * document : 指定されたindexの内部文書を返す
     * バインダーの内部文書のインスタンスのポインタを返す
     *
     * 引数：
     * int index   内部文書のインデックス(0オリジンで指定する)
     *
     * 返り値：
     * 内部文書インスタンスのポインタ
     */
    virtual MXCDocumentInBinder* document(int index) = 0;    

    /**
     * totalPageCount : すべての内部文書を合わせた総ページ数を返す
     * バインダー文書の中のすべての内部文書を合わせた総ページ数を返す。
     *
     * 返り値：
     * すべての内部文書を合わせた総ページ数
     */
    virtual int totalPageCount() = 0;

    /**
     * seqPage : 通しページ指定された文書ページを返す
     * バインダーの通しページで指定されたページの MXCPage インスタンスのポインタを返す。
     *
     * 引数：
     * int pageNo   バインダーの通しページでのページ番号(１オリジンで指定する)
     *
     * 返り値：
     * MXCPage インスタンスのポインタ
     */
    virtual MXCPage* seqPage(int pageNo) = 0;

    /**
     * version : 文書を作成したDocuWorksのバージョンを数値で返す
     *
     * 返り値：
     * バージョン(int)
     */
    virtual int version() = 0;

    /**
     * innerDocIndex : 指定された通しページ番号でそのページを含む内部文書のインデックスを返す。
     *
     * 引数：
     * int seqPageNo   バインダーの通しページでのページ番号(１オリジンで指定する)
     *
     * 返り値：
     * 内部文書のインデックス(int)
	 * ページ番号が不正な場合は -1
     */
    virtual int innerDocIndex(int seqPageNo) = 0;

    /**
     * security : セキュリティオブジェクトを返す
     * セキュリティオブジェクト MXCSecurity を返す
     *
     * 返り値：
     * MXCSecurity インスタンスのポインタ
     */
    virtual MXCSecurity* security() = 0;    
    
    /**
     * originalDataMgr : オリジナルデータ管理オブジェクトを返す
     * オリジナルデータ管理オブジェクト MXCOriginalDataMgr を返す
     *
     * 返り値：
     * MXCOriginalDataMgr インスタンスのポインタ
     */
    virtual MXCOriginalDataMgr* originalDataMgr() = 0;    
    
    /**
     * binderColor : バインダーの色を返す
     * バインダー情報の中の「バインダーの色」を返す
     *
     * バインダーの色は6色固定。コアは属性として0〜5のインデックスを持っている。
     * 色は、
     * index[0] -- R[0x00] G[0x33] B[0x66]
     * index[1] -- R[0x00] G[0x66] B[0x33]
     * index[2] -- R[0x33] G[0x66] B[0xff]
     * index[3] -- R[0xff] G[0xff] B[0x66]
     * index[4] -- R[0xff] G[0x66] B[0x33]
     * index[5] -- R[0xff] G[0x33] B[0x66]
     *
	 * これに従って、このメソッドでは COLORREF(unsigned int)を作成して返す。
	 * (BIG ENDIANになっている事に注意)
     *
     * 返り値：
     * 色を示すCOLORREFの整数(unsigned int)
	 */
    virtual unsigned long binderColor() = 0;    

    /**
     * binderSize : バインダーの用紙サイズを返す
     * バインダー情報の中の「バインダーのサイズ」情報に当たる用紙サイズを返す
     *
     * コアではサイズは 実サイズをMP_Dimで持っている。
	 * このサイズを参照して、用紙サイズを示す定数を返す。
     *
     * 返り値：
     * 用紙サイズを示す定数
	 */
    virtual int binderSize() = 0;
    
    /**
     * isDisplayAnnotation : アノテーションの表示／非表示を返す
     * 文書オープン時にアノテーションを表示するかどうかを返す。
	 *
     * 返り値：
     * MXC_TRUE     アノテーション表示
     * MXC_FALSE    アノテーション非表示
	 */
    virtual int isDisplayAnnotation() = 0;
	
    /**
	 * DWVLT62 add 2006.09.19 by akiyoshi.
	 * [for Version 6.2]
     * documentSummary : 文書概要情報オブジェクトを返す
	 *
     * 返り値：
     * MXCDocumentSummary インスタンスのポインタ
	 */
    virtual MXCDocumentSummary* documentSummary() = 0;

};

/**
 * MXCDWDocument : コアラッパー文書クラス
 * 
 * コアラッパーの文書を表すクラス。
 * DW文書を表すMXCDocument、バインダー文書内の内部文書を表すMXCDocumentInBinderの親クラスにあたる。
 *
 */ 
class MXCDWDocument {

public:
	virtual ~MXCDWDocument(){};
	
    /**
     * pageCount : ページ数を返す
     * 総ページ数を返す。
     * バインダーの場合はすべての内部文書を合わせた総ページ数が返る。
     *
     * 返り値：
     * ページ数
     */
    virtual int pageCount() = 0;

    /**
     * page : 文書ページを返す
     * MXCPage のインスタンスのポインタを返す。
     *
     * 引数：
     * int pageNo   ページ番号(１オリジンで指定する)
     *
     * 返り値：
     * MXCPage インスタンスのポインタ
     */
    virtual MXCPage* page(int pageNo) = 0;

    /**
     * unloadPage : ページを指定して描画オブジェクトのアンロードを行う
     *
     * 引数：
     * int pageNo   ページ番号(１オリジンで指定する)
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int unloadPage(int pageNo) = 0;

    /**
     * unloadPage : ページ範囲を指定して描画オブジェクトのアンロードを行う
     *
     * 引数：
     * int fromPage     開始ページ番号(１オリジンで指定する)
     * int toPage       終了ページ番号(１オリジンで指定する)
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int unloadPage(int fromPage, int toPage) = 0;
	
};

/**
 * MXCDocument : DW文書クラス
 * 
 * DW文書を表すクラス。MXCDWDocumentを継承する。
 * DW文書を構成するオブジェクトのルートオブジェクトになる。
 *
 */ 
class MXCDocument : public MXCDWDocument {

public:
    /**
     * openFile : ファイルオープンメソッド
     * DW文書をオープンする。文書の解析が行われコアのオブジェクトが作成される。
     * データのロードは行われない。
     *
     * 引数：
     * char* path   DW文書へのパス文字列 (UTF-8である必要がある)
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     * MXC_AUTH_FAILED  認証エラーもしくは認証が失敗した
     * MXC_AUTH_NEEDED  認証が必要
     */
    // 2004/01/13現在
    // 保護文書の場合はすべて(パスワード保護されているか否かにかかわらず)MXC_AUTH_FAILEDが返る。
    // MXC_AUTH_NEEDED は返らない。
    virtual int openFile(char *path) = 0;

    /**
     * closeFile : ファイルクローズメソッド
     * DW文書をクローズする。
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int closeFile() = 0;

    /*
     * passwordComment : パスワードのコメントを返す
     * パスワード入力ダイアログを表示するときにコメントの表示が必要。
     * 文字コードはShiftJISでしょう多分
     *
     * 返り値：
     * コメントを格納するバッファのポインタ(char *)
     */
    virtual char* passwordComment() = 0;
    
    /*
     * authenticate : パスワード認証メソッド
     * 引数で指定されたパスワードでパスワード認証を行う。
     *
     * 引数：
     * char *pass   入力されたパスワード
	 * int saveFlg  パスワードを保管するかどうかのフラグ
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     * MXC_AUTH_FAILED  認証が失敗した
     */
    virtual int authenticate(char *pass, int saveFlg) = 0;

    /**
     * version : 文書を作成したDocuWorksのバージョンを数値で返す
     *
     * 返り値：
     * バージョン(int)
     */
    virtual int version() = 0;

    /**
     * security : セキュリティオブジェクトを返す
     * セキュリティオブジェクト MXCSecurity を返す
     *
     * 返り値：
     * MXCSecurity インスタンスのポインタ
     */
    virtual MXCSecurity* security() = 0;    

    /**
     * originalDataMgr : オリジナルデータ管理オブジェクトを返す
     * オリジナルデータ管理オブジェクト MXCOriginalDataMgr を返す
     *
     * 返り値：
     * MXCOriginalDataMgr インスタンスのポインタ
     */
    virtual MXCOriginalDataMgr* originalDataMgr() = 0;    
    
    /**
     * isDisplayAnnotation : アノテーションの表示／非表示を返す
     * 文書オープン時にアノテーションを表示するかどうかを返す。
	 *
     * 返り値：
     * MXC_TRUE     アノテーション表示
     * MXC_FALSE    アノテーション非表示
	 */
    virtual int isDisplayAnnotation() = 0;

    /**
	 * DWVLT62 add 2006.09.19 by akiyoshi.
	 * [for Version 6.2]
     * documentSummary : 文書概要情報オブジェクトを返す
	 *
     * 返り値：
     * MXCDocumentSummary インスタンスのポインタ
	 */
    virtual MXCDocumentSummary* documentSummary() = 0;
};

/**
 * MXCDocumentInBinder : バインダー内部文書クラス
 * 
 * バインダー文書の内部文書を表すクラス。MXCDWDocumentを継承する。
 * MXCBinderクラスがツリー構造で複数持つ。
 *
 */ 
class MXCDocumentInBinder : public MXCDWDocument {

public:
    /**
     * name: 内部文書名を返す
     * バインダーの内部文書名を返す
     *
     * 返り値：
     * 内部文書名へのポインタ(char*)
     */
    virtual char* name() = 0;

    /**[DWVLT70 2008.02.04 by ushijima]
     * nameW: 内部文書名を返す
     * バインダーの内部文書名を返す
     *
     * 返り値：
     * 内部文書名へのポインタ(char*)
	 * 内部文書名の文字長(int*)
     */
    virtual char* nameW(int* unilen) = 0;

    /**
     * seqPageNo: 通しページの番号を返す
     * バインダーの内部文書のページ番号を引数にして、
	 * 内部文書のページ番号で指定されたページが、バインダーの通しページで
	 * 何ページ目になるかを返す。
	 * 引数で指定されたページが内部文書のページ数を超えていたり数値が不正だったりした場合は、
	 * -1 を返す。
     *
     * 引数：
     * int pageNo   内部文書でのページ番号
	 *
	 * 返り値：
     * バインダー通してのページ番号(int)
     */
    virtual int seqPageNo(int pageNo) = 0;

    /**
     * originalDataCount : オリジナルデータの数を返す。
     * この内部文書が持つオリジナルデータの数を返す。バインダ索引で使用する。
     *
     * 返り値：
     * オリジナルデータの数
     */
    virtual int originalDataCount() = 0;    
};


/**
 * MXCPage : ページクラス
 * 
 * 文書のページを表すクラス。
 * MXCDWDocumentクラスがツリー構造でページの数だけ持つ。
 *
 */ 
class MXCPage {

public:
	virtual ~MXCPage(){};

    /**
     * unloadPage : 描画オブジェクトのアンロードを行う
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int unloadPage() = 0;

    /**
     * imageCount : ＤＷ文書描画オブジェクトの数を返す
	 * 見出しは入らない為、返り値は 0 もしくは 1 となる。
     *
     * 返り値：
     * ＤＷ文書描画オブジェクトの数
     */
    virtual int imageCount() = 0;
    
    /**
     * image : 指定されたＤＷ文書描画オブジェクトを返す
     * 引数で指定されたＤＷ文書描画オブジェクトを返す。
     *
     * 引数：
     * int index   ＤＷ文書描画オブジェクトのインデックス(0オリジンで指定する)
     *
     * 返り値：
     * MXCImage インスタンスのポインタ
     */
    virtual MXCImage* image(int index) = 0;
    
    /**
     * pageformCount : 見出しオブジェクトの数を返す
	 * 見出しは１ページに最高４個までの為、返り値は 0 から 4 までの間の値を取る。
     *
     * 返り値：
     * 見出しオブジェクトの数
     */
    virtual int pageformCount() = 0;
    
    /**
     * pageform : 指定された見出しを返す
     * 引数で指定された見出しオブジェクトを返す。
     *
     * 引数：
     * int index   MXCPageformのインデックス(0オリジンで指定する)
     *
     * 返り値：
     * MXCPageform インスタンスのポインタ
     */
    virtual MXCPageform* pageform(int index) = 0;
    
    /**
     * annotationCount : アノテーションオブジェクトの数を返す
     *
     * 返り値：
     * アノテーションオブジェクトの数
     */
    virtual int annotationCount() = 0;
    
    /**
     * annotation : 指定されたアノテーションオブジェクトを返す
     * 引数で指定されたアノテーションオブジェクトを返す。
     *
     * 引数：
     * int index   アノテーションオブジェクトのインデックス(0オリジンで指定する)
     *
     * 返り値：
     * MXCAnnotation インスタンスのポインタ
     */
    virtual MXCAnnotation* annotation(int index) = 0;
    
    /**
     * width : ページの幅を返す
     *
     * 返り値：
     * ページの幅
     */
    virtual int width() = 0;
    
    /**
     * height : ページの高さを返す
     *
     * 返り値：
     * ページの高さ
     */
    virtual int height() = 0;
    
    /**
     * pageSize : ページの用紙サイズを返す
     * ページ情報の中の「ページのサイズ」にあたる用紙サイズを返す
     * ページのサイズから用紙サイズを割り出し、用紙サイズを示す定数を返す。
     *
     * 返り値：
     * 用紙サイズを示す定数
	 */
    virtual int pageSize() = 0;

    /**
     * originalKind : オリジナル種別を返す
     * オリジナル種別はイメージ文書／アプリケーション文書／その他の３種類
     * それぞれに対応した定数を返す。
     *
     * 返り値：
     * オリジナル種別定数
     */
    virtual int originalKind() = 0;
    
    /**
     * resolutionKind : 解像度の種別を返す
     * 解像度種別は
     *      ファックス標準
     *      ファックス高画質(200dpi)
     *      ファックス高画質(200x400dpi)
     *      その他
     * のうちのいずれかで、それぞれに対応した定数を返す。
     *
     * 返り値：
     * 解像度種別定数
     */
    virtual int resolutionKind() = 0;
    
    /**
     * resolution : 解像度を返す
     * 解像度を数値で返す。
     *
     * 返り値：
     * 解像度
     */
    virtual int resolution() = 0;

    /**
     * compressMode : 圧縮モードを返す
     * 圧縮モードは
     *      高圧縮
     *      標準
     *      高画質
     *      画像劣化なし
     * のうちのいずれかで、それぞれに対応した定数を返す。
     * イメージのページのみ有効。
     *
     * 返り値：
     * 圧縮モード定数
     */
    virtual int compressMode() = 0;
    
    /**
     * colorNumber : 色数を定数で返す
     * 色数を定数で返す。
     * イメージのページのみ有効。
     *
     * 返り値：
     * 色数を表す定数
     */
    virtual int colorNumber() = 0;
    
    /**
     * colorMode : カラーモードを返す
     * カラー指定で文書化されたページかどうかを返す。
     * アプリケーションのページのみ有効。
     *
     * 返り値：
     * MXC_TRUE     カラー指定あり
     * MXC_FALSE    カラー指定なし
     */
    virtual int colorMode() = 0;
    
    /**
     * isOCR : OCRデータの有無を返す
     * OCRデータがあるかないかを返す。
     * イメージのページのみ有効。
     *
     * 返り値：
     * MXC_TRUE     OCRデータあり
     * MXC_FALSE    OCRデータなし
     */
    virtual int isOCR() = 0;
	
	/**
	 * [for Version 6.0]
	 *
	 * isProtrusion : はみ出し付箋があるかどうかを返す
	 * 厚み表示の際に描画が必要なはみ出した付箋があるかどうかを返す。
	 *
	 * 返り値：
     * MXC_TRUE     はみ出しあり
     * MXC_FALSE    はみ出しなし
     */
    virtual int isProtrusion() = 0;
	
	/**
	 * [for Version 6.0]
	 *
	 * protrusionCount : はみ出した付箋の数を返す
	 * 厚み表示の際に描画が必要なはみ出した付箋の数を返す。
	 *
     * 返り値：
     * はみ出し付箋の数
     */
    virtual int protrusionCount() = 0;

	/**
	 * [for Version 6.0]
	 *
	 * protrusion : はみ出した付箋インスタンスを返す
	 * 厚み表示の際に描画が必要なはみ出した付箋インスタンスのポインタを返す。
	 *
     * 引数：
     * int index   アノテーションオブジェクトのインデックス(0オリジンで指定する)
     *
     * 返り値：
     * はみ出し付箋インスタンスのポインタ
     */
    virtual MXCAnnotation* protrusion(int index) = 0;

};

/**
 * MXCSecurity : セキュリティ情報クラス
 * 
 * セキュリティ情報を保持するクラス。
 * MXCDocument、MXCBinderクラスが持つ。
 *
 */ 
class MXCSecurity {

public:
	virtual ~MXCSecurity(){};
	
    /*
     * isSecurity : 保護文書かどうかを返す
     * 開いているDW文書／バインダー文書が保護文書かどうかを返す。
     *
     * 返り値：
     * MXC_TRUE     保護文書
     * MXC_FALSE    保護文書でない
     */
    virtual int isSecurity() = 0;

    /*
     * isEditDocument : 文書の編集権があるかないかを返す
     * 保護文書の場合、文書の編集権があるかないかを返す。
     * 保護文書でない場合は常にMXC_TRUEが返る。
     *
     * 返り値：
     * MXC_TRUE     文書編集権あり
     * MXC_FALSE    文書編集権なし
     */
    virtual int isEditDocument() = 0;
    
    /*
     * isEditAnnotation : アノテーションの編集権があるかないかを返す
     * 保護文書の場合、アノテーションの編集権があるかないかを返す。
     * 保護文書でない場合は常にMXC_TRUEが返る。
     *
     * 返り値：
     * MXC_TRUE     アノテーション編集権あり
     * MXC_FALSE    アノテーション編集権なし
     */
    virtual int isEditAnnotation() = 0;
    
    /*
     * isPrint : 印刷権があるかないかを返す
     * 保護文書の場合、印刷権があるかないかを返す。
     * 保護文書でない場合は常にMXC_TRUEが返る。
     *
     * 返り値：
     * MXC_TRUE     印刷権あり
     * MXC_FALSE    印刷権なし
     */
    virtual int isPrint() = 0;

    /*
     * isCopy : 転記権があるかないかを返す
     * 保護文書の場合、転記権があるかないかを返す。
     * 保護文書でない場合は常にMXC_TRUEが返る。
     *
     * 返り値：
     * MXC_TRUE     転記権あり
     * MXC_FALSE    転記権なし
     */
    virtual int isCopy() = 0;

    /*
     * securitykind : セキュリティの種類を返す
     * セキュリティの種類を表す定数を返す。
     *
     * 返り値：
     * セキュリティの種類を表す定数(int)
     */
    virtual int securitykind() = 0;
    
    /*
     * isExistsSignature : 電子署名が存在するかどうか返す
     * 電子署名・電子印鑑が文書に存在するかどうか返す
     *
     * 返り値：
     * MXC_TRUE     電子署名あり
     * MXC_FALSE    電子署名なし
     */
    virtual int isExistsSignature() = 0;

	/*
	 * isTMB() : TrustMarking があるかどうか返す
	 *
	 * 返り値：
	 * MXC_TRUE     TrustMarkingあり
	 * MXC_FALSE    TrustMarkingなし
	 */
	virtual int isTMB() = 0;
};

/**
 * MXCOriginalDataMgr : オリジナルデータ管理クラス
 * 
 * オリジナルデータを管理するクラス。
 * MXCDocument、MXCBinderクラスが持つ。
 *
 */ 
class MXCOriginalDataMgr {

public:
	virtual ~MXCOriginalDataMgr(){};
	
    /*
     * count: オリジナルデータの数を返す
     * 開いているDW文書／バインダー文書に設定されているオリジナルデータの数を返す。
     *
     * 返り値：
     * オリジナルデータの数(int)
     */
    virtual int  count() = 0;

    /*
     * originalData : オリジナルデータクラスを返す
	 * 引数で指定されたMXCOriginalDataのインスタンスのポインタを返す
     *
     * 引数：
     * int index   MXCOriginalDataのインデックス(0オリジンで指定する)
     *
     * 返り値：
     * MXCOriginalDataクラスのインスタンスのポインタ
     */
    virtual MXCOriginalData* originalData(int index) = 0;
    
};

/**
 * MXCOriginalData : オリジナルデータクラス
 * 
 * オリジナルデータを表すクラス。
 * MXCOriginalDataMgrクラスが持つ。
 *
 */ 
class MXCOriginalData {

public:
	virtual ~MXCOriginalData(){};
	
    /*
     * name: オリジナルデータのファイル名を返す
     *
     * 返り値：
     * オリジナルデータのファイル名(char*)
     */
    virtual char*  name() = 0;

	/**[DWVLT70 2008.02.04 by ushijima]
     * nameW: オリジナルデータのファイル名を返す
     *
     * 返り値：
     * オリジナルデータのファイル名(char*)
	 * オリジナルデータ名の文字長(int*)
     */
	virtual char* nameW(int* unilen) = 0;

    /*
     * size: オリジナルデータのサイズ(バイト数)を返す
     *
     * 返り値：
     * オリジナルデータのサイズ(long)
     */
    virtual size_t  size() = 0;

    /*
     * save: オリジナルデータを保存する
     *
     * 引数：
     * char* path   オリジナルデータを保存するパス（ファイル名まで含む）
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int  save(char* path) = 0;

};

/**
 * DWVLT62 add 2006.09.19 by akiyoshi
 * MXCDocumentSummary : 文書概要情報クラス
 * 
 * 文書の概要情報を表すクラス。
 * MXCDocument、MXCBinderクラスが持つ。
 *
 */ 
class MXCDocumentSummary {

public:
	virtual ~MXCDocumentSummary(){};
	
    /*
     * title: 文書概要情報のタイトルを返す
     *
     * 返り値：
     * 文書概要情報　タイトル(char*)
     */
    virtual char*  title() = 0;

    /*
     * subject: 文書概要情報のサブタイトルを返す
     *
     * 返り値：
     * 文書概要情報　サブタイトル(char*)
     */
    virtual char*  subject() = 0;

    /*
     * author: 文書概要情報の作成者を返す
     *
     * 返り値：
     * 文書概要情報　作成者(char*)
     */
    virtual char*  author() = 0;

    /*
     * keywords: 文書概要情報のキーワードを返す
     *
     * 返り値：
     * 文書概要情報　キーワード(char*)
     */
    virtual char*  keywords() = 0;

    /*
     * comments: 文書概要情報のコメントを返す
     *
     * 返り値：
     * 文書概要情報　コメント(char*)
     */
    virtual char*  comments() = 0;

	/**[DWVLT70 2008.02.06 by ushijima]
     * titleW: 文書概要情報のタイトルを返す(unicode用)
     *
     * 返り値：
     * 文書概要情報　タイトル(char*)
	 * タイトルの文字長(int*)
     */
    virtual char*  titleW(int* titlen) = 0;

	/**[DWVLT70 2008.02.06 by ushijima]
     * subjectW: 文書概要情報のサブタイトルを返す(unicode用)
     *
     * 返り値：
     * 文書概要情報　サブタイトル(char*)
	 * サブタイトルの文字長(int*)
     */
    virtual char*  subjectW(int* sublen) = 0;

	/**[DWVLT70 2008.02.06 by ushijima]
     * authorW: 文書概要情報の作成者を返す(unicode用)
     *
     * 返り値：
     * 文書概要情報　作成者(char*)
	 * 作成者の文字長(int*)
     */
    virtual char*  authorW(int* autlen) = 0;

	/**[DWVLT70 2008.02.06 by ushijima]
     * keywordsW: 文書概要情報のキーワードを返す(unicode用)
     *
     * 返り値：
     * 文書概要情報　キーワード(char*)
	 * キーワードの文字長(int*)
     */
    virtual char*  keywordsW(int* keylen) = 0;

	/**[DWVLT70 2008.02.06 by ushijima]
     * commentsW: 文書概要情報のコメントを返す(unicode用)
     *
     * 返り値：
     * 文書概要情報　コメント(char*)
	 * コメントの文字長(int*)
     */
    virtual char*  commentsW(int* comlen) = 0;

};

// function
/**
 * createMXCDocument : MXCDocumentインスタンス作成
 * 
 * MXCDocumentのインスタンスを作成して返す。
 * MXCDocumentのインスタンスを作成するときには必ずこの関数を呼ぶ。
 * MXCDocumentのインスタンス破棄時には必ずdestroyMXCDocumentを呼ぶ。
 */
MXCDocument*	createMXCDocument();

/**
 * destroyMXCDocument : MXCDocumentインスタンス破棄
 * 
 * MXCDocumentのインスタンスを破棄する。
 */
void destroyMXCDocument(MXCDocument* doc);

/**
 * createMXCBinder : MXCBinderインスタンス作成
 * 
 * MXCBinderのインスタンスを作成して返す。
 * MXCBinderのインスタンスを作成するときには必ずこの関数を呼ぶ。
 * MXCBinderのインスタンス破棄時には必ずdestroyMXCBinderを呼ぶ。
 */
MXCBinder*	createMXCBinder();

/**
 * destroyMXCBinder : MXCBinderインスタンス破棄
 * 
 * MXCBinderのインスタンスを破棄する。
 */
void destroyMXCBinder(MXCBinder* binder);

#endif // __cplusplus

#endif // MXCWRAPPER_H
