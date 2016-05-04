//
//  w2m_gdi_def.h
//
//  Updater : $Author: chikyu $
//  Version : $Revision: 1.5 $, $Date: 2009/12/22 08:11:31 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//
// w2m_gdi.h に定義すべきだが、メタレコード定義など、OSX版との情報共有が必要なので
// 定数／データ構造定義／typedef を別ファイルにした。
//

#ifndef W2WM_WINGDI_DEF_H
#define W2WM_WINGDI_DEF_H

typedef unsigned long HGDIOBJ_XD;
typedef unsigned long HPEN_XD;
typedef unsigned long HBRUSH_XD;
typedef unsigned long HFONT_XD;
typedef unsigned long HRGN_XD;
typedef unsigned long HBITMAP_XD;

typedef int           BOOL_XD;
typedef BOOL_XD      *PBOOL_XD;

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif


#if !defined _PF_WIN32_

#include "w2mpf_def.h"
#include "w2mpf_gdi_def2.h"

#endif


// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

// Logical Pen
typedef struct _tagLOGPEN { 
    UINT        lopnStyle;
    POINT       lopnWidth;      
    COLORREF    lopnColor;
} LOGPEN, *PLOGPEN, *NPLOGPEN, *LPLOGPEN;

// for OSX's WMF
typedef struct _tagLOGPEN16 { 
    WORD        lopnStyle;
    POINTS       lopnWidth;      
    COLORREF    lopnColor;
} LOGPEN16;

// Color for Logical Palette
typedef struct _tagPALETTEENTRY {
    BYTE        peRed;
    BYTE        peGreen;
    BYTE        peBlue;
    BYTE        peFlags;
} PALETTEENTRY, *PPALETTEENTRY, *LPPALETTEENTRY;

// Logical Palette
typedef struct _tagLOGPALETTE {
    WORD        palVersion;
    WORD        palNumEntries;  
    PALETTEENTRY        palPalEntry[1];
} LOGPALETTE, *PLOGPALETTE, *NPLOGPALETTE, *LPLOGPALETTE;

#define LF_FULLFACESIZE 64
#define LF_FACESIZE		32
#define ELF_VENDOR_SIZE 4

typedef struct tagLOGFONT {
    LONG  lfHeight;                  // 文字セルまたは文字の高さ
    LONG  lfWidth;                   // 平均文字幅
    LONG  lfEscapement;              // 文字送りの方向とX軸との角度
    LONG  lfOrientation;             // ベースラインとX軸との角度
    LONG  lfWeight;                  // フォントの太さ
    BYTE  lfItalic;                  // イタリック体指定
    BYTE  lfUnderline;               // 下線付き指定
    BYTE  lfStrikeOut;               // 打ち消し線付き指定
    BYTE  lfCharSet;                 // キャラクタセット
    BYTE  lfOutPrecision;            // 出力精度
    BYTE  lfClipPrecision;           // クリッピングの精度
    BYTE  lfQuality;                 // 出力品質
    BYTE  lfPitchAndFamily;          // ピッチとファミリ
    char  lfFaceName[LF_FACESIZE];   // フォント名
} LOGFONT, *PLOGFONT, LOGFONTA, *PLOGFONTA;

typedef struct tagLOGFONTW
{
    LONG      lfHeight;
    LONG      lfWidth;
    LONG      lfEscapement;
    LONG      lfOrientation;
    LONG      lfWeight;
    BYTE      lfItalic;
    BYTE      lfUnderline;
    BYTE      lfStrikeOut;
    BYTE      lfCharSet;
    BYTE      lfOutPrecision;
    BYTE      lfClipPrecision;
    BYTE      lfQuality;
    BYTE      lfPitchAndFamily;
    WCHAR     lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW;

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_


#if !defined _PF_WIN32_

typedef struct tagEXTLOGFONTW {
    LOGFONTW    elfLogFont;
	char*		elfExt; // 以下は createFontIndirect では使用しない
/*
    WCHAR       elfFullName[LF_FULLFACESIZE];
    WCHAR       elfStyle[LF_FACESIZE];
    DWORD       elfVersion;     // 0 for the first release of NT
    DWORD       elfStyleSize;
    DWORD       elfMatch;
    DWORD       elfReserved;
    BYTE        elfVendorId[ELF_VENDOR_SIZE];
    DWORD       elfCulture;     // 0 for Latin					
    PANOSE      elfPanose;
*/
} EXTLOGFONTW, *PEXTLOGFONTW;

typedef struct tagEXTLOGPEN {
    DWORD       elpPenStyle;
    DWORD       elpWidth;
    UINT        elpBrushStyle;
    COLORREF    elpColor;
    LONG        elpHatch;
    DWORD       elpNumEntries;
    DWORD       elpStyleEntry[1];
} EXTLOGPEN, *PEXTLOGPEN;

#endif //  !defiend _PF_WIN32_


// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

typedef struct tagLOGBRUSH
{
	UINT	lbStyle;
	COLORREF	lbColor;
	LONG	lbHatch;
} LOGBRUSH, *PLOGBRUSH;

// for OSX's WMF
typedef struct tagLOGBRUSH16
{
	WORD	lbStyle;
	COLORREF	lbColor;
	WORD	lbHatch;
} LOGBRUSH16;

typedef struct _RGNDATAHEADER {
    DWORD   dwSize;
    DWORD   iType;
    DWORD   nCount;
    DWORD   nRgnSize;
    RECT    rcBound;
} RGNDATAHEADER, *PRGNDATAHEADER;

typedef struct _RGNDATA {
    RGNDATAHEADER   rdh;
    char            Buffer[1]; // array of RECT
} RGNDATA, *PRGNDATA, *NPRGNDATA, *LPRGNDATA;

typedef struct tagBITMAP { // bm
	int bmType;
	int bmWidth;
	int bmHeight;
	int bmWidthBytes;
	BYTE bmPlanes;
	BYTE bmBitsPixel;
	LPVOID bmBits;
} BITMAP, *PBITMAP;

typedef struct  tagXFORM
{
    FLOAT   eM11;
    FLOAT   eM12;
    FLOAT   eM21;
    FLOAT   eM22;
    FLOAT   eDx;
    FLOAT   eDy;
} XFORM, *PXFORM, *LPXFORM;

typedef struct tagTEXTMETRIC { 
	LONG tmHeight; 
	LONG tmAscent; 
	LONG tmDescent; 
	LONG tmInternalLeading; 
	LONG tmExternalLeading; 
	LONG tmAveCharWidth; 
	LONG tmMaxCharWidth; 
	LONG tmWeight; 
	LONG tmOverhang; 
	LONG tmDigitizedAspectX; 
	LONG tmDigitizedAspectY; 
	char tmFirstChar; 
	char tmLastChar; 
	char tmDefaultChar; 
	char tmBreakChar; 
	BYTE tmItalic; 
	BYTE tmUnderlined; 
	BYTE tmStruckOut; 
	BYTE tmPitchAndFamily; 
	BYTE tmCharSet; 
} TEXTMETRIC, *PTEXTMETRIC; 

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_


#if !defined _PF_WIN32_

///////////////////////////////////////////////////////////////////
//-------------------- Windowsメタファイル
// その他
#define MFCOMMENT   15

// Windowsメタレコードタイプ
#define META_ARC                        0x0817
#define META_CHORD                      0x0830
#define META_CREATEBRUSHINDIRECT        0x02FC
#define META_CREATEFONTINDIRECT         0x02FB
#define META_CREATEPALETTE              0x00F7
#define META_CREATEPATTERNBRUSH         0x01F9
#define META_CREATEPENINDIRECT          0x02FA
#define META_CREATEREGION               0x06FF
#define META_DELETEOBJECT               0x01F0
#define META_DIBBITBLT                  0x0940
#define META_DIBCREATEPATTERNBRUSH      0x0142
#define META_DIBSTRETCHBLT              0x0B41
#define META_ELLIPSE                    0x0418
#define META_ESCAPE                     0x0626
#define META_EXTTEXTOUT                 0x0A32
#define META_INTERSECTCLIPRECT          0x0416
#define META_LINETO                     0x0213
#define META_MOVETO                     0x0214
#define META_PATBLT                     0x061D
#define META_PIE                        0x081A
#define META_POLYGON                    0x0324
#define META_POLYLINE                   0x0325
#define META_POLYPOLYGON                0x0538
#define META_REALIZEPALETTE             0x0035
#define META_RECTANGLE                  0x041B
#define META_RESTOREDC                  0x0127
#define META_ROUNDRECT                  0x061C
#define META_SAVEDC                     0x001E
#define META_SCALEVIEWPORTEXT           0x0412
#define META_SELECTCLIPREGION           0x012C
#define META_SELECTOBJECT               0x012D
#define META_SELECTPALETTE              0x0234
#define META_SETBKCOLOR                 0x0201
#define META_SETBKMODE                  0x0102
#define META_SETPIXEL                   0x041F
#define META_SETPOLYFILLMODE            0x0106
#define META_SETROP2                    0x0104
#define META_SETSTRETCHBLTMODE          0x0107
#define META_SETTEXTALIGN               0x012E
#define META_SETTEXTCOLOR               0x0209
#define META_SETWINDOWEXT               0x020C
#define META_SETWINDOWORG               0x020B
#define META_STRETCHDIB                 0x0F43
#define META_TEXTOUT                    0x0521

// [XDWAPI for Spotlight Importer V70 2008.02.14 by akiyoshi] >>>
#define META_ANIMATEPALETTE             0x0436
#define META_BITBLT                     0x0922
#define META_EXCLUDECLIPRECT            0x0415
#define META_EXTFLOODFILL               0x0548
#define META_FILLREGION                 0x0228
#define META_FLOODFILL                  0x0419
#define META_FRAMEREGION                0x0429
#define META_INVERTREGION               0x012A
#define META_OFFSETCLIPRGN              0x0220
#define META_OFFSETVIEWPORTORG          0x0211
#define META_OFFSETWINDOWORG            0x020F
#define META_PAINTREGION                0x012B
#define META_RESIZEPALETTE              0x0139
#define META_SCALEWINDOWEXT             0x0410
#define META_SETDIBTODEV                0x0d33
#define META_SETMAPMODE                 0x0103
#define META_SETMAPPERFLAGS             0x0231
#define META_SETPALENTRIES              0x0037
#define META_SETRELABS                  0x0105
#define META_SETTEXTCHAREXTRA           0x0108
#define META_SETTEXTJUSTIFICATION       0x020A
#define META_SETVIEWPORTEXT             0x020E
#define META_SETVIEWPORTORG             0x020D
#define META_STRETCHBLT                 0x0B23
// <<<

#pragma pack(push, _mr_, 2) // adjust alignment

// Windowsメタレコード
typedef struct tagMETARECORD { 
	DWORD rdSize; 
	WORD  rdFunction; 
	WORD  rdParm[1]; 
}METARECORD, *PMETARECORD, *LPMETARECORD;
	
// Windowsメタファイルヘッダーレコード
#define WORD_SIZE			2   // 1WORD = 2bytes

typedef struct tagMETAHEADER
{
    SHORT        mtType;
    SHORT        mtHeaderSize;
    SHORT        mtVersion;
    DWORD        mtSize;
    SHORT        mtNoObjects;
    DWORD        mtMaxRecord;
    SHORT        mtNoParameters;
} METAHEADER, *PMETAHEADER, *LPMETAHEADER;
#pragma pack(pop, _mr_)

#endif // !defined _PF_WIN32_


#define WMF_HEADER_SIZE		9   // 9WORD = 18bytes

struct WMF_XD;
typedef WMF_XD* HMETAFILE_XD;

typedef void* HWND_XD;

typedef struct tagMETAFILEPICT_XD {
	LONG	mm;
	LONG	xExt;
	LONG	yExt;
	HMETAFILE_XD	hMF;
} METAFILEPICT_XD;


#if !defined _PF_WIN32_

///////////////////////////////////////////////
// -------------------- 拡張メタファイル
// 拡張メタレコードタイプ
// [XDWAPI for Spotlight Importer V70 2008.02.14 by akiyoshi] >>>
// Win2Unixに合わせる形で全入れ替え
// >>>
#define EMR_HEADER                      1
#define EMR_POLYBEZIER                  2
#define EMR_POLYGON                     3
#define EMR_POLYLINE                    4
#define EMR_POLYBEZIERTO                5
#define EMR_POLYLINETO                  6
#define EMR_POLYPOLYLINE                7
#define EMR_POLYPOLYGON                 8
#define EMR_SETWINDOWEXTEX              9
#define EMR_SETWINDOWORGEX              10
#define EMR_SETVIEWPORTEXTEX            11
#define EMR_SETVIEWPORTORGEX            12
#define EMR_SETBRUSHORGEX               13
#define EMR_EOF                         14
#define EMR_SETPIXELV                   15
#define EMR_SETMAPPERFLAGS              16
#define EMR_SETMAPMODE                  17
#define EMR_SETBKMODE                   18
#define EMR_SETPOLYFILLMODE             19
#define EMR_SETROP2                     20
#define EMR_SETSTRETCHBLTMODE           21
#define EMR_SETTEXTALIGN                22
#define EMR_SETCOLORADJUSTMENT          23
#define EMR_SETTEXTCOLOR                24
#define EMR_SETBKCOLOR                  25
#define EMR_OFFSETCLIPRGN               26
#define EMR_MOVETOEX                    27
#define EMR_SETMETARGN                  28
#define EMR_EXCLUDECLIPRECT             29
#define EMR_INTERSECTCLIPRECT           30
#define EMR_SCALEVIEWPORTEXTEX          31
#define EMR_SCALEWINDOWEXTEX            32
#define EMR_SAVEDC                      33
#define EMR_RESTOREDC                   34
#define EMR_SETWORLDTRANSFORM           35
#define EMR_MODIFYWORLDTRANSFORM        36
#define EMR_SELECTOBJECT                37
#define EMR_CREATEPEN                   38
#define EMR_CREATEBRUSHINDIRECT         39
#define EMR_DELETEOBJECT                40
#define EMR_ANGLEARC                    41
#define EMR_ELLIPSE                     42
#define EMR_RECTANGLE                   43
#define EMR_ROUNDRECT                   44
#define EMR_ARC                         45
#define EMR_CHORD                       46
#define EMR_PIE                         47
#define EMR_SELECTPALETTE               48
#define EMR_CREATEPALETTE               49
#define EMR_SETPALETTEENTRIES           50
#define EMR_RESIZEPALETTE               51
#define EMR_REALIZEPALETTE              52
#define EMR_EXTFLOODFILL                53
#define EMR_LINETO                      54
#define EMR_ARCTO                       55
#define EMR_POLYDRAW                    56
#define EMR_SETARCDIRECTION             57
#define EMR_SETMITERLIMIT               58
#define EMR_BEGINPATH                   59
#define EMR_ENDPATH                     60
#define EMR_CLOSEFIGURE                 61
#define EMR_FILLPATH                    62
#define EMR_STROKEANDFILLPATH           63
#define EMR_STROKEPATH                  64
#define EMR_FLATTENPATH                 65
#define EMR_WIDENPATH                   66
#define EMR_SELECTCLIPPATH              67
#define EMR_ABORTPATH                   68

#define EMR_GDICOMMENT                  70
#define EMR_FILLRGN                     71
#define EMR_FRAMERGN                    72
#define EMR_INVERTRGN                   73
#define EMR_PAINTRGN                    74
#define EMR_EXTSELECTCLIPRGN            75
#define EMR_BITBLT                      76
#define EMR_STRETCHBLT                  77
#define EMR_MASKBLT                     78
#define EMR_PLGBLT                      79
#define EMR_SETDIBITSTODEVICE           80
#define EMR_STRETCHDIBITS               81
#define EMR_EXTCREATEFONTINDIRECTW      82
#define EMR_EXTTEXTOUTA                 83
#define EMR_EXTTEXTOUTW                 84
#define EMR_POLYBEZIER16                85
#define EMR_POLYGON16                   86
#define EMR_POLYLINE16                  87
#define EMR_POLYBEZIERTO16              88
#define EMR_POLYLINETO16                89
#define EMR_POLYPOLYLINE16              90
#define EMR_POLYPOLYGON16               91
#define EMR_POLYDRAW16                  92
#define EMR_CREATEMONOBRUSH             93
#define EMR_CREATEDIBPATTERNBRUSHPT     94
#define EMR_EXTCREATEPEN                95
#define EMR_POLYTEXTOUTA                96
#define EMR_POLYTEXTOUTW                97

//#if(WINVER >= 0x0400)
#define EMR_SETICMMODE                  98
#define EMR_CREATECOLORSPACE            99
#define EMR_SETCOLORSPACE              100
#define EMR_DELETECOLORSPACE           101
#define EMR_GLSRECORD                  102
#define EMR_GLSBOUNDEDRECORD           103
#define EMR_PIXELFORMAT                104
//#endif /* WINVER >= 0x0400 */

//#if (WINVER >= 0x0500)
#define EMR_DRAWESCAPE                 105
#define EMR_EXTESCAPE                  106
#define EMR_STARTDOC                   107
#define EMR_SMALLTEXTOUT               108
#define EMR_FORCEUFIMAPPING            109
#define EMR_NAMEDESCAPE                110
#define EMR_COLORCORRECTPALETTE        111
#define EMR_SETICMPROFILEA             112
#define EMR_SETICMPROFILEW             113
#define EMR_ALPHABLEND                 114
#define EMR_ALPHADIBBLEND              115
#define EMR_TRANSPARENTBLT             116
#define EMR_TRANSPARENTDIB             117
#define EMR_GRADIENTFILL               118
#define EMR_SETLINKEDUFIS              119
#define EMR_SETTEXTJUSTIFICATION       120
//#endif
// <<<

// 拡張メタレコード
typedef struct tagENHMETARECORD {
    DWORD   iType;              // Record type EMR_XXX
	DWORD   nSize;              // Record size in bytes
	DWORD   dParm[1];           // Parameters
} ENHMETARECORD, *PENHMETARECORD, *LPENHMETARECORD;

// 拡張メタファイルヘッダーレコード
typedef struct tagENHMETAHEADER { // enmh 
    DWORD iType; 
    DWORD nSize; 
    RECTL rclBounds; 
    RECTL rclFrame; 
    DWORD dSignature; 
    DWORD nVersion; 
    DWORD nBytes; 
    DWORD nRecords; 
    WORD  nHandles; 
    WORD  sReserved; 
    DWORD nDescription; 
    DWORD offDescription; 
    DWORD nPalEntries; 
    SIZEL szlDevice; 
    SIZEL szlMillimeters;
    DWORD cbPixelFormat;
    DWORD offPixelFormat;
    DWORD bOpenGL;
	SIZEL szlMicrometers;		// add by tamazou(08.09.03)
} ENHMETAHEADER, *LPENHMETAHEADER, *PENHMETAHEADER;

// 拡張メタレコード共通部
typedef struct tagEMR {
    DWORD   iType;              // Enhanced metafile record type
    DWORD   nSize;              // Length of the record in bytes.
                                // This must be a multiple of 4.
} EMR, *PEMR;

// 拡張メタレコード
typedef struct tagABORTPATH
{
    EMR     emr;
} EMRBEGINPATH,      *PEMRBEGINPATH,
  EMRENDPATH,        *PEMRENDPATH,
  EMRCLOSEFIGURE,    *PEMRCLOSEFIGURE,
  EMRSAVEDC,         *PEMRSAVEDC,
  EMRREALIZEPALETTE, *PEMRREALIZEPALETTE;
  
// 拡張メタレコード・弧／弦／扇形
typedef struct tagEMRARC
{
    EMR     emr;
    RECTL   rclBox;             // Inclusive-inclusive bounding rectangle
    POINTL  ptlStart;
    POINTL  ptlEnd;
} EMRARC,   *PEMRARC,
  EMRCHORD, *PEMRCHORD,
  EMRPIE,   *PEMRPIE;

// 拡張メタレコード・パレット作成
typedef struct tagEMRCREATEPALETTE
{
    EMR     emr;
    DWORD   ihPal;              // Palette handle index
    LOGPALETTE lgpl;            // The peFlags fields in the palette entries
                                // do not contain any flags
} EMRCREATEPALETTE, *PEMRCREATEPALETTE;

// 拡張メタレコード／ペン作成
typedef struct tagEMRCREATEPEN 
{   
    EMR     emr;
    DWORD   ihPen;              // Pen handle index
    LOGPEN  lopn;
} EMRCREATEPEN, *PEMRCREATEPEN; 

// 拡張メタレコード／
typedef struct tagEMREXTCREATEPEN
{
    EMR     emr;
    DWORD   ihPen;              // Pen handle index
    DWORD   offBmi;             // Offset to the BITMAPINFO structure if any
    DWORD   cbBmi;              // Size of the BITMAPINFO structure if any
                                // The bitmap info is followed by the bitmap
                                // bits to form a packed DIB.
    DWORD   offBits;            // Offset to the brush bitmap bits if any
    DWORD   cbBits;             // Size of the brush bitmap bits if any
    EXTLOGPEN elp;              // The extended pen with the style array.
} EMREXTCREATEPEN, *PEMREXTCREATEPEN;
  
// 拡張メタレコード・テキスト出力
typedef struct tagEMRTEXT
{
    POINTL  ptlReference;
    DWORD   nChars;
    DWORD   offString;          // Offset to the string
    DWORD   fOptions;
    RECTL   rcl;
    DWORD   offDx;              // Offset to the inter-character spacing array.
                                // This is always given.
} EMRTEXT, *PEMRTEXT;

typedef struct tagEMREXTTEXTOUTA {
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    DWORD   iGraphicsMode;      // Current graphics mode
    FLOAT   exScale;            // X and Y scales from Page units to .01mm units
    FLOAT   eyScale;            //   if graphics mode is GM_COMPATIBLE.
    EMRTEXT emrtext;            // This is followed by the string and spacing
                                // array
} EMREXTTEXTOUTA, *PEMREXTTEXTOUTA,
  EMREXTTEXTOUTW, *PEMREXTTEXTOUTW;
  
// 拡張メタレコード／ユーザ拡張
typedef struct tagEMRGDICOMMENT
{
	EMR emr;
	DWORD   cbData; // Size of data in bytes
	BYTE	Data[1];
} EMRGDICOMMENT, *PEMRGDICOMMENT;

// 拡張メタレコード／
typedef struct tagEMRSETVIEWPORTORGEX
{
	EMR emr;
	POINTL  ptlOrigin;
} EMRSETVIEWPORTORGEX, *PEMRSETVIEWPORTORGEX,
  EMRSETWINDOWORGEX, *PEMRSETWINDOWORGEX,
  EMRSETBRUSHORGEX, *PEMRSETBRUSHORGEX;
  
// 拡張メタレコード／
typedef struct tagEMRSETTEXTALIGN
{
	EMR emr;
	DWORD iMode;
} EMRSELECTCLIPPATH, *PEMRSELECTCLIPPATH,
  EMRSETBKMODE, *PEMRSETBKMODE,
  EMRSETMAPMODE, *PEMRSETMAPMODE,
  EMRSETPOLYFILLMODE, *PEMRSETPOLYFILLMODE,
  EMRSETROP2, *PEMRSETROP2,
  EMRSETSTRETCHBLTMODE, *PEMRSETSTRETCHBLTMODE,
  EMRSETICMMODE, *PEMRSETICMMODE,
  EMRSETTEXTALIGN, *PEMRSETTEXTALIGN;
  
// 拡張メタレコード／
typedef struct tagEMRLINETO
{
	EMR emr;
	POINTL ptl;
} EMRLINETO, *PEMRLINETO,
  EMRMOVETOEX, *PEMRMOVETOEX;
  
// 拡張メタレコード
typedef struct tagEMREXTCREATEFONTINDIRECTW
{
	EMR emr;
	DWORD   ihFont;		// index to the font in handle table
	EXTLOGFONTW elfw;   // Logical font
} EMREXTCREATEFONTINDIRECTW, *PEMREXTCREATEFONTINDIRECTW;

// 拡張メタレコード
typedef struct tagEMRSELECTOBJECT
{
	EMR emr;
	DWORD   ihObject;		// index of object in handle table
} EMRSELECTOBJECT, *PEMRSELECTOBJECT,
  EMRDELETEOBJECT, *PEMRDELETEOBJECT;
  
// 拡張メタレコード
typedef struct tagEMRCREATEBRUSHINDIRECT
{
	EMR emr;
	DWORD   ihBrush;	// Brush handle index
	LOGBRUSH	lb;		// The style must be BS_SOLID, BS_HOLLOW, BS_NULL or BS_HATCHED.
} EMRCREATEBRUSHINDIRECT, *PEMRCREATEBRUSHINDIRECT;

// 拡張メタレコード
typedef struct tagEMRSETTEXTCOLOR
{
	EMR emr;
	COLORREF	crColor;
} EMRSETBKCOLOR, *PEMRSETBKCOLOR,
  EMRSETTEXTCOLOR, *PEMRSETTEXTCOLOR;
  
// 拡張メタレコード／楕円、四角
typedef struct tagEMRELLIPSE
{ 
    EMR     emr;
    RECTL   rclBox;             // Inclusive-inclusive bounding rectangle
} EMRELLIPSE,  *PEMRELLIPSE,
  EMRRECTANGLE, *PEMRRECTANGLE;

// 拡張メタレコード／パスの塗りつぶし、パスの描画
typedef struct tagEMRFILLPATH
{ 
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
} EMRFILLPATH,          *PEMRFILLPATH,
  EMRSTROKEPATH,        *PEMRSTROKEPATH;

// 拡張メタレコード／クリッピング
typedef struct tagEMREXCLUDECLIPRECT
{ 
    EMR     emr;
    RECTL   rclClip;
} EMRINTERSECTCLIPRECT, *PEMRINTERSECTCLIPRECT;

// 拡張メタレコード／クリッピング
typedef struct tagEMREXTSELECTCLIPRGN
{ 
    EMR     emr;
    DWORD   cbRgnData;          // Size of region data in bytes
    DWORD   iMode;
    BYTE    RgnData[1];			// array of RGNDATA
} EMREXTSELECTCLIPRGN, *PEMREXTSELECTCLIPRGN;

// 拡張メタレコード／ベジエパス、多角形（32ビット対応： POINTL は座標が LONG）
typedef struct tagEMRPOLYLINE
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    DWORD   cptl;
    POINTL  aptl[1];
} EMRPOLYLINE,     *PEMRPOLYLINE,
  EMRPOLYBEZIER,   *PEMRPOLYBEZIER,
  EMRPOLYGON,      *PEMRPOLYGON,
  EMRPOLYBEZIERTO, *PEMRPOLYBEZIERTO,
  EMRPOLYLINETO,   *PEMRPOLYLINETO;

// 拡張メタレコード／ベジエパス、多角形　（１６ビット対応： POINTS は座標が SHORT）
typedef struct tagEMRPOLYLINE16
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    DWORD   cpts;
    POINTS  apts[1];
} EMRPOLYLINE16,     *PEMRPOLYLINE16,
  EMRPOLYBEZIER16,   *PEMRPOLYBEZIER16,
  EMRPOLYGON16,      *PEMRPOLYGON16,
  EMRPOLYBEZIERTO16, *PEMRPOLYBEZIERTO16,
  EMRPOLYLINETO16,   *PEMRPOLYLINETO16;

// 拡張メタレコード／複数の多角形
typedef struct tagEMRPOLYPOLYLINE
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    DWORD   nPolys;             // Number of polys
    DWORD   cptl;               // Total number of points in all polys
    DWORD   aPolyCounts[1];     // Array of point counts for each poly
    POINTL  aptl[1];            // Array of points
} EMRPOLYPOLYGON,  *PEMRPOLYPOLYGON;

// 拡張メタレコード／複数の多角形（１６ビット対応）
typedef struct tagEMRPOLYPOLYLINE16
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    DWORD   nPolys;             // Number of polys
    DWORD   cpts;               // Total number of points in all polys
    DWORD   aPolyCounts[1];     // Array of point counts for each poly
    POINTS  apts[1];            // Array of points
} EMRPOLYPOLYLINE16, *PEMRPOLYPOLYLINE16, EMRPOLYPOLYGON16,  *PEMRPOLYPOLYGON16;

// 拡張メタレコード／デバイスコンテキストの状態を戻す
typedef struct tagEMRRESTOREDC
{
    EMR     emr;
    LONG    iRelative;          // Specifies a relative instance 
} EMRRESTOREDC, *PEMRRESTOREDC;

// 拡張メタレコード／角が丸い四角
typedef struct tagEMRROUNDRECT
{
    EMR     emr;
    RECTL   rclBox;             // Inclusive-inclusive bounding rectangle
    SIZEL   szlCorner;
} EMRROUNDRECT, *PEMRROUNDRECT;

// 拡張メタレコード／描画領域のスケーリング
typedef struct tagEMRSCALEVIEWPORTEXTEX {
  EMR  emr; 
  LONG xNum; 
  LONG xDenom; 
  LONG yNum; 
  LONG yDenom; 
} EMRSCALEVIEWPORTEXTEX, *PEMRSCALEVIEWPORTEXTEX, 
  EMRSCALEWINDOWEXTEX,   *PEMRSCALEWINDOWEXTEX; 
  

// 拡張メタレコード／論理パレットを選択する
typedef struct tagEMRSELECTPALETTE
{
    EMR     emr;
    DWORD   ihPal;              // Palette handle index, background mode only
} EMRSELECTPALETTE, *PEMRSELECTPALETTE;

// 拡張メタレコード／ウィンドウの大きさを設定する
typedef struct tagEMRSETVIEWPORTEXTEX
{
    EMR     emr;
    SIZEL   szlExtent;          
} EMRSETVIEWPORTEXTEX, *PEMRSETVIEWPORTEXTEX,
  EMRSETWINDOWEXTEX,   *PEMRSETWINDOWEXTEX;
  
// 拡張メタレコード／ビットマップ転送
typedef struct tagEMRBITBLT
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    LONG    xDest;
    LONG    yDest;
    LONG    cxDest;
    LONG    cyDest;
    DWORD   dwRop;
    LONG    xSrc;
    LONG    ySrc;
    XFORM   xformSrc;           // Source DC transform
    COLORREF crBkColorSrc;      // Source DC BkColor in RGB
    DWORD   iUsageSrc;          // Source bitmap info color table usage
                                // (DIB_RGB_COLORS)
    DWORD   offBmiSrc;          // Offset to the source BITMAPINFO structure
    DWORD   cbBmiSrc;           // Size of the source BITMAPINFO structure
    DWORD   offBitsSrc;         // Offset to the source bitmap bits
    DWORD   cbBitsSrc;          // Size of the source bitmap bits
} EMRBITBLT, *PEMRBITBLT;

// 拡張メタレコード／サイズ縮小機能付きビットマップ転送
typedef struct tagEMRSTRETCHBLT
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    LONG    xDest;
    LONG    yDest;
    LONG    cxDest;
    LONG    cyDest;
    DWORD   dwRop;
    LONG    xSrc;
    LONG    ySrc;
    XFORM   xformSrc;           // Source DC transform
    COLORREF crBkColorSrc;      // Source DC BkColor in RGB
    DWORD   iUsageSrc;          // Source bitmap info color table usage
                                // (DIB_RGB_COLORS)
    DWORD   offBmiSrc;          // Offset to the source BITMAPINFO structure
    DWORD   cbBmiSrc;           // Size of the source BITMAPINFO structure
    DWORD   offBitsSrc;         // Offset to the source bitmap bits
    DWORD   cbBitsSrc;          // Size of the source bitmap bits
    LONG    cxSrc;
    LONG    cySrc;
} EMRSTRETCHBLT, *PEMRSTRETCHBLT;

typedef struct tagEMRSTRETCHDIBITS
{
    EMR     emr;
    RECTL   rclBounds;          // Inclusive-inclusive bounds in device units
    LONG    xDest;
    LONG    yDest;
    LONG    xSrc;
    LONG    ySrc;
    LONG    cxSrc;
    LONG    cySrc;
    DWORD   offBmiSrc;          // Offset to the source BITMAPINFO structure
    DWORD   cbBmiSrc;           // Size of the source BITMAPINFO structure
    DWORD   offBitsSrc;         // Offset to the source bitmap bits
    DWORD   cbBitsSrc;          // Size of the source bitmap bits
    DWORD   iUsageSrc;          // Source bitmap info color table usage
    DWORD   dwRop;
    LONG    cxDest;
    LONG    cyDest;
} EMRSTRETCHDIBITS, *PEMRSTRETCHDIBITS;

typedef struct tagEMRCREATEMONOBRUSH
{
    EMR     emr;
    DWORD   ihBrush;            // Brush handle index
    DWORD   iUsage;             // Bitmap info color table usage
    DWORD   offBmi;             // Offset to the BITMAPINFO structure
    DWORD   cbBmi;              // Size of the BITMAPINFO structure
    DWORD   offBits;            // Offset to the bitmap bits
    DWORD   cbBits;             // Size of the bitmap bits
} EMRCREATEMONOBRUSH, *PEMRCREATEMONOBRUSH;

typedef struct tagEMRCREATEDIBPATTERNBRUSHPT
{
    EMR     emr;
    DWORD   ihBrush;            // Brush handle index
    DWORD   iUsage;             // Bitmap info color table usage
    DWORD   offBmi;             // Offset to the BITMAPINFO structure
    DWORD   cbBmi;              // Size of the BITMAPINFO structure
                                // The bitmap info is followed by the bitmap
                                // bits to form a packed DIB.
    DWORD   offBits;            // Offset to the bitmap bits
    DWORD   cbBits;             // Size of the bitmap bits
} EMRCREATEDIBPATTERNBRUSHPT, *PEMRCREATEDIBPATTERNBRUSHPT;

typedef struct tagEMRMASKBLT
{
	EMR     emr; 
	RECTL   rclBounds; 
	LONG    xDest; 
	LONG    yDest; 
	LONG    cxDest; 
	LONG    cyDest; 
	DWORD   dwRop; 
	LONG    xSrc; 
	LONG    ySrc; 
	XFORM   xformSrc; 
	COLORREF crBkColorSrc; 
	DWORD   iUsageSrc; 
	DWORD   offBmiSrc; 
	DWORD   cbBmiSrc; 
	DWORD   offBitsSrc; 
	DWORD   cbBitsSrc; 
	LONG    xMask; 
	LONG    yMask; 
	DWORD   iUsageMask; 
	DWORD   offBmiMask; 
	DWORD   cbBmiMask; 
	DWORD   offBitsMask; 
	DWORD   cbBitsMask; 
} EMRMASKBLT, *PEMRMASKBLT;

#ifndef _M3CORE_MP_

/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version                    */
#define TECHNOLOGY    2     /* Device classification                    */
#define HORZSIZE      4     /* Horizontal size in millimeters           */
#define VERTSIZE      6     /* Vertical size in millimeters             */
#define HORZRES       8     /* Horizontal width in pixels               */
#define VERTRES       10    /* Vertical height in pixels                */
#define BITSPIXEL     12    /* Number of bits per pixel                 */
#define PLANES        14    /* Number of planes                         */
#define NUMBRUSHES    16    /* Number of brushes the device has         */
#define NUMPENS       18    /* Number of pens the device has            */
#define NUMMARKERS    20    /* Number of markers the device has         */
#define NUMFONTS      22    /* Number of fonts the device has           */
#define NUMCOLORS     24    /* Number of colors the device supports     */
#define PDEVICESIZE   26    /* Size required for device descriptor      */
#define CURVECAPS     28    /* Curve capabilities                       */
#define LINECAPS      30    /* Line capabilities                        */
#define POLYGONALCAPS 32    /* Polygonal capabilities                   */
#define TEXTCAPS      34    /* Text capabilities                        */
#define CLIPCAPS      36    /* Clipping capabilities                    */
#define RASTERCAPS    38    /* Bitblt capabilities                      */
#define ASPECTX       40    /* Length of the X leg                      */
#define ASPECTY       42    /* Length of the Y leg                      */
#define ASPECTXY      44    /* Length of the hypotenuse                 */

#endif // _M3CORE_MP_

/* Device Technologies */
#define DT_PLOTTER          0   /* Vector plotter                   */
#define DT_RASDISPLAY       1   /* Raster display                   */
#define DT_RASPRINTER       2   /* Raster printer                   */
#define DT_RASCAMERA        3   /* Raster camera                    */
#define DT_CHARSTREAM       4   /* Character-stream, PLP            */
#define DT_METAFILE         5   /* Metafile, VDM                    */
#define DT_DISPFILE         6   /* Display-file                     */

/* Object Definitions for EnumObjects() */
#define OBJ_PEN             1
#define OBJ_BRUSH           2
#define OBJ_DC              3
#define OBJ_METADC          4
#define OBJ_PAL             5
#define OBJ_FONT            6
#define OBJ_BITMAP          7
#define OBJ_REGION          8
#define OBJ_METAFILE        9
#define OBJ_MEMDC           10
#define OBJ_EXTPEN          11
#define OBJ_ENHMETADC       12
#define OBJ_ENHMETAFILE     13

#endif //  !defined _PF_WIN32_


//------------------------------------------------------------
// Bitmap 関連

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

typedef struct tagRGBQUAD {
	BYTE	rgbBlue;
	BYTE	rgbGreen;
	BYTE	rgbRed;
	BYTE	rgbReserved;
} RGBQUAD, *LPRGBQUAD;

typedef struct tagBITMAPINFOHEADER {
	DWORD	biSize;
	LONG	biWidth;
	LONG	biHeight;
	WORD	biPlanes;
	WORD	biBitCount;
	DWORD	biCompression;
	DWORD	biSizeImage;
	LONG	biXPelsPerMeter;
	LONG	biYPelsPerMeter;
	DWORD	biClrUsed;
	DWORD	biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

/* structures for defining DIBs */
typedef struct tagBITMAPCOREHEADER {
        DWORD   bcSize;       // used to get to color table
        WORD    bcWidth;
        WORD    bcHeight;
        WORD    bcPlanes;
        WORD    bcBitCount;
} BITMAPCOREHEADER, *LPBITMAPCOREHEADER, *PBITMAPCOREHEADER;

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_


#if !defined _PF_WIN32_

/* constants for the biCompression field */
//#define BI_RGB			0L
#define BI_RLE8			1L
#define BI_RLE4			2L
#define BI_BITFIELDS	3L

#endif // !defined _PF_WIN32_

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER	bmiHeader;
	RGBQUAD	bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

#define BITMAPFILEHEADER_SIZE 14
//#include <pshpack2.h> (２バイト境界でデータが格納されている）
#pragma pack(push,2) // 2バイトバウンダリをpush
typedef struct tagBITMAPFILEHEADER {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
//#include <poppack.h>
#pragma pack(pop)	// 元に戻す

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_

#if !defined _PF_WIN32_

typedef struct tagEMRSETWORLDTRANSFORM {
	EMR   emr; 
	XFORM xform; 
} EMRSETWORLDTRANSFORM, *PEMRSETWORLDTRANSFORM; 

#endif // !defined _PF_WIN32_

// [XDWAPI for Spotlight Importer V70 2008.02.14 by akiyoshi] >>>
//#ifdef _XDWAPI_
#include <map>

struct FONTINFO {
	bool bIsFont;
	int height;
	int width;
    int escapement;
	int orientation;
	BYTE charset;
};

struct DC_XD;
struct EMF_XD;
typedef DC_XD* HDC_XD;
typedef EMF_XD* HENHMETAFILE_XD;

/*
// WMF/EMFのレコードをもとに、カレントのCharSetを設定する
bool w2m_PlayMetaFileRecordForCharSet(HDC hDC,PMETARECORD pWMFR);
bool w2m_PlayEnhMetaFileRecordForCharSet(HDC hDC,CONST ENHMETARECORD *lpEMFR);

// カレントのCharsetを取得する
BYTE w2m_GetCurrentCharSet(HDC hDC);

// カレントフォントのサイズを取得する
SIZE w2m_GetCurrentFontSize(HDC hDC);

// カレントフォントのベースラインの角度を取得する
int w2m_GetCurrentFontOrientation(HDC hDC);
*/

class CFontMgr
{
public:
	CFontMgr();
	~CFontMgr();
	void Add(int nID,FONTINFO fontInfo);
	void Add(FONTINFO fontInfo);
	void Delete(int nID);
	void Select(int nID);
	void Clear();
	FONTINFO GetFontInfo();
private:
	int m_nFontInfoID;
	std::map<int,FONTINFO> m_FontInfo;
};
//#endif //def _XDWAPI_
// <<< [XDWAPI]

/////////////////////////////////////////////////////////////////////////////

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end
typedef HGDIOBJ_XD		HGDIOBJ;
typedef HPEN_XD		HPEN;
typedef HBRUSH_XD		HBRUSH;
typedef HFONT_XD		HFONT;
typedef HRGN_XD		HRGN;
typedef HBITMAP_XD		HBITMAP;
//typedef DC_XD			DC;
typedef HDC_XD			HDC;
#endif

#include "HBPS.h"
// add 2011/03/03 by NEU for Android begin
#if (defined _PF_ANDROID_ && defined USE_SKIABRIDGE)
class XdwBridgeSkia;
#endif
// add 2011/03/03 by NEU for Android begin
struct DC_XD
{
#if defined _PF_IOS_ || _PF_OSX_
	XdwBridgeQuartz* bridge;
#else
	// add 2011/03/03 by NEU for Android begin
	#if (defined _PF_ANDROID_ && defined USE_SKIABRIDGE)
		XdwBridgeSkia* bridge;
	#else
		XdwBridgeHBPS* bridge;
	#endif
	// add 2011/03/03 by NEU for Android end
#endif
	XdwOffScreenDIB* offscreen;
	XdwNulLog* log;
	CFontMgr* fontmgr;
	// オブジェクトクリッピング領域格納
	XdwRectangle clipRect;
    // 12.02.06 Bito - テキスト選択・検索対応
    // テキスト座標計算に必要な情報を格納
    POINTL  winOrg; // 原点のオフセット
    SIZEL   winExt; // ページのドット数 
    SIZEL   ext;    // ページの寸法(1/100mm)
    // テキスト配置設定
    UINT    align;
};

struct WMF_XD
{
	XdwDocuWorks::BinaryInterface* binary;
	METAFILEPICT_XD mfpict;
	RECT drawrect;
	NthDataGenerator* nthGenerator;
	int angle;
};

struct EMF_XD
{
	XdwDocuWorks::BinaryInterface* binary;
	NthDataGenerator* nthGenerator;
	int angle;
};

/////////////////////////////////////////////////////////////////////////////

#endif
// W2M_WINGDI_DEF_H

