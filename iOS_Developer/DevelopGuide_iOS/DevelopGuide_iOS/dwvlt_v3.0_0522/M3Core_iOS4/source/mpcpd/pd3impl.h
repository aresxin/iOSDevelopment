// File: PD3IMPL.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996-2005 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*
*/

#ifndef _PD3IMPL_H_
#define _PD3IMPL_H_

#include "mpc_api.h"
#include "../mpcinc/bind_pd3.h"
#include "ifmtattr.h"

MPC_EXTERN_GUID(IID_BMPPD, 0x1367);
MPC_EXTERN_GUID(IID_WMFPD, 0x1368);
MPC_EXTERN_GUID(IID_EMFPD, 0x1375);
MPC_EXTERN_GUID(IID_MP_MHPD, 0x1380);
MPC_EXTERN_GUID(IID_MP_BMPMHPD, 0x1381);

HPALETTE CreateMediaPalette();

// PDイメージの最大サイズ
#define MPC_MAX_IMAGE_WIDTH		65535
#define MPC_MAX_IMAGE_HEIGHT	65535
#define MPC_MAX_JPEG_SIZE		MPC_MAX_PD_SIZE

// キャンセル用コールバック関数を呼び出す頻度(ms単位)
#define MPC_CANCEL_CALLBACK_FREQ_TIME	500

// libjpegに渡す画質パラメータ。ACCESにも値が必要なためJpgPDSeed.cppから移動した。
enum { jpeg_high_quality = 83, jpeg_standard_quality = 55, jpeg_low_quality = 31 };
enum { jpeg_high_SF = 34, jpeg_standard_SF = 90, jpeg_low_SF = 161 };
enum { mrc_high_quality = 83, mrc_standard_quality = 55, mrc_low_quality = 31 };

// PD Factory (V3までのPD生成系I/Fに新規I/Fを追加する際に用いる。バイナリ互換を保つため)
// V4.1 以降、MP_PDFactory2 の実装を与える
// V6 以降、MP_PDFactory3 の実装を与える
class ImplPDFactory : MP_PDFactory3
{
#ifndef SFXVW

public:
STDMETHOD_(MP_PD*, MPCreateBMPPD)(MPCSession* session, MP_Path* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres);
STDMETHOD_(MP_PD*, MPCreatePDfromMemBitmap)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim dim, MP_Integer level, HRESULT* phres);
STDMETHOD_(MP_PD*, MPCCreateIconPD)(MPCSession* session, MP_PD* pd, HRESULT* phres);
STDMETHOD_(MP_PD*, MPCreateJPEGPD)(MPCSession* session, MP_Path* jpegfilepath, MP_Dim dim, HRESULT* phres);
// V4 修正
STDMETHOD_(MP_PD*, MPCreateWMFPD)(MPCSession* session, METAFILEPICT_XD wmf, MP_Integer level, HRESULT* phres);
STDMETHOD_(MP_PD*, MPCreateEMFPD)(MPCSession* session, HENHMETAFILE_XD hemf, MP_Integer level, HRESULT* phres);
// V4 新規追加
STDMETHOD_(MP_PD*, MPCreateBMPPDAdv)(MPCSession* session, MP_Path* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo* info);
STDMETHOD_(MP_PD*, MPCreatePDfromMemBitmapAdv)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim dim, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo* info);
STDMETHOD_(MP_PD*, MPCreateMMRPD)(MPCSession* session, BYTE* pCompData, long compSize, long width, long height, long xppm, long yppm, MP_Dim mdim, HRESULT* phRes);
STDMETHOD_(MP_PD*, MPCreateMMRPDfromMHPD)(MPCSession* session, MP_PD* pMHPD, HRESULT* phres);
// V4.1 新規追加
STDMETHOD_(MP_PD*, MPCreateJPEGPDfromMem)(MPCSession* session, BYTE* pJpegData, long jpegSize, MP_Dim dim, HRESULT* phres = NULL);
// V6 新規追加
STDMETHOD_(MP_PD*, MPCreatePDfromImsFile)(MPCSession* pSession, MP_Path* pszImsFilePath, MP_Dim dim, HRESULT* phres = NULL);
STDMETHOD_(MP_PD*, MPCreatePDfromImsMem)(MPCSession* pSession, BYTE* pCompData, long compSize, MP_Dim dim, HRESULT* phres = NULL);
// V7 Unicode I/F
STDMETHOD_(MP_PD*, MPCreateBMPPDW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres);
STDMETHOD_(MP_PD*, MPCreateJPEGPDW)(MPCSession* session, const MP_WPath* jpegfilepath, MP_Dim dim, HRESULT* phres);
STDMETHOD_(MP_PD*, MPCreateBMPPDAdvW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo* info = NULL);
STDMETHOD_(MP_PD*, MPCreatePDfromImsFileW)(MPCSession* pSession, const MP_WPath* imsFilePath, MP_Dim dim, HRESULT* phres = NULL);

#endif //SFXVW
};

class ImplBitmapOperations : MP_BitmapOperations
{
public:
	STDMETHOD_(HBITMAP_XD, MPCHDIBtoHBITMAP)(MPCSession* session, HGLOBAL hDIB, HPALETTE* phPal) ;
	STDMETHOD_(HGLOBAL, MPCHBITMAPtoHDIB)(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, HRESULT* phres) ;

	STDMETHOD(MPCHBITMAPtoDIBFile)(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, const char* dstPath) ;

	STDMETHOD(MPCHDIBtoDIBFile)(MPCSession* session, HGLOBAL hDIB, MP_Dim dim, const MP_Path* dstPath) ;
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	STDMETHOD(MPCHDIBtoDIBFileW)(MPCSession* session, HGLOBAL hDIB, MP_Dim dim, const MP_WPath* dstPathW) ;

	STDMETHOD_(HGLOBAL, MPCDIBFiletoHDIB)(MPCSession* session, const MP_Path* srcPath, MP_Dim dim) ;
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	STDMETHOD_(HGLOBAL, MPCDIBFiletoHDIBW)(MPCSession* session, const MP_WPath* srcPathW, MP_Dim dim) ;

	STDMETHOD_(HGLOBAL, MPCShrinkHDIB)(MPCSession* session, HGLOBAL hDIB, MP_Rate rate) ;
	// V4 追加
	STDMETHOD_(HRESULT, MPCNoiseReduceDIBFile)(MPCSession* session, const MP_Path* dstPath, MP_Integer level, MPC_AdvCancelInfo* info);
	STDMETHOD_(HRESULT, MPCNoiseReduceHDIB)(MPCSession* session, HGLOBAL hDIB, MP_Integer level, MPC_AdvCancelInfo* info);
	STDMETHOD_(MP_Integer, MPCCheckDIBColorType)(MPCSession* session, BITMAPINFO* pbi, BYTE* pbits);
	STDMETHOD(MPCStretchBlt)(MPCSession* session, HDC_XD hdcDest, int xDest, int yDest, int cxDest, int cyDest, HDC_XD hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, DWORD dwROP, BOOL_XD bColorReduction);
	STDMETHOD_(HBITMAP_XD, MPCHDIBtoHBITMAP4)(MPCSession* session, HGLOBAL hDIB, HPALETTE* phPal, BOOL_XD bBackGround) ;
	// V7 Unicode I/F
	STDMETHOD(MPCHBITMAPtoDIBFileW)(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, const MP_WPath* dstPath) ;
	STDMETHOD_(HRESULT, MPCNoiseReduceDIBFileW)(MPCSession* session, const MP_WPath* dibPathW, MP_Integer level, MPC_AdvCancelInfo* info = NULL) ;
	
	STDMETHOD_(HGLOBAL, MPCHDIBtoHJPEG)(MPCSession* session, HGLOBAL hDIB, MP_Integer level, MP_Integer* pjpegsize, HRESULT* phres) ;
};

class ImplBindPD3 : SPIBindPD3
{
	ImplBitmapOperations* m_bmpops;
	ImplPDFactory* m_pdfactory;

public:
	ImplBindPD3() {
		m_bmpops = NULL;
		m_pdfactory = NULL;
		};

	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL) {
			if (phres) *phres = MP_NOERROR;

			if ( MP_IsEqual(riid, IID_MPCInterface) ) {
				return (void*)this;
			} else if ( MP_IsEqual(riid, IID_SPIBindPD3) ) {
				return (void*)this;
			} else if ( MP_IsEqual(riid, IID_BitmapOperations) ) {
				if ( ! m_bmpops )
					m_bmpops = new ImplBitmapOperations;
				return (void*)m_bmpops;
			} else if (MP_IsEqual(riid, IID_PDFactory)) {	// V4新規I/F
				if (!m_pdfactory)
					m_pdfactory = new ImplPDFactory;
				return (void*)m_pdfactory;
			} else if (MP_IsEqual(riid, IID_PDFactory2)) {	// V4.1新規I/F
				if (!m_pdfactory)
					m_pdfactory = new ImplPDFactory;
				return (void*)m_pdfactory;
			} else if (MP_IsEqual(riid, IID_PDFactory3)) {	// V6新規I/F
				if (!m_pdfactory)
					m_pdfactory = new ImplPDFactory;
				return (void*)m_pdfactory;
			}
			if ( phres )	*phres = MP_E_NOINTERFACE;
			return NULL;
		};

	STDMETHOD(Destroy)() {
			if ( m_bmpops )
				delete m_bmpops;
			m_bmpops = NULL;
			if (m_pdfactory)
				delete m_pdfactory;
			m_pdfactory = NULL;

			delete this	;
			return MP_NOERROR;
		};

	STDMETHOD_(MP_PD*, MPCreateEMFPD)(MPCSession* session, HENHMETAFILE_XD hemf, HRESULT* phres);
	STDMETHOD_(MP_PD*, MPCreateWMFPD)(MPCSession* session, METAFILEPICT_XD wmf, HRESULT* phres);
#ifndef SFXVW
	STDMETHOD_(MP_PD*, MPCreateBMPPD)(MPCSession* session, MP_Path* dibfilepath, MP_Dim mdim, MP_Integer level, HRESULT* phres);
	STDMETHOD_(MP_PD*, MPCreateJPEGPD)(MPCSession* session, MP_Path* jpegfilepath, MP_Dim mdim, HRESULT* phres);
#endif //SFXVW
	STDMETHOD_(MP_PD*, MPCLoadPD)(MPCSession* session, IStgObject* stgobj, const MP_AName* aname, HRESULT* phres);

	STDMETHOD_(MP_PD*, MPCreateBMPPDFromHBITMAP)(MPCSession* session, HBITMAP_XD hbitmap, MP_Dim mdim, HPALETTE hpalette, HRESULT* phres);
#ifndef SFXVW
	STDMETHOD_(MP_PD*, MPCreatePDfromMemBitmap)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim dim, MP_Integer level, HRESULT* phres);
#endif //SFXVW
	STDMETHOD_(MP_PD*, MPCCreateIconPD)(MPCSession* session, MP_PD* pd, HRESULT* phres) ;
#ifndef SFXVW
	STDMETHOD_(MP_PD*, MPCreateJPEGPDfromMem)(MPCSession* session, BYTE* pJpegData, long jpegSize, MP_Dim mdim, HRESULT* phres);
	STDMETHOD_(MP_PD*, MPCreatePDfromImsFile)(MPCSession* pSession, MP_Path* pszImsFilePath, MP_Dim dim, MP_Integer level = 9, HRESULT* phres = NULL);
	STDMETHOD_(MP_PD*, MPCreatePDfromImsMem)(MPCSession* pSession, BYTE* pCompData, long compSize, MP_Dim dim, MP_Integer level = 9, HRESULT* phres = NULL);
	// V7 Unicode I/F
	STDMETHOD_(MP_PD*, MPCreateBMPPDW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim mdim, MP_Integer level, HRESULT* phres);
	STDMETHOD_(MP_PD*, MPCreateJPEGPDW)(MPCSession* session, const MP_WPath* jpegfilepath, MP_Dim dim, HRESULT* phres);
	STDMETHOD_(MP_PD*, MPCreatePDfromImsFileW)(MPCSession* pSession, const MP_WPath* imsFilePath, MP_Dim dim, MP_Integer level = 9, HRESULT* phres = NULL);
#endif //SFXVW
};


/*
*   PD種別　（PDヘッダの TAG_PD_TYPE タグに格納される値）
*/
#define PDTYPE_OLD_DIB  0     // P3 SST 以前の旧フォーマット：　圧縮なしのDIB
#define PDTYPE_OLD_WMF  0x100 // P3 SST 以前の旧フォーマット：　PDにmetafileを用いる

#define PDTYPE_P3_WMF   1     // OKDによって圧縮されたWMF
#define PDTYPE_P3_DIB   2     // OKDによって圧縮された多値ビットマップ
#define PDTYPE_P3_MH    3     // MHによって圧縮されたモノクロ２値ビットマップ
#define PDTYPE_P3_EMF   4     // OKDによって圧縮されたEMF
//V3で作成されるビットマップPDは以下の4つのタイプのいずれかである
#define PDTYPE_V3_JPEG  5     // JPEG圧縮された多値ビットマップ
#define PDTYPE_V3_ABMC  6     // ABMC圧縮された多値ビットマップ
#define PDTYPE_V3_OKD   7     // OKD圧縮されたビットマップ
#define PDTYPE_V3_MH    8     // MH圧縮されたモノクロ2値ビットマップ
//V4新規
#define PDTYPE_V4_MMR   9     // MMR圧縮されたモノクロ2値ビットマップ
#define PDTYPE_V4_ADP  10     // Adaptive圧縮された多値ビットマップ
//V6新規
#define PDTYPE_V6_MRC  11     // MRC(imsフォーマット)圧縮された多値画像

/*
*   PD属性のタグ情報
*/
#define TAG_PD_TYPE		(0)
#define TAG_PD_FILELEN	(1)
#define TAG_PD_MM		(3)		// WMF PD のマッピングモード	WMFのみ有意
#define TAG_PD_XEXT		(4)		// PD幅（メディア座標系）
#define TAG_PD_YEXT		(5)		// PD高（メディア座標系）
#define TAG_PD_DATA		(6)
#define TAG_PD_WIDTH	(7)		// ビットマップ幅(pixel)	MHのみ有意
#define TAG_PD_HEIGHT	(8)		// ビットマップ幅(pixel)	今はMHのみ有意
#define TAG_PD_PACKLEN	(9)		// MHやOKDの圧縮結果バイト数。０の場合無圧縮を意味する。
#define TAG_PD_OPAQUE	(10)	// 不透過なＰＤを指定。WMFキャッシュに必須
#define TAG_PD_XPPM		(11)	// 元々のDIBに格納されていた解像度情報 biXPelsPerMeter
#define TAG_PD_YPPM		(12)	// 元々のDIBに格納されていた解像度情報 biYPelsPerMeter
#define TAG_PD_QUALITY	(13)	// ビットマップPDで非可逆圧縮のとき、圧縮後の画質を意味する。2:高画質、3:標準、4:高圧縮、5:外部JPEG
#define TAG_PD_PALETTE	(15)	// V4 MMRPDにおいて、元のビットマップが白=0か黒=0かを格納する

// 64bit対応：物理メモリの空き容量を安全に取得するための共通関数追加
size_t GetAvailPhysSize();

#endif

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.3 - Ichiriki - 生成系実装( MPCreatePDfromMemBitmap, MPCHBITMAPtoDIBHandle, MPCHBITMAPtoDIBFile)
//96.7.9 - Ichiriki - MPCreatePDfromMemBitmapの型変更
//96.7.25 - Ichiriki - MPCCreateIconPD の追加
//96.8.8 - Ichiriki - PDフォーマット変更
//96.8.26 - Ichiriki - コメント訂正
//96.9.2 - Ichiriki - TAG_PD_OPAQUE,CreateMediaPalette(),MPCDIBtoHBITMAP()宣言
//96.9.3 - Ichiriki - ImplBitmapOperationインタフェースの追加
//97.1.10 - ysato - EMF対応
//97.1.13 - Komoda - メタファイルアイコンPD作成対応. class宣言をcppから移動.
//97.1.28 - Ichiriki - TAG_PD_MH_XPPM, TAG_PD_MH_YPPMの#define追加
//97.3.19 - Nagano - AR466 DeletePDCash()の追加
//97.9.24 - Sumida - ImplBindPD3::MPCreateJPEGPDを追加
//97.9.24 - ysato - ImplWMFPD, ImplEMFPD修正
//97.9.24 - Sumida - V3で作成するビットマップPD4つのタイプPDTYPE_V3_*を定義、およびTAG_PD_*(12)〜(16)を追加
//97.10.20 - Ichiriki - V2互換性維持コード PDConverter1 を削除
//97.10.27 - ysato - PSパッチの組み込み
//97.10.30 - Komoda - 透過contentのPS対応
//97.11.06 - ysato - PSPatchInfo等のデータ構造変更に伴う修正(不要なメモリ使用を削減)
//97.11.21 - ysato - AR1244対応（EnumUserData変更)
//97.12.11 - Nakazawa - 画面表示とキャッシュ作成の別スレッド化に伴う修正
//97.12.19 - ysato - AR2030(Escape版)対策に伴う変更
//97.12.19 - Nakazawa - AR1905,1907,1926,1927,2005対策に伴うUserDataの変更
//98.05.14 - Komoda - V3.1対応 class ImplBMPPDを削除
//98.06.08 - Komoda - V3.1OLEサーバ対応 ImplEMFPD::OnDrawToWMF を追加
//98.06.26 - Komoda - AR2989 EnumUserData に bForceBackgroundPalette を追加
//98.09.02 - Nakazawa - MMRPD追加
//99.04.08 - Nakazawa - MPCNoiseReductionHDIB 追加
//99.05.11 - Nakazawa - V4追加分実装
//99.05.19 - Komoda - V4追加分実装
//99.05.26 - Nakazawa - TAG_PD_MH_?PPM 削除
//99.05.27 - Nakazawa - V4 mpcincディレクトリ作成、インクルード先修正
//99.05.27 - Nakazawa - V4 TAG_PD_PALETTE 追加
//99.06.01 - Komoda - V4 サイズ削減追加
//99.06.03 - Nakazawa - V4 TAG_PD_COLOR 削除
//99.06.03 - Ichiriki - V4 PDTYPE_V4_ADP 追加
//99.06.14 - Nakazawa - V4 IID_MP_MHPD, IID_MP_BMPMHPD 追加
//99.06.18 - Komoda - V4 メタファイル関連の宣言をpd3mf.hに移動
//99.07.23 - Nakazawa - V4 PDイメージの最大サイズを定義
//99.07.30 - Ichiriki - V4 ImplBitmapOperations::MPCHDIBtoHBITMAP4 追加
//99.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//----V41開発
//00.09.25 - Tashiro - V41 メモリからのJPEG直接取り込みを追加
//00.09.29 - Tashiro - V41 可逆圧縮の自動選択への対応
//00.10.23 - Tashiro - V41 AR5898 ACCESに渡すSF値の定義が間違っていた
//----V6開発
//2004.04.07 - Tashiro - V6.0 MRC-PD追加
//2004.05.21 - Tashiro - V6.0 PDFactory3, IMS直接取り込み追加
//2004.06.08 - Tashiro - IMS直接取り込み用I/F変更(dim指定削除)
//2004.08.06 - Tashiro - AR10261 IMS直接取り込みI/Fのdim指定復活
//2004.08.10 - Tashiro - AR10553関連 MPCreatePDfromIms…()に関数名変更
//----V6.0.5開発
//2005.11.09 - Nakazawa - 64bit対応 GetAvailPhysSize()追加
//----V7開発
//2007.08.14 - Komoda - V7.0 Unicode I/Fの追加
