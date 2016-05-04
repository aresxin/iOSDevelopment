//
//  MXDPalette.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDGdiObject.h"

typedef struct tagPALETTEENTRY {
	unsigned char   peRed;				// 赤
    unsigned char   peGreen;			// 緑
    unsigned char   peBlue;				// 青
    unsigned char   peFlags; 
} MXD_PaletteEntry;

typedef struct tagLOGPALETTE {
    unsigned int	palVersion; 
    unsigned int	palNumEntries; 
    MXD_PaletteEntry palPalEntry[1]; 
} MXD_LogPalette; 

@interface MXDPalette : MXDGdiObject {
	unsigned int _palNumEntries;
	unsigned int* _colorTable;
}

/*
 *  ストックオブジェクト用
 */
+ (MXDPalette*)defaultPalette;

/*
 *  Windows の論理カラー パレットを作成し、MXDPalette オブジェクトを初期化します。さらに、そのパレットを MXDPalette オブジェクトに結び付けます。
 *
 *  @param lpLogPalette 論理パレットのカラー情報を保持する LOGPALETTE 構造体へのポインタ。
 *
 *  @return 正常終了した場合は 0 以外を返します。それ以外の場合は 0 を返します。
 */
+ (MXDPalette*)createPalette:(MXD_LogPalette*)lpLogPalette;

// テスト用
- (NSColor*)colorAtIndex:(int)index;
- (unsigned long)colorIntOfAtIndex:(int)index;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//-- new method --- added by YuFei[2010/8/20]

// Resize palette.
- (BOOL)resizePalette:(unsigned int)palNumEntries;
- (BOOL)setPaletteEntries:(unsigned int)position length:(unsigned int)length colorTable:(unsigned int*)color;

@end
