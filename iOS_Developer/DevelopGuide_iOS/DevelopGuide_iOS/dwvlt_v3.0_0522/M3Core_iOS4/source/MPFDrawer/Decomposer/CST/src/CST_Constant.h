/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_Constant.h	色補正パラメータ定数用ヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	May,29,2001	Toshio Yamazaki
 *
 * IMARI PLWドライバの以下のファイルの内，定数を切り出したものです.
 */
/**************************************************************
 * 名称：	ACCTHLib.c
 * 内容：	CST&LCCモジュール上位部分
 * ＯＳ：	Windows 95 / NT4.0
 * 言語：	MS-VC++
 *
 * 作成：	1998.11.27
 * 作成者：	穴吹哲士
 * 内容：	以下の画質調整共通ライブラリを実装する
 *			★CST系関数群
 *				cil_Check_ICC_Prof
 *				cil_Create_CST_Param_WpGm
 *				cil_Create_CST_Param_Prof
 *				cil_Dispose_CST_Param
 *			★LCC系関数群
 *				cil_Create_LCC_Param_sBGR
 *				cil_Create_LCC_Param_sGray
 ***************************************************************/
/*
 * $History: acctHlib.c $
 * 
 * *****************  Version 1  *****************
 * User: Miyazono-kenzo Date: 99/04/23   Time: 16:00
 * Created in $/PLWNTDrv_Post/lib/um
 * 
 * *****************  Version 17  *****************
 * User: Anabuki      Date: 99/01/20   Time: 13:45
 * Updated in $/PLW95Drv/Src
 * AR211６（Win95ドライバでICC profileを読み込むときにtagの大きさが64kB
 * 以上だと正常にプリントされない）の問題を解決するため、huge_read()関数
 * 内部で32768byte単位でデータを読み込むようにし、一度のデータ読み込み
 * でセグメント境界を跨いだ読み込みが行われないようにした。（従来は65532
 * byte単位で読み込んでいた）
 * 
 * *****************  Version 16  *****************
 * User: Kawata-tomoya Date: 98/12/10   Time: 14:50
 * Updated in $/PLW95Drv/Src
 * 色変換モジュール仕様変更修正完了に伴い、"-DCIL_CST_RCADDED"部分のロジッ
 * クを正式版とし、#ifdef定義を削除。
 */
#ifndef CST_CONSTANT_H_INCLUDED
#define CST_CONSTANT_H_INCLUDED
#include "CST_InternalDef.h"
#include "CST_acctHlib.h"

/*
 * ローカルに用いられる型
 */

/*
 * ローカルに用いられる定数
 */
/* sRGBの三刺激値			*/
extern const CST_ACCT_XYZ sRedXYZ;
extern const CST_ACCT_XYZ sGreenXYZ;
extern const CST_ACCT_XYZ sBlueXYZ;

/* sRGBの三刺激値をD50に変換した値	*/
extern const CST_ACCT_XYZ d50RedXYZ;
extern const CST_ACCT_XYZ d50GreenXYZ;
extern const CST_ACCT_XYZ d50BlueXYZ;

/* sRGBの三刺激値を9300Kに変換した値	*/
extern const CST_ACCT_XYZ k9300RedXYZ;
extern const CST_ACCT_XYZ k9300GreenXYZ;
extern const CST_ACCT_XYZ k9300BlueXYZ;
/* D50のwhite point			*/
extern const CST_ACCT_XYZ d50XYZ;
/* D65のwhite point			*/
extern const CST_ACCT_XYZ d65XYZ;
/* 9300Kのwhite point			*/
extern const CST_ACCT_XYZ k9300XYZ;

/* XYZからsRGBへの変換行列		*/
extern const float CST_ACCT_XYZ2sRGBMatrix[3][3];

/* White, Thomsonの生理三原色のxy座標	*/
extern const CST_ACCT_xy wtRedxy;
extern const CST_ACCT_xy wtGreenxy;
extern const CST_ACCT_xy wtBluexy;

#define kACCT_N_TRC		256		/* TRCのステップ数 */

/* γ=1.0のTRC		*/
extern const unsigned short gamma10TRC[kACCT_N_TRC];
/* γ=1.4のTRC		*/
extern const unsigned short gamma14TRC[kACCT_N_TRC];
/* γ=1.8のTRC		*/
extern const unsigned short gamma18TRC[kACCT_N_TRC];
/* γ=2.2のTRC		*/
extern const unsigned short gamma22TRC[kACCT_N_TRC];
/* γ=2.6のTRC		*/
extern const unsigned short gamma26TRC[kACCT_N_TRC];

// RGB→sRGB色変換の出力側のLUT
//extern const unsigned char XYZ2sRGBTrc[4096];
extern const unsigned char CST_Default_XYZ2sRGB_1DLUT_Data[4096];
#endif	/* CST_CONSTANT_H_INCLUDED */
