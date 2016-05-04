/** 
 * @file  XdwOffScreenControlerForViewerLightOnCE.h
 * @brief XdwOffScreenControlerForViewerLightOnCEクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreenControlerForViewerLightOnCE.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_CONTROLER_FOR_VIEWER_LIGHT_ON_CE_H_
#define _XDW_OFF_SCREEN_CONTROLER_FOR_VIEWER_LIGHT_ON_CE_H_

/* Windows GDIの定義のためのIncludeファイル */
#include <windows.h>

/* 親クラスのためのIncludeファイル */
#include "XdwOffScreenControlerForViewerLight.h"

/**
 * @brief DocuWorks Viewer Light for Windows CE用のオフスクリーンを管理するための実装クラス
 *
 * XdwOffScreenDIBクラスを管理する<br>
 * アプリケーションは本クラスを利用して、オフスクリーンを管理する
 */
class XdwOffScreenControlerForViewerLightOnCE : public XdwOffScreenControlerForViewerLight
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwOffScreenControlerForViewerLightOnCE();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenControlerForViewerLightOnCE();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
    /**
     * @brief メモリDCを取得する
     *
     * @return  メモリDC
     */
    virtual HDC GetMemoryDC();
    
    /**
     * @brief デフォルトのビットマップハンドルをセットする
     *
     * @param handle ビットマップハンドル
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetDefaultHandle(HBITMAP handle);

    /**
     * @brief デフォルトのビットマップハンドルをメモリDCにセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SelectDefaultHandle();
    
protected:
    
    /********************************************/
    /* 属性 */

    /*! メモリDC */
    HDC fMemoryDC;
    /*! デフォルトのビットマップハンドル */
    HBITMAP fDefaultHandle;
    
};

#endif
