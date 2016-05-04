/**
 * @file  XdwColor.h
 * @brief Color関連クラス用ヘッダファイル
 *
 * Colorと色変換に関する型の宣言やグローバルな関数，ライブラリへのI/Fを提供する．<br>
 * Palette ( indexed color )もここ．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-03
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-03	Toshio Yamazaki<br>
 */
#ifndef XDWCOLOR_H_INCLUDED
#define XDWCOLOR_H_INCLUDED

#include "XdwBridgeCommon.h"
#include "System/SystemIF/XdwError.h"

/*!色空間コード定義

  色空間を指定する必要がある場合の指定されるコード
 */
enum XdwColorSpaceID {
    XDW_COLORSPACEID_UNKNOWN = 0,	/*!< 不明や，圧縮イメージを展開しないと特定不可な場合	*/
    XDW_COLORSPACEID_PALETTE,	/*!< 現在設定されているパレットを参照する		*/
    XDW_COLORSPACEID_RGB,	/*!< RGB のどれ? なんて質問はしないように		*/
    XDW_COLORSPACEID_MASK,      /*!< 色値は指定されたマスクを掛けて、取得する           */
    XDW_COLORSPACEID_GRAY,	/*!< GRAY，明度と一致するだろう．			*/
    XDW_COLORSPACEID_BLACK,	/*!< 意味するところは process Black のこと		*/
    XDW_COLORSPACEID_CMYK,	/*!< Device CMYK のこと.				*/
    XDW_COLORSPACEID_CIELAB,	/*!< CIE Lab, Luv は未だ無い				*/
    XDW_COLORSPACEID_YCbCr,	/*!< JPEG 用						*/
    XDW_COLORSPACEID_ARTRGB,	/*!< Art用RGB						*/
    XDW_COLORSPACEID_PCLGRAY,	/*!< GRAY だけど,意味するところは Brightness のこと	*/
    XDW_COLORSPACEID_ITULAB,	/*!< TIFF 用						*/
    XDW_COLORSPACEID_CRGB,	/*!< PCL用 CRGB						*/
};

/*! Palette クラス

  Paletteを定義するクラス．暫定．
 */
class XdwColorPalette {
public:
    XdwColorSpaceID	ColorSpaceF;	/*!< パレットの色空間		*/
    XdwUInt32Vector	TableF;		/*!< パレットテーブル<br>色空間がXDW_COLORSPACEID_RGBの場合には、0x00RRGGBBである */
    long		EntryNumberF;	/*!< パレットテーブルの要素数	*/
    long		DepthF;		/*!< パレットの色深さ		*/

    XdwErrorCode GetInfomation( XdwColorSpaceID&, long&, long& );
    XdwErrorCode SetPaletteEntries( const long &,
				    const XdwUInt32Vector &);
    XdwErrorCode ResizePalette( const long & );

    XdwErrorCode SetColor( const long&, const unsigned long& );
    XdwErrorCode GetColor( const long&, unsigned long& );
};
#endif /* XDWCOLOR_H_INCLUDED */
