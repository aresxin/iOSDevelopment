/** 
 * @file  XdwOkdCommon.h
 * @brief XdwOkdCommonクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOkdCommon.h,v 1.4 2009/12/22 08:11:00 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OKD_COMMON_H_
#define _XDW_OKD_COMMON_H_

/* 関連するパッケージのIncludeファイル */
#include "XdwDataObject.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwError.h"

/**
 * @brief OKD圧縮されたバイナリーデータを伸張するためのメソッドを共通化したクラス
 *
 * XdwDataObject::Common中の圧縮データを伸張する
 */
class XdwOkdCommon
{
protected:
    /********************************************/
    /* 列挙型 */
//マクロがバッティングするので修正(t.kitahashi 2003.1.16)
#ifdef CHAR_BIT
#undef CHAR_BIT
    enum{CHAR_BIT = 8};
#define CHAR_BIT 8
#else
    enum{CHAR_BIT = 8};
#endif

#ifdef UCHAR_MAX
#undef UCHAR_MAX
    enum{UCHAR_MAX = ((1 << (sizeof(unsigned char) * 8)) - 1)};
#define UCHAR_MAX 0xff
#else
    enum{UCHAR_MAX = ((1 << (sizeof(unsigned char) * 8)) - 1)};
#endif

    enum{
        //CHAR_BIT = 8,
        USHRT_BIT = 16,
        //UCHAR_MAX = ((1 << (sizeof(unsigned char) * 8)) - 1),
        THRESHOLD = 3,
        MAXMATCH = 256,
        NC = (UCHAR_MAX + MAXMATCH + 2 - THRESHOLD),
        CBIT = 9,
        DICBIT= 13,
        NP = (DICBIT + 1),
        NT = (USHRT_BIT + 3),
        PBIT = 4,
        TBIT = 5,
        NPT = 0x80
    };
    
public:    
    /********************************************/
    /* 列挙型 */
    enum{
        /*! 辞書サイズ */
          DIC_SIZE =  5120000
       /* AR11807対応 辞書サイズ(名前はそうだが、実際はOKD展開バッファサイズでしかつかわない)*/
//        DIC_SIZE = (1 << DICBIT)


    };
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    XdwOkdCommon();

    /**
     * @brief デストラクタ
     */
    virtual ~XdwOkdCommon();
    
    /**
     * @brief 関連のセット
     *
     * @param data 圧縮データが格納されているXdwDataObject::Commonのインスタンス
     * @param offset 圧縮データまでのデータ先頭からのオフセット
     * @param size 圧縮データのサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set(XdwDataObject::Common* data, long offset, long size);
    
protected:

    /********************************************/
    /* 関連 */

    /*! 圧縮データが格納されているデータオブジェクト */
    XdwDataObject::Common* fPackedData;
    
    /********************************************/
    /* 属性 */

    /*! 圧縮データサイズ */
    long fPackedSize;
    /*! データ先頭からのオフセット */
    long fPackedOffset;
    /*! 現在のデコード位置 */
    long fPackedCT;

    /********************************************/
    /* 以下流用 */
    
    unsigned char fSubBitBuf;
    unsigned char fBitCount;
    unsigned short fBitBuf;
    unsigned short fHufBlockSize;

    unsigned char* fHufCLen;
    unsigned char* fHufPtLen;
    unsigned short* fHufPtTable;
    unsigned short* fHufCTable;
    
    unsigned short* fDecLeft;
    unsigned short* fDecRight;
    
    /********************************************/
    /* メソッド */
    
    /**
     * @brief 属性の初期化
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode InitialAttribute();
    
    /**
     * @brief 属性の削除
     */
    virtual void Delete();

    /********************************************/
    /* 以下流用 */
    
    virtual unsigned int DecodePSt1(void);    //RETURN : RANGE_SHORT
    virtual unsigned int DecodeCSt1(void);    //RETURN : RANGE_SHORT

    virtual unsigned int GetBits(unsigned char n);    //RETURN : RANGE_SHORT
    virtual void ReadPtLen(short nn, unsigned char nbit, short i_special);
    virtual void ReadCLen(void);
    virtual void FillBuf(unsigned char n);
    virtual void MakeTable(short nchar, unsigned char* bitlen, short tablebits, unsigned short* table);
    
};

#endif
