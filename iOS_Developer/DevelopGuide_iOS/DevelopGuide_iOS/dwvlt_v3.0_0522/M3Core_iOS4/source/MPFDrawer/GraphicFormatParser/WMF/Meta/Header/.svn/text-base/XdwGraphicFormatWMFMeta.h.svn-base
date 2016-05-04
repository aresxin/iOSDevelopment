/**
 * @file  XdwGraphicFormatWMFMeta.h
 * @brief XdwGraphicFormat::WMF::Metaクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMeta.h,v 1.4 2009/12/22 08:10:48 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_WMF_META_H_
#define _XDW_GRAPHIC_FORMAT_WMF_META_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "GraphicFormatParser/WMF/Header/XdwGraphicFormatWMF.h"

/**
 * @brief WMFのレコードを管理するパッケージ
 */
class XdwGraphicFormat::WMF::Meta
{
public:

    /********************************************/
    /* 列挙型 */
    
    /*! DocuWorksファイル中のWMFのレコードの識別子 */
    enum TypeID{
        /*! META_SETBKCOLORの識別子 */
        TYPE_SET_BK_COLOR  = 0x0201,
        /*! META_SETBKMODEの識別子 */
        TYPE_SET_BK_MODE  = 0x0102,
        /*! META_SETMAPMODEの識別子 */
        TYPE_SET_MAP_MODE  = 0x0103,
        /*! META_SETROP2の識別子 */
        TYPE_SET_ROP2  = 0x0104,
        /*! META_SETRELABSの識別子 */
        TYPE_SET_RELABS  = 0x0105,
        /*! META_SETPOLYFILLMODEの識別子 */
        TYPE_SET_POLY_FILL_MODE  = 0x0106,
        /*! META_SETSTRETCHBLTMODEの識別子 */
        TYPE_SET_STRETCH_BLT_MODE  = 0x0107,
        /*! META_SETTEXTCHAREXTRAの識別子 */
        TYPE_SET_TEXT_CHAR_EXTRA  = 0x0108,
        /*! META_SETTEXTCOLORの識別子 */
        TYPE_SET_TEXT_COLOR  = 0x0209,
        /*! META_SETTEXTJUSTIFICATIONの識別子 */
        TYPE_SET_TEXT_JUSTIFICATION  = 0x020A,
        /*! META_SETWINDOWORGの識別子 */
        TYPE_SET_WINDOW_ORG  = 0x020B,
        /*! META_SETWINDOWEXTの識別子 */
        TYPE_SET_WINDOW_EXT  = 0x020C,
        /*! META_SETVIEWPORTORGの識別子 */
        TYPE_SET_VIEWPORT_ORG  = 0x020D,
        /*! META_SETVIEWPORTEXTの識別子 */
        TYPE_SET_VIEWPORT_EXT  = 0x020E,
        /*! META_OFFSETWINDOWORGの識別子 */
        TYPE_OFFSET_WINDOW_ORG  = 0x020F,
        /*! META_SCALEWINDOWEXTの識別子 */
        TYPE_SCALE_WINDOW_EXT  = 0x0410,
        /*! META_OFFSETVIEWPORTORGの識別子 */
        TYPE_OFFSET_VIEWPORT_ORG  = 0x0211,
        /*! META_SCALEVIEWPORTEXTの識別子 */
        TYPE_SCALE_VIEWPORT_EXT  = 0x0412,
        /*! META_LINETOの識別子 */
        TYPE_LINE_TO  = 0x0213,
        /*! META_MOVETOの識別子 */
        TYPE_MOVE_TO  = 0x0214,
        /*! META_EXCLUDECLIPRECTの識別子 */
        TYPE_EXCLUDE_CLIP_RECT  = 0x0415,
        /*! META_INTERSECTCLIPRECTの識別子 */
        TYPE_INTERSECT_CLIP_RECT  = 0x0416,
        /*! META_ARCの識別子 */
        TYPE_ARC  = 0x0817,
        /*! META_ELLIPSEの識別子 */
        TYPE_ELLIPSE  = 0x0418,
        /*! META_FLOODFILLの識別子 */
        TYPE_FLOOD_FILL  = 0x0419,
        /*! META_PIEの識別子 */
        TYPE_PIE  = 0x081A,
        /*! META_RECTANGLEの識別子 */
        TYPE_RECTANGLE  = 0x041B,
        /*! META_ROUNDRECTの識別子 */
        TYPE_ROUND_RECT  = 0x061C,
        /*! META_PATBLTの識別子 */
        TYPE_PAT_BLT  = 0x061D,
        /*! META_SAVEDCの識別子 */
        TYPE_SAVE_DC  = 0x001E,
        /*! META_SETPIXELの識別子 */
        TYPE_SET_PIXEL  = 0x041F,
        /*! META_OFFSETCLIPRGNの識別子 */
        TYPE_OFFSET_CLIP_RGN  = 0x0220,
        /*! META_TEXTOUTの識別子 */
        TYPE_TEXT_OUT  = 0x0521,
        /*! META_BITBLTの識別子 */
        TYPE_BIT_BLT  = 0x0922,
        /*! META_STRETCHBLTの識別子 */
        TYPE_STRETCH_BLT  = 0x0B23,
        /*! META_POLYGONの識別子 */
        TYPE_POLYGON  = 0x0324,
        /*! META_POLYLINEの識別子 */
        TYPE_POLYLINE  = 0x0325,
        /*! META_ESCAPEの識別子 */
        TYPE_ESCAPE  = 0x0626,
        /*! META_RESTOREDCの識別子 */
        TYPE_RESTORE_DC  = 0x0127,
        /*! META_FILLREGIONの識別子 */
        TYPE_FILL_REGION  = 0x0228,
        /*! META_FRAMEREGIONの識別子 */
        TYPE_FRAME_REGION  = 0x0429,
        /*! META_INVERTREGIONの識別子 */
        TYPE_INVERT_REGION  = 0x012A,
        /*! META_PAINTREGIONの識別子 */
        TYPE_PAINT_REGION  = 0x012B,
        /*! META_SELECTCLIPREGIONの識別子 */
        TYPE_SELECT_CLIP_REGION  = 0x012C,
        /*! META_SELECTOBJECTの識別子 */
        TYPE_SELECT_OBJECT  = 0x012D,
        /*! META_SETTEXTALIGNの識別子 */
        TYPE_SET_TEXT_ALIGN  = 0x012E,
        /*! META_CHORDの識別子 */
        TYPE_CHORD  = 0x0830,
        /*! META_SETMAPPERFLAGSの識別子 */
        TYPE_SET_MAPPER_FLAGS  = 0x0231,
        /*! META_EXTTEXTOUTの識別子 */
        TYPE_EXT_TEXT_OUT  = 0x0A32,
        /*! META_SETDIBTODEVの識別子 */
        TYPE_SET_DIB_TO_DEV  = 0x0D33,
        /*! META_SELECTPALETTEの識別子 */
        TYPE_SELECT_PALETTE  = 0x0234,
        /*! META_REALIZEPALETTEの識別子 */
        TYPE_REALIZE_PALETTE  = 0x0035,
        /*! META_ANIMATEPALETTEの識別子 */
        TYPE_ANIMATE_PALETTE  = 0x0436,
        /*! META_SETPALENTRIESの識別子 */
        TYPE_SET_PAL_ENTRIES  = 0x0037,
        /*! META_POLYPOLYGONの識別子 */
        TYPE_POL_YPOLYGON  = 0x0538,
        /*! META_RESIZEPALETTEの識別子 */
        TYPE_RESIZE_PALETTE  = 0x0139,
        /*! META_DIBBITBLTの識別子 */
        TYPE_DIB_BIT_BLT  = 0x0940,
        /*! META_DIBSTRETCHBLTの識別子 */
        TYPE_DIB_STRETCH_BLT  = 0x0B41,
        /*! META_DIBCREATEPATTERNBRUSHの識別子 */
        TYPE_DIB_CREATE_PATTERN_BRUSH  = 0x0142,
        /*! META_STRETCHDIBの識別子 */
        TYPE_STRETCH_DIB  = 0x0F43,
        /*! META_EXTFLOODFILLの識別子 */
        TYPE_EXT_FLOOD_FILL  = 0x0548,
        /*! META_DELETEOBJECTの識別子 */
        TYPE_DELETE_OBJECT  = 0x01F0,
        /*! META_CREATEPALETTEの識別子 */
        TYPE_CREATE_PALETTE  = 0x00F7,
        /*! META_CREATEPATTERNBRUSHの識別子 */
        TYPE_CREATE_PATTERN_BRUSH  = 0x01F9,
        /*! META_CREATEPENINDIRECTの識別子 */
        TYPE_CREATE_PEN_INDIRECT  = 0x02FA,
        /*! META_CREATEFONTINDIRECTの識別子 */
        TYPE_CREATE_FONT_INDIRECT  = 0x02FB,
        /*! META_CREATEBRUSHINDIRECTの識別子 */
        TYPE_CREATE_BRUSH_INDIRECT  = 0x02FC,
        /*! META_CREATEREGIONの識別子 */
        TYPE_CREATE_REGION  = 0x06FF,
        /*! 終了コード */
        TYPE_END = 0x0000
    };
    
    /********************************************/
    /* クラス */

    /*! 規定クラス */
    class Record;

    /*! 座標を表す汎化クラス */
    class PointRecord;
    /*! サイズを表す汎化クラス */
    class SizeRecord;
    /*! 倍率を表す汎化クラス */
    class ScaleRecord;
    /*! 矩形を表す汎化クラス */
    class RectRecord;
    /*! 円弧を表す汎化クラス */
    class CurveRecord;
    /*! 描画オブジェクトを表す汎化クラス */
    class ObjectRecord;
    /*! 色を表す汎化クラス */
    class ColorRecord;
    /*! 描画属性を表す汎化クラス */
    class ModeRecord;
    /*! 複数の座標を表す汎化クラス */
    class PolyRecord;
    /*! ラスターを表す汎化クラス */
    class RasterRecord;
    /*! Mapモード属性を表すクラス*/
	class SetMapModeRecord;
    /*! 描画オブジェクトのハンドルを管理するクラス */
    class Object;
    /*! パレットオブジェクトのハンドルを管理するクラス */
    class PaletteObject;
    /*! 描画オブジェクトを空にするクラス */
    class NullObject;
    
    /*! ヘッダ */
    class Header;
    /*! SetBkColor */
    class SetBKColorRecord;
    /*! SetBkMode */
    class SetBKModeRecord;
    /*! SetROP2 */
    class SetROP2Record;
    /*! SetPolyFillMode */
    class SetPolyFillModeRecord;
    /*! SetStretchBltMode */
    class SetStretchBltModeRecord;
    /*! SetTextCharExtra */
    class SetTextCharExtraRecord;
    /*! SetTextColor */
    class SetTextColorRecord;
    /*! SetTextJustification */
    class SetTextJustificationRecord;
    /*! SetWindowOrg */
    class SetWindowOrgRecord;
    /*! SetWindowExt */
    class SetWindowExtRecord;
    /*! SetViewportOrg */
    class SetViewportOrgRecord;
    /*! SetViewportExt */
    class SetViewportExtRecord;
    /*! ScaleWindowExt */
    class ScaleWindowExtRecord;
    /*! ScaleViewportExt */
    class ScaleViewportExtRecord;
    /*! LineTo */
    class LineToRecord;
    /*! MoveTo */
    class MoveToRecord;
    /*! IntersectClipRect */
    class IntersectClipRectRecord;
    /*! Arc */
    class ArcRecord;
    /*! Ellipse */
    class EllipseRecord;
    /*! Pie */
    class PieRecord;
    /*! Rectangle */
    class RectangleRecord;
    /*! RoundRect */
    class RoundRectRecord;
    /*! ParBlt */
    class PatBltRecord;
    /*! SaveDC */
    class SaveDCRecord;
    /*! SetPixel */
    class SetPixelRecord;
    /*! Polygon */
    class PolygonRecord;
    /*! PolylineRecord */
    class PolylineRecord;
    /*! RestoreDC */
    class RestoreDCRecord;
    /*! SetTextAlign */
    class SetTextAlignRecord;
    /*! Chord */
    class ChordRecord;
    /*! ExtTextOut */
    class ExtTextOutRecord;
    /*! RealizePalette */
    class RealizePaletteRecord;
    /*! DIBBitBlt */
    class DIBBitBltRecord;
    /*! DIBStretchBlt */
    class DIBStretchBltRecord;
    /*! DIBCreatePatternBrush */
    class DIBCreatePatternBrushRecord;
    /*! StretchDIB */
    class StretchDIBRecord;
    /*! CreatePalette */
    class CreatePaletteRecord;
    /*! CreatePenIndirect */
    class CreatePenIndirectRecord;
    /*! CreateFontIndirect */
    class CreateFontIndirectRecord;
    /*! CreateBrushIndirect */
    class CreateBrushIndirectRecord;
    /*! CreateRegion */
    class CreateRegionRecord;
	/*! TextOut*/
	class TextOutRecord; /*AR11957*/
};

#endif
