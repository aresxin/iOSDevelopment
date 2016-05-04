// File: mppmutil.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

/*
	mppmodel.cpp 内の実装が大きくなってきたので、
	内部で用いるローカル関数を別ファイルにした。
	現在は V4 追加分のみ。
*/

#ifndef _MPPUTIL_H_
#define _MPPUTIL_H_

#define WIDTHBYTES(bits)      ((((bits) + 31) & ~31) >> 3)
#define DPI_TO_DPM(dpi)		(((LONG)(dpi) * 10000) / 254)
#define FDPI_TO_DPM(dpi)		((LONG)(dpi * 10000.0f / 254.0f))
#define DPM_TO_DPI(dpm)		(((LONG)(dpm) * 127 + 2500) / 5000)

//V5.0 白黒高画質用
#define	RIGHT_RATE						0.375	//= 3/8
#define	DOWN_RATE						0.375	//= 3/8
#define	RIGHT_DOWN_RATE					0.25	//= 1/4
#define	MPPM_RED						0.3
#define	MPPM_GREEN						0.59
#define	MPPM_BLUE						0.11
#define HIQUALITYMONO_THRESHOLD			0x80	//= 128
#define	MIN(a, b)						((a <= b) ? a : b)
#define	rgb_to_gray(red, green, blue)	MIN(255, (int)(MPPM_RED * (int)red + MPPM_GREEN * (int)green + MPPM_BLUE * (int)blue))

// BITMAPINFOから実際のイメージデータへのポインタを返す
unsigned char* GetDibBits(BITMAPINFO* dibinfo);

// BasicPageからへテロを取得する
IHeteroBodyCont* GetHeteroBodyCont(MPCObject* basicPage);

// BMPファイルからBITMAPINFOHEADERを取得する
HRESULT GetBmpInfoHeaderFromFile( MPCSession* pSession, const char* pszBmpPath, BITMAPINFOHEADER* pBmpInfoHeader );

// BMPファイルからBITMAPINFOHEADERを取得する(ユニコード対応版)
HRESULT GetBmpInfoHeaderFromFileW( MPCSession* pSession, const MP_WPath* pszBmpPath, BITMAPINFOHEADER* pBmpInfoHeader );

// メモリ上のBMPからBITMAPINFOHEADERを取得する
HRESULT GetBmpInfoHeaderFromMem( void* pBmp, BITMAPINFOHEADER* pBmpInfoHeader );

// イメージ変換出力用
// BasicPageまたはPDのOnPrintを用いてメモリビットマップに描画する。
// 1999.07.26 dstPath 追加、ファイルに出力する場合の省メモリ化
// 2002.07.18 AR7859対応 アノテ有無フラグ追加
// 09.07.14 - M.Chikyu UNICODE対応
//HGLOBAL ConvertBPorPDToDIB(MPCSession* session, MPCObject* basicPage, MP_PD* pd, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres, MPC_AdvCancelInfo* info, LPCTSTR dstPath = NULL, bool bWithAnno = true);
HGLOBAL ConvertBPorPDToDIB(MPCSession* session, MPCObject* basicPage, MP_PD* pd, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres, MPC_AdvCancelInfo* info, const MP_Path* dstPath = NULL, bool bWithAnno = true);

// イメージ変換出力用 (解像度 小数指定版)
// 白枠を付けないオプションを指定する引数bClipInsideを追加。
// bClipInsideがtrue(=白枠を付ける)が従来通りの描画かつデフォルト。
// MPPMConvertBasicPageToHDIBCentiDPI から呼ばれるときに使われる。
// 09.07.14 - M.Chikyu UNICODE対応
//HGLOBAL ConvertBPorPDToDIBFloatDPI(MPCSession* session, MPCObject* basicPage, MP_PD* pd, float fDPI, MPPM_CONVDIB_MODE mode, HRESULT* phres, MPC_AdvCancelInfo* info, LPCTSTR dstPath = NULL, bool bWithAnno = true, bool bClipInside = true, bool bHighQuality = false);
HGLOBAL ConvertBPorPDToDIBFloatDPI(MPCSession* session, MPCObject* basicPage, MP_PD* pd, float fDPI, MPPM_CONVDIB_MODE mode, HRESULT* phres, MPC_AdvCancelInfo* info, const MP_Path* dstPath = NULL, bool bWithAnno = true, bool bClipInside = true, bool bHighQuality = false);

// イメージ変換出力用 (ユニコード対応版)
HGLOBAL ConvertBPorPDToDIBW(MPCSession* session, MPCObject* basicPage, MP_PD* pd, MP_Integer dpi, MPPM_CONVDIB_MODE mode, HRESULT* phres, MPC_AdvCancelInfo* info, const MP_WPath* dstPath = NULL, bool bWithAnno = true);

// イメージ変換出力用 (ユニコード対応、解像度 小数指定版)
HGLOBAL ConvertBPorPDToDIBFloatDPIW(MPCSession* session, MPCObject* basicPage, MP_PD* pd, float fDPI, MPPM_CONVDIB_MODE mode, HRESULT* phres, MPC_AdvCancelInfo* info, const MP_WPath* dstPath = NULL, bool bWithAnno = true);

// 圧縮データからPDを作る際に必要な情報をまとめた構造体
typedef struct tag_TiffInfo {
	unsigned char* pCompData;
	unsigned long compSize;
	unsigned long width;
	unsigned long height;
	unsigned long xppm;	// (PelsPerMeter)
	unsigned long yppm;	// (PelsPerMeter)
	int pageNumber;
	tag_TiffInfo() {
		pCompData = NULL;
	}
	~tag_TiffInfo() {
		if (pCompData)
			delete [] pCompData;
	}
} TiffInfo;

// 各IFDのタグ情報をチェックし、圧縮データを取り出す。
HRESULT CheckTIFFTag(MP_File* mpfile, int nth, TiffInfo* pInfo);

#endif // _MPPUTIL_H_

// CHANGE LOG
// 1999.05.11 - Nakazawa - 作成
// 1999.07.26 - Nakazawa - V4 ConvDIB File出力の省メモリ化
// 1999.08.03 - Nakazawa - V4 コードレビューの結果を反映
// 2001.11.26 - Ichikawa - V5.0 白黒 1bit 高画質出力、文書属性・アノテーションの継承 対応
// 2002.07.18 - Nakazawa - V5.0 AR7859対応 イメージ変換にアノテ有無フラグを追加
// ----V6
// 2004.06.01 - Tashiro - 文書属性・アノテ継承の実装をDocAttr.cppに集約
// 2004.10.29 - Tashiro - AR11563 BMPからヘッダ情報を取り出す関数を追加
// ----V7
// 2008.1.11 - Tashiro - ConvertBPorPDToDIBに解像度を小数で指定する版を追加
// 2008.03.13 - Tashiro - AR14268 ConvertBPorPDToDIBに白枠を付けない機能を追加
// 2008.05.27 - Tashiro - AR14867 ConvertBPorPDToDIBに17%と同様の画質で描画する引数を追加
