// File: SignatureCont.h
// Author: Kiyoshi Tashiro
// Copyright (C) 2002 by Fuji Xerox Co., Ltd.  All rights reserved.

#ifndef	_SIGNATURE_CONT_H_
#define	_SIGNATURE_CONT_H_

// 署名オブジェクト
MPC_EXTERN_GUID(OT_SIGNATURE_CONTENT, 0x8043);

// 印鑑ケースのルートオブジェクト
MPC_EXTERN_GUID(CLSID_STAMP_CASE_ROOT, 0xC044);

// 署名オブジェクトが持つ属性
#define ATT_SIGNATURE_MODULE_ID "%smid"
	// 署名モジュールのID  INT
#define ATT_SIGNATURE_MODULE_NAME "%smin"
	// 署名モジュールの名前  OCTS
#define ATT_SIGNATURE_PRIVATE_DATA "%spd"
	// 署名モジュールが扱うデータ OCTS
#define ATT_SIGNATURE_PD_BEFORE_VERIFICATTON "%pdbv"
	// 署名の検証前の外観のPD
	// #pd には状態表示無しの外観を付ける

#define ATT_SIGNATURE_BEFORE_SAVE "%sbs"

// 署名オブジェクトのDoProcedureで使うprocedureID
#define PROC_SIGNATURE_SHOW_STATUS 0x2F41 // 署名状態の表示/非表示
#define PROC_SIGNATURE_VERIFY_ALL 0x2F42 // すべての署名を検証
#define PROC_SIGNATURE_GETPATH 0x2F03 // 開いているファイルのパスを得る
	// リンクオブジェクトの PROC_LINK_GETPATH と同じ動作なので同じIDを付ける
	// LINKCMM.H 参照
#endif

// Change Log.
// 2002.2.5 - Tashiro - Created.
// 2002.02.28 - Tashiro - クラスID確定、属性定義、DoProcedure ID追加
// 2002.05.18 - Tashiro - DoProcedure用ID追加 ロールバック機能用
// 2002.05.22 - Tashiro - AR7435 印鑑ケースファイルのルートオブジェクトIDを変更
// 2006.12.08 - Tashiro - AR13322 署名保存が完了する前の状態を表す属性を定義
