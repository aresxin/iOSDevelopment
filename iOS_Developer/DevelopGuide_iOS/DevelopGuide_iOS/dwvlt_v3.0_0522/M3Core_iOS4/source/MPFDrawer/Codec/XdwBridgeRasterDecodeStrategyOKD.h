/*!
  @file  XdwBridgeRasterDecodeStrategyOKD.h
  @brief XdwBridgeRasterDecodeStrategyOKD関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyOKD classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-10-04
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-10-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYOKD_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYOKD_H_INCLUDED

#include "XdwDataObjectFilterOKD.h"
#include "XdwBridgeRasterDecodeStrategy.h"

#ifdef DEBUG
//#include <stdio.h>
#endif
/*! XdwDataObject::Binaryの読み込む専用ラッパー
 *
 * XdwDataObject::Binaryをラップして，
 * read()同様のメソッドを提供する．
 */
class XdwBridgeDecoReader {
private:
    XdwDataObject::Binary	*img_dataF;	/*!< 読込先Object			*/
    long			img_sizeF;	/*!< Encoded DataのSize			*/
    long			img_offsetF;	/*!< Encoded DataまでのOffset		*/

    long			current_offsetF;/*!< 読み込み中DataまでのOffset		*/
    long			read_data_numF;	/*!< Data Objectから読み込んだデータ数	*/
public:
    XdwBridgeDecoReader();
    ~XdwBridgeDecoReader();

    XdwErrorCode Init( XdwDataObject::Binary *, long, long );
    size_t ReadData( void *, size_t, size_t );
    XdwErrorCode Seek(long, XdwDataObject::Binary::SeekMode );
    XdwErrorCode GetStatus( XdwDataObject::Binary **, long*, long*, long*, long* );
};

/*#define XDWDECO_DIB_DEBUG_FILEOUT*/

/*!OKD Decode Class
 *
 * OKDをラスタにデコードするクラス.
 * OKDデコード機能を提供する．
 */
class XdwBridgeDecoStOKD : public XdwBridgeDecodeStrategy {
private:
    XdwDataObject::Filter::OKD	*okdF;		/*!< OKD Decoder Object		*/
    long			okd_dev_numF;	/*!< OKDデータの分割数		*/
    long			okd_dst_sizeF;	/*!< OKDデータdestinationサイズ	*/
    long			okd_src_sizeF;	/*!< OKDデータsourceサイズ	*/
    long			okd_src_line_numF;/*!< OKDデータsource line数	*/

    XdwBridgeDecoReader		master_readerF;
    XdwBridgeDecoReader		okd_readerF;

    long	read_data_numF;	/*!< Data Objectから読み込んだデータ数 */
    long	scanline_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte]	*/
    long	padding_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte] に	*/
				/* 付加されるパディングバイト( scanline が4byte Alignされてるから)*/
    long	current_pointF;	/*!< デコードイメージ中の現在読み取り位置[byte]		*/
    long	current_scanlineF;/*!< デコードイメージ中の現在読み取り位置[scanline]	*/

#ifdef XDWDECO_DIB_DEBUG_FILEOUT
    unsigned long	debug_call_SetF;/*!< ::Setが呼ばれた回数	*/
    unsigned long	debug_countF;	/*!< デバッグ用カウンタ		*/
    FILE		*debug_fileF;	/*!< デバッグ用FILE		*/
#endif

    XdwErrorCode NextOkdFilter( void );
public:
    XdwBridgeDecoStOKD();
    ~XdwBridgeDecoStOKD();

    bool IsPaletteIndexOut(void);
    bool IsBottomUp(void);

    XdwErrorCode Set( const XdwRasterImageAttribute	&img_attr,
		      XdwDataObject::Binary		*img_data,
		      long				img_offset,
		      long				img_size );
    XdwErrorCode GetHeader( XdwRasterImageAttribute *img_header );

    XdwErrorCode ReadRaster( unsigned char *buffer );
    XdwErrorCode Finish( void );
};

#endif /* XDWBRIDGERASTERDECODESTRATEGYOKD_H_INCLUDED */
