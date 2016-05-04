/*!
  @file  XdwLogFile.h
  @brief XdwLogFileクラスの定義を記述したIncludeファイル

  @author Tomohiro Yamada (Fuji Xelox Co., Ltd. DPC DS&S STD) <Tomohiro.Yamada@fujixerox.co.jp>
  @date 2002-04-24
  @version 0.1
 
  Copyright (C) Fuji Xerox Co., Ltd. DPC CS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
 */
#ifndef _XDW_LOG_FILE_H_
#define _XDW_LOG_FILE_H_

/* 列挙型の定義のためのIncludeファイル */
#include "XdwError.h"

/* インターフェースのIncludeファイル */
#include "XdwLogInterface.h"

/* 関連するクラスの宣言 */
class XdwFileIO;

/**
 * @brief DocuWorksDecoder用にLogファイルを記述するためのクラス
 */
class XdwLogFile : public XdwLogInterface
{
public:
    /********************************************/
    /* メソッド */
    
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwLogFile();
    
    /**
     * @brief デストラクタ
     */
    virtual ~XdwLogFile();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @param file_io システムが規定するファイル入出力ラッパーインターフェース
     * @param write_flag 書き込みフラグ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize(XdwFileIO* file_io, bool write_flag = true);
    
    /**
     * @brief Logファイルを開く
     *
     * @param file XdwFileIOインターフェースのインスタンスが認識できるファイル識別子
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Open(void* file);
    
    /**
     * @brief 現在開いているLogファイルを閉じる
     */
    virtual void Close();
    
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
    
    /*! ファイル入出力ラッパー */
    XdwFileIO* fFileIO;
    
    /********************************************/
    /* 属性 */
    
    /*! ファイルポインタ */
    void* fFile;
    /*! 書き込みフラグ */
    bool fWriteFlag;
};

#endif
