// File: DWSPswdA.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999-2005 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _DWSPSWDA_H_
#define _DWSPSWDA_H_

#include "../mpcinc/mpc_secu.h"
#include "../mpcinc/mpc_cryp.h"
#include "mpc_pswd.h"	// V4.1

#ifndef _M3CORE_MP_
#include "dwresutl.h"
#endif

// バージョン
// UTがすむまでは 0
// 1999.06.08 UT中にフォーマットが変わったのでとりあえず1とする
#define DWSPSWD_VERSION		1

// V5:128bit版のセキュリティ情報のバージョン
#define DWSPSWD_VERSION_128		2

// コメントの最大領域サイズ(NULL含む)
#define DWSPSWD_COMMENT_MAX_SIZE	1001

// フルアクセスモード時の全てOKのパーミッション
#define DWSPSWD_PERM_ALL_OK	(MP_PERM_FULL | MP_PERM_DOC_EDIT | MP_PERM_ANNO_EDIT | MP_PERM_PRINT | MP_PERM_COPY)

// 秘密定数の型定義(8Byte)
typedef __int64 DWSPSWD_SecretNumber;

// セキュリティ情報に埋め込む乱数のサイズ
#define DWSPSWD_RAND_SIZE		4

// セキュリティ情報に埋め込む O_Key, U_Key のサイズ
#define DWSPSWD_O_U_KEY_SIZE	20

// SHA1のハッシュ値のサイズ
#define DWSPSWD_SHA1_SIZE		20

// MAC のサイズ
#define DWSPSWD_MAC_SIZE		8

// EXE との通信時にイベント待ちをタイムアウトする時間[ms]
//#define DWSPSWD_TIMEOUT_TIME	INFINITE	// タイムアウトなし
#define DWSPSWD_TIMEOUT_TIME	5000		// 5秒

// EXE の起動確認または通信失敗のリトライ時に待つ時間の最大と間隔[ms]
#define DWSPSWD_IDLETIME_MAX	2000
#define DWSPSWD_IDLETIME_UNIT	50

// セキュリティ対応 12/03/02 Bito
typedef bool BOOL;

// MFC
#ifndef _M3CORE_MP_
class CDWSPswdAApp : public CWinApp
{
protected:
	CDwResourceModuleManager m_resMgr; // 言語リソース

public:
	CDWSPswdAApp();

	// for ClassWizard
	//{{AFX_VIRTUAL(CDWSPswdAApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CDWSPswdAApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif

// dll ロード時に呼ばれる関数
DLLBINDFUNC_(MPCObject*, MPCSPI_DLLCreateMPCObject)(MP_RefObjectType type);


// MPCSecuritySPIの実体
class ImplPswdSecurityTemplateSPI;
class ImplSecuritySPI : MPCSecuritySPI5
{
public:
    // セキュリティ対応 12/03/02 Bito
	STDMETHOD(OpenSecurity)(MPS_SecurityInfo* pSecurityInfo, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, void* authdata, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle, MPS_SDataKey* pDataKey, MPS_SPermission* pAuthenticatedPerm);
	//STDMETHOD(OpenSecurity)(MPS_SecurityInfo* pSecurityInfo, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle, MPS_SDataKey* pDataKey, MPS_SPermission* pAuthenticatedPerm);
	STDMETHOD(AddAuthentication)(MPS_SecurityHandle securityHandle, MP_Permission requestedPerm, MPS_DataBlock* pNonce, MP_AuthMode mode, MPS_SPermission* pAuthenticatedPerm);
	STDMETHOD(GetAuthenticatedPermission)(MPS_SecurityHandle securityHandle, MPS_DataBlock* pNonce, MPS_SPermission* pAuthenticatedPerm);
	STDMETHOD(GetPermission)(MPS_SecurityInfo* pSecurityInfo, MP_Permission* pPerm);
	STDMETHOD(GetNewSecurityInfo)(MPS_SecurityHandle securityHandle, MPS_DataBlock* pNonce, MPS_SecurityLabel* pSecurityLabel, MPS_SDataKey* pDataKey, MPS_SecurityInfo* pSecurityInfo);
	STDMETHOD(CloseSecurity)(MPS_SecurityHandle securityHandle);
	STDMETHOD(EditSecurity)(MPS_SecurityHandle securityHandle);
	STDMETHOD(CreateSecurity)(MPS_DataBlock* pNonce, MPS_SecurityTemplate* pSecurityTemplate, MPS_DataBlock* pSessionKey, MPS_SecurityHandle* pSecurityHandle);
	STDMETHOD(ShowSecurity)(MPS_SecurityInfo* pSecurityInfo);
	STDMETHOD(OnBeginPrint)(MPS_SecurityHandle securityHandle, MP_Canvas* pCanvas, MPCObject* pBasicPage);
	STDMETHOD(OnEndPrint)(MPS_SecurityHandle securityHandle, MP_Canvas* pCanvas, MPCObject* pBasicPage);
	STDMETHOD(GetPermissionFromCache)(MPS_SecurityHandle securityHandle, MP_Permission* pPerm);
	STDMETHOD(CreateSecurityIcon)(MP_Integer type, HBITMAP* phBitmap);
	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres);
	STDMETHOD(Destroy)();
	// V5
	STDMETHOD(CreateSecurityTemplate)(MPC_SecurityTemplate** ppSecutiryTemplate);
	STDMETHOD(DestroySecurityTemplate)(MPC_SecurityTemplate* pSecutiryTemplate);
	STDMETHOD(GetSecurityName)(char* pSecurityName);

	// V5:128bit対応
	ImplSecuritySPI(MP_RefInterfaceID iid = MPC_IID_SecuritySPI_Pswd);
	ImplPswdSecurityTemplateSPI* m_pPswdTemplateSPI;

	// V5:128bit対応
	MP_InterfaceID m_iid;
	int GetDataKeySize();
	int GetVersion();
	const char* GetLabel();
	MPS_CryptType GetCryptType();
	UINT GetChangePermDlgTitleID();
	long GetSecurityType();

	// マルチスレッド対応
	unsigned int m_seed;

};

// DWSPswd のセキュリティ情報
typedef struct tag_DWSPswdSecurityInfo {
	int nSize;							// この構造体のサイズ
	int nVersion;						// バージョン
	char rand1[DWSPSWD_RAND_SIZE];		// 乱数1
	char rand2[DWSPSWD_RAND_SIZE];		// 乱数2
	char ukey[DWSPSWD_O_U_KEY_SIZE];	// 開くパスワードの情報
	char okey[DWSPSWD_O_U_KEY_SIZE];	// フルアクセスパスワードの情報
	MPS_CryptType cryptType;			// 文書暗号化アルゴリズム識別子
	MP_Permission perm;					// 文書のパーミッション
	int nCommentSize;					// コメントのサイズ(NULL含まず、純粋な文字数(バイト))
} DWSPswdSecurityInfo;

// DWSPswd のセキュリティオブジェクト
class CDWSPswdObject
{
public:
	CDWSPswdObject(DWSPswdSecurityInfo* pSecuInfo = NULL);
	// 内部データ
	BOOL m_bProtected;							// 保護されているかどうか
	BOOL m_bChanged;							// 設定が変更されたかどうか
	DWSPswdSecurityInfo m_secuInfo;				// セキュリティ情報
	char m_sessionKey[DWSPSWD_KEY_SIZE];		// セッション鍵
	MP_Permission m_perm;						// 文書に設定されているパーミッション
	MP_Permission m_authPerm;					// 認証済みパーミッション
	char m_openPswd[DWSPSWD_PSWD_MAX_SIZE];		// 開くパスワード
	char m_rootPswd[DWSPSWD_PSWD_MAX_SIZE];		// フルアクセスパスワード
	char m_comment[DWSPSWD_COMMENT_MAX_SIZE];	// コメント
};

// DWSPswd.exe のパスを取得する関数(レジストリから読み込む)
HRESULT GetDWSPswdExePath(char* sExePath);

// ヘルプファイルのパスを取得する関数
HRESULT GetDWSPswdHelpPath(char* sHelpPath);

// パスワード文字列に正しい値が設定されているかどうかチェックする関数
BOOL CheckPswdStr(LPCSTR str);

// V4.1 開くパスワード保存フラグを取得する関数(レジストリから)
HRESULT GetCacheFlag(BOOL* pbCachePswd);

// V4.1 開くパスワード保存フラグを書き込む関数(レジストリに)
HRESULT SetCacheFlag(BOOL bCachePswd);

// V4.1 セキュリティテンプレートインタフェースの実装
class ImplPswdSecurityTemplateSPI : MPCPswdSecurityTemplateSPI
{
public:
STDMETHOD(CreateSecurityTemplate)(MPS_SecurityStruct_Pswd* pSecurityStruct, MPC_SecurityTemplate** ppSecutiryTemplate);
STDMETHOD(DestroySecurityTemplate)(MPC_SecurityTemplate* pSecutiryTemplate);
STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres);
STDMETHOD(Destroy)();

// V5:128bit対応
ImplPswdSecurityTemplateSPI(int nVersion = DWSPSWD_VERSION);
~ImplPswdSecurityTemplateSPI();
int m_nVersion;
long GetSecurityType();
};

// V4.1 パスワード用セキュリティテンプレートの実体
typedef struct tag_DWSPswdTemplate {
	int nSize;								// この構造体のサイズ
	int nVersion;							// バージョン
	MP_Permission	perm;					// 開くときのパーミッション指定
	char szOpenPswd[MPS_PSWD_MAX_PSWD];		// 開くパスワード
	char szRootPswd[MPS_PSWD_MAX_PSWD];		// フルアクセスパスワード
	char szComment[MPS_PSWD_MAX_COMMENT];	// コメント
} DWSPswdTemplate;

// V5:ユーティリティ ポインタの解放を自動で行うクラス
class DWSPPointerMgr
{
public:
	DWSPPointerMgr(char* pPtr = NULL);
	~DWSPPointerMgr();
	void SetPointer(char* pPtr);
	void DeletePointer();
protected:
	char* m_pPtr;
};

#endif // _DWSPSWDA_H_

// CHANGE LOG
// 1999.01.22 - Nakazawa - 新規作成
// 1999.05.31 - Nakazawa - GetPermissionFromCache 追加
// 1999.06.11 - Nakazawa - AddAuthentication に対話モードを追加
// 1999.06.16 - Nakazawa - CreateSecurity で pSecurityTemplate の宣言を void* に変更
// 1999.06.18 - Nakazawa - CreateSecurity で pSecurityTemplate の宣言を MPS_SecurityTemplate* に変更
// 1999.06.30 - Nakazawa - mpcapi.lib をリンクしないように修正
// 1999.07.05 - Nakazawa - CreateSecurityIcon 追加
// 1999.08.06 - Nakazawa - AR4169対応：キャッシュに失敗する場合があるのでリトライするコードを追加
// 1999.08.09 - Nakazawa - ヘルプの実装を追加
// 2000.09.25 - Nakazawa - V4.1 キャッシュするかしないかのフラグを参照・保持する関数を追加
// 2000.09.25 - Nakazawa - V4.1 セキュリティテンプレートの実装を追加
// 2000.10.12 - Nakazawa - V4.1 コードレビューの結果を反映
// --- V5 開発
// 2002.02.08 - Tashiro - 新規I/F追加(一括設定など)
// 2002.02.19 - Nakazawa - 128bit暗号対応
// 2002.02.20 - Nakazawa - ポインタの解放を自動で行うクラスの追加
// 2002.02.22 - Nakazawa - コードレビューの結果を反映
// 2002.05.14 - Nakazawa - 一括設定時の128bit暗号対応漏れを修正
// 2002.11.06 - Komoda - 5.0Eng 言語リソースの読み込み対応
// --- V6.0.5 開発
// 2005.11.09 - Nakazawa - 64bit 2.0対応
//----- マルチスレッド対応
// 2006.05.26 - Kudo - マルチスレッド対応：乱数のseedをメンバとして保持
// 2006.06.12 - Okamoto - マルチスレッド対応：
// 2006.06.20 - Okamoto - マルチスレッド対応：コメント追加
// 2006.10.26 - Kudo - AR13264 OpenSecurityはの複合化/再暗号化の部分だけを排他する
// 2007.12.12 - k-okamoto - 2.1対応
