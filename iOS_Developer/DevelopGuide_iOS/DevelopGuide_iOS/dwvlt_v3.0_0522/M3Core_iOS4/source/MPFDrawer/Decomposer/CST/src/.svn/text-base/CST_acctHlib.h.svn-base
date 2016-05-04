/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_acctHlib.h	色補正パラメータ生成モジュールヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	May,29,2001	Toshio Yamazaki
 *
 * IMARI PLWドライバの以下のファイルをHostBased用に移植しました．
 * ただし，必要な部分のみが移植されています．
 * (特に，ICC周り別ファイルになっています)
 */
/**************************************************************
 * 名称：	cil_Hlib.h
 * 内容：	CST&LCCモジュール上位部分ヘッダファイル
 * ＯＳ：	Windows 95 / NT4.0
 * 言語：	MS-VC++
 *
 * 作成：	1998.11.27
 * 作成者：	穴吹哲士
 * 内容：	CST&LCCモジュール上位部分関数宣言
 *			ICCプロファイルデータフォーマットの定義
 ***************************************************************/
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

#include "CST_IF.h"

#ifndef CST_ACCTHLIB_H_INCLUDED
#define CST_ACCTHLIB_H_INCLUDED

/* RGB色補正モジュール関数					*/
/* White Point, GammaからRGB->sRGB変換パラメータを生成する	*/
/* 旧 cil_Create_CST_Param_WpGm()				*/
int CST_ACCT_MakeCorrectParamWpGm( CST_RGBcrParaData *, CST_RGBcrParaStatus * );

/* LCCモジュール関数						*/
/* LCC色調整パラメータを計算する				*/
/* 旧cil_Create_LCC_Param_sBGR()				*/
int CST_ACCT_MakeCorrectLCCParamsBGR( CST_LCCcrParaData *, CST_LCCcrParaStatus * );
/* グレイ調整パラメータを計算する				*/
/* 旧cil_Create_LCC_Param_sGray()				*/
int CST_ACCT_MakeCorrectLCCPramsGray( CST_LCCcrParaData *, CST_LCCcrParaStatus * );

#endif	/* CST_ACCTHLIB_H_INCLUDED */
