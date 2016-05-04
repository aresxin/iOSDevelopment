/** 
 * @file  XdwDocuWorksAccessGenerator.h
 * @brief XdwDocuWorks::Generatorインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDocuWorksAccessGenerator.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_ACCESS_GENERATOR_H_
#define _XDW_DOCUWORKS_ACCESS_GENERATOR_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwDocuWorksAccess.h"

/**
 * @brief XdwDocuWorks::Access::Interraceインターフェースのインスタンスを作成するクラス
 *
 * ファイルフォーマットなどによって、特別なインターフェースのインスタンスも作成する
 */
class XdwDocuWorks::Access::Generator
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     *
     * 初期化関数を呼ばなければ、使用できない
     */
    Generator();

    /**
     * @brief デストラクタ
     */
    virtual ~Generator();

    /**
     * @brief DocuWorksファイルにアクセスするためのXdwDocuWorks::Access::ASN1Interfaceインターフェースのインスタンスの作成
     *
     * @return XdwDocuWorks::Access::ASN1Interfaceインターフェースのインスタンス<br>
     */
    virtual XdwDocuWorks::Access::ASN1Interface* CreateDocuWorks();
    
};

#endif
