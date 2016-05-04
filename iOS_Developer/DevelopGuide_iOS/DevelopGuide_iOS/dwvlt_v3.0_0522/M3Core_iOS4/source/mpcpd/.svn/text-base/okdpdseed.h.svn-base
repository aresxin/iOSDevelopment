// File: OKDPDSeed.H
// Auther: Hisashi Sumida
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef OKDPDSEED_H
#define OKDPDSEED_H

#include "mpc_api.h"
#include "mpc_spi.h"

//#include <windows.h>
#include "win2mpf.h"

//#define MAX_OKD_BLOCK	200	//256KB * 200 = 50MB
#define MAX_OKD_BLOCK	1000	//256KB * 1000 = 250MB	//n

class OKDPDSeed {
public:
	OKDPDSeed( MPCSession * );
	~OKDPDSeed();

	void *GetInterface( MP_RefInterfaceID riid, HRESULT *phres = 0 ) {
		if ( phres ) *phres = MP_E_NOINTERFACE;
			return NULL;
		};
	HRESULT Load( MP_Octet *, long, IStgObject * );
	HRESULT Save( IStgObject *, const MP_AName * = 0 );

	BITMAPINFO *InitForDraw(MP_Canvas *, MP_Integer);
	int GetLineForDraw(unsigned char *);
	void FinishForDraw();

	BITMAPINFO *InitForPrint(MP_Canvas *, MP_Integer);
	int GetLineForPrint(unsigned char *);
	void FinishForPrint();

	BITMAPINFO *InitForGetDIB(int = 100);
	int GetLineForGetDIB(unsigned char *);
	void FinishForGetDIB();

	//n
	HRESULT CreateFromDIBFile( MP_Path *, MP_Dim, MP_Integer , MPC_AdvCancelInfo* info = NULL);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT CreateFromDIBFileW(const MP_WPath *, MP_Dim, MP_Integer , MPC_AdvCancelInfo* info = NULL);

	HRESULT CreateFromMemDIB( BITMAPINFO *, unsigned char *, MP_Dim, MP_Integer , MPC_AdvCancelInfo* info = NULL);
	HRESULT GetDIBHeader( BITMAPINFOHEADER *);

	MP_Integer GetPDType();
	MP_Integer GetCompressInfo();
	MP_Integer GetColorDepth();
	MP_Integer GetColorType(BOOL_XD);
	MP_Dim GetDimensions();
	SIZE GetPixels();
	SIZE GetResolutions();

	static void FreeBitmapInfo(BITMAPINFO *);

	//n V4追加
	BYTE* GetRLTable();
	HRESULT DirectBltPrint(HDC_XD hDC, POINT* pLogPos, SIZE* pLogDim, MP_Integer degree, void* pReserved = NULL);
	HRESULT GetCompDataToFile(MP_Path* dstPath, MP_Integer* compDataType = NULL);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT GetCompDataToFileW(const MP_WPath* dstPathW, MP_Integer* compDataType = NULL);

	HRESULT GetCompDataToHandle(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL);

	HRESULT	GetPercent() { return MP_E_NOTIMPL; };
	HRESULT	SetPercent(MP_Integer percent) {
		m_percent = percent; return MP_NOERROR; };

private:
	HRESULT CreateFromDIB(unsigned char *, MP_Dim, MPC_AdvCancelInfo* info = NULL);
	int GetLineCommon(unsigned char *, long);

	MPC_BigAlloc* m_mpcBigAlloc;	//コンストラクターでインタフェースを取得し、デストラクターで解放する
	MPCSession* m_session;
	MP_Dim m_mdim;
	long m_bitmapinfo_size;			//m_bitmapinfoのサイズ
	//BITMAPINFO* m_bitmapinfo;		//BITMAPINFO
	MP_Octet* m_bitmapinfo;
	void* m_dstBMInfo;

	long m_okd_dst_index;
	unsigned char* m_okd_dst_data[MAX_OKD_BLOCK];
	long m_okd_dst_data_size[MAX_OKD_BLOCK];
	long m_okd_src_data_size[MAX_OKD_BLOCK];
	long m_okd_src_line_num[MAX_OKD_BLOCK];
	unsigned char* m_okd_decode_data;
	long m_okd_decode_data_index;

	long m_compressMode;

	long m_finishDraw;
	long m_currentDrawLine;
	long m_finishPrint;
	long m_currentPrintLine;
	long m_finishGetDIB;
	long m_currentGetDIBLine;
	MP_Integer m_percent;
};

#endif

//
//CHANGE LOG
//97.9.26 - Sumida - 作成
//97.10.6 - Sumida - GetLineを共通化
//97.10.9 - Sumida - MAX_OKD_BLOCKを定義
//97.10.17 - Sumida - m_whiteIsZeroを追加
//97.11.11 - Sumida - AR1510: モノクロビットマップ印刷パフォーマンス改善実施
//97.12.18 - Sumida - AR1510: NT4.0モノクロ印刷改善のための修正
//98.05.06 - matsu - V3.1モノクロ高速印刷ルーチン共通化: 削除 - 拡大処理部分
//98.05.06 - matsu - V3.1対応: いくつかMP_DimをSIZEに変更
//98.05.14 - Nakazawa - V3.1対応 : 各 Seed の CheckAcceptableDIB を削除し、ImplBindPD3 内にまとめた
//99.04.27 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - V4 GetColorTypeを追加
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
