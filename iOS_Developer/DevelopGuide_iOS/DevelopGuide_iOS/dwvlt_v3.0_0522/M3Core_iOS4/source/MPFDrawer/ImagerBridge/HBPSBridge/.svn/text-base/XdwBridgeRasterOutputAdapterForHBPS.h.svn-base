// Copyright (C) 2002-2004 Fuji Xerox Co.,Ltd. All rights reserved.

/*!
 * @file  XdwBridgeRasterOutputAdapter.h
 * @brief XdwBridgeRasterOutputAdapter関連ヘッダファイル
 *
 * XdwBridgeRasterOutputAdapter classの宣言等
 *
 * @author Toshio Yamazaki (DPC DS&S STD)
 * @date 2002-07-18
 *
 * 分割描画対応: 2002-10-07 Kenichi Ishida<br>
 * MRC対応: 2004-07-22 Norio Yamamoto (OPBG SD5G 54T)<br>
 */

#ifndef XDW_BRIDGE_RASTER_OUTPUT_ADAPTER_H_INCLUDED
#define XDW_BRIDGE_RASTER_OUTPUT_ADAPTER_H_INCLUDED

#include "XdwError.h"
#include "XdwRaster.h"

class XdwBridgeDecodeStrategy;
class XdwBridgeGraphicStateManager;

////////////////////////////////////////////////////////////////////////////////
/*! Image出力用 Adapter class
 *
 * Raseter Imageを出力するクラスのI/F定義クラス.
 * 各クラスは, このクラスを継承して, XdwBridgeRasterManagerをclientとした
 * Adapter Patternを構成する.
 */
class XdwBridgeRasterOutputAdapter {
public:
    XdwBridgeRasterOutputAdapter() {}
    virtual ~XdwBridgeRasterOutputAdapter() {}

    virtual XdwErrorCode Draw(const XdwRasterImageAttribute& img_attr,
                                XdwBridgeDecodeStrategy* image,
                                const XdwRasterImageAttribute& mask_attr,
                                XdwBridgeDecodeStrategy* mask) = 0;

    virtual XdwErrorCode DrawPattern(const XdwRasterImageAttribute& img_attr,
                                        XdwBridgeDecodeStrategy* image) = 0;

    virtual XdwErrorCode StartDrawDivided(
                            const XdwRasterImageAttribute& img_attr,
                            XdwBridgeDecodeStrategy* image,
                            const XdwRasterImageAttribute& mask_attr,
                            XdwBridgeDecodeStrategy* mask, long nlines) = 0;

    virtual XdwErrorCode DrawDivided() = 0;

    virtual XdwErrorCode EndDrawDivided() = 0;

    ////////////////////////////////////////////////////////////////////////////
    /*! @name サーポート問い合わせI/F
     * XdwBridgeRasterOutputAdapterの出力先がサポートする,
     * 圧縮形式・ラスター形式等を問い合わせる関数
     */

    /*@{*/

    virtual bool IsIndexedRasterSupport() = 0;

    virtual void setDrawMethod(int) = 0;

    /*@}*/
};

////////////////////////////////////////////////////////////////////////////////
class XdwBridgeRasterOutputAdapterForHBPS
        : public XdwBridgeRasterOutputAdapter {
public:
    XdwBridgeRasterOutputAdapterForHBPS() {}
    XdwBridgeRasterOutputAdapterForHBPS(void*, XdwBridgeGraphicStateManager*);
    ~XdwBridgeRasterOutputAdapterForHBPS() {}

    ////////////////////////////////////////////////////////////////////////////
    /*! Raster Imageまたはmaskの描画開始
     *
     * イメージとマスク描画をここで選択する.
     *
     * @param img_attr Image属性
     * @param image Image
     * @param mask_attr Mask属性
     * @param mask Mask
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_ERROR エラー終了
     */
    XdwErrorCode Draw(const XdwRasterImageAttribute& img_attr,
                        XdwBridgeDecodeStrategy* image,
                        const XdwRasterImageAttribute& mask_attr,
                        XdwBridgeDecodeStrategy* mask);

    ////////////////////////////////////////////////////////////////////////////
    /*! Raster Imageまたはmaskパターンの描画開始
     *
     * イメージとマスク描画をここで選択する.
     *
     * @param img_attr Image属性
     * @param image Image
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_ERROR エラー終了
     */
    XdwErrorCode DrawPattern(const XdwRasterImageAttribute& img_attr,
                                XdwBridgeDecodeStrategy* image);

    ////////////////////////////////////////////////////////////////////////////
    /*! Raster Imageまたはmaskの分割描画開始
     *
     * 分割描画指定の場合にイメージとマスク描画をここで選択する.
     *
     * @param img_attr Image属性
     * @param image Image
     * @param mask_attr Mask属性
     * @param mask Mask
     * @param nlines 一回に描画するライン数
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_ERROR エラー終了
     */
    XdwErrorCode StartDrawDivided(
                    const XdwRasterImageAttribute& img_attr,
                    XdwBridgeDecodeStrategy* image,
                    const XdwRasterImageAttribute& mask_attr,
                    XdwBridgeDecodeStrategy* mask, long nlines);

    ////////////////////////////////////////////////////////////////////////////
    /*! Raster Imageの分割描画
     *
     * DrawImageが分割描画指定の場合にここでHostBasedに描画命令を送る.
     *
     * @param なし
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_CONTINUE 未処理のイメージあり
     * @retval XDW_ERRORCODE_ERROR エラー終了
     */
    XdwErrorCode DrawDivided();

    ////////////////////////////////////////////////////////////////////////////
    /*! Raster Imageの分割描画終了処理
     *
     * メモリ解放などの終了処理を行う.
     *
     * @param なし
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_ERROR エラー終了
     */
    XdwErrorCode EndDrawDivided();

    bool IsIndexedRasterSupport();
    void setDrawMethod(int);

private:
    XdwErrorCode DrawImage(const XdwRasterImageAttribute&,
                            XdwBridgeDecodeStrategy*, long);
    XdwErrorCode DrawMask(const XdwRasterImageAttribute&,
                            XdwBridgeDecodeStrategy*, long);

    XdwErrorCode DrawImagePattern(const XdwRasterImageAttribute&,
                                    XdwBridgeDecodeStrategy*, long);

    XdwErrorCode GenerateMatrixForDrawImage(double, double, double, double, XdwMatrix*);

    unsigned char* GeneratePalette(const XdwRasterImageAttribute&);
    unsigned char* GeneratePaletteBW(const XdwRasterImageAttribute&);

    XdwErrorCode GetLineSize(int, int, long, long*);

    // 共通で使用される変数
    void* imagerF;	// Imagerのハンドル
    XdwBridgeGraphicStateManager* gstateF;

    // Decoder (Image, Maskデータの読み出し元)
    XdwBridgeDecodeStrategy* imageF;
    XdwBridgeDecodeStrategy* maskF;

    // Image, Mask共通属性
    unsigned short widthF, heightF;		// マスク&イメージデータの幅高さ
    double srcWidthF, srcHeightF;		// ソースの幅高さ
    double sxF;							// 描画開始x座標
    double syF;							// 描画開始y座標
    double dstWidthF, dstHeightF;		// 出力画像の幅高さ
    XdwMatrix mappingMatrixF;			// イメージ変換行列
    unsigned short compressionMethodF;	// 圧縮方式 (現状非圧縮のみ)

    // Image固有属性
    unsigned short colorSpaceF;			// 色空間 (イメージなしの場合は未使用)
    unsigned short imageDataDepthF;		// イメージデータの深さ
    unsigned short orderF;				// イメージデータの色順次
    unsigned short colorDepthF;			// paletteDataのdepth (Indexed Colorでない場合は未使用)
    unsigned short paletteEntriesF;		// palettetableのエントリー数 (Indexed Colorでない場合は未使用)
    unsigned short paletteByteSizesF;	// palettetableのバイト数 (Indexed Colorでない場合は未使用)
    unsigned char* paletteF;			// palette tableデータ

    // 処理方法の指定
    long nlinesF;						// 一回に描画するライン数
    int drawMethodF;					// 描画モード

    // 処理用変数
    unsigned char* imgBufferF;			// デコードされるデータを格納するバッファ (Image)
    unsigned char* maskBufferF;			// デコードされるデータを格納するバッファ (Mask)

    long imgLineSizeF;					// イメージ１ライン分のサイズ (Image)
    long maskLineSizeF;					// イメージ１ライン分のサイズ (Mask)

    double currentLineF;				// 現在描画中のライン
    double sySkipF;						// y座標のスキップ数
};

#endif	// XDW_BRIDGE_RASTER_OUTPUT_ADAPTER_H_INCLUDED
