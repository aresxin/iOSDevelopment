//
//  MXCAnnotation.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *	MXCAnnotation.h	DWCORE Annotation Class
 *
 *	MXCAnnotationクラスとその派生クラスのインターフェースを定義する。
 */

#ifndef MXCANNOTATION_H
#define MXCANNOTATION_H

#include "MXCWrapperConst.h"

#ifdef __cplusplus

class MXCImagePD;

/**
 * MXCAnnotation : DW文書 アノテーションオブジェクトクラス
 * 
 * アノテーションを表すクラス。
 * アノテーションの数だけ作成される。
 */
class MXCAnnotation {

public:
	virtual ~MXCAnnotation(){};

    /**
     * annotationKind : アノテーションの種別を返す
     * アノテーションの種別を定数で返す。
     *
     * 返り値：
     * アノテーション種別定数
     */
    virtual int annotationKind() = 0;
    
    /**
     * width : アノテーションの幅を返す
     *
     * 返り値：
     * 画像の幅
     */
    virtual int width() = 0;
    
    /**
     * height : アノテーションの高さを返す
     *
     * 返り値：
     * 画像の高さ
     */
    virtual int height() = 0;

    /**
     * x : アノテーションのX座標を返す
     *
     * 返り値：
     * 画像のX座標
     */
    virtual int x() = 0;
    
    /**
     * y : アノテーションのY座標を返す
     *
     * 返り値：
     * 画像のY座標
     */
    virtual int y() = 0;

    /**
	 * [for Version 6.0]
     * unloadPD : PDのアンロードを行う
     *
     * 返り値：
     * MXC_OK           OK
     * MXC_ERROR        エラー
     */
    virtual int unloadPD() = 0;
};

/**
 * MXCHasChildAnnotation : 子供を持つことの出来るアノテーションクラス
 * このアノテーションは他のアノテーションを子供として持つことが出来る。
 *
 * since:
 *  DWVLT70 V7Format 2008.07.14 by akiyoshi.
 *  カスタムアノテ、グループアノテの追加に伴い作成
 */
class MXCHasChildAnnotation : public MXCAnnotation {

public:

    /**
     * annotationCount : 子供アノテーションの数を返す
     *
     * 返り値：
     * アノテーションの数
     */
    virtual int annotationCount() = 0;

    /**
     * annotation : 子供アノテーションを返す
     *
	 * 引数：
	 * int index	MXCAnnotationのインデックス(0オリジンで指定する)
     *
     * 返り値：
     * アノテーション
     */
    virtual MXCAnnotation* annotation(int index) = 0;

};

/**
 * MXCLabelAnnotation : 付箋アノテーションクラス
 * 
 * 付箋アノテーションを表すクラス。
 * 付箋アノテーションは他のアノテーションを持つことが出来る。
 *
 * DWVLT70 V7Format 2008.07.14 by akiyoshi.
 * カスタムアノテ、グループアノテの追加に伴い、子供アノテーションの情報を返すメソッドを
 * MXCHasChildAnnotationに定義し、それを継承するよう変更
 */
class MXCLabelAnnotation : public MXCHasChildAnnotation {

public:

    /**
     * color : 付箋の色を返す
	 * 付箋の色を定数で返す
     *
     * 返り値：
     * 付箋の色を表す定数
     */
    virtual unsigned long color() = 0;

	/**
	 * [for Version 6.0]
	 * 
	 * isFusenProtrusion : 付箋がはみ出しているか判断
	 * 引数の付箋がページをはみ出しているかを判断する。
	 * 
	 * 返り値：
	 * MXC_TRUE			はみ出している
	 * MXC_FALSE		はみ出していない
	 */
	virtual int isFusenProtrusion() = 0;
};

/**
 * MXCDefaultAnnotation : 線アノテーションクラス
 * 
 * メタレコードを使って描画するアノテーションを表すクラス。
 * 
 */
class MXCDefaultAnnotation : public MXCAnnotation {

public:

    /**
     * lineKind : 線アノテーションの種別を返す
     * 線アノテーションの種別を定数で返す。
	 * 種別は自由曲線・直線・矩形・楕円・多角形・スタンプ・署名・OLE・その他
     *
     * 返り値：
     * アノテーション種別定数
     */
    virtual int lineKind() = 0;

    /**
     * isTransparentLine : 線が透過かどうかを返す。
     * 線が透過かどうか、属性を取得して返す。
	 *
	 * [自由曲線・直線の場合]
	 *		透過属性を取得してMXC_TRUE/MXC_FALSEを返す。
	 * [矩形・楕円・多角形の場合]
	 *		枠線の透過属性を取得してMXC_TRUE/MXC_FALSEを返す。
	 * [スタンプ・署名・OLE・その他の場合]
	 *		常にMXC_FALSEを返す。
     *
     * 返り値：
     * MXC_TRUE     透過表示する
     * MXC_FALSE    透過表示しない
     */
    virtual int isTransparentLine() = 0;

    /**
     * isTransparentFill : 塗りつぶしが透過かどうかを返す。
     * 塗りつぶしが透過かどうか、属性を取得して返す。
	 *
	 * [自由曲線・直線の場合]
	 *		常にMXC_FALSEを返す。
	 * [矩形・楕円・多角形の場合]
	 *		塗りつぶしの透過属性を取得してMXC_TRUE/MXC_FALSEを返す。
	 * [スタンプ・署名・OLE・その他の場合]
	 *		常にMXC_FALSEを返す。
     *
     * 返り値：
     * MXC_TRUE     透過表示する
     * MXC_FALSE    透過表示しない
     */
    virtual int isTransparentFill() = 0;

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCEMFPD
	 * もしくはMXCWMFPDのものとなる。
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;

};

/**
 * MXCImageAnnotation : ラスタ画像アノテーションクラス
 * 
 * ラスタ画像アノテーションを表すクラス。
 * 
 */
class MXCImageAnnotation : public MXCAnnotation {

public:

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCEMFPD
	 * もしくはMXCWMFPDのものとなる。
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;

};

/**
 * MXCTextAnnotation : テキストアノテーションクラス
 * 
 * テキストアノテーションを表すクラス。
 * 
 */
class MXCTextAnnotation : public MXCAnnotation {

public:

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCEMFPD
	 * もしくはMXCWMFPDのものとなる。
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;
	
};

/**
 * MXCLinkAnnotation : リンクアノテーションクラス
 * 
 * リンクアノテーションを表すクラス。
 * 
 */
class MXCLinkAnnotation : public MXCAnnotation {

public:

    /**
     * linkKind : リンクアノテーションの種別を返す。
	 * 種別は
     *		この文書へのリンク（ページ指定）
     *		この文書へのリンク（内部文書指定）
     *		この文書へのリンク（リンクタイトル指定）
     *		別文書へのリンク
     *		URLへのリンク
     *		別ファイルへのリンク
     *		メールアドレスへのリンク
	 * の７種類
     *
	 * 返り値：
	 * MXC_OK           OK
	 * MXC_ERROR        エラー
     */
    virtual int linkKind() = 0;

    /**
     * title : リンクタイトルを返す
     *
	 * 返り値：
     * リンクタイトルのポインタ(char*)
	 * 
     */
    virtual char* title() = 0;

    /**
     * isTransparent : 透過表示をするかどうかを返す
	 * 透過表示であればリンク表示 透過表示でなければボタン表示
     *
     * 返り値：
     * MXC_TRUE     透過表示する
     * MXC_FALSE    透過表示しない
     */
    virtual int isTransparent() = 0;

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCEMFPD
	 * もしくはMXCWMFPDのものとなる。
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;
	
	/**
	 * isDisplayIcon : アイコンを表示するかどうかを返す
	 * アイコンを表示するかどうかを返す(MXC_TRUE/MXC_FALSE)
     *
     * 返り値：
     * MXC_TRUE     アイコンを表示する
     * MXC_FALSE    アイコンを表示しない
     */
	virtual int isDisplayIcon() = 0;
	
	/**
	 * isCustomToolTip : カスタムツールチップが設定されているかどうかを返す
	 *
     * 返り値：
     * MXC_TRUE     カスタムツールチップが設定されている
     * MXC_FALSE    カスタムツールチップが設定されていない
	 */
	virtual int isCustomToolTip() = 0;
	
	/**
	 * customToolTip() : カスタムツールチップ（ユーザーツールチップ）の文言を返す
	 * 
	 * 返り値：
     * カスタムツールチップの文字列(char*)
	 * 取得できなければNULL
	 */
	virtual char* customToolTip() = 0;
};

/**
 * MXCDWPageLinkAnnotation : リンクアノテーション ページ指定クラス
 * 
 * リンクアノテーションの中で「この文書へのリンク（ページ指定）」を表すクラス。
 * 
 */
class MXCDWPageLinkAnnotation : public MXCLinkAnnotation {

public:

     /**
     * page : リンクするページ番号を返す
	 * 通常文書の場合はページ番号を
	 * バインダ文書の場合は通しのページ番号を返す。
	 * 0 の場合はプロファイルを表示
	 * -1 の場合は属性に矛盾がある
     *
     * 返り値：
     * ページ番号(1オリジン)
	 * 0 の場合はプロファイル表示
	 * -1 の場合は属性に矛盾がある
     */
    virtual int page() = 0;

	/**
     * isConflict : リンクが矛盾しているかどうかを返す
	 * 文書へのリンクを示す属性がお互い矛盾しているかどうかを調べ、
	 * 矛盾している場合はフラグをセットする。
	 * このフラグが立っているときには、リンクジャンプの際にメッセージを表示する。
     *
     * 返り値：
     * MXC_TRUE     属性が矛盾する
     * MXC_FALSE    属性が矛盾しない
     */
	virtual int isConflict() = 0;

	/**
     * isBinder : このリンクアノテーションがある文書がバインダー文書かどうかを返す。
     *
     * 返り値：
     * MXC_TRUE     バインダー文書
     * MXC_FALSE    ＤＷ文書
     */
	virtual int isBinder() = 0;

};

/**
 * MXCDWInnerLinkAnnotation : リンクアノテーション 内部文書指定クラス
 * 
 * リンクアノテーションの中で「この文書へのリンク（内部文書指定）」を表すクラス。
 * 
 */
class MXCDWInnerLinkAnnotation : public MXCDWPageLinkAnnotation {

public:

    /**
     * innerDocName : リンク先の内部文書の名前を返す
     *
     * 返り値：
     * 内部文書の名前のポインタ(char*)
     */
    virtual char* innerName() = 0;

     /**
     * innerPage : リンクする内部文書でのページ番号を返す
	 * 通常文書の場合は属性が矛盾するので-1
	 * バインダ文書の場合は内部文書でのページ番号を返す。
	 * 0 の場合はプロファイルを表示
     *
     * 返り値：
     * ページ番号(1オリジン)
	 * 0 の場合はプロファイル表示
	 * -1 の場合は属性に矛盾がある
     */
    virtual int innerPage() = 0;

};

/**
 * MXCDWTitleLinkAnnotation : リンクアノテーション リンクタイトルへのリンククラス
 * 
 * リンクアノテーションの中で「この文書へのリンク（リンクタイトル指定）」を表すクラス。
 * 
 */
class MXCDWTitleLinkAnnotation : public MXCLinkAnnotation {

public:

	/**
     * linkTitle : リンクするリンクアノテーションのタイトルを返す
	 * リンクアノテーションの種別が「同じDocuworks文書」
	 * もしくは「別のDocuworks文書」で、
	 * リンク先の種別(linkDest())が「リンクアノテーションのタイトル」の場合に必要。
     *
     * 引数：
     * リンクアノテーションのタイトルのポインタ(char*)
     *
	 * 返り値：
	 * MXC_OK           OK
	 * MXC_ERROR        エラー
     */
    virtual char* linkTitle() = 0;

     /**
     * page : リンクするリンクアノテーションが存在するページ番号を返す
	 * 通常文書の場合はページ番号を
	 * バインダ文書の場合は通しのページ番号を返す。
	 * リンクアノテーションが見つからない場合は 1 を返す
     *
     * 返り値：
     * ページ番号(1オリジン)
     */
	virtual int page() = 0;
	
};

/**
 * MXCOtherDWLinkAnnotation : リンクアノテーション 別文書へのリンククラス
 * 
 * リンクアノテーションの中で「別文書へのリンク」を表すクラス。
 * 
 */
class MXCOtherDWLinkAnnotation : public MXCLinkAnnotation {

};

/**
 * MXCURLLinkAnnotation : リンクアノテーション URLへのリンククラス
 * 
 * リンクアノテーションの中で「URLへのリンク」を表すクラス。
 * 
 */
class MXCURLLinkAnnotation : public MXCLinkAnnotation {

public:

    /**
     * url : URLを返す
	 * リンクアノテーションの種別が「URL」の場合に必要
     *
	 * 返り値：
     * URLのポインタ(char*)
     *
     */
    virtual char* url() = 0;
	
};

/**
 * MXCOtherFileLinkAnnotation : リンクアノテーション 別ファイルへのリンククラス
 * 
 * リンクアノテーションの中で「別ファイルへのリンク」を表すクラス。
 * 
 */
class MXCOtherFileLinkAnnotation : public MXCLinkAnnotation {

};

/**
 * MXCMailLinkAnnotation : リンクアノテーション メールアドレスへのリンククラス
 * 
 * リンクアノテーションの中で「メールアドレスへのリンク」を表すクラス。
 * 
 */
class MXCMailLinkAnnotation : public MXCLinkAnnotation {

public:

    /**
     * mailAddress : メールアドレスを返す
	 * リンクアノテーションの種別が「メールアドレス」の場合に必要
     *
	 * 返り値：
     * メールアドレスのポインタ(char*)
     *
     */
    virtual char* mailAddress() = 0;

};

/**
 * MXCCustomAnnotation : カスタムアノテーションクラス
 * 
 * カスタムアノテーションを表すクラス。
 * カスタムアノテーションは他のアノテーションを持つことが出来る。
 *
 * since: 
 *  DWVLT70 V7Format 2008.07.14 by akiyoshi.
 */
class MXCCustomAnnotation : public MXCHasChildAnnotation {

public:

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCEMFPD
	 * もしくはMXCWMFPDとなる。
	 * ※このPDが子アノテーションのPDを含むものなのかは現状不明
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;

};

/**
 * MXCGroupAnnotation : グループアノテーションクラス
 * 
 * グループアノテーションを表すクラス。
 * グループアノテーションは他のアノテーションを持つことが出来る。
 *
 * since: 
 *  DWVLT70 V7Format 2008.07.14 by akiyoshi.
 */
class MXCGroupAnnotation : public MXCHasChildAnnotation {

public:

    /**
     * pd : メタファイルPDクラスを返す。
     * メタファイルPDクラス(MXCImagePD)のインスタンスのポインタを返す。
	 * インスタンスは実際にはMXCImagePDのサブクラスであるMXCEMFPD
	 * もしくはMXCWMFPDとなる。
	 * ※このPDが子アノテーションのPDを含むものなのかは現状不明
     *
     * 返り値：
     * メタファイルPDクラスのインスタンスのポインタ
     */
    virtual MXCImagePD* pd() = 0;

};


#endif // __cplusplus

#endif // MXCANNOTATION_H
