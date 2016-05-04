/**
 * @file  XdwGraphicFormatGDIBitmapInfoHeader.h
 * @brief XdwGraphicFormat::GDI::BitmapInfoHeaderクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatGDIBitmapInfoHeader.h,v 1.4 2009/12/22 08:10:55 chikyu Exp $
 *
 * @date 2003-3-27 DPSC S開 S開部 TD-G Yasuhiro Ito <Yasuhiro.Ito@fujixerox.co.jp>
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_GDI_BITMAP_INFO_HEADER_H_
#define _XDW_GRAPHIC_FORMAT_GDI_BITMAP_INFO_HEADER_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatGDI.h"
#include "XdwDocuWorks.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDISize.h"

/**
 * @brief BITMAPINFOHEADER構造体を管理するクラス
 */
class XdwGraphicFormat::GDI::BitmapInfoHeader
{
public:

    /********************************************/
    /* 列挙型 */

    /*! DIBのヘッダサイズ */
    enum BitmapHeaderSize{
        /*! BITMAPCOREHEADER構造体のサイズ */
        BITMAP_CORE_HEADER_BYTES = 12,
        /*! BITMAPINFOHEADER構造体のサイズ */
        BITMAP_INFO_HEADER_BYTES = 40,
        /*! BITMAPV4HEADER構造体のサイズ */
        BITMAP_V4_HEADER_BYTES = 104,
        /*! BITMAPV5HEADER構造体のサイズ */
        BITMAP_V5_HEADER_BYTES = 120
    };
    
    /*! ビットカウント数 */
    enum BitCountType{
        /*! 2色 */
        MONOCHROME = 1,
        /*! 16色 */
        PALETTE_16 = 4,
        /*! 256色 */
        PALETTE_256 = 8,
        /*! フルカラー */
        FULL_COLOR = 24,
        /*! 16Bitマスク */
        MASK_16 = 16,
        /*! 32Bitマスク */
        MASK_32 = 32
    };

    /*! 圧縮形式 */
    enum CompressionType{
        /*! 圧縮なし */
        RAW_BITMAP = 0,
        /*! 8Bit Run Length */
        RUN_LENGTH_8,
        /*! 4Bit Run Length */
        RUN_LENGTH_4,
        /*! Bit Fileds */
        BIT_FIELDS,
        /*! Jpegフォーマット */
        JPEG_FORMAT,
        /*! PNGフォーマット */
        PNG_FORMAT
    };

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    BitmapInfoHeader();

    /**
     * @brief デストラクタ
     */
    virtual ~BitmapInfoHeader();

    /**
     * @brief インスタンスを初期化する
     *
     * @param binary BITMAPINFOHEADER構造体が格納されているバイナリデータ
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Initialize(XdwDocuWorks::BinaryInterface* binary);

    /**
     * @brief BITMAPINFOHEADER構造体の読み込み
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Read();
    
    /**
     * @brief 構造体のByte数の取得
     *
     * @return 構造体の数の取得
     */
    virtual long GetHeaderBytes();
    
    /**
     * @brief 横幅を取得する
     *
     * @return 横幅(pixel単位)
     */
    virtual long GetWidth();
    
    /**
     * @brief 縦幅を取得する
     *
     * @return 縦幅(pixel単位)
     */
    virtual long GetHeight();
    
    /**
     * @brief ビットカウントを取得する
     *
     * @return XdwGraphicFormat::GDI::BitmapInfoHeader::BitCountType参照
     */
    virtual XdwGraphicFormat::GDI::BitmapInfoHeader::BitCountType GetBitCount();
    
    /**
     * @brief 圧縮形式を取得する
     *
     * @return XdwGraphicFormat::GDI::BitmapInfoHeader::CompressionType参照
     */
    virtual XdwGraphicFormat::GDI::BitmapInfoHeader::CompressionType GetCompression();
    
    /**
     * @brief パレットの色数を取得する
     *
     * @return パレットの色数
     */
    virtual long GetColorCounts();
    
    /**
     * @brief イメージのサイズを取得する
     *
     * @return イメージのサイズ
     */
    virtual long GetImageSize();
    
protected:

    /********************************************/
    /* 列挙型 */
    
    enum{
        /*! プレーン数は1しか認めない */
        PLANE_NUM = 1
    };

    /********************************************/
    /* 集約 */

    /*! 画像サイズを管理するクラス */
    XdwGraphicFormat::GDI::Size fSize;
    
    /********************************************/
    /* 関連 */

    /*! BITMAPINFOHEADER構造体が格納されているバイナリデータのインターフェース */
    XdwDocuWorks::BinaryInterface* fBinary;

    /********************************************/
    /* 属性 */

    /* BITMAPINFO構造体の属性 */
    /*! BITMAPINFOHEADER構造体のサイズ */
    long fHeaderSize;
    /*! プレーン数 */
    unsigned short fPlanes;
    /*! ビットカウント */
    unsigned short fBitCount;
    /*! 圧縮 */
    unsigned long fCompression;
    /*! 画像サイズ */
    long fSizeImage;
    /*! x軸方向の解像度 */
    long fXPPM;
    /*! y軸方向の解像度 */
    long fYPPM;
    /*! 使用されている色数 */
    long fColorUsed;
    /*! 重要な色数 */
    long fColorImportant;
    
};

#endif
