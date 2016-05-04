// File: JpgPDSeed.H
// Auther: Ryoji Matsumura
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.
#ifndef _JPEG_PD_SEED_H_
#define _JPEG_PD_SEED_H_

//#include <windows.h>
#include "win2mpf.h"

#include "mpc_api.h"
#include "mpc_pd.h"
#include "jpgcodec.h"

class JpegCodec;
class CImsDataRead;

class JpegPDSeed : public MP_JpegPD{
public:
	JpegPDSeed(MPCSession *session);
	~JpegPDSeed();

	void *GetInterface(MP_RefInterfaceID riid, HRESULT *phres = 0) {
		if (phres)
			*phres = MP_NOERROR;
		if (MP_IsEqual(riid, IID_MP_JPEGPD)) {
			return (void *)this;
		}
		if (phres)
			*phres = MP_E_NOINTERFACE;
		return 0;
	}
	HRESULT Load(MP_Octet *inbase, long insize, IStgObject *stgobj);
	HRESULT Save(IStgObject *stgobj, const MP_AName *aname = 0);

	BITMAPINFO *InitForDraw(MP_Canvas *canvas, MP_Integer degree);
	int GetLineForDraw(unsigned char *);
	void FinishForDraw();

	BITMAPINFO *InitForPrint(MP_Canvas *canvas, MP_Integer degree);
	int GetLineForPrint(unsigned char *);
	void FinishForPrint();

	BITMAPINFO *InitForGetDIB(int hint = 100);
	int GetLineForGetDIB(unsigned char *);
	void FinishForGetDIB();

	HRESULT CreateFromDIBFile(MP_Path *dibfilepath, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT CreateFromDIBFileW(const MP_WPath *dibfilepathW, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL);

	HRESULT CreateFromMemDIB(BITMAPINFO *dibinfo, unsigned char *imagedata, MP_Dim dim, MP_Integer level, MPC_AdvCancelInfo* info = NULL);

	HRESULT GetDIBHeader(BITMAPINFOHEADER *);

	MP_Integer GetPDType();
	MP_Integer GetCompressInfo();
	MP_Integer GetColorDepth();
	MP_Integer GetColorType(BOOL_XD) { return MP_E_NOTIMPL; }
	MP_Dim GetDimensions();
	SIZE GetPixels();
	SIZE GetResolutions();

	static void FreeBitmapInfo(BITMAPINFO *);

	//from MP_JpegPD
	STDMETHOD(CreateFromJpegFile)(MP_Path *path, MP_Dim mdim);
	STDMETHOD(CreateFromMemJpeg)(unsigned char* jpeg_data, long jpeg_size, MP_Dim mdim);
	STDMETHOD(CreateFromImsFile)( MP_Path *pszPath, MP_Dim mdim );
	STDMETHOD(CreateFromImsMem)(unsigned char* pCompData, long compSize, MP_Dim mdim );
	STDMETHOD(CreateFromJpegFileW)(const MP_WPath *path, MP_Dim mdim);
	STDMETHOD(CreateFromImsFileW)(const MP_WPath *path, MP_Dim mdim);

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
	// 省メモリ対策 新規追加 09/07/03 M.Chikyu

	// 新規コード
	MPC_BigAlloc* m_mpcBigAlloc;
	// 新規コードここまで

	MPCSession *m_session;
	MP_Octet *m_octstr;
	long m_octlen;
	MP_Dim m_mdim;
	MP_Integer m_quality;
	SIZE m_bmpSize;
	SIZE m_bmpPpm;

	JpegCodec *m_codec4draw;
	JpegCodec *m_codec4other;
	enum draw_codec_state { draw_idle, draw_processing };
	enum other_codec_state { idle, print_processing, getdib_processing };
	draw_codec_state m_draw_state;
	other_codec_state m_other_state;
	int m_draw_count;
	int m_other_count;

	HRESULT VerifyJpeg( JpegCodec::decomp_source srcJpeg, JpegCodec::decomp_result dstDib, MP_Dim mdim );
#ifndef SFXVW
	HRESULT CreateFromImsRead( CImsDataRead* pIms, MP_Dim dimPD );
	unsigned char* RewriteJFIFResolution( unsigned char* pJfif, long int iJfifSize, int iDpiX, int iDpiY, HRESULT* phres );
	unsigned char* InsertJFIFHeader( unsigned char* pJpeg, long int iJpegSize, int iDpiX, int iDpiY, HRESULT* phres );
#endif
};

#endif //!_JPEG_PD_SEED_H_

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//98.05.07 - matsu - V3.1対応: いくつかMP_DimをSIZEに変更
//99.05.12 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - V4 GetColorTypeを追加
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
//99.07.30 - Ichiriki - 不要 pd3pub.h を削除（mpc_pd.hに変更）
//----V41開発
//00.09.25 - Tashiro - V41 メモリからのJPEG直接取り込みを追加
//----V6開発
//2004.04.28 - Tashiro - IMS形式からの直接取り込みを追加
//2004.06.08 - Tashiro - IMS直接取り込み用I/F変更(dim指定削除)
//2004.08.06 - Tashiro - AR10261 IMS直接取り込みI/Fのdim指定復活
//2004.11.12 - Tashiro - AR11714 可能なときは伸張/圧縮しないで解像度を書き換える
//----V7開発
//2007.08.13 - Komoda  - V7 Unicode I/Fの追加
//07.09.19 - M.Chikyu UNICODE対応
