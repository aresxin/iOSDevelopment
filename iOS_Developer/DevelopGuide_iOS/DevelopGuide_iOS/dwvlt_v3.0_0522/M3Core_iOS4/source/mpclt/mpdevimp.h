// File: MPDevImp.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _MPDEVIMPL_H_
#define _MPDEVIMPL_H_

#include "mpc_devu.h"

class ImplDeviceUtilities : MP_DeviceUtilities
{
public:
STDMETHOD(CanDirectBlt)(MPCSession* session, HDC_XD hDC, int imageType);
STDMETHOD(DirectBlt)(MPCSession* session, HDC_XD hDC, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, DWORD dwRop, LPBITMAPINFO lpBitsInfo, DWORD dwBitsInfoSize, LPSTR lpImageData, DWORD dwImageSize, int degree, int imageType);
STDMETHOD(CanSetColorMode)(MPCSession* session, HDC_XD hDC);
STDMETHOD(PreSetColorMode)(MPCSession* session, HDC_XD hDC);
STDMETHOD(SetColorMode)(MPCSession* session, HDC_XD hDC, int mode);
STDMETHOD(GetNup)(MPCSession* session, HDC_XD hDC);
};

#endif // _MPDEVIMPL_H_

// CHANGE LOG
// 1999.05.18 - Nakazawa - 作成
