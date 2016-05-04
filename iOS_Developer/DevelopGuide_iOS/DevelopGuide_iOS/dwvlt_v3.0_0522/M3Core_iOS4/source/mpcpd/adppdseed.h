// File: AdpPDSeed.H
// Auther: Hideki Ichiriki
// Copyright(C) 1999 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef _ADPPDSEED_
#define _ADPPDSEED_

#include "mpc_api.h"
#include "mpc_spi.h"
#include "mpc_pd.h"

#include "qomoenc.h"
#include "qomodec.h"

class AdpPDSeed
{
public:
	AdpPDSeed(MPCSession *);
	~AdpPDSeed();

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
	//07.09.13 - M.Chikyu UNICODE対応
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

	//n V4追加
	BYTE* GetRLTable();
	HRESULT DirectBltPrint(HDC_XD hDC, POINT* pLogPos, SIZE* pLogDim, MP_Integer degree, void* pReserved = NULL);

	HRESULT GetCompDataToFile(MP_Path* dstPath, MP_Integer* compDataType = NULL);
	//07.09.13 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT GetCompDataToFileW(const MP_WPath* dstPathW, MP_Integer* compDataType = NULL);

	HRESULT GetCompDataToHandle(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL);

	HRESULT	GetPercent() {
		return m_percent; };
	HRESULT	SetPercent(MP_Integer percent) { return MP_E_NOTIMPL; };

private:

	MPC_BigAlloc* m_mpcBigAlloc;
	MPCSession* m_session;
	MP_Octet* m_octstr;
	long m_octlen;
	long m_bitmapinfo_size;


	inline BITMAPINFOHEADER* BitmapInfoHeader() {
			return (BITMAPINFOHEADER*)m_octstr;
		};
	inline BITMAPINFO* BitmapInfoPtr() {
			return (BITMAPINFO*)m_octstr;
		};
	inline long BitmapInfoSize() {
			return m_bitmapinfo_size;
		};
	inline MP_Octet* AdaptivedPtr() {
			return m_octstr + m_bitmapinfo_size;
		};
	inline long AdaptivedSize() {
			return m_octlen - m_bitmapinfo_size;
		};

	BITMAPINFO* GetBitmapInfo();


	MP_Dim m_mdim;
	long m_compressMode;
	long m_x_pixel;
	long m_y_pixel;
	unsigned short m_depth;
	long m_bytes_per_line;

	enum {
		getline_success_complete = 0,
		getline_success_continue = 1,
		getline_error = -1
	};
	long m_currentDrawLine;
	long m_currentPrintLine;
	long m_currentGetDIBLine;


	QomoDec* m_QomoDec_draw;
	QomoDec* m_QomoDec_print;
	QomoDec* m_QomoDec_getdib;

	MP_Integer m_percent;
};


#endif

//CHANGE LOG
//99.5.25 - Ichiriki - 新規作成
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
//99.7.30 - Ichiriki - 不要 pd3pub.h を削除（mpc_pd.hに変更）
