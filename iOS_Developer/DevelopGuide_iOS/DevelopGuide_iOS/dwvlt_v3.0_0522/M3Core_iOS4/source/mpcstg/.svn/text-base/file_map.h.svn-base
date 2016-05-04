// File: File_Map.H
// Auther: Hisashi Sumida
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef _File_Map_
#define _File_Map_

#include "mpc_api.h"
#include "mpcwcstr.h"

//#include <windows.h>

/*
*     File Mapping API
*/

class MPC_FileMap
{
public:
	MPC_FileMap();
	~MPC_FileMap();
	
	// WindowsMobile対応
	// 09/12/03 M.Chikyu
	
	// メモリ割り当て位置までのオフセットを指定可能に変更
	void* MPC_CreateFileMapping(const MP_WPath*	filepath,
								long			size,
								long			exist,
								HRESULT*		phres = NULL,
								MP_OpenMode		openMode = OM_READWRITE,
								long*			rtnSize = NULL,
								MP_Integer		sizeLimit = FALSE,
								long			offset = 0);
	// exist = 0:新たに作成するファイル、1:すでに存在するファイル
	// offset:ファイル先頭からメモリ割り当て位置までのオフセット
	
	// マルチバイト対応を用意
	void* MPC_CreateFileMapping(const MP_Path*	filepath,
								long			size,
								long			exist,
								HRESULT*		phres = NULL,
								MP_OpenMode		openMode = OM_READWRITE,
								long*			rtnSize = NULL,
								MP_Integer		sizeLimit = FALSE,
								long			offset = 0);
	
	// WindowsMobile対応
	// 09/12/09 M.Chikyu
	
	// 仮想メモリ領域をReadOnlyでマッピングしなおす
	void* MPC_ChangeReadOnly(HRESULT *phr);
	
	long MPC_CloseFileMapping(void* ptr, long deleteFile);
	//deleteFile = 0:ファイルを削除しない、1:ファイルを削除する
	
private:
	
	void *SUB_CreateFileMapping(const MP_WPath* w_path,
								const MP_Path* a_path,
								long size,
								long exist,
								HRESULT* phres,
								MP_OpenMode openMode,
								long* rtnSize,
								MP_Integer sizeLimit,
								long offset);
	
private:
	
	HANDLE m_hFile;
	HANDLE m_mFile;
	void* m_buf;
	mpcwcstring m_filepath;
	
};

#endif // _File_Map_

//CHANGE LOG
//97.9.24 - Sumida - 作成
//97.10.30 - Nagano - CORE SPI変更に対応
//2002.11.12 - Tashiro - 5.0.2 AR6978対応に併せてm_filepath長に定数を使用
