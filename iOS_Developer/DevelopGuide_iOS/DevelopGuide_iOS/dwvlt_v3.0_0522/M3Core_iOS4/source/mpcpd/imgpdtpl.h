// File: imgpdtpl.h
// Authors: Ryoji Matsumura, Toshiyuki Komoda
// Copyright (C) 1997-2005 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _IMAGE_PD_TEMPLATE_H_
#define _IMAGE_PD_TEMPLATE_H_

/*
// 09.07.14 - M.Chikyu UNICODE対応
#ifdef _M3CORE_MP_

#include "imgpdtpl_linux.h"

#endif

// 09.07.14 - M.Chikyu UNICODE対応
#ifndef _M3CORE_MP_
*/

#include "imgpdbse.h"
#include "imgshk.h"
#include "imgmag.h"
#include "imgrot.h"
#include "imgpdutl.h"
#include "okdpdseed.h"
#include "../mpcinc/mpc_pchk.h"
#include "../mpcinc/secret.h"

#define SZTECH_PDF		"PDF"	// PDFWriterの文字列

const int BAND_WIDTH = 64;
const int BAND_WIDTH_MONOCHROME = 256;

// V4 セキュリティ OnDraw と OnPrint のパーミッションチェックに用いる。
// チェックが少し複雑で、ImagePD, MFPD共通で用いるため別関数にまとめた。
inline HRESULT PermCheckForDrawOrPrint(IStgObject* stgobj, MP_Canvas* canvas)
{
	MP_Permission checkPerm = 0;
	HDC_XD hDC = canvas->GetHDC();
	int devTech = ::GetDeviceCaps(hDC, TECHNOLOGY);
	DWORD objType = ::GetObjectType(hDC);
	if (devTech == DT_METAFILE) {	// hDC がメタファイルの場合
		const long CLSID_HBODYCONT_ = 0x8010;	// ヘテロのクラスID(hcntdoc.hでしか宣言されていないので、暫定的にここで定義する)
		if (stgobj && (stgobj->GetObjectType() == CLSID_HBODYCONT_))	// AR4647対応:MetafileDCに対してはヘテロのみ保護する
			checkPerm = MP_PERM_COPY;
	} else
	if (devTech == DT_RASDISPLAY && objType == OBJ_MEMDC) {	// hDC がビットマップの場合で
		MP_Integer xper, yper;
		canvas->GetMagnify(&xper, &yper);
		// サムネイル倍率より大きかったら
		if ((xper > 17) && (yper > 17)) {
			checkPerm = MP_PERM_COPY;
		}
	} else
	if (devTech == DT_RASPRINTER) {	// hDC がプリンタの場合
		checkPerm = MP_PERM_PRINT;
	}
	if (checkPerm == 0)
		return MP_NOERROR;
	return PermCheckFromStgObj(stgobj, checkPerm);
}

// V4 セキュリティ PD::Save 時のパーミッションチェックに用いる。
// ImagePD, MFPD共通で用いるため別関数にまとめた。
inline HRESULT PermCheckForSave(IStgObject* stgobj)
{
	MP_Permission checkPerm = 0;
	// アノテかヘテロかを調べる
	MP_Integer cop = -1;
	MP_AValue aValue = {sizeof(MP_Integer), MP_A_INT, &cop};
	HRESULT hRes = stgobj->GetAttribute("#cop", &aValue);
	if (hRes != MP_NOERROR) {	// 属性がない場合はアノテ
		checkPerm = MP_PERM_ANNO_EDIT;
	} else
	if (hRes == MP_NOERROR && cop == 0) {	// ヘテロ
		checkPerm = MP_PERM_DOC_EDIT;
	}
	if (checkPerm == 0)
		return MP_NOERROR;
	return PermCheckFromStgObj(stgobj, checkPerm);
}

// アプリ->イメージ変換時に、拡張MFPD内で用いていたJpegデータを削除する
static void DeleteJpegDataInMFPD(MPCSession* session, IStgObject* stgobj)
{
	if (session == NULL || stgobj == NULL)
		return;
	ICompressedMPAttribute* icompAttr = (ICompressedMPAttribute*)session->GetInterface(IID_ICompressedMPAttribute);
	if (icompAttr == NULL)
		return;

	// Jpegデータ数の取得
	WORD nImage = 0;
	MP_AValue aValue = {sizeof(WORD), MP_A_OCTS, &nImage};
	HRESULT hRes = icompAttr->GetCompressedAttribute(stgobj, "#pd", &aValue, 0);
	if ((hRes < 0) || (nImage < 0))	// Jpegデータがない
		return;
	// Jpegデータの削除
	for (int n = 0; n <= nImage; n++)
		icompAttr->SetCompressedAttribute(stgobj, "#pd", NULL, n);
}

template <class ImagePDSeed> class ImagePD : public ImagePDBase {
public:
    ImagePD(MPCSession *session);
    //~ImagePD():デストラクタを定義してはいけない

    //from MPCInterface
    STDMETHOD_(void *, GetInterface)(MP_RefInterfaceID riid, HRESULT *phres = 0);
    STDMETHOD(Destroy)();

    //from MP_PD
    STDMETHOD(Save)(IStgObject *stgobj, const MP_AName *aname = 0);
    STDMETHOD_(MP_PD *, CreateIconPD)(HRESULT *phres);
    STDMETHOD(GetPDInfo)(MP_Integer *org, MP_Integer *compLevel, MP_Integer *depth, MP_Dim *mdim);
    STDMETHOD(ConvertToDIBHandle)(HGLOBAL hDIB = 0);
    STDMETHOD(ConvertToDIBFile)(MP_Path *dibfilepath);
    STDMETHOD(ConvertToDIBHeader)(BITMAPINFOHEADER *bmiHeader);
    STDMETHOD(OnDraw)(MP_Canvas *canvas, MP_Integer bPart = 0);
    STDMETHOD(OnPrint)(MP_Canvas *canvas, MPC_AdvCancelInfo *info = 0);

	//n V4追加分
	STDMETHOD(ConvertToDIBHandleAdv)(HGLOBAL hDIB = NULL, BOOL bRotate = TRUE, MPC_AdvCancelInfo* info = NULL);
	STDMETHOD(ConvertToDIBFileAdv)(MP_Path* dibfilepath, BOOL bRotate = TRUE, MPC_AdvCancelInfo* info = NULL);
	STDMETHOD(ConvertToDIBHeaderAdv)(BITMAPINFOHEADER* bmiHeader, BOOL bRotate = TRUE);
	STDMETHOD(GetCompDataToFile)(MP_Path* dstPath, MP_Integer* compDataType = NULL);
	STDMETHOD(GetCompDataToHandle)(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL);
	STDMETHOD(CompressImage)(MP_Integer level)  {return MP_E_NOTIMPL;};
														//V5.0 解像度変換 追加
	STDMETHOD(ThinImage)(MP_Integer level, MP_Integer specified_resolution = 0)  {return MP_E_NOTIMPL;};
	STDMETHOD_(MP_Integer, GetColorType)(BOOL bCheck = TRUE);

	// V7 Unicode I/F
	STDMETHOD(ConvertToDIBFileW)(const MP_WPath* dibfilepath);
	STDMETHOD(ConvertToDIBFileAdvW)(const MP_WPath* dibfilepath, BOOL bRotate = TRUE, MPC_AdvCancelInfo* info = NULL);
	STDMETHOD(GetCompDataToFileW)(const MP_WPath* dstPath, MP_Integer* compDataType = NULL);

	STDMETHOD(GetPercent)();
	STDMETHOD(SetPercent)(MP_Integer percent);


    //ImagePD専用
	HRESULT Load(MP_Octet *inbase, long insize, IStgObject *stgobj);
	//n キャンセル機構追加
	HRESULT CreateFromDIBFile(MP_Path *dibfilepath, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info);
	//07.09.19 - M.Chikyu UNICODE対応
	// 対応関数の追加
	HRESULT CreateFromDIBFileW(const MP_WPath *dibfilepathW, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info);

	HRESULT CreateFromMemDIB(BITMAPINFO *dibinfo, unsigned char *imagedata, MP_Dim dim, MP_Integer level, MPC_AdvCancelInfo* info);

    //for self
    void set_degree(MP_Integer degree) {
        if (degree == 0 || degree == 90 || degree == 180 || degree == 270)
            m_degree = degree;
    }
	MP_Integer get_degree() {
		return m_degree;
	}

private:
    //データメンバ
    ImagePDSeed m_seed;

    //メンバ関数
	BOOL CanCreateCache(MP_Canvas *canvas);
	void UpdateCacheSize(MP_Canvas *canvas);
	HRESULT PrepareDraw(MP_Canvas *canvas, WinCoord *win);
	HRESULT DrawCommon(MP_Canvas *canvas, MP_Integer bPart);
	HRESULT CreateCacheBmp(MP_Canvas *canvas);
	HRESULT DrawCacheBmp(MP_Canvas *canvas);
	void DeleteCacheBmp();

    //static member functions for ImageShrink or ImageRotate
    static int GetLine4DrawDispatch(unsigned char *buf, void *arg);
    static int GetLine4PrintDispatch(unsigned char *buf, void *arg);
    static int GetLine4GetDIBDispatch(unsigned char *buf, void *arg);

	// AR5442対応：パーミッションチェックをしない内部OnDrawを追加
    STDMETHOD(DrawInternal)(MP_Canvas *canvas, MP_Integer bPart);
};

template <class ImagePDSeed>
ImagePD<ImagePDSeed>::ImagePD(MPCSession *session)
    : ImagePDBase(session), m_seed(session)
{}

template <class ImagePDSeed>
void *ImagePD<ImagePDSeed>::GetInterface(MP_RefInterfaceID riid, HRESULT *phres) {
    if (phres)
        *phres = MP_NOERROR;
    if (MP_IsEqual(riid, IID_MP_PD)) {
        return (void*)this;
    } else {
        return m_seed.GetInterface(riid, phres);
    }
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::Destroy() {
    ///>>>
	if (m_cacheBmp) {
		::DeleteBitmap(m_cacheBmp);
		m_cacheBmp = 0;
	}
	if (m_cachePal) {
        ::DeleteObject(m_cachePal);
        m_cachePal = 0;
    }
    if (m_pbi) {
        ImagePDSeed::FreeBitmapInfo(m_pbi);
        m_pbi = 0;
    }
    if (m_rotBuf) {
		m_rotate4Draw.release();
		m_shrink4Draw.release();
		m_shrinkrl4Draw.release();
		m_seed.FinishForDraw();
		delete [] m_rotBuf;
		m_rotBuf = 0;
    }
    ///<<<
    destroy(); //call ImagePDBase::destroy()
    delete this;
	return MP_NOERROR;
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::Save(IStgObject *stgobj, const MP_AName *aname) {

	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckForSave(stgobj);
		if (hRes != MP_NOERROR) return hRes;
	}
	if ( m_bRotatedOnMem )
		return MP_E_INVALID_CALL;

	if( !(strcmp((char*)aname, "#pd")) ) {
		//#rotate属性の更新
		switch( m_degree ) {
		case 0:
		case 90:
		case 180:
		case 270:
			MP_AValue avrot;
			avrot.asize = sizeof(MP_Integer);
			avrot.atype = MP_A_INT;
			avrot.adata = (void *)&m_degree;
			stgobj->SetAttribute("#rotate", &avrot);
			break;
		default:
			stgobj->SetAttribute("#rotate", NULL);
			break;
		}
	}
    HRESULT hRes = m_seed.Save(stgobj, aname);
	if ((hRes == MP_NOERROR) && (strcmp(aname, "#pd") == 0)) {	// AR4229
		DeleteJpegDataInMFPD(m_session, stgobj);
	}
	return hRes;
}

extern int CheckDIBColorType(BITMAPINFO *pbi, BYTE *pbits); // pd3bmp.cpp

template <class ImagePDSeed>
MP_PD* ImagePD<ImagePDSeed>::CreateIconPD(HRESULT *phres)
{
	if ( phres ) *phres = MP_E_UNEXPECTED;

	// アイコンのpixサイズを計算
	MP_Dim dim = m_seed.GetDimensions(); // 画像の寸法(1/100mm)
	if (dim.cx <= 0 || dim.cy <= 0) {
		return NULL;
	}
	MP_Dim dst; // アイコンのpixサイズ
	const int ICON_PPM = 492; // アイコンの解像度(=12.5dpi)
	//Modify2003/06/19 K.Takahashi
	//AR8301対策:dstの計算がオーバーフローしないようにキャストして計算する
	dst.cx = (MP_Integer)((__int64)dim.cx * ICON_PPM / 100000);
	dst.cy = (MP_Integer)((__int64)dim.cy * ICON_PPM / 100000);

	// AR2362 アイコンは何%のサイズになるか計算
	// (JPEGPDSeedに必要 : 通常は17でよいが
	//  拡大になるようにdropした場合は17に倍数を掛けないといけない)
	BITMAPINFOHEADER bih;
	HRESULT hres;
	if ((hres = m_seed.GetDIBHeader(&bih)) != MP_NOERROR) {
        if (phres)
            *phres = hres;
		return NULL;
	}
	SIZE ppm = m_seed.GetResolutions();
	int xpercent = 0, ypercent;
	if (ppm.cx > 0 && ppm.cy > 0) {
		const double ICON_PERCENT = 17.0;
		MP_Dim dim2; // 100%でdropした場合の寸法
		dim2.cx = bih.biWidth  * 100000 / ppm.cx; // 値のflowを防ぐため式を分割
		dim2.cy = bih.biHeight * 100000 / ppm.cy;
		xpercent = (int)(ICON_PERCENT * dim.cx / dim2.cx + 0.5);
		ypercent = (int)(ICON_PERCENT * dim.cy / dim2.cy + 0.5);
		if (xpercent < ypercent) xpercent = ypercent;
	}

	// seed を初期化
	BITMAPINFO *pbi = m_seed.InitForGetDIB(xpercent);
	if (!pbi) {
		return NULL;
    }

	// shrink を初期化
	ImageShrink shk;
	shk.pSrcBI = pbi;
	shk.dstWidth = dst.cx;
	shk.dstHeight = dst.cy;
	shk.isGray = is_gray(pbi);
	shk.colorReduction = FALSE;
	shk.decodeLine = ImagePD<ImagePDSeed>::GetLine4GetDIBDispatch;
	shk.decodeArg = (void *)&m_seed;

	ImagePD<OKDPDSeed> *iconpd = NULL;
	if (shk.init() == ImageShrink::SHRINK_OK) {
		int lineBytes = ((shk.pDstBI->bmiHeader.biWidth * shk.pDstBI->bmiHeader.biBitCount + 31) >> 3) & (-4);
		int bufSize = lineBytes * shk.pDstBI->bmiHeader.biHeight;
		BYTE *pbits = new BYTE [bufSize];
		if (pbits) {
			BYTE *p = pbits + lineBytes * (shk.pDstBI->bmiHeader.biHeight - 1);
			int ret;
			while ((ret = shk.getLine(p)) == ImageShrink::SHRINK_INCOMPLETE) {
				p -= lineBytes;
			}
			if (ret == ImageShrink::SHRINK_OK) {
				m_colorType = ::CheckDIBColorType(shk.pDstBI, pbits); // カラー判定
				if (shk.pDstBI->bmiHeader.biBitCount == 24)
					sharpenColor24(shk.pDstBI, pbits);
				iconpd = new ImagePD<OKDPDSeed>(m_session);
				if (iconpd) {
					if (iconpd->CreateFromMemDIB(shk.pDstBI, pbits, m_seed.GetDimensions(), 1, NULL) != MP_NOERROR) {
						iconpd->Destroy();
						iconpd = NULL;
					} else {
                        //success
	                    if ( phres ) *phres = MP_NOERROR;
                        iconpd->set_degree(m_degree);//回転角のセット 971105
                    }
				}
			}
			delete [] pbits;
		}
		shk.release();
	}
	m_seed.FinishForGetDIB();
    ImagePDSeed::FreeBitmapInfo(pbi);

	return iconpd;
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::GetPDInfo(MP_Integer *org, MP_Integer *compLevel, MP_Integer *depth, MP_Dim *mdim) {
    if (org)
        *org = m_seed.GetPDType();
    if (compLevel)
        *compLevel = m_seed.GetCompressInfo();
    if (depth)
        *depth = m_seed.GetColorDepth();
    if (mdim) {
        *mdim = m_seed.GetDimensions();
        if (m_degree == 90 || m_degree == 270) {
            MP_Integer tmp = mdim->cx;
            mdim->cx = mdim->cy;
            mdim->cy = tmp;
        }
    }
    return MP_NOERROR;
}

//n 共通ルーチンを通るように修正
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBHandle(HGLOBAL hDIB) {
	return ConvertToDIBHandleAdv(hDIB);
}

//n V4新規
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBHandleAdv(HGLOBAL hDIB, BOOL bRotate, MPC_AdvCancelInfo* info) {

	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckFromStgObj(m_stgobj, MP_PERM_COPY);
		if (hRes != MP_NOERROR) return hRes;
	}

	//n キャンセル機構追加
	BOOL bCanCancel = FALSE;
	if (info && info->callback)
		bCanCancel = TRUE;
	long percent = 0;
	long processed = 0;
    if (bCanCancel) {
        //0%のコールバック
        if (info->callback(info->userData, 0) == MP_PROCESS_CANCEL) {
            return MP_S_PROCESS_CANCELED;
        }
    }

    //DIBに必要なサイズ(bytes)を計算する(ヘッダ、回転を考慮する)
    BITMAPINFO *pbi = m_seed.InitForGetDIB(0);//0はヒントなし(オリジナルサイズ)を意味する
    if (!pbi) {
        return MP_E_UNEXPECTED;
    }
    BITMAPINFOHEADER *pbih = &pbi->bmiHeader;
    LONG width, height;
	//nr
	width = pbih->biWidth;
	height = pbih->biHeight;
    if ((bRotate) && (m_degree == 90 || m_degree == 270)) {
        height = pbih->biWidth;
        width = pbih->biHeight;
	}
    LONG bits_per_pixel = pbih->biBitCount;
    LONG header_bytes = getBISize(pbi);
    LONG image_bytes = WIDTHBYTES(width * bits_per_pixel) * height;
    LONG need_bytes = header_bytes + image_bytes;
    if (!hDIB) {
        //DIBのサイズ(bytes)を返す
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return need_bytes;
    }

	long bytes = (long)GlobalSize(hDIB);
	if (bytes < need_bytes) {
	    if (bytes < sizeof(BITMAPINFOHEADER)) {
            ImagePDSeed::FreeBitmapInfo(pbi);
            m_seed.FinishForGetDIB();
		    return MP_E_INVALIDARG;
        } else {
            //BITMAPINFOHEADERを返す
	        BITMAPINFOHEADER *bmpih = (BITMAPINFOHEADER *)GlobalLock(hDIB);
            memcpy(bmpih, pbih, sizeof(BITMAPINFOHEADER));
            if (bRotate && (m_degree == 90 || m_degree == 270)) {	//nr
                LONG tmp = bmpih->biWidth;
                bmpih->biWidth = bmpih->biHeight;
                bmpih->biHeight = tmp;
            }
	        GlobalUnlock(hDIB);
            ImagePDSeed::FreeBitmapInfo(pbi);
            m_seed.FinishForGetDIB();
            return sizeof(BITMAPINFOHEADER);
        }
    }

    //伸長しながら回転するための初期設定
    ImageRotate rot;
    //>>Rotateパラメタ設定
    rot.mode = ImageRotate::MODE_PAGE;// 部分かページか
	if (bRotate)	//nr
		rot.angle = m_degree;// 回転角 : 0,90,180,270
	else
		rot.angle = 0;
	rot.nLine = BAND_WIDTH;// バンド幅  (rotateで返る) 実際に処理したライン数
	rot.pSrcBI = pbi;// 入力画像のbmpinfo
	rot.srcBISize = header_bytes; // 入力画像のbmpinfoのサイズ
    rot.getLine = ImagePD<ImagePDSeed>::GetLine4GetDIBDispatch;// srcBitsに1ライン出力する関数のポインタ
	rot.getParam = (void *)&m_seed;// getLineに必要なパラメータ構造体のポインタ
    //<<Rotateパラメタ設定
    if (rot.init() < 0) {
        //error
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return MP_E_UNEXPECTED;
    }
    if (rot.dstBufSize != image_bytes) {
        //error
        rot.release();
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return MP_E_UNEXPECTED;
    }

    //BITMAPINFOHEADER+PaletteをpDIBにセット
	unsigned char *pDIB = (unsigned char *)GlobalLock(hDIB);
    memcpy(pDIB, rot.pDstBI, header_bytes);
    unsigned char *pImage = pDIB + header_bytes;

    //伸長しながら回転する
    //int ret;
    //while ((ret = rot.rotate(pImage)) == ImageRotate::ROTATE_INCOMPLETE);
	//n キャンセル機構追加
	int ret = ImageRotate::ROTATE_INCOMPLETE;
	while (ret == ImageRotate::ROTATE_INCOMPLETE) {
		ret = rot.rotate(pImage);
		if (bCanCancel) {
			processed += BAND_WIDTH;
			percent = processed * 100 / pbih->biHeight;
			// AR4037 : キャンセルコールバックは0%・100%それぞれ一回だけ呼ぶ
			if (percent > 0 && percent < 100) {
				if (info->callback(info->userData, percent) == MP_PROCESS_CANCEL) {
					GlobalUnlock(hDIB);
					rot.release();
					ImagePDSeed::FreeBitmapInfo(pbi);
					m_seed.FinishForGetDIB();
					return MP_S_PROCESS_CANCELED;
				}
			}
		}
	}

	GlobalUnlock(hDIB);
    rot.release();
    ImagePDSeed::FreeBitmapInfo(pbi);
    m_seed.FinishForGetDIB();

	//n キャンセル機構追加
    if (bCanCancel) {
        // 100%のコールバック
        if (info->callback(info->userData, 100) == MP_PROCESS_CANCEL) {
            return MP_S_PROCESS_CANCELED;
        }
    }

    if (ret == ImageRotate::ROTATE_COMPLETE) {//完了
        //DIBのサイズ(bytes)を返す
        return need_bytes;
    } else {
        //何らかのエラー発生
        return MP_E_UNEXPECTED;
    }
}


//n 共通ルーチンを通るように修正
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBFile(MP_Path *dibfilepath) {
	return ConvertToDIBFileAdv(dibfilepath);
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBFileW(const MP_WPath *dibfilepathW) {
	return ConvertToDIBFileAdvW(dibfilepathW);
}

//n V4新規
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBFileAdv(MP_Path *dibfilepath, BOOL bRotate, MPC_AdvCancelInfo* info)
{
	// 09.07.14 - M.Chikyu UNICODE対応
	// オリジナルコード全削除

	/*
	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckFromStgObj(m_stgobj, MP_PERM_COPY);
		if (hRes != MP_NOERROR) return hRes;
	}

    //DIBに必要なサイズ(bytes)を計算する(ヘッダ、回転を考慮する)
    BITMAPINFO *pbi = m_seed.InitForGetDIB(0);//0はヒントなし(オリジナルサイズ)を意味する
    if (!pbi) {
        return MP_E_UNEXPECTED;
    }
    BITMAPINFOHEADER *pbih = &pbi->bmiHeader;
    LONG width, height;
	//nr
	width = pbih->biWidth;
	height = pbih->biHeight;
    if ((bRotate) && (m_degree == 90 || m_degree == 270)) {
        height = pbih->biWidth;
        width = pbih->biHeight;
	}
    LONG bits_per_pixel = pbih->biBitCount;
    LONG header_bytes = sizeof(BITMAPFILEHEADER) + getBISize(pbi);
    LONG image_bytes = WIDTHBYTES(width * bits_per_pixel) * height;
    LONG need_bytes = header_bytes + image_bytes;

    //伸長しながら回転するための初期設定
    ImageRotate rot;
    //>>Rotateパラメタ設定
    rot.mode = ImageRotate::MODE_PAGE;// 部分かページか
	if (bRotate)	//nr
		rot.angle = m_degree;// 回転角 : 0,90,180,270
	else
		rot.angle = 0;
	rot.nLine = BAND_WIDTH;// バンド幅  (rotateで返る) 実際に処理したライン数
	rot.pSrcBI = pbi;// 入力画像のbmpinfo
	rot.srcBISize = getBISize(pbi);// 入力画像のbmpinfoのサイズ
    rot.getLine = ImagePD<ImagePDSeed>::GetLine4GetDIBDispatch;// srcBitsに1ライン出力する関数のポインタ
	rot.getParam = (void *)&m_seed;// getLineに必要なパラメータ構造体のポインタ
    //<<Rotateパラメタ設定
    if (rot.init() < 0) {
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return MP_E_UNEXPECTED;
    }
    if (rot.dstBufSize != image_bytes) {
        rot.release();
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return MP_E_UNEXPECTED;
    }

    HRESULT hres;
    if (set_bmp_to_file(dibfilepath, &rot, need_bytes, &hres, info) == -1) {
        rot.release();
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        //ファイルを消すか?
		::DeleteFile(dibfilepath);	// とりあえず消す仕様にしておく
        return hres;
    }

    rot.release();
    ImagePDSeed::FreeBitmapInfo(pbi);
    m_seed.FinishForGetDIB();

    return MP_NOERROR;
	*/
	// パラメータをUNICODEへ変換

	HRESULT hr;
	MP_String dibfilepathW;

	hr = dibfilepathW.Convert(FILEPATH_CODEPAGE, dibfilepath);
	if (FAILED(hr))
	{
		return hr;
	}

	return ConvertToDIBFileAdvW(dibfilepathW, bRotate, info);
}

//07.09.19 - M.Chikyu UNICODE対応
// 対応関数の追加
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBFileAdvW(const MP_WPath *dibfilepathW, BOOL bRotate, MPC_AdvCancelInfo* info) {

	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckFromStgObj(m_stgobj, MP_PERM_COPY);
		if (hRes != MP_NOERROR) return hRes;
	}

    //DIBに必要なサイズ(bytes)を計算する(ヘッダ、回転を考慮する)
    BITMAPINFO *pbi = m_seed.InitForGetDIB(0);//0はヒントなし(オリジナルサイズ)を意味する
    if (!pbi) {
        return MP_E_UNEXPECTED;
    }
    BITMAPINFOHEADER *pbih = &pbi->bmiHeader;
    LONG width, height;
	//nr
	width = pbih->biWidth;
	height = pbih->biHeight;
    if ((bRotate) && (m_degree == 90 || m_degree == 270)) {
        height = pbih->biWidth;
        width = pbih->biHeight;
	}
    LONG bits_per_pixel = pbih->biBitCount;
    LONG header_bytes = sizeof(BITMAPFILEHEADER) + getBISize(pbi);
    LONG image_bytes = WIDTHBYTES(width * bits_per_pixel) * height;
    LONG need_bytes = header_bytes + image_bytes;

    //伸長しながら回転するための初期設定
    ImageRotate rot;
    //>>Rotateパラメタ設定
    rot.mode = ImageRotate::MODE_PAGE;// 部分かページか
	if (bRotate)	//nr
		rot.angle = m_degree;// 回転角 : 0,90,180,270
	else
		rot.angle = 0;
	rot.nLine = BAND_WIDTH;// バンド幅  (rotateで返る) 実際に処理したライン数
	rot.pSrcBI = pbi;// 入力画像のbmpinfo
	rot.srcBISize = getBISize(pbi);// 入力画像のbmpinfoのサイズ
    rot.getLine = ImagePD<ImagePDSeed>::GetLine4GetDIBDispatch;// srcBitsに1ライン出力する関数のポインタ
	rot.getParam = (void *)&m_seed;// getLineに必要なパラメータ構造体のポインタ
    //<<Rotateパラメタ設定
    if (rot.init() < 0) {
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return MP_E_UNEXPECTED;
    }
    if (rot.dstBufSize != image_bytes) {
        rot.release();
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        return MP_E_UNEXPECTED;
    }

    HRESULT hres;
	//07.09.19 - M.Chikyu UNICODE対応
    //if (set_bmp_to_file(dibfilepath, &rot, need_bytes, &hres, info) == -1) {
    if (set_bmp_to_fileW(dibfilepathW, &rot, need_bytes, &hres, info) == -1) {

        rot.release();
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForGetDIB();
        //ファイルを消すか?
		//07.09.19 - M.Chikyu UNICODE対応
		//::DeleteFile(dibfilepath);	// とりあえず消す仕様にしておく
		::DeleteFileW(dibfilepathW);	// とりあえず消す仕様にしておく

        return hres;
    }

    rot.release();
    ImagePDSeed::FreeBitmapInfo(pbi);
    m_seed.FinishForGetDIB();

    return MP_NOERROR;
}

//n 共通ルーチンを通るように修正
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBHeader(BITMAPINFOHEADER *bmiHeader) {
	return ConvertToDIBHeaderAdv(bmiHeader);
}

//n V4新規
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::ConvertToDIBHeaderAdv(BITMAPINFOHEADER *bmiHeader, BOOL bRotate) {
    if (bmiHeader) {
		HRESULT hres = m_seed.GetDIBHeader(bmiHeader);
		if (hres < 0)
			return hres;
		if (bRotate && (m_degree == 90 || m_degree == 270)) {
			LONG tmp = bmiHeader->biWidth;
			bmiHeader->biWidth = bmiHeader->biHeight;
			bmiHeader->biHeight = tmp;
			bmiHeader->biSizeImage = WIDTHBYTES(bmiHeader->biWidth * bmiHeader->biBitCount) * bmiHeader->biHeight;
			tmp = bmiHeader->biXPelsPerMeter;
			bmiHeader->biXPelsPerMeter = bmiHeader->biYPelsPerMeter;
			bmiHeader->biYPelsPerMeter = tmp;
		}
		return hres;
	}
	return MP_E_INVALIDARG;
}


// AR5442対応：OnDrawはパーミッションチェックをしてから内部OnDrawを呼ぶように修正
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::OnDraw(MP_Canvas *canvas, MP_Integer bPart)
{
	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckForDrawOrPrint(m_stgobj, canvas);
		if (hRes != MP_NOERROR) return hRes;
	}
	return DrawInternal(canvas, bPart);
}

// AR5442対応：パーミッションチェックをしない内部OnDrawを追加
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::DrawInternal(MP_Canvas *canvas, MP_Integer bPart)
{
	// OLEサーバ対応: MetaFileDC出力ならばOnPrint()へ分岐
	if (::GetDeviceCaps(canvas->GetHDC(), TECHNOLOGY) == DT_METAFILE) {
		return OnPrint(canvas, 0);
	}
	// AR15288 アノテPDがEMFになったので、EMF-DCに対しても通常描画
	if (::GetObjectType(canvas->GetHDC()) == OBJ_ENHMETADC) {
		return OnPrint(canvas, 0);
	}

	WinCoord win;
	if (!getWindowCoordinate(canvas, m_degree, m_seed.GetDimensions(), &win)) {
		// 座標値のオーバーフロー発生(Win9x)
		return MP_E_UNEXPECTED;
	}

	// キャッシュの大きさが変わるならばキャッシュを作りかえる
	// ハイコントラスト指定が変わる場合もキャッシュを作りかえる
	if (isNeedChangeCache(&win, canvas)) {
		HRESULT hResult = MP_NOERROR;
		
		UpdateCacheSize(canvas);
		DeleteCacheBmp();
		// キャッシュを作るのに十分な空きメモリはあるか？
		if (CanCreateCache(canvas)) {
			// AR11061 キャッシュが作れなくてもエラーにしない
			CreateCacheBmp(canvas);
		}
		// 伸長処理の初期化
		hResult = PrepareDraw(canvas, &win);
		if (hResult != MP_NOERROR)
			return hResult;
	}

	// 伸長と描画
	return DrawCommon(canvas, bPart);
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::PrepareDraw(MP_Canvas *canvas, WinCoord *win)
{
	// seed を初期化
	if (m_pbi) {//AR1501
		m_seed.FreeBitmapInfo(m_pbi);
	}
	m_pbi = m_seed.InitForDraw(canvas, m_degree);

	// shrink を初期化
	if (!m_pbi) {// error
		return MP_E_UNEXPECTED;
	}

	int bandWidth = BAND_WIDTH;
	if (m_pbi->bmiHeader.biBitCount == 1)
		bandWidth = BAND_WIDTH_MONOCHROME;

	//>>Shrinkパラメータ設定
	m_shrink4Draw.pSrcBI = m_pbi;
	if (m_degree == 0 || m_degree == 180) {
		m_shrink4Draw.dstWidth = m_cacheSize.cx;
		m_shrink4Draw.dstHeight = m_cacheSize.cy;
	} else {
		m_shrink4Draw.dstWidth = m_cacheSize.cy;
		m_shrink4Draw.dstHeight = m_cacheSize.cx;
	}
	m_shrink4Draw.isGray = ::is_gray(m_pbi);
	m_shrink4Draw.colorReduction = FALSE;
	if ((::GetDeviceCaps(canvas->GetHDC(), TECHNOLOGY)) == DT_RASDISPLAY) {
		//displayかつ
		if (::GetDeviceCaps(canvas->GetHDC(), NUMCOLORS) != -1) {
			// !-1: palette color
			m_shrink4Draw.colorReduction = TRUE;
		}
	}
	m_shrink4Draw.decodeLine = ImagePD<ImagePDSeed>::GetLine4DrawDispatch;
	m_shrink4Draw.decodeArg = (void *)&m_seed;

	// V7ハイコントラスト
	// ハイコントラスト指定をm_shrink4Drawなどにセット
	m_shrink4Draw.iContrastMode = MPC_CONTRAST_DRAW_NONE;
	MPC_ContrastDrawInfo ContInfo;
	HRESULT hres = canvas->GetContrastDrawInfo( &ContInfo );
	if ( hres == MP_NOERROR ) {
		switch ( ContInfo.iContrastMode ) {
		case MPC_CONTRAST_DRAW_NONE:
			m_shrink4Draw.iContrastMode = ImageShrink::CONTRAST_NONE;
			m_shrinkrl4Draw.iContrastMode = ImageShrink::CONTRAST_NONE;
			break;
		case MPC_CONTRAST_DRAW_TEXT:
			m_shrink4Draw.iContrastMode = ImageShrink::CONTRAST_BIN;
			m_shrinkrl4Draw.iContrastMode = ImageShrink::CONTRAST_BIN;
			break;
		case MPC_CONTRAST_DRAW_COLOR_CONT:
			m_shrink4Draw.iContrastMode = ImageShrink::CONTRAST_CONT;
			m_shrinkrl4Draw.iContrastMode = ImageShrink::CONTRAST_CONT;
			break;
		case MPC_CONTRAST_DRAW_COLOR_BIN:
		default:
			m_shrink4Draw.iContrastMode = ImageShrink::CONTRAST_BIN_REV;
			m_shrinkrl4Draw.iContrastMode = ImageShrink::CONTRAST_BIN_REV;
			break;
		}

		m_shrink4Draw.ForeColor[0] = ContInfo.ColorFore[0];
		m_shrink4Draw.ForeColor[1] = ContInfo.ColorFore[1];
		m_shrink4Draw.ForeColor[2] = ContInfo.ColorFore[2];
		m_shrink4Draw.BackColor[0] = ContInfo.ColorBack[0];
		m_shrink4Draw.BackColor[1] = ContInfo.ColorBack[1];
		m_shrink4Draw.BackColor[2] = ContInfo.ColorBack[2];
		m_shrinkrl4Draw.ForeColor[0] = ContInfo.ColorFore[0];
		m_shrinkrl4Draw.ForeColor[1] = ContInfo.ColorFore[1];
		m_shrinkrl4Draw.ForeColor[2] = ContInfo.ColorFore[2];
		m_shrinkrl4Draw.BackColor[0] = ContInfo.ColorBack[0];
		m_shrinkrl4Draw.BackColor[1] = ContInfo.ColorBack[1];
		m_shrinkrl4Draw.BackColor[2] = ContInfo.ColorBack[2];
	}

	//<<Shrinkパラメータ設定
	if (m_shrink4Draw.init() < 0) {//error
	    m_seed.FinishForDraw();
		m_shrink4Draw.release();
	    return MP_E_UNEXPECTED;
	}

	//n ShrinkRL対応：パラメータ設定
	m_shrinkrl4Draw.pSrcBI = m_pbi;
	if (m_degree == 0 || m_degree == 180) {
		m_shrinkrl4Draw.dstWidth = m_cacheSize.cx;
		m_shrinkrl4Draw.dstHeight = m_cacheSize.cy;
	} else {
		m_shrinkrl4Draw.dstWidth = m_cacheSize.cy;
		m_shrinkrl4Draw.dstHeight = m_cacheSize.cx;
	}
	//n ShrinkRL対応
	BYTE* pRLTable = m_seed.GetRLTable();
	if (pRLTable) {
		m_shrinkrl4Draw.pRL = pRLTable;
		if (m_shrinkrl4Draw.init() < 0) {	// error
			m_seed.FinishForDraw();
			m_shrink4Draw.release();
			m_shrinkrl4Draw.release();
			return MP_E_UNEXPECTED;
		}
		m_bCanUseRL = TRUE;
	}

	// rotate を初期化
	//>>Rotateパラメタ設定
	m_rotate4Draw.mode = ImageRotate::MODE_PART;// 部分かページか
	m_rotate4Draw.angle = m_degree;// 回転角 : 0,90,180,270
	m_rotate4Draw.nLine = bandWidth;// バンド幅  (rotateで返る) 実際に処理したライン数
	m_rotate4Draw.pSrcBI = m_shrink4Draw.pDstBI;// 入力画像のbmpinfo
	m_rotate4Draw.srcBISize = m_shrink4Draw.dstBISize; // 入力画像のbmpinfoのサイズ
	m_rotate4Draw.getLine = ImageShrink::getLineDispatch;// srcBitsに1ライン出力する関数のポインタ
	m_rotate4Draw.getParam = (void *)&m_shrink4Draw;// getLineに必要なパラメータ構造体のポインタ
	//n ShrinkRL対応
	if (m_bCanUseRL) {
		m_rotate4Draw.pSrcBI = m_shrinkrl4Draw.pDstBI;// 入力画像のbmpinfo
		m_rotate4Draw.srcBISize = m_shrinkrl4Draw.dstBISize; // 入力画像のbmpinfoのサイズ
		m_rotate4Draw.getLine = ImageShrinkRL::getLineDispatch;// srcBitsに1ライン出力する関数のポインタ
		m_rotate4Draw.getParam = (void *)&m_shrinkrl4Draw;// getLineに必要なパラメータ構造体のポインタ
	}
	//<<Rotateパラメタ設定
	if (m_rotate4Draw.init() < 0) {
	    m_seed.FinishForDraw();
		m_shrink4Draw.release();
		m_shrinkrl4Draw.release();
		m_rotate4Draw.release();
	    return MP_E_UNEXPECTED;
	}

	//回転後のバッファを獲得
	if (m_rotBuf)
		delete [] m_rotBuf;
	m_rotBuf = new unsigned char [m_rotate4Draw.dstBufSize];
	if (!m_rotBuf) {	//error
	    m_seed.FinishForDraw();
		m_shrink4Draw.release();
		m_shrinkrl4Draw.release();
		m_rotate4Draw.release();
	    return MP_E_OUTOFMEMORY;
	}

	// 伸張カウントを初期化
	m_decodedLine = 0;
	m_needLine = 0;
    m_isFinished = FALSE; //AR1495対応 971105

	return MP_NOERROR;
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::DrawCommon(MP_Canvas *canvas, MP_Integer bPart)
{
	WinCoord win;
	if (!getWindowCoordinate(canvas, m_degree, m_seed.GetDimensions(), &win)) {
		// 座標値のオーバーフロー発生(Win9x)
		return MP_E_UNEXPECTED;
	}

	// 無効領域を求め、伸張が必要か調べる
    if (!m_isFinished) //AR1495対応 971105
        m_needLine = getNeedLine(canvas->GetHDC(), m_needLine, m_degree, m_cacheSize, &win);
	
	if (m_cacheBmp != NULL && m_needLine <= m_decodedLine) {
		// 伸張が必要なければキャッシュを表示して終了
		HRESULT hres = DrawCacheBmp(canvas);
		if (hres != MP_NOERROR)
			return hres;
		return MP_S_DRAW_FINISHED;
	}


	// 伸張が必要な場合
	int bandWidth = BAND_WIDTH;
	if (m_pbi->bmiHeader.biBitCount == 1)
		bandWidth = BAND_WIDTH_MONOCHROME;

	HDC_XD hBmpDC = NULL;
	HGDIOBJ_XD hOldBmp = NULL;
	HPALETTE hOldPal1 = NULL;
	HPALETTE hOldPal2 = NULL;

	// パレットを作ってなければ作成
	if (m_cachePal == NULL) {
		m_cachePal = CreateMediaPalette();
	}

	hOldPal1 = MPSelectPalette(canvas->GetHDC(), m_cachePal, canvas);
	::RealizePalette(canvas->GetHDC());
	if (m_cacheBmp != NULL) {
		hBmpDC = ::CreateCompatibleDC(canvas->GetHDC());
		hOldBmp = ::SelectObject(hBmpDC, m_cacheBmp);
		::SetStretchBltMode(hBmpDC, COLORONCOLOR);
		hOldPal2 = ::SelectPalette(hBmpDC, m_cachePal, FALSE);
		::RealizePalette(hBmpDC);
	}

	int needLine = m_needLine;
	if (m_cacheBmp != NULL && bPart) {
		if (m_decodedLine + bandWidth < m_needLine)
			needLine = m_decodedLine + bandWidth;
	}

	for (int lineOfs = m_decodedLine; lineOfs < needLine; lineOfs += bandWidth) {
		int nLine = bandWidth;
		if (m_degree == 0 || m_degree == 180) {
			if (m_decodedLine + nLine > m_cacheSize.cy)
				nLine = m_cacheSize.cy - m_decodedLine;
		} else {
			if (m_decodedLine + nLine > m_cacheSize.cx)
				nLine = m_cacheSize.cx - m_decodedLine;
		}
		//   1バンド分回転後の画像を作成する
		m_rotate4Draw.rotate(m_rotBuf);

		//   キャッシュ & 画面に転送
		TransferParam prm;
		prm.hDC = canvas->GetHDC();
		prm.hBmpDC = hBmpDC;
		prm.pbits = m_rotBuf;
		prm.pbi = m_rotate4Draw.pDstBI;
		prm.lineOfs = lineOfs;
		prm.nLine = nLine;
		prm.dstW = m_cacheSize.cx;
		prm.dstH = m_cacheSize.cy;
		if (m_cacheBmp == NULL) {
			transferToDevice(m_degree, &prm, &win);
		} else {
			transferToCacheAndDevice(m_degree, &prm, &win);
		}

		m_decodedLine += nLine;
	}

	::SelectPalette(canvas->GetHDC(), hOldPal1, FALSE);
	if (m_cacheBmp != NULL) {
		::SelectPalette(hBmpDC, hOldPal2, FALSE);
		::SelectObject(hBmpDC, hOldBmp);
		::DeleteDC(hBmpDC);
	}

	// 伸張完了ならば Seedのfinish
	int cmpLine = m_cacheSize.cy;
	if (m_degree == 90 || m_degree == 270)
		cmpLine = m_cacheSize.cx;
	if (m_decodedLine >= cmpLine) {
		m_rotate4Draw.release();
		m_shrink4Draw.release();
		m_shrinkrl4Draw.release();
		m_seed.FinishForDraw();
		if (m_pbi) {
			ImagePDSeed::FreeBitmapInfo(m_pbi);
			m_pbi = 0;
		}
		delete [] m_rotBuf;
		m_rotBuf = NULL;

		m_isFinished = TRUE; //AR1495対応 971105
		m_needLine = m_decodedLine; //AR1495対応 971105
	}

	if (bPart) {
		if (m_decodedLine < m_needLine)
			return MP_S_DRAW_SUSPENDED;
	}
	return MP_S_DRAW_FINISHED;
}

template <class ImagePDSeed>
BOOL ImagePD<ImagePDSeed>::CanCreateCache(MP_Canvas *canvas)
{
	// A4-300%表示以下ならば無条件にキャッシュを作成しようとする
	const int A4_LENGTH = 29700;
	const int MAGNIFY = 300;
	const int SIZE_THRESHOLD = (A4_LENGTH * MAGNIFY / 100) * 75 / 2540;
	WinCoord win;
	if (!getWindowCoordinate(canvas, m_degree, m_seed.GetDimensions(), &win)) {
		// 座標値のオーバーフロー発生(Win9x)
		return FALSE;
	}
	if (win.dev.dim.cx <= SIZE_THRESHOLD && win.dev.dim.cy <= SIZE_THRESHOLD)
		return TRUE;

	// A4-300%表示より大きい場合は
	// ビットマップ+1MB以上空きメモリがあればキャッシュを作成しようとする
	int planes = GetDeviceCaps(canvas->GetHDC(), PLANES);
	int bp = GetDeviceCaps(canvas->GetHDC(), BITSPIXEL);
	int cbBmp = (win.dev.dim.cx * planes * bp / 8) * win.dev.dim.cy;

	// 64bit対応：空きメモリサイズ取得の共通化
	size_t cbFreeMemory = ::GetAvailPhysSize();

	const int MEMORY_THRESHOLD = 0x100000; // 1MB
	if (cbFreeMemory >= (size_t)cbBmp + MEMORY_THRESHOLD)
		return TRUE;

	return FALSE;
}

template <class ImagePDSeed>
void ImagePD<ImagePDSeed>::UpdateCacheSize(MP_Canvas *canvas)
{
	WinCoord win;
	getWindowCoordinate(canvas, m_degree, m_seed.GetDimensions(), &win);

	// AR6597 02.10.30 h.arai
	m_cacheSize = CalcCacheSize( win );
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::CreateCacheBmp(MP_Canvas *canvas)
{
	HDC_XD hBmpDC = CreateCompatibleDC(canvas->GetHDC());
	if (hBmpDC == NULL) {
		return MP_E_UNEXPECTED;
	}

	// キャッシュBITMAPを作成
	m_cacheBmp = ::CreateCompatibleBitmap(canvas->GetHDC(), m_cacheSize.cx, m_cacheSize.cy);
	if (m_cacheBmp == NULL) {
		::DeleteDC(hBmpDC);
		return MP_E_OUTOFMEMORY;
		// 以後、キャッシュBITMAPがあるかどうかを m_cacheBmpでチェック
	}

	// キャッシュを白く塗る
	HGDIOBJ_XD hWhiteBrush = ::GetStockObject(WHITE_BRUSH);
    HGDIOBJ_XD hWhitePen = ::GetStockObject(WHITE_PEN);
    HGDIOBJ_XD hOldBrush = ::SelectObject(hBmpDC, hWhiteBrush);
    HGDIOBJ_XD hOldPen = ::SelectObject(hBmpDC, (HGDIOBJ_XD)hWhitePen);
	HBITMAP_XD hOldBmp = (HBITMAP_XD)::SelectObject(hBmpDC, m_cacheBmp);
	::Rectangle(hBmpDC, 0, 0, m_cacheSize.cx, m_cacheSize.cy);
	::SelectObject(hBmpDC, hOldBmp);
	::SelectObject(hBmpDC, hOldPen);
	::SelectObject(hBmpDC, hOldBrush);

	::DeleteDC(hBmpDC);

	// キャッシュを作ったときのハイコントラスト状態を記録
	MPC_ContrastDrawInfo ContInfo;
	HRESULT hres = canvas->GetContrastDrawInfo( &ContInfo );
	if ( hres == MP_NOERROR ) {
		m_iCachedContrastMode = ContInfo.iContrastMode;
		m_CachedForeColor[0] = ContInfo.ColorFore[0];
		m_CachedForeColor[1] = ContInfo.ColorFore[1];
		m_CachedForeColor[2] = ContInfo.ColorFore[2];
		m_CachedBackColor[0] = ContInfo.ColorBack[0];
		m_CachedBackColor[1] = ContInfo.ColorBack[1];
		m_CachedBackColor[2] = ContInfo.ColorBack[2];
	} else {
		m_iCachedContrastMode = MPC_CONTRAST_DRAW_NONE;
		m_CachedForeColor[0] = 0;
		m_CachedForeColor[1] = 0;
		m_CachedForeColor[2] = 0;
		m_CachedBackColor[0] = 255;
		m_CachedBackColor[1] = 255;
		m_CachedBackColor[2] = 255;
	}

	return MP_NOERROR;
}

template <class ImagePDSeed>
void ImagePD<ImagePDSeed>::DeleteCacheBmp()
{
	if (m_cacheBmp != NULL) {
		::DeleteBitmap(m_cacheBmp);
		m_cacheBmp = NULL;
	}
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::DrawCacheBmp(MP_Canvas *canvas)
{
	HDC_XD hdc = canvas->GetHDC();

    HDC_XD hBmpDC = ::CreateCompatibleDC(hdc);
    if (hBmpDC == NULL) {
	    return MP_E_UNEXPECTED;
    }

	HGDIOBJ_XD hOldBmp = ::SelectObject(hBmpDC, m_cacheBmp);
	HPALETTE hOldPal1 = MPSelectPalette(hdc, m_cachePal, canvas);
	::RealizePalette(hdc);
	HPALETTE hOldPal2 = ::SelectPalette(hBmpDC, m_cachePal, FALSE);
	::RealizePalette(hBmpDC);
	::SetStretchBltMode(hdc, COLORONCOLOR);
	
	WinCoord win;
	if (!getWindowCoordinate(canvas, m_degree, m_seed.GetDimensions(), &win)) {
		// 座標値のオーバーフロー発生(Win9x)
		return MP_E_UNEXPECTED;
	}

	if (m_cacheSize.cx < win.log.dim.cx || m_cacheSize.cy < win.log.dim.cy) {//拡大のときは...
		if (::StretchBlt(hdc, win.log.pos.x, win.log.pos.y, win.log.dim.cx, win.log.dim.cy,
				hBmpDC,	0, 0, m_cacheSize.cx, m_cacheSize.cy, SRCCOPY) == 0) {
			::NewStretchBlt(hdc, win.log.pos.x, win.log.pos.y, win.log.dim.cx, win.log.dim.cy,
				hBmpDC,	0, 0, m_cacheSize.cx, m_cacheSize.cy, SRCCOPY);
		}
	} else {
		::BitBlt(hdc, win.log.pos.x, win.log.pos.y, m_cacheSize.cx, m_cacheSize.cy,
		hBmpDC, 0, 0, SRCCOPY);
	}
	
	::SelectPalette(hdc, hOldPal1, FALSE);
	::SelectPalette(hBmpDC, hOldPal2, FALSE);
	::SelectObject(hBmpDC, hOldBmp);

	::DeleteDC(hBmpDC);

	return MP_NOERROR;
}


template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::OnPrint(MP_Canvas *canvas, MPC_AdvCancelInfo *info) {

	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckForDrawOrPrint(m_stgobj, canvas);
		if (hRes != MP_NOERROR) return hRes;
	}

	const int BAND_WIDTH_FULL = 65535;	// バンド分割しない版

	const int ALLBLT_MAX_SIZE = 2300 * 1024;	// バンド分割しない場合のイメージの最大サイズ(A3 300dpi強まで)

	int bandWidth = BAND_WIDTH;	// 通常はこちら

    HDC_XD hDC = canvas->GetHDC();
    WinCoord win;
    getWindowCoordinate(canvas, m_degree, m_seed.GetDimensions(), &win);
    WinCoord winBack = win;	// AR5108対応

	//n V4 DirectBlt
	if (MPC_PCAP_IsDirectBlt(canvas->GetPrinterCaps())) {	//n canvasからDirectBltするかどうかのフラグを取得
		HRESULT hRes = m_seed.DirectBltPrint(hDC, &(win.log.pos), &(win.log.dim), m_degree, NULL);
		if (hRes == MP_NOERROR)
			return MP_S_PRINT_FINISHED;
			// DirectBltに失敗したら通常の印刷ルーチンを通る
	}

    BITMAPINFO *pbi = m_seed.InitForPrint(canvas, m_degree);
    if (!pbi) {
        return MP_E_UNEXPECTED;
    }

	// 2000.01.20 AR3258, 5154, 5211 対応
	// モノクロでPSプリンタまたは(Win9xで)PDFWriterの場合のみバンド幅を広くする
	if (pbi->bmiHeader.biBitCount == 1) {		// モノクロ
		if (canvas->GetPrinterType() == 1) {	// PSプリンタの場合
			bandWidth = BAND_WIDTH_MONOCHROME;
		} else {
			const int nStringSize = 256;
			char szTech[nStringSize];
			memset(szTech, 0, nStringSize);
			// (この文字列取得方法は一般的にWin9xの場合しか有効ではない)
			// (NTの場合はPDFWriterかどうかわからないが、NTではAR3258は発生しないので)
			::ExtEscape(hDC, GETTECHNOLOGY, NULL, NULL, nStringSize, (LPSTR)szTech);
			szTech[nStringSize - 1] = NULL;	// (安全のため)
			//if (lstrcmp(szTech, SZTECH_PDF) == 0) {	// PDFWriterの場合
			if (lstrcmpA(szTech, SZTECH_PDF) == 0) {		// UNICODEビルド対応 GlobalSize M.Chikyu
				bandWidth = BAND_WIDTH_MONOCHROME;
			}
		}
	}

    int tech = GetDeviceCaps(hDC, TECHNOLOGY);
    DWORD objtype = GetObjectType(hDC);

    //971111 H.Sumida AR1510
    long isMonoFastPrint = 0;
    //V3.1:モノクロ印刷高速化対応部分のメンテナンス向上のためImageMagnifyを使用する
    ImageMagnify *pMagnify = 0;
	int mag = 0;
    if (m_seed.GetColorDepth() == 1) {
        if (tech == DT_RASPRINTER) {
            if (GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES) == 1) {
				POINT trimOffset;
                SIZE trimSize;
                NeedMagnifyResult ret = needMagnify(hDC, pbi, m_degree, &win, &mag, &trimOffset, &trimSize);
                switch (ret) {
                case need_mag:
                case need_mag_with_trim:
                    isMonoFastPrint = 1;
                    pMagnify = new ImageMagnify;
                    if (!pMagnify) {
                        ImagePDSeed::FreeBitmapInfo(pbi);
                        m_seed.FinishForPrint();
                        return MP_E_UNEXPECTED;//メモリ不足
                    }
                    pMagnify->pSrcBI = pbi;
                    pMagnify->magnification = mag;
                    pMagnify->bTrimming = FALSE;
                    pMagnify->decodeLine = ImagePD<ImagePDSeed>::GetLine4PrintDispatch;
                    pMagnify->decodeArg = (void *)&m_seed;
		            if (ret == need_mag_with_trim) {
                        pMagnify->bTrimming = TRUE;
						pMagnify->trimOffset = trimOffset;
                        pMagnify->trimSize = trimSize;
		            }
                    if (pMagnify->init() < 0) {
                        //error
                        ImagePDSeed::FreeBitmapInfo(pbi);
                        m_seed.FinishForPrint();
                        delete pMagnify;
                        return MP_E_UNEXPECTED;
                    }
                    break;
                case no_mag:
                default:
                    //なにもしない
                    break;
                }
            }
        }
    }

    //971210 AR1511対策:強制StretchDIBitsモード追加
    BOOL forceUseStretchDIBits = FALSE;
    if (m_seed.GetColorDepth() == 1 && tech == DT_RASDISPLAY && objtype == OBJ_MEMDC) {
        HBITMAP_XD dummy_bmp = ::CreateCompatibleBitmap(hDC, 1, 1);
        if (dummy_bmp) {
            BITMAPINFOHEADER bih;
            bih.biSize = sizeof(BITMAPINFOHEADER);
            bih.biBitCount = 0;
            if (GetDIBits(hDC, dummy_bmp, 0, 0, 0, (BITMAPINFO *)&bih, DIB_RGB_COLORS)) {
                if (bih.biBitCount == 1) {
                    forceUseStretchDIBits = TRUE;
                }
            }
            DeleteObject(dummy_bmp);
        }
    }

	// AR4036対応 (AR3185 高速印刷ルーチンの見直しPS対応も含む)
	/* モノクロイメージをPSプリンタに出力する場合のみ
		1. 等倍の高速印刷ルーチンは通す。等倍でなかったら次の判定。
		2. サイズが一定値以下なら、バンド分割しないでメモリに全伸長して一気に描画する。
		  一定値以上ならバンド分割して高速印刷ルーチンは通さずに描画。いずれも黒=0、白=1のパレットにする。
	*/
	BOOL monoInvert = FALSE;	// 後でモノクロパレットを反転処理するかどうか
	if ((m_seed.GetColorDepth() == 1) && (canvas->GetPrinterType() == 1)) {	// モノクロでPSプリンタに出力するとき
		if (mag != 1) {
			if (pMagnify) {
				pMagnify->release();
				delete pMagnify;
				pMagnify = NULL;
				win = winBack;	// AR5108対応:needMagnifyを呼んで高速印刷ルーチンを通る場合は座標が変わってしまう場合があるので元に戻す
			}
			isMonoFastPrint = 0;
			monoInvert = TRUE;	// 常にパレットを黒=0、白=1にする
			DWORD dwImageSize = WIDTHBYTES(pbi->bmiHeader.biWidth) * pbi->bmiHeader.biHeight;
			if (dwImageSize < ALLBLT_MAX_SIZE)
				bandWidth = BAND_WIDTH_FULL;
		}
	}

	if (PRIMARYLANGID(GetUserDefaultLangID()) != LANG_JAPANESE) {
	// AR4036対応のため
		if (canvas->GetPrinterType() != 1) {
		// PSで等倍以外の場合は英語版で拡大印刷ルーチンは通さない
		// (PSならここは等倍の場合しか通らない)
			if (pMagnify) {
				pMagnify->release();
				delete pMagnify;
				pMagnify = NULL;
				win = winBack;	// needMagnifyを呼んで高速印刷ルーチンを通る場合は座標が変わってしまう場合があるので元に戻す
			}
			isMonoFastPrint = 0;
		}
	}

    //971210 AR1511対策:ImageShrinkを使わないモードを考慮.
    //  ImageShrink shrink -> ImageShrink *pShrinkに変更
    //  以下このための変更
    ImageShrink *pShrink = 0;
	long dstWidth, dstHeight;
	if (m_degree == 0 || m_degree == 180) {
		dstWidth = win.log.dim.cx;
		dstHeight = win.log.dim.cy;
	} else {
		dstWidth = win.log.dim.cy;
		dstHeight = win.log.dim.cx;
	}
    if (forceUseStretchDIBits || pMagnify) {
        //入力1bit/出力1bitの
        //イメージ変換出力or部分イメージコピー
        //ではshrinkを使わない
        //ImageMagnifyを使用するときもshrinkは使わない
	} else {
		/* AR4946対応
		   モノクロイメージをImageShrinkを使って印刷すると、イメージの方がプリンタの解像度より大きい場合、
		   転送するイメージがImageShrinkにより縮小され、出力は4bitグレーのビットマップとなる。
		   ほとんど縮小されない場合は、単純にデータ量が約4倍になってしまい、
		   印刷に非常に時間がかかってしまう場合がある。
		   しかし、印刷時間は単純に送るデータサイズに依るものでもなく、またImageShrinkを使わないと
		   サイズは小さくても送るビットマップのドット数は大きくなり、プリンタによっては障害を誘発してしまう恐れがある。
		   このため、ほとんど縮小されないのにImageShrinkにより4bitになってしまう場合のみ修正することにする。
		   縮小率の許容範囲は、拡大印刷ルーチンの等倍と同じ0.2%とする。(1999.09.27時点)
		   1999.10.04修正:
		   XS4120でスキャンしたイメージは0.064〜0.635%の誤差があったので、これに対応する。
		   若干余裕を持って、0.7%まで許容するように変更。
		   これによる影響は、従来4bitで縮小してWin32APIに渡していたのが1bitでStretchDIBitsにそのまま渡すだけで、
		   印刷結果が0.7%ずれるわけではない(座標としては同じ)。
		*/
		BOOL bUseShrink = TRUE;
		if ((tech == DT_RASPRINTER) && (m_seed.GetColorDepth() == 1)) {
			const double NOSHRINK_MAX_ERR = 0.7 / 100;	// 誤差0.7%まで
			double dxErr = (double)(pbi->bmiHeader.biWidth - dstWidth) / (double)dstWidth;
			double dyErr = (double)(pbi->bmiHeader.biHeight - dstHeight) / (double)dstHeight;
			if ((0 < dxErr) && (dxErr < NOSHRINK_MAX_ERR) &&
				(0 < dyErr) && (dyErr < NOSHRINK_MAX_ERR)) {
				// 縮小かつ誤差が微少な場合のみShrinkを使用しない
				bUseShrink = FALSE;
				forceUseStretchDIBits = TRUE;
			}
		}
		if (bUseShrink) {
			pShrink = new ImageShrink;
			if (!pShrink) {
				ImagePDSeed::FreeBitmapInfo(pbi);
				m_seed.FinishForPrint();
				return MP_E_UNEXPECTED;//メモリ不足
			}
		}
    }
    if (pShrink) {
        //>>Shrinkパラメータ設定
        pShrink->pSrcBI = pbi;
        pShrink->dstWidth = dstWidth;
        pShrink->dstHeight = dstHeight;
        pShrink->isGray = ::is_gray(pbi) ? 1 : 0;
        pShrink->colorReduction = FALSE;
        if (tech == DT_RASDISPLAY) {
            //displayかつ
            if (GetDeviceCaps(hDC, NUMCOLORS) != -1) {
                // !-1: palette color
                pShrink->colorReduction = TRUE;
            }
        }
        pShrink->decodeLine = ImagePD<ImagePDSeed>::GetLine4PrintDispatch;
        pShrink->decodeArg = (void *)&m_seed;
        //<<Shrinkパラメータ設定
        if (pShrink->init() < 0) {
            //error
            ImagePDSeed::FreeBitmapInfo(pbi);
            m_seed.FinishForPrint();
            delete pShrink;
            return MP_E_UNEXPECTED;
        }
    }

    ImageRotate rot;
    //>>Rotateパラメタ設定
    rot.mode = ImageRotate::MODE_PART;// 部分かページか
    rot.angle = m_degree;// 回転角 : 0,90,180,270
    rot.nLine = bandWidth;// バンド幅  (rotateで返る) 実際に処理したライン数
    //3パターンに分かれる
    if (pShrink) {
        rot.pSrcBI = pShrink->pDstBI;// 入力画像のbmpinfo
        rot.srcBISize = pShrink->dstBISize;// 入力画像のbmpinfoのサイズ
        rot.getLine = ImageShrink::getLineDispatch;// srcBitsに1ライン出力する関数のポインタ
        rot.getParam = (void *)pShrink;// getLineに必要なパラメータ構造体のポインタ
    } else if (pMagnify) {
        rot.pSrcBI = pMagnify->pDstBI;// 入力画像のbmpinfo
        rot.srcBISize = pMagnify->dstBISize;// 入力画像のbmpinfoのサイズ
        rot.getLine = ImageMagnify::getLineDispatch;// srcBitsに1ライン出力する関数のポインタ
        rot.getParam = (void *)pMagnify;// getLineに必要なパラメータ構造体のポインタ
    } else {
        rot.pSrcBI = pbi;// 入力画像のbmpinfo
        rot.srcBISize = getBISize(pbi);// 入力画像のbmpinfoのサイズ
        rot.getLine = ImagePD<ImagePDSeed>::GetLine4PrintDispatch;// srcBitsに1ライン出力する関数のポインタ
        rot.getParam = (void *)&m_seed;// getLineに必要なパラメータ構造体のポインタ
    }

    //<<Rotateパラメタ設定
    if (rot.init() < 0) {
        //error
        if (pShrink) {
            pShrink->release();
            delete pShrink;
        }
        if (pMagnify) {
            pMagnify->release();
            delete pMagnify;
        }
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForPrint();
        return MP_E_UNEXPECTED;
    }

    //回転後のバッファを獲得
    unsigned char *rot_buf = new unsigned char [rot.dstBufSize];
    if (!rot_buf) {
        //error
        if (pShrink) {
            pShrink->release();
            delete pShrink;
        }
        if (pMagnify) {
            pMagnify->release();
            delete pMagnify;
        }
        rot.release();
        ImagePDSeed::FreeBitmapInfo(pbi);
        m_seed.FinishForPrint();
        return MP_E_OUTOFMEMORY;
    }

    // パレットをセット
    HPALETTE hPal = CreateMediaPalette();
    HPALETTE hOldPal = MPSelectPalette(hDC, hPal, canvas);
    ::RealizePalette(hDC);

    // 971215 komoda
    // 速度優先のため forceUseStretchDIBitsモードでもCONCをセットするよう変更
    ::SetStretchBltMode(hDC, COLORONCOLOR);
    print_result_t ret;
    //980320 matsu AR2705:モノクロ高速印刷と通常印刷を分けた
    if (isMonoFastPrint) {
        ret = print_rotate_MonoFast(hDC, m_degree, &win, &rot, rot_buf, info, monoInvert);
    } else {
        ret = print_rotate(hDC, m_degree, &win, &rot, rot_buf, info, forceUseStretchDIBits, monoInvert);
    }

    ::SelectPalette(hDC, hOldPal, FALSE);
    ::DeleteObject(hPal);
    delete [] rot_buf;
    rot.release();
    if (pShrink) {
        pShrink->release();
        delete pShrink;
    }
    if (pMagnify) {
        pMagnify->release();
        delete pMagnify;
    }
    ImagePDSeed::FreeBitmapInfo(pbi);
    m_seed.FinishForPrint();

    if (ret == print_cancel) {
        return MP_S_PRINT_CANCELED;
    } else if (ret == print_error) {
        //error
        return MP_E_UNEXPECTED;
    }
    //print_success
    return MP_S_PRINT_FINISHED;
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::Load(MP_Octet *inbase, long insize, IStgObject *stgobj) {
    ///回転角のとりだし
	// Loadされていなければm_degree = 0となる
	m_stgobj = stgobj; // stgobjは getDegreeで必要
	m_degree = getDegree();
    HRESULT ret = m_seed.Load(inbase, insize, stgobj);
    m_bmpSize = m_seed.GetPixels();
    return ret;
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::CreateFromDIBFile(MP_Path *dibfilepath, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) {
    HRESULT result = m_seed.CreateFromDIBFile(dibfilepath, mdim, level, info);
    if (result == MP_NOERROR)
        m_degree = 0;//成功したら回転角を0度にする 971105
    return result;
}

//07.09.19 - M.Chikyu UNICODE対応
// 対応関数の追加
template <class ImagePDSeed>
//HRESULT ImagePD<ImagePDSeed>::CreateFromDIBFile(MP_Path *dibfilepath, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) {
HRESULT ImagePD<ImagePDSeed>::CreateFromDIBFileW(const MP_WPath *dibfilepathW, MP_Dim mdim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) {

	//07.09.19 - M.Chikyu UNICODE対応
    //HRESULT result = m_seed.CreateFromDIBFile(dibfilepath, mdim, level, info);
    HRESULT result = m_seed.CreateFromDIBFileW(dibfilepathW, mdim, level, info);
    if (result == MP_NOERROR)
        m_degree = 0;//成功したら回転角を0度にする 971105
    return result;
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::CreateFromMemDIB(BITMAPINFO *dibinfo, unsigned char *imagedata, MP_Dim dim, MP_Integer level, MPC_AdvCancelInfo* info = NULL) {
    HRESULT result = m_seed.CreateFromMemDIB(dibinfo, imagedata, dim, level, info);
	m_bmpSize = m_seed.GetPixels();// 02.12.04 h.arai V502 AR8359対応
    if (result == MP_NOERROR)
        m_degree = 0;//成功したら回転角を0度にする 971105
    return result;
}


template <class ImagePDSeed>
int ImagePD<ImagePDSeed>::GetLine4DrawDispatch(unsigned char *buf, void *arg) {
    if (arg)
        return ((ImagePDSeed *)arg)->GetLineForDraw(buf);
    else
        return -1;
}

template <class ImagePDSeed>
int ImagePD<ImagePDSeed>::GetLine4PrintDispatch(unsigned char *buf, void *arg) {
    if (arg)
        return ((ImagePDSeed *)arg)->GetLineForPrint(buf);
    else
        return -1;
}

template <class ImagePDSeed>
int ImagePD<ImagePDSeed>::GetLine4GetDIBDispatch(unsigned char *buf, void *arg) {
    if (arg)
        return ((ImagePDSeed *)arg)->GetLineForGetDIB(buf);
    else
        return -1;
}

//n V4新規追加
template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::GetCompDataToFile(MP_Path* dstPath, MP_Integer* compDataType)
{
	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckFromStgObj(m_stgobj, MP_PERM_COPY);
		if (hRes != MP_NOERROR) return hRes;
	}

	return m_seed.GetCompDataToFile(dstPath, compDataType);
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::GetCompDataToFileW(const MP_WPath* dstPathW, MP_Integer* compDataType)
{
	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckFromStgObj(m_stgobj, MP_PERM_COPY);
		if (hRes != MP_NOERROR) return hRes;
	}

	//07.09.19 - M.Chikyu UNICODE対応
	//return m_seed.GetCompDataToFile(dstPath, compDataType);
	return m_seed.GetCompDataToFileW(dstPathW, compDataType);
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::GetCompDataToHandle(HGLOBAL hData, MP_Integer* compDataType)
{
	{	// V4 AuthPermCheck
		HRESULT hRes = PermCheckFromStgObj(m_stgobj, MP_PERM_COPY);
		if (hRes != MP_NOERROR) return hRes;
	}

	return m_seed.GetCompDataToHandle(hData, compDataType);
}

// AR5442対応
#include "pd3local.h"
const MP_ObjectType CLSID_HBODYCONT_ = 0x8010;
template <class ImagePDSeed>
MP_Integer ImagePD<ImagePDSeed>::GetColorType(BOOL bCheck)
{
	if (!bCheck) {
		// AR5442対応：ヘテロ以外の場合はビットマップに描画して判断する
		if (m_stgobj) {
			MP_ObjectType type = m_stgobj->GetObjectType();
			if (type != CLSID_HBODYCONT_) {
				CCheckColorFromBmp check;
				MP_Dim dim;
				GetPDInfo(NULL, NULL, NULL, &dim);
				HRESULT hRes = check.CreateBmp(m_session, dim);
				if (hRes < 0)
					return MP_COLORTYPE_MONO;
				DrawInternal(check.GetCanvas(), 0);
				return check.GetColorType();
			}
		}
		return m_colorType;
	}
	return m_seed.GetColorType(bCheck);
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::GetPercent()
{
	return m_seed.GetPercent();
}

template <class ImagePDSeed>
HRESULT ImagePD<ImagePDSeed>::SetPercent(MP_Integer percent)
{
	return m_seed.SetPercent(percent);
}

//#endif //WIN32

#endif //!_IMAGE_PD_TEMPLATE_H_

//CHANGE LOG
//97.10.03 - matsu - 新規作成(V3)
//97.10.04 - Sumida - アイコン用PDをBMPPDSeedとして作成するように変更
//97.10.07 - komoda - 表示キャッシュを初期化時に白く塗るよう変更
//97.10.15 - Sumida - アイコン用PDをOKDPDSeedとして作成するように変更
//97.10.15 - komoda - OnDrawで、伸張が必要ない場合にFINISHを返さない不具合を修正
//97.10.15 - komoda - OnDrawで、表示キャッシュサイズ変更時にメンバ変数の初期化忘れを修正
//97.10.23 - matsu - AR1335対応: ConvertToDIBHandleでBITMAPINFOHEADERだけでも返せるようにした
//97.10.23 - matsu - AR1390対応: 「OnDrawでfinishを返す以前にDestroyされるとリークする」を修正
//97.10.23 - matsu - OnPrintでパレットを解放していなかった(リソースリーク)、を修正
//97.10.27 - matsu - AR1423:ConvertToDIBFile(Handle)で、bitcountが4bit以下かつbiClrUsedが0、のときもcmap_entriesが正しくなるようにした。
//97.10.27 - matsu - AR1428:OnDrawでキャッシュを白く塗りつぶすときに黒い枠が描かれないように白いペンを使うようにした
//97.10.28 - komoda - CreateIconPDで解像度が0ならばサイズから計算するよう変更
//97.10.31 - Sumida - #pdのSave時に、#rotate属性をSetAttributeするように追加
//97.10.31 - komoda - CreateIconPD解像度が0ならばサイズから計算する部分の誤りを修正
//97.11.05 - matsu - AR1501対応: OnDrawでメモリリークを修正
//97.11.05 - matsu - AR1502対応: CreateIconPDでメモリリークを修正
//97.11.05 - matsu - CreateIconPDでiconpd作成後に回転角をセットするようにした
//97.11.05 - matsu - CreateFromXXXで作成成功後に回転角を0度にセットするようにした
//97.11.05 - matsu - AR1495: OnDrawで、伸長が終了していたらneedLineを更新しないようにした。
//97.11.11 - Sumida - AR1510: OnPrintで、モノクロビットマップ印刷パフォーマンス改善実施
//97.11.27 - matsu - AR1711対応:OnDrawの先頭でCreateCompatibleDC(hDC)が失敗したとき(付箋上のBMP-content)の動作をV2と同等な動作にした
//97.12.10 - matsu - AR1511:モノクロイメージ変換出力(1bit->1bit)性能改善のため「強制StretchDIBits(Shrinkを使わない)モード」を追加(OnPrint)
//97.12.15 - komoda - AR1511:forceUseStretchDIBitsモードでもColorOnColorをセットするよう変更
//97.12.17 - komoda - AR1807:回転性能改善のためOnDraw,Loadを変更
//97.12.19 - matsu - AR1807その2:rotateCacheBmpで、回転によりwin.dev.dimの値が1pixずれる場合がある。そのときはキャッシュの回転をしない。
//97.12.19 - Sumida - AR1510: NT4.0モノクロ印刷改善のための修正。OnPrint()を修正。
//97.12.26 - matsu - AR2119:InitForGetDIB(100)と呼んでいるところをInitForGetDIB(0)に修正。0はヒントなし(オリジナルサイズ)を意味する
//98.01.28 - ysato - AR2208対応、DWVLTWEBでの表示をSelectPalette(TRUE)に変更
//98.02.18 - komoda - AR2362:CreateIconPDで縮小画像のサイズ計算が誤っていたのを修正
//98.02.26 - Sumida - AR2558:AP版でWin95上の動作のとき、モノクロ印刷改善実施しない
//98.03.03 - komoda - AR2362:JPEG圧縮の場合に誤っていたのを修正
//98.03.20 - Sumida - AR2705:AP版でNT40上の動作のとき、モノクロ印刷改善実施しない
//98.05.06 - matsu - V3.1モノクロ高速印刷ルーチン共通化: 変更OnPrint(), ImageMagnifyを使用
//98.05.06 - matsu - V3.1対応: いくつかMP_DimをSIZEに変更
//98.05.11 - matsu - V3.1対応: ConvertToDIBFile()で、set_bmp_to_file()からのFile I/O系エラーを返すようにした。
//98.05.22 - komoda - AR2800対応: ImageMagnifyのパラメータ変更にともなう修正
//98.06.08 - komoda - V3.1OLEサーバ対応: MetaFileDC出力の処理を追加
//98.06.15 - komoda - AR2928: Rotate()でキャッシュビットマップの回転を行うよう変更
//98.06.26 - komoda - AR2989: OnDraw(),OnPrint()中のSelectPalette()を一部MPSelectPalette()に変更
//98.07.07 - Komoda - V3.1モノクロ縮小の高速化:1bitの場合はOnPrint()で描画幅を256ラインにする
//98.11.11 - Nakazawa - ランレングスデータ専用高速縮小処理追加
//98.01.06 - Nakazawa - AR3258: OnPrint()で、モノクロのときはバンド幅を大きくとるようにした
//99.04.27 - Nakazawa - V4追加分実装
//99.05.20 - Komoda - ImagePDSeed::GetColorType()を追加
//99.05.26 - Nakazawa - V4 セキュリティ 認証パーミッションチェック追加
//99.05.31 - Nakazawa - ConvertToDIBFile でキャンセルor失敗した場合はファイルを消すようにした
//99.06.14 - Nakazawa - get_degree 追加 (V4 MH->MMRコンバート用)
//99.06.14 - Nakazawa - V4 セキュリティ 認証パーミッションチェックに追加認証コードを追加
//99.07.23 - Nakazawa - V4 モノクロ印刷ルーチンの見直しは保留とする
//99.07.27 - Nakazawa - V4 AR4037 : キャンセルコールバックは0%・100%それぞれ一回だけ呼ぶ
//99.07.27 - Ichiriki - V4 Get/SetPercentを追加
//99.07.30 - Nakazawa - V4 Save時に拡張MFPDのJpegデータを削除する実装を追加
//99.08.03 - Nakazawa - V4 コードレビューの結果を反映
//99.08.05 - Nakazawa - V4 AR4229:IconPDのSave時に誤ってJpegデータを削除していた場所を修正
//99.08.27 - Nakazawa - V4 AR4580対応: Rotate時にImageShrinkRLを用いた場合の不具合対応
//99.09.07 - Nakazawa - V4 AR4036対応: PS印刷時に黒筋がでる対策(AR3185 高速印刷ルーチンの見直しPS対応も含む)
//99.09.20 - Nakazawa - V4 AR4036残項目対応: PS印刷時でStretchを使用する場合は常にパレットを固定するように変更
//99.09.22 - Nakazawa - V4 AR4647対応:描画時にMetafileDCに対してはヘテロのみ保護するように変更
//99.09.27 - Nakazawa - V4 AR4946対応:モノクロイメージ印刷時にほぼ等倍の場合はShrinkを通さないように修正
//99.10.04 - Nakazawa - V4 AR4946対応修正:XS4120でスキャンされたイメージの誤差に対応
//99.10.13 - Nakazawa - V4 AR5108対応:AR4036,3185の副作用を修正
//99.12.08 - Nakazawa - V4 AR5154, 5211 個別対応追加
//00.01.20 - Nakazawa - V4.02 AR3258, 5154, 5211 全てに対応するためプリンタによる場合分けを追加
//00.03.24 - Nakazawa - V4 英語版対応：PSプリンタのときのみ拡大印刷ルーチンを通るように修正
//00.05.10 - Nakazawa - V4 AR5442 ヘテロ以外の場合はビットマップに描画して判断するように修正
//00.05.10 - Nakazawa - V4 AR5442 レビューの結果を反映
//00.05.12 - Nakazawa - V4 AR5442 修正漏れ分を修正
//02.02.22 - Komoda - V5 キャッシュなし表示対応
//2002.02.28 - Ichikawa V5.0 アプリケーションページのイメージ低解像度変換 追加 (ThinImage)
//02.05.10 - Komoda - V5 AR7242 キャッシュ作成の条件を変更
//02.07.18 - Komoda - V5 AR7530 StretchBltが失敗した場合の対策を追加
//02.11.05 - h.arai - V5.0.2 AR6597 UpdateCacheSizeにCalcCacheSizeで求めた値をセットするように修正した
//02.12.02 - h.arai - V5.0.2 AR8359対応 アイコン用DIBのサイズをm_bmpSizeにセットするように修正した
// -----6.0
//04.09.27 - Tashiro - AR11061 特定範囲の倍率で×表示になる動作の修正(AR8341のデグレード)
//04.10.18 - Komoda - AR11201 Win9xでキャッシュビットマップのサイズが異常になる不具合の修正
//----V6.0.5開発
//05.11.09 - Nakazawa - 64bit対応
//----V6.2.2
//2007.05.17 - Tashiro - AR13155 MP_PD::RotateOnMem追加
//----V7.0
//2007.08.14 - Komoda  - V7 Unicode I/Fの追加
//2008.09.05 - Tashiro - V7 AR15288 アノテPDがEMFになったので、DrawInternalはEMF-DCに対しても通常描画
