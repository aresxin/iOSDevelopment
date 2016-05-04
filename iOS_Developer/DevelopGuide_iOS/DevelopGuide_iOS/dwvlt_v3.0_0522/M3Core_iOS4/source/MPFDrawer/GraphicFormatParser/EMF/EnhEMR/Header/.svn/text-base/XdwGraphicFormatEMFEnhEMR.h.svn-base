/**
 * @file  XdwGraphicFormatEMFEnhEMR.h
 * @brief XdwGraphicFormat::EMF::EnhEMRクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwGraphicFormatEMFEnhEMR.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_EMF_ENH_EMR_H_
#define _XDW_GRAPHIC_FORMAT_EMF_ENH_EMR_H_

/* 本パッケージの上位パッケージのIncludeファイル */
#include "GraphicFormatParser/EMF/Header/XdwGraphicFormatEMF.h"

/**
 * @brief DocuWorks独自の拡張されたEMFのレコードを管理するパッケージ
 */
class XdwGraphicFormat::EMF::EnhEMR
{
public:

    /********************************************/
    /* 列挙型 */
    
    /*! DocuWorks独自の拡張されたEMRの識別子の定義 */
    enum TypeID{
        /*! 拡張されたEMRの共通した識別子 */    
        TYPE_MASK = 0x00005744,
        /*! 複雑なクリッピングの識別子 */
        TYPE_COMPLEX_CLIP  = 0x31305744,
        /*! BeginPathの識別子 */
        TYPE_BEGIN_PATH = 0x32305744,
        /*! EndPath + SelectClipPathの識別子 */
        TYPE_END_PATH_SELECT_CLIP_PATH = 0x33305744,
        /*! EndPath + FillPathの識別子 */
        TYPE_END_PATH_FILL_PATH = 0x34305744,
        /*! EndPath + StrokePathの識別子 */
        TYPE_END_PATH_STROKE_PATH = 0x35305744,
        /*! 矩形でのクリッピング */
        TYPE_RECT_CLIP  = 0x36305744,
        /*! PolylineToの識別子 */
        TYPE_POLYLINE_TO = 0x00005744,
        /*! MoveToEx + PolylineToの識別子 */
        TYPE_MOVE_TO_EX_POLYLINE_TO = 0x00015744,
        /*! PolylineTo + CloseFigureの識別子 */
        TYPE_POLYLINE_TO_CLOSE_FIGURE = 0x00025744,
        /*! MoveToEx + PolylineTo + CloseFigureの識別子 */
        TYPE_MOVE_TO_EX_POLYLINE_TO_CLOSE_FIGURE = 0x00035744,
        /*! PolyBezierToの識別子 */
        TYPE_POLY_BEZIER_TO = 0x00105744,
        /*! MoveToEx + PolyBezierToの識別子 */
        TYPE_MOVE_TO_POLY_BEZIER_TO = 0x00115744,
        /*! PolyBezierTo + CloseFigureの識別子 */
        TYPE_POLY_BEZIER_TO_CLOSE_FIGURE = 0x00125744,
        /*! MoveToEx + PolyBezierTo + CloseFigureの識別子 */
        TYPE_MOVE_TO_POLY_BEZIER_TO_CLOSE_FIGURE = 0x00135744,
        /*! Polygonの識別子 */
        TYPE_POLYGON = 0x00205744,
        /*! Polylineの識別子 */
        TYPE_POLYLINE = 0x00405744,
        /*! PolyBezierの識別子 */
        TYPE_POLY_BEZIER = 0x00505744,
        /*! 参照型DIBの識別子 */
        TYPE_SET_DIB = 0x00615744,
        /*! 参照型JPEGの識別子 */
        TYPE_SET_JPEG = 0x00625744,
        /*! 参照型ラスタの描画の識別子 */
        TYPE_STRETCH_DIB_REF = 0x00635744
    };
    
    /********************************************/
    /* クラス */
    
    /*! 指定された矩形をクリッピング領域とするクラス */
    class RectClipRecord;
    /*! 参照されるラスターデータを規定する汎化クラス */
    class SetRasterRecord;
    /*! 参照されるDIBを規定するクラス */
    class SetDIBRecord;
    /*! 参照されるJpegを規定するクラス */
    class SetJpegRecord;
    /*! ラスターデータを参照して、描画するクラス */
    class StretchDIBitsRefRecord;

};

#endif
