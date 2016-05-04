//  w2m_gdi_def2.h
//
//  Updater : $Author: chikyu $
//  Version : $Revision: 1.5 $, $Date: 2009/12/22 08:11:31 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//
// w2m_gdi_def.h に定義すべきだが、OSX版のGDI-APIで使用するモードなどの定数を、
// メタレコードを媒介にして Windows版と共有するので、それらに限定して別ファイルとする。
//
// このファイルは、純粋な Objective-C(*.m)で import するので、
// Winodws固有の型は使用しない。
//
// w2m_gdi_def.h で、このファイルを include している。
// コアラッパーやコアで、このファイルでの定義が必要な場合は、このファイルを直接includeせずに、
// w2m_gdi_def.h を include すること。
// (重複 include の防御対策をとっていないので、このファイルを C および C++ で直接
//  include すると、コンパイルエラーになる可能性が高い)
//
#ifndef W2M_WINGDI_DEF2_H
#define W2M_WINGDI_DEF2_H

// Binary raster ops
#define R2_BLACK            1   //  0       
#define R2_NOTMERGEPEN      2   // DPon     
#define R2_MASKNOTPEN       3   // DPna     
#define R2_NOTCOPYPEN       4   // PN       
#define R2_MASKPENNOT       5   // PDna     
#define R2_NOT              6   // Dn       
#define R2_XORPEN           7   // DPx      
#define R2_NOTMASKPEN       8   // DPan     
#define R2_MASKPEN          9   // DPa      
#define R2_NOTXORPEN        10  // DPxn     
#define R2_NOP              11  // D        
#define R2_MERGENOTPEN      12  // DPno     
#define R2_COPYPEN          13  // P        
#define R2_MERGEPENNOT      14  // PDno     
#define R2_MERGEPEN         15  // DPo      
#define R2_WHITE            16  //  1       
#define R2_LAST             16


// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

// Ternary raster operations
#define SRCCOPY        (unsigned long)0x00CC0020 // dest = source
#define SRCPAINT       (unsigned long)0x00EE0086 // dest = source OR dest
#define SRCAND         (unsigned long)0x008800C6 // dest = source AND dest
#define SRCINVERT      (unsigned long)0x00660046 // dest = source XOR dest
#define SRCERASE       (unsigned long)0x00440328 // dest = source AND (NOT dest )
#define NOTSRCCOPY     (unsigned long)0x00330008 // dest = (NOT source)
#define NOTSRCERASE    (unsigned long)0x001100A6 // dest = (NOT src) AND (NOT dest)
#define MERGECOPY      (unsigned long)0x00C000CA // dest = (source AND pattern)
#define MERGEPAINT     (unsigned long)0x00BB0226 // dest = (NOT source) OR dest
#define PATCOPY        (unsigned long)0x00F00021 // dest = pattern
#define PATPAINT       (unsigned long)0x00FB0A09 // dest = DPSnoo
#define PATINVERT      (unsigned long)0x005A0049 // dest = pattern XOR dest
#define DSTINVERT      (unsigned long)0x00550009 // dest = (NOT dest)
#define BLACKNESS      (unsigned long)0x00000042 // dest = BLACK
#define WHITENESS      (unsigned long)0x00FF0062 // dest = WHITE

// Quaternary raster codes
#define MAKEROP4(fore,back) (unsigned long)((((back) << 8) & 0xFF000000) | (fore))

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_

#define GDI_ERROR (0xFFFFFFFFL)
#define HGDI_ERROR ((HANDLE)(0xFFFFFFFFL))

// Region Flags
#define ERROR               0
#define NULLREGION          1
#define SIMPLEREGION        2
#define COMPLEXREGION       3
#define RGN_ERROR ERROR



// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

// CombineRgn() Styles
#define RGN_AND             1
#define RGN_OR              2
#define RGN_XOR             3
#define RGN_DIFF            4
#define RGN_COPY            5
#define RGN_MIN             RGN_AND
#define RGN_MAX             RGN_COPY

/* in OSX; setStretchMode() is empty.
// StretchBlt() Modes
#define BLACKONWHITE                 1
#define WHITEONBLACK                 2
#define COLORONCOLOR                 3
#define HALFTONE                     4
#define MAXSTRETCHBLTMODE            4

//#if(WINVER >= 0x0400)
// New StretchBlt() Modes 
#define STRETCH_ANDSCANS    BLACKONWHITE
#define STRETCH_ORSCANS     WHITEONBLACK
#define STRETCH_DELETESCANS COLORONCOLOR
#define STRETCH_HALFTONE    HALFTONE
//#endif // WINVER >= 0x0400
*/

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_

// PolyFill() Modes
#define ALTERNATE                    1
#define WINDING                      2
#define POLYFILL_LAST                2

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

// Text Alignment Options
#define TA_NOUPDATECP                0
#define TA_UPDATECP                  1

#define TA_LEFT                      0
#define TA_RIGHT                     2
#define TA_CENTER                    6

#define TA_TOP                       0
#define TA_BOTTOM                    8
#define TA_BASELINE                  24
//#if (WINVER >= 0x0400)
#define TA_RTLREADING                256
#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP+TA_RTLREADING)
//#else
//#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP)
//#endif

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_

// for 
#define OUT_DEFAULT_PRECIS          0
#define OUT_STRING_PRECIS           1
#define OUT_CHARACTER_PRECIS        2
#define OUT_STROKE_PRECIS           3
#define OUT_TT_PRECIS               4
#define OUT_DEVICE_PRECIS           5
#define OUT_RASTER_PRECIS           6
#define OUT_TT_ONLY_PRECIS          7
#define OUT_OUTLINE_PRECIS          8
#define OUT_SCREEN_OUTLINE_PRECIS   9

#define CLIP_DEFAULT_PRECIS     0
#define CLIP_CHARACTER_PRECIS   1
#define CLIP_STROKE_PRECIS      2
#define CLIP_MASK               0xf
#define CLIP_LH_ANGLES          (1<<4)
#define CLIP_TT_ALWAYS          (2<<4)
#define CLIP_EMBEDDED           (8<<4)

#define DEFAULT_QUALITY         0
#define DRAFT_QUALITY           1
#define PROOF_QUALITY           2
//#if(WINVER >= 0x0400)
#define NONANTIALIASED_QUALITY  3
#define ANTIALIASED_QUALITY     4
//#endif // WINVER >= 0x0400

#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2
//#if(WINVER >= 0x0400)
#define MONO_FONT               8
//#endif // WINVER >= 0x0400

// charset
#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#define SHIFTJIS_CHARSET        128
#define HANGEUL_CHARSET         129
#define HANGUL_CHARSET          129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255
//#if(WINVER >= 0x0400)
#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204

#define MAC_CHARSET             77
#define BALTIC_CHARSET          186

#define FS_LATIN1               0x00000001L
#define FS_LATIN2               0x00000002L
#define FS_CYRILLIC             0x00000004L
#define FS_GREEK                0x00000008L
#define FS_TURKISH              0x00000010L
#define FS_HEBREW               0x00000020L
#define FS_ARABIC               0x00000040L
#define FS_BALTIC               0x00000080L
#define FS_VIETNAMESE           0x00000100L
#define FS_THAI                 0x00010000L
#define FS_JISJAPAN             0x00020000L
#define FS_CHINESESIMP          0x00040000L
#define FS_WANSUNG              0x00080000L
#define FS_CHINESETRAD          0x00100000L
#define FS_JOHAB                0x00200000L
#define FS_SYMBOL               0x80000000L
//#endif // WINVER >= 0x0400

// Font Families
#define FF_DONTCARE   (0<<4) // Don't care or don't know. 
#define FF_ROMAN      (1<<4) // Variable stroke width, serifed. 
                             // Times Roman, Century Schoolbook, etc. 
#define FF_SWISS      (2<<4) // Variable stroke width, sans-serifed. 
                             // Helvetica, Swiss, etc. 
#define FF_MODERN     (3<<4) // Constant stroke width, serifed or sans-serifed. 
                             // Pica, Elite, Courier, etc. 
#define FF_SCRIPT     (4<<4) // Cursive, etc. 
#define FF_DECORATIVE (5<<4) // Old English, etc. 

// Font Weights 
#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

#define FW_ULTRALIGHT       FW_EXTRALIGHT
#define FW_REGULAR          FW_NORMAL
#define FW_DEMIBOLD         FW_SEMIBOLD
#define FW_ULTRABOLD        FW_EXTRABOLD
#define FW_BLACK            FW_HEAVY

// Text Alignment Options
#define ETO_OPAQUE          0x0002
#define ETO_CLIPPED         0x0004

// Background Modes 
#define TRANSPARENT         1
#define OPAQUE              2
#define BKMODE_LAST         2

// Mapping Modes
#define MM_TEXT             1
#define MM_LOMETRIC         2
#define MM_HIMETRIC         3
#define MM_LOENGLISH        4
#define MM_HIENGLISH        5
#define MM_TWIPS            6
#define MM_ISOTROPIC        7
#define MM_ANISOTROPIC      8

#define BS_SOLID			0	// 純色のブラシ
#define BS_NULL				1	// BS_HOLLOWと同じ
#define BS_HOLLOW			BS_NULL	// 中空のブラシ
#define BS_HATCHED			2   // ハッチブラシ
#define BS_PATTERN			3	// メモリビットマップで定義されるブラシパターン
#define BS_DIBPATTERN		5	// デバイスに依存しないビットマップ(DIB)仕様で定義されるパターンブラシ
								// このときlbHatchメンバはパックされたDIBのハンドルを保持します。
#define BS_DIBPATTERNPT		6	// デバイスに依存しないビットマップ(DIB)仕様で定義されるパターンブラシ
								// このときlbHatchメンバはパックされたDIBのポインンタを保持します。

// Hatch Styles
#define HS_HORIZONTAL		0	// ----- 水平ハッチ
#define HS_VERTICAL			1	// ||||| 垂直ハッチ
#define HS_FDIAGONAL		2	// \\\\\ 45 度の右下がりのハッチ
#define HS_BDIAGONAL		3	// ///// 45 度の右上がりのハッチ
#define HS_CROSS			4	// +++++ 水平と垂直のクロスハッチ
#define HS_DIAGCROSS		5	// xxxxx 45 度のクロスハッチ

// Pen Styles
#define PS_SOLID            0
#define PS_DASH             1       // -------
#define PS_DOT              2       // .......
#define PS_DASHDOT          3       // _._._._
#define PS_DASHDOTDOT       4       // _.._.._
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define PS_ENDCAP_ROUND     0x00000000
#define PS_ENDCAP_SQUARE    0x00000100
#define PS_ENDCAP_FLAT      0x00000200
#define PS_ENDCAP_MASK      0x00000F00

#define PS_JOIN_ROUND       0x00000000
#define PS_JOIN_BEVEL       0x00001000
#define PS_JOIN_MITER       0x00002000
#define PS_JOIN_MASK        0x0000F000

#define PS_COSMETIC         0x00000000
#define PS_GEOMETRIC        0x00010000
#define PS_TYPE_MASK        0x000F0000

// DIB color table identifiers
#define DIB_RGB_COLORS  0	// color table in RGBs
#define DIB_PAL_COLORS  1	// color table in palette indices

// Stock Logical Objects
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define OEM_FIXED_FONT      10
#define ANSI_FIXED_FONT     11
#define ANSI_VAR_FONT       12
#define SYSTEM_FONT         13
#define DEVICE_DEFAULT_FONT 14
#define DEFAULT_PALETTE     15
#define SYSTEM_FIXED_FONT   16
// MFCを使うと再定義されたとWarningが出るので
#ifndef DEFAULT_GUI_FONT
#define DEFAULT_GUI_FONT    17
#endif
#define DC_BRUSH            18
#define DC_PEN              19
#define STOCK_LAST          19

// Stock object flag used inthe object handle index in the enhanced
// metafile records.
// E.g. The object handle index (META_STOCK_OBJECT | BLACK_BRUSH)
// represents the stock object BLACK_BRUSH.
#define ENHMETA_STOCK_OBJECT 0x80000000

// enhanced metafile record で使われるストックオブジェクトのオブジェクトハンドルインデックスから、
// ストックオブジェクトのインデックスを取得する為のマクロ。
// OSX版固有。
#define getStockObjectIndex(index)      (index & ~ENHMETA_STOCK_OBJECT)

#endif

