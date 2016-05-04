// File: BIND_LT.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef BIND_LT_H
#define BIND_LT_H

#include "mpc_api.h"
//#include "windows.h"

MPC_EXTERN_GUID(IID_SPIBindMPCLT, 0x1369);

mpinterface SPIBindMPCLT : public MPCInterface
{
STDMETHOD(IsAlive)() PURE;
/*NOT SUPPORT*/ STDMETHOD_(HGLOBAL, MPCRotateHBITMAP)(MPCSession* session, HBITMAP_XD hBmp, MP_Integer angle, HDC_XD hDC, HPALETTE hPal, HRESULT* phres = NULL) PURE;
/*OLD API*/ STDMETHOD_(HGLOBAL, MPCRotateHDIB)(MPCSession* session, HGLOBAL hDIB, MP_Integer angle, HRESULT* phres = NULL) PURE;
STDMETHOD_(HGLOBAL, MPCRotateDIB)(MPCSession* session, BITMAPINFO* bi, MP_Integer degree, HRESULT* phres = NULL, unsigned char* imagedata = NULL) PURE;

};


#endif //BIND_LT_H

//CHANGE LOG
//96.7.5 - Ichiriki - 作成
//97.1.24 - Ichiriki - V2 回転自前化に伴い、MPCRotateHBITMAP_XD()の無効化と、MPCRotateHDIB_V2()の追加
