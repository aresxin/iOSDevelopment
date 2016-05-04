// File: imgpdbse.h
// Author: Ryoji Matsumura
// Copyright (C) 1997 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _IMAGE_PD_BASE_H_
#define _IMAGE_PD_BASE_H_

#include "mpc_pd.h"

#include "imgshk.h"
#include "imgrot.h"
#include "imgshkrl.h"	//n RL高速縮小のため

struct WinCoord;
 
class ImagePDBase : public MP_PD {
public:
    ImagePDBase(MPCSession *session);
    //~ImagePDBase():デストラクタを定義してはいけない

    //from MPCInterface ここでは実装しない
    //STDMETHOD_(void *, GetInterface)(MP_RefInterfaceID riid, HRESULT *phres = 0) PURE;
    //STDMETHOD(Destroy)() PURE;

    //from MP_PD
    //STDMETHOD(Save)(IStgObject *stgobj, MP_AName *aname = 0) PURE;
    STDMETHOD(OLD_OnDraw)(MP_Canvas* canvas) { return MP_E_NOTIMPL; } //バイナリ互換用。V3結合後削除する
    STDMETHOD(OLD_OnPrint)(MP_Canvas* canvas) { return MP_E_NOTIMPL; } //バイナリ互換用。V3結合後削除する
    STDMETHOD(CanRotate)(MP_Integer degree) { return MP_S_OK; }
    STDMETHOD(Rotate)(MP_Integer degree);
    //STDMETHOD_(MP_PD *, CreateIconPD)(HRESULT *phres) PURE;
    STDMETHOD_(void, DeletePDCash)(HRESULT* phres);
    //STDMETHOD(GetPDInfo)(MP_Integer *org, MP_Integer *compLevel, MP_Integer *depth) PURE;
    //STDMETHOD(ConvertToDIBHandle)(HGLOBAL hDIB = 0) PURE;
    //STDMETHOD(ConvertToDIBFile)(MP_Path *dibfilepath) PURE;
    //STDMETHOD(ConvertToDIBHeader)(BITMAPINFOHEADER *bmiHeader) PURE;
    //STDMETHOD(OnDraw)(MP_Canvas *canvas, MP_Integer bPart = 0) PURE;
    //STDMETHOD(OnPrint)(MP_Canvas *canvas, MPC_AdvCancelInfo *info = 0) PURE;

	virtual HRESULT Load(MP_Octet *inbase, long insize, IStgObject *stgobj) = 0;
	//n キャンセル機構追加
	virtual HRESULT CreateFromDIBFile(MP_Path *dibfilepath, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) = 0;
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	virtual HRESULT CreateFromDIBFileW(const MP_WPath *dibfilepathW, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) = 0;

	virtual HRESULT CreateFromMemDIB(BITMAPINFO *dibinfo, unsigned char *imagedata, MP_Dim dim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) = 0;

	STDMETHOD(GetPercent)()  { return MP_E_NOTIMPL; };
	STDMETHOD(SetPercent)(MP_Integer percent)  { return MP_E_NOTIMPL; };

    STDMETHOD(RotateOnMem)(MP_Integer degree) {
		m_degree += degree;
		m_degree = m_degree % 360;
		m_bRotatedOnMem = TRUE;
		return MP_NOERROR;
	}

protected:
    //メンバ関数
    void destroy();
    int isNeedChangeCache(const WinCoord *win, MP_Canvas *canvas);
	SIZE CalcCacheSize(const WinCoord &win);
    MP_Integer getDegree();
	HRESULT rotateCacheBmp(MP_Integer cache_degree);
	HPALETTE MPSelectPalette(HDC_XD hDC, HPALETTE hPal, MP_Canvas *canvas); //AR2989

    //データメンバ
    MPCSession *m_session;
    HBITMAP_XD	m_cacheBmp;
    HPALETTE m_cachePal;
    SIZE m_cacheSize;
    SIZE m_bmpSize;
    MP_Integer m_decodedLine;
    MP_Integer m_needLine;
    BITMAPINFO *m_pbi;
    unsigned char *m_rotBuf;
    MP_Integer m_degree;//回転角
    IStgObject *m_stgobj;//AR1807対応
    ImageShrink m_shrink4Draw;
    ImageShrinkRL m_shrinkrl4Draw;	//n RL高速縮小のため
    ImageRotate m_rotate4Draw;
    BOOL_XD m_isFinished;//AR1495対応 971105
	MP_Integer m_colorType;
	BOOL_XD m_bCanUseRL;	// AR4580対応
	BOOL_XD m_bRotatedOnMem;

	// V7 ハイコントラスト
	int m_iCachedContrastMode;
	BYTE m_CachedForeColor[3];
	BYTE m_CachedBackColor[3];
};
#undef DeleteBitmap
#define     DeleteBitmap(hbm)       MPF_DeleteObject((HGDIOBJ_XD)(HBITMAP_XD)(hbm))

#endif //!_IMAGE_PD_BASE_H_

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//97.10.07 - matsu - ImagePD Creation, Load時により簡単にpdを扱えるためにpure-virtualを3つ宣言した
//97.11.05 - matsu - AR1495対応: m_isFinishedを追加
//97.12.18 - komoda - AR1807:回転性能改善対応
//98.05.07 - matsu - V3.1対応: いくつかMP_DimをSIZEに変更
//98.06.15 - komoda - AR2928対応: 回転処理の変更によりm_isRotatedを削除
//98.06.26 - komoda - AR2989対応: MPSelectPalette()を追加
//99.04.27 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - V4 m_colorTypeを追加
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
//99.08.27 - Nakazawa - V4 AR4580対応: Rotate時にImageShrinkRLを用いた場合の不具合対応
//02.11.05 - h.arai - V5.0.2 AR6597 CalcCacheSizeを追加した。
//----V6.2.2
//2007.05.17 - Tashiro - AR13155 MP_PD::RotateOnMem追加
//07.09.19 - M.Chikyu UNICODE対応
