//
//  w2m_base.h
//
//  Updater : $Author: kawashin $
//  Version : $Revision: 1.3 $, $Date: 2009/03/10 08:34:23 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

// Windows版からの移植に際し、winbase.h の必要な内容をMAC用に定義
#ifndef W2M_BASE_H
#define W2M_BASE_H

#include <stdio.h>
#include <fcntl.h>

#include "w2mpf_def.h"
#include "w2mpf_error.h"
#include "w2mpf_gdi_def.h"

#ifdef __cplusplus
extern "C" {
#endif
// ファイル操作
#define CREATE_NEW	    1
#define CREATE_ALWAYS	2
#define OPEN_EXISTING	3
#define OPEN_ALWAYS		4
#define TRUNCATE_EXISTING	5

// ファイルポインタ操作
#define	FILE_BEGIN	SEEK_SET
#define FILE_CURRENT	SEEK_CUR
#define FILE_END	SEEK_END

// ファイルフラグ
#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000

#define INVALID_HANDLE_VALUE	(HANDLE)-1

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;

typedef struct _OVERLAPPED {
    DWORD   Internal;
    DWORD   InternalHigh;
    DWORD   Offset;
    DWORD   OffsetHigh;
    HANDLE  hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL_XD bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

HANDLE CreateFile(
	LPCTSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);

BOOL_XD CloseHandle(
	HANDLE	hObject
);

BOOL_XD DeleteFile(
	LPCTSTR path
);

BOOL_XD CopyFile(
	LPCTSTR lpExistingFileName,
	LPCTSTR lpNewFileName,
	BOOL_XD bFailIfExists
);

DWORD SetFilePointer(
	HANDLE	hFile,
	LONG	lDistanceToMove,
	PLONG	lpDistanceToMoveHigh,
	DWORD	dwMoveMethod
);

BOOL_XD SetEndOfFile(
	HANDLE hFile
);

BOOL_XD ReadFile(
	HANDLE	hFile,
	LPVOID	lpBuffer,
	DWORD	nNumberOfBytesToRead,
	LPDWORD	lpNumberOfBytesRead,
	LPOVERLAPPED	lpOverlapped
);

BOOL_XD WriteFile(
	HANDLE hFile,
	LPCVOID	lpBuffer,
	DWORD	nNumberOfBytesToWrite,
	LPDWORD	lpNumberOfBytesWritten,
	LPOVERLAPPED	lpOverlapped
);

DWORD GetFileSize(
	HANDLE	hFile,
	LPDWORD	lpFileSizeHigh
);

UINT GetTempFileName(
	LPCTSTR lpPathName,
	LPCTSTR lpPrefixString,
	UINT    uUnique,
	LPTSTR  lpTempFileName
);

DWORD GetTempPath(
	DWORD nBufferLength,
	LPTSTR lpBuffer
);

// エラー操作
#define initErrno() (errno = 0)

DWORD GetLastError();

void SetLastError(
	DWORD	dwErrCode
);

// 文字列操作
int lstrlen(
	LPCTSTR	lpString
);

LPTSTR lstrcpy(
	LPTSTR lpString1,
	LPCTSTR lpString2
);

// メモリアクセス
/* Global Memory Flags */
#define GMEM_FIXED          0x0000
#define GMEM_MOVEABLE       0x0002
#define GMEM_NOCOMPACT      0x0010
#define GMEM_NODISCARD      0x0020
#define GMEM_ZEROINIT       0x0040
#define GMEM_MODIFY         0x0080
#define GMEM_DISCARDABLE    0x0100
#define GMEM_NOT_BANKED     0x1000
#define GMEM_SHARE          0x2000
#define GMEM_DDESHARE       0x2000
#define GMEM_NOTIFY         0x4000
#define GMEM_LOWER          GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS    0x7F72
#define GMEM_INVALID_HANDLE 0x8000

#define GHND                (GMEM_MOVEABLE | GMEM_ZEROINIT)
#define GPTR                (GMEM_FIXED | GMEM_ZEROINIT)

typedef struct _MEMORYSTATUS {
    DWORD dwLength;
    DWORD dwMemoryLoad;
    DWORD dwTotalPhys;
    DWORD dwAvailPhys;
    DWORD dwTotalPageFile;
    DWORD dwAvailPageFile;
    DWORD dwTotalVirtual;
    DWORD dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

HGLOBAL GlobalAlloc(
	UINT uFlags,
	DWORD dwBytes
);

HGLOBAL GlobalFree(
	HGLOBAL	hMem
);

#define GlobalAllocPtr(flags, cb) GlobalAlloc((flags), (cb))
#define GlobalFreePtr(lp) GlobalFree(lp)

//DWORD GlobalSize(HGLOBAL hMem);

LPVOID GlobalLock(
    HGLOBAL hMem // handle to the global memory object
);

BOOL_XD GlobalUnlock(
    HGLOBAL hMem // handle to the global memory object
);

/*VOID GlobalMemoryStatus(
    LPMEMORYSTATUS lpBuffer // pointer to the memory status structure
);*/

#define CopyMemory RtlCopyMemory

typedef CRITICAL_SECTION*	LPCRITICAL_SECTION;

VOID InitializeCriticalSection(
    LPCRITICAL_SECTION  lpCriticalSection
);

VOID DeleteCriticalSection(
	LPCRITICAL_SECTION lpCriticalSeciton
);

VOID EnterCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
);

VOID LeaveCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
);

HANDLE CreateEvent(
	LPSECURITY_ATTRIBUTES lpEventAttributes,
	BOOL_XD bManualReset,
	BOOL_XD bInitialState,
	LPCSTR lpName
);

DWORD WaitForSingleObject(
	HANDLE hHandle,
	DWORD dwMilliseconds
);

DWORD WaitForMultipleObjects(
	DWORD nCount,
	const HANDLE* lpHandles,
	BOOL_XD bWaitAll,
	DWORD dwMilliseconds
);

// その他
typedef struct _OSVERSIONINFO{ 
	DWORD dwOSVersionInfoSize; 
	DWORD dwMajorVersion; 
	DWORD dwMinorVersion; 
	DWORD dwBuildNumber; 
	DWORD dwPlatformId; 
	char  szCSDVersion[ 128 ]; 
} OSVERSIONINFO, *LPOSVERSIONINFO; 

#define VER_PLATFORM_UNIX               10
#define VER_PLATFORM_WIN32s             0
#define VER_PLATFORM_WIN32_WINDOWS      1
#define VER_PLATFORM_WIN32_NT           2

BOOL_XD GetVersionEx(
	LPOSVERSIONINFO	lpVersionInformation
);

// add 2001/12/12 by AVSS
DWORD GetTickCount();

// add for Mac OSX
#define ZeroMemory(area,len) memset(area,0x0,len);

// 
// Linux対応
// 09/02/12 Masafumi Chikyu
//

// 新規コード

//
// HANDLEに格納するHANDLEオブジェクトのクラスを定義する
//
// base_handle：ベースクラス
// file_handle：FILE*を格納する
//
namespace WIN_HANDLE
{
	///////////////////////////////////////
	//
	// ハンドルベースクラス
	//
	///////////////////////////////////////
	class base_handle
	{
	protected:
	
		// ハンドルがオープンしているかどうかのフラグ
		// フラグがオープンとなる条件は各クラスによって異なる
		bool m_openFlag;
		
		// 各メンバ変数の初期化		
		virtual void initVal()	{};
		
	public:

		//
		// コンストラクタ
		//		
		base_handle()
		{
			// メンバ変数の初期化
			initVal();
		};
		
		//
		// デストラクタ
		//
		virtual ~base_handle()
		{
			// ハンドルがオープンの場合はクローズする
			if (m_openFlag == true)
			{
				closeHandle();
			}
		};

		//
		// ハンドルのクローズ処理
		// 実装は各クラスに依存する
		//
		virtual bool closeHandle()
		{
			return false;
		};
		
		virtual operator FILE*()
		{
			return NULL;
		};
	};
	
	
	///////////////////////////////////////
	//
	// ファイルハンドルクラス
	//
	///////////////////////////////////////
	class file_handle: public base_handle
	{
	protected:
	
		// ストリームファイルポインタ
		FILE *m_fp;
		
		// クローズ時にファイル削除を示すフラグ
		bool m_delOnCloseFlag;
		
		// 削除するファイル名
		std::string m_fname;

		// 各メンバ変数の初期化		
		void initVal();
		
	public:

		//
		// コンストラクタ
		//
		file_handle()
		{
			initVal();
		};
		
		//
		// デストラクタ
		//
		virtual ~file_handle()
		{
		};
		
		//
		// ハンドルのクローズ処理
		//
		// 返り値：成功した場合にtrue、失敗した場合にfalse
		//
		bool closeHandle();
		
		//
		// ハンドルクローズ時にファイルを削除するフラグを設定
		//
		// fname：削除するファイル名
		//
		void setDelOnCloseFlag(const char *fname);

		//
		// 代入演算子
		//
		// fp：オープンしたファイルのストリームファイルポインタ
		//
		// ファイルポインタを代入されるとハンドルをオープンに設定する
		//
		file_handle& operator =(FILE *fp);

		//
		// キャスト演算子
		//
		// 返り値：未オープン時はNULLが返る
		//
		// ハンドルをストリームファイルポインタにキャストした場合に
		// 格納しているポインタを返す。
		// (現存のファイルHANDLEを利用しているコードとの互換性を確保)
		//	
		operator FILE*()
		{
			return m_fp;
		};
	};
}
//
// Linux対応 ここまで
//

#ifdef __cplusplus
}
#endif
#endif /* W2M_BASE_H */

