/**
 * @file  XdwCharacterTranslator.h
 * @brief XdwCharacterTranslatorインターフェースの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwCharacterTranslator.h,v 1.4 2009/12/22 08:11:34 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_CHARACTER_TRANSLATOR_H_
#define _XDW_CHARACTER_TRANSLATOR_H_

/* 列挙型のIncludeファイル */
#include "XdwError.h"

/**
 * @interface XdwCharacterTranslator XdwCharacterTranslator.h
 * @brief 文字コードの変換をラップするインターフェース
 * 
 * 1文字(1byte or 2byte)を変換するメソッドを提供する
 */
class XdwCharacterTranslator
{
public:
    /********************************************/
    /* 列挙型 */

    /*! サポートする文字コード */
    enum CharacterCode{
        /*! ANSI */
        ANSI_CODE,
        /*! Symbol */
        SYMBOL_CODE,
        /*! UNICODE */
        UNICODE_CODE,
        /*! Shift JIS */
        SJIS_CODE,
        /*! EUC */
        EUC_CODE
    };
  
    /********************************************/
    /* メソッド */
    
    /**
     * @brief デストラクタ
     */
    virtual ~XdwCharacterTranslator() = 0;

    /**
     * @brief 指定された文字コードの文字をUNICODE文字に変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     * @param code XdwCharacterTranslator::CharacterCodeを参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CharacterToUNICODE(unsigned char* src, unsigned char* dst, XdwCharacterTranslator::CharacterCode code) = 0;
    
    /**
     * @brief 指定された文字コードの文字をSJIS文字に変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     * @param code XdwCharacterTranslator::CharacterCodeを参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CharacterToSJIS(unsigned char* src, unsigned char* dst, XdwCharacterTranslator::CharacterCode code) = 0;
    
    /**
     * @brief ANSI文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ANSItoUNICODE(unsigned char* src, unsigned char* dst) = 0;

    /**
     * @brief SYMBOL文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SYMBOLtoUNICODE(unsigned char* src, unsigned char* dst) = 0;

    /**
     * @brief SJIS文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SJIStoUNICODE(unsigned char* src, unsigned char* dst) = 0;

    /**
     * @brief EUC文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode EUCtoUNICODE(unsigned char* src, unsigned char* dst) = 0;

    /**
     * @brief UNICODE文字をSJISに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode UNICODEtoSJIS(unsigned char* src, unsigned char* dst) = 0;

    /**
     * @brief EUC文字をSJISに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode EUCtoSJIS(unsigned char* src, unsigned char* dst) = 0;
    
};

/********************************************/
/* inline関数 */

/**
 * @brief デストラクタ
 */
inline XdwCharacterTranslator::~XdwCharacterTranslator()
{
}

#endif
