/**
 * @file  XdwRaster.h
 * @brief Raster処理関連クラス用ヘッダファイル
 *
 * Raster処理に関する型の宣言やグローバルな関数，ライブラリへのI/Fを提供する．
 * Pattern, Raster関連の圧縮処理ライブラリへのI/Fもここ．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-03
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-03	Toshio Yamazaki<br>
 */
#ifndef XDWRASTER_H_INCLUDED
#define XDWRASTER_H_INCLUDED

#include "XdwPoint.h"
#include "XdwMatrix.h"
#include "XdwColor.h"
#include "XdwGraphicsAttribute.h"
#include "XdwBridgeCommon.h"

/*! サポートするラスターフォーマットのコード定義

  Bridgeへ渡すRasterImageがどのグラフィックデータの
  ラスターデータかを指定するために用いる．
*/
enum XdwRasterFormatID {
    XDW_RASTERFORMATID_INVALID = -1,    /*!< 不明のフォーマット */
    XDW_RASTERFORMATID_WMF_RASTER = 1,	/*!< WMF中のラスターデータ(XDW独自の拡張形式も含む)*/
    XDW_RASTERFORMATID_OKD_OLD = 2,	/*!< 古いバージョンのOKD圧縮されたDIB   */
    XDW_RASTERFORMATID_MH_OLD = 3,	/*!< 古いバージョンのMH			*/
    XDW_RASTERFORMATID_EMF_RASTER = 4,	/*!< EMF中のラスターデータ(XDW独自の拡張形式も含む)*/
    XDW_RASTERFORMATID_JPEG = 5,	/*!< JPEG				*/
    XDW_RASTERFORMATID_OKD = 7,	/*!< OKD圧縮されたDIB	                */
    XDW_RASTERFORMATID_MH = 8,	/*!< MH					*/
    XDW_RASTERFORMATID_MMR = 9,	/*!< MMR				*/
    XDW_RASTERFORMATID_ALLA = 10, /*!< ALLA				*/
    XDW_RASTERFORMATID_MRC = 11, /*!< MRC				*/
    XDW_RASTERFORMATID_ALLAV2 = 12, /*!< ALLAv2				*/

};

/*! WMF/EMF中のラスターデータのEncode方法の定義 */
enum XdwRasterCodecID{
    /*! 不明のEncode方法 */
    XDW_RASTERCIDECID_INVALID = -1,
    /*! 生のDIB */
    XDW_RASTERCODECID_DIB_RAW = 0,
    /*! 8Bit Run LengthのDIB */
    XDW_RASTERCODECID_DIB_RLE_8,
    /*! 4Bit Run LengthのDIB */
    XDW_RASTERCODECID_DIB_RLE_4,
    /*! BitFildesのDIB */
    XDW_RASTERCODECID_DIB_BIT_FILDES,
    /*! Jpeg圧縮されたDIB */
    XDW_RASTERCODECID_DIB_JPEG,
    /*! PNG圧縮されたDIB */
    XDW_RASTERCODECID_DIB_PNG,

    /* 以下 XDW独自 */
    /*! Jpegフォーマット */
    XDW_RASTERCODECID_XDW_JPEG
};

/*! 極性 */
enum XdwRasterPolarity {
	/*! 1が黒 */
	XDW_RASTERPOLARITY_ONE_IS_BLACK = 0,
	/*! 1が白 */
	XDW_RASTERPOLARITY_ONE_IS_WHITE = 1,
	/*! 1が黒 */
	XDW_RASTERPOLARITY_NOT_SPECIFIED = -1
};

/*! 画像の属性

  Bridgeへ渡すRasterImageの属性を指定する．<br>
  Codec方式によっては，展開しないと各要素が特定できない場合，
  0を入れる．つまり，各要素値が，圧縮イメージを展開して判明した値と，
  異なる場合，展開して判明した値が優先される．<br>
*/
class XdwRasterImageAttribute {
public:
    /*! イメージをデバイス座標にマッピングするモード
      イメージの入力側座標系はユーザー座標系であり，
      出力側座標系はデバイス座標系となる．その間の
      座標変換パラメータをどのような形式で与えるかを指定する．
     */
    enum RasterMappingMode {
	XDW_RASTERMAPPINGMODE_AREA,	/*!< 出力先矩形領域で指定	*/
	XDW_RASTERMAPPINGMODE_MATRIX	/*!< 変換マトリクスで指定	*/
    };
    XdwRasterFormatID   FormatF;        /*!< ラスターのフォーマット     */
    XdwRasterCodecID	CodecF;		/*!< Codec方式			*/
    int			ComponentF;	/*!< コンポーネント数 1<=c<=4	*/
    XdwColorSpaceID	ColorSpaceF;	/*!< 色空間			*/
    int			DepthF;		/*!< 色深さ 1<=d<=8		*/
    long		WidthF;		/*!< 幅 0の時は不明		*/
    long		HeightF;	/*!< 高さ 0の時は不明		*/
    bool		InterriveF;	/*!< 点順次or面(線)順次		*/
    XdwRasterPolarity	PoleF;	/*!< 極性			*/
    XdwColorPalette	PaletteF;	/*!< パレットデータ		*/
    unsigned long	TotalDataSizeF;	/*!< イメージデータの総バイト数	*/
    XdwPoint		SrcStartPointF;	/*!< 入力開始位置		*/
    long		SrcWidthF;	/*!< 入力画像幅			*/
    long		SrcHeightF;	/*!< 入力画像高さ		*/
    XdwPoint		DstStartPointF;	/*!< 描画開始位置		*/
    XdwRasterImageAttribute::RasterMappingMode	MappingModeF;	/*!< Mapping Mode */
    long		DstWidthF;	/*!< 描画領域幅			*/
    long		DstHeightF;	/*!< 描画領域高さ		*/
    XdwMatrix		MappingMatrixF;	/*!< マッピングマトリクス	*/
    XdwGSRopMode	RopModeF;	/*!< ROPモード，3〜4のみ	*/
    XdwTypeUInt32	RopCodeF;	/*!< ROPコード．(MSDNの定義と同じ)	*/
	bool	UseFGBGColorF;	/*!< BitmapInfoHeaderにパレットがあるかどうか */
	int			JpegScaleDenomF;	/*!< JPEGの間引き伸長 =1,2,4,8 */	
};

/*! パターンの属性

  Bridgeへ渡すPatterneの属性を指定する．<br>
*/
class XdwPatternAttribute {
public:
    /*!パターン形状
      パターンがどのように生成されたかor生成するか指定する．
    */
    enum PatternStyle {
	XDW_PATTERNSTYLE_SOLID = 0,		/*!< 単色パターン	*/
	XDW_PATTERNSTYLE_NULL = 1,		/*!< NULLパターン	*/
	XDW_PATTERNSTYLE_BITMAP = 6,	/*!< Bitmapパターン	*/
	XDW_PATTERNSTYLE_HATCH = 2		/*!< ハッチパターン	*/
    };
    /*!ハッチパターン形状
      XdwPatternAttribute::PatternStyle::XDW_PATTERNSTYLE_HATCH
      が指定されたときのパターン形状を指定する．
    */
    enum HatchPatternStyle {
	XDW_HATCHPATTERNSTYLE_HORIZONTAL = 0,	/*!< ----- */
	XDW_HATCHPATTERNSTYLE_VERTICAL,		/*!< ||||| */
	XDW_HATCHPATTERNSTYLE_FDIAGONAL,	/*!< \\\\\ */
	XDW_HATCHPATTERNSTYLE_BDIAGONAL,	/*!< ///// */
	XDW_HATCHPATTERNSTYLE_CROSS,		/*!< +++++ */
	XDW_HATCHPATTERNSTYLE_DIAGCROSS		/*!< xxxxx */
    };

    XdwPatternAttribute::PatternStyle		StyleF;	/*!< パターンスタイル	*/
    XdwPatternAttribute::HatchPatternStyle	HatchF;	/*!< ハッチスタイル	*/
    XdwTypeUInt32 ColorF; /*!< パターンの色<br>色空間がXDW_COLORSPACEID_RGBの場合には、0x00RRGGBBである */
    XdwColorSpaceID ColorSpaceF; /*!< パターンの色空間 */
    
};

#endif /* XDWRASTER_H_INCLUDED */
