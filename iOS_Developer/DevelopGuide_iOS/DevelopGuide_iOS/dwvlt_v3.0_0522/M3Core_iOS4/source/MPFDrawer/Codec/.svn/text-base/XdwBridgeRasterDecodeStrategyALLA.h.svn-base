/*!
  @file  XdwBridgeRasterDecodeStrategyALLA.h
  @brief XdwBridgeRasterDecodeStrategyALLA関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyALLA classの宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-10-04
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-10-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYALLA_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYALLA_H_INCLUDED

#include "XdwBridgeRasterDecodeStrategy.h"

#ifdef DEBUG
#include <stdio.h>
#endif

class QomoDec;

/*#define XDWDECO_ALLA_DEBUG_FILEOUT*/
/*#define XDWDECO_ALLA_DEBUG_READLINECOUNT*/

/*!ALLA Decode Class
 *
 * ALLAをラスタにデコードするクラス.
 * ALLAデコード機能を提供する．
 */
class XdwBridgeDecoStALLA : public XdwBridgeDecodeStrategy {
private:
    QomoDec	*allaF;		/*!< ALLA Decoder Object	*/
    /* AR1100 */
    bool			isindexedoutF;
    /* AR1100 */

    long	read_data_numF;	/*!< Data Objectから読み込んだデータ数 */
    long	scanline_sizeF;	/*!< デコードされたImageのスキャンラインサイズ[byte]	*/
    long	current_pointF;	/*!< デコードイメージ中の現在読み取り位置[byte]		*/
    long	current_scanlineF;/*!< デコードイメージ中の現在読み取り位置[scanline]	*/

#ifdef XDWDECO_ALLA_DEBUG_FILEOUT
    unsigned long	debug_call_SetF;/*!< ::Setが呼ばれた回数	*/
    FILE		*debug_fileF;	/*!< デバッグ用FILE		*/
#endif
#ifdef XDWDECO_ALLA_DEBUG_READLINECOUNT
    unsigned long	debug_countF;	/*!< デバッグ用カウンタ		*/
#endif

public:
    XdwBridgeDecoStALLA();
    ~XdwBridgeDecoStALLA();

    size_t ReadData( void *, size_t, size_t );

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

#endif /* XDWBRIDGERASTERDECODESTRATEGYALLA_H_INCLUDED */
