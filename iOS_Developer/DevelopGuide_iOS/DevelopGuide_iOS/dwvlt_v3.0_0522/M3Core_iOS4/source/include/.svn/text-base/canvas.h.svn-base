// File: CANVAS.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
* CANVAS.H	Win32用描画対象管理ユーティリティ
*
*	MPCMedia::OnDraw(), MPCMedia::OnPrint()を利用するアプリケーションが実装し
*	MP / Content コアオブジェクト実装者がこのインタフェースに対して描画する
*
*	MPC_DLL.libをリンクして
*		CreateMPCanvasでデフォルト動作をするキャンバスを生成できる、
*		不要になったらobj->Destroyで解放する
*/

#ifndef MPCANVAS_H
#define MPCANVAS_H

#include "mpc_pd.h"

//V3 削除　DLLBINDFUNC_(MP_Canvas*, MPCreateWMFCanvas)(MPCSession* session, MP_Dim dim, HRESULT* phres = NULL);
//V3 削除　DLLBINDFUNC_(MP_PD*, MPCreateWMFPDAndDestroyWMFCanvas)(MPCSession* session, MP_Canvas** ppcanvas, HRESULT* phres);

inline MP_Canvas* MPCreateWMFCanvas(MPCSession* session, MP_Dim mdim, HRESULT* phres = NULL)
/*
	MPCreateWMFCanvas
	WMFDCを内部に持ったキャンバスを作成するインライン関数
	mdim にはメタファイルの寸法を、メディア座標＆正整数で指定しなければならない。
	成功したら MP_Canvas へのポインタを、失敗したらNULLを返す。
*/
{
#ifndef _M3CORE_MP_

	if ( (mdim.cx <= 0) || (mdim.cy <= 0) ) {
		if ( phres )
			*phres = MP_E_INVALIDARG;
		return NULL;
	}

	// 09.07.14 - M.Chikyu UNICODE,WindowsMobile対応
	//HDC	hDC = ::CreateMetaFile(NULL);
	HDC_XD	hDC = ::CreateMetaFileA(NULL);
	if ( !hDC ) {
		if ( phres )
			*phres = MP_E_INVALIDARG;
		return NULL;
	}

	MP_Canvas*	wmfcanvas = ::MPCreateRAWCanvas(session, hDC, 300, mdim, phres);	// AR8314 75dpi→300dpi

	if ( !wmfcanvas) {

		HMETAFILE_XD	hMF = ::MPF_CloseMetaFile( hDC );
		if ( hMF )
			::MPF_DeleteMetaFile(hMF);
		return NULL;
	}

	SIZE size = wmfcanvas->GetSIZE(mdim);

	::MPF_SetWindowOrgEx(hDC, 0, 0, NULL);
	::MPF_SetWindowExtEx(hDC, size.cx, size.cy, NULL);

	return wmfcanvas;

#else

	return NULL;

#endif // _M3CORE_MP_
}


inline MP_Canvas* MPCreateEMFCanvas(MPCSession* session, MP_Dim mdim, HRESULT* phres = NULL)
/*
	MPCreateEMFCanvas
	EMFDCを内部に持ったキャンバスを作成するインライン関数
	mdim にはメタファイルの寸法を、メディア座標＆正整数で指定しなければならない。
	成功したら MP_Canvas へのポインタを、失敗したらNULLを返す。
*/
{
#ifndef _M3CORE_MP_

	if ( (mdim.cx <= 0) || (mdim.cy <= 0) ) {
		if ( phres )
			*phres = MP_E_INVALIDARG;
		return NULL;
	}

	int iDPI = 300;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = mdim.cx * iDPI / 2540;
	rect.bottom = mdim.cy * iDPI / 2540;
	HDC_XD hDC = ::CreateEnhMetaFile(NULL, NULL, &rect, NULL);

	if ( !hDC ) {
		if ( phres )
			*phres = MP_E_UNEXPECTED;
		return NULL;
	}

	MP_Canvas*	emfcanvas = ::MPCreateRAWCanvas(session, hDC, iDPI, mdim, phres);	// AR8314 75dpi→300dpi

	if ( !emfcanvas) {
		HENHMETAFILE_XD	hMF = ::CloseEnhMetaFile( hDC );
		if ( hMF )
			::MPF_DeleteEnhMetaFile(hMF);
		return NULL;
	}

	SIZE size = emfcanvas->GetSIZE(mdim);

	::MPF_SetWindowOrgEx(hDC, 0, 0, NULL);
	::MPF_SetWindowExtEx(hDC, size.cx, size.cy, NULL);

	return emfcanvas;

#else

	return NULL;

#endif // _M3CORE_MP_
}

inline MP_PD*	MPCreateWMFPDAndDestroyWMFCanvas(MPCSession* session, MP_Canvas** ppcanvas, HRESULT* phres)
/*
	MPCreateWMFPDAndDestroyWMFCanvas
	WMFCanvasを開放し、キャンバス内部に保持していたメタファイルから WMFPD を生成する
	リターン値
		!NULL	作成したWMFPDへのアドレスを返す。キャンバスは解放される。*ppcanvas はNULLを返す。
		NULL	エラー。　*ppcanvasがNULLでない場合、呼び出し元でキャンバスを解放する
*/
{
#ifndef _M3CORE_MP_

	if (phres) *phres = MP_E_INVALIDARG;
	if ( (!ppcanvas) || (!session) ) return NULL;

	MP_Canvas*	canvas = *ppcanvas;

	if ( ! canvas ) return NULL;

	HDC_XD	hDC = canvas->GetHDC();
	MP_Dim	mdim = canvas->GetCanvasDim();

	HMETAFILE_XD	hMF = ::MPF_CloseMetaFile( hDC );
	if ( ! hMF ) {
		// ppcanvas が正しい メタファイルDCを持っていなかったとみなし、canvasを開放せずにMP_E_INVALIDARGを返す。
		// CloseMetafileでWinAPIからエラー復帰した場合に、hDCが有効と保証されているかどうかは未確認
		return NULL;
	}

	canvas->Destroy();
	*ppcanvas = NULL;	//この時点で利用者側のcanvasは無効になる

	METAFILEPICT_XD mfl;
	mfl.mm = MM_ANISOTROPIC;
	mfl.hMF = hMF;
	mfl.xExt = mdim.cx;
	mfl.yExt = mdim.cy;

	MP_PD* pd = ::MPCreateWMFPD(session, mfl, phres);
	if ( ! pd ) {
		// リソースリークを避けるために HMETAFILEを解放する
		::MPF_DeleteMetaFile(mfl.hMF);
		return NULL;
	}
	if (phres)
		*phres = MP_NOERROR;
	return pd;

#else

	return NULL;

#endif // _M3CORE_MP_
}

#ifdef new
#undef new
#include <vector>
#define new DEBUG_NEW
#else
#include <vector>
#endif

inline void ModifyEnhMetaFile(HENHMETAFILE_XD& hemf, MP_Dim mdim, SIZE wdim)
{
#ifndef _M3CORE_MP_

	enum {
		GDICOM_POLYGON = 0x00205744,
		GDICOM_POLYBEZTOBC = 0x00135744,
		GDICOM_BEGINPATH = 0x32305744,
		GDICOM_FILLPATH = 0x34305744,
	};

	UINT size = ::GetEnhMetaFileBits( hemf, 0, NULL );
	BYTE* srcbits = new BYTE[size];
	if ( srcbits == NULL ) {
		::MPF_DeleteEnhMetaFile(hemf);
		return;
	}
	::GetEnhMetaFileBits( hemf, size, srcbits );
	ENHMETAHEADER* pEmfHeader = (ENHMETAHEADER*)srcbits;
	pEmfHeader->rclFrame.left = 0;
	pEmfHeader->rclFrame.top  = 0;
	pEmfHeader->rclFrame.right  = mdim.cx;
	pEmfHeader->rclFrame.bottom = mdim.cy;
	pEmfHeader->szlDevice.cx = wdim.cx;
	pEmfHeader->szlDevice.cy = wdim.cy;
	pEmfHeader->szlMillimeters.cx = mdim.cx / 100;
	pEmfHeader->szlMillimeters.cy = mdim.cy / 100;
	pEmfHeader->szlMicrometers.cx = mdim.cx * 10;
	pEmfHeader->szlMicrometers.cy = mdim.cy * 10;


	// 塗りつぶしを行うレコードをV6の透過対応ずみレコードに変換する
	// FillPath, Polygon16, Ellipse ⇒ GdiComment(FillPath)
	std::vector<BYTE> dstbits;
	int nRecords = 0;
	bool modified = false;

	UINT offset = 0;
	bool permeable = false;
	while (offset < size) {
		EMR* record = (EMR*)&srcbits[offset];
		BYTE* p = (BYTE*)record;
		switch (record->iType) {
		default:
			dstbits.insert(dstbits.end(), p, p + record->nSize);
			nRecords += 1;
			break;
		case EMR_GDICOMMENT:
			{
				EMRGDICOMMENT* pGDIComment = (EMRGDICOMMENT*)p;
				//if (pGDIComment->cbData == lstrlen("DW3:PermeableON") + 1 &&
				if (pGDIComment->cbData == lstrlenA("DW3:PermeableON") + 1 &&			// UNICODEビルド対応 GlobalSize M.Chikyu
					//lstrcmp((char*)pGDIComment->Data, "DW3:PermeableON") == 0) {
					lstrcmpA((char*)pGDIComment->Data, "DW3:PermeableON") == 0) {		// UNICODEビルド対応 GlobalSize M.Chikyu
						permeable = true;
				}
				//else if (pGDIComment->cbData == lstrlen("DW3:PermeableOFF") + 1 &&
				else if (pGDIComment->cbData == lstrlenA("DW3:PermeableOFF") + 1 &&		// UNICODEビルド対応 GlobalSize M.Chikyu
					//lstrcmp((char*)pGDIComment->Data, "DW3:PermeableOFF") == 0) {
					lstrcmpA((char*)pGDIComment->Data, "DW3:PermeableOFF") == 0) {		// UNICODEビルド対応 GlobalSize M.Chikyu
						permeable = false;
				}
				else {
					dstbits.insert(dstbits.end(), p, p + record->nSize);
					nRecords += 1;
				}
			}
			break;
		case EMR_ENDPATH: //ENDPATH + FILLPATH
			{
				EMR* next = (EMR*)(&srcbits[offset + record->nSize]);
				if (permeable && next->iType == EMR_FILLPATH) {
					offset += record->nSize;
					record = next;
					EMR e = {EMR_GDICOMMENT, sizeof(DWORD) * 4};
					DWORD arg[2] = {sizeof(DWORD), GDICOM_FILLPATH};
					dstbits.insert(dstbits.end(), (BYTE*)&e, (BYTE*)&e + sizeof(e));
					dstbits.insert(dstbits.end(), (BYTE*)arg, (BYTE*)(arg + 2));
					nRecords += 2;
				} else {
					dstbits.insert(dstbits.end(), p, p + record->nSize);
					nRecords += 1;
				}
			}
			break;
		case EMR_POLYGON16:
			if (permeable) {
				EMRPOLYGON16* polygon = (EMRPOLYGON16*)p;

				EMR emr1 = {EMR_GDICOMMENT, sizeof(DWORD) * 4};
				DWORD arg1[2] = {sizeof(DWORD), GDICOM_BEGINPATH};
				dstbits.insert(dstbits.end(), (BYTE*)&emr1, (BYTE*)&emr1 + sizeof(emr1));
				dstbits.insert(dstbits.end(), (BYTE*)arg1, (BYTE*)arg1 + sizeof(arg1));

				EMR emr2 = {EMR_GDICOMMENT, sizeof(DWORD) * 5 + sizeof(WORD) * 2 * polygon->cpts};
				DWORD flag = 0x20000000;
				DWORD arg2[3] = {sizeof(DWORD), GDICOM_POLYGON | flag, polygon->cpts};
				dstbits.insert(dstbits.end(), (BYTE*)&emr2, (BYTE*)&emr2 + sizeof(emr2));
				dstbits.insert(dstbits.end(), (BYTE*)arg2, (BYTE*)arg2 + sizeof(arg2));
				dstbits.insert(dstbits.end(), (BYTE*)polygon->apts, (BYTE*)polygon->apts + sizeof(WORD) * 2 * polygon->cpts);

				EMR emr3 = {EMR_GDICOMMENT, sizeof(DWORD) * 4};
				DWORD arg3[2] = {sizeof(DWORD), GDICOM_FILLPATH};
				dstbits.insert(dstbits.end(), (BYTE*)&emr3, (BYTE*)&emr3 + sizeof(emr3));
				dstbits.insert(dstbits.end(), (BYTE*)arg3, (BYTE*)arg3 + sizeof(arg3));

				nRecords += 3;
			} else {
				dstbits.insert(dstbits.end(), p, p + record->nSize);
				nRecords += 1;
			}
			break;
		case EMR_ELLIPSE:
			if (permeable) {
				EMRELLIPSE* ellipse = (EMRELLIPSE*)p;

				EMR emr1 = {EMR_GDICOMMENT, sizeof(DWORD) * 4};
				DWORD arg1[2] = {sizeof(DWORD), GDICOM_BEGINPATH};
				dstbits.insert(dstbits.end(), (BYTE*)&emr1, (BYTE*)&emr1 + sizeof(emr1));
				dstbits.insert(dstbits.end(), (BYTE*)arg1, (BYTE*)arg1 + sizeof(arg1));

				EMR emr2 = {EMR_GDICOMMENT, sizeof(DWORD) * 5 + sizeof(DWORD) * 2 * 13};
				int nPoints = 13;
				int flag = 0;
				DWORD arg2[3] = {sizeof(DWORD), flag | GDICOM_POLYBEZTOBC, nPoints};
				int x = ellipse->rclBox.left;
				int y = ellipse->rclBox.top;
				int w = ellipse->rclBox.right - ellipse->rclBox.left;
				int h = ellipse->rclBox.bottom - ellipse->rclBox.top;
				int w1 = (int)(w * 0.22386);
				int w2 = (int)(w * 0.5);
				int w3 = w - 1 - w1;
				int w4 = w - 1;
				int h1 = (int)(h * 0.22386);
				int h2 = (int)(h * 0.5);
				int h3 = h - 1 - h1;
				int h4 = h - 1;
				POINT coord[13] = {
					{x + w4, y + h2},
					{x + w4, y + h1}, {x + w3, y + 0 }, {x + w2, y + 0 },
					{x + w1, y + 0 }, {x + 0,  y + h1}, {x + 0,  y + h2},
					{x + 0,  y + h3}, {x + w1, y + h4}, {x + w2, y + h4},
					{x + w3, y + h4}, {x + w4, y + h3}, {x + w4, y + h2}
				};
				dstbits.insert(dstbits.end(), (BYTE*)&emr2, (BYTE*)&emr2 + sizeof(emr2));
				dstbits.insert(dstbits.end(), (BYTE*)arg2, (BYTE*)arg2 + sizeof(arg2));
				dstbits.insert(dstbits.end(), (BYTE*)coord, (BYTE*)coord + sizeof(coord));

				EMR emr3 = {EMR_GDICOMMENT, sizeof(DWORD) * 4};
				DWORD arg3[2] = {sizeof(DWORD), GDICOM_FILLPATH};
				dstbits.insert(dstbits.end(), (BYTE*)&emr3, (BYTE*)&emr3 + sizeof(emr3));
				dstbits.insert(dstbits.end(), (BYTE*)arg3, (BYTE*)arg3 + sizeof(arg3));

				nRecords += 3;
			} else {
				dstbits.insert(dstbits.end(), p, p + record->nSize);
				nRecords += 1;
			}
			break;
		case EMR_SETWORLDTRANSFORM :
			// AR15494 SetWorldTransformの平行移動成分のみ、MPF_SetWindowOrgExに変換する
			// アノテの子供PD描画の時に出てくる特定パターンのみで有効
			{
				EMRSETWORLDTRANSFORM *pdef = (EMRSETWORLDTRANSFORM*)p;
				EMRSETWINDOWORGEX newdef2;
				newdef2.emr.iType = EMR_SETWINDOWORGEX;
				newdef2.emr.nSize = sizeof(EMRSETWINDOWORGEX);
				newdef2.ptlOrigin.x = (LONG)(-pdef->xform.eDx);
				newdef2.ptlOrigin.y = (LONG)(-pdef->xform.eDy);

				dstbits.insert(dstbits.end(), (BYTE*)&newdef2, (BYTE*)&newdef2 + sizeof(EMRSETWINDOWORGEX));

				nRecords += 1;
			}
			/*
			*/
			break;
		case EMR_MODIFYWORLDTRANSFORM :
			// AR15494 ModifyWorldTransformを無視する
			// アノテの子供PD描画の時に出てくる特定パターンのみで有効
			break;
		}
		offset += record->nSize;
	}
	ENHMETAHEADER* pHeader = (ENHMETAHEADER*)&dstbits[0];
	pHeader->nRecords = nRecords;
	pHeader->nBytes = (int)dstbits.size();

	HENHMETAFILE_XD hModifiedMF = ::MPF_SetEnhMetaFileBits((int)dstbits.size(), &dstbits[0]);
	delete[] srcbits;
	::MPF_DeleteEnhMetaFile(hemf);
	hemf = hModifiedMF;

#else

	::MPF_DeleteEnhMetaFile(hemf);
	return;

#endif // _M3CORE_MP_
}

inline MP_PD*	MPCreateEMFPDAndDestroyEMFCanvas(MPCSession* session, MP_Canvas** ppcanvas, HRESULT* phres)
/*
	MPCreateEMFPDAndDestroyEMFCanvas
	EMFCanvasを開放し、キャンバス内部に保持していたメタファイルから WMFPD を生成する
	リターン値
		!NULL	作成したEMFPDへのアドレスを返す。キャンバスは解放される。*ppcanvas はNULLを返す。
		NULL	エラー。　*ppcanvasがNULLでない場合、呼び出し元でキャンバスを解放する
*/
{
#ifndef _M3CORE_MP_

	if (phres) *phres = MP_E_INVALIDARG;
	if ( (!ppcanvas) || (!session) ) return NULL;

	MP_Canvas*	canvas = *ppcanvas;

	if ( ! canvas ) return NULL;

	HDC_XD	hDC = canvas->GetHDC();
	MP_Dim	mdim = canvas->GetCanvasDim();
	SIZE wdim = canvas->GetSIZE(mdim);

	// AR15539 アノテのEMF-PDがアノテ自身による表示と比べて若干小さくなる
	//  EMFのサイズに1mm以下の端数がある場合に問題が発生、端数を切り上げたアノテを作成する
	if (mdim.cx % 100 != 0) {
		ULONG newMdim_cx = (mdim.cx + 99) / 100 * 100;
		wdim.cx = MulDiv(wdim.cx, newMdim_cx, mdim.cx);
		mdim.cx = newMdim_cx;
	}
	if (mdim.cy % 100 != 0) {
		ULONG newMdim_cy = (mdim.cy + 99) / 100 * 100;
		wdim.cy = MulDiv(wdim.cy, newMdim_cy, mdim.cy);
		mdim.cy = newMdim_cy;
	}

	HENHMETAFILE_XD	hMF = ::CloseEnhMetaFile( hDC );
	if ( ! hMF ) {
		// ppcanvas が正しい メタファイルDCを持っていなかったとみなし、canvasを開放せずにMP_E_INVALIDARGを返す。
		// CloseMetafileでWinAPIからエラー復帰した場合に、hDCが有効と保証されているかどうかは未確認
		return NULL;
	}



	canvas->Destroy();
	*ppcanvas = NULL;	//この時点で利用者側のcanvasは無効になる

	ModifyEnhMetaFile(hMF, mdim, wdim);

	MP_PD* pd = ::MPCreateEMFPD(session, hMF, phres);
	if ( ! pd ) {
		// リソースリークを避けるために HMETAFILEを解放する
		//::MPF_DeleteMetaFile(mfl.hMF);
		::MPF_DeleteEnhMetaFile(hMF);
		return NULL;
	}
	if (phres)
		*phres = MP_NOERROR;
	return pd;

#else

	return NULL;

#endif // _M3CORE_MP_
}

inline HRESULT MP_Canvas_SpecialMagnifyForP3MPM(MPCSession* /*session*/, MP_Canvas* canvas, MP_Integer xpercent, MP_Integer ypercent)
{
	if ( !canvas )
		return MP_E_INVALIDARG;

	return canvas->Magnify(xpercent, ypercent);
}

// V3で削除　DLLBINDFUNC_(MP_Canvas*, MPCreateBMPCanvas)(MPCSession* session, MP_Dim dim, MP_Integer xpercent, MP_Integer ypercent, MP_Integer bitCount = 0, HDC hRefDC = NULL, HRESULT* phres = NULL);
// V3で削除　DLLBINDFUNC_(HMETAFILE, MPCDetachWMFAndDestroyWMFCanvas)(MPCSession* session, MP_Canvas** ppcanvas, MP_Integer* pXExt, MP_Integer* pYExt, HRESULT* phres);
// V3で削除　DLLBINDFUNC_(HBITMAP_XD, MPCDetachBMPAndDestroyBMPCanvas)(MPCSession* session, MP_Canvas** ppcanvas, HRESULT* phres, HPALETTE* p_hpal=NULL);




//	MP_RichCanvasは、Ｖ３で廃止


#define IID_MP_RichCanvas IID_MP_Canvas
#define MP_RichCanvas	MP_Canvas
inline MP_RichCanvas* MP_GetRichCanvas(MP_Canvas* c) { return c; }

#endif //MPCANVAS_H

// V3で削除	STDMETHOD_(MP_Rect,GetInvalidRect)(MP_Rect rect = MP_NULL_RECT) PURE;
// V3で削除	STDMETHOD(SetDrawRect)(MP_Rect rect = MP_NULL_RECT) PURE;
// V3で削除	STDMETHOD_(MP_Rect, IntersectDrawRect)(MP_Rect rect = MP_NULL_RECT) PURE;

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.22 - Ichiriki - MPCreateMediaPalette() 追加
//97.03.27 - Nagano - AR579 AR580 TuneRawDensity()を追加
//97.10.17 - Ichiriki - V2 バイナリ互換コードの除去
//97.10.21 - Ichiriki - V2コード　WMFCanvasのマクロ化
//99.2.24 - Ichiriki - V4開発：寸法を指定しないWMFCanvasのエラー復帰時に起きるリークを防止（CBS連携で発見した潜在障害）
//00.09.25 - Nakazawa - V41 MP_Canvas_SpecialMagnifyForP3MPMの未使用session引数をコメントアウト
