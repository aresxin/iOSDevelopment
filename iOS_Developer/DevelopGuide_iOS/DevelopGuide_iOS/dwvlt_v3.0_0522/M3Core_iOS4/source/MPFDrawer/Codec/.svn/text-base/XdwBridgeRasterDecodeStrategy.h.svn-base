/*!
  @file  XdwBridgeRasterDecodeStrategy.h
  @brief XdwBridgeRasterDecodeStrategy関連ヘッダファイル

  XdwBridgeRasterDecodeStrategy classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-07-18
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-07-18	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGY_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGY_H_INCLUDED

/*
  ここでincludeしてるのは，XdwOkdCommon.hの
  CHAR_BIT, USHORT_BIT, e.t.c. のenum定義が
  どっかのdefineとバッティングするから
*/
#include "XdwDataObjectFilterOKD.h"

#include "XdwError.h"
#include "XdwRaster.h"
#include "XdwDataObject.h"

/*! XdwDataObject::Binaryの切り替えクラス

  XdwDataObject::Binaryのフィルタを切り替えるクラス．
  とりあえず, OKDのみ対応<br>
  XdwDataObjectに格納されているデータがOKD圧縮されている時，
  利用側は展開してからラスタイメージ用のCodecに渡す必要がある．
  そこで，このクラスは，XdwDataObjectオブジェクトの切り替えや
  (Codec側から見ると，両方とも同じXdwDataObjectだから)，
  OKD展開フィルタ用のラッパーを提供する．
 */
class XdwBridgeDecoSelectDataObject {
private:
    XdwDataObject::Binary	*masterF;	/*!< 読込先Object			*/
    long			img_sizeF;	/*!< Encoded DataのSize			*/
    long			img_offsetF;	/*!< Encoded DataまでのOffset		*/
    long			current_offsetF;/*!< 読み込み中DataまでのOffset		*/
    long			read_data_numF;	/*!< Data Objectから読み込んだデータ数	*/
    long			read_line_numF;	/*!< 読み込んだスキャンライン数		*/

    XdwDataObject::Filter::OKD	*okdF;	/*!< OKD Decoder Object		*/
    long		okd_dev_numF;	/*!< OKDデータの分割数		*/
    long		okd_read_block_numF;/*!< 読み込み済みのOKDデータブロック数	*/
    long		okd_dst_sizeF;	/*!< OKDデータdestinationサイズ	*/
    long		okd_src_sizeF;	/*!< OKDデータsourceサイズ	*/
    long		okd_src_line_numF;/*!< OKDデータsource line数	*/

    XdwErrorCode NextOkdFilter( void );
    size_t ReadDataFromMaster( void *, size_t, size_t );
public:
    XdwBridgeDecoSelectDataObject();
    ~XdwBridgeDecoSelectDataObject();

    XdwErrorCode Init( const XdwRasterImageAttribute &, XdwDataObject::Binary *, long, long,
		       XdwDataObject::Binary**, long*, long* );
    bool Check(void);
    XdwErrorCode GetDataObject( XdwDataObject::Binary**, long*, long* );

    void Finish(void);
};

/*! 圧縮Image Decode用Strategy class

  圧縮されたImageをDecodeするクラスのI/F定義クラス．
  各クラスは，このクラスを継承してXdwBridgeRasterManager
  をcontextとしたStrategy Patternを構成する．<br>
  また，XdwBridgeRasterOutputAdapterから，ラスターを読み込むために
  Stream classとして使用される.

  @par 使用方法:
	-# Codecに合わせたXdwBridgeDecodeStrategyオブジェクトを生成する
	-# 出力先に合わせたXdwBridgeRasterOutputAdapterオブジェクトを生成する
	-# 各オブジェクトへの設定
	-# XdwBridgeRasterOutputAdapter::Draw()で出力先へ描画
  @code
	＊コード例＊

	＊出力先＊
	XdwBridgeRasterOutputAdapter	*out;
	＊イメージの属性＊
	const XdwRasterImageAttribute	img_attr;
	＊イメージが入っているXdwDataObject＊
	XdwDataObject::Binary		*img_data;
	const long			img_offset;
	const long			img_size;

	＊これらのデータであらわされるイメージを描画する＊

	XdwBridgeDecodeStrategy	*image;

	switch (img_attr.FormatF ) {
	case XDW_RASTERFORMATID_WMF_RASTER:
	case XDW_RASTERFORMATID_EMF_RASTER:
	case XDW_RASTERFORMATID_OKD_OLD:

	    switch (img_attr.CodecF ) {
	    case XDW_RASTERCODECID_DIB_RAW:
	    case XDW_RASTERCODECID_DIB_RLE_8:
	    case XDW_RASTERCODECID_DIB_RLE_4:
	    case XDW_RASTERCODECID_DIB_BIT_FILDES:

		if ( out->IsIndexedRasterSupport() ) {
			image = XdwNew(XdwBridgeDecoStDIBIndexed);
		};
	＊こんな感じでXdwBridgeDecodeStrategyオブジェクトを生成＊

	＊XdwBridgeDecodeStrategyオブジェクトの設定をして……＊
	ret_code = image->Set(tmp_img_attr, img_data, img_offset, img_size );
	ret_code = image->GetHeader(&tmp_img_attr);

	＊XdwBridgeRasterOutputAdapterへDrawするとImageを描いてくれる＊
	ret_code = out->Draw(tmp_img_attr, image, tmp_mask_attr, mask);
  @endcode

  @par XdwDataObjectからの読み込み方法:
	XdwDataObjectからの読み込みは，以下のコード例で示すような，
	定番の処理で行われている．XdwBridgeDecodeStrategyオブジェクトは，
	ほぼ全てこの例と同様の処理で読み込みを行っている．
  @code
    ＊コード例＊
    ＊XdwDataObjectから要求データサイズを読み出すための定番処理＊
    unsigned char	*src;	＊XdwDataObject内のデータの位置＊
    unsigned char	*dst;	＊読み込んだデータの書き込み位置＊

    ＊読み込みデータの存在する位置current_offsetFまでXdwDataObjectをSeek()＊
    ret_code = masterF->Seek(current_offsetF, XdwDataObject::Binary::START );
    if (  ret_code != XDW_ERRORCODE_SUCCESS ) return 0;

    ＊ これから読み込むデータサイズ=desired_sizeが0でない限りループ	＊
    while( desired_size > 0 ) {
	＊ desired_size分のデータを要求し，				＊
	＊ コピー可能なサイズfeasible_sizeとデータへのポインタを取得	＊
	src = masterF->GetCurrentPointer( desired_size, feasible_size );
	if ( feasible_size < 0 ) return 0;
	＊ データを取得							＊
	if ( memcpy( dst, src, feasible_size ) != dst ) {
	    return 0;
	};

	＊ 読み込んだサイズ分だけ，カレントからXdwDataObjectをSeek()	＊
	ret_code = masterF->Seek(feasible_size, XdwDataObject::Binary::CURRENT );
	if (  ret_code != XDW_ERRORCODE_SUCCESS ) return 0;

	＊ 読み込んだサイズを引いておいて，				＊
        desired_size -= feasible_size;
	＊ 書き込んだポインタを読み込んだサイズ分だけインクリメント	＊
	dst += feasible_size;
    };
  @endcode
 */
class XdwBridgeDecodeStrategy {
protected:
    XdwDataObject::Binary	*img_dataF;		/*!< 読込先Object		*/
    long			img_offsetF;		/*!< Encoded DataまでのOffset	*/
    long			img_sizeF;		/*!< Encoded DataのSize		*/
    long			current_offsetF;	/*!< 読み込み中DataまでのOffset	*/
    long			skip_heightF;		/*!< Imageを縦方向に読み飛ばすライン数	*/
public:
    /*! コンストラクタ
     * コンストラクタ
     */
    XdwBridgeDecodeStrategy();
    /*! デストラクタ
     * デストラクタ
     */
    virtual ~XdwBridgeDecodeStrategy();

    /*! XdwDataObject::Binaryの設定
     *
     * EncodeされているImageの読込先である,
     * XdwDataObject::Binaryの設定．<br>
     * 以降，このXdwDataObjectからEncoded Dataを読み込むことが可能となる．
     *
     * @param img_attr		Image属性
     * @param img_data		読込先Object
     * @param img_offset	Encoded Dataまでのオフセット
     * @param img_size		Encoded Dataのサイズ
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Set( const XdwRasterImageAttribute	&img_attr,
			      XdwDataObject::Binary		*img_data,
			      long				img_offset,
			      long				img_size ) = 0;

    /*! Encoded Imageのヘッダ情報取得
     *
     * Encode Formatの中には，Decodeして初めてRaster Imageの属性が
     * 判明するForamtが存在する．そのための，Encoded ImageをDecodeして，
     * Raster Imageの属性を取得するI/Fである．<br>
     * Decodeせずに属性が判明するFormatの場合，引数のimg_header
     * には何も書き込まれない.
     *
     * @param img_header	Imagerのヘッダ情報．Encoded Data中に存在
     *				しない場合は，何も取得しない．
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode GetHeader( XdwRasterImageAttribute *img_header ) = 0;

    /*! Raster Imageの取得
     *
     * 設定されたXdwDataObject::Binaryから，Encoded Imageを読み込み，
     * 1 line ( num pixle x 1 scan line) 分Decodeしてbufferに書き込む．
     * 書き込まれるPixelの Depth, Component等は,
     * XdwBrigeDecodeStrategy::Set()で設定された値になる．<br>
     *
     * @param buffer	Decodeされたピクセルの書き込み先
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode ReadRaster( unsigned char *buffer ) = 0;

    /*! Decodeの終了
     *
     * Decodeを行うライブラリ・モジュールの中には，
     * Decode終了処理を行う必要があるものもある．
     * ので，Encoded ImageのDecodeが終了した後，
     * 呼ぶ必要がある．
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Finish( void ) = 0;

    /***************************************************/
    /*! @name サーポート問い合わせI/F
     * XdwBridgeDecodeStrategyの出力がサポートする，
     * index形式・ラスター形式等を問い合わせる関数<br>
     * @note
     *	基本的に，XdwBridgeDecodeStrategy::Set()を実行した後のみ，
     *  返値は保証される．(フォーマットによっては，実行するまえでも保証される)
     */
    /***************************************************/
    /*@{*/
    /*! Palette Index Out出力？

      Decode後のラスタがIndex形式かラスタか答える

      @retval true Index
      @retval false Raster
     */
    virtual bool IsPaletteIndexOut(void) = 0;
    /*! BottomUp Image出力

      DIB等の，下のスキャンラインから
      格納されているラスタ形式か否か答える

      @retval true BottomUp
      @retval false TopDown
     */
    virtual bool IsBottomUp(void) = 0;
    /*@}*/
};

#endif /* XDWBRIDGERASTERDECODESTRATEGY_H_INCLUDED */
