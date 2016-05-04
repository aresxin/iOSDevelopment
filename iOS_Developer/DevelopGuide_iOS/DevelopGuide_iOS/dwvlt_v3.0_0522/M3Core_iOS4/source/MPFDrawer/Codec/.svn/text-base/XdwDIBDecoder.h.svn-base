/*!
  @file  XdwDIBDecoder.h
  @brief XdwDIBDecoder関連ヘッダファイル

  DIBデータをDecodeするclassの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-07-23
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-07-23	Toshio Yamazaki<br>
 */
#ifndef XDWDEIBDECODER_H_INCLUDED
#define XDWDEIBDECODER_H_INCLUDED

typedef long	XdwDIB_FixedPoint2dot30;

/*! CIEカラー値
 *
 * CIEカラースペースで表現されたカラー値を示すための構造体．
 * 元はWINGDI.HのCIEXYZT．どうも固定小数点表記らしいが詳細は不明．
 * 2.30の固定小数点ってどういう意味？
 */
typedef struct
{
    XdwDIB_FixedPoint2dot30	ciexyz_xF;	/*!< CIE XYZ X値 */
    XdwDIB_FixedPoint2dot30	ciexyz_yF;	/*!< CIE XYZ Y値 */
    XdwDIB_FixedPoint2dot30	ciexyz_zF;	/*!< CIE XYZ Z値 */
} XdwDIB_CIEXYZ;

/*! CIE ColorSpaceでのRGB値
 *
 * CIEカラースペースにおける，Red, Green, Blue各原色の値．
 * 元はWINGDI.HのCIEXYZTRIPLE．end pointって記述があるから，
 * 原色の値でいいと思う．厳密な色空間はCIE 1931 XYZらしい．
 */
typedef struct
{
    XdwDIB_CIEXYZ	redF;	/*!< Red end point color value		*/
    XdwDIB_CIEXYZ	greenF;	/*!< Green end point color value	*/
    XdwDIB_CIEXYZ	blueF;	/*!< Blue end point color value		*/
} XdwDIB_CIEXYZ_Triple;

/*! DIBの圧縮方式の指定
 *
 * DIB中のBitmapの圧縮方式を指定する．
 */
enum XdwDIB_CompressionType {
    XDWDIB_COMPRESSIONTYPE_RGB = 0,		/*!< 非圧縮				*/
    XDWDIB_COMPRESSIONTYPE_RLE8 = 1,		/*!< 8bps画素のrun-length encoding	*/
    XDWDIB_COMPRESSIONTYPE_RLE4 = 2,		/*!< 4bps画素のrun-length encoding	*/
    XDWDIB_COMPRESSIONTYPE_BITFIELDS = 3,	/*!< 非圧縮．カラーテーブルの色値がマスクで指定される*/
    XDWDIB_COMPRESSIONTYPE_JPEG = 4,		/*!< JPEG				*/
    XDWDIB_COMPRESSIONTYPE_PNG = 5		/*!< PNG				*/
};

/*! DIB Coreヘッダ
 *
 * DIBフォーマットのCoreヘッダ．
 * どうも，Win 3.x頃のDIBのヘッダらしい．
 */
typedef struct
{
    unsigned long	SizeF;		/*!< Headerのサイズ [byte]	*/
    long		WidthF;		/*!< bitmap幅 [pixel]		*/

    /*! bitmap高さ [pixel]		*/
    /* BitMapの高さを指定．		*/
    /* 正ならbottom-up DIB		*/
    /* 負ならtop-down DIB		*/
    long		HeightF;

    unsigned short	PlanesF;	/*!< 常に1			*/

    /*! bits-per-pixel
     * 1ピクセルのビット数を指定する<br>
     *
     * 0 : JPEG/PNGの圧縮フォーマット中に記述<br>
     * 1 : モノクロ<br>
     * 4 : 16色<br>
     * 8 : 256色<br>
     * 16: 2^16色<br>
     * 24: 2^24色<br>
     * 32: 2^24色<br>
     */
    unsigned short	BitCountF;
} XdwDIB_BitmapCoreInfoHeader;

/*! DIBヘッダ
 *
 * DIBフォーマットのヘッダ．
 * ただし，NT4.0, Win95で生成されたならXdwDIB_BitmapInfoHeader_V4を，
 * Win2k, Win98以降で生成されたならXdwDIB_BitmapInfoHeader_V5が使われる．
 * もっとも前半は一緒なのでXDWDIB_BitmapInfoHeaderだけで事足りるけど.<br>
 * 元は，BITMAPINFOHEADER.
 */
typedef struct
{
    XdwDIB_BitmapCoreInfoHeader	CoreF;	/*!< CoreHeader					*/
    unsigned long	CompressionF;	/*!< XdwDIB_CompressionTypeで指定される圧縮手法	*/
    unsigned long	SizeImageF;	/*!< Imageの実サイズ．				*/
    long		XPelsPerMeterF;	/*!< X軸方向解像度				*/
    long		YPelsPerMeterF;	/*!< Y軸方向解像度				*/
    unsigned long	ClrUsedF;	/*!< 色テーブル中のcolor index数		*/
    unsigned long	ClrImportantF;	/*!< 表示に必要なcolor index数			*/
} XdwDIB_BitmapInfoHeader;

/*! DIBヘッダVersion 4
 *
 * DIBフォーマットのヘッダ．ただし，NT4.0, Win95で追加されたやつ．
 * 共通なメンバはXdwDIB_BitmapInfoHeaderにまとめた
 */
typedef struct {
    XdwDIB_BitmapInfoHeader	BaseF;		/*!< 共通のヘッダ			*/
    unsigned long		RedMaskF;	/*!< ピクセル中のRedを指定するマスク	*/
    unsigned long		GreenMaskF;	/*!< ピクセル中のGreenを指定するマスク	*/
    unsigned long		BlueMaskF;	/*!< ピクセル中のBlueを指定するマスク	*/
    unsigned long		AlphaMaskF;	/*!< ピクセル中のα Planeを指定するマスク*/
    unsigned long		CSTypeF;	/*!< DIBの色空間を指定			*/
    XdwDIB_CIEXYZ_Triple	EndpointsF;	/*!< CIE CMS用				*/
    unsigned long		GammaRedF;	/*!< CIE CMS用				*/
    unsigned long		GammaGreenF;	/*!< CIE CMS用				*/
    unsigned long		GammaBlueF;	/*!< CIE CMS用				*/
} XdwDIB_BitmapInfoHeader_V4;

/*! DIBヘッダVersion 5
 *
 * DIBフォーマットのヘッダ．ただし，Win2k, Win98で追加されたやつ．
 * 共通なメンバはXdwDIB_BitmapInfoHeader,XdwDIB_BitmapInfoHeader_V4にまとめた
 */
typedef struct {
    XdwDIB_BitmapInfoHeader	BaseF;	/*!< 共通のヘッダ			*/
    XdwDIB_BitmapInfoHeader_V4	V4F;	/*!< Version 4 で追加されたメンバ	*/
    unsigned long	IntentF;	/*!< ICM用				*/
    unsigned long	ProfileDataF;	/*!< ICM用プロファイルデータまでのオフセット [byte]*/
    unsigned long	ProfileSizeF;	/*!< ICM用プロファイルデータサイズ [byte]*/
    unsigned long	ReservedF;	/*!< ICM用				*/
} XdwDIB_BitmapInfoHeader_V5;

/*! RGB色値
 *
 * パレットの配列に使われるRGB色値.
 */
typedef struct {
    unsigned char	BlueF;	/*!< Blue intensity	*/
    unsigned char	GreenF;	/*!< Green intensity	*/
    unsigned char	RedF;	/*!< Red intensity	*/
    unsigned char	ReservedF;
} XdwDIB_RGBQuad;

/*! DIBヘッダ実体
 *
 * DIBの実体．ヘッダとRGBで表されるテーブルの配列で構成される.
 * ファイルの場合はこの前にXdwIB_BitmapFileHeaderが付く.
 */
typedef struct {
    XdwDIB_BitmapInfoHeader	HeaderF;	/*!< Header情報				*/
    XdwDIB_RGBQuad		ColorsF[1];	/*!< 色パレットテーブル．無い場合もある	*/
} XdwDIB_BitmapInfomation;

/*! DIBファイル用ヘッダ
 *
 * DIBがファイルとして使用される時に，先頭に追加されるヘッダ．
 * この後に，XdwDIB_BitmapInfomationが続く.
 */
typedef struct {
    unsigned short	TypeF;		/*!< DIBファイルフォーマットID. 'BM'	*/
    unsigned long	SizeF;		/*!< DIBファイルサイズ [byte]		*/
    unsigned short	Reserved1F;	/*!< 予約				*/
    unsigned short	Reserved2F;	/*!< 予約				*/
    unsigned long	OffBitsF;	/*!< 予約				*/
} XdwDIB_BitmapFileHeader;


#endif /* XDWDEIBDECODER_H_INCLUDED */
