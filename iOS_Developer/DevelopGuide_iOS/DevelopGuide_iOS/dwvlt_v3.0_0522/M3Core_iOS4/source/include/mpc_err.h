// File: mpc_err.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

/*
Win32API の GetLastError() で返ってくるエラーコードを、
mpc_api.h で定義されている HRESULT 型のエラーコードに変換する。
いくつかのモジュールで似たようなコードが分散して入っているので、
それらをまとめる意味で作成された。
もともとは mpstg の mpfile.cpp に実装されていたものである。
*/

#ifndef _MPC_ERR_H
#define _MPC_ERR_H

#include "mpc_api.h"

//#include <windows.h>

/*
§HRESULT 型のエラーコード を Windows のエラーコードから取得する関数

(いくつかのモジュールで共通に用いたいため、ここに定義する)
*/

/*
§MPCConvertWinErrorToMPError	〜　HRESULT 型のエラーコード を Windows のエラーコードから取得する
*/
DLLBINDFUNC_(HRESULT, MPCConvertWinErrorToMPError)(DWORD errcd);
/*
Win32API の GetLastError() で取得されるエラーコード errcd から、
HRESULT 型で定義されている MP_E_* のエラーコードに変換する。
*/

/*
§MPCGetLastError	〜　MP版GetLastError関数
*/
#define MPCGetLastError()	MPCConvertWinErrorToMPError(::GetLastError())
/*
上記の MPCConvertWinErrorToMPError を使用する。
*/

#endif // _MPC_ERR_H

// CHANGE LOG
// 1999.05.28 - Nakazawa - 新規作成
// 1999.06.14 - Nakazawa - 関数をインライン化
// 1999.06.18 - Nakazawa - 実装を mpcapi に移動
// 1999.06.29 - Nakazawa - 関数名変更に伴う修正
