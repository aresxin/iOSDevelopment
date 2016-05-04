// $Archive: EMRCore.h $
//
// Copyright (c) 2011 Fuji Xerox Co.,  Ltd. All rights reserved.
//
// $Author: liuxu $
// $Date: 2011/03/31 08:16:28 $
// $Revision: 1.0 $
#ifndef EMF_CORE_H
#define EMF_CORE_H

#include "EMRDef.h"
#include "DC.h"
#include "listimpl.h"

namespace EMFGenCom {

class AnnEMFData
{
public:
	AnnEMFData();
	~AnnEMFData();
public:
	int m_width;
	int m_height;
	DWORD m_EMFSize;
	BYTE* m_EMFData;
};

typedef MyList<EMR*> EMRList;

class EMFCore
{
public:
	EMFCore(int width, int height, int density);
	EMFCore(int width, int height, const RECT &rclBounds, int density);
	~EMFCore();
	int StartOfEMF();
	int EndOfEMF(DWORD palentries, DWORD off_palentries);
	int SetWindowExtEx(int width = 0, int height = 0);
	int SetWindowOrgEx(int x, int y);
	int SelectObject(DWORD ih_object);
	int DeleteObject(DWORD ih_object);
	int SelectPalette(DWORD ih_pal);
	int CreatePen(UINT lopn_style, int lopn_width, COLORREF lopn_color, DWORD &ih_pen);
	int CreateBrushIndirect(UINT lb_style, COLORREF lb_color, DWORD lb_hatch, DWORD &ih_brush);
	int CreatePalette(WORD pal_num_entries, const PALETTEENTRY *pal_entry, DWORD &ih_palette);
	int ExtCreateFontIndirectW(LogFontEx logical_font_ex, DWORD num_axes, int *axes_values, DWORD &ih_fonts);
	int ExtCreatePen(LogPenEx logical_pen_ex, DWORD num_style_entries, const DWORD *style_entry, DIBPosition dib_pos, const BYTE *bitmap_buffer, DWORD &ih_pen);
	int SetMiterLimit(DWORD miter_limit);
	int SetPolyFillMode(DWORD mode);
	int SetRop2(DWORD mode);
	int SetStretchBltMode(DWORD mode);
	int SetTextAlign(DWORD mode);
	int SetTextColor(COLORREF color);
	int SetLayout(DWORD mode);
	int SetBrushOrgEx(POINT origin);
	int SetBkMode(DWORD mode);
	int SetBkColor(COLORREF color);
	int RestoreDC(int relative);
	int SaveDC();
	int RealizePalette();
	int MovetoEx(POINT point);
	int BeginPath();
	int EndPath();
	int Ellipse(int left, int top, int right, int bottom);
	int Ellipse(RECT box);
	int ExtTextoutW(DWORD graphics_mode, FLOAT x_scale, FLOAT y_scale, POINT ref_position, DWORD num_chars, DWORD options, RECT rectangle, const WCHAR *text, const int* dx);
	int LineTo(POINT point);
	int Polygon16(DWORD num_points, const POINT* point);
	int Polygon16(DWORD num_points, const POINTS* points);
	int Rectangle(RECT rectangle_box);
	int StrokePath(RECT stroke_path_box);
	int GDIComment(DWORD data_size, const BYTE *private_data);
	int IntersectClipRect(int left, int top, int right, int bottom);
	int SetMetargn();
	int BitBlt(RECT bounds, DestinationRect dest_rect, DWORD dwrop, POINT src, XFORM xform_src, COLORREF back_color_src, DWORD usage_src, DIBPosition dib_pos_src, const BYTE *bitmap_buffer);
	int GetHandleList(int *handle_cnt, Handle **handle_list);
	int CreateAnnEMFData(AnnEMFData &annEMF);
	SIZE GetWindowExtent();
	bool IsShortPoint(int num, const POINT* point);
private:
	void GetBoundsOfPoints(RECT &bounds, DWORD num_points, const POINTS *points);
private:
	EMFCore();
	EMFCore(const EMFCore&);
	EMFCore& operator=(const EMFCore&);
private:
	DC *m_dc;
	EMRList m_emrList;
	enum StatusCode {
		kNOERROR							= 0x00000000, 				//処理成功
		kERRUNEXPECTED				= 0x8000FFFF, 				//予期せぬエラー
		kERRFILENOTFOUND			= 0x80070002, 				//指定パスのファイルが見つからない
		kERROUTOFMEMORY			= 0x8007000E, 				//メモリの獲得に失敗した
		kERRINVALIDARG					= 0x80070057				//引数の異常
	};
};

}
#endif //EMF_CORE_H
// $History: EMFCore.h $
//
// *****************  Version 1.0  *****************
// User: liuxu       Date: 11/03/31   Time: 08:16