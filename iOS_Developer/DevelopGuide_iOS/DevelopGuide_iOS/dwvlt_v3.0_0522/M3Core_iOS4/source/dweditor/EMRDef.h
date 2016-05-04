// $Archive: EMRDef.h $
//
// Copyright (c) 2011 Fuji Xerox Co., Ltd. All rights reserved.
//
// $Author: liuxu $
// $Date: 2011/03/31 08:15:28 $
// $Revision: 1.0 $

#ifndef EMR_DEF_H
#define EMR_DEF_H

#include "DC.h"

namespace EMFGenCom {

DWORD GetByteRound(DWORD byte_size);
DWORD GetWordRound(DWORD word_size);

enum StatusCode {
	kNOERROR							= 0x00000000, 				//処理成功
	kERRUNEXPECTED				= 0x8000FFFF, 				//予期せぬエラー
	kERRFILENOTFOUND			= 0x80070002, 				//指定パスのファイルが見つからない
	kERROUTOFMEMORY			= 0x8007000E, 				//メモリの獲得に失敗した
	kERRINVALIDARG					= 0x80070057				//引数の異常
};

struct LogPen {
	UINT								lopnStyle;
	POINT							lopnWidth;
	COLORREF					lopnColor;
};

struct LogBrush32 {
	UINT								lbStyle;
	COLORREF					lbColor;
	DWORD							lbHatch;
};

struct LogFont {
	int							lfHeight;
	int							lfWidth;
	int							lfEscapement;
	int							lfOrientation;
	int							lfWeight;
	BYTE								lfItalic;
	BYTE								lfUnderline;
	BYTE								lfStrikeOut;
	BYTE								lfCharSet;
	BYTE								lfOutPrecision;
	BYTE								lfClipPrecision;
	BYTE								lfQuality;
	BYTE								lfPitchAndFamily;
	WCHAR							lfFaceName[LF_FACESIZE];
};

struct LogFontEx {
	LogFont logFont;
	WCHAR							fullName[64];
	WCHAR							style[32];
	WCHAR							script[32];
};

struct LogPenEx {
	DWORD						elpPenStyle;
	DWORD						elpWidth;
	DWORD						elpBrushStyle;
	COLORREF					elpColor;
	DWORD						elpHatch;
};

struct DIBPosition {
	DWORD						offBmi;
	DWORD						cbBmi;
	DWORD						offBits;
	DWORD						cbBits;
};

struct TextInfo {
	POINT						ptlReference;
	DWORD						nChars;
	DWORD						offString;
	DWORD						fOptions;
	RECT						rcl;
	DWORD						offDx;
};

struct DestinationRect {
	int xDest;
	int yDest;
	int cxDest;
	int cyDest;
};

struct EMRInfo {
	DWORD iType;
	DWORD nSize;
};

struct EMRHeaderData {
	RECT rclBounds;//The rectangular inclusive-inclusive bounds in device units
	RECT rclFrame;//The rectangular inclusive-inclusive dimensions, in .01 millimeter units
	DWORD dSignature;
	DWORD nVersion;
	DWORD nBytes;
	DWORD nRecords;
	WORD nHandles;
	WORD sReserved;
	DWORD nDescription;
	DWORD offDescription;
	DWORD nPalEntries;
	SIZE szlDevice;
	SIZE szlMillimeters;//The size of the reference device, in millimeters.
	DWORD cbPixelFormat;
	DWORD offPixelFormat;
	DWORD bOpenGL;
	SIZE szlMicrometers;//The size of the display device for which the metafile image was generated, in micrometers.
};

struct EMREOFData {
	DWORD nPalEntries;
	DWORD offPalEntries;
	DWORD nSizeLast;
};

struct EMRSetWindowExtExData {
	SIZE szlExtent;
};

struct EMRSetWindowOrgExData {
	POINT ptlOrigin;
};

struct EMRSelectObjectData {
	DWORD ihObject;
};

struct EMRDeleteObjectData {
	DWORD ihObject;
};

struct EMRSelectPaletteData {
	DWORD ihPal;
};

struct EMRCreatePenData {
	DWORD ihPen;
	LogPen logicalPen;
};

struct EMRCreateBrushIndirectData {
	DWORD ihBrush;
	LogBrush32 logicalBrush;
};

struct EMRCreatePaletteData {
	DWORD ihPal;
	WORD palVersion;
	WORD palNumEntries;
};

struct EMRExtCreateFontIndirectWData {
	DWORD ihFonts;
	LogFontEx logFontEX;
	DWORD signature;
	DWORD numAxes;
};

struct EMRExtCreatePenData {
	DWORD ihPen;
	DIBPosition dibPosition;
	LogPenEx logicalPenEX;
	DWORD numEntries;
};

struct EMRSetMiterLimitData {
	DWORD eMiterLimit;
};

struct EMRSetPolyFillModeData {
	DWORD iMode;
};

struct EMRSetROP2Data {
	DWORD iMode;
};

struct EMRSetStretchBltModeData {
	DWORD iMode;
};

struct EMRSetTextAlignData {
	DWORD iMode;
};

struct EMRSetTextColorData {
	COLORREF crColor;
};

struct EMRSetLayoutData {
	DWORD iMode;
};

struct EMRSetBrushOrgEXData {
	POINT ptlOrigin;
};

struct EMRSetBKModeData {
	DWORD iMode;
};

struct EMRSetBKColorData {
	COLORREF crColor;
};

struct EMRRestoreDCData {
	int iRelative;
};

struct EMRMoveToEXData {
	POINT ptl;
};

struct EMREllipseData {
	RECT rclBox;
};

struct EMRExtTextOutWData {
	RECT rclBounds;
	DWORD iGraphicsMode;
	FLOAT exScale;
	FLOAT eyScale;
	TextInfo textInfo;
};

struct EMRLineToData {
	POINT ptl;
};

struct EMRPolygon16Data {
	RECT rclBounds;
	DWORD pointsCount;
};

struct EMRRectangleData {
	RECT rclBox;
};

struct EMRStrokePathData {
	RECT rclBounds;
};

struct EMRCommentData {
	DWORD nDataSize;
};

struct EMRIntersectClipRectData {
	RECT rclClip;
};

struct EMRBitBltData {
	RECT rclBounds;
	DestinationRect destRect;
	DWORD dwRop;
	POINT ptlSrc;
	XFORM xformSrc;
	COLORREF crBkColorSrc;
	DWORD iUsageSrc;
	DIBPosition dibPositionSrc;
};

/*
 * @brief:EMF base class
 *
 */
class EMR
{
public:
	EMR();
	virtual ~EMR();
	EMRInfo GetEMRInfo();
	BYTE *GetEMRData() const;
protected:
	virtual int SerializeData();
private:
	EMR(const EMR&);
	EMR& operator=(const EMR&);
public:
	EMRInfo m_emrInfo;
	BYTE *m_emrData;
};

class EMRHeader: public EMR
{
public:
	int Create(DC &dc);
	int Create(BYTE *emr_data);
	int SetRecords(DWORD records);
	int SetBytes(DWORD size);
	int SetHandles(WORD handles);
	DWORD GetBytes();
protected:
	int SerializeData();
private:
	EMRHeader& operator=(const EMRHeader&);
	int UnserializeData(BYTE *emr_data);
private:
	EMRHeaderData m_emrHeaderData;
};

class EMREOF: public EMR
{
public:
	int Create(DWORD palentries, DWORD off_palentries);
protected:
	int SerializeData();
private:
	EMREOF& operator=(const EMREOF&);
private:
	EMREOFData m_emrEOFData;
};

class EMRSetWindowExtEx: public EMR
{
public:
	int Create(SIZE extent);
protected:
	int SerializeData();
private:
	EMRSetWindowExtExData m_emrSetWindowExtExData;
};

class EMRSetWindowOrgEx: public EMR
{
public:
	int Create(POINT point);
protected:
	int SerializeData();
private:
	EMRSetWindowOrgExData m_emrSetWindowOrgExData;
};

class EMRSelectObject: public EMR
{
public:
	int Create(DWORD ih_object);
protected:
	int SerializeData();
private:
	EMRSelectObjectData m_emrSelectObjectData;
};

class EMRDeleteObject: public EMR
{
public:
	int Create(DWORD ih_object);
protected:
	int SerializeData();
private:
	EMRDeleteObjectData m_emrDeleteObjectData;
};

class EMRSelectPalette: public EMR
{
public:
	int Create(DWORD ih_pal);
protected:
	int SerializeData();
private:
	EMRSelectPaletteData m_emrSelectPaletteData;
};

class EMRCreatePen: public EMR
{
public:
	int Create(DWORD ih_pen, LogPen log_pen);
protected:
	int SerializeData();
private:
	EMRCreatePenData m_emrCreatePenData;
};

class EMRCreateBrushIndirect: public EMR
{
public:
	int Create(DWORD ih_brush, LogBrush32 log_brush);
protected:
	int SerializeData();
private:
	EMRCreateBrushIndirectData m_emrCreateBrushIndirectData;
};

class EMRCreatePalette: public EMR
{
public:
	EMRCreatePalette();
	virtual ~EMRCreatePalette();
	int Create(DWORD ih_pal, WORD pal_num_entries, const PALETTEENTRY *pal_entry);
protected:
	int SerializeData();
private:
	EMRCreatePaletteData m_emrCreatePaletteData;
	PALETTEENTRY *m_palEntry;
};

class EMRExtCreateFontIndirectW: public EMR
{
public:
	EMRExtCreateFontIndirectW();
	virtual ~EMRExtCreateFontIndirectW();
	int Create(DWORD ih_fonts, LogFontEx logical_font_ex, DWORD num_axes, int *axes_values);
protected:
	int SerializeData();
private:
	EMRExtCreateFontIndirectWData m_emrExtCreateFontIndirectWData;
	int *m_axesValues;
};

class EMRExtCreatePen: public EMR
{
public:
	EMRExtCreatePen();
	virtual ~EMRExtCreatePen();
	int Create(DWORD ih_pen, LogPenEx logical_pen_ex, DWORD num_style_entries, const DWORD *style_entry, DIBPosition dib_pos, const BYTE *bitmap_buffer);
protected:
	int SerializeData();
private:
	EMRExtCreatePen& operator=(const EMRExtCreatePen&);
private:
	EMRExtCreatePenData m_emrExtCreatePenData;
	DWORD *m_styleEntry;
	BYTE *m_bitmapBuffer;
};

class EMRSetMiterLimit: public EMR
{
public:
	int Create(DWORD miter_limit);
protected:
	int SerializeData();
private:
	EMRSetMiterLimitData m_emrSetMiterLimitData;
};

class EMRSetPolyFillMode: public EMR
{
public:
	int Create(DWORD mode);
protected:
	int SerializeData();
private:
	EMRSetPolyFillModeData m_emrSetPolyFillModeData;
};

class EMRSetROP2: public EMR
{
public:
	int Create(DWORD mode);
protected:
	int SerializeData();
private:
	EMRSetROP2Data m_emrSetROP2Data;
};

class EMRSetStretchBltMode: public EMR
{
public:
	int Create(DWORD mode);
protected:
	int SerializeData();
private:
	EMRSetStretchBltModeData m_emrSetStretchBltModeData;
};

class EMRSetTextAlign: public EMR
{
public:
	int Create(DWORD mode);
protected:
	int SerializeData();
private:
	EMRSetTextAlignData m_emrSetTextAlignData;
};

class EMRSetTextColor: public EMR
{
public:
	int Create(COLORREF color);
protected:
	int SerializeData();
private:
	EMRSetTextColorData m_emrSetTextColorData;
};

class EMRSetLayout: public EMR
{
public:
	int Create(DWORD mode);
protected:
	int SerializeData();
private:
	EMRSetLayoutData m_emrSetLayoutData;
};

class EMRSetBrushOrgEX: public EMR
{
public:
	int Create(POINT origin);
protected:
	int SerializeData();
private:
	EMRSetBrushOrgEXData m_emrSetBrushOrgEXData;
};

class EMRSetBKMode: public EMR
{
public:
	int Create(DWORD mode);
protected:
	int SerializeData();
private:
	EMRSetBKModeData m_emrSetBKModeData;
};

class EMRSetBKColor: public EMR
{
public:
	int Create(COLORREF color);
protected:
	int SerializeData();
private:
	EMRSetBKColorData m_emrSetBKColorData;
};

class EMRRestoreDC: public EMR
{
public:
	int Create(int relative);
protected:
	int SerializeData();
private:
	EMRRestoreDCData m_emrRestoreDCData;
};

class EMRSaveDC: public EMR
{
public:
	int Create();
};

class EMRRealizePalette: public EMR
{
public:
	int Create();
};

class EMRMoveToEX: public EMR
{
public:
	int Create(POINT point);
protected:
	int SerializeData();
private:
	EMRMoveToEXData m_emrMoveToEXData;
};

class EMRBeginPath: public EMR
{
public:
	int Create();
};

class EMREndPath: public EMR
{
public:
	int Create();
};

class EMREllipse: public EMR
{
public:
	int Create(RECT box);
protected:
	int SerializeData();
private:
	EMREllipseData m_emrEllipseData;
};

class EMRExtTextOutW: public EMR
{
public:
	EMRExtTextOutW();
	virtual ~EMRExtTextOutW();
	int Create(RECT bounds, DWORD graphics_mode, FLOAT x_scale, FLOAT y_scale, TextInfo text_info, const WCHAR *text, const int* dx);
protected:
	int SerializeData();
private:
	EMRExtTextOutWData m_emrExtTextOutWData;
	WCHAR *m_text;
	int *m_dx;
};

class EMRLineTo: public EMR
{
public:
	int Create(POINT point);
protected:
	int SerializeData();
private:
	EMRLineToData m_emrLineToData;
};

class EMRPolygon16: public EMR
{
public:
	EMRPolygon16();
	virtual ~EMRPolygon16();
	int Create(RECT bounds, DWORD num_points, const POINTS* points);
	POINTS *GetPoints();
protected:
	int SerializeData();
private:
	EMRPolygon16Data m_emrPolygon16Data;
	POINTS *m_lpoints;
};

class EMRRectangle: public EMR
{
public:
	int Create(RECT box);
protected:
	int SerializeData();
private:
	EMRRectangleData m_emrRectangleData;
};

class EMRStrokePath: public EMR
{
public:
	int Create(RECT box);
protected:
	int SerializeData();
private:
	EMRStrokePathData m_emrStrokePathData;
};

class EMRComment: public EMR
{
public:
	EMRComment();
	virtual ~EMRComment();
	int Create(DWORD data_size, const BYTE *private_data);
protected:
	int SerializeData();
private:
	EMRCommentData m_emrCommentData;
	BYTE *m_PrivateData;
};

class EMRIntersectClipRect: public EMR
{
public:
	int Create(RECT box);
protected:
	int SerializeData();
private:
	EMRIntersectClipRectData m_emrIntersectClipRectData;
};

class EMRSetMetaRGN: public EMR
{
public:
	int Create();
};

class EMRBitBlt: public EMR
{
public:
	EMRBitBlt();
	virtual ~EMRBitBlt();
	int Create(RECT bounds, DestinationRect dest_rect, DWORD dwrop, POINT src, XFORM xform_src, COLORREF back_color_src, DWORD usage_src, DIBPosition dib_pos_src, const BYTE *bitmap_buffer);
protected:
	int SerializeData();
private:
	EMRBitBltData m_emrBitBltData;
	BYTE *m_bitmapBuffer;
};

}
#endif //EMR_DEF_H
// $History: EMRDef.h $
//
// *****************  Version 1.0  *****************
// User: liuxu       Date: 11/03/31   Time: 08:15