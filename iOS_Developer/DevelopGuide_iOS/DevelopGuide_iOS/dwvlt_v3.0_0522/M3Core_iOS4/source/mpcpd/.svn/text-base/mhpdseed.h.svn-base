// File: MHPDSeed.H
// Auther: Hisashi Sumida
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#include "mpc_api.h"
#include "mpc_spi.h"

//#include <windows.h>
#include "win2mpf.h"

class MHPDSeed {
public:
	MHPDSeed( MPCSession * );
	~MHPDSeed();

	void *GetInterface( MP_RefInterfaceID riid, HRESULT *phres = 0 );
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

	HRESULT CreateFromDIBFile( MP_Path *, MP_Dim, MP_Integer , MPC_AdvCancelInfo* info = NULL);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT CreateFromDIBFileW(const MP_WPath *, MP_Dim, MP_Integer , MPC_AdvCancelInfo* info = NULL);

	HRESULT CreateFromMemDIB( BITMAPINFO *, unsigned char *, MP_Dim, MP_Integer , MPC_AdvCancelInfo* info = NULL);
	HRESULT GetDIBHeader( BITMAPINFOHEADER *);

	MP_Integer GetPDType();
	MP_Integer GetCompressInfo();
	MP_Integer GetColorDepth();
	MP_Integer GetColorType(BOOL_XD) { return MP_E_NOTIMPL; }
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

	HRESULT	GetPercent() { return MP_E_NOTIMPL; }
	HRESULT	SetPercent(MP_Integer percent) { return MP_E_NOTIMPL; }

	// V4 MH->MMRコンバート用
	// 注：mpcpd内だけで用いること
	// (MMREncodeを使用するが、mppd_mmr.hをここでincludeしたくないのでとりあえずvoid*にした)
	int ConvertMMRSub(void* pMMREnc, long* pMHCodeSize, long* pWidth, long* pHeight, long* pXppm, long* pYppm);

private:

	MPC_BigAlloc* m_mpcBigAlloc;
	MP_Octet* m_octstr;
	long m_octlen;
	MPCSession* m_session;
	MP_Dim m_mdim;
	void* m_dstBMInfo;

	MP_Octet* m_packedData;
	long m_packedLen;
	IStgObject* m_stgobj;

	long m_compressMode;
	long m_imageOffset;
	long m_x_pixel;
	long m_y_pixel;
	long m_x_resol;
	long m_y_resol;

	long m_finishDraw;
	long m_currentDrawLine;
	long m_finishPrint;
	long m_currentPrintLine;
	long m_finishGetDIB;
	long m_currentGetDIBLine;

};

//
//CHANGE LOG
//97.9.26 - Sumida - 作成
//97.10.17 - Sumida - 不要なコメントを削除
//97.11.11 - Sumida - AR1510: モノクロビットマップ印刷パフォーマンス改善実施
//97.12.18 - Sumida - AR1510: NT4.0モノクロ印刷改善のための修正
//98.05.06 - matsu - V3.1モノクロ高速印刷ルーチン共通化: 削除 - 拡大処理部分
//98.05.06 - matsu - V3.1対応: いくつかMP_DimをSIZEに変更
//98.05.14 - Nakazawa - V3.1対応 : 各 Seed の CheckAcceptableDIB を削除し、ImplBindPD3 内にまとめた
//99.05.12 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - V4 GetColorTypeを追加
//99.06.14 - Nakazawa - V4 MH->MMRコンバータ追加
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
