// File: BIND_PD3.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*
*/
#ifndef BIND_PD3_H
#define BIND_PD3_H

#include "mpc_api.h"
//#include "windows.h"

MPC_EXTERN_GUID(IID_SPIBindPD3, 0x1365);

mpinterface SPIBindPD3 : public MPCInterface
{
STDMETHOD_(MP_PD*, MPCreateWMFPD)(MPCSession* session, METAFILEPICT_XD wmf, HRESULT* phres) PURE;
#ifndef SFXVW
STDMETHOD_(MP_PD*, MPCreateBMPPD)(MPCSession* session, MP_Path* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres) PURE;
#endif //SFXVW
STDMETHOD_(MP_PD*, MPCLoadPD)(MPCSession* session, IStgObject* stgobj, const MP_AName* aname, HRESULT* phres) PURE;
#ifndef SFXVW
STDMETHOD_(MP_PD*, MPCreateBMPPDFromHBITMAP)(MPCSession* session, HBITMAP_XD hbitmap, MP_Dim mdim, HPALETTE hpalette, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreatePDfromMemBitmap)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim dim, MP_Integer level, HRESULT* phres) PURE;
#endif //SFXVW
STDMETHOD_(MP_PD*, MPCCreateIconPD)(MPCSession* session, MP_PD* pd, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreateEMFPD)(MPCSession* session, HENHMETAFILE_XD hemf, HRESULT* phres) PURE;
#ifndef SFXVW
STDMETHOD_(MP_PD*, MPCreateJPEGPD)(MPCSession* session, MP_Path* jpegfilepath, MP_Dim dim, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreateJPEGPDfromMem)(MPCSession* session, BYTE* pJpegData, long jpegSize, MP_Dim dim, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreatePDfromImsFile)(MPCSession* pSession, MP_Path* pszImsFilePath, MP_Dim dim, MP_Integer level = 9, HRESULT* phres = NULL) PURE;
STDMETHOD_(MP_PD*, MPCreatePDfromImsMem)(MPCSession* pSession, BYTE* pCompData, long compSize, MP_Dim dim, MP_Integer level = 9, HRESULT* phres = NULL) PURE;
STDMETHOD_(MP_PD*, MPCreateBMPPDW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreateJPEGPDW)(MPCSession* session, const MP_WPath* jpegfilepath, MP_Dim dim, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreatePDfromImsFileW)(MPCSession* pSession, const MP_WPath* imsFilePath, MP_Dim dim, MP_Integer level = 9, HRESULT* phres = NULL) PURE;
#endif //SFXVW
};

MPC_EXTERN_GUID(IID_SPIBindCanvas, 0x1364);

mpinterface SPIBindCanvas : public MPCInterface
{
STDMETHOD_(MP_Canvas*, MPCreatePRTCanvas)(MPCSession* session, HDC_XD hDC, MP_Integer printerdpi, MP_Dim dim, HRESULT* phres) PURE;
STDMETHOD_(MP_Canvas*, MPCreateRAWCanvas)(MPCSession* session, HDC_XD hDC, MP_Integer dpi, MP_Dim dim, HRESULT* phres) PURE;
STDMETHOD_(HBITMAP_XD, MPCreateIconBitmap)(MPCMedia* media, HPALETTE* p_hpal, HRESULT* phres = NULL) PURE;
STDMETHOD_(HPALETTE, MPCreateMediaPalette)(MPCSession* session, HRESULT* phres = NULL) PURE;
STDMETHOD_(HGLOBAL, MPCreateIconDIB)(MPCMedia* media, HRESULT* phres = NULL) PURE;
STDMETHOD_(MP_Canvas*, MPCreatePRTCanvasFloatDPI)(MPCSession* session, HDC_XD hDC, float fPrintDPI, MP_Dim dim, HRESULT* phres) PURE;
};

#endif //BIND_PD3_H

//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.3 - Ichiriki - 生成系実装( MPCreatePDfromMemBitmap, MPCHBITMAPtoDIBHandle, MPCHBITMAPtoDIBFile)
//96.7.9 - Ichiriki - MPCreatePDfromMemBitmap() 引数型変更
//96.7.22 - Ichiriki - MPCreateMediaPalette() 追加
//96.7.25 - Ichiriki - 性能改善 MPCCreateIconPD追加
//96.9.3 - Ichiriki - DIB関連API増加に伴い、export構成を変更
//97.1.10 - ysato - EMF対応
//97.1.29 - Ichiriki - MPCreateEMFPD を関数テーブルの末尾に移動
//97.9.24 - Sumida - SPIBindPD3::MPCreateJPEGPD()を追加
//97.10.23 - Ichiriki - 不要になった実装の削除
//99.05.19 - Komoda - SPIBindCanvas::MPCreateIconDIB()を追加
//99.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//----V41開発
//00.09.25 - Tashiro - V41 メモリからのJPEG直接取り込みを追加
//----V6開発
//2004.04.07 - Tashiro - V6.0 SPIBindPD3::MPCreateMrcPDfromImsFile()追加
//2004.05.21 - Tashiro - V6.0 SPIBindPD3::MPCreateMrcPDfromImsMem()追加
//2004.06.08 - Tashiro - IMS直接取り込み用I/F変更(dim指定削除)
//2004.08.06 - Tashiro - AR10261 IMS直接取り込みI/Fのdim指定復活
//2004.08.10 - Tashiro - AR10553関連 MPCreatePDfromIms…()に関数名変更
//----V7開発
//2007.08.13 - Komoda  - V7.0 Unicode I/Fの追加
//2007.01.15 - Tashiro - MPCreatePRTCanvasの小数解像度指定版を追加
