/*!
  @file  XdwBridgeRasterDecodeStrategyMMR.h
  @brief XdwBridgeRasterDecodeStrategyMMR関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyMMR classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-09-30
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-09-30	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYMMR_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYMMR_H_INCLUDED

#include "XdwBridgeRasterDecodeStrategy.h"

#ifdef DEBUG
#include <stdio.h>
#endif

/*
 * Copyright (c) 1990-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

 /*
 * TIFF Library.
 *
 * CCITT Group 3 (T.4) and Group 4 (T.6) Compression Support.
 *
 * This file contains support for decoding and encoding TIFF
 * compression algorithms 2, 3, 4, and 32771.
 *
 * Decoder support is derived, with permission, from the code
 * in Frank Cringle's viewfax program;
 *      Copyright (C) 1990, 1995  Frank D. Cringle.
 */

/* ここからlibtiffからのコードらしい		*/
/* 各変数の名前は libTIFF を元にしている	*/
struct XdwCodecTIFF_MMRState {
    unsigned long	rowbytes;	/* bytes in a decoded scanline		*/
    unsigned long	rowpixels;	/* pixels in a scanline			*/
    unsigned long	td_imagelength;	/* total scanlines			*/
    unsigned long	tif_row;	/* current scanline			*/
    unsigned char	*tif_data;	/* compression scheme private data	*/
    unsigned char	*tif_rawdata;	/* raw data buffer			*/
    long		tif_rawdatasize;/* # of bytes in raw data buffer	*/
    unsigned char	*tif_rawcp;	/* current spot in raw buffer		*/
    long		tif_rawcc;	/* bytes unread from raw buffer		*/
};

/* 以下，オリジナルコード			*/

/*!MMR Decode Class
 *
 * MMRをラスタにデコードするクラス.
 * MMRデコード機能を提供する．
 */
class XdwBridgeDecoStMMR : public XdwBridgeDecodeStrategy {
private:
    void CleanUp(XdwCodecTIFF_MMRState* mmrs, unsigned char* buf);
    int CheckAlloc(unsigned char *pointer, XdwCodecTIFF_MMRState*mmrs, unsigned char* buf);
    int Decode(unsigned char* pMMRBuf, unsigned long codeSize, unsigned long width, unsigned long height);
    int SetDecode(unsigned char* pMMRBuf, unsigned long codeSize, unsigned long width, unsigned long height);

    XdwCodecTIFF_MMRState	*mmrF;	/*!< MMR状態			*/

    unsigned char	*src_imgF;	/*!< 圧縮イメージ全部		*/
    unsigned char	*dst_imgF;	/*!< 展開後イメージ全部		*/
    long		scanline_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte]	*/
    long		current_pointF;	/*!< デコードイメージ中の現在読み取り位置[byte]		*/
    long		current_scanlineF;/*!< デコードイメージ中の現在読み取り位置[scanline]	*/
#if DEBUG
    unsigned long	debug_call_SetF;/*!< ::Setが呼ばれた回数	*/
    unsigned long	debug_countF;	/*!< デバッグ用カウンタ		*/
    FILE		*debug_fileF;	/*!< デバッグ用FILE		*/
#endif

public:
    XdwBridgeDecoStMMR();
    ~XdwBridgeDecoStMMR();

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

#endif /* XDWBRIDGERASTERDECODESTRATEGYMMR_H_INCLUDED */
