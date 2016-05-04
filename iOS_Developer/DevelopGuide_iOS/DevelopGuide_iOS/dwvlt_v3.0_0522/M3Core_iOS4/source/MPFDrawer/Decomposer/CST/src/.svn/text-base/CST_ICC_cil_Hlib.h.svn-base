/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_ICC_cil_Hlib.h	ICC処理モジュールヘッダファイル
 * Fuji Xerox Co., Ltd. DPSC SD開推 PFCore G 山崎寿夫
 *
 * Created:	Feb,25,2003	Toshio Yamazaki
 *
 * IMARI PLWドライバの以下のファイルをのうちICC周りをHostBased用に移植しました．
 */
//**************************************************************
// 名称：	cil_Hlib.h
// 内容：	CST&LCCモジュール上位部分ヘッダファイル
// ＯＳ：	Windows 95 / NT4.0
// 言語：	MS-VC++
//
// 作成：	1998.11.27
// 作成者：	穴吹哲士
// 内容：	CST&LCCモジュール上位部分関数宣言
//			ICCプロファイルデータフォーマットの定義
//**************************************************************
/*
 * $History: cil_Hlib.h $
 * 
 * *****************  Version 1  *****************
 * User: Miyazono-kenzo Date: 99/04/23   Time: 16:00
 * Created in $/PLWNTDrv_Post/inc
 * 
 * *****************  Version 9  *****************
 * User: Kawata-tomoya Date: 98/12/10   Time: 14:50
 * Updated in $/PLW95Drv/Src
 * 色変換モジュール仕様変更修正完了に伴い、"-DCIL_CST_RCADDED"部分のロジッ
 * クを正式版とし、#ifdef定義を削除。
 */

#ifndef CST_ICC_CIL_HLIB_H_INCLUDED
#define CST_ICC_CIL_HLIB_H_INCLUDED

#include "CST_IF.h"
#include "icc34.h"

#define CST_ICC_CIL_NOERROR			0	/* 正常終了 */
#define CST_ICC_CIL_PARAM_ERROR			-1	/* パラメータの値が不正 */

#define CST_ICC_CIL_FILE_OPEN_ERROR		-2	/* ファイルopen失敗 */
#define CST_ICC_CIL_FILE_READ_ERROR		-3	/* ファイルread失敗 */
#define CST_ICC_CIL_FILE_CLOSE_ERROR		-4	/* ファイルclose失敗 */
#define CST_ICC_CIL_NOT_PROFILE_ERROR		-5	/* 与えられたファイルはprofileではない */
#define CST_ICC_CIL_UNSUPPORTED_PROFILE_ERROR	-6	/* このprofileはCSTライブラリで使用できない */
#define CST_ICC_CIL_ILLEGAL_PROFILE_ERROR	-7	/* profileがICCのspecに反している */
#define CST_ICC_CIL_MEMORY_ERROR		-8	/* メモリエラー */

int CST_ICC_cil_Check_ICC_Prof( CST_ICCProfileData* cst_p );
int CST_ICC_cil_Create_CST_Param_Prof( void *sif_mi, CST_ICCProfileData* cst_p );

#endif	/* CST_ICC_CIL_HLIB_H_INCLUDED */
