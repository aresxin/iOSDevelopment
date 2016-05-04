// File: DevUtils.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _DEVUTILS_H_
#define _DEVUTILS_H_

//#include <windows.h>

// 直接送信の場合にbiCompressionに指定する値
#define DEV_BI_JPEG		0x04
#define DEV_BI_ALLA		0x05

// カラーモノクロ指定用
#define DEV_PAGE_MONO		0x01
#define DEV_PAGE_COLOR		0x02

// PrivateEscapeのGate番号を返し、GateをEnableにする。失敗した場合は0以下の値のエラーコードを返す。
// pCheckCaps1〜3にはPrivateGateのCapabilityが格納される。必要がないなら指定しなくてもよい。
int PE_GetPrivateGateNo(HDC_XD hDC, DWORD* pCheckCaps1, DWORD* pCheckCaps2, DWORD* pCheckCaps3);

// checkCaps1〜3の機能のあるiFuncIDで指定したPrivateEscapeのPrivateFunction番号を返す。失敗した場合は0以下の値のエラーコードを返す。
// checkCaps1〜3は確認の必要がないなら指定しなくてもよい。
int PE_GetPrivateFuncNo(HDC_XD hDC, int iGateNo, int iFuncID, DWORD* pCheckCaps1 = NULL, DWORD* pCheckCaps2 = NULL, DWORD* pCheckCaps3 = NULL);

// PrivateEscapeを用いたDirectBltを使用可能にする関数。
// 成功ならPrivateFunctionの番号を、失敗なら0以下の値のエラーコードを返す。
int PE_EnableDirectBltFunc(HDC_XD hDC, int imageType);

// PrivateEscapeを用いたDirectBltができるかどうか判定する関数。
// 可能ならTRUE、不可ならFALSEを返す。
BOOL_XD PE_CanDirectBlt(HDC_XD hDC, int imageType);

// PrivateEscapeを用いたDirectBlt関数。
// 成功ならDirectBltしたライン数、失敗なら0以下の値のエラーコードを返す。
int PE_DirectBlt(HDC_XD hDC, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, DWORD dwRop,
				 LPBITMAPINFO lpBitsInfo, DWORD dwBitsInfoSize,
				 LPSTR lpImageData, DWORD dwImageSize, int degree, int imageType);

// PrivateEscapeを用いたカラーモノクロ指定を使用可能にする関数。
// 成功ならPrivateFunctionの番号を、失敗なら0以下の値のエラーコードを返す。
int PE_EnableSetColorModeFunc(HDC_XD hDC);

// PrivateEscapeを用いたカラーモノクロ指定ができるかどうか判定する関数。
// 可能ならTRUE、不可ならFALSEを返す。
BOOL_XD PE_CanSetColorMode(HDC_XD hDC);

// PrivateEscapeを用いたカラーモノクロ指定を使用可能にする関数。
// ::StartDoc()の前に呼び出さなければならない。
// 成功なら正の値を、失敗なら0以下の値のエラーコードを返す。
int PE_PreSetColorMode(HDC_XD hDC);

// PrivateEscapeを用いたカラーモノクロ指定関数。
// ::StartPage()の前に呼び出さなければならない。
// 成功なら正の値を、失敗なら0以下の値のエラーコードを返す。
int PE_SetColorMode(HDC_XD hDC, int mode);

// PrivateEscapeを用いたNup数取得関数。
// 成功なら正のNup数を、失敗なら0以下の値のエラーコードを返す。
int PE_GetNup(HDC_XD hDC);

// ローカルなエラーコード(mpc_api.hのエラーコードに一部準拠)
#define DEV_E_NOTSUPPORT	((int)0x00000000)		// サポートしていない
#define DEV_E_INVALIDARG	((int)0x80070057)		// パラメータ不正
#define DEV_E_OUTOFMEMORY	((int)0x8007000E)		// メモリ不足
#define DEV_E_UNEXPECTED	((int)0x8000FFFF)		// 予期せぬエラー
// 以下、pescape.h に準拠したエラーコード(pescdata.hで更新されたらこちらも修正する)
#define DEV_E_GENERAL		(-1)
#define DEV_E_UNKNOWN_ITEM	(-2)
#define DEV_E_UNKNOWN_FUNC	(-3)
#define DEV_E_PARAM			(-4)
#define DEV_E_RANGE			(-5)


#endif // _DEVUTILS_H_

// CHANGE LOG
// 1999.02.03 - Nakazawa - 新規作成
// 1999.02.10 - Nakazawa - BITMAPINFOを正しく渡せるよう修正
// 1999.02.12 - Nakazawa - PrivateEscapeのヘッダ更新を受けて差し替え
// 1999.02.16 - Nakazawa - PrivateEscape仕様変更を受けて修正
// 2000.09.25 - Nakazawa - V4.1 ALLA直接送信対応
