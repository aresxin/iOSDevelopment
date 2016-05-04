// File: Decoders.h
// Authors: Kiyoshi Tashiro
// Copyright (C) 2004 by Fuji Xerox Co., Ltd. All rights reserved.

// 以下のデコーダ・クラス定義
// CMrcDecoder
// CJpegDecoder
// CMmrDecoder
// CMhDecoder
// CJbig2Decoder

// これらのクラスはIDecoders.hで定義されるIDecoderの実装クラス

#ifndef __DECODERS_H__
#define __DECODERS_H__

#include "idecoder.h"
#include "jpgcodec.h"
#include "imsobjectdrawer.h"

/// CJpegDecoder クラス
class CJpegDecoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CJpegDecoder();

private:
	enum { JPG_ERROR = -1, JPG_OK = 0 };

	virtual ~CJpegDecoder();

	static JpegCodec::Scaling calc_scale_denom(MP_Dim logicalDim, int degree, MP_Dim mdim, SIZE bmpSize);
	static JpegCodec::Scaling calc_scale_denom(BITMAPINFOHEADER *pbih, int percent);
	HRESULT GetDIBHeader(BITMAPINFOHEADER *pbih);
	MP_Dim m_mdim;
	SIZE m_bmpSize;
	SIZE m_bmpPpm;
	MP_Octet *m_octstr;
	long m_octlen;

  JpegCodec *m_codec4draw;
  JpegCodec *m_codec4other;
  enum draw_codec_state { draw_idle, draw_processing };
  enum other_codec_state { idle, print_processing, getdib_processing };
  draw_codec_state m_draw_state;
  other_codec_state m_other_state;

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);
};

#include "mppd_mmr.h"

/// CMmrDecoder クラス
class CMmrDecoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CMmrDecoder();

private:
	virtual ~CMmrDecoder();

	MP_MMRDecode* m_pmmrd;
	unsigned char* m_pRLTable;
	unsigned char* m_pCurrentDrawRL;
	unsigned char* m_pCurrentPrintRL;
	unsigned char* m_pCurrentGetDIBRL;
	MP_Octet* m_octstr;
	long m_octlen;
	SIZE m_bmpSize;
	SIZE m_bmpPpm;
	PaletteType m_palType;
	BITMAPINFO* GetBitmapInfo(BOOL_XD bLookPallete = FALSE);
	HRESULT MMRErrorToMPError(int mmrerr);

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);
};

#include "mppd_mh.h"

/// CMhDecoder クラス
class CMhDecoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CMhDecoder();

private:
	virtual ~CMhDecoder();

	long m_currentDrawLine;
	long m_currentPrintLine;
	long m_currentGetDIBLine;
	long m_x_pixel;
	long m_y_pixel;
	long m_x_resol;
	long m_y_resol;
	long m_imageOffset;
	BITMAPINFO* GetBitmapInfo(BOOL_XD bLookPallete = FALSE);
	MP_Octet* m_octstr;
	long m_octlen;
};

/// CMrcDecoder クラス
class CMrcDecoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CMrcDecoder();


private:
	typedef enum {
		FOR_DRAW = 1,
		FOR_PRINT = 2,
		FOR_GETDIB = 3,
		FOR_NONE = -1
	} WhatFor;
	virtual ~CMrcDecoder();
	BITMAPINFO* CreateBitMapInfo() const;
	CImsObjectDrawer** SetupObjectDrawers( WhatFor whatFor );
	void CleanupObjectDrawers(CImsObjectDrawer** ppDrawers);

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);

	CImsObjectDrawer** m_ppObjectDrawerForDraw;
	CImsObjectDrawer** m_ppObjectDrawerForPrint;
	CImsObjectDrawer** m_ppObjectDrawerForGetDIB;
	CImsDataRead* m_pMrc;
	int m_iNumObjects;
	unsigned short int m_iDepthBits;
	MP_Dim m_RootDimDraw;
	MP_Dim m_RootDimPrint;
	MP_Dim m_RootDimGetDIB;
	unsigned char* m_pMaskBufDraw;
	unsigned char* m_pMaskBufPrint;
	unsigned char* m_pMaskBufGetDIB;
};

extern "C" {
#include "jbf2_pdf.h"
}

/// CJbig2Decoder クラス
class CJbig2Decoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CJbig2Decoder();

private:
	virtual ~CJbig2Decoder();
	BITMAPINFO* GetBitmapInfo(BOOL_XD bLookPallete = FALSE);

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);

	MP_Dim m_mdim;
	SIZE m_bmpSize;
	MP_Octet *m_octstr;
	long m_octlen;
	MP_Octet *m_pGlobalData;
	long m_iGLobalDataLength;
	long m_iLineToGet;
	SIZE m_bmpPpm;
	BOOL_XD m_bGlobalDecoded;
	BOOL_XD m_bImageDecoded;

	JBF2Pdf *m_pJbig2Decoder;
	PaletteType m_palType;
};


/// CRectDummyDecoder クラス
class CRectDummyDecoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CRectDummyDecoder();

private:
	virtual ~CRectDummyDecoder();
	BITMAPINFO* GetBitmapInfo();

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);

	MP_Dim m_mdim;
	SIZE m_bmpSize;
	SIZE m_bmpPpm;
	int m_iWidthBytes;
};

#undef CALLBACK
#pragma warning( push, 3 )
#include "ALLAv2/include/alla.h"
#pragma warning( pop )

/// CAllaV2Decoder クラス
class CAllaV2Decoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	CAllaV2Decoder();

private:
	virtual ~CAllaV2Decoder();
	BITMAPINFO* GetBitmapInfo();

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);

	static int CallBackForRead(void* ptr, const int bytes, void* userdata);
	static int CallBackForWrite(void* ptr, const int bytes, void* userdata);
	static void RGBtoBGR( unsigned char* pBuff, long int iBytes );

	alla::Dec* m_pDecoder;
	MP_Octet* m_octstr;
	long m_octlen;
	long m_iBytesSent;
	unsigned char* m_pOutBuff;
	long m_iBytesGot;

	alla::color_space m_iColorSpace;

	MP_Dim m_mdim;
	SIZE m_bmpSize;
	SIZE m_bmpPpm;
	int m_iWidthBytes;
	int m_iDepthBits;
};

class QomoDec;

/// COldAllaDecoder クラス
class COldAllaDecoder : public IDecoder
{
public:
	STDMETHOD(SetCompressedData)(MP_Integer iLen, MP_Octet* pData);
	STDMETHOD(SetDimension)(MP_Dim dim);
	STDMETHOD(SetBMPSize)(SIZE size);
	STDMETHOD(SetBMPResolution)(SIZE size);
	STDMETHOD(SetPaletteType)(PaletteType iType);

	STDMETHOD(AssertDecodable)();

	STDMETHOD_(BITMAPINFO*, InitForDraw)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForDraw)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForDraw)();

	STDMETHOD_(BITMAPINFO*, InitForPrint)(MP_Dim logicalDim, HDC_XD hdc, MP_Integer degree);
	STDMETHOD_(DecodeResult, GetLineForPrint)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForPrint)();

	STDMETHOD_(BITMAPINFO*, InitForGetDIB)(int iPercent = 100);
	STDMETHOD_(DecodeResult, GetLineForGetDIB)(unsigned char* pLineBuff);
	STDMETHOD_(void, FinishForGetDIB)();

	STDMETHOD_(GetLineFunctionType *, GetFuncToGetLine)();

	STDMETHOD(GetImageDepth)();
	STDMETHOD(SetGlobalData)(MP_Integer iDataLength, unsigned char* pData);

	STDMETHOD_(void, Destroy)();

	COldAllaDecoder();

private:
	virtual ~COldAllaDecoder();
	BITMAPINFO* GetBitmapInfo();

	static DecodeResult __stdcall GetLineForDrawInternal(IDecoder* pMe, unsigned char* pLineBuff);

	BITMAPINFOHEADER* BitmapInfoHeader() const;
	/*
	BITMAPINFO* BitmapInfoPtr() const;
	long BitmapInfoSize() const;
	MP_Octet* AdaptivedPtr() const;
	long AdaptivedSize() const;
	*/
	long m_x_pixel;
	long m_y_pixel;
	unsigned short int m_depth;
	long m_currentDrawLine;
	long m_bytes_per_line;

	int m_iLineToDraw;
	QomoDec* m_pDecoder;
	MP_Octet* m_octstr;
	long m_octlen;
	long m_iBytesSent;
	unsigned char* m_pOutBuff;
	long m_iBytesGot;
	long m_bitmapinfo_size;

	MP_Dim m_mdim;
	SIZE m_bmpPpm;
	//int m_iWidthBytes;
};


#endif //__DECODERS_H__


//CHANGE LOG
//2004.04.07 - Tashiro - 新規作成(V6)
//2004.04.28 - Tashiro - ALLAv2、旧ALLAデコーダを追加
//2004.09.27 - Tashiro - AR11102 JPEG内の解像度ではなくIMS中の解像度を用いる
//2004.10.12 - Tashiro - AR11316 ALLAデコード繰り返し時のリーク修正
