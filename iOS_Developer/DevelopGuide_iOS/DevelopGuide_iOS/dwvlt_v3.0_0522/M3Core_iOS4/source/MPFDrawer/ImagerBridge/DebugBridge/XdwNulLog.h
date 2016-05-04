/*!
  @file  XdwNulLog.h
  @brief XdwNulLogクラスの定義を記述したIncludeファイル

  @author Toshiyuki Komoda (Fuji Xelox Co., Ltd.)
  @date 2009-02-24
  @version 1.0
 
  Copyright (C) Fuji Xerox Co., Ltd.<br>
  Created:	2009-02-24	Toshiyuki Komoda<br>
 */
#ifndef _XDW_NUL_LOG_H_
#define _XDW_NUL_LOG_H_

/* 列挙型の定義のためのIncludeファイル */
#include "System/SystemIF/XdwError.h"

/* インターフェースのIncludeファイル */
#include "XdwLogInterface.h"

/* 関連するクラスの宣言 */
class XdwFileIO;

/**
 * @brief Logファイルを記述するためのクラス
 */
class XdwNulLog : public XdwLogInterface
{
public:
    /********************************************/
    /* メソッド */
    
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwNulLog();
    
    /**
     * @brief デストラクタ
     */
    virtual ~XdwNulLog();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @param file_io システムが規定するファイル入出力ラッパーインターフェース
     * @param write_flag 書き込みフラグ
     *
     * @return XdwErrorCode参照
     */
//    virtual XdwErrorCode Initialize(XdwFileIO* file_io, bool write_flag = true);
    
    /**
     * @brief Logファイルを開く
     *
     * @param file XdwFileIOインターフェースのインスタンスが認識できるファイル識別子
     *
     * @return XdwErrorCode参照
     */
//    virtual XdwErrorCode Open(void* file);
    
    /**
     * @brief 現在開いているLogファイルを閉じる
     */
//    virtual void Close();
    
    /**
     * @brief Logを記述する
     *
     * @param log 記述するlogの文字列<br>
     *            ASCIIコード以外は認めない
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode WriteLog(const char* log);
    
protected:
    /********************************************/
    /* 関連 */
    
    /********************************************/
    /* 属性 */

};

#endif
