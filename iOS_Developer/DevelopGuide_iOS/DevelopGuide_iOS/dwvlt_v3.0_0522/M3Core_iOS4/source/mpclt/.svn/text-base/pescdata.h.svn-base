//****************************************************************************
//	Fuji Xerox PLW Printer Driver for Windows95
//
//	名称：pescdata.h
//	内容：PrivateEscapeを使用するアプリケーション/ドライバー用ヘッダーファイル
//
//
//  Copyright (C) 1998,1999 Fuji Xerox Co., Ltd. All rights reserved.
//	作成開始：	1998.12.17
//****************************************************************************

/*
 * $History: pescdata.h $
// 
// *****************  Version 1  *****************
// User: Terajima     Date: 03/06/23   Time: 11:48
// Created in $/DocuWorks/60/SOURCE/mpclt
// 新規作成
 * 
 * *****************  Version 9  *****************
 * User: Asada-kei    Date: 00/01/17   Time: 4:04p
 * Updated in $/PLW95Drv_PostPost/Source/Src
 * ALLAデータ処理の追加
 * 
 * *****************  Version 8  *****************
 * User: Asada-kei    Date: 99/07/09   Time: 10:23a
 * Updated in $/tools/ControlUT/ctrluts
 * AR3384:RECT構造体の定義がWin16とWin32とで異なっていたので共通使用のため
 * に、FXPE_RECTを定義した。
 * 
 * *****************  Version 7  *****************
 * User: Asada-kei    Date: 99/07/08   Time: 8:17p
 * Updated in $/PLW95Drv_Post/Source/Src
 * 
 * *****************  Version 6  *****************
 * User: Asada-kei    Date: 99/06/24   Time: 11:29a
 * Updated in $/PLWNTDrv_Post/source/fxplw
 * GATE呼出し番号範囲の下限を0x1000から0x0040に下げた。
 * 
 * *****************  Version 5  *****************
 * User: Asada-kei    Date: 99/06/18   Time: 8:59p
 * Updated in $/PLW95Drv_Post/Source/Src
 * PrivateGateのCapabilities1の値が一段ずれていたのを修正した。
 * 
 * *****************  Version 4  *****************
 * User: Asada-kei    Date: 99/06/09   Time: 9:17p
 * Updated in $/PLW95Drv_Post/Source/Src
 * コードレビュー指摘事項の反映
 * 
 * *****************  Version 3  *****************
 * User: Asada-kei    Date: 99/06/09   Time: 8:32p
 * Updated in $/PLW95Drv_Post/Source/Src
 * FXESCCAPS_GATE_PRIVATEGATEの値を0x1から0x80000000に変更した。
 * 
 * *****************  Version 2  *****************
 * User: Asada-kei    Date: 99/06/04   Time: 9:52p
 * Updated in $/PLW95Drv_Post/Source/Src
 * ページごとのカラーモードして、レイアウト情報の取得/設定の実装追加
 * 
 * *****************  Version 1  *****************
 * User: Miyazono-kenzo Date: 99/04/23   Time: 15:55
 * Created in $/PLWNTDrv_Post/fxplw
 * 
 * *****************  Version 5  *****************
 * User: Asada-kei    Date: 99/03/02   Time: 6:34p
 * Updated in $/PLW95Drv/Src
 * FXPE_DIRECT_BLT_IMAGE構造体のメンバー DestX、DestY、SrcX、SrcYを WORD
 * からSHORTに変更した。
 * 
 * *****************  Version 4  *****************
 * User: Asada-kei    Date: 99/02/15   Time: 6:26p
 * Updated in $/PLW95Drv/Src
 * 構造体中にintが混在していたので、unsigned shortに変更した。
 * 
 * *****************  Version 3  *****************
 * User: Asada-kei    Date: 99/02/12   Time: 11:01p
 * Updated in $/PLW95Drv/Src
 * PrivateEscape:イメージデータを分割して送付できるように変更した。
 * 
 * *****************  Version 2  *****************
 * User: Asada-kei    Date: 99/02/10   Time: 11:31p
 * Updated in $/PLW95Drv/Src
 * バイトアライメントのためのProgrma命令の追加
 * 
 * *****************  Version 1  *****************
 * User: Asada-kei    Date: 99/02/10   Time: 6:43p
 * Created in $/PLW95Drv/Src
 * アプリ/ドライバー共用のデータ定義ファイル
 */

#ifndef _PESCDATA_H_
#define	_PESCDATA_H_

//========================================
//	構造体のアライメントをBYTEバウンダリにする
//========================================
#ifdef PRIVATEESCAPE_ALIGN_BYTE
#pragma pack(push, enter_parser)
#pragma pack(1)
#endif // PRIVATEESCAPE_ALIGN_BYTE

#if defined(QUERYESCSUPPORT)
	;
#else //  undefined(QUERYESCSUPPORT)
#define GETTECHNOLOGY		8
#define QUERYESCSUPPORT		20
#endif //  undefined(QUERYESCSUPPORT)

#if defined(PRIVATEESCAPE_BASIC_TYPES)
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned long		DWORD;
typedef unsigned int		UINT;
typedef signed short		USHORT;
#endif // defined(PRIVATEESCAPE_BASIC_TYPES)

//
//	エラーコード
//
#define FXPE_ERROR_GENERAL		(-1)
#define FXPE_ERROR_UNKNOWN_ITEM	(-2)
#define FXPE_ERROR_UNKNOWN_FUNC	(-3)
#define FXPE_ERROR_PARAM		(-4)
#define FXPE_ERROR_RANGE		(-5)
#define FXPE_ERROR_MODE			(-6)

// GATE呼出し番号範囲
#define FXESC_GATENO_MIN		0x0040
#define FXESC_GATENO_MAX		0x7FFF

// GATEコマンド
#define FXESC_IDENTIFY		0x6585
#define FXESC_ENABLE		0x1
#define FXESC_DISABLE		0x2
#define FXESC_QUERY_FUNCINFO		0x3

// ID文字列
#define FXESC_ID_NUMBER	0x46585045L		// "FXPE"を表す4バイト

//PrivateFunction機能番号
#define FXESCFUNC_PRIVATEGATE			0x1101
#define FXESCFUNC_DIRECT_BLT			0x1102
#define FXESCFUNC_SET_PAGE_COLORMODE	0x1103
#define FXESCFUNC_LAYOUT				0x1104
#define FXESCFUNC_GET_PROP				0x1105
#define FXESCFUNC_QUERY_DEVMODE			0x1106
#define FXESCFUNC_GETSET_DEVMODE		0x1107

//PrivateGateのCapabilities1の値
#define FXESCCAPS_GATE_PRIVATEGATE			0x00000001
#define FXESCCAPS_GATE_DIRECT_BLT			0x00000002
#define FXESCCAPS_GATE_SET_PAGE_COLORMODE	0x00000004
#define FXESCCAPS_GATE_LAYOUT				0x00000008
#define FXESCCAPS_GATE_GET_PROP				0x00000010
#define FXESCCAPS_GATE_QUERY_DEVMODE		0x00000020
#define FXESCCAPS_GATE_GETSET_DEVMODE		0x00000040

// FXESCFUNC_DIRECT_BLTコマンドで使用する値
#define FXBI_RGB		BI_RGB			// 0x00
#define FXBI_RLE8		BI_RLE8			// 0x01
#define FXBI_RLE4		BI_RLE4			// 0x02
#define FXBI_BITFIELDS	BI_BITFIELDS	// 0x03
#define FXBI_JPEG		0x04
#define FXBI_ALLA		0x05

//	イメージIDの最大値
#define	FXPE_IMAGE_ID_MAX		(0x4000)

// FXESC_DIRECT_BLTのCapabilities1の値
#define FXESCCAPS_DIRECT_BLT_BI_RGB			0x00000001
#define FXESCCAPS_DIRECT_BLT_BI_RLE8		0x00000002
#define FXESCCAPS_DIRECT_BLT_BI_RLE4		0x00000004
#define FXESCCAPS_DIRECT_BLT_BI_BITFIELDS	0x00000008
#define FXESCCAPS_DIRECT_BLT_BI_JPEG		0x00000010
#define FXESCCAPS_DIRECT_BLT_BI_ALLA		0x00000020

// FXESCFUNC_SET_PAGE_COLORMODEコマンド
#define FXPE_SET_COLORMODE_APPAUTO	0x1201
#define FXPE_SET_COLORMODE_DRVDEF	0x1202
#define FXPE_SET_PAGE_GRAY			0x1203
#define FXPE_SET_PAGE_COLOR			0x1204
#define FXPE_SET_PAGE_AUTO			0x1205

// FXESCFUNC_SET_PAGE_COLORMODEのCapabilities1の値
#define FXPECAPS_SPC_SET_COLORMODE_APPAUTO	0x00000001
#define FXPECAPS_SPC_SET_COLORMODE_DRVDEF	0x00000002
#define FXPECAPS_SPC_SET_PAGE_GRAY			0x00000004
#define FXPECAPS_SPC_SET_PAGE_COLOR			0x00000008
#define FXPECAPS_SPC_SET_PAGE_AUTO			0x00000010

// FXESCFUNC_LAYOUTコマンド
#define FXPE_GET_DUPLEX			0x1301
#define FXPE_SET_DUPLEX			0x1302
#define FXPE_GET_SIMPLY_N		0x1303
#define FXPE_SET_SIMPLE_NUP		0x1304

// FXESCFUNC_NUP設定値
#define FXPE_LAYOUT_SIMPLEX			0x1311
#define FXPE_LAYOUT_DUPLEX_LONG		0x1312
#define FXPE_LAYOUT_DUPLEX_SHORT	0x1313
#define FXPE_LAYOUT_DUPLEX_DRVDEF	0x1314

// FXESCFUNC_LAYOUTのCapabilities1の値
#define FXPECAPS_LAYOUT_GET_DUPLEX			0x00000001
#define FXPECAPS_LAYOUT_SET_SIMPLEX			0x00000002
#define FXPECAPS_LAYOUT_SET_DUPLEX_LONG		0x00000004
#define FXPECAPS_LAYOUT_SET_DUPLEX_SHORT	0x00000008
#define FXPECAPS_LAYOUT_SET_DUPLEX_DRVDEF	0x00000010
#define FXPECAPS_LAYOUT_GET_SIMPLY_N		0x00000100
#define FXPECAPS_LAUOUT_SET_SIMPLE_NUP		0x00000200

// FXESCFUNC_LAYOUTのCapabilities2の値
#define FXPECAPS__LAYOUT_NUP_01	0x00000001
#define FXPECAPS__LAYOUT_NUP_02	0x00000002
#define FXPECAPS__LAYOUT_NUP_03	0x00000004
#define FXPECAPS__LAYOUT_NUP_04	0x00000008
#define FXPECAPS__LAYOUT_NUP_05	0x00000010
#define FXPECAPS__LAYOUT_NUP_06	0x00000020
#define FXPECAPS__LAYOUT_NUP_07	0x00000040
#define FXPECAPS__LAYOUT_NUP_08	0x00000080
#define FXPECAPS__LAYOUT_NUP_09	0x00000100
#define FXPECAPS__LAYOUT_NUP_10	0x00000200
#define FXPECAPS__LAYOUT_NUP_11	0x00000400
#define FXPECAPS__LAYOUT_NUP_12	0x00000800
#define FXPECAPS__LAYOUT_NUP_13	0x00001000
#define FXPECAPS__LAYOUT_NUP_14	0x00002000
#define FXPECAPS__LAYOUT_NUP_15	0x00004000
#define FXPECAPS__LAYOUT_NUP_16	0x00008000
#define FXPECAPS__LAYOUT_NUP_17	0x00010000
#define FXPECAPS__LAYOUT_NUP_18	0x00020000
#define FXPECAPS__LAYOUT_NUP_19	0x00040000
#define FXPECAPS__LAYOUT_NUP_20	0x00080000
#define FXPECAPS__LAYOUT_NUP_21	0x00100000
#define FXPECAPS__LAYOUT_NUP_22	0x00200000
#define FXPECAPS__LAYOUT_NUP_23	0x00400000
#define FXPECAPS__LAYOUT_NUP_24	0x00800000
#define FXPECAPS__LAYOUT_NUP_25	0x01000000
#define FXPECAPS__LAYOUT_NUP_26	0x02000000
#define FXPECAPS__LAYOUT_NUP_27	0x04000000
#define FXPECAPS__LAYOUT_NUP_28	0x08000000
#define FXPECAPS__LAYOUT_NUP_29	0x10000000
#define FXPECAPS__LAYOUT_NUP_30	0x20000000
#define FXPECAPS__LAYOUT_NUP_31	0x40000000
#define FXPECAPS__LAYOUT_NUP_ANY	0x80000000

//FXESCFUNC_GET_PROPコマンド
#define FXPE_PROP_DRIVER		0x1401
#define FXPE_PROP_LANGUAGE		0x1402
#define FXPE_PROP_DFILE_NUM		0x1403
#define FXPE_PROP_DFILES		0x1404

// FXESCFUNC_GET_PROPのCapabilities1の値
#define FXPECAPS_GP_PROP_DRIVER	0x00000001
#define FXPECAPS_GP_PROP_LANGUAGE	0x00000002
#define FXPECAPS_GP_PROP_DFILE_NUM	0x00000004
#define FXPECAPS_GP_PROP_DFILES	0x00000008

// FXESCFUNC_QUERY_DEVMODEコマンド
#define FXESC_QUERY_DEVMODE_PROP	0x1501
#define FXESC_QUERY_MEMBER_LIST	0x1502
#define FXESC_QUERY_MEMBER_PROP	0x1503
#define FXESC_QUERY_COLLECTION_LIST	0x1504

// FXESCFUNC_QUERY_DEVMODE機能ビットフラグ
#define FXESC_HAS_COLOR		0x00000001L
#define FXESC_HAS_1PERPIXEL		0x00000002L
#define FXESC_HAS_8PERPIXEL		0x00000004L
#define FXESC_HAS_DUPLEX		0x00000008L
#define FXESC_HAS_COLLATE		0x00000010L
#define FXESC_HAS_NUP		0x00000020L
#define FXESC_HAS_SIGNATURE		0x00000040L
#define FXESC_HAS_OCT		0x00000080L
#define FXESC_HAS_ZOOM		0x00000100L

// FXESCFUNC_QUERY_DEVMODE値範囲タイプ
#define FXESC_ANY		0x1511
#define FXESC_AREA		0x1512
#define FXESC_SOME		0x1513

// FXESCFUNC_QUERY_DEVMODE/FXESCFUNC_ACCESS_DEVMODE変数型
#if 0 // now no use
#if !defined(DDM_TYPE_BOOL_XD)
#define	DDM_TYPE_BOOL_XD	1	//BOOL_XD
#define	DDM_TYPE_INT16	5	//16bit signed integer
#define	DDM_TYPE_UINT16	6	//16bit unsigned Integer / WORD
#define	DDM_TYPE_INT32	10	//32bit signed integer /LONG
#define	DDM_TYPE_UINT32	11	//32bit unsigned integer /DWORD
#define	DDM_TYPE_STRING	20	//string value
#define	DDM_TYPE_FLOAT	30	//float value
#endif !defined(DDM_TYPE_BOOL_XD)
#endif // 0 // now no use

// FXESCFUNC_QUERY_DEVMODEのCapabilities1の値
#define FXESCCAPS_QD_DEVMODE_PROP	0x00000001
#define FXESCCAPS_QD_MEMBER_LIST	0x00000002
#define FXESCCAPS_QD_MEMBER_PROP	0x00000004
#define FXESCCAPS_QD_COLLECTION_LIST	0x00000008

// FXESCFUNC_GETSET_DEVMODEのCapabilities1の値
#define FXESCCAPS_GSD_GETSET_DEVMODE	0x00000001

// GATE入力用構造体

typedef struct tag_FXPE_STRCT_GATE{
		DWORD	dwSize;				// 構造体サイズ
		WORD	wCommand;			// GATEコマンド
		WORD	wFuncID;			// Function番号
}FXPE_STRCT_GATE, FAR *LPFXPE_STRCT_GATE;
typedef const FXPE_STRCT_GATE FAR *		LPC_FXPE_STRCT_GATE;

typedef struct tag_FXPE_STRCT_FUNC_CAPS{
		DWORD	dwSize;				// 構造体サイズ
		WORD	wFuncNo;			// 呼出し番号
		DWORD	dwCapabilities1;	// ビットフラグ1
		DWORD	dwCapabilities2;	// ビットフラグ2
		DWORD	dwCapabilities3;	// ビットフラグ3
}FXPE_STRCT_FUNC_CAPS, FAR *LPFXPE_STRCT_FUNC_CAPS;

// FXESCFUNC_DIRECT_BLT入力用構造体

typedef struct tag_FXPE_DIRECT_BLT_PARAM{
		DWORD	dwSize;							// この構造体のサイズ
		DWORD	dwo_DirectBltImageParam;		// StretchDIBの引数相当
		DWORD	dwImageTotalSize;				// イメージデータ全体のサイズ
		DWORD	dwImageSendingOffset;			// 添付したイメージの先頭からのオフセット
		DWORD	dwImageSendingSize;				// 今回添付したデータのサイズ
		WORD	wImageID;						// 最初は0を設定する。以降は、戻り値のIDを設定する。
		USHORT	iDegree;						// 時計と反対周りの回転角度(90度単位のみ有効)
		DWORD	dwo_Logbr;						// 論理ブラシ
		DWORD	dwo_dm;							// DRAWMODE
		DWORD	dwo_Clip;						// ClipRect
}FXPE_DIRECT_BLT_PARAM, FAR * LPFXPE_DIRECT_BLT_PARAM;
typedef const FXPE_DIRECT_BLT_PARAM FAR *LPC_FXPE_DIRECT_BLT_PARAM;


typedef struct tag_LPFXPE_DIRECT_BLT_IMAGE{
		DWORD	dwSize;							// この構造体のサイズ
		SHORT	DestX;							// 描画する位置とサイズ
		SHORT	DestY;
		WORD	DestXE;
		WORD	DestYE;
		SHORT	SrcX;							// 元画像のサイズ(位置は常に0,0)
		SHORT	SrcY;
		WORD	SrcXE;
		WORD	SrcYE;
		DWORD	dwo_Bits;						// イメージデータへのオフセット値
		DWORD	dwo_BitmapInfo;					// BITMAPINFOへのオフセット値
		DWORD	dwRop;							// ROP3の値
}FXPE_DIRECT_BLT_IMAGE, FAR* LPFXPE_DIRECT_BLT_IMAGE;
typedef const FXPE_DIRECT_BLT_IMAGE FAR *LPC_FXPE_DIRECT_BLT_IMAGE;


//AR3384:
//	Win16とWin32とでRECTの定義が異なるので、再定義する。
//
typedef struct tag_FXPE_RECT{
	SHORT	left;
	SHORT	top;
	SHORT	right;
	SHORT	bottom;
} FXPE_RECT, FAR *LPFXPE_RECT;
typedef const FXPE_RECT FAR *LPC_FXPE_RECT;


// FXESCFUNC_LAYOUT入出力用構造体
typedef struct tag_FXPE_LAYOUT{
		DWORD	dwSize;						// 構造体のサイズ
		WORD	wCommand;					// コマンド種
		WORD	wParam;						// 引数
}FXPE_LAYOUT, LPFXPE_LAYOUT;
typedef const FXPE_LAYOUT FAR *LPC_FXPE_LAYOUT;

// FXESCFUNC_GET_PROP入出力用構造体
typedef struct tag_FXPE_STRCT_PROP_DRIVER{
		DWORD	dwSize;						// 構造体のサイズ
		BYTE	szName[64];
		DWORD	dwLevel;
}FXPE_STRCT_PROP_DRIVER, FAR *LPFXPE_STRCT_PROP_DRIVER;

typedef struct tag_FXPE_STRCT_PROP_LANGUAGE{
		DWORD	dwSize;						// 構造体のサイズ
		BYTE	szName[64];
		DWORD	dwLevel;
}FXPE_STRCT_PROP_LANGUAGE, FAR *LPFXPE_STRCT_PROP_LANGUAGE;

typedef struct tag_FXPE_STRCT_PROP_DFILE{
		DWORD	dwSize;						// 構造体のサイズ
		BYTE	szName[MAX_PATH];
		DWORD	dwLevel;
}FXPE_STRCT_PROP_DFILE, FAR *LPFXPE_STRCT_PROP_DFILE;

// FXESCFUNC_QUERY_DEVMODE入出力用構造体

typedef struct tag_FXPE_QUERY_DEVMDOE{
		DWORD	dwSize;
		WORD	wCommand;
		WORD	wMemberID;
		WORD	wItemNum;
}FXPE_QUERY_DEVMDOE, FAR *LPFXPE_QUERY_DEVMDOE;

typedef struct tag_FXPE_DEVMODE_PROP{
		DWORD	dwSize;
		DWORD	dwType;
		WORD	wNumMember;
}FXPE_DEVMODE_PROP, FAR *LPFXPE_DEVMODE_PROP;

typedef struct tag_FXPE_MEMBER_PROP{
		DWORD	dwSize;
		WORD	wType;
		WORD	wNumCollection;
}FXPE_MEMBER_PROP, FAR *LPFXPE_MEMBER_PROP;

// FXESCFUNC_GETSET_DEVMODE入出力用構造体
typedef WORD DDM_DATATYPE;
typedef struct tag_FXPE_ACCESS_DEVMDOE{
		DWORD			dwSize;
		WORD			wFuncID;
		DDM_DATATYPE	t_dataType;
		DWORD			dwValue;
}FXPE_ACCESS_DEVMDOE, FAR *LPFXPE_ACCESS_DEVMDOE;

//========================================
//	構造体のアライメントを元に戻す
//========================================
#ifdef PRIVATEESCAPE_ALIGN_BYTE
#pragma pack(pop, enter_parser)
#endif // PRIVATEESCAPE_ALIGN_BYTE

#endif // ifndef _PESCDATA_H_
// EOF
