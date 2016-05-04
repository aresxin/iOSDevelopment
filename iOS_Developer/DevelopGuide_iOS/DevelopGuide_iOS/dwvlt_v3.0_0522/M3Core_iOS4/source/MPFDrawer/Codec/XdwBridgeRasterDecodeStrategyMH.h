/*!
  @file  XdwBridgeRasterDecodeStrategyMH.h
  @brief XdwBridgeRasterDecodeStrategyMH関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyMH classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-10-03
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-10-03	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYMH_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYMH_H_INCLUDED

#include "XdwBridgeRasterDecodeStrategy.h"

#ifdef DEBUG
#include <stdio.h>
#endif

/*!MMR Decode Class
 *
 * MMRをラスタにデコードするクラス.
 * MMRデコード機能を提供する．
 */
class XdwBridgeDecoStMH : public XdwBridgeDecodeStrategy {
private:

    long DecodeLine(unsigned char *pBits);
    long Decode(unsigned char *packedmemory, long packedlen, long width, long height);
    long SetDecode(unsigned char *packedmemory, long packedlen, long width, long height);
    inline void FillBuffer(unsigned char n);
    inline int GetBits(unsigned char n, int fill = 1);

//  unsigned char	*m_dec_packedmemory;	/*!< 圧縮イメージ全部		*/
    long		m_dec_packedsizeF;	/*!< 圧縮イメージ全部のサイズ	*/

    unsigned char	*m_dec_cur_ptrF;
    unsigned char	m_dec_subbitbufF;
    unsigned char	m_dec_bitcountF;
    unsigned long	m_dec_bitbufF;

    unsigned char	*src_imgF;	/*!< 圧縮イメージ全部		*/
    unsigned char	*dst_imgF;	/*!< 展開後イメージ全部		*/
    long		scanline_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte]	*/
    long		current_pointF;	/*!< デコードイメージ中の現在読み取り位置[byte]		*/
#if DEBUG
    unsigned long		debug_call_SetF;
    unsigned long		debug_countF;
    FILE			*debug_fileF;
#endif

public:
    XdwBridgeDecoStMH();
    ~XdwBridgeDecoStMH();

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

#endif /* XDWBRIDGERASTERDECODESTRATEGYMH_H_INCLUDED */
