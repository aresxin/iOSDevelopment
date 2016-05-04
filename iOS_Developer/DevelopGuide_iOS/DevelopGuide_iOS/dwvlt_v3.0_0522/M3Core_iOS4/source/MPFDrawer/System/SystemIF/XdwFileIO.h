/**
 * @file  XdwFileIO.h
 * @brief XdwFileIOインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwFileIO.h,v 1.6 2009/12/22 08:11:35 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_FILE_IO_H_
#define _XDW_FILE_IO_H_

/**
 * @interface XdwFileIO XdwFileIO.h
 * @brief システム依存のファイル入出力をラップするインターフェース
 * 
 * 標準ファイルIO関数のように各メソッドを用いる
 */
class XdwFileIO
{
public:
    /********************************************/
    /* 列挙型 */

    /*! Seek時のデータの開始位置 */
    enum SeekMode{
        /*! データ先頭から */
        START,
        /*! データ終端から */
        END,
        /*! 現在位置から */
        CURRENT
    };
  
    /********************************************/
    /* メソッド */
    
    /**
     * @brief デストラクタ
     */
    virtual ~XdwFileIO() = 0;
    
    /**
     * @brief ファイルを開く
     *
     * fopenと動作は同一
     *
     * @param file_name char型のファイル名
     * @param mode オープンモード(標準ファイル入出力に完全準拠)
     *
     * @return ファイルハンドル。定義は見せない。<br>
     * @return エラー時はNULLコード
     */
    virtual void* Open(void* file_name, char* mode) = 0;
    
    /**
     * @brief ファイルを閉じる
     *
     * fcloseと動作は同一
     *
     * @param file ファイルハンドル
     *
     * @return なし
     */
    virtual void Close(void* file) = 0;

    /**
     * @brief ファイルから指定されたバッファに読み込む
     *
     * freadと動作は同一
     *
     * @param buffer バッファ
     * @param size 一度に読み込むサイズ
     * @param n 読み込む回数
     * @param file ファイルハンドル
     *
     * @return ファイルからバッファに読み込んだ回数
     */
    virtual long Read(void* buffer, long size, long n, void* file) = 0;

    /**
     * @brief 指定されたバッファからファイルに書き込む
     *
     * fwirteと動作は同一<br>
     *
     * @param buffer バッファ
     * @param size 一度に書き込むサイズ
     * @param n 書き込む回数
     * @param file ファイルハンドル
     *
     * @return ファイルからバッファに書き込んだ回数
     */
    virtual long Write(void* buffer, long size, long n, void* file) = 0;

    /**
     * @brief ファイルの現在位置を、指定されたモードでオフセット分移動する
     *
     * fseekと動作は同一<br>
     *
     * @param file ファイルハンドル
     * @param offset オフセット
     * @param mode XdwFileIO::SeekModeを参照
     *
     * @return 成功の場合は0、失敗の場合は0以外
     */
    virtual int Seek(void* file, long offset, XdwFileIO::SeekMode mode) = 0;

    /**
     * @brief ファイルの現在位置を、ファイル先頭からのbyte数で知らせる
     *
     * ftellと動作は同一<br>
     *
     * @param file ファイルハンドル
     *
     * @return ファイル先頭位置からの現在位置のbyte数
     */
    virtual long Tell(void* file) = 0;

    /**
     * @brief 一時記憶用のファイル名を取得する際に必要なByte数を取得する
     *
     * @return 一時記憶用のファイル名を取得する際に必要なByte数
     */
    virtual long GetTmpNamSize() = 0;
    
    /**
     * @brief 一時記憶用のファイルを作成するための、ファイル名を取得する
     *
     * tmpnamと動作は同一<br>
     *
     * @param name TmpNamメソッドが作成した名前を書き込むバッファ<br>
     *             必ず指定しなければならない
     *
     * @return 引数nameのポインタ<br>
     * @return エラー時はNULLコード。
     */
    virtual void* TmpNam(void* name) = 0;

    /**
     * @brief 指定されたファイル名のファイルを削除する
     *
     * removeと動作は同一
     *
     * @param filename 削除するファイル名
     *
     * @retval 0 成功
     * @retval 0以外　失敗
     */
    virtual int Remove(void* filename) = 0;

   /**
     * @brief 一時記憶用のファイルを作成する
     * 	省メモリ対策 新規追加 09/07/02 M.Chikyu
     *
     * tmpfileと動作は同一<br>
     *
     * @return 一時ファイルのFILEポインタ<br>
     * @return エラー時はNULLコード。
     */
// WinMobile対応 パラメータ追加 09/09/11 M.Chikyu
#if defined _PF_WIN32_ || defined _PF_WINCE_
	virtual void* TmpFile(long fileSize = 0) = 0;
#else
	virtual void* TmpFile(void) = 0;
#endif
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwFileIO::~XdwFileIO()
{
}

#endif
