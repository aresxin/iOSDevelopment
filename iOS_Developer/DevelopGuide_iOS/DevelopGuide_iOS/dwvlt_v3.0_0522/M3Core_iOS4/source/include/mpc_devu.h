// File: mpc_devu.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _MPDEVUTL_H_
#define _MPDEVUTL_H_

#include "mpc_api.h"

//#include <windows.h>

/*
§9. デバイス連携関連のインタフェース

V4 デバイス連携のカラーモノクロ指定や圧縮イメージ直接送信で必要な関数群をまとめたものである。
mpc_devu.h は、MSVC++ 6.0 の WIN32 API の ヘッダファイル windows.h に依存する。
*/

DLLBINDFUNC_(MP_DeviceUtilities*, MPCGetDeviceUtilities)(MPCSession* session);

/*
§9.1 デバイス連携関連 共通定義

§9.1.1 定数・マクロ定義
*/

// 直接送信の際、biCompression に指定する値
#define MP_DEV_BI_JPEG		0x04
#define MP_DEV_BI_ALLA		0x05	// V4.1

/*
§9.2 MP_DeviceUtilities インタフェース

§9.2.1 インタフェースID
*/
MPC_EXTERN_GUID(IID_DeviceUtilities, 0x1321);

/*
§9.2.2 メソッド一覧
*/
mpinterface MP_DeviceUtilities
{
STDMETHOD(CanDirectBlt)(MPCSession* session, HDC_XD hDC, int imageType = MP_DEV_BI_JPEG) PURE;
STDMETHOD(DirectBlt)(MPCSession* session, HDC_XD hDC, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, DWORD dwRop, LPBITMAPINFO lpBitsInfo, DWORD dwBitsInfoSize, LPSTR lpImageData, DWORD dwImageSize, int degree, int imageType) PURE;
STDMETHOD(CanSetColorMode)(MPCSession* session, HDC_XD hDC) PURE;
STDMETHOD(PreSetColorMode)(MPCSession* session, HDC_XD hDC) PURE;
STDMETHOD(SetColorMode)(MPCSession* session, HDC_XD hDC, int mode) PURE;
STDMETHOD(GetNup)(MPCSession* session, HDC_XD hDC) PURE;
};

/*
§9.2.3 各メソッドの定義

対応しているデバイスのみ可能(Limogesなど)。

利用者は mpc_api.h と mpdevutl.h をインクルードして、
	MP_DeviceUtilities* devutl = (MP_DeviceUtilities*)MPCGetDeviceUtilities(session);
により MP_DeviceUtilities を取得することで以下の関数群を使用することができる。

圧縮イメージ直接送信は、印刷処理開始時に
	MP_Canvas *pCanvas = ::MPCreatePRTCanvas(...);
	if (bDirectBlt) {	// 直接送信が指定されていたら
		MPC_PrinterCaps printerCaps = pCanvas->GetPrinterCaps();
		MPC_PCAP_SetDirectBlt(printerCaps);	// 直接送信フラグをセット
		pCanvas->SetPrinterCaps(printerCaps);
	}
	// 印刷処理続行(これでPDがフラグを見て自動的に直接送信を行う)
とすればよい。


§CanDirectBlt
・パラメータ
MPCSession* session
HDC hDC					プリンタのデバイスコンテキスト
int imageType			直接送信するイメージのタイプ

・説明
hDCにDirectBlt(Jpeg直接送信など)ができるかどうかを尋ねる。
imageType には直接送信可能かどうかを尋ねたいイメージのタイプを指定する。
V4 では Jpeg しか送れないので、imageType は省略して呼ぶこと。
V4.1 からは Jpeg と ALLA(Adaptive) ともに直接送信できるようになったが、
UIでは分けられていないので、imageType は省略したままで構わない。

・リターン値
可能：MP_S_OK
不可：MP_S_FALSE


§DirectBlt
・パラメータ
MPCSession* session
HDC hDC					プリンタのデバイスコンテキスト
int XDest				転送先の矩形の左上隅のX座標(論理単位)
int YDest				転送先の矩形の左上隅のY座標(論理単位)
int nDestWidth			転送先の矩形の幅(論理単位)
int nDestHeight			転送先の矩形の高さ(論理単位)
int XSrc				元画像の矩形のX座標(ピクセル単位)(現在は0でなければならない)
int YSrc				元画像の矩形のY座標(ピクセル単位)(現在は0でなければならない)
int nSrcWidth			元画像の矩形の幅(ピクセル単位)
int nSrcHeight			元画像の矩形の高さ(ピクセル単位)
DWORD dwRop				ラスタオペレーション(現在はSRCCOPYでなければならない)
LPBITMAPINFO lpBitsInfo	元画像のBITMAPINFO構造体へのポインタ(必要ならパレット情報も付加する)
DWORD dwBitsInfoSize	元画像のBITMAPINFOのサイズ
LPSTR lpImageData		圧縮イメージデータへのポインタ
DWORD dwImageSize		圧縮イメージデータのサイズ
int degree				回転角度(90度単位)
int imageType			圧縮イメージの種類(現在はMP_DEV_BI_JPEGのみサポート)
						V4.1よりMP_DEV_BI_ALLAもサポートする。

・説明
hDCに圧縮イメージを指定パラメータで伸長せずに送る。
各パラメータは StretchDIBits で指定するパラメータと同じものを指定する。

・リターン値
成功：MP_NOERROR
失敗：負の値(MP_E_*)


§CanSetColorMode
・パラメータ
MPCSession* session
HDC hDC					プリンタのデバイスコンテキスト

・説明
hDCにカラーモノクロ指定ができるかどうかを尋ねる。

・リターン値
可能：MP_S_OK
不可：MP_S_FALSE


§PreSetColorMode
・パラメータ
MPCSession* session
HDC hDC					プリンタのデバイスコンテキスト

・説明
hDCに「これからアプリケーション側でカラーモノクロ指定をする」と宣言する。
Win32APIのStartDocの前に行わなければならない。
この関数実行後のデフォルトはモノクロモードである。

・リターン値
成功：MP_NOERROR
失敗：負の値(MP_E_*)


§SetColorMode
・パラメータ
MPCSession* session
HDC hDC					プリンタのデバイスコンテキスト
int mode				カラー/モノクロのモード

・説明
hDCにカラーモノクロ指定をする。
Win32APIのStartPageの前に行わなければならない。
mode には mpc_api.h に定義されている MP_COLORTYPE_* を指定すること。

・リターン値
成功：MP_NOERROR
失敗：負の値(MP_E_*)


§GetNup
・パラメータ
MPCSession* session
HDC hDC					プリンタのデバイスコンテキスト

・説明
hDCからN-up数を取得する。
カラーモノクロ指定を行うとき、あらかじめ先読みするページ数を取得する際に用いる。

・リターン値
成功：正の値(N-up数)
失敗：0または負の値(MP_E_*)

*/

#endif // _MPDEVUTL_H_

// CHANGE LOG
// 1999.05.18 - Nakazawa - 作成
// 1999.06.04 - Nakazawa - コメント修正
// 1999.08.03 - Nakazawa - V4 コードレビューの結果を反映
// 2000.09.25 - Nakazawa - V4.1 ALLA直接送信対応
