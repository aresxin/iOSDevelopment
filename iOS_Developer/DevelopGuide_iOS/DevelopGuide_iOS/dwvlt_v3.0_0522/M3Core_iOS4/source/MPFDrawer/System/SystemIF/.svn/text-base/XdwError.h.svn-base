/**
 * @file  XdwError.h
 * @brief Error関連用ヘッダファイル
 *
 * Error処理に関する型の宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-03-28
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC CS&S STD Toshio Yamazaki<br>
 * Created:	2002-03-28	Toshio Yamazaki<br>
 */
#ifndef XDWERROR_H_INCLUDED
#define XDWERROR_H_INCLUDED

/*! XDW パッケージのControler用エラーコード定義

  XDWパッケージのControler ( DirectPrint, Viewer, e.t.c.) が，システムへ
  返すエラーコードの定義．<br>
  Controlerは，エラーのシステムへの影響を判断して，
  以下のエラーコードの内，適切なコードをシステムへ返す必要がある．
*/
enum XdwErrorCodeForControler {
    /*! 正常終了 */
    XDW_ERRORCODEFORCONTROLER_SUCCESS = 0,
    /*! 正常終了．表示が不正確，復帰は可能 */
    XDW_ERRORCODEFORCONTROLER_WARNING,
    /*! なんらかのエラー終了．表示が不可能，復帰は可能 */
    XDW_ERRORCODEFORCONTROLER_ERROR,
    /*! なんらかのエラー終了．表示も不可能，復帰も不可能 */
    XDW_ERRORCODEFORCONTROLER_FATAL
};
/*! XDW パッケージ用エラーコード定義

  XDWパッケージに含まれるメソッドが返すエラーコードの定義．
  XDWパッケージに含まれるメソッドは，必ず，このエラーコードを返す．<br>
  以下は，とりあえず作ったもの．必要なものがあれば追加すること.
*/
enum XdwErrorCode {
    XDW_ERRORCODE_SUCCESS = 0,		/*!< 正常終了			*/
    XDW_ERRORCODE_INVALID_ATTRIBUTE,	/*!< 不正な属性			*/
    XDW_ERRORCODE_NOT_IMPLEMENTED,	/*!< 未実装処理			*/
    XDW_ERRORCODE_INSUFFICIENT_MEMORY,	/*!< メモリの確保が不可能	*/
    XDW_ERRORCODE_INVALID_PARAMETER,	/*!< 不正なパラメータ		*/

    /* 020509 Added By T.Yamada */
    /*! メモリアクセス違反 */
    XDW_ERRORCODE_MEMORY_ACCESS_FAULT,
    /*! ファイルアクセス違反 */
    XDW_ERRORCODE_FILE_ACCESS_FAULT,
    /*! ファイルオープンができないことによるエラー */
    XDW_ERRORCODE_FILE_OPEN_ERROR,
    /*! Lockされていてアクセスできない */
    XDW_ERRORCODE_DATA_OBJECT_LOCKED,

    XDW_ERRORCODE_ERROR,/*!< なんらかのエラー		*/

    /* 020510 Added By T.Yamada */
    /*! 初期化されていない */
    XDW_ERRORCODE_NOT_INITIALIZED,

    /* 020517 Added By T.Yamada */
    /*! バイナリデータにアクセスできない */
    XDW_ERRORCODE_BINARY_ACCESS_FAULT,

    /* 020523 Added Bt T.Yamada */
    /*! DWファイルはDESで暗号化されている */
    XDW_ERRORCODE_FILE_ENCRYPTED_DES,

    /* 020603 Added By T.Yamada */
    /*! 引き続き処理が可能 */
    XDW_ERRORCODE_CONTINUE,

    /* 020620 Added By T.Yamada */
    /*! キャッシュの使用不可 */
    XDW_ERRORCODE_NOT_CACHE_USED,

    /* 020828 Added By T.Yamada */
    /*! 未サポートのフォーマットである */
    XDW_ERRORCODE_NOT_SUPPORTED,

    /* 020903 Added By T.Yamada */
    /*! 処理の中断 */
    XDW_ERRORCODE_INTERRUPTION,

    /* 021031 Added By T.Yamada */
	/*! ページが存在しないとき*/
    XDW_ERRORCODE_PAGE_NOT_EXISTED,

	/* 030306 Added By Y.Ito*/
	/*! 未サポートのＯＬＥオブジェクト*/
	XDW_ERRORCODE_OLE_OBJECT,

	/* 031008 Added By Y.Ito*/
	/*! バージョン１と2のファイルのとき*/
	XDW_ERRORCODE_NOT_SUPPORTED_VERSION,

	/* 031017 Added By T.Kitahashi*/
	/*! リンクアノテーションがプロファイル表示へ設定されている */
	XDW_ERRORCODE_LINK_TO_PROFILE,

	/* 031017 Added By T.Kitahashi*/
	/*! リンクアノテーションが他のDWファイルもしくは任意のファイルに設定されている */
	XDW_ERRORCODE_LINK_TO_OTHER_FILE,

	/* 031017 Added By T.Kitahashi*/
	/*! リンクアノテーションの設定に矛盾がある */
	XDW_ERRORCODE_INCONSISTENT_LINK,

    // 031021 Added By N.Yamamoto
    /// オブジェクト (Font, Pen, Brush, Palette) をDeleteしようとしたときに
    // 参照カウントが0で無い場合に返すコード
    XDW_ERRORCODE_REFCOUNT_NOT_ZERO,

	/* AR9099 031125 Added By Y.Ito */
	/*! コンテンツ情報はあるがPDがない場合*/
	XDW_ERRORCODE_NOT_PD_DATA,

	// 040730  Added By Y.Ito 
	// 保護文書対応により追加20
	/*! 保護文書オープンに成功した*/
	XDW_ERRORCODE_CRYPT_OPENED,
	/*! パスワードの入力が必要である*/
	XDW_ERRORCODE_NEED_PSWD,
	/*! 対応していない保護文書である*/
	XDW_ERRORCODE_CRYPT_ERROR,// = XDW_ERRORCODE_FILE_ENCRYPTED_DES
    /* 040817 Added By Y.Ito*/
    /* ページ指定ダイアログで無効な数値のとき*/
    XDW_ERRORCODE_INVALID_PAGE_NUM,
	/*! 文書の改竄を検出
	  VLT5.0では、「ファイルを開けませんでした」というエラーメッセージが出るので、それにあわせる
		*/
    XDW_ERRORCODE_BAD_CHECKSUM,
    /*! リンクのヘルパーアプリのメーラーの設定が間違っている*/
    XDW_ERRORCODE_BAD_MAILER,
    /*! リンクのヘルパーアプリのブラウザの設定が間違っている*/
    XDW_ERRORCODE_BAD_BROWSER
};

#endif /* XDWERROR_H_INCLUDED */
