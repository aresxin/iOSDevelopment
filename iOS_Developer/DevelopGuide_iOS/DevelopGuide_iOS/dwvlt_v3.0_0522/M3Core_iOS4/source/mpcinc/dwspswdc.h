// File: DWSPswdC.h (DWSPswd Common)
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

// DWSPswd exe と dll 間で共通して用いるヘッダファイル

#ifndef _DWSPSWD_COMMON_H_
#define _DWSPSWD_COMMON_H_

#ifdef _M3CORE_MP_
#include <string.h> // for memset()
#endif // _M3CORE_MP_

// パスワードの最大文字数(NULL含む)
#define DWSPSWD_PSWD_MAX_SIZE		256

// キャッシュするパスワードの数
#define DWSPSWD_PSWD_MAX_CACHE_NUM	20

// 固定鍵の型定義(8Byte)
#ifdef _M3CORE_MP_
typedef long long DWSPSWD_SecretKey;
#else
typedef __int64 DWSPSWD_SecretKey;
#endif // _M3CORE_MP_

// 文書・セッション鍵のサイズ
#define DWSPSWD_KEY_SIZE		8

// V5:128bit版のデータ鍵サイズ
#define DWSPSWD_KEY_SIZE_128	16

// DWSPswd のタイトル
#define DWSPSWD_TITLE			"DWSPswd"

// DWSPswd.exe のウィンドウの名前
#define DWSPSWD_WINDOW_NAME		"DWSPswd Window"

// データ共有用ファイルマッピング識別子
#define DWSPSWD_SHAREDATA_NAME	"DWSPswd ShareData"

// 保護情報処理中を示す Mutex 名
#define DWSPSWD_PROCESSING		"DWSPswd Processing"

// DWSPswd.exe のメニュー処理中を示す Mutex 名
#define DWSPSWD_MENU_PROCESSING	"DWSPswd Menu Processing"

// すでにキャッシュされているパスワードを取得するイベント名
// DWSPswd.exe 側で Create/Close、dll 側で Open/Close/Set/Reset
#define DWSPSWD_EVENT_GET_CACHED_PSWDS	"DWSPswd Event GetCachedPswds"

// 新しいパスワードをキャッシュするイベント名
// DWSPswd.exe 側で Create/Close、dll 側で Open/Close/Set/Reset
#define DWSPSWD_EVENT_CACHE_PSWD	"DWSPswd Event CachePswd"

// パスワード鍵受け渡し用のイベント名
// DWSPswd.exe 側で Create/Close、dll 側で Open/Close/Set/Reset
#define DWSPSWD_EVENT_GET_KEY		"DWSPswd Event GetKey"

// DWSPswd.exe での処理が終わったことを示すイベント名
// DWSPswd.exe 側で Create/Close/Set/Reset、dll 側で Open/Close
#define DWSPSWD_EVENT_GET_CACHED_PSWDS_FINISHED	"DWSPswd Event GetCachedPswds Finished"
#define DWSPSWD_EVENT_CACHE_PSWD_FINISHED		"DWSPswd Event CachePswd Finished"
#define DWSPSWD_EVENT_GET_KEY_FINISHED			"DWSPswd Event GetKey Finished"

// パスワードキャッシュ関係のデータ受け渡し用構造体
// パスワード鍵を受け渡す際のデータ
typedef struct tag_StructForGetKey {
	int nSize;							// この構造体のサイズ
	char nonce[DWSPSWD_KEY_SIZE];		// 通信用データ(鍵と同じサイズ)
	char sessionKey[DWSPSWD_KEY_SIZE];	// 保護されたセッション鍵
	char pswdKey[DWSPSWD_KEY_SIZE];		// 保護されたパスワード鍵
	tag_StructForGetKey() {
		nSize = sizeof(struct tag_StructForGetKey);
		memset(sessionKey, 0, DWSPSWD_KEY_SIZE);
		memset(pswdKey, 0, DWSPSWD_KEY_SIZE);
	}
} StructForGetKey;

// パスワードをキャッシュする際のデータ
// (パスワードは暗号化したまま送るので、通信用の乱数は必要ない)
typedef struct tag_StructForCachePswd {
	int nSize;							// この構造体のサイズ
	char pswd[DWSPSWD_PSWD_MAX_SIZE];	// これからキャッシュするパスワード
	tag_StructForCachePswd() {
		nSize = sizeof(struct tag_StructForCachePswd);
		memset(pswd, 0, DWSPSWD_PSWD_MAX_SIZE);
	}
} StructForCachePswd;

// キャッシュされているパスワードを取得する際のデータ
// (パスワードは暗号化したまま送るので、通信用の乱数は必要ない)
typedef struct tag_StructForGetCachedPswd {
	int nSize;						// この構造体のサイズ
	int nCachedPswds;				// すでにキャッシュされているパスワードの数
	char cachedPswds[DWSPSWD_PSWD_MAX_CACHE_NUM][DWSPSWD_PSWD_MAX_SIZE];	// すでにキャッシュされているパスワード
	tag_StructForGetCachedPswd() {
		nSize = sizeof(struct tag_StructForGetCachedPswd);
		nCachedPswds = 0;
		memset(cachedPswds, 0, DWSPSWD_PSWD_MAX_CACHE_NUM * DWSPSWD_PSWD_MAX_SIZE);
	}
} StructForGetCachedPswd;

// 12.02.17 Bito - セキュリティ対応
#ifdef _SEC_MP_
// パスワードセキュリティ文書を開くために必要となるデータ（OpenMP()の引数にvoid*型で渡す）
typedef struct {
    int size;								// この構造体のサイズ
    int type;								// セキュリティの種類
    char password[DWSPSWD_PSWD_MAX_SIZE];	// 文書を開くためのパスワード
} PasswordSecurityAuthData;
#endif

#endif // _DWSPSWD_COMMON_H_

// CHANGE LOG
// 1999.01.22 - Nakazawa - 新規作成
// 1999.06.08 - Nakazawa - 構造体の定義を修正
// 1999.07.06 - Nakazawa - 不必要な定義を削除
// 2002.02.19 - Nakazawa - 128bit暗号対応
