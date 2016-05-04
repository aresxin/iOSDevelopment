//
// $Archive: /DocuWorks/701/Source/include/linkcmm.h $ 
//
// Copyright (c) 1996-2002 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:29 $ 
// $Revision: 1.5 $ 
//

//
//	@ (s)
//		ViewerLight / for Webでリンクアノテの操作を行うため、
//		不必要な関数は、#ifndef で区別した。	('99/02/23 T.Matsuo)
//
#ifndef _LINKCMM_H_
#define _LINKCMM_H_

MPC_EXTERN_GUID(OT_LINK_CONTENT, 0xC02F); //リンクコンテント（付箋に乗らないため）

//リンクアノテーションの属性
#define	LINKATT_TITLESTR		"%LINKATT_TITLESTR"  	//リンクボタンのタイトル文字列
#define	LINKATT_ISDISPLAYICON	"%LINKATT_ISDISPLAYICON"	//アイコンを表示するか
#define LINKATT_LINKTO			"%LINKATT_LINKTO"		//URLか自分自身か、XDW文書パスか?
#define	LINKATT_URLSTR			"%LINKATT_URLSTR"		//URL文字列
#define	LINKATT_XDWSTR			"%LINKATT_XDWSTR"		//XDW文書パス文字列
#define LINKATT_XDWPAGENUM		"%LINKATT_XDWPAGENUM"	//XDW文書のページ番号（0ならPROFILE)

//
//	for DocuWorks V4.0 Viewer / Viewer Light / for Web
//
#define LINKATT_TRANSPARENT		"%LINKATT_TRANSPARENT"	//「透過表示」
#define LINKATT_AUTO_RESIZE		"%LINKATT_AUTO_RESIZE"	//「自動リサイズ」
#define LINKATT_PAGECHECK		"%LINKATT_PAGECHECK"	//ページの属性
#define LINKATT_SHEAFNAME		"%LINKATT_SHEAFNAME"	//内部文書名

///V50新規
const char LINKATT_MAILADDRESS[] = {"%LINKATT_MAILADDRESS"};	///メールアドレス文字列
const char LINKATT_OTHERFILE_PATH[] = {"%LINKATT_OTHERFILE_PATH"};	///”その他のファイル”ファイルパス
const char LINKATT_OTHERFILE_RELATIVE[] = {"%LINKATT_OTHERFILE_RELATIVE"};	///”その他のファイル”相対パスチェック
const char LINKATT_DW_JUMPTYPE[] =	{"%LINKATT_DW_JUMPTYPE"};	///DocuWorks文書の場合の、ページ指定かリンクジャンプ指定か？
const char LINKATT_DW_RELATIVE[] = {"%LINKATT_DW_RELATIVE"};	///DocuWorks文書の相対パスチェック
const char LINKATT_LINKTITLE[] = {"%LINKATT_LINKTITLE"};	///DocuWorks文書のリンクタイトルジャンプのタイトル文字列
const char LINKATT_USERTOOLTIP[] = {"%LINKATT_USERTOOLTIP"};	///ツールチップをユーザ指定とするかどうか？
const char LINKATT_USER_TOOLTIP_STR[] = {"%LINKATT_USER_TOOLTIP_STR"};	///ユーザが設定したツールチップ文字列
const char LINKATT_DWJUMP_FILETYPE[] = {"%LINKATT_DWJUMP_FILETYPE"};	///DocuWorks文書のジャンプで、このファイル、他のファイルの指定

const char LINKATT_STARCH[] = {"%ATTR_STARCH"};	//糊付け属性

//
//タイトル周りは不必要
//
#ifndef _M3CORE_MP_
//タイトル文字のフォント属性
#define LINKATT_TITLE_FACE      "%LINKATTR_TITLE_FACE"	//タイトル文字列のフェイス
#define LINKATT_TITLE_STYLE     "%LINKATTR_TITLE_STYLE"	//タイトル文字列のスタイル
#define LINKATT_TITLE_POINTSIZE "%LINKATTR_TITLE_POINTSIZE"	//タイトル文字列のポイントサイズ
#define LINKATT_TITLE_COLOR     "%LINKATTR_TITLE_COLOR"	//タイトル文字列の色
#define LINKATT_TITLE_PITCHANDFAMILY     "%LINKATTR_TITLE_PITCHANDFAMILY" //タイトル文字列のファミリー
#define	LINKATT_TITLE_CHARSET	"%LINKATT_TITLE_CHARSET"
#define LINKATT_TEXT_TOO_LARGE     "%LINKATT_TEXT_TOO_LARGE"
#endif	//_M3CORE_MP_

#define MAX_LINK_TITLE	255//最大文字列長//AR7628
#define MAX_LINK_URL	256
//#define MAX_LINK_XDWPATH 256
const int MAX_LINK_XDWPATH	=	256;

const int MAX_TOOLTIP_LENGTH_BUFFER	= 512;

const int MAX_MAIL_ADDRESS = 256;		// AR6879

//LINKTO属性（URLか自分自身か、XDW文書パス）
//#define LINK_TO_ME		0
//#define LINK_TO_XDW		1
//#define LINK_TO_URL		2
const int LINK_TO_ME			=	0;
const int LINK_TO_XDW			=	1;
const int LINK_TO_URL			=	2;
const int LINK_TO_OTHERFILE		=	3;
const int LINK_TO_MAILADDRESS	=	4;

///V50新規
///DocuWorks文書へのリンクで、このファイルか他のファイルかのフラグ
///上のLINKTO属性との兼ね合いに注意すること。
const int DW_LINK_TYPE_THIFILE		=	0;
const int DW_LINK_TYPE_OTHERFILE	=	1;

//
//	for DocuWorks V4.0 Viewer / Viewer Light / for Web
//
#define LINK_THIS_FILE			0	///「この文書」指定
#define LINK_BINDER_ALLPAGE		1	///「このバインダの通しページ」指定
#define LINK_BINDER_OTHER_DOC	2	///「このバインダの他の文書のページ」指定

///V50。リンク先を設定するコンボボックスで使用する定義
///上のLINKTO属性と整合性をとる必要がある。
const int LINK_TARGET_WWW		=	0;
const int LINK_TARGET_DWDATA	=	1;
const int LINK_TARGET_OTHER		=	2;
const int LINK_TARGET_MAIL		=	3;

///V50。DocuWorks文書へのリンクで、
///ページ指定か、リンクアノテーションへのジャンプか？を示す
const int LINK_TO_DWTYPE_PAGE		=	0;
const int LINK_TO_DWTYPE_LINKANN	=	1;
//
//	これ以降は、VLT/forWebでは使用しない
//	
#ifndef _M3CORE_MP_
//LINKContのDoProcedureのID
#define PROC_LINK_SETDOWNFLAG 0x2F01
#define PROC_LINK_GETDOWNFLAG 0x2F02
#define PROC_LINK_GETPATH	  0x2F03
#define PROC_LINK_SET_MPUISVC_HANDLE	0x2F04	// マルチスレッド対応

#include "mpsvchdl.h"

class CMPUIObject;
__declspec(dllexport) BOOL_XD WINAPI IsLinkActive(MPUISVC_HANDLE hMpuisvc);
__declspec(dllexport) void WINAPI AddUIObject(MPUISVC_HANDLE hMpuisvc, CMPUIObject* uiObj);
__declspec(dllexport) void WINAPI RemoveUIObject(MPUISVC_HANDLE hMpuisvc, CMPUIObject* uiObj);
__declspec(dllexport) void WINAPI InitializeLinkAgentDll(MPUISVC_HANDLE hMpuisvc);
__declspec(dllexport) void WINAPI FinalizeLinkAgentDll(MPUISVC_HANDLE hMpuisvc);
#endif	//_M3CORE_MP_

#endif //#ifndef _LINKCMM_H_

// $History: linkcmm.h $
// 
// *****************  Version 3  *****************
// User: Maruyama     Date: 09/07/17   Time: 16:28
// Updated in $/DocuWorks/701/Source/include
// [FD004] 医療DMS対応
// 
// *****************  Version 1  *****************
// User: Yoji         Date: 09/05/27   Time: 15:15
// Created in $/DocuWorks/etc/proto/IryoDMS/Source/include
// 医療DMSプロジェクトを追加
// 
// *****************  Version 4  *****************
// User: Yoji         Date: 06/06/02   Time: 19:48
// Updated in $/DocuWorks/62/Source/include
// FinalizeAgentDllの追加
// 
// *****************  Version 3  *****************
// User: Yoji         Date: 06/05/29   Time: 17:47
// Updated in $/DocuWorks/62/Source/include
// 先行開発分のマージ
// 
// *****************  Version 2  *****************
// User: Yoji         Date: 06/05/15   Time: 14:45
// Updated in $/Proto/MultiThread/Source/include
// Title用のDoProcedureのIDを定義、InitializeAgentDllを追加
// 
// *****************  Version 1  *****************
// User: Yoji         Date: 06/03/30   Time: 9:42
// Created in $/Proto/MultiThread/Source/include
// 2006/03/30 マルチスレッド対応先行開発
// 
// *****************  Version 1  *****************
// User: Terajima     Date: 03/06/23   Time: 11:44
// Created in $/DocuWorks/60/SOURCE/include
// 新規作成
// 
// *****************  Version 12  *****************
// User: Tmatsuo      Date: 02/06/27   Time: 18:41
// Updated in $/V50/Viewer/include
// 
// *****************  Version 11  *****************
// User: Tatsu        Date: 02/05/16   Time: 6:48p
// Updated in $/V50/Viewer/include
// AR6879 修正
// 
// *****************  Version 10  *****************
// User: Arai         Date: 02/04/12   Time: 7:49p
// Updated in $/V50/Viewer/include
// のり付け属性値のプレフィックス”%”を追加した
// 
// *****************  Version 9  *****************
// User: Kurimura-yoshio Date: 02/04/05   Time: 22:15
// Updated in $/V50/Viewer/include
//
