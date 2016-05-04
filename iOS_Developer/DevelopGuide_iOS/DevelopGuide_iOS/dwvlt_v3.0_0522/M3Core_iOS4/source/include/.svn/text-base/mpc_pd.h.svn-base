// File: MPC_PD.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.


#ifndef MPC_PD_H
#define MPC_PD_H

#include "mpc_api.h"

//#include <windows.h>
#include "win2mpf.h"

/*
描画関連のインターフェイス

描画関連のインターフェイスは、WinAPIのグラフィック関連機能と密接に関連する。
MPC_PD.H は、WIN32 API の ヘッダファイル windows.h に依存する。

PD関連　共通定義

定数・マクロ定義
*/

/*!
@brief キャンバス用情報ビットフラグ

MP_Canvasの GetPrinterCaps(), SetPrinterCaps() に使うビットフラグである。
*/
typedef unsigned long MPC_PrinterCaps;

/*!
@brief 透過描画をサポートするプリンタ

MPC_PCAP_SUPPORT_TRANSPARENCYビットは、透過機能を前提とした描画を行うかどうかの指定である。
PostScriptや、ESC/Pのように、透過描画能力を持たないPDLに対応するためにある。

このビットがクリアされている場合、透過描画部分をハッチなどの代替表現に置き換えて描画する。

キャンバス生成時のMPC_PCAP_SUPPORT_TRANSPARENCYビットの初期値は1である。
*/
const MPC_PrinterCaps MPC_PCAP_SUPPORT_TRANSPARENCY = (0x00000001L);

#define MPC_PCAP_SetTransparency(flag) (flag |= MPC_PCAP_SUPPORT_TRANSPARENCY)
#define MPC_PCAP_ClearTransparency(flag) (flag &= ~MPC_PCAP_SUPPORT_TRANSPARENCY)
#define MPC_PCAP_IsTransparency(flag) (flag & MPC_PCAP_SUPPORT_TRANSPARENCY)


/*!
MPC_PCAP_USE_PDビットは、本来の文書画像の描画を行うかどうかの指定である。
OLEサーバがWMFを生成する場合や、APIで文書画像を得る場合に用いる。

例えばリンクアノテーションの場合、
このビットがセットされていると、本来の文書画像を描画する。
このビットがクリアされていると、停止状態表示など、対話操作に依存した描画を行う。

キャンバス生成時のMPC_PCAP_USE_PDビットの初期値は0である。
*/
const MPC_PrinterCaps MPC_PCAP_USE_PD = (0x00000002L);	//本来の文書画像の描画を要求するキャンバス

#define MPC_PCAP_SetUsePD(flag) (flag |= MPC_PCAP_USE_PD)
#define MPC_PCAP_ClearUsePD(flag) (flag &= ~MPC_PCAP_USE_PD)
#define MPC_PCAP_IsUsePD(flag) (flag & MPC_PCAP_USE_PD)


/*!
@brief バックグラウンドパレットを使用する

VLT for WebやOLEサーバのインプレイス表示など、フォアグラウンドパレットを
セットしてほしくない場合に、このビットをセットする。

このビットがセットされている場合、PDの描画においてMPF_SelectPalette()の
引数bForceBackgroundの値をTRUEにする。

キャンバス生成時のMPC_PCAP_BACKGROUND_PALETTEビットの初期値は0である。
*/
const MPC_PrinterCaps MPC_PCAP_BACKGROUND_PALETTE = (0x00000004L);

#define MPC_PCAP_SetBackgroundPalette(flag) (flag |= MPC_PCAP_BACKGROUND_PALETTE)
#define MPC_PCAP_ClearBackgroundPalette(flag) (flag &= ~MPC_PCAP_BACKGROUND_PALETTE)
#define MPC_PCAP_IsBackgroundPalette(flag) (flag & MPC_PCAP_BACKGROUND_PALETTE)


/*!
@brief DirectBltを用いて圧縮イメージを直接送る(V4デバイス連携)

V4デバイス連携で、圧縮イメージを直接送るかどうかのフラグを操作する。
このフラグを見て、各PDでDirectBltするかどうかを判断する。
*/
const MPC_PrinterCaps MPC_PCAP_DIRECTBLT = (0x00000008L);

#define MPC_PCAP_SetDirectBlt(flag) (flag |= MPC_PCAP_DIRECTBLT)
#define MPC_PCAP_ClearDirectBlt(flag) (flag &= ~MPC_PCAP_DIRECTBLT)
#define MPC_PCAP_IsDirectBlt(flag) (flag & MPC_PCAP_DIRECTBLT)


/*!
@brief はみ出しオブジェクトのPD描画フォントサイズの矯正フラグ

AR5286:縦横混在のDocuWorks文書において用紙からはみ出た付箋の見え方が違い、
付箋上の文字の間隔が狭くなりつぶれて見えないことがある

上記AR対応のためにオブジェクト側でPD描画前にフラグをセットし、描画後にフラグをクリアする

フラグがセットされているときは、WMFPD描画時のCreateFontIndirectでフォントサイズが矯正される
*/
const MPC_PrinterCaps MPC_PCAP_STICKOUTCONTENT = (0x00000010L);

#define MPC_PCAP_SetStickOutContent(flag) (flag |= MPC_PCAP_STICKOUTCONTENT)
#define MPC_PCAP_ClearStickOutContent(flag) (flag &= ~MPC_PCAP_STICKOUTCONTENT)
#define MPC_PCAP_IsStickOutContent(flag) (flag & MPC_PCAP_STICKOUTCONTENT)


/*!
@brief 埋め込まれた文字の表示改善

埋め込まれたビットマップ文字/図形文字の表示画質改善(V6.0)

アプリケーションは設定によってこのフラグをセットする。
フラグがセットされるとビットマップや図形文字の表示が改善される。
初期値は従来の表示である。
*/
const MPC_PrinterCaps MPC_PCAP_DRAW_ADVANCE = (0x00000020L);

#define MPC_PCAP_SetDrawAdvance(flag) (flag |= MPC_PCAP_DRAW_ADVANCE)
#define MPC_PCAP_ClearDrawAdvance(flag) (flag &= ~ MPC_PCAP_DRAW_ADVANCE)
#define MPC_PCAP_IsDrawAdvance(flag) (flag & MPC_PCAP_DRAW_ADVANCE)


/*!
@brief WMFのPolygonの描画を矯正する

AR12815:直線アノテの細線が拡縮によって見えなくなってしまうことがある。

このフラグがセットされている時には、WMFPD描画時のplayPolygonで描画を矯正する。
*/
const MPC_PrinterCaps MPC_PCAP_REFORM_PLAYPOLYGON = (0x00000040L); // 拡縮による細線(直線アノテ)描画の矯正フラグ

#define MPC_PCAP_SetReformPlayPolygon(flag) (flag |= MPC_PCAP_REFORM_PLAYPOLYGON)
#define MPC_PCAP_ClearReformPlayPolygon(flag) (flag &= ~MPC_PCAP_REFORM_PLAYPOLYGON)
#define MPC_PCAP_IsReformPlayPolygon(flag) (flag & MPC_PCAP_REFORM_PLAYPOLYGON)


/*!
@brief 256色画面の見出しのパレット無効化

V6.2
AR12610対応：ディスプレイの画面色が256色の場合に、上(下)見出し設定で画像が指定されている場合に
Viewer Control/Viewer Light Controlで描画が繰り返して行われる。

このフラグがセットされている場合は、上(下)見出し設定のPDを描画する際にPALETTEに関連した描画命令を実施するかの判定処理を行わせる。
ディスプレイへの描画で、画面色が256色の場合はMPC_PCAP_DISABLE_PALETTEのフラグを立ててPALETTEに対する処理を実施しない。
*/
const MPC_PrinterCaps MPC_PCAP_DISABLE_PALETTE_FOR_PAGEFORM = (0x00000080L);

#define MPC_PCAP_SetDisablePaletteForPageform(flag) (flag |= MPC_PCAP_DISABLE_PALETTE_FOR_PAGEFORM)
#define MPC_PCAP_ClearDisablePaletteForPageform(flag) (flag &= ~MPC_PCAP_DISABLE_PALETTE_FOR_PAGEFORM)
#define MPC_PCAP_IsDisablePaletteForPageform(flag) (flag & MPC_PCAP_DISABLE_PALETTE_FOR_PAGEFORM)


/*!
@brief 256色画面のWMFのパレット無効化

V6.2
AR12610対応：ディスプレイの画面色が256色の場合に、上(下)見出し設定で画像が指定されている場合に
Viewer Control/Viewer Light Controlで描画が繰り返して行われる。

このフラグがセットされている場合、WMFPDの描画時にPALETTEに対する処理を実施しない。
描画命令のうち、実行しない処理は以下の二つ。
META_SELECTPALETTE
META_REALIZEPALETTE
*/
const MPC_PrinterCaps MPC_PCAP_DISABLE_PALETTE = (0x00000100L);

#define MPC_PCAP_SetDisablePalette(flag) (flag |= MPC_PCAP_DISABLE_PALETTE)
#define MPC_PCAP_ClearDisablePalette(flag) (flag &= ~MPC_PCAP_DISABLE_PALETTE)
#define MPC_PCAP_IsDisablePalette(flag) (flag & MPC_PCAP_DISABLE_PALETTE)


/*!
@brief ページ描画時に白枠を付けない設定

V7
AR14268対応：mppmodelからmpcmpへのオプション引渡しに使う。

MPPMConvertBasicPageToHDIBCentiDPI()関数に、白枠を付けない指定がされている場合、
このフラグを立てる。
ImplCompositeMedia::DrawChild()内部で、このフラグが立っていれば、クリップ範囲を
ページの大きさと等しくする。このフラグが立っていなければ従来通りの動作で、
クリップ範囲はページの大きさから1画素内側の大きさでクリップされる。
*/
const MPC_PrinterCaps MPC_PCAP_DISABLE_INSIDE_CLIP = (0x00000200L);

#define MPC_PCAP_SetDisableInsideClip(flag) (flag |= MPC_PCAP_DISABLE_INSIDE_CLIP)
#define MPC_PCAP_ClearDisableInsideClip(flag) (flag &= ~MPC_PCAP_DISABLE_INSIDE_CLIP)
#define MPC_PCAP_IsDisableInsideClip(flag) (flag & MPC_PCAP_DISABLE_INSIDE_CLIP)


/*!
@brief メタファイルをサムネール並みの画質で描画する指定

V7
mppmodelからmpcmpへのオプション引渡しに使う。

MPPMConvertBasicPageToHDIBCentiDPI()関数に、高画質指定がされている場合、
このフラグを立てる。
*/
const MPC_PrinterCaps MPC_PCAP_THUMBNAIL_QUALITY = (0x00000400L);

#define MPC_PCAP_SetThumbnailQuality(flag) (flag |= MPC_PCAP_THUMBNAIL_QUALITY)
#define MPC_PCAP_ClearThumbnailQuality(flag) (flag &= ~MPC_PCAP_THUMBNAIL_QUALITY)
#define MPC_PCAP_IsThumbnailQuality(flag) (flag & MPC_PCAP_THUMBNAIL_QUALITY)

// V7 ハイコントラスト
// MPC_ContrastDrawInfoのiContrastModeに指定する定数
const int MPC_CONTRAST_DRAW_NONE = 0;
	// ハイコントラスト表示をしないモード
const int MPC_CONTRAST_DRAW_TEXT = 1;
	// アプリ系はテキスト命令のみを描画する
	// イメージ系は2値化し、明色を背景色、暗色を前面色で描画する
const int MPC_CONTRAST_DRAW_COLOR_BIN = 2;
	// アプリ系はなるべく描画命令の色を2値化して描画する。(明色を背景色、暗色を前面色)
	// イメージ系は2値化し、明色を前面色、暗色を背景色で描画する
const int MPC_CONTRAST_DRAW_COLOR_CONT = 3;
	// アプリ系はなるべく描画命令の色を背景色と前面色の中間調で描画する
	// イメージ系はグレースケール化し、背景色と前面色の中間調で描画する

// MP_Canvas::Set/GetContrastDrawInfoに用いる構造体
struct MPC_ContrastDrawInfo {
	int iContrastMode;	// ハイコントラストのモード
	unsigned char ColorFore[3];	// 前面色 RGB順
	unsigned char ColorBack[3];	// 背景色 RGB順
};

/*!
@defgroup mpc_pd_function_utility [MPC_PD]ユーティリティ関数
*/
/*@{*/

/*!
@brief mediaの内容を描画したサムネイル用のHBITMAPとHPALETTEを返す。

DWDeskのサムネイル表示にのみ使用する。

取得したHBITMAP及びHPALETTEは利用者が解放しなければならない。

作成するHBITMAPの仕様は、
解像度：12.5dpi (75dpi換算で17%相当）
色数：作成時点の画面色と同じ（MPF_CreateCompatibleBitmapを使用）
である。

HPALETTEは、画面色が8bit（256色）で、かつ、p_hpalの値がNULLでなければ
DWCore内部で定義する固定のパレットを返す。
このパレットはMPCreateMediaPaletteで取得するパレットと同じである。

@param[in] media メディアオブジェクトのアドレス
@param[out] p_hpal パレットのハンドル格納アドレス
@return HBITMAP サムネイルのビットマップのハンドル
*/
DLLBINDFUNC_(HBITMAP_XD, MPCreateIconBitmap)(MPCMedia* media, HPALETTE* p_hpal=NULL);

/*!
@brief DWCore内部で定義する固定色のパレットを返す。

取得したHPALETTEは利用者が解放しなければならない。
*/
DLLBINDFUNC_(HPALETTE, MPCreateMediaPalette)(MPCSession* session);

/*!
@brief mediaの内容を描画したサムネイル用のDIBのメモリハンドルを返す。

DWDeskのサムネイル表示、DWViewerの一覧表示に使用する。

取得したメモリハンドルは利用者が解放しなければならない。

作成するDIBの仕様は、
解像度：12.5dpi (75dpi換算で17%相当）
色数：アプリページ、モノクロイメージページは8bit、カラーイメージページは24bit
である。
*/
DLLBINDFUNC_(HGLOBAL, MPCreateIconDIB)(MPCMedia* media);

/*!
@brief セキュリティのアイコンを作成する
@param secu
-	MP_S_PROTECTED_BY_PSWD		パスワードセキュリティのマークを要求
-	MP_S_PROTECTED_BY_DDSA		DDSAセキュリティのマークを要求<br>
	※　セキュリティシステムが追加されたら随時定義を拡張する
	(V5新機能)
	上記以外の値でもMPCAvailableSecurityTypesで取得した
	セキュリティのタイプを指定可能。

@param type
	11、大きい保護マーク		12、大きい保護マークのマスク
	21、小さい保護マーク		22、小さい保護マークのマスク

@retval	HBITMAP アイコンのビットマップハンドル
@retval NULL secuで指定したセキュリティシステムがインストールされていない場合など、
エラーが発生した場合は NULL を返す

ビットマップが不要になったら呼び出し側で破棄すること

@par ビットマップの仕様
LoadResourceで取得する事を想定している。
色数＝16と限定する。
パレット情報は返さない。
ビットマップの寸法は別途規定する。
*/
DLLBINDFUNC_(HBITMAP_XD, MPCCreateSecurityIcon)(MPCSession*session, MP_Integer secu, MP_Integer type);


/*!
@brief 利用可能なセキュリティのタイプを問合せる(V5以降)

@param types 利用可能なセキュリティのタイプを受け取る配列
-	NULLのときは代入は行わず、セキュリティの数をリターン値として返すのみ。
-	NULLでなければ、セキュリティの数以上確保された配列と仮定して、
	利用可能なセキュリティのタイプを代入する。
	セキュリティのタイプはMPCCreateSecurityIcon()の第1引数として利用できる。

@return
	利用可能なセキュリティの数
	負数の場合はエラー
*/
DLLBINDFUNC_(MP_Integer, MPCAvailableSecurityTypes)(MPCSession*session, MP_Integer* types);


/*!
@brief 署名マークのアイコンを作成する(V5以降)

@param type		11、署名マーク		12、署名マークのマスク

@retval	HBITMAP 署名マークのビットマップハンドル
@retval NULL エラーが発生した場合は NULL を返す

ビットマップが不要になったら呼び出し側で破棄すること
(署名モジュールによらず同じアイコンをサムネイル上に表示するので、タイプの指定などは特に無い)

@par ビットマップの仕様
LoadResourceで取得する事を想定している。
色数＝16と限定する。
パレット情報は返さない。
ビットマップの寸法は別途規定する。
*/
DLLBINDFUNC_(HBITMAP_XD, MPCCreateSignatureIcon)(MPCSession*session, MP_Integer type);
/*@}*/


/*!
@defgroup mpc_pd_function_create_canvas [MPC_PD]キャンバスオブジェクトの生成と破棄の関数

キャンバスをDestroyする時は、MPF_RestoreDCを実行しHDCを生成時の状態に復元する。
（但しRawCanvasは除く）

キャンバスは生成時に渡されたHDCを解放しない。

利用者は、キャンバスをDestroyしてから、必要に応じてHDCを解放する。
*/
/*@{*/

/*!
@brief 印刷描画用のキャンバスを作成する。

キャンバス生成時には、HDCの状態を保存（MPF_SaveDC)し、必要な初期設定を行う。
キャンバスを生成してから破棄するまでの間、原則として利用者がDCの状態を直接変更してはならない。

特に、WindowExt, ViewportExt, MapModeを変更した場合、その後クラッシュする場合がある。
MPF_SaveDCを行う場合、次のキャンバス操作を行う前にMPF_RestoreDCを行わなければならない。
SelectObjectを行う場合、次のキャンバス操作を行う前にSelectを解除しなければならない。

@param session		セッションオブジェクトのアドレス
@param hDC			プリンタのDC
@param printerdpi	プリンタの解像度（単位　dpi）
@param paperdim		用紙寸法（メディア座標系）
@param phres		結果コードアドレス

@return MP_Canvas*
生成に成功したら、キャンバスオブジェクトのアドレスを返す
失敗したらNULLを返す。この時phresがNULLでなければエラーコードをセットする。
*/
DLLBINDFUNC_(MP_Canvas*, MPCreatePRTCanvas)(MPCSession* session, HDC_XD hDC, MP_Integer printerdpi, MP_Dim paperdim, HRESULT* phres);

/*!
@brief 印刷描画用のキャンバスを作成する。

解像度の指定を除いてMPCreatePRTCanvasと同じ。
この関数で生成された印刷用キャンバスは解像度を小数で保持し動作する。

@param fPrintDPI	小数指定したプリンタの解像度（単位　dpi）
*/
DLLBINDFUNC_(MP_Canvas*, MPCreatePRTCanvasFloatDPI)(MPCSession* session, HDC_XD hDC, float fPrintDPI, MP_Dim paperdim, HRESULT* phres);

/*!
@brief 画面描画用のキャンバスを作成する。

注意：
CRTキャンバスとPRTキャンバスに機能的な違いはない。
解像度の初期値が75dpi固定な点を除き、MPCreatePRTCanvasと同じ仕様である。

@param session		セッションオブジェクトのアドレス
@param hDC					ウインドウのDC
@param phres			結果コードアドレス
@return （MPCreatePRTCanvas参照）
*/
DLLBINDFUNC_(MP_Canvas*, MPCreateCRTCanvas)(MPCSession* session, HDC_XD hDC, HRESULT* phres = NULL);

/*!
@brief 任意描画用のキャンバスを作成する。

MPCreateRawCanvasは生成時にDCの初期化（座標系の初期化や、MPF_SaveDC等）を行わない。
主にMetafileDCに利用する。

@param session		セッションオブジェクトのアドレス
@param hDC					任意のDC
@param dpi			解像度（単位　dpi）
@param dim				描画範囲（メディア座標系）
@param phres			結果コードアドレス

@return （MPCreatePRTCanvas参照）
*/
DLLBINDFUNC_(MP_Canvas*, MPCreateRAWCanvas)(MPCSession* session, HDC_XD hDC, MP_Integer dpi, MP_Dim dim, HRESULT* phres = NULL);
/*@}*/

// 09.07.14 - M.Chikyu UNICODE対応
//#ifdef _M3CORE_MP_

/*!
@brief device contextを作成する。
<pre>
MPCreateRAWCanvasやMPCreatePRTCanvasに与えるためのDCを作成する。
同時にoffscreen bitmapも作成される。DCに対する描画がビットマップに反映される。
</pre>
@param[in] session		セッションオブジェクトのアドレス
@param[in] dim			作成するビットマップの寸法(0.01mm)
@param[in] dpi			作成するビットマップの解像度(DPI)
@param[in] percent		表示倍率
@param[out] phres		結果コードを格納するバッファのアドレス

@return HDC
*/
DLLBINDFUNC_(HDC_XD, MPCCreateDC)(MPCSession* session, MP_Dim dim, MP_Integer dpi, MP_Integer percent, HRESULT* phres = NULL);

/*!
@brief device contextを作成する。
<pre>
解像度を浮動小数で与える。offscreen bitmapのサイズ計算精度が異なることを除いてMPCCreateDC()と同じ。
</pre>
@param[in] session		セッションオブジェクトのアドレス
@param[in] dim			作成するオフスクリーンの寸法(0.01mm)
@param[in] fdpi			作成するビットマップの解像度(DPI)をfloatで与える
@param[in] percent		表示倍率
@param[out] phres		結果コードを格納するバッファのアドレス

@return HDC
*/

DLLBINDFUNC_(HDC_XD, MPCCreateDCFloatDPI)(MPCSession* session, MP_Dim dim, float fdpi, MP_Integer percent, HRESULT* phres = NULL);

/*!
@brief device contextを作成する。
<pre>
offscreen sizeをpixel数で与える。他はMPCCreateDC()と同じ。
Windows Mobile Viewerでの固定オフスクリーン制御を想定。
</pre>
@param[in] session MPCSessionオブジェクト
@param[in] width 作成するオフスクリーンの幅(Pixel)
@param[in] height 作成するオフスクリーンの高さ(Pixel)
@param[in] dpi 作成するオフスクリーンの解像度
@param[out] phres 結果コードを格納する領域

@return HDC 作成したDCオブジェクトのハンドル
*/
DLLBINDFUNC_(HDC_XD, MPCCreateDCPixel)(MPCSession* session, MP_Integer width, MP_Integer height, MP_Integer dpi, HRESULT* phres = NULL);

/*!
@brief device contextを破棄する。

@param[in] hdc MPCCreateDC()またはMPCCreateDCFloatDPI()を呼び出して作成したHDC

@return HRESULT 		結果コード
*/

DLLBINDFUNC_(HRESULT, MPCDeleteDC)(HDC_XD hdc);

/*!
@brief DCからビットマップのメモリを取得する。
<pre>
DIBへのポインタが*ppbiに格納される。
transfer=falseの場合は、MPCDeleteDC()を呼び出すとビットマップのメモリが解放される。
transfer=trueの場合は、ビットマップメモリの所有権が呼び出し元に移り、呼び出し元は
MPCGlobalFree()を使って*ppbiを解放しなければならない。所有権が移った後はDCに対して
描画することはできない。
*ppbitsはDIBのビットデータの先頭を指すポインタであり、解放はしなくてよい。
</pre>
@param[in] hdc			MPCCreateDC()またはMPCCreateDCFloatDPI()を呼び出して作成したHDC
@param[out] ppbi		BITMAPINFOへのポインタを受け取るバッファのアドレス
@param[out] ppbits 		ビットデータへのポインタを受け取るバッファのアドレス
@param[in] transfer		ビットマップメモリの所有権を呼び出し元に移すかどうか

@return HRESULT			結果コード
*/
DLLBINDFUNC_(HRESULT, MPCGetDIB)(HDC_XD hdc, BITMAPINFO** ppbi, void** ppbits, bool transfer);

//#endif	// _M3CORE_MP_


#if defined _PF_WIN32_ || defined _PF_WINCE_
/*!
@brief オフスクリーンのメモリDCを取得する

@param[in] hdc HDC_XD DCオブジェクトのハンドル

@return HDC ビットマップのメモリDC。エラーのときはNULLを返す。
*/
DLLBINDFUNC_(HDC, MPCGetMemoryDC)(HDC_XD hdc);
#endif

/*!
@struct MP_Canvas
@brief MP_Canvasインターフェイス

アプリケーションが文書内容を表示・印刷・イメージ変換する時に、
Windows APIのDC（デバイスコンテクスト）を内包して一時的に作成するオブジェクト。

@par Destroy()
キャンバスをDestroyする時は、MPF_RestoreDCを実行しHDCを生成時の状態に復元する。
（但しRawCanvasは除く）
キャンバスは生成時に渡されたHDCを解放しない。
利用者は、キャンバスをDestroyしてから、必要に応じてHDCを解放する。
*/
//! @brief MP_CanvasのインターフェイスID
MPC_EXTERN_GUID(IID_MP_Canvas, 0x1362);

mpinterface MP_Canvas : public MPCInterface
{
/*!
@brief キャンバスがラップしているDCハンドルを返す
@param なし
@return HDC
*/
STDMETHOD_(HDC_XD,GetHDC)() PURE;
/*!
@brief メディア座標系→ウインドウズ論理座標系　の座標変換
@param position		座標（メディア座標系）
@return POINT	座標（ウインドウズ論理座標系）
*/
STDMETHOD_(POINT,GetPOINT)(MP_Pos position) PURE;
/*!
@brief メディア座標系→ウインドウズ論理座標系　の寸法変換
@param dim		寸法（メディア座標系）
@return SIZE			寸法（ウインドウズ論理座標系）
*/
STDMETHOD_(SIZE,GetSIZE)(MP_Dim dim) PURE;
/*!
@brief ウインドウズ論理座標系→メディア座標系　の座標変換
@param point		座標（ウインドウズ論理座標系）
@return MP_Pos		座標（メディア座標系）
*/
STDMETHOD_(MP_Pos,GetPos)(POINT point) PURE;
/*!
@brief ウインドウズ論理座標系→メディア座標系　の寸法変換
@param size	寸法（ウインドウズ論理座標系）
@return MP_Dim		寸法（メディア座標系）
*/
STDMETHOD_(MP_Dim,GetDim)(SIZE size) PURE;
/*!
@brief 原点の移動
@param origin	新しい原点の座標（メディア座標系）
@return HRESULT
*/
STDMETHOD(MoveOrigin)(MP_Pos origin) PURE;
/*!
@brief 座標系や描画状態の保存

WinAPIの　MPF_SaveDC　実行後、キャンバスが保持する　原点　と　表示倍率　を待避する。
@param なし
@return HRESULT
*/
STDMETHOD(SaveTransform)() PURE;
/*!
@brief 座標系や描画状態の復元

WinAPIの　MPF_RestoreDC　実行後、SaveTransformで待避した状態を復元する。
@param なし
@return HRESULT
*/
STDMETHOD(RestoreTransform)() PURE;
/*!
@brief 表示倍率変更
@param xpercent		
@param ypercent
@return HRESULT
*/
STDMETHOD(Magnify)(MP_Integer xpercent, MP_Integer ypercent) PURE;

/*!
@brief 矩形を描画する
@param rect
@return HRESULT
*/
STDMETHOD(Rectangle)(MP_Rect rect) PURE;

/*!
@brief 矩形を描画する
@param left
@param top
@param right
@param bottom
@return HRESULT
*/
STDMETHOD(Rectangle)(long left, long top, long right, long bottom) PURE;

/*!
@brief 現在設定されている表示倍率の取得
@param[out] xpercent
@param[out] ypercent
@return HRESULT
*/
STDMETHOD(GetMagnify)(MP_Integer* xpercent, MP_Integer* ypercent) PURE;

/*!
@brief 矩形のクリップをかける

現在のクリップ領域とのANDとなる
@param rect
@return HRESULT
*/
STDMETHOD(IntersectClipRect)(MP_Rect rect) PURE;

/*!
@brief 表示倍率と解像度の調整（Arashi/Chage PlugIn FAXの微調整用）
@param xpercent X方向表示倍率
@param ypercent Y方向表示倍率
@param xdpi X方向解像度
@param ydpi Y方向解像度
@return HRESULT
*/
STDMETHOD(TuneRawDensity)(MP_Integer xpercent, MP_Integer ypercent, MP_Integer xdpi, MP_Integer ydpi) PURE;

/*!
@brief 特別なプリンタかどうかの情報取得
@param なし
@retval 0 : 下記のいずれにも該当しない。
@retval 1 : このキャンバスが保持するDCは、POSTSCRIPTプリンタへの出力である。
*/
STDMETHOD(GetPrinterType)() PURE;

/*!
@brief 印刷能力関連の情報をセットする。

アプリケーションが各コンテントの描画方式を制御する時に利用する。

例えば、
-# プリンタの能力に応じてコンテントの描画方式を変える場合
-# 印刷ダイアログで指定されたユーザ設定フラグによって描画方式を変える場合<br>
などに利用する事を想定している。

各ビットフラグの意味は、MP_PrinterCapsのマクロ定義を参照
@param pcaps	キャンバスに記憶させるデータ
@return 常にMP_NOERRORを返す。
*/
STDMETHOD(SetPrinterCaps)(MPC_PrinterCaps pcaps) PURE;

/*!
@brief 印刷能力関連の情報取り出し

各ビットフラグの意味は、MP_PrinterCapsのマクロ定義を参照
@param なし
@return MP_PrinterCaps	SetPrinterCaps()でセットし、キャンバスが保持している値を返す
*/
STDMETHOD_(MPC_PrinterCaps, GetPrinterCaps)() PURE;

/*!
@brief このCanvasの描画範囲を返す。

これはコンテントのWMFPDを生成する処理の中で利用する。
MPCreateRAWCanvas()で生成したcanvasの場合、引数dimの値を返す。
その他の方法で生成したcanvasの場合、動作は定義しない。
@param なし
@return MP_Dim	描画範囲
*/
STDMETHOD_(MP_Dim,GetCanvasDim)() PURE;

/*!
@brief ハイコントラスト描画情報をCanvasに設定する

主にアプリケーション側が、ハイコントラスト描画をさせたい場合にセットする
@param pInfo 設定する描画情報
@return HRESULT
*/
STDMETHOD(SetContrastDrawInfo)(MPC_ContrastDrawInfo* pInfo) PURE;

/*!
@brief ハイコントラスト描画情報をCanvasに取得する

主に描画側が、情報を取得し、描画時の振る舞いを変える。
@param pInfo 取得する描画情報
@return HRESULT
*/
STDMETHOD(GetContrastDrawInfo)(MPC_ContrastDrawInfo* pInfo) PURE;
};



/*!
@defgroup mpc_pd_function_create_pd [MPC_PD]PDオブジェクトの生成と破棄の関数

PDオブジェクトの破棄は自身のDestroy()メソッドで解放する。
*/
/*@{*/

/*!
@brief PDをロードする

ストレージオブジェクトstgobjのanameに格納されたPDをロードして、PDメモリオブジェクトを生成する。

注意1）この関数は、自分自身や自身の子オブジェクトの画像を表示する
モデルオブジェクト開発者のために用意されている。

この関数はストレージオブジェクトに保存されているPDをロードする。
編集中の文書など、ストレージオブジェクトのPDが更新されていない状態で
MPCLoadPD を発行すると、最新の画像を得られない場合がある。
またモデルがPDを取り扱う処理に応じてPDが削除され存在しない場合もある。

アプリケーションがPDを取得する場合は、
目的に応じてモデルが提供するインターフェイスを用いる事

注意2）MPCLoadPDに成功したら、PDオブジェクトを破棄するまでは、stgobjを破棄したり、anameの属性を変更してはならない。

@param session		セッションオブジェクトアドレス
@param stgobj		ストレージオブジェクトアドレス
@param aname			PDが格納された属性名
@param phres			結果コードアドレス

@retval MP_PD*
@retval 成功した場合 オブジェクトアドレスを返す。
@retval 失敗した場合 NULLを返す。この時、phresがNULLでなければエラーコードをセットする。
*/
DLLBINDFUNC_(MP_PD*, MPCLoadPD)(MPCSession* session, IStgObject* stgobj, const MP_AName* aname = NULL, HRESULT* phres = NULL);

/*!
@brief EMFハンドルからPDを作成する。

PDの寸法は、HENHMETAFILEのヘッダ情報 ENHMETAHEADER構造体の
rclFrame要素から算出する。
EMF作成者は、メディア座標系の寸法を、rclFrameに設定しなければならない。

@param session		セッションオブジェクトアドレス
@param hemf		EMFハンドル
@param[out] phres 結果コードアドレス
@return
MP_PD*
成功した場合、オブジェクトアドレスを返す。
失敗した場合、リターン値を返す。この時、phresがNULLでなければエラーコードをセットする。
*/
DLLBINDFUNC_(MP_PD*, MPCreateEMFPD)(MPCSession* session, HENHMETAFILE_XD hemf, HRESULT* phres = NULL);

/*!
@brief WMFハンドルからPDを作成する。

PD寸法は、METAFILEPICTの xExt, yExt 要素で指定する。
WMF作成者は、xExt, yExtにメディア座標系の寸法を設定しなければならない。
@param session		セッションオブジェクトアドレス
@param wmf		METAFILEPICT構造体
@param[out] phres 結果コードアドレス
@return （MPCreateEMFPD参照）
*/
DLLBINDFUNC_(MP_PD*, MPCreateWMFPD)(MPCSession* session, METAFILEPICT_XD wmf, HRESULT* phres = NULL);


/*!
@brief DIBファイルからPDを作成する。

mdimは、メディア座標系の寸法を設定しなければならない。

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。

・V1 bitmap の互換性維持仕様
mdim に 0 以下を指定した場合、BITMAPINDOHEADERの情報から
	mdim.cx = biWidth * 100000 / biXPelsPerMeter
	mdim.cy = biHeight * 100000 / biYPelsPerMeter
でメディア座標系寸法を算出する。
これはV1のPDデータと互換性を維持するための移行措置である。
本関数利用者はmdimに正しい寸法値を指定しなければならない。

@param session		セッションオブジェクトアドレス
@param dibfilepath	DIBファイルパス
@param mdim			文書上のPDの寸法（メディア座標系）
@param level		PDが保持する画質指定（劣化なし、ありなど）
@param phres		結果コードアドレス
@return （MPCreateEMFPD参照）
*/
DLLBINDFUNC_(MP_PD*, MPCreateBMPPD)(MPCSession* session, MP_Path* dibfilepath, MP_Dim mdim, MP_Integer level, HRESULT* phres = NULL);
DLLBINDFUNC_(MP_PD*, MPCreateBMPPDW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim mdim, MP_Integer level, HRESULT* phres = NULL);

/*!
@brief JPEGファイルからPD（外部JPEG）を作成する。

この関数で作成したPDに対して、MP_PD::GetPDInfo()を発行した場合、
	compLevel（ビットマップ圧縮率）は、「5:外部JPEG」を返す。

@param session		セッションオブジェクトアドレス
@param jpegfilepath	JPEGファイルパス
@param mdim			文書上の寸法（メディア座標系）
@param phres		結果コードアドレス
@return（MPCreateEMFPD参照）
*/
DLLBINDFUNC_(MP_PD*, MPCreateJPEGPD)(MPCSession* session, MP_Path* jpegfilepath, MP_Dim mdim, HRESULT* phres = NULL);
DLLBINDFUNC_(MP_PD*, MPCreateJPEGPDW)(MPCSession* session, const MP_WPath* jpegfilepath, MP_Dim mdim, HRESULT* phres = NULL);

/*!
@brief メモリ上のDIBからPDを作る

dibinfoでヘッダ＋パレット情報を渡す。
imagedataでdibinfoに対応するイメージデータを渡す

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。

@param session		セッションオブジェクトアドレス
@param dibinfo		イメージヘッダへのアドレス
@param imagedata	イメージデータへのアドレス
@param mdim			文書上の寸法（メディア座標系）
@param level		PDが保持する画質指定（劣化なし、ありなど）
@param phres		結果コードアドレス

@return （MPCreateEMFPD参照）
*/
DLLBINDFUNC_(MP_PD*, MPCreatePDfromMemBitmap)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim mdim, MP_Integer level, HRESULT* phres = NULL);

/*!
@brief pd->CreateIconPD(phres)を実行するマクロ。（Ｖ３結合後、削除予定）
*/
DLLBINDFUNC_(MP_PD*, MPCCreateIconPD)(MPCSession* session, MP_PD* pd, HRESULT* phres = NULL);

/*!
@brief imsファイルからPD(MRC)を作成する。

imsが1層でかつJPEGならば、JPEG-PDを生成する。
PDの文書上の寸法はimsの画素数と解像度から決定する。
背景層をDW標準のJPEG Qualityで生成してあるときのみlevelを6/7/8に
指定してよい。また背景層がALLAのときはlevelを6に指定してよい。

@param session		セッションオブジェクトアドレス
@param pImsFilePath	imsファイルパス
@param dimPD		生成するPDのサイズ
@param level		生成するPDに格納する圧縮レベル
@param phres		結果コードアドレス

@return  （MPCreateEMFPD参照）
*/
DLLBINDFUNC_(MP_PD*, MPCreatePDFromImsFile)(MPCSession* session, MP_Path* pImsFilePath, MP_Dim dimPD, MP_Integer level = 9, HRESULT* phres = NULL);
DLLBINDFUNC_(MP_PD*, MPCreatePDFromImsFileW)(MPCSession* session, const MP_WPath* pImsFilePath, MP_Dim dimPD, MP_Integer level = 9, HRESULT* phres = NULL);

/*!
@brief メモリ上のIMSデータからPDを生成する
@param session		セッション
@param pImsData		IMSデータのポインタ
@param iImsSize		IMSデータのサイズ
@param mdim			生成するPDの寸法（メディア座標系）
@param level		PDの画質指定
@param[out] phres	結果コードアドレス
@return MP_PD*
*/
DLLBINDFUNC_(MP_PD*, MPCreatePDFromImsMem)(MPCSession* session, BYTE* pImsData, long iImsSize, MP_Dim mdim, MP_Integer level = 9, HRESULT* phres = NULL);
/*@}*/


//! @brief MP_PDのインターフェイスID
MPC_EXTERN_GUID(IID_MP_PD, 0x1366);

/*!
@brief MP_PDインターフェイス
*/
mpinterface MP_PD : public MPCInterface
{
/*!
@brief ストレージにPDを格納する

このPDが保持している画像データをシリアライズし、stgobjのanameという名前の属性としてSetAttributeする。
anameのデフォルト値（NULLを指定した場合）は、"#pd"　にSetAttributeする。
@param stgobj	pdを格納するストレージオブジェクト
@param aname		pdを格納する属性名
@return
@par セキュリティ
文書編集禁止（またはアノテ編集禁止）でstgobjに属性を設定できない場合、MP_E_ACCESSDENIEDエラーになる。<br>
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
Save時点で、内部で保持している stgobj のアクセス権をチェックする。<br>
もし stgobjが転記禁止の場合、他のstgobj へのSaveは、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(Save)(IStgObject* stgobj, const MP_AName* aname = NULL) PURE;

/*!
@brief 指定した角度の回転が可能かどうかを問い合わせる。
実際の回転は行わない。
@param degree	右回りの回転角 90, 180, 270 のいずれか
@retval MP_S_OK		回転可能
@retval MP_S_FALSE	回転不可
@note CanRotateのリターン値は回転を保証するものではない。
*/
STDMETHOD(CanRotate)(MP_Integer degree) PURE;

/*!
@brief 指定した角度の回転を行う。
@param degree	右回りの回転角 90, 180, 270 のいずれか
@return	HRESULT
*/
STDMETHOD(Rotate)(MP_Integer degree) PURE;

/*!
@brief アイコン寸法のPDを作成する

BodyContent専用関数である。
引数pd から、アイコン寸法のPDを作成する。

BodyContentは、性能向上のためにPDと合わせて縮小画像をDWファイルに格納する。
MPCCreateIconPDは、BodyContentが#iconpdとして保存する縮小画像のPDを作る。

@param[out] phres			結果コードアドレス
@return MP_PD*
成功した場合、オブジェクトアドレスを返す。
失敗した場合、リターン値を返す。この時、phresがNULLでなければエラーコードをセットする。

@par セキュリティ
サムネイルは転記権で保護する対象にしないので、転記禁止でもCreateIconPDを実行できる。
*/
STDMETHOD_(MP_PD*, CreateIconPD)(HRESULT* phres) PURE;

/*!
@brief PDオブジェクト内部でキャッシュしているHBITMAP等のメモリ資源を解放する。

メモリ不足時と、画面の色数変更時を想定する。

特に画面の色数が変わった場合、この関数を呼び出さなければならない。
@param[out] phres	結果コードへのアドレス
@return
*/
STDMETHOD_(void, DeletePDCash)(HRESULT* phres) PURE;

/*!
@brief PDに関する情報を返す

depthは、orgがビットマップ系データの場合に限り有効である。
compLevelとmdimは、orgに関わらず有効である。

- EMFの場合、MPCreateWMFPD()で指定したHENHMETAFILEから
MPF_GetEnhMetaFileHeader()で取得したENHMETAHEADERデータのrclFrame要素で算出する。

- WMFの場合、MPCreateWMFPD()で指定したMETAFILEPICTのxExt, yExtの値である。

- ビットマップ系PDの場合、MPCreateBMPPD()、MPCreateJPEGPD、MPCreatePDfromMemBitmapで
指定した引数mdimを返す。

@param[out] org			オリジナルデータの種別　11:WMF, 12:EMF, 21:DIB, 22:JPEG
@param[out] compLevel	ビットマップ圧縮率　1:劣化無圧縮、2:劣化有（高画質）、3:劣化有（標準）、4:劣化有（高圧縮）、5:外部JPEG
@param[out] depth		ビットマップ色数を表すビット数（1, 4, 8, 24)
@param[out] mdim			PD内部で保持している描画寸法（メディア座標系）
@return HRESULT
*/
STDMETHOD(GetPDInfo)(MP_Integer* org, MP_Integer* compLevel, MP_Integer* depth, MP_Dim* mdim = NULL) PURE;

/*!
@brief イメージ変換出力(メモリ)

このPDの画像をDIBに変換して、HDIBに出力する。

出力されるDIBは、90度単位の回転角を反映したものであり、
PDの種類によって以下のように異なる。
- OKDPDの場合は、PD作成元のビットマップと同じものが出力される。
  元が解像度0なら、DIBの解像度も0となる。
- MHPDの場合は、必ず黒=1, 白=0 のパレットが出力される。biSizeImage には必ず正しい値が格納される。
  元が解像度0なら、DIBの解像度も0となる。
- MMRPDの場合は、パレットはPD作成元のビットマップと同じものが出力される。biSizeImage には必ず正しい値が格納される。
  TIFF-MMR直接取り込みされていた場合は、パレットは黒=1, 白=0 に固定、解像度は元のTIFFと同じものが出力される。
  元が解像度0なら、DIBの解像度も0となる。
- JpegPDの場合は、PD作成元のビットマップが8bitカラーの場合でもフルカラーで出力される。
  PD作成元のビットマップが8bitグレーの場合は8bitグレースケールで出力される。
  元のイメージのの解像度が0だった場合は、200dpi固定で出力される。
- MetafilePDの場合は、MP_E_NOTIMPL エラーとなる。
なお、出力されるDIBの解像度は、拡縮取り込みされていた場合は、
Deskのステータスで表示される解像度とは異なる。

hDIB == NULLの場合、DIB取得に必要なバイト数（取得できない場合は０）を返す。<br>
hDIB != NULLの場合、GlobalSize(hDIB)バイトのDIB情報セットし、セットしたバイト数を返す。

@param[out] hDIB	作成結果を出力するDIBハンドル
@retval 正数	DIB取得に必要なバイト数、または、セットしたバイト数
@retval 負数はエラー
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
@retval MP_E_INVALIDARG		不正なDIBハンドル（GlobalSize、GlobalLockできない）

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(ConvertToDIBHandle)(HGLOBAL hDIB=NULL) PURE;

/*!
@brief イメージ変換出力(ファイル)

このPDの画像をDIBに変換して、dibfilepathで指定されたファイルに出力する。

出力されるDIBについては ConvertToDIBHandle の説明を参照のこと。

@param[in] dibfilepath 出力パス
@retval MP_NOERROR	成功
@retval 負数はエラー
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
ファイル生成系エラー

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(ConvertToDIBFile)(MP_Path* dibfilepath) PURE;

/*!
@brief このPDの画像に関するBITMAPINFOHEADERを返す

出力される BITMAPINFOHEADER は、
ConvertToDIBHandle で出力されるDIBのヘッダと同じものである。
@param[out] bmiHeader			結果を格納するBITMAPINFOHEADER構造体のアドレス
@retval MP_NOERROR	成功
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
@retval MP_E_INVALIDARG		不正な引数
*/
STDMETHOD(ConvertToDIBHeader)(BITMAPINFOHEADER* bmiHeader) PURE;

/*!
@brief Canvasへ描画する(表示用)

このPDが保持している画像データをcanvasに対して描画する。

描画内容は、画像縮小や減色など、画面への表示に適した状態に加工する。

その他、細線消えや文字消失防止など、表示に適した画質劣化障害の対策を行う。

bPartが0の場合分割描画を、１の場合一括描画を行う。
（詳細は基本設計書本文を参照）
@param canvas
@param bPart
@retrun

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
転記禁止の場合、対象DCがメタファイルやビットマップだと MP_E_ACCESSDENIED エラーになる。<br>
印刷禁止の場合、対象DCがプリンタだと MP_E_ACCESSDENIED エラーになる。
*/
STDMETHOD(OnDraw)(MP_Canvas* canvas, MP_Integer bPart = 0) PURE;

/*!
@brief Canvasへ描画する(印刷用)

このPDが保持している画像データをcanvasに対して描画する。
描画内容は、プリンタへの印刷を想定する。

その他、細線消えや文字消失防止など、印刷に適した画質劣化障害の対策を行う
モノクロプリンタやPOSTSCRIPTプリンタなど印刷特有の障害対策もある。

infoがNULL以外の場合分割描画を、NULLの場合一括描画を行う。
（詳細は基本設計書本文を参照）

@param canvas
@param info
@return

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
転記禁止の場合、対象DCがメタファイルやビットマップだと MP_E_ACCESSDENIED エラーになる。<br>
印刷禁止の場合、対象DCがプリンタだと MP_E_ACCESSDENIED エラーになる。
*/
STDMETHOD(OnPrint)(MP_Canvas* canvas, MPC_AdvCancelInfo* info = NULL) PURE;

// V4追加
/*!
@brief イメージ変換出力(メモリ)
@param hDIB	作成結果を出力するDIBハンドル
@param bRotate	回転角を反映するかどうか(デフォルトはTRUE)
@param info	途中経過表示＆キャンセル用構造体(デフォルトはNULL)

このPDの画像をDIBに変換して、HDIBに出力する。
- hDIB == NULLの場合、DIB取得に必要なバイト数（取得できない場合は０）を返す。
- hDIB != NULLの場合、GlobalSize(hDIB)バイトのDIB情報セットし、セットしたバイト数を返す。

出力されるDIBは、
- bRotate == TRUE ならば90度単位の回転角を反映したもの、
- bRotate == FALSE ならば回転角を反映せずにPDが持っているイメージの向きと同じものである。

処理は中断可能で、内部でDIB変換時のバンド幅単位(64line)で
info->callback に指定されたコールバック関数を呼び出す。

アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを指定すること。

コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。

MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。

引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。

bRotate, info を省略した場合は ConvertToDIBHandle() と同じ動作をする。

@retval 正数(>1) DIB取得に必要なバイト数、または、セットしたバイト数を示す。
@retval MP_S_PROCESS_CANCELED(=1) 途中で中断されたことを示す。
@retval 負数 エラー
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
@retval MP_E_INVALIDARG		不正なDIBハンドル（GlobalSize、GlobalLockできない）

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(ConvertToDIBHandleAdv)(HGLOBAL hDIB = NULL, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@brief イメージ変換出力(ファイル)
@param[in] dibfilepath 出力パス
@param[in] bRotate	回転角を反映するかどうか(デフォルトはTRUE)
@param[in] info	途中経過表示＆キャンセル用構造体(デフォルトはNULL)

このPDの画像をDIBに変換して、dibfilepathで指定されたファイルに出力する。

出力されるDIBは、
- bRotate == TRUE ならば90度単位の回転角を反映したもの、
- bRotate == FALSE ならば回転角を反映せずにPDが持っているイメージの向きと同じものである。

処理は中断可能で、内部でDIB変換時のバンド幅単位(64line)で
info->callback に指定されたコールバック関数を呼び出す。

アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを指定すること。

コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。

MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。

引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。

bRotate, info を省略した場合は ConvertToDIBFile() と同じ動作をする。

@retval MP_NOERROR(=0) 成功を示す。
@retval MP_S_PROCESS_CANCELED(=1) 途中で中断されたことを示す。
@retval 負数 エラー
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
ファイル生成系エラー

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(ConvertToDIBFileAdv)(MP_Path* dibfilepath, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@brief このPDの画像に関するBITMAPINFOHEADERを返す

出力されるBITMAPINFOHEADERは、
- bRotate == TRUE ならば90度単位の回転角を反映したもの、
- bRotate == FALSE ならば回転角を反映せずにPDが持っているイメージの向きと同じものである。

bRotate を省略した場合は ConvertToDIBHeader() と同じ動作をする。
@param[out] bmiHeader			結果を格納するBITMAPINFOHEADER領域の先頭アドレスを指定する
@param[in] bRotate				回転角を反映するかどうか(デフォルトはTRUE)
@retval MP_NOERROR	成功
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
@retval MP_E_INVALIDARG		不正な引数
*/
STDMETHOD(ConvertToDIBHeaderAdv)(BITMAPINFOHEADER* bmiHeader, BOOL_XD bRotate = TRUE) PURE;

/*!
@brief PDの圧縮データをファイルに出力する

@param[in] dstPath			出力先のパス。既にファイルがあっても上書きする。
@param[out] compDataType	出力するイメージデータのタイプが格納される

dstPath にPD内で保持している圧縮イメージを書き出す。

dstPath == NULL で compDataType が指定されている場合は、
compDataType に MPC_COMPDATATYPE_* で定義されている圧縮フォーマットを返す。

利用者はまず dstPath = NULL としてこの関数を呼び出し、
圧縮フォーマットを見て拡張子を決めること。

dstPath == NULL かつ compDataType == NULL の場合はエラーとなる。

dstPath を指定した場合は、compDataType は NULL でも構わない。

出力される圧縮イメージは、PDの種類によって以下のようになる。
- JpegPDの場合は、Jpegが出力される。
  元が解像度0だった場合は200dpi固定のJpegが出力される。
- MHPD, MMRPDの場合は、TIFFが出力される。
  出力されるTIFFのフォーマットは以下の通りである。
  - TIFFファイルヘッダ
	- バイトオーダはII(リトルインディアン)
  - IFDエントリ
	- ImageWidth		元イメージの横幅
	- ImageLength		元イメージの高さ
	- BitsPerSample		1(モノクロ)
	- Compression		MMRの場合は4, MHの場合は3
	- PhotometricInterpretation	0(白=0, 黒=1)
	- StripOffsets		圧縮イメージへのオフセット
	- RowsPerStrip		ImageLengthと同じ(1ストリップ)
	- StripByteCounts	圧縮イメージのサイズ
	- ResolutionUnit	2(dpi単位)
	- XResolution		横方向解像度(dpi)
	- YResolution		縦方向解像度(dpi)
  元が解像度0なら、出力されるTIFFの解像度も0となる。
  これら以外のタグは付けない。
- OKDPD, metafilePD の場合は、MP_E_NOTIMPL エラーとなる。

@retval MP_NOERROR	成功
@retval MP_E_NOTIMPL		このPDは取り出せる圧縮イメージを持っていない
@retval MP_E_INVALIDARG		不正な引数
@retval MP_E_DISK_FULL		出力先のディスク容量不足
@retval その他				状況に応じて MP_E_* のエラーを返す

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(GetCompDataToFile)(MP_Path* dstPath, MP_Integer* compDataType = NULL) PURE;

/*!
@brief PDの圧縮データをメモリ上に出力する

hData にPD内で保持している圧縮イメージを格納する。

hData == NULL の場合は、アロケートに必要なメモリサイズを返す。

compDataType が指定されている場合は、
compDataType に MPC_COMPDATATYPE_* で定義されている圧縮フォーマットを返す。

hData != NULL の場合は、hData に圧縮イメージを格納する。

出力される圧縮イメージについては GetCompDataToFile を参照すること。

@param hData					圧縮イメージを格納する先
@param compDataType	出力するイメージデータのタイプが格納される
@retval MP_NOERROR			成功
@retval MP_E_NOTIMPL		このPDは取り出せる圧縮イメージを持っていない
@retval MP_E_INVALIDARG		不正な引数
@retval その他				状況に応じて MP_E_* のエラーを返す

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(GetCompDataToHandle)(HGLOBAL hData = NULL, MP_Integer* compDataType = NULL) PURE;

/*!
@brief メタファイルPD中の画像を圧縮する

@param level	ビットマップ圧縮率  2:高画質、3:標準、4:高圧縮

PDが保持するイメージデータを圧縮する。メタファイルPDのみ機能する。

GetPDInfoで取得できる圧縮率の値が更新される。

現在より高圧縮にならない場合は圧縮しない。

@retval MP_NOERROR			成功
@retval MP_E_NOTIMPL		このPDは機能しない
@retval MP_E_INVALIDARG		不正な引数
@retval その他				状況に応じて MP_E_* のエラーを返す
*/
STDMETHOD(CompressImage)(MP_Integer level) PURE;

/*!
@brief PDのカラー判定を行う

@param bCheck	FALSEの場合は、ヘテロならサムネイル作成時の判定結果を、
				それ以外なら50dpi相当のビットマップに描画して判定した結果を返す。<br>
				TRUEの場合は、PDの中身を調べた結果を返す。

このPDの画像に対するカラーモード判定結果を返す

bCheck=FALSEの場合は、HeteroBodyContentがMP_PD::CreateIconPD()を呼び出した後や、
アノテーションの色を判定したいときにこのメソッドを呼び出すことを想定している。

bCheck=TRUEの場合は、BasicPageがicon pdやheader contentのpdに対して
呼び出すことを想定している。

それら以外でTRUEで呼び出すと、現在はMP_E_NOTIMPLが返る。

MP_PDのインターフェイスとして公開しているが、特殊な呼び出しを想定しているので、
コアモジュール担当者以外はこのメソッドを呼んではいけない。

@retval 負数						エラー
@retval MP_COLORTYPE_MONO(=0)		モノクロ(グレー含む)
@retval MP_COLORTYPE_COLOR(=1)	カラー
*/
STDMETHOD_(MP_Integer, GetColorType)(BOOL_XD bCheck = TRUE) PURE;

// V5で追加
/*!
@brief メタファイルPD中の画像を低解像度化する

@param level
@param spcified_resolution
@retval MP_NOERROR 成功
@retval 負数 エラー
*/
STDMETHOD(ThinImage)(MP_Integer level, MP_Integer spcified_resolution = 0) PURE;

/*!
@brief メモリ上のPDを回転する
<pre>
PDオブジェクトのメモリ上の状態に対して回転を加える。
PDから画像を取り出し処理で、ページ上の回転状態を反映して、
画像の回転を伴って取り出されてしまうのを回避する目的などで使用する。
(この目的の場合、ヘテロなどから取り出したPDオブジェクトに対して
このメソッドでページ上の回転角をキャンセルするような角度を指定する)

あくまでもメモリ上のPDに対する操作のためのメソッドであり、
この操作を行ったPDをヘテロなどにセットしてはならない。

イメージPDのみに実装されている。
</pre>
@param degree	回転する角度(90度ごと)
@retval MP_NOERROR 成功
@retval 負数 エラー (MF-PDに対して呼ぶ場合 MP_E_NOTIMPL)
*/
STDMETHOD(RotateOnMem)(MP_Integer degree) PURE;

// Unicode版
/*!
@brief イメージ変換出力(ファイル) (unicode)

このPDの画像をDIBに変換して、dibfilepathで指定されたファイルに出力する。

出力されるDIBについては ConvertToDIBHandle の説明を参照のこと。

@param[in] dibfilepath 出力パス
@retval MP_NOERROR	成功
@retval 負数はエラー
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
ファイル生成系エラー

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(ConvertToDIBFileW)(const MP_WPath* dibfilepath) PURE;

/*!
@brief イメージ変換出力(ファイル) (unicode)
@param[in] dibfilepath 出力パス
@param[in] bRotate	回転角を反映するかどうか(デフォルトはTRUE)
@param[in] info	途中経過表示＆キャンセル用構造体(デフォルトはNULL)

このPDの画像をDIBに変換して、dibfilepathで指定されたファイルに出力する。

出力されるDIBは、
- bRotate == TRUE ならば90度単位の回転角を反映したもの、
- bRotate == FALSE ならば回転角を反映せずにPDが持っているイメージの向きと同じものである。

処理は中断可能で、内部でDIB変換時のバンド幅単位(64line)で
info->callback に指定されたコールバック関数を呼び出す。

アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを指定すること。

コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。

MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。

引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。

bRotate, info を省略した場合は ConvertToDIBFile() と同じ動作をする。

@retval MP_NOERROR(=0) 成功を示す。
@retval MP_S_PROCESS_CANCELED(=1) 途中で中断されたことを示す。
@retval 負数 エラー
@retval MP_E_NOTIMPL		このPDはDIBに変換できない。（MetafilePD等）
ファイル生成系エラー

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(ConvertToDIBFileAdvW)(const MP_WPath* dibfilepath, BOOL_XD bRotate = TRUE, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@brief PDの圧縮データをファイルに出力する (unicode)

@param[in] dstPath			出力先のパス。既にファイルがあっても上書きする。
@param[out] compDataType	出力するイメージデータのタイプが格納される

dstPath にPD内で保持している圧縮イメージを書き出す。

dstPath == NULL で compDataType が指定されている場合は、
compDataType に MPC_COMPDATATYPE_* で定義されている圧縮フォーマットを返す。

利用者はまず dstPath = NULL としてこの関数を呼び出し、
圧縮フォーマットを見て拡張子を決めること。

dstPath == NULL かつ compDataType == NULL の場合はエラーとなる。

dstPath を指定した場合は、compDataType は NULL でも構わない。

出力される圧縮イメージは、PDの種類によって以下のようになる。
- JpegPDの場合は、Jpegが出力される。
  元が解像度0だった場合は200dpi固定のJpegが出力される。
- MHPD, MMRPDの場合は、TIFFが出力される。
  出力されるTIFFのフォーマットは以下の通りである。
  - TIFFファイルヘッダ
	- バイトオーダはII(リトルインディアン)
  - IFDエントリ
	- ImageWidth		元イメージの横幅
	- ImageLength		元イメージの高さ
	- BitsPerSample		1(モノクロ)
	- Compression		MMRの場合は4, MHの場合は3
	- PhotometricInterpretation	0(白=0, 黒=1)
	- StripOffsets		圧縮イメージへのオフセット
	- RowsPerStrip		ImageLengthと同じ(1ストリップ)
	- StripByteCounts	圧縮イメージのサイズ
	- ResolutionUnit	2(dpi単位)
	- XResolution		横方向解像度(dpi)
	- YResolution		縦方向解像度(dpi)
  元が解像度0なら、出力されるTIFFの解像度も0となる。
  これら以外のタグは付けない。
- OKDPD, metafilePD の場合は、MP_E_NOTIMPL エラーとなる。

@retval MP_NOERROR	成功
@retval MP_E_NOTIMPL		このPDは取り出せる圧縮イメージを持っていない
@retval MP_E_INVALIDARG		不正な引数
@retval MP_E_DISK_FULL		出力先のディスク容量不足
@retval その他				状況に応じて MP_E_* のエラーを返す

@par セキュリティ
MPCLoadPDを使ってファイルからロードしたPDや、すでにMP_PD::Saveを実行したPDは、
実行時に 内部で保持している stgobj のアクセス権をチェックする。<br>
stgobj が転記禁止でビットマップ取出が禁止されている場合、MP_E_ACCESSDENIEDエラーになる。
*/
STDMETHOD(GetCompDataToFileW)(const MP_WPath* dstPath, MP_Integer* compDataType = NULL) PURE;
};

// 圧縮イメージ取り出し時のイメージのタイプ
#define MPC_COMPDATATYPE_JPEG		1
#define MPC_COMPDATATYPE_TIFF_MMR	2
#define MPC_COMPDATATYPE_TIFF_MH	4
#define MPC_COMPDATATYPE_IMS		8

//! @brief MP_JpegPDのインターフェイスID
MPC_EXTERN_GUID(IID_MP_JPEGPD, 0x1377);
/*!
@brief Jpeg直接取り込み時にプロセスモデルで用いるインターフェイス

もともと pd3pub.h に記述されていたものを移した。
*/
mpinterface MP_JpegPD {
/*!
@brief path で指定されたJpegファイルをPDとして取り込む。
@param path	Jpegファイル
@param mdim 生成するPDの寸法
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(Jpegファイルが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromJpegFile)(MP_Path *path, MP_Dim mdim) PURE;
/*!
@brief メモリ上のJpegデータをPDとして取り込む
@param pJpegData Jpegデータのポインタ
@param jpegSize Jpegデータのサイズ
@param mdim 生成するPDの寸法
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(Jpegファイルが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromMemJpeg)(unsigned char* pJpegData, long jpegSize, MP_Dim mdim) PURE;
/*!
@brief path で指定されたIMSファイルをPDとして取り込む。

PDの文書上の寸法はimsの画素数と解像度から決定する。

IMSファイル中のオブジェクトが1つでJPEGである場合にのみ成功する。
@param pszPath	IMSファイルのパス
@param mdim 生成するPDの寸法
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(imsファイルが不正、Jpegデータが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromImsFile)( MP_Path *pszPath, MP_Dim mdim ) PURE;
/*!
@brief path で指定されたIMSファイルをPDとして取り込む。

PDの文書上の寸法はimsの画素数と解像度から決定する。

IMSデータ中のオブジェクトが1つでJPEGである場合にのみ成功する。
@param pCompData  IMSデータの先頭ポインタ
@param compSize  IMSデータのバイト数
@param mdim 生成するPDの寸法
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(imsファイルが不正、Jpegデータが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromImsMem)(unsigned char* pCompData, long compSize, MP_Dim mdim ) PURE;
/*!
@brief path で指定されたJpegファイルをPDとして取り込む。
@param path	Jpegファイル
@param mdim 生成するPDの寸法
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(Jpegファイルが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromJpegFileW)(const MP_WPath *path, MP_Dim mdim) PURE;
/*!
@brief path で指定されたIMSファイルをPDとして取り込む (unicode)

PDの文書上の寸法はimsの画素数と解像度から決定する。

IMSファイル中のオブジェクトが1つでJPEGである場合にのみ成功する。
@param path	IMSファイルのパス
@param mdim 生成するPDの寸法
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(imsファイルが不正、Jpegデータが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromImsFileW)(const MP_WPath *path, MP_Dim mdim) PURE;
};

//! @brief MP_MMRPDのインターフェイスID
MPC_EXTERN_GUID(IID_MP_MMRPD, 0x1379);
/*!
@brief TIFF-MMR直接取り込み時にプロセスモデルで用いるためのインターフェイス
*/
mpinterface MP_MMRPD {
/*!
pCompData で指定されている MMR のデータを、mdim で指定された大きさでPDとして取り込む。

@param pCompData	MMRデータへのポインタ
@param compSize	MMRデータサイズ
@param width		元イメージの横幅
@param height		元イメージの縦幅
@param xppm		元イメージの横方向の解像度(単位はppm)
@param yppm		元イメージの縦方向の解像度(単位はppm)
@param mdim		生成するPDの寸法
@param bCodeCheck	MMRデータをチェックするかどうか

@retval MP_NOERROR 取り込めた
@retval 負の値 取り込めなかった(JpegFileが不正、libJPEGで扱えないものなど)
*/
    STDMETHOD(CreateFromMMRData)(BYTE* pCompData, long compSize, long width, long height, long xppm, long yppm, MP_Dim mdim, BOOL_XD bCodeCheck = TRUE) PURE;
/*!
@brief imsファイルからPDを作成する
@param pszPath	imsファイルのパス
@param mdim		生成するPDの寸法
*/
    STDMETHOD(CreateFromImsFile)( MP_Path *pszPath, MP_Dim mdim ) PURE;
/*!
@brief メモリ上のimsデータからPDを作成する
@param pCompData	imsデータへのポインタ
@param compSize	imsデータサイズ
@param mdim		生成するPDの寸法
*/
    STDMETHOD(CreateFromImsMem)( unsigned char* pCompData, long compSize, MP_Dim mdim ) PURE;
/*!
@brief imsファイルからPDを作成する (unicode)
@param path	imsファイルのパス
@param mdim		生成するPDの寸法
*/
    STDMETHOD(CreateFromImsFileW)( const MP_WPath *path, MP_Dim mdim ) PURE;
};

//! @brief MP_MrcPDのインターフェイスID
MPC_EXTERN_GUID(IID_MP_MRCPD, 0x1382);
/*!
@brief MRC(imsフォーマット)直接取り込み用のインターフェイス
*/
mpinterface MP_MrcPD {
/*!
@brief imsフォーマットのファイルから直接取り込みによりPDを生成する。

pszPath で指定されたimsフォーマットのファイルから直接取り込みによりPDを生成する。

PDの文書上の寸法はimsの画素数と解像度から決定する。

MPPMDIBFileToIMSFile()などを用いて画質を指定して作成したimsデータの場合、
生成時に指定した画質レベル(6:MRC高画質/7:MRC標準/8:MRC高圧縮)をlevelに指定する。

@param pszPath	imsフォーマットのファイル
@param level  PDに付ける画質レベル
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
    STDMETHOD(CreateFromImsFile)( MP_Path *pszPath, MP_Dim mdim, MP_Integer level = 9 ) PURE;
/*!
@brief imsフォーマットのメモリから直接取り込みによりPDを生成する。

pImsData で指定されたimsフォーマットのメモリから直接取り込みによりPDを生成する。

PDの文書上の寸法はimsの画素数と解像度から決定する。

MPPMDIBMemToIMSMem()などを用いて画質を指定して作成したimsデータの場合、
生成時に指定した画質レベル(6:MRC高画質/7:MRC標準/8:MRC高圧縮)をlevelに指定する。

@param pImsData  imsデータの先頭ポインタ
@param iImsSize  imsデータのバイト数
@param level  PDに付ける画質レベル
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
    STDMETHOD(CreateFromImsMem)( unsigned char* pImsData, long iImsSize, MP_Dim mdim, MP_Integer level = 9 ) PURE;
/*!
@brief imsフォーマットのファイルから直接取り込みによりPDを生成する (unicode)

path で指定されたimsフォーマットのファイルから直接取り込みによりPDを生成する。

PDの文書上の寸法はimsの画素数と解像度から決定する。

MPPMDIBFileToIMSFile()などを用いて画質を指定して作成したimsデータの場合、
生成時に指定した画質レベル(6:MRC高画質/7:MRC標準/8:MRC高圧縮)をlevelに指定する。

@param path	imsフォーマットのファイル
@param level  PDに付ける画質レベル
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
    STDMETHOD(CreateFromImsFileW)( const MP_WPath *path, MP_Dim mdim, MP_Integer level = 9 ) PURE;
};


/*
セッションオブジェクトのPD関連インターフェイス
*/

/*!
@struct MP_BitmapOperations
@brief BITMAP操作ユーティリティ　インターフェイス

アプリケーションが文書内容を表示・印刷・イメージ変換する時に、
Windows APIのDC（デバイスコンテクスト）を内包して一時的に作成するオブジェクト。

@par 注意
大規模イメージ対策のため、以下の仕様は流動的である。
現時点で詳細な仕様は開示しない。（DWDeskと個別に仕様調整予定。）
*/
//! @brief MP_BitmapOperationsのインターフェイスID
MPC_EXTERN_GUID(IID_BitmapOperations, 0x1318);

/*!
@brief MPCShrinkHDIBの引数に使用する、ビットマップ拡縮率を指定するためのデータ。
*/
struct MP_Rate {
	MP_Integer	inX;
	MP_Integer	inY;
	MP_Integer	outX;
	MP_Integer	outY;
};

mpinterface MP_BitmapOperations
{
/*!
@brief HDIBをHBITMAPとHPALETTEに変換する
@param[in] session	セッション
@param[in] hDIB		入力のDIBのメモリ
@param[out] phPal	出力パレットのハンドルを受け取るアドレス
@return HBITMAP		出力ビットマップのハンドル
*/
STDMETHOD_(HBITMAP_XD, MPCHDIBtoHBITMAP)(MPCSession* session, HGLOBAL hDIB, HPALETTE* phPal) PURE;

/*!
@brief HBITMAPとHPALETTEをHDIBに変換する。

BITMAPINFOHEADERの　XPPM, YPPMは、dimに基づいて計算しセットする。
dim.cx が 0 以下の場合は XPPM は 0、dim.cy が 0 以下の場合は YPPM は 0 となる。
@param[in] session	セッション
@param[in] hBmp		入力ビットマップ
@param[in] hPal		入力パレット
@param[in] dim		メディア座標系の画像サイズ(解像度情報に使用)
@param[out] phres	結果コードのアドレス
@return HGLOBAL		出力DIBのメモリハンドル
*/
STDMETHOD_(HGLOBAL, MPCHBITMAPtoHDIB)(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, HRESULT* phres) PURE;

/*!
@brief HBITMAPとHPALETTEからDIBを作成して、ファイルに保存する。

BITMAPINFOHEADERの　XPPM, YPPMは、dimに基づいて計算しセットする。
dim.cx が 0 以下の場合は XPPM は 0、dim.cy が 0 以下の場合は YPPM は 0 となる。
@param[in] session	セッション
@param[in] hBmp		入力ビットマップ
@param[in] hPal		入力パレット
@param[in] dim		メディア座標系の画像サイズ(解像度情報に使用)
@param[in] dstPath	出力BMPファイルのパス
@return HRESULT		結果コード
*/
STDMETHOD(MPCHBITMAPtoDIBFile)(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, const char* dstPath) PURE;

/*!
@brief HDIBをファイルに保存する。

解像度情報は、dim.cx, dim.cy が 0 以下の場合は、
BITMAPINFOHEADER にもともとセットされている XPPM, YPPM に従う。
@param[in] session	セッション
@param[in] hDIB		入力DIBのハンドル
@param[in] dim		メディア座標系の画像サイズ(解像度情報に使用)
@param[in] dstPath	出力BMPファイルのパス
@return HRESULT		結果コード
*/
STDMETHOD(MPCHDIBtoDIBFile)(MPCSession* session, HGLOBAL hDIB, MP_Dim dim, const MP_Path* dstPath) PURE;

/*!
@brief DIBファイルをHDIBにロードする。
@param[in] session	セッション
@param[in] srcPath	入力BMPファイルのパス
@param[in] dim		メディア座標系の画像サイズ(解像度情報に使用)
@return HGLOBAL		出力DIBのメモリハンドル
*/
STDMETHOD_(HGLOBAL, MPCDIBFiletoHDIB)(MPCSession* session, const MP_Path* srcPath, MP_Dim dim) PURE;

/*!
@brief HDIBで渡されたビットマップを画像縮小し、HDIBにして返す。
@param[in] session	セッション
@param[in] hDIB		入力DIBのメモリハンドル
@param[in] rate		MP_Rate 縮小する割合
@return HGLOBAL		出力DIBのメモリハンドル
*/
STDMETHOD_(HGLOBAL, MPCShrinkHDIB)(MPCSession* session, HGLOBAL hDIB, MP_Rate rate) PURE;

// V4追加
/*!
@brief BMPファイルのノイズ除去を行う
<pre>
dibPathで渡されたビットマップファイルを指定レベルでごみ取りする。
現在はモノクロ2値ビットマップのみごみ取り可能である。
その他のビットマップの場合はエラーを返す。
level には1〜3を指定でき、数字が大きいほど除去作用が大きい
処理は中断可能で、約0.5秒間隔で MPCNoiseReduceDIBFile() 内部の
info->callback に指定されたコールバック関数を呼び出す。
アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを指定すること。
コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。
MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。
引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。
☆注意☆
この関数は dibPath を直接ごみ取りするので、
PDから取り出した一時的なビットマップファイルにのみ適用すること。
中断された場合は、dibPath のビットマップファイルは途中までごみ取りされた状態になる。
</pre>
@param[in] session	セッション
@param[in] dibPath	入出力ファイルのパス
@param[in] level	ノイズ除去の強さ (1=弱..3=強)
@param[in] info		コールバック情報
@retval HRESULTで返す。
@retval MP_NOERROR(=0) ごみ取りが正常に完了したことを示す。
@retval MP_S_PROCESS_CANCELED(=1) 途中で中断されたことを示す。
@retval 負の値 mpc_api.hで定義されているエラーを返す。
*/
STDMETHOD_(HRESULT, MPCNoiseReduceDIBFile)(MPCSession* session, const MP_Path* dibPath, MP_Integer level, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@brief DIBのノイズ除去を行う
<pre>
hDIBで渡されたビットマップを指定レベルでごみ取りする。
その他の仕様は MPCNoiseReduceDIBFile() と同じである。
☆注意☆
この関数は hDIB を直接ごみ取りするので、
PDから取り出した一時的な hDIB にのみ適用すること。
中断された場合は、hDIB は途中までごみ取りされた状態になる。
</pre>
@param[in] session	セッション
@param[in,out] hDIB	入出力DIBのメモリハンドル
@param[in] level	ノイズ除去の強さ (1=弱..3=強)
@param[in] info		コールバック情報

@return MPCNoiseReduceDIBFile() を参照。
*/
STDMETHOD_(HRESULT, MPCNoiseReduceHDIB)(MPCSession* session, HGLOBAL hDIB, MP_Integer level, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@brief DIBのカラーモードを判定する。

ビット数に応じて次のような処理を行う。
- 1bit:  パレットの内容を調べる
- 4,8bit:パレットとビットデータの内容を調べる
- 24bit: ビットデータの内容を調べる

@param[in] session	セッション
@param[in] pbi		BITMAPINFO構造体のアドレス
@param[in] pbits	ビットデータのアドレス

@retval 負数					エラー
@retval MP_COLORTYPE_MONO(=0)	モノクロ(グレー含む)
@retval MP_COLORTYPE_COLOR(=1)	カラー
*/
STDMETHOD_(MP_Integer, MPCCheckDIBColorType)(MPCSession *session, BITMAPINFO *pbi, BYTE *pbits) PURE;

/*!
@brief HDCからHDCへ描画する
<pre>
転送元デバイスコンテキストに選択されたビットマップを転送先デバイスコンテキストに描画する。
コアのビットマップ縮小機能で縮小・減色したビットマップを描画する。
bColorReductionがTRUEである場合、コアパレットを使った256色のビットマップを描画する。
bColorReductionがFALSEである場合、ビットマップを減色せずに描画する。
hdcSrcにはビットマップが選択されていること。
hdcDestにはコアパレットが選択されていること。
</pre>
@param session			セッション
@param hdcDest			転送先デバイスコンテキスト
@param xDest			転送先矩形のX座標
@param yDest			転送先矩形のY座標
@param cxDest			転送先矩形の幅
@param cyDest			転送先矩形の高さ
@param hdcSrc			転送元デバイスコンテキスト
@param xSrc				転送元矩形のX座標
@param ySrc				転送元矩形のY座標
@param cxSrc			転送元矩形の幅
@param cySrc			転送元矩形の高さ
@param dwROP			ROPコード
@param bColorReduction	減色フラグ

@retval MP_NOERROR			成功
@retval MP_E_INVALIDARG		不正な引数
@retval MP_E_OUTOFMEMORY	メモリ不足
*/
STDMETHOD(MPCStretchBlt)(MPCSession *session, HDC_XD hdcDest, int xDest, int yDest, int cxDest, int cyDest, HDC_XD hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, DWORD dwROP, BOOL_XD bColorReduction) PURE;

STDMETHOD_(HBITMAP_XD, MPCHDIBtoHBITMAP4)(MPCSession* session, HGLOBAL hDIB, HPALETTE* phPal, BOOL_XD bBackGround) PURE;

// Unicode版
/*!
@brief HBITMAPとHPALETTEからDIBを作成して、ファイルに保存する (unicode)

BITMAPINFOHEADERの　XPPM, YPPMは、dimに基づいて計算しセットする。
dim.cx が 0 以下の場合は XPPM は 0、dim.cy が 0 以下の場合は YPPM は 0 となる。
@param[in] session	セッション
@param[in] hBmp		入力ビットマップ
@param[in] hPal		入力パレット
@param[in] dim		メディア座標系の画像サイズ(解像度情報に使用)
@param[in] dstPath	出力BMPファイルのパス
@return HRESULT		結果コード
*/
STDMETHOD(MPCHBITMAPtoDIBFileW)(MPCSession* session, HBITMAP_XD hBmp, HPALETTE hPal, MP_Dim dim, const MP_WPath* dstPath) PURE;

/*!
@brief BMPファイルのノイズ除去を行う (unicode)
<pre>
dibPathで渡されたビットマップファイルを指定レベルでごみ取りする。
現在はモノクロ2値ビットマップのみごみ取り可能である。
その他のビットマップの場合はエラーを返す。
level には1〜3を指定でき、数字が大きいほど除去作用が大きい
処理は中断可能で、約0.5秒間隔で MPCNoiseReduceDIBFile() 内部の
info->callback に指定されたコールバック関数を呼び出す。
アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを指定すること。
コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。
MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。
引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。
☆注意☆
この関数は dibPath を直接ごみ取りするので、
PDから取り出した一時的なビットマップファイルにのみ適用すること。
中断された場合は、dibPath のビットマップファイルは途中までごみ取りされた状態になる。
</pre>
@param[in] session	セッション
@param[in] dibPath	入出力ファイルのパス
@param[in] level	ノイズ除去の強さ (1=弱..3=強)
@param[in] info		コールバック情報
@retval HRESULTで返す。
@retval MP_NOERROR(=0) ごみ取りが正常に完了したことを示す。
@retval MP_S_PROCESS_CANCELED(=1) 途中で中断されたことを示す。
@retval 負の値 mpc_api.hで定義されているエラーを返す。
*/
STDMETHOD_(HRESULT, MPCNoiseReduceDIBFileW)(MPCSession* session, const MP_WPath* dibPath, MP_Integer level, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@brief DIBをJPEGに変換する
@param[in] session    セッション
@param[in] hDIB       DIBのメモリハンドル
@param[in] level      圧縮率 (2:高圧縮/3:標準/4:高画質)
@param[out] pjpegsize JPEGデータのサイズを格納する整数変数へのポインタ
@param[out] phres     結果コードを格納するHRESULTへのポインタ
@return JPEGデータのメモリハンドル (後でGlobalFreeで解放すること)
*/
STDMETHOD_(HGLOBAL, MPCHDIBtoHJPEG)(MPCSession* session, HGLOBAL hDIB, MP_Integer level, MP_Integer* pjpegsize, HRESULT* phres) PURE;
};

// V4追加
/*!
@struct MP_PDFactory
@brief PD生成 インターフェイス

下位バイナリ互換を保つため(V3までのXDWAPIやCBSモジュールとV4コアの組み合わせでも動作するようにするため)、
V4新規のPD生成インターフェイスを別に宣言する。
同時に、V3までのPD生成インターフェイスもまとめておく。

V4.1でMP_PDFactory2を追加。MP_PDFactoryのすべてのI/Fを含む。
*/

/*!
@defgroup mpc_pd_function_get_factory [MPC_PD]PD生成インターフェイス取得の関数
*/
/*@{*/
//! @brief MP_PDFactoryオブジェクトを取得する
DLLBINDFUNC_(MP_PDFactory*, MPCGetPDFactory)(MPCSession* session);
//! @brief MP_PDFactory2オブジェクトを取得する(V4.1)
DLLBINDFUNC_(MP_PDFactory2*, MPCGetPDFactory2)(MPCSession* session);
//! @brief MP_PDFactory3オブジェクトを取得する(V6.0)
DLLBINDFUNC_(MP_PDFactory3*, MPCGetPDFactory3)(MPCSession* session);
/*@}*/


//! @brief MP_PDFactoryのインターフェイスID
MPC_EXTERN_GUID(IID_PDFactory, 0x1320);
//! @brief MP_PDFactory2のインターフェイスID
MPC_EXTERN_GUID(IID_PDFactory2, 0x1326); // V4.1で追加
//! @brief MP_PDFactory3のインターフェイスID
MPC_EXTERN_GUID(IID_PDFactory3, 0x132F); // V6で追加

mpinterface MP_PDFactory
{
#ifndef SFXVW
/*
(V3と同じ関数名のものは同じ仕様であるので説明は割愛)
*/
/*!
@param level	ビットマップ圧縮率  1:劣化無、2:高画質、3:標準、4:高圧縮
(他はV3のI/Fと同じ仕様であるので略)
*/
STDMETHOD_(MP_PD*, MPCreateWMFPD)(MPCSession* session, METAFILEPICT_XD wmf, MP_Integer level, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreateBMPPD)(MPCSession* session, MP_Path* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreatePDfromMemBitmap)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim dim, MP_Integer level, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCCreateIconPD)(MPCSession* session, MP_PD* pd, HRESULT* phres) PURE;
/*!
@param level	ビットマップ圧縮率  1:劣化無、2:高画質、3:標準、4:高圧縮
(他はV3のI/Fと同じ仕様であるので略)
*/
STDMETHOD_(MP_PD*, MPCreateEMFPD)(MPCSession* session, HENHMETAFILE_XD hemf, MP_Integer level, HRESULT* phres) PURE;
STDMETHOD_(MP_PD*, MPCreateJPEGPD)(MPCSession* session, MP_Path* jpegfilepath, MP_Dim dim, HRESULT* phres) PURE;
// V4追加
/*!
@param session		セッションオブジェクトアドレス
@param dibfilepath	DIBファイルパス
@param dim				文書上の寸法（メディア座標系）
@param level		PDが保持する画質指定（劣化なし、ありなど）
@param phres			結果コードアドレス
@param info	途中結果報告＆キャンセル用

MPCreateBMPPDに途中結果報告＆キャンセル機構を追加したものである。
info == NULL の場合はMPCreateBMPPDとまったく同じ動作をする。
処理は中断可能で、内部で info->callback に指定されたコールバック関数を呼び出す。
アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを返すこと。
コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。
MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。
引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。

@return
処理が中断された場合は MP_S_PROCESS_CANCELED (>0) を返す。
それ以外の場合はMPCreateBMPPDと同じである。*/
STDMETHOD_(MP_PD*, MPCreateBMPPDAdv)(MPCSession* session, MP_Path* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo* info = NULL) PURE;

/*!
@param session	セッションオブジェクトアドレス
@param dibinfo	イメージヘッダへのアドレス
@param imagedata	イメージデータへのアドレス
@param mdim		文書上の寸法（メディア座標系）
@param level	PDが保持する画質指定（劣化なし、ありなど）
@param phres	結果コードアドレス
@param info		途中結果報告＆キャンセル用

MPCreatePDfromMemBitmapに途中結果報告＆キャンセル機構を追加したものである。
info == NULL の場合はMPCreatePDfromMemBitmapとまったく同じ動作をする。
処理は中断可能(MPCreateBMPPDAdv参照)。

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。

@return
処理が中断された場合は MP_S_PROCESS_CANCELED (>0) を返す。
それ以外の場合はMPCreatePDfromMemBitmapと同じである。
*/
STDMETHOD_(MP_PD*, MPCreatePDfromMemBitmapAdv)(MPCSession* session, BITMAPINFO* dibinfo, unsigned char* imagedata, MP_Dim dim, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo* info = NULL) PURE;
/*!
@brief MMRデータからPDを作成する。

mdimは、メディア座標系の寸法を設定しなければならない。
@param session
@param pInfo				MMRデータの情報(後でキャストする)
@param mdim				文書上の寸法（メディア座標系）
@param phres			結果コードアドレス
@return （MPCreateEMFPD参照）
*/
STDMETHOD_(MP_PD*, MPCreateMMRPD)(MPCSession* session, BYTE* pCompData, long compSize, long width, long height, long xppm, long yppm, MP_Dim mdim, HRESULT* phres = NULL) PURE;
/*!
@brief MHPDからV4のMMRPDを作成する。

この関数はV4のMH->MMRコンバータで使用し、
新しく作成されたPDをSetPDすることでコンバートが可能である。
このとき、古いMHPDをDestroy()することを忘れないこと。
MMRPDのサイズがもとのMHPDのサイズを超えた場合は、
リターン値=NULL, 結果コードは MP_NOERROR となる。
(コンバートする必要がないという意味)
pMHPD が転記禁止の場合は MP_ACCESSDENIED エラーとなる。
@param session		セッション
@param pMHPD		MHPD
@param[out] phres		結果コードアドレス
@return （MPCreateEMFPD参照）
*/
STDMETHOD_(MP_PD*, MPCreateMMRPDfromMHPD)(MPCSession* session, MP_PD* pMHPD, HRESULT* phres = NULL) PURE;
#endif //SFXVW
};

/*!
@brief V4.1拡張  PD生成インターフェイス
*/
mpinterface MP_PDFactory2 : public MP_PDFactory
{
#ifndef SFXVW
/*!
@brief メモリ上のJPEGデータからJPEG PDを作成する

pJpegdata で指定されたJpegデータを、mdim で指定された大きさでPDとして取り込む。
@param pSession セッション
@param pJpegdata	メモリ上のJpegデータ
@param jpegSize  Jpegデータのバイト数
@param dim		PDのサイズ
@retval MP_NOERROR 成功
@retval 負の値 取り込めなかった(Jpegファイルが不正、libJPEGで扱えないものなど)
*/
STDMETHOD_(MP_PD*, MPCreateJPEGPDfromMem)(MPCSession* session, BYTE* pJpegData, long jpegSize, MP_Dim dim, HRESULT* phres = NULL) PURE;
#endif //SFXVW
};

/*!
@brief V6拡張  PD生成インターフェイス
*/
mpinterface MP_PDFactory3 : public MP_PDFactory2
{
#ifndef SFXVW
/*!
@brief IMSファイルからPDを作成する
@param pSession セッション
@param pszImsFilePath IMSファイルのパス
@param dim PDのサイズ
@param[out] phres
@retval MP_PD* 生成されたPDのポインタ
*/
STDMETHOD_(MP_PD*, MPCreatePDfromImsFile)(MPCSession* pSession, MP_Path* pszImsFilePath, MP_Dim dim, HRESULT* phres = NULL) PURE;
/*!
@brief メモリ上のIMSデータからPDを作成する
@param pSession セッション
@param pCompData IMSデータのポインタ
@param compSize IMSデータのサイズ
@param dim PDのサイズ
@param[out] phres
@retval MP_PD* 生成されたPDのポインタ
*/
STDMETHOD_(MP_PD*, MPCreatePDfromImsMem)(MPCSession* pSession, BYTE* pCompData, long compSize, MP_Dim dim, HRESULT* phres = NULL) PURE;

// Unicode版
/*!
@param level	ビットマップ圧縮率  1:劣化無、2:高画質、3:標準、4:高圧縮
(他はV3のI/Fと同じ仕様であるので略)
*/
STDMETHOD_(MP_PD*, MPCreateBMPPDW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres) PURE;
/*!
@param level	ビットマップ圧縮率  1:劣化無、2:高画質、3:標準、4:高圧縮
(他はV3のI/Fと同じ仕様であるので略)
*/
STDMETHOD_(MP_PD*, MPCreateJPEGPDW)(MPCSession* session, const MP_WPath* jpegfilepath, MP_Dim dim, HRESULT* phres) PURE;
// V4追加
/*!
@param session		セッションオブジェクトアドレス
@param dibfilepath	DIBファイルパス
@param dim				文書上の寸法（メディア座標系）
@param level		PDが保持する画質指定（劣化なし、ありなど）
@param phres			結果コードアドレス
@param info	途中結果報告＆キャンセル用

MPCreateBMPPDに途中結果報告＆キャンセル機構を追加したものである。
info == NULL の場合はMPCreateBMPPDとまったく同じ動作をする。
処理は中断可能で、内部で info->callback に指定されたコールバック関数を呼び出す。
アプリケーションはコールバック関数のリターン値として、
MP_PROCESS_CONTINUE (処理を継続)
または
MP_PROCESS_CANCEL (処理を中断)
のいずれかを返すこと。
コールバック関数のリターン値が MP_PROCESS_CONTINUE の場合は処理を継続する。
MP_PROCESS_CANCEL の場合は処理を中断し制御を呼び出し元に返す。
引数 info が NULL、または info->callback が NULL の場合は
コールバック関数を呼び出さないので、この場合は処理を中断することはできない。

V4.1以降、levelにフラグMPC_AUTO_LOSSLESS_FLAGが
立っていると、高画質/標準/高圧縮のときでも劣化なしが
選択されることがある(圧縮サイズがより小さいと推定されたとき)
劣化なしでフラグが立っていても無視される。

@return
処理が中断された場合は MP_S_PROCESS_CANCELED (>0) を返す。
それ以外の場合はMPCreateBMPPDと同じである。*/
STDMETHOD_(MP_PD*, MPCreateBMPPDAdvW)(MPCSession* session, const MP_WPath* dibfilepath, MP_Dim dim, MP_Integer level, HRESULT* phres, MPC_AdvCancelInfo* info = NULL) PURE;
/*!
@brief IMSファイルからPDを作成する (unicode)
@param pSession セッション
@param imsFilePath IMSファイルのパス
@param dim PDのサイズ
@param[out] phres
@retval MP_PD* 生成されたPDのポインタ
*/
STDMETHOD_(MP_PD*, MPCreatePDfromImsFileW)(MPCSession* pSession, const MP_WPath* imsFilePath, MP_Dim dim, HRESULT* phres = NULL) PURE;
#endif //SFXVW
};


#endif // MPC_PD_H

//
//CHANGE LOG
//97.9.9 - Ichiriki - V3ヘッダ定義にて、pd3pub.h と canvas.hをマージ
//97.10.2 - Sumida - MP_PD::GetPDInfo()仕様変更（引数mdimの追加）
//97.10.2 - Sumida - MPCreateEMFPD, MPCreateWMFPD, MPCreateBMPPDの説明を補足
//97.10.6 - Sumida - MP_PD::GetPDInfo()引数のmdimに初期値NULLを設定
//97.10.21 - Ichiriki - 関数名のミス修正　MPCreateRAWCanvas()
//97.10.21 - Ichiriki - MP_Canvas に GetCanvasDim() 追加（WMFCanvas移行用）
//97.10.21 - Ichiriki - MP_PD::OLD_OnDraw, OLD_OnPrint 削除, MPCreateRAWCanvas引数修正
//97.11.6 - Ichiriki - MPC_PCAP_SUPPORT_TRANSPARENCY関連マクロ追加、デフォルト値記述変更。
//97.12.19 - Komoda - MPCLoadPDのコメントを変更(AR1807対応)
//98.06.16 - Ichiriki - V3.1：AR2947対策：設計ボード〜 MPC_PCAP_USE_PDの定義追加
//98.06.25 - Komoda - V3.1：AR2989対策：MPC_PCAP_BACKGROUND_PALETTEの定義追加
//99.03.16 - Ichiriki - V4: 仕様コメントを追記
//99.05.18 - Nakazawa - V4 DIRECTBLTフラグ、MP_PDFactory, MP_DeviceUtilities, GetCompData* 関連の実装追加
//99.05.18 - Komoda - V4 カラー判定、メタファイルのJPEG圧縮、サムネイル作成に関する実装追加
//99.05.18 - Ichiriki - セキュリティ関係の仕様を追記
//99.05.19 - Komoda - V4 MP_BitmapOperationsにMPCStretchBltを追加
//99.05.27 - Nakazawa - V4 MP_EMFPD, MP_WMFPD を削除
//99.06.14 - Nakazawa - V4 MP_MMRPD に bCodeCheck 追加, MPCreateMMRPDfromMHPD 追加
//99.07.01 - Ichiriki - V4 MPCCreateSecurityIcon() 追加
//99.07.30 - Ichiriki - V4 MP_BitmapOperations::MPCHDIBtoHBITMAP4 追加
//99.08.20 - Ichiriki - GetPDInfo() 仕様記載修正 compLevel 0: 圧縮無 の記述を削除
//99.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//00.05.10 - Nakazawa - V4 AR5442 GetColorTypeの仕様を追記
//----V41開発
//00.09.25 - Tashiro - V41 メモリからのJPEG直接取り込みを追加
//00.09.29 - Tashiro - V41 可逆圧縮の自動選択を指定するフラグ定義を追加
//00.11.30 - Tashiro - AR6224 可逆圧縮の自動選択を指定するフラグ定義をmpc_api.hに移動
//----V5開発
//2002.02.23 - Tashiro - 署名アイコン取得、利用可能セキュリティタイプ取得関数の追加
//2002.02.28 - Ichikawa - イメージページの低解像度変換関数 ThinImage 追加
//2002.03.01 - Ichikawa - MP_PD ThinImage の宣言を末尾 (GetColorType の次) に変更
//----V6開発
//2004.03.11 - Kudo - AR5286対応 WMFPD描画時のフォントサイズの矯正のためのSetPrinterCapsのフラグを追加
//2004.03.18 - Komoda - V60 PrinterCapsにMPC_PCAP_DRAW_ADVANCEを追加
//2004.04.09 - Tashiro - MP_PDFactory3追加
//2004.05.21 - Tashiro - IMS直接取り込み用I/Fを追加
//2004.06.08 - Tashiro - IMS直接取り込み用I/F変更(dim指定削除)
//2004.06.14 - Tashiro - MPCreateMrcPDFromImsMem()の宣言を追加
//2004.07.29 - Tashiro - AR10336 紛らわしい定数名の変更
//2004.08.06 - Tashiro - AR10261 IMS直接取り込みI/Fのdim指定復活
//2004.08.10 - Tashiro - AR10553 IMSからのMMR-PDへの直接取り込み機能を追加
//2004.08.10 - Tashiro - AR10553関連 MPCreatePDfromIms…()に関数名変更
//----V6.2.2
//2007.05.17 - Tashiro - AR13155 MP_PD::RotateOnMem追加
//----V7.0
//2007.08.06 - Komoda - ヘッダファイルのdoxygen対応
//2007.08.07 - Komoda - Unicode I/Fの追加
//2008.01.11 - Tashiro - MPCreatePRTCanvasの解像度小数指定版を追加
//2008.02.24 - Tashiro - Canvasにハイコントラスト描画情報を保持する機能を追加
//2008.03.13 - Tashiro - AR14268 ページ描画時に1画素内側でクリップしない指定をCanvasに追加
//2008.05.28 - Tashiro - AR14867 MF-PDをサムネールと同様の画質で描画する指定をCanvasに追加
