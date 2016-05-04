/**
 * @file  XdwCharacterTranslatorLinuxQT.h
 * @brief XdwCharacterTranslatorLinuxQTクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwCharacterTranslatorLinuxQT.h,v 1.4 2009/12/22 08:11:29 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_CHARACTER_TRANSLATOR_LINUX_QT_H_
#define _XDW_CHARACTER_TRANSLATOR_LINUX_QT_H_

/* インターフェースのIncludeファイル */
#include "XdwCharacterTranslator.h"

/**
 * @brief Windows上で文字コードの変換をラップする実装クラス
 */
class XdwCharacterTranslatorLinuxQT : public XdwCharacterTranslator
{
public:
  
    /********************************************/
    /* メソッド */

    /**
     * @brief コンストラクタ
     */
    XdwCharacterTranslatorLinuxQT();
    
    /**
     * @brief デストラクタ
     */
    virtual ~XdwCharacterTranslatorLinuxQT();

    /**
     * @brief 指定された文字コードの文字をUNICODE文字に変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     * @param code XdwCharacterTranslator::CharacterCodeを参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CharacterToUNICODE(unsigned char* src, unsigned char* dst, XdwCharacterTranslator::CharacterCode code);
    
    /**
     * @brief 指定された文字コードの文字をSJIS文字に変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     * @param code XdwCharacterTranslator::CharacterCodeを参照
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode CharacterToSJIS(unsigned char* src, unsigned char* dst, XdwCharacterTranslator::CharacterCode code);
    
    /**
     * @brief ANSI文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ANSItoUNICODE(unsigned char* src, unsigned char* dst);

    /**
     * @brief SYMBOL文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SYMBOLtoUNICODE(unsigned char* src, unsigned char* dst);

    /**
     * @brief SJIS文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SJIStoUNICODE(unsigned char* src, unsigned char* dst);

    /**
     * @brief EUC文字をUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode EUCtoUNICODE(unsigned char* src, unsigned char* dst);

    /**
     * @brief UNICODE文字をSJISに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode UNICODEtoSJIS(unsigned char* src, unsigned char* dst);

    /**
     * @brief EUC文字をSJISに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode EUCtoSJIS(unsigned char* src, unsigned char* dst);

protected:

    /**
     * @brief 指定された文字をMultiByteToWideCharを使用してUNICODEに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     * @param code Windows上でのコードページ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode MtoW(unsigned char* src, unsigned char* dst, unsigned int code);

    /**
     * @brief 指定された文字をWideCharToMultiByteを使用してSJISに変換する
     *
     * @param src 変換前の文字(2byte)
     * @param dst 変換後の文字(2byte)
     * @param code Windows上でのコードページ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode WtoM(unsigned char* src, unsigned char* dst, unsigned int code);
    
};

#endif	/* _XDW_CHARACTER_TRANSLATOR_LINUX_QT_H_ */
