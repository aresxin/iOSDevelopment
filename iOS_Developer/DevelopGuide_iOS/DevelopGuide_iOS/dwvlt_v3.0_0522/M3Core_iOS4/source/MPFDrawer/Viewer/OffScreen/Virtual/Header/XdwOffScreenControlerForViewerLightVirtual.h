/** 
 * @file  XdwOffScreenControlerForViewerLightVirtual.h
 * @brief XdwOffScreenControlerForViewerLightVirtualクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOffScreenControlerForViewerLightVirtual.h,v 1.4 2009/12/22 08:11:40 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_CONTROLER_FOR_VIEWER_LIGHT_VIRTUAL_H_
#define _XDW_OFF_SCREEN_CONTROLER_FOR_VIEWER_LIGHT_VIRTUAL_H_

/* 親クラスのためのIncludeファイル */
#include "XdwOffScreenControlerForViewerLight.h"

/**
 * @brief DocuWorks Viewer Light Virtual 用のオフスクリーンを管理するための実装クラス
 *
 * XdwOffScreenVirtualクラスを管理する<br>
 * アプリケーションは本クラスを利用して、オフスクリーンを管理する
 * OSやWindow環境に依存しない
 */
class XdwOffScreenControlerForViewerLightVirtual : public XdwOffScreenControlerForViewerLight
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwOffScreenControlerForViewerLightVirtual();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenControlerForViewerLightVirtual();
    
    /**
     * @brief インスタンスを初期化する
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
    
    
protected:
    
    /********************************************/
    /* 属性 */
    
};

#endif
