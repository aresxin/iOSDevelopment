/**
 * @file  XdwDocuWorksAccess.h
 * @brief XdwDocuWorksAccessクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDocuWorksAccess.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_ACCESS_H_
#define _XDW_DOCUWORKS_ACCESS_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "DocuWorksDecoder/Include/XdwDocuWorks.h"

/**
 * @brief DataObjectパッケージへのアクセスを許可するパッケージ
 * 
 * エンディアンの差の吸収や、各種バイナリデータへの表記方法の解釈を提供する
 */
class XdwDocuWorks::Access
{
public:

    /********************************************/
    /* クラス */

    /*! XdwDocuWorks::Access::Interraceインターフェースのインスタンスを作成するクラス */
    class Generator;
    
    /*! ASN.1にアクセスするインターフェース */
    class ASN1Interface;
    
    /*! バイナリデータにアクセスる際に、共通化できる抽象クラス */
    class Common;
    
    /*! Little Endianのバイナリデータにアクセスするクラス */
    class LittleEndianBinary;
    /*! Little EndianのASN.1表記のバイナリデータにアクセスするクラス */
    class ASN1LittleEndianBinary;

};

#endif
