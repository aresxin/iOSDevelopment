/*!
  @file  XdwBridgeRasterDecodeStrategyJPEG.h
  @brief XdwBridgeRasterDecodeStrategyJPEG関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyJPEG classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-08-26
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-08-26	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYJPEG_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYJPEG_H_INCLUDED

#include <stdio.h>
#include <setjmp.h>
#include <ctype.h>
extern "C" {
#include "jpeglib.h"
};

#include "XdwBridgeRasterDecodeStrategy.h"

/*#define XDWDECO_JPEG_DEBUG_FILEOUT*/

/*!JPEG Decode Class
 * JPEGをラスタにデコードするクラス.
 * 各ライブラリを隠蔽してJPEGデコード機能を提供する．
 */
class XdwBridgeDecoStJPEG : public XdwBridgeDecodeStrategy {
private:
    /* jlib用に使われるprivateメンバ変数とメソッド	*/
    long read_data_numF;	/*!< Data Objectから読み込んだデータ数 */
    void InitErrorMgr(void);
    void InitSourceMgr(void);
protected:
    unsigned long	scanline_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte]	*/
    unsigned long	read_scanlineF;	/*!< 読み込んだスキャンライン数 */

#ifdef XDWDECO_JPEG_DEBUG_FILEOUT
    unsigned long		debug_countF;
    unsigned long		debug_call_SetF;
    FILE			*debug_fileF;
#endif
public:
    /* jlib 用の構造体			*/
    /* Error Manager用			*/
    struct jpeg_error_mgr		jerr_mgrF;	/*!< エラーマネージャ		*/
    jmp_buf				setjmp_bufferF;	/*!<  for return to caller	*/
    int					jpeg_init_error_code;/*!< エラーコード取得用	*/
    /* Source Manager用			*/
    struct jpeg_source_mgr		jsrc_mgrF;	/*!< ソースマネージャ		*/
    JOCTET				*jsrc_bufferF;	/*!< ソース用バッファ		*/
    bool				jsrc_start_of_fileF;	/*!< have we gotten any data yet? */
    /* Jpeg Decoder用			*/
    struct jpeg_decompress_struct	jcinfoF;	/*!< Jpeg Decomposer情報	*/

    /* jlib用に使われるpublicメンバ変数とメソッド	*/
    /* jlib用オーバーライト関数からアクセスされるから	*/
    /* publicになってる					*/
    size_t ReadData( void *, size_t, size_t );

    XdwBridgeDecoStJPEG();
    ~XdwBridgeDecoStJPEG();

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

#endif /* XDWBRIDGERASTERDECODESTRATEGYDIB_H_INCLUDED */
