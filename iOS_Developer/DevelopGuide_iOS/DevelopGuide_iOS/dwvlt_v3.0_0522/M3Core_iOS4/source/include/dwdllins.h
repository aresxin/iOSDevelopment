#ifndef _DW_DLL_INS_H_
#define _DW_DLL_INS_H_

// DocuWorks関連のDLLを動的にロードするときに使える基底クラス。
// 各DLLに対応した派生クラスを作って利用する。

// スレッドセーフな状況を想定して作ってあるが、V60時点ではマルチスレッドから使われる状況にはないため、
// 複数のスレッドから呼ばれる場合には、正しく動作するかをきちんと検証すること

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////
// CDwThreadInstance
// 一つのスレッドで一つのDLLがロードされるように、スレッドIDとハンドルの対で管理するクラス
class CDwThreadInstance {
public:
	CDwThreadInstance() { 
		m_hInst = NULL; 
		m_dwThreadID = 0; 
	}
	CDwThreadInstance(LPCTSTR lpszPath) {
		CDwThreadInstance();
		Create(lpszPath);
	}
	
	virtual ~CDwThreadInstance() { 
		Delete(); 
	}

	HINSTANCE Create(LPCTSTR lpszPath) {
		if (m_hInst == NULL) {
			m_hInst = ::LoadLibrary(lpszPath);
		}
		m_dwThreadID = ::GetCurrentThreadId();

		return m_hInst;
	}

	void Delete() {
		if (m_hInst != NULL) {
			::FreeLibrary(m_hInst);
			m_hInst = NULL;
		}
		m_dwThreadID = 0;
	}

	HINSTANCE GetThreadInstance() {
		return m_hInst;
	}

	DWORD GetThreadID() {
		return m_dwThreadID;
	}

protected:
	HINSTANCE m_hInst;
	DWORD m_dwThreadID;
};

/////////////////////////////////////////////////////////////////////////////
// CDllInsMutex
// MFCのCMutexから必要なものだけをコピーして作成したMutexクラス
class CDllInsMutex
{
	HANDLE  m_hObject;

// Constructor
public:
	CDllInsMutex(BOOL bInitiallyOwn = FALSE, LPCTSTR lpszName = NULL,
		LPSECURITY_ATTRIBUTES lpsaAttribute = NULL) {
		m_hObject = NULL;
		m_hObject = ::CreateMutex(lpsaAttribute, bInitiallyOwn, lpszName);
	}
	virtual ~CDllInsMutex() {
		if (m_hObject != NULL) {
			::CloseHandle(m_hObject);
			m_hObject = NULL;
		}
	}

// Implementation
public:
	BOOL Lock(DWORD dwTimeout = INFINITE) {
		if (::WaitForSingleObject(m_hObject, dwTimeout) == WAIT_OBJECT_0)
			return TRUE;
		else
			return FALSE;
	}
	BOOL Unlock() {
		return ::ReleaseMutex(m_hObject);
	}
};


/////////////////////////////////////////////////////////////////////////////
// CDwThreadInstance
// CDwThreadInstanceの配列を保持し、複数のスレッドから呼ばれても影響がないように
// Mutexを使用して排他したクラス
class CDwDllInstance
{
protected:
	CDwThreadInstance** m_pDllInsArray;
	CDllInsMutex m_mutex;
	int m_count;
	char m_pszDllName[_MAX_PATH];	// ☆これを派生クラスのコンストラクタで各DLL毎にセットする
	BOOL m_bDllInBinPath;			// ☆DLLがBinの直下ならTRUE、Systemなどパスの通ったところならFALSE
	char m_pszDllPath[_MAX_PATH];	// DLLのフルパス。必要に応じて直接パスを書き込んでも良い
public:
	CDwDllInstance() : m_pDllInsArray(NULL), m_bDllInBinPath(TRUE) { *m_pszDllPath = NULL; *m_pszDllName = NULL; m_count = 0; }
	virtual ~CDwDllInstance() {
		if (m_pDllInsArray != NULL) {
			int count = m_count;
			for (int i=0; i<count; i++) {
				FreeInstance();
			}
		}
		*m_pszDllPath = NULL;

		if (m_pDllInsArray != NULL) {
			m_mutex.Lock();
			delete[] m_pDllInsArray;
			m_pDllInsArray = NULL;
			m_mutex.Unlock();
		}
	}

	HINSTANCE GetInstance() {
		m_mutex.Lock();
		if (*m_pszDllPath == NULL) {
			GetDllPath(m_pszDllPath);		
		}
		// まず同じスレッドですでにロードされているかを調べる
		for (int i=0; i<m_count; i++) {
			CDwThreadInstance* dwThreadIns = NULL;
			dwThreadIns = (CDwThreadInstance*)m_pDllInsArray[i];
			if (dwThreadIns->GetThreadID() == ::GetCurrentThreadId()) {
				m_mutex.Unlock();
				return dwThreadIns->GetThreadInstance();
			}
		}
		// 同じスレッドでロードされていなかったらLoadLibraryする
		CDwThreadInstance* dwThreadIns2 = new CDwThreadInstance;
		if (dwThreadIns2 == NULL) return NULL;
		dwThreadIns2->Create(m_pszDllPath);

		CDwThreadInstance** pNewArray = new CDwThreadInstance*[m_count+1];
		if (pNewArray == NULL) {
			if (dwThreadIns2 != NULL)
				delete dwThreadIns2;
			return NULL;
		}
		for (int i=0; i<m_count; i++) {
			pNewArray[i] = m_pDllInsArray[i];
		}
		pNewArray[m_count] = dwThreadIns2;

		if (m_pDllInsArray != NULL) {
			delete[] m_pDllInsArray;
		}
		m_pDllInsArray = pNewArray;
		m_count++;
		m_mutex.Unlock();
		return dwThreadIns2->GetThreadInstance();
	}

	void FreeInstance() {
		m_mutex.Lock();
		for (int i=0; i<m_count; i++) {
			CDwThreadInstance* dwThreadIns = (CDwThreadInstance*)m_pDllInsArray[i];
			if (dwThreadIns->GetThreadID() == ::GetCurrentThreadId()) {
				// 同じスレッドIDのものをdeleteする
				delete dwThreadIns;
				m_count--;

				// 削除した分の配列をつめる。上でm_countは1減らしているのでm_countまででOK
				for (int j=i; j<m_count; j++) {
					m_pDllInsArray[j] = m_pDllInsArray[j+1];
				}
				m_mutex.Unlock();
				return;
			}
			m_mutex.Unlock();
		}
	}

protected:
	virtual BOOL GetDllPath(char* pszDllPath) {	// 必要に応じてオーバーライドしてよい
		*pszDllPath = NULL;	// 念のため初期化
		if (*m_pszDllName == NULL)
			return FALSE;
		if (m_bDllInBinPath) {
			char pszDwBinPath[_MAX_PATH] = "";
			GetDwBinPathWithYen(pszDwBinPath);
			wsprintf(pszDllPath, "%s%s", pszDwBinPath, m_pszDllName);
		} else {
			strcpy(pszDllPath, m_pszDllName);
		}
		return TRUE;
	}
private:
	BOOL GetDwBinPathWithYen(char* pszBinPath) {	// "...\DocuWorks\bin\"を取得するユーティリティ関数
		
		BOOL bRes = FALSE;
		HKEY hSubKey = NULL;
		//dw6.0.5以降で設定されるレジストリを使う。
		const char* const KEYNAME_MPM3 = "Software\\FujiXerox\\MPM3";
		const char* const INSTALLPATH = "InstallPath";
		if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, KEYNAME_MPM3, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
			char pszValue[_MAX_PATH] = "";
			DWORD dwType = REG_SZ, dwSize = _MAX_PATH;
			if ((::RegQueryValueEx(hSubKey, INSTALLPATH, NULL, &dwType, (LPBYTE)pszValue, &dwSize) == ERROR_SUCCESS)
				&& (dwType == REG_SZ)) {
				wsprintf(pszBinPath, "%s\\bin\\", pszValue);
				bRes = TRUE;
			}
			::RegCloseKey(hSubKey);
		}		
		// 上記レジストリ参照に失敗したらビューアのパスから作る
		if(bRes == FALSE){
			const char* const KEYNAME_MPM3_MPM3 = "Software\\FujiXerox\\MPM3\\MPM3";
			const char* const VALUENAME_PATH = "PATH";
			if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, KEYNAME_MPM3_MPM3, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
				char pszValue[_MAX_PATH] = "";
				DWORD dwType = REG_SZ, dwSize = _MAX_PATH;
				if ((::RegQueryValueEx(hSubKey, VALUENAME_PATH, NULL, &dwType, (LPBYTE)pszValue, &dwSize) == ERROR_SUCCESS)
					&& (dwType == REG_SZ)) {
					char pszDrive[_MAX_DRIVE] = "", pszDir[_MAX_DIR] = "";
					_splitpath(pszValue, pszDrive, pszDir, NULL, NULL);
					wsprintf(pszBinPath, "%s%s", pszDrive, pszDir);
					bRes = TRUE;
				}
				::RegCloseKey(hSubKey);
			}
		}
		return bRes;
	}
};

#endif // _DW_DLL_INS_H_
