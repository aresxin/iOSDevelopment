// $Archive: EMRAnn.h $
//
// Copyright (c) 2011 Fuji Xerox Co.,  Ltd. All rights reserved.
//
// $Author: liuxu $
// $Date: 2011/03/31 08:16:28 $
// $Revision: 1.0 $

#ifndef EMF_ANN_H
#define EMF_ANN_H

#include "w2mpf_gdi_def.h"
#include "anparameter.h"
#include "EMFCore.h"
#include <cmath>

namespace EMFGenCom {

struct FontParam
{
	UTF16Text facename;
	int pitchAndFamily;
	int charset;
	int style;
	float size;
	float angle;
};

struct FormatText
{
	WCHAR* start;
	WCHAR* end;
	int currentLine;
	int x;
	int width;
	int charset;
	int pitchAndFamily;
	UTF16Text facename;
};

class EMFAnn
{
public:
	EMFAnn(int dpi);
	~EMFAnn();
	int MakeTextAnn(TextAnnotationParameter& textParam,  AnnEMFData& annEMF);
	int MakeFreehandAnn(FreehandAnnotationParameter& freehandParam,  AnnEMFData& annEMF);
	int MakeNotepadAnn(NotepadAnnotationParameter& notepadParam,  AnnEMFData& annEMF);
	int MakeLineAnn(LineAnnotationParameter& lineParam,  AnnEMFData& annEMF);
	int MakeRectangleAnn(RectangleAnnotationParameter& rectangleParam,  AnnEMFData& annEMF);
	int MakeEllipseAnn(EllipseAnnotationParameter& ellipseParam, AnnEMFData& annEMF);
	int MakePolygonAnn(PolygonAnnotationParameter& polygonParam,  AnnEMFData& annEMF);
	int MakeTextNotepadAnn(TextNotepadAnnotationParameter& textNotepadParam,  AnnEMFData& annEMF);
private:
	EMFAnn();
	EMFAnn(const EMFAnn&);
	EMFAnn& operator=(const EMFAnn&);

	int CreateTextFill(const MyArray<POINT>& points, COLORREF fill_color, EMFCore &emf_core);
	void SetFontParam(const TextAnnotationParameter& textParam, FontParam& fontParam);
	void HandleVerticalFont(bool vertical, FontParam& fontParam);
	int DrawTextLine(const TextAnnotationParameter& textParam, const FormatText& format,  const RECT& linerect, const POINT& offsetAxis, EMFCore& emf);
	int GetSpacing(float charsize, int text_length, const WCHAR *text, const WCHAR* facename, int pitchAndFamily, int charset, MyArray<int>& text_spacing);

	int CreateFreehand(const MyArray<POINT>& points, int thickness, COLORREF frame_color, bool is_permeable, EMFCore& emf_core);

	int CreateRectangleFill(const POINT* point, COLORREF fill_color, int frameThickness, bool is_permeable, EMFCore &emf_core);
	int CreateRectangleFrame(int width, int height, int frame_thickness, COLORREF frame_color, EMFCore &emf_core);

	int CreatePolygon(const MyArray<POINT>& points, int frame_thickness, COLORREF fill_color, COLORREF frame_color, bool is_fill, bool is_frame, bool is_permeable, EMFCore& emf_core);

	int CreateEllipse(int width, int height, int frame_thickness, COLORREF fill_color, COLORREF frame_color, bool is_fill, bool is_frame, bool is_permeable, EMFCore& emf_core);

	int CreateSolidLine(POINT startPoint, POINT endPoint, int thickness, COLORREF color, bool is_permeable, EMFCore& emf_core);
	int CreateDotLine(POINT startPoint, POINT endPoint, int thickness, COLORREF color, bool is_permeable, EMFCore& emf_core);
	int CreateDashLine(POINT startPoint, POINT endPoint, int thickness, COLORREF color, EMFCore& emf_core);
	int CreateDashdotLine(POINT startPoint, POINT endPoint, int thickness, COLORREF color, EMFCore& emf_core);
	int CreateDoubleLine(POINT startPoint, POINT endPoint, int thickness, COLORREF color, bool is_permeable, EMFCore& emf_core);
	int CreateArrow(const POINT* points, int arrow_style, int thickness, EMFCore& emf_core);
	int SetToolsForDashLine(int thickness, COLORREF color, EMFCore& emf_core);
	int SetToolsForSolidLine(COLORREF color, EMFCore& emf_core);
	int ResetToolsForDashLine(EMFCore& emf_core);
	int ResetToolsForSolidLine(EMFCore& emf_core);
	int GetPointsFromDotLine(POINT start_point, POINT end_point, int thickness, MyArray<POINT>& points);
	int GetInclusiveLineFromDashLine(POINT start_point, POINT end_point, int thickness, MyArray<POINT>&points);
	int GetInclusiveLineFromDashdotLine(POINT start_point, POINT end_point, int thickness, MyArray<POINT>& points);

	int GetRoundValue(double decimal_value);
	int SetPen(UINT pen_style, int lopn_width, COLORREF lopn_color, EMFCore &emf_core);
	int SetExtPen(int width, COLORREF color, EMFCore &emf_core);
	int SetBrush(COLORREF brush_color, EMFCore &emf_core);
	int SetFont(const FontParam& fontParam, EMFCore &emf_core);
	int ResetTools (EMFCore &emfCore, int handle_type);
	double Pt2Pixel(int pt, int dpi);
	COLORREF GetDensityColor(COLORREF color);
private:
	int m_dpi;//dpi
	enum StatusCode {
		kNOERROR							= 0x00000000, 				//処理成功
		kERRUNEXPECTED				= 0x8000FFFF, 				//予期せぬエラー
		kERRFILENOTFOUND			= 0x80070002, 				//指定パスのファイルが見つからない
		kERROUTOFMEMORY			= 0x8007000E, 				//メモリの獲得に失敗した
		kERRINVALIDARG					= 0x80070057				//引数の異常
	};

	enum {
		WHITE_BRUSH_ID     = 0x80000000,
		NULL_BRUSH_ID      = 0x80000005,
		BLACK_PEN_ID       = 0x80000007,
		NULL_PEN_ID        = 0x80000008,
		SYSTEM_FONT_ID     = 0x8000000d,
		DEFAULT_PALETTE_ID = 0x8000000f,
	};
};

}
#endif //EMF_ANN_H
// $History: EMRAnn.h $
//
// *****************  Version 1.0  *****************
// User: liuxu       Date: 11/03/31   Time: 08:16