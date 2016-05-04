// $Archive: /DocuWorks/70/Source/mpcpd/pd3mf.h $
//
// Copyright (c) 1999-2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:26 $
// $Revision: 1.7 $

#ifndef _PD3MF_H_
#define _PD3MF_H_

#include "mpc_pd.h"
#include "ifmtattr.h"
#include "imgshk.h"

// -----------------------------------------------------------------------------------------------
// PS Patch 関係
// -----------------------------------------------------------------------------------------------

enum PSP_OS {		//稼動OS <--EnumUserDataのものと重複するが、コード変更量が多くなるのでこれで勘弁
	PSP_OS_NIL,
	PSP_OS_WIN95,
	PSP_OS_WINNT
};

struct PSPatchInfo {
	MP_PtrArray*		clipFigsInfo;
	MP_PtrArray*		maskedBmpInfo;
	DWORD				orgROP;			//Play実行時にのみ使用(元々のROP)
	DWORD				orgROP2;		//Play実行時にのみ使用(元々のROP2)
	HRGN_XD				hClipRgn;		//Play実行時にのみ使用(MASK図形から変換したクリップ領域)
	HRGN_XD				hOrgClipRgn;	//Play実行時にのみ使用(元々のクリップ領域)
	int					bTransparent;	//Play実行時にのみ使用(透過処理中かどうか)
	HBRUSH_XD				hOrgBrush;		//Play実行時にのみ使用(元々のブラシ)
	int					orgBkMode;		//Play実行時にのみ使用(元々のBkMode))
	PSP_OS				os;				//稼動OS <--EnumUserDataのものと重複するが、コード変更量が多くなるのでこれで勘弁
	const BITMAPINFO*	pBmi;
	const BYTE*			pBits;

	PSPatchInfo(MPCSession* session);
	~PSPatchInfo();
};

enum PSPPlayResult {
	PlayRes_nil = 0,
	PlayRes_NeedPlayRecord,			// このあとPlayRecord処理をすること
	PlayRes_NeedlessPlayRecord,		// このあとPlayRecord処理をしないこと
};

class WordPatchInfo {
public:
	MP_PtrArray* bitbltWithClearClipRectTable;

	enum WWLinePatchType{
		type_clearcliprect_and_draw_nil = 0,
		type_clearcliprect_and_draw_bitblt,
		type_expand_area_and_draw_bitblt,
	};

	RECTL	clearClipRect;
	HENHMETAFILE_XD hCurrentEMF;
	MP_Integer last_draw_table_index;

	WordPatchInfo(HENHMETAFILE_XD hemf);
	~WordPatchInfo();
};

class WordPatchElem{
public:
	DWORD emf_count_of_target_bitblt;
	DWORD emf_count_of_clipblock_bitblt;
	WordPatchInfo::WWLinePatchType patch_type;
	RECTL newBltBltRect;
	RECTL unClippedAreaRect;

	WordPatchElem() {
		emf_count_of_target_bitblt = 0;
		emf_count_of_clipblock_bitblt = 0;
	}
};


// for WMF
int				ParseWMFHandleForDecoratedChar(MPCSession* session, HMETAFILE_XD hmf);
int				ParseWMFBitsForDecoratedChar(MPCSession* session, void* mfBits, long bitsBytes);
int				ParseWMFHandleForClipFigure(MPCSession* session, HMETAFILE_XD hmf, PSPatchInfo* res);
int				ParseWMFBitsForClipFigure(MPCSession* session, void* mfBits, long bitsBytes, PSPatchInfo* res);
PSPPlayResult	PrePlayWMFToPS(HDC_XD hdc, METARECORD* lpmr, long counter, PSPatchInfo* info);
void			PostPlayWMFToPS(HDC_XD hdc, METARECORD* lpmr, long counter, PSPatchInfo* info);

// for EMF
int				ParseEMFHandleForDecoratedChar(MPCSession* session, HENHMETAFILE_XD hmf);
int				ParseEMFBitsForDecoratedChar(MPCSession* session, void* mfBits, long bitsBytes);
int				ParseEMFHandleForClipFigure(MPCSession* session, HENHMETAFILE_XD hmf, PSPatchInfo* res);
int				ParseEMFBitsForClipFigure(MPCSession* session, void* mfBits, long bitsBytes, PSPatchInfo* res);
PSPPlayResult	PrePlayEMFToPS(HDC_XD hdc, ENHMETARECORD* lpmr, long counter, PSPatchInfo* info);
void			PostPlayEMFToPS(HDC_XD hdc, ENHMETARECORD* lpmr, long counter, PSPatchInfo* info);

int				ParseEMFHandleForWordWhiteLine(MPCSession* session, HENHMETAFILE_XD hmf, WordPatchInfo* res);
int				ParseEMFBitsForWordWhiteLine1st(MPCSession* session, void* mfBits, long bitsBytes, WordPatchInfo* res);
int				ParseEMFBitsForWordWhiteLine2nd(MPCSession* session, void* mfBits, long bitsBytes, WordPatchInfo* res, MP_PtrArray* clipPathBlockArray);

// -----------------------------------------------------------------------------------------------
// 拡張レコード
// -----------------------------------------------------------------------------------------------

// common

enum DWImageCompressLevel {
	COMPLEVEL_LOSSLESS			= 1,
	COMPLEVEL_HIGHQUALITY		= 2,
	COMPLEVEL_STANDARD			= 3,
	COMPLEVEL_HIGHCOMPRESSION	= 4,
	COMPLEVEL_MINVALUE	= 1,
	COMPLEVEL_MAXVALUE	= 4,
};

struct MFImageData;
struct MPCSession;

extern
HRESULT CompressMfImage(MFImageData *pImage, MP_Integer level);
static
HRESULT getThinnedPixelNumber(int specified_resolution, //変換後解像度
							  int source_resolution,	//イメージデータ解像度
							  DWORD src_pixelX,			//変換前のソースピクセル数 X
							  DWORD src_pixelY,			//変換前のソースピクセル数 Y
							  MP_Dim *Thinned			//変換後のピクセル数
							  ) ;
static
HRESULT getSourceResolution(int content_resolution,		//コンテント解像度
							DWORD src_pixelX,			//変換前のソースピクセル数 X
							DWORD dest_pixelX			//デスティネーションピクセル数 X
							) ;
static
HRESULT judgeResolutionConversion(int specified_resolution, //変換後解像度
								  int source_resolution	//イメージデータ解像度
							      ) ;
static
HRESULT judgeResolutionConversion(int specified_resolution, //変換後解像度
								  int source_resolution,//イメージデータ解像度
							      int src_pixelX,		//変換前のソースピクセル数 X
								  int dest_pixelX,		//変換後のソースピクセル数 X
							      BITMAPINFO *p_bi		//BITMAPINFO へのポインタ
							      ) ;
static
HRESULT judgeDatasizeDecrease(float conversion_rate,	//解像度の変換率
							  BITMAPINFO *p_bi			//BITMAPINFO へのポインタ
							  ) ;
static
HRESULT isMonochromePalette(DWORD *p) ;
static
HRESULT shrinkBitmap(ImageShrink *shk,					//変換パラメータへのポインタ
					 ImageShrinkPack *pack,
					 BITMAPINFO *p_bi,					//BITMAPINFO へのポインタ
					 MP_Dim *Thinned,					//変換後のピクセル数
					 BYTE *p_bmp						//ビットマップへのポインタ
					 ) ;

// WMF

#pragma pack(push, mr_extend, 2) // adjust alignment

struct METAESCAPE
{
	DWORD	rdSize;
	WORD	rdfunction;
	WORD	mfComment;
	WORD	extSize;
	DWORD	extFunction;
};

struct DWMRSETDIB
{
	DWORD	rdSize;
	WORD	rdFunction;
	WORD	mfComment;
	WORD	extSize;
	DWORD	extFunction;

	WORD	cbBmi;
	DWORD	cbBits;
};

struct DWMRSETJPEG
{
	DWORD	rdSize;
	WORD	rdFunction;
	WORD	mfComment;
	WORD	extSize;
	DWORD	extFunction;
};

struct DWMRSTRETCHDIBREF
{
	DWORD	rdSize;
	WORD	rdFunction;
	WORD	mfComment;
	WORD	extSize;
	DWORD	extFunction;

	short	xDest;
	short	yDest;
	short	cxDest;
	short	cyDest;
	short	xSrc;
	short	ySrc;
	short	cxSrc;
	short	cySrc;
	DWORD	dwRop;
};
#pragma pack(pop, mr_extend)

enum {
	DW_ESC_STRETCHDIB_REUSE	= 0x00015744,	// DWPrnで作成
	DW_ESC_JPEG_REUSE		= 0x01015744,
	DW_ESC_MASK_DIB			= 0x02015744,
	DW_ESC_SETDIB			= 0x00025744,	// PDで作成
	DW_ESC_SETJPEG			= 0x01025744,
	DW_ESC_STRETCHDIB_REF	= 0x02025744,
	DW_ESC_POLYPOLYPATBLT	= 0x03025744,

	DW_STRETCHDIB_JPEG		= 0x00005744,	// DWPrnで作成
};

struct RecordInfo {
	METARECORD *pmr;
	int type;
};

class CReduceWMF {
private:
	MPCSession *m_session;
	int m_nRecord;
	int m_totalSize; // WORD size
	int m_iStretchDIB; // previous ESCAPE or STRETCHDIB
	int m_level;
	int m_nJpeg ;					//外部イメージで登録してある JPEG 数
	int m_nNewJpeg ;				//DIB から生成した JPEG 数
	int m_bResolution ;				//再圧縮か解像度変換か
	int m_content_resolution ;		//コンテントの解像度
	int	m_specified_resolution ;	//解像度変換での変換率

	HANDLE m_hMfFile;
	HANDLE m_hImageFile;
	MFImageData *m_image;
	RecordInfo *m_aInfo;

	HRESULT check(HMETAFILE_XD hmf);
	int checkEscape(int n);
	int checkEscapeJpegFragment(int n);
	int checkStretchDIB(int n);
//	HRESULT reduce(HMETAFILE hmf);
	HRESULT reduce(HMETAFILE_XD hmf,
				   MFImageData *pImage					//外部イメージへのポインタ
				   ) ;
	int reducePatBlt(int first, HRESULT *phres);
	int reduceClippedStretchDIB(int first, BOOL_XD bFirstClip, HRESULT *phres);
//	int reduceStretchDIB(int n, HRESULT *phres);
	int reduceMaskedStretchDIB(int first, HRESULT *phres);
	int reduceMaskedJpeg(int first, HRESULT *phres);
	int reduceStretchDIBJpeg(int first, HRESULT *phres);
	int reduceReuseJpeg(int n, HRESULT *phres);
	HRESULT putMR(int n);
//	HRESULT putDWMRSetDIB(int n);
//	HRESULT putDWMRSetJPEG(int n);
//	HRESULT putDWMRStretchDIBRef(int n, int ROP);
	int reduceStretchDIB(int n,
						 HRESULT *phres,
						 MP_Integer *last_def,			//最後が JPEG か DIB かを識別
						 unsigned int *ref_count,		//参照カウンタ
						 MP_Integer *last_dib_number,	//最後の DIB レコード番号
						 int *doneResolutionConversion,	//解像度変換を行ったか否か
						 MFImageData *pImage			//外部イメージへのポインタ
						 ) ;
	HRESULT putDWMRSetDIB(int n,						//メタレコード番号
						  int *doneResolutionConversion = NULL //解像度変換有無
						  ) ;
	HRESULT putDWMRSetJPEG(int n,						//メタレコード番号
						   int *doneResolutionConversion = NULL //解像度変換有無
						   ) ;
	HRESULT putDWMRStretchDIBRef(int n,					//メタレコード番号
								 int ROP,				//ROP
								 int *doneResolutionConversion = NULL //解像度変換有無
								 ) ;
	HRESULT putDWMRSetDIBRecord(int bmpinfo_size,		//BITMAPINFO のサイズ
								BYTE *pBI,				//BITMAPINFO へのポインタ
								int bmp_size,			//ビットマップのサイズ
								BYTE *pDIB				//ビットマップへのポインタ
								) ;
	HRESULT putDWMRSetJPEGRecord(int bmpinfo_size,		//BITMAPINFO のサイズ
								  BITMAPINFOHEADER *pbih,//BITMAPINFOHEADER へのポインタ
								  int bmp_size,			//ビットマップのサイズ
								  BYTE *pDIB			//ビットマップへのポインタ
								  ) ;
	HRESULT putDWMRThinRef(MP_Integer *last_dib_number,	//DIB データの番号
						   MFImageData *pImage,			//外部イメージデータへのポインタ
						   MP_Integer n,				//メタレコード番号
						   MP_Integer *last_def,		//最後に描画したビットマップデータ
						   unsigned int *ref_count,		//DWEMRSTRETCHDIBITSREF のカウンタ
						   int *doneResolutionConversion//解像度が変換された?
						   ) ;
	HRESULT putDWMRThinJPEG(MFImageData *pImage,		//外部イメージデータへのポインタ
							MP_Integer n,				//メタレコード番号
							int *doneResolutionConversion //解像度が変換された?
							) ;
	HRESULT putDWMRThinDIB(MP_Integer *last_dib_number,	//DWEMRSETDIB の番号
						   MP_Integer n,				//メタレコード番号
						   int *doneResolutionConversion //解像度が変換された?
						   ) ;
	HRESULT putMRThinDIB(MP_Integer n,					//メタレコード番号
						 int *doneResolutionConversion	//解像度が変換された?
						 ) ;
public:
	CReduceWMF(MPCSession *session) : m_session(session), m_aInfo(0) {}
	~CReduceWMF() { if (m_aInfo) delete [] m_aInfo; }
//	HRESULT Convert(HMETAFILE *hmf, MFImageData *pImage, int level);
	HRESULT Convert(HMETAFILE_XD *phmf,					//MetaFile ハンドルへのポインタ
					MFImageData *pImage,				//外部イメージへのポインタ
					int level,							//圧縮レベル
					MP_Integer content_resolution,		//コンテント解像度
					MP_Integer specified_resolution,	//変換後解像度
					BOOL_XD bResolution					//再圧縮か解像度変換か
					) ;
};

// EMF

enum {
	GDICOM_DW					= 0x00005744,
	GDICOM_MASK_DW				= 0x0000ffff,
	GDICOM_MASK_TYPE			= 0x00ffffff,

	GDICOM_POLYLINETO			= 0x00005744,	// DWPrnで作成
	GDICOM_POLYLINETOB			= 0x00015744,
	GDICOM_POLYLINETOC			= 0x00025744,
	GDICOM_POLYLINETOBC			= 0x00035744,

	GDICOM_POLYBEZTO			= 0x00105744,
	GDICOM_POLYBEZTOB			= 0x00115744,
	GDICOM_POLYBEZTOC			= 0x00125744,
	GDICOM_POLYBEZTOBC			= 0x00135744,

	GDICOM_POLYGON				= 0x00205744,
	GDICOM_POLYLINE				= 0x00405744,
	GDICOM_POLYBEZIER			= 0x00505744,

	GDICOM_CLIPFLAG				= 0x31305744,
	GDICOM_BEGINPATH			= 0x32305744,
	GDICOM_SELECTCLIPPATH		= 0x33305744,
	GDICOM_FILLPATH				= 0x34305744,
	GDICOM_STROKEPATH			= 0x35305744,
	GDICOM_CLIPRECT				= 0x36305744,

	GDICOM_SETDIB				= 0x00615744,	// PDで作成
	GDICOM_SETJPEG				= 0x00625744,
	GDICOM_STRETCHDIBITSREF		= 0x00635744,
};

struct DWEMRSETDIB
{
	EMR		emr;		// 拡張レコード共通部
	DWORD	cbData;		//
	DWORD	iTypeExt;	//

	DWORD	offBmi;
	DWORD	cbBmi;
	DWORD	offBits;
	DWORD	cbBits;
};

struct DWEMRSETJPEG
{
	EMR		emr;
	DWORD	cbData;
	DWORD	iTypeExt;
};

struct DWEMRSTRETCHDIBITSREF
{
	EMR		emr;
	DWORD	cbData;
	DWORD	iTypeExt;

	RECTL	rclBounds;
	LONG	xDest;
	LONG	yDest;
	LONG	xSrc;
	LONG	ySrc;
	LONG	cxSrc;
	LONG	cySrc;
	DWORD	iUsage;
	DWORD	dwRop;
	LONG	cxDest;
	LONG	cyDest;
};

struct EmfRecordInfo {
	const ENHMETARECORD *pmr;
	int type;
};

class CReduceEMF {
private:
	MPCSession *m_session;
	int m_nRecord;
	int m_totalSize;
	int m_nOutRecord;
	int m_iEmrStretchDIBits; // previous StretchDIBits
	int m_level;
	int m_nJpeg ;					//外部イメージで登録してある JPEG 数
	int m_nNewJpeg ;				//DIB から生成した JPEG 数
	int m_bResolution ;				//サイズ削減か解像度変換か
	int m_content_resolution ;		//コンテントの解像度
	int	m_specified_resolution ;	//変換後の解像度

	HANDLE m_hMfFile;
	HANDLE m_hImageFile;
	MFImageData *m_image;
	EmfRecordInfo *m_aInfo;

	HRESULT check(HENHMETAFILE_XD hmf);
//	HRESULT check(HENHMETAFILE hmf, BOOL_XD bResolution = 0) ;	//解像度変換 修正
	int checkStretchDIBits(int n);
/* 7/12 public へ
	HRESULT reduce();
*/
	HRESULT reduce(MFImageData *pImage						//外部イメージデータへのポインタ
				   ) ;
	HRESULT putDWEMRSetDIB(int n,
						   int *doneResolutionConversion	//解像度が変換された?
						   );
	HRESULT putDWEMRSetJPEG(int n,
							int *doneResolutionConversion	//解像度が変換された?
							);
	HRESULT putDWEMRStretchDIBitsRef(int n,
									 int doneResolutionConversion	//解像度が変換された?
									 );
	HRESULT putDWEMRSetDIBRecord(int bmpinfo_size,			//BITMAPINFO のサイズ
								 BYTE *pBI,					//BITMAPINFO へのポインタ
								 int bmp_size,				//ビットマップのサイズ
								 BYTE *pDIB					//ビットマップへのポインタ
								 ) ;
	HRESULT putDWEMRSetJPEGRecord(int bmpinfo_size,			//BITMAPINFO のサイズ
								  BITMAPINFOHEADER *pbih,	//BITMAPINFO へのポインタ
								  int bmp_size,				//ビットマップのサイズ
								  BYTE *pDIB				//ビットマップへのポインタ
								  ) ;

/* 7/12 public へ											//解像度変換 追加
	HRESULT thin(MFImageData *pImage,						//外部イメージデータへのポインタ
				 MP_Integer resolution,						//解像度
				 MP_Integer param							//変換パラメータ
				 ) ;
*/
	HRESULT putDWEMRThinRef(MP_Integer last_dib_number,		//DIB データの番号
							MFImageData *pImage,			//外部イメージデータへのポインタ
							MP_Integer n,					//メタレコード番号
							MP_Integer last_def,			//最後に描画したビットマップデータ
							unsigned int ref_count,			//DWEMRSTRETCHDIBITSREF のカウンタ
							int *doneResolutionConversion	//解像度が変換された?
							) ;
	HRESULT putDWEMRThinJPEG(MFImageData *pImage,			//外部イメージデータへのポインタ
							 MP_Integer n,					//メタレコード番号
							 int *doneResolutionConversion	//解像度が変換された?
							 ) ;
	HRESULT putDWEMRThinDIB(MP_Integer last_dib_number,		//DWEMRSETDIB の番号
							MP_Integer n,					//メタレコード番号
							int *doneResolutionConversion	//解像度が変換された?
							) ;
	HRESULT putEMRThinDIB(MP_Integer n						//メタレコード番号
						  ) ;

public:
	CReduceEMF(MPCSession *session) : m_session(session), m_aInfo(0) {}
	~CReduceEMF() { if (m_aInfo) delete [] m_aInfo; }
/* 7/12
	HRESULT Convert(HENHMETAFILE *hemf, MFImageData *pImage, int level);
*/
/* 7/19 private へ
	HRESULT reduce(MFImageData *pImage						//外部イメージデータへのポインタ
				   ) ; */
/* 7/19 reduce と共通に出来るので削除
	HRESULT thin(MFImageData *pImage						//外部イメージデータへのポインタ
				 ) ; */
/* 7/19 reduce, thin 共通化により関数ポインタは削除
	HRESULT Convert(HRESULT (CReduceEMF::*func)(MFImageData *pImage),
					HENHMETAFILE *phmf,						//MetaFile ハンドルへのポインタ */
	HRESULT Convert(HENHMETAFILE_XD *phmf,						//MetaFile ハンドルへのポインタ
					MFImageData *pImage,					//外部イメージデータへのポインタ
					int level,								//圧縮レベル
					MP_Integer content_resolution,			//コンテント解像度
					MP_Integer specified_resolution,		//変換後解像度
					BOOL_XD bReduce							//サイズ削減か解像度変換か
					) ;
/* 7/12														//解像度変換 追加
	HRESULT ThinImageData(HENHMETAFILE *phmf,				//MetaFile ハンドルへのポインタ
						  MFImageData *pImage,				//外部イメージデータへのポインタ
						  MP_Integer resolution,			//解像度
						  MP_Integer param,					//変換パラメータ
						  int level							//圧縮レベル
						  ) ;
*/
};

// -----------------------------------------------------------------------------------------------
// MetaFile PD
// -----------------------------------------------------------------------------------------------

#define MFPD_PLAY_UNIT_MIN	10000
#define MFPD_PLAY_UNIT_MAX	20000
#define MFPD_PLAY_TIME		  500 // 描画間隔(時間、ms)

enum MFPD_Output {	//メタファイル出力先
	MFPD_OUTPUT_NIL = 0,
	MFPD_OUTPUT_DISPLAY,
	MFPD_OUTPUT_PRINTER,
};
enum MFPD_Apl {		//生成アプリ識別子
	MFPD_APL_NIL = 0,
	MFPD_APL_MS_WORD,
	MFPD_APL_MS_EXCEL,
	MFPD_APL_MS_POWERPOINT,
	MFPD_APL_LOTUS_123,
	MFPD_APL_LOTUS_FREELANS,
	MFPD_APL_ICHITARO6,
	MFPD_APL_ICHITARO7,
	MFPD_APL_ICHITARO8,
	MFPD_APL_OASYS
};
enum MFPD_OS {		//稼動OS
	MFPD_OS_NIL = 0,
	MFPD_OS_WIN95,
	MFPD_OS_WINNT
};

// AR12815対応 描画矯正フラグ
// ビットフラグを用いるため、追加するときにはビットが被らないようにすること。
// フラグをセットするときには"|="を用いる。
// フラグをクリアするときには"&= ~"を用いる。
// フラグを確認するときには"&"を用いる。
const DWORD MFPD_REFORM_NIL			= (0x00000000L);
const DWORD MFPD_REFORM_THINPOLYGON	= (0x00000001L);

// 外部イメージデータ
struct MFImageData {
	int nData;
	BYTE **ptr;
	HRESULT setN(int n);
	int getN() { return nData; }
	HRESULT setJpeg(int n, int cbData, void *pData);
	HRESULT setJpeg(int n, int cx, int cy, int cbJpeg, void *pJpeg);
	void free();
	MFImageData() : nData(-1), ptr(NULL) {}
	~MFImageData() { free(); }
};

// 外部JPEGデータ
struct MFJpegData {
	DWORD cbData;
	DWORD iType;
	DWORD cxDest;
	DWORD cyDest;
};

//
struct DIBOBJECT {
	enum Mode {
		NONE = 0, DIB = 1, JPEG = 2,
	} mode;
	BOOL_XD bAlloc;
	BITMAPINFO *pBmi;
	BYTE *pBits;

	void free() {
		if (bAlloc) delete [] (BYTE*)pBmi;
		mode = NONE; bAlloc = FALSE; pBmi = 0; pBits = 0;
	}
	BOOL_XD alloc(int cbBmi, int cbBits) {
		pBmi = (BITMAPINFO*) new BYTE [cbBmi + cbBits];
		if (pBmi == NULL) return FALSE;
		bAlloc = TRUE; pBits = (BYTE*)pBmi + cbBmi;
		return TRUE;
	}
	void setPtr(BITMAPINFO *pBmi_, int cbBmi) {
		pBmi = pBmi_; pBits = (BYTE*)pBmi_ + cbBmi;
	}
	DIBOBJECT() {
		mode = NONE; bAlloc = FALSE; pBmi = 0; pBits = 0;
	}
	~DIBOBJECT() { free(); }
};

class MfpdPathData;
class WordPatchInfo;
struct EnumUserData {	// メタファイルプレイ時に渡すユーザデータ
	// 描画用
	HPALETTE			hPal;			// パレットハンドル(EMF用)
	HPALETTE			hPalOld;		// パレットハンドル(EMF用)
	BOOL_XD				bForceBGPalette;// バックグラウンドパレットを使用するか(EMF用)
	BOOL_XD				bDisablePalette;// V62 AR12160 パレットに関するレコードを実行しない
	MP_PtrArray*		pStackArray;	// 座標保存のスタック (DrawToWMF用)
	MP_Integer			angle;			// ページの回転角(回転用)
	POINT				worg;			// WindowOrg(回転用)
	SIZE				wext;			// WindowExt(回転用)
	MFImageData*		pImage;			// 外部イメージデータ
	MP_Integer			currentImage;	// 注目している外部イメージデータのイメージ番号
	DIBOBJECT			dibobj;			// ビットマップの再利用
	MP_DeviceUtilities*	pDevUtil;		// JPEG直接送信用
	MPCSession*			session;		// session

	// 画質障害対策用
	MFPD_Output			output;			// 出力先、印刷か表示か
	MFPD_Apl			apl;			// メタファイルを吐き出したアプリケーション識別
	MFPD_OS				os;				// 現在稼働中のOS種別
	LANGID				lang;			// UserDefaultLangID
	BOOL_XD				bNeedTransparent;// 透過処理が必要かどうか
	BOOL_XD				bPermeable;		// 透過content用
	BOOL_XD				bPostscript;	// Postscriptプリンタかどうか
	PSPatchInfo*		psPatchInfo;	// PSパッチ情報
	BOOL_XD				complexClippedDIB;	// クリップされたStretchDIBの情報(EMF用)
	MP_Integer			preDstYExt;		// StretchDIBits のパッチ用
	MP_Integer			preDestY;		// StretchDIBits のパッチ用
	// V60 AR5286
	MP_Integer			drawRatio;		// フォント描画時の比率
	// V60 図形文字の表示改善
	BOOL_XD				bSmoothDraw;	// なめらかな描画をするかどうか
	MfpdPathData*		pathData;		// パスの頂点の情報を保存
	// AR12815対応
	DWORD				drawReform;		// 描画矯正用のフラグ。ビットフラグを使用する。

	// 逐次描画用
	MP_Integer			counter;		// 現在何番目のレコードか
	MP_Integer			recordNum;		// メタファイルの全レコード数(概数)
	MP_Integer			playUnit;		// 逐次表示および印刷キャンセルコールバックのタイミング
	MPC_AdvCancelInfo*	callbackInfo;	// 印刷中断用コールバック情報
	BOOL_XD				isKillThrd;		// スレッドを殺すかどうか
	HANDLE				hThrd;			// スレッドのハンドル
	HANDLE				hEventStartThrd;// イベント：別スレッドを開始・再開
	HANDLE				hEventStopThrd;	// イベント：別スレッドが停止可能
	DWORD				preTime;		// キャッシュ作成スレッドの更新時間
	BOOL_XD				bCanceled;		// キャンセル要求があったかどうか(OnDrawToPrinter用)
	BOOL_XD				bEMFFromFile;	// V506 AR8283 ファイルから取得したEMFハンドルかどうかのフラグ

	int                 iContrastMode;  // V7 ハイコントラスト描画モード
	unsigned char       ForeColor[3];   // 前面色 RGB順
	unsigned char       BackColor[3];   // 背景色 RGB順

	WordPatchInfo*		wordPatchInfo;  // V7 AR13942 Word白線パッチ
	
	EnumUserData() : pImage(0), pathData(0), iContrastMode(MPC_CONTRAST_DRAW_NONE), wordPatchInfo(0) {}
	void Initialize();
};

struct MFPD_WindowInfo { // ウィンドウの情報
	int		mm;		//マップモード
	POINT	worg;	//WindowOrg
	SIZE	wext;	//WindowExt
	POINT	vorg;	//ViewportOrg
	SIZE	vext;	//ViewportExt
	XFORM	xform;	//NT用
};

struct MFPD_EnumMFParam { // 別スレッドで MPF_EnumMetaFile に引数を渡すための構造体
	HDC_XD			hBmpDC;
	HMETAFILE_XD	hMF;
	MFENUMPROC_XD	pFunc;
	LPARAM		lParam;
};

struct MFPD_EnumEnhMFParam { // 別スレッドで MPF_EnumEnhMetaFile に引数を渡すための構造体
	HDC_XD				hBmpDC;
	HENHMETAFILE_XD	hMF;
	ENHMFENUMPROC_XD	pFunc;
	LPVOID			lpData;
	CONST RECT*		lpRect;
};


class MP_ImplWMFPD;

class ImplWMFPD : public MP_PD
{
public:
	ImplWMFPD(MPCSession* session);
	STDMETHOD(Destroy)() ;

	HRESULT Create(METAFILEPICT_XD wmf);
	HRESULT Load(IStgObject* stgobj, const MP_AName* aname, MP_Octet* his_adata, MP_Integer his_asize);
	STDMETHOD(Save)(IStgObject* stgobj, const MP_AName* aname = NULL) ;

	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;

	// AR5442対応：実装を.cppファイルに移動
	STDMETHOD(OnDraw)(MP_Canvas* canvas, MP_Integer bPart = 0);
	STDMETHOD(OnPrint)(MP_Canvas* canvas, MPC_AdvCancelInfo* info = NULL);

	STDMETHOD(CanRotate)(MP_Integer degree) {return MP_S_OK;}
	STDMETHOD(Rotate)(MP_Integer degree);
	STDMETHOD_(MP_PD*, CreateIconPD)(HRESULT* phres);
	STDMETHOD_(void, DeletePDCash)(HRESULT* phres) ;
	STDMETHOD(GetPDInfo)(MP_Integer* org, MP_Integer* compLevel, MP_Integer* depth, MP_Dim* mdim);

	STDMETHOD(ConvertToDIBHeader)(BITMAPINFOHEADER* bmiHeader) {return MP_E_NOTIMPL;}
	STDMETHOD(ConvertToDIBHandle)(HGLOBAL hDIB=NULL)  {return MP_E_NOTIMPL;};
	STDMETHOD(ConvertToDIBFile)(MP_Path* dibfilepath)  {return MP_E_NOTIMPL;};
	//n V4 追加分
	STDMETHOD(ConvertToDIBHandleAdv)(HGLOBAL hDIB = NULL, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(ConvertToDIBFileAdv)(MP_Path* dibfilepath, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(ConvertToDIBHeaderAdv)(BITMAPINFOHEADER* bmiHeader, BOOL_XD bRotate = TRUE) {return MP_E_NOTIMPL;};
	STDMETHOD(GetCompDataToFile)(MP_Path* dstPath, MP_Integer* compDataType = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(GetCompDataToHandle)(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(CompressImage)(MP_Integer level);
	STDMETHOD(ThinImage)(MP_Integer level, MP_Integer specifiedResolution = 0);
	STDMETHOD_(MP_Integer, GetColorType)(BOOL_XD bCheck = TRUE);

	STDMETHOD(RotateOnMem)(MP_Integer degree) { return MP_E_NOTIMPL; }

	STDMETHOD(ConvertToDIBFileW)(const MP_WPath* dibfilepath) { return MP_E_NOTIMPL; }
	STDMETHOD(ConvertToDIBFileAdvW)(const MP_WPath* dibfilepath, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) { return MP_E_NOTIMPL; }
	STDMETHOD(GetCompDataToFileW)(const MP_WPath* dstPath, MP_Integer* compDataType = NULL) { return MP_E_NOTIMPL; }

	//MP_WMFPDのI/F
	STDMETHOD_(HMETAFILE_XD, GetWMFHandle)(LONG *mm = NULL, LONG *xExt = NULL, LONG *yExt = NULL) ;
	STDMETHOD(GetText)(MP_Text* pbuffer, int cchbuffer);

private:
	MPCSession*		m_session;
	IStgObject*		m_stgobj;
	MP_AName*		m_aname;
	MP_ImplWMFPD*	m_mp_wmfpd_if;
	MFPD_OS			m_os;
	MP_Integer		m_bPatchInvalid;
	MP_Integer		m_colorType;	// カラー/モノクロ判定

	// PDの属性
	METAFILEPICT_XD	m_mfpict;
	long			m_opaque;
	MP_Integer		m_level;		// イメージの圧縮レベル

	// コンテントの属性
	MP_Integer		m_degree;		// 回転角
	MFPD_Apl		m_apl;
	MP_Integer		m_recordNum;
	MFImageData		m_image;		// 外部イメージデータ
	MP_Integer		m_resolution ;	// 解像度		//解像度変換 追加

	// OnDraw用
	SIZE			m_cacheSize;
	HDC_XD				m_hBmpDC;
	HBITMAP_XD			m_cacheBmp;
	HPALETTE		m_hPal;
	HGDIOBJ_XD			m_hOldBmp;
	HPALETTE		m_hOldPal;
	MFPD_WindowInfo	m_winInfo;
	EnumUserData	m_ud;
	MFPD_EnumMFParam	m_thPar;	// 別スレッドで MPF_EnumMetaFile するために必要な情報

	STDMETHOD(DrawToMetaFile)(MP_Canvas* canvas) ;
	STDMETHOD(DrawToDisplay)(MP_Canvas* canvas, MP_Integer bPart) ;
	STDMETHOD(DrawToPrinter)(MP_Canvas* canvas, long isPrint, MPC_AdvCancelInfo* info) ;
	STDMETHOD_(MP_Integer, GetDegree)() ;
	STDMETHOD(RotateCacheBmp)(MP_Integer cacheDegree);
	STDMETHOD_(void, ClearBackGround)(HDC_XD hDC, MP_Rect* rect);

	// 表示関連
	STDMETHOD(DrawInternal)(MP_Canvas* canvas, long isPrint, MP_Integer bPart=0, MPC_AdvCancelInfo* info=NULL);
	STDMETHOD(DrawToDisplayDirect)(MP_Canvas* canvas);
	STDMETHOD(DrawToDisplayWithCacheFirst)(MP_Canvas* canvas, MP_Integer bPart);
	STDMETHOD(DrawToDisplayWithCacheSecond)(MP_Canvas* canvas);
	STDMETHOD_(BOOL_XD, IsFirstDrawOrResize)(MP_Canvas* canvas);
	STDMETHOD_(BOOL_XD, CanCreateCache)(MP_Canvas* canvas);
	STDMETHOD(CreateCacheBmp)(MP_Canvas* canvas);
	STDMETHOD_(void, DeleteCacheBmp)();
	STDMETHOD_(void, DeleteBmpDC)();
	STDMETHOD_(void, BltCacheBmp)(MP_Canvas* canvas);
	STDMETHOD_(SIZE, CalcMFLogicalSize)(MP_Canvas* canvas);
	STDMETHOD_(SIZE, CalcMFDeviceSize)(MP_Canvas* canvas);
	STDMETHOD_(POINT, CalcMFLogicalPoint)(MP_Canvas* canvas);
	STDMETHOD_(POINT, CalcMFDevicePoint)(MP_Canvas* canvas);
	STDMETHOD_(void, PrepareDisplayDC)(MP_Canvas* canvas);
	STDMETHOD_(void, CleanupDisplayDC)(MP_Canvas* canvas);

#ifndef _M3CORE_MP_
	STDMETHOD(CreateEventAndThread)(HDC_XD hdc);
	STDMETHOD_(void, CloseEventAndThread)();
	STDMETHOD(WaitThread)();
	STDMETHOD(KillThread)();
#endif

	STDMETHOD(LoadImageData)();
	STDMETHOD(SaveImageData)(IStgObject* stgobj, const MP_AName* aname);
	STDMETHOD(CompressJpeg)(MP_Integer level);
	STDMETHOD(CompressWMF)(MP_Integer level);

	MPC_BigAlloc*	m_allocator;
	STDMETHOD_(void*, MPBigAlloc)(unsigned int nSize) {
		if (nSize <= 0 || m_allocator == NULL) return NULL;
		return m_allocator->Allocate(nSize);
	};
	STDMETHOD(MPBigFree)(void* p) {
		if (m_allocator == NULL) return MP_E_INVALIDARG;
		return m_allocator->Free(p);
	};
	//17%サムネールと同じように、大きく描いて縮小、エッジ強調する
	HRESULT DrawLargeThenShrink(MP_Canvas* canvas);
};

class MP_ImplEMFPD;

class ImplEMFPD : public MP_PD
{
public:
	ImplEMFPD(MPCSession* session);
	virtual ~ImplEMFPD();
	
	STDMETHOD(Destroy)() ;

	HRESULT Create(HENHMETAFILE_XD hemf);
	HRESULT Load(IStgObject* stgobj, const MP_AName* aname, MP_Octet* his_adata, MP_Integer his_asize);
	STDMETHOD(Save)(IStgObject* stgobj, const MP_AName* aname = NULL) ;

	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;

	// AR5442対応：実装を.cppファイルに移動
	STDMETHOD(OnDraw)(MP_Canvas* canvas, MP_Integer bPart = 0);
	STDMETHOD(OnPrint)(MP_Canvas* canvas, MPC_AdvCancelInfo* info = NULL);

	STDMETHOD_(MP_PD*, CreateIconPD)(HRESULT* phres);
	STDMETHOD_(void, DeletePDCash)(HRESULT* phres) ;

	STDMETHOD(CanRotate)(MP_Integer degree) { return MP_S_OK; }
	STDMETHOD(Rotate)(MP_Integer degree);
	STDMETHOD(GetPDInfo)(MP_Integer* org, MP_Integer* compLevel, MP_Integer* depth, MP_Dim* mdim);
	STDMETHOD_(void, SetAplID)(MP_Integer id) {m_apl = (MFPD_Apl)id;};
	STDMETHOD_(void, SetRecordNum)(MP_Integer num) {m_recordNum = num;};

	STDMETHOD(ConvertToDIBHeader)(BITMAPINFOHEADER* bmiHeader) { return MP_E_NOTIMPL; }
	STDMETHOD(ConvertToDIBHandle)(HGLOBAL hDIB=NULL)  {return MP_E_NOTIMPL;};
	STDMETHOD(ConvertToDIBFile)(MP_Path* dibfilepath)  {return MP_E_NOTIMPL;};

	//n
	STDMETHOD(ConvertToDIBHandleAdv)(HGLOBAL hDIB = NULL, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(ConvertToDIBFileAdv)(MP_Path* dibfilepath, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(ConvertToDIBHeaderAdv)(BITMAPINFOHEADER* bmiHeader, BOOL_XD bRotate = TRUE) {return MP_E_NOTIMPL;};
	STDMETHOD(GetCompDataToFile)(MP_Path* dstPath, MP_Integer* compDataType = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(GetCompDataToHandle)(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL) {return MP_E_NOTIMPL;};
	STDMETHOD(CompressImage)(MP_Integer level);
	STDMETHOD(ThinImage)(MP_Integer level, MP_Integer specifiedResolution = 0);
	STDMETHOD_(MP_Integer, GetColorType)(BOOL_XD bCheck = TRUE);

	STDMETHOD(RotateOnMem)(MP_Integer degree) { return MP_E_NOTIMPL; }

	STDMETHOD(ConvertToDIBFileW)(const MP_WPath* dibfilepath) { return MP_E_NOTIMPL; }
	STDMETHOD(ConvertToDIBFileAdvW)(const MP_WPath* dibfilepath, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) { return MP_E_NOTIMPL; }
	STDMETHOD(GetCompDataToFileW)(const MP_WPath* dstPath, MP_Integer* compDataType = NULL) { return MP_E_NOTIMPL; }

	//MP_EMFPDのI/F
	STDMETHOD_(HENHMETAFILE_XD,GetEMFHandle)() ;
	STDMETHOD(SetEMF)(HENHMETAFILE_XD hemf);

private:
	MPCSession*		m_session;
	IStgObject*		m_stgobj;
	MP_AName*		m_aname;
	MP_ImplEMFPD*	m_mp_emfpd_if;
	MFPD_OS			m_os;
	MP_Integer		m_bPatchInvalid;
	MP_Integer		m_colorType;	// カラー/モノクロ判定

	// PDの属性
	HENHMETAFILE_XD	m_hemf;		//拡張メタファイルハンドル
	long			m_xExt;		//PDの幅(0.01mm単位)
	long			m_yExt;		//PDの高さ(0.01mm単位)
	long			m_opaque;
	MP_Integer		m_level;		// イメージの圧縮レベル

	// コンテントの属性
	MP_Integer		m_degree;		// 回転角
	MFPD_Apl		m_apl;
	MP_Integer		m_recordNum;
	MFImageData		m_image;		// 外部イメージデータ
	MP_Integer		m_resolution ;	// 解像度		//解像度変換 追加

	// OnDraw用
	SIZE			m_cacheSize;
	RECT			m_rect;
	HDC_XD				m_hBmpDC;
	HBITMAP_XD			m_cacheBmp;
	HPALETTE		m_hPal;
	HGDIOBJ_XD			m_hOldBmp;
	HPALETTE		m_hOldPal;
	MFPD_WindowInfo	m_winInfo;
	EnumUserData	m_ud;
	MFPD_EnumEnhMFParam	m_thPar;	// 別スレッドで MPF_EnumMetaFile するために必要な情報
	WordPatchInfo*	m_pWordPatchInfo;	// V7 AR13942 Word白線パッチ

	STDMETHOD(DrawInternal)(MP_Canvas* canvas, long isPrint, MP_Integer bPart=0, MPC_AdvCancelInfo* info=NULL) ;
	STDMETHOD(DrawToWMF)(MP_Canvas* canvas) ;
	STDMETHOD(DrawToPrinter)(MP_Canvas* canvas, long isPrint, MPC_AdvCancelInfo* info) ;
	STDMETHOD_(MP_Integer, GetDegree)() ;
	STDMETHOD(RotateCacheBmp)(MP_Integer cacheDegree);
	STDMETHOD_(void, ClearBackGround)(HDC_XD hDC, MP_Rect* rect);
	STDMETHOD_(void, InitEnumUserData)(EnumUserData* ud, BOOL_XD bDrawAdvance);
	STDMETHOD_(void, CleanupEnumUserData)(EnumUserData *ud);

	// 表示関連
	STDMETHOD(DrawToDisplay)(MP_Canvas* canvas, MP_Integer bPart) ;
	STDMETHOD(DrawToDisplayDirect)(MP_Canvas* canvas);
	STDMETHOD(DrawToDisplayWithCacheFirst)(MP_Canvas* canvas, MP_Integer bPart);
	STDMETHOD(DrawToDisplayWithCacheSecond)(MP_Canvas* canvas);
	STDMETHOD_(BOOL_XD, IsFirstDrawOrResize)(MP_Canvas* canvas);
	STDMETHOD_(BOOL_XD, CanCreateCache)(MP_Canvas* canvas);
	STDMETHOD(CreateCacheBmp)(MP_Canvas* canvas);
	STDMETHOD_(void, DeleteCacheBmp)();
	STDMETHOD_(void, DeleteBmpDC)();
	STDMETHOD_(void, BltCacheBmp)(MP_Canvas* canvas);
	STDMETHOD_(SIZE, CalcMFLogicalSize)(MP_Canvas* canvas);
	STDMETHOD_(SIZE, CalcMFDeviceSize)(MP_Canvas* canvas);
	STDMETHOD_(POINT, CalcMFLogicalPoint)(MP_Canvas* canvas);
	STDMETHOD_(POINT, CalcMFDevicePoint)(MP_Canvas* canvas);
	STDMETHOD_(void, PrepareDisplayDC)(MP_Canvas* canvas);
	STDMETHOD_(void, CleanupDisplayDC)(MP_Canvas* canvas);

#ifndef _M3CORE_MP_
	STDMETHOD(CreateEventAndThread)(HDC_XD hdc);
	STDMETHOD_(void, CloseEventAndThread)();
	STDMETHOD(WaitThread)();
	STDMETHOD(KillThread)();
#endif

	STDMETHOD(LoadImageData)();
	STDMETHOD(SaveImageData)(IStgObject* stgobj, const MP_AName* aname);
	STDMETHOD(CompressJpeg)(MP_Integer level);
	STDMETHOD(CompressEMF)(MP_Integer level);

	MPC_BigAlloc*	m_allocator;
	STDMETHOD_(void*, MPBigAlloc)(unsigned int nSize) {
		if (nSize <= 0 || m_allocator == NULL) return NULL;
		return m_allocator->Allocate(nSize);
	};
	STDMETHOD(MPBigFree)(void* p) {
		if (m_allocator == NULL) return MP_E_INVALIDARG;
		return m_allocator->Free(p);
	};
	
	// 09.07.14 - M.Chikyu UNICODE対応
	/*
	char * m_pszTempEmfPath; // V506 AR8283
	STDMETHOD_(BOOL_XD, GetTempEmfPath)(char * pDst);
	*/
	MP_WPath * m_pszTempEmfPathW; // V506 AR8283
	STDMETHOD_(BOOL_XD, GetTempEmfPathW)(MP_WPath * pDst);

	STDMETHOD_(HENHMETAFILE_XD, SetEnhMetaFileBitsFromFile)(ULONG length, void * ptr);

	//17%サムネールと同じように、大きく描いて縮小、エッジ強調する
	HRESULT DrawLargeThenShrink(MP_Canvas* canvas);
};

static const double			RATE_DPI_TO_DPM = 0.254 ;	//dot per inch から dot per meter への変換率
static const int			RESOLUTION_CONVERSION = 1 ;	//解像度変換 識別

const DWORD ROP_DPa		= 0xa000c9;
const DWORD ROP_PSDPxax	= 0xb8074a;
const DWORD ROP_DSPDxax	= 0xe20746;
const DWORD ROP_DPSao	= 0xea02e9;

#endif

//
//CHANGE LOG
//1999.06.18 - Komoda - V4 pd3impl.hからメタファイル関連を分離、pspatch.hとmfreduce.hを統合
//1999.06.22 - Komoda - V4 getUncompressedBitsSize() を追加
//1999.08.19 - Komoda - V4 AR4498 DWMRSTRETCHDIBREF の座標パラメータをWORDからshortに変更
//1999.10.05 - Komoda - V4 AR5051 getBISizeMF()の名前変更
//2000.05.09 - Nakazawa - V4 AR5442 OnDraw, OnPrintの実装を.cppファイルに移動
//2000.07.26 - Komoda - V4 AR5709 ClearBackGround()の第2引数をMP_Rectに変更
//2002.02.27 - Komoda - V5.0 キャッシュなし表示対応
//2002.02.28 - Ichikawa - V5.0 アプリケーションページのイメージデータ解像度 対応
//2002.03.01 - Komoda - V5.0 DWPrn95 JPEG圧縮対応
//2002.06.27 - Komoda - V5.0 AR7029 EnumUserDataにlangを追加
//2002.07.26 - Komoda - V5.0 AR8094 DWPrn95のJPEGレコード出力の変更に伴う変更
//2004.03.11 - Kudo - V6.0 AR5286 EnumUserDataにdrawRatioを追加

// $History: pd3mf.h $
// 
// *****************  Version 11  *****************
// User: Tashiro      Date: 08/08/15   Time: 16:43
// Updated in $/DocuWorks/70/Source/mpcpd
// [AR15494] 暫定的に入れた命令置き換え動作をcanvas.hに移動
// 
// *****************  Version 9  *****************
// User: Arai         Date: 08/06/06   Time: 21:34
// Updated in $/DocuWorks/70/Source/mpcpd
// [AR13942]Word白線パッチ対応
// 
// *****************  Version 8  *****************
// User: Tashiro      Date: 08/05/28   Time: 19:26
// Updated in $/DocuWorks/70/Source/mpcpd
// [AR14867] 17%サムネール並みの画質で描画する機能をDrawToPrinterに追加
// 
// *****************  Version 7  *****************
// User: Komoda       Date: 08/05/14   Time: 20:53
// Updated in $/DocuWorks/70/Source/mpcpd
// AR14721 ImplEMFPにSetEMFを追加
// 
// *****************  Version 6  *****************
// User: Arai         Date: 08/05/09   Time: 19:47
// Updated in $/DocuWorks/70/Source/mpcpd
// [AR13942]Word白線パッチ対応
// 
// *****************  Version 5  *****************
// User: Arai         Date: 08/04/25   Time: 19:24
// Updated in $/DocuWorks/70/Source/mpcpd
// [AR13942]Word白線パッチ対応
// 
// *****************  Version 4  *****************
// User: Tashiro      Date: 08/02/24   Time: 18:38
// Updated in $/DocuWorks/70/Source/mpcpd
// [FD186] ハイコントラスト指定に応じて描画動作を変える
// 
// *****************  Version 16  *****************
// User: Komoda       Date: 07/08/14   Time: 21:41
// Updated in $/DocuWorks/70/Source/mpcpd
// Unicode I/Fの追加
// 
// *****************  Version 14  *****************
// User: Tashiro      Date: 07/05/18   Time: 19:40
// Updated in $/DocuWorks/62/Source/mpcpd
// (再度サブミット)
// 
// *****************  Version 12  *****************
// User: Tashiro      Date: 07/05/17   Time: 18:58
// Updated in $/DocuWorks/62/Source/mpcpd
// [AR13155] MP_PD::RotateOnMem追加
// 
// *****************  Version 11  *****************
// User: Komoda       Date: 06/12/15   Time: 16:24
// Updated in $/DocuWorks/62/Source/mpcpd
// AR13635対応
// 
// *****************  Version 10  *****************
// User: Ktakahashi   Date: 06/09/28   Time: 11:38
// Updated in $/DocuWorks/62/Source/mpcpd
// [AR12160]WMF描画時にPALETTEに対する処理を補正するためのフラグ
// 
// *****************  Version 9  *****************
// User: Hiroki       Date: 06/08/30   Time: 11:04
// Updated in $/DocuWorks/62/Source/mpcpd
// [AR12815] 1ptの直線アノテの描画障害対応
// 
// *****************  Version 7  *****************
// User: Komoda       Date: 04/06/14   Time: 19:19
// Updated in $/DocuWorks/60/Source/mpcpd
// EnumUserDataにbSmoothDrawを追加
// 
// *****************  Version 6  *****************
// User: Arai         Date: 04/04/14   Time: 19:29
// Updated in $/DocuWorks/60/Source/mpcpd
// V6マージ　AR8283
// 
// *****************  Version 5  *****************
// User: Komoda       Date: 04/04/14   Time: 16:54
// Updated in $/DocuWorks/60/Source/mpcpd
// PSPatch関連の変更
// 
// *****************  Version 4  *****************
// User: Komoda       Date: 04/04/12   Time: 16:53
// Updated in $/DocuWorks/60/Source/mpcpd
// ImplWMFPDにGetTextを追加(アノテーションのテキスト検索用)
// 
// *****************  Version 3  *****************
// User: Komoda       Date: 04/03/18   Time: 15:37
// Updated in $/DocuWorks/60/Source/mpcpd
// EnumUserDataにpathDataを追加(図形文字のなめらか描画)
