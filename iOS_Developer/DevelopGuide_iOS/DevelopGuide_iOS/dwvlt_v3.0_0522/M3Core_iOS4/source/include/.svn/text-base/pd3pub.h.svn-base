// File: PD3PUB.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*	PD3PUB.H : PD for proto3 public interface
*
*	コアモデル実装者のPD属性の扱いを楽にするためのコア内部ユーティリティ。
*
*	仕様：
*		当面、ＭＰとコンテント実装者以外には未公開
*/

#ifndef MP_PD_H
#define MP_PD_H

#include "mpc_pd.h"
#include "mpc_spi.h"

DLLBINDFUNC_(MP_BitmapOperations*, MPCGetBitmapOperations)(MPCSession* session);

inline HGLOBAL MPCHBITMAPtoDIBHandle(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, HRESULT* phres = NULL)
{
	MP_BitmapOperations* spi = ::MPCGetBitmapOperations(session);
	if ( ! spi ) return NULL;
	return spi->MPCHBITMAPtoHDIB(session, hBmp, hPal, dim, phres);
}


inline HRESULT MPCHBITMAPtoDIBFile(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, const char* dstPath)
{
	MP_BitmapOperations* spi = ::MPCGetBitmapOperations(session);
	if ( ! spi ) return MP_E_UNEXPECTED;
	return spi->MPCHBITMAPtoDIBFile(session, hBmp, hPal, dim, dstPath);
}

inline HBITMAP_XD MPCDIBtoHBITMAP(MPCSession* session, HGLOBAL hDIB, HPALETTE* phPal=NULL, BOOL_XD bBackGround=FALSE)
{
	MP_BitmapOperations* spi = ::MPCGetBitmapOperations(session);
	if ( ! spi ) return NULL;
	return spi->MPCHDIBtoHBITMAP4(session, hDIB, phPal, bBackGround);
}

// MPSPI_PDConverter1 は、MP_PD に統合して削除

#define IID_MPSPI_PDConverter1	IID_MP_PD
#define MPSPI_PDConverter1	MP_PD
#define GetAsDIBHandle	ConvertToDIBHandleAdv	//n
#define GetAsDIBFile	ConvertToDIBFileAdv		//n


#endif // MP_PD_H

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.6.28 - Ichiriki - API追加
//96.7.9 - Ichiriki - MPCreatePDfromMemBitmap 引数を unsigned charに変更
//96.7.24 - Ichiriki - MPCCreateIconPD を追加
//96.8.30 - Ichiriki - MPCDIBtoHBITMAP(), MPSPI_PDConverter1 を追加
//96.9.3 - Ichiriki - MPARS.DLL MT社変更要求対応。MP_BitmapOperationsを追加
//97.1.10 - ysato - EMF対応
//97.1.13 - Komoda - メタファイルアイコンPD作成対応. MP_PDにCreateIconPD() を追加.
//97.3.19 - Nagano - AR466 DeletePDCash()の追加
//97.10.03 - matsu MP_JpegPDの定義の追加(V3)
//97.10.17 - Ichiriki -  V2旧定義とのバイナリ互換コード除去
//97.10.21 - Ichiriki -  stg_spi.h -> mpc_spi.h
//99.05.18 - Nakazawa - V4追加分実装、MP_JpegPD を mpc_pd.h に移動
//99.07.30 - Ichiriki - V4 DeskIcon色化け防止：MPCDIBtoHBITMAPの引数を変更しMPCDIBtoHBITMAP4()コールに変更
