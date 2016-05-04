// $Archive: DC.h $
//
// Copyright (c) 2011 Fuji Xerox Co.,  Ltd. All rights reserved.
//
// $Author: liuxu $
// $Date: 2011/03/31 08:11:28 $
// $Revision: 1.0 $
#ifndef DC_H
#define DC_H

#include "w2mpf_gdi_def.h"
#include "listimpl.h"

namespace EMFGenCom {

class Handle
{
public:
	Handle();
public:
	DWORD handle;
	int handleType;
};

typedef MyList<Handle> HandleTable;

class DC
{
public:
	DC(int dc_width, int dc_height, const RECT &rclBounds, int dpi);
	~DC();
	RECT GetBounds();
	RECT GetFrame();
	SIZE GetWindowExt();
	POINT GetWindowOrg();
	SIZE GetRefPixel();
	SIZE GetRefSize();
	SIZE GetFrameMicroSize();
	SIZE GetSizeInMM();
	void SetWindowExt(SIZE extent);
	void SetWindowOrg(POINT point);
	int AddHandle(const int handle_type, DWORD &handle);
	int AddHandle(const int handle_type, WORD &handle);
	int RemoveHandle(DWORD handle);
	int GetHandleList(int *handle_cnt, Handle **handle_list);
private:
	DC();
	DC(const DC&);
	DC& operator=(const DC&);
	void SetPhysicalSize(int left, int top, int right, int bottom);
	void SetPixelSize(int left, int top, int right, int bottom);
private:
	HandleTable m_handleTable;
	Handle *m_handleList;

	//the rectangular inclusive-inclusive dimensions,  in .01 millimeter units
	int m_frameLeft;
	int m_frameTop;
	int m_frameRight;
	int m_frameBottom;
	//frame size, in .01 millimeter units
	int m_logicalWidth;
	int m_logicalHeight;

	//rectangular inclusive-inclusive bounds in device units
	int m_boundsLeft;
	int m_boundsTop;
	int m_boundsRight;
	int m_boundsBottom;
	//bounds size, in pixels
	int m_pixelWidth;
	int m_pixelHeight;

	//size of the reference device,  in pixels
	int m_refPixelWidth;
	int m_refPixelHeight;
	//size of the reference device,  in millimeters
	int m_refWidth;
	int m_refHeight;

	int m_WindowX;
	int m_WindowY;

	int m_windowExtX;
	int m_windowExtY;

	int m_widthInMM;
	int m_heightInMM;

	enum StatusCode {
		kNOERROR							= 0x00000000, 				//èàóùê¨å˜
		kERRUNEXPECTED				= 0x8000FFFF, 				//ó\ä˙ÇπÇ ÉGÉâÅ[
		kERROUTOFMEMORY			= 0x8007000E, 				//ÉÅÉÇÉäÇÃälìæÇ…é∏îsÇµÇΩ
	};
};

const int DC_HANDLE_NULL = 0;
const int DC_HANDLE_PEN = 1;
const int DC_HANDLE_BRUSH = 2;
const int DC_HANDLE_FONT = 3;
const int DC_HANDLE_PALETTE = 4;
const int DC_HANDLE_HEADER = 5;

}
#endif //DC_H
// $History: DC.h $
//
// *****************  Version 1.0  *****************
// User: liuxu       Date: 11/03/31   Time: 08:11