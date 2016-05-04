/**
 * @file  XdwGraphicFormatRasterMRC.h
 * @brief XdwGraphicFormat::Raster::MRCクラスの定義
 *
 * @author OPSD 5G 54T Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-06-16
 * @version 1.0
 *
 * @author OPSD 5G 54T Norio.Yamamoto@fujixerox.co.jp
 * @date 2004-07-14
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_RASTER_MRC_H_
#define _XDW_GRAPHIC_FORMAT_RASTER_MRC_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatRaster.h"
#include "XdwDataObject.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatParser.h"

/* 集約するクラスのIncludeファイル */
#include "XdwRaster.h"

// IMSからデータを読み出すために使用
#include "XdwDocuWorksAccessLittleEndianBinary.h"

/**
 * @brief DocuWorksファイルのラスターデータを読み込むクラス
 *
 */
class XdwGraphicFormat::Raster::MRC : public XdwGraphicFormat::Parser
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    MRC();

    /**
     * @brief デストラクタ
     */
    virtual ~MRC();

    /**
     * @brief グラフィックデータの横幅を取得する
     *
     * @return グラフィックデータの横幅(pixel単位)
     */
    virtual long GetWidth();

    /**
     * @brief グラフィックデータの縦幅を取得する
     *
     * @return グラフィックデータの縦幅(pixel単位)
     */
    virtual long GetHeight();

    /**
     * @brief パースするグラフィックデータをセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Set();

    /**
     * @brief セットされたグラフィックデータのパースを終了する
     *
     * XdwGraphicFormat::Parser::Parseメソッドを終了する場合(正常終了/異常終了)に、必ず呼ばなければならない
     *
     * @return XdwErrorCodeを参照
     */
    virtual XdwErrorCode Terminate();
    
protected:

    /* 列挙型 */
    enum{
        /* イメージを単純にコピーする */
        ROP_COPY_IMAGE = 0x00CC0020
    };  
    
    /********************************************/
    /* 集約 */
    
    /* イメージの描画属性 */
    XdwRasterImageAttribute fImageAttribute;
    /* マスクデータの描画属性 */
    XdwRasterImageAttribute fMaskAttribute;

    /********************************************/
    /* 関連 */
    
    /* イメージデータを管理するクラス */
    XdwDataObject::Common* fImageData;
    /* マスクデータを管理するクラス */
    XdwDataObject::Common* fMaskData;
    
    /********************************************/
    /* 属性 */
    
    /*! イメージデータのオフセット */
    long fImageOffset;
    /*! マスクデータのオフセット */
    long fMaskOffset;
    /*! イメージデータのサイズ */
    long fImageBytes;
    /*! マスクデータのサイズ */
    long fMaskBytes;
    
    /********************************************/
    /* メソッド */

    /**
     * @brief インスタンスを初期化する
     *
     * 継承クラスは本メソッドを実行するればよい
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();

    /**
     * @brief ラスターの描画属性を初期化する
     *
     * @param attribute 初期化するラスターの描画属性
     *
     * @return XdwErrorCode参照
     */
    virtual void InitializeAttribute(XdwRasterImageAttribute* attribute);

    /**
     * @brief BridgeIFに描画属性をセットする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode SetBridge();
    
    /**
     * @brief MRCデータを一気にパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseAll();

    /**
     * @brief MRCデータを指定されたライン数だけパースする
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode ParseLeg();
private:
	/*! Divided 描画のときのStartフラグ */
	bool fIsDividedInitialize;


    ////////////////////////////////////////////////////////////////////////////
    // MRC関連固有定義 (ここから)

public:
    // 以下はWindows版ソースIMSUtil.hからコピー

    /// IMS内の各オブジェクトのタイプを表す定数
    typedef enum {
        /// 不透明なcontone画像 (8 or 24bpp)
        contone_object = 1,
        /// マスク。次のオブジェクトはcontone_objectでなければならない。
        /// このマスクと次のオブジェクトで、masked imageとして扱われる。
        contone_mask   = 2,
        /// マスク。1はカレントカラーで塗られ、0は透明(現状に影響を与えない)
        color_mask     = 3,
        /// 色付きの矩形
        color_rect     = 4,
        /// JBIG2辞書。1ファイルに1つのみ。
        JBIG2_dict     = 5,
        /// サムネイル。
        thumbnail      = 6,
        /// 不透明な2値画像
        binary_object  = 7,
        /// 最終オブジェクト。numObjectのみが続く特殊なオブジェクト。
        trailer_object = 0xDEADFEED,
    } IMS_ObjectType;

    /// IMS内の各オブジェクトの圧縮種別を表す定数
    typedef enum {
        RAW_pix_intl   = 1, ///< 画素単位のインターリーブ
        RAW_scn_intl   = 2, ///< スキャンライン単位のインターリーブ
        RAW_pln_intl   = 3, ///< 面単位のインターリーブ
        G3MH           = 16,
        G4MMR          = 17,
        JBIG2          = 18,
        XLZ            = 19, ///< Xerox内部の固有形式
        FX_ALLA        = 20, ///< FX拡張
        JPEG           = 32,
        JPEG2000       = 33,
        FX_ABMC        = 34, ///< FX拡張
        oldALLA        = 99, ///< ClientMRCから受け取る場合にのみ用いる。IMS仕様では未定義
                             ///< ALLAv1として扱うべきものだが、市場にはないはずなので、
                             ///< 本Viewerでは未対応
        FX_ALLA_old_def = 16384, ///< FX拡張 (0x4000) 一時期定義されたので念のため対応する
                                 ///< 市場にはないはずだが、FX_ALLAと同じ扱いなので、
                                 ///< 本Viewerでも対応
        FX_ABMC_old_def = 16385, ///< FX拡張 (0x4001) 一時期定義されたのみ
    } IMS_CompressionType;

    /// IMS内の各オブジェクトの色空間を表す定数
    typedef enum {
        binary_one_is_black = 1, ///< 2値空間
        binary_one_is_white = 2,
        deviceGray          = 16, ///< 8bppグレー空間
        linearY             = 17,
        sY                  = 18,
        ITU_LStar           = 19,
        CIE_LStar           = 20,
        FX_LStar            = 21,
        deviceRGB           = 32, ///< 24bppカラー空間
        sRGB                = 33,
        linearSRGB          = 34,
        ITULAB              = 35,
        CIELAB              = 36,
        FXLAB               = 37,
        YCbCr               = 38,
        sYCC                = 39,
    } IMS_ColorSpace;

    // 以上はWindows版ソース IMSUtil.hからコピー


    ////////////////////////////////////////////////////////////////////////////
    /*! IMS Root Headerクラス
     */
    class IMSRootHeader {
    public:
        unsigned long magicNumber_;
        unsigned long versionNumber_;
        unsigned long xDim_;
        unsigned long yDim_;
        unsigned long xRes_;
        unsigned long yRes_;
        unsigned long subSampling_;

        unsigned long objectsNum_;	// trailerを除いたオブジェクト数
    };

    ////////////////////////////////////////////////////////////////////////////
    /*! IMS Root Headerで使う値
     */
    enum {
        ////////////////////////////////////////////////////////////////////////
        /*! マジックナンバー
         */
        MAGIC_NUMBER = 0x736d692e,
        ////////////////////////////////////////////////////////////////////////
        /*! バージョン番号
         *
         * この値より大きいバージョン番号のファイルは処理せずにエラーとする
         * (解釈方法が分からないので)
         */
        VERSION_NUMBER = 0x00010000
    };

    ////////////////////////////////////////////////////////////////////////////
    /*! IMS Object Headerクラス
     */
    class IMSObjectHeader {
    public:
        unsigned long objectType_;
        unsigned long objectXPos_;
        unsigned long objectYPos_;
        unsigned long objectXDim_;
        unsigned long objectYDim_;
        unsigned long w_;
        unsigned long h_;
        unsigned long bytesPerScanline_;
        unsigned long compressionType_;
        unsigned long colorSpace_;
        unsigned long estObjectWhiteSep1_;
        unsigned long estObjectWhiteSep2_;
        unsigned long estObjectWhiteSep3_;
        unsigned long sep1_;
        unsigned long sep2_;
        unsigned long sep3_;
        unsigned long numBytes_;

        ////////////////////////////////////////////////////////////////////////
        /*! ファイル先頭からこのオブジェクト (ヘッダ) までのオフセット (バイト数)
         */
        unsigned long offset_;
    };

private:
    XdwErrorCode ParseIMSHeaders();

    ////////////////////////////////////////////////////////////////////////////
    /*! IMS Root Headerインスタンス
     */
    IMSRootHeader rootHeader_;

    ////////////////////////////////////////////////////////////////////////////
    /*! IMS Object Headerインスタンス
     */
    IMSObjectHeader* objectHeaders_;

    ////////////////////////////////////////////////////////////////////////////
    /*! いろいろなオフセット値 (IMSヘッダ解釈時に使う)
     */
    enum {
        ////////////////////////////////////////////////////////////////////////
        /*! IMS Root Headerの総バイト数 (4バイト × 7)
         */
        ROOT_HEADER_SIZE = 28,
        ////////////////////////////////////////////////////////////////////////
        /*! 各IMS Object Headerの総バイト数 (4バイト × 17)
         */
        OBJECT_HEADER_SIZE = 68,
        ////////////////////////////////////////////////////////////////////////
        /*! IMS Object HeaderのObjectTypeからNumBytesまでのオフセット
         *
         * 4バイト × 15
         */
        OFFSET_OBJECTTYPE_TO_NUMBYTES = 60
    };

    ////////////////////////////////////////////////////////////////////////////
    /*! これから処理する (もしくは現在処理中の) オブジェクトインデックスを保持する
     */
    unsigned long curObjectIndex_;

    XdwErrorCode PrepareContoneParameter(unsigned long index);
    XdwErrorCode PrepareBinaryParameter(
                    unsigned long index,
                    XdwRasterImageAttribute* attr, long* offset, long* bytes);

    XdwErrorCode GetRGBValue(
                    unsigned long index,
                    unsigned char* r, unsigned char* g, unsigned char* b);
    void YCCtoRGB(long y, long cb, long cr,
                    unsigned char* r, unsigned char* g, unsigned char* b);

    ////////////////////////////////////////////////////////////////////////////
    /*! bridgeのRestore()呼び出しが必要かどうか
     *
     * color_mask描画のために, 一時的に単色のブラシを作成し, カレントブラシとする.
     * 他へ影響させないために, bridgeのSave()を呼んでグラフィック状態を保存する.
     * 最終的に (描画が終わったら), グラフィック状態を元に戻すためにRestore()を
     * 呼ぶ必要があるが, それを覚えておくためにフラグ.
     */
    bool needRestore_;

    ////////////////////////////////////////////////////////////////////////////
    /*! 一時的に作成した単色ブラシのhandle
     */
    unsigned long brushHandle_;

    bool IsContoneMaskProcessable();

    XdwErrorCode DrawColorRect();

    // MRC関連固有定義 (ここまで)
    ////////////////////////////////////////////////////////////////////////////
};

#endif
