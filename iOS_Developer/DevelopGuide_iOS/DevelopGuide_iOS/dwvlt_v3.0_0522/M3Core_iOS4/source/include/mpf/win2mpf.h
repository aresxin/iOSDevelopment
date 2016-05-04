//
//  WINDOWS.H
//
//  Updater : $Author: chikyu $
//  Version : $Revision: 1.6 $, $Date: 2009/12/22 08:11:31 $
//  Tag     : $Name:  $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
09.07.24 M.Chikyu

次のハンドルをWindowsMobileのために定義している。

HMETAFILE_XD
HENHMETAFILE_XD;
HWND_XD
HDC_XD;

HGDIOBJ_XD
HPEN_XD
HBRUSH_XD
HFONT_XD
HRGN_XD
HBITMAP_XD

このハンドルは"_XD"をとったLinuxの定義と同じものである。
全ソースファイルでハンドルは"_XD"をつけたものに変更しているので
Win32、Linuxでコンパイルするときは"typedef HDC_XD HDC"のような
定義を全てのファイルで読み込まれるファイルに定義すること。

WindowsMobileはハンドルを別名とすることでハンドルおよび
ハンドルを利用するオリジナル関数との衝突を回避している。

Win32ラッパーはオリジナル関数のオーバーライドとして定義する。

*/

// Windows特有の型やキーワードを定義する
#ifndef WINMOBILE_H
#define WINMOBILE_H

#if defined _PF_WIN32_ || _PF_WINCE_

#include <windows.h>

#endif // defined _PF_WIN32_ || _PF_WINCE_


//#include <dbgapi.h>
#include <stdlib.h>


#include "w2mpf_msvc.h"

// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

#define _WINDOWS_
#define MAX_PATH	_MAX_PATH

#include "w2mpf_base.h"

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_

#include "w2mpf_gdi.h"


// add 2011/03/03 by NEU for Android begin
//#if defined _PF_WINCE_ || defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_WINCE_ || defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

// シグニチャタイプ
#define ENHMETA_SIGNATURE	0

// 
#define POSTSCRIPT_PASSTHROUGH	0
#define PASSTHROUGH				1

// Escape
#define QUERYESCSUPPORT		10
#define	GETTECHNOLOGY		4

// abort()は存在しないのでexit(3)を代わりに使用する
#define abort() exit(3)

typedef struct _OSVERSIONINFOEX{ 
	DWORD dwOSVersionInfoSize; 
	DWORD dwMajorVersion; 
	DWORD dwMinorVersion; 
	DWORD dwBuildNumber; 
	DWORD dwPlatformId; 
	char  szCSDVersion[ 128 ];
	WORD  wServicePackMajor;
	WORD  wServicePackMinor;
	WORD  wSuiteMask;
	BYTE  wProductType;
	BYTE  wReserved;
} OSVERSIONINFOEX, *POSVERSIONINFOEX, *LPOSVERSIONINFOEX;

#endif // defined _PF_WINCE_ || defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_



// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end


#define __min(x,y)	min(x,y)


void ConvertWideStringToShort(wchar_t* wideStr);


// jpegmem.hの中で_P等を変数名に使っちゃっているので
// usr/include/ctype.hの定義をundefしておく 
#undef	_A		//_CTYPE_A		/* Alpha */
#undef	_C		//_CTYPE_C		/* Control */
#undef	_D		//_CTYPE_D		/* Digit */
#undef	_G		//_CTYPE_G		/* Graph */
#undef	_L		//_CTYPE_L		/* Lower */
#undef	_P		//_CTYPE_P		/* Punct */
#undef	_S		//_CTYPE_S		/* Space */
#undef	_U		//_CTYPE_U		/* Upper */
#undef	_X		//_CTYPE_X		/* X digit */
#undef	_B		//_CTYPE_B		/* Blank */
#undef	_R		//_CTYPE_R		/* Print */
#undef	_I		//_CTYPE_I		/* Ideogram */
#undef	_T		//_CTYPE_T		/* Special */
#undef	_Q		//_CTYPE_Q		/* Phonogram */

// min/maxマクロ対応（完全ではない）
using std::min;
using std::max;

// Windows定義・キーワード
#define _tcscpy strcpy
#define _T(x)	x

#define DECLARE_MESSAGE_MAP()
#define UNUSED_ALWAYS(x)
#define SUCCEEDED(x) (x==0)
#define AFX_MANAGE_STATE(x)
#define TRACE(x)
#define TRACE1(x,y)
#define AFX_EXT_CLASS
#define HRESULT_FROM_WIN32(x)	x

#define CLR_INVALID 0xffffffff

#define ERROR_ALREADY_EXISTS	183
#define WAIT_OBJECT_0			0x00000000L
#define PALETTERGB(r,g,b)		0
#define wsprintfA				wsprintf


#define APIENTRY
#define __cdecl
#define WINAPI
#define BEGIN_MESSAGE_MAP(x,y)
#define END_MESSAGE_MAP()

#define S_OK		1
#define S_FALSE		0

#define DMPAPER_A2			0
#define DMPAPER_A3			1
#define DMPAPER_A4			2
#define DMPAPER_A5			3
#define DMPAPER_B4			4
#define DMPAPER_B5			5
#define DMPAPER_LETTER		6
#define DMPAPER_LEGAL		7
#define DMPAPER_JAPANESE_POSTCARD 8
#define DMPAPER_FOLIO		9
#define DMPAPER_LEDGER		10
#define DMPAPER_9X11		11

#define CP_ACP				0
#define CP_OEMCP			1
#define CP_MACCP			2	
#define CP_THREAD_ACP		3
#define CP_SYMBOL			42
#define CP_UTF7				65000
#define CP_UTF8				65001

#define _MBC_LEAD		0
#define _MBC_TRAIL		1
#define _MBC_SINGLE		2
#define _MBC_ILLEGAL	3

#define LANG_JAPANESE	0
#define LANG_KOREAN		1
#define LANG_CHINESE	2
#define LANG_CHINESE	2

// 予期せぬエラー
#define E_UNEXPECTED	0x8000FFFF
// WIN32エラーコード
#define ERROR_NEGATIVE_SEEK	131

// Bitmap伸縮モード
#define BLACKONWHITE	0
#define	COLORONCOLOR	1
#define WHITEONBLACK	7

// 直線と曲線の識別子
#define PT_MOVETO		0
#define PT_LINETO		1
#define PT_BEZIERTO		2
#define PT_CLOSEFIGURE	99

// ファイルアクセスモード
#define DELETE	1

// 
#define LOGPIXELSX	0
#define LOGPIXELSY	1

// アロケート関連
#define LPTR 0

// レジストリ
#define HKEY_LOCAL_MACHINE	(void*)0xff
#define HKEY_CURRENT_USER	(void*)0xff

#define REG_OPTION_NON_VOLATILE	0x00000000L
#define KEY_WRITE				0x20006
#define KEY_READ				0x20019

#define ERROR_SUCCESS			0L
#define ERROR_MORE_DATA			234L

#define REG_NONE		0
#define REG_SZ			1
#define REG_DWORD		2
#define REG_BINARY		3
#define REG_EXPAND_SZ	4
#define REG_MULTI_SZ	5

#define CBM_INIT		0

// LCMAP
// 12.02.06 Bito - テキスト選択・検索対応
// 割り当てられた定数では判別不可だったので修正
//#define LCMAP_LOWERCASE 0
//#define LCMAP_HALFWIDTH 1
//#define LCMAP_KATAKANA	2
#define LCMAP_LOWERCASE           0x00000100  // lower case letters
#define LCMAP_KATAKANA            0x00200000  // map hiragana to katakana
#define LCMAP_HALFWIDTH           0x00400000  // map double byte to single byte

// The type of access to a file mapping object
#define FILE_MAP_READ	0
#define FILE_MAP_WRITE	1

// マッピングされたファイルに対する保護属性の設定をする定数の組み合わせ
#define	PAGE_READONLY	0
#define PAGE_READWRITE	1

// MAKELANGID プライマリ
#define	LANG_NEUTRAL	0
// MAKELANGID サブ
#define	SUBLANG_DEFAULT 0
// MAKELCID 
#define	SORT_DEFAULT	0

// 文字列比較用
// ロケール
#define LOCALE_SYSTEM_DEFAULT	0
#define LOCALE_USER_DEFAULT		1
// 比較オプション
#define NORM_IGNORECASE			1
// 結果
#define CSTR_EQUAL			0
#define CSTR_LESS_THAN		-1
#define CSTR_GREATER_THAN	1

// グラフィックモード
#define GM_COMPATIBLE		0
#define GM_ADVANCED			1

// タイムアウト（ミリ秒）
#define INFINITE			1000
// ユーザ名文字列長？
#define UNLEN				256

// wProductType
#define VER_NT_WORKSTATION	0x0000001		// updatepd.cpp#133

// システム色
#define CTLCOLOR_MSGBOX             0
#define CTLCOLOR_EDIT               1
#define CTLCOLOR_LISTBOX            2
#define CTLCOLOR_BTN                3
#define CTLCOLOR_DLG                4
#define CTLCOLOR_SCROLLBAR          5
#define CTLCOLOR_STATIC             6
#define CTLCOLOR_MAX                7
#define COLOR_SCROLLBAR             0
#define COLOR_BACKGROUND            1
#define COLOR_ACTIVECAPTION         2
#define COLOR_INACTIVECAPTION       3
#define COLOR_MENU                  4
#define COLOR_WINDOW                5
#define COLOR_WINDOWFRAME           6
#define COLOR_MENUTEXT              7
#define COLOR_WINDOWTEXT            8
#define COLOR_CAPTIONTEXT           9
#define COLOR_ACTIVEBORDER         10
#define COLOR_INACTIVEBORDER       11
#define COLOR_APPWORKSPACE         12
#define COLOR_HIGHLIGHT            13
#define COLOR_HIGHLIGHTTEXT        14
#define COLOR_BTNFACE              15
#define COLOR_BTNSHADOW            16
#define COLOR_GRAYTEXT             17
#define COLOR_BTNTEXT              18
#define COLOR_INACTIVECAPTIONTEXT  19
#define COLOR_BTNHIGHLIGHT         20
#define COLOR_3DDKSHADOW           21
#define COLOR_3DLIGHT              22
#define COLOR_INFOTEXT             23
#define COLOR_INFOBK               24
#define COLOR_DESKTOP           COLOR_BACKGROUND
#define COLOR_3DFACE            COLOR_BTNFACE
#define COLOR_3DSHADOW          COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT

// イベントアクセス権
#define SYNCHRONIZE					(0x00100000L)
#define STANDARD_RIGHTS_REQUIRED	(0x000F0000L)
#define EVENT_MODIFY_STATE			0x0002
#define EVENT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)

// MessageBox() フラグ値
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
#define MB_CANCELTRYCONTINUE        0x00000006L
#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L
#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND
#define MB_ICONINFORMATION          MB_ICONASTERISK
#define MB_ICONSTOP                 MB_ICONHAND
#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#define MB_DEFBUTTON4               0x00000300L
#define MB_APPLMODAL                0x00000000L
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L
#define MB_HELP                     0x00004000L // Help Button
#define MB_NOFOCUS                  0x00008000L
#define MB_SETFOREGROUND            0x00010000L
#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L
#define MB_TOPMOST                  0x00040000L
#define MB_RIGHT                    0x00080000L
#define MB_RTLREADING               0x00100000L

// ダイアログの返り値
#define IDOK		1
#define IDCANCEL	2
#define IDABORT		3
#define IDRETRY		4
#define IDIGNORE	5
#define IDYES		6
#define IDNO		7
#define IDCLOSE		8
#define IDHELP		9

// UI Message
#define afx_msg

#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define MN_GETHMENU                     0x01E1
#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#define WM_MOUSEWHEEL                   0x020A
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#define WM_MOUSELAST                    0x020D

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14
#define VK_KANA           0x15
#define VK_HANGEUL        0x15  // old name - should be here for compatibility
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19
#define VK_ESCAPE         0x1B
#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F
#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#define ON_BN_CLICKED(x,y)
#define ON_EN_CHANGE(x,y)

#define DWORD_PTR DWORD

// Windows型定義
typedef unsigned short	LANGID;
typedef char			TCHAR;

typedef void			*HCURSOR;
typedef void			*HMENU;

typedef unsigned short const	*LPCWSTR;
typedef LPCWSTR			LPCWTSTR;
typedef unsigned short	*LPWSTR;
typedef LPWSTR			LPWTSTR;
typedef LPCWSTR			LPCOLESTR;
typedef unsigned long	ULONG;
typedef DWORD			LCID;
typedef HANDLE			HLOCAL;
typedef unsigned short	*BSTR;
typedef unsigned int	*PUINT;

typedef void			*FARPROC;
typedef void			*GUID;
typedef void			*CObject;
typedef int				CFrameWnd;
typedef void			VARIANT;
typedef BOOL_XD*			PBOOL_XD;
typedef	unsigned int	REGSAM;
typedef HANDLE			HKEY;
typedef HANDLE			*PHKEY;
typedef const char		*PCSTR;
typedef unsigned int	*UINT_PTR;

typedef struct tagMSG {     // msg  
	HWND hwnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD time;
	POINT pt;
} MSG;

// ファイル関連
typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME;

typedef FILETIME *LPFILETIME;

typedef struct _WIN32_FIND_DATAW {
	DWORD			dwFileAttributes;
	FILETIME		ftCreationTime;
	FILETIME		ftLastAccessTime;
	FILETIME		ftLastWriteTime;
	DWORD			nFileSizeHigh;
	DWORD			nFileSizeLow;
	DWORD			dwReserved0;
	DWORD			dwReserved1;
	WCHAR			cFileName[256];
	WCHAR			cAlternateFileName[14];
} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, LPWIN32_FIND_DATAW;

typedef void* HPROPSHEETPAGE;

typedef struct _PROPSHEETHEADER 
	{
		DWORD dwSize;
		DWORD dwFlags;
		HWND_XD  hwndParent;
		HINSTANCE hInstance;
		/*
		 union {
		 HICON hIcon;
		 LPCTSTR pszIcon;
		 };
		 LPCTSTR pszCaption;
		 UINT nPages;
		 union {
		 UINT nStartPage;
		 LPCTSTR pStartPage;
		 };
		 union {
		 LPCPROPSHEETPAGE ppsp;
		 HPROPSHEETPAGE *phpage;
		 };
		 PFNPROPSHEETCALLBACK pfnCallback;
		 #if (_WIN32_IE >= 0x0400)
		 union {
		 HBITMAP_XD hbmWatermark;
		 LPCTSTR pszbmWatermark;
		 };
		 HPALETTE hplWatermark;
		 union {
		 HBITMAP_XD hbmHeader; 
		 LPCSTR pszbmHeader;
		 };
		 #endif
		 */
	} PROPSHEETHEADER, *LPPROPSHEETHEADER;

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

typedef struct tagNMHDR {
    HWND_XD hwndFrom;
    UINT_PTR idFrom;
    UINT code;
} NMHDR;

#define _ASSERT MPF_ASSERT 
void MPF_ASSERT(BOOL_XD booleanex);

//
// クラス定義
//

/*
class CString {
public:
	CString() {}
	CString(char* str) {}
	CString operator=(char* str) { return *this; }
	bool operator!=(const char* str) { return false; }
	bool operator!=(const CString& str) { return false; }
	bool operator==(const char* str) { return true; }
	bool operator==(const CString& str) { return true; }
	CString operator+(const CString* str) { return *this; }
	CString operator+(const char* str) { return *this; }
	CString operator+=(const CString* str) { return *this; }
	CString operator+=(const char* str) { return *this; }
	operator const char*() { return "dummy"; }
	void Empty() {}
	void LoadString(int a) {}
	int Find(unsigned short* str) { return 0; }
	int Find(char* str) { return 0; }
	CString Left(int pos) { return *this; }
	CString Mid(int pos) { return *this; }
	int GetLength() { return 0; }
};

class CStringW {
public:
	void Empty() {}
};

class CComBSTR {
public:
	CComBSTR(unsigned short* str) { m_str = str; }
	operator unsigned short*() { return m_str; }
	long ByteLength() { return wcslen(m_str); }
private:
	unsigned short *m_str;
};

class _bstr_t {
public:
	_bstr_t(unsigned short* str) { m_str = str; }
	operator const unsigned short*() const { return m_str; }
	unsigned int length ( ) const { return wcslen(m_str); }
private:
	unsigned short* m_str;
};

class CBitmap
{
public:
	BOOL_XD LoadBitmap(LPCTSTR lpszResourceName) { return true; }
	BOOL_XD LoadBitmap(UINT nIDResource) { return true; }
	HGDIOBJ_XD Detach() { return NULL; }
};

class CDataExchange {};

class CWnd
{
public:
	virtual BOOL_XD PreTranslateMessage(MSG* pMsg) { return true; }
	void SetWindowText(LPCTSTR lpszString) {}
	BOOL_XD UpdateData(BOOL_XD bSaveAndValidate = TRUE) { return true; }
	void GetDlgItem(int nID, HWND_XD* phWnd) const {}
	BOOL_XD EnableWindow(BOOL_XD bEnable = TRUE) { return true; }
	CWnd* SetFocus() { return (CWnd*)this; }
	
	CWnd* GetDlgItem(int nID) const { return (CWnd*)this; }
};

class CEdit : public CWnd
{
public:
	void SetSel(DWORD dwSelection, BOOL_XD bNoScroll = FALSE) {}
	void SetSel(int nStartChar, int nEndChar, BOOL_XD bNoScroll = FALSE) {}
};

class CButton : public CWnd
{
public:
	void SetCheck(int nCheck) {}
};

class CDialog : public CWnd
{
public:
	explicit CDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL) {}
	explicit CDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL) {}
	CDialog() {}
	int DoModal() { return 0; }
	void DoDataExchange(CDataExchange* pDX) {}
	void OnInitDialog() {}
	void EndDialog(int nResult) {}
	virtual void OnOK() {}
};
*/

#endif // defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_


//
//
// マルチプラットフォーム用ラッパー関数定義
//
//

/*
int wsprintfA(
			 LPSTR lpOut,
			 LPCSTR lpFmt,
			 ...
);
*/

/*
int wsprintfW(
			 LPWSTR lpOut,
			 LPCWSTR lpFmt,
			 ...
);
*/

HANDLE MPF_CreateFileA(
			LPCSTR lpFileName,                         // ファイル名
			DWORD dwDesiredAccess,                      // アクセスモード
			DWORD dwShareMode,             // 共有モード
			LPSECURITY_ATTRIBUTES lpSecurityAttributes, // セキュリティ記述子
			DWORD dwCreationDisposition,                // 作成方法
			DWORD dwFlagsAndAttributes,                 // ファイル属性
			HANDLE hTemplateFile           // テンプレートファイルのハンドル
);

HANDLE MPF_CreateFileW(
			LPCWSTR lpFileName,                         // ファイル名
			DWORD dwDesiredAccess,                      // アクセスモード
			DWORD dwShareMode,             // 共有モード
			LPSECURITY_ATTRIBUTES lpSecurityAttributes, // セキュリティ記述子
			DWORD dwCreationDisposition,                // 作成方法
			DWORD dwFlagsAndAttributes,                 // ファイル属性
			HANDLE hTemplateFile           // テンプレートファイルのハンドル
);

UINT MPF_RealizePalette(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);

BOOL_XD MPF_SetViewportOrgEx(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			int X,          // 新しいビューポート原点の x 座標
			int Y,          // 新しいビューポート原点の y 座標
			LPPOINT lpPoint // 以前のビューポート原点
);

int MPF_SetDIBits(
			HDC_XD hdc,                  // handle to DC
			HBITMAP_XD hbmp,             // handle to bitmap
			UINT uStartScan,          // starting scan line
			UINT cScanLines,          // number of scan lines
			CONST VOID *lpvBits,      // array of bitmap bits
			CONST BITMAPINFO *lpbmi,  // bitmap data
			UINT fuColorUse           // type of color indexes to use
);

int MPF_SetDIBitsToDevice(
			HDC_XD hdc,                 // デバイスコンテキストのハンドル
			int XDest,               // 転送先長方形の左上隅の x 座標
			int YDest,               // 転送先長方形の左上隅の y 座標
			DWORD dwWidth,           // 転送元長方形の幅
			DWORD dwHeight,          // 転送元長方形の高さ
			int XSrc,                // 転送元長方形の左下隅の x 座標
			int YSrc,                // 転送元長方形の左下隅の y 座標
			UINT uStartScan,         // 配列内の最初の走査行
			UINT cScanLines,         // 走査行の数
			CONST VOID *lpvBits,     // DIB ビットからなる配列
			CONST BITMAPINFO *lpbmi, // ビットマップ情報
			UINT fuColorUse          // RGB 値またはパレットインデックス
);

BOOL_XD MPF_UnmapViewOfFile(
			LPCVOID lpBaseAddress   // 開始アドレス
);

LPVOID MPF_MapViewOfFile(
			HANDLE hFileMappingObject,   // ファイルマッピングオブジェクトのハンドル
			DWORD dwDesiredAccess,       // アクセスモード
			DWORD dwFileOffsetHigh,      // オフセットの上位 DWORD
			DWORD dwFileOffsetLow,       // オフセットの下位 DWORD
			size_t dwNumberOfBytesToMap  // マップ対象のバイト数
);

HANDLE MPF_CreateFileMapping(HANDLE hFile,
							 LPSECURITY_ATTRIBUTES lpAttributes,
							 DWORD flProtect,
							 DWORD dwMaximumSizeHigh,
							 DWORD dwMaximumSizeLow);

int MPF_StretchDIBits(
			HDC_XD hdc,                      // デバイスコンテキストのハンドル
			int XDest,                    // コピー先長方形の左上隅の x 座標
			int YDest,                    // コピー先長方形の左上隅の y 座標
			int nDestWidth,               // コピー先長方形の幅
			int nDestHeight,              // コピー先長方形の高さ
			int XSrc,                     // コピー元長方形の左上隅の x 座標
			int YSrc,                     // コピー元長方形の左上隅の x 座標
			int nSrcWidth,                // コピー元長方形の幅
			int nSrcHeight,               // コピー元長方形の高さ
			CONST VOID *lpBits,           // ビットマップのビット
			CONST BITMAPINFO *lpBitsInfo, // ビットマップのデータ
			UINT iUsage,                  // データの種類
			DWORD dwRop                   // ラスタオペレーションコード
);

BOOL_XD MPF_PlayMetaFileRecord(
			HDC_XD hdc,                      // デバイスコンテキストのハンドル
			LPHANDLETABLE lpHandletable,  // メタファイルハンドルのテーブルへのポインタ
			LPMETARECORD lpMetaRecord,    // メタファイルレコードへのポインタ
			UINT nHandles                 // ハンドルの数
);

BOOL_XD MPF_PlayEnhMetaFile(
			HDC_XD hdc,            // handle to DC
			HENHMETAFILE_XD hemf,  // handle to an enhanced metafile
			CONST RECT *lpRect  // bounding rectangle
);


BOOL_XD MPF_PlayEnhMetaFileRecord(
			HDC_XD hdc,								// デバイスコンテキストのハンドル
			LPHANDLETABLE lpHandletable,			// メタファイルハンドルのテーブルへのポインタ
			const ENHMETARECORD *lpEnhMetaRecord,	// メタファイルレコードへのポインタ
			UINT nHandles							// ハンドルの数
);

void MPF_LPtoDP(
			HDC_XD hdc,
			LPPOINT lpPoints,
			int nCount = 1 
);

void MPF_DPtoLP(
			HDC_XD hdc,
			LPPOINT lpPoints,
			int nCount = 1 
);

BOOL_XD MPF_SetViewportExtEx(
			HDC_XD hdc,       // デバイスコンテキストのハンドル
			int nXExtent,  // 新しい水平ビューポート範囲
			int nYExtent,  // 新しい垂直ビューポート範囲
			LPSIZE lpSize  // 以前のビューポート範囲
);

BOOL_XD MPF_GetViewportExtEx(
			HDC_XD hdc,      // デバイスコンテキストのハンドル
			LPSIZE lpSize // ビューポートのサイズ
);

int MPF_SetMapMode(
			HDC_XD hdc,        // handle to device context
			int fnMapMode   // new mapping mode
);

DWORD MPF_GetFileAttributesW(
			LPCWSTR lpFileName   // ファイルまたはディレクトリの名前
);

BOOL_XD MPF_SetFileAttributesW(
			LPCWSTR lpFileName,
			DWORD dwFileAttributes
);

HANDLE MPF_FindFirstFileW(
			LPCWSTR lpFileName,               // ファイル名
			WIN32_FIND_DATAW* lpFindFileData  // データバッファ
);

BOOL_XD MPF_FindClose(
			HANDLE hFindFile   // ファイル検索ハンドル
);

int MPF_MultiByteToWideChar(
			UINT CodePage,         // コードページ
			DWORD dwFlags,         // 文字の種類を指定するフラグ
			LPCSTR lpMultiByteStr, // マップ元文字列のアドレス
			int cchMultiByte,      // マップ元文字列のバイト数
			LPWSTR lpWideCharStr,  // マップ先ワイド文字列を入れるバッファのアドレス
			int cchWideChar        // バッファのサイズ
);

HRESULT MPF_CopyFileA(
					  LPCSTR lpExistingFileName, // 既存のファイルの名前
					  LPCSTR lpNewFileName,      // 新しいファイルの名前
					  BOOL_XD bFailIfExists          // ファイルが存在する場合の動作
					  );

HRESULT MPF_CopyFileW(
					  LPCWSTR lpExistingFileName, // 既存のファイルの名前
					  LPCWSTR lpNewFileName,      // 新しいファイルの名前
					  BOOL_XD bFailIfExists          // ファイルが存在する場合の動作
					  );

BOOL_XD MPF_DeleteFileA(LPCSTR fileName);

BOOL_XD MPF_DeleteFileW(LPCWSTR fileName);

BOOL_XD MPF_CreateDirectoryA(LPCSTR lpPathName);

BOOL_XD MPF_RemoveDirectoryA(LPCSTR lpPathName);

void MPF_splitpath(
			const char *path,
			char *drive,
			char *dir,
			char *fname,
			char *ext
);


void MPF_wsplitpath(
			LPCWSTR path,
			LPWSTR drive,
			LPWSTR dir,
			LPWSTR fname,
			LPWSTR ext 
);

int MPF_IntersectClipRect(
			HDC_XD hdc,         // デバイスコンテキストのハンドル
			int nLeftRect,   // 長方形の左上隅の x 座標
			int nTopRect,    // 長方形の左上隅の y 座標
			int nRightRect,  // 長方形の右下隅の x 座標
			int nBottomRect  // 長方形の右下隅の y 座標
);

int MPF_WideCharToMultiByte(
			UINT CodePage,         // コードページ
			DWORD dwFlags,         // 処理速度とマッピング方法を決定するフラグ
			LPCWSTR lpWideCharStr, // ワイド文字列のアドレス
			int cchWideChar,       // ワイド文字列の文字数
			LPSTR lpMultiByteStr,  // 新しい文字列を受け取るバッファのアドレス
			int cchMultiByte,      // 新しい文字列を受け取るバッファのサイズ
			LPCSTR lpDefaultChar,  // マップできない文字の既定値のアドレス
			BOOL_XD *lpUsedDefaultChar   // 既定の文字を使ったときにセットするフラグのアドレス
);

DWORD MPF_GetTempPathA(
			DWORD nBufferLength,
			LPSTR path
);

DWORD MPF_GetTempPathW(
			DWORD nBufferLength,
			LPWSTR path
);

UINT MPF_GetTempFileNameA(LPCSTR lpPathName,      // ディレクトリ名
						  LPCSTR lpPrefixString,  // ファイル名の接頭辞
						  UINT uUnique,           // 整数
						  LPSTR path);

UINT MPF_GetTempFileNameW(LPCWSTR lpPathName,      // ディレクトリ名
						  LPCWSTR lpPrefixString,  // ファイル名の接頭辞
						  UINT uUnique,            // 整数
						  LPWSTR path);

int MPF_ExcludeClipRect(
			HDC_XD hdc,         // デバイスコンテキストのハンドル
			int nLeftRect,   // 長方形の左上隅の x 座標
			int nTopRect,    // 長方形の左上隅の y 座標
			int nRightRect,  // 長方形の右下隅の x 座標
			int nBottomRect  // 長方形の右下隅の y 座標
);

BOOL_XD MPF_ScaleViewportExtEx(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			int Xnum,       // 水平方向の乗数
			int Xdenom,     // 水平方向の除数
			int Ynum,       // 垂直方向の乗数
			int Ydenom,     // 垂直方向の除数
			LPSIZE lpSize   // 以前のビューポート範囲
);

unsigned int MPF_getmbcp();

BOOL_XD MPF_PlayMetaFile(
			HDC_XD hdc,        // handle to DC
			HMETAFILE_XD hmf   // handle to metafile
);

int MPF_MessageBox(
			HWND hWnd,          // オーナーウィンドウのハンドル
			LPCSTR lpText,     // メッセージボックス内のテキスト
			LPCSTR lpCaption,  // メッセージボックスのタイトル
			UINT uType          // メッセージボックスのスタイル
);

FILE* MPF_wfopen( 
			LPCWSTR filename,
			LPCWSTR mode 
);

int MPF_wremove(
			LPCWSTR path 
);

int MPF_wrename(
			LPCWSTR oldname,
			LPCWSTR newname 
);

void* MPF_Alloc(size_t dwBytes);

void MPF_Free(void* hMem);

size_t MPF_AllocSize(void *hMem);

BOOL_XD MPF_FAILED(HRESULT resultobj);

BOOL_XD MPF_GetFileTime(
			HANDLE hFile,                 // ファイルのハンドル
			LPFILETIME lpCreationTime,    // 作成日時
			LPFILETIME lpLastAccessTime,  // 最終アクセス日時
			LPFILETIME lpLastWriteTime    // 最終更新日時
);

BOOL_XD MPF_SetFileTime(
			HANDLE hFile,                     // ファイルのハンドル
			CONST FILETIME *lpCreationTime,   // 作成日時
			CONST FILETIME *lpLastAccessTime, // 最終アクセス日時
			CONST FILETIME *lpLastWriteTime   // 最終更新日時
);

void MPF_GetSystemTime(
			LPSYSTEMTIME lpSystemTime
);

BOOL_XD MPF_SystemTimeToFileTime(
			const SYSTEMTIME *lpSystemTime,
			LPFILETIME lpFileTime
);


// [XDWAPI for Spotlight Importer V70 2008.02.14 by akiyoshi] >>>
// Wide文字関数群を独自実装

LPWSTR MPF_wcsncpy(
	LPWSTR	strDest,
	LPCWSTR	strSource,
	size_t count
);

LPWSTR MPF_wcscpy(
	LPWSTR	strDest,
	LPCWSTR	strSource
);

LPWSTR MPF_wcscat(
	LPWSTR	strDest,
	LPCWSTR	strSource
);

int MPF_wcscmp(
	LPCWSTR	string1,
	LPCWSTR	string2
);

int MPF_wcsncmp(
	LPCWSTR	string1,
	LPCWSTR	string2,
	size_t count
);

size_t MPF_wcslen(
	LPCWSTR	string
);

//
//
// WinMobile分割描画対応
// 09/10/06 M.Chikyu
//
//

// 分割描画初回呼び出し
void* MPF_PlayMetaFileEx(
			HDC_XD			hdc,
			HMETAFILE_XD	hwmf,
			UINT			imgCount,	// イメージ分割ライン数
			UINT			recCount
);	// レコード分割数

// 分割描画2回め以降呼び出し
void* MPF_ContMetaFileEx(
			void* hParser,
			HDC_XD hdc
);

// 分割描画中止
void MPF_StopMetaFileEx(void* hParser);

// 分割描画初回呼び出し
void* MPF_PlayEnhMetaFileEx(
			HDC_XD			hdc,
			HENHMETAFILE_XD	hemf,
			const RECT*		rect,
			UINT			imgCount,	// イメージ分割ライン数
			UINT			recCount	// レコード分割数
);

// 分割描画2回め以降呼び出し
void* MPF_ContEnhMetaFileEx(
			void* hParser, HDC_XD hdc
);

// 分割描画中止
void MPF_StopEnhMetaFileEx(void* hParser);

BOOL_XD MPF_MoveFileW(
			LPCWSTR lpExistingFileName, // ファイル名
			LPCWSTR lpNewFileName       // 新しいファイル名
);

//
//
// WinMobile分割描画対応 ここまで
//
//



// add 2011/03/03 by NEU for Android begin
//#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_
#if defined _PF_LINUX_ || defined _PF_IOS_ || defined _PF_OSX_ || defined _PF_ANDROID_
// add 2011/03/03 by NEU for Android end

//
// ファイルマッピング対応
// 09/02/12 Masafumi Chikyu
//

// 新規コード

//
// HANDLEに格納するHANDLEオブジェクトのクラスを定義する
//
// fm_handle：ファイルマッピングに必要な情報を格納する
//

namespace WIN_HANDLE
{
	///////////////////////////////////////	
	//
	// ファイルマッピングハンドルクラス
	//
	///////////////////////////////////////
	class fm_handle: public base_handle
	{
	protected:
		void	*m_addr;			// マッピングアドレス
		DWORD	m_flProtect;		// ページ保護モード
		int		m_fd;				// ファイル記述子
		int		m_accessMode;		// アクセスモード
		off_t	m_mapSize;			// マッピングサイズ
		
		//
		// 変数の初期化
		//
		void initVal();
				
	public:

		//
		// コンストラクタ
		//
		// AR fx_18522 modified begin
		// fm_handle(){};
		fm_handle() { initVal(); }
		// AR fx_18522 modified end
		
		//
		// デストラクタ
		//
		virtual ~fm_handle(){};
		
		//
		// ファイルマッピングオブジェクトの作成
		//
		// fp：ストリームファイルポインタ
		// fpProtect：ページ保護モード(CreateFileMapping互換)
		// MaxSizeHigh, MaxSizeLow：ファイル最大サイズ(上位、下位)
		// 
		// 返り値：成功失敗をboolで返す。
		//
		// エラー：成功ならtrue、失敗ならfalse。
		//
		// ページ保護モードはPAGE_READONLYまたはPAGE_READWRITEのみサポートします。
		// PAGE_READONLYの場合はマッピングサイズの指定を無視します。
		// fpへのINVALID_HANDLE_VALUEの指定はサポートしません。
		// ファイルサイズに32ビットしか指定できない場合にMaxSizeHighに0以外を指定するとエラーです。
		// PAGE_READWRITEを指定して、マッピングサイズにファイルサイズより大きいサイズを指定すると
		// 指定サイズまでファイルサイズを拡大します。
		//
		bool createFileMapping(FILE *fp,
								DWORD flProtect,
								DWORD MaxSizeHigh,
								DWORD MaxSizeLow);

		//
		// ファイルマッピングの作成
		//
		// mode：アクセスモード(MapViewOfFile互換)
		// offsetHigh, offsetLow：ファイル先頭からのオフセット
		// 
		// 返り値：ファイルマッピング開始アドレス
		//
		// エラー：返り値がNULL
		//
		// アクセスモードはFILE_MAP_READおよびFILE_MAP_WRITEのみサポートします。
		// 実装上はファイル全体をマッピングし、先頭アドレスにオフセットを加えたアドレスを返します。
		// マッピングに成功した場合、オブジェクトのハンドルはオープン状態にフラグを設定します。
		//
		void* mapViewOfFile(DWORD accessMode,
							 DWORD offsetHigh,
							 DWORD offsetLow);

		//
		// ハンドルのクローズ処理
		//
		// ファイルマッピングを解放し、変数を初期化する。
		//
		bool closeHandle();
	};
}

//
// ファイルマッピング対応 ここまで
//

#endif


//
//
// 以降の関数は現在未使用のためラッパーを作成しない
//
//

/*
int _mbsbtype(
			const unsigned char *mbstr,
			size_t count
);
*/

/*
LONG RegCreateKeyEx(
			HKEY hKey,
			LPCTSTR lpSubKey,
			DWORD Reserved,
			LPTSTR lpClass,
			DWORD dwOptions,
			DWORD samDesired,
			SECURITY_ATTRIBUTES* lpSecurityAttributes,
			HKEY* phkResult,
			LPDWORD lpdwDisposition
);
*/

/*
LONG RegQueryValueEx(
			HKEY hKey,            // キーのハンドル
			LPCTSTR lpValueName,  // レジストリエントリ名
			LPDWORD lpReserved,   // 予約済み
			LPDWORD lpType,       // データ型が格納されるバッファ
			LPBYTE lpData,        // データが格納されるバッファ
			LPDWORD lpcbData      // データバッファのサイズ
);
*/

/*
LONG RegCloseKey(
			HKEY hKey   // 閉じるべきキーのハンドル
);
*/

/*
LONG RegSetValueEx(
			HKEY hKey,           // 親キーのハンドル
			LPCTSTR lpValueName, // レジストリエントリ名
			DWORD Reserved,      // 予約済み
			DWORD dwType,        // レジストリエントリのデータ型
			const BYTE *lpData,  // レジストリエントリのデータ
			DWORD cbData         // レジストリエントリのデータのサイズ
);
*/

/*
LONG RegOpenKeyEx(
			HKEY hKey,         // 開いている親キーのハンドル
			LPCTSTR lpSubKey,  // 開くべきサブキーの名前
			DWORD ulOptions,   // 予約済み
			DWORD samDesired,  // セキュリティアクセスマスク
			HKEY* phkResult    // 開くことに成功したサブキーのハンドル
);
*/

/*
BOOL_XD MPF_GetViewportOrgEx(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			LPPOINT lpPoint // ビューポートの原点
);
*/

/*
int MPF_GetDIBits(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			HBITMAP_XD hbmp,      // ビットマップのハンドル
			UINT uStartScan,   // 取得対象の最初の走査行
			UINT cScanLines,   // 取得対象の走査行の数
			LPVOID lpvBits,    // ビットマップのビットからなる配列
			LPBITMAPINFO lpbi, // ビットマップデータのバッファ
			UINT uUsage        // RGB とパレットインデックスのどちらか
);
*/

/*
HBITMAP_XD CreateDIBitmap(
			HDC_XD hdc,                        // handle to DC
			const BITMAPINFOHEADER *lpbmih, // bitmap data
			DWORD fdwInit,                  // initialization option
			const VOID *lpbInit,            // initialization data
			const BITMAPINFO *lpbmi,        // color-format data
			UINT fuUsage               // color-data usage
);
*/

/*
HBITMAP_XD CreateDIBSection(
			HDC_XD hdc,                 // handle to DC
			CONST BITMAPINFO *pbmi,  // bitmap data
			UINT iUsage,             // data type indicator
			VOID **ppvBits,          // bit values
			HANDLE hSection,         // handle to file mapping object
			DWORD dwOffset     // offset to bitmap bit values
);
*/

/*
int LCMapStringW(
			LCID Locale,       // ロケール識別子
			DWORD dwMapFlags,  // マップ変換の種類
			const WCHAR* lpSrcStr,  // マップ元文字列のアドレス
			int cchSrc,        // マップ元文字列の文字数
			WCHAR* lpDestStr,  // マップ先バッファのアドレス
			int cchDest        // マップ先バッファのサイズ
);
*/

/*
int GetClipBox(
			HDC_XD hdc,      // デバイスコンテキストのハンドル
			LPRECT lprc   // 長方形
);
*/

/*
int SetStretchBltMode(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			int iStretchMode   // ビットマップの伸縮モード
);
*/

/*
int SetBkMode(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			int nBkMode
);
*/

/*
int GetBkMode(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
int SetROP2(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			int nDrawMode
);
*/

/*
BYTE GetRValue(
			DWORD rgb  // RGB value
);

BYTE GetGValue(
			DWORD rgb     // RGB value
);

BYTE GetBValue(
			DWORD rgb     // RGB value
);
*/

/*
HGDIOBJ_XD GetCurrentObject(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			UINT uObjectType   // オブジェクトのタイプ
);
*/

/*
int GetObject(
			HGDIOBJ_XD hgdiobj,  // グラフィックオブジェクトのハンドル
			int cbBuffer,     // オブジェクト情報を格納するバッファのサイズ
			LPVOID lpvObject  // オブジェクト情報を格納するバッファ
);
*/

/*
UINT GetPaletteEntries(
			HPALETTE hpal,
			UINT iStart,
			UINT cEntries,
			LPPALETTEENTRY pPalEntries
);
*/

/*
COLORREF SetTextColor(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			COLORREF crColor   // テキストの色
);
*/



/*
HBRUSH_XD CreateBrushIndirect(
			const LOGBRUSH* lpLogBrush 
);
*/

/*
int ExtEscape(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			int nEscape,        // エスケープ機能
			int cbInput,        // 入力構造体のサイズ
			LPCSTR lpszInData,  // 入力構造体
			int cbOutput,       // 出力構造体のサイズ
			LPSTR lpszOutData   // 出力構造体
);
*/

/*
int Escape(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			int nEscape,        // エスケープ機能
			int cbInput,        // 入力構造体のサイズ
			LPCSTR lpszInData,  // 入力構造体
			LPSTR lpszOutData   // 出力構造体
);
*/

/*
int StretchBlt(
			HDC_XD hdc,
			int x,
			int y,
			int nWidth,
			int nHeight,
			HDC_XD pSrcDC,
			int xSrc,
			int ySrc,
			int nSrcWidth,
			int nSrcHeight,
			DWORD dwRop 
);
*/

/*
BOOL_XD PatBlt(
			HDC_XD hdc,      // デバイスコンテキストのハンドル
			int nXLeft,   // 長方形の左上隅の x 座標
			int nYLeft,   // 長方形の左上隅の y 座標
			int nWidth,   // 長方形の幅
			int nHeight,  // 長方形の高さ
			DWORD dwRop   // ラスタオペレーションコード
);
*/

/*
HDC_XD CreateEnhMetaFile(
			HDC_XD hdcRef,            // 参照 DC のハンドル
			LPCTSTR lpFilename,    // ファイル名
			const RECT *lpRect,    // 境界長方形
			LPCTSTR lpDescription  // 説明文字列
);
*/

/*
UINT GetWinMetaFileBits(
			HENHMETAFILE_XD hemf, // 拡張形式メタファイルのハンドル
			UINT cbBuffer,     // バッファのサイズ
			LPBYTE lpbBuffer,  // バッファへのポインタ
			INT fnMapMode,     // マッピングモード
			HDC_XD hdcRef         // 基準デバイスコンテキストのハンドル
);
*/

/*
UINT GetMetaFileBitsEx(
			HMETAFILE_XD hmf,  // メタファイルのハンドル
			UINT nSize,     // メタファイルのサイズ（バイト数）
			LPVOID lpvData  // メタファイルのデータへのポインタ
);
*/

/*
UINT GetEnhMetaFileBits(
			HENHMETAFILE_XD hemf, // メタファイルのハンドル
			UINT cbBuffer,     // バッファのサイズ（バイト数）
			LPBYTE lpbBuffer   // データバッファへのポインタ
);
*/

/*
HENHMETAFILE_XD GetEnhMetaFile(
			LPCTSTR lpszMetaFile   // ファイル名
);
*/

/*
HMETAFILE_XD MPF_CloseMetaFile(
			HDC_XD hdc   // メタファイルデバイスコンテキストのハンドル
);
*/

/*
BOOL_XD BitBlt(
			HDC_XD hdcDest, // コピー先デバイスコンテキストのハンドル
			int nXDest,  // コピー先長方形の左上隅の x 座標
			int nYDest,  // コピー先長方形の左上隅の y 座標
			int nWidth,  // コピー先長方形の幅
			int nHeight, // コピー先長方形の高さ
			HDC_XD hdcSrc,  // コピー元デバイスコンテキストのハンドル
			int nXSrc,   // コピー元長方形の左上隅の x 座標
			int nYSrc,   // コピー元長方形の左上隅の y 座標
			DWORD dwRop  // ラスタオペレーションコード
);
*/

/*
HENHMETAFILE_XD CloseEnhMetaFile(HDC_XD hDC);
*/

/*
BOOL_XD FreeLibrary(
			HMODULE hModule   // DLL モジュールのハンドル
);
*/

/*
FARPROC GetProcAddress(
			HMODULE hModule,    // DLL モジュールのハンドル
			LPCSTR lpProcName   // 関数名
);
*/

/*
HANDLE GetCurrentProcess();
*/

/*
COLORREF SetBkColor(
			HDC_XD hdc,
			COLORREF crColor
);
*/

/*
COLORREF GetBkColor(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
COLORREF GetTextColor(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
BOOL_XD SetRect(
			LPRECT lprc, // 長方形
			int xLeft,   // 左辺
			int yTop,    // 上辺
			int xRight,  // 右辺
			int yBottom  // 下辺
);
*/

/*
BOOL_XD PolyBezier(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			const POINT *lppt,  // 端点と制御点
			DWORD cPoints       // 端点と制御点の合計数
);
*/

/*
BOOL_XD Polygon(
			HDC_XD hdc,                // デバイスコンテキストのハンドル
			const POINT *lpPoints,  // ポリゴンの頂点
			int nCount              // ポリゴンの頂点の数
);
*/

/*
BOOL_XD PolygonDummy(
			HDC_XD hdc,                // デバイスコンテキストのハンドル
			const POINT *lpPoints,  // ポリゴンの頂点
			int nCount              // ポリゴンの頂点の数
);
*/

/*
BOOL_XD Polyline(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			const POINT *lppt,  // 端点からなる配列
			int cPoints         // 配列内の点の数
);
*/

/*
BOOL_XD PolyBezierTo(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			const POINT *lppt,  // 端点と制御点
			DWORD cCount        // 端点と制御点の合計数
);
*/

/*
BOOL_XD PolylineTo(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			const POINT *lppt,  // 複数の点からなる配列
			DWORD cCount        // 配列内の点の数
);
*/

/*
BOOL_XD StrokePath(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
BOOL_XD StrokeAndFillPath(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
BOOL_XD MoveToEx(
			HDC_XD hdc,          // デバイスコンテキストのハンドル
			int X,            // 新しい現在の位置の x 座標
			int Y,            // 新しい現在の位置の y 座標
			LPPOINT lpPoint   // それまでの現在の位置
);
*/

/*
BOOL_XD CloseFigure(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

BOOL_XD MPF_GetCurrentPositionEx(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			LPPOINT lpPoint // 現在の位置
);

/*
BOOL_XD GetWorldTransform(
			HDC_XD hdc,  // デバイスコンテキストのハンドル
			LPXFORM lpXform	// 座標変換を受け取る構造体へのポインタ
);
*/

/*
int GetROP2(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
int BeginPath(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
int EndPath(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
BOOL_XD SelectClipPath(
			HDC_XD hdc,    // デバイスコンテキストのハンドル
			int iMode   // クリッピングモード
);
*/

/*
HRGN_XD CreateRectRgn(
			long nLeftRect,   // 左上隅の x 座標
			long nTopRect,    // 左上隅の y 座標
			long nRightRect,  // 右下隅の x 座標
			long nBottomRect  // 右下隅の y 座標
);
*/

/*
int SetGraphicsMode(
			HDC_XD hdc,    // デバイスコンテキストのハンドル
			int iMode   // グラフィックスモード
);
*/

/*
BOOL_XD SetWorldTransform(
			HDC_XD hdc,               // デバイスコンテキストのハンドル
			CONST XFORM *lpXform   // 変換データのアドレス
);
*/

/*
BOOL_XD GetWindowOrgEx(
			HDC_XD hdc,         // デバイスコンテキストのハンドル
			LPPOINT lpPoint  // ウィンドウ原点
);
*/

/*
BOOL_XD GetWindowExtEx(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			LPSIZE lpSize   // ウィンドウの範囲
);
*/

/*
int GetMapMode(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
int CombineRgn(
			HRGN_XD hrgnDest,      // 結合先リージョンのハンドル
			HRGN_XD hrgnSrc1,      // 結合元リージョンのハンドル
			HRGN_XD hrgnSrc2,      // 結合元リージョンのハンドル
			int fnCombineMode   // リージョンの結合モード
);
*/

/*
int SetPolyFillMode(
			HDC_XD hdc,            // デバイスコンテキストのハンドル
			int iPolyFillMode   // 多角形塗りつぶしモード
);
*/

/*
int GetPolyFillMode(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);
*/

/*
HRGN_XD CreatePolygonRgn(
			const POINT *lppt,  // 複数の点からなる配列
			int cPoints,        // 配列内の点の数
			int fnPolyFillMode  // 多角形塗りつぶしモード
);
*/

/*
HRGN_XD CreateRoundRectRgn(
			long nLeftRect,      // 左上隅の x 座標
			long nTopRect,       // 左上隅の y 座標
			long nRightRect,     // 右下隅の x 座標
			long nBottomRect,    // 右下隅の y 座標
			int nWidthEllipse,  // 楕円の高さ
			int nHeightEllipse  // 楕円の幅
);
*/

/*
HRGN_XD CreateEllipticRgn(
			long nLeftRect,   // 長方形の左上隅の x 座標
			long nTopRect,    // 長方形の左上隅の y 座標
			long nRightRect,  // 長方形の右下隅の x 座標
			long nBottomRect  // 長方形の右下隅の y 座標
);
*/

/*
int SelectClipRgn(
			HDC_XD hdc,    // デバイスコンテキストのハンドル
			HRGN_XD hrgn   // リージョンのハンドル
);
*/

/*
int GetClipRgn(
			HDC_XD hdc,           // デバイスコンテキストのハンドル
			HRGN_XD hrgn          // リージョンのハンドル
);
*/

/*
int ExtSelectClipRgn(
			HDC_XD hdc,          // デバイスコンテキストのハンドル
			HRGN_XD hrgn,        // リージョンのハンドル
			int fnMode        // リージョン選択モード
);
*/

/*
DWORD GetRegionData(
			HRGN_XD hRgn,            // リージョンのハンドル
			DWORD dwCount,        // リージョンデータバッファのサイズ
			LPRGNDATA lpRgnData   // リージョンデータバッファ
);
*/

/*
BOOL_XD LineTo(
			HDC_XD hdc,    // device context handle
			int nXEnd,  // x-coordinate of ending point
			int nYEnd   // y-coordinate of ending point
);
*/

/*
BOOL_XD FillPath(HDC_XD hDC);
*/

/*
HRGN_XD CreateRectRgnIndirect(
			RECT *lpRect 
);
*/

/*
int MulDiv(
			int nNumber,       // 符号付き 32 ビット被乗数
			int nNumerator,    // 符号付き 32 ビット乗数
			int nDenominator   // 符号付き 32 ビット除数
);
*/

/*
WORD MAKELANGID(
			USHORT usPrimaryLanguage,  
			USHORT usSubLanguage       
);
*/

/*
DWORD MAKELCID(
			WORD wLanguageID,  
			WORD wSortID
);
*/

/*
int CompareString(
			LCID    Locale,
			DWORD   dwCmpFlags,
			LPCTSTR lpString1,
			int     cchCount1,
			LPCTSTR lpString2,
			int     cchCount2
);
*/

/*
HMODULE LoadLibrary(LPCTSTR lpFileName);
*/

/*
long MoveFile(
			const char* lpExistingFileName, // ファイル名
			const char* lpNewFileName       // 新しいファイル名
);
*/

/*
UINT GetPrivateProfileInt(
			LPCTSTR lpAppName,  // セクション名
			LPCTSTR lpKeyName,  // キー名
			INT nDefault,       // キー名が見つからなかった場合に返すべき値
			LPCTSTR lpFileName  // .ini ファイルの名前
);
*/

/*
UINT GetPrivateProfileIntW(
			LPCWSTR lpAppName,  // セクション名
			LPCWSTR lpKeyName,  // キー名
			INT nDefault,       // キー名が見つからなかった場合に返すべき値
			LPCWSTR lpFileName  // .ini ファイルの名前
);
*/

/*
ULONGLONG UInt32x32To64(
			DWORD Multiplier,    // 最初の符号なし 32 ビット整数
			DWORD Multiplicand   // 2 番目の符号なし 32 ビット整数
);
*/

/*
HBRUSH_XD CreateSolidBrush(
			COLORREF crColor 
);

HPEN_XD CreatePen(
			int nPenStyle,
			int nWidth,
			COLORREF crColor 
);

HPEN_XD ExtCreatePen(
			DWORD dwPenStyle,      // pen style
			DWORD dwWidth,         // pen width
			CONST LOGBRUSH *lplb,  // brush attributes
			DWORD dwStyleCount,    // length of custom style array
			CONST DWORD *lpStyle   // custom style array
);
*/

/*
int FillRect(
			HDC_XD hDC,           // デバイスコンテキストのハンドル
			CONST RECT *lprc,  // 長方形
			HBRUSH_XD hbr         // ブラシのハンドル
);
*/

/*
BOOL_XD InflateRect(
			LPRECT lprc,  // 長方形
			int dx,       // 幅を調整する量
			int dy        // 高さを調整する量
);
*/

/*
BOOL_XD CreateDirectory(
			LPCTSTR lpPathName,
			LPSECURITY_ATTRIBUTES lpSecurityAttributes
);

BOOL_XD RemoveDirectory(
			LPCTSTR lpPathName   // ディレクトリ名
);
*/

/*
int lstrcmp(
			LPCTSTR lpString1,  // 最初の文字列
			LPCTSTR lpString2   // 2 番目の文字列
);

LPTSTR lstrcat(
			LPTSTR lpString1,  // 最初の文字列
			LPCTSTR lpString2  // 2 番目の文字列
);
*/

/*
LPTSTR lstrcpyn(
			LPTSTR lpString1,  // コピー先のバッファ
			LPCTSTR lpString2, // コピー元の文字列
			int iMaxLength     // コピーするべき文字の数
);
*/

/*
LPSTR lstrcpynA(
			LPSTR lpString1,  // コピー先のバッファ
			LPCSTR lpString2, // コピー元の文字列
			int iMaxLength    // コピーするべき文字の数
);
*/

BOOL_XD MPF_IntersectRect(
			LPRECT lprcDst,        // 交差部分が格納されるバッファ
			CONST RECT *lprcSrc1,  // 最初の長方形
			CONST RECT *lprcSrc2   // 2 番目の長方形
);

/*
#undef GetTextExtentPoint32
BOOL_XD GetTextExtentPoint32(
			HDC_XD hdc,           // handle to DC
			LPCTSTR lpString,  // text string
			int c,      // characters in string
			LPSIZE lpSize      // string size
);
*/

/*
#undef GetTextExtentPoint32W
BOOL_XD GetTextExtentPoint32W(
			HDC_XD hdc,           // handle to DC
			LPWSTR lpString,  // text string
			int c,      // characters in string
			LPSIZE lpSize      // string size
);
*/

UINT MPF_GetTextAlign(
			HDC_XD hdc   // デバイスコンテキストのハンドル
);

BOOL_XD MPF_GetTextMetrics(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			TEXTMETRIC *lptm   // フォント情報を格納する構造体
);

/*
BOOL_XD GetTextMetricsA(
			HDC_XD hdc,        // デバイスコンテキストのハンドル
			TEXTMETRICA *lptm   // フォント情報を格納する構造体
);
*/

/*
BOOL_XD ExtTextOut(
			HDC_XD hdc,          // handle to DC
			int X,            // x-coordinate of reference point
			int Y,            // y-coordinate of reference point
			UINT fuOptions,   // text-output options
			CONST RECT* lprc, // optional dimensions
			LPCTSTR lpString, // string
			UINT cbCount,     // number of characters in string
			CONST INT* lpDx   // array of spacing values
);
*/

/*
BOOL_XD ExtTextOutA(
			HDC_XD hdc,          // handle to DC
			int X,            // x-coordinate of reference point
			int Y,            // y-coordinate of reference point
			UINT fuOptions,   // text-output options
			CONST RECT* lprc, // optional dimensions
			LPCSTR lpString, // string
			UINT cbCount,     // number of characters in string
			CONST INT* lpDx   // array of spacing values
);
*/

/*
HPALETTE CreatePalette(
			LPLOGPALETTE lpLogPalette 
);
*/

/*
HLOCAL LocalFree(
			HLOCAL hMem
);

HGLOBAL GlobalReAlloc(
			HGLOBAL hMem,   // グローバルメモリオブジェクトのハンドル
			size_t dwBytes, // 新しいブロックサイズ
			UINT uFlags     // オブジェクトを再割り当てする方法
);

HLOCAL LocalAlloc(
			UINT uFlags,
			size_t uBytes
);

VOID FillMemory (
			VOID *Destination,  // メモリブロック
			size_t Length,      // メモリブロックのサイズ
			BYTE Fill           // 書き込みたい値
);

VOID GlobalMemoryStatus(
			LPMEMORYSTATUS lpBuffer   // メモリステータスの構造体
);

DWORD GlobalSize(
			HGLOBAL hMem   // グローバルメモリオブジェクトのハンドル
);
*/

/*
WORD PRIMARYLANGID( 
			LANGID lgid 
);
*/

/*
BOOL_XD ReleaseMutex(
			HANDLE hMutex   // ミューテックスオブジェクトのハンドル
);
*/

/*
BOOL_XD GetUserName(
			LPTSTR lpBuffer,  // 名前バッファ
			LPDWORD nSize     // 名前バッファのサイズ
);
*/

/*
char *_strrev(
			char *string 
);

int _stricmp (
			const char *string1,
			const char *string2
);

int strnicmp(
			const char *string1,
			const char *string2,
			size_t count 
);
*/

/*
LANGID GetUserDefaultLangID();
*/

/*
void strcpy_s(
			char *strDestination,
			size_t numberOfElements,
			const char *strSource 
);

long strncpy_s(
			char *strDest,
			size_t numberOfElements,
			const char *strSource,
			size_t count
);

long strcat_s(
			char *strDestination,
			size_t numberOfElements,
			const char *strSource 
);

unsigned short* wcscpy(
			unsigned short * string1,
			const unsigned short * string2
);

long wcsncpy_s(
			unsigned short *strDest,
			size_t numberOfElements,
			const unsigned short *strSource,
			size_t count 
);
*/

/*
char* _tempnam(
			const char *dir,
			const char *prefix 
);
*/

/*
int CompareStringW(      
			LCID Locale,
			DWORD dwCmpFlags,
			const unsigned short* lpString1,
			int cchCount1,
			const unsigned short* lpString2,
			int cchCount2
);
*/

/*
void SysFreeString(  
			BSTR  bstr
);
*/

/*
void* CoTaskMemAlloc(
			unsigned long cb
);
*/

/*
void CoTaskMemFree(
			void * pv
);
*/

/*
class CWinApp {
public:
	static BOOL_XD InitInstance() { return false; };
	static int ExitInstance() { return 0; };
};

class CPropertyPage {
public:
	HWND_XD	m_hWnd;
	CPropertyPage(void* wnd) { m_hWnd = wnd; };
	static CPropertyPage* FromHandle(HWND wnd) { return new CPropertyPage(wnd); };
};

class CPalette {
public:
	static CPalette* FromHandle( HPALETTE hPalette ) { return NULL; };
	UINT GetPaletteEntries( UINT nStartIndex, UINT nNumEntries, LPPALETTEENTRY lpPaletteColors ) const { return 0; };
};
*/

/*
#undef GetTextExtentPoint32
BOOL_XD GetTextExtentPoint32(
			HDC_XD hdc,			// handle to DC
			LPCTSTR lpString,	// text string
			int c,				// characters in string
			LPSIZE lpSize		// string size
);
*/

/*
CWinApp* AfxGetApp();
*/

/*
DWORD WaitForSingleObject(
			HANDLE hHandle,
			DWORD dwMilliseconds
);
*/

/*
HANDLE CreateMutexA(
			LPSECURITY_ATTRIBUTES lpMutexAttributes,
			BOOL_XD bInitialOwner,
			LPCTSTR lpName
);
*/

/*
DWORD GetCurrentProcessId(void);
*/

/*
BOOL_XD VerQueryValue(      
			LPCVOID pBlock,
			LPCTSTR lpSubBlock,
			LPVOID *lplpBuffer,
			PUINT puLen
);
*/

/*
struct VS_FIXEDFILEINFO { 
	DWORD dwSignature; 
	DWORD dwStrucVersion; 
	DWORD dwFileVersionMS; 
	DWORD dwFileVersionLS; 
	DWORD dwProductVersionMS; 
	DWORD dwProductVersionLS; 
	DWORD dwFileFlagsMask; 
	DWORD dwFileFlags; 
	DWORD dwFileOS; 
	DWORD dwFileType; 
	DWORD dwFileSubtype; 
	DWORD dwFileDateMS; 
	DWORD dwFileDateLS; 
};
*/

/*
BOOL_XD GetFileVersionInfo(      
			LPCTSTR lptstrFilename,
			DWORD dwHandle,
			DWORD dwLen,
			LPVOID lpData
);
*/

/*
DWORD GetFileVersionInfoSize(      
			LPCTSTR lptstrFilename,
			LPDWORD lpdwHandle
);
*/

/*
DWORD GetSysColor(
			int nIndex
);
*/

/*
HMODULE GetModuleHandle(
			LPCTSTR lpModuleName   // モジュール名
);
*/

/*
HPEN_XD CreatePenIndirect(
			CONST LOGPEN_XD *lplgpn   // スタイル、幅、色を保持している構造体
);
*/

/*
LONG RegOpenKeyExW(
			HKEY hKey,         // 開いている親キーのハンドル
			LPCWSTR lpSubKey,  // 開くべきサブキーの名前
			DWORD ulOptions,   // 予約済み
			REGSAM samDesired, // セキュリティアクセスマスク
			HKEY* phkResult    // 開くことに成功したサブキーのハンドル
);

LONG RegQueryValueExW(
			HKEY hKey,            // キーのハンドル
			LPCWSTR lpValueName,  // レジストリエントリ名
			LPDWORD lpReserved,   // 予約済み
			LPDWORD lpType,       // データ型が格納されるバッファ
			LPBYTE lpData,        // データが格納されるバッファ
			LPDWORD lpcbData      // データバッファのサイズ
);

LONG RegCreateKeyExW(
			HKEY hKey,                                  // 開くべきキーのハンドル
			LPCWSTR lpSubKey,                           // サブキーの名前
			DWORD Reserved,                             // 予約済み
			LPWSTR lpClass,                             // クラスの文字列
			DWORD dwOptions,                            // 特別なオプション
			REGSAM samDesired,                          // 希望のセキュリティアクセス権
			LPSECURITY_ATTRIBUTES lpSecurityAttributes, // 継承の指定
			PHKEY phkResult,                            // キーのハンドル
			LPDWORD lpdwDisposition    // 既存かどうかを示す値が格納される変数
);

LONG RegSetValueExW(
			HKEY hKey,           // 親キーのハンドル
			LPCWSTR lpValueName, // レジストリエントリ名
			DWORD Reserved,      // 予約済み
			DWORD dwType,        // レジストリエントリのデータ型
			CONST BYTE *lpData,  // レジストリエントリのデータ
			DWORD cbData         // レジストリエントリのデータのサイズ
);
*/

/*
HANDLE OpenEvent(
			DWORD dwDesiredAccess,  // アクセス権
			BOOL_XD bInheritHandle,    // 継承オプション
			LPCTSTR lpName          // イベントオブジェクトの名前
);
*/

/*
BOOL_XD ResetEvent(
			HANDLE hEvent   // イベントオブジェクトのハンドル
);
*/

/*
BOOL_XD SetEvent(
			HANDLE hEvent   // イベントオブジェクトのハンドル
);
*/

/*
HANDLE CreateMutex(
			LPSECURITY_ATTRIBUTES lpMutexAttributes,  // セキュリティ記述子
			BOOL_XD bInitialOwner,                       // 最初の所有者
			LPCTSTR lpName                            // オブジェクトの名前
);
*/

/*
SHORT GetAsyncKeyState(
			int vKey   // 仮想キーコード
);
*/

/*
HWND HtmlHelpA(
			HWND hwndCaller,
			LPCSTR pszFile,
			UINT uCommand,
			DWORD_PTR dwData
);
*/

/*
unsigned short *_wstrdate(
			unsigned short *datestr 
);

unsigned short *_wstrtime(
			unsigned short *timestr 
);
*/

/*
void DDX_Check(
			CDataExchange* pDX,
			int nIDC,
			int& value 
);

void DDX_Check(
			CDataExchange* pDX,
			int nIDC,
			BOOL_XD& value 
);

void DDX_Text(
			CDataExchange* pDX,
			int nIDC,
			CString& value 
);

void DDV_MaxChars(
			CDataExchange* pDX,
			CString const& value,
			int nChars 
);

void DDX_Control(
			CDataExchange* pDX,
			int nIDC,
			CWnd& rControl 
);
*/

/*
void OutputDebugString(
			const char* message
);
*/


#endif /* WINDOWS_H */

