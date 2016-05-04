// File: MMRPDSeed.H
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _MMRPDSEED_
#define _MMRPDSEED_

#include "mpc_api.h"
#include "mpc_spi.h"
#include "mppd_mmr.h"
#include "mpc_pd.h"

HRESULT MMRErrorToMPError(int mmrerr);

class CImsDataRead;

class MMRPDSeed : public MP_MMRPD {
public:
	MMRPDSeed(MPCSession *);
	~MMRPDSeed();

	void *GetInterface(MP_RefInterfaceID, HRESULT * = 0);
	HRESULT Load(MP_Octet *, long, IStgObject *);
	HRESULT Save(IStgObject *, const MP_AName * = 0);

	BITMAPINFO *InitForDraw(MP_Canvas *, MP_Integer);
	int GetLineForDraw(unsigned char *);
	void FinishForDraw();

	BITMAPINFO *InitForPrint(MP_Canvas *, MP_Integer);
	int GetLineForPrint(unsigned char *);
	void FinishForPrint();

	BITMAPINFO *InitForGetDIB(int = 100);
	int GetLineForGetDIB(unsigned char *);
	void FinishForGetDIB();

	HRESULT CreateFromDIBFile(MP_Path *, MP_Dim, MP_Integer, MPC_AdvCancelInfo* info = NULL);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT CreateFromDIBFileW(const MP_WPath *, MP_Dim, MP_Integer, MPC_AdvCancelInfo* info = NULL);

	HRESULT CreateFromMemDIB(BITMAPINFO *, unsigned char *, MP_Dim, MP_Integer, MPC_AdvCancelInfo* info = NULL);
	HRESULT GetDIBHeader(BITMAPINFOHEADER *);

	MP_Integer GetPDType();
	MP_Integer GetCompressInfo();
	MP_Integer GetColorDepth();
	MP_Integer GetColorType(BOOL_XD) { return MP_E_NOTIMPL; }
	MP_Dim GetDimensions();
	SIZE GetPixels();
	SIZE GetResolutions();

	static void FreeBitmapInfo(BITMAPINFO *);

	BYTE* GetRLTable();
	HRESULT DirectBltPrint(HDC_XD hDC, POINT* pLogPos, SIZE* pLogDim, MP_Integer degree, void* pReserved = NULL);
	HRESULT GetCompDataToFile(MP_Path* dstPath, MP_Integer* compDataType = NULL);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT GetCompDataToFileW(const MP_WPath* dstPathW, MP_Integer* compDataType = NULL);

	HRESULT GetCompDataToHandle(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL);

	HRESULT	GetPercent() { return MP_E_NOTIMPL; };
	HRESULT	SetPercent(MP_Integer /*percent*/) { return MP_E_NOTIMPL; };

	// from MP_MMRPD
	STDMETHOD(CreateFromMMRData)(BYTE* pCompData, long compSize, long width, long height, long xppm, long yppm, MP_Dim mdim, BOOL_XD bCodeCheck = TRUE);
	STDMETHOD(CreateFromImsFile)( MP_Path *pszPath, MP_Dim mdim );
	STDMETHOD(CreateFromImsMem)( unsigned char* pCompData, long compSize, MP_Dim mdim );
	STDMETHOD(CreateFromImsFileW)( const MP_WPath *path, MP_Dim mdim );

private:
	HRESULT CreateFromImsRead( CImsDataRead* pImsRead, MP_Dim dimPD );


	MPC_BigAlloc* m_mpcBigAlloc;
	MPCSession* m_session;
	MP_Octet* m_octstr;
	long m_octlen;

	MP_Dim m_mdim;
	long m_compressMode;
	long m_x_pixel;
	long m_y_pixel;
	long m_x_resol;
	long m_y_resol;

	enum {
		getline_success_complete = 0,
		getline_success_continue = 1,
		getline_error = -1
	};
	long m_currentDrawLine;
	long m_currentPrintLine;
	long m_currentGetDIBLine;

	BITMAPINFO* GetBitmapInfo(BOOL_XD bLookPallete = FALSE);
	MP_MMRDecode* m_pmmrd;

	enum {
		pal_white_is_zero = 1,
		pal_black_is_zero = 2
	};
	long m_palType;
	long m_widthByte;

	// ランレングスデータをメモリ上に保持する(完全にビットマップに伸長しない)
	unsigned char* m_pRLTable;
	unsigned char* m_pCurrentDrawRL;
	unsigned char* m_pCurrentPrintRL;
	unsigned char* m_pCurrentGetDIBRL;
};

#endif

//CHANGE LOG
//98.09.01 - Nakazawa - 新規作成
//99.05.12 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - V4 GetColorTypeを追加
//99.06.14 - Nakazawa - V4 MP_MMRPD に bCodeCheck 追加
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
//99.07.30 - Ichiriki - 不要 pd3pub.h を削除（mpc_pd.hに変更）
//99.09.03 - Nakazawa - V4 AR4448対応：圧縮率上限値はdefineで定義するように変更
//---- 6.0
//2004.08.10 - Tashiro - AR10553 IMSからの直接取り込み機能を追加
//---- 7.0
//2007.08.14 - Komoda  - V7 Unicode I/Fの追加
