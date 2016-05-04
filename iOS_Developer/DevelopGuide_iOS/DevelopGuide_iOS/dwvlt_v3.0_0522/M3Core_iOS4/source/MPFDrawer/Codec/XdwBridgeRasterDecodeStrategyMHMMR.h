/*!
  @file  XdwBridgeRasterDecodeStrategyMHMMR.h
  @brief XdwBridgeRasterDecodeStrategyMHMMR関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyMHMMR classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-09-11
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-09-11	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYMHMMR_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYMHMMR_H_INCLUDED

#include "XdwBridgeRasterDecodeStrategy.h"

#include "imgPfImgLib.h"

#ifdef DEBUG
#include <stdio.h>
#endif

/*!MH,MMR Decode Class
 *
 * MH,MMRをラスタにデコードするクラス.
 * 各ライブラリを隠蔽して，MH,MMRデコード機能を提供する．
 */
class XdwBridgeDecoStMHMMR : public XdwBridgeDecodeStrategy {
private:
    unsigned char	*src_imgF;	/*!< 圧縮イメージ全部		*/
    unsigned char	*dst_imgF;	/*!< 展開後イメージ全部		*/
    pfimg_params_t	src_paraF;	/*!< ソースMH,MMRパラ		*/
    pfimg_params_t	dst_paraF;	/*!< ディストMH,MMRパラ		*/
    pfimg_opt_t		opt_paraF;	/*!< オプションMH,MMRパラ	*/
    long		scanline_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte]	*/
    long		current_pointF;	/*!< デコードイメージ中の現在読み取り位置[byte]		*/

#if DEBUG
    unsigned long		debug_call_SetF;
    unsigned long		debug_countF;
    FILE			*debug_fileF;
#endif

    void ReverseLongByte( unsigned char *, unsigned long );

public:
    XdwBridgeDecoStMHMMR();
    ~XdwBridgeDecoStMHMMR();

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

#endif /* XDWBRIDGERASTERDECODESTRATEGYMHMMR_H_INCLUDED */
