// File: dwmdll.h
// Author: Takashi Matsumoto
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.  

#ifndef DWMDLL_H
#define DWMDLL_H

#include "mpc_api.h"

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_HANDLE(HDWMAKER);

/*!
変換処理のステータスを表す構造体
*/
typedef struct tagDWM_Status
{
	int	phase;
    int	pages;
	int page;
} DWM_Status;

// DWM_Status.phaseの値
#define DWM_P_BEGINNING			1	//!<生成処理準備中
#define DWM_P_PRINTING			2	//!<アプリケーションで印刷中
#define DWM_P_PAGE_CREATING		3	//!<ページを生成中
#define DWM_P_CNTDOC_CREATING	4	//!<オリジナルデータ生成中
#define DWM_P_WRITING			5	//!<ファイルに書き込み中
#define DWM_P_ENDING			6	//!<終了処理中
#define DWM_P_CANCELING			7	//!<中止処理中
#define DWM_P_FINISHED			8	//!<処理完了
#define DWM_P_CANCELD			9	//!<中止完了

/*!
@brief アプリケーションファイルの変換処理を開始する

@param[in] originalFile アプリケーションファイルのパス
@param[in] directory 出力ディレクトリのパス
@param[in] withOriginal オリジナルデータを添付するかどうか
@param[in] session MPCSessionオブジェクト
@param[out] phres リザルトコード格納先
@return HDWMAKER makerのハンドル
*/
__declspec(dllexport) HDWMAKER __stdcall DWM_BeginDWFileCreation(
	LPCSTR originalFile, LPCSTR directory, BOOL_XD withOriginal,
	MPCSession *session, HRESULT *phres);

/*!
@brief アプリケーションファイルの変換処理を開始する (unicode)

@param[in] originalFile アプリケーションファイルのパス
@param[in] directory 出力ディレクトリのパス
@param[in] withOriginal オリジナルデータを添付するかどうか
@param[in] session MPCSessionオブジェクト
@param[out] phres リザルトコード格納先
@return HDWMAKER makerのハンドル
*/
__declspec(dllexport) HDWMAKER __stdcall DWM_BeginDWFileCreationW(
	const MP_WPath *originalFile, const MP_WPath *directory, BOOL_XD withOriginal,
	MPCSession *session, HRESULT *phres);

/*!
@brief アプリケーションファイルの変換処理を開始する(サマリ指定)

@param[in] originalFile
@param[in] directory
@param[in] bSummaryInfo サマリインフォをつけるかどうか
@param[in] withOriginal
@param[in] session
@param[out] phres
@return HDWMAKER makerのハンドル
*/
__declspec(dllexport) HDWMAKER __stdcall DWM_BeginDWFileCreationEx(
	LPCSTR originalFile, LPCSTR directory, BOOL_XD withOriginal,
	BOOL_XD bSummaryInfo, MPCSession *session, HRESULT *phres);

/*!
@brief アプリケーションファイルの変換処理を開始する(サマリ指定) (unicode)

@param[in] originalFile
@param[in] directory
@param[in] bSummaryInfo サマリインフォをつけるかどうか
@param[in] withOriginal
@param[in] session
@param[out] phres
@return HDWMAKER makerのハンドル
*/
__declspec(dllexport) HDWMAKER __stdcall DWM_BeginDWFileCreationExW(
	const MP_WPath *originalFile, const MP_WPath *directory, BOOL_XD withOriginal,
	BOOL_XD bSummaryInfo, MPCSession *session, HRESULT *phres);

/*!
@brief 文書変換の終了処理

@param[in] handle makerのハンドル
@param[out] destPath 出力パスを格納するバッファ
@param[in] pathBytes 出力パスのバッファサイズ
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
__declspec(dllexport) HRESULT __stdcall DWM_EndDWFileCreation(
	HDWMAKER handle, LPSTR destPath = NULL, int pathBytes = 0);

/*!
@brief 文書変換の終了処理 (unicode)

@param[in] handle makerのハンドル
@param[out] destPath 出力パスを受け取る文字列オブジェクト
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
__declspec(dllexport) HRESULT __stdcall DWM_EndDWFileCreationW(
	HDWMAKER handle, MP_String &destPath);

/*!
@brief 文書変換のステータスを確認する

@param[in] handle makerのハンドル
@param[out] status ステータスの格納先
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
__declspec(dllexport) HRESULT __stdcall DWM_GetDWFileCreationStatus(
	HDWMAKER handle, DWM_Status *status);

/*!
@brief 文書変換を中止する

@param[in] handle makerのハンドル
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
__declspec(dllexport) HRESULT __stdcall DWM_CancelDWFileCreation(
	HDWMAKER handle);

/*!
@brief アプリケーションファイルのプロパティを取得する

@param[in] filename アプリケーションファイルのパス
@param[in] mp 文書オブジェクト
@param[in] nSuccession 継承する
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
__declspec(dllexport) HRESULT __stdcall DWM_GetApliProperties(
	LPCSTR filename, MPCObject *mp, MP_Integer nSuccession) ;

/*!
@brief アプリケーションファイルのプロパティを取得する (unicode)

@param[in] filename アプリケーションファイルのパス
@param[in] mp 文書オブジェクト
@param[in] nSuccession 継承する
@retval MP_NOERROR 成功
@retval 負値 エラー
*/
__declspec(dllexport) HRESULT __stdcall DWM_GetApliPropertiesW(
	const MP_WPath *filename, MPCObject *mp, MP_Integer nSuccession) ;

// for DWMAKER.EXE
/*!
@brief mpiファイルからの変換処理を開始する

@param[in] mpiFilePath DWPrinterが出力したmpiファイルのパス
@param[in] dwFilePath 生成するDW文書のパス
@param[in] overWrite 文書がすでに存在したときに上書きするかどうか
@param[in] session MPCSessionオブジェクト
@param[in] phres リザルトコード格納先
@return HDWMAKER makerのハンドル
*/
__declspec(dllexport) HDWMAKER __stdcall DWM_BeginDWFileCreationFromMpi(
	LPCSTR mpiFilePath, LPCSTR dwFilePath, BOOL_XD overWrite,
	MPCSession *session, HRESULT *phres);

/*!
@brief mpiファイルからの変換処理を開始する (unicode)

@param[in] mpiFilePath DWPrinterが出力したmpiファイルのパス
@param[in] dwFilePath 生成するDW文書のパス
@param[in] overWrite 文書がすでに存在したときに上書きするかどうか
@param[in] session MPCSessionオブジェクト
@param[in] phres リザルトコード格納先
@return HDWMAKER makerのハンドル
*/
__declspec(dllexport) HDWMAKER __stdcall DWM_BeginDWFileCreationFromMpiW(
	const MP_WPath *mpiFilePath, const MP_WPath *dwFilePath, BOOL_XD overWrite,
	MPCSession *session, HRESULT *phres);

/*!
@brief mpiファイルとwmf/emfファイルを削除する

@param[in] mpiPath 削除するmpiファイルのパス
@return なし
*/
__declspec(dllexport) void __stdcall DWM_DeleteMpiAndMetafiles(
	LPCSTR mpiPath);

/*!
@brief mpiファイルとwmf/emfファイルを削除する (unicode)

@param[in] mpiPath 削除するmpiファイルのパス
@return なし
*/
__declspec(dllexport) void __stdcall DWM_DeleteMpiAndMetafilesW(
	const MP_WPath *mpiPath);

#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // DWMDLL_H

// CHANGE LOG
// 97.9.12 - Matsumoto - 新規作成
// 97.10.31 - Matsumoto - Desk要求: DWM_EndDWFileCreationに引数追加
// 2002.1.31 - Ichikawa - V5.0 DWM_BeginDWFileCreationEx, DWM_GetApliProperties 追加
