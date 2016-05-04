/*!
  @file  XdwBridgeRasterDecodeStrategyMMRConstants.h
  @brief XdwBridgeRasterDecodeStrategyMMRConstants関連ヘッダファイル

  XdwBridgeRasterDecodeStrategyMMR で使う定数の宣言等

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-09-30
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-09-30	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYMMRCONSTANTS_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYMMRCONSTANTS_H_INCLUDED

/* libtiffのmmrcodes.hを*.cppと*.hに分離したコード．
 * Constatsがヘッダファイルに在るのって気持ち悪いからね．
 */

/*
 * Copyright (c) 1988-1997 Sam Leffler
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

typedef struct {		/* state table entry */
    unsigned char	State;	/* see above */
    unsigned char	Width;	/* width of code in bits */
    unsigned short	Param;	/* unsigned 16-bit run length in bits */
} XdwCodecTIFF_TIFFFaxTabEnt;

typedef struct tableentry {
    unsigned short	length;	/* bit length of g3 code */
    unsigned short	code;	/* g3 code */
    short		runlen;	/* run length in bits */
} XdwCodecTIFF_tableentry;

/* 以下，extern宣言 */

extern const XdwCodecTIFF_tableentry TIFFFaxWhiteCodes[];
extern const XdwCodecTIFF_tableentry TIFFFaxBlackCodes[];
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxMainTable[128];
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxWhiteTable[4096];
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxBlackTable[8192];
extern const unsigned char TIFFBitRevTable[256];
extern const unsigned char zeroruns[256];
extern const unsigned char oneruns[256];
extern const XdwCodecTIFF_tableentry horizcode;
extern const XdwCodecTIFF_tableentry passcode;
extern const XdwCodecTIFF_tableentry vcodes[7];
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxBlack8Table[256]; 
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxBlack5_0[256]; 
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxBlack5_1[256]; 
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxWhite8Table[256]; 
extern const XdwCodecTIFF_TIFFFaxTabEnt TIFFFaxWhite80Table[16]; 
extern const unsigned short TIFFFaxWhite9Bit[16];

#endif /* XDWBRIDGERASTERDECODESTRATEGYMMRCONSTANTS_H_INCLUDED */
