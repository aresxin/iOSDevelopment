// File: BMPPDSeed.H
// Auther: Hisashi Sumida
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#include "mpc_api.h"
#include "mpc_spi.h"	//MPC_BigAlloc

//#include <windows.h>
#include "win2mpf.h"

//#define MAX_OKD_BLOCK	200	//256KB * 200 = 50MB
#define MAX_OKD_BLOCK	1000	//256KB * 1000 = 250MB	//n

class BMPPDSeed {// : public ImageSeed {
public:
	BMPPDSeed( MPCSession * );
	~BMPPDSeed();

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

	//n キャンセル機構追加
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
	HRESULT	SetPercent(MP_Integer percent) { return MP_E_NOTIMPL; };

private:
	HRESULT CreateFromDIB(unsigned char *);

	MPC_BigAlloc* m_mpcBigAlloc;
	MP_Octet* m_octstr;
	long m_octlen;
	MPCSession* m_session;
	MP_Dim m_mdim;

	long m_bitmapinfo_size;			//m_bitmapinfoのサイズ
	//BITMAPINFO* m_bitmapinfo;		//BITMAPINFO
	MP_Octet* m_bitmapinfo;

	long m_okd_dst_index;
	unsigned char* m_okd_dst_data[MAX_OKD_BLOCK];
	long m_okd_dst_data_size[MAX_OKD_BLOCK];
	long m_okd_src_data_size[MAX_OKD_BLOCK];
	long m_okd_src_line_num[MAX_OKD_BLOCK];
	unsigned char* m_okd_decode_data;
	long m_okd_decode_data_index;

	long m_compressMode;	//V2 OKD only
	long m_colorDepth;
	long m_colorUsed;
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
//97.10.2 - Sumida - V2までのビットマップPD用にBMPPDSeedとして作成
//97.10.9 - Sumida - MAX_OKD_BLOCKを定義
//98.05.07 - matsu - V3.1対応: いくつかMP_DimをSIZEに変更
//98.05.14 - Nakazawa - V3.1対応 : 各 Seed の CheckAcceptableDIB を削除し、ImplBindPD3 内にまとめた
//99.05.12 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - V4 GetColorTypeを追加
//99.06.09 - Komoda - V4 GetColorTypeの実装をBMPPDSeed.cppに移動
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
