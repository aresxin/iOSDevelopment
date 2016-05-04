/** 
 * @file  XdwFileIOLinuxQT.h
 * @brief XdwFileIOLinuxQTクラスの定義
 *
 * @author
 * @date 2002-3-29
 * @version 1.0
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_FILE_IO_LINUXQT_H_
#define _XDW_FILE_IO_LINUXQT_H_

/* インターフェースのIncludeファイル */
#include "XdwFileIO.h"

#include <vector>
#include <qfile.h>

class XdwFileIOLinuxQT_QFile {
public:
    bool	isUse;
    QFile	file_F;

    XdwFileIOLinuxQT_QFile() : isUse(false) {};
};

typedef XdwStlVector(XdwFileIOLinuxQT_QFile) XdwFileIOLinuxQT_QFileVector;
#define XDWFILEIOLINUQT_QFILEVECTOR_DEFAULTSIZE	5

/**
 * @brief qfileをラップするクラス
 *
 * XdwFileIOインターフェースの実装クラス<br>
 * qfile class をFile Handleでラップできるようにした。
 * ただし、返すのはFile Handleではなくて、
 * 内部QFile Vectorの位置をHandleの代わりに返す。
 * したがって返された値をFile Handleとしては使えない。
 */
class XdwFileIOLinuxQT : public XdwFileIO
{
private:
    XdwFileIOLinuxQT_QFileVector	qfilevectorF;
    /**
     * @brief int番目のQFileオブジェクトを検索する
     * 内部でQFileオブジェクトをVectorで管理しているので、
     * int番目のQFileオブジェクトを返す.<br>
     * Vectorは0基数だが、この引数は1基数であることに注意
     */
    QFile* SearchQFileObject(int);
    /**
     * @brief 空いているQFileオブジェクトを検索する
     * 内部でQFileオブジェクトをVectorで管理しているので、
     * 使われていないQFileオブジェクトの前から何番目かを返す。<br>
     * Vectorは0基数だが、この帰り値は1基数であることに注意
     */
    int SearchEmptyQFileObject(void);
public:
    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwFileIOLinuxQT();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwFileIOLinuxQT();
  
    /**
     * @brief ファイルを開く
     *
     * fopenと動作は同一
     *
     * @param file_name プラットフォーム依存の文字列でファイル名
     * @param mode オープンモード
     *
     * @return ファイルハンドル。定義は見せない。<br>
     * @return エラー時はNULLコード
     */
    virtual void* Open(void* file_name, char* mode);
  
    /**
     * @brief ファイルを閉じる
     *
     * fcloseと動作は同一
     *
     * @param file ファイルハンドル
     *
     * @return なし
     */
    virtual void Close(void* file);

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
    virtual long Read(void* buffer, long size, long n, void* file);

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
    virtual long Write(void* buffer, long size, long n, void* file);

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
    virtual int Seek(void* file, long offset, XdwFileIO::SeekMode mode);

    /**
     * @brief ファイルの現在位置を、ファイル先頭からのbyte数で知らせる
     *
     * ftellと動作は同一<br>
     *
     * @param file ファイルハンドル
     *
     * @return ファイル先頭位置からの現在位置のbyte数
     */
    virtual long Tell(void* file);

    /**
     * @brief 一時記憶用のファイル名を取得する際に必要なByte数を取得する
     *
     * @return 一時記憶用のファイル名を取得する際に必要なByte数
     */
    virtual long GetTmpNamSize();
    
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
    virtual void* TmpNam(void* name);

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
    virtual int Remove(void* filename);
};

#endif	/* #ifndef _XDW_FILE_IO_LINUXQT_H_ */
