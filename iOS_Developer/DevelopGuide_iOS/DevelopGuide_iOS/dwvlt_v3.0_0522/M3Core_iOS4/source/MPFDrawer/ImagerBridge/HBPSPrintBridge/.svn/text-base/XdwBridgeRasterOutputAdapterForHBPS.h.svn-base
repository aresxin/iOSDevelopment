/*!
  @file  XdwBridgeRasterOutputAdapter.h
  @brief XdwBridgeRasterOutputAdapter関連ヘッダファイル

  XdwBridgeRasterOutputAdapter classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-07-18
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-07-18	Toshio Yamazaki<br>
  分割描画対応:	2002-10-07	Kenichi.Ishida<br>
 */
#ifndef XDWBRIDGERASTEROUTPUTADAPTER_H_INCLUDED
#define XDWBRIDGERASTEROUTPUTADAPTER_H_INCLUDED

#include "XdwError.h"
#include "XdwRaster.h"
#include "XdwBridgeHBPSInternal.h"

class XdwBridgeDecodeStrategy;

/*!Image出力用 Adapter class
 *
 * Raseter Imageを出力するクラスのI/F定義クラス．
 * 各クラスは，このクラスを継承して，XdwBridgeRasterManager
 * をclientとしたAdapter Patternを構成する.
 */
class XdwBridgeRasterOutputAdapter {
public:
    /*!コンストラクタ
     * コンストラクタ
     */
    XdwBridgeRasterOutputAdapter() {};
    /*!デストラクタ
     * デストラクタ
     */
    virtual ~XdwBridgeRasterOutputAdapter() {};

    /*! MaskとRaster Imageの描画
     *
     * XdwBridgeDecodeStrategy ObjectからDecodeされた
     * Raster Image or Maskを読み込み，出力先へ描画する.<br>
     * 引数にNULLが指定されていた場合，そのデータ無いものとして動作する.
     *
     * @param img_attr		Image属性
     * @param image		Image読込先
     * @param mask_attr		Mask属性
     * @param mask		Mask読込先
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Draw(const XdwRasterImageAttribute	&img_attr,
			      XdwBridgeDecodeStrategy	*image,
			      const XdwRasterImageAttribute	&mask_attr,
			      XdwBridgeDecodeStrategy	*mask ) = 0;
    /*! RasterImagePatternの描画
     *
     * XdwBridgeDecodeStrategy ObjectからDecodeされた
     * RasterPatternImageを読み込み，出力先へ描画する.<br>
     * 引数にNULLが指定されていた場合，そのデータ無いものとして動作する.
     *
     * @param img_attr		Image属性
     * @param image		Image読込先
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode DrawPattern(const XdwRasterImageAttribute	&img_attr,
			      XdwBridgeDecodeStrategy	*image) = 0;
    /*! MaskとRaster Imageの分割描画
     *
     * XdwBridgeDecodeStrategy ObjectからDecodeされた
     * Raster Image or Maskを読み込み，出力先へ描画する設定の初期化.<br>
     * 引数にNULLが指定されていた場合，そのデータは無いものとして動作する.
     *
     * @param img_attr		Image属性
     * @param image		Image読込先
     * @param mask_attr		Mask属性
     * @param mask		Mask読込先
     * @param nlines		DrawDividedImage一回あたりの描画ライン数
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode StartDrawDivided(
					const XdwRasterImageAttribute &img_attr,
				    XdwBridgeDecodeStrategy *image,
				    const XdwRasterImageAttribute &mask_attr,
				    XdwBridgeDecodeStrategy *mask,
					long nlines) = 0;
    /*! MaskとRaster Imageの分割描画
     *
     * StartDrawDividedImageでセットされたイメージとパラメータに従って分割出力する
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_CONTINUE	引き続き処理が可能
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    virtual XdwErrorCode DrawDivided( void ) = 0;
    /*! MaskとRaster Imageの分割描画終了
     *
     * StartDrawDividedImage->DrawDividedImageの順で処理される一連のイメージ描画処理を終了する。
     * 処理を中断する場合でも必ず呼ばれなければならない。
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    virtual XdwErrorCode EndDrawDivided( void ) = 0;
    /***************************************************/
    /*! @name サーポート問い合わせI/F
     * XdwBridgeRasterOutputAdapterの出力先がサポートする，
     * 圧縮形式・ラスター形式等を問い合わせる関数
     */
    /***************************************************/
    /*@{*/
    /*!Indexed Rasterサポート問い合わせ
     * XdwBridgeRasterOutputAdapterが
     * Indexed Rsterをサポートするか否か答える．
     * @retval true サポート
     * @retval false 非サポート
     */
    virtual bool IsIndexedRasterSupport(void) = 0;
	virtual void setDrawMethod(int) = 0;
    /*@}*/
};

class XdwBridgeGraphicStateManager;

class XdwBridgeRasterOutputAdapterForHBPS : public XdwBridgeRasterOutputAdapter {
private:
    void *imagerF;				/* Imagerのハンドル */
    XdwBridgeGraphicStateManager *gstateF;
	unsigned char *fBufferF;
    XdwBridgeDecodeStrategy *imageF;
	long  nlinesF;				/* 一回に描画するライン数 */
	unsigned char *paletteF;	/* palette tableデータ */

	double srcWidthF, srcHeightF;	/* ソースの幅高さ */
	double dstWidthF, dstHeightF;	/* 出力画像の幅高さ */
	double currentLineF;			/* 現在描画中のライン */
    long lineSizeF;				/* イメージ１ライン分のサイズ */

	double sxF;					/* 描画開始x座標 */
	double syF;					/* 描画開始y座標 */
	double sySkipF;				/* y座標のスキップ数 */
	XdwMatrix mappingMatrixF;	/* イメージ変換行列 */
	unsigned short widthF;		/* マスク＆イメージデータの幅 */
	unsigned short heightF;		/* マスク＆イメージデータの高さ */
	int existmaskF;				/* マスクの有無BOOLpolarityマスクの極性（マスクなしの場合は未使用） */
	int polarityF;				/* マスクの極性（マスクなしの場合は未使用） */
	unsigned long maskSizeF;	/* マスクデータのバイト数（マスクなしの場合は未使用） */
	int existimageF;			/* イメージの有無 */
	unsigned short colorSpaceF;	/* 色空間(イメージなしの場合は未使用) */
	unsigned short colorDepthF;	/* paletteDataのdepth(Indexed Colorでない場合は未使用） */
	unsigned short paletteEntriesF;		/* palettetableのエントリー数(Indexed Colorでない場合は未使用） */
	unsigned short paletteByteSizesF;		/* palettetableのバイト数(Indexed Colorでない場合は未使用） */
	char *paletteData;					/* palettetableデータ */
	unsigned short orderF;		/* イメージデータの色順次 */
	unsigned short imageDataDepthF;		/* イメージデータの深さ */
	unsigned short compressionMethodF;	/* 圧縮方式 */
	char *maskDataF;	/* 高さx幅の1bitマスクデータ（マスクなしの場合は未使用） */
	char *imageDataF;	/* imageSzeバイトのイメージデータ（イメージデータなしの場合は未使用） */
	int	drawMethodF;	/* 描画モード */

	/*!HBPS用Paletteテーブルの生成
	 * XdwRasterImageAttribute内のPaletteテーブルをHBPS用の
	 * Paletteテーブルに変換する．newによりテーブルを生成するので，
	 * 呼び出し側でdeleteしなければならない.<br>
	 * 面倒なので，とりあえず3planeパレット固定
	 * @param img_attr Image属性
	 * @retval NULL メモリ不足
	 * @retval 確保してPaletteデータが入っているHBPS用パレットデータ
	 */
    unsigned char* GeneratePalette( const XdwRasterImageAttribute & );
	/*!BWPaletteテーブルの生成
	 * Paletteテーブルを無視して,Black/White用Globe Paletteテーブルを生成する.
	 * newによりテーブルを生成するので，呼び出し側でdeleteしなければならない.<br>
	 * 面倒なので，とりあえず3planeパレット固定
	 * @param img_attr Image属性
	 * @retval NULL メモリ不足
	 * @retval 確保してPaletteデータが入っているパレットデータ
	 */
	unsigned char* GeneratePaletteBW( const XdwRasterImageAttribute & );
	/*! Raster Imageの描画
	 *
	 * XdwBridgeDecodeStrategy ObjectからDecodeされた
	 * Raster Imageを読み込み，出力先へ描画する.<br>
	 * 引数にNULLを指定してはならない．
	 *
	 * nlines = 0 の時は全てのラインを一度に描画する
	 *
	 * @param img_attr	Image属性
	 * @param image		Image読込先
	 * @param nlines	一度に描画するライン数
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 * @retval XdwErrorCode
	 */
    XdwErrorCode DrawImage(const XdwRasterImageAttribute &, XdwBridgeDecodeStrategy *, long);
	/*! Raster Imageパターンの描画
	 *
	 * XdwBridgeDecodeStrategy ObjectからDecodeされた
	 * Raster Imageを読み込み，出力先へ描画する.<br>
	 * 引数にNULLを指定してはならない．
	 *
	 * @param img_attr	Image属性
	 * @param image		Image読込先
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 * @retval XdwErrorCode
	 */
    XdwErrorCode DrawImagePattern(const XdwRasterImageAttribute &, XdwBridgeDecodeStrategy *, long);
	/*! MaskとRaster Imageの描画
	 *
	 * XdwBridgeDecodeStrategy ObjectからDecodeされた
	 * Raster Image and Maskを読み込み，出力先へ描画する.<br>
	 * 引数にNULLを指定してはならない．
	 *
	 * @param img_attr	Image属性
	 * @param image		Image読込先
	 * @param mask_attr	Mask属性
	 * @param mask		Mask読込先
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 */
    XdwErrorCode DrawImageAndMask(	const XdwRasterImageAttribute &, 
									XdwBridgeDecodeStrategy	*,
									const XdwRasterImageAttribute	&,
									XdwBridgeDecodeStrategy	* );
	/*! Maskの描画
	 *
	 * XdwBridgeDecodeStrategy ObjectからDecodeされた
	 * Raster Maskを読み込み，出力先へ描画する.<br>
	 * 引数にNULLを指定してはならない．
	 *
	 * @param mask_attr	Mask属性
	 * @param mask		Mask読込先
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 */
    XdwErrorCode DrawMask(const XdwRasterImageAttribute &, XdwBridgeDecodeStrategy * );
	/*! イメージ描画用マトリクスの作成
	 *
	 * 入出力サイズからマトリクスを作成する.<br>
	 *
	 * @param dstWidth	出力イメージ幅（デバイス座標）
	 * @param dstHeight	出力イメージ高さ（デバイス座標）
	 * @param srcWidth	入力イメージ幅（ユーザー座標）
	 * @param srcHeight	入力イメージ高さ（ユーザー座標）
	 * @param DstStartPointF 描画開始位置（デバイス座標）
	 * @param matrix 作成されたマトリクス
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
	XdwErrorCode GenerateMatrixForDrawImage(double, double, double, double, XdwMatrix *);
	/*! イメージ描画用マトリクスの作成
	 *
	 * 入出力サイズからマトリクスを作成する.<br>
	 *
	 * @param 色の深さ：depth, コンポーネント数：component, 幅：width
	 * @param lineSize	１ラインのサイズ
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
	XdwErrorCode GetLineSize( int, int, long, long *);

public:
    XdwBridgeRasterOutputAdapterForHBPS() {};
    XdwBridgeRasterOutputAdapterForHBPS( void *, XdwBridgeGraphicStateManager *);
    ~XdwBridgeRasterOutputAdapterForHBPS() {};

    bool IsIndexedRasterSupport(void);
	/*! Raster Imageまたはmaskの描画開始
	 *
	 * イメージとマスク描画をここで選択する.<br>
	 *
	 * @param img_attr　Image属性
	 * @param image		Image
	 * @param mask_attr Mask属性
	 * @param mask		Mask
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
    XdwErrorCode Draw(	const XdwRasterImageAttribute &img_attr,
						XdwBridgeDecodeStrategy *image,
						const XdwRasterImageAttribute &mask_attr,
						XdwBridgeDecodeStrategy *mask );

	/*! Raster Imageまたはmaskパターンの描画開始
	 *
	 * イメージとマスク描画をここで選択する.<br>
	 *
	 * @param img_attr　Image属性
	 * @param image		Image
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
    XdwErrorCode DrawPattern(	const XdwRasterImageAttribute &img_attr,
						XdwBridgeDecodeStrategy *image);

	/*! Raster Imageまたはmaskの分割描画開始
	 *
	 * 分割描画指定の場合にイメージとマスク描画をここで選択する.<br>
	 *
	 * @param img_attr　Image属性
	 * @param image		Image
	 * @param mask_attr Mask属性
	 * @param mask		Mask
	 * @param nlines	一回に描画するライン数
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
    XdwErrorCode StartDrawDivided(
					const XdwRasterImageAttribute &img_attr,
				    XdwBridgeDecodeStrategy *image,
				    const XdwRasterImageAttribute &mask_attr,
				    XdwBridgeDecodeStrategy *mask,
					long nlines);
	/*! Raster Imageの分割描画
	 *
	 * DrawImageが分割描画指定の場合にここでHostBasedに描画命令を送る.<br>
	 *
	 * @param なし
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_CONTINUE 未処理のイメージあり
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
	XdwErrorCode DrawDivided( void );
	/*! Raster Imageの分割描画終了処理
	 *
	 * メモリ解放などの終了処理を行う.<br>
	 *
	 * @param なし
	 *
	 * @retval XDW_ERRORCODE_SUCCESS 正常終了
	 * @retval XDW_ERRORCODE_ERROR   エラー終了
	 */
	XdwErrorCode EndDrawDivided( void );

	void setDrawMethod(int);
};
#endif /* XDWBRIDGERASTEROUTPUTADAPTER_H_INCLUDED */
