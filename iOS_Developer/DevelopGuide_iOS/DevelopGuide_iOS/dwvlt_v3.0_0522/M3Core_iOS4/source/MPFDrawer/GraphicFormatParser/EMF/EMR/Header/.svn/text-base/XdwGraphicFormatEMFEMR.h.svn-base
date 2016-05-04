/**
 * @file  XdwGraphicFormatEMFEMR.h
 * @brief XdwGraphicFormat::EMF::EMRクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.4
 * $Id: XdwGraphicFormatEMFEMR.h,v 1.4 2009/12/22 08:10:57 chikyu Exp $
 * 
 * @date 2002-11-28 CreatePen Add Yasuhiro Ito
 * @date 2003-08-28 すべてのOLE出現レコードのIDを追加 Yasuhiro Ito
 * @date 2004-01-19 残OLE対応開始
 * @date 2004-03-09 コメント整理 Yasuhiro Ito
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_EMR_H_
#define _XDW_GRAPHIC_FORMAT_EMF_EMR_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "GraphicFormatParser/EMF/Header/XdwGraphicFormatEMF.h"

/**
 * @brief EMFのレコードを管理するパッケージ
 */
class XdwGraphicFormat::EMF::EMR
{
public:

    /********************************************/
    /* 列挙型 */
    
    /*! DocuWorksファイル中のEMFのレコードの識別子 */
    enum TypeID{
        /*! EMR_HEADERの識別子 */
        TYPE_ENH_META_HEADER = 0x01,
        /*! EMR_POLYBEZIERの識別子 */
        TYPE_POLY_BEZIER,
        /*! EMR_POLYGONの識別子 */
        TYPE_POLYGON,
        /*! EMR_POLYLINEの識別子 */
        TYPE_POLYLINE,
        /*! EMR_POLYBEZIERTOの識別子 */
        TYPE_POLY_BEZIER_TO,
        /*! EMR_POLYLINETOの識別子 */
        TYPE_POLYLINE_TO,
		/*! EMR_POLYPOLYLINEの識別子 *//*2003/08/28*/
		TYPE_POLYPOLYLINE,
		/*! EMR_POLYPOLYGONの識別子 *//*2003/08/28*/
		TYPE_POLYPOLYGON,
        /*! EMR_SETWINDOWEXTEXの識別子 *//*2003/08/28*/
        TYPE_SET_WINDOW_EXT_EX ,
        /*! EMR_SETWINDOWORGEXの識別子 */
        TYPE_SET_WINDOW_ORG_EX = 0x0A,
        /*! EMR_SETVIEWPORTEXTEXの識別子 *//*2003/08/28*/
        TYPE_SET_VIEWPORT_EXT_EX,
        /*! EMR_SETVIEWPORTORGEXの識別子 *//*2003/08/28*/
        TYPE_SET_VIEWPORT_ORG_EX,
        /*! EMR_SETBRUSHORGEXの識別子 */
        TYPE_SET_BRUSH_ORG_EX = 0x0D,
        /*! EMR_EOFの識別子 */
        TYPE_EOF,
        /*! EMR_SETPIXELVの識別子 *//*2003/08/28*/
        TYPE_SET_PIXELV,
        /*! EMR_SETMAPPERFLAGSの識別子 *//*2003/08/28*/
       TYPE_SET_MAP_PAR_FLAGS,
        /*! EMR_SETMAPMODEの識別子 *//*2003/08/28*/
        TYPE_SET_MAP_MODE,
        /*! EMR_SETBKMODEの識別子 */
        TYPE_SET_BK_MODE = 0x12,
        /*! EMR_SETPOLYFILLMODEの識別子 */
        TYPE_SET_POLY_FILL_MODE,
        /*! EMR_SETROP2の識別子 */
        TYPE_SET_ROP2,
        /*! EMR_SETSTRETCHBLTMODEの識別子 */
        TYPE_SET_STRETCH_BLT_MODE,
        /*! EMR_SETTEXTALIGNの識別子 */
        TYPE_SET_TEXT_ALIGN,
		/*! EMR_SETCOLORADJIUSTMENTの識別子 *//*2003/08/28*/
        TYPE_SET_COLOR_ADJUSTMENT,
        /*! EMR_SETTEXTCOLORの識別子 */
        TYPE_SET_TEXT_COLOR = 0x18,
        /*! EMR_SETBKCOLORの識別子 */
        TYPE_SET_BK_COLOR,
		/*! EMR_OFFSETCLIPRGNの識別子 *//*2003/08/28*/
        TYPE_OFFSET_CLIP_RGN,
        /*! EMR_MOVETOEXの識別子 */
        TYPE_MOVE_TO_EX = 0x1B,
		/*! EMR_SETMETARGNの識別子 *//*2003/08/28*/
        TYPE_SET_META_RGN,
		/*! EMR_EXCLUDECLIPRECTの識別子 *//*2003/08/28*/
        TYPE_EXCLUDE_CLIP_RECT,
		/*! EMR_INTERSECTCLIPRECTの識別子*//*2002/12/11 For OLE*/
		TYPE_INTERSECT_CLIP_RECT = 0x1E,
        /*! EMR_SCALEVIEWPORTEXTEXの識別子 *//*2003/08/28*/
        TYPE_SCALE_VIEWPORT_EXT_EX,
		/*! EMR_SCALEWINDOWEXTEXの識別子 *//*2003/08/28*/
        TYPE_SCALE_WINDOW_EXT_EX,
        /*! EMR_SAVEDCの識別子 */
        TYPE_SAVE_DC = 0x21,
        /*! EMR_RESTOREDCの識別子 */
        TYPE_RESTORE_DC,
		/*! EMR_SETWORLDTRANSFORMの識別子 *//*2003/08/28*/
        TYPE_SET_WORLD_TRANSFORM,
		/*! EMR_MODIFYWORLDTRANSFORMの識別子 *//*2003/08/28*/
        TYPE_MIDIFY_WORLD_TRANSFORM,
		/*! EMR_SELECTOBJECTの識別子 */
        TYPE_SELECT_OBJECT = 0x25,
		/*! EMR_CREATEPENの識別子*/
		TYPE_CREATE_PEN,/*2002/11/28 YasuhiroIto*/
        /*! EMR_CREATEBRUSHINDIRECTの識別子 */
        TYPE_CREATE_BRUSH_INDIRECT = 0x27,
        /*! EMR_DELETEOBJECTの識別子 */
        TYPE_DELETE_OBJECT,
		/*! EMR_ANGLEARCの識別子 *//*2003/08/28*/
        TYPE_ANGLE_ARC,
		/*! EMR_ELLIPSEの識別子 *//*2003/08/28*/
        TYPE_ELLIPSE,
        /*! EMR_RECTANGLEの識別子 */
        TYPE_RECTANGLE = 0x2B,
		/*! EMR_ROUNDRECTの識別子 *//*2003/08/28*/
        TYPE_ROUND_RECT,
		/*! EMR_ARCの識別子 *//*2003/08/28*/
        TYPE_ARC,
		/*! EMR_CHORDの識別子 *//*2003/08/28*/
        TYPE_CHORD,
		/*! EMR_PIEの識別子 *//*2003/08/28*/
        TYPE_PIE,
		/*! EMR_SELECTPALETTE*//*2002/12/11 For OLE*/
		TYPE_SELECT_PALETTE = 0x30,
		/*! EMR_CREATEPALETTEの識別子*//*2002/12/11 For OLE*/
		TYPE_CREATE_PALETTE = 0x31,
		/*! EMR_SETPALETTEENTRIESの識別子 *//*2003/08/28*/
        TYPE_SET_PALETTE_ENTRIES,
		/*! EMR_RESIZEPALETTEの識別子 *//*2003/08/28*/
        TYPE_RESIZE_PALETTE,
		/*! EMR_REALIZEPALETTEの識別子*//*2002/12/11 For OLE*/
		TYPE_REALIZE_PALETTE = 0x34,
		/*! EMR_EXTFLOODFILLの識別子*//*2003/08/28*/
		TYPE_EXT_FLOOD_FILL,
        /*! EMR_LINETOの識別子 */
        TYPE_LINE_TO = 0x36,
		/*! EMR_ARCTOの識別子*//*2003/08/28*/
		TYPE_ARC_TO,
		/*! EMR_POLYDRAWの識別子*//*2003/08/28*/
		TYPE_POLY_DRAW,
		/*! EMR_SETARCDIRECTIONの識別子*//*2003/08/28*/
		TYPE_SET_ARC_DIRECTION,
        /*! EMR_SETMITERLIMITの識別子 */
        TYPE_SET_MITER_LIMIT = 0x3A,
        /*! EMR_BEGINPATHの識別子 */
        TYPE_BEGIN_PATH,
        /*! EMR_ENDPATHの識別子 */
        TYPE_END_PATH,
        /*! EMR_CLOSEFIGUREの識別子 */
        TYPE_CLOSE_FIGURE,
        /*! EMR_FILLPATHの識別子 */
        TYPE_FILL_PATH,
		/*! EMR_STROKEANDFILLPATHの識別子*//*2003/08/28*/
		TYPE_STROKE_AND_FILL_PATH,
        /*! EMR_STROKEPATHの識別子 */
        TYPE_STROKE_PATH = 0x40,
		/*! EMR_FLATTENPATHの識別子*//*2003/08/28*/
		TYPE_FLATTEN_PATH,
		/*! EMR_WIDENPATHの識別子*//*2003/08/28*/
		TYPE_WIDEN_PATH,
        /*! EMR_SELECTCLIPPATHの識別子 */
        TYPE_SELECT_CLIP_PATH = 0x43,
		/*! EMR_ABORTPATHの識別子*//*2003/08/28*/
		TYPE_ABORT_PATH =0x44,
		/* 0x45 はない*/
        /*! EMR_GDICOMMENTの識別子 */
        TYPE_GDI_COMMENT = 0x46,
		/*! EMR_FILLRGNの識別子*//*2003/08/28*/
		TYPE_FILL_RGN,
		/*! EMR_FRAMERGNの識別子*//*2003/08/28*/
		TYPE_FRAME_RGN,
		/*! EMR_INVERTRGNの識別子*//*2003/08/28*/
		TYPE_INVERT_RGN,
		/*! EMR_PAINTRGNの識別子*//*2003/08/28*/
		TYPE_PAINT_RGN,
		/*! EMR_EXTSELECTCLIPRGNの識別子*//*2002/12/11 For OLE*/
		TYPE_EXT_SELECT_CLIP_RGN = 0x4B,
        /*! EMR_BITBLTの識別子 */
        TYPE_BIT_BLT = 0x4C,
		/*! EMR_STRETCHBLTの識別子*//*2003/08/28*/
		TYPE_STRETCH_BLT,
        /*! EMR_MASKBLTの識別子 */
        TYPE_MASK_BLT = 0x4E,
		/*! EMR_PLGBLTの識別子*//*2003/08/28*/
		TYPE_PLG_BLT,
		/*! EMR_SETDIBITSTODEVICEの識別子*//*2003/08/28*/
		TYPE_SET_DIBITS_TO_DEVICE,
        /*! EMR_STRETCHDIBITSの識別子 */
        TYPE_STRETCH_DIB = 0x51,
        /*! EMR_EXTCREATEFONTINDIRECTWの識別子 */
        TYPE_EXT_CREATE_FONT_INDIRECT_W,
        /*! EMR_EXTTEXTOUTAの識別子 */
        TYPE_EXT_TEXT_OUT_A,
        /*! EMR_EXTTEXTOUTWの識別子 *//*2003/08/28*/
        TYPE_EXT_TEXT_OUT_W,
        /*! EMR_POLYBEZIER16の識別子 */
        TYPE_POLY_BEZIER_16 = 0x55,
        /*! EMR_POLYGON16の識別子 */
        TYPE_POLYGON_16,
        /*! EMR_POLYLINE16の識別子 */
        TYPE_POLYLINE_16,
        /*! EMR_POLYBEZIERTO16の識別子 */
        TYPE_POLY_BEZIER_TO_16,
        /*! EMR_POLYLINETO16の識別子 */
        TYPE_POLYLINE_TO_16,
        /*! EMR_POLYPOLYLINE16の識別子 *//*2003/08/28*/
        TYPE_POLYPOLYLINE_16,
        /*! EMR_POLYPOLYGON16の識別子 *//*2003/08/28*/
        TYPE_POLYPOLYGON_16,
        /*! EMR_POLYDRAW16の識別子 *//*2003/08/28*/
        TYPE_POLYDRAW_16,
        /*! EMR_CREATEMONOBRUSHの識別子 *//*2003/08/28*/
        TYPE_CREATE_MONO_BRUSH,
        /*! EMR_CREATEDIBPATTERNBRUSHPTの識別子 */
        TYPE_CREATE_DIB_PATTERN_BRUSH_PT = 0x5E,
        /*! EMR_EXTCREATEPENの識別子 */
        TYPE_EXT_CREATE_PEN =0x5F,
		/* EMR_EXTCREATEPENの識別子 */
		TYPE_EXTCREATEPEN,
		/* EMR_POLYTEXTOUTAの識別子 */
		TYPE_POLYTEXTOUTA,
		/* EMR_POLYTEXTOUTWの識別子 */
		TYPE_POLYTEXTOUTW,

		//version 4.0 later
		/* EMR_SETICMMODEの識別子 */
		TYPE_SETICMMODE,
		/* EMR_CREATECOLORSPACEの識別子 */
		TYPE_CREATECOLORSPACE,
		/* EMR_SETCOLORSPACEの識別子 */
		TYPE_SETCOLORSPACE,
		/* EMR_DELETECOLORSPACEの識別子 */
		TYPE_DELETECOLORSPACE,
		/* EMR_GLSRECORDの識別子 */
		TYPE_GLSRECORD,
		/* EMR_GLSBOUNDEDRECORDの識別子 */
		TYPE_GLSBOUNDEDRECORD,
		/* EMR_PIXELFORMATの識別子 */
		TYPE_PIXELFORMAT,
		
		//version 5.0 later
		/* EMR_DRAWESCAPEの識別子 */
		TYPE_DRAWESCAPE,
		/* EMR_EXTESCAPEの識別子 */
		TYPE_EXTESCAPE,
		/* EMR_STARTDOCの識別子 */
		TYPE_STARTDOC,
		/* EMR_SMALLTEXTOUTの識別子 */
		TYPE_SMALLTEXTOUT,
		/* EMR_FORCEUFIMAPPINGの識別子 */
		TYPE_FORCEUFIMAPPING,
		/* EMR_NAMEDESCAPEの識別子 */
		TYPE_NAMEDESCAPE,
		/* EMR_COLORCORRECTPALETTEの識別子 */
		TYPE_COLORCORRECTPALETTE,
		/* EMR_SETICMPROFILEAの識別子 */
		TYPE_SETICMPROFILEA,
		/* EMR_SETICMPROFILEWの識別子 */
		TYPE_SETICMPROFILEW,
		/* EMR_ALPHABLENDの識別子 */
		TYPE_ALPHABLEND,
		/* EMR_ALPHADIBBLENDの識別子 */
		TYPE_ALPHADIBBLEND,
		/* EMR_TRANSPARENTBLTの識別子 */
		TYPE_TRANSPARENTBLT,
		/* EMR_TRANSPARENTDIBの識別子 */
		TYPE_TRANSPARENTDIB,
		/* EMR_GRADIENTFILLの識別子 */
		TYPE_GRADIENTFILL,
		/* EMR_SETLINKEDUFISの識別子 */
		TYPE_SETLINKEDUFIS,
		/* EMR_SETTEXTJUSTIFICATIONの識別子 */
		TYPE_SETTEXTJUSTIFICATION,

    };
    
    /********************************************/
    /* クラス */

    /*! 規定クラス */
    class Record;

    /*! 描画オブジェクトの汎化クラス */
    class ObjectRecord;
    /*! ラスターパターンを扱う描画オブジェクトの汎化クラス */
    class RasterObjectRecord;
    /*! 単一の座標を扱う汎化クラス */
    class PointRecord;
    /*! 単一の矩形を圧かつ汎化クラス */
    class RectRecord;
    /*! 単一のモードを扱う汎化クラス */
    class ModeRecord;
    /*! ラスターを扱う汎化クラス */
    class RasterRecord;
    /*! 単一色を扱う汎化クラス */
    class ColorRecord;
    /*! 座標配列を扱う汎化クラス */ 
    class PolyRecord;

    /*! ヘッダ */
    class HeaderRecord;
    /*! PolyBezier */
    class PolyBezierRecord;
    /*! Polygon */
    class PolygonRecord;
    /*! Polyline */
    class PolylineRecord;
    /*! SetWindowsOrgEx */
    class SetWindowOrgExRecord;
    /*! SetBrushOrgEx */
    class SetBrushOrgExRecord;
    /*! EOF */
    class EndOfFileRecord;
    /*! SetBKMode */
    class SetBKModeRecord;
    /*! SetPolyFillMode */
    class SetPolyFillModeRecord;
    /*! SetROP2 */
    class SetROP2Record;
    /*! SetStretchBltMode */
    class SetStretchBltModeRecord;
    /*! SetTextAlign */
    class SetTextAlignRecord;
    /*! SetTextColor */
    class SetTextColorRecord;
    /*! SetBKColor */
    class SetBKColorRecord;
    /*! MoveToEx */
    class MoveToExRecord;
    /*! CreateBrushIndirect */
    class CreateBrushIndirectRecord;
    /*! Rectangle */
    class RectangleRecord;
    /*! LineTo */
    class LineToRecord;
    /*! SetMiterLimit */
    class SetMiterLimitRecord;
    /*! SelectClipPath */
    class SelectClipPathRecord;
    /*! BitBlt */
    class BitBltRecord;
    /*! MaskBlt */
    class MaskBltRecord;
    /*! StretchDIBits */
    class StretchDIBitsRecord;
    /*! ExtCreateFontIndirectW */
    class ExtCreateFontIndirectWRecord;
    /*! ExtTextOutA */
    class ExtTextOutRecord;
    /*! CreateDIBPatternBrushPt */
    class CreateDIBPatternBrushPTRecord;
    /*! ExtCreatePen */
    class ExtCreatePenRecord;

	/******************/
	/*以下 OLE Annotationでのみ出現するメタレコード*/
	/*コメントアウトしてあるものが実装済み*/
    /*DocuWorks標準付属のOLEアノテーション出現レコードはすべて実装済み*/

	/* 描画属性管理*/

	/*! CreatePen*/
	class CreatePenRecord;

	// CreateDIBPatternBrushPTRecordで代用
	//class CreateMonoBrushIndirectRecord;
	/*! SetArcDirection*/
	class SetArcDirectionRecord;

	/*座標変換*/
	class ScaleRecord;
    /*! SetMapMode*/
	class SetMapModeRecord;
	/*! SetViewPortExtEx*/
	class SetViewPortExtExRecord;
	/*! SetViewPortOrgEx*/
	class SetViewPortOrgExRecord;
	/*! SetWindowExtEx*/
	class SetWindowExtExRecord;
	/*! ScaleViewportExtEx*/
	class ScaleViewportExtRecord;
	/*! ScaleWindowExtEx*/
	class ScaleWindowExtExRecord;
	/*! SetWorldTransForm*/
//未出現：定義済	class SetWorldTransFormRecord;
	/*! ModifyWorldTransForm*/
//未出現：定義済	class ModifyWorldTransFormRecord;

	/*リージョン*/
	/* 出現しない?*/
	/*! FillRgn*/
//未出現：定義済	class FillRgnRecord;
	/*! FrameRgn*/
//未出現：定義済	class FrameRgnRecord;
	/*! InvertRgn*/
//未出現：定義済	class InvertRgnRecord;
	/*! PaintRgn*/
//未出現：定義済	class PaintRgnRecord;
//	040128 クラスとして定義しない：class SetMetaRgnRecord;
	/*! OffsetClipRgn*/
//未出現：定義済	class OffsetClipRgnRecord;

	/*パレット*/
    /*! CreatePalette*/
	class CreatePaletteRecord;
    /*! RealizePalette*/
	class RealizePaletteRecord;		
	/*! ResizePalette*/ 
	class ResizePaletteRecord;
	/*! SetPaletteentries*/
//未出現：定義済	class SetPaletteEntriesRecord;
     
	/* クリップ*/
    
	/*! IntersectClipRect*/
    class IntersectClipRectRecord;
	/*! ExcludeClipRect*/
	class ExcludeClipRectRecord;
	/*! SelectClipRgn*/
	class ExtSelectClipRgnRecord;

	/*図形*/
	
	/*! Ellipse*/
	class EllipseRecord;
	/*! PolyPolygonとPolyPolygon16を兼務*/
	class PolyPolygonRecord;//class PolyPolygon16Record;
	/*! Pie*/
	class PieRecord;
	/*! PolyDraw*/
//未出現：定義済	class PolyDrawRecord;// PolyDrawで代用	class PolyDraw16Record;
	/*! PolyPolyline*/
	class PolyPolylineRecord;//PolyPolylineで代用	class PolyPolyLine16Record;
	/*! SetPixelv*/
//未出現：定義済	class SetPixelvRecord;
	/*! AngleArc*/
//未出現：定義済	class AngleArcRecord;
	/*! Arc*/
	class ArcRecord;
	/*! ArcTo*/
//未出現：定義済	class ArcToRecord;
	/*! Chord*/
//未出現：定義済	class ChordRecord;
	/*! ExtFloodfill*/
//未出現：定義済	class ExtFloodFillRecord;
	/*! RoundRect*/
	class RoundRectRecord;

	/*パス*/

//040128 クラスとして定義しない：	class AbortPathRecord;
//040128 クラスとして定義しない：	class FlattenPathRecord;
//	class StrokeAndFillPathRecord;
//040128 クラスとして定義しない：	class WideNPathRecord;

	/*イメージ*/

//	class PlgBltRecord;
//	class SetDibitsToDeviceRecord;
	/*! StretchBlt*/
	class StretchBltRecord;
	/*文字*/
// 040130:ExtTextOutRecrodで代用	class ExtTextOutWRecord;
//	class PolyTextOutARecord;
//	class PolyTextOutWRecord;
	/*! SetMapperFlags*/
//未出現：定義済	class SetMapperFlagsRecord;
	
	/*カラーマッチング*/

//	class CreateColorSpaceRecord;
//	class DeleteColorSpaceRecord;
//  class SetColorAdjustmentRecord;
//	class SetColorSpaceRecord;
//	class SetIcmModeRecord;


	/*その他*/

//	class GlsBoundedRecordRecord;
//	class GlsRecordRecord;
//	class PixelFormatRecord;


};

#endif
