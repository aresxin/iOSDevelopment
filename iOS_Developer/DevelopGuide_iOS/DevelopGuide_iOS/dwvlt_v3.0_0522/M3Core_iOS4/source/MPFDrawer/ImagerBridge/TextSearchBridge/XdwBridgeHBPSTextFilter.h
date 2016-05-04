/*!
  @file  XdwBridgeHBPSTextFilter.h
  @brief XdwBridgeHBPSTextFilterクラスの定義を記述したIncludeファイル

  @author Tomohiro Yamada (Fuji Xelox Co., Ltd. DPC DS&S STD) <Tomohiro.Yamada@fujixerox.co.jp>
  @date 2002-04-24
  @version 0.1
 
  Copyright (C) Fuji Xerox Co., Ltd. DPC CS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Tomohiro Yamada<br>
 */
#ifndef _XDW_BRIDGE_HBPS_TEXT_FILTER_H_
#define _XDW_BRIDGE_HBPS_TEXT_FILTER_H_

/* 依存するパッケージのIncludeファイル */
#include "XdwDocuWorks.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwError.h"

/* 親クラスの定義のためのIncludeファイル */
#include "XdwBridgeHBPS.h"

/* 関連するクラスのIncludeファイル */
#include "XdwPageTextManager.h"

/**
 * @brief 指定されたコンテント内のテキスト情報を描画しながら、取得するクラス
 */
class XdwBridgeHBPSTextFilter : public XdwBridgeHBPS
{
public:

    /********************************************/
    /* メソッド */
    
    /*! コンストラクタ
      コンストラクタでは，動的メモリの確保は行われない．
      ただし，ポインタのNULL初期化は行われる．
     */
    XdwBridgeHBPSTextFilter();
    /*! デストラクタ
      XdwBridgeが動的に確保したメモリ領域のみFreeされる．
      他のクラスにおいて生成したと思われる領域のFreeは行わない．
     */
    virtual ~XdwBridgeHBPSTextFilter();
    
    /**
     * @brief テキスト取得のための初期化
     *
     * @param page ページ内テキストを管理するクラス
     *
     * @recutn XdwErrorCode参照
     */
    virtual XdwErrorCode InitializeText(XdwPageTextManager* page);
    
    /**
     * @breif コンテントのセット
     *
     * 指定されたコンテントから、テキスト取得位置の設定など<br>
     * CTM設定後でなければならない
     *
     * @param content コンテント情報取得クラス
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode InitializeContent(XdwDocuWorks::ContentManager* content);
    
    /**
     * @breif コンテントの終了
     *
     * 指定されたコンテントの、テキスト取得の終了
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode TerminateContent();
    
protected:
    
    /********************************************/
    /* 関連 */
    
    /*! ページ内テキスト管理クラス */
    XdwPageTextManager* fPage;
    /*! 現在追加する文字列管理クラス */
    XdwDisplayCharacterVector* fText;
    
    /********************************************/
    /* 属性 */
    
    /*! デコンポーザからのテキスト情報取得の有無 */
    bool fTerminateFlag;
    /*! 文字単位のID */
    unsigned long fID;
    
};

#endif
