/**
 * @file  XdwDocuWorksAccessLittleEndianBinary.h
 * @brief XdwDocuWorks::Access::LittleEndianBinaryクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwDocuWorksAccessLittleEndianBinary.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DOCUWORKS_ACCESS_LITTLE_ENDIAN_BINARY_H_
#define _XDW_DOCUWORKS_ACCESS_LITTLE_ENDIAN_BINARY_H_

/* パッケージを記述するためのIncludeファイル */
#include "DocuWorksDecoder/Access/Include/XdwDocuWorksAccess.h"

/* 親クラスを規定するためのIncludeファイル */
#include "XdwDocuWorksAccessCommon.h"

/**
 * @brief Little Endianのバイナリデータにアクセスするためのクラス
 */
class XdwDocuWorks::Access::LittleEndianBinary : public XdwDocuWorks::Access::Common
{
public:
        
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    LittleEndianBinary();

    /**
     * @brief デストラクタ
     */
    virtual ~LittleEndianBinary();

    /**
     * @brief 8BitのByteデータの読み込み
     *
     * 読み込みに成功すると1Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(unsigned char& data);
    
    /**
     * @brief 32BitのLong Wordデータの読み込み
     *
     * 読み込みに成功すると4Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(unsigned long& data);

    /**
     * @brief 32BitのLong Wordデータの読み込み
     *
     * 読み込みに成功すると4Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(long& data);
    
    /**
     * @brief 16BitのWordデータの読み込み
     *
     * 読み込みに成功すると2Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(unsigned short& data);

    /**
     * @brief 16BitのWordデータの読み込み
     *
     * 読み込みに成功すると2Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(short& data);
    
    /**
     * @brief 32BitのFloatデータの読み込み
     *
     * 読み込みに成功すると4Byte移動する
     *
     * @param data 読み込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read(float& data);

    /**
     * @brief 32BitのLong Wordデータの書き込み
     *
     * 書き込みに成功すると4Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(unsigned long data);

    /**
     * @brief 32BitのLong Wordデータの書き込み
     *
     * 書き込みに成功すると4Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(long data);
    
    /**
     * @brief 16BitのWordデータの書き込み
     *
     * 書き込みに成功すると2Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(unsigned short data);

    /**
     * @brief 16BitのWordデータの書き込み
     *
     * 書き込みに成功すると2Byte移動する
     *
     * @param data 書き込むデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Write(short data);
    
protected:

};

#endif
