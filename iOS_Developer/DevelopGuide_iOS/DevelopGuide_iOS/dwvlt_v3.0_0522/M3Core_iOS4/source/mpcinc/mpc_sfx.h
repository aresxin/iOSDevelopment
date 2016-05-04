// File: mpc_sfx.h
// Auther: Hideki Ichiriki
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

// 自己解凍文書ファイルに関する定義

#ifndef _MPC_SFX_H_
#define _MPC_SFX_H_


// 自己解凍型MP管理情報(V3の48バイト(12要素)時の配列要素番号)
const int Info_MagicNum = 0;		// SFXファイル識別用マジックナンバー
									//   V3 = "DW30", V4 = "DW40"
const int Info_SelfextSize = 1;		// mpcsfx.exe のサイズ (bytes)
const int Info_ViewerSize = 2;		// dwqview.exe （圧縮前）のサイズ (bytes)
const int Info_ViewerCompSize = 3;	// dwqview.exe （圧縮後）のサイズ (bytes)
const int Info_MpSize = 4;			// DW文書のサイズ (bytes)
const int Info_InfoSize = 5;		// 管理情報のサイズ (bytes)　V3=48, V4=56
const int Info_MpCreateTimeL = 6;	// DWFileの作成日時（ファイル時間の下位32ビット）
const int Info_MpCreateTimeH = 7;	// DWFileの作成日時（ファイル時間の上位32ビット）
const int Info_MpWriteTimeL = 8;	// DWFileの最終更新日時（ファイル時間の下位32ビット）
const int Info_MpWriteTimeH = 9;	// DWFileの最終更新日時（ファイル時間の下位32ビット）
const int Info_MpAtt = 10;			// DWFileのファイル属性
const int Info_Version = 11;		// SFXファイルのバージョン 
									//		V3=0x00000300, V4=0x00000400


// 自己解凍文書 管理情報
const int InfoNumV3 = 12;
const int InfoSizeV3 = 48;
const unsigned long InfoVersion3 = 0x00000300;

const int InfoNumV4 = 14;
const int InfoSizeV4 = 56;
const unsigned long InfoVersion4 = 0x00000400;

#endif // _MPC_SFX_H_

// CHANGE LOG
// 1999.07.3 - Ichiriki - 新規作成 ( V4開発のため 定義を mpcstg から転記）
