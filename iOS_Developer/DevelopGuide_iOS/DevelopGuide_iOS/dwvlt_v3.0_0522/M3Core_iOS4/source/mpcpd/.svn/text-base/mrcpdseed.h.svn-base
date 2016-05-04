// File: MrcPDSeed.H
// Auther: Kiyoshi Tashiro
// Copyright(C) 2003 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef _MRCPDSEED_
#define _MRCPDSEED_

#include "mpc_api.h"
#include "mpc_spi.h"
#include "mpc_pd.h"
#include "idecoder.h"

class CImsDataRead;

/// MrcPDSeed クラス
class MrcPDSeed : public MP_MrcPD
{
public:
	MrcPDSeed(MPCSession *);
	~MrcPDSeed();

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

	// from MP_MrcPD
	STDMETHOD_(void*, GetInterface) (MP_RefInterfaceID riid, HRESULT *phres );

	STDMETHOD(CreateFromImsFile)( MP_Path *pszPath, MP_Dim dimPD, MP_Integer level = 9 );
	STDMETHOD(CreateFromImsMem)( unsigned char* pImsData, long iImsSize, MP_Dim dimPD, MP_Integer level = 9 );
	STDMETHOD(CreateFromImsFileW)( const MP_WPath *path, MP_Dim mdim, MP_Integer level = 9 );

private:

	MPC_BigAlloc* m_mpcBigAlloc;
	MPCSession* m_session;
	MP_Octet* m_octstr;
	long m_octlen;
	SIZE m_bmpSize;
	SIZE m_bmpPpm;

	HRESULT CreateFromImsRead( CImsDataRead *pImsRead, MP_Dim dimPD, MP_Integer level );
	HRESULT IsAcceptableIms( CImsDataRead *pImsRead );

	MP_Dim m_mdim;
	long m_compressMode;
	long m_x_pixel;
	long m_y_pixel;

	enum {
		getline_success_complete = 0,
		getline_success_continue = 1,
		getline_error = -1
	};
	long m_currentDrawLine;
	long m_currentPrintLine;
	long m_currentGetDIBLine;

	long m_iBytesBufferForDraw;
	long m_iBytesBufferForPrint;
	long m_iBytesBufferForGetDIB;
	MP_Octet* m_pBufferForDraw;
	MP_Octet* m_pBufferForPrint;
	MP_Octet* m_pBufferForGetDIB;
	MP_Integer m_quality;

	IDecoder* m_pDecoder;

	IDecoder::GetLineFunctionType* m_pFuncGetLine;
};


#endif

//CHANGE LOG
//2003.09.19 - Tashiro - 新規作成
//2004.04.28 - Tashiro - IMS形式からの直接取り込みを追加
//2004.06.08 - Tashiro - IMS直接取り込み用I/F変更(dim指定削除)
//2004.08.06 - Tashiro - AR10261 IMS直接取り込みI/Fのdim指定復活
//2004.10.29 - Tashiro - AR10653 描画層が1層でもマスクのみ(ベース層なし)なら取り込む
//2007.08.14 - Komoda  - V7.0 Unicode I/Fの追加
